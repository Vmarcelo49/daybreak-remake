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
// Framing (2026-10-03): the *behaviour* above is the remake's and stays, but the
// *framing* is the original's, because the visual target is the original's screens
// (foundation/docs/FULL-REPLACEMENT-PLAN.md §6a) and the remake's camera is not it.
// The two are separate: ArenaCameraPreset carries the framing numbers, the class
// carries the ported rules, and a preset swap changes only where the eye lands.
// See ArenaCameraPreset::original() for how the numbers were measured.
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
// D3DXMatrixPerspectiveFovLH(preset.fovY, aspect, preset.nearClip, preset.farClip) as
// glm::perspectiveLH_ZO with the same arguments; view_matrix() reproduces
// D3DXMatrixLookAtLH as glm::lookAtLH. The projection leaves Y-up NDC unchanged (no
// Y flip), which is the convention the rest of the renderer relies on.
//
// Not ported from the source because it is never read there: the cached m_proj (only
// ever written by the constructor, proj_matrix() returns a local), and m_lastHitDist /
// m_hitLastFrame plus their only consumer kMaxRaycastDist (write-only bookkeeping).

#include <vector>
#include "assets/xmodel.h"

#include <glm/glm.hpp>

#include "physics/raycast.h"       // game::physics::CameraCollision
#include "render/arena_camera.h"   // render::ArenaTarget, render::arenaViewProj

namespace gameplay {

// The camera's framing: where the eye sits relative to the locked fighter and what it
// looks at. Every field is a number the *look* of a frame depends on, so a preset is
// the unit of A/B here — the behaviour in ArenaCamera is preset-independent.
//
// The eye is  fighter.position + (-sin(angle), 0, -cos(angle)) * distance + (0, height, 0),
// the aim is  fighter.position + (0, aimHeight, 0),
// with angle = facingYaw - baselineOrbit + orbitNudge.
struct ArenaCameraPreset {
    float height        = 211.f;         // eye height above the fighter's origin (feet)
    float distance      = 289.f;         // horizontal eye distance from the fighter
    float aimHeight     = 138.f;         // the aim is the position raised this much
    float baselineOrbit = 0.f;           // 0 = directly behind the facing
    float fovY          = 0.7853982f;    // vertical FOV, radians
    float nearClip      = 50.f;
    float farClip       = 150000.f;

    // The original game's arena camera: THE match camera.
    //
    // Measured from the original's own screens (remake/docs/reference/*.webp, the
    // visual specification since §6a), not from the remake. Four pixel measurements on
    // battle-hud.webp — player head top 287 / sole 599, opponent head top 143 / sole
    // 194 in a 606-row frame — over-determine the geometry. Four unknowns (distance,
    // height, aim height, the opponent's distance) fall out of the four rows exactly,
    // for the FOV below, at distance 288.9, height 210.9, aimHeight 138.3 and an
    // opponent 2141 units from the eye; the values here are those rounded to whole
    // units, and the residuals are 0.0 px on all four rows. Two things make the solve
    // trustworthy rather than circular: the two fighters are 145 units tall (the rig's
    // rendered standing height, re-measured from a foundation capture), and the rows
    // then agree with each other to 0.1% on the opponent's size AND her ground contact
    // — a wrong height for her would break them apart. The solve is degenerate in the
    // FOV (a narrower FOV is a proportionally larger distance with the SAME height and
    // aim: at fov 20 the distance would be 775, at 60 it would be 178), which is why
    // the FOV had to come from the original's own code and not from the print.
    //
    // fovY/near/far are NOT fitted — they are read from the original's camera setup:
    // D3DXMatrixPerspectiveFovLH(&cam, 0x3f490fdb /* pi/4 */, 0x3faaaaab /* 4/3 */,
    // 0x42480000 /* 50 */, 0x48127c00 /* 150000 */) at DaybreakDX.exe 0x6338ae, applied
    // to the camera object at 0x6d1420 — which is the gameplay scene struct 0x6d13c0
    // + 0x60, i.e. exactly the camera the scene's per-frame update (0x6507c0, called at
    // 0x639b80) sets as D3DTS_VIEW/D3DTS_PROJECTION. The same fov/aspect/near/far
    // triple appears in the camera class's own setup at 0x661726. The original's fovy
    // is therefore 45 degrees, and the distance above is the only free parameter the
    // FOV leaves; the 300/800 constants the remake read as height/distance are the
    // NEAR/FAR offsets of a different (camera-node) projection at 0x6508bb/0x6508ae,
    // not a framing.
    //
    // baselineOrbit 0 = directly behind. In this tree the fighter's forward is
    // (sin yaw, 0, cos yaw) (gameplay/fighter.cpp:667), so the eye at angle
    // yaw - baseline is opposite that forward exactly when baseline is 0; the remake's
    // pi/4 is 45 degrees off it. Two pieces of evidence say the original sits behind:
    // the print's opponent — whom the fighter faces — is on the frame's vertical centre
    // line (x 395 of 798 against the player's 408; at the opponent's distance a
    // 45-degree offset is tens of pixels, not four), and the original's own pi/4
    // constant (0x6aac70) is used at 0x65092f as a *screen-space* rotation offset of a
    // billboard matrix, not as a camera azimuth. Measured against the running
    // foundation: with baseline 0 the eye lands on the line through the fighter
    // opposite her facing, which is the print's viewpoint.
    static constexpr ArenaCameraPreset original() { return ArenaCameraPreset{}; }

