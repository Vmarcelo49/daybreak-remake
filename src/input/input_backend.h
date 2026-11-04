#pragma once
// SDL3 polling backend: public contract (Track M).
//
// Why a Backend class instead of free functions: the remake's InputManager
// owns the same trio (device reads, script override, edge computation) as
// one per-frame unit, and the future --input-test wiring needs exactly that
// shape (init once, tick/poll per frame). Every action is bound by default: the original
// has one melee input (issue #10).
//
// Player slots (issue #102, owner decision): no device owns a slot at start. The keyboard
// and each pad take the lowest free slot on their first press of a bound input, and that
// press acts, so whoever presses first is player 1. The keyboard has one binding set
// wherever it sits; pad bindings belong to the slot. A pad that leaves keeps its slot
// reserved for the rest of the session, so a dead battery does not hand player 1 to the
// keyboard (input/gamepad_identity.h).
//
// This header is SDL-free on purpose: the tables in input_sdl3.h test
// without SDL linked, and so does everything here (key state is tracked as
// plain scancode-indexed bools fed by note_key). The SDL3 event/pad calls
// live in input_backend.cpp, which static_asserts the table pins against
// the real headers.

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "input/gamepad_identity.h"
#include "input/input.h"
#include "input/input_sdl3.h"

namespace fnd::input {
class TickInput;

// One frame-indexed held-set, mirroring the remake's ScriptEvent.
struct ScriptEvent {
    uint64_t frame = 0;
    uint32_t mask = 0;  // bit i = Action i held
    // When set, this event does not deliver input: it HOLDS the script (keeping the
    // previous mask) until the named scene becomes current, then releases. A menu whose
    // navigation is state-dependent — the selection screen after a rematch, where a
    // time-shifted replay stalls — cannot be driven by frame offsets alone, and a fixed
    // offset that guesses wrong is worse than waiting. The caller publishes the scene
    // name; an empty name (no scene yet) matches nothing, so a wait cannot be skipped
    // by accident.
    std::string waitScene;
};

class Backend {
  public:
    Backend();
    ~Backend();
    Backend(const Backend&) = delete;
    Backend& operator=(const Backend&) = delete;

    // Opens the gamepad subsystem and re-polls pads. SDL itself must already
    // be initialised (foundation's plat::init owns that); only the gamepad
    // subsystem is taken/released here so shutdown order stays with plat.
    bool init();
    void shutdown();

    // One frame: pump OS input, absorb queued key events, re-poll hotplug, let a device's
    // first press take a slot, read every slot's device, apply the script override to P0,
    // then derive edges for every player. Live fixed-tick hosts pass false
    // and sample_script separately; the default retains capture/test callers.
    void poll(bool applyScript = true);
    void sample_tick_inputs(TickInput (&pending)[kMaxPlayers]);

    const PlayerState& player(int index) const;
    DeviceType device(int index) const;
    int gamepad_player(int32_t instanceId) const;
    bool any_just_pressed(Action action) const;
    bool any_down(Action action) const;

    // Raw keyboard state, by SDL_Scancode — the one read outside the Action map. The front
    // end's opening movie is skipped by the keys the ORIGINAL tests directly on its
    // keyboard buffer (frontend/screen_opening.h recovers them: VK_RETURN and the two Alt codes),
    // and those keys are deliberately not actions: routing them through the key-config
    // screen would let a player rebind away the only way to skip a movie, and a remapped
    // action would skip it on the wrong key. Fed by note_key like everything else, so the
    // focus gate and suppression still hold — a script or synthetic pad can never report a
    // key down here.
    bool key_down(int scancode) const {
        return scancode >= 0 && scancode < kKeyHeldSize && key_held_[scancode];
    }

    // Event feed. Under SDL3 callbacks the app forwards SDL_AppEvent keys
    // here (see docs/INPUT-BACKEND.md); under SDL_PollEvent loops poll()
    // harvests the queue itself, so forwarding is optional and idempotent.
    // `scancode` is the numeric SDL_Scancode; out-of-range values are ignored.
    void note_key(int scancode, bool pressed);
    // `player` is a slot and `button` a pad input code (input_sdl3.h, triggers included).
    void note_gamepad_button(int player, int button, bool pressed);
    // The SDL_AppEvent feed for pads, by SDL instance id. A press on a pad that has no slot
    // yet takes one, exactly as the poll would; a trigger is turned into its press/release.
    void note_pad_button(int32_t instanceId, int button, bool pressed);
    void note_pad_axis(int32_t instanceId, int axis, int value);
    // Logs a device SDL reports (SDL_EVENT_JOYSTICK_ADDED, including those present at
    // startup), saying whether SDL recognises it as a gamepad: one that is not is never
    // opened, and the log is all a player's report can show of that (issue #102).
    void note_joystick_added(int32_t instanceId) const;
    void suppress_key(int scancode);
    void suppress_gamepad_button(int player, int button);
    bool set_keyboard_binding(Action action, int scancode);
    bool set_gamepad_binding(int player, Action action, int button);
    // Focus (issue #29). Unknown focus means FOCUSED: only an explicit FOCUS_LOST arms the
    // gate, so a compositor that never delivers the event — or a run with no window at all,
    // like --headless — cannot leave the game permanently unresponsive. While unfocused the
    // device state is ignored (everything reads as released) but the device is NOT
    // relinquished: device() keeps naming it, because a --local-players slot reported empty
    // would be handed to a synthetic pad and the game would play itself.
    void note_focus_lost();   // also clears held keys (a lost window drops KEY_UP)
    void note_focus_gained();
    bool window_focused() const { return window_focused_; }

