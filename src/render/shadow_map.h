#pragma once
// The original's character shadow pass (issue #21 row 1), as pure glm: the light camera,
// its projection and the receiver's lookup. No WebGPU, no device — the same split
// render/arena_camera.h uses, so a host test can pin the recovered numbers with nothing
// but the standard library.
//
// All of it was read on the live original (DaybreakDX.exe, md5
// a136ddc01bd7ef355b759b88ac89e02c) and cross-checked against research/decompiled (the
// patched copy, which agrees instruction for instruction). foundation/docs/SHADOWS.md
// carries the full chain and the call sites; the addresses below are the load-bearing
// ones.
//
// The shape of it: FUN_006507c0 builds a light *camera* per view — a hardcoded eye 1.1e6
// units out, looking at the frame camera's own eye — and FUN_00652880 draws every
// fighter's body and weapon with that camera into a 1024x1024 A8R8G8B8 target whose alpha
// carries the caster's light NDC depth. The stage then samples that map projectively and
// subtracts 0.3 from its albedo where its own light depth is behind the map
// (FUN_00652af0 -> effect_3.bin).
//
// This is a shadow map, not a planar projected silhouette: the receiver compares a
// per-texel stored depth against its own with a bias and a clamp, the map is cleared to
// alpha 1.0 as a "nothing cast here" sentinel, and D3DXMatrixShadow is not in the
// original's import table at all.

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace render {

// The light's eye: three float immediates at 0x650833-0x65084d (1000.0, 1000000.0,
// 500000.0). The target is the frame camera's own eye and the up is the camera's up, so
// the direction of travel is normalize(cameraEye - lightEye) — a constant
// -(0, 2, 1)/sqrt(5) to within 0.1 degrees anywhere in the arena. The human's "the
// direction of the sun depends on the map" is NOT supported by the data: the only
// per-frame input is the camera's position, and no stage/env.dat field reaches this code.
inline constexpr glm::vec3 kShadowLightEye{1000.f, 1000000.f, 500000.f};
// FUN_006507c0:0x6508ca, D3DXMatrixPerspectiveFovLH's fovy (0x3a89421f) with aspect 1.0:
// a 0.06-degree cone at ~1.1e6 units, i.e. a ~1170-unit window on the scene centred on
// the camera eye — effectively an orthographic light box, and why the original's shadows
// read only near the fighters the camera follows.
inline constexpr float kShadowFovY = 0.0010471975f;   // 0x3a89421f
// The projection's near/far offsets from the camera eye's distance (0x6a1720 = 300.0,
// 0x6a4928 = 800.0, read from the live image at those addresses): 1100 units deep.
inline constexpr float kShadowNearOffset = 300.f;
inline constexpr float kShadowFarOffset  = 800.f;
// The receiver's own constants, out of effect_3.bin's vs_1_1 (c9.w and c10.x).
inline constexpr float kShadowDepthBias  = -0.02f;   // light NDC, the recovered bias
inline constexpr float kShadowDepthClamp = 0.95f;
// effect_3.bin's ps_1_1 def c0: the flat subtract the original applies to a shadowed
// albedo. Rides CameraUniform::shadowParams.w, so the shader and this constant cannot
// drift apart.
inline constexpr float kShadowDarken = 0.3f;
// FUN_00650410:0x65047c: the map's own size (0x400) and format 0x15 = A8R8G8B8.
inline constexpr uint32_t kShadowMapSize = 1024;

// The recovered light view * projection for one frame camera eye. The up vector is world
// +Y: the original reads the camera object's own up vector (FUN_006507c0:0x65089f) and
// every camera this port builds is Y-up (glm::lookAtLH(eye, aim, (0,1,0))), so the
// constant is the same vector. PORT RULE (issue #21 row 1): the original also
// post-multiplies a small clip-space tweak (RotZ(-camYaw - pi/4) * S(0.9,0.9,1) *
// T(0.7,-0.7,0), FUN_006507c0:0x6508e1-0x6509a0) that touches clip x/y only and is applied
// identically to the caster's clip position and the receiver's projected texcoords, so it
// cancels in the depth test and the lookup; the port omits it.
inline glm::mat4 shadowViewProj(const glm::vec3& eye) {
    const float d = glm::length(eye - kShadowLightEye);
    const glm::mat4 view = glm::lookAtLH(kShadowLightEye, eye, glm::vec3(0.f, 1.f, 0.f));
    const glm::mat4 proj =
        glm::perspectiveLH_ZO(kShadowFovY, 1.f, d - kShadowNearOffset, d + kShadowFarOffset);
    return proj * view;
}

// One receiver lookup, term for term the shader's (effect_3.bin's vs_1_1 and ps_1_1):
// the projected texture coordinate pair, the receiver's own biased-and-clamped light
// depth, and whether the coordinate is inside the map at all. `inside` stands in for the
// original's D3DTADDRESS_BORDER + black border colour, which WebGPU has no address mode
// for; the original's Tex1 sampler state is at FUN_00651110:0x6513ab-0x6513f6.
struct ShadowLookup {
    glm::vec2 uv{0.f};
    float     own = 0.f;
    bool      inside = false;
};

inline ShadowLookup shadowLookup(const glm::mat4& lightViewProj, const glm::vec3& world) {
    const glm::vec4 clip = lightViewProj * glm::vec4(world, 1.f);
    ShadowLookup out;
    if (!(clip.w > 0.f)) return out;   // behind the light: no lookup at all
    const float inv = 1.f / clip.w;
    out.uv = glm::vec2(clip.x * inv * 0.5f + 0.5f, 0.5f - clip.y * inv * 0.5f);
    out.own = std::fmin(clip.z * inv + kShadowDepthBias, kShadowDepthClamp);
    out.inside = out.uv.x >= 0.f && out.uv.x <= 1.f && out.uv.y >= 0.f && out.uv.y <= 1.f;
    return out;
}

// What the receiver's pixel shader decides: the albedo loses kShadowDarken where its own
// depth is behind the map's stored depth. `mapDepth` is the alpha the caster pass wrote
// (its light NDC depth), or 1.0 where nothing cast — the cleared sentinel, which the 0.95
// clamp keeps a receiver past the far plane from ever beating.
inline bool shadowDarkens(const ShadowLookup& lookup, float mapDepth) {
    return lookup.inside && lookup.own > mapDepth;
}

}  // namespace render
