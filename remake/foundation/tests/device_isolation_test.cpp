// =============================================================================
//  device_isolation_test.cpp — issue #29 regression guard.
//
//  THE DEFECT (issue #29, measured during #23's gate): SDL reports a connected controller
//  whether or not the window has focus, so on a machine whose owner was using the pad for
//  another game, that pad's live input reached this port's menus and captures. The measured
//  effects: `hud_cell_scale` failed ("cyan marker MISSING"), a `--screen=title
//  --local-players=2` run picked the title's *story* item instead of *versus* because the
//  pad's state moved the cursor first, and the four-view battle capture produced a
//  different hash on every run of the same binary (also at a pre-change commit, so it was
//  never a regression from one issue).
//
//  WHAT THIS DRIVES — the real app and the real injection path, not a re-statement:
//    * `src/main.cpp` is compiled into this TU (SDL_MAIN_HANDLED, so its SDL_App* entry
//      points do not collide with this test's main) and driven the way SDL drives a
//      callbacks app: SDL_AppInit -> SDL_AppIterate* -> SDL_AppQuit, with focus events
//      delivered through SDL_AppEvent, the same entry point SDL calls.
//    * the frames compared are the demo's own `--out` PPM captures, read back and hashed
//      byte for byte (FNV-1a 64); the menu's scene ladder is compared too, so a failure
//      says WHICH scene the stray input reached and not merely that pixels moved.
//    * device events are injected through the backend's documented feeds —
//      `Backend::note_key` / `Backend::note_gamepad_button` — plus a real
//      `SDL_PushEvent(KEY_DOWN)`, which is the queue the backend's own drain_key_events()
//      harvests in a headless run, and a real SDL gamepad
//      (`SDL_AttachVirtualJoystick`), which the backend opens into a player slot and polls
//      with `SDL_GetGamepadButton` exactly like the attached hardware. Nothing here mocks
//      or bypasses those paths.
//
//  WHAT IT ASSERTS (every row is the same headless title capture, `--frames=200`, so every
//  row's picture is the same picture whenever device input is ignored):
//    * (a) a VERIFICATION run (--headless/--out=) is device-free by default: a capture with
//      a keyboard walk, a forwarded pad walk, a pushed SDL key and a virtual gamepad's
//      press injected into it is byte- and ladder-identical to the same capture with
//      nothing injected. That is the issue's acceptance test — pre-change the injected pad
//      walks the title's cursor off *versus*, confirms, and the run ends on the select
//      screen instead.
//    * the injection is live, i.e. the test is not vacuous: with `--devices` the same
//      injection DOES change the capture (the pad drives the title into select).
//    * (b) an unfocused window accepts no input: with `--devices`, a focus-lost event
//      before the injection leaves the capture identical to the clean one, and a following
//      focus-gained event puts the run back on the injected path. The `--devices` rows are
//      also the "unknown focus means focused" case: they never receive a focus event and
//      still accept device input.
//    * `--no-devices` still means what it always meant (same capture as the clean one).
//
//  THE FIXTURE DELIBERATELY PASSES NO --local-players. That flag gives a controller with
//  no attached pad a deterministic synthetic pattern (driveSyntheticLocalPads), which
//  overwrites the slot's tick input — on a machine with no pad it would mask the very
//  device event this test injects. The issue's own recipe (`--local-players=2`) is
//  reproduced by hand in the write-up; this file needs the device slot to stay a device.
//
//  WHAT IT DOES NOT PROVE (state it, do not imply it): that a *windowed* player run reads
//  the attached pad — that is the same backend call with the gate left on, and this test
//  never creates a window or a surface. Nor does it prove anything about a real
//  compositor's focus events: the events below are SDL window events delivered through the
//  app's own handler, not a window manager's.
//
//  It needs the game install (skips itself, exit 77, without one) and a WebGPU adapter
//  (skips itself when the child cannot create one), the same contract as
//  hud_cell_scale.py / npr_experiments.py.
//
//  Usage: device_isolation_test [install-dir]      (or GAME_DIR)
// =============================================================================

#define SDL_MAIN_HANDLED 1
#include "../src/main.cpp"
#undef main

#include <chrono>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#if !defined(_WIN32)
#include <sys/wait.h>
#endif

