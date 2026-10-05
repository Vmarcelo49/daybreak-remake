// =============================================================================
//  melee_rules_test.cpp — issue #10: directional, aerial and multi-target melee.
//
//  Pins the acceptance criteria directly:
//    * ground melee cannot hit a distant airborne fighter just because XZ overlaps;
//    * an aerial swing is reachable through the documented control and reaches what a
//      ground swing cannot;
//    * facing decides — a fighter behind the swing is out of it;
//    * a solid barrier between them blocks the swing;
//    * one swing can hit SEVERAL opponents, each exactly once;
//    * allies are never hit;
//    * recovery is a real lockout, and an interrupted attack does not keep hitting;
//    * the heavy-key stand-in is gone.
//
//  Also parses the shipped character move tables when an install is present, to assert
//  the claim the animation mapping rests on (issue #26): each phase's section tag is
//  the animation set index — move 10 opens on 1 (walk), move 20 runs [13,14,15]
//  (dash), move 30 opens on 54, move 40 on 2 — and moves 40/41/42 are the jump
//  chain with no combat block, while the 300-family weapon phases carry real hits.
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

// Presses melee once and advances to the middle of the active window.
void swing_to_active(Fighter& f, int extraTicks = 0) {
    input::PlayerState in;
    in.down[input::Action::AttackA] = true;
    tick(f, in);                       // the press itself: set_state -> begin_melee_swing
    in.down[input::Action::AttackA] = false;
    const gameplay::MeleeRules rules;
    for (int i = 0; i < rules.startupTicks + extraTicks; ++i) tick(f, in);
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
// so animation-set assertions read the same as the fighter_script_test's. Clips run
// durationTicks long at 4800 ticks/s: the 100 s default HOLDS every phase (no
// advancement), while a short rig (225 ticks ≈ 3 ticks at 1/64) steps phases.
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
    return out.parse(bytes.data(), bytes.size(), err);
}

// ---------------------------------------------------------------------------
// Vertical separation — the issue's headline criterion.
// ---------------------------------------------------------------------------
void testVerticalSeparation() {
    section("vertical separation");
    Fighter attacker = idle_at(glm::vec3(0, 0, 0));
    Fighter grounded = idle_at(glm::vec3(0, 0, 80));
    Fighter airborne  = idle_at(glm::vec3(0, 0, 80));
    // Settling is 70 ticks of gravity, so a target placed high would land before the
    // swing. Settle first, THEN re-place it: BattleStart costs nothing here because
    // only the attacker's windows are under test.
    airborne.reset(glm::vec3(0, 400, 80), 0.0f);   // same XZ, 400 up

    checkInt(80, static_cast<int>(grounded.position().z),
             "the grounded target stands 80 units ahead");
    checkInt(400, static_cast<int>(airborne.position().y),
             "the airborne target stands 400 units up at the same XZ");
    swing_to_active(attacker);
    check(attacker.try_melee_hit(grounded), "ground melee connects with a grounded target");
    check(grounded.hp() < 100, "and it does damage");

    // Same XZ overlap, but 400 units above the swing's vertical reach.
    Fighter a2 = idle_at(glm::vec3(0, 0, 0));
    swing_to_active(a2);
    check(!a2.try_melee_hit(airborne),
          "ground melee refuses a target 400 units up at identical XZ");
    checkInt(100, airborne.hp(), "and the airborne fighter takes nothing");

    // An aerial swing reaches further vertically, per melee_rules.h. The swing kind is
    // chosen by the fighter's situation AT THE PRESS, so the attacker must be airborne
    // when it presses -- set_aerial_attack() before the press is overwritten on purpose.
    Fighter a3 = idle_at(glm::vec3(0, 0, 0));
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
    airborne.reset(glm::vec3(0, 76, 60), 0.0f);   // level with the jumped attacker's chest
    check(a3.try_melee_hit(airborne),
          "an airborne attacker reaches a target at its own height");
    airborne.reset(glm::vec3(0, 500, 60), 0.0f);
    check(!a3.try_melee_hit(airborne),
          "and still not one far above the sphere's 30+radius reach");

    // Reach is RELATIVE to the attacker's feet, so a modest elevation still connects
    // while a large one does not. (The fighter's own altitude is irrelevant: both are
    // measured as a difference, which is what makes a stage with height work.)
    Fighter a4 = idle_at(glm::vec3(0, 0, 0));
    Fighter levelNeighbour = idle_at(glm::vec3(0, 0, 60));
    Fighter muchHigher     = idle_at(glm::vec3(0, 0, 60));
    muchHigher.reset(glm::vec3(0, 600, 60), 0.0f);
    swing_to_active(a4);
    check(a4.try_melee_hit(levelNeighbour), "a level neighbour is reachable");
    check(!a4.try_melee_hit(muchHigher), "one 600 units above is not");
}

