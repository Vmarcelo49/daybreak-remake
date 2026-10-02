# INPUT-BACKEND — SDL3 polling backend (Track M)

Owner files: `src/input/input_backend.{h,cpp}`, this doc. Parent-owned seams
(`CMakeLists.txt`, `src/main.cpp`) are recorded in §5 as landed.

Layering, unchanged: `input.h` owns the device-free model (13 actions,
edges, deadzone, script parsing), `input_sdl3.h` owns the pinned tables and
stays SDL-include-free, and `input_backend.{h,cpp}` owns everything that
needs a window, events or opened pads. `input_backend.h` is likewise
SDL-free (proved by compiling it without SDL headers, §4); only the `.cpp`
includes `<SDL3/SDL.h>`.

## 1. Mapping (reference: MEDIA-INPUT.md §1, remake `input_manager.*`)

- P0 keyboard = verified P1 layout via `kP1ScancodeByAction`
  (arrows + Z/X/C/A/S/D/Q/W; AttackB unbound). Q is Tactics *and*
  camera-left (same scancode, so orbit and action agree by construction);
  E is camera-right only.
- P1–P3 gamepads = **provisional** map carried over verbatim from the
  remake (`X=melee, A=guard, B=jump, Y=shoot, LB=lock, RB=special,
  Back=tactics, Start=pause`, D-pad + left stick with deadzone 8000).
  The original P2–P4 pads are buttons 1–8 with exact layout unknown, so this
  stays labelled provisional until captures say otherwise. AttackB has no
  key or button anywhere and stays exist-but-unbound.

## 2. Backend contract (`fnd::input::Backend`)

- `init()` takes only the gamepad subsystem (`SDL_INIT_GAMEPAD`); SDL
  itself (video/events) stays with `plat::init`, so `shutdown()` can never
  `SDL_Quit` a window it does not own.
- `poll()` order: pump OS input → absorb queued key events → re-poll
  hotplug → read P0 keyboard + P1–P3 pads → script override on P0 →
  `compute_edges` for all four players (2-frame `press_timer` included).
- Keyboard is event-held **OR** `SDL_GetKeyboardState`: pushed/forwarded
  `KEY_DOWN` never reaches SDL's internal array (verified headless, §4),
  while keys already down at startup never produce events. Either source
  alone drops real input.
- Hotplug is re-poll (`SDL_GetGamepads` every frame), not ADDED/REMOVED
  events: under SDL3 callbacks the event consumer is `SDL_AppEvent`, so an
  event-driven pad table would split-brain with it. Failed opens keep the
  slot free; a removed pad reads as released once (one `just_released`),
  never as a stuck hold.
- Key events are consumed with `GETEVENT` (bounds the queue for apps with
  no `SDL_PollEvent` loop); everything else stays queued for the app, and
  focus-loss is only observed (never consumed) to clear held keys. Under
  callbacks, dispatched keys never sit queued, so nothing here can steal
  `SDL_AppEvent` input — that path forwards to `note_key` instead (§5).
- Script driver: `load_script` / `tick_script(frame)` / `clear_script`.
  Same line format as the remake (`<frame> TOKEN…`, `-` releases all, `#`
  comments, unknown tokens ignored); the override replaces P0's held set
  wholesale inside `poll()`, so scripted taps get real edges.

## 3. Web gamepad caveats (also in code where they bite)

- Pads appear only after a button press and only on secure contexts
  (https/localhost); zero pads before the first press is expected, not a
  backend failure (`repoll_gamepads`).
- The page needs focus and one frame before events flow; the foundation's
  iterate callback is that frame (`drain_key_events`).
- No rumble: the browser haptics path is async and permission-gated, so it
  stays a future backend option, not a promise (`update_gamepad`).

## 4. Headless verification (this machine, SDL 3.4.16, dummy video)

Harness sources live only in `/tmp/trackm_in/` (never in the repo); they
compile the backend TU directly:

