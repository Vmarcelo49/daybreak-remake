// =============================================================================
//  melee_rules_test.cpp — issue #10: directional, aerial and multi-target melee.
//
//  Pins the current combat-port behavior against weapon-bound move data:
//    * ground melee cannot hit a distant airborne fighter just because XZ overlaps;
//    * the situation selects a weapon move for aerial swings, which still use 3D reach;
//    * the recovered sphere has no angle term, so a target behind can connect;
//    * a solid barrier between them blocks the swing;
//    * one swing can hit SEVERAL opponents, each exactly once;
//    * allies are never hit;
//    * recovery is a real lockout, and an interrupted attack does not keep hitting;
//    * the heavy-key stand-in is gone.
//
//  Also parses the shipped character move tables when an install is present, to check
//  recovered file facts (issue #26): each phase's section tag is treated as the
//  animation-set index — move 10 opens on 1 (walk), move 20 lists [13,14,15],
//  move 30 opens on 54, move 40 on 2 — and moves 40/41/42 are the jump chain with no
//  combat block, while 300-family weapon phases carry real hits. The common neutral
//  attack input uses a documented port inference for move 300; source selectors remain
//  conditional on player fields that this simplified state machine does not model.
//
//  Build (CMake target `melee_rules_test`):
//    cmake --build remake/foundation/build/linux --target melee_rules_test
//  Exit status: 0 when every check passes, 1 otherwise.
// =============================================================================
#include "gameplay/character_moves.h"
#include "gameplay/melee_rules.h"
#include "gameplay/match.h"

#include <array>
#include <cmath>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

namespace {

namespace fs = std::filesystem;
using gameplay::Fighter;
using gameplay::FighterState;
namespace input = fnd::input;

int checks = 0;
int failures = 0;
int skipped = 0;

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

// One simulation tick with a freshly derived edge set, like the live poll path.
void tick(Fighter& f, const input::PlayerState& in) {
    input::PlayerState copy = in;
    input::compute_edges(copy);
    f.update(&copy, nullptr, 1.0 / 64.0);
}

// A fresh fighter out of the 60-frame BattleStart pose, so it can act immediately.
Fighter idle_at(const glm::vec3& at, float facing = 0.0f) {
    Fighter f;
    f.init(nullptr, nullptr, at, facing);
    input::PlayerState idle;
    for (int i = 0; i < 70; ++i) tick(f, idle);
    return f;
}

// Press once and advance through the bound weapon move's own startup window.
void swing_to_active(Fighter& f, int extraTicks = 0) {
    input::PlayerState in;
    in.down[input::Action::AttackA] = true;
    tick(f, in);
    in.down[input::Action::AttackA] = false;
    for (int i = 0; i < 240 && !f.melee_in_active(); ++i) tick(f, in);
    for (int i = 0; i < extraTicks && f.melee_in_active(); ++i) tick(f, in);
}

// Presses melee once and advances to exactly `elapsed` swing ticks (the press tick
// counts as elapsed 1). Data-driven swings size their own windows, so they cannot
// use the legacy-timed helper above.
void swing_to_elapsed(Fighter& f, int elapsed) {
    input::PlayerState in;
    in.down[input::Action::AttackA] = true;
    tick(f, in);
    in.down[input::Action::AttackA] = false;
    for (int i = 1; i < elapsed; ++i) tick(f, in);
}

// A 124-set synthetic rig, named like the shipped files (index i = "Anim-(124-i)"),
// so animation-set assertions use the same controller indices. `durationTicks` controls
// the D3DX period threshold used by the phase-boundary regression.
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

// Double-tap a direction: the second press chains into a committed dash.
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

// Loads one shipped item definition; false when the install is absent.
bool load_weapon(const fs::path& install, int itemId, gameplay::WeaponDefinition& out) {
    std::error_code ec;
    if (install.empty() || !fs::is_directory(install / "data" / "item", ec))
        return false;
    char rel[32];
    std::snprintf(rel, sizeof(rel), "%03d.dat", itemId);
    std::ifstream in(install / "data" / "item" / rel, std::ios::binary);
    if (!in) return false;
    const std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(in)),
                                     std::istreambuf_iterator<char>());
    std::string err;
    return out.parse(itemId, bytes.data(), bytes.size(), err);
}

// Decodes both charge levels' bullet parameters the way the live path does
// (lowest-type bullet per magazine; missing files keep the shared table).
// Returns true when at least one level armed.
bool load_bullet_params(const fs::path& install, const gameplay::WeaponDefinition& weapon,
                        gameplay::BulletParameter& tap, gameplay::BulletParameter& chg) {
    bool any = false;
    for (int level = 1; level <= 2; ++level) {
        const int want = weapon.magazineForChargeLevel(level).chargeLevel - 1;
        const gameplay::BulletDefinition* best = nullptr;
        for (int i = 0; i < weapon.bulletCount; ++i) {
            const gameplay::BulletDefinition& b = weapon.bullets[i];
            if (b.magazine != want) continue;
            if (!best || b.type < best->type) best = &b;
        }
        if (!best) continue;
        char rel[48];
        std::snprintf(rel, sizeof(rel), "bullet/%03d/%03d.dat", weapon.id, best->type);
        std::ifstream in(install / "data" / rel, std::ios::binary);
        if (!in) continue;
        const std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(in)),
                                         std::istreambuf_iterator<char>());
        std::string err;
        gameplay::BulletParameter& slot = (level == 1) ? tap : chg;
        any |= gameplay::parseBulletParameter(bytes.data(), bytes.size(), best->status,
                                              slot, err);
    }
    return any;
}

// Loads one shipped character move table; false when the install is absent.
bool load_moves(const fs::path& install, const char* character, const char* nn,
                gameplay::CharacterMoves& out) {
    std::error_code ec;
    if (install.empty() || !fs::is_directory(install / "data" / character, ec))
        return false;
    std::ifstream in(install / "data" / character / nn, std::ios::binary);
    if (!in) return false;
    const std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(in)),
                                     std::istreambuf_iterator<char>());
    std::string err;
    if (!out.parse(bytes.data(), bytes.size(), err)) return false;
    out.set_character_index(gameplay::characterIndexForDir(character));
    return true;
}

// Generic Fighter combat checks still use a real roster pairing: Rena 0's parsed
// move table and its matching slot-0 item. FUN_0041e180's NN.dat header carries the
// item id at +0x114, verified against kWeaponIds for every shipped table.
struct CombatCombo {
    std::unique_ptr<gameplay::CharacterMoves> moves =
        std::make_unique<gameplay::CharacterMoves>();
    gameplay::WeaponDefinition weapon;

