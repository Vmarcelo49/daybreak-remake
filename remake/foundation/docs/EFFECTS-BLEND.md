# EFFECTS-BLEND — per-effect factors: surveyed, not wired; uniform additive kept

No owned files changed. Per the track order (per-effect blend factors driven by
parsed material/technique data *where it exists*; otherwise say so and keep the
current path), this records what was surveyed and why `SRC_ALPHA, ONE` stays
uniform.

## The parsed material data has no blend signal

Full material survey of the shipped effect/aura corpus (`/tmp` probe linking the
foundation parser; texture names below SJIS-decoded where ASCII):

- **Diffuse is `(1,1,1,1)` on every effect/aura material** — zero alpha variation,
  zero tint. There is no per-card opacity or color factor to drive anything with.
  (Diffuse already rides `DrawUniform.baseColor` per R1; it just never varies here.)
- Specular is `0` or `(0.05,0.05,0.05)` (`aura/06.x` is `(1,1,1)` but untextured —
  outlier geometry, not a factor). Power is `0` except `aura/03.X` (0.3) and one
  `hit2.X` material (3.2). Neither is a blend factor; R4 already keeps both
  parsed-but-unused because the DX9 reference never enables specular either.
- **Emissive is the only term that varies per card**: `aura/03.X (1,1,1)`,
  `aura/04.X (0.40,0.47,0.67)`, `effect/08.X (0.94,0.63,0.47)`, `hit2.X` mat 3
  `(0.55,0.57,0.76)` — zero everywhere else. It is *not* wired, for the R4 reason:
  wiring emissive as the fixed-function flat add blew out materials the original
  shades normally (akane's face, emissive ≈ skin tone → featureless white, 39821
  px in the rejected `/tmp` experiment). On the unlit Effect pass emissive could
  plausibly scale the additive term — but no technique data says so, and the DX9
  reference path (which does feed `MatD3D` emissive to FFP) draws these cards
  opaque-alpha-tested, not additive, so there is no consistent reference to copy.
  Mapping emissive → blend factor would be invention with a known-bad precedent.

## The technique data does not exist on either path

- The 10 compiled effects (`remake/assets/shaders/effect_0..9.bin`,
  `FUN_0064ff80` "CreateAllShaders" — sizes match the decompile's `0xd6c, 0xe38,
  0x32c, …` lengths verbatim) each carry **exactly one technique**
  (`SampleTexhnique` — the original's typo, 1 occurrence per blob) with distinct
  parameter sets: `MaterialColor` (0/1/7), `Alpha` (5/6), `MulColor` (8), bare
  `mTransform+Tex0` (9). Per-effect factors would therefore be per-effect-*index*
  — but **no card→effect-index mapping exists in any parsed data**: all 491
  shipped `.X` files define the `EffectInstance` template and zero instantiate
  it (RENDER-MATERIALS.md survey), so D3DX hands the reference loader an empty
  effect list for every asset, and the foundation parser drops nested instances
  before the renderer could ever see them (parent-owned asset layer).
- The DX9 remake receives `pEffectInstances` in `create_mesh_container` and only
  **logs** the filename; it never calls `SetTechnique`/`BeginPass` (no occurrences
  in `remake/src/`). Technique binding is unimplemented on both paths — the "10
  compiled effect shaders" are loaded (`EffectSystem`) and never bound.

## What stays

The Effect pipeline remains blend `SRC_ALPHA, ONE` / alpha `ONE, ONE`, unlit,
depth-test-on/write-off, cull-off for every effect card (RENDER-PASSES.md R2),
with the planted-frame monotonicity re-verified this session: a billboarded
`aura/00.X` over `stage01` darkens **0 of 160000 px** (Δ ∈ [1,247]).

## What would unblock per-effect factors (all parent-owned or RE)

1. Asset layer parses nested `MeshMaterialList`-level `EffectInstance` children
   into `Material` (filename + params) — the R1 follow-up already reported to the
   parent — *and* a shipped asset carrying one is found (none observed to date).
2. RE maps effect-blob index → mesh category (which of the 10 effects draws
   which cards) and decodes each blob's pass states at `FUN_0064ff80`'s callers.
3. A renderer-side factor table keyed on that binding, verified against a DX9 /
   original frame — not against heuristics. Texture-name routing stays
   deliberately excluded regardless.
