# Knockdown, tech-roll and get-up system — recovered map and port gap (2026-10-29)

Scope: the shared post-hit ground system (every combo), as it bears on the pilot's
"Rena+0 is perfect" claim. Research only; nothing here is implemented yet.

Evidence tiers, highest first:

- **Tier 2** — recovered code with an address: `FUN_00428510` handlers 0x2d/0x67/0x74/
  0x76/0x77/0x78/0x79/0x7c/0x80 (and the 0xcb/0xd5..0xd8 mirrors), the timer owner
  `FUN_0041f580`, the two state predicates `FUN_004236c0`/`FUN_00423700`, and the hit
  path `FUN_00637950`. Binary SHA-256
  `27e61475fbb3ea67f5058e3e0e6e93ad71d16a4d83fa42b02e605913a6a07f02`.
- **Tier 3** — the reconstructed runtime bodies in
  `.local-analysis/daybreak-rebuild/DaybreakRebuild-20261010/source/src/`
  (`battle_common_hit_motion.hpp`, `battle_hit_stagger.hpp`, `battle_hit_timers.hpp`,
  `battle_air_hit_landing.hpp`). They fill the branches not yet re-read in the binary
  and are labelled as such.
- The port's current implementation is described from `fighter.cpp`/`fighter.h` and is
  **not** evidence for the original.

## 1. The recovered flow

```
hit lands (FUN_00637950)
  stagger meter +0x7b8 += combat[7]*resist/100, window +0x7bc = 120
  if it trips:
     down meter +0x7c0 += combat[8], window +0x7c4 = 120
     row = combat[13] (grounded && +0x7c0 < 100) | combat[14] (heavy) | 121 (record flag 0x800)
     back hit: row += 100, impact bearing += 180
     if +0x7c0 >= 100  ->  invincible +0x7ac = 30
     write movement yaw offset +0x64 = -(facing - impact)
  row handler runs (+100 variants mirror front/back)

flight rows 113/114/115 (and 213/214/215 back)
  on touchdown with vertical speed < 0:
      front 113/114/115/116 + jump held + down(+0x7c0) < 100 -> 45
      otherwise front -> 118, back 213..216 -> 119 (no tech branch)
  45: +0x7ac/+0x7b0/+0x7b8/+0x7c0 cleared, velocities zeroed
  118/119: state + down<100 decides the lying row

45 (tech roll)
  speed = -25 (backwards along facing), vertical = 12.5
  frame < 26: vertical -= 1.0; if speed < -10 -> +0.5
  frame == 25 and airborne: hold; frame == 26: speed = 0
  completes -> Idle

118/119 (lying)
  completion (FUN_004218c0) -> 120
  if airborne again -> 103/203 (fall), vertical zeroed

120 (get-up)
  completion: if input x == 0 && input z == 0 -> 128 (in place)
              else                        -> 124 (roll get-up)
  124: phase 0 steers at 180 deg/tick; phase 1 steers at 3 deg/tick, speed 10, and
       leaves past 150 ticks, or past 30 with a button counter live; phase 2 speed 0
       (FUN_00428510 case 0x7c)
  128: no movement; if airborne -> 43 (FUN_00428510 case 0x80)

invincibility (+0x7ac):
  FUN_0041f580, while hitstop +0xa0 == 0:
      FUN_00423700 true (state in 124..129 or 194) -> +0x7ac = 30 every tick,
          and +0x7b8/+0x7bc/+0x7c0/+0x7c4 zeroed
      FUN_004236c0 false (state < 100 or > 299)   -> +0x7ac decremented
```

Tier-2 reads behind each line. One tier-3 disagreement was resolved by the binary:
`battle_air_hit_landing.hpp` lists only 113/114/115 as tech-capable, but cases 0x71..0x74
(front 113..116) all carry the branch and the back rows 0xd5..0xd8 carry none.

