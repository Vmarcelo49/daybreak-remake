// Foundation demo: SDL3 window + WebGPU, one code path for Linux, Windows and web.
//
// With no asset argument it draws the spinning triangle that proves the
// multi-platform plumbing. With one (`--stage`, `--character`, `--weapon`,
// `--model`) it loads the game's real assets through the asset layer and draws
// them with render/scene_renderer: depth buffer, textures, per-draw uniforms,
// camera and stage fog. `--out` renders offscreen and writes a PPM, which is how
// the renderer is verified without a display.

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#include <algorithm>
#include <array>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <filesystem>
#include <cstdlib>
#include <random>
#include <deque>
#include <sstream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>

#include "gpu/gpu.h"
#include "assets/asset_source.h"
#include "assets/stage_catalog.h"
#include "platform/asset_client.h"
#include "platform/platform.h"
#include "platform/surface.h"
#include "platform/web_pack.h"
#include "camera/arena_view.h"
#include "render/debug_prims.h"
#include "render/scene_renderer.h"
// After the renderer on purpose: raycast.h includes assets/xmodel.h without
// XMODEL_WEBGPU (its queries need the mesh arrays, not the GPU helpers), and xmodel.h's
// include guard means a first include without that macro would hide xm::CameraUniform
// from scene_renderer.h further down.
#include "physics/raycast.h"
#include "movie/movie_player.h"
#include "hud/hud.h"
#include "hud/pause_layout.h"
#include "ui/sprite.h"
#include "frontend/screen.h"
#include "frontend/screen_vs.h"
#include "frontend/screen_opening.h"
#include "frontend/screen_story.h"
#include "ui/sheet_locale.h"
#include "frontend/frontend_state.h"
#include "frontend/frontend_launch.h"
#include "frontend/participants.h"
#include "frontend/frontend_settings.h"
#include "settings/user_settings.h"
#include "hud/hud_bridge.h"
#include "camera/fighter_pose.h"
#if defined(_WIN32)
#include <io.h>
#elif !defined(__EMSCRIPTEN__)
#include <unistd.h>
#endif
#ifdef DAYBREAK_ONLINE
#include <chrono>
#include <thread>

#include "frontend/screen_online.h"
#include "net/session.h"
#endif
#include "battle/match_view.h"
#include "hud/view_layout.h"
#include "camera/arena_camera.h"
#include "battle/battle_pause.h"
#include "battle/battle_view.h"
#include "battle/core_battle.h"
#include "battle/fixed_step.h"
#include "hud/hud_fill.h"
#include "frontend/result_title.h"
#include "audio/audio.h"
#include "audio/audio_engine.h"
#include "audio/combat_audio.h"
#include "render/effect_events.h"
#include "render/effect_catalog.h"
#include "render/aura_attach.h"
#include "render/fx_cards.h"
#include "render/muzzle_slot.h"
#include "render/shot_visual.h"
#include "input/input_backend.h"
#include "input/tick_input.h"
#include "input/input_sdl3.h"
#include "input/synthetic_pad.h"
#include "shaders/demo_wgsl.h"
#include <unordered_map>

