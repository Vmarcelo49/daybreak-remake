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
#include "frontend/frontend_state.h"
#include "frontend/frontend_launch.h"
#include "frontend/participants.h"
#include "frontend/frontend_settings.h"
#include "settings/user_settings.h"
#include "hud/hud_bridge.h"
#include "camera/fighter_pose.h"
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



// ---------------------------------------------------------------------------------------
// The app
// ---------------------------------------------------------------------------------------
// The stack asks for a screen per id; the battle itself is drawn by the match path.




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
static void loadUserSettings(App& app) {
    app.settingsPath = settings::defaultConfigPath();
#if defined(_WIN32)
    // Explorer launches usually have no HOME/XDG variables. Use Windows user
    // application data so a portable release never writes settings into the game.
    if (!std::getenv("XDG_CONFIG_HOME")) {
        if (char* directory = SDL_GetPrefPath("", "daybreak-decomp")) {
            app.settingsPath = std::string(directory) + "settings.conf";
            SDL_free(directory);
        }
    }
#endif
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

// Defined beside the media helpers further down; the pause cue loads through it.
static fnd::audio::SfxHandle loadSoundAsset(fnd::audio::Sdl3Engine& engine, const std::string& path);
// Defined with the match setup further down; the standalone rematch rebuilds through it.
static bool initMatch(App& app);

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

void writePpm(const std::string& path, const std::vector<uint8_t>& rgba, int w, int h) {
    std::FILE* f = std::fopen(path.c_str(), "wb");
    if (!f) {
        std::fprintf(stderr, "cannot write %s\n", path.c_str());
        return;
    }
    std::fprintf(f, "P6\n%d %d\n255\n", w, h);
    for (int i = 0; i < w * h; ++i) std::fwrite(rgba.data() + i * 4, 1, 3, f);
    std::fclose(f);
    std::printf("wrote %s\n", path.c_str());
}

// The shadow pass's own counts (issue #21 row 1): casters are the character/weapon draws
// the light-space map received this frame, receivers the stage draws that sampled it. Both
// are zero on a frame without the pass, so this is the honest check that a capture's
// --shadows actually reached the renderer rather than silently staying off.
// DSH_DUMP_SHADOW=<path>: write the first view's shadow map as a PGM after a capture.
// Gated and read on demand — the map is the only artefact that separates "the caster pass
// drew nothing" from "the receiver's lookup missed", and neither is visible in a frame.
void maybeDumpShadowMap(App& app) {
    const char* path = std::getenv("DSH_DUMP_SHADOW");
    if (!path || !*path || !app.rendererReady) return;
    std::string why;
    if (!app.renderer.dumpShadowMap(path, why))
        std::fprintf(stderr, "[shadow] dump failed: %s\n", why.c_str());
    else
        std::printf("shadow map dumped to %s\n", path);
}

void reportShadows(const render::Stats& st) {
    if (st.shadowCasters > 0 || st.shadowReceivers > 0)
        std::printf("shadows: %d caster draw(s) into the map, %d receiver draw(s) sampling it\n",
                    st.shadowCasters, st.shadowReceivers);
}

void reportCoverage(const std::vector<uint8_t>& rgba, int w, int h) {
    int covered = 0;
    float minLum = 1.f, maxLum = 0.f;
    for (int i = 0; i < w * h; ++i) {
        const uint8_t* p = rgba.data() + i * 4;
        if (p[0] < 20 && p[1] < 22 && p[2] < 26) continue;   // clear colour
        const float lum = (0.2126f * p[0] + 0.7152f * p[1] + 0.0722f * p[2]) / 255.f;
        ++covered;
        minLum = std::min(minLum, lum);
        maxLum = std::max(maxLum, lum);
    }
    std::printf("coverage: %d px of %d (%.2f%%)  luminance %.3f..%.3f\n", covered, w * h,
                100.0 * covered / (double)(w * h), minLum, maxLum);
}

void report(App& app) {
    const double elapsed = plat::now() - app.startTime;
    const double avg = app.frames ? app.deltaSum / (double)app.frames : 0.0;
    std::printf("\n-- render frame timing (wall-clock delta) --\n");
    std::printf("frames      : %llu in %.3f s\n", (unsigned long long)app.frames, elapsed);
    if (app.opts.match || !app.opts.screen.empty())
    {
        // Print the live cadence from its single source rather than a second literal,
        // so the diagnostic cannot drift from FixedStep::tickRate again (F1-9).
        char cadence[16];
        std::snprintf(cadence, sizeof cadence, "%d Hz", gameplay::FixedStep::tickRate);
        std::printf("logic       : %llu ticks, %s\n", (unsigned long long)app.logicTicks,
                    app.opts.out.empty() ? cadence : "explicit capture cadence");
    }
    if (app.frames > 1) {
        std::printf("delta avg   : %.3f ms (%.1f fps)\n", avg * 1000.0, avg > 0 ? 1.0 / avg : 0.0);
        std::printf("delta min   : %.3f ms\n", app.deltaMin * 1000.0);
        std::printf("delta max   : %.3f ms\n", app.deltaMax * 1000.0);
    } else {
        // The first delta is deliberately excluded (it contains setup time), so a
        // one-frame run — which is what a capture is — has no delta to report.
        std::printf("delta       : not sampled (a single frame has no delta)\n");
    }
    std::printf("RESULT: %s\n", app.error.empty() ? "ok" : app.error.c_str());
}


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
        id == ui::ScreenId::Select ? "data/bgm/select01.ogg" :
        id == ui::ScreenId::VsIntro ? "data/bgm/vs.ogg" :
        id == ui::ScreenId::Result && app.frontend.resultWinner >= 0 ?
            (app.frontend.resultWinner == localSide ? "data/bgm/win.ogg" : "data/bgm/lose.ogg") : nullptr;
    // Already playing exactly this track: leave it running. The host starts a scene's music
    // when its fade BEGINS (SDL_AppIterate), so by the time the factory constructs the scene
    // 25 frames later the track is up and restarting it here would cut the first bars —
    // which is the hole this whole path exists to close.
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
    if (!ui::frontendLaunch(app.frontend, launch, app.error, (uint32_t)app.logicTicks)) return false;
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
    // No --screen and a plain launch means the original's boot scene, 0x00 (resolveBootOpening
    // decided that); anything else here has to name an id the parser knows.
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

    const bool ok = (!app->opts.screen.empty() || app->opts.bootOpening) ? initScreens(*app)
                   : hasAsset(app->opts)                                ? initScene(*app)
                                                                        : initTriangle(*app);
    if (!ok) return SDL_APP_FAILURE;

    app->startTime = app->lastTime = plat::now();
    return app->opts.list ? SDL_APP_SUCCESS : SDL_APP_CONTINUE;
}