    bool load(const fs::path& install) {
        const int itemId = gameplay::kWeaponIds[0][0];
        return load_moves(install, "rena", "00.dat", *moves) &&
               moves->weapon_id() == itemId && load_weapon(install, itemId, weapon) &&
               weapon.id == itemId;
    }
    void bind(Fighter& fighter) const {
        fighter.set_moves(moves.get());
        fighter.set_weapon(&weapon);
    }
};

bool requireCombatCombo(const fs::path& install, CombatCombo& combo,
                        const char* testName) {
    if (combo.load(install)) return true;
    skip(testName);
    return false;
}

// ---------------------------------------------------------------------------
// Vertical separation — the issue's headline criterion.
// ---------------------------------------------------------------------------
void testVerticalSeparation(const fs::path& install) {
    section("vertical separation");
    CombatCombo combo;
    if (!requireCombatCombo(install, combo, "vertical separation (no install found)")) return;
    Fighter attacker = idle_at(glm::vec3(0, 0, 0));
    Fighter grounded = idle_at(glm::vec3(0, 0, 40));
    Fighter airborne  = idle_at(glm::vec3(0, 0, 40));
    combo.bind(attacker);
    combo.bind(grounded);
    combo.bind(airborne);
    // Settling is 70 ticks of gravity, so a target placed high would land before the
    // swing. Settle first, THEN re-place it: BattleStart costs nothing here because
    // only the attacker's windows are under test.
    airborne.reset(glm::vec3(0, 400, 40), 0.0f);   // same XZ, 400 up

    checkInt(40, static_cast<int>(grounded.position().z),
             "the grounded target stands within Rena 0's move radius");
    checkInt(400, static_cast<int>(airborne.position().y),
             "the airborne target stands 400 units up at the same XZ");
    swing_to_active(attacker);
    check(attacker.try_melee_hit(grounded), "ground melee connects with a grounded target");
    check(grounded.hp() < 100, "and it does damage");

    // Same XZ overlap, but 400 units above the weapon swing's vertical reach.
    Fighter a2 = idle_at(glm::vec3(0, 0, 0));
    combo.bind(a2);
    swing_to_active(a2);
    check(!a2.try_melee_hit(airborne),
          "ground melee refuses a target 400 units up at identical XZ");
    checkInt(100, airborne.hp(), "and the airborne fighter takes nothing");

    // The swing kind and move are chosen by the fighter's situation AT THE PRESS, so
    // the attacker must be airborne when it presses; airborne height, not a separate
    // aerial hitbox shape, is what closes the gap to this target.
    Fighter a3 = idle_at(glm::vec3(0, 0, 0));
    combo.bind(a3);
    {
        input::PlayerState jump;
        jump.down[input::Action::Jump] = true;
        tick(a3, jump);
    }
    check(!a3.aerial_attack(), "the jump alone does not select an aerial swing");
    swing_to_active(a3);
    check(a3.aerial_attack(), "pressing melee while airborne selects the aerial swing");
    // The recovered hitbox is ONE sphere: a grounded and an aerial swing resolve through
    // the same predicate, so the swing KIND is not what decides a hit -- the 3D distance
    // to the victim's head/chest anchors is. What an aerial swing buys is that the
    // attacker has RISEN, closing the vertical gap to a target that is off the floor.
    airborne.reset(glm::vec3(0, a3.position().y, 30), 0.0f);
    check(a3.try_melee_hit(airborne),
          "an airborne attacker reaches a target at its own height");
    airborne.reset(glm::vec3(0, a3.position().y + 500.0f, 30), 0.0f);
    check(!a3.try_melee_hit(airborne),
          "and still not one far above the sphere's 30+radius reach");

    // Reach is RELATIVE to the attacker's feet, so a modest elevation still connects
    // while a large one does not. (The fighter's own altitude is irrelevant: both are
    // measured as a difference, which is what makes a stage with height work.)
    Fighter a4 = idle_at(glm::vec3(0, 0, 0));
    Fighter levelNeighbour = idle_at(glm::vec3(0, 0, 30));
    Fighter muchHigher     = idle_at(glm::vec3(0, 0, 30));
    combo.bind(a4);
    combo.bind(levelNeighbour);
    combo.bind(muchHigher);
    muchHigher.reset(glm::vec3(0, 600, 40), 0.0f);
    swing_to_active(a4);
    check(a4.try_melee_hit(levelNeighbour), "a level neighbour is reachable");
    check(!a4.try_melee_hit(muchHigher), "one 600 units above is not");
}

// ---------------------------------------------------------------------------
// Facing.
// ---------------------------------------------------------------------------
void testFacing(const fs::path& install) {
    section("the recovered hitbox is a sphere, not a cone");
    CombatCombo combo;
    if (!requireCombatCombo(install, combo, "facing (no install found)")) return;
    // FUN_0063b470 is a hard 3D sphere test with no angle term. Use distances inside
    // Rena 0's weapon move radius; the bound table/item define this swing's geometry.
    Fighter front = idle_at(glm::vec3(0, 0, 0));
    Fighter ahead  = idle_at(glm::vec3(0, 0, 40));
    Fighter rear   = idle_at(glm::vec3(0, 0, -40));
    combo.bind(front);
    combo.bind(ahead);
    combo.bind(rear);
    swing_to_active(front);
    check(front.try_melee_hit(ahead), "a target 40 ahead is in the weapon move's sphere");
    check(front.try_melee_hit(rear), "a target directly behind is EQUALLY in the sphere");

    // The attack sphere is 30 (recovered body radius) + MeleeRules::radius, in 3D, so
    // the same horizontal distance that connects on the ground is decided by the
    // vertical difference too.
    const gameplay::MeleeRules rules;
    const float combined = rules.bodyRadius + rules.radius;
    check(rules.sphere_hits(0.0f), "an overlapping anchor connects");
    check(!rules.sphere_hits((combined + 1.0f) * (combined + 1.0f)),
          "an anchor just past 30+radius does not");

    // Reach is 3D, so the same horizontal gap that connects on the floor is decided by
    // the vertical difference: at 60 apart the opponent connects, at 400 it cannot.
    Fighter swinger = idle_at(glm::vec3(0, 0, 0));
    Fighter level = idle_at(glm::vec3(0, 0, 40));
    combo.bind(swinger);
    combo.bind(level);
    swing_to_active(swinger);
    check(swinger.try_melee_hit(level), "an opponent 40 away and level connects");
    Fighter high = idle_at(glm::vec3(0, 0, 40));
    combo.bind(high);
    high.reset(glm::vec3(0, 400, 40), 0.0f);
    check(!swinger.try_melee_hit(high),
          "the same opponent 400 above does not, because the sphere is 3D");
}

