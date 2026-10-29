# Scoreboard — the port's only progress metric

> **Headline: `0/46` accepted under approved contract v3.** The owner approved v3 on
> 2026-10-22; the pilot verdict remains pending, including the source-provenance defect
> recorded at Q19. **Original-runtime
> parity is a separate column and `not verified` for every combo** — no coherent
> original per-update trace is demonstrated in this repo, and no trace is never
> scored as zero differences. Coverage is explicit per combo: the pilot's target
> cases are named in [`DIRECTION.md`](DIRECTION.md) §4 Phase 2, and the bounded F1-5 observation probe is recorded in
> [PILOT-EVIDENCE-CONTRACT.md](PILOT-EVIDENCE-CONTRACT.md), not accepted pilot coverage.
>
> Retired metric: "combos at zero defined differences against the original" belonged
> to the per-frame original-trace gate that
> [`DIRECTION.md`](DIRECTION.md) §5 item 1 replaces with contract acceptance.
> Acceptance is under the approved contract; green accepts the integration method,
> not original-runtime parity (§4 2g).
>
> Updated by whoever runs the approved fixtures; the pilot verdict is written by the
> repo owner. This file records no approval or verdict the owner has not given.

Plan: [`DIRECTION.md`](DIRECTION.md). Task list and work reports:
[`DIRECTION-STATUS.md`](DIRECTION-STATUS.md). Freeze list and the three-question
test: [`../AGENTS.md`](../AGENTS.md). Questions: [`QUESTIONS.md`](QUESTIONS.md).

## Headline

| Metric | Value |
|---|---|
| Accepted under the coverage contract | **0/46** |
| Runner's current matrix | **30 fixtures / 31 case rows / 49 acceptance fields**, 6 unsupported, 0 unreferenced extras (measured 2026-10-29 with `rena0_fixture_test`). The approved v3 set was **24 / 25 / 44**; the six fixtures added since (the EX camera, the air-dash and landing pins, the shot and card cases) are pinned by tests and carried by the runner, and their formal re-approval belongs to the owner's verdict — the metric below stays `0/46` either way |
| Contract version | **v3 — APPROVED 2026-10-22, amended V3-8 (2026-10-23)** for the stated Rena+0 pilot scope (reviewed content `sha256 12bd62ec…`; erratum V3-6 changes no acceptance field, tolerance or exclusion). It supersedes v2 (`c5df9931…`, approved 2026-10-16). The set is **25 case rows over 24 fixtures, 44 acceptance fields**, 6 unsupported declared, 0 unreferenced extras — after the owner-approved Q19 correction (V3-7), which replaced the misattributed powered-shot spend with the powered-launch and recovery cases and removed the production deduction. **Approving a contract is not a verdict**: acceptance stays **0/46** until the owner records 2g. **Owner correction recorded in V3-6 (2026-10-22):** the dash resource is the stamina meter, not a second gauge — the earlier gauge-0 dash 'discrepancy' was an injected-state artefact and the pilot gate on that counter was removed |
| Coverage | Approved v3 declares 24 fixtures / 25 case rows / 44 acceptance fields / 6 unsupported. The 11 target categories have port fixtures with source citations; Q19’s misattributed spend was replaced by source-backed powered-launch and recovery cases rather than dropped. Case/fixture and field/fixture bindings plus mandatory manifest enforcement are held by a seven-mutation regression. This is still not recovered-body equivalence for the whole combo, and acceptance remains pending |
| Original-runtime parity | **not verified** for all 46 combos — historical sampled live reads only; no coherent per-update original trace is demonstrated in this repo ([`DIRECTION.md`](DIRECTION.md) §2.2, §6) |
| Pilot verdict | **pending — not merely awaiting a signature.** The 2026-10-22 re-audit reproduced and fixed acceptance-enforcement holes and found the required powered-402 spend misattributed to a non-Rena dash-cancel. V3 approval is retained, but a source-backed green recommendation needs Q19 resolved. Current evidence and limitations: [`PILOT-SEAM.md`](PILOT-SEAM.md) §29; [`QUESTIONS.md`](QUESTIONS.md) Q19/Q20. No cleanup or scaling authorized |

## Pilot verdict

| Field | Value |
|---|---|
| Combo | Rena+0 (`character_index()==0`, weapon slot 0, item 001) |
| Verdict | **pending.** V3 was approved by the owner on 2026-10-22; Q19 and Q21 corrections applied since (V3-7, V3-8). No agent is authorized to turn approval into a green verdict or begin 2h cleanup |
| Declared by | repo owner |
| Criteria | [`DIRECTION.md`](DIRECTION.md) §4, 2g |
| Accepts | the integration method under the approved contract only; it does not assert original-runtime parity (2g) |
| Date | — |
| Evidence | Current findings supersede old readiness summaries: [`PILOT-SEAM.md`](PILOT-SEAM.md) §29 and [`PILOT-EVIDENCE-CONTRACT.md`](PILOT-EVIDENCE-CONTRACT.md) V3-7. The approved matrix is 24 fixtures / 25 case rows / 44 fields / 6 unsupported. Q19’s contradicted spend is gone: the powered air tap now launches bullet row 7 with no gauge subtraction, and the row-403 recovery is pinned at +40/tick with its clamp. The empty-ammo release window (19 frames voicing, 20 silent) is enforced and proven load-bearing. Enforcement regression checks seven scratch mutations. The split stamina/charge channels are unified on the pilot path (V3-8, §30.6): one 0..1000 word with the recovered integer rates; re-pinned guard exhaustion 245 → 99 and tick-59 stamina 75 → 40. Carried-forward limits: state-30 −3 arm, jump row variants, guard phase granularity, port-rule fly drain, Kakera mapping. Still needed from the owner: the `EXCEPTIONS.md` row and the 2g verdict |

