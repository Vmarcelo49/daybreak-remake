// =============================================================================
//  controller_scene_lifetime_test.cpp — issue #46 regression guard.
//
//  Controller::model_ is a raw const Model* (assets/xmodel.h:238) bound to
//  &app.scene.models[rig].model for the character rigs of the current match
//  (main.cpp:2259-2261). initScene replaces app.scene wholesale (main.cpp:3522) and
//  app.controllers.resize() (main.cpp:3570) only constructs and destroys entries, so a
//  controller bound by an earlier round kept a pointer into the freed scene. The next
//  advanceAnimation (main.cpp:3855-3856) evaluates every controller with a non-null
//  model_, which is the reporter's crash: coredumpctl 563299 shows evalLocal reading a
//  freed Model's frame list as nf = 66584576 and asking operator new for
//  0x5555555555555580 bytes (the defect is a stale pointer, not out-of-memory).
//
//  What this drives — the REAL code, not a re-statement of it:
//    * initScene() itself, three times, over three shipped stages whose character rigs
//      sit at different model indices (stage04 -> 8,10; stage15 -> 7,9; stage02 -> 9,11
//      for the same rena+keiichi pair), with the standalone --match composition the
//      boot path uses;
//    * the real initMatch() rig binding, which initScene calls at main.cpp:3604 before
//      it needs a renderer — so the controllers this test inspects were bound by the
//      product's own code (Match::reset -> Fighter -> m_anim->bind, fighter.cpp:105);
//    * advanceAnimation() once per swap, the function the reporter's backtrace died in.
//
//  What it asserts: after every swap, at the point advanceAnimation may run, every
//  non-null Controller::model_ names a model of the CURRENT app.scene.models, and no
//  controller the new match does not adopt kept the binding it had before the swap.
//
//  What it does NOT prove (state it, do not imply it): that the *windowed* run reaches
//  match N (that is the manual recipe in the write-up), nor anything about capture
//  recipes — `capturing` is !opts.out.empty() (main.cpp:4943) and advanceAnimation runs
//  only `if (!capturing)` (main.cpp:5018), so no --out recipe can observe this defect.
//
//  No window, no WebGPU device: everything above runs before initScene's renderer
//  stage, which fails here by design ("renderer needs a live device..."), and the test
//  checks that the scene and the bindings got that far. It needs the game install, the
//  same contract as npr_normals_test/raycast_analytic: without one it exits 77.
//
//  Usage: controller_scene_lifetime_test [install-dir]     (or GAME_DIR)
// =============================================================================

#define SDL_MAIN_HANDLED 1
#include "../src/main.cpp"
// main.cpp sets SDL_MAIN_USE_CALLBACKS, and SDL_main.h's callback block then renames
// `main` to `SDL_main` for the rest of that translation unit. This TU is the entry point
// (it never calls SDL_AppInit), so take the name back after the include.
#undef main

#include <filesystem>

namespace {

int g_checks = 0;
int g_failures = 0;

void check(bool ok, const std::string& what) {
    ++g_checks;
    std::printf("  [%s] %s\n", ok ? "ok  " : "FAIL", what.c_str());
    if (!ok) ++g_failures;
}

// Is `model` one of the model objects the CURRENT scene owns? This is exactly what
// Controller::evalWorld -> evalLocal needs: it sizes its scratch from model_->frames
// (assets/xmodel.h:2051).
bool isCurrentSceneModel(const App& app, const xm::Model* model) {
    for (const xm::SceneModel& sm : app.scene.models)
        if (&sm.model == model) return true;
    return false;
}

std::vector<const xm::Model*> boundModels(const App& app) {
    std::vector<const xm::Model*> out;
    out.reserve(app.controllers.size());
    for (const xm::Controller& c : app.controllers) out.push_back(c.model());
    return out;
}

// How many controllers would make advanceAnimation -> evalWorld -> evalLocal read a
// Model the current scene does not own. Reports each offender by index and pointer.
size_t staleControllers(const App& app, const std::string& stage) {
    size_t stale = 0;
    for (size_t i = 0; i < app.controllers.size(); ++i) {
        const xm::Model* m = app.controllers[i].model();
        if (m && !isCurrentSceneModel(app, m)) {
            std::printf("        controller %zu holds %p, which is not a model of %s\n",
                        i, static_cast<const void*>(m), stage.c_str());
            ++stale;
        }
    }
    return stale;
}

std::string rigList(const App& app) {
    std::string out;
    for (int i = 0; i < app.match.config().fighterCount; ++i) {
        if (!out.empty()) out += ",";
        out += std::to_string(app.matchRig[i]);
    }
    return out;
}

bool isNewMatchRig(const App& app, size_t controller) {
    for (int i = 0; i < app.match.config().fighterCount; ++i)
        if (app.matchRig[i] == controller) return true;
    return false;
}

std::string resolveInstall(const char* arg) {
    std::vector<std::string> candidates;
    if (arg && *arg) candidates.push_back(arg);
    if (const char* env = std::getenv("GAME_DIR"); env && *env) candidates.push_back(env);
    candidates.push_back("Higurashi-Daybreak");
    for (const std::string& dir : candidates) {
        std::error_code ec;
        const std::filesystem::path p(dir);
        if (std::filesystem::exists(p / "daybreak00.dat", ec) ||
            std::filesystem::exists(p / "data", ec))
            return dir;
    }
    for (const std::string& dir : candidates) std::printf("  tried %s\n", dir.c_str());
    return {};
}

// The standalone --match shape: a stage plus the two fighters' character+weapon combos.
// Weapons are not named here on purpose — initMatch resolves each fighter to its own
// character's legal combo (main.cpp:2201-2241), so no bare fighter is ever built.
void configureMatch(App& app, const std::string& install, const std::string& stage) {
    app.opts.install    = install;
    app.opts.match      = true;
    app.opts.stage      = stage;
    app.opts.character  = "data/rena:0";
    app.opts.enemy      = "data/keiichi:0";
    // Explicit spawns keep the fixture independent of the stage's env.dat; a stage
    // without one would otherwise be rejected by initMatch (main.cpp:2142).
    app.opts.hasSpawn[0] = app.opts.hasSpawn[1] = true;
    app.opts.spawn[0] = glm::vec3(0.f);
    app.opts.spawn[1] = glm::vec3(500.f, 0.f, 0.f);
}

}  // namespace

