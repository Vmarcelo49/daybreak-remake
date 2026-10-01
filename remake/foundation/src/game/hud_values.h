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
    std::string hyperName = "FRIENDSHIP";
    float hyperGauge = 0.f;
    bool  hyperActive = false;
    bool  hyperReady = false;       // full gauge, S activates
    float hyperSecondsLeft = 0.f;
    GameRgb hyperAura{1.f, 1.f, 1.f};
    bool  staminaVisible = false;   // dash/guard/airborne only
    float staminaFrac = 0.f;
    bool  koVisible = false;        // elapsed < stingUntil in the DX9 path
};

// The synthetic --hud-test values from src/main.cpp (syntheticHudState),
// expressed as game values. Exists so the deterministic capture rig becomes
// "fill bridge from this struct" instead of hand-building ui state — one
// trivial GameHudValues implementation proving the seam.
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
    return v;
}

}  // namespace game
