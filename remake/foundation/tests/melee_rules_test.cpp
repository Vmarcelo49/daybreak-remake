// NN.dat collision/clock integration. Real combat uses an equipped item and its
// bundle-winning rig; synthetic rigs below isolate selector/blend/period contracts.
#include "combo_fixture.h"
#include "gameplay/fixed_step.h"
#include "gameplay/melee_admission.h"
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
    f.update(&copy, nullptr, gameplay::FixedStep::seconds);
}

void tick_held(Fighter& f, input::PlayerState& in) {
    input::compute_edges(in);
    f.update(&in, nullptr, gameplay::FixedStep::seconds);
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
        victim.update(nullptr,nullptr,gameplay::FixedStep::seconds); ++stunTicks;
    }
    check(stunTicks > 0 && stunTicks < 60 && victim.state() != FighterState::Hit,
          "the reaction eventually completes rather than sticking in Hit");
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

    // FUN_00428510 case 0x71 seeds vertical velocity from combat[17] and
    // horizontal speed from combat[18], each scaled by 0.01 per update.
    combo.init(victim);
    check(victim.state() != FighterState::Knockdown, "victim starts grounded");
    // Rena+0 move 302's contact record (the XXX finisher): row 113, combat[17] = 500 (lift) and
    // combat[18] = 2000 (slide), scaled by the recovered 0.01.
    gameplay::HitReaction reaction;
    reaction.row = 113;
    reaction.rowHigh = 113;
    reaction.counter = 5.0f;
    reaction.rise = 20.0f;
    reaction.meterA = 120;
    reaction.meterB = 20;
    victim.take_damage(0, &attacker, 6, reaction.row, false, reaction);
    check(victim.airborne(), "combat[17]*0.01 lifts a grounded victim (+0x40)");
    const float risenY = victim.position().y;
    for (int i = 0; i < 6; ++i) victim.update(nullptr, nullptr, gameplay::FixedStep::seconds);
    check(victim.position().y > risenY, "and the victim keeps rising under its own integration");

    // The launch has to land somewhere: on touchdown the victim enters the knockdown chain
    // (lying row 118, then the get-up row 120) instead of standing straight back up.
    const glm::vec3 launchStart = victim.position();
    check(victim.airborne(), "the XXX finisher lifts her off the ground");
    float prevSpeed = 0.f;
    float firstSpeed = 0.f;
    for (int i = 0; i < 4; ++i) {
        const glm::vec3 beforeStep = victim.position();
        victim.update(nullptr, nullptr, gameplay::FixedStep::seconds);
        const glm::vec3 delta = victim.position() - beforeStep;
        const float speed = glm::length(glm::vec2(delta.x, delta.z));
        if (i == 0) firstSpeed = speed;
        prevSpeed = speed;
    }
    check(firstSpeed - prevSpeed > 0.5f,
          "row 113's horizontal speed approaches -4 by 0.25 per tick");
    int ticks = 0;
    float peak = victim.position().y;
    while (victim.state() != FighterState::Knockdown && ticks < 400) {
        victim.update(nullptr, nullptr, gameplay::FixedStep::seconds);
        peak = std::max(peak, victim.position().y);
        ++ticks;
    }
    check(peak >= 35.f, "row 113 uses 0.3 per-tick gravity rather than 0.5");
    check(victim.state() == FighterState::Knockdown, "a launched victim lands into Knockdown");
    // combat[18] = 2000 gives a 20/tick slide along her facing, so the throw is unmistakable.
    const glm::vec3 thrown = victim.position() - launchStart;
    check(glm::length(glm::vec2(thrown.x, thrown.z)) > 40.f,
          "and the throw carries her across the stage before she lands");
    const int lyingRow = victim.down_row_for_test();
    checkInt(118, lyingRow, "front row 113 lands into row 118");
    const glm::vec3 landedAt = victim.position();
    int down = 0;
    bool boundGetup = false;
    while (victim.state() == FighterState::Knockdown && down < 400) {
        victim.update(nullptr, nullptr, gameplay::FixedStep::seconds);
        if (victim.down_row_for_test() == 120) {
            const auto* getup = combo.moves.find(120);
            boundGetup |= getup && victim.anim_set_index() == getup->phase_set_index(0);
        }
        ++down;
    }
    check(boundGetup, "lying row binds the get-up row 120's own animation");
    check(victim.state() == FighterState::Idle, "and gets up into Idle after the chain");
    const glm::vec3 duringDown = victim.position() - landedAt;
    check(glm::length(glm::vec2(duringDown.x, duringDown.z)) < 900.f,
          "knockdown slide decelerates at 0.25 per tick");
    const glm::vec3 afterDown = victim.position();
    for (int i = 0; i < 10; ++i)
        victim.update(nullptr, nullptr, gameplay::FixedStep::seconds);
    check(glm::length(victim.position() - afterDown) < 1.f,
          "the reaction leaves no residual movement in Idle");
    combo.init(attacker); swing_to_active(attacker);
    for (int i = 0; i < 240 && attacker.state() == FighterState::AttackA; ++i) tick_held(attacker,in);
    check(attacker.state() == FighterState::Idle,"actual final-set period completes the attack without a recovery timer");
}
// FUN_00637950 only refreshes the stagger window when combat[7] is positive.
void test_zero_meter_hit_does_not_refresh_stagger() {
    section("zero-meter hits preserve stagger expiry");
    test::Combo combo; std::string error;
    if (!combo.load(0, 0, error)) { skip("Rena+0 rig/item/moves unavailable"); return; }
    Fighter attacker, victim;
    combo.init(attacker); combo.init(victim);
    victim.reset(glm::vec3(0.f), 0.f);
    victim.set_state(FighterState::Idle);
    gameplay::HitReaction weak; weak.meterA = 60;
    victim.take_damage(0, &attacker, 0, 100, false, weak);
    for (int i = 0; i < 119; ++i)
        victim.update(nullptr, nullptr, gameplay::FixedStep::seconds);
    gameplay::HitReaction zero;
    victim.take_damage(0, &attacker, 0, 100, false, zero);
    victim.update(nullptr, nullptr, gameplay::FixedStep::seconds);
    victim.take_damage(0, &attacker, 0, 100, false, weak);
    check(victim.state() != FighterState::Hit,
          "a zero-meter contact does not extend the 120-update stagger window");
}

