// Title backdrop (issue #98): a live stage behind the title menu.
//
// WHY this shape: the original's title is one still painting (data/title/back00) and its
// scene machine has no 3D pass there (FUN_004114f0 draws three sheets, nothing else), so
// nothing here is recovered. It is the owner's experiment — a stage the game already
// renders, behind the same menu, with a slow camera — and its configuration lives in the
// user's settings ([title] backdrop) with an Options row to switch it.
//
// The composition is not new: resultOverScene already draws a front-end screen over a live
// 3D scene (renderer.render + ui::drawScreenOverlay), and this reuses exactly that pair.
//
// Included by main.cpp inside its anonymous namespace, after scene.inc (viewProj) and before
// frame_loop.inc, which asks it per frame.

// The stage the running title should draw, or empty for the original art. The flag wins
// over the stored setting, the same precedence the toon row's flag uses.
static std::string titleBackdropStage(const App& app) {
    return app.opts.titleBackdropSet ? app.opts.titleBackdrop
                                     : ui::frontendSettings().titleBackdrop;
}

// The framing a stage's title backdrop uses. stage13 is stage03 at sunset — the same
// layout — so the shrine's composed framing applies to both, verified by rendering it on
// each: the hall lands in the same place, only the light differs. Any other stage keeps the
// arena camera's view of its spawn, which is a gameplay framing, not a title one: a curated
// framing there is follow-up work if the owner keeps the experiment.
static render::TitleCamera titleCameraForStage(const std::string& stage, const glm::vec3& spawn) {
    if (stage == "stage03" || stage == "stage13") return render::shrineTitleCamera();
    return render::titleCameraFor(spawn);
}

// Loads `stage` into app.titleBackdrop: geometry, bind pose, the camera's framing and the
// camera-collision mesh. A stage that does not load is reported once and remembered as
// failed, so a missing folder cannot turn into a per-frame load attempt.
static bool loadTitleBackdrop(App& app, const std::string& stage) {
    TitleBackdropState& state = app.titleBackdrop;
    if (state.stage == stage) return true;
    if (state.failed == stage) return false;
    state = TitleBackdropState{};

    xm::SceneOptions options;
    options.resolveTextures = !app.opts.noTextures;
    // collision_camera.x is the sweep's clamp (scene.inc:1128 does the same for a battle's
    // arena camera); the collision models are not drawable, so they never reach a pass.
    options.includeCollision = true;
    try {
        // The setting stores the bare stage name (docs/USER-SETTINGS.md); the loader takes
        // the game's own directory, data/stageNN.
        state.scene = xm::loadStage("data/" + stage, options);
    } catch (const std::exception& e) {
        std::fprintf(stderr, "[title] backdrop %s: %s; keeping the original art\n",
                     stage.c_str(), e.what());
        state.failed = stage;
        return false;
    }
    if (state.scene.models.empty()) {
        std::fprintf(stderr, "[title] backdrop %s: no models; keeping the original art\n",
                     stage.c_str());
        state.failed = stage;
        return false;
    }
    xm::resolveSceneTextures(state.scene);
    state.worlds.resize(state.scene.models.size());
    state.matrices.assign(state.scene.models.size(), glm::mat4(1.f));
    for (size_t i = 0; i < state.scene.models.size(); ++i)
        state.scene.models[i].model.evalPose(nullptr, 0.f, false, state.worlds[i]);

    const xm::Model* cameraMesh = nullptr;
    for (const xm::SceneModel& model : state.scene.models)
        if (model.hasCollisionChannel(xm::StageCollisionChannel::Camera)) cameraMesh = &model.model;
    app.cameraCollision.setMesh(cameraMesh);

    // Frame the play area, not the whole stage: the visible set includes a sky dome tens of
    // thousands of units out (scene.inc:1173-1186 makes the same cut). env.dat's spawn is
    // the play area by construction; a stage without one falls back to the collision bounds.
    glm::vec3 lo(1e30f), hi(-1e30f);
    const bool packed = state.scene.bounds(lo, hi, /*playArea=*/true);
    if (!packed && !state.scene.bounds(lo, hi, /*playArea=*/false)) {
        lo = glm::vec3(-1.f);
        hi = glm::vec3(1.f);
    }
    const glm::vec3 spawn = state.scene.env.present ? state.scene.env.points[0]
                                                    : (lo + hi) * 0.5f;
    state.camera = titleCameraForStage(stage, spawn);
    // The far plane has to reach the sky dome: the same reach the asset path computes.
    glm::vec3 slo(1e30f), shi(-1e30f);
    if (state.scene.bounds(slo, shi, /*playArea=*/false)) {
        for (int corner = 0; corner < 8; ++corner) {
            const glm::vec3 point((corner & 1) ? shi.x : slo.x, (corner & 2) ? shi.y : slo.y,
                                  (corner & 4) ? shi.z : slo.z);
            state.reach = std::max(state.reach, glm::length(point - state.camera.pivot));
        }
    }
    state.stage = stage;
    state.uploaded = false;
    std::printf("[title] backdrop %s\n", assets::describeStage(stage).c_str());
    return true;
}