// ---------------------------------------------------------------------------
// Solid barriers — uses the synthetic collision model from #7's test helpers.
// ---------------------------------------------------------------------------
xm::Model wall_between_fighters() {
    xm::Model model;
    model.meshes.emplace_back();
    const float h = 400.f;
    const glm::vec3 a(-40, 0, 0), b(40, 0, 0), c(40, h, 0), d(-40, h, 0);
    const uint32_t base = static_cast<uint32_t>(model.meshes.back().vertices.size());
    for (const glm::vec3& p : {a, b, c, d}) {
        xm::Vertex v;
        v.pos = p;
        model.meshes.back().vertices.push_back(v);
    }
    model.meshes.back().indices.insert(model.meshes.back().indices.end(),
                                       {base, base + 1, base + 2, base, base + 2, base + 3});
    return model;
}

void testBarriers(const fs::path& install) {
    section("solid barriers block the swing");
    CombatCombo combo;
    if (!requireCombatCombo(install, combo, "barriers (no install found)")) return;
    xm::Model model = wall_between_fighters();
    game::physics::MovementCollision collision;
    const xm::Model* mesh = &model;
    collision.setMeshes(mesh, nullptr);

    // Without collision the same pair connects: proves the wall is what stops it.
    Fighter open = idle_at(glm::vec3(0, 0, -20));
    Fighter far  = idle_at(glm::vec3(0, 0, 20));
    combo.bind(open);
    combo.bind(far);
    swing_to_active(open);
    check(open.try_melee_hit(far), "with no collision the swing reaches across");

    Fighter walled = idle_at(glm::vec3(0, 0, -20));
    Fighter behindWall = idle_at(glm::vec3(0, 0, 20));
    combo.bind(walled);
    combo.bind(behindWall);
    swing_to_active(walled);
    check(!walled.try_melee_hit(behindWall, &collision),
          "a wall between them blocks the swing");
    checkInt(100, behindWall.hp(), "and the fighter behind it takes nothing");

    // No barrier in the way -> still connects even with collision present.
    Fighter clear = idle_at(glm::vec3(300, 0, -20));
    Fighter clearTarget = idle_at(glm::vec3(300, 0, 20));
    combo.bind(clear);
    combo.bind(clearTarget);
    swing_to_active(clear);
    check(clear.try_melee_hit(clearTarget, &collision),
          "a clear line still connects with collision loaded");

    // An empty collision is permissive, matching the no-collision.x case.
    game::physics::MovementCollision empty;
    Fighter permissive = idle_at(glm::vec3(0, 0, -20));
    Fighter permissiveTarget = idle_at(glm::vec3(0, 0, 20));
    combo.bind(permissive);
    combo.bind(permissiveTarget);
    swing_to_active(permissive);
    check(permissive.try_melee_hit(permissiveTarget, &empty),
          "an empty collision model does not block anything");
}

// ---------------------------------------------------------------------------
// Multiple opponents, per-swing accounting, ally exclusion.
// ---------------------------------------------------------------------------
void testMultipleOpponentsAndAllies(const fs::path& install) {
    section("multiple opponents, per-swing accounting, ally exclusion");
    CombatCombo combo;
    if (!requireCombatCombo(install, combo, "multiple opponents (no install found)")) return;
    Fighter attacker = idle_at(glm::vec3(0, 0, 0));
    Fighter enemyA = idle_at(glm::vec3(-20, 0, 35));
    Fighter enemyB = idle_at(glm::vec3(20, 0, 35));
    combo.bind(attacker);
    combo.bind(enemyA);
    combo.bind(enemyB);
    swing_to_active(attacker);

    const int hpA = enemyA.hp(), hpB = enemyB.hp();
    check(attacker.try_melee_hit(enemyA), "swing connects with the first opponent");
    attacker.note_melee_hit(0);
    check(attacker.try_melee_hit(enemyB), "the SAME swing also connects with the second");
    attacker.note_melee_hit(1);
    check(enemyA.hp() < hpA && enemyB.hp() < hpB, "both took damage from one swing");
    checkInt(2, attacker.swing_hit_count(), "the swing counted two victims");

    // Repeated contact within the same swing is refused by the per-victim set.
    check(attacker.already_hit_this_swing(0), "victim 0 is recorded");
    check(attacker.already_hit_this_swing(1), "victim 1 is recorded");
    check(!attacker.already_hit_this_swing(2), "an untouched victim is not recorded");

    // A new swing re-arms everything.
    attacker.set_state(FighterState::Idle);
    swing_to_active(attacker);
    check(!attacker.already_hit_this_swing(0), "a fresh swing clears the victim's record");
    checkInt(0, attacker.swing_hit_count(), "and resets the count");
}

// ---------------------------------------------------------------------------
// Startup / active / recovery, and interruption.
// ---------------------------------------------------------------------------
void testWindowsAndRecovery(const fs::path& install) {
    section("startup, active, recovery and interruption");
    CombatCombo combo;
    if (!requireCombatCombo(install, combo, "windows and recovery (no install found)")) return;
    const gameplay::MeleeRules rules;
    check(rules.total_ticks() == 30, "the window split still totals the historical 30 ticks");
    check(rules.is_startup(0) && rules.is_startup(rules.startupTicks - 1),
          "the first ticks are startup");
    check(!rules.is_startup(rules.startupTicks), "startup ends at its bound");
    check(rules.is_active(rules.startupTicks), "the active window opens");
    check(rules.is_active(rules.startupTicks + rules.activeTicks - 1),
          "the active window stays open through its last tick");
    check(!rules.is_active(rules.startupTicks + rules.activeTicks),
          "the active window closes at its bound");
    check(rules.is_recovery(rules.startupTicks + rules.activeTicks),
          "recovery follows the active window");

    // A swing that never reaches the active window cannot hit.
    Fighter early = idle_at(glm::vec3(0, 0, 0));
    Fighter earlyTarget = idle_at(glm::vec3(0, 0, 40));
    combo.bind(early);
    combo.bind(earlyTarget);
    input::PlayerState in;
    in.down[input::Action::AttackA] = true;
    tick(early, in);
    check(!early.try_melee_hit(earlyTarget), "the swing cannot land during startup");

    // Recovery is a lockout: once it opens the swing cannot hit again.
    Fighter recovering = idle_at(glm::vec3(0, 0, 0));
    Fighter victim = idle_at(glm::vec3(0, 0, 40));
    combo.bind(recovering);
    combo.bind(victim);
    swing_to_active(recovering);
    check(recovering.try_melee_hit(victim), "it lands during the active window");
    input::PlayerState released;
    for (int i = 0; i < rules.activeTicks; ++i) tick(recovering, released);
    check(recovering.melee_in_recovery(), "the swing is in recovery");
    check(!recovering.try_melee_hit(victim), "and cannot land again during recovery");

    // Being hit interrupts the attack outright.
    Fighter interrupted = idle_at(glm::vec3(0, 0, 0));
    Fighter aggressor = idle_at(glm::vec3(0, 0, 40));
    combo.bind(interrupted);
    combo.bind(aggressor);
    swing_to_active(interrupted);
    interrupted.take_damage(5, &aggressor);   // the swing's OWNER is hit mid-swing
    tick(interrupted, in);
    checkInt(static_cast<int>(FighterState::Hit), static_cast<int>(interrupted.state()),
             "a fighter hit mid-swing is interrupted into Hit");
    Fighter interruptedTarget = idle_at(glm::vec3(0, 0, 40));
    combo.bind(interruptedTarget);
    check(!interrupted.try_melee_hit(interruptedTarget),
          "and its interrupted swing cannot land");

    // The whole swing still expires on its own.
    Fighter expiring = idle_at(glm::vec3(0, 0, 0));
    combo.bind(expiring);
    swing_to_active(expiring);
    input::PlayerState expiryReleased;   // NOT `in`: that one still held the melee key,
                                         // which would re-press and re-arm the timer.
    for (int i = 0; i < rules.total_ticks(); ++i) tick(expiring, expiryReleased);
    checkInt(static_cast<int>(FighterState::Idle), static_cast<int>(expiring.state()),
             "the swing expires back to Idle");
}

