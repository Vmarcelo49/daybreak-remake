#pragma once
// Battle HUD composition: bars, meters, labels and layout rules.
//
// Two compositions share this class. The **art HUD** is the original's own: sprite
// sub-rects from data/object/P00..P02.cnv drawn at the layout constants in
// .rdata 0x6a4c90..0x6a4cd8 by FUN_00644150 @0x00644150 — the bar frames, the HP
// ramp, the MAIN/CHARGE fills and counts, and the OYASHIRO fan gauge. The **text
// HUD** is the DX9 remake's Arial labels + flat bars (remake/src/core/scenes.cpp),
// which is what this file drew before the atlases were wired; it stays as the
// fallback whenever an atlas is missing, and it is the only path for a build with
// no game data. Which one runs is decided per frame in compose().
//
// The split of duties is unchanged: HudState is plain data the game fills per
// frame (no clock, no device), computeHudLayout derives the DX9 text layout from
// the live viewport, and HudComposer turns the two into quads in the caller's
// batch. The art path uses fixed 800x600-space anchors, not computeHudLayout:
// single-player HUD coordinates are absolute screen pixels (scale 1.0, viewport
// origin (0,0) — FUN_0063a130 @0x0063a130 sets 1.0 when DAT_006cfba0 == 1, the
// 1P case, and FUN_006396f0 @0x006396f0's SetRect is 0,0,800,600).
//
// The text path's labels still come from the reference's own metrics when the
// pinned font chain is present (ui/text.h's loadFontChain): the DX9 HUD builds an
// Arial Bold 22 px cell with D3DXCreateFontA and lays it out through
// GetCharWidth32A, and under the Wine stack that banked the frames "Arial"
// resolves to Liberation Sans Bold. With no font file the bitmap atlas draws them
// instead, byte for byte as before — a fetch failure must not change a frame.
#include <string>

#include "ui/font.h"
#include "ui/hud_atlas.h"
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
// The art composition draws from these fields too: hp, mainWhole/mainFrac,
// chargeWhole/chargeFrac, the hold tier, and the hyper gauge/ready/active triple.
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

    // Turns state + layout into batch quads. Draws the original's art HUD when its
    // atlases are available; otherwise the DX9 text/bars HUD below, byte for byte.
    // Reads nothing but its arguments plus the one-shot atlas load, so any frame's
    // HUD is a pure function of that frame's game state.
    void compose(SpriteRenderer& batch, const HudState& st, const HudRects& layout);

private:
    void bar(SpriteRenderer& batch, const UiRect& r, float frac, UiColor fill);
    // The original's composition, in FUN_00644150's own draw order: HP frame + fill,
    // the fan gauge (frame, clipped gradient, MAX), MAIN frame + count + fill,
    // CHARGE frame + count + fills. Elements whose atlas or state the port does not
    // have yet — the balloon %/LIMIT readouts, the com bar and targeting brackets,
    // STAMINA, the boxed tactics label, the round stings — are simply not drawn here;
    // they land in the spec's priority order (BATTLE-HUD-SPEC.md §5 items 4-9).
    void composeBattle(SpriteRenderer& batch, const HudState& st);
    // One-shot resolve + upload of P00/P01/P02. False (and a single stderr line)
    // leaves the text HUD in place, which is the documented asset-less behaviour.
    bool ensureBattleAtlas(SpriteRenderer& batch);
    // One label through whichever text path is live. See the header comment: the two
    // produce the same arrangement from different metrics, and the bitmap one is what
    // the HUD drew before the TrueType path existed.
    void drawText(SpriteRenderer& batch, const char* text, float x, float y, UiColor color);
    void drawTextCentered(SpriteRenderer& batch, const char* text, float centerX, float y,
                          UiColor color);
    // Uploads the chain's glyph atlas, growing in place. False leaves the previous
    // upload alone and stops label drawing rather than sampling stale UVs.
    bool refreshTextAtlas(SpriteRenderer& batch, std::string& error);

    HudAtlas battleAtlas_;
    bool     battleTried_ = false;   // one load attempt, never one per frame
    int  atlas_ = -1;             // bitmap fallback; -1 when the chain is live
    TextLayer text_;              // the reference's metrics, empty without a font
    int       textAtlas_ = -1;
    bool      textAtlasOk_ = true;
    uint64_t  textAtlasRevision_ = 0;
};

}  // namespace ui
