# AUDIO-BACKEND — SDL3 streaming engine (Track M)

Real `fnd::audio::Engine` implementation on SDL3 audio streams. No SDL_mixer:
it has no SDL3/web build in-tree, and its file-path API is what forces the
remake through temp files. Video stays stubbed (decided in MEDIA-INPUT.md §3).

## Files

| File | Owns |
|---|---|
| `src/audio/audio_engine.h` | `SfxBus`, `bus_range`, `convert_to_mix_s16`, `decode_wav_s16`, `decode_cnv_s16` (all inline, SDL-free), `Sdl3Engine` declaration (PIMPL — SDL types stay in the `.cpp`) |
| `src/audio/audio_engine.cpp` | Device open, 33 bound streams, bank/channel/volume/gate logic |

## Design

One playback device at the game Spec (44100 stereo S16, requested; the bound
streams resample when hardware disagrees) plus 33 streams bound with
`SDL_BindAudioStreams`: slot streams 0–31 reproduce the remake's reservation
(ch 0 UI, 1–15 voice, 16–31 gameplay SFX), stream 33 is the music/movie push
path. Everything converts once to 44100 stereo S16 on load/push, so stream
src/dst specs are constant and never depend on which source ran.

- **Push, never block.** `push_music_s16` and `play` return frames accepted /
  channel assigned; a full voice/SFX bus returns −1 (backpressure, no voice
  stealing) and an explicit `req.channel` that is busy or out of range is −1.
- **Volumes.** Four option-screen sliders; effective gain is `bus_gain(bus,
  master)` applied with `SDL_SetAudioStreamGain` per stream. No UI slider
  exists, so UI cues follow the SFX bus. Gains are cached, so `set_volumes`
  before `open` still applies.
- **UnlockGate.** Null gate = always ready (native). Web passes a `Gated`
  gate; pushes and `play` calls while gated are dropped and never queued, so
  BGM starts on the first gesture instead of arriving as one late burst.
- **Bank.** `load_*` copies go in; playback streams already-pushed PCM, so
  callers can free their buffers immediately. Handles recycle through a free
  list; `clear_bank` invalidates all handles (in-flight streams drain
  already-pushed bytes safely).
- **Lazy reclaim.** A slot whose stream drained (`queued == 0`) reads as free
  on the next `play`/`channel_busy`, so callers never poll. A `stop` clears
  the stream and the flag together.

## Decoder seam (BGM streaming + OGG/MP3 — out of scope)

The engine accepts decoded PCM or synthesized buffers only. What decodes
today: WAV-PCM (`decode_wav_s16`: re-walks chunks so JUNK/LIST files decode,
rejects non-PCM) and CNV-PCM (`decode_cnv_s16`: same payload
`cnv_convert.py::convert_audio_cnv` wraps into a WAV, without the temp
file). OGG/MP3 blobs are detected by `audio_format.h` but refused by every
`load_*` — reverified in the harness below.

The future decoder feeds the two push paths and nothing else:

- BGM file: decode OGG (vorbisfile/stb_vorbis or SDL3 stream helper) into
  S16 stereo chunks → `push_music_s16`, honouring `.sfl` loop points (136 B,
  format still unparsed — see MEDIA-INPUT.md §7).
- Movie audio: MP2 frames → `interleave_lr_s16` (already in `audio_sdl3.h`) →
  `push_music_s16`.
- Short cues in new containers: decode → `load_pcm_s16` → `play`.

No engine change is needed for any of these; they are a new `load_ogg` /
`stream_bgm` caller, not a new backend.

## Verification (headless, SDL dummy driver)

Harness sources live only in `/tmp/audio-verify/` (never committed);
test tones/bytes are synthesized in code — no game data, no hardware.