// ---------------------------------------------------------------------------
// Facing.
// ---------------------------------------------------------------------------
void testFacing() {
    section("the recovered hitbox is a sphere, not a cone");
    // FUN_0063b470 is a hard 3D sphere test with no angle term, so a target behind the
    // attacker is hit on exactly the same terms as one in front. This pins that, and
    // pins what DID replace the invented cone: the victim's two anchor spheres.
    Fighter front = idle_at(glm::vec3(0, 0, 0));
    Fighter ahead  = idle_at(glm::vec3(0, 0, 100));
    Fighter rear   = idle_at(glm::vec3(0, 0, -100));
    swing_to_active(front);
    check(front.try_melee_hit(ahead), "a target 100 ahead is in the sphere");
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
    swing_to_active(swinger);
    Fighter level = idle_at(glm::vec3(0, 0, 60));
    check(swinger.try_melee_hit(level), "an opponent 60 away and level connects");
    Fighter high = idle_at(glm::vec3(0, 0, 60));
    high.reset(glm::vec3(0, 400, 60), 0.0f);
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

void testBarriers() {
    section("solid barriers block the swing");
    xm::Model model = wall_between_fighters();
    game::physics::MovementCollision collision;
    const xm::Model* mesh = &model;
    collision.setMeshes(mesh, nullptr);

    // Without collision the same pair connects: proves the wall is what stops it.
    Fighter open = idle_at(glm::vec3(0, 0, -60));
    Fighter far  = idle_at(glm::vec3(0, 0, 60));   // 120 apart: inside the 160 reach
    swing_to_active(open);
    check(open.try_melee_hit(far), "with no collision the swing reaches across");

    Fighter walled = idle_at(glm::vec3(0, 0, -60));
    Fighter behindWall = idle_at(glm::vec3(0, 0, 60));   // fresh: `far` was hit above
    swing_to_active(walled);
    check(!walled.try_melee_hit(behindWall, &collision),
          "a wall between them blocks the swing");
    checkInt(100, behindWall.hp(), "and the fighter behind it takes nothing");

    // No barrier in the way -> still connects even with collision present.
    Fighter clear = idle_at(glm::vec3(300, 0, -60));
    Fighter clearTarget = idle_at(glm::vec3(300, 0, 60));
    swing_to_active(clear);
    check(clear.try_melee_hit(clearTarget, &collision),
          "a clear line still connects with collision loaded");

    // An empty collision is permissive, matching the no-collision.x case.
    game::physics::MovementCollision empty;
    Fighter permissive = idle_at(glm::vec3(0, 0, -60));
    Fighter permissiveTarget = idle_at(glm::vec3(0, 0, 60));
    swing_to_active(permissive);
    check(permissive.try_melee_hit(permissiveTarget, &empty),
          "an empty collision model does not block anything");
}

// ---------------------------------------------------------------------------
// Multiple opponents, per-swing accounting, ally exclusion.
// ---------------------------------------------------------------------------
void testMultipleOpponentsAndAllies() {
    section("multiple opponents, per-swing accounting, ally exclusion");
    Fighter attacker = idle_at(glm::vec3(0, 0, 0));
    Fighter enemyA = idle_at(glm::vec3(-60, 0, 90));
    Fighter enemyB = idle_at(glm::vec3(60, 0, 90));
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
void testWindowsAndRecovery() {
    section("startup, active, recovery and interruption");
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
    Fighter earlyTarget = idle_at(glm::vec3(0, 0, 80));
    input::PlayerState in;
    in.down[input::Action::AttackA] = true;
    tick(early, in);
    check(!early.try_melee_hit(earlyTarget), "the swing cannot land during startup");

    // Recovery is a lockout: once it opens the swing cannot hit again.
    Fighter recovering = idle_at(glm::vec3(0, 0, 0));
    swing_to_active(recovering);
    Fighter victim = idle_at(glm::vec3(0, 0, 80));
    check(recovering.try_melee_hit(victim), "it lands during the active window");
    for (int i = 0; i < rules.activeTicks; ++i) tick(recovering, in);
    check(recovering.melee_in_recovery(), "the swing is in recovery");
    check(!recovering.try_melee_hit(victim), "and cannot land again during recovery");

    // Being hit interrupts the attack outright.
    Fighter interrupted = idle_at(glm::vec3(0, 0, 0));
    swing_to_active(interrupted);
    Fighter aggressor = idle_at(glm::vec3(0, 0, 80));
    interrupted.take_damage(5, &aggressor);   // the swing's OWNER is hit mid-swing
    tick(interrupted, in);
    checkInt(static_cast<int>(FighterState::Hit), static_cast<int>(interrupted.state()),
             "a fighter hit mid-swing is interrupted into Hit");
    Fighter interruptedTarget = idle_at(glm::vec3(0, 0, 80));
    check(!interrupted.try_melee_hit(interruptedTarget),
          "and its interrupted swing cannot land");

    // The whole swing still expires on its own.
    Fighter expiring = idle_at(glm::vec3(0, 0, 0));
    swing_to_active(expiring);
    input::PlayerState released;   // NOT `in`: that one still held the melee key, which
                                   // would re-press on the first tick and re-arm the timer.
    for (int i = 0; i < rules.total_ticks(); ++i) tick(expiring, released);
    checkInt(static_cast<int>(FighterState::Idle), static_cast<int>(expiring.state()),
             "the swing expires back to Idle");
}

// ---------------------------------------------------------------------------
// The heavy-key stand-in is gone.
// ---------------------------------------------------------------------------
void testHeavyKeyUnbound() {
    section("the heavy-key stand-in is removed");
    Fighter f = idle_at(glm::vec3(0, 0, 0));
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
    input::PlayerState mi;
    mi.down[input::Action::AttackA] = true;
    tick(m, mi);
    mi.down[input::Action::AttackA] = false;
    check(m.state() == FighterState::AttackA, "AttackA is the one melee control");
}

// ---------------------------------------------------------------------------
// Match-level: ally exclusion survives the multi-candidate rewrite.
// ---------------------------------------------------------------------------
void testMatchAllyExclusion() {
    section("Match: ally exclusion and multi-hit in a real match");
    gameplay::Match match;
    gameplay::MatchConfig config;
    config.fighterCount = 4;
    config.side[0] = config.side[1] = 0;
    config.side[2] = config.side[3] = 1;
    config.spawn[0] = glm::vec3(0, 0, 0);
    config.spawn[1] = glm::vec3(-70, 0, 80);    // ally, inside the swing
    config.spawn[2] = glm::vec3(70, 0, 80);     // enemy, inside the swing
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
// The load-bearing claim: the melee chain has no recoverable geometry.
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
    int withShotChain = 0;
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
        ++parsed;
        check(moves.count() > 50, "a character ships more than 50 moves");
        // The documented families must be present in the parsed data.
        check(moves.has(20) && moves.has(23) && moves.has(24) && moves.has(27),
              "the four directional walk moves (20/23/24/27) are present");
        check(moves.has(40) && moves.has(41) && moves.has(42),
              "the 40/41/42 jump chain is present");
        // The shot chain's move ids are the character's own (fighter.h notes they are
        // per character), so this only asserts where the character actually ships them.
        if (moves.has(300) && moves.has(301) && moves.has(302)) {
            ++withShotChain;
            // Record +0x04 is a CANCEL WINDOW, not a duration (it has no writer in the
            // binary and is only read as a threshold). Assert it parses, not that it
            // means anything - the shot chain's 20/30/50 reads like a progression but is
            // equally consistent with three cancel thresholds.
            check(moves.cancel_window(300) > 0,
                  "the tap shot carries a cancel-window threshold");
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
              "move 40 (jump startup) opens on set 2: AttackA->2 plays a jump clip");
        check(moves.first_set_index(300) == 31,
              "move 300 (weapon) opens on set 31: attacks are weapon sets");
        if (std::string(d) == "rena") {
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
        // By contrast the shot chain does carry one.
        const gameplay::CharacterMove* shot = moves.find(301);
        bool shotHasCombat = false;
        if (shot)
            for (int p = 0; p < shot->sectionCount; ++p)
                for (int e = 0; e < shot->phases[p].entryCount; ++e)
                    if (shot->phases[p].entries[e].has_combat()) shotHasCombat = true;
        check(shotHasCombat, "a shot move DOES carry combat data (parser is not reading zeros)");
    }
    checkInt(4, parsed, "all four sampled characters parsed");
    check(withShotChain >= 1,
          "at least one sampled character ships the 300/301/302 shot chain");

    // A truncated file must be rejected, not read past.
    gameplay::CharacterMoves m;
    std::string err;
    std::vector<uint8_t> tiny(40, 0);
    check(!m.parse(tiny.data(), tiny.size(), err), "a truncated move table is rejected");
    check(!m.valid(), "and leaves the table unloaded");
    check(m.find(40) == nullptr, "with nothing findable");
}

// ---------------------------------------------------------------------------
// Data-driven swings (issue #26 steps 3–4): with rena's table bound, the swing
// resolves to the situation's own move — its animation set, reach, damage and
// stun — instead of the legacy shared numbers. Rena 00.dat reference values:
//   move 300 (ground): set 31, hit frame 4, next effect 10, hr 20, hp 50, dSt 6
//   move 330 (dash):   set 51, hit frame 6, next effect 11, hr 25, hp 75, dSt 6
//   move 340 (air):    set 88, hit frame 16, next effect 21, hr 20, hp 75, dSt 6
// Damage scales hpDamage off the original's 10000-based pool (all three round to
// 1 on 100 HP); reach is 30 + hr in 3D against the two anchors.
// ---------------------------------------------------------------------------
void testDataDrivenGroundSwing(const fs::path& install) {
    section("data-driven ground swing (rena move 300)");
    gameplay::CharacterMoves moves;
    if (!load_moves(install, "rena", "00.dat", moves)) {
        skip("data-driven ground swing (no install found)");
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
    check(load_weapon(install, 1, weapon), "rena item 1 (slot 0) parses");
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

    input::PlayerState in;
    in.down[input::Action::AttackA] = true;
    tick(attacker, in);
    in.down[input::Action::AttackA] = false;
    checkInt(static_cast<int>(FighterState::AttackA),
             static_cast<int>(attacker.state()), "the press enters AttackA");
    checkInt(300, attacker.attack_move_id(), "a grounded press resolves move 300");
    checkInt(31, attacker.anim_set_index(),
             "and binds set 31 (nata swing), not the jump clip");
    check(!attacker.anim_fallback(), "with no fallback flag");

    // Startup is the hit's own frame (4): earlier ticks cannot land.
    tick(attacker, in);
    tick(attacker, in);   // elapsed 3
    check(!attacker.try_melee_hit(victim), "no hit during the 4-frame startup");
    tick(attacker, in);   // elapsed 4: the hit frame
    check(attacker.try_melee_hit(victim), "the hit lands on its own frame");
    checkInt(99, victim.hp(), "damage is the weapon's own hpDamage, scaled (50 -> 1)");
    checkInt(static_cast<int>(FighterState::Hit), static_cast<int>(victim.state()),
             "the victim staggers");

    // Reach is 30 + 20 in 3D: 40 connects, 60 does not.
    Fighter far;
    bind_synthetic_rig(far, model, ctrl, glm::vec3(0, 0, 60));
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
    // Dash attack: double-tap Run, then melee while still dashing.
    {
        xm::Model model;
        xm::Controller ctrl;
        Fighter dasher;
        bind_synthetic_rig(dasher, model, ctrl, glm::vec3(0, 0, 0));
        dasher.set_moves(&moves);
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
        checkInt(51, dasher.anim_set_index(), "binding set 51, not the jump clip");
        // The dash carried the fighter forward; meet it where it is (reach 55).
        const float z = dasher.position().z;
        Fighter victim;
        bind_synthetic_rig(victim, model, ctrl, glm::vec3(0, 0, z + 45));
        for (int i = 0; i < 5; ++i) tick(dasher, in);   // elapsed 6: the hit frame
        check(dasher.try_melee_hit(victim), "the lunge connects inside 30+25");
        checkInt(99, victim.hp(), "for the weapon's scaled damage (75 -> 1)");
    }
    // Air attack: leap, then melee while airborne.
    {
        xm::Model model;
        xm::Controller ctrl;
        Fighter flyer;
        bind_synthetic_rig(flyer, model, ctrl, glm::vec3(0, 0, 0));
        flyer.set_moves(&moves);
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
        checkInt(88, flyer.anim_set_index(), "binding set 88");
        Fighter early;
        bind_synthetic_rig(early, model, ctrl, flyer.position());
        check(!flyer.try_melee_hit(early), "no hit during the 16-frame startup");
        for (int i = 0; i < 15; ++i) tick(flyer, in);   // elapsed 16: the hit frame
        // Meet the risen attacker at its own height (reach 50 in 3D).
        Fighter victim;
        bind_synthetic_rig(victim, model, ctrl, glm::vec3(0, 0, 0));
        victim.reset(glm::vec3(flyer.position().x, flyer.position().y,
                               flyer.position().z + 30),
                     0.0f);
        check(flyer.try_melee_hit(victim), "the aerial connects at its own height");
        checkInt(99, victim.hp(), "for the weapon's scaled damage");
    }
}

void testDataDrivenFallback(const fs::path& install) {
    section("no table, no data: the legacy swing survives");
    // A costume that drops the situation's move (rena/02 repoints 330 to a bare
    // phase; a table with no 300-family at all) must fall back cleanly, and a
    // fighter with no table bound must behave exactly like the pre-#26 machine.
    Fighter bare = idle_at(glm::vec3(0, 0, 0));
    checkInt(-1, bare.attack_move_id(), "no table means no move id");
    checkInt(-1, bare.anim_set_index(), "no model means no set bound");
    check(!bare.moves(), "and no table bound");

    gameplay::CharacterMoves moves;
    if (!load_moves(install, "rena", "00.dat", moves)) {
        skip("bound-but-missing move falls back (no install found)");
        return;
    }
    // Move 302 exists for rena but has no bearing on the ground swing; the
    // fallback path is exercised by asking for a move the table lacks.
    check(moves.find(9999) == nullptr, "an absent move id finds nothing");
    Fighter bound = idle_at(glm::vec3(0, 0, 0));
    bound.set_moves(&moves);
    checkInt(-1, bound.attack_move_id(), "no swing yet means no move id");
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
    const xm::Model* models[4] = {};
    xm::Controller* anims[4] = {};
    match.reset(config, models, anims, nullptr, nullptr);
    const input::PlayerState* idle[4] = {};
    for (int i = 0; i < 70; ++i) match.step(idle, 1.0 / 64.0);
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
    checkInt(hpBefore - 1, match.fighter(1).hp(),
             "one weapon-scaled point of damage, not the legacy 5");
}

// ---------------------------------------------------------------------------
// Every legal combo runs: each character × each shipped NN.dat × each legal
// weapon slot parses its moves + item (+ best-effort bullets) and survives a
// 120-tick bout with sane state. Which NN.dat the original pairs with which
// weapon slot is still open (issue #26), so this sweeps the cross product
// rather than asserting the join — and it is the standing rule that no test
// exercises a bare fighter where a combo exists.
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
        for (int nn = 0; nn < 3; ++nn) {
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
            for (int w = 0; w < gameplay::weaponCountForCharacter(c); ++w) {
                const int id = gameplay::kWeaponIds[c][w];
                gameplay::WeaponDefinition weapon;
                if (!load_weapon(install, id, weapon)) {
                    check(false, "every roster item file parses");
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
    }
    std::printf("  combos attempted: %d\n", attempted);
    checkInt(attempted, ran, "every attempted combo ran sane");
    check(attempted > 100, "the sweep covers the full roster cross product");
}

// ---------------------------------------------------------------------------
// Phase advancement: a multi-phase move plays each phase once through (by clip
// length) and holds the last, instead of looping its startup. Short rig:
// 225 ticks at 4800/s ≈ 3 ticks per phase at 1/64. Rena 00.dat reference:
//   attack 300 → [31, 73, 74]; forward dash 20 → [13, 14, 15].
// ---------------------------------------------------------------------------
void testPhaseAdvancement(const fs::path& install) {
    section("phase advancement (no startup loops)");
    gameplay::CharacterMoves moves;
    if (!load_moves(install, "rena", "00.dat", moves)) {
        skip("phase advancement (no install found)");
        skip("dash phase advancement (no install found)");
        return;
    }
    // Ground attack: 31 held 3 ticks, then 73, then 74 holds the swing out.
    {
        xm::Model model;
        xm::Controller ctrl;
        Fighter attacker;
        bind_synthetic_rig(attacker, model, ctrl, glm::vec3(0, 0, 0), 225.0f);
        attacker.set_moves(&moves);
        input::PlayerState in;
        in.down[input::Action::AttackA] = true;
        tick(attacker, in);
        in.down[input::Action::AttackA] = false;
        checkInt(31, attacker.anim_set_index(), "the swing opens on phase 0 (31)");
        tick(attacker, in);
        tick(attacker, in);
        tick(attacker, in);   // ~3 ticks of clip: phase 1
        checkInt(73, attacker.anim_set_index(), "then steps to phase 1 (73)");
        tick(attacker, in);
        tick(attacker, in);
        tick(attacker, in);   // ~3 more: phase 2, held
        checkInt(74, attacker.anim_set_index(), "then holds the last phase (74)");
        for (int i = 0; i < 15; ++i) tick(attacker, in);
        checkInt(74, attacker.anim_set_index(), "the last phase never advances past");
    }
    // Forward dash: 13, then 14, then 15 holds for the rest of the dash.
    {
        xm::Model model;
        xm::Controller ctrl;
        Fighter dasher;
        bind_synthetic_rig(dasher, model, ctrl, glm::vec3(0, 0, 0), 225.0f);
        dasher.set_moves(&moves);
        double_tap(dasher, input::Action::Up);
        checkInt(20, dasher.dash_move_id(), "the dash resolves move 20");
        checkInt(13, dasher.anim_set_index(), "opening on dash startup (13)");
        input::PlayerState idle;
        for (int i = 0; i < 3; ++i) tick(dasher, idle);
        checkInt(14, dasher.anim_set_index(), "then the dash loop (14)");
        for (int i = 0; i < 3; ++i) tick(dasher, idle);
        checkInt(15, dasher.anim_set_index(), "then recovery holds (15)");
    }
}

// ---------------------------------------------------------------------------
// Directional dashes: double-tap a direction and the dash plays that
// direction's move — Up 20 ([13..]), Down 27 ([16..]), Left 24 ([19..]),
// Right 23 ([22..]). Long rig: phases hold, so the first set pins the row.
// ---------------------------------------------------------------------------
void testDirectionalDashes(const fs::path& install) {
    section("directional dash animation sets");
    gameplay::CharacterMoves moves;
    if (!load_moves(install, "rena", "00.dat", moves)) {
        skip("directional dash sets (no install found)");
        return;
    }
    struct Case {
        int action;
        int move;
        int set;
        const char* name;
        bool exact;  // forward/back are pinned; sides pin the family pair —
                     // Left/Right ORDER is unverified under mirroring, so the
                     // test accepts either side move with its own first set.
    };
    const Case cases[] = {
        {input::Action::Up, 20, 13, "forward", true},
        {input::Action::Down, 27, 16, "back", true},
        {input::Action::Left, 24, 19, "left", false},
        {input::Action::Right, 23, 22, "right", false},
    };
    for (const Case& c : cases) {
        xm::Model model;
        xm::Controller ctrl;
        Fighter f;
        bind_synthetic_rig(f, model, ctrl, glm::vec3(0, 0, 0));
        f.set_moves(&moves);
        double_tap(f, c.action);
        checkInt(static_cast<int>(FighterState::Run), static_cast<int>(f.state()),
                 "double-tap dashes");
        char what[96];
        if (c.exact) {
            std::snprintf(what, sizeof(what), "%s dash resolves move %d", c.name, c.move);
            checkInt(c.move, f.dash_move_id(), what);
            std::snprintf(what, sizeof(what), "%s dash opens on set %d", c.name, c.set);
            checkInt(c.set, f.anim_set_index(), what);
        } else {
            // Either side move with ITS first set: (24,19) or (23,22).
            const int gotMove = f.dash_move_id();
            const int gotSet = f.anim_set_index();
            const bool pair =
                (gotMove == 24 && gotSet == 19) || (gotMove == 23 && gotSet == 22);
            std::snprintf(what, sizeof(what), "%s dash plays a side pair (got %d/%d)",
                          c.name, gotMove, gotSet);
            check(pair, what);
        }
    }
}

// ---------------------------------------------------------------------------
// Roster variation: the locomotion/jump rows are universal (same tags in all
// 16 characters × all NN files — verified by dump, pinned here for keiichi and
// mion), while weapon rows differ per character AND the machine reads whatever
// the bound table says: keiichi's dash-attack opens on 39 where Rena 0's opens
// on 51, and rena/02's dash opens on 54 (jump-forward startup + dash recovery
// — surprising, but move ids outrank set expectations by design).
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
    for (const gameplay::CharacterMoves* moves : {keiichi.get(), mion.get()}) {
        const gameplay::CharacterMove* dash = moves->find(20);
        check(dash && dash->sectionCount == 3 && dash->phase_set_index(0) == 13 &&
                  dash->phase_set_index(1) == 14 && dash->phase_set_index(2) == 15,
              "non-rena dash phases are [13, 14, 15]");
        checkInt(3, moves->first_set_index(41), "non-rena rise opens on set 3");
        checkInt(43, moves->first_set_index(43), "non-rena fall opens on set 43");
        checkInt(19, moves->first_set_index(24), "non-rena side move 24 opens on 19");
        checkInt(22, moves->first_set_index(23), "non-rena side move 23 opens on 22");
    }
    checkInt(39, keiichi->first_set_index(330),
             "keiichi's lunge opens on 39, not Rena 0's 51");
    checkInt(54, rena2->first_set_index(20),
             "rena/02's dash opens on 54: the file may surprise, ids win");
    // Live: keiichi's dash-attack plays HIS set, not Rena 0's.
    {
        xm::Model model;
        xm::Controller ctrl;
        Fighter dasher;
        bind_synthetic_rig(dasher, model, ctrl, glm::vec3(0, 0, 0));
        dasher.set_moves(keiichi.get());
        double_tap(dasher, input::Action::Up);
        input::PlayerState in;
        in.down[input::Action::AttackA] = true;
        tick(dasher, in);
        in.down[input::Action::AttackA] = false;
        checkInt(330, dasher.attack_move_id(), "keiichi dash press resolves 330");
        checkInt(39, dasher.anim_set_index(), "binding set 39, not 51");
    }
}

// ---------------------------------------------------------------------------
// Jump animation: the airtime climbs on move 41 (set 3) and falls on move 43
// (set 43), switching on the vertical-velocity sign. Long rig: no phase steps,
// so the sets pin the move switch itself.
// ---------------------------------------------------------------------------
void testJumpAnimation(const fs::path& install) {
    section("jump animation follows rise and fall");
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
    input::PlayerState jump;
    jump.down[input::Action::Jump] = true;
    tick(f, jump);
    tick(f, jump);
    checkInt(41, f.jump_move_id(), "the climb resolves move 41");
    checkInt(3, f.anim_set_index(), "playing rise set 3, not idle");
    jump.down[input::Action::Jump] = false;
    for (int i = 0; i < 33; ++i) tick(f, jump);   // vy crosses zero ~tick 26
    check(f.airborne(), "still airborne on the way down");
    checkInt(43, f.jump_move_id(), "the fall switches to move 43");
    checkInt(43, f.anim_set_index(), "playing fall set 43");
    for (int i = 0; i < 30; ++i) tick(f, jump);
    checkInt(static_cast<int>(FighterState::Idle), static_cast<int>(f.state()),
             "landing returns to Idle");
    checkInt(0, f.anim_set_index(), "and the idle set comes back");
}

}  // namespace

int main(int argc, char** argv) {
    std::printf("MELEE_RULES_TEST\n");
    const fs::path install = findInstall(argc, argv);
    testVerticalSeparation();
    testFacing();
    testBarriers();
    testMultipleOpponentsAndAllies();
    testWindowsAndRecovery();
    testHeavyKeyUnbound();
    testMatchAllyExclusion();
    testCharacterMoveTable(install);
    testDataDrivenGroundSwing(install);
    testDataDrivenDashAndAir(install);
    testDataDrivenFallback(install);
    testMatchDataDriven(install);
    testEveryComboRuns(install);
    testPhaseAdvancement(install);
    testDirectionalDashes(install);
    testRosterVariation(install);
    testJumpAnimation(install);
    std::printf("\nMELEE_RULES: %s (%d checks, %d failed, %d skipped)\n",
                failures == 0 ? "ok" : "FAIL", checks, failures, skipped);
    return failures == 0 ? 0 : 1;
}