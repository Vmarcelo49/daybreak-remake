# Direction status — the task list and the work reports

> The working document. [`DIRECTION.md`](DIRECTION.md) says **why** and sets the
> gates; this file says **what is next, who is on it, and what came out**. The
> metric is [`SCOREBOARD.md`](SCOREBOARD.md), blockers go to
> [`QUESTIONS.md`](QUESTIONS.md), owner overrides to
> [`EXCEPTIONS.md`](EXCEPTIONS.md), and the enforcement rules are in
> [`../AGENTS.md`](../AGENTS.md).
>
> The plan plus these four status documents are the only places state is
> written. Do not open another ledger.

> **Plan alignment (2026-10-14).** The task rows below were realigned with the
> revised, offline-first [`DIRECTION.md`](DIRECTION.md) at the owner's request;
> the alignment entry is the last item in the work log. Aligning documents is not
> approval of an unwritten fixture/coverage contract, a pilot budget, a green
> verdict, or a lift of the freeze: bounded baseline, evidence-inventory and
> feasibility work may proceed, product integration waits for the explicit gates
> in `DIRECTION.md` §4 Phase 2 and §5. The work log is append-only and unchanged;
> entries written under the previous plan stand as history.

## Current snapshot (2026-10-30) — authoritative over older cells

| Item | Current value |
|---|---|
| Plan | Reference core approved 2026-10-30: [`DIRECTION.md`](DIRECTION.md). Everything below this section under Phases 0-3 is the closed pilot's history |
| Metric | **0/46 running under `--sim=core`** ([`SCOREBOARD.md`](SCOREBOARD.md)). Closed: 1/46 under contract v3 |
| Original-runtime parity | **not verified** |

The measured numbers inside old task cells and the whole work log are **historical**. The
work log stays append-only; corrections go into new entries, never edits of old ones.

## Reference-core milestones

| ID | Task | State | Artifact |
|---|---|---|---|
| M1 | `foundation_sim`, `simctl`, 46/46 and determinism tests, mutation check | done 2026-10-30 (`49ed7dcc`) | `remake/foundation/src/sim/`, `sim_core_test` |
| M2 | Trust report: fuzz, invariants, coverage map, comparison with independent evidence | done 2026-10-30 (`6c575915`) | [`reports/m2-trust-2026-10-30.md`](reports/m2-trust-2026-10-30.md), `sim_oracle_test`, `scripts/sim_trust.py` |
| M3 | `game::BattleView` over the legacy path | done 2026-10-30 (`6ff07484`) | `src/game/battle_view.h`, `src/gameplay/legacy_battle.h`, `battle_seam_test` |
| M4 | `--sim=core` backend, starting with Rena+0 poses; owner playtest | doing: the battle presentation, front-end flow and audio are wired (`b773954c`, `1e7200c7`, `11a04469`, `ec0c9d83`); the core's camera not committed; closing owner playtest remains | `src/sim/core_battle.h`, `sim_pose_test`, scripted captures |
| M5 | Default switch and legacy deletion in its own commit; owner approval | todo | recorded pre-cleanup revision |
| M6 | Product work ordered by the owner | todo | — |

## Rena+0 frame-data audit (2026-10-29)

**Correction of record.** V3-47 had `+0x40` as a countdown and `+0x54` as vertical.
`FUN_00428510` case 0x71 uses `+0x40` as vertical velocity, `+0x54` as horizontal
speed and `+0x58` = 0.3 as per-update gravity. The original selector (slot 7) runs
before the gated executor, and hitstop ends movement one update before it releases
the executor. Original binary SHA-256:
`27e61475fbb3ea67f5058e3e0e6e93ad71d16a4d83fa42b02e605913a6a07f02`.

**Verified and corrected**, each with a regression that failed first where a fix
was involved (tier 2 recovered code + tier 4 install-backed tests): record layout,
periods and the `record_at` cursor; attacker and victim hitstop, including the
round-reset and stagger-window gates; row 310's premature 27-tick cutoff; row
341's chain lifetime (guard test, not a failing-first case); the 113–116 flight
law and the knockdown/get-up rebind; delayed rows 104/105/204/205 (Q24); and
powered projectile row 8 → explosion row 10 (Q23); and the live contact window of
every reachable melee row, including the 300→301→302 and landing chains and the
EX's eight hand records, plus row 370's charge binding and phase-2 launch, the row
2→3 explosion child, and Q25's six projectile rows; and the
shot charge is now asserted before the action branches (`FUN_00445ee0:17-19`),
which fixed a port-only reset that made the airborne second charge unreachable.
The 300 contact fixture's
recovery anchor moved 22 → 26 under the owner-approved correction; that tick is a
port trace, and the placement helper resets the victim, so it is not a real combat
chain.

**Now covered by unit tests** (install-backed, real inputs): the live contact
window and reaction row for every reachable melee row — 300, 301, 302 (the real
300→301→302 chain), 310, 311, 320, 330, 331, 332, 340 and 341 (the landing chain)
and the Hyper EX 350 (all eight shipped hand records become the live volume and
the hit plays reaction 130). Fixtures still assert contact only for
`rena0-hit-ground-300`.

**Projectile coverage:** both stage-triggered explosions are now install-backed —
powered row 8 → child 10 (Q23) and unpowered row 2 → child 3 (wall spawn, record
window through age 9, one 15-damage contact). **Q25 projectile rows implemented:** the model gained an explicit initial yaw offset and
a growing degree-based turn rate; rows 4/6/7/9/13/14 now carry their recovered speed,
lifetime, ±45/±60 launch yaw and wall child 5, with tests for each. Named approximations:
0x3c's vertical 20, the sub-degree inner steering, the aim jitter and the particles.
**Every attack row in the pilot scope is now covered.** Shots: 400 (fixture), 401/405/406/407/408
(walking and dash tap routes, bound state and frame-12 row-0 request), 402/450/460/360 (existing
tests) and 370 (Red charge survives the jump, binds 370, fires rows 11/12 on phase-2 frame 2).
Handler-only rows 351 and 404 are pinned as never selected by any admission sweep. Recovery
states 409/469 are not attacks and stay outside this list; their rules exist but have no
dedicated test.

**Provisional values left in code:** the legacy preview window 5/8/17 and radius
130 on the preview/COM path, and `resolve_swing`'s first-record preview (row 350's
1000-power opening record instead of its 3000-power finisher). Motion conventions
still tier 6: the +100 back-row sign (205's recovered seed keeps the front sign;
the port inverts it except for 216) and `fabs(combat[17])`, which turns 25 shipped
negative impulses upward.

**Ceiling:** tier 2 recovered code and tier 4 install-backed tests. No original
runtime was executed, so original-runtime parity is not claimed.

## How to use this file

1. **Before starting:** find your task by ID below and confirm it passes the
   three-question test in `AGENTS.md`. Set its State to `doing` and put your role
   in Owner. If the work you need is not a row here, it is either a
   `QUESTIONS.md` entry or a change to `DIRECTION.md` — not a new task invented
   locally.
2. **When finished:** set the State, put the path or command that proves it in
   Artifact, and append one line to the Work log. **A task is not `done` without
   an artifact** (`AGENTS.md`, evidence tiers).
3. **Never rewrite the Work log.** Append; correct a wrong entry by adding
   another. Change a task's plan only by editing `DIRECTION.md` first.
4. States: `todo` · `doing` · `blocked` (name the question ID) · `done` ·
   `dropped` (say why).
5. Owners are roles, not people: `coordinator`, `harness agent`, `pilot agent`,
   `owner` (the human).

### Retired task orders

These were real plan rows and are **not** work orders any more:

| Retired | Why | Now |
|---|---|---|
| Trace schema v1 with per-actor-per-tick rows; original-side producers; the **L1/L2 fallback ladder** (tracer DLL, host-side reader chosen per trace) | `DIRECTION.md` §4 Phase 1 replaces the tracing platform with an offline fixture runner and contract; building one is outside the plan (`AGENTS.md`, work mandate) | F1-3, F1-4, F1-8, F1-9; the reader/tracer tooling survives only as historical capability evidence (work log, "Optional live observation" below) |
| Deterministic input to the original; deciding an original-side **input-injection route** | Frame-perfect original-game input is not viable for this plan (`DIRECTION.md` §2.3); menu delivery is not deterministic combat input | dropped (P1-13); the proven menu driver is optional observation only |
| Reconstructing the reference's **59 compared field names** and adopting its 59-field posture | `DIRECTION.md` §4 Phase 1 step 3 and §5 item 3: the contract is chosen for observability and pilot relevance, not to reproduce 59 | F1-2; the count 59 is evidence about the reference, not a schema |
| **Delete the Rena+0 hand path before the verdict** (as a pilot completion criterion) | `DIRECTION.md` §4 2f/2h: keep the legacy path through the owner's verdict; deletion is the separate 2h cleanup | P2-8 (rollback check, do not delete) and P2-10 (cleanup only after green) |
| **D14's exact-trace prerequisite and D15's "60 Hz is implemented" implication**, as they read in `remake/docs/decisions.md` | Owner decisions are not edited; `AGENTS.md`'s precedence table now states that those two implications do not override the revised plan. Original-runtime parity is a separate claim, and D15 stays an intended change until P0-10 lands and F1-9 asserts it | P0-10 (apply and test the cadence), F1-9 (assert it), P2-9 (parity reported separately). The historical D14 record in P0-3 stays; no original-harness task is resurrected |

## Tasks

### Phase 0 — baseline and plan alignment (`DIRECTION.md` §4)

