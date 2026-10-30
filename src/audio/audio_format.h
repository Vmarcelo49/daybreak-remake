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
#include <cstdio>
#include <string>
#include <vector>

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

struct SflLoop {
    bool     valid = false;
    uint32_t startSample = 0;  // loop start, in file-rate samples
    uint32_t endSample = 0;    // loop end (exclusive), same units
};

// Loop points for a BGM track, from its sibling .sfl file. The shipped files
// are RIFF 'SFPL' sheets: a 'cue ' chunk whose first point carries the loop
// start as a sample offset, plus an adtl 'labl' chunk naming the region in
// text ("Region 00:00:06.741 to 00:01:30.221"). Both name the same region —
// the cue offset is authoritative for the start (exact samples, no float
// round-trip) and the label for the end — and every shipped pair agrees, so
// a mismatch fails the parse rather than silently looping the wrong bars.
// fileRate converts the label times to samples; it is the decoded audio's
// rate (44100 on every shipped track).
inline SflLoop parse_sfl_loop(const uint8_t* bytes, size_t size, uint32_t fileRate) {
    SflLoop out;
    if (!bytes || size < 12 || fileRate == 0) return out;
    auto u32 = [&](size_t o) -> uint32_t {
        return static_cast<uint32_t>(bytes[o] | (bytes[o + 1] << 8) |
                                     (bytes[o + 2] << 16) | (bytes[o + 3] << 24));
    };
    if (!(bytes[0] == 'R' && bytes[1] == 'I' && bytes[2] == 'F' && bytes[3] == 'F' &&
          bytes[8] == 'S' && bytes[9] == 'F' && bytes[10] == 'P' && bytes[11] == 'L'))
        return out;
    bool haveCue = false, haveLabel = false;
    uint32_t cueStart = 0, labelStartMs = 0, labelEndMs = 0;
    size_t pos = 12;
    // Walk top-level chunks; LIST/adtl is descended one level for labl chunks.
    // A small fixed bound keeps a corrupt length field from looping forever.
    for (int guard = 0; guard < 64 && pos + 8 <= size; ++guard) {
        uint32_t chunk = u32(pos), len = u32(pos + 4), body = pos + 8;
        if (body + len > size) break;
        if (chunk == 0x20657563u) {  // "cue "
            if (len >= 4 && u32(body) >= 1 && body + 4 + 24 <= size) {
                cueStart = u32(body + 4 + 20);  // first point's sample offset
                haveCue = true;
            }
        } else if (chunk == 0x5453494cu) {  // "LIST"
            if (len >= 4 && bytes[body] == 'a' && bytes[body + 1] == 'd' &&
                bytes[body + 2] == 't' && bytes[body + 3] == 'l') {
                size_t sub = body + 4, subEnd = body + len;
                for (int sg = 0; sg < 64 && sub + 8 <= subEnd && sub + 8 <= size; ++sg) {
                    uint32_t schunk = u32(sub), slen = u32(sub + 4), sbody = sub + 8;
                    if (sbody + slen > size || sbody + slen > subEnd) break;
                    if (schunk == 0x6c62616cu && slen >= 4) {  // "labl"
                        // Text is "Region HH:MM:SS.mmm to HH:MM:SS.mmm"; parse
                        // both timestamps rather than trusting any binary end
                        // field, because the shipped sheets carry the end only
                        // in text.
                        unsigned sh = 0, sm = 0, ss = 0, sms = 0;
                        unsigned eh = 0, em = 0, es = 0, ems = 0;
                        const char* t = (const char*)bytes + sbody + 4;
                        size_t tlen = slen - 4;
                        // Bounded scan: the label is short; never read past it.
                        // Eight conversions, no trailing %c: the label's NUL
                        // terminator ends sscanf input rather than matching.
                        for (size_t i = 0; i + 7 < tlen; ++i) {
                            if (std::sscanf(t + i, "Region %u:%u:%u.%u to %u:%u:%u.%u",
                                            &sh, &sm, &ss, &sms, &eh, &em, &es, &ems) == 8) {
                                labelStartMs = ((sh * 60 + sm) * 60 + ss) * 1000 + sms;
                                labelEndMs = ((eh * 60 + em) * 60 + es) * 1000 + ems;
                                haveLabel = true;
                                break;
                            }
                        }
                    }
                    sub = sbody + slen + (slen & 1);
                }
            }
        }
        pos = body + len + (len & 1);
    }
    if (!haveCue || !haveLabel) return out;
    const uint32_t endSample =
        (uint32_t)(((uint64_t)labelEndMs * fileRate + 500) / 1000);
    const uint32_t labelStart =
        (uint32_t)(((uint64_t)labelStartMs * fileRate + 500) / 1000);
    // The two start readings name the same bar; beyond one second of drift
    // something is off, and looping the wrong region is worse than no loop.
    uint32_t drift = cueStart > labelStart ? cueStart - labelStart : labelStart - cueStart;
    if (endSample <= cueStart || drift > fileRate) return out;
    out.valid = true;
    out.startSample = cueStart;
    out.endSample = endSample;
    return out;
}