| Branch | Evidence |
|---|---|
| roll on landing, `down < 100`, jump held | `FUN_00428510` cases 0x71..0x74 (front 113..116): `param_1[0x1f0] < 100 && param_1[0xa0] != 0` -> `FUN_00421080(0x2d)`, `param_1[0x1eb] = 1`, velocities 0 |
| 45 body | case 0x2d: clears `+0x7ac/+0x7b0/+0x7b8/+0x7c0` at frame 0; speed `-25`, vertical `12.5`; frame<26 gravity 1.0 and speed floor -10 with +0.5; frame 26 speed 0 |
| 118/119 -> 120 | cases 0x76/0x77: complete -> 0x78 (120); airborne -> 0x67 (103) / 0xcb (203) |
| 120 -> 124/128 by stick | case 0x78: `param_1[0x9f] == 0 && param_1[0x9e] == 0` -> 0x80 (128), else 0x7c (124); 0x9e/0x9f are +0x278/+0x27c, the input axes |
| 124 body | case 0x7c: phase 0 `param_1[0x21d] = 180`, phase 1 `param_1[0x21d] = 3`, `param_1[0x15] = 10`, leave on `param_1[0x3a] > 150` or `> 30` with `param_1[0xa0..0xa2]` (word indices: the button counters at bytes +0x280/+0x284/+0x288, not hitstop), phase 2 speed 0 |
| 128 body | case 0x80: airborne -> 0x2b (43), else speed 0 |
| i-frames of 124..129/194 | `FUN_00423700` returns true for `0x7c..0x81` and `0xc2`; `FUN_0041f580` sets `+0x7ac = 30` and clears the meters on that predicate |
| decrement gate | `FUN_004236c0` returns true for 100..299; the timer block runs only when it is false |
| down meter -> 30 i-frames | `FUN_00637950`: `+0x7c0 += combat[8]`; if `+0x7c0 > 99` -> `+0x7ac = 30` |

## 2. What the port has today

- `FighterState::Knockdown` is a two-phase port state: row 118/119 chosen by
  `m_reactionMove >= 200`, then row 120, then Idle. The phase length is a port-only
  `m_stateTimer`; the row itself plays through `present_move`.
- There is **no** tech roll (45), **no** 120 -> 124/128 choice, **no**
  `124..129` invincibility, **no** `+0x7ac` timer, **no** 103/203 down state, **no**
  121 flagged ground roll, **no** wall bounce (133), and **no** down/knockdown meter
  semantics: `m_hitMeterB` accumulates `meterB` and selects the heavy row, but it is
  not reset by the 120-tick timer the original uses and never grants invincibility.
- The back-hit yaw is applied, but the original only rotates when the current state is
  outside 100..299 (`FUN_004236c0`); the port rotates unconditionally.
- `120` completion currently always returns to Idle; the original always passes
  through 124 or 128, so the victim is never invincible while standing up.

## 3. Why this matters for the claim

A launched victim in the port cannot:

- tech the landing with Jump (45) and erase the down meter — the original's escape
  from a juggle;
- choose a rolling get-up (124) or an in-place get-up (128) with the stick;
- be invincible during the get-up (the 30-tick refresh), so follow-ups that the
  original whiffs always connect here;
- fall back into 103/203 when hit again while lying;
- take the flagged ground-roll reaction (121, damage x0.7) instead of the ordinary
  knockdown row;
- bounce off a wall into the 113 flight (133);
- be pushed toward the heavy row by the down meter with its 120-tick memory.

Every one of these changes combo routes, proration opportunities and wake-up pressure.
The "Rena+0 is perfect" claim therefore cannot be made while the port only has
"lie down, stand up, no protection".

## 4. Open items before implementation

1. **Row data**: confirm phases/durations/windows for 45, 103, 118..121, 124, 128,
   133, 134 in the real `NN.dat` (the handlers read `+0x2b81` frame and
   `FUN_004218c0` completion; the port's `move_row_frames` is a port approximation and
   must not become the authority).
2. **45 collision/hitboxes**: does the tech roll have any hit reaction or is it fully
   untargetable? The handler clears `+0x7ac` at frame 0, so the 1-tick flag set at
   landing may only cover the transition; the 124..129 refresh is the durable i-frame
   window, not 45.
3. **Exact input fields**: `+0x278/+0x27c` are the stick axes the port already samples;
   confirm the dead zone and whether a held direction at the moment 120 completes is
   enough (tier 2 says "nonzero", the bundle uses `(x||z)`).
4. **KO state 194**: the same invincibility predicate covers it; the port's KO handling
   is separate and must not inherit a 30-tick i-frame by accident.
5. **Damage flag 0x800**: which shipped records carry it (the reconstructed stagger body
   chooses 121); if no Rena+0 record carries it, the branch is latent for the pilot but
   still part of the shared body.

## 5. Implementation status

