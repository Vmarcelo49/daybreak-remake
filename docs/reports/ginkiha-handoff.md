# Handoff — Phase 2 combo porting (`ginkiha-help` branch)

To the next agent: continue porting character+weapon combo shot programs exactly as below.
Everything here is verified against the workspace — trust files over memory.

## 1. What this is

Port of Higurashi Daybreak's combat/animations (DaybreakDX.exe, SHA256
`27e61475…a6a07f02`) into `remake/foundation/src/gameplay/`, driven by combo tables
recovered by Ginkiha. Plan (PT): `docs/reports/ginkiha-port-plan.md` (has a phase-status
table — keep it updated: completed = date+time, pending = date only). Comparison:
`docs/reports/ginkiha-comparison.md`. Goal object `goal-91adad8f…` stays active until
Phases 2–5 are done; do not mark complete early.

## 2. Sources (read-only, NEVER committed)

- `.local-analysis/balance-reference/balance-reference-v0.10/` — `reference-data.json`
  (roster 46, magazines, params), `catalogs/` (attack-preview, combat-hooks, exe-catalog,
  timing-hooks). Git-ignored via `.git/info/exclude`. Never add to git.
- `.local-analysis/porting-support/DaybreakPortingSupport-20261010/` — `catalogs/`,
  `evidence/*.tsv/*.md`, `traces/*.jsonl`, `reference/source/*.hpp` (recovered C++ bodies
  `shoot_body_<ch>_<we>_<state>`), `reference/original_tools/`, `assets/decoded/` (46 actor
  DATs + item/bullet DATs). Verified bundle (verify_bundle.py passes).
- `.local-analysis/pilot-rena0-mion0.md`, `.local-analysis/cancel-matrix-{shot,melee}.json`,
  `.local-analysis/RELATORIO-combate-daybreak.md` — working notes (git-ignored).
- `Higurashi-Daybreak/` — local game install (git-ignored). Tests need it; CI skips without it.

## 3. Branch state (2026-10-09, suite 65/65 green)

- Branch `ginkiha-help`, forked off `main` WITH the user's uncommitted Windows work
  (`remake/foundation/CMakeLists.txt` WIN32 hunks, `BUILD-windows.md`, package files, etc.).
  **Never stage or commit those files.** Before every commit, `git status` + stage ONLY your
  files; the CMakeLists Windows hunk must stay unstaged (use `git apply --cached` with an
  extracted hunk if you touch that file — precedent exists in history).
- Push scope per AGENTS.md Git section; never commit: `research/recomp/`, game files,
  `*.full.json`, `remake/foundation/build/`, `third_party/`, `.local-analysis/`.

## 4. The combo pipeline (the mold — follow it exactly per combo)

1. **Rank**: usage pairs per combo (`shot400_usage` keys `ch:we:r`): pick the richest unported
   combo. Done so far (usage order): Rena 0 (pilot), Mion 0, Rika 1, Tomitake 2, Keiichi 2,
   Chie 2, Kasai 1, Takano 0, Irie 1, Mion 2, Rika 2, Satoko 0, Rika 0. Since then,
   Rena 1 and Natsumi 0 landed as limited normal subsets; Akane 2 is pinned/deferred.
   Keiichi 0 is pinned/deferred on hand-origin launch support; Keiichi 1 is next to recon.
2. **Recon** (one bash + python): swap/item/actor/params/mags from `reference-data.json`;
   dispatch+usage from `combat-hooks.json`; births from `attack-preview.json` (`swap:slot`);
   walks from `exe-catalog.json`; traces fire events per variant. Delimit bodies:
   `grep -n "^inline void shoot_body_<ch>_<we>_{400,402,450,460}" reference/source/shoot_native_bodies_20260929.hpp`.
3. **Delegate the body read** to ONE tight subagent: 4 named functions with EXACT line ranges
   (+grep for the ends), ask for phases/fire-ticks/rows/values/gates per function, mapped to
   MoveRule fields, every fact tagged [medido-no-body]/[inferência]. Broad surveys die —
   past two attempts failed; tight scopes succeed.
