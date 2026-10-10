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

} // namespace gameplay
