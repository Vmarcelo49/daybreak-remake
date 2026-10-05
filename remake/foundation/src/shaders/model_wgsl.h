#pragma once
// Skinning + lambert shading for xm::Vertex / xm::DrawUniform, embedded in the binary
// for the same reason the demo shader is: the web build has no filesystem to load a
// .wgsl from.
//
// Bind groups, matching the contract documented in xmodel.h:
//   group 0, binding 0   Camera uniform   (xm::CameraUniform)
//   group 0, binding 1   toon ramp        (the shipped data/directX/toon.bmp, issue #21)
//   group 0, binding 2   ramp sampler     (clamp, linear)
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
  lightColor : vec4<f32>,   // rgb = light 0 Diffuse
  ambient    : vec4<f32>,   // rgb = D3DRS_AMBIENT + light 0 Ambient (already summed,
                            //       because the material multiplies the sum once), a unused
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
@group(0) @binding(1) var toonRampTex : texture_2d<f32>;
@group(0) @binding(2) var toonRampSampler : sampler;
@group(1) @binding(0) var<uniform> draw : Draw;
@group(1) @binding(1) var<storage, read> palette : array<mat4x4<f32>>;
@group(2) @binding(0) var albedoTex : texture_2d<f32>;
@group(2) @binding(1) var albedoSampler : sampler;

const FLAG_TEXTURED   : u32 = 1u;
const FLAG_UNLIT      : u32 = 2u;
const FLAG_ALPHA_TEST : u32 = 4u;
const FLAG_TOON       : u32 = 8u;

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
  // Texture stage 0 is left at its D3D9 defaults by the reference: COLOROP = MODULATE
  // over COLORARG1 = TEXTURE and COLORARG2 = DIFFUSE (the *lit* colour computed below),
  // ALPHAOP = SELECTARG1 over ALPHAARG1 = TEXTURE. So the texel multiplies the lighting
  // result and the surface alpha is the texel's. A mesh's own vertex colour therefore
  // never reaches the pixel here — it is the lighting diffuse material (see below) —
  // and an unbound stage reads white, which is why the untextured branch is 1.0.
  var albedo = select(vec4<f32>(1.0), texel, textured);

  // The original's 3D passes alpha-test against ref 0x08 with GE — the DX9 renderer
  // sets ALPHAREF 0x08 / ALPHAFUNC GE, so texels at exactly 8/255 stay. A 0.5
  // threshold here used to eat soft foliage and ground-card edges the original keeps.
  if ((draw.flags & FLAG_ALPHA_TEST) != 0u && albedo.a * 255.0 < 8.0) {
    discard;
  }

  var lit = vec3<f32>(1.0, 1.0, 1.0);
  // Both lighting inputs and the toon ramp are computed before the branch: WGSL allows
  // textureSample only where derivatives are defined (the same reason the albedo sample
  // sits above the alpha test), and the values cost nothing when the draw is unlit.
  let n = normalize(in.normal);
  let l = normalize(-cam.lightDir.xyz);
  let ndl = saturate(dot(n, l));
  // Toon ramp (issue #21). The shipped data/directX/toon.bmp read at the diffuse term:
  // u = N.L, v = 0.5 (the bitmap is constant down its columns), clamped by the sampler
  // so N.L = 1 reads the bright end instead of wrapping to the dark one. The ramp's
  // band structure comes from the bitmap alone — no constant stands in for it.
  let ramp = textureSample(toonRampTex, toonRampSampler, vec2<f32>(ndl, 0.5)).r;
  if ((draw.flags & FLAG_UNLIT) == 0u) {
    // Fixed-function D3D9 lighting, the equation the reference's state block selects
    // (remake/src/core/scenes.cpp:745-769 sets LIGHTING TRUE, D3DRS_AMBIENT 0.35 and
    // light 0 = DIRECTIONAL diffuse 0.85 / ambient 0.20 / dir (0.5,-1,0.5)):
    //
    //   lit = Ca*(Ga + La) + Cd*Ld*saturate(N.L)
    //
    // Ca is the *material* ambient: D3DRS_AMBIENTMATERIALSOURCE defaults to
    // D3DMCS_MATERIAL, and the DX9 loader forces material Ambient := Diffuse
    // (x_model_loader.cpp:432), so baseColor carries both terms. Cd is vertex colour 1,
    // because D3DRS_DIFFUSEMATERIALSOURCE defaults to D3DMCS_COLOR1 with
    // D3DRS_COLORVERTEX TRUE — the stages' baked-light vertex colours (0.03..0.29 on
    // stage21) are exactly this term, and are white on meshes that carry none.
    //
    // The placement of the vertex colour is measured, not assumed: fitting dx9/texel per
    // pixel over 83k samples of the banked frame's stage21 ground gives 0.245 where that
    // mesh's vertex colour is 0.244 (and 0.167 where it is 0.179) — the vertex colour
    // scales the diffuse term alone, not the whole lit colour and not the ambient term.
    //
    // saturate, not abs: D3D clamps N.L at 0, so a surface facing away from the light
    // keeps the ambient term alone instead of being lit at full strength.
    //
    // The toon flag swaps that saturate(N.L) for the ramp sample and nothing else: the
    // ambient term stays linear, which is what makes the two states differ only in the
    // diffuse banding the ramp carries.
    let diffuse = select(ndl, ramp, (draw.flags & FLAG_TOON) != 0u);
    lit = draw.baseColor.rgb * cam.ambient.rgb
        + in.color.rgb * cam.lightColor.rgb * diffuse;
  }

  // Emissive, specular and power stay parsed-but-unused (R4): the fixed-function
  // EMISSIVE term is a flat add to the lit colour (EMISSIVEMATERIALSOURCE = MATERIAL),
  // and wiring it blows out the character materials that carry one (rika's skin is
  // e = (0.91,0.75,0.68), which lands on top of the 0.55 ambient and clips) — see
  // docs/RENDER-MATERIALS.md. Specular stays off for the same reason the reference
  // leaves it off: D3DRS_SPECULARENABLE defaults FALSE and is never set, and the
  // light's Specular is zero-initialised (scenes.cpp:763).
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