namespace {
#include "app.h"
#include "app_forward.inc"
#include "options.inc"
#include "scene.inc"
#include "combat_audio.inc"
#include "match.inc"
#include "render_capture.inc"
#include "frame_loop.inc"


// --- persisted user settings (issue #19) ------------------------------------------
// The config file is read and written ONLY on a plain interactive frontend run. Every
// capture, replay or bounded run is a verification path: --match, --versus, --hud-test,
// --out/--headless captures and the asset viewers must produce the same frames and the
// same traces whether or not the user has a config file, so they neither read it nor
// write it. --screen=<menu> without a capture is interactive and does use it.
static bool usesUserConfig(const Options& o) {
    return o.frames == 0 && o.out.empty() && !o.headless && !o.match && !o.versus &&
           !o.hudTest && !o.list && !o.audioTest && !o.inputTest && o.anim < 0 &&
           o.model.empty() && o.stage.empty() && o.character.empty() && o.effect.empty();
}

// Load before anything the frontend builds: the volumes and bindings are live state, so
// they are in place before the first screen, and the display preference is applied later
// (initScreens owns the resolution list). A malformed file, an unsupported version or an
// unreadable directory all land here as "keep the defaults" plus a printed reason.
static std::string settingsFilePath() {
#if defined(_WIN32)
    // Explorer launches usually have no HOME/XDG variables. Use Windows user
    // application data so a portable release never writes settings into the game.
    if (!std::getenv("XDG_CONFIG_HOME")) {
        if (char* directory = SDL_GetPrefPath("", "daybreak-decomp")) {
            const std::string path = std::string(directory) + "settings.conf";
            SDL_free(directory);
            return path;
        }
    }
#endif
    return settings::defaultConfigPath();
}

static void loadUserSettings(App& app) {
    app.settingsPath = settingsFilePath();
    if (app.settingsPath.empty()) {
        std::printf("[settings] no $XDG_CONFIG_HOME or $HOME: running with defaults, "
                    "nothing will be written\n");
        return;
    }
    settings::LoadReport report;
    const bool loaded = settings::load(app.settingsPath, app.userSettings, report);
    for (const std::string& message : report.messages)
        std::printf("[settings] %s\n", message.c_str());
    ui::applyUserSettings(ui::frontendSettings(), app.userSettings);
    app.settingsActive = true;
    std::printf("[settings] %s: %s\n", app.settingsPath.c_str(),
                loaded ? "loaded" : "using defaults");
}

// The display half of the document, applied once the frontend has built the resolution
// list and installed the SDL callbacks. An unavailable size falls back to desktop (index
// 0) exactly like the Options screen's own cycle, so moving to a display that does not
// offer the stored mode cannot fail the launch.
static void applyPersistedDisplay(App& app) {
    if (!app.settingsActive) return;
    auto& settings = ui::frontendSettings();
    if (!settings.resolutionAvailable) return;   // headless/web: no modes to choose from
    std::vector<settings::DisplaySize> available;
    available.reserve(settings.resolutions.size());
    for (const ui::DisplayResolution& size : settings.resolutions)
        available.push_back({size.width, size.height});
    const int wanted = settings::chooseResolutionIndex(available, app.userSettings.resolution);
    if (app.userSettings.resolution != settings::DisplaySize{})
        std::printf("[settings] resolution %dx%d (%s)\n", app.userSettings.resolution.width,
                    app.userSettings.resolution.height,
                    wanted == 0 ? "not offered by this display, using desktop" : "restored");
    settings.resolutionIndex = wanted;
    settings.resolutionChoice = {app.userSettings.resolution.width, app.userSettings.resolution.height};
    if (app.userSettings.fullscreen) {
        settings.fullscreen = true;
        if (settings.applyFullscreen) settings.applyFullscreen(true);
        if (!settings.fullscreen)
            std::printf("[settings] fullscreen unavailable: staying windowed\n");
    } else if (wanted != 0) {
        if (!settings.applyResolution(settings.resolutions[static_cast<size_t>(wanted)]) &&
            !settings.applyResolution(settings.resolutions[0])) {
            settings.resolutionIndex = 0;
            std::printf("[settings] resolution unavailable: falling back to desktop\n");
        }
    }
}

static void flushUserSettings(App& app) {
    if (!app.settingsActive || !app.settingsDirty) return;
    std::string error;
    if (settings::save(app.settingsPath, app.userSettings, error)) {
        app.settingsDirty = false;
        app.settingsSaveReported = false;
        std::printf("[settings] saved %s\n", app.settingsPath.c_str());
        return;
    }
    // Keep the dirty flag — a later attempt may succeed — but report once and back off,
    // so an unwritable directory cannot turn into a per-frame retry storm. Nothing is
    // written anywhere else: there is no fallback into the working directory.
    if (!app.settingsSaveReported) {
        app.settingsSaveReported = true;
        std::printf("[settings] cannot save: %s\n", error.c_str());
    }
}

// The pad identity is device state, not UI state: refresh it from the backend, then let
// the comparison below notice it. A disconnected pad keeps the identity it had, which is
// what keeps its bindings on the same player across a replug.
static void pollUserSettings(App& app, double now) {
    if (!app.settingsActive) return;
    if (app.matchInputReady) {
        for (int player = 0; player < fnd::input::kMaxPlayers; ++player) {
            const std::string guid = app.matchInput.gamepad_guid(player);
            if (guid.empty()) continue;
            app.userSettings.padGuid[static_cast<size_t>(player)] = guid;
            app.userSettings.padName[static_cast<size_t>(player)] = app.matchInput.gamepad_name(player);
        }
    }
    settings::UserSettings current = ui::toUserSettings(ui::frontendSettings());
    current.padGuid = app.userSettings.padGuid;
    current.padName = app.userSettings.padName;
    if (current != app.userSettings) {
        app.userSettings = current;
        app.settingsDirty = true;
        app.settingsDirtyAt = now;
    }
    if (!app.settingsDirty) return;
    // Write when the user has stopped changing things: leaving the two config screens, or
    // a pause after the last change (which also covers a quit that never reaches the
    // shutdown flush). Keeps a slider drag from writing the file on every step.
    const bool inConfigScreen = app.screensMode &&
        (app.screens.current() == ui::ScreenId::Options ||
         app.screens.current() == ui::ScreenId::KeyConfig);
    if (inConfigScreen && now - app.settingsDirtyAt < 2.0) return;
    if (now < app.settingsNextSaveAt) return;
    flushUserSettings(app);
    if (app.settingsDirty) app.settingsNextSaveAt = now + 5.0;   // failed: try again later
}

// --- battle pause (issue #15) ------------------------------------------------------
// The freeze itself is recovered: the original's pause flag scene+0x4430 gates its whole
// battle update (FUN_00634f60 @0x635093-0x6350aa skips the frame counter and every
// fighter/economy/camera step) and is toggled from the per-fighter pause action while the
// live battle phase runs (@0x634fb3-0x635006, playing system SE 0x11). What the port adds
// is the readable four-row menu, its captions and the leave-battle actions — see
// battle/battle_pause.h for the full provenance and docs/PAUSE.md for the policy.

// Pause is a live-battle feature of the interactive frontend only. Every capture and
// replay path keeps its historical behaviour — --match, --versus, --hud-test,
// --screen=battle captures, --out/--headless runs and bounded --frames runs never enter
// the pause state — so their frames and traces are identical whether or not a pause key is
// bound. Same shape as #19's usesUserConfig, for the same reason.
static bool battlePauseAvailable(const App& app) {
    // Everyone else's game cannot wait online.
#ifdef DAYBREAK_ONLINE
    if (app.netSession) return false;
#endif
    return app.matchMode && app.opts.out.empty() && !app.opts.headless && app.opts.frames == 0;
}

// The controller slot that drives a frontend panel, or -1 for COM.
static int panelController(const App& app, int panel) {
    const int controller = app.frontend.slots[panel].controller;
    return (controller >= 0 && controller < 4) ? controller : -1;
}

// Standalone battles use P1; frontend battles use their human owners, or the
// local spectators when every fighter is COM. The menu uses this same set.
static int battlePauseControllers(const App& app, int out[4]) {
    if (!app.frontendMatch) {
        out[0] = 0;
        return app.matchInputReady ? 1 : 0;
    }
    int count = 0;
    for (int i = 0; i < app.battleLaunch.fighterCount && count < 4; ++i) {
        const int controller = panelController(app, app.battleLaunch.fighters[i].panel);
        if (controller >= 0) out[count++] = controller;
    }
    // Port rule (#64): with only COM fighters, any local controller may operate the
    // pause menu. Human matches retain fighter ownership so spectators cannot interrupt.
    if (count == 0 && app.battleLaunch.fighterCount > 0) {
        for (int controller = 0; controller < 4; ++controller) out[count++] = controller;
    }
    return count;
}

// Opening and operating the pause share the same ownership rule.
static bool battlePausePressed(const App& app) {
    int controllers[4] = {-1, -1, -1, -1};
    const int count = battlePauseControllers(app, controllers);
    for (int i = 0; i < count; ++i)
        if (app.tickInput[controllers[i]].just_pressed[fnd::input::Pause]) return true;
    return false;
}

// Combat SFX are the gameplay bus (channels 16..31, audio.h). While paused no new cue can
// start (the match does not step) and this stops the ones already ringing, so a pause
// cannot leave a hit cue playing over a frozen frame. BGM is deliberately left alone: the
// original's pause path plays SE 0x11 and never touches the music stream.
static void suspendCombatSfx(App& app) {
    int first = 0, last = 0;
    if (!fnd::audio::bus_range(fnd::audio::SfxBus::Sfx, first, last)) return;
    for (int channel = first; channel <= last; ++channel) app.versusAudio.stop(channel);
}

// The recovered pause cue: system SE 0x11 (FUN_0064aed0(0x11), FUN_00634f60 @0x634fe8),
// loaded from data/sysse/017 once and reused. A missing asset leaves the pause silent
// rather than failing it.
static void playPauseCue(App& app) {
    if (!app.pauseSoundTried) {
        app.pauseSoundTried = true;
        char stem[48];
        std::snprintf(stem, sizeof(stem), "data/sysse/%03d", 0x11);
        const std::string path = fnd::assets::assetSource().resolve(
            {std::string(stem) + ".cnv", std::string(stem) + ".wav"});
        app.pauseSound = loadSoundAsset(app.menuAudio, path);
    }
    if (app.pauseSound >= 0) app.menuAudio.play(app.pauseSound, fnd::audio::SfxBus::Ui);
}

static void enterBattlePause(App& app, const char* reason) {
    if (app.battlePaused) return;
    app.battlePaused = true;
    app.battle->set_paused(true);   // the authoritative gate
    app.pauseMenu.rows = app.frontendMatch ? gameplay::kPauseRowsWithSelection
                                           : gameplay::kPauseRowsStandalone;
    app.pauseMenu.reset();
    // The overlay's own batch is created with the first pause of the process. Not in
    // initScene: the frontend turns matchMode on only when the countdown ends, so a
    // `--screen=battle` run builds its scene before that block's condition is true — the
    // pause is the one point every path that can pause shares, and a run that never pauses
    // pays nothing. A failure here is silent like a caption that will not load (below):
    // the pause still works, it just has no menu on screen. A local error keeps it out of
    // App::error, which is what the run's RESULT line reports.
    if (!app.pauseUiReady) {
        std::string uiError;
        app.pauseUiReady = app.pauseUi.init(app.ctx.device, app.ctx.queue, uiError);
    }
    suspendCombatSfx(app);
    playPauseCue(app);
    std::printf("[pause] paused (%s)\n", reason);
}

static void resumeBattle(App& app) {
    if (!app.battlePaused) return;
    app.battlePaused = false;
    app.battle->set_paused(false);
    app.pauseMenu.reset();
    // Nothing is replayed: the paused ticks drained the device queues, so a button held
    // across the pause has no edge left to fire (the acceptance case) and the clock's
    // remainder is exactly where the pause stopped it.
    std::printf("[pause] resumed\n");
}

// Leaving a battle without a result: the same cleanup the round-over path performs, so a
// return to selection or a rematch cannot inherit the finished match. enterFrontendBattle
// is written to be re-entered (it clears weaponDefs/bulletParams, resets the counters and
// rebuilds the scene), which is what makes repeated cycles safe.
#ifdef DAYBREAK_ONLINE
static void reportNetSession(const net::Session& session) {
    const net::SessionStats& stats = session.stats();
    std::printf("[net] %u updates, %u rollbacks, %u desyncs, worst %.2f ms\n", stats.updates, stats.rollbacks,
                stats.desyncs, stats.worstUpdate.count() / 1000.0);
}

// Whatever the selection screen has decided so far, which every peer must agree on.
static std::uint32_t onlineSelectionHash(const ui::FrontendState& state) {
    std::uint32_t digest = 2166136261u ^ state.randomState;
    const auto mix = [&digest](int value) { digest = (digest ^ static_cast<std::uint32_t>(value)) * 16777619u; };
    for (const ui::FrontendSlot& slot : state.slots) {
        mix(slot.character);
        mix(slot.weapon);
        mix(slot.hypermode);
        mix(slot.costume);
        mix(slot.controller);
    }
    mix(state.stage);
    mix(state.variation);
    mix(state.timeLimit);
    mix(state.health);
    mix(state.gauge);
    mix(state.blueBalloon);
    mix(state.redBalloon);
    return digest;
}

// Back to the room's lobby from the selection, with a new match to prepare.
static void leaveOnlineSelection(App& app, const char* why) {
    app.netMenu.reset();
    app.netMenuHeld = {};
    if (why) app.frontend.onlineMessage = why;
    std::printf("[net] selection ended: %s\n", why ? why : "a player backed out");
    std::uint32_t token, seed;
    ui::onlineMatchNumbers(token, seed);
    app.frontend.online->lobby->next_match(token, seed);
    app.frontend.online->inMatch = false;
}

// The room outlives the match: everyone goes back to its lobby from here.
static void endOnlineMatch(App& app) {
    if (!app.frontend.online || !app.netSession) return;
    reportNetSession(*app.netSession);
    app.coreBattle.set_driver(nullptr);
    app.netSession.reset();
    std::uint32_t token, seed;
    ui::onlineMatchNumbers(token, seed);
    app.frontend.online->lobby->next_match(token, seed);
    app.frontend.online->inMatch = false;
}
#endif

static void leaveBattleTo(App& app, ui::ScreenId next) {
    app.matchMode = false;
    app.frontendBattleReady = false;
    app.versusAudio.clear_music();
    app.screens.request(next);
    app.screensMode = true;
}

// A rematch must replay the battle that was just left. The front end rolls a random stage
// when none was chosen (frontend_launch.cpp:39, `state.stage == 0`), so the resolved stage
// is pinned back into the front-end state before the battle is re-entered; the characters,
// weapons and controllers already live there and are unchanged by a battle.
static void pinFrontendStage(App& app) {
    const size_t digits = app.opts.stage.find_first_of("0123456789");
    if (digits == std::string::npos) return;
    const int resolved = std::atoi(app.opts.stage.c_str() + digits);
    if (resolved < 1 || resolved > 26) return;
    app.frontend.stage = resolved % 10;
    app.frontend.variation = resolved / 10;
}

static SDL_AppResult applyPauseChoice(App& app, gameplay::PauseChoice choice) {
    switch (choice) {
        case gameplay::PauseChoice::None:
            return SDL_APP_CONTINUE;
        case gameplay::PauseChoice::Resume:
            resumeBattle(app);
            return SDL_APP_CONTINUE;
        case gameplay::PauseChoice::Rematch:
            resumeBattle(app);
            if (!app.frontendMatch) {
                // Standalone harness: rebuild the same match in place (same opts, same
                // scene), which is the whole of a rematch there.
                if (!initMatch(app)) return SDL_APP_FAILURE;
                std::printf("[pause] rematch\n");
                return SDL_APP_CONTINUE;
            }
            pinFrontendStage(app);
            // Through the VS intro, not straight back to Battle: ScreenStack::update only
            // swaps when the target differs from the current id, so re-requesting Battle
            // while the battle screen is current is a no-op (the factory would never run
            // and the old match would keep playing). VS re-enters the battle properly,
            // countdown included.
            leaveBattleTo(app, ui::ScreenId::VsIntro);
            std::printf("[pause] rematch\n");
            return SDL_APP_CONTINUE;
        case gameplay::PauseChoice::ReturnToSelection:
            resumeBattle(app);
            leaveBattleTo(app, ui::ScreenId::Select);
            std::printf("[pause] return to selection\n");
            return SDL_APP_CONTINUE;
        case gameplay::PauseChoice::Quit:
            std::printf("[pause] quit\n");
            return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

// One paused tick: the match is not stepped at all, only the menu is read. Called from the
// tick loop in place of the battle tick, so the device queues are drained at the same
// cadence they would be during play — which is what keeps a held button from arriving as a
// stale edge on resume.
static SDL_AppResult tickBattlePause(App& app) {
    ++app.pauseScriptAdvance;   // keep the standalone script clock moving (see the member)
    bool up = false, down = false, confirm = false, cancel = false;
    int controllers[4] = {-1, -1, -1, -1};
    const int count = battlePauseControllers(app, controllers);
    for (int i = 0; i < count; ++i) {
        const fnd::input::PlayerState& in = app.tickInput[controllers[i]];
        // The pause action toggles back out, exactly like the original's key.
        if (in.just_pressed[fnd::input::Pause]) {
            resumeBattle(app);
            return SDL_APP_CONTINUE;
        }
        up = up || in.just_pressed[fnd::input::Up];
        down = down || in.just_pressed[fnd::input::Down];
        confirm = confirm || in.just_pressed[fnd::input::Jump];
        cancel = cancel || in.just_pressed[fnd::input::AttackA];
    }
    return applyPauseChoice(app, app.pauseMenu.update(up, down, confirm, cancel));
}

// A readable hint from the CURRENT bindings (P1 keyboard plus, when the pausing player has
// a pad, that pad's button names), so a rebind shows up here with no second table.
static std::string bindingHint(const App& app, fnd::input::Action action, int padPlayer) {
    const auto& settings = ui::frontendSettings();
    std::string out;
    const int key = settings.keyboard[action];
    if (key >= 0) {
        const char* name = SDL_GetScancodeName(static_cast<SDL_Scancode>(key));
        if (name && *name) out = name;
    }
    if (padPlayer >= 0 && padPlayer < 4) {
        const int button = settings.gamepad[static_cast<size_t>(padPlayer)][action];
        if (button >= 0) {
            const char* name = SDL_GetGamepadStringForButton(static_cast<SDL_GamepadButton>(button));
            if (name && *name) out += out.empty() ? name : std::string(" / ") + name;
        }
    }
    return out.empty() ? "unbound" : out;
}

// The caption cell the pause menu rasterizes at. Fixed on purpose: CaptionText::load
// rasterizes once and keeps the atlas (ui/caption.cpp), so the drawn size has to come from
// the draw scale, exactly as the HUD's own caption path does it. 32 px is the face's
// design cell — the layout's own resolution-relative size is kPauseFontFrac of the target.
static constexpr float kPauseFontCellPx = 32.f;

// The pause overlay: a system menu drawn once over the frozen frame (not per view, so a
// split-screen match gets one readable menu instead of one per cell). Text goes through the
// shared D7 caption path; a caption that cannot load leaves the pause working but silent on
// screen rather than failing the frame.
//
// It owns its batching: `app.pauseUi`, not the battle HUD's `app.uiRenderer`. A SpriteRenderer
// used to hand every pass in a frame the same vertex buffer, written at offset 0 by each
// render() call, and all of a frame's writes land before its single submission — so a
// renderer shared with the HUD gave this pass the HUD's vertices (its dim quad took the
// reticle's geometry and drew it with the 1x1 white fallback, issue #50 defect 1, and its
// first quads ghosted the HUD's art, defect 2). Issue #56 fixed that at the batch (one
// vertex region per render() call, ui/sprite.h), so the second renderer is now ownership
// rather than the only way to keep the two batches apart; see docs/PAUSE.md §"Why the
// overlay owns a renderer".
static bool drawBattlePauseOverlay(App& app, WGPUCommandEncoder encoder, WGPUTextureView view,
                                   uint32_t width, uint32_t height, WGPUTextureFormat format) {
    if (!app.battlePaused || !app.pauseUiReady || width == 0 || height == 0) return true;
    int padPlayer = 0;
    if (app.frontendMatch) {
        const int controller = panelController(app, ui::kFrontendBattleSlots[0]);
        if (controller > 0) padPlayer = controller;
    }
    std::vector<std::string> lines;
    lines.push_back("PAUSED");
    for (int row = 0; row < app.pauseMenu.rows; ++row)
        lines.push_back(std::string(row == app.pauseMenu.row ? "> " : "  ") +
                        gameplay::pauseRowLabel(row, app.pauseMenu.rows));
    // No footer. The binding-hint line used to sit here ("Up/Down: choose  Z: confirm ...")
    // and it was the WIDEST line in the block, so it — not the menu — set the panel's width,
    // and on a 4:3 target the panel ran past the frame. The rows are the menu; the keys are
    // the player's own bindings and the options screen is where they are read.
    std::string textError;
    if (!app.pauseText.load(app.pauseUi, kPauseFontCellPx, textError) ||
        !app.pauseText.prepare(app.pauseUi, lines, textError))
        return true;
    // Title and rows: the sizes are ratios of the canvas (hud/pause_layout.h — a port
    // decision, the original has no readable menu), and each line's measured width is what
    // sizes the panel.
    const auto lineScale = [](size_t i) { return i == 0 ? ui::kPauseTitleScale : 1.f; };
    std::vector<ui::PauseLine> measured;
    measured.reserve(lines.size());
    for (size_t i = 0; i < lines.size(); ++i)
        measured.push_back(ui::PauseLine{app.pauseText.width(lines[i].c_str()), lineScale(i)});
    const ui::PauseOverlayLayout layout =
        ui::computePauseOverlayLayout(width, height, kPauseFontCellPx, measured);
    if (!layout.valid) return true;
    app.pauseUi.beginFrame(width, height);
    // Dim the frozen frame so the menu is readable over any stage (the same solid fill the
    // screen stack's fade overlay uses), then the panel the block sits on (defect 4).
    app.pauseUi.pushSolid(ui::UiRect{0.f, 0.f, static_cast<float>(width),
                                     static_cast<float>(height)},
                          ui::UiColor{0.f, 0.f, 0.f, 0.55f});
    app.pauseUi.pushSolid(layout.panel, layout.panelColor);
    for (size_t i = 0; i < lines.size(); ++i) {
        const bool title = i == 0;
        // No `footer` term: there is no footer line any more, and `lines.size() - 1` is the LAST
        // ROW — so testing for one suppressed that row's highlight. The cursor does reach it
        // (PauseMenu::update wraps), so "Quit to desktop" drew in the unselected grey.
        const bool selected = !title && static_cast<int>(i) - 1 == app.pauseMenu.row;
        const ui::UiColor color = title      ? ui::UiColor{1.f, 1.f, 1.f, 1.f}
                                  : selected ? ui::UiColor{1.f, 0.8f, 0.3f, 1.f}
                                             : ui::UiColor{0.85f, 0.85f, 0.9f, 1.f};
        app.pauseText.draw(app.pauseUi, lines[i].c_str(), layout.textX,
                           layout.firstY + layout.pitch * static_cast<float>(i),
                           layout.drawScale * lineScale(i), color, 1.f);
    }
    return app.pauseUi.render(encoder, view, format, app.error);
}

// Defined beside the HUD helpers below: initMatch fills the roster while it assembles the
// match, and enterFrontendBattle fills it earlier so the VS screen can draw it.
bool buildTrianglePipeline(App& app) {
    WGPUShaderModule shader = gpu::createShaderModule(app.ctx.device, shaders::kDemoWGSL);
    if (!shader) {
        app.error = "shader module creation failed";
        return false;
    }

    WGPUVertexAttribute attrs[2] = {};
    attrs[0].format = WGPUVertexFormat_Float32x3;
    attrs[0].offset = 0;
    attrs[0].shaderLocation = 0;
    attrs[1].format = WGPUVertexFormat_Float32x3;
    attrs[1].offset = 3 * sizeof(float);
    attrs[1].shaderLocation = 1;

    WGPUVertexBufferLayout vbl = {};
    vbl.arrayStride = 6 * sizeof(float);
    vbl.stepMode = WGPUVertexStepMode_Vertex;
    vbl.attributeCount = 2;
    vbl.attributes = attrs;

    WGPUBindGroupLayoutEntry entry = {};
    entry.binding = 0;
    entry.visibility = WGPUShaderStage_Vertex;
    entry.buffer.type = WGPUBufferBindingType_Uniform;
    entry.buffer.minBindingSize = 64;

    WGPUBindGroupLayoutDescriptor bglDesc = {};
    bglDesc.entryCount = 1;
    bglDesc.entries = &entry;
    WGPUBindGroupLayout bgl = wgpuDeviceCreateBindGroupLayout(app.ctx.device, &bglDesc);

    WGPUPipelineLayoutDescriptor plDesc = {};
    plDesc.bindGroupLayoutCount = 1;
    plDesc.bindGroupLayouts = &bgl;
    WGPUPipelineLayout layout = wgpuDeviceCreatePipelineLayout(app.ctx.device, &plDesc);

    WGPUColorTargetState target = {};
    target.format = app.sc.format;
    target.writeMask = WGPUColorWriteMask_All;
    WGPUBlendState blend = {};
    blend.color.srcFactor = WGPUBlendFactor_SrcAlpha;
    blend.color.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
    blend.color.operation = WGPUBlendOperation_Add;
    blend.alpha.srcFactor = WGPUBlendFactor_One;
    blend.alpha.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
    blend.alpha.operation = WGPUBlendOperation_Add;
    target.blend = &blend;

    WGPUFragmentState fs = {};
    fs.module = shader;
    fs.entryPoint = WGPUStringView{"fs_main", WGPU_STRLEN};
    fs.targetCount = 1;
    fs.targets = &target;

    WGPURenderPipelineDescriptor rpd = {};
    rpd.layout = layout;
    rpd.vertex.module = shader;
    rpd.vertex.entryPoint = WGPUStringView{"vs_main", WGPU_STRLEN};
    rpd.vertex.bufferCount = 1;
    rpd.vertex.buffers = &vbl;
    rpd.primitive.topology = WGPUPrimitiveTopology_TriangleList;
    rpd.primitive.frontFace = WGPUFrontFace_CCW;
    rpd.primitive.cullMode = WGPUCullMode_None;
    rpd.multisample.count = 1;
    rpd.multisample.mask = 0xFFFFFFFFu;
    rpd.fragment = &fs;

    app.pipeline = wgpuDeviceCreateRenderPipeline(app.ctx.device, &rpd);

    WGPUBindGroupEntry bgEntry = {};
    bgEntry.binding = 0;
    bgEntry.buffer = app.uniformBuffer;
    bgEntry.offset = 0;
    bgEntry.size = 64;
    WGPUBindGroupDescriptor bgDesc = {};
    bgDesc.layout = bgl;
    bgDesc.entryCount = 1;
    bgDesc.entries = &bgEntry;
    app.bindGroup = wgpuDeviceCreateBindGroup(app.ctx.device, &bgDesc);

    wgpuPipelineLayoutRelease(layout);
    wgpuBindGroupLayoutRelease(bgl);
    wgpuShaderModuleRelease(shader);

    if (!app.pipeline || !app.bindGroup) {
        app.error = "pipeline creation failed";
        return false;
    }
    return true;
}

const float kVertices[] = {
    0.00f,  0.62f, 0.0f, 1.00f, 0.35f, 0.25f,
   -0.58f, -0.52f, 0.0f, 0.25f, 0.90f, 0.45f,
    0.58f, -0.52f, 0.0f, 0.30f, 0.55f, 1.00f,
};

bool initTriangle(App& app) {
    app.vertexBuffer = gpu::createBuffer(app.ctx.device, sizeof(kVertices),
                                         WGPUBufferUsage_Vertex | WGPUBufferUsage_CopyDst,
                                         kVertices);
    app.uniformBuffer = gpu::createBuffer(app.ctx.device, 64,
                                          WGPUBufferUsage_Uniform | WGPUBufferUsage_CopyDst,
                                          nullptr);
    if (!app.vertexBuffer || !app.uniformBuffer) {
        app.error = "buffer creation failed";
        return false;
    }
    return buildTrianglePipeline(app);
}

// The whole scene path: load, pose, frame, upload. Everything after this is per-frame.
// Decodes a BGM track plus its sibling .sfl loop into engine-ready state.
// Shared by versus BGM streaming; the --audio-test file path keeps its own
// inline version because its reporting differs. Loop points are file-rate
// samples, so anything but 44100 stereo is refused rather than misaligned.


// Versus one-time setup, after load/pose/bind and before framing: ranges,
// spawn bases, audio decode, initial placement for the setScene bake.



bool runAudioTest(App& app) {
    // A 440 Hz sine, one second, mix-ready stereo: synthesized so the check needs
    // no copyrighted bytes and stays deterministic across targets.
    fnd::audio::Sdl3Engine engine(nullptr);   // null gate: native always ready
    fnd::audio::Spec spec;
    if (!engine.open(spec)) {
        app.error = "audio device open failed";
        return false;
    }
    std::vector<int16_t> tone(44100 * 2);
    for (size_t i = 0; i < 44100; ++i) {
        const float v = std::sin(2.f * 3.14159265f * 440.f * (float)i / 44100.f);
        const int16_t q = (int16_t)(v * 32767.f);
        tone[i * 2] = q;
        tone[i * 2 + 1] = q;
    }
    const size_t pushed = engine.push_music_s16(tone.data(), tone.size() / 2);
    fnd::audio::SfxHandle h = engine.load_pcm_s16(tone.data(), tone.size() / 2);
    const int ch = engine.play(h, fnd::audio::SfxBus::Sfx);
    fnd::audio::Volumes vols;
    vols.music = 50;
    vols.sfx = 25;
    engine.set_volumes(vols);
    std::printf("audio-test: device open, music pushed %zu/44100 frames, sfx handle %d on channel %d\n",
                pushed, (int)h, ch);
    std::printf("audio-test: music queued %zu frames, music gain %.2f, sfx gain %.2f\n",
                engine.music_queued_frames(), engine.music_gain(),
                engine.bus_gain_applied(fnd::audio::SfxBus::Sfx));
    if (!app.opts.audioFile.empty()) {
        // A real shipped file through the same bank: format-detected, decoded,
        // and fired once. Local data only, never committed.
        std::ifstream f(app.opts.audioFile, std::ios::binary);
        if (!f) {
            app.error = "cannot open " + app.opts.audioFile;
            return false;
        }
        const std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(f)),
                                         std::istreambuf_iterator<char>());
        fnd::audio::SfxHandle fh = fnd::audio::kInvalidSfx;
        const char* kind = "unknown";
        switch (fnd::audio::detect_format(bytes.data(), bytes.size())) {
            case fnd::audio::BlobFormat::Ogg:
                fh = engine.load_ogg(bytes.data(), bytes.size());
                kind = "ogg";
                break;
            case fnd::audio::BlobFormat::Wav:
                fh = engine.load_wav(bytes.data(), bytes.size());
                kind = "wav";
                break;
            case fnd::audio::BlobFormat::CnvPcm:
                fh = engine.load_cnv(bytes.data(), bytes.size());
                kind = "cnv";
                break;
            default: break;
        }
        if (fh < 0) {
            app.error = "decode failed for " + app.opts.audioFile;
            return false;
        }
        const int fch = engine.play(fh, fnd::audio::SfxBus::Sfx);
        std::printf("audio-test: file %s (%s, %zu bytes) decoded, handle %d on channel %d\n",
                    app.opts.audioFile.c_str(), kind, bytes.size(), (int)fh, fch);
        if (fch < 0) {
            app.error = "file playback failed";
            return false;
        }
        // A sibling .sfl file carries the BGM loop region. When one parses,
        // stream the track through it twice in engine-sized chunks: this is the
        // production streaming path (decode once, push looped chunks), verified
        // by exact frame accounting rather than by listening. No sheet — or an
        // unusable one — is still a playable track, not a failure: it streams to
        // EOF once, which is what FUN_00668820's zero loop region means.
        if (std::string(kind) == "ogg") {
            fnd::audio::DecodedOgg decoded;
            if (fnd::audio::decode_ogg_s16(bytes.data(), bytes.size(), decoded) && decoded.ok &&
                decoded.srcRate == 44100 && decoded.srcChannels == 2) {
                // This mode reads through the filesystem rather than the asset
                // source (it takes a path on the command line), so the sheet
                // lookup follows the same path.
                const fnd::audio::LoopSheetResult sheet = fnd::audio::resolve_loop_sheet(
                    app.opts.audioFile, 44100,
                    [](const std::string& path, std::vector<uint8_t>& out) {
                        std::ifstream sf(path, std::ios::binary);
                        if (!sf) return false;
                        out.assign(std::istreambuf_iterator<char>(sf),
                                   std::istreambuf_iterator<char>());
                        return true;
                    });
                fnd::audio::LoopPlayer player;
                player.set_source(decoded.stereo44100.data(), decoded.stereo44100.size() / 2);
                player.set_loop(sheet.loop.startSample, sheet.loop.endSample);
                size_t streamed = 0;
                if (sheet.status == fnd::audio::LoopSheet::Parsed) {
                    const uint32_t start = sheet.loop.startSample;
                    const uint32_t end = sheet.loop.endSample;
                    // Two full loops, bounded: a runaway wrap would show
                    // up here as iterations past the budget, not a hang.
                    const size_t budget = (2 * (size_t)(end - start) + end) / 4096 + 8;
                    for (size_t i = 0; i < budget && player.loops_completed() < 2; ++i)
                        streamed += player.push_next(engine, 4096);
                    // Two wraps land at end + (end - start): the opening
                    // [0, end) pass plus one full [start, end) loop.
                    const size_t expect = 2 * (size_t)end - start;
                    // The call containing the second wrap keeps pushing
                    // into the third pass up to its chunk budget, so the
                    // total overshoots by less than one chunk: wraps are
                    // the exact signal, totals are bounded each side.
                    std::printf("audio-test: loop %u..%u streamed %zu frames, %llu wraps\n",
                                start, end, streamed,
                                (unsigned long long)player.loops_completed());
                    if (player.loops_completed() != 2 || streamed < expect ||
                        streamed >= expect + 4096 || player.position() < start ||
                        player.position() >= end) {
                        app.error = "loop streaming mismatch";
                        return false;
                    }
                } else {
                    // One pass to EOF with no wrap; the push total is the
                    // positive proof the whole track reached the engine.
                    const size_t frames = decoded.stereo44100.size() / 2;
                    const size_t budget = frames / 4096 + 16;
                    for (size_t i = 0; i < budget && player.position() < frames; ++i)
                        streamed += player.push_next(engine, 4096);
                    if (sheet.status == fnd::audio::LoopSheet::Unparsable)
                        std::printf("audio-test: %s [port rule: reported, FUN_00668820 is "
                                    "silent]\n", sheet.note.c_str());
                    else
                        std::printf("audio-test: no loop sheet for %s, playing to EOF\n",
                                    app.opts.audioFile.c_str());
                    std::printf("audio-test: streamed %zu/%zu frames to EOF, %llu wraps\n",
                                streamed, frames,
                                (unsigned long long)player.loops_completed());
                    if (streamed != frames || player.loops_completed() != 0 ||
                        player.position() != frames) {
                        app.error = "no-loop streaming mismatch";
                        return false;
                    }
                }
            }
        }
    }
    engine.close();
    return pushed == 44100 && h >= 0 && ch >= 0;
}

bool runInputTest(App& app) {
    fnd::input::Backend backend;
    if (!backend.init()) {
        app.error = "input backend init failed";
        return false;
    }
    // Canned tap on P1 melee (X): down at frame 2, up at frame 4. No hardware
    // input exists headless, so the event-held set carries the whole test.
    bool ok = true;
    for (uint64_t frame = 1; frame <= 6; ++frame) {
        if (frame == 2) backend.note_key(fnd::input::sdl3::kScMelee, true);
        if (frame == 4) backend.note_key(fnd::input::sdl3::kScMelee, false);
        backend.poll();
        const fnd::input::PlayerState& p0 = backend.player(0);
        const bool held = p0.down[fnd::input::AttackA];
        const bool jp = p0.just_pressed[fnd::input::AttackA];
        const bool jr = p0.just_released[fnd::input::AttackA];
        const int timer = p0.press_timer[fnd::input::AttackA];
        std::printf("input-test: frame %llu held=%d just_pressed=%d just_released=%d timer=%d\n",
                    (unsigned long long)frame, (int)held, (int)jp, (int)jr, timer);
        if (jp != (frame == 2) || jr != (frame == 4) || held != (frame >= 2 && frame < 4))
            ok = false;
    }
    backend.shutdown();
    if (!ok) app.error = "input edge sequence mismatch";
    return ok;
}

static void playFrontendMusic(App& app, ui::ScreenId id) {
    // Decode independently of the device so muted/device-less runs retain VS
    // pacing, and a direct VS start has its duration before the factory runs.
    const int localSide = app.frontend.slots[0].controller < 4 ? 0 : 1;
    // Scene 0x00's own track (FUN_00404ff0:0x405096, "data/bgm/titlesemi.ogg" at 0x6a14c0)
    // — the movie's audio is a separate stream and plays over it.
    const char* path = id == ui::ScreenId::Opening ? "data/bgm/titlesemi.ogg" :
        id == ui::ScreenId::Title ? "data/bgm/title.ogg" :
        id == ui::ScreenId::Select || id == ui::ScreenId::StoryTeam ? "data/bgm/select01.ogg" :
        id == ui::ScreenId::VsIntro ? "data/bgm/vs.ogg" :
        id == ui::ScreenId::Result && app.frontend.resultWinner >= 0 ?
            (app.frontend.resultWinner == localSide ? "data/bgm/win.ogg" : "data/bgm/lose.ogg") : nullptr;
    // Already playing exactly this track: leave it running. The host starts a scene's music
    // when its fade BEGINS (SDL_AppIterate), so by the time the factory constructs the scene
    // 25 frames later the track is up and restarting it here would cut the first bars —
    // which is the hole this whole path exists to close.
    playMenuTrack(app, path);
}

void playMenuTrack(App& app, const char* path) {
    if (path && app.menuBgmPath == path) return;
    app.menuAudio.clear_music();
    app.menuLoop = fnd::audio::LoopPlayer{};
    app.menuBgmPath.clear();
    if (!path) return;
    std::string failure;
    if (!loadBgmTrack(path, app.menuAudio, app.menuBgm, app.menuLoop, failure)) {
        std::fprintf(stderr, "[menu] %s\n", failure.c_str());
        return;
    }
    app.menuBgmPath = path;
}

// Issue #4 (web delivery): ask the same-origin service for the assets this match needs.
// A native run has no delivery client running, so this is a no-op there and the native
// path is untouched. The set is the loader's own directory scopes (stage directory,
// fighter directories with their costume sibling, the weapons' bullet directories); the
// server expands each prefix from the catalog, so the client never guesses a file list.
static void requestWebMatchGroup(const std::string& stageDir,
                                 const std::vector<std::string>& slots,
                                 const std::vector<int>& weaponIds) {
    plat::AssetClient& client = plat::assetClient();
    if (!client.running() || stageDir.empty() || slots.empty()) return;
    std::string stage = stageDir;
    const std::size_t slash = stage.find_last_of('/');
    if (slash != std::string::npos) stage = stage.substr(slash + 1);   // "stage21"
    std::vector<std::string> weapons;
    for (int id : weaponIds) {
        char buf[16];
        std::snprintf(buf, sizeof(buf), "%03d", id);
        weapons.push_back(buf);
    }
    if (!client.requestMatch(stage, slots, weapons)) return;
    std::printf("[delivery] match group requested: %s, %zu fighter(s), %zu weapon(s)\n",
                stage.c_str(), slots.size(), weapons.size());
}

// Issue #4 (web delivery): the same request for a standalone recipe. `--stage=`,
// `--character=`/`--enemy=` and `--match` go straight to the battle with no VS
// transition to hook, so the dependency set comes from the arguments instead — the
// loaders' own directory scopes again, with each fighter's weapon bound (a battle is
// always a character+weapon combo, issue #26). False means "nothing to wait for".
static bool requestWebStandaloneGroup(App& app) {
    plat::AssetClient& client = plat::assetClient();
    if (!client.running() || app.opts.stage.empty()) return false;
    std::vector<std::string> slots;
    std::vector<int> weaponIds;
    for (int i = 0; i < 4; ++i) {
        std::string spec, explicitSpec;
        if (app.opts.battleFighterCount > 0 && i < 4) {
            spec = app.opts.battleCharacters[i];
            explicitSpec = app.opts.battleWeapons[i];
        } else if (i == 0) {
            spec = app.opts.character;
            explicitSpec = app.opts.weapon;
        } else if (i == 1) {
            spec = app.opts.enemy;
            explicitSpec = app.opts.enemyWeapon;
        } else {
            continue;
        }
        if (spec.empty()) continue;
        // splitSuffix's path half is unused here: charDirForSpec already drops the
        // `:N` suffix and the directory part, which is exactly what the manifest needs.
        std::string ignoredPath;
        int costume = 0;
        splitSuffix(spec, ignoredPath, costume);
        const std::string dir = charDirForSpec(spec);
        // A costume directory spelled out in the spec ("data/rena_B:0") is the same
        // request as the index ("data/rena:1"); normalise so the server's prefix rule
        // sees one shape.
        std::string base = dir;
        if (dir.size() > 2 && dir[dir.size() - 2] == '_' &&
            dir.back() >= 'B' && dir.back() <= 'F') {
            if (costume == 0) costume = dir.back() - 'A';
            base = dir.substr(0, dir.size() - 2);
        }
        slots.push_back(base + ":" + std::to_string(costume));
        std::string mesh;
        int itemId = 0;
        if (resolveFighterWeapon(dir, explicitSpec, mesh, itemId)) {
            weaponIds.push_back(itemId);
        } else {
            const int character = gameplay::characterIndexForDir(dir);
            if (character >= 0) weaponIds.push_back(gameplay::kWeaponIds[character][0]);
        }
    }
    if (slots.empty()) return false;
    requestWebMatchGroup(app.opts.stage, slots, weaponIds);
    return client.matchRequested();
}

static bool enterFrontendBattle(App& app) {
    // Direct --screen=vsintro/battle gets a usable two-fighter default.
    for (int i = 0; i < 2; ++i) if (app.frontend.slots[ui::kFrontendBattleSlots[i]].character < 0) {
        app.frontend.slots[ui::kFrontendBattleSlots[i]].character = i;
        app.frontend.slots[ui::kFrontendBattleSlots[i]].controller = i == 0 ? 0 : 4;
    }
    // --local-players=N (verification): open N local human views by assigning controllers
    // 0..N-1 in panel order. One or two humans fight the 1v1 panel pair (0 blue, 2 red);
    // three or four use all four panels as a 2v2, where the human-less panel stays COM and
    // must not allocate a view (issue #12). This is the same controller-slot order
    // FUN_0040d130 counts humans in and FUN_006396f0 keys views by.
    if (app.opts.localPlayers > 0) {
        static constexpr int kDuelPanels[2] = {0, 2};
        static constexpr int kTeamPanels[4] = {0, 1, 2, 3};
        const int humans = app.opts.localPlayers;
        const int panelCount = humans <= 2 ? 2 : 4;
        const int* panels = humans <= 2 ? kDuelPanels : kTeamPanels;
        // Roster picks that actually gear up: a character whose slot-0 item does not join
        // fails the launch loudly (rule 7), and an install gap in one character's item data
        // must not turn a --local-players run into a false negative about split-screen.
        int chosen[4] = {-1, -1, -1, -1};
        for (int i = 0; i < panelCount; ++i) {
            for (int candidate = 0; candidate < gameplay::kCharacterCount && chosen[i] < 0;
                 ++candidate) {
                bool used = false;
                for (int j = 0; j < i; ++j) used = used || chosen[j] == candidate;
                if (used) continue;
                std::string mesh;
                int itemId = 0;
                if (resolveFighterWeapon(gameplay::kCharacterDirs[candidate], "", mesh, itemId) &&
                    !mesh.empty())
                    chosen[i] = candidate;
            }
            if (chosen[i] < 0) chosen[i] = i;   // nothing usable: let the loud error fire
        }
        for (int i = 0; i < panelCount; ++i) {
            ui::FrontendSlot& slot = app.frontend.slots[panels[i]];
            if (slot.character < 0) slot.character = chosen[i];
            slot.controller = i < humans ? i : 4;
        }
        // Keep the match to the panels this flag selected: a panel left over from an
        // earlier menu run would silently add a fighter (and a COM slot) to the roster.
        for (int i = 0; i < 4; ++i) {
            bool selected = false;
            for (int j = 0; j < panelCount; ++j) selected = selected || panels[j] == i;
            if (!selected) app.frontend.slots[i] = ui::FrontendSlot{};
        }
    }
    // The core always plays four actors. FUN_0040d130 gives each unselected slot a random
    // COM (character, weapon, mode, costume), as the bundle's prepare_local_roster does; the
    // draws here are the port's own, not the battle RNG's.
    std::mt19937 fill(static_cast<uint32_t>(app.logicTicks) * 2654435761u + 1u);
    for (int panel = 0; panel < 4; ++panel) {
        ui::FrontendSlot& slot = app.frontend.slots[panel];
        if (slot.character >= 0) continue;
        slot = ui::FrontendSlot{};
        slot.character = static_cast<int>(fill() % gameplay::kCharacterCount);
        slot.weapon = static_cast<int>(fill() % gameplay::weaponCountForCharacter(slot.character));
        slot.hypermode = static_cast<int>(fill() % 3);
        slot.controller = 4;
    }
    ui::FrontendLaunch launch;
    // A random stage must land on the same one for every peer.
    uint32_t launchSeed = (uint32_t)app.logicTicks;
#ifdef DAYBREAK_ONLINE
    if (app.frontend.online) launchSeed = app.frontend.online->matchPlan.seed;
#endif
    if (!ui::frontendLaunch(app.frontend, launch, app.error, launchSeed)) return false;
    app.battleLaunch = launch;
    // Issue #4: the match readiness barrier. This is the first moment the exact dependency
    // set is known — a random stage is rolled inside frontendLaunch — so the request goes
    // out here and the battle does not start until it has resolved. Resolved means ready or
    // failed, never "partially loaded": a failed asset is reported and the run stops rather
    // than entering a battle whose stage or fighter is half present.
    {
        std::vector<std::string> slots;
        std::vector<int> weaponIds;
        for (int i = 0; i < launch.fighterCount; ++i) {
            const int panel = launch.fighters[i].panel;
            const int costume =
                (panel >= 0 && panel < 4) ? app.frontend.slots[panel].costume : 0;
            slots.push_back(launch.fighters[i].character + ":" + std::to_string(costume));
            weaponIds.push_back(launch.fighters[i].weaponId);
        }
        requestWebMatchGroup(launch.stage, slots, weaponIds);
        plat::AssetClient& client = plat::assetClient();
        if (client.running() && client.matchRequested()) {
            const bool ready = client.waitForMatch();
            std::printf("[delivery] match group %s: %s\n", ready ? "ready" : "INCOMPLETE",
                        client.matchProgress().line("match").c_str());
            if (!ready) {
                app.error = "match assets unavailable: " + client.error();
                return false;
            }
        }
    }
    // The penalty flag is per PLAYER: a panel that is COM has no player, so its flag is cleared
    // (FUN_0040d130:99-101 clears DAT_006cfdf1 for a panel whose controller byte says COM).
    for (int panel = 0; panel < 4; ++panel)
        if (app.frontend.slots[panel].controller >= 4) app.frontend.penaltyDecided[panel] = false;
    // The roster the VS screen, the battle HUD and the results all read (issue #13). Built
    // here because VS runs before the match exists; initMatch rebuilds it for the standalone
    // path and to link each entry to its MatchConfig index.
    buildMatchRoster(app);
    // Parse every selected weapon's combat definition now, so the battle has real
    // per-weapon tuning by the time initMatch builds MatchConfig (issue #9).
    app.weaponDefs.clear();
    app.weaponDefs.resize(static_cast<size_t>(launch.fighterCount));
    app.bulletParams.clear();
    app.bulletParams.resize(static_cast<size_t>(launch.fighterCount));
    for (int i = 0; i < launch.fighterCount; ++i)
        if (!loadWeaponDefinition(app, i, launch.fighters[i].weaponId, app.error))
            return false;
    // Load the recovered per-weapon projectile parameters. Damage, hit radius and hitstun
    // are used here; blob fields +0x64/+0x68 are retained as decoded values, but their
    // hit-resolution use does not establish a charge-tier shot selector. A level with no
    // matching bullet file stays empty, the shared provisional table for that port tier.
    for (int i = 0; i < launch.fighterCount; ++i)
        for (int row = 0; row < app.weaponDefs[static_cast<size_t>(i)]->bulletCount; ++row)
            loadBulletParameter(row, *app.weaponDefs[static_cast<size_t>(i)],
                                app.bulletParams[static_cast<size_t>(i)]
                                          [static_cast<size_t>(row)]);
    app.frontendMatch = true;
    app.frontendBattleReady = false;
    app.battlePaused = false;   // a fresh battle never starts paused (issue #15)
    app.battle->set_paused(false);
    app.pauseMenu.reset();
    app.frontend.resultStats = {};
    app.opts.stage = launch.stage;
    app.opts.character = launch.character;
    app.opts.enemy = launch.enemy;
    app.opts.weapon = launch.weapon;
    app.opts.enemyWeapon = launch.enemyWeapon;
    app.opts.battleFighterCount = launch.fighterCount;
    for (int i = 0; i < launch.fighterCount; ++i) {
        app.opts.battleCharacters[i] = launch.fighters[i].character;
        app.opts.battleWeapons[i] = launch.fighters[i].weapon;
    }
    app.opts.match = true;
    app.opts.camera = "arena";
    app.matchFrame = app.matchRoundOverFrame = 0;
    app.liveFx.clear();
    app.fxCatalog.clear();
    for (int& slot : app.fxAttach) slot = -1;
    for (float& sec : app.fxAttachSeconds) sec = 0.f;
    app.fxNextInstance = 1;
    app.fxTally = game::FxCardTally{};
    app.fxBadEffect = app.fxShotCards = 0;
    app.matchFx.drain();
    if (!initScene(app)) return false;
    app.versusAudio.set_volumes(ui::frontendSettings().volumes);
    // Live combat audio (issue #16): the sink adapts this App's battle engine, the dispatcher
    // owns the recovered event -> voice/SE policy. Built here, after the match exists, so the
    // per-fighter voice directories come from the actual launch roster.
    if (!app.combatSink) app.combatSink = std::make_unique<App::CombatSink>(app);
    if (!app.combatAudio) app.combatAudio = std::make_unique<fnd::audio::CombatAudio>(*app.combatSink);
    setupCombatVoices(app);
    app.matchMode = false;
    // The round's own settings are part of the evidence line: a release run has to be able to
    // say which match it played (a rematch keeps them; a fresh stage-page walk can change them).
    std::printf("[menu] battle: %d fighters on %s (time %ds, health %d%%, gauge %d%%, "
                "balloon %d%%/%d%%)\n",
                launch.fighterCount, launch.stage.c_str(), app.frontend.timeLimit,
                app.frontend.health, app.frontend.gauge, app.frontend.blueBalloon,
                app.frontend.redBalloon);
    // The spawn each fighter starts from: MatchConfig keys it by the fighter's PANEL
    // (FUN_00423420 indexes the stage's env points by the selected panel), so a 2v2 starts
    // from four different points. Printed because how far apart teammates stand is the whole
    // question behind the four-fighter spawn-crowding note in ROADMAP-PENDING.md.
    for (int i = 0; i < launch.fighterCount; ++i) {
        const glm::vec3& spawn = app.scene.env.points[launch.fighters[i].panel];
        std::printf("[menu]   fighter %d panel %d spawn=(%.0f,%.0f,%.0f)\n", i,
                    launch.fighters[i].panel, spawn.x, spawn.y, spawn.z);
    }
    return true;
}

// --screen: the front end's entry point. The stack is built with the app's own
// makeScreen factory, so an id the port has not implemented is the factory's `default`
// — no scene, no fake transition (frontend/screen.h) — and the input backend is the same one
// --match uses, so a script drives the menu through the vocabulary the DX9 suite speaks.
bool initScreens(App& app) {
    ui::ScreenId id = ui::ScreenId::Quit;
    if (!app.opts.story.empty()) app.frontend.storyScript = "data/scenario/" + app.opts.story + ".txt";
    // No --screen and a plain launch means the original's boot scene, 0x00 (resolveBootOpening
    // decided that); anything else here has to name an id the parser knows.
#ifdef DAYBREAK_ONLINE
    if (!app.opts.netHost.empty() || !app.opts.netJoin.empty()) {
        const bool opened = app.opts.netHost.empty() ? ui::beginOnlineJoin(app.frontend, app.opts.netJoin, app.error)
                                                     : ui::beginOnlineHost(app.frontend, std::atoi(app.opts.netHost.c_str()), app.error);
        if (!opened) return false;
    }
#endif
    if (app.opts.screen.empty()) {
        id = ui::ScreenId::Opening;
    } else if (!ui::parseScreenId(app.opts.screen.c_str(), id)) {
        app.error = "unknown --screen=" + app.opts.screen;
        return false;
    }
    // Front-end install: --install= wins, then $DAYBREAK_INSTALL — the two spellings that
    // make the binary usable on its own — then the folder a previous run remembered
    // (settings.conf's [game] install_dir, issue #36), and last the historical filesystem
    // fallback, because running from the install directory (or an extracted tree) must keep
    // working. The packaged launcher (package/daybreak) owns the wider SEARCH (its own
    // location, the working directory, conventional homes) and hands its choice in as
    // --install=, which is also what makes the binary remember it — so where a folder is
    // looked for stays defined once, in package/README-LINUX.md.
    std::string install = app.opts.install;
    const char* installSource = "--install=";
    if (install.empty()) {
        if (const char* env = std::getenv("DAYBREAK_INSTALL"); env && *env) {
            install = env;
            installSource = "DAYBREAK_INSTALL";
        }
    }
#if defined(_WIN32)
    const char* applicationDir = SDL_GetBasePath();
    if (!applicationDir) {
        app.error = "Cannot locate the application folder. Extract the release ZIP again.";
        return false;
    }
    // ZIP releases are copied into the original install. The executable's own
    // directory is stable even when a shortcut uses an unrelated working folder.
    if (install.empty()) {
        install = applicationDir;
        installSource = "executable folder";
    }
    std::error_code fileError;
    for (const char* font : {"gyrotrope-black.otf", "NotoSansCJKjp-Regular.otf"}) {
        const std::string path = std::string(applicationDir) + "assets/fonts/" + font;
        if (!std::filesystem::is_regular_file(std::filesystem::u8path(path), fileError)) {
            app.error = "Required font missing: " + path +
                        ". Extract all files from the release ZIP beside DaybreakRemake.exe.";
            return false;
        }
    }
    for (const char* bundle : {"daybreak00.dat", "daybreak02.dat", "daybreak04.dat",
                               "daybreak05.dat", "daybreak06.dat", "daybreak07.dat"}) {
        const std::string path = install + "/" + bundle;
        if (!std::filesystem::is_regular_file(std::filesystem::u8path(path), fileError)) {
            app.error = "Required game file missing: " + path +
                        ". Copy the complete release into your Higurashi Daybreak game folder, "
                        "beside DaybreakDX.exe and the original daybreakXX.dat files.";
            return false;
        }
    }
#endif
#if !defined(_WIN32)
    // Opened directly from a file manager, past the launcher. The package sits in the game folder,
    // or in a subfolder an archive tool made for it.
    if (install.empty() && app.userSettings.installDir.empty()) {
        if (const char* base = SDL_GetBasePath()) {
            std::error_code fileError;
            for (const std::filesystem::path& folder : {std::filesystem::u8path(base), std::filesystem::u8path(base).parent_path().parent_path()}) {
                if (std::filesystem::is_regular_file(folder / "daybreak00.dat", fileError)) {
                    install = folder.u8string();
                    installSource = "beside the package";
                    break;
                }
            }
        }
    }
#endif
    if (!install.empty()) {
        // An explicit folder that is unusable is a mistake worth failing on: silently
        // falling through to the filesystem would report a missing asset several screens
        // later instead of naming the wrong path.
        if (!openInstallOrReport(install, installSource, app.error)) return false;
        std::printf("[install] game folder: %s (from %s)\n", install.c_str(), installSource);
        rememberInstallDir(app, install);
    } else if (!app.userSettings.installDir.empty()) {
        // The remembered folder is a hint for this run, not an instruction the user gave
        // for it: a moved or deleted install must not brick the launch the way a wrong
        // --install= does, so say what happened and fall through to the current directory.
        const std::string& remembered = app.userSettings.installDir;
        if (fnd::assets::assetSource().openInstall(remembered)) {
            std::printf("[install] game folder: %s (from the remembered folder)\n",
                        remembered.c_str());
        } else {
            std::printf("[install] ignoring the remembered folder %s: it is gone or holds no "
                        "daybreakXX.dat\n", remembered.c_str());
        }
    }
    if (!fnd::assets::assetSource().bundlesOpen()) {
        if (!fnd::assets::assetSource().exists("data/title/back00.cnv")) {
            // No folder was opened and the working directory is not one either (neither a
            // bundle install nor an extracted tree): the title art is the first read of a
            // front-end run, so fail here naming the folder to point at instead of leaving
            // a per-asset message from inside the title screen.
            app.error = "no Higurashi Daybreak data found: no --install=, no DAYBREAK_INSTALL, "
                        "no remembered folder and no data/title/back00.cnv in the current "
                        "directory. Point the port at your game folder, e.g. "
                        "--install=\"/path/to/Higurashi-Daybreak\"";
            return false;
        }
        std::printf("[install] no usable folder was named or remembered: reading data/ from "
                    "the current directory\n");
    }
    // No scene is ever submitted on this path, but the capture readback lives in
    // SceneRenderer (device/queue/instance plus the mapped-buffer copy), so a --out menu
    // frame needs it initialized even though render() is never called.
    if (!app.rendererReady && !app.renderer.init(app.ctx, app.error)) return false;
    app.rendererReady = true;
    if (!app.uiReady && !app.uiRenderer.init(app.ctx.device, app.ctx.queue, app.error)) return false;
    app.uiReady = true;
    // The input backend has to exist before the first screen: scene 0x00 reads its raw key
    // state for the recovered skip, and ui::makeScreen builds it through the host seams.
    if (!app.matchInput.init()) {
        app.error = "--screen needs the input backend";
        return false;
    }
    app.matchInputReady = true;
    if (!app.opts.script.empty() && !app.matchInput.load_script(app.opts.script.c_str())) {
        app.error = "cannot read input script " + app.opts.script;
        return false;
    }
    // Scene 0x00's host seams: its audio engine, the backend its skip keys are read from,
    // and which file it plays (--movie, default the original's op.mpg).
    ui::setOpeningHost(&app.movieAudio, &app.matchInput,
                       app.opts.movie.empty() ? fnd::movie::kOpeningMovie : app.opts.movie);
    auto factory = [&app](ui::ScreenId sid) -> std::unique_ptr<ui::Screen> {
        // Scene 0x00 starts its own BGM from inside the scene, on the tick the movie starts
        // (FUN_00404ff0:0x405096), so the factory must not pre-empt it here.
        if (sid != ui::ScreenId::Opening) playFrontendMusic(app, sid);
        // Issue #4: the VS presentation is where the selection is final, so the match
        // group starts transferring as the animation begins instead of after it. A stage
        // still set to "random" (state.stage == 0) is not requested here — the roll happens
        // in frontendLaunch, and the barrier below requests the exact set then. Requesting
        // twice is safe: the second set is served from the per-asset cache for anything the
        // first one already materialised.
        if (sid == ui::ScreenId::VsIntro && plat::assetClient().running() &&
            app.frontend.stage != 0) {
            std::vector<std::string> slots;
            std::vector<int> weaponIds;
            for (int panel = 0; panel < 4; ++panel) {
                const ui::FrontendSlot& slot = app.frontend.slots[panel];
                const char* dir = ui::frontendCharacterDirectory(slot.character);
                if (!dir) continue;
                slots.push_back(std::string(dir) + ":" + std::to_string(slot.costume));
                if (slot.weapon >= 0 && slot.weapon < gameplay::weaponCountForCharacter(slot.character))
                    weaponIds.push_back(gameplay::kWeaponIds[slot.character][slot.weapon]);
            }
            char stage[24];
            std::snprintf(stage, sizeof(stage), "stage%02d",
                          app.frontend.stage + app.frontend.variation * 10);
            requestWebMatchGroup(stage, slots, weaponIds);
        }
        if (sid == ui::ScreenId::Battle) {
            // The VS intro has ended and enterFrontendBattle built the match. Nothing holds the
            // round back: this screen only hands over.
            if (!enterFrontendBattle(app)) return nullptr;
            for (int i = 0; i < app.battle->fighter_count(); ++i)
                app.previousFighter[i] = app.battle->fighter(i).pose();
            app.frontendBattleReady = true;
            return std::make_unique<BattleEntryScreen>();
        }
        // FUN_00411ae0 supplies the slide/scale timing, but not a sting-completion
        // gate. PORT PACING: retain the finished VS logo until its decoded track
        // ends instead of cutting vs.ogg when the battle factory clears the bus.
        const int vsTicks = app.menuBgmPath == "data/bgm/vs.ogg"
            ? static_cast<int>(std::ceil((app.menuBgm.stereo44100.size() / 2) *
                (app.opts.out.empty() ? gameplay::FixedStep::tickRate
                                      : gameplay::FixedStep::scriptedCaptureRate) / 44100.0))
            : 0;
        auto screen = sid == ui::ScreenId::VsIntro
            ? ui::makeVsScreen(app.uiRenderer, app.frontend, app.error, vsTicks)
            : ui::makeScreen(sid, app.uiRenderer, app.frontend, app.error);
        if (screen) std::printf("[menu] scene: %s (tick %llu)\n", screen->name(), (unsigned long long)app.logicTicks);
        return screen;
    };
    // --language wins for one run and is an error if it cannot load; a stale saved one only warns.
    if (!app.opts.language.empty()) {
        if (!ui::setSheetLanguage(app.opts.language, app.error)) return false;
    } else if (!app.userSettings.language.empty()) {
        std::string failure;
        if (!ui::setSheetLanguage(app.userSettings.language, failure)) {
            std::fprintf(stderr, "[settings] %s; using Japanese\n", failure.c_str());
            ui::frontendSettings().language.clear();
        }
    }
    if (app.opts.storyTeam >= 0 && !ui::beginStoryTeam(app.frontend, app.opts.storyTeam, app.error))
        return false;
    if (!app.opts.storyFight.empty()) {
        int fight = 0, part = 0;
        if (std::sscanf(app.opts.storyFight.c_str(), "%d:%d", &fight, &part) != 2 || fight < 0 ||
            fight >= ui::kStoryFights || part < 0 || part > 1 || !app.frontend.story.active) {
            app.error = "--story-fight needs --story-team and F:P, with F 0..5 and P 0..1";
            return false;
        }
        app.frontend.story.fight = fight;
        app.frontend.story.part = part;
    }
    if (!app.screens.begin(id, factory, app.error)) return false;
    auto& settings = ui::frontendSettings();
    settings.applyVolumes = [&app](const fnd::audio::Volumes& v) {
        app.menuAudio.set_volumes(v);
        app.versusAudio.set_volumes(v);
        // A live volume change while a movie plays has to reach the movie's own stream too.
        app.movieAudio.set_volumes(v);
    };
    settings.resolutionAvailable = false;
    settings.resolutions = {{0, 0}};
    settings.resolutionIndex = 0;
#if !defined(__EMSCRIPTEN__)
    if (app.window) {
        const SDL_DisplayID display = SDL_GetDisplayForWindow(app.window);
        if (const SDL_DisplayMode* mode = SDL_GetDesktopDisplayMode(display))
            settings.displayResolution = {mode->w, mode->h};
        int width = 0, height = 0;
        SDL_GetWindowSizeInPixels(app.window, &width, &height);
        settings.currentResolution = {width, height};
        constexpr ui::DisplayResolution common[] = {
            {800,600},{960,540},{1024,768},{1280,720},{1280,960},{1600,900},
            {1920,1080},{1920,1200},{2560,1080},{2560,1440},{3440,1440},{3840,2160}
        };
        auto addResolution = [&settings](ui::DisplayResolution size) {
            if (size.width > 0 && size.height > 0 &&
                std::find(settings.resolutions.begin(), settings.resolutions.end(), size) == settings.resolutions.end())
                settings.resolutions.push_back(size);
        };
        for (const auto size : common) addResolution(size);
        addResolution(settings.currentResolution);
        int count = 0;
        SDL_DisplayMode** modes = SDL_GetFullscreenDisplayModes(display, &count);
        if (modes) {
            for (int i = 0; i < count; ++i) addResolution({modes[i]->w, modes[i]->h});
            SDL_free(modes);
        }
        std::sort(settings.resolutions.begin() + 1, settings.resolutions.end(),
            [](ui::DisplayResolution a, ui::DisplayResolution b) {
                return a.width == b.width ? a.height < b.height : a.width < b.width;
            });
        const auto current = std::find(settings.resolutions.begin(), settings.resolutions.end(), settings.currentResolution);
        settings.resolutionIndex = static_cast<int>(current - settings.resolutions.begin());
        settings.resolutionAvailable = true;
    }
#endif
    settings.applyResolution = [&app](const ui::DisplayResolution& requested) {
#if defined(__EMSCRIPTEN__)
        (void)app; (void)requested;
        return false;
#else
        if (!app.window) return false;
        auto& settings = ui::frontendSettings();
        const SDL_DisplayID display = SDL_GetDisplayForWindow(app.window);
        const SDL_DisplayMode* desktop = SDL_GetDesktopDisplayMode(display);
        if (!desktop) return false;
        settings.displayResolution = {desktop->w,desktop->h};
        const bool useDesktop = requested.width == 0;
        const int width = useDesktop ? desktop->w : requested.width;
        const int height = useDesktop ? desktop->h : requested.height;
        bool applied = false;
        if (settings.fullscreen) {
            SDL_DisplayMode mode;
            if (!useDesktop && (!SDL_GetClosestFullscreenDisplayMode(display,width,height,0.f,true,&mode) ||
                mode.w != width || mode.h != height)) return false;
            applied = SDL_SetWindowFullscreenMode(app.window,useDesktop ? nullptr : &mode);
        } else {
            const float density = std::max(0.1f,SDL_GetWindowPixelDensity(app.window));
            applied = SDL_SetWindowSize(app.window,static_cast<int>(std::lround(width/density)),
                static_cast<int>(std::lround(height/density)));
        }
        // Evidence for the release checklist's resize/fullscreen item: the requested size and
        // what the window actually became (a compositor may round or refuse it).
        if (applied) {
            int w = 0, h = 0;
            SDL_GetWindowSizeInPixels(app.window, &w, &h);
            std::printf("[display] requested %dx%d%s, window now %dx%d\n", width, height,
                        settings.fullscreen ? " fullscreen" : "", w, h);
        }
        return applied;
#endif
    };
    settings.applyFullscreen = [&app](bool enabled) {
        auto& settings = ui::frontendSettings();
        if (!app.window) { settings.fullscreen = false; return; }
        const int previousResolution = settings.resolutionIndex;
#if !defined(__EMSCRIPTEN__)
        if (enabled && !settings.applyResolution(settings.resolutions[settings.resolutionIndex])) {
            if (!settings.applyResolution(settings.resolutions[0])) { settings.fullscreen = false; return; }
            settings.resolutionIndex = 0;
        }
#endif
        if (!SDL_SetWindowFullscreen(app.window,enabled)) {
            settings.fullscreen = !enabled;
            settings.resolutionIndex = previousResolution;
            std::printf("[display] fullscreen %s refused by the window system\n",
                        enabled ? "on" : "off");
            return;
        }
        int w = 0, h = 0;
        SDL_GetWindowSizeInPixels(app.window, &w, &h);
        std::printf("[display] fullscreen %s, window %dx%d\n", enabled ? "on" : "off", w, h);
    };
    settings.applyBindings = [&app]() {
        const auto& settings = ui::frontendSettings();
        for (int a = 0; a < fnd::input::ActionCount; ++a) {
            app.matchInput.set_keyboard_binding((fnd::input::Action)a, settings.keyboard[a]);
            for (int p = 0; p < 4; ++p)
                app.matchInput.set_gamepad_binding(p, (fnd::input::Action)a, settings.gamepad[p][a]);
        }
    };
    settings.applyBindings();
    if (app.settingsActive) {
        // Stable-controller identity: the hints have to be in place before the first pad
        // poll, so a replugged pad is given back its player slot (issue #19).
        for (int player = 0; player < fnd::input::kMaxPlayers; ++player)
            app.matchInput.set_gamepad_guid_hint(player, app.userSettings.padGuid[static_cast<size_t>(player)]);
        applyPersistedDisplay(app);
    }
    // FUN_00647e00 loads the system bank separately from gameplay data/se.
    if (app.menuAudio.open(fnd::audio::Spec{})) {
        app.menuAudio.set_volumes(settings.volumes);
        for (int i = 0; i < 4; ++i) {
            char stem[48];
            std::snprintf(stem, sizeof(stem), "data/sysse/%03d", i);
            const auto& source = fnd::assets::assetSource();
            const std::string path = source.resolve({std::string(stem)+".cnv", std::string(stem)+".wav"});
            app.menuSounds[i] = loadSoundAsset(app.menuAudio, path);
        }
    }
    playFrontendMusic(app, id);
    app.screensMode = true;
    std::printf("screen       : %s (0x%02x)\n", app.screens.screen()->name(),
                (int)app.screens.current());
    return true;
}

}  // namespace

