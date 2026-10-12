# Handoff — Phase 2 combo porting (`ginkiha-help` branch)

To the next agent: continue porting character+weapon combo shot programs exactly as below.
Everything here is verified against the workspace — trust files over memory.

**Owner-directed change of order (2026-10-10):** stop usage-order combo porting and
implement shared blockers first. Follow [ginkiha-blockers-plan.md](ginkiha-blockers-plan.md),
then close every blocked/partial combo and audit all 46. “Next: Tomitake 0” below is the
historical usage-order pointer, not the active task. Earlier “full program” counts do
not establish complete shooting-path coverage.

**Current owner focus (2026-10-11): Rena+0 playable defects.** The
[Rena group record](ginkiha-rena-iteration.md) now carries full-charge targeting,
move-specific voices, black projectile-padding policy and side-dash animation
selection. Continue Rena+0 manual feedback before expanding the roster again.

Checkpoint: recon tooling, the [46-combo ledger](ginkiha-shooting-coverage.md),
[launch/admission contracts](ginkiha-launch-contracts.md),
[architecture decisions](ginkiha-shooting-architecture.md), and the isolated magazine
primitive are now present. Bound Fighter stocks, row admission, charge counters, the
powered gate and per-move counters have migrated. Satoko 2's tap is the first typed-world
program and Rika 1's charge was repaired with the counter model. Resume from the blocker
plan's latest append-only checkpoint (entry 3.0).

**2026-10-12 — correction: weapons 1 and 2's prop-latch spans.** The weapon-0 audit was
only one handler; FUN_00448220 and FUN_00438310 carry the same
`(tick < N) || (M < tick)` windows around FUN_00434b30/bd0, and NEITHER table had a
single `Active` rule, so their props never armed. Now bound: w1 301 (10..16), 310 (5..7),
311 (12..18); w2 310 (24..45), 311 (32..49), 330 (28..34), 331 (26..109), 340 (16..24).
Left unbound on purpose and recorded: w2 301/302 (its admission has no such branch, so
the rows are unreachable) and both weapons' 320/350 (those already model the contact half
via ContactOff — w1's 350 is exactly 21..64 — so their ribbon half awaits the phase
structure).

**2026-10-12 — correction: three weapon-0 melee rows.** The same body-by-body pass found
310 missing its phase-0 180-degree entry snap and its phase-2 5..7 contact/ribbon span
(FUN_0043ffc0:756-765/772-774, 791), 311 missing the ungated tick-0 180-degree snap
(824-829 — weapon 2's table already had it), and 341 missing its phase-1 0..19 span
(1365). All four are pinned now. Also retired 310's stale "needs the effect renderer and
the melee voice latch" comment: those cues were bound in the voice/effect slice.

**2026-10-12 — correction: Rena+0's mobile/dash shot windows.** Re-reading
FUN_0043ffc0's own case bodies (not the donor summaries) showed the 401/405/406/407/408
windows had been read from the wrong side of the same lines: the unbind is
`threshold < tick`, so it starts the tick AFTER the recorded number. 401 bleeds 0.25 (not
0.5) and unbinds from 14 (not 12); 405/406 approach 15 deg for ticks 0..9 (not 20 for
0..11), bleed 0.5 only after tick 10, and unbind from 14; 407 turns 9 deg for ticks 0..9
PLUS 15 deg on every phase-0 tick (two `FUN_0042db10` calls) and unbinds from 14; 408
unbinds from 14. 400 and 402 were already right, which is what fixes the convention.
`melee_admission_test` now pins all five windows so they cannot silently revert.

**2026-10-12 — Mion group started; her melee admission is on the recovered path.** The
port's `kDispatchIdentity` slot 7 names Mion's dispatchers (0x45F4D0 / 0x467D70 / 0x456030
for weapons 0/1/2), and their melee sections are the same condition sequence line for line,
so `melee_admission.h` carries one shared `mion_melee_admission` behind
`melee_admission_for(character, …)`. `attack_admission_recovered` now covers character 1,
which puts Mion on the same admission path as Rena; her family is *not* Rena's — no
311/332/334, the directional kick is 312, and 340→341 belongs to all three weapons. Real
input reaches 300 (neutral), 310 (back held), 312 (lateral held), 330 (forward dash) and 320
(airborne) for each weapon. Two things are recorded rather than guessed: Mion's 0x15e is
reached from a different section of her dispatchers, so the port's boosted-350 admission
stays scoped to the Rena group; and her dispatchers route the WALKING tap to her own mobile
states 401/410/411/412 (weapons 0/1 only — FUN_00456030 has no such branch), which the port
has not bound. The ledger rows and the new
[Mion matrix](ginkiha-mion-attack-matrix.md) carry both.

**2026-10-11 — remaining verification items 3/4:** `fighter_script_test` section 45 now
checks Rika+1 normal ground shooting against an independent MT19937 oracle for every shot
(two seeds), and Satoko+0 normal/powered ground fans (five/eight shots). It also checks the
actual launch positions against pre-update posed hand transforms, independently of the
launch resolver, at nonzero positions/headings. These are grounded-path witnesses; do not
promote untested air paths or claim original global RNG stream alignment. Validation is
recorded in the blocker plan's latest entry.

**2026-10-11 — character-group iteration:** work now audits all legal weapons of one
character together. [Rena+0/+1/+2](ginkiha-rena-iteration.md) is the first group. Original
handlers replaced incorrect Rena+1 bridge schedules, restored its model2 muzzle and
charge yaw sweep, corrected Rena+2's ring angle and bound its ground hand charge,
and corrected Rena+0's integer tap aim / second-charge geometry and freeze. Section46
checks the grouped ground paths. Continue the same trio's air/landing and follow-on
states before claiming completion, then advance to Mion's three weapons. All runs
remain silent; unrelated working-tree changes are preserved.

**2026-10-12 — shared-mechanism review + the aerial/recovery slice:** the review of the
just-landed movement/execution mechanisms found and fixed four discrepancies, each
source-backed: (1) FUN_00420b30 applies the chase/dive lean as `T(0,-pivot,0) *
Rx(pitch) * Ry(yaw) * T(position+pivot)` — `+0x2c` is a PITCH and `+0x2d8` a pivot
HEIGHT, and the earlier cut folded both into the Y angle (now pinned by an independent
matrix witness); (2) the landing branch only ran for `AttackA`, so the air taps/charges
(Shoot states here) never reached their 403/409/469 recoveries — `switch_attack_row`
now moves the active channel; (3) the attacker-side guard-exit table was wrong (300/320
never have the branch; 302/330 exist only for weapons 0 and 2; 392 now also carries its
scratch→phase-1 body); (4) the 403/409/469 zeroing windows were 0..1 despite the bodies
having no guard, and weapon 0's 350 must cut contact for the whole move. The
`+0x20d` question is settled: it is `param_1[0x20d]` = byte +0x834, the fighter-level
special/charge gauge, not a magazine. The aerial slice landed with it: weapon 1's
three-phase 402 dive, weapon 2's clamp/seek 402 with its ten-request ring, the
403/409/469 recoveries, the model-2 prop rebind for weapon 1's 450/460, the 350
awakened-melee bodies for weapons 0/1 (including the frames-1..9 clock-replay window
fix), 392's exit body, and the melee voice/effect producer latches. `melee_admission_test`
is now 253 checks. Remaining, in order: the live visual parity window (lean sign and
the model-2 frame), the close-target voice cascade, and the consumer of the
`(*actor+0xc)` vtable cue.

**2026-10-12 — boosted admission and the voice/SE dispatch:** the special-gauge
admission is implemented and input-driven-verified (armed press → 350, unarmed → 300);
its two recorded deltas are the action-intent slots `+0x284`/`+0x288` (produced by the
input dispatch FUN_0041efe0, which merges the pad array at `+0x9e` into `+0xa0..+0xa2`,
and by the COM brain FUN_0043f4d0; button identities not established, so the port's
single melee press is a looser stand-in) and the
aim-lock-only arming. The audio layer now consumes the body cues: the melee voice ids
ARE the voice vocabulary's indices (the original's 40-name table at 0x6b73b0), so a
`MeleeVoice` event maps the id straight to a `VoiceEvent` with the FUN_00422490
alternative, and a row whose cue policy is recovered suppresses the fallback swing
voice. **Provenance correction:** `FUN_0042c8b0`/`FUN_0042c880` are not visual effects —
they call `FUN_0064b060` → `FUN_0064ae70`, which indexes the manager's data/se table and
plays the id through the 3D audio mixer at the actor's position. Every non-scatter id in
the rules (60..77, 170..172) exists under `data/se/`, while the scatter ids (320/340/350,
from the still-unidentified `(*actor+0xc)(id,x,y,z,yaw,pitch)` vtable call) do not — which
is what fixes the split. The op/field/factory were renamed to `SoundEffect`, the SE is
dispatched on the SFX bus (positional placement recorded as unmatched), and the vtable
cue's consumer stays open with only its RNG consumption bound.

