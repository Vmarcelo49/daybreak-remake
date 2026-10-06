// Issue #43: the select screen's two recovered transitions, pinned against the recovered
// constants. Device-free: both are plain state machines in ui/screen_select.h, so no screen,
// no GPU and no install are involved — the draw calls the same objects this test ticks.
//
//  1. The scene's ENTRY reveal — FUN_004090a0:24-26, the same loop in FUN_0041bae0:37-40:
//     slot i's float at scene+0x3d50+i*4 ramps 0 -> 1 in steps of 0.1 and may only start once
//     the scene tick has passed i+5, so the 16 slots start one tick apart and each needs ten
//     ticks. FUN_0040b2b0:96-104 hands the slot's value to FUN_0040da60 as the PAIR
//     (v, 2-v), which lands at sprite+0x84/+0x88 (FUN_0040da60 @0x40da60), and the sprite quad
//     builder FUN_00655830 @0x65583f-0x6558db multiplies them into the pivot and the cell:
//     x0 = x - pivotX*sx, w = srcW*sx, y0 = y - pivotY*sy, h = srcH*sy. The pair is a scale,
//     not an offset; the test checks the quad the draw actually builds for it.
//  2. The phase-row slide — FUN_00409340:589-595 sets 0x3cc4[controller] = 300.0 on a phase
//     change and steps 20.0 off it in the same call while it is above 0.0; FUN_0040b2b0
//     :0x40c09f-0x40c0c4 signs it by the panel's column (1 - 2*(panel < 2)) and adds it to the
//     header's and the phase rows' x.
//
// The literals below are the recovered constants, not tuned values: 0.1 = 0x3dcccccd
// (_DAT_006a1984), 1.0 = _DAT_006a16d0, the stagger's 5, 300.0 = 0x43960000, 20.0 =
// _DAT_006a16c4 and the > 0.0 guard's _DAT_006a16c8.
#include "ui/screen_select.h"
#include <cmath>
#include <cstdio>

namespace {
bool near(float a, float b) { return std::fabs(a - b) < 0.0005f; }
bool sameRect(const ui::UiRect& a, const ui::UiRect& b) {
    return near(a.x, b.x) && near(a.y, b.y) && near(a.w, b.w) && near(a.h, b.h);
}
}  // namespace

