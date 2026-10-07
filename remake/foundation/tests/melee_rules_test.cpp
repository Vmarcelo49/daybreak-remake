// NN.dat collision/clock integration. Real combat uses an equipped item and its
// bundle-winning rig; synthetic rigs below isolate selector/blend/period contracts.
#include "combo_fixture.h"
#include "gameplay/melee_rules.h"
#include "gameplay/match.h"
#include <array>
#include <cmath>
#include <cstdio>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace {
namespace fs = std::filesystem;
using gameplay::Fighter;
using gameplay::FighterState;
namespace input = fnd::input;
int checks = 0, failures = 0, skipped = 0;
void check(bool condition, const char* name) {
    ++checks;
    if (!condition) ++failures;
    std::printf("  %-60s %s\n", name, condition ? "ok" : "FAIL");
}

void checkInt(int expected, int actual, const char* name) {
    ++checks;
    const bool same = expected == actual;
    if (!same) ++failures;
    std::printf("  %-60s %s", name, same ? "ok" : "FAIL");
    if (!same) std::printf("  (expected %d, got %d)", expected, actual);
    std::printf("\n");
}

void skip(const char* name) {
    ++skipped;
    std::printf("  %-60s SKIP\n", name);
}

void section(const char* title) { std::printf("\n-- %s\n", title); }

void tick(Fighter& f, const input::PlayerState& in) {
    input::PlayerState copy = in;
    input::compute_edges(copy);
    f.update(&copy, nullptr, 1.0 / 64.0);
}

void tick_held(Fighter& f, input::PlayerState& in) {
    input::compute_edges(in);
    f.update(&in, nullptr, 1.0 / 64.0);
}

void bind_synthetic_rig(Fighter& f, xm::Model& model, xm::Controller& ctrl,
                        const glm::vec3& at, float durationTicks = 480000.0f) {
    model.anims.clear();
    model.ticksPerSecond = 4800.0f;
    for (int i = 0; i < 124; ++i) {
        xm::AnimSet a;
        a.name = "Anim-" + std::to_string(124 - i);
        a.duration = durationTicks;
        model.anims.push_back(a);
    }
    ctrl.bind(&model);
    f.init(&model, &ctrl, at, 0.0f);
    input::PlayerState idle;
    for (int i = 0; i < 70; ++i) tick(f, idle);
}

void double_tap(Fighter& f, int action) {
    input::PlayerState in;
    in.down[action] = true;
    tick(f, in);
    in.down[action] = false;
    tick(f, in);
    in.down[action] = true;
    tick(f, in);
    in.down[action] = false;
}

fs::path findInstall(int argc, char** argv) {
    if (argc > 1) return fs::path(argv[1]);
    if (const char* env = std::getenv("GAME_DIR")) return fs::path(env);
    fs::path game = fs::path("Higurashi-Daybreak");
    for (const fs::path& d : {fs::absolute(fs::path(argv[0])).parent_path(),
                              fs::current_path()}) {
        for (fs::path r = d; !r.empty(); r = r.parent_path()) {
            std::error_code ec;
            if (fs::is_directory(r / "remake" / "foundation", ec)) {
                game = r / "Higurashi-Daybreak";
                break;
            }
            if (r == r.parent_path()) break;
        }
        std::error_code ec;
        if (fs::is_directory(game / "data", ec)) return game;
    }
    return fs::path();
}