#if defined(__EMSCRIPTEN__)
// Whether this page asked for the per-asset delivery path. Read once: the query string
// cannot change under a running wasm instance, and three call sites ask the same
// question (the bootstrap, the standalone match request, the VS hook).
static bool webDeliveryEnabled() {
    static const bool enabled = [] {
        const std::string value = plat::webQueryParam("delivery");
        return !value.empty() && value != "0";
    }();
    return enabled;
}
#endif

#if !defined(__EMSCRIPTEN__)
// A game opened from a file manager has no console, so everything it prints would be lost, including
// what a tester needs to report. The log sits beside the settings, and the last run's is kept once,
// since a player usually opens the game again after a crash.
static void logToFileWithoutConsole(const Options& options) {
    if (verificationRun(options) || options.frames > 0) return;
#if !defined(_WIN32)
    if (isatty(STDOUT_FILENO)) return;
#endif
    const std::filesystem::path config = std::filesystem::u8path(settingsFilePath());
    if (config.empty()) return;
    std::error_code error;
    std::filesystem::create_directories(config.parent_path(), error);
    const std::filesystem::path log = config.parent_path() / "daybreak.log";
    std::filesystem::rename(log, config.parent_path() / "daybreak-previous.log", error);
    if (!std::freopen(log.u8string().c_str(), "w", stdout)) return;
    std::setvbuf(stdout, nullptr, _IOLBF, 4096);
    // Both streams in one file, in the order they happened.
#if defined(_WIN32)
    _dup2(_fileno(stdout), _fileno(stderr));
#else
    dup2(fileno(stdout), fileno(stderr));
#endif
    std::setvbuf(stderr, nullptr, _IONBF, 0);
}
#endif

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
    auto* app = new App();
    *appstate = app;

