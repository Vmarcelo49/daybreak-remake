# Plan — shared shooting blockers, then all 46 combos

2026-10-10 · `ginkiha-help` · status: live magazine/row admission implemented; typed origin/aim plumbing started; source branch/selection bridge and move counters next.

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
| Hand and explicit-world origins | `FUN_00435220/00435250/00435450`; the legacy adapter retains Prop1/root-offset behavior, while typed specs now carry named-bone, explicit-world and actor-relative origins. No combo uses the new families yet. | Keiichi 0/1, Akane 2, Satoko 2, Natsumi 0 charges |
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

## Append-only execution log

### 2026-10-10 — 0.1 Recon helper and initial roster ledger

**Done:** added `remake/foundation/tools/ginkiha_recon.py`, sharing catalog identity
checks with the existing importer. It resolves exact character+weapon identities, validates
support input hashes, reads actual runtime dispatch bindings, counts all callback requests
by origin/row, and reports exact shooting/full-charge body ranges. Unknown runtime syntax
and hash drift fail instead of silently returning incomplete evidence. Sources stay local.

Created [the 46-combo ledger](ginkiha-shooting-coverage.md): 15 bound schedules, zero
combos declared audited complete, all normal/powered ground/air tap/charge paths pending.
Satoko 1's zero-usage case and Rena 1's missing generated bodies remain visible.

**Verified:** five stdlib Python tests passed, including exact selection, 21/31 Kasai
requests, both Satoko 2 traces, zero usage, missing bodies, chronological first request,
body boundaries, malformed binding syntax and hash drift. All-roster recon produced
46 unique entries. No game runtime or research files changed.

**Next:** normalize helper operands/admission from original corpus and verified archive.
The supplied state400 evidence cites a corrected world-origin oracle and numeric scratch
adapter in `runtime/DaybreakRebuild-20261010.zip`; inspect those before repeating probes.
Step 0 remains open: prove helper contracts and freeze/launch/ammo ordering, then start
step 1's typed request/admission boundary with witness tests.

### 2026-10-10 — 0.2 Original launch/admission and archive contracts

**Done:** added [normalized launch contracts](ginkiha-launch-contracts.md). Original
bytes confirm row-selected magazine admission, negative-index bypass, six world-spawn
operands, degree/table-based trig, and consume-before-creation ordering. Verified the
canonical EXE hash and runtime archive SHA; found the numeric scratch adapter and corrected
Satoko 2 state400 world geometry. Recorded remaining original FILD/indexing/oracle gates.

**Important correction:** a generic launch latch is not the fix for all frozen frames.
Rika 1's state450 body gates tick30 requests on scratch counter%10==0 and freezes until
counter60. The current static salvo+Hold30 misses those semantics. Source ranges and
limits are in the contract report; previously bound schedules remain unaudited.

**Verified:** targeted disassembly of `00435450`, `00435920`, `0065d010/0065d050`;
archive hashes and three entry hashes recorded. The corrected 690-record world golden
TSV was not found in the supplied inventory, so its geometry verification remains open.
No runtime behavior changed yet.

**Next:** implement a typed magazine admission/refill model, verified against the original
helpers, then wire it into requests without eager tier spending or double charging.
Audit charge/HUD/bot consumers together; do not change only consumption. In parallel
within the same workstream, add full-freeze request-count witnesses before replacing
Rika's schedule. Step 0 remains in progress; use the recon helper/ledger to cover all46.

### 2026-10-10 — 1.1 Round-counted magazine primitive

**Done:** implemented `src/gameplay/shooting_magazine.h`: typed round-counted state,
DAT-definition initialization, reset, signed interval admission, and mode0/1/2 tick/refill
behavior. Original 32-bit wrap and flag/counter effects are preserved. This is an isolated
primitive; live Fighter still uses provisional AmmoStock, so no live ammo migration is
claimed. Keeping this tested boundary separate avoids changing charge/HUD/bot behavior
before all of their consumers are accounted for.

**Verified:** added 31 fixture-backed checks using Rena 0 + item1; focused fighter suite
passed 681 checks, zero failures/skips. Tests cover same-tick callbacks, zero stock and
nonzero interval rejection, signed cooldown, partial versus empty refill, all three modes,
reset/flag/counter behavior, and retained empty-refill display progress. The rebuilt full
Linux suite is running; append its result before committing this slice.

**Next:** implement row-selected request admission (negative magazine bypass, bounds,
consume-before-spawn), then connect the new stocks to Fighter with one authoritative tick,
correct request-time consumption and consistent HUD/bot/charge reads. Audit original
refillStep initialization/modifiers and charge helper before enabling live stocks. In the
same migration, add mixed-row/failed-pool tests and whole-freeze counter-gated witnesses.
Steps 0 and 1 remain open; all46 ledger entries remain pending complete-path audit.

### 2026-10-10 — Validation and resumption checkpoint

