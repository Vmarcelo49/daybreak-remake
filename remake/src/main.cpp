// ============================================================================
//  daybreak — main entry point.
//
//  Architecture:
//    main() bootstraps SDL2 + D3D9, creates the SceneManager with a
//    SceneContext (device + assets + viewport size), pushes the initial
//    Scene_Bootstrap, and runs the main loop:
//
//      while (mgr.is_running()) {
//          dt = steady_clock::now() - last_frame;
//          if (mgr.update(dt) == Quit) break;
//          mgr.render();
//          device->Present();
//      }
//
//  CLI modes:
//    daybreak.exe -dat <file.dat> -list         (DAT inspector, no SDL/D3D)
//    daybreak.exe -asset-info <bundle.dat>:... <asset-name>  (asset lookup, no SDL/D3D)
//    daybreak.exe -asset <bundle.dat>:... <asset-name>       (legacy: load 1 model directly)
//    daybreak.exe                               (scene state machine)
//
//  Window: fixed 800×600 (matches the original game's hardcoded resolution;
//  see docs/reverse-engineering.md section 14 + RE round 3).
// ============================================================================
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_syswm.h>

#include <windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#include <chrono>
#include <cstdio>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "assets/asset_manager.h"
#include "audio/audio_engine.h"
#include "core/scene.h"
#include "core/scene_manager.h"
#include "core/scenes.h"
#include "input/input_manager.h"
#include "file_parser/dat_bundle.h"
#include "file_parser/x_model_loader.h"
#include "physics/raycast.h"
#include "render/arena_camera.h"
#include "render/effect_system.h"
#include "render/x_model_renderer.h"

// ----------------------------------------------------------------------------
// RAII helper for COM-ish DX9 interfaces
// ----------------------------------------------------------------------------
template <class T>
void safe_release(T*& p) noexcept {
    if (p) { p->Release(); p = nullptr; }
}

// ----------------------------------------------------------------------------
// App state — owns the SDL window, D3D9 device, and AssetManager.
// Passed to scenes via the SceneContext struct.
// ----------------------------------------------------------------------------
struct App {
    SDL_Window*        window = nullptr;
    HWND               hwnd   = nullptr;
    IDirect3D9*        d3d    = nullptr;
    IDirect3DDevice9*  device = nullptr;
    D3DPRESENT_PARAMETERS pp{};  // stored for device Reset() on lost-device

    // Fixed resolution — matches the original game (RE round 3).
    static constexpr int kWidth  = 800;
    static constexpr int kHeight = 600;

    daybreak::assets::AssetManager  assets;
    daybreak::audio::AudioEngine   audio;
    daybreak::input::InputManager  input;
    daybreak::render::EffectSystem effects;
    std::vector<std::unique_ptr<daybreak::file_parser::DatBundle>> bundles;
};

// ----------------------------------------------------------------------------
// SDL → HWND (mirrors the original game's Win32 setup)
// ----------------------------------------------------------------------------
static bool acquire_hwnd(App& app) {
    SDL_SysWMinfo wm{};
    SDL_VERSION(&wm.version);
    if (!SDL_GetWindowWMInfo(app.window, &wm)) {
        std::fprintf(stderr, "[daybreak] SDL_GetWindowWMInfo failed: %s\n",
                     SDL_GetError());
        return false;
    }
#if defined(SDL_VIDEO_DRIVER_WINDOWS)
    if (wm.subsystem != SDL_SYSWM_WINDOWS) {
        std::fprintf(stderr, "[daybreak] unexpected WM subsystem %d\n",
            static_cast<int>(wm.subsystem));
        return false;
    }
    app.hwnd = wm.info.win.window;
#else
    return false;
#endif
    return app.hwnd != nullptr;
}

// ----------------------------------------------------------------------------
// D3D9 init (windowed, 800×600, with z-buffer)
// ----------------------------------------------------------------------------
static bool d3d_init(App& app) {
    app.d3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (!app.d3d) {
        std::fprintf(stderr, "[daybreak] Direct3DCreate9 failed\n");
        return false;
    }

    D3DPRESENT_PARAMETERS& pp = app.pp;
    pp.Windowed               = TRUE;
    pp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
    pp.BackBufferFormat       = D3DFMT_UNKNOWN;
    pp.BackBufferWidth        = App::kWidth;
    pp.BackBufferHeight       = App::kHeight;
    pp.EnableAutoDepthStencil = TRUE;
    pp.AutoDepthStencilFormat = D3DFMT_D16;
    pp.PresentationInterval   = D3DPRESENT_INTERVAL_ONE;

    HRESULT hr = app.d3d->CreateDevice(
        D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, app.hwnd,
        D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
        &app.pp, &app.device);
    if (FAILED(hr)) {
        hr = app.d3d->CreateDevice(
            D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, app.hwnd,
            D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
            &app.pp, &app.device);
    }
    if (FAILED(hr)) {
        std::fprintf(stderr, "[daybreak] CreateDevice failed: hr=0x%08lx\n",
                     static_cast<unsigned long>(hr));
        return false;
    }
    return true;
}