bool load_weapon(const fs::path& install, int itemId, gameplay::WeaponDefinition& out) {
    char path[40]; std::snprintf(path,sizeof path,"data/item/%03d.dat",itemId);
    std::vector<uint8_t> bytes; std::string error;
    return fnd::assets::assetSource().read(path,bytes) && out.parse(itemId,bytes.data(),bytes.size(),error);
}
bool load_moves(const fs::path& install, const char* character, const char* nn,
                gameplay::CharacterMoves& out) {
    const auto path = std::string("data/") + character + "/" + nn;
    std::vector<uint8_t> bytes; std::string error;
    if (!fnd::assets::assetSource().read(path,bytes) || !out.parse(bytes.data(),bytes.size(),error)) return false;
    out.set_character_index(gameplay::characterIndexForDir(character));
    return true;
}
void swing_to_active(Fighter& f) {
    input::PlayerState in;
    in.down[input::Action::AttackA] = true; tick_held(f,in);
    in.down[input::Action::AttackA] = false;
    for (int i = 0; i < 240 && f.state() == FighterState::AttackA && !f.melee_in_active(); ++i)
        tick_held(f,in);
}
xm::Model wall(glm::vec3 center) {
    xm::Model model; model.meshes.emplace_back();
    auto& mesh = model.meshes.back();
    for (glm::vec3 offset : {glm::vec3(-200,-200,0),glm::vec3(200,-200,0),
                            glm::vec3(200,200,0),glm::vec3(-200,200,0)}) {
        xm::Vertex vertex; vertex.pos = center + offset; mesh.vertices.push_back(vertex);
    }
    mesh.indices = {0,1,2,0,2,3};
    return model;
}
void testPosedCombat() {
    section("Rena+0: phase-local records and posed sphere/capsule collision");
    test::Combo combo; std::string error;
    if (!combo.load(0,0,error)) { skip("Rena+0 rig/item/moves unavailable"); return; }
    Fighter attacker, victim, second;
    combo.init(attacker); combo.init(victim); combo.init(second);
    input::PlayerState in; in.down[input::Action::AttackA] = true; tick_held(attacker,in);
    check(!attacker.melee_in_active(),"startup does not borrow a later phase's combat record");
    in.down[input::Action::AttackA] = false;
    for (int i = 0; i < 240 && !attacker.melee_in_active(); ++i) tick_held(attacker,in);
    check(attacker.melee_in_active() && attacker.move_phase() == 2,"neutral reaches phase two's combat record");
    const auto volume = attacker.hitbox_debug();
    check(volume.attacking && volume.capsule == (attacker.current_move_record()->collisionShape != 0) &&
          volume.attackRadius == 20.f,
          "Rena+0 current record supplies the posed shape and radius");
    test::Combo::placeAtAttack(attacker,victim,{0,400,0});
    check(!attacker.try_melee_hit(victim),"same XZ cannot hit a victim 400 units above the weapon");
    test::Combo::placeAtAttack(attacker,victim,{0,0,40});
    check(attacker.try_melee_hit(victim),"a chest anchor forty units from the actual weapon sphere connects");
    checkInt(92,victim.hp(),"the current record's power removes eight HP");
    int stunTicks = 0;
    while (victim.state() == FighterState::Hit && stunTicks < 60) {
        victim.update(nullptr,nullptr,1.0/64.0); ++stunTicks;
    }
    checkInt(6,stunTicks,"the current record supplies defender hitstop");
    test::Combo::placeAtAttack(attacker,second,{0,0,-40});
    check(attacker.try_melee_hit(second),"sphere distance has no cone/angle term around the weapon anchor");
    attacker.note_melee_hit(1); attacker.note_melee_hit(2);
    check(attacker.already_hit_this_swing(1) && attacker.already_hit_this_swing(2),
          "one swing remembers multiple victims");

    combo.init(attacker); combo.init(victim); swing_to_active(attacker);
    test::Combo::placeAtAttack(attacker,victim,{0,0,40});
    xm::Model mesh = wall(attacker.hitbox_debug().attackCenter + glm::vec3(0,0,20));
    game::physics::MovementCollision collision; collision.setMeshes(&mesh,nullptr);
    check(!attacker.try_melee_hit(victim,&collision),"solid geometry blocks the posed weapon-to-chest segment");
    check(attacker.try_melee_hit(victim),"the same posed pair connects without that barrier");
    for (int i = 0; i < 120 && attacker.melee_in_active(); ++i) tick_held(attacker,in);
    check(!attacker.try_melee_hit(victim),"the next noncombat record disables collision");
    attacker.take_damage(1,&victim);
    check(!attacker.try_melee_hit(victim),"interruption disables the old attack volume");
    combo.init(attacker); swing_to_active(attacker);
    for (int i = 0; i < 240 && attacker.state() == FighterState::AttackA; ++i) tick_held(attacker,in);
    check(attacker.state() == FighterState::Idle,"actual final-set period completes the attack without a recovery timer");
}
void testPosedMatch() {
    section("Match: current record damages each enemy once, never its ally");
    test::Combo combo; std::string error;
    if (!combo.load(0,0,error)) { skip("Rena+0 match fixture unavailable"); return; }
    gameplay::MatchConfig config; config.fighterCount = 4;
    const xm::Model* models[4]{}; xm::Controller* controllers[4]{};
    for (int i = 0; i < 4; ++i) {
        config.side[i] = i < 2 ? 0 : 1;
        config.moves[i] = &combo.moves; config.weapon[i] = &combo.weapon;
        models[i] = &combo.model; controllers[i] = combo.controller();
        config.spawn[i] = glm::vec3(2000.f * i,0,0);
    }
    gameplay::Match match; match.reset(config,models,controllers,nullptr,nullptr);
    match.economy().setLogFile(nullptr);
    const input::PlayerState* idle[4]{};
    for (int i = 0; i < 70; ++i) match.step(idle,1.0/64.0);
    input::PlayerState input; input.down[input::Action::AttackA] = true;
    const input::PlayerState* inputs[4] = {&input,nullptr,nullptr,nullptr};
    int enemyContacts = 0;
    for (int i = 0; i < 180; ++i) {
        input::compute_edges(input);
        if (match.fighter(0).melee_in_active())
            for (int victim = 1; victim < 4; ++victim)
                test::Combo::placeAtAttack(match.fighter(0),match.fighter(victim));
        match.step(inputs,1.0/64.0);
        enemyContacts = std::max(enemyContacts,match.fighter(0).swing_hit_count());
        input.down[input::Action::AttackA] = false;
    }
    checkInt(100,match.fighter(1).hp(),"the ally inside the actual volume takes no damage");
    checkInt(92,match.fighter(2).hp(),"first enemy is hit exactly once");
    checkInt(92,match.fighter(3).hp(),"second enemy is hit exactly once by the same swing");
    checkInt(2,enemyContacts,"Match reports both contacts and suppresses repeated overlap");
}
// The per-swing allowance proved THROUGH the scene, not by calling the flag helpers: the
// victim is re-placed inside the live volume on every active frame, so without the
// allowance the swing would land repeatedly. This is FUN_00637950's this+0x90 consumption
// (0x637cd7) as Match implements it (already_hit_this_swing before try_melee_hit).
void testRepeatContactSuppression() {
    section("Match: one swing damages a re-placed victim exactly once");
    test::Combo combo; std::string error;
    if (!combo.load(0,0,error)) { skip("Rena+0 match fixture unavailable"); return; }
    gameplay::MatchConfig config; config.fighterCount = 2;
    const xm::Model* models[2]{}; xm::Controller* controllers[2]{};
    for (int i = 0; i < 2; ++i) {
        config.side[i] = i;                      // opposed sides: hostile
        config.moves[i] = &combo.moves; config.weapon[i] = &combo.weapon;
        models[i] = &combo.model; controllers[i] = combo.controller();
        config.spawn[i] = glm::vec3(200.f * i,0,0);
    }
    gameplay::Match match; match.reset(config,models,controllers,nullptr,nullptr);
    match.economy().setLogFile(nullptr);
    const input::PlayerState* idle[2]{};
    for (int i = 0; i < 70; ++i) match.step(idle,1.0/64.0);
    match.fighter(0).set_state(FighterState::Idle);

    input::PlayerState input; input.down[input::Action::AttackA] = true;
    const input::PlayerState* inputs[2] = {&input,nullptr};
    int hpAfterFirst = -1, activeFrames = 0;
    for (int i = 0; i < 240; ++i) {
        input::compute_edges(input);
        if (match.fighter(0).melee_in_active()) {
            ++activeFrames;
            // Force the overlap the allowance exists for: every active frame starts with
            // the victim back inside the posed volume.
            test::Combo::placeAtAttack(match.fighter(0),match.fighter(1));
        }
        match.step(inputs,1.0/64.0);
        if (hpAfterFirst < 0 && match.fighter(1).hp() < match.fighter(1).max_hp())
            hpAfterFirst = match.fighter(1).hp();
        input.down[input::Action::AttackA] = false;
    }
    check(activeFrames > 1,"the neutral swing really spans more than one active frame");
    check(hpAfterFirst >= 0,"the swing connects with the re-placed victim");
    checkInt(hpAfterFirst,match.fighter(1).hp(),
             "and the victim keeps the HP from that single contact");
    checkInt(1,match.fighter(0).swing_hit_count(),
             "Match counted exactly one contact for the whole swing");
}

