#include "hud/fallback.h"

#include <cstdio>
#include <algorithm>

namespace ui {

DiagPanel computeDiagPanel(int viewW, int viewH, size_t lineCount, size_t maxChars) {
    DiagPanel p;
    // Longest line determines the width; one line always fits by construction.
    const float textW =
        (float)maxChars * (float)kGlyphAdvance * kDiagTextScale - kDiagTextScale;
    const float textH = (float)lineCount * kDiagLineH - (kDiagLineH - (float)kGlyphH * kDiagTextScale);
    float w = textW + kDiagPad * 2.f;
    float h = textH + kDiagPad * 2.f;
    // Never cover the whole frame on tiny surfaces: the panel is diagnostics,
    // not a splash screen.
    if (w > (float)viewW - 16.f) w = (float)viewW - 16.f;
    if (h > (float)viewH - 16.f) h = (float)viewH - 16.f;
    if (w < 64.f) w = 64.f;
    if (h < 32.f) h = 32.f;
    p.rect = UiRect{kDiagPad, kDiagPad, w, h};
    p.textX = kDiagPad + kDiagPad;
    p.textY = kDiagPad + kDiagPad;
    return p;
}

std::vector<std::string> buildDiagLines(const std::string& adapter, const std::string& backend,
                                       int viewW, int viewH, const std::string& error,
                                       unsigned long long frames, double avgDeltaMs,
                                       const std::string& extra) {
    std::vector<std::string> lines;
    char buf[256];
    std::snprintf(buf, sizeof buf, "adapter: %s [%s]", adapter.c_str(), backend.c_str());
    lines.emplace_back(buf);
    std::snprintf(buf, sizeof buf, "surface: %dx%d fifo", viewW, viewH);
    lines.emplace_back(buf);
    if (!error.empty()) {
        // Keep the panel to one error line; callers log the full diagnostic separately.
        std::string first = error.substr(0, error.find('\n'));
        if (first.size() > 60) first = first.substr(0, 57) + "...";
        lines.emplace_back("error: " + first);
    } else {
        std::snprintf(buf, sizeof buf, "frames: %llu  avg delta: %.2f ms", frames, avgDeltaMs);
        lines.emplace_back(buf);
    }
    if (!extra.empty()) lines.emplace_back(extra);
    // Hard cap: the panel sizes from lineCount, and an unbounded caller could
    // push it past the frame clamp above into a useless full-screen box.
    if (lines.size() > 24) lines.resize(24);
    return lines;
}

bool FallbackOverlay::uploadFont(SpriteRenderer& batch, std::string& error) {
    if (atlasTexture() >= 0) return true;
    std::string fontError;
    if (captions_.load(batch,14.f,fontError)) return true;
    std::vector<uint8_t> rgba;
    uint32_t w = 0, h = 0;
    buildAtlasRGBA(rgba, w, h);
    atlas_ = batch.addTexture(w, h, rgba.data(), error);
    return atlas_ >= 0;
}

void FallbackOverlay::draw(SpriteRenderer& batch, const DiagPanel& panel,
                           const std::vector<std::string>& lines) {
    DiagPanel fitted = panel;
    std::string error;
    if (captions_.atlasTexture() >= 0) {
        if (!captions_.prepare(batch,lines,error)) return;
        float width = 0;
        for (const auto& line : lines) width = std::max(width,captions_.width(line.c_str()));
        fitted.rect.w = std::clamp(width + kDiagPad*2.f,64.f,
                                   std::max(64.f,float(batch.viewportW())-fitted.rect.x-kDiagPad));
    }
    // Backing first (translucent black), then a 1 px white frame drawn as four
    // thin solids — the batch has no line primitive, and four quads are exact.
    batch.pushSolid(fitted.rect, fromRgb8(0, 0, 0, 0.72f));
    const UiColor frame = fromRgb8(200, 200, 200, 0.9f);
    const float x0 = fitted.rect.x, y0 = fitted.rect.y;
    const float x1 = x0 + fitted.rect.w, y1 = y0 + fitted.rect.h;
    batch.pushSolid(UiRect{x0, y0, fitted.rect.w, 1.f}, frame);
    batch.pushSolid(UiRect{x0, y1 - 1.f, fitted.rect.w, 1.f}, frame);
    batch.pushSolid(UiRect{x0, y0, 1.f, fitted.rect.h}, frame);
    batch.pushSolid(UiRect{x1 - 1.f, y0, 1.f, fitted.rect.h}, frame);
    float y = panel.textY;
    for (const std::string& line : lines) {
        if (captions_.atlasTexture() >= 0) captions_.draw(batch,line.c_str(),panel.textX,y,1.f,kHudWhite);
        else pushText(batch, atlas_, line.c_str(), panel.textX, y, kDiagTextScale, kHudWhite);
        y += kDiagLineH;
    }
}

}  // namespace ui
