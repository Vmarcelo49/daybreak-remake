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
// Split of duties: HudState is plain data the game fills per frame (no clock,
// no device); computeHudLayout derives every rect from the live viewport size
// (pure host-side, unit-tested); HudComposer turns the two into sprite/text
// quads in the caller's batch. Variable-delta fit falls out of that split:
// the caller rebuilds state and re-composes every frame, like the DX9 path
// which re-issues text/bar calls between BeginScene and EndScene.
#include <string>

#include "ui/font.h"
#include "ui/sprite.h"

namespace ui {

// Text scale for HUD labels. The DX9 HUD font is 22 px high; the 7 px bitmap
// at scale 3 is 21 px, the closest integer scale, keeping measurement exact.
inline constexpr float kHudTextScale = 3.f;

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

    // Uploads the bitmap atlas once (cached); idempotent. Bars compose without
    // it when upload fails — text is skipped, never fatal — which is also the
    // asset-less fallback behaviour.
    bool uploadFont(SpriteRenderer& batch, std::string& error);
    int  atlasTexture() const { return atlas_; }

    // Turns state + layout into batch quads: bars as back+fill solids, labels
    // as atlas quads. Reads nothing but its arguments, so any frame's HUD is a
    // pure function of that frame's game state.
    void compose(SpriteRenderer& batch, const HudState& st, const HudRects& layout);

private:
    void bar(SpriteRenderer& batch, const UiRect& r, float frac, UiColor fill);

    int atlas_ = -1;
};

}  // namespace ui
