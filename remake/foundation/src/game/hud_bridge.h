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
//
// It is also where the per-fighter HUD's projection lives: the two screen points
// FUN_00643230 draws its ring and com bar at are camera arithmetic, not HUD layout,
// so the caller that owns the view-projection matrix computes them here and the HUD
// layer only ever sees screen pixels. The matrix is taken as a raw column-major
// float[16] — glm's storage order — so this header stays free of even glm.
#include <string>

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

// FUN_00644150 draws the fan's hypermode caption from a fixed row of P01
// (0,384+32*row,128,32) selected by hud+0x318 (0x644859): row 0 OYASHIRO, 1
// FRIENDSHIP, 2 KAKERA — the order FUN_00642c50 writes the per-team captions in. The
// game speaks the mode's name (hypermode_params), so the row is resolved from it;
// an unknown name keeps row 0, which is the OYASHIRO fan the reference frame shows.
inline int hyperRowFor(const std::string& name) {
    if (name == "FRIENDSHIP") return 1;
    if (name == "KAKERA") return 2;
    return 0;
}

// FUN_00643230's projection (FUN_00643230.c:56-58): clip = viewProj * (world, 1), then
// the screen mapping in ui::hudProjectClip. The original divides by a hard 1.0
// because D3DXVec4Transform of a w = 1 point through its affine matrix leaves w = 1;
// dividing by the real w is what a perspective matrix needs and is the same number
// when w == 1. False when the point is at or behind the eye, which is the original's
// `0 < clip.z` gate (FUN_00643230.c:179) — a point there has no screen position.
inline bool projectHudPoint(const float viewProj[16], float wx, float wy, float wz, float& x,
                            float& y) {
    const float cx = viewProj[0] * wx + viewProj[4] * wy + viewProj[8] * wz + viewProj[12];
    const float cy = viewProj[1] * wx + viewProj[5] * wy + viewProj[9] * wz + viewProj[13];
    const float cw = viewProj[3] * wx + viewProj[7] * wy + viewProj[11] * wz + viewProj[15];
    if (!(cw > 0.f)) return false;
    ui::hudProjectClip(cx / cw, cy / cw, x, y);
    return true;
}

// The two anchors of one fighter's HUD: the ring at +70 world units (FUN_00643230.c:52)
// and the com bar at +150 (FUN_00643230.c:173), whose projected y then drops 32 px
// (0x6acf48 = 32.0f, FUN_00643230.c:182). Returns false (and leaves `out.visible`
// false) when the fighter is behind the camera. `HudEntry` is duck-typed on the four
// anchor fields so a caller holding either the game struct (GameFighterHud) or the
// state the composer reads (ui::HudFighterHud) writes straight into it — main.cpp's
// versus/match paths hold the latter and should not have to copy through the bridge.
template <class HudEntry>
inline bool projectFighterHud(const float viewProj[16], float wx, float wy, float wz,
                              HudEntry& out) {
    out.visible = projectHudPoint(viewProj, wx, wy + ui::kHudRingLift, wz, out.ringX, out.ringY);
    float bx = 0.f, by = 0.f;
    if (projectHudPoint(viewProj, wx, wy + ui::kHudBarLift, wz, bx, by)) {
        out.barX = bx;
        out.barY = by - ui::kHudBarDrop;
    }
    return out.visible;
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
    st.hpLag = v.hpLag;
    st.hyperName = v.hyperName;
    st.hyperRow = hyperRowFor(v.hyperName);
    st.hyperGauge = v.hyperGauge;
    st.hyperActive = v.hyperActive;
    st.hyperReady = v.hyperReady;
    st.hyperSecondsLeft = v.hyperSecondsLeft;
    st.hyperAura = ui::UiColor{v.hyperAura.r, v.hyperAura.g, v.hyperAura.b, 1.f};
    st.staminaVisible = v.staminaVisible;
    st.staminaFrac = v.staminaFrac;
    st.koVisible = v.koVisible;
    st.hudFrame = v.hudFrame;
    st.commandCell = v.commandCell;
    st.commandScale = v.commandScale;
    st.balloonPulse[0] = v.balloonPulse[0];
    st.balloonPulse[1] = v.balloonPulse[1];
    st.balloonPulseValue[0] = v.balloonPulseValue[0];
    st.balloonPulseValue[1] = v.balloonPulseValue[1];
    for (int i = 0; i < 2; ++i) {
        st.fighters[i].ringX = v.fighters[i].ringX;
        st.fighters[i].ringY = v.fighters[i].ringY;
        st.fighters[i].barX = v.fighters[i].barX;
        st.fighters[i].barY = v.fighters[i].barY;
        st.fighters[i].ringDeg = v.fighters[i].ringDeg;
        st.fighters[i].visible = v.fighters[i].visible;
        st.fighters[i].target = v.fighters[i].target;
        st.fighters[i].slot = v.fighters[i].slot;
        st.fighters[i].tagSheet = v.fighters[i].tagSheet;
        st.fighters[i].hp = v.fighters[i].hp;
        st.fighters[i].hpLag = v.fighters[i].hpLag;
        st.fighters[i].alertDir = v.fighters[i].alertDir;
    }
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
