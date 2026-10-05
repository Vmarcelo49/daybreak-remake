# Placeholders — how they should be, how they were (DX9, removed)

> **Historical (2026-10-02).** This inventory was written against the DX9
> tree in `remake/src/`, which was deleted in the Phase 5 cutover; the
> product is now `remake/foundation/`. It is kept because the "should be"
> targets and their provenance still stand — the port's own open gaps are
> tracked in `foundation/docs/ROADMAP-PENDING.md`.
>
> Each entry states the target behaviour (**Should be**, with its
> provenance) and the stand-in the DX9 remake shipped (**Now**), so the
> difference is visible without reading the (now deleted) code. Nothing
> here is a plan or an estimate — it is a status inventory.
>
> Provenance keys: `capture` = `docs/reference/*.webp` (original-game
> screenshots), `wiki` = higurashidaybreak.fandom.com, `binary` =
> `DaybreakDX.exe` strings/addresses, `RE` = `docs/reverse-engineering.md`.

## 1. Effect techniques (root of most VFX placeholders)

**Should be** — the game's 10 compiled effects (binary `CreateAllShaders`,
`FUN_0064ff80`) bound per mesh/material with their own techniques and passes;
every hit, muzzle, aura and decal effect runs through them
(`docs/port-from-mvp-plan.md` P3.1).

**Now** — `render::EffectSystem` loads all 10 blobs
(`assets/shaders/effect_N.bin`) and **nothing binds them**; all rendering is
fixed-function. Everything in §2/§3/§4 below is a consequence of this.

## 2. Hypermode aura

**Should be** — a pulsing particle burst in the mode's colour hugging the
character's silhouette: magenta/pink for Oyashiro, cyan for Friendship
(`wiki` Hypermode page captures of Keiichi and Shion); the binary names the
aura states `oyashiro` / `oyashiroB`.

**Now** — one additive translucent **cube shell** drawn in the fighter's
model space: centre local `(0, 58, 0)`, half-extent `56 + 4·pulse` units,
alpha `70 + 40·pulse` at 8 rad/s, colour from the mode
(Friendship `130,220,255`, Oyashiro `255,110,220`, Kakera `150,255,160`);
Kakera has no capture, so its colour is chosen only to be distinguishable.
`gameplay/fighter.cpp` (`Fighter::render`).

## 3. Shot and spark visuals

**Should be** — per-weapon projectile models with the binary's `fire`
(muzzle) and `spark` (impact) VFX triggers.

**Now** — unlit cubes via `render::UnlitCubePass`: shots are 16-unit
half-extent cubes tinted by tier (tap `150,200,255`, yellow `255,230,80`,
red `255,90,60`, EX `255,90,255`); sparks are additive cubes growing
`14 → 60` units while fading over `0.3–0.35 s`, spawned at the muzzle and at
impact. `gameplay/projectile.cpp` (`ProjectilePool::render`).

## 4. Baked-shadow decals

**Should be** — blend mode and keying driven by the material's effect
technique (same missing binding as §1).

**Now** — heuristics keyed on the texture name: a material is a "shadow
decal" when its `TextureFilename` contains ASCII `shadow` or 影
(`校舎影02`, `手すり影`). Such textures get exact-white texels set to
alpha 0 (**alpha only** — zeroing RGB made bilinear filtering bleed black
into kept edge pixels, which drew a hard dark rim), then render with
multiply blend (`DESTCOLOR`/`ZERO`), depth-write off, and a stencil that
lets each pixel darken at most once (`INCRSAT` under `EQUAL`/ref 0, hence
the `D24S8` depth-stencil). `assets/asset_manager.cpp`,
`file_parser/x_model_loader.cpp`.

## 5. Character animation

**Should be** — the original binds an animation **index**, not a name. A
fighter's state *is* a move id (`[player+0xadec]`): `FUN_00428510` switches on
it, `FUN_00421080` starts the move and caches its 28-byte entry, and
`FUN_00421100` takes phase 0 and binds that phase's first dword to **both**
tracks (`FUN_00421410(0, phase[0])` and `(1, phase[0])`). `FUN_0041e180`
fills the per-player 124-entry animation table from the controller's own sets,
so the `.dat` index *is* the D3DX set index, and the per-move data ships in
`data/<char>/NN.dat`.

**Correction, measured 2026-10-02.** The 39-entry ASCII table at
`0x6b73b0`/`0x6b73c0` (16-byte stride: `attackA/B/C`, `guard`, `recovery`,
`tagfront`, …) is **not** an animation-name table: its only indexer is the
voice system in `FUN_00431e70` (`shl edx,4; add edx,0x6b73b0`), which builds
`data/voice/<char>/<key>/%03d.wav`. Shipped `.X` rigs name their
`AnimationSet`s `Anim-1`…`Anim-124`, so no `attackA` ever appears in a model —
the earlier "40+ named animation sets matched case-insensitively" reading of
this table was wrong (and `ASSET-CATALOG.md` trap 15 inherits the error).
**Foundation correction (2026-10-05).** The current renderer resolves source-
supported port states through a verified character + weapon `NN.dat` table, then
binds its phase tag. It has no parallel state-to-set table. Neutral grounded
attack → 300 and Up/Down ground dash → 20/27 are explicit port inferences; the
original initial-input selectors depend on player fields the port does not model.
Air/side dash, projectile, jump, guard, and contextual attack selectors remain
unresolved. Phase changes use the rig's rounded D3DX period and the trailer's
`+0x20` counter/phase gate; that field does not establish clip playback looping.
Only Rena slot 2 transitions 1→31/34/39 have a recovered cross-fade callback.
See `foundation/docs/ANIMATION-SETS.md` for current details.