#if defined(__EMSCRIPTEN__)
    // argv never reaches wasm, so the web build takes its asset four ways, in this
    // order: ?delivery=<base> (the self-hosted site's per-asset API, issue #4),
    // ?pack=<manifest-url> (the older pack loader, kept for local verification),
    // ?asset=<single CLI arg>, then the configure-time FOUNDATION_WEB_ASSET. Plain
    // builds with none of these keep the triangle demo.
    {
        static std::string webAsset;
        const std::string deliveryParam = plat::webQueryParam("delivery");
        const std::string packUrl = plat::webQueryParam("pack");
        // The site's entry point is ?delivery=1 (this origin); ?delivery=<origin> names
        // another one. The pack path stays available and unchanged beside it.
        const bool delivery = webDeliveryEnabled();
        if (delivery) {
            plat::AssetClient& client = plat::assetClient();
            const std::string base = (deliveryParam == "1") ? std::string() : deliveryParam;
            if (!client.begin(base)) {
                app->error = "asset delivery client refused to start";
                return SDL_APP_FAILURE;
            }
            // The startup gate: every asset the first usable screen needs, fetched and
            // validated one at a time. waitForGate yields to the browser rather than
            // spinning, so the page stays responsive; the optional startup assets (the
            // movie, BGM) keep loading from SDL_AppIterate's poll().
            const bool gateMet = client.waitForGate();
            // The gate line is also the cold/warm measurement the issue asks for: a cold
            // session pays the gate's transfer size here, a warm one pays nothing because
            // every asset was answered from the per-asset cache.
            std::printf("[delivery] startup gate %s: %s (network %llu request(s), %.1f MB "
                        "received)\n", gateMet ? "met" : "NOT met",
                        client.startupProgress().line("startup").c_str(),
                        (unsigned long long)client.networkRequests(),
                        double(client.bytesReceived()) / 1048576.0);
            if (!gateMet) {
                app->error = "startup assets unavailable: " + client.error();
                return SDL_APP_FAILURE;
            }
        } else if (!packUrl.empty()) {
            std::string packAsset;
            if (!plat::fetchWebPack(packUrl, packAsset, app->error)) return SDL_APP_FAILURE;
            webAsset = packAsset;
        }
        const std::string assetParam = plat::webQueryParam("asset");
        if (!assetParam.empty()) webAsset = assetParam;
#ifdef FOUNDATION_WEB_ASSET
        if (webAsset.empty()) webAsset = FOUNDATION_WEB_ASSET;
#endif
        static std::vector<std::string> webArgs;
        static std::vector<const char*> webArgv;
        webArgs.clear();
        webArgs.push_back("daybreak");
        if (!webAsset.empty()) webArgs.push_back(webAsset);
        // Local browser verification needs the same multi-asset recipe as native.
        const std::string extra = plat::webQueryParam("args");
        size_t begin = 0;
        while (begin < extra.size()) {
            const size_t end = extra.find('|', begin);
            const std::string arg = extra.substr(begin, end == std::string::npos ? end : end - begin);
            if (!arg.empty()) webArgs.push_back(arg);
            if (end == std::string::npos) break;
            begin = end + 1;
        }
        // The hosted site opens on the front end: delivery mode exists to serve it, so
        // with no explicit asset or args the default screen is the title rather than the
        // asset-free triangle demo.
        if (delivery && webAsset.empty() && extra.empty()) webArgs.push_back("--screen=title");
        webArgv.clear();
        for (const auto& arg : webArgs) webArgv.push_back(arg.c_str());
        argc = (int)webArgv.size();
        argv = const_cast<char**>(webArgv.data());
    }