// A track's loop sheet (.sfl), resolved. The sheet is optional and the original
// plays without it: FUN_00668820 — which FUN_006683d0 calls at the end of its
// success path, i.e. only after the track itself opened — first writes the
// stream's loop start/end fields (+0x12e8, +0x12f0) from the constant at
// 0x6a5630, reads as eight zero bytes = double 0.0 (the same initialiser as the
// literal 0 in the first-pass dump, research/decompiled/FUN_00668820.c:24-25),
// then rewrites the path's last three characters to "sfl" and only parses
// cue/adtl when FUN_00653540 reports the sheet exists. No sheet therefore leaves
// a zero-length loop region: the track plays once to EOF and nothing fails.
enum class LoopSheet {
    Parsed,      // cue/adtl read; `loop` carries the region
    Absent,      // no sibling sheet: no loop region (recovered behaviour)
    Unparsable,  // sheet present, cue/adtl unusable (port rule: only reported)
};

struct LoopSheetResult {
    LoopSheet   status = LoopSheet::Absent;
    SflLoop     loop;  // set only when status == Parsed
    std::string note;  // non-empty only when status == Unparsable
};

// Sibling .sfl path for `trackPath`, or "" when the path carries no extension.
// The original does not look for a dot — it overwrites the last three
// characters outright — so replacing a known extension is the port's rule:
// a path without one can then only mean "no sheet", never a mangled probe.
inline std::string loop_sheet_path(const std::string& trackPath) {
    const size_t dot = trackPath.find_last_of('.');
    const size_t sep = trackPath.find_last_of("/\\");
    if (dot == std::string::npos || (sep != std::string::npos && dot < sep))
        return std::string();
    return trackPath.substr(0, dot) + ".sfl";
}

// Resolves `trackPath`'s loop sheet through `read(path, out)`, which returns
// false when the sheet is not there. A track with no usable sheet is a success
// with no loop region, not a load failure — the original distinguishes absent
// from unparsable nowhere and is silent in both cases, so telling them apart
// here (status + note) is a PORT RULE for diagnosing a corrupt install.
//
// Callers must apply the result to the player either way: a LoopPlayer reused
// across tracks keeps its previous region (set_source resets position and wrap
// count only), so a track without a sheet has to clear it explicitly.
template <typename ReadFn>
inline LoopSheetResult resolve_loop_sheet(const std::string& trackPath, uint32_t fileRate,
                                          ReadFn&& read) {
    LoopSheetResult out;
    const std::string sflPath = loop_sheet_path(trackPath);
    std::vector<uint8_t> bytes;
    if (sflPath.empty() || !read(sflPath, bytes)) return out;  // Absent: no loop region
    out.loop = parse_sfl_loop(bytes.data(), bytes.size(), fileRate);
    if (out.loop.valid) {
        out.status = LoopSheet::Parsed;
        return out;
    }
    out.status = LoopSheet::Unparsable;
    out.note = "unparsable loop sheet " + sflPath;
    return out;
}

}  // namespace fnd::audio