void testPhaseClock() {
    section("D3DX period / 0.016, strict boundary, counter gate");
    test::Combo combo; std::string error;
    if (!combo.load(0,0,error)) { skip("Rena+0 clock fixture unavailable"); return; }
    xm::Model model; xm::Controller controller; Fighter fighter;
    // Two original updates, not two seconds. The continuation gate must hold
    // independently of this deliberately tiny startup clip.
    bind_synthetic_rig(fighter,model,controller,{},153.6f);
    fighter.set_moves(&combo.moves); fighter.set_weapon(&combo.weapon);
    input::PlayerState input; input.down[input::Action::Up] = true;
    tick_held(fighter,input); input.down[input::Action::Up] = false; tick_held(fighter,input);
    input.down[input::Action::Up] = true; tick_held(fighter,input);
    checkInt(13,fighter.anim_set_index(),"dash binds its table's startup");
    checkInt(1,fighter.phase_elapsed(),"a normal handler update advances its phase clock");
    check(std::abs(controller.trackPosition(0) - gameplay::kOriginalAnimationTick) < 1e-8,
          "pose and record use the same elapsed times 0.016");
    tick_held(fighter,input);
    checkInt(13,fighter.anim_set_index(),"period equality does not switch phase");
    tick_held(fighter,input);
    checkInt(14,fighter.anim_set_index(),"strictly greater elapsed switches to continuation");
    checkInt(0,fighter.phase_elapsed(),"phase transition resets elapsed");
    for (int i = 0; i < 5; ++i) tick_held(fighter,input);
    checkInt(14,fighter.anim_set_index(),"nonzero counter gate holds beyond the tiny clip period");
    input.down[input::Action::Up] = false; tick_held(fighter,input);
    checkInt(15,fighter.anim_set_index(),"the recovered release event exits the gated phase");

    bind_synthetic_rig(fighter,model,controller,{});
    model.anims[13].duration = .008f * model.ticksPerSecond;
    fighter.set_moves(&combo.moves); fighter.set_weapon(&combo.weapon);
    double_tap(fighter,input::Action::Up);
    checkInt(14,fighter.anim_set_index(),"nearest-even half-update period rounds to zero");
}
void testCharacterMoveTable(const fs::path& install) {
    section("the character move table (recovered)");
    std::error_code ec;
    if (install.empty() || !fs::is_directory(install / "data" / "rena", ec)) {
        skip("parsing data/<char>/00.dat (no install found)");
        skip("confirming the melee chain carries no geometry");
        return;
    }
    const char* dirs[4] = {"rena", "keiichi", "mion", "satoko"};
    int parsed = 0;
    int withMoveChain = 0;
    for (const char* d : dirs) {
        std::ifstream in(install / "data" / d / "00.dat", std::ios::binary);
        if (!in) continue;
        const std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(in)),
                                         std::istreambuf_iterator<char>());
        gameplay::CharacterMoves moves;
        std::string err;
        if (!moves.parse(bytes.data(), bytes.size(), err)) {
            check(false, "every character move table parses");
            continue;
        }
        const int characterIndex = gameplay::characterIndexForDir(d);
        const int itemId = gameplay::kWeaponIds[characterIndex][0];
        gameplay::WeaponDefinition weapon;
        if (moves.weapon_id() != itemId || !load_weapon(install, itemId, weapon) ||
            weapon.id != itemId) {
            check(false, "the character table joins its slot-0 item data");
            continue;
        }
        moves.set_character_index(characterIndex);
        ++parsed;
        check(moves.count() > 50, "a character ships more than 50 moves");
        // The documented families must be present in the parsed data.
        check(moves.has(20) && moves.has(23) && moves.has(24) && moves.has(27),
              "the four directional dash moves (20/23/24/27) are present");
        check(moves.has(40) && moves.has(41) && moves.has(42),
              "the 40/41/42 jump chain is present");
        // FUN_00445ee0:412-422 conditionally transitions 300→301→302. This checks
        // only that these numeric move ids exist in the character table; it does not
        // identify shot cues, charge tiers, or a firing-animation selector.
        if (moves.has(300) && moves.has(301) && moves.has(302)) {
            ++withMoveChain;
            // Record +0x04 is read as a cancel-window threshold in FUN_0043ded0,
            // not established as a phase duration or a tier-specific shot timing.
            check(moves.cancel_threshold(300) > 0,
                  "move 300 carries a parsed cancel-window threshold");
        }
        // THE CLAIM, corrected by issue #26: moves 40/41/42 are the JUMP chain, not
        // the melee chain, and they carry no combat block. Real melee numbers live
        // in the 300-family weapon phases (Prop/Toe-bone entries below).
        int jumpChainCombat = 0;
        for (int id : {40, 41, 42}) {
            const gameplay::CharacterMove* m = moves.find(id);
            if (!m) continue;
            for (int p = 0; p < m->sectionCount; ++p)
                for (int e = 0; e < m->phases[p].entryCount; ++e)
                    if (m->phases[p].entries[e].has_combat()) ++jumpChainCombat;
        }
        check(jumpChainCombat == 0,
              "the 40/41/42 jump chain has no combat block");
        // Issue #26 anchors: each phase's section tag is the animation set index the
        // original binds (FUN_00421100/FUN_0041f580 via phase[0]).
        check(moves.first_set_index(10) == 1,
              "move 10 (walk) opens on set 1, not 13");
        {
            const gameplay::CharacterMove* dash = moves.find(20);
            check(dash && dash->sectionCount == 3 &&
                  dash->phase_set_index(0) == 13 &&
                  dash->phase_set_index(1) == 14 &&
                  dash->phase_set_index(2) == 15,
                  "move 20 (dash) phases are [13, 14, 15]");
        }
        check(moves.first_set_index(30) == 54,
              "move 30 (jump-forward) opens on set 54, not the dash");
        check(moves.first_set_index(40) == 2,
              "move 40 (jump startup) has phase tag 2; this does not map port AttackA");
        check(moves.first_set_index(300) == 31,
              "move 300 (weapon) opens on set 31: attacks are weapon sets");
        if (std::string(d) == "rena") {
            checkInt(124, moves.animation_set_count(),
                     "Rena 00 has 124 animation-set metadata rows");
            checkInt(0, moves.animation_set_phase_gate(13),
                     "set 13 +0x20 permits automatic phase advance");
            checkInt(1, moves.animation_set_phase_gate(14),
                     "set 14 +0x20 blocks automatic phase advance");
            checkInt(0, moves.animation_set_phase_gate(73),
                     "set 73 gate remains aligned after eventful rows");
            checkInt(-1, moves.animation_set_phase_gate(124),
                     "out-of-range set metadata is unresolved");
            const gameplay::CharacterMove* big = moves.find(350);
            check(big && big->sectionCount >= 1 && big->phases[0].entryCount == 19,
                  "move 350's 19-effect phase parses whole (no silent truncation)");
            // The damaging entry carries its in-phase frame (record v04): rena move
            // 301's weapon hit lands on frame 7 at radius 20. Timings differ per
            // character (keiichi 9, mion 10, satoko 17), which is why the hit
            // window must come from data, not a shared constant (issue #26 step 4).
            const gameplay::CharacterMove* swing = moves.find(301);
            bool hitAt7 = false;
            if (swing)
                for (int p = 0; p < swing->sectionCount; ++p)
                    for (int e = 0; e < swing->phases[p].entryCount; ++e) {
                        const auto& en = swing->phases[p].entries[e];
                        if (en.baseDamage > 0 && en.activeFrame == 7 && en.hitRadius == 20)
                            hitAt7 = true;
                    }
            check(hitAt7, "rena move 301's hit entry fires on frame 7 at radius 20");
        }
        // Verify the parser retains combat data on numeric move 301. This describes
        // the character-table entry only; it does not assign the move a projectile role.
        const gameplay::CharacterMove* move301 = moves.find(301);
        bool move301HasCombat = false;
        if (move301)
            for (int p = 0; p < move301->sectionCount; ++p)
                for (int e = 0; e < move301->phases[p].entryCount; ++e)
                    if (move301->phases[p].entries[e].has_combat()) move301HasCombat = true;
        check(move301HasCombat, "numeric move 301 parses combat data");
    }
    checkInt(4, parsed, "all four sampled characters parsed");
    check(withMoveChain >= 1,
          "at least one sampled character contains moves 300, 301, and 302");

    // A truncated file must be rejected, not read past.
    gameplay::CharacterMoves m;
    std::string err;
    std::vector<uint8_t> tiny(40, 0);
    check(!m.parse(tiny.data(), tiny.size(), err), "a truncated move table is rejected");
    check(!m.valid(), "and leaves the table unloaded");
    check(m.find(40) == nullptr, "with nothing findable");
}

