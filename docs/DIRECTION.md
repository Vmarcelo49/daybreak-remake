# Direction — finishing Higurashi Daybreak's character runtime

Original plan: 2026-10-14. Revised after review at the owner's request.

This document answers **what must be completed, in what order, using methods
agents can execute now**. The goal remains a playable modern port with faithful
character behaviour. The plan must not depend on agents playing the original in
real time or on a large new original-game automation project.

> **Execution status:** at the owner's request, the companion rules and task
> lists are aligned with this offline-first direction. This is not approval of
> an unwritten fixture/coverage contract, a green pilot verdict, or a lift of the
> existing freeze. Bounded baseline, evidence inventory and feasibility work may
> proceed through the task list; product integration waits for the explicit seam
> and contract gates. Historical work logs remain unchanged. Old tasks ordering
> tick-perfect original input, exactly 59 fields, or deletion before the verdict
> are retired, not fallback work orders.

---

## 1. Where the project is

The repository has two halves: a playable remake and a reverse-engineering
corpus. The platform, renderer, assets, front end and instrumentation already
represent substantial work. The character runtime is the bottleneck.

The original uses 46 character+weapon classes. `FUN_00649790` constructs them;
46 distinct vtables occupy `0x6a4e10`–`0x6a5518`, with stride `0x28`. The battle
update (`FUN_00634f60`) calls per-combo selection and execution slots. This is
not a problem that can safely be reduced to one generic fighter plus a few
unverified exceptions.

The original plan recorded:

- 0/46 combos audited complete;
- about 550 hand-encodings in a restrictive `MoveRule` vocabulary;
- animation decisions spread across seven row selectors and two binders;
- extensive decompiled character code, but little reviewed combat provenance;
- a previous DX9-remake capture bank that is **not** an original-game oracle.

These are the reasons to change the character integration method, not a claim
that every historical count or platform status has been reverified in this
revision. Current task state belongs in
[`DIRECTION-STATUS.md`](DIRECTION-STATUS.md), not in this diagnosis.

## 2. What the evidence actually supports

### 2.1 The recovered bundle is promising, not proven complete

The local `DaybreakRebuild` bundle contains recovered body modules, control
headers, dispatch and animation services that could replace the hand-encoding
bottleneck. Adapting them is the recommended approach, subject to the pilot.

Its validation reports 3,968 stage04 updates, four actors, 59 fields per actor,
and zero **defined** differences after correction. The fixture uses combos
15+0, 11+1, 8+1 and 14+1. It does **not** validate Rena+0 or all 46 combos.
The report also records 35,777 classified raw differences, missing awake-air-dash
coverage and no observed attack-cancel event. Zero differences and sufficient
coverage are separate requirements.

Sources in the local, untracked bundle:
`DaybreakRebuild-20261010/docs/VALIDATION.md` and
`validation/battle-comparison-summary.json`.

Portability of the source is encouraging, but neither compilation nor a low
count of Windows dependencies proves that its actor/services seam fits our
engine. **Feasibility is the pilot's question, not an established premise.**

### 2.2 Live memory access exists; deterministic replay does not

The existing harness has demonstrated Wine guest-memory reads, a way to obtain
reader permission by spawning Wine under a subreaper, live actor pointers at
`DAT_006cfae0`, and an unattended menu sequence that reached a battle.

Those milestones are useful, but distinct:

1. reaching a battle;
2. reading live memory;
3. obtaining coherent, update-indexed snapshots;
4. replaying identical consumed input and initial conditions.

Only the first two have supporting results in the current work log. A successful
menu run is not a robust state-driven driver or a deterministic combat replay.

**Actor `+0xae04` is an animation frame index, not a monotonic simulation
counter.** It resets on animation changes and can stop changing while idle.
The current recorder skips unchanged values, so it cannot be called a per-update
trace producer. See [`tools/harness/README.md`](../tools/harness/README.md) and
[`orig_capture.py`](../tools/harness/orig_capture.py).

Polling live memory may miss updates or mix values from different updates.
Running a poller inside a DLL does not by itself solve either problem. Such
output is **sampled original runtime state** unless coherence, update identity
and missing-sample detection have actually been demonstrated.

### 2.3 Real-time agent gameplay is not the verification method

**Owner constraint:** frame-perfect original-game input by agents is not viable
for this plan. Building a tick-synchronised original-game controller, save-state
system or complete capture/replay framework would be a substantial separate
project. None is a prerequisite, a default next task or a promised fallback.

