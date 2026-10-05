# Track M — media and input (foundation side)

Owner files: `src/audio/*`, `src/input/*`, this doc. The `main.cpp` / CMake
seam has landed (`--audio-test`/`--audio-file`, `--input-test` via
`runAudioTest`/`runInputTest`; `src/audio/audio_engine.cpp` +
`src/input/input_backend.cpp` compile into `foundation_media`).

## 1. Inventory (pre-cutover survey — reference tree deleted, findings kept)

Surveyed `remake/src/audio/audio_engine.{h,cpp}`,
`remake/src/input/input_manager.{h,cpp}`,
`remake/src/render/video_player.{h,cpp}`, `remake/src/third_party/pl_mpeg.h`,
`remake/src/core/scenes.cpp`, `remake/docs/{reverse-engineering,placeholders,
roadmap}.md`, `remake/tools/asset-tools/cnv_convert.py`. Nothing there was
edited; all paths below are the reference's. Note: the `remake/src/**` paths
above were deleted in the Phase 5 cutover (2026-10-02) — treat their rows as
transcribed findings. Live provenance is the foundation (`src/audio/*`,
`src/input/*`, `src/gameplay/*`) plus the surviving
`remake/tools/asset-tools/cnv_convert.py` and the banked
`remake/tests/parity-baseline/` evidence.

### Audio

| Need | Reference finding |
|---|---|
| BGM format | `data/bgm/*.ogg` Vorbis, 44100 Hz stereo (`win.ogg` validated by ffprobe; `Mix_OpenAudio(44100, S16SYS, stereo, 2048)`) |
| BGM bundles | `daybreak05.dat`: 41 entries, `.ogg` + `.sfl` pairs; `.sfl` (136 B) holds loop points |
| BGM now | single hardcoded `data/bgm/01.ogg` per match, streamed via `Mix_Music`; currently fails to decode (`Unrecognized audio format`), so matches run silent |
| Voice/SFX format | `data/voice/entry/%s.wav` WAV PCM; `daybreak07.dat` (178 entries) items/bullets/voice snippets |
| CNV audio | 16-byte header (channels, reserved==1, rate ∈ {22050,44100,48000}, bits ∈ {8,16}) + raw PCM, from `FUN_00665020`; converter: `remake/tools/asset-tools/cnv_convert.py` |
| Mixer model | 32 SFX channels + 1 music; ch 0 = UI, 1–15 = voice, 16–31 = gameplay SFX; option screen has 4 sliders (master/music/voice/SFX) |
| Load path | temp files everywhere (`write_temp_file`, `extract_to_temp`): SDL_mixer takes file paths, not memory |
| Movie audio | MP2 stereo 44100 Hz via pl_mpeg; float[−1,1] → S16 stereo chunks drained by `Mix_HookMusic` callback |
| Original API | `WINMM.dll` import; DirectSound-era 44.1 kHz stereo throughout |

### Video (`.mpg` decision: **stub** — see §3)

| Need | Reference finding |
|---|---|
| Files | `movie/op.mpg` (boot), `movie/prologue.mpg`, `movie/staffroll{,2}.mpg`; story FMVs also fill `daybreak06.dat` (439 MB, 5 entries) |
| Codec | MPEG-PS (MPEG1 video + MP2 audio); decoded by vendored pl_mpeg (~4300-line single header, `remake/src/third_party/pl_mpeg.h`) |
| Presentation | video → DX9 texture (`plm_frame_to_bgra`, alpha pre-set 255) drawn as a fullscreen quad; audio via the `Mix_HookMusic` chunk queue above |
| Behaviour | boot plays `op.mpg`, **skippable on any button** (`Scene_Opening`) |
| Framing | letterbox bars are baked into the video itself (reference capture `opening-frame-01`) |

### Input

