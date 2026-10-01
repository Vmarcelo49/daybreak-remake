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
//  and gamepad), but mirror the same 7-action enum and 4-player structure.
//
//  Actions (7 per player, inferred from RE + game design):
//    0: Up
//    1: Down
//    2: Left
//    3: Right
//    4: AttackA  (light attack — punch/kick)
//    5: AttackB  (heavy attack / special)
//    6: Guard    (block / target switch when tapped)
//
//  Note: "Target switch" (Tab in our camera) is action 6 tapped quickly
//  while guarding.  The original game uses a dedicated button on the
//  controller; we map it to Guard-tap for keyboard and to a shoulder
//  button on gamepad.
// =============================================================================
#pragma once

#include <cstdint>

#include <SDL.h>

namespace daybreak::input {

enum Action : int {
    Up      = 0,
    Down    = 1,
    Left    = 2,
    Right   = 3,
    AttackA = 4,  // light
    AttackB = 5,  // heavy / special
    Guard   = 6,  // block / target switch
    ActionCount = 7,
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
struct KeyboardBindings {
    SDL_Scancode up      = SDL_SCANCODE_W;
    SDL_Scancode down    = SDL_SCANCODE_S;
    SDL_Scancode left    = SDL_SCANCODE_A;
    SDL_Scancode right   = SDL_SCANCODE_D;
    SDL_Scancode attackA = SDL_SCANCODE_J;   // light
    SDL_Scancode attackB = SDL_SCANCODE_K;   // heavy
    SDL_Scancode guard   = SDL_SCANCODE_L;   // block
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
