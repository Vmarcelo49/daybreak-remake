// =============================================================================
//  lock_switch_camera_test.cpp — issue #51 regression guard.
//
//  THE DEFECT (reported): pressing the target-switch button (LockSwitch) did not just
//  change the combat target — the CAMERA moved onto the enemy, "as if they had switched
//  to a character they cannot control". The tap handler in tickMatch did two writes:
//  Match::cycle_locked_target (the combat target — correct) and ArenaCamera::cycle_target
//  (the camera's FOLLOWED fighter — wrong). The recovered target-change writer
//  FUN_00421e30 stores only the fighter's own target state (+0x300 current target,
//  +0x30c = 0xf pulse, +0x308 the target's team field, +0x304 = -1, +0x848 hold + cue) —
//  no view, camera or followed-player field — and its other caller FUN_0063c2a0 case 0x2a
//  applies a REMOTE player's target switch, which would be nonsense if it moved the local
//  camera. So the tap must never touch the view's camera.
//
//  WHAT THIS DRIVES — the product's own per-tick path, not a re-statement of it:
//    * src/main.cpp is compiled into this TU (SDL_MAIN_HANDLED, the shape
//      controller_scene_lifetime_test/device_isolation_test use) and tickMatch() is called
//      once per simulated tick, exactly as the frame loop calls it;
//    * the button is delivered through app.tickInput[controller], the PlayerState slot the
//      real input backend fills, with the down/just-pressed edges derived by
//      fnd::input::compute_edges;
//    * the views are built the way initMatch builds them (a camera pool over
//      app.arenaTargets, one view per human controller, set_active_target(follower) at
//      setup), so view.followed, the camera's own index and the eye are the product's.
//
//  WHAT IT ASSERTS (a 1v1 with two views, then the four-view 2v2):
//    * a LockSwitch tap re-points the view's COMBAT target and leaves the camera's
//      followed fighter alone: view.followed, camera.active_target_index() and the
//      camera's nearest fighter are unchanged on the tap tick AND on the ticks after it;
//    * the combat target still cycles in a 2v2 (2 -> 3 -> 2 for blue, 0 -> 1 -> 0 for red);
//    * the hold gesture aims at the ally (the recovered 0xb4 hold) without moving the
//      camera either;
//    * every view keeps its own camera: view v follows fighter v across all four views,
//      and a tap in one view moves no other view's camera;
//    * measured: the eye stays nearest the view's own fighter, and its distance to that
//      fighter does not jump on a tap tick.
//
//  No GPU, no window, no physical device and no game install: the match runs with the
//  historical null models/weapons, the data-free shape target_lock_test uses. No combat
//  claim rides on these fighters — they never attack here (the test presses LockSwitch
//  only), which is why no character+weapon data is bound; AGENTS rule 7's combos are what
//  the asset-backed recipes in docs/RELEASE-CHECKLIST.md §3 fight (its measured 1v1 is
//  1P Rena 0 vs 2P Mion 0).
//
//  Build (the CMake target is `lock_switch_camera_test`):
//    cmake --build remake/foundation/build/linux --target lock_switch_camera_test
//  Exit status: 0 when every check passes, 1 otherwise.
// =============================================================================

#define SDL_MAIN_HANDLED 1
#include "../src/main.cpp"
// main.cpp sets SDL_MAIN_USE_CALLBACKS, so SDL_main.h renames `main` for the rest of this
// TU. This file is the entry point, so take the name back (same as the other two tests
// that compile the app in).
#undef main

#include <cmath>
#include <string>
#include <vector>