```bash
g++ -std=c++17 -Werror -Wall -Wextra -I remake/foundation/src \
  /tmp/trackm_in/test_backend_keys.cpp remake/foundation/src/input/input_backend.cpp \
  -o /tmp/trackm_in/t_keys $(pkg-config --cflags --libs sdl3) && /tmp/trackm_in/t_keys
g++ -std=c++17 -Werror -Wall -Wextra -I remake/foundation/src \
  /tmp/trackm_in/test_backend_script.cpp remake/foundation/src/input/input_backend.cpp \
  -o /tmp/trackm_in/t_script $(pkg-config --cflags --libs sdl3) && /tmp/trackm_in/t_script
printf '#include "input/input_backend.h"\nint main() { return 0; }\n' > /tmp/trackm_in/hdronly.cpp
g++ -std=c++17 -Werror -Wall -Wextra -I remake/foundation/src \
  -c /tmp/trackm_in/hdronly.cpp -o /tmp/trackm_in/hdronly.o  # SDL-free proof
```

Observed:

```
[keys] pads=1
[keys] pad1: sticks=-6,-1,0,-1
[keys] X-down: down=1 jp=1 timer=2
[keys] X-up: down=0 jr=1 timer=0
[keys] Up: down=1 stick_y=-32768
[keys] Q: tactics=1 stick_rx=-32768
[keys] E: stick_rx=32767 actions_clear=1
[keys] focus-lost: down=0 jr=1
[keys] RESULT: ok (60 checks)
[fnd::input] script: /tmp/trackm_in/script.txt (7 events)
[script] f=1 down=0x100 jp=0x100 jr=0x000 tJ=2 tM=0 tG=0
[script] f=2 down=0x100 jp=0x000 jr=0x000 tJ=1 tM=0 tG=0
[script] f=3 down=0x000 jp=0x000 jr=0x100 tJ=0 tM=0 tG=0
[script] f=4 down=0x050 jp=0x050 jr=0x000 tJ=0 tM=2 tG=2
[script] f=5 down=0x050 jp=0x000 jr=0x000 tJ=0 tM=1 tG=1
[script] f=6 down=0x000 jp=0x000 jr=0x050 tJ=0 tM=0 tG=0
[script] f=7 down=0x000 jp=0x000 jr=0x000 tJ=0 tM=0 tG=0
[script] RESULT: ok (47 checks)
```

What this pins: `SDL_PushEvent` KEY_DOWN/UP → P0 down/just_pressed/
just_released + 2-frame timer through `poll()`; arrow→stick synthesis;
Q→Tactics+camera-left, E→camera-right with no action; focus-loss release;
pad open path read-only on the attached 8BitDo (all released, rest axes
inside the deadzone, stable across re-polls); script playback with exact
edge/timer output incl. `-`, comments and unknown-token lines; the public
header compiles with no SDL headers present.

## 5. Integration (landed)

```cmake
# CMakeLists.txt — backend compiled into foundation_media (landed):
#   target_sources(foundation_media PRIVATE src/input/input_backend.cpp)
#   (foundation_media already links SDL3 on non-Emscripten targets.)
```

```cpp
// main.cpp — --input-test mode (landed as runInputTest):
//   #include "input/input_backend.h"
//   // App gains: fnd::input::Backend input; bool inputTest = false;
//   //   uint64_t inputFrame = 0; std::string inputScript;
//   // parseArgs: --input-test[=script] sets inputTest (+script path).
//   // After plat::init: if (inputTest && !app->input.init()) return SDL_APP_FAILURE;
//   //   if (!inputScript.empty()) app->input.load_script(inputScript.c_str());
//   // SDL_AppEvent: on SDL_EVENT_KEY_DOWN/UP ->
//   //   app->input.note_key((int)event->key.scancode, event->type == SDL_EVENT_KEY_DOWN);
//   //   on SDL_EVENT_WINDOW_FOCUS_LOST -> app->input.note_focus_lost();
//   // SDL_AppIterate (inputTest): app->input.tick_script(++app->inputFrame);
//   //   app->input.poll(); print P0 down/just_pressed masks; return SUCCESS
//   //   after --frames (or 1 frame with a script, mirroring --out).
```

## 6. Explicitly not verified

- Pressed gamepad buttons/trigger paths: pushed `GAMEPAD_BUTTON` events do
  not move SDL's device state (same synthetic-event wall as keys, §2), and
  no presses were synthesised on the attached pad — it was read at rest
  only. Button/axis reads are code review + `static_assert` pins, and the
  P2–P4 map stays provisional regardless.
- No browser run: web behaviour is documented from the SDL3/Emscripten
  contract, not executed.
- `main.cpp`/CMake wiring has landed (§5: `foundation_media` compiles
  `src/input/input_backend.cpp`, `src/main.cpp` wires `--input-test`
  through `runInputTest`).
