#pragma once
// gameplay/arena_camera.h — the arena match camera: state and behaviour, ported
// from the DX9 reference (remake/src/render/arena_camera.{h,cpp}; RE section 14,
// fcn.006507c0 camera update + fcn.0042cb50 camera collision).
//
// WHY a port and not render::arenaViewProj: the reference camera is STATEFUL, and
// Phase 3's gate is a foundation frame compared against a banked DX9 frame. The
// one-shot path (render/arena_camera.h) computes the same desired eye but starts
// converged and always smooths, so the eye lands elsewhere. This class owns the
// reference's state machine — target pool, orbit nudges, the retained eye, the
// collision snap — and calls render::arenaViewProj for the eye math, so the formula
// keeps exactly one implementation in the tree.
//
// Behaviour, identical to the reference (each point is load-bearing for a trace diff):
//   * the eye starts at (0,0,0) and is NOT seeded from the desired eye: the first
//     update() lands at 10% of the desired eye, which is what the banked DX9 logs show
//     (hud-dash frame 1: eye=(70,50,-38) with a 500-unit desired height);
//   * dt is not used. The reference's blend is 10% per CALL (arena_camera.cpp:123-136),
//     not per second, and the DX9 harness steps the match at a fixed 1/60, so scaling
//     the blend by dt would break the frame-by-frame comparison. render::
//     arenaSmoothEyeDt is the dt-correct path for a variable-delta loop;
//   * a blocked segment SNAPS the eye to hit.dist - 20 in the same call — the
//     reference has no smoothing on the blocked path (arena_camera.cpp:113-121) —
//     while an unblocked one lerps 10%;
//   * no active target means no update at all: eye, up and view keep their last values
//     (arena_camera.cpp:85-89 returns before touching any of them).
//
// Collision: the reference takes a D3DXFRAME* and calls physics::raycast_model on it.
// The ported physics side already owns that query as game::physics::CameraCollision
// (physics/raycast.h), whose queryClamp is the reference's rule verbatim — raycast
// aim -> desiredEye over the full segment and report a hit only when hit.dist is
// shorter than the segment — so this class consumes it instead of re-implementing the
// raycast. A default-constructed CollisionQuery is the reference's nullptr
// collisionFrame, which is what the match scene actually passes today
// (remake/src/core/scenes.cpp:729, "No collision_camera.x is loaded in this scene
// yet") and therefore the parity default: update(dt) always lerps,
// update(dt, {&stageCameraCollision}) clamps.
//
// Conventions (pinned by tests/arena_camera_test.cpp): left-handed, Y-up, depth range
// [0,1] (ZO), column vectors — clip = proj * view * world, which is the composition
// render::arenaViewProj returns and the transform the DX9 device applied through
// D3DTS_VIEW/D3DTS_PROJECTION. proj_matrix() reproduces
// D3DXMatrixPerspectiveFovLH(kFovY, aspect, kNearClip, kFarClip) as
// glm::perspectiveLH_ZO with the same arguments; view_matrix() reproduces
// D3DXMatrixLookAtLH as glm::lookAtLH. The projection leaves Y-up NDC unchanged (no
// Y flip), which is the convention the rest of the renderer relies on.
//
// Not ported from the source because it is never read there: the cached m_proj (only
// ever written by the constructor, proj_matrix() returns a local), and m_lastHitDist /
// m_hitLastFrame plus their only consumer kMaxRaycastDist (write-only bookkeeping).

#include <vector>

#include <glm/glm.hpp>

#include "physics/raycast.h"       // game::physics::CameraCollision
#include "render/arena_camera.h"   // render::ArenaTarget, render::arenaViewProj

namespace gameplay {

// One fighter the camera can lock onto. `position`/`facingYaw` are render::ArenaTarget's
// (world-space Y-up position and the FUN_00420b30 actor yaw), inherited so the eye math
// can hand this straight to render::arenaViewProj and so a caller that already holds an
// ArenaTarget needs no conversion. `alive` is the DX9 CameraTarget field that
// render::ArenaTarget dropped (render/arena_camera.h): cycle_target skips dead
// fighters, which is a lock-on policy, not render math.
struct CameraTarget : render::ArenaTarget {
    bool alive = true;
};

// What update() clamps the eye against. Mirrors the reference's D3DXFRAME* argument:
// nullptr — the default — is the reference's "no collision frame" branch, where the
// eye always lerps. The non-null form is the stage's collision_camera.x query, whose
// own setMesh(nullptr) / empty-mesh state also answers "no hit".
struct CollisionQuery {
    const game::physics::CameraCollision* collision = nullptr;
};

class ArenaCamera {
public:
    // The reference's constructor body (identity view, zero eye/target, +Y up) is the
    // member initializers below; nothing is left to construct.
    ArenaCamera() = default;

