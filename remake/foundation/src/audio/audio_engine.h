#pragma once
// SDL3 streaming audio backend behind fnd::audio::Engine (Track M).
//
// Why streams and not SDL_mixer: SDL_mixer has no SDL3/web build in this tree
// and its file-path API forced the remake through temp files. One playback
// device plus 33 pushed-S16 streams (32 SFX slots + 1 music) reproduces the
// remake's 32-channel reservation with no temp files: the device resamples,
// so every source converts once to 44100 stereo S16 on load/push.
//
// BGM file streaming and OGG/MP3 decoding are NOT here (decoder seam is in
// docs/AUDIO-BACKEND.md): the engine takes decoded PCM or synthesized
// buffers, and the future decoder feeds push_music_s16 / load_pcm_s16.

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include "audio/audio.h"
#include "audio/audio_format.h"

namespace fnd::audio {

// Which option-screen slider a channel follows. The remake's option screen
// has master/music/voice/SFX sliders and no UI slider, so UI cues follow SFX.
enum class SfxBus { Ui, Voice, Sfx };

// Channel range owned by a bus; mirrors the kUiChannel/kVoiceFirst…
// reservation in audio.h so auto-pick never crosses a bus boundary.
inline bool bus_range(SfxBus bus, int& first, int& last) {
    switch (bus) {
        case SfxBus::Ui: first = kUiChannel; last = kUiChannel; return true;
        case SfxBus::Voice: first = kVoiceFirst; last = kVoiceLast; return true;
        case SfxBus::Sfx: first = kSfxFirst; last = kSfxLast; return true;
    }
    return false;
}

// Resample one PCM source to 44100 stereo S16 frames. Linear interpolation is
// enough because sources are already near rate (22050/44100/48000) and this
// runs once per load, never per callback. 8-bit sources are unsigned
// (128 center) per the WAV/CNV convention; 16-bit are little-endian.
inline void convert_to_mix_s16(const uint8_t* pcm, size_t src_frames,
                               int src_channels, uint32_t src_rate,
                               int src_bits, std::vector<int16_t>& out_stereo) {
    out_stereo.clear();
    if (!pcm || src_frames == 0 || src_rate == 0) return;
    if (src_channels != 1 && src_channels != 2) return;
    if (src_bits != 8 && src_bits != 16) return;
    const size_t dst_frames = (src_frames * 44100 + src_rate - 1) / src_rate;
    out_stereo.resize(dst_frames * 2);
    if (src_rate == 44100 && src_channels == 2 && src_bits == 16) {
        // Already mix-ready: copy exactly. The float path below is ±1 LSB
        // (32768 vs 32767 scale), inaudible but needlessly lossy here.
        const auto* s16 = reinterpret_cast<const int16_t*>(pcm);
        for (size_t i = 0; i < dst_frames * 2; ++i) out_stereo[i] = s16[i];
        return;
    }
    auto sample_at = [&](size_t f, int c) -> float {
        // Clamp the read index so the interpolator never runs past the tail.
        size_t f0 = f < src_frames ? f : src_frames - 1;
        size_t base = (f0 * static_cast<size_t>(src_channels) + static_cast<size_t>(c)) *
                      static_cast<size_t>(src_bits / 8);
        if (src_bits == 8)
            return (static_cast<float>(pcm[base]) - 128.0f) / 128.0f;
        int16_t v = static_cast<int16_t>(pcm[base] | (pcm[base + 1] << 8));
        return static_cast<float>(v) / 32768.0f;
    };
    for (size_t d = 0; d < dst_frames; ++d) {
        // Source position in fixed point; frac weights the lerp partner.
        size_t pos = d * src_frames / dst_frames;
        size_t next = pos + 1 < src_frames ? pos + 1 : pos;
        float frac = dst_frames > 1
                         ? static_cast<float>(d * src_frames % dst_frames) /
                               static_cast<float>(dst_frames)
                         : 0.0f;
        for (int c = 0; c < 2; ++c) {
            int sc = src_channels == 1 ? 0 : c;  // mono fans out to both ears
            float v = sample_at(pos, sc) * (1.0f - frac) + sample_at(next, sc) * frac;
            out_stereo[d * 2 + static_cast<size_t>(c)] = float_to_s16(v);
        }
    }
}

// Decode a WAV-PCM blob to mix-ready S16 stereo. False for non-WAV blobs,
// non-PCM layouts, and formats owned by the future decoder (OGG/MP3 never
// route here; see detect_format + AUDIO-BACKEND.md).
inline bool decode_wav_s16(const uint8_t* bytes, size_t size,
                           std::vector<int16_t>& out_stereo) {
    out_stereo.clear();
    WavInfo info = parse_wav(bytes, size);
    if (!info.valid) return false;
    if (info.bits != 8 && info.bits != 16) return false;
    // Re-walk to the data payload: parse_wav validates, but the chunk walk
    // stays there so JUNK/LIST-bearing files still decode, not just parse.
    size_t pos = 12;
    auto u32 = [&](size_t o) -> uint32_t {
        return static_cast<uint32_t>(bytes[o] | (bytes[o + 1] << 8) |
                                     (bytes[o + 2] << 16) | (bytes[o + 3] << 24));
    };
    const uint8_t* pcm = nullptr;
    while (pos + 8 <= size) {
        uint32_t len = u32(pos + 4);
        size_t body = pos + 8;
        if (body + len > size) break;
        if (u32(pos) == 0x61746164u) {  // "data"
            pcm = bytes + body;
            break;
        }
        pos = body + len + (len & 1);
    }
    if (!pcm) return false;
    convert_to_mix_s16(pcm, info.frames, info.channels, info.sample_rate,
                       info.bits, out_stereo);
    return !out_stereo.empty();
}

// Decode a CNV audio blob (16-byte header + raw little-endian PCM, the
// FUN_00665020 path) to mix-ready S16 stereo. Layout mirrors
// tools/asset-tools/cnv_convert.py: u16 channels @0, u32 rate @4, u16 bits
// @14, payload @16 — convert_audio_cnv wraps these bytes straight into a WAV,
// so this decodes the same payload without the temp-file round trip.
inline bool decode_cnv_s16(const uint8_t* bytes, size_t size,
                           std::vector<int16_t>& out_stereo) {
    out_stereo.clear();
    if (detect_format(bytes, size) != BlobFormat::CnvPcm) return false;
    int ch = bytes[0] | (bytes[1] << 8);
    uint32_t rate = static_cast<uint32_t>(bytes[4] | (bytes[5] << 8) |
                                          (bytes[6] << 16) | (bytes[7] << 24));
    int bits = bytes[14] | (bytes[15] << 8);
    size_t bytes_per_frame = static_cast<size_t>(ch) * static_cast<size_t>(bits / 8);
    size_t payload = size - 16;
    if (payload == 0 || payload % bytes_per_frame != 0) return false;
    convert_to_mix_s16(bytes + 16, payload / bytes_per_frame, ch, rate, bits,
                       out_stereo);
    return !out_stereo.empty();
}

// Real Engine: SDL3 device at the game Spec, 32 SFX slot streams + 1 music
// stream, volume buses, web UnlockGate. SDL types stay in the .cpp (PIMPL)
// so this header keeps audio.h's no-SDL promise and tests without SDL linked.
class Sdl3Engine : public Engine {
public:
    // A null gate means always-ready (native); web passes a Gated gate and
    // unlocks it from the first input gesture. The gate outlives the engine.
    explicit Sdl3Engine(UnlockGate* gate = nullptr);
    ~Sdl3Engine() override;
    Sdl3Engine(const Sdl3Engine&) = delete;
    Sdl3Engine& operator=(const Sdl3Engine&) = delete;