void testClassSpecificAnimationBlend(const fs::path& install) {
    section("the recovered Rena 2 animation blend uses NN.dat timing");
    gameplay::CharacterMoves moves;
    if (!load_moves(install, "rena", "02.dat", moves)) {
        skip("Rena 2 animation blend (no install found)");
        return;
    }
    gameplay::WeaponDefinition weapon;
    if (moves.weapon_id() != gameplay::kWeaponIds[0][2] ||
        !load_weapon(install, moves.weapon_id(), weapon) || weapon.id != moves.weapon_id()) {
        skip("Rena 2 animation blend (matching item unavailable)");
        return;
    }
    checkInt(33, moves.weapon_id(), "Rena 2 table binds its matching item 33");
    checkInt(0, moves.character_index(), "the move table carries its loaded roster identity");
    // FUN_0041e180 indexes rows by move ID, clears an existing phase vector,
    // and then writes the later row into that same slot. Rena 02 repeats 311;
    // its second record at file offset 0x7116 replaces the earlier set-40 row.
    const gameplay::CharacterMove* repeated = moves.find(311);
    checkInt(1, repeated ? repeated->sectionCount : -1,
             "repeated move 311 resolves to one overwritten phase");
    checkInt(34, repeated ? repeated->first_set_index() : -1,
             "last move 311 row wins with phase tag 34");
    checkInt(4, repeated ? repeated->phases[0].entryCount : -1,
             "the winning move 311 row keeps its four entries");
    checkInt(10, moves.animation_set_transition_duration(1),
             "old set 1 seeds the callback countdown with 10");
    checkInt(20, moves.animation_set_transition_duration(31),
             "new set 31 supplies the 20-tick ramp denominator");
    checkInt(20, moves.animation_set_transition_duration(34),
             "new set 34 supplies its own ramp denominator");
    checkInt(10, moves.animation_set_transition_duration(39),
             "new set 39 supplies its own ramp denominator");

    auto startBlend = [&](Fighter& fighter, xm::Model& model, xm::Controller& ctrl) {
        bind_synthetic_rig(fighter, model, ctrl, glm::vec3(0, 0, 0));
        fighter.set_moves(&moves);
        fighter.set_weapon(&weapon);
        fighter.set_state(FighterState::Walk);
    };
    input::PlayerState attack;
    attack.down[input::Action::AttackA] = true;
    input::PlayerState idle;
    {
        xm::Model model;
        xm::Controller ctrl;
        Fighter fighter;
        startBlend(fighter, model, ctrl);
        checkInt(1, fighter.anim_set_index(), "walk supplies callback old set 1");
        tick(fighter, attack);
        checkInt(31, fighter.anim_set_index(), "Rena 2 neutral move targets set 31");
        checkInt(1, ctrl.trackAnimationSet(0), "old pose remains on track 0 during blend");
        checkInt(31, ctrl.trackAnimationSet(1), "new pose starts on track 1");
        check(std::abs(ctrl.trackWeight(0) - 0.5f) < 1e-6f,
              "the parsed 10/20 durations start the old set at half weight");
        check(std::abs(ctrl.trackWeight(1) - 0.5f) < 1e-6f,
              "the parsed 10/20 durations start the new set at half weight");

        attack.down[input::Action::AttackA] = false;
        tick(fighter, idle);
        check(std::abs(ctrl.trackWeight(0) - 0.45f) < 1e-6f,
              "the next source countdown step leaves 45 percent on the old set");
        check(std::abs(ctrl.trackWeight(1) - 0.55f) < 1e-6f,
              "the next source countdown step gives 55 percent to the new set");
        for (int i = 0; i < 9; ++i) tick(fighter, idle);
        checkInt(31, ctrl.trackAnimationSet(0), "the source countdown commits after 11 updates");
        checkInt(31, ctrl.trackAnimationSet(1), "both tracks settle on the requested set");
    }
    {
        xm::Model model;
        xm::Controller ctrl;
        Fighter interrupted;
        startBlend(interrupted, model, ctrl);
        attack.down[input::Action::AttackA] = true;
        tick(interrupted, attack);
        attack.down[input::Action::AttackA] = false;
        const int hitSet = moves.first_set_index(103);
        check(hitSet >= 0, "the interruption target exists in Rena 2's table");
        interrupted.set_state(FighterState::Hit);
        checkInt(hitSet, ctrl.trackAnimationSet(0),
                 "a callback-rejected interruption hard-binds track 0");
        checkInt(hitSet, ctrl.trackAnimationSet(1),
                 "a callback-rejected interruption hard-binds track 1");
    }
}

