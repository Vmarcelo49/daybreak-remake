# Launch contracts — initial normalized evidence

2026-10-10. Step 0 of [the shared blocker plan](ginkiha-blockers-plan.md).
Target: DaybreakDX.exe SHA256
`27e61475fbb3ea67f5058e3e0e6e93ad71d16a4d83fa42b02e605913a6a07f02`.
These are source/disassembly findings, not a claim that the remake implements them.

## Callback operands and ordering

| Original helper | Normalized arguments, excluding implicit manager `this` | Evidence / limit |
|---|---|---|
| `FUN_00435000` | attachment slot, item row, yaw offset, pitch, retarget-from-muzzle flag | `research/decompiled/FUN_00435000.c`; slot indexes manager bone/prop binding, row indexes manager's 12-byte registration. Direction normally uses actor heading + movement offset + yaw offset; nonzero flag recomputes horizontal aim from the muzzle. General transform/flag geometry still needs dedicated tests |
| `FUN_00435220` | bone matrix, item row, yaw offset, pitch | wrapper calls `00435250(matrix,row,0,0,0,yawOffset,pitch)`; zero local offsets, not an attachment muzzle. Named hand origin must use the looked-up transform |
| `FUN_00435450` | item row, world X, world Y, world Z, absolute legacy yaw, pitch | original bytes `0x435450–0x435553`; six stack args, explicit position forwarded independently of direction |

The original world direction is
`(cos(yaw)*cos(pitch), sin(pitch), sin(yaw)*cos(pitch))` in its angle convention.
The remake convention instead uses `(sin(yaw), 0, cos(yaw))` for horizontal forward;
convert at the boundary, not by relabeling an original angle. The original trig helpers
use a 3,600-entry cosine table and degree-to-index conversion, not unconstrained libm
sin/cos: `0x65d010–0x65d040` subtracts a quarter-turn before table lookup;
`0x65d050–0x65d07a` is the cosine lookup. Ghidra's exported `int` return and extra
arguments are inaccurate: original bytes load one float argument and return via x87.
Exact table indexing/rounding remains a required geometry gate.

All three origin families select admission by **item row**, not attachment slot or
charge tier. The world helper reads `manager+0xf4` row table, stride 12, signed magazine
index at row+8 (`0x4354a9–0x4354bd`). Negative index bypasses magazine consumption;
otherwise it calls `00435920` on `manager+0x24+magazineIndex*0x44`
(`0x4354f4–0x435511`). Only successful admission invokes projectile creation at
manager vtable+0x0c. Target comes from actor+0x38. Consumption occurs before that
creation call; a later pool rejection must not automatically refund it.

The signed row index is loaded from the first bullet-table field of item DAT:
`FUN_00433eb0` reads it into row+8. The existing `BulletDefinition::magazine` is the
corresponding field. Missing raw row mappings for world callbacks can now be resolved
through the real item registration, while spawn behavior remains separately pending.

## Magazine admission, not tier cost

`FUN_00435920`, confirmed against bytes `0x435920–0x43598f`, receives one magazine:

| Magazine offset | Meaning supported by constructor / archive |
|---|---|
| +0x00 | mode |
| +0x08 | capacity in rounds |
| +0x0c | reload threshold |
| +0x10 | shot interval |
| +0x18 | remaining rounds |
| +0x3c | reload progress |
| +0x40 | cooldown / interval progress |

Reject if rounds==0 or signed cooldown < signed shot interval, without mutation.
On success, clear reload progress if starting full, decrement rounds once, clear cooldown,
and clear reload progress if now empty. Repeated callbacks each run this test: a twin
request can admit its first row and reject its second. A negative magazine index admits
without touching either stock. Reload threshold is not the admission cost; current
`fire_shot` eagerly spending `reloadTime` units is a port rule needing migration.

Do not migrate only `consume`: magazine tick/refill, charge progression, HUD, bots and
move-entry admission currently consume the old `AmmoStock` representation. The next
runtime slice must own and test this boundary explicitly, maintaining both representations
only during a documented migration and preventing double charging.

## Numeric scratch and corrected world geometry

Archive identity was verified against `reference/source-provenance.json`:
`runtime/DaybreakRebuild-20261010.zip`, SHA256
`0c98eba760f06404150f0543edb5d1b26c536cf9ad35261780b690c0bdf0843f`.
The following archive entries use the prefix `DaybreakRebuild-20261010/source/`:

- `src/shoot_native_field_types_20260929.hpp`, SHA256
  `c9c39746f618590d58dfc2edfe7c0d8ecba5fc5bfd8a1c6d3f9f21352cf84f02`:
  source words 0x3a..0x3e are numeric integer-to-float conversions; other words use bit
  interpretation. Therefore Satoko/Keiichi scratch pitch must not reinterpret integer
  30 as an IEEE float bit pattern. This is an archive adapter finding; verify the relevant
  original FILD/FIADD sites as each combo is migrated.
- `src/roster_ground_shot400_world.hpp`, SHA256
  `c77cb43621d0da188ca5ea2314c2574be4202ef46ec833df955430f75dcf554f`:
  corrected state400 world geometry includes Satoko 2 forward100/height70/lateral±50.
  Its origin follows actor heading while movement offset changes projectile yaw.
- `src/battle_magazine.hpp`, SHA256
  `6b78d15d0aa33934f177ef477f031eb219e5eec8c0bbcf1ffc864c81126219e8`:
  normalized magazine state, consume, tick/refill and charge helpers; compare individual
  original helpers before porting, do not wholesale copy the runtime.

`evidence/roster-ground-shot400.md`'s 2026-09-27 correction reports a 690-record original
world oracle after restoring the native cosine table. That golden TSV is not in the supplied
archive/bundle inventory checked here; reproducing or locating it is an open verification
task. The older JSONL's zero X/Z remains unsuitable as a geometry oracle. The corrected
header addresses ground state400 only; it does not prove air or charge trajectories.

## Freeze semantics: no global launch-once rule

The absence of the documented launch latch is confirmed in current source. However,
adding one globally would also erase source-required repeated firing.
`shoot_body_4_1_450` (Rika 1 + item19) in the supplied header:

- At tick10, normal branch requests world rows2+5.
- At tick30, normal branch requests world rows3+6 only when scratch counter0x3e>0
  AND counter%10==0 (`L23549` predicate). It increments the counter on every update,
  then returns before clock advancement while counter<60 (`L23665–23670`).
- Thus the current static rows3+6 Launch at every visit to tick30 plus Hold30 is not
  equivalent to that counter-gated body. A single launch latch would not fix it either.
  Natural phase/counter initialization and admitted counts still need fixture comparison.

Counter-gated repeated events, one-shot events and clock freezes must be represented
separately. Existing fighter tests checking one pair of pendings do not prove the total
requests over the complete frozen interval. Next: add that whole-interval witness alongside
state-counter implementation, rather than asserting a universal duplicate-suppression rule.

## Live implementation checkpoint — 2026-10-10

`ShootingMagazine` and `admit_shooting_row` now drive bound Fighter stocks. Source
`0043f3e0` charges the secondary magazine at actor+0x708: initial30 updates, then the
secondary DAT threshold. HUD/bot reads, reset/respawn/F4, and callback consumption share
the same stocks. Programmed move entry no longer spends a tier cost. A saturated real
row0 pool test confirms callback consumption is retained when creation fails.

This closes the old eager-spend representation boundary, not launch-origin/counter parity.
Hypermode refill uses the current enum adapter (Friendship3/Kakera2/normal1); complete
raw status/branch parity remains a separate gate. See the blocker plan's latest checkpoint.