// ---------------------------------------------------------------------------
// The heavy-key stand-in is gone.
// ---------------------------------------------------------------------------
void testHeavyKeyUnbound(const fs::path& install) {
    section("the heavy-key stand-in is removed");
    CombatCombo combo;
    if (!requireCombatCombo(install, combo, "heavy key (no install found)")) return;
    Fighter f = idle_at(glm::vec3(0, 0, 0));
    combo.bind(f);
    input::PlayerState in;
    in.down[input::Action::AttackB] = true;
    tick(f, in);
    in.down[input::Action::AttackB] = false;
    for (int i = 0; i < 10; ++i) tick(f, in);
    check(f.state() == FighterState::Idle, "AttackB leaves the fighter idle");
    check(f.melee_in_active() == false && f.already_hit_this_swing(0) == false,
          "and starts no swing");

    // The single melee key still works.
    Fighter m = idle_at(glm::vec3(0, 0, 0));
    combo.bind(m);
    input::PlayerState mi;
    mi.down[input::Action::AttackA] = true;
    tick(m, mi);
    mi.down[input::Action::AttackA] = false;
    check(m.state() == FighterState::AttackA, "AttackA is the one melee control");
}

// ---------------------------------------------------------------------------
// Match-level: ally exclusion survives the multi-candidate rewrite.
// ---------------------------------------------------------------------------
void testMatchAllyExclusion(const fs::path& install) {
    section("Match: ally exclusion and multi-hit in a real match");
    CombatCombo combo;
    if (!requireCombatCombo(install, combo, "match ally exclusion (no install found)")) return;
    gameplay::Match match;
    gameplay::MatchConfig config;
    config.fighterCount = 4;
    for (int i = 0; i < 4; ++i) {
        config.moves[i] = combo.moves.get();
        config.weapon[i] = &combo.weapon;
    }
    config.side[0] = config.side[1] = 0;
    config.side[2] = config.side[3] = 1;
    config.spawn[0] = glm::vec3(0, 0, 0);
    config.spawn[1] = glm::vec3(-10, 0, 35);    // ally, inside Rena 0's move sphere
    config.spawn[2] = glm::vec3(10, 0, 35);     // enemy, inside the same sphere
    config.spawn[3] = glm::vec3(0, 0, 300);     // enemy, out of reach
    config.facing[0] = 0.0f;
    config.facing[1] = 0.0f;
    config.facing[2] = 3.14159f;
    config.facing[3] = 3.14159f;
    const xm::Model* models[4] = {};
    xm::Controller* anims[4] = {};
    match.reset(config, models, anims, nullptr, nullptr);
    match.economy().setLogFile(nullptr);

    // Settle past BattleStart.
    const input::PlayerState* idle[4] = {};
    for (int i = 0; i < 70; ++i) match.step(idle, 1.0 / 64.0);

    const int allyHpBefore = match.fighter(1).hp();
    const int enemyHpBefore = match.fighter(2).hp();
    const int farHpBefore = match.fighter(3).hp();

    // Swing on the tick the fighter is in its active window.
    input::PlayerState melee{};
    melee.down[input::Action::AttackA] = true;
    input::PlayerState release{};
    const input::PlayerState* after[4] = {&release, nullptr, nullptr, nullptr};
    // Match::step reads the PlayerState as given; deriving the edges is the scene's
    // job (main.cpp polls, then calls compute_edges), so the test does it here too.
    for (int i = 0; i < 20; ++i) {
        input::PlayerState press = melee;
        input::compute_edges(press);
        const input::PlayerState* withMelee[4] = {&press, nullptr, nullptr, nullptr};
        input::PlayerState rest = release;
        input::compute_edges(rest);
        const input::PlayerState* idle[4] = {&rest, nullptr, nullptr, nullptr};
        match.step(i == 0 ? withMelee : idle, 1.0 / 64.0);
    }
    checkInt(allyHpBefore, match.fighter(1).hp(), "the ally inside the swing takes nothing");
    check(match.fighter(2).hp() < enemyHpBefore, "the enemy inside the swing is hit");
    checkInt(farHpBefore, match.fighter(3).hp(), "the out-of-reach enemy is untouched");
    check(match.fighter(1).stats().damageTaken == 0, "the ally records no damage taken");
}