Held keys and screenshots may bootstrap a match or answer a coarse named
question. They cannot establish exact input timing, cancels or per-update parity.
Video can show pose, facing and gross timing; it does not uniquely identify an
internal animation-set number or prove state-machine equivalence.

The agent works primarily on source, deterministic offline fixtures, our own
scriptable runtime and saved artifacts. It does not need to react at game speed.

---

## 3. Main focus and available methods

> **Replace the hand-transcribed character decision layer with recovered logic,
> prove the adapter on Rena+0 using bounded offline experiments, and make the
> evidence and remaining limits explicit before scaling.**

Three deliverables:

1. **A practical evidence contract:** named behaviours, fixtures, expected
   outputs, provenance, tolerances and coverage that agents can inspect now.
2. **A recovered-runtime pilot:** one combo behind a flag, with one binding
   owner and a quantified actor/services seam.
3. **A coverage-aware scoreboard:** accepted combos under the approved contract,
   with original-runtime parity tracked separately, never implied.

### Methods allowed on the critical path

| Method | What agents can do | What the result establishes |
|---|---|---|
| Recovered-code audit | Inspect addressed original functions, bundle bodies and actual game tables | Source-backed expectations; not a live execution claim |
| Offline body fixtures | Feed explicit actor context, input, RNG state and service results into selected recovered bodies | Repeatable body outputs for those conditions |
| Adapter differential tests | Run the same fixture through the standalone bodies and the integrated port path | Adapter equivalence to the recovered implementation, not independent original parity |
| Scripted port scenarios | Use our existing script/debug/capture paths with fixed inputs and explicit conditions | Product integration, binding and behaviour regression evidence |
| Existing original artifacts | Analyse captures, traces and prints already available, with their provenance and scope | Only the behaviours the artifact actually exposes |
| Optional bounded live observation | Use already-working reads or a short capture for a specific unresolved question | Sampled observations or coarse visual evidence, not exact replay |

Two paths sharing recovered source are not independent confirmation that the
recovery is correct. Report that limitation. A test expectation produced by the
same code under test is a consistency check, not independent ground truth.

Original-function execution tools may add evidence **only where an existing,
usable setup can be demonstrated within the normal attempt ceiling**. An
unimplemented Unicorn oracle is not a dependency or an excuse to start a new
emulation project.

### Reverse-engineering skill: focused original-binary evidence

Agents must load `reverse-engineer-anything` when a task needs evidence from the
original compiled executable, and follow its **REA CLI / Ghidra** workflow.
Use existing addressed research first. Fresh binary queries are for a named
pilot seam dependency, fixture expectation or demonstrated discrepancy, not an
unbounded survey of all 46 combos.

A typical investigation is: pin the binary hash → inspect the known function and
necessary callers/callees → check ambiguous decompiled operations against
instructions → save and validate the complete Evidence → derive a cited fixture
expectation. Keep observations, inferred field meanings, unresolved calls and
coverage limits distinct. Static analysis does not prove runtime timing or
original-runtime parity; `rea trace` follows static references, not execution.

Save full results under ignored `local-data/harness/`, validate exit status,
Evidence operation and target identity, and reuse results instead of repeating
expensive imports. Avoid concurrent writers to shared snapshot caches. The
normal investigation ceiling applies. The skill's examples use another game's
addresses; none may be assumed to apply to Daybreak.

Source-only adaptation, fixture runners and port tests use ordinary repository
tools, not REA. Loading the skill does not authorize target execution, runtime
instrumentation, frame-perfect input automation, annotation changes, tool
installation or integration setup. Any such action needs separately scoped
owner authorization; frame-perfect original control remains outside this plan.
See [`../AGENTS.md`](../AGENTS.md) "Original-binary skill routing" for enforcement.

### Adoption options

- **A — adapt recovered bodies into the foundation (recommended):** preserve our
  engine and replace the hand-decision layer. The seam audit determines viability.
- **B — adopt the reference simulation core more broadly:** consider if the bodies
  require much of its actor/services machinery. This needs an explicit owner
  decision and a revised integration scope; it is not automatically faster.
- **C — continue hand-porting:** not the default; the existing vocabulary and
  throughput are the reason for this revision.
