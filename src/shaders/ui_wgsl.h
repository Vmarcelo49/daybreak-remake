#pragma once
// Pixel-space textured quads for the 2D/UI pass, embedded in the binary for the
// same reason the model shader is: the web build has no filesystem to load a
// .wgsl from.
//
// Bind groups:
//   group 0, binding 0   viewport uniform (UiViewport: surface size in pixels)
//   group 1, binding 0   texture_2d<f32>  (RGBA8 sprite, font atlas, or 1x1 white)
//   group 1, binding 1   sampler
//
// Conventions, all inherited from the DX9 2D path and none optional:
//   * Positions are viewport pixels with a top-left origin and y down — exactly
//     the XYZRHW convention ui_image.cpp and hud.cpp draw in — so HUD constants
//     recorded from the DX9 reference transfer verbatim. The vertex shader maps
//     them to NDC itself (WebGPU NDC is y-up on every backend, hence the flip).
//   * One texture format everywhere (RGBA8Unorm): sprite images, the font atlas
//     (white with coverage in alpha) and the 1x1 white solid fallback. A single
//     pipeline therefore draws bars, sprites and glyphs, and text needs no OS
//     font on any target.
//   * Blending is SrcAlpha/OneMinusSrcAlpha, set on the pipeline, matching
//     D3DXSPRITE_ALPHABLEND (hud.cpp begin) and the UIImage quad path. The UI
//     pass loads — never clears — the 3D frame, so it composes rather than
//     replaces it.
namespace shaders {

inline constexpr const char* kUiWGSL = R"WGSL(
struct UiViewport {
  size : vec2f,
};

@group(0) @binding(0) var<uniform> vp : UiViewport;
@group(1) @binding(0) var quadTex : texture_2d<f32>;
@group(1) @binding(1) var quadSampler : sampler;

struct VSOut {
  @builtin(position) clip  : vec4f,
  @location(0)       uv    : vec2f,
  @location(1)       color : vec4f,
};

@vertex
fn vs_main(
  @location(0) pos   : vec2f,
  @location(1) uv    : vec2f,
  @location(2) color : vec4f,
) -> VSOut {
  var out : VSOut;
  let ndc = vec2f(pos.x / vp.size.x * 2.0 - 1.0, 1.0 - pos.y / vp.size.y * 2.0);
  out.clip = vec4f(ndc, 0.0, 1.0);
  out.uv = uv;
  out.color = color;
  return out;
}

@fragment
fn fs_main(in : VSOut) -> @location(0) vec4f {
  // Sampled unconditionally: WebGPU requires every binding to be valid, and the
  // 1x1 white fallback makes a solid quad sample to exactly the tint colour.
  let texel = textureSample(quadTex, quadSampler, in.uv);
  return texel * in.color;
}
)WGSL";

}  // namespace shaders
