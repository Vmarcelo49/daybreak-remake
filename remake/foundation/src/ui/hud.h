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
#include <cmath>
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

// One fighter's per-fighter HUD (FUN_00643230 @0x00643230, plus the target-bar
// drawer at 0x00643e38). The two anchors are the same world point projected twice:
// the ring uses the fighter's position + 70 world units (FUN_00643230.c:52) and the
// com bar + 150 (:173), and the bar's y then drops another 32 px (0x6acf48). The
// original divides by the transformed w — D3DXVec4Transform leaves w = 1 for its
// affine matrix, so the divide is invisible there — and maps to
// (x*400 + 400, -y*300 + 300) (FUN_00643230.c:56-58). game/hud_bridge.h's
// projectFighterHud() is the port's version of that arithmetic.
struct HudFighterHud {
    float ringX = 0.f, ringY = 0.f;   // projected point of position + 70 units
    float barX = 0.f, barY = 0.f;     // projected point of position + 150 units, -32 px
    float ringDeg = 0.f;              // 9 * hud+0x30c (FUN_00643230 @0x64344d); frame/2 is added
    bool  visible = false;            // in front of the camera (the original's clip.w > 0)
    bool  target = false;             // the locked target: red ring + its com bar
    int   slot = 0;                   // 0..4 -> 1P/2P/3P/4P/com tag cell (0x643a93)
    int   tagSheet = 0;               // 0 blue rows, 1 red rows (0x64408c)
    float hp = 1.f;                   // 0..1, hud+0x7a4 / 10000: the live com-bar fill
    float hpLag = 1.f;                // 0..1, hud+0x7a8 / 10000: the ghost under it
    int   alertDir = -1;              // -1 none, else 0 top 1 bottom 2 left 3 right (0x643722)
};

// The world lifts FUN_00643230 projects its two per-fighter anchors at (FUN_00643230.c:52
// and :173) and the screen drop it applies to the com bar afterwards (0x6acf48 = 32.0f).
// game/hud_bridge.h's projectFighterHud() is the arithmetic that uses them.
inline constexpr float kHudRingLift = 70.f;
inline constexpr float kHudBarLift = 150.f;
inline constexpr float kHudBarDrop = 32.f;

// FUN_00643230's screen mapping on its own (FUN_00643230.c:58-59): a clip-space point
// already divided by w maps to the 800x600 frame. Separate from the matrix multiply so
// the mapping is unit-testable without a camera.
inline void hudProjectClip(float ndcX, float ndcY, float& x, float& y) {
    x = ndcX * 400.f + 400.f;
    y = -ndcY * 300.f + 300.f;
}

// FUN_00644150 @0x644bb4-0x644bf2: a corner balloon's scale is
// (pct*1.5 + 20 + sin(pulse*3 deg)*20) / 100 of its 192 px art — the sine is the
// change pulse's wobble, so a resting balloon (pulse 0) is exactly (pct*1.5 + 20)/100.
inline float hudBalloonScale(float pct, int pulse) {
    const float wobble = std::sin((float)pulse * 3.f * 3.14159265358979323846f / 180.f) * 20.f;
    return (pct * 1.5f + 20.f + wobble) / 100.f;
}

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
    int   hyperRow = 0;              // the caption row (0 OYASHIRO, 1 FRIENDSHIP, 2 KAKERA)
    float   hyperGauge = 0.f;
    bool    hyperActive = false;
    bool    hyperReady = false;      // full gauge, S activates
    float   hyperSecondsLeft = 0.f;
    UiColor hyperAura = kHudWhite;   // per-mode aura, fills the bar while active
    bool  staminaVisible = false;    // contextual: dash/guard/airborne only
    float staminaFrac = 0.f;
    bool  koVisible = false;         // elapsed < stingUntil in the DX9 path
    // The original's frame counter (`*param_1`, the HUD object's first field) and the
    // values its clock-driven elements read. The composer itself stays clock-free —
    // it draws whatever these say — so the seam is explicit: the caller advances
    // hudFrame once per HUD frame and owns the HP lag ramp.
    int   hudFrame = 0;
    float hpLag = 100.f;             // hud+0x7a8: the ghost fill's lagging percentage
    int   commandCell = -1;          // hud+0x310: boxed tactics cell; < 0 hides it
    float commandScale = 0.f;        // hud+0x314: extra scale, 0 draws at 1.0
    // hud+0x78e0 / hud+0x78e8: a balloon corner's change popup. FUN_006431d0
    // @0x6431d0 arms a 60-frame countdown and the value to show when a corner's value
    // changes, FUN_006430f0 @0x6430f0 decrements it; the small green font draws it at
    // (110, 30 + pulse/2) while it runs (0x644d5b). 0 means "no popup".
    int   balloonPulse[2] = {0, 0};
    int   balloonPulseValue[2] = {0, 0};
    HudFighterHud fighters[2];       // FUN_00643230's per-fighter entries
};

// Every rect/position compose() needs, derived from the live viewport.
struct HudRects {    UiRect balloonL, limitL;    // text origins (w/h unused, kept for uniformity)
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
    // The original's composition, in FUN_00644150's own draw order: HP frame + ghost
    // + live fill, the fan gauge (frame, clipped gradient, MAX, caption), STAMINA,
    // the boxed command label, MAIN frame + count + fill, CHARGE frame + count +
    // fills, then the two balloon corners. Elements whose atlas or state the port
    // does not have are simply not drawn here; what is deliberately left out and why
    // is recorded in the track's report, not silently mixed in.
    void composeBattle(SpriteRenderer& batch, const HudState& st);
    // FUN_00643230 + the target-bar drawer at 0x00643e38: the targeting ring, the
    // target's com bar (frame, lagging fill, live fill, 1P/2P/3P/com tag) and the
    // P06 off-screen alert marker, all hung off one projected point per fighter.
    void composeFighters(SpriteRenderer& batch, const HudState& st);
    // One-shot resolve + upload of every HUD sheet. False (and a single stderr line)
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
