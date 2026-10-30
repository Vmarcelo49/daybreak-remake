# Questions for the owner

The destination for "stop and ask" ([`../AGENTS.md`](../AGENTS.md); task list and
work reports in [`DIRECTION-STATUS.md`](DIRECTION-STATUS.md)). One entry per
question, newest last. While a question is open, mark the affected claim
`TODO(question NN)` in code or docs and either take the next allowed task or end
the session — never invent work to stay busy.

Format:

```
## Q<n> — <short question> (YYYY-MM-DD, agent/task)
- **Blocks:** what cannot proceed
- **Tried:** what was checked, with paths and commands
- **Options:** the concrete choices, if known
- **Default if unanswered:** what the agent will do meanwhile
```

Entries keep their original text and answers. Where the 2026-10-14 plan revision
changes what an old answer implies for current work, the implication is marked
**superseded** inline; the historical record is not rewritten, and no answer is
recorded that the owner did not give. Current plan: [`DIRECTION.md`](DIRECTION.md).

## Open

## Q26 — Implement the shared knockdown/tech/get-up system for the pilot? (2026-10-29, owner-reported gap)
- **Blocks:** the "Rena+0 is perfect" claim. The port only has 118/119 -> 120 -> Idle; the original also has the Jump-held landing tech (45), the 120 -> 124/128 choice, 30-tick get-up invincibility (124..129/194), the down meter (`+0x7c0`, 120-tick window, 30 i-frames at >=100), 103/203 fall-back, the flagged 121 ground roll and 133 wall bounce. Every one changes combo routes and wake-up pressure. Evidence and the port gap: [`reports/knockdown-getup-2026-10-29.md`](reports/knockdown-getup-2026-10-29.md).
- **Why it needs the owner:** the implementation edits the frozen decision path (`fighter.{h,cpp}`, reaction scripts) and adds a shared system, not a Rena+0-only rule. The Q24 exception covers only the delayed reaction rows.
- **Options:** (a) authorize the staged plan in the report (rows/timers first, then landing tech, then the down meter, then the shared extras) with the same fail-first test rule; (b) authorize only the landing tech 45 as the minimum change to the claim; (c) defer and keep the gap named in `DIRECTION-STATUS.md`.
- **Owner response (2026-10-29):** authorized the full staged plan (option a), and then retired the "global work is frozen" reading entirely: any change that directly or indirectly affects Rena+0 is pilot work and proceeds without an exception (`AGENTS.md`, pilot-scope rule). Recorded in `EXCEPTIONS.md` Q26 with the scope from the report; the global shared system is explicitly in scope because the owner named it as a blocker for the "Rena+0 is perfect" claim.
- **Default if unanswered:** do not edit the frozen path; the report stands as the evidence and the gap stays named. TODO(question 26).


## Q25 — Extend the projectile behavior table to the remaining shipped rows? (2026-10-29, frame-data audit)
- **Blocks:** full frame-data coverage of Rena+0's shot family. The powered taps launch item rows 6/7 (`parameter 60/70`) and state 407 launches rows 4/9/13/14 (`40/90/130/140`); none of those parameters has an entry in `kProjectileBehavior`, so they fall back to the provisional per-tier tuning instead of the recovered motion, lifetime and wall-child rules. The other rows are covered: 0/1/2/3/10/11/12/17 and the two stage explosions (row 8→10, row 2→3).
- **Evidence available:** the reconstructed switch (`rena_projectile_switches.hpp`, tier 3) covers all 18 registrations, and the original function `FUN_005f91c0` is addressable in the binary for the disputed cases (tier 2). This is a table extension, not a new mechanic.
- **Why it needs the owner:** `projectile_behavior.h` is the frozen decision table. The Q23 exception covers only row 8→10, and Q24 only the reaction rows; neither reaches these six parameters.
- **Options:** approve a scoped exception for the six parameters plus their tests (recommended), or leave the fallback documented as a named limit.
- **Owner response (2026-10-29):** approved the scoped exception; recorded in `EXCEPTIONS.md` Q25.
- **Tier-2 verification done (2026-10-29), and it found a model gap.** `FUN_005f91c0` confirms: 0x28 → speed 30, lifetime 480, initial yaw +45°, wall child 5; 0x3c → vertical 20, speed 45, lifetime 240, child 5; 0x46 → speed 45, lifetime 240, child 5; 0x5a → speed 30, yaw -45°, lifetime 480, child 5; 0x82/0x8c → speed 25, yaw ±60°, lifetime 480, child 5. The offsets are written to `+0x30` (an initial yaw offset relative to the aim) and the steering steps (`FUN_0042db10(0, step)`) are offsets in the same angle space as `+0x64`, while `ProjectileBehavior` can only set a visual `modelRoll`/`randomYaw` and treats its turn fields as radians. The unit is now settled: `FUN_0042db10` wraps `+0x64` within ±180 and steps by `param_3`, so these offsets are **degrees**, not radians. Applying the constants now would either drop the ±45/±60 launch yaw or convert degrees to radians without a model that means degrees.
- **Implemented (2026-10-29):** `ProjectileBehavior` gained `initialYaw` (degrees added at
  spawn) and `turnGrow` (degrees/tick per counted tick, capped by `turnCounter`). The six
  parameters are registered: 40/90 at speed 30 and 130/140 at speed 25 (all lifetime 480,
  3-degree approach, wall child 5, initial yaw +45/-45/+60/-60); 60/70 at speed 45,
  lifetime 240 and the growing step `0.25 + 0.01 x min(120, tick+1)`. `animation_data_test`
  checks each row's per-update speed, initial yaw, wall child and row 6's lifetime
  boundary. **Still approximate, and named in `projectile_behavior.h`:** 0x3c's `+0x34`
  vertical 20, the sub-degree inner steering (0.0035/0.004 x counter), the `FUN_0042dac0`
  aim jitter and the 0xf/0x10 particles.


