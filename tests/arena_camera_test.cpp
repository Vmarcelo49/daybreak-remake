// tests/arena_camera_test.cpp — device-free test for gameplay/ArenaCamera.
//
// Build from the repo root (glm ships in the foundation's third_party):
//   g++ -std=c++20 -O2 -Wall -Wextra -I src
//       -I third_party/glm
//       src/camera/arena_camera.cpp
//       src/physics/raycast.cpp
//       tests/arena_camera_test.cpp -o /tmp/arena_camera_test
//   /tmp/arena_camera_test
//
// What this pins (every expectation is hand arithmetic, printed next to the measured
// value; each check states its tolerance — 1e-3 absolute at the 800-unit scale is
// 1.25e-6 relative, i.e. float noise — and drops to 0.f where the arithmetic is exact):
//   1. the desired-eye formula, including the height/distance overrides, the orbit
//      nudge and the aim raise;
//   2. convergence from the (0,0,0) seed: N updates leave 1 - 0.9^N of the desired
//      offset. The banked DX9 frame 1 is this rule with N = 1 — hud-dash logs
//      eye=(70,50,-38) with a 500-unit desired height, and 10% of 500 is 50 — which is
//      why the seed matters for parity;
//   3. the blocked path: snap to target + dir*(hit.dist - 20) in the same call, a
//      blocker inside the 20-unit margin collapsing onto the aim, and a miss (or a
//      blocker past the desired eye) taking the 10% lerp instead;
//   4. target management: dead-skipping, wrapping (both directions, including the
//      reference's walk from "no active target"), out-of-range/dead refusals;
//   5. the LH / Y-up / ZO [0,1] view-projection convention: the aim lands on the screen
//      centre, one unit in front is inside the depth range, and the projection equals
//      glm::perspectiveLH_ZO with referenceRemake()'s fov/near/far;
//   6. the ORIGINAL game's framing — ArenaCameraPreset::original(), which is what a
//      match now renders with: its seven numbers, the four axis-aligned desired-eye
//      cases they produce, its aim, its convergence and collision arithmetic, and its
//      projection.
//
// Which preset each section runs: 1-5 pin the ported rules against the DX9 remake's
// framing (height 300 / distance 800 / aim +50 / baseline π/4 / near 1 / far 100000),
// because those are the numbers the *behavioural* oracle's traces were banked with;
// 6 pins the original's numbers, which are the *visual* oracle's (the prints). A
// framing change must move section 6 and leave 1-5 alone — that is the point of the
// preset split, and it is what makes "the port's semantics are unchanged" testable.
//
// What this does NOT prove: parity with the DX9 binary. There is no in-process DX9
// oracle, and the collision cases use this test's own two-triangle quads, so they pin
// the rule (snap vs lerp, offsets, cutoff), not a banked frame. The frame-by-frame
// comparison against research/evidence/parity-baseline/logs/ is the caller's.
//
// Exit status: 0 when every check passed, 1 otherwise.

#include "camera/arena_camera.h"

#include "assets/xmodel.h"   // the synthetic collision quads below are xm::Model/Mesh

#include <cmath>
#include <cstdio>
#include <string>
#include <utility>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>

