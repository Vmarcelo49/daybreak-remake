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

// ---- Game-side smoothing + collision clamp (pure helpers, no state) ----
//
// WHY these live here yet own nothing: the reference springs the eye toward
// the desired eye at ~10% per frame (remake/src/render/arena_camera.cpp:123-136,
// fcn.006507c0 camera update) and clamps the eye against collision_camera.x
// (fcn.0042cb50 camera collision). Both need game-loop state the one-shot
// arenaViewProj above deliberately lacks — the previous eye, the frame delta,
// and the physics raycast — so the game layer owns the state and these answer
// only the math. No game constants are baked in: the caller passes the
// per-frame blend explicitly (the reference happens to use 0.1f at 60 fps),
// keeping this header free of tuning that belongs to gameplay code.

// One exponential-lerp step of the eye toward the desired eye. `alpha` is the
// blend fraction for this frame in [0,1] (0 = frozen, 1 = snap); out-of-range
// input is clamped so a bad caller cannot invert or overshoot the eye.
inline glm::vec3 arenaSmoothEye(const glm::vec3& prevEye, const glm::vec3& desiredEye,
                               float alpha) {
    const float a = glm::clamp(alpha, 0.f, 1.f);
    return prevEye + (desiredEye - prevEye) * a;
}

// Converts the reference's per-frame blend convention to a delta-correct
// alpha: alphaAt60fps is the fraction the caller wants at 60 fps (the
// reference passes 0.1f), dtSeconds is the real frame delta, refDt the frame
// the convention was tuned at (1/60 s). At dt == refDt this returns
// alphaAt60fps exactly; shorter/longer frames blend proportionally less/more
// so the eye converges in the same wall-clock time at any frame rate.
inline float arenaFrameAlpha(float alphaAt60fps, float dtSeconds, float refDt = 1.f / 60.f) {
    const float a = glm::clamp(alphaAt60fps, 0.f, 1.f);
    if (!(dtSeconds > 0.f) || !(refDt > 0.f)) return a;
    if (dtSeconds == refDt) return a;   // fixed-step fast path: exact, no pow rounding
    return 1.f - std::pow(1.f - a, dtSeconds / refDt);
}

// Smoothing step driven by wall-clock delta instead of a raw per-frame blend:
// the same lerp as arenaSmoothEye with the alpha mapped through
// arenaFrameAlpha, so callers on a variable-delta loop (the foundation demo's
// frame model) pass dt straight through. Takes (previous eye, desired eye,
// delta) as one call.
inline glm::vec3 arenaSmoothEyeDt(const glm::vec3& prevEye, const glm::vec3& desiredEye,
                                 float dtSeconds, float alphaAt60fps) {
    return arenaSmoothEye(prevEye, desiredEye, arenaFrameAlpha(alphaAt60fps, dtSeconds));
}

// Clamps the eye along the aim->desired segment to a physics hit distance.
// `hitDist` is the game physics query's answer: the distance from `aim` to
// the first collision_camera.x blocker along the aim->desiredEye ray, or a
// value >= the full segment length when unblocked. `margin` pulls the eye
// back from the wall so the near plane never sits inside geometry (the
// reference keeps ~20 units, arena_camera.cpp:115 — passed in, not baked in).
// Returns the desired eye unchanged when nothing blocks it; a hit at/below
// the margin collapses the eye onto the aim rather than behind it.
inline glm::vec3 arenaClampEye(const glm::vec3& aim, const glm::vec3& desiredEye, float hitDist,
                               float margin = 20.f) {
    const glm::vec3 leg = desiredEye - aim;
    const float full = glm::length(leg);
    if (!(full > 0.f)) return aim;
    const float m = glm::max(margin, 0.f);
    if (!(hitDist < full)) return desiredEye;   // unblocked (or a miss): nothing to do
    const float clamped = hitDist - m;
    if (clamped <= 0.f) return aim;
    return aim + leg * (clamped / full);
}

}  // namespace render