#endif
    if (!parseArgs(argc, argv, app->opts, app->error)) {
        usage();
        return SDL_APP_FAILURE;
    }
    app->opts.bootOpening = resolveBootOpening(app->opts);
#if !defined(__EMSCRIPTEN__)
    logToFileWithoutConsole(app->opts);
#endif
    const bool muteOutput = app->opts.noAudio || (!app->opts.withAudio &&
        (verificationRun(app->opts) || app->opts.frames > 0 || app->opts.audioTest));
    fnd::audio::set_output_muted(muteOutput);
    if (muteOutput) std::printf("audio output : muted (verification/no-audio)\n");
#if defined(__EMSCRIPTEN__)
    // Delivery mode with a standalone recipe: request the match's assets from the
    // arguments and wait for them before the scene is built. A front-end run needs none
    // of this — its barrier is the VS transition.
    if (webDeliveryEnabled() && requestWebStandaloneGroup(*app)) {
        const bool ready = plat::assetClient().waitForMatch();
        std::printf("[delivery] match group %s: %s\n", ready ? "ready" : "INCOMPLETE",
                    plat::assetClient().matchProgress().line("match").c_str());
        if (!ready) {
            app->error = "match assets unavailable: " + plat::assetClient().error();
            return SDL_APP_FAILURE;
        }
    }
