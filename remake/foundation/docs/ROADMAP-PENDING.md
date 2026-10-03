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
  height). The slot is the fighter's own `+8` field, read as the index arg
  (Ghidra elides it in `FUN_0041dcb0`'s `FUN_00423420(param_1+5, param_1[2])`
  call — the `+5` is the *dest* `fighter+0x14`, the `[2]` is the *index*
  `*(fighter+8)`; confirmed against the bytes at `0x41dcb0`). `FUN_0064ab30(i)`
  creates the four fighters in slot order 0..3, so **P1 takes `points[0]` and
  P2 `points[1]`** — the two `z=-2200` points in stage01/stage21. The port's
  `readEnv` + `points[0]`/`points[1]` default was already correct; the old
  "trace A/B only matched with `--spawn2`" was matching the deleted DX9
  build's hardcoded pair, not the original's env.dat pick. Provenance added to
  `src/main.cpp` (`initMatch` comment). No code change required.

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
  `(-463,200,-2200)`, P2 at `points[1]`** — landing exactly on the documented
  0.2755 floor, and corroborating A1 (P1=`points[0]`) by an independent method.
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
  `data/effect/000.dat` (measured header: u32 mesh count, then 4-byte
  NUL-padded names — slot 000 names `14.X`, the hitC-textured card), and in
  match mode assets 1–2 are `data/aura/00.X`, `FUN_00633ca0`'s first aura
  slot. The gameplay `EffectEventQueue`s (`game/effect_events.h`) are no
  longer drained to nothing: `updateFxCards` owns the live card set (spawn /
  kill-by-id / ttl expiry) and `placeFxCards` writes the per-frame model
  matrices, so the existing `Pass::Effect` additive pass and cylindrical
  billboard (`scene_renderer.cpp`) draw them. The aura follows fighter state
  through the fighter's own model matrix, in local space, exactly where the
  cube used to. `--debug-prims` is the A/B: with it, the old all-cube view
  (aura cube included) renders and the cards are hidden; without it, the
  cards render and the aura cube does not. Shot/spark cubes stay as-is:
  their real VFX are trails, which remain RE-blocked below. Two measured
  facts the port needed: the cards' textures ship split across two
  directories (the hitC*/muzzle/aura `.cnv` set sits in `data/aura/`, the
  hitb*/g* set in `data/effect/`), so the card texture cache falls back from
  the card's own directory to `data/aura/`; and `aura/00.X` is a 54.6-unit
  icosahedron-ish blob while `effect/14.X` is a 137.4-unit quad plus four
  76-unit beams, which is why no scale factor was needed in the first pass.
  **Unknown (unchanged):** the slot→fighter rule for `FUN_00633ca0`'s seven
  aura slots (both fighters share slot 0 for now), the per-effect factors
  (sketch b), and the trail strip (sketch c).
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
  clones **two controllers per model** (`FUN_00464d94`) and the `.dat`
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
* **Result (done, commit `563a3e3`).** `xm::Controller` already carried 8
  tracks with an ordered weighted blend, so the gap was the bind: added
  `Controller::setAnimationBothTracks()` (the `FUN_00421100` starting state)
  and `Fighter::try_switch_animation()` now uses it on both the mapped and
  fallback paths. The weight fields `FUN_0041f580` consumes are the per-track
  table at `player+0x75e0 + i*0x38` (track 0 at `+0xc`, track 1 at `+0x10`)
  plus the cross-fade counters at `+0xae14/0xae18` — read, not guessed.
  **Measured:** the idle band is unchanged at **0.2772** — at bind time both
  tracks hold the same set at weight 1.0, so the weighted blend is a no-op
  and the composite only diverges once `FUN_0041f580` starts cross-fading
  track 1. The track mechanism is the foundation for that cross-fade, now in
  place; it does not by itself move the static idle band.
* **Weapon (separate, not started).** The print's raised blade is why the
  capture can't match the band, and it is a distinct task from the track
  composite. Measured on the install: `data/bullet/001/03.X` (rena's weapon-1
  cleaver) has **one** anim set — the spin (`dur=880`) — so the idle pose
  needs no weapon anim at all, the weapon must stay rigid on the hand bone.
  Three gaps, each blocking: (a) the per-weapon local offset
  (`FUN_00433eb0`, position + two rotations) is un-parsed, so a loaded weapon
  sits un-rotated on `Bip01_Prop1`; (b) the weapon's ring mesh renders in the
  opaque pass with no alpha-test, so its black background shows instead of
  vanishing (the additive effect pass would make black add zero); (c) driving
  its single set makes it spin in idle. None of these is part of B2.

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

## C. Animation states

### C1. Guard / Jump / TagOut mapping

* **What.** Three states keep the reported set-0 fallback instead of their
  real animation.