## Q24 — Implement the latent reaction rows 104/105/204/205? — **ANSWERED 2026-10-29: implement**
- **Owner response:** "Q24, implement agora, pode continuar." The bounded four-row
  correction is recorded in [`EXCEPTIONS.md`](EXCEPTIONS.md) Q24 with its expiry.
- **Tried (before the change):** Static read of `FUN_00428510` cases 0x68/0x69/0xcc/0xcd.
  Phase 0 is an eight-frame gated clip (`+0x20 = 1`), so the generic tail never advances
  it; each handler waits until the phase frame is greater than 0x3c before seeding motion
  in phase 1. 105/205 take `combat[18]` as the slide and `combat[17]` as the lift with
  0.3 gravity; 105 approaches -4 and 205 approaches +4 (0.25 a tick); touchdown
  binds 118/119. Parsing
  every `NN.dat` in the install: Rena+0's contact rows name only 100/101/113/114/115/
  130/131, and 105/204/205 appear in no file at all (104 only in `ohishi/02.dat`).
- **Implemented:** the gate now holds those four rows through phase 0, the phase-1
  transition seeds the recovered law, 205 gained its entry with its +4 floor/0.25
  decay, 105 gained the -4 floor, and 121/221 gained their 0.25 settle. `melee_rules_test` injects each row through
  `take_damage` (documented as injection, not shipped contact) and asserts the 61-update
  standstill, the 62nd-call transition, the per-row decay and the 118/119 touchdown. The
  same test fails at the transition assertion when the new branch is disabled.
- **Limits:** no tier-1 evidence; the port maps the recovered per-row seed signs
  (0x69 negates combat[18], 0xcd adds it; 0xd8 alone stays negated) into its rotated
  back frame, which is a tier-6 mapping of a tier-2 rule; the rows remain unreachable
  from any shipped contact, so this is latent-path coverage, not pilot behaviour.

## Q23 — Reconcile the approved melee fixture with recovered attacker hitstop, and scope projectile work? (2026-10-29, frame-data audit)
- **Blocks:** an honest green pilot fixture run and changes to the approved acceptance expectation; extending the frozen Rena+0 projectile decision table for powered charge row 8.
- **Tried:** `FUN_00637950:307-308` writes combat[9] to attacker hitstop and combat[10] to victim; the shipped Rena+0 row 300 contains 6 for each. A failing-first install-backed test now checks the attacker clock. The unchanged `rena0-hit-ground-300.fixture` expects recovery at tick 22 and fails after the fix; a scratch port trace sees recovery beginning at tick 26. The fixture repeatedly resets/repositions its dummy, so this is a port observation, not an original-runtime trace. The approved contract must not be silently changed. Separately, powered projectile row 8 has radius zero and the current projectile table lacks its wall-child behavior; the reconstructed table describes child row 10, but the relevant decision-table work is frozen without an allowed scoped exception or cited pilot blocker.
- **Options:** approve a versioned correction to the melee expectation after reviewing its evidence (and, separately, a scoped pilot exception for the projectile behavior), or retain the old acceptance baseline and direct a different integration approach.
- **Owner response (2026-10-29):** approved a versioned fixture correction with its port-observation limit, and approved a narrowly scoped exception for powered row 8 → child row 10. The owner subsequently explicitly requested that the agent record the narrow, dated, expiring exception on their behalf; see Q23 in `EXCEPTIONS.md`. No comprehensive parity claim.

## Q3 — Is Idle really move row 0? (2026-10-14, coordinator/AGENTS.md review)
- **Decision (owner, 2026-10-14):** leave the row in place but mark it as needing
  static research.
- **Blocks:** nothing. It is an evidence-strength question about a documented row.
- **Tried:** `ANIMATION-SETS.md` cited `FUN_0041de68`, which does not exist; the
  citation is corrected to `FUN_0041dcb0:57`, which calls `FUN_00421080` with a
  **field value**, not a literal `0`. The doc now says so inline.
- **Next:** static read of the reset caller and that field. Do not present the row
  as verified until then.