// FUN_00445ee0 admits 341 only from row 340, and FUN_0043ffc0 case 0x155 runs its four
// phases (sets 89/90/43/91). The chain branch that admits 341 installs no legacy swing
// timer, so the row must run to its gated landing phase instead of being cut at the
// fallback's 36-update total.
// `melee_in_active()` reads the current record's radius, not its active frame, and
// `record_at` starts from entry 0 unconditionally — so a phase whose FIRST record is a
// live hitbox must open at frame 0, or the swing would report a hit window before the
// data opens it. The shipped rows satisfy this; the sweep pins the premise for every
// row the table carries.
void test_first_live_record_opens_at_frame_zero() {
    section("Rena+0: every phase's first live record opens at frame 0");
    test::Combo combo; std::string error;
    if (!combo.load(0,0,error)) { skip("Rena+0 rig/item/moves unavailable"); return; }
    int rows = 0, liveFirst = 0, lateFirst = 0;
    for (int id = 0; id < gameplay::CharacterMoves::kMaxMoves; ++id) {
        const gameplay::CharacterMove* move = combo.moves.find(id);
        if (!move) continue;
        ++rows;
        for (int phase = 0; phase < move->sectionCount; ++phase) {
            const gameplay::MovePhase& records = move->phases[phase];
            if (records.entryCount == 0) continue;
            const gameplay::MoveEntry& first = records.entries[0];
            if (!first.has_combat()) continue;
            ++liveFirst;
            if (first.activeFrame != 0) ++lateFirst;
        }
    }
    check(rows > 0, "the Rena+0 move table parses");
    check(liveFirst > 0, "its phases carry live hitbox records");
    checkInt(0, lateFirst, "no phase opens with a live record after frame 0");
}

// FUN_00428510 cases 0x68/0x69/0xcc/0xcd: phase 0 is a gated eight-frame clip and the
// handler keeps it until its own frame counter passes 0x3c, then seeds the motion on the
// phase-1 transition. No shipped Rena+0 contact names these rows, so the row is injected
// through take_damage; the phases, gates and clips are the real 00.dat/00.X ones.
// The live contact gate is the CURRENT phase-local record (record_at), not a window
// derived from the move's first entry. Each reachable melee row is driven with its
// fixture input script; the first connecting tick must be exactly the first tick whose
// record carries a hitbox, and the victim must play that record's reaction row.
void test_move_contact_windows() {
    section("Rena+0: contact opens exactly on the record's frame");
    test::Combo combo; std::string error;
    if (!combo.load(0,0,error)) { skip("Rena+0 rig/item/moves unavailable"); return; }
    struct Script {
        int row;
        std::vector<std::pair<int, std::vector<input::Action>>> frames;
    };
    const auto keys = [](std::initializer_list<input::Action> list) {
        return std::vector<input::Action>(list);
    };
    const Script scripts[] = {
        {300, {{0, keys({input::Action::AttackA})}}},
        {310, {{0, keys({input::Action::Down, input::Action::AttackA})}}},
        {311, {{0, keys({input::Action::Right, input::Action::AttackA})}}},
        {330, {{0, keys({input::Action::Up})}, {1, {}}, {2, keys({input::Action::Up})},
               {3, keys({input::Action::AttackA})}}},
        {331, {{0, keys({input::Action::Left})}, {1, {}}, {2, keys({input::Action::Left})},
               {3, keys({input::Action::AttackA})}}},
        {320, {{0, keys({input::Action::Jump})}, {1, {}},
               {13, keys({input::Action::AttackA})}, {14, {}}}},
        {332, {{0, keys({input::Action::Jump})}, {1, {}},
               {12, keys({input::Action::Left})}, {13, {}},
               {14, keys({input::Action::Left})}, {15, keys({input::Action::AttackA})},
               {16, {}}}},
    };
    for (const Script& script : scripts) {
        Fighter attacker, opponent, victim;
        combo.init(attacker);
        combo.init(opponent, glm::vec3(0, 0, 2000));
        combo.init(victim, glm::vec3(0, 0, 2000));
        input::PlayerState in;
        int entered = -1, firstActive = -1, firstHit = -1;
        const gameplay::MoveEntry* hitRecord = nullptr;
        for (int tick = 0; tick < 400 && firstHit < 0; ++tick) {
            for (bool& down : in.down) down = false;
            for (const auto& frame : script.frames)
                if (frame.first == tick)
                    for (input::Action action : frame.second) in.down[action] = true;
            input::compute_edges(in);
            attacker.update(&in, &opponent, gameplay::FixedStep::seconds);
            if (entered < 0 && attacker.attack_move_id() == script.row &&
                attacker.state() == FighterState::AttackA)
                entered = tick;
            if (entered < 0 || attacker.state() != FighterState::AttackA) continue;
            if (attacker.melee_in_active()) {
                if (firstActive < 0) firstActive = tick;
                hitRecord = attacker.current_move_record();
                test::Combo::placeAtAttack(attacker, victim);
                // placeAtAttack keeps the victim's yaw, so she would be struck from
                // behind; face her at the attacker to exercise the front reaction row.
                const glm::vec3 toward = attacker.position() - victim.position();
                victim.reset(victim.position(), std::atan2(toward.x, toward.z));
                victim.set_state(FighterState::Idle);
            }
            if (attacker.try_melee_hit(victim)) firstHit = tick;
        }
        checkInt(script.row, attacker.attack_move_id(), "the script admits the expected row");
        check(entered >= 0, "the row is entered from real input");
        check(firstActive >= 0 && firstHit == firstActive,
              "the first contact lands on the first record-active tick");
        check(hitRecord && hitRecord->has_combat() && hitRecord->hitRadius != 0,
              "the connecting record carries the live hitbox");
        check(victim.hp() < 100 && victim.state() == FighterState::Hit,
              "the contact damages and staggers the placed victim");
        checkInt(hitRecord ? hitRecord->reactionMove : -1,
                 victim.reaction_move_for_test(),
                 "the victim plays the connecting record's reaction row");
    }
}