- **Stage 1 — done (2026-10-29).** The knockdown chain now advances on row completion
  (`advance_animation_phase` -> `FUN_004218c0`'s predicate), not on `m_stateTimer`:
  118/119 complete into 120; 120's completion reads `stick_x/stick_y` and binds 124
  (held) or 128 (neutral); both complete into Idle. `bind_recovery_row` restarts the
  phase clock, 124's gated phase 1 cancels into phase 2 after 30 frames once the player
  acts (case 0x7c), and `m_invincible` (+0x7ac) refreshes to 30 every tick while
  124..129 plays, then decays outside the reaction range. `try_melee_hit` and the
  projectile contact path both honour it (FUN_00637950's `+0x7ac < 1` test).
  Regression: `melee_rules_test` -> `test_knockdown_getup_chain` (chain, both get-up
  choices, i-frame value, rejected swing vs the same swing after decay). Suite 84/84.
- **Stage 2 — done (2026-10-29).** On touchdown from a front flight row (113..116)
  with Jump held and `+0x7c0 < 100`, the victim now teches into row 45 instead of
  118/119; back rows keep 119. Binding clears the stagger/combo meters and `+0x7ac`,
  sets speed -25 and vertical 12.5, and row 45 runs the recovered law (gravity 1.0 and
  the -10 speed floor until frame 26, then speed 0) before completing into Idle.
  Regression: `test_landing_tech_roll` (tech row, meter reset, -25/tick, completion,
  the no-Jump 118 branch and the back 119 branch).
- **Stage 3 — done (2026-10-29).** `+0x7c0` is now the down meter: combat[8] adds on a
  trip, the 120-tick window only ticks outside the reaction band (FUN_004236c0), 100
  grants 30 i-frames, and the heavy row is chosen at 100 or while airborne. The
  stagger meter keeps its own per-tick window. Regression: `test_down_meter_semantics`
  (60 -> 110, i-frames at the threshold, heavy row 130, frozen during the reaction,
  cleared on the 120th idle tick).
- **Stage 4 — done for the reachable part (2026-10-29).** The 0x800 record flag
  (`FUN_00637950`'s `+0x28 & 0x800`) now overrides the reaction row with 121 (221 from
  behind), scales the blow to 70% before the HP math, and its completion enters the
  120 get-up (case 0x79). It is injected-tested because **no shipped Rena+0 record
  carries the flag**: a scan of every phase-0..n entry asserts zero flagged records
  and zero records naming 121, 133 or 103 as a reaction. 103/203 and the 133 wall
  bounce therefore have no requester and no reachable port path (no ledge/knock-off
  and no wall-contact signal in the reaction step); they stay documented limits
  rather than untestable code, and `test_shared_recovery_reachability` fails if the
  shipped data ever changes that.
- **Stage 1 correction (2026-10-30).** Stage 1 misread the word indices `0xa0..0xa2` as
  hitstop and omitted the 150-tick exit, so a neutral victim stayed in 124, invincible,
  forever. Row 124 now follows case 0x7c: stick steering, speed 10, both exits, buttons
  only, and the +40/+5 meter refill. 120's choice reads the held axes, including the
  keyboard and the dead zone. Row 45 zeroes vertical from frame 26, holds frame 25 while
  airborne and stops without drift. Shots now skip an invincible victim before any
  contact work (`FUN_00637950:74`). Regressions: `test_getup_roll_body`,
  `test_tech_roll_end` and the `animation_data_test` pass-through case. Port mapping
  (tier 6): the steering turns `m_facing` as the dash does, not a separate `+0x64`
  offset, and `+0x288` maps to Shoot or Special as the charge assertion does. Airborne
  124/128 -> 43 still has no path.

### 5.1 Proposed order (original)

1. Knockdown data + timers: play 118/119/120 through the row data (completion, not
   `m_stateTimer`), add 124/128 choice and the 124 phases, and the 124..129 i-frame
   refresh + `+0x7ac` timer.
2. Landing tech: the 45 branch (jump held + `down < 100`), 45's motion, and the meter
   reset it performs.
3. Down meter: 120-tick window, `+0x7c0` accumulation/reset, 30 i-frames at >= 100,
   and the heavy-row selection using it.
4. Shared extras: 103/203 fall-back, 121 flagged ground roll, 133 wall bounce.

Each step needs install-backed tests that fail before the change, with rows driven by
real input through `take_damage`; injected-contact tests are allowed only where no
shipped contact reaches the row (the Q24 precedent) and must say so.

## 6. Limits of this report

Nothing here was observed on the original runtime (no tier 1). The tier-2 reads cover
the branches named in the table; the 103/203/121/133/134 details come from the tier-3
reconstruction and still need a binary read before they are implemented. The row data
for the shared recovery rows was not dumped in this pass.
