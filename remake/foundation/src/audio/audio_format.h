#pragma once
// Format/stream helpers for Track M.
//
// Why this file exists: the remake reads WAV/OGG/MP3 bytes plus CNV-wrapped
// PCM and MPEG-PS movie audio, but decoding itself is a backend job. What the
// foundation needs first is deterministic: identify a blob, describe a WAV
// header, convert decoded floats to the S16 stereo the stream drains, and
// account chunk-queue drains without touching SDL. All functions here are
// pure so they unit-test without an audio device.

#include <cstddef>
#include <cstdint>

namespace fnd::audio {

// What the remake reference actually carries (see MEDIA-INPUT.md inventory).
enum class BlobFormat {
    Unknown,
    Wav,     // RIFF....WAVE — data/voice/entry/*.wav, CNV-converted SFX
    Ogg,     // OggS — data/bgm/*.ogg BGM tracks
    Mp3,     // ID3 or frame sync — accepted by the remake's mixer path
    MpegPs,  // 0x000001BA pack start — movie/*.mpg program streams
    CnvPcm,  // CNV audio header (FUN_00665020 path): raw PCM after 16 bytes
};

// Magic-byte sniff. MP3 detection stays conservative on purpose: bare 0xFF
// frame syncs false-positive on arbitrary blobs, so only ID3 counts here and
// sync-bar streams fall through to Unknown rather than misrouting.
inline BlobFormat detect_format(const uint8_t* bytes, size_t size) {
    if (!bytes || size < 4) return BlobFormat::Unknown;
    if (size >= 12 && bytes[0] == 'R' && bytes[1] == 'I' && bytes[2] == 'F' &&
        bytes[3] == 'F' && bytes[8] == 'W' && bytes[9] == 'A' &&
        bytes[10] == 'V' && bytes[11] == 'E')
        return BlobFormat::Wav;
    if (bytes[0] == 'O' && bytes[1] == 'g' && bytes[2] == 'g' && bytes[3] == 'S')
        return BlobFormat::Ogg;
    if (size >= 3 && bytes[0] == 'I' && bytes[1] == 'D' && bytes[2] == '3')
        return BlobFormat::Mp3;
    if (bytes[0] == 0x00 && bytes[1] == 0x00 && bytes[2] == 0x01 &&
        bytes[3] == 0xBA)
        return BlobFormat::MpegPs;
    // CNV audio header: channels(1-2), reserved==1, rate in {22050,44100,48000},
    // bits in {8,16} — mirrors tools/asset-tools/cnv_convert.py is_audio_cnv.
    if (size >= 16) {
        uint16_t ch = static_cast<uint16_t>(bytes[0] | (bytes[1] << 8));
        uint16_t reserved = static_cast<uint16_t>(bytes[2] | (bytes[3] << 8));
        uint32_t rate = static_cast<uint32_t>(bytes[4] | (bytes[5] << 8) |
                                              (bytes[6] << 16) | (bytes[7] << 24));
        uint16_t bits = static_cast<uint16_t>(bytes[14] | (bytes[15] << 8));
        if ((ch == 1 || ch == 2) && reserved == 1 &&
            (rate == 22050 || rate == 44100 || rate == 48000) &&
            (bits == 8 || bits == 16))
            return BlobFormat::CnvPcm;
    }
    return BlobFormat::Unknown;
}

struct WavInfo {
    bool valid = false;
    uint16_t channels = 0;
    uint32_t sample_rate = 0;
    uint16_t bits = 0;
    uint32_t data_bytes = 0;
    uint32_t frames = 0;  // data_bytes / block_align, 0 when header is bogus
};

// Minimal RIFF walk: "fmt " gives the layout, "data" gives the payload size.
// Unknown chunks are skipped so JUNK/LIST-bearing files still parse; only
// PCM (format 1) counts because every game WAV the reference loads is PCM.
inline WavInfo parse_wav(const uint8_t* bytes, size_t size) {
    WavInfo out;
    if (detect_format(bytes, size) != BlobFormat::Wav || size < 44) return out;
    auto u16 = [&](size_t o) -> uint32_t {
        return static_cast<uint32_t>(bytes[o] | (bytes[o + 1] << 8));
    };
    auto u32 = [&](size_t o) -> uint32_t {
        return static_cast<uint32_t>(bytes[o] | (bytes[o + 1] << 8) |
                                     (bytes[o + 2] << 16) | (bytes[o + 3] << 24));
    };
    size_t pos = 12;  // past "RIFF....WAVE"
    uint16_t fmt_tag = 0, channels = 0, bits = 0;
    uint32_t rate = 0, data_bytes = 0;
    bool have_fmt = false, have_data = false;
    while (pos + 8 <= size) {
        uint32_t chunk = u32(pos);
        uint32_t len = u32(pos + 4);
        size_t body = pos + 8;
        if (body + len > size) break;  // truncated tail: stop, keep what we have
        if (chunk == 0x20746D66u) {    // "fmt "
            if (len >= 16) {
                fmt_tag = static_cast<uint16_t>(u16(body));
                channels = static_cast<uint16_t>(u16(body + 2));
                rate = u32(body + 4);
                bits = static_cast<uint16_t>(u16(body + 14));
                have_fmt = true;
            }
        } else if (chunk == 0x61746164u) {  // "data"
            data_bytes = len;
            have_data = true;
        }
        pos = body + len + (len & 1);  // chunks pad to even sizes
    }
    if (!have_fmt || !have_data || fmt_tag != 1 || channels == 0 || bits == 0)
        return out;
    uint32_t block = static_cast<uint32_t>(channels) * bits / 8;
    if (block == 0) return out;
    out.valid = true;
    out.channels = channels;
    out.sample_rate = rate;
    out.bits = bits;
    out.data_bytes = data_bytes;
    out.frames = data_bytes / block;
    return out;
}

// pl_mpeg hands movie audio over as float[-1,1]; the SDL3 stream drains S16.
// Clamping (not wrapping) is what keeps overdriven samples a click instead of
// a full-scale snap.
inline int16_t float_to_s16(float v) {
    if (v > 1.0f) v = 1.0f;
    if (v < -1.0f) v = -1.0f;
    return static_cast<int16_t>(v * 32767.0f);
}

// How many bytes a stream callback consuming `want` bytes takes from a queue
// of `count` chunks with a read offset into the head chunk. Pure so the drain
// accounting tests without a device; the SDL3 callback itself just memcpys.
inline size_t drain_bytes(const size_t* chunk_sizes, size_t count,
                          size_t head_offset, size_t want) {
    size_t total = 0;
    for (size_t i = 0; i < count; ++i) total += chunk_sizes[i];
    if (head_offset >= total) return 0;
    size_t avail = total - head_offset;
    return want < avail ? want : avail;
}

// Mixer-style 0..128 volume to linear gain. Out-of-range inputs clamp because
// the option sliders feed this from config.dat and must never invert phase.
inline float volume_gain(int volume_0_128) {
    if (volume_0_128 < 0) volume_0_128 = 0;
    if (volume_0_128 > 128) volume_0_128 = 128;
    return static_cast<float>(volume_0_128) / 128.0f;
}

}  // namespace fnd::audio
