#pragma once
// Fallback diagnostics: a minimal overlay that works when game assets — or
// even the HUD's own font upload — are unavailable.
//
// The bitmap font is embedded, so "fonts unavailable" cannot happen the way it
// does on the DX9 path (D3DXCreateFont failing under Wine without CJK fonts):
// the atlas builds from static data with no OS call. What CAN be missing is
// everything else — textures, scene, HUD state — and this overlay covers
// exactly that: a translucent panel with device/status lines plus the failing
// error string, drawn with solids and atlas glyphs only. No texture slot but
// the renderer's own white fallback and the font atlas is touched.
#include <string>
#include <vector>

#include "ui/hud.h"
#include "ui/sprite.h"

namespace ui {

// Scale for diagnostic lines: 7 px * 2 = 14 px rows, half the HUD size so a
// dozen lines still fit a 540 p frame.
inline constexpr float kDiagTextScale = 2.f;
inline constexpr float kDiagLineH = (float)kLineHeight * kDiagTextScale;   // 16
inline constexpr float kDiagPad = 8.f;

// Panel geometry for `lineCount` diagnostic lines at the top-left.
struct DiagPanel {
    UiRect rect;      // translucent backing, viewport pixels
    float  textX = 0.f, textY = 0.f;
};

// Pure host-side: panel sizing is arithmetic, so tests pin it without a device.
// Width fits the longest line at the diagnostic scale plus padding both sides.
DiagPanel computeDiagPanel(int viewW, int viewH, size_t lineCount, size_t maxChars);

// Pure host-side line builder: adapter/backend, surface state, then the error
// (or frame stats when healthy). The caller owns wording of `extra`; each
// entry is one '\n'-free line.
std::vector<std::string> buildDiagLines(const std::string& adapter, const std::string& backend,
                                       int viewW, int viewH, const std::string& error,
                                       unsigned long long frames, double avgDeltaMs,
                                       const std::string& extra = {});

class FallbackOverlay {
public:
    FallbackOverlay() = default;

    // Same atlas ownership pattern as HudComposer: upload once, cache the id.
    bool uploadFont(SpriteRenderer& batch, std::string& error);
    int  atlasTexture() const { return atlas_; }

    // Draws the panel plus lines. Works with an empty scene and zero uploaded
    // game textures; when even the font upload failed, the panel still draws
    // so a missing-glyphs failure reads as a dark box, not silence.
    void draw(SpriteRenderer& batch, const DiagPanel& panel,
              const std::vector<std::string>& lines);

private:
    int atlas_ = -1;
};

}  // namespace ui
