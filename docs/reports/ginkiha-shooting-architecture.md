# Shooting architecture — decisions, corrections and census

2026-10-10. Decision record for [the shared blocker plan](ginkiha-blockers-plan.md).
Companion: [launch/admission contracts](ginkiha-launch-contracts.md),
[the 46-combo ledger](ginkiha-shooting-coverage.md), [the handoff](ginkiha-handoff.md).

This file records **why** the port is shaped the way it is from here on, the
corrections the evidence forced on the existing reports, and the census that sizes
the work. The execution log stays in the blocker plan; the per-combo cells stay in
the ledger.

## 0. Validated starting point

The tree that resumed work carried unvalidated changes (blocker-plan entries 2.1/2.2:
typed origin/aim descriptors with no test and no build). Both gaps are closed:

- `cmake --build build/linux` — 63 targets, exit 0.
- full `ctest --test-dir build/linux` — **65/65 passed (167.60 s)**.

Those descriptors are engine support, not coverage. Nothing in this document promotes
a combo on their basis.

## 1. Why the blocker list grows (measured, not asserted)

Counting the recovered corpus (`reference/source/shoot_native_bodies_20260929.hpp`,
43 combos, SHA256 `235744…c9d`):

| Measure | Value |
|---|---|
| shooting body functions | **841** |
| lines of body source | 98,770 |
| explicit origin-family calls | **1,632** |
| attachment-origin bodies (`FUN_00435000`) | 148 |
| hand-origin bodies (`FUN_00435220`) | 123 |
| world-origin bodies (`FUN_00435450`) | 185 |
| powered-gate idiom `byte(+0x845) && word(+0x848)` | **514 bodies** |
| RNG draws (`FUN_0065d150`) | 70 bodies |
| scratch-counter writes | 518 bodies |
| muzzle-variant events (`FUN_004223d0`) | 493 |

The roster's 46 combos × reachable paths is ~550 hand-encodings against a rule type
(`MoveRule`) with nine ops and three floats. Each encoding that does not fit becomes
a documented gap, each gap becomes a deferral, and each deferral is re-investigated
by the next agent. That is the mechanism producing "way too many blockers" — not a
shortage of evidence, but a mismatch between the body corpus and the rule vocabulary.

Three structural facts follow, and they are the decisions below:

1. **The corpus is 60% non-firing bodies** (movement, clocks, phase transitions,
   prop re-binding, effects). They still have to be right, but they need no new
   primitives — they need the ones already there plus gates.
2. **One predicate dominates**: the powered gate is read in 514 of 841 bodies, across
   every action family. One port predicate closes it for the whole roster.
3. **The request schedule is data** (state, phase, tick, row, gate, offsets), while
   the *geometry* is often computed. Both are known per body; neither needs a
   word-bank interpreter.

## 2. Corrections forced by the evidence

These are the revisit items. Each was found while tracing this session and each
contradicts a statement in the current reports.

### 2.1 The powered gate is `byte +0x845 && word +0x848` — the "0x212" is a word index

The blocker plan (2.2) states the gate as `byte +0x845 != 0 && word +0x848 != 0`.
The handoff states it as `byte 0x845 != 0 && word 0x212 != 0`. **Both describe the
same field.** The runtime simulator stores the actor words in an `int` array and
indexes it by word number, so its `w[0x212]` is byte offset `0x212*4 = 0x848`. The
decompiled EXE agrees in the other direction: `param_1[0x212]` with `int* param_1`
is also byte `0x848` (`FUN_0043ffc0.c:1909`). The plan was right; the handoff
transcribed an array index as a byte offset.

### 2.2 The ally hold: same word, NOT the same producer (corrected 2026-10-10)

**Correction:** this section previously claimed the mapping was exact. It is not, and
the retraction matters more than the original claim.

The word is right — `target_lock.h` models `+0x848` as the 180-tick (0xb4) hold with
the correct *maintenance shape* (re-pin per tick vs countdown, `FUN_0041f580:242-248`).
The **producer is different**:

*Original* (`FUN_0041f580:244` and `FUN_00421e30:26-31`): `+0x308` holds the
aim-selection target (`+0x300`)'s actor **pointer** — decisive evidence is
`FUN_0041f580.c:221`, which reads `*(int *)(*(int *)(param_1 + 0x308) + 0xaecc)`, i.e.
it dereferences `+0x308` and indexes a player struct. The hold is re-pinned while
**this fighter's aim target is the same actor as player 0's aim target**. For fighter 0
that comparison is self-referential, so under the original's predicate player 0's
fighter holds it continuously.

