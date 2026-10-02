#pragma once
// SDL3 polling backend: public contract (Track M).
//
// Why a Backend class instead of free functions: the remake's InputManager
// owns the same trio (device reads, script override, edge computation) as
// one per-frame unit, and the future --input-test wiring needs exactly that
// shape (init once, tick/poll per frame). Devices stay fixed: P0 is the
// verified keyboard layout, P1-P3 are gamepads; the original's P2-P4 pads
// were buttons 1-8 with unknown layout, so no keyboard fallback is offered
// there and unbound AttackB stays unbound.
//
// This header is SDL-free on purpose: the tables in input_sdl3.h test
// without SDL linked, and so does everything here (key state is tracked as
// plain scancode-indexed bools fed by note_key). The SDL3 event/pad calls
// live in input_backend.cpp, which static_asserts the table pins against
// the real headers.

#include <cstddef>
#include <cstdint>
#include <vector>

#include "input/input.h"

namespace fnd::input {

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
    // then derive edges for every player. Call before the scene update.
    void poll();

    const PlayerState& player(int index) const;
    DeviceType device(int index) const;
    bool any_just_pressed(Action action) const;
    bool any_down(Action action) const;

    // Event feed. Under SDL3 callbacks the app forwards SDL_AppEvent keys
    // here (see docs/INPUT-BACKEND.md); under SDL_PollEvent loops poll()
    // harvests the queue itself, so forwarding is optional and idempotent.
    // `scancode` is the numeric SDL_Scancode; out-of-range values are ignored.
    void note_key(int scancode, bool pressed);
    void note_focus_lost();  // clears held keys (a lost window drops KEY_UP)

    // Deterministic driver, same line format as the remake
    // ("<frame> TOKEN...", "-" releases all, "#" comments). The override
    // replaces P0's held set wholesale inside poll(), so scripted taps get
    // real just_pressed/just_released edges. tick_script advances to `frame`
    // (1-based render index); poll applies.
    bool load_script(const char* path);
    void tick_script(uint64_t frame);
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

    std::vector<ScriptEvent> script_;
    size_t script_pos_ = 0;
    uint32_t script_mask_ = 0;
    bool script_active_ = false;

    void repoll_gamepads();
    void drain_key_events();
    void update_keyboard();
    void update_gamepad(int index);
};

}  // namespace fnd::input
