#pragma once
// WebGPU half of the asset layer's model declarations: uniform layouts and vertex
// buffer layouts consumed by scene_renderer.h and model.wgsl.
//
// These declarations used to sit inside assets/xmodel.h behind XMODEL_WEBGPU. Because
// that header is #pragma once, whichever consumer included it first decided whether
// this half existed at all: a CPU-only include (raycast.h, npr_normals.h, the device-free
// tests) hid it from a later renderer include. It owns its guard and its webgpu.h
// dependency here instead, so include order no longer matters (issue #129).
// Nothing in the CPU parser (XMODEL_IMPLEMENTATION) depends on this header.
#include <webgpu/webgpu.h>

#include <cstddef>   // offsetof

#include "assets/xmodel.h"

// ---------------------------------------------------------------------------------------
// Bind group contract expected by model.wgsl (the shader shipped next to xmodel.h):
//   group 0, binding 0  uniform Camera { mat4 viewProj; vec4 lightDir; vec4 lightColor; vec4 ambient; }
//   group 0, binding 1  texture_2d<f32>  (the toon ramp, issue #21)
//   group 0, binding 2  sampler
//   group 1, binding 0  uniform Draw   (dynamic offset; see DrawUniform below)
//   group 1, binding 1  storage readonly array<mat4x4<f32>, N>  (bone palettes)
//   group 2, binding 0  texture_2d<f32>
//   group 2, binding 1  sampler
// ---------------------------------------------------------------------------------------

