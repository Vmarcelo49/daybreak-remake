# EFFECTS-BILLBOARD — cylindrical camera-facing for effect cards

> **Status: research for `ROADMAP-PENDING.md` B1, not a gameplay effect path.**
> Match-mode shots/sparks still render as untextured `debug_prims.h` cubes,
> but auras and melee-hit bursts draw their real cards by default (B1 commit
> `c0c2f4e`; `--debug-prims` keeps the all-cube A/B). `--effect` cards
> exercise only the
> verification scaffolding (additive Effect pass, cylindrical yaw). Nothing here
> changes gameplay VFX.

Owned files changed: `src/render/scene_renderer.{h,cpp}` (classifyBillboard verdict,
`setEye` eye, render-time yaw) plus the `src/main.cpp` wiring (`renderer.setEye` next
to `setCamera`) that activates it. `src/shaders/model_wgsl.h` untouched (no shader
change needed); no texture-name routing added (deliberately excluded).

## Choice: cylindrical, not spherical — and why

Effect cards yaw around world **Y** to face the camera; world up is preserved.
Spherical billboarding was rejected on surveyed geometry:

- `aura/03.X` mesh0 is a 400x400 **floor quad** in XZ (normal +Y). Spherical facing
  would tilt it up toward an overhead camera; cylindrical keeps it in-plane.
  Proof on pixels: `--effect=aura/03.X --camera=top` changes **50 px / 65536**
  old-vs-new (edge rasterization of the two vertical cards), while the floor card
  keeps its authored orientation by construction (it is never marked).
- Uprights that pass the ground rule yaw (`effect/05.X` YZ quad, `aura/03.X`
  verticals, crossed sets); `aura/04.X` (mean `|normal.y|` 0.60) and `aura/06.x`
  (0.65) are ground-dominant by the 0.5 rule and keep their authored orientation —
  the yaw helps single quads, not capped bands or box-like outliers. The arena
  camera stays near level (spawn + 320), so a Y-only yaw faces them without ever
  laying them flat.
- Y-symmetric geometry (rings, bands, beam fans) is rotation-invariant around Y,
  so yawing it is at worst harmless.