int main() {
    int failures = 0;
    auto check = [&](bool value, const char* name) {
        if (!value) { std::fprintf(stderr, "FAIL %s\n", name); ++failures; }
    };

    // --- The recovered constants themselves (FUN_004090a0:24-26 / FUN_00409340:589-595) -----
    check(ui::SelectReveal::kStep == 0.1f, "the ramp's step is 0.1 (0x3dcccccd, _DAT_006a1984)");
    check(ui::SelectReveal::kSettled == 1.f, "the ramp's target is 1.0 (_DAT_006a16d0)");
    check(ui::SelectReveal::kStagger == 5, "slot i waits for tick > i + 5");
    check(ui::SelectRowSlide::kStart == 300.f, "a phase change starts the slide at 300.0 (0x43960000)");
    check(ui::SelectRowSlide::kStep == 20.f, "the slide's step is 20.0 (_DAT_006a16c4)");

    // --- Nothing moves before tick 6, and then one slot starts per tick ---------------------
    {
        ui::SelectReveal reveal;
        for (int tick = 1; tick <= 5; ++tick) reveal.tick(tick);
        bool any = false;
        for (int i = 0; i < 16; ++i) any |= reveal.value[(size_t)i] != 0.f;
        check(!any, "no slot has stepped by tick 5 (the earliest is i + 5 < tick)");
    }
    for (int slot = 0; slot < 16; ++slot) {
        ui::SelectReveal reveal;
        int firstStep = -1, settledAt = -1, steps = 0;
        float previous = 0.f;
        for (int tick = 1; tick <= 64; ++tick) {
            reveal.tick(tick);
            const float v = reveal.value[(size_t)slot];
            if (v != previous) {
                if (firstStep < 0) firstStep = tick;
                ++steps;
                previous = v;
            }
            if (settledAt < 0 && v >= ui::SelectReveal::kSettled) settledAt = tick;
        }
        if (slot == 0 || slot == 15) {   // one line for each end of the stagger
            std::printf("slot %2d: first step at tick %d, settled at tick %d, %d steps, value %.9g\n",
                        slot, firstStep, settledAt, steps, (double)reveal.value[(size_t)slot]);
        }
        check(firstStep == slot + 6, "slot i's first 0.1 step lands on scene tick i + 6");
        check(steps == 10, "a slot takes exactly ten 0.1 steps");
        check(settledAt == slot + 15, "and has settled ten ticks after it started (i + 15)");
        // Ten accumulations of 0.1 in binary32 land one ULP ABOVE 1.0 (1.0000001), which is
        // what stops the loop: an 11th step would draw the quad at 1.1. The original does the
        // same arithmetic and stores a float (FADD/FSTP float at FUN_004090a0:0x409161), so it
        // stops on the same step; the sub-ULP difference is 1e-5 px of quad.
        check(!(reveal.value[(size_t)slot] < ui::SelectReveal::kSettled),
              "the ramp stops on the loop's own < 1.0 guard, never an 11th step");
        check(near(reveal.value[(size_t)slot], 1.f), "and it ends on 1.0 (float32 rounding aside)");
    }

    // --- The stagger: the slots are mid-flight together, and not all on the same tick -------
    {
        // One call per scene tick, exactly as SelectScreen::update drives it.
        ui::SelectReveal reveal;
        int tick = 0;
        while (tick < 12) reveal.tick(++tick);
        int moving = 0;
        for (int i = 0; i < 16; ++i) moving += reveal.value[(size_t)i] > 0.f && reveal.value[(size_t)i] < 1.f;
        check(moving == 7, "at tick 12 slots 0..6 are mid-flight and 7..15 have not started");
        check(near(reveal.value[0], 0.7f) && near(reveal.value[6], 0.1f) && reveal.value[7] == 0.f,
              "and each holds the value its own start tick gives it");
        // Overlap: the i + 5 stagger means several slots animate at once (issue #44's
        // "several overlap" flash), never one at a time.
        while (tick < 15) reveal.tick(++tick);
        moving = 0;
        for (int i = 0; i < 16; ++i) moving += reveal.value[(size_t)i] > 0.f && reveal.value[(size_t)i] < 1.f;
        check(moving == 9, "at tick 15 nine slots are still moving at once");
        check(!(reveal.value[0] < ui::SelectReveal::kSettled), "while slot 0 has settled");
    }

    // --- The transform: (v, 2-v) is the quad's x/y SCALE (FUN_00655830 @0x65583f-0x6558db) ---
    {
        // Keiichi's chibi: the `i%02d` cell is 80x128 with the pivot (40,80) FUN_00408330
        // gave it, drawn at the roster's own anchor.
        const ui::UiRect settled = ui::scaledSpriteDst(448.f, 160.f, 80.f, 128.f, 40.f, 80.f, 1.f, 1.f);
        check(sameRect(settled, ui::spriteDst(448.f, 160.f, 80.f, 128.f, 40.f, 80.f, 1.f)),
              "a settled slot (1,1) is exactly the batch's uniform-scale rect");
        const ui::UiRect mid = ui::scaledSpriteDst(448.f, 160.f, 80.f, 128.f, 40.f, 80.f, .5f, 1.5f);
        check(near(mid.w, 40.f) && near(mid.h, 192.f) && near(mid.x, 428.f) && near(mid.y, 40.f),
              "at v = 0.5 the quad is half as wide and 1.5x as tall about the pivot");
        const ui::UiRect start = ui::scaledSpriteDst(448.f, 160.f, 80.f, 128.f, 40.f, 80.f, 0.f, 2.f);
        check(near(start.w, 0.f) && near(start.h, 256.f) && near(start.x, 448.f) && near(start.y, 0.f),
              "at v = 0 it is zero-width and double-height, not translated");
        // It is a scale, not an offset: the pivot's column is the quad's centre here (the pivot
        // is 40 = srcW/2), so it stays on the anchor at every v while the extents are v and
        // 2-v times the source's.
        for (float v : {0.f, .3f, .7f, 1.f}) {
            const ui::UiRect r = ui::scaledSpriteDst(448.f, 160.f, 80.f, 128.f, 40.f, 80.f, v, 2.f - v);
            check(near(r.x + r.w * .5f, 448.f), "the quad stays centred on its anchor's column");
            check(near(r.w, 80.f * v) && near(r.h, 128.f * (2.f - v)),
                  "the width is v * srcW and the height is (2 - v) * srcH");
        }
    }

    // --- The slide's own arithmetic (FUN_00409340:589-595) ---------------------------------
    {
        ui::SelectRowSlide slide;
        slide.step(0, false);
        check(slide.offsetFor(0) == 0.f, "an unchanged phase leaves the slide alone");
        slide.step(0, true);
        check(slide.offsetFor(0) == 280.f,
              "a phase change sets 300.0 and takes the first 20.0 step in the same call");
        int ticks = 1;
        while (slide.offsetFor(0) > 0.f && ticks < 64) { slide.step(0, false); ++ticks; }
        check(ticks == 15 && slide.offsetFor(0) == 0.f,
              "the slide reaches 0 fifteen ticks after the change (280, 260, ... 0)");
        slide.step(0, false);
        check(slide.offsetFor(0) == 0.f, "and the > 0.0 guard leaves it at 0");
        slide.step(2, true);
        check(slide.offsetFor(0) == 0.f && slide.offsetFor(2) == 280.f,
              "each controller's slide is its own (0x3cc4[controller])");
    }

    // --- The sign FUN_0040b2b0 gives it by the panel's column -------------------------------
    check(ui::rowSlideOffset(280.f, 0) == -280.f && ui::rowSlideOffset(280.f, 1) == -280.f,
          "the left column starts 300 px to the LEFT and travels right");
    check(ui::rowSlideOffset(280.f, 2) == 280.f && ui::rowSlideOffset(280.f, 3) == 280.f,
          "the right column starts 300 px to the right and travels left");

    // --- The wiring: SelectMenu::update's tail is the original's tail ------------------------
    {
        ui::FrontendState state;
        ui::SelectMenu menu(state);
        ui::ScreenInput confirm; confirm.confirm = true;
        ui::ScreenInput up;      up.up = true; up.upHeld = true;
        ui::ScreenInput idle;
        menu.update(confirm);   // team -> character: this panel's first phase change
        check(menu.phase() == ui::SelectPhase::Character, "the team confirm opens the character phase");
        check(menu.rowSlide(0) == 280.f, "and restarts that controller's slide");
        check(menu.rowSlide(1) == 0.f && menu.rowSlide(2) == 0.f && menu.rowSlide(3) == 0.f,
              "only the controller whose phase changed");
        for (int i = 0; i < 13; ++i) menu.update(idle);
        check(menu.rowSlide(0) == 20.f, "an unchanged phase keeps stepping it down");
        menu.update(idle);
        check(menu.rowSlide(0) == 0.f, "settled after the 15 ticks");
        menu.update(idle);
        menu.update(idle);
        check(menu.rowSlide(0) == 0.f, "and nothing restarts it while the phase holds");
        menu.update(confirm);   // character -> weapon
        check(menu.phase() == ui::SelectPhase::Weapon, "the character confirm opens the weapon phase");
        check(menu.rowSlide(0) == 280.f, "which restarts the slide");
        for (int i = 0; i < 15; ++i) menu.update(idle);
        check(menu.rowSlide(0) == 0.f, "settled again");
        const int weapon = state.slots[0].weapon;
        menu.update(up);        // a row's VALUE changed, not the phase
        check(state.slots[0].weapon != weapon, "the weapon cursor moved");
        check(menu.rowSlide(0) == 0.f, "a changed row inside the phase does not restart the slide");
    }

    std::printf("select_row_slidein_test: %d failures\n", failures);
    return failures ? 1 : 0;
}