## Q11 — Can we snapshot the original's memory and restore it later to skip menus? (2026-10-14)
- **Asked by:** owner, as a time-saving idea; explicitly "not claiming it's possible".
- **Answered:** **no for a full process save state; yes for narrower forms.**
- **Why a full save/restore fails:**
  1. Memory is not the whole state. A live run had 26 threads with their own
     registers and stacks, plus the D3D9 device, DXVK's internal state,
     DirectSound buffers and Win32/Wine handles. Bytes can be restored without
     those; the threads then run against half-old state.
  2. Addresses move between runs. The same candidate struct appeared at
     `0x0717b538` in one run and `0x1afcc78` in another, and the live battle's
     actors sat at `0x086be378`, `0x11632fa8`, `0x133c33b8`, `0x15ea3668` —
     heap addresses that differ every launch. Saved pointers only survive if the
     *entire* address space is restored at the same addresses, which is process
     migration (CRIU territory), not a memory copy.
  3. Loaded resources are heap objects reached through pointers. A restored
     "in battle" state without them is dangling pointers; with them it is the
     whole-image problem again.
- **What is worth doing instead:**
  1. a **menu driver** — the documented flow with held keys, a screenshot check
     per step and the actor array as the "in battle" signal (proved 2026-10-14,
     ~11 inputs, ~40 s);
  2. **targeted field writes** once the match-parameter structs are mapped
     (mode/character/weapon/stage), so a few dwords replace the character-select
     screens — this is the useful 1% of the save-state idea;
  3. check whether `config.dat` persists the last selection, which would remove
     most navigation for free.
- **Not a blocker:** the harness needs *repeatable* runs, not instant ones, and it
  needs evidence — a key sequence and screenshots are evidence; an opaque memory
  blob is not.
- **Superseded implication (2026-10-14 plan revision):** the menu driver and
  targeted field writes are convenience for a bounded live observation, not a route
  to deterministic combat input; the plan needs neither
  ([`DIRECTION.md`](DIRECTION.md) §2.3, Phase 1 "Optional original observation").
  Historical note: the documented flow later did reach a match unattended
  ([`drive_match.py`](../tools/harness/drive_match.py)), which is entry/liveness
  evidence only.

## Q9 — How do we drive the original into a battle, and inject input? — **ANSWERED 2026-10-14**
- **Answered:** drive it with real input — `xdotool` keys **held ~2 s** so a 60 Hz
  frame always samples them — and verify each step by screenshot, per the owner's
  documented 11-input flow (recorded in `tools/harness/README.md`). Proven: the
  original went from the title menu to a live battle with four actors, and
  `+0xae04` ticked at 62.5 Hz. DirectInput memory injection is **not** needed.
- **Blocks (historically):** P1-13 and P1-12, therefore every tier-1 trace.
- **Tried:** the title screen leaves the actor array null, so a battle is required.
  Three routes exist: (a) a human clicks into a match while the poller samples —
  fastest and zero guesswork; (b) `xdotool` keys to the game window, using the
  menu flow the port already documents from RE in
  `remake/foundation/docs/FRONTEND-PLAN.md`; (c) memory writes, either `winedbg`'s
  documented `set {int}0xADDR=VAL` or `process_vm_writev`, once the input globals
  are identified.
- **Options:** (a) for the proof now, then (b)/(c) for the harness; or go straight
  to (b)/(c).
- **Default if unanswered:** (a) for the proof; input injection stays open.
- **Superseded implications (2026-10-14 plan revision):** driving the original into
  a battle and reading its live fields is a real capability (P1-13), but it is
  **not** deterministic combat input and no tier-1 combat replay follows from it
  ([`DIRECTION.md`](DIRECTION.md) §2.2). The plan retires frame-perfect original
  control and requires no input controller or DirectInput memory injection (§2.3).
  The `+0xae04` "62.5 Hz" reading is an animation frame counter that resets and
  wraps, not a monotonic update counter: it is not exact-cadence evidence and not a
  per-update trace (§2.2; §4 Phase 0 item 5). P1-12/P1-13 therefore no longer block
  acceptance — original-runtime parity is a separate claim, not the acceptance gate
  (§6).

## Q10 — How does `pika` fit, given `ptrace_scope=1`? (2026-10-14)
- **Blocks:** nothing; a convenience decision about which reader the harness uses.
- **Tried:** `pika` builds clean (`/home/marcelo/Projetos/pika/target/release/pika`)
  and `pika ps` sees the game, but reads go through its daemon and need either the
  `cap_sys_ptrace` capability or the daemon being the game's ancestor. The harness
  already reads directly with `process_vm_readv` after `PR_SET_CHILD_SUBREAPER`
  (proven), so pika is needed for *scanning* (AOB, pointer chains), not for reads.
- **Options:** (a) add a `pika spawn`/`--subreaper` mode so the daemon owns the
  game and needs no capability; (b) `sudo setcap cap_sys_ptrace=eip` on the binary;
  (c) keep pika offline (run it on a dumped memory image) and let the harness read.
- **Default if unanswered:** (c) — the harness reads directly; pika stays available
  for offline scanning.
