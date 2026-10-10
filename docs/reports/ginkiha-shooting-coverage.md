# Shooting coverage ledger — all 46 combos

Initial snapshot: 2026-10-10. Companion: [blocker plan](ginkiha-blockers-plan.md),
[architecture decisions](ginkiha-shooting-architecture.md).

**Completion: 0/46 audited complete; 3/46 have first programs (Satoko 2 tap, Keiichi 0,
Keiichi 1).** The 18 bound schedules below still require full path verification. No
absence of a generated body proves that a path is absent.

Each ground/air cell is `normal binding / powered audit`. `400?` means state400 is
bound but source, origin/aim, branch/RNG, ammo/admission, motion/clocks, projectile behavior
and verification remain pending. `—` means no runtime binding; `P` means pending.
All 12 paths per combo have pending reachability and completeness audits. Additional
follow-on/EX states remain pending for every combo, not implicitly N/A.

| Combo | Swap / item | Tap ground | Tap air | Charge 1 ground | Charge 1 air | Charge 2 ground | Charge 2 air | Available body count |
|---|---|---|---|---|---|---|---|---|
| Rena 0 | 1 / 1 | 400 attach, gate-bound / rows 6 powered | 402 attach, gate-bound / rows 7 powered | 450 attach, gate-bound / rows 8 powered, fixed 45° | 460 attach, gate-bound / rows 8 powered, fixed 45° | 360 world 11/12 / no branch split | 370 world 11/12 / no branch split | 1 |
| Rena 1 | 2 / 3 | 400 attach fan 12–26, gate-bound / rows 3 powered | — / P | 450 attach, gate-bound / rows 8 powered, fixed 45° | — / P | — / P | — / P | 0 |
| Rena 2 | 3 / 33 | 400 attach + 10 world @35, RNG-blocked | — / P | — / P | — / P | — / P | — / P | 0 |
| Mion 0 | 4 / 2 | 400? / P | 402? / P | 450? / P | 460? / P | — / P | — / P | 30 |
| Mion 1 | 5 / 4 | — / P | — / P | — / P | — / P | — / P | — / P | 30 |
| Mion 2 | 6 / 35 | 400? / P | 402? / P | 450? / P | 460? / P | — / P | — / P | 24 |
| Keiichi 0 | 7 / 5 | 400 hand R, gate-bound / rows 3 powered | 402 hand R, gate-bound / rows 3 powered | 450 hand L + attach, gate-bound / rows 4 powered | 460 hand L + attach, gate-bound / rows 4 powered | — / P | — / P | 20 |
| Keiichi 1 | 8 / 18 | 400 hand R, gate-bound / rows 1 powered | 402 hand R, gate-bound / rows 1 powered | 450 world pair, gate-bound / rows 3 powered | 460 world pair, gate-bound / rows 3 powered | — / P | — / P | 19 |
| Keiichi 2 | 9 / 34 | 400? / P | 402? / P | 450? / P | 460? / P | — / P | — / P | 18 |
| Satoko 0 | 10 / 8 | 400? / P | 402? / P | 450? / P | 460? / P | — / P | — / P | 18 |
| Satoko 1 | 11 / 17 | — / P | — / P | — / P | — / P | — / P | — / P | 18 |
| Satoko 2 | 12 / 38 | 400 twin world, gate-bound / rows 1 powered | 402 twin world, gate-bound / rows 1 powered | — / P | — / P | — / P | — / P | 18 |
| Rika 0 | 13 / 7 | 400? / P | 402? / P | 450? / P | 460? / P | — / P | — / P | 20 |
| Rika 1 | 14 / 19 | 400? / P | 402? / P | 450? / P | 460? / P | — / P | — / P | 19 |
| Rika 2 | 15 / 37 | 400? / P | 402? / P | 450? / P | 460? / P | — / P | — / P | 19 |
| Shion 0 | 16 / 6 | — / P | — / P | — / P | — / P | — / P | — / P | 25 |
| Shion 1 | 17 / 20 | — / P | — / P | — / P | — / P | — / P | — / P | 18 |
| Shion 2 | 18 / 36 | — / P | — / P | — / P | — / P | — / P | — / P | 25 |
| Tomitake 0 | 19 / 12 | — / P | — / P | — / P | — / P | — / P | — / P | 19 |
| Tomitake 1 | 20 / 21 | — / P | — / P | — / P | — / P | — / P | — / P | 15 |
| Tomitake 2 | 21 / 42 | 400? / P | 402? / P | 450? / P | 460? / P | — / P | — / P | 20 |
| Takano 0 | 22 / 11 | 400? / P | 402? / P | 450? / P | 460? / P | — / P | — / P | 30 |
| Takano 1 | 23 / 22 | — / P | — / P | — / P | — / P | — / P | — / P | 28 |
| Takano 2 | 24 / 41 | — / P | — / P | — / P | — / P | — / P | — / P | 30 |
| Ohishi 0 | 25 / 9 | — / P | — / P | — / P | — / P | — / P | — / P | 19 |
| Ohishi 1 | 26 / 23 | — / P | — / P | — / P | — / P | — / P | — / P | 21 |
| Ohishi 2 | 27 / 39 | — / P | — / P | — / P | — / P | — / P | — / P | 26 |
| Akasaka 0 | 28 / 10 | — / P | — / P | — / P | — / P | — / P | — / P | 19 |
| Akasaka 1 | 29 / 24 | — / P | — / P | — / P | — / P | — / P | — / P | 17 |
| Akasaka 2 | 30 / 40 | — / P | — / P | — / P | — / P | — / P | — / P | 16 |
| Irie 0 | 31 / 13 | — / P | — / P | — / P | — / P | — / P | — / P | 19 |
| Irie 1 | 32 / 26 | 400? / P | 402? / P | 450? / P | 460? / P | — / P | — / P | 19 |
| Irie 2 | 33 / 43 | — / P | — / P | — / P | — / P | — / P | — / P | 19 |
| Chie 0 | 34 / 14 | — / P | — / P | — / P | — / P | — / P | — / P | 23 |
| Chie 1 | 35 / 25 | — / P | — / P | — / P | — / P | — / P | — / P | 21 |
| Chie 2 | 36 / 44 | 400? / P | 402? / P | 450? / P | 460? / P | — / P | — / P | 23 |
| Kasai 0 | 37 / 15 | — / P | — / P | — / P | — / P | — / P | — / P | 30 |
| Kasai 1 | 38 / 27 | 400? / P | 402? / P | 450? / P | 460? / P | — / P | — / P | 28 |
| Kasai 2 | 39 / 45 | — / P | — / P | — / P | — / P | — / P | — / P | 30 |
| Akane 0 | 40 / 16 | — / P | — / P | — / P | — / P | — / P | — / P | 30 |
| Akane 1 | 41 / 28 | — / P | — / P | — / P | — / P | — / P | — / P | 30 |
| Akane 2 | 42 / 46 | — / P | — / P | — / P | — / P | — / P | — / P | 30 |
| Hanyu 0 | 43 / 31 | — / P | — / P | — / P | — / P | — / P | — / P | 18 |
| Hanyu 1 | 44 / 32 | — / P | — / P | — / P | — / P | — / P | — / P | 22 |
| Natsumi 0 | 45 / 29 | 400? / P | — / P | — / P | — / P | — / P | — / P | 24 |
| Natsumi 1 | 46 / 30 | — / P | — / P | — / P | — / P | — / P | — / P | 16 |

