#pragma once
// Scene 0x00 — the skippable opening movie (issue #40).
//
// Recovered from the ORIGINAL DaybreakDX.exe (md5 a136ddc01bd7ef355b759b88ac89e02c, read
// through the Ghidra bridge; research/decompiled/ is a PATCHED copy of the same build and
// agrees on every address below that it also contains):
//
//   FUN_00404eb0 @0x404eb0 — the scene constructor (research/decompiled/FUN_00404eb0.c:32-39)
//     FUN_0065c080("movie/op.mpg")        open the program stream (the exe's cwd is data/,
//                                         so the file is data/movie/op.mpg)
//     FUN_00655af0(spr, 0, 0, 0x280, 0x1e0) configure the blit: 640x480 at (0,0)
//     FUN_00408250(0x3fa00000)            sprite scale = 1.25f -> 800x600 on screen
//   0x6a14ec+0x0c is the update (the loop calls vtable slot 3, frontend/screen.h:5-6), which is
//   FUN_00404ff0 @0x404ff0, live-verified by disassembly; the factory's switch reaches the
//   constructor at 0x402107 (FUN_004020a0).
//
// FUN_00404ff0's machine, in order:
//
//   :0x404ffe  if FUN_00405250() -> return 0            end of stream: leave the scene
//   :0x405011  FUN_006584e0 + FUN_006585f0              keyboard + every pad poll
//   :0x405025  FUN_006586d0(0x1c)                       key down? 0x1c = VK_RETURN
//   :0x405038  FUN_006586d0(0xb8)                       VK key 0xb8 and ...
//   :0x40504e  FUN_006586d0(0x38)                       VK_MENU (0x38) — Alt
//              -> FUN_0064ad70(0x6ca820)                ... then toggle the pause menu
//   :0x40506b  [+0xac] == 0: set it to 1, FUN_0065c950() (start), BGM titlesemi.ogg,
//              FUN_00405290(2)                         the movie begins on the FIRST tick
//   :0x4050b1  poll again
//   :0x4050c5  [+0xac] == 1 && FUN_0065c9d0():          movie still running?
//   :0x4050f3  for each of 4 players: FUN_00657390 (update that player's counters), then
//              break if row+0x9c, row+0xa0 or row+0xb8 is non-zero, or FUN_006586d0(1) —
//              the pad's button bytes, i.e. a pad button held
//   :0x405157  -> FUN_0065c990() (stop), BGM title.ogg, FUN_00405290(1), return 1
//   :0x40518c  otherwise return 1                        stay
//
// TWO RULES THE PORT TAKES FROM THAT, both labelled because they are not transcriptions:
//
//   RULE 1 (skip keys). The original tests virtual-key codes 0x1c, 0xb8 and 0x38 straight
//     out of its 256-byte keyboard buffer (FUN_006586d0 @0x6586d0 reads
//     `*(byte*)(kb + 0x20 + code) & 0x80`, and 0x1c is VK_RETURN in every other caller of
//     that test: FUN_00404220 @0x404220 checks 0x1c/0x39 for confirm, and FUN_00657390's
//     own FUN_00657820 path checks 0xcb/0xcd as directions). So: Enter or either Alt key,
//     HELD (not a press edge — the original never clears the state it reads). The port maps
//     them to the SDL scancodes below and reads the backend's raw key state; it does NOT
//     route them through the action map, because the key-config screen owns that map and a
//     player could then rebind away the only way to skip a movie. The pad half (the button
//     bytes above) is not nameable from the RE, so the port does not invent one — every
//     button of the port's menu grammar stays a port rule, not a recovered input.
//   RULE 2 (no hold gate). FUN_00404ff0 does not gate the skip on the movie having played
//     for a while, so neither does this.
//
// The scene leaves to id 1 (Title) on both the skip and the end of stream — what
// FUN_00410d60's title scene then does with its own BGM is its business.
//
// Not built here on purpose: no second screen for the staff roll (scene 0x15's own
// constructor is FUN_004052b0 @0x4052b0 and it drives the same player through
// FUN_004053d0), no media framework, no seek, no pause. `--movie=` names which file this
// ONE screen plays so the staff roll can be driven through it without a new scene.

#include <cstdint>
#include <memory>
#include <string>

#include "audio/audio_engine.h"
#include "input/input_backend.h"
#include "movie/movie_player.h"
#include "frontend/screen.h"

