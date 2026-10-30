// The pause overlay's layout rule (ui/pause_layout.h). The overlay is a port-only feature
// (#15, docs/PAUSE.md): the original draws a banner and a rematch prompt and has no readable
// menu, so there is nothing to compare against and nothing here is "recovered". What this
// pins is the contract issue #50's criteria state instead: the glyph size, the line pitch
// and the backing panel all derive from the canvas, the panel is the measured text block
// plus its margin, the block stays inside the frame at every size, and the same target gives
// the same menu whether it is a single view or a 4-view split.
#include "ui/pause_layout.h"

#include <cmath>
#include <cstdio>
#include <vector>

namespace {
int failures = 0;
void check(bool ok, const char* what) {
    if (!ok) {
        ++failures;
        std::printf("FAIL: %s\n", what);
    }
}
bool near(float a, float b, float tol = .001f) { return std::fabs(a - b) <= tol; }

// The cell height main.cpp rasterizes the caption at (kPauseFontCellPx there): the layout's
// one conversion between the caption's own units and target pixels.
constexpr float kCell = 32.f;

// The menu's line set as the overlay measures it: a short title and four rows. There is no
// binding footer — it was the widest line, so it set the panel's width and ran past a 4:3
// frame — so the widest line is now a row.
std::vector<ui::PauseLine> menuLines() {
    return {{132.f, ui::kPauseTitleScale}, {210.f, 1.f}, {190.f, 1.f},
            {430.f, 1.f}, {352.f, 1.f}};
}

// The tallest line's scale: the title.
float tallest(const std::vector<ui::PauseLine>& lines) {
    float out = 0.f;
    for (const ui::PauseLine& line : lines) out = std::max(out, line.scale);
    return out;
}

float widest(const std::vector<ui::PauseLine>& lines, float drawScale) {
    float out = 0.f;
    for (const ui::PauseLine& line : lines)
        out = std::max(out, line.width * drawScale * line.scale);
    return out;
}

void checkCanvas(uint32_t w, uint32_t h) {
    const std::vector<ui::PauseLine> lines = menuLines();
    const ui::PauseOverlayLayout l = ui::computePauseOverlayLayout(w, h, kCell, lines);
    check(l.valid, "a real canvas yields a valid layout");
    check(near(l.drawScale, l.fontPx / kCell), "draw scale is the layout size over the cell");
    check(l.panel.w > 0.f && l.panel.h > 0.f, "the panel has an area");
    check(l.panel.x >= 0.f && l.panel.y >= 0.f &&
              l.panel.x + l.panel.w <= (float)w + .001f &&
              l.panel.y + l.panel.h <= (float)h + .001f,
          "the panel stays inside the canvas");
    check(near(l.panel.x + l.panel.w * .5f, (float)w * .5f, 1.f), "the panel is centred in x");
    check(near(l.panel.y + l.panel.h * .5f, (float)h * .5f, 1.f), "the panel is centred in y");
    // Sized to the text: the widest line fits with the rule's margin on both sides.
    const float textW = widest(lines, l.drawScale);
    check(textW <= l.panel.w, "the widest line fits inside the panel");
    check(l.textX >= l.panel.x && l.textX + textW <= l.panel.x + l.panel.w + .001f,
          "the text block sits inside the panel");
    check(near(l.panel.w - textW, 2.f * std::round(l.fontPx * ui::kPausePanelPad), 2.f),
          "the panel is the text plus the margin on both sides");
    // Every line's cell fits between the first line's pen and the panel's bottom edge.
    const float titleScale = tallest(lines);
    const float blockBottom = l.firstY + l.pitch * (float)(lines.size() - 1) +
                              l.fontPx * titleScale;
    check(l.firstY >= l.panel.y && blockBottom <= l.panel.y + l.panel.h + .001f,
          "the block fits inside the panel");
    check(l.pitch >= l.fontPx * titleScale, "the pitch is at least the tallest line's cell");
    // The overlay is one block over the whole target, so a split-screen frame (same target)
    // reads at exactly this size; the shorter side drives it, not the wider one.
    const ui::PauseOverlayLayout vertical = ui::computePauseOverlayLayout(h, w, kCell, lines);
    if (w != h)
        check(near(vertical.fontPx, l.fontPx), "the shorter side fixes the size");
}

void checkDegenerate() {
    const std::vector<ui::PauseLine> lines = menuLines();
    check(!ui::computePauseOverlayLayout(0, 540, kCell, lines).valid, "a zero canvas is invalid");
    check(!ui::computePauseOverlayLayout(960, 0, kCell, lines).valid, "a zero height is invalid");
    check(!ui::computePauseOverlayLayout(960, 540, 0.f, lines).valid, "a zero cell is invalid");
    check(!ui::computePauseOverlayLayout(960, 540, kCell, {}).valid, "no lines is invalid");
}
}

int main() {
    // The three sizes the issue names, plus the split-screen target and two extremes.
    checkCanvas(960, 540);
    checkCanvas(1920, 1080);
    checkCanvas(3840, 2160);
    checkCanvas(2560, 1080);
    checkCanvas(320, 180);

    const std::vector<ui::PauseLine> lines = menuLines();
    const ui::PauseOverlayLayout small = ui::computePauseOverlayLayout(960, 540, kCell, lines);
    const ui::PauseOverlayLayout big = ui::computePauseOverlayLayout(1920, 1080, kCell, lines);
    // Criterion 3: the size is canvas-derived, so doubling the frame doubles the menu.
    check(near(big.fontPx, small.fontPx * 2.f, small.fontPx * .1f),
          "1080p is twice the 540-row menu within rounding");
    check(big.panel.w > small.panel.w * 1.8f && big.panel.h > small.panel.h * 1.8f,
          "the panel scales with the canvas");
    // The legibility floor the human asked for: the smallest cell at 540 rows.
    check(small.fontPx >= 12.f, "the body cell is at least 12 px at 960x540");
    // Monotone in canvas size, and clamped at both ends.
    check(ui::computePauseOverlayLayout(640, 360, kCell, lines).fontPx <= small.fontPx,
          "a smaller canvas is not a bigger menu");
    check(near(ui::computePauseOverlayLayout(64, 64, kCell, lines).fontPx, ui::kPauseFontMinPx),
          "a tiny canvas clamps at the minimum font");
    check(near(ui::computePauseOverlayLayout(7680, 4320, kCell, lines).fontPx,
               ui::kPauseFontMaxPx),
          "an 8K canvas clamps at the maximum font");

    checkDegenerate();

    if (failures == 0) std::printf("pause_overlay_layout_test: all checks passed\n");
    return failures == 0 ? 0 : 1;
}