- **D — derive missing behaviour from addressed original code:** a focused way to
  fill demonstrated gaps, not a restart of all 46 hand ports.

Bundle code permission was resolved by the owner. Adapted code needs attribution;
original game assets remain untracked. There is no unresolved licence gate for
bundle code in this plan.

---

## 4. Critical path

### Phase 0 — Establish a safe baseline

1. Review and park the existing WIP in reviewable parts, or leave it unchanged
   with a clear blocker. **Never discard an uncommitted diff.**
2. Inspect stale branches/worktrees and their unique commits. Removal is optional
   housekeeping, not a prerequisite for character validation; show the owner
   before any deletion under the repository's git rules.
3. Keep the freeze and D14 decision visible. Reconcile the changed verification
   tasks and gates after owner review of this document.
4. Pin the original binary before any original-side comparison: SHA-256
   `27e61475fbb3ea67f5058e3e0e6e93ad71d16a4d83fa42b02e605913a6a07f02`.
   A different hash stops original-side work.
5. D15 selects a 60 Hz port cadence, but a decision is not an implementation.
   At review, `FixedStep::tickRate` still reads 64. Apply and test the intended
   change deliberately after resolving overlapping WIP. Do not infer an exact
   original cadence from an animation-counter/wall-clock measurement.

**Gate:** a known baseline, preserved WIP, approved plan/task alignment and explicit
cadence status. No new character-rule work is authorised by housekeeping.

### Phase 1 — Assemble usable evidence, not a new automation platform

**Deliverable:** a controlled experiment using the port's production gameplay
library, a comparison/report format and an owner-approved coverage contract for
Rena+0. A separate simulation runner is not a prerequisite.

**First feasibility experiment (F1-5):** after the baseline/WIP review, drive a
real, equipped Rena+0 through grounded idle → walk → turn → stop, with a neutral
equipped dummy opponent. A device-free test links `foundation_gameplay` and
steps the real `Match`/`Fighter` path. Reset the match per case and step startup
normally; do not force Idle while leaving its startup timer active. Use the
port's declared fixed-step cadence and record it.

Run a reviewed, attributed adaptation of the bundle's compact idle/walk control
alongside that path: observe proposed outputs without applying them. Assert
source-backed behaviour and repeatability; legacy agreement is diagnostic, not
an original-behaviour oracle. Keep clocks/phase ownership legacy in this probe,
and label unresolved resource/stop/angle mappings rather than guessing. This
control is a reconstruction, not proof that the larger generated combat bodies
fit. No authoritative native-action flag or default-path replacement yet.

Reuse the regular port's `--live-debug` for optional visual inspection after the
automated probe works. Standalone scripts/`--out` disable movement collision for
historical comparisons; any open-field test must declare that scope. Do not
change those historical defaults to make this experiment work. Body-only unit
fixtures remain useful where they isolate a dependency, not as a separate-engine
requirement.

1. **Inventory available inputs and evidence.** Locate usable bundle fixtures,
   existing traces, addressed body code and service dependencies. A missing
   artifact is recorded as missing, not reconstructed by assumption.
2. **Request the author's existing verification material through the owner:**
   field definitions, defined/raw classification, capture tooling, initial-state
   and RNG setup, input banks and comparison rules. This request is not a
   blocking dependency; continue with evidence already present.
3. **Define a minimal independent contract.** Choose fields because they are
   observable and relevant to the pilot, not to reproduce the number 59.
   Include units, sampling domain, provenance, tolerances, exclusions and expected
   transitions/events. An independently assembled schema is our contract, not a
   reproduction of the author's unpublished contract.
4. **Create deterministic offline fixtures.** Each records combo, actor state,
   input and previous-input state, RNG state or deterministic service response,
   move/item data identities, service outputs and expected body effects.
   Expectations cite original code or independent artifacts where available.
5. **Run fixtures repeatedly and report differences.** Include a deliberately
   wrong input/output or adapter mutation to demonstrate that the comparison
   catches a relevant failure. Missing required fields and skipped required
   cases fail acceptance rather than disappearing from the denominator.
6. **Freeze the pilot contract for review.** Describe covered and uncovered cases
   explicitly. Later changes to acceptance fields, tolerances or exclusions need
   a version bump and owner approval, not a quiet adjustment to reach green.

**Gate:** agents can run a documented command now, repeat the same offline case,
obtain the same outputs, detect a seeded failure and explain the evidence tier.
No original-game frame-perfect input or new tracing platform is required.