**2026-10-12 — the "vtable cue" identified, and the effect path wired:** the
`(*actor+0xc)(id,x,y,z,heading,pitch)` call is the actor-side EFFECT request, not an
unidentified hunk: FUN_00421aa0 converts the heading/pitch to a direction and forwards
to FUN_00435990, which calls the effect manager's own create with (id, position,
heading, pitch). Its id indexes data/effect by `id / 10` (FUN_0042eba0's 100 slots), so
the 350 beats' 320/340/350 resolve to 032/034/035.dat — the earlier confusion came from
checking those ids under data/se, where they legitimately do not exist. The model now
keeps the two paths apart (`MoveOp::SoundEffect` for data/se ids, `MoveOp::Effect` for
the effect request with its yaw/pitch), `melee_admission_test` drives a real boosted 350
and sees effect 320 with its two rand%40-20 draws at frame 7 and SE 061 at frame 11, and
the match spawns the effect card at the actor's position. One gap left on this path: the
card queue is position-only, so the request's heading/pitch do not orient the card yet.

**2026-10-12 — secondary clocks resolved, Rena+1's visible weapon fixed:** the two actor
clocks (`+0xae04`/`+0xae08`) never diverge on a recovered attack path. Every confirmed
seek writes BOTH together (w2 320's windup skip at FUN_00438310:952-954, w0 350's stall
and rewind, the 350/360 seeks to 95, Mion 0's 0xbc/0xbd, Mion 2's teleport),
`FUN_00421100` zeroes both and the epilogue increments both, so the port's single
`m_moveElapsedTicks` (which drives both the rule ticks and the animation playhead) is
exact. An earlier note claimed w2 320 wrote the secondary clock alone; the full body
contradicts that partial grep and the claim is retracted. The only lone-clock site is
FUN_0046a190:2346 (Keiichi 0), which resets `+0x2b82` and immediately calls
FUN_00421410(0,0) — a channel-0 animation rebind, not a phase seek. Separately, the
rendered-weapon gap is closed: FUN_00434a70(slot, model) re-points a prop slot at another
of the item's models and the original draws whichever model the slot names, so
`Fighter::draws_item_model` is now the render gate's predicate (item 3 ships 11.x at
model 0 and 12.x at model 2 with identical muzzles, which is why the launch-origin
witness could not catch the wrong mesh). The install-backed Rena+1 test asserts model 2
is drawn for the 450 and model 0 for the tap. Remaining before Mion: the boosted gate,
the voice/effect consumers, and the live visual window (lean sign and the model-2 frame).
All runs silent; the 2-player capture keeps both fighters armed.

**2026-10-12 — admission rejection contract + the melee execution slice:** the
attack-input branch now resolves admission BEFORE any attack-entry mutation — a
declined press (failed priority gate, missing destination row, declined air/chain
press) no longer enters AttackA, binds a fallback clip, arms a swing or touches
facing/aerial metadata, and falls through to the later input checks exactly as
FUN_00445ee0's declined branches do. The regression is pinned through the real
Fighter input path in `melee_admission_test` (now 210 checks). The shared
attack-state movement slice landed with it: a vertical channel (Vertical/Gravity
ops in the bodies' u/tick units, sticky per move and carried across row
switches), landing transitions (LandExit/LandPhase), body-driven exits
(ContactExit/JumpCancel/PhaseExit), w2's double-speed clock (ClockSkip), the
distance-latch gates, and the recovered 320 chase and 332/334 dive bodies with
per-weapon policies in `move_behavior.h`. All three weapons' melee families
(300/301/302/310/311/320/329/330/331/332+334/333/340/341) carry execution rules
with provenance comments, and the 407 back-dash pair and the 408 air-dash fast
shot are driven end-to-end. The matrix now uses four status labels (selection
implemented / execution implemented / automated verification / live parity) —
"verified" means the named input-driven tests pass, never live equality, and the
chase/dive body-lean sign is explicitly pending an owner-present live window.
Next: the aerial shooting transitions (matrix §6.3 quotes the exact handler
lines), then boosted/350.

**2026-10-11 — owner-requested attack/animation scope review:** the next work is
[the attack-animation plan](ginkiha-attack-animation-plan.md), starting with Rena+0/+1/+2.
Audit real input admission, melee transitions, pose clocks and rendered props alongside
the existing shooting work. **2026-10-12 — first slice landed:** the recovered
attack/shot admission for the whole Rena group is implemented
(`melee_admission.h`, `melee_admission_test` 127 checks) and the per-weapon evidence
matrix lives in [ginkiha-rena-attack-matrix.md](ginkiha-rena-attack-matrix.md). The usage-ranked shooting recipe in §4 is historical and
only applies to a shooting subtask; it is not the complete combo-port workflow. Do not
advance to Mion based on launch checks alone. Phase 1's full attack acceptance is reopened;
its initial pipeline and subsequent verified improvements remain implemented.

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

## 3. Branch state (historical baseline: 2026-10-09, suite 65/65 green)

- Branch `ginkiha-help`, forked off `main` WITH the user's uncommitted Windows work
  (`remake/foundation/CMakeLists.txt` WIN32 hunks, `BUILD-windows.md`, package files, etc.).
  The owner authorized committing that Windows packaging work on 2026-10-12; it is
  now included in a separate packaging commit. The earlier instruction to leave those
  hunks unstaged is retired. Inspect current `git status` and stage only task-owned
  changes; do not keep treating already committed Windows code as pending work.
- Push scope per AGENTS.md Git section; never commit: `research/recomp/`, game files,
  `*.full.json`, `remake/foundation/build/`, `third_party/`, `.local-analysis/`.

## 4. The combo pipeline (the mold — follow it exactly per combo)