void testDirectionalDashes(const fs::path& install) {
    section("directional dash animation sets");
    gameplay::CharacterMoves moves;
    if (!load_moves(install, "rena", "00.dat", moves)) {
        skip("directional dash sets (no install found)");
        return;
    }
    gameplay::WeaponDefinition weapon;
    if (moves.weapon_id() != gameplay::kWeaponIds[0][0] ||
        !load_weapon(install, moves.weapon_id(), weapon) || weapon.id != moves.weapon_id()) {
        skip("directional dash sets (matching item unavailable)");
        return;
    }
    struct Case { int action; int move; int set; const char* name; bool known; };
    const Case cases[] = {
        {input::Action::Up, 20, 13, "forward", true},
        {input::Action::Down, 27, 16, "back", true},
        {input::Action::Left, -1, 0, "left", false},
        {input::Action::Right, -1, 0, "right", false},
    };
    for (const Case& c : cases) {
        xm::Model model;
        xm::Controller ctrl;
        Fighter f;
        bind_synthetic_rig(f, model, ctrl, glm::vec3(0, 0, 0));
        f.set_moves(&moves);
        f.set_weapon(&weapon);
        double_tap(f, c.action);
        checkInt(static_cast<int>(FighterState::Run), static_cast<int>(f.state()),
                 "double-tap dashes");
        char what[96];
        if (c.known) {
            std::snprintf(what, sizeof(what), "%s dash resolves move %d", c.name, c.move);
            checkInt(c.move, f.dash_move_id(), what);
            std::snprintf(what, sizeof(what), "%s dash opens on set %d", c.name, c.set);
            checkInt(c.set, f.anim_set_index(), what);
        } else {
            std::snprintf(what, sizeof(what), "%s selector remains unresolved", c.name);
            checkInt(c.move, f.dash_move_id(), what);
            checkInt(c.set, f.anim_set_index(), "unresolved side dash uses set 0");
            check(f.anim_fallback(), "unresolved side dash reports fallback");
        }
    }

    // Changing the direction during an active Run state changes the port's
    // inferred move candidate without changing its state label; the animation
    // must rebind instead of keeping the previous dash clip.
    {
        xm::Model model;
        xm::Controller ctrl;
        Fighter f;
        bind_synthetic_rig(f, model, ctrl, glm::vec3(0, 0, 0));
        f.set_moves(&moves);
        f.set_weapon(&weapon);
        double_tap(f, input::Action::Up);
        checkInt(13, f.anim_set_index(), "up dash begins on its inferred move-20 clip");
        double_tap(f, input::Action::Down);
        checkInt(static_cast<int>(FighterState::Run), static_cast<int>(f.state()),
                 "a second dash keeps the Run port state");
        checkInt(27, f.dash_move_id(), "down dash replaces the candidate with move 27");
        checkInt(16, f.anim_set_index(), "same-state dash rebinds to move 27's clip");
        check(!f.anim_fallback(), "the ground dash inference resolves through the table");
    }

    // Reusing a ground input mapping for airborne dashes is unverified, so leave
    // the aerial Run on the explicit default pose.
    {
        xm::Model model;
        xm::Controller ctrl;
        Fighter f;
        bind_synthetic_rig(f, model, ctrl, glm::vec3(0, 0, 0));
        f.set_moves(&moves);
        f.set_weapon(&weapon);
        input::PlayerState jump;
        jump.down[input::Action::Jump] = true;
        tick(f, jump);
        jump.down[input::Action::Jump] = false;
        tick(f, jump);
        double_tap(f, input::Action::Up);
        checkInt(static_cast<int>(FighterState::Run), static_cast<int>(f.state()),
                 "air double-tap still enters the port dash state");
        checkInt(-1, f.dash_move_id(), "air dash has no inferred ground move candidate");
        checkInt(0, f.anim_set_index(), "unmapped air dash uses set 0");
        check(f.anim_fallback(), "unmapped air dash reports its animation fallback");
    }
}

