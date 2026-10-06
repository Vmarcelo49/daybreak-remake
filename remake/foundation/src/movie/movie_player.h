#pragma once
// The opening/staff-roll movie player: MPEG-PS -> RGBA frames + PCM audio (issue #40).
//
// Recovered shape (original DaybreakDX.exe, md5 a136ddc01bd7ef355b759b88ac89e02c, read
// through the Ghidra bridge; the corpus copy in research/decompiled/ is a PATCHED build
// and agrees on all of it here):
//
//   * the opening scene is screen id 0x00, constructed by FUN_00404eb0 @0x404eb0
//     (research/decompiled/FUN_00404eb0.c:32-39): it opens "movie/op.mpg", configures a
//     640x480 blit and calls FUN_00408250(0x3fa00000) = 1.25f. 0x3fa00000 is float 1.25
//     and FUN_00408250 @0x408250 writes it to sprite+0x84/+0x88, the two scale fields
//     ui::SpriteRenderer::pushSprite documents (ui/sprite.h:277) — so the movie is drawn
//     640x480 * 1.25 = 800x600, i.e. exactly the port's menu canvas, and its own black
//     bars are inside the video (remake/docs/reference/README.md:42).
//   * the same constructor's update is vtable slot 3 of 0x6a14ec = FUN_00404ff0
//     @0x404ff0; its skip/exit machine is transcribed in ui/screen_opening.cpp.
//
// What this class deliberately is NOT: no media framework, no background thread, no
// plane/shader path, no decoder abstraction. pl_mpeg is one header; the player is one
// class with one job, and the UI renderer's existing RGBA texture upload
// (SpriteRenderer::updateTexture) is the whole GPU side.
//
// PORT RULE (web): pl_mpeg is not used in the wasm build at all — a browser has to
// decode through an HTMLVideoElement/WebCodecs and hand the frame over with
// copyExternalImageToTexture, which needs the movie served as a URL (issue #4's asset
// delivery). MoviePlayer compiles to a stub that reports that, so the web target keeps
// building and never silently pretends a movie played (see the .cpp).

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace fnd::movie {

// 44.1 kHz stereo S16 — what fnd::audio::Sdl3Engine plays. The push feeds the player's
// own engine instance; see ui/screen_opening.h for why the movie gets its own.
using AudioPush = std::function<size_t(const int16_t*, size_t)>;

class MoviePlayer {
  public:
    MoviePlayer() = default;
    ~MoviePlayer();
    MoviePlayer(const MoviePlayer&) = delete;
    MoviePlayer& operator=(const MoviePlayer&) = delete;

    // Opens `path` and probes the stream. False (with `error`) when the file is missing
    // or is not an MPEG-1 program stream this decoder can play: pl_mpeg reports neither,
    // so the sequence header is validated here rather than presenting 90 seconds of black
    // (issue #40's error-handling requirement). `push` may be null (silent playback); the
    // return value is the frames the sink accepted, for the A/V accounting.
    bool open(const std::string& path, AudioPush push, std::string& error);
    void close();

    // Advances playback by `dt` seconds of wall time, decodes what is due within it,
    // converts the newest due frame to RGBA and feeds audio. Mirrors the recovered loop
    // (FUN_00404ff0 @0x404ff0): decode every tick, the decoder's own frame clock decides
    // what is presented.
    void update(double dt);

    bool playing() const { return open_ && !ended_; }
    // The recovered exit condition (FUN_00405250 @0x405250): the stream ended on its own.
    bool finished() const { return open_ && ended_; }
    const std::string& error() const { return error_; }
    // One line naming what was opened, for the startup/evidence log.
    std::string describeFormat() const;

    int width() const { return width_; }
    int height() const { return height_; }
    double frameRate() const { return frameRate_; }
    double duration() const { return duration_; }

    // RGBA8, top-down, `width() * height() * 4` bytes; empty before the first frame.
    // Valid until the next update().
    const uint8_t* framePixels() const { return rgba_.empty() ? nullptr : rgba_.data(); }
    // The presented frame's own timestamp — pl_mpeg drives it from the sequence header's
    // frame rate, because the container's PTS is ignored (pl_mpeg README, "Limitations").
    double frameTime() const { return frameTime_; }
    // The decoder's playback clock after the last update, for the sync readout.
    double decodeTime() const { return decodeTime_; }

    uint64_t framesDecoded() const { return framesDecoded_; }
    uint64_t framesPresented() const { return framesPresented_; }
    size_t audioFramesPushed() const { return audioFramesPushed_; }

  private:
    void convertToRgba(const void* frame);
    void feedAudio(const float* interleaved, int count);

    void* plm_ = nullptr;   // plm_t* — pl_mpeg stays out of this header
    AudioPush push_;
    std::string error_;

    int width_ = 0, height_ = 0;
    double frameRate_ = 0.0, duration_ = 0.0;
    double decodeTime_ = 0.0, frameTime_ = 0.0;
    uint64_t audioFrames_ = 0;            // PCM frames the decoder produced
    uint64_t framesDecoded_ = 0;
    uint64_t framesPresented_ = 0;
    size_t audioFramesPushed_ = 0;
    bool open_ = false, ended_ = false;
    std::vector<uint8_t> rgba_;
    std::vector<int16_t> audio_;
};

// The two movies the install ships. The original passes the literal "movie/op.mpg" to
// FUN_0065c080 (FUN_00404eb0 @0x404eb0, string at 0x6cfbe5) because it has already made
// data/ its working directory — the file on disk is data/movie/op.mpg, and every other
// asset path the exe builds is data/-rooted ("data/bgm/title.ogg" at 0x6a14c0). These are
// install-relative paths, which is what AssetSource::resolve resolves.
inline constexpr const char* kOpeningMovie = "data/movie/op.mpg";
inline constexpr const char* kStaffRollMovie = "data/movie/staffroll.mpg";

// How far decoded audio runs ahead of the drawn frame. Not a recovered number: the
// original's DirectShow graph owned both clocks, so the port has to pick one, and
// pl_mpeg's own default for it. Exposed because the A/V evidence quotes it.
inline constexpr double kAudioLeadSeconds = 0.25;
// The largest wall-clock step one update() turns into decoding — a suspended window must
// not come back as a multi-second decode burst.
inline constexpr double kMaxStepSeconds = 0.25;
// pl_mpeg decodes MP2 at the file's own rate and the engine plays 44100; every shipped
// movie is 44100 stereo (ffprobe), and a movie that is not is resampled by the device.
inline constexpr int kAudioRate = 44100;

}  // namespace fnd::movie
