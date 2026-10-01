#pragma once
// Game/arena camera path, isolated from the demo's framing heuristic.
//
// main.cpp frames captures from mesh bounds and env.dat spawn points, which is a
// verification convenience, not the game: the original follows its fighters with a
// target-locked arena camera (remake/src/render/arena_camera.h, RE section 14 —
// fcn.006507c0 camera update + fcn.0042cb50 camera collision). This header is the
// foundation side of that path: the same eye/target/projection math, expressed in
// glm so render/ and the future game layer share it, with no window, input or
// collision state. The caller owns targets, smoothing and the collision raycast
// against collision_camera.x; this only answers "where is the eye for this
// target, and what is its view-projection".
//
// Deliberately one-shot (no spring lerp, no retained eye): smoothing needs the
// previous frame's eye and the frame delta, which belong to the game loop, not to
// a camera function. The integration patch is reported in docs/RENDER-CAMERA.md.

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace render {

// One fighter the camera locks onto. `position` is world-space, Y-up game units;
// fighter spawns come from env.dat's point triples read as (x, y, z) with y the
// shared ~200 height — the reading scene.h uses and the arena eye math below
// assumes (a stage21 spawn lands on the playfield only under that order).
struct ArenaTarget {
    glm::vec3 position{0.f};
    float     facingYaw = 0.f;   // actor yaw about Y, FUN_00420b30 convention
};

struct ArenaCameraParams {
    float heightOffset = 300.f;       // 0x6a1720, generous: keeps 4 fighters framed
    float distanceOffset = 800.f;     // 0x6a4928
    float orbitNudge = 0.f;           // right-stick adjustment, radians
    float fovY = 0.7853982f;          // π/4 — arena_camera.h marks this a guess
    float nearClip = 1.f;
    float farClip = 100000.f;         // 0x461c4000; max() with the scene reach, as
                                      // the framing path does, when the sky dome may
                                      // sit further out
};

struct ArenaFrame {
    glm::vec3 eye{0.f};
    glm::vec3 aim{0.f};
    glm::mat4 viewProj{1.f};
};

// Desired eye for one target, then its view-projection at `aspect`. Mirrors
// ArenaCamera::compute_desired_eye/update/proj_matrix term by term:
//   * the eye sits 45° (π/4, 0x6aac70) to the side of the facing, giving a 3/4 view
//     rather than directly behind;
//   * XZ is the horizontal plane, Y is up: dx = -sin(angle)*dist, dz = -cos(angle)*dist;
//   * the aim is the fighter's position raised 50 units, not the position itself;
//   * left-handed lookAt and FOV projection, Y-up NDC passed through unchanged
//     (the WebGPU convention the whole renderer relies on).
inline ArenaFrame arenaViewProj(const ArenaTarget& t, const ArenaCameraParams& p, float aspect) {
    constexpr float kBaselineOrbit = 0.7853982f;   // π/4, 0x6aac70
    const float angle = t.facingYaw - kBaselineOrbit + p.orbitNudge;
    ArenaFrame f;
    f.eye = t.position + glm::vec3(-std::sin(angle) * p.distanceOffset, p.heightOffset,
                                   -std::cos(angle) * p.distanceOffset);
    f.aim = t.position + glm::vec3(0.f, 50.f, 0.f);
    const glm::mat4 view = glm::lookAtLH(f.eye, f.aim, glm::vec3(0.f, 1.f, 0.f));
    const glm::mat4 proj = glm::perspectiveLH_ZO(p.fovY, aspect, p.nearClip, p.farClip);
    f.viewProj = proj * view;
    return f;
}

}  // namespace render