// ---------------------------------------------------------------------------------------
// The --hud-test rig: one deterministic synthetic HUD, composited into --out captures
// through the renderer's UiHook (same encoder, same 3D-then-UI order a game uses).
// Fixed values, so captures stay byte-identical across runs and targets.
//
// A match composites one pass per human view (issue #12): each pass draws its view's own
// HUD state into that view's cell. Everything else is one pass over the whole target, which
// is exactly what this hook did before split-screen existed.
// ---------------------------------------------------------------------------------------


ui::HudState syntheticHudState() {
    // Field-equal to game::syntheticHudState() by construction (the track's own
    // test pins it); forwarding keeps one definition of the test values.
    return game::syntheticHudState();
}

HudTestHook battleHudHook(App& app) {
    HudTestHook hook{&app.uiRenderer, &app.hudComposer, &app.error, app.opts.hudProbe};
    if (app.versusMode) {
        hook.passes.push_back(HudPass{app.versusHud, true, true, {}});
    }
    return hook;
}

// The match's HUD passes: one per rendered view, in view order, each carrying the state
// that view's controller filled at tick time and the cell geometry gave it.
void appendMatchHudPasses(App& app, const std::vector<FrameView>& views, uint32_t width,
                          uint32_t height, HudTestHook& hook) {
    hook.target = ui::UiViewport{width, height, 0, 0};
    const bool noticesOnly = app.battle->hud_hidden();
    for (const FrameView& view : views) {
        // Phase 3 draws its notices once over the whole target, with the battle HUD gone.
        if (noticesOnly && (&view != &views.front() ||
                            (view.hud.noticeType < 0 && view.hud.resultWinner < 0 &&
                             view.hud.resultBarOffset < 0))) continue;
        HudPass pass;
        pass.state = view.hud;
        pass.state.noticesOnly = noticesOnly;
        pass.hasState = true;
        // A match view's markers were already projected into its own logical viewport, so
        // they need no reference-coordinate shift; the versus vignette still does.
        pass.referenceCoordinates = false;
        pass.viewport = noticesOnly ? hook.target
                                    : ui::UiViewport{(uint32_t)view.cell.w, (uint32_t)view.cell.h,
                                                     (uint32_t)view.cell.x, (uint32_t)view.cell.y};
        hook.passes.push_back(std::move(pass));
    }
    hook.syntheticWhenEmpty = false;
    const int separators = noticesOnly ? 0 : game::separatorCount(game::splitLayoutFor(app.matchViewCount));
    for (int i = 0; i < separators; ++i) {
        const game::ViewRect rect = game::separatorRect(i, width, height);
        hook.separators.push_back(ui::UiRect{rect.x, rect.y, rect.w, rect.h});
    }
}

