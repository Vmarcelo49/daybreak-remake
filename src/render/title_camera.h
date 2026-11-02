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
    glm::vec3 pivot{0.f};   // what the sweep looks at
    float radius = 800.f;   // horizontal distance from the pivot
    float height = 250.f;   // eye height relative to the pivot; negative puts the eye below it
    float azimuth0 = 0.f;   // centre of the sweep, radians about +Y (from +X toward +Z)
    float swing = 0.35f;    // half-width of the sweep, radians
    float period = 88.f;    // seconds for one there-and-back pass: half speed, by the owner's eye
    float fovY = 45.f;      // vertical field of view, degrees; 45 is viewProj's own
    // Clamp the eye to collision_camera, as the arena camera does. Only a framing seeded
    // from the arena wants it: that mesh bounds the play area, and an authored eye that
    // stands outside it on purpose would be pulled in against the aim.
    bool clampToArena = true;
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

// stage03 (the Furude shrine) composed after the painting in data/title/back00: the main
// hall small and low in the frame, a stone lantern either side, cedars filling the top.
// Measured on stage03's own geometry, not recovered: the hall (本体メイン) spans x ±570,
// y 383..1080, z 4346..5225, and the yard in front of it sits at y ~200 behind a retaining
// wall whose top the eye has to clear. The eye stands at (0, 430, 2300) — above that wall,
// short of the torii at z ~1800 — and looks up at (0, 1000, 4800), so the hall's base
// lands near the bottom of the menu. Beyond ±0.2 rad the flanking cedars cross the hall,
// hence the narrow swing.
inline TitleCamera shrineTitleCamera() {
    TitleCamera camera;
    camera.pivot = glm::vec3(0.f, 1000.f, 4800.f);
    camera.radius = 2500.f;
    camera.height = -570.f;
    camera.azimuth0 = -1.57079632679f;   // eye on -Z of the hall, facing its front
    camera.swing = 0.12f;
    camera.fovY = 50.f;
    camera.clampToArena = false;   // the eye is south of the play area by design
    return camera;
}

}  // namespace render
