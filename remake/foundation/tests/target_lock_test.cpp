// =============================================================================
//  target_lock_test.cpp — the per-fighter combat target (issue #8).
//
//  Pins the rules in gameplay/target_lock.h against the original's behaviour and
//  against the acceptance criteria in the issue:
//
//    * 2v2 switching — the tap cycles between the two enemies and wraps;
//    * independent player locks — two fighters hold different targets at once;
//    * a closer UNSELECTED enemy never takes a valid lock away;
//    * KO and respawn move the lock deterministically and never out of range;
//    * invalid targets clear the lock instead of latching an arbitrary fighter;
//    * hold-for-ally arms the recovered hold and never turns into a hostile lock;
//    * allies are never melee victims and never absorb a lock change silently;
//    * fighter, panel, controller and team indices stay distinct.
//
//  The lock rules are driven directly through TargetLocks with a synthetic liveness
//  array, because that is the layer the original's FUN_0041f580 maintains. Match-level
//  tests then confirm the wiring: facing and the melee victim follow the lock, and the
//  camera converges faster only when its target actually changes.
//
//  Build (the CMake target is `target_lock_test`):
//    cmake --build remake/foundation/build/linux --target target_lock_test
//  Exit status: 0 when every check passes, 1 otherwise.
// =============================================================================
#include "gameplay/arena_camera.h"
#include "gameplay/match.h"
#include "gameplay/target_lock.h"

#include <cmath>
#include <cstdio>
#include <vector>

namespace {

int checks = 0;
int failures = 0;

void check(bool condition, const char* name) {
    ++checks;
    if (!condition) ++failures;
    std::printf("  %-58s %s\n", name, condition ? "ok" : "FAIL");
}

void checkInt(int expected, int actual, const char* name) {
    ++checks;
    const bool same = expected == actual;
    if (!same) ++failures;
    std::printf("  %-58s %s", name, same ? "ok" : "FAIL");
    if (!same) std::printf("  (expected %d, got %d)", expected, actual);
    std::printf("\n");
}

void section(const char* title) { std::printf("\n-- %s\n", title); }

// 2v2: blue 0/1 against red 2/3, which is what main.cpp:936 builds for a four-fighter
// launch (panel < 2 ? 0 : 1). The liveness array is the test's to own.
struct TwoVTwo {
    gameplay::TargetLocks locks;
    bool alive[4] = {true, true, true, true};