namespace {

using game::physics::buildModelIndex;
using game::physics::CameraCollision;
using game::physics::ModelIndex;
using game::physics::RayHit;
using game::physics::raycastModel;
using gameplay::ArenaCamera;
using gameplay::CameraTarget;
using gameplay::ArenaCameraPreset;
using gameplay::CollisionQuery;

int g_checks   = 0;
int g_failures = 0;

// ---------------------------------------------------------------------------------------
// Reporting
// ---------------------------------------------------------------------------------------
std::string f2s(float v) {
    char b[32];
    // -0 and +0 are the same number; print them the same so "got" does not depend on
    // which side of a rotation produced the zero.
    std::snprintf(b, sizeof b, "%.6f", static_cast<double>(v == 0.f ? 0.f : v));
    return b;
}
std::string v3s(const glm::vec3& v) {
    return "(" + f2s(v.x) + ", " + f2s(v.y) + ", " + f2s(v.z) + ")";
}

void section(const char* s) { std::printf("\n%s\n", s); }
void info(const std::string& s) { std::printf("  --   %s\n", s.c_str()); }

void check(bool ok, const std::string& what, const std::string& got, const std::string& want) {
    ++g_checks;
    if (ok) {
        std::printf("  ok   %-52s got=%s want=%s\n", what.c_str(), got.c_str(), want.c_str());
    } else {
        ++g_failures;
        std::printf("  FAIL %-52s got=%s want=%s\n", what.c_str(), got.c_str(), want.c_str());
    }
}

void checkNear(const std::string& what, const glm::vec3& got, const glm::vec3& want, float eps) {
    const bool ok = std::fabs(got.x - want.x) <= eps && std::fabs(got.y - want.y) <= eps &&
                    std::fabs(got.z - want.z) <= eps;
    check(ok, what, v3s(got), v3s(want) + " eps=" + f2s(eps));
}
void checkFloat(const std::string& what, float got, float want, float eps) {
    check(std::fabs(got - want) <= eps, what, f2s(got), f2s(want) + " eps=" + f2s(eps));
}
void checkInt(const std::string& what, int got, int want) {
    check(got == want, what, std::to_string(got), std::to_string(want));
}
void checkBool(const std::string& what, bool got, bool want) {
    check(got == want, what, got ? "true" : "false", want ? "true" : "false");
}
// Bit-exact by construction where both sides run the same arithmetic.
void checkMatExact(const std::string& what, const glm::mat4& got, const glm::mat4& want) {
    bool ok = true;
    for (int c = 0; c < 4; ++c)
        for (int r = 0; r < 4; ++r) ok = ok && got[c][r] == want[c][r];
    check(ok, what, ok ? "identical" : "differs", "identical");
}

// ---------------------------------------------------------------------------------------
// Fixtures
// ---------------------------------------------------------------------------------------
constexpr float kPi      = 3.14159265358979323846f;
constexpr float kPiOver4 = 0.7853982f;   // the reference's kBaselineZRotation/kFovY
constexpr float kSin45   = 0.7071067811865475f;
constexpr float kCos45   = 0.7071067811865475f;
// 800 * sin(π/4), the horizontal leg of the default orbit.
constexpr float kLeg800  = 565.6854249492379f;

CameraTarget makeTarget(float x, float y, float z, float yaw, bool alive = true) {
    CameraTarget t;
    t.position  = glm::vec3(x, y, z);
    t.facingYaw = yaw;
    t.alive     = alive;
    return t;
}

// One quad as two triangles in the plane z = `z`, spanning [x0,x1] x [y0,y1]. Frame-less
// (xm::Mesh::frame == -1), the shape every shipped collision_camera.X has, so the
// traversal order is mesh order and the ray test is plain geometry.
xm::Model quadAtZ(float z, float x0, float x1, float y0, float y1) {
    xm::Mesh m;
    const glm::vec3 corners[4] = {{x0, y0, z}, {x1, y0, z}, {x1, y1, z}, {x0, y1, z}};
    for (const glm::vec3& c : corners) {
        xm::Vertex v;
        v.pos = c;   // the raycast reads pos only
        m.vertices.push_back(v);
    }
    m.indices = {0, 1, 2, 0, 2, 3};
    xm::Model model;
    model.meshes.push_back(std::move(m));
    return model;
}

// ---------------------------------------------------------------------------------------
// 1. constants and the desired-eye formula
// ---------------------------------------------------------------------------------------
void desiredEyeCases() {
    section("1. constants + desired-eye formula");
    ArenaCamera cam(ArenaCameraPreset::referenceRemake());
    // angle = facing - π/4 + nudge. facing 0 -> angle = -π/4, so the horizontal offset
    // is (-sin(-π/4), -cos(-π/4)) * 800 = (+800·sin45, -800·cos45); height 300.
    const CameraTarget front = makeTarget(0.f, 200.f, 0.f, 0.f);
    checkNear("facing 0  ->  eye = pos + (800·sin45, 300, -800·cos45)",
              cam.compute_desired_eye(&front),
              glm::vec3(0.f + kLeg800, 200.f + 300.f, 0.f - kLeg800), 1e-3f);

    // facing π/2 -> angle = +π/4: the offset rotates a quarter turn.
    const CameraTarget side = makeTarget(0.f, 200.f, 0.f, kPi / 2.f);
    checkNear("facing π/2 -> rotated counterpart (-800·sin45, 300, -800·cos45)",
              cam.compute_desired_eye(&side),
              glm::vec3(0.f - kLeg800, 200.f + 300.f, 0.f - kLeg800), 1e-3f);

    // The desired eye follows the target's position, not the origin.
    const CameraTarget moved = makeTarget(1393.f, 200.f, -463.f, 0.f);
    checkNear("position is added component-wise",
              cam.compute_desired_eye(&moved),
              glm::vec3(1393.f + kLeg800, 500.f, -463.f - kLeg800), 1e-3f);

    // Height override: 500 replaces 300, distance untouched.
    cam.set_height_offset(500.f);
    checkNear("set_height_offset(500) -> dy = 500",
              cam.compute_desired_eye(&front),
              glm::vec3(kLeg800, 200.f + 500.f, -kLeg800), 1e-3f);
    // Distance override: 1000 replaces 800, height stays overridden.
    cam.set_distance_offset(1000.f);
    checkNear("set_distance_offset(1000) -> both legs scale (height stays 500)",
              cam.compute_desired_eye(&front),
              glm::vec3(1000.f * kSin45, 700.f, -1000.f * kCos45), 1e-3f);
    // The reference's override test is `>= 0`, so 0 is a legal height.
    cam.set_height_offset(0.f);
    checkNear("set_height_offset(0) is a legal override (dy = 0)",
              cam.compute_desired_eye(&front),
              glm::vec3(1000.f * kSin45, 200.f, -1000.f * kCos45), 1e-3f);
    // Negative restores the constant, not 0.
    cam.set_height_offset(-1.f);
    checkNear("set_height_offset(-1) restores 300",
              cam.compute_desired_eye(&front),
              glm::vec3(1000.f * kSin45, 500.f, -1000.f * kCos45), 1e-3f);
    cam.set_distance_offset(-1.f);
    checkNear("set_distance_offset(-1) restores 800",
              cam.compute_desired_eye(&front),
              glm::vec3(kLeg800, 500.f, -kLeg800), 1e-3f);

    // Orbit nudge: angle shifts by exactly the nudge, nothing else.
    cam.nudge_orbit(0.25f);
    // angle = 0 - 0.7853982 + 0.25 = -0.5353982 -> (-sin·800, -cos·800).
    checkNear("nudge_orbit(+0.25) shifts the angle by 0.25 rad",
              cam.compute_desired_eye(&front),
              glm::vec3(408.146836f, 500.f, -688.052440f), 1e-3f);
    cam.nudge_orbit(0.15f);   // accumulates to +0.40
    checkNear("nudges accumulate (0.25 + 0.15 = 0.40)",
              cam.compute_desired_eye(&front),
              glm::vec3(300.742516f, 500.f, -741.319054f), 1e-3f);
    cam.reset_orbit();
    checkNear("reset_orbit() returns to the π/4 baseline",
              cam.compute_desired_eye(&front),
              glm::vec3(kLeg800, 500.f, -kLeg800), 1e-3f);

    // No target: the reference's fallback, (0, 0, kHeightOffset).
    checkNear("compute_desired_eye(nullptr) = (0, 0, 300)",
              cam.compute_desired_eye(nullptr), glm::vec3(0.f, 0.f, 300.f), 1e-3f);

    // The aim update() builds is the position raised 50, not the position.
    ArenaCamera aimCam(ArenaCameraPreset::referenceRemake());
    CameraTarget piOver4 = makeTarget(0.f, 200.f, 0.f, kPiOver4);
    std::vector<CameraTarget*> pool{&piOver4};
    aimCam.set_target_pool(pool);
    aimCam.set_active_target(0);
    aimCam.update(1.0 / 60.0);
    checkNear("update() aim = position + 50y", aimCam.target(), glm::vec3(0.f, 250.f, 0.f), 1e-6f);
    checkNear("facing π/4 cancels the baseline: eye = position + (0, 300, -800)",
              aimCam.compute_desired_eye(&piOver4), glm::vec3(0.f, 500.f, -800.f), 1e-3f);
}

// ---------------------------------------------------------------------------------------
// 2. convergence from the (0,0,0) seed
// ---------------------------------------------------------------------------------------
void convergenceCases() {
    section("2. convergence: N updates leave (1 - 0.9^N) of the desired offset");
    ArenaCamera cam(ArenaCameraPreset::referenceRemake());
    CameraTarget t = makeTarget(0.f, 0.f, 0.f, kPiOver4);   // desired eye (0, 300, -800)
    std::vector<CameraTarget*> pool{&t};
    cam.set_target_pool(pool);
    cam.set_active_target(0);

    checkNear("seed: eye() is (0,0,0) before any update", cam.eye(), glm::vec3(0.f), 0.f);

    struct Step { int n; glm::vec3 want; float eps; const char* label; };
    const Step steps[] = {
        // 1 - 0.9^1 = 0.1        -> (0, 30, -80)
        {1, glm::vec3(0.f, 30.f, -80.f), 1e-4f, "N=1   (0.1 of the desired)"},
        // 1 - 0.9^2 = 0.19       -> (0, 57, -152)
        {2, glm::vec3(0.f, 57.f, -152.f), 1e-4f, "N=2   (0.19)"},
        // 1 - 0.9^10 = 0.6513215599 -> (0, 195.396468, -521.057248)
        {10, glm::vec3(0.f, 195.396468f, -521.057248f), 1e-3f, "N=10  (0.6513215599)"},
    };
    // The 10%-per-call blend is the reference's (arena_camera.cpp:123-136), NOT dt
    // scaled: these counts are update calls whatever dt says.
    checkNear("N=0   the same before stepping", cam.eye(), glm::vec3(0.f), 0.f);
    int done = 0;
    for (const Step& s : steps) {
        while (done < s.n) { cam.update(0.5, {}); ++done; }   // dt deliberately not 1/60
        checkNear(s.label, cam.eye(), s.want, s.eps);
    }

    // Never overshoots: every step stays on the segment [origin, desired], the distance
    // to the desired eye never grows, and it strictly shrinks while there is still
    // progress to make (the last ~4 float ulps stop moving: the increment rounds away).
    const float segLen = glm::length(glm::vec3(0.f, 300.f, -800.f) - glm::vec3(0.f, 50.f, 0.f));
    info("segment length |aim->desired| = sqrt(250² + 800²) = " + f2s(segLen));
    float prevDist = glm::length(cam.eye() - glm::vec3(0.f, 300.f, -800.f));
    float prevS    = 1.f - prevDist / segLen;
    bool  progress = true, monotone = true, onSegment = true, inside = true;
    for (int i = 0; i < 300; ++i) {
        cam.update(1.0 / 60.0, {});
        const glm::vec3 e = cam.eye();
        const float dist = glm::length(e - glm::vec3(0.f, 300.f, -800.f));
        const float s    = 1.f - dist / segLen;
        if (i < 100 && !(dist < prevDist)) progress = false;   // still far from converged
        if (!(dist <= prevDist)) monotone = false;
        if (!(std::fabs(e.x) < 1e-6f)) onSegment = false;
        if (!(s >= 0.f && s <= 1.f && s >= prevS)) inside = false;
        prevDist = dist;
        prevS    = s;
    }
    checkBool("300 further updates: the first 100 each move the eye closer (strict)", progress, true);
    checkBool("300 further updates: distance to the desired eye never grows", monotone, true);
    checkBool("300 further updates: the eye never leaves the origin->desired segment", onSegment, true);
    checkBool("300 further updates: the approach parameter is monotone inside [0,1]", inside, true);
    info("after 300 calls: eye=" + v3s(cam.eye()) +
         " residual=" + f2s(glm::length(cam.eye() - glm::vec3(0.f, 300.f, -800.f))));
}

// ---------------------------------------------------------------------------------------
// 3. collision: snap on hit, collapse inside the margin, lerp on a miss
// ---------------------------------------------------------------------------------------
void collisionCases() {
    section("3. collision: blocked frames snap in the same call");
    // facing π/4 -> angle 0 -> desired eye = pos + (0, 300, -800); aim = pos + 50y.
    // With pos (0,0,0): aim (0,50,0), desired (0,300,-800), leg (0,250,-800),
    // |leg| = sqrt(250² + 800²) = 838.152731.
    const glm::vec3 aim(0.f, 50.f, 0.f);
    const glm::vec3 desired(0.f, 300.f, -800.f);
    const glm::vec3 leg = desired - aim;
    const float     len = glm::length(leg);
    const glm::vec3 dir = leg / len;
    info("aim=" + v3s(aim) + " desired=" + v3s(desired) + " |leg|=" + f2s(len));

    // A blocker at z = -400 sits halfway along z, so t = |leg|/2 = 419.076365.
    {
        xm::Model model = quadAtZ(-400.f, -500.f, 500.f, -100.f, 900.f);
        const ModelIndex index = buildModelIndex(model);
        const RayHit independent = raycastModel(model, index, aim, dir, len);
        CameraCollision cc;
        cc.setMesh(&model);
        checkBool("quad at z=-400: the test's own raycast hits", independent.hit, true);
        checkFloat("quad at z=-400: hit.dist = |leg|/2", independent.dist, 419.076365f, 1e-3f);

        ArenaCamera cam(ArenaCameraPreset::referenceRemake());
        CameraTarget t = makeTarget(0.f, 0.f, 0.f, kPiOver4);
        std::vector<CameraTarget*> pool{&t};
        cam.set_target_pool(pool);
        cam.set_active_target(0);
        const glm::vec3 lerpValue = desired * 0.1f;
        cam.update(1.0 / 60.0, CollisionQuery{&cc});
        // target + dir*(hit.dist - 20) with hit.dist = 419.076365 -> clamp 399.076365:
        //   y = 50 + (250/838.152731)·399.076365 = 169.034500
        //   z = 0  - (800/838.152731)·399.076365 = -380.910400
        checkNear("blocked: eye snaps to aim + dir·(hit.dist-20) in the SAME call",
                  cam.eye(), glm::vec3(0.f, 169.034500f, -380.910400f), 1e-3f);
        checkNear("blocked: eye = aim + dir·(hit.dist-20), rule form",
                  cam.eye(), aim + dir * (independent.dist - 20.f), 1e-3f);
        info("same frame, the unblocked 10% lerp would have been " + v3s(lerpValue));
    }

    // A blocker inside the 20-unit margin: clamp distance 0, so the eye lands exactly on
    // the aim (t = 10/0.954480 = 10.476909 < 20).
    {
        xm::Model model = quadAtZ(-10.f, -500.f, 500.f, -100.f, 900.f);
        CameraCollision cc;
        cc.setMesh(&model);
        ArenaCamera cam(ArenaCameraPreset::referenceRemake());
        CameraTarget t = makeTarget(0.f, 0.f, 0.f, kPiOver4);
        std::vector<CameraTarget*> pool{&t};
        cam.set_target_pool(pool);
        cam.set_active_target(0);
        cam.update(1.0 / 60.0, CollisionQuery{&cc});
        checkNear("hit closer than 20 units collapses the eye onto the aim",
                  cam.eye(), aim, 0.f);
    }

    // A miss: no geometry on the segment -> the 10% lerp.
    {
        xm::Model model = quadAtZ(-400.f, 2000.f, 3000.f, -100.f, 900.f);
        CameraCollision cc;
        cc.setMesh(&model);
        ArenaCamera cam(ArenaCameraPreset::referenceRemake());
        CameraTarget t = makeTarget(0.f, 0.f, 0.f, kPiOver4);
        std::vector<CameraTarget*> pool{&t};
        cam.set_target_pool(pool);
        cam.set_active_target(0);
        cam.update(1.0 / 60.0, CollisionQuery{&cc});
        checkNear("miss: the eye lerps 10% instead", cam.eye(),
                  glm::vec3(0.f, 30.f, -80.f), 1e-4f);
    }

    // A blocker beyond the desired eye (z = -900 -> t = 942.921822 > |leg|): the raycast
    // is asked over the desired distance only, so this is a miss and the eye lerps.
    {
        xm::Model model = quadAtZ(-900.f, -500.f, 500.f, -100.f, 900.f);
        const ModelIndex index = buildModelIndex(model);
        const RayHit beyond = raycastModel(model, index, aim, dir, 0.f);   // no cutoff
        checkBool("quad at z=-900: reachable with no cutoff (so the case is live)",
                  beyond.hit, true);
        checkBool("quad at z=-900: beyond the desired eye", beyond.dist > len, true);
        CameraCollision cc;
        cc.setMesh(&model);
        ArenaCamera cam(ArenaCameraPreset::referenceRemake());
        CameraTarget t = makeTarget(0.f, 0.f, 0.f, kPiOver4);
        std::vector<CameraTarget*> pool{&t};
        cam.set_target_pool(pool);
        cam.set_active_target(0);
        cam.update(1.0 / 60.0, CollisionQuery{&cc});
        checkNear("blocker past the desired eye: full-distance ray misses, eye lerps",
                  cam.eye(), glm::vec3(0.f, 30.f, -80.f), 1e-4f);
    }

    // No query configured (the reference's nullptr collisionFrame, the match scene's
    // configuration): the same 10% lerp, never a snap.
    {
        ArenaCamera cam(ArenaCameraPreset::referenceRemake());
        CameraTarget t = makeTarget(0.f, 0.f, 0.f, kPiOver4);
        std::vector<CameraTarget*> pool{&t};
        cam.set_target_pool(pool);
        cam.set_active_target(0);
        cam.update(1.0 / 60.0);
        checkNear("default query (nullptr frame): eye lerps 10%", cam.eye(),
                  glm::vec3(0.f, 30.f, -80.f), 1e-4f);
    }
}

// ---------------------------------------------------------------------------------------
// 4. target management
// ---------------------------------------------------------------------------------------
void targetCases() {
    section("4. target management: dead-skipping, wrapping, refusals");
    CameraTarget a = makeTarget(0.f, 0.f, 0.f, 0.f, true);
    CameraTarget b = makeTarget(100.f, 0.f, 0.f, 0.f, false);
    CameraTarget c = makeTarget(200.f, 0.f, 0.f, 0.f, true);
    CameraTarget d = makeTarget(300.f, 0.f, 0.f, 0.f, false);
    std::vector<CameraTarget*> pool{&a, &b, &c, &d};

    ArenaCamera cam(ArenaCameraPreset::referenceRemake());
    checkInt("fresh camera: active_target_index() = -1", cam.active_target_index(), -1);
    checkBool("fresh camera: active_target() = nullptr", cam.active_target() == nullptr, true);

    cam.set_target_pool(pool);
    checkInt("set_target_pool picks the first ALIVE target (index 0, skipping none)", cam.active_target_index(), 0);

    cam.set_active_target(1);   // dead
    checkInt("set_active_target(dead 1) refused", cam.active_target_index(), 0);
    cam.set_active_target(4);   // out of range
    checkInt("set_active_target(4) refused (out of range)", cam.active_target_index(), 0);
    cam.set_active_target(-1);
    checkInt("set_active_target(-1) refused", cam.active_target_index(), 0);
    cam.set_active_target(2);
    checkInt("set_active_target(2) accepted", cam.active_target_index(), 2);
    checkBool("active_target() is the pool entry at that index", cam.active_target() == &c, true);

    cam.cycle_target(true);     // 3 dead -> wraps to 0
    checkInt("cycle_target(forward) from 2 skips dead 3 and wraps to 0", cam.active_target_index(), 0);
    cam.cycle_target(true);     // 1 dead -> 2
    checkInt("cycle_target(forward) from 0 skips dead 1 -> 2", cam.active_target_index(), 2);
    cam.cycle_target(false);    // 1 dead -> wraps back to 0
    checkInt("cycle_target(backward) from 2 skips dead 1 -> 0", cam.active_target_index(), 0);

    // A pool with nobody alive leaves no target; set_target_pool then re-scans.
    a.alive = false;
    b.alive = false;
    c.alive = false;   // d is already dead
    cam.set_target_pool(pool);
    checkInt("all dead: set_target_pool leaves index -1", cam.active_target_index(), -1);
    cam.cycle_target(true);
    checkInt("all dead: cycle_target keeps -1", cam.active_target_index(), -1);
    cam.set_active_target(0);
    checkInt("a dead pool refuses set_active_target", cam.active_target_index(), -1);

    // A still-valid alive index survives set_target_pool.
    c.alive = true;
    cam.set_target_pool(pool);   // from -1: first alive is 2
    checkInt("set_target_pool from -1 picks the first alive (2)", cam.active_target_index(), 2);
    cam.set_target_pool(pool);
    checkInt("set_target_pool keeps an index that is still alive", cam.active_target_index(), 2);

    // Losing the current target re-picks.
    a.alive = true;
    c.alive = false;
    cam.set_target_pool(pool);
    checkInt("the active target died: set_target_pool re-picks (0)", cam.active_target_index(), 0);

    // The reference walks from m_activeIdx, so with NO active target (-1) a forward walk
    // starts at index 0 and a backward one at n-2 — it never tries the last index first.
    // Reach -1 with an all-dead pool, then revive entries without re-scanning (the
    // pointers are live, so the camera sees the new flags).
    {
        CameraTarget p0 = makeTarget(0.f, 0.f, 0.f, 0.f, false);
        CameraTarget p1 = makeTarget(0.f, 0.f, 0.f, 0.f, false);
        CameraTarget p2 = makeTarget(0.f, 0.f, 0.f, 0.f, false);
        CameraTarget p3 = makeTarget(0.f, 0.f, 0.f, 0.f, false);
        std::vector<CameraTarget*> mixed{&p0, &p1, &p2, &p3};

        ArenaCamera fwd;
        fwd.set_target_pool(mixed);
        checkInt("walk fixture: all dead -> no active target", fwd.active_target_index(), -1);
        p1.alive = true;
        p2.alive = true;
        p3.alive = true;
        fwd.cycle_target(true);
        checkInt("forward from -1 lands on the first alive (1)", fwd.active_target_index(), 1);

        p1.alive = false;
        p2.alive = false;
        p3.alive = false;
        ArenaCamera back;
        back.set_target_pool(mixed);
        checkInt("walk fixture: all dead again -> no active target", back.active_target_index(), -1);
        p1.alive = true;
        p2.alive = true;
        p3.alive = true;
        back.cycle_target(false);
        checkInt("backward from -1 starts at n-2 (2), not at the last index", back.active_target_index(), 2);
    }

    // Empty pool: nothing to do, and update() must not touch the view or the eye.
    {
        ArenaCamera empty;
        empty.set_target_pool({});
        empty.update(1.0 / 60.0);
        empty.cycle_target(true);
        checkInt("empty pool: cycle_target is a no-op", empty.active_target_index(), -1);
        checkBool("empty pool: active_target() = nullptr", empty.active_target() == nullptr, true);
        checkNear("empty pool: update() leaves the eye at (0,0,0)", empty.eye(), glm::vec3(0.f), 0.f);
        checkMatExact("empty pool: update() leaves the view at identity", empty.view_matrix(), glm::mat4(1.f));
    }
}

// ---------------------------------------------------------------------------------------
// 5. view/projection convention
// ---------------------------------------------------------------------------------------
void matrixCases() {
    section("5. view/projection: LH, Y-up, depth [0,1]");
    ArenaCamera cam(ArenaCameraPreset::referenceRemake());
    CameraTarget t = makeTarget(0.f, 0.f, 0.f, kPiOver4);   // desired eye (0, 300, -800)
    std::vector<CameraTarget*> pool{&t};
    cam.set_target_pool(pool);
    cam.set_active_target(0);
    const float aspect = 1280.f / 720.f;
    cam.update(1.0 / 60.0);

    // view_matrix() is D3DXMatrixLookAtLH == glm::lookAtLH(eye, aim, +Y).
    const glm::mat4 view = cam.view_matrix();
    checkMatExact("view_matrix() == glm::lookAtLH(eye, aim, +Y)",
                  view, glm::lookAtLH(cam.eye(), cam.target(), glm::vec3(0.f, 1.f, 0.f)));
    checkNear("view maps the eye to the view-space origin", glm::vec3(view * glm::vec4(cam.eye(), 1.f)),
              glm::vec3(0.f), 1e-3f);

    const glm::mat4 proj = cam.proj_matrix(1280, 720);
    // D3DXMatrixPerspectiveFovLH(fovY, aspect, near, far) is glm::perspectiveLH_ZO with
    // the same arguments; the reference's constants are π/4, 1, 100000.
    checkMatExact("proj_matrix() == glm::perspectiveLH_ZO(π/4, aspect, 1, 100000)",
                  proj, glm::perspectiveLH_ZO(kPiOver4, aspect, 1.f, 100000.f));
    // Hand-checked entries: 1/(aspect·tan(fov/2)), 1/tan(fov/2), far/(far-near),
    // 1, -(far·near)/(far-near), 0.
    checkFloat("proj[0][0] = 1/(aspect·tan(π/8))", proj[0][0], 1.357995059f, 1e-6f);
    checkFloat("proj[1][1] = 1/tan(π/8)", proj[1][1], 2.414213437f, 1e-6f);
    checkFloat("proj[2][2] = far/(far-near) = 100000/99999", proj[2][2], 1.000010000f, 1e-7f);
    checkFloat("proj[2][3] = 1 (w_clip = z_view)", proj[2][3], 1.f, 0.f);
    checkFloat("proj[3][2] = -far·near/(far-near)", proj[3][2], -1.000010000f, 1e-7f);
    checkFloat("proj[3][3] = 0", proj[3][3], 0.f, 0.f);
    // A viewport height of 0 means aspect 1 (the reference's guard), not a division.
    const glm::mat4 square = cam.proj_matrix(1280, 0);
    checkFloat("proj_matrix(w, 0) uses aspect 1", square[0][0], square[1][1], 0.f);

    const glm::mat4 vp = proj * view;   // column vectors: clip = proj·view·world
    // The aim projects to the screen centre: x = y = 0, z inside the depth range.
    const glm::vec4 aimClip = vp * glm::vec4(cam.target(), 1.f);
    const glm::vec3 aimNdc  = glm::vec3(aimClip) / aimClip.w;
    checkNear("aim projects to the NDC centre", aimNdc, glm::vec3(0.f, 0.f, aimNdc.z), 1e-5f);
    checkBool("aim is in front of the eye (w_clip > 0)", aimClip.w > 0.f, true);
    checkBool("aim's z/ w is inside [0,1]", aimNdc.z >= 0.f && aimNdc.z <= 1.f, true);
    info("aim clip=(" + f2s(aimClip.x) + ", " + f2s(aimClip.y) + ", " + f2s(aimClip.z) +
         ", " + f2s(aimClip.w) + ")  ndc.z=" + f2s(aimNdc.z));

    // One unit in front of the eye is the near plane: z_ndc = 0, w = 1. The range tests
    // carry 1e-4 of slack: the point is float-computed, so the exact zero comes back as
    // a few ulps either side.
    constexpr float kDepthEps = 1e-4f;
    const glm::vec3 forward = glm::normalize(cam.target() - cam.eye());
    const glm::vec4 nearClip = vp * glm::vec4(cam.eye() + forward, 1.f);
    const glm::vec3 nearNdc  = glm::vec3(nearClip) / nearClip.w;
    checkBool("a point 1 unit in front is inside the depth range",
              nearNdc.z >= -kDepthEps && nearNdc.z <= 1.f + kDepthEps, true);
    checkFloat("a point 1 unit in front is at the near plane (z_ndc = 0)", nearNdc.z, 0.f, 1e-4f);

    // Depth is ZO: z_ndc = (far/(far-near))·(1 - near/z). At z = 2 (near = 1) that is
    // 1.00001·(1 - 0.5) = 0.500005, and at z = far = 100000 it is 1.
    const glm::vec4 midClip = vp * glm::vec4(cam.eye() + forward * 2.f, 1.f);
    checkFloat("z_ndc at 2 units = (100000/99999)·(1 - 1/2) = 0.500005",
               midClip.z / midClip.w, 0.500005f, 1e-4f);
    const glm::vec4 farClip = vp * glm::vec4(cam.eye() + forward * 100000.f, 1.f);
    checkFloat("a point at 100000 units is z_ndc = 1", farClip.z / farClip.w, 1.f, 1e-4f);
    // Beyond the far plane is NOT asserted: at far/near = 100000 the ZO mapping is
    // already 1 + 1e-10 at 100001 units, which float cannot represent apart from 1. The
    // near/far values are pinned by the projection entries above instead.
    // Left-handed: the forward direction has positive z in view space.
    checkBool("LH: a point in front has positive view z",
              (view * glm::vec4(cam.eye() + forward * 10.f, 1.f)).z > 0.f, true);
    // Behind the eye: negative w, i.e. outside the frustum.
    checkBool("a point behind the eye has w_clip < 0",
              (vp * glm::vec4(cam.eye() - forward * 100.f, 1.f)).w < 0.f, true);

    // Before the first update the view is the constructor's identity.
    ArenaCamera fresh(ArenaCameraPreset::referenceRemake());
    checkMatExact("fresh camera: view_matrix() = identity", fresh.view_matrix(), glm::mat4(1.f));
}

// ---------------------------------------------------------------------------------------
// 6. the original game's preset (the default: what a match renders with)
// ---------------------------------------------------------------------------------------
void originalPresetCases() {
    section("6. the original's framing (ArenaCameraPreset::original(), the default)");
    // Why these numbers and not the remake's: the visual target is the original's own
    // prints (FULL-REPLACEMENT-PLAN.md §6a). The preset's own comment carries the
    // measurement; this section pins the arithmetic every frame's framing follows from.
    const ArenaCameraPreset p = ArenaCameraPreset::original();
    checkFloat("original: eye height above the fighter = 211", p.height, 211.f, 0.f);
    checkFloat("original: horizontal eye distance = 289", p.distance, 289.f, 0.f);
    checkFloat("original: aim = position + 138 (her neck, not the remake's +50)", p.aimHeight,
               138.f, 0.f);
    checkFloat("original: baseline orbit = 0 (directly behind the facing)", p.baselineOrbit,
               0.f, 0.f);
    checkFloat("original: fovy = pi/4 (the original's own D3DX call)", p.fovY, kPiOver4, 1e-9f);
    checkFloat("original: near = 50", p.nearClip, 50.f, 0.f);
    checkFloat("original: far = 150000", p.farClip, 150000.f, 0.f);

    // The default camera IS the original: a match must render the game's framing.
    ArenaCamera def;
    checkFloat("default-constructed camera uses the original preset", def.preset().height,
               p.height, 0.f);
    checkFloat("default-constructed camera: aim height is the original's", def.preset().aimHeight,
               p.aimHeight, 0.f);

    ArenaCamera cam;   // default = original
    // The fighter's forward is (sin yaw, 0, cos yaw) (fighter.cpp:667), so "directly
    // behind" (baseline 0) puts the eye at pos - forward*distance + height.
    // facing 0 -> forward +z -> eye = pos + (0, 211, -289).
    CameraTarget behind = makeTarget(0.f, 200.f, 0.f, 0.f);
    checkNear("original: facing 0 (+z) -> eye = pos + (0, 211, -289)",
              cam.compute_desired_eye(&behind), glm::vec3(0.f, 411.f, -289.f), 1e-3f);
    // facing pi/2 -> forward +x -> eye = pos + (-289, 211, 0).
    const CameraTarget plusX = makeTarget(10.f, 200.f, 20.f, kPi / 2.f);
    checkNear("original: facing pi/2 (+x) -> eye = pos + (-289, 211, 0)",
              cam.compute_desired_eye(&plusX), glm::vec3(-279.f, 411.f, 20.f), 1e-3f);
    // facing pi -> forward -z -> the opposite side again.
    const CameraTarget minusZ = makeTarget(0.f, 200.f, 0.f, kPi);
    checkNear("original: facing pi (-z) -> eye = pos + (0, 211, 289)",
              cam.compute_desired_eye(&minusZ), glm::vec3(0.f, 411.f, 289.f), 1e-3f);

    // No target: still the preset's height, as the reference's fallback used its constant.
    checkNear("original: compute_desired_eye(nullptr) = (0, 0, 211)",
              cam.compute_desired_eye(nullptr), glm::vec3(0.f, 0.f, 211.f), 0.f);

    // The aim update() builds is position + 138.
    std::vector<CameraTarget*> pool{&behind};
    cam.set_target_pool(pool);
    cam.set_active_target(0);
    cam.update(1.0 / 60.0);
    checkNear("original: update() aim = position + 138y", cam.target(),
              glm::vec3(0.f, 338.f, 0.f), 1e-6f);

    // Convergence is the same per-call rule; only the desired eye changed. From the
    // (0,0,0) seed, N calls leave 1 - 0.9^N of it: 10% of (0, 211, -289). The target
    // sits at the origin so the arithmetic is the desired eye itself, as in section 2.
    CameraTarget origin = makeTarget(0.f, 0.f, 0.f, 0.f);
    ArenaCamera conv;
    std::vector<CameraTarget*> cpool{&origin};
    conv.set_target_pool(cpool);
    conv.set_active_target(0);
    conv.update(0.5, {});
    checkNear("original: N=1 leaves 10% of (0, 211, -289)", conv.eye(),
              glm::vec3(0.f, 21.1f, -28.9f), 1e-4f);
    conv.update(0.5, {});
    checkNear("original: N=2 leaves 19%", conv.eye(), glm::vec3(0.f, 40.09f, -54.91f), 1e-4f);
    for (int i = 2; i < 10; ++i) conv.update(0.5, {});
    checkNear("original: N=10 leaves 0.6513215599", conv.eye(),
              glm::vec3(0.f, 137.428881f, -188.232831f), 1e-3f);

    // The blocked path under the new framing: the same snap rule, a different segment.
    {
        // aim (0,138,0) -> desired (0,211,-289); |leg| = sqrt(73^2 + 289^2) = 298.077...
        const glm::vec3 aim(0.f, 138.f, 0.f);
        const glm::vec3 desired(0.f, 211.f, -289.f);
        const glm::vec3 leg = desired - aim;
        const float     len = glm::length(leg);
        const glm::vec3 dir = leg / len;
        info("original: |aim->desired| = " + f2s(len));
        xm::Model model = quadAtZ(-144.5f, -500.f, 500.f, -100.f, 900.f);
        const ModelIndex index = buildModelIndex(model);
        const RayHit independent = raycastModel(model, index, aim, dir, len);
        checkBool("original: quad at z=-144.5 is hit", independent.hit, true);
        CameraCollision cc;
        cc.setMesh(&model);
        std::vector<CameraTarget*> hpool{&origin};
        ArenaCamera hit;
        hit.set_target_pool(hpool);
        hit.set_active_target(0);
        hit.update(1.0 / 60.0, CollisionQuery{&cc});
        checkNear("original: blocked -> eye = aim + dir.(hit.dist - 20)",
                  hit.eye(), aim + dir * (independent.dist - 20.f), 1e-3f);
        ArenaCamera miss;
        miss.set_target_pool(hpool);
        miss.set_active_target(0);
        miss.update(1.0 / 60.0);
        checkNear("original: unblocked 10% lerp is much closer than the snap",
                  miss.eye(), desired * 0.1f, 1e-4f);
        checkBool("original: the snap lands past the lerp (both on the same ray)",
                  glm::length(hit.eye() - aim) > glm::length(miss.eye()), true);
    }

    // The projection is the original's: fovy pi/4 (unchanged), near 50, far 150000.
    const glm::mat4 proj = cam.proj_matrix(1280, 720);
    checkMatExact("original: proj_matrix() == glm::perspectiveLH_ZO(pi/4, aspect, 50, 150000)",
                  proj, glm::perspectiveLH_ZO(kPiOver4, 1280.f / 720.f, 50.f, 150000.f));
    checkFloat("original: proj[1][1] = 1/tan(pi/8)", proj[1][1], 2.414213437f, 1e-6f);
    checkFloat("original: proj[2][2] = far/(far-near) = 150000/149950", proj[2][2],
               1.000333444f, 1e-7f);
    checkFloat("original: proj[3][2] = -far.near/(far-near)", proj[3][2], -50.016672240f, 1e-5f);
    // The vertical scale is what a pixel-height measurement rides on; it is unchanged
    // from the remake's because both use pi/4 -- which is why only the distance moved.
    const glm::mat4 ref = glm::perspectiveLH_ZO(kPiOver4, 1280.f / 720.f, 1.f, 100000.f);
    checkFloat("original: the vertical scale matches the remake's fov (proj[1][1])",
               proj[1][1], ref[1][1], 0.f);
}

// 7. Per-view cameras (issue #12): the original holds one camera per controller slot —
// FUN_006396f0 renders each view with its own per-controller context and its LockSwitch walk
// moves that view's followed player — so one ArenaCamera per view is the unit. What matters
// is that they are INDEPENDENT: two views follow different fighters, cycling one leaves the
// other untouched, and each projects its own cell aspect.
void splitViewCameraCases() {
    section("7. per-view cameras: independent targets and per-cell projection");
    CameraTarget blue = makeTarget(0.f, 200.f, 0.f, 0.f);
    CameraTarget red = makeTarget(1200.f, 200.f, 400.f, kPi);
    std::vector<CameraTarget*> pool{&blue, &red};

    ArenaCamera views[2];
    for (ArenaCamera& cam : views) {
        cam.set_preset(ArenaCameraPreset::original());
        cam.set_target_pool(pool);
    }
    views[0].set_active_target(0);
    views[1].set_active_target(1);
    for (int i = 0; i < 200; ++i) {
        views[0].update(1.0 / 60.0);
        views[1].update(1.0 / 60.0);
    }
    checkInt("view 0 follows fighter 0", views[0].active_target_index(), 0);
    checkInt("view 1 follows fighter 1", views[1].active_target_index(), 1);
    check(glm::length(views[0].eye() - views[1].eye()) > 100.f,
          "two views following different fighters have different eyes", v3s(views[0].eye()),
          v3s(views[1].eye()));

    // Cycling one view's lock moves that view only: the other keeps both its index and the
    // eye it had converged on. A shared camera would fail this.
    const glm::vec3 view1Eye = views[1].eye();
    const int view1Index = views[1].active_target_index();
    views[0].cycle_target(true);
    views[0].update(1.0 / 60.0);
    checkInt("cycling view 0 does not move view 1's lock", views[1].active_target_index(),
             view1Index);
    checkNear("cycling view 0 does not move view 1's eye", views[1].eye(), view1Eye, 0.f);
    checkInt("view 0's own cycle did move view 0", views[0].active_target_index(), 1);

    // Each view projects its own cell: the same camera state at two cell aspects gives two
    // different horizontal scales, each exactly glm::perspectiveLH_ZO at that aspect. This is
    // what lets a 400x300 quadrant and an ultrawide cell share one camera class (D8).
    const glm::mat4 quadrant = views[1].proj_matrix(400, 300);
    const glm::mat4 wide = views[1].proj_matrix(1720, 720);
    checkMatExact("a 400x300 view projects at 4:3",
                  quadrant, glm::perspectiveLH_ZO(kPiOver4, 400.f / 300.f, 50.f, 150000.f));
    checkMatExact("an ultrawide view projects at its own aspect",
                  wide, glm::perspectiveLH_ZO(kPiOver4, 1720.f / 720.f, 50.f, 150000.f));
    checkFloat("the vertical scale is aspect-independent (same fov)", quadrant[1][1],
               wide[1][1], 0.f);
    check(std::fabs(quadrant[0][0] - wide[0][0]) > 0.1f,
          "the horizontal scale differs per cell aspect", f2s(quadrant[0][0]), f2s(wide[0][0]));
}

// ===========================================================================
//  Recovered normal follow — FUN_006333b0 (+0x95 == 0 && +0x94 == 0)
//  Every constant is from the pinned binary's .rdata; see
//  docs/PILOT-EVIDENCE-CONTRACT.md V3-15. The behavioural claim this covers is
//  the owner's: raising the rig must change the eye->aim ANGLE (a jump tilts the
//  camera), which the old flat height/aim formula could never do.
// ===========================================================================
void recoveredFollowCases() {
    section("recovered normal follow (V3-15)");
    render::ArenaCameraParams p;
    const float aspect = 4.f / 3.f;

    // Rig at the origin, anchor 600 units ahead on +Z: inside the 400..800 band, so
    // the aim basis shrinks by dist/800 = 0.75 and dist stays 600.
    const render::ArenaFrame f =
        render::arenaRecoveredFollow(glm::vec3(0.f), glm::vec3(0.f, 0.f, 600.f), p, aspect);
    // offset = delta*0.75 - (0,120,0) = (0,-120,450); |offset| = 465.7; scale = 300/465.7.
    const float scale = std::min(300.f / std::sqrt(120.f * 120.f + 450.f * 450.f), 1.5f);
    checkFloat("eye sits behind the rig on the anchor axis", f.eye.z,
               -(450.f * scale), 1e-3f);
    checkFloat("eye is lifted by 140 + 0.03*dist over the bias",
               f.eye.y, 140.f + 600.f * 0.03f + 120.f * scale, 1e-3f);
    checkFloat("eye keeps the rig's x", f.eye.x, 0.f, 1e-4f);
    checkFloat("aim lands on the anchor axis", f.aim.z, 450.f, 1e-3f);
    checkFloat("aim is lifted by 20 - 0.2*dist", f.aim.y, 20.f - 600.f * 0.2f, 1e-3f);

    // The tilt: hold the anchor fixed and raise the rig by a jump. The eye->aim
    // angle must change; a flat-offset camera would keep it identical.
    const glm::vec3 anchor(0.f, 0.f, 600.f);
    const render::ArenaFrame grounded = render::arenaRecoveredFollow(glm::vec3(0.f), anchor, p, aspect);
    const render::ArenaFrame airborne =
        render::arenaRecoveredFollow(glm::vec3(0.f, 300.f, 0.f), anchor, p, aspect);
    const auto pitchOf = [](const render::ArenaFrame& fr) {
        const glm::vec3 d = fr.aim - fr.eye;
        return std::atan2(-d.y, std::sqrt(d.x * d.x + d.z * d.z));
    };
    check(std::fabs(pitchOf(airborne) - pitchOf(grounded)) > 0.02f,
          "a raised rig changes the camera pitch", f2s(pitchOf(airborne)),
          "!= " + f2s(pitchOf(grounded)));

    // Near band: closer than 400 the basis is expanded to the 400 floor, so the
    // reported distance stops shrinking.
    const render::ArenaFrame near =
        render::arenaRecoveredFollow(glm::vec3(0.f), glm::vec3(0.f, 0.f, 100.f), p, aspect);
    checkFloat("below the 400 floor the aim basis uses 400", near.aim.z, 400.f * (400.f / 100.f) / 2.f * (100.f / 400.f) + 0.f,
               1e-2f);
    // offset at the floor = (0, -120, 200); the lift term is -offset.y after scaling.
    const float nearScale = std::min(300.f / std::sqrt(120.f * 120.f + 200.f * 200.f), 1.5f);
    checkFloat("below the floor the eye lift uses dist = 400", near.eye.y,
               140.f + 400.f * 0.03f + 120.f * nearScale, 1e-2f);

    // The 1.5 cap: a nearly coincident rig and anchor saturates the view distance.
    const render::ArenaFrame capped =
        render::arenaRecoveredFollow(glm::vec3(0.f), glm::vec3(0.f, 0.5f, 0.5f), p, aspect);
    const float capLen = glm::length(capped.eye - glm::vec3(0.f));
    check(capLen <= 450.f + 1e-2f, "the view distance caps at 1.5x300", f2s(capLen), "<= 450");
}

}  // namespace