**Done/verified:** full rebuilt Linux CTest passed 65/65 (163.74 s), including the
updated fighter suite (681 checks). Recon tests now pass six cases: the added case
proves a wrong combo locomotion handler is rejected instead of misreporting a runtime
binding. All46 recon and exact Satoko 2 recon both succeed; output is barred from writing
over the read-only support/reference bundles. Full diff review completed before commits.

**Current boundary:** code supplies the tested magazine primitive and recon tooling;
Fighter, charge/HUD/bots and projectile request/spawn behavior have not yet migrated.
Neither step0 nor step1 is declared complete. No combo was promoted to full coverage.

**Exact next task for the next agent:** read `ginkiha-launch-contracts.md` and the new
`shooting_magazine.h`. Audit `FUN_0043f3e0` and refillStep setup/modifiers, inventory
Fighter's `m_main/m_charge` consumers, then implement row-selected admission and integrate
one authoritative stock per magazine across charge/HUD/bot reads. Preserve negative-index
bypass and consumption before failed pool creation; add tests for mixed rows and no eager
spend. Then replace counter-gated freeze schedules with source-driven event state, starting
Rika1 state450, before declaring origins/spawn paths complete. Update the ledger and append
done/verification/next notes after each unit. Preserve the unrelated Windows edits.

### 2026-10-10 — 1.2 Consumer/charge/refill audit before live migration

**Done:** inventoried Fighter init/reset/respawn/weapon swap/F4, HUD fraction/count,
BotBrain can_fire/hold_ticks, eager fire_shot, and callback launch consumption. Original
`0043ded0` charges the SECOND magazine (bytes add actor+0x708 at 0x43dee9), with
`0043f3e0`'s initial30 ticks followed by the DAT secondary charge threshold. Primary
chargeMax is not the yellow threshold. `00435560` sets both magazines' refillStep;
`0043ded0` resets it to1, uses3 for active byte845 and2 for byte846. Common `0041f580`
calls `00434800` after the action/animation pass, which ticks each magazine once.

**Next:** add charge counters and row-admission primitives, then switch bound weapon
stocks and their public readers together. Preserve the explicitly provisional mobile
charge/action gate and unbound move selection as pending paths, not source parity claims.
Remove eager tier spending for programmed shots; consume each callback's own row, retain
negative-index bypass, and test rejected pool creation without refunds. Validate against
the complete suite and append all changed expectations with their source reason.

### 2026-10-10 — 1.3 Live row admission, stocks and charge migration

**Done:** bound weapons now own two round-counted ShootingMagazines. Programmed move
selection spends nothing; each Launch consumes its item row's magazine, negative indices
bypass stock, invalid metadata fails explicitly, and failed pool creation cannot refund
consumption. HUD fractions/digits, can_fire/bot hold planning, charge counters, weapon-swap
fill preservation, init/reset/respawn and F4 use the same authoritative bound stocks.
Charge stage1 uses30 initial updates and stage2 uses the secondary DAT threshold; refill
steps are1 normally,3 for the current Friendship adapter and2 for Kakera. The C-held marker
is independent of secondary charge: an empty CHARGE stock still permits a primary tap.

Admitted requests use a growable FIFO rather than the eight-entry truncation. This removes
that queue limit only; the global32 projectile pool and actual scatter/RNG remain open.
Unbound move selection, row-less provisional requests, mobile/actionable charge restrictions,
legacy no-weapon tuning, exact hypermode/status parity and origin geometry remain explicitly
pending. No combo is declared complete by this shared migration.

**Verified so far:** focused fighter suite697 checks, zero failures/skips. Rena0 witnesses
cover no eager spend, primary/secondary row selection, unmetered red rows11/12,30/210-tick
charge, source refill, empty-secondary tap, F4/reset, negative-index bypass and saturated
pool consumption without refund. A shared semantic hold_yellow driver replaced13 repeated
charge calculations/drivers. Initial full-suite failures exposed obsolete threshold/air
reachability, approximate empty-stock setup and AI-seed-dependent audio coverage; corrected
these without weakening their functional assertions. The air-charge animation case now
executes460 instead of incorrectly claiming it cannot be reached. The bot empty-stock case
now binds character AND weapon; the audio gate drives a real activation input explicitly.
Those four focused suites passed, then the rebuilt full suite passed65/65 (163.76s).

Linux native non-capture 1v1 smoke completed3000 frames/1065 logic ticks at64Hz, RESULT ok;
this is not a played parity or four-view rematch gate. Windows and web cross-builds passed.
Review removed redundant request initialization and an unused bound-tier parameter lookup;
final rebuild/full-suite/platform confirmations are running and must be appended next.

**Next:** introduce explicit typed origin/aim requests and pose transforms, starting hand
and world witnesses (Keiichi0/1 and Satoko2). Do not bind rawworld/hand bodies to Prop1.
Preserve request/admission/spawn distinctions; finish per-move counter semantics (Rika1
450 is the known witness) before accepting its frozen salvo totals. Audit global projectile
capacity and deterministic spread for Kasai0, and remaining source-specific branch/status
inputs. Update the ledger by path; step1 still needs those integration/coverage gates.

