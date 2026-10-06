// tests/shadow_map_test.cpp — device-free test for render/shadow_map.h (issue #21 row 1).
//
// The shadow pass is the one renderer feature whose *numbers* are the whole feature: the
// light's direction, the light camera's near/far and the receiver's bias/clamp/darkening
// are all recovered constants, and a wrong one of any of them moves every shadow in every
// frame without breaking a single draw. render/shadow_map.h exists so those numbers can be
// pinned with no device; this test pins them against the addresses the recovery came from
// (foundation/docs/SHADOWS.md carries the chain).
//
// What this does NOT prove: that the renderer *uses* these numbers. That is
// tests/character_shadow.py's job — it renders the frames and measures the pixels — and
// the two are deliberately separate: this one fails when a constant is edited, the
// capture one fails when the pass stops drawing.

#include <cmath>
#include <cstdio>

#include <glm/glm.hpp>

#include "render/shadow_map.h"

namespace {

int g_checks = 0;
int g_failures = 0;

void check(bool ok, const char* what) {
    ++g_checks;
    if (!ok) {
        ++g_failures;
        std::printf("FAIL: %s\n", what);
    }
}

void checkNear(float got, float want, float tolerance, const char* what) {
    const bool ok = std::fabs(got - want) <= tolerance;
    ++g_checks;
    if (!ok) {
        ++g_failures;
        std::printf("FAIL: %s (got %.6f, want %.6f +- %.6f)\n", what, got, want, tolerance);
    }
}

// The recovered constants, verbatim from the live original.
void constantCases() {
    check(render::kShadowLightEye == glm::vec3(1000.f, 1000000.f, 500000.f),
          "the light's eye is the three immediates at 0x650833-0x65084d");
    checkNear(render::kShadowFovY, 0.0010471975f, 1e-9f,
              "the light's fovy is D3DXMatrixPerspectiveFovLH's 0x3a89421f");
    checkNear(render::kShadowNearOffset, 300.f, 0.f, "the near offset is 0x6a1720 = 300.0");
    checkNear(render::kShadowFarOffset, 800.f, 0.f, "the far offset is 0x6a4928 = 800.0");
    checkNear(render::kShadowDepthBias, -0.02f, 1e-9f,
              "the receiver's bias is effect_3's c9.w = -0.02");
    checkNear(render::kShadowDepthClamp, 0.95f, 1e-9f,
              "the receiver's clamp is effect_3's c10.x = 0.95");
    checkNear(render::kShadowDarken, 0.3f, 1e-9f,
              "the shadowed albedo loses effect_3's ps c0 = 0.3");
    check(render::kShadowMapSize == 1024u, "the map is FUN_00650410's 0x400 square");
}

// The direction the light travels, which is what makes every shadow point the way it
// does. The original anchors the light camera on the *frame camera's eye*, so the
// direction is normalize(cameraEye - lightEye): the sun sits at the light eye's own
// direction from the scene, and the claim to pin is that it is a constant.
void directionCases() {
    const glm::vec3 sun = glm::normalize(render::kShadowLightEye);
    // The human's hypothesis was "the direction of the sun depends on the map". It does
    // not: (0, 2, 1)/sqrt(5) is 0.894427 and 0.447214, and the light eye's x term is
    // 0.000894 — three orders down, i.e. invisible.
    checkNear(sun.y, 2.f / std::sqrt(5.f), 1e-6f, "the sun's elevation is 2/sqrt(5)");
    checkNear(sun.z, 1.f / std::sqrt(5.f), 1e-6f, "the sun's azimuth is +Z, 1/sqrt(5)");
    check(std::fabs(sun.x) < 0.001f, "the sun's x term is negligible (0.0009)");

    // Across the whole playfield the travel direction moves by well under a tenth of a
    // degree: the arena is thousands of units across against a 1.1e6-unit light distance.
    const glm::vec3 travel = glm::normalize(glm::vec3(0.f) - render::kShadowLightEye);
    float worst = 0.f;
    for (int x = -2000; x <= 2000; x += 500)
        for (int z = -3000; z <= 0; z += 500) {
            const glm::vec3 eye((float)x, 200.f, (float)z);
            const glm::vec3 d = glm::normalize(eye - render::kShadowLightEye);
            worst = std::fmax(worst, glm::degrees(std::acos(glm::clamp(glm::dot(d, travel), -1.f, 1.f))));
        }
    check(worst < 0.2f, "the travel direction is stage-independent to within 0.2 degrees");
}

// The light camera itself: the recovered projection, and the two properties the receiver
// depends on — the camera eye projects to the map's centre, and a point offset along the
// light keeps the same map coordinate while landing deeper.
void cameraCases() {
    const glm::vec3 eye(-463.f, 200.f, -2200.f);   // stage01's own spawn triple
    const glm::mat4 m = render::shadowViewProj(eye);

    // The camera eye is the light camera's target, so it must land on the map's centre.
    const render::ShadowLookup at = render::shadowLookup(m, eye);
    checkNear(at.uv.x, 0.5f, 2e-3f, "the frame camera's eye projects to the map's centre (u)");
    checkNear(at.uv.y, 0.5f, 2e-3f, "the frame camera's eye projects to the map's centre (v)");
    check(at.inside, "and it is inside the map");

    // The near/far bracket that eye: z_ndc at the reference distance is
    // zf*(d-zn) / (d*(zf-zn)) = (d+800)*300 / (d*1100) — 0.273 for any d this large.
    const float d = glm::length(eye - render::kShadowLightEye);
    const float expected = (d + render::kShadowFarOffset) * render::kShadowNearOffset /
                           (d * (d + render::kShadowFarOffset - (d - render::kShadowNearOffset)));
    checkNear(at.own, expected + render::kShadowDepthBias, 5e-3f,
              "the reference point's biased depth is the recovered projection's z/w");

    // A caster standing on the ground: its feet are at the camera eye's own depth, its
    // head ~145 units closer to the light, and the ground point the light ray through the
    // head reaches is deeper still. That difference is the shadow.
    const glm::vec3 feet = eye;
    const glm::vec3 head = eye + glm::vec3(0.f, 145.f, 0.f);
    const float headTravel = glm::dot(head - render::kShadowLightEye,
                                      glm::normalize(eye - render::kShadowLightEye));
    const float feetTravel = glm::dot(feet - render::kShadowLightEye,
                                      glm::normalize(eye - render::kShadowLightEye));
    check(headTravel < feetTravel, "a raised caster is closer to the light than its feet");

    // The receiver that shares the head's map coordinate is 145 units further along the
    // light: same uv, deeper own — which is exactly the test the pixel shader runs.
    // Down the light ray (the direction of travel), which is where the shadow lands.
    const glm::vec3 shadowPoint = head + glm::normalize(eye - render::kShadowLightEye) * 145.f;
    const render::ShadowLookup headLookup = render::shadowLookup(m, head);
    const render::ShadowLookup groundLookup = render::shadowLookup(m, shadowPoint);
    checkNear(groundLookup.uv.x, headLookup.uv.x, 2e-3f,
              "the shadowed ground keeps the caster's map coordinate (u)");
    checkNear(groundLookup.uv.y, headLookup.uv.y, 2e-3f,
              "the shadowed ground keeps the caster's map coordinate (v)");
    check(groundLookup.own > headLookup.own, "and is deeper than the caster it samples");

    // The comparison the receiver's pixel shader makes: the map's alpha is the caster's
    // depth where something cast, and the cleared 1.0 sentinel where nothing did.
    check(render::shadowDarkens(groundLookup, headLookup.own),
          "a receiver behind a caster is shadowed");
    check(!render::shadowDarkens(groundLookup, 1.0f),
          "the cleared map (alpha 1.0) shadows nothing");
    check(!render::shadowDarkens(headLookup, headLookup.own),
          "a surface at its own depth is not shadowed (the bias' job)");

    // The 0.95 clamp: a receiver past the light's far plane still cannot beat the cleared
    // sentinel, which is why the original clamps it at all.
    const glm::vec3 farPoint = eye + glm::normalize(eye - render::kShadowLightEye) * 5000.f;
    const render::ShadowLookup farLookup = render::shadowLookup(m, farPoint);
    check(farLookup.own <= render::kShadowDepthClamp,
          "a receiver past the far plane is clamped at 0.95");
    check(!render::shadowDarkens(farLookup, 1.0f),
          "so it does not shadow itself against the empty map");

    // Behind the light: no lookup at all (the shader tests w > 0 before dividing).
    const glm::vec3 behind = render::kShadowLightEye + glm::vec3(0.f, 1000.f, 0.f);
    check(!render::shadowLookup(m, behind).inside, "a point behind the light is never inside");
}

// The border rule the port substitutes for D3DTADDRESS_BORDER: WebGPU has no border
// address mode, so the shader treats an out-of-range coordinate as "no caster" rather
// than reading the clamped edge texel.
void rangeCases() {
    const glm::vec3 eye(-463.f, 200.f, -2200.f);
    const glm::mat4 m = render::shadowViewProj(eye);
    // 600 units to the side of the light axis is outside the ~585-unit half-window.
    const glm::vec3 aside = eye + glm::vec3(600.f, 0.f, 0.f);
    const render::ShadowLookup l = render::shadowLookup(m, aside);
    check(!l.inside || l.uv.x < 0.f || l.uv.x > 1.f,
          "a receiver outside the light's window is not inside the map");
    check(!render::shadowDarkens(l, 0.0f),
          "and an out-of-range lookup never darkens, whatever the map holds");
}

}  // namespace

int main() {
    constantCases();
    directionCases();
    cameraCases();
    rangeCases();

    std::printf("\nchecks=%d failures=%d\n", g_checks, g_failures);
    std::printf("SHADOW_MAP: %s\n", g_failures == 0 ? "ok" : "FAIL");
    return g_failures == 0 ? 0 : 1;
}