The freeze list in `AGENTS.md` stays in force until this verdict is **green**:

- **green** → that list is replaced by the Phase 3 order (scale to 46/46).
- **red** → the adoption decision in [`DIRECTION.md`](DIRECTION.md) §3 (Option B or
  a re-scoped pilot); the pilot is disabled behind its flag and what was learned is
  recorded here.

**Deletion and rollback (2f/2h).** The pre-pilot Rena+0 path stays in place as the
experimental control through the 2g verdict: no deletion before it, and flag-off
must restore that baseline before anything is removed (2f). A green verdict is
followed by the separate, reviewed 2h cleanup; after that, rollback is the recorded
pre-cleanup revision, not a runtime flag that pretends deleted code still exists.
Later combos follow the same order — recorded acceptance, then deletion
([`DIRECTION.md`](DIRECTION.md) §4 2f/2h, §7; [`../AGENTS.md`](../AGENTS.md)
"Frozen work"). The older "delete the Rena+0 hand path outright" as a pilot step is
retired.

## Combos

Rows are added as Phase 3 reaches each combo; until the pilot is green, the only row
is the pilot. Acceptance is reported with its contract version and coverage status;
original-runtime parity is a separate column and never inferred from acceptance.

| # | Combo | Accepted (contract) | Coverage | Original-runtime parity | Evidence |
|--:|---|---|---|---|---|
| 1 | Rena+0 | no — v3 approved, 2g pending | 24 fixtures / 25 case rows / 44 acceptance fields / 6 unsupported; the Q19 misattribution is corrected and re-tested, the split stamina/charge channels remain open | not verified — no coherent original trace | [approved contract and re-audit](PILOT-EVIDENCE-CONTRACT.md); [current seam review](PILOT-SEAM.md#29-independent-readiness-check-after-v3-approval-2026-10-22) |

The old "defined diffs" column is retired with the per-frame original-trace gate:
with no original trace it would read *not verified*, never zero
([`DIRECTION.md`](DIRECTION.md) §6).

## Phase progress (until the pilot verdict)

| Phase | State | Evidence |
|---|---|---|
| 0 — safe baseline | **all four gate items recorded 2026-10-16** (known baseline, preserved WIP, aligned plan/tasks, explicit cadence); the only owner-facing item left is whether to commit the WIP and plan documents, which P0-1 leaves to the owner | Done 2026-10-14: D14 + freeze list, binary pin `27e614…a6a07f02` (re-verified 2026-10-16), status documents, issue hygiene (alignment rows P0-7a/P0-7b live in the task list). P0-1 reviewed the actual baseline (56 modified tracked + 10 untracked at 2026-10-16), preserved it unchanged and mapped it into a five-part commit plan; nothing committed or staged. **P0-10 landed: live cadence is 60 Hz** (`FixedStep::tickRate`), capture domain derived, full suite 72/72; F1-9's two assertions pin it. P0-2 closed 2026-10-16: the five stale worktrees and four fully-merged branches were removed after the owner reviewed the listing (no commit lost, ~1.4 GB freed), and `AGENTS.md` now points at the recorded listing. Not gate items: REPLACE banners (P0-6, dropped), split build dirs (P0-9, optional if parallel work needs them), Windows-rematch check (P0-11, deferred to Phase 4 platform verification). Rows: [`DIRECTION-STATUS.md`](DIRECTION-STATUS.md) Phase 0 |
| 1 — evidence assembly and minimal fixture | Approved v3 scope and runner exist; acceptance-enforcement re-audit strengthened exact fixture bindings | Source/body consistency and install-backed product evidence are distinct from original-runtime parity, which is not verified |
| 2 — Rena+0 pilot (2a–2h) | 2e implemented in bounded slices; 2f reopened for discovered correctness/enforcement defects; 2g pending; 2h prohibited | Q19: required shot-spend provenance contradicted. Q20: requested Luna model unavailable for further delegation. No other combo implementation |
| 3 — scale to 46/46 | closed until a green verdict | [`DIRECTION.md`](DIRECTION.md) §4 Phase 3 gate; freeze list A stands. Rows: [`DIRECTION-STATUS.md`](DIRECTION-STATUS.md) Phase 3 |

Keep entries compact: state, date where recorded, and the artifact that proves it,
cited inline. A claim without an artifact does not belong here.
