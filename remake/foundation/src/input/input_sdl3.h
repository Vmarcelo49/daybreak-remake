#pragma once
#include "input/input.h"
// SDL3 device mapping for Track M (tables only, no polling here).
//
// Why tables instead of a poll loop: polling needs a window, events and
// opened gamepads — none of which exist in a unit test — while the mapping
// itself is the part the port must get right (verified P1 keys, provisional
// pad map). The future backend .cpp owns SDL_OpenGamepad/event drain and
// includes this for the constants. Web caveats are documented where they
// bite because they change integration, not the tables.

// This header intentionally does NOT include <SDL3/SDL.h>: the numeric codes
// below are the SDL3 scancode/button values, pinned so the tables test
// without SDL linked. The backend static_asserts them against the real
// headers at build time.

namespace fnd::input::sdl3 {

// SDL3 key codes (SDL_Scancode) for the verified P1 layout. Names kept so a
// reader can check against input_manager.h without opening SDL headers.
inline constexpr int kScUp = 82;     // SDL_SCANCODE_UP
inline constexpr int kScDown = 81;    // SDL_SCANCODE_DOWN
inline constexpr int kScLeft = 80;    // SDL_SCANCODE_LEFT
inline constexpr int kScRight = 79;   // SDL_SCANCODE_RIGHT
inline constexpr int kScMelee = 27;   // SDL_SCANCODE_X
inline constexpr int kScGuard = 7;    // SDL_SCANCODE_D
inline constexpr int kScShoot = 6;    // SDL_SCANCODE_C
inline constexpr int kScJump = 29;    // SDL_SCANCODE_Z
inline constexpr int kScSpecial = 22;  // SDL_SCANCODE_S
inline constexpr int kScTactics = 20;  // SDL_SCANCODE_Q
inline constexpr int kScLock = 4;      // SDL_SCANCODE_A
inline constexpr int kScPause = 26;    // SDL_SCANCODE_W
inline constexpr int kScCamLeft = 20;  // Q doubles as camera-left nudge
inline constexpr int kScCamRight = 8;  // SDL_SCANCODE_E, camera-right nudge

// The original's in-battle debug keys (issue #48). SDL scancodes are USB HID codes, NOT the
// DIK codes FUN_00634f60 reads (gameplay/debug_keys.h names those), so the mapping lives here
// where pin_tables.cpp can assert it against SDL: Escape DIK 0x01 -> HID 41, F1 DIK 0x3b ->
// HID 58, F2 0x3c -> 59, F3 0x3d -> 60, F4 0x3e -> 61. Deliberately not actions: the debug
// keys are not part of the 13-action vocabulary and must not be rebindable.
inline constexpr int kScEscape = 41;  // SDL_SCANCODE_ESCAPE
inline constexpr int kScF1 = 58;      // SDL_SCANCODE_F1
inline constexpr int kScF2 = 59;      // SDL_SCANCODE_F2
inline constexpr int kScF3 = 60;      // SDL_SCANCODE_F3
inline constexpr int kScF4 = 61;      // SDL_SCANCODE_F4

// Index by fnd::input::Action (0..11); -1 = unbound.
// Order: Up Down Left Right | AttackA Guard Shoot | Jump Special Tactics |
//        LockSwitch Pause.
inline constexpr int kP1ScancodeByAction[ActionCount] = {
    kScUp, kScDown, kScLeft, kScRight,  // Up Down Left Right
    kScMelee, kScGuard, kScShoot,       // AttackA Guard Shoot
    kScJump, kScSpecial, kScTactics,    // Jump Special Tactics
    kScLock, kScPause,                 // LockSwitch Pause
};

// SDL3 gamepad buttons (SDL_GamepadButton), Xbox-label layout. Provisional —
// the original P2-P4 pads are buttons 1-8 with exact layout unknown, and the
// remake's map (X=melee, A=guard, B=jump, Y=shoot, LB=lock, RB=special,
// Back=tactics, Start=pause) is carried over verbatim until captures say
// otherwise.
inline constexpr int kPadDpadUp = 11;
inline constexpr int kPadDpadDown = 12;
inline constexpr int kPadDpadLeft = 13;
inline constexpr int kPadDpadRight = 14;
inline constexpr int kPadMelee = 2;   // X (west)
inline constexpr int kPadGuard = 0;   // A (south)
inline constexpr int kPadJump = 1;    // B (east)
inline constexpr int kPadShoot = 3;   // Y (north)
inline constexpr int kPadLock = 9;    // left shoulder
inline constexpr int kPadSpecial = 10;  // right shoulder
inline constexpr int kPadTactics = 4;   // back
inline constexpr int kPadPause = 6;     // start (5 is guide, not start)
inline constexpr int kPadButtonByAction[ActionCount] = {
    kPadDpadUp, kPadDpadDown, kPadDpadLeft, kPadDpadRight,
    kPadMelee, kPadGuard, kPadShoot, kPadJump,
    kPadSpecial, kPadTactics, kPadLock, kPadPause,
};

// Web gamepad caveats (integration, not tables):
// - Browsers expose pads only after a button press AND only on secure
//   contexts (https or localhost); SDL3 polls the Gamepad API underneath, so
//   "no pads found" before the first press is expected, not a bug.
// - The page needs focus and one animation frame before events flow; the
//   foundation's SDL3 iterate callback is that frame, so no extra pump is
//   needed, but pads connected mid-session appear on re-poll, not instantly.
// - Vibration/rumble is not wired here: the browser API is async and
//   permission-gated, so haptics stay a future backend option, not a promise.

}  // namespace fnd::input::sdl3
