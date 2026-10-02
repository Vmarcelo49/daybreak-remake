// Compile-time pins for the media/input tables (Track M).
//
// input_sdl3.h deliberately does not include <SDL3/SDL.h> so its tables unit-test
// anywhere — which means nothing would catch the numbers drifting from SDL3
// itself. This TU exists for exactly that: static_asserts against the real
// headers, compiled on every target (native SDL3 package, MinGW payload,
// Emscripten port). No code, no runtime, no behavior.
#include <SDL3/SDL.h>

#include "audio/audio.h"
#include "audio/audio_format.h"
#include "audio/audio_sdl3.h"
#include "audio/video.h"
#include "input/input.h"
#include "input/input_sdl3.h"

// SDL scancodes are USB HID codes, platform-independent by design; SDL3 gamepad
// buttons are the Xbox-layout enum. If SDL ever renumbers, every assert fires and
// the table gets re-surveyed instead of silently misbinding.
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
static_assert(fnd::input::sdl3::kScCamRight == SDL_SCANCODE_E, "camera-right drifted");
static_assert(sizeof(fnd::input::sdl3::kP1ScancodeByAction) /
                      sizeof(fnd::input::sdl3::kP1ScancodeByAction[0]) ==
                  13,
              "action table lost a slot");
static_assert(fnd::input::sdl3::kPadDpadUp == SDL_GAMEPAD_BUTTON_DPAD_UP, "pad up drifted");
static_assert(fnd::input::sdl3::kPadDpadDown == SDL_GAMEPAD_BUTTON_DPAD_DOWN, "pad down drifted");
static_assert(fnd::input::sdl3::kPadDpadLeft == SDL_GAMEPAD_BUTTON_DPAD_LEFT, "pad left drifted");
static_assert(fnd::input::sdl3::kPadDpadRight == SDL_GAMEPAD_BUTTON_DPAD_RIGHT, "pad right drifted");
static_assert(fnd::input::sdl3::kPadMelee == SDL_GAMEPAD_BUTTON_WEST, "pad melee drifted");
static_assert(fnd::input::sdl3::kPadGuard == SDL_GAMEPAD_BUTTON_SOUTH, "pad guard drifted");
static_assert(fnd::input::sdl3::kPadJump == SDL_GAMEPAD_BUTTON_EAST, "pad jump drifted");
static_assert(fnd::input::sdl3::kPadShoot == SDL_GAMEPAD_BUTTON_NORTH, "pad shoot drifted");
static_assert(fnd::input::sdl3::kPadLock == SDL_GAMEPAD_BUTTON_LEFT_SHOULDER, "pad lock drifted");
static_assert(fnd::input::sdl3::kPadSpecial == SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER,
              "pad special drifted");
static_assert(fnd::input::sdl3::kPadTactics == SDL_GAMEPAD_BUTTON_BACK, "pad tactics drifted");
static_assert(fnd::input::sdl3::kPadPause == SDL_GAMEPAD_BUTTON_START, "pad pause drifted");
