#pragma once
// Plain game-side HUD values: the dependency-light half of the HUD bridge.
//
// WHY a second struct next to ui::HudState: HudState speaks renderer (UiColor
// fills, pre-resolved hold colours), while gameplay speaks rules (charge
// tiers from ShotTier, per-mode hyper params from hypermode_params, stamina
// integers — remake/src/gameplay/fighter.h, scenes.cpp:833-887). Game code
// fills this struct from fighter/scene state and never includes a ui header;
// hud_bridge.h maps it onto ui::HudState at the seam. Field layout mirrors
// HudState 1:1 so the mapping is auditable line by line. std only (plus
// <string> for the hyper name): not even glm is needed here.
#include <string>

namespace game {

// Charge-hold tier while C is held (spec §3.1 charge attacks). The DX9 path
// picks the meter colour from the tier (scenes.cpp:847-853); the bridge maps
// this enum onto the surveyed tier colours, so gameplay never names pixels.
enum class HoldTier : unsigned char { Idle, Yellow, Red };

// Plain 0..1 float colour for the hyper aura. The DX9 path passes the mode's
// aura D3DCOLOR straight into the bar (scenes.cpp:873-876); the game resolves
// its mode to RGB here and the bridge copies it across.
struct GameRgb {
    float r = 1.f, g = 1.f, b = 1.f;
};

// Who a fighter is from one view's point of view (issue #13). The gameplay side cannot
// include ui/hud.h, so the enum is mirrored here and hud_bridge.h maps it 1:1.
enum class GameHudRole : unsigned char { Owner = 0, Ally = 1, Enemy = 2 };

// One fighter's per-fighter HUD entry (FUN_00643230 @0x00643230). Screen-space
// because the projection is the camera's business: whoever owns the view-projection
// matrix fills these (game/hud_bridge.h's projectFighterHud does the arithmetic), and
// the HUD layer only draws at the point it is handed.
//
// One entry per ACTIVE PARTICIPANT (issue #13): the roster decides how many exist, and
// `role` says who the fighter is from the view's own point of view.
struct GameFighterHud {
    float ringX = 0.f, ringY = 0.f;   // projected position + 70 world units
    float barX = 0.f, barY = 0.f;     // projected position + 150 units, then -32 HUD units
    int ringPulse = 0;                // fighter+0x30c target-switch countdown
    bool  visible = false;            // in front of the camera
    bool  target = false;             // the fighter the viewer has locked on (ring + com bar)
    GameHudRole role = GameHudRole::Enemy;   // owner / ally / enemy, per view
    bool  targetsViewer = false;      // this fighter has locked the active player
    int   slot = 0;                   // 0..4 -> 1P/2P/3P/4P/com
    int   tagSheet = 0;               // 0 blue tag rows, 1 red
    float hp = 1.f;                   // hud+0x7a4 / 10000
    float hpLag = 1.f;                // hud+0x7a8 / 10000
    int   alertDir = -1;              // -1 none, else 0 top 1 bottom 2 left 3 right
};

// Every value the battle HUD needs, in game units. Fractions are 0..1, hp and
// balloon/limit are percentages — the same units scenes.cpp formats with
// "%.0f%%" and the same bar fractions it passes to m_hud.bar.
struct GameHudValues {
    float balloon[2] = {0.f, 0.f};
    float limit = 100.f;
    int   mainWhole = 0;
    float mainFrac = 0.f;
    bool  reloading = false;        // RELOAD gate tag between volleys
    int   chargeWhole = 0;
    float chargeFrac = 0.f;
    bool  holdVisible = false;      // C held and fighter alive
    float holdFrac = 0.f;
    HoldTier holdTier = HoldTier::Idle;
    float hp = 100.f;               // 0..100
    float hpLag = 100.f;            // hud+0x7a8: the lagging HP the ghost fill draws
    std::string hyperName = "FRIENDSHIP";
    float hyperGauge = 0.f;
    bool  hyperActive = false;
    bool  hyperReady = false;       // full gauge, S activates
    float hyperSecondsLeft = 0.f;
    GameRgb hyperAura{1.f, 1.f, 1.f};
    bool  staminaVisible = false;   // dash/guard/airborne only
    float staminaFrac = 0.f;
    bool  koVisible = false;        // elapsed < stingUntil in the DX9 path
    // The original's clock and the values its clock-driven elements read. The HUD
    // layer draws whatever these say; whoever advances the match advances hudFrame.
    int   hudFrame = 0;             // *param_1, the HUD object's frame counter
    int   commandCell = -1;         // hud+0x310: boxed tactics cell, < 0 hides it
    float commandScale = 0.f;       // hud+0x314: extra scale on that label
    int   balloonPulse[2] = {0, 0};         // hud+0x78e0: change popups
    int   balloonPulseValue[2] = {0, 0};    // hud+0x78e8
    // One entry per selection panel; the roster decides how many are filled (issue #13).
    GameFighterHud fighters[4];     // FUN_00643230's per-fighter entries
};

// The synthetic --hud-test values from src/main.cpp (syntheticHudState),
// expressed as game values. Exists so the deterministic capture rig becomes
// "fill bridge from this struct" instead of hand-building ui state — one
// trivial GameHudValues implementation proving the seam.
//
// The fields the text HUD draws are exactly what they always were, so the
// asset-less fallback frame stays byte-identical; the ones the art HUD added are
// set to the reference print's own state where the print has them (the boxed
// `適当` command cell, the target's com bar and ring, the right corner's +21 popup)
// and to a mid-range value where it does not (the HP lag ghost).
inline GameHudValues syntheticHudValues() {
    GameHudValues v;
    v.balloon[0] = 87.f;
    v.balloon[1] = 42.f;
    v.limit = 100.f;
    v.mainWhole = 5;
    v.mainFrac = 0.6f;
    v.reloading = false;
    v.chargeWhole = 2;
    v.chargeFrac = 0.3f;
    v.holdVisible = true;
    v.holdFrac = 0.5f;
    v.holdTier = HoldTier::Yellow;
    v.hp = 73.f;
    v.hyperName = "OYASHIRO";
    v.hyperGauge = 0.8f;
    v.hyperActive = false;
    v.hyperReady = true;
    v.hyperSecondsLeft = 0.f;
    v.hyperAura = GameRgb{1.f, 1.f, 1.f};
    v.staminaVisible = true;
    v.staminaFrac = 0.4f;
    v.koVisible = false;
    v.hpLag = 90.f;            // the ghost sits above the live fill, as after a hit
    v.hudFrame = 120;          // fixed: the flash/alternation must be deterministic
    v.commandCell = 0;         // P03 cell 0, the boxed 適当 the print shows
    v.commandScale = 0.f;
    v.balloonPulse[0] = 0;
    v.balloonPulse[1] = 40;    // the right corner's "+21 %" popup, mid-flight
    v.balloonPulseValue[0] = 0;
    v.balloonPulseValue[1] = 21;
    // The target, at the screen point battle-hud.webp's ring and com bar were
    // measured on: ring centre (400,162), bar anchor (400,99).
    v.fighters[0].ringX = 400.f;
    v.fighters[0].ringY = 162.f;
    v.fighters[0].barX = 400.f;
    v.fighters[0].barY = 99.f;
    v.fighters[0].ringPulse = 0;
    v.fighters[0].visible = true;
    v.fighters[0].target = true;
    v.fighters[0].slot = 4;      // "com"
    v.fighters[0].tagSheet = 1;  // the red tag rows
    v.fighters[0].hp = 0.8f;
    v.fighters[0].hpLag = 0.95f;
    v.fighters[0].alertDir = 0;  // the pentagon above the bar
    return v;
}

}  // namespace game
