#pragma once
// HUD-state bridge: fills ui::HudState from plain game values.
//
// WHY this file exists separately from hud_values.h: the game side must stay
// WebGPU-free, but producing a ui::HudState needs its definition
// (ui/hud.h -> sprite.h includes webgpu.h). So hud_values.h is the
// dependency-light contract gameplay implements against, and this header is
// the render-side seam — the only game/ TU that includes ui. Field mapping
// follows remake/src/core/scenes.cpp:818-893 term by term (balloon/LIMIT
// corners, MAIN/CHARGE stocks + RELOAD tag, tier-coloured hold meter,
// HP, hyper bar + READY/active states, contextual stamina, KO sting).
#include "game/hud_values.h"
#include "ui/hud.h"

namespace game {

// Tier enum to the surveyed DX9 hold-meter colours (scenes.cpp:848-851).
inline ui::UiColor holdColorFor(HoldTier tier) {
    switch (tier) {
        case HoldTier::Red:
            return ui::kHudTierRed;
        case HoldTier::Yellow:
            return ui::kHudTierYellow;
        case HoldTier::Idle:
        default:
            return ui::kHudTierIdle;
    }
}

// Pure mapping: one frame's game values in, the HUD state the composer
// drains out. Reads nothing but its argument, so any frame's HUD is a pure
// function of that frame's game state — same property HudComposer relies on.
inline ui::HudState makeHudState(const GameHudValues& v) {
    ui::HudState st;
    st.balloon[0] = v.balloon[0];
    st.balloon[1] = v.balloon[1];
    st.limit = v.limit;
    st.mainWhole = v.mainWhole;
    st.mainFrac = v.mainFrac;
    st.reloading = v.reloading;
    st.chargeWhole = v.chargeWhole;
    st.chargeFrac = v.chargeFrac;
    st.holdVisible = v.holdVisible;
    st.holdFrac = v.holdFrac;
    st.holdColor = holdColorFor(v.holdTier);
    st.hp = v.hp;
    st.hyperName = v.hyperName;
    st.hyperGauge = v.hyperGauge;
    st.hyperActive = v.hyperActive;
    st.hyperReady = v.hyperReady;
    st.hyperSecondsLeft = v.hyperSecondsLeft;
    st.hyperAura = ui::UiColor{v.hyperAura.r, v.hyperAura.g, v.hyperAura.b, 1.f};
    st.staminaVisible = v.staminaVisible;
    st.staminaFrac = v.staminaFrac;
    st.koVisible = v.koVisible;
    return st;
}

// The --hud-test rig as a bridge user: synthetic game values in, the exact
// HudState main.cpp's syntheticHudState() builds today. Lets the parent
// replace the hand-built state with this one-line call without changing any
// capture pixel (see docs/GAME-INTERFACES.md).
inline ui::HudState syntheticHudState() {
    return makeHudState(syntheticHudValues());
}

}  // namespace game