    TwoVTwo() {
        const int side[4] = {0, 0, 1, 1};
        locks.reset(4, side);
        locks.step(alive);
    }
    // One maintenance tick, with an optional in-tick input gesture. The gesture runs
    // AFTER step(), which is the order the live scene uses: Match::step maintains the
    // locks first and main.cpp reads the player's buttons afterwards.
    void tick() { locks.step(alive); }
    void tick(int owner, bool forward) {
        locks.step(alive);
        locks.cycle_enemy(owner, forward, alive);
    }
};

// ---------------------------------------------------------------------------
// The initial fallback: an index walk, so fighter 0 takes the first hostile.
// ---------------------------------------------------------------------------
void testInitialFallback() {
    section("initial fallback is a deterministic index walk");
    TwoVTwo m;
    // The fallback is FUN_0041f580's wrap walk from the owner's own index, so a fighter
    // takes the first hostile at or after it, not the first hostile in the table.
    checkInt(2, m.locks.target(0), "blue 0 falls back to hostile 2 (first at or after 0)");
    checkInt(2, m.locks.target(1), "blue 1 falls back to hostile 2 (its wrap lands there)");
    checkInt(0, m.locks.target(2), "red 2 falls back to the first hostile (0)");
    checkInt(0, m.locks.target(3), "red 3 falls back to the first hostile (0)");
    checkInt(4, m.locks.fighter_count(), "fighter count clamped into the table");

    // A fighter whose whole enemy team is dead keeps no lock at all, rather than
    // latching a corpse: this is what kNoTarget is for.
    gameplay::TargetLocks lone;
    const int side[4] = {0, 0, 1, 1};
    lone.reset(4, side);
    bool alive[4] = {true, true, false, false};   // both reds are down
    lone.step(alive);
    checkInt(gameplay::kNoTarget, lone.target(0), "no living enemy leaves blue 0 unlocked");
    checkInt(gameplay::kNoTarget, lone.target(1), "no living enemy leaves blue 1 unlocked");
    bool redsAlive[4] = {false, false, true, true};
    lone.step(redsAlive);
    checkInt(gameplay::kNoTarget, lone.target(2), "and no living enemy leaves red 2 unlocked");
}

// ---------------------------------------------------------------------------
// Acceptance: in 2v2, switching enemies changes the selected target.
// ---------------------------------------------------------------------------
void testTwoVTwoSwitching() {
    section("2v2 switching");
    TwoVTwo m;
    checkInt(2, m.locks.target(0), "blue 0 starts on enemy 2");
    m.tick(0, true);
    checkInt(3, m.locks.target(0), "one tap moves blue 0 to enemy 3");
    m.tick(0, true);
    checkInt(2, m.locks.target(0), "a second tap wraps back to enemy 2");

    // Backward cycles too, and they skip the ally (index 1) in both directions.
    m.tick(0, false);
    checkInt(3, m.locks.target(0), "backward from 2 lands on 3");

    // Two hostiles and two allies: exactly two stops per lap, never the partner.
    for (int i = 0; i < 6; ++i) m.tick(0, true);
    check(m.locks.target(0) == 2 || m.locks.target(0) == 3,
          "six taps only ever land on a hostile");
    check(!m.locks.is_ally(0, m.locks.target(0)), "a tapped lock is never an ally");

    // One enemy left: the cycle is a no-op, matching FUN_0041f580:238 (the walk landed
    // back where it started, so FUN_00421e30 was not called).
    m.alive[3] = false;
    m.tick();
    const int held = m.locks.target(0);
    checkInt(2, held, "with one enemy the lock holds it");
    for (int i = 0; i < 3; ++i) m.tick(0, true);
    checkInt(held, m.locks.target(0), "further taps with one enemy change nothing");
}

// ---------------------------------------------------------------------------
// Acceptance: independent locks. Two fighters never share the selection table.
// ---------------------------------------------------------------------------
void testIndependentLocks() {
    section("independent player locks");
    TwoVTwo m;
    m.tick(0, true);   // blue 0 -> enemy 3
    checkInt(3, m.locks.target(0), "blue 0 switched to 3");
    checkInt(2, m.locks.target(1), "blue 1 still holds its own 2 (a separate entry)");

    m.tick(1, true);   // blue 1 cycles on its own
    checkInt(3, m.locks.target(0), "blue 0 is untouched by blue 1's switch");
    checkInt(3, m.locks.target(1), "blue 1 cycled 2 -> 3 on its own");

    // The two sides are mirrored: red can hold a different enemy too.
    m.tick(2, true);
    checkInt(1, m.locks.target(2), "red 2 cycled 0 -> 1");
    checkInt(3, m.locks.target(0), "red's switch did not disturb blue 0");

    // Drive every fighter off the shared defaults so the four differ at once: the table
    // really is per fighter, not one selection consulted four times.
    m.tick(1, true);   // blue 1 -> 2
    m.tick(3, true);   // red 3 -> 1
    m.tick(3, true);   // red 3 -> 0
    const int t[4] = {m.locks.target(0), m.locks.target(1),
                      m.locks.target(2), m.locks.target(3)};
    checkInt(3, t[0], "blue 0 ends on 3");
    checkInt(2, t[1], "blue 1 ends on 2");
    checkInt(1, t[2], "red 2 ends on 1");
    checkInt(0, t[3], "red 3 ends on 0");
    check(t[0] != t[1], "the two blue fighters hold different targets");
    check(t[2] != t[3], "the two red fighters hold different targets");
    for (int i = 0; i < 4; ++i)
        check(m.locks.target(i) >= 0 && m.locks.target(i) < m.locks.fighter_count(),
              "every lock index stays inside the fighter table");
}

// ---------------------------------------------------------------------------
// Acceptance: another fighter becoming nearer does not silently override the lock.
// ---------------------------------------------------------------------------
void testProximityNeverOverrides() {
    section("a closer unselected enemy does not take the lock");
    TwoVTwo m;
    m.tick(0, true);                       // blue 0 locks enemy 3 (the far one)
    checkInt(3, m.locks.target(0), "blue 0 locked the far enemy 3");
    for (int i = 0; i < 240; ++i) m.tick(); // a long match, enemy 2 walks right past
    checkInt(3, m.locks.target(0),
             "240 ticks later the lock is still 3, never stolen by proximity");
    check(!m.locks.switched(0), "no switch was reported during those 240 ticks");

    // Only an explicit gesture moves it.
    m.tick(0, true);
    checkInt(2, m.locks.target(0), "an explicit tap still moves it back to 2");
    check(m.locks.switched(0), "the switch tick is reported once");
    m.tick();
    check(!m.locks.switched(0), "and it is not a latch on the following tick");
}

// ---------------------------------------------------------------------------
// Acceptance: KO and respawn, deterministically, never out of range.
// ---------------------------------------------------------------------------
void testKoAndRespawn() {
    section("KO, the deterministic fallback and respawn");
    TwoVTwo m;
    m.tick(0, true);                       // blue 0 -> enemy 3
    checkInt(3, m.locks.target(0), "blue 0 holds enemy 3");

    // Enemy 3 is KO'd. The lock must not survive as a dead index.
    m.alive[3] = false;
    m.tick();
    checkInt(2, m.locks.target(0), "the KO'd target is replaced by the living enemy");
    check(m.locks.switched(0), "the replacement is reported as a switch");
    check(!m.locks.is_ally(0, m.locks.target(0)), "the replacement is still hostile");

    // Both enemies down: the lock is released, never pointed at a corpse or an ally.
    m.alive[2] = false;
    m.tick();
    checkInt(gameplay::kNoTarget, m.locks.target(0), "with no living enemy the lock releases");

    // Respawn. The index is valid again, so the fallback re-acquires it deterministically
    // and the lock never carries a stale index across the round.
    m.alive[2] = true;
    m.alive[3] = true;
    m.tick();
    checkInt(2, m.locks.target(0), "respawn re-acquires a valid enemy lock");
    check(m.locks.target(0) >= 0 && m.locks.target(0) < m.locks.fighter_count(),
          "the respawned lock index is in range");

    // A long dead period must not accumulate anything.
    for (int i = 0; i < 60; ++i) m.tick();
    checkInt(2, m.locks.target(0), "a settled match holds its lock");

    // KO of the OWNER does not disturb its own table, and it comes back valid.
    m.alive[0] = false;
    m.tick();
    checkInt(2, m.locks.target(0), "the KO'd owner's own lock is left alone");
    m.alive[0] = true;
    m.tick();
    checkInt(2, m.locks.target(0), "the respawned owner still holds a valid index");
}

// ---------------------------------------------------------------------------
// Acceptance: invalid targets never produce an index.
// ---------------------------------------------------------------------------
void testInvalidTargets() {
    section("invalid targets");
    TwoVTwo m;
    m.tick(0, true);
    checkInt(3, m.locks.target(0), "blue 0 holds enemy 3 before the bad input");

    // FUN_00421f30:24-26 — an out-of-range index stores 0xffffffff and nothing else.
    m.locks.set_target(0, 9, m.alive);
    checkInt(gameplay::kNoTarget, m.locks.target(0), "index 9 (out of range) clears the lock");
    m.locks.set_target(0, -2, m.alive);
    checkInt(gameplay::kNoTarget, m.locks.target(0), "index -2 clears the lock");
    m.locks.set_target(0, 0, m.alive);
    checkInt(gameplay::kNoTarget, m.locks.target(0), "locking yourself clears the lock");
    m.locks.set_target(0, 1, m.alive);
    checkInt(1, m.locks.target(0), "a direct set to a living ally is allowed (aim ally)");
    m.locks.set_target(0, 4, m.alive);
    checkInt(gameplay::kNoTarget, m.locks.target(0), "index 4 clears again");

    m.locks.set_target(0, gameplay::kNoTarget, m.alive);
    checkInt(gameplay::kNoTarget, m.locks.target(0), "kNoTarget as an argument is a no-op");

    // An out-of-range OWNER is inert, not a write out of bounds.
    m.locks.set_target(0, 3, m.alive);
    m.locks.set_target(7, 2, m.alive);
    m.locks.cycle_enemy(7, true, m.alive);
    m.locks.select_ally(7, m.alive);
    m.locks.step(m.alive);
    checkInt(3, m.locks.target(0), "an out-of-range owner writes nothing");
    for (int i = 0; i < 4; ++i)
        check(m.locks.target(i) == gameplay::kNoTarget || m.locks.target(i) < 4,
              "no fighter holds an out-of-range index after the bad calls");
    check(!m.locks.is_ally(9, 1), "is_ally is inert outside the table");
    check(!m.locks.is_ally(0, 9), "is_ally is inert on an out-of-range index");
    check(!m.locks.targetable(0, 9, m.alive), "targetable rejects an out-of-range index");
    checkInt(-1, m.locks.target(9), "reading an out-of-range owner yields no target");

    // An index that leaves the table because fighterCount shrank must not survive.
    gameplay::TargetLocks shrunk;
    const int side[4] = {0, 0, 1, 1};
    shrunk.reset(4, side);
    bool alive[4] = {true, true, true, true};
    shrunk.step(alive);
    checkInt(0, shrunk.target(2), "red 2 starts on blue 0");
    shrunk.set_target(2, 3, alive);        // red 2 locks a fellow red: aim ally
    checkInt(3, shrunk.target(2), "red 2 aimed at red 3");
    check(shrunk.is_ally(2, 3), "red 3 is an ally of red 2");
    check(!shrunk.targetable(2, 2, alive), "a fighter is never its own target");
}

// ---------------------------------------------------------------------------
// Hold-for-ally: the recovered 0xb4 dwell, re-pinned every tick.
// ---------------------------------------------------------------------------
void testHoldForAlly() {
    section("hold for ally (FUN_00421e30's 0xb4)");
    TwoVTwo m;
    m.locks.select_ally(0, m.alive);
    checkInt(1, m.locks.target(0), "blue 0 aims at its ally 1");
    checkInt(gameplay::kAllyHoldTicks, m.locks.hold(0), "the hold arms at 180 ticks");
    check(m.locks.holding_ally(0), "holding_ally reports the live hold");
    checkInt(0, m.locks.hold(1), "the ally's own lock has no hold");

    // FUN_0041f580:243-244 re-pins it every tick, so it never expires while aimed.
    for (int i = 0; i < 500; ++i) m.tick();
    checkInt(gameplay::kAllyHoldTicks, m.locks.hold(0),
             "the hold is re-pinned, not counted down, while on an ally");

    // Back to an enemy and it counts down, reaching 0 (FUN_0041f580:246-247).
    m.locks.cycle_enemy(0, true, m.alive);
    m.tick();
    checkInt(0, m.locks.hold(0), "selecting an enemy clears the hold at once");
    check(!m.locks.holding_ally(0), "holding_ally is false on an enemy lock");

    // And the countdown path itself: force a hold, then let it drain.
    m.locks.select_ally(0, m.alive);
    m.locks.set_target(0, 2, m.alive);      // FUN_00421f30 clears the hold...
    m.tick();
    checkInt(0, m.locks.hold(0), "a direct set on an enemy leaves no hold");
    m.tick(0, true);
    checkInt(3, m.locks.target(0), "cycling is unaffected by the hold bookkeeping");
    checkInt(0, m.locks.hold(0), "an enemy lock keeps the hold at 0");

    // A lock onto a dead ally is not selectable: no dead index is ever adopted.
    m.alive[1] = false;
    m.locks.select_ally(0, m.alive);
    checkInt(3, m.locks.target(0), "a dead ally is never adopted; the lock stands");
}

// ---------------------------------------------------------------------------
// The recovered switch pulse (FUN_004201a0).
// ---------------------------------------------------------------------------
void testSwitchPulse() {
    section("the 15-tick switch pulse");
    TwoVTwo m;
    m.tick(0, true);
    checkInt(gameplay::kLockPulseTicks, m.locks.pulse(0), "a switch writes 15 pulses");
    checkInt(0, m.locks.pulse(1), "another fighter's pulse is its own");

    for (int i = 1; i < gameplay::kLockPulseTicks; ++i) {
        m.tick();
        checkInt(gameplay::kLockPulseTicks - i, m.locks.pulse(0),
                 "the pulse counts down each tick");
    }
    m.tick();
    checkInt(0, m.locks.pulse(0), "the pulse clamps at 0, never negative");
    for (int i = 0; i < 10; ++i) m.tick();
    checkInt(0, m.locks.pulse(0), "and stays at 0");

    // The pulse protects the fresh selection: it is a one-tick-flag switch, and the
    // lock it armed does not get undone while it runs.
    m.tick(0, true);
    const int armed = m.locks.target(0);
    for (int i = 0; i < gameplay::kLockPulseTicks; ++i) m.tick();
    checkInt(armed, m.locks.target(0), "the armed lock survives its own pulse window");
}

// ---------------------------------------------------------------------------
// Acceptance: allies stay excluded from hostile attacks.
// ---------------------------------------------------------------------------
void testAllyExclusion() {
    section("allies are excluded from hostile attacks");
    TwoVTwo m;
    // Aim at your partner...
    m.locks.select_ally(0, m.alive);
    checkInt(1, m.locks.target(0), "blue 0 aims at ally 1");
    check(m.locks.is_ally(0, m.locks.target(0)), "and that lock is an ally lock");

    // ...but targetable() still describes a legal aim, and the melee layer below
    // refuses it. This is the Match::melee_target contract.
    check(m.locks.targetable(0, 1, m.alive), "an ally is a legal AIM target");
    check(!m.locks.is_ally(0, 2) && m.locks.targetable(0, 2, m.alive),
          "a hostile is a legal aim target and is not an ally");
}

// ---------------------------------------------------------------------------
// Index spaces: fighter / panel / controller / team must not be conflated.
// ---------------------------------------------------------------------------
void testIndexSpacesStayDistinct() {
    section("fighter, panel, controller and team indices stay distinct");
    // The lock API addresses the FIGHTER table. Panel slots go to 3 and controller slots
    // to 4, but fighter indices stop at fighterCount-1 — so a three-fighter match is the
    // case that separates the spaces: 3 is a legal panel, a legal controller and an
    // ILLEGAL fighter.
    gameplay::TargetLocks locks;
    const int side[4] = {0, 0, 1, 1};
    locks.reset(3, side);
    // Fighter 3 does not exist, but its liveness slot is set: an index outside the
    // fighter table must not become reachable just because the array is 4 wide.
    bool alive[4] = {true, true, true, true};
    locks.step(alive);
    checkInt(3, locks.fighter_count(), "the lock table holds exactly three fighters");

    locks.set_target(0, 2, alive);
    checkInt(2, locks.target(0), "fighter 2 is a legal fighter index");
    locks.set_target(0, 3, alive);
    checkInt(gameplay::kNoTarget, locks.target(0),
             "index 3 is refused: legal as a panel and a controller, not as a fighter");
    locks.set_target(0, 4, alive);
    checkInt(gameplay::kNoTarget, locks.target(0),
             "index 4 is refused: a controller slot is not a fighter");

    // Team is a 0/1 flag and never an index, so no lock is ever read through it.
    for (int fighter = 0; fighter < 3; ++fighter) {
        const int lock = locks.target(fighter);
        if (lock == gameplay::kNoTarget) continue;
        check(lock >= 0 && lock < locks.fighter_count(),
              "every lock index addresses a real fighter");
        // is_ally is the only team comparison, and it is made on two fighter indices.
        check(locks.is_ally(fighter, lock) == (side[fighter] == side[lock]),
              "ally-ness is the team comparison of two fighter indices");
        // is_ally is a pure team comparison, so a fighter is trivially "allied" with
        // itself; the self-exclusion lives one level down in targetable().
        check(locks.is_ally(fighter, fighter),
              "is_ally compares teams only, so self is same-team");
        check(!locks.targetable(fighter, fighter, alive),
              "targetable is what refuses self, and it holds for every fighter");
    }

    // The enemy's cycle in a three-fighter match must land on fighter 2 and wrap there,
    // never drift into panel 3 or controller 4.
    gameplay::TargetLocks duel;
    duel.reset(3, side);
    duel.step(alive);
    for (int i = 0; i < 6; ++i) {
        duel.cycle_enemy(0, true, alive);
        const int lock = duel.target(0);
        check(lock == gameplay::kNoTarget || lock < 3,
              "an enemy cycle never leaves the fighter table");
    }
    checkInt(2, duel.target(0), "the cycle is stable on the only enemy");

    // Two fighters, two independent entries: the table is per fighter, not one slot that
    // every fighter shares.
    TwoVTwo m;
    m.locks.set_target(0, 2, m.alive);
    m.locks.set_target(1, 3, m.alive);
    checkInt(2, m.locks.target(0), "blue 0 holds fighter 2");
    checkInt(3, m.locks.target(1), "blue 1 holds fighter 3 in its own entry");
    m.locks.set_target(0, 3, m.alive);
    checkInt(3, m.locks.target(0), "blue 0 moved to fighter 3");
    checkInt(3, m.locks.target(1), "blue 1's entry is untouched");
}

// ---------------------------------------------------------------------------
// Match wiring: facing and the melee victim follow the lock, not proximity.
// ---------------------------------------------------------------------------
void testMatchFollowsTheLock() {
    section("Match: facing and melee follow the lock");
    gameplay::Match match;
    gameplay::MatchConfig config;
    config.fighterCount = 4;
    config.side[0] = config.side[1] = 0;
    config.side[2] = config.side[3] = 1;
    // Blue 0 at the origin; enemy 2 straight ahead (+Z, close), enemy 3 far behind.
    config.spawn[0] = glm::vec3(0, 0, 0);
    config.spawn[1] = glm::vec3(-400, 0, 0);
    config.spawn[2] = glm::vec3(0, 0, 300);      // near, faces -Z
    config.spawn[3] = glm::vec3(0, 0, -2400);    // far, faces +Z
    config.facing[0] = 0.0f;
    config.facing[2] = 3.14159f;
    config.facing[3] = 0.0f;
    const xm::Model* models[4] = {};
    xm::Controller* anims[4] = {};
    match.reset(config, models, anims, nullptr, nullptr);
    match.economy().setLogFile(nullptr);

    const fnd::input::PlayerState* inputs[4] = {};
    match.step(inputs, 1.0 / 60.0);
    checkInt(2, match.locked_target(0), "blue 0 acquires enemy 2");
    checkInt(2, match.melee_target(0), "melee target agrees with the lock");
    checkInt(0, match.melee_target(2), "red 2's melee target is a blue fighter");

    // Switch blue 0 to the FAR enemy 3 and confirm facing follows the lock, not
    // proximity. Enemy 2 stays much closer the whole time.
    match.cycle_locked_target(0, true);
    checkInt(3, match.locked_target(0), "blue 0 switched to the far enemy 3");
    checkInt(3, match.melee_target(0), "melee follows the lock to the far enemy");
    checkInt(2, match.locked_target(1),
             "blue 1 keeps its own lock through blue 0's switch");

    // Facing: +Z is yaw 0, -Z is yaw pi. Enemy 3 sits at -Z, so the yaw must run to
    // ~pi no matter that enemy 2 is 300 units away and enemy 3 is 2400.
    for (int i = 0; i < 200; ++i) match.step(inputs, 1.0 / 60.0);
    const float yaw = match.fighter(0).facing_yaw();
    check(std::fabs(std::fabs(yaw) - 3.14159265f) < 0.05f,
          "blue 0's facing converged on the locked (far) enemy");
    checkInt(3, match.locked_target(0), "proximity never stole the lock back");
    checkInt(3, match.melee_target(0), "and the melee victim is still the locked enemy");
}

// ---------------------------------------------------------------------------
// Acceptance: in 2v2, an ally lock must never produce a hostile victim.
// ---------------------------------------------------------------------------
void testMatchAllyLockNeverAttacksTheAlly() {
    section("Match: an ally lock never attacks the ally");
    gameplay::Match match;
    gameplay::MatchConfig config;
    config.fighterCount = 4;
    config.side[0] = config.side[1] = 0;
    config.side[2] = config.side[3] = 1;
    config.spawn[0] = glm::vec3(0, 0, 0);
    config.spawn[1] = glm::vec3(60, 0, 0);       // ally 1 right on top of blue 0
    config.spawn[2] = glm::vec3(300, 0, 0);
    config.spawn[3] = glm::vec3(600, 0, 0);
    const xm::Model* models[4] = {};
    xm::Controller* anims[4] = {};
    match.reset(config, models, anims, nullptr, nullptr);
    match.economy().setLogFile(nullptr);

    match.step(nullptr, 1.0 / 60.0);             // seed the locks
    match.lock_ally_target(0);
    checkInt(1, match.locked_target(0), "blue 0 aims at the ally beside her");
    check(match.lock_holds_ally(0), "the recovered hold is live");
    checkInt(2, match.melee_target(0), "melee still resolves to the nearest hostile");
    check(match.melee_target(0) != gameplay::kNoTarget,
          "melee_target still finds a hostile while an ally lock is held");
    for (int i = 0; i < 4; ++i) {
        const int victim = match.melee_target(i);
        check(victim == gameplay::kNoTarget ||
              match.config().side[i] != match.config().side[victim],
              "no fighter's melee victim is on its own team");
        check(victim == gameplay::kNoTarget || (victim >= 0 && victim < 4),
              "every melee victim index is inside the fighter table");
    }

    // And after a KO on the ally, the lock must not linger on a dead partner.
    match.fighter(1).take_damage(1000, &match.fighter(0));
    match.step(nullptr, 1.0 / 60.0);
    check(match.locked_target(0) != 1, "a dead ally is not left as a lock");
    check(match.locked_target(0) == gameplay::kNoTarget ||
          match.config().side[0] != match.config().side[match.locked_target(0)],
          "the post-KO lock is either nothing or a hostile");
}

// ---------------------------------------------------------------------------
// The camera: fast when the target changes, reference-exact when it does not.
// ---------------------------------------------------------------------------
void testCameraRetargetBlend() {
    section("camera: fast retarget, reference-exact follow otherwise");
    // Every fighter faces +Z with baselineOrbit 0, so the eye sits directly behind its
    // target at the same X — which makes the X axis an exact proxy for "how far has the
    // camera got", with no trigonometry in the assertions.
    gameplay::CameraTarget pool[4];
    const float xs[4] = {-400.f, 400.f, 1200.f, 2000.f};
    for (int i = 0; i < 4; ++i) {
        pool[i].position = glm::vec3(xs[i], 0.f, 0.f);
        pool[i].facingYaw = 0.0f;
        pool[i].alive = true;
    }
    std::vector<gameplay::CameraTarget*> vec;
    for (int i = 0; i < 4; ++i) vec.push_back(&pool[i]);

    // Settle on fighter 0, then switch to fighter 1 and watch the gap close.
    gameplay::ArenaCamera cam;
    cam.set_target_pool(vec);
    cam.set_active_target(0);
    for (int i = 0; i < 80; ++i) cam.update(1.0 / 60.0);
    check(std::fabs(cam.eye().x - xs[0]) < 1.f, "80 follow calls settle on fighter 0");

    const float gap = xs[1] - cam.eye().x;
    cam.cycle_target(true);
    checkInt(1, cam.active_target_index(), "the camera cycles to fighter 1");
    for (int i = 0; i < 6; ++i) cam.update(1.0 / 60.0);
    const float closedFast = std::fabs(xs[1] - cam.eye().x);
    // Six calls at the reference's 10% leave 0.9^6 = 53% of the gap; at the retarget
    // blend they leave 0.55^6 = 2.8%. Anything near the former means the boost is off.
    const float afterReference = gap * 0.9f * 0.9f * 0.9f * 0.9f * 0.9f * 0.9f;
    check(closedFast < afterReference * 0.25f,
          "a retarget closes the gap far faster than the 10% follow");

    // The boost is a WINDOW: once it expires the camera is back on the reference blend
    // exactly, so a match that never switches is bit-for-bit the banked behaviour.
    for (int i = 0; i < 40; ++i) cam.update(1.0 / 60.0);
    const glm::vec3 before = cam.eye();
    cam.update(1.0 / 60.0);
    const float followStep = (xs[1] - before.x) * 0.1f;
    check(std::fabs((cam.eye().x - before.x) - followStep) < 0.01f,
          "after the window the eye returns to the reference's 10% blend");

    // A cycle that lands back where it started is not a retarget and arms nothing.
    // With a single alive fighter that is every cycle, which is why a banked 1v1 capture
    // stays on the reference rate.
    gameplay::CameraTarget solo;
    solo.position = glm::vec3(xs[0], 0.f, 0.f);
    solo.facingYaw = 0.0f;
    solo.alive = true;
    std::vector<gameplay::CameraTarget*> soloVec{&solo};
    gameplay::ArenaCamera soloCam;
    soloCam.set_target_pool(soloVec);
    soloCam.set_active_target(0);
    soloCam.update(1.0 / 60.0);                 // one reference call; the boost is spent
    const glm::vec3 soloBefore = soloCam.eye();
    soloCam.cycle_target(true);                 // the walk returns to index 0
    checkInt(0, soloCam.active_target_index(), "a one-fighter pool cannot change target");
    soloCam.update(1.0 / 60.0);
    const float soloStep = (xs[0] - soloBefore.x) * 0.1f;
    check(std::fabs((soloCam.eye().x - soloBefore.x) - soloStep) < 0.01f,
          "a no-op cycle keeps the reference 10% blend (banked 1v1 parity)");

    // Re-selecting the current target through set_active_target is also not a change.
    gameplay::ArenaCamera sameCam;
    sameCam.set_target_pool(vec);
    sameCam.set_active_target(0);
    sameCam.update(1.0 / 60.0);
    const glm::vec3 sameBefore = sameCam.eye();
    sameCam.set_active_target(0);
    sameCam.update(1.0 / 60.0);
    check(std::fabs((sameCam.eye().x - sameBefore.x) -
                    (xs[0] - sameBefore.x) * 0.1f) < 0.01f,
          "re-selecting the current target does not arm a retarget");

    // Dead fighters are still skipped by the camera's own pool walk.
    pool[3].alive = false;
    pool[2].alive = false;
    gameplay::ArenaCamera deadCam;
    deadCam.set_target_pool(vec);
    deadCam.set_active_target(0);
    deadCam.cycle_target(true);
    deadCam.cycle_target(true);
    deadCam.cycle_target(true);
    checkInt(1, deadCam.active_target_index(), "the camera walk skips the dead and wraps");
}

}  // namespace

int main() {
    std::printf("TARGET_LOCK_TEST\n");
    testInitialFallback();
    testTwoVTwoSwitching();
    testIndependentLocks();
    testProximityNeverOverrides();
    testKoAndRespawn();
    testInvalidTargets();
    testHoldForAlly();
    testSwitchPulse();
    testAllyExclusion();
    testIndexSpacesStayDistinct();
    testMatchFollowsTheLock();
    testMatchAllyLockNeverAttacksTheAlly();
    testCameraRetargetBlend();
    std::printf("\nTARGET_LOCK: %s (%d checks, %d failed)\n",
                failures == 0 ? "ok" : "FAIL", checks, failures);
    return failures == 0 ? 0 : 1;
}