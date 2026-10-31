// The frame loop: the per-frame front-end tick and the bodies of the three SDL
// callbacks. main.cpp keeps the entry points themselves.
// Included by main.cpp inside its anonymous namespace.

static SDL_AppResult tickFrontend(App& state) {
    App* app = &state;
#ifdef DAYBREAK_ONLINE
    // Through the result and VS screens too: peers tell each other they are still there.
    if (app->frontend.online && !app->netSession) app->frontend.online->lobby->poll(16);
#endif
    auto anyPressed = [&](fnd::input::Action action) {
        for (const auto& player : app->tickInput) if (player.just_pressed[action]) return true;
        return false;
    };
    auto anyDown = [&](fnd::input::Action action) {
        for (const auto& player : app->tickInput) if (player.down[action]) return true;
        return false;
    };
    ui::ScreenInput in;
    in.up      = anyPressed(fnd::input::Up);
    in.down    = anyPressed(fnd::input::Down);
    in.left    = anyPressed(fnd::input::Left);
    in.right   = anyPressed(fnd::input::Right);
    in.confirm = anyPressed(fnd::input::Jump);
    in.cancel  = anyPressed(fnd::input::AttackA);
    in.start   = anyPressed(fnd::input::Pause);
    in.escape  = std::exchange(app->storyEscape, false);
    // The held state beside the edges (screen.h): the select screen's free cursor slides while
    // a direction is down, which an edge alone cannot express on the keyboard path.
    in.upHeld    = anyDown(fnd::input::Up);
    in.downHeld  = anyDown(fnd::input::Down);
    in.leftHeld  = anyDown(fnd::input::Left);
    in.rightHeld = anyDown(fnd::input::Right);
    in.separatePlayers = true;
    for (int p = 0; p < 4; ++p) {
        const auto& input = app->tickInput[p];
        auto& buttons = in.players[p];
        buttons.up = input.just_pressed[fnd::input::Up];
        buttons.down = input.just_pressed[fnd::input::Down];
        buttons.left = input.just_pressed[fnd::input::Left];
        buttons.right = input.just_pressed[fnd::input::Right];
        buttons.confirm = input.just_pressed[fnd::input::Jump];
        buttons.cancel = input.just_pressed[fnd::input::AttackA];
        buttons.upHeld = input.down[fnd::input::Up];
        buttons.downHeld = input.down[fnd::input::Down];
        buttons.leftHeld = input.down[fnd::input::Left];
        buttons.rightHeld = input.down[fnd::input::Right];
    }
    const ui::ScreenId previousScreen = app->screens.current();
    app->screens.update(in);
    if (previousScreen != app->screens.current()) {
        // FUN_00404ff0:0x405096 starts the movie's BGM from inside the scene, on the tick the
        // start call runs — i.e. on the first update after the scene was constructed. It is a
        // one-shot the screen hands up rather than a takeSound() cue, because it names a track
        // and the cue table is the system-SE bank.
        if (app->screens.current() == ui::ScreenId::Opening) {
            auto* opening = dynamic_cast<ui::OpeningScreen*>(app->screens.mutableScreen());
            if (opening && opening->takeBgmRequest())
                playFrontendMusic(*app, ui::ScreenId::Opening);
        }
        if (app->screens.current() == ui::ScreenId::Battle) app->lastTime = plat::now();
    } else if (app->screens.current() == ui::ScreenId::Opening &&
               app->screens.transitionInFlight()) {
        // Leaving the opening movie: start the incoming scene's music when the fade BEGINS,
        // not when the swap happens 25 frames later. The movie's own audio ends with its last
        // frame, so a title track that waited for the swap left an audible hole — the menu
        // theme cut in a third of a second after the film's music stopped.
        //
        // SCOPED to the movie on purpose. Its audio ending with its last frame is what makes
        // the hole, and no other front-end scene has that property, so every other transition
        // keeps the recovered order (the scene is built at the end of the fade). Widening it
        // would move every track's start by the fade length for no reported reason.
        // playFrontendMusic is idempotent per track, so this fires once and the factory's
        // later call for the same scene is a no-op.
        //
        // Scene 0x00 is excluded as a DESTINATION because it starts its own track from inside
        // the scene, on the tick the movie starts (FUN_00404ff0:0x405096) — see the factory.
        const ui::ScreenId pending = app->screens.pending();
        if (pending != ui::ScreenId::Quit && pending != ui::ScreenId::Opening)
            playFrontendMusic(*app, pending);
    }
    if (!app->error.empty()) return SDL_APP_FAILURE;
    if (app->menuAudio.music_queued_frames() < 4096)
        app->menuBgmPushed += app->menuLoop.push_next(app->menuAudio, 1024);
    const std::string track = app->screens.takeMusic();
    if (!track.empty()) playMenuTrack(*app, track.c_str());
    if (app->screens.takeMusicStop()) playMenuTrack(*app, nullptr);
    const std::string voice = app->screens.takeVoice();
    if (!voice.empty()) {
        // FUN_0040f4c0's case 4: a story line cuts off the one before it.
        if (app->screens.current() == ui::ScreenId::StoryAdv)
            app->menuAudio.stop_bus(fnd::audio::SfxBus::Voice);
        auto& source = fnd::assets::assetSource();
        const size_t dot = voice.find_last_of('.');
        const std::string stem = dot == std::string::npos ? voice : voice.substr(0,dot);
        const std::string path = source.resolve({stem+".cnv",stem+".wav"});
        const auto handle = loadSoundAsset(app->menuAudio,path);
        if (app->menuAudio.play(handle,fnd::audio::SfxBus::Voice) >= 0) ++app->menuVoicePlays;
    }
    if (app->screens.current() == ui::ScreenId::Battle && app->frontendBattleReady && app->screens.fadeFrame() == 0) {
        // The stack's fade is done: the round starts now, and the core plays its own 3-2-1
        // while the fighters fall, with commands locked (battle_startup.hpp).
        app->screensMode = false;
        app->matchMode = true;
        return SDL_APP_CONTINUE;
    }
    const int cue = app->screens.takeSound();
    if (cue >= 0 && cue < 4 && app->menuSounds[cue] >= 0) {
        app->menuAudio.stop(fnd::audio::kUiChannel);
        if (app->menuAudio.play(app->menuSounds[cue], fnd::audio::SfxBus::Ui) >= 0)
            ++app->menuSoundPlays[cue];
    }
    // 終了 reaches here: its item returns 0x16, the factory has no such scene, and
    // the switcher reads the null scene as "no scene: quit" (frontend/screen.h).
    if (app->screens.finished()) return app->error.empty() ? SDL_APP_SUCCESS : SDL_APP_FAILURE;

    return SDL_APP_CONTINUE;
}

