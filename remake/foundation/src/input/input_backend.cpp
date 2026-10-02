// SDL3 polling backend (Track M): the device half of fnd::input.
//
// Tables stay in input_sdl3.h (SDL-free); this TU owns everything that needs
// a window, events or opened pads: key harvest, SDL_OpenGamepad hotplug,
// button/axis reads, script-file loading. Provenance for the mapping itself
// (P1 keys, 2-frame window, deadzone 8000, script format) is the remake's
// input_manager.{h,cpp} and MEDIA-INPUT.md §1, read-only.

#include "input/input_backend.h"

#include <SDL3/SDL.h>

#include <cstdio>
#include <fstream>
#include <string>

#include "input/input_sdl3.h"

// The backend reads the pinned tables, so it re-pins what it touches: a
// renumbered SDL would otherwise misbind silently instead of failing loudly.
// (Table shape — 13 slots, pad Start=6 — is pin_tables.cpp's job.)
static_assert(SDL_SCANCODE_COUNT == 512, "key-held array size drifted");
static_assert(fnd::input::sdl3::kScUp == SDL_SCANCODE_UP, "P1 up drifted");
static_assert(fnd::input::sdl3::kScDown == SDL_SCANCODE_DOWN, "P1 down drifted");
static_assert(fnd::input::sdl3::kScLeft == SDL_SCANCODE_LEFT, "P1 left drifted");
static_assert(fnd::input::sdl3::kScRight == SDL_SCANCODE_RIGHT, "P1 right drifted");
static_assert(fnd::input::sdl3::kScMelee == SDL_SCANCODE_X, "P1 melee drifted");
static_assert(fnd::input::sdl3::kScGuard == SDL_SCANCODE_D, "P1 guard drifted");
static_assert(fnd::input::sdl3::kScShoot == SDL_SCANCODE_C, "P1 shoot drifted");
static_assert(fnd::input::sdl3::kScJump == SDL_SCANCODE_Z, "P1 jump drifted");
static_assert(fnd::input::sdl3::kScSpecial == SDL_SCANCODE_S, "P1 special drifted");
static_assert(fnd::input::sdl3::kScTactics == SDL_SCANCODE_Q, "P1 tactics drifted");
static_assert(fnd::input::sdl3::kScLock == SDL_SCANCODE_A, "P1 lock drifted");
static_assert(fnd::input::sdl3::kScPause == SDL_SCANCODE_W, "P1 pause drifted");
static_assert(fnd::input::sdl3::kScCamLeft == SDL_SCANCODE_Q, "camera-left drifted");
static_assert(fnd::input::sdl3::kScCamRight == SDL_SCANCODE_E, "camera-right drifted");
static_assert(fnd::input::sdl3::kPadDpadUp == SDL_GAMEPAD_BUTTON_DPAD_UP, "pad up drifted");
static_assert(fnd::input::sdl3::kPadDpadDown == SDL_GAMEPAD_BUTTON_DPAD_DOWN, "pad down drifted");
static_assert(fnd::input::sdl3::kPadDpadLeft == SDL_GAMEPAD_BUTTON_DPAD_LEFT, "pad left drifted");
static_assert(fnd::input::sdl3::kPadDpadRight == SDL_GAMEPAD_BUTTON_DPAD_RIGHT, "pad right drifted");
static_assert(fnd::input::sdl3::kPadMelee == SDL_GAMEPAD_BUTTON_WEST, "pad melee drifted");
static_assert(fnd::input::sdl3::kPadGuard == SDL_GAMEPAD_BUTTON_SOUTH, "pad guard drifted");
static_assert(fnd::input::sdl3::kPadJump == SDL_GAMEPAD_BUTTON_EAST, "pad jump drifted");
static_assert(fnd::input::sdl3::kPadShoot == SDL_GAMEPAD_BUTTON_NORTH, "pad shoot drifted");
static_assert(fnd::input::sdl3::kPadLock == SDL_GAMEPAD_BUTTON_LEFT_SHOULDER, "pad lock drifted");
static_assert(fnd::input::sdl3::kPadSpecial == SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER, "pad special drifted");
static_assert(fnd::input::sdl3::kPadTactics == SDL_GAMEPAD_BUTTON_BACK, "pad tactics drifted");
static_assert(fnd::input::sdl3::kPadPause == SDL_GAMEPAD_BUTTON_START, "pad pause drifted");