**Historical DX9 status (backend removed in Phase 5)** — every fighter model loaded with **0 animation sets**:
the character animation data lives in separate `.dat` files that were not
loaded, so the name lookup in `try_switch_animation()` always missed and fell
back to track 0. Poses were static (bind pose); a state change only changed the
logged name. `F2` animation debug listed an empty set table. The loader itself
would bind up to 2 tracks for a model that has sets; no loaded model did.
`gameplay/fighter.cpp`, `file_parser/x_model_loader.cpp`.

## 6. Melee move set

**Should be** — the wiki's move list: **NA** neutral (chains into ~2 autocombo
hits), **FA** forward, **HA** horizontal, **DashA**, **StepA** (sidestep),
**j.A** (air), **LA** (landing, chains into a 2nd hit), **ADA** (airdash),
plus a 25-damage special.

**Now** — one swing (`AttackA`, 30 frames, active from frame 5, XZ range 160,
5 damage) reused for **all** of dash/aerial; `AttackB` is a 12-damage
stand-in with no key bound; FA/HA/StepA/LA/ADA have no input path; the
special is unimplemented (`specialA/B/C` unused). `gameplay/fighter.cpp`.

## 7. Fighter hit detection

**Should be** — mesh raycasts: the original answers every "did this hit?"
with `D3DXIntersect` against triangle meshes (there is no sphere/AABB code in
the binary; `RE` §10 and `physics/raycast.h`), with the three stage
collision channels (`collision.x`, `collision_camera.x`,
`collision_tama.x`) and fighter meshes as the targets.

**Now** — distance checks on the ground plane: melee is an XZ radius
(≤ 160 units) to the target's position with no vertical component, and a shot
hit is an XZ radius around the projectile (55/65/80/90 per tier). The only
mesh query in gameplay is shot-vs-wall against `collision_tama.x`, loaded
directly by the scene. Fighters themselves have **no collision at all**: the
floor is their spawn height (`m_groundY`) with gravity below it, no wall
queries, and `maps::Stage` (which exposes all three channels) is not used by
`Scene_Gameplay`; the camera runs unclamped (`m_camera.update(dt, nullptr)`)
because `collision_camera.x` is never loaded. `gameplay/fighter.cpp`
(`try_melee_hit`), `gameplay/projectile.cpp`, `core/scenes.cpp`.

## 8. Battle HUD

**Should be** — the captured layout (`capture` `battle-hud.webp`): balloon %
+ `LIMIT` in both top corners with a small player-index digit, the game's own
**FPS counter top-right**, target reticule (red circle, `com` tag, `!` when
targeted) with an **overhead HP bar per fighter**, bottom-right MAIN /
CHARGE / HP with **proportional** fills (3/6 = half fill, `capture`
`ammo-bar.webp` — the fill *is* the recharge readout), bottom-left the
hypermode gauge labelled with the chosen mode, and a CPU-mode readout above
it when an ally is a bot.

**Now** — ASCII text plus solid-colour bars via `D3DXFont`/`D3DXSprite`:
balloon `%.0f%%` + `LIMIT %.0f%%` text per corner, one player digit, MAIN and
CHARGE digits with bars (fractional fill implemented) and a `RELOAD` tag,
HP bar, hypermode bar with mode name plus `READY (S)` / remaining seconds,
and a contextual stamina bar. **Absent**: balloon artwork, FPS counter,
reticule/`com`/`!`, overhead HP bars, CPU-mode readout, and any menu text
(CJK rendering); balloon size handicap % is not modelled (LIMIT is fixed at
100). `render/hud.cpp`, `core/scenes.cpp`.

## 9. KO presentation

**Should be** — fullscreen 撃破！ sting, then the balloon visibly inflates,
then a floating `+N%` delta (`capture` `ko-moment.webp`: 43% with `+21%`);
the wiki range for a KO is 20–23%.

**Now** — ASCII `KO!` centred for 2.0 s, and the balloon total jumps by a
flat `+21.0%` instantly: no kanji sting, no inflate animation, no floating
delta readout. `core/scenes.cpp`, `render/hud.cpp`.

## 10. Respawn

**Should be** — the KO'd fighter **respawns in the air** (wiki Basics, spec
§3.5), i.e. drops back in from above.