// FUN_00445ee0's chain: a connected 300 admits 301 and a connected 301 admits 302.
// Each row must connect on its own phase-local record, not on the first swing's window.
void test_melee_chain_contacts() {
    section("Rena+0: the 300 -> 301 -> 302 chain connects on its own records");
    test::Combo combo; std::string error;
    if (!combo.load(0,0,error)) { skip("Rena+0 rig/item/moves unavailable"); return; }
    Fighter attacker, opponent, victim;
    combo.init(attacker);
    combo.init(opponent, glm::vec3(0, 0, 2000));
    combo.init(victim, glm::vec3(0, 0, 2000));
    input::PlayerState in;
    const auto step = [&]() {
        input::compute_edges(in);
        attacker.update(&in, &opponent, gameplay::FixedStep::seconds);
    };
    const auto tap = [&]() {
        for (bool& down : in.down) down = false;
        in.down[input::Action::AttackA] = true;
        step();
        for (bool& down : in.down) down = false;
        step();
    };
    const auto place = [&]() {
        test::Combo::placeAtAttack(attacker, victim);
        const glm::vec3 toward = attacker.position() - victim.position();
        victim.reset(victim.position(), std::atan2(toward.x, toward.z));
        victim.set_state(FighterState::Idle);
    };
    // Connect the current swing; returns the hit tick or -1.
    const auto connect = [&](const gameplay::MoveEntry** record) {
        for (int i = 0; i < 240 && attacker.state() == FighterState::AttackA; ++i) {
            step();
            if (!attacker.melee_in_active()) continue;
            *record = attacker.current_move_record();
            place();
            if (attacker.try_melee_hit(victim)) return i;
        }
        return -1;
    };

    tap();
    checkInt(300, attacker.attack_move_id(), "the first press enters row 300");
    const gameplay::MoveEntry* first = nullptr;
    check(connect(&first) >= 0, "row 300 connects on its own record");
    checkInt(100, victim.reaction_move_for_test(), "the 300 contact plays reaction row 100");

    // The chain window is the current record's 0x100 flag, so the press has to land
    // on a tick that carries it; mash like a player until the admission opens.
    bool chained = false;
    for (int i = 0; i < 90 && !chained; ++i) {
        tap();
        chained = attacker.attack_move_id() == 301;
    }
    check(chained, "a connected 300 chains into row 301");
    const gameplay::MoveEntry* second = nullptr;
    check(connect(&second) >= 0, "row 301 connects on its own record");
    check(second && second != first, "row 301 uses its own phase-local record");
    checkInt(101, victim.reaction_move_for_test(), "the 301 contact plays reaction row 101");

    chained = false;
    for (int i = 0; i < 90 && !chained; ++i) {
        tap();
        chained = attacker.attack_move_id() == 302;
    }
    check(chained, "a connected 301 chains into row 302");
    const gameplay::MoveEntry* third = nullptr;
    check(connect(&third) >= 0, "row 302 connects on its own record");
    checkInt(113, victim.reaction_move_for_test(),
             "the 302 contact plays the launcher reaction row 113");
    check(victim.airborne(), "row 302's contact lifts its victim");
}

// Rows 340 and 341 are reached only through the landing follow-up chain; each must
// connect on its own phase-local record (340 -> reaction 101, 341 -> launcher 113).
void test_landing_followup_contacts() {
    section("Rena+0: rows 340 and 341 connect on the landing chain");
    test::Combo combo; std::string error;
    if (!combo.load(0,0,error)) { skip("Rena+0 rig/item/moves unavailable"); return; }
    Fighter attacker, opponent, victim;
    combo.init(attacker);
    combo.init(opponent, glm::vec3(0, 0, 2000));
    combo.init(victim, glm::vec3(0, 0, 2000));
    input::PlayerState in;
    const auto step = [&]() {
        input::compute_edges(in);
        attacker.update(&in, &opponent, gameplay::FixedStep::seconds);
    };
    const auto tap = [&]() {
        for (bool& down : in.down) down = false;
        in.down[input::Action::AttackA] = true;
        step();
        for (bool& down : in.down) down = false;
        step();
    };
    const auto place = [&]() {
        test::Combo::placeAtAttack(attacker, victim);
        const glm::vec3 toward = attacker.position() - victim.position();
        victim.reset(victim.position(), std::atan2(toward.x, toward.z));
        victim.set_state(FighterState::Idle);
    };
    const auto connect = [&](const gameplay::MoveEntry** record) {
        for (int i = 0; i < 240 && attacker.state() == FighterState::AttackA; ++i) {
            step();
            if (!attacker.melee_in_active()) continue;
            *record = attacker.current_move_record();
            place();
            if (attacker.try_melee_hit(victim)) return i;
        }
        return -1;
    };
    // Jump, then the airborne press admits 320 and the landing exit row 329.
    for (bool& down : in.down) down = false;
    in.down[input::Action::Jump] = true;
    step();
    for (bool& down : in.down) down = false;
    for (int i = 0; i < 40 && attacker.attack_move_id() != 320; ++i) {
        if (attacker.airborne() && attacker.state() != FighterState::AttackA) {
            in.down[input::Action::AttackA] = true;
            step();
            for (bool& down : in.down) down = false;
        }
        step();
    }
    checkInt(320, attacker.attack_move_id(), "the air press starts the landing chain");
    for (int i = 0; i < 240 && attacker.attack_move_id() != 329; ++i) step();
    checkInt(329, attacker.attack_move_id(), "row 320 lands into the 329 exit");
    for (int i = 0; i < 240 && attacker.phase_elapsed() < 5; ++i) step();
    tap();
    checkInt(340, attacker.attack_move_id(), "329 admits the landing row 340");
    const gameplay::MoveEntry* landing = nullptr;
    check(connect(&landing) >= 0, "row 340 connects on its own record");
    checkInt(101, victim.reaction_move_for_test(), "the 340 contact plays reaction row 101");

    bool chained = false;
    for (int i = 0; i < 120 && !chained; ++i) {
        tap();
        chained = attacker.attack_move_id() == 341;
    }
    check(chained, "a connected 340 chains into row 341");
    const gameplay::MoveEntry* followup = nullptr;
    check(connect(&followup) >= 0, "row 341 connects on its own record");
    checkInt(113, victim.reaction_move_for_test(),
             "the 341 contact plays the launcher reaction row 113");
}