// The split-screen evidence line: which layout ran, and per view its controller, its
// fighter, its cell and the HUD values that view actually drew. Printed on the capture
// frame and periodically by --local-players, so a headless run shows independent per-view
// cameras and HUD values without reading pixels.
void reportMatchViews(const App& app, uint32_t width, uint32_t height) {
    const game::SplitLayout layout = game::splitLayoutFor(app.matchViewCount);
    std::printf("[split] layout=%s views=%d target=%ux%u roster=%d\n",
                layout == game::SplitLayout::Single ? "single"
                                                    : (layout == game::SplitLayout::Two ? "two" : "four"),
                app.matchViewCount, width, height, app.participantCount);
    for (int v = 0; v < app.matchViewCount; ++v) {
        const game::MatchView& view = app.matchViews[v];
        if (!view.active()) continue;
        const game::ViewRect rect = game::viewCell(layout, v, width, height);
        const ui::HudState& hud = view.hud;
        // `followed` is the camera's own followed fighter, next to `fighter`, the one it
        // must follow for the whole match (issue #51): printing both makes a cell whose
        // camera left its fighter visible in the report instead of only in the pixels.
        std::printf("[split] view %d: controller=%d fighter=%d followed=%d "
                    "cell=(%.0f,%.0f,%.0f,%.0f) "
                    "hp=%.0f main=%d charge=%d stamina=%.2f hyper=%s gauge=%.2f\n",
                    v, view.controller, view.fighter, view.followed, rect.x, rect.y, rect.w,
                    rect.h, hud.hp, hud.mainWhole, hud.chargeWhole, hud.staminaFrac,
                    hud.hyperName.c_str(), hud.hyperGauge);
        // Per-participant markers, projected through THIS view's camera on this frame's own
        // cell: the entry's role, its tag (controller/COM), whether this view sees it and
        // which edge its marker points at when it does not (issue #13's evidence line).
        ui::HudState projected = hud;
        const glm::mat4 viewProj = view.camera.proj_matrix((int)rect.w, (int)rect.h) *
                                   view.camera.view_matrix();
        projectViewHud(app, &viewProj[0][0], rect.w, rect.h, projected);
        for (int i = 0; i < app.participantCount; ++i) {
            const ui::HudFighterHud& f = projected.fighters[i];
            const ui::Participant& p = app.participants[i];
            std::printf("[split]   p%d panel=%d team=%d %s %s role=%s fighter=%d visible=%d "
                        "target=%d incoming=%d reticle=%d hp=%.0f ring=(%.0f,%.0f)\n",
                        i, p.panel, p.team, ui::controllerLabel(p.controller), p.combo().c_str(),
                        f.role == ui::HudFighterRole::Owner
                            ? "owner"
                            : (f.role == ui::HudFighterRole::Ally ? "ally" : "enemy"),
                        p.fighter, f.visible ? 1 : 0, f.target ? 1 : 0, f.targetsViewer ? 1 : 0,
                        f.ring ? 1 : 0, f.hp * 100.f, f.ringX, f.ringY);
        }
    }
}