static void teardown(App& app) {
    app.effects.unload_all();
    app.input.shutdown();
    app.audio.shutdown();
    app.assets.unload_all();
    app.bundles.clear();
    safe_release(app.device);
    safe_release(app.d3d);
    if (app.window) {
        SDL_DestroyWindow(app.window);
        app.window = nullptr;
    }
    SDL_Quit();
}

// ============================================================================
// CLI tools — kept here so the same .exe can do double
// duty as a .DAT inspector / asset-info probe.
// ============================================================================
static int run_dat_tool(int argc, char* argv[]) {
    using namespace daybreak::file_parser;

    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        freopen("CONIN$",  "r", stdin);
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }

    if (argc < 4) {
        std::fprintf(stderr,
            "Usage:\n"
            "  %s -dat <file.dat> -list\n"
            "  %s -dat <file.dat> -extract <outdir>\n"
            "  %s -dat <file.dat> -extract-file <index> -out <path>\n",
            argv[0], argv[0], argv[0]);
        return 1;
    }

    const std::string dat_path = argv[2];
    const std::string subcmd   = argv[3];

    DatBundle bundle;
    if (!bundle.open(dat_path)) {
        std::fprintf(stderr, "[daybreak] failed to open .DAT: %s\n",
                     dat_path.c_str());
        return 1;
    }
    std::printf("[daybreak] opened %s  (%zu entries)\n",
                dat_path.c_str(), bundle.entries().size());

    if (subcmd == "-list") {
        for (const auto& e : bundle.entries()) {
            std::printf("%s\n", format_entry(e).c_str());
        }
        return 0;
    }

    if (subcmd == "-extract" && argc >= 5) {
        const std::string outdir = argv[4];
        std::printf("[daybreak] extracting %zu files to %s\n",
                    bundle.entries().size(), outdir.c_str());
        std::size_t ok = 0, fail = 0;
        for (const auto& e : bundle.entries()) {
            std::vector<uint8_t> data;
            if (!bundle.read_file(e, data)) {
                std::fprintf(stderr, "  FAIL  %s (read)\n", e.name.c_str());
                ++fail; continue;
            }
            std::string path = outdir;
            const bool needs_sep = path.empty() ||
                (path.back() != '\\' && path.back() != '/');
            if (needs_sep) path += '\\';
            path += e.name;
            std::string acc;
            for (std::size_t i = 0; i < path.size(); ++i) {
                acc += path[i];
                if (path[i] == '\\' || path[i] == '/') {
                    CreateDirectoryA(acc.c_str(), nullptr);
                }
            }
            FILE* f = std::fopen(path.c_str(), "wb");
            if (!f) { std::fprintf(stderr, "  FAIL  %s (open)\n",
                                    e.name.c_str()); ++fail; continue; }
            const std::size_t n = std::fwrite(data.data(), 1, data.size(), f);
            std::fclose(f);
            if (n != data.size()) {
                std::fprintf(stderr, "  FAIL  %s (short write)\n",
                             e.name.c_str()); ++fail; continue;
            }
            std::printf("  OK    %s  (%u bytes)\n",
                        e.name.c_str(), e.length);
            ++ok;
        }
        std::printf("[daybreak] extracted: %zu ok, %zu failed\n", ok, fail);
        return fail == 0 ? 0 : 1;
    }

    if (subcmd == "-extract-file" && argc >= 7 &&
        std::string(argv[5]) == "-out") {
        const std::string idx_str = argv[4];
        const std::string outpath = argv[6];
        int idx = std::atoi(idx_str.c_str());
        if (idx < 0) {
            std::fprintf(stderr, "invalid index: %s\n", idx_str.c_str());
            return 1;
        }
        const DatFileEntry* e = bundle.find_by_index(
            static_cast<uint32_t>(idx));
        if (!e) { std::fprintf(stderr, "index out of range: %d\n", idx); return 1; }
        std::vector<uint8_t> data;
        if (!bundle.read_file(*e, data)) {
            std::fprintf(stderr, "read failed for index %d\n", idx); return 1;
        }
        FILE* f = std::fopen(outpath.c_str(), "wb");
        if (!f) { std::fprintf(stderr, "cannot open %s\n", outpath.c_str()); return 1; }
        const std::size_t n = std::fwrite(data.data(), 1, data.size(), f);
        std::fclose(f);
        if (n != data.size()) { std::fprintf(stderr, "short write\n"); return 1; }
        std::printf("[daybreak] extracted index %d (%s, %u bytes) to %s\n",
                    idx, e->name.c_str(), e->length, outpath.c_str());
        return 0;
    }

    std::fprintf(stderr, "[daybreak] unknown -dat subcommand: %s\n",
                 subcmd.c_str());
    return 1;
}