// True when the renderer holds this stage's geometry. Re-uploading is not free, and the
// battle path re-points the renderer at its own scene, so the caller must ask every frame
// rather than trusting the load to have stuck.
static bool ensureTitleBackdrop(App& app, const std::string& stage) {
    if (!loadTitleBackdrop(app, stage)) return false;
    TitleBackdropState& state = app.titleBackdrop;
    if (state.uploaded) return true;
    if (!app.rendererReady && !app.renderer.init(app.ctx, app.error)) return false;
    app.rendererReady = true;
    app.renderOptions.textures = !app.opts.noTextures;
    if (!app.renderer.setScene(state.scene, state.worlds, state.matrices, app.renderOptions,
                               app.error))
        return false;
    app.renderer.setFog(state.scene.env);
    app.renderer.setAppearance(app.appearance);
    state.uploaded = true;
    return true;
}

// Places the renderer's camera for the sweep's current second. Separate from the draw so a
// --out capture (which renders the scene itself, scene_renderer.h) uses the same framing as
// a window frame.
static void applyTitleBackdropCamera(App& app, float aspect) {
    TitleBackdropState& state = app.titleBackdrop;
    render::TitleCameraPose pose = render::titleCameraPose(state.camera, state.seconds);
    if (state.camera.clampToArena && !app.opts.noCameraClamp) {
        const game::CameraClampResult clamp =
            app.cameraCollision.queryClamp({state.camera.pivot, pose.eye});
        if (clamp.hit) {
            const float segment = glm::length(pose.eye - state.camera.pivot);
            pose.eye = render::arenaClampEye(state.camera.pivot, pose.eye,
                                             game::clampHitDistance(clamp, segment));
        }
    }
    app.eye = pose.eye;
    app.target = pose.aim;
    // A stage's sky dome sits far outside the framed mesh, so the far plane follows the
    // scene's own reach (viewProj, scene.inc:184) instead of the framed distance.
    app.renderer.setCamera(viewProj(pose.eye, pose.aim, aspect, state.camera.radius, state.reach,
                                    state.camera.fovY));
    app.renderer.setEye(pose.eye);
}

// The title screen of the current scene, or null. The host owns the 3D backdrop, so the
// screen has to be told whether it is live before its draw decides to keep its painted
// background out.
static ui::TitleScreen* currentTitleScreen(App& app) {
    if (app.screens.current() != ui::ScreenId::Title) return nullptr;
    return dynamic_cast<ui::TitleScreen*>(app.screens.mutableScreen());
}

// Whether this frame draws the title over the stage. Advances the sweep, so it must be
// called exactly once per frame, and only while the title is the current scene.
static bool titleBackdropThisFrame(App& app, bool capturing, double delta) {
    const std::string stage = titleBackdropStage(app);
    const bool live = !stage.empty() && app.screens.current() == ui::ScreenId::Title &&
                      ensureTitleBackdrop(app, stage);
    if (live) app.titleBackdrop.seconds += capturing ? app.opts.dt : (float)delta;
    if (ui::TitleScreen* title = currentTitleScreen(app)) title->setBackdropLive(live);
    return live;
}