### 2026-10-10 — Final migration gate and next-agent checkpoint

**Done/verified:** final reviewed tree rebuilt; Linux CTest65/65 passed (167.18s),
fighter suite704 checks/zero failures/skips, recon six tests passed. Windows and web
reviewed cross-builds passed; neither platform was executed for this slice. Linux native
1v1 non-capture smoke previously completed3000 frames/1065 logic ticks, RESULT ok.
Review retained clip completion and provisional EX input/event checks while replacing
obsolete eager-spend/refill expectations. Thirteen duplicated charge drivers were unified.
The code and tests form one coherent stock/admission migration; documentation is separate.

**Still open:** typed launch-origin/aim descriptions, explicit request/admission/spawn
verification records, exact hypermode/status bridge, counter-gated move bodies, global
projectile allocation/spread, and all46 complete-path audits. Legacy no-weapon and
unbound/row-less request paths remain provisional. This is not46/46 shooting completion.

**Exact next task:** implement typed Launch origin/aim resolution using the normalized
contracts and existing row-admission boundary. Add real posed-rig witnesses for hand versus
Prop1 (Keiichi0/1), and nonzero-position/heading/elevation twin world requests for Satoko2;
preserve fixed actor-heading origin versus offset projectile yaw. Verify scratch numeric
conversion and legacy trig at their original sites. Then integrate source per-move counters
with Rika1 450's whole frozen interval, and audit the global32 pool with Kasai0 21/31
requests and simultaneous2v2 volleys. Keep the growable request FIFO, avoid reintroducing
eager tier costs, and append done/verification/next notes after each unit.

### 2026-10-10 — 2.1 Typed origin/aim plumbing started

**Done:** added `shot_launch.h` value types for attachment, bound-bone fallback, named-bone,
explicit-world, and actor-relative-offset origins, plus facing, target-elevation, legacy-angle
and explicit-direction aims. `MoveRule` can carry these descriptors; `PendingShot` preserves
them through the scene handoff. Existing Launch rules now pass through a compatibility adapter
that retains their current attachment/root-offset and symmetric pitch behavior. A named-bone
request rejects a missing posed rig/bone. Origin and direction resolve before row admission,
so a missing transform cannot consume stock; accepted requests still consume before pool spawn.

No character program has yet opted into a new origin/aim family. The LegacyDegrees path records
the source angle convention but uses the current math library; exact 3,600-entry table indexing
and actor-basis parity remain required. Handler-specific gates, paired launches, spread/RNG and
per-move counters also remain outstanding.

**Verification:** no tests or build were run in this step. The source changes are uncommitted and
await the required validation. Do not bind a deferred combo from these descriptors alone.

**Next:** connect a source-evidenced combo to typed specs. Start with the Satoko 2 state400 normal
world pair (row mapping and fixed actor-heading origin already measured), preserving target-offset
aim separately. Recover the two powered-branch inputs and emission-count semantics before wiring
tag. Then add per-move counters/events for the counter-gated Rika 1 charge freeze. Keep hand-bone
rows deferred until callback operands versus item rows are reconciled for Keiichi 0/1.

### 2026-10-10 — 2.2 Typed world geometry and Satoko 2 branch audit

**Done:** extended typed launch resolution with actor-relative XYZ offsets and a world aim that
converts the remake's facing basis into `FUN_00435450`'s legacy yaw basis, with target-derived
elevation and independent pitch bounds. Explicit attachment-local offsets now add to the DAT muzzle
instead of being ignored. This is engine support only; no combo is promoted from these descriptors.

Audited Satoko 2 state400's actual request rows: ordinary fires row 0 twice and powered fires row 1
twice at tick 20. Both pairs use forward 100, height 70 and lateral -50/+50; pitch comes from the
dynamic scratch value clamped to ±40, and yaw uses actor heading plus the movement offset. The
powered predicate is byte `+0x845 != 0` AND word `+0x848 != 0`; the ordinary branch is its inverse.
The latter is the `+0x300` aim-selection team's hold against player 0, maintained by
`FUN_00421e30` / `FUN_0041f580`, not simply the remake's per-owner combat-lock (`+0x304`) hold.
Therefore the existing `TargetLocks::holding_ally` value is not wired into Satoko firing. The
source movement offset and numeric scratch conversion also still need a live runtime input path.

**Verification:** source findings were cross-checked against `FUN_0043ffc0`,
`FUN_00421e30`, `FUN_0041f580`, `FUN_004220e0`, and the normalized `FUN_00435450` contract.
No tests or build were run; the typed engine changes remain uncommitted and unvalidated. Satoko 2
remains pending, as do all other combo completion cells.