namespace xm {

inline constexpr uint64_t kVertexAttributeCount = 6;

// Per-draw uniform, 176 bytes of payload. Bound with a dynamic offset, so each record
// must start on a minUniformBufferOffsetAlignment boundary (256 on every current
// adapter) — see kDrawStride.
struct DrawUniform {
    glm::mat4 model{1.f};          // entity -> world; identity when the palette bakes it
    glm::vec4 baseColor{1.f};      // multiplies the material diffuse and vertex colour
    // The material's Emissive, alpha 1. This is the original's "MaterialColor" for the
    // toon effect (issue #21): the runtime material records are D3DXMATERIAL copies
    // (0x48 bytes, FUN_00661f60:116 memcpy), so the float4 the effect is handed at
    // material+0x30 is D3DMATERIAL9.Emissive, NOT the diffuse at +0x00 — the fixed-
    // function path's ambient is the diffuse (D3DX sets Ambient := Diffuse for .X
    // materials), which is why baseColor carries that term instead.
    glm::vec4 emissive{0.f, 0.f, 0.f, 1.f};
    // NPR experiment parameters (issue #25), one slot per experiment so a COMPOSED arm
    // (the issue's suggested D/E stack runs bands, key, rim and normals together) keeps
    // each one's own values. They shared one slot at first and the last writer won, which
    // silently turned the composed capture into a rim-only one. Everything here is zero on
    // an unmodified renderer, and the band thresholds are shader constants — see
    // model_wgsl.h — because they were fixed across the whole grid and a uniform that
    // never changes is a uniform that hides the values it was chosen for.
    glm::vec4 nprBand{0.f};   // rgb = shadow tint, w = softness (0 = the hard step, <0 = 3-band)
    glm::vec4 nprKey{0.f};    // xyz = character key direction, w = strength
    glm::vec4 nprRim{0.f};    // rgb = rim tint, w = strength
    glm::vec4 nprSpec{0.f};   // rgb = specular tint, w = strength
    // x = how much of the generated shadow mask (F) the band curve is allowed to read.
    // Its own slot rather than a bit, because 0 (the neutral arm) has to be expressible:
    // the mask is a separate hypothesis from the curve and must not ride along with it.
    glm::vec4 nprMask{0.f};
    uint32_t  paletteOffset = 0;   // first palette matrix for this mesh
    uint32_t  flags = 0;
    uint32_t  pad[2] = {0u, 0u};
};

inline constexpr uint32_t kDrawTextured  = 1u << 0;   // sample group 2
inline constexpr uint32_t kDrawUnlit     = 1u << 1;   // skip the lambert term
inline constexpr uint32_t kDrawAlphaTest = 1u << 2;   // discard alpha < 0.5
// Read the shipped toon ramp at the diffuse term instead of the linear N.L (issue #21).
// Set per frame by SceneRenderer::fillDrawData from the appearance switch, so the toggle
// needs no re-upload; with the bit clear the shader's lighting is the fixed-function term
// bit for bit, which is what keeps the banked captures still.
inline constexpr uint32_t kDrawToon      = 1u << 3;
// Draw the inverted-hull outline instead of the surface (issue #21): the vertex stage
// offsets the clip position along the world normal and the fragment stage returns the
// flat darkened material colour. A separate draw of the same mesh, as in the original.
inline constexpr uint32_t kDrawOutline   = 1u << 4;
// This draw samples the shadow map (issue #21 row 1): the original's stage technique
// (mode 3/4, FUN_00652af0) is the only one that reads the map's alpha, and the port's
// `stage` role is its stand-in. Set per frame by SceneRenderer::fillDrawData from the
// appearance switch, so the toggle needs no re-upload; with the bit clear (and the
// shadow pass off) the fragment stage's arithmetic is the pre-change one bit for bit.
inline constexpr uint32_t kDrawShadowReceiver = 1u << 10;

// ---------------------------------------------------------------------------------------
// NPR experiment bits (issue #25). These are the switches the experiment harness adds
// ON TOP of the recovered toon technique: each one is set per draw by
// SceneRenderer::fillDrawData from Appearance, so an experiment is a draw-time state
// change with no re-upload behind it. With all of them clear the fragment shader takes
// the same branch it took before this issue existed, which is what keeps every banked
// capture byte-identical. They are NOT part of the recovered technique and carry no RE
// provenance: see foundation/docs/NPR-EXPERIMENTS.md for what each one is.
// ---------------------------------------------------------------------------------------
// xyz = draw.nprBand.rgb as the shadow tint instead of a neutral-darkened diffuse; w =
// the band softness, 0 being the hard 2-band step.
inline constexpr uint32_t kDrawNprShadow = 1u << 5;
// Shade with the secondary lighting normal (the NprVertex stream's xyz) instead of the
// geometric one. Its w, the generated shadow mask, rides the toon coordinate's free
// component instead — it is not a switch of its own: the band experiment reads it.
inline constexpr uint32_t kDrawNprNormals = 1u << 6;
// Add a character key light on top of the recovered world light (the experiment's "world
// + weak character key" mode). The key is always a second term beside the world light,
// never a replacement, so the stage's own lighting keeps anchoring the silhouette.
inline constexpr uint32_t kDrawNprKey = 1u << 7;
// Stylized specular: a hard-threshold half-vector lobe tinted by draw.nprSpec.rgb and
// scaled by draw.nprSpec.w.
inline constexpr uint32_t kDrawNprSpec = 1u << 8;
// Character-only rim light: the edge term tinted by draw.nprRim.rgb and scaled by
// draw.nprRim.w.
inline constexpr uint32_t kDrawNprRim = 1u << 9;
// (There is deliberately no bit for the outline-width experiment: the outline entry point
// reads draw.nprBand.w directly, so a bit that only ever meant "multiply by 1.0" would be
// a switch with nothing behind it.)

inline constexpr uint64_t kDrawStride = 256;          // == minUniformBufferOffsetAlignment

struct CameraUniform {
    // LH view * LH projection, used as-is: wgpu normalizes NDC to Y-up for every
    // backend, so unlike a raw Vulkan port there is NO proj[1][1] negation here.
    // Getting this wrong renders every model upside down; see tools/wgpu_smoke.cpp.
    glm::mat4 viewProj{1.f};
    glm::vec4 lightDir{0.f, -1.f, 0.f, 0.f};
    glm::vec4 lightColor{1.f};
    glm::vec4 ambient{0.25f};
    // Stage fog from env.dat: the original sets FOGTABLEMODE = LINEAR with these
    // start/end values and colour (FUN_00650a30), so this reproduces it exactly.
    glm::vec4 fogColor{0.f, 0.f, 0.f, 1.f};
    glm::vec4 fogParams{0.f, 0.f, 0.f, 0.f};   // x = start, y = end, z = enabled
    // Camera eye in world space (issue #25). The rim and stylized-specular experiments
    // need a view vector, and the viewProj alone cannot yield one; the renderer already
    // knows the eye (setEye, for effect-card billboarding) and now publishes it here too.
    // Nothing recovered reads it, so it changes no existing pixel.
    glm::vec4 eye{0.f, 0.f, 0.f, 1.f};
    // Character shadows (issue #21 row 1). `shadowViewProj` is the original's light
    // camera — FUN_006507c0:697-712 and :727-734 build it per view from a hardcoded eye
    // at (1000, 1e6, 5e5) looking at the frame camera's own eye — and `shadowParams` is
    // what the receiver's pixel shader needs from it: x = the recovered depth bias
    // (-0.02 in light NDC, effect_3's vs `c9.w`), y = the recovered depth clamp (0.95,
    // `c10.x`), z = 1 when the shadow pass ran for this view. z is 0 on every frame the
    // appearance does not ask for shadows, which is what keeps those frames' arithmetic
    // untouched. See foundation/docs/SHADOWS.md.
    glm::mat4 shadowViewProj{1.f};
    glm::vec4 shadowParams{0.f};
};

// The secondary lighting-normal stream's layout (issue #25, attribute location 6), or a
// null layout when a pipeline should not carry one. Returns by value so the caller owns
// the single-element attribute array the descriptor points at.
inline WGPUVertexBufferLayout wgpuNprVertexLayout(WGPUVertexAttribute (&attr)[1]) {
    attr[0].format = WGPUVertexFormat_Float32x4;
    attr[0].offset = 0;
    attr[0].shaderLocation = 6;
    WGPUVertexBufferLayout layout = {};
    layout.arrayStride = sizeof(NprVertex);
    layout.stepMode = WGPUVertexStepMode_Vertex;
    layout.attributeCount = 1;
    layout.attributes = attr;
    return layout;
}

// Fills `attrs` (which must hold kVertexAttributeCount entries) and returns a layout
// pointing at it. The array must outlive the pipeline-creation call.
inline WGPUVertexBufferLayout wgpuVertexLayout(WGPUVertexAttribute (&attrs)[kVertexAttributeCount]) {
    // Field-by-field: WGPUVertexAttribute has no aggregate-assignment in C++.
    struct Attr { WGPUVertexFormat format; uint64_t offset; uint32_t location; };
    const Attr spec[kVertexAttributeCount] = {
        {WGPUVertexFormat_Float32x3, offsetof(Vertex, pos),     0},
        {WGPUVertexFormat_Float32x3, offsetof(Vertex, normal),  1},
        {WGPUVertexFormat_Float32x2, offsetof(Vertex, uv),      2},
        {WGPUVertexFormat_Float32x4, offsetof(Vertex, color),   3},
        {WGPUVertexFormat_Uint32x4,  offsetof(Vertex, bones),   4},
        {WGPUVertexFormat_Float32x4, offsetof(Vertex, weights), 5},
    };
    for (uint64_t i = 0; i < kVertexAttributeCount; ++i) {
        attrs[i].format = spec[i].format;
        attrs[i].offset = spec[i].offset;
        attrs[i].shaderLocation = spec[i].location;
    }

    WGPUVertexBufferLayout layout = {};
    layout.arrayStride    = sizeof(Vertex);
    layout.stepMode       = WGPUVertexStepMode_Vertex;
    layout.attributeCount = kVertexAttributeCount;
    layout.attributes     = attrs;
    return layout;
}

}  // namespace xm