## Shared capability update — 2026-10-10 (gates and counters)

Bound magazines, row-selected admission and charge counters are live. A programmed
selection no longer spends ammo; callbacks consume their own row, with negative-index
bypass and no refund on pool failure. HUD/bot reads share that stock. The request FIFO
can grow; global32 projectile capacity, geometry, branches/RNG and shot counters remain
pending. The cells above are still pending per-path audit; no combo has been promoted.

Four more shared capabilities landed with this snapshot:

- **Named-bone origins with posed-rig witnesses.** `FUN_00435220` hand requests resolve
  the named bone matrix or fail explicitly (never substitute). Keiichi 0/1 are the first
  users (right hand taps, left-hand charge request). The rig bone-existence check plus
  the origin KIND on the armed request is the witness pattern.
- **Snap pitch, range pitch, fixed angles.** The air-tap discontinuity (compare ±30,
  assign ±45, in 9 bodies) rides on `CapturePitch`'s assign bound; Keiichi 1's charge
  pitch (stored base plus live `dist*40/5000`, ×0.95 when negative) is
  `ElevationPlusRange`; literal yaw/pitch requests use `FixedAngles`.
- **The powered gate.** `byte(+0x845) && word(+0x848)` is now one port predicate
  (`Fighter::shoot_gate_powered()`): the Oyashiro special armed byte plus the aim hold
  the scene publishes from `Match::aim_holds()`. Both branches of a body can now be
  bound, and the port no longer has to skip every tag/powered secondary. 514 of the 841
  shoot bodies read this gate. **The hold's producer is source-backed:** the port carries
  the `+0x300` aim layer and re-pins on the recovered same-target-as-player-0 comparison
  (see the architecture record §2.2). A Friendship/Kakera fighter never takes it; 1v1
  fighters hold by default and 2v2 holders are the ones sharing player 0's aim — both
  demonstrated live.