static int run_asset_info_tool(int argc, char* argv[]) {
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        freopen("CONIN$",  "r", stdin);
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }
    if (argc < 4) {
        std::fprintf(stderr,
            "Usage: %s -asset-info <bundle.dat>[:<bundle.dat>...] <asset-name>\n",
            argv[0]);
        return 1;
    }
    using namespace daybreak::file_parser;

    std::vector<std::unique_ptr<DatBundle>> bundles;
    std::vector<DatBundle*> bundle_ptrs;
    std::string bundle_list = argv[2];
    size_t start = 0;
    while (start <= bundle_list.size()) {
        size_t colon = bundle_list.find(':', start);
        std::string path = (colon == std::string::npos)
            ? bundle_list.substr(start)
            : bundle_list.substr(start, colon - start);
        if (!path.empty()) {
            auto b = std::make_unique<DatBundle>();
            if (b->open(path)) {
                std::printf("[daybreak] opened %s (%zu entries)\n",
                            path.c_str(), b->entries().size());
                bundle_ptrs.push_back(b.get());
                bundles.push_back(std::move(b));
            }
        }
        if (colon == std::string::npos) break;
        start = colon + 1;
    }
    if (bundle_ptrs.empty()) {
        std::fprintf(stderr, "[daybreak] no bundles opened\n");
        return 1;
    }
    std::string asset_name = argv[3];
    const DatFileEntry* entry = nullptr;
    DatBundle* src_bundle = nullptr;
    for (DatBundle* b : bundle_ptrs) {
        entry = b->find_by_name(asset_name);
        if (entry) { src_bundle = b; break; }
    }
    if (!entry) {
        std::fprintf(stderr, "[daybreak] asset not found: %s\n",
                     asset_name.c_str());
        return 1;
    }
    std::printf("[daybreak] found: %s\n  index: %u\n  offset: %u\n  length: %u\n",
                asset_name.c_str(), entry->index, entry->offset, entry->length);
    std::vector<uint8_t> bytes;
    if (!src_bundle->read_file(*entry, bytes)) {
        std::fprintf(stderr, "read_file failed\n"); return 1;
    }
    std::printf("  magic hex: ");
    for (size_t i = 0; i < 16 && i < bytes.size(); ++i)
        std::printf("%02x ", bytes[i]);
    std::printf("\n  magic str: ");
    for (size_t i = 0; i < 16 && i < bytes.size(); ++i) {
        uint8_t c = bytes[i];
        std::printf("%c ", (c >= 32 && c < 127) ? c : '.');
    }
    std::printf("\n");
    return 0;
}

