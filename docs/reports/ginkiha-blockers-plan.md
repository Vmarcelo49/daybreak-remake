# Plan — shared shooting blockers, then all 46 combos

2026-10-10 · `ginkiha-help` · status: planned, implementation not started.

This changes Phase 2's order at the owner's request: stop advancing the usage-order
worklist just to defer another combo. Implement the shared mechanisms, return to every
blocked or partial combo, and finish the roster. Companion documents:
[ginkiha-port-plan.md](ginkiha-port-plan.md) and
[ginkiha-handoff.md](ginkiha-handoff.md).

## Completion contract

Every one of the 46 **character+weapon** combos must have an explicit shooting coverage
record. Cover normal and powered branches, ground and air, tap and both charge levels,
plus the additional shooting states reachable from those paths. Include movement,
clock/phase changes, ammunition, request geometry and the projectile behavior required
for that attack to function. A source-proven absent path is N/A with evidence; a missing
implementation or unknown rule is pending. Zero-usage combos, especially Satoko 1,
receive body-driven investigation rather than exclusion.

An existing program, a callback pin, or a successful asset launch is not completion.
The handoff's “13 full programs” means previously bound schedules; those 13 also need
this audit. No unresolved roster path may pass the final gate through the provisional
magazine scan, animation set 0, substituted origins, or silently truncated volleys.
Evidence gaps become concrete investigation tasks, not permanent deferrals.

This plan closes Phase 2 shooting blockers. The broader melee, combat, CPU/camera and
stage-parity phases remain pending; attack-critical dependencies discovered here must
be implemented or tracked against this completion gate, not hidden by that boundary.

## Verified starting point

Latest Linux gate: 65/65 tests, table pins 398 checks, fighter suite 650 checks.
These tests are the starting baseline, not proof of the completion contract above.

| Shared gap | Evidence / current code | First witnesses |
|---|---|---|
| Hand and explicit-world origins | `FUN_00435220/00435250/00435450`; `Fighter::launch_bullet` uses Prop1 when lateral=0 and a special root-relative formula otherwise | Keiichi 0/1, Akane 2, Satoko 2, Natsumi 0 charges |
| Aim semantics and branch inputs | Launch has one symmetric pitch bound; bundle bodies use dynamic scratch pitch, asymmetric branches and raw powered gates | Keiichi 1, Satoko 2, Rena 1, Mion 0 |
| Volleys and randomness | fighter request array holds 8; projectile pool holds 32 globally; per-row capacity is also enforced separately | Kasai 0: 21 normal / 31 tag callback requests; upgraded Kasai bursts |
| Admission/ammunition ordering | `fire_shot` spends tier stock before the callback; original launch helpers call `FUN_00435920` conditionally by row | Satoko 2 twins, mixed-row salvos, capacity exhaustion |
| State/counter/movement operations | rules have no vertical set/scale/gravity or general branch/counter state; both turn helpers currently collapse into limited Turn support | Satoko 2 charge freeze; Rena 1 conditional phase; aerial shooting |
| Projectile-specific behavior | item rows may be non-damaging controllers/traps; birth/expiry/steering and child/effect behavior cannot be replaced with an ordinary damaging shot | Satoko 2 rows 0/1/4/5; verify each remaining combo |

The handoff also describes `m_lastLaunchRule/Phase/Tick`, but those members are absent
from the current `fighter.h`/`fighter.cpp`. Treat this as a documentation/source mismatch
until a test establishes the actual freeze/repeated-fire behavior; do not assume a latch
already exists. The shared Hold owner (`m_holdRule`) does exist.

## 0. Normalize evidence and establish the roster ledger

- Add a read-only recon helper under `remake/foundation/tools/`: select by character AND
  weapon, resolve swap/item from the roster, report dispatch/walk/birth/usage and complete
  trace event counts by origin, and delimit named bodies. Record source identity and exact
  ranges. Keep the local bundles ignored; do not generate or commit their whole contents.
- Establish the 46-combo coverage ledger, with one entry per combo and cells for each
  reachable shooting path: source, runtime binding, origin/aim, branch/RNG, ammo/admission,
  movement/clocks, projectile behavior, verification, and outstanding dependency.
