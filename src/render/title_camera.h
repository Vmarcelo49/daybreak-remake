#pragma once
// The title backdrop's camera (issue #98).
//
// PORT RULE, tier 6 — the original's title is one still painting (data/title/back00, drawn
// by FUN_004114f0), so there is no recovered title camera to copy and this file claims
// none. Two decisions, both deliberate:
//
//   * the framing is SEEDED from the arena camera's own 3/4 view at the stage's spawn
//     (render::arenaViewProj), so the composition is the game's own view of that stage
//     rather than a number invented here;
//   * the motion is a there-and-back azimuth sweep, not a full orbit: a stage is an arena
//     box, and a full turn shows its back side — geometry that exists for a fight, not for
//     a view. The sweep also keeps the shrine approach, the subject of the original's
//     backdrop, on screen.
//
// Pure and clock-free: the caller passes the seconds, so a --out capture of the title is
// repeatable (scene_renderer.h's capture path) and the motion is testable without a device.
#include <cmath>

#include <glm/glm.hpp>

#include "camera/arena_view.h"

namespace render {

struct TitleCamera {
    glm::vec3 pivot{0.f};   // what the sweep looks at: the arena camera's aim at the spawn
    float radius = 800.f;   // ground distance from the pivot
    float height = 250.f;   // eye height above the pivot
    float azimuth0 = 0.f;   // centre of the sweep, radians about +Y (from +X toward +Z)
    float swing = 0.35f;    // half-width of the sweep, radians
    float period = 44.f;    // seconds for one there-and-back pass
};

struct TitleCameraPose {
    glm::vec3 eye{0.f};
    glm::vec3 aim{0.f};
};

// The eye and aim `seconds` into the sweep. Any finite `seconds` is valid; a non-positive
// period would divide by zero, so the caller's framing supplies a positive one.
inline TitleCameraPose titleCameraPose(const TitleCamera& camera, float seconds) {
    constexpr float kTau = 6.28318530718f;
    const float azimuth = camera.azimuth0 + camera.swing * std::sin(kTau * seconds / camera.period);
    TitleCameraPose pose;
    pose.eye = camera.pivot + glm::vec3(std::cos(azimuth) * camera.radius, camera.height,
                                        std::sin(azimuth) * camera.radius);
    pose.aim = camera.pivot;
    return pose;
}

// The sweep for a stage's spawn point, framed the way the arena camera frames a fighter
// standing there. `facingYaw` is the spawn's facing in FUN_00420b30's convention; a stage
// carries no facing of its own, so 0 (what --camera=arena uses) is the default.
inline TitleCamera titleCameraFor(const glm::vec3& spawn, float facingYaw = 0.f,
                                  const ArenaCameraParams& params = {}) {
    const ArenaFrame arena = arenaViewProj(ArenaTarget{spawn, facingYaw}, params, 1.f);
    const glm::vec3 offset = arena.eye - arena.aim;
    TitleCamera camera;
    camera.pivot = arena.aim;
    camera.height = offset.y;
    camera.radius = std::sqrt(offset.x * offset.x + offset.z * offset.z);
    // The sweep starts exactly where the arena camera would put the eye, so its first
    // frame is the game's own view of that spawn; the swing then moves away from it.
    camera.azimuth0 = std::atan2(offset.z, offset.x);
    return camera;
}

}  // namespace render