| Need | Reference finding |
|---|---|
| Shape | 4 players (`fcn.00634f60` loop `i = 0..3`); original polled 7 slots via DirectInput8 — deliberately **not** mirrored |
| Action model | 12 actions from `controller-setup.webp`: Up/Down/Left/Right, melee (X), guard (D), shoot (C), jump/confirm (Z), special (S), tactics (Q), lock-switch tap-cycle/hold-ally (A), pause (W). There is ONE melee action: the corpus has one attack input bit and no heavy bit (issue #10 removed the stand-in) |
| P1 layout | arrows + `Z X C A S D Q W`; P2–P4 use pads (buttons 1–8, exact map unknown) → provisional pad map (X=melee, A=guard, B=jump, Y=shoot, LB=lock, RB=special, Back=tactics, Start=pause) |
| State | `down / prev_down / just_pressed / just_released`, analog sticks ±32767, `press_timer` 2-frame window (mirrors `+0x828`) |
| Script driver | `<frame> <TOKEN>…` lines (`-` = release all, `#` = comment), tokens `UP DOWN LEFT RIGHT MELEE GUARD SHOOT JUMP SPECIAL TACTICS LOCK PAUSE`; override applied inside `poll()` before edge computation |

## 2. Interfaces added

All headers are C++17, dependency-free (no SDL include), so they compile and
test anywhere. SDL3 numeric codes are pinned as constants; the future backend
`.cpp` `static_assert`s them against `<SDL3/SDL.h>` at build time.

| File | Owns |
|---|---|
| `src/audio/audio_format.h` | `detect_format` (WAV/OGG/MP3/MPEG-PS/CNV magic), `parse_wav`, `float_to_s16`, `drain_bytes`, `volume_gain` |
| `src/audio/audio.h` | `Spec` (44100/stereo/2048 — what every source already is), channel reservation (`kUiChannel/kVoiceFirst…/kSfxLast`), `Volumes` + `bus_gain`, `UnlockGate`, `Engine` contract + `NullEngine` |
| `src/audio/audio_sdl3.h` | `to_device_spec`, `interleave_lr_s16` (MP2 1152-frame path), `may_push` unlock rule |
| `src/audio/video.h` | `is_mpeg_ps` probe, `StubPlayer` (`Unimplemented`, `skippable() == true`), `ycrcb_to_rgb` (BT.601, RGBA order) for the future uploader |
| `src/input/input.h` | `Action` (13), `DeviceType`, `PlayerState`, `compute_edges`, `apply_deadzone` / `stick_to_digital` (deadzone 8000), `parse_script_line` |
| `src/input/input_sdl3.h` | P1 scancode table (verified against SDL 3.4.16 headers), provisional pad button table, web gamepad caveats |

Why SDL3 streams and not SDL_mixer: SDL_mixer has no SDL3/web build in this
tree, and its file-path API is what forces the remake through temp files.
`SDL_AudioStream` takes pushed PCM and resamples, so BGM/voice/movie audio
converge on one push path and the temp-file dance disappears.

## 3. Video decision: stub, with reasons

**Implement or stub: stub.** Not silent — `StubPlayer::open()` recognises an
MPEG-PS blob and reports `Unimplemented`, so the boot-movie call site can be
wired now without anyone mistaking it for working.

1. Cost vs gate: a real port vendors ~4300 lines of pl_mpeg plus a new WebGPU
   texture-upload path, while the D2 gate (a matching *in-game* frame) never
   needs video.
2. Data: every `.mpg` is copyrighted game data, absent from the repo and from
   CI; verification would be subjective playback, not a number.
3. Web delivery of those bytes is Track W's open question (preload vs
   fetch/streaming); decoding before that path exists builds on sand.
4. The behaviour contract (play `op.mpg` at boot, any-button skip,
   letterbox-in-video) is recorded above and in the stub so the future
   implementer starts from requirements, not archaeology.

## 4. Deterministic tests (scratch, under `/tmp`)

Nothing here needs a device, window, or game data. Each test compiles the
headers only:

```bash
g++ -std=c++17 -Werror -Wall -Wextra -I remake/foundation/src \
  /tmp/trackm/test_audio_format.cpp -o /tmp/trackm/t_audio_format && /tmp/trackm/t_audio_format
g++ -std=c++17 -Werror -Wall -Wextra -I remake/foundation/src \
  /tmp/trackm/test_audio_engine.cpp -o /tmp/trackm/t_audio_engine && /tmp/trackm/t_audio_engine
g++ -std=c++17 -Werror -Wall -Wextra -I remake/foundation/src \
  /tmp/trackm/test_input.cpp -o /tmp/trackm/t_input && /tmp/trackm/t_input
g++ -std=c++17 -Werror -Wall -Wextra -I remake/foundation/src \
  /tmp/trackm/test_video.cpp -o /tmp/trackm/t_video && /tmp/trackm/t_video
```

Observed (Linux, GCC 16.2.1, SDL3 3.4.16 present but not linked):

```
[audio_format] detect: wav=1 ogg=1 mp3=1 ps=1 cnv=1 unknown=1
[audio_format] wav: rate=44100 ch=2 bits=16 frames=1152 data=4608
[audio_format] wav_trunc: invalid=1
[audio_format] f32->s16: over=32767 under=-32767 zero=0
[audio_format] drain: full=4096 partial=1000 past_end=0
[audio_format] vol: 0->0.000 64->0.500 128->1.000 clip_hi=1.000 clip_lo=0.000
[audio_format] RESULT: ok (16 checks)
[audio_engine] spec: rate=44100 ch=2 frames=2048
[audio_engine] channels: ui=0 voice=1..15 sfx=16..31 max=32
[audio_engine] bus: mute=0.000 half=0.250 full=1.000
[audio_engine] gate: native_ready=1 web_gated=0 web_after_unlock=1
[audio_engine] null: pushed=2304 open=1
[audio_engine] sdl3: rate=44100 ch=2 frames=2048 silent_bytes=0
[audio_engine] RESULT: ok (17 checks)
[input] edges: tap p=1 r=0 | hold p=0 | release p=0 r=1
[input] timer: t0=2 t1=1 t2=0
[input] deadzone: rest=0 edge=0 live=9000 neg=-9000
[input] stick: left=1 right=0 up=1 down=0
[input] script: f1=10,mask=0x180 f2=30,mask=0x0 skip=1
[input] sdl3: p1_up=82 p1_melee=27 p1_pause=26 pad_pause=6
[input] RESULT: ok (17 checks)
[video] probe: ps=1 wav_not_ps=1 empty=0
[video] stub: recognised=1 status=unimplemented skippable=1 non_ps_rejected=1
[video] ycrcb: black=0,0,0 white=255,255,255 red=254,0,0
[video] RESULT: ok (10 checks)
```