bool hudTestHook(WGPUCommandEncoder enc, WGPUTextureView view, WGPUTextureFormat format,
                 uint32_t w, uint32_t h, void* ud) {
    auto* hk = static_cast<HudTestHook*>(ud);
    if (hk->passes.empty() && hk->syntheticWhenEmpty) {
        HudPass pass;
        pass.viewport = ui::UiViewport{w, h, 0, 0};
        hk->passes.push_back(std::move(pass));
    }
    for (const HudPass& pass : hk->passes) {
        // A pass with no cell of its own is the whole target — the versus vignette, the
        // synthetic --hud-test frame and every pre-split-screen capture path.
        const ui::UiViewport viewport = pass.viewport.w && pass.viewport.h
            ? pass.viewport
            : ui::UiViewport{w, h, 0, 0};
        hk->ui->beginFrame(viewport);
        ui::HudState state = pass.hasState ? pass.state : syntheticHudState();
        if (pass.referenceCoordinates) {
            const auto layout = ui::computeBattleHudLayout(viewport.w,viewport.h);
            for (auto& fighter : state.fighters) {
                fighter.ringX += (layout.width-800.f)*.5f;
                fighter.barX += (layout.width-800.f)*.5f;
                fighter.ringY += (layout.height-600.f)*.5f;
                fighter.barY += (layout.height-600.f)*.5f;
            }
        }
        hk->hud->compose(*hk->ui, state);
        if (hk->probe) {
            // Two markers in the VIEW's own coordinates: the top-left and the
            // bottom-right corner of this pass's viewport. A capture then pins the
            // view -> target mapping exactly (tests/hud_cell_scale.py): correct means
            // each cell's markers sit on that cell's corners, and the split-screen HUD
            // scale defect moved them to half the cell instead. The composer leaves its
            // canvas transform and clip set, so both are reset first — otherwise the
            // markers inherit the HUD's own clip and half of them never reach the frame.
            hk->ui->resetCanvasTransform();
            const float mw = 6.f;
            hk->ui->pushSolid({0.f, 0.f, mw, mw}, ui::UiColor{1.f, 0.f, 1.f, 1.f});
            hk->ui->pushSolid({(float)viewport.w - mw, (float)viewport.h - mw, mw, mw},
                              ui::UiColor{0.f, 1.f, 1.f, 1.f});
        }
        if (!hk->ui->render(enc, view, format, *hk->error)) return false;
    }
    if (!hk->separators.empty()) {
        hk->ui->beginFrame(hk->target);
        for (const ui::UiRect& rect : hk->separators)
            hk->ui->pushSolid(rect, ui::UiColor{0.f, 0.f, 0.f, 1.f});
        if (!hk->ui->render(enc, view, format, *hk->error)) return false;
    }
    return true;
}