static SDL_AppResult appIterate(App* app) {

    // Rendering measures wall time; combat and menu frame counters use 60 Hz ticks.
    const double now = plat::now();
    const double delta = now - app->lastTime;
    app->lastTime = now;
    if (app->frames > 0) {  // skip the first sample: it includes setup time
        app->deltaSum += delta;
        if (delta < app->deltaMin) app->deltaMin = delta;
        if (delta > app->deltaMax) app->deltaMax = delta;
    }
    ++app->frames;

    // Issue #4: keep the delivery client's transfers moving during normal frames. It never
    // blocks and never sleeps — one call per frame is what lets the optional startup assets
    // (the movie, BGM) finish after the gate has already let the front end open, and what
    // drives the match group while the VS presentation plays. Native builds no-op.
    plat::assetClient().poll();

    const bool capturing = !app->opts.out.empty();

    // Render-FPS meter tick (D1): wall-clock frames per second, frozen at 60
    // while capturing so the counter cannot make two --out runs differ.
    if (capturing) {
        app->fpsShown = 60;
        app->fpsWindow = 0.0;
        app->fpsFrames = 0;
    } else if (app->frames > 1) {  // first delta includes setup time
        app->fpsWindow += delta;
        ++app->fpsFrames;
        if (app->fpsWindow >= 0.5) {
            app->fpsShown = (int)std::lround((double)app->fpsFrames / app->fpsWindow);
            app->fpsWindow = 0.0;
            app->fpsFrames = 0;
        }
    }

    if (capturing) {
        // Verify with real time, not with a fixed step: the pose follows the clock, so
        // a capture after N frames of --dt is the pose at N * dt seconds.
        if (app->opts.anim >= 0 && app->frames > 1) advanceAnimation(*app, (double)app->opts.dt);
    } else if (!app->controllers.empty() && !app->matchMode && !app->frontendMatch) {
        advanceAnimation(*app, delta);
    }

    if (app->versusMode) tickVersus(*app, app->frames);
    if (app->matchInputReady) {
        app->matchInput.poll(false);
        app->matchInput.sample_tick_inputs(app->pendingInput);
    }
    pollUserSettings(*app, now);
    // The toon toggle is a draw-time switch (issue #21): the Options row flips live state
    // and the renderer's copy follows it here, so no scene re-upload and no restart is
    // behind the change. Only the interactive frontend reaches this (settingsActive is
    // false for every capture recipe), and an explicit --toon/--no-toon still wins.
    if (app->settingsActive && app->rendererReady) {
        const bool toon = app->opts.toonSet ? app->opts.toon
                                            : ui::frontendSettings().toonRendering;
        const bool shadows = app->opts.shadowsSet ? app->opts.shadows
                                                  : ui::frontendSettings().shadowRendering;
        if (toon != app->appearance.toon || shadows != app->appearance.shadows) {
            app->appearance.toon = toon;
            app->appearance.shadows = shadows;
            app->renderer.setAppearance(app->appearance);
        }
    }
    // The animation browser owns its own clock rather than the match's fixed step, so the
    // clip advances at wall-clock rate and reads as a smooth player.
    if (app->opts.animPlayer) animPlayerTick(*app, delta);

    // While paused the clock is not advanced at all, so paused wall time cannot become
    // catch-up ticks when the pause ends; the paused ticks still run so the device queues
    // are drained and the menu can be driven (issue #15).
#ifdef DAYBREAK_ONLINE
    // A capture runs as fast as it can, but peers and their timeouts live in real time.
    if (capturing && app->frontend.online) {
        static auto next = std::chrono::steady_clock::now();
        next += std::chrono::nanoseconds(1000000000 / 60);
        std::this_thread::sleep_until(next);
    }
#endif
    const int ticks = capturing ? 1
                    : (app->battlePaused ? 1
                                         : app->logicClock.advance(app->frames > 1 ? delta : 0.0));
    app->matchAlpha = matchAlphaFor(*app, capturing);
    for (int tick = 0; tick < ticks; ++tick) {
        ++app->logicTicks;
        for (int p = 0; p < 4; ++p) app->tickInput[p] = app->pendingInput[p].consume();
        driveSyntheticLocalPads(*app);
        if (app->matchInput.script_active()) {
            const uint64_t scriptTick = app->frontendMatch || app->screensMode
                ? app->logicTicks : app->matchFrame + 1 + app->pauseScriptAdvance;
            // Publish the scene before sampling so a `WAIT <scene>` directive sees the
            // scene this tick is actually running rather than the previous one.
            app->matchInput.set_scene_name(app->screens.currentName());
            app->matchInput.sample_script(app->scriptInput, scriptTick);
            app->tickInput[0] = app->scriptInput;
        }
        if (app->matchMode) {
            if (app->battlePaused) {
                const SDL_AppResult result = tickBattlePause(*app);
                if (result != SDL_APP_CONTINUE) return result;
                continue;   // frozen: no match step, no animation, no counters this tick
            }
            if (battlePauseAvailable(*app) && battlePausePressed(*app)) {
                enterBattlePause(*app, "pause key");
                continue;
            }
            // --pause-overlay=N's pause, on the tick the match frame reaches N — the same
            // entry the key uses, so the capture that follows is a real paused frame.
            // Parsed only with --out, so no played run can reach this.
            if (app->opts.pauseOverlay > 0 && app->matchFrame >= (uint64_t)app->opts.pauseOverlay) {
                enterBattlePause(*app, "--pause-overlay");
                continue;
            }
            if (!capturing) advanceAnimation(*app, gameplay::FixedStep::seconds);
            tickMatch(*app, capturing ? app->opts.dt : gameplay::FixedStep::seconds);
            traceMatch(*app);
            // --local-players evidence: the per-view cameras/HUD values every 128 ticks,
            // bounded by the run's own length so a long run cannot flood the log.
            if (app->opts.localPlayers > 0 && app->matchFrame % 128 == 0)
                reportMatchViews(*app, capturing ? (uint32_t)app->opts.sizeW : app->sc.width,
                                 capturing ? (uint32_t)app->opts.sizeH : app->sc.height);
#ifdef DAYBREAK_ONLINE
            // Online there is no pause to leave from, so this key leaves. The others get a COM.
            if (app->frontend.online && app->netSession && !capturing && battlePausePressed(*app)) {
                app->frontend.onlineMessage.clear();
                endOnlineMatch(*app);
                stopCombatAudio(*app);
                leaveBattleTo(*app, ui::ScreenId::NetplayMenu);
                continue;
            }
            // Stuck on the first frame: someone's address does not answer.
            if (app->frontend.online && app->netSession && app->netSession->frame() == 0 && ++app->netWaitTicks > 20 * 60) {
                app->frontend.onlineMessage = "Could not reach every player.";
                endOnlineMatch(*app);
                stopCombatAudio(*app);
                leaveBattleTo(*app, ui::ScreenId::NetplayMenu);
                continue;
            }
            const bool roundOver = app->frontend.online && app->netSession ? app->netSession->round_over_confirmed()
                                                                           : app->battle->economy().roundOver();
#else
            const bool roundOver = app->battle->economy().roundOver();
#endif
            if (app->frontendMatch && roundOver) {
                // The economy reports the WINNING side (issue #11); the DX9 port
                // reported the burst side here and this line inverted it.
                const gameplay::MatchEconomy& eco = app->battle->economy();
                app->frontend.resultWinner = eco.roundOverSide();
                app->frontend.matchFrame = app->matchFrame;
                // The quote rule's inputs (FUN_00635d40:288-318): the balloon margin, clamped
                // by the winner's own capacity, and whether both winners ended below half HP.
                {
                    const int winner = std::max(0, app->frontend.resultWinner);
                    const int loser = 1 - winner;
                    const int winnerCapacity = (int)eco.capacity(winner);
                    const int loserBalloon = (int)eco.balloon(loser);
                    const int winnerBalloon = (int)eco.balloon(winner);
                    app->frontend.resultMargin =
                        std::min(winnerCapacity, loserBalloon) - winnerBalloon;
                    bool hurt = true;
                    for (int i = 0; i < app->battle->fighter_count(); ++i)
                        if (app->battle->side(i) == winner &&
                            app->battle->fighter(i).hp() * 2 >= app->battle->fighter(i).max_hp())
                            hurt = false;
                    app->frontend.resultWinnersHurt = hurt;
                }
                for (int i = 0; i < app->battle->fighter_count(); ++i) {
                    const auto& stats = app->battle->fighter(i).stats();
                    const int panel = app->battleLaunch.fighters[i].panel;
                    app->frontend.resultStats[panel] = {stats.kos,stats.deaths,stats.damageDealt,stats.damageTaken};
                    // The core chose the earned title with the round's real counters.
                    const int title = app->battle->fighter(i).result_title();
                    static gameplay::ResultTitleTable titleTable;
                    static bool titleTableTried = false;
                    if (!titleTableTried) {
                        titleTableTried = true;
                        std::string titleError;
                        const std::string& install = fnd::assets::assetSource().installDir();
                        if (install.empty() ||
                            !gameplay::loadResultTitles(install + "/DaybreakDX.exe", titleTable,
                                                        titleError))
                            std::fprintf(stderr, "[title] names unavailable: %s\n",
                                         titleError.empty() ? "no install open" : titleError.c_str());
                    }
                    app->frontend.resultTitleText[panel] = titleTable.text(title);
                    // The penalty title's session flag (FUN_00635d40:377-380), keyed by the panel
                    // because that is a local player's stable identity here. Session state only:
                    // it is never written to any settings file.
                    if (title == gameplay::kResultTitlePenalty &&
                        app->frontend.slots[panel].controller < 4)
                        app->frontend.penaltyDecided[panel] = true;
                    std::printf("[title] panel %d fighter %d -> %d '%s'\n", panel, i, title, titleTable.text(title));
                }
#ifdef DAYBREAK_ONLINE
                endOnlineMatch(*app);
#endif
                app->matchMode = false;
                app->frontendBattleReady = false;
                app->versusAudio.clear_music();
                // The match is over: release every channel the combat layer claimed, so the
                // result screen's own cues and the next match start from a clean bus
                // (issue #16's repeated-match cleanup). The decoded sample cache stays.
                reportCombatAudio(*app);
                stopCombatAudio(*app);
                if (app->frontend.story.active && app->frontend.resultWinner == 0) {
                    // FUN_00403b70: a won story fight goes back to the dialogue.
                    app->screens.request(ui::ScreenId::StoryAdv);
                } else {
                    app->screens.requestInstant(ui::ScreenId::Result);
                    app->resultOverScene = true;
                }
                app->screensMode = true;
                const SDL_AppResult result = tickFrontend(*app);
                if (result != SDL_APP_CONTINUE) return result;
            }
        } else if (app->screensMode) {
            if (app->resultOverScene) tickResultScene(*app, capturing ? app->opts.dt : gameplay::FixedStep::seconds);
            const SDL_AppResult result = tickFrontend(*app);
            if (result != SDL_APP_CONTINUE) return result;
            app->resultOverScene = app->resultOverScene && app->screens.current() == ui::ScreenId::Result;
            // Loading a new battle must not turn asset-load time into combat ticks.
            if (app->matchMode) {
                app->lastTime = plat::now();
                return SDL_APP_CONTINUE;
            }
        }
    }

    if (app->matchMode || app->resultOverScene) {
        placeFxCards(*app);
        placeMatchFighters(*app);
    }

    if (app->screensMode && !app->resultOverScene) {

        if (capturing) {
            if (app->frames >= (uint64_t)app->opts.frames) {
                std::vector<uint8_t> rgba;
                ScreenCaptureHook hook{&app->screens, &app->uiRenderer, &app->error};
                // captureUi: a menu frame has no 3D scene, so the scene pass is skipped
                // and the UI hook draws onto the cleared target (scene_renderer.h).
                if (!app->renderer.captureUi((uint32_t)app->opts.sizeW,
                                             (uint32_t)app->opts.sizeH, rgba, app->error,
                                             screenCaptureHook, &hook))
                    return SDL_APP_FAILURE;
                reportCoverage(rgba, app->opts.sizeW, app->opts.sizeH);
                writePpm(app->opts.out, rgba, app->opts.sizeW, app->opts.sizeH);
                reportShadows(app->renderer.stats());
                maybeDumpShadowMap(*app);
                return SDL_APP_SUCCESS;
            }
            return SDL_APP_CONTINUE;   // wait for the capture frame, as the asset path does
        }

        gpu::Frame frame;
        if (!gpu::beginFrame(app->ctx, app->sc, frame, app->error)) return SDL_APP_FAILURE;
        // Clear first: the UI pass loads (sprite.cpp:468), the screen art is authored
        // 800x600, and a larger window would otherwise present undefined backbuffer
        // pixels around it. Same opaque-black background captureUi gives a --out frame.
        WGPURenderPassColorAttachment clear = {};
        clear.view = frame.view;
        clear.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;
        clear.loadOp = WGPULoadOp_Clear;
        clear.storeOp = WGPUStoreOp_Store;
        clear.clearValue = WGPUColor{0.0, 0.0, 0.0, 1.0};
        WGPURenderPassDescriptor clearPass = {};
        clearPass.colorAttachmentCount = 1;
        clearPass.colorAttachments = &clear;
        WGPURenderPassEncoder clearRp =
            wgpuCommandEncoderBeginRenderPass(frame.encoder, &clearPass);
        wgpuRenderPassEncoderEnd(clearRp);
        wgpuRenderPassEncoderRelease(clearRp);
        if (!ui::drawScreenFrame(app->screens, app->uiRenderer, app->sc.width, app->sc.height,
                                 frame.encoder, frame.view, app->sc.format, app->error)) {
            gpu::endFrame(app->ctx, app->sc, frame);
            return SDL_APP_FAILURE;
        }
        if (!gpu::endFrame(app->ctx, app->sc, frame)) return SDL_APP_FAILURE;
    } else if (hasAsset(app->opts)) {
        const uint32_t w = capturing ? (uint32_t)app->opts.sizeW : app->sc.width;
        const uint32_t h = capturing ? (uint32_t)app->opts.sizeH : app->sc.height;
        // Not in match mode: tickMatch already stepped the ported reference camera,
        // and this block's spring would overwrite its eye with the demo's own framing.
        // The countdown is the same case (issue #47): its views carry the arena camera.
        if (app->opts.camera == "arena" && !app->matchMode && !app->resultOverScene) {
            // First frame seeds from the desired eye, so single-frame captures stay
            // exactly deterministic; longer runs converge through the dt-correct
            // spring instead of snapping.
            if (!app->havePrevEye) {
                app->prevEye = app->arenaDesired;
                app->havePrevEye = true;
            }
            // Captures step the spring with the fixed --dt, not wall time: the
            // eye must be as deterministic as the pose or captures would drift.
            const double stepDt = capturing ? (double)app->opts.dt : delta;
            // Clamp the desired eye against the stage's camera collision mesh before
            // smoothing, exactly as the reference composes it (arena_camera.cpp:106-131):
            // one query, the 20-unit margin inside arenaClampEye, no second refine pass.
            // Stages without camera geometry answer "no hit" and this is a pass-through.
            glm::vec3 desired = app->arenaDesired;
            if (!app->opts.noCameraClamp) {
                const game::CameraClampResult clamp =
                    app->cameraCollision.queryClamp({app->target, desired});
                if (clamp.hit) {
                    const float segment = glm::length(desired - app->target);
                    desired = render::arenaClampEye(app->target, desired,
                                                    game::clampHitDistance(clamp, segment));
                }
            }
            app->eye = render::arenaSmoothEyeDt(app->prevEye, desired, (float)stepDt, 0.1f);
            app->prevEye = app->eye;
        }
        // This frame's views (issue #12): a match builds one per human controller — its own
        // camera, its own cell and its own HUD — while every other asset path keeps the one
        // historical view, whose matrix the scene and prims passes have always shared.
        // Match frames use the reference camera's own projection (fov pi/4, near 50,
        // far 150000) so a foundation frame and a banked DX9 frame of the same case differ
        // by their content, not by their projection.
        std::vector<FrameView> frameViews;
        std::vector<render::ViewCamera> frameCameras;
        glm::mat4 vp;
        // A countdown frame takes the match's own camera path (issue #47): the match is
        // built and its per-view cameras are already converging on the spawns, so the digit
        // is drawn over the real arena, at the real split-screen cells.
        if (app->matchMode || app->resultOverScene) {
            buildFrameViews(*app, w, h, frameViews);
            for (const FrameView& view : frameViews) frameCameras.push_back(view.camera);
            vp = frameCameras.front().viewProj;
            // The primary view's interpolated presentation eye/aim: the paths that read
            // app.eye/app.target (billboard eye, debug crosses) stay on the first player.
            app->eye = frameCameras.front().eye;
            app->target = glm::mix(app->matchViews[0].previousTarget,
                                   app->matchViews[0].camera.target(), app->matchAlpha);
        } else {
            // Every other path: one view over the whole target, the matrix the scene and
            // prims passes have always shared in this branch.
            vp = viewProj(app->eye, app->target, (float)w / (float)h, app->cameraRadius,
                          app->sceneReach);
            render::ViewCamera camera;
            camera.viewProj = vp;
            camera.eye = app->eye;
            frameCameras.push_back(camera);
        }
        // The UI batch gives each render() call one vertex region and one uniform slot, and
        // wraps round-robin past the budget. beginFrame() is per-batch, so the renderer
        // cannot see a frame boundary and cannot detect the wrap; this is the one place that
        // knows how many passes this frame will compose, so the check lives here (issue #56
        // review). The HUD draws one pass per view plus the separator, and a countdown frame
        // adds the overlay and possibly the clip-browser caption.
        {
            const size_t uiPasses = frameCameras.size() + 1 /*separator*/ + (app->resultOverScene ? 1u : 0u);
            if (uiPasses > ui::SpriteRenderer::kMaxPassesPerFrame) {
                std::fprintf(stderr,
                             "[ui] %zu passes on one renderer exceed the %u-region budget; "
                             "passes would alias (issue #56)\n",
                             uiPasses, ui::SpriteRenderer::kMaxPassesPerFrame);
                std::abort();
            }
        }
        app->renderer.setCamera(vp);
        app->renderer.setEye(app->eye);

        if (capturing) {
            // --out without --frames means one frame, so the last frame is always defined.
            if (app->frames >= (uint64_t)app->opts.frames) {
                std::vector<uint8_t> rgba;
                HudTestHook hook = battleHudHook(*app);
                if (app->matchMode) appendMatchHudPasses(*app, frameViews, w, h, hook);
                const bool useHud = (app->opts.hudTest || app->versusMode || app->matchMode) &&
                                    app->uiReady;
                CaptureHook cap;
                cap.renderer = &app->renderer;
                cap.error = &app->error;
                cap.views = frameCameras;
                if (app->battlePaused) cap.pauseApp = app;
                if (useHud) cap.hud = &hook;
                // One batch for both sources: the debug overlay and the match's
                // shots/sparks share the pass, so neither can clobber the other.
                if (app->opts.debugPrims || app->matchMode) {
                    if (app->opts.debugPrims) fillDebugLines(*app);
                    else app->debugLines.clear();
                    if (app->matchMode) fillMatchCubes(*app);
                    cap.prims = &app->debugPrims;
                    cap.lines = &app->debugLines;
                    if (app->matchMode) {
                        cap.solid = &app->matchCubes;
                        cap.additive = &app->auraCubes;
                    }
                }
                const bool useHook = useHud || cap.prims;
                // Only more than one view takes the split-screen scene pass; a single view
                // keeps render()'s exact commands (and the banked captures' pixels).
                const std::vector<render::ViewCamera>* viewArg =
                    (app->matchMode || app->resultOverScene) && frameCameras.size() > 1
                        ? &frameCameras : nullptr;
                ScreenCaptureHook overlay{&app->screens, &app->uiRenderer, &app->error, true};
                render::SceneRenderer::UiHook uiHook = nullptr;
                void* uiData = nullptr;
                if (app->resultOverScene) { uiHook = screenCaptureHook; uiData = &overlay; }
                else if (useHook) { uiHook = captureHook; uiData = &cap; }
                if (!app->renderer.capture((uint32_t)app->opts.sizeW,
                                           (uint32_t)app->opts.sizeH, rgba, app->error,
                                           uiHook, uiData, viewArg))
                    return SDL_APP_FAILURE;
                reportCoverage(rgba, app->opts.sizeW, app->opts.sizeH);
                writePpm(app->opts.out, rgba, app->opts.sizeW, app->opts.sizeH);
                reportShadows(app->renderer.stats());
                maybeDumpShadowMap(*app);
                // Issue #25's cost measurement: the capture above proves what the frame
                // looks like, this proves what it costs. Both run the same scene state;
                // the benchmark allocates its own target so the capture's bytes are
                // already on disk before it starts.
                if (app->opts.bench > 0) {
                    double ms = 0.0;
                    if (!app->renderer.benchmark((uint32_t)app->opts.sizeW,
                                                 (uint32_t)app->opts.sizeH, app->opts.bench,
                                                 ms, app->error, viewArg))
                        return SDL_APP_FAILURE;
                    const render::Stats& bs = app->renderer.stats();
                    std::printf("bench: %d frames, mean %.4f ms/frame (%.0f fps), "
                                "%zu draws (%d outlines, %d effects)\n",
                                app->opts.bench, ms, ms > 0.0 ? 1000.0 / ms : 0.0,
                                bs.draws, bs.outlines, bs.effects);
                }
                if (app->opts.debugPrims) {
                    const render::DebugPrims::Stats& ds = app->debugPrims.stats();
                    std::printf("debug prims : %zu line(s), %zu vertices, %zu dropped, %zu pass(es)\n",
                                ds.lines, ds.vertices, ds.droppedVertices, ds.passes);
                }
                // The front-end battle runs the same Match as --match, so its end-of-run
                // summary (and issue #14's per-COM counters) is printed for it too.
                if (app->matchMode || app->frontendMatch) {
                    reportMatchViews(*app, w, h);
                    const gameplay::MatchEconomy& eco = app->battle->economy();
                    std::printf("match: %llu frames, hp1=%d hp2=%d, balloon=%.0f%%/%.0f%% "
                                "(LIMIT %.0f%%/%.0f%%), "
                                "fx events=%llu, bgm pushed %llu frames, %llu wraps, roundOver=%d\n",
                                (unsigned long long)app->matchFrame, app->battle->fighter(0).hp(),
                                app->battle->fighter(1).hp(), (double)eco.balloon(0),
                                (double)eco.balloon(1), (double)eco.capacity(0),
                                (double)eco.capacity(1),
                                (unsigned long long)app->matchFxEvents,
                                (unsigned long long)app->versusBgmPushed,
                                (unsigned long long)app->versusLoop.loops_completed(),
                                app->matchRoundOverFrame ? 1 : 0);
                    // Issue #11's single-counted audit: one KO credit per death, one
                    // Overkill credit per hit, one respawn per return.
                    reportCombatAudio(*app);
                    std::printf("match round : winner=%d (%s), KOs=%d/%d overkill=%d/%d "
                                "respawns=%d/%d, time left=%.1fs\n",
                                eco.roundOverSide(),
                                eco.roundEnd() == gameplay::RoundEnd::Timeout ? "time up" :
                                (eco.roundEnd() == gameplay::RoundEnd::Burst ? "burst" : "running"),
                                eco.kos(0), eco.kos(1), eco.overkills(0), eco.overkills(1),
                                eco.respawns(0), eco.respawns(1), eco.timeLeft());
                    // Issue #17's effect population (see printFxSummary).
                    printFxSummary(*app);
                }
                if (app->versusMode) {
                    std::printf("versus: %llu frames, hp1=%.0f hp2=%.0f, bgm pushed %llu frames, %llu wraps, sfx plays %llu, fx events %llu\n",
                                (unsigned long long)app->frames, (double)app->versusHud.hp, 100.0,
                                (unsigned long long)app->versusBgmPushed,
                                (unsigned long long)app->versusLoop.loops_completed(),
                                (unsigned long long)app->versusSfxPlays,
                                (unsigned long long)app->versusFxEvents);
                    printFxSummary(*app);
                }
                return SDL_APP_SUCCESS;
            }
            return SDL_APP_CONTINUE;
        }

        gpu::Frame frame;
        if (!gpu::beginFrame(app->ctx, app->sc, frame, app->error)) {
            // A lost/outdated surface is recoverable in principle; for the foundation
            // demo it is enough to stop cleanly rather than spin on a broken swapchain.
            return SDL_APP_FAILURE;
        }
        render::Target target;
        target.encoder = frame.encoder;
        target.colorView = frame.view;
        target.format = app->sc.format;
        target.width = app->sc.width;
        target.height = app->sc.height;
        const bool multiView = (app->matchMode || app->resultOverScene) && frameCameras.size() > 1;
        const bool sceneOk = multiView ? app->renderer.renderViews(target, frameCameras, app->error)
                                       : app->renderer.render(target, app->error);
        if (!sceneOk) {
            gpu::endFrame(app->ctx, app->sc, frame);
            return SDL_APP_FAILURE;
        }
        if (app->opts.debugPrims || app->matchMode) {
            if (app->opts.debugPrims) fillDebugLines(*app);
            else app->debugLines.clear();
            if (app->matchMode) fillMatchCubes(*app);
            for (const render::ViewCamera& camera : frameCameras) {
                if (app->matchMode && !app->matchCubes.empty()) {
                    render::DebugPrims::Options cubeOptions;
                    cubeOptions.viewport = camera.rect;
                    if (!app->debugPrims.drawCubes(target, camera.viewProj, app->matchCubes,
                                                   app->renderer.depthView(), cubeOptions,
                                                   app->error)) {
                        gpu::endFrame(app->ctx, app->sc, frame);
                        return SDL_APP_FAILURE;
                    }
                }
                if (app->matchMode && !app->auraCubes.empty()) {
                    render::DebugPrims::Options cubeOptions;
                    cubeOptions.additive = true;
                    cubeOptions.viewport = camera.rect;
                    if (!app->debugPrims.drawCubes(target, camera.viewProj, app->auraCubes,
                                                   app->renderer.depthView(), cubeOptions,
                                                   app->error)) {
                        gpu::endFrame(app->ctx, app->sc, frame);
                        return SDL_APP_FAILURE;
                    }
                }
                // depth-tested: lines behind walls hide
                render::DebugPrims::Options primOptions;
                primOptions.viewport = camera.rect;
                if (!app->debugPrims.draw(target, camera.viewProj, app->debugLines,
                                          app->renderer.depthView(), primOptions, app->error)) {
                    gpu::endFrame(app->ctx, app->sc, frame);
                    return SDL_APP_FAILURE;
                }
            }
        }
        if (app->opts.animPlayer && app->uiReady && !app->scene.models.empty()) {
            char buf[160];
            const xm::Model& m = app->scene.models[0].model;
            const char* name = (app->apIndex >= 0 && app->apIndex < (int)m.anims.size())
                                   ? m.anims[app->apIndex].name.c_str() : "(none)";
            std::snprintf(buf, sizeof(buf), "[%d/%d]  %s", app->apIndex,
                          (int)m.anims.size(), name);
            const std::string line = buf;
            const std::string hint = "arrows: set index    WASD: orbit";
            std::string textError;
            if (app->apText.load(app->uiRenderer, 14.f, textError) &&
                app->apText.prepare(app->uiRenderer, {line, hint}, textError)) {
                app->uiRenderer.beginFrame(app->sc.width, app->sc.height);
                app->apText.draw(app->uiRenderer, line.c_str(), 24.f, 20.f, 1.f, ui::kHudWhite);
                app->apText.draw(app->uiRenderer, hint.c_str(), 24.f, 40.f, 1.f, ui::kHudWhite);
                if (!app->uiRenderer.render(frame.encoder, frame.view, app->sc.format, app->error)) {
                    gpu::endFrame(app->ctx, app->sc, frame);
                    return SDL_APP_FAILURE;
                }
            }
        }
        if (!drawBattlePauseOverlay(*app, frame.encoder, frame.view, app->sc.width,
                                    app->sc.height, app->sc.format)) {
            gpu::endFrame(app->ctx, app->sc, frame);
            return SDL_APP_FAILURE;
        }
        if (app->uiReady && (app->opts.hudTest || app->matchMode || app->versusMode)) {
            HudTestHook hook = battleHudHook(*app);
            if (app->matchMode)
                appendMatchHudPasses(*app, frameViews, app->sc.width, app->sc.height, hook);
            if (!hudTestHook(frame.encoder,frame.view,app->sc.format,app->sc.width,app->sc.height,&hook)) {
                gpu::endFrame(app->ctx,app->sc,frame);
                return SDL_APP_FAILURE;
            }
        }
        if (app->resultOverScene &&
            !ui::drawScreenOverlay(app->screens, app->uiRenderer, app->sc.width, app->sc.height,
                                   frame.encoder, frame.view, app->sc.format, app->error)) {
            gpu::endFrame(app->ctx, app->sc, frame);
            return SDL_APP_FAILURE;
        }
        if (!gpu::endFrame(app->ctx, app->sc, frame)) return SDL_APP_FAILURE;
    } else {
        app->spin += (float)delta * 1.2f;
        const Mat4 transform = rotationZ(app->spin, 1.0f);
        wgpuQueueWriteBuffer(app->ctx.queue, app->uniformBuffer, 0, transform.m, sizeof(transform.m));

        gpu::Frame frame;
        if (!gpu::beginFrame(app->ctx, app->sc, frame, app->error)) return SDL_APP_FAILURE;

        WGPURenderPassColorAttachment color = {};
        color.view = frame.view;
        color.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;
        color.loadOp = WGPULoadOp_Clear;
        color.storeOp = WGPUStoreOp_Store;
        color.clearValue = WGPUColor{0.06, 0.07, 0.09, 1.0};

        WGPURenderPassDescriptor pass = {};
        pass.colorAttachmentCount = 1;
        pass.colorAttachments = &color;

        WGPURenderPassEncoder rp = wgpuCommandEncoderBeginRenderPass(frame.encoder, &pass);
        wgpuRenderPassEncoderSetPipeline(rp, app->pipeline);
        wgpuRenderPassEncoderSetBindGroup(rp, 0, app->bindGroup, 0, nullptr);
        wgpuRenderPassEncoderSetVertexBuffer(rp, 0, app->vertexBuffer, 0, WGPU_WHOLE_SIZE);
        wgpuRenderPassEncoderDraw(rp, 3, 1, 0, 0);
        wgpuRenderPassEncoderEnd(rp);
        wgpuRenderPassEncoderRelease(rp);

        if (!gpu::endFrame(app->ctx, app->sc, frame)) return SDL_APP_FAILURE;
    }

    if (app->opts.frames > 0 && app->frames >= (uint64_t)app->opts.frames) return SDL_APP_SUCCESS;
    return SDL_APP_CONTINUE;
}