4. **Pins** in `remake/foundation/tests/ginkiha_tables_test.cpp` (new numbered section):
   dispatch update == `kLocomotion` handler, birth speed/turn, usage shape (phases/frames),
   trace fire frame + event count (or documented silence), walks VA. Build + run that binary.
   Commit `test(gameplay): fixa linhas do <Name> (...)`.
5. **Program** in `remake/foundation/src/gameplay/move_behavior.h`: `k<Name>Rules[]` +
   `MoveProgram` const + dispatch line on the update VA. Rules carry bundle line refs
   (e.g. `L21772-30`). Unverified tiers stay `-1` in `shot[3][2]` (fire_shot falls back to
   the provisional magazine scan — today's behavior, no regression).
6. **Test** in `remake/foundation/tests/fighter_script_test.cpp`: fixture `TestCombo load(ch,slot)`
   (reuse the parameterized loader), tap → move 400 + launch tick/row asserts, Yellow hold
   (loop-computed frames, NEVER hardcoded — float accumulation) → charge move + salvo asserts.
   Register the case in `main()` with the next section number.
7. **Verify**: rebuild all, run FULL `ctest --test-dir remake/foundation/build/linux`
   (never trust a single-target run for the gate; ctest runs stale binaries if you skip the build).
8. **Commit** after full diff review (AGENTS.md checklist: dead code, debug leftovers,
   duplication, useless comments). Keep code and docs commits separate.

## 5. Combo status (programs live in `move_behavior.h`, tests in `fighter_script_test.cpp`)

| Combo | Handler | Program | Shape (tap / charge) | Test |
|---|---|---|---|---|
| Rena 0 | 0x43ffc0 | rena (pre-existing) | anchor 12F; jump-cancel 400@20 | pilot cancel + cross-checks |
| Rena 1 | 0x448220 | rena1 (normal schedule subset) | 400 row 6 @18; 450 row 1 @12–26 | tap + charge schedule |
| Akane 2 | 0x5a7ea0 | deferred: world-origin callbacks | 400 row 0 @10; tag adds row 1 @15 | callback pins only; no program |
| Natsumi 0 | 0x5e2af0 | natsumi0 (normal ground 400 subset) | row 0 @14; Hide slots 0/1 | tap request schedule |
| Mion 0 | 0x4582a0 | mion | row 0 @2; row 0 @17 | tap + charge |
| Rika 1 | 0x492f70 | rika | even ticks 12–40; twin salvos | tap repeat + T10/T30 |
| Tomitake 2 | 0x527880 | tomitake | twin 7+5 every 3 ticks; freeze-then-fire | tap + charge |
| Keiichi 2 | 0x47b940 | keiichi | dense every-tick 10–20; rewind stalls | tap + charge + Hold latch |
| Chie 2 | 0x566a40 | chie | scratch-counter burst; single salvos | tap + charge |
| Kasai 1 | 0x5b9680 | kasai | twins 2+0; fan of four | tap + charge |
| Takano 0 | 0x531ce0 | takano | triple row 0 (12/15/18); single row 1 | tap + charge |
| Irie 1 | 0x57f600 | irie | twins 0+1 @12; single row 4 | tap + charge |
| Mion 2 | 0x44fa10 | mion2 | single @ entry-10 (jump!); 10× burst | single-shot pin + burst |
| Rika 2 | 0x49d890 | rika2 | single @15 + Hold; fan ×3 @10 | tap + charge |
| Satoko 0 | 0x4a9c40 | satoko | 5× @17; frozen twin salvos | tap ×5 + T25/T31 |
| Rika 0 | 0x484be0 | rika0 | twins @15; twin salvos @15/@25 | tap + charge |

Pinned-only (table test, no program yet): Kasai 0 (deferred — scatter needs engine work,
§7), Shion 0 (pins committed; bodies delimited, extraction not yet delegated).

Remaining usage-order worklist (27 TODO combos, plus two limited subsets and three pinned/
deferred entries). Keiichi 0 is pinned below; resume at Keiichi 1. Verify body and origin
mapping before promising programs):

