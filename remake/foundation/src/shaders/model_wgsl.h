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
  emissive      : vec4<f32>,     // the material's Emissive, the toon effect's MaterialColor
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
const FLAG_OUTLINE    : u32 = 16u;

struct VSOut {
  @builtin(position) clip   : vec4<f32>,
  @location(0)       normal : vec3<f32>,
  @location(1)       uv     : vec2<f32>,
  @location(2)       color  : vec4<f32>,
  @location(3)       viewZ  : f32,   // view-space depth, the fog coordinate
  @location(4)       toonU  : f32,   // toon ramp coordinate, object-space N.L (issue #21)
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
  let clip  = cam.viewProj * world * vec4<f32>(pos, 1.0);

  var out : VSOut;
  // Toon ramp coordinate (issue #21). The original's toon effect computes it in its own
  // vertex shader as `min(max(N.L, 0), 1)` with the light direction BAKED IN as the
  // constant (0, 0.287347883, 0.957826257) and the *object-space* normal (the shader's
  // `dp3 r0.x, v1, c9`), so the banding follows the character's own facing rather than
  // the world light the fixed-function path uses.
  out.toonU = saturate(dot(nrm, vec3<f32>(0.0, 0.287347883, 0.957826257)));
  if ((draw.flags & FLAG_OUTLINE) != 0u) {
    // Outline hull (issue #21). The original's outline pass offsets the clip position
    // along the world normal's x/y, scaled by the clip-space w, which makes the rim a
    // constant screen width after the perspective divide: 0.00275 and 0.00366666657 NDC
    // are 0.011/4 and 0.011/3, i.e. the same ~1.1 px at the original's 800x600 canvas.
    // The 1e-6*w z push keeps the hull behind the model it surrounds, so the model's own
    // depth wins everywhere except the rim that sticks out past the silhouette.
    let wn = normalize((world * vec4<f32>(nrm, 0.0)).xyz);
    out.clip = vec4<f32>(clip.x + wn.x * clip.w * 0.00275,
                         clip.y + wn.y * clip.w * 0.00366666657,
                         clip.z + clip.w * 0.000001,
                         clip.w);
  } else {
    out.clip = clip;
  }
  // Uniform scale assumed; a rig with non-uniform bone scale would need the
  // inverse-transpose of the upper 3x3 here.
  out.normal = (world * vec4<f32>(nrm, 0.0)).xyz;
  out.uv     = uv;
  out.color  = color * draw.baseColor;
  // For a perspective projection the clip-space w IS the view depth, which is the
  // coordinate D3D's linear table fog uses. The outline branch keeps w, so this stays
  // the same depth for both draws of one mesh.
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

  // Outline hull (issue #21): a flat colour and nothing else. The original's outline
  // pass has NO pixel shader at all — its vertex shader writes the interpolated diffuse
  // from a preshader that computed `MaterialColor * 0.285714286` — so the texture, the
  // alpha test, the lighting and the fog never touch it. 0.285714286 is 2/7, the
  // preshader's own constant (blob +0x934: `mul c5.xyz, (0.285714286, ...), c0.xyz`),
  // and MaterialColor is the material's Emissive: the shipped character materials carry
  // tinted values there (measured rim colours on rena's bind pose imply emissives from
  // ~0.30 to ~0.92 per channel), so the outline is a dark rim tinted by the material it
  // surrounds rather than a pure black one.
  if ((draw.flags & FLAG_OUTLINE) != 0u) {
    return vec4<f32>(draw.emissive.rgb * 0.285714286, draw.emissive.a);
  }

  // The original's 3D passes alpha-test against ref 0x08 with GE — the DX9 renderer
  // sets ALPHAREF 0x08 / ALPHAFUNC GE, so texels at exactly 8/255 stay. A 0.5
  // threshold here used to eat soft foliage and ground-card edges the original keeps.
  if ((draw.flags & FLAG_ALPHA_TEST) != 0u && albedo.a * 255.0 < 8.0) {
    discard;
  }

  // The shipped toon ramp, sampled unconditionally for the same uniform-control-flow
  // reason the albedo is (and it costs nothing on a draw that does not read it).
  let ramp = textureSample(toonRampTex, toonRampSampler, vec2<f32>(in.toonU, 0.5)).r;

  var lit = vec3<f32>(1.0, 1.0, 1.0);
  if ((draw.flags & FLAG_UNLIT) == 0u) {
    if ((draw.flags & FLAG_TOON) != 0u) {
      // The original's toon pixel shader (ps_1_1, effect blob +0x4d0) is
      //
      //   tex t0 / tex t1 / tex t2
      //   cnd r1, .., c0, c0        ; r1 = 0.1
      //   sub r0, v0, r1            ; MaterialColor - 0.1
      //   add_sat r0, t1, r0        ; + the ramp sample at (N.L, 0.5)
      //   mul r0, t0, r0            ; * the albedo
      //
      // i.e. albedo * saturate(ramp + materialEmissive - 0.1), with t1 bound to the
      // shipped data/directX/toon.bmp (the technique's "Tex1" parameter, which only the
      // effect-based modes ever set — the plain mode never touches the ramp) and
      // MaterialColor being the material's Emissive (D3DMATERIAL9 +0x30). There is no
      // ambient term, no light colour and no vertex colour in this path: the effect
      // carries its own lighting, and the ramp is its only N.L term.
      lit = saturate(vec3<f32>(ramp) + draw.emissive.rgb - vec3<f32>(0.1));
    } else {
      let n = normalize(in.normal);
      let l = normalize(-cam.lightDir.xyz);
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
      // The placement of the vertex colour is measured, not assumed: fitting dx9/texel
      // per pixel over 83k samples of the banked frame's stage21 ground gives 0.245 where
      // that mesh's vertex colour is 0.244 (and 0.167 where it is 0.179) — the vertex
      // colour scales the diffuse term alone, not the whole lit colour and not the
      // ambient term.
      //
      // saturate, not abs: D3D clamps N.L at 0, so a surface facing away from the light
      // keeps the ambient term alone instead of being lit at full strength. This branch
      // is the state every banked capture was made in and must stay bit for bit.
      let ndl = saturate(dot(n, l));
      lit = draw.baseColor.rgb * cam.ambient.rgb
          + in.color.rgb * cam.lightColor.rgb * ndl;
    }
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