- Normalize helper signatures from the existing corpus and bundle wrappers: attachment
  slot versus item row, hand matrix versus local offset, explicit XYZ, yaw/pitch units and
  axis conventions, raw-word versus numeric scratch conversion, target selection and
  powered/ready predicates. Start with `FUN_00435000`, `00435220`, `00435250`, `00435450`,
  `00435920`, `0042da80`, `0042db10`, `0042dc20`, `0066b668`, and trig helpers.
- Verify generated `source_float` adapters and helper services before deriving numeric
  geometry from raw tuples. State400 stubs at `(0,70,0)` do not validate Satoko 2's
  forward/lateral displacement. Use targeted disassembly/live probes when necessary.
- Compare old tests and source claims, including freeze/launch handling. Establish tests
  that expose duplicate requests, missing requests and early/late ammo consumption.

**Exit:** all 46 identities represented; each known blocker has evidence and a witness;
normalized contracts exist for the first origins and admission helpers. Unknown contracts
remain explicit investigation tasks. No runtime port is claimed from this step.

## 1. Introduce an explicit launch contract and admission boundary

Keep simple movement rules, but stop packing origin, aim and branch semantics into
`MoveRule`'s three floats. Proposed design: typed launch/aim descriptions and a small
shooting context; use focused C++ callbacks for genuinely computed bodies. Confirm the
concrete types after step 0; do not embed a decompiler word-bank interpreter in the game.

Separate three observable stages: **callback request → ammo/row admission → pool spawn**.
Trace them separately in verification. Preserve original ordering and side effects,
including rejected requests; do not force a whole salvo to be atomically admitted unless
that is established by the original. Resolve item row/magazine/registration from actual
DATs. Verify whether gate/consumption happens at move entry, callback time, or both for
that path. Correct the current eager tier-spend path where the evidence requires it.

**Exit:** tests cover unmetered/metered rows, empty ammo, reload gates, rejected pool
spawns, mixed-magazine requests and multiple requests in one tick, with measured ordering.

## 2. Support all three origin families and computed aim

- Attachment: explicit slot/bone, item muzzle anchor, and the unbound-prop bone-origin
  case. Preserve slot 0 versus slot 1 rather than always choosing Prop1.
- Hand: transform the named hand bone with the exact helper's offset/aim semantics.
  A missing expected bone in a roster rig is an explicit failure, not root substitution.
- World: accept computed XYZ independently of aim. Carry yaw/pitch or normalized direction
  from an explicit aim calculation; distinguish base heading, movement-preserving offset,
  target-relative yaw and absolute angles.
- Implement separate lower/upper pitch bounds, fixed pitch, target-derived pitch and the
  distance-dependent adjustment where recovered. Reproduce integer conversion and the
  air-tap ±30 comparison / ±45 assignment discontinuity for Keiichi 1.

**Exit:** real posed-rig tests at multiple headings and animation ticks verify hand versus
Prop1; world tests use nonzero positions, lateral offsets, target heights and distances.
Satoko 2's two tap origins must remain distinct even with empty prop meshes. Existing
programs are checked against evidence; preserve proven behavior and correct proven errors.

## 3. Add branch inputs, deterministic spread and adequate capacity

- Recover the powered/ready/tag/aim predicates and connect them to actual fighter state;
  do not equate a bundle label “tag” with a particular hypermode without evidence.
- Supply a deterministic simulation RNG through the match/shooting context. Keep it
  separate from visual RNG; preserve recovered draw order, distribution and per-volley
  shared aim versus per-pellet perturbations. Tests use known seeds and branch inputs.
- Support runtime burst counts/upgrades and asymmetric row/count selection.
- Replace the eight-request truncation with storage sized or growable for measured
  volleys. Audit the 32-shot global pool independently against original allocation and
  DAT per-row capacities; increasing only the pending array does not solve four-fighter
  scatter. Keep source-proven admission limits, with visible verification outcomes.

**Exit:** Kasai 0 normal 21 and tag 31 requests retained in order, correct per-row admission,
exact spread/RNG behavior, upgraded burst counts, and simultaneous 2v2 volleys. Capacity
or RNG failures cannot masquerade as a successful schedule.

## 4. Complete shooting state, counters and movement