    // ---- target management -------------------------------------------------
    // Sets the pool of fighters the camera can target. Pointers are NOT owned —
    // the caller keeps them alive (and refreshes the pointed-to position/facing
    // each frame; this class reads them at update time).
    void set_target_pool(const std::vector<CameraTarget*>& fighters);

    // Sets the active target by index. Does nothing when the index is out of range
    // or the fighter there is dead.
    void set_active_target(int index);

    // Cycles to the next alive fighter, wrapping. Dead fighters are skipped; with
    // none alive the current target is kept. `forward` false cycles backward.
    void cycle_target(bool forward = true);

    int           active_target_index() const { return m_activeIdx; }
    CameraTarget* active_target() const;

    // ---- orbit control -----------------------------------------------------
    // The camera orbits the target about the Y axis, its angle derived from the
    // target's facingYaw (camera behind the fighter) plus this nudge.
    void nudge_orbit(float delta_radians) { m_orbitNudge += delta_radians; }
    void reset_orbit() { m_orbitNudge = 0.0f; }
    // Visual-validation overrides; negative means "use the constant" (so 0 is a
    // legal override, matching the reference's `>= 0.0f` test).
    void set_height_offset(float h) { m_heightOverride = h; }
    void set_distance_offset(float d) { m_distOverride = d; }

    // ---- update ------------------------------------------------------------
    // Advances the camera one call: aim from the active target, then the reference's
    // blocked/unblocked eye rule (see the header banner). `dt` is accepted for call
    // shape only and deliberately unused — the reference blends per call.
    void update(double dt, const CollisionQuery& collision = {});

    // ---- outputs -----------------------------------------------------------
    const glm::mat4& view_matrix() const { return m_view; }
    glm::mat4        proj_matrix(int viewport_w, int viewport_h) const;

    // ---- state -------------------------------------------------------------
    const glm::vec3& eye() const { return m_eye; }
    const glm::vec3& target() const { return m_target; }
    const glm::vec3& up() const { return m_up; }

    // Desired eye for one target: position + height, offset 45° from the facing in
    // the XZ plane, with this camera's orbit nudge and height/distance overrides.
    // Public here (private in the reference) so the device-free parity test can pin
    // the constants and the formula without stepping the eye toward them. Does NOT
    // apply collision.
    glm::vec3 compute_desired_eye(const CameraTarget* t) const;

private:
    float effective_height() const {
        return m_heightOverride >= 0.0f ? m_heightOverride : kHeightOffset;
    }
    float effective_distance() const {
        return m_distOverride >= 0.0f ? m_distOverride : kDistanceOffset;
    }

    // Camera state (the reference's m_view/m_eye/m_target/m_up).
    glm::mat4 m_view{1.0f};
    glm::vec3 m_eye{0.0f};
    glm::vec3 m_target{0.0f};
    glm::vec3 m_up{0.0f, 1.0f, 0.0f};   // Y-up world

    // Target pool.
    std::vector<CameraTarget*> m_pool;
    int                        m_activeIdx = -1;

    // Orbit nudge and the visual-validation overrides.
    float m_orbitNudge = 0.0f;
    float m_heightOverride = -1.0f;   // <0 = kHeightOffset
    float m_distOverride = -1.0f;     // <0 = kDistanceOffset

    // Constants, from the reference (RE section 14.7); the addresses are the
    // originals' data locations.
    static constexpr float kHeightOffset     = 300.0f;      // 0x6a1720
    static constexpr float kDistanceOffset   = 800.0f;      // 0x6a4928
    static constexpr float kBaselineZRotation = 0.7853982f; // π/4 (0x6aac70)
    static constexpr float kFovY             = 0.7853982f;  // π/4 — guess in the source
    static constexpr float kNearClip         = 1.0f;
    static constexpr float kFarClip          = 100000.0f;
    static constexpr float kFollowBlend      = 0.1f;        // per call, not per second
    static constexpr float kCollisionMargin  = 20.0f;       // arena_camera.cpp:115
};

}  // namespace gameplay
