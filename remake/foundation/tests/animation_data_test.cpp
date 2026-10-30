// FUN_0041e180 / FUN_0043ffc0 / FUN_005f8510: parser and execution regressions.
// Bundle-winning bytes, equipped item and the actual .X periods travel together.
#include "assets/asset_source.h"
#include "assets/cnv.h"
#include "assets/xmodel.h"
#include "game/fx_cards.h"
#include "game/shot_visual.h"
#include "gameplay/fighter.h"
#include "gameplay/fixed_step.h"
#include "gameplay/match.h"
#include "gameplay/move_behavior.h"
#include "gameplay/projectile_behavior.h"
#include "combo_fixture.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <memory>

namespace {
int checks = 0, failures = 0;
int gatedTimelineCharacter = -1, gatedTimelineWeapon = -1, gatedTimelineMove = -1;
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

// One effect card as the game would load it (the bundles carry the .X; the texture resolves
// beside it). Returns null when the install does not ship the file.
std::unique_ptr<xm::Model> read_card_model(const std::string& path) {
    std::vector<uint8_t> bytes;
    if (!read(path, bytes) || bytes.empty()) return nullptr;
    try {
        return std::make_unique<xm::Model>(xm::loadMemory(bytes.data(), bytes.size()));
    } catch (const std::exception&) {
        return nullptr;
    }
}

using Combo = test::Combo;

void tick(gameplay::Fighter& fighter, fnd::input::PlayerState& input, gameplay::Fighter* opponent = nullptr) {
    fnd::input::compute_edges(input);
    fighter.update(&input,opponent,gameplay::FixedStep::seconds);
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
    check(vertices[0].uv.x == 0.f && vertices[0].uv.y == 0.f &&
          vertices[1].uv.x == 1.f && vertices[1].uv.y == 0.f &&
          vertices[gameplay::WeaponTrail::kVertices - 1].uv.x == 1.f &&
          vertices[gameplay::WeaponTrail::kVertices - 1].uv.y == 1.f,
          "ribbon texture keeps U at the outer edge and advances V along the trail");
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
            if (gatedTimelineCharacter < 0) {
                for (int candidate : {300,311,330}) {
                    const auto* move = combo->moves.find(candidate);
                    if (!move) continue;
                    for (int phase = 0; phase < move->sectionCount; ++phase) {
                        const int set = move->phase_set_index(phase);
                        if (set >= 0 && combo->moves.animation_set_phase_gate(set) != 0) {
                            gatedTimelineCharacter = character;
                            gatedTimelineWeapon = slot;
                            gatedTimelineMove = candidate;
                            break;
                        }
                    }
                    if (gatedTimelineCharacter >= 0) break;
                }
            }
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

void air_attack_route(const Combo& combo, const char* label, bool afterAirDash,
                      fnd::input::Action dashDirection,
                      fnd::input::Action attackDirection,
                      float targetBearingAfterDash, bool analogBack = false,
                      bool checkTravel = false) {
    constexpr float kFarTarget = 1000.f;
    const float initialActorFacing = glm::half_pi<float>();
    gameplay::Fighter fighter, opponent;
    combo.init(fighter,{},initialActorFacing);
    combo.init(opponent,{0.f,0.f,kFarTarget});

    // Leave the lock unbound during takeoff so this fixture's visible body yaw is
    // deliberately different from the later target bearing.
    fnd::input::PlayerState input;
    input.down[fnd::input::Action::Jump] = true;
    tick(fighter,input);
    input.down[fnd::input::Action::Jump] = false;
    tick(fighter,input);
    check(fighter.airborne(),std::string(label) + " jumps before the attack input");

    if (afterAirDash) {
        input.down[dashDirection] = true;
        tick(fighter,input,&opponent);
        input.down[dashDirection] = false;
        tick(fighter,input,&opponent);
        input.down[dashDirection] = true;
        tick(fighter,input,&opponent);
        check(fighter.state() == gameplay::FighterState::Run,
              std::string(label) + " reaches Run through a real airborne double tap");
        input.down[dashDirection] = false;
        tick(fighter,input,&opponent);

        // Move the lock only after the dash commits. The selector and the attack-time
        // facing rule must use this live bearing, while Back keeps the body's actual yaw.
        const glm::vec3 offset(std::sin(targetBearingAfterDash) * kFarTarget,0.f,
                               std::cos(targetBearingAfterDash) * kFarTarget);
        opponent.reset(fighter.position() + offset,0.f);
    }

    const float actorYawAtAttack = fighter.facing_yaw();
    const glm::vec3 toTarget = opponent.position() - fighter.position();
    const float lockedYaw = std::atan2(toTarget.x,toTarget.z);
    const bool backHeld = analogBack || attackDirection == fnd::input::Action::Down;
    if (analogBack) input.stick_y = 16000; // SDL's positive Y is the Back half of the stick.
    else input.down[attackDirection] = true;
    const glm::vec3 beforeAttack = fighter.position();
    input.down[fnd::input::Action::AttackA] = true;
    tick(fighter,input,&opponent);

    const int expectedMove = afterAirDash ? 332 : 320;
    const std::string prefix = std::string(label) + ": ";
    check(fighter.state() == gameplay::FighterState::AttackA &&
          fighter.attack_move_id() == expectedMove,
          prefix + (afterAirDash ? "air-dash attack binds source row 332 (visual check separate)" :
                                   "ordinary jump attack binds row320; visual identity and timing checked separately"));
    check(fighter.anim_set_index() == combo.moves.first_set_index(expectedMove) &&
          !fighter.anim_fallback(),
          prefix + "plays this equipped combo's first move tag without set-0 fallback");
    check(fighter.aerial_attack(),prefix + "records this swing as aerial");

    const float expectedYaw = backHeld ? actorYawAtAttack : lockedYaw;
    const float yawAfterEntry = fighter.pose().facingYaw;
    check(std::abs(std::remainder(yawAfterEntry - expectedYaw,glm::two_pi<float>())) < 1e-4f,
          prefix + (backHeld ? "Back keeps the actor's visible yaw at attack entry" :
                               "Forward/side faces the currently locked target at attack entry"));

    const bool hasRena0Approach = combo.moves.character_index() == 0 &&
        gameplay::weaponSlotForItem(combo.moves.character_index(),combo.moves.weapon_id()) == 0;
    if (checkTravel && hasRena0Approach && expectedMove == 300) {
        const glm::vec3 delta = fighter.position() - beforeAttack;
        const glm::vec3 horizontal(delta.x,0.f,delta.z);
        const glm::vec3 expectedForward(std::sin(expectedYaw),0.f,std::cos(expectedYaw));
        check(glm::length(horizontal) > 0.1f &&
              glm::dot(glm::normalize(horizontal),expectedForward) > 0.999f,
              prefix + "move 300's first attack step travels along its selected facing basis");
    }

    bool heldThroughHandlerTicks = true;
    int protectedTicks = 0;
    for (int frame = 0; frame < 6 && fighter.state() == gameplay::FighterState::AttackA;
         ++frame) {
        tick(fighter,input,&opponent);
        ++protectedTicks;
        heldThroughHandlerTicks &=
            std::abs(std::remainder(fighter.pose().facingYaw - expectedYaw,
                                    glm::two_pi<float>())) < 1e-4f;
    }
    check(protectedTicks >= 2,
          prefix + "keeps the selected move active while its direction is checked");
    check(heldThroughHandlerTicks,
          prefix + (backHeld ? "move Turn rules do not override Back's actor-facing basis" :
                               "move Turn rules preserve the target-facing attack basis"));
    if (checkTravel && hasRena0Approach) {
        for (int frame = 0; frame < 180 && fighter.state() == gameplay::FighterState::AttackA;
             ++frame)
            tick(fighter,input,&opponent);
        check(fighter.state() != gameplay::FighterState::AttackA && !fighter.aerial_attack(),
              prefix + "clears the per-swing aerial-facing mode when the attack ends");
    }
}

// User-confirmed #31 contract, checked with real per-combo NN.dat, rig and item rows:
// Rena+0 ordinary Jump→Attack binds row320; after airborne dash it binds332.
// Live user inspection confirmed the slash/kick poses, but rejected slash timing. Attack-time Back follows the visible actor yaw, while
// forward/side use the current lock, independent of the dash's initiating direction.
void air_attack_facing_persistence(const Combo& combo, const char* label) {
    gameplay::Fighter fighter, opponent;
    combo.init(fighter,{},glm::half_pi<float>());
    combo.init(opponent,{0.f,0.f,1000.f});
    fighter.set_state(gameplay::FighterState::Idle);
    fnd::input::PlayerState input;
    input.down[fnd::input::Action::Jump] = true;
    tick(fighter,input);
    input.down[fnd::input::Action::Jump] = false;
    tick(fighter,input);
    input.down[fnd::input::Action::Down] = true;
    input.down[fnd::input::Action::AttackA] = true;
    tick(fighter,input,&opponent);
    check(fighter.state() == gameplay::FighterState::AttackA &&
          fighter.attack_move_id() == 320 && fighter.aerial_attack(),
          std::string(label) + ": Back attack enters the aerial slash");
    const float backFacing = fighter.facing_yaw();
    check(std::abs(std::remainder(backFacing-glm::half_pi<float>(),glm::two_pi<float>())) < 1e-4f,
          std::string(label) + ": Back keeps the pre-attack actor yaw");
    input.down[fnd::input::Action::Down] = false;
    input.down[fnd::input::Action::AttackA] = false;
    bool landed = false;
    for (int i = 0; i < 180 && !!fighter.airborne(); ++i) {
        tick(fighter,input,&opponent);
        landed |= !fighter.airborne();
        if (fighter.state() != gameplay::FighterState::AttackA) break;
    }
    if (!fighter.airborne()) fighter.set_state(gameplay::FighterState::Idle);
    check(landed && fighter.state() != gameplay::FighterState::AttackA &&
          !fighter.aerial_attack(),
          std::string(label) + ": landing and attack exit clear the aerial Back mode");
}

void reset_respawn_clear(const Combo& combo, const char* label) {
    gameplay::Fighter fighter;
    combo.init(fighter);
    fighter.set_state(gameplay::FighterState::Idle);
    fnd::input::PlayerState input;
    input.down[fnd::input::Action::Jump] = true;
    tick(fighter,input);
    input.down[fnd::input::Action::Jump] = false;
    tick(fighter,input);
    input.down[fnd::input::Action::Down] = true;
    input.down[fnd::input::Action::AttackA] = true;
    tick(fighter,input);
    check(fighter.aerial_attack(),std::string(label) + ": aerial swing arms before reset");
    fighter.reset(glm::vec3(1.f,0.f,2.f),0.f);
    check(!fighter.aerial_attack() && fighter.state() == gameplay::FighterState::BattleStart,
          std::string(label) + ": round reset clears aerial swing mode");

    fighter.set_state(gameplay::FighterState::Idle);
    input = {};
    input.down[fnd::input::Action::Jump] = true;
    tick(fighter,input);
    input.down[fnd::input::Action::Jump] = false;
    tick(fighter,input);
    input.down[fnd::input::Action::Down] = true;
    input.down[fnd::input::Action::AttackA] = true;
    tick(fighter,input);
    check(fighter.aerial_attack(),std::string(label) + ": second aerial swing arms before respawn");
    fighter.respawn(glm::vec3(2.f,0.f,3.f),0.f,800.f);
    check(!fighter.aerial_attack() && fighter.state() == gameplay::FighterState::BattleStart,
          std::string(label) + ": respawn clears aerial swing mode");
}

void grounded_attack_after_air(const Combo& combo, const char* label) {
    gameplay::Fighter fighter, opponent;
    combo.init(fighter,{},glm::half_pi<float>());
    combo.init(opponent,{0.f,0.f,1000.f});
    fighter.set_state(gameplay::FighterState::Idle);
    fnd::input::PlayerState input;
    input.down[fnd::input::Action::Jump] = true;
    tick(fighter,input);
    input.down[fnd::input::Action::Jump] = false;
    tick(fighter,input);
    input.down[fnd::input::Action::Down] = true;
    input.down[fnd::input::Action::AttackA] = true;
    tick(fighter,input,&opponent);
    input.down[fnd::input::Action::Down] = false;
    input.down[fnd::input::Action::AttackA] = false;
    bool landed = false;
    for (int i = 0; i < 180; ++i) {
        tick(fighter,input,&opponent);
        landed |= !fighter.airborne();
        if (landed && fighter.state() != gameplay::FighterState::AttackA) break;
    }
    check(landed && !fighter.airborne() && !fighter.aerial_attack(),
          std::string(label) + ": landing clears aerial mode before the next grounded attack");
    fighter.set_state(gameplay::FighterState::Idle);
    input.down[fnd::input::Action::AttackA] = true;
    tick(fighter,input,&opponent);
    check(fighter.state() == gameplay::FighterState::AttackA &&
          fighter.attack_move_id() == 300 && !fighter.aerial_attack(),
          std::string(label) + ": grounded attack retains neutral move 300");
}

void aerial_attack(const Combo& combo, const char* label) {
    air_attack_route(combo,label,false,fnd::input::Action::Up,
                     fnd::input::Action::Down,0.f,false,true);
    air_attack_route(combo,label,false,fnd::input::Action::Up,
                     fnd::input::Action::Up,0.f);
    air_attack_route(combo,label,false,fnd::input::Action::Up,
                     fnd::input::Action::Right,0.f);
    air_attack_route(combo,label,false,fnd::input::Action::Up,
                     fnd::input::Action::Up,0.f,true);
    // Attack-time input, not the historical dash direction, determines Back.
    air_attack_route(combo,label,true,fnd::input::Action::Up,
                     fnd::input::Action::Down,glm::half_pi<float>());
    air_attack_route(combo,label,true,fnd::input::Action::Down,
                     fnd::input::Action::Up,0.f);
    air_attack_route(combo,label,true,fnd::input::Action::Left,
                     fnd::input::Action::Right,-glm::half_pi<float>());
    air_attack_route(combo,label,true,fnd::input::Action::Right,
                     fnd::input::Action::Up,0.f,true);
    air_attack_route(combo,label,true,fnd::input::Action::Up,
                     fnd::input::Action::Left,-glm::half_pi<float>());
    air_attack_facing_persistence(combo,label);
    grounded_attack_after_air(combo,label);
    reset_respawn_clear(combo,label);
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
    // A zero-POWER contact (combat[0] == 0) still carries staggering power, so it interrupts
    // the victim exactly like any other contact — power and stagger are different columns.
    check(victim.state() == gameplay::FighterState::Hit,
          "a zero-power contact still staggers the victim");
    int stunned = 1;
    while (victim.state() == gameplay::FighterState::Hit && stunned < 200) {
        tick(victim, input, nullptr);
        ++stunned;
    }
    check(stunned > 1, "and runs its own stun window");
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

void miss_trail_world_anchors(const Combo& combo) {
    check(combo.weapon.slotCount > 1 && combo.weapon.slots[0].has_prop(),
          "Rena+0 item001 prop0 is an available weapon attachment");
    check(combo.weapon.slotCount > 1 && !combo.weapon.slots[1].has_prop() &&
          !combo.weapon.slots[1].textureName.empty(),
          "Rena+0 item001 prop1 has a texture field but no model/prop availability");
    gameplay::MatchConfig config;
    config.fighterCount = 2;
    const xm::Model* models[2] = {&combo.model, &combo.model};
    xm::Controller* controllers[2] = {combo.controller(), combo.controller()};
    for (int i = 0; i < 2; ++i) {
        config.side[i] = i;
        config.moves[i] = &combo.moves;
        config.weapon[i] = &combo.weapon;
        config.spawn[i] = glm::vec3(0.f, 0.f, i ? 1500.f : 0.f);
    }
    gameplay::Match match;
    match.reset(config, models, controllers, nullptr, nullptr);
    match.economy().setLogFile(nullptr);

    fnd::input::PlayerState input;
    const fnd::input::PlayerState* inputs[2] = {&input, nullptr};
    bool contacted = false;
    bool ribbonOnWhiff = false;
    bool anchorMatch = false;
    int firstRibbonFrame = -1;
    int firstRibbonPhase = -1;
    int firstRibbonElapsed = -1;
    for (int frame = 1; frame <= 120; ++frame) {
        input.down[fnd::input::Action::AttackA] = frame == 62;
        fnd::input::compute_edges(input);
        const gameplay::MatchFrame report = match.step(inputs, gameplay::FixedStep::seconds);
        contacted |= report.meleeHit[0];

        const gameplay::Fighter& attacker = match.fighter(0);
        const gameplay::WeaponTrail& ribbon = attacker.trail(0);
        if (ribbon.triangles() <= 0 || report.meleeHit[0]) continue;
        ribbonOnWhiff = true;
        if (firstRibbonFrame < 0) {
            firstRibbonFrame = frame;
            firstRibbonPhase = attacker.move_phase();
            firstRibbonElapsed = attacker.phase_elapsed();
        }

        // FUN_00430120 transforms the equipped item's prop-local root/tip through
        // the posed Prop1 frame. Rebuild that path from the controller and matrices
        // independently of Fighter::bone_point, then compare it with the dynamic
        // mesh's world-space endpoints.
        const int propFrame = combo.model.findFrame("Bip01_Prop1");
        if (propFrame < 0) continue;
        std::vector<glm::mat4> posed;
        controllers[0]->evalWorld(posed);
        if (static_cast<size_t>(propFrame) >= posed.size()) continue;
        const auto& slot = combo.weapon.slots[0];
        const glm::vec3 rootLocal(slot.ribbonRoot[0], slot.ribbonRoot[1], slot.ribbonRoot[2]);
        const glm::vec3 tipLocal(slot.ribbonTip[0], slot.ribbonTip[1], slot.ribbonTip[2]);
        const glm::mat4 actorWorld = attacker.modelMatrix();
        const glm::vec3 expectedRoot = glm::vec3(actorWorld * posed[static_cast<size_t>(propFrame)] *
                                                  glm::vec4(rootLocal, 1.f));
        const glm::vec3 expectedTip = glm::vec3(actorWorld * posed[static_cast<size_t>(propFrame)] *
                                                 glm::vec4(tipLocal, 1.f));
        const auto vertices = ribbon.vertices();
        if (glm::length(vertices[0].pos - expectedRoot) < 1e-3f &&
            glm::length(vertices[1].pos - expectedTip) < 1e-3f)
            anchorMatch = true;
    }
    check(!contacted && match.fighter(0).swing_hit_count() == 0,
          "Rena+0 move 300 stays a whiff with the dummy outside its reach");
    check(ribbonOnWhiff,
          "Rena+0 move 300 activates its weapon ribbon without a melee contact");
    check(firstRibbonFrame == 87 && firstRibbonPhase == 2 && firstRibbonElapsed == 4,
          "Rena+0 miss ribbon begins at move300 phase2 source tick3 (post-step tick4)");
    check(match.fighter(0).trail(1).triangles() == 0,
          "the texture-only item001 slot cannot generate a phantom second ribbon");
    check(anchorMatch,
          "Rena+0 ribbon endpoints match the posed item anchors in world space");
}

void akane0_trail_windows(const Combo& combo) {
    const auto window = [&](int move, int phase, int tick) {
        return gameplay::trail_window(&combo.moves, move, phase, tick, 0);
    };
    const auto binding = [&](int move) {
        return gameplay::trail_binding(&combo.moves,move,0);
    };
    check(gameplay::comboSlotLabel(13,0) == "Akane 0" && combo.moves.weapon_id() == 16,
          "trail source witness is the bound Akane+0/item016 combo");
    check(combo.weapon.slotCount > 2 && combo.weapon.slots[2].has_prop(),
          "Akane+0 item016 model 2 is a real mesh-backed prop");
    check(binding(300) && binding(300)->itemModel == 2 &&
          window(300,2,3) && window(300,2,10) && !window(300,2,11) &&
          window(300,2,10)->propSlot == 0,
          "Akane+0 move300 binds Prop0<-item2 throughout, active phase2 ticks3..10");
    check(binding(301) && binding(301)->itemModel == 2 &&
          window(301,0,10) && window(301,0,16) && !window(301,0,17),
          "Akane+0 source move301 ribbon window is ticks10..16");
    check(binding(302) && binding(302)->itemModel == 2 &&
          window(302,0,10) && window(302,0,13) && !window(302,0,14),
          "Akane+0 source move302 ribbon window is ticks10..13");
    check(binding(330) && binding(330)->itemModel == 2 &&
          window(330,2,10) && window(330,2,15) && !window(330,2,16),
          "Akane+0 move330 ribbon window is phase2 ticks10..15");
    check(binding(331) && binding(331)->itemModel == 2 &&
          window(331,2,7) && window(331,2,16) && !window(331,2,17),
          "Akane+0 source move331 ribbon window is phase2 ticks7..16");
    check(binding(340) && binding(340)->itemModel == 2 &&
          window(340,0,16) && window(340,0,24) && !window(340,0,25),
          "Akane+0 move340 ribbon window is ticks16..24");
    check(binding(341) && binding(341)->itemModel == 2 &&
          window(341,0,17) && window(341,0,19) && !window(341,0,20),
          "Akane+0 source move341 ribbon window is ticks17..19");
    check(gameplay::trail_window(&combo.moves,300,1,3,0) == nullptr &&
          gameplay::trail_window(&combo.moves,300,2,3,1) == nullptr,
          "Akane+0 trail descriptor rejects wrong phase and wrong manager prop slot");
}

void akane0_miss_trail(const Combo& combo, int expectedMove, const char* label) {
    gameplay::MatchConfig config;
    config.fighterCount = 2;
    const xm::Model* models[2] = {&combo.model, &combo.model};
    xm::Controller* controllers[2] = {combo.controller(), combo.controller()};
    for (int i = 0; i < 2; ++i) {
        config.side[i] = i;
        config.moves[i] = &combo.moves;
        config.weapon[i] = &combo.weapon;
        config.spawn[i] = glm::vec3(0.f, 0.f, i ? 1500.f : 0.f);
    }
    gameplay::Match match;
    match.reset(config, models, controllers, nullptr, nullptr);
    match.economy().setLogFile(nullptr);
    fnd::input::PlayerState input;
    const fnd::input::PlayerState* inputs[2] = {&input, nullptr};
    bool sourcePeriodTimeline = combo.model.ticksPerSecond > 0.f;
    int periodBudget = 0;
    const auto* attack = combo.moves.find(expectedMove);
    if (!attack) sourcePeriodTimeline = false;
    if (attack) for (int phase = 0; phase < attack->sectionCount; ++phase) {
        const int set = attack->phase_set_index(phase);
        if (set < 0 || static_cast<size_t>(set) >= combo.model.anims.size() ||
            combo.moves.animation_set_phase_gate(set) != 0) {
            sourcePeriodTimeline = false;
            continue;
        }
        const float duration = combo.model.anims[static_cast<size_t>(set)].duration;
        if (!std::isfinite(duration) || duration < 0.f) {
            sourcePeriodTimeline = false;
            continue;
        }
        const int period = static_cast<int>(std::nearbyint(
            duration / combo.model.ticksPerSecond / gameplay::kOriginalAnimationTick));
        periodBudget += period + 1;
    }
    gameplay::Fighter lifetimeFixture;
    combo.init(lifetimeFixture);
    const auto contactTimer = lifetimeFixture.preview_melee_swing(
        expectedMove == 311 || expectedMove == 330,
        expectedMove == 311).total_ticks();
    const int expectedLifetime = sourcePeriodTimeline ? periodBudget : contactTimer;
    bool selected = false;
    bool contacted = false;
    bool active = false;
    bool correctItem = false;
    bool decayUsesBoundModel = false;
    bool anchorMatch = false;
    bool havePreviousBoundTip = false;
    glm::vec3 previousBoundTip(0.f);
    int boundTipChanges = 0;
    int firstTrailTipChanges = -1;
    bool sawAttack = false;
    bool released = false;
    int firstFrame = -1;
    int firstPhase = -1;
    int firstTick = -1;
    int releaseFrame = -1;
    for (int frame = 1; frame <= 300; ++frame) {
        input.down[fnd::input::Action::AttackA] =
            expectedMove == 300 ? frame == 62 : false;
        input.down[fnd::input::Action::Up] =
            expectedMove == 330 && (frame == 62 || frame == 64);
        input.down[fnd::input::Action::Jump] =
            expectedMove == 340 && frame == 62;
        if (expectedMove == 330 && frame == 65)
            input.down[fnd::input::Action::AttackA] = true;
        if (expectedMove == 340 && frame == 71)
            input.down[fnd::input::Action::AttackA] = true;
        fnd::input::compute_edges(input);
        const gameplay::MatchFrame report = match.step(inputs, gameplay::FixedStep::seconds);
        contacted |= report.meleeHit[0];
        const auto& attacker = match.fighter(0);
        const bool inExpectedAttack = attacker.state() == gameplay::FighterState::AttackA &&
                                      attacker.attack_move_id() == expectedMove;
        selected |= inExpectedAttack;
        sawAttack |= inExpectedAttack;
        if (sawAttack && !inExpectedAttack && releaseFrame < 0) {
            released = true;
            releaseFrame = frame;
        }
        glm::vec3 expectedRoot(0.f), expectedTip(0.f);
        bool anchorsValid = false;
        const int propFrame = combo.model.findFrame("Bip01_Prop1");
        if (inExpectedAttack && propFrame >= 0) {
            std::vector<glm::mat4> posed;
            controllers[0]->evalWorld(posed);
            if (static_cast<size_t>(propFrame) < posed.size()) {
                const auto& slot = combo.weapon.slots[2];
                const glm::vec3 root(slot.ribbonRoot[0],slot.ribbonRoot[1],slot.ribbonRoot[2]);
                const glm::vec3 tip(slot.ribbonTip[0],slot.ribbonTip[1],slot.ribbonTip[2]);
                const glm::mat4 boneWorld = attacker.modelMatrix() * posed[static_cast<size_t>(propFrame)];
                expectedRoot = glm::vec3(boneWorld * glm::vec4(root,1.f));
                expectedTip = glm::vec3(boneWorld * glm::vec4(tip,1.f));
                anchorsValid = true;
                if (!havePreviousBoundTip || expectedTip != previousBoundTip)
                    ++boundTipChanges;
                previousBoundTip = expectedTip;
                havePreviousBoundTip = true;
            }
        }
        const auto& ribbon = attacker.trail(0);
        if (attacker.attack_move_id() == expectedMove &&
            attacker.trail_item_model(0) == 2 && ribbon.triangles() > 0 &&
            !gameplay::trail_window(&combo.moves,expectedMove,attacker.move_phase(),
                                   attacker.phase_elapsed(),0))
            decayUsesBoundModel = true;
        if (ribbon.triangles() <= 0 || attacker.trail_item_model(0) != 2) continue;
        active = true;
        correctItem = true;
        if (firstFrame < 0) {
            firstFrame = frame;
            firstPhase = attacker.move_phase();
            firstTick = attacker.phase_elapsed();
            firstTrailTipChanges = boundTipChanges;
        }
        if (!anchorsValid) continue;
        const auto vertices = ribbon.vertices();
        if (glm::length(vertices[0].pos - expectedRoot) < 1e-3f &&
            glm::length(vertices[1].pos - expectedTip) < 1e-3f)
            anchorMatch = true;
    }
    const std::string prefix = std::string(label) + ": ";
    check(selected,prefix + "actual input selects its mapped weapon move " + std::to_string(expectedMove));
    check(!contacted && match.fighter(0).swing_hit_count() == 0,
          prefix + "distant Akane+0 target keeps the swing a miss");
    check(active && correctItem,
          prefix + "source-window ribbon uses prop-manager slot0 and item model2 on a miss");
    check(decayUsesBoundModel,
          prefix + "keeps item-model-2 anchors/texture bound while the inactive ribbon decays");
    check(anchorMatch,
          prefix + "item016 model2 root/tip match the independently posed Prop1 world anchors");
    check(firstTrailTipChanges >= 12,
          prefix + "more than the twelve-sample trail history is refreshed from item-model-2 tips before activation");
    // The source window's frame numbers come from the engine's truncating period rule
    // (animation_period.h): the phase before the ribbon's first active one is one update
    // shorter than nearest-even rounding predicted, so both frames moved down by one and
    // the in-phase tick did not move at all.
    const int expectedFrame = expectedMove == 300 ? 91 : expectedMove == 330 ? 101 : 87;
    const int expectedPhase = expectedMove == 340 ? 0 : 2;
    const int expectedTick = expectedMove == 300 ? 4 : expectedMove == 330 ? 11 : 17;
    check(firstFrame == expectedFrame && firstPhase == expectedPhase && firstTick == expectedTick,
          prefix + "begins on the source window at the expected move frame/phase/tick (" +
              std::to_string(firstFrame) + "/" + std::to_string(firstPhase) + "/" +
              std::to_string(firstTick) + ")");
    check(released,
          prefix + "completes its table-backed phases and releases AttackA");
    const int attackStartFrame = expectedMove == 300 ? 62 : expectedMove == 330 ? 65 : 71;
    const int observedLifetime = releaseFrame >= 0 ? releaseFrame - attackStartFrame + 1 : 0;
    check(released && observedLifetime <= expectedLifetime + 2,
          prefix + "releases within measured " +
              std::string(sourcePeriodTimeline ? "NN/.X period sum " : "fallback contact timer ") +
              std::to_string(expectedLifetime) + " ticks (observed " +
              std::to_string(observedLifetime) + ")");
    check(match.fighter(0).trail(1).triangles() == 0,
          prefix + "does not invent an active second prop trail");
}

void akane0_contact_timing(const Combo& combo) {
    gameplay::Fighter attacker, victim;
    xm::Controller attackerController, victimController;
    attacker.init(&combo.model,&attackerController,glm::vec3(0.f),0.f);
    victim.init(&combo.model,&victimController,glm::vec3(0.f,0.f,1500.f),0.f);
    combo.bind(attacker);
    combo.bind(victim);
    for (int i = 0; i < 70; ++i) {
        attacker.update(nullptr,nullptr,gameplay::FixedStep::seconds);
        victim.update(nullptr,nullptr,gameplay::FixedStep::seconds);
    }
    fnd::input::PlayerState input;
    input.down[fnd::input::Action::AttackA] = true;
    tick(attacker,input);
    input.down[fnd::input::Action::AttackA] = false;
    tick(attacker,input);
    bool hit = false;
    int hitPhase = -1;
    int hitTick = -1;
    bool hitRecord = false;
    for (int frame = 0; frame < 100 && !hit; ++frame) {
        tick(attacker,input);
        if (!attacker.melee_in_active()) continue;
        const auto& record = attacker.current_move_record();
        if (!record || !record->has_combat()) continue;
        const int bone = combo.model.findFrame(record->boneName);
        if (bone < 0) continue;
        std::vector<glm::mat4> posed;
        attackerController.evalWorld(posed);
        if (static_cast<size_t>(bone) >= posed.size()) continue;
        // Independently transform the parsed move-record anchors through the rig.
        // Do not use HitboxDebug::attackCenter as both target input and assertion.
        const glm::mat4 boneWorld = attacker.modelMatrix() * posed[static_cast<size_t>(bone)];
        const glm::vec3 start = glm::vec3(boneWorld * glm::vec4(record->anchor[0],
            record->anchor[1],record->anchor[2],1.f));
        const glm::vec3 end = glm::vec3(boneWorld * glm::vec4(record->endAnchor[0],
            record->endAnchor[1],record->endAnchor[2],1.f));
        const glm::vec3 center = record->collisionShape != 0 ? (start + end) * 0.5f : start;
        victim.reset(center - victim.hurtbox_anchor_offset(1),victim.facing_yaw());
        victim.set_state(gameplay::FighterState::Idle);
        hit = attacker.try_melee_hit(victim);
        if (!hit) continue;
        attacker.note_melee_hit(1);
        hitPhase = attacker.move_phase();
        hitTick = attacker.phase_elapsed();
        const auto* current = attacker.current_move_record();
        hitRecord = attacker.attack_move_id() == 300 && current && current->has_combat() &&
                    current->boneName == "Bip01_Prop1" && current->activeFrame <= hitTick;
    }
    check(hit,"Akane+0 move300 connects when its live weapon volume is occupied");
    check(hitPhase == 2 && hitTick >= 3 && hitRecord,
          "Akane+0 contact lands on the current phase-2 Prop1 record, after its activeFrame");
    check(attacker.swing_hit_count() == 1,
          "the longer move lifetime preserves one-contact-per-victim accounting");
    check(victim.hp() < victim.max_hp(),
          "the phase-2 contact applies the weapon record's damage");
}

void gated_timeline_fallback() {
    if (gatedTimelineCharacter < 0) {
        check(false,"roster has a gated 300/311/330 phase to validate fallback lifetime");
        return;
    }
    Combo combo;
    std::string error;
    const bool loaded = combo.load(gatedTimelineCharacter,gatedTimelineWeapon,error);
    const std::string label = gameplay::comboSlotLabel(gatedTimelineCharacter,
                                                        gatedTimelineWeapon);
    check(loaded,label + " gated-phase combo fixture reloads");
    if (!loaded) return;
    gameplay::Fighter fighter;
    combo.init(fighter);
    fnd::input::PlayerState input;
    auto pulse = [&](fnd::input::Action action) {
        input.down[action] = true;
        tick(fighter,input);
        input.down[action] = false;
        tick(fighter,input);
    };
    if (gatedTimelineMove == 330) {
        pulse(fnd::input::Action::Up);
        pulse(fnd::input::Action::Up);
    } else if (gatedTimelineMove == 311) {
        pulse(fnd::input::Action::Jump);
        pulse(fnd::input::Action::Up);
        pulse(fnd::input::Action::Up);
    }
    input.down[fnd::input::Action::AttackA] = true;
    tick(fighter,input);
    input.down[fnd::input::Action::AttackA] = false;
    tick(fighter,input);
    const bool selected = fighter.state() == gameplay::FighterState::AttackA &&
                          fighter.attack_move_id() == gatedTimelineMove;
    check(selected,label + " actual input selects gated move " +
          std::to_string(gatedTimelineMove));
    bool released = false;
    for (int i = 0; i < 300 && fighter.state() == gameplay::FighterState::AttackA; ++i)
        tick(fighter,input);
    released = fighter.state() != gameplay::FighterState::AttackA;
    check(released,label + " nonzero +0x20 callback gate keeps the fallback timer and releases");
}

void shots(const Combo& combo) {
    for (int tier = 0; tier < 3; ++tier) {
        gameplay::Fighter fighter;
        combo.init(fighter);
        fnd::input::PlayerState input;
        input.down[fnd::input::Action::Shoot] = true;
        const int hold = tier == 0 ? 1 : tier == 1 ? 30
            : 30 + combo.weapon.magazines[1].chargeMax;
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
        // FUN_0043f3e0 reaches Yellow in30 updates, now within the leap.
        {gameplay::ShotTier::Yellow, 30, true,  12, 2, false, "Rena+0 air first charge"},
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
    for (int i = 0; i < 30 + combo.weapon.magazines[1].chargeMax; ++i) tick(charged,held);
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
    // The air fixture above exercises460; also pin its transcribed launch anchor.
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
    pool.update(gameplay::FixedStep::seconds, &victim, 1, nullptr, nullptr);
    check(victim.hp() == hpBefore, "a zero-power projectile takes no HP");
    check(victim.stats().damageTaken == 0, "and records no damage taken");
    check(pool.contact_count() > 0, "while still reporting a contact");
    if (pool.contact_count() > 0)
        check(pool.contact(0).effect == 30,
              "carrying the record's own impact effect");
    check(victim.state() == gameplay::FighterState::Hit,
          "and the zero-power projectile still staggers its victim");

    // FUN_00637950:74 rejects a victim with +0x7ac >= 1 before any contact work, so the
    // shot flies through: no contact event, no spent allowance, no status.
    gameplay::Fighter invincible;
    combo.init(invincible, {0, 0, 40});
    gameplay::HitReaction grant;
    grant.row = grant.rowHigh = 100;
    grant.meterA = 120;
    grant.meterB = 120;
    invincible.take_damage(0, &owner, 0, 100, false, grant);
    check(invincible.invincible_ticks() > 0, "a full down meter grants +0x7ac");
    const gameplay::FighterState stateBefore = invincible.state();
    gameplay::ProjectilePool passThrough;
    check(passThrough.spawn(invincible.position() - glm::vec3(0, 0, 30), {0, 0, 1},
                            gameplay::ShotTier::Tap, &owner, 0),
          "the second shot allocates");
    passThrough.update(gameplay::FixedStep::seconds, &invincible, 1, nullptr, nullptr);
    check(passThrough.contact_count() == 0, "an invincible victim reports no contact");
    check(passThrough.live_shots() == 1, "and the shot survives it");
    check(invincible.state() == stateBefore, "and the reaction is unchanged");
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
    pool.update(gameplay::FixedStep::seconds,nullptr,0,nullptr,nullptr);
    check(std::abs(pool.shots()[0].pos.z-37.5f) < 1e-4f,"nata speed is 37.5 per original update, not shared tier tuning");
    check(pool.spawn({100,0,0},{0,0,1},gameplay::ShotTier::Tap,&owner,0),"second tap has its own instance");
    pool.update(gameplay::FixedStep::seconds,nullptr,0,nullptr,nullptr);
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
    pool.update(gameplay::FixedStep::seconds,nullptr,0,nullptr,nullptr);
    pool.update(gameplay::FixedStep::seconds,nullptr,0,nullptr,nullptr);
    check(std::abs(pool.shots()[0].pos.z-50.f)<1e-4f && std::abs(pool.shots()[0].pos.y-9.7f)<1e-4f,
          "grenade uses its own speed, delayed vertical launch and gravity");
    pool.clear();
    pool.spawn({0,0,0},{0,0,1},gameplay::ShotTier::Red,&owner,11);
    pool.update(gameplay::FixedStep::seconds,nullptr,0,nullptr,nullptr);
    check(pool.live_shots() == 2 && pool.shots()[1].bulletRow == 17 && pool.shots()[1].elapsed == 0,
          "red nata emits exact secondary trail row 17, with a newborn independent clock");
    const glm::vec3 trailPosition = pool.shots()[1].pos;
    pool.update(gameplay::FixedStep::seconds,nullptr,0,nullptr,nullptr);
    check(pool.shots()[1].pos == trailPosition,"secondary trail is stationary, not a guessed moving projectile");
    bool finite = true;
    const auto matrix = pool.shots()[1].model_matrix();
    for (int col=0; col<4; ++col) for (int row=0; row<4; ++row) finite &= std::isfinite(matrix[col][row]);
    check(finite,"zero-speed trail retains its launch direction and finite model rotation");
    pool.update(gameplay::FixedStep::seconds,nullptr,0,nullptr,nullptr);
    check(pool.live_shots() == 3,"red secondary emissions repeat every two original updates");

    gameplay::Fighter victim;
    combo.init(victim);
    const auto chest = victim.hitbox_debug().anchors[1];
    pool.clear();
    pool.spawn(chest-glm::vec3(0,0,37.5f),{0,0,1},gameplay::ShotTier::Tap,&owner,0);
    pool.update(gameplay::FixedStep::seconds,&victim,1,nullptr,nullptr);
    check(victim.hp()<victim.max_hp() && pool.shots()[0].alive,
          "normal nata contact spends a victim allowance without consuming the projectile");
    const int tapHp = victim.hp();
    pool.update(gameplay::FixedStep::seconds,&victim,1,nullptr,nullptr);
    check(victim.hp()==tapHp,"normal nata cannot damage the same victim twice");

    combo.init(victim);
    pool.clear();
    pool.spawn(victim.hitbox_debug().anchors[1]-glm::vec3(0,0,45.f),{0,0,1},
               gameplay::ShotTier::Red,&owner,11);
    pool.update(gameplay::FixedStep::seconds,&victim,1,nullptr,nullptr);
    const auto contactPosition = pool.shots()[0].pos;
    const int contactAge = pool.shots()[0].elapsed;
    check(victim.hp()<victim.max_hp() && pool.shots()[0].contactPending,
          "red nata records contact for its executable pause policy");
    for (int i=0; i<5; ++i) pool.update(gameplay::FixedStep::seconds,nullptr,0,nullptr,nullptr);
    check(pool.shots()[0].pos==contactPosition && pool.shots()[0].elapsed==contactAge,
          "red nata's first five contact updates freeze movement and its record clock");
    pool.update(gameplay::FixedStep::seconds,nullptr,0,nullptr,nullptr);
    check(std::abs(pool.shots()[0].pos.z-contactPosition.z-60.f)<1e-4f &&
          pool.shots()[0].hitsRemaining[0]==4 && !pool.shots()[0].contactPending,
          "red nata resumes at sixty units/update, retaining its five-hit victim budget");

    // Q25 rows (item 001 parameters 40/60/70/90/130/140): FUN_005f91c0's speeds,
    // lifetime, wall child 5 and the +0x30 initial yaw offset. No target, so the
    // projectile flies straight along that offset.
    struct Q25Row { int row; float speed; float yawDegrees; };
    const Q25Row q25[] = {{4,30.f,45.f},{6,45.f,0.f},{7,45.f,0.f},
                          {9,30.f,-45.f},{13,25.f,60.f},{14,25.f,-60.f}};
    for (const Q25Row& expected : q25) {
        pool.clear();
        check(pool.spawn({0,0,0},{0,0,1},gameplay::ShotTier::Tap,&owner,expected.row),
              "Q25 row allocates");
        const gameplay::Projectile* shot = nullptr;
        for (const auto& s : pool.shots())
            if (s.alive && s.bulletRow==expected.row) shot=&s;
        check(shot && shot->behavior && shot->behavior->wallRow==5,
              "Q25 row carries the recovered behavior and wall child 5");
        if (!shot) continue;
        const glm::vec3 from = shot->pos;
        pool.update(gameplay::FixedStep::seconds,nullptr,0,nullptr,nullptr);
        const gameplay::Projectile* moved = nullptr;
        for (const auto& s : pool.shots())
            if (s.alive && s.bulletRow==expected.row) moved=&s;
        check(moved!=nullptr,"Q25 row survives its first update");
        if (!moved) continue;
        const glm::vec3 delta = moved->pos - from;
        check(std::abs(glm::length(delta)-expected.speed)<1e-3f,
              "Q25 row moves at the recovered per-update speed");
        const float yaw = glm::degrees(std::atan2(delta.x,delta.z));
        check(std::abs(std::remainder(yaw-expected.yawDegrees,360.f))<0.5f,
              "Q25 row launches on its recovered initial yaw offset");
    }
    // Row 60's lifetime is 240 updates (FUN_005f91c0 case 0x3c); the tick that sees
    // ticks > lifetime retires it.
    pool.clear();
    check(pool.spawn({0,0,0},{0,0,1},gameplay::ShotTier::Tap,&owner,6),
          "row 6 lifetime probe allocates");
    for (int i=0;i<241;++i) pool.update(gameplay::FixedStep::seconds,nullptr,0,nullptr,nullptr);
    check(pool.shots()[0].ticks==241, "row 6 has ticked 241 times (got " +
          std::to_string(pool.shots()[0].ticks) + ")");
    check(pool.live_shots()==1,"row 6 is alive while its tick count equals the lifetime");
    pool.update(gameplay::FixedStep::seconds,nullptr,0,nullptr,nullptr);
    check(pool.live_shots()==0,"row 6 retires once the tick count passes its 240 lifetime");
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
    gated_timeline_fallback();
    auto rena = std::make_unique<Combo>();
    std::string error;
    const bool loaded = rena->load(0,0,error);
    check(loaded,"Rena+0 actual move/item/rig fixture loads");
    if (loaded) {
        aerial_attack(*rena,"Rena+0");
        execution(*rena);
        miss_trail_world_anchors(*rena);
        zero_power_contact();
        zero_power_projectile(*rena);
        shots(*rena);
        launch_rules(*rena);
        projectile_clocks(*rena);
    }
    // V3-34: effect cards animate, and their clock is the card's lifetime. The card the
    // empty tap draws is data/effect/01.X (texture 渦巻き); it ships an AnimationSet, and
    // before this the port drew every card in bind pose, so a moving card read as static
    // hoops. This checks the two halves separately: that shipping the model exposes an
    // animation, and that the clock reaches distinct pose samples across the card's life.
    if (const auto card = read_card_model("data/effect/01.X")) {
        check(!card->anims.empty() && card->anims[0].duration > 0.f,
              "the empty-tap card ships an animation to play");
        if (!card->anims.empty() && card->ticksPerSecond > 0.f) {
            const double animSeconds =
                card->anims[0].duration / card->ticksPerSecond;
            check(animSeconds > 0.0, "the card's animation has a positive duration");
            std::vector<glm::mat4> first, middle, last;
            for (const auto& [age, out] : {std::pair<float, std::vector<glm::mat4>*>{0.f, &first},
                                           {0.5f, &middle}, {1.f, &last}}) {
                xm::Controller pose;   // fresh: each card starts from bind pose
                pose.bind(card.get());
                pose.setAnimation(0, false);
                pose.setTrackPosition(0, game::cardAnimationSeconds(
                                               age, 1.f, animSeconds));
                pose.evalWorld(*out);
            }
            bool moved = false;
            if (first.size() == last.size())
                for (size_t i = 0; i < first.size(); ++i)
                    if (first[i] != last[i]) { moved = true; break; }
            check(moved, "the card's pose differs between birth and expiry");
            bool halfway = false;
            if (first.size() == middle.size())
                for (size_t i = 0; i < first.size(); ++i)
                    if (first[i] != middle[i]) { halfway = true; break; }
            check(halfway, "and it moves through the middle of its life, not only at the end");
        }
    } else {
        check(false, "the empty-tap card data/effect/01.X loads from the install");
    }

    auto akane = std::make_unique<Combo>();
    error.clear();
    const bool akaneLoaded = akane->load(13,0,error);
    check(akaneLoaded,"Akane+0 actual move/item/rig fixture loads");
    if (akaneLoaded) {
        akane0_trail_windows(*akane);
        // #31's confirmed selector is Rena+0-only. Another real combo checks
        // its own existing aerial row/tag rather than inheriting that contract.
        gameplay::Fighter smoke;
        akane->init(smoke);
        fnd::input::PlayerState input;
        input.down[fnd::input::Jump] = true;
        tick(smoke,input);
        input.down[fnd::input::Jump] = false;
        tick(smoke,input);
        input.down[fnd::input::AttackA] = true;
        tick(smoke,input);
        check(smoke.attack_move_id() == 340 &&
              smoke.anim_set_index() == akane->moves.first_set_index(340) &&
              !smoke.anim_fallback(), "Akane+0 retains its own aerial table binding, not Rena's selector");
        akane0_miss_trail(*akane,300,"Akane+0 neutral 300");
        akane0_miss_trail(*akane,330,"Akane+0 dash 330");
        akane0_contact_timing(*akane);
    }
    std::printf("ANIMATION_DATA: %d checks, %d failures\n",checks,failures);
    return failures ? 1 : 0;
}