namespace fnd::input {

namespace {
const PlayerState kEmptyPlayer;
}  // namespace

Backend::Backend() : devices_{}, pads_{}, key_held_{} {}

Backend::~Backend() { shutdown(); }

bool Backend::init() {
    if (inited_) return true;
    // Subsystem only: SDL itself (video/events) belongs to plat::init, so a
    // backend shutdown must never SDL_Quit a window it does not own.
    if (!SDL_InitSubSystem(SDL_INIT_GAMEPAD)) {
        std::fprintf(stderr, "[fnd::input] SDL_INIT_GAMEPAD failed: %s\n", SDL_GetError());
        return false;
    }
    devices_[0] = DeviceType::Keyboard;
    repoll_gamepads();
    inited_ = true;
    return true;
}

void Backend::shutdown() {
    for (int i = 0; i < kMaxPlayers; ++i) {
        if (SDL_Gamepad* pad = static_cast<SDL_Gamepad*>(pads_[i])) SDL_CloseGamepad(pad);
        pads_[i] = nullptr;
        devices_[i] = DeviceType::None;
    }
    SDL_QuitSubSystem(SDL_INIT_GAMEPAD);
    // A re-init must start clean, never holding a key the window forgot.
    for (bool& k : key_held_) k = false;
    clear_script();
    inited_ = false;
}

void Backend::poll() {
    if (!inited_) return;
    drain_key_events();
    repoll_gamepads();
    update_keyboard();
    for (int i = 1; i < kMaxPlayers; ++i) {
        if (devices_[i] == DeviceType::Gamepad) {
            update_gamepad(i);
        } else {
            // A removed (or never present) pad reads as released, not frozen:
            // clearing before edge computation turns a mid-hold removal into
            // one just_released instead of a stuck hold.
            PlayerState& p = players_[i];
            for (int a = 0; a < ActionCount; ++a) p.down[a] = false;
            p.stick_x = p.stick_y = p.stick_rx = p.stick_ry = 0;
        }
    }
    // Script replaces P0's held set wholesale inside poll() (before edges),
    // so scripted taps derive just_pressed/just_released exactly like played
    // ones — the remake's visual-validation contract.
    if (script_active_) {
        PlayerState& p = players_[0];
        for (int a = 0; a < ActionCount; ++a) p.down[a] = (script_mask_ & (1u << a)) != 0;
    }
    for (int i = 0; i < kMaxPlayers; ++i) compute_edges(players_[i]);
}

const PlayerState& Backend::player(int index) const {
    if (index < 0 || index >= kMaxPlayers) return kEmptyPlayer;
    return players_[index];
}

DeviceType Backend::device(int index) const {
    if (index < 0 || index >= kMaxPlayers) return DeviceType::None;
    return devices_[index];
}

bool Backend::any_just_pressed(Action action) const {
    for (int i = 0; i < kMaxPlayers; ++i)
        if (players_[i].just_pressed[action]) return true;
    return false;
}

bool Backend::any_down(Action action) const {
    for (int i = 0; i < kMaxPlayers; ++i)
        if (players_[i].down[action]) return true;
    return false;
}

void Backend::note_key(int scancode, bool pressed) {
    if (scancode < 0 || scancode >= kKeyHeldSize) return;
    key_held_[scancode] = pressed;
}

void Backend::note_focus_lost() {
    // A lost window drops KEY_UP on most drivers; without this the next poll
    // would read a key nobody holds anymore.
    for (bool& k : key_held_) k = false;
}

bool Backend::load_script(const char* path) {
    if (!path) return false;
    std::ifstream f(path);
    if (!f.is_open()) {
        std::fprintf(stderr, "[fnd::input] script not found: %s\n", path);
        return false;
    }
    std::vector<ScriptEvent> events;
    std::string line;
    while (std::getline(f, line)) {
        uint64_t frame = 0;
        uint32_t mask = 0;
        if (!parse_script_line(line.c_str(), frame, mask)) continue;
        events.push_back({frame, mask});
    }
    script_ = std::move(events);
    script_pos_ = 0;
    script_mask_ = 0;
    script_active_ = true;
    std::printf("[fnd::input] script: %s (%zu events)\n", path, script_.size());
    return true;
}

void Backend::tick_script(uint64_t frame) {
    if (!script_active_) return;
    // File order is frame-ascending by contract (same as the remake); the
    // last event at or before `frame` wins, so holds need no per-frame lines.
    while (script_pos_ < script_.size() && script_[script_pos_].frame <= frame) {
        script_mask_ = script_[script_pos_].mask;
        ++script_pos_;
    }
}

void Backend::clear_script() {
    script_.clear();
    script_pos_ = 0;
    script_mask_ = 0;
    script_active_ = false;
}

void Backend::repoll_gamepads() {
    // Re-polled every frame rather than wired to ADDED/REMOVED events: one
    // hotplug path means no split-brain between the event consumer (which
    // under SDL3 callbacks is SDL_AppEvent, not us) and the pad table.
    // Web note: browsers reveal pads only after a button press and only on
    // secure contexts, so zero pads before the first press is expected here,
    // not a backend failure.
    int count = 0;
    SDL_JoystickID* ids = SDL_GetGamepads(&count);
    for (int i = 1; i < kMaxPlayers; ++i) {
        SDL_Gamepad* pad = static_cast<SDL_Gamepad*>(pads_[i]);
        if (!pad) continue;
        SDL_JoystickID id = SDL_GetGamepadID(pad);
        bool gone = (id == 0);
        if (!gone && ids) {
            gone = true;
            for (int k = 0; k < count; ++k) {
                if (ids[k] == id) {
                    gone = false;
                    break;
                }
            }
        }
        if (gone) {
            SDL_CloseGamepad(pad);
            pads_[i] = nullptr;
            devices_[i] = DeviceType::None;
        }
    }
    if (ids) {
        for (int k = 0; k < count; ++k) {
            bool known = false;
            for (int i = 1; i < kMaxPlayers; ++i) {
                SDL_Gamepad* pad = static_cast<SDL_Gamepad*>(pads_[i]);
                if (pad && SDL_GetGamepadID(pad) == ids[k]) {
                    known = true;
                    break;
                }
            }
            if (known) continue;
            for (int i = 1; i < kMaxPlayers; ++i) {
                if (pads_[i]) continue;
                // A failed open keeps the slot free for the next re-poll
                // rather than burning a player on a dead pad.
                if (SDL_Gamepad* opened = SDL_OpenGamepad(ids[k])) {
                    pads_[i] = opened;
                    devices_[i] = DeviceType::Gamepad;
                }
                break;
            }
        }
        SDL_free(ids);
    }
}

void Backend::drain_key_events() {
    // Pump first: without it OS key state never reaches the queue when the
    // app has no SDL_PollEvent loop of its own (the callback demo doesn't).
    SDL_PumpEvents();
    // Consume only key events (GETEVENT removes them, which also bounds the
    // queue for apps that never SDL_PollEvent themselves). Anything else —
    // quit, resize, gamepad add/remove — stays queued for the app's own
    // event sink, and gamepad presence is covered by repoll_gamepads anyway.
    // Under SDL3 callbacks dispatched keys never sit queued, so nothing here
    // can steal SDL_AppEvent's input; that path feeds note_key directly.
    SDL_Event buf[32];
    for (;;) {
        int n = SDL_PeepEvents(buf, 32, SDL_GETEVENT, SDL_EVENT_KEY_DOWN, SDL_EVENT_KEY_UP);
        if (n <= 0) break;
        for (int i = 0; i < n; ++i)
            note_key(static_cast<int>(buf[i].key.scancode), buf[i].type == SDL_EVENT_KEY_DOWN);
    }
    // Focus loss is only observed, never consumed: the app may pause on it.
    if (SDL_PeepEvents(nullptr, 0, SDL_PEEKEVENT, SDL_EVENT_WINDOW_FOCUS_LOST,
                       SDL_EVENT_WINDOW_FOCUS_LOST) > 0)
        note_focus_lost();
}

void Backend::update_keyboard() {
    int num = 0;
    const bool* kb = SDL_GetKeyboardState(&num);
    // Either source alone drops real input: pushed/forwarded KEY events never
    // reach SDL's internal array (verified headless), while keys already down
    // at startup never produce events. Both agree on ordinary presses.
    auto key_down = [&](int sc) {
        if (sc < 0) return false;
        if (sc < kKeyHeldSize && key_held_[sc]) return true;
        return kb && sc < num && kb[sc];
    };
    PlayerState& p = players_[0];
    for (int a = 0; a < ActionCount; ++a) p.down[a] = key_down(sdl3::kP1ScancodeByAction[a]);
    // No analog source on a keyboard: sticks are synthesised from the digital
    // D-pad, verbatim from the remake.
    p.stick_x = p.down[Right] ? 32767 : (p.down[Left] ? -32768 : 0);
    p.stick_y = p.down[Down] ? 32767 : (p.down[Up] ? -32768 : 0);
    // Q is both Tactics and camera-left by construction (same scancode), E is
    // camera-right only; the orbit stick agrees with the actions by design.
    p.stick_rx = key_down(sdl3::kScCamRight) ? 32767 : (key_down(sdl3::kScCamLeft) ? -32768 : 0);
    p.stick_ry = 0;
}

void Backend::update_gamepad(int index) {
    SDL_Gamepad* pad = static_cast<SDL_Gamepad*>(pads_[index]);
    if (!pad) return;
    PlayerState& p = players_[index];
    p.down[Up] = SDL_GetGamepadButton(pad, SDL_GAMEPAD_BUTTON_DPAD_UP);
    p.down[Down] = SDL_GetGamepadButton(pad, SDL_GAMEPAD_BUTTON_DPAD_DOWN);
    p.down[Left] = SDL_GetGamepadButton(pad, SDL_GAMEPAD_BUTTON_DPAD_LEFT);
    p.down[Right] = SDL_GetGamepadButton(pad, SDL_GAMEPAD_BUTTON_DPAD_RIGHT);
    // PROVISIONAL P2-P4 map, carried over verbatim from the remake: the
    // original pads are buttons 1-8 with exact layout unknown, so this stays
    // labelled provisional until captures say otherwise. AttackB has no key
    // or button anywhere and stays exist-but-unbound.
    p.down[AttackA] = SDL_GetGamepadButton(pad, SDL_GAMEPAD_BUTTON_WEST);
    p.down[AttackB] = false;
    p.down[Guard] = SDL_GetGamepadButton(pad, SDL_GAMEPAD_BUTTON_SOUTH);
    p.down[Jump] = SDL_GetGamepadButton(pad, SDL_GAMEPAD_BUTTON_EAST);
    p.down[Shoot] = SDL_GetGamepadButton(pad, SDL_GAMEPAD_BUTTON_NORTH);
    p.down[Special] = SDL_GetGamepadButton(pad, SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER);
    p.down[LockSwitch] = SDL_GetGamepadButton(pad, SDL_GAMEPAD_BUTTON_LEFT_SHOULDER);
    p.down[Tactics] = SDL_GetGamepadButton(pad, SDL_GAMEPAD_BUTTON_BACK);
    p.down[Pause] = SDL_GetGamepadButton(pad, SDL_GAMEPAD_BUTTON_START);
    p.stick_x = SDL_GetGamepadAxis(pad, SDL_GAMEPAD_AXIS_LEFTX);
    p.stick_y = SDL_GetGamepadAxis(pad, SDL_GAMEPAD_AXIS_LEFTY);
    p.stick_rx = SDL_GetGamepadAxis(pad, SDL_GAMEPAD_AXIS_RIGHTX);
    p.stick_ry = SDL_GetGamepadAxis(pad, SDL_GAMEPAD_AXIS_RIGHTY);
    // Left-stick deflection feeds the digital directions through the shared
    // deadzone helper, so stick and D-pad agree (remake ORs them the same).
    // Web note: no rumble is wired here — the browser haptics API is async
    // and permission-gated, so it stays a future backend option, not a promise.
    stick_to_digital(p.stick_x, p.stick_y, p.down[Left], p.down[Right], p.down[Up], p.down[Down]);
}

}  // namespace fnd::input
