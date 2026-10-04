# Pending work — the foundation, after the DX9 cutover

> Written 2026-10-02, the day of the Phase 5 cutover
> (`FULL-REPLACEMENT-PLAN.md` §8). DX9 is gone, so this file is the handoff:
> what is still open, what evidence points at it, and a concrete way in.
> Ordered by **what unblocks the most**, not by size: first the two
> instruments every other number depends on (A), then the battle frame's
> remaining fidelity (B–D), then front-end breadth (E–F), then the claim
> debts that must not be outrun (G).
>
> Honesty labels, used per item: **measured** = a number or artifact exists
> and is cited; **inferred** = read from the original's code or the prints
> but not yet executed; **unknown** = no pointer was found in this repo.
> Every pointer was re-checked on 2026-10-02 against the cutover tree; the
> two places where the hand-off notes were wrong say so inline. Line numbers
> for the deleted DX9 tree refer to the `pre-webgpu-cutover` tag
> (`37ed31d`).

## Implementation update — 2026-10-04

The front end now runs title → team/character/weapon/hypermode/controller
selection → stage settings → VS → countdown → two- or four-fighter matches →
victory/quote/report → selection. The earlier evidence and sketches below
remain the historical handoff; these status notes supersede their claims
that these screens or their audio do not exist.

| Item | Current status | Remaining work |
|---|---|---|
| D2 | Complete: both arcs and the 15-tick lock-switch pulse | None for the recovered ring transform |
| D3 | Countdown and winning-team sting implemented; four-fighter simulation builds and passes host tests | Extra fighter bars; original countdown trigger/timing and asset-backed four-fighter run remain unverified |
| E1 | Selection, real atlases, roster tables, costumes, weapons, controller slots, seeded COM choices and entry voices implemented; selected panels load into the four-fighter match path | Four-fighter HUD/VS/result presentation and exact original navigation parity remain open; asset-backed launch remains unverified |
| E2 | Stage/variation and all five battle settings implemented and connected | Original balloon-capacity and timed-round winner rules need recovery; current normalized capacity and timed comparison are port rules |
| E3 | Volumes, fullscreen, native resolution selection and keyboard/gamepad rebinding implemented | Three renderer controls are unavailable; settings are process-local |
| E4 | 109-update VS transition implemented | Four-fighter VS presentation; confirm-to-skip is a port extension |
| E5 | Sting, quote, voice, actual participant stats and draw handling implemented | Original earned titles and outcome-specific quote selection; missing single quotes use that character's self-pair script |
| E6 | Reusable two-page atlas keyboard implemented and tested | Netplay host remains outside D6 scope |
| F1 | Four menu SEs, entry/result voices and menu BGM connected | Hardware audio listening remains separate from dummy-device verification |
| G1 | Real-asset versus and live match executed in a browser | Hardware GPU and usable browser screenshots remain unverified |
| G2 | Unverified | No macOS hardware available |
| G3 | Rechecked: 165 pass, 43 known flags, 0 pipeline failures | Existing install texture gaps remain |

Implementation lives in `src/ui/screen_select.*`, `screen_stage_select.*`,
`screen_options.*`, `screen_vs.*`, `screen_result.*`, `soft_keyboard.*`,
`frontend_launch.*` and `frontend_settings.*`; the host in `src/main.cpp`
loads the selected assets and applies `MatchConfig`. A 1v1 match uses upper
panels and env slots 0 (blue) and 2 (red); a multi-fighter match uses each
selected panel's corresponding env slot. Standalone parity captures retain
their existing 0/1 spawn recipe. COM battle input is a
deterministic port sparring policy, not recovered original AI.

Recovered details: the roster anchors/order/costume limits are the tables
at `0x6b71d0/0x6b7210/0x6b7250/0x6b7290`; the stage constructor's count
makes the school stage three-way and other stages two-way. Result report
art is in `FUN_00633ca0` (header y=320, width=288). D2's writer is
`FUN_00421e30`/`FUN_00421f30`, decrement `FUN_004201a0`: lock switch writes
15 and ticks decrement it; the first arc adds 9 degrees per pulse tick,
both arcs scale by `1 + 0.1*pulse`.

B1 also received a parser correction: `FUN_0042eec0` reads a version dword
then one fixed 260-byte model path at offset 4, not a mesh count and short
name slots. `src/game/effect_descriptor.h` now checks that contract.
Lifetime remains unresolved: all 22 installed descriptor variants have a
zero raw lifetime field. `FUN_00436630` ticks instance `+0x130` against the
variant referenced at `+0x120`; constructor/factory are `FUN_0042f820` /
`FUN_0042f5e0`. Aura defaults in `FUN_004205e0` select 0/5/1, with an
explicit override at `+0x7d4`; state overrides in `FUN_0042e110` select 2/3.
These findings do not yet establish the complete mode mapping or a safe
replacement for the placeholder effect lifetime. B1 trails and C1's
unproven guard/jump writers remain open.

Verification: native full-flow runs reached live battle and results with
`RESULT: ok`, including a result voice. The browser asset run used
SwiftShader (details in `BUILD-web.md`). The full texture sweep reproduced
the existing 43 flags without new misses. Regression tests cover menu
states, settings, launch mapping, results, descriptor parsing, ring pulse,
match rules and combat statistics. All 24 Linux CTest tests pass; Linux,
Windows cross-build and web asset builds succeed. Native smoke recipe:

```bash
SDL_AUDIODRIVER=dummy ./remake/foundation/build/linux/foundation_demo \
  --headless --install=Higurashi-Daybreak --screen=title \
  --script=remake/foundation/tests/scripts/frontend-smoke.txt \
  --frames=4700 --out=/tmp/frontend-smoke.ppm --size=800x600
```