    // The pad currently in that slot: its SDL GUID string and name, "" when empty, and its
    // SDL_GamepadType, -1 when the slot holds no pad.
    std::string gamepad_guid(int player) const;
    std::string gamepad_name(int player) const;
    int gamepad_type(int player) const;

    // Deterministic driver, same line format as the remake
    // ("<frame> TOKEN...", "-" releases all, "#" comments). The override
    // replaces P0's held set wholesale inside poll(), so scripted taps get
    // real just_pressed/just_released edges. tick_script advances to `frame`
    // (1-based render index); poll applies.
    bool load_script(const char* path);
    void tick_script(uint64_t frame);
    // Advance scripts at simulation cadence without sampling SDL again.
    void sample_script(PlayerState& state, uint64_t tick);
    void clear_script();
    bool script_active() const { return script_active_; }
    // The current scene, for ScriptEvent::waitScene. main.cpp sets it once per tick
    // before sample_script so a wait sees the scene the tick is actually running.
    void set_scene_name(std::string name) { scene_name_ = std::move(name); }

  private:
    // SDL_SCANCODE_COUNT without including SDL; backend.cpp pins the equality.
    static constexpr int kKeyHeldSize = 512;

    PlayerState players_[kMaxPlayers];
    DeviceType devices_[kMaxPlayers];
    void* pads_[kMaxPlayers];  // SDL_Gamepad* when open; void* keeps SDL out
    std::vector<void*> idlePads_;   // opened, waiting for the press that gives them a slot
    int keyboardSlot_ = -1;
    std::array<std::string, kMaxPlayers> slotGuid_{};      // the pad in each slot
    std::array<std::string, kMaxPlayers> reservedGuid_{};  // a pad that left, this session
    bool triggerHeld_[kMaxPlayers][2] = {};                // the event feed's trigger state
    bool key_held_[kKeyHeldSize];
    bool inited_ = false;
    bool window_focused_ = true;   // unknown focus means focused (note_focus_lost)
    bool suppressedKeys_[kKeyHeldSize] = {};
    bool suppressedButtons_[kMaxPlayers][sdl3::kPadInputCount] = {};
    int keyboard_[ActionCount];
    int buttons_[kMaxPlayers][ActionCount];
    int32_t failedPadId_ = 0;   // the last pad SDL_OpenGamepad refused, logged once
    bool traceButtons_ = false; // DAYBREAK_INPUT_TRACE=1: log every pad button event
    struct TickSample { int player; PlayerState state; };
    std::vector<TickSample> tickSamples_;
    PlayerState eventStates_[kMaxPlayers];

    std::vector<ScriptEvent> script_;
    size_t script_pos_ = 0;
    uint32_t script_mask_ = 0;
    bool script_active_ = false;
    std::string scene_name_;

    void record_button(int player, int code, bool down);
    int claim_slot(DeviceType device, const std::string& guid);
    bool claim_keyboard(int scancode);
    void claim_idle_pads();
    void repoll_gamepads();
    void drain_key_events();
    void update_keyboard();
    void update_gamepad(int index);
    void suppress_held_devices();
    // True when physical device input must not be read: the window is unfocused. A lost
    // focus drops held keys and ignores the devices until focus returns.
    bool device_input_ignored() const { return !window_focused_; }
};

// The printed name of a pad input code (input_sdl3.h, triggers included) for the pad family
// SDL reports: A/B/X/Y and LB/RT on Xbox-style pads, CROSS/CIRCLE and L1/R2 on PlayStation,
// L/ZR on Nintendo. `gamepadType` is an SDL_GamepadType; -1 (no pad) reads as Xbox.
std::string padInputLabel(int code, int gamepadType);

}  // namespace fnd::input