    // The DX9 remake's port: height 300, distance 800, aim +50, baseline π/4, fov π/4,
    // near 1, far 100000. Kept reachable because it is the *behavioural* oracle's
    // framing: tests/arena_camera_test.cpp pins the ported rules against it and
    // tests/parity-baseline/logs/*.log were banked with it. Not the match camera.
    static constexpr ArenaCameraPreset referenceRemake() {
        ArenaCameraPreset p;
        p.height        = 300.f;
        p.distance      = 800.f;
        p.aimHeight     = 50.f;
        p.baselineOrbit = 0.7853982f;
        p.fovY          = 0.7853982f;
        p.nearClip      = 1.f;
        p.farClip       = 100000.f;
        return p;
    }
};

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
    void set_action_rig(const xm::Model* model) {
        m_actionRig = model;
        m_actionController.bind(model);
        m_actionClip = 0;
        m_actionTime = 0.f;
    }
    void set_action(int clip, const glm::vec3& position, float yaw, const glm::vec3& opponent) {
        if (clip != m_actionClip) {
            m_actionClip = clip;
            m_actionTime = 0.f;
            m_actionYaw = yaw;
            m_previousActionAim = m_target;
            if (clip > 0) m_actionController.setAnimationBothTracks(clip, false);
        }
        m_actionPosition = position;
        m_actionOpponent = opponent;
    }
    // The reference's constructor body (identity view, zero eye/target, +Y up) is the
    // member initializers below; nothing is left to construct. The default preset is
    // the original game's framing — a match wants the game's camera, and the remake's
    // is one explicit argument away.
    ArenaCamera() = default;
    explicit ArenaCamera(const ArenaCameraPreset& preset) : m_preset(preset) {}

    // Swaps the framing. State (eye, target, orbit nudge, pool) is untouched: a preset
    // is geometry, not behaviour, and update() re-derives the desired eye from it.
    void                     set_preset(const ArenaCameraPreset& preset) { m_preset = preset; }

    // Switches the desired-eye formula to the recovered follow and supplies its anchor
    // (the opponent the followed fighter is locked onto). Call the setter every frame;
    // the camera reads it at update time. Deliberately separate from set_preset:
    // a preset is framing geometry, this is a different *rule*.
    void set_recovered_follow(bool on) { m_recoveredFollow = on; }
    void set_follow_anchor(const glm::vec3& anchorPos) { m_followAnchor = anchorPos; }
    bool recovered_follow() const { return m_recoveredFollow; }
    const ArenaCameraPreset& preset() const { return m_preset; }

    // ---- target management -------------------------------------------------
    // Sets the pool of fighters the camera can target. Pointers are NOT owned —
    // the caller keeps them alive (and refreshes the pointed-to position/facing
    // each frame; this class reads them at update time).
    void set_target_pool(const std::vector<CameraTarget*>& fighters);

    // Sets the active target by index. Does nothing when the index is out of range
    // or the fighter there is dead. A real change also arms the retarget blend
    // (kRetargetBlend) for kRetargetTicks calls; re-selecting the current target is not
    // a retarget and arms nothing.
    void set_active_target(int index);

    // Cycles to the next alive fighter, wrapping. Dead fighters are skipped; with
    // none alive the current target is kept. `forward` false cycles backward. As with
    // set_active_target, landing on a different fighter arms the retarget blend.
    //
    // NO MATCH CALLER since issue #51: the LockSwitch tap re-picks the COMBAT target
    // (Match::cycle_locked_target) and leaves the camera on the view's own fighter, which
    // is all FUN_00421e30/FUN_00421f30 write. It is kept because it is the ported
    // reference's own API — tests/arena_camera_test.cpp and tests/target_lock_test.cpp pin
    // its walk, its dead-skip and its retarget arming — not because a match reaches it.
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