Display support now derives battle HUD anchors from the viewport, projects fighter
markers through the actual battle camera, and keeps menus on a uniformly scaled
4:3 canvas with black bars. Aspect handling is automatic, including ultrawide.
Native Options offers Desktop/common/display-mode resolution choices; browser
and headless rows show their externally controlled sizing. Linux native Wayland
checks exercised window resize, fullscreen toggling and fullscreen resolution
changes. Real-asset captures checked 1920×1080 and 3440×1440 battle layout,
3440×1440 selection, and an irregular 1373×777 menu viewport. Layout tests also
cover portrait, 4:3 and clipped/rotated sprites.

## A. Correctness and the measurement instruments (do first)

These gate every number the other items are judged by, which is why they
come before the visible work.

### A1. `env.dat` spawn: which point, and in which order — **diagnosis changed**

* **What.** The foundation's default (no `--spawn`/`--spawn2`) takes P1/P2
  from `scene.env.points[0]`/`[1]`, and a trace A/B only matched after
  passing `--spawn2` explicitly. Every default-spawned match is therefore
  placed on unverified coordinates.
* **Evidence.** Plan §6a's note ("puts P2 at `(-1363,200,-2200)` where the
  DX9 log has `(-2200,200,-1363)` — x and z swapped"); the wiring is
  `src/main.cpp:762-763, 810-826`.
  **What this pass measured, and it changes the item:** the original's own
  reader is `FUN_004011f0` (`research/decompiled/FUN_004011f0.c:40-64`) —
  five fog ints, four header ints at `0x14`–`0x20`, then **four** spawn
  triples at `0x24`, stride 12, in stored order. `src/assets/scene.h:253-273`
  (`readEnv`) reads exactly the same offsets in the same order, so this is
  **not** a field-order bug against the original. The installed
  `data/stage21/env.dat` holds `(-463,200,-2200)`, `(-1363,200,-2200)`,
  `(-406,200,-105)`, `(-1363,200,-105)` there; `data/stage01/env.dat` holds
  the same spawn region byte for byte (verified: identical from `0x14` to the
  end of the 84-byte file, only the fog header differs) — two points at
  `z = -2200`, two at `z = -105`, which reads like two teams' spawn pairs.
  The DX9 pair starts one int
  earlier (`0x20`) and reads `(x, z, y)`, which is where its
  `(1393,-463,200)` came from. Also: the DX9 side had **no** env.dat parse
  at all — `pre-webgpu-cutover:remake/src/core/scenes.cpp:527-535` is a
  hardcode plus that comment — so "compare against the DX9 loader" has
  nothing to compare, and the plan's word "loader bug" overstates what was
  established.
* **Resolved (this pass).** The consumer is `FUN_00423420`
  (`research/decompiled/FUN_00423420.c`): it copies **three floats
  verbatim** from `scene + 0x44 + slot*12` into the fighter's position
  (`*dest = *src; dest[1]=src[1]; dest[2]=src[2]`) — **no axis swap**, so the
  file's `(a,b,c)` is the vec3 `(x,y,z)` (the middle `200` is the y-up
  height). The slot is read as the fighter's own `+8` field, `+0x14` the dest
  (Ghidra elides the index in `FUN_0041dcb0`'s
  `FUN_00423420(param_1+5, param_1[2])` call — the `+5` is the *dest*
  `fighter+0x14`, the `[2]` is the *index* `*(fighter+8)`; the call shape
  fits exactly, though no writer of the slot field was located, so the
  field's meaning is triangulated inference, not a confirmed store).
  `FUN_0064ab30(i)` creates the four fighters in slot order 0..3 (with four
  consecutive `FUN_0041dcb0` applications beside it), so **P1 takes
  `points[0]` and P2 `points[1]`** — the two `z=-2200` points in
  stage01/stage21. The port's `readEnv` + `points[0]`/`points[1]` default was
  already correct; the old "trace A/B only matched with `--spawn2`" was
  matching the deleted DX9 build's hardcoded pair, not the original's
  env.dat pick. Provenance added to `src/main.cpp` (`initMatch` comment).
  The sketch's `compare_match_traces.py` re-run is moot (the DX9 tree it
  compared against is deleted); port-side determinism is pinned by
  `fighter_script_test` case 14 instead. Pinned by `tests/env_spawn_test.cpp`
  (ctest): both stages' fog/header/points through the port's own `readEnv`,
  the shared spawn region, and the far/near pairing. No code change required.

### A2. The exact viewpoint within `stage01` — the instrument for every print claim

* **What.** Print-parity frames are compared against `battle-hud.webp`
  without the print's capture position being pinned, so part of the
  background RMSE is framing, not renderer error.
* **Evidence.** The camera itself is solved from the print and lands
  (`dist 288.9`, `height 210.9`, `aimHeight 138.3`, 0.0 px residual on the
  four rows that over-determine it, baseline orbit 0) — commit `92156ac`.
  The residual floor is measured: every HUD band is now better than the
  **0.2755 scene-only floor** (commit `37657cd`, `tests/hud_bands.py`).
  **Not found anywhere in the tree or history:** the claim that the camera
  track's spawn was a coarse grid-search match — treat that as unverified
  and this item as "the spawn is not pinned", which the floor supports
  either way.
* **Sketch.** Either solve it from the print's own geometry (two ground
  contacts — the wall base and the building's pixels — back-projected
  against `data/stage01/collision.x`'s ground height and the known π/4 FOV),
  or score the stage's four `env.dat` points through the now-solved camera
  and keep the minimum scene-band RMSE (`tests/hud_bands.py` reports the
  bands; `tests/compare_frames.py` the whole-frame number). Record the
  winner in the capture recipe so later numbers stay comparable.