static SDL_AppResult appEvent(App* app, SDL_Event* event) {
    switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
        case SDL_EVENT_KEY_DOWN:
            if (ui::bindingCaptureActive()) {
                app->matchInput.suppress_key((int)event->key.scancode);
                if (event->key.key == SDLK_ESCAPE) ui::cancelBindingCapture();
                else if (!event->key.repeat) ui::submitBindingInput(true, 0, (int)event->key.scancode);
                return SDL_APP_CONTINUE;
            }
            app->matchInput.note_key((int)event->key.scancode, true);
            if (event->key.key == SDLK_ESCAPE && app->screensMode &&
                app->screens.current() == ui::ScreenId::StoryAdv) {
                // FUN_0040eb30:20-22: Escape leaves the story for the title, not the game.
                app->storyEscape = true;
                return SDL_APP_CONTINUE;
            }
            if (event->key.key == SDLK_ESCAPE) {
                // A live offline battle: Escape opens the pause menu (or leaves it) instead
                // of killing the process — the audit's "Escape exits immediately" is what
                // this replaces. Every capture/replay path keeps the old behaviour, and so
                // does every menu screen.
                if (battlePauseAvailable(*app)) {
                    if (app->battlePaused) resumeBattle(*app);
                    else enterBattlePause(*app, "Escape");
                    return SDL_APP_CONTINUE;
                }
                return SDL_APP_SUCCESS;
            }
            if (app->opts.animPlayer && !event->key.repeat) animPlayerKey(*app, event->key.key);
            break;
        case SDL_EVENT_KEY_UP:
            app->matchInput.note_key((int)event->key.scancode, false);
            break;
        case SDL_EVENT_WINDOW_FOCUS_LOST:
            // Owner decision: losing focus no longer pauses the battle. Held keys are still
            // dropped (a lost KEY_UP must not hold Guard) and the input backend ignores the
            // devices while unfocused, so the match keeps running but takes no input.
            app->matchInput.note_focus_lost();
            break;
        case SDL_EVENT_WINDOW_FOCUS_GAINED:
            // Focus gate: an unfocused window accepts no input — SDL reports pads whatever
            // the focus is. Focus is re-armed here and nowhere else; note_focus_gained also
            // re-derives the release-before-input snapshot, because releases that happened
            // while unfocused were never delivered. Losing focus did not pause the battle,
            // so nothing resumes here.
            app->matchInput.note_focus_gained();
            break;
        case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
            if (ui::bindingCaptureActive()) {
                const int player = app->matchInput.gamepad_player((int32_t)event->gbutton.which);
                app->matchInput.suppress_gamepad_button(player,(int)event->gbutton.button);
                ui::submitBindingInput(false, player, (int)event->gbutton.button);
            } else {
                const int player = app->matchInput.gamepad_player((int32_t)event->gbutton.which);
                app->matchInput.note_gamepad_button(player, (int)event->gbutton.button, true);
            }
            break;
        case SDL_EVENT_GAMEPAD_BUTTON_UP:
            app->matchInput.note_gamepad_button(
                app->matchInput.gamepad_player((int32_t)event->gbutton.which),
                (int)event->gbutton.button, false);
            break;
        case SDL_EVENT_WINDOW_DISPLAY_CHANGED:
            if (app->window) {
                const SDL_DisplayID display = SDL_GetDisplayForWindow(app->window);
                if (const SDL_DisplayMode* mode = SDL_GetDesktopDisplayMode(display))
                    ui::frontendSettings().displayResolution = {mode->w,mode->h};
            }
            break;
        case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED: {
            // A resized window needs the swapchain reconfigured, not just a new
            // viewport: the surface's back buffers are sized at configure time.
            const uint32_t w = (uint32_t)event->window.data1;
            const uint32_t h = (uint32_t)event->window.data2;
            if (w && h && !gpu::configureSwapchain(app->ctx, app->sc, w, h, app->error))
                return SDL_APP_FAILURE;
            if (app->window && w && h) {
                auto& settings = ui::frontendSettings();
                settings.currentResolution = {static_cast<int>(w),static_cast<int>(h)};
                if (settings.resolutionAvailable && !settings.fullscreen) {
                    auto current = std::find(settings.resolutions.begin(),settings.resolutions.end(),settings.currentResolution);
                    if (current == settings.resolutions.end()) {
                        settings.resolutions.push_back(settings.currentResolution);
                        settings.resolutionIndex = static_cast<int>(settings.resolutions.size()) - 1;
                    } else settings.resolutionIndex = static_cast<int>(current - settings.resolutions.begin());
                }
            }
            break;
        }
        default:
            break;
    }
    return SDL_APP_CONTINUE;
}

static void appQuit(App* app, SDL_AppResult result) {
    if (!app) return;
#if defined(_WIN32)
    if (result == SDL_APP_FAILURE && !app->opts.headless) {
        const char* message = app->error.empty()
            ? "The game stopped because an error occurred. Please report which character, weapon and stage were in use."
            : app->error.c_str();
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Higurashi Daybreak port", message, app->window);
    }
#endif
    if (!app->opts.screen.empty())
        std::printf("menu-audio: confirm=%llu back=%llu cursor=%llu ready=%llu voices=%llu "
                    "bgm=%llu frames\n",
            (unsigned long long)app->menuSoundPlays[0], (unsigned long long)app->menuSoundPlays[1],
            (unsigned long long)app->menuSoundPlays[2], (unsigned long long)app->menuSoundPlays[3],
            (unsigned long long)app->menuVoicePlays,
            (unsigned long long)app->menuBgmPushed);
    flushUserSettings(*app);   // last chance for a change made after the last screen exit
    ui::frontendSettings().applyVolumes = {};
    ui::frontendSettings().applyFullscreen = {};
    ui::frontendSettings().applyResolution = {};
    ui::frontendSettings().applyBindings = {};
    report(*app);
    teardown(*app);
    delete app;
}
