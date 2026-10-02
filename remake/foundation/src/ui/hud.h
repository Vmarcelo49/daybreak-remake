#pragma once
// Battle HUD composition: bars, meters, labels and layout rules.
//
// Mirrors the DX9 battle HUD assembled in remake/src/core/scenes.cpp (itself
// laid out from docs/reference/battle-hud.webp): balloon % + LIMIT in the top
// corners, MAIN/CHARGE stocks plus HP bottom-right, the hypermode gauge
// bottom-left, a contextual stamina bar, and the centred "KO!" sting. Colours
// and anchors are transcribed from those call sites — see docs/UI-DESIGN.md
// for the mapping — so a future wiring produces the same arrangement.
//
// Labels are drawn with the reference's own text metrics when the pinned font chain is
// present (ui/text.h's loadFontChain): the DX9 HUD builds an Arial Bold 22 px cell with
// D3DXCreateFontA and lays it out through GetCharWidth32A, and under the Wine stack
// that banked the frames "Arial" resolves to Liberation Sans Bold. With no font file the
// bitmap atlas draws them instead, byte for byte as before — a fetch failure must not
// change a frame, and the currency of this HUD is frame parity.
//
// Split of duties: HudState is plain data the game fills per frame (no clock,
// no device); computeHudLayout derives every rect from the live viewport size
// (pure host-side, unit-tested); HudComposer turns the two into sprite/text
// quads in the caller's batch. Variable-delta fit falls out of that split:
// the caller rebuilds state and re-composes every frame, like the DX9 path
// which re-issues text/bar calls between BeginScene and EndScene.
#include <string>

#include "ui/font.h"
#include "ui/sprite.h"
#include "ui/text.h"

