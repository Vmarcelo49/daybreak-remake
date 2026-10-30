# EFFECTS-BLEND — ordinary effect cards use uniform additive blending

> **Scope: material/technique research for aura and event-card effects.** These
> gameplay cards now render through the foundation's `Pass::Effect`; their blend
> remains uniform because no shipped material or recovered binding supplies a
> per-card factor. In-flight projectiles are a separate path: their own models
> use the shot record's `+0x7C` selector to choose opaque/additive and lit/unlit
> modes (`FUN_005f60b0`; `ROADMAP-PENDING.md` B1). That runtime selector is not
> an `EffectInstance` material binding or an effect-card factor table.
>
> `--effect` remains a verification route. `--debug-prims` retains cube
> stand-ins; the live card/model behavior is tracked in B1 and issue #32.

This note preserves the material and technique survey behind the current uniform
`SRC_ALPHA, ONE` blend for ordinary effect cards, and distinguishes it from the
projectile record modes now consumed by `SceneRenderer`.

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
  `(0.55,0.57,0.76)` — zero elsewhere in the surveyed corpus. It is not wired as
  an additive factor. Fixed-function emissive previously blew out normally shaded
  materials (the rejected akane-face experiment); no recovered technique or
  card-to-shader binding establishes emissive as an effect-card blend control.

## Technique bindings and projectile selector

- The ten compiled shader blobs (`research/evidence/assets/shaders/effect_0..9.bin`,
  `FUN_0064ff80` "CreateAllShaders" — sizes match the decompile's `0xd6c, 0xe38,
  0x32c, …` lengths verbatim) each carry **exactly one technique**
  (`SampleTexhnique` — the original's typo, 1 occurrence per blob) with distinct
  parameter sets: `MaterialColor` in 0/1/7 only, `Alpha` in 5/6 only, `MulColor` in
  8 only. Blobs 2/3/4/9 all lack color params: 9 is `mTransform`+`Tex0` without
  light terms, 3/4 add light transforms, and 2 has no `Tex0` at all. The
  per-index→mesh-category binding is still unknown, so no factor table follows from
  this survey. Per-effect factors would therefore be per-effect-*index*
  — but **no card→effect-index mapping exists**: all 491 binary `.X` files (of the
  728-file corpus) define the `EffectInstance` template and zero instantiate it, so
  D3DX hands the reference loader an empty effect list for every asset. Nested
  `EffectInstance` children now parse into `Material::effectFile`
  (`src/assets/xmodel.h:1400-1407`), but the 728-file reload found zero shipped
  materials carrying one (`RENDER-MATERIALS.md`). No card-to-technique binding is
  established, and the foundation does not load or bind the ten blobs. The deleted
  DX9 remake's loader log is retained as history in `docs/archive/placeholders.md`
  and the frozen evidence bank, not as current renderer behavior.
- The projectile path forwards the active shot record's `combat[19]` (wire
  offset `+0x7c`) as `EffectInstance::renderMode`. The switch behind it is now read
  rather than guessed: `FUN_005f60b0` branches on that field (`:77`) and sets D3D
  state per case — case 1 sets `ALPHABLENDENABLE` (`:79`), case 3 sets it with the
  technique-8 state and an optional colour (`:91-99`), cases 2 and 4 set it with
  `DESTBLEND = ZERO` and `ZENABLE = 0` for the draw, restoring both afterwards
  (`:84-89`, `:100-109`), and `default` changes no state at all and only picks a
  technique (`:136-143`). `scene_renderer.cpp` maps that to: 2/4 → `Pass::EffectNoDepth`
  (additive, no depth test), 3/4 → unlit shading, a quad mesh inside a shot model →
  `Pass::Effect`, and a non-quad mesh in a mode 0/1/3 model stays on `Pass::Opaque`.
  No case turns blending off for the *card* surfaces, which is why the pass is additive
  for every quad (V3-35, V3-38, V3-39).
  This controls projectile model draws, not the ordinary aura/event-card factor or
  technique binding.

## Ordinary effect-card blend

The card pipeline remains color blend `SRC_ALPHA, ONE` / alpha `ONE, ONE`, unlit,
depth-test-on/write-off, cull-off (`RENDER-PASSES.md` R2). Surveyed effect textures
have alpha 255, so the color result coincides with `ONE, ONE`. A historical planted
`aura/00.X` over `stage01` check reported 0 darkened pixels out of 160000 (Δ in
[1,247]); it is a recorded result, not a current-run claim.

Per-card factors would require recovered card-to-technique binding or new evidence
from a shipped material carrying a binding. Texture-name routing remains excluded.
