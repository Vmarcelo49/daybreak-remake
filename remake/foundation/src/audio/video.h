#pragma once
// Video decision for Track M: STUB, explicitly.
//
// Why a stub and not a port: the remake plays movie/*.mpg (MPEG-PS: MPEG1
// video + MP2 audio) through pl_mpeg into a DX9 texture with SDL_mixer
// audio. Carrying that to the foundation means vendoring ~4300 lines of
// pl_mpeg, writing a new WebGPU texture-upload path, and solving web
// delivery of copyrighted .mpg bytes (Track W owns that question) — all for
// a boot movie that is skippable on any button. The D2 gate is a matching
// in-game frame, which never needs video. So video waits: this header pins
// the probe math and the future interface shape, and the player reports
// Unimplemented instead of silently dropping the movie.

#include <cstddef>
#include <cstdint>

namespace fnd::video {

// MPEG-PS pack start code 0x000001BA. Enough to route a blob to the movie
// path vs the audio path; full demux stays with the future decoder.
inline bool is_mpeg_ps(const uint8_t* bytes, size_t size) {
    return bytes && size >= 4 && bytes[0] == 0x00 && bytes[1] == 0x00 &&
           bytes[2] == 0x01 && bytes[3] == 0xBA;
}

enum class Status {
    Closed,
    Unimplemented,  // open() called: movie path recognised, decoder absent
    Playing,
    Finished,
};

// Placeholder player. open() accepts an MPEG-PS blob so callers wire the
// real call sites now; it always lands on Unimplemented so nobody mistakes
// the boot movie for working. Skippability (any button ends playback) is
// part of the contract because the original boots through op.mpg that way.
class StubPlayer {
public:
    bool open(const uint8_t* bytes, size_t size) {
        if (!is_mpeg_ps(bytes, size)) return false;
        status_ = Status::Unimplemented;
        return true;  // recognised, not playable — see status()
    }
    void close() { status_ = Status::Closed; }
    Status status() const { return status_; }
    bool skippable() const { return true; }

private:
    Status status_ = Status::Closed;
};

// BT.601 full-range YCrCb->RGB kept here (not in a .cpp) so the future
// decoder reuses tested math for the WebGPU texture upload instead of
// re-deriving it. pl_mpeg's plm_frame_to_bgra targets BGRA byte order; the
// foundation uploads RGBA, hence R/G/B order here.
inline void ycrcb_to_rgb(uint8_t y, uint8_t cr, uint8_t cb, uint8_t& r,
                         uint8_t& g, uint8_t& b) {
    float fy = static_cast<float>(y);
    float fcr = static_cast<float>(cr) - 128.0f;
    float fcb = static_cast<float>(cb) - 128.0f;
    auto clamp8 = [](float v) -> uint8_t {
        if (v < 0.0f) return 0;
        if (v > 255.0f) return 255;
        return static_cast<uint8_t>(v + 0.5f);
    };
    r = clamp8(fy + 1.402f * fcr);
    g = clamp8(fy - 0.344136f * fcb - 0.714136f * fcr);
    b = clamp8(fy + 1.772f * fcb);
}

}  // namespace fnd::video