bool screenCaptureHook(WGPUCommandEncoder enc, WGPUTextureView view, WGPUTextureFormat format,
                       uint32_t w, uint32_t h, void* ud) {
    auto* sk = static_cast<ScreenCaptureHook*>(ud);
    return sk->overlay
        ? ui::drawScreenOverlay(*sk->screens, *sk->ui, w, h, enc, view, format, *sk->error)
        : ui::drawScreenFrame(*sk->screens, *sk->ui, w, h, enc, view, format, *sk->error);
}

// The overlay's line set: a pure function of loaded state (bounds, aim, desired eye), so
// two runs of the same frame upload identical bytes — no clock, no RNG, no container
// iteration whose order could vary. render/debug_prims.h documents why captures care.
//
// The eye->aim ray is deliberately NOT drawn: the camera always looks at the aim (and
// sits at the desired eye), so such a segment is edge-on and invisible. The arena mode
// marks the desired eye with its own cross instead — the point the clamp and the
// smoothing spring pull towards, and the one place a camera bug shows up.
void fillDebugLines(App& app) {
    app.debugLines.clear();
    float cross = 40.f;
    if (app.haveDebugBounds) {
        app.debugLines.box(app.debugBoundsLo, app.debugBoundsHi, render::kYellow);
        // Sized from the box so the cross reads at any framing distance: a fixed 40
        // units is sub-pixel in a stage whose play area spans thousands.
        cross = std::max(20.f, 0.015f * glm::length(app.debugBoundsHi - app.debugBoundsLo));
    }
    app.debugLines.cross(app.target, cross, render::kRed);
    if (app.opts.camera == "arena")
        app.debugLines.cross(app.arenaDesired, cross * 0.75f, render::kCyan);
}

// capture() owns its colour and depth textures and takes ONE hook, so the UI pass and
// the prims pass share this one: HUD first (it is the frame's overlay), prims second.
// Both preserve the frame they annotate (LoadOp_Load), so the order between them is
// the only difference. The depth view is read inside the hook, never before it: the
// --anim-player input. Arrows step the set index, WASD orbits. This view deliberately
// ignores matchInput: a clip browser wants raw keys, not the gameplay action map, where
// Up is bound to double-tap dash.
static void animPlayerKey(App& app, SDL_Keycode key) {
    int sets = 0;
    if (!app.scene.models.empty()) sets = (int)app.scene.models[0].model.anims.size();
    if (sets <= 0) return;
    switch (key) {
        case SDLK_RIGHT: case SDLK_UP:
            app.apIndex = (app.apIndex + 1) % sets;
            break;
        case SDLK_LEFT: case SDLK_DOWN:
            app.apIndex = (app.apIndex - 1 + sets) % sets;
            break;
        case SDLK_W: app.apPitch -= 0.08f; break;
        case SDLK_S: app.apPitch += 0.08f; break;
        case SDLK_A: app.apYaw -= 0.12f; break;
        case SDLK_D: app.apYaw += 0.12f; break;
        default: return;
    }
    app.apPitch = std::clamp(app.apPitch, -1.2f, 1.2f);
    app.apTime = 0.0;   // a new clip starts at its beginning
}