| Combo | Usage pairs | Note |
|---|---|---|
| Rena 1 (ch=0 we=1) | 18 | landed as normal schedule subset; runtime-source path (not a reference body); geometry gaps noted below |
| Akane 2 (ch=13 we=2) | 18 | pinned; deferred: 400/402/450/460 callbacks include explicit-world origin; current MoveRule cannot carry computed XYZ/yaw/pitch |
| Natsumi 0 (ch=15 we=0) | 18 | landed as normal ground 400 row-0 schedule subset; 402/boost and world-charge paths remain unbound |
| Keiichi 0 (ch=2 we=0) | 12 | pinned; deferred: state400/402 use hand-origin FUN_00435220, unsupported by Prop1 Launch |
| Keiichi 1 (ch=2 we=1) | 12 | next feasible after Keiichi 0 hand-origin deferral |
| Satoko 2 (ch=3 we=2) | 12 | |
| Tomitake 0 (ch=6 we=0) | 12 | |
| Tomitake 1 (ch=6 we=1) | 12 | |
| Takano 1 (ch=7 we=1) | 12 | |
| Takano 2 (ch=7 we=2) | 12 | |
| Ohishi 0 (ch=8 we=0) | 12 | |
| Ohishi 2 (ch=8 we=2) | 12 | |
| Irie 0 (ch=10 we=0) | 12 | |
| Irie 2 (ch=10 we=2) | 12 | |
| Chie 0 (ch=11 we=0) | 12 | |
| Chie 1 (ch=11 we=1) | 12 | |
| Kasai 2 (ch=12 we=2) | 12 | |
| Akane 0 (ch=13 we=0) | 12 | |
| Hanyu 0 (ch=14 we=0) | 12 | only 2 weapons for ch14/15 (not 3) |
| Hanyu 1 (ch=14 we=1) | 12 | only 2 weapons for ch14/15 (not 3) |
| Natsumi 1 (ch=15 we=1) | 12 | only 2 weapons for ch14/15 (not 3) |
| Akasaka 0 (ch=9 we=0) | 8 | |
| Rena 2 (ch=0 we=2) | 4 | |
| Mion 1 (ch=1 we=1) | 4 | |
| Shion 1 (ch=5 we=1) | 4 | |
| Ohishi 1 (ch=8 we=1) | 3 | thinnest usage of the roster — expect sparse rules |
| Shion 2 (ch=5 we=2) | 2 | thinnest usage of the roster — expect sparse rules |
| Akasaka 1 (ch=9 we=1) | 2 | thinnest usage of the roster — expect sparse rules |
| Akasaka 2 (ch=9 we=2) | 2 | thinnest usage of the roster — expect sparse rules |
| Akane 1 (ch=13 we=1) | 2 | thinnest usage of the roster — expect sparse rules |
| Satoko 1 (ch=3 we=1) | 0 | no usage rows at all — bodies-only port, extra care |

Rena 1 blocker / scope note (runtime-source path, not full body parity): `reference/source/shoot_native_bodies_20260929.hpp` contains no `shoot_body_0_1_*`; the separately verified `runtime/DaybreakRebuild-20261010.zip` source has `battle_rena_ground_shot.hpp:45-54` (400 normal row 6 @18) and `battle_rena_mobile_shooting.hpp:178-189` (450 normal row 1 @12-26). The port schedules only those normal fixed-row events. State402's conditional phase-2 jump, 450/460 RNG spread, all 460 air behavior, and 360/370 fixed-pitch second charge need state/trajectory operations absent from MoveRule and remain deliberately unbound; this is a documented scope limit, not a guessed implementation. Runtime archive identity: `reference/source-provenance.json` SHA256 `0c98eba7…`.