**Next:** represent the original aim-selection target/team and `+0x848` hold separately from the
combat lock, then bind Satoko 2 state400's two row-specific branches with the measured origins and
pitch conversion. Extend that path to air and charge bodies only after their movement, counter,
freeze, row-admission and projectile-controller behavior are represented. Then add the whole-frozen-
interval counter/event model, starting with Rika 1 state450. Keep exact cosine-table parity open.

### 2026-10-10 — 3.0 Decision record, powered gate recovered, Rika 1 repaired, Satoko 2 tap bound

**Decisions first:** [ginkiha-shooting-architecture.md](ginkiha-shooting-architecture.md) records the census
that explains the blocker count (841 bodies / 43 combos / 1,632 origin calls / 514 powered-gate reads /
70 RNG bodies), the corrections below, and five architecture decisions (D-S1..D-S5). It supersedes the
plan's step-0 "normalize helper signatures" framing where it conflicts: the gate predicate was the missing
piece, not a new normalization pass.

**Corrections established from source:**
- The powered gate is `byte +0x845 && word +0x848`. The handoff's "word `0x212`" is the runtime
  simulator's *array index* for byte offset `0x848` (its `w[]` is an int array); the decompiled EXE
  agrees in the other direction (`param_1[0x212]` with `int*`). The plan's `+0x848` was correct.
- `TargetLocks::holding_ally` **is** word `+0x848`. The port already models it (180-tick hold,
  re-pinned per tick while the aim selection shares player 0's team, `FUN_0041f580:242-248`); it simply
  was not wired to firing. No new field had to be recovered.
- `byte +0x845` is the **Oyashiro special armed** byte: `FUN_004220e0` sets it (`charge1 = duration1`),
  gated on mode byte `+0x318 == 1` with `limit1 (+0x32c) <= charge1 (+0x83c)`; `FUN_0041f580:88-92`
  clears it when the countdown ends. `+0x318` is the same 0/1/2 selector as `Hypermode`'s enum order, so
  the port predicate is exact: `m_hyperActive && m_hypermode == Oyashiro && allyHold`.
  Consequence: a Friendship/Kakera fighter never takes a powered branch, and in 1v1 nobody can — both
  branches are team-play only.
- The usage catalog's "tag", the oracle fixture's "special" and the body's "powered" are **one branch**;
  Satoko 2's measured split (normal row 0 twice at 20F, tag row 1 twice at 20F) confirms the identity.

**Done — engine:** `MoveRule` gained `gate`/`gateValue` and `MoveOp::Counter`/`CounterSet`; the executor
evaluates gates and drives a per-move counter reset with the move (`set_state`, init/reset/respawn), not
per section. `Fighter` exposes `shoot_gate_powered()` and a narrow `ShootingContext` the scene publishes
each tick from `TargetLocks::holding_ally` (match.cpp). Dead vocabulary from the earlier
typed-origin work (WorldPosition, LegacyDegrees, Facing, Direction and their fields) was removed in the
pre-commit diff review; the surviving families each have a user.

**Done — Rika 1 450/460 repaired** (the known-incorrect program, now first because it needed no new
origin family): the tick-30 salvo is counter-gated (`counter > 0 && counter % 10 == 0`) and fires **three
times** while the clock is pinned for 30 updates by a `kGateCounterBelow 60` Hold ordered after the
counter increment, the twin requests carry the measured lateral ±50, and the powered branch's rows 4/7
are now bound alongside the normal 3/6.

**Done — Satoko 2 tap bound** (`kSatoko2Rules`, 400/402): the measured twin at tick 20 — forward 100,
lateral −50/+50, height +70, legacy-basis yaw, elevation pitch clamped ±40 — with the normal/powered row
split, the 15°/20° turns and the 0.5 bleed. This is the first real user of the typed origin/aim specs.
450/460 stay pending with their measured parameters recorded in the ledger.

**Verified:** `cmake --build build/linux` 63 targets; full `ctest` **65/65 (167.41 s)** with the fighter
suite at 730 checks (Rika's frozen interval now counted over the whole 30-update freeze; Satoko 2's twin
worlds, row split and gate read from a live fixture); recon 6/6; Windows and web cross-builds; a live
2-player battle of 2400 frames / 852 logic ticks at 64 Hz, RESULT ok. The uncommitted typed-origin work
that resumed this session is now built, tested and included in this slice.

**Next:** the whole-frozen-interval model is now reusable — audit the other `Hold` schedules against
their bodies before trusting their tests (Tomitake 2, Keiichi 2, Satoko 0). Then Keiichi 0/1's hand
origin (`FUN_00435220`, `Bip01_R_Hand`/`Bip01_L_Hand`) with a posed-rig witness, then Kasai 0 as the
first C++ handler with the pool/allocation audit. Wire the battle movement offset (`source_float(0x19)`)
into the world yaw, and re-pin Satoko 2 450/460 (phase 1, tick 6, row 4/5, tick-26 ten-update freeze).

### 2026-10-10 — 3.1 Corrections found in review, plus a live powered witness

**Done — three review findings fixed:**

1. **Rows 3/6 were missing `kGateNormal`** in both 450 and 460, so a powered fighter fired
   both the normal and the powered tick-30 pair — 10 requests over the charge instead of
   the body's 8, and extra ammunition spent. The body selects one pair per branch.
2. **The Rika charge geometry was still the legacy adapter's**: lateral ±50 requested
   forward 70 / height 70 and a ±1° yaw nudge. That adapter encodes Rena 0's measured
   red-charge shape (`FUN_0043ffc0.c:1526-1543`: forward 70, lateral 70, height +70, yaw
   ±1.0 — a real angle offset, not a bug), so it must not be reused for other bodies.
   Rika's charge now uses typed specs with its measured forward 60 / lateral ±50 /
   height +70 and no yaw offset, and the test pins those numbers so the next body cannot
   quietly inherit the wrong ones.
3. **The ally-hold mapping is downgraded from "exact" to "analogue".** The maintenance
   shape is right but the producer is not: the original re-pins `+0x848` while this
   fighter's aim-selection target (`+0x308`, a player **pointer** — `FUN_0041f580.c:221`
   dereferences it and reads `+0xaecc` off the result) equals player 0's; the port pins
   it from the combat lock (`+0x304`) when that names an ally. `target_lock.h`'s own
   header reads the comparison as "shares player 0's team", which the pointer evidence
   contradicts; that is now a recorded work item with its blast radius
   (`Match::lock_holds_ally`, the HUD ring, two test suites) instead of a silent claim.