    // Desired eye for one target: position + this preset's height, offset by its
    // baseline orbit in the XZ plane (plus this camera's orbit nudge and the
    // height/distance overrides). Public here (private in the reference) so the
    // device-free parity test can pin the numbers and the formula without stepping the
    // eye toward them. Does NOT apply collision.
    glm::vec3 compute_desired_eye(const CameraTarget* t) const;

private:
    const xm::Model* m_actionRig = nullptr;
    xm::Controller m_actionController;
    int m_actionClip = 0;
    float m_actionTime = 0.f;
    float m_actionYaw = 0.f;
    glm::vec3 m_actionPosition{0.f};
    glm::vec3 m_actionOpponent{0.f};
    glm::vec3 m_previousActionAim{0.f};
    float effective_height() const {
        return m_heightOverride >= 0.0f ? m_heightOverride : m_preset.height;
    }
    float effective_distance() const {
        return m_distOverride >= 0.0f ? m_distOverride : m_preset.distance;
    }

    // Camera state (the reference's m_view/m_eye/m_target/m_up).
    glm::mat4 m_view{1.0f};
    glm::vec3 m_eye{0.0f};
    glm::vec3 m_target{0.0f};
    glm::vec3 m_up{0.0f, 1.0f, 0.0f};   // Y-up world

    // Target pool.
    std::vector<CameraTarget*> m_pool;
    int                        m_activeIdx = -1;

    // Retarget window: calls left where followBlend() uses kRetargetBlend instead of
    // the reference's kFollowBlend. See armRetarget().
    int m_retargetTicks = 0;

    // Orbit nudge and the visual-validation overrides.
    float m_orbitNudge = 0.0f;
    float m_heightOverride = -1.0f;   // <0 = preset height
    float m_distOverride = -1.0f;     // <0 = preset distance

    // ---- recovered follow (PILOT-EVIDENCE-CONTRACT V3-15) --------------------
    // `arenaViewProj`'s height/distance are a reconstruction (V3-14), so the pitch is
    // constant and a jump cannot tilt the view. With this on, the desired eye comes
    // from render::arenaRecoveredFollow — FUN_006333b0's normal branch — which needs
    // the lock-on anchor (the followed fighter's target). Opt-in so the default
    // framing, and every capture pinned to it, is untouched.
    bool      m_recoveredFollow = false;
    glm::vec3 m_followAnchor{0.f};

    ArenaCameraPreset m_preset{};

    // render::arenaViewProj's own baseline orbit (render/arena_camera.h: angle =
    // facingYaw - π/4 + nudge). Passing nudge + (this - preset.baselineOrbit) to it puts
    // the eye at the preset's azimuth while leaving the eye formula in exactly one place.
    static constexpr float kRenderBaselineOrbit = 0.7853982f;   // π/4

    // Behaviour constants, from the reference: neither is framing, so neither is in a
    // preset. kFollowBlend is per CALL, not per second (arena_camera.cpp:123-136).
    static constexpr float kFollowBlend      = 0.1f;
    static constexpr float kCollisionMargin  = 20.0f;       // arena_camera.cpp:115

    // ---- retarget blend (issue #8) -------------------------------------------
    // The reference's 10%-per-call follow is a FOLLOWING camera's rate: over the ~40
    // calls it takes to converge, the old target has long left the screen, and the
    // switch reads as a slow drift. Switching targets is a different event, and at 0.1
    // it is the slowest part of a fight. kRetargetBlend converges in ~7 calls instead
    // while keeping the same exponential form, so the path stays smooth — no cut, no
    // overshoot — and the camera is back on the new fighter before the next exchange.
    //
    // PORT RULE, not recovered: the corpus pins the 0.1 follow (arena_camera.cpp:123-
    // 136) but nothing reads a switch-rate branch, and FUN_00421e30/FUN_00421f30 only
    // write the lock. The window is armed by a real target CHANGE, so a match that never
    // switches — every banked 1v1 capture, and any single-fighter pool — is bit-for-bit
    // on the reference's blend.
    //
    // WHO ARMS IT TODAY (audited for issue #51, which removed the match's cycle_target
    // call): only a set_active_target/cycle_target that lands somewhere new. A match
    // calls set_active_target once per view at construction, and set_target_pool has
    // already selected pool slot 0, so view 0's call is not a change (reference 0.1 from
    // its first update) while any OTHER view's call is one — a further view starts on 0.45
    // for kRetargetTicks calls. MEASURED with a two-fighter pool: first update at ratio
    // 0.100 for followed=0 and 0.450 for followed=1. Pre-existing (the construction order
    // is untouched by #51) and left as found: it is camera behaviour, not this issue's.
    static constexpr float kRetargetBlend     = 0.45f;
    static constexpr int   kRetargetTicks     = 10;

    void armRetarget() { m_retargetTicks = kRetargetTicks; }
    float followBlend() const;
};

}  // namespace gameplay