void testRosterVariation(const fs::path& install) {
    section("roster variation: shared locomotion, per-character attacks");
    // One table is ~2.3 MB of fixed-size phase storage: heap-allocate, since
    // three of them would overflow the stack.
    auto keiichi = std::make_unique<gameplay::CharacterMoves>();
    auto mion = std::make_unique<gameplay::CharacterMoves>();
    auto rena2 = std::make_unique<gameplay::CharacterMoves>();
    if (!load_moves(install, "keiichi", "00.dat", *keiichi) ||
        !load_moves(install, "mion", "00.dat", *mion) ||
        !load_moves(install, "rena", "02.dat", *rena2)) {
        skip("roster variation (no install found)");
        return;
    }
    gameplay::WeaponDefinition keiichiWeapon;
    gameplay::WeaponDefinition mionWeapon;
    gameplay::WeaponDefinition rena2Weapon;
    if (keiichi->weapon_id() != gameplay::kWeaponIds[2][0] ||
        mion->weapon_id() != gameplay::kWeaponIds[1][0] ||
        rena2->weapon_id() != gameplay::kWeaponIds[0][2] ||
        !load_weapon(install, keiichi->weapon_id(), keiichiWeapon) ||
        !load_weapon(install, mion->weapon_id(), mionWeapon) ||
        !load_weapon(install, rena2->weapon_id(), rena2Weapon)) {
        check(false, "roster tables join their character-specific slot items");
        return;
    }
    for (const gameplay::CharacterMoves* moves : {keiichi.get(), mion.get()}) {
        const gameplay::CharacterMove* dash = moves->find(20);
        check(dash && dash->sectionCount == 3 && dash->phase_set_index(0) == 13 &&
                  dash->phase_set_index(1) == 14 && dash->phase_set_index(2) == 15,
              "non-rena dash phases are [13, 14, 15]");
        checkInt(3, moves->first_set_index(41), "move 41's first phase tag is 3");
        checkInt(43, moves->first_set_index(43), "move 43's first phase tag is 43");
        checkInt(19, moves->first_set_index(24), "non-rena side move 24 opens on 19");
        checkInt(22, moves->first_set_index(23), "non-rena side move 23 opens on 22");
    }
    checkInt(39, keiichi->first_set_index(330),
             "keiichi's lunge opens on 39, not Rena 0's 51");
    checkInt(54, rena2->first_set_index(20),
             "rena/02's dash opens on 54: the file may surprise, ids win");
    // Live: combat tuning's candidate does not override the unresolved dash
    // animation selector with a character-family guess.
    {
        xm::Model model;
        xm::Controller ctrl;
        Fighter dasher;
        bind_synthetic_rig(dasher, model, ctrl, glm::vec3(0, 0, 0));
        dasher.set_moves(keiichi.get());
        dasher.set_weapon(&keiichiWeapon);
        check(dasher.weapon() == &keiichiWeapon &&
                  keiichiWeapon.id == gameplay::kWeaponIds[2][0],
              "the dash attack binds its matching Keiichi 0 weapon");
        double_tap(dasher, input::Action::Up);
        input::PlayerState in;
        in.down[input::Action::AttackA] = true;
        tick(dasher, in);
        in.down[input::Action::AttackA] = false;
        checkInt(330, dasher.attack_move_id(), "keiichi dash press resolves 330");
        checkInt(39, dasher.anim_set_index(),
                 "keiichi's lunge plays its own table row (set 39)");
        check(!dasher.anim_fallback(), "the keiichi lunge row is not a fallback");
    }
}

