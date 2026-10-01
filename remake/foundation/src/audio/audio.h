#pragma once
// Backend-agnostic audio interface for Track M.
//
// Why a tiny interface instead of wiring SDL3 directly: the remake's engine
// is SDL2_mixer (Mix_Chunk/Mix_Music, temp-file loads, Mix_HookMusic for movie
// audio), which does not exist on the foundation's SDL3/web targets. The game
// needs SFX slots + one streamed BGM + streamed movie audio; this header pins
// that contract so the SDL3 backend (audio_sdl3.h) can land behind it without
// gameplay code depending on SDL. No SDL include here keeps this testable.

#include <cstddef>
#include <cstdint>

namespace fnd::audio {

// The mix target everything in the inventory already is (OGG BGM at 44100,
// MP2 movie audio at 44100, WAV/CNV voice at 22050/44100/48000). The SDL3
// stream resamples when the device disagrees, so sources convert once here.
struct Spec {
    uint32_t sample_rate = 44100;
    uint16_t channels = 2;  // stereo everywhere: BGM, movie, voice cues
    uint16_t frames_per_callback = 2048;  // matches the remake's Mix_OpenAudio buffer
};

// Mirrors the remake's reservation so gameplay porting keeps its channel math:
// channel 0 UI, 1-15 voice cues, 16-31 gameplay SFX, plus one music stream.
inline constexpr int kMaxSfxChannels = 32;
inline constexpr int kUiChannel = 0;
inline constexpr int kVoiceFirst = 1;
inline constexpr int kVoiceLast = 15;
inline constexpr int kSfxFirst = 16;
inline constexpr int kSfxLast = 31;

inline constexpr bool is_voice_channel(int ch) {
    return ch >= kVoiceFirst && ch <= kVoiceLast;
}

// Four sliders on the option screen (master/music/voice/SFX), each 0..100 in
// the UI. Effective gain multiplies master with the bus so muting master
// silences everything without losing per-bus settings.
struct Volumes {
    int master = 100;
    int music = 100;
    int voice = 100;
    int sfx = 100;
};

inline float bus_gain(int ui_0_100, int master_0_100) {
    auto clamp = [](int v) { return v < 0 ? 0 : (v > 100 ? 100 : v); };
    return (static_cast<float>(clamp(ui_0_100)) / 100.0f) *
           (static_cast<float>(clamp(master_0_100)) / 100.0f);
}

// Browser autoplay: the web AudioContext starts suspended and the first sound
// must follow a user gesture. Native targets leave the gate open; the web
// backend starts gated and flips on the first input event (see audio_sdl3.h).
enum class UnlockState { Unlocked, Gated };

class UnlockGate {
public:
    explicit UnlockGate(UnlockState initial) : state_(initial) {}
    bool ready() const { return state_ == UnlockState::Unlocked; }
    void unlock() { state_ = UnlockState::Unlocked; }
    void reset_web() { state_ = UnlockState::Gated; }

private:
    UnlockState state_;
};

// Opaque playback request. `loop < 0` means forever (BGM); `loop == 0` once.
struct PlayRequest {
    int channel = -1;  // -1 = first free in the caller's bus range
    int loops = 0;
};

using SfxHandle = int;
inline constexpr SfxHandle kInvalidSfx = -1;

// Backend contract. Implementations own the device/stream lifetime; callers
// only move PCM or fire requests. Kept narrow so a null backend satisfies it
// in headless tests.
class Engine {
public:
    virtual ~Engine() = default;
    virtual bool open(const Spec& spec) = 0;
    virtual void close() = 0;
    virtual bool is_open() const = 0;
    // Push decoded S16 stereo frames for the music/movie stream; returns frames
    // accepted (backpressure, never blocks).
    virtual size_t push_music_s16(const int16_t* frames, size_t frame_count) = 0;
    virtual void set_volumes(const Volumes& v) = 0;
};

// Headless stand-in: accepts pushes into a counter so stream accounting tests
// without a device. Not a mixer — mixing needs the real backend.
class NullEngine : public Engine {
public:
    bool open(const Spec&) override {
        open_ = true;
        return true;
    }
    void close() override { open_ = false; }
    bool is_open() const override { return open_; }
    size_t push_music_s16(const int16_t*, size_t n) override {
        pushed_ += n;
        return n;
    }
    void set_volumes(const Volumes& v) override { volumes_ = v; }
    size_t pushed_frames() const { return pushed_; }

private:
    bool open_ = false;
    size_t pushed_ = 0;
    Volumes volumes_;
};

// BGM looping over decoded mix-ready PCM (S16 stereo @44100), driven through
// the Engine push interface — so NullEngine tests it with no device, and the
// real engine streams it without ever holding more than a chunk. The PCM is
// borrowed and must outlive the player; BGM buffers are MBs, so no copy.
// Loop points come from parse_sfl_loop (.sfl sibling) in file-rate samples;
// every shipped track decodes at 44100, which is the mix rate, so no scaling.
class LoopPlayer {
public:
    void set_source(const int16_t* stereo44100, size_t frames) {
        pcm_ = stereo44100;
        frames_ = frames;
        pos_ = 0;
        loops_ = 0;
    }
    // [startFrame, endFrame); endFrame == 0 or past EOF means play to EOF once.
    void set_loop(uint32_t startFrame, uint32_t endFrame) {
        loopStart_ = startFrame;
        loopEnd_ = endFrame;
    }
    // Push up to maxFrames, wrapping at the loop end as needed. Returns frames
    // pushed this call: 0 at EOF with no loop, or when the engine takes none
    // (backpressure — call again later, never spins: no progress, no wrap).
    size_t push_next(Engine& engine, size_t maxFrames) {
        if (!pcm_ || maxFrames == 0) return 0;
        const size_t end =
            (loopEnd_ > loopStart_ && loopStart_ < frames_)
                ? (loopEnd_ < frames_ ? loopEnd_ : frames_)
                : frames_;
        size_t pushed = 0;
        while (pushed < maxFrames && pos_ < frames_) {
            if (pos_ >= end) {
                if (end == frames_) return pushed;  // EOF, no loop region left
                pos_ = loopStart_;
                ++loops_;
                continue;
            }
            size_t want = end - pos_;
            if (want > maxFrames - pushed) want = maxFrames - pushed;
            const size_t got = engine.push_music_s16(pcm_ + pos_ * 2, want);
            pos_ += got;
            pushed += got;
            if (got == 0) break;
        }
        return pushed;
    }
    uint64_t loops_completed() const { return loops_; }
    size_t position() const { return pos_; }

private:
    const int16_t* pcm_ = nullptr;
    size_t frames_ = 0, pos_ = 0;
    uint32_t loopStart_ = 0, loopEnd_ = 0;
    uint64_t loops_ = 0;
};

}  // namespace fnd::audio
