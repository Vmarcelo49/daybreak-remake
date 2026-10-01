# R1 material routing + R4 material fidelity — what the renderer does now

Owned files changed: `src/render/scene_renderer.{h,cpp}`, `src/shaders/model_wgsl.h`.
Nothing outside `src/render/*`, `src/shaders/model*.h` was edited.

## R1 — the technique signal was surveyed, not assumed

The provisional shadow-name heuristic (`shadow*` + 影) is kept, and is now labeled
provisional at its definition site, because the survey below shows the real signal
is structurally absent from shipped assets — there is nothing to replace the
heuristic *with* yet.

Evidence (token-level scan of every shipped `.X`, `/tmp` probe, repo untouched):

- All 491 binary `.X` files define the `EffectInstance` template (exporter
  boilerplate, alongside `FVFData`); **zero instantiate it**. No text `.X`
  mentions it either. So D3DX would hand the reference loader an empty
  `pEffectInstances` list for every shipped asset — consistent with the DX9
  loader's effect-filename log never having fired anywhere in the recorded docs.
- The foundation text parser could not have reported it anyway: nested template
  instances consumed as member refs are silently dropped by the binary→text
  converter, and nested `EffectInstance` children are skipped without setting even
  the `hadEffectInstance` flag (it only fires at top level, where instances never
  appear). Both halves of that are asset-layer (`src/assets/`) behavior, i.e.
  parent-owned; the render side cannot see effect bindings until that lands.

What the renderer *did* change for R1: route on the real per-material signals it
can already see. Material diffuse now rides `DrawUniform.baseColor` (previously
dropped — everything shaded white). Observed tinted materials (174/4758) all live
in non-drawn collision meshes, so this changes zero capture pixels; it is wired
because it is the D3DX `faceColor` path, not a heuristic.

Landed as `Material::effectFile`: nested `EffectInstance` children parse into the
material (filename + stats flag) in `readMaterialBody`, covering both named and
inline materials. Verified with a synthetic instance (`glow.fx` lands, texture
untouched) and a full 728-file corpus reload (0 failures, 0 shipped materials
carry one — the survey result stands). Routing deliberately unchanged: with no
shipped instance to key on, `classifyPass()` keeps its current signals until an
asset actually carries an effect file.

## R4 — terms wired only with observed justification

Corpus survey (all 728 `.X`, 4758 materials): diffuse alpha < 1 nowhere;
specular sum > 0.3 in 171; power ≠ 0 in 80; emissive sum > 0.3 in 1268 (27%) —
all emissive on characters/weapons (`akane/00.X` face `e=(0.91,0.75,0.68)`,
`item/24.X` `e=(1,1,1)`), zero on stages.

- **Diffuse: wired** (see above). Zero capture impact, proven-correct path.
- **Emissive/specular/power: deliberately parsed-but-unused.** Wiring emissive as
  the fixed-function flat add was tried in a `/tmp`-only build and rejected on
  observed pixels: akane's face (emissive ≈ skin tone, authored shaded) blew out
  to featureless white, 39821 px changed. The original shades that material
  normally, so the term belongs to the effect-technique binding (R1), not to the
  FFP equation. Specular stays off for the same reason the DX9 reference leaves
  it off (`SPECULARENABLE` is never enabled there) plus power ≈ 0 almost
  everywhere. The shader now says so in two lines at the term.
- **Mipmaps: not added.** The sampler advertises `Nearest` on a single level,
  unchanged. Minification aliasing without mips is real, but adding mips moves
  every minified pixel with no original/DX9 frame to validate against — the
  exact unproven-gain case the track rules exclude. Revisit with a reference frame.
- **Alpha-test threshold: corrected 0.5 → 8/255 (GE semantics kept).** The old
  0.5 had no provenance (the shader comment itself described the original's
  `0x08`/GE); the in-tree DX9 reference sets `ALPHAREF 0x08` / `ALPHAFUNC GE` in
  *two* places — the asset viewer (`x_model_renderer.cpp`) and the actual
  gameplay scene (`scenes.cpp`). Effect on captures: stage01 9636 px (6.02%,
  max Δ99) confined to foliage/ground-card soft edges the artist authored with
  alpha in (0.03, 0.5); stage21 1082 px (0.68%, max Δ21); akane 88 px (0.06%);
  weapon and lone-effect captures byte-identical. Direction matches the DX9
  reference in every case.

## Verification (all `/tmp` builds, repo `build/` untouched)

```bash
cp -a remake/foundation /tmp/fcheck   # minus build/; cmake -B /tmp/fcheck/build/linux; build
remake/foundation/build/linux/foundation_demo --stage=<data>/stage01 \
  --out=/tmp/rprobe/s01_old.ppm --size=400        # pre-change binary, still pristine
/tmp/fcheck/build/linux/foundation_demo --stage=<data>/stage01 \
  --out=/tmp/rprobe/s01_new.ppm --size=400
# akane :0, stage21, item/05.X, effect/01.X likewise; PIL ImageChops.difference
```

Linux-new vs Windows/Wine-new (MinGW cross-build in `/tmp/fwin`, run under Wine):
**byte-identical** on stage01 and akane (0 px). Web target compiles
(`emcmake` + build ok); web *runtime* not executed this session.

## Not verified

- No original-exe or DX9-remake pixel comparison anywhere in R1/R4 (no DX9 run
  in this session); the alpha-ref correction is validated against the in-tree
  DX9 reference states + authored-alpha reasoning, not against a DX9 frame.
- EffectInstance instances: absent in all surveyed assets, but bzip payloads were
  only checked post-decode via the parser (no converted-text hits), not at token
  level — a perverse packing could hide one; unlikely, stated for completeness.
- Stale comment in parent-owned `src/assets/cnv.h` (`keyOutWhite` docs say the
  WebGPU path presents decals "without a stencil" — R3 now adds one; one-line
  touch-up for the parent).
