// SDL3 polling backend (Track M): the device half of fnd::input.
//
// Tables stay in input_sdl3.h (SDL-free); this TU owns everything that needs
// a window, events or opened pads: key harvest, SDL_OpenGamepad hotplug,
// button/axis reads, script-file loading. Provenance for the mapping itself
// (P1 keys, 2-frame window, deadzone 8000, script format) is the remake's
// input_manager.{h,cpp} and MEDIA-INPUT.md §1, read-only.

#include "input/input_backend.h"
#include "input/tick_input.h"

#include <SDL3/SDL.h>

#include <array>
#include <cstdio>
#include <cstdlib>
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
static_assert(fnd::input::sdl3::kPadButtonCount == SDL_GAMEPAD_BUTTON_COUNT,
              "the trigger codes must sit past the last SDL button");
static_assert(fnd::input::sdl3::kPadPause == SDL_GAMEPAD_BUTTON_START, "pad pause drifted");

namespace fnd::input {

namespace {
const PlayerState kEmptyPlayer;

// The pad's identity string: SDL's 32-hex-character GUID. Empty when the id is not a
// pad (or SDL cannot say), which the slot policy reads as "no identity".
std::string guidStringForId(SDL_JoystickID id) {
    const SDL_GUID guid = SDL_GetGamepadGUIDForID(id);
    char text[64] = {};
    SDL_GUIDToString(guid, text, sizeof text);
    return std::string(text);
}

// A pad input code is down: a button, or a trigger past half travel.
bool padInputDown(SDL_Gamepad* pad, int code) {
    if (!pad || code < 0) return false;
    if (code < sdl3::kPadButtonCount) return SDL_GetGamepadButton(pad, static_cast<SDL_GamepadButton>(code));
    if (code == sdl3::kPadLeftTrigger)
        return SDL_GetGamepadAxis(pad, SDL_GAMEPAD_AXIS_LEFT_TRIGGER) >= sdl3::kPadTriggerThreshold;
    if (code == sdl3::kPadRightTrigger)
        return SDL_GetGamepadAxis(pad, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER) >= sdl3::kPadTriggerThreshold;
    return false;
}
}  // namespace

Backend::Backend() : devices_{}, pads_{}, key_held_{} {
    for (int a = 0; a < ActionCount; ++a) {
        keyboard_[a] = sdl3::kP1ScancodeByAction[a];
        for (auto& row : buttons_) row[a] = sdl3::kPadButtonByAction[a];
    }
}

bool Backend::set_keyboard_binding(Action action, int scancode) {
    if (action < 0 || action >= ActionCount || scancode < -1 || scancode >= kKeyHeldSize) return false;
    keyboard_[action] = scancode;
    return true;
}

bool Backend::set_gamepad_binding(int player, Action action, int button) {
    if (player < 0 || player >= kMaxPlayers || action < 0 || action >= ActionCount ||
        button < -1 || button >= sdl3::kPadInputCount) return false;
    buttons_[player][action] = button;
    return true;
}

std::string Backend::gamepad_guid(int player) const {
    if (player < 0 || player >= kMaxPlayers) return {};
    auto* pad = static_cast<SDL_Gamepad*>(pads_[player]);
    if (!pad) return {};
    return guidStringForId(SDL_GetGamepadID(pad));
}

std::string Backend::gamepad_name(int player) const {
    if (player < 0 || player >= kMaxPlayers) return {};
    auto* pad = static_cast<SDL_Gamepad*>(pads_[player]);
    if (!pad) return {};
    const char* name = SDL_GetGamepadName(pad);
    return name ? std::string(name) : std::string();
}

int Backend::gamepad_type(int player) const {
    if (player < 0 || player >= kMaxPlayers || !pads_[player]) return -1;
    return static_cast<int>(SDL_GetGamepadType(static_cast<SDL_Gamepad*>(pads_[player])));
}

Backend::~Backend() { shutdown(); }

bool Backend::init() {
    if (inited_) return true;
    // Subsystem only: SDL itself (video/events) belongs to plat::init, so a
    // backend shutdown must never SDL_Quit a window it does not own.
    if (!SDL_InitSubSystem(SDL_INIT_GAMEPAD)) {
        std::fprintf(stderr, "[fnd::input] SDL_INIT_GAMEPAD failed: %s\n", SDL_GetError());
        return false;
    }
    const char* trace = std::getenv("DAYBREAK_INPUT_TRACE");
    traceButtons_ = trace && trace[0] == '1';
    const int version = SDL_GetVersion();
    std::printf("[fnd::input] SDL %d.%d.%d, gamepad subsystem up\n", SDL_VERSIONNUM_MAJOR(version),
                SDL_VERSIONNUM_MINOR(version), SDL_VERSIONNUM_MICRO(version));
    repoll_gamepads();
    inited_ = true;
    return true;
}

void Backend::shutdown() {
    for (int i = 0; i < kMaxPlayers; ++i) {
        if (SDL_Gamepad* pad = static_cast<SDL_Gamepad*>(pads_[i])) SDL_CloseGamepad(pad);
        pads_[i] = nullptr;
        devices_[i] = DeviceType::None;
        slotGuid_[i].clear();
        reservedGuid_[i].clear();
        triggerHeld_[i][0] = triggerHeld_[i][1] = false;
    }
    for (void* pad : idlePads_) SDL_CloseGamepad(static_cast<SDL_Gamepad*>(pad));
    idlePads_.clear();
    keyboardSlot_ = -1;
    SDL_QuitSubSystem(SDL_INIT_GAMEPAD);
    // A re-init must start clean, never holding a key the window forgot — and never
    // remembering a focus loss it was not there for.
    for (bool& k : key_held_) k = false;
    window_focused_ = true;
    for (bool& k : suppressedKeys_) k = false;
    for (auto& player : suppressedButtons_) for (bool& button : player) button = false;
    clear_script();
    tickSamples_.clear();
    for (auto& state : eventStates_) state = {};
    inited_ = false;
}

void Backend::poll(bool applyScript) {
    if (!inited_) return;
    if (!device_input_ignored()) {
        drain_key_events();
        repoll_gamepads();
        claim_idle_pads();
        update_keyboard();
        for (int i = 0; i < kMaxPlayers; ++i) {
            if (devices_[i] == DeviceType::Gamepad) {
                update_gamepad(i);
            } else if (devices_[i] == DeviceType::None) {
                // A removed (or never present) device reads as released, not frozen:
                // clearing before edge computation turns a mid-hold removal into
                // one just_released instead of a stuck hold.
                PlayerState& p = players_[i];
                for (int a = 0; a < ActionCount; ++a) p.down[a] = false;
                p.stick_x = p.stick_y = p.stick_rx = p.stick_ry = 0;
            }
        }
    } else {
        // Device input ignored: the window is unfocused. Reading a physical device here is
        // what makes a capture depend on whoever is holding a pad: SDL reports a connected
        // controller whether or not this window has focus, so a second game on the same
        // machine moves this run's menus. Every slot reads as released; nothing rejoins the
        // game until released and pressed afresh (see note_focus_lost).
        for (int i = 0; i < kMaxPlayers; ++i) {
            PlayerState& p = players_[i];
            for (int a = 0; a < ActionCount; ++a) p.down[a] = false;
            p.stick_x = p.stick_y = p.stick_rx = p.stick_ry = 0;
        }
    }
    // Script replaces P0's held set wholesale inside poll() (before edges),
    // so scripted taps derive just_pressed/just_released exactly like played
    // ones — the remake's visual-validation contract.
    if (script_active_ && applyScript) {
        PlayerState& p = players_[0];
        for (int a = 0; a < ActionCount; ++a) p.down[a] = (script_mask_ & (1u << a)) != 0;
    }
    for (int i = 0; i < kMaxPlayers; ++i) {
        compute_edges(players_[i]);
        eventStates_[i] = players_[i];
    }
    if (applyScript) tickSamples_.clear();
}

void Backend::sample_tick_inputs(TickInput (&pending)[kMaxPlayers]) {
    // KEY_DOWN/UP can both arrive during a stalled render. A held-state poll
    // alone erases the tap; queue event snapshots before the final device state.
    for (const auto& sample : tickSamples_) pending[sample.player].sample(sample.state);
    tickSamples_.clear();
    for (int i = 0; i < kMaxPlayers; ++i) pending[i].sample(players_[i]);
}

const PlayerState& Backend::player(int index) const {
    if (index < 0 || index >= kMaxPlayers) return kEmptyPlayer;
    return players_[index];
}

DeviceType Backend::device(int index) const {
    if (index < 0 || index >= kMaxPlayers) return DeviceType::None;
    // The focus gate does not blank the slot: an unfocused window still names the pad it
    // has, because a slot reported empty would be handed to the synthetic pad and the game
    // would play itself.
    return devices_[index];
}

int Backend::gamepad_player(int32_t instanceId) const {
    for (int p = 0; p < kMaxPlayers; ++p)
        if (pads_[p] && SDL_GetGamepadID(static_cast<SDL_Gamepad*>(pads_[p])) == (SDL_JoystickID)instanceId)
            return p;
    return -1;
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

int Backend::claim_slot(DeviceType device, const std::string& guid) {
    std::array<bool, kMaxPlayers> occupied{};
    for (int i = 0; i < kMaxPlayers; ++i) occupied[i] = devices_[i] != DeviceType::None;
    const int slot = slotForNewDevice(reservedGuid_, occupied, guid);
    if (slot < 0) return -1;
    devices_[slot] = device;
    slotGuid_[slot] = guid;
    reservedGuid_[slot].clear();
    triggerHeld_[slot][0] = triggerHeld_[slot][1] = false;
    eventStates_[slot] = players_[slot] = {};
    return slot;
}

// The keyboard joins on a key bound to an action; Escape, Enter and the like do not make it
// a player.
bool Backend::claim_keyboard(int scancode) {
    if (keyboardSlot_ >= 0) return true;
    bool bound = false;
    for (int a = 0; a < ActionCount; ++a) bound = bound || keyboard_[a] == scancode;
    if (!bound) return false;
    keyboardSlot_ = claim_slot(DeviceType::Keyboard, {});
    if (keyboardSlot_ >= 0) std::printf("[fnd::input] keyboard is player %d\n", keyboardSlot_ + 1);
    return keyboardSlot_ >= 0;
}

void Backend::claim_idle_pads() {
    for (size_t k = 0; k < idlePads_.size();) {
        auto* pad = static_cast<SDL_Gamepad*>(idlePads_[k]);
        const std::string guid = guidStringForId(SDL_GetGamepadID(pad));
        std::array<bool, kMaxPlayers> occupied{};
        for (int i = 0; i < kMaxPlayers; ++i) occupied[i] = devices_[i] != DeviceType::None;
        const int target = slotForNewDevice(reservedGuid_, occupied, guid);
        bool pressed = false;
        for (int a = 0; target >= 0 && a < ActionCount; ++a)
            pressed = pressed || padInputDown(pad, buttons_[target][a]);
        if (!pressed) {
            ++k;
            continue;
        }
        const int slot = claim_slot(DeviceType::Gamepad, guid);
        pads_[slot] = pad;
        idlePads_.erase(idlePads_.begin() + static_cast<std::ptrdiff_t>(k));
        const char* name = SDL_GetGamepadName(pad);
        std::printf("[fnd::input] pad \"%s\" is player %d\n", name ? name : "?", slot + 1);
    }
}

void Backend::note_key(int scancode, bool pressed) {
    if (scancode < 0 || scancode >= kKeyHeldSize) return;
    // The forwarded DEVICE events obey the same gate as the polling read: an ignored run
    // cannot be entered through SDL_AppEvent either. A release is dropped too, which only
    // ever re-arms a suppression; note_focus_gained re-derives that snapshot from the
    // physical state, so a key let go while unfocused is not left stuck suppressed.
    if (device_input_ignored()) return;
    key_held_[scancode] = pressed;
    if (!pressed) suppressedKeys_[scancode] = false;
    if (keyboardSlot_ < 0 && !(pressed && !suppressedKeys_[scancode] && claim_keyboard(scancode))) return;
    record_button(keyboardSlot_, scancode, pressed && !suppressedKeys_[scancode]);
}

void Backend::note_gamepad_button(int player, int button, bool pressed) {
    if (player < 0 || player >= kMaxPlayers || button < 0 || button >= sdl3::kPadInputCount) return;
    if (device_input_ignored()) return;   // same gate as note_key
    if (!pressed) suppressedButtons_[player][button] = false;
    record_button(player, button, pressed && !suppressedButtons_[player][button]);
}

void Backend::note_pad_button(int32_t instanceId, int button, bool pressed) {
    int player = gamepad_player(instanceId);
    if (player < 0 && pressed && !device_input_ignored()) {
        // The poll's claim, early: the press that joins a pad is the one that acts, even
        // when it is released before the next poll.
        for (void* pad : idlePads_)
            if (SDL_GetGamepadID(static_cast<SDL_Gamepad*>(pad)) == (SDL_JoystickID)instanceId) {
                claim_idle_pads();
                player = gamepad_player(instanceId);
                break;
            }
    }
    if (traceButtons_)
        std::printf("[fnd::input] pad %d button %d %s, player %d%s\n", instanceId, button,
                    pressed ? "down" : "up", player + 1,
                    device_input_ignored() ? " (window unfocused, ignored)" : "");
    note_gamepad_button(player, button, pressed);
}

void Backend::note_pad_axis(int32_t instanceId, int axis, int value) {
    const int trigger = axis == SDL_GAMEPAD_AXIS_LEFT_TRIGGER    ? 0
                        : axis == SDL_GAMEPAD_AXIS_RIGHT_TRIGGER ? 1
                                                                 : -1;
    const int player = gamepad_player(instanceId);
    if (trigger < 0 || player < 0) return;   // a pad with no slot joins through the poll
    const bool down = value >= sdl3::kPadTriggerThreshold;
    if (triggerHeld_[player][trigger] == down) return;
    triggerHeld_[player][trigger] = down;
    note_pad_button(instanceId, trigger == 0 ? sdl3::kPadLeftTrigger : sdl3::kPadRightTrigger, down);
}

void Backend::note_joystick_added(int32_t instanceId) const {
    const SDL_JoystickID id = static_cast<SDL_JoystickID>(instanceId);
    const char* name = SDL_GetJoystickNameForID(id);
    char guid[64] = {};
    SDL_GUIDToString(SDL_GetJoystickGUIDForID(id), guid, sizeof guid);
    std::printf("[fnd::input] device %u connected: \"%s\" guid %s, %s\n", (unsigned)id,
                name ? name : "?", guid,
                SDL_IsGamepad(id) ? "a gamepad" : "not a gamepad (no mapping), ignored");
}

void Backend::record_button(int player, int code, bool down) {
    PlayerState& state = eventStates_[player];
    const bool keyboard = devices_[player] == DeviceType::Keyboard;
    const int* bindings = keyboard ? keyboard_ : buttons_[player];
    bool changed = false;
    for (int a = 0; a < ActionCount; ++a) {
        if (bindings[a] != code) continue;
        changed = changed || state.down[a] != down;
        state.down[a] = down;
    }
    if (keyboard) {
        state.stick_x = state.down[Right] ? 32767 : (state.down[Left] ? -32768 : 0);
        state.stick_y = state.down[Down] ? 32767 : (state.down[Up] ? -32768 : 0);
    } else {
        stick_to_digital(state.stick_x, state.stick_y, state.down[Left], state.down[Right],
                         state.down[Up], state.down[Down]);
    }
    if (changed) tickSamples_.push_back({player, state});
}

void Backend::suppress_key(int scancode) {
    if (scancode >= 0 && scancode < kKeyHeldSize) suppressedKeys_[scancode] = true;
}

void Backend::suppress_gamepad_button(int player, int button) {
    if (player >= 0 && player < kMaxPlayers && button >= 0 && button < sdl3::kPadInputCount)
        suppressedButtons_[player][button] = true;
}

// Everything held on a physical device right now must be released before it can act in
// the game again. Used at focus loss, and again at focus gain: releases that happened while
// the window was unfocused were never delivered, so a snapshot taken at focus loss can name
// a key or button the player has already let go.
void Backend::suppress_held_devices() {
    int count = 0;
    const bool* keys = SDL_GetKeyboardState(&count);
    for (int sc = 0; sc < kKeyHeldSize; ++sc)
        suppressedKeys_[sc] = keys && sc < count && keys[sc];
    // Pads continue reporting physical holds after the window loses focus.
    for (int p = 0; p < kMaxPlayers; ++p) {
        auto* pad = static_cast<SDL_Gamepad*>(pads_[p]);
        for (int b = 0; b < sdl3::kPadInputCount; ++b) suppressedButtons_[p][b] = padInputDown(pad, b);
    }
}

void Backend::note_focus_lost() {
    window_focused_ = false;
    // A lost window drops KEY_UP on most drivers; without this the next poll
    // would read a key nobody holds anymore.
    for (bool& k : key_held_) k = false;
    suppress_held_devices();
    for (int p = 0; p < kMaxPlayers; ++p) {
        eventStates_[p] = {};
        tickSamples_.push_back({p, eventStates_[p]});
    }
}

void Backend::note_focus_gained() {
    window_focused_ = true;
    suppress_held_devices();
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
        std::string waitScene;
        if (!parse_script_line(line.c_str(), frame, mask, waitScene)) continue;
        ScriptEvent event;
        event.frame = frame;
        event.mask = mask;
        event.waitScene = std::move(waitScene);
        events.push_back(std::move(event));
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
    // File order is frame-ascending by contract (same as the remake); the last event at
    // or before `frame` wins, so holds need no per-frame lines. A WAIT event is
    // different: it is reached at its frame and then HOLDS the script until its scene is
    // current, leaving the previous mask in place (a release, not a press). It is
    // consumed only once the scene matches, so a wait cannot be stepped over.
    while (script_pos_ < script_.size()) {
        const ScriptEvent& event = script_[script_pos_];
        if (!event.waitScene.empty()) {
            if (event.frame > frame) break;
            if (scene_name_ != event.waitScene) return;
            ++script_pos_;
            continue;
        }
        if (event.frame > frame) break;
        script_mask_ = event.mask;
        ++script_pos_;
    }
}

void Backend::sample_script(PlayerState& state, uint64_t tick) {
    tick_script(tick);
    for (int a = 0; a < ActionCount; ++a) state.down[a] = (script_mask_ & (1u << a)) != 0;
    // Scripted intent must not inherit a physical device's analog deflection.
    state.stick_x = state.stick_y = state.stick_rx = state.stick_ry = 0;
    compute_edges(state);
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
    const auto connected = [&](SDL_Gamepad* pad) {
        const SDL_JoystickID id = SDL_GetGamepadID(pad);
        if (id == 0) return false;
        if (!ids) return true;
        for (int k = 0; k < count; ++k)
            if (ids[k] == id) return true;
        return false;
    };
    for (int i = 0; i < kMaxPlayers; ++i) {
        SDL_Gamepad* pad = static_cast<SDL_Gamepad*>(pads_[i]);
        if (!pad || connected(pad)) continue;
        std::printf("[fnd::input] pad left player %d; the slot waits for it\n", i + 1);
        SDL_CloseGamepad(pad);
        pads_[i] = nullptr;
        devices_[i] = DeviceType::None;
        reservedGuid_[i] = slotGuid_[i];
        slotGuid_[i].clear();
    }
    for (size_t k = 0; k < idlePads_.size();) {
        auto* pad = static_cast<SDL_Gamepad*>(idlePads_[k]);
        if (connected(pad)) {
            ++k;
            continue;
        }
        SDL_CloseGamepad(pad);
        idlePads_.erase(idlePads_.begin() + static_cast<std::ptrdiff_t>(k));
    }
    if (ids) {
        for (int k = 0; k < count; ++k) {
            bool known = gamepad_player(ids[k]) >= 0;
            for (void* pad : idlePads_)
                known = known || SDL_GetGamepadID(static_cast<SDL_Gamepad*>(pad)) == ids[k];
            if (known) continue;
            // A failed open is retried on the next re-poll rather than burning a player on
            // a dead pad; its reason is logged once.
            if (SDL_Gamepad* opened = SDL_OpenGamepad(ids[k])) {
                idlePads_.push_back(opened);
                const char* name = SDL_GetGamepadName(opened);
                std::printf("[fnd::input] pad \"%s\" ready; its first press takes a player\n",
                            name ? name : "?");
            } else if (failedPadId_ != static_cast<int32_t>(ids[k])) {
                failedPadId_ = static_cast<int32_t>(ids[k]);
                std::printf("[fnd::input] pad %u could not be opened: %s\n", (unsigned)ids[k],
                            SDL_GetError());
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
        if (sc < 0 || (sc < kKeyHeldSize && suppressedKeys_[sc])) return false;
        if (sc < kKeyHeldSize && key_held_[sc]) return true;
        return kb && sc < num && kb[sc];
    };
    if (keyboardSlot_ < 0) {
        for (int a = 0; a < ActionCount && keyboardSlot_ < 0; ++a)
            if (key_down(keyboard_[a])) claim_keyboard(keyboard_[a]);
        if (keyboardSlot_ < 0) return;
    }
    PlayerState& p = players_[keyboardSlot_];
    for (int a = 0; a < ActionCount; ++a) p.down[a] = key_down(keyboard_[a]);
    // No analog source on a keyboard: sticks are synthesised from the digital
    // D-pad, verbatim from the remake.
    p.stick_x = p.down[Right] ? 32767 : (p.down[Left] ? -32768 : 0);
    p.stick_y = p.down[Down] ? 32767 : (p.down[Up] ? -32768 : 0);
    // Camera nudges retain Q/E independently of configurable action bindings.
    p.stick_rx = key_down(sdl3::kScCamRight) ? 32767 : (key_down(sdl3::kScCamLeft) ? -32768 : 0);
    p.stick_ry = 0;
}

void Backend::update_gamepad(int index) {
    SDL_Gamepad* pad = static_cast<SDL_Gamepad*>(pads_[index]);
    if (!pad) return;
    PlayerState& p = players_[index];
    for (int a = 0; a < ActionCount; ++a) {
        const int b = buttons_[index][a];
        const bool pressed = padInputDown(pad, b);
        if (b >= 0 && !pressed) suppressedButtons_[index][b] = false;
        p.down[a] = pressed && !suppressedButtons_[index][b];
    }
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

std::string padInputLabel(int code, int gamepadType) {
    if (code < 0) return "--";
    const auto type = static_cast<SDL_GamepadType>(gamepadType);
    const bool playstation = type == SDL_GAMEPAD_TYPE_PS3 || type == SDL_GAMEPAD_TYPE_PS4 ||
                             type == SDL_GAMEPAD_TYPE_PS5;
    const bool nintendo = type == SDL_GAMEPAD_TYPE_NINTENDO_SWITCH_PRO ||
                          type == SDL_GAMEPAD_TYPE_NINTENDO_SWITCH_JOYCON_LEFT ||
                          type == SDL_GAMEPAD_TYPE_NINTENDO_SWITCH_JOYCON_RIGHT ||
                          type == SDL_GAMEPAD_TYPE_NINTENDO_SWITCH_JOYCON_PAIR;
    // Face buttons are positional in SDL; the printed label is the pad family's.
    if (code <= SDL_GAMEPAD_BUTTON_NORTH) {
        switch (SDL_GetGamepadButtonLabelForType(type, static_cast<SDL_GamepadButton>(code))) {
        case SDL_GAMEPAD_BUTTON_LABEL_A: return "A";
        case SDL_GAMEPAD_BUTTON_LABEL_B: return "B";
        case SDL_GAMEPAD_BUTTON_LABEL_X: return "X";
        case SDL_GAMEPAD_BUTTON_LABEL_Y: return "Y";
        case SDL_GAMEPAD_BUTTON_LABEL_CROSS: return "CROSS";
        case SDL_GAMEPAD_BUTTON_LABEL_CIRCLE: return "CIRCLE";
        case SDL_GAMEPAD_BUTTON_LABEL_SQUARE: return "SQUARE";
        case SDL_GAMEPAD_BUTTON_LABEL_TRIANGLE: return "TRIANGLE";
        default: break;
        }
    }
    const char* shoulders[4] = {"LB", "RB", "LT", "RT"};
    if (playstation) shoulders[0] = "L1", shoulders[1] = "R1", shoulders[2] = "L2", shoulders[3] = "R2";
    if (nintendo) shoulders[0] = "L", shoulders[1] = "R", shoulders[2] = "ZL", shoulders[3] = "ZR";
    switch (code) {
    case SDL_GAMEPAD_BUTTON_SOUTH: return "A";
    case SDL_GAMEPAD_BUTTON_EAST: return "B";
    case SDL_GAMEPAD_BUTTON_WEST: return "X";
    case SDL_GAMEPAD_BUTTON_NORTH: return "Y";
    case SDL_GAMEPAD_BUTTON_BACK: return playstation ? (type == SDL_GAMEPAD_TYPE_PS5 ? "CREATE" : "SHARE")
                                         : nintendo  ? "-" : "BACK";
    case SDL_GAMEPAD_BUTTON_GUIDE: return playstation ? "PS" : "HOME";
    case SDL_GAMEPAD_BUTTON_START: return playstation ? "OPTIONS" : nintendo ? "+" : "START";
    case SDL_GAMEPAD_BUTTON_LEFT_STICK: return playstation ? "L3" : "LS";
    case SDL_GAMEPAD_BUTTON_RIGHT_STICK: return playstation ? "R3" : "RS";
    case SDL_GAMEPAD_BUTTON_LEFT_SHOULDER: return shoulders[0];
    case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER: return shoulders[1];
    case sdl3::kPadLeftTrigger: return shoulders[2];
    case sdl3::kPadRightTrigger: return shoulders[3];
    case SDL_GAMEPAD_BUTTON_DPAD_UP: return "UP";
    case SDL_GAMEPAD_BUTTON_DPAD_DOWN: return "DOWN";
    case SDL_GAMEPAD_BUTTON_DPAD_LEFT: return "LEFT";
    case SDL_GAMEPAD_BUTTON_DPAD_RIGHT: return "RIGHT";
    case SDL_GAMEPAD_BUTTON_TOUCHPAD: return "TOUCHPAD";
    default: return "#" + std::to_string(code);
    }
}

}  // namespace fnd::input
