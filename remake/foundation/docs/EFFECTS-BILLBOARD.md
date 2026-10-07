# EFFECTS-BILLBOARD — cylindrical camera-facing for effect cards

> **Status: geometry research for the live Effect renderer.**
> Gameplay now renders aura and event cards through the Effect pass; in-flight
> shots use their own recovered bullet models. `--debug-prims` retains cube
> stand-ins, and `--effect` remains a verification route, not the gameplay event
> system. Projectile models differ from flat cards: shot-record flags control
> whether they request billboarding (`FUN_005f60b0`; see `ROADMAP-PENDING.md` B1).

Implementation in the current tree: `src/render/scene_renderer.{h,cpp}` classifies
billboard candidates, stores the camera eye, and applies render-time yaw; `src/main.cpp`
wires `renderer.setEye(app.eye)` next to `setCamera`. `src/shaders/model_wgsl.h` is
untouched (no shader change needed), and texture-name routing remains deliberately
excluded.

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

## Historical verification (shim results, not current-tree measurements)

A deleted `/tmp/eshim` copy compared a pre-change binary against this billboard
implementation with `setEye` wired. The shim and its captures cannot be rerun;
these are historical observations, not measurements of today's gameplay path.
The test found that a formerly edge-on single `effect/05.X` quad became visible
from the front, the vertical cards of `aura/03.X` changed only 50 pixels in a
top-camera comparison while its XZ floor quad stayed authored, and a planted
`aura/00.X` Effect pass over `stage01` darkened 0/160000 pixels. The old pass
also recorded byte-identical Linux/Wine captures for selected assets. Do not use
the detailed deltas from the discarded harness as current parity evidence.

## Not verified

- Original-exe comparison: whether the original yaws single quads (or anything)
  at runtime is unknown — its `.dat` effect player is unmapped. Crossed-plane
  cards change orientation vs the no-billboard reference whenever the camera yaw
  is not a multiple of 90°; on radially symmetric glow textures (the surveyed
  majority) that rotation is invisible, on directional art it is a real
  difference with no reference to check against.
- `hikari`-style beam fans rotate rigidly with the yaw; their authored burst
  direction is relative to the attack, which the historical verification captures
  do not model.
- The exact original runtime behavior remains unknown: its `.dat` effect player is
  unmapped. Crossed-plane cards change orientation at camera yaws other than 90°
  increments; that is invisible on most surveyed radial glow textures but can matter
  for directional artwork. Current gameplay captures are billboard-enabled when the
  card geometry qualifies and the view supplies an eye; the overhead singularity and
  ground-dominant exclusions preserve authored orientation.