1. **Rank**: usage pairs per combo (`shot400_usage` keys `ch:we:r`): pick the richest unported
   combo. Done so far (usage order): Rena 0 (pilot), Mion 0, Rika 1, Tomitake 2, Keiichi 2,
   Chie 2, Kasai 1, Takano 0, Irie 1, Mion 2, Rika 2, Satoko 0, Rika 0. Since then,
   Rena 1 and Natsumi 0 landed as limited normal subsets; Akane 2 is pinned/deferred.
   Keiichi 0/1 and Satoko 2 remain pinned/deferred while typed origins are connected to
   body state. The current next task is in `ginkiha-blockers-plan.md`: model aim-selection
   and its +0x848 hold separately from the combat lock before binding Satoko 2 branches.
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
| Rena 0 | 0x43ffc0 | rena (pre-existing, now gate-bound + counter freezes) | 400 rows 0/6 @12; 402 rows 1/7 @13; 450/460 rows 2/8 fixed 45°; 360/370 rows 11/12 | powered branches on every site + freeze |
| Rena 1 | 0x448220 | rena1 (runtime-source path, now gate-bound) | 400 fan frames 12–26 rows 1/3; 450 row 2/8 fixed 45° @13 | tap fan both branches + fixed-pitch charge |
| Akane 2 | 0x5a7ea0 | deferred: typed world origin exists; body calculations/branch are unbound | 400 row 0 @10; powered adds row 1 @15 | callback pins only; no program |
| Satoko 2 | 0x4bc040 | **satoko2: typed-world twin tap, normal/powered gate** | 400/402 twin world rows 0/1 @20; 450/460 phase1 @6 still pending | table + item38 fixture pins; twin-world + gate test |
| Keiichi 1 | 0x473610 | **keiichi1: hand tap + world charges, gate-bound** | 400/402 hand R @13 rows 0/1; 450/460 world @20 rows 9+2/3 | tap + charge, both branches |
| Natsumi 0 | 0x5e2af0 | natsumi0 (normal ground 400 subset) | row 0 @14; Hide slots 0/1 | tap request schedule |
| Mion 0 | 0x4582a0 | mion (audited: slots, powered rows, counter freezes) | 400 p1t2 rows 0/4 slot 0 + p3t2 slot 1 (contact); 402 dual-slot c=15/20/25; 450 rows 2/3 @17; 460 rows 2/3 @17 | tap + air volleys + both charges |
| Rika 1 | 0x492f70 | rika | even ticks 12–40; twin salvos; **counter-gated 30-update freeze at T30 (3 salvos), ground + air, both branches** | tap repeat + T10/T30 + frozen interval + latch + air 460 normal/powered |
| Tomitake 2 | 0x527880 | tomitake | twin 7+5 every 3 ticks; freeze-then-fire | tap + charge |
| Keiichi 2 | 0x47b940 | keiichi (audited: sweeping tap, gate-bound) | 400/402 sweep ticks 10-20 rows 0/1; 450/460 world @13 rows 2/3 measured but unbound | tap sweep + charge rows measured |
| Chie 2 | 0x566a40 | chie | scratch-counter burst; single salvos | tap + charge |
| Kasai 1 | 0x5b9680 | kasai | twins 2+0; fan of four | tap + charge |
| Takano 0 | 0x531ce0 | takano | triple row 0 (12/15/18); single row 1 | tap + charge |
| Irie 1 | 0x57f600 | irie | twins 0+1 @12; single row 4 | tap + charge |
| Mion 2 | 0x44fa10 | mion2 (audited: teleport shift, powered rows) | 400 single @entry-10; 402 single @18; 450/460 phase-1 emissions @15..60 rows 2/3 | tap + burst |
| Rika 2 | 0x49d890 | rika2 | single @15 + Hold; fan ×3 @10 | tap + charge |
| Satoko 0 | 0x4a9c40 | satoko | 5× @17; frozen twin salvos | tap ×5 + T25/T31 |
| Rika 0 | 0x484be0 | rika0 | twins @15; twin salvos @15/@25 | tap + charge |

Pinned-only (table test, no program yet): Kasai 0 (deferred — scatter needs engine work,
§7), Shion 0 (pins committed; bodies delimited, extraction not yet delegated).

The usage-order worklist below is historical. The active sequence is the blocker plan's
(entry 3.0: audit the other Hold schedules → Keiichi 0/1 hand geometry → Kasai 0
allocation/spread → roster by family). Usage density orders work inside a family only.

Remaining usage-order worklist (25 TODO combos; audited subsets/deferred entries are retained
below for context). Resume at Tomitake 0. Verify body and origin mapping before promising programs:

| Combo | Usage pairs | Note |
|---|---|---|
| Rena 1 (ch=0 we=1) | 18 | **bound**: tap fan frames 12–26 rows 1/3 + fixed-45 charge rows 2/8; spread yaw/pitch and 402/460 unbound |
| Akane 2 (ch=13 we=2) | 18 | pinned; typed origin/aim fields now exist; body-computed XYZ/yaw/pitch and branch are not connected to a program |
| Natsumi 0 (ch=15 we=0) | 18 | landed as normal ground 400 row-0 schedule subset; 402/boost and world-charge paths remain unbound |
| Keiichi 0 (ch=2 we=0) | 12 | **bound**: hand tap + left-hand/attachment charges, both branches, snap pitch on air |
| Keiichi 1 (ch=2 we=1) | 12 | **bound**: hand tap + world charges with range pitch, both branches |
| Satoko 2 (ch=3 we=2) | 12 | pinned; typed world origin exists; source aim-selection branch and movement offset remain unbound |
| Tomitake 0 (ch=6 we=0) | 12 | next to recon; origin/body audit required |
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
| Rena 2 (ch=0 we=2) | 4 | RNG-blocked: state400's 11-request volley needs per-shot spread; see defer note below |
| Mion 1 (ch=1 we=1) | 4 | **bound**: taps (slot-1 contact follow-up) + 15-shot spread fans, rows 1/5 |
| Shion 1 (ch=5 we=1) | 4 | |
| Ohishi 1 (ch=8 we=1) | 3 | thinnest usage of the roster — expect sparse rules |
| Shion 2 (ch=5 we=2) | 2 | thinnest usage of the roster — expect sparse rules |
| Akasaka 1 (ch=9 we=1) | 2 | thinnest usage of the roster — expect sparse rules |
| Akasaka 2 (ch=9 we=2) | 2 | thinnest usage of the roster — expect sparse rules |
| Akane 1 (ch=13 we=1) | 2 | thinnest usage of the roster — expect sparse rules |
| Satoko 1 (ch=3 we=1) | 0 | no usage rows at all — bodies-only port, extra care |

Rena 1 blocker / scope note (runtime-source path, not full body parity): `reference/source/shoot_native_bodies_20260929.hpp` contains no `shoot_body_0_1_*`; the separately verified `runtime/DaybreakRebuild-20261010.zip` source has `battle_rena_ground_shot.hpp:45-54` (400 normal row 6 @18) and `battle_rena_mobile_shooting.hpp:178-189` (450 normal row 1 @12-26). The port schedules only those normal fixed-row events. State402's conditional phase-2 jump, 450/460 RNG spread, all 460 air behavior, and 360/370 fixed-pitch second charge need state/trajectory operations absent from MoveRule and remain deliberately unbound; this is a documented scope limit, not a guessed implementation. Runtime archive identity: `reference/source-provenance.json` SHA256 `0c98eba7…`.

Rena 1 update (2026-10-10, ledger slice): the runtime source is richer than that first note and is now fully bound. `battle_rena_mobile_shooting.hpp:181-184` requests **one shot per frame 12..26 (15 rolls)** on state400 — row 1 normal / row 3 powered — with yaw `scratch_ec-30` and pitch from a `draw()%10`; the fan is bound per-frame with the row split, while the spread stays an explicit gap because there is no per-tick draw service. Line 187 (`bullet(special?8:2,0,45)`) makes the 450 charge a single **fixed-45** attachment shot, now bound with its powered row. State402's grounded phase jump and 460 air behavior still need phase/trajectory ops; 360/370 have no evidence in the runtime source.

Rena 2 defer note (2026-10-10, ledger slice): no `shoot_body_0_2_*` exists in either body header, so the handler `FUN_00438310.c` is the only source. Its state400 body is fully measured and **deliberately left unbound on one blocker**: at phase 1 tick 35 it emits `FUN_00434fd0(0,0,0,0)` (attachment slot 0, row 0 normal / row 2 powered, zero yaw/pitch) and then loops **ten times** requesting `FUN_00435450(row 1 normal / row 3 powered, ...)` where each shot's pitch is `rng()%30 + 20`, its yaw is `heading + movement offset + 90 − rng()%180`, and its position is 200 forward / +30 height on that yaw. The EXE trace (`roster-ground-shot400-continuity-extended.jsonl`, phase 1 frame 35) confirms 11 requests — 1 attachment + 10 world, rows 0/1 normal and 2/3 powered — but the harness fixes the RNG and stubs the actor, so all ten world rows read the same `(0,30,0,85,25)`; the real spread is per-shot. Binding this now would fire ten **stacked identical** projectiles, which is an approximation the completion contract forbids. Unbind it until the deterministic shooting RNG of Kasai 0's slice exists, then this is a one-step port. No 402/450/460/360/370 evidence exists for this combo either.

Akane 2 defer note (2026-10-10): pinned handler identity/update, usage and origin-counted state400 callbacks; no MoveProgram was bound. Bodies 400/402/450/460 use `FUN_00435450` with explicit world coordinates. Typed origin/aim specs now allow world XYZ and legacy angles, but the body calculations, powered branch and dynamic runtime inputs are not connected to a schedule; callback probes also do not prove admission/spawn. Normal/powered probes record one world request at frame 10; powered adds one at 15 across six forced phases.

Natsumi 0 scope note (2026-10-10): added `natsumi0` for the **normal ground state400 callback schedule only**: Hide prop bindings 0/1 from tick 14 onward, then Launch item row 0 at tick 14. This matches the controlled normal `fire_attachment(0,0,...)` request and the DAT registration map. The executor rebuilds prop bindings at the start of every tick, but the tick-14 Hide is applied before Launch during that same update, selecting the fallback bone-origin family. The test drives the actual Natsumi+item29 fixture. Phase labels are forced probes; raw callback flag/aim, exact geometry, actual projectile admission and natural phase reachability remain outside the claim. State 402 stays unbound despite an analogous raw helper call because no state402 normalized callback trace is included. The tag/boost five-row randomized requests and world-origin 450/460 charges also remain unbound.