namespace {

int g_checks = 0;
int g_failures = 0;

void check(bool ok, const std::string& what) {
    ++g_checks;
    std::printf("  %-64s %s\n", what.c_str(), ok ? "ok" : "FAIL");
    if (!ok) ++g_failures;
}

void checkInt(int expected, int actual, const std::string& what) {
    ++g_checks;
    const bool same = expected == actual;
    std::printf("  %-64s %s", what.c_str(), same ? "ok" : "FAIL");
    if (!same) std::printf("  (expected %d, got %d)", expected, actual);
    std::printf("\n");
    if (!same) ++g_failures;
}

void section(const char* title) { std::printf("\n-- %s\n", title); }

// One simulated tick through the product's own per-tick path. Every controller's buttons
// are released first, so `lockDown` is this tick's whole input and a press is a fresh edge;
// the frame loop feeds tickInput the same way (driveSyntheticLocalPads writes down[] and
// calls compute_edges per tick).
void tick(App& app, int controller, bool lockDown) {
    for (int c = 0; c < 4; ++c) {
        fnd::input::PlayerState& in = app.tickInput[c];
        for (int a = 0; a < fnd::input::ActionCount; ++a) in.down[a] = false;
        in.down[fnd::input::LockSwitch] = (c == controller) && lockDown;
        fnd::input::compute_edges(in);
    }
    tickMatch(app, gameplay::FixedStep::seconds);
}

// A tap: one tick pressed, one released — the shape input.h's "tap = cycle enemy" reads.
void tap(App& app, int controller) {
    tick(app, controller, true);
    tick(app, controller, false);
}

// The test's fixture: the match and the per-view state the way initMatch sets them up,
// with one human controller per fighter (the front-end battle's keying). `dt` is the port's
// fixed step (gameplay::FixedStep::seconds) and the round has no time limit, so the fixture
// cannot end mid-test.
struct Fixture {
    App app;

    Fixture(int fighters, const int side[4], const glm::vec3 spawn[4]) {
        gameplay::MatchConfig config;
        config.fighterCount = fighters;
        config.timeLimit = 0;
        for (int i = 0; i < fighters; ++i) {
            config.side[i] = side[i];
            config.spawn[i] = spawn[i];
        }
        const xm::Model* models[4] = {};
        xm::Controller* anims[4] = {};
        app.legacyBattle.match().reset(config, models, anims, nullptr, nullptr);
        app.legacyBattle.match().economy().setLogFile(nullptr);

        // The front-end battle's input keying: fighter i sits on panel i and is driven by
        // controller i, which is what gives every view its own input (tickMatch reads
        // tickInput[controller] per fighter).
        app.frontendMatch = true;
        app.battleLaunch.fighterCount = fighters;
        for (int i = 0; i < fighters; ++i) {
            app.battleLaunch.fighters[i].panel = i;
            app.frontend.slots[i].controller = i;
        }

        // initMatch's view construction: one view per human controller, its camera's pool
        // over app.arenaTargets, following its own fighter from the start.
        std::vector<gameplay::CameraTarget*> pool;
        for (int i = 0; i < fighters; ++i) pool.push_back(&app.arenaTargets[i]);
        app.matchViewCount = fighters;
        for (int v = 0; v < fighters; ++v) {
            game::MatchView& view = app.matchViews[v];
            view = game::MatchView{};
            view.controller = v;
            view.fighter = v;
            view.followed = v;
            view.camera.set_target_pool(pool);
            view.camera.set_active_target(view.followed);
        }
    }

    // The camera's eye distance to a fighter: the measured half of the issue's acceptance
    // criterion 1 ("the camera eye stays nearest the player's own fighter").
    float eyeDistance(int view, int fighter) const {
        return glm::length(app.matchViews[view].camera.eye() -
                           app.legacyBattle.match().fighter(fighter).position());
    }

    // The camera is on its own fighter: both follow indices name it, and its eye is nearer
    // that fighter than ANY other one on the field.
    bool cameraOnItsOwnFighter(int view) const {
        const game::MatchView& v = app.matchViews[view];
        if (v.followed != v.fighter || v.camera.active_target_index() != v.fighter) return false;
        const float own = eyeDistance(view, v.fighter);
        for (int j = 0; j < app.legacyBattle.match().config().fighterCount; ++j)
            if (j != v.fighter && eyeDistance(view, j) <= own) return false;
        return true;
    }