#endif

    // Headless verification: no window, no surface, no swapchain, so the adapter is
    // requested without a presentation target. That is what lets a machine with no
    // DRI3/Wayland display render on the real GPU: Mesa's Vulkan WSI cannot present
    // on Xvfb ("No DRI3 support detected - required for presentation"), and wgpu then
    // falls back to software GL, which would make a Linux/Wine capture pair compare
    // two different rasterizers.
    if (app->opts.headless) {
        if (!SDL_Init(SDL_INIT_EVENTS)) {
            app->error = SDL_GetError();
            return SDL_APP_FAILURE;
        }
        if (!gpu::createContext(app->ctx, nullptr, app->error)) return SDL_APP_FAILURE;
        std::printf("=== Higurashi Daybreak Kai Fan Remake ===\n");
        std::printf("video driver : headless (no window, no surface)\n");
        std::printf("adapter      : %s [%s]\n", app->ctx.adapterName.c_str(),
                    app->ctx.backend.c_str());
    } else {
        if (!plat::init(app->error)) return SDL_APP_FAILURE;

        app->window = plat::createWindow("Higurashi Daybreak Kai Fan Remake", 960, 540, app->error);
        if (!app->window) return SDL_APP_FAILURE;

        // instance -> surface -> adapter/device: the surface has to exist before the
        // adapter is chosen, because it is requested as "compatible with" it.
        if (!gpu::createInstance(app->ctx, app->error)) return SDL_APP_FAILURE;
        app->sc.surface = plat::createSurface(app->ctx.instance, app->window);
        if (!app->sc.surface) {
            app->error = "could not create a window surface: run the game from a desktop "
                         "session with a working Wayland or X11 display";
            return SDL_APP_FAILURE;
        }
        if (!gpu::createContext(app->ctx, app->sc.surface, app->error)) return SDL_APP_FAILURE;

        int w = 960, h = 540;
        SDL_GetWindowSizeInPixels(app->window, &w, &h);
        if (!gpu::configureSwapchain(app->ctx, app->sc, (uint32_t)w, (uint32_t)h, app->error))
            return SDL_APP_FAILURE;

        std::printf("=== Higurashi Daybreak Kai Fan Remake ===\n");
        std::printf("video driver : %s\n", plat::videoDriver());
        std::printf("adapter      : %s [%s]\n", app->ctx.adapterName.c_str(),
                    app->ctx.backend.c_str());
        std::printf("surface      : %dx%d, %d format(s), %d present mode(s), fifo=%s\n", w, h,
                    app->sc.formatCount, app->sc.presentModeCount,
                    app->sc.supportsFifo ? "yes" : "no");
        std::printf("surface format: 0x%x\n", (unsigned)app->sc.format);
        std::printf("present mode : %s\n", gpu::presentModeName(app->sc.presentMode));
    }

    if (app->opts.audioTest) return runAudioTest(*app) ? SDL_APP_SUCCESS : SDL_APP_FAILURE;
    if (app->opts.inputTest) return runInputTest(*app) ? SDL_APP_SUCCESS : SDL_APP_FAILURE;

    // Persisted settings land before any screen exists, so the first frame the frontend
    // draws already uses the user's volumes and bindings (issue #19). Capture and parity
    // runs skip this entirely — see usesUserConfig.
    if (usesUserConfig(app->opts)) loadUserSettings(*app);

    // Earlier folders win. A verification run reads only the pack it names, so what happens
    // to sit beside the executable cannot change a capture.
    std::vector<std::string> packs;
    if (!app->opts.texturePack.empty()) packs.push_back(app->opts.texturePack);
    if (!verificationRun(app->opts)) {
        if (const char* base = SDL_GetBasePath()) {
            packs.push_back(std::string(base) + "custom-textures");
            packs.push_back(std::string(base) + "hd-textures");
        }
    }
    const size_t packImages = fnd::assets::assetSource().openTexturePacks(packs);
    if (packImages > 0) std::printf("[pack] %zu image(s)\n", packImages);
    const bool ok = (!app->opts.screen.empty() || app->opts.bootOpening) ? initScreens(*app)
                   : hasAsset(app->opts)                                ? initScene(*app)
                                                                        : initTriangle(*app);
    if (!ok) return SDL_APP_FAILURE;

    app->startTime = app->lastTime = plat::now();
    return app->opts.list ? SDL_APP_SUCCESS : SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    return appIterate(static_cast<App*>(appstate));
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    return appEvent(static_cast<App*>(appstate), event);
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
#ifdef DAYBREAK_ONLINE
    if (static_cast<App*>(appstate)->netSession) reportNetSession(*static_cast<App*>(appstate)->netSession);
#endif
    appQuit(static_cast<App*>(appstate), result);
}
