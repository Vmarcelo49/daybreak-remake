#pragma once
// FUN_0063b470 / FUN_0063b4d0 test spheres/capsules against two posed
// victim anchors (Head origin, Spine local -50 on X; FUN_00420880).
// NN.dat current records supply geometry and combat values. melee_rules.h
// keeps only the anatomical radius and the legacy/custom-character defaults;
// the active data path does not use a fabricated startup/recovery window.

namespace gameplay {

struct MeleeRules {
    // ---- RECOVERED (FUN_0063b470) ----
    // The victim's own body radius: the literal 30.0 the original passes to the sphere
    // test (0x41f00000 in FUN_00637950:96). Every hit is `dist < bodyRadius + radius`.
    float bodyRadius = 30.0f;
    // Victim anchors as fractions of MovementCollision::kFighterHeight. The original
    // takes these from the Head and Spine bones (FUN_0063dad0:238-243, spine at -50.0);
    // fractions stand in for the rig, and are the reason a swing cannot reach legs.
    float headHeightFrac  = 1.0f;
    float chestHeightFrac = 0.42f;

    // The recovered sphere predicate: hit when the attack sphere (victim body radius +
    // `radius`) overlaps EITHER victim anchor sphere. A miss is "both anchors out", so
    // the argument is the NEARER anchor's squared distance. Live: Fighter::try_melee_hit
    // calls this, so the shape below and the shape the simulation applies are one code
    // path rather than two descriptions of it.
    bool sphere_hits(float nearestAnchorDistSq, float radius) const {
        const float combined = bodyRadius + radius;
        return nearestAnchorDistSq < combined * combined;
    }
};

// A swing's startup/active/recovery split, in ticks of the fixed simulation. The
// historical 30-frame attack is 5 + 8 + 17, so no timing drifts; a bound move table
// overwrites the three fields per swing.
struct MeleeWindow {
    int startupTicks  = 5;
    int activeTicks   = 8;
    int recoveryTicks = 17;

    int total_ticks() const { return startupTicks + activeTicks + recoveryTicks; }
    bool is_startup(int elapsed) const { return elapsed < startupTicks; }
    bool is_active(int elapsed) const {
        return elapsed >= startupTicks && elapsed < startupTicks + activeTicks;
    }
    bool is_recovery(int elapsed) const { return elapsed >= startupTicks + activeTicks; }
};

// The legacy swing's radius: stands in for weapon+0x24, which a legacy melee move has
// no record for. There is only ONE of it because the recovered test has no separate
// aerial or ground radius - what differs between a grounded and an aerial swing in the
// original is the MOVE (its id, animation and script, the 300/310/350/360 families
// FUN_0043ded0 selects), and each still resolves through this same sphere.
inline constexpr float kLegacyRadius = 130.0f;

// The legacy swing's window, derived from the defaults above.
inline constexpr MeleeWindow kLegacyWindow{};

}  // namespace gameplay
