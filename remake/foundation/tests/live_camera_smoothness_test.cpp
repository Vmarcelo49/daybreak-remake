// =============================================================================
//  live_camera_smoothness_test.cpp — issue #39 regression guard.
//
//  THE BLIND SPOT (reported): the camera defect fixed in 92b6d70 survived twenty-odd
//  issues of verification — every agent's capture evidence, the whole CTest suite and
//  the owner's own measurements — because the capture path renders with
//  `app.matchAlpha = 1` (D9's one-update-per-frame recipes) and buildFrameViews draws
//  `glm::mix(previousEye, camera.eye(), matchAlpha)`. At alpha 1 that mix returns the
//  current camera unchanged, so a capture was byte-perfect while a PLAYED battle swept
//  the camera between the match's opening pose and the converged one on every frame
//  (measured live: 19-938 units/frame, median 387; after the fix ~4.2 units/frame).
//  The defect was structural, not a one-off: nothing in the capture stack can see
//  presentation-time interpolation, per-frame smoothing or input-driven per-frame state.
//
//  WHAT THIS DRIVES — the product's own live frame composition, no GPU and no game data:
//    * src/main.cpp is compiled into this TU (SDL_MAIN_HANDLED, the shape
//      lock_switch_camera_test/debug_keys_test use);
//    * a hand-built 1v1 (and a 2v2) Match whose fighters carry a real character+weapon
//      combo (AGENTS rule 7) and stand still — the acceptance's "followed fighter is
//      stationary";
//    * one frame at a time exactly as the frame loop composes it: gameplay::FixedStep
//      decides how many simulation ticks the frame runs and what fraction of the next one has
//      elapsed, tickMatch() steps the match, and buildFrameViews() then builds the frame
//      the scene pass draws. matchAlphaFor() is the product's own alpha resolution, so a
//      break in the live alpha path breaks this test;
//    * the assertion reads FrameView::camera.eye — the frame-view state the renderer
//      consumes — not pixels, so it needs no adapter and cannot pass by accident of
//      rasterisation.
//
//  WHAT IT ASSERTS:
//    * after the camera has settled on its stationary fighter, consecutive live frames
//      must not move the rendered eye by more than kMaxEyeStep units — the acceptance's
//      smoothness bound. The camera's own eye is asserted to be still over the same
//      window, so a rendered eye that moves while the camera does not is a failure by
//      construction;
//    * the same bound at three frame cadences (60 Hz: one tick per frame, 144 Hz: frames
//      with no tick at all, 30 Hz: two ticks per frame), because the live loop's tick
//      fraction is what the defect fed on;
//    * --match-alpha reaches the frame: with it a capture renders the interpolated eye and
//      an interpolated view matrix, and at the option's own fraction between the two
//      ticks; without it a capture still renders the camera's own eye and its own view
//      matrix, which is the byte-identity rule every banked capture depends on (D9).
//
//  Build (the CMake target is `live_camera_smoothness_test`):
//    cmake --build remake/foundation/build/linux --target live_camera_smoothness_test
//  Exit status: 0 when every check passes, 1 otherwise.
// =============================================================================

#define SDL_MAIN_HANDLED 1
#include "../src/main.cpp"
// main.cpp sets SDL_MAIN_USE_CALLBACKS, so SDL_main.h renames `main` for the rest of this
// TU. This file is the entry point, so take the name back (same as the other tests that
// compile the app in).
#undef main

#include <algorithm>
#include <cmath>
#include <cstring>
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

// The acceptance's numbers, printed: `measured` against `limit`.
void checkAtMost(float measured, float limit, const std::string& what) {
    ++g_checks;
    const bool ok = measured <= limit;
    std::printf("  %-64s %s", what.c_str(), ok ? "ok" : "FAIL");
    std::printf("  (measured %.3f, limit %.3f)\n", measured, limit);
    if (!ok) ++g_failures;
}

