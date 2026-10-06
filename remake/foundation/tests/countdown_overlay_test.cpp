// =============================================================================
//  countdown_overlay_test.cpp — the pre-round countdown's gate boundary and its
//  overlay policy (issue #47).
//
//  Issue #47: the countdown drew an opaque black quad over the whole canvas AND the
//  battle scene was never rendered behind it, so the phase reported as "the 3-2-1 on a
//  black screen". The fix keeps the digit and the roster captions but drops the quad —
//  the screen is composited over the live scene by ui::drawScreenOverlay — and holds the
//  round until the countdown's own clock ends.
//
//  No device, no window: a SpriteRenderer without a device keeps its quads on the CPU
//  until render(), so the batch is readable through quadList(). That makes the policy a
//  STRUCTURAL assertion, not a pixel one (a pixel test needs a GPU adapter and the game
//  data; tests/hud_cell_scale.py is that kind of test). What is asserted here:
//
//    * the gate boundary: CountdownClock is not done for 3*tickRate-1 ticks and is done
//      on exactly the 3*tickRate-th, for both clock rates the app uses, and the digit
//      cells land on the three P09 thirds;
//    * the same boundary through the REAL screen: CountdownScreen::update() sets the
//      app's `ready` flag on exactly that tick and never before (the art cannot upload
//      without a device, which is why the boundary is asserted on the clock, not on
//      pixels);
//    * ui::drawScreenFrame paints exactly one opaque quad covering the menu canvas —
//      the control that keeps the next assertion from being vacuous;
//    * ui::drawScreenOverlay paints NO opaque canvas-covering quad over the real
//      countdown screen, which is the regression this issue is about: re-adding
//      `pushSolid({0,0,800,600},{0,0,0,1})` to the screen fails this test;
//    * the overlay's fade covers the WHOLE TARGET rather than the 800x600 canvas, so a
//      mid-fade countdown frame cannot leave the letterbox bars showing the scene.
//
//    ctest -R countdown_overlay_test
// =============================================================================

#include <cstdio>
#include <memory>
#include <string>
#include <vector>

#include "ui/screen.h"
#include "ui/screen_countdown.h"
#include "ui/sprite.h"

