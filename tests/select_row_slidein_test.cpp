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
// Issue #44 extends the same file with the two things #43 left. Its line numbers are
// research/decompiled/FUN_0040b2b0.c (the live original's copy is shifted by one) unless the
// live original is named:
//
//  3. The flashing cell — the non-selected branch (:123-130; the call at :128-129) draws an
//     unselected slot from cell (local_2c, bVar1), which is (2,1) while its value is < 1.0 and
//     (0,0) after; cell (2,1) of the `i%02d` sheet is the white silhouette (measured, 100 %
//     opaque white on this install) and FUN_00655830 has no colour parameter, so the white is
//     the cell.
//  4. The entry screen flash — the draw's own tail (:466-475; :480-489 in the live original)
//     pushes two white 800x600 quads whose alpha windows meet at tick 35.
//
// The literals below are the recovered constants, not tuned values: 0.1 = 0x3dcccccd
// (_DAT_006a1984), 1.0 = _DAT_006a16d0, the stagger's 5, 300.0 = 0x43960000, 20.0 =
// _DAT_006a16c4, the > 0.0 guard's _DAT_006a16c8, the flash's 0xf/'\x18'/'\f' and the
// 0x18/0x22/0x37 tick bounds.
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

    // --- The flashing cell while a slot's value is below 1.0 (FUN_0040b2b0:96-131) ----------
    {
        // The original's non-selected branch calls FUN_00655830(x, y, local_2c, bVar1) with
        // local_2c = 2 while the slot is revealing and 0 after, and bVar1 the same < 1.0 test
        // (:97-102 sets it, :128-129 is the call). FUN_00655830 has no colour parameter:
        // param_4/param_5 are the cell's column and row and only feed the quad's UVs
        // (:24-31 in research/decompiled, :21-28 in the live original). The white is the cell.
        const ui::SelectChibiCell flash = ui::selectChibiCell(false, 15, true);
        check(flash.col == 2 && flash.row == 1,
              "a revealing slot draws atlas cell (2,1) (local_2c = 2, bVar1 = true)");
        const ui::SelectChibiCell settled = ui::selectChibiCell(false, 15, false);
        check(settled.col == 0 && settled.row == 0,
              "a settled slot draws cell (0,0) (local_2c = 0, bVar1 = false)");
        // The cell is the draw's src rect: 80x128 at (col*80, row*128) — (160,128) for the
        // flashing cell. Measured on this install (data/select/i00.cnv): that cell is 100 %
        // opaque white, mean RGB 255/255/255, while the other five are coloured art.
        const ui::UiRect cellRect{float(flash.col) * 80.f, float(flash.row) * 128.f, 80.f, 128.f};
        check(sameRect(cellRect, ui::UiRect{160.f, 128.f, 80.f, 128.f}),
              "and that cell is the 80x128 rect at (160,128) of the i%02d sheet");
        // A selected slot draws the idle CYCLE instead, even while its ramp is below 1.0: the
        // original's branch at :106 tests the panel match, not the ramp. Cells (1,0) (2,0)
        // (0,1) (1,1) over 40 ticks — the port's existing cell%3/cell/3 spelling.
        const auto idle = [](int tick) { return ui::selectChibiCell(true, tick, true); };
        check(idle(0).col == 1 && idle(0).row == 0,
              "a selected slot's idle cycle starts on cell (1,0) even while revealing");
        check(idle(10).col == 2 && idle(10).row == 0, "at tick 10 it is on (2,0)");
        check(idle(20).col == 0 && idle(20).row == 1, "at tick 20 on (0,1)");
        check(idle(30).col == 1 && idle(30).row == 1, "at tick 30 on (1,1)");
        check(idle(40).col == 1 && idle(40).row == 0,
              "and the cycle wraps at 40 ticks (the same counter the draw already used)");
        // revealing() is the draw's own bVar1 and the ramp's guard: it is true for a slot that
        // has not started (value 0) as well as one mid-flight, which is why a not-yet-started
        // slot also draws the white cell on the very first ticks.
        ui::SelectReveal reveal;
        check(reveal.revealing(15) && ui::selectChibiCell(false, 1, reveal.revealing(15)).col == 2,
              "a slot that has not started yet is still 'revealing', so it draws white too");
        for (int tick = 1; tick <= 32; ++tick) reveal.tick(tick);
        check(!reveal.revealing(0) && !reveal.revealing(15), "all settled after the last one");
    }

    // --- The entry screen flash (FUN_0040b2b0:466-475) --------------------------------------
    {
        // Two full-screen 800x600 quads with the call's own `| 0xffffff`: white, NOT the black
        // cross-fade of FUN_0040b1f0:23-24 / scene+0x3c42, which the port already has as the
        // screen stack's fade. The windows are [25..34] rising and [35..54] falling.
        check(ui::SelectFlash::alpha8(24) == 0, "no flash before tick 25 (0x18 < tick)");
        check(ui::SelectFlash::alpha8(25) == 15, "the flash opens on tick 25 at alpha 15 (+0xf)");
        check(ui::SelectFlash::alpha8(26) == 39, "and climbs by 24 ('\\x18') per tick");
        check(ui::SelectFlash::alpha8(34) == 231, "reaching 231 on the ramp's last tick");
        check(ui::SelectFlash::alpha8(35) == 255,
              "the peak is tick 35, fully opaque ((55 - 35) * 12 + 15)");
        check(ui::SelectFlash::alpha8(36) == 243, "the fall is 12 ('\\f') per tick");
        check(ui::SelectFlash::alpha8(54) == 27, "tick 54, the last tick drawn, is alpha 27");
        check(ui::SelectFlash::alpha8(55) == 0, "tick 55 has no quad (tick < 0x37)");
        int drawn = 0, peakTick = -1, peakAlpha = 0;
        for (int tick = 0; tick <= 80; ++tick) {
            const int a = ui::SelectFlash::alpha8(tick);
            if (a > 0) ++drawn;
            if (a > peakAlpha) { peakAlpha = a; peakTick = tick; }
        }
        check(drawn == 30 && peakTick == 35 && peakAlpha == 255,
              "30 ticks drawn (25..54) and the maximum is tick 35 alone at 255");
        // Monotone rise then monotone fall, i.e. the two windows really are one curve.
        bool rises = true, falls = true;
        for (int tick = ui::SelectFlash::kFirst; tick < ui::SelectFlash::kPeak; ++tick)
            rises &= ui::SelectFlash::alpha8(tick + 1) > ui::SelectFlash::alpha8(tick);
        for (int tick = ui::SelectFlash::kPeak; tick < ui::SelectFlash::kLast; ++tick)
            falls &= ui::SelectFlash::alpha8(tick + 1) < ui::SelectFlash::alpha8(tick);
        check(rises && falls, "it rises every tick to its peak and falls every tick after");
        // It is drawn in white: alpha8 << 24 | 0xffffff, so r/g/b are 1 at every tick.
        const ui::UiColor color = ui::SelectFlash::color(35);
        check(color.r == 1.f && color.g == 1.f && color.b == 1.f && near(color.a, 1.f),
              "the quad is white (| 0xffffff) and fully opaque at the peak");
        check(ui::SelectFlash::color(24).a == 0.f, "and carries no alpha outside the windows");
        // The overlap with the reveal, which is what the human sees: the flash opens while
        // five slots (11..15) are still mid-reveal — slot i settles at i + 15 — and peaks
        // once the last of them (slot 15, tick 30) has settled.
        ui::SelectReveal reveal;
        int tick = 0;
        while (tick < ui::SelectFlash::kFirst) reveal.tick(++tick);
        int moving = 0;
        for (int i = 0; i < 16; ++i) moving += reveal.revealing(i);
        check(moving == 5, "five slots are still revealing when the flash opens (tick 25)");
        while (tick < ui::SelectFlash::kPeak) reveal.tick(++tick);
        moving = 0;
        for (int i = 0; i < 16; ++i) moving += reveal.revealing(i);
        check(moving == 0, "and none is left at the peak (tick 35; slot 15 settles at 30)");
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