void checkNear(float expected, float actual, float tolerance, const std::string& what) {
    ++g_checks;
    const bool ok = std::fabs(expected - actual) <= tolerance;
    std::printf("  %-64s %s", what.c_str(), ok ? "ok" : "FAIL");
    std::printf("  (expected %.4f, got %.4f, tol %.4f)\n", expected, actual, tolerance);
    if (!ok) ++g_failures;
}

void section(const char* title) { std::printf("\n-- %s\n", title); }

constexpr uint32_t kWidth  = 960;
constexpr uint32_t kHeight = 540;

// The acceptance bound: consecutive live frames with a stationary followed fighter must
// not move the rendered camera eye more than this. The reference camera converges 10% per
// call, so once it has settled its own eye is a float fixed point; the correct
// interpolation of two equal poses is that same point, while a frozen snapshot sweeps the
// full distance between the opening pose and the converged one (~300 units here). 5 units
// is far above the blend's float noise and far below the defect's sweep.
constexpr float kMaxEyeStep = 5.f;

// ---------------------------------------------------------------------------
// The fighters carry a real combo (AGENTS rule 7), the same synthetic "Rena 1" the other
// device-free match tests parse: weapon id 1 / item 001 with the shipped magazine and
// charge numbers, and a move table carrying move 300's recovered hit window (live at
// frame 4, radius 20 — melee_rules_test's anchor). Nothing in this test attacks; the combo
// is bound so no fighter is ever bare, not because the camera reads it.
// ---------------------------------------------------------------------------
void putU32(std::vector<uint8_t>& b, int v) {
    const uint32_t u = static_cast<uint32_t>(v);
    for (int i = 0; i < 4; ++i) b.push_back(static_cast<uint8_t>((u >> (8 * i)) & 0xffu));
}
void putF32(std::vector<uint8_t>& b, float v) {
    int i = 0;
    std::memcpy(&i, &v, 4);
    putU32(b, i);
}
void putName(std::vector<uint8_t>& b, const char* s, int width) {
    const size_t n = std::strlen(s);
    for (int i = 0; i < width; ++i)
        b.push_back(i < static_cast<int>(n) ? static_cast<uint8_t>(s[i]) : 0u);
}

// One 0x9a-byte effect record: name, in-phase frame, three placement floats, radius, the
// 20-dword combat block (5 = HP power, 10 = defender hitstun) and the record's tail.
void putEntry(std::vector<uint8_t>& b, const char* name, int frame, int radius, int hpDamage,
              int hitstun) {
    putName(b, name, 30);
    putU32(b, frame);
    putF32(b, 0.f);
    putF32(b, 0.f);
    putF32(b, 0.f);
    putU32(b, radius);
    int combat[20] = {0};
    combat[5] = hpDamage;
    combat[10] = hitstun;
    for (int c : combat) putU32(b, c);
    putU32(b, 0);
    putU32(b, 0);
    putU32(b, 0);
    putF32(b, 0.f);
    putF32(b, 0.f);
    putF32(b, 0.f);
}

struct Combo {
    std::vector<uint8_t>            table;
    gameplay::CharacterMoves        moves;
    gameplay::WeaponDefinition      weapon;
    bool                            parsed = false;

    Combo() {
        putU32(table, 0x00010000);                 // the table's tag
        putName(table, "data/rena/00.X", 0x104);   // 260-byte model path block
        putU32(table, 0);
        putU32(table, 0);
        putU32(table, 0);
        putU32(table, 1);                          // header[3] = weapon id (file 0x114)
        putU32(table, 0);
        putU32(table, 0);
        putU32(table, 1);                          // one move
        putU32(table, 300);                        // rena's ground swing
        putU32(table, 0);
        putU32(table, 12);                         // cancel window
        putU32(table, 1);                          // one phase
        putU32(table, 31);                         // the animation set the phase binds
        putU32(table, 2);                          // two effect records
        putEntry(table, "Prop1", 4, 20, 750, 10);  // the live hit
        putEntry(table, "Whiff", 7, 0, 0, 0);      // bounds the window at frame 7
        putU32(table, 0);                          // no animation-set rows
        std::string error;
        parsed = moves.parse(table.data(), table.size(), error);
        if (!parsed) std::printf("  combo table rejected: %s\n", error.c_str());
        weapon.id = 1;
        weapon.slotCount = 2;
        weapon.magazines[0] = gameplay::MagazineDefinition{6, 2, 300, 0, 60, 1};
        weapon.magazines[1] = gameplay::MagazineDefinition{2, 2, 300, 0, 180, 2};
    }
};