**Time and scope:** follow the repository ceiling of 3 attempts or 2 hours per
investigation. On failure, record the concrete missing capability and ask or
re-scope. Do not automatically descend through days of new DLLs, memory writers
or screen-replay tooling. Finish a smaller honest contract rather than promise
future capabilities. This ceiling applies to focused investigations, not to the
whole pilot's implementation. Report implementation effort separately and obtain
a bounded pilot budget before integration; do not evade ceilings by renaming an
unresolved investigation.

**Optional original observation:** existing reads and captures may answer a
specific question within that ceiling and the desktop-safety rules. If an exact
trace tool is supplied and already works, first test original-versus-original
repeatability, snapshot coherence, update identity, consumed inputs and initial
conditions. Only then consider original-versus-port replay. If any requirement
needs substantial new tooling, defer that capability outside the critical path.

### Phase 2 — Reversible Rena+0 pilot

Only Rena+0 (`character_index()==0`, weapon slot 0, item 001) is in scope.
Target cases: idle, walk, ground dashes, jump/landing, air dash, tap shot, charge
levels, the 300-family melee string, guard, hit and KO. Every target case has a
coverage status; listing it is not proof that a usable fixture already exists.

**2a — Quantified seam audit**
Enumerate every field the selected bodies read/write, services they invoke and
effects returned. Include animation, movement, RNG, targeting, hit/contact,
projectile creation and lifecycle dependencies. Count fields/services and estimate
glue. If the seam requires most of the reference actor/services, stop and present
Option B rather than growing an unbounded adapter.

**2b — Explicit actor context**
Map each field to an existing product field, a justified new field or a named
unresolved dependency. No silent zeroes. Specify update order, previous-input
semantics and service ownership. An unresolved load-bearing dependency blocks
the affected case.

**2c — Offline body tests**
Use Phase 1 fixtures to exercise the recovered bodies independently of product
integration. Check state, move, phase, motion and emitted service/events where
supported. Source-backed fixtures are labelled as such; without original traces,
this is not a claim that original runtime sequences were reproduced.

**2d — One binding owner, limited to the pilot seam**
Implement a resolver in `src/gameplay/native/` with explicit move/phase/set and
fallback reasons. The pilot path uses it; the legacy default remains unchanged.
Do not globally reroute the other 45 combos just to call the addition generic.
Test model bounds, equipped weapon, phase changes and the side-dash regression.

**2e — Integration behind a flag**
With `--native-actions=rena0` or an equivalent flag, recovered bodies drive the
pilot and presentation consumes their outputs. Compare the adapter against the
standalone fixture runner, then run deterministic scripted port scenarios with
`--no-audio`. Test RNG/service results and all gameplay-relevant projectile or
contact dependencies within scope, not just clip binding.

**2f — Evidence and rollback check; do not delete yet**
Run the approved coverage matrix and compare binding, state transitions, motion
and gameplay events. Attach source/artifact provenance and unresolved limits.
Confirm flag-off restores the baseline without a global resolver change.
Keep the old Rena+0 implementation until the owner declares the verdict.

**2g — Owner verdict**

| Criterion | Required for green under the approved contract |
|---|---|
| Repeatability | Fixtures and scripted port runs execute with current tools and reproduce their declared outputs |
| Correctness | Required comparisons pass; independent addressed-code/artifact checks support expectations; no invented load-bearing field |
| Coverage | Every required pilot case is exercised or explicitly removed from scope by the owner before acceptance |
| Seam and cost | Dependencies enumerated; integration bounded; actual effort and likely remaining variability reported |
| Test sensitivity | A seeded relevant error or a real defect is detected; absence of a newly discovered defect alone is not a failure |
| Reversibility | Flag-off restores the pre-pilot path before its removal |
| Honesty | Adapter equivalence, source-backed behaviour and original-runtime parity are separate claims |

**Green means the integration method is accepted under this contract. It does
not mean original-runtime parity has been proved.** A missing original trace is
not disguised as a pass; it is an explicit evidence limit. Red means stop and
re-scope or consider Option B. Missing required evidence means pending, not green.

Only the owner records the verdict in [`SCOREBOARD.md`](SCOREBOARD.md) and lifts
freeze list A. Until then, no scaling beyond Rena+0.

