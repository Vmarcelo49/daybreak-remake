#pragma once
// SDL3 streaming adapter notes for Track M (no device touched here).
//
// Why SDL3 streams instead of SDL_mixer: SDL_mixer has no SDL3/web build in
// this tree and its file-path API forced the remake through temp files.
// SDL3's SDL_AudioStream takes pushed PCM and resamples, so BGM (OGG), voice
// (WAV/CNV PCM) and movie audio (MP2 float->S16) all converge on one push
// path. This header holds only the parts that are deterministic: spec
// mapping, interleave math, and the unlock rule. Device open/push lives in
// the future backend .cpp so this file tests without SDL linked.

#include <cstddef>
#include <cstdint>

#include "audio/audio_format.h"

namespace fnd::audio::sdl3 {

// SDL3 wants an explicit device spec; the game spec is already it. Keeping
// float32 out is deliberate: sources convert to S16 once (float_to_s16) so
// the stream format never depends on which decoder ran.
struct DeviceSpec {
    uint32_t sample_rate = 44100;
    uint8_t channels = 2;
    uint16_t frames = 2048;
};

inline DeviceSpec to_device_spec(const Spec& s) {
    DeviceSpec d;
    d.sample_rate = s.sample_rate ? s.sample_rate : 44100;
    d.channels = (s.channels == 1 || s.channels == 2) ? s.channels : 2;
    d.frames = s.frames_per_callback ? s.frames_per_callback : 2048;
    return d;
}

// Interleave L/R float planes into one S16 stereo chunk (MP2 path: pl_mpeg
// yields 1152-sample frames). Returns bytes appended; clamps via
// float_to_s16 so hot samples click instead of wrapping.
inline size_t interleave_lr_s16(const float* left, const float* right,
                                size_t count, int16_t* out_stereo) {
    if ((!left && !right) || !out_stereo) return 0;
    for (size_t i = 0; i < count; ++i) {
        float l = left ? left[i] : 0.0f;
        float r = right ? right[i] : 0.0f;
        out_stereo[i * 2] = float_to_s16(l);
        out_stereo[i * 2 + 1] = float_to_s16(r);
    }
    return count * 2 * sizeof(int16_t);
}

// Web unlock rule: SDL3 on Emscripten suspends the AudioContext until a
// gesture. The backend must call gate.unlock() from the first
// pointer/key event (SDL_EVENT_FINGER/PAD/key down) before pushing; pushes
// while gated are dropped, never queued, so BGM starts on gesture, not late.
inline bool may_push(bool gate_ready) { return gate_ready; }

}  // namespace fnd::audio::sdl3
