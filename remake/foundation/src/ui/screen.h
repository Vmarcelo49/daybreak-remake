#pragma once
// Front-end screen stack: the original's scene machine, as the menus use it.
//
// Provenance (FRONTEND-PLAN.md §1.2 and §5.1 carry the full reading):
//   * the main loop calls the current scene's vtable slot 3 (update) and hands the
//     RETURN VALUE to the scene switcher — FUN_00657ef0.c:29-34;
//   * the switcher FUN_00657c80.c:12-64 compares that id with the current one
//     (DAT_006b77b8), runs a 25-frame fade whose overlay alpha is (n*10+5) << 24
//     (:16-22 fading in, :36-41 fading out, clamped at :24-28), then destroys the old
//     scene and constructs the new one through the App's factory (:51-59) —
//     FUN_004020a0, ids 0x00-0x15; 0x16+ falls to `default` and returns null, which the
//     loop reads as "no scene: quit" (FUN_00657ef0.c:49-53).
//
// Why this is a seam and not a pile of screens: the id an update returns is the whole
// contract. Adding a screen is one factory entry plus one class, which is what the
// plan's later steps (select, stage, VS intro, result) need.
//
// Two deliberate differences from the original, both recorded here rather than hidden:
//   * The fade is applied over the *live* screen. FUN_00657c80 clears a "do not draw"
//     flag while fading out (:35) and relies on the D3D9 backbuffer still holding the
//     last frame; the port rebuilds every frame from scratch, so the equivalent
//     content is the screen itself drawn under the ramp.
//   * A request is latched when it is made. FUN_00657c80 re-reads the id the current
//     scene returns on every frame of the fade; every screen in the RE table returns a
//     constant while fading, so latching is equivalent and gives the stack a one-shot
//     "go to id" API.
#include <array>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>

#include "ui/sprite.h"

namespace fnd::input { class Backend; }