What the tests pin: magic-byte routing for all five blob kinds, WAV
parse incl. truncated-tail rejection, float→S16 clamping (no wraparound),
queue-drain accounting, volume/bus math, channel reservation, web-gate
transitions, MP2 interleave sizing, edge/timer/deadzone/stick/script
behaviour incl. `-`/comment/unknown-token lines, SDL3 code pinning
(P1 scancodes, pad Start=6), MPEG-PS probe, stub status, BT.601 primaries.

Pinned codes additionally verified against the real SDL 3.4.16 headers
(`check_sdl_pin.cpp`: 25 `static_assert`s vs `SDL_SCANCODE_*` /
`SDL_GAMEPAD_BUTTON_*` — all hold; compile-only, no link).

## 5. Integration (landed)

```cmake
# CMakeLists.txt — media lib beside foundation_render (landed):
add_library(foundation_media STATIC
  src/audio/audio_engine.cpp   # SDL3 stream backend: load_ogg (stb_vorbis) + bank/play/gate
  src/input/input_backend.cpp) # event drain + tables: init/poll/script driver
target_include_directories(foundation_media PUBLIC src)
target_link_libraries(foundation_media PUBLIC foundation)
if(NOT EMSCRIPTEN)
  target_link_libraries(foundation_media PUBLIC SDL3::SDL3)
endif()
# + foundation_media is linked into foundation_demo.
```

```cpp
// main.cpp — unlock on first gesture, poll input before scene update (landed
// as runAudioTest/runInputTest, src/main.cpp:1530/1659):
//   static fnd::audio::UnlockGate gate =
//   #ifdef __EMSCRIPTEN__
//     fnd::audio::UnlockGate(fnd::audio::UnlockState::Gated);
//   #else
//     fnd::audio::UnlockGate(fnd::audio::UnlockState::Unlocked);
//   #endif
//   // in SDL_AppEvent: on finger/key/pad-down -> gate.unlock()
//   // in SDL_AppIterate: if (gate.ready()) engine.push_music_s16(...)
// Backend .cpps must also: static_assert(kScUp == SDL_SCANCODE_UP, …)
// against the real SDL3 headers so the pinned tables cannot drift.
```

Landed on top of this: OGG Vorbis decode (`Sdl3Engine::load_ogg` via
vendored stb_vorbis), `.sfl` loop parsing (`parse_sfl_loop` in
`src/audio/audio_format.h:161`) with `LoopPlayer` chunk streaming
(`src/audio/audio.h:123`), and the SDL3 audio/input backends
(`src/audio/audio_engine.cpp`, `src/input/input_backend.cpp`) behind the
`--audio-test`/`--input-test` seams (`src/main.cpp:1527+`).

## 6. Platform caveats

| Target | Audio | Input |
|---|---|---|
| Linux | SDL3 stream push; device resamples if ≠44100; no mixer needed | SDL3 keyboard + `SDL_OpenGamepad`; hotplug via re-poll |
| Windows (MinGW/Wine) | same stream path; verify no temp files remain (old mixer limitation, gone) | same; XInput pads appear as SDL gamepads |
| Web (Emscripten) | AudioContext starts **suspended**: gate stays `Gated` until first pointer/key/pad gesture; pushes while gated are dropped, never queued (no late BGM burst) | pads visible only after a button press, secure context (https/localhost) only; first-frame focus needed; no rumble (async/permission-gated — future option, not promised) |
| macOS | not attempted (standing PORT-PLAN rule); code is dependency-free so nothing here blocks it | same as above |

## 7. Explicitly not verified

- No audible playback check (subjective; no device in this environment).
- No `movie/op.mpg` decode — no game data in the repo; stub only
  (`src/audio/video.h` `StubPlayer`).
- No MP3 *decoding* — detection only, correctly absent (nothing shipped is
  MP3).
- No live gamepad or browser-gesture execution — tables pinned against SDL
  3.4.16 headers; web behaviour documented from the SDL3/Emscripten
  contract, not executed.