void testJumpAnimationChain(const fs::path& install) {
    section("the recovered jump chain plays its own clips");
    gameplay::CharacterMoves moves;
    if (!load_moves(install, "rena", "00.dat", moves)) {
        skip("jump chain (no install found)");
        return;
    }
    gameplay::WeaponDefinition weapon;
    if (moves.weapon_id() != gameplay::kWeaponIds[0][0] ||
        !load_weapon(install, moves.weapon_id(), weapon) || weapon.id != moves.weapon_id()) {
        skip("jump chain (matching item unavailable)");
        return;
    }
    checkInt(2, moves.first_set_index(40), "move 40 opens on the startup set 2");
    checkInt(3, moves.first_set_index(41), "move 41 opens on the takeoff set 3");
    const gameplay::CharacterMove* fallRow = moves.find(42);
    check(fallRow && fallRow->sectionCount == 2 && fallRow->phase_set_index(0) == 5 &&
              fallRow->phase_set_index(1) == 43,
          "move 42 is the two-section down-momentum [5] -> falling [43] row");

    // 9,600 keys at 4,800/s is a rounded 2-tick period, so a section completes on
    // the third elapsed tick and the whole chain fits in ~20 ticks.
    xm::Model model;
    xm::Controller ctrl;
    Fighter f;
    bind_synthetic_rig(f, model, ctrl, glm::vec3(0, 0, 0), 153.6f);
    f.set_moves(&moves);
    f.set_weapon(&weapon);
    check(f.weapon() == &weapon && weapon.id == gameplay::kWeaponIds[0][0],
          "the jump chain runs on the matching Rena 0 weapon combo");
    input::PlayerState jump;
    jump.down[input::Action::Jump] = true;
    tick(f, jump);
    check(f.airborne(), "the leap leaves the ground on the press tick");
    checkInt(2, f.anim_set_index(), "the launch tick plays move 40's startup set 2");
    check(!f.anim_fallback(), "the startup row is a bound row, not a fallback");
    jump.down[input::Action::Jump] = false;
    tick(f, jump);
    checkInt(3, f.anim_set_index(), "the rise rebinds to move 41's set 3");
    check(!f.anim_fallback(), "the rise row is a bound row");
    tick(f, jump);
    checkInt(3, f.anim_set_index(), "period equality does not advance the section");
    tick(f, jump);
    checkInt(4, f.anim_set_index(),
             "move 41 advances to its up-momentum section 4");
    while (f.airborne() && f.anim_set_index() != 5 && f.state() == FighterState::Jump)
        tick(f, jump);
    checkInt(5, f.anim_set_index(),
             "vy under the apex threshold switches to move 42's down set 5");
    check(!f.anim_fallback(), "the falling row is a bound row");
    int ticksToFall = 0;
    while (f.airborne() && f.anim_set_index() != 43 && ticksToFall < 10) {
        tick(f, jump);
        ++ticksToFall;
    }
    checkInt(43, f.anim_set_index(), "move 42 completes into its final falling set 43");
    check(ticksToFall < 10, "the final section completes inside the fall");
    for (int i = 0; i < 60; ++i) tick(f, jump);
    checkInt(static_cast<int>(FighterState::Idle), static_cast<int>(f.state()),
             "landing returns to Idle");
    checkInt(0, f.anim_set_index(), "and the idle set comes back");
    check(!f.anim_fallback(), "the landing pose is not a fallback");

    // Interrupting the chain mid-air must not leave the old jump clip blended in:
    // a reaction row is a rejected class change in this combo, so both tracks
    // hard-bind it (the same rule the Rena 2 blend test pins).
    {
        xm::Model imodel;
        xm::Controller ictrl;
        Fighter hit;
        bind_synthetic_rig(hit, imodel, ictrl, glm::vec3(0, 0, 0), 153.6f);
        hit.set_moves(&moves);
        hit.set_weapon(&weapon);
        input::PlayerState up;
        up.down[input::Action::Jump] = true;
        tick(hit, up);
        up.down[input::Action::Jump] = false;
        tick(hit, up);
        checkInt(3, hit.anim_set_index(), "the interrupted fighter is mid-rise");
        hit.set_state(FighterState::Hit);
        const int hitSet = moves.first_set_index(103);
        check(hitSet >= 0, "Rena 0's hit row exists");
        checkInt(hitSet, ictrl.trackAnimationSet(0),
                 "an interruption hard-binds track 0 off the jump clip");
        checkInt(hitSet, ictrl.trackAnimationSet(1),
                 "an interruption hard-binds track 1 off the jump clip");
        check(!hit.anim_fallback(), "the reaction row is a bound row");
    }
}

void testGuardHoldsPlayingClip(const fs::path& install) {
    section("guard holds the playing clip (no selector, not a fallback)");
    test::Combo combo;
    std::string error;
    if (!combo.load(0,0,error)) { skip("Rena+0 guard fixture unavailable"); return; }
    xm::Model model;
    xm::Controller ctrl;
    Fighter f;
    bind_synthetic_rig(f, model, ctrl, glm::vec3(0, 0, 0));
    combo.bind(f);
    input::PlayerState walk;
    walk.down[input::Action::Right] = true;
    tick_held(f, walk);
    tick_held(f, walk);
    checkInt(static_cast<int>(FighterState::Walk), static_cast<int>(f.state()),
             "movement enters Walk");
    checkInt(1, f.anim_set_index(), "walk plays its own row's set 1");
    walk.down[input::Action::Guard] = true;
    tick_held(f, walk);
    checkInt(static_cast<int>(FighterState::Guard), static_cast<int>(f.state()),
             "holding the guard key enters Guard");
    checkInt(1, f.anim_set_index(), "guard keeps the walk clip it was already playing");
    check(!f.anim_fallback(), "guard is not a set-0 fallback");
    check(f.anim_no_selector(), "guard reports the no-selector hold");
    for (int i = 0; i < 5; ++i) tick_held(f, walk);
    checkInt(1, f.anim_set_index(), "the held clip stays bound while guarding");
    walk.down[input::Action::Guard] = false;
    tick_held(f, walk);
    checkInt(static_cast<int>(FighterState::Walk), static_cast<int>(f.state()),
             "releasing the guard key while moving returns to Walk");
    checkInt(1, f.anim_set_index(), "walk's own row binds again");
    check(!f.anim_no_selector(), "Walk has a selector again");
    walk.down[input::Action::Right] = false;
    tick_held(f, walk);
    tick_held(f, walk);
    checkInt(static_cast<int>(FighterState::Idle), static_cast<int>(f.state()),
             "releasing the direction returns to Idle");
    checkInt(0, f.anim_set_index(), "and the idle row binds again");
    // A guard from a standing start holds the idle clip, which is set 0 too: the
    // status, not the number, is what says whether it was a miss.
    f.set_state(FighterState::Idle);
    input::PlayerState stand;
    tick_held(f, stand);
    stand.down[input::Action::Guard] = true;
    tick_held(f, stand);
    checkInt(0, f.anim_set_index(), "a standing guard holds the idle set 0");
    check(!f.anim_fallback(), "a standing guard is still not a fallback");
    check(f.anim_no_selector(), "a standing guard is a no-selector hold");
    // An unmapped state keeps the visible fallback: this is the distinction.
    f.set_state(FighterState::TagOut);
    check(f.anim_fallback(), "an unresolved state still reports its fallback");
    check(!f.anim_no_selector(), "an unresolved state is not a no-selector hold");
}