**Now** — after a 3.0 s KO clock the fighter is reset at its stored spawn
point **on the ground** (`reset()` sets `m_grounded = true`, zero velocity),
so there is no airborne drop. `core/scenes.cpp`, `gameplay/fighter.cpp`.

## 11. Audio

**Should be** — per-stage/character BGM plus voice and SFX, with the
option screen's four sliders (master/music/voice/SFX) (`capture`
`option-screen.webp`).

**Now** — a single hardcoded track (`data/bgm/01.ogg`) extracted to a temp
file and played through SDL_mixer for every match; **no SFX or voice at
all** (hits, shots, UI and KO are silent). The track currently fails to
decode (`Mix_LoadMUS ... Unrecognized audio format`), so matches run silent.
`core/scenes.cpp`, `audio/audio_engine.cpp`.

## 12. Stage spawns

**Should be** — each stage's own spawn points from its `env.dat`
(`data/stageNN/env.dat`; stage21's file holds `(1393,-463,200)` and
`(-2200,-1363,200)` verbatim, read as (x, z, y)).

**Now** — that one stage21 pair is hardcoded for every stage, both fighters
at the same flat height, so uneven terrain buries them at some spawns (see
the visual suite's delta D5). `core/scenes.cpp`.

**Correction, measured 2026-10-02.** The "(x, z, y)" reading above is the DX9
hardcode's, not the original's: `FUN_004011f0.c:42-64` reads four header ints
(0x14–0x20), then four 3-int spawn points at 0x24 (stride 12) in stored order.
The installed `data/stage21/env.dat` (and `data/stage01/env.dat`) holds
`(-463,200,-2200)`, `(-1363,200,-2200)`, `(-406,200,-105)`,
`(-1363,200,-105)` there; the DX9 pair starts one int earlier (0x20) and reads
(x, z, y), which is where its `(1393,-463,200)` came from. Which of the four
points a versus match spawns at, and with which component order, is still
open — see `foundation/docs/ROADMAP-PENDING.md`.

## 13. Frontend scenes

**Should be** — the captured flow: Title (6 JP items: Story · Versus ·
Netplay · Option · Controller · Exit, `capture` `title-menu.webp`) → Team →
Character → Weapon/Costume → Hypermode → Controller (PLAYER/COM) → Ready →
Stage + battle settings → VS sting → Battle → Result (sting → quote →
report) → back to Team.

**Now** — `Scene_Title` renders only `data/select/bg00.cnv` with **no menu
text or cursor**; `Scene_ModeSelect` is a 3-item ASCII list explicitly marked
unverified against the captures; `Scene_CharacterSelect` shows four portraits
with a TODO comment where cursor highlight and name text belong; gameplay is
entered directly with character indices passed in, and the hypermode pick
comes from the `-hyper` launch flag rather than a select screen.
`core/scenes.cpp`, `core/scenes.h`.

## 14. Flight model (unresolved target)

**Should be** — unresolved between two sources: the wiki describes flight as
a **rising airdash** ("press the jump button and a direction in the air"),
while the owner's observation and spec §3.6 describe **holding jump** to fly
for a limited time.

**Now** — hold-`Z` flight: 1.2 s budget per airtime, rise 40 u/s against
gravity 900, ceiling 420 units above takeoff, 30 stamina/s drain on top of
the 10-stamina leap; air dash is double-tap in the air (once per airtime,
260 u/s for 20 frames), and air control is 0.7 of walk speed.
`gameplay/fighter.cpp`.

## 15. Provisional tuning constants

**Should be** — RE'd or captured values per system.

**Now** — invented for playability (all marked in-code as tuning):

| System | Values in use |
|---|---|
| Shots (tap/yellow/red/EX) | speed 650/550/460/520, damage 4/9/16/22, hit radius 55/65/80/90, life 2.5/2.5/3.0/3.0 s, cost 1 MAIN / 1 / 2 / 1 CHARGE, reload 15/30/45/60 frames |
| Charge thresholds | hold 0.45 s = yellow, 1.10 s = red |
| Ammo recharge | MAIN 0.8/s, CHARGE 0.3/s (max 6 / 2) |
| Hypermode fill | Friendship 1/60 per HP dealt, Oyashiro 1/50 taken, Kakera 1/90 taken |
| Hypermode effects | duration 15/15/25 s, taken ×0.75 / ×1.5 / ×0.20, dealt ×1.5, Friendship recharge ×1.6, Kakera HP drain 100→1 over 25 s, Oyashiro stun skip on even hits |
| Stamina | dash 20, jump 10, guard 25/s, flight 30/s, refill 60/s (max 100) |
| Movement | walk 80 u/s, dash 200, air dash 260, gravity 900 u/s², leap 380 u/s, turn 8 rad/s, double-tap window 0.30 s, dash 20 frames, air control 0.7 |
| Melee | range 160 units, light 5, heavy 12, 30 frames with active window from frame 5 |
| KO / respawn | balloon +21% per KO, 3.0 s respawn delay |
| Fighters | HP 100 (`0x64` in the binary), spawn/max stamina 100 |
