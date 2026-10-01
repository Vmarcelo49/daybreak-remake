#pragma once
// Skinning + lambert shading for xm::Vertex / xm::DrawUniform, embedded in the binary
// for the same reason the demo shader is: the web build has no filesystem to load a
// .wgsl from.
//
// Bind groups, matching the contract documented in xmodel.h:
//   group 0, binding 0   Camera uniform   (xm::CameraUniform)
//   group 1, binding 0   Draw uniform     (xm::DrawUniform, bound with a dynamic offset)
//   group 1, binding 1   palette storage  (one mat4x4<f32> per bone, see buildPalette)
//   group 2, binding 0   texture_2d<f32>  (1x1 white when the draw is untextured)
//   group 2, binding 1   sampler
//
// Conventions, all of them inherited from DX9 and none of them optional: the assets
// are left-handed with clockwise front faces, so the pipeline uses frontFace = cw and
// cullMode = back. The clip-space projection goes in UNCHANGED — WebGPU normalizes NDC
// to Y-up on every backend, so the Vulkan-style proj[1][1] negation a raw port reaches
// for renders every model upside down here.
namespace shaders {

inline constexpr const char* kModelWGSL = R"WGSL(
struct Camera {
  viewProj   : mat4x4<f32>,
  lightDir   : vec4<f32>,   // direction the light travels, world space
  lightColor : vec4<f32>,
  ambient    : vec4<f32>,   // rgb = ambient term, a unused
  // Stage fog straight out of env.dat: FUN_00650a30 writes D3DRS_FOGSTART/FOGEND/
  // FOGCOLOR with FOGTABLEMODE = LINEAR, so a linear ramp on view depth is the
  // original's fog, not an approximation of it. fogParams.zw: z = enabled.
  fogColor   : vec4<f32>,
  fogParams  : vec4<f32>,   // x = start, y = end, z = 1 when fog is on
};

struct Draw {
  model         : mat4x4<f32>,   // entity -> world; identity when the palette bakes it
  baseColor     : vec4<f32>,     // multiplies material diffuse and vertex colour
  paletteOffset : u32,           // index of this mesh's first palette matrix
  flags         : u32,
  _pad0         : u32,
  _pad1         : u32,
};

@group(0) @binding(0) var<uniform> cam : Camera;
@group(1) @binding(0) var<uniform> draw : Draw;
@group(1) @binding(1) var<storage, read> palette : array<mat4x4<f32>>;
@group(2) @binding(0) var albedoTex : texture_2d<f32>;
@group(2) @binding(1) var albedoSampler : sampler;

const FLAG_TEXTURED   : u32 = 1u;
const FLAG_UNLIT      : u32 = 2u;
const FLAG_ALPHA_TEST : u32 = 4u;

struct VSOut {
  @builtin(position) clip   : vec4<f32>,
  @location(0)       normal : vec3<f32>,
  @location(1)       uv     : vec2<f32>,
  @location(2)       color  : vec4<f32>,
  @location(3)       viewZ  : f32,   // view-space depth, the fog coordinate
};

@vertex
fn vs_main(
  @location(0) pos     : vec3<f32>,
  @location(1) nrm     : vec3<f32>,
  @location(2) uv      : vec2<f32>,
  @location(3) color   : vec4<f32>,
  @location(4) bones   : vec4<u32>,
  @location(5) weights : vec4<f32>,
) -> VSOut {
  let o = draw.paletteOffset;

  // Unskinned meshes carry a single-matrix palette, so this path covers both cases.
  let skin = weights.x * palette[o + bones.x]
           + weights.y * palette[o + bones.y]
           + weights.z * palette[o + bones.z]
           + weights.w * palette[o + bones.w];

  let world = draw.model * skin;

  var out : VSOut;
  out.clip   = cam.viewProj * world * vec4<f32>(pos, 1.0);
  // Uniform scale assumed; a rig with non-uniform bone scale would need the
  // inverse-transpose of the upper 3x3 here.
  out.normal = (world * vec4<f32>(nrm, 0.0)).xyz;
  out.uv     = uv;
  out.color  = color * draw.baseColor;
  // For a perspective projection the clip-space w IS the view depth, which is the
  // coordinate D3D's linear table fog uses.
  out.viewZ  = out.clip.w;
  return out;
}

@fragment
fn fs_main(in : VSOut) -> @location(0) vec4<f32> {
  // Sampled unconditionally: WebGPU requires every binding to be valid anyway, and
  // it keeps the sample out of conditional control flow.
  let texel = textureSample(albedoTex, albedoSampler, in.uv);
  let textured = (draw.flags & FLAG_TEXTURED) != 0u;
  var albedo = select(in.color, in.color * texel, textured);

  // The original's 3D passes alpha-test against ref 0x08 with GE — a very low
  // threshold, which trims foliage and ground cards without eating soft edges.
  if ((draw.flags & FLAG_ALPHA_TEST) != 0u && albedo.a < 0.5) {
    discard;
  }

  var lit = vec3<f32>(1.0, 1.0, 1.0);
  if ((draw.flags & FLAG_UNLIT) == 0u) {
    let n = normalize(in.normal);
    let l = normalize(-cam.lightDir.xyz);
    // Two-sided: DX9 meshes are not guaranteed to have outward normals after
    // skinning, and a flipped term reads as a black hole in the model.
    let ndl = abs(dot(n, l));
    lit = cam.ambient.rgb + cam.lightColor.rgb * ndl;
  }

  var shaded = albedo.rgb * lit;
  if (cam.fogParams.z > 0.5) {
    let span = max(cam.fogParams.y - cam.fogParams.x, 1e-3);
    let f = clamp((cam.fogParams.y - in.viewZ) / span, 0.0, 1.0);
    shaded = mix(cam.fogColor.rgb, shaded, f);
  }
  return vec4<f32>(shaded, albedo.a);
}
)WGSL";

}  // namespace shaders