| ID | Task | State | Owner | Artifact |
|---|---|---|---|---|
| P0-1 | Review and park the uncommitted WIP: inspect the actual current staged/unstaged baseline and preserve it in reviewable parts or unchanged. **Never discard an uncommitted diff** (`DIRECTION.md` §4 Phase 0); the historical 16-file count is stale | done — reviewed, preserved unchanged, and now mapped into a five-part commit plan; **nothing committed** (no commit requested) | coordinator | work-log entries 2026-10-16 (baseline review; commit plan); inventory: 56 modified tracked + 10 untracked, empty index |
| P0-2 | Inspect the stale branches/worktrees and their unique commits (`refactor-*`, `fix/live-input`, `gate-baseline`) and show the owner. Removal is **optional housekeeping**, not a prerequisite for character validation | done — listing shown to the owner 2026-10-16: **zero unique commits anywhere** (all tips are ancestors of `main`), every worktree clean, no stashes; the owner then approved removal, and it was carried out the same day: all five worktrees removed and the four fully-merged branches deleted (no commit lost, ~1.4 GB freed); `ginkiha-help` kept because it also exists on `origin` | coordinator | work-log entries 2026-10-16 (listing, then removal + verification); `AGENTS.md` Git section |
| P0-3 | Record decision **D14** and the freeze list | done | coordinator | `remake/docs/decisions.md` D14; `../AGENTS.md` "Frozen work" |
| P0-4 | Verify the original binary pin with `sha256sum` | done — **re-verified 2026-10-16** against `Higurashi-Daybreak/DaybreakDX.exe`, exact match | coordinator | `27e61475fbb3ea67f5058e3e0e6e93ad71d16a4d83fa42b02e605913a6a07f02` |
| P0-5 | Create the status documents and point `AGENTS.md`/`DIRECTION.md` at them | done | coordinator | this file, `SCOREBOARD.md`, `QUESTIONS.md`, `EXCEPTIONS.md` |
| P0-6 | ~~Banner the REPLACE files with the `PORT-REPLACED` line~~ | dropped | — | the current plan does not authorise it: the REPLACE files are frozen decisions and do not need banners. The convention itself is history (work log 2026-10-14); no independent banner task |
| P0-7a | Align the task rows, enforcement wording and scoreboard with the offline-first plan (`DIRECTION.md` §5) | done — documentation only; no contract approval or pilot verdict | coordinator | this file; `AGENTS.md`; `DIRECTION.md`; `SCOREBOARD.md`; final alignment work-log entry |
| P0-7b | Resolve the obsolete Q8/Q9 implications in `QUESTIONS.md`: menu delivery is not deterministic combat input, and 59 is not a schema (`DIRECTION.md` §5 item 4) | done — historical answers preserved; superseded implications marked | coordinator | `QUESTIONS.md` Q8/Q9 and final alignment work-log entry |
| P0-8 | Issue hygiene: close the character/combat issues so the tracker stops recruiting frozen work | done | coordinator | 27 closed 2026-10-14 with a pointer comment; 8 remain open (web #58–#60, renderer #61/#38, tooling #63, netplay #3) |
| P0-9 | Give the two parallel tracks separate build dirs (`build/linux-harness`, `build/linux-pilot`) and confirm `tools/harness/` + `local-data/harness/` | dropped — the check was done and the split is unnecessary: there is **no parallel C++ track** (the harness tools are Python and share no build), the tree already carries nine build dirs, and adding two unused ones is configuration nobody reads. Confirmed 2026-10-16: `tools/harness/` exists (8 files, untracked and **not** ignored) and `local-data/harness/` exists (14 files) and **is** ignored by `.gitignore:29` | coordinator | work-log entry 2026-10-16 (P0-9 check) |
| P0-10 | **Move live simulation to 60 Hz (D15)** — after P0-1, since the WIP touches the same files | done — `FixedStep::tickRate` is **60**; the scripted/`--out` capture domain is the derived `scriptedCaptureRate`/`scriptedCaptureSeconds` (1/60, D9); 131 test step literals converted to `FixedStep::seconds`; live-path and standing-doc statements updated, dated records/quoted run output preserved; full suite **72/72** | coordinator | `fixed_step.h`; `fixed_step_test.cpp` F1-9 assertions; work-log entry |
| P0-11 | Verify the Windows rematch really no longer faults (#57), then correct `README.md` and `RELEASE-CHECKLIST.md` | todo — deferred to Phase 4; not part of the Phase 0–2 baseline and not a step toward the pilot | coordinator | build windows + play two rounds under Wine; `QUESTIONS.md` Q7 |

### Phase 1 — evidence assembly, minimal fixture (`DIRECTION.md` §4 Phase 1)

No row here requires frame-perfect original input, a new tracing platform or a
save-state/emulator project. A missing artifact is recorded as missing
(`DIRECTION.md` §4 Phase 1 step 1).

| ID | Task | State | Owner | Artifact |
|---|---|---|---|---|
| F1-0 | Ask the owner to request the author's existing verification material: field definitions, defined/raw classification, capture tooling, initial-state and RNG setup, input banks, comparison rules. **Not a blocking dependency** | blocked on the owner request (not on bundle evidence) — narrowed by F1-1: most material is already on disk (traces for all 46 combos, original-vs-runtime evidence TSVs, catalogs, a bundle verifier, and a manifest whose `reference_exe_sha256` **equals our pinned binary**). Ask only for the five missing items listed in the F1-1 report; still not a blocking dependency | coordinator | F1-1 report section; `QUESTIONS.md` Q12 |
| F1-1 | Inventory available inputs and evidence in `.local-analysis/`: bundle bodies and control headers, the existing validation artifacts, addressed body code, service dependencies; record what is missing as missing | done — inventory recorded below; **five items named as missing** (59-field names/classification, original capture tooling, input bank + RNG/initial state, comparison rules, `roster-walk-profiles.json`) | harness agent | F1-1 report section; work-log entry 2026-10-16 |
| F1-2 | Define the **minimal independent contract** for the pilot: observable, pilot-relevant fields with units, sampling domain, provenance, tolerances, exclusions and expected transitions/events. Independent schema, **not** a reconstruction of the reference's 59 fields | done — F1-2's draft; the same document was approved as **v2 on 2026-10-16** and is now **v3, approved 2026-10-22 plus the 2026-10-29 correction** for the stated Rena+0 scope (§1-§11 incl. the acceptance map §2b); acceptance stays 0/46 until the 2g verdict | pilot agent | [`PILOT-EVIDENCE-CONTRACT.md`](PILOT-EVIDENCE-CONTRACT.md) |
| F1-3 | Build the deterministic offline fixtures: combo, actor state, input and previous-input, RNG state or deterministic service response, move/item data identity, service outputs, expected body effects; expectations cite code or independent artifacts | done — schema + runner + **19 source-cited fixtures covering all 11 target cases**: locomotion, four ground dashes, jump chain, air dash, guard, tap shot, charge tiers, the whole 300-family string (300/310/311/320/330/331/332, the last two new evidence) and hit/KO through posed-volume placement. Findings recorded as open questions: row 300's melee active window shifts from 14–19 to 25–30 with the opponent out of reach, and `koCredits[0..1]`/`overkillHits[0]` stay 0 after a KO while the victim's balloon reads 20 | pilot agent | `tests/fixtures/rena0/*.fixture` (19 at freeze time; the runner now carries 30 fixtures / 31 case rows / 49 fields — see the snapshot); `tests/rena0_fixture_test.cpp`; contract §8/§10
| F1-4 | Run fixtures repeatedly and report differences, including a deliberately wrong input/output or adapter mutation that the comparison must catch; missing required fields and skipped required cases fail acceptance | done — recorded campaign: 3 runs byte-identical, wrong **input** and wrong **output** both caught, unknown field rejected, four missing-required-field cases and an empty fixture directory all fail, and a failure cannot hide beside a pass (`FAIL (1 of 2)`); the only skip is no-install (exit 77, never a pass) | pilot agent | contract §9; Appendix A (F1-5 seeded failure) |
| F1-5 | **Controlled in-port Rena+0 feasibility experiment:** after baseline/WIP review, a device-free test linked to `foundation_gameplay` drives the real `Match`/`Fighter` through grounded idle → walk → turn → stop with real combo data and a neutral equipped dummy. Reset per case, step startup normally, use the declared port cadence. Run the attributed recovered idle/walk control observation-only; assert source-backed outputs and repeatability without applying them or changing the default path. Keep phase/clocks legacy and unresolved mappings explicit. Optional regular-port `--live-debug` inspection follows; scripted capture's open-field collision limits must be declared. No separate simulation runner or authoritative integration required | done — observation-only feasibility probe passes locally; the hardened **contract**, coverage approval and pilot verdict are **not** given | pilot agent | `remake/foundation/tests/rena0_locomotion_observation_test.cpp`; `remake/foundation/src/gameplay/native/rena0_locomotion_observation.h`; `docs/PILOT-EVIDENCE-CONTRACT.md` (a draft at the time; later approved — see F1-2/F1-7); work-log entry below |
| F1-6 | Run the fixture path and the comparison from a documented command with no manual steps | done — one documented ctest/build command runs the F1-3 fixtures and the F1-5 probe device-free; exit 0/1/77 defined. Recorded in the contract rather than `tools/harness/README.md`, which is untracked historical tooling awaiting the owner's Part E decision Plus the P2-5 body tests, which run in the same documented ctest call (or directly as `./build/linux/rena0_body_test` and `./build/linux/rena0_admission_body_test`, the latter exiting 77 without game data). | harness agent | [`PILOT-EVIDENCE-CONTRACT.md`](PILOT-EVIDENCE-CONTRACT.md) §8 "Commands" |
| F1-7 | Freeze a candidate contract for owner review: covered and uncovered cases explicit; this is not approval. After P2-0b approval, changes to acceptance fields, tolerances or exclusions need a version bump and owner approval | done — **v1 frozen for review, revised to v2 after the owner's four review items, and APPROVED 2026-10-16** (`sha256 c5df99313725d80ee1ba9ae8d7161d4ca252512349ac65e962f37730565a18c6`) for the stated Rena+0 scope: fields, units, sampling, tolerances, exclusions and the coverage matrix are explicit; approval stays at P2-0b and any post-approval change needs a version bump | pilot agent | [`PILOT-EVIDENCE-CONTRACT.md`](PILOT-EVIDENCE-CONTRACT.md) (approved; v2 was superseded by v3 and the 2026-10-29 correction) |
| F1-8 | Coverage matrix over the §4 Phase 2 target cases (idle, walk, ground dashes, jump/landing, air dash, tap shot, charge levels, 300-family melee string, guard, hit, KO) with an explicit status and evidence tier per case — listed is not covered | done — matrix names status, evidence and tier per case: **11 of 11 covered / 0 partial / 0 untested-but-unlisted**, with two findings carried as open questions (melee-window distance dependence; KO credit counters) rather than folded into the claim | pilot agent | contract §10 |
| F1-9 | Confirm the shipped cadence and the port's fixed-step domain are the same number after P0-10 (one assertion, not a document) | done — `fixed_step_test.cpp` asserts `tickRate == 60` and `scriptedCaptureSeconds == seconds`; the live diagnostic prints the cadence from `FixedStep::tickRate` instead of a second literal | harness agent | `fixed_step.h`; `fixed_step_test.cpp:19-24` |

Rebuilt from the plan's own steps, so the retired IDs next to them keep their old
meaning only as history:

| Retired ID | Was | Superseded by |
|---|---|---|
| P1-1 | Specify trace schema v1 (fields, units, per-actor-per-tick row) | F1-2 (minimal contract) |
| P1-2 | Port-side per-tick producer reusing `--live-debug` | F1-3, F1-6 |
| P1-3 | Original-side producer, rung L1 (tracer DLL) | dropped: out of scope (`DIRECTION.md` §4 Phase 1) |
| P1-4 | Original-side producer, rung L2 — host-side reader | historical capability evidence only (P1-4x below) |
| P1-5 | Deterministic input to the original | dropped: out of scope (`DIRECTION.md` §2.3) |
| P1-6 | Differ/report tool over the two traces, per field per tick | F1-4 (fixture comparison) |
| P1-7 | First end-to-end scenario (stage04, 4 actors) and the first diff report | F1-3…F1-5 |
| P1-8 | ~~Silent-launch procedure for original-side runs~~ | dropped (Q2 answered 2026-10-14: muting is courtesy only) |
| P1-9 | Freeze trace schema v1; record the fallback rung per trace | F1-7 (freeze the contract) |
| P1-10 | Reconstruct the reference's 59 compared field names | F1-2: the contract is independent, not a reproduction of 59 |
| P1-11 | Cadence assertion (shipped vs harness domain) | F1-9, unchanged |
| P1-12 | Decide the original-side input-injection route | dropped: out of scope (`DIRECTION.md` §2.3) |
| P1-13 | Get the original into a battle and prove the actor read | historical capability evidence only (P1-13x below) — `+0xae04` is an animation frame index, so this was a sampled read, not a per-update trace |

#### Optional live observation (not a Phase 1 gate)

Historical capability only; usable for a named unresolved question inside the
attempt ceiling and the desktop-safety rules (`DIRECTION.md` §4 Phase 1,
"Optional original observation"). None of it is required by F1-0…F1-9.

| ID | Record | Status | Owner | Artifact |
|---|---|---|---|---|
| P1-4x | Host-side reader (subreaper + `process_vm_readv`) and the menu driver into a battle | recorded fact, 2026-10-14 (work log: P1-4, P1-13; not re-executed by this alignment). Reachable path: `process_vm_readv` works once the reader sets `PR_SET_CHILD_SUBREAPER` and spawns Wine itself; a live battle was reached and four actor pointers read from `DAT_006cfae0` | coordinator | work log 2026-10-14; `tools/harness/`, `tools/harness/README.md` |
| P1-13x | Live-actor read inside a battle: four actor pointers and `+0xae04`/`+0xadf4` advancing | recorded fact, 2026-10-14 (work log: P1-13; not re-executed by this alignment). `+0xae04` is a per-actor animation frame index that wraps on animation change (`DIRECTION.md` §2.2), so this is **sampled** runtime state, not a coherent update-indexed trace, and it does not make the original's per-update behaviour settled | coordinator | `tools/harness/README.md`; existing `local-data/harness/` shots |

### Phase 2 — reversible Rena+0 pilot (`DIRECTION.md` §4)

Only Rena+0 (`character_index()==0`, weapon slot 0, item 001) is in scope. None
of the rows below is authorized to delete the legacy path before the owner's
verdict.

| ID | Task | State | Owner | Artifact |
|---|---|---|---|---|
| P2-0a | **Pilot budget approval** — agree a bounded implementation budget for the pilot before integration (`DIRECTION.md` §4 Phase 1, "Time and scope"; §5) | settled by the owner 2026-10-16: **no fixed cap** — implement step by step and have the measured effort reviewed after each row, stopping at any scope growth. Gates 2e/2f integration only | owner | `EXCEPTIONS.md` or `QUESTIONS.md` entry recording the budget |
| P2-0b | **Contract/coverage approval** — owner approves the coverage matrix, field meanings, tolerances, exclusions and the Option A/B choice after the seam audit (`DIRECTION.md` §5) | done — **APPROVED 2026-10-16** (contract v2, `sha256 c5df99313725d80ee1ba9ae8d7161d4ca252512349ac65e962f37730565a18c6`) for the stated Rena+0 scope. The owner rebuilt and ran five suites (all passed, none skipped) and independently repeated four enforcement mutations (missing fixture, case declaration, field declaration, required assertion) — each failed as intended. The approval carries the seven declared unsupported fields, the fixture manifest and the per-observable tolerances. **Acceptance stays 0/46 until the 2g verdict**, and any post-approval change to acceptance fields, tolerances or exclusions needs a version bump | owner | recorded approval in `SCOREBOARD.md`/`QUESTIONS.md`; the approved contract |
| P2-0c | Route decision support for P2-0b: present the seam cost against Option A and Option B | done — route support presented as `PILOT-SEAM.md` §1-§12 with the per-family Option A/B split, and the owner chose **Option A with a bounded `BattleWorld` façade** (Q18, 2026-10-16); the remaining P2-1 work is the host-side scheduling count, not the route decision | pilot agent | [`PILOT-SEAM.md`](PILOT-SEAM.md) §11-§12; [`QUESTIONS.md`](QUESTIONS.md) Q18 (answered)
| P2-1 | **2a — seam spec, quantified:** every field the selected bodies read/write, services invoked, effects returned, including animation, movement, RNG, targeting, hit/contact and projectile lifecycle; count fields/services and estimate glue. If the seam needs most of the reference actor/services, stop and present Option B | done — seam quantified end to end: **17 locomotion fields / 4 services**, 13 Rena bodies (~950 lines) plus ~40 shared/generated bodies, the air-shot/jump families measured at **zero** world/bone references, and the charge family's `BattleWorld` need bounded to five requirements (§12) and decided by the owner as Option A (Q18). Option B trigger does not fire | pilot agent | [`PILOT-SEAM.md`](PILOT-SEAM.md) §1-§13; [`QUESTIONS.md`](QUESTIONS.md) Q18 (answered) |
| P2-2 | Which RNG the bodies expect, and whether `character_moves` needs new fields for them (`DIRECTION.md` §7 KEEP row) | done — the recovered locomotion seam consumes **no RNG** (no draw in its four headers), and the port already carries the recovered MT19937 (`SimulationRng`, `FUN_0065d150`/`FUN_0065d0c0`) fed through `ShootingContext` (`match.cpp:44,203`). No new `character_moves` field is needed for locomotion: its phase duration and gate are already parsed. Seeding is not exposed (named gap) | pilot agent | `PILOT-SEAM.md` |
| P2-3 | Confirm the EVIDENCE-ONLY call on `ginkiha_tables.h` (verified 2026-10-14: only its own test includes it; deletion needs owner sign-off) and the REPLACE call on `rena_dash_admission.h` (verified 2026-10-14: no product include; deleted with its test when the pilot's replacement is accepted) | done — verified on this revision: `ginkiha_tables.h` is included only by `tests/ginkiha_tables_test.cpp` (EVIDENCE-ONLY confirmed), and `rena_dash_admission.h` only by `tests/rena_dash_admission_test.cpp` with no product include (REPLACE confirmed). Deletion of either still needs the owner's sign-off at its gate | pilot agent | `PILOT-SEAM.md`; `git diff` at the gate |
| P2-4 | **2b — explicit actor context:** per-field provenance mapping each field to an existing product field, a justified new field, or a named unresolved dependency — no silent zeroes; update order, previous-input semantics, service ownership | done — increment 1 (locomotion fields, §7-§9) and increment 2 (§14: shot-body and melee-admission field maps, the 11 event kinds, update order and service ownership). Notable reuse found rather than assumed: `melee_admission.h` already implements the recovered admission with its priority gate (Rena `boosted` arm a named gap) and `move_behavior.h` already encodes the recovered shot programmes. Unresolved items named, none zeroed | pilot agent | [`PILOT-SEAM.md`](PILOT-SEAM.md) §7-§9, §14 |
| P2-5 | **2c — offline body tests:** exercise the recovered bodies through the F1-3 fixtures independently of product integration; check state, move, phase, motion and emitted service/events where supported; label source-backed expectations as source-backed | done — **increment 1 (explicit-input body tests) and increment 2 (fixture-linked differential) complete**: two offline body tests, 77 checks, no Match/Fighter in the loop. `tests/rena0_body_test.cpp` (data-free, 53 checks) feeds explicit scalars into the recovered locomotion body: idle entry/tail/gauge refill and its 1000 clamp, the walk admission and release proposals, the recovered 7.2 speed, direction categories with the 20→19 turn decay, the stop-word suppression, strict phase completion and the held gate, plus the body's own validators (state 43/1, grounded 2, gauge 2000 all rejected) and an invariant sweep over **3456** input combinations with 0 violations. `tests/rena0_admission_body_test.cpp` (install-backed, 24 checks, skip-not-pass at 77) pins the recovered melee admission against explicit inputs and the real move table's priority gate: dash sources 330/331, directional 310/311, landing 340 and the 340→341 follow-up, the 300→301→302 chain, the airborne 332/320 split and the weapon-2 exclusions. Findings: the gate is **data-driven, not structural** — the real table refuses 300 out of row 310 and 320 out of row 15 while admitting them from permissive sources, and those refusals are asserted as cases; an env-gated `RENA0_ADMISSION_MATRIX=1` prints the reachable set. Shared-source agreement with the bundle body is labelled a consistency check, and the port's decided `boosted` gap is not asserted. **Increment 2** — `tests/rena0_differential_test.cpp` drives every fixture's own input script through BOTH the production Match/Fighter and the recovered locomotion body (the F1-5 mapping), classifying each tick as in-domain (grounded Idle/Walk, established axis mapping, no victim placement) or out-of-domain, then comparing the body's own decisions. Measured across the set: **313 in-domain ticks compared** (540 out-of-domain, 7 transition ticks), state admission **313/313**, walk speed **312/313**, clock **313/313** and turn step **313/313**; the only divergence class is the already-recorded `speed-retained-on-stop` on **1** tick. Fail-closed in both directions, mutation-verified: a wrong expectation yields `unexplained=7` and exit 1, and a fixture set with no in-domain ticks exits 1 with `no in-domain ticks were compared`; without game data it exits 77, never a pass. The 7 `clock` mismatches seen while authoring were all transition ticks where the body correctly resets its paired clocks — the harness now applies the transition rule instead of the strict arithmetic there, which is why clock agreement is 313/313 rather than 306/313. The row's *emitted service/events where supported* clause is explicitly vacuous for these two bodies — neither the locomotion body nor the admission returns events or calls a service; the service needs the locomotion body does have are listed in [`PILOT-SEAM.md`](PILOT-SEAM.md) §7-§9, and the shot body, which is the one that emits event kinds, is not adapted yet: its event surface is mapped in §14 and is P2-6/resolver scope | pilot agent | `tests/rena0_body_test.cpp`, `tests/rena0_admission_body_test.cpp`, `tests/rena0_differential_test.cpp`; [`PILOT-EVIDENCE-CONTRACT.md`](PILOT-EVIDENCE-CONTRACT.md) §8 |
| P2-6 | **2d — one binding owner, limited to the pilot seam:** resolver in `src/gameplay/native/` with explicit move/phase/set and fallback reasons; pilot path only, legacy default unchanged; no global rerouting of the other 45 combos. Test model bounds, equipped weapon, phase changes and the side-dash regression | done — **the isolated resolver is implemented and pilot-path only.** `src/gameplay/native/rena0_resolver.h` is the single binding owner: a host-filled `Rena0ResolverView` (scalars from [`PILOT-SEAM.md`](PILOT-SEAM.md) §14, never a Fighter reference) goes in, and **explicit move/phase/set plus fallback reasons** come out — `resolve_rena0_set` (row → phase → set, bounds-checked against the rig), `resolve_rena0_locomotion` (the recovered body picks the state, the row follows), `resolve_rena0_admission` (the recovered admission picks the row) and `resolve_rena0_weapon` (the two-halves rule). Named reasons replace silent zeros: `set-out-of-model-bounds`, `no-move-table`, `no-move-row`, `move-row-absent`, `phase-set-unbound`, `admission-refused`, `not-a-locomotion-state`, `airborne-set-unresolved`, `armed-special-unrecovered`, `weapon-unbound`, `weapon-data-absent`. Unresolved seam dependencies are **named rather than guessed**: the boosted (armed+ready) arm sets `boostedGap`, and an airborne proposal returns no row. `tests/rena0_resolver_test.cpp` covers the row's four named areas — model bounds (including a rig one anim short), equipped weapon, phase changes (row 20's three phases resolve their own differing sets) and the side-dash regression (23/24 ± back → 330/331, and the forward dash branch still does not collapse) — 46 checks. **Unwired is verified, not asserted:** the test walks all 162 source files and fails if anything under `src/` includes the resolver; both that guarantee and the bounds check are mutation-tested (a temporary include in `main.cpp` fails the scan; disabling the bounds check fails 3 checks). Nothing in the default path changed and the other 45 combos are not rerouted | pilot agent | [`rena0_resolver.h`](../remake/foundation/src/gameplay/native/rena0_resolver.h); `tests/rena0_resolver_test.cpp` |
| P2-7 | **2e — integration behind the flag** (`--native-actions=rena0` or equivalent): recovered bodies drive the pilot and presentation consumes their outputs. Compare the adapter against the standalone fixture runner, then run deterministic scripted port scenarios with `--no-audio`; cover RNG/service results and gameplay-relevant projectile/contact dependencies | doing — **slice 1 (observe) and slice 2 (drive, locomotion) done**: `--native-actions=rena0` first observed the recovered body against the port (180 in-domain ticks, 180 agreed, 0 disagreed) and now **drives** P1's Idle/Walk state proposal and walk speed through `Fighter::PilotLocomotion`, a policy attached only to the pilot fighter while the flag is on — 181 drive ticks measured. The port keeps position integration, collision, animation binding, the turn step and the phase clock, with the reasons recorded in [`PILOT-SEAM.md`](PILOT-SEAM.md) §16 (the port already encodes the recovered turn rule and clock convention; driving them would be a second implementation of identical behaviour). **Flag-off restoration holds in drive mode too**: stdout byte-identical apart from wall-clock timing lines, rendered capture byte-identical, and with the flag off no policy is attached at all. The drive path is mutation-proven load-bearing — forcing the policy to propose idle changes the capture and makes the observer report 136 disagreements. **First combat family (melee) added** the owner's way: offline expectations (the 24-check admission body test and the melee fixtures) and event checks already existed; the runtime comparison (`observe_rena0_melee`) plus `tests/scripts/melee-ground-300.txt` measured **4/4 live admissions agreed** (300, 301, 302, 310) with stdout and the rendered capture byte-identical, and the suite carries it at **9/9**. Two findings: the **default path already drives melee from the recovered admission** (`attack_admission_recovered`, `fighter.cpp:467-475`, `:1604-1612`), so the pilot verifies and names gaps here rather than adding a mechanism; and the admission axes are facing-relative (`held_axis_z`: Up +1, Down -1), which the adapter first had inverted — the helpers are now shared in `src/gameplay/held_axis.h` so the dispatcher and the adapter cannot drift. **Second family (shot) started**: the ground-shot body had no port-side counterpart, so it is now adapted for weapon slots 0/1 in `src/gameplay/native/rena0_ground_shot_observation.h` (with its two steering helpers), and its **ordered event list is pinned offline** by `tests/rena0_shot_body_test.cpp` (36 checks, data-free): activate at frame 0, nothing through frame 11, then model/model/sound 70/statistics/voice 27 (30 on the last round)/attachment at frame 12 with the pitch clamp, weapon 1's frame 7/15/18 events and 8-18 strike window, and the completed/airborne proposals. Weapon 2's scatter needs `legacy_trig`'s cosine table and is **not** adapted: it throws with that reason rather than returning an empty list. The **live comparison is done**: `observe_rena0_shot` owns the body's frame clock and compares the fire tick, sound id and voice id — measured on `tests/scripts/shot-ground-400.txt` at **98 shot ticks, fire 2/2, sound 2/2, voice 2/2, 0 disagreements**, capture byte-identical, and carried in the suite at fire/sound/voice 1/1. A bound row other than 400 is named `shot-row-unadapted` (the held press reaches a charged row and is named, not mis-compared); projectile positions, pitch and model requests are explicitly not compared. Charge levels stay the port's own path, pinned offline by the charge fixture (Red boundary at update 210) with `charge_gauge` declared unsupported. **Third family (guard) adapted offline**: `src/gameplay/native/rena0_guard_observation.h` reproduces the bundle's `battle_guard_motion.hpp` (states 390/391/392) with the steering helpers now shared in `rena0_steering.h`, and `tests/rena0_guard_body_test.cpp` pins its transition logic in **26 data-free checks** (the frame-0 clear, the 10-per-frame gauge drain, the phase-2 release conditions, the 391 contact path, the 20-frame hold release, the −15 recoil entry with its same-frame ramp, and the 103 airborne-guard proposal). A units caveat is kept explicit: the body's 0..1000 gauge is **not** the port's 0..100 stamina (measured 25/s), so the live comparison will compare decisions, not the gauge. **Hit/KO are deliberately not adapted** — the bundle spreads them across a damage/death pipeline, a larger adaptation than one round should start unsteered; their observables are already pinned by the hit and KO fixtures (8 HP at update 15; KO at 16 with 1 HP left) and the unsupported fields are declared in contract §2b. The **live guard comparison is done**: `observe_rena0_guard` compares the two facts both sides have — measured on `guard-hold-live.txt` + `guard-attacker.txt` at **118 guard ticks, 3 starts, 2/2 guarded contacts agreed, 0 disagreements**, capture byte-identical, carried in the suite at 240 guard ticks. **Two findings:** the port binds no clip or phase for `Guard`, so the body's phases/390/391/392/hold counter have no counterpart (`guard-granularity-unrepresented`) — while the attacker-side 392 recoil **is** recovered (`rena_guard_exit_row`); and the victim-side guard damage gate is an explicitly **PROVISIONAL port rule** (guarded damage reduced to 20%, `fighter.cpp:1228-1235`, whose comment says the original's gate is unmapped). The body's gauge is also not the port's stamina (`guard-gauge-units-unresolved`). **Owner decision needed:** whether the hit/guard damage pipeline is adapted (recovering the real gate) or the provisional rule stands for the pilot. **Slice 3 (this pass, corrected 2026-10-22): the empty tap is now a pilot-path decision; the dash "fix" was withdrawn.** The silent empty tap publishes the recovered body's voice id 24 through one method on the existing `PilotShot` interface (`empty_shot_voice`) consulted in `fire_shot`'s empty branch. The dash half of that slice was **wrong**: the owner observed that only the stamina meter gates a dash in the original, and the code agrees — `+0x834` *is* stamina at 1/10 scale (`dashDrain` 1.20 = the recovered 12/tick, same phase exit, and `try_dash` already refuses at `m_stamina <= 0`), so the gauge-0 "difference" was an injected-state artefact. The `PilotCharge::dash_gauge_refuses` consult was removed and the test now pins the drain equivalence and flag-on/flag-off dash agreement instead. Recorded as erratum `PILOT-EVIDENCE-CONTRACT.md` V3-6. Both are entry-time, one consultation each, flag-on only: with no policy attached neither block runs. Pinned by `tests/rena0_pilot_gate_test.cpp` (install-backed, skip-not-pass at 77), whose own `--seed-wrong-gate` run must exit 1 — and the flag-off control is asserted **inside** the same test (gauge 0 still enters row 20/set 13 with stamina 98; the empty tap is still silent), so the control is evidence rather than a claim. Offline half: `local-data/harness/rena0_slot7_gate_probe.cpp` (`sha256 b23bddd9…`) passes on the correct gate, is byte-identical over 3 runs, and fails under the deliberately wrong gate. Scripted port runs (`melee-ground-300`, `locomotion-walk-turn`, `shot-ground-400`, flag-off vs `--native-actions=rena0`, 260 frames) are capture-byte-identical with only the capture path and wall-clock timing lines differing in stdout; the pilot drive reports 200/200, 33/33 and 99/99 with 0 disagreements. Field maps: [`PILOT-SEAM.md`](PILOT-SEAM.md) §25-§27. Named, not implemented: the port's two counters for the one original resource and their differing regen rates (V3-6), and the empty-shot statistic `+0xaf4c`, which has no port owner and was not invented as a `Fighter` field. Remaining after that: 2f | pilot agent | [`rena0_pilot_adapter.h`](../remake/foundation/src/gameplay/native/rena0_pilot_adapter.h); [`rena0_pilot_gate_test.cpp`](../remake/foundation/tests/rena0_pilot_gate_test.cpp); `tests/scripts/locomotion-walk-turn.txt`; [`PILOT-SEAM.md`](PILOT-SEAM.md) §16, §25-§27 |
| P2-8 | **2f — evidence and rollback check; do not delete yet:** run the approved coverage matrix and compare binding, state transitions, motion and gameplay events; attach provenance and unresolved limits; confirm flag-off restores the baseline without a global resolver change. **The old Rena+0 implementation stays until the owner's verdict** | done, then amended 2026-10-22 — **the 2f evidence and rollback check is written up in [`PILOT-SEAM.md`](PILOT-SEAM.md) §21, and repeated after the owner's three gaps were closed in §24.** The repeat runs the approved v2 matrix (23 fixtures, 21 case rows, 39 acceptance fields asserted, 7 unsupported declared, **3 unreferenced extras — explicitly v3-dependent**), the offline bodies (locomotion 53, admission 24, shot 36, guard 26, charge 29, mode gauges 44, guard flags 4, resolver 48), the fixture-linked differential (**357 in-domain ticks**, no unexplained divergence) and the four live comparisons (locomotion 200/200, melee 33/33, shot 99/99, guard 62/62), with the mode gauges at `charge1=220`, the guard predicate `asked=3 guarded=2 no-record=0 not-guard-capable=1` and the shot model comparison at 144/148. Rollback: locomotion, melee and shot byte-identical in capture and deterministic stdout; the guard scenario differs only in the HP fields (90 → 92), now from the data-backed predicate. Provenance tabulated and unresolved limits named. Acceptance stays 0/46: the three new cases and the `charge_gauge` promotion need the **proposed v3** approved, and the verdict stays with the owner. **2f repeated again this round against the v3 candidate** ([`PILOT-SEAM.md`](PILOT-SEAM.md) §28): both manifests run from the current source and are 3×-byte-identical (`fce0e063…` v2 / `4c8063be…` v3, differing only in the summary line), the offline bodies are 8/8, the differential is 357 in-domain ticks, the live comparisons agree 200/33/99 with 0 disagreements, the guard pair reproduces `asked=3 guarded=2` with the intended `90 → 92` HP difference and is 2×-repeatable, and the suite is 83/83 with 0 skips. One honest gap is recorded: the three new v3 rows are guarded by the **manifest**, not yet by the runner's own `kRequiredCases`/`kRequiredFields` constants, because those are the v2 lists and moving them is part of the post-approval diff. **Amended 2026-10-22 (Q19 correction):** the misattributed powered-shot spend was deleted from production, the required case was replaced by two source-backed ones, and the matrix now runs **24 fixtures / 25 case rows / 44 asserted fields / 6 unsupported / 0 extras** with a seven-mutation fail-closed regression. Details in [`PILOT-SEAM.md`](PILOT-SEAM.md) §29 and the contract's V3-1/V3-7 | pilot agent | coverage report + flag-off run |
| P2-9 | **2g — pilot verdict:** present repeatability, correctness, coverage, seam/cost, test sensitivity, reversibility and honesty separately; a missing original trace is recorded as *not verified*, never as zero differences | done — **green, declared by the owner 2026-10-30** for the state at `261078b0` ("aprovo o estado atual do 2g"), with a perfect Rena+0 explicitly not the goal. Earlier history: this file's work log | owner | [`SCOREBOARD.md`](SCOREBOARD.md) |
| P2-10 | **2h — cleanup after green only:** delete the accepted Rena+0 hand-decision path in a separate reviewed change, remove obsolete tests only where replacement coverage exists, and record the pre-cleanup revision that rollback now uses | todo — **only after P2-9 is green** | pilot agent | `git diff`; recorded pre-cleanup revision |

### Phase 3 — scale to 46/46 (`DIRECTION.md` §4 Phase 3)

Acceptance is `N/46` under the versioned contract, with original-runtime parity a
**separate** column, never implied (`DIRECTION.md` §6).

| ID | Task | State | Owner | Artifact |
|---|---|---|---|---|
| P3-0 | Open Phase 3 only on a green P2-9 verdict; add the 45 combo rows here then. Per combo: inspect body availability and dependencies, add offline and scripted-product cases, compare against independent evidence where available, document genuine recovered per-combo behaviour, record acceptance and evidence limits, then delete the replaced hand path | todo | coordinator | `SCOREBOARD.md` |
| P3-Gate | Phase 3 gate: 46/46 accepted under the versioned contract, required coverage complete, no unresolved load-bearing fallback in accepted scope, scripted end-to-end 1v1 and 2v2 checks. Original-runtime parity stays a separate result | todo | coordinator | gate report |

The 16 per-character checklists (#71–#86) that used to carry these criteria are
closed; their shared definition of done is **retired** and replaced by the
Phase 3 gate above. A green build, static data inspection or a pinned-interpolation
capture is still not sufficient on its own — such evidence is admissible under the
approved contract only where the contract names it, with its tier and scope; the
difference is that acceptance now comes from that versioned contract, not from a
live original match with real input.

### Phase 4 — finish the product

Opened only when Phase 3 closes. Effect polish, CPU, camera, then freeze list B,
then `remake/foundation/docs/RELEASE-CHECKLIST.md` §3. Gameplay-relevant
projectile lifecycle, collision and damage must already be handled in the
relevant acceptance cases (`DIRECTION.md` §4 Phase 4); only presentation polish
waits here.

## New documents

Documents created or planned by this effort. Add a row when a task produces one;
a planned document is named by the task that will write it.

| Document | Purpose | Produced by | State |
|---|---|---|---|
| [`DIRECTION.md`](DIRECTION.md) | the plan: focus, phases, gates, risks | coordinator | exists |
| `DIRECTION-STATUS.md` (this file) | task list, work reports, document index | coordinator | exists |
| [`SCOREBOARD.md`](SCOREBOARD.md) | the one metric + the pilot verdict record | harness/pilot agents, owner | exists; aligned with `DIRECTION.md` §6, contract approval and pilot verdict pending |
| [`QUESTIONS.md`](QUESTIONS.md) | blockers and decisions for the owner | any agent | exists |
| [`EXCEPTIONS.md`](EXCEPTIONS.md) | dated, expiring owner overrides of the freeze | owner | exists |
| [`PILOT-EVIDENCE-CONTRACT.md`](PILOT-EVIDENCE-CONTRACT.md) | the minimal pilot contract: fields, units, tolerances, exclusions, coverage matrix, fixture expectations | F1-2, F1-3, F1-5, F1-7, F1-8 | **exists — v3 APPROVED 2026-10-22** (v2 superseded), plus the owner-approved 2026-10-29 correction recorded at the top of the file; acceptance stays 0/46 until the 2g verdict; the runner's matrix is 30/31/49 |
| [`PILOT-SEAM.md`](PILOT-SEAM.md) | the pilot's seam spec and per-field provenance table | P2-1, P2-4 | **exists** — increments through §30 (locomotion, admission, shot, guard, melee, dash, hit/reaction) plus the readiness and rollback checks |
| [`RENA0-SOURCE-MAP.md`](RENA0-SOURCE-MAP.md) | static navigation inventory for Rena+0 in the ignored Ginkiha bundle: named files, weapon-0 selectors, generated bodies, and call routes; not a completeness or parity claim | owner-requested P2-1 source review | exists; static navigation inventory only — not a completeness or parity claim |
| [`RENA0-ADAPTER-MOCKS.md`](RENA0-ADAPTER-MOCKS.md) | non-compiling Rena+0 design sketches grounded in the source map and the current pilot seam | owner-requested P2-1/2b reconnaissance follow-up | exists; review material only, no integration or contract change |
| [`RENA0-SLOT7-AUDIT.md`](RENA0-SLOT7-AUDIT.md) | Rena+0 slot-7 field/service/DAT census plus bounded recovered-body and equipped-port scenarios | owner-requested P2-1/2b evidence follow-up | exists; source/body and tier-4 port evidence separated, no original-runtime parity claim |
| `tools/harness/README.md` | how agents run the harness tooling that exists, the mute policy, and its limits | existing; F1-6 adds the fixture command | exists (pre-dates this list) |

`TRACE-SCHEMA.md` is no longer planned: trace schema v1 belongs to the retired
tracing platform (see "Retired task orders"). If a future approved scope needs a
trace schema, it gets a new task and a new contract version.

Do not create a document before its task exists. When one of these is written,
link it here and from `AGENTS.md`'s routing list if agents will need it.

## F1-5 report (2026-10-16)

Commands, all from the repository root, all silent (no audio backend is created;
CTest forces SDL's dummy driver):

| Command | Result |
|---|---|
| `git status --short`; `git diff`; `git diff --cached` | Baseline reviewed and preserved: 25 modified tracked files, empty index, no revert/clean/commit |
| Before any edit, the four pre-existing focused tests (`fighter_script_test`, `rena_animation_audit_test`, `combat_audio_test`, `combat_audio_match_test`) | 4/4 passed |
| `cmake --build remake/foundation/build/linux --target rena0_locomotion_observation_test -j 4` | Builds clean |
| `ctest --test-dir remake/foundation/build/linux --output-on-failure -R` selecting the eleven tests from the work-log entry | **11/11 passed**, 0 skipped; `rena0_locomotion_observation_test` 0.35 s |
| `./remake/foundation/build/linux/rena0_locomotion_observation_test` | exit 0; `startup=60 cadence=64 dt=0.015625000`; `PASS: 32 updates x 3 reset cases; repeatability/noninterference; stop-word and wrong-speed sensitivity; skips=0` |
| `./remake/foundation/build/linux/rena0_locomotion_observation_test --seed-wrong-speed` | **exit 1** (intended): `FAIL: source Rena+0 walk speed mismatch (seed detected)` — the seeded error is detected, not a passing case |
| Same binary invoked with a cwd that cannot reach an install (`cd /tmp`) | exit 77; CTest has `SKIP_RETURN_CODE 77` registered, so an install-free run is reported Skipped and never as a pass (CTest's own cwd is the build dir, where the walk-up does find this host's install, so this host cannot display the Skipped line itself) |
| Same binary with `GAME_DIR` naming an install that is present but unreadable (empty `daybreak00.dat`) | exit 1 (`required Rena+0 data unreadable`) — the skip cannot hide missing or mismatched combo data |

The exact aggregate command, so it can be re-run as written:

```bash
ctest --test-dir remake/foundation/build/linux --output-on-failure \
  -R '^(rena0_locomotion_observation_test|fighter_script_test|rena_animation_audit_test|rena_dash_admission_test|fixed_step_test|combat_audio_test|combat_audio_match_test|damage_scale_test|animation_data_test|match_economy_test|stage_movement_test)$'
```

Establishes: the production `Match`/`Fighter` path runs Rena+0 with real move,
item and rig data through a normal startup at the declared cadence; grounded
idle/walk/turn/stop transitions, real row 0/10 clip binding, 7.2 units/update,
±19° turns, stop stillness and dummy neutrality are repeatable across resets and
unchanged by the observer; the attributed recovered control can be evaluated
side-by-side without touching the default path; and the comparison detects a
seeded wrong result.

Does not establish: original-runtime parity (no tier-1 trace exists); the
unmapped resource/stop/slow/angle/clock correspondences; behaviour outside
grounded locomotion (attacks, jump/dash, guard, hit/KO, projectiles, collision);
that the larger generated combat bodies fit the port (this is a 57-line narrowing
plus four helpers, not the generated body); contract approval, coverage
acceptance, a pilot budget or a verdict. Legacy numeric agreement is diagnostic
only: the control and the port are not independent confirmations of the recovery.

Remaining when this report was written: `TODO(question 13)` contract approval,
`TODO(question 14)` Option A/B, `TODO(question 15)` pilot budget and
`TODO(question 16)` the next bounded mapping. **Superseded:** Q13–Q15 were
answered on 2026-10-16 (contract approved, Option A chosen, budget settled),
P0-10 moved the cadence to 60 Hz, and Q16's paired-clock seam was subsequently
covered by P2-4/P2-7 — see [`QUESTIONS.md`](QUESTIONS.md). The report's own
measurements stay as the record of that probe.

## F1-1 evidence inventory (2026-10-16)

Produced read-only from the ignored local bundles plus the repo. Everything below
was read from the files named; nothing was extracted, converted, built or launched.

### Present — local bundles (all under ignored `.local-analysis/`)

| Location | Size | What it is |
|---|---|---|
| `daybreak-rebuild/DaybreakRebuild-20261010` | 1,491 files / 43 MB | `source/src` **638 files**; docs `VALIDATION.md`, `ARCHITECTURE.md`, `SOURCE_INVENTORY.md`, `SOURCE_GUIDE.md`, `BUILD.md`, `RUN.md`, `THIRD_PARTY.md`; `validation/` 5 JSON reports |
| `porting-support/DaybreakPortingSupport-20261010` | 3,927 files / 181 MB | `traces/` **2 JSONL × 18,216 rows covering all 46 combos**; `evidence/` 12 files incl. paired `-original-`/`-runtime-` TSVs and per-topic markdown; `tools/` 4 (bundle verifier, attack-preview regeneration, projectile-handler probe); `reference/` 28 files; `catalogs/` 8 files; `assets/` 2,375 decoded original assets (**never committable**); `runtime/` 1 file; `manifest.json` + `SHA256SUMS.txt` |
| `balance-reference/balance-reference-v0.10` | 29 files / 15 MB | balance docs (EN/JA), `reference-data.json`, collector scripts — a numbers reference, not body behaviour |

Provenance facts read from the artifacts: the bundle manifest's
`reference_exe_sha256` is `27e61475…a6a07f02`, **identical to the repository's
pinned binary**; the two traces' hashes are listed in `RESPONSE.en.md:11-14`; the
`runtime-extracted` copy of `roster_locomotion_native_control.hpp` is
byte-identical to the rebuild copy (sha256 `976bf7a1…`), so the duplicate tree is
not a divergent source.

### Present — repo side

Addressed decompilations for the Rena+0 seam all exist under `research/decompiled/`:
`FUN_0043ffc0.c` (2,447 lines), `FUN_00445ee0.c` (464), `FUN_0041f580.c` (300),
`FUN_00421080.c` (20), `FUN_00421100.c` (28), `FUN_00421780.c` (40),
`FUN_0042db10.c` (41), `FUN_00649790.c` (606), `FUN_00634f60.c` (209); the corpus
holds 3,191 entries / 3,109 `FUN_*.c`. Port service surfaces an adapter must bind:
`ShootingContext` (`fighter.h:348`), `MatchEconomy` (`match_economy.h:226`),
`SimulationRng` (`simulation_rng.h:22`), `MovementCollision`
(`physics/raycast.h:181`), `ProjectilePool` (`projectile.h:187`), `TargetLocks`
(`target_lock.h:116`). Ten install-backed tests already bind real combos
(`damage_scale_test`, `synthetic_combo.h`, `rena0_locomotion_observation_test`,
`bot_brain_test`, `melee_rules_test`, `animation_data_test`,
`rena_animation_audit_test`, `combat_shot_voice_test`, `melee_admission_test`,
`fighter_script_test`). `src/gameplay/native/` holds exactly one file (the F1-5
observer), included only by its own test. Historical ignored evidence:
`local-data/harness/` 14 files / 6.5 MB (13 screenshots plus
`battle-attempt1.jsonl`, 692 rows whose `tick` column holds values such as
`0xFF000000`), and the 91-file DX9 `parity-baseline` bank that AGENTS already
labels history rather than a fidelity oracle.

### What the validation artifacts actually claim

`VALIDATION.md:37-47`: 3,968 stage04 updates, four actors, 59 fields per row,
936,448 observations; defined differences 20,403 → **0** after a correction;
**35,777** raw differences; awake air-dash coverage **not reached**; **no
attack-cancel** observed. `validation/battle-comparison-summary.json` agrees
(`frames` 3968, `actor_rows` 15872, `fields` 59, `defined_differences_before`
20403, `..._after` 0, `raw_differences_after` 35777) and itself states
`native_capture_coverage_gate_pass: false` and `whole_game_parity: false`. The two
porting-support traces are **synthetic-fixture handler traces**, not original
runtime traces: `evidence/roster-ground-shot400.md:13` describes 11,454 / 11,316 /
22,632 synthetic samples with a configured RNG returning five, and `:92` states
the callbacks record *requested* projectile creation only — synthetic bone
pointers, no real models, synthetic world coordinates — so bullet counts and
geometry "cannot be trusted from this oracle".

### Missing — named as missing

1. The **59 field names and the defined/raw classification** are not shipped; only
   counts and a partial unresolved-field table exist (`RESPONSE.en.md:49-54` names
   contact `fields[4]`, `fields[11]`, `fields[12]`, actor `parameters[2]`/`0x110`,
   `flags28`, all marked preserve-raw). F1-2 must define our own observable set.
2. The **original capture tooling** that produced the stage04 four-actor capture is
   absent; only post-hoc probes and a bundle verifier ship.
3. **Input banks** as such are absent, and the **initial state / RNG setup** of the
   original capture is not shipped (the RNG=5 configuration belongs to the
   synthetic shot fixture).
4. The **comparison rules** that define a "defined difference" are absent; only
   results are reported.
5. `roster-walk-profiles.json`, referenced by `battle_roster_walk.hpp:5`, is
   **absent** (so that table's provenance stays unverified even though addressed
   code backs Rena+0's 7.2 walk speed).
6. Repo-side documents that were unwritten at F1-1 time: `PILOT-SEAM.md` now
   exists as P2-1 increment 1, and the coverage matrix is contract §10 (F1-8); no
   coherent original per-update trace exists anywhere in the repo.

### Consequence

F1-0's request to the owner can be **narrowed to exactly items 1-4**: the traces,
evidence TSVs, catalogs, verifier and a pin-matching manifest are already on disk.
Items 2-4 are not needed for F1-2's minimal independent contract, which stays the
next unblocked row.

## Work log

> **Append-only; newest last.** A number inside an entry is what was measured when
> that entry was written, not the current metric (see the snapshot above). One line
> minimum per finished task: `date — role — task ID — result — artifact`; longer
> entries are fine when a task fails or a finding changes the plan.
> Rough eras: 2026-10-11 baseline; 2026-10-14/15 plan alignment and evidence
> inventory; 2026-10-16 the contract, fixture and seam push; 2026-10-22/23 the
> V3 re-audit and the live-play fixes; 2026-10-28/29 the owner defect intake
> (side dash, air dash, hyper, cards) and this frame-data audit.

- 2026-10-14 — coordinator — P0-3, P0-4, P0-5 — decided D14 (recovered bodies
  become the runtime), wrote the freeze list into `AGENTS.md`, verified the
  binary pin, and created the four status documents. Verified: 57 relative links
  resolve; `AGENTS.md` carries no absolute local paths.
- 2026-10-14 — coordinator — review fix — retired the stale per-character
  instructions: banners on the four `ginkiha-*` plan/handoff reports and on
  `ROADMAP-PENDING.md`; fixed the two source errata (`ANIMATION-SETS.md:135`,
  `ROADMAP-PENDING.md`); added `.local-analysis/` to `.gitignore` (it was only in
  `.git/info/exclude`). Artifact: `git diff`.
- 2026-10-14 — coordinator — plan gap — added the fighter/animation **file
  disposition table** to `DIRECTION.md` §7 (KEEP / REPLACE / EVIDENCE-ONLY /
  PARK), the `PORT-REPLACED` marker convention, and the rule that new code lives
  in `src/gameplay/native/`. Verified before writing it: `ginkiha_tables.h` is
  included only by its test, and `rena_dash_admission.h` by no product file.
  Tasks P0-6, P0-7 and P2a-2 added above.
- 2026-10-14 — coordinator — plan gap — made the rewrite stance explicit after
  review: REPLACE code is deleted outright at its gate, with no shims and no
  permission request; keeping an old path past its gate is the failure mode.
  `AGENTS.md` now separates "frozen" (do not extend) from "preserved" (never the
  intent), and its git rule states that deleting a REPLACE file is an ordinary
  edited-and-reviewed change, not the branch/worktree deletion that needs
  sign-off.
- 2026-10-14 — coordinator — plan review — found and fixed three gaps before
  execution: the harness's **tick domain** (per-tick diffs are only meaningful at
  60 Hz; live is 64 Hz per D9), the **RNG contract** (record/inject the seed or
  exclude RNG outputs from the defined set), and the missing definition of
  **"defined difference"** (field set + scenarios + tolerances, owner-approved).
  Also corrected two of my own claims: the port's match stream *is* documented as
  the original's MT19937 (`match.h:293`) — what is unverified is seeding and
  alignment — and the AGENTS "read-only instrumentation" line contradicted the
  input injection the harness needs, so it now distinguishes code (never written)
  from game data (written, recorded, announced). Added Q4–Q6 and tasks P0-8,
  P0-9, P1-10, P1-11; P2c-1 is now blocked on Q1.
- 2026-10-14 — owner — Q1 — **licence resolved**: full permission from the bundle
  author for anything; the project's own licence is open. Bundle code may be
  vendored with attribution; decoded original game assets stay untracked. `P2c-1`
  unblocked.
- 2026-10-14 — owner — Q2, Q4, Q5, Q6, Q7 — answered the plan's open questions:
  audio muting is courtesy only; **live cadence becomes 60 Hz (D15)**; the
  comparison contract adopts the reference's 59-field posture with the names to be
  reconstructed (Q8); the character/combat issues are closed; the Windows-rematch
  line is verified before it is edited. Tasks P0-10, P0-11 added; P1-10/P1-11
  rewritten.
- 2026-10-14 — coordinator — P0-8 — closed 27 character/combat issues (#71–#86,
  #26, #31, #52–#54, #65–#70) with a pointer comment. Left open: #58–#60, #61,
  #63, #38, #3, and **#62 (stage01 ground alignment)** as the one borderline case.
- 2026-10-14 — coordinator — P1-4 — **proved the host-side reader** for the
  original with no privileges: the PE is mapped at its image base, VA `0x400000`
  reads back byte-identical to the on-disk exe, and `process_vm_readv` succeeds
  once the reader sets `PR_SET_CHILD_SUBREAPER` and spawns Wine itself (Wine's
  loader forks and exits, so without the subreaper the game reparents to systemd
  and every attach is denied). `DAT_006cfae0` read as four zeroes at the title
  screen. Also established that `winedbg` scripts non-interactively and can write
  memory (a documented injection route) but stops the process, and that `pika`
  built from source here and needs either `cap_sys_ptrace` or a spawn mode to be
  the ancestor. Remaining unknowns: actor state in a battle, input injection,
  tick pacing.
- 2026-10-14 — coordinator — P1-13 (in progress) — built `tools/harness/`
  (`orig_capture.py`, `find_gamestate.py`, `find_scene.py`, `find_scene_diff.py`,
  `probe_input.py`, README). Proved: the game window is `WM_CLASS=daybreakdx.exe`;
  keys do reach DirectInput (a held `Z` pulsed `DAT_006cae94` slot 0 field `[2]`);
  the original runs at **~1 fps** under Wine here, so un-held `xdotool` taps are
  lost between frames and menu driving must be **state-driven**; and `pika` with
  `cap_sys_ptrace` reads the detached game directly. A timing-driven attempt
  reproduced the owner's predicted failure — the movie ended on its own and the
  skip key selected ストーリー. The current-scene variable (stack local of
  `FUN_0064d250`, switch at `+0x2e18`) is still being located, now with pika value
  scans across human-driven screen transitions.
- 2026-10-14 — coordinator — P1-13 **done** — reached a live battle in the original
  with the owner's documented flow (every press held ~2 s, each step verified by
  screenshot) and read four live actors from `DAT_006cfae0`
  (`0x086be378`, `0x11632fa8`, `0x133c33b8`, `0x15ea3668`), with `+0xae04` ticking
  (`192 -> 505` over 5.00 s = **62.5 Hz**) and `+0xadf4` phase advancing. This is
  the tier-1 field read inside a battle. It also **corrects** an earlier claim of
  ~1 fps in `tools/harness/README.md`: that came from misreading a latched input
  field as a frame period; the game runs at ~60 Hz, which independently supports
  D15. The current-scene variable remains unfound and the `0x1afcc78` candidate was
  falsified; screenshot verification plus the actor array are the working state
  signals. `pika` (with `cap_sys_ptrace`) reads the detached game, so the harness
  no longer needs to own the process to observe it.
- 2026-10-14 — coordinator — harness — made the launch step deterministic:
  `tools/harness/open_skip.py` launches the original, waits for the process, waits
  2 s and presses **Z once**, which lands on the main menu (screenshot
  `local-data/harness/shots/open-skip.png`). Two earlier attempts overshot into
  story mode — repeated Z presses after the movie was gone, and a motion-gated
  Z loop whose gate never closed (the title measured 13-40 frame-to-frame, same
  range as the movie). `drive_match.py` now uses the single-press recipe as its
  first stage. Next: run the full driver unattended through the menu flow to a
  match, then capture a trace with defined inputs.
- 2026-10-14 — coordinator — harness — `drive_match.py` ran end to end **unattended
  on a fresh process** (pid 455790) and reached a live match: one Z at 2 s skipped
  the movie, DOWN/Z entered versus, five confirms took red team / Rena / weapon 0 /
  hypermode / 1P, UP/Z then UP/Z started the match. Verified by screenshot
  (`local-data/harness/shots/drive-4-match.png`: 開始!, Rena, COM opponent, HUD) and
  by memory (actors `0x8695420`, `0x110f8378`, `0x11f18870`, `0x153284b0` with
  advancing ticks). Actor addresses differ from the earlier manual run
  (`0x86be378`, `0x11632fa8`, `0x133c33b8`, `0x15ea3668`), which is the expected
  cross-run heap variance and confirms the driver does not depend on them.
  Note: the per-slot tick wraps when an animation changes, so "ticks advanced" is a
  liveness check only — a stricter gate would use the match timer.
- 2026-10-14 — coordinator — **plan alignment (offline-first revision)** —
  rewrote the task rows in this file against the revised `DIRECTION.md` and
  `AGENTS.md`, at the owner's request, without touching the work log above.
  Removed as orders: trace schema v1 with per-actor-per-tick rows, the
  original-side producer ladder (L1 tracer DLL / L2 reader chosen per trace), the
  deterministic-input and input-injection tasks, the reconstruction of the
  reference's 59 compared field names, and the pre-verdict deletion of the Rena+0
  hand path. Added, under new `F1-*` IDs so no retired ID changes meaning: the
  Phase 1 evidence-inventory request and minimal independent contract, the
  deterministic fixture rows, the **minimal standalone Rena+0 fixture**
  feasibility probe (F1-5), the coverage matrix, the fixture command row, explicit
  owner gates for the pilot budget (P2-0a) and the contract/coverage approval
  (P2-0b), the 2f rollback check that keeps the old path (P2-8), and cleanup only
  after green (P2-10). P1-1…P1-15 are retired or kept only as history.
  Retired the old Phase 3 "definition of done" (live match with real input) in
  favour of the §4 Phase 3 gate with original-runtime parity as a separate
  column. State discipline: the alignment marks no technical row `done`; P0-7a
  records this file's part of the alignment as **partial**, with the parent
  finishing the companion documents, and P0-7b stays open. Alignment is not
  approval of the contract, budget or verdict, and no technical work is claimed to
  have been executed. Companion fixes landed in the same pass by the coordinator:
  `.gitignore` now carries `local-data/harness/`, which was **not** actually
  ignored before (verified with `git check-ignore`; the obsoleted
  non-redistributable-code comment was corrected at the same time), and `AGENTS.md`
  now permits compiling explicitly selected recovered code for offline feasibility
  while keeping the local bundles immutable and forbidding the whole external
  application as an implicit dependency. Artifact: `git diff` of
  `DIRECTION-STATUS.md` (this file is untracked, so the diff is against the
  working tree, not `HEAD`). Reader/tracer and menu-driver results are kept as
  historical capability evidence in the "Optional live observation" rows;
  `DIRECTION.md` §2.2 still governs how those sampled reads may be described.
- Plan-alignment completion — coordinator — P0-7a/P0-7b — reviewed the two
  subagent contributions and completed the companion alignment in `AGENTS.md`,
  `DIRECTION.md`, this task list, `SCOREBOARD.md` and `QUESTIONS.md`. Acceptance
  is contract/coverage-based; original-runtime parity is separate and not
  verified. Required owner decisions remain Q13 (contract), Q14 (route after
  seam audit) and Q15 (integration budget); Q12 is a non-blocking author-material
  request. The legacy path stays through the verdict, and cleanup is separate.
  New offline work uses F1 IDs; prior capture work remains history. Final checks:
  relative Markdown links resolve, scoped whitespace checks pass, and
  `git check-ignore` confirms raw harness evidence exclusion. No fixture,
  integration, cadence change, game run, contract approval or verdict was
  performed by this documentation pass. Artifacts are the current documents
  (the four direction/status documents are untracked, so ordinary `git diff`
  does not display their contents).
- Feasibility-step revision — coordinator — F1-5 — at the owner's request,
  replaced the separate-runner-first proposal with an observation-only grounded
  Rena+0 experiment using the production gameplay library, followed by optional
  regular-port debug inspection. Baseline/WIP review precedes coding. Real combo
  data, normal startup, explicit cadence and collision scope are required;
  phase/clock ownership remains legacy. Internal source research informed this
  choice; nothing was built, launched or implemented. Artifacts: `DIRECTION.md`
  §4 Phase 1 and the F1-5 task row; task remains `todo`.
- 2026-10-16 — pilot agent — P0-1 + F1-5 — reviewed the actual uncommitted
  baseline and preserved it unchanged: **25** modified tracked files (the
  historical "16-file" count is stale), an **empty index**, plus untracked
  direction/status documents and `tools/harness/`. No commit, revert, reset or
  clean was performed, and no existing WIP file was overwritten; the two
  overlapping areas (issue #71 hypermode/EX work in `fighter.cpp/h`, `match.*`,
  `main.cpp`, HUD/audio and four tests) were left alone and the new code keeps
  disjoint ownership. Four pre-existing focused tests passed before any edit
  (`rena_animation_audit_test`, `fighter_script_test`, `combat_audio_test`,
  `combat_audio_match_test`).
  Implemented the F1-5 experiment read-only against the real runtime:
  `remake/foundation/tests/rena0_locomotion_observation_test.cpp` links
  production `foundation_gameplay`, loads real Rena+0 (`data/rena/00.dat`, item
  001, rig `00.x`, 124 sets) for both fighters, resets `Match` per case, steps the
  normal 60-update BattleStart → grounded actionable Idle, and drives an explicit
  32-update idle → Right walk → Up turn → release/stop sequence with
  `compute_edges`. The dummy is equipped and fed no input (COM-off shape), and its
  position, yaw and state are pinned from the reset. Cadence is read from
  `FixedStep` and recorded: **64 Hz** (0.015625 s) — P0-10's 60 Hz change is still
  pending and this probe does not implement or claim original cadence. Scope is
  explicitly open-field (no stage collision provider), and the historical
  standalone/`--out` collision defaults are untouched.
  The attributed adaptation is `remake/foundation/src/gameplay/native/
  rena0_locomotion_observation.h`, a Rena+0-only narrowing of the bundle's
  slot-6 State0/State10 locomotion control with required-argument structs (a
  missing field cannot compile), no 46-row table and no `Fighter` include. It is
  observation-only: the test feeds mapped inputs and records proposals; nothing
  is applied to `Fighter`, `Match` or the legacy animation controller, and the
  legacy path still owns phase, clocks and binding.
  Verified: 0→10 on held direction, 10→0 on release, real move-row 0/10 clip
  binding with no fallback, exactly 7.2 units/update production walk (the
  addressed `0x40e66666` constant, cadence-independent), ±19° production turn on
  entry and reversal, exact 0 movement in idle/stop, observer tail/clock-reset/
  refill/steering/turn-decay expectations, and byte-identical production
  snapshots across a repeat run and an observation-disabled run. Because the
  in-match resource channel is saturated at 1000, the refill arithmetic is pinned
  by explicit cases (100/clear → 140, 100/slow → 105, 995/clear → 1000), and the
  strict phase-completion branch plus its gated counter-case and the losing-ground
  → airborne + gravity 0.5 proposal are explicit cases as well; an independent
  reviewer found that the earlier saturated-gauge assertion alone could not fail
  and that no production tick crossed a phase boundary. A no-install checkout now
  exits 77 with `SKIP_RETURN_CODE 77` registered to keep the repository's
  data-free CI invariant (an install-free run is reported Skipped and never as an
  F1-5 pass — `SKIP_RETURN_CODE 77` is registered in `CTestTestfile.cmake`; this
  host cannot display the Skipped line because CTest's own cwd is the build dir,
  where the walk-up does find the install, so the exit-77 path itself was verified
  by direct invocation from `/tmp`). An install that is present but unreadable
  still fails hard (verified: exit 1 with an empty `daybreak00.dat`), so missing
  or mismatched combo data cannot hide behind the skip. The seeded `--seed-wrong-speed` run exits 1 through the same source
  expectation, and the deliberate run is documented rather than registered as a
  `WILL_FAIL` ctest case (which would also pass on a crash or on the data-missing
  failure).
  Mapping discrepancies recorded, not papered over: the Idle→Walk proposal
  zeroes speed and resets its clocks while legacy already moves 7.2 units and
  reports elapsed 1; Walk→Idle resets clocks while legacy stops and reports 1;
  the diagnostic `move_counter` proxy stays 0 against proposed `+AE08` increments.
  `stop`, `slow`, the resource gauge, the observer angles and the paired
  clocks/secondary remain explicit fixture assumptions or unmapped
  (`TODO(question 16)`). Cadence status was 64 Hz when this report was written;
  P0-10 moved it to 60 Hz and F1-9 asserts it.
  Evidence tier: 4 (install-backed automated test) plus tier-2 addressed research
  cross-checks (`FUN_0043ffc0:28-30`, `:84-179`, `:2439-2443`); the shared-source
  bundle differential run by the subagent (1,660,176 cases, bit-exact) is a
  consistency check, not independent original validation. No tier-1 parity, no
  contract approval, no pilot verdict and no authoritative native integration.
  Artifacts: the test, the native header, `docs/PILOT-EVIDENCE-CONTRACT.md`
  (draft scope), the CMake target and this entry; sha256 — header
  `20434618eff87f3d7fe687ae52c3e83e9e68d08837d09a34b57995d73c92c399`, test
  `e429d43304c5ce19cc1ff3c1003ddec739402dc7ba80b00be9e7ad5bd047b486`, CMake
  `a898a3d9500c3ca3727497df5696ea220f340e3dde6334ce2473bbb1731928d7`, contract
  `237e7c77f25e8ad3e629cadeeefe8ed3fbcc5805685281e35babe59aca0f2fd2`.
- 2026-10-16 — coordinator — **P0-10 + F1-9** — applied owner decision **D15**: the live
  port cadence is now **60 Hz** (`FixedStep::tickRate`; `fixed_step.h`). Added the
  scripted/`--out` capture domain as derived constants (`scriptedCaptureRate = 60`,
  `scriptedCaptureSeconds = 1/60`, D9 keeps captures on their own explicit recipe) and
  routed the three capture sites through them, so the two domains cannot drift apart
  silently. Converted **131** test step literals across 20 test files to
  `FixedStep::seconds` and updated rate-derived expectations (effect lifetimes
  16 → 15 ticks at 60 Hz; `yellow_hold_sec`/`red_hold_sec` mirrors; an airborne
  comment recomputed to 720 − 1800·16/60 = 240 < 360); F1-9 is now two
  `static_assert`s in `fixed_step_test.cpp` (`tickRate == 60`,
  `scriptedCaptureSeconds == seconds`) and the live diagnostic prints the cadence
  from `FixedStep::tickRate` rather than a second literal. Normative 64 Hz
  statements were updated in eight docs; dated records, quoted run logs and
  measured tables were deliberately preserved as history (D15 owns the change), and
  the standing ANIMATION-DATA-AUDIT §11.2 finding was marked resolved by D15 with
  its measurement kept.
  Verification and fallout, all measured on this revision: full host suite went
  72/72 → **70/72** with exactly two cadence-calibrated fixtures failing, both fixed
  honestly and re-run: `fighter_script_test`'s guard-drain windows were 64/256/128
  **ticks** used as seconds (now `FixedStep::tickRate`/4×/2×, expectations 75 and 0
  unchanged and now exact); `live_camera_smoothness_test`'s 60 Hz/60 Hz case consumes
  exactly one tick per frame so its alpha span is 0 by construction — the D9
  interpolation gate is retained verbatim in the 144 Hz case (span 0.917) and the
  60 Hz case now pins the boundary-exact shape instead of a false fraction. Final
  suite: **72/72 passed, 0 failed**; F1-5 still exits 0 at the new cadence
  (`startup=60 cadence=60 dt=0.016666667`, walk step still exactly 7.20000 —
  the observer is cadence-independent) and `--seed-wrong-speed` still exits 1.
  Two review findings were caught and handled rather than shipped: the docs worker
  found my own `main.cpp` VS-sting conversion using `scriptedCaptureSeconds` where a
  **rate** is required (would have held the VS logo 1 tick instead of 282 on the
  capture path) — fixed to `scriptedCaptureRate`; and the tests worker found ten
  hardcoded ×64 per-tick→u/s conversions in `fighter.cpp` that `fighter.h:240-249`
  contradicts (documented convention is 60×), which the suite cannot see. Changing
  them alters every combo's vertical attack motion, so they are **not** changed
  inside this cadence work: recorded as [`QUESTIONS.md`](QUESTIONS.md) Q17 with
  addressed-code evidence as the prerequisite, `TODO(question 17)`.
  No commit; the pre-existing 25-file WIP is preserved (only `fixed_step.h`,
  `main.cpp`, `screen_opening.cpp`, eight docs and the test files carry this task's
  edits). Preservation note repeated for the record: 64 Hz statements inside dated
  sections and quoted verification output were kept as evidence, so a future reader
  seeing "64 Hz" there is looking at history, not at a stale claim about today.
- 2026-10-16 — coordinator — **P0-2** — inspected the stale branches and worktrees
  read-only and showed the owner; **nothing removed** (removal is optional
  housekeeping and the owner's decision). Measured facts, all from `main` at
  `96482b92`: `refactor/refactor-gameplay` tip `b14f052c` (2026-10-07, 214 behind),
  `refactor/refactor-render` `0f71ba46` (2026-10-07, 199 behind),
  `refactor/refactor-ui` `64a56428` (2026-10-07, 223 behind), `fix/live-input`
  `db6a0831` (2026-10-07, 198 behind) — each **0 commits ahead** and fully merged;
  `ginkiha-help` `c080598c` (2026-10-13, 7 behind, 0 ahead, also on
  `origin/ginkiha-help`). The five worktrees under `/home/marcelo/Projetos/dbd-worktrees/`
  (`fix-input`, `gate-baseline`, `refactor-gameplay`, `refactor-render`,
  `refactor-ui`) are each **clean — 0 modified, 0 untracked**; `gate-baseline` is a
  detached checkout at `db6a0831`, the same commit as `fix/live-input`. There are no
  stashes. `git merge-base --is-ancestor` confirms all four tips are reachable from
  `main`, so deleting the branches would lose **no commit**; the only thing removal
  deletes is ~**1.4 GB** of clean working directories. Consequence recorded for the
  decision: `AGENTS.md` currently cites these very worktrees as the live evidence for
  why long-lived parallel refactor branches are rejected, so removing them means
  updating that sentence to the recorded listing rather than leaving a stale claim.
  Local `main` is 4 commits ahead of `origin/main` (the Rena #71 work) and 1 behind
  it (an origin README rewrite) — pre-existing, unrelated to P0-2, and left alone.
  No branch, worktree, ref or file was deleted, reset, cleaned or checked out.
- 2026-10-16 — coordinator — **P0-2 removal (owner-approved)** — carried out the removal
  the owner selected after reading the listing, and recorded it here because the
  previous entry correctly said nothing had been removed at that time. Removed all
  five worktrees (`fix-input`, `gate-baseline`, `refactor-gameplay`,
  `refactor-render`, `refactor-ui`) and deleted the four fully-merged local branches
  (`refactor/refactor-gameplay` `b14f052c`, `refactor/refactor-render` `0f71ba46`,
  `refactor/refactor-ui` `64a56428`, `fix/live-input` `db6a0831`) with `git branch -d`,
  never `-D`. Safety before deleting, all verified: every target path existed and its
  `realpath` matched, each worktree was clean (0 modified, 0 untracked), every branch
  tip was an ancestor of `main` with 0 commits ahead, and the four
  `Higurashi-Daybreak/` entries inside the worktrees were **symlinks** into the main
  install — each link was unlinked before removal so no tree walk could reach the
  install. Verified after: the main install is intact (`daybreak00.dat` present),
  `main` is unchanged at `96482b92`, `git worktree list` shows only the main checkout,
  the only remaining branches are `main` and `ginkiha-help`, and all four deleted tips
  are still reachable from `main`, so **no commit or history was lost**. The empty
  `/home/marcelo/Projetos/dbd-worktrees/` directory is left in place (0 bytes).
  `AGENTS.md` now records the removal and points at this listing instead of claiming
  the worktrees are still on disk. No source, test, doc or config file was touched by
  the removal; the 66-entry working tree is exactly as it was before it.

- 2026-10-16 — coordinator — **P0-9 check + P0-4 re-verification** — closed the two
  remaining Phase 0 housekeeping questions without building anything. P0-4: the
  original binary pin was re-read from `Higurashi-Daybreak/DaybreakDX.exe` and is
  **byte-identical to the required SHA-256**
  `27e61475fbb3ea67f5058e3e0e6e93ad71d16a4d83fa42b02e605913a6a07f02`. P0-9: the
  proposed `build/linux-harness` / `build/linux-pilot` split has no user — the
  harness tooling is Python (`tools/harness/`, 8 files) and shares no CMake build,
  only one C++ build tree is in active use, and nine build directories already exist
  — so the row is dropped with that reason rather than adding unused dirs; its
  "confirm" half is done (`tools/harness/` exists, untracked and not ignored;
  `local-data/harness/` exists with 14 files and is ignored by `.gitignore:29`).
  Also fixed the one whitespace defect the repository's own pre-commit check reports
  inside the preserved WIP: the trailing blank line at the end of
  `remake/docs/decisions.md` (D15's addition), so `git diff --check` is clean for
  that file. Nothing else in the WIP was touched.

- 2026-10-16 — coordinator — **P0-1 commit plan (nothing committed)** — mapped the
  working tree into reviewable parts at the owner's P0-1 requirement, without
  staging or committing anything. Inventory: 56 modified tracked files, 10 untracked
  entries, empty index, no stashes. **The plan is hunk-level, not file-level**, because
  the pre-existing issue #71 WIP and this session's work overlap inside the same files
  (`main.cpp`, `fighter_script_test.cpp`, `rena_animation_audit_test.cpp`,
  `combat_audio_match_test.cpp`; `main.cpp` alone carries #71, the cadence change and
  the capture-constant rewiring):
  **Part A — plan alignment, enforcement and plan documents:** `AGENTS.md` (alignment
  rewrite + the P0-2 removal record), `.gitignore`, the four
  `docs/reports/ginkiha-*.md` banners, `remake/docs/decisions.md` (D14/D15),
  `remake/foundation/docs/ROADMAP-PENDING.md`, `remake/foundation/docs/ANIMATION-SETS.md`
  (Q3 errata), plus the untracked `docs/DIRECTION.md`, `DIRECTION-STATUS.md`,
  `SCOREBOARD.md`, `QUESTIONS.md`, `EXCEPTIONS.md`.
  **Part B — issue #71 hypermode per-mode presentation:** `src/audio/combat_audio.*`,
  `src/game/hud_{bridge,values}.h`, `src/gameplay/{fighter.cpp,fighter.h,hud_fill.h,match.cpp,match.h}`,
  `src/ui/hud.*`, the #71 hunks of `src/main.cpp`, and #71 hunks of
  `tests/{combat_audio_test,combat_audio_match_test,fighter_script_test,rena_animation_audit_test}.cpp`.
  **Part C — P0-10 60 Hz cadence + F1-9:** `src/gameplay/fixed_step.h`, the cadence
  hunks of `src/main.cpp` (including the `vsTicks`/`ttl` rate-vs-step fix),
  `src/ui/screen_opening.cpp`, cadence comments in `src/{audio/combat_audio.*,game/effect_catalog.h,game/fx_cards.h,gameplay/{bot_brain.h,match.h,match_economy.h},input/synthetic_pad.h}`,
  the 19 converted test files, and the cadence statements in `remake/foundation/README.md`
  and eight foundation docs.
  **Part D — F1-5 observation experiment:** untracked
  `src/gameplay/native/rena0_locomotion_observation.h` and
  `tests/rena0_locomotion_observation_test.cpp`, `remake/foundation/CMakeLists.txt`,
  untracked `docs/PILOT-EVIDENCE-CONTRACT.md`.
  **Part E — owner decision only, do not commit on an agent's initiative:**
  `tools/harness/` (8 files of historical live-observation tooling, untracked and not
  ignored) and `.vscode/` (editor config, unrelated to the project — better ignored
  than committed). Recommended order A → B → C → D so each part is reviewable and the
  suite stays green; the mandatory full diff review applies to each. Two known items
  the #71 review should settle inside Part B: the stale `match.cpp:34` comment
  ("Before init()/reset(), which size the magazines from it" — `set_weapon` runs
  after them) and the `fighter.cpp` ×64 conversions recorded as Q17. No staging,
  commit, push or branch was performed, and the working tree is byte-identical to
  before this entry apart from the `decisions.md` blank line.

- 2026-10-16 — harness agent — **F1-1 done** — inventoried the available evidence
  read-only and recorded it in the F1-1 report section above; nothing was
  extracted, converted, built or launched, and no file in `.local-analysis/` was
  modified. Highlights: the porting-support bundle is substantially the material
  F1-0 was going to request (two hash-listed JSONL traces of 18,216 rows each
  covering **all 46 combos**, original-vs-runtime evidence TSVs, 8 catalogs, 28
  reference files, a bundle verifier, and a manifest whose `reference_exe_sha256`
  **equals the repository's pinned binary**), so F1-0 is narrowed to four genuinely
  missing items plus the absent `roster-walk-profiles.json`. The validation claim is
  recorded with its own limits rather than repeated as parity: 3,968 stage04
  updates / 59 fields / zero *defined* differences but 35,777 raw differences and
  `native_capture_coverage_gate_pass: false`; the two traces are **synthetic-fixture
  handler traces** (RNG fixed at five; synthetic bone pointers and world
  coordinates), so they support handler-argument expectations, not runtime parity.
  Repo side: nine addressed `FUN_*` decompilations for the seam, six port service
  surfaces an adapter must bind, ten install-backed tests already binding real
  combos, and no coherent original per-update trace anywhere. A parallel survey
  subagent was stopped once this in-session survey had covered its scope; its
  partial findings were not used, so nothing here rests on an unverified claim.

- 2026-10-16 — pilot agent — **F1-2 done (draft v0)** — wrote the minimal independent
  contract into `docs/PILOT-EVIDENCE-CONTRACT.md` as §1-§7 ahead of the preserved F1-5
  appendix: sampling domain (production `Match`/`Fighter`, one row per fighter per
  60 Hz tick, per-case reset, explicit inputs and collision scope), a **35-row field
  table** with unit, documented domain, provenance split `[R?]`/`[P]` with `file:line`,
  and role (acceptance vs diagnostic) plus tolerance, a determinism/RNG policy built
  on `simulation_rng.h` (MT19937 from `FUN_0065d150`/`FUN_0065d0c0`, seed 5489 =
  `0x1571`, reset per case, stream position explicitly not claimed), source-backed
  expected transitions for all eleven target cases, and explicit exclusions. It is our
  schema for observability and pilot relevance, **not** a reconstruction of the
  author's 59 fields, and it deliberately records eight observables the port does not
  expose (per-shot identity and lifecycle, attacker-side contact records, applied
  hitstun, per-channel animation clocks and blend state, landing/takeoff/apex events,
  a per-fighter tick index, per-shot spawn source, per-slot hit-status power) as named
  gaps rather than inventing accessors. A read-only subagent compiled the supporting
  inventory (81 observables across the case families plus the gap list); its verified
  `file:line` citations are the ones in the table. No source, test or build file was
  touched; nothing was built, run or committed.

- 2026-10-16 — pilot agent — **F1-3 done (first fixture set)** — added the F1-3
  deliverable: a documented fixture schema (contract §8), three data fixtures under
  `remake/foundation/tests/fixtures/rena0/`, and a device-free runner
  `tests/rena0_fixture_test.cpp` that drives the production `Match`/`Fighter` over the
  real combo. Fixtures reuse the repo's `--script` token vocabulary through
  `input::parse_script_line` (`src/input/input.h:133-146`) instead of inventing one;
  directives cover combo, seed, per-slot spawn, collision scope, per-tick inputs and
  per-tick expectations over the F1-2 field names (`state`, `anim_row`, `phase`,
  `elapsed`, `dash_row`, `airborne`, `hp`, `stamina`, `x`, `z`, `step`, `turn_deg`,
  `dummy_static`). Expectations are source-cited in each fixture header:
  `FUN_0043ffc0:84-179/:167/:121-166` for the locomotion fixture and
  `FUN_00445ee0:86-95` for the dash rows, with the tick anchors labelled as this
  build's recorded F1-5 probe trace rather than runtime evidence. Verified: all three
  fixtures pass (`RENA0_FIXTURES: PASS (3 fixtures, 60 Hz, skips=0)`), ctest registers
  them (`1/1 Passed`), no install exits 77 (Skipped, never a pass), a wrong expected
  step fails with `tick 4 step exp 8.200000 got 7.200000`, and an unknown `expect`
  field fails with `unknown field 'anim_row_typo'` — both mutations in `/tmp` copies,
  the tracked fixtures untouched. Two limits recorded rather than hidden: `Match`
  exposes no RNG seeding, so a non-default fixture seed fails loudly (gap tied to
  P2-2), and only three of the eleven pilot case families have fixtures yet; F1-8 owns
  the uncovered list.

- 2026-10-16 — harness agent — **F1-6 done** — the fixture path and the F1-5 probe now
  run from documented commands with no manual steps and no device:
  `cmake --build … --target rena0_fixture_test rena0_locomotion_observation_test` then
  `ctest … -R '^rena0_(fixture|locomotion_observation)'`, with exit codes defined
  (0 pass, 1 fixture/expectation failure, 77 no install → Skipped, never a pass). The
  command is recorded in the contract §8 instead of `tools/harness/README.md` because
  that file is untracked historical tooling whose commit is an owner decision (Part E
  of the P0-1 plan). Verified by running both the direct binary and the ctest selector.

- 2026-10-16 — pilot agent — **F1-4, F1-8, F1-7 done** — closed the remaining unblocked
  Phase 1 rows. F1-4: recorded a sensitivity/repeatability campaign (contract §9) — the
  tracked fixture set runs three times with **byte-identical** output and exit 0; a
  wrong **input** (`RIGHT`→`LEFT`) is caught as `turn_deg exp 19 got -19`; a wrong
  **output** (`step 8.2`) as `step exp 8.2 got 7.2`; an unknown field as `unknown field
  'anim_row_typo'`; missing `seed`/`collision`/`combo`/expectations each fail by name;
  an empty fixture directory fails as `no .fixture files`; and one bad fixture beside a
  good one reports `FAIL (1 of 2)`, so a failure cannot hide. The only skip is
  no-install (exit 77, Skipped, never a pass). F1-8: the coverage matrix (contract §10)
  gives every one of the eleven target cases a status, its evidence, a tier and its
  named gap — **2 covered (idle, walk), 9 partial**, none silently accepted, and
  original-runtime parity not verified for any case. F1-7: the contract is frozen as
  **candidate v1 for owner review, explicitly not approved**; F1-2's content, the F1-3
  fixture schema, the F1-4 report and the F1-8 matrix are its sections, and post-approval
  changes to acceptance fields need a version bump. All mutations were made in `/tmp`
  copies; no tracked fixture, source or test file was altered by the campaign, nothing
  was launched, and nothing was committed.

- 2026-10-16 — pilot agent — **P2-3, P2-2 done; P2-1 increment 1** — three Phase 2
  analysis rows advanced without touching product code or crossing a gate. P2-3:
  verified `ginkiha_tables.h` is included **only** by its own test (EVIDENCE-ONLY
  confirmed) and `rena_dash_admission.h` only by its own test with no product include
  (REPLACE confirmed); deletion still needs the owner at each gate. P2-2: the recovered
  locomotion seam consumes **no RNG** (no random draw in
  `roster_locomotion_native_control.hpp`, `battle_roster_walk.hpp`,
  `battle_walk_motion.hpp`, `battle_steering.hpp`), the port already carries the
  recovered MT19937 (`SimulationRng`; `FUN_0065d150`/`FUN_0065d0c0`) and feeds it to
  fighters through `ShootingContext` (`match.cpp:44,203`), and locomotion needs no new
  `character_moves` field because its phase duration and gate are already parsed;
  `Match` exposing no seeding remains a named gap. P2-1 increment 1: wrote
  `docs/PILOT-SEAM.md`, quantifying the F1-5-selected body's seam as **17 fields**
  (4 product-owned, 6 partial, 7 unmapped), **4 services** (3 left with the legacy
  path, 1 reproduced as arithmetic), the proposed effects, an explicit no-silent-zero
  policy for the unmapped seven, and a measured glue estimate (~150 code lines).
  The `DIRECTION.md` §4 2a Option A/B trigger is explicitly **not yet answerable**:
  the pilot's attack/shot/guard/hit/KO bodies are uncounted, and that is where the
  reference's RNG/targeting/hit/projectile services would appear. P2-1 therefore stays
  `doing` for increment 2 rather than being closed on a partial count. No source, test
  or data file was changed by this round; nothing was built, launched or committed.

- 2026-10-16 — pilot agent — **P2-4 increment 1** — recorded the actor context for the
  fields quantified in P2-1 increment 1, as `PILOT-SEAM.md` §7-§9: the confirmed update
  order (`Match::step` economy → locks → per-fighter aim/context → `Fighter::update`'s
  state-timer, state machine, movement, stamina, vertical order, with line refs), the
  previous-input edge contract (`compute_edges`, the 2-tick press timer, per-fighter
  `PlayerState`, sign-only stick words, fixtures/scripts deriving edges identically),
  and a per-field disposition table — **7 existing, 3 needing an accessor, 1 justified
  new field, 6 unresolved** — each with its justification and **no silent zeroes**. The
  unresolved six (`+0xae08` paired clock, `+0xa0` stop, `+0x7f4` slow, `+0x60`
  movement, `+0x64` angle ownership, `+0x834` battle gauge) are named dependencies, not
  defaults, and the angle-ownership and battle-gauge decisions would need owner input
  before authoritative use. Attack/shot/guard/hit/KO context stays for increment 2.
  Read-only: no source, test or data file changed; nothing built, launched or committed.

- 2026-10-16 — pilot agent — **owner condition recorded + sampling gap addressed** — the
  owner stated that candidate v1 is **not approved until the Phase 1 and Phase 2 gaps are
  closed, mostly checking sampling and proper documentation**; that condition is now
  recorded on the P2-0b row with the concrete gap inventory it points at, and the
  SCOREBOARD contract cell was updated to match. Worked the sampling half: verified the
  fixture domain is anchored to tick indices (a one-tick-shifted expectation fails as
  `tick 3 state exp 10 got 0`; a wrong per-tick value as `tick 13 step exp 0.000000 got
  7.200002`; two contradictory expectations on one tick are both evaluated), added
  **sampled-update accounting** to the runner (it now counts its own steps, prints
  `sampled=N updates`, and fails if the count leaves the tick domain), and documented the
  whole sampling model as contract §11 — what is sampled (end-of-tick values in the
  60 Hz fixed-step domain) and what is deliberately not (sub-tick values, interpolation,
  wall-clock or render frames, and any original-side state). Honest limit stated there:
  this samples the port's domain only and can never establish the original's update
  timing, which stays "not verified" for every case. Read-only apart from the test
  runner and documents; nothing built into the tracked tree, launched or committed.

- 2026-10-16 — pilot agent — **P2-1 increment 2, first cut** — enumerated the
  Rena-specific bodies in the bundle: **13 files, ~950 lines** (`battle_rena_ground_shot`,
  `mobile_shooting`, `full_charge`, `rena_projectile_switches`, the melee family,
  `rena_dash`, and `melee_admission`). Read two of them and recorded the seam in
  `PILOT-SEAM.md` §10: the State-400 shot body is **scalars plus an ordered event
  vector** (11 event kinds) that leaves magazine admission, attachment/world-projectile
  spawning and voice resolution to the host, and the melee admission body is a scalar
  selector returning a move id behind a data-supplied `Priority` gate — **not** a 46-way
  dispatch. Verified `battle_random.hpp` is the same recovered MT19937 the port already
  carries (init `1812433253u*(…)`, re-seed 5489), which strengthens P2-2's answer for the
  shot bodies, and corrected one of my own false positives: the "world/registry" grep hit
  was the `world_projectile` event **name**, and no actor registry or asset loader is
  referenced. Provisional judgement for these two families is **Option A**, with the real
  seam cost on the host side (admission, contact capacity, spawn, voice order). Guard,
  hit/KO, jump/air-dash, the charge/mobile bodies and `rena_projectile_switches` remain
  uncounted, so P2-1 stays `doing`; the parallel enumerator had not reported and its
  claims will be spot-checked against the files rather than accepted wholesale. No
  product source or test changed; nothing built, launched or committed.

- 2026-10-16 — pilot agent — **P2-1 increment 2 completed; Q18 raised** — bounded the
  enumeration myself after the parallel enumerator ran several rounds without reporting
  (it was stopped; it left no report, so nothing here rests on it). Counted the remaining
  families in the bundle (`PILOT-SEAM.md` §11): guard (3 bodies, 115 lines), hit/damage/KO
  (~14 shared bodies, ~400 lines), jump/landing/air-dash (~300 lines plus the generated
  `jump_native_bodies_20260929.hpp` at 19,727 lines), air shot (four generated schedule
  tables, 3,591 lines) and the charge family. The decisive find:
  `full_charge_native_world.inc.hpp:23-43` reads a real `BattleWorld` —
  `world.actors.at(slot)`, `relationships.secondary_target`, `actor_bone_world`,
  `transform_actor_point`, `selected_weapon_socket` — so the Phase 2 **charge-level** case
  needs a bounded world façade (actors, relationships, bone/weapon-socket transforms,
  statistics), while locomotion, ground shot, melee admission, guard, hit/damage/KO and
  jump/air-dash bodies need only scalars, RNG, trig, steering and event sinks. Per
  `DIRECTION.md` §4 2a this is presented instead of absorbed: **Q18** asks the owner to
  choose (a) Option A with a bounded façade sized by that body, (b) keep charge out of the
  pilot's first scope, or (c) read it as the Option B signal; the safe default is (b), with
  the exclusion explicit. P2-1 therefore stays `doing` with its count recorded rather than
  closing on a scope guess. No product source or test changed; nothing built, launched or
  committed.

- 2026-10-16 — owner decision + coordinator record — **Q18 answered: Option A with a
  bounded `BattleWorld` façade sized by the charge body** (not Option B, not deferral).
  Recorded in `QUESTIONS.md` Q18 (answered), `PILOT-SEAM.md` §12 (the façade's five
  bounded requirements, each mapped to data the port already has: `Match::fighter`,
  `TargetLocks`, the match rig worlds, the attachment/muzzle transform path and
  `Fighter::stats()`), and the P2-0c/P2-1 rows. The growth rule is explicit: a sixth
  requirement is a stop-and-re-present event, not an extension. P2-0c is therefore
  closed (route support delivered and decided); P2-1 continues only for the air-shot/jump
  host-side scheduling count. No product source or test changed; nothing built, launched
  or committed.

- 2026-10-16 — pilot agent — **P2-1 done** — completed the host-side count and closed the
  seam audit. Measured on the files themselves: the air-shot schedules (1,401 + 1,442 +
  488 + 260 lines), `roster_air_shot.hpp`, `jump_native_control.hpp`, `battle_jump_motion.hpp`
  and `battle_air_dash.hpp` all have **zero** references to `BattleWorld`, `world.`,
  `actors.at`, `actor_bone` or `weapon_socket`, and their entry points are self-contained
  `advance_roster_*` functions — so the charge family is the **only** pilot family needing
  the bounded façade. `PILOT-SEAM.md` §13 records the counts and the resulting three-group
  seam (port-owned scalars/services; generated tables read as data; one bounded façade),
  concluding that the §4 2a Option B trigger does **not** fire and that the owner's Option A
  decision is consistent with the measurement. P2-1 is closed with no product source or test
  change; nothing built, launched or committed.

- 2026-10-16 — pilot agent — **F1-3 fixtures extended to six; jump/guard/tap-shot covered** —
  added `rena0-jump-chain`, `rena0-guard-hold` and `rena0-tap-shot` and extended the runner
  with the expectation fields they need (`anim_set`, `state_enum`, `shot_row`, `shots`,
  `shot_fired`, `guard_started`, `melee_hit`, the last four read from the tick's
  `MatchFrame`), keeping the schema documented in contract §8. Three findings came out of
  authoring them and are recorded rather than smoothed over: (1) the **jump chain is
  phase-driven, not apex-driven** — the port's cited physics puts the apex at update 24,
  yet row 41 is bound at 4-6, an intermediate chain set at 10 and row 42 by 30, with the
  fighter airborne through 47 and landing at 48, so one intermediate chain row is
  **unresolved** and asserted by raw set index (the audit's allow-list is {2,3,4,5,43});
  (2) a held guard costs **exactly 25 of 100 stamina per second** (asserted over 60
  updates) and `guard_started` fires on the press update; (3) the ground tap binds row 400
  by update 12 and spawns on **update 13 — the State-400 body's own frame 12** once the
  press is frame 0, an agreement between recovered timing and the production path rather
  than a runtime comparison. Coverage in the F1-8 matrix moves from 2 covered / 9 partial
  to **5 covered / 6 partial / 0 untested-but-unlisted**. All six fixtures pass
  (`RENA0_FIXTURES: PASS (6 fixtures, 60 Hz, skips=0)`); nothing was committed.

- 2026-10-16 — pilot agent — **F1-3 coverage extended to 11 fixtures; three more cases covered,
  one blocker named** — added `rena0-ground-dash-up`/`-down` (rows 20/27), `rena0-air-dash-left`
  (row 30 after jump + double tap), `rena0-melee-ground-300` (row 300 clip, `AttackA` = enum 3,
  `swing_started`, active window opening at update 25) and `rena0-charge-hold` (Tap at 0, Yellow
  by the cited 30 updates, still Yellow at 205, Red by 212), extending the runner with
  `attack_row`, `charge_tier`, `charge_gauge`, `melee_active`, `swing_started` and `dummy_hp`.
  F1-8's matrix moves to **8 covered / 3 partial / 0 untested-but-unlisted**. Two findings are
  recorded rather than smoothed: the ground swing's **active window opens only at update 25**
  (this build's timing, not a recovered tick), and `charge_gauge` reads **1000 (full) at rest**,
  which contradicts the "0..1000 with +40/+5 refill" reading and leaves the seam's `+0x834`
  mapping unresolved. A Hit fixture was authored and then **removed rather than shipped failing**:
  the 300 swing produced no melee contact with the dummy at z = 60/40/30/20, so the runner needs a
  victim-placement helper like `test::Combo::placeAtAttack`; that is now the named blocker on the
  hit/KO rows. All 11 fixtures pass (`RENA0_FIXTURES: PASS (11 fixtures, 60 Hz, skips=0)`); nothing
  was committed.

- 2026-10-16 — pilot agent — **F1-3: hit and KO covered; 13 fixtures** — implemented the
  `place_at_attack <tick|active>` directive by reusing `test::Combo::placeAtAttack` exactly as the
  device-free melee tests do (`tests/damage_scale_test.cpp:184-185`,
  `tests/fighter_script_test.cpp:761`), added `dummy_start_hp` (the port's own
  `MatchConfig::startHP[1]`), the `dummy_ko`/`ko_credit`/`dummy_respawned` observables and a
  `trace` directive as an authoring aid (prints instead of asserting; tracked fixtures do not
  depend on it). Hit fixture: with the dummy on the attacker's posed volume the swing is active
  over updates 14-19, the contact lands at **15** and removes the recovered **8 HP** (100 → 92).
  KO fixture: one such hit on a dummy launched at 8 HP leaves the victim at **1 HP**, with the
  economy registering the KO at update 16 and no respawn on the contact update. Two things are
  recorded as open rather than frozen: `MatchFrame::koCredits[0]` stayed 0 through update 100
  (balloon credit on another index, or needing the round's balloon rules — unprobed), and row 300
  reports its active window at 14-19 with a victim on the volume versus from 25 onward with the
  victim out of reach, a discrepancy whose cause is not established. F1-8 moves to
  **10 covered / 1 partial / 0 untested-but-unlisted**. All 13 fixtures pass, three runs are
  byte-identical; nothing was committed.

- 2026-10-16 — pilot agent — **F1-3 complete: 19 fixtures, 11/11 target cases covered** — added the
  six remaining 300-family variants (`rena0-melee-back-310`, `-lateral-311`, `-forward-dash-330`,
  `-air-320`, `-lateral-dash-331`, `-air-dash-332`), all passing; 331 and 332 are **new** evidence
  that no existing test asserted. Two open questions were probed to a concrete answer rather than
  guessed: (1) the row-300 melee active window is **distance-dependent** — updates 14-19 with the
  opponent within reach and 25-30 with it out of reach, same six-update length, measured with tap
  and held inputs alike, so the opponent's distance is the factor and not the input or the
  placement; the plausible "approach phase skipped when already in reach" cause is labelled a
  hypothesis. (2) After a KO, `koCredits[0]`, `koCredits[1]` and `overkillHits[0]` all stay 0
  through update 100 while the victim's side balloon reads 20, so the balloon-fill credit path
  looks unexercised under default round rules — also labelled a hypothesis. F1-8's matrix is now
  **11 of 11 covered / 0 partial / 0 untested-but-unlisted**. All 19 fixtures pass, three runs are
  byte-identical, and nothing was committed.

- 2026-10-16 — pilot agent — **P2-4 done (both increments)** — recorded the actor context for the
  non-locomotion bodies as `PILOT-SEAM.md` §14: the shot body's field map (7 existing product
  counterparts, `elevation`/`complete` derived, `offset`/`movement` unresolved), the nine event
  kinds mapped to the port's own surfaces (`MatchFrame` voice/sound fields, `ProjectilePool`,
  `contact_disabled`, the melee contact path), the melee-admission field map (9 existing
  counterparts), the shot path's update order (`m_shotMoveId` binds when the shot fires,
  `fighter.cpp:2488`, and clears on leaving the Shoot states, `:1053`), and the host/service
  ownership split. Two pieces of **reuse were found rather than assumed**: `melee_admission.h`
  already implements the recovered admission with its `cancelThreshold <= priority` gate (with
  Rena's `boosted` arm a named gap) and `move_behavior.h` already encodes the recovered shot
  programmes as data ops — real adapter glue already paid, though that file stays in the plan's
  REPLACE list. Counted: 9 of 11 event kinds mapped, 1 partial, 1 unresolved (contact capacity);
  unresolved items carried forward are `offset`/`movement`, the Rena `boosted` arm, capacity
  semantics, `elevation` derivation and the statistics admission order. Nothing was silently
  zeroed and no product file was modified; nothing built, launched or committed.

- 2026-10-16 — pilot agent — **owner review recorded; contract revised to candidate v2** — the owner
  reviewed candidate v1 and **withheld approval** for four acceptance gaps, and answered the budget and
  offline questions: **P2-0a has no fixed cap** (implement step by step, effort reviewed after each row,
  stop at scope growth), and **P2-5 (offline body tests) and P2-6 (isolated resolver, unwired to the
  default path) are allowed** while approval is pending, with 2e flag integration still gated. All four
  review items are answered in candidate **v2**: (1) a fail-closed acceptance set — `MANIFEST.txt` plus
  the runner's own required lists of the eleven §4 Phase 2 cases and the §2b observables, so a deleted
  fixture, a deleted manifest line or a removed assertion fails the run (all four mutations verified with
  their exact messages); (2) §2b maps every acceptance field to its required fixture and tolerance and
  **declares seven fields unsupported with reasons** (`charge_gauge`, `koCredits`, `overkillHits`,
  `pending_ko`, `charge_whole`, `round_over_side`, `kos`) instead of leaving them claimed; (3) tolerances
  are per observable in the runner and in §2b (exact for int/enum/bool, 1e-3 for position/step/balloon,
  1e-4 for the hold-seconds, 1e-2 degrees for `turn_deg`), with the tolerance printed on failure; (4) the
  scoreboard, the document index and Q13 now agree with the candidate. The fixture set grew to **20**
  while doing this (a timed-round case was added, and assertions for `phase`, `elapsed`, `x`, `z`,
  `shot_tier`, `main_whole`, `swing_hits`, `melee_victim`, `melee_recovery`, `guard_exhausted`,
  `air_dash_context`, `round_over`/`round_end`, `balloon1` and the hold-seconds were added), with new
  findings: `red_hold_sec` 3.5 s puts the Red boundary at update 210, and the round clock runs during the
  60-update BattleStart so `time_limit 1` expires before a fixture's tick 0. The run reports
  `PASS (20 fixtures, 60 Hz, 21 case rows, 39 acceptance fields, 7 unsupported declared, 0 unreferenced
  extras, skips=0)`. Approval remains the owner's; nothing was self-approved and no product source was
  touched.

- 2026-10-16 — pilot agent — **P2-5 (2c) done: offline body tests for two recovered bodies** — with the
  owner's authorisation to proceed while contract approval is pending. `tests/rena0_body_test.cpp` is
  data-free and feeds explicit scalars into the recovered locomotion body (53 checks): idle entry/tail,
  the gauge refill and its 1000 clamp, walk admission and release proposals, the recovered 7.2 speed,
  direction categories with the 20→19 turn decay, stop-word suppression, strict phase completion versus
  the held gate, the body's own validators (state 43/1, grounded 2 and gauge 2000 are rejected rather
  than clamped) and an invariant sweep over **3456** input combinations with **0** violations.
  `tests/rena0_admission_body_test.cpp` is install-backed (24 checks, 77 = skip, verified from a
  data-free directory) and pins the recovered melee admission against explicit inputs and the **real**
  move table's priority gate: dash sources 330/331, directional 310/311, landing 340 and the 340→341
  follow-up, the 300→301→302 chain, the airborne 332/320 split, and the weapon-2 exclusions. Two
  failures during authoring were mine, not the port's: I had assumed the gate would admit the 300 and 320
  fallbacks from rows 310 and 15, and the measured matrix shows the gate is **data-driven, not
  structural** — those refusals are now asserted as cases, and an env-gated `RENA0_ADMISSION_MATRIX=1`
  prints the reachable set for future work. The tests are labelled a consistency check against the
  bundle body (shared source), not independent original proof, and the port's deliberate `boosted` gap
  is not asserted. Effort report (owner set no fixed cap): one round, two new test files plus CMake
  wiring, no product source touched; full host suite now **75 tests, 100% passed**, with the body test's
  rena0 group at 4/4. Documented counts in `README.md` and `RELEASE-CHECKLIST.md` §2 were updated to the
  measured number, and contract §8 now states that body-test checks are not acceptance cases.

- 2026-10-16 — pilot agent — **P2-5 (2c) done: the fixture-linked differential** — increment 2 of the
  offline body tests, with the owner's authorisation. To avoid a second parser, the fixture format now
  lives in one place (`tests/rena0_fixture.h`, shared by the F1-3 runner and the differential; the F1-3
  run stays byte-identical and the manifest mutations still fail). `tests/rena0_differential_test.cpp`
  drives each fixture's own input script through both the production Match/Fighter and the recovered
  locomotion body, classifies every tick as in-domain or out-of-domain with the reason, and compares the
  body's decisions: **313 in-domain ticks** across the set (540 out-of-domain, 7 transition ticks), state
  admission **313/313**, walk speed **312/313**, clock **313/313**, turn step **313/313**, and exactly one
  divergence class — the recorded `speed-retained-on-stop` on **1** tick. The 7 clock mismatches seen while
  authoring were all transition ticks where the body correctly resets its paired clocks, so the harness now
  applies the transition rule there rather than the strict arithmetic; that investigation is why the final
  clock agreement is 313/313 instead of 306/313, and the earlier number was a harness defect, not a body
  divergence. The harness fails closed both ways, mutation-verified: a deliberately wrong expectation gives
  `unexplained=7` and exit 1, and a fixture set with no in-domain ticks exits 1 with
  `no in-domain ticks were compared`; without game data it exits 77. Effort report (no fixed cap): one
  round, one shared parser header, one harness, CMake wiring, no product source touched. Host suite now
  **76 tests**; the rena0 group is 5 tests. Documented counts updated in `README.md` and
  `RELEASE-CHECKLIST.md` §2.

- 2026-10-16 — pilot agent — **P2-6 (2d) done: the isolated resolver** — with the owner's authorisation
  to proceed while contract approval is pending, and explicitly unwired. `rena0_resolver.h` is the single
  binding owner for the pilot seam: a scalar view in, explicit move/phase/set out, every path carrying a
  reason instead of a silent zero. The unresolved dependencies the seam recorded are named rather than
  invented — an armed+ready view inside the 299 < state < 350 window sets `boostedGap` (the port's own
  admission gap) and an airborne locomotion proposal returns `airborne-set-unresolved` with no row. The
  test covers the row's four named areas with 46 checks: model bounds (a rig one anim short, plus
  no-move-table/no-move-row/move-row-absent/phase-set-unbound), equipped weapon (bound/unbound/absent),
  phase changes (shipped row 20's three phases resolve their own differing sets) and the side-dash
  regression (states 23/24 with and without back → 330/331, with the forward-dash branch shown not to
  collapse). **The unwired guarantee is enforced, not promised**: the test walks all 162 files under
  `src/` and fails if any of them includes the resolver, and both that guard and the bounds check are
  mutation-tested (a temporary include in `main.cpp` fails with `unwired scan: .../main.cpp includes the
  resolver`; disabling the bounds check fails 3 checks). Two of my own expectations were wrong during
  authoring and were corrected against the bodies: the stop word keeps the incoming row (the body is
  suppressed, not returned to idle), and `test::Combo` holds its weapon by value. Effort report (no fixed
  cap): one round, one native header, one test, CMake wiring; no product source changed and nothing was
  rerouted. Host suite count moves to 77 with the new test.

- 2026-10-16 — pilot agent — **contract v2 APPROVED; records reconciled; 2e ordered in slices** — the owner
  approved candidate v2 for the stated Rena+0 scope (`sha256 c5df99313725d80ee1ba9ae8d7161d4ca252512349ac65e962f37730565a18c6`), having rebuilt and run five suites (all
  passed, none skipped) and independently repeated four enforcement mutations (missing fixture, case
  declaration, field declaration, required assertion) — each failed as intended. The approval is recorded in
  the contract's status line, this file's F1-2/F1-7/P2-0b rows and the document index, and the scoreboard's
  contract row; **acceptance stays 0/46 until the 2g verdict**, and post-approval changes to acceptance
  fields, tolerances or exclusions need a version bump. The owner's budget answer (P2-0a: no fixed cap,
  stepwise effort review) is now also recorded in **Q15**, which previously said no budget was recorded, and
  the remaining stale "not approved" summaries were updated. Owner's ordered plan for 2e, recorded here as
  the working order: (1) locomotion behind the flag first, resolving clock and state ownership, with adapter
  equivalence and flag-off restoration demonstrated before any combat family is added; (2) each later body
  added with its offline expectations, event checks and scripted scenarios — noting explicitly that the
  11/11 fixture count does **not** establish recovered-body coverage for every family; (3) complete 2f, then
  present the verdict evidence, with cleanup following a green verdict in a separate change.

- 2026-10-16 — pilot agent — **2e ownership resolved; slice 1 scoped** — per the owner's ordered plan,
  the clock and state ownership question is answered before any code: [`PILOT-SEAM.md`](PILOT-SEAM.md) §16
  records who owns each locomotion decision today, in slice 1 (observe mode behind
  `--native-actions=rena0`) and in slice 2 (drive mode), with the two acceptance conditions for slice 1 —
  adapter equivalence using the divergence classes the offline differential already named, and flag-off
  restoration verified as byte-identical gameplay log lines between two runs of one scripted scenario —
  and with position integration, collision and animation binding explicitly staying with the port. The
  insertion points are named: `Options` at `main.cpp:137` and the live step at `main.cpp:3953`. Combat
  families stay out of these slices and follow one at a time with their own offline expectations, event
  checks and scripted scenarios; §16 records the owner's point that the fixture matrix is observable
  coverage, not recovered-body coverage for every family.

- 2026-10-16 — pilot agent — **2e slice 1 done: the pilot flag with locomotion in observe mode** — built to
  the owner's order. `--native-actions=rena0` samples P1 before each match step and compares after it, using
  the resolver; nothing is written to the fighter, and diagnostics go to stderr so gameplay stdout is
  untouched. Measured on a new scripted locomotion recipe (240 frames): 180 in-domain ticks, **180 agreed, 0
  disagreed**, 60 out-of-domain with named reasons (BattleStart et al.). Flag-off restoration is demonstrated
  two ways: stdout is byte-identical between the flagged and unflagged runs apart from the wall-clock timing
  lines, and the rendered capture is byte-identical. Two clock facts were measured instead of assumed and both
  corrected my harness: a transition tick's clock already reads 1 (enter_phase then advance, fighter.cpp:1759),
  and locomotion sets carry the phase gate so their clock never completes (measured 35 -> 36 past a 35-update
  clip). One mapping correction came out of it: **`move_counter` is not a per-tick clock** but a move-program
  data counter (CounterSet/Counter ops, kGateCounter gates, aim spread), so F1-5's `secondary = move_counter`
  was a proxy and the body's secondary has no established port counterpart — the adapter names that on every
  run and does not compare it. The acceptance contract is unaffected (the secondary clock is not an acceptance
  field), so the approved revision stands and its hash citations are unchanged. The adapter's comparison rules
  also now run inside the fixture-linked differential (331 in-domain ticks, 331 agreed), and the resolver test's
  unwired scan was refined to the 2e boundary and mutation-verified in both directions. Effort report (no fixed
  cap): one round, one adapter header, the flag plumbing, one script asset and one differential extension; the
  host suite stays at 77 tests. Slice 2 (drive mode) awaits the owner's sign-off on this evidence.

- 2026-10-16 — pilot agent — **2e slice 2 done: the recovered body drives P1's locomotion behind the flag** —
  `Fighter` gained a `PilotLocomotion` policy (state proposal + walk speed) that is attached **only** to the
  pilot fighter while `--native-actions=rena0` is set; with the flag off no policy exists and both hook sites
  are skipped, which is why the default path is structurally unchanged (the 77-test suite confirms it).
  Measured on the locomotion recipe: **181 drive ticks**, observer still 180 in-domain / 180 agreed / 0
  disagreed, stdout byte-identical to the legacy run apart from wall-clock timing lines, and the rendered
  capture byte-identical. The drive path is **mutation-proven load-bearing**: forcing the policy to propose
  idle changes the capture and makes the observer report 136 disagreements, so a divergent body is caught
  rather than silently accepted. The turn step and the phase clock stay port-owned, with the reason recorded
  in PILOT-SEAM §16: the port already encodes the same recovered turn rule (20 reset, decay, floor 1) and the
  same clock convention, so driving them would add a second implementation of identical behaviour rather than
  a recovered one. One guard fix came out of this: the resolver test's unwired scan matched header names in
  comments, so a documentation comment naming the adapter tripped it — it now matches `#include` lines only,
  and a real include in `fighter.cpp` still fails it (re-verified). Effort report (no fixed cap): one round,
  two hook sites in the legacy decision file, one policy interface, the adapter's driving half and the flag
  attachment. Combat families remain, one at a time, with their offline expectations, event checks and
  scripted scenarios.

- 2026-10-16 — pilot agent — **P2-7: first combat family (melee) added the owner's way** — offline
  expectations and event checks already existed (the 24-check admission body test against the real move
  table; the F1-3 melee fixtures pinning `swingStarted`/`meleeHit`/`meleeVictim` and damage), so this round
  added the runtime comparison and the scripted scenario. `observe_rena0_melee` asks the recovered admission
  the same question the port asked on every fresh admission; `tests/scripts/melee-ground-300.txt` drives four
  presses (neutral, chain, walking, back-held) and measured **4/4 agreed** — rows 300, 301, 302, 310 — with the
  flagged run's stdout and rendered capture byte-identical to the unflagged run. The suite carries the same
  comparison across the fixture set: **9 fresh admissions, 9 agreed**. Two findings came out of it. First, the
  **default path already drives melee from the recovered admission** (`attack_admission_recovered` and
  `AttackAdmissionInput` at `fighter.cpp:467-475` and `:1604-1612`), so for this family the pilot's
  contribution is verification and gap-naming (the `boosted` arm), not a new driving path — which is exactly
  why equivalence, not a new mechanism, is the right evidence. Second, the admission axes are
  **facing-relative**: `held_axis_z` reads Up as +1 and Down as -1, so the recovered back branch (`z < 0`) is a
  Down press; my adapter had it inverted and reported a false mismatch on the back-held fixture. The helpers
  now live in one shared header (`src/gameplay/held_axis.h`) used by both the legacy dispatcher and the
  adapter, so they cannot drift, and the suite went from 8/9 to 9/9. Effort report (no fixed cap): one round,
  one observation function, one script asset, one small shared-header extraction and its two include sites.

- 2026-10-16 — pilot agent — **P2-7: second combat family (shot) started — the body is adapted and its
  event order pinned offline** — unlike melee, the ground-shot body had no port-side counterpart, so this
  family began with the adaptation: `src/gameplay/native/rena0_ground_shot_observation.h` reproduces the
  bundle's `battle_rena_ground_shot.hpp` for weapon slots 0 and 1 (plus the two steering helpers it uses,
  with the bundle's `42dc20` note) and returns the body's **ordered** event list. `tests/rena0_shot_body_test.cpp`
  pins that order from scalars alone — 36 checks, data-free, never skips: activate only at frame 0; nothing
  from frame 1 to 11 while phase 0 decays the speed by 0.5; at frame 12 model(-1,0), model(-1,1), sound 70,
  shot_statistics, voice 27 (30 on the last round, with the host-resolved predicate recorded on the event),
  and the attachment (bullet 6 when armed) with the elevation clamped to ±30; from frame 13 only the two model
  requests repeat; `complete` proposes state 0 and the airborne case proposes 43 with gravity 0.5, both silent.
  Weapon 1's branch is adapted too (first frame activate/melee_statistics/clear_contact/contact_capacity plus
  the strike request, frame 7 speed 45, frame 15 sound 67 + voice 29, frame 18 sound 77 + statistics + one
  attachment or two when armed, strike live over frames 8-18). Weapon 2's scatter is the only caller of
  `legacy_trig` and its 3600-entry cosine table, which is **not** adapted, so that branch **throws** with the
  reason instead of returning a silent empty result — Rena+0 is slot 0, so the pilot's path is complete while
  the gap stays visible. The pilot-path guard was extended to the observation bodies (included only from
  `native/`, mutation-verified). Effort report (no fixed cap): one round, one adapted body header, one
  data-free test and its CMake target. Still to come for this family: the live comparison against the port's
  shot path and the charge levels, then guard/hit/KO.

- 2026-10-16 — pilot agent — **P2-7: the shot family's live comparison is done** — `observe_rena0_shot`
  advances the recovered ground-shot body once per tick while the port holds a shot row and owns the body's
  `frame` clock (the body reads it and never advances it), then compares the three correspondences the seam can
  defend: the fire tick (the body's frame-12 statistics/projectile request against `shotFired[0]`/`shotsSpawned`),
  the sound id (`soundEffectId[0]`) and the voice id (`shotVoice[0]`/`shotVoiceAlternative[0]`). Measured on the
  new `tests/scripts/shot-ground-400.txt` (two taps and one held press): **98 shot ticks, fire 2/2, sound 2/2,
  voice 2/2, 0 disagreements**, with stdout and the rendered capture byte-identical to the unflagged run. The
  suite carries the same comparison on the tap-shot fixture (fire/sound/voice 1/1). A **row guard** keeps the
  comparison honest: the adapted body models state 400 only, so a bound walking/dash/charge row (401/403/405-408,
  450/469) is reported as `shot-row-unadapted` instead of being compared against the wrong body — the live run
  shows exactly that, with the held press reaching a charged row and being named while the two taps match on all
  three channels. Projectile positions, the pitch (whose `elevation` input is the derived value the seam lists as
  computed) and the model requests are explicitly not compared. Charge levels stay the port's own path, pinned
  offline by the charge fixture (tiers, 0.5 s yellow, 3.5 s red → Red at update 210) with `charge_gauge` declared
  unsupported; the charge rows' bodies are not adapted. Effort report (no fixed cap): one round, one observation
  function, one script asset and one differential extension. Remaining families: guard/hit/KO, then 2f.

- 2026-10-16 — pilot agent — **P2-7: third combat family (guard) adapted offline** — the guard body
  (`battle_guard_motion.hpp`, the original's 438310) is now reproduced in
  `src/gameplay/native/rena0_guard_observation.h`, with the two steering helpers moved into a shared
  `rena0_steering.h` that the shot body uses as well. `tests/rena0_guard_body_test.cpp` pins the body's
  transition logic in 26 data-free checks: the frame-0 speed/contact clear and its `clear_contacts`
  request, the offset approach of 20, the guard gauge draining 10 per frame in phase 1, the three phase-2
  release conditions, the 391 contact path (and its refusal at gauge 0), the 20-frame hold release, the
  −15 recoil entry with the same frame's ramp to −14, the 391 phase cap, and the completion/airborne
  proposals including 103 for an airborne successful guard. Two of my expectations were wrong and were
  corrected against the body's own ordering (the entry reset clears the hold counter before it counts;
  the ramp applies in the entry frame). A units caveat is recorded rather than papered over: the body's
  gauge is 0..1000 drained 10 per frame while the port's stamina is 0..100 at 25 per second, so the live
  comparison will compare state/phase/contact decisions and not the gauge — consistent with contract §2b
  declaring `charge_gauge` unsupported. **Hit/KO are deliberately not adapted**: the bundle spreads them
  across a damage/death pipeline (damage pipeline, hit damage, death motion, first death and more), which
  is more than one round should start without the owner's steer, and their observables are already pinned
  by the hit and KO fixtures with the unsupported fields declared. The pilot-path guard now also covers the
  guard and steering headers. Effort report (no fixed cap): one round, one adapted body, one shared-header
  extraction, one data-free test and its CMake target. Remaining: the live guard comparison, then 2f.

- 2026-10-16 — pilot agent — **P2-7: the guard family's live comparison is done, and it surfaced a
  provisional port rule** — `observe_rena0_guard` advances the guard body while the port is in `Guard` and
  compares the two facts both sides have. Measured on the new `guard-hold-live.txt` + `guard-attacker.txt`
  (P1 guards updates 70-200, P2 swings three times from inside reach): **118 guard ticks, 3 guard starts,
  2/2 guarded contacts agreed, 0 disagreements**, stdout and rendered capture byte-identical to the unflagged
  run, and the suite carries it at 240 guard ticks. Getting the comparison honest took one correction: the
  port reads the guard **before** the damage call and that same call stuns the victim out of `Guard`
  (`match.cpp:265-280`), so the block report and the state exit arrive on one tick — the observer now checks
  the contact first, which is why the first run saw `blocks 0/0` and the final one sees `2/2`. Two findings
  are recorded rather than smoothed over: (1) the port binds no *move* and keeps no simulation phase for
  `Guard`, so the body's phases 0/1/2, its 390/391/392 rows and its 20-frame hold counter have no port
  counterpart (`guard-granularity-unrepresented`) — later work bound the stance's *animation* sections
  (sets 60 then 61, gate-aware), which is why the later entries read differently — although the attacker-side 392 recoil **is** recovered through
  `rena_guard_exit_row`; and (2) the victim-side guard damage gate is an explicitly **PROVISIONAL** port rule
  (guarded damage reduced to 20%, `fighter.cpp:1228-1235`, whose own comment says the original's guard damage
  gate is unmapped), while the body's gauge is not the port's stamina (`guard-gauge-units-unresolved`). That
  second one is a decision for the owner: adapt the hit/guard damage pipeline to recover the real gate, or let
  the provisional rule stand for the pilot. Effort report (no fixed cap): one round, one observation function,
  two script assets and one differential extension. Remaining after that decision: 2f.

- 2026-10-16 — pilot agent — **the guard damage gate is established, and it is zero damage** — the owner
  asked for the victim-side gate before closing 2e because it changes HP and KO outcomes, and for focused
  binary analysis only if needed. It was not needed: the bundle's `battle_hit_guard.hpp` reproduces the
  predicate and the repo's own listing `research/decompiled/FUN_00637950.c` (0x637950) confirms it at lines
  185-192 — guarded when the impact is within **±45°** of the victim's facing (unless the victim carries
  flag 0x2000), the victim carries flag **0x400**, and the attack lacks flag **8** (unblockable); the guarded
  path writes contact word 2, ORs 0x100 when the victim carries 0x8000, decrements `remaining`, calls
  `FUN_0042c800(2)` (the attacker's 392 reaction the port already implements) and increments the guard
  counter. **The decisive part is the outcome: the guarded branch (`FUN_00637950`'s `else`, lines 541-552)
  applies no damage at all** — no `FUN_00435990` damage call, no health write, no statistics update. So a
  guarded melee hit deals **0 HP**, and the port's current 20% rule is wrong rather than merely provisional;
  the port's predicate is also coarser, testing only `state() == Guard` and ignoring the angle, the victim's
  0x400/0x2000 flags and the unblockable attack flag. Next, per the owner's bounded plan: carry the recovered
  predicate and zero-damage outcome behind the flag, add a guarded-contact fixture that checks the resulting
  HP and the hit/KO events, and show the flag-off path is byte-for-byte the legacy behaviour. This is the
  pilot's first behaviour-changing feature, so the guard scenario's restoration claim is "legacy behaviour
  unchanged" with the measured difference as the evidence, not "identical output".

- 2026-10-16 — pilot agent — **the recovered guard gate is implemented behind the flag, with fixtures and live
  evidence** — following the owner's bounded plan after the gate was established as zero damage. `Fighter`
  gained a `PilotGuard` policy attached to the victim, and both melee damage sites in `try_melee_hit` (the
  data-driven record path and the recovered-hitbox path) now route through one helper, so a guarded hit never
  reaches `take_damage`: no damage and no stun, which is what `FUN_00637950`'s guarded branch does. The
  adapter's predicate applies the recovered angle term (the victim must face the attacker within 45°) and
  stands in the port's own `Guard` state for the victim's unrecovered `0x400` term; the victim's `0x2000`
  (guard from any angle) and the attacker's unblockable flag `8` are **not expressible** from port data and are
  named as not applied rather than guessed. Two new fixtures differ only by the `pilot rena0-guard` directive —
  `rena0-guard-gate-pilot` pins **100 HP** (recovered) and `rena0-guard-gate-legacy` pins **99 HP** (the legacy
  20% rule floored at 1) — and they are deliberately **extras, not acceptance cases**, so approved v2's scope is
  untouched. The live guard scenario reports `guard gate asked=3 guarded=2 not-guarding=1 outside-angle=0`: the
  two guarded hits are blocked and the third lands after the release, so P1 ends at **92 HP** (0+0+8) where the
  legacy rule gives 90 (1+1+8), and the flagged and unflagged captures now differ. That makes this the pilot's
  **first behaviour-changing feature**: for guard scenarios, flag-off restoration means the legacy behaviour is
  unchanged (legacy fixture still 99, unflagged capture unchanged from before), not identical output — and the
  difference between the two fixtures and the two captures is the evidence. Two harness corrections on the way:
  the first hook sat only in the legacy-hitbox branch, so the shipped records bypassed it (`asked=0` revealed
  it), and the adapter header was not self-contained (it relied on `match.h` from its includer). Effort report
  (no fixed cap): one round, one policy, two gated damage sites, two fixture directives, two fixtures and one
  live scenario. Remaining: 2f.

- 2026-10-16 — pilot agent — **P2-8 (2f) done: the evidence and rollback check** — written up in
  [`PILOT-SEAM.md`](PILOT-SEAM.md) §21 against the approved contract v2 (reviewed content `sha256 c5df9931…`), with no
  cleanup (2h waits for the verdict) and acceptance still 0/46. The approved matrix runs green: 22 fixtures, 21 case
  rows, 39 acceptance fields each mapped to a fixture that asserts it, 7 unsupported fields declared, and the two
  guard-gate fixtures reported as extras outside the approved scope; the offline body tests (53/24/36/26 checks) and
  the resolver's 48 checks are green too. Comparisons: the fixture-linked differential covers **315 in-domain ticks**
  with no unexplained divergence, and the live observers agree on locomotion 180/180, melee 4/4 (11/11 in the suite),
  shot fire/sound/voice 2/2 (1/1 in the suite) and guard 2/2 guarded contacts. Provenance is tabulated per claim with
  its tier and artifact, and the unresolved limits are named individually rather than summarised. **Rollback:** the
  locomotion, melee and shot scenarios are byte-identical to the legacy baseline in deterministic stdout and in the
  rendered capture; the guard scenario differs only in the HP fields (`hp=90` → `hp=92`, exactly the two guarded hits
  at 0 instead of `max(1, 8/5)` = 1) with `hits=3`, `shots=0`, `sparks=0` and `fx events=3` identical, and the legacy
  fixture still pins 99 HP — so the flag-off baseline is unchanged from before the gate existed. No global resolver
  change: with the flag off no pilot policy is attached, and the resolver test's scans (mutation-verified both ways)
  keep the resolver, the adapter and the recovered observation bodies out of the default path. Rollback is removing
  the flag; after 2h the recorded pre-cleanup revision is the fallback. 2f claims neither original-runtime parity nor
  acceptance: the verdict is 2g and belongs to the owner.

- 2026-10-16 — pilot agent — **2g stays pending; the owner named three gaps** — the owner reviewed the 2f evidence
  (their own focused run: 10/10, no skips) and kept the verdict pending: the evidence supports a working, reversible
  pilot slice but not a green verdict for the approved Rena+0 scope, and red was rejected because the method did not
  fail. The three named gaps are recorded verbatim in the P2-9 row and the scoreboard's verdict block: charge and
  hit/KO bodies still on the port path; the shot comparison covering fire/sound/voice but not projectile positions or
  model requests; and the guard predicate's port proxy for one flag plus two inexpressible flags, with its fixtures
  outside approved v2. The owner's instruction is explicit: finish or explicitly re-scope those load-bearing cases,
  then repeat 2f against the resulting approved contract — and **do not start 2h cleanup or lift the freeze while the
  verdict is pending**. This is recorded as the pilot's working order; the closure plan lives in
  [`PILOT-SEAM.md`](PILOT-SEAM.md) §22.

- 2026-10-16 — pilot agent — **the pending-verdict closure plan (v3 proposal) is written, and gap 2 is partly
  closed** — after the owner kept 2g pending and named three gaps, `PILOT-SEAM.md` §22 records a per-gap
  proposal for the owner to choose from: adapt the charge and hit/KO bodies or exclude them explicitly (1a/1b);
  investigate the shot `model` request's real port counterpart or record it as an unverified mapping, and leave
  the projectile spawn positions as a named limit or treat them as required tier-1 evidence (2a-2d); and locate
  the guard flag words' builder with focused binary analysis, re-scope the flag terms, and/or promote the two
  guard-gate fixtures into the contract (3a-3c). Work done this round on gap 2: the shot observer now also
  compares the **projectile pitch** (agreeing **2/2** on the live shot scenario, and still 1/1 in the suite) and
  counts the body's `model` clear requests, which the port's per-slot binding never matches — measured **0/148**.
  That comparison was deliberately made **non-gating**: the mapping is unverified, and asserting my guess would
  have frozen it as behaviour. The verdict stays pending, the freeze stays in force, and no cleanup has started.

- 2026-10-16 — pilot agent — **the owner chose the closure package for all three pending-verdict gaps** —
  recorded in `PILOT-SEAM.md` §22 with the working order. Gap 1: **adapt the charge bodies** and **explicitly
  re-scope the hit/KO damage-and-death pipeline** out of v3 by name, with the hit and KO fixtures as its only
  evidence. Gap 2: run **one bounded investigation** into what the body's shot `model` clear request corresponds
  to before asserting anything, and leave the projectile **spawn positions a named limit** (tier-1 evidence, which
  the plan allows to remain unverified). Gap 3: **locate the flag words' builder with focused binary analysis** so
  the victim's 0x400/0x2000 and the attacker's unblockable 8 become expressible and the proxy goes away, and
  **promote the two guard-gate fixtures into v3** so the gate's evidence is inside the approved scope. Working
  order: charge bodies → model-mapping investigation → flag-word analysis → write contract v3 → owner approval →
  re-run the matrix and the four live comparisons → repeat 2f against approved v3 → 2g. The verdict stays pending
  and the freeze stays in force; no 2h cleanup.

- 2026-10-16 — pilot agent — **gap 1a first increment: the charge-gauge bodies are adapted** — following the
  owner's choice, `src/gameplay/native/rena0_charge_observation.h` now reproduces the bundle's
  `battle_attack_charge.hpp` (0x63844e-0x6384fa, attacker mode 1) and `battle_hit_charge.hpp`
  (0x6382d9-0x63844e, victim modes 0/2) with the shared integer helpers, and `tests/rena0_charge_body_test.cpp`
  pins them in 29 data-free checks: the mode and blocked gates, the divisors 90/133/225, the defense and
  modifier factors, the limit clamp, the notification ids 6 (attacker) and 5 (victim mode 0, while mode 2
  notifies nothing), and the preserved integer semantics including the original's `INT_MIN / -1` fault. Those
  rules are exactly what the contract's unsupported `charge_gauge` lacked. The adaptation also produced a
  finding worth the owner's attention: "the charge bodies" splits in two — the hand-reconstructed **gauge**
  bodies (adapted now) and the charge **move** bodies (states 350-362), which live in the bundle's
  `full_charge_native_bodies_20260929.hpp`, are **generated decompiler output** whose own header warns that
  generation is not parity proof, and whose Rena+0 slice is a 40-line wrapper over host calls (clear a word,
  bind item models 0/1 to the two slots, two service calls) with little decision content to drive. They are
  therefore deliberately not adapted, and the port's charge rows stay on their own data-driven programmes pinned
  by the charge fixture (tiers, 0.5 s yellow, 3.5 s red, Red at update 210). Next for this family is the bounded
  correspondence question: how the recovered gauge (0..limit) relates to the port's `charge_gauge` (0..1000,
  full at rest) — the `+0x834` item that v3 must either resolve or explicitly exclude. The pilot-path guard now
  also covers the charge header, and the suite grows to 80 tests.

- 2026-10-16 — pilot agent — **the charge-gauge correspondence is answered, and it corrects the contract's reason** —
  following gap 1a, the bounded correspondence question is settled: the adapted gauge bodies belong to the **special
  gauge** (`BattleSpecialGauges.charge0/charge2`, consumed by the special body), whose port counterpart is the **hyper
  gauge** (`m_gauge`) — and the port refills that gauge but **never accumulates it from damage**, which is precisely
  what those bodies describe. The port's `charge_gauge` is a **different** gauge, the +0x834 shot gauge, and its
  refill **is** implemented (`MoveOp::Recharge` adds +40, or +5 with hit-status slot 6, capped at 1000, on the
  dash-recovery rows 403/409/469). What the port lacks is a **spend path**: `m_chargeGauge` is only reset to 1000,
  refilled toward 1000, and read by two charged-attack gates — nothing decrements it, so a gauge that starts full can
  never be observed to move. That, not an unresolved refill, is why §2b declares it unsupported, and the recorded
  reason was both too pessimistic about the refill and silent about the spend. v3's options are now explicit:
  (a) implement the damage-based special-gauge accumulation behind the flag (the charge family's drive step),
  (b) find the +0x834 spend rule with focused analysis so `charge_gauge` can be promoted to asserted, or (c) record
  both as exclusions with this evidence. The owner's steer decides; both (a) and (b) are bounded.

- 2026-10-16 — pilot agent — **the owner chose both charge items, and the spec is recovered with one hard
  dependency** — the special-gauge accumulation and the +0x834 spend-rule analysis are both approved in principle
  for v3. `PILOT-SEAM.md` §23 now carries the full implementation spec from `battle_special_gauges.hpp`: the
  mode-selected three-gauge system (charge0/limit0, charge1/limit1 attacker-side, charge2 on duration0), the
  accumulation through the adapted bodies via `victim_state`/`attacker_state` and `store_victim`/`store_attacker`,
  the consumption rules (mode 0/1 decrement while active; mode 2 advances a movement gauge to 1000 and drains
  **health by 7 per tick**, ending below 9), the activation chords (melee+shoot in 1..2 with an action window and
  `charge >= limit`), and the refill steps (active2 → 2, active0 → 1, active1 → 3, else 1). The dependency is
  explicit: `limit0`/`limit1`/`duration0`/`duration1` are **per-character asset parameters**
  (`assets[i]->parameters[0,1,4,5]`, `development_animated_combat.hpp:642`) and the port **parses no such table
  today**, so there is no limit to clamp at and no chord threshold to test. Order from here: parse the actor
  parameters and pin Rena+0's values, then implement the accumulation behind the flag and compare, then the +0x834
  spend analysis, then v3.

- 2026-10-16 — pilot agent — **the charge parameter "dependency" is already satisfied, and the mode mapping is
  already documented** — correcting my own previous note: the four special-gauge parameters are the actor DAT's
  six header dwords (`DAT108..11f`), and the port **already parses and exposes them** — `CharacterMoves::parse`
  reads them and `header_values()` returns them (`character_moves.h:98`), with index 3 the weapon id that
  `weapon_id()` already uses, from the same `data/<char>/NN.dat` the combo loader feeds to `moves.parse`
  (`tests/combo_fixture.h:42`). Read independently from the shipped data, **Rena+0 is limit0 = 850, duration0 =
  900, limit1 = 850, duration1 = 900** (header `[850, 900, 0, 1, 850, 900]`). The mode mapping is documented in
  the port as well: `fighter.h:185-191` records the executable's wire numbering (Oyashiro 0, Friendship 1, Kakera
  2) and states that **value 0 fills the victim-side gauge by taking damage** — exactly the adapted **mode 0** rule
  — so the gauge to accumulate is the port's `m_gauge` (hyper gauge 0..1 ↔ 0..1000). That leaves one question
  before code: the recovered rule's `base`/`scale`/`defense`/`modifier` inputs, which the port carries in
  different shapes (`MoveEntry::baseDamage`/`combat[]` at the hit-resolution site and the per-actor multipliers in
  the damage path). Next: pin that mapping, then implement the accumulation behind the flag and compare.

- 2026-10-16 — pilot agent — **two corrections on the charge family, both from the port's own comments** — while
  pinning the accumulation's inputs I found that (a) the port **does** accumulate a gauge from damage
  (`gain_gauge(amount × fillPerDamageDealt)` / `fillPerDamageTaken`, `fighter.cpp:1263-1265`), so my earlier
  "the port never accumulates it from damage" was wrong; and (b) that gauge is the **hypermode bar**
  (`m_gauge`), which the port explicitly keeps separate from the original's mode gauges — `fighter.cpp:1254-1262`
  states that the original's mode gauges are the **+0x838/+0x840/+0x83C** counters ("0..100 counters with their
  own thresholds"), accumulated at `FUN_00637950`'s sites **0x638321/0x6383e6/0x638493** by the record's
  **combat[5]/[6]** columns, and that the port **deliberately leaves those columns unread** ("routing the
  recovered columns into it would report the right number through the wrong system… until the port has the
  mode-gauge accumulators"). Those unread columns are the `gaugeGainA`/`gaugeGainB` aliases in
  `combat_record.h`. So the adapted charge bodies' true target is a **mode-gauge state the port does not have
  yet**, with the original's write sites named by the port itself and the limits (Rena+0: 850/900) already parsed
  from the actor DAT via `header_values()`, and the match's `charge_scale` shipped at 100. My §23 note that the
  gauge to accumulate is `m_gauge` is corrected accordingly. Next: add the mode-gauge counters behind the flag,
  feed them from combat[5]/[6] through the adapted rules, and compare.

- 2026-10-16 — pilot agent — **the mode-gauge state is built on the shipped parameters, with 17 install-backed
  checks** — `src/gameplay/native/rena0_mode_gauges.h` adds the three counters, the two limits and durations from
  the actor DAT's header dwords, the `ready1` latch and the id-5/id-6 notification counters, with `on_hit`
  feeding the adapted bodies from the hit record's columns and writing the results back.
  `tests/rena0_mode_gauge_test.cpp` pins the **shipped parameters** through the parser's own accessor — Rena+0 is
  limit0 850, duration0 900, limit1 850, duration1 900, with the same header block still carrying the weapon id —
  and the state's behaviour: the victim gauge adds `base*scale/133` and clamps at 850 notifying id 5 once, the
  attacker gauge adds `base*scale/90` and clamps at 850 notifying id 6 once, **the modes are exclusive**, mode 2
  accumulates at `/225`, and an active mode 0 blocks further victim accumulation. Three of my first expectations
  were wrong and the body was right: the attacker gauge only accumulates in **mode 1**, so mode 0 correctly leaves
  it at zero — the test now asserts that exclusivity explicitly. The input mapping is named: `victim_charge_base`
  is the record's `combat[5]` and `attacker_charge_base` its `combat[6]` (the port's `hpDamage`/`reflectDamage`
  provisional aliases, deliberately unread per its own comment), scale is the match's `charge_scale` (shipped 100),
  and defense/modifier are the damage chain's factors. Still to do before it drives anything: the live wiring needs
  the attacker's hit record at the contact site, which the port does not expose — so the next step is the smallest
  accessor for `combat[5]`/`combat[6]` on a landed hit, then the comparison on real hits and the consumption side.

- 2026-10-16 — pilot agent — **the mode gauges now run on real hits, with the arithmetic checked** — the
  accessor landed as `Fighter::MeleeChargeBases` (the record's `combat[5]`/`combat[6]`), captured at the single
  place a data-driven hit lands in `try_melee_hit` and zeroed on the legacy swing path (a swing carries no record
  columns); `feed_rena0_mode_gauges` feeds the pilot fighter's own gauges from the hits the frame reports, with
  the limits from its own move table and the mode from its hypermode's wire value. Evidence through the
  fixture-linked differential: `victim-hits=0 attacker-hits=4 charge0=0 charge1=220 notify5=0 notify6=0
  (limits 850/850)` — four landed hits advanced the attacker gauge to **220**, which is 55 per hit from the
  record's `combat[6]` of 50 through `50*100/90` with the adapted body's integer division, while neither gauge
  reached the shipped 850 so neither notified. The victim gauge correctly stayed at zero because the port's
  default mode is **Friendship (wire 1)** and the victim path is mode 0/2 only — a finding worth naming, since
  it means the mode-0 accumulation the port's own comment describes ("fills by taking damage") is off by
  default, which is also why the live guard scenario shows `victim-hits=3` with `charge0=0`. The port has no
  consumer for these gauges (its `gain_gauge` feeds the hypermode bar by design), so this is observation of the
  recovered rules on real hits, not a comparison against port behaviour; the offline test pins the rules and the
  shipped parameters, this pins that they run live. Next: the consumption side (mode 0/1 decrement, mode 2's
  movement and health drain), which needs the consumer decision v3 will carry.

- 2026-10-16 — pilot agent — **the recovered special-gauge control is complete and pinned offline** — `Rena0ModeGauges`
  gained the rest of the recovered control surface: `begin0`/`begin1` (fill from the shipped durations and mark the
  mode active), `begin2` (restores health to the original's 10000), both admission chords (both buttons in 1..2,
  the mode's action window, and the gauge at its limit), `refill_step` (active2 → 2, active0 → 1, active1 → 3,
  else 1) and `tick` (mode 0/1 spend one per tick and end at zero; mode 2 advances the movement gauge to its 1000
  clamp and drains health by 7 a tick, ending itself below 9 by setting health to 1, or below 1). The offline test
  grew from 17 to **44 checks**, still install-backed, so every clamp uses the shipped limits (850/850 with
  durations 900/900 for Rena+0), and a data-free run still exits 77 — a skip, never a pass. Stated plainly in the
  report: nothing in the pilot *activates* a mode, so the consumption path never runs live — it is pinned offline
  and named as unexercised at runtime rather than implied to be covered, and its inputs are the caller's by design
  because this state observes the original's rules and never writes the port's fighters. What remains for the
  charge family is the +0x834 spend-rule analysis and then v3's consumer decision.

- 2026-10-16 — pilot agent — **the +0x834 spend rule is found, and the field's recovery is complete** — the
  owner's second charge item is answered from the **existing addressed research**, with no fresh binary work
  needed. The full rule set for the field: reset to 1000 (`FUN_004219a0:19`); a **+1 per tick** refill
  (`FUN_0041f580:97-98`, `FUN_00508a60:58-59`); the `MoveOp::Recharge` +40/+5 refill already implemented in the
  port (`fighter.cpp:2030-2036`, rows 403/409/469); and the **spend: action 402 (0x192) costs 500**, requiring
  more than 499 (`FUN_00508a60:84-90`), gated on `+0x830 == 4`, a positive gauge, a target-action condition
  (`[[+0xade0]+4] <= [+0xb04]`, or one of 0x27/0x13/0x59 with `FUN_0042c7b0() == 0`) and bit **0x100** of the
  actor's `[[+0x10]+0x28]` word, with the `+0x84` flag and the current action having to be `0x192` first. Action
  402 is a real port row (`move_behavior.h:487-489`, the air tap whose powered case is `case 0x192`), so
  `charge_gauge` is observable: 1000 → spend 500 → a second attempt refused at 500 ≤ 499, which is exactly the
  gate the port already reads (`m_chargeGauge <= 0`, `fighter.cpp:1608`/`:2991`) without ever moving the value.
  The port is also missing the +1/tick refill. Next: implement the spend and the slow refill **behind the flag**,
  then a fixture or scenario watching 1000 → 500 → refused, which is what lets v3 promote `charge_gauge` from
  unsupported to asserted.

- 2026-10-16 — pilot agent — **and the spend lands on the powered tap shot** — following the thread one step
  further: action 402 is the **air tap** (the ground tap binds 400; both are recorded in
  `rena0-tap-shot.fixture`), and its powered case is `case 0x192`, so the 500-gauge spend belongs to the
  **powered tap shot** — the charged projectile attack, which is exactly what the port's `m_chargeGauge <= 0`
  gate guards and why the field is a *shot* gauge. That makes the next step concrete: implement the spend and the
  +1/tick refill behind the flag, then extend the shot scenario or a fixture to perform a powered air tap (402)
  and watch the field move 1000 → 500 → refused at 500 ≤ 499, which is what v3 needs to promote `charge_gauge`
  from unsupported to asserted.

- 2026-10-16 — pilot agent — **the +0x834 spend is implemented behind the flag, and its reachability is
  pinned** — `Fighter::PilotCharge` carries the recovered cost and threshold, and the spend is applied exactly
  where the port's powered branch lives: `case MoveOp::Launch` with `kGatePowered`, attack move **402** and a
  gauge above **499** → `m_chargeGauge -= 500` (`FUN_00508a60:84-90`). The policy is null unless the pilot flag
  attaches it, and the three unchanged scenarios are still byte-identical in capture and deterministic stdout
  with the flag off. The first observation attempt correctly saw nothing: the port's `kGatePowered` is
  `m_hyperActive && Hypermode::Oyashiro && aimHold` (`fighter.h:849-851`) and its own note says Friendship or
  Kakera never takes a powered branch — source behaviour, not a gap — so the pilot's Friendship-mode air taps
  took the normal branch (they threw their items; the enemy lost 27 HP; the pilot's shot observer reported
  nothing because the 402 body is not adapted, the `shot-row-unadapted` class). The scenario that observes the
  spend therefore needs the gauge full, **Oyashiro** selected, an activation and a shooting context with
  `aimHold` — the last of which the fixture runner does not publish yet. Since the fixture vocabulary already
  carries a **`charge_gauge`** observable (`rena0_fixture_test.cpp:107`), the promotion is one `hyper`-setup
  directive away: gauge 1000 → one powered air tap → `charge_gauge 500` → a second → 0. Named, not guessed: the
  `+0x830 == 4` word, the target-action condition and bit 0x100 of `[[+0x10]+0x28]` are not expressible and are
  not applied, and the **+1/tick refill** (`FUN_0041f580:97-98`, `FUN_00508a60:58-59`) is identified but its
  enclosing condition is not, so it is not implemented rather than approximated.

- 2026-10-16 — pilot agent — **the shot gauge's spend is observed and pinned; `charge_gauge` is now assertable** —
  `rena0-charge-spend.fixture` passes and pins the whole recovered interaction: gauge full with Oyashiro active and
  the aim selection armed, a scripted SPECIAL press as the real activation edge, an air tap whose 402 action runs
  its powered launch → **500**, held at 500 while the action runs → back to **1000** by the air recovery's own
  recovered `Recharge` (+40/tick on row 403) → a second tap spends **500** again. Two harness seams made it
  possible and neither bypasses runtime behaviour: a `hyper oyashiro` fixture directive (fills the gauge, selects
  the mode, arms the aim selection) and `Match::cycle_aim_selection`, which reuses the lock's own `cycle_enemy`
  rule because the offline runner cannot press the lock input. Two of my own errors surfaced by running it: the
  spend hook first tested `attack_move_id()`, which is -1 for an air tap because a tap is a **shot** (the recovered
  action id belongs to `shot_move_id()`), and the fixture's first shape expected the second tap to reach zero when
  the port's recovered Recharge refill (+40/tick) restores the cap first. **The significance for v3:** the
  `charge_gauge` field that approved v2 declares **unsupported** is now asserted by a passing fixture, alongside
  the recovered spend, refill and activation gate — promoting it, the two guard-gate fixtures and this one is a v3
  scope decision for the owner, and it stays an unreferenced extra until then.

- 2026-10-16 — pilot agent — **gap 2a closed: the shot body's model request is mapped and driven** — the
  investigation the owner asked for is answered: the body's `model(id, slot)` writes the bundle host's
  per-fighter **held-model pair** (`development_animated_combat.hpp:2542`, initialised and reset to `{0,1}`),
  whose port counterpart is `m_trailItemModel` — initialised `{0,1}` in the same prologue (`fighter.cpp:1816`)
  and **already consumed as a clear**: `itemModel < 0` resets the trail (`:751-755`). Only the writer refused it
  (`MoveOp::PropModel` required `model >= 0`), which is exactly the measured 0/148. The writer now accepts a
  negative model (behaviour-neutral: no shipped row carries one), and the pilot drives the clear behind the flag.
  Driving it took three corrections, each caught by measuring: the hook first tested `attack_move_id()`, which is
  -1 for a shot (the recovered action id belongs to `shot_move_id()`); a one-shot write does not survive because
  the port **re-derives the slots every tick** from the move's trail binding (`:1898-1903`), so the clear became
  part of that derivation behind `Fighter::PilotShot::clears_item_models()`; and the latch reset every frame
  because the pilot block runs once per frame from a function, so it now lives on `App`. Result: the comparison
  went **0/148 → 144/148**, the residual four being a **one-tick lead** (the body clears from its frame 12, the
  port fires on tick 13) — named, not papered over. Stated plainly: the clear has **no visible pixel effect** at
  640x360 in this scenario, so it is verified by state, not by the capture; and the three unchanged scenarios stay
  byte-identical in capture and deterministic stdout with the flag off.

- 2026-10-16 — pilot agent — **gap 3a first pass: the guard's flag words are data, not buttons** — the owner's
  requested binary analysis was scoped and partly answered from the bundle's own pipeline, in three cited hops:
  `battle_hit_pipeline.hpp:23` passes `input.stagger.flags` as the predicate's `victim_flags` and
  `input.attack_flags` as its `attack_flags`; `actor_frame_hit.hpp:8` sets the latter from the attacker's hit
  record word at **+0x2c** — which the port **already parses** as `MoveEntry::attackFlags`, so the unblockable
  term needs no proxy; and `development_animated_combat.hpp:3922` sets the former from
  **`live_body_contact_frame(v).flags28`**, the victim's live body frame word at +0x28, where 0x400/0x2000/0x8000
  live. So the victim's term is a per-frame *data* word, which is exactly why the port's Guard-state proxy was a
  stand-in and not the same thing. Binary work (pinned `sha256 27e61475…`, Evidence saved under
  `local-data/harness/`): masked byte searches found no immediate-OR write to the +0x28 word with those masks, 31
  stores to +0x28 and 24 to +0x2c overall, and the one function writing both (`FUN_00427f40`) is a **record copy
  constructor** (`memcpy` of +0x28..+0x3c), consistent with copied data rather than computed flags; its callers
  (`0x427f1b`/`0x428017`/`0x42822b` in `FUN_00427fe0`) drive a table-iteration copy. **Remaining question, named:**
  where the port's parsed data carries the victim's live body contact frame and its `flags28` — the port's
  `MoveEntry` flags are at record offsets 0x82/0x86 (the hit record) and must not be conflated with the live body
  frame the guard reads, though `rena_dash_admission.h:13` already refers to "current NN record flags28 & 0x100",
  so the notion exists somewhere. Locating that source is the next bounded step and would let the predicate drop
  the proxy entirely.

- 2026-10-16 — pilot agent — **gap 3a closed: the guard's flag words are the live records' words, and the
  proxy can go** — the question left open in the previous pass is answered from the shipped data, with a new
  install-backed check. `CharacterMove::phases[].record_at(elapsed)` is the port's **live frame record** for the
  current tick — exactly the bundle's `live_body_contact_frame(v)` — and its `MoveEntry::stateFlags`/`attackFlags`
  are the two words `FUN_00637950`'s predicate reads. `rena0_guard_flags_test` walks every record of Rena+0 and
  reports: **276 records; `0x400` in 6, first row 390; bit 8 in 8, first row 350; `0x2000` and `0x8000` in none**.
  The row identity is what makes it decisive rather than suggestive — the first `0x400` record is **row 390**, the
  guard row whose body this pilot already adapted (390/391/392), and the first bit-8 record is row 350, an attack
  row. And the two terms the pilot had recorded as "not expressible" are in fact **expressible but unused by this
  combo**: they appear zero times in Rena+0's records. The predicate therefore becomes
  `(|relative| <= 45° || victimRecord->stateFlags & 0x2000) && (victimRecord->stateFlags & 0x400) &&
  !(attackerRecord->attackFlags & 8)` — no proxy, all three terms, no new parsing. Implementing that (and promoting
  the guard fixtures) is the next step and a v3 item.

- 2026-10-16 — pilot agent — **gap 3a implemented: the guard predicate reads the recovered records, and the proxy is
  gone** — `Rena0PilotGuard::guards_hit` now reads the victim's and attacker's live frame records
  (`current_move_record()`, the same accessor the port's dash admission already uses for the flags28 word) and applies
  the recovered predicate verbatim: `(|relative| <= 45° || victimRecord->stateFlags & 0x2000) &&
  (victimRecord->stateFlags & 0x400) && !(attackRecord->attackFlags & 8)`. All three terms are expressed, and the
  diagnostics name every refusal (`no-record`, `not-guard-capable`, `unblockable`, `outside-angle`) so a silent gate
  is impossible. One honest bridge was needed and is named: the port's Guard state binds no clip or phase
  (`state_move_id()` returns -1 for Guard, per its own note), so a human fighter guarding has no live record —
  running it that way first **broke the guard fixtures** (99 instead of 100 HP), which is exactly what measurement
  is for: the predicate was right and the port had nothing to hand it. `Fighter::PilotGuardMotion` lets the pilot
  supply the recovered guard row's guard-capable record (`Rena0GuardRecord`, row 390 — the standing guard whose body
  this pilot already adapted), with the victim's own live record preferred whenever the port binds one; the guard's
  animation granularity stays the named limit it was. Evidence after the change: the pilot guard-gate fixture passes
  with `asked=1 guarded=1 no-record=0` (100 HP), the legacy fixture still pins 99, the live scenario reports
  `asked=3 guarded=2 no-record=0 not-guard-capable=1` with P1 at **92 HP** (0+0+8), the flag-off comparison differs
  only in the HP fields (90 → 92) while locomotion, melee and shot stay byte-identical in capture and deterministic
  stdout, and the suite is **82 tests, 0 failures** with the differential at 357 in-domain ticks and no unexplained
  divergence. A stale-binary trap bit twice during this work (a failed build left the previous binary in place and
  briefly made the fixtures look green); the counters printed per fixture are what exposed it.

- 2026-10-16 — pilot agent — **2f repeated against the current evidence, with the v3-dependent parts labelled** —
  `PILOT-SEAM.md` §24 is the repeat the owner asked for, run against the approved v2 matrix plus everything closed
  since the first 2f. The matrix passes with 23 fixtures / 21 case rows / 39 acceptance fields / 7 unsupported
  declared / **3 unreferenced extras**, and those three extras (the two guard-gate fixtures and the charge-spend
  fixture) are explicitly **v3-dependent** — under v2 they are not acceptance cases. Offline bodies are green
  (locomotion 53, admission 24, shot 36, guard 26, charge 29, mode gauges 44, guard flags 4, resolver 48), the
  differential covers **357 in-domain ticks** with no unexplained divergence, and the four live comparisons agree
  everywhere they are in domain: locomotion 200/200, melee 33/33, shot 99/99, guard 62/62, with the mode gauges
  reporting `charge1=220` from four landed hits, the guard predicate `asked=3 guarded=2 no-record=0
  not-guard-capable=1`, and the shot model comparison at 144/148. Rollback is unchanged in shape: locomotion,
  melee and shot are byte-identical in capture and deterministic stdout with the flag off, and the guard scenario
  differs only in the HP fields (90 → 92) — now produced by the data-backed predicate instead of a state proxy.
  Provenance is tabulated per claim and the unresolved limits are named individually. The repeat claims neither
  acceptance (0/46; the three new cases and the `charge_gauge` promotion need the **proposed v3** approved) nor
  original-runtime parity, and it leaves the verdict with the owner, freeze list A in force and no cleanup started.

- 2026-10-15 — coordinator — **Rena+0 bundle navigation map added at the owner's request** —
  [`RENA0-SOURCE-MAP.md`](RENA0-SOURCE-MAP.md) inventories the 13 Rena-named source files,
  the 22 other files with literal Rena mentions, explicit weapon-0 selectors, generated
  `0_0` bodies, and static entry/admission/action/projectile call routes. It marks
  text-search false positives and conditional dispatch, and lists questions for the
  owner's next reviewing agent. This was source-only inspection: no bundle or
  product code changed, no binary/game run, no acceptance or parity claim.

- 2026-10-15 — coordinator — **Rena+0 source reconnaissance and adapter mocks** —
  two bounded read-only reviews checked the bundle's actual dispatch order and
  asset/projectile route. [`RENA0-SOURCE-MAP.md`](RENA0-SOURCE-MAP.md) now records
  the slot-7 early return, native/generated body precedence, the corrected
  slot-7 dispatch line, production DAT-derived mobile resources (the helper
  defaults are unused), and the separate shot-attempt, admission, spawn and
  contact stages. A further bounded read of `slot7_body_0_0` mapped its broad
  admission groups and synchronous `N`/`R`/`A`/`V`/`v`/`P` services, while leaving
  per-branch field and DAT reachability open. [`RENA0-ADAPTER-MOCKS.md`](RENA0-ADAPTER-MOCKS.md)
  gives four non-compiling pilot-only shapes: slot-7 admission, a narrow action
  proposal, a synchronous State-400 shot host, and a bounded charge/socket world view, each with
  explicit gates. Source-only inspection; no bundle or product source edit,
  runtime execution, contract change, acceptance or parity claim. Next:
  count slot-7 fields per branch and verify DAT-backed reachability before
  choosing any implementation shape.

- 2026-10-15 — coordinator — **Rena+0 slot-7 source/data census completed** —
  [`RENA0-SLOT7-AUDIT.md`](RENA0-SLOT7-AUDIT.md) records 61 direct body-word
  indexes (29 destination-priority constants), five byte-read offsets, six
  synchronous world-service kinds, and the fields still needing port semantics.
  Read-only hashes matched the required original EXE and pinned Rena+0 actor/
  item DATs; the existing parser consumed both files. All **33 literal state
  requests** in `slot7_body_0_0` have Rena+0 DAT rows, with priority pairs and
  phase set sequences recorded; item 001 has two magazines and 18 bullet rows.
  A repeatable assertion script passed (`actor rows=122; targets=33;
  missing=0; bullets=18`). The source map and adapter mocks now point to this
  audit. No game run, source-code change, original-runtime parity or pilot
  acceptance claim. Next: one complete-context offline slot-7 branch fixture
  with an intentionally wrong gate, then map only the fields/services that
  branch proves necessary.

- 2026-10-15 — coordinator — **two bounded Rena+0 slot-7 branches executed offline** —
  the ignored `local-data/harness/rena0_slot7_body_probe.cpp` compiled the
  bundle's actual generated body and asserted idle→dash 20 with frame flag
  `0x100`, refusal when that flag is zero, idle→shot 400 with six primary
  rounds, and an empty-magazine refusal that emits one voice and increments
  the empty-shot statistic. The build and probe exited 0; exact command,
  source hash, fixture values and output are recorded in
  [`RENA0-SLOT7-AUDIT.md`](RENA0-SLOT7-AUDIT.md). Services were stubbed and no
  integrated or original-runtime execution occurred. Next: map one tested
  branch to the port's input/priority/binding owners and compare it in the
  real `Match`/`Fighter` path; keep pool birth/contact distinct from slot-7
  admission.

- 2026-10-15 — coordinator — **Rena+0 slot-7 branch-to-port mapping refined** —
  the local body probe now also asserts that a zero `+0x834` gauge refuses
  idle→dash 20; it still passes the frame-flag, shot-400 and empty-magazine
  cases (`RENA0-SLOT7-AUDIT.md`, updated source hash and output). Static port
  review mapped row priority A/B to `CharacterMove::priority`/
  `cancelThreshold`, and identified two **candidate**, unverified gate
  differences: the programmed dash checks port stamina rather than the
  source body's fighter gauge, and an empty tap returns before the source
  body's voice/statistic requests. The adapter mock now exposes these
  channels. No port scenario has demonstrated a gameplay failure; no
  runtime code or approved contract was changed. Next: make a bounded
  equipped Rena+0 port scenario for one candidate and compare its admission,
  effects and flag-off path against the body fixture before considering a fix.

- 2026-10-15 — coordinator with two GPT-6 Luna read-only agents — **two
  equipped Rena+0 discrepancies reproduced** — separate, freshly built local
  `Match`/`Fighter` probes loaded real `00.dat`, item 001 and rig `00.x`, stepped
  normal startup, and kept the pilot policy detached. The zero-gauge Up,
  release, Up scenario entered dash row 20/set 13 at its second press while
  the generated slot-7 body refused its matching command-1/gauge-0 branch;
  the bundle's own dash-history helper confirmed that input produces command
  1. Six funded taps reduced the real main stock to zero, and a seventh tap
  produced no row, projectile or voice; the generated slot-7 body emits a
  voice and increments its empty-shot statistic for release count 1/rounds 0.
  The bundle input helper confirmed a one-tick press/release produces that
  count. Exact source/output hashes, commands, tick values, pool-capacity
  separation and limits are in [`RENA0-SLOT7-AUDIT.md`](RENA0-SLOT7-AUDIT.md).
  Both probes exited 0; dash repeats within the probe and the updated empty
  outputs compare byte-identically. These are tier-4 port observations versus
  source-backed body outcomes, **not** original-runtime parity. The port
  exposes no corresponding empty-shot statistic, so only its missing voice
  is an observed difference there. No product source or approved contract
  changed. Next: choose a Rena+0 pilot-flag admission/service seam and test
  its corrections against these exact scenarios while preserving flag-off.

- 2026-10-15 — coordinator — **slot-7 mock refined around observed refusals** —
  [`RENA0-ADAPTER-MOCKS.md`](RENA0-ADAPTER-MOCKS.md) now distinguishes an
  unsupported pilot branch, a handled input with no state transition, and a
  requested state. The two named scenarios require that distinction: a
  source refusal at zero gauge must not fall through to the old dash selector,
  and an empty tap must service its voice/statistic without entering shot 400.
  This is design-only; no runtime or contract code changed. Next: implement
  only a bounded flagged Rena+0 seam after mapping its required fields and
  check both scenarios plus flag-off restoration.

- 2026-10-15 — coordinator with three GPT-6 Luna read-only agents — **Rena+0
  source-map completeness pass** — [`RENA0-SOURCE-MAP.md`](RENA0-SOURCE-MAP.md)
  now separates the 122 installed actor DAT rows by state family and lists
  the shared action, hit/reaction, death, guard, asset, prop, voice, projectile
  and peripheral routes missed by a name search. A conservative include
  closure from the combat integrator reaches 343 local files but is explicitly
  not execution coverage. Of 65 reaction-range DAT rows, 39 have the common
  hit predicate, nine the death range, four shared-recovery bodies and 13 no
  dedicated case/entry established in the targeted pass; generic fallback can
  animate a state already active. The map names unproven entries for Rena+0
  rows 11/12, 303, 351, guard 393/394 and shot 404, without declaring them
  unreachable. CPU/camera/result/network references are navigation only and
  do not expand the pilot. This was source/DAT inspection only; no body/port
  test, original run, contract change, other-combo work or acceptance claim.
  Next: resolve only the unproven rows or services that block an approved
  Rena+0 pilot case; retain the others as explicit inventory limits.

- 2026-10-15 — pilot agent with four GPT-6 Luna read-only bundle agents — **the two slot-7
  refusals now have a pilot path, and the required case is mapped field by field** —
  Reproductions first: the dash probe and the empty-shot probe were rebuilt against current
  `foundation_gameplay` and are **byte-identical** to their recorded logs (`0cec45e2…`, `7c219504…`),
  and the compiled body probe still passes. New: [`PILOT-SEAM.md`](PILOT-SEAM.md) §25 maps the
  **grounded forward dash admission** end to end — actor/item identity, the input history →
  `+0x830` command word, the four compared DAT words (read from the pinned install: row 0 A/B 0/0,
  row 20 A/B 0/5, row 400 A 40, phase-0 `flags28` 0x100, row 20 phase-0 set 13), the one `N`
  service the branch uses, and the port owner of every field. Two long-standing documentation
  questions were closed on the way: `slot7_body_0_0` **is** the recovered `FUN_00445ee0` for
  Rena+0 (line-for-line against `research/decompiled/FUN_00445ee0.c:12-70`), and the dash **drains
  the charge gauge, not stamina** (12/tick with a gauge-0 phase exit,
  `dash_native_bodies_20260929.hpp:53,180,290,387`; air 11+3 at `:554,572`) — a named finding that
  this increment does **not** implement. §26 does the same for the empty-magazine tap, including
  the wrapper (`slot7_body_0_0:172`) whose `+0x834 < 1` term is why the port's existing gauge gate
  does not cover it, and why the branch has no `return`: a voice and a statistic, no state, no
  magazine write, no projectile. §27 records the implementation: `PilotCharge::dash_gauge_refuses`
  and `PilotShot::empty_shot_voice`, each consulted once at the port's existing decision point
  (`try_dash`'s `programmed` arm, `fire_shot`'s empty branch), flag-on only — nothing decided
  twice per tick, and with no policy attached neither block runs. The empty-shot statistic
  `+0xaf4c` has no port owner and was **not** invented as a `Fighter` field. In parallel, three
  read-only agents produced the state-ownership census now merged into
  [`RENA0-SOURCE-MAP.md`](RENA0-SOURCE-MAP.md): for Rena+0 with item 001 the generated slot-7 body
  is the **only** live admission owner (`development_animated_combat.hpp:1690-1693` skips the whole
  hand-written fallback block), rows **11/12, 303, 393, 394** have no owner found at all, **351**
  and **404** are handler-only, and the flagged reaction rows split into DAT-driven entries
  (`battle_hit_stagger.hpp:16-18` — the attacker's frame fields `0x64`/`0x68`) versus rows with no
  handler either (117, 122-123, 125-127, 129, 132, 232 → the generic reaction tick). Evidence for
  the new work, kept separate: **builds** — `build/linux` clean, `rena0_pilot_gate_test` built and
  registered; **tests** — `ctest` **83/83 passed, 0 skipped** (was 82; +1 suite), the new test's own
  3 runs byte-identical, and the offline fixture passes with 3 byte-identical runs; **seeded
  failures (intended, not passes)** — `rena0_pilot_gate_test --seed-wrong-gate` exit 1 at the
  refusal assertion and `rena0_slot7_gate_probe --seed-wrong-gate` exit 1
  (`gauge-positive command-1 dash must request state 20`); **flag-off control asserted inside the
  new test** — gauge 0 still enters row 20/set 13 with stamina 98 and the empty tap is still
  silent; **scripted port runs** — `melee-ground-300`, `locomotion-walk-turn` and `shot-ground-400`
  under flag-off vs `--native-actions=rena0` (260 frames, `--headless --out`) are **capture
  byte-identical** with only the capture path and wall-clock timing differing in stdout, and the
  pilot drive reports 200/200, 33/33 and 99/99 with 0 disagreements. Limitations, stated: tier 2 +
  tier 4 only, no original-runtime parity for either refusal; the command word `+0x830` stays a
  named stand-in for the port's 0.30 s double-tap window; the dash drain and the empty-shot
  statistic are mapped but not implemented; the new test is an addition to the 2e comparison set,
  not an acceptance case (adding it to the contract is a **v3** decision). Acceptance stays
  **0/46**, the verdict stays the owner's, freeze list A stands and no cleanup started. Next: 2f
  repeated against this evidence, or the owner's review of the proposed v3.

- Night session 2026-10-29 (branch `overnight`) — **V3-34 through V3-42: card animation, the EX camera's real value, and three limits retired.** All work is pilot-scope (Rena+0), nothing merged, nothing pushed. Full suite 83/83 excluding the known `device_isolation_test` flake; fixtures 30 / 31 case rows / 49 fields.
  - **V3-34 card animation.** Live effect cards now play their own clip at `age * 0.016` (`FUN_00436150`), sampled through a fresh controller per card, instead of standing in bind pose. The clock's edges are pinned in `fx_cards_test`; `--no-fx-anim` is the rollback switch and is documented in `usage()`.
  - **V3-35 — the "ring" is a bullet model, not `data/effect/01.X`.** The nata's glow is `data/bullet/001/03.X` mesh 1..2 and the ring is `data/bullet/001/06.X`; nothing loads the file V3-33 named. V3-33 is marked superseded.
  - **V3-36/V3-38 per-mesh pass for shots.** A quad mesh inside a shot model draws additively, everything else keeps the record's `+0x7c` mapping. Swept against **all 351 shipped shot models** (155 quads, no counter-example); `effect_catalog_test` now asserts the premise so an asset that breaks it fails instead of rendering wrong quietly. The rule flips 17 quads in 10 models, and the under-inclusive half (non-quad black-backed cards) is recorded rather than implied.
  - **V3-39 depth.** `+0x7c` cases 2/4 draw with `ZENABLE = 0` and restore it (`FUN_005f60b0:84-89`, `:100-109`); that is now a depthless additive pass sorted last, keyed on the record's own value.
  - **V3-37 — the EX action camera is set 0, and the tier-3 answer of 5 was wrong.** `FUN_0043ffc0` case `0x15e` writes the actor's `+0x684` itself (`:1437-1442`): set **0** for the whole move, set **1** from tick `0x33` only when the late hit latch `+0xe8` is armed. No instruction in row 350 writes 5. The port's `0`-as-"off" sentinel made the recovered value unrepresentable and is why the eye picked the nearest visible set; the sentinel is negative now (matching the original's `< 0` test) and set 0 plays.
  - **V3-40 guard row 390: specified, not shipped.** The release is a *phase* (`FUN_00421100(2)` → set 63, state stays `0x186`), the drain is phase-1 only, and there are five exits. Implementing it turned a validated guard into a 20-tick lock-out because the port has no cancellation rule for that window and the original's admission gate is not established, so the change was reverted and the limit is now precisely specified instead of vague.
  - **V3-41 two camera limits closed.** `[cam+0x78]` is a float distance of 300.0 (one store, two reads; the port already hardcodes it) and the ally anchor branch is unreachable in a different-team 1v1, so it is not a pilot gap. The opposite offsets were settled from the disassembly (`+0x300` indexes the other-team list at `+0x2e0`, `+0x304` the same-team one at `+0x2f0`); a relabel of the port's lock field was attempted and **reverted**, because six paragraphs of recovered notes in `target_lock.h` are built on the old naming — the field's note and V3-41 carry the address table instead.
  - **V3-42 the air dash's fall.** A dash that ends airborne enters the original's state 43 — move 43, set 43 — not the jump chain's row 42 whose first section is set 5; the port played 32 frames of the wrong clip and now plays set 43 from the first post-dash update, with the row-41 hover suppressed. The fixture pins it and fails with `anim_set exp 43 got 5` without the change. State 44 (the shared 22-frame landing row) is implemented too — it plays for the row's own derived length (22 frames for Rena+0), and closing it clears the bound set *and* the row clock, which the first cut missed.
  - Owner items still outstanding and unchanged: the `EXCEPTIONS.md` rows for frozen-file edits, the 2g verdict, and any push decision.


- Late addition to the overnight session — **the Hyper EX deals damage again (V3-43).** The port cut row 350's melee contact for the whole move, on the reading that the body's tick-0 `FUN_00434bd0` call removed the hit volume. That reading was wrong: at `0x4433f4` the body does `add ecx,0x6a0` before the call, so it operates on the actor's **trail** object, while the hit path reads the contact record pointer `char+0x10` (maintained by `FUN_004212f0`), transforms its anchors through `FUN_00420880` and resolves them in `FUN_00637950` (HP subtraction at `0x638a96`). Row 350's data carries seven one-tick hand contacts (radius 30) and one right-hand contact at frame 57, which is what the body preps with `FUN_0042c800(0)`/`FUN_0042c840(1)`. The rule is deleted; the EX now lands for the standard 8 damage (100 → 92 HP) and, because it can hit, the late camera switch V3-37 recovered (set 1 past the move's clock tick `0x33`) is reachable too. `melee_admission_test` previously asserted the wrong rule and now asserts the program carries no contact cut for row 350; `rena0_pilot_gate_test` asserts the hit and both camera paths. Suite 83/83 excluding the known `device_isolation_test` flake; fixtures 30 / 31 / 49 unaffected.

- 2026-10-29 — frame-data audit (this session) — **contact-window coverage for every reachable Rena+0 melee row, and the charge-ordering defect the air second charge exposed.** New install-backed tests in `melee_rules_test` drive real inputs and assert that each row's first contact lands exactly on the first record-active tick and plays that record's reaction row (302/341 also launch): 300, the 300→301→302 chain, 310, 311, 320, 330, 331, 332, the 340/341 landing chain, and the Hyper EX 350 (all eight shipped hand records become the live volume; reaction 130). Building the 370 test exposed a proven divergence: `FUN_00445ee0:17-19` asserts the shot charge **before** any action branch, but the port charged only inside its shoot block, so a Jump/melee/dash/guard tick skipped one assertion and `ShootingMagazine::tick` reset the whole charge. In the port that made the airborne second charge unreachable (the 72-update fly budget against the 210-update Red hold); the charge is now asserted at the top of the update for a live fighter holding Shoot/Special under the same hyper rule, and the existing flight test's "charge is re-lost for one tick" expectation was corrected to "the charge survives the leap". Row 370 is covered: Red survives the jump, binds 370, and launches rows 11/12 on phase-2 frame 2. Suite 84/84 excluding `device_isolation_test`; fixtures 30/31/49; `melee_rules_test` 398 checks; `fighter_script_test` green. Remaining: row 351 (handler-only), projectile rows 4/6/7/9/13/14 and the row-2→3 child, and no tier-1 runtime. Nothing committed.

- 2026-10-29 — frame-data audit (follow-up) — **the unpowered stage explosion is now covered, and the remaining projectile gap is recorded as Q25.** `fighter_script_test` gained a row-2 test (item parameter 20) that drives the real charge into the stage wall and verifies the child row 3: spawn position/clock, the 0..9 record window closing at age 10, and one 15-damage contact. The audit's row-2→3 item is therefore closed. The six remaining projectile parameters (rows 4/6/7/9/13/14) still have no recovered behavior and fall back to the provisional tier tuning; extending that frozen table needs the owner's scoped exception requested in Q25, with a TODO in `projectile_behavior.h`. Suite 84/84 excluding `device_isolation_test`; fixtures 30/31/49; `fighter_script_test` green. Nothing committed.

- 2026-10-29 — frame-data audit (Q25) — **the six remaining projectile parameters are registered from `FUN_005f91c0`.** The model gained `initialYaw` (the `+0x30` offset, in degrees, added at spawn) and `turnGrow` (a growing degree step, capped by `turnCounter`); the existing entries leave both at zero, so their behaviour is unchanged. Rows 4/9 (speed 30), 13/14 (speed 25), all lifetime 480 and yaw ±45/±60, and rows 6/7 (speed 45, lifetime 240, step `0.25+0.01*min(120,tick+1)`) now carry wall child 5 and their recovered motion; `animation_data_test` asserts per-row speed, launch yaw, wall child and row 6's lifetime boundary. Named approximations kept in the header: 0x3c's `+0x34` vertical 20, the sub-degree inner steering, `FUN_0042dac0` aim jitter and the 0xf/0x10 particles. Suite 84/84 excluding `device_isolation_test`; fixtures 30/31/49; `animation_data_test` 83,605 checks. Nothing committed.

- 2026-10-29 — frame-data audit (coverage close) — **every attack row in the pilot scope now has an install-backed test, and the two handler-only rows are pinned.** Added: the walking/dash tap routes (401, 405, 406, 408) each bind their state and fire the normal row-0 request on frame 12; the back-dash route (407) fires the row-4/row-9 pair at fixed ±75° on phase-0 frame 13; and a sweep of `rena_melee_admission` (3 weapons × 21 states × 3 phases × 81 axis/flag/grounded combinations) plus `rena_tap_shot_state` (3 weapons × 51 states) proves no input selects handler-only rows 351 or 404. The 407 test also exercises the Q25 projectile behaviors end to end. Suite 84/84 excluding `device_isolation_test`; fixtures 30/31/49; `melee_rules_test` 436 checks. Nothing committed.

- 2026-10-29 — frame-data audit (correction) — **row 205's slide follows `FUN_00428510` case 0xcd, not case 0x69 with a flipped sign.** Case 0xcd seeds `+combat[18]*0.01` and decays `+0x54 > 4 -> -0.25`, so the port now gives 205 its 0.25 settle and +4 floor; the delayed-row test's "205 holds its seed / travels 35" expectation was the Q24 implementation's assumption, not the recovered law, and now reads 0.25 / 29.5 like 105. Case 0xd8 (216) is the one +100 row whose handler negates `combat[18]`, which is why 216 keeps the front sign in the seed rule. Suite 84/84; fixtures 30/31/49; `melee_rules_test` 436 checks. Nothing committed.

- 2026-10-29 — owner-requested input/pause change (play-test ergonomics) — **losing focus no longer pauses the battle, the device-isolation switch is gone, and an unfocused window simply ignores input.** `--devices`/`--no-devices` and the verification-run device gate were removed (`Options`, `readPhysicalDevices`, `Backend::set_devices_enabled`); `--match` now reads the keyboard/pads with no extra flag. Focus loss still drops held keys and the backend still ignores devices while unfocused (pinned by `input_backend_test`). The device-isolation regression test was deleted with the instrument, `pin_viewpoint.py`/`showcase.py`/`capture_probe.py` no longer pass the flag, and `INPUT-BACKEND.md`/`RELEASE-CHECKLIST.md`/`RELEASE-LINUX.md`/`SPLIT-SCREEN.md`/`ROADMAP-PENDING.md`/`BUILD-windows.md`/`LIVE-DEBUG.md` were updated. Suite 84/84 excluding nothing (the isolation test is gone). Nothing committed.

- 2026-10-29 — knockdown/tech research (owner-reported gap) — **the shared ground-recovery system is mapped, and the port has only its first two states.** Report: [`reports/knockdown-getup-2026-10-29.md`](reports/knockdown-getup-2026-10-29.md). Tier-2 reads of `FUN_00428510` (cases 0x2d/0x67/0x74/0x76/0x77/0x78/0x79/0x7c/0x80, plus the +100 mirrors), `FUN_0041f580`, `FUN_004236c0`/`FUN_00423700` and `FUN_00637950` establish: landing tech row 45 when a front air-hit (113..116) touches down with Jump held and `+0x7c0 < 100`; row 45 clears the down/stagger/hit meters and hops back (speed -25, vertical 12.5, gravity 1.0 to frame 26); 118/119 complete into 120; 120 completes into 124 (directional roll, speed 10, cancel after 30 frames) or 128 (in place) by the stick axes at `+0x278/+0x27c`; states 124..129 and 194 refresh `+0x7ac = 30` every tick (get-up invincibility) while `FUN_004236c0` gates the decrement; `+0x7c0` accumulates combat[8] with a 120-tick window and grants 30 i-frames at >=100; a record flag 0x800 selects the 121 ground roll with 0.7 damage. Tier 3 fills 103/203/121/133/134 and still needs a binary read. The tier-3 helper that lists only 113..115 was overruled by cases 0x71..0x74 (all four front rows tech; the back rows do not). The port has 118/119 -> 120 -> Idle only, with no 45, 124/128, i-frames or down-meter semantics; this is why the "Rena+0 is perfect" claim cannot be made yet. Implementation scope requested in Q26. Nothing committed.

- 2026-10-29 — knockdown/tech implementation, stage 1 — **the get-up chain is row-completion driven and the 124/128 choice plus get-up invincibility are live.** Replaced the port-only `m_stateTimer` chain with `advance_animation_phase` completion (FUN_004218c0): 118/119 complete into 120, 120's completion reads the stick axes (`+0x278/+0x27c`) and binds 124 (held) or 128 (neutral), 124's gated phase 1 cancels into phase 2 after 30 frames once the player acts (case 0x7c), and both end in Idle. Added `m_invincible` (+0x7ac): refreshed to 30 every tick while 124..129 plays, decaying outside the reaction range and while hitstop holds; `try_melee_hit` and the projectile path now reject an invincible victim (FUN_00637950's `+0x7ac < 1`). `downPhase` removed. Regression `test_knockdown_getup_chain` covers the chain, both choices, the 30-tick value and a rejected swing against the same swing after decay. Suite 84/84; fixtures 30/31/49. Stages 2-4 (45 tech, down meter, 103/133/121) remain under the Q26 goal. Nothing committed.

- 2026-10-29 — knockdown/tech implementation, stages 2-3 — **the landing tech roll and the down meter are live.** Stage 2: a front air hit (113..116) that lands with Jump held and `+0x7c0 < 100` now binds row 45 (case 0x74) instead of 118/119; the bind clears the stagger/combo meters and `+0x7ac`, row 45 runs speed -25, vertical 12.5, gravity 1.0 with the -10 speed floor until frame 26 (case 0x2d) and completes into Idle; back rows (0xd5..0xd8) keep 119. Stage 3: the down meter `+0x7c0` accumulates combat[8] on a trip, keeps its 120-tick memory only outside the reaction band (matching FUN_0041f580/FUN_004236c0), grants 30 i-frames at 100 and selects the heavy row; the stagger decoder stays per-tick. Tests: `test_landing_tech_roll` and `test_down_meter_semantics`. Stage 4 (103/203, 121 flag 0x800, 133) and 124's steering remain. Suite 84/84; fixtures 30/31/49; `melee_rules_test` 469 checks. Nothing committed.

- 2026-10-29 — knockdown/tech implementation, stage 4 — **the 0x800 ground roll is implemented and the remaining shared extras are proven unreachable for Rena+0.** `HitReaction` now carries the record state flags (+0x28); flag 0x800 overrides the reaction row with 121 (221 from behind), scales the blow to 70% before the HP math, and its completion enters the 120 get-up (case 0x79). The melee and projectile records both fill the field. A scan of every shipped Rena+0 move entry (`test_shared_recovery_reachability`) asserts **zero** records with the 0x800 flag and zero records naming 121/133/103 as a reaction, so the 121 path is latent (injection-tested) and 103/203 + 133 have no requester and no port path; they stay documented limits instead of untestable code. 124's steering and the 45/133/death-row details remain named. Suite 84/84; fixtures 30/31/49; `melee_rules_test` 477 checks. Nothing committed.

- 2026-10-30 — knockdown/tech correction (owner-approved after review) — **row 124 no longer locks, and its body follows case 0x7c.** A scratch probe showed a neutral victim held in 124 with `+0x7ac = 30` for 3,600 ticks; the stage 1 test never released the stick. Fixed: the 150-tick exit, the button-only 30-tick cancel (`param_1[0xa0..0xa2]` are the input counters, not hitstop), stick steering, speed 10 and the +40/+5 meter refill; 120's choice now uses the held axes; row 45 zeroes vertical from frame 26, holds frame 25 while airborne and stops without drift; shots skip an invincible victim before contact work (`FUN_00637950:74`). New checks failed first (14 failures across `melee_rules_test` and `animation_data_test`). A scan found rows 45/120/124/128 on all 46 combos, with 124 carrying at least three sections. Tier 2 expectations, tier 4 tests, no original runtime. Named limit: airborne 124/128 -> 43. Report: [`reports/knockdown-getup-2026-10-29.md`](reports/knockdown-getup-2026-10-29.md) §5. Nothing committed.

- 2026-10-30 — reference-core feasibility (owner-requested reuse review) — **the reference simulation runs headless on Linux, and a new plan is proposed.** The closure of `local_normal_projectiles.hpp` is 423 files / 283,754 lines with only `xmmintrin.h` and `zlib.h` as external headers. All seven body modules and a CPU-versus-CPU harness built with g++ and clang after forcing `<cstring>`, `<climits>`, `<set>` and `<cstdint>`; the bundle stayed unchanged. All 46 combos ran 2,400 ticks without an exception, and one fixed match gave the same hash on repeat, with `-O1`, `-O2` and clang. It also linked beside `foundation_gameplay`, and all 78 Rena+0 port frame names exist among the core's 79 bones. This shows the code runs, not that it matches the original: tier 5, no original runtime. Proposal: [`reports/reference-core-plan-2026-10-30.md`](reports/reference-core-plan-2026-10-30.md). Spike sources: ignored `local-data/harness/reference-core-spike/`. Nothing committed.

- 2026-10-30 — M1 — **the owner approved the reference-core plan, and the core now builds inside the foundation.** `DIRECTION.md` was rewritten and `AGENTS.md`, `SCOREBOARD.md` and `QUESTIONS.md` aligned. `src/sim/core/` holds 437 vendored files (284,160 lines) byte-identical to the bundle per `MANIFEST.sha256`, with `PATCHES.md` still empty, plus the inflate subset of zlib. `sim::Battle` is the only includer and follows `RuntimeBattle`'s setup and update order; it adds the voice inventory and the victory and award draws, because all of them consume the battle RNG (the earlier spike omitted them, so its hashes are not comparable). `simctl` runs any roster and script and writes JSONL traces. `sim_core_test` (110 checks, 23 s) covers 46/46 combos for 1,200 ticks, repeatable digests, seed and one-tick input sensitivity, scripted Rena+0 rows 300/400/40 and rejected invalid combos. Full suite 85/85. Native host only; the legacy path is still the product and nothing in the game uses the core yet. Execution evidence only, no original-behaviour claim. Not committed.

- 2026-10-30 — M2 — **the core agrees with every available original-derived record, and random input found one real defect.** `simfuzz` ran 9.9M ticks over 46 combos with no process crash and no invariant failure; its first run threw in matches with Ohishi+2, and the disassembly of the pinned binary showed the throw was the core's guard, not the original's behaviour, so `legacy_trig.hpp` now follows `_ftol2` (first entry in `PATCHES.md`). `sim_oracle_test` matches 50,056/50,056 recorded answers of the original under emulation, with negative controls. Coverage is 55% of declared rows, and Rena's own hand-written shots are not compared. Report: [`reports/m2-trust-2026-10-30.md`](reports/m2-trust-2026-10-30.md). Not committed.

- 2026-10-30 — M3 — **the product now reads a battle through `game::BattleView`.** `src/game/battle_view.h` declares the fighter and battle read surface plus the commands the product sends, `src/game/battle_types.h` takes the plain data (`FighterState`, `ShotTier`, `BattleFrame` and others) out of the legacy headers, and `gameplay::LegacyBattle` implements it over `Match`. `main.cpp` reaches `Match` at 12 named seams only: setup 5, debug keys 1, COM input 1, pilot 2, live debug 3. `battle_seam_test` fails if that grows or if `main.cpp`, `render`, `ui`, `audio` or `game` name the legacy simulation. The pilot flag path moved to `gameplay/native/rena0_pilot_run.h`. Still coupled at M4's door: `MatchEconomy` stays in the view, `moves()`/`weapon()` return our parsers, `hypermode_wire_value` and `hypermode_params` still come from `fighter.h`, and animation still reaches the renderer through the legacy-owned `xm::Controller`. One test fixed: `debug_keys_test` read `fighter(-1)`, out of bounds, which only happened to work before these calls became virtual. Behaviour evidence is the full suite; no visual comparison before and after. Not committed.

- 2026-10-30 — M4 first slice — **the core drives the rendered fighters behind `--sim=core`.** `sim::CoreBattle` implements `game::Battle` over `sim::Battle`; `--sim-roster=<dir>/<name>[:costume][@weaponSlot]` starts a four-fighter match. `sim_pose_test` compares the core's bones with our `xm::Controller` sampling on Rena+0: all 12 sets the script binds agree within 0.09 units (a fighter is about 150 tall), and all 46 combos' rigs align at frame i = bone i+1. A headless sweep rendered 46/46 combos for 300 ticks with `RESULT: ok`, and captures show posed fighters with weapons in the stage. Still empty on this path: combat events, projectiles and effects, audio, hypermode and aura, trails, the match economy and result flow, lock-on (fixed to the opposing slot), and the `Special` button. The sweep shows they load and fight, not that they look right. Not committed.

- 2026-10-30 — M4 second slice — **shots, effects, audio cues, hypermode meter, score and round end now come from the core.** Live projectiles render through `projectile_render_pose` on the weapon's own bullet models (registration numbers map back to rows); `effect_requests`, `sound_requests` and resolved `voice_requests` reach the product as lists on `BattleFrame`, and the round's winner and time limit come from `combat.match`. Four more headers were vendored for the projectile pose (in `MANIFEST.sha256`). `sim_core_test` pins that events arrive and resolve and that a 10-second limit decides a winner and opens the result; `combat_audio_test` covers the direct cues. Captures show shots flying with the right model. **Not heard:** every run so far is silent, so audio is verified only to the sink. Still empty: weapon trails, animated shot models, combat statistics and hit counts behind the title rules, hypermode duration, flash and activation overlay, the debug overlay. A shot from another item has no card and is skipped. Front-end entry is unexercised. A headless sweep rendered 46/46 combos for 900 ticks with no missing shot model and no unknown effect id. **Separate finding:** `pause_overlay_panel` and `character_shadow` now fail intermittently on this machine, on a non-deterministic four-view frame. `character_shadow` failed 7 of 8 runs both on this tree and on a clean build of `6c575915` (before M3), so these changes did not introduce it; the cause is not known. Not committed.

- 2026-10-30 — M4 owner playtest, first — **"o combate parece bom", "o gameplay em si parece correto", "a CPU parece reagir corretamente".** Owner observation (tier 3) on the `--sim=core` build at `1e7200c7`, with the known missing details confirmed as missing. It is a first impression, not M4's closing playtest, and it does not establish parity with the original.

- 2026-10-30 — M4 third slice — **the front end reaches the core, and the known gaps are closed.** With `--sim=core` an empty panel becomes a random COM, as `prepare_local_roster` does, so one human still fights four; `sim_frontend_flow` drives title, selection, versus, battle and result through the shipped screens. Results read the core's own statistics, and titles come from its recovered selector (FUN_00430880) instead of the port's partial chain. The product leaves the battle when the core has finished its KO presentation and chosen the titles. Added too: hypermode clock, flash and activation state; animated shot models; weapon trails from the core's trail flags and Prop bones; position interpolation between ticks. **Not done:** the camera stays ours, not the core's. Shots from another item still have no card. The combat debug overlay, the tactics readout and hit counters behind `titleHits` stay empty on this path. Nothing here was played or heard yet. **Flaky captures explained:** the intermittent `pause_overlay_panel`, `character_shadow` and front-end script failures came from a connected 8BitDo pad. Physical devices have been read in every run since 2026-10-29, so its input reached the scripted runs: `character_shadow` passed 2 of 8 with the pad and 8 of 8 with SDL told to ignore it. CTest now sets that hint for every test; the game itself still reads every device. Not committed.

- 2026-10-30 — M4 second owner playtest — **trails and hypermode work, but only music played, and "certa parte da lógica do golpe da Rena" is missing.** Owner observation (tier 3). Some strikes do not change the camera and the HUD is not fully right, which the owner set aside for later. **Audio cause found:** a standalone `--match` never built the combat audio layer; it was built only in `enterFrontendBattle`. Fixed, along with the volumes and data/sysse system sounds, including the activation notice. Measured with a dummy device: 72 voices played in 2,400 ticks. Headless runs far outpace real time, so busy SE channels refuse most effects there (`se_missing`); real-time mixing still needs the owner's ears. Not committed.

- 2026-10-30 — M4, action cameras — **the core's camera requests now reach the product, and Rena+0's Hyper EX asks for its own.** A subagent traced the most likely gap in the owner's Rena report: the core computes the row 350 camera flag and drops it, and `CoreFighter` ignored every camera request. Both are fixed, and the dropped flag is the second entry in `PATCHES.md`. This may also address "alguns golpes não mudando a câmera", since Rena's follow-up and landing melee ask for clip 2. It is not confirmed to be what the owner meant, and the rendered camera has not been seen. Not committed.

- 2026-10-30 — M4, the core's camera — **owner playtest:** the game "tá muito bom", but Rena's hypermode switches the camera to view the target instead of only rotating, a KO looks wrong, and follow-ups should be reviewed. **Cause:** the product's `ArenaCamera` interpreted the core's camera requests with its own rules. **Change:** `sim::Battle` now runs `RuntimeBattle::update_cameras` (tracking, animated clips, manual aim) and its layout's result focus, and `ArenaCamera::set_external_pose` takes the result on this path. Rena+0's EX clip orbits her anchor per `FUN_006333b0`, pinned by `test_rena_ex_camera`. **Open:** no eye clamp and no hiding of the mesh between camera and fighter yet (the original's `collision_camera` selects one to hide), so walls can block the view; the camera has not been seen by the owner. Not committed.

- 2026-10-30 — M4 owner playtest with the core's camera — **Rena's hypermode camera "agora está correto"; follow-ups "parece correto"; walls covering the view also happen in the real game, and the render is close to the original's.** Owner observation (tier 3). On a KO the owner describes the victim thrown into the air with no extra camera logic beyond switching to the other opponent once the character vanishes for its respawn. A `sim::Battle` trace agrees in one case: the lock on a KO'd Satoko-team slot held for 116 ticks until the respawn row 194 at y=1000, with no animated camera. In a second case the CPU's lock moved after 4 ticks, so a CPU can retarget earlier. No eye clamp or mesh hiding will be added. Still open for M4: the HUD, which the owner reports as not fully working and set aside; audio has had no explicit complaint since its fix, but no explicit confirmation either.

- 2026-10-30 — M4, HUD values and platforms — **the core now builds for Windows and web, and the HUD reads more true values.** A read-only subagent listed the HUD gaps; the coordinator re-read the ones acted on. Now from the core: bar fills with reload progress (`battle_magazine_hud`), charge strips, the hypermode fan including Kakera and its active clock (`battle_special_hud`), the HP ghost, the score popup, the target-ring pulse, no HUD in result phases, and a survivor below 1% no longer reads as dead. `foundation_demo.exe` ran a 120-tick `--sim=core` capture under Wine. The web build links the core through `-msse -msimd128`, but **it has not run**: the core reads `daybreak*.dat` directly and the web build streams single assets, so web needs an asset seam, and `_mm_rcp_ps`/`_mm_rsqrt_ss` are approximations that can differ across CPUs, so the hash is not portable. **HUD still missing:** round clock, KO sting and start/respawn notices, win/lose glyphs, attack-direction warnings, the scope mask, Kakera art, player names, overhead bars on all fighters, the tactics readout, and the roster mapping in standalone `--match`. Checked: the Linux suite passes 90/90, and one still from a 1500-frame Linux capture shows the bars, HP, score and fan drawn. The ghost, popup, ring pulse and reload motion were not seen moving, and no one has played this revision.

- 2026-10-30 — M4 owner playtest of the HUD, and spatial audio — **the owner reports combat audio works and the listed HUD items look right, but every sound played at 100% regardless of distance.** Cause: `spatial_mix` used `(min/distance)^rolloff`, which at the original's rolloff .0005 gives about 0.997 at 3,000 units. Original inputs, tier 2: raw world positions (`FUN_0042c8b0`, `FUN_0065a260`, `FUN_006677f0`), listener +150 Y (`FUN_006358c0`), rolloff .0005 (`FUN_00648ad0`, `FUN_006492f0`), min distance 3 (`FUN_006676d0`). The law is now `min/(min+rolloff*(d-min))`, **a tier-6 port rule**: Microsoft publishes no formula, and this one comes from a secondary source. It gives 0.86 at 1,000 units, 0.67 at 3,000 and 0.5 at 6,000. It applies to both battle paths. A 3,600-tick Rena+0 match had 189 positional and 21 plain sounds, the farthest 5,949 units from the listener. Plain sounds stay at full volume. The claim here that voices do too was wrong; see the next entry.

- 2026-10-30 — M4, voices — **the owner reports the four start lines all audible and distant fighting still loud; both had causes beyond the law.** (1) In the front end, the legacy `dispatchCombatAudio` still ran under `--sim=core` and added a BattleStart voice per fighter. It no longer runs on the core; a `--match` capture now logs `events=0` and one start line. (2) Attack and hit voices were always flat. Tier 2: `FUN_0065b420` sends the `FUN_004223d0`/`FUN_00422490` callers to the 3D buffer when `DAT_006cfd00` is 1 (one view, `FUN_006396f0`), and `FUN_00420880` keeps it at the actor +5 forward, +145 Y. They now use the same attenuation as sound effects; start and other flat-route voices stay flat. Wine's `DSOUND_Calc3DBuffer` reduces to the same law as the port's, which is consistent with it but is not the original running. **Limits:** at rolloff .0005 the drop is modest, 14% at 1,000 units and 50% at 6,000, so if the original sounds stronger the cause is still unknown. A voice's position is fixed when it starts, while the original moves it each frame. Voice priority (`FUN_0065b420`'s admission) is not applied on this path. Linux suite 90/90; no one has heard this revision.

- 2026-10-30 — M4 owner playtest of the voice fix (`43583fad`) — **the owner likes the result: "audio parece bom agora".** Tier 3 owner observation of our build by ear, not a comparison measurement; original-runtime parity stays not verified. The limits in the previous entry still stand.

- 2026-10-30 — M5 started — **the owner said "seguir para o M5", and the core is now the default on native builds; `--sim=legacy` keeps the old path until the cleanup commit.** Linux suite 90/90 on the new default. `pause_overlay_panel` assumed the panel always darkens the frame, and the core's camera frames a dark forest where it lightens it, so the test now measures the composite. `release_flow_check.py` on the core (tier 5, headless, scripted): `2v2` and `4p` with `--fighters 4` pass the whole loop with rematches, 4 and 2 rounds. `com` resolves 1 of its 3 rounds, because its timed script drifts into other menus; CTest's `sim_frontend_flow` requires 1. `1v1` never reaches versus, and also fails on legacy, so the script is the suspect, not the core. On legacy, `2v2` and `com` also fall short at 2 of 3 rounds. The web build keeps legacy as its default because it cannot read the core's archives.

- 2026-10-30 — M5 cleanup — **the hand-written combat is deleted; the vendored core is the only battle. Pre-cleanup revision: `e9347627`.** Removed: `fighter`, `match`, `projectile`, `move_behavior`, the bot, the selectors and rule tables, `native/`, `ginkiha_tables.h`, their tests and fixtures, and the tools that generated them, about 48,000 lines. Also gone because they only acted on that path: `--spawn`, `--debug-keys`, `--hitbox-debug`, `--live-debug`, `--native-actions`, `--body-separation`, `--sim=`, and the COM summary. A read-only subagent mapped the deletion; the coordinator checked it against the compiler. Checked (tier 5 unless noted): Linux suite 56/56 on the install, down from 90 by deleted suites; `release_flow_check.py` `2v2` and `4p` with `--fighters 4` complete the loop with rematches, 4 and 2 rounds; `foundation_demo` builds for Linux, Windows and web. **Lost, and known:** web battles (they ran on the old path and need the core's asset seam, M6). Two-fighter `--match` now refuses and asks for `--sim-roster`. F1-F4 debug keys and the tactics cell do nothing on the core; the HUD no longer draws the cell. Device-free coverage of round rules, damage and locks is gone: those behaviours are pinned only by asset-backed core tests, which skip without the install. `live_camera_smoothness_test` and `lock_switch_camera_test` went with the legacy fixtures, so frame-to-frame camera smoothness has no automated test now, only the owner's playtest. **Not cleaned yet:** `BattleFrame` fields the core never fills, `combat_events_for_frame` and its test, and no-op `game::Battle` methods. Metric measured after the commit (`ec789371`, tier 5): 46/46 combos ran 900 ticks through `foundation_demo --headless --match` on stage01. Not played by the owner on this revision, so M5 still waits for the owner's approval.

- 2026-10-30 — M5 closed — **the owner approved M5 ("Aprovado") after being asked to play `534b990f`.** The core stays the only battle; the limits in the M5 cleanup entry stand. Original-runtime parity stays not verified. M6 waits for the owner to order it.

- 2026-10-30 — M6, round start and end — **the owner reported the fighters waiting in the air through a product countdown, then falling with input locked, and a wrong match end.** Cause: the core runs its own start (`battle_startup.hpp`, FUN_00635d40 case 1: three digits of 60 ticks while everyone falls with commands locked), and the product held the core still during a second countdown, so the two ran in sequence. The product countdown is gone: the core starts on the first tick after the VS screen, and the HUD draws its notices from P09 and P04, including KO and respawn. The match end had a defect of mine: hiding the HUD in result phases left no pass, and the empty case fell back to the synthetic test HUD (87%, +21%). That is fixed. Phases 3 to 5 now show one full-screen view, as FUN_006396f0 does, with the team and result glyphs from P05 and P08, then the closing bars. **Port rule:** the bars are solid black, without the original sheet's soft edge. `test_round_start` pins digits 3, 2, 1 and start, the fall, and no movement until the count ends (tier 5). Captures of a 4P front-end run show the same order (tier 5). Linux suite 55/55; `2v2` and `4p` flows pass; Windows builds. **Open:** the product's own result screen still replaces the original's portrait, victory-line and bars composition, and the owner has not said what else is wrong with the end. Not played on this revision.

- 2026-10-30 — M6, result over the battle — **the owner reports the rest of the start and end is right, and that the team announcement and the conclusion screen should draw over the game, not on black.** The result screen now draws over the live scene with no fade into it, and the core keeps animating behind it, without input or sound. The screen no longer repeats the 180-tick team announcement, because the core has already played it. Its bars and dim now reach past 800x600 on a wide target. A fade-out flash, where the report fell back to the quote, is fixed. Linux suite 55/55; a 4P front-end capture shows the portraits sliding in over the stage, then the report over the dimmed scene (tier 5). The black bars and portraits are still the product's result screen, not the original's composition code. Not played on this revision.

- 2026-10-30 — M6, owner playtest of `f7374d61` — **the result over the battle "ficou certo".** Tier 3 owner observation of our build. Original-runtime parity stays not verified.

- 2026-10-30 — M6, HUD from the core and cleanup — **the remaining HUD gaps now read the core's state.** Round clock; the tactic a human gives a CPU ally, with the Tactics key now reaching the core; direction warnings from the actor+850 records, replacing the port's off-screen markers; overhead bars on every other fighter, with the ally's own art; one reticle on the view's target, with its invincible, ally and Friendship cells; the P13 scope in full-charge manual aim; the fan's cells per mode, including P12 for Kakera; and all four fighters in the standalone `--match` roster. **Port rules:** the scope mask uploads as black with alpha 1 - luminance, because the batch has no multiply blend, and on a wide frame the area past 4:3 is solid black. Player names do not apply offline: the original only draws them when a name is present, which comes from netplay. Cleanup: `BattleFrame` keeps only what the core fills; `combat_events_for_frame` and the audio policy layer are gone, leaving request playback; the product's title chain is gone, because the core picks titles. Checked (tier 5): Linux suite 55/55; `test_hud_state` pins the tactic, clock, warnings and reticle; forced-state captures showed the clock with its last-ten pulse, the Kakera and Friendship fans, and the scope. The forcing patch was temporary and is removed. `2v2` and `4p` flows pass; Windows builds. Not played on this revision.

- 2026-10-30 — M6, hypermode order — **the owner reports the HUD is right, and that the hypermode order was wrong, with Friendship first.** The port's enum put Friendship at 0 and translated to the actor's value at +0x318, while the selection screen's first row and the actor's value 0 are both Oyashiro. So choosing the first row, 恐怖のオヤシロ, fought as Friendship. Tier 2: FUN_0040d130:106 copies the slot's +0x3d18 to the actor untouched. The enum now is that value, Oyashiro 0, Friendship 1, Kakera 2, and the translation is gone. Linux suite 55/55; a 4P capture shows the first row on the selection and on the HUD (tier 5). Not played on this revision.

- 2026-10-30 — M6, owner playtest of `b389ca6d` — **the HUD (`176cae2d`) and the hypermode order "ficou certo".** Tier 3 owner observation of our build. Original-runtime parity stays not verified.

- 2026-10-30 — repository reorganization on `reorganize` from `b389ca6d` — **the layout now says what each part is, with no behaviour change.** The product tree moved from `remake/foundation/` to the repository root; `remake/docs/` and the foundation's docs became one `docs/` tree (closed plans in `docs/archive/`), the tracked tools joined `tools/`, and the banks moved to `research/evidence/`. `src/` was regrouped into `app/`, `battle/` (with the untouched vendored core at `battle/core/`), `hud/`, `frontend/`, `ui/` and `camera/`; `main.cpp` was split into the blocks under `src/app/` and keeps only the entry points and the app wiring. The executable is `daybreak`, the CMake targets dropped the `foundation_` prefix, and the packaged binary is `daybreak-bin` so the launcher keeps the name `daybreak`. `docs/PATHS.md` maps every moved path. Checked (tier 5): the baseline fingerprints (three `simctl` roster runs and three headless captures) are byte-identical before and after; Linux suite 55/55 with no new skips; `release_flow_check.py` `2v2 --fighters 4` and `4p` pass; the Windows and web builds exit 0; `scripts/package_linux.sh` and `tests/launcher_test.sh` pass. `sha256sum -c MANIFEST.sha256` in the core reports the same two PATCHES.md-documented divergences it reported at the base revision (443/445) and nothing else. The game was not played on this revision; original-runtime parity stays not verified.

- 2026-10-30 — M6, order set by the owner — **platforms first: CI, Windows and web battles; story mode follows, then graphics and translation.** Reorganization reviewed and merged into `main` (`8ef274cf`). Measured before starting (tier 5): under Wine, headless with no audio, `daybreak.exe` ran the `4p` script through two rounds and a rematch without a fault, and its `--screen=battle` capture is byte-identical to Linux's. Windows has not been played with a window or on real hardware. Web still cannot run a battle. ARM, macOS, netplay and graphics stay out of this step.

- 2026-10-30 — M6, platforms — **CI runs when `VERSION` changes, and a web battle runs on the core again.** The workflow built and packaged all three targets on `8a05b5df`. The packaged Windows zip passed the `2v2` and `4p` scripts under Wine, headless. The core reads loose files when no archive is present (`PATCHES.md`), and `tests/web_match_group_check.py` gives the install's hash for all 46 combos on only the files a browser downloads. The web build had no optimization since its first commit; Release took `--screen=battle` from 2.7 to 58.9 fps in headless Chromium, 33 s after a cold start, with no audio (tier 5). A Release web link takes about 18 minutes, and that build has not run in CI. **Not verified:** the menu flow in a browser, audio there, a human playing web or Windows. Issues #58-#60 stay open. With no pad attached, `release_flow_check` ends early on both the old and new revisions, likely script calibration (#63).

- 2026-10-30 — M6, story mode — **the story mode runs from the title to the credits.** Scene ids and rules come from recovered code (tier 2): the prologue, the team select (FUN_00406850, 0x406310, FUN_004072b0), the dialogue (FUN_0065e500, FUN_0040eb30, FUN_0040f130), the ladder (FUN_00648f30, FUN_006492f0), the retry prompt and game over, the ending movies and the staff roll. The owner compared the dialogue, the team cursor, its art and its panels with the original and accepted them (tier 3). This supersedes D6's "story mode is not built"; the owner updates that decision. Checked (tier 5): all 120 scripts parse, and every asset they name exists; `--story-fight=5:1` reaches the ending and credits on teams 0 and 1; a scripted campaign won two fights and retried losses. **Port rules:** a retry goes back through VS, and the portraits and quote before the retry prompt are not drawn. **Not verified:** a human or a script finishing all six fights, what the original draws on the black interlude at (650, 520). After the staff roll the game returns to the title (FUN_0040e0b0, confirmed by the owner); game over belongs to a refused retry. Story data is not in the web download groups, so the mode is native only.

- 2026-10-30 — M6, graphics and translation — **the owner decided that art derived from the original, the HUD vectors and a font from its letterforms, is distributed in the project ("Distribuir no projeto").** This covers derived art only: the original's own files stay out of the repository. `docs/TRANSLATION-INVENTORY.md` lists what a translation replaces, about 235 strings in images, 983 lines of dialogue and 570 quote files. Nothing is built yet. The target language is the owner's call.

## Recovered-body completeness census (2026-10-15, measured)

The owner's working hypothesis is that the Ginkiha recovery "is probably almost everything we need
for parity with the original game". That is a claim about **coverage**, and it can be measured from
the bundle without running anything. Measurement below; it is not a behaviour claim.

Roster denominator, reconciled from two independent shipped sources: `data/*/NN.dat` in the
install and the 46 `(character, weapon)` rows of the bundle's `character_dispatch.hpp` agree
exactly — **46 legal combos** over 16 characters (14 with three weapons, `hanyu` and `natumi`
with two). Note for anyone re-deriving this: the bundle's `character_names.hpp` order puts
`akasaka` at 9 and `hanyu`/`natumi` last, which is *not* the data-directory order, so combo labels
must be taken from that header rather than from directory names.

### The generated-body families

| Family | Bodies | Combos covered | Combos with no body |
|---|---:|---:|---|
| slot-7 admission (`slot7_body_c_w`) | 46 | **46 / 46** | none |
| dash states 20/23/24/27/28/30 | 276 | **46 / 46** | none |
| jump 40-44 | 230 | **46 / 46** | none |
| remaining melee | 258 | **46 / 46** | none |
| shoot states | 841 | 43 / 46 | `rena+0`, `rena+1`, `rena+2`, `akasaka+2` |
| full charge | 123 | 43 / 46 | `rena+1`, `rena+2`, `akasaka+2` |
| special strike | 33 | 31 / 46 | 15 combos (Rena ×3, Mion ×3, `rika+2`, Hanyu ×3, `tomitake+1`, Irie ×3, `akasaka+1`) |
| ranked slot-7 (Kasai only, by design) | 8 | 2 | — |

**1,815 generated bodies.** The four families that carry locomotion and melee cover every legal
combo. The two Rena shooting states the pilot adapts are covered by the hand-written
`battle_rena_ground_shot.hpp` / `battle_rena_mobile_shooting.hpp` pair instead — which is why the
*shoot* table's three Rena gaps are not a gap in Rena's shooting, and why the pilot adapts those
two files rather than a generated body. (`slot7_body_14_2` genuinely does not exist, but neither
does the combo: `14` is Hanyu, who has two weapons, and the dispatch switch simply has no label
`44`. The bundle's own comment about an "Akasaka +2" gap is a stale label, not a missing body.)

**What this establishes, and what it does not.** It establishes that body recovery is
near-complete at the roster level: **every legal combo has a generated slot-7 admission body**,
and the locomotion/melee families are universal. It does **not** establish parity. A generated
body is a source artifact, not an executed behaviour, and the generated files' own first line says
generation is not a native/world proof; the recovered original for Rena+0 *is* the same function
as the body (`slot7_body_0_0` ≡ `FUN_00445ee0`), but that equivalence was established per body,
not for all 1,815. The bundle's own validation report covers four combos (15+0, 11+1, 8+1, 14+1),
records 35,777 raw differences after its defined ones were corrected to zero, and names **missing
awake-air-dash coverage** and **no observed attack-cancel**. The remaining work is the host seam
and per-combo integration, not body recovery — which is the part this pilot has been measuring on
one combo, one family at a time.

- 2026-10-15 — pilot agent with three GPT-6 Luna read-only agents — **v3 prepared to the point where
  approval is the only gate** — The owner asked to continue until the v3 decision is the sole
  blocker. Working from the pending verdict's three named gaps, everything that does not need the
  owner's signature was closed or explicitly re-scoped, and each closure is measured rather than
  asserted. **(1) The proposed matrix now runs.** The fixture runner reads its manifest from the
  directory it is handed, so a scratch directory holding the fixture links plus
  `local-data/harness/MANIFEST-v3-proposed.txt` executes the proposed acceptance set without
  touching the approved file: `PASS (23 fixtures, 60 Hz, **24 case rows, 40 acceptance fields, 6
  unsupported declared, 0 unreferenced extras**, skips=0)`, byte-identical over three runs, against
  the approved v2 manifest's `21 case rows, 39 fields, 7 unsupported, 3 extras` — so the approved
  denominator has provably not moved. **(2) `charge_gauge` is promotable**: the spend is
  implemented behind the flag and asserted by `rena0-charge-spend.fixture`; the old "reads 1000 and
  never moves" reason is corrected in the contract. **(3) The guard gate's "inexpressible" terms are
  expressible after all.** The predicate is now a pure function (`decide_rena0_guard`) pinned
  offline for all four terms — any-angle guards from behind, the 45-degree bound inclusive inside,
  the attacker's bit 8 defeats it, a row without `0x400` cannot guard — and the two remaining terms
  are **unreachable with this combo's shipped records** (zero records carry `0x2000`/`0x8000`), a
  data fact verified by `rena0_guard_flags_test` (12 checks) rather than an implementation gap. The
  bundle's `0x8000` contact-OR term is named as the one term the predicate does not read. **(4) The
  hit/KO pipeline is measured, not hand-waved**: ~250 lines of genuinely portable integer arithmetic
  (S3-S8-selection, zero actor lookups, zero virtual calls) fed by a named-bone world matrix per DAT
  frame plus the victim's `Bip01_Head`/`Bip01_Spine` spheres, and by a DAT phase/hold table for
  every reaction row the attacker's fields `0x64`/`0x68` can name; its damage chain reads the live
  `+0x7c8`/`+0x7cc` modifiers, which for the 300-family swing default to the neutral 100 the port
  already hard-codes. Recommendation stays the owner's recorded exclusion, now with its cost and
  its evidence named. **(5) The shot spawn point is re-scoped precisely**: no recovered body
  computes it (the generated layer has no projectile event, and the request structs carry no
  position); it is composed at one host site from a `Bip01_Prop1` bone matrix and, only when the
  held model is not hidden, the item's socket offset. The port spawns at a fixed `(forward 60, up
  100)` — labelled an approximation, and the fields stay excluded and unasserted. **(6) The
  +1/tick refill is identified**: it runs exactly when the mode-2 special is active
  (`slot7_native_bodies_20260929.hpp:52-64` with `byte(0x846)`), so it is a bounded unit rather than
  an unknown. **Also in this round:** the owner's completeness hypothesis was measured — every one
  of the 46 legal combos has a generated slot-7 admission body, the dash/jump/remaining-melee
  families cover 46/46, shoot and full-charge cover 43/46 (Rena's shooting is the hand-written
  pair the pilot adapts), and `1,815` generated bodies exist in total (census above). Evidence
  separated: **builds** — clean, no warnings in the changed files; **tests** — `ctest` **83/83
  passed, 0 skipped**, the offline bodies 8/8, the fixture-linked differential `357 in-domain
  ticks, no unexplained divergence`, and both saved probes re-verified **byte-identical** against
  the current source (`0cec45e2…`, `7c219504…`) so flag-off is provably unchanged; **seeded
  failures (intended, not passes)** — `rena0_pilot_gate_test --seed-wrong-gate` and
  `rena0_slot7_gate_probe --seed-wrong-gate` both exit 1. Limitations unchanged and stated: no
  original-runtime parity, acceptance still **0/46**, freeze list A in force, nothing committed,
  no cleanup started. **Blocker: the v3 approval itself** (`PILOT-EVIDENCE-CONTRACT.md` V3-1/V3-5),
  which only the owner can give.

- 2026-10-15 — pilot agent — **2f repeated against the v3 candidate; the v3 signature is now the
  only blocker** — [`PILOT-SEAM.md`](PILOT-SEAM.md) §28 is the repeat the objective asked for, run
  on the current source with the approved and proposed manifests side by side. **The matrix:** both
  sets pass, each 3×-byte-identical, and their logs differ in exactly one line — v2 `21 case rows,
  39 acceptance fields, 7 unsupported, 3 extras` (`fce0e063…`) versus v3 `24 case rows, 40 fields,
  6 unsupported, 0 extras` (`4c8063be…`), so the approved denominator provably has not moved and
  the revision's entire delta is three case rows plus one promoted field. **Fail-closed, measured:**
  deleting the promoted field's assertions with its manifest line standing fails the run
  (`does not assert field 'charge_gauge'`, exit 1). **Honest gap found and recorded rather than
  hidden:** deleting the `case shot-gauge-spend` line still passes at `23 case rows`, because the
  runner's own `kRequiredCases`/`kRequiredFields` are the v2 lists — promoting the three rows into
  those constants would break the approved v2 manifest, so it is part of the post-approval diff,
  not something this report may pre-empt. **The rest of the evidence:** offline bodies 8/8, the
  fixture-linked differential at 357 in-domain ticks with no unexplained divergence, live
  locomotion/melee/shot at 200/33/99 compared and agreed with 0 disagreements, the guard pair
  reproducing `asked=3 guarded=2 no-record=0 not-guard-capable=1` with its intended `90 → 92` HP
  difference and a 2×-identical capture and stdout, the pilot gate test's two refusals and both
  flag-off controls, and `ctest` **83/83 passed, 0 skipped**. Rollback is unchanged in shape:
  locomotion/melee/shot captures byte-identical with the flag off, the guard pair differing only
  in the HP fields (and in the guard-attacker-alone scenario, where the victim-side predicate is
  never asked, byte-identical with `asked=0`). §28.4 maps each 2g criterion to its evidence and
  states what is *not* claimed: acceptance, original-runtime parity, the dash drain, the spawn
  point, and the runner-constant gap. **Nothing in the objective's list is now blocked on an
  agent:** the three v3 cases exist and run, the charge-gauge promotion is implemented and
  asserted, the hit/KO pipeline is measured per stage and recommended as the recorded exclusion,
  the spawn point is attributed to its real owner and declared an approximation, the guard
  predicate's four terms are pinned offline with the two unreachable terms proven unreachable from
  shipped data, and the completeness hypothesis has its counter-number (1,815 generated bodies;
  46/46 combos for the four core families). **The remaining work is owner-only:** approve, amend
  or reject the v3 candidate, which also decides whether the three rows move into the runner's
  required lists. Acceptance stays **0/46**, the verdict stays the owner's, freeze list A stands,
  nothing committed, no cleanup started.

- 2026-10-22 — owner + pilot agent — **v3 APPROVED, and one of the pilot's two dash claims
  withdrawn on the owner's observation** — The owner approved **v3** of the acceptance contract
  (reviewed content `sha256 12bd62ec…`; recorded in `SCOREBOARD.md` and
  [`PILOT-EVIDENCE-CONTRACT.md`](PILOT-EVIDENCE-CONTRACT.md)), and in the same message supplied the
  game-behaviour correction that mattered most: **in the original, nothing but the stamina meter
  interacts with a dash.** Checked against the code, the owner is right and the pilot's first dash
  claim was wrong. `+0x834` — the field the adapted dash bodies gate on (`0 < +0x834`) and drain at
  **12/tick** — **is** the stamina meter, and this port already applies that rule to `m_stamina` at
  1/10 scale: the recovered 12/tick is `LocomotionDefinition::dashDrain` **1.20** for Rena+0
  (`move_behavior.h`), drained at `fighter.cpp:1872` for `m_phaseIndex < 2`, with the same phase-1
  exit at `m_stamina <= 0` (`:1883`) and the same admission refusal in the programmed gate at
  `:2951`. The "gauge-0 dash discrepancy" was therefore an **injected-state artefact**: the probe
  forced `set_charge_gauge(0)` while stamina stayed at 100, a state the original cannot produce
  because the port's two counters are one original resource. The `PilotCharge::dash_gauge_refuses`
  consult and its policy override were **removed**; the pilot gate test now pins the true
  invariants instead — the recovered 12/tick equals `dashDrain × 10`, flag-on and flag-off both
  enter row 20/set 13 with the charge counter untouched, and a `--seed-wrong-gate` run that expects
  the charge gauge to block the dash must fail (it does). The empty-tap voice from the same slice is
  **kept** and independently confirmed by the owner ("Rena says a line in Japanese that she needs to
  wait"). With v3 approved, the recorded post-approval gap was also closed: the tracked
  `tests/fixtures/rena0/MANIFEST.txt` now carries the v3 rows, and the runner's own
  `kRequiredCases`/`kRequiredFields` gained `guard-gate`, `shot-gauge-spend` and `charge_gauge` —
  the mutation that previously slipped through (deleting the `shot-gauge-spend` case line) now fails
  with `the manifest no longer declares the required target case 'shot-gauge-spend'`, and deleting
  the `charge_gauge` field line fails likewise. The port's remaining modelling debt is named, not
  fixed: two counters for one resource, with different regen rates (`m_stamina` 1/tick versus the
  recovered +40/tick at 1/10 = 4/tick), deferred to the post-verdict cleanup as
  [`PILOT-EVIDENCE-CONTRACT.md`](PILOT-EVIDENCE-CONTRACT.md) V3-6. **Verification:** build clean
  with no warnings; `ctest` **83/83 passed, 0 skipped**; offline bodies 8/8; differential 357
  in-domain ticks; both saved probes re-verified **byte-identical** against the current source
  (`0cec45e2…`, `7c219504…`), so flag-off is provably unchanged by the removal; the tracked v3
  matrix is 3×-identical (`d283a70c…`). Acceptance is still **0/46** and the 2g verdict is still the
  owner's; freeze list A stands, nothing committed, no cleanup started. **Next: the owner records the
  2g verdict** — the contract gate it was waiting on is now satisfied.

- 2026-10-22 — pilot agent — **verification of the claimed final gate found acceptance-enforcement defects; P2-8 reopened for this bounded fix.** Done: preserved the existing WIP and rebuilt the current pilot targets; all 12 `rena0_*` CTest suites passed with zero skips. Verification: three scratch mutations under ignored `local-data/harness/v3-gate-review-20261022/` incorrectly exited 0: remove the legacy guard fixture and its manifest row (22 fixtures/23 case rows); replace the pilot guard row/fixture with ordinary guard-hold (22 fixtures/24 rows); remove `MANIFEST.txt` but provide a decoy `.txt`. These violate the already-approved fail-closed contract, not a new coverage proposal. Limitations: passing the existing suite does not establish that acceptance cannot shrink; no original game was run and no verdict/cleanup/other-combo work is authorized. Exact next action: require the approved case-to-fixture pairs and the literal manifest filename, add an automated mutation regression, then rerun the pilot suites and review the stamina/spend provenance independently.

- 2026-10-22 — pilot agent — **re-audit fixes verified; the earlier “only 2g remains” claim was false.** Done: enforced all 24 approved case/fixture pairs and all 40 approved field/fixture pairs independently; required literal `MANIFEST.txt`; added a permanent six-mutation regression (`rena0_manifest_enforcement_test.py`); checked no-stun on the actual guarded-contact tick and required the guard fixture to exercise a recovered block; constrained CLI policy attachment to loaded Rena+0/item001 and detached every policy outside its domain; added equipped-identity safety assertions and removed misleading source-equivalence prose from the diagnostic dash test. Verification: full current-source build and **84/84 CTest suites passed, zero failures, zero skips** (new suite accounts for +1); focused pilot campaign **13/13 passed**, including the six intended mutation rejections. One transient compile failure in the new safety test used deleted CharacterMoves copying; fixed by using an unbound metadata-only negative probe and rebuilt successfully. The diagnostic seeded wrong gate still exits 1 as intended. Evidence failure kept separate: a scratch Rena-corrected no-spend expectation **fails** at tick25 (expected1000/got500), proving the approved powered-shot deduction is not source agreement. Direct source read: Rena executor `FUN_0043ffc0.c:1968-2020` and `battle_rena_mobile_shooting.hpp:216-221` emit bullet1/7 without −500; the cited `FUN_00508a60.c:76-114` describes a directional air-dash cancel out of402 to30, with matching generated statements in `slot7_body_5_1:6466-6501`, not Rena's selector. **TODO(question 19)** requests a reviewed contract correction; the required fixture and production deduction remain unchanged and explicitly labelled provisional so approval is not silently weakened. V3 approval and 0/46 acceptance remain recorded; no green verdict, cleanup, other-combo implementation or original-runtime parity is claimed. Another bounded remaining check is empty-shot release19/20: only release1 is dynamically pinned, and the hook currently lacks the exact source hold-count gate. Q20 records the delegation limitation: requested Luna routing was unavailable; both read-only children disclosed gpt-6.1-sol and were stopped, with no edits/builds; cited source findings were directly checked by the coordinator. Exact next action: resolve Q19's source-corrected powered-shot/recovery scope, then implement/test that reviewed correction and the remaining bounded input/resource seam cases before repeating 2f. No commit/push; original install and reference bundle unchanged.

- 2026-10-22 — pilot agent — **owner approved the Q19 correction; the misattributed powered-shot spend is deleted and re-tested.** Done: (1) removed `Fighter::PilotCharge` entirely — the interface, `Rena0PilotChargePolicy`, the `m_pilotCharge` member, the `main.cpp` attach/detach calls, and the `MoveOp::Launch` deduction that spent 500 of `m_chargeGauge` on the 402 powered branch; (2) replaced the contradicted `rena0-charge-spend.fixture` with two source-backed required cases — `rena0-powered-shot.fixture` (the powered air tap launches **bullet row 7**, `FUN_0043ffc0.c:2009-2014`, and `charge_gauge` stays at its 1000 cap on the launch tick and through the action: no subtraction exists on that path) and `rena0-shot-recovery.fixture` (row-403 recovery **+40/tick** clamped at 1000, `FUN_0043ffc0.c:2021-2040`, observed 900→940→980→1000 from a below-cap start); (3) added the `shot_bullet_row` observable (the newest live P1 shot's item row) so the powered branch is distinguishable at all — the ordinary ground tap is row 0, the powered air tap row 7, which mirrors the source's own `FUN_00434fd0(0|1|6|7,…)` argument rather than asserting a bare 7; (4) added a `charge_gauge <n>` fixture directive so a fixture can start below the cap, since after the deletion the product has no path that lowers this counter and the refill is otherwise unobservable — labelled a harness affordance in the fixture and the contract; (5) implemented the empty-ammo release window the audit had flagged as unverified: a held-frame counter `m_chargeHeldTicks` now feeds the recovered `0 < released < 20` test, replacing the seconds field that a bound weapon pins to one tick, with all hold resets routed through one `clear_charge_hold()` helper so the two stay in step. Verification: full current-source build clean; **84/84 CTest suites passed, zero failures, zero skips**; focused pilot campaign **13/13**. Matrix grew rather than shrank — **24 fixtures / 25 case rows / 44 asserted fields / 6 unsupported / 0 extras**, verified by the runner's own summary line. Test sensitivity proven twice: seeding `kChargeHoldTickCap` to 21 makes the 20-frame assertion fail (header restored byte-identically afterwards), and the seven-mutation enforcement regression rejects a missing `MANIFEST.txt`, the legacy guard pair, the pilot guard pair, the right dash, the `charge_gauge` declaration, the powered-shot case row, and a redirected `dummy_hp` binding. The diagnostic `--seed-wrong-gate` still exits 1 by design. Limitations, recorded rather than resolved: the recovery fixture's 900 start is not a reachable original state — Rena+0's gauge spend is still unrecovered, so the refill is exercised as a rule, not as an observed economy; and the port's two stamina/charge counters remain unsynchronized against the single source `+0x834` that feeds the HUD (`runtime_battle.hpp:2221`), which is a frozen-path change and not cleanup. Docs updated: `PILOT-EVIDENCE-CONTRACT.md` V3-1 (both replacement rows), V3-5 erratum, V3-7 (resolution record), `PILOT-SEAM.md` §23f superseded notice + §28.1/§29, `QUESTIONS.md` Q19 answered, `SCOREBOARD.md` counts, `MANIFEST.txt` header. Acceptance remains **0/46**, freeze list A stands, nothing committed or pushed, existing WIP preserved, untouched combos unaffected. **Next: the owner's 2g verdict; no agent-side blocker remains for this slice.**

- 2026-10-22 — pilot agent — **the split `+0x834` resource is scoped, not implemented (Q21).** Done: read every writer/reader of the actor word behind `+0x834` and mapped it against the port's two counters; wrote the scope into [`PILOT-SEAM.md`](PILOT-SEAM.md) §30 (recovered rule table, port rule table, quantified divergences, options A/B/C with cost/risk/rollback) and recorded the decision request as Q21. Key measured facts: the recovered meter is one 0..1000 word with dash −12/tick (Rena+0's five grounded dash bodies) and −11/−3 in state 30, guard −10 per phase-1 tick, recovery +40/+5 clamped at 1000, a mode-2 +1/tick refill, and **no passive grounded refill** anywhere in the recovered update; 881 gauge-arithmetic sites exist across the adapted bodies. The port drains `m_stamina` (0..100, 1/10 scale: dash 1.20/tick matches, guard 0.4167 should be 1.0, regen 1.0 has no source counterpart) while refilling `m_chargeGauge` (0..1000) which **nothing drains** — so the recovered "no attack with an empty meter" gate is unreachable, and the existing `rena0-guard-hold.fixture` pins exhaustion at tick 245 where the source rate gives ~100. Verification: this is a read-only scoping pass — no production file, fixture, test or frozen path was modified; the suite state is unchanged from the previous entry (84/84, pilot 13/13). Limitations: the fly drain has no citation and stays a labelled port rule; the state-30 −11/−3 split needs its own branch decision; original-runtime behaviour of the meter under match conditions is unverified (no tier-1 trace). Exact next action: the owner answers Q21; option (a) would need an `EXCEPTIONS.md` row naming `fighter.cpp`, `fighter.h`, `main.cpp` and the pilot tests, and a contract amendment because `stamina` is an asserted acceptance field. Nothing committed or pushed.

- 2026-10-23 — pilot agent — **owner approved Option A (Q21); the meter is unified behind the pilot flag.** Done: added source-shaped 0..1000 `m_actionMeter` to `Fighter`, authoritative only when a `PilotMeter` policy is attached (`--native-actions=rena0` for Rena+0 via `main.cpp`; the acceptance runner attaches it for its fixtures); default path untouched. All rates now the recovered integers at cited call sites (dash −12/−11, guard −10/tick with exit at 0, recovery +40/+5 clamp 1000, mode-2 +1/tick, no passive refill, no flat trigger spends, modal leap −100). Re-pinned: guard-hold stamina 75→40 at tick 59 with exhaustion 245→99 (source rate predicts ~100, run confirms 99); shot fixtures for the jump's own −100/−5 (795 base, recovery 835→915→955→995, clamp tick 54); gate test Case A rebuilt (admission at full meter both paths, pilot refusal + flag-off admission at empty meter, exactly one −12 drain 1000→988 on the admission tick; seeded admitted-at-zero fails). Verification: full build clean, **84/84 CTest, zero failures/skips**; pilot **13/13**; seven-mutation regression all rejected; `git diff --check` clean. Named limits carried forward: state-30 −3 arm, jump row variants, guard phase granularity, port-rule fly drain, Kakera mapping. Docs: contract V3-8, `PILOT-SEAM.md` §30.6, Q21 answered, scoreboard counts/rows. **Still needed from the owner (cannot be done by an agent):** the `EXCEPTIONS.md` row for these frozen-file edits and the 2g verdict itself. Nothing committed or pushed; existing WIP preserved; no other combo's behaviour changes.

- 2026-10-23 — pilot agent — **manual validation found a real meter defect; fixed and re-verified.** The user held guard to exhaustion and the bar never refilled. Root cause, confirmed against the source: the first unification invented a modal −100 leap spend and left the recovered jump refills unimplemented, while no jump body charges a launch spend at all — every row-41 spend (−10 modal, −4/−6/−12 by combo) is gated on `gravity == 0`, i.e. the hover drain, and rows 40/44 refill +40/tick. Fix on the pilot path only: leap spend deleted; +40 on the launch tick (`m_jumpStartup`) and +40 on the Jump→Idle landing transition (one tick of the row-44 rule; the port has no landing row); hold-to-fly drains the recovered −10/tick (launch tick excluded). Legacy path untouched. Re-pins: jump-chain pins 900→940 on launch and 940→980 on landing; shot fixtures read the cap through the launch with recovery tail 980→1000, clamp tick 50. Verification: full build clean, **84/84 CTest, zero failures/skips**; fixture matrix and seven-mutation regression green; `git diff --check` clean. Named limits: row-44 multi-tick duration, row-41 combo variants, state-30 −3 arm, guard phase granularity, legacy fly rate, Kakera mapping. Docs: contract V3-8 supplement, `PILOT-SEAM.md` §30/§30.6, fixture comments. Nothing committed or pushed; the `EXCEPTIONS.md` row and the 2g verdict remain the owner's.

- 2026-10-23 — pilot agent — **the meter's ordinary refill was missing; found in the binary, not guessed.** Manual play reported the meter never recovering. Rather than speculate, I pinned the binary (`27e61475…`), decompiled `FUN_0043ffc0` with Ghidra via REA, and read the executor's state dispatch: **case 0 (standing/idle) adds `0x28` = 40 to `+0x834` every tick** (5 with hit-status slot 6), clamped at 1000, before input handling. My V3-8 claim that "no passive refill exists" was wrong — `FUN_0041f580`'s gated `+1` and the row refills are additional, not the whole story — and the V3-8 supplement's row-only implementation left idle completely dead, which is exactly the symptom. Fixed: the standing refill is implemented on the pilot path, gated to ticks that were already standing before input (`stateBeforeInput`) so a launch/landing/attack tick takes its own row's rule and does not double-refill. Verification: full build clean, **84/84 CTest, zero failures/skips**; new required `idle-refill` fixture holds Guard from a below-cap start, releases, and pins +40/tick from 440 to the 1000 clamp; proven load-bearing (the branch deleted → 3 fixture failures; restored → green). Matrix **25 fixtures / 26 case rows / 45 fields / 6 unsupported / 0 extras**. Also checked against the user's belief that the pre-plan code was right: the milestone-1 implementation (`d462f56b`) refilled whenever the fighter could act, which is the same intent the binary confirms — the later rewrite narrowed it to grounded-only, and my unification then deleted it entirely from the pilot path. Named limits updated: the combo-specific spend variants and hover rates remain; the standing rule is now evidence-backed rather than inferred. Docs: contract V3-9, `PILOT-SEAM.md` §30.6. Nothing committed or pushed; the `EXCEPTIONS.md` row and the 2g verdict remain the owner's.

- 2026-10-23 — pilot agent — **jump/float is once per airtime; port allowed unlimited re-hover.** Owner report (applies to all characters): releasing the jump button and pressing again must not double-jump or keep floating. Traced in the shipped binary (`rea decompile` of `0x00445ee0`): the jump row is admitted only while grounded (`0x84 != '\0'`), and the airborne dispatcher offers only dash/attack rows — the air chain runs once per airtime with hover as one of its phases. The port's `wantFly` was a re-enterable time budget (`input down && m_flyLeft > 0`), so a re-press resumed the climb. Fixed with one latch (`m_hoverSpent`) armed on button release while airborne, cleared on landing/new airtime; a held button still climbs the full budget. Verification: full build clean, **84/84 CTest zero failures/skips**, pilot 13/13, seeded wrong-gate still fails by design. New required `single-hover` fixture (jump/hold/release/re-press → lands on schedule) is load-bearing: removing the latch reports `airborne exp 0 got 1`. Matrix 26 fixtures / 27 case rows / 45 fields / 6 unsupported / 0 extras. Process note recorded honestly: two earlier "failures" in this pass were a stale build (`ninja: no work to do` while `fighter.cpp` had not compiled), which briefly produced wrong conclusions about both the latch and `fighter_script_test`; both were re-checked after a forced rebuild and are green. Side observation, not investigated: after the re-press the fighter ended in `state=2` (Run) while airborne in one probe — a possible separate air-dash stall worth a future look. Docs: contract V3-10. Nothing committed or pushed.

- 2026-10-23 — pilot agent — **jump height was capped by a port invention; the meter is now the only limit.** Owner report: holding jump should go higher, bounded only by stamina. Binary evidence (`rea decompile` of `0x0043ffc0` case 0x29 / row 41): vy accumulates +0.2/tick capped at 6.0/tick and each climbing tick spends 10 of the action meter; no altitude ceiling exists anywhere in the air chain, and `FUN_00421bd0` — cited by the port as a "flight cap" — only writes spawn X/Z and a 1000.0 respawn Y, the constant the port already knows as `kRespawnAirY`. Two port defects fixed on the pilot path: vy was overwritten with the constant 12/tick every tick (no acceleration, no sustained climb), and a `kFlyMaxAlt` 420-unit clamp capped every jump regardless of meter. Measured after: y 246/366/**468** at ticks 40/60/80 — past the old cap — with the meter at 280 at apex, descent starting as it empties. New required `jump-climb` case with a new `y` observable is load-bearing (restoring the cap → `y exp 468 got 402`). Re-pinned with it: tap-jump now lands at 25 (was 48, an artefact of the pinned vy), single-hover and shot-recovery anchors. Verification: full build clean, **84/84 CTest zero failures/skips**; matrix 27 fixtures / 28 case rows / 46 fields / 6 unsupported / 0 extras. Process note: an earlier scratch-trace round in this pass fought the manifest's required-field machinery instead of using the fixture vocabulary directly — the `y` observable is the durable fix for that. Named limits: row-41 combo spend variants (−4/−6/−12) and state-30 −3 arm unchanged; the legacy path keeps the old cap until its gate. Docs: contract V3-11. Nothing committed or pushed.

- 2026-10-23 — pilot agent — **the climb was cut by a 1.2 s time budget while the bar still showed ~28%; fixed.** Owner screenshot showed holding jump stopping with a quarter of the STA‌MINA bar full. The arithmetic matched the port's `kFlyTimeSec` 1.2 s budget exactly: 72 climbing ticks × 10 meter/tick = 720 spent, 28% left. Source (row 41, case 0x29) has no duration and no altitude test — the climb ends only on button release or meter zero. Fixed on the pilot path: the budget no longer gates the climb, `m_actionMeter > 0` does; legacy keeps the budget. Correcting it also exposed that the previous gate let the climb continue past meter zero (726 vs 621), now caught. Measured: y 246/366/486/606 peaking **621** as the meter hits 0 (~tick 100), falling to 436 by tick 140. `jump-climb` pins curve + apex meter + zero crossing; removing the meter gate fails it. Verification: serial suite **84/84**; matrix 27 fixtures / 28 case rows / 46 fields. Honest test note: `device_isolation_test` is intermittently red under `ctest -j 4` and green serially/alone — synthetic-pad title navigation, no relation to jump physics; the pre-existing uncommitted 64→60 Hz comment edit in `synthetic_pad.h` made it deterministic in one probe, so it is timing-sensitive and was left untouched and reported rather than silently changed. Docs: contract V3-12. Nothing committed or pushed.

- 2026-10-23 — pilot agent — **airborne turn implemented (binary-backed); camera vertical geometry scoped, not guessed.** Owner reported two items. (1) *Air turn — fixed.* The port had no airborne turn: the turn block only ran in the Walk state, so a held direction moved the body without rotating it. Source: `FUN_00428510` @`0x428d9b` writes `+0x874 = 0x40000000` (2.0 deg/tick) then calls `FUN_00421780`, whose `FUN_0042db10` turns yaw toward the input bearing by at most that step (read from the disassembly: `mov DWORD PTR [ecx+0x874],0x40000000` immediately precedes `call 0x421780`). Implemented on the pilot path; measured `turn_deg` −2.0/tick with Left, +2.0 with Right, sustained. New required `air-turn` case is load-bearing (branch removed → `exp -2 got 0`). (2) *Camera vertical — measured and scoped, deliberately not changed.* `DAYBREAK_CAMINFO` shows the eye does translate with the fighter (p1.y 200→620, eye 410→813) but eye and aim rise together, so the view never tilts. More importantly the port's `heightOffset 300` / `distanceOffset 800` are **misattributed**: in `FUN_006507c0`, the function the camera doc cites, `0x6a4928`/`0x6a1720` are the **far/near plane** offsets applied to the eye→aim distance (`fadd ds:0x6a4928`, `fsub ds:0x6a1720` at the `PerspectiveFovLH` call site, disassembled). So the eye geometry is a reconstruction with no recovered basis — tuning it cannot make it faithful, and the real battle-camera function must be identified first. That needs its own bounded pass, not a guess. Verification: full build clean, serial **84/84**; matrix 28 fixtures / 29 case rows / 47 fields / 6 unsupported / 0 extras. Test-writing note: fixture input lines REPLACE the held mask, so multi-axis cases must repeat every held button (`input 20 LEFT JUMP`), which cost two iterations here. Docs: contract V3-13. Nothing committed or pushed.

- 2026-10-23 — pilot agent — **camera scoping pass (owner-approved): the follow is recovered, the port never had it, three constants were misattributed.** Identified the real camera path in the pinned binary. `FUN_006507c0` is the camera *renderer* (builds `LookAtLH`/`PerspectiveFovLH`, binds shader constants) — it computes no follow, so the port's eye formula never came from it. The two constants the port calls `heightOffset 300` / `distanceOffset 800` are the **near and far plane offsets** at that projection call (`fadd ds:0x6a4928` @`0x6508ae`, `fsub ds:0x6a1720` @`0x6508bb`); 300.0 is also the camera reset's eye Z (`FUN_006616d0`). `FUN_0042cb50`, the port's "camera collision", is actually the **fighter push-apart** used by `FUN_006394c0`. The real follow is `FUN_006333b0` (`mode95==0 && mode94==0`): eye height `dist*0.03 + 140`, vertical clamp `min(eye.y, camY + 200 - (dy-120))`, a `-120` vertical bias, aim `+20 - dist*0.2`. That explains the reported symptom exactly — the port's flat 300 height and `+50` aim keep eye and aim rising together, so a jump translates the view instead of tilting it (measured: fighter y 200→620, eye 410→813, one-for-one). Named as still unrecovered rather than guessed: the `+0x18` rig chain (`FUN_0042dec0`), the `mode95` alternate follow, `[camera+0x78]`, and the two projection modes. **Not implemented**: it is shared presentation state with no fixture gating it, so it is scoped, documented (contract V3-14 + GAME-CAMERA.md correction) and left for an owner decision. Verification: full build clean, serial 84/84; matrix unchanged (28 fixtures / 29 case rows / 47 fields). Nothing committed or pushed.

- 2026-10-23 — pilot agent — **recovered camera follow implemented behind the pilot flag (V3-15/16), with one named tier-6 link.** Continued the camera work the owner approved. Recovered the last constant: `[camera+0x78] = 300.0`, written once by the camera default-init `FUN_00632e10` at `0x632e1a` (verified directly by me; two independent delegated lookups found the same store, so Q20's runtime restriction is now answered by the owner's permission and the results are cross-checked, not taken on trust). Delegation also resolved the two mode flags the coordinator had only stubbed: `+0x94` = "scripted camera animation playing" (set when the followed actor's `int[0x684] >= 0`), `+0x95` = "cinematic frozen shot" (set when `actor+0x2dc != 0`, which also switches the projection to a 6.43° telephoto — confirmed to be a real fovy in radians through the IAT thunk to `D3DXMatrixPerspectiveFovLH`), and corrected two more RE-table entries: `+0x7c` is an int index, not a distance, and `fcn.0042cb50` is the fighter push-apart, not camera collision. Implemented `render::arenaRecoveredFollow` with every constant sourced, wired to pilot views only (`--native-actions=rena0` + Rena+0), and pinned by a new `recoveredFollowCases()` (123 checks, 0 failures) that asserts the behaviour the owner reported missing: raising the rig changes the eye→aim pitch by >0.02 rad. Live trace with the flag on: fighter y 200/512/839 → eye y 435/694/1042, versus the old flat one-for-one 410/813. Full suite unchanged at **84/84** because the default path never changes path. **Named limit, tier 6:** the formula is recovered, its *inputs* are not fully — `FUN_00632ed0` confirms the rig is the followed actor, but `FUN_00632e70` copies the anchor from a global per-slot container (`FUN_00658a10(i)->+0x14`) gated on `+0x94`, so "anchor = locked opponent" is a port assumption, labelled in code; settling it needs the writer of `+0x18` and the `+0x94` gate. Nothing committed or pushed.

- 2026-10-23 — pilot agent — **camera anchor settled: it is the lock-on target (tier 2), so the recovered follow is fully sourced.** Closed the one open link from V3-16. The camera updater selects the anchor immediately before the follow (`FUN_006358c0`, `0x635ab6`–`0x635b2c`): `cmp [actor+0x304],0` / `jl 0x635af4`, and the primary branch pushes `container[actor+0x300].position` (+0x14) into `camera+0x48` via `FUN_00632e70`. `actor+0x300` is the lock-on target field this project already documents (written by `FUN_00421e30`), so the anchor is the **locked opponent's position** — exactly what the port feeds it; it was never the local player. The rig is proven too: `FUN_00632ed0` stores the raw actor position at `+0x24..0x2c` and copies the camera's own point into `+0x18..0x20` when forced, and the updater passes force (`0x634c2f`). So both inputs are recovered and the only remaining gap is narrow and explicit: the source's ally branch (`+0x304 >= 0`, a second container at `actor+0x2f0`, index 0) is unimplemented, and a view with no lock falls back to a point 600 units along the facing (port constant). Updated contract V3-16 (the former "tier-6 assumption" block is replaced by the evidence) and the `main.cpp` comment. Verification: full build clean, serial **84/84**, pilot matrix 28 fixtures / 29 case rows / 47 fields unchanged, live trace with the flag on unchanged (fighter y 200/512/839 → eye y 435/694/1042). Delegation note: the owner's permission (Q20 answered) let two lookups run; both independently found the `+0x78 = 300.0` store that I then verified directly, and the third lookup was stopped once this chain settled the question without it. Nothing committed or pushed.

- 2026-10-23 — pilot agent — **camera anchor corrected to +0x300; the initial-targeting complaint was my wiring, not the formula.** Owner tested the recovered camera: much closer to the original, but the initial targeting was wrong and needed a manual change-target press. Cause found in the binary: the fighter reset `FUN_0041dcb0` (run for all four fighters at round start) sets `+0x300 = 0` (the aim selection) and `+0x304 = -1` (the combat lock), so the recovered camera branch reads `container[actor+0x300]`. I had wired the anchor to `Match::locked_target()` — the `+0x304` field — which is `-1` at round start, so the camera fell back to the facing ray until a gesture installed a lock. Now wired to `Match::aim_target()`, the same selection the camera's bearing already used, which resolves to the living hostile through the recovered fallback pick before any gesture. Verified with zero input: eye now sits on the p1→p2 axis from the opening frames (`cam eye=(-166,407,-2200)` vs p1/p2 at x −463/−1363) instead of behind the player. Labelled reconciliation: raw `+0x300` is 0 for every fighter, which for player 0 is its own index and would degenerate the follow, so the port reads it through `aim_target()` rather than the literal integer — that index-space question is not established. Verification: serial **84/84**; pilot matrix unchanged; `device_isolation_test` flaked once under `-j` parallel load and passed alone and serially, as recorded earlier. Docs: contract V3-17. Nothing committed or pushed.

- 2026-10-23 — pilot agent — **removed the melee meter gate; the owner's scope for the meter is what the binary says.** Owner report: normal attacks were refused at empty stamina, unlike the original; stamina covers blocking, dashes, jump and air dash. `admit_attack_move` declined every press at `meter <= 0`, justified by "every recovered arm gates on `0 < +0x834`". Re-read `FUN_00445ee0` line by line: all eight explicit `0 < +0x834` tests guard dash/jump arms (lines 59/65/72/82/92/100/441/449, binding moves 0x14/0x1e/0x28 and the +0x830 selector), and the lone `+0x834 < 1` (line 168) is an OR term inside the condition that routes the press into the SHOT path — it selects the shot branch, it does not refuse melee. Gate removed; the dash gate and jump/hover gates are unchanged and remain the recovered ones; `fire_shot` gates on ammo, not this meter. Coverage: `melee_admission_test` case (9) rewritten from "empty gauge declines" to "empty gauge still admits 300, enters AttackA, spends nothing" — it failed on the old expectation and is the load-bearing guard; new `rena0-attack-empty-meter` fixture pins the pilot observable, with its header recording honestly that the standing +40/tick refill lands on the same tick so the fixture alone cannot distinguish the rules. Verification: full build clean, serial **84/84**, matrix 29 fixtures / 30 case rows / 47 fields. Docs: contract V3-18. Nothing committed or pushed.

- 2026-10-23 — pilot agent — **guard stance now animates; right-sidestep routing verified correct, artwork left open.** Owner reported that the right grounded sidestep plays a blocking-looking clip and that blocking itself shows no animation. Blocking: the port returned `-1` from `state_move_id()` for Guard and held the playing clip, which measured as the **idle** clip (`guard -> anim_idx=0 Anim-124`) — the missing animation. The "Guard binds nothing" reading came from the damage function's block branch, which does indeed bind no move (re-verified: its `else` writes the registry `=2`, the `0x100` marker and calls `FUN_0042c800(2)`, a 4-slot registry fill) — but the character DAT carries the stance as rows 390/391/392 (Rena+0 clips 60/61/63, 77/62/63, 64/65), and the bundle's `battle_guard_motion.hpp` names the same states with the `-10`/tick drain the port already models. Fixed by binding row 390's opening clip at the animation seam; adopting the 390 *move body* was tried first and rejected because it is a two-button chord that exits the stance and let a guarded hit land (`rena0-guard-gate-pilot` caught it as `dummy_hp exp 100 got 99`). Right sidestep: verified NOT mis-routed — `FUN_00445ee0` sends `+0x830==3 -> row 24` and `==4 -> row 23`, and the bundle's command detector makes 3 = x(−1) = Left and 4 = x(+1) = Right, so Right → row 23 whose DAT clips are 22/23/24. Set 22 is not a guard clip, so the pose is row 23's own startup art: a data/art question left open rather than guessed. Tests updated to the corrected rule (`melee_rules_test` guard section now pins row 390's clip; `melee_admission_test` case 9 asserts a zero-gauge melee is admitted). Verification: build clean, **83/83** excluding the pre-existing `device_isolation_test` flake (still red alone and under `-j`, unrelated path). Docs: contract V3-19. Nothing committed or pushed.

- 2026-10-23 — pilot agent — **guard stance now actually moves; right-sidestep fault not reproducible as wiring.** Owner: both still incorrect after the first guard fix. Live probe (temporary `DBG_ANIM` on `bind_animation_set`, removed afterwards) proved the guard binds correctly (`state=6 move=-1 set->60`) yet consecutive guard captures differed by only 0.9% of pixels — the clip was bound but frozen, because nothing advanced row 390's sections. Added stance progression through row 390's own section order (preparation → hold), stepping when the preparation clip's own DAT duration elapses — no invented constant; captures now differ 8.8% between phases. Release section (63) stays a named limit since leaving Guard goes straight to Idle. Right sidestep: a right double-tap probes as `state=2 move=23 set->22` then `->23`, which is exactly what the DAT pairs with row 23; set 22 is not the guard art (pixel distance to guard sets 60/61 is 24.0/24.6%, the same band as the left-dash set 19's 24.3/25.3%), and the index space is consistent (124 model clips, all referenced sets in range). So routing and clip both match the shipped data and the artwork question is left open rather than guessed, with the discriminating observation named (does the LEFT sidestep look correct?). Tests updated for the corrected guard rule incl. the stand→guard entry. Verification: **83/83** excluding the pre-existing `device_isolation_test` flake. Docs: contract V3-19 follow-up. Nothing committed or pushed.

- 2026-10-23 — pilot agent — **guard loop fixed via the hold_phase flag the port already parsed but never used.** Owner: still wrong, do one at a time, block first, and pointed at the Ginkiha bundle. `development_animated_combat.hpp:2245` advances a phase only when the clip's own duration has elapsed AND the clip does not declare `hold_phase` — a hold phase stays and loops, which is the looping guard stance in the owner's screenshot. The port parses that exact flag: the per-set record is `(blend_frames, hold_phase, event_count)` and the port reads the middle word as `animation_set_phase_gate()` with the comment "gates elapsed-count advance", then never applies it. Now applied: the stance steps through row 390's sections only when the current clip's duration has elapsed and the clip is not a hold phase. Live measurement with Guard held: prep→hold 2.7% pixel change, hold stable at 0.3–0.5%, stance ends on the −10/tick meter drain (the recovered exit). Release section (63) still unreached — named limit. Verification: **83/83** excluding the known `device_isolation_test` flake; pilot matrix 29 fixtures / 30 case rows / 47 fields. Right-sidestep issue deliberately parked until this one is confirmed good by the owner. Docs: contract V3-19b. Nothing committed or pushed.

- 2026-10-23 — pilot agent — **guard static: two clock bugs and a unit bug, not the art.** Owner: the button plays one frame of the blocking animation, static. Diagnosed with a temporary DBG_GUARD probe (removed): (1) the playhead was set from `m_moveElapsedTicks`, which only a running move advances, so Guard sat at track position 0 forever — now driven from the guard's own counter (the bundle's `guard_tick`) and wrapped inside the clip length so a hold phase loops; (2) the stance reset sat in a branch that fires on every HELD tick, wiping clip/phase/tick each frame — now edge-gated on the state change; (3) `anim.duration` is in the model's X tick scale (4800/s), not seconds, so the prep phase never ended when compared against elapsed seconds. Verified live: prep clip 60 for ~7 ticks, then hold clip 61 (`hold_phase=1`) looping with its clock wrapping 0.048/0.041/0.028/0.015. Release section 63 remains unreached (releasing leaves Guard) — named limit. Frame-to-frame change over the hold is small (0.5–0.9% of pixels) because set 61 is a subtle loop; the mechanism is verified against the recovered rule, and whether the shipped loop is lively enough is an art judgement this evidence can't settle. Verification: **83/83** excluding the known `device_isolation_test` flake. Docs: contract V3-19c. Nothing committed or pushed.

- 2026-10-23 — pilot agent — **guard is grounded-only; airborne block removed.** Owner confirmed the block now works and reported the remaining rule: the original does not allow blocking in the air. The port's guard entry tested only the held button, the exhaustion latch and the meter, so an airborne press entered Guard and started the −10/tick drain. Entry now requires `m_grounded`, so an airborne press neither enters the stance nor spends the meter, and the exit set gained a positional case — leaving the ground ends the stance alongside button release and meter exhaustion. `fighter_script_test` asserted the old behaviour ("airborne Guard entered" = true) and was inverted to assert the refusal, that the fighter stays airborne, and that the refused press drains no stamina (baseline captured before the press so the comparison is real, after a first attempt that accidentally compared a value with itself). Verification: **83/83** excluding the known `device_isolation_test` flake; pilot matrix unchanged at 29 fixtures / 30 case rows / 47 fields. Docs: contract V3-20. Nothing committed or pushed.

- 2026-10-23 — pilot agent — **side-dash timing measured; two defects named, not fixed.** Owner: right sidestep art is correct but timing is too slow, and neither side step has a recovery animation (left otherwise correct). Parsed both rows: 23 → sets 22/23/24 at 7/12/24 ticks; 24 → sets 19/20/21 at the same 7/12/24 — identical structure, so the asymmetry the owner sees is not row data, matching the owner's own "correct art, wrong timing" diagnosis. Live probe of both sides shows the same sequence: phase 0 binds, phase 1 binds at state tick 13, and **phase 2 never binds on either side** — the recovery section is never played. Second defect: phase 0 lasts 13 state ticks against a 7-tick clip, which is the slowness the owner measured. Suspect for the lost ticks is the `m_holdAnimation` hold on transition ticks, but it does not account for six, so it needs one more instrumented run rather than a guess. Deliberately did not ship a timing change: the recovery's exit interacts with the dash movement model and I would have been guessing. All temporary probes removed (`grep DBG_DASH` = 0). Verification: build clean, **83/83** excluding the known `device_isolation_test` flake; matrix unchanged. Docs: contract V3-21. Nothing committed or pushed.

- 2026-10-23 — pilot agent — **side-dash recovery: cause narrowed to an early return, not timing; not yet fixed.** Owner: art is right, timing is too slow and neither side step has a recovery animation; suggested the real fault is phase 2 never happening. Instrumented three runs on a right side dash (all probes removed, `grep DBG_` = 0): (1) the phase clock is correct — `phase=0 thr=7 elapsed 1..8`, then `phase=1 thr=12 elapsed 1..12`, so phase 0 ends on schedule and phase 1 gets its full window; (2) a `set_state` probe filtered on leaving Run printed **nothing**, so no state change ends the dash; (3) an entry probe on `advance_animation_phase` filtered to move 23 stops at `phase=1 elapsed=11`. So the animation/phase step simply stops being called partway through phase 1 while the state is still Run — which is why set 24 (and set 21 on the left) never bind and no recovery plays. The phase-2 hold rule already exists at `fighter.cpp:2086` (the bundle's `extra_side_ticks`) and cannot fire while phase 2 is unreachable, so reaching phase 2 should restore the extra ticks in the same change. Remaining budget did not cover finding the early return; next step is named (dash-completion guards in `update()` / `move_behavior.h`'s `dash*` fields). Verification: build clean, **83/83** excluding the known `device_isolation_test` flake; tree clean, no probes left. Docs: contract V3-21b. Nothing committed or pushed.

- 2026-10-23 — pilot agent — **side-dash recovery FIXED: fixed frame timer was cutting the row.** Root cause: `try_dash` sets `m_stateTimer = programmed ? 0 : kDashFrames`, and `programmed` is true only for the forward dash (move 20), so side (23/24) and back (27) dashes ran on `kDashFrames = 20` and the generic state-timer expiry forced Idle before the row's last section — measured at exactly phase 1 elapsed 11, which is the 20th tick. One cause for both reported symptoms: the "next part" never arrived and the recovery set (24 right / 21 left) was unreachable. Fix: a GROUNDED dash whose recovered row has more than one section is phase-driven (`m_stateTimer = 0`), ending through `advance_animation_phase`'s last-section branch. Verified live: right side dash binds **set 22 → 23 → 24** and phase 2 runs its full 24 ticks. Two scoping decisions both caught by tests: applying it to the air dash broke its expiry into Jump (`fighter_script_test`: expected 15, got 2) so the air dash keeps the timer; and applying it to everyone dropped the COM's swing cadence from 3+ to 2 per 900 ticks (`bot_brain_test`) so it is gated on `m_pilotMeter` — the COM/legacy truncated timing is recorded as a named limit rather than covered by editing the expectation. Suite **83/83** excluding the known `device_isolation_test` flake; matrix unchanged 29/30/47. All probes removed (`grep DBG_` = 0). Docs: contract V3-21c. Nothing committed or pushed.

- 2026-10-23 — pilot agent — **side-step timing: phase 0 length measured, no shorter source found (NOT fixed).** Owner: both side-step animations now correct, but the first part should end much earlier. Measured the port's phase-0 length two independent ways and they agree: the DAT clip set 22/19 gives `duration/ticksPerSecond/0.016` = 7 frames, and the recovered conversion in `actor_animation_clock.hpp:17` (`unsigned(period/0.016)`, truncating, 4800 ticks/s) yields the same 7. The port advances at elapsed 8 (`>=` comparison). So phase 0 is 8 frames ≈ 133 ms both in the port and under the recovered formula, which does not explain "much earlier". Checked the move-program rules for a side-dash phase-0 window and found none: `move_behavior.h`'s dash fields and the 310/311/320 rules are attack rows, not rows 23/24. Did **not** ship a speculative shortening — a smaller phase-0 would be an invented number. Named next step: one observation of how many frames the original's first side-step part lasts, or confirmation that the original skips the startup phase for side dashes; either settles whether the phase length comes from a source other than the clip period. Tree clean, no probes (`grep DBG_` = 0), **83/83** excluding the known flake. Nothing committed or pushed.

- **Hyper EX camera — V3-37 (owner: timing right, index wrong, then picked).** Owner report with an original-runtime print: in Hyper mode the Special press fires the EX move (row 350) and it plays the cinematic camera whether or not it connects. **Found:** the port never played it — row 350's recovered program had 29 ops and **zero** `ActionCamera` ops, measured with the opponent out of reach. **Done:** the rule `{350,-1,0,9999,ActionCamera,5,ungated}`, plus an ungated arm (`MoveRule::second` now means "regardless of contact" for this op only) because the executor gated every camera on the melee contact latch — right for the chain, wrong here. **Index history, honestly:** the first attempt borrowed the melee combo's 2; the owner played it, said the angle was wrong, and after every set of `data/camera/01.x` (six) was rendered for this move against their print they picked **set 5** — **superseded 2026-10-29:** the recovered body requests set **0** and the pick of 5 was an artefact of the port treating 0 as "off" (see the 2026-10-29 entry above and contract V3-37). So the index is an owner observation standing in for a recovered constant, labelled as such. **Verification:** Case G drives the sequence — whiffed melee leaves the camera at 0, Hyper activation does not arm it, the EX press puts set 5 on with the opponent 2000 units away; removing the rule fails with `got 0`. Remaining difference at the strike frame is framing distance, not angle. Suite **83/83** excluding the known `device_isolation_test` flake. Contract V3-37.

- **Effect cards now animate — V3-34 (global fix, owner-approved).** Owner: the empty-tap ring card does not match the original, and the fix was worth doing globally because every 2D bullet/impact card is drawn the same way; the clock was to be the card's lifetime, noted in code. **Done:** `EffectInstance` gained a pre-evaluated `poseWorld` (a card lives a few frames, so there is no controller to keep), `placeFxCards` samples each live card from its own model at its own age, and `game::cardAnimationSeconds` maps age→animation time across exactly the card's lifetime — a labelled PORT RULE with the reason in the header and one place to change. `--no-fx-anim` restores the old bind-pose draw for A/B and rollback. **Evidence:** the shipped cards do animate (`data/effect/01.X` carries 10 keys over 40 frames; `data/aura/00.x` scales 1.0→0.876), and `animation_data_test` now asserts the shipped card animates and that its pose differs at birth, middle and expiry — freezing the clock fails both checks, so they are load-bearing. The renderer uploads a different palette for an animated card (1.5708→1.2234) and none with the flag off, and the instance remap matches the template, which is verified to the palette boundary. **Raster check closed:** forcing a card to a fixed mid-animation pose changes the captured pixels (`bind=e3a47a0365` vs `mid=a03a3f70db` at one frame), so the sampled pose reaches the raster; the plain on/off A/B is identical only because `--out` renders one frame and these cards live 1-3, landing on the spawn frame. **What the cards animate** (probe log kept under `local-data/harness/`): the empty-tap ring card scales 1.0 -> 1.11 and collapses to **0.158 on Y** over its 1.333 s animation; the muzzle starburst pops 1.0 -> 1.43 -> 0.876 over **0.050 s**, which is exactly its descriptor lifetime — the first shipped evidence that the lifetime clock is not arbitrary. The owner's visual confirmation is still the last step. Named limits: the eleven-point hyper aura still draws bind pose (fighter state, no per-instance age), and the per-card controller is per-frame work. Suite **83/83** excluding the known `device_isolation_test` flake. Contract V3-34.

- **Rendering report: the empty-tap shot's ring card (V3-33).** Owner posted two screenshots: the original's effect is a soft bright band, the port's is separated hard-edged hoops with dark gaps. **Found:** the card is `data/effect/01.X` (rendering it alone reproduces the port's in-game look exactly); the file is MSZIP-compressed and names the texture `渦巻き.bmp`, which resolves to the shipped `渦巻き.cnv` fire-streak texture through the existing `.bmp`→`.cnv` swap, so the asset is present and bound; the inflated stream carries one `AnimationSet` with **10 keys and 40 frames**; and the port never plays it — `EffectInstance` has no pose for cards, so all cards draw their bind pose, and the card renders identically at demo frames 1/5/10/20/30/40/60. That is a mechanical explanation (a spiral drawn frozen) and consistent with the hoops never blending into a band, but it is **not proof**: no original-side frame trace exists, so "the original animates this card" rests on the asset carrying keys plus the owner's observation. **Not implemented:** animating effect cards changes the shared effect path for every combo (muzzle, impacts, hit cards, hyper aura), which is a blast-radius decision the owner must make. Contract V3-33 records the evidence, the proposed shape (`EffectInstance` gains the card's own pose clock; `main.cpp` advances it from the card's age; the renderer binds `pose` as it already does for projectiles) and the two open questions.

- **Air dash accepted by the owner (2026-10-28, live play; tier 3).** Owner verdict after playing the V3-29/V3-30/V3-32 build: *"Quite good the air dashes feel just like the original game! i see no defects on those!"* That closes the D2/D3/D4 intake — momentum, facing, the gated travel window, the recovery descent and the hold-to-lift arm all read correctly in play. It is an acceptance of behaviour, not a claim of original-runtime parity, and the air dash's two structural remainders stay open and recorded in V3-31: the phase-2-only ground test into state 44, and the dash completing into state 43 rather than the port's Jump (which re-arms the row-41 hover). Neither is visible in ordinary play yet; both are named limits, not defects the owner reported.

- **D4 fixed — V3-32 `+0x280` identified as the jump-held counter; the air dash lifts while it is down.** The arm was blocked on identifying the word, and identifying it also corrected a mislabel the contract carried since V3-25: `+0x280` is **not** the `+0xa0` freeze word but slot 0 of an 8-word held-input counter array at `+0x280..+0x29c` (input object at `+0x240`), incremented while the bound key is down and zeroed on release by the per-frame poll `FUN_00657390` (asm `0x657478-0x6574cb`, no actor-state gate), with a one-frame release mirror at `+0x2b0`. The admissions use it as a 3-frame press window (`[0x280] == 3 || 0 < [+0x2b0] < 3`, asm `cmp dword [reg+0x280],3` at `0x43f2af`), grounded to row 40 and airborne to row 30; row 390's hold stance exits on `[0xa0] == 0`, proving it is a held state, not an id. Nothing in rows 30/41/42/43 writes it, so it stays non-zero through an air dash whenever the button is held — a tap releases in two frames and the arm never fires. **Done:** while it is non-zero and the phase is below 2, the dash's vertical gains 0.5/tick up to 8.0/tick and the meter pays an extra 3; with the button up the vertical bleeds back to zero, which is the hang the port had hard-coded. **Verification:** holding jump through a dash measures exactly **14/update in phases 0-1 and 11 in phase 2**, y rising 19.5 → 62.5 by the transition and on to 85 before the dash ends — the accumulator carrying over as `:423-425` describes. Case F's lift variant requires 10 updates at exactly 14, 3 at exactly 11, none above 14, a rise over 5, and that the recovery phase is reached. Suite **83/83** excluding the known `device_isolation_test` flake; fixtures 29/30/47 unchanged. Contract V3-32; `PILOT-SEAM.md:1467` already had the mapping and now the contract agrees with it. Remaining from V3-31: the phase-2-only ground test into state 44, and the dash completing into state 43 rather than the port's Jump.

- **Air dash audit — V3-31 what remains unmodelled.** A parallel read of case `0x1e`/`0x2b` plus the transcribed body confirmed V3-29/V3-30 (slide 16.5, steering 60/2 deg, fall 0.5/tick^2, release on `5 < +0x3a`, hang floor) and listed five remaining divergences: **(1)** the climb arm — when byte `+0x280` is non-zero the vertical adds 0.5/tick up to a cap of 8.0/tick and charges an extra -3 meter, so an air dash can rise fast at extra cost, absent from the port; **(2)** phase 2 subtracts from that accumulator, so a dash that exited phases 0-1 climbing keeps rising ~16 updates — inert today, must ship with (1); **(3)** the ground test lives only in phase 2 and goes to state 44, the air-landing row, which the port never enters (it ends the dash on touchdown and goes to Idle) — a structural gap, not a constant; **(4)** the dash completes into state 43, not the port's Jump, which wrongly re-enables the row-41 hover; **(5)** state 41 suspends gravity while the button word sits in 1..59 — the port's +0.2/tick climb comes from the *horizontal* `+0x15` ramp, not a vertical rate. Items (1), (2) and (5) all wait on identifying byte `+0x280`; (3) and (4) are state-model work. Also noted: `battle_air_dash.hpp`'s tuning defaults (15.5 speed, 9 drain) contradict both its own transcribed body and the dump (16.5, 11); the port already uses the body's values. Contract V3-31. No code changed in this entry.

- **Air dash shape — V3-30 gated travel section, descent and release rule.** Testing V3-29 exposed that the air dash never reached its recovery phase at all; the 20-update `kDashFrames` timer was hiding three separate defects. (1) Row 30's travel set declares the `+0x20` hold, so neither the clock nor the completion predicate can end it — the body counts its own visits in `+0x3a` and advances once `5 < counter` and either no direction is held or the meter is empty (`:413-420`); holding the stick extends the dash, which is what makes it steerable. (2) Phases below 2 floor `+0x10` at zero (a hang) while phase 2 subtracts `+0x16` with no floor — a real descent the port never ran; `kGravity` is 1800 u/s^2, exactly the body's 0.5/tick^2, so only the hang window needed narrowing. (3) The row is 10/15/10 = 35 updates and was cut at 20. The pilot's airborne dash is now phase-driven like the ground ones, scoped to the pilot path so `fighter_script_test`'s meter-less air-dash case keeps the legacy window. **Verification:** measured 5 hang updates, a 6-update steerable travel window, then a descent from y=16.5 to the ground; Case F now also requires the descent and climbs to y>40 first so the momentum carry still has airborne ticks to observe. Suite **83/83** excluding the known `device_isolation_test` flake; fixtures 29/30/47 unchanged. Contract V3-30. D4 remains open, and with it the `+0x10` climb arm that the same word gates.

- **D2 + D3 fixed — V3-29 the air dash points along the input and keeps its momentum.** Both reports were the same state and the same misreading. **D3:** case `0x1e` sets the movement angle to 0 — along the actor's own angle — and calls `FUN_00421780` every update (`:412`, `:427`) with `+0x874` = 60 deg/tick in phase 0 then 2 deg/tick; that function steers `+0x64` toward one of eight bearings built from the **held-input words** `+0x278`/`+0x27c`, not toward the target. The port resolved the direction against the target axis and left `m_facing` at the target bearing, so she slid sideways facing the enemy. Now the airborne dash takes its direction from the held axes, faces it, and re-steers at 60 deg then 2 deg per tick. **D2:** case `0x1e` completes into state 43 and case `0x2b` never writes the horizontal speed `+0x15` or the angle `+0x18` — it only steers at 1 deg/tick and integrates the vertical — so the slide survives. The port recomputed velocity from the stick and zeroed it with nothing held, hence the straight drop; `m_airDashCarry` now carries the dash's speed and direction through the following airborne state, cleared wherever the air dash re-arms. **Also corrected:** the air dash speed was 20.0/tick where the body writes `0x41840000` = 16.5/tick. **Verification:** new Case F jumps, double taps Right airborne with the opponent at +z, and requires row 30/set, more than 1 rad between yaw and target bearing, and more than 20 units of horizontal travel after the dash ends; reverting the facing work fails (`facing -0.002520 vs bearing -0.010770`) and reverting the carry fails (`covered 0.000000 units`). Suite **83/83** excluding the known `device_isolation_test` flake; fixtures 29/30/47 unchanged. Contract V3-29. Remaining in the intake: **D4**, the air dash's `+0x280`-gated extra -3 meter arm.

- **D1 fixed — V3-28 the side step now arcs toward the target.** Owner report: both side dashes moved in a straight line along the input direction instead of curving toward the targeted enemy. The port had the mechanism available and collapsed it: `FUN_0043ffc0` case `0x17`/`0x18` writes the movement as **±90 relative** to the actor's target-facing basis (`:265-271`), and that basis is refreshed every update (the port's own `m_inputFacing`), while `try_dash` froze `target_relative(±1,0)` into one world vector for the whole row. **Done:** `m_dashSide` records the axis at admission and the Run movement step re-derives the direction from the live basis each tick, so the path bends as the bearing rotates. Measured on the pinned scenario: path length unchanged at **382.90**, displacement along the tap 380.61, displacement toward the opponent **35.80** where the old code gave 0.45 (tap drift only) — the arc is subtle at 2000 units and steeper up close, which is why the owner sees it as a curve. **Verification:** the gate test now measures path length separately from displacement and requires the lateral gain, the shorter x, and that the first update still leaves along the tapped axis; disabling the re-derivation fails it (`z stayed at 0.450308`). Suite **83/83** excluding the known `device_isolation_test` flake; fixtures 29/30/47 unchanged. Contract V3-28. Committed and pushed. Remaining defects in the intake: **D2** air-dash momentum, **D3** air-dash facing, **D4** air-dash -3 meter arm.

- **Defect intake 2026-10-28 (owner, live play; tier 3 observation, nothing recovered yet).** Three new reports, recorded before any of them is worked, in the owner's words condensed: **(D1) side dashes travel in a straight line** — both sides should instead move in a **circular arc toward the targeted enemy**, not along the input direction. **(D2) air dashes do not apply momentum** — when one ends the character drops straight down instead of carrying the dash. **(D3) air dashes should point where the dash was input**; the character currently always faces the target. Plus the already-recorded **(D4)** the air dash's extra -3 meter arm needs the byte-`+0x280` word, whose identity is unresolved (see V3-25). Order of work: **D1 first** (same state as the just-finished side step, so the context is hot and the blast radius is rows 23/24), then D2/D3 together as one air-dash pass, then D4. None of the three has a fixture or a pinned expectation yet; each will need one before it can be called fixed. Nothing implemented for D1-D4 at the time of this entry.

- Global row end — **V3-27 the completion predicate ends a row one update before the tail rule.** Closing the open question V3-26 left behind. `FUN_004218c0` is `period <= entry_frame + 1` **and** `sectionCount - 1 <= phase`; `FUN_0063bf40` is just `this + 0x10`, the section count `FUN_00421100:15` caches at every phase change. The record question is also closed: `+0xade4` (tail) and `+0xade8` (predicate) hold the **same** pointer — `FUN_00421410:31` stores `param_1 + set*0xe + 0x1d78`, an expression with no track index, so both tracks point at one per-set record — so the two sites read one period and differ only in the comparison. The port used the tail rule for the last section too, so **every row ran one update long**. **Done:** explicit early completion for the last section using the frame the update entered with; it does not run on a held-clock tick, matching the body's early `FUN_00421100` return. **Verification:** the whole suite moves by exactly one assertion — Rena+0's side dash 39 -> **38** updates — and nothing else in 83 tests changes, which is the correct signature of a one-update truncation of a row's end; reverting the predicate fails the pinned row (`update 38 must end the row on Idle`). Suite **83/83** excluding the known `device_isolation_test` flake; fixtures 29/30/47 unchanged. Contract V3-27. Phase timing is now three separately cited rules: window length (V3-26), between-section advance (strict `<`), row completion (this entry). Nothing pushed.

- Global period rule — **V3-26 the engine truncates the clip period; the port rounded.** Follow-up after the meter work, found while checking what "phase 2 lasts 24" actually rests on. The saved disassembly settles it: `0x41e839` divides `GetPeriod` by 0.016 and `0x41e83f` calls `0x66b668`, which is not a rounding helper but the compiler's own float-to-int conversion — **1148 call sites** in the image, and its body (`0x66b668-0x66b6c5`) forms the residual `x - round(x)` and corrects it with `add ecx,0x7fffffff; sbb eax,0`, i.e. truncation under any FPU mode. The bundle agrees (`actor_animation_clock.hpp:17-22`). The port used `std::nearbyint`, which is right only for whole-number or round-down ties, so roughly half the clips in the game ran one update too long. **Done:** one shared helper (`gameplay/animation_period.h`) now feeds `advance_animation_phase`, the pre-emptive last-section exit, the activation-overlay window and both adapter windows; the duplicated arithmetic went with it. A zero window stays a real window (the source's test is strict), so the helper returns -1 for "cannot derive" and 0 for a genuine zero — an existing synthetic half-update case in `melee_rules_test` caught that distinction on the first attempt, which is exactly why it exists. **Approved by the owner before applying** because it is the first *global* rule change in this work and it touches a frozen combo: measured blast radius is Rena+0's side-dash recovery 24 -> 23 (row 40 -> 39 updates) and two Akane+0 ribbon observations moving one frame each with their in-phase tick unchanged — the signature of the preceding phase shortening, not of a different window shape. **Verification:** suite **83/83** excluding the known `device_isolation_test` flake; fixtures 29/30/47 unchanged. Docs: contract V3-26, plus `ANIMATION-SETS.md` and `ANIMATION-DATA-AUDIT.md` corrected (they stated the rounding rule as fact). Still open: `FUN_004218c0` completes on `period <= frame+1` while the tail advances on `period < frame`, and whether `+0xade8` and `+0xade4` carry the same period is not settled. Nothing pushed.

- Side-dash meter — **V3-25 the ground dash charges only before its recovery phase.** Owner asked for the meter usage to be tracked before implementing. Two read-only agents mapped the recovered rules and the port in parallel; I verified every claim they made against `FUN_0043ffc0.c` before changing anything, and settled the two questions they could not (whether the side rows carry a meter exit, and where the drain sits relative to the clock). **Done:** rows 23/24/27/28 drain -12 only while the phase is below 2 (`FUN_0043ffc0` :195/:257-259/:309-311/:355); the port billed every Run update, so the 22 recovery updates spent 264 meter the body never charges — 480 total instead of 216 on a right side dash (1000 → 520 before, 1000 → 784 now). Air dash 30 is unchanged: its body guards `phase < 3`, which is every section of its three-phase row; its extra -3 was left as a named limit at the time. **CORRECTION (V3-32): the field it needs is byte `+0x280`, the jump button's held-frame counter — not `+0xa0`, the freeze word. It is now implemented.** Also settled: states 23/24/27/28 have **no** meter exit (only the forward and air dashes leave phase 1 on `+0x834 < 1`), so the port was already right not to end the dash early, and adding one would have been wrong. **Verification:** the gate test now samples the meter per dash update — 988…784 across updates 1-18, flat 784 through 40, flag-off control at 1000 — and the guard's absence fails it (`the recovery phase must open at 784, got 772`); suite **83/83** excluding the known `device_isolation_test` flake; fixtures 29/30/47 unchanged. Contract line for the rate list amended with the phase qualifier. Docs: contract V3-25. Nothing committed yet; the tree is otherwise clean.

- Right-dash follow-up 3 — **V3-24 sparse clips retain the previous pose: the side-step travel is FIXED and the owner confirmed it live.** Root cause was not the clip. The right row's travel tag (set 23, `Anim-101`) is **sparse**: 22 of 78 frames — right arm, left leg, hands, props; no left arm, spine or root. The native controller keeps its skeleton between updates and a bound set writes only the bones it names (`prepared_actor_controller_pose.hpp:27`, `ActorSkeleton&` patched per named bone; `actor_controller_pose.hpp:42` — "sparse sets leave unnamed matrices intact, as the native D3DX controller does"). So the travel pose is a *composition*: the sparse clip's bones over whatever the startup clip left. The port rebuilt every pose from bind, collapsing the left arm to the mannequin stance — exactly the owner's "left arm forward and not visible". **Done:** `Controller` retains its evaluated local pose and seeds from it, clearing only on a rig change; a Case E regression samples `Bip01_L_UpperArm` through bind → startup → travel and requires travel == startup (dot 1.000000) with startup != bind so it cannot pass vacuously. Temporary switches removed (`DAYBREAK_DASH_TRAVEL_CLIP`, the pose probe and the A/B flag; `grep getenv` in fighter.cpp = 0). **Verification:** suite **83/83** excluding the known `device_isolation_test` flake; fixtures 29/30/47 unchanged; owner confirmed the live side step is correct. **Two process findings that cost real time, both recorded:** (1) the object owning the header's implementation (`src/assets/assets.cpp`) was **stale** — last built 2026-10-11 while the tree had moved on — so a test linking the library exercised old code while a standalone probe from the same header showed the new behaviour; deleting that object exposed the real result. Follow-up check: the dependency itself is sound (`touch xmodel.h` makes ninja rebuild the object), so this was a stale artefact, **not** a systemic hole; the working rule is that a header change which appears inert means suspect the object file, not the header. (2) `--out` captures never exercise the live pose path for a match (`advanceAnimation` is skipped when capturing, `main.cpp:6345`), so captures drew the load-time pose and my A/B was structurally blind — the earlier "0 pixels, no effect" reading was an artefact of the instrument, not evidence about the change. **Lessons recorded in the contract:** a clip index is not evidence of clip content (the same `Anim-NN` name has different channels in `00.X`/`01.X`/`02.X`), and a "missing animation" can be a runtime composition rather than missing data. **Still open:** the meter drains on every Run update instead of only before recovery; set 24 rounding vs truncation; side-dash movement/meter rows unchanged. Nothing committed or pushed.

- Right-dash follow-up 2 — **V3-23 travel distance: the side step now covers the recovered ~383 units, not 600.** Owner's verdict on V3-22 was that the speed reads right but the step **goes about twice as far** as the original, and that the travel portion of the three-part animation still looks wrong. The distance half is source-backed and now fixed: the row body seeds 20.0 on the first update and bleeds 0.5/update below phase 2 (floor 12.5), then 0.7/update in recovery (floor 0) — `FUN_0043ffc0.c:257-286`, bundle `dash_native_bodies_20260929.hpp:177-214`, roster `battle_roster_side_dash.hpp:9-10`. The port held `kRunSpeed` (15.0/update) for the whole row: the same 40 updates at the wrong speed, 600 units instead of 382.9. That is also why the animation read as wrong — a correct clip under a 57% over-speed slide looks like the clip is wrong, which is exactly how the owner described it. **Done:** pilot-only per-update profile for rows 23 **and** 24 together (identical profile data, one code path; fixing one side alone would have made the steps visibly asymmetric). COM and flag-off keep the constant legacy speed. **Verification:** the gate test now pins cumulative travel to 380-386 units (measured 382.9) plus an assertion that the 600-unit constant cannot return; the V3-22 clock cases still pass; suite **83/83** excluding the known `device_isolation_test` flake; fixtures 29/30/47 unchanged. **Still open:** the meter drains on every Run update instead of only before recovery; set 24's duration is 24 under x87 rounding and 23 under the bundle's truncation; the body exits on `frame+1 >= duration` while the port keeps the strict test. The one thing this patch does **not** claim to fix is the owner's animation-content complaint — if the travel clip still reads wrong now that the ground speed matches, the next step is that clip's content, not the clock or the distance. Nothing committed or pushed.

- Right-dash follow-up — **V3-22 side-dash clock: the missing extra increment is in, with a failing-first regression.** Owner approved proceeding through automated verification. Two read-only investigations traced the full recovered body and the production path; I checked `FUN_0043ffc0.c:246-292,2439-2443` and the bundle body myself. **Done:** the right side step now advances its phase clock the way the row's body does — a second increment to both counters when the entering primary clock is divisible by 9, before the common tail's ordinary one — so the sequence is 2,3,…9,11,12 instead of 1,2,3,… and the sections end on one-based updates 7/18/40 instead of 8/21/46. Scope is pilot + grounded Run + row 23 only; left (row 24's body carries the same rule) is a named follow-up, and the flag-off path deliberately keeps the old single increment. Also removed the `DAYBREAK_DASH_TRAVEL_SET` experiment: it swapped clip, duration and playhead rate together, so no verdict taken under it measured the clip, and it could not A/B the clip alone. Clip identity was never the fault — the executed trace already bound 22→23→24. **Verification:** new Cases in `rena0_pilot_gate_test` capture 40 one-based updates (phase, set, elapsed, state, both controller tracks = elapsed·0.016) with explicit entry-2, transition-7/18 and Idle-40 assertions, plus pilot-left and flag-off entry-clock-1 controls. RED before the fix (`FAIL: pilot right dash entry must sample clock 2…`, exit 1) then GREEN (exit 0); suite **83/83** excluding the known `device_isolation_test` flake; fixtures 29/30/47 unchanged. **Limits, all source-backed and deliberately not in this patch:** worth noting the previous entry's "phase 0 is 8 frames both in the port and under the recovered formula" was measured on the wrong clock — the body's own extra increments shorten it to 7, which is the owner's "first part should end much earlier". Still open: the side dash moves at a constant 15/tick where the body brakes 19.5→12.5→0 (production update 1 moves 15.0 vs the body's 19.5); the meter drains every Run update instead of only before phase 2; set 24's duration is 24 under x87 rounding and 23 under the bundle's truncation, unresolved; and the body exits on `frame+1 >= duration` while the port keeps the strict `period < elapsed` test. Evidence tier 2 (recovered code + addresses) and tier 4 (install-backed regression); no original-runtime or visual-parity claim — the owner's visual verdict is the next step. Nothing committed or pushed.
