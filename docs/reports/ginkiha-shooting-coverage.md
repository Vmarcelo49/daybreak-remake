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

## Character iterations — current work

Work proceeds in roster order, with all of a character's legal weapon combos audited together.
The first iteration is [Rena+0/+1/+2](ginkiha-rena-iteration.md). Ground taps and first charges
are now tested together against the original handlers, with Rena+0's second-charge world pair
also checked across its natural phases. Air transitions, additional states and projectile
lifecycle gates remain explicit dependencies; this is not three completed combos.
Hanyu and Natsumi have two legal weapons each, so their iterations contain two combos.

## Correction: the "no flag field" notes are wrong

Several recovered tables say a powered/tag branch was skipped because the body has "no flag
field". **That is false.** The gate is `byte(+0x845) && word(+0x848)` (word index `0x212`) — the predicate
the port models as `kGatePowered` — and it was verified directly in seven bodies: Keiichi 2 (`4_0`/`2_2`), Satoko 0
(`3_0`), Rika 0 (`4_0`), Rika 2 (`4_2`), Chie 2 (`11_2`), Takano 0 (`7_0`) and Irie 1 (`10_1`).
All seven have since been rebound with it.

**Every site that carried the claim has now been re-read**, and each row/count branch turned
out to test the same idiom — so the list is empty:


Rika 2's note was also wrong, and re-reading its body showed the branch hides two further
gaps that a flag alone would not fix. Its TAG branches are now bound — the tap fires three
`Bip01_R_Hand` requests on rows 0, 2 and 1, and the charges fire three fan requests on row 6
against row 4 normally. What remains is the **NORMAL** tap's row selector: `w[0x9e]` picks
row 2 below 0, row 0 in [0,1) and row 1 otherwise, and `w[0x9e]` is READ throughout the corpus
but **never written anywhere in it**, so it has no recovered source. That rule keeps the row-0
reading the traces show, and every request's pitch stays 0 even though scratch `0x3c` is
filled with the clamped ±40 target elevation and then unused.

### Correction: the hand helpers' third argument is a YAW, not a position

A review of the committed spread work found a real error that had propagated across four
combos. `FUN_00435220`'s third argument — the one Rika 1's tap, Satoko 0's fan, Chie 2's burst and
Tomitake 2's tap all draw into — is **not** a muzzle offset. `FUN_00435220` is a thin wrapper over
`FUN_00435250`, which does this at `0x4352a0`:

```
fVar3 = FUN_0065d010(param_7 + actor[0x5c] + actor[100]);
```

i.e. it ADDS the value to the bone's own angles and runs the sum through the sin/cos table. It is
a **yaw offset in degrees**, so it swings the shot; it never moves the muzzle. Only
`FUN_00435450`'s world form takes a perpendicular POSITION, and those families state that per rule
through `origin_actor_relative`.

`SpreadAxis::Lateral` therefore adds to the aim's yaw now, not to the bone's local offset. The
build and the four witnesses agreed with the wrong version because they read the value back out of
the field the binding had written it to — the same self-confirming shape as the constant and axis
errors above. The witnesses now assert a swing: Satoko's five requests fan by direction, Chie's
burst widens shot by shot, and Tomitake's row-5 shot swings off its deterministic row-7 partner.

**Witness quality, corrected after a second review.** The first replacement witnesses were too
loose, and one bound was mathematically wrong:

* **Chie 2's sweep is deterministic** — no draw, the counter steps by 3 between the shots the gate
  lets through — so its offsets are exactly −1.5, 0, 1.5, 3. The witness now pins the 1.5° spacing,
  the monotonic direction and the 4.5° span. Only the global SIGN stays open, because the body adds
  the value to the bone's angles while the witness measures yaw against the fighter's facing; that
  convention is a named follow-up rather than a range. A "span between 4 and 8" would have accepted
  wrong spacing, order or direction.
* **Satoko 0's bound was wrong.** Each offset is `(draw%240-120)*0.1`, so an INDIVIDUAL offset lies
  in [−12.0, +11.9] and two shots may differ by 23.9 — a "half-span ≤ 12.5" check can reject a
  valid fan. The witness now checks each offset against the body's own bounds, and separately
  asserts that all five shots leave the muzzle in one place.