namespace ui {

// The scene ids the RE proves (FUN_004020a0's switch; FRONTEND-PLAN.md §1.2 lists every
// update function's returned ids). 0x02 and 0x0e-0x13 are story-mode support scenes
// whose identity is deliberately not RE'd (plan §7.6), so they are not named here.
enum class ScreenId : int {
    Opening      = 0x00,   // FUN_00404eb0: movie/op.mpg
    Title        = 0x01,   // FUN_00410d60 ctor, FUN_00410f60 update, FUN_004114f0 draw
    Select       = 0x03,   // FUN_00408330: team/character/weapon/hypermode/controller/ready
    Prologue     = 0x04,   // FUN_00405650: the title's ストーリー target
    StoryTeam    = 0x05,   // FUN_004057c0
    Options      = 0x06,   // FUN_00402890
    KeyConfig    = 0x07,   // FUN_00403eb0
    StoryAdv     = 0x08,   // FUN_0040e720
    VsIntro      = 0x09,   // FUN_004115f0
    Battle       = 0x0a,   // FUN_00403ae0 stub; the battle module owns the frame
    NetplayMenu  = 0x0b,   // FUN_00412110, deferred (remake/docs/decisions.md D6)
    NetplayLobby = 0x0c,   // FUN_00414750, deferred
    NetplayEntry = 0x0d,   // FUN_00419f10 (name/IP), deferred
    GameOver     = 0x14,   // FUN_00403d70
    StaffRoll    = 0x15,   // FUN_0040e0b0
    Result       = 0x17,   // Port presentation id; original results are owned by the battle module.
    Quit         = 0x16,   // the factory's default: no scene, the loop tears down
};

// The menu grammar: four directions and two buttons, as this frame's edges. The
// original merges all four input slots into one set of counters (FUN_00410f60.c:81-100)
// so a pad confirm works from any slot; confirm is Jump (Z — docs/reference/README.md's
// control correction notes Z is confirmed in menus) and cancel is AttackA (X).
//
// `upHeld`/`downHeld`/`leftHeld`/`rightHeld` are the same four directions as HELD state
// instead of this frame's edge. The select screen's free cursor is the one consumer that
// needs it — it slides at a fixed rate per call while a direction is down
// (FUN_00409340:239-244) — and it travels BESIDE the edge fields so that every other
// front-end screen keeps its one-step-per-press grammar. PORT RULE: the port's input layer
// is edge-based (just_pressed), and a synthetic pad's down-state is held for a whole hold,
// so without this the same rule would behave differently per device.
struct ScreenButtons {
    bool up = false, down = false, left = false, right = false, confirm = false, cancel = false;
    bool upHeld = false, downHeld = false, leftHeld = false, rightHeld = false;
};
struct ScreenInput {
    bool up = false, down = false, left = false, right = false, confirm = false, cancel = false;
    bool upHeld = false, downHeld = false, leftHeld = false, rightHeld = false;
    int player = 0;
    bool separatePlayers = false;
    std::array<ScreenButtons,4> players{};
};

// One front-end screen. update is the original's vtable slot 3: the return value is the
// next screen id, and the screen's own id means "stay".
class Screen {
public:
    virtual ~Screen() = default;
    virtual ScreenId update(const ScreenInput& in) = 0;
    // The original's draw (slot 1). The stack has already called batch.beginFrame().
    virtual void draw(SpriteRenderer& batch) const = 0;
    virtual const char* name() const = 0;
    // FUN_0064aed0 system-bank ids; the host owns playback.
    virtual int takeSound() { return -1; }
    virtual std::string takeVoice() { return {}; }
};

// FUN_004020a0's switch as a predicate: true for the ids the port can construct. The
// port grows this list one screen at a time; screens read it to tell "would go to X"
// from "goes to X" instead of pretending a transition happened.
bool screenAvailable(ScreenId id);

class MovieAudio;
// Scene 0x00's host-owned seams (ui/screen_opening.h): the movie's audio output, the input
// backend its recovered skip keys are read from, and which file it plays (--movie; empty
// keeps the original's op.mpg). The host installs them before the first screen exists; with
// either pointer left null, constructing the opening scene reports that instead of building
// one that cannot work — which is what a device-free test gets.
void setOpeningHost(MovieAudio* audio, fnd::input::Backend* input, std::string movie);

// Constructs the screen for an id, or returns null (with `error` naming the id) when
// there is none — the factory's own `default` behaviour, which the switcher turns into
// "no scene" (FUN_00657c80.c:58, FUN_00657ef0.c:49-53). The caller owns `state` (the App's
// ui::FrontendState): a screen that owns part of it re-initialises that part here, exactly
// where the original's factory constructs the scene — the select scene's selection is the
// entry-time case (FrontendState::beginSelection).
struct FrontendState;
std::unique_ptr<Screen> makeScreen(ScreenId id, SpriteRenderer& batch, FrontendState& state,
                                   std::string& error);

// "--screen=<id|name>": decimal, 0x-prefixed hex, or the lowercase name (a leading
// "scene"/"screen" is accepted). Device-free, so the CLI contract is testable.
bool parseScreenId(const char* text, ScreenId& out);

// The switcher: one screen current, one fade counter, one injected factory. Hold it
// next to the App and call update() once per frame before draw().
class ScreenStack {
public:
    // FUN_00657c80 asks the App's vtable slot 2 for the new scene. Injecting the factory
    // keeps the fade/transition machine testable with no device (a test passes fake
    // screens); the app passes a lambda over makeScreen.
    using Factory = std::function<std::unique_ptr<Screen>(ScreenId)>;

    static constexpr int kFadeFrames = 0x19;   // FUN_00657c80.c:16/:34 bound

    // The overlay alpha of fade frame n (1..kFadeFrames), 0..255. FUN_00657c80.c:16-28
    // ramps (n*10+5)<<24 while n < 0x18 and pins 0xff000000 from 0x18 on, so 23 -> 235
    // and both 24 and 25 -> 255.
    static uint8_t fadeAlpha8(int frame);

