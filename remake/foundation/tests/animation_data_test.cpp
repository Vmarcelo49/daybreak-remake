// FUN_0041e180 / FUN_0043ffc0 / FUN_005f8510: parser and execution regressions.
// Bundle-winning bytes, equipped item and the actual .X periods travel together.
#include "assets/asset_source.h"
#include "assets/cnv.h"
#include "game/shot_visual.h"
#include "gameplay/fighter.h"
#include "gameplay/move_behavior.h"
#include "combo_fixture.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <memory>

namespace {
int checks = 0, failures = 0;
void check(bool pass, const std::string& label) {
    ++checks;
    if (!pass) { ++failures; std::printf("FAIL: %s\n", label.c_str()); }
}

std::string install() {
    if (const char* path = std::getenv("GAME_DIR"))
        if (std::filesystem::exists(std::filesystem::path(path) / "daybreak00.dat")) return path;
    for (auto path = std::filesystem::current_path(); !path.empty(); path = path.parent_path()) {
        const auto game = path / "Higurashi-Daybreak";
        if (std::filesystem::exists(game / "daybreak00.dat")) return game.string();
        if (path == path.parent_path()) break;
    }
    return {};
}

bool read(const std::string& path, std::vector<uint8_t>& bytes) {
    return fnd::assets::assetSource().read(path, bytes);
}

using Combo = test::Combo;

void tick(gameplay::Fighter& fighter, fnd::input::PlayerState& input, gameplay::Fighter* opponent = nullptr) {
    fnd::input::compute_edges(input);
    fighter.update(&input,opponent,1.0/64.0);
}

void records() {
    std::vector<uint8_t> bytes(30,0);
    const auto word = [&](int value) {
        const auto raw = static_cast<uint32_t>(value);
        for (int i=0; i<4; ++i) bytes.push_back(static_cast<uint8_t>(raw >> (8*i)));
    };
    word(7);
    for (int value : {-3,7,100}) word(value);
    word(20);
    for (int i=0; i<20; ++i) word(100*i-50);
    word(0x4100); word(0x314); word(1);
    for (int value : {-2,4,77}) word(value);
    gameplay::MoveEntry decoded;
    size_t offset = 0;
    check(bytes.size()==154 && gameplay::readCombatRecord(bytes.data(),bytes.size(),offset,decoded) && offset==154,
          "state record consumes exactly thirty name bytes and thirty-one four-byte fields");
    check(decoded.anchor==std::array<float,3>{-3,7,100} &&
          decoded.endAnchor==std::array<float,3>{-2,4,77},
          "both anchor triples use signed numeric conversion, not float-bit reinterpretation");
    bool columns = true;
    for (int i=0; i<20; ++i) columns &= decoded.combat[static_cast<size_t>(i)]==100*i-50;
    check(columns && decoded.stateFlags==0x4100 && decoded.attackFlags==0x314 && decoded.collisionShape==1,
          "every combat column and tail word survives at its audited offset");
    offset = 0;
    check(!gameplay::readCombatRecord(bytes.data(),bytes.size()-1,offset,decoded) && offset==0,
          "a truncated anchor tail cannot produce a partially consumed record");

    gameplay::MovePhase phase;
    phase.entryCount = 3;
    phase.entries[0].activeFrame = 10;
    phase.entries[1].activeFrame = 12;
    phase.entries[2].activeFrame = 16;
    check(phase.record_at(0) == &phase.entries[0],"first record is selected at bind, even before its threshold");
    check(phase.record_at(11) == &phase.entries[0],"phase cursor holds the current record");
    check(phase.record_at(12) == &phase.entries[1],"phase cursor changes at equality");
    check(phase.record_at(100) == &phase.entries[2],"last record persists, not an invented eight-tick window");
    gameplay::TextureEvent event{2,4,6,"eyes","closed"};
    check(!event.active(1) && event.active(2) && event.active(3) && !event.active(4) && event.active(8),
          "texture events are half-open, with repeat applied before the interval");
    gameplay::WeaponTrail trail;
    for (int i = 0; i < 8; ++i) trail.step(true,{0,0,0},{float(i),10,20});
    check(trail.triangles() == 40,"ribbon grows by five triangles per accepted sample, bounded at forty");
    const auto vertices = trail.vertices();
    bool finite = true;
    for (const auto& v : vertices) finite &= std::isfinite(v.pos.x) && std::isfinite(v.pos.y) && std::isfinite(v.pos.z);
    check(finite,"all clamped spline spans produce finite vertices");
    // FUN_0042fff0 shifts the history and grows only when the tip sample CHANGED
    // (0x43001d FUN_00430670 gates 0x43004e/0x4300a1). A held weapon must not keep
    // stacking the same point, and its inactive ribbon still decays by two per call.
    gameplay::WeaponTrail held;
    for (int i = 0; i < 8; ++i) held.step(true,{0,0,0},{5,10,20});
    check(held.triangles() == 5,"a stationary active tip grows once, not once per call");
    for (int i = 0; i < 20; ++i) held.step(false,{},{5,10,20});
    check(held.triangles() == 0,"an inactive held tip still decays two per update");
    for (int i = 0; i < 20; ++i) trail.step(false,{},{1,2,3});
    check(trail.triangles() == 0,"inactive ribbon decays by two, then disappears");

    gameplay::BulletParameter bullet;
    bullet.phases.resize(2);
    bullet.phases[0] = phase;
    bullet.phases[1].entryCount = 1;
    bullet.phases[1].entries[0].activeFrame = 0;
    gameplay::Projectile shot;
    shot.parameter = &bullet;
    shot.elapsed = 100;
    check(shot.record() == &bullet.phases[0].entries[2],
          "bullets retain section zero's last record instead of advancing fighter phases");
    bullet.animationSets.resize(2);
    bullet.animationSets[1].textures.push_back({0,200,0,"source","replacement"});
    check(shot.texture_overrides().size() == 1,
          "bullet material intervals include every trailer row, not a phase-selected subset");
    bullet.phases[0].entries[2].stateFlags = 0x4000;
    shot.ownRotation = {0.f,0.f,glm::radians(35.f)};
    shot.aimDirection = {0,0,1};
    const auto expected = game::shotModelMatrix({}, {}, shot.ownRotation);
    check(glm::length(glm::vec3(shot.model_matrix()[0]-expected[0])) < 1e-6f,
          "record flag 0x4000 suppresses aiming without dropping the handler's own rotation");
}

void roster() {
    int combos = 0, moves = 0, phases = 0, entries = 0, sets = 0, textures = 0;
    for (int character = 0; character < gameplay::kCharacterCount; ++character) {
        for (int slot = 0; slot < gameplay::weaponCountForCharacter(character); ++slot) {
            auto combo = std::make_unique<Combo>();
            std::string error;
            const bool loaded = combo->load(character,slot,error);
            const auto label = gameplay::comboSlotLabel(character,slot);
            check(loaded,label + " joins the exact NN.dat and item ID");
            if (!loaded) continue;
            ++combos; moves += combo->moves.count(); sets += combo->moves.animation_set_count();
            xm::TextureCache itemTextures("data/item/");
            for (int slotIndex = 0; slotIndex < combo->weapon.slotCount; ++slotIndex) {
                const auto& slotData = combo->weapon.slots[slotIndex];
                if (!slotData.meshName.empty() && !slotData.textureName.empty())
                    check(itemTextures.get(slotData.textureName) != nullptr,
                          label + " ribbon texture resolves beside the item model");
            }
            check(gameplay::locomotion(&combo->moves) != nullptr,label + " resolves its original constructor/handler");
            gameplay::Fighter fighter;
            combo->init(fighter);
            fnd::input::PlayerState input;
            input.down[fnd::input::Action::Up] = true;
            const auto* motion = gameplay::locomotion(&combo->moves);
            const float walkStart = fighter.position().z;
            tick(fighter,input);
            check(motion && std::abs(fighter.position().z-walkStart-motion->walk)<1e-3f,
                  label + " walk displacement comes from its recovered handler");
            input.down[fnd::input::Action::Up] = false; tick(fighter,input);
            input.down[fnd::input::Action::Up] = true;
            const float dashStart = fighter.position().z;
            tick(fighter,input);
            check(motion && std::abs(fighter.position().z-dashStart-motion->forwardDash)<1e-3f,
                  label + " forward dash binds its own speed and animation phases");
            for (int i=0; i<30; ++i) tick(fighter,input);
            check(fighter.state()==gameplay::FighterState::Run && fighter.move_phase()==1,
                  label + " held dash is not cut off by the old twenty-tick timer");
            input.down[fnd::input::Action::Up] = false; tick(fighter,input);
            check(fighter.move_phase()==2,label + " input release enters data-defined recovery");
            for (int i=0; i<180 && fighter.state()==gameplay::FighterState::Run; ++i) tick(fighter,input);
            check(fighter.state()==gameplay::FighterState::Idle,label + " recovered pause and .X period finish recovery");
            for (int id = 0; id < gameplay::CharacterMoves::kMaxMoves; ++id) {
                const auto* move = combo->moves.find(id);
                if (!move) continue;
                phases += move->sectionCount;
                for (int p = 0; p < move->sectionCount; ++p) {
                    const auto& phase = move->phases[p];
                    entries += phase.entryCount;
                    check(phase.setIndex >= 0 && static_cast<size_t>(phase.setIndex) < combo->model.anims.size(),
                          label + " phase names a real .X controller set");
                    for (int e = 0; e < phase.entryCount; ++e) {
                        const auto& record = phase.entries[e];
                        for (float value : record.anchor) check(std::isfinite(value) && value == std::trunc(value),label + " first anchor is a numeric integer conversion");
                        for (float value : record.endAnchor) check(std::isfinite(value) && value == std::trunc(value),label + " second anchor is a numeric integer conversion");
                    }
                }
            }
            for (int set = 0; set < combo->moves.animation_set_count(); ++set)
                textures += static_cast<int>(combo->moves.texture_events(set).size());
        }
    }
    check(combos == 46,"all 46 legal character+weapon combos parse");
    check(moves == 5847 && phases == 9903 && entries == 12161 && sets == 5879 && textures == 7921,
          "bundle-winning structure matches the audited full stream counts");
    std::printf("roster: %d combos, %d moves, %d phases, %d records, %d sets, %d texture events\n",combos,moves,phases,entries,sets,textures);
}

// Issue #31's own selector: an airborne melee press must bind the aerial row and play
// that row's set, not fall back to the grounded neutral. `execution()` covers the ground
// chain; this is the air half, which the reworked tests had dropped.
void aerial_attack(const Combo& combo) {
    gameplay::Fighter fighter, opponent;
    combo.init(fighter);
    combo.init(opponent,{0,0,300});
    fighter.set_state(gameplay::FighterState::Idle);
    fnd::input::PlayerState input;
    input.down[fnd::input::Action::Jump] = true;
    tick(fighter,input,&opponent);
    check(fighter.airborne(),"Rena+0 leaves the ground on the jump press");
    check(!fighter.aerial_attack(),"the jump alone does not select an aerial swing");
    input.down[fnd::input::Action::Jump] = false;
    for (int i = 0; i < 8 && fighter.state() != gameplay::FighterState::Jump; ++i)
        tick(fighter,input,&opponent);
    input.down[fnd::input::Action::AttackA] = true;
    tick(fighter,input,&opponent);
    check(fighter.aerial_attack(),"pressing melee while airborne flags the aerial swing");
    const int air = combo.moves.find(340) ? 340 : -1;
    check(air > 0 && fighter.attack_move_id() == air,
          "the airborne press resolves the weapon's own aerial row 340");
    const int set = combo.moves.first_set_index(340);
    check(set >= 0 && fighter.anim_set_index() == set,
          "move 340 plays its own table set (" + std::to_string(set) + "), not set 0");
}

// FUN_00637950's entry test is radius != 0 (0x6379e0, byte-verified) and combat[0] is read
// only inside the HP math, so a zero-power record is a real contact. This drives one
// through the REAL collision and resolution path: a synthetic zero-power record is
// installed into an equipped combo's row and the actual hit volume is used, so the test
// fails if the OLD PREDICATE comes back (the record stops being checkable at all) or if
// the OLD HP CLAMP comes back (the victim loses 1 HP it should not).
void zero_power_contact() {
    // Its OWN fixture: the reshaped row must not leak into the combos the other tests
    // share (install_move_phase0_record rewrites the row in place).
    Combo combo;
    std::string loadError;
    if (!combo.load(0, 0, loadError)) {
        check(false, "Rena+0 fixture for the zero-power contact loads");
        return;
    }
    gameplay::Fighter attacker, victim;
    combo.init(attacker);
    combo.init(victim, {0, 0, 60});

    // Take the neutral row's own hit record and keep its bone and both anchor triples, so
    // the volume sits exactly where the shipped swing puts it, then strip its HP power.
    const gameplay::CharacterMove* row = combo.moves.find(300);
    const gameplay::MoveEntry* shipped = nullptr;
    for (int p = 0; row && p < row->sectionCount && !shipped; ++p)
        for (int e = 0; e < row->phases[p].entryCount; ++e)
            if (row->phases[p].entries[e].has_combat()) { shipped = &row->phases[p].entries[e]; break; }
    check(shipped != nullptr, "Rena+0 row 300 ships a hit volume to reshape");
    if (!shipped) return;
    gameplay::MoveEntry zero = *shipped;
    zero.combat[0] = 0;              // power 0: the case under test
    zero.baseDamage = 0;
    zero.defenderHitstun = 9;        // an assertion target the shipped row need not match
    zero.reactionMove = 113;         // the reaction the zero-power rows carry
    check(combo.moves.install_move_phase0_record(300, zero),
          "the reshaped row installs into the equipped table");

    fnd::input::PlayerState input;
    input.down[fnd::input::Action::AttackA] = true;
    tick(attacker, input, &victim);
    input.down[fnd::input::Action::AttackA] = false;
    check(attacker.attack_move_id() == 300, "the press binds the neutral row under test");
    check(attacker.move_phase() == 0 && attacker.phase_elapsed() < 2,
          "and row 300's phase-0 hit volume is live at the start it was installed for");

    const int hpBefore = victim.hp();
    const int takenBefore = victim.stats().damageTaken;
    const float hyperBefore = victim.hyper_gauge();
    // Put the victim inside the posed volume, not at a guessed distance (issue #31).
    const auto attack = attacker.hitbox_debug();
    const auto body = victim.hitbox_debug();
    victim.reset(victim.position() + attack.attackCenter - body.anchors[1],
                 victim.facing_yaw());
    const bool landed = attacker.try_melee_hit(victim);
    check(landed, "a zero-power record still lands through the collision test");
    check(victim.hp() == hpBefore , "a zero-power contact takes no HP");
    check(victim.stats().damageTaken == 0, "and records no damage taken");
    check(attacker.stats().damageDealt == 0, "nor any for the attacker");
    check(victim.hyper_gauge() == hyperBefore,
          "and does not misroute the record's mode-gauge column into the hyper bar");
    check(victim.state() == gameplay::FighterState::Hit,
          "the zero-power contact still stuns the victim");
    int stunned = 1;
    while (victim.state() == gameplay::FighterState::Hit && stunned < 200) {
        tick(victim, input, nullptr);
        ++stunned;
    }
    // The landing frame is the first of the state; the counter then runs down once per
    // update, so the state lasts defenderHitstun + 1 observed frames.
    check(stunned == zero.defenderHitstun + 1,
          "for exactly the record's own defender hitstop: " + std::to_string(stunned) +
              " frames for the record's " + std::to_string(zero.defenderHitstun) +
              " (a shared default would be " +
              std::to_string(gameplay::FighterConstants::kHitStunFrames + 1) + ")");
}

void execution(const Combo& combo) {
    gameplay::Fighter fighter, opponent;
    combo.init(fighter);
    combo.init(opponent,{0,0,1000});
    fnd::input::PlayerState input;
    input.down[fnd::input::Action::Up] = true;
    const float walkStart = fighter.position().z;
    tick(fighter,input,&opponent);
    check(std::abs(fighter.position().z - walkStart - 7.2f) < 1e-4f,"Rena+0 walk uses recovered 7.2 units/update");
    check(fighter.anim_set_index() == combo.moves.first_set_index(10),"walk still binds the equipped table's move 10");
    input.down[fnd::input::Action::Up] = false; tick(fighter,input,&opponent);
    input.down[fnd::input::Action::Up] = true;
    const float dashStart = fighter.position().z;
    tick(fighter,input,&opponent);
    check(std::abs(fighter.position().z - dashStart - 17.f) < 1e-4f,"Rena+0 forward dash uses recovered 17 units/update");
    check(fighter.anim_set_index() == combo.moves.first_set_index(20),"dash still binds the equipped table's move 20");
    for (int i = 0; i < 10; ++i) tick(fighter,input,&opponent);
    check(fighter.move_phase() == 1,"dash passes its actual startup period into the gated continuation");
    input.down[fnd::input::Action::Up] = false; tick(fighter,input,&opponent);
    check(fighter.move_phase() == 2,"release, not a fixed twenty-tick timer, starts dash recovery");
    for (int i = 0; i < 100 && fighter.state() != gameplay::FighterState::Idle; ++i) tick(fighter,input,&opponent);
    check(fighter.state() == gameplay::FighterState::Idle,"dash's data period plus recovered hold complete");

    combo.init(fighter);
    input = {}; input.down[fnd::input::Action::AttackA] = true;
    const float start = fighter.position().z;
    tick(fighter,input,&opponent);
    check(fighter.position().z > start,"neutral attack applies its original approach displacement");
    check(!fighter.melee_in_active() && fighter.move_phase() == 0,"combat cannot borrow phase two's frame four during startup");
    input.down[fnd::input::Action::AttackA] = false;
    bool active = false, ribbon = false;
    for (int i = 0; i < 150 && fighter.state() == gameplay::FighterState::AttackA; ++i) {
        tick(fighter,input,&opponent);
        ribbon |= fighter.trail(0).triangles() > 0;
        // The melee rows carry no FUN_00434a70 clear, so the weapon must stay in hand for
        // the whole swing — only the throw moves detach it (checked in launch_rules).
        check(fighter.weapon_slot_bound(0),"the swung weapon stays bound through the neutral chain");
        if (!fighter.melee_in_active()) continue;
        active = true;
        check(fighter.move_phase() == 2,"neutral combat comes from phase two's current record");
        const auto* record = fighter.current_move_record();
        check(record && record->boneName == "Bip01_Prop1","active collision resolves the data's weapon bone");
        fighter.note_melee_hit(1);
        for (int delay = 0; delay < 30; ++delay) {
            const auto* current = fighter.current_move_record();
            if (current && (current->stateFlags & 0x100)) break;
            tick(fighter,input,&opponent);
        }
        input.down[fnd::input::Action::AttackA] = true;
        tick(fighter,input,&opponent);
        check(fighter.attack_move_id() == 301,"second press compares cancel threshold to row 301 priority");
        check(fighter.action_camera() == 2,"contact survives the chain bind and selects action camera two");
        break;
    }
    check(active,"actual .X periods reach the neutral combat record");
    check(ribbon,"phase-local trail events generate ribbon geometry");
    input.down[fnd::input::Action::AttackA] = false;
    bool chainedThird = false;
    for (int i = 0; i < 100 && fighter.state() == gameplay::FighterState::AttackA; ++i) {
        tick(fighter,input,&opponent);
        const auto* record = fighter.current_move_record();
        if (!record || !(record->stateFlags & 0x100)) continue;
        input.down[fnd::input::Action::AttackA] = true;
        tick(fighter,input,&opponent);
        chainedThird = fighter.attack_move_id() == 302;
        break;
    }
    check(chainedThird,"third press selects row 302, not directional kick 311");
}

void shots(const Combo& combo) {
    for (int tier = 0; tier < 3; ++tier) {
        gameplay::Fighter fighter;
        combo.init(fighter);
        fnd::input::PlayerState input;
        input.down[fnd::input::Action::Shoot] = true;
        const int hold = tier == 0 ? 1 : tier == 1 ? 80 : 200;
        for (int i = 0; i < hold; ++i) tick(fighter,input);
        input.down[fnd::input::Action::Shoot] = false;
        tick(fighter,input);
        check(!fighter.take_pending_shot().armed,"release selects an animation; it does not fire immediately");
        std::vector<int> rows;
        for (int i = 0; i < 150; ++i) {
            tick(fighter,input);
            for (auto shot = fighter.take_pending_shot(); shot.armed; shot = fighter.take_pending_shot())
                rows.push_back(shot.bulletRow);
            if (!rows.empty()) break;
        }
        const std::vector<int> expected = tier == 0 ? std::vector<int>{0} : tier == 1 ? std::vector<int>{2} : std::vector<int>{11,12};
        check(rows == expected,"Rena+0 tier " + std::to_string(tier) + " launches exact item rows");
        for (int row : rows) {
            check(combo.hasBullet[static_cast<size_t>(row)],"launched row retains its own parameter variant");
            const std::string name = tier == 0 ? "03.X" : tier == 1 ? "05.X" : "09.X";
            check(combo.bullets[static_cast<size_t>(row)].modelName == name,"launched row " + std::to_string(row) + " draws " + combo.bullets[static_cast<size_t>(row)].modelName + " (expected " + name + ")");
        }
    }
}

// The move program a shot plays comes from the equipped table, so the launches below are
// read off the fighter's real output instead of repeating the table's own numbers: a
// launch whose position no rule matches is exactly the transcription error these catch.
void launch_rules(const Combo& combo) {
    struct Case { gameplay::ShotTier tier; int hold; bool airborne; int expectedTick;
                  int expectedRow; bool detaches; const char* label; };
    const Case cases[] = {
        {gameplay::ShotTier::Tap,     1, false, 12, 0, true,  "Rena+0 ground tap"},
        {gameplay::ShotTier::Tap,     1, true,  13, 1, true,  "Rena+0 air tap"},
        {gameplay::ShotTier::Yellow, 80, false, 13, 2, false, "Rena+0 first charge"},
        // The airborne charged move 460 is NOT reachable with this combo: Rena 0's own
        // magazine charges yellow at 0.9375 s, longer than the leap, so the whole charge
        // window fits inside an airtime only as a partial one and the release fires the
        // tap tier. This case asserts the airborne launch against whichever move actually
        // bound, which is what catches a transcription error like the air tap firing a
        // tick early. 460's own rule is checked against the table below.
        {gameplay::ShotTier::Yellow, 40, true,  13, 1, true,  "Rena+0 airborne release"},
    };
    for (const Case& test : cases) {
        gameplay::Fighter fighter;
        combo.init(fighter);
        fnd::input::PlayerState input;
        gameplay::Fighter opponent;
        gameplay::Fighter* foe = nullptr;
        if (test.airborne) {
            // An air shot is RELEASED airborne, so the jump precedes the charge: a
            // grounded release binds the ground move and the fixture never fires aloft.
            combo.init(opponent,{0,0,300});
            foe = &opponent;
            // A bare fixture never leaves the count-in pose, so put the fighter in a
            // state that can act before asking it to jump (the other cases here do the
            // same rather than waiting on a match's BattleStart handover).
            fighter.set_state(gameplay::FighterState::Idle);
            input.down[fnd::input::Action::Jump] = true;
            tick(fighter,input,foe);
            input.down[fnd::input::Action::Jump] = false;
            for (int i = 0; i < 12 && fighter.state() != gameplay::FighterState::Jump; ++i)
                tick(fighter,input,foe);
            if (fighter.state() != gameplay::FighterState::Jump) {
                check(false,std::string(test.label) + " fixture left the ground");
                continue;
            }
        }
        input.down[fnd::input::Action::Shoot] = true;
        for (int i = 0; i < test.hold; ++i) tick(fighter,input,foe);
        const gameplay::ShotTier released = fighter.charge_tier();
        input.down[fnd::input::Action::Shoot] = false;
        tick(fighter,input,foe);
        if (test.airborne && test.tier != gameplay::ShotTier::Tap)
            check(released == gameplay::ShotTier::Tap,
                  std::string(test.label) + " cannot build a charge inside the leap");
        else
            check(released == test.tier,std::string(test.label) + " holds long enough for its tier");
        if (test.airborne && !fighter.airborne()) {
            check(false,std::string(test.label) + " fixture released while still airborne");
            continue;
        }
        int fired = -1, row = -1, phase = -1, move = -1;
        // The move binds on the release tick and the clock advances at the end of that
        // same update, so the first tick a rule can see carries phase_elapsed() == 2 and
        // rule tick N is evaluated while phase_elapsed() == N+1. This is the same clock
        // Fighter::execute_move_program matches rules against, not a test-side constant.
        for (auto shot = fighter.take_pending_shot(); shot.armed; shot = fighter.take_pending_shot()) {}
        for (int frame = 0; frame < 80 && row < 0; ++frame) {
            tick(fighter,input,foe);
            for (auto shot = fighter.take_pending_shot(); shot.armed; shot = fighter.take_pending_shot()) {
                fired = fighter.phase_elapsed() - 1;
                row = shot.bulletRow; phase = fighter.move_phase();
                move = fighter.shot_move_id();
                break;
            }
        }
        check(row == test.expectedRow,std::string(test.label) + " launches its recovered item row");
        check(fired == test.expectedTick,
              std::string(test.label) + " launches on the recovered tick " +
              std::to_string(test.expectedTick) + " (observed " + std::to_string(fired) + ")");
        bool matched = false;
        for (const auto& rule : gameplay::kRenaRules)
            matched |= rule.move == move && rule.operation == gameplay::MoveOp::Launch &&
                       rule.first <= fired && fired <= rule.last &&
                       static_cast<int>(rule.value) == test.expectedRow &&
                       (rule.phase < 0 || rule.phase == phase);
        check(matched,std::string(test.label) + " launch matches a rule at its own move/phase/tick");
        // The hide pair belongs to 400 (tick 12) and 402 (tick 13) only: 450 and 460 have
        // no FUN_00434a70 call in their case bodies, so their attachment stays bound and
        // the grenade leaves the muzzle anchor instead. Requiring a detach everywhere was
        // assuming a rule the assembly does not contain.
        const bool detached = !fighter.weapon_slot_bound(0) && !fighter.weapon_slot_bound(1);
        check(detached == test.detaches,
              std::string(test.label) + (test.detaches ? " has detached its attachments"
                                                       : " keeps its attachment")
                  + " at the launch tick");
    }
    // The second charge is the one whose ten-update hold sits in PHASE TWO tick 13,
    // inside the same phase-2 branch as its two tick-2 red launches; a hold left in
    // phase 0 froze the startup instead of the throw.
    gameplay::Fighter charged;
    combo.init(charged);
    fnd::input::PlayerState held;
    held.down[fnd::input::Action::Shoot] = true;
    for (int i = 0; i < 200; ++i) tick(charged,held);
    held.down[fnd::input::Action::Shoot] = false;
    tick(charged,held);
    for (int frame = 0; frame < 40 && charged.state() != gameplay::FighterState::ShootC; ++frame)
        tick(charged,held);
    check(charged.state() == gameplay::FighterState::ShootC,"Rena+0 second charge plays a shoot move");
    bool launches = false;
    for (int frame = 0; frame < 60; ++frame) {
        const int phase = charged.move_phase();
        tick(charged,held);
        for (auto shot = charged.take_pending_shot(); shot.armed; shot = charged.take_pending_shot())
            if (shot.bulletRow == 11 || shot.bulletRow == 12) {
                launches = true;
                check(phase == 2,"Rena+0 second charge throws its natas from phase two");
            }
        if (launches) break;
    }
    check(launches == false || charged.phase_elapsed() <= 3,
          "Rena+0 second charge reaches its red launches by phase two tick two");
    // Move 460 is a real row in the table even though this combo cannot charge inside a
    // leap: assert the recovered tick directly instead of inventing a fixture.
    bool airCharge = false;
    for (const auto& rule : gameplay::kRenaRules)
        airCharge |= rule.move == 460 && rule.operation == gameplay::MoveOp::Launch &&
                     rule.first == 12 && rule.last == 12;
    check(airCharge,"air charge 460 launches row 2 on tick twelve in the recovered table");
}

// The projectile half of the same gate: the shot's own record must pass through the
// volume test and resolve with zero HP. A shipped row is reshaped to zero power and the
// real collision runs, so restoring the old predicate (the record stops being checked) or
// the old clamp (1 HP lands) both fail here.
void zero_power_projectile(const Combo& combo) {
    gameplay::Fighter owner, victim;
    combo.init(owner);
    combo.init(victim, {0, 0, 40});
    gameplay::BulletParameter shot = combo.bullets[0];
    check(!shot.phases.empty() && shot.phases[0].entryCount > 0,
          "Rena+0 tap row carries a phase-0 record to reshape");
    if (shot.phases.empty() || shot.phases[0].entryCount == 0) return;
    gameplay::MoveEntry& rec = shot.phases[0].entries[0];
    rec.combat[0] = 0;                 // power 0
    rec.baseDamage = 0;
    rec.defenderHitstun = 7;           // distinct from the shared default
    rec.combat[10] = 7;
    rec.reactionMove = 113;
    rec.combat[13] = 113;
    rec.combat[16] = 30;               // impact effect the contact must report
    rec.hitRadius = 60;                // a volume wide enough to guarantee the contact
    // The parser also publishes the first record's columns as scalar aliases, and the shot
    // spawn reads those (shot_params_for_row -> params.damage/hitRadius), so the reshape
    // has to update them too or the shot keeps the shipped row's numbers.
    shot.baseDamage = 0;
    shot.defenderHitstun = 7;
    shot.impactEffect = 30;
    shot.hitRadius = 60;

    // The pool resolves a shot's parameter through its owner's bound row, so bind the
    // reshaped copy there rather than reaching into the live shot. The model matters too:
    // a shot without one takes the legacy XZ fallback (projectile.cpp:185) and never reads
    // the record at all, which would make this test prove nothing.
    owner.set_bullet_row(0, &shot);
    std::vector<uint8_t> modelBytes;
    const std::string modelPath = "data/bullet/001/" + shot.modelName;
    check(read(modelPath, modelBytes), "the tap row's own bullet model loads");
    if (modelBytes.empty()) return;
    xm::Model shotModel = xm::loadMemory(modelBytes.data(), modelBytes.size());
    owner.set_bullet_model(0, &shotModel);
    gameplay::ProjectilePool pool;
    check(pool.spawn(victim.position() - glm::vec3(0, 0, 30), {0, 0, 1},
                     gameplay::ShotTier::Tap, &owner, 0),
          "the reshaped shot allocates");
    const int hpBefore = victim.hp();
    const int takenBefore = victim.stats().damageTaken;
    pool.update(1.0 / 64.0, &victim, 1, nullptr, nullptr);
    check(victim.hp() == hpBefore, "a zero-power projectile takes no HP");
    check(victim.stats().damageTaken == 0, "and records no damage taken");
    check(pool.contact_count() > 0, "while still reporting a contact");
    if (pool.contact_count() > 0)
        check(pool.contact(0).effect == 30,
              "carrying the record's own impact effect");
    check(victim.state() == gameplay::FighterState::Hit,
          "and the zero-power projectile still stuns its victim");
    int stunned = 1;
    fnd::input::PlayerState idle;
    while (victim.state() == gameplay::FighterState::Hit && stunned < 200) {
        tick(victim, idle, nullptr);
        ++stunned;
    }
    check(stunned == rec.defenderHitstun + 1,
          "for the record's own defender hitstop (" + std::to_string(stunned) + " frames)");
}

void projectile_clocks(const Combo& combo) {
    gameplay::Fighter owner;
    combo.init(owner);
    std::array<std::unique_ptr<xm::Model>,64> models;
    for (int row : {0,2,3,5,11,12,17}) {
        std::vector<uint8_t> bytes;
        const std::string path = "data/bullet/001/" + combo.bullets[static_cast<size_t>(row)].modelName;
        check(read(path,bytes),"Rena+0 projectile row " + std::to_string(row) + " rig loads");
        if (bytes.empty()) continue;
        models[static_cast<size_t>(row)] = std::make_unique<xm::Model>(xm::loadMemory(bytes.data(),bytes.size()));
        owner.set_bullet_model(row,models[static_cast<size_t>(row)].get());
    }
    gameplay::ProjectilePool pool;
    check(pool.spawn({0,0,0},{0,0,1},gameplay::ShotTier::Tap,&owner,0),"exact tap row allocates");
    pool.update(1./64.,nullptr,0,nullptr,nullptr);
    check(std::abs(pool.shots()[0].pos.z-37.5f) < 1e-4f,"nata speed is 37.5 per original update, not shared tier tuning");
    check(pool.spawn({100,0,0},{0,0,1},gameplay::ShotTier::Tap,&owner,0),"second tap has its own instance");
    pool.update(1./64.,nullptr,0,nullptr,nullptr);
    check(pool.shots()[0].elapsed == 2 && pool.shots()[1].elapsed == 1,
          "same-row simultaneous shots retain independent pose clocks");
    check(pool.shots()[0].record() == combo.bullets[0].phases[0].record_at(2),
          "projectile collision selects the current variant record");
    check(pool.spawn({200,0,0},{0,0,1},gameplay::ShotTier::Tap,&owner,0) &&
          pool.spawn({300,0,0},{0,0,1},gameplay::ShotTier::Tap,&owner,0) &&
          !pool.spawn({400,0,0},{0,0,1},gameplay::ShotTier::Tap,&owner,0),
          "row capacity four limits live instances, not a four-projectile volley");
    pool.clear();
    pool.spawn({0,0,0},{0,0,1},gameplay::ShotTier::Yellow,&owner,2);
    pool.update(1./64.,nullptr,0,nullptr,nullptr);
    pool.update(1./64.,nullptr,0,nullptr,nullptr);
    check(std::abs(pool.shots()[0].pos.z-50.f)<1e-4f && std::abs(pool.shots()[0].pos.y-9.7f)<1e-4f,
          "grenade uses its own speed, delayed vertical launch and gravity");
    pool.clear();
    pool.spawn({0,0,0},{0,0,1},gameplay::ShotTier::Red,&owner,11);
    pool.update(1./64.,nullptr,0,nullptr,nullptr);
    check(pool.live_shots() == 2 && pool.shots()[1].bulletRow == 17 && pool.shots()[1].elapsed == 0,
          "red nata emits exact secondary trail row 17, with a newborn independent clock");
    const glm::vec3 trailPosition = pool.shots()[1].pos;
    pool.update(1./64.,nullptr,0,nullptr,nullptr);
    check(pool.shots()[1].pos == trailPosition,"secondary trail is stationary, not a guessed moving projectile");
    bool finite = true;
    const auto matrix = pool.shots()[1].model_matrix();
    for (int col=0; col<4; ++col) for (int row=0; row<4; ++row) finite &= std::isfinite(matrix[col][row]);
    check(finite,"zero-speed trail retains its launch direction and finite model rotation");
    pool.update(1./64.,nullptr,0,nullptr,nullptr);
    check(pool.live_shots() == 3,"red secondary emissions repeat every two original updates");

    gameplay::Fighter victim;
    combo.init(victim);
    const auto chest = victim.hitbox_debug().anchors[1];
    pool.clear();
    pool.spawn(chest-glm::vec3(0,0,37.5f),{0,0,1},gameplay::ShotTier::Tap,&owner,0);
    pool.update(1./64.,&victim,1,nullptr,nullptr);
    check(victim.hp()<victim.max_hp() && pool.shots()[0].alive,
          "normal nata contact spends a victim allowance without consuming the projectile");
    const int tapHp = victim.hp();
    pool.update(1./64.,&victim,1,nullptr,nullptr);
    check(victim.hp()==tapHp,"normal nata cannot damage the same victim twice");

    combo.init(victim);
    pool.clear();
    pool.spawn(victim.hitbox_debug().anchors[1]-glm::vec3(0,0,45.f),{0,0,1},
               gameplay::ShotTier::Red,&owner,11);
    pool.update(1./64.,&victim,1,nullptr,nullptr);
    const auto contactPosition = pool.shots()[0].pos;
    const int contactAge = pool.shots()[0].elapsed;
    check(victim.hp()<victim.max_hp() && pool.shots()[0].contactPending,
          "red nata records contact for its executable pause policy");
    for (int i=0; i<5; ++i) pool.update(1./64.,nullptr,0,nullptr,nullptr);
    check(pool.shots()[0].pos==contactPosition && pool.shots()[0].elapsed==contactAge,
          "red nata's first five contact updates freeze movement and its record clock");
    pool.update(1./64.,nullptr,0,nullptr,nullptr);
    check(std::abs(pool.shots()[0].pos.z-contactPosition.z-60.f)<1e-4f &&
          pool.shots()[0].hitsRemaining[0]==4 && !pool.shots()[0].contactPending,
          "red nata resumes at sixty units/update, retaining its five-hit victim budget");
}
} // namespace

int main() {
    records();
    const std::string path = install();
    if (path.empty() || !fnd::assets::assetSource().openInstall(path)) {
        std::printf("SKIP: shipped combo checks require daybreak bundles; %d hermetic checks\n",checks);
        return failures ? 1 : 0;
    }
    roster();
    auto rena = std::make_unique<Combo>();
    std::string error;
    const bool loaded = rena->load(0,0,error);
    check(loaded,"Rena+0 actual move/item/rig fixture loads");
    if (loaded) {
        aerial_attack(*rena);
        execution(*rena);
        zero_power_contact();
        zero_power_projectile(*rena);
        shots(*rena);
        launch_rules(*rena);
        projectile_clocks(*rena);
    }
    std::printf("ANIMATION_DATA: %d checks, %d failures\n",checks,failures);
    return failures ? 1 : 0;
}