// The Hyper EX (row 350) is the one melee row whose data carries eight one-tick hand
// records. V3-43 removed the port's contact cut for weapon 0 and added the per-tick
// ContactReset, so every shipped window must open and connect. Q22's "deals no
// damage" reading is superseded by those rule lines; this pins the live result.
void test_hyper_ex_contact() {
    section("Rena+0: the Hyper EX connects on every hand record");
    test::Combo combo; std::string error;
    if (!combo.load(0,0,error)) { skip("Rena+0 rig/item/moves unavailable"); return; }
    Fighter attacker, opponent, victim;
    combo.init(attacker);
    combo.init(opponent, glm::vec3(0, 0, 4000));
    combo.init(victim, glm::vec3(0, 0, 4000));
    input::PlayerState in;
    const auto step = [&]() {
        input::compute_edges(in);
        attacker.update(&in, &opponent, gameplay::FixedStep::seconds);
    };
    const auto tap = [&](input::Action action) {
        for (bool& down : in.down) down = false;
        in.down[action] = true;
        step();
        for (bool& down : in.down) down = false;
        step();
    };
    const auto start_ex = [&]() {
        attacker.set_hypermode(gameplay::Hypermode::Oyashiro);
        attacker.set_hyper_gauge(1.0f);
        tap(input::Action::Special);
        tap(input::Action::Special);
        return attacker.attack_move_id() == 350;
    };

    int expectedWindows = 0;
    if (const gameplay::CharacterMove* ex = combo.moves.find(350)) {
        for (int phase = 0; phase < ex->sectionCount; ++phase)
            for (int entry = 0; entry < ex->phases[phase].entryCount; ++entry)
                if (ex->phases[phase].entries[entry].has_combat()) ++expectedWindows;
    }
    check(expectedWindows > 0, "row 350 ships hand contact records");

    check(start_ex(), "the second Special press fires the EX row 350");
    // The body rewinds part of its clock, so a window can span several updated ticks;
    // what matters is that every distinct shipped record becomes current.
    std::vector<std::pair<int, int>> seen;
    for (int i = 0; i < 400 && attacker.state() == FighterState::AttackA; ++i) {
        step();
        if (!attacker.melee_in_active()) continue;
        const gameplay::MoveEntry* current = attacker.current_move_record();
        const int phase = attacker.move_phase();
        const gameplay::CharacterMove* ex = combo.moves.find(350);
        if (!ex || phase < 0 || phase >= ex->sectionCount) continue;
        for (int entry = 0; entry < ex->phases[phase].entryCount; ++entry) {
            if (&ex->phases[phase].entries[entry] != current) continue;
            const std::pair<int, int> key{phase, entry};
            bool known = false;
            for (const auto& prior : seen) known = known || prior == key;
            if (!known) seen.push_back(key);
        }
    }
    checkInt(expectedWindows, static_cast<int>(seen.size()),
             "every shipped hand record becomes the live volume");

    combo.init(attacker);
    check(start_ex(), "the EX can be fired again from a fresh activation");
    const gameplay::MoveEntry* record = nullptr;
    bool hit = false;
    for (int i = 0; i < 400 && attacker.state() == FighterState::AttackA && !hit; ++i) {
        step();
        if (!attacker.melee_in_active()) continue;
        record = attacker.current_move_record();
        test::Combo::placeAtAttack(attacker, victim);
        const glm::vec3 toward = attacker.position() - victim.position();
        victim.reset(victim.position(), std::atan2(toward.x, toward.z));
        victim.set_state(FighterState::Idle);
        hit = attacker.try_melee_hit(victim);
    }
    check(hit, "a placed victim is struck during a hand window");
    checkInt(record ? record->reactionMove : -1, victim.reaction_move_for_test(),
             "the EX contact plays its own reaction row");
    checkInt(130, victim.reaction_move_for_test(), "row 350's record selects reaction 130");
}

// Row 370 is the airborne second charge: the program's shot matrix maps the red
// tier airborne to 370, whose phase-2 tick-2 launches the row-11/12 pair.
void test_air_full_charge_370() {
    section("Rena+0: the airborne full charge binds row 370 and fires rows 11/12");
    test::Combo combo; std::string error;
    if (!combo.load(0,0,error)) { skip("Rena+0 rig/item/moves unavailable"); return; }
    Fighter fighter, target;
    combo.init(fighter);
    combo.init(target, glm::vec3(0, 0, 2000));
    input::PlayerState in;
    const auto step = [&]() {
        input::compute_edges(in);
        fighter.update(&in, &target, gameplay::FixedStep::seconds);
    };
    // Charge on the ground past the Red boundary, then jump and release aloft.
    for (bool& down : in.down) down = false;
    in.down[input::Action::Shoot] = true;
    for (int i = 0; i < 230; ++i) step();
    check(fighter.charge_tier() == gameplay::ShotTier::Red,
          "230 held updates reach the Red charge tier");
    in.down[input::Action::Jump] = true;
    step();
    in.down[input::Action::Jump] = false;
    step();
    check(fighter.airborne(), "the charge is released airborne");
    check(fighter.charge_tier() == gameplay::ShotTier::Red,
          "the Red tier survives the jump");
    in.down[input::Action::Shoot] = false;
    step();
    checkInt(370, fighter.shot_move_id(), "the airborne red charge binds row 370");

    std::vector<gameplay::PendingShot> shots;
    std::vector<std::pair<int, int>> frames;
    for (int update = 0; update < 240 && shots.size() < 2; ++update) {
        const int phase = fighter.move_phase();
        const int elapsed = fighter.phase_elapsed();
        step();
        for (gameplay::PendingShot shot = fighter.take_pending_shot(); shot.armed;
             shot = fighter.take_pending_shot()) {
            shots.push_back(shot);
            frames.emplace_back(phase, elapsed);
        }
    }
    checkInt(2, static_cast<int>(shots.size()), "the red air charge launches the row-11/12 pair");
    if (shots.size() == 2) {
        check(shots[0].bulletRow == 11 || shots[1].bulletRow == 11,
              "the pair includes the row-11 projectile");
        check(shots[0].bulletRow == 12 || shots[1].bulletRow == 12,
              "the pair includes the row-12 projectile");
        check(frames[0] == std::make_pair(2, 2) && frames[1] == std::make_pair(2, 2),
              "both requests fire on phase-2 frame 2");
    }
}

// FUN_00445ee0 routes a tap shot out of the back dash (state 27) to 407, whose body
// fires the row-4/row-9 pair at fixed +-75 yaw on phase-0 frame 13.
void test_back_dash_shot_407() {
    section("Rena+0: the back-dash tap binds 407 and fires rows 4/9");
    test::Combo combo; std::string error;
    if (!combo.load(0,0,error)) { skip("Rena+0 rig/item/moves unavailable"); return; }
    Fighter fighter, target;
    combo.init(fighter);
    combo.init(target, glm::vec3(0, 0, 2000));
    input::PlayerState in;
    const auto step = [&]() {
        input::compute_edges(in);
        fighter.update(&in, &target, gameplay::FixedStep::seconds);
    };
    // Double-tap back: the second tap admits the back dash row 27.
    for (int tap = 0; tap < 2; ++tap) {
        in.down[input::Action::Down] = true;
        step();
        in.down[input::Action::Down] = false;
        step();
    }
    check(fighter.state() == FighterState::Run, "the double tap starts a dash");
    checkInt(27, fighter.dash_move_id(), "the dash is the back row 27");
    // A tap shot released here leaves the dash through 407.
    in.down[input::Action::Shoot] = true;
    step();
    in.down[input::Action::Shoot] = false;
    step();
    checkInt(407, fighter.shot_move_id(), "the back-dash tap binds the 407 body");

    std::vector<gameplay::PendingShot> shots;
    std::vector<std::pair<int, int>> frames;
    for (int update = 0; update < 40 && shots.size() < 2; ++update) {
        const int phase = fighter.move_phase();
        const int elapsed = fighter.phase_elapsed();
        step();
        for (gameplay::PendingShot shot = fighter.take_pending_shot(); shot.armed;
             shot = fighter.take_pending_shot()) {
            shots.push_back(shot);
            frames.emplace_back(phase, elapsed);
        }
    }
    checkInt(2, static_cast<int>(shots.size()), "407 fires its row-4/9 pair");
    if (shots.size() == 2) {
        check(shots[0].bulletRow == 4 || shots[1].bulletRow == 4,
              "the pair includes row 4");
        check(shots[0].bulletRow == 9 || shots[1].bulletRow == 9,
              "the pair includes row 9");
        check(frames[0] == std::make_pair(0, 13) && frames[1] == std::make_pair(0, 13),
              "both fire on phase-0 frame 13");
        const float yaw0 = glm::degrees(std::atan2(shots[0].dir.x, shots[0].dir.z));
        check(std::abs(std::abs(yaw0) - 75.f) < 0.5f,
              "the pair keeps the body's fixed +-75 yaw");
    }
}