*Port* (`target_lock.h:step`): the hold is pinned when the **combat lock** (`+0x304`)
names an ally of the lock's owner.

Two independent differences — a different field and a different comparison. Naming both
values `+0x848` does not make the producers equivalent, so:

- `shoot_gate_powered()` is an **analogue**, not a recovered predicate. Its tests prove
  the plumbing (the context reaches the rule and selects the row) and that the port's
  own producer arms it in a live match; they do not prove parity.
- The earlier claim that powered branches are impossible in 1v1 follows only from the
  port's predicate. Under the original's, player 0's fighter holds it in any match
  including 1v1. **That claim is retracted** and the 1v1 availability is an open item.
- `target_lock.h`'s header describes the comparison as "shares player 0's **team**".
  That reading is inconsistent with the pointer dereference above and should be
  revisited; its blast radius is `Match::lock_holds_ally` (HUD/ring reads,
  `lock_switch_camera_test`, `target_lock_test`) plus this shooting gate, so it needs
  its own slice rather than a silent change.

The work is still worth keeping: it is one predicate with both halves wired and
witnessed, versus a documented skip on 514 bodies. It is a hypothesis to verify, not a
recovered rule.

### 2.3 `byte +0x845` is "the Oyashiro special is armed", not a generic hypermode bit

`FUN_004220e0` (research/decompiled, hash `e06c3b4a…`) arms it:

```
FUN_0064af20(actor_id, 7);
*(actor + 0x83c) = *(actor + 0x330);   // charge1 = duration1
*(byte *)(actor + 0x845) = 1;
```

and its callers gate on `byte(+0x318) == 1` (e.g. `FUN_00445ee0.c:142-145`):
state outside 100/299, not already armed, and `limit1 (+0x32c) <= charge1 (+0x83c)`.
`FUN_0041f580:88-92` clears it when the `+0x83c` countdown reaches zero. `+0x318` is
the same three-valued mode selector as the port's `Hypermode` enum (Friendship 0 /
Oyashiro 1 / Kakera 2 — the value order matches the runtime mapping in
`slot7_native_world.inc.hpp:95-98`). The port's predicate combines that with the
§2.2 hold:

> **powered ⇔ `m_hyperActive && m_hypermode == Oyashiro && ShootingContext::allyHold`**

Two further divergences in this half, recorded so they are not mistaken for parity:

* The original *arms* `+0x845` automatically once `limit1 <= charge1`; the port
  activates hypermode on a Special press at a full gauge. The port therefore cannot
  reach the powered branch until the player presses Special, and the arming threshold
  is not modelled.
* The original's `+0x83c` countdown is in ticks (`duration1` from the DAT); the port
  runs `m_hyperTimer` in seconds (15 s nominal). The gate's *lifetime* differs.

So: a fighter running Friendship or Kakera never takes a powered branch (that much is
firm, it is the mode byte). Whether any given match can reach one at all depends on
§2.2's unresolved predicate, not on the 1v1 fighter count.

### 2.4 The usage catalog's "tag" variant is this branch, not a separate mechanic

`combat-hooks.json` labels the two state-400 usage variants `normal` and `tag`; the
EXE-derived oracle fixture's "special" scenario sets `+0x845` and `+0x848`
(`evidence/roster-ground-shot400.md:13`); the recon tool counts them as
`normal`/`tag`. Satoko 2's measured split confirms the identity — normal fires world
row 0 twice at frame 20, tag fires world row 1 twice at frame 20. So "tag", "special"
and "powered" are one branch with three labels, and the port must stop treating
"tag" as an unknown separate flag (handoff §7).

### 2.5 Rika 1's first charge is already bound *incorrectly*

`kRikaRules`'s 450/460 entries fire rows 2/5 at tick 10 and rows 3/6 once at tick 30
with `Hold 30`. The body (`shoot_body_4_1_450`, bundle lines 23427-23701) says:

| Body statement | Port before the repair | Port after |
|---|---|---|
| tick 10: two world requests, forward **60**, lateral **+50 / −50**, height +70, yaw = heading + movement offset | two requests, lateral 0 | typed specs, forward 60, lateral ±50, height 70 |
| a scratch counter initialized at phase0/tick0 and incremented every update | absent | `CounterSet` + `Counter` |
| tick 30 salvo fires when `counter > 0 && counter % 10 == 0` | fires once, ungated | gated, fires 3 pairs |
| after the counter increment, `if (tick==30 && counter<60) return` — the clock is **frozen** | `Hold 30` (right duration, wrong reason) | `Hold` gated on `counter < 60` |
| while frozen, tick stays 30, so the tick-30 salvo fires at counter 30, 40, 50 — **3 salvos = 6 requests**, plus the tick-10 pair = **8** | 4 requests | **8 requests** |
| branch selection: normal rows 3/6, powered rows 4/7 — ONE pair per branch | powered pair unbound | both bound, `kGateNormal` on 3/6 |

So the existing program under-fired by four requests over the frozen interval. This
is the first repair (§5) precisely because it needs no new origin family: it needs
the counter and the gate, which the whole roster needs anyway.

Two traps found while repairing it, both worth remembering:

* **The tick-30 salvo is not one event.** Sampling a single visit — as the old test
  did — passes even when the program is wrong. The witness now counts every request
  over the whole frozen interval.
* **The legacy `Launch(row, lateral, pitch)` adapter is not a general world model.**
  It encodes Rena 0's measured red-charge shape (forward 70, lateral 70, height +70,
  yaw ±1.0 deg — `FUN_0043ffc0.c:1526-1543`, where the ±1.0 is a literal angle offset,
  not a bug). Rika's charge was briefly routed through it and got forward 70 with a
  spurious ±1° yaw. Any body measuring anything else needs typed specs.
* **The pitch is latched, not re-derived.** `shoot_body_4_1_450` computes the elevation
  once at tick 10 (`FUN_0042da80` → `FUN_0066b668` → `write_scratch(0x3c)`) and reads it
  back for the frozen salvos. Recomputing the elevation per launch re-aims a salvo whose
  target changed height mid-attack — which is what the port did until
  `MoveOp::CapturePitch` / `ShotAimKind::StoredPitch` latched it. **106 bodies** in the
  corpus read `0x3c` more than once, so this is a roster-wide mechanism rather than a
  Rika special case, and the witness drives a dummy that rises 600 units between the
  two salvos to prove the latch holds.

### Reaching the air charge is its own port problem

The air copy needs two things the port does not provide for free: the charge must survive
the leap (a Jump press returns before the charge block, costing one tick before the charge
re-accrues), and the air window must outlast the program (a plain leap is 47 updates;
holding Z against the fly budget extends it to ~112). Both are documented in the witness
so the next agent does not mistake an unreachable path for a broken rule.

### 2.6 Satoko 2's tap geometry is fully measured and needs no new engine type

`shoot_body_3_2_400` (bundle lines 16450-16605): both attachment slots bound
(`FUN_00434a70(0,0)/(1,1)`), turn 15° while tick<20, horizontal bleed 0.5/tick, and
at tick 20 the twin pair — position = actor + 100·forward(heading) ± 50·right(heading),
height +70; yaw = heading + movement offset; pitch = target elevation clamped ±40;
rows 0 normal / 1 powered. The `ActorRelativeOffset` origin and
`ActorHeadingTargetElevation` aim already express this exactly (their 2.2 validation).
What is missing is only the gate and the movement-offset input.

## 3. Architecture decisions

**D-S1 — `MoveRule` stays for schedules; gates and counters are added, not replaced.**
`MoveRule` already carries the 60%-corpus movement/prop/recovery schedules with
proven behavior. Adding an explicit `gate` bitmask and a per-move counter to it is
additive and cannot regress the 13 bound programs. No new rule language is invented.

**D-S2 — The powered gate is one named predicate over port state, not a bundle label.**
`Fighter` gains a narrow shooting context (currently the ally hold) that the scene
publishes each tick, and one predicate `shoot_gate_powered()` implementing §2.3. The
original's `+0x300` aim selection remains the camera's concern; only its `+0x848`
consequence is a firing input.

**D-S3 — No word-bank interpreter, and no generated gameplay rules.**
The recovered bodies stay evidence. Rule tables stay reviewed values with body line
citations, as they are today. The runtime never indexes a decompiler word array; this
is the plan's existing constraint and the census does not change it.