    // Engine contract: opens the playback device at 44100 stereo (the device
    // resamples when hardware disagrees) and binds all 33 streams. Pushes
    // while the gate is closed are dropped, never queued, so web BGM starts
    // on gesture instead of arriving as one late burst.
    bool open(const Spec& spec) override;
    void close() override;
    bool is_open() const override;
    size_t push_music_s16(const int16_t* frames, size_t frame_count) override;
    void set_volumes(const Volumes& v) override;

    // Decoded-PCM SFX bank. Copies go in; playback streams them per slot, so
    // callers can free or reuse their buffers right after the call.
    SfxHandle load_pcm_s16(const int16_t* stereo_frames, size_t frame_count);
    SfxHandle load_wav(const uint8_t* bytes, size_t size);
    SfxHandle load_cnv(const uint8_t* bytes, size_t size);
    void clear_bank();

    // Fire a loaded buffer. req.channel >= 0 plays exactly there (returns -1
    // when out of range, busy, or the handle is stale); otherwise the first
    // free slot in the bus range. Full bus returns -1 (backpressure like the
    // music push) rather than stealing a live voice. Gated drops, as above.
    int play(SfxHandle h, SfxBus bus, const PlayRequest& req = PlayRequest{});
    void stop(int channel);
    void stop_all_sfx();
    bool channel_busy(int channel) const;

    // Observability for tests and the future --audio-test wiring.
    size_t music_queued_frames() const;
    size_t sfx_queued_frames(int channel) const;
    float music_gain() const;                 // last applied music-stream gain
    float bus_gain_applied(SfxBus bus) const;  // last applied per-bus gain
    const Volumes& volumes() const { return volumes_; }
    size_t bank_size() const;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
    UnlockGate* gate_;  // not owned; null means always ready
    Volumes volumes_;
};

}  // namespace fnd::audio