Akane 2 defer note (2026-10-10): pinned handler identity/update, usage and origin-counted state400 callbacks; no MoveProgram was bound. Bodies 400/402/450/460 use `FUN_00435450` with explicit world coordinates, while `MoveRule::Launch` computes an attachment/bone muzzle. The current MoveRule cannot carry the computed XYZ/yaw/pitch, and callback probes do not prove admission/spawn. Normal/tag probes record one world request at frame 10; tag adds one at 15 across six forced phases. Add a world-origin op before implementing this combo.

Natsumi 0 scope note (2026-10-10): added `natsumi0` for the **normal ground state400 callback schedule only**: Hide prop bindings 0/1 from tick 14 onward, then Launch item row 0 at tick 14. This matches the controlled normal `fire_attachment(0,0,...)` request and the DAT registration map. The executor rebuilds prop bindings at the start of every tick, but the tick-14 Hide is applied before Launch during that same update, selecting the fallback bone-origin family. The test drives the actual Natsumi+item29 fixture. Phase labels are forced probes; raw callback flag/aim, exact geometry, actual projectile admission and natural phase reachability remain outside the claim. State 402 stays unbound despite an analogous raw helper call because no state402 normalized callback trace is included. The tag/boost five-row randomized requests and world-origin 450/460 charges also remain unbound.

Keiichi 0 scope note (2026-10-10): pinned update/vtable, walk, birth, usage (normal slot 0 and tag slot 3 at 13F across six forced phases), and callback families. `shoot_body_2_0_400/402` call `FUN_00435220` on `Bip01_R_Hand` at frame 13; trace callback rows are normal slot 0/tag slot 3. The MoveRule executor's only Launch uses `bone_point("Bip01_Prop1", item-slot muzzle)`, whereas FUN_00435220 delegates to FUN_00435250 with the looked-up hand transform, so binding Launch as a substitute would claim incorrect origin/geometry. The four body files contain measured movement/turn windows (400 ground, 402 air, first charges 450/460), but no hand-origin operation in the port. Do not claim the callback request as an admitted projectile/spawn. Concrete blocker: no distinct hand-bone spawn op exists; defer tap and continue with Keiichi 1, whose state400 trace is also hand-origin and must be independently body-audited before any partial schedule. Raw 450/460 `FUN_00435000` row mapping is also not established from its body tuple, so charge shot rows remain unbound.

Scoreboard: 13 full programs + 2 schedule subsets (Rena 1, Natsumi 0) + 4 pinned/deferred (Kasai 0, Shion 0, Akane 2, Keiichi 0) + 27 remaining TODO = 46 roster combos.

## 6. Engine mechanisms you must know (all in `src/gameplay/`)

- `MoveRule{move,phase,first,last,op,value,second,third}`; ops incl. `Launch(row,lateral,pitchClamp)`,
  `Hold` (freezes elapsed), `Hide` (slot 0 only — slot-1 halves have no field).
- `fire_shot`: exact-row programs bypass the provisional magazine scan; `-1` rows keep it.
  `m_stateTimer = programmed >= 0 ? 0 : kShotStateFrames`.
- **Hold latch** (`m_holdRule`, fighter.h/cpp): per-rule hold progress — a shared counter would
  starve a second Hold in one move (Keiichi 450: 10f@5 + 15f@32). Dash path untouched.
- **Launch latch** (`m_lastLaunchRule/Phase/Tick`, reset in `set_state`): one firing per
  (rule,phase,tick) — without it, same-tick Launch+Hold combos (Rika 450) queue up to 8
  pendings instead of 2. Twin rules (different objects, same tick) still both fire.
- **Update order**: input/fire → `execute_move_program` (rules see PRE-increment elapsed) →
  `advance_animation_phase` (increments). Consequence for tests: a `while elapsed<N` loop
  exits right after the tick that SET N, whose rule pass still saw N−1 — add ONE more tick
  before taking pendings. Fixed-count drives (Rena: exactly 12 post-release ticks) also work.
- **Phase resets elapsed** (`enter_phase`): long bursts spanning phases need elapsed-driven
  loops with caps, never fixed counts (Mion 2 precedent).