**Retracted:** the claim that powered branches are impossible outside team play. It
follows only from the port's predicate; under the original's, fighter 0 holds it in any
match, 1v1 included. Also recorded: the port arms Oyashiro on a Special press where the
original arms it automatically at `limit1 <= charge1`, and its countdown is seconds
against the original's tick-based `+0x83c`.

**Done — witnesses:** the Rika test now counts both branches over the whole frozen
interval (normal 3/6 ×3, powered 4/7 ×3, 8 requests each, no leakage) and pins the
geometry; and a new live 4-fighter match drives the powered branch through `Match`'s
own lock maintenance — an ally lock on fighter 0 makes the scene spawn item row 1, a
hostile lock keeps row 0. That witness proves the port's producer, not the original's.

**Verified:** full Linux suite **65/65**, fighter suite **755 checks / 0 failures**,
recon 6/6. Windows and web cross-builds and the live battle smoke re-run after these
edits.

**Next:** settle the `+0x848` producer (model `+0x300`, or keep the analogue and say so
everywhere), then Keiichi 0/1's hand origin, then Kasai 0 as the first C++ handler with
the pool audit. The 1v1 powered availability question rides on the producer work.

### 2026-10-10 — 3.2 Pitch latch, air-copy witness, and a counting fix

**Done — the pitch is latched, not re-derived.** `shoot_body_4_1_450` computes the target
elevation once at tick 10 (`FUN_0042da80` → `FUN_0066b668` → `write_scratch(0x3c)`) and reads
it back for the frozen tick-30 salvos. The port was recomputing it per launch, so a target
that changed height between the two would silently re-aim the later salvos.
`MoveOp::CapturePitch` + `ShotAimKind::StoredPitch` now latch it (keeping the original's
integer truncation), and **106 bodies** read `0x3c` more than once, so this is a roster
mechanism rather than a Rika fix.

**Done — the air copy is witnessed end to end, both branches.** `460` was untested in
both branches. Reaching it exposed two port behaviors worth writing down: a Jump press
returns before the charge block (one tick lost, then the charge re-accrues), and a plain
leap's 47-update air window is too short for the 60-update program, so the witness holds
Z against the fly budget to reach ~112. The air frozen interval then fires all three
pairs per branch (powered 4/7, normal 3/6) with the opposite gate correctly off. What the
air copy still does not show: the fired yaw omits the battle movement offset, and the
source's phase0/tick0 velocity/gravity clears have no `MoveOp` — both documented, both
blocking any full-fidelity claim for this area.

**Done — the live witness no longer double-counts.** It appended every living projectile
on each update until it had two entries, so one surviving twin could satisfy the
assertion. It now reads the SPAWN update only, which is where both requests of a volley
appear together.

**Verified:** full Linux suite **65/65 (166.6 s)**, fighter suite **788 checks / 0
failures**, recon 6/6, Windows and web cross-builds, live battle smoke RESULT ok.

**Next:** the `+0x848` producer (model `+0x300`, or commit to the analogue everywhere),
then Keiichi 0/1's hand origin, then Kasai 0 with the pool audit. The latched-pitch
mechanism is expected to be needed by dozens of bodies, so keep using it rather than
re-deriving elevation per launch.

### 2026-10-10 — 3.3 Recovered aim-selection producer replaces the analogue

