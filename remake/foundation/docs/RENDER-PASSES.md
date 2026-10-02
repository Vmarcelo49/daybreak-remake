# R2 effect passes + R3 decal correctness — what the renderer does now

Owned files changed: `src/render/scene_renderer.{h,cpp}` (`Pass`, pipelines,
ordering, stencil depth). Shader untouched except R1/R4 items (see
`RENDER-MATERIALS.md`).

## R2 — additive effect pass for the observed cards

Observed failure (pre-change binary, `effect/hit.X` 0.00% coverage is a framing
miss; the telling ones): `aura/00.X` and `effect/01.X` render as **opaque black
quads** — the glow texture's near-black skirt drawn with `SRC_ALPHA/INV_SRC_ALPHA`
at texture alpha 255. Surveyed effect/aura textures are alpha-255 *everywhere*
with low mean luminance (0.01–0.35), so no alpha-test threshold can ever cut the
skirt: the cards require an additive-like blend. Their parsed material terms are
identical to opaque geometry (white diffuse, power 0, ~zero spec/emissive), so no
material signal can route them either.

What was implemented (all in owned files):

- `render::Pass { Opaque, Decal, Effect }`; `classifyPass(role, texture)` routes
  `role == "effect"/"aura"` → Effect, shadow names → Decal, else Opaque. Roles
  are the asset layer's model-category vocabulary — the only honest signal, since
  materials cannot distinguish the cards.
- Effect pipeline: blend `SRC_ALPHA, ONE` / alpha `ONE, ONE`, unlit, depth test
  on / write off, cull off — the 2D/effect-pass treatment (cull-off precedented
  by the original's effect passes and the DX9 debug additive `SRCALPHA, ONE`).
  `SRC_ALPHA, ONE` coincides with `ONE, ONE` on every surveyed effect texture
  (alpha ≡ 255); the general-case difference is unverified and stated as such.
- Explicit 3-way ordering, asset order preserved within a pass (two stable
  partitions): opaque → multiply decals → additive effects. Decal-after-opaque
  reproduces the original's decal-pass-last order; effect-last is the renderer's
  choice, unverified against the original, documented at the code.
- Pipelines build lazily per pass: scenes with no effect draws never create the
  effect pipeline (no dead GPU objects in the default captures).

Verification — `/tmp`-only caller shim (a copied `main.cpp` in `/tmp`, repo
`main.cpp` untouched; shim flags `--tag-effects`, `--with-aura`, role retitle by
`/effect|/aura/` path, effect cards planted at the frame aim):

- `aura/00.X` as effect: black quads gone, muzzle-flash glow over black
  (coverage 10.82% → 25.14%, luminance peak 1.0). `effect/01.X`: 7.12% → 17.95%.
- Mixed frame (stage01 + aura card at the aim, 30×): the glow composites **over**
  the lit stage — opaque → decal → effect ordering in one frame. Faint quad skirt
  edges remain visible against sky (texture floor ≈ 0.06 adds uniformly); the
  original presumably shows the same with these textures, or its technique keys
  the skirt — unverified, observed and stated.
- Without role assignment (all in-repo demo paths: `--model` keeps role
  `"model"`), effect captures are **byte-identical** to pre-change
  (`effect/01.X`: 0 px) — the new pass cannot alter any existing capture.

Out of scope (labeled, not claimed): trails, hit sparks beyond `hit.X`/`hit2`,
per-effect blend factors from the 10 compiled effect shaders (technique
binding unimplemented on both paths), any effect routing by texture name
(would be a second provisional heuristic; deliberately not added).
Billboarding is in scope and landed: effect cards yaw to face the camera
cylindrically around world Y — the verdict is geometry-only in
`classifyBillboard` (`src/render/scene_renderer.cpp:55-100`), dormant until
`setEye()` runs, then folded into the draw model matrix
(`:457-460`, `:567-570`, `:761-773`; header documents it at
`src/render/scene_renderer.h:214-220,268-280`). Ground-plane cards stay put.

Parent-owned follow-up, now landed: `--effect=<file>` loads one card with the
effect role (standalone, or riding along with any other asset the way a weapon
rides a character), and the `main.cpp` draws line prints the effects count.
Nested `EffectInstance` parsing landed as `Material::effectFile` in
`readMaterialBody`, covering named and inline materials
(`src/assets/xmodel.h:1400-1407`). Routing in `classifyPass` is deliberately
unchanged until an asset actually carries an effect file
(`src/render/scene_renderer.cpp:41-45`).

## R3 — decal overlap: DX9 stencil guard, verified on captures

The DX9 reference (`x_model_loader.cpp render_frame`) draws shadow decals with
`EQUAL 0 / INCRSAT` stencil so overlapping cards darken each pixel at most once.
The foundation had no stencil (white-keying alone), so overlaps multiplied twice.

What was implemented: depth texture `Depth24Plus` → `Depth24PlusStencil8`
(identical 24-bit depth values); decal pipeline stencil `EQUAL`, `passOp
INCRSAT`, full masks (full masks on all passes — behavior-neutral, avoids any
zero-mask validation question on unexecuted backends); stencil ref 0 set on
decal-pass bind; per-frame stencil clear 0 / discard. Alpha-tested-away texels
never reach the stencil, so silhouettes stay exact — same construction as DX9.

Verification (stencil isolated via a `/tmp`-only variant with the alpha change
reverted, so every pixel below is the guard alone):

- Full-stage frames: **0 px changed** on stage01 and stage21 vs pre-change
  (the verified captures carry no visible overlap at this camera — the guard is
  behavior-preserving where it does not fire).
- Decal closeup (`stage01/04.X` alone: 校舎影02 / 影坂01 / shadow01 / 手すり影,
  top camera): 123 px differ, **all 123 brighter in the stencil build, 0 darker,
  159877 unchanged** — exactly the double-darken signature: previously
  twice-multiplied overlap texels now multiply once, nothing else touched.

## Not verified

- Shadow cards against a DX9 frame (PORT-PLAN's bar): no DX9 run this session.
  The guard matches the in-tree DX9 states verbatim and the pixel signature is
  exactly single-vs-double multiply, but an original-exe comparison is still open.
- Web/Dawn runtime for the stencil path: compiles; not executed (browser page
  came up empty in this session — Emscripten shell issue unrelated to the change,
  wasm/js built fine). Native Vulkan validates the full path on two drivers
  (RADV Linux + Wine).