* **Evidence (inferred, from the port's own RE notes).**
  `src/gameplay/fighter.h:136-143`: guard's voice keys exist (indices 12/13)
  but no call site with a constant move key was found; the air state comes
  from the locomotion system `FUN_004235d0`'s `{state,dir,timer}`, not a
  move id, and its animation consumer was not located; "recovery" is a voice
  key, and the 2v2 tag animation is un-RE'd. `Fighter::anim_fallback()`
  reports each case, so the gap is visible. The move-id switch itself is 49
  cases in `FUN_00428510` (count from commit `8fae1f9`; not recounted here).
* **Sketch.** (a) Locate the locomotion system's animation consumer (who
  reacts to `FUN_004235d0`'s state) and bind its set for Jump. (b) Find
  guard's move id among the `FUN_00428510` cases the port's table does not
  claim, checking it against the move list in the character `.dat`s.
  (c) Leave TagOut on the fallback until the tag mechanic itself is ported.

## D. HUD leftovers

The HUD's remaining gaps are listed verbatim in commit `0294916`'s "Still
open, deliberately" paragraph; the pointers below are from
`BATTLE-HUD-SPEC.md`.

### D1. The top-right counter `181`

* **Evidence.** `BATTLE-HUD-SPEC.md` §6 Q1 (lines 251-258): the only
  `DAT_006cf3c4` counter (`FUN_00644150.c:177-198`) anchors top-**centre**
  with a different digit colour; the print's `181` is top-right
  (`(761,0)-(797,12)`) in P00 yellow. The next step named there is reading
  `FUN_0064c1e0` (`0x0064c1e0`, called from `FUN_00644150.c:213` when
  `DAT_006cfdb0 == 2`); `FUN_00431b50`'s signature is also contradictory.
* **Sketch.** Read `FUN_0064c1e0` and rescan P00's small-digit bands for the
  yellow set (Q5: `y 210-250` and `y 308-330`); then draw at the print's
  anchor, gated the way the original gates it.

### D2. The mirrored second ring and the `9*hud+0x30c` angle term

* **Evidence.** Commit `0294916`: "the mirrored second ring and the
  `9*hud+0x30c` angle term (unidentified field)". The port draws one ring,
  substituted as `f.ringDeg + hudFrame*0.5` (`src/ui/hud.cpp:362-369`,
  `src/ui/hud.h:79`, `src/game/hud_values.h:35`).
* **Sketch.** Identify the HUD struct field at `+0x30c` as read in
  `FUN_00643230` (`@0x64344d`) and whether the second ring is the same
  drawer with the mirrored cell (the print's two arcs); then add the mirror
  and the real angle term, re-measuring against `battle-hud.webp`.

### D3. Other fighters' com bars, round countdown, team stings

* **Evidence.** Commit `0294916`: the print's com bar is the **target's**
  drawer (`0x643e38`); `FUN_00643230`'s other-fighters bar is a different
  sprite set and is not drawn. Round stings have assets and layout
  (`BATTLE-HUD-SPEC.md` §5 item 7: `P09/P04/P05/P08` via
  `FUN_00633ca0.c:77-86`) but "the demo's match has no round timer or
  winning team to drive them".
* **Sketch.** (a) Port the per-fighter bar (frame, ghost fill, live fill,
  tag cell) for every visible fighter. (b) Add round-timer and
  winning-team state to `gameplay::Match`/`MatchEconomy`, then drive the
  `3 2 1` countdown and the `赤組/青組 大勝利` sting through `HudState`.

## E. Front end (`FRONTEND-PLAN.md` is the spec)

The plan's own order: **select page 0 → select page 1 → the rest**. Title
already landed on the screen stack (`src/ui/screen_title.*`, commit
`c67ead3`), so new screens follow that pattern: device-free update returning
the next screen id, a factory for construction, tests against fakes.

### E1. Select page 0 — the recommended next screen

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

### E2. Select page 1 — STAGE SELECT + BATTLE SETTING

* **Evidence.** Contract fully extracted (plan §2.9, lines 508-568): five
  knobs, their domains/steps, the eight-row list, confirm returns 9 = VS
  intro. Assets `sbg00`/`pbg01`/`pbg02`/`P01`; numerals through
  `FUN_00431b20`/`FUN_00431ce0`. **Blocker:** the stage variation count —
  the count byte at `scene+0x3d90` and the default 2-way cycle vs the three
  names in `pbg02.cnv` need one on-screen cycle capture (plan §7 item 5).
* **Sketch.** `src/ui/screens/stage_select.cpp` writing `MatchConfig`
  (plan line 1093); capture the variation cycle with the original to settle
  the count.

### E3. Options and key config

* **Evidence.** Plan §1.3: both optional/deferrable. Option scope is tiny
  and closed — 4 toggles + 4 sliders (`option-screen.webp`); key config's
  binding reference is already in `src/input/input.h`, so the screen is a
  luxury (plan §2.10/§2.11, lines 569-613).
* **Sketch.** Two small screens on the same stack; wire the volume sliders
  to `fnd::audio` (the backend already has a UI channel,
  `src/audio/audio.h:26`). Defer toon/shadow toggles until the effect
  system exists (item B1).

### E4. VS intro (scene 9)

* **Evidence.** `vs-intro.webp`; draw functions `FUN_004115f0`,
  `FUN_00411ae0`, `FUN_00411cb0` (plan line 112, §2.12 line 614); the
  plan's coverage table says the draw function and coordinates are read.
* **Sketch.** A skippable transition screen with the entry tween; portraits
  slide in and the VS animates centre.

### E5. The result sequence (sting → quote → report)

* **Evidence.** Three beats in one screen: victory sting (`FUN_00633ca0`
  loads `P05`/`P08`), quote (`FUN_00635d40` result phase, sub-phase 0, GDI
  text), report (`result-report.webp`). The report's layout function is
  **not isolated** (plan §7 item 2, lines 1253-1256; coverage line 837).
* **Sketch.** One screen with three states; treat the report page as new
  work measured from the print with a pixel check, per the plan's own
  instruction.

### E6. Soft keyboard

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

### F1. A seam from the screen layer to the audio backend (menu SEs)

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

### G1. Web: the plain demo runs; the game assets in a browser do not

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
