#pragma once
// HUD value computation: live gameplay state -> game::GameHudValues, the
// WebGPU-free contract the HUD composer drains (src/game/hud_values.h; mapped
// onto ui::HudState by game/hud_bridge.h). Reproduces the display rules of
// Scene_Gameplay::render term by term (remake/src/core/scenes.cpp:818-893):
// balloon % + LIMIT in both top corners, the bottom-right P1 resource block
// (MAIN/CHARGE stocks + RELOAD tag, tier-coloured hold meter only while C is
// held and the fighter is alive, HP), the bottom-left hypermode label/bar, the
// contextual stamina pair, and the KO sting flag.
//
// Which side goes where, pinned from the reference: the balloon corners are the
// only two-side readout (side 0 left, side 1 right, scenes.cpp:825-828); every
// other field comes from fighters[0] (scenes.cpp:833-887), so HudFillInput
// carries one fighter — side 1's hp, stocks, hyper and stamina have no HUD
// destination in the DX9 layout.
//
// fillHudValues is inline here rather than in hud_fill.cpp so a host test can
// include this header without hud_bridge.h's ui/ -> webgpu.h chain; hud_fill.cpp
// is the ui seam and defines hudStateFor().
#include <string>

#include "game/hud_values.h"
#include "gameplay/match_economy.h"

// ui::HudState (hud_bridge.h) stays incomplete on purpose: declaring the return
// type must not drag webgpu.h into this header. A caller of hudStateFor includes
// game/hud_bridge.h, which completes it.
namespace ui { struct HudState; }

namespace gameplay {

// One frame of P1's HUD-side state, sampled by the caller from the live fighter
// and input (Fighter in remake/src/gameplay/fighter.h). Values are copied, not
// linked: plain data in the units GameHudValues speaks.
struct HudFighterValues {
    int   hp = 100;                     // Fighter::hp(), 0..100
    bool  alive = true;                 // Fighter::is_alive()
    int   mainWhole = 0;                // Fighter::main_whole()
    float mainFrac = 0.f;               // Fighter::main_frac()
    bool  reloadOk = true;              // Fighter::reload_ok()
    int   chargeWhole = 0;              // Fighter::charge_whole()
    float chargeFrac = 0.f;             // Fighter::charge_frac()
    bool  shootHeld = false;            // input->player(0).down[input::Action::Shoot]
    float chargeHoldFrac = 0.f;         // Fighter::charge_hold_frac()
    // ShotTier -> HoldTier, resolved caller-side: ShotTier lives in
    // remake/src/gameplay/projectile.h (D3D-typed), which this tree cannot
    // include. Red -> Red, Yellow -> Yellow, anything else -> Idle
    // (scenes.cpp:847-851).
    game::HoldTier chargeTier = game::HoldTier::Idle;
    std::string hyperName = "FRIENDSHIP";    // hypermode_params(...).name
    float hyperGauge = 0.f;                  // Fighter::hyper_gauge()
    bool  hyperActive = false;               // Fighter::hyper_active()
    bool  hyperReady = false;                // Fighter::hyper_ready()
    float hyperSecondsLeft = 0.f;            // Fighter::hyper_seconds_left()
    game::GameRgb hyperAura{1.f, 1.f, 1.f};  // hypermode_params(...).aura, rgb8/255
    int   stamina = 100;                     // Fighter::stamina()
    // Fighter::state() in {Run, Guard, Jump} (scenes.cpp:879-882): the state enum
    // does not cross into this tree, so the caller resolves the contextual gate.
    bool  staminaVisible = false;
};

struct HudFillInput {
    HudFighterValues p1;  // fighters[0]
};

// One frame's game values: the economy (balloon / LIMIT / KO sting) plus P1's
// resources. Pure — reads nothing but its arguments and formats nothing, so the
// composer's own "%.0f%%" / "%.0fs" (ui/hud.cpp:77-104) round exactly as the
// reference's printf did on the same floats. Pass raw values through; no
// pre-rounding, or the text would round twice.
inline game::GameHudValues fillHudValues(const MatchEconomy& eco, const HudFillInput& in) {
    const HudFighterValues& f = in.p1;
    game::GameHudValues v;
    // The animated value the original's own % readout formats (FUN_006430f0 eases
    // hud+0x78f0 toward the credited value). The port keeps the RAW value here: the
    // banked DX9 captures and tests/compare_match_traces.py were taken against it, and
    // balloonDisplay() is exposed for a caller that wants the inflation animation.
    v.balloon[0] = eco.balloon(0);
    v.balloon[1] = eco.balloon(1);
    v.limit = eco.limit();
    // The "+N%" popup: hud+0x78e0 is the 60-frame window FUN_006431d0 arms and
    // hud+0x78e8 the signed amount it shows (scenes.cpp carried both as balloonPulse).
    // Both sides are live now that the economy credits them per side.
    for (int i = 0; i < kSideCount; ++i) {
        v.balloonPulse[i] = eco.balloonDeltaTicks(i);
        v.balloonPulseValue[i] = eco.balloonDelta(i);
    }
    v.mainWhole = f.mainWhole;
    v.mainFrac = f.mainFrac;
    v.reloading = !f.reloadOk;               // scenes.cpp:834 (reloadTag)
    v.chargeWhole = f.chargeWhole;
    v.chargeFrac = f.chargeFrac;
    v.holdVisible = f.shootHeld && f.alive;  // scenes.cpp:845-846
    v.holdFrac = f.chargeHoldFrac;
    v.holdTier = f.chargeTier;
    v.hp = static_cast<float>(f.hp);         // scenes.cpp:857 divides by 100
    v.hyperName = f.hyperName;
    v.hyperGauge = f.hyperGauge;
    v.hyperActive = f.hyperActive;
    v.hyperReady = f.hyperReady;
    v.hyperSecondsLeft = f.hyperSecondsLeft;
    v.hyperAura = f.hyperAura;
    v.staminaVisible = f.staminaVisible;                             // scenes.cpp:880-882
    v.staminaFrac = static_cast<float>(f.stamina) / 100.f;           // scenes.cpp:885
    v.koVisible = eco.koStingActive();                               // scenes.cpp:889
    return v;
}

// The full chain: fillHudValues + game::makeHudState (hud_bridge.h — hud_fill.cpp's
// only reason to reach ui/ -> webgpu.h). Declared here, defined there; a caller
// needs hud_bridge.h for the complete ui::HudState.
ui::HudState hudStateFor(const MatchEconomy& eco, const HudFillInput& in);

}  // namespace gameplay
