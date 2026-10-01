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

## Decoder seam (BGM streaming + MP3 — out of scope)

The engine accepts decoded PCM or synthesized buffers only. What decodes
today: WAV-PCM (`decode_wav_s16`: re-walks chunks so JUNK/LIST files decode,
rejects non-PCM), CNV-PCM (`decode_cnv_s16`: same payload
`cnv_convert.py::convert_audio_cnv` wraps into a WAV, without the temp
file), and OGG Vorbis (`Sdl3Engine::load_ogg` via vendored stb_vorbis
pinned in `scripts/fetch_deps.sh` — every shipped BGM file, verified below).
MP3 blobs are detected by `audio_format.h` but refused by every `load_*`;
nothing in the shipped game data is MP3, so no second decoder is carried.

What remains decoder-side:

- BGM file: OGG is done, and so are `.sfl` loop points and streaming.
  `parse_sfl_loop` reads the RIFF cue offset (authoritative start) plus the
  `Region MM:SS.mmm to MM:SS.mmm` label (end), failing on mismatch rather
  than looping the wrong bars; `LoopPlayer` streams decoded PCM through any
  `Engine` in chunks, wrapping at the loop end. `--audio-test --audio-file`
  streams every `.sfl` pair through two full wraps with exact accounting.
- Movie audio: MP2 frames → `interleave_lr_s16` (already in `audio_sdl3.h`) →
  `push_music_s16` — waiting on the video decision, not on audio.

No engine change is needed for any of these; they are new callers of the two
push paths, not a new backend.

## Verification (headless, SDL dummy driver)

In-engine `--audio-test` extends the harness: `--audio-file=<path>` decodes
a real shipped file through the bank (ogg/wav/cnv by format detection) and
fires it once. All 21 shipped BGM files decode with `RESULT: ok`, and decoded
sample counts match `ffprobe` durations to within container padding on every
file (e.g. `01.ogg`: 94.09 s vs 4,149,248 samples).

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
- No BGM file streaming or `.sfl` loop points — implemented (see above); all
  20 pairs stream two wraps with exact accounting on Linux and Wine.
- No MP3 decoding — detection only; nothing shipped is MP3, so no decoder.
- OGG Vorbis decodes (all 21 BGM files, durations cross-checked with ffprobe).
- No browser gesture run — gate logic executed natively; web AudioContext
  behaviour is per the SDL3/Emscripten contract, not executed.
- `main.cpp`/CMake wiring for `--audio-test --audio-file` landed with the
  decoder (this doc's § Verification describes it).
- macOS untouched (standing PORT-PLAN rule).