// Row 351 ships with a hand record but no requester: no recovered admission branch
// returns it, which is why it is recorded as handler-only rather than as coverage.
void test_row_351_is_handler_only() {
    section("Rena+0: row 351 exists but no admission selects it");
    test::Combo combo; std::string error;
    if (!combo.load(0,0,error)) { skip("Rena+0 rig/item/moves unavailable"); return; }
    const gameplay::CharacterMove* move = combo.moves.find(351);
    check(move && move->sectionCount == 3, "row 351 parses with its three phases");
    const gameplay::AttackAdmissionTable table{&combo.moves};
    bool selected = false;
    const int states[] = {0, 10, 20, 23, 24, 27, 30, 40, 41, 42,
                          300, 301, 302, 310, 311, 320, 329, 332, 333, 340, 341};
    for (int weapon = 0; weapon < 3; ++weapon)
        for (int state : states)
            for (int phase = 0; phase < 3; ++phase)
                for (int x : {-1, 0, 1})
                    for (int z : {-1, 0, 1})
                        for (bool flag : {false, true})
                            for (bool grounded : {true, false}) {
                                gameplay::AttackAdmissionInput in;
                                in.weaponSlot = weapon;
                                in.state = state;
                                in.phase = phase;
                                in.grounded = grounded;
                                in.x = x;
                                in.z = z;
                                in.normalFlag = flag;
                                in.contact = flag ? 1u : 0u;
                                selected = selected ||
                                    gameplay::rena_melee_admission(in, table) == 351;
                            }
    check(!selected, "no admission input selects row 351");
    // 404 is the shooting side's handler-only row: no recovered tap-shot route
    // returns it either.
    bool shot404 = false;
    for (int weapon = 0; weapon < 3; ++weapon)
        for (int state = 0; state <= 50; ++state)
            for (bool grounded : {true, false})
                shot404 = shot404 ||
                    gameplay::rena_tap_shot_state(weapon, state, grounded) == 404;
    check(!shot404, "no tap-shot route selects handler-only row 404");
}

// The walking/dash taps route through FUN_00445ee0's shot branches: walking to 401,
// side dashes to 405/406 and the air dash to 408. Each fires its normal row-0 request
// on frame 12.
void test_dash_tap_shots() {
    section("Rena+0: the walking/dash taps bind 401/405/406/408 on frame 12");
    test::Combo combo; std::string error;
    if (!combo.load(0,0,error)) { skip("Rena+0 rig/item/moves unavailable"); return; }
    struct Case { int expectedState; input::Action dir; bool airborneDash; bool walk; int dashRow; };
    const Case cases[] = {{401, input::Action::Right, false, true, 0},
                          {405, input::Action::Right, false, false, 23},
                          {406, input::Action::Left, false, false, 24},
                          {408, input::Action::Right, true, false, 30}};
    for (const Case& c : cases) {
        Fighter fighter, target;
        combo.init(fighter);
        combo.init(target, glm::vec3(0, 0, 2000));
        input::PlayerState in;
        const auto step = [&]() {
            input::compute_edges(in);
            fighter.update(&in, &target, gameplay::FixedStep::seconds);
        };
        if (c.walk) {
            in.down[c.dir] = true;
            for (int i = 0; i < 8; ++i) step();
            check(fighter.state() == FighterState::Walk, "holding a direction walks");
        } else {
            if (c.airborneDash) {
                in.down[input::Action::Jump] = true;
                step();
                in.down[input::Action::Jump] = false;
                for (int i = 0; i < 10; ++i) step();
            }
            for (int tap = 0; tap < 2; ++tap) {
                in.down[c.dir] = true;
                step();
                in.down[c.dir] = false;
                step();
            }
            check(fighter.state() == FighterState::Run, "the tap opens a dash state");
            checkInt(c.dashRow, fighter.dash_move_id(), "the dash carries its row");
            // Hold the direction through a tick first: re-pressing it here would be a
            // fresh double-tap edge, which admits another dash and returns before the
            // shot charge branch (408's admission needs the axis held).
            in.down[c.dir] = true;
            step();
        }
        in.down[input::Action::Shoot] = true;
        step();
        in.down[input::Action::Shoot] = false;
        step();
        check(fighter.state() == FighterState::ShootA, "the release enters the shot state");
        checkInt(c.expectedState, fighter.shot_move_id(), "the tap binds its shot state");
        if (fighter.shot_move_id() != c.expectedState) continue;
        bool fired = false;
        int frame = -1, row = -1;
        for (int update = 0; update < 40 && !fired; ++update) {
            const int elapsed = fighter.phase_elapsed();
            step();
            for (gameplay::PendingShot shot = fighter.take_pending_shot(); shot.armed;
                 shot = fighter.take_pending_shot()) {
                fired = true;
                frame = elapsed;
                row = shot.bulletRow;
            }
        }
        check(fired, "the tap fires a request");
        checkInt(0, row, "the tap request is the normal row 0");
        checkInt(12, frame, "the request fires on frame 12");
    }
}