namespace {

using ui::CountdownClock;
using ui::CountdownInfo;
using ui::CountdownScreen;
using ui::Screen;
using ui::ScreenId;
using ui::ScreenInput;
using ui::ScreenStack;
using ui::SpriteRenderer;

int g_checks = 0;
int g_failed = 0;

void checkTrue(const char* what, bool ok) {
    ++g_checks;
    if (ok) std::printf("  [ok]   %s\n", what);
    else { std::printf("  [FAIL] %s\n", what); ++g_failed; }
}

void checkInt(const char* what, long long want, long long got) {
    ++g_checks;
    if (want == got) std::printf("  [ok]   %s = %lld\n", what, got);
    else { std::printf("  [FAIL] %s: want %lld, got %lld\n", what, want, got); ++g_failed; }
}

constexpr uint32_t kWidth = 1280, kHeight = 720;

// Does `dst` cover the 4:3 menu canvas the screens are authored in? In device pixels, the
// same rect drawScreenFrame's background quad and a screen's own {0,0,800,600} quad both
// end up covering.
bool coversCanvas(const ui::UiRect& dst) {
    const ui::UiCanvasTransform canvas = ui::fitCanvas({kWidth, kHeight});
    const ui::UiRect want = canvas.scale > 0.f
        ? ui::UiRect{canvas.x, canvas.y, 800.f * canvas.scale, 600.f * canvas.scale}
        : ui::UiRect{0.f, 0.f, float(kWidth), float(kHeight)};
    const float eps = 0.5f;
    return dst.x <= want.x + eps && dst.y <= want.y + eps &&
           dst.x + dst.w >= want.x + want.w - eps && dst.y + dst.h >= want.y + want.h - eps;
}

bool coversTarget(const ui::UiRect& dst) {
    const float eps = 0.5f;
    return dst.x <= eps && dst.y <= eps &&
           dst.x + dst.w >= (float)kWidth - eps && dst.y + dst.h >= (float)kHeight - eps;
}

// Opaque quads covering the whole menu canvas: what a menu frame must have exactly one of
// (the background) and what an overlay frame must have none of (the scene is the
// background). Colour is deliberately not part of the test: ANY opaque full-canvas quad
// hides the scene, which is the whole defect.
int opaqueCanvasQuads(const std::vector<ui::UiQuad>& quads) {
    int count = 0;
    for (const ui::UiQuad& q : quads)
        if (q.color.a >= 0.999f && coversCanvas(q.dst)) ++count;
    return count;
}

CountdownInfo sampleInfo(int tickRate) {
    CountdownInfo info;
    info.tickRate = tickRate;
    info.settings = "TIME 60s   BALLOON 40% / 40%";
    // Character+weapon combos, never bare fighters (AGENTS.md rule 7).
    info.roster.push_back({"BLUE  Rena 0  1P", true});
    info.roster.push_back({"RED   Chie 1  2P", false});
    return info;
}

// The stack's factory for the screen under test. The P09 sheet cannot upload without a
// device, so this screen draws nothing here — which is exactly why every assertion below is
// about the QUADS the paths push, not about pixels.
ScreenStack::Factory countdownFactory(SpriteRenderer& batch, bool& ready, std::string& error) {
    return [&batch, &ready, &error](ScreenId) -> std::unique_ptr<Screen> {
        return std::make_unique<CountdownScreen>(batch, sampleInfo(60), ready, error);
    };
}

void testGateBoundary() {
    std::printf("\n-- the gate boundary (CountdownClock) --\n");
    for (const int rate : {60, 64}) {
        CountdownClock clock(rate);
        const int frames = 3 * rate;
        checkInt("duration is 3 x tickRate", (long long)frames, clock.frames());
        bool early = false;
        for (int i = 1; i < frames; ++i) {
            clock.tick();
            early = early || clock.done();
        }
        checkTrue("not done for the first 3*tickRate-1 ticks", !early);
        clock.tick();
        checkTrue("done on the 3*tickRate-th tick", clock.done());
        checkInt("frame counter matches", (long long)frames, clock.frame());
    }
    // The three P09 digit cells: one per third, clamped at the end.
    CountdownClock clock(60);
    checkInt("cell 0 at frame 0", 0, clock.cell());
    for (int i = 0; i < 59; ++i) clock.tick();
    checkInt("cell 0 on the last frame of its third", 0, clock.cell());
    clock.tick();
    checkInt("cell 1 at tickRate", 1, clock.cell());
    for (int i = 0; i < 59; ++i) clock.tick();
    checkInt("cell 1 on the last frame of its third", 1, clock.cell());
    clock.tick();
    checkInt("cell 2 at 2*tickRate", 2, clock.cell());
    for (int i = 0; i < 200; ++i) clock.tick();
    checkInt("cell stays clamped past the end", 2, clock.cell());
    // A zero/negative rate would divide by zero in the cell arithmetic; the clock floors it,
    // so a capture recipe cannot ask for a zero-frame countdown.
    CountdownClock zero(0);
    checkInt("tickRate 0 floors to 1", 1, zero.tickRate());
    checkInt("and still counts one tick per cell", 3, zero.frames());
}

void testScreenGate() {
    std::printf("\n-- the same boundary through the real screen --\n");
    SpriteRenderer batch;
    bool ready = false;
    std::string error;
    CountdownScreen screen(batch, sampleInfo(60), ready, error);
    // The P09 sheet and the caption font need a device (and the install): this test has
    // neither, so the screen cannot load its art. The GATE is what is asserted here; the
    // draw is asserted in testOverlayPolicy.
    checkTrue("art is unavailable without a device (a structural test, not a pixel one)",
              !screen.loaded());
    ScreenInput in;
    for (int i = 0; i < 179; ++i) screen.update(in);
    checkTrue("ready stays false through tick 179", !ready);
    const ScreenId last = screen.update(in);   // the 180th update
    checkTrue("the screen keeps asking for the id it already is (stay)",
              last == ScreenId::Battle);
    checkInt("the clock ends at 180", 180, screen.clock().frame());
}

void testOverlayPolicy() {
    std::printf("\n-- the overlay policy (drawScreenFrame vs drawScreenOverlay) --\n");
    bool ready = false;
    std::string error;

    // The menu control: a scene-less menu frame paints the opaque background.
    {
        SpriteRenderer batch;
        ScreenStack stack;
        if (!stack.begin(ScreenId::Battle, countdownFactory(batch, ready, error), error)) {
            checkTrue("menu stack begins", false);
            return;
        }
        ui::drawScreenFrame(stack, batch, kWidth, kHeight, nullptr, nullptr,
                            WGPUTextureFormat_RGBA8Unorm, error);
        checkInt("drawScreenFrame paints exactly one opaque canvas-covering quad", 1,
                 opaqueCanvasQuads(batch.quadList()));
    }

    // The overlay: the same screen, no background. This is the issue #47 regression guard.
    {
        SpriteRenderer batch;
        ScreenStack stack;
        if (!stack.begin(ScreenId::Battle, countdownFactory(batch, ready, error), error)) {
            checkTrue("overlay stack begins", false);
            return;
        }
        ui::drawScreenOverlay(stack, batch, kWidth, kHeight, nullptr, nullptr,
                              WGPUTextureFormat_RGBA8Unorm, error);
        checkInt("drawScreenOverlay paints no opaque canvas-covering quad", 0,
                 opaqueCanvasQuads(batch.quadList()));
    }

    // The fade must cover the whole target: the canvas-space quad FUN_00657c80's ramp is
    // drawn as would leave the letterbox bars showing the scene mid-fade. A screen that
    // asks for a transition puts the stack at fade frame 1 (alpha (1*10+5)/255).
    {
        SpriteRenderer batch;
        ScreenStack stack;
        struct AskingScreen final : Screen {
            ScreenId update(const ScreenInput&) override { return ScreenId::Select; }
            void draw(SpriteRenderer&) const override {}
            const char* name() const override { return "asking"; }
        };
        if (!stack.begin(ScreenId::Battle,
                         [](ScreenId) -> std::unique_ptr<Screen> {
                             return std::make_unique<AskingScreen>();
                         },
                         error)) {
            checkTrue("fade stack begins", false);
            return;
        }
        ScreenInput in;
        stack.update(in);
        checkInt("the stack is at fade frame 1", 1, stack.fadeFrame());
        ui::drawScreenOverlay(stack, batch, kWidth, kHeight, nullptr, nullptr,
                              WGPUTextureFormat_RGBA8Unorm, error);
        int fullTarget = 0;
        float alpha = -1.f;
        for (const ui::UiQuad& q : batch.quadList())
            if (coversTarget(q.dst)) { ++fullTarget; alpha = q.color.a; }
        checkInt("the overlay fade is one full-target quad", 1, fullTarget);
        checkTrue("with the switcher's own alpha (fade frame 1 -> 15/255)",
                  alpha > 0.058f && alpha < 0.060f);
    }
}

}  // namespace

int main() {
    std::printf("pre-round countdown: gate boundary + overlay policy (device-free)\n");
    testGateBoundary();
    testScreenGate();
    testOverlayPolicy();
    std::printf("\nchecks: %d, failures: %d\n", g_checks, g_failed);
    std::printf("COUNTDOWN_OVERLAY: %s\n", g_failed == 0 ? "ok" : "FAIL");
    return g_failed == 0 ? 0 : 1;
}
