// =============================================================================
//  arena_camera.h — 2v2 arena fighter camera with target lock-on.
//
//  Mirrors the design of the original game's camera (see
//  docs/reverse-engineering.md section 14):
//
//    * The camera is ALWAYS focused on one fighter (the "target").
//    * A button press cycles the target through the alive fighters.
//    * Camera orbits the target about the vertical (Y) axis with a
//      baseline angle of 45° (= π/4) offset from the target's facing.
//      (An earlier Z-up reading of fcn.006507c0's RotationZ was wrong:
//      that rotation feeds a 2D overlay transform in the same function,
//      while actors yaw with RotationY (FUN_00420b30), models stand along
//      Y, and D3D is Y-up by default.)
//    * Camera height offset = 300.0 units, distance offset = 800.0 units
//      (generous, to keep all 4 fighters visible in 2v2).
//    * Camera collision: raycast against `collision_camera.x` from the
//      desired eye position toward the target.  If blocked, the camera
//      springs to the unobstructed position.
//    * Up to 2 animation tracks (camera shake / scripted moves).
//
//  In the original game this is fcn.006507c0 (camera update) +
//  fcn.0042cb50 (camera collision).  We don't bit-exact mirror the
//  original's two-pass raycast yet — that's a future refinement.  For
//  now we do a single raycast and clamp the eye to the hit distance.
//
//  Usage:
//    ArenaCamera cam;
//    cam.set_target_fighters({&f1, &f2, &f3, &f4});
//    cam.set_active_target(0);
//    // each frame:
//    cam.update(dt, stage_collision_frame);
//    device->SetTransform(D3DTS_VIEW, &cam.view_matrix());
//    device->SetTransform(D3DTS_PROJECTION, &cam.proj_matrix(viewport_w, viewport_h));
// =============================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9anim.h>   // for D3DXFRAME (used by collision raycast)

#include <vector>

namespace daybreak {

struct CameraTarget {
    D3DXVECTOR3 position;       // world-space position (Y-up world)
    float       facing_yaw;     // yaw angle in radians (about Y axis)
    bool        alive = true;   // dead fighters are skipped by cycle_target
};

class ArenaCamera {
public:
    ArenaCamera();

    // ---- target management ------------------------------------------------
    // Sets the pool of fighters the camera can target.  Pointers are NOT
    // owned — caller must keep them alive.  Pass up to 4 fighters for 2v2.
    void set_target_pool(const std::vector<CameraTarget*>& fighters);

    // Sets the active target by index into the pool.  Does nothing if the
    // index is out of range or the fighter at that index is dead.
    void set_active_target(int index);

    // Cycles to the next alive fighter.  Wraps around.  Skips dead fighters.
    // If `forward` is false, cycles backward.
    void cycle_target(bool forward = true);

    int  active_target_index() const { return m_activeIdx; }
    CameraTarget* active_target() const;

    // ---- orbit control ----------------------------------------------------
    // The camera orbits the target about the Y axis (horizontal XZ plane).
    // The orbit angle is normally derived from the target's facing_yaw
    // (camera stays behind the target).  The user can nudge it with the
    // right stick.
    void nudge_orbit(float delta_radians) { m_orbitNudge += delta_radians; }
    void reset_orbit() { m_orbitNudge = 0.0f; }
    // Visual-validation overrides (suite explores viewpoints per stage).
    void set_height_offset(float h) { m_heightOverride = h; }
    void set_distance_offset(float d) { m_distOverride = d; }

    // ---- update -----------------------------------------------------------
    // Advances the camera by `dt` seconds.  If `collisionFrame` is non-null,
    // performs a raycast from the desired eye position toward the target
    // against the collision mesh; if blocked, clamps the eye distance.
    //
    // After update, view_matrix() and proj_matrix() return the latest
    // D3D9 view/projection matrices.
    void update(double dt, D3DXFRAME* collisionFrame = nullptr);

    // ---- outputs ----------------------------------------------------------
    const D3DXMATRIX& view_matrix() const { return m_view; }
    D3DXMATRIX proj_matrix(int viewport_w, int viewport_h) const;

    // ---- debug ------------------------------------------------------------
    const D3DXVECTOR3& eye()    const { return m_eye; }
    const D3DXVECTOR3& target() const { return m_target; }
    const D3DXVECTOR3& up()     const { return m_up; }

private:
    // Compute the desired eye position from the active target's position
    // and facing, accounting for the orbit nudge.  Does NOT apply collision.
    D3DXVECTOR3 compute_desired_eye(const CameraTarget* t) const;

    // Camera state (mirrors the original game's struct layout, see RE 14.8).
    D3DXMATRIX  m_view;
    D3DXMATRIX  m_proj;
    D3DXVECTOR3 m_eye;
    D3DXVECTOR3 m_target;
    D3DXVECTOR3 m_up;

    // Target pool.
    std::vector<CameraTarget*> m_pool;
    int                        m_activeIdx = -1;

    // Orbit nudge (user-controlled offset from the baseline 45° angle).
    float m_orbitNudge = 0.0f;
    float m_heightOverride = -1.0f;  // <0 = kHeightOffset
    float m_distOverride = -1.0f;    // <0 = kDistanceOffset

    // Cached collision state (for the spring lerp).
    float m_lastHitDist = 10000.0f;
    bool  m_hitLastFrame = false;

    // Constants (from RE section 14.7).
    static constexpr float kHeightOffset     = 300.0f;   // 0x6a1720
    static constexpr float kDistanceOffset   = 800.0f;   // 0x6a4928
    static constexpr float kBaselineZRotation = 0.7853982f; // π/4 (0x6aac70)
    static constexpr float kMaxRaycastDist   = 10000.0f; // 0x461c4000
    static constexpr float kFovY             = 0.7853982f; // π/4 — guess
    static constexpr float kNearClip         = 1.0f;
    static constexpr float kFarClip          = 100000.0f;
};

} // namespace daybreak