int main(int argc, char** argv) {
    std::printf("controller_scene_lifetime — issue #46: Controller::model_ across a scene swap\n");

    const std::string install = resolveInstall(argc > 1 ? argv[1] : nullptr);
    if (install.empty()) {
        std::printf("SKIP: no game install (pass <install-dir> or set GAME_DIR)\n");
        return 77;
    }
    std::printf("install: %s\n", install.c_str());

    // Three shipped stages whose rigs differ for the same fighter pair, so every swap
    // leaves controllers the new match does not adopt.
    const char* stages[3] = {"data/stage04", "data/stage15", "data/stage02"};

    App app;
    std::vector<const xm::Model*> before;
    std::string previousRigs;
    for (int round = 0; round < 3; ++round) {
        configureMatch(app, install, stages[round]);
        // The bindings made against the scene this call is about to replace.
        before = boundModels(app);

        const bool started = initScene(app);
        std::printf("\n-- swap %d: %s\n", round + 1, stages[round]);
        if (app.scene.models.empty()) {
            // No install, or a stage this copy of the game does not ship: not a failure
            // of the invariant, and the suite must stay runnable without the data.
            std::printf("SKIP: %s did not load (%s)\n", stages[round], app.error.c_str());
            return 77;
        }
        // initScene is expected to stop at its renderer stage here (no WebGPU device);
        // everything this test inspects happens before it. Printed so a changed order
        // shows up as a note rather than as a silent difference in coverage.
        if (started)
            std::printf("   note: initScene reported success (a device was available?)\n");

        int bound = 0;
        for (const xm::Model* m : boundModels(app)) bound += m ? 1 : 0;
        std::printf("   scene %s: %zu models, %d controller(s) bound, rigs %s\n",
                    stages[round], app.scene.models.size(), bound, rigList(app).c_str());
        if (app.match.config().fighterCount < 2 || bound < 2) {
            // The scene loaded but the standalone match did not (a missing move table
            // or item on this install): there is no rig binding to check, and a test
            // that quietly passed here would claim coverage it does not have.
            std::printf("SKIP: %s built no two-fighter match (%s)\n", stages[round],
                        app.error.c_str());
            return 77;
        }
        check(bound == app.match.config().fighterCount,
              "initMatch bound exactly its fighters' controllers");

        // 1. The invariant advanceAnimation relies on.
        check(staleControllers(app, stages[round]) == 0,
              "every non-null Controller::model_ names a model of the current scene");

        // 2. No binding from the replaced scene survived. Stated against the pointers
        //    recorded before the swap so an allocator that hands the same block back to
        //    the new scene cannot mask check 1. Controllers the new match adopts are
        //    excluded: rebinding those is the other legal fix.
        size_t survivors = 0;
        for (size_t i = 0; i < before.size() && i < app.controllers.size(); ++i) {
            if (!before[i] || isNewMatchRig(app, i)) continue;
            if (app.controllers[i].model() == before[i]) {
                std::printf("        controller %zu still bound to %p from the replaced scene\n",
                            i, static_cast<const void*>(before[i]));
                ++survivors;
            }
        }
        check(survivors == 0, "no controller kept a binding from the replaced scene");

        if (g_failures != 0) break;

        // 3. advanceAnimation is allowed to run now — the call the reporter's backtrace
        //    died in (evalLocal -> operator new -> std::bad_alloc). It must return, and the
        //    pose pass it drives must leave the same invariant behind.
        advanceAnimation(app, 1.0 / 64.0);
        check(staleControllers(app, stages[round]) == 0,
              "advanceAnimation ran over the swapped scene and left the invariant intact");

        const std::string rigs = rigList(app);
        if (round > 0 && rigs == previousRigs)
            check(false, "fixture: " + std::string(stages[round]) +
                             " must select rigs different from the previous stage");
        previousRigs = rigs;
    }

    std::printf("\nchecks=%d failures=%d\n", g_checks, g_failures);
    std::printf("CONTROLLER_SCENE_LIFETIME: %s\n", g_failures == 0 ? "ok" : "FAIL");
    return g_failures == 0 ? 0 : 1;
}
