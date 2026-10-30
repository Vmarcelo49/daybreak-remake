#pragma once
// World-space debug line list, embedded in the binary for the same reason the model
// and UI shaders are: the web build has no filesystem to load a .wgsl from.
//
// Bind groups:
//   group 0, binding 0   camera uniform (one mat4x4<f32>: the viewProj the caller
//                        already handed to SceneRenderer::setCamera)
//
// Conventions, and why they are what they are:
//   * Topology is line-list — two vertices per segment, no index buffer, no strips.
//     WebGPU has no line-width state: every line rasterises one physical pixel wide
//     on every backend. That is what makes a debug overlay readable, and it is also
//     why this pipeline exposes no width option.
//   * The vertex colour attribute is a raw u32 holding D3DCOLOR (0xAARRGGBB), which
//     is exactly the value a DX9 call site already passes to D3DFVF_DIFFUSE. The
//     shader unpacks it with shifts, so no host-side swizzle and no endianness
//     assumption is involved. The result is Gouraud-interpolated, as D3DFVF_DIFFUSE
//     is under DX9.
//   * The clip-space projection goes in UNCHANGED, like model_wgsl.h: WebGPU
//     normalizes NDC to Y-up with a 0..1 depth range on every backend, which is what
//     glm::perspectiveLH_ZO already produces, so no proj[1][1] negation belongs here.
namespace shaders {

inline constexpr const char* kDebugLineWGSL = R"WGSL(
struct DebugCamera {
  viewProj : mat4x4<f32>,
};

@group(0) @binding(0) var<uniform> camera : DebugCamera;

struct VSOut {
  @builtin(position) clip  : vec4<f32>,
  @location(0)       color : vec4<f32>,
};

@vertex
fn vs_main(
  @location(0) pos    : vec3<f32>,
  @location(1) packed : u32,
) -> VSOut {
  var out : VSOut;
  // No model matrix: the DX9 debug pass forces D3DTS_WORLD to identity so callers can
  // pass world-space centres, and the same convention holds here by construction.
  out.clip = camera.viewProj * vec4<f32>(pos, 1.0);
  // D3DCOLOR is 0xAARRGGBB and the vertex attribute is read little-endian, so the
  // shifts below reproduce D3DCOLOR's channel order on every backend. Keep in sync
  // with render::unpackColor (debug_prims.h), which mirrors this for CPU callers.
  out.color = vec4<f32>(
    f32((packed >> 16u) & 0xFFu),
    f32((packed >>  8u) & 0xFFu),
    f32( packed        & 0xFFu),
    f32((packed >> 24u) & 0xFFu)
  ) / 255.0;
  return out;
}

@fragment
fn fs_main(in : VSOut) -> @location(0) vec4<f32> {
  return in.color;
}
)WGSL";

}  // namespace shaders