namespace ui {

// The opening movie's audio output. Why the movie gets its own engine instead of
// borrowing the menu's: the original's movie audio is an independent DirectShow stream
// that plays UNDER the front end's BGM — the opening scene starts titlesemi.ogg while the
// film runs (FUN_00404ff0 @0x404ff0:0x405096) — so two sources are live at once.
// fnd::audio has one music stream per engine and the front end's BGM already owns the menu
// engine's, so the movie pushes into its own. It is one object owned by the app, not by
// the screen, because the device has to outlive a screen re-entry.
//
// The engine opens LAZILY, on the first PCM frame the decoder produces: a verification run
// never reaches this object, so it must not open an audio device at boot, and a device-less
// run must not fail because a cutscene cannot make a sound.
class MovieAudio {
  public:
    // PCM frames the sink accepted; 0 before the device is open, which is also what the
    // movie's A/V readout reports rather than a fabricated number.
    size_t push(const int16_t* stereo, size_t frames);
    size_t queuedFrames() const;
    // The host closes it with the other engines, BEFORE SDL shuts down: the device is an
    // SDL handle, so letting the destructor find it after plat::shutdown() is a use of a
    // dead subsystem (measured: a segfault inside SDL_CloseAudioDevice).
    void close();
    // The option screen's sliders govern every bus, movies included.
    void set_volumes(const fnd::audio::Volumes& v) { engine_.set_volumes(v); }

  private:
    fnd::audio::Sdl3Engine engine_;
    bool opened_ = false;
    bool openOk_ = false;
};

// The recovered skip input, as SDL scancodes. SDL_SCANCODE_RETURN = 40, LALT = 226,
// RALT = 230; input_sdl3.h pins the same values for the actions it binds. 0x1c/0xb8/0x38
// are the original's virtual-key codes (RULE 1 above), in the order FUN_00404ff0 tests
// them.
inline constexpr int kMovieSkipScancodes[] = {40, 226, 230};
inline constexpr int kMovieSkipScancodeCount = 3;

// The recovered skip test, split out from the screen so it is checkable with no device and
// no movie: `held` answers "is this scancode down". It is a HELD read, never an edge — the
// original never clears the state it reads — so holding Return skips on the first frame the
// check runs.
template <typename HeldFn>
inline bool movieSkipHeld(HeldFn&& held) {
    for (int i = 0; i < kMovieSkipScancodeCount; ++i)
        if (held(kMovieSkipScancodes[i])) return true;
    return false;
}

class OpeningScreen final : public Screen {
  public:
    OpeningScreen(SpriteRenderer& batch, fnd::input::Backend& input, MovieAudio& audio,
                  std::string path, ScreenId own = ScreenId::Opening, ScreenId next = ScreenId::Title);
    ScreenId update(const ScreenInput& in) override;
    void draw(SpriteRenderer& batch) const override;
    const char* name() const override { return "opening"; }

    // The BGM one-shot: the title screen's own music is the switcher's business
    // (playFrontendMusic), but FUN_00404ff0 starts the movie's BGM from inside the scene
    // (:0x405096, titlesemi.ogg at 0x6a14c0), before the movie's first frame is presented.
    bool takeBgmRequest();
    bool failed() const { return failed_; }
    const std::string& error() const { return error_; }

  private:
    SpriteRenderer& batch_;
    fnd::input::Backend& input_;
    MovieAudio& audio_;
    std::string path_;
    ScreenId own_, next_;
    fnd::movie::MoviePlayer player_;
    // Written from draw(), which the Screen contract makes const (the original's draw is
    // too, and it is where its own texture upload lives).
    mutable int texture_ = -1;
    bool started_ = false;    // [+0xac] == 1: the start call and the BGM switch ran
    bool bgmPending_ = false;
    uint64_t lastLoggedFrame_ = 0;   // DAYBREAK_MOVIE_LOG progress line (see the .cpp)
    bool endReported_ = false;       // the end-of-stream line prints once, not once a frame
    bool failed_ = false;
    std::string error_;
};

std::unique_ptr<Screen> makeOpeningScreen(SpriteRenderer& batch, fnd::input::Backend& input,
                                          MovieAudio& audio, std::string path, std::string& error,
                                          ScreenId own = ScreenId::Opening, ScreenId next = ScreenId::Title);

}  // namespace ui
