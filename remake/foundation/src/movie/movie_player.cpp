// The movie player (pl_mpeg -> RGBA + PCM). Header carries the recovered provenance.
//
// Platform split: pl_mpeg is a native decoder and the native build uses it; the web
// build compiles the stub at the bottom instead, because a browser decodes video itself
// and the port must not carry a second, silent decoder into wasm (issue #40's web note).
#include "movie/movie_player.h"

#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>

#include "audio/audio_format.h"

#if !defined(__EMSCRIPTEN__)

// pl_mpeg is one header plus one translation unit's worth of implementation: this is the
// only file in the tree that defines PL_MPEG_IMPLEMENTATION (dependency: fetch_deps.sh).
#define PL_MPEG_IMPLEMENTATION
#include "pl_mpeg.h"

namespace fnd::movie {
namespace {

// The stream check pl_mpeg itself cannot make (it "will silently ignore any invalid
// data"): an MPEG-PS has to start with a pack start code, and the sequence header's
// width/height are what the surface and the texture are sized from. A missing or
// non-MPEG-2-free stream must fail here rather than present black for its whole length.
bool readHeaderAndValidate(const std::string& path, int& width, int& height,
                           std::string& error) {
    FILE* f = std::fopen(path.c_str(), "rb");
    if (!f) {
        error = "cannot open " + path;
        return false;
    }
    unsigned char head[8] = {};
    const size_t got = std::fread(head, 1, sizeof(head), f);
    std::fclose(f);
    if (got < 4 || head[0] != 0x00 || head[1] != 0x00 || head[2] != 0x01 || head[3] != 0xBA) {
        error = path + ": not an MPEG program stream (no pack start code; expected MPEG-1 "
                      "system multiplex with MPEG-1 video and MP2 audio)";
        return false;
    }
    plm_t* probe = plm_create_with_filename(path.c_str());
    if (!probe) {
        error = "cannot decode " + path;
        return false;
    }
    const int w = plm_get_width(probe);
    const int h = plm_get_height(probe);
    plm_destroy(probe);
    if (w <= 0 || h <= 0 || w > 4096 || h > 4096) {
        // pl_mpeg decodes MPEG-1 and does not test the sequence header's version bits, so an
        // MPEG-2 stream can pass this check and then decode partially or not at all; what this
        // rejects is a file with no usable sequence header, which is the case that used to
        // present as a silent black screen for the movie's whole length.
        error = path + ": no MPEG-1 sequence header (not an MPEG-1 video stream, or a "
                      "stream this decoder cannot read)";
        return false;
    }
    width = w;
    height = h;
    return true;
}

// YCrCb -> RGBA. The 4:2:0 replication, the >>1 truncation for odd dimensions and the
// BT.601 integer chroma matrix are pl_mpeg's own (pl_mpeg.h's
// PLM_DEFINE_FRAME_CONVERT_FUNCTION); what differs is the luma range.
//
// pl_mpeg's converter treats Y as full range (its own 1.16438 row in the header's GLSL
// matrix is the only hint that it is not), but an MPEG-1 stream is limited range: Y in
// [16,235], chroma in [16,240]. Measured against ffmpeg on this install's op.mpg frame
// 100, full range differs from the reference decode by mean |d| = 13.03 per channel and
// this expansion by 5.20 (max 71, the rest being chroma upsampling — ffmpeg interpolates,
// pl_mpeg replicates). The whole movie is that much too dark and flat without it.
// Done on the CPU rather than in a shader because the UI layer already owns exactly this
// upload: one RGBA texture, no second pipeline.
void convertFrameToRgba(const plm_frame_t& frame, std::vector<uint8_t>& out) {
    const int cols = frame.width >> 1;
    const int rows = frame.height >> 1;
    const int yw = frame.y.width;
    const int cw = frame.cb.width;
    uint8_t* dst = out.data();
    for (int row = 0; row < rows; ++row) {
        const uint8_t* cr_row = frame.cr.data + row * cw;
        const uint8_t* cb_row = frame.cb.data + row * cw;
        const uint8_t* y0 = frame.y.data + row * 2 * yw;
        const uint8_t* y1 = y0 + yw;
        for (int col = 0; col < cols; ++col) {
            const int cr = (int)cr_row[col] - 128;
            const int cb = (int)cb_row[col] - 128;
            // Chroma gain 255/224 folded into pl_mpeg's coefficients.
            const int r_add = (cr * 104597) >> 16;
            const int g_add = (cb * 25674 + cr * 53278) >> 16;
            const int b_add = (cb * 132201) >> 16;
            const uint8_t* ys[2] = {y0 + col * 2, y1 + col * 2};
            for (int half = 0; half < 2; ++half) {
                for (int side = 0; side < 2; ++side) {
                    // (Y - 16) * 255/219, rounded.
                    const int y = (((int)ys[half][side] - 16) * 255 + 109) / 219;
                    const int yc = y < 0 ? 0 : (y > 255 ? 255 : y);
                    uint8_t* p = dst + ((row * 2 + half) * frame.width + col * 2 + side) * 4;
                    const int r = yc + r_add;
                    const int g = yc + g_add;
                    const int b = yc + b_add;
                    p[0] = (uint8_t)(r < 0 ? 0 : r > 255 ? 255 : r);
                    p[1] = (uint8_t)(g < 0 ? 0 : g > 255 ? 255 : g);
                    p[2] = (uint8_t)(b < 0 ? 0 : b > 255 ? 255 : b);
                    p[3] = 255;
                }
            }
        }
    }
}

}  // namespace

void MoviePlayer::close() {
    if (plm_) plm_destroy(static_cast<plm_t*>(plm_));
    plm_ = nullptr;
    push_ = nullptr;
    open_ = ended_ = false;
    decodeTime_ = frameTime_ = 0.0;
    width_ = height_ = 0;
    frameRate_ = duration_ = 0.0;
    audioFrames_ = framesDecoded_ = framesPresented_ = 0;
    audioFramesPushed_ = 0;
    rgba_.clear();
    audio_.clear();
    error_.clear();
}

MoviePlayer::~MoviePlayer() { close(); }

bool MoviePlayer::open(const std::string& path, AudioPush push, std::string& error) {
    close();
    int w = 0, h = 0;
    if (!readHeaderAndValidate(path, w, h, error)) return false;
    plm_t* plm = plm_create_with_filename(path.c_str());
    if (!plm) {
        error = "cannot decode " + path;
        return false;
    }
    plm_ = plm;
    push_ = std::move(push);
    width_ = w;
    height_ = h;
    frameRate_ = plm_get_framerate(plm);
    duration_ = plm_get_duration(plm);

    plm_set_video_enabled(plm, 1);
    plm_set_audio_enabled(plm, 1);
    // Audio has to run AHEAD of video: its samples are consumed by the output device while
    // video frames are only drawn. pl_mpeg calls this "audio lead time" and it is the
    // library's own answer to the container's ignored PTS (pl_mpeg README, "Limitations").
    plm_set_audio_lead_time(plm, kAudioLeadSeconds);
    // The high-level interface with no callbacks does not decode at all (plm_decode
    // returns immediately), so both are installed even though the frame arrives through a
    // member and the samples are pushed straight to the sink.
    plm_set_video_decode_callback(
        plm, [](plm_t*, plm_frame_t* frame, void* user) {
            static_cast<MoviePlayer*>(user)->convertToRgba(frame);
        },
        this);
    plm_set_audio_decode_callback(
        plm, [](plm_t*, plm_samples_t* samples, void* user) {
            static_cast<MoviePlayer*>(user)->feedAudio(samples->interleaved, samples->count);
        },
        this);

    rgba_.assign((size_t)width_ * (size_t)height_ * 4, 0);
    open_ = true;
    return true;
}

void MoviePlayer::update(double dt) {
    if (!open_ || ended_) return;
    plm_t* plm = static_cast<plm_t*>(plm_);
    // A stalled wall clock (a debugger, a suspended window) must not become a decode
    // burst: the decoder catches up at its own rate, one frame per tick at worst.
    if (dt > kMaxStepSeconds) dt = kMaxStepSeconds;
    plm_decode(plm, dt);
    decodeTime_ = plm_get_time(plm);
    if (plm_has_ended(plm)) ended_ = true;
}

void MoviePlayer::convertToRgba(const void* frame_ptr) {
    const plm_frame_t& frame = *static_cast<const plm_frame_t*>(frame_ptr);
    ++framesDecoded_;
    if ((int)frame.width != width_ || (int)frame.height != height_) return;
    convertFrameToRgba(frame, rgba_);
    frameTime_ = frame.time;
    ++framesPresented_;
}

void MoviePlayer::feedAudio(const float* interleaved, int count) {
    // pl_mpeg always hands over PLM_AUDIO_SAMPLES_PER_FRAME interleaved stereo pairs.
    if (count <= 0) return;
    audioFrames_ += (uint64_t)count;
    audio_.resize((size_t)count * 2);
    for (int i = 0; i < count * 2; ++i) audio_[(size_t)i] = fnd::audio::float_to_s16(interleaved[i]);
    if (push_) audioFramesPushed_ += push_(audio_.data(), (size_t)count);
}

std::string MoviePlayer::describeFormat() const {
    if (!open_) return error_;
    char text[160];
    std::snprintf(text, sizeof(text),
                  "MPEG-1 system multiplex, %dx%d, %.2f fps, %.2f s, MP2 %.0f Hz stereo",
                  width_, height_, frameRate_, duration_, (double)kAudioRate);
    return text;
}

}  // namespace fnd::movie

#else  // __EMSCRIPTEN__: the browser decodes, the port does not

namespace fnd::movie {

void MoviePlayer::close() {
    plm_ = nullptr;
    push_ = nullptr;
    open_ = ended_ = false;
    error_.clear();
}

MoviePlayer::~MoviePlayer() { close(); }

bool MoviePlayer::open(const std::string& path, AudioPush push, std::string& error) {
    (void)path;
    (void)push;
    // PORT RULE (web): the movie is decoded by the browser, not by wasm. That path is an
    // HTMLVideoElement (or WebCodecs) feeding copyExternalImageToTexture, and it needs the
    // .mpg served as a URL — issue #4's asset delivery, not this player's business. Until
    // that exists the web build reports the gap instead of decoding nothing in silence.
    error = "the web build does not decode movies in wasm: the browser must play them "
            "(HTMLVideoElement/WebCodecs); see remake/foundation/docs/MEDIA-INPUT.md";
    open_ = false;
    return false;
}

void MoviePlayer::update(double dt) { (void)dt; }
void MoviePlayer::convertToRgba(const void*) {}
void MoviePlayer::feedAudio(const float*, int) {}

std::string MoviePlayer::describeFormat() const { return error_; }

}  // namespace fnd::movie

#endif
