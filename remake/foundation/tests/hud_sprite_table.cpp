// =============================================================================
//  hud_sprite_table.cpp — host test for the battle HUD's sprite table and its
//  draw geometry (ui/hud_atlas.h + the pure half of ui/sprite.h).
//
//  No WebGPU device, no window, no game data: everything here is arithmetic over
//  the constants transcribed from the exe, so it runs anywhere.
//
//    g++ -std=gnu++17 -Wall -Wextra -I remake/foundation/src
//        -isystem <wgpu include> -isystem <wgpu include>/webgpu
//        remake/foundation/tests/hud_sprite_table.cpp -o /tmp/hud_sprite_table
//    /tmp/hud_sprite_table        # prints HUD_SPRITE_TABLE: ok|FAIL
//
//  What it pins, and why each one is worth pinning:
//    * the sprite table itself (BATTLE-HUD-SPEC.md §3's rects, FUN_00642510 /
//      FUN_00642a00 / FUN_00642c50) — a wrong rect or pivot silently draws the
//      wrong art at the right place, which no capture diff names;
//    * the anchors' derived top-left corners, which is where the reference print
//      was measured: HP (492,540), MAIN (607,442), CHARGE (581,490), fan (10,467);
//    * the fill/ghost rects at 100%, which the print measures pixel-exactly:
//      HP (505,565) 230x14, MAIN (623,471) 160x6, CHARGE (597,517) 160x6;
//    * the number font's right-aligned run, including the digit ink offset the
//      print confirms for the frame's `6` and `2`;
//    * FUN_00645250's three growth modes in both destination and source;
//    * the "no atlas, no art HUD" state, which is the documented fallback.
// =============================================================================

#include <cmath>
#include <cstdio>

#include "game/hud_bridge.h"
#include "ui/hud_atlas.h"
#include "ui/sprite.h"

