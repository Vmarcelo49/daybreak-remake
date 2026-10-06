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
  // World-space camera eye (issue #25): the rim and stylized-specular experiments need a
  // view vector, which a viewProj cannot be decomposed into cheaply per fragment.
  eye        : vec4<f32>,
};

struct Draw {
  model         : mat4x4<f32>,   // entity -> world; identity when the palette bakes it
  baseColor     : vec4<f32>,     // multiplies material diffuse and vertex colour
  emissive      : vec4<f32>,     // the material's Emissive, the toon effect's MaterialColor
  // NPR experiment parameters (issue #25), one slot per experiment: rgb is the colour it
  // tints with and w its strength (or, for the band, the curve's softness). Zero on an
  // unmodified renderer, so every branch below that reads them is dead there.
  nprBand       : vec4<f32>,
  nprKey        : vec4<f32>,
  nprRim        : vec4<f32>,
  nprSpec       : vec4<f32>,
  nprMask       : vec4<f32>,   // x = scale on the generated shadow mask (issue #25, F)
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
// NPR experiment bits (issue #25). Nothing here is recovered: these are the switches the
// experiment harness adds on top of the recovered toon technique, all off by default.
const FLAG_NPR_SHADOW  : u32 = 32u;    // nprBand.rgb tints the shadow band
const FLAG_NPR_NORMALS : u32 = 64u;    // light the secondary normal, bias by its mask
const FLAG_NPR_KEY     : u32 = 128u;   // add the character key light term
const FLAG_NPR_SPEC    : u32 = 256u;   // stylized hard-threshold specular
const FLAG_NPR_RIM     : u32 = 512u;   // character-only rim light

// The band edges are experiment constants, not uniforms: they were fixed across the whole
// grid below and a value that never changes belongs next to the code that reads it.
const BAND_LO    : f32 = 0.25;   // the 3-band arm's lower edge
const BAND_MID   : f32 = 0.50;   // the 2-band terminator
const BAND_BIAS  : f32 = 0.22;   // how far the generated mask may move an edge
const BAND_CORE  : f32 = 0.55;   // how much tint survives under the lower edge
const NPR_RIM_POW : f32 = 2.0;
const NPR_RIM_BOOST : f32 = 1.6;

struct VSOut {
  @builtin(position) clip   : vec4<f32>,
  @location(0)       normal : vec3<f32>,
  @location(1)       uv     : vec2<f32>,
  @location(2)       color  : vec4<f32>,
  @location(3)       viewZ  : f32,   // view-space depth, the fog coordinate
  // x = toon ramp coordinate (object-space N.L, issue #21), y = the generated
  // shadow-threshold mask (issue #25), interpolated across the triangle.
  @location(4)       toonU  : vec2<f32>,
  @location(5)       wpos   : vec3<f32>,  // world-space position (the view vector's tail)
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
  // The toon ramp coordinate (issue #21): `min(max(N.L, 0), 1)` with the light direction
  // BAKED IN as the constant (0, 0.287347883, 0.957826257) and the *object-space* normal
  // (the shader's `dp3 r0.x, v1, c9`), so the banding follows the character's own facing
  // rather than the world light the fixed-function path uses. The second component is the
  // generated shadow mask (issue #25) and is a literal 0 here: this entry point is the one
  // every pre-#25 capture was made with, and it must not change.
  out.toonU = vec2<f32>(saturate(dot(nrm, vec3<f32>(0.0, 0.287347883, 0.957826257))), 0.0);
  if ((draw.flags & FLAG_OUTLINE) != 0u) {
    // Outline hull (issue #21). The original's outline pass offsets the clip position
    // along the world normal's x/y, scaled by the clip-space w, which makes the rim a
    // constant screen width after the perspective divide: 0.00275 and 0.00366666657 NDC
    // are 0.011/4 and 0.011/3, i.e. the same ~1.1 px at the original's 800x600 canvas.
    // The 1e-6*w z push keeps the hull behind the model it surrounds, so the model's own
    // depth wins everywhere except the rim that sticks out past the silhouette.
    // The issue #25 outline-width experiment (I) scales both xy offsets by
    // draw.nprBand.w, which is 1.0 on every draw that did not ask for it, and leaves the
    // z push exactly as recovered so a scaled rim is still behind the model. The scale is
    // folded into the constant rather than applied after it: `* 0.00275 * 1.0` is not the
    // same instruction as `* 0.00275` on this driver, and the difference showed up in the
    // OFF frame's bytes.
    let scale = draw.nprBand.w;
    let wn = normalize((world * vec4<f32>(nrm, 0.0)).xyz);
    out.clip = vec4<f32>(clip.x + wn.x * clip.w * (0.00275 * scale),
                         clip.y + wn.y * clip.w * (0.00366666657 * scale),
                         clip.z + clip.w * 0.000001,
                         clip.w);
  } else {
    out.clip = clip;
  }
  // Uniform scale assumed; a rig with non-uniform bone scale would need the
  // inverse-transpose of the upper 3x3 here.
  out.normal = (world * vec4<f32>(nrm, 0.0)).xyz;
  out.wpos   = (world * vec4<f32>(pos, 1.0)).xyz;
  out.uv     = uv;
  out.color  = color * draw.baseColor;
  // For a perspective projection the clip-space w IS the view depth, which is the
  // coordinate D3D's linear table fog uses. The outline branch keeps w, so this stays
  // the same depth for both draws of one mesh.
  out.viewZ  = out.clip.w;
  return out;
}

@vertex
fn vs_npr(
  @location(0) pos     : vec3<f32>,
  @location(1) nrm     : vec3<f32>,
  @location(2) uv      : vec2<f32>,
  @location(3) color   : vec4<f32>,
  @location(4) bones   : vec4<u32>,
  @location(5) weights : vec4<f32>,
  @location(6) nprNrm  : vec4<f32>,
) -> VSOut {
  let o = draw.paletteOffset;

  // Unskinned meshes carry a single-matrix palette, so this path covers both cases.
  let skin = weights.x * palette[o + bones.x]
           + weights.y * palette[o + bones.y]
           + weights.z * palette[o + bones.z]
           + weights.w * palette[o + bones.w];

  let world = draw.model * skin;
  let clip  = cam.viewProj * world * vec4<f32>(pos, 1.0);
  // The secondary lighting normal (issue #25, E). (0,0,0,0) is "this mesh has no such
  // normal", which is every mesh whose role the experiments do not cover; its w is the
  // generated shadow mask (F).
  let haveNpr = (draw.flags & FLAG_NPR_NORMALS) != 0u &&
                dot(nprNrm.xyz, nprNrm.xyz) > 0.25;
  let nprNrmUse = select(nrm, nprNrm.xyz, haveNpr);

  var out : VSOut;
  // Toon ramp coordinate (issue #21). The original's toon effect computes it in its own
  // vertex shader as `min(max(N.L, 0), 1)` with the light direction BAKED IN as the
  // constant (0, 0.287347883, 0.957826257) and the *object-space* normal (the shader's
  // `dp3 r0.x, v1, c9`), so the banding follows the character's own facing rather than
  // the world light the fixed-function path uses.
  // The toon ramp coordinate (issue #21): `min(max(N.L, 0), 1)` with the light direction
  // BAKED IN as the constant (0, 0.287347883, 0.957826257) and the *object-space* normal
  // (the shader's `dp3 r0.x, v1, c9`), so the banding follows the character's own facing
  // rather than the world light the fixed-function path uses. The second component is the
  // generated shadow mask (issue #25) and is a literal 0 here: this entry point is the one
  // every pre-#25 capture was made with, and it must not change.
  out.toonU = vec2<f32>(saturate(dot(nrm, vec3<f32>(0.0, 0.287347883, 0.957826257))),
                        select(0.0, nprNrm.w, haveNpr));
  if ((draw.flags & FLAG_OUTLINE) != 0u) {
    // Outline hull (issue #21). The original's outline pass offsets the clip position
    // along the world normal's x/y, scaled by the clip-space w, which makes the rim a
    // constant screen width after the perspective divide: 0.00275 and 0.00366666657 NDC
    // are 0.011/4 and 0.011/3, i.e. the same ~1.1 px at the original's 800x600 canvas.
    // The 1e-6*w z push keeps the hull behind the model it surrounds, so the model's own
    // depth wins everywhere except the rim that sticks out past the silhouette.
    // The issue #25 outline experiment (I) scales both xy offsets by draw.nprBand.w and
    // leaves the z push exactly as recovered, so a scaled rim is still behind the model.
    let scale = draw.nprBand.w;
    let wn = normalize((world * vec4<f32>(nrm, 0.0)).xyz);
    out.clip = vec4<f32>(clip.x + wn.x * clip.w * (0.00275 * scale),
                         clip.y + wn.y * clip.w * (0.00366666657 * scale),
                         clip.z + clip.w * 0.000001,
                         clip.w);
  } else {
    out.clip = clip;
  }
  // Uniform scale assumed; a rig with non-uniform bone scale would need the
  // inverse-transpose of the upper 3x3 here.
  out.normal = (world * vec4<f32>(nprNrmUse, 0.0)).xyz;
  out.wpos   = (world * vec4<f32>(pos, 1.0)).xyz;
  out.uv     = uv;
  out.color  = color * draw.baseColor;
  // For a perspective projection the clip-space w IS the view depth, which is the
  // coordinate D3D's linear table fog uses. The outline branch keeps w, so this stays
  // the same depth for both draws of one mesh.
  out.viewZ  = out.clip.w;
  return out;
}

// The banding curve the issue #25 experiments select (B: toon threshold / ramp). One
// shape, three parameter sets, so the captures differ only in the curve:
//   softness 0    -> a hard step at the edge (the hard 2-band read)
//   softness > 0  -> a short smoothstep across [edge - softness, edge + softness]
// `bias` is the generated per-vertex shadow mask (F): positive pushes the surface
// towards light, negative towards shadow, which is what lets a region hold its band
// through an extreme pose without touching the mesh.
fn nprBandWeight(ndl : f32, edge : f32, softness : f32, bias : f32) -> f32 {
  let e = clamp(edge + bias, 0.0, 1.0);
  if (softness > 0.0) {
    return smoothstep(e - softness, e + softness, ndl);
  }
  return select(0.0, 1.0, ndl >= e);
}

// The third band's own factor (B's 3-band arm): 1 everywhere the surface is lit, falling
// to BAND_CORE below the lower edge. It multiplies the DIFFUSE term, not the tint weight:
// scaling a weight that is already 0 in the shadow does nothing at all, which is what the
// first two attempts at this arm measured (identical frame, byte for byte). A second band
// is a darker SHADOW, so it has to scale the thing that is not already zero.
fn nprBandCore(ndl : f32, edgeLow : f32, softness : f32, bias : f32) -> f32 {
  let e2 = clamp(edgeLow + bias, 0.0, 1.0);
  if (softness > 0.0) {
    return BAND_CORE + (1.0 - BAND_CORE) * smoothstep(e2 - softness, e2 + softness, ndl);
  }
  return select(BAND_CORE, 1.0, ndl >= e2);
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
  let ramp = textureSample(toonRampTex, toonRampSampler, vec2<f32>(in.toonU.x, 0.5)).r;

  // The experiment bits are read once here; `nprAny` is what keeps the unmodified path
  // bit-for-bit the arithmetic it always was.
  let nprShadow  = (draw.flags & FLAG_NPR_SHADOW) != 0u;
  let nprKey     = (draw.flags & FLAG_NPR_KEY) != 0u;
  let nprSpec    = (draw.flags & FLAG_NPR_SPEC) != 0u;
  let nprRim     = (draw.flags & FLAG_NPR_RIM) != 0u;
  let nprAny     = nprShadow || nprKey || nprSpec || nprRim;

  var lit = vec3<f32>(1.0, 1.0, 1.0);
  if ((draw.flags & FLAG_UNLIT) == 0u) {
    if ((draw.flags & FLAG_TOON) != 0u && !nprAny) {
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
      // PORT RULE (issue #25): when an NPR experiment is active on the same draw the
      // experiment's own band function replaces this term. The recovered technique is not
      // edited — the guard above is the whole interaction — and a capture with no --npr
      // flag never reaches the branch below.
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
      let ambient = draw.baseColor.rgb * cam.ambient.rgb;
      var diffuse = in.color.rgb * cam.lightColor.rgb * ndl;
      // Character key light (D, issue #25). A second lambert term from the character's
      // own direction, added at draw.nprBand.w strength: the world light still carries
      // the frame, the key only holds the face and the silhouette readable as the fighter
      // turns away from it. Deliberately an ADD rather than a replacement — the "world
      // light only" arm of the experiment is simply this term absent.
      if (nprKey) {
        diffuse = diffuse + in.color.rgb * cam.lightColor.rgb *
                            saturate(dot(n, draw.nprKey.rgb)) * draw.nprKey.w;
      }
      if (nprShadow) {
        // Colored shadows (C, issue #25): only the DIFFUSE side is tinted, and only the
        // part the band function sends to shadow. Tinting the whole lit colour (the
        // classic `shadow = base * 0.4` this experiment exists to replace) would drag the
        // ambient term with it and grey out whites; tinting the diffuse alone keeps the
        // world light's structure and shifts just the shadowed side's hue.
        //
        // draw.nprBand.w carries the softness for the 2-band arms and the softness
        // NEGATED for the 3-band arm, which is how one float selects both the curve and
        // whether there is a second edge (see fillDrawData).
        let soft = abs(draw.nprBand.w);
        let bias = (in.toonU.y - 0.5) * BAND_BIAS * draw.nprMask.x;
        let w = nprBandWeight(ndl, BAND_MID, soft, bias);
        diffuse = diffuse * mix(draw.nprBand.rgb, vec3<f32>(1.0), w);
        if (draw.nprBand.w < 0.0) {
          diffuse = diffuse * nprBandCore(ndl, BAND_LO, soft, bias);
        }
      }
      lit = ambient + diffuse;
      // Rim light (H, issue #25): a fresnel edge on the character alone. `1 - |n.v|`
      // rather than `1 - n.v` so the term reads on both facings — a rim that only lights
      // the light side cannot separate a silhouette that is turned away.
      if (nprRim) {
        let v = normalize(cam.eye.xyz - in.wpos);
        let fres = pow(1.0 - abs(dot(n, v)), NPR_RIM_POW);
        lit = lit + in.color.rgb * cam.lightColor.rgb * draw.nprRim.rgb *
                    (fres * draw.nprRim.w * NPR_RIM_BOOST);
      }
      // Stylized specular (G, issue #25): a hard-threshold half-vector lobe instead of a
      // physically-shaped highlight, so the highlight has a drawn edge and a fixed size
      // rather than sliding and shrinking with the view. From the toon-shading literature,
      // not from the original: the reference never enables D3DRS_SPECULARENABLE (R4).
      if (nprSpec) {
        let v = normalize(cam.eye.xyz - in.wpos);
        let h = normalize(l + v);
        let s = saturate(dot(n, h));
        let high = smoothstep(0.86, 0.92, s) * step(0.001, ndl);
        lit = lit + draw.nprSpec.rgb * high * draw.nprSpec.w;
      }
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