    // The camera's whole per-view follow state, printed so a failing run shows what moved.
    void reportCameras(const char* when) const {
        std::printf("  cameras %s:", when);
        for (int v = 0; v < app.matchViewCount; ++v) {
            const game::MatchView& view = app.matchViews[v];
            std::printf(" v%d{fighter=%d followed=%d cam=%d eye=(%.0f,%.0f,%.0f) d_own=%.0f}",
                        v, view.fighter, view.followed, view.camera.active_target_index(),
                        view.camera.eye().x, view.camera.eye().y, view.camera.eye().z,
                        eyeDistance(v, view.fighter));
        }
        std::printf("\n");
    }
};

// ---------------------------------------------------------------------------
// The issue's recipe: a live 1v1 with two views. The first tap selects the enemy; the
// camera must stay on the player's own fighter before, during and after it.
// ---------------------------------------------------------------------------
void testOneVersusOneTapKeepsTheCamera() {
    section("1v1: the tap re-targets combat, not the camera");
    const int side[4] = {0, 1, 0, 1};
    const glm::vec3 spawn[4] = {glm::vec3(0.f), glm::vec3(2000.f, 0.f, 0.f),
                                glm::vec3(0.f), glm::vec3(0.f)};
    Fixture f(2, side, spawn);

    // Settle both cameras on their own fighters before anything is pressed (80 follow
    // calls at the reference's 10% blend is converged for a 2000-unit separation).
    for (int i = 0; i < 80; ++i) tick(f.app, -1, false);
    f.reportCameras("settled");
    checkInt(gameplay::kNoTarget, f.app.legacyBattle.match().locked_target(0),
             "round start: no lock until a gesture (issue #49)");
    check(f.cameraOnItsOwnFighter(0), "view 0's camera is on fighter 0 and nearest it");
    check(f.cameraOnItsOwnFighter(1), "view 1's camera is on fighter 1 and nearest it");
    const float beforeOwn = f.eyeDistance(0, 0);

    tap(f.app, 0);
    checkInt(1, f.app.legacyBattle.match().locked_target(0), "the tap selects the enemy");
    // The tap raises the recovered 15-tick pulse (FUN_00421e30's +0x30c). Match::step is
    // what decrements it (FUN_004201a0), so the release tick of the tap has already spent
    // one; what matters here is that the pulse is live after the gesture.
    check(f.app.legacyBattle.match().lock_pulse(0) > 0, "and raises the recovered switch pulse");
    checkInt(0, f.app.matchViews[0].followed, "the view's followed fighter is unchanged");
    checkInt(0, f.app.matchViews[0].camera.active_target_index(),
             "the camera's own active target is unchanged");
    check(f.cameraOnItsOwnFighter(0), "and its eye is still nearest fighter 0");
    check(std::fabs(f.eyeDistance(0, 0) - beforeOwn) < 20.f,
          "the eye's distance to its own fighter did not jump on the tap");
    check(f.cameraOnItsOwnFighter(1), "view 1's camera did not move either");
    f.reportCameras("after the tap");

    // One enemy: a further tap walks back onto the same selection and is a no-op
    // (FUN_0041f580:238 commits only when the walk lands somewhere new). The camera must
    // stay put through it too.
    const float afterTapOwn = f.eyeDistance(0, 0);
    tap(f.app, 0);
    checkInt(1, f.app.legacyBattle.match().locked_target(0), "a second tap with one enemy is a no-op");
    checkInt(0, f.app.matchViews[0].camera.active_target_index(),
             "and still does not move the camera");
    check(std::fabs(f.eyeDistance(0, 0) - afterTapOwn) < 20.f,
          "the eye distance stays stable across repeated taps");

    // The hold gesture: in a 1v1 there is no ally to aim at, so the lock stands — and the
    // camera is untouched either way. The press tick is the tap, and the ally aim fires on
    // the kLockHoldTicks-th tick AFTER it, so the hold is 1 + kLockHoldTicks pressed ticks.
    for (int i = 0; i <= kLockHoldTicks; ++i) tick(f.app, 0, true);
    checkInt(1, f.app.legacyBattle.match().locked_target(0), "holding with no living ally leaves the lock");
    checkInt(0, f.app.matchViews[0].camera.active_target_index(),
             "the hold gesture does not move the camera");
    tick(f.app, 0, false);
    checkInt(0, f.app.matchViews[0].followed, "and the release leaves it where it was");
    f.reportCameras("after the hold");
}

// ---------------------------------------------------------------------------
// Issue #12's concern, four views: every cell's camera stays on its own fighter while the
// taps cycle the combat targets (2v2, where the target genuinely alternates).
// ---------------------------------------------------------------------------
void testFourViewsKeepTheirOwnCameras() {
    section("2v2, four views: taps cycle combat targets, cameras stay put");
    const int side[4] = {0, 0, 1, 1};
    const glm::vec3 spawn[4] = {glm::vec3(0.f), glm::vec3(0.f, 0.f, 800.f),
                                glm::vec3(2000.f, 0.f, 0.f), glm::vec3(2000.f, 0.f, 800.f)};
    Fixture f(4, side, spawn);
    for (int i = 0; i < 80; ++i) tick(f.app, -1, false);
    f.reportCameras("settled");
    for (int v = 0; v < 4; ++v)
        check(f.cameraOnItsOwnFighter(v), "view v's camera follows its own fighter");

    // Three taps per view, with the release tick between them. Blue cycles 2 -> 3 -> 2 and
    // red 0 -> 1 -> 0; after EVERY tick, all four cameras must still be on their own
    // fighters — a tap in one view must not move any other view's camera.
    for (int round = 0; round < 3; ++round) {
        for (int v = 0; v < 4; ++v) {
            const int enemyA = v < 2 ? 2 : 0;
            const int enemyB = v < 2 ? 3 : 1;
            const int want = (round % 2 == 0) ? enemyA : enemyB;
            tap(f.app, v);
            checkInt(want, f.app.legacyBattle.match().locked_target(v),
                     "the tap cycles this view's combat target");
            check(f.app.legacyBattle.match().lock_pulse(v) > 0, "and raises its own switch pulse");
            for (int w = 0; w < 4; ++w)
                check(f.cameraOnItsOwnFighter(w), "every view's camera is still its own");
        }
    }
    checkInt(2, f.app.legacyBattle.match().locked_target(0), "blue 0's cycle wrapped back to 2");
    checkInt(0, f.app.legacyBattle.match().locked_target(2), "red 2's cycle wrapped back to 0");
    f.reportCameras("after twelve taps");

    // The hold gesture: aim the ally, arm the recovered 180-tick hold, never the camera.
    // Physical taps last several ticks. Only a fresh continuous press past the port's
    // threshold selects the ally; the recovered ally dwell must not override a later tap.
    // kLockHoldTicks is a port constant (main.cpp): 16 ticks, ~267 ms at the 60 Hz cadence
    // (D15 superseded D9's 64 Hz, where the same tick count was 250 ms).
    checkInt(16, kLockHoldTicks, "ally hold keeps its 16 ticks (~267 ms at 60 Hz)");
    for (int i = 0; i < kLockHoldTicks - 1; ++i) {
        tick(f.app, 2, true);
        check(f.app.legacyBattle.match().locked_target(2) == 0 || f.app.legacyBattle.match().locked_target(2) == 1,
              "before the threshold the target remains hostile");
    }
    tick(f.app, 2, true);
    checkInt(3, f.app.legacyBattle.match().locked_target(2), "holding picks the ally (red 3)");
    check(f.app.legacyBattle.match().lock_holds_ally(2), "and arms the recovered ally hold");
    check(f.cameraOnItsOwnFighter(2), "the camera stays on red 2 through the hold");
    for (int w = 0; w < 4; ++w)
        check(f.cameraOnItsOwnFighter(w), "and no other view's camera moved");
    tick(f.app, 2, false);
    check(!f.app.legacyBattle.match().lock_holds_ally(2) || f.app.legacyBattle.match().locked_target(2) == 3,
          "the ally aim survives the release (FUN_0041f580:243-244 re-pins it)");
    for (int duration : {1, 3, 6, kLockHoldTicks - 1}) {
        for (int tickIndex = 0; tickIndex < duration; ++tickIndex) {
            tick(f.app, 2, true);
            check(f.app.legacyBattle.match().locked_target(2) == 0 || f.app.legacyBattle.match().locked_target(2) == 1,
                  "a short press leaves the ally and stays on an enemy");
        }
        tick(f.app, 2, false);
        for (int tickIndex = 0; tickIndex < 32; ++tickIndex) {
            tick(f.app, 2, false);
            check(f.app.legacyBattle.match().locked_target(2) == 0 || f.app.legacyBattle.match().locked_target(2) == 1,
                  "after release no stale hold returns the target to the ally");
        }
    }
    for (int i = 0; i < kLockHoldTicks; ++i) tick(f.app, 2, true);
    checkInt(3, f.app.legacyBattle.match().locked_target(2), "a new full hold can select the ally again");
    tick(f.app, 2, false);
    f.reportCameras("after the hold");
}

// ---------------------------------------------------------------------------
// The measured before/after the issue asks for, stated as numbers: the eye is a follower
// of its own fighter for the whole match, and a tap changes nothing about which fighter
// the view's camera is looking at.
// ---------------------------------------------------------------------------
void testEyeIsAMeasuredFollower() {
    section("measured: the eye follows its own fighter across taps");
    const int side[4] = {0, 1, 0, 1};
    const glm::vec3 spawn[4] = {glm::vec3(0.f), glm::vec3(2000.f, 0.f, 0.f),
                                glm::vec3(0.f), glm::vec3(0.f)};
    Fixture f(2, side, spawn);
    for (int i = 0; i < 200; ++i) tick(f.app, -1, false);
    const glm::vec3 settledEye = f.app.matchViews[0].camera.eye();
    const float own = f.eyeDistance(0, 0);
    const float enemy = f.eyeDistance(0, 1);
    std::printf("  measured: eye=(%.0f,%.0f,%.0f) d_own=%.0f d_enemy=%.0f\n",
                settledEye.x, settledEye.y, settledEye.z, own, enemy);
    check(own < enemy, "the settled eye is nearest its own fighter");
    // The eye is a FOLLOWER: it does not teleport onto the fighter, it converges (the
    // reference's 10% per call). An eye sitting on top of the fighter would mean the
    // camera had been re-pointed by something else.
    check(own > 100.f, "and sits behind/above it, not on it (a following camera)");

    tap(f.app, 0);
    const float ownAfter = f.eyeDistance(0, 0);
    const float enemyAfter = f.eyeDistance(0, 1);
    std::printf("  measured: after the tap d_own=%.0f d_enemy=%.0f (followed=%d cam=%d)\n",
                ownAfter, enemyAfter, f.app.matchViews[0].followed,
                f.app.matchViews[0].camera.active_target_index());
    check(ownAfter < enemyAfter, "the tap leaves the eye nearest its own fighter");
    check(f.app.matchViews[0].followed == 0 &&
              f.app.matchViews[0].camera.active_target_index() == 0,
          "and both follow indices are still the view's own fighter");
    check(std::fabs(ownAfter - own) < 20.f,
          "the eye's measured distance to its own fighter is unchanged by the tap");
}

}  // namespace

int main() {
    std::printf("LOCK_SWITCH_CAMERA_TEST (issue #51)\n");
    testOneVersusOneTapKeepsTheCamera();
    testFourViewsKeepTheirOwnCameras();
    testEyeIsAMeasuredFollower();
    std::printf("\nLOCK_SWITCH_CAMERA: %s (%d checks, %d failed)\n",
                g_failures == 0 ? "ok" : "FAIL", g_checks, g_failures);
    return g_failures == 0 ? 0 : 1;
}
