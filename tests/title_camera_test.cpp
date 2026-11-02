// tests/title_camera_test.cpp — the title backdrop's sweep (issue #98).
//
// Device-free: render/title_camera.h is pure math, and the seeding of that sweep is the
// arena camera's own view of the stage's spawn, so the first frame can be checked against
// arenaViewProj itself rather than against a number copied into this file.
#include "render/title_camera.h"

#include <cmath>
#include <cstdio>

#define CHECK(x) do { if (!(x)) { std::fprintf(stderr, "failure: %s\n", #x); return 1; } } while (0)

namespace {

bool nearly(const glm::vec3& a, const glm::vec3& b, float epsilon = 1e-3f) {
    return std::fabs(a.x - b.x) <= epsilon && std::fabs(a.y - b.y) <= epsilon &&
           std::fabs(a.z - b.z) <= epsilon;
}

float groundDistance(const glm::vec3& from, const glm::vec3& to) {
    return std::sqrt((from.x - to.x) * (from.x - to.x) + (from.z - to.z) * (from.z - to.z));
}

}  // namespace

int main() {
    using namespace render;
    const glm::vec3 spawn(120.f, 200.f, -60.f);
    const TitleCamera camera = titleCameraFor(spawn);

    // The sweep starts where the arena camera puts the eye for a fighter at that spawn, so
    // the first frame is the game's own view of the stage rather than port framing.
    const ArenaFrame arena = arenaViewProj(ArenaTarget{spawn, 0.f}, ArenaCameraParams{}, 1.f);
    const TitleCameraPose start = titleCameraPose(camera, 0.f);
    CHECK(nearly(start.eye, arena.eye));
    CHECK(nearly(start.aim, arena.aim));
    CHECK(nearly(camera.pivot, arena.aim));

    // A framing the caller can rely on: the aim never moves, the eye keeps its height and
    // its ground distance for every second of the sweep.
    for (const float seconds : {0.f, 3.3f, 11.f, 21.9f, 43.9f, 600.f}) {
        const TitleCameraPose pose = titleCameraPose(camera, seconds);
        CHECK(nearly(pose.aim, camera.pivot));
        CHECK(std::fabs((pose.eye.y - camera.pivot.y) - camera.height) < 1e-3f);
        CHECK(std::fabs(groundDistance(pose.eye, camera.pivot) - camera.radius) < 1e-2f);
        CHECK(std::isfinite(pose.eye.x) && std::isfinite(pose.eye.y) && std::isfinite(pose.eye.z));
    }

    // One period is one there-and-back pass, so the pose repeats: a capture recipe can name
    // a phase in [0, period) and know what it gets.
    CHECK(nearly(titleCameraPose(camera, 0.7f).eye,
                 titleCameraPose(camera, 0.7f + camera.period).eye));
    // Pure: the same seconds give the same eye, which is what makes --out repeatable.
    CHECK(titleCameraPose(camera, 5.f).eye == titleCameraPose(camera, 5.f).eye);

    // Slow: a sixtieth of a second moves the eye by a small fraction of the radius. This is
    // the property the issue asks for ("the camera moving slowly"), pinned so a later tweak
    // cannot turn the backdrop into a spin.
    const glm::vec3 a = titleCameraPose(camera, 10.f).eye;
    const glm::vec3 b = titleCameraPose(camera, 10.f + 1.f / 60.f).eye;
    CHECK(glm::length(b - a) < camera.radius * 0.01f);
    CHECK(glm::length(b - a) > 0.f);

    // A zero swing is a locked camera, so the whole motion is the swing term and nothing
    // else contributes drift.
    TitleCamera locked = camera;
    locked.swing = 0.f;
    CHECK(nearly(titleCameraPose(locked, 0.f).eye, titleCameraPose(locked, 20.f).eye));

    // The motion is a SWEEP, not an orbit: the eye never crosses to the far side of the
    // pivot, which is what keeps a stage's arena-box back side out of the title.
    for (float seconds = 0.f; seconds < camera.period; seconds += 0.25f) {
        const TitleCameraPose pose = titleCameraPose(camera, seconds);
        const glm::vec3 centre = pose.eye - camera.pivot;
        const float azimuth = std::atan2(centre.z, centre.x);
        float delta = azimuth - camera.azimuth0;
        while (delta > 3.14159265f) delta -= 6.28318530718f;
        while (delta < -3.14159265f) delta += 6.28318530718f;
        CHECK(std::fabs(delta) <= camera.swing + 1e-5f);
    }

    // The composed shrine framing (issue #98): these numbers are an authored port rule, but
    // they are the ones the owner judged against the original's painting, so the frame is
    // pinned here — a later tweak to the pose math or a stray constant would move it.
    const TitleCamera shrine = shrineTitleCamera();
    const TitleCameraPose shrineStart = titleCameraPose(shrine, 0.f);
    CHECK(nearly(shrineStart.eye, glm::vec3(0.f, 430.f, 2300.f), 0.01f));
    CHECK(nearly(shrineStart.aim, glm::vec3(0.f, 1000.f, 4800.f), 0.01f));
    CHECK(std::fabs(shrine.fovY - 50.f) < 1e-4f);
    CHECK(!shrine.clampToArena);   // the eye stands outside the play area on purpose
    // The hall's front is at z 4346 and its side walls at x ±570 (title_camera.h): through
    // the whole sweep the eye must stay in front of it, centred enough to keep it framed.
    for (float seconds = 0.f; seconds < shrine.period; seconds += 0.5f) {
        const TitleCameraPose pose = titleCameraPose(shrine, seconds);
        CHECK(pose.eye.z < 4346.f);
        CHECK(std::fabs(pose.eye.x) < 600.f);
        CHECK(std::isfinite(pose.eye.x) && std::isfinite(pose.eye.y) && std::isfinite(pose.eye.z));
    }

    // The spawn's facing turns the sweep with it: a stage that faces another way is framed
    // from that way, because the seeding is arenaViewProj's own bearing.
    const TitleCamera turned = titleCameraFor(spawn, 1.2f);
    CHECK(std::fabs(turned.azimuth0 - camera.azimuth0) > 1e-3f);
    CHECK(nearly(turned.pivot, camera.pivot));
    CHECK(std::fabs(turned.radius - camera.radius) < 1e-3f);
    CHECK(std::fabs(turned.height - camera.height) < 1e-3f);
    return 0;
}