// ---------------------------------------------------------------------------
// The load-bearing claim: only weapon-bound moves carry combat geometry.
// ---------------------------------------------------------------------------
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
            check(moves.cancel_window(300) > 0,
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

// ---------------------------------------------------------------------------
// Data-driven swings (issue #26 steps 3–4): with rena's table and matching item
// bound, hit data comes from the selected move. Only the grounded move-300
// animation selector is currently mapped; dash/air animation contexts remain
// visible fallbacks until their binary selector flags are represented. Rena 00.dat:
//   move 300 (ground): set 31, hit frame 4, next effect 10, hr 20, base 1500, dSt 6
//   move 330 (dash):   set 51, hit frame 6, next effect 11, hr 25, base 1500, dSt 6
//   move 340 (air):    set 88, hit frame 16, next effect 21, hr 20, base 1750, dSt 6
// Damage is combat[0x00] (baseDamage) through FUN_00639160 @0x639160: power * 100/100
// (attacker +0x7c8) * 50/100 (victim +0x7cc) * 100/100 (scene +0x43cc) on the original's
// 10000-based pool, which is 8 / 8 / 9 HP on this port's 100 HP scale. The record's
// combat[0x05] field is the victim's gauge feed, not HP. Reach is 30 + hr in 3D against
// the two anchors.
// ---------------------------------------------------------------------------
void testDataDrivenGroundSwing(const fs::path& install) {
    section("data-driven ground swing (rena move 300)");
    gameplay::CharacterMoves moves;
    if (!load_moves(install, "rena", "00.dat", moves)) {
        skip("data-driven ground swing (no install found)");
        return;
    }
    if (moves.weapon_id() != gameplay::kWeaponIds[0][0]) {
        check(false, "Rena 0 move table's header matches item 1");
        return;
    }
    xm::Model model;
    xm::Controller ctrl;
    Fighter attacker;
    bind_synthetic_rig(attacker, model, ctrl, glm::vec3(0, 0, 0));
    attacker.set_moves(&moves);
    // The full live combo: rena's slot-0 weapon (item 1) with both bullet levels,
    // exactly as initMatch binds them. A bare move table is the false-claim trap
    // this suite refuses: behaviour must come from character AND weapon together.
    gameplay::WeaponDefinition weapon;
    gameplay::BulletParameter tapParam, chgParam;
    if (!load_weapon(install, gameplay::kWeaponIds[0][0], weapon) ||
        weapon.id != gameplay::kWeaponIds[0][0]) {
        check(false, "Rena 0's slot-0 item parses and matches the move table");
        return;
    }
    check(true, "Rena 0's slot-0 item parses and matches the move table");
    attacker.set_weapon(&weapon);
    check(attacker.weapon() == &weapon, "the slot-0 weapon is bound with the table");
    if (load_bullet_params(install, weapon, tapParam, chgParam)) {
        attacker.set_bullet_parameter(1, &tapParam);
        attacker.set_bullet_parameter(2, &chgParam);
        check(attacker.shot_params_for(gameplay::ShotTier::Tap).damage !=
                  gameplay::shot_params(gameplay::ShotTier::Tap).damage,
              "bound bullet data reaches the shots");
    } else {
        skip("bound bullet parameters (no bullet files ship them)");
    }
    Fighter victim;
    bind_synthetic_rig(victim, model, ctrl, glm::vec3(0, 0, 40));
    victim.set_moves(&moves);
    victim.set_weapon(&weapon);

    input::PlayerState in;
    in.down[input::Action::AttackA] = true;
    tick(attacker, in);
    in.down[input::Action::AttackA] = false;
    checkInt(static_cast<int>(FighterState::AttackA),
             static_cast<int>(attacker.state()), "the press enters AttackA");
    checkInt(300, attacker.attack_move_id(),
             "the port's grounded neutral candidate uses move 300");
    checkInt(31, attacker.anim_set_index(),
             "the inferred neutral mapping reads Rena 00 move 300's first set");
    check(!attacker.anim_fallback(), "the port inference resolves through the bound combo");

    // Startup is the hit's own frame (4): earlier ticks cannot land.
    tick(attacker, in);
    tick(attacker, in);   // elapsed 3
    check(!attacker.try_melee_hit(victim), "no hit during the 4-frame startup");
    tick(attacker, in);   // elapsed 4: the hit frame
    check(attacker.try_melee_hit(victim), "the hit lands on its own frame");
    checkInt(92, victim.hp(),
             "move 300's combat[0] power: 1500 -> 750 -> 8 HP (FUN_00639160)");
    checkInt(static_cast<int>(FighterState::Hit), static_cast<int>(victim.state()),
             "the victim staggers");

    // Reach is 30 + 20 in 3D: 40 connects, 60 does not.
    Fighter far;
    bind_synthetic_rig(far, model, ctrl, glm::vec3(0, 0, 60));
    far.set_moves(&moves);
    far.set_weapon(&weapon);
    check(!attacker.try_melee_hit(far), "60 units is past the 30+20 sphere");

    // Active until the next effect (frame 10), then recovery locks the swing out.
    for (int i = 0; i < 5; ++i) tick(attacker, in);   // elapsed 9
    check(!attacker.melee_in_recovery(), "still swinging on the last active tick");
    tick(attacker, in);   // elapsed 10
    check(attacker.melee_in_recovery(), "recovery follows the active window");
    check(!attacker.try_melee_hit(victim), "and recovery cannot land");
    // The victim's stun is the weapon's own defenderHitstun (6), not the legacy 8.
    int stun = 0;
    while (victim.state() == FighterState::Hit && stun < 60) {
        victim.update(nullptr, nullptr, 1.0 / 64.0);
        ++stun;
    }
    checkInt(6, stun, "hit-stun lasts the weapon's 6 ticks");
    // The swing totals 4 + 6 + 17 = 27 ticks, then expires on its own.
    for (int i = 0; i < 18; ++i) tick(attacker, in);
    checkInt(static_cast<int>(FighterState::Idle), static_cast<int>(attacker.state()),
             "the 27-tick swing expires back to Idle");
}

void testDataDrivenDashAndAir(const fs::path& install) {
    section("data-driven dash and air swings (rena moves 330/340)");
    gameplay::CharacterMoves moves;
    if (!load_moves(install, "rena", "00.dat", moves)) {
        skip("data-driven dash swing (no install found)");
        skip("data-driven air swing (no install found)");
        return;
    }
    if (moves.weapon_id() != gameplay::kWeaponIds[0][0]) {
        check(false, "Rena 0 move table's header matches item 1");
        return;
    }
    gameplay::WeaponDefinition weapon;
    if (!load_weapon(install, gameplay::kWeaponIds[0][0], weapon) ||
        weapon.id != moves.weapon_id()) {
        check(false, "Rena 0 slot-0 item parses and matches its move table");
        return;
    }
    // Dash attack: double-tap Run, then melee while still dashing.
    {
        xm::Model model;
        xm::Controller ctrl;
        Fighter dasher;
        bind_synthetic_rig(dasher, model, ctrl, glm::vec3(0, 0, 0));
        dasher.set_moves(&moves);
        dasher.set_weapon(&weapon);
        check(dasher.weapon() == &weapon && weapon.id == gameplay::kWeaponIds[0][0],
              "the dash attack binds its matching Rena 0 weapon");
        input::PlayerState in;
        in.down[input::Action::Up] = true;
        tick(dasher, in);
        in.down[input::Action::Up] = false;
        tick(dasher, in);
        in.down[input::Action::Up] = true;
        tick(dasher, in);
        checkInt(static_cast<int>(FighterState::Run), static_cast<int>(dasher.state()),
                 "double-tap enters the dash");
        in.down[input::Action::Up] = false;
        in.down[input::Action::AttackA] = true;
        tick(dasher, in);
        in.down[input::Action::AttackA] = false;
        checkInt(330, dasher.attack_move_id(), "a dash press resolves the lunge (330)");
        checkInt(0, dasher.anim_set_index(),
                 "dash attack selector is unresolved; no lunge clip is guessed");
        check(dasher.anim_fallback(), "dash attack reports its animation fallback");
        // The dash carried the fighter forward; meet it where it is (reach 55).
        const float z = dasher.position().z;
        Fighter victim;
        bind_synthetic_rig(victim, model, ctrl, glm::vec3(0, 0, z + 45));
        victim.set_moves(&moves);
        victim.set_weapon(&weapon);
        for (int i = 0; i < 5; ++i) tick(dasher, in);   // elapsed 6: the hit frame
        check(dasher.try_melee_hit(victim), "the lunge connects inside 30+25");
        checkInt(92, victim.hp(), "move 330's power: 1500 -> 750 -> 8 HP");
    }
    // Air attack: leap, then melee while airborne.
    {
        xm::Model model;
        xm::Controller ctrl;
        Fighter flyer;
        bind_synthetic_rig(flyer, model, ctrl, glm::vec3(0, 0, 0));
        flyer.set_moves(&moves);
        flyer.set_weapon(&weapon);
        check(flyer.weapon() == &weapon && weapon.id == gameplay::kWeaponIds[0][0],
              "the aerial attack binds its matching Rena 0 weapon");
        input::PlayerState jump;
        jump.down[input::Action::Jump] = true;
        tick(flyer, jump);
        jump.down[input::Action::Jump] = false;
        tick(flyer, jump);
        check(flyer.airborne(), "the leap leaves the ground");
        input::PlayerState in;
        in.down[input::Action::AttackA] = true;
        tick(flyer, in);
        in.down[input::Action::AttackA] = false;
        check(flyer.aerial_attack(), "the airborne press flags the aerial swing");
        checkInt(340, flyer.attack_move_id(), "resolving the weapon aerial (340)");
        checkInt(0, flyer.anim_set_index(),
                 "air attack selector is unresolved; no aerial clip is guessed");
        check(flyer.anim_fallback(), "air attack reports its animation fallback");
        Fighter early;
        bind_synthetic_rig(early, model, ctrl, flyer.position());
        early.set_moves(&moves);
        early.set_weapon(&weapon);
        check(!flyer.try_melee_hit(early), "no hit during the 16-frame startup");
        for (int i = 0; i < 15; ++i) tick(flyer, in);   // elapsed 16: the hit frame
        // Meet the risen attacker at its own height (reach 50 in 3D).
        Fighter victim;
        bind_synthetic_rig(victim, model, ctrl, glm::vec3(0, 0, 0));
        victim.set_moves(&moves);
        victim.set_weapon(&weapon);
        victim.reset(glm::vec3(flyer.position().x, flyer.position().y,
                               flyer.position().z + 30),
                     0.0f);
        check(flyer.try_melee_hit(victim), "the aerial connects at its own height");
        checkInt(91, victim.hp(), "move 340's power: 1750 -> 875 -> 9 HP");
    }
}

void testDataDrivenFallback(const fs::path& install) {
    section("projectile firing has no recovered animation selector");
    CombatCombo combo;
    if (!requireCombatCombo(install, combo,
                            "projectile animation selector (no install found)")) return;
    xm::Model model;
    xm::Controller ctrl;
    Fighter bound;
    bind_synthetic_rig(bound, model, ctrl, glm::vec3(0, 0, 0));
    combo.bind(bound);
    input::PlayerState charge;
    charge.down[input::Action::Shoot] = true;
    tick(bound, charge);
    charge.down[input::Action::Shoot] = false;
    tick(bound, charge);
    checkInt(static_cast<int>(FighterState::ShootA), static_cast<int>(bound.state()),
             "a released tap fires through the projectile input path");
    const gameplay::PendingShot shot = bound.take_pending_shot();
    check(shot.armed, "the matching weapon combo produces a projectile");
    checkInt(0, bound.anim_set_index(),
             "shot cue does not borrow Rena's weapon swing set");
    check(bound.anim_fallback(), "unmapped projectile animation reports fallback");
    for (FighterState state : {FighterState::ShootB, FighterState::ShootC,
                               FighterState::ShotFinal}) {
        bound.set_state(state);
        checkInt(0, bound.anim_set_index(), "unmapped shot tier stays on set 0");
        check(bound.anim_fallback(), "unmapped shot tier reports fallback");
    }
}

void testMatchDataDriven(const fs::path& install) {
    section("Match: data-driven swings damage once, allies stay safe");
    gameplay::CharacterMoves moves;
    if (!load_moves(install, "rena", "00.dat", moves)) {
        skip("data-driven match swing (no install found)");
        return;
    }
    gameplay::Match match;
    gameplay::MatchConfig config;
    config.fighterCount = 2;
    config.side[0] = 0;
    config.side[1] = 1;
    config.spawn[0] = glm::vec3(0, 0, 0);
    config.spawn[1] = glm::vec3(0, 0, 40);   // inside the 30+20 sphere
    config.moves[0] = &moves;
    config.moves[1] = &moves;
    gameplay::WeaponDefinition weapon;
    if (moves.weapon_id() != gameplay::kWeaponIds[0][0] ||
        !load_weapon(install, gameplay::kWeaponIds[0][0], weapon) ||
        weapon.id != moves.weapon_id()) {
        check(false, "Rena 0 slot-0 item parses and matches its move table");
        return;
    }
    check(true, "Rena 0 slot-0 item parses and matches its move table");
    config.weapon[0] = &weapon;
    config.weapon[1] = &weapon;
    const xm::Model* models[4] = {};
    xm::Controller* anims[4] = {};
    match.reset(config, models, anims, nullptr, nullptr);
    const input::PlayerState* idle[4] = {};
    for (int i = 0; i < 70; ++i) match.step(idle, 1.0 / 64.0);
    check(match.fighter(0).weapon() == &weapon && match.fighter(1).weapon() == &weapon,
          "both match attackers carry the Rena 0 slot-0 weapon");
    const int hpBefore = match.fighter(1).hp();
    input::PlayerState melee{};
    melee.down[input::Action::AttackA] = true;
    input::PlayerState release{};
    for (int i = 0; i < 20; ++i) {
        input::PlayerState press = melee;
        input::compute_edges(press);
        const input::PlayerState* withMelee[4] = {&press, nullptr, nullptr, nullptr};
        input::PlayerState rest = release;
        input::compute_edges(rest);
        const input::PlayerState* atRest[4] = {&rest, nullptr, nullptr, nullptr};
        match.step(i == 0 ? withMelee : atRest, 1.0 / 64.0);
    }
    checkInt(300, match.fighter(0).attack_move_id(),
             "the match swing resolved move 300");
    checkInt(hpBefore - 8, match.fighter(1).hp(),
             "move 300's recovered 8 HP, not the legacy 5 and not the old 1");
}

// ---------------------------------------------------------------------------
// Every legal combo runs: each character × each shipped NN.dat is paired with
// its own NN weapon slot and survives a 120-tick bout with sane state. The file header
// at +0x114 carries that item id, verified against kWeaponIds (46/46); cross-slot
// pairings are not original game combos and must not be tested as such.
// ---------------------------------------------------------------------------
void testEveryComboRuns(const fs::path& install) {
    section("every character x costume-dat x weapon combo runs");
    std::error_code ec;
    if (install.empty() || !fs::is_directory(install / "data" / "item", ec)) {
        skip("combo sweep (no install found)");
        return;
    }
    int attempted = 0, ran = 0;
    for (int c = 0; c < gameplay::kCharacterCount; ++c) {
        const char* dir = gameplay::kCharacterDirs[c];
        for (int nn = 0; nn < gameplay::weaponCountForCharacter(c); ++nn) {
            char nnname[16];
            std::snprintf(nnname, sizeof(nnname), "%02d.dat", nn);
            gameplay::CharacterMoves moves;
            if (!load_moves(install, dir, nnname, moves)) continue;  // e.g. hanyu 02
            // The file identifies its own weapon (0x114): the NN number IS the
            // slot, so the parsed id must equal this row's id for that slot.
            if (moves.weapon_id() != gameplay::kWeaponIds[c][nn]) {
                std::printf("  JOIN BREAK: %s/%s weapon_id %d != %d\n", dir, nnname,
                            moves.weapon_id(), gameplay::kWeaponIds[c][nn]);
                check(false, "every NN.dat carries its own slot's weapon id");
            }
            const int w = nn;
            const int id = gameplay::kWeaponIds[c][w];
            gameplay::WeaponDefinition weapon;
            if (!load_weapon(install, id, weapon) || weapon.id != id) {
                check(false, "the NN.dat slot's matching item file parses");
                continue;
            }
            ++attempted;
            // Best effort, like the live path: absent files keep shared tuning,
            // and an all-zero parameter decodes to the shared table anyway.
            gameplay::BulletParameter tap, chg;
            load_bullet_params(install, weapon, tap, chg);
            gameplay::Match match;
            gameplay::MatchConfig config;
            config.fighterCount = 2;
            config.side[0] = 0;
            config.side[1] = 1;
            config.spawn[0] = glm::vec3(0, 0, 0);
            config.spawn[1] = glm::vec3(300, 0, 0);
            config.moves[0] = config.moves[1] = &moves;
            config.weapon[0] = config.weapon[1] = &weapon;
            const xm::Model* models[4] = {};
            xm::Controller* anims[4] = {};
            match.reset(config, models, anims, nullptr, nullptr);
            for (int f = 0; f < 2; ++f) {
                match.fighter(f).set_bullet_parameter(1, &tap);
                match.fighter(f).set_bullet_parameter(2, &chg);
            }
            const input::PlayerState* idle[4] = {};
            for (int i = 0; i < 70; ++i) match.step(idle, 1.0 / 64.0);
            for (int tick = 0; tick < 120; ++tick) {
                input::PlayerState p1{}, p2{};
                p1.down[input::Action::Shoot] = true;
                p2.down[input::Action::Shoot] = true;
                if (tick == 0) p1.down[input::Action::AttackA] = true;
                input::compute_edges(p1);
                input::compute_edges(p2);
                const input::PlayerState* in[4] = {&p1, &p2, nullptr, nullptr};
                match.step(in, 1.0 / 64.0);
            }
            const auto& f0 = match.fighter(0);
            const auto& f1 = match.fighter(1);
            const bool sane =
                f0.hp() >= 0 && f0.hp() <= f0.max_hp() &&
                f1.hp() >= 0 && f1.hp() <= f1.max_hp() &&
                f0.main_frac() >= 0.0f && f0.main_frac() <= 1.0f &&
                f0.charge_frac() >= 0.0f && f0.charge_frac() <= 1.0f;
            if (!sane) {
                std::printf("  INSANE: %s with item %03d\n",
                            gameplay::comboSlotLabel(c, w).c_str(), id);
                check(false, "a combo bout stays within sane state");
            } else {
                ++ran;
            }
        }
    }
    std::printf("  combos attempted: %d\n", attempted);
    checkInt(attempted, ran, "every attempted combo ran sane");
    checkInt(46, attempted, "the sweep covers all legal character/item-slot combos");
}

// ---------------------------------------------------------------------------
// Section transitions use the D3DX period rounded by the original loader, a
// strict elapsed > period boundary, and the NN.dat set +0x20 auto-advance gate.
// Controller clip looping stays at the remake default; +0x20 does not establish it.
// ---------------------------------------------------------------------------
void testAnimationPhaseProgression(const fs::path& install) {
    section("animation phases follow D3DX periods and NN.dat gates");
    CombatCombo combo;
    if (!requireCombatCombo(install, combo,
                            "animation phase progression (no install found)")) return;
    checkInt(124, combo.moves->animation_set_count(),
             "Rena 00 trailer has one row per animation set");
    checkInt(0, combo.moves->animation_set_phase_gate(13),
             "dash startup set 13 auto-advances");
    checkInt(1, combo.moves->animation_set_phase_gate(14),
             "dash continuation set 14 is explicitly gated");
    checkInt(0, combo.moves->animation_set_phase_gate(73),
             "attack continuation set 73 auto-advances after event data");

    // A 9,600-key-tick synthetic clip at 4,800 ticks/s has a verified D3DX
    // period of 2 seconds; FUN_0066b668 rounds it to 2 and the source switches
    // only when integer elapsed ticks become greater than 2.
    {
        xm::Model model;
        xm::Controller ctrl;
        Fighter dash;
        bind_synthetic_rig(dash, model, ctrl, glm::vec3(0, 0, 0), 9600.0f);
        dash.set_moves(combo.moves.get());
        dash.set_weapon(&combo.weapon);
        double_tap(dash, input::Action::Up);
        checkInt(13, dash.anim_set_index(), "dash starts on table phase zero");
        check(ctrl.trackLoop(0), "zero +0x20 does not override controller playback mode");
        check(std::abs(ctrl.trackPosition(0)) < 1e-9,
              "a newly selected state starts at position zero");
        input::PlayerState idle;
        tick(dash, idle);
        checkInt(13, dash.anim_set_index(), "period equality does not advance");
        tick(dash, idle);
        checkInt(14, dash.anim_set_index(), "strictly greater elapsed period advances");
        check(ctrl.trackLoop(0), "nonzero +0x20 does not set clip playback mode");
        check(std::abs(ctrl.trackPosition(0)) < 1e-9,
              "the newly bound phase stays at zero on its transition tick");
        tick(dash, idle);
        check(std::abs(ctrl.trackPosition(0) - 1.0 / 64.0) < 1e-9,
              "the bound phase advances on the following stable tick");
        for (int i = 0; i < 10; ++i) tick(dash, idle);
        checkInt(14, dash.anim_set_index(), "nonzero +0x20 gate holds the next phase");
    }

    // FUN_0066b668 uses x87 ROUND, which is nearest-even under the game's default
    // floating-point mode. A half-period of 0.5 rounds to zero, unlike lround().
    {
        xm::Model model;
        xm::Controller ctrl;
        Fighter dash;
        bind_synthetic_rig(dash, model, ctrl, glm::vec3(0, 0, 0));
        model.anims[13].duration = 2400.0f;  // 0.5 seconds at 4,800 ticks/second
        dash.set_moves(combo.moves.get());
        dash.set_weapon(&combo.weapon);
        double_tap(dash, input::Action::Up);
        checkInt(14, dash.anim_set_index(), "nearest-even zero threshold advances on elapsed tick 1");
    }

    // Rena's neutral move 300 has three ungated phase sets. Each new section
    // resets its move-local elapsed counter before another period can expire.
    {
        xm::Model model;
        xm::Controller ctrl;
        Fighter attack;
        bind_synthetic_rig(attack, model, ctrl, glm::vec3(0, 0, 0), 9600.0f);
        attack.set_moves(combo.moves.get());
        attack.set_weapon(&combo.weapon);
        input::PlayerState in;
        in.down[input::Action::AttackA] = true;
        tick(attack, in);
        in.down[input::Action::AttackA] = false;
        checkInt(31, attack.anim_set_index(), "neutral move 300 starts on set 31");
        tick(attack, in);
        checkInt(31, attack.anim_set_index(), "first section holds through period equality");
        tick(attack, in);
        checkInt(73, attack.anim_set_index(), "move 300 advances after the strict boundary");
        check(std::abs(ctrl.trackPosition(0)) < 1e-9,
              "move 300's new phase stays at zero on the switch tick");
        tick(attack, in);
        checkInt(73, attack.anim_set_index(), "next section gets a fresh elapsed counter");
        tick(attack, in);
        checkInt(73, attack.anim_set_index(), "second section also holds at equality");
        tick(attack, in);
        checkInt(74, attack.anim_set_index(), "move 300 advances to its final phase");
    }
}

// FUN_0064c8a0 permits a blend only for Rena's weapon slot 2, from set 1 to
// 31/34/39. Its two countdown values come from the bound NN.dat set rows.
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

// ---------------------------------------------------------------------------
// Up/Down ground dash mappings are port inferences from the directional clip
// families; source input selectors depend on opaque state/cancel fields. Side and
// air-dash animation selectors stay unresolved.
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// Roster variation: the move-table tags are shared where verified (same tags in all
// 16 characters × all NN files — verified by dump, pinned here for keiichi and
// mion), while weapon rows differ per character AND the machine reads whatever
// the bound table says. Attack selectors stay separate from phase-tag facts.
// ---------------------------------------------------------------------------
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
        checkInt(0, dasher.anim_set_index(), "dash animation remains on explicit fallback");
        check(dasher.anim_fallback(), "dash animation fallback is reported");
    }
}