namespace {

using ui::FillMode;
using ui::HudDigit;
using ui::HudFont;
using ui::HudIcon;
using ui::HudSheet;
using ui::HudSprite;
using ui::UiRect;

int g_checks = 0;
int g_failed = 0;

void checkInt(const char* what, long long want, long long got) {
    ++g_checks;
    if (want == got) {
        std::printf("  [ok]   %s = %lld\n", what, got);
    } else {
        std::printf("  [FAIL] %s: want %lld, got %lld\n", what, want, got);
        ++g_failed;
    }
}

void checkFloat(const char* what, float want, float got) {
    ++g_checks;
    if (std::fabs(want - got) < 1e-4f) {
        std::printf("  [ok]   %s = %.3f\n", what, (double)got);
    } else {
        std::printf("  [FAIL] %s: want %.3f, got %.3f\n", what, (double)want, (double)got);
        ++g_failed;
    }
}

// The print is a lossy WebP: its ink mask is thresholded, so a measured edge can
// land a pixel either side of the sprite's own alpha edge. Agreement within 1 px
// is the honest bound for a print-derived expectation; the cell geometry above is
// exact and is checked exactly.
void checkNear(const char* what, int want, int got) {
    ++g_checks;
    if (std::abs(want - got) <= 1) {
        std::printf("  [ok]   %s = %d (print %d, within 1 px)\n", what, got, want);
    } else {
        std::printf("  [FAIL] %s: print says %d, sprite geometry gives %d (>1 px apart)\n", what,
                    want, got);
        ++g_failed;
    }
}

void checkRect(const char* what, UiRect want, UiRect got) {
    ++g_checks;
    const bool ok = std::fabs(want.x - got.x) < 1e-4f && std::fabs(want.y - got.y) < 1e-4f &&
                    std::fabs(want.w - got.w) < 1e-4f && std::fabs(want.h - got.h) < 1e-4f;
    if (ok) {
        std::printf("  [ok]   %s = (%.0f,%.0f %.0fx%.0f)\n", what, (double)got.x, (double)got.y,
                    (double)got.w, (double)got.h);
    } else {
        std::printf("  [FAIL] %s: want (%.0f,%.0f %.0fx%.0f), got (%.0f,%.0f %.0fx%.0f)\n", what,
                    (double)want.x, (double)want.y, (double)want.w, (double)want.h, (double)got.x,
                    (double)got.y, (double)got.w, (double)got.h);
        ++g_failed;
    }
}

const HudSprite& S(HudIcon i) { return ui::hudSprite(i); }

// The sub-rect and pivot of every element this track draws, straight from the
// exe's FUN_00655b20 calls (addresses in hud_atlas.h). Order follows the enum.
void testSpriteTable() {
    std::printf("sprite table (FUN_00642510 / FUN_00642a00 / FUN_00642c50):\n");
    struct Row {
        HudIcon icon;
        HudSheet sheet;
        UiRect src;
        float px, py;
    };
    const Row rows[] = {
        {HudIcon::HpFrame, HudSheet::P01, {32.f, 192.f, 256.f, 64.f}, 13.f, 25.f},
        {HudIcon::MainFrame, HudSheet::P01, {64.f, 128.f, 192.f, 64.f}, 16.f, 29.f},
        {HudIcon::ChargeFrame, HudSheet::P01, {64.f, 64.f, 192.f, 64.f}, 16.f, 27.f},
        {HudIcon::FanFrame, HudSheet::P01, {0.f, 256.f, 300.f, 128.f}, 45.f, 21.f},
        {HudIcon::MaxLabel, HudSheet::P00, {384.f, 384.f, 128.f, 128.f}, 64.f, 64.f},
        {HudIcon::HpFill, HudSheet::P02, {0.f, 480.f, 230.f, 14.f}, 0.f, 0.f},
        {HudIcon::HpFillPale, HudSheet::P02, {256.f, 480.f, 230.f, 14.f}, 0.f, 0.f},
        {HudIcon::HpFillGhost, HudSheet::P02, {0.f, 496.f, 230.f, 14.f}, 0.f, 0.f},
        {HudIcon::MainFill, HudSheet::P01, {320.f, 128.f, 160.f, 6.f}, 0.f, 0.f},
        {HudIcon::MainFillEmpty, HudSheet::P01, {320.f, 144.f, 160.f, 6.f}, 0.f, 0.f},
        {HudIcon::ChargeFill, HudSheet::P01, {320.f, 64.f, 160.f, 6.f}, 0.f, 0.f},
        {HudIcon::ChargeFillEmpty, HudSheet::P01, {320.f, 80.f, 160.f, 6.f}, 0.f, 0.f},
        {HudIcon::ChargeTierYellow, HudSheet::P01, {320.f, 96.f, 160.f, 5.f}, 0.f, 0.f},
        {HudIcon::ChargeTierRed, HudSheet::P01, {320.f, 112.f, 160.f, 5.f}, 0.f, 0.f},
        {HudIcon::FanFillCharging, HudSheet::P02, {0.f, 0.f, 230.f, 91.f}, 0.f, 0.f},
        {HudIcon::FanFillReady, HudSheet::P02, {0.f, 288.f, 230.f, 91.f}, 0.f, 0.f},
        {HudIcon::FanFillReadyAlt, HudSheet::P02, {0.f, 384.f, 230.f, 91.f}, 0.f, 0.f},
        {HudIcon::FanCaption, HudSheet::P01, {0.f, 384.f, 128.f, 32.f}, 0.f, 0.f},
        {HudIcon::BalloonLeft, HudSheet::P00, {0.f, 320.f, 192.f, 192.f}, 96.f, 160.f},
        {HudIcon::BalloonRight, HudSheet::P00, {192.f, 320.f, 192.f, 192.f}, 96.f, 160.f},
        {HudIcon::LimitLabel, HudSheet::P00, {384.f, 320.f, 96.f, 32.f}, 56.f, 8.f},
        {HudIcon::StaminaFrame, HudSheet::P01, {64.f, 0.f, 192.f, 64.f}, 96.f, 32.f},
        {HudIcon::StaminaFill, HudSheet::P01, {320.f, 0.f, 107.f, 6.f}, 53.f, 3.f},
        {HudIcon::CommandLabel, HudSheet::P03, {0.f, 0.f, 128.f, 64.f}, 64.f, 32.f},
        {HudIcon::Ring, HudSheet::P03, {0.f, 128.f, 128.f, 128.f}, 64.f, 64.f},
        {HudIcon::ComBarFrame, HudSheet::P01, {320.f, 192.f, 192.f, 64.f}, 96.f, 32.f},
        {HudIcon::ComBarFill, HudSheet::P01, {320.f, 320.f, 80.f, 6.f}, 40.f, 3.f},
        {HudIcon::ComBarFillGhost, HudSheet::P01, {320.f, 352.f, 80.f, 6.f}, 40.f, 3.f},
        {HudIcon::TagCell, HudSheet::P01, {320.f, 256.f, 64.f, 32.f}, 32.f, 16.f},
        {HudIcon::AlertPale, HudSheet::P06, {0.f, 128.f, 128.f, 128.f}, 64.f, 64.f},
        {HudIcon::KoSting, HudSheet::P09, {0.f, 256.f, 512.f, 256.f}, 256.f, 128.f},
    };
    for (const Row& r : rows) {
        checkRect("src", r.src, S(r.icon).src);
        checkInt("sheet", (long long)r.sheet, (long long)S(r.icon).sheet);
        checkFloat("pivot x", r.px, S(r.icon).pivotX);
        checkFloat("pivot y", r.py, S(r.icon).pivotY);
    }
}

// The anchors are FUN_00644150's immediates; the derived top-left is what the
// reference print was matched against (template match over each sprite's opaque
// pixels, best offset (0,0) for all four).
void testFrameAnchors() {
    std::printf("frame anchors -> top-left (FUN_00644150 @0x644187/0x64428d/0x6448e5/0x64491d):\n");
    const struct {
        HudIcon icon;
        float ax, ay;
        UiRect want;
    } rows[] = {
        {HudIcon::HpFrame, 505.f, 565.f, {492.f, 540.f, 256.f, 64.f}},
        {HudIcon::MainFrame, 623.f, 471.f, {607.f, 442.f, 192.f, 64.f}},
        {HudIcon::ChargeFrame, 597.f, 517.f, {581.f, 490.f, 192.f, 64.f}},
        {HudIcon::FanFrame, 55.f, 488.f, {10.f, 467.f, 300.f, 128.f}},
        {HudIcon::MaxLabel, 64.f, 534.f, {0.f, 470.f, 128.f, 128.f}},
        // The balloon corners: the readout cluster's own top-lefts, which the print
        // measures as "0%" ink (73,83)-(106,103) for the number cell and (116,84)
        // for the '%' — both reproduced by these two anchors.
        {HudIcon::LimitLabel, 70.f, 110.f, {14.f, 102.f, 96.f, 32.f}},
        {HudIcon::BalloonLeft, 85.f, 140.f, {-11.f, -20.f, 192.f, 192.f}},
        {HudIcon::LimitLabel, 700.f, 110.f, {644.f, 102.f, 96.f, 32.f}},
        {HudIcon::BalloonRight, 715.f, 140.f, {619.f, -20.f, 192.f, 192.f}},
        {HudIcon::StaminaFrame, 400.f, 517.f, {304.f, 485.f, 192.f, 64.f}},
        {HudIcon::StaminaFill, 400.f, 517.f, {347.f, 514.f, 107.f, 6.f}},
        {HudIcon::CommandLabel, 216.f, 520.f, {152.f, 488.f, 128.f, 64.f}},
        {HudIcon::Ring, 400.f, 162.f, {336.f, 98.f, 128.f, 128.f}},
        {HudIcon::ComBarFrame, 400.f, 99.f, {304.f, 67.f, 192.f, 64.f}},
        {HudIcon::ComBarFill, 400.f, 99.f, {360.f, 96.f, 80.f, 6.f}},
        {HudIcon::TagCell, 424.f, 115.f, {392.f, 99.f, 64.f, 32.f}},
        {HudIcon::AlertPale, 400.f, 64.f, {336.f, 0.f, 128.f, 128.f}},
        {HudIcon::KoSting, 400.f, 300.f, {144.f, 172.f, 512.f, 256.f}},
    };
    for (const auto& r : rows) {
        const HudSprite& s = S(r.icon);
        checkRect("top-left", r.want, ui::spriteDst(r.ax, r.ay, s.src.w, s.src.h, s.pivotX,
                                                    s.pivotY));
    }
}

// At 100% a fill is the plain sprite rect at its anchor; the print measures the
// HP and MAIN fills pixel-exactly there (503,571)-(733,585) and
// (621,477)-(781,483) in print space = game (505,565) and (623,471).
void testFillGeometry() {
    std::printf("fill geometry (FUN_00645250 @0x645250):\n");
    checkRect("HP fill at 100%", {505.f, 565.f, 230.f, 14.f},
              ui::fillDst(ui::spriteDst(505.f, 565.f, 230.f, 14.f, 0.f, 0.f), 1.f, FillMode::Right));
    checkRect("MAIN fill at 100%", {623.f, 471.f, 160.f, 6.f},
              ui::fillDst(ui::spriteDst(623.f, 471.f, 160.f, 6.f, 0.f, 0.f), 1.f, FillMode::Right));
    checkRect("CHARGE fill at 100%", {597.f, 517.f, 160.f, 6.f},
              ui::fillDst(ui::spriteDst(597.f, 517.f, 160.f, 6.f, 0.f, 0.f), 1.f, FillMode::Right));

    const UiRect dst{100.f, 200.f, 160.f, 6.f};
    const UiRect src{320.f, 128.f, 160.f, 6.f};
    // Mode 0 grows right: the left edge is fixed and both dst and source are
    // scaled by the fraction, which is why a half bar shows the whole ramp.
    checkRect("mode 0 dst at 25%", {100.f, 200.f, 40.f, 6.f}, ui::fillDst(dst, 0.25f, FillMode::Right));
    checkRect("mode 0 src at 25%", {320.f, 128.f, 40.f, 6.f}, ui::fillSrc(src, 0.25f, FillMode::Right));
    // Mode 1 grows up: the bottom edge is fixed and the source loses its top.
    checkRect("mode 1 dst at 25%", {100.f, 204.5f, 160.f, 1.5f},
              ui::fillDst(dst, 0.25f, FillMode::Up));
    checkRect("mode 1 src at 25%", {320.f, 132.5f, 160.f, 1.5f}, ui::fillSrc(src, 0.25f, FillMode::Up));
    // Mode 2 grows left: the right edge is fixed and the source loses its right.
    checkRect("mode 2 dst at 25%", {220.f, 200.f, 40.f, 6.f}, ui::fillDst(dst, 0.25f, FillMode::Left));
    checkRect("mode 2 src at 25%", {440.f, 128.f, 40.f, 6.f}, ui::fillSrc(src, 0.25f, FillMode::Left));
    // An empty gauge draws nothing at all (the composer's frac <= 0 guard is what
    // the print's 0% fan relies on), and over 100% is clamped by the caller.
    checkFloat("mode 0 dst width at 0%", 0.f, ui::fillDst(dst, 0.f, FillMode::Right).w);
}

// FUN_00431a50's fonts. Big white: 12 cells of 64x64 from P00 (0,0), 8 per row,
// leading 0xc1e00000 = -28, so the advance is 64 - 28 = 36; drawn least-significant
// first at x - 64 (FUN_00431b50). The print's `6` at anchor (702,443) has ink at game
// (667,448)-(696,467); P00's cell (384,0) has its `6` ink at +29..+59 x, +4..+24 y.
// The LIMIT readout's "100" at (138,110) half scale is the print's multi-digit case:
// its three cells sit at 106/88/70, which the print's ink confirms (119/101/90).
void testNumberRun() {
    std::printf("number fonts (FUN_00431a50 @0x6431a50, FUN_00431b50 @0x431b50):\n");
    HudDigit d[10];
    int n = ui::hudDigitRun(HudFont::BigWhite, 6, 702.f, 443.f, 1.f, d);
    checkInt("one digit for 6", 1, n);
    checkRect("6 cell", {384.f, 0.f, 64.f, 64.f}, d[0].src);
    checkFloat("6 cell x", 638.f, d[0].x);
    checkFloat("6 cell y", 443.f, d[0].y);
    checkInt("6 ink left  (print 667)", 667, (long long)(d[0].x + 29.f));
    checkNear("6 ink top   (print 448)", 448, (int)(d[0].y + 4.f));

    n = ui::hudDigitRun(HudFont::BigWhite, 2, 676.f, 489.f, 1.f, d);
    checkInt("one digit for 2", 1, n);
    checkRect("2 cell", {128.f, 0.f, 64.f, 64.f}, d[0].src);
    checkFloat("2 cell x", 612.f, d[0].x);
    checkInt("2 ink left  (print 641)", 640, (long long)(d[0].x + 28.f));

    // Two digits: the units cell keeps the anchor, the tens cell steps left by 36.
    n = ui::hudDigitRun(HudFont::BigWhite, 12, 702.f, 443.f, 1.f, d);
    checkInt("two digits for 12", 2, n);
    checkRect("12 units cell", {128.f, 0.f, 64.f, 64.f}, d[0].src);
    checkFloat("12 units x", 638.f, d[0].x);
    checkRect("12 tens cell", {64.f, 0.f, 64.f, 64.f}, d[1].src);
    checkFloat("12 tens x", 602.f, d[1].x);

    // 8 and 9 live in the font's second row; 0 is still one digit.
    n = ui::hudDigitRun(HudFont::BigWhite, 9, 702.f, 443.f, 1.f, d);
    checkRect("9 cell", {64.f, 64.f, 64.f, 64.f}, d[0].src);
    n = ui::hudDigitRun(HudFont::BigWhite, 0, 702.f, 443.f, 1.f, d);
    checkInt("one digit for 0", 1, n);
    checkRect("0 cell", {0.f, 0.f, 64.f, 64.f}, d[0].src);
    n = ui::hudDigitRun(HudFont::BigWhite, 100, 702.f, 443.f, 1.f, d);
    checkInt("three digits for 100", 3, n);
    checkFloat("100 leading cell x", 566.f, d[2].x);

    // The LIMIT readout: same font at half scale, ending on x = 138 (0x6a4c90).
    n = ui::hudDigitRun(HudFont::BigWhite, 100, 138.f, 110.f, 0.5f, d);
    checkInt("three digits for the LIMIT value", 3, n);
    checkFloat("LIMIT units cell x", 106.f, d[0].x);
    checkFloat("LIMIT units cell scale", 0.5f, d[0].scale);
    checkFloat("LIMIT tens cell x", 88.f, d[1].x);
    checkFloat("LIMIT hundreds cell x", 70.f, d[2].x);

    // The small green font (0x6c9050): 32x32 cells from P00 (0,256), 15 per row,
    // leading -4, digits 0..9 then '+ - . %' at 10..13. The balloon popup uses it.
    n = ui::hudDigitRun(HudFont::SmallGreen, 21, 110.f, 50.f, 1.f, d);
    checkInt("two small digits for 21", 2, n);
    checkRect("small units cell", {32.f, 256.f, 32.f, 32.f}, d[0].src);
    checkFloat("small units x", 78.f, d[0].x);
    checkRect("small tens cell", {64.f, 256.f, 32.f, 32.f}, d[1].src);
    checkFloat("small tens x", 50.f, d[1].x);

    // The small yellow font (D1 FPS counter): 32x32 cells from P00 (0,288), 15
    // per row, leading 0 — the 32 px pitch is measured off the atlas (a 28 px
    // pitch like SmallGreen's fails at cell 6). The print's "181" anchors at
    // (800,0) half scale: units cell x = 800-16, stepping 16 px left per digit.
    n = ui::hudDigitRun(HudFont::SmallYellow, 181, 800.f, 0.f, 0.5f, d);
    checkInt("three yellow digits for 181", 3, n);
    checkRect("181 units cell", {32.f, 288.f, 32.f, 32.f}, d[0].src);
    checkFloat("181 units cell x", 784.f, d[0].x);
    checkRect("181 tens cell", {256.f, 288.f, 32.f, 32.f}, d[1].src);
    checkFloat("181 tens cell x", 768.f, d[1].x);
    checkRect("181 hundreds cell", {32.f, 288.f, 32.f, 32.f}, d[2].src);
    checkFloat("181 hundreds cell x", 752.f, d[2].x);
    checkFloat("181 cell y", 0.f, d[0].y);
    checkFloat("181 cell scale", 0.5f, d[0].scale);
}

// FUN_00431ce0's cell draw is a *single* font cell, placed at x + scale*leading — the
// reason the readout's '%' sits four pixels left of its anchor at scale 1 and two at
// half scale. The cells are the ones the atlas holds: the big font's '%' is (5,1) =
// P00 (320,64) (its second white row reads "8 9 … % /"), the small green font's is
// (13,0) = P00 (416,256).
void testFontCells() {
    std::printf("font cells (FUN_00431ce0 @0x431ce0):\n");
    const ui::HudFontSpec& big = ui::hudFont(HudFont::BigWhite);
    const ui::HudFontSpec& small = ui::hudFont(HudFont::SmallGreen);
    checkFloat("big leading (0xc1e00000)", -28.f, big.leading);
    checkInt("big cells per row", 8, big.perRow);
    checkFloat("small leading (0xc0800000)", -4.f, small.leading);
    checkInt("small cells per row", 15, small.perRow);
    checkRect("big '%' cell (5,1)", {320.f, 64.f, 64.f, 64.f},
              UiRect{big.base.x + 5.f * big.base.w, big.base.y + 1.f * big.base.h, big.base.w,
                     big.base.h});
    checkRect("small '%' cell (13,0)", {416.f, 256.f, 32.f, 32.f},
              UiRect{small.base.x + 13.f * small.base.w, small.base.y, small.base.w,
                     small.base.h});
    // The small yellow row (D1): same 10+4 layout one row down, zero leading.
    const ui::HudFontSpec& yellow = ui::hudFont(HudFont::SmallYellow);
    checkFloat("yellow base y", 288.f, yellow.base.y);
    checkFloat("yellow leading", 0.f, yellow.leading);
    checkInt("yellow cells per row", 15, yellow.perRow);
    checkRect("yellow '%' cell (13,0)", {416.f, 288.f, 32.f, 32.f},
              UiRect{yellow.base.x + 13.f * yellow.base.w, yellow.base.y, yellow.base.w,
                     yellow.base.h});
    // The draw offset the print shows: (110,78) for the left corner's '%'.
    checkFloat("'%' draw x at scale 1", 82.f, 110.f + 1.f * big.leading);
    checkFloat("'%' draw x at scale 0.5", 124.f, 138.f + 0.5f * big.leading);
}

// FUN_00655830's cell draw: a sprite built by FUN_006556c0/55690 stores its own rect
// as the cell pitch, so cell (cx, cy) is the atlas rect offset by (cx*w, cy*h). The
// per-fighter HUD depends on exactly that: P03's ring cells are 128 px apart and the
// command label's are 128x64, P01's tag cells 64x32.
void testCellGeometry() {
    std::printf("cell draws (FUN_00655830 @0x655830):\n");
    const auto cellAt = [](HudIcon icon, int cx, int cy) {
        const HudSprite& s = S(icon);
        return UiRect{s.src.x + (float)cx * s.src.w, s.src.y + (float)cy * s.src.h, s.src.w,
                      s.src.h};
    };
    // The print's red ring is P03's (0,256,128,128) cell — the print's ink sits at
    // (368,130)-(433,195) inside the 128x128 quad centred on the projected point.
    checkRect("ring cell (0,1)", {0.f, 256.f, 128.f, 128.f}, cellAt(HudIcon::Ring, 0, 1));
    // The command label's cells: 0 適当, 1 格闘, 2 射撃, 3 集中, 4 各個, 5 後退. The
    // print's boxed 適当 is cell 0 at (216,520), whose quad origin is (152,488).
    checkRect("command cell (0,0)", {0.f, 0.f, 128.f, 64.f}, cellAt(HudIcon::CommandLabel, 0, 0));
    checkRect("command cell (3,1)", {384.f, 64.f, 128.f, 64.f},
              cellAt(HudIcon::CommandLabel, 3, 1));
    // The tag rows: 1P/2P/3P in row 0, 4P/com in row 1, the red copies four rows on.
    checkRect("tag cell (1,0) '2P'", {384.f, 256.f, 64.f, 32.f}, cellAt(HudIcon::TagCell, 1, 0));
    checkRect("tag cell (1,5) red 'com'", {384.f, 416.f, 64.f, 32.f},
              cellAt(HudIcon::TagCell, 1, 5));
    // The hypermode caption: the row is hud+0x318, and daybreak04's P01 (the copy
    // assetSource() resolves) holds OYASHIRO/FRIENDSHIP/KAKERA at 32-px rows.
    checkRect("caption row 0", {0.f, 384.f, 128.f, 32.f}, cellAt(HudIcon::FanCaption, 0, 0));
    checkRect("caption row 2", {0.f, 448.f, 128.f, 32.f}, cellAt(HudIcon::FanCaption, 0, 2));
}

// FUN_00643230's projection and the two lifts it hangs the per-fighter HUD on, plus
// the balloon scale formula. All pure arithmetic, so no camera is needed: an
// orthographic matrix that maps world units to NDC at 1/100 stands in for the fitted
// arena camera.
void testProjectionAndBalloon() {
    std::printf("per-fighter projection (FUN_00643230 @0x64333c) and balloon scale:\n");
    float x = 0.f, y = 0.f;
    ui::hudProjectClip(0.f, 0.f, x, y);
    checkFloat("clip origin x", 400.f, x);
    checkFloat("clip origin y", 300.f, y);
    ui::hudProjectClip(0.5f, -0.5f, x, y);
    checkFloat("clip (0.5,-0.5) x", 600.f, x);
    checkFloat("clip (0.5,-0.5) y", 450.f, y);

    // Column-major ortho: x_ndc = wx/400, y_ndc = wy/300 (so 300 world units is the
    // half-height), w = 1. Screen y grows downward, so +70 units lands 70 px up.
    float vp[16] = {0.f};
    vp[0] = 1.f / 400.f;
    vp[5] = 1.f / 300.f;
    vp[10] = 1.f;
    vp[15] = 1.f;
    game::GameFighterHud f;
    checkInt("a fighter at the origin is visible", 1,
             game::projectFighterHud(vp, 0.f, 0.f, 0.f, f) ? 1 : 0);
    checkFloat("ring x at the origin", 400.f, f.ringX);
    checkFloat("ring y at +70 units", 230.f, f.ringY);
    checkFloat("bar x at the origin", 400.f, f.barX);
    checkFloat("bar y at +150 units, -32 px", 118.f, f.barY);
    checkFloat("ring lift constant (FUN_00643230.c:52)", 70.f, ui::kHudRingLift);
    checkFloat("bar lift constant (FUN_00643230.c:173)", 150.f, ui::kHudBarLift);
    checkFloat("bar drop constant (0x6acf48)", 32.f, ui::kHudBarDrop);
    // Behind the eye: the original's `0 < clip.z` gate means no draw at all.
    float behind[16] = {0.f};
    behind[0] = behind[5] = behind[10] = 1.f;
    behind[15] = -1.f;
    checkInt("a fighter behind the eye is not visible", 0,
             game::projectFighterHud(behind, 0.f, 0.f, 0.f, f) ? 1 : 0);

    // The balloon: (pct*1.5 + 20 + sin(pulse*3 deg)*20)/100. At 0% with no pulse the
    // print's balloon is the 0.2-scale tip; the print's 43% balloon (ko-moment.webp)
    // is 0.845.
    checkFloat("balloon scale at 0%, rest", 0.2f, ui::hudBalloonScale(0.f, 0));
    checkFloat("balloon scale at 43%, rest", 0.845f, ui::hudBalloonScale(43.f, 0));
    checkFloat("balloon scale at 0%, pulse 30", 0.4f, ui::hudBalloonScale(0.f, 30));
}

// The composer draws the art HUD only once every sheet is uploaded; before that
// (and with no game data at all) HudComposer::compose keeps the text/bars path.
void testFallbackState() {
    std::printf("fallback state (no upload yet):\n");
    ui::HudAtlas atlas;
    ++g_checks;
    if (!atlas.ready()) {
        std::printf("  [ok]   a fresh atlas is not ready, so compose() uses the text HUD\n");
    } else {
        std::printf("  [FAIL] a fresh atlas reported ready\n");
        ++g_failed;
    }
    checkInt("P00 slot before upload", -1, atlas.sheet(HudSheet::P00));
    checkInt("P01 slot before upload", -1, atlas.sheet(HudSheet::P01));
    checkInt("P02 slot before upload", -1, atlas.sheet(HudSheet::P02));
}

}  // namespace

int main() {
    std::printf("battle HUD sprite table + draw geometry (device-free)\n\n");
    testSpriteTable();
    testFrameAnchors();
    testFillGeometry();
    testNumberRun();
    testFontCells();
    testCellGeometry();
    testProjectionAndBalloon();
    testFallbackState();
    std::printf("\nchecks: %d, failures: %d\n", g_checks, g_failed);
    std::printf("HUD_SPRITE_TABLE: %s\n", g_failed == 0 ? "ok" : "FAIL");
    return g_failed == 0 ? 0 : 1;
}