void test_delayed_reaction_rows() {
    section("rows 104/105/204/205 hold phase 0 before seeding");
    test::Combo combo; std::string error;
    if (!combo.load(0,0,error)) { skip("Rena+0 rig/item/moves unavailable"); return; }
    struct Case {
        int row;
        float expectedFirstDelta;
        float expectedChange;   // first minus second per-update delta
        float expectedTravel;   // distance covered over the 7 updates after the seed
        bool lifts;
    };
    // 104/204 seed a fixed -15/+15 and decay 1.5 a tick; 105/205 seed the record pair
    // (counter 5 lift, rise 5 slide), 105 settling toward -4 and 205 toward +4
    // (FUN_00428510 cases 0x69/0xcd).
    const Case cases[] = {
        {104, 15.f, 1.5f, 63.f, false},
        {105,  5.f, 0.25f, 29.5f, true},
        {204, 15.f, 1.5f, 63.f, false},
        {205,  5.f, 0.25f, 29.5f, true},
    };
    for (const Case& c : cases) {
        Fighter attacker, victim;
        combo.init(attacker, glm::vec3(0, 0, 100));
        combo.init(victim);
        victim.set_state(FighterState::Idle);
        gameplay::HitReaction injected;
        injected.row = injected.rowHigh = c.row;
        injected.meterA = 120;
        injected.counter = 5.f;
        injected.rise = 5.f;
        victim.take_damage(0, &attacker, 0, c.row, false, injected);
        checkInt(c.row, victim.reaction_move_for_test(),
                 "an injected contact keeps its reaction row");
        checkInt(0, victim.move_phase(), "the injected reaction starts in phase 0");
        const glm::vec3 held = victim.position();
        float peak = held.y;
        for (int i = 0; i < 61; ++i) {
            victim.update(nullptr, nullptr, gameplay::FixedStep::seconds);
            peak = std::max(peak, victim.position().y);
        }
        const glm::vec3 heldAfter = victim.position();
        check(glm::length(glm::vec2(heldAfter.x - held.x, heldAfter.z - held.z)) < 1e-3f,
              "phase 0 plays standing still");
        check(peak - held.y < 1e-3f, "phase 0 does not lift the victim");
        checkInt(0, victim.move_phase(), "the gated phase 0 still holds at 61 updates");

        victim.update(nullptr, nullptr, gameplay::FixedStep::seconds);
        checkInt(1, victim.move_phase(), "the 62nd executor call enters phase 1");
        const glm::vec3 seededAt = victim.position();
        const float firstDelta = glm::length(
            glm::vec2(seededAt.x - heldAfter.x, seededAt.z - heldAfter.z));
        check(std::fabs(firstDelta - c.expectedFirstDelta) < 0.06f,
              "phase 1 seeds the recovered slide speed");
        check(victim.airborne() == c.lifts, "only the launcher rows leave the ground");

        float previous = firstDelta;
        victim.update(nullptr, nullptr, gameplay::FixedStep::seconds);
        const float second = glm::length(glm::vec2(victim.position().x - seededAt.x,
                                                   victim.position().z - seededAt.z));
        check(std::fabs((previous - second) - c.expectedChange) < 0.06f,
              "the slide follows the row's own per-tick decay");
        for (int i = 0; i < 6; ++i)
            victim.update(nullptr, nullptr, gameplay::FixedStep::seconds);
        const float travelled = glm::length(glm::vec2(victim.position().x - seededAt.x,
                                                      victim.position().z - seededAt.z));
        check(std::fabs(travelled - c.expectedTravel) < 0.5f,
              "the seeded law travels the recovered distance");
        if (c.lifts) {
            for (int i = 0; i < 40 && victim.state() == FighterState::Hit; ++i)
                victim.update(nullptr, nullptr, gameplay::FixedStep::seconds);
            checkInt(c.row == 205 ? 119 : 118, victim.down_row_for_test(),
                     "the launcher lands into its own lying row");
        }
    }
}

void test_landing_followup_chain_runs_to_its_last_phase() {
    section("Rena+0 landing follow-up chain reaches row 341's last phase");
    test::Combo combo; std::string error;
    if (!combo.load(0,0,error)) { skip("Rena+0 rig/item/moves unavailable"); return; }
    Fighter fighter;
    combo.init(fighter);
    input::PlayerState in;
    const auto step = [&]() {
        input::compute_edges(in);
        fighter.update(&in, nullptr, gameplay::FixedStep::seconds);
    };
    const auto press = [&](input::Action action) {
        for (bool& down : in.down) down = false;
        in.down[action] = true;
        step();
        for (bool& down : in.down) down = false;
        step();
    };
    press(input::Action::Jump);
    for (int i = 0; i < 40 && !fighter.airborne(); ++i) step();
    check(fighter.airborne(), "the chain starts from an airborne fighter");
    press(input::Action::AttackA);
    for (int i = 0; i < 40 && fighter.attack_move_id() != 320; ++i) step();
    checkInt(320, fighter.attack_move_id(), "the air press admits row 320");
    for (int i = 0; i < 240 && fighter.attack_move_id() != 329; ++i) step();
    checkInt(329, fighter.attack_move_id(), "row 320 lands into the 329 exit row");
    for (int i = 0; i < 240 && fighter.phase_elapsed() < 5; ++i) step();
    press(input::Action::AttackA);
    for (int i = 0; i < 40 && fighter.attack_move_id() != 340; ++i) step();
    checkInt(340, fighter.attack_move_id(), "329 admits the landing row 340");
    for (int i = 0; i < 240 && fighter.phase_elapsed() < 25; ++i) step();
    press(input::Action::AttackA);
    for (int i = 0; i < 40 && fighter.attack_move_id() != 341; ++i) step();
    checkInt(341, fighter.attack_move_id(), "340 admits its follow-up row 341");

    const gameplay::CharacterMove* followup = combo.moves.find(341);
    check(followup && followup->sectionCount == 4, "row 341 carries its four-phase body");
    int seenPhases = 0;
    bool setsMatch = true;
    int updates = 0;
    while (fighter.state() == FighterState::AttackA && updates++ < 200) {
        if (followup) {
            const int phase = fighter.move_phase();
            if (phase >= 0 && phase < followup->sectionCount) {
                seenPhases = std::max(seenPhases, phase + 1);
                setsMatch &= fighter.anim_set_index() == followup->phase_set_index(phase);
            }
        }
        step();
    }
    checkInt(4, seenPhases, "the row advances through all four phases");
    check(setsMatch, "every phase binds its own phase's animation set");
    check(fighter.state() == FighterState::Idle && !fighter.airborne(),
          "the chain finishes standing");
}

void test_back_kick_completes_its_final_phase() {
    section("Rena+0 back kick lifetime");
    test::Combo combo; std::string error;
    if (!combo.load(0,0,error)) { skip("Rena+0 rig/item/moves unavailable"); return; }
    Fighter fighter, opponent;
    combo.init(fighter); combo.init(opponent, glm::vec3(0,0,2000));
    input::PlayerState in;
    in.down[input::Action::Down] = true;
    in.down[input::Action::AttackA] = true;
    tick_held(fighter, in);
    checkInt(310, fighter.attack_move_id(), "back input selects row 310");
    in.down[input::Action::Down] = false;
    in.down[input::Action::AttackA] = false;
    for (int i = 0; i < 27; ++i) tick_held(fighter, in);
    check(fighter.state() == FighterState::AttackA && fighter.move_phase() == 2,
          "row 310 stays active after the legacy 27-tick timer");
    int updates = 0;
    while (fighter.state() == FighterState::AttackA && updates++ < 100)
        tick_held(fighter, in);
    check(fighter.state() != FighterState::AttackA,
          "row 310 exits after its last phase completes");
}

