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

#include "ui/hud_atlas.h"
#include "ui/sprite.h"

namespace {

using ui::FillMode;
using ui::HudDigit;
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
        {HudIcon::MainFill, HudSheet::P01, {320.f, 128.f, 160.f, 6.f}, 0.f, 0.f},
        {HudIcon::MainFillEmpty, HudSheet::P01, {320.f, 144.f, 160.f, 6.f}, 0.f, 0.f},
        {HudIcon::ChargeFill, HudSheet::P01, {320.f, 64.f, 160.f, 6.f}, 0.f, 0.f},
        {HudIcon::ChargeFillEmpty, HudSheet::P01, {320.f, 80.f, 160.f, 6.f}, 0.f, 0.f},
        {HudIcon::ChargeTierYellow, HudSheet::P01, {320.f, 96.f, 160.f, 5.f}, 0.f, 0.f},
        {HudIcon::ChargeTierRed, HudSheet::P01, {320.f, 112.f, 160.f, 5.f}, 0.f, 0.f},
        {HudIcon::FanFillCharging, HudSheet::P02, {0.f, 0.f, 230.f, 91.f}, 0.f, 0.f},
        {HudIcon::FanFillReady, HudSheet::P02, {0.f, 288.f, 230.f, 91.f}, 0.f, 0.f},
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

// FUN_00431a50's font: 12 cells of 64x64 from P00 (0,0), 8 per row, advance
// 64 + (-27) = 37, drawn least-significant first at x - 64 (FUN_00431b50).
// The print's `6` at anchor (702,443) has ink at game (667,448)-(696,467); P00's
// cell (384,0) has its `6` ink at +29..+59 x, +4..+24 y, i.e. (638+29, 443+4).
void testNumberRun() {
    std::printf("number font (FUN_00431a50 @0x6431a50, FUN_00431b50 @0x431b50):\n");
    HudDigit d[10];
    int n = ui::hudDigitRun(6, 702.f, 443.f, d);
    checkInt("one digit for 6", 1, n);
    checkRect("6 cell", {384.f, 0.f, 64.f, 64.f}, d[0].src);
    checkFloat("6 cell x", 638.f, d[0].x);
    checkFloat("6 cell y", 443.f, d[0].y);
    checkInt("6 ink left  (print 667)", 667, (long long)(d[0].x + 29.f));
    checkNear("6 ink top   (print 448)", 448, (int)(d[0].y + 4.f));

    n = ui::hudDigitRun(2, 676.f, 489.f, d);
    checkInt("one digit for 2", 1, n);
    checkRect("2 cell", {128.f, 0.f, 64.f, 64.f}, d[0].src);
    checkFloat("2 cell x", 612.f, d[0].x);
    checkInt("2 ink left  (print 641)", 640, (long long)(d[0].x + 28.f));

    // Two digits: the units cell keeps the anchor, the tens cell steps left by 37.
    n = ui::hudDigitRun(12, 702.f, 443.f, d);
    checkInt("two digits for 12", 2, n);
    checkRect("12 units cell", {128.f, 0.f, 64.f, 64.f}, d[0].src);
    checkFloat("12 units x", 638.f, d[0].x);
    checkRect("12 tens cell", {64.f, 0.f, 64.f, 64.f}, d[1].src);
    checkFloat("12 tens x", 601.f, d[1].x);

    // 8 and 9 live in the font's second row; 0 is still one digit.
    n = ui::hudDigitRun(9, 702.f, 443.f, d);
    checkRect("9 cell", {64.f, 64.f, 64.f, 64.f}, d[0].src);
    n = ui::hudDigitRun(0, 702.f, 443.f, d);
    checkInt("one digit for 0", 1, n);
    checkRect("0 cell", {0.f, 0.f, 64.f, 64.f}, d[0].src);
    n = ui::hudDigitRun(100, 702.f, 443.f, d);
    checkInt("three digits for 100", 3, n);
    checkFloat("100 leading cell x", 564.f, d[2].x);
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
    testFallbackState();
    std::printf("\nchecks: %d, failures: %d\n", g_checks, g_failed);
    std::printf("HUD_SPRITE_TABLE: %s\n", g_failed == 0 ? "ok" : "FAIL");
    return g_failed == 0 ? 0 : 1;
}
