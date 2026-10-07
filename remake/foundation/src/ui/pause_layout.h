#pragma once
// The pause overlay's geometry. **PORT DECISION — nothing here is recovered.**
//
// The original's pause draws the PAUSE banner and its rematch prompt out of
// system.cnv (docs/PAUSE.md) and has no readable menu at all, so there is no
// reference layout to transcribe: the four rows, their captions, the panel and
// every size below are the port's own. What the rule does fix is the defect the
// human reported (issue #50): the overlay used to load its caption at a constant
// 16 px and lay the block out at constant pixel offsets, so on a 540-row frame it
// was a stamp in the middle of the screen and on a 4K frame unreadable. Here the
// glyph size, the line pitch, the panel and the block's position all derive from
// the target the overlay is being drawn into, and nothing reads a constant that
// is not a ratio of that size.
//
// Device-free like the other layout rules in this directory (screen_select.h's
// scaledSpriteDst, hud.h's computeBattleHudLayout), so
// tests/pause_overlay_layout_test.cpp pins the arithmetic without a renderer.
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <vector>

#include "ui/sprite.h"   // UiRect

namespace ui {

// Body glyph cell height as a fraction of the canvas's shorter side. 0.045 puts the
// body text at 24 px on a 540-row frame and 49 px on a 1080-row one — the ratio is
// the rule, so a 4-view split (same target, one overlay over it) reads exactly as
// large as the single-view frame it splits.
inline constexpr float kPauseFontFrac = 0.045f;
// Clamps: below 12 px a caption is not text any more, and past 96 px the menu would
// be taller than most frames for no gain.
inline constexpr float kPauseFontMinPx = 12.f;
inline constexpr float kPauseFontMaxPx = 96.f;
// The title relative to the body size. There is no footer step any more: the binding-hint
// line that used it was the widest line in the block and so set the panel's width, which ran
// past a 4:3 frame — the rows are the menu and the keys live on the options screen.
inline constexpr float kPauseTitleScale = 1.35f;
// Baseline-to-baseline step and the panel's margin, both multiples of the body size.
inline constexpr float kPauseLinePitch = 1.5f;
inline constexpr float kPausePanelPad = 0.7f;
// The backing panel: dark grey, mostly opaque, so the block reads over a bright stage
// (issue #50 defect 4; the 55 % full-frame dim alone was not enough).
inline constexpr float kPausePanelGrey = 0.16f;
inline constexpr float kPausePanelAlpha = 0.78f;

// One menu line as measured through the loaded caption face: `width` is what
// CaptionText::width() returns — the line's drawn width when the glyphs are drawn at the
// cell height the face was rasterized at — and `scale` the line's own size relative to the
// body (title, row or footer). The layout converts both to the target's pixels, so the
// caller measures and nothing else.
struct PauseLine {
    float width = 0.f;
    float scale = 1.f;
};

struct PauseOverlayLayout {
    float  fontPx = 16.f;      // the body glyph cell height in target pixels
    float  drawScale = 1.f;    // fontPx / captionCellPx: what the caller draws at
    float  pitch = 24.f;       // y step between lines, target pixels
    float  textX = 0.f;        // pen x shared by every line
    float  firstY = 0.f;       // pen y of the first line
    UiRect panel{};            // the backing panel, target pixels
    UiColor panelColor{};      // straight-alpha dark grey for pushSolid
    bool   valid = false;      // false when the target or the caption size is unusable
};

// The whole overlay geometry from the target size and the measured lines. The block is
// centred on the target and the panel is the block's own box plus the padding, so the
// panel is "sized to the text" by construction rather than by a second constant.
// `captionCellPx` is the cell height the face was rasterized at (kPauseFontCellPx in
// main.cpp): dividing the layout's own size by it is the one conversion between the
// caption's units and the target's pixels, and it is here so the test can pin it.
inline PauseOverlayLayout computePauseOverlayLayout(uint32_t targetW, uint32_t targetH,
                                                    float captionCellPx,
                                                    const std::vector<PauseLine>& lines) {
    PauseOverlayLayout out;
    if (targetW == 0 || targetH == 0 || captionCellPx <= 0.f || lines.empty()) return out;
    out.valid = true;
    const float shorter = (float)std::min(targetW, targetH);
    out.fontPx = std::clamp(std::round(shorter * kPauseFontFrac), kPauseFontMinPx,
                            kPauseFontMaxPx);
    out.drawScale = out.fontPx / captionCellPx;
    out.pitch = std::round(out.fontPx * kPauseLinePitch);
    const float pad = std::round(out.fontPx * kPausePanelPad);
    float blockW = 0.f, blockH = 0.f;
    for (const PauseLine& line : lines) {
        blockW = std::max(blockW, line.width * out.drawScale * line.scale);
        blockH = std::max(blockH, out.fontPx * line.scale);
    }
    // The tallest line's box plus one pitch per remaining line: the block the panel wraps.
    blockH += out.pitch * (float)(lines.size() - 1);
    const float left = std::round(((float)targetW - blockW) * .5f);
    const float top = std::round(((float)targetH - blockH) * .5f);
    out.textX = left;
    out.firstY = top;
    out.panel = UiRect{left - pad, top - pad, blockW + pad * 2.f, blockH + pad * 2.f};
    out.panelColor = UiColor{kPausePanelGrey, kPausePanelGrey, kPausePanelGrey,
                             kPausePanelAlpha};
    return out;
}

}  // namespace ui
