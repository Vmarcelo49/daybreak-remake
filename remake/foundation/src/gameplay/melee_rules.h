#pragma once
// gameplay/melee_rules.h — melee reach, windows and hit accounting.
//
// WHY a separate file: melee is the one combat system whose numbers could NOT be
// recovered, and that needs to be visible in one place rather than smeared through
// fighter.cpp as "tuned" constants. Everything here is an EXPLICIT PORT RULE unless a
// line cites otherwise.
//
// ---------------------------------------------------------------------------
// WHAT WAS RECOVERED, and it changed the shape of the test
// ---------------------------------------------------------------------------
// The melee hitbox is NOT a cone and NOT a height band. FUN_00637950 (0x637950) is the
// hit resolver for bullets AND players alike - it never branches on attacker type, it
// just reads the weapon/phase record at *(entity+0x10). It picks between two tests on
// weapon+0x08:
//
//   weapon+0x08 == 0  ->  FUN_0063b470 (0x63b470): a hard 3D SPHERE test.
//                        `dist² < (30.0 + radius)²`, where 30.0 is the literal 0x41f00000
//                        passed as the body's radius and `radius` is weapon+0x24.
//   weapon+0x08 != 0  ->  FUN_0063b4d0 (0x63b4d0): point-to-SEGMENT distance against
//                        (30.0 + radius)², i.e. a CAPSULE swept between two anchors.
//
// There is no angle term in either. So an earlier draft of this file used a 60-degree
// swing cone, which was invented; it is gone, and melee_rules.h below uses the sphere.
//
// The victim's extent is the real vertical limit, and it is ANATOMICAL rather than
// numeric: FUN_0063dad0 (0x63dad0):238-243 builds exactly two victim anchors, from the
// Bip01_Head and Bip01_Spine bones (the spine one offset -50.0). So a fighter is a head
// sphere and a chest sphere and nothing else - which is why a low sweep cannot reach
// legs, and why a fighter far above the attacker is unreachable at all. That is the
// shape this file reproduces.
//
// A directional filter DOES exist in the original - weapon+0x2C is an 8-way facing mask
// filtered at FUN_00637950:383-385 - but its bit order is unverified and it selects which
// INBOUND faces are hittable rather than shaping the volume. It is deliberately not
// implemented here rather than guessed.
//
// ---------------------------------------------------------------------------
// WHAT WAS NOT RECOVERED
// ---------------------------------------------------------------------------
// Per-character melee radius, damage and phase durations are not in data/<char>/NN.dat at
// all: the 0x28-0x2D group every character ships parses with an entirely zero combat
// block. They are produced by a per-character handler-class virtual at vtable slot 0x20
// (called from FUN_00421410.c:15, implemented across ~46 classes). So the VALUES here are
// port rules; the SHAPE above is recovered.
//
// What IS recovered about melee input, and it justifies removing the second key: the
// corpus has exactly one attack bit - `weapon+0x28 & 0x100`, used 1378 times - and no
// heavy/strong bit anywhere. AttackB therefore had no original justification and is gone
// from the remake; the swing is chosen by the fighter's situation at the press.
//
// PORT RULES below are chosen to be defensible rather than arbitrary:
//   * The attack sphere's radius stands in for `weapon+0x24`, which melee has no record
//     for. It keeps the recovered `30 + radius` form, so the moment a weapon radius IS
//     recovered only this one number changes.
//   * The body radius is the recovered literal 30.0, not a new constant.
//   * The two victim anchors are placed as fractions of the collision body height (145,
//     physics/raycast.h, measured in #7) rather than as fresh magic numbers.
//   * Startup/active/recovery split the existing 30-frame attack into the same 5-frame
//     startup the tree already used, a short active window, and a recovery tail during
//     which the fighter cannot act. The totals are unchanged, so no timing drifts.

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

    // ---- PORT RULE ----
    // Stands in for weapon+0x24, which a melee move has no record for. There is only
    // ONE of these: the recovered test has no separate aerial or ground radius. What
    // differs between a grounded and an aerial swing in the original is the MOVE (its
    // id, animation and script), not the hitbox shape - the arena moves 300/310/350/360
    // and similar families are selected by guards in FUN_0043ded0, and each still
    // resolves through this same sphere.
    float radius = 130.0f;

    // ---- PORT RULE: windows, in ticks of the fixed simulation ----
    int startupTicks  = 5;
    int activeTicks   = 8;
    int recoveryTicks = 17;              // 5 + 8 + 17 == the historical 30

    int total_ticks() const { return startupTicks + activeTicks + recoveryTicks; }

    bool is_startup(int elapsed) const { return elapsed < startupTicks; }
    bool is_active(int elapsed) const {
        return elapsed >= startupTicks && elapsed < startupTicks + activeTicks;
    }
    bool is_recovery(int elapsed) const { return elapsed >= startupTicks + activeTicks; }

    // The recovered sphere predicate: hit when the attack sphere (victim body radius +
    // weapon radius) overlaps EITHER victim anchor sphere.
    bool sphere_hits(float distSqToAnchor) const {
        const float combined = bodyRadius + radius;
        return distSqToAnchor < combined * combined;
    }
};

}  // namespace gameplay