// ---------------------------------------------------------------------------------------
// 9. the action camera's sentinel: set 0 plays, and only a negative value means "off"
//
// FUN_006358c0:59-64 clears the action camera on a NEGATIVE request and otherwise passes the
// value to FUN_00633140 as an animation set on the rig — 0 included. The port used 0 as its own
// "off" value until V3-37, which made the recovered Hyper EX request (set 0) unplayable; the rig
// path is guarded by `m_actionClip >= 0`. This case fails if that comparison goes back to `> 0`,
// which no fighter-level assertion can see.
// ---------------------------------------------------------------------------------------
glm::vec3 actionCameraEye(const xm::Model& rig, int clip) {
    ArenaCamera cam(ArenaCameraPreset::referenceRemake());
    CameraTarget self{};
    self.position = glm::vec3(0.f, 200.f, 0.f);
    CameraTarget foe{};
    foe.position = glm::vec3(0.f, 200.f, 400.f);
    std::vector<CameraTarget*> pool = {&self, &foe};
    cam.set_target_pool(pool);
    cam.set_active_target(0);
    cam.set_action_rig(&rig);
    cam.set_action(clip, self.position, 0.f, foe.position);
    cam.update(1.0 / 60.0);
    return cam.eye();
}

void actionCameraCases() {
    section("9. the action camera plays set 0 and is off at -1");
    // A minimal rig with the real frame names and one animation per set. The bind offsets do
    // not matter: the action eye is actionPosition + rotation * pose[Box01] * (1,0,0), which
    // sits at the fighter, while the ordinary follow sits a preset distance behind her.
    xm::Model rig;
    xm::Frame box1;
    box1.name = "Box01";
    box1.bindLocal = glm::mat4(1.f);
    xm::Frame box2;
    box2.name = "Box02";
    box2.bindLocal = glm::mat4(1.f);
    rig.frames = {box1, box2};
    rig.anims.resize(2);
    rig.anims[0].duration = 800.f;
    rig.anims[1].duration = 480.f;
    rig.ticksPerSecond = 4800.f;

    const glm::vec3 off = actionCameraEye(rig, -1);
    const glm::vec3 setZero = actionCameraEye(rig, 0);
    const glm::vec3 setOne = actionCameraEye(rig, 1);
    check(glm::length(setZero - off) > 50.f,
          "set 0 leaves the ordinary follow (0 is a real set, not off)", v3s(setZero - off), "> 50");
    check(glm::length(setOne - off) > 50.f,
          "control: set 1 leaves it too, so the check above is not luck", v3s(setOne - off), "> 50");
    // And -1 is the sentinel. This baseline never calls set_action at all, so it is an
    // independent expectation rather than a second copy of the -1 setup: a camera that ignored
    // the sentinel and played set 0 would fail the comparison.
    ArenaCamera plain(ArenaCameraPreset::referenceRemake());
    CameraTarget self{};
    self.position = glm::vec3(0.f, 200.f, 0.f);
    std::vector<CameraTarget*> pool = {&self};
    plain.set_target_pool(pool);
    plain.set_active_target(0);
    plain.set_action_rig(&rig);
    plain.update(1.0 / 60.0);
    checkNear("-1 keeps the ordinary follow (no action camera was ever requested)",
              off, plain.eye(), 1e-3f);
}

int main() {
    desiredEyeCases();
    convergenceCases();
    collisionCases();
    targetCases();
    matrixCases();
    originalPresetCases();
    splitViewCameraCases();
    recoveredFollowCases();
    actionCameraCases();

    std::printf("\nchecks=%d failures=%d\n", g_checks, g_failures);
    std::printf("ARENA_CAMERA: %s\n", g_failures == 0 ? "ok" : "FAIL");
    return g_failures == 0 ? 0 : 1;
}