// ---------------------------------------------------------------------------
// The fixture: a match and its per-view state the way initMatch builds them, with one
// human controller per fighter (the front-end battle's keying). `dt` is the live fixed step
// (gameplay::FixedStep::seconds) and the round has no time limit, so the fixture cannot end
// mid-test.
// ---------------------------------------------------------------------------
struct Fixture {
    Combo combo;   // declared first: app.match borrows its weapon/move table
    App   app;

    Fixture(int fighters, const int side[4], const glm::vec3 spawn[4]) {
        gameplay::MatchConfig config;
        config.fighterCount = fighters;
        config.timeLimit = 0;
        for (int i = 0; i < fighters; ++i) {
            config.side[i] = side[i];
            config.spawn[i] = spawn[i];
            config.weapon[i] = &combo.weapon;
            config.moves[i] = &combo.moves;
        }
        const xm::Model* models[4] = {};
        xm::Controller* anims[4] = {};
        app.match.reset(config, models, anims, nullptr, nullptr);
        app.match.economy().setLogFile(nullptr);

        app.frontendMatch = true;
        app.battleLaunch.fighterCount = fighters;
        for (int i = 0; i < fighters; ++i) {
            app.battleLaunch.fighters[i].panel = i;
            app.frontend.slots[i].controller = i;
        }

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
            view.previousEye = view.camera.eye();
            view.previousTarget = view.camera.target();
        }
    }
};

// One live frame, composed exactly as the frame loop composes it: the clock decides the
// tick count and the presentation fraction, the ticks step the match through the product's
// own tickMatch, and buildFrameViews then builds the frame the scene pass draws. The clock
// is app.logicClock — the product's own accumulator, which is what matchAlphaFor reads.
struct FrameSample {
    std::vector<glm::vec3> renderedEye;   // per view: what the renderer draws with
    std::vector<glm::vec3> cameraEye;     // per view: the camera's own converged eye
    float                  alpha = 0.f;
    int                    ticks = 0;
};

FrameSample liveFrame(App& app, double delta) {
    FrameSample sample;
    sample.ticks = app.logicClock.advance(delta);
    app.matchAlpha = matchAlphaFor(app, /*capturing=*/false);
    for (int tick = 0; tick < sample.ticks; ++tick) tickMatch(app, gameplay::FixedStep::seconds);
    std::vector<FrameView> views;
    buildFrameViews(app, kWidth, kHeight, views);
    for (const FrameView& view : views) sample.renderedEye.push_back(view.camera.eye);
    for (int v = 0; v < app.matchViewCount; ++v) sample.cameraEye.push_back(app.matchViews[v].camera.eye());
    sample.alpha = app.matchAlpha;
    return sample;
}

// What one run of live frames measured. Every number the assertions use is recorded here,
// so a failure prints the measurement rather than only the verdict.
struct Sweep {
    int   frames = 0;
    int   views = 0;
    float maxRenderedStep = 0.f;   // the acceptance number
    float maxCameraStep = 0.f;     // the precondition: the camera itself is settled
    float fighterDrift = 0.f;      // the precondition: the followed fighter is stationary
    float facingDrift = 0.f;       //   ... in facing too (the camera's desired eye orbits it)
    float minAlpha = 1.f, maxAlpha = 0.f;
    int   zeroTickFrames = 0;      // frames with no simulation tick (the live loop's own case)
    int   multiTickFrames = 0;     // frames with two or more (catch-up)
};