namespace {

namespace fs = std::filesystem;

int g_checks = 0;
int g_failures = 0;

void check(bool ok, const std::string& what) {
    ++g_checks;
    std::printf("  [%s] %s\n", ok ? "ok  " : "FAIL", what.c_str());
    if (!ok) ++g_failures;
}

std::string shellQuote(const std::string& s) {
    std::string out = "'";
    for (char c : s) {
        if (c == '\'') out += "'\\''";
        else out += c;
    }
    out += "'";
    return out;
}

// std::system's return value is a wait status on POSIX and the exit code on Windows.
int exitCodeOf(int rc) {
#if !defined(_WIN32)
    return WIFEXITED(rc) ? WEXITSTATUS(rc) : -1;
#else
    return rc;
#endif
}

std::string readTextFile(const std::string& path) {
    std::ifstream f(path, std::ios::binary);
    std::ostringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

// FNV-1a 64 over the captured PPM's bytes. The assertion is byte equality; the hash is how
// a match and a mismatch are both reported without printing 230 000 bytes.
uint64_t fnv1a64(const std::vector<uint8_t>& bytes) {
    uint64_t hash = 1469598103934665603ull;
    for (uint8_t b : bytes) {
        hash ^= b;
        hash *= 1099511628211ull;
    }
    return hash;
}

std::string ladderText(const std::vector<std::string>& ladder) {
    std::string text;
    for (size_t i = 0; i < ladder.size(); ++i) text += (i ? " -> " : "") + ladder[i];
    return text.empty() ? std::string("(none)") : text;
}

void printLogTail(const std::string& log, size_t lines) {
    std::vector<std::string> all;
    std::istringstream in(log);
    std::string line;
    while (std::getline(in, line)) all.push_back(line);
    const size_t begin = all.size() > lines ? all.size() - lines : 0;
    for (size_t i = begin; i < all.size(); ++i) std::printf("        | %s\n", all[i].c_str());
}

// ---------------------------------------------------------------------------------------
// Injection spec: "<frame>:<kind>", one spec text per event, parsed identically on the
// child side so the driver cannot hand the child a spec it would not accept.
//   key:<name>  key-up:<name>            Backend::note_key (the SDL_AppEvent feed)
//   pad:<1..3>:<name>  pad-up:...        Backend::note_gamepad_button
//   push-key:<name>  push-key-up:<name>  SDL_PushEvent(KEY_*), the queue poll() harvests
//   vpad:<name>  vpad-up:<name>          the attached virtual gamepad's button, which the
//                                        backend polls with SDL_GetGamepadButton
//   focus-lost / focus-gained            SDL_AppEvent(WINDOW_FOCUS_*)
// Frame numbers are 1-based and match the demo's own --frames counter: an event scheduled
// at frame N is applied after frame N and is read by frame N+1's poll.
// ---------------------------------------------------------------------------------------
struct Injection {
    enum class Kind { Key, KeyUp, Pad, PadUp, PushKey, PushKeyUp, VirtualPad, VirtualPadUp,
                      FocusLost, FocusGained };
    int         frame = 0;
    Kind        kind = Kind::Key;
    int         player = 1;
    int         code = 0;
    std::string spec;   // the text handed to the child
};

bool keyByName(const std::string& name, int& scancode) {
    struct Entry { const char* name; SDL_Scancode code; };
    static const Entry kKeys[] = {
        {"up", SDL_SCANCODE_UP},     {"down", SDL_SCANCODE_DOWN},
        {"left", SDL_SCANCODE_LEFT}, {"right", SDL_SCANCODE_RIGHT},
        {"z", SDL_SCANCODE_Z},       {"x", SDL_SCANCODE_X},
        {"c", SDL_SCANCODE_C},       {"a", SDL_SCANCODE_A},
        {"s", SDL_SCANCODE_S},       {"d", SDL_SCANCODE_D},
        {"q", SDL_SCANCODE_Q},       {"w", SDL_SCANCODE_W},
        {"return", SDL_SCANCODE_RETURN},
    };
    for (const Entry& e : kKeys) {
        if (name == e.name) {
            scancode = (int)e.code;
            return true;
        }
    }
    return false;
}

bool padByName(const std::string& name, int& button) {
    struct Entry { const char* name; SDL_GamepadButton code; };
    static const Entry kButtons[] = {
        {"up", SDL_GAMEPAD_BUTTON_DPAD_UP},       {"down", SDL_GAMEPAD_BUTTON_DPAD_DOWN},
        {"left", SDL_GAMEPAD_BUTTON_DPAD_LEFT},   {"right", SDL_GAMEPAD_BUTTON_DPAD_RIGHT},
        {"south", SDL_GAMEPAD_BUTTON_SOUTH},      {"east", SDL_GAMEPAD_BUTTON_EAST},
        {"west", SDL_GAMEPAD_BUTTON_WEST},        {"north", SDL_GAMEPAD_BUTTON_NORTH},
        {"lb", SDL_GAMEPAD_BUTTON_LEFT_SHOULDER}, {"rb", SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER},
        {"back", SDL_GAMEPAD_BUTTON_BACK},        {"start", SDL_GAMEPAD_BUTTON_START},
    };
    for (const Entry& e : kButtons) {
        if (name == e.name) {
            button = (int)e.code;
            return true;
        }
    }
    return false;
}

std::vector<std::string> splitColon(const std::string& text) {
    std::vector<std::string> parts;
    size_t begin = 0;
    for (;;) {
        const size_t end = text.find(':', begin);
        parts.push_back(text.substr(begin, end == std::string::npos ? end : end - begin));
        if (end == std::string::npos) return parts;
        begin = end + 1;
    }
}

bool parseInjection(const std::string& text, Injection& out, std::string& error) {
    const std::vector<std::string> parts = splitColon(text);
    if (parts.size() < 2) {
        error = "--inject wants <frame>:<kind>, got '" + text + "'";
        return false;
    }
    out.frame = std::atoi(parts[0].c_str());
    if (out.frame < 1) {
        error = "--inject frame must be >= 1, got '" + parts[0] + "'";
        return false;
    }
    const std::string& kind = parts[1];
    if (kind == "focus-lost" || kind == "focus-gained") {
        out.kind = kind == "focus-lost" ? Injection::Kind::FocusLost : Injection::Kind::FocusGained;
        out.spec = text;
        return true;
    }
    if ((kind == "pad" || kind == "pad-up") && parts.size() == 4) {
        out.kind = kind == "pad" ? Injection::Kind::Pad : Injection::Kind::PadUp;
        out.player = std::atoi(parts[2].c_str());
        if (out.player < 1 || out.player >= fnd::input::kMaxPlayers ||
            !padByName(parts[3], out.code)) {
            error = "--inject pad wants <frame>:pad:<1..3>:<button>, got '" + text + "'";
            return false;
        }
        out.spec = text;
        return true;
    }
    if ((kind == "vpad" || kind == "vpad-up") && parts.size() == 3) {
        out.kind = kind == "vpad" ? Injection::Kind::VirtualPad : Injection::Kind::VirtualPadUp;
        if (!padByName(parts[2], out.code)) {
            error = "--inject " + kind + ": unknown button '" + parts[2] + "'";
            return false;
        }
        out.spec = text;
        return true;
    }
    if (((kind == "key" || kind == "key-up") || (kind == "push-key" || kind == "push-key-up")) &&
        parts.size() == 3) {
        out.kind = kind == "key"          ? Injection::Kind::Key
                   : kind == "key-up"     ? Injection::Kind::KeyUp
                   : kind == "push-key"   ? Injection::Kind::PushKey
                                          : Injection::Kind::PushKeyUp;
        if (!keyByName(parts[2], out.code)) {
            error = "--inject " + kind + ": unknown key '" + parts[2] + "'";
            return false;
        }
        out.spec = text;
        return true;
    }
    error = "--inject: unknown kind in '" + text + "'";
    return false;
}

// ---------------------------------------------------------------------------------------
// Child mode: one app run in this process, driven the way SDL drives a callbacks app.
// ---------------------------------------------------------------------------------------
std::string screenNameOf(const App& app) {
    if (!app.screensMode) return {};
    const ui::Screen* screen = app.screens.screen();
    return screen ? std::string(screen->name()) : std::string("none");
}

void recordLadder(const App& app, std::vector<std::string>& ladder) {
    const std::string name = screenNameOf(app);
    if (name.empty() || (!ladder.empty() && ladder.back() == name)) return;
    ladder.push_back(name);
}

struct InjectionContext {
    App* app = nullptr;
    SDL_Joystick* virtualPad = nullptr;   // SDL_AttachVirtualJoystick, when --virtual-pad
    SDL_JoystickID virtualPadId = 0;
};

void applyInjection(InjectionContext& context, const Injection& injection) {
    App& app = *context.app;
    switch (injection.kind) {
        case Injection::Kind::Key:
            app.matchInput.note_key(injection.code, true);
            break;
        case Injection::Kind::KeyUp:
            app.matchInput.note_key(injection.code, false);
            break;
        case Injection::Kind::Pad:
            app.matchInput.note_gamepad_button(injection.player, injection.code, true);
            break;
        case Injection::Kind::PadUp:
            app.matchInput.note_gamepad_button(injection.player, injection.code, false);
            break;
        case Injection::Kind::PushKey:
        case Injection::Kind::PushKeyUp: {
            // The real event queue. Nothing in this harness pumps events, so in a devices
            // run this is exactly the queue Backend::drain_key_events() harvests.
            SDL_Event event = {};
            event.type = injection.kind == Injection::Kind::PushKey ? SDL_EVENT_KEY_DOWN
                                                                   : SDL_EVENT_KEY_UP;
            event.key.scancode = (SDL_Scancode)injection.code;
            event.key.key =
                SDL_GetKeyFromScancode((SDL_Scancode)injection.code, SDL_KMOD_NONE, false);
            event.key.down = injection.kind == Injection::Kind::PushKey;
            if (!SDL_PushEvent(&event))
                std::fprintf(stderr, "[child] SDL_PushEvent failed: %s\n", SDL_GetError());
            break;
        }
        case Injection::Kind::VirtualPad:
        case Injection::Kind::VirtualPadUp: {
            // A device-level press: SDL's own virtual pad is a gamepad the backend opens
            // and reads with SDL_GetGamepadButton, exactly like the attached hardware. The
            // slot is resolved here because a real pad on this machine may already own
            // slot 1 and take the lowest free slot away from the virtual one.
            if (!context.virtualPad) {
                std::fprintf(stderr, "[child] vpad injection without --virtual-pad\n");
                break;
            }
            const int player = app.matchInput.gamepad_player((int32_t)context.virtualPadId);
            if (player < 0) {
                std::fprintf(stderr, "[child] the virtual pad is in no player slot yet\n");
                break;
            }
            SDL_SetJoystickVirtualButton(context.virtualPad, (SDL_GamepadButton)injection.code,
                                         injection.kind == Injection::Kind::VirtualPad);
            SDL_UpdateJoysticks();
            break;
        }
        case Injection::Kind::FocusLost:
        case Injection::Kind::FocusGained: {
            SDL_Event event = {};
            event.type = injection.kind == Injection::Kind::FocusLost
                             ? SDL_EVENT_WINDOW_FOCUS_LOST
                             : SDL_EVENT_WINDOW_FOCUS_GAINED;
            event.window.windowID = app.window ? SDL_GetWindowID(app.window) : 0;
            SDL_AppEvent(&app, &event);
            break;
        }
    }
}

// Runs one capture and writes the child status file. Exit code: 0 the run reached its
// capture frame, 1 it failed with a reason, 77 it could not start (no adapter / no install).
int runCapture(const std::vector<std::string>& appArgs, const std::vector<Injection>& injections,
               const std::string& statusPath, bool wantVirtualPad) {
    // A device-level pad, attached before the app starts so the backend opens it like any
    // other gamepad. SDL's own facility, and the only way this test can press a *device*
    // rather than feed the backend's event entry points: SDL_SetJoystickVirtualButton moves
    // what SDL_GetGamepadButton returns, which is the polling read the gate must stop.
    SDL_JoystickID virtualPadId = 0;
    SDL_Joystick* virtualPad = nullptr;
    if (wantVirtualPad) {
        if (!SDL_Init(SDL_INIT_JOYSTICK)) {
            std::fprintf(stderr, "[child] SDL_INIT_JOYSTICK failed: %s\n", SDL_GetError());
            return 77;
        }
        SDL_VirtualJoystickDesc desc{};
        SDL_INIT_INTERFACE(&desc);
        desc.type = SDL_JOYSTICK_TYPE_GAMEPAD;
        desc.nbuttons = SDL_GAMEPAD_BUTTON_COUNT;
        // Every button, not just the two this test presses: SDL derives the pad's gamepad
        // mapping from the mask, and a partial mask renumbers what the buttons mean (a
        // two-bit mask made the "down" press arrive as SOUTH and the confirm never arrive).
        desc.button_mask = (1u << SDL_GAMEPAD_BUTTON_COUNT) - 1u;
        desc.name = "device isolation virtual pad";
        virtualPadId = SDL_AttachVirtualJoystick(&desc);
        if (!virtualPadId) {
            std::fprintf(stderr, "[child] SDL_AttachVirtualJoystick failed: %s\n", SDL_GetError());
            return 1;
        }
        virtualPad = SDL_OpenJoystick(virtualPadId);
        if (!virtualPad) {
            std::fprintf(stderr, "[child] SDL_OpenJoystick failed: %s\n", SDL_GetError());
            SDL_DetachVirtualJoystick(virtualPadId);
            return 1;
        }
    }

    std::vector<std::string> args{"foundation_demo"};
    args.insert(args.end(), appArgs.begin(), appArgs.end());
    std::vector<char*> argv;
    argv.reserve(args.size() + 1);
    for (std::string& arg : args) argv.push_back(arg.data());
    argv.push_back(nullptr);

    auto writeStatus = [&](const std::string& status, const std::string& reason, int frames,
                           const std::vector<std::string>& ladder) {
        std::ofstream out(statusPath, std::ios::binary | std::ios::trunc);
        out << "status=" << status << "\n";
        out << "reason=" << reason << "\n";
        out << "frames=" << frames << "\n";
        out << "ladder=";
        for (size_t i = 0; i < ladder.size(); ++i) out << (i ? "," : "") << ladder[i];
        out << "\n";
    };

    void* state = nullptr;
    SDL_AppResult result = SDL_AppInit(&state, (int)argv.size() - 1, argv.data());
    auto* app = static_cast<App*>(state);
    if (result == SDL_APP_FAILURE) {
        const std::string reason = app ? app->error : std::string("SDL_AppInit failed");
        std::fprintf(stderr, "[child] init failed: %s\n", reason.c_str());
        writeStatus("init-failed", reason, 0, {});
        if (app) SDL_AppQuit(app, result);
        if (virtualPad) SDL_CloseJoystick(virtualPad);
        if (virtualPadId) SDL_DetachVirtualJoystick(virtualPadId);
        return 77;
    }

    InjectionContext context{app, virtualPad, virtualPadId};
    std::vector<std::string> ladder;
    int frames = 0;
    if (result == SDL_APP_CONTINUE) {
        for (;;) {
            result = SDL_AppIterate(state);
            ++frames;
            recordLadder(*app, ladder);
            if (result != SDL_APP_CONTINUE) break;
            // Injections land between frames: what frame N leaves in the backend is what
            // frame N+1's poll reads, which is how a real event arrives.
            for (const Injection& injection : injections)
                if (injection.frame == frames) applyInjection(context, injection);
        }
    }
    const std::string failure = result == SDL_APP_FAILURE ? app->error : std::string();
    SDL_AppQuit(app, result);
    if (virtualPad) SDL_CloseJoystick(virtualPad);
    if (virtualPadId) SDL_DetachVirtualJoystick(virtualPadId);
    if (result == SDL_APP_FAILURE) {
        writeStatus("failed", failure, frames, ladder);
        return 1;
    }
    writeStatus("ok", {}, frames, ladder);
    return 0;
}

// ---------------------------------------------------------------------------------------
// Driver mode: one child process per row, hashes compared.
// ---------------------------------------------------------------------------------------
struct RunResult {
    bool        initFailed = false;
    bool        failed = false;
    std::string reason;
    int         frames = 0;
    size_t      bytes = 0;
    uint64_t    hash = 0;
    std::vector<std::string> ladder;
    std::string log;

    bool producedFrame() const { return !initFailed && !failed && bytes > 0; }
};

// One row: this test binary re-invoked with --capture, the app's own argv after `--`, and
// one --inject per injected event. The child's output goes to a log file so the ctest
// transcript stays readable; the status file is the machine-readable result.
RunResult runChild(const std::string& self, const fs::path& work, const std::string& name,
                   const std::vector<std::string>& appArgs,
                   const std::vector<Injection>& injections, const fs::path& ppm,
                   bool virtualPad = false) {
    const fs::path statusPath = work / (name + ".status");
    const fs::path logPath = work / (name + ".log");
    std::string cmd = shellQuote(self) + " --capture --status=" + shellQuote(statusPath.string());
    if (virtualPad) cmd += " --virtual-pad";
    for (const Injection& injection : injections)
        cmd += " --inject=" + shellQuote(injection.spec);
    cmd += " --";
    for (const std::string& arg : appArgs) cmd += " " + shellQuote(arg);
    cmd += " > " + shellQuote(logPath.string()) + " 2>&1";

    const int rc = exitCodeOf(std::system(cmd.c_str()));

    RunResult result;
    result.log = readTextFile(logPath.string());
    std::istringstream in(readTextFile(statusPath.string()));
    std::string line;
    while (std::getline(in, line)) {
        const size_t eq = line.find('=');
        if (eq == std::string::npos) continue;
        const std::string key = line.substr(0, eq), value = line.substr(eq + 1);
        if (key == "status") {
            result.initFailed = value == "init-failed";
            result.failed = value == "failed";
        } else if (key == "reason") {
            result.reason = value;
        } else if (key == "frames") {
            result.frames = std::atoi(value.c_str());
        } else if (key == "ladder") {
            result.ladder = splitColon(value);
            if (result.ladder.size() == 1 && result.ladder[0].empty()) result.ladder.clear();
        }
    }
    if (rc == 77 && !result.initFailed && !result.failed) {
        result.initFailed = true;
        result.reason = "child exited with status 77";
    } else if (rc != 0 && !result.initFailed && !result.failed) {
        result.failed = true;
        result.reason = "child exited with status " + std::to_string(rc);
    }
    if (fs::exists(ppm)) {
        std::ifstream f(ppm, std::ios::binary);
        std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(f)),
                                   std::istreambuf_iterator<char>());
        result.bytes = bytes.size();
        result.hash = fnv1a64(bytes);
        if (bytes.size() < 4 || bytes[0] != 'P' || bytes[1] != '6') {
            result.failed = true;
            result.reason = "the capture is not a PPM";
        }
    }
    return result;
}