// FUN_0043ffc0 pauses the executor; FUN_004202b0 skips integration until
// the preceding FUN_0041f580 decrement clears +0xa0.
void test_hitstop_freezes_reaction() {
    section("Rena+0 hitstop pauses reaction and movement");
    test::Combo combo; std::string error;
    if (!combo.load(0,0,error)) { skip("Rena+0 rig/item/moves unavailable"); return; }
    Fighter attacker, victim;
    combo.init(attacker, glm::vec3(0,0,100));
    combo.init(victim);
    gameplay::HitReaction hit;
    hit.row = 113; hit.rowHigh = 113; hit.meterA = 200;
    hit.counter = 5.f; hit.rise = 20.f;
    victim.take_damage(0, &attacker, 6, 113, false, hit);
    const glm::vec3 start = victim.position();
    const int frame = victim.phase_elapsed();
    for (int i = 0; i < 5; ++i)
        victim.update(nullptr, nullptr, gameplay::FixedStep::seconds);
    check(glm::length(victim.position() - start) < 1e-4f,
          "hitstop prevents horizontal and vertical displacement");
    checkInt(frame, victim.phase_elapsed(), "hitstop holds the reaction clock");
    victim.update(nullptr, nullptr, gameplay::FixedStep::seconds);
    check(glm::length(victim.position() - start) > 1.f,
          "movement resumes after the final hitstop decrement");
    checkInt(frame, victim.phase_elapsed(), "the executor still sees the last hitstop tick");
    victim.update(nullptr, nullptr, gameplay::FixedStep::seconds);
    check(victim.phase_elapsed() > frame, "the reaction clock resumes on the next update");

    victim.take_damage(0, &attacker, 6, 113, false, hit);
    victim.reset(glm::vec3(0.f), 0.f);
    victim.set_state(FighterState::Idle);
    const int resetFrame = victim.phase_elapsed();
    victim.update(nullptr, nullptr, gameplay::FixedStep::seconds);
    check(victim.phase_elapsed() > resetFrame,
          "round reset clears the previous hitstop");
}

// FUN_00637950 adds 180 degrees to the impact bearing for a back hit;
// row 200's positive speed must carry the victim away from the attacker.
void test_back_hit_throws_away() {
    section("a hit from behind throws the victim away from the attacker");
    test::Combo combo; std::string error;
    if (!combo.load(0,0,error)) { skip("Rena+0 rig/item/moves unavailable"); return; }
    gameplay::MatchConfig config; config.fighterCount = 2;
    for (int i = 0; i < 2; ++i) {
        config.moves[i] = &combo.moves; config.weapon[i] = &combo.weapon;
    }
    // The attacker stands BEHIND the victim: she faces -Z, he is at +Z of her.
    config.spawn[0] = glm::vec3(0, 0, 60);
    config.spawn[1] = glm::vec3(0, 0, -60);
    const xm::Model* models[4] = {&combo.model, &combo.model};
    xm::Controller* controllers[4] = {combo.controller(), combo.controller()};
    gameplay::Match match; match.reset(config, models, controllers, nullptr, nullptr);
    match.economy().setLogFile(nullptr);
    const input::PlayerState* idle[4]{};
    for (int i = 0; i < 70; ++i) match.step(idle, gameplay::FixedStep::seconds);

    Fighter& victim = match.fighter(1);
    gameplay::HitReaction finisher;
    finisher.row = 113; finisher.rowHigh = 113;
    finisher.counter = 5.0f;   // combat[17]: the lift
    finisher.rise = 20.0f;     // combat[18]: the slide
    finisher.meterA = 120; finisher.meterB = 20;
    const glm::vec3 start = victim.position();
    const glm::vec3 attackerAt = match.fighter(0).position();
    // Face away explicitly: match targeting may otherwise rotate the actors during setup.
    victim.reset(start, glm::pi<float>());
    victim.set_state(FighterState::Idle);
    finisher.row = finisher.rowHigh = 100;
    finisher.meterA = 60;
    const float facingBefore = victim.facing_yaw();
    victim.take_damage(0, &match.fighter(0), 6, 100, false, finisher);
    check(victim.state() == FighterState::Idle &&
          std::abs(std::remainder(victim.facing_yaw() - facingBefore, glm::two_pi<float>())) < 1e-5f,
          "a non-tripping hit preserves the victim's facing");
    victim.take_damage(0, &match.fighter(0), 6, 100, false, finisher);
    checkInt(200, victim.reaction_move_for_test(), "two 60-point back hits select row 200");
    for (int i = 0; i < 20; ++i) match.step(idle, gameplay::FixedStep::seconds);
    const glm::vec3 moved = victim.position() - start;
    const float awayFromAttacker = glm::length(glm::vec2(moved.x, moved.z));
    check(awayFromAttacker > 30.f, "the victim travels horizontally");
    // The displacement must increase her distance from the attacker, not reduce it.
    const float before = glm::length(glm::vec2(start.x - attackerAt.x, start.z - attackerAt.z));
    const float after = glm::length(glm::vec2(victim.position().x - attackerAt.x,
                                              victim.position().z - attackerAt.z));
    check(after > before, "and away from him, not through him");
}