**Done — the `+0x848` producer is source-backed.** The full trace closed all four
fields: `+0x300` (aim selection, init 0, written only by the 0x2a cycle),
`+0x304` (combat lock, closed writer set), `+0x308` (aim-target actor pointer,
proven by the `+0xaecc` dereference at `FUN_0041f580.c:221`), `+0x30c` (15-tick
pulse), `+0x848` (180 on cycle iff aim targets match; cleared by direct-set and the
state-0x1e gate; re-pinned iff match, else decayed). Commands 0x2a/0x2b reach the
writers from `FUN_0063c2a0`; player 0 is index 0 of the player list.

**Done — the boundary.** `TargetLocks` carries the `+0x300` aim layer (`m_aim[]`,
`m_aimHold[]`) beside the behaviorally untouched combat-lock layer; gestures move the
aim with the lock, direct-set clears the shooting hold without touching the aim,
maintenance re-picks carry the aim, and the per-tick re-pin/decay has no liveness
test exactly like the original. `Match::aim_holds()` feeds `ShootingContext::aimHold`
(renamed from `allyHold`); the combat lock, ring, pulse, bot retarget gate and camera
are identical — their suites pass unmodified, and no production HUD/bot/camera code
ever read the hold value. Deliberate divergences kept and labelled: no state-0x1e
gate, no aim re-pick on selection-invalid, enemies-only tap cycle.