// Advances the browsed clip and re-poses the rig. Runs in the frame loop so the clip
// plays, is looped at its own length, and re-poses when the index changes.
static void animPlayerTick(App& app, double dt) {
    if (app.scene.models.empty()) return;
    xm::Model& m = app.scene.models[0].model;
    if (app.apIndex < 0 || app.apIndex >= (int)m.anims.size()) return;

    xm::Controller& c = app.controllers[0];
    if (app.apIndex != app.opts.anim) {
        app.opts.anim = app.apIndex;
        c.bind(&m);
        c.setAnimation(app.apIndex, true);
        // AnimSet::duration is in the file's own ticks; setTrackPosition takes SECONDS
        // and converts through Model::ticksPerSecond (xmodel.h:1979). So the length is
        // converted here once, and the per-frame seek stays in seconds.
        const double tps = m.ticksPerSecond > 0.f ? (double)m.ticksPerSecond : 4800.0;
        app.apLength = std::max(0.05, (double)m.anims[app.apIndex].duration / tps);
        app.apTime = 0.0;
    }
    app.apTime += dt;
    if (app.apTime > app.apLength) app.apTime = std::fmod(app.apTime, app.apLength);
    c.setTrackPosition(0, app.apTime);
    c.evalWorld(app.worlds[0]);

    // The equipped props were loaded against models[0]'s rig (loadScene) and must follow
    // it every frame, or the weapon freezes at the bind pose while the body animates.
    // Same composition the match uses per fighter (placeAttachedProp); the browser's one
    // rig owns every prop and its model matrix is the identity.
    for (size_t i = 1; i < app.scene.models.size(); ++i)
        if (app.scene.models[i].attachFrame >= 0) placeAttachedProp(app, i, 0);
    app.renderer.setModelMatrices(app.modelMatrices);

    const float ch = std::cos(app.apPitch);
    app.target = glm::vec3(0.f, 80.f, 0.f);
    app.eye = app.target + glm::vec3(std::sin(app.apYaw) * ch, std::sin(app.apPitch),
                                     std::cos(app.apYaw) * ch) * app.apDist;
}



bool captureHook(WGPUCommandEncoder enc, WGPUTextureView view, WGPUTextureFormat format,
                 uint32_t w, uint32_t h, void* ud) {
    auto* ck = static_cast<CaptureHook*>(ud);
    if (ck->pauseApp) {
        App& paused = *static_cast<App*>(ck->pauseApp);
        if (paused.battlePaused &&
            !drawBattlePauseOverlay(paused, enc, view, w, h, format)) return false;
    }
    if (ck->hud && !hudTestHook(enc, view, format, w, h, ck->hud)) return false;
    if (!ck->prims) return true;
    const render::Target target{enc, view, format, w, h};
    for (const render::ViewCamera& frameView : ck->views) {
        const render::ViewportRect& rect = frameView.rect;
        if (ck->solid && !ck->solid->empty()) {
            render::DebugPrims::Options o;   // depth-tested, the reference's opaque cube pass
            o.viewport = rect;
            if (!ck->prims->drawCubes(target, frameView.viewProj, *ck->solid,
                                      ck->renderer->depthView(), o, *ck->error))
                return false;
        }
        if (ck->additive && !ck->additive->empty()) {
            render::DebugPrims::Options o;
            o.additive = true;   // SrcAlpha/One, the aura pass's blend
            o.viewport = rect;
            if (!ck->prims->drawCubes(target, frameView.viewProj, *ck->additive,
                                      ck->renderer->depthView(), o, *ck->error))
                return false;
        }
        if (ck->lines && !ck->lines->empty()) {
            render::DebugPrims::Options o = ck->primOptions;
            o.viewport = rect;
            if (!ck->prims->draw(target, frameView.viewProj, *ck->lines,
                                 ck->renderer->depthView(), o, *ck->error))
                return false;
        }
    }
    return true;
}

static SDL_AppResult tickFrontend(App& state) {
    App* app = &state;
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
    const std::string voice = app->screens.takeVoice();
    if (!voice.empty()) {
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

SDL_AppResult SDL_AppIterate(void* appstate) {
    auto* app = static_cast<App*>(appstate);

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
            if (app->frontendMatch && app->battle->economy().roundOver()) {
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
                app->matchMode = false;
                app->frontendBattleReady = false;
                app->versusAudio.clear_music();
                // The match is over: release every channel the combat layer claimed, so the
                // result screen's own cues and the next match start from a clean bus
                // (issue #16's repeated-match cleanup). The decoded sample cache stays.
                reportCombatAudio(*app);
                stopCombatAudio(*app);
                app->screens.requestInstant(ui::ScreenId::Result);
                app->resultOverScene = true;
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

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    auto* app = static_cast<App*>(appstate);
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

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    auto* app = static_cast<App*>(appstate);
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
