# Scoreboard — the port's only progress metric

> **Headline: `46/46` running under the core** (the metric from
> [`DIRECTION.md`](DIRECTION.md) §6). Measured 2026-10-30 at `ec789371`: each combo as fighter 0
> in `foundation_demo --headless --match`, 900 ticks on stage01 with three CPU opponents,
> `RESULT: ok` and 900 frames. Tier 5 execution evidence on one stage, with no human input and
> no judgement of correctness. **Original-runtime parity is a separate column and `not
> verified` for every combo.** Open disagreements stay in `DIRECTION-STATUS.md`.
>
> Closed metric: `1/46` accepted under contract v3 (Rena+0, owner verdict 2026-10-30,
> state at `261078b0`). It accepted the legacy-path pilot under that contract and does
> not claim a perfect Rena+0.
>
> M5 approved by the owner on 2026-10-30 at `534b990f`; the legacy path last exists at `e9347627`.
>
> Updated by whoever runs the checks; verdicts are written by the repo owner.

Plan: [`DIRECTION.md`](DIRECTION.md). Task list and work reports:
[`DIRECTION-STATUS.md`](DIRECTION-STATUS.md). What work is allowed:
[`../AGENTS.md`](../AGENTS.md). Questions: [`QUESTIONS.md`](QUESTIONS.md).

## Headline

| Metric | Value |
|---|---|
| Running under `--sim=core` | **0/46** (M4 has not started) |
| Closed: accepted under contract v3 | 1/46 (Rena+0, owner verdict 2026-10-30) |
| Runner's current matrix | **30 fixtures / 31 case rows / 49 acceptance fields**, 6 unsupported, 0 unreferenced extras (measured 2026-10-29 with `rena0_fixture_test`). The approved v3 set was **24 / 25 / 44**; the six fixtures added since (`idle-refill`, `single-hover`, `jump-climb`, `air-turn`, `attack-empty-meter` and the Hyper EX camera) are pinned by tests and carried by the runner, and their formal re-approval belongs to the owner's verdict — the metric below stays `0/46` either way. Two of the 49 fields (`action_camera`, `hyper`) were also missing from the runner's own `kRequiredFields` until 2026-10-29; they are listed there now, so the manifest cannot lose them silently |
| Contract version | **v3 — APPROVED 2026-10-22, amended V3-8 (2026-10-23)** for the stated Rena+0 pilot scope (reviewed content `sha256 12bd62ec…`; erratum V3-6 changes no acceptance field, tolerance or exclusion). It supersedes v2 (`c5df9931…`, approved 2026-10-16). The set is **25 case rows over 24 fixtures, 44 acceptance fields**, 6 unsupported declared, 0 unreferenced extras — after the owner-approved Q19 correction (V3-7), which replaced the misattributed powered-shot spend with the powered-launch and recovery cases and removed the production deduction. **Approving a contract is not a verdict**: acceptance stays **0/46** until the owner records 2g. **Owner correction recorded in V3-6 (2026-10-22):** the dash resource is the stamina meter, not a second gauge — the earlier gauge-0 dash 'discrepancy' was an injected-state artefact and the pilot gate on that counter was removed |
| Coverage | Approved v3 declares 24 fixtures / 25 case rows / 44 acceptance fields / 6 unsupported. The 11 target categories have port fixtures with source citations; Q19’s misattributed spend was replaced by source-backed powered-launch and recovery cases rather than dropped. Case/fixture and field/fixture bindings plus mandatory manifest enforcement are held by a seven-mutation regression. This is still not recovered-body equivalence for the whole combo, and acceptance remains pending |
| Original-runtime parity | **not verified** for all 46 combos — historical sampled live reads only; no coherent per-update original trace is demonstrated in this repo ([`DIRECTION.md`](DIRECTION.md) §2.2, §6) |
| Pilot verdict | **green, declared by the owner 2026-10-30** for the state at `261078b0`: "aprovo o estado atual do 2g". The owner also recorded that a perfect Rena+0 is not a realistic goal. No cleanup or scaling started; the next direction is under review in [`reports/reference-core-plan-2026-10-30.md`](reports/reference-core-plan-2026-10-30.md) |

## Pilot verdict

| Field | Value |
|---|---|
| Combo | Rena+0 (`character_index()==0`, weapon slot 0, item 001) |
| Verdict | **green** for the state at `261078b0`, with the limits named in the evidence below; original-runtime parity stays not verified. 2h has not started |
| Declared by | repo owner |
| Criteria | [`DIRECTION.md`](DIRECTION.md) §4, 2g |
| Accepts | the integration method under the approved contract only; it does not assert original-runtime parity (2g) |
| Date | 2026-10-30 |
| Evidence | Current findings supersede old readiness summaries: [`PILOT-SEAM.md`](PILOT-SEAM.md) §29 and [`PILOT-EVIDENCE-CONTRACT.md`](PILOT-EVIDENCE-CONTRACT.md) V3-7. The approved matrix is 24 fixtures / 25 case rows / 44 fields / 6 unsupported. Q19’s contradicted spend is gone: the powered air tap now launches bullet row 7 with no gauge subtraction, and the row-403 recovery is pinned at +40/tick with its clamp. The empty-ammo release window (19 frames voicing, 20 silent) is enforced and proven load-bearing. Enforcement regression checks seven scratch mutations. The split stamina/charge channels are unified on the pilot path (V3-8, §30.6): one 0..1000 word with the recovered integer rates; re-pinned guard exhaustion 245 → 99 and tick-59 stamina 75 → 40. Carried-forward limits: state-30 −3 arm, jump row variants, guard phase granularity, port-rule fly drain, Kakera mapping. Still needed from the owner: the `EXCEPTIONS.md` row and the 2g verdict |

The green verdict closed the pilot. The owner then approved the reference-core direction on
2026-10-30, so the old Phase 3 order and the separate 2h cleanup do not apply; M5 deletes the
legacy path as a whole.

## Combos

Rows start at M4. The closed pilot row stays as history.

| # | Combo | Running under `--sim=core` | Coverage | Original-runtime parity | Evidence |
|--:|---|---|---|---|---|
| 1 | Rena+0 | no — M4 not started (legacy path accepted under v3, 2026-10-30) | M2 reports the core's coverage | not verified | [closed contract](PILOT-EVIDENCE-CONTRACT.md) |

## Milestones

| Milestone | State | Evidence |
|---|---|---|
| Pilot (old Phases 0-2) | closed green 2026-10-30 | this file's verdict; [`DIRECTION-STATUS.md`](DIRECTION-STATUS.md) |
| M1-M6 | see the task list | [`DIRECTION-STATUS.md`](DIRECTION-STATUS.md) |

Keep entries compact: state, date where recorded, and the artifact that proves it,
cited inline. A claim without an artifact does not belong here.