**Done — Oyashiro settled.** Threshold `limit1` = 850 (700 Hanyu+1) from DAT
`parameters[4]` is auto-satisfied (the corpus never increments `+0x83c`, so no
accumulation gameplay gates the arming; the runtime bridge's seed is an invention).
Countdown `duration1` = 900 ticks (1800 Hanyu+1 only) from `parameters[5]` — the
port's 15 s matches 45/46 combos, halves Hanyu+1's 30 s (recorded, needs DAT plumbing
to fix). Activation stays player-driven (Special press at full gauge) vs the
original's automatic first-frame arming, and 15 s at 64 Hz runs ~7% long — both stated.

**Done — witnesses.** Aim-layer units (init, player-0 trivial hold, shared/diverged
2v2 aims, gesture updates, direct-set clear, 300-tick expiry, death persistence,
rematch reset, 1v1 permanence: 266 lock checks); live 1v1 powered twin with no gesture
plus Friendship control with admission separated per magazine; live 2v2 shared-aim
powered vs diverged-aim normal through one scene drain; live death (locks+aims re-pick
together onto the survivor, holds re-pin) and rematch (reset restores init). No roster
expansion: still 13 programs + Satoko 2 tap + 5 deferred + 25 TODO.

**Verified:** full rebuilt Linux CTest **65/65 (184.24 s)**, fighter suite 822 checks,
lock suite 266 checks, recon six tests passed. Windows and web reviewed cross-builds
passed; neither platform was executed for this slice. Linux native 2-player battle
smoke (1200 frames) RESULT ok; rematch logic (reset path) covered by unit and
Match-level tests.

**Next:** Keiichi 0/1's hand origin (`FUN_00435220`), then Kasai 0 with the pool audit.
The movement-offset yaw and the remaining gaps in §6 of the architecture record are
the next fidelity items after the roster unblocks.

### 2026-10-10 — 3.4 Keiichi 0/1 bound: hand origins, snap pitch, range pitch

**Done — both combos bound** (`kKeiichi0Rules`, `kKeiichi1Rules`, handlers 0x46a190 /
0x473610): taps as single hand requests at tick 13 (Bip01_R_Hand, rows 0 + 3/1, stored
pitch), charges at tick 4 (Keiichi 0 only: left hand row 1, fixed angles) and tick 20
(Keiichi 0: attachment slot 0 rows 2/4; Keiichi 1: world rows 9 + 2/3 at lateral -50 /
forward 0 / height +40/+20). All branches gate on the recovered powered predicate; the
`FUN_00435000` row mapping the handoff called unestablished resolves to slot 0 with rows
2 normal / 4 powered straight from the body tuple.

**Done — three pitch mechanisms, all measured:** the air-tap discontinuity (compare
±30, assign ±45, in 9 bodies) rides on `CapturePitch`'s new assign bound; Keiichi 1's
charge pitch (base plus live `dist*40/5000`, ×0.95 when negative, horizontal distance
only) is the new `ElevationPlusRange` kind (2 bodies use it, named honestly); literal
yaw/pitch requests use the new `FixedAngles` kind. `NamedBone` gets its first real
users plus the `origin_named_bone` factory; a rig missing the bone fails explicitly.

**Verified:** full rebuilt Linux CTest **65/65 (203.48 s)**, fighter suite 878 checks 0
failures (56 new Keiichi checks: hand KIND + bone names, row splits on both branches,
tick-4/tick-20 charges, forward-60/lateral-50 geometry, range pitch exact at sin(4°)),
recon six tests passed, Windows and web cross-builds passed, live 2-player battle smoke
RESULT ok. Table pins for both combos already existed in the shared origin-pin loop;
no new pins needed.

**Still pending for both:** movement-offset yaw, air velocity/gravity ops (entry halve,
movement clear, gravity tails), second charges (no 360/370 bodies in scope). The ledger
carries the per-path cells; the handoff scoreboard is now 13 + 2 subsets + 5 partial
typed programs (Satoko 2 tap, Keiichi 0, Keiichi 1) + 3 deferred + 25 TODO.

**Next:** Kasai 0 as the first C++ handler with the pool audit (21/31 requests, spread,
global-32 capacity), then the roster families. The latched-pitch, snap-pitch and
range-pitch mechanisms are expected to recur — keep using them.

### 2026-10-10 — 3.5 Ledger order: Rena 0 powered branches, Rena 1 fan, Rena 2 RNG-blocked

**Done — Rena 0 audited and extended** (handler 0x43ffc0): every launch site was gated on
the recovered predicate and every powered row was missing. Tap 400 rows 0/6, air tap 402
rows 1/7, charge 450/460 rows 2/8 (all `FUN_00434fd0` = slot-0 attachment) are now
gate-bound. The charge pitch is a **fixed 45° constant** (`0x42340000`), not the scratch —
`FixedAngles` carries it and the old `pitch 45` adapter value is replaced. The 360/370
freeze is counter-gated (init 0, +1, release at 10) like Rika's, replacing the plain
`Hold 10` — 22 updates to clear tick 13, witnessed by draining the interval.

**Done — Rena 1 audited and extended** (runtime source, not a body): the tap is a
**15-roll fan at frames 12..26** (row 1 normal / 3 powered), not a single frame-18
anchor — the earlier note read the ground-phase helper only. The fan is bound per-frame
with the row split; its per-shot `draw()%10` spread stays an explicit gap. The 450 charge
is the single fixed-45 attachment shot (rows 2/8). 402/460/360/370 stay unbound.

**Done — Rena 2 audited and documented as blocked**: no body exists at all; the handler
`FUN_00438310.c` gives a fully measured state400 volley at phase 1 tick 35 — one
attachment row 0/2 plus ten world rows 1/3, each with pitch `rng()%30+20`, yaw
`heading+offset+90 − rng()%180` and a 200-forward/+30-high position. The EXE trace
confirms 11 requests but the harness fixes the RNG, so all ten rows read identical
coordinates. **Deliberately not bound**: without a per-shot draw the program would fire
ten stacked projectiles, which the completion contract forbids. It is a one-step port once
Kasai 0's deterministic shooting RNG lands — same blocker, same queue.

**Verified:** full rebuilt Linux CTest **65/65 (168.55 s)**, fighter suite 905 checks 0
failures (Rena 0/1 rewrote the 27-section test; 37 new powered/freeze checks), recon six
tests passed, Windows and web cross-builds passed, live 2-player battle smoke RESULT ok.
No roster expansion; ledger rows and the handoff scoreboard updated.

### 2026-10-10 — 3.6 Ledger order: Mion 0 fully bound, 1/2 taps, RNG isolated as the gate

**Done — Mion 0 audited and repaired** (handler 0x4582a0). Three real defects fell out:
(1) every powered row was missing (0/4 on the taps, 2/3 on the charges — the gate switches
the row, never the slot); (2) the ground tap fired at elapsed tick 2 in ANY phase, which is
phase 0 in practice, while the body's condition is phase 1 tick 2; (3) the charge bound row
0 where the body fires rows 2/3. The 402 air tap was misread as "two rows" when it is two
SLOTS with the same row, so the old program fired a powered row on the normal branch and
never touched slot 1. Now bound: phase-1 slot-0 tap (±30) plus the phase-3 slot-1 follow-up
(±40, contact-gated), the three dual-slot counter volleys at 15/20/25, the asymmetric
[-40, +45] charge clamp, and counter-gated freezes of 30 and 20 updates replacing plain
`Hold` values that only coincided.

**Done — Mion 1 and 2 audited.** Mion 1's 400 has the same slot-0/slot-1 split with a
contact-gated phase-2 follow-up and a repeated one-frame hold; its 402 fires both slots at
counter 13. Mion 2's 400 force-writes its tick counter from 10 to 18, so ticks 11..17 never
run — the port places the launch on the teleport update and shifts every later window by
seven, which moved the tick-23 freeze to elapsed 15 (the pre-existing rule had it at 23).

**Done — the shared mechanisms the family needed:** `origin_attachment_slot` (slot 1 was
unreachable before), `kGateContact` (the `0 < w[0x1b7]` "has connected" flag that 186 bodies
guard on, with no writer in the corpus so the mapping is by role), `kGateCounterEquals` and
`kGateCounterAbove` (the bodies' scratch counters survive a phase change while the phase
tick does not — FUN_00421100 zeroes `+0xadfc`), and `CapturePitch` now taking separate low
and high bounds, because 12 bodies clamp asymmetrically (Mion 0 [-40,+45], Shion 0
[-70,+40], Akane [-15,+55]).

**Blocked, and now precisely so — the draw service.** Mion 1's 450/460 (15-iteration bursts,
rows 1/5, yaw `(rand%200-100)*0.1`, pitch `(rand%100-50)*0.1`) and Mion 2's 450/460 (rows
2/3, yaw `(rand%100-50)*0.1`, pitch `(rand%80-40)*0.1`, plus the `0 < w[0x1c8]` gate with no
writer) cannot be bound faithfully without it, and neither can Rena 2's ten-shot ring. The
original RNG is recoverable: `FUN_0065d150` is standard MT19937 and `FUN_0065d0c0` seeds it
with the canonical 5489, so a deterministic port RNG can match the algorithm, the modulo
ranges and the draw counts even though stream position will not match (no bit-matching is
attempted). That is the next mechanism, ahead of Kasai 0, which needs it too.

