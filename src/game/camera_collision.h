#pragma once
// Camera collision query interface: what the game must provide so the arena
// eye can clamp against collision_camera.x.
//
// WHY a query, not a raycast: the blocker test raycasts the stage's
// camera-only collision mesh (remake/src/maps/stage.h — collision_camera.x,
// CollisionChannel::Camera; render path in arena_camera.cpp:106-131 against
// physics/raycast.h, RE fcn.0042cb50). Mesh access + raycast machinery live
// in gameplay/physics, which the foundation must not own per PORT-PLAN.md.
// So physics implements this interface, and the camera path combines the
// answer with the pure render::arenaClampEye math: query in, clamped eye
// out, no raycast code in shared headers. glm + std only.
#include <glm/glm.hpp>

namespace game {

// One clamp query: the segment from the aim (fighter position + 50y, the
// lookAt target render::arenaViewProj computes) to the desired eye. Mirrors
// the reference raycast's inputs (target -> desiredEye, arena_camera.cpp:107).
struct CameraClampQuery {
    glm::vec3 aim{0.f};
    glm::vec3 desiredEye{0.f};
};

// The physics answer. `hit` false means the segment is clear; `hitDist` is
// then ignored. On a hit, `hitDist` is the distance from `aim` to the first
// blocker along the segment, in the same game units.
struct CameraClampResult {
    bool  hit = false;
    float hitDist = 0.f;
};

// Physics-side contract. Implementations raycast collision_camera.x (falling
// back to "no hit" on stages that ship none — stage.h notes some do) and
// return the first-blocker distance. Called once per frame per camera.
class ICameraCollision {
public:
    virtual ~ICameraCollision() = default;
    virtual CameraClampResult queryClamp(const CameraClampQuery& q) const = 0;
};

// Resolves a query result to the `hitDist` render::arenaClampEye takes: a
// miss becomes "at least the full segment length" (the clamp helper's
// pass-through case), so callers never branch on `hit` themselves.
inline float clampHitDistance(const CameraClampResult& r, float segmentLength) {
    return r.hit ? r.hitDist : segmentLength;
}

}  // namespace game