// A landed hit must (a) play the reaction row the record names and (b) MOVE the victim. The
// harness above teleports the dummy every active tick, which resets its state, so this case
// places the pair once and then lets the blow land on its own.
void test_reaction_displaces_victim() {
    section("a landed hit plays its row and displaces the victim");
    test::Combo combo; std::string error;
    if (!combo.load(0,0,error)) { skip("Rena+0 rig/item/moves unavailable"); return; }
    gameplay::MatchConfig config; config.fighterCount = 2;
    for (int i = 0; i < 2; ++i) {
        config.moves[i] = &combo.moves; config.weapon[i] = &combo.weapon;
        config.spawn[i] = glm::vec3(0, 0, 120.f * i);
    }
    const xm::Model* models[4] = {&combo.model, &combo.model};
    xm::Controller* controllers[4] = {combo.controller(), combo.controller()};
    gameplay::Match match; match.reset(config, models, controllers, nullptr, nullptr);
    match.economy().setLogFile(nullptr);

    Fighter& attacker = match.fighter(0);
    Fighter& victim = match.fighter(1);
    const input::PlayerState* idle[4]{};
    for (int i = 0; i < 70; ++i) match.step(idle, gameplay::FixedStep::seconds);

    // One placement puts the dummy's chest in the posed volume; the swing then lands on its own.
    input::PlayerState input; input.down[input::Action::AttackA] = true;
    const input::PlayerState* inputs[4] = {&input, nullptr, nullptr, nullptr};
    bool landed = false;
    int setOnHit = -1;
    int attackerStop = 0;
    for (int i = 0; i < 120 && !landed; ++i) {
        input::compute_edges(input);
        if (attacker.melee_in_active()) test::Combo::placeAtAttack(attacker, victim);
        const gameplay::MatchFrame frame = match.step(inputs, gameplay::FixedStep::seconds);
        if (frame.meleeHit[0]) {
            landed = true;
            setOnHit = victim.anim_set_index();
            attackerStop = attacker.current_move_record()->combat[9];
        }
    }
    check(landed, "the swing lands");
    if (!landed) return;
    // Row 100 is the standing flinch and its first phase is set 25.
    checkInt(25, setOnHit, "the victim plays the standing-flinch row's clip");
    checkInt(static_cast<int>(FighterState::Hit), static_cast<int>(victim.state()),
             "and is in the reaction state");

    const int attackerFrame = attacker.phase_elapsed();
    input.down[input::Action::AttackA] = false;
    if (attackerStop > 0) {
        input::compute_edges(input);
        match.step(inputs, gameplay::FixedStep::seconds);
        checkInt(attackerFrame, attacker.phase_elapsed(),
                 "the attacker's record combat[9] freezes its clock");
    } else {
        skip("row 300 attacker hitstop is zero");
    }
    const glm::vec3 before = victim.position();
    for (int i = 0; i < 24; ++i) {
        input::compute_edges(input);
        match.step(inputs, gameplay::FixedStep::seconds);
    }
    const glm::vec3 moved = victim.position() - before;
    // The row's own law is a -25/tick slide along the victim's facing, so it must travel.
    check(glm::length(glm::vec2(moved.x, moved.z)) > 5.f,
          "and the row's slide actually carries her");
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
    for (int i = 0; i < 70; ++i) match.step(idle,gameplay::FixedStep::seconds);
    input::PlayerState input; input.down[input::Action::AttackA] = true;
    const input::PlayerState* inputs[4] = {&input,nullptr,nullptr,nullptr};
    int enemyContacts = 0;
    for (int i = 0; i < 180; ++i) {
        input::compute_edges(input);
        if (match.fighter(0).melee_in_active())
            for (int victim = 1; victim < 4; ++victim)
                test::Combo::placeAtAttack(match.fighter(0),match.fighter(victim));
        match.step(inputs,gameplay::FixedStep::seconds);
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
    for (int i = 0; i < 70; ++i) match.step(idle,gameplay::FixedStep::seconds);
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
        match.step(inputs,gameplay::FixedStep::seconds);
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
    // 0.008 s / 0.016 = 0.5 frames, and 0x66b668 truncates toward zero, so the clip takes
    // its whole duration (480 ticks = 14 updates) instead of expiring on the entry update.
    // This is the case an earlier std::nearbyint read got wrong (it would have used 1
    // update), which is why the label names the truncation rule rather than a rounding mode.
    checkInt(14,fighter.anim_set_index(),"half-frame period truncates to zero updates");
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
    // Side rows are command-mapped: history x=-1 (Left, command 3) selects row
    // 24 (sets 19/20/21) and x=+1 (Right, command 4) selects row 23 (sets
    // 22/23/24), per FUN_00445ee0:86-95 (+0x830==3 -> 0x18, ==4 -> 0x17) and the
    // donor command switches (rena_dash.hpp:11 et al).
    struct Case { int action; int move; int set; const char* name; };
    const Case cases[] = {
        {input::Action::Up, 20, 13, "forward"},
        {input::Action::Down, 27, 16, "back"},
        {input::Action::Left, 24, 19, "left"},
        {input::Action::Right, 23, 22, "right"},
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
        std::snprintf(what, sizeof(what), "%s dash resolves move %d", c.name, c.move);
        checkInt(c.move, f.dash_move_id(), what);
        std::snprintf(what, sizeof(what), "%s dash opens on set %d", c.name, c.set);
        checkInt(c.set, f.anim_set_index(), what);
        check(!f.anim_fallback(), "directional dash binds the equipped animation");
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
        checkInt(30, f.dash_move_id(), "Rena+0 airborne dispatch binds its source row 30");
        checkInt(moves.first_set_index(30), f.anim_set_index(), "air dash uses the equipped row-30 tag");
        check(!f.anim_fallback(), "Rena+0 air dash no longer presents idle fallback");
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
    section("guard plays row 390's stance clip (no selector, not a fallback)");
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
    // Guard has no move SELECTOR (the block branch of FUN_00637950 binds nothing), but it
    // is not animateless: the character DAT carries the stance as row 390, whose opening
    // clip is what the state must show. Holding the previous clip read as "blocking has
    // no animation at all" (PILOT-EVIDENCE-CONTRACT V3-19).
    const int guardSet = combo.moves.first_set_index(390);
    check(guardSet >= 0, "row 390 carries the guard stance clip");
    checkInt(guardSet, f.anim_set_index(), "guard binds row 390's opening clip");
    check(!f.anim_fallback(), "guard is not a set-0 fallback");
    for (int i = 0; i < 5; ++i) tick_held(f, walk);
    checkInt(guardSet, f.anim_set_index(), "the guard clip stays bound while guarding");
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
    // A guard entered from standing binds row 390's opening clip for the same reason a
    // guard entered from walking does: the stance has its own animation (V3-19).
    checkInt(combo.moves.first_set_index(390), f.anim_set_index(),
             "a standing guard binds row 390's opening clip");
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
    testPosedCombat(); testPosedMatch(); test_reaction_displaces_victim();
    test_hitstop_freezes_reaction();
    test_zero_meter_hit_does_not_refresh_stagger();
    test_move_contact_windows();
    test_melee_chain_contacts();
    test_landing_followup_contacts();
    test_hyper_ex_contact();
    test_air_full_charge_370();
    test_back_dash_shot_407();
    test_row_351_is_handler_only();
    test_dash_tap_shots();
    test_delayed_reaction_rows();
    test_first_live_record_opens_at_frame_zero();
    test_landing_followup_chain_runs_to_its_last_phase();
    test_back_kick_completes_its_final_phase();
    test_back_hit_throws_away();
    testRepeatContactSuppression(); testPhaseClock();
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