    // The original boots by constructing the App's first scene with no fade, which is
    // what --screen does. False (with `error`) when the id has no screen.
    bool begin(ScreenId id, Factory factory, std::string& error);

    // One frame: the current screen's update, then the switcher. Returns the current id
    // after the frame (Quit once the stack has finished).
    ScreenId update(const ScreenInput& in);
    void request(ScreenId id) { target_ = id; fade_ = 1; }

    // Current screen, then the fade overlay in the 800x600 menu canvas.
    // Call between beginFrame and render.
    void draw(SpriteRenderer& batch) const;

    // The current screen ALONE. FUN_00657c80's fade is this class's own overlay, and a
    // caller that has to fade the whole target rather than the 800x600 canvas draws it
    // itself from fadeFrame() + fadeAlpha8() — ui::drawScreenOverlay does (the countdown
    // over the live battle has no opaque background to hide the letterbox bars).
    void drawContent(SpriteRenderer& batch) const;

    int takeSound() { return current_ ? current_->takeSound() : -1; }
    std::string takeVoice() { return current_ ? current_->takeVoice() : std::string{}; }

    bool     finished() const { return finished_; }
    ScreenId current() const { return currentId_; }
    int      fadeFrame() const { return fade_; }          // 0 = no overlay
    // The scene being faded TO, while the fade is in flight; equal to current() when nothing
    // is. The host needs this because the swap happens at the END of the 25-frame fade
    // (FUN_00657c80.c:32-64) and part of a scene's start-up is AUDIBLE before then: the
    // opening movie's own audio ends with its last frame, so a music track that waited for
    // the swap leaves an audible hole where the menu theme should already be. Starting it
    // here keeps the recovered fade untouched and the sound continuous.
    bool     transitionInFlight() const { return target_ != currentId_; }
    ScreenId pending() const { return target_; }
    const Screen* screen() const { return current_.get(); }
    // The same screen, non-const: one screen owns a one-shot the host has to drain (the
    // opening scene's recovered BGM start, ui/screen_opening.h), and the stack is the host's
    // only handle on the live screen.
    Screen*  mutableScreen() { return current_.get(); }

private:
    std::unique_ptr<Screen> current_;
    ScreenId currentId_ = ScreenId::Quit;
    ScreenId target_    = ScreenId::Quit;   // latched request while fading out
    int      fade_      = 0;                // FUN_00657c80's +0x60 counter
    bool     finished_  = false;
    Factory  factory_;
};

// The UI pass of one front-end frame: beginFrame -> stack.draw -> render, the same three
// calls main.cpp's hudTestHook makes for the HUD (docs/UI-INTEGRATION.md). Shared by the
// app and by capture harnesses so neither can drift from the other. It paints the opaque
// menu background first: a menu frame has no scene, so the screen is composited over a
// defined black.
bool drawScreenFrame(const ScreenStack& stack, SpriteRenderer& batch, uint32_t w, uint32_t h,
                     WGPUCommandEncoder encoder, WGPUTextureView view, WGPUTextureFormat format,
                     std::string& error);

// The same pass WITHOUT that background quad, for a screen drawn over an already-rendered
// scene — the pre-round countdown (issue #47), whose background is the live battle. Both
// draw the same screen with the same canvas transform and clip and the same fadeAlpha8()
// ramp; they differ in exactly two things, both required by the missing background: no
// opaque quad, and a fade that covers the whole target rather than the 800x600 canvas
// (which the opaque quad would otherwise back).
bool drawScreenOverlay(const ScreenStack& stack, SpriteRenderer& batch, uint32_t w, uint32_t h,
                       WGPUCommandEncoder encoder, WGPUTextureView view, WGPUTextureFormat format,
                       std::string& error);

}  // namespace ui