// ============================================================================
// Main loop
// ============================================================================
int main(int argc, char* argv[]) {
    // ---- CLI modes (no SDL/D3D) ----
    if (argc >= 2 && std::string(argv[1]) == "-dat") {
        return run_dat_tool(argc, argv);
    }
    if (argc >= 2 && std::string(argv[1]) == "-asset-info") {
        return run_asset_info_tool(argc, argv);
    }

    // ---- GUI mode: bootstrap SDL + D3D + SceneManager ----
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) != 0) {
        std::fprintf(stderr, "[daybreak] SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    App app;
    app.window = SDL_CreateWindow(
        "daybreak",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        App::kWidth, App::kHeight,
        SDL_WINDOW_SHOWN);
    if (!app.window) {
        std::fprintf(stderr, "[daybreak] SDL_CreateWindow failed: %s\n",
                     SDL_GetError());
        SDL_Quit();
        return 1;
    }
    if (!acquire_hwnd(app)) { teardown(app); return 1; }
    if (!d3d_init(app))     { teardown(app); return 1; }

    app.input.init();

    // Bundle registration (P1.1, from mvp/src/archive_init.c): the
    // original loads daybreak00/02/04/05/06/07.dat in this order,
    // first match wins.  -asset overrides the list explicitly; otherwise
    // try the 6 canonical names from the working directory, tolerating
    // absent files (scenes fail gracefully until bundles exist).
    std::string bundle_list;
    if (argc >= 4 && std::string(argv[1]) == "-asset") {
        bundle_list = argv[2];
    } else {
        bundle_list =
            "daybreak00.dat:daybreak02.dat:daybreak04.dat:"
            "daybreak05.dat:daybreak06.dat:daybreak07.dat";
    }
    size_t start = 0;
    while (start <= bundle_list.size()) {
        size_t colon = bundle_list.find(':', start);
        std::string path = (colon == std::string::npos)
            ? bundle_list.substr(start)
            : bundle_list.substr(start, colon - start);
        if (!path.empty()) {
            auto b = std::make_unique<daybreak::file_parser::DatBundle>();
            if (b->open(path)) {
                std::printf("[daybreak] bundle: %s (%zu entries)\n",
                            path.c_str(), b->entries().size());
                app.bundles.push_back(std::move(b));
            } else if (argc >= 4 && std::string(argv[1]) == "-asset") {
                std::fprintf(stderr, "[daybreak] bundle not found: %s\n",
                             path.c_str());
            }
        }
        if (colon == std::string::npos) break;
        start = colon + 1;
    }
    std::printf("[daybreak] %zu/6 archives loaded\n", app.bundles.size());
    app.assets.set_device(app.device);
    for (auto& b : app.bundles) app.assets.register_bundle(b.get());

    // Strict effect load (P3.1): any missing/failing effect aborts
    // startup — rendering without effects is a bug, not a degraded mode.
    if (!app.effects.load(app.device)) {
        std::fprintf(stderr, "[daybreak] EffectSystem load failed — aborting\n");
        teardown(app);
        return 1;
    }

    daybreak::SceneContext ctx;
    ctx.device     = app.device;
    ctx.assets     = &app.assets;
    ctx.audio      = &app.audio;
    ctx.input      = &app.input;
    ctx.effects    = &app.effects;
    ctx.viewport_w = App::kWidth;
    ctx.viewport_h = App::kHeight;

    daybreak::SceneManager mgr(ctx);
    // Skip Bootstrap+Opening+Title+ModeSelect+CharacterSelect — go straight
    // to Gameplay.
    {
        auto gameplay = std::make_unique<daybreak::Scene_Gameplay>();
        gameplay->m_p1CharIndex = 0;  // rika
        gameplay->m_p2CharIndex = 1;  // takano
        mgr.start(std::move(gameplay));
    }

    // ---- main loop ----
    // P1.2: device-lost recovery (TestCooperativeLevel → Reset, from
    // mvp/src/render_loop.c).  P1.3: 60 fps throttle on top of vsync.
    using clock = std::chrono::steady_clock;
    constexpr double kMinFrame = 1.0 / 60.0;
    auto last = clock::now();
    uint64_t frame_count = 0;
    double fps_timer = 0.0;
    uint64_t frames_in_window = 0;

    while (mgr.is_running()) {
        HRESULT coop = app.device->TestCooperativeLevel();
        if (coop == D3DERR_DEVICELOST) {
            SDL_Delay(50);
            last = clock::now();
            continue;
        }
        if (coop == D3DERR_DEVICENOTRESET) {
            if (SUCCEEDED(app.device->Reset(&app.pp))) {
                // Reset destroys D3DPOOL_DEFAULT resources — re-enter
                // the scene so on_enter rebuilds them.
                mgr.reset_current();
            } else {
                SDL_Delay(50);
                last = clock::now();
                continue;
            }
        }

        const auto now = clock::now();
        const std::chrono::duration<double> dt_dur = now - last;
        const double dt = dt_dur.count();

        if (mgr.update(dt) == daybreak::UpdateResult::Quit) break;

        mgr.render();
        app.device->Present(nullptr, nullptr, nullptr, nullptr);

        // FPS counter (debug).
        ++frame_count;
        ++frames_in_window;
        fps_timer += dt;
        if (fps_timer >= 1.0) {
            double fps = static_cast<double>(frames_in_window) / fps_timer;
            std::printf("[daybreak] fps=%.1f scene=%s frames=%llu\n",
                        fps, mgr.current() ? mgr.current()->name() : "(none)",
                        static_cast<unsigned long long>(frame_count));
            frames_in_window = 0;
            fps_timer = 0.0;
        }

        // Throttle to 60 fps; `last` is stamped after the sleep so dt
        // stays real time.
        const std::chrono::duration<double> frame_dur =
            clock::now() - now;
        if (frame_dur.count() < kMinFrame) {
            SDL_Delay(static_cast<Uint32>(
                (kMinFrame - frame_dur.count()) * 1000.0));
        }
        last = clock::now();
    }

    std::printf("[daybreak] main loop ended after %llu frames\n",
                static_cast<unsigned long long>(frame_count));

    teardown(app);
    return 0;
}