* **Rika 1's muzzle check was too weak.** `|position.x| < 1000` proves nothing. It now asserts the
  resolved `localOffset` is exactly zero for every shot, which the rule's own spec sets and only the
  spread could change.

**The yaw inversion is explained, and now stated as a convention rather than left open.** A
third review traced it to the resolver: `FUN_00435250` aims at `legacyYaw = 90 − actorHeading +
offset`, and the resolver's legacy kinds build the direction as `(cos legacyYaw, _, sin
legacyYaw)`. Converting back to the remake's yaw gives

```
shotYaw − fighterFacing = −offset
```

The remake-basis kinds use `yaw = facing + offset` directly. Every hand family here binds
`aim_target_elevation`, which returns `ActorHeadingTargetElevation` — the LEGACY kind — so their
body offsets reach a witness **negated**. That is why `−1.5°` measured as `+1.5°`, and it is a
conversion, not an unexplained bone rotation.

With the convention established:

* **Chie 2's signed values are pinned exactly** — `remake_yaw_for_legacy_offset(−1.5, 0, 1.5, 3)`.
  Spacing and monotonicity alone would have permitted the whole sweep to shift.
* **Satoko 0's bounds are converted with the offsets**: `(draw%240−120)*0.1` is [−12.0, +11.9] in
  the body, i.e. **[−11.9, +12.0]** at the shot, so the raw bounds would have rejected a valid +12.
  Rika 1's `draw%14−7`, i.e. [−7, +6], converts to [−6, +7] and is checked the same way.
* The comment claiming the helper adds the offset to "the bone's angles" was wrong: it adds it to
  the **actor's heading and movement offset**; the bone matrix supplies the ORIGIN only.

Closed by `fighter_script_test` section 45 (2026-10-11): Rika+1's normal ground state400
pins all 15 requests for seeds 5489 and 37; Satoko+0's normal/powered ground state400 pins
all five/eight requests. Expected yaw and pitch use independent `std::mt19937` draws and
body formulas, not runtime spread descriptors. The next unused draw verifies total consumption.

Every launch position is compared with the named hand's pre-update animated rig position,
transformed independently at nonzero actor positions and two headings. Rika+1's witnesses
sample different animation ticks and distinguish the left hand from Prop1, the right hand,
and the actor root. This verifies the remake's posed-hand launch boundary, not original global
RNG stream alignment or the untested air/powered Rika paths. The old zero-`localOffset`
regression assertion is superseded by these position checks.

### Correction: which axis the displacement uses

A body's world position is built from **two** table lookups: the table at `yaw` gives the forward
components and the table at `yaw + 90` (`0x42b40000`) gives the perpendicular ones. Reading which
one a constant multiplies is what decides `origin_actor_relative(right, forward, height)`.

* Rika 0's tap multiplies the **`yaw + 90`** table by ±50 and the `yaw` table by 10, so the pair
  is `(±50, 10, 70)` — **lateral**, not forward. The first binding had it as forward ±50, and its
  witness could not tell the difference because the pair is 100 apart either way; the witness now
  checks the pair's X separation, the shared forward line and the 10-unit forward offset.
* Keiichi 2's charges multiply the **`yaw + 90`** table by −50 and pass height +40, so they are
  `(-50, 0, 40)` — a pure lateral offset, not the attachment the adapter implied.
* Rika 0's charges multiply the `yaw + 90` table by ±25 and the `yaw` table by 50, giving
  `(±25, 50, 50)`, and they pass an explicit world yaw and pitch instead of the target
  elevation: `±5`/45 at tick 15 and `±10`/30 (450) or `±10`/40 (460) at tick 25. The witness
  checks all of it — 50 apart laterally, 50 in front, 50 up, 10 degrees of yaw separation, and
  the fixed 45 pitch.

### Correction: float constants must be decoded, not eyeballed

Two bindings this pass quoted a displacement or height that the hex does not say, and one of
them shipped:

* Rika 0's world pair was noted as `+-600` on the taps and `+-50` on the charges. The taps are
  `0x42480000` = **50**, and the charges `0x41c80000` = **25**. The tap is now bound at ±50 and
  witnessed at 100 apart / 70 above; the charge note is corrected.
* Satoko 1's periodic shot was bound at `origin_actor_relative(0, 0, 600)` and its note said
  "600 units UP". The body says `0x42480000` = **50**. The binding and the witness are both
  corrected, and Satoko 1's ledger cell now reads `+50 @h50`.

The second one is the instructive failure: **the witness asserted 600, the binding's own
constant**, so it could only ever confirm the binding against itself — it passed for a whole
slice while being wrong. A witness has to take its numbers from the body, which is why the
world-geometry witness added here checks a 100-unit separation and a 70-unit height that come
from the constants rather than from the rules. Decimal literals in the decompilation (the
`draw%12-6)*0.25` spreads, the integer clamps like `0x28`/`0x1e`) are safe; hex floats are not.

### Open: the move table has no state transition

Irie 1's state 401 fires a two-slot attachment request at tick 15 and then, after tick 29, JUMPS
to one of four follow-up states (0x19b/0x19c/0x19a/0x191) chosen by the signs of `w[0x9e]`/
`w[0x9f]`. Two things stand in the way, and neither is a rule:

* `MoveOp` has no state-transition operation, so a rule cannot request the jump; and
* 401 is not in Irie 1's `{400, 402}` mapping, so changing which state the tap enters would move
  the phase progression the traces validate.

That is a product change (a new op plus a progression decision), not a binding, and it is the
concrete blocker behind the follow-ups. The direction plumbing added for Rika 2 already carries
the sign test 401 needs.

### Decode: `w[0x9e]`/`w[0x9f]` are the COM's movement direction

Rika 2's normal tap picks its item row from `w[0x9e]` (row 2 below 0, row 0 at 0, row 1 above),
and Irie 1's state 401 picks one of four follow-up states from the signs of **both** `w[0x9e]`
and `w[0x9f]`. That pair is `(+0x278, +0x27c)`, and the corpus settles it:

* **Only two functions write it**, `FUN_0043f4d0` and `FUN_00447730`, and both are the COM
  decision routines — they drive `+0x278` to −1/0/+1 from a wander timer `+0x864 ∈ [−200,199]`
  and from squared-distance tests (`< 250000`, `< 122500`, `< 90000`), setting `+0x278` and
  `+0x27c` together.
* **All 471 other references are reads** — the movement, action and shoot code branching on the
  direction. The port's own `bot_brain.h` already documents this field as "a 3×3 movement
  direction in +0x278/+0x27c" and models the timer, which corroborates the decode from the
  other side.

So it is an **AI decision**, not a player input: a human-controlled fighter never has it
written, leaves it at 0, and therefore takes Rika 2's **row 0** branch and Irie 1's no-direction
branch.

**Bound (2026-10-10).** `ShootingContext::moveLateral` now carries the sign, `Match::step`
publishes it for **AI slots only** (derived from the applied direction keys, which is how the
port expresses the brain's intent), and three exclusive gates `kGateDirLeft/Neutral/Right`
state the branches. Rika 2's normal tap carries `kGateNormal | kGateDir*`, so the direction
picks the NORMAL row while the powered branch still fires all three. The witness drives all
three signs and gets rows 2, 0 and 1. A human slot keeps 0, so its behaviour is unchanged.

### Correction: which field the tag branch actually reads

Writing this up exposed a second, subtler error in my own notes. Several said "the tag branch
reads `w[0x1b7] < N`". That is **not** the row/count gate. Every body that chooses a powered row
or count tests

```
byte(+0x845) != 0 && word(+0x212) != 0
```

which is exactly the pair `kGatePowered` models (`0x212 * 4 == 0x848`, the aim hold the scene
publishes; `+0x845` is the Oyashiro armed byte). `w[0x1b7]` is a *different* field: in Chie 2,
Rika 0, Takano 0 and Irie 1 it only picks the **sound** played on the first burst tick, and in
Tomitake 2 it is an outer gate on the whole burst. The bindings were right — the justification
quoted in those comments was not, and all six are corrected.

### Correction: the spread axis order is now total

The first cut of the draw-order table named only the two axes a family draws, so an order
that did not mention an axis **silently dropped that axis's draw** — it happened twice, first
to Satoko 0's lateral (`PitchThenYaw` has no lateral) and then to Chie 2's. `spread_axis_order`
now returns all three axes for every order: the named pair in the stated order and the
remaining axis last. No measured family configures all three, so the trailing position is
unobservable, and no spec can lose an axis to an order it did not consider.

### Editing hazard: identical rule lines across tables

Several families fire on the same tick with identical text — Chie 2's and Rika 2's 400 taps are
both `{400,-1,15,15,MoveOp::Launch,0.f,0.f,40.f}`, and Takano 0's 402 matches Rika 2's. A
file-wide string replace therefore lands in the wrong table, which is exactly what happened
while binding Rika 2: the edit silently rewrote **Chie 2's 400 and Takano 0's 402** instead.
Scope an edit to the array (locate `kXxxRules[] = {` through its closing `};` and operate on
that substring), and assert the occurrence count *within that scope*.

| Combo | Swap / item | Tap ground | Tap air | Charge 1 ground | Charge 1 air | Charge 2 ground | Charge 2 air | Available body count |
|---|---|---|---|---|---|---|---|---|
| Rena 0 | 1 / 1 | 400 Prop1 fallback @12, integer ±30 / row6 powered | 402 bound; audit pending | 450 slot0 @13 fixed45 / row8 powered | 460 bound; audit pending | 360 phase2 tick2 world rows11/12, signed offsets; freeze10 | 370 binding corrected; air audit pending | 1 |
| Rena 1 | 2 / 3 | 400 slot0 row6 @18 / rows0 then9 powered | — / landing phase2 tick5 pending | 450 model2 on slot0, 15-shot yaw sweep @12..26 / row3 powered | — / @15..29 source audited, lifecycle pending | — / row8 pitch70 @16 source audited | — / landing transition pending | 0 |
| Rena 2 | 3 / 33 | 400 attach rows0/2 + ten-world ring rows1/3 @p1t35; exact RNG/geometry | — / landing graph pending | 450 right hand @40, integer ±40 / rows4/5 | — / @36 source audited; landing recovery pending | — / dispatcher and seek pending | — / dispatcher and seek pending | 0 |
| Mion 0 | 4 / 2 | 400 slot 0 @p1t2, rows 0/4 gate-bound; phase-3 slot 1 contact-gated | 402 dual-slot volleys c=15/20/25, rows 0/4 gate-bound | 450 slot 0 @17 rows 2/3, clamp −40/+45, freeze 30 | 460 slot 0 @17 rows 2/3, freeze 20 | — / P | — / P | 30 |
| Mion 1 | 5 / 4 | 400 slot 0 @p1t2 rows 0/4, slot 1 @p2t1 contact-gated rows 0/4 | 402 dual-slot volley c=13, rows 0/4 | 450/460 spread-bound: 15-shot fan @17 rows 1/5 | — / P | — / P | 30 |
| Mion 2 | 6 / 35 | 400 slot 0 @teleport-tick 10, rows 0/1 | 402 slot 0 @18, rows 0/1, freeze 10 | 450 phase-1 emissions @15..60 rows 2/3, spread-bound (+0x1c8 unmodelled) | 460 same as 450 | — / P | — / P | 24 |
| Keiichi 0 | 7 / 5 | 400 hand R, gate-bound / rows 3 powered | 402 hand R, gate-bound / rows 3 powered | 450 hand L + attach, gate-bound / rows 4 powered | 460 hand L + attach, gate-bound / rows 4 powered | — / P | — / P | 20 |
| Keiichi 1 | 8 / 18 | 400 hand R, gate-bound / rows 1 powered | 402 hand R, gate-bound / rows 1 powered | 450 world pair, gate-bound / rows 3 powered | 460 world pair, gate-bound / rows 3 powered | — / P | — / P | 19 |
| Keiichi 2 | 9 / 34 | 400 sweep, gate-bound / rows 1 powered | 402 sweep, gate-bound / rows 1 powered | 450 world -50 lateral @h40 @13, range pitch, rows 2/3 | 460 same, rows 2/3 | — / P | — / P | 18 |
| Satoko 0 | 10 / 8 | 400 hand fan, gate-bound / rows 1 powered | 402 hand fan, gate-bound / rows 1 powered | 450? / P | 460? / P | — / P | — / P | 18 |
| Satoko 1 | 11 / 17 | 400 periodic +50 @h50, gate-bound / rows 1 powered | 402 periodic +50 @h50, gate-bound / rows 1 powered | 450 tick-35 pair + periodic, bound | 460 tick-35 pair + periodic, bound | — / P | — / P | 18 |
| Satoko 2 | 12 / 38 | 400 twin world, gate-bound / rows 1 powered | 402 twin world, gate-bound / rows 1 powered | — / P | — / P | — / P | — / P | 18 |
| Rika 0 | 13 / 7 | 400 world lateral +-50, fwd 10 @h70, rows 0/1 gate-bound | 402 same, rows 0/1 gate-bound | 450 world lateral +-25, fwd 50 @h50, yaw +-5/+-10, pitch 45/30, rows 2/3 | 460 same, pitch 45/40 | — / P | — / P | 20 |
| Rika 1 | 14 / 19 | 400 hand L, 15-shot window counter-gated, spread-bound / no branch split | 402 attach @13 rows 1/7 gate-bound | 450 attach @13 rows 2/8 fixed 45° | 460 attach @12 rows 2/8 fixed 45° | — / P | — / P | 19 |
| Rika 2 | 15 / 37 | 400 hand R, normal rows 2/0/1 by COM direction, tag 3x rows 0/2/1 | 402 same, direction- and tag-bound | 450 attach @10 rows 4/6 tag-bound | 460 attach @10 rows 4/6 tag-bound | — / P | — / P | 19 |
| Shion 0 | 16 / 6 | — / P | — / P | — / P | — / P | — / P | — / P | 25 |
| Shion 1 | 17 / 20 | — / P | — / P | — / P | — / P | — / P | — / P | 18 |
| Shion 2 | 18 / 36 | — / P | — / P | — / P | — / P | — / P | — / P | 25 |
| Tomitake 0 | 19 / 12 | — / P | — / P | — / P | — / P | — / P | — / P | 19 |
| Tomitake 1 | 20 / 21 | — / P | — / P | — / P | — / P | — / P | — / P | 15 |
| Tomitake 2 | 21 / 42 | 400 slot0 row 7 + row 5/6 gate-bound, spread-bound | 402 rows 7 + 5/6 gate-bound | 450 world fwd 50 @h75, row 4 pitch 0 / rows 0/+2 | 460 same, rows 0/2 | — / P | — / P | 20 |
| Takano 0 | 22 / 11 | 400 R-hand 3x @12/15/18, rows 0/6 gate-bound | 402 same, rows 0/6 gate-bound | 450 slot0 @18 rows 1/7 gate-bound | 460 slot0 @17 rows 1/7 gate-bound | — / P | — / P | 30 |
| Takano 1 | 23 / 22 | — / P | — / P | — / P | — / P | — / P | — / P | 28 |
| Takano 2 | 24 / 41 | — / P | — / P | — / P | — / P | — / P | — / P | 30 |
| Ohishi 0 | 25 / 9 | — / P | — / P | — / P | — / P | — / P | — / P | 19 |
| Ohishi 1 | 26 / 23 | — / P | — / P | — / P | — / P | — / P | — / P | 21 |
| Ohishi 2 | 27 / 39 | — / P | — / P | — / P | — / P | — / P | — / P | 26 |
| Akasaka 0 | 28 / 10 | — / P | — / P | — / P | — / P | — / P | — / P | 19 |
| Akasaka 1 | 29 / 24 | — / P | — / P | — / P | — / P | — / P | — / P | 17 |
| Akasaka 2 | 30 / 40 | — / P | — / P | — / P | — / P | — / P | — / P | 16 |
| Irie 0 | 31 / 13 | — / P | — / P | — / P | — / P | — / P | — / P | 19 |
| Irie 1 | 32 / 26 | 400 world 2x rows 1/0, tag 4x rows 3/2/1/0 gate-bound | 402 same, gate-bound | 450 attach @22 rows 4/5 gate-bound | 460 attach @17 rows 4/5 gate-bound | — / P | — / P | 19 |
| Irie 2 | 33 / 43 | — / P | — / P | — / P | — / P | — / P | — / P | 19 |
| Chie 0 | 34 / 14 | — / P | — / P | — / P | — / P | — / P | — / P | 23 |
| Chie 1 | 35 / 25 | — / P | — / P | — / P | — / P | — / P | — / P | 21 |
| Chie 2 | 36 / 44 | 400 burst 4x R-hand, rows 0/1 gate-bound, lateral sweep | 402 burst 5x L-hand, rows 0/1 gate-bound | 450 R-hand @22 rows 2/3 gate-bound | 460 R-hand @15 rows 2/3 gate-bound | — / P | — / P | 23 |
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
- **A stated draw order across three axes.** The spread's axes are drawn in the order the
  body states, named per rule: `PitchThenYaw` (most families), `YawThenPitch` (Keiichi 2),
  `PitchThenLateral` (Satoko 0) and `LateralThenPitch` (Rika 1). Rika 1 is the family that
  draws the LATERAL first, and its witness pins that: shots 1-3 must offset the hand by
  1, 1 and -5 and pitch at -3, 0 and -4. Swapping the draws moves all six values.
- **The periodically-repeating world shot.** Satoko 1's weapon is not a salvo at all: a
  countdown starts at 120, drops one a tick, and the request fires whenever it is
  `1 mod 30`, in *every* state of the family — ticks 28, 58, 88. `kGateCounterMod` already
  tests `counter % n == 0`, so the binding starts the counter at 118 and lands on the same
  ticks; no new op was needed. Only the first fire lands, because the port's tap move lasts
  about 40 ticks while the body's family runs ten states — a state/duration gap, recorded.
- **A per-request lateral offset for the hand fans.** `ShotSpreadSpec::lateralModulus`
  moves the bone origin's own local offset, which is what `FUN_00435220`'s third argument
  is: Satoko 0 draws `(draw%240-120)*0.1` per request, so her five- and eight-shot salvos
  come off the posed hand as a fan rather than five identical pellets. This also fixed a
  latent bug: the `NamedBone` resolver read the *spec's* offset, so any spread that moved
  the resolved offset would have been silently dropped.
- **A counter-driven yaw sweep and a per-rule draw order.** Some bodies do not fire
  straight: Keiichi 2's tap grows a scratch by 2 a tick and aims `scratch - 15 + draw%10`,
  so the volley walks across the arc. `ShotSpreadSpec::yawPerTick` adds
  `counter * yawPerTick` before the jitter (the counter is the move's own `MoveOp::Counter`,
  which is what the scratch is), and `SpreadOrder` states which axis draws first because
  Keiichi 2 is the one family that reads the YAW draw before the pitch.
- **The deterministic draw service.** `simulation_rng.h` reproduces the original's
  stream algorithm — `FUN_0065d150` is MT19937 and `FUN_0065d0c0` seeds it with 0x1571
  (5489, the canonical default) — pinned against MT19937's own seed-5489 vector, so the
  distribution, modulo ranges and per-request draw counts match the bodies. It does not
  claim stream POSITION: the original draws from one global stream in its own frame order.
  `ShotSpreadSpec` states each axis's modulus/offset/scale, a zero modulus consumes no
  draw (so a deterministic rule cannot shift the stream), and the draw order is
  pitch-then-yaw because every measured family loads the pitch draw first. `MoveRule::
  repeats` carries the bodies' `for` loop so a volley lands in one tick with a fresh draw
  per iteration.
- **Attachment slots, contact gating and counter cadences.** `FUN_00435000`'s slot is
  now first-class (`origin_attachment_slot`), because several bodies pick slot 1 for a
  follow-up (Mion 0's 400 phase-3 and 402, Mion 1's 400 phase-2 and 402) and some fire
  BOTH slots on one trigger. `kGateContact` is the port's analogue of the `0 < w[0x1b7]`
  "this move has connected" flag that 186 recovered bodies guard on; `+0x1b7` has no
  writer in the corpus, so the mapping is by role. The scratch counters gain
  `kGateCounterEquals`/`kGateCounterAbove` alongside the existing below/mod gates,
  because the bodies' counters survive a phase change while the phase tick does not.
- **Asymmetric pitch clamps.** `CapturePitch` now states both ends (low in `second`,
  high in `third`, optional snap in `value`). Twelve bodies clamp asymmetrically —
  Mion 0's 450 is [-40, +45], Shion 0's [-70, +40], Akane's [-15, +55] — and Mion 1's 460
  is the compare/assign mismatch (±30 tested, ±45 written) that the snap half covers.
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