**D-S4 — Complex bodies get focused C++ handlers; the schedule data does not.**
Where a body computes a request from runtime inputs the data model cannot express
(spread loops, child spawning, steering), the port writes a handler that calls the
same shared services (`launch_bullet`'s typed specs, `admit_shooting_row`). Kasai 0's
scatter is the first expected user. The rule table keeps everything that *is* data.

**D-S5 — One pending-shot path, one stock representation, one freeze mechanism.**
The migration notes leave three dual representations (legacy `m_pending` beside the
growable FIFO, `AmmoStock` beside `ShootingMagazine` for unbound fighters, `Hold`
beside a counter freeze). Each dual needs its consumers audited again by every agent.
They are collapsed into the FIFO / `ShootingMagazine` / gated `Hold` respectively as
the affected slices land, with the collapse recorded in the execution log.

## 4. Work sequence

Evidence-normalize → **repair Rika 1 450/460** (correctness first, it is wrong today)
→ **bind Satoko 2 tap** (first real typed-world + gate witness) → Kasai 0 allocation
and spread (first C++ handler, first pool audit) → roster by family, Satoko 1 and the
sparse combos investigated early → gates.

Each slice ships with witness tests and leaves the capability behind for the next
combo; nothing is deferred to a "combat phase" that no one owns.

## 5. What this session implements

1. `MoveOp::Counter` / `CounterSet` + `MoveRule::gate`/`gateValue` in `move_behavior.h`,
   carrying `kGatePowered`, `kGateNormal`, `kGateCounter`, `kGateCounterMod` and
   `kGateCounterBelow`. A gated `Hold` is a bounded freeze whose counter rule is written
   before it, which is how the original's `return`-before-clock-advance is reproduced.
2. `Fighter` shooting context + `shoot_gate_powered()`, published by `Match` from
   `TargetLocks::holding_ally` — an analogue per §2.2, labelled as one in code and tests.
3. `kRikaRules` 450/460 repaired to the measured counter/freeze semantics (§2.5): the
   frozen-interval salvo count, the ±50/60/70 geometry, both branch pairs, and the latched
   pitch (`MoveOp::CapturePitch` + `ShotAimKind::StoredPitch`, which 106 bodies need).
4. `kSatoko2Rules` 400/402 bound: twin world requests, lateral ±50, dynamic pitch
   clamp, powered row selection, turns and bleed. 450/460 stay pending with their
   measured parameters recorded in the ledger.
5. Witness tests: whole-frozen-interval request counts for Rika 1 on **ground and air**
   and on both branches, with the geometry and the latched pitch pinned; the Satoko 2 twin
   worlds and both gate halves from the real item-38 fixture; and a **live 4-fighter
   match** where an ally lock produced by `Match`'s own maintenance switches the fired row
   from 0 to 1. The live witness counts the SPAWN update only, so a single surviving
   projectile cannot satisfy a two-entry assertion.
6. The unused typed vocabulary (WorldPosition, LegacyDegrees, Facing, Direction and
   their fields) removed in the pre-commit diff review.

Validated: build green, full Linux suite 65/65 with the fighter suite at 788 checks,
recon 6/6, Windows and web cross-builds, and a live 2-player battle of 2400 frames /
852 logic ticks. The typed-origin descriptors that resumed the session unvalidated are
included in that validation.

## 6. Still open (recorded, not hidden)

* The `+0x848` producer: the port derives the hold from the combat lock and an own-team
  test; the original derives it from the aim-selection target and a same-target-as-
  player-0 test. Decide whether to model `+0x300` in the port or keep the analogue.
  Until then no powered-branch result is a parity claim.
* The Oyashiro arming condition (`limit1 <= charge1`, automatic) vs the port's
  Special-press activation, and the tick-based vs second-based `+0x83c` countdown.
* The battle movement offset (`source_float(0x19)`) feeding the world yaw.
* Global 32-projectile pool vs original allocation; deterministic spread and RNG draw
  order; per-move state reset on death/respawn/rematch; the legacy no-weapon
  provisional path; exact 3,600-entry cosine-table parity (a measured-tolerance
  decision is required and is not yet made); Satoko 2 charge bodies; every other combo.