The reference behavior the assets themselves encode is billboard-*free*: crossed
3-plane sets (`aura/00.X`, `effect/02.X` meshes 0–1) plus tumbling spin animations
(`aura/00.X` frame `obj2` rotates through general orientations over its 240-tick
`Anim-1`). The artists baked view-independence into geometry, and neither the DX9
remake reference (`x_model_loader.cpp render_frame` draws every mesh as-is) nor
the original's crossed-plane construction shows runtime facing. The one case the
authored geometry cannot cover is the **single quad seen edge-on** (`effect/05.X`
from `--camera=front`: 0 px — the card's YZ plane contains the view ray), which is
what this change fixes. Whether the original yaws such cards at runtime (its
`.dat` effect player is unmapped) remains unverified; see "Not verified".

## Routing (geometry only, no texture names)

Per Effect-pass draw, at `setScene()` time (`classifyBillboard()`):

- Only `Pass::Effect` (role `effect`/`aura`) draws are candidates — bare `--model`
  stays opaque and unmarked, full-stage frames contain no such draws.
- Skinned meshes are excluded (all 12 surveyed effect/aura files are unskinned,
  so the pivot math below is exact on the corpus; a future skinned effect card
  keeps its authored orientation rather than rotating around a wrong pivot).
- Ground-dominant cards (mean `|normal.y| > 0.5`) are excluded: their plane already
  contains every camera yaw (`aura/03.X` mesh0, shockwave flats).
- Pivot = submesh bounds center (mesh space); authored facing = dominant normal
  axis (`+X → +90°`, `-X → −90°`, `−Z → 180°`, else `0°`; a crossed-plane tie
  falls through to `+Z`, which faces one of its cards at the camera). A YZ-plane
  card's normal starts at +X, so facing the camera needs `yaw − 90°`, not `yaw`.

At `render()` time, for marked draws only, with the eye from `setEye()`:

```
Cw = model * palette[0] * bbCenter      // posed pivot (palette_ is post-updatePose)
yaw = atan2(eye.x − Cw.x, eye.z − Cw.z) − bbYaw0
du.model = T(Cw) · Ry(yaw) · T(−Cw) · model
```

An overhead camera (`|d|² ≤ 1e-6`) keeps the authored orientation instead of
spinning on the yaw singularity. `setEye()` is a new setter because the viewProj
matrix alone cannot yield the eye (a perspective product does not separate). It is
wired in-repo: `src/main.cpp` calls `renderer.setEye(app.eye)` next to `setCamera`
every frame, so `haveEye_` is true and marked Effect draws yaw in current captures;
the dormant switch (`haveEye_` false, byte-identical) applies only to callers that
never call `setEye()`, not to the repo demo.

## Verification — historical shim results (deleted `/tmp/eshim` copy; not re-runnable)

The rows below come from a deleted `/tmp/eshim` copy whose `main.cpp` wired `setEye`
behind `ESHIM_NO_EYE` (with `ESHIM_PLANT` for the mixed frame only); that copy exists
nowhere in the tree, so no entry can be re-run. Because in-repo `main.cpp` now wires
`setEye` unconditionally, current captures include billboarding and these old-vs-new
deltas do not describe the present tree. Re-verify by capturing `--effect` cards with
and without the `setEye` call before citing deltas.

- Shim (history): `cp -a remake/foundation /tmp/eshim` (build/ excluded), `cmake -B
  /tmp/eshim/build/linux` + build; the *copy's* `main.cpp` called
  `renderer.setEye(app.eye)` (gated on `ESHIM_NO_EYE` unset) and, for the mixed
  frame only, `ESHIM_PLANT` moved ride-along effects to the eye/aim midpoint at
  30x. Old binary = repo `remake/foundation/build/linux/foundation_demo`
  (pre-change). New binary = shim build. Sizes 256 (cards) / 400 (stages).

| Capture | Old | New | Δ |
|---|---|---|---|
| `--model=effect/05.X --camera=front` (opaque path) | 0 px (edge-on) | 0 px | **0 px** — change does not fire where it should not |
| `--stage=stage01` (141 draws, 4 decals) | 157886 px cov | same | **0 px / 160000** |
| `--character=akane` | 15022 px cov | same | **0 px / 65536** |
| `--effect=effect/05.X --camera=front` | 0 px (edge-on) | 20684 px (31.56%), lum peak 0.996, 1 billboarded | **22499 px, maxΔ240** — card faces camera |
| same, `ESHIM_NO_EYE=1` (dormant switch in new code) | — | 0 px | **0 px vs old** — the eye is the only switch |
| `--effect=aura/00.X --camera=front` (3-plane cross) | 23.79% | 23.94% | 23363 px, maxΔ227 — cross re-yawed, one card exactly face-on |
| `--effect=aura/00.X --camera=bounds` | 10.25% | 10.26% | 9545 px — near-invariant, as a cross should be |
| `--effect=aura/03.X --camera=top` (2 of 3 billboarded; floor skipped) | 358 px | 357 px | **50 px, maxΔ103** — cylindricality proof (spherical would tilt cards at the top camera: thousands of px) |
| `--effect=effect/02.X --camera=front` (cross + `hikari` beam fan) | 426 px | 423 px | 424 px, maxΔ242 — fan rotates rigidly, stays plausible |
| `--stage=stage01 --effect=aura/00.X --camera=player` planted 30x | — | glow starburst over lit stage, lum peak 1.0 | additive monotonicity: **0/160000 px darker**, Δ ∈ [1,247] — the Effect pass only adds light |

- Linux-new vs Windows/Wine-new (MinGW cross-build in `/tmp/eshim/build/windows`,
  run under Wine, same RADV adapter via winevulkan): **byte-identical (0 px)** on
  `effect/05.X`, `aura/00.X`, `stage01`, and bare `--model` — the yaw math
  (`atan2`, dominant-axis vote) is deterministic across targets.
- Web target compiles (`./build.sh web` ok in the shim); web runtime not executed.

## Not verified

- Original-exe comparison: whether the original yaws single quads (or anything)
  at runtime is unknown — its `.dat` effect player is unmapped. Crossed-plane
  cards change orientation vs the no-billboard reference whenever the camera yaw
  is not a multiple of 90°; on radially symmetric glow textures (the surveyed
  majority) that rotation is invisible, on directional art it is a real
  difference with no reference to check against.
- `hikari`-style beam fans rotate rigidly with the yaw; their authored burst
  direction is relative to the attack, which verification captures do not model.
- In-repo `main.cpp` wires `setEye()` unconditionally (next to `setCamera`), so the
  billboard block is live in current captures; the dormant-switch rows above describe
  the historical shim copy gated behind `ESHIM_NO_EYE`, not the present tree.