int driverMode(int argc, char** argv) {
    std::printf("device_isolation — issue #29: a verification capture owns its input slots\n");

    // The gate's own decision table, before anything is spawned: this is the value
    // initScreens/initMatch hand to the backend, so a player run's device cannot be
    // silently switched off by a later change to the set. It needs no install, no adapter
    // and no window, so it also runs on a CI box without the game data.
    {
        Options player;
        player.screen = "title";   // a plain front-end run, and nothing else
        check(readPhysicalDevices(player), "a plain front-end player run reads the devices");
        Options viewer = player;
        viewer.screen.clear();
        viewer.animPlayer = true;
        viewer.frames = 300;   // a bounded asset viewer is played too
        check(readPhysicalDevices(viewer), "a bounded asset viewer run reads the devices");
        struct Mode { const char* flag; void (*set)(Options&); };
        const Mode modes[] = {
            {"--out=", [](Options& o) { o.out = "/tmp/device_isolation.ppm"; }},
            {"--script=", [](Options& o) { o.script = "s.txt"; }},
            {"--script2=", [](Options& o) { o.script2 = "s.txt"; }},
            {"--headless", [](Options& o) { o.headless = true; }},
            {"--match", [](Options& o) { o.match = true; }},
            {"--versus", [](Options& o) { o.versus = true; }},
            {"--hud-test", [](Options& o) { o.hudTest = true; }},
            {"--bench=", [](Options& o) { o.bench = 10; }},
            {"--list", [](Options& o) { o.list = true; }},
        };
        for (const Mode& mode : modes) {
            Options verification = player;
            mode.set(verification);
            check(!readPhysicalDevices(verification),
                  std::string(mode.flag) + ": a verification run owns its input slots");
        }
        Options forced = player;
        forced.noDevices = true;
        check(!readPhysicalDevices(forced), "--no-devices silences a player run");
        Options optedIn = player;
        optedIn.out = "/tmp/device_isolation.ppm";
        optedIn.devices = true;
        check(readPhysicalDevices(optedIn), "--devices asks a verification run for them back");
    }
    if (g_failures != 0) {
        std::printf("\nchecks=%d failures=%d\n", g_checks, g_failures);
        std::printf("DEVICE_ISOLATION: FAIL (the gate's decision table)\n");
        return 1;
    }

    fs::path install = argc > 1 ? argv[1] : "";
    if (install.empty()) {
        if (const char* env = std::getenv("GAME_DIR"); env && *env) install = env;
    }
    if (install.empty() || !fs::exists(install / "data")) {
        std::printf("SKIP: no game install (pass <install-dir> or set GAME_DIR)\n");
        return 77;
    }
    std::printf("install: %s\n", install.string().c_str());

    const fs::path work =
        fs::temp_directory_path() /
        ("device_isolation_" +
         std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::error_code ec;
    fs::create_directories(work, ec);
    if (ec) {
        std::printf("SKIP: cannot create %s (%s)\n", work.string().c_str(), ec.message().c_str());
        return 77;
    }

    const std::string self = fs::absolute(argv[0]).string();
    // One capture shape for every row: a 200-frame title screen. No --local-players (see
    // the file header): the row that must observe a device event needs the slot to stay a
    // device, and the synthetic pad's per-tick override would replace it otherwise.
    const std::vector<std::string> captureBase{"--headless", "--install=" + install.string(),
                                               "--screen=title", "--size=320x240",
                                               "--frames=200"};

    std::string error;
    auto injection = [&](int frame, const std::string& spec) {
        Injection out;
        const std::string text = std::to_string(frame) + ":" + spec;
        if (!parseInjection(text, out, error)) {
            std::fprintf(stderr, "fixture: %s\n", error.c_str());
            std::exit(2);
        }
        return out;
    };
    // The walk the issue recorded: a direction moves the title's cursor off *versus*, a
    // confirm then takes the run into another scene. Presses are released between frames so
    // the menu sees real edges.
    const std::vector<Injection> padWalk{injection(40, "pad:1:down"), injection(44, "pad-up:1:down"),
                                         injection(60, "pad:1:east"), injection(64, "pad-up:1:east")};
    const std::vector<Injection> keyWalk{injection(40, "key:down"), injection(44, "key-up:down"),
                                         injection(60, "key:z"), injection(64, "key-up:z")};
    const std::vector<Injection> pushKeyWalk{
        injection(40, "push-key:down"), injection(44, "push-key-up:down"),
        injection(60, "push-key:z"), injection(64, "push-key-up:z")};
    // The same walk pressed on a real SDL gamepad (SDL_AttachVirtualJoystick): the backend
    // opens it in a player slot and reads it with SDL_GetGamepadButton, so this is the
    // POLLED device path rather than the app's event feed.
    const std::vector<Injection> virtualPadWalk{
        injection(40, "vpad:down"), injection(44, "vpad-up:down"),
        injection(60, "vpad:east"), injection(64, "vpad-up:east")};

    struct Row {
        std::string name;
        std::string extraArgs;
        std::vector<Injection> injections;
        bool virtualPad = false;   // attach SDL's virtual pad for this row
    };
    const std::vector<Row> rows{
        {"pad-default", "", padWalk},
        {"key-default", "", keyWalk},
        {"pushkey-default", "", pushKeyWalk},
        {"pad-no-devices", "--no-devices", padWalk},
        {"pad-devices", "--devices", padWalk},
        {"key-devices", "--devices", keyWalk},
        {"pad-focus-lost", "--devices", [&] {
             std::vector<Injection> all{injection(20, "focus-lost")};
             all.insert(all.end(), padWalk.begin(), padWalk.end());
             return all;
         }()},
        {"pad-focus-regained", "--devices", [&] {
             std::vector<Injection> all{injection(20, "focus-lost"), injection(30, "focus-gained")};
             all.insert(all.end(), padWalk.begin(), padWalk.end());
             return all;
         }()},
        {"vpad-default", "", virtualPadWalk, true},
        {"vpad-devices", "--devices", virtualPadWalk, true},
        {"vpad-focus-lost", "--devices", [&] {
             std::vector<Injection> all{injection(20, "focus-lost")};
             all.insert(all.end(), virtualPadWalk.begin(), virtualPadWalk.end());
             return all;
         }(), true},
    };

    auto capture = [&](const Row& row) {
        const fs::path ppm = work / (row.name + ".ppm");
        std::vector<std::string> args = captureBase;
        if (!row.extraArgs.empty()) args.push_back(row.extraArgs);
        args.push_back("--out=" + ppm.string());
        return runChild(self, work, row.name, args, row.injections, ppm, row.virtualPad);
    };

    const RunResult clean = capture(Row{"clean", "", {}, false});
    if (clean.initFailed) {
        std::printf("SKIP: the capture path is unavailable here (%s)\n", clean.reason.c_str());
        printLogTail(clean.log, 12);
        fs::remove_all(work, ec);
        return 77;
    }
    std::printf("  %-20s: frames=%d bytes=%zu hash=0x%016llx ladder=%s\n", "clean", clean.frames,
                clean.bytes, (unsigned long long)clean.hash, ladderText(clean.ladder).c_str());
    check(clean.producedFrame() && clean.frames == 200,
          "the clean title capture ran to its capture frame");
    check(clean.ladder == std::vector<std::string>{"title"},
          "the clean title capture stays on the title (the fixture's reference ladder)");

    std::map<std::string, RunResult> byName;
    for (const Row& row : rows) {
        RunResult run = capture(row);
        std::printf("  %-20s: frames=%d bytes=%zu hash=0x%016llx ladder=%s\n", row.name.c_str(),
                    run.frames, run.bytes, (unsigned long long)run.hash,
                    ladderText(run.ladder).c_str());
        byName.emplace(row.name, std::move(run));
    }

    // Every row's capture has to exist before its hash can mean anything; a row that did
    // not produce one is its own failure (and the log tail names the cause).
    for (const Row& row : rows) {
        const RunResult& run = byName[row.name];
        check(run.producedFrame(),
              row.name + ": the run produced a capture (" +
                  (run.reason.empty() ? std::string("no reason reported") : run.reason) + ")");
        if (!run.producedFrame()) printLogTail(run.log, 12);
    }

    // (a) A verification capture (--headless/--out=) is device-free by default: the same
    // events through the app's key feed, the pad feed and SDL's own event queue change
    // nothing. This is the issue's acceptance assertion.
    for (const char* name : {"pad-default", "key-default", "pushkey-default", "vpad-default"}) {
        const RunResult& run = byName[name];
        check(run.producedFrame() && run.hash == clean.hash,
              std::string(name) + ": injected device events did not change the frame");
        check(run.producedFrame() && run.ladder == clean.ladder,
              std::string(name) + ": injected device events did not move the menu");
    }
    // --no-devices still means what it always meant.
    check(byName["pad-no-devices"].producedFrame() &&
              byName["pad-no-devices"].hash == clean.hash &&
              byName["pad-no-devices"].ladder == clean.ladder,
          "--no-devices: injected device events did not change the frame");

    // The control rows: with --devices the very same events DO drive the run, so the
    // assertions above are about the gate and not about dead injections.
    for (const char* name : {"pad-devices", "key-devices", "vpad-devices"}) {
        const RunResult& run = byName[name];
        check(run.producedFrame() && run.hash != clean.hash,
              std::string(name) + ": the injected device events DID change the capture");
        check(run.producedFrame() && run.ladder != clean.ladder,
              std::string(name) + ": the injected device events walked the title into another scene");
    }

    // (b) An unfocused window accepts no input, and regaining focus puts the run back on
    // the injected path (unknown focus means focused, so the two --devices rows above are
    // also the "no focus event ever arrived" case).
    for (const char* name : {"pad-focus-lost", "vpad-focus-lost"}) {
        const RunResult& lost = byName[name];
        check(lost.producedFrame() && lost.hash == clean.hash && lost.ladder == clean.ladder,
              std::string(name) + ": injected device events did not change the frame");
    }
    const RunResult& regained = byName["pad-focus-regained"];
    check(regained.producedFrame() && regained.hash == byName["pad-devices"].hash &&
              regained.ladder == byName["pad-devices"].ladder,
          "focus regained: the same injected events drive the run again");

    std::printf("\nchecks=%d failures=%d\n", g_checks, g_failures);
    std::printf("DEVICE_ISOLATION: %s\n", g_failures == 0 ? "ok" : "FAIL");
    if (g_failures != 0) {
        // The failing row's own transcript is the diagnosis: it names the scene the stray
        // input reached.
        for (const auto& entry : byName) {
            const fs::path logPath = work / (entry.first + ".log");
            if (!fs::exists(logPath)) continue;
            std::printf("\n-- %s --\n", entry.first.c_str());
            printLogTail(readTextFile(logPath.string()), 10);
        }
    }
    fs::remove_all(work, ec);
    return g_failures == 0 ? 0 : 1;
}

}  // namespace

int main(int argc, char** argv) {
    if (argc > 1 && std::strcmp(argv[1], "--capture") == 0) {
        std::string statusPath;
        std::vector<Injection> injections;
        std::vector<std::string> appArgs;
        std::string error;
        bool virtualPad = false;
        bool afterSeparator = false;
        for (int i = 2; i < argc; ++i) {
            const std::string arg = argv[i];
            if (!afterSeparator && arg == "--") {
                afterSeparator = true;
            } else if (!afterSeparator && arg == "--virtual-pad") {
                virtualPad = true;
            } else if (!afterSeparator && arg.rfind("--status=", 0) == 0) {
                statusPath = arg.substr(9);
            } else if (!afterSeparator && arg.rfind("--inject=", 0) == 0) {
                Injection injection;
                if (!parseInjection(arg.substr(9), injection, error)) {
                    std::fprintf(stderr, "%s\n", error.c_str());
                    return 2;
                }
                injections.push_back(injection);
            } else {
                appArgs.push_back(arg);
            }
        }
        if (statusPath.empty()) {
            std::fprintf(stderr, "--capture needs --status=<path>\n");
            return 2;
        }
        return runCapture(appArgs, injections, statusPath, virtualPad);
    }
    return driverMode(argc, argv);
}