- **Superseded implication (2026-10-14 plan revision):** neither a `pika spawn`
  mode, nor setting `cap_sys_ptrace`, nor standing up a scanning workflow is in the
  revised plan's scope. The reader and scans are historical capability evidence;
  new live attachment or scanning work needs separately scoped owner authorisation
  ([`DIRECTION.md`](DIRECTION.md) §2.2 and §4 Phase 1 "Optional original
  observation"; [`../AGENTS.md`](../AGENTS.md) original-binary rules).

## Q8 — Where are the reference's 59 compared field names? (2026-10-14, plan review)
- **Blocks:** the comparison contract (P1-10) and therefore every verdict.
- **Tried:** the shipped bundles contain only the count (`battle-comparison-summary.json`:
  `"fields": 59`; `VALIDATION.md` describes 15,872 actor rows × 59 fields and the
  defined/raw split). The comparison tooling was not exported; no field-name list
  exists anywhere under `.local-analysis/`.
- **Options:** ask the author for the list (`battle-comparison` generator); let
  P1-1 reconstruct it from the actor spine plus `catalogs/timing-hooks.json`'s
  field-access map; or both, and diff the two lists.
- **Default if unanswered:** reconstruct and present it for approval as part of
  `TRACE-SCHEMA.md`; the verdict stays blocked until the owner approves.
- **Superseded implication (2026-10-14 plan revision):** the author's 59 field names
  are **not** a prerequisite for the pilot. Phase 1 defines our own minimal
  independent contract from observable, pilot-relevant fields — explicitly not a
  reproduction of the number 59 — and the request to the author through the owner is
  not a blocking dependency ([`DIRECTION.md`](DIRECTION.md) §4 Phase 1 steps 2 and 3).
  Missing author material does not authorise inventing his contract, and "59" is not
  a sufficient schema definition (§5 items 3 and 4). The verdict is blocked on our
  frozen, owner-approved contract, not on this list; the task row that ordered
  reconstructing the reference's 59 names is superseded by the plan.

## Q12 — Will you request the author's existing verification material? (2026-10-14, plan alignment)
- **Asked by:** [`DIRECTION.md`](DIRECTION.md) §4 Phase 1 step 2 and §9 item 3 — the
  request goes through the owner; an agent must not reach outside the repository.
- **Blocks:** nothing. The plan says the request is not a blocking dependency, and the
  agent continues with the bundle and repository evidence already present.
- **Tried:** the bundle summary confirms the 59-field count, and it does not
  establish what else is available — field definitions, the defined/raw rule,
  capture tooling, initial-state/RNG setup, input banks and comparison code may or
  may not exist in the shipped material. The Phase 1 evidence inventory (F1-1)
  determines what is actually present, and anything absent is recorded as missing
  ([`DIRECTION.md`](DIRECTION.md) §4 Phase 1 step 1).
- **Options:** (a) you relay the request and pass back whatever arrives; (b) you decide
  the material is not obtainable and the pilot proceeds on present evidence, recorded
  as a coverage limit; (c) you name a different source for the material.
- **Default if unanswered:** proceed with evidence already on disk, label each contract
  field's provenance, and do not assume the author's material will arrive — never
  invent it.

## Q13 — Do you approve the pilot evidence contract and its coverage basis? (2026-10-14, plan alignment)
- **Asked by:** [`DIRECTION.md`](DIRECTION.md) §5 items 1 and 3, §4 Phase 1 steps 3 and 6.
- **Blocks:** adopting contract v1 as approved, the acceptance of any combo and pilot
  **integration** (2e–2f): the scoreboard headline stays `0/46` with no contract
  version until this is answered. Scoped offline work (2a–2c) and 2d's bounded
  resolver work are not automatically blocked; the plan sets these gates "before the
  pilot integrates". `TODO(question 13)`: [`SCOREBOARD.md`](SCOREBOARD.md).
- **Tried:** no draft contract exists yet — it is Phase 1 work. The plan fixes the shape
  already: acceptance against our own versioned contract, original-runtime parity a
  separate result that may remain unverified ([`DIRECTION.md`](DIRECTION.md) §6), and
  missing or skipped required cases failing acceptance instead of leaving the
  denominator.
- **Owner review 2026-10-16:** approval **withheld** on candidate v1 with four required fixes:
  a fail-closed required-case set; every acceptance field mapped to a case or declared
  unsupported; one consistent tolerance per observable; and companion documents that agree
  with the candidate. Candidate **v2** answers all four (contract §2b, §8, §9 and the
  updated scoreboard/document index). Offline work stayed authorised in the meantime:
  the owner allowed **P2-5** (offline body tests) and **P2-6** (isolated resolver, unwired
  to the default path) while approval is pending, with 2e flag integration still gated.
  **Next:** owner re-review of v2.
- **Options:** (a) approve the acceptance basis now, and approve the field matrix,
  tolerances and exclusions when the draft is presented; (b) approve the basis only
  after seeing the draft matrix; (c) require specific original-runtime evidence in the
  contract before any pilot work.
- **Default if unanswered:** draft the minimal independent contract and the first
  fixtures inside Phase 1, freeze a candidate for review without treating it as
  approved, and accept no combo. This
  file records no approval.

## Q14 — Option A or B, once the 2a seam audit reports? (2026-10-14, plan alignment)
- **Asked by:** [`DIRECTION.md`](DIRECTION.md) §5 item 2; the decision point is the seam
  count from 2a.
- **Blocks:** nothing in 2a–2c or the offline feasibility probe; it selects the route
  for pilot integration (2e) once 2a is reported. No seam audit exists yet, so the
  adapter's cost is unknown and a blind choice is not possible.
  `TODO(question 14)`: [`SCOREBOARD.md`](SCOREBOARD.md) phase table.
- **Tried:** [`DIRECTION.md`](DIRECTION.md) §2.1 records the bundle as promising, not
  proven: its validation covers combos 15+0, 11+1, 8+1 and 14+1 (not Rena+0), with
  35,777 classified raw differences and missing awake-air-dash and attack-cancel
  coverage. Feasibility is the pilot's question, not an established premise.
- **Options:** (a) Option A — adapt recovered bodies into the foundation behind the
  pilot flag (recommended); (b) Option B — adopt more of the reference actor/services
  core, which needs a new owner-approved integration scope; (c) stop and re-scope the
  pilot.
- **Default if unanswered:** Option A for the seam audit and offline feasibility work
  only. That default grants no integration permission: 2e still needs the approved
  contract and the agreed budget, and if 2a shows the seam needs most of the reference
  actor/services, the agent stops and presents Option B rather than growing an
  unbounded adapter ([`DIRECTION.md`](DIRECTION.md) §4 2a, §5 items 1–3).

## Q15 — What is the bounded pilot implementation budget before integration? (2026-10-14, plan alignment)
- **Asked by:** [`DIRECTION.md`](DIRECTION.md) §4 Phase 1 "Time and scope" and
  [`../AGENTS.md`](../AGENTS.md) attempt ceilings — the 3-attempt/2-hour ceiling covers
  focused investigations, not the whole pilot's implementation, and a bounded pilot
  budget is to be agreed before integration.
- **Blocks:** nothing in Phase 1, 2a–2c or the offline feasibility probe; it gates the
  start of 2e integration work.
- **Tried:** no budget is recorded in [`DIRECTION.md`](DIRECTION.md) or
  [`DIRECTION-STATUS.md`](DIRECTION-STATUS.md). The plan asks for implementation effort
  to be reported separately.
- **Options:** (a) a fixed cap for the pilot implementation (2e–2f, optionally 2d);
  (b) a scope cap — only the seam fields the 2a audit marks load-bearing; (c) no fixed
  cap, owner reviews reported effort step by step.
- **Answered 2026-10-16 (owner): option (c) — no fixed cap.** Implement step by step and have
  the measured effort reviewed after each row, stopping at any scope growth. This is recorded in
  the P2-0a row, which is now *settled*; it gates 2e/2f integration only, and effort is reported
  per row in the work log (P2-5 and P2-6 carry their own effort notes).

## Q16 — Which bounded mapping should follow the F1-5 probe? (2026-10-14, pilot agent/F1-5)
- **Blocks:** authoritative use of the compact control's resource, stop, angle and paired clocks; not the observation-only F1-5 case. `TODO(question 16)` in the draft evidence contract.
- **Tried:** [production probe](../remake/foundation/tests/rena0_locomotion_observation_test.cpp) uses explicit stop=0/slow=0 assumptions, stamina×10 and move-counter diagnostic proxies, observer-only angle seeds. Normal startup takes 60 updates at the declared 64 Hz. At Idle→Walk the proposal has speed 0/frame 0, while legacy moves 7.2 units/frame 1; on release proposal clocks reset to 0 while legacy frame is 1. Legacy move-counter stays 0 versus proposed secondary increment. Existing addressed [FUN_0043ffc0](../research/decompiled/FUN_0043ffc0.c) cases 0/10 support admission, speed and turn arithmetic, but do not settle production update ownership.
- **Options:** (a) next audit the paired-clock/update-order seam for Rena+0 only, using existing addressed research first; (b) prioritize resource/stop mapping instead; (c) retain this observer and complete the separate cadence task before extending cases.
- **Default if unanswered:** recommend (a), do not apply native proposals or expand coverage; contract/route/budget gates Q13–Q15 remain open.

## Q17 — Should the hardcoded ×64 per-tick→u/s conversions in `fighter.cpp` move to the documented 60× convention? (2026-10-16, pilot agent/P0-10)
- **Blocks:** nothing in Phase 0/1; it is a gameplay-behaviour question newly exposed by D15, not a cadence change. `TODO(question 17)` where relevant.
- **Tried:** P0-10 set `FixedStep::tickRate` to 60 and converted every test/doc statement. A tests worker then found ten hardcoded `64.f` conversions in `fighter.cpp` (`m_vy`/vertical attack channels: lines 1989, 2529, 2535, 2550, 2590, 2623, 2625, 2632, 2668, plus `4096.f` = 64² at 626) while `fighter.h:240-249` documents the port convention as **u/s = 60 × the tick literal** and `kJumpApexSpeed = 360` is written as "6.0/tick at the original's 60 Hz". No test pins either convention, so the suite cannot detect the discrepancy.
- **Options:** (a) treat the literals as per-original-update values and convert with the documented 60× convention (changes every combo's vertical attack motion by 64/60 ≈ 6.7 %); (b) treat them as per-port-tick values and convert with `FixedStep::tickRate` (behaviour then tracks whatever the port rate is); (c) leave them and record the inconsistency. Any of these changes combat movement, so it is not done inside a cadence commit.
- **Default if unanswered:** no change; the 72/72 suite result does not cover this channel, and it does not block F1-5 or the observer, both of which are grounded-locomotion only. Recommended: get the addressed-code evidence for the literals' unit before choosing (a) or (b).

## Q18 — Option A with a bounded `BattleWorld` façade for the charge case, or keep charge out of the pilot's first scope? (2026-10-16, pilot agent/P2-1)
- **Blocks:** P2-1's Option A/B verdict (`DIRECTION.md` §4 2a) and the scope of the charge-level case among the Phase 2 targets. Nothing else: locomotion, ground shot, melee admission, guard, hit/damage/KO and jump/air-dash bodies need only scalars, RNG, trig, steering and event sinks.
- **Tried:** bounded enumeration of the bundle's Rena-named and shared bodies (`PILOT-SEAM.md` §10-§11). The State-400 shot body and the 300-family melee selector are scalar/event machines; `battle_random.hpp` is the same MT19937 the port already carries. But `full_charge_native_world.inc.hpp:23-43` reads a `BattleWorld`: `world.actors.at(slot)`, `relationships.secondary_target`, `actor_bone_world`, `transform_actor_point`, `selected_weapon_socket`. The air-shot and jump families are large **generated tables** (19,727 + 3,591 lines), and their host-side scheduling is still uncounted.
- **Options:** (a) Option A with a **bounded world façade** (actors, relationships, bone/socket transforms, statistics) sized by the charge body alone, Option B only if that façade grows past the pilot's budget; (b) keep charge levels out of the pilot's first scope and record the exclusion, revisiting after the seam audit; (c) treat the world requirement as the Option B signal and re-scope the pilot to the reference simulation core.
- **Default if unanswered:** (b) is the safe default — it keeps the pilot's Option A path free of a new world abstraction, and the exclusion is explicit rather than a silent denominator change; the charge case returns only with an owner decision.

**ANSWERED 2026-10-16 (owner): Option (a) — Option A with a bounded `BattleWorld` façade sized by the charge body.** The façade must not grow past what that body needs; if it does, stop and re-present rather than extending it. The air-shot/jump host-side scheduling count still completes as part of P2-1, but the route question is settled.

## Answered

## Q1 — Bundle licence — **ANSWERED 2026-10-14**
Full permission from the author for anything; the project's own licence is open
("use what you want"). Bundle **code** may be vendored with attribution; decoded
original game assets stay untracked. `P2c-1` unblocked.

## Q2 — Silent launch of the original — **ANSWERED 2026-10-14**
Not needed. `--no-audio` is courtesy so verification does not disturb the machine;
audio is fine. No silent-launch procedure will be built.

## Q4 — Live cadence — **ANSWERED 2026-10-14: 60 Hz (D15)**
64 Hz came from general online-3D guidance and is irrelevant beside matching the
original for proper tests. `FixedStep::tickRate` changes to 60; D9's other content
stands. Task `P0-10`.

**Superseded implication (2026-10-14 plan revision):** D15 stands as the port's
60 Hz cadence decision, but the ~62.5 Hz animation-counter reading is not evidence
of the original's exact update timing, and the decision is not an implementation:
`FixedStep::tickRate` still reads 64 ([`DIRECTION.md`](DIRECTION.md) §4 Phase 0
item 5).

## Q5 — The comparison contract — **ANSWERED 2026-10-14: adopt the reference's posture**
59 fields per actor row with defined-versus-raw classification. The names must be
reconstructed (Q8); the owner approves the list before any verdict.

**Superseded implication (2026-10-14 plan revision):** "adopt the reference's
posture — 59 fields per actor row" no longer defines the schema. The
defined-versus-raw distinction stays useful; the field set, units, tolerances and
exclusions are our own minimal contract and need owner approval
([`DIRECTION.md`](DIRECTION.md) §4 Phase 1 steps 3 and 6, §5 items 1 and 3).

## Q6 — The open issues — **ANSWERED 2026-10-14: close the character/combat set**
27 issues closed on 2026-10-14 with a comment pointing at the plan; work is
tracked in `DIRECTION-STATUS.md` and `SCOREBOARD.md` only. Closed issues remain
readable and are reopened per combo if Phase 3 needs their detail. The Phase 3
acceptance template they shared is recorded in `DIRECTION-STATUS.md`.

**Superseded implication (2026-10-14 plan revision):** the Phase 3 acceptance
template recorded in `DIRECTION-STATUS.md` — per-combo completion validated in a
live match with real input compared against the original — predates this revision.
Combos are now accepted under the approved versioned offline/scripted contract, and
original-runtime parity is a separate result that may remain unverified
([`DIRECTION.md`](DIRECTION.md) §4 Phase 3 gate, §6). The task-list wording is
updated by its owners; this note records why the old template no longer gates.

## Q7 — Stale Windows-rematch line — **ANSWERED 2026-10-14: verify before editing**
Do not correct the docs from the issue's state alone; confirm on a real
Windows/Wine run that a rematch no longer faults, then fix the lines. Task
`P0-11`.

## Q19 — Correct v3's misattributed powered-air-shot spend before 2g? (2026-10-22, pilot agent/P2-8 re-audit)
- **Blocks:** a source-backed green recommendation under v3; **not** the already-recorded owner approval itself. `TODO(question 19)` applies to V3-1's `shot-gauge-spend` case and its fixture, not to the valid empty-tap voice.
- **Tried:** directly read the unchanged bundle's Rena+0 selector (`slot7_native_bodies_20260929.hpp:3-398`) and mobile shot executor (`battle_rena_mobile_shooting.hpp:216-221`), plus existing addressed listings `FUN_0043ffc0.c:1968-2040` and `FUN_00508a60.c:76-114`. Rena's powered 402 shot selects item row 7 at frame 13 without a 500-resource subtraction. The cited `FUN_00508a60` subtraction occurs after dash command 4/3 while already in state 402 and transitions to **state 30 (air dash)**, not to a powered shot. The corresponding bundle statements occur in `slot7_body_5_1` at lines 6466-6501, not `slot7_body_0_0`; no other combo implementation was changed. Current production `MoveOp::Launch` nevertheless subtracts 500 through `PilotCharge`, and the approved fixture pins that mistaken rule. A source-corrected scratch expectation fails at tick 25 (`charge_gauge exp 1000 got 500`), saved under ignored `local-data/harness/v3-gate-review-20261022/no-spend.before.log`.
- **Options:** (a, recommended) authorize a reviewed contract correction: remove the unsupported 402 spend and replace that required case with source-cited Rena+0 powered-shot/no-spend and genuine 403 recovery coverage; retain the same coverage obligations until the replacement is reviewed; (b) explicitly retain the 500 deduction as a provisional port rule, not recovered Rena behaviour. Do not silently delete the required case or relabel its passing result as source agreement.
- **Default if unanswered:** preserve the approved fixture, its fail-closed enforcement and current production spend; mark the claim contradicted, keep the verdict pending, and finish independent bounded enforcement/safety fixes. A two-counter stamina model remains unresolved integration debt; an owner observation about the visible meter does not prove their runtime coupling is correct.
- **ANSWERED 2026-10-22 — owner approved option (a).** Implemented as approved: the `PilotCharge` deduction and its policy were deleted from the production path, and `shot-gauge-spend` was replaced by two source-backed required cases — `rena0-powered-shot.fixture` (powered 402 launches bullet row 7, `charge_gauge` unchanged: `FUN_0043ffc0.c:2009-2014` with no subtraction) and `rena0-shot-recovery.fixture` (row-403 recovery, +40/tick clamped at 1000: `FUN_0043ffc0.c:2021-2040`). Coverage grew rather than shrank: 23→24 fixtures, 24→25 case rows, 40→44 fields, with `shot_bullet_row` added as an asserted observable (ground tap row 0 vs powered row 7). The correction also implemented and pinned the empty-ammo release window `0 < released < 20` (19 frames voice, 20 silent). Recorded in `PILOT-EVIDENCE-CONTRACT.md` V3-1/V3-7 and `PILOT-SEAM.md` §29. The split-stamina-resource limitation remained open at the time and was covered two days later
by **Q21**, which the owner answered by unifying the `+0x834` meter (implemented, V3-8).

## Q20 — Required Luna subagent runtime unavailable (2026-10-22, pilot agent/review)
- **Blocks:** further delegated bundle review under the user's GPT-6 Luna restriction, not ordinary source work by the coordinator.
- **Tried:** two read-only child reviews disclosed their actual runtime as `gpt-6.1-sol`, not Luna. The exposed subagent tools have no model-selection parameter. Delegations were stopped on disclosure; neither child edited files or ran builds. Their output is not represented as Luna verification; cited findings used in this round were checked directly against source by the coordinator.
- **Options:** supply a Luna-selectable delegation route, or explicitly permit the available subagent runtime for further review.
- **Default if unanswered:** no further non-Luna delegation; continue only bounded coordinator work without pretending the requested model was used.
- **ANSWERED 2026-10-23 — owner explicitly permitted the available subagent runtime** ("if you need more research you can use sub agents too"). Delegation resumes; every delegated result must still name the runtime that actually served it and must not be presented as Luna verification. Findings a delegated result contributes are re-checked against the binary by the coordinator before they enter a tracked claim.

## Q21 — Unify the split `+0x834` meter before the pilot verdict? (2026-10-22, pilot agent/scope)
- **Blocks:** nothing mechanically; it is the last *mechanism-level* divergence inside the pilot's accepted path. The verdict can proceed without it if the limit is accepted in writing.
- **Tried:** full source read of every writer/reader of the actor word behind `+0x834` (881 arithmetic sites in the adapted bodies, plus `FUN_0041f580`, `FUN_0043ffc0:2021-2040`, `FUN_00445ee0` and `guard_native_control.hpp`) and the port's two counters. The scope, the numbered divergences and the options are in [`PILOT-SEAM.md`](PILOT-SEAM.md) §30. Key measured facts: the recovered meter is 0..1000 with dash −12/tick, guard −10/tick, recovery +40/+5 and no passive refill; the port drains `m_stamina` (0..100, 1/10 scale) but refills `m_chargeGauge` (0..1000), which nothing drains — so `m_chargeGauge` is **inert** and the recovered "cannot attack with an empty meter" gate can never fire; guard drains 2.4× too slow (`rena0-guard-hold.fixture` pins exhaustion at tick 245 where the source rate gives ~100); `kStaminaRegenSec` 60/s has no recovered counterpart.
- **Options:** (a, recommended) unify into one source-shaped 0..1000 meter **behind `--native-actions=rena0`**, delete `m_chargeGauge`, re-pin the `stamina` expectations it changes, keep the legacy path, and record the air-dash state-30 branch and the fly drain as named limits if they cannot be closed in the same change; (b) mirror the two counters at 10:1 as an expiring stopgap; (c) document the divergence and proceed to the verdict with it accepted as a limitation.
- **Default if unanswered:** option (c) — nothing frozen is touched, the divergence stays recorded in §30 and in the scoreboard's open-limit row, and the verdict remains the owner's to give. Because (a) edits frozen files, it additionally needs an owner exception row in [`EXCEPTIONS.md`](EXCEPTIONS.md) naming `fighter.cpp`, `fighter.h`, `main.cpp` and the pilot tests; that row cannot be written by an agent.
- **ANSWERED 2026-10-23 — owner approved option (a).** Implemented as scoped: one source-shaped 0..1000 `m_actionMeter`, authoritative only when a `PilotMeter` policy is attached (`--native-actions=rena0` for Rena+0; the acceptance fixtures attach it directly); default path untouched. Guard exhaustion re-pinned 245 → 99, tick-59 stamina 75 → 40; shot fixtures re-pinned for the jump's own costs; gate test Case A rebuilt around the now-reachable empty-meter refusal. Recorded in `PILOT-EVIDENCE-CONTRACT.md` V3-8 and `PILOT-SEAM.md` §30.6. Full suite 84/84, pilot 13/13, seeded wrong-gate fails by design. **Still needed from the owner:** the `EXCEPTIONS.md` row for the frozen-file edits (dated, expiring, naming `fighter.cpp`, `fighter.h`, `main.cpp` and the pilot tests) — an agent cannot write it — and the 2g verdict itself.

## Q22 — How should the Hyper EX deal damage? (2026-10-29, overnight pilot session)
- **Blocks:** the pilot's most visible gap. The EX (row 350) is the combo's signature attack and it
  currently deals **no damage at all**, verified with the opponent at twelve distances from 40 to
  480 units and with the fixture's own `place_at_attack` helper (`swing_hits` 0, HP unchanged).
- **What is recovered:** `FUN_0043ffc0` case `0x15e` calls the contact **cut** (`FUN_00434bd0`) in
  its tick-0 block and never re-arms it (`FUN_00434b30` does not appear in the case), which is why
  the port's table carries `{350,-1,0,9999,MoveOp::ContactOff}` and why `m_contactDisabled` is 1 on
  every one of the seven ticks where the shipped data DOES carry a contact entry
  (`Bip01_L_Hand`, radius 30, frames 11/15/20/24/28/32/36 — the entries alternate with radius-0
  ones, so each window is one tick). The rule table's note reads: "350's damage is the
  particle/effect scatter, not a swing", and the body's particles are ids 320/350 at frames
  7/15/23/31 and 7/22/37 plus 340 at frame 56. The port spawns those as **visuals only**; it has no
  damaging effect entity.
- **Options:** (a) implement effect-carried damage — spawn the particle with a short-lived hit
  volume and resolve it against the opponent's two anchors, the reading the port rule implies, and
  the larger piece; (b) re-arm the melee contact for row 350 and let the shipped hand records do the
  work — small, uses data that already exists, but contradicts the recorded reading of the body;
  (c) leave it, accept that the EX deals no damage, and record it as a declared limitation of the
  pilot.
- **Default if unanswered:** (c). Nothing is invented, the gap is named in
  [`PILOT-EVIDENCE-CONTRACT.md`](PILOT-EVIDENCE-CONTRACT.md) V3-43 with measurements, and neither
  option is started without a decision because both change gameplay the owner has already judged by
  feel.
- **RESOLVED FROM THE EVIDENCE 2026-10-29 — no owner decision needed.** A bounded read of the
  damage chain settled it: the tick-0 call the port's rule cited is `add ecx,0x6a0` →
  `FUN_00434bd0`, which clears the actor's **trail** object, while the hit path reads the contact
  record pointer `char+0x10` (maintained by `FUN_004212f0`), transforms its anchors with
  `FUN_00420880` and resolves them in `FUN_00637950` (HP subtraction at `0x638a96`). So neither
  option above was needed: the `ContactOff` rule was a misreading and has been **deleted**. With it
  gone the EX lands and takes the opponent from 100 to 92 HP; restoring it returns zero hits.
  Recorded in V3-43 with the address table. The row's own length is a separate open item there.