void testRosterAnimationSweep(const fs::path& install) {
    section("roster sweep: idle/walk/jump/guard/attack/hit/KO per combo");
    std::error_code ec;
    if (install.empty() || !fs::is_directory(install / "data" / "item", ec)) {
        skip("roster animation sweep (no install found)");
        return;
    }
    struct Row { int set; bool fallback; bool hold; };
    int combos = 0, combosWithFallback = 0;
    int guardHolds = 0;
    for (int c = 0; c < gameplay::kCharacterCount; ++c) {
        for (int nn = 0; nn < gameplay::weaponCountForCharacter(c); ++nn) {
            char nnname[16];
            std::snprintf(nnname, sizeof(nnname), "%02d.dat", nn);
            auto moves = std::make_unique<gameplay::CharacterMoves>();
            if (!load_moves(install, gameplay::kCharacterDirs[c], nnname, *moves)) continue;
            gameplay::WeaponDefinition weapon;
            if (!load_weapon(install, moves->weapon_id(), weapon) ||
                weapon.id != moves->weapon_id()) {
                check(false, "every swept combo's table joins its own weapon item");
                continue;
            }
            ++combos;
            xm::Model model;
            xm::Controller ctrl;
            Fighter f;
            bind_synthetic_rig(f, model, ctrl, glm::vec3(0, 0, 0));
            f.set_moves(moves.get());
            f.set_weapon(&weapon);
            auto sample = [&f]() {
                return Row{f.anim_set_index(), f.anim_fallback(), f.anim_no_selector()};
            };
            const Row idle = sample();

            input::PlayerState walk;
            walk.down[input::Action::Right] = true;
            tick_held(f, walk);
            tick_held(f, walk);
            const Row walkSet = sample();

            walk.down[input::Action::Guard] = true;
            tick_held(f, walk);
            const Row guardSet = sample();
            if (guardSet.hold && !guardSet.fallback) ++guardHolds;

            input::PlayerState free;
            for (int i = 0; i < 4; ++i) tick(f, free);
            input::PlayerState jump;
            jump.down[input::Action::Jump] = true;
            tick(f, jump);
            const Row launch = sample();
            jump.down[input::Action::Jump] = false;
            tick(f, jump);
            const Row rise = sample();
            Row fall{0, true, false};
            const int fallSet = moves->first_set_index(42);
            for (int i = 0; i < 60 && f.state() == FighterState::Jump; ++i) {
                tick(f, jump);
                const Row r = sample();
                if (r.set == fallSet && !r.fallback) fall = r;
            }
            for (int i = 0; i < 90 && f.airborne(); ++i) tick(f, free);

            input::PlayerState swing;
            swing.down[input::Action::AttackA] = true;
            tick(f, swing);
            swing.down[input::Action::AttackA] = false;
            const Row attack = sample();

            Row hit{0, true, false}, down{0, true, false}, ko{0, true, false};
            for (FighterState st : {FighterState::Hit, FighterState::Knockdown,
                                    FighterState::KO}) {
                f.set_state(st);
                const Row r = sample();
                if (st == FighterState::Hit) hit = r;
                if (st == FighterState::Knockdown) down = r;
                if (st == FighterState::KO) ko = r;
            }
            f.set_state(FighterState::ShootA);
            const Row shoot = sample();
            f.set_state(FighterState::TagOut);
            const Row tag = sample();

            const std::string label = gameplay::comboSlotLabel(c, nn);
            std::printf("  %-20s idle=%d%s walk=%d%s jump=%d/%d/%d%s guard=%d%s "
                        "attack=%d%s hit=%d%s down=%d%s ko=%d%s shootA=%d%s tagOut=%d%s\n",
                        label.c_str(),
                        idle.set, idle.fallback ? "!" : "",
                        walkSet.set, walkSet.fallback ? "!" : "",
                        launch.set, rise.set, fall.set,
                        (launch.fallback || rise.fallback || fall.fallback) ? "!" : "",
                        guardSet.set,
                        guardSet.hold ? "(hold)" : (guardSet.fallback ? "!" : ""),
                        attack.set, attack.fallback ? "!" : "",
                        hit.set, hit.fallback ? "!" : "",
                        down.set, down.fallback ? "!" : "",
                        ko.set, ko.fallback ? "!" : "",
                        shoot.set, shoot.fallback ? "!" : "",
                        tag.set, tag.fallback ? "!" : "");
            // `!` marks a fallback. Every recovered row above must be free of one.
            const bool recovered =
                !idle.fallback && !walkSet.fallback && !launch.fallback && !rise.fallback &&
                !fall.fallback && guardSet.hold && !guardSet.fallback && !attack.fallback &&
                !hit.fallback && !down.fallback && !ko.fallback;
            if (shoot.fallback || tag.fallback) ++combosWithFallback;
            char what[160];
            std::snprintf(what, sizeof(what),
                          "%s resolves its idle/walk/jump/guard/attack/hit/down/KO rows",
                          label.c_str());
            check(recovered, what);
        }
    }
    std::printf("  combos swept: %d, combos whose shoot/tagOut rows fall back: %d, "
                "guard holds: %d\n", combos, combosWithFallback, guardHolds);
    checkInt(46, combos, "the sweep covers all legal character/item-slot combos");
    checkInt(combos, guardHolds,
             "every combo's Guard holds a clip instead of falling back");
}
} // namespace
int main(int argc, char** argv) {
    const fs::path install = findInstall(argc,argv);
    if (install.empty()) { std::puts("MELEE_RULES: SKIP (no game install)"); return 0; }
    fnd::assets::assetSource().openInstall(install.string());
    testPosedCombat(); testPosedMatch(); testRepeatContactSuppression(); testPhaseClock();
    testCharacterMoveTable(install);
    testClassSpecificAnimationBlend(install);
    testDirectionalDashes(install);
    testRosterVariation(install);
    testJumpAnimationChain(install);
    testGuardHoldsPlayingClip(install);
    testRosterAnimationSweep(install);
    std::printf("MELEE_RULES: %s (%d checks, %d failed, %d skipped)\n",failures ? "FAIL" : "ok",checks,failures,skipped);
    return failures ? 1 : 0;
}