Tomitake 2's charges closed (2026-10-10, ledger slice): **all four states now bound.** The
charges (L39390-39440, L39550-39600) fire row 4 unconditionally — lateral 0, pitch 0, height +75
— and then row 0 normally or row 2 powered on `byte(+0x845) && word(+0x212)`. The old note called
the tag rows "6/2"; the body says row 4 always plus row 2 powered, so the ROW-4 shot is shared
and only the second moves. Witnessed as rows 4 then 2.

**Irie 1's 401 is blocked by the move table, not by a flag.** It fires a two-slot attachment
request at tick 15 and then jumps after tick 29 to one of four follow-up states
(0x19b/0x19c/0x19a/0x191) chosen by the signs of `w[0x9e]`/`w[0x9f]`. `MoveOp` has no
state-transition operation, and 401 is outside Irie 1's `{400, 402}` mapping — so binding it
means a new op PLUS a progression change that would move the phase sequence the traces validate.
The direction plumbing from the previous slice already carries the sign test it needs; the
missing piece is the op.

AI movement direction bound (2026-10-10, ledger slice): **Rika 2's three normal rows are
live.** The decode landed as a mechanism: `ShootingContext::moveLateral` carries the sign of
`+0x278`, `Match::step` publishes it for AI slots only (from the applied direction keys, which
is how this port expresses the brain's intent), and `kGateDirLeft/Neutral/Right` state the three
branches. Rika 2's normal tap rules carry `kGateNormal | kGateDir*`, so the direction selects the
normal row while the powered branch keeps firing all three — the first cut omitted `kGateNormal`
and a powered fighter fired four shots, which the suite caught.

The human path is untouched by construction: a human slot publishes 0 and takes row 0. The
witness drives all three signs through the context and gets rows 2, 0 and 1, so the gate is
tested end to end rather than through the rules' own constants.

`+0x27c` (the second axis, `w[0x9f]`) is decoded but not yet published: nothing in the port's
table reads it. Irie 1's state 401 uses both signs to pick one of four follow-up states, and 401
is outside the port's `{400, 402}` mapping for that family — so the plumbing is ready and the
rules are what remain.

`w[0x9e]`/`w[0x9f]` decoded (2026-10-10, ledger slice): **they are the COM's movement
direction, not a player input.** Rika 2's normal tap picks its row from `w[0x9e]` and Irie 1's
state 401 picks one of four follow-up states from the signs of both components, so the pair had
been blocking both. It is `(+0x278, +0x27c)` and the corpus is unambiguous:

* only `FUN_0043f4d0` and `FUN_00447730` write it, and both are COM decision routines — a
  wander timer `+0x864 ∈ [-200,199]` drives `+0x278` to -1/0/+1, and squared-distance tests
  (`< 250000`, `< 122500`, `< 90000`) set `+0x278` and `+0x27c` together;
* every one of the 471 other references is a read, in movement, action and shoot code;
* the port's own `bot_brain.h` independently documents the field as "a 3x3 movement direction
  in +0x278/+0x27c" and models the timer — the two readings corroborate.

**Consequence for the ledger:** a human-controlled fighter never has it written, so it stays 0
and the fighter takes Rika 2's row-0 branch and Irie 1's no-direction branch. The port's row-0
binding is therefore RIGHT for players and incomplete only for a COM attacker. That re-scopes
both entries from flat blockers to a COM-only gap. Closing it needs a direction gate on the
shooting context; the bot brain already carries the value, so the work is a publish plus a gate,
not new AI.

Tomitake 2 audit (2026-10-10, ledger slice): **the tap is bound with its gate; the charge's
tag rows stay open.** `shoot_body_6_2_400/402` fire TWO shots per scheduled tick (15..33 step
3), and the whole burst is gated on `scratch % 3 == 0 && 0 < w[0x1b7]`. The first shot is
always row 7 with lateral 0 and pitch 0; the second is row 5 normally or row 6 powered, chosen
by `byte(+0x845) && word(+0x212)` — the kGatePowered idiom the old note claimed did not exist.
Both draw `(draw%12-6)*0.25` of pitch and then `(draw%6-3)*0.5` of lateral **on the ground
tap**, with the powered row swapping the two moduli; the air tap uses 6/-3 for both. Elevation
clamped ±45. The witness pins all of it against the canonical stream: row 5 at +0.5 pitch and
-1.5 lateral, row 6 at -0.25 and 0.

The charge's rows 6/2 are NOT bound — not for want of a flag (there is one, as the tap proves)
but because its body was not re-read in this pass. That is the honest reason and the note says
so rather than repeating the excuse.

**Correction to my own earlier notes.** Six comments written in previous slices justified a
powered binding by citing `w[0x1b7] < N`. That is not the row/count gate: it is a separate field
that picks the *sound* (and in this family an outer gate on the whole burst). The row/count gate
in every one of these bodies is `byte(+0x845) && word(+0x212)`, which is what `kGatePowered`
models. The bindings were right; the stated justification was not, and all six comments are
corrected.

Irie 1 audit (2026-10-10, ledger slice): **all four states bound; the "no flag field" note
retired.** `shoot_body_10_1_{400,402}` fire at tick 12: TWO world requests normally, on rows
**1 then 0**, and FOUR powered, on rows **3, 2, 1 then 0** — the tag branch ADDS the row-2/3
pair rather than replacing the row-0/1 one (L63286-63302, L63551-63610). The gate is
`w[0x1b7] < 4`, i.e. kGatePowered. Each request sits 100 units out at ±4 degrees of heading
with the target elevation clamped ±40; that world pair is still placed through the adapter.

**The old test encoded the wrong order**: it asserted rows 0 then 1 because the un-ordered
binding produced them in table order. The body is authoritative (row 1 first), the rules now
follow it, and the assertion was corrected rather than the rules.

The charges fire one `FUN_00434fd0` request — row 4 normal / row 5 powered, elevation clamped
±30 — at tick 22 (450) and tick 17 (460). Worth recording: the first grep for this family's
fire helper looked for `FUN_00435220`/`FUN_00435000`/`FUN_00435450` and found nothing, which
looked like a fabricated rule; the actual helper is `FUN_00434fd0`, a name this audit had not
seen. Grep the whole `FUN_0043xxxx` family, not the helper names already known.

Also seen and NOT bound here: state 401's tick-15 pair (slots 0 and 1, row 0, elevation ±40)
and its after-tick-29 transition to 0x19b/0x19c/0x19a/0x191 selected by `w[0x9e]`/`w[0x9f]`.
The port maps {400, 402} for this family's tap, so 401 is out of its table — note that
`w[0x9e]` appears here too, the same selector Rika 2 is waiting on.

Takano 0 audit (2026-10-10, ledger slice): **all four states bound; the "no flag field" note
retired.** `shoot_body_7_0_{400,402}` fire three `FUN_00435220` requests on `Bip01_R_Hand` at
ticks 12, 15 and 18 — three single shots, not a repeating window — each taking the target
elevation clamped ±40. Row 0 normal / row 6 powered, and the tag branch reads `w[0x1b7] < 4`,
which is kGatePowered. The charges fire one slot-0 attachment request at tick 18 (450) and
tick 17 (460), row 1 normal / row 7 powered on the same gate, also clamped ±40. Note the two
families use DIFFERENT tag rows: the taps 0/6, the charges 1/7.

The witness checks the tap fires three times on row 0 and, powered, three times on row 6.

**Process note:** the ledger has two tables, and both carry a Takano 0 row (the correction
table and the main ledger). The first attempt at this update matched the correction table's row
— exactly the mistake made with Chie 2 last round. A guard that asserts the full expected row
text (including its swap/item and body count) caught it here; keep using that pattern for every
ledger edit.

Chie 2 audit (2026-10-10, ledger slice): **all four states bound; the "no flag field" note
retired.** `shoot_body_11_2_{400,402,450,460}` fires a scratch-driven burst: the counter starts
at 1, steps one a tick, and the request fires while `counter % 3 == 1` — ticks 15/18/21/24 on
the ground tap (gate `counter < 11`) and 17/20/23/26/29 on the air tap (`< 14`). Each shot is a
`FUN_00435220` request on the posed hand — `Bip01_R_Hand` on the ground tap, `Bip01_L_Hand` on
the air tap — aiming `counter * 0.5 - 2` of lateral offset with the pitch from the target
elevation clamped ±40, so the burst walks -1.5, 0, 1.5, 3.0 (4.5 on the air tap's fifth shot).
Row 0 normal / row 1 powered; the tag branch reads `w[0x1b7] < 5` / `< 6`, the kGatePowered
idiom.

The charges fire one request — row 2 normal / row 3 powered, lateral 0, `Bip01_R_Hand`, target
elevation clamped ±30 — at tick 22 (450) and tick 15 (460). **The 460 rule sat at tick 22 while
its own comment said 15**; the body's `== 0xf` settles it, so the tick is corrected here. The
lateral walk needed one new term, `ShotSpreadSpec::lateralPerTick`, the mirror of `yawPerTick`
(Chie's burst draws nothing: the counter IS the spread), and it is witnessed exactly at -1.5,
0, 1.5 and 3.0.

**Mechanism correction.** `spread_axis_order` now returns all three axes for every order. The
earlier cut named only the pair a family draws, which silently dropped an unmentioned axis —
twice: Satoko 0's lateral under `PitchThenYaw`, and Chie 2's before the fix. The trailing axis
is unobservable because no measured family configures all three.

Rika 2 audit (2026-10-10, ledger slice): **the tag branches are bound; the normal tap's row
selector is not.** `shoot_body_4_2_{400,402,450,460}` fires one `Bip01_R_Hand` request at tick
15 in the taps and three fan requests at tick 10 in the charges. The old note said the tag
branch needed "an aim/tag flag this model has no field for" — the flag is `w[0x1b7] < 3`, i.e.
kGatePowered, and the tag branches are now bound: the tap fires THREE requests on rows 0, 2
and 1 **in that order**, and the charges fire three on row 6 against row 4 normally. The
witness checks both, including the row order.

What is still open is the NORMAL tap's row selector: `w[0x9e]` picks row 2 below 0, row 0 in
[0,1) and row 1 otherwise. It is READ in the corpus (including in FUN_0043ffc0's prologue) and
**never written anywhere in it**, so it has no recovered source; that rule keeps the row-0
reading the traces show. Every request in both branches also passes pitch 0 even though scratch
`0x3c` is filled with the clamped ±40 target elevation immediately above and then unused.

**Process note added to the ledger:** several families share byte-identical rule lines — Chie
2's and Rika 2's 400 taps, and Takano 0's 402 against Rika 2's — so a file-wide string replace
lands in the wrong table. It did while binding Rika 2, silently rewriting Chie 2's 400 and
Takano 0's 402. The fix was to revert and scope every edit to the array's own text, asserting
the occurrence count inside that scope. Future edits to this file should do the same.

Rika 1 audit (2026-10-10, ledger slice): **the tap window is now counter-gated and its
per-shot spread is bound; the charges keep their existing rules.** `shoot_body_4_1_400` fires
while `tick > 11 && scratch < 30` on EVEN scratch values — ticks 12..40, fifteen shots. The
scratch only increments inside that window, so it equals `tick - 12` and the parity is the
tick's own: one `kGateCounterMod` rule over the tick window replaces the fifteen unrolled
anchors, stated before the Counter so it reads the pre-increment value the body does. Each
shot draws `draw%14 - 7` of LATERAL offset first and then `draw%10 - 5` of pitch over the live
clamped (+-40) target elevation (L21797-21805). The hand is `Bip01_L_Hand` and the row is 0,
both from the body's own `FUN_00435220` call — the older note claiming the row came only from
the item table was wrong, and the note claiming a counter gate would be "kept explicit because
already verified" is retired.

The witness pins the window (fifteen shots), the pitch values -3/0/-4 and the lateral offsets
1/1/-5 against the canonical stream. The lateral is read off the RESOLVED origin
(`origin.localOffset[0]`), not the world position: the hand bone moves between ticks, so a
position distance would mix the fan with the animation.

**New mechanism:** the spread axes are now drawn in a stated order across three axes —
`PitchThenYaw`, `YawThenPitch`, `PitchThenLateral` (Satoko 0) and `LateralThenPitch` (Rika 1).
Rika 1 is the only measured family that draws the LATERAL first.

Review findings on the spread work (2026-10-10): **one fixed, two confirmed and carried.**

**Fixed — the spread's "lateral" axis is a YAW, not a muzzle offset.** `FUN_00435220` wraps
`FUN_00435250`, which at `0x4352a0` adds its `param_7` to the bone's own angles and runs the sum
through the sin/cos table. So the value Rika 1's tap, Satoko 0's fan, Chie 2's burst and Tomitake
2's tap draw into swings the shot; it never moves the muzzle. Only `FUN_00435450`'s world form
takes a perpendicular position. `SpreadAxis::Lateral` now adds to the aim's yaw, and the four
witnesses assert a swing instead of reading back the field the binding wrote. Their per-shot
absolutes are now ordered steps and ranges, because the stream position is not pinned — that is the
follow-up.

**Confirmed, carried — Keiichi 2's charges drop the range-based pitch.** The body has `0x457a0000`
(4000) and `0x42200000` (40): the same `base + clamp(dist*40/N, ...)` shape Keiichi 1 uses, with
N = 4000 rather than 5000 and the `*0.95` on a negative base. The rules call `aim_stored_pitch()`,
so the port adds 0 where the source adds a distance term. `aim_elevation_plus_range()` exists but
hard-codes the 5000.

**Confirmed, carried — Tomitake 2's charges are still on the adapter.** The bodies carry
`0x42480000` (50) and `0x42960000` (75): world requests 50 forward, 75 above, row 4 at literal
pitch 0. The row fix landed; the origin and pitch did not.

Rika 0's charges bound (2026-10-10, later slice): **the combo's geometry is now complete.**
The charges (L20788-20845) fire twin WORLD requests at ticks 15 and 25 with lateral `+-25`
(`0x41c80000` against the `yaw + 90` table), forward 50 (`0x42480000` against the `yaw` table)
and height +50, and they pass an explicit world YAW and PITCH rather than the target elevation:
yaw `+-5` with pitch 45 at tick 15, yaw `+-10` with pitch 30 (450) / 40 (460) at tick 25 — the
`uVar14` assignments. So `origin_actor_relative(+-25, 50, 50)` with `aim_fixed_angles(+-5, 45)`
and `(+-10, 30/40)`. The witness checks 50 apart laterally, 50 in front, 50 up, the 10-degree yaw
separation and the fixed 45 pitch.

**Note the two families differ in kind:** Rika 0's charges are a FIXED aim (the body names the
angles), while Keiichi 2's latched the target elevation and clamped it. Both are now correct;
the difference is why the aim spec has to come from the body rather than from the family.

Keiichi 2's charges bound (2026-10-10, later slice): **the combo is complete on all four
states.** The charges (L12186-12217) are WORLD requests, not attachments: the actor's position
displaced `-50` on the PERPENDICULAR axis — `0x42480000` against the table at `yaw + 90`
(`0x42b40000`) — at height +40 (`0x42200000`), with the elevation latched at tick 13 and clamped
±40. So they are `origin_actor_relative(-50, 0, 40)`, rows 2 normal / 3 powered on kGatePowered.
Witnessed exactly: -50 on X, 0 on the forward line, +40 above, at facing 0.

**Axis correction that also fixed Rika 0.** A world position is built from TWO table lookups — at
`yaw` for forward and at `yaw + 90` for perpendicular — and which one a constant multiplies is
what decides the `origin_actor_relative(right, forward, height)` arguments. Rika 0's tap
multiplies the `yaw + 90` table by ±50 and the `yaw` table by 10, so it is `(±50, 10, 70)`, LATERAL
and not forward. The earlier binding had the axis inverted, and its witness could not catch it: the
pair is 100 apart whichever axis it lies on. The witness now checks the X separation, the shared
forward line and the forward offset separately.

Rika 0 audit (2026-10-10, ledger slice): **the powered branches are bound; the twin
separation is not.** `shoot_body_4_0_{400,402,450,460}` fires TWIN world requests at tick 15
in the taps and at ticks 15 AND 25 in the charges. The taps are TWO requests on row 0
normally and FOUR on row 1 powered (L18360-18438); the charges are two on row 2 normally and
two on row 3 powered, with the pitch thirds 45/30 ground and 45/40 air (L20797-20941). The
previous binding fired row 0 / row 2 always and recorded the tag branch as "no flag field,
skipped" — the flag is `w[0x1b7] < 3`, i.e. kGatePowered. One rule per branch now carries it,
and the witness checks four row-1 requests on the powered tap and two row-3 requests on the
powered charge. Both branches use the SAME pitch thirds, so the row is the only difference.

**Bound (later slice): the pair is `origin_actor_relative(0, +-50, 70)`** — the actor's own
position displaced ±50 ALONG THE FACING at height +70 (`0x42480000`/`0x428c0000`), which is
exactly what `facing_relative(0, R)` computes. The tap fires +50 then -50 normally and
+50/-50/+50/-50 powered, witnessed 100 apart and 70 above. The charges are the same shape with
**R = 25** (`0x41c80000`) at height **+50**, still on the adapter. Earlier notes gave the tap as
±600 and the charges as ±50: both were mis-reads of the hex.

**Systemic correction.** The "no flag field" note is FALSE wherever it appears: the flag is
`w[0x1b7]`, which the port models as `kGatePowered`, verified in Keiichi 2, Satoko 0, Rika 0
and Rika 2. Keiichi 2's and Satoko 0's rules were already rebound with it; **Chie 2 (L1098),
Takano 0 (L1128), Irie 1 (L1194) and Tomitake 2 (L1399) still carry the note and their bodies
have not been re-read.** Rika 2's note was wrong too, and re-reading it showed a deeper gap: the
normal tap's row is selected by `w[0x9e]`, the powered tap fires all three rows, and every
request passes pitch 0 although the clamped scratch is computed and then unused.

Satoko 1 audit (2026-10-10, ledger slice): **bound; it was entirely unbound before.** The
port had no move program for handler 0x4b4090 at all, so the combo had no shooting behaviour.
The family is unusual and uniform: `shoot_body_3_1_{400,402,450,460}` each run the SAME
periodic fire — a countdown starts at 120, drops one a tick, and ONE world request fires
whenever it is `1 mod 30`, from the actor's own position 50 units UP (`0x42480000`), aimed
along the heading
with pitch 0, row 6 normally and row 7 powered. The charges (`450`/`460`) add one request at
tick 35 at the actor's own position with no height, row 0 normal / row 1 powered; `460`'s
tick-0 block only zeroes velocities. Not modelled: the gravity tail (`w[0x15] -= 1.5`) and the
movement-offset yaw term `w[0x19]`.

`kGateCounterMod` tests `counter % gateValue == 0`, so starting the counter at 118 lands the
fire on the body's tick 28 (118 - 28 = 90, and 90 % 30 == 0 where the body has 91 % 30 == 1).
No new op was needed. The witness pins the tick-28 landing, row 6/7, the 50-unit height and
the single request per firing.

**Corrected:** this binding first used a 600-unit height — a mis-read of `0x42480000` — and its
witness asserted 600 too, so it confirmed the binding against itself and passed while wrong. Both
are now 50. A witness that quotes the binding's own constant proves nothing; take the number from
the body.

**Measured limitation, not a binding bug:** only the FIRST fire lands, because the port's tap
move lasts about 40 ticks while the body's family runs ten states (400..409, each with its own
duration) and would fire five times. The port's shot table maps two states per form, so the
later fires need the **state/duration model widened** — recorded as an open item rather than
papered over by shortening the period.

Satoko 0 audit (2026-10-10, ledger slice): **the tap is bound; the charges keep their
existing binding.** `shoot_body_3_0_400/402` fire the salvo through `FUN_00435220` on the
posed `Bip01_R_Hand`: a loop of FIVE iterations at tick 17, EIGHT powered, all on item row 0.
Each request draws `draw%15` of extra pitch over the target elevation (latched, ±40) and then
`(draw%240-120)*0.1` of lateral offset — `(draw%300-150)*0.1` powered — so the powered branch
widens the loop and the fan, not the row. The previous binding unrolled five identical
adapter launches and its own comment recorded the powered eight as "no flag field, skipped";
the flag is `w[0x1b7]`, which is the powered gate the rest of the port already uses. It is now
one `CapturePitch` plus one repeated Launch per branch, so the two draws land in the body's
order. The witness pins the canonical stream exactly: request 1 pitches at 2 and request 2 at
14, and requests 1 and 2 sit 8.3 lateral units apart — drawing the lateral first would move
both. The fan is bounded at 23.9 units normal and 29.9 powered.

Note for the next slice: **Satoko 1 (handler 0x4b4090) has NO usage evidence at all** — the
recon's shot400 harness reaches no request on any variant, so it is a bodies-only combo. Its
`shoot_body_3_1_400` fires two WORLD requests at tick 0 on rows 6/7 at `y + 50`, then a
10 deg / 15 deg turn pair, then a hand request at tick 13 with a powered count split
(`w[0x1b7] < 6`), and more world rows 6/7 after. Auditing it needs the bodies read directly
plus a purpose-built harness — the preview cannot be trusted for it.

Keiichi 2 audit (2026-10-10, ledger slice): **the tap is bound; the charges are measured and
left unbound.** `shoot_body_2_2_400/402` fire ONE slot-0 attachment request a tick for eleven
ticks (10..20, guard `9 < tick < 0x15`), row 0 normally and row 1 powered. Each tick grows
scratch `0x3a` by 2 and aims `0x3a - 15 + draw%10` on the yaw with `draw%10 + 5` of pitch over
the clamped target elevation (compare/assign ±30 — see below), so the tap SWEEPS across roughly
±11 degrees instead of firing straight. It is the one family that takes the YAW draw first
(`0x3b` from draw 1, `0x3c` from draw 2), which `SpreadOrder::YawThenPitch` states. The
previous binding fired one straight row-0 shot a tick with no gate, no sweep and no jitter.
State 401 is the same request with an extra 15 deg phase-0 turn and no state-403 abort; the
port binds 402, the air-tap slot the rest of the roster uses, and leaves 401 unbound.

Two things are recorded rather than modelled:

* **The low pitch clamp assigns a different value than it compares.** The body tests
  `0x40 < -30.0` and then writes `-0x3e100000` (-0.140625), while the high end writes the
  +30.0 it compared. Both the body header and the handler decompilation (`FUN_0047b940.c:1825`
  and `:1884`) agree on this, so it is not a one-off transcription, but a clamp to
  [-0.140625, +30] is NOT equivalent (it would also flatten values in [-30, -0.14)). The port
  keeps the symmetric ±30 clamp, which matches both comparisons, and this quirk stays open.
* **The charges are world requests the port does not yet place.** `shoot_body_2_2_450/460`
  turn 18 deg while tick under 13 (on the movement-preserving helper), clamp the scratch to
  ±40 at tick 13, then fire rows 2/3 through `FUN_00435450` — the WORLD helper, displaced ±50
  along the facing (`0x42480000`) — and freeze 10 updates at tick 5 and 15 at tick 32. The port
  binds them through the attachment adapter with a ±50 pitch, which is a different ORIGIN
  FAMILY and a different clamp. The 600-unit term is not decoded here, and Keiichi 1's charge
  binding used the same family's shape (`origin_actor_relative(-50, 0, 40)`), so that binding
  should be re-verified against this formula before either is trusted. The rewind stalls are
  plain `Hold 10`/`Hold 15`: the body's 0x3e counter only rewinds the clock, so the observable
  timing matches and the counter adds nothing else.

Mion audit (2026-10-10, ledger slice): **Mion 0 fully bound; Mion 1 and Mion 2 have
their taps bound and their charges documented as blocked.** The three combos share one
shape — every launch is `FUN_00435000(slot, row, yawSpread, pitch, 0)`, so the attachment
slot and the item row are both explicit, and the powered gate (`byte 0x845` &&
`word 0x212`) switches the ROW only, never the slot.

- **Mion 0** (0x4582a0): 400 fires slot 0, rows 0/4 at phase-1 tick 2 (clamp ±30) and slot
  1, rows 0/4 at phase-3 tick 2 (clamp ±40) — the second only on connect, because phase 1
  jumps to phase 3 while `6 < tick && 0 < w[0xae] < 10 && fires < 6 && 0 < w[0x1b7]`. The
  hit counter `+0xae` has no port counterpart, so only the contact half is modelled and the
  port reaches phase 3 through the DAT phase advance instead of the jump. 402 is a
  three-volley air tap: scratch 0x3b counts the state and the volleys fire at counters
  15/20/25, each on BOTH slots with the SAME row (two muzzles, not two rows) — the earlier
  port bound row 1 as an unconditional second request, which fired a powered row on the
  normal branch. 450/460 fire rows 2/3 at tick 17 and then hold: 450 clamps the pitch
  asymmetrically ([-40, +45]) and freezes 30 updates, 460 clamps ±40 and freezes 20.
- **Mion 1** (0x461810): 400 fires slot 0 rows 0/4 at phase-1 tick 2 (clamp ±40) and slot 1
  rows 0/4 at phase-2 tick 1 (clamp ±30) **only on connect** (`(tick == 1) && (0 < w[0x1b7])`),
  then holds one frame at a time past tick 7 while counter 0x3b is under 1. 402 fires both
  slots at counter 13 (clamp ±40). Its 450/460 are 15-iteration bursts whose every request
  carries `(rand%200-100)*0.1` yaw and `(rand%100-50)*0.1` pitch jitter, so they stay on the
  provisional path; the measured rows are 1 normal / 5 powered at tick 17 with a ±45 clamp
  (460 compares ±30 and writes ±45).
- **Mion 2** (0x44fa10): 400 fires one slot-0 request, rows 0/1, at entry-tick 10 — the body
  FORCE-WRITES its tick counter from 10 to 18 there (`write_clock(0x2b81, 0x12)`), so ticks
  11..17 never execute and the frame-18 anchor is that same single shot. A phase clock cannot
  be written, so the port places the launch on the teleport update and shifts every later
  window by seven, which moves the tick-23 freeze to elapsed 15. 402 is the same request on
  the real tick-18 window, with a 10-update freeze at tick 23. Its 450/460 are repeated
  emissions inside phase 1 while `tick > 14 && tick % 5 == 0 && 0x3e < 10 && 0 < w[0x1c8]`:
  the count, rows 2/3, slot, clamp ±45 and cadence are bound, but the per-emission
  `(rand%100-50)*0.1` yaw / `(rand%80-40)*0.1` pitch jitter needs the RNG service and
  `+0x1c8` has no writer in the corpus, so both gaps are stated rather than implied.

The shared mechanisms this needed are now in place: `origin_attachment_slot`, `kGateContact`,
`kGateCounterEquals`/`kGateCounterAbove` (the bodies' scratch counters survive a phase change
while the phase tick does not), and `CapturePitch` taking a separate low and high bound
(12 bodies clamp asymmetrically).

**Draw service (2026-10-10, same day):** the spread is now real, so Mion 1's 450/460 and
Mion 2's 450/460 are bound with their jitter, and Rena 2's state 400 is bound outright.
`simulation_rng.h` reproduces MT19937 as `FUN_0065d150`/`FUN_0065d0c0` implement it (seed
0x1571 = 5489) and is pinned against the canonical seed-5489 vector; `ShotSpreadSpec` states
each axis's modulus/offset/scale with pitch drawn before yaw, and a zero modulus consumes no
draw so a deterministic rule cannot shift the stream. `MoveRule::repeats` carries the bodies'
`for` loops (Mion 1's 15 iterations at tick 17, Rena 2's 10), and each iteration re-draws,
which is what fans the volley. Two gaps remain recorded rather than hidden: the port applies
the spread to the DIRECTION only — the original also rotates the attachment, so the muzzle's
positional offset is not reproduced — and Mion 2's emissions still ignore the `0 < w[0x1c8]`
gate, a field at byte +0x720 with no writer in the corpus.

Keiichi 0 scope note (2026-10-10): pinned update/vtable, walk, birth, usage (normal slot 0 and powered slot 3 at 13F across six forced phases), and callback families. `shoot_body_2_0_400/402` call `FUN_00435220` on `Bip01_R_Hand` at frame 13; trace callback rows are normal slot 0/powered slot 3. The typed `NamedBone` origin can now describe a hand transform, but no posed-rig witness or body-bound rule has been added; callback row/admission semantics still need reconciliation. The four body files contain measured movement/turn windows (400 ground, 402 air, first charges 450/460). Do not claim the callback request as an admitted projectile/spawn. Keiichi 1 has now been independently audited and is also deferred (below). Raw 450/460 `FUN_00435000` row mapping is also not established from its body tuple, so charge shot rows remain unbound.

**Update (2026-10-10, Keiichi slice):** fully bound as `kKeiichi0Rules` — the tap (hand R
row 0/3 at tick 13 with stored ±30 pitch, snapped ±45 on air), the tick-4 left-hand
row 1 at fixed angles, and the tick-20 attachment pair (slot 0, rows 2/4, stored ±40
pitch). The `FUN_00435000` row mapping above is resolved by the body tuple after all
(slot 0, rows 2 normal / 4 powered). First `NamedBone` user; rig bone-existence plus
origin KIND is the witness pattern. Remaining gaps: air movement clear/halve and
gravity have no ops, and the movement-offset yaw is unimplemented.

Keiichi 1 audit / defer note (2026-10-10 10:40, São Paulo): actor `data/keiichi/01.dat`,
item `018.dat`, swap 8, handler/vtable `0x473610`/`0x6a4f28`, walk `0x473a5a`. Row-0 birth
speed 30, turn 0.1 at birth/next tick; magazines `{6,2,360,0,60,1}` and
`{3,2,540,0,180,2}`. State400 usage and both extended traces agree on one hand callback
at 13F in each of six forced phases: normal slot 0, tag slot 1, no attachment/world
requests. These are request probes, not natural phase reachability or admitted projectiles.

The independent body audit used `reference/source/shoot_native_bodies_20260929.hpp`:

| Bodies / lines | Measured request | Concrete blocker |
|---|---|---|
| 400 L8719–8834; 402 L8954–9069 | tick 13, no phase gate; `FUN_00435220` on `Bip01_R_Hand`, operand 0 normally / 1 when byte `0x845 != 0` and word `0x212 != 0` | typed named-bone origin exists, but row mapping and posed transform are not bound |
| 450 L9944–10100; 460 L10102–10258 | tick 20, no phase gate; `FUN_00435450` operand 9 then 2 normally / 3 under the same powered condition | typed world origin/aim exist, but body formulas, dynamic pitch and row mapping are unbound |

Charge geometry is explicit-world: lateral displacement 50, height +40 ground / +20 air,
yaw `source_float(0x17)+source_float(0x19)`, and scratch pitch plus a distance term clamped
0–40 (`sqrt(distance_squared)*40/5000`, scaled by 0.95 when the scratch word is negative).
Raw charge operands 9/2/3 are body observations; their runtime row/admission mapping is
not established by the state400 traces. Ground tap scratch compares/clamps to ±30; air
tap compares against ±30 but assigns ±45 outside that range. A single symmetric clamp
would lose that discontinuity even after adding a hand-origin op.

Measured locomotion: 400 phase 0 turns 20 through tick 13 and decelerates 0.5 to zero;
450 turns 18 through tick 19 and decelerates 0.5 to zero. Air bodies use the distinct
movement-preserving turn helper, zero movement (402) or halve speed (460) at tick 0,
and subtract gravity from vertical velocity. Ground movement rules alone do not justify
binding a firing program: that would replace provisional shot selection/timing while
omitting every measured firing origin. No MoveProgram was added; current fallback remains.
Satoko 2 has now been independently audited and is also deferred (below).

Verification: rebuilt Linux tree; `ginkiha_tables_test` 387 checks / 0 failures,
`fighter_script_test` 637 checks / 0 failures / 0 skipped, full CTest 65/65 passed
(162.26 s). No runtime program changed. The unrelated Windows edits remain uncommitted.

**Update (2026-10-10, Keiichi slice):** fully bound as `kKeiichi1Rules` — the tap (hand R
row 0/1 at tick 13, same snap pitch as Keiichi 0) and the tick-20 world pair (row 9 plus
row 2/3, all at lateral -50 / forward 0 / height +40 ground / +20 air, with the
range-dependent pitch now modelled as `ElevationPlusRange`). The "unbound formulas" cell
above is closed; remaining gaps are the movement-offset yaw and the air
velocity/gravity ops, as with Keiichi 0.

Satoko 2 audit / defer note (2026-10-10 10:48, São Paulo): actor `data/satoko/02.dat`,
item `038.dat`, swap 12, handler/vtable `0x4bc040`/`0x6a4fc8`, walk `0x4bc47f`.
Row-0 isolated birth speed 1, no recorded turn values (generated as zero). Magazines
`{100,2,50,0,30,1}` and `{100,2,100,0,100,2}`; two empty prop meshes and fifteen bullet
registrations. The real combo fixture confirms item38 and identity registrations 0/1/4/5,
including decoded bullet data; it does not claim firing or projectile admission.

Independent audit of `reference/source/shoot_native_bodies_20260929.hpp`:

| Bodies / lines | Measured request | Missing representation |
|---|---|---|
| 400 L16450–16601; 402 L16756–16912 | tick 20, no phase gate; two `FUN_00435450` calls, raw operand 0 normally / 1 powered | world XYZ with forward coefficient 100, lateral coefficients −50/+50, height +70; dynamic scratch pitch |
| 450 L17804–17934; 460 L18016–18147 | phase 1, tick 6; one `FUN_00435450` call, raw operand 4 normally / 5 powered | world XYZ with forward coefficient 100, lateral coefficient 0, height +70; dynamic scratch pitch |

Powered selection requires both byte `0x845 != 0` and word `0x212 != 0`. The pitch path
writes `FUN_0066b668` into scratch `0x3c`, compares/clamps the word to ±40, then reads
`source_float(0x3c)`; numeric reinterpretation needs helper confirmation. Coefficients
above are body observations, not verified world trajectories. State400 catalogs and both
extended traces record two world requests at 20F per forced phase, normal slot0/tag slot1,
with no attachment/hand requests. Their stubbed coordinates `(0,70,0)` do not validate
the forward/lateral geometry or natural reachability. No charge callback trace was supplied.

All four bodies use movement-preserving `FUN_0042dc20`: ground tap turns 15 through
19F and decelerates 0.5 to zero; air tap turns 20 through 19F, clears movement at tick0,
and subtracts gravity from vertical velocity. Charges turn 15 while phase<1; ground
charge decelerates 1.5 to zero, air charge scales horizontal/vertical velocity by 0.25
at phase0/tick0 and applies gravity in phase2 after 30F. Both charges initialize a
scratch counter at phase0/tick0 and freeze clock advancement ten updates at tick26,
with no phase guard.

**Update (2026-10-10, entry 3.0):** the tap is now bound — `kSatoko2Rules` carries the
measured twin at tick 20 with the powered gate, and `fighter_script_test` drives both
branches. The charge bodies above stay pending with their measured parameters in the
ledger. Remaining Satoko 2 dependencies: the battle movement offset (`source_float(0x19)`)
feeding the world yaw, and its vertical-velocity rules (the air charge's 0.25 scaling and
phase-2 gravity), which have no MoveRule op yet.

Verification: rebuilt Linux tree; `ginkiha_tables_test` 398 checks / 0 failures,
`fighter_script_test` 650 checks / 0 failures / 0 skipped, full CTest 65/65 passed
(162.92 s). The shared origin-pin loop now covers Keiichi 0/1 and Satoko 2 without
duplicating the catalog/usage/trace scans. Unrelated Windows work remains uncommitted.

Scoreboard: 13 full programs + 10 partial/audited programs (Rena 0 powered branches,
Rena 1, Rena 2 ring, Natsumi 0, Satoko 2 tap, Keiichi 0, Keiichi 1, Mion 0, Mion 1,
Mion 2) + 3 pinned/deferred (Kasai 0, Shion 0, Akane 2) + 25 remaining TODO = 46 roster
combos. A program is a
schedule, not coverage: see the ledger for per-path state.

## 6. Engine mechanisms you must know (all in `src/gameplay/`)

- `MoveRule{move,phase,first,last,op,value,second,third,gate,gateValue,origin,aim}`. Ops:
  `Launch(row,lateral,pitchClamp)` (legacy adapter; a typed `origin`/`aim` bypasses it),
  `Hold` (freezes elapsed; a gate makes it a bounded freeze),
  `Hide`/`Active` (slot 0..1; the executor restores bindings before each rule pass),
  `Counter`/`CounterSet` (per-move scratch counter). Gates: `kGatePowered`, `kGateNormal`,
  `kGateCounter`, `kGateCounterMod`, `kGateCounterBelow` (see the enum comment for the
  source expressions).
- `fire_shot`: exact-row programs bypass the provisional magazine scan; `-1` rows keep it.
  `m_stateTimer = programmed >= 0 ? 0 : kShotStateFrames`.
- **Hold latch** (`m_holdRule`, fighter.h/cpp): per-rule hold progress — a shared counter would
  starve a second Hold in one move (Keiichi 450: 10f@5 + 15f@32). Dash path untouched. A gated
  Hold holds only while its gate does (Rika 1: `kGateCounterBelow 60`), and the counter rules
  must be written BEFORE it so the gate reads the post-increment value.
- **Per-move counter** (`m_moveCounter`): reset with the move (`set_state`, init/reset/respawn),
  NOT per section, because a body seeds it once at phase0/tick0 and then counts updates
  including frozen ones.
- **Latched pitch** (`m_movePitch`, `MoveOp::CapturePitch` + `ShotAimKind::StoredPitch`): 106
  bodies compute the target elevation once and read it back, so write the capture rule at
  the tick that computes it and use `aim_stored_pitch()` for every later request. A body
  that re-derives the elevation per launch re-aims salvos whose target moved.
- **The powered gate** (`shoot_gate_powered()`): `m_hyperActive && m_hypermode == Oyashiro &&
  ShootingContext::aimHold`, published each tick from `Match::aim_holds()`. That is the
  original's `byte(+0x845) && word(+0x848)`; it is the roster-wide "tag"/"special"/"powered"
  branch. Bind BOTH halves of a branch with `kGatePowered`/`kGateNormal` rather than skipping
  the powered one — the old "no tag flag, bind normal, document the skip" guidance is superseded.
  **The hold half is now source-backed:** `TargetLocks` carries the `+0x300` aim layer beside
  the untouched combat-lock layer, and the per-tick re-pin/decay implements the recovered
  same-target-as-player-0 comparison (architecture record §2.2). Aim selection, combat lock
  and camera selection are three distinct states — never substitute one for another. The port
  still arms Oyashiro on a Special press where the original arms it automatically, keeps no
  state-0x1e gate, and halves Hanyu+1's 30 s window to 15 s; those deltas are recorded, not hidden.
- **Update order**: input/fire → `execute_move_program` (rules see PRE-increment elapsed) →
  `advance_animation_phase` (increments). Consequence for tests: a `while elapsed<N` loop
  exits right after the tick that SET N, whose rule pass still saw N−1 — add ONE more tick
  before taking pendings. Fixed-count drives (Rena: exactly 12 post-release ticks) also work.
- **Phase resets elapsed** (`enter_phase`): long bursts spanning phases need elapsed-driven
  loops with caps, never fixed counts (Mion 2 precedent).
- **Charge driver:** use the shared hold_yellow fixture helper, which waits for the actual
  tier. Original charge is initial30 updates plus SECOND magazine threshold; earlier MAIN
  chargeMax/float-accumulation instructions were provisional and are superseded.
- Admitted requests now use a growable FIFO; the independent global32 projectile pool
  remains a capacity audit for Kasai0 and simultaneous volleys.
- `m_moveElapsedTicks` resets in `set_state`/`enter_phase`/init paths.

## 7. Known gaps — do NOT guess these (document, defer, or extend the engine deliberately)

- **Kasai 0 pending:** 21 normal /31 tag requests need spread/RNG and an audit of global
  projectile capacity. The eight-pending queue was removed in the shared ammo migration;
  that alone does not establish admitted/spawned scatter counts. Pins stay as evidence.
- Tag/aim branches now HAVE a flag: `kGatePowered`/`kGateNormal`. Unbound secondaries are
  still a documented gap per combo, but they are no longer unrepresentable.
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