**Verified:** full rebuilt Linux CTest **65/65 (176.91 s)**, fighter suite 933 checks 0
failures (new sections 38/39: dual-slot volley counting, the exact +45 high bound against a
+40 symmetric clamp, and the contact gate discriminating both ways), recon six tests passed,
Windows and web cross-builds passed, live 2-player battle smoke RESULT ok.

**Next:** the deterministic shooting RNG (MT19937 + per-body draw ranges) to close Mion
1/2's charges and Rena 2, then Kasai 0's scatter, then the remaining families.

### 2026-10-10 — 3.7 The deterministic draw service; Mion 1/2 charges and Rena 2 bound

**Done — the RNG is recovered, not invented.** `FUN_0065d150` is stock MT19937: the twist
reads `mt[i+397]` below 227 and `mt[i-227]` above (the two base pointers `DAT_006d3804` and
`DAT_006d2e44` are mt+397*4 and mt-227*4), selects the 0x9908b0df matrix word through a
two-entry table by the low bit, and tempers with the canonical `>>11`,
`(<<7)&0x9d2c5680`, `(<<15)&0xefc60000`, `>>18`. `FUN_0065d0c0` is `init_genrand`, and the
re-seed path calls it with 0x1571 — **5489, MT19937's own default seed**. `simulation_rng.h`
reproduces it and is pinned against the canonical seed-5489 vector
(3499211612, 581869302, 3890346734, 3586334585, 545404204), so a wrong twist, matrix word,
temper mask or seed fails the test rather than quietly shifting every spread.

**Done — the spread boundary.** `ShotSpreadSpec` states each axis as
`(modulo(n) + offset) * scale`, because that is literally the bodies' expression. The draw
order is pitch-then-yaw: every measured family loads the pitch draw first and the yaw draw
second, and the witness pins both against the canonical stream (the first burst request
pitches at `(3499211612 % 100 - 50) * 0.1 = -3.8` degrees and yaws at
`(581869302 % 200 - 100) * 0.1 = +0.2`), so swapping the order fails. A zero modulus
consumes **no** draw, so a deterministic rule cannot shift the stream for later spreads.
`MoveRule::repeats` carries the bodies' `for` loops — Mion 1 runs 15 iterations inside tick
17 and Rena 2 runs 10 — and each iteration re-draws, which is what makes the volley a fan.

**Done — three families closed:** Mion 1's 450/460 (15-shot fans, rows 1/5, the 460 clamp
being the ±30-compare/±45-write mismatch), Mion 2's 450/460 (phase-1 emissions, rows 2/3),
and Rena 2's state 400 outright (one slot-0 attachment at fixed angles, rows 0/2, plus the
ten-world ring at 200 forward / +30 high, rows 1/3). Rena 2 had no recovered bodies at all,
so the handler was the only source and nothing is claimed for its 402/450/460.

**Fixed in passing:** the +5-degree air-tap turn on Mion 0's 402 was gated on the wrong
bound — `kGateCounterAbove` reads `gateValue2` and the rule passed only one bound, so the
extra turn would have applied from counter 1 instead of 16.

**Recorded gaps, not hidden:** the port applies the spread to the DIRECTION only, while the
original also rotates the attachment (so the muzzle's positional offset is not reproduced);
and Mion 2's emissions still ignore the `0 < w[0x1c8]` gate, a field at byte +0x720 with no
writer anywhere in the corpus — its usage (`0 < +0x2b8 && +0x730 == N && 0 < +0x720`,
`< 5` picking a voice line) reads as an input hold counter, but that is inference, so the
port treats the gate as satisfied rather than inventing a source.

**Verified:** full rebuilt Linux CTest **65/65 (171.06 s)**, fighter suite 962 checks 0
failures (sections 40-42 pin the RNG vector, the draw order against it, and the ring's
count/rows/range), recon six tests passed, Windows and web cross-builds passed, live
2-player battle smoke RESULT ok.

**Next:** Keiichi 2's audit (the last unaudited member of the Keiichi trio), then Satoko
0/1/2, then Kasai 0 — whose scatter is now unblocked.