* **Resolved (this pass, second route).** Four converged captures, P1 on each
  env point with P2 on its pair-mate (far pair `z=-2200`, near pair `z=-105`),
  print cast (rena/mion), `--match --frames=150 --size=800x600`: scene-floor
  RMSE **0.2772** (P1 `points[0]`), 0.2908 (`points[1]`), 0.3162 (`points[2]`),
  0.2961 (`points[3]`). The winner is **P1 at `points[0]`
  `(-463,200,-2200)`, P2 at `points[1]`** — within 0.002 of the documented
  0.2755 floor (**correction 2026-10-03:** the original entry said "landing
  exactly on"; 0.2772 is near, not equal), and corroborating A1
  (P1=`points[0]`) by an independent method. Re-runnable as
  `tests/pin_viewpoint.py` (same four captures, same instruments, winner and
  tolerances asserted — reproduced 2026-10-03 to all four decimals on the
  post-B1/B2 binary).
  Whole-frame context: 0.2567 / 0.2438 / 0.2699 / 0.2478 (config 1 lower, but
  whole-frame is confounded by the mirrored fighter pose and HUD art; the
  scene band is the prescribed instrument). Converged trace eye
  `(-174,411,-2200)` = P1+`(289,211,0)` — the preset offset exactly, and the
  sim faces the fighters toward each other. Gotchas for the recipe: match
  frames render through `gameplay::ArenaCamera` (original preset), **not** the
  static `camera arena at ...` log line (remake-preset seed, overwritten by
  the first tick); `--frames` must be ≥121 (eye converges 10%/call from the
  origin — the frame-1 eye is unconverged); capturing fixes `--dt` at 1/60 so
  the run is deterministic; the match path passes a null collision frame, so
  the eye is unclamped. Recipe recorded in `BATTLE-HUD-SPEC.md` §7.

## B. Battle visuals

### B1. VFX: auras and effects first, trails are RE-blocked — **partially done**

* **Progress (this pass).** The aura and hit-effect classes now draw their
  real cards, replacing the cube A/B one class at a time as sketched:
  `src/main.cpp` builds a renderer effect-asset table at match/versus start
  (`buildFxAssets`): asset 0 is the melee-hit card, resolved through
  `data/effect/000.dat` (corrected header: version dword then a fixed 260-byte
  model path — slot 000 names `14.X`), and in match mode assets
  1–2 are `data/aura/00.X`, `FUN_00633ca0`'s first aura slot. The gameplay
  `EffectEventQueue`s (`game/effect_events.h`) are no longer drained to
  nothing: `updateFxCards` owns the live card set (spawn / kill-by-id /
  ttl expiry) and `placeFxCards` writes the per-frame model matrices, so
  the existing `Pass::Effect` additive pass and cylindrical billboard
  (`scene_renderer.cpp`) draw them. The aura follows fighter state
  through the fighter's own model matrix in local space — verified
  bit-for-bit the aura cube's transform (`modelMatrix() *
  aura_center_local()`). `--debug-prims` is the A/B: with it, the old
  all-cube view (aura cube included) renders and the cards are hidden;
  without it, the cards render and the aura cube does not (A/B with a live
  card differs by 0.08 RMSE in the fighter band). Shot/spark cubes stay
  as-is: their real VFX are trails, which remain RE-blocked below.
  Draw-count attribution, verified by rebuilding the pre-B1 binary:
  parity capture was **167** draws / 0 effects, now **177** / 10 effects
  (8 submeshes from `14.X` + 1 per aura card; versus is 175 / 8 with the
  hit card alone) — pixels byte-identical, since hidden cards emit only
  degenerate triangles. **Correction 2026-10-03:** commit `c0c2f4e`'s
  message reports "177 draws ... unchanged", quoting the post-change count
  as the baseline; pre-B1 was 167. The "broke nothing" substance (identical
  pixels, 0 untextured) stands.
  Two measured facts the port needed: the card texture cache falls back
  from the card's own directory to `data/aura/`; and `aura/00.X` is a
  54.6-unit cube-extent blob (12 verts, texture `炎上オーラ`) while
  `effect/14.X` spans 20×178×137 units over 8 quads (1 `hitC01` + 7
  `hitC05`), so both are fighter-scale with no scale factor in the first
  pass. **Correction 2026-10-03:** the fallback never fires for either
  shipped card — `hitC05.cnv` exists in `data/effect/` and `炎上オーラ.cnv`
  in `data/aura/` — and no loaded card references the `muzzle`/`hitb`/`g`
  textures the split story cites. It is untested defensive generality, not
  a measured need; likewise "quad plus four beams" misdescribes 8 quads.
  **Undisclosed tuning (now disclosed):** hit cards live **12 s**
  (`tickMatch` pushSpawn) and versus cards 5 s, full-bright with no fade —
  a frame-600 capture still shows a ~frame-105 hit blazing 8 s later.
  Kill-chaining retires non-final cards on the next hit, but the last one
  lingers. Both numbers are placeholders until sketch (b) recovers the
  real factors; the roadmap's "unknown" stands.
  **Unknown (unchanged, plus one addition):** the slot→fighter rule for
  `FUN_00633ca0`'s seven aura slots (both fighters share slot 0 for now);
  **new:** the slot→*mode* rule is equally unmapped — every mode shows
  slot-0 art, flattening the per-mode aura colors (`hypermode_params`:
  magenta Oyashiro, cyan Friendship) down to the `--debug-prims` view;
  the per-effect factors (sketch b), and the trail strip (sketch c).
* **What (remaining).** Shots and sparks are still drawn as `debug_prims.h`
  cubes (their real VFX are trails, RE-blocked below); the aura slot→fighter
  rule is unmapped (both fighters share slot 0); per-effect factors and the
  billboard yaw against the original are not matched.
* **Evidence (read/measured).** `FUN_00633ca0` loads **10** trail textures
  (`data/trail/%02d.bmp`, loop `< 10`) and **7** aura models
  (`data/aura/%02d.x`, loop `< 7`) — `research/recomp/FUN_00633ca0.c:52-60`.
  Effect instances are already parsed off `.X` materials
  (`src/assets/xmodel.h:1400-1407`, `Material::effectFile`), and the
  renderer already classifies cylindrical billboards for `Pass::Effect`
  (`src/render/scene_renderer.cpp:55,457`); `EFFECTS-BILLBOARD.md` has the
  yaw survey and its measured per-view numbers. `EFFECTS-TRAILS.md` is a
  **negative result**: no trail geometry ships, no `.X` names a trail
  texture, and the table's owner (`param_1 + 0x4434…`) is not mapped to the
  producer that writes ribbon vertices — so trails need RE, not a draw
  path. **Unknown:** the per-effect factor table (there is no committed
  pointer to it; `remake/assets/shaders/effect_*.bin` are extracted blobs
  the DX9 remake never bound — historical `placeholders.md` §1).
* **Sketch.** (a) Draw the aura/effect meshes the combat events and
  `data/<char>/NN.dat` already spawn, replacing cubes one class at a time
  and keeping `--debug-prims` as the A/B. (b) Recover the per-effect factors
  from the original's effect code before touching tuning. (c) Trails: map
  `FUN_00633ca0`'s table owner to the update that writes the strip
  (`EFFECTS-TRAILS.md` §"What would unblock"), including the slot →
  texture-index rule and the blend technique.

### B2. The idle pose is a composite: two controllers per model

* **What.** The print's lowered-arm idle is not any single shipped set, and
  the port binds one set per state.
* **Evidence (measured).** Commit `8fae1f9`: round start (set 43) 0.3933,
  walk (set 13) 0.2749, the closest single set in the whole rig (91, from
  the shot finisher) 0.3003 — against idle's own band 0.2747. The original
  clones **two controllers per model** (`FUN_0064d940`: the
  `for (local_24 = 0; local_24 < 2)` clone loop at
  `research/decompiled/FUN_0064d940.c:60-68`; earlier notes cited a
  transposed `FUN_00464d94`, which does not exist — corrected 2026-10-03)
  and the `.dat`
  animation entries carry per-track floats at `+0xc` and `+0x10`
  (`research/decompiled/FUN_0041e180.c:145,149` — offsets verified this
  pass, the *weight* semantics are inferred), cross-faded by
  `FUN_0041f580`. The missing link is `FUN_00421410`'s vtable call
  `(*(*player + 0x20))(oldIdx, newIdx)`.
  `src/gameplay/fighter.h:96-119` documents the binding the port needs:
  `FUN_00421100` binds phase 0 to **both** tracks.
* **Sketch.** Give `xm::Controller` a second track plus per-track weights,
  read the weight fields `FUN_0041f580` actually consumes, bind `phase[0]`
  to both tracks as `FUN_00421100` does, then re-measure the pose band
  against `battle-hud.webp` (the instrument that produced 0.2747).
* **Result (in progress, commit `563a3e3` is scaffolding, not the close).**
  `xm::Controller` already carried 8 tracks with an ordered weighted blend,
  so the first gap was the bind: added
  `Controller::setAnimationBothTracks()` (the `FUN_00421100` starting state)
  and `Fighter::try_switch_animation()` now uses it on both the mapped and
  fallback paths. The weight fields `FUN_0041f580` consumes are the per-track
  table at `player+0x75e0 + i*0x38` (track 0 at `+0xc`, track 1 at `+0x10`)
  plus the cross-fade counters at `+0xae14/0xae18` — read, not guessed
  (the `+0xc/+0x10` mapping derives at `research/decompiled/FUN_00421410.c:30-35`:
  the two `0x3f800000` writes land exactly on those slots).
  **Correction 2026-10-03:** the `563a3e3` entry reported "idle band
  unchanged at 0.2772" — that number is the **scene-floor control band**
  (`tests/hud_bands.py --bands scene-floor` on the post-change capture
  `/tmp/bh_p0.ppm` re-runs at 0.2772), not the pose band (0.2747 in commit
  `8fae1f9`). Scene-floor is pose-insensitive by construction
  (`hud_bands.py`: "scene-only control"), so the reading is vacuous as pose
  evidence; and the no-op is analytically guaranteed anyway (same set, same
  `t=0`, weights 1.0/1.0 through the incremental blend is `mix(v,v,·) = v`).
  **Still open after `563a3e3` (the rest of the sketch):** the
  interrupt-side rebind — `FUN_00421240` (track-1-only) with its driver
  `FUN_004211f0` — and `FUN_0041f580`'s per-tick weight evolution are
  unported; the port binds once per state and ticks both tracks identically,
  so track 1 can never diverge. Within-move phase advance
  (`FUN_004212f0`'s cursor over the `.dat` phase durations) is a further,
  separate step. Then re-measure a **pose-relevant** band
  (`per-fighter` / `ring` / `com-bar`, or the `8fae1f9` pose protocol),
  never scene-floor.
* **Result (continued 2026-10-03 — move-change blend ported).** The
  interrupt path is now in place: `Fighter::set_state` keeps the old set on
  track 0 and binds the new set on track 1 from t=0
  (`FUN_004211f0`/`FUN_00421240`), `tick_blend()` ramps the weights
  1->0 / 0->1 over `kAnimBlendTicks = 8` ticks (INFERRED duration — the
  `+0xae14/0xae18` initial value was not located; only the decay/rise
  mechanism is read), then `commit_blend()` restores the both-tracks steady
  state. Mid-blend interruptions only retarget track 1 with the live weights
  preserved, so the pose never snaps; `init`/`reset` share a `clear_tracks`
  fresh bind. A/B against the pre-blend binary (stash-built) on the
  BattleStart(43)->Idle(0) transition, per-fighter band RMSE:
  frame 55: **0.0000** (pre-transition control), frame 61: **0.0536**,
  frame 64: **0.0508**, frame 68: **0.0000** (committed), frame 75:
  **0.0000**, and frame 150 byte-identical — the composite exists exactly
  inside the 8-tick window and converges to the same steady state, so all
  static parity numbers stand. `fighter_script_test` case 12 pins the
  semantics (track-1 target, weight ramp, commit, interruption retarget).
  **Remaining:** within-move phase advance (`FUN_004212f0` cursor + phase
  durations from the `.dat` move table, still unparsed — the STL-serialized
  map layout defeated a transcription attempt), the blend duration, and any
  print-parity gain (none expected: the print is steady-state idle).
* **Overlay negative result (this pass).** The two dev-only tools added in
  `a96f6bf` (`tools/anim_sets_dump.cpp`, `tools/anim_frames_dump.cpp`;
  build with `g++ -std=c++17 -O1 -I src -I third_party/glm
  tools/anim_sets_dump.cpp -o /tmp/asd`) were built to hunt base
  (full-body) vs overlay (arms-only) sets. Run on `data/rena/00.X`: all
  **124 sets are full-body** (typical 37 bones incl. legs+torso; minimum 14
  bones on set 17, none arms-only). No base/overlay split exists in the
  shipped sets, which constrains what the composite can be: same-set binds
  plus cross-faded phase changes, not bone-masked overlays (D3DX tracks have
  no bone masks anyway).
* **Weapon (separate, not started).** The print's raised blade is why the
  capture can't match the band, and it is a distinct task from the track
  composite. Measured on the install: `data/bullet/001/03.X` (rena's weapon-1
  cleaver) has **one** anim set (`dur=880`, verified with
  `tools/anim_sets_dump.cpp`) — the idle pose needs no weapon anim at all,
  the weapon must stay rigid on the hand bone. Three gaps, each blocking:
  (a) the per-weapon local offset (`FUN_00433eb0`, position + rotation
  floats read from `data/item/*.dat` at `FUN_00433eb0.c:93-110` and passed
  to `FUN_0042fe90`) is un-parsed — `loadWeapon` (`src/assets/scene.h`)
  attaches to `Bip01_Prop1` with no offset, so a loaded weapon sits
  un-rotated on the hand; (b) **hypothesis, unverified:** the weapon's ring
  mesh may show its black background instead of vanishing — but the stated
  mechanism ("no alpha-test") contradicts `src/render/scene_renderer.cpp:470`,
  where every textured draw gets `kDrawAlphaTest`, so if the symptom is real
  the cause is likelier the texture's own alpha (or an untextured mesh), and
  no ring mesh has even been identified (the file's 3 meshes are unnamed);
  needs a weapon-in-frame capture before it is claimed; (c) **hypothesis,
  unverified:** the single set was described as "the spin", but no
  rotation-key analysis was done (3 channels on 3 unnamed bones), and nothing
  in the tree drives weapon animations today. None of these is part of B2.

### B3. Mips: feed the shipped levels instead of the box chain

* **What.** The renderer builds a 2x2 box chain for stage textures; the
  original's own filtered levels ship as `X_1.cnv`/`X_2.cnv`.
* **Evidence (measured).** Commit `429ccf8`: shipped levels differ from the
  box chain by ~12/255 (`アスファルト05_1`) and ~1.6/255 (`shadow01_1`);
  only stage dirs ship them (85 groups in `stage01`, 94.7% of its referenced
  textures); the original walks `%s_%d.bmp` and fills one level per file
  (`FUN_00656c80.c:87-118`). `src/assets/cnv.h` has no level concept (it
  decodes one image per name), and `src/render/scene_renderer.cpp:389-426`
  generates the chain with `mipLevelCount`. The siblings are on disk and
  plentiful (`data/stage01/` has 143 `_[12].cnv` names — counted on the
  install), and the asset source reads by name, so they should resolve
  through the bundle path; **not yet verified through a bundle lookup**.
* **Sketch.** In the stage-role texture load, probe the `_1`/`_2` sibling
  names before `.cnv`, and when present upload those levels instead of the
  box levels; keep the box chain as the fallback for the ~5% with no shipped
  art and for every non-stage role. Regression checks: level 0 write stays
  byte-identical, and the stage band against `battle-hud.webp` improves past
  0.254041.
* **Result (done, mechanism faithful, print number honest).**
  `mipSiblingName()` / `mipShippedDimsOk()` (`scene_renderer.h`, unit-tested
  in `lighting_test`: name surgery, the width gate, the one observed misfit)
  plus a substitution loop at the stage-role upload: levels 1–2 upload the
  shipped bytes when the sibling resolves through the same bundle-first
  cache at exactly the halved dims, else the box level stays. The chain
  truncates to the shipped depth — `D3DXCreateTexture`'s `MipLevels=1+#files`
  (`FUN_00656c80.c:87-118`: load loop breaks on first miss, per-level copy
  gated on width) — so sampling past the smallest shipped level clamps
  there as on the original. Verified live: 166 substitutions in the stage01
  capture (bundle path — the sketch's "not yet verified" is now verified);
  dims survey: all 85 `_1` exact, 57/58 `_2` exact, the one `_2`-sized-like-
  `_1` truncating to a clean 2-level chain. Draws unchanged (177/177/0);
  level 0 is the same bytes through the same path by construction.
  **Measured (pinned recipe, SPEC §7):** overall 0.2567 → **0.2596**,
  hud-all 0.2483 → 0.2522, scene-floor 0.2772 → 0.2777 — the print number
  moves the *wrong* way, and the sketch's "past 0.254041" is not met (that
  figure itself does not reproduce on the pinned recipe: current baseline is
  0.2567 — flagged, not chased). Two variants were tried first (full chain
  with shipped L1/L2: 0.2591; truncated: 0.2596); truncation ships as the
  structure-faithful one. **Why this is instrument error, not render error:**
  grain energy in the wall band reads print 4.33 < box 5.63 < shipped 7.60 —
  the lossy resampled print is smoother than *both* renders, so the overall
  RMSE rewards blur and cannot adjudicate the sharpness the shipped levels
  restore (visual triple-check: print mush vs box mottle vs shipped grain).
  The bytes are authoritative; the +0.003 overall residual is recorded as
  print-pipeline confound. Open and un-actionable: whether D3D9 and WebGPU
  pick identical LODs at these pixels (same trilinear math, possibly
  different derivative conventions) — no experiment available distinguishes
  it from correct rendering, so it stays a note, not a task.

## C. Animation states

### C1. Guard / Jump mapping (TagOut reframed, see below)

* **What.** Two states keep the reported set-0 fallback instead of their
  real animation; a third was a mistaken mechanic.
* **Evidence (inferred, from the port's own RE notes, corrected 2026-10-03).**
  `src/gameplay/fighter.h:146-163`: guard's voice keys exist (indices 12/13,
  shipped for all 12 characters) but the corpus holds no `FUN_0064ae10`
  key-12 play site, so the "no call site" result now rests on two independent
  searches; blocking may be a damage-path flag rather than a move id at all.
  Jump: the port's leap/fly/fall may span several of `FUN_0043ded0`'s air
  branches (`FUN_00421080(0x168/0x15e/0x1cc/500/0x1f5)`), and pinning one
  needs the jump input-bit mapping, which is not located; `FUN_004235d0` is
  steering (relation index + relative angle from `FUN_0041f580`), not the
  jump driver as earlier notes claimed. `Fighter::anim_fallback()`
  reports each case, so the gap is visible. The move-id switch itself is 49
  cases in `FUN_00428510` (count from commit `8fae1f9`; not recounted here).
* **TagOut — reframed, not mapped (owner observation 2026-10-03).** There is
  no character swap: control never transfers between fighters, and the only
  switch mechanic is the reticle target cycle (`FUN_00421e30`, which also
  plays the 0xd/0xe/0xf switch cues). The swap story traces to old PT
  `remake/docs/roadmap.md:127-128`, an inference from voice-dir names
  (`tagfront`/`tagback`/`tagOK`) that `remake/docs/game-spec.md:93` and then
  `fighter.h` repeated. Those keys sit between `tactics` and `thank` in the
  16-byte key table — a team-communication cluster (orders, callouts,
  thanks), consistent with COM-partner coordination, not a swap. Consequences
  landed: the `TagOut` state (never entered by anything) keeps its fallback
  with corrected comments; LockSwitch tap now cycles the camera target in
  match mode beside the DX9 combo (camera-only in this 1v1 port — shots fly
  the facing, which tracks the single enemy; hold-for-ally needs allies).
  "recovery" stays as the state's trace name (the voice key exists; the
  state never occurs, so no trace changes).
* **Sketch.** (a) Jump: map the jump input bit first, then read which of the
  `FUN_0043ded0` air branches it selects — not the reverse. (b) Guard: look
  for the block flag read on the incoming-damage path, not another
  `FUN_00428510` case hunt (46 labels, ~40 unclaimed — blind). (c) TagOut:
  closed as reframed above; the remaining switch work is multi-enemy
  reticle/aim, not animation.

## D. HUD leftovers

The HUD's remaining gaps are listed verbatim in commit `0294916`'s "Still
open, deliberately" paragraph; the pointers below are from
`BATTLE-HUD-SPEC.md`. Rewritten 2026-10-03 in plain language: each item now
says what you SEE on screen, not just which function draws it.

### D1. The top-right counter `181` — DONE (it is the render-FPS counter)

* **What you see.** Yellow 3D digits at the top-right edge reading `181`.
  Owner-confirmed: this is the **rendering FPS counter** — fixed-timestep
  logic underneath, uncapped rendering on top (which is also why netplay
  stays deterministic), and the number floats with machine speed, render
  only, never logic.
* **How the original draws it.** `FUN_006396f0` (the per-frame battle render)
  draws `DAT_006d18a4` right-aligned at x=800, y=0, scale 0.5
  (`FUN_00431b20(DAT_006d18a4, 0x44480000, 0, 0x3f000000, 0)`), unconditionally
  — no gate surrounds the call, so it is always on in battle. The value is a
  render-thread present count (`FUN_006580a0` bumps `DAT_006d18a8` per
  present in a worker thread; the per-second reduction into `DAT_006d18a4`
  was not located and does not matter — the port measures its own presents).
  A sibling counter draws two `FUN_0063bf40` counts at x=20 top-left; its
  values are unmapped (decompiler arg confusion) and out of scope.
* **What the port does.** `HudFont::SmallYellow` (`hud_atlas.h`: P00 row
  y288–319, 32 px cells, pitch 32, leading 0 — measured off the atlas; the
  old Q5 guess bands were wrong, and a 28 px pitch fails at cell 6),
  `HudState::fps` (default 60), drawn in `composeBattle` at (800,0,0.5).
  The App meters wall-clock renders over a rolling half second; fixed-dt
  captures pin the display at 60 so `--out` frames stay deterministic
  (a live counter would make `hud-all` nondeterministic run to run).
  Unit-tested (`hud_sprite_table`: the "181" layout — units x=784 stepping
  16 px left — plus the font spec). Measured: our "60" ink is game
  (772–796, 2–7) against the print's (763–793, 2–7) — same height (scale
  confirmed), same right edge family (anchor 800 in both; 3 px is
  threshold noise), narrower only because "60" is two digits. Draws
  unchanged (177, HUD is one batch).
* **Not this.** The `DAT_006cf3c4` top-centre counter and `FUN_0064c1e0`
  are a different element; the sketch's old next step is retired.

### D2. The mirrored second ring — DONE (counter-rotating arcs)

* **What you see.** The red ring around the targeted fighter is really two
  arc groups sweeping opposite ways (in the print: arcs above, below, left
  and right of her — one P03 four-arc cell drawn twice, counter-rotated).
* **How the original draws it.** `FUN_00643230` draws the P03 ring cell once
  rotated `+(frame/2 + 9*hud+0x30c)`, then — gated on local_31, i.e. this
  fighter is the viewer's locked target — draws the same cell at the same
  anchor/scale rotated `-(frame/2)` with NO 9-term (`0x643545-0x64354b`).
* **What the port does.** `composeFighters` now draws both arcs under the
  existing `f.target` gate (the target-valid half of local_31 is implied).
  Verified structurally (same cell/anchor/scale, mirrored rotation, correct
  gate) and visually across frames (arcs at ±50° in frame 100 vs ±75° in
  frame 150 — counter-rotation live). Single-frame RMSE is phase lottery
  (0.3888 → 0.4025: added red pixels at non-print phases), so the band is
  reported, not chased — same confound class as the mirrored fighter pose.
* **Resolved 2026-10-03.** The lock-switch writer/decrement and pulse
  transform are implemented and tested; see the implementation update above.

### D3. Other fighters' com bars, round countdown, team stings — PARTIAL (1v1 transients implemented)

* **What you see (and don't).** The print shows exactly one com bar with its
  `com` tag, over the targeted (distant) fighter — which is exactly what the
  port draws (target's drawer, `0x643e38`: frame + ghost + live fill + tag
  cell). Nothing is missing in this frame.
* **Why the rest stays out.** The "other-fighters bar" (a different sprite
  set in `FUN_00643230`'s per-fighter loop) only matters with 3–4 fighters
  on screen (allies, extra enemies); this port's match is 1v1, and the
  followed fighter correctly carries no bar. Round countdown (`3 2 1`) and
  team stings (`赤組/青組 大勝利`) are transients absent from the print and
  need new gameplay state first (round timer, winning team in
  `gameplay::Match`/`MatchEconomy` driving `HudState`); their art and layout
  are already surveyed (`BATTLE-HUD-SPEC.md` §5 item 7, `P09/P04/P05/P08`
  via `FUN_00633ca0.c:77-86`). No parity pixels depend on any of it.
* **Sketch.** (a) Other-fighters bars come with the third fighter, not
  before. (b) Countdown/stings come with `Match` round state — gameplay
  breadth, not parity; schedule it with the front-end track (E), not here.

## E. Front end (`FRONTEND-PLAN.md` is the spec)

The plan's own order: **select page 0 → select page 1 → the rest**. Title
already landed on the screen stack (`src/ui/screen_title.*`, commit
`c67ead3`), so new screens follow that pattern: device-free update returning
the next screen id, a factory for construction, tests against fakes.

### E1. Select page 0 — IMPLEMENTED (four-fighter presentation remains open)

* **What.** One state machine for team → character → weapon → hypermode →
  PLAYER/COM → ready, covering **six of the 23 prints** (team-select,
  char-select, weapon-select, hypermode-select, controller-select,
  ready-confirm — plan lines 102-107, 1152).
* **Evidence.** Layout and per-slot states: plan §2.3-2.8 (lines 338-507);
  file plan: `src/ui/screens/select.cpp` (line 1092). Its one remaining
  extraction job is the 16-cell roster grid table inside `FUN_0040b2b0`
  (plan §7 item 1, lines 1247-1252); the second open geometry is the
  team-select diamond's **y anchor 150 px below** the measured centres
  (pivot vs quadrant origin, plan §2.3 lines 355-359).
* **Sketch.** First transcribe `FUN_0040b2b0`'s anchor/cell tables
  (mechanical read), reconcile the diamond y anchor against the print, then
  implement the screen on the landed stack. The roster grid formula is
  plan §2.17.

### E2. Select page 1 — IMPLEMENTED (original match-rule fidelity remains open)

* **Evidence.** Contract fully extracted (plan §2.9, lines 508-568): five
  knobs, their domains/steps, the eight-row list, confirm returns 9 = VS
  intro. Assets `sbg00`/`pbg01`/`pbg02`/`P01`; numerals through
  `FUN_00431b20`/`FUN_00431ce0`. **Blocker:** the stage variation count —
  the count byte at `scene+0x3d90` and the default 2-way cycle vs the three
  names in `pbg02.cnv` need one on-screen cycle capture (plan §7 item 5).
* **Sketch.** `src/ui/screens/stage_select.cpp` writing `MatchConfig`
  (plan line 1093); capture the variation cycle with the original to settle
  the count.

### E3. Options and key config — PARTIAL (three renderer controls unavailable)

* **Evidence.** Plan §1.3: both optional/deferrable. Option scope is tiny
  and closed — 4 toggles + 4 sliders (`option-screen.webp`); key config's
  binding reference is already in `src/input/input.h`, so the screen is a
  luxury (plan §2.10/§2.11, lines 569-613).
* **Sketch.** Two small screens on the same stack; wire the volume sliders
  to `fnd::audio` (the backend already has a UI channel,
  `src/audio/audio.h:26`). Defer toon/shadow toggles until the effect
  system exists (item B1).

### E4. VS intro (scene 9) — IMPLEMENTED for 1v1

* **Evidence.** `vs-intro.webp`; draw functions `FUN_004115f0`,
  `FUN_00411ae0`, `FUN_00411cb0` (plan line 112, §2.12 line 614); the
  plan's coverage table says the draw function and coordinates are read.
* **Sketch.** A skippable transition screen with the entry tween; portraits
  slide in and the VS animates centre.

### E5. The result sequence (sting → quote → report) — PARTIAL (titles/quote selection remain open)

* **Evidence.** Three beats in one screen: victory sting (`FUN_00633ca0`
  loads `P05`/`P08`), quote (`FUN_00635d40` result phase, sub-phase 0, GDI
  text), report (`result-report.webp`). The report's layout function is
  **not isolated** (plan §7 item 2, lines 1253-1256; coverage line 837).
* **Sketch.** One screen with three states; treat the report page as new
  work measured from the print with a pixel check, per the plan's own
  instruction.

### E6. Soft keyboard — DONE as reusable widget

* **Evidence.** The grid **is** the name font: `data/chat/name_p1.cnv` grid
  cells (ASCII/kana), names stored as `(cellX,cellY)` pairs via
  `FUN_00646bd0`; action bar `network/nameMenu.cnv`; host scene known
  (scene 13), the widget function is not isolated (plan §2.16 lines 713-755;
  the name-font identity at lines 744 and 879; §7 item 4, lines 1259-1260).
* **Sketch.** Build the reusable widget as the plan schedules it
  (`src/ui/soft_keyboard.*`, line 1097); needed only when names are
  editable, so host it in the netplay track later.

**The plan's thin-RE list (`FRONTEND-PLAN.md` §7) is the checklist for all
of E:** the `FUN_0040b2b0` / `FUN_004072b0` anchor tables, the result-report
composition, the KO trigger (its art is located in `P09`, the firing
sequence is not — §7 item 3), the soft-keyboard widget, the stage variation
counts, and the team-select diamond's y anchor discrepancy. Scenes 2 and
14–19 and scene 5 stay story-mode scope by D6.

## F. Audio

### F1. A seam from the screen layer to the audio backend (menu SEs) — DONE

* **What.** Menu cursor/confirm SEs are silent: the screen stack returns an
  action but cannot play a sound.
* **Evidence (measured).** `src/ui/screen_title.h:76-79`: the screen returns
  `TitleAction::{Moved,Activated}` "so the caller can play the SE the
  original plays there (`FUN_0064aed0`: 0 on confirm, 2 on a cursor move)
  without the state machine needing an audio seam. Audio is not wired on
  this screen yet". The ids and the full mapping (0 決定, 1 戻る, 2 cursor,
  3 lock/ready) are in plan lines 279-280, 309-311. The backend exists and
  reserves channel 0 for UI (`src/audio/audio.h:26`).
* **Sketch.** Give the screen host in `main.cpp` a small SE callback (or map
  `TitleAction` there) and load the SE bank through the existing audio
  backend; count plays under a headless run the way `--audio-test` does.

## G. Verification debts — do not make these claims yet

### G1. Web — GAME DATA VERIFIED on software WebGPU; hardware/visual check remains open

* **Evidence (measured).** `BUILD-web.md:32-47` records a real run —
  Chrome for Testing 152 headless, SwiftShader, 845 frames, 60.1 fps,
  `RESULT: ok`. The same file documents the asset-preload build as
  *expected* output (`:54-74`) and its own "Not verified" list: canvas
  screenshots come back black headless, and only SwiftShader has been
  exercised (`:107-116`). So the corrected statement is: the **plain web
  demo** has been executed; a browser run **with game data and the versus
  scene** has not, nor has a hardware adapter.
* **Sketch.** Run the `FOUNDATION_WEB_ASSETS` build against `data/`, record
  the console numbers in `BUILD-web.md`, and only then extend the claim to
  the game; the screenshot path needs an X server that outlives the command
  (`--headed`).

### G2. macOS: never executed

* **Evidence.** `README.md:189` ("not attempted — no Mac available"),
  `PORT-PLAN.md:11-12`, `MEDIA-INPUT.md:179`, `WEB-ASSETS-RUNTIME.md:242`,
  and D2's macOS bullet all agree. No execution evidence exists anywhere.
* **Sketch.** Either keep the explicit "unverified" status (the honest
  default every doc currently uses) or do a first run on real hardware:
  wgpu-native prebuilts + `sdl3webgpu`'s Metal path, `foundation_demo`
  offscreen, and record the adapter/backend lines. Nothing in the code is
  claimed to block it; nothing has been run.

### G3. Texture coverage: two install data gaps, checked by `tests/showcase.py`

* **What.** Full texture coverage of the asset pipeline has **not** been
  claimed. A 16-character × 13-stage sweep found 43 untextured draws, all
  reducing to gaps in the installed game data — not loader bugs. This is the
  baseline to re-check in the future.
* **Evidence (measured, this pass).** `tests/showcase.py --check` runs every
  (character, stage) pair headless and reads the demo's own
  `draws: N (X textured, Y untextured)` line, so the loader is the oracle.
  Result: **165/208 pass, 43 flag, zero pipeline failures**. The 43 reduce to
  two install gaps:
  - **stage05 / stage15** — the stage `.X` scenes name dust/particle
    textures as `.bmp` (e.g. `01`–`05`, `08`, `11`) that have no `.cnv` in
    these two dirs; the cache resolves `.bmp`→`.cnv` and misses 4 per stage,
    on every character.
  - **kasai** — `data/kasai/00.X` references a `g` texture present
    **nowhere** in the install (checked `g.cnv`/`g.bmp` across `data/`);
    2 untextured draws on every stage.
  Both are data the install does not ship, so the loader is doing the right
  thing (reporting the miss, not fabricating a texture).
* **Check in the future.** Re-run `tests/showcase.py --check` after any
  install update, re-extraction, or new character/stage. The two gaps above
  are the known baseline; any **new** untextured draw is a regression (a
  loader or cache bug), not a data gap, and needs investigation.

## H. Out of scope (stated, not scheduled)

* **Netplay and video stay out of scope by D6** (LAN netplay is a
  design-first Phase 4; story-mode video stays stubbed). They are named
  here only so the next session does not re-litigate it: the versus loop and
  the front end come first.