- **Yellow hold frames must be loop-computed** from `magazineForChargeLevel(1).chargeMax /
  tickRate` — hardcoded counts overshoot into Red on float error (Tomitake precedent).
- Pending queue caps at 8 (`launch_bullet` drops beyond) — relevant for volleys (Kasai 0 §7).
- `m_moveElapsedTicks` resets in `set_state`/`enter_phase`/init paths; the launch latch resets
  in `set_state`.

## 7. Known gaps — do NOT guess these (document, defer, or extend the engine deliberately)

- **Kasai 0 DEFERRED** (program not landed): 21-pellet scatter (1× row 2 + 20× row 0, shared aim)
  exceeds the 8-pending queue and per-pellet aim has no fields. Needs: pending capacity +
  spread fields. Pins stay as bundle reference.
- Tag/aim branches (rows 1/3/5/6/7 secondaries, asymmetric counts): no aim/tag flag in the
  model — always bind the normal branch, document the skip (precedent everywhere).
- Projectile speeds: live in item data / update VAs, never in MoveRule. Births table is the
  reference (`ginkiha_tables.h`, generated by `tools/import_ginkiha_tables.py` — deterministic,
  hash-checked; regenerate, don't hand-edit).
- Gravity tails (`w0x10` channel, unclamped), one-shot velocity sets, `FUN_004223d0` muzzle
  variants, `fields[4,11,12]`, `flags28`, `parameters[2]`: no fields — skip explicitly.
- Extended bursts needing runtime burst-count state (Kasai base-2 vs upgraded 4/6): static
  schedules only; the upgrade is a documented gap.
- Asymmetric pitch clamps: model clamps symmetric — keep the ceiling, note the floor gap
  (Mion 450 precedent).
- `shot400` key suffix is the usage VARIANT, not the slot (Tomitake lesson — Rena coincides).
  Trace `fire_frame` = FIRST fire; `fire_events` = total count.
- `hud_view_geometry.py` ally-green predicate is calibrated to green-DOMINANT (pale art),
  NOT pure green — the old predicate never matched ally art (proven: 78–88 vs background 0,
  no cross-talk). Do not "fix" it back; red path untouched.

## 8. Traps that already bit (learn from them)

- **Destructive edits**: the `edit` tool replaces `old_string` — twice it ate neighboring lines
  (`return nullptr`, whole rule arrays, program consts). Always re-verify with grep + brace
  count + build after every edit to `move_behavior.h`. Prefer tiny unique anchors; never span
  lines you want to keep.
- **Stale binaries**: `ctest` without rebuilding runs old binaries — always `cmake --build`
  first for the gate. A "green suite" on a stale tree once hid a broken HEAD (test referenced
  a header field that wasn't committed).
- **HEAD must always build**: commit regenerable artifacts together (importer + generated header
  + tests). Never commit a test referencing an uncommitted header change.
- **Truncated dumps lie**: a `[:4]` slice once showed 4 trace events where 21 existed — the test
  caught it. Never pin numbers from truncated output; count fully.
- **Recon filters**: `startswith('10:')` matched swap 10 instead of 9 — verify swap codes against
  `reference-data.json`, not string prefixes.
- **Section numbering** in `fighter_script_test.cpp` must stay unique and ordered; the `main()`
  call list must include every new case.
- The `update` VA in dispatch must equal the `kLocomotion` handler for the combo — the table
  test pins this per combo; a mismatch means a wrong-handler bug, investigate, don't adjust.

## 9. Verification checklist (every combo commit)

1. `python3 remake/foundation/tools/import_ginkiha_tables.py` regenerates byte-identical output
   (only if the importer changed).
2. `cmake --build build/linux` — zero errors (watch for silently-eaten lines: grep counts).
3. New fighter test green standalone + FULL `ctest` green (65/65 as of 2026-10-09; read ctest's
   own summary — the denominator moves).
4. `git status` shows ONLY your files; `git diff` + `git diff --cached` fully reviewed.
5. Plan status line appended (`docs/reports/ginkiha-port-plan.md`): combo + time concluded.
