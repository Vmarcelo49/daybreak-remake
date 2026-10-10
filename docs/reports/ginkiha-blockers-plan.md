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
