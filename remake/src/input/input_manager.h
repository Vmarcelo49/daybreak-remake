// =============================================================================
//  input_manager.h — 4-player input system mirroring the original game.
//
//  RE findings (docs/reverse-engineering.md):
//    - The game supports 4 players (loop "for i = 0..3" in fcn.00634f60)
//    - Each player has 7 action slots (loop "for j = 0..6" checking +0x280)
//    - Device type at +0x29c (1=keyboard, 2=joystick)
//    - Per-player timers at +0x828/+0x82c (just-pressed / just-released frames)
//    - DirectInput8Create with version 0x800
//
//  We use SDL2 instead of DirectInput8 directly (SDL2 abstracts both keyboard
//  and gamepad). The 4-player structure mirrors the original; the action
//  model is our own (below), verified against the controller-setup capture
//  (remake/docs/reference/controller-setup.webp). The original's internal
//  7-slot polling loop is deliberately NOT mirrored.
//
//  "Target switch" is the dedicated LockSwitch action (tap = cycle enemy,
//  hold = aim ally -- matches the original's A key). ArenaCamera still also
//  accepts its legacy Guard-tap/Q-E stand-ins until scenes migrate fully.
// =============================================================================
#pragma once

#include <cstdint>

#include <SDL.h>

namespace daybreak::input {

//  Action model (redesigned 2026-10-01 from ground truth —
//  remake/docs/reference/controller-setup.webp). The original's internal
//  7-slot polling loop is deliberately NOT mirrored: this is a remake,
//  so we model the 11 verified player functions + pause directly.
//  Authoritative P1 layout: arrows + Z jump/confirm, X melee/cancel,
//  C shoot, A lock-switch, S special, D guard, Q tactics, W pause;
//  P2–P4 use pads (buttons 1–8, exact map unknown).
enum Action : int {
    Up      = 0,
    Down    = 1,
    Left    = 2,
    Right   = 3,
    AttackA = 4,  // melee (X) — feeds FighterState::AttackA
    AttackB = 5,  // heavy stand-in, UNBOUND by default (no dedicated key
                  // exists; real game uses directional variants — TODO)
    Guard   = 6,  // block (D)
    Shoot   = 7,  // projectile (C)
    Jump    = 8,  // jump, hold = fly (Z); doubles as menu confirm
    Special = 9,  // special attack (S)
    Tactics = 10, // team tactics (Q) — behavior unmodeled, TODO
    LockSwitch = 11, // target switch, hold = aim ally (A)
    Pause   = 12, // pause (W)
    ActionCount = 13,
};

enum class DeviceType : int {
    None     = 0,
    Keyboard = 1,
    Gamepad  = 2,
};

// Per-player input state.  Mirrors the original game's per-player struct
// (7 action slots at +0x280, device type at +0x29c, timers at +0x828/+0x82c).
struct PlayerInput {
    DeviceType device = DeviceType::None;

    // Current frame state: true while the button is held down.
    bool down[ActionCount] = {};

    // Previous frame state (for edge detection).
    bool prev_down[ActionCount] = {};

    // Edge-detected: true for exactly 1 frame when the button transitions
    // from up→down (just_pressed) or down→up (just_released).
    bool just_pressed[ActionCount] = {};
    bool just_released[ActionCount] = {};

    // Analog stick values (-32768..32767).  Used for movement when a
    // gamepad is connected; keyboard uses the digital D-pad actions instead.
    int16_t stick_x = 0;
    int16_t stick_y = 0;

    // Right stick (camera orbit).  Keyboard: Q/E nudges.
    int16_t stick_rx = 0;
    int16_t stick_ry = 0;

    // "Just pressed" frame timer (mirrors +0x828 in the original).
    // Decrements each frame; >0 means "recently pressed".
    int press_timer[ActionCount] = {};
};

// Keyboard bindings for one player.  Maps Action → SDL_Scancode.
// P0 defaults are the verified 1P layout (arrows + Z/X/C/A/S/D/Q/W);
// P1+ fallbacks are provisional (original uses pads there).
struct KeyboardBindings {
    SDL_Scancode up      = SDL_SCANCODE_UP;
    SDL_Scancode down    = SDL_SCANCODE_DOWN;
    SDL_Scancode left    = SDL_SCANCODE_LEFT;
    SDL_Scancode right   = SDL_SCANCODE_RIGHT;
    SDL_Scancode attackA = SDL_SCANCODE_X;       // melee
    SDL_Scancode attackB = SDL_SCANCODE_UNKNOWN; // unbound (no key exists)
    SDL_Scancode guard   = SDL_SCANCODE_D;       // block
    SDL_Scancode shoot   = SDL_SCANCODE_C;
    SDL_Scancode jump    = SDL_SCANCODE_Z;       // + menu confirm
    SDL_Scancode special = SDL_SCANCODE_S;
    SDL_Scancode tactics = SDL_SCANCODE_Q;
    SDL_Scancode lockSwitch = SDL_SCANCODE_A;
    SDL_Scancode pause   = SDL_SCANCODE_W;
};

class InputManager {
public:
    static constexpr int kMaxPlayers = 4;

    InputManager() = default;
    ~InputManager();

    // Initializes SDL GameController subsystem and opens up to 4 gamepads.
    // Players without a gamepad fall back to keyboard (P1 only by default;
    // P2-P4 need their own keyboard bindings or a gamepad).
    bool init();

    void shutdown();

    // Polls SDL events + reads keyboard/gamepad state.  Call once per
    // frame BEFORE any scene update.  This updates all 4 PlayerInput
    // structs + drains the SDL event queue.
    void poll();

    // Access per-player state.
    const PlayerInput& player(int index) const;

    // Set which player uses the keyboard (default: player 0).
    void set_keyboard_player(int index) { m_keyboardPlayer = index; }

    // Set keyboard bindings for a player.
    void set_keyboard_bindings(int index, const KeyboardBindings& kb);

    // True if any player pressed `action` this frame (for UI navigation).
    bool any_just_pressed(Action action) const;

    // True if any player is holding `action` (for UI hold-to-scroll).
    bool any_down(Action action) const;

private:
    PlayerInput      m_players[kMaxPlayers];
    KeyboardBindings m_kbBindings[kMaxPlayers];
    int              m_keyboardPlayer = 0;  // which player uses keyboard
    SDL_GameController* m_gamepads[kMaxPlayers] = {};
    const uint8_t*   m_keyboardState = nullptr;

    void update_player_keyboard(int index);
    void update_player_gamepad(int index);
    void compute_edges(int index);
};

} // namespace daybreak::input