// Runs `frameCount` live frames at `delta` seconds per frame, measuring consecutive
// frame-to-frame movement of the rendered eye and of the camera's own eye, both in units.
Sweep sweep(Fixture& f, double delta, int frameCount) {
    Sweep s;
    std::vector<glm::vec3> previousRendered, previousCamera;
    const glm::vec3 fighterStart = f.app.match.fighter(0).position();
    const float facingStart = f.app.match.fighter(0).facing_yaw();
    for (int frame = 0; frame < frameCount; ++frame) {
        const FrameSample sample = liveFrame(f.app, delta);
        if (previousRendered.size() != sample.renderedEye.size()) {
            previousRendered = sample.renderedEye;
            previousCamera = sample.cameraEye;
            s.views = static_cast<int>(sample.renderedEye.size());
            continue;   // the first frame has nothing to compare against
        }
        for (size_t v = 0; v < sample.renderedEye.size(); ++v) {
            s.maxRenderedStep = std::max(
                s.maxRenderedStep, glm::length(sample.renderedEye[v] - previousRendered[v]));
            s.maxCameraStep = std::max(
                s.maxCameraStep, glm::length(sample.cameraEye[v] - previousCamera[v]));
        }
        previousRendered = sample.renderedEye;
        previousCamera = sample.cameraEye;
        s.minAlpha = std::min(s.minAlpha, sample.alpha);
        s.maxAlpha = std::max(s.maxAlpha, sample.alpha);
        if (sample.ticks == 0) ++s.zeroTickFrames;
        if (sample.ticks > 1) ++s.multiTickFrames;
        ++s.frames;
    }
    s.fighterDrift = glm::length(f.app.match.fighter(0).position() - fighterStart);
    s.facingDrift = std::fabs(std::remainder(f.app.match.fighter(0).facing_yaw() - facingStart,
                                             glm::two_pi<float>()));
    return s;
}

// The camera settles on its stationary fighter: the reference blend is 10% per call, so
// 200 calls leave the eye a float fixed point. Nothing is rendered here — the sweep's own
// first frames are what is measured.
void settle(Fixture& f, int ticks) {
    for (int i = 0; i < ticks; ++i) tickMatch(f.app, gameplay::FixedStep::seconds);
}

void report(const Sweep& s, const char* when, double delta) {
    std::printf("  measured %-9s delta=%.5f s: %d frames x %d view(s), alpha %.3f..%.3f, "
                "ticks/frame %d zero / %d multi\n",
                when, delta, s.frames, s.views, s.minAlpha, s.maxAlpha, s.zeroTickFrames,
                s.multiTickFrames);
    std::printf("             rendered eye max step %.4f units, camera eye max step %.4f, "
                "fighter drift %.4f (facing %.4f rad)\n",
                s.maxRenderedStep, s.maxCameraStep, s.fighterDrift, s.facingDrift);
}

// ---------------------------------------------------------------------------
// The acceptance's smoothness check at one cadence: a settled camera, a stationary
// followed fighter, that cadence's own tick shape, and a bound on how far the RENDERED eye
// may move between frames.
// ---------------------------------------------------------------------------
void testSettledCameraDoesNotSweep(double delta, const char* name, int fighters,
                                   const int side[4], const glm::vec3 spawn[4]) {
    section(name);
    Fixture f(fighters, side, spawn);
    settle(f, 200);
    const Sweep s = sweep(f, delta, 400);
    report(s, name, delta);
    check(s.frames == 399, "the sweep measured consecutive frames");
    checkAtMost(s.fighterDrift, 0.5f, "the followed fighter is stationary over the window");
    checkAtMost(s.facingDrift, 0.001f, "and does not turn: the camera's desired eye cannot orbit");
    checkAtMost(s.maxCameraStep, 0.5f, "the camera's own eye is settled over the window");
    // At the port cadence an exact 60 Hz render delta consumes exactly one tick and leaves no
    // remainder, so this case is boundary-exact: one tick, alpha 0, every frame. The D9 tick
    // fraction — a frame that renders BETWEEN two ticks — is asserted where it is real, at
    // the 144 Hz sub-tick render below.
    check(s.zeroTickFrames == 0 && s.multiTickFrames == 0,
          "the cadence runs exactly one tick per frame (no fraction to span)");
    checkAtMost(s.maxRenderedStep, kMaxEyeStep,
                "consecutive rendered frames do not sweep the camera eye");
}