namespace ui {

// Text scale for HUD labels on the bitmap fallback. The DX9 HUD font is 22 px high; the
// 7 px bitmap at scale 3 is 21 px, the closest integer scale, keeping measurement exact.
// The TrueType path draws at scale 1: ui/text.h's chain is loaded at the reference's own
// design size, so its layout is already in viewport pixels.
inline constexpr float kHudTextScale = 3.f;

// Name under third_party/fonts/ of one link in the HUD's font chain.
struct HudFontFiles {
    const char* latin = "LiberationSans-Bold.ttf";
    const char* cjk = "NotoSansCJKjp-Regular.otf";
};

// Surveyed DX9 HUD colours (D3DCOLOR_XRGB values from scenes.cpp).
inline const UiColor kHudWhite = fromRgb8(255, 255, 255);
inline const UiColor kHudLimitLeft = fromRgb8(160, 200, 255);
inline const UiColor kHudLimitRight = fromRgb8(255, 160, 160);
inline const UiColor kHudMainFill = fromRgb8(90, 140, 255);
inline const UiColor kHudChargeFill = fromRgb8(90, 255, 150);
inline const UiColor kHudHpFill = fromRgb8(255, 220, 60);
inline const UiColor kHudBarBack = fromRgb8(20, 20, 30);
inline const UiColor kHudHyperIdleFill = fromRgb8(170, 170, 170);
inline const UiColor kHudHyperReadyText = fromRgb8(255, 255, 120);
inline const UiColor kHudStaminaFill = fromRgb8(255, 255, 255);
inline const UiColor kHudKoText = fromRgb8(255, 60, 60);
// scenes.cpp:829 draws a bare yellow "0" at (4, 4) with no state behind it.
inline const UiColor kHudMarkerText = fromRgb8(255, 255, 0);
// Charge-hold tier colours (§3.1 charge attacks): red/yellow tiers, grey below.
inline const UiColor kHudTierRed = fromRgb8(255, 70, 50);
inline const UiColor kHudTierYellow = fromRgb8(255, 230, 80);
inline const UiColor kHudTierIdle = fromRgb8(120, 120, 120);

// Per-frame game state feeding the HUD. Fractions are 0..1 (clamped at draw).
struct HudState {
    float balloon[2] = {0.f, 0.f};   // corner percentages vs the LIMIT below
    float limit = 100.f;             // shared LIMIT both corners compare against
    int   mainWhole = 0;             // whole MAIN stock left (P1)
    float mainFrac = 0.f;            // MAIN recharge readout (the fill IS the data)
    bool  reloading = false;         // RELOAD gate tag between volleys
    int   chargeWhole = 0;
    float chargeFrac = 0.f;
    bool  holdVisible = false;       // C held: the tier-coloured hold meter
    float holdFrac = 0.f;
    UiColor holdColor = kHudTierIdle;
    float hp = 100.f;                // 0..100
    std::string hyperName = "FRIENDSHIP";
    float   hyperGauge = 0.f;
    bool    hyperActive = false;
    bool    hyperReady = false;      // full gauge, S activates
    float   hyperSecondsLeft = 0.f;
    UiColor hyperAura = kHudWhite;   // per-mode aura, fills the bar while active
    bool  staminaVisible = false;    // contextual: dash/guard/airborne only
    float staminaFrac = 0.f;
    bool  koVisible = false;         // elapsed < stingUntil in the DX9 path
};

// Every rect/position compose() needs, derived from the live viewport.
struct HudRects {
    UiRect balloonL, limitL;    // text origins (w/h unused, kept for uniformity)
    UiRect balloonR, limitR;
    UiRect mainText, mainBar;
    UiRect chargeText, chargeBar;
    UiRect holdBar;
    UiRect hpText, hpBar;
    UiRect hyperText, hyperBar;
    UiRect markerText;          // the unlabelled corner "0", scenes.cpp:829
    UiRect staminaText, staminaBar;
    float  koCenterX = 0.f;
    float  koY = 0.f;
};

// Anchors reproduce scenes.cpp exactly at any size: corners pinned to the
// viewport edges with the same pixel margins the DX9 path uses at 800x600, so
// resizing moves HUD with the frame instead of stranding it.
HudRects computeHudLayout(int viewW, int viewH);

// Pushes one laid-out string into the batch through the font atlas.
void pushText(SpriteRenderer& batch, int atlasTexture, const char* text, float x, float y,
              float scale, UiColor color);
void pushTextCentered(SpriteRenderer& batch, int atlasTexture, const char* text, float centerX,
                      float y, float scale, UiColor color);

class HudComposer {
public:
    HudComposer() = default;

    // Uploads the atlas the labels will be drawn from: the fetched font chain's if it
    // loads, the bitmap atlas otherwise. Idempotent. Bars compose without either when
    // the upload fails — text is skipped, never fatal — which is also the asset-less
    // fallback behaviour.
    bool uploadFont(SpriteRenderer& batch, std::string& error);
    int  atlasTexture() const { return atlas_; }

    // Turns state + layout into batch quads: bars as back+fill solids, labels
    // as atlas quads. Reads nothing but its arguments, so any frame's HUD is a
    // pure function of that frame's game state.
    void compose(SpriteRenderer& batch, const HudState& st, const HudRects& layout);

private:
    void bar(SpriteRenderer& batch, const UiRect& r, float frac, UiColor fill);
    // One label through whichever text path is live. See the header comment: the two
    // produce the same arrangement from different metrics, and the bitmap one is what
    // the HUD drew before the TrueType path existed.
    void drawText(SpriteRenderer& batch, const char* text, float x, float y, UiColor color);
    void drawTextCentered(SpriteRenderer& batch, const char* text, float centerX, float y,
                          UiColor color);
    // Uploads the chain's glyph atlas, growing in place. False leaves the previous
    // upload alone and stops label drawing rather than sampling stale UVs.
    bool refreshTextAtlas(SpriteRenderer& batch, std::string& error);

    int  atlas_ = -1;             // bitmap fallback; -1 when the chain is live
    TextLayer text_;              // the reference's metrics, empty without a font
    int       textAtlas_ = -1;
    bool      textAtlasOk_ = true;
    uint64_t  textAtlasRevision_ = 0;
};

}  // namespace ui