**2h — Cleanup after green**
Delete the accepted Rena+0 hand-decision path in a separate reviewed change.
Remove obsolete tests only when replacement coverage exists. After deletion,
rollback uses the recorded pre-cleanup revision, not a flag that pretends deleted
code still exists. Keep legacy paths only for combos not yet accepted.

### Phase 3 — Scale with coverage, not presumed mechanical work

Add combos in roster order, using actual legal weapon counts. For each:

1. inspect body availability and combo-specific dependencies;
2. add applicable offline and scripted-product cases;
3. test the adapter and compare against independent evidence where available;
4. resolve mechanism errors or document genuine recovered per-combo behaviour;
5. record acceptance and evidence limits, then delete the replaced hand path.

The Rena+0 pilot does not prove that the remaining 45 seams or bodies are complete.
Required coverage expands to applicable attacks, charge levels, cancels,
awakening, hit/guard/knockdown/KO, target interactions and gameplay-relevant
projectiles. Environmental and multi-actor interactions need their own cases;
per-body checks alone cannot prove full-match integration.

**Gate:** 46/46 accepted under the versioned contract, required coverage complete,
no unresolved load-bearing fallback in accepted scope, and scripted end-to-end
1v1 and 2v2 integration checks. Original-runtime parity is a separate result and
may remain unverified. Do not call finite test coverage whole-game equivalence.

### Phase 4 — Finish the product

CPU behaviour, camera completion, visual effect polish, previously frozen
platform work and the release checklist. Gameplay-relevant projectile lifecycle,
collision and damage must already be handled in the relevant acceptance cases;
only presentation polish may wait here.

---

## 5. Owner decisions and plan alignment

Before the pilot integrates:

1. Approve this practical evidence contract and its separation of method acceptance
   from original-runtime parity. The previous mandatory per-frame original-trace
   gate is being replaced, not claimed satisfied.
2. Confirm Option A or choose Option B after the seam audit. Bundle code permission
   is resolved; retain attribution and keep original game assets untracked.
3. Approve the pilot coverage matrix, field meanings, tolerances and exclusions.
   Missing author material does not authorise inventing his 59-field contract.
4. Align [`../AGENTS.md`](../AGENTS.md),
   [`DIRECTION-STATUS.md`](DIRECTION-STATUS.md) and
   [`SCOREBOARD.md`](SCOREBOARD.md) with the approved gates. Resolve obsolete Q8/Q9
   implications in [`QUESTIONS.md`](QUESTIONS.md): menu delivery is not deterministic
   combat input, and the number 59 is not a sufficient schema definition.
5. Keep D15's intended 60 Hz cadence separate from evidence that the implementation
   changed and from claims about the original's precise update timing.
6. Agree a bounded pilot implementation budget before 2e, informed by the seam
   audit and minimal fixture effort. The focused-investigation ceiling does not
   substitute for this budget.

Companion documentation alignment is maintained with this plan. It does not
record acceptance-contract approval or a pilot verdict on the owner's behalf.
Historical D14 wording about mandatory original replay and D15 wording implying
implemented cadence do not override these gates; retain their decision history
while using the current plan and measured implementation status.

## 6. Verification and reporting

Retain the evidence ordering: original runtime observations > addressed recovered
original code > original prints/owner observation > install-backed automated
tests > captures of our build > provisional port rules.

Evidence tier and experimental validity are separate. A live memory read is an
original observation, but not necessarily a coherent frame trace. A capture is
not a live gameplay run. A build is not verification. A skip is not a pass.

Every acceptance report records:

- combo, binary/data identities, code revision and contract version;
- command and fixture identities, initial conditions and RNG/service policy;
- required cases, executed cases, failed/skipped cases and untested interactions;
- expected versus actual outputs, tolerances and reasons for exclusions;
- independent evidence versus shared-source consistency checks;
- sampled original observations, exact original parity if actually available,
  and all remaining unknowns as distinct categories.

The scoreboard headline is **N/46 accepted under contract vN**, accompanied by
coverage status. A separate column records original-runtime parity as proved for
a named scope or not verified. No original trace means **not verified**, never
zero original differences. Do not quietly weaken the contract to increase N.

### Definition of done

The character layer is accepted for product integration when all legal combos
meet the approved coverage contract, use their own recovered decision/binding
paths, have no unresolved load-bearing unknowns within accepted scope, and pass
end-to-end scripted match checks. Full-match human playtesting and release gates
remain distinct. Stronger original-runtime parity requires stronger evidence;
it is neither implied by acceptance nor a hidden future prerequisite.