```bash
g++ -std=c++17 -Werror -Wall -Wextra -I remake/foundation/src \
  /tmp/audio-verify/test_audio_backend.cpp remake/foundation/src/audio/audio_engine.cpp \
  -o /tmp/audio-verify/t_audio_backend $(pkg-config --libs sdl3)
SDL_AUDIO_DRIVER=dummy /tmp/audio-verify/t_audio_backend

# header stays SDL-free (decode path tests/links without SDL at all):
g++ -std=c++17 -Werror -Wall -Wextra -I remake/foundation/src \
  /tmp/audio-verify/decode_only.cpp -o /tmp/audio-verify/t_decode_only && /tmp/audio-verify/t_decode_only

# lifetime check (open/bind/play/close under ASan+UBSan):
g++ -std=c++17 -Werror -Wall -Wextra -g -fsanitize=address,undefined \
  -I remake/foundation/src /tmp/audio-verify/test_audio_backend.cpp \
  remake/foundation/src/audio/audio_engine.cpp \
  -o /tmp/audio-verify/t_audio_asan $(pkg-config --libs sdl3)
SDL_AUDIO_DRIVER=dummy /tmp/audio-verify/t_audio_asan
```

Observed (Linux, GCC, SDL3 3.4.16, dummy driver; ASan/UBSan run exit 0,
zero reports):

```
[decode] wav44100_stereo16: frames=100 passthrough=1
[decode] wav22050_mono8: stereo_frames=200
[decode] cnv44100_stereo16: frames=64 match=1
[decode] rejects: ogg/mp3/junk/trunc/empty all refused
[engine] open: dummy device at 44100/stereo ok
[engine] volumes: music=0.50 voice=1.00 sfx=0.25 ui_follows_sfx=1 mute_master=0
[engine] bank: wav=0 cnv=1 pcm=2 size=3
[engine] channels: ui=0 voice_first=1 sfx_first=16 explicit=20 full_bus=-1
[engine] music: pushed=44100 queued=44100
[engine] gate: gated_push=0 gated_play=-1 after_unlock_push=2048 queued>0 regate_drop=1
[engine] null_gate: push=512 ok
RESULT: ok (all checks passed)
decode_only: range=1..15 ok=1 (no SDL linked)
```

What the harness pins: WAV/CNV decode incl. 22050-mono8→44100-stereo
resample math (100 → 200 frames) and exact passthrough for mix-ready input;
OGG/MP3/truncated/empty refusal; device open at 44100/stereo; applied gains
equal `bus_gain` math with master-mute silencing all buses and UI following
SFX; auto-pick inside each bus range; full voice bus (15/15) backpressures
instead of stealing; freed-slot reuse; explicit-channel and stale-handle
rejection; music push/drain accounting; gated push/play dropped with queues
unchanged; post-unlock push accepted; re-gate drops again; null-gate native
push; closed-engine silence.

## Proposed wiring (parent-owned, NOT applied)

```cmake
# CMakeLists.txt — backend TU joins the existing header-only media lib:
#   target_sources(foundation_media PRIVATE src/audio/audio_engine.cpp)
#   if(NOT EMSCRIPTEN)
#     target_link_libraries(foundation_media PUBLIC SDL3::SDL3)
#   endif()
# (Emscripten already supplies SDL3 via -sUSE_SDL=3; no new find-module.)
```

```cpp
// main.cpp — future --audio-test mode sketch (needs game/CLI owner approval):
//   static fnd::audio::UnlockGate gate =
//   #ifdef __EMSCRIPTEN__
//     fnd::audio::UnlockGate(fnd::audio::UnlockState::Gated);
//   #else
//     fnd::audio::UnlockGate(fnd::audio::UnlockState::Unlocked);
//   #endif
//   fnd::audio::Sdl3Engine audio(&gate);
//   if (wants_audio_test) {
//     audio.open(fnd::audio::Spec{});
//     audio.set_volumes(fnd::audio::Volumes{});
//     // --tone <hz>: synthesize N frames, audio.push_music_s16(...)
//     // --wav <path>: read blob, audio.load_wav(...) + audio.play(h, SfxBus::Sfx)
//     // SDL_AppEvent: on finger/key/pad-down -> gate.unlock()
//   }
// Backend .cpp already includes <SDL3/SDL.h>; no pin asserts needed here
// (no SDL codes are pinned by this module — that stays in pin_tables.cpp).
```

## Explicitly not verified

- No audible playback check (subjective; dummy driver only).
- No BGM file streaming or `.sfl` loop points — seam documented above.
- No OGG/MP3 decoding — detection only; every `load_*` refuses them.
- No browser gesture run — gate logic executed natively; web AudioContext
  behaviour is per the SDL3/Emscripten contract, not executed.
- No `main.cpp`/CMake wiring — proposed above, parent decides.
- macOS untouched (standing PORT-PLAN rule).