- Add typed per-move state for counters, phase jumps, conditional transitions, tick rewind,
  freeze and per-event execution. Reset it correctly on entry, cancellation, re-entry,
  death and respawn. Distinguish an event that must fire once at a frozen tick from a
  loop deliberately firing repeatedly; choose semantics from the body, not a global latch.
- Support vertical velocity set/scale, horizontal scaling, unclamped gravity tails, and
  phase-dependent gravity. Preserve distinct `FUN_0042db10` / `FUN_0042dc20` behavior.
- Match lower/upper animation metadata and clock order where bodies depend on them. Use
  actual DAT phase durations to prove reachable firing paths and termination.
- Cover air/ground landing transitions and second-charge/EX/follow-on shooting states
  wherever the combo's input/state dispatcher reaches them.

**Exit:** Satoko 2 phase1/tick6 request and ten-update tick26 freeze; Keiichi multiple
stalls; Rena 1 conditional state402; representative air gravity/landing paths; exact
request counts across held ticks and re-entered phases. No invented phase-0 restriction.

## 5. Revisit blocked and partial ports, then complete the roster

Capability witnesses land with their implementation; do not wait for every engine step
before exercising real combos. Close the currently deferred/partial entries first:

| Combo | Required closure |
|---|---|
| Keiichi 0 | hand tap/air tap; normalize and implement charge helpers/rows |
| Keiichi 1 | hand tap/air tap, world charges, dynamic/discontinuous pitch |
| Akane 2 | computed world requests and normal/powered secondary scheduling |
| Satoko 2 | twin world tap, phase1 charge, freeze, row controller/projectile behavior |
| Kasai 0 | normal/tag scatter, request/pool capacity, shared aim and per-pellet spread |
| Shion 0 | finish the bounded body audit; record and implement its actual requirements |
| Rena 1 | conditional air tap, random spread, air/second charges |
| Natsumi 0 | air tap, powered/random multi-row tap, world charges |

Then migrate the remaining bound schedules and finish the unported combos using the
ledger. Usage density can order work within a family, but cannot remove a combo.
For every combo, implement all reachable required paths, not just its state400 probe.
Investigate required steering/expiry, non-damaging controllers, child spawning and effects
with the same provenance rules. Asset availability does not prove behavior.

## 6. Finish with 46/46 coverage and integration gates

1. Ledger contains exactly the authoritative roster, each combo with real NN.dat AND item
   data. All required cells complete; N/A cells carry source evidence; no pending/deferred
   entries. Replace the misleading “full program” scoreboard with measured path coverage.
2. Asset-backed tests drive natural ground/air, tap/charge and powered paths. Pure geometry
   tests isolate transforms; request/admission/spawn tests retain separate counts. Test
   sparse/no-usage combos through bodies and reachable state dispatch.
3. Four-fighter cases exercise simultaneous volleys, pool saturation, branch/RNG state,
   death/respawn and rematches. Run the complete rebuilt Linux suite after each coherent
   runtime slice, then Linux/Windows/web builds for the integrated change.
4. Perform actual live runs with game data, including a four-view 2v2 rematch, plus targeted
   original/remake comparisons of newly supported attacks. Captures supplement live runs;
   document platform execution gaps instead of treating compilation as execution.

## Delivery and execution rules

Implement in dependency order: evidence/contracts → request/admission → origins/aim →
branches/spread/capacity → state/movement → roster closure → integrated gate. Each slice
ships with meaningful witness tests; subsequent discoveries extend the shared capabilities
rather than restarting the defer cycle. No fixed time estimate until step 0 resolves the
contracts and inventories all dependencies.

Use the shared recon helper and parameterized catalog checks to reduce repeated extraction
and test boilerplate. Body predicates, geometry and admission still require review; an
extractor must not automatically turn raw operands into gameplay rules.

All new runtime code stays in `remake/foundation/`. Keep original `.X` assets and D1–D9.
Never edit `research/recomp/`; research promotion is targeted and requires the coverage
report. Keep local bundles/game assets ignored. Rebuild before runtime gates, read both
full diffs before every commit, stage only the current slice, and keep the unrelated
Windows work uncommitted. Separate engine/test commits from documentation updates.
