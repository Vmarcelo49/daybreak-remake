# EFFECTS-TRAILS — finding: no trail geometry ships; documented, not built

No owned files changed. Per the track order (survey `data/trail/` and aura/effect
meshes first; build only if the assets carry trail data), this records the survey
and why there is nothing to implement against.

## What `data/trail/` holds

Six textures, nothing else: `00.cnv` … `05.cnv` (65553 bytes each — the standard
256x256 packed BMP-backed `.cnv` size; the trail loop below asks for `%02d`, and
only six indices ship). No `.X` meshes, no `.dat` effect descriptors, no animation
sets.

## Nothing references trails except the exe's runtime table

- Case-insensitive byte search for `trail` across all of `Higurashi-Daybreak/data/`
  (effect, aura, bullet, item, stages included): **zero files**. No `.X` material
  names a trail texture; no `data/effect/*.dat` payload mentions one.
- `grep -rn -i trail remake/src/ research/symbols/`: no trail system, no ribbon
  builder, no trail render state anywhere in the remake or the symbol map.
- The sole consumer is the original binary itself: `DaybreakDX.exe` contains the
  format string `data/trail/%02d.bmp`, loaded by **`FUN_00633ca0`** into a runtime
  texture table — loop `local_124 = 0..9`, `wsprintfA("data/trail/%02d.bmp")`,
  each handle stored at `param_1 + 0x445c + local_124 * 4` (10 slots), immediately
  followed by the `data/aura/%02d` table load. The string address is pinned in the
  corpus (`research/binary_data/strings/filter_bmp.txt`: `006a49b0:
  "data/trail/%02d.bmp"`).

## Why that means "document, don't build"

Trail geometry is **procedural**: the exe keeps indexed trail textures and (per the
genre — sword/afterimage ribbons) must extrude ribbon strips from motion history
at runtime. The producers — sample points, widths, lifetimes, UV scroll, blend
state — live in unmapped exe logic; no shipped mesh, frame, or animation carries
them, and the foundation's parsed material (`diffuse/power/specular/emissive/
texture`, `xmodel.h`) has no field that could drive a ribbon even if one were
invented. Any `src/render/*` trail builder written now would be fan fiction
dressed as a port: geometry sources, update rules, and the card→texture-index
mapping would all be guesses with no reference frame to check against.

Aura/effect meshes corroborate the absence: all 12 surveyed files (`aura/00–05.X`,
`06.x`, `effect/01,02,04,05,08,14`) are static unskinned cards/fans/rings with
`anims=1` spin-or-scale sets — none is a ribbon, none carries per-vertex trail
parameters, and none names `data/trail/*`.

## What would unblock trail rendering (parent-owned RE, not this track)

1. Map the `FUN_00633ca0` table owner (`param_1 + 0x4434…` region) to the fighter/
   projectile update that writes ribbon vertices — the trail producer.
2. Recover the ribbon format (positions per frame history? widths? UV.x along the
   strip?) and the slot→texture-index rule (which of the 10 slots a trail uses).
3. Recover the blend/technique for the strip (likely one of the 10 compiled
   effects from `FUN_0064ff80` — see `EFFECTS-BLEND.md` — but the binding is
   unobserved on both render paths today).

Until then, `data/trail/*.cnv` remain loadable textures with no geometry to wear
them, and no trail code exists in `src/render/*` by decision, not omission.