// ---------------------------------------------------------------------------
// Jump's original input/state selector is not located. Physics still runs, but
// animation remains on the reported fallback instead of switching on vy sign.
// ---------------------------------------------------------------------------
void testJumpAnimationFallback(const fs::path& install) {
    section("jump animation remains unresolved without the original selector");
    gameplay::CharacterMoves moves;
    if (!load_moves(install, "rena", "00.dat", moves)) {
        skip("jump animation (no install found)");
        return;
    }
    xm::Model model;
    xm::Controller ctrl;
    Fighter f;
    bind_synthetic_rig(f, model, ctrl, glm::vec3(0, 0, 0));
    f.set_moves(&moves);
    gameplay::WeaponDefinition weapon;
    if (!load_weapon(install, moves.weapon_id(), weapon)) {
        skip("jump animation (matching item unavailable)");
        return;
    }
    f.set_weapon(&weapon);
    input::PlayerState jump;
    jump.down[input::Action::Jump] = true;
    tick(f, jump);
    tick(f, jump);
    checkInt(0, f.anim_set_index(), "unmapped jump uses set 0");
    check(f.anim_fallback(), "unmapped jump reports fallback");
    jump.down[input::Action::Jump] = false;
    for (int i = 0; i < 33; ++i) tick(f, jump);   // vy crosses zero ~tick 26
    check(f.airborne(), "still airborne on the way down");
    checkInt(0, f.anim_set_index(), "fall keeps the unresolved fallback");
    check(f.anim_fallback(), "fall does not imply a recovered move ID");
    for (int i = 0; i < 30; ++i) tick(f, jump);
    checkInt(static_cast<int>(FighterState::Idle), static_cast<int>(f.state()),
             "landing returns to Idle");
    checkInt(0, f.anim_set_index(), "and the idle set comes back");
}

}  // namespace

int main(int argc, char** argv) {
    std::printf("MELEE_RULES_TEST\n");
    const fs::path install = findInstall(argc, argv);
    testVerticalSeparation(install);
    testFacing(install);
    testBarriers(install);
    testMultipleOpponentsAndAllies(install);
    testWindowsAndRecovery(install);
    testHeavyKeyUnbound(install);
    testMatchAllyExclusion(install);
    testCharacterMoveTable(install);
    testDataDrivenGroundSwing(install);
    testDataDrivenDashAndAir(install);
    testDataDrivenFallback(install);
    testMatchDataDriven(install);
    testEveryComboRuns(install);
    testAnimationPhaseProgression(install);
    testClassSpecificAnimationBlend(install);
    testDirectionalDashes(install);
    testRosterVariation(install);
    testJumpAnimationFallback(install);
    std::printf("\nMELEE_RULES: %s (%d checks, %d failed, %d skipped)\n",
                failures == 0 ? "ok" : "FAIL", checks, failures, skipped);
    return failures == 0 ? 0 : 1;
}
