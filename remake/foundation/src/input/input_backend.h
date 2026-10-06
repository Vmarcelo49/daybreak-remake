#pragma once
// SDL3 polling backend: public contract (Track M).
//
// Why a Backend class instead of free functions: the remake's InputManager
// owns the same trio (device reads, script override, edge computation) as
// one per-frame unit, and the future --input-test wiring needs exactly that
// shape (init once, tick/poll per frame). Devices stay fixed: P0 is the
// verified keyboard layout, P1-P3 are gamepads; the original's P2-P4 pads
// were buttons 1-8 with unknown layout, so no keyboard fallback is offered
// there. Every action is bound by default: the original has one melee input (issue #10).
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

namespace fnd::input {
class TickInput;

// One frame-indexed held-set, mirroring the remake's ScriptEvent.
struct ScriptEvent {
    uint64_t frame = 0;
    uint32_t mask = 0;  // bit i = Action i held
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

    // One frame: pump OS input, absorb queued key events, re-poll hotplug,
    // read keyboard (P0) + gamepads (P1-P3), apply the script override to P0,
    // then derive edges for every player. Live fixed-tick hosts pass false
    // and sample_script separately; the default retains capture/test callers.
    void poll(bool applyScript = true);
    void sample_tick_inputs(TickInput (&pending)[kMaxPlayers]);

    const PlayerState& player(int index) const;
    DeviceType device(int index) const;
    // Device isolation (issue #29; a verification instrument, not a player feature). When
    // off: poll() stops reading the keyboard and the gamepads, the forwarded device events
    // (note_key/note_gamepad_button) are dropped, and device() reports none of them, so a
    // run is driven only by its script and by --local-players' synthetic pads. WHY it
    // exists: SDL reports a connected controller whether or not this window has focus, so
    // on a shared machine another application's pad moves this run's menus and changes its
    // captures. main.cpp turns it off for every verification run (--headless, --out=,
    // --script=, ...) unless --devices asks for the physical devices back; --no-devices
    // asks for the same thing in a run that would otherwise read them.
    void set_devices_enabled(bool enabled) { devices_enabled_ = enabled; }
    int gamepad_player(int32_t instanceId) const;
    bool any_just_pressed(Action action) const;
    bool any_down(Action action) const;

    // Event feed. Under SDL3 callbacks the app forwards SDL_AppEvent keys
    // here (see docs/INPUT-BACKEND.md); under SDL_PollEvent loops poll()
    // harvests the queue itself, so forwarding is optional and idempotent.
    // `scancode` is the numeric SDL_Scancode; out-of-range values are ignored.
    void note_key(int scancode, bool pressed);
    void note_gamepad_button(int player, int button, bool pressed);
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

    // Stable-controller identity (issue #19): the GUID recorded for each player slot.
    // A pad is opened into the slot whose hint matches its GUID when that slot is free,
    // so a replugged pad keeps its player (and its bindings) instead of taking the
    // lowest free slot. See input/gamepad_identity.h for the policy.
    void set_gamepad_guid_hint(int player, const std::string& guid);
    const std::string& gamepad_guid_hint(int player) const;
    // The pad currently in that slot: its SDL GUID string and name, "" when empty.
    std::string gamepad_guid(int player) const;
    std::string gamepad_name(int player) const;

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

  private:
    // SDL_SCANCODE_COUNT without including SDL; backend.cpp pins the equality.
    static constexpr int kKeyHeldSize = 512;

    PlayerState players_[kMaxPlayers];
    DeviceType devices_[kMaxPlayers];
    void* pads_[kMaxPlayers];  // SDL_Gamepad* when open; void* keeps SDL out
    bool key_held_[kKeyHeldSize];
    bool inited_ = false;
    bool devices_enabled_ = true;
    bool window_focused_ = true;   // unknown focus means focused (note_focus_lost)
    bool suppressedKeys_[kKeyHeldSize] = {};
    bool suppressedButtons_[kMaxPlayers][26] = {};
    int keyboard_[ActionCount];
    int buttons_[kMaxPlayers][ActionCount];
    std::array<std::string, kMaxPlayers> guidHints_{};
    struct TickSample { int player; PlayerState state; };
    std::vector<TickSample> tickSamples_;
    PlayerState eventStates_[kMaxPlayers];

    std::vector<ScriptEvent> script_;
    size_t script_pos_ = 0;
    uint32_t script_mask_ = 0;
    bool script_active_ = false;

    void record_button(int player, int code, bool down);
    void repoll_gamepads();
    void drain_key_events();
    void update_keyboard();
    void update_gamepad(int index);
    void suppress_held_devices();
    // True when physical device input must not be read: the run owns every slot
    // (set_devices_enabled(false)) or the window is unfocused.
    bool device_input_ignored() const { return !devices_enabled_ || !window_focused_; }
};

}  // namespace fnd::input
