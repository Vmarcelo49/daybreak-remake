# Placeholders — DX9 remake record (backend removed)

> **Historical inventory, frozen at the 2026-10-02 Phase 5 cutover.** “Now”
> below means the deleted DX9 remake, not the current product. The original-game
> targets and their provenance remain useful; current foundation behavior and
> open gaps are tracked in
> [`remake/foundation/docs/ROADMAP-PENDING.md`](../foundation/docs/ROADMAP-PENDING.md),
> [`ANIMATION-SETS.md`](../foundation/docs/ANIMATION-SETS.md), and the
> [reference prints](reference/README.md). This is a record, not a work plan.
>
> Provenance: `capture` = original-game print in `reference/`; `wiki` = the
> Higurashi Daybreak wiki; `binary`/`RE` = executable or reverse-engineering
> evidence. The details under “DX9 record” describe only the removed tree.

## 1. Effect techniques

**Original target:** the compiled effects and their techniques/passes, as
identified by `CreateAllShaders` / `FUN_0064ff80` and
`docs/port-from-mvp-plan.md` P3.1. **DX9 record:** ten blobs were loaded but
nothing bound them; fixed-function rendering was used instead. This explains
several of the stand-ins below.

## 2. Hypermode aura

**Original target:** a pulsing silhouette aura, magenta/pink for Oyashiro and
cyan for Friendship (`wiki` captures); the binary names `oyashiro` and
`oyashiroB`. **DX9 record:** one additive cube shell, including an invented,
distinguishable Kakera colour. The old implementation's dimensions and pulse
are deliberately omitted; they are not current tuning.

## 3. Shot and spark visuals

**Original target:** per-weapon projectile models and the binary's `fire`
(muzzle) and `spark` (impact) effects. **DX9 record:** tinted unlit cubes for
shots and expanding/fading additive cubes for sparks (`UnlitCubePass`).

## 4. Baked-shadow decals

**Original target:** blend mode and keying from the material effect technique
(§1). **DX9 record:** texture-name heuristic for `shadow`/影, exact-white alpha
keying, multiply blend and stencil-once darkening. The old implementation
needed D24S8 to avoid drawing a decal repeatedly.

## 5. Character animation

**Original target:** the original binds animation indices from the selected
move's phases and the character/weapon `.dat` table (`FUN_00428510`,
`FUN_00421080`, `FUN_00421100`, `FUN_0041e180`). The 39-entry ASCII table at
`0x6b73b0/0x6b73c0` is a voice-cue table used to construct
`data/voice/<char>/<key>/%03d.wav`, not an animation-name map. Shipped rigs use
`Anim-1`…`Anim-124`; see the current detailed account in
[`ANIMATION-SETS.md`](../foundation/docs/ANIMATION-SETS.md) and the supporting
[asset catalog](ASSET-CATALOG.md) trap 15.

**DX9 record:** its loader bound zero animation sets for fighter models, so
poses stayed at bind pose and state changes changed only the logged name. That
is a fact about the retired renderer, not the foundation's animation system.

## 6. Melee move set

**Original target:** distinct neutral/forward/horizontal, dash, step, air,
landing and airdash attacks, plus a special (wiki move list). **DX9 record:**
one shared 5-damage `AttackA` swing, a 12-damage `AttackB` stand-in and no
input paths for several listed moves. Current selectors and remaining
animation/combat gaps are documented in the foundation roadmap.

## 7. Fighter hit detection

**Original target:** mesh intersections (`D3DXIntersect`) against fighter and
stage collision meshes; no sphere/AABB fighter hit test was found in the
cited reverse-engineering pass. **DX9 record:** ground-plane distance checks
for melee/projectiles, no fighter mesh collision, and no gameplay use of the
camera collision channel. This describes the DX9 implementation only.

## 8. Battle HUD

**Original target:** the art and layout in `reference/battle-hud.webp` and
`reference/ammo-bar.webp`: team balloons/LIMIT, reticule and target status,
overhead HP, proportional ammo fills, hypermode and CPU indicators.
**DX9 record:** mostly Arial text and flat bars; the balloons, reticule,
overhead HP and CPU readout were absent. Use
[`foundation/docs/BATTLE-HUD-SPEC.md`](../foundation/docs/BATTLE-HUD-SPEC.md)
for the current evidence-based atlas/layout inventory.

## 9. KO presentation

**Original target:** the `撃破！` sting, balloon-inflation animation and floating
percentage delta (`reference/ko-moment.webp`). **DX9 record:** ASCII `KO!` and
an immediate fixed `+21%` balloon update.

## 10. Respawn

**Original target:** the KO'd fighter returns from above (wiki Basics, spec
§3.5). **DX9 record:** a ground-position reset after a three-second KO clock.
The original's spawn/respawn evidence and current behavior should be checked in
the living roadmap, not inferred from this old description.

## 11. Audio

**Original target:** per-stage/character BGM, voice and SFX, with master/music/
voice/SFX options (`reference/option-screen.webp`). **DX9 record:** one hardcoded
BGM path, no gameplay SFX or voice, and a then-observed decode failure. Do not
carry that failure forward as a claim about SDL3 audio.

## 12. Stage spawns

**Original target:** stage-specific spawn points from `env.dat`. The old DX9
reader used a hardcoded pair and a different component interpretation.
**Correction:** `FUN_004011f0` reads four header integers at 0x14–0x20, then four
three-integer spawn points from 0x24 in stored order; the old pair beginning
at 0x20 was not the original layout. Which points a versus match uses is a
separate consumer question; see `foundation/docs/ROADMAP-PENDING.md` item A1.

## 13. Frontend scenes

**Original target:** the captured flow in `reference/`: Japanese title menu →
team/character/weapon/costume/hypermode/controller selection → stage settings
→ VS/battle → result/quote/report. **DX9 record:** its scene named `title`
rendered only `data/select/bg00.cnv` (the shared select-panel background), with
no menu labels/cursor; other select scenes were incomplete or unreachable from
the CLI. The actual original title is the shrine menu in
`reference/title-menu.webp`; the name trap and the current frontend belong to
the current docs, not this historical “Now” column.

## 14. Flight model (original target unresolved)

The wiki describes a rising airdash; the owner's observation and game spec §3.6
describe holding jump to fly. Both possibilities remain part of the historical
spec conflict. **DX9 record:** hold-Z flight with a time budget, altitude limit
and stamina drain. That old tuning is not the current product's flight model.

## 15. Provisional tuning constants

The deleted DX9 remake used provisional shot, charge, ammo, hypermode,
stamina, movement, melee and respawn numbers. They were playability choices,
not recovered constants. The detailed old table is intentionally removed:
current product values and provenance are in the foundation source/docs, and
this historical inventory should not be used to tune or verify the port.