- **Per-move counters and gated freezes.** `MoveOp::Counter`/`CounterSet` plus
  `kGateCounter*` reproduce counter-gated salvos and clock freezes. Rika 1's 450/460 was
  the first repair: its tick-30 salvo fires three times over a 30-update frozen interval
  (it previously fired once). The same model covers the counter-seeded bodies
  (`write_scratch(0x3e, 0)` at phase0/tick0) without a universal launch latch.

Still pending for every combo: natural reachability, admission/spawn verification,
projectile behavior, and the follow-on states.

## Provenance and resumption

Bound state selectors come from the current `move_program` dispatch, not inferred from
usage. Body counts combine the supplied shooting and full-charge headers; a count is
availability, not an audit. Resolve exact function/ranges and request origins with:

```bash
python3 remake/foundation/tools/ginkiha_recon.py --character=3 --weapon=2
python3 remake/foundation/tools/ginkiha_recon.py --all --output=/tmp/ginkiha-recon.json
python3 remake/foundation/tests/ginkiha_recon_test.py -v
```

Recon checks catalog EXE identity and support-file hashes against the bundle manifest.
It preserves full callback counts and distinguishes attachment-slot operands from bullet
rows. Output cannot establish actual admission, spawn, reachability or geometry.

Snapshot inputs (SHA256):

- `balance-reference/reference-data.json`: `ce2c828b48719e70756c171b09eb22c19df28cea0b8c7dc6cb8afbd9c26e1e2a`.
- `reference/source/shoot_native_bodies_20260929.hpp`: `2357445053b28b6266ccb86406783e2dc14f0c9e3a32c4b47c34068af44dec9d`.
- `reference/source/full_charge_native_bodies_20260929.hpp`: `1cc1794b3cd44718051703237198224151b379f292c742ba85226b0a5a41fd4f`.

`move_behavior.h` is no longer hash-pinned here: it changes with every slice and the
recon tool reports its current hash per run, which is the provenance that matters.

Satoko 2's charge bodies (450/460) are measured and pending: phase 1, tick 6, one
`FUN_00435450` each with forward 100, lateral 0, height +70, rows 4/5 for normal/powered;
the bodies turn 15 while phase<1, the ground charge decelerates 1.5 to zero, the air
charge scales horizontal and vertical velocity by 0.25 at phase0/tick0 and applies
gravity in phase2 after 30F, and both seed a scratch counter at phase0/tick0 and freeze
clock advancement for ten updates at tick26.

Next: follow the append-only execution log in the blocker plan. When a path changes,
update its audit dimensions and evidence here; do not promote a whole combo on a binding
change alone. Replace compact pending cells with links to completed per-path records.