## 7. What to keep, replace and freeze

Do not rewrite the fighter directory wholesale. Preserve parsers, asset storage,
renderer integration and useful services; replace hand-written decision logic
only after its replacement is accepted.

| Area under `src/gameplay/` | Disposition |
|---|---|
| `character_moves`, `weapon_definition`, combat records/volumes | KEEP; validate service semantics at the seam |
| Projectile storage/lifecycle | KEEP or adapt as needed for required combat cases; do not defer gameplay correctness |
| RNG and simulation RNG | KEEP, verify seeding/consumption; explicit deterministic fixture policy |
| Match loop, economy, HUD, camera, debug tools, fixed-step plumbing | KEEP; modify only for approved integration needs or demonstrated failures |
| Recovered dispatch identities and measured tables | KEEP as evidence; make actual consumers explicit |
| `MoveRule`, hand rule arrays, selectors, admission and shot/dash programmes | REPLACE per accepted combo; frozen until that gate |
| `ginkiha_tables.h` | EVIDENCE-ONLY; no deletion without owner approval |
| Bot AI and unrelated roadmap work | PARK until Phase 4 |

New runtime code belongs in `src/gameplay/native/`. The pilot must not make other
combos depend on its resolver. Keep the legacy implementation as the experimental
control until the owner verdict; delete accepted replacement debt after green,
without permanent compatibility shims or two authoritative decision paths.

Preserve provenance (`FUN_xxxxxx`, field offsets and bundle attribution).
Addressed-code research is allowed where a concrete seam or test requires it;
it is not an invitation to audit the whole corpus before the pilot can proceed.

The freeze list remains owned by [`../AGENTS.md`](../AGENTS.md). Old per-character
hand-port reports and roadmap suggestions are evidence, not fresh work orders.

## 8. Risks and stop rules

| Risk | Response |
|---|---|
| Bodies need a large reference actor/services layer | Quantify at 2a; owner decides Option B or re-scope |
| Reference is wrong or incomplete | Independent code/artifact checks, negative tests and explicit missing coverage; do not treat shared-source agreement as original proof |
| Original automation expands into its own project | Stop at normal attempt ceiling; exclude from critical path; no frame-perfect agent gameplay requirement |
| Live samples are mistaken for exact traces | Label sampling domain and coherence limits; never use `+0xae04` as global update identity |
| Missing fields/fixtures prevent a case | Record the blocker; narrow acceptance only with owner approval |
| Pilot passes but next combos differ substantially | Re-audit dependencies per combo; measured scheduling, not linear promises |
| Old code deleted before the decision | Keep baseline through 2g; separate 2h cleanup and record rollback revision |
| Documentation keeps obsolete gates alive | Align companion tasks after review before agents resume execution |

No original code patching, global desktop input or unannounced desktop takeover.
Original runs must obey the binary pin and repository safety rules. Existing
focus-based XTEST helpers are not process-isolated input: checking focus does
not remove the race or make use of the owner's desktop safe. Prefer an isolated
session if a bounded live observation is approved; do not launch it merely to
keep an agent busy. Use `--no-audio` for remake verification.

## 9. Immediate work after owner review

1. Align the enforcement rules, scoreboard and task rows with the approved plan.
2. Preserve/review WIP and establish the pilot baseline and cadence status.
3. Inventory available evidence and ask the owner to request the author's existing
   verification material; proceed without assuming that material will arrive.
4. In parallel, audit the Rena+0 seam and define a small offline fixture contract.
5. Demonstrate one repeatable body fixture and one sensitive comparison using
   current tools. Start small, then grow the required pilot coverage.
6. Integrate the pilot behind its flag, run adapter and scripted-product checks,
   and present coverage, costs, limits and rollback evidence for the verdict.
7. Only after green: cleanup, then scale. No new original-game controller project.

Harness and pilot roles coordinate through the fixture/service contract. They
may use disjoint files/build directories, but file ownership must not forbid
changes genuinely needed for a port-side producer. Such changes are scoped and
reviewed rather than forced into a fictitious “no gameplay files” constraint.

## 10. The plan in one line

**Use evidence and repeatable offline experiments available now, prove one
recovered-runtime integration without real-time agent gameplay, then scale with
explicit coverage and honest limits.**