// ---------------------------------------------------------------------------
// The cadence matrix: the live loop runs 0, 1 or 2 ticks in a frame depending on the
// render rate against the fixed-step clock, and the defect's sweep grew with the tick fraction
// the frame happened to land on. All three shapes must hold the same bound.
// ---------------------------------------------------------------------------
void testCadences() {
    const int side[4] = {0, 1, 0, 1};
    const glm::vec3 spawn[4] = {glm::vec3(0.f), glm::vec3(2000.f, 0.f, 0.f),
                                glm::vec3(0.f), glm::vec3(0.f)};

    // 60 Hz render against the same 60 Hz clock: the ordinary live case, boundary-exact.
    testSettledCameraDoesNotSweep(1.0 / 60.0, "1v1, two views, 60 Hz (one tick per frame)",
                                  2, side, spawn);

    // 144 Hz: fewer ticks than frames, so most frames step nothing at all. A frozen
    // snapshot still moves when only the fraction changes, which is what this catches.
    section("1v1, two views, 144 Hz (frames with no tick at all)");
    {
        Fixture f(2, side, spawn);
        settle(f, 200);
        const Sweep s = sweep(f, 1.0 / 144.0, 400);
        report(s, "144 Hz", 1.0 / 144.0);
        check(s.zeroTickFrames > 100, "most frames run no simulation tick");
        // The D9 gate (issue #39): the live path must render between ticks, so the fixture
        // has to land on a spread of fractions rather than on one alpha.
        check(s.maxAlpha - s.minAlpha > 0.5f, "the frames span a real tick fraction, not one alpha");
        checkAtMost(s.fighterDrift, 0.5f, "the followed fighter is stationary over the window");
        checkAtMost(s.facingDrift, 0.001f, "and does not turn: the camera's desired eye cannot orbit");
        checkAtMost(s.maxCameraStep, 0.5f, "the camera's own eye is settled over the window");
        checkAtMost(s.maxRenderedStep, kMaxEyeStep,
                    "a frame with no tick still does not sweep the rendered eye");
    }

    // 30 Hz: two ticks per frame — the catch-up shape, where previousEye advances twice
    // inside one rendered frame.
    section("2v2, four views, 30 Hz (two ticks per frame)");
    {
        const int side4[4] = {0, 0, 1, 1};
        const glm::vec3 spawn4[4] = {glm::vec3(0.f), glm::vec3(0.f, 0.f, 800.f),
                                     glm::vec3(2000.f, 0.f, 0.f), glm::vec3(2000.f, 0.f, 800.f)};
        Fixture f(4, side4, spawn4);
        settle(f, 200);
        const Sweep s = sweep(f, 1.0 / 30.0, 400);
        report(s, "30 Hz 2v2", 1.0 / 30.0);
        check(s.multiTickFrames > 300, "every frame runs two simulation ticks");
        checkAtMost(s.fighterDrift, 0.5f, "the followed fighter is stationary over the window");
        checkAtMost(s.facingDrift, 0.001f, "and does not turn: the camera's desired eye cannot orbit");
        checkAtMost(s.maxCameraStep, 0.5f, "every view's camera eye is settled over the window");
        checkAtMost(s.maxRenderedStep, kMaxEyeStep,
                    "four views do not sweep the rendered eye either");
    }
}

