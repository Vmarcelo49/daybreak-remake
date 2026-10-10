#pragma once

#include <array>

namespace gameplay {

// The origin families the recovered launch helpers actually use. Every world-style
// body (FUN_00435450) computes its position from the actor's own position plus a
// forward/lateral/height displacement, so the world family is expressed actor-
// relative rather than as absolute XYZ: no measured body passes absolute coordinates.
enum class ShotOriginKind {
    MoveRuleAdapter,
    // FUN_00435000: an item muzzle transformed by a posed prop attachment.
    WeaponAttachment,
    // FUN_00435000 uses its transformed bone when the corresponding prop is unbound.
    BoundBoneFallback,
    // FUN_00435220: the supplied hand/bone matrix and its local point.
    NamedBone,
    // FUN_00435450: actor position plus a heading-relative displacement, resolved
    // independently of the aim direction.
    ActorRelativeOffset,
};

struct ShotOriginSpec {
    ShotOriginKind kind = ShotOriginKind::MoveRuleAdapter;
    int attachmentSlot = 0;
    const char* boneName = nullptr;
    std::array<float, 3> localOffset{};
    // right, forward, height in the actor's heading basis (ActorRelativeOffset).
    std::array<float, 3> actorRightForwardHeight{};
};

enum class ShotAimKind {
    MoveRuleAdapter,
    // Yaw from the fighter's own facing, pitch from the target elevation.
    TargetElevation,
    // FUN_00435450's world yaw follows the legacy basis (90 deg - heading) the
    // original's cosine table indexes, with target-derived elevation.
    ActorHeadingTargetElevation,
    // The pitch a CapturePitch rule stored at an earlier tick. 106 recovered bodies
    // compute the target elevation ONCE (FUN_0042da80 -> FUN_0066b668 ->
    // write_scratch(0x3c)) and read it back for later salvos, so a target that changes
    // height mid-attack must not re-aim salvos that already have their pitch.
    StoredPitch,
    // Literal yaw/pitch in degrees (yaw on the fighter's own basis, pitch absolute).
    // For bodies that pass constant angles rather than deriving them — e.g. a hand
    // request with yaw 0 and pitch 0 that must not track the target.
    FixedAngles,
    // Stored base pitch plus a live range term, on the legacy yaw basis. Measured in
    // shoot_body_2_1_450/460 only: pitch = clamp(int(elevation), +-40) plus
    // clamp(dist*40/5000, 0, 40), scaled by 0.95 when the base is negative.
    ElevationPlusRange,
};

struct ShotAimSpec {
    ShotAimKind kind = ShotAimKind::MoveRuleAdapter;
    // Offset added to the heading before the legacy-basis conversion, in degrees.
    float yawDegrees = 0.f;
    // Offset added to the target elevation before clamping, in degrees.
    float pitchDegrees = 0.f;
    float minimumPitchDegrees = -40.f;
    float maximumPitchDegrees = 40.f;
};

// Rule-table factories. Bodies state their geometry in original units — lateral,
// forward and height coefficients, and a pitch clamp — so the tables read as
// measurements instead of pre-baked transforms. The kinds they pick are the ones the
// bodies actually call: FUN_00435450's world request resolves its position from the
// actor heading, and aims on the legacy yaw basis.
inline constexpr ShotOriginSpec origin_actor_relative(float right, float forward,
                                                      float height) {
    return ShotOriginSpec{ShotOriginKind::ActorRelativeOffset, 0, nullptr, {},
                          {right, forward, height}};
}

// Target-derived elevation, clamped symmetrically to +/- clampDegrees, aimed on the
// legacy yaw basis (90 deg - facing) the world helper uses.
inline constexpr ShotAimSpec aim_target_elevation(float clampDegrees) {
    return ShotAimSpec{ShotAimKind::ActorHeadingTargetElevation, 0.f, 0.f, -clampDegrees,
                       clampDegrees};
}

// The pitch a preceding CapturePitch rule stored, aimed on the legacy yaw basis. Use it
// for every request a body makes after it has latched its pitch.
inline constexpr ShotAimSpec aim_stored_pitch() {
    return ShotAimSpec{ShotAimKind::StoredPitch, 0.f, 0.f, -40.f, 40.f};
}

// Literal yaw/pitch in degrees, no target tracking. Use it for requests whose body
// passes constant angles.
inline constexpr ShotAimSpec aim_fixed_angles(float yawDegrees, float pitchDegrees) {
    return ShotAimSpec{ShotAimKind::FixedAngles, yawDegrees, pitchDegrees, -45.f, 45.f};
}

// Stored base pitch plus a live range term, on the legacy yaw basis. The resolver
// derives both from the live target geometry; see the kind comment for the formula.
inline constexpr ShotAimSpec aim_elevation_plus_range() {
    return ShotAimSpec{ShotAimKind::ElevationPlusRange, 0.f, 0.f, -40.f, 40.f};
}

// A named hand/bone transform with its local point (FUN_00435220). The rule states
// the bone; a rig missing it fails explicitly at request time, never substitutes.
inline constexpr ShotOriginSpec origin_named_bone(const char* boneName) {
    return ShotOriginSpec{ShotOriginKind::NamedBone, 0, boneName, {}, {}};
}

// FUN_00435000's attachment slot, stated explicitly. Slot 0 is Bip01_Prop1 and is what
// the legacy adapter picks; slot 1 is Bip01_Prop2, which several bodies select by ROW
// position (Mion 0's 400 phase-3 and 402, Mion 1's 400 phase-2 and 402). The two slots
// are independent muzzles, so a body firing both must state both rules.
inline constexpr ShotOriginSpec origin_attachment_slot(int slot) {
    return ShotOriginSpec{ShotOriginKind::WeaponAttachment, slot, nullptr, {}, {}};
}

// A body's random spread on one request. Every measured family draws the PITCH jitter
// first and the YAW offset second (Mion 1's 450/460, Mion 2's 450/460 and Rena 2's 400
// all load the pitch draw into the scratch read and the yaw draw into the argument), so
// the draw order is part of the contract — not an implementation detail:
//
//   pitch += (modulo(pitchModulus) + pitchOffset) * pitchScale
//   yaw   += (modulo(yawModulus)   + yawOffset)   * yawScale
//
// A zero modulus means the axis is deterministic and MUST consume no draw, so an unset
// spread cannot shift the stream. The two axes are independently shaped because the
// bodies clamp the pitch before jittering it while the yaw offset is unclamped.
struct ShotSpreadSpec {
    int pitchModulus = 0;
    float pitchOffset = 0.f;
    float pitchScale = 0.f;
    int yawModulus = 0;
    float yawOffset = 0.f;
    float yawScale = 0.f;
};

inline constexpr ShotSpreadSpec spread_pitch_then_yaw(int pitchModulus, float pitchOffset,
                                                      float pitchScale, int yawModulus,
                                                      float yawOffset, float yawScale) {
    return ShotSpreadSpec{pitchModulus, pitchOffset, pitchScale,
                          yawModulus, yawOffset, yawScale};
}

// Mion 1's 450/460 burst: `(rand%100-50)*0.1` on the pitch and `(rand%200-100)*0.1` on
// the yaw, two draws per request over a 15-request loop.
inline constexpr ShotSpreadSpec kSpreadBurstJitter =
    spread_pitch_then_yaw(100, -50.f, .1f, 200, -100.f, .1f);

// Mion 2's 450/460 repeated emission: the same shape with tighter draws
// (`rand%80-40` pitch, `rand%100-50` yaw).
inline constexpr ShotSpreadSpec kSpreadEmissionJitter =
    spread_pitch_then_yaw(80, -40.f, .1f, 100, -50.f, .1f);

// Rena 2's 400 ring: the pitch is `rand%30 + 20` absolute (no clamp base) and the yaw is
// `heading + offset + 90 - rand%180`, so the yaw draw is subtracted through its scale.
inline constexpr ShotSpreadSpec kSpreadRing =
    spread_pitch_then_yaw(30, 20.f, 1.f, 180, 0.f, -1.f);

} // namespace gameplay
