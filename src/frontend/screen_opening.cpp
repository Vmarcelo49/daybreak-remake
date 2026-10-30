// The opening scene (issue #40). The header carries the recovered provenance, the skip
// rules and what is deliberately not built; this file is the machinery.
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <utility>

#include "assets/asset_source.h"
#include "audio/audio_engine.h"
#include "frontend/frontend_settings.h"
#include "frontend/screen_opening.h"
#include "battle/fixed_step.h"

namespace ui {
namespace {

// DAYBREAK_MOVIE_LOG=1 turns on the per-frame A/V progress line. Gate rather than always-on
// because an interactive run would otherwise print ~5 lines a second for the whole movie,
// and gate rather than delete because it is the only instrument that shows the decoder's
// frame clock, the presented-frame count and the audio pushed advancing together — which is
// what "the opening plays in sync" means, and what issue #40's evidence asks to see. It is
// read once: a run cannot change it mid-playback.
bool movieLogEnabled() {
    static const bool enabled = [] {
        const char* v = std::getenv("DAYBREAK_MOVIE_LOG");
        return v && *v && *v != '0';
    }();
    return enabled;
}

}  // namespace

size_t MovieAudio::push(const int16_t* stereo, size_t frames) {
    if (!opened_) {
        opened_ = true;
        openOk_ = engine_.open(fnd::audio::Spec{});
        if (openOk_) {
            // The option screen's sliders govern every bus, movies included.
            engine_.set_volumes(frontendSettings().volumes);
        } else {
            std::fprintf(stderr, "[movie] audio device unavailable; the movie plays silently\n");
        }
    }
    if (!openOk_) return 0;
    return engine_.push_music_s16(stereo, frames);
}

size_t MovieAudio::queuedFrames() const { return engine_.music_queued_frames(); }

void MovieAudio::close() {
    engine_.close();
    opened_ = false;
    openOk_ = false;
}

OpeningScreen::OpeningScreen(SpriteRenderer& batch, fnd::input::Backend& input,
                             MovieAudio& audio, std::string path)
    : batch_(batch), input_(input), audio_(audio), path_(std::move(path)) {}

bool OpeningScreen::takeBgmRequest() {
    const bool pending = bgmPending_;
    bgmPending_ = false;
    return pending;
}

ScreenId OpeningScreen::update(const ScreenInput& in) {
    (void)in;   // the recovered skip is a raw key read, not a menu action (RULE 1 above)

    if (!started_) {
        started_ = true;
        // FUN_0065c950() is the start call and the BGM switch is [+0xac]'s 0->1 step. The
        // title scene loads the menu bank and plays its own music; the movie needs only the
        // engine the player pushes into.
        //
        // The path is resolved through the asset source first: the original reads
        // "movie/op.mpg" relative to its own directory, and a run started elsewhere (every
        // capture recipe) has to land on the same file. pl_mpeg then opens the file itself
        // — it is the one asset in this tree read by a decoder rather than by
        // AssetSource::read, so the resolved path is what it gets.
        const std::string& install = fnd::assets::assetSource().installDir();
        const std::string resolved = fnd::assets::assetSource().resolve(
            {install.empty() ? path_ : install + "/" + path_, path_});
        const std::string& file = resolved.empty() ? path_ : resolved;
        std::string openError;
        fnd::movie::AudioPush sink = [this](const int16_t* stereo, size_t frames) {
            return audio_.push(stereo, frames);
        };
        if (!player_.open(file, std::move(sink), openError)) {
            failed_ = true;
            error_ = openError;
            std::fprintf(stderr, "[movie] %s\n", openError.c_str());
            return ScreenId::Title;
        }
        bgmPending_ = true;
        std::printf("movie        : %s (%s)\n", path_.c_str(), player_.describeFormat().c_str());
    }

    player_.update(gameplay::FixedStep::seconds);   // the front end's logic tick
    if (movieLogEnabled() && player_.framesPresented() != lastLoggedFrame_ &&
        player_.framesPresented() % 64 == 0) {
        lastLoggedFrame_ = player_.framesPresented();
        // One line per 64 presented frames (~2.1 s): the frame clock against the decoder's
        // own time, the audio the sink accepted, and how far apart they are. `drift` is the
        // number to watch — the container's PTS is ignored, so frame.time and the audio the
        // decoder has produced are the only two clocks there are.
        const double audioSeconds = (double)player_.audioFramesPushed() / fnd::movie::kAudioRate;
        std::printf("[movie] frame %4llu  frame.time %7.3f s  audio %7.3f s  drift %+6.3f s"
                    "  queued %6.2f s\n",
                    (unsigned long long)player_.framesPresented(), player_.frameTime(),
                    audioSeconds, audioSeconds - player_.frameTime(),
                    (double)audio_.queuedFrames() / fnd::movie::kAudioRate);
    }
    if (player_.finished()) {
        // Reported once: update() keeps running through the switcher's fade-out, so this
        // branch is reached on every frame of it.
        if (!endReported_) {
            endReported_ = true;
            // decoded/presented are reported together: a frame the decoder produced but
            // this player refused (a size that is not the surface's) would show up as the two
            // numbers disagreeing.
            std::printf("movie        : ended after %llu frames decoded/%llu presented (%.3f s), "
                        "audio %.3f s\n",
                        (unsigned long long)player_.framesDecoded(),
                        (unsigned long long)player_.framesPresented(), player_.frameTime(),
                        (double)player_.audioFramesPushed() / fnd::movie::kAudioRate);
        }
        return ScreenId::Title;
    }
    // The recovered skip input (Return/LAlt/RAlt) OR the front-end's own buttons.
    //
    // The original reads raw VK codes and its Return IS the front-end's confirm key, so there
    // the two are one press. This port binds confirm to Z (Jump) and cancel to X (AttackA),
    // which left the skip reachable only by Return — a key that does nothing in these menus —
    // while the buttons a player is actually holding did nothing at all. Taking both keeps the
    // recovered keys working and makes the buttons work too.
    if (movieSkipHeld([this](int sc) { return input_.key_down(sc); }) || in.confirm || in.cancel) {
        std::printf("movie        : skipped at frame %llu (%.3f s)\n",
                    (unsigned long long)player_.framesPresented(), player_.frameTime());
        return ScreenId::Title;
    }
    return ScreenId::Opening;   // stay
}

void OpeningScreen::draw(SpriteRenderer& batch) const {
    const uint8_t* pixels = player_.framePixels();
    if (!pixels) return;
    const uint32_t w = (uint32_t)player_.width(), h = (uint32_t)player_.height();
    if (w == 0 || h == 0) return;
    // One upload per presented frame, into one slot: addTexture the first time,
    // updateTexture after (which keeps the id and recreates the texture only if the pixel
    // size changed — it cannot here, a movie's dimensions are fixed by its sequence header).
    std::string error;
    if (texture_ < 0)
        texture_ = batch.addTexture(w, h, pixels, error);
    else
        batch.updateTexture(texture_, w, h, pixels, error);
    if (texture_ < 0) {
        if (!error.empty()) std::fprintf(stderr, "[movie] texture: %s\n", error.c_str());
        return;
    }
    // FUN_00655af0(spr,0,0,0x280,0x1e0) + FUN_00408250(1.25f): the 640x480 blit drawn at
    // 1.25x, which is exactly the 800x600 menu canvas. The film's own black bars are
    // inside the video, so the port draws no letterbox of its own
    // (docs/reference/README.md:42 says the same about the banked reference frame).
    batch.pushTextured(texture_, UiRect{0.f, 0.f, 800.f, 600.f}, UiRect{0.f, 0.f, 1.f, 1.f},
                       UiColor{1.f, 1.f, 1.f, 1.f});
}

std::unique_ptr<Screen> makeOpeningScreen(SpriteRenderer& batch, fnd::input::Backend& input,
                                          MovieAudio& audio, std::string path,
                                          std::string& error) {
    // An unopenable movie is not a construct failure: the scene is built, reports it from
    // inside its own first update and leaves for the title (the original's scene is built
    // the same way, and FUN_0065c080's own failure just leaves the stream closed).
    (void)error;
    return std::make_unique<OpeningScreen>(batch, input, audio, std::move(path));
}

}  // namespace ui