// ---------------------------------------------------------------------------
// --match-alpha (issue #39's mode): a capture that renders the presentation interpolation
// the live path renders. The other half of the check is the byte-identity rule — with the
// option off, a capture must still render the camera's own eye through the camera's own
// view matrix, which is what keeps every banked capture unchanged.
// ---------------------------------------------------------------------------
void testMatchAlphaReachesTheFrame() {
    section("--match-alpha: a capture renders the interpolation; alpha 1 stays the identity");
    const int side[4] = {0, 1, 0, 1};
    const glm::vec3 spawn[4] = {glm::vec3(0.f), glm::vec3(2000.f, 0.f, 0.f),
                                glm::vec3(0.f), glm::vec3(0.f)};
    Fixture f(2, side, spawn);
    // Barely settled on purpose: the camera's own per-call step is 10% of what is left, so
    // after two calls the two ticks are still ~30 units apart and the blend is measurable.
    settle(f, 2);
    App& app = f.app;
    // A capture's rule (matchAlphaFor(app, capturing=true)) is what this section pins: with
    // no --match-alpha it is exactly 1, and alpha 1 has to render the camera's own eye
    // through the camera's own view matrix — the identity every banked capture depends on.
    // `opts.out` is never written to; it is what makes this run a capture for that rule.
    app.opts.out = "/tmp/issue39-live-camera-smoothness.ppm";

    checkNear(1.f, matchAlphaFor(app, /*capturing=*/true),
              0.f, "a capture with no --match-alpha renders at alpha 1");
    app.opts.matchAlpha = 0.5f;
    checkNear(0.5f, matchAlphaFor(app, /*capturing=*/true), 0.f,
              "--match-alpha=0.5 is the alpha the frame renders with");

    app.opts.matchAlpha = -1.f;
    app.matchAlpha = matchAlphaFor(app, true);
    std::vector<FrameView> exact;
    buildFrameViews(app, kWidth, kHeight, exact);
    const bool twoCells = exact.size() == 2;
    check(twoCells, "both views have a cell at 960x540");
    if (!twoCells) return;
    const game::MatchView& view = app.matchViews[0];
    const glm::mat4 proj = view.camera.proj_matrix((int)exact[0].cell.w, (int)exact[0].cell.h);
    check(exact[0].camera.eye == view.camera.eye(),
          "alpha 1 renders the camera's own eye (the byte-identity rule)");
    check(exact[0].camera.viewProj == proj * view.camera.view_matrix(),
          "and the camera's own view matrix");

    app.opts.matchAlpha = 0.5f;
    app.matchAlpha = matchAlphaFor(app, true);
    std::vector<FrameView> blended;
    buildFrameViews(app, kWidth, kHeight, blended);
    const float gap = glm::length(view.camera.eye() - view.previousEye);
    const float toCurrent = glm::length(view.camera.eye() - blended[0].camera.eye);
    std::printf("  measured: previous->camera gap %.3f units, rendered eye sits %.3f from the "
                "camera\n", gap, toCurrent);
    check(gap > 10.f, "the two ticks are far enough apart for the blend to be measurable");
    check(blended[0].camera.eye != view.camera.eye(), "alpha 0.5 renders an interpolated eye");
    check(blended[0].camera.viewProj != proj * view.camera.view_matrix(),
          "and an interpolated view matrix, not the camera's own");
    checkNear(0.5f * gap, toCurrent, 0.01f * gap + 1e-3f,
              "the rendered eye sits at the option's own fraction between the two ticks");
}

}  // namespace

int main() {
    std::printf("LIVE_CAMERA_SMOOTHNESS_TEST (issue #39)\n");
    testCadences();
    testMatchAlphaReachesTheFrame();
    std::printf("\nLIVE_CAMERA_SMOOTHNESS: %s (%d checks, %d failed)\n",
                g_failures == 0 ? "ok" : "FAIL", g_checks, g_failures);
    return g_failures == 0 ? 0 : 1;
}
