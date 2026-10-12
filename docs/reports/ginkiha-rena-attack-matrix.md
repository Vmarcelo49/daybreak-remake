# Rena attack matrix — evidence-based status for the full attack port

2026-10-12 · branch `ginkiha-help` · companion to [the attack-animation plan](ginkiha-attack-animation-plan.md),
[the group iteration record](ginkiha-rena-iteration.md) and [the shooting ledger](ginkiha-shooting-coverage.md).

This is the revised working plan for **Rena+0 / Rena+1 / Rena+2** (character 0, weapon
slots 0/1/2 = NN.dat items 1/3/33). It replaces "combo concluded" claims with per-path
status. The port unit is character+weapon+attack path; nothing here promotes a combo.

Sources: the original handlers `FUN_0043ffc0.c` / `FUN_00448220.c` / `FUN_00438310.c`
(read directly), the recovered dispatchers `FUN_00445ee0` (input selector) /
`FUN_0044d850` / `FUN_0043ded0` (situation selector), and the Ginkiha implementation
reference under `.local-analysis/daybreak-rebuild/DaybreakRebuild-20261010/source/src/`
(`battle_rena_melee_admission.hpp`, `battle_rena_{ordinary,directional,followup,landing}_melee.hpp`,
`battle_rena_ground_dash.hpp`, `battle_chasing_air_melee.hpp`, `battle_rena_ground_shot.hpp`,
`battle_rena_mobile_shooting.hpp`, `battle_rena_full_charge.hpp`, `roster_{walk,ground}_shot_admission.hpp`,
`roster_air_dash_cancels.hpp`). Where the donor and the handler disagree, the handler wins;
no discrepancy is currently known for the rows below.

## Conventions

* States are the original's numeric action rows; the port maps them onto
  `FighterState` + `m_attackMoveId` / `m_shotMoveId` + `m_phaseIndex`.
* `normal` = the state word's 0x100 bit (actionable); in the port it is the current
  NN record's `stateFlags & 0x100` during attacks and true for locomotion/air rows.
* `gate(next)` = current row's cancel threshold ≤ candidate row's priority — the same
  comparison the port's 300→301→302 chain already uses (verified pinned behavior).
* `boosted` = special-gauge active+ready chaining (contact-gated). **Landed
  2026-10-12 for the reachable case:** `Fighter::admit_attack_move` ports
  FUN_00445ee0:162-168 / FUN_0044d850:160-167 — grounded + the current row's
  0x2ec8 threshold + the 0x100 window + an armed special state selects 350 for
  weapons 0/1 ahead of the ordinary admission, and `melee_admission_test` drives it
  through the real input path (armed press → 350, unarmed → 300). Two recorded
  deltas: (a) the branch also requires the actor's two other action-intent slots to
  read 1 or 2 — `+0x284`/`+0x288` are produced by the input dispatch FUN_0041efe0
  (it merges the pad array at `+0x9e` into `+0xa0..+0xa2`) and by the COM brain
  FUN_0043f4d0 (1 = attack now, 4 = wander), so they are input intents rather than
  unknown flags; their button identities are not established and the port's single
  melee press stands in for them, a slightly LOOSER gate; (b) the port's
  `m_hyperActive` carries the armed
  hyper states while the aim-lock-only arming (`+0x844` without a hyper state) is
  not published to admission. Chains still honor the 0x100 window in general.
* Weapon-specific families are facts, not assumptions: the admission table below is
  the recovered selector itself, so "absent for weapon 2" means the dispatcher never
  selects it — not a missing row.

## Status vocabulary (claims discipline)

Every path below states its status with four distinct labels, and a path only
carries one at a time:

* **selection implemented** — the input situation resolves to the row through the
  recovered dispatcher; nothing about the row's own body is claimed.
* **execution implemented** — the row's movement/vertical/phase/exit contracts are
  bound (rules or bodies) from the recovered sources; contact windows still ride
  NN.dat's posed records where the donor defers to them.
* **automated verification** — an input-driven test pins the named behavior
  (melee_admission_test's sections). Passing tests establish the behavior those
  tests exercise; they do not prove zero regressions throughout the game.
* **live parity** — a silent native run compared against a comparable original
  run. No path in this matrix currently holds this label. **Exact limitation
  (2026-10-12):** the 320/332 lean sign and the model-2 frame have no comparable
  reference here — the parity bank (`remake/tests/parity-baseline/`) holds the
  deleted DX9 REMAKE's captures, not the original's, and none of them is an aerial
  pose; `remake/docs/reference/` (the original's own prints) has no aerial-attack
  frame; and the original's launcher
  (`remake/tools/hook-tracer/daybreak_launcher.c`) takes only exe/dll paths, with
  no script or screenshot facility, so the original cannot be driven to a chosen
  frame and captured from this environment. The lean sign is instead pinned
  analytically (donor tilt point map ≡ glm's Rx; the face direction's Y is
  `sin(pitch)`, zero under the old fold) and the port-side frames were inspected
  but are not parity evidence.

"Implemented" never silently means "verified"; "verified" never silently means
"live-equal". The boosted/special-gauge admission is implemented for weapons 0/1
(§1 conventions), with its two deltas recorded there — including that the port's
single melee press stands in for the original's two action-intent slots.

## 1. Melee admission (input → move), all three weapons

Recovered from `battle_rena_melee_admission.hpp` (= the 445ee0/44d850/43ded0 branches),
air branch first:

| Situation | w0 | w1 | w2 | Gate |
|---|---|---|---|---|
| air, in dash row 30, phase<2, normal | **332** | **332** | — (no 332 branch) | gate(332) |
| air, any other actionable air row | 320 | 320 | 320 | enabled && gate(320) |
| ground, dash row 20 + lateral input | 331 | 331 | 331 | normal && gate(331) |
| ground, dash row 20 | 330 | 330 | 330 | normal && gate(330) |
| ground, dash rows 23/24 + back (z<0) | 330 | 330 | 330 | normal && gate(330) |
| ground, dash rows 23/24 | 331 | 331 | 331 | normal && gate(331) |
| ground, back input (z<0) | 310 | 310 | 310 | enabled && gate(310) |
| ground, lateral input (x≠0) | 311 | 311 | 311 | enabled && gate(311) |
| ground, from 329/333/44 | 340 | 340 | — (weapon≠2 branch) | enabled && gate(340) |
| ground, in 340 | 341 | — (w0 only) | — | normal && gate(341) |
| ground, in 300 | 301 | 301 | — (weapon≠2 branch) | normal && gate(301) |
| ground, in 301 | 302 | — (w0 only!) | — | normal && gate(302) |
| ground, otherwise | 300 | 300 | 300 | enabled && gate(300) |

`enabled = normal || (boosted && contact)` — with boosted deferred, chains need the
0x100 record window. The `(weapon!=2 || state!=X)` guards stop weapon 2 from
re-entering 300/310/311 while already inside them.

**Port status: selection implemented + automated verification (2026-10-12).** `melee_admission.h` ports the
dispatcher for the whole group; the attack press AND chain presses during AttackA run
through it (`Fighter::admit_attack_move`). `melee_admission_test` pins it three ways:
42 independent table cases, synthetic-Fighter input edges, and install-backed real
sequences for all three weapons — idle→300, back→310, lateral→311, dash→330/331,
air→320 for every weapon; chains w0 300→301→302, w1 stops at 301 (restarts 300), w2
never leaves 300 (127 checks, 0 failures). The shipped priorities/thresholds were
probed: every gate from the locomotion rows passes, and the 0x100 windows open
mid-move. Non-Rena combos keep their previous bounded candidates; nothing here
generalizes Rena selectors to the roster. The `boosted` (special-gauge) admission is
implemented for weapons 0/1 and driven through the real input path (§1 conventions
list its two recorded deltas). The rejection side is pinned through the real
Fighter input path: a declined press (failed priority gate, missing destination
row, declined air press, declined chain) preserves the previous action, its
bound clip, its phase/tick timeline, the body yaw and the aerial metadata, and
falls through to the later input checks exactly as FUN_00445ee0's declined
branches do.

## 2. Melee execution contracts (per state, per weapon)

Strike windows and movement from the Ginkiha execution headers; NN.dat supplies the
phases/clips and the posed hit volumes (the port's `resolve_swing` already reads them).

| State | w0 | w1 | w2 | Key contracts (source) | Port status |
|---|---|---|---|---|---|
| *(movement mechanism)* | ✓ | ✓ | ✓ | Speed/Decelerate/Turn/Approach existed; **added** the vertical channel (Vertical/Gravity ops, u/tick units), LandExit/LandPhase landing transitions, ContactExit/JumpCancel body-driven exits, PhaseExit, ClockSkip (w2's double-speed frames), kGateNear/kGateFar distance latches, the 320 chase body (ChasePolicy per weapon) and the 332/334 dive body (DivePolicy) | **execution implemented + automated verification** (movement section, 40 checks: profiles, hop/leap vertical, chase arc and 329 landing, dive rebound to 334 and 333 landing, jump-cancel, double clock) |
| 300 ordinary | ✓ | ✓ | ✓ | w0/w1: speed 15/25 by distance (640000; w1 810000), approach 180→20/phase; phase-1 exit at dist<90000 or frame>10; strike = phase 2, frames 2–10; effect 60/64 @ph2 f0. w2: no movement, offset approach 3°, effect 67 @ph1 f18, motion-driven strike | clip/phases + posed volumes via NN.dat; **movement execution implemented + verified** (w0/w1 profiles, w2's spin incl. the 16..28 double clock); the row's voice and SE cues bound (this row makes no effect request) |
| 301 followup | ✓ | ✓ | ✓ | w0: speed 10@f1→0@f16; w1: 10@f0→0@f8; w2: 0→12 (10)→22 (0); strike f10–16; effect 61/67 | clip + volumes bound; **movement execution implemented + verified** (w0/w1 301 frame-8 stop, w2's motion-driven 301/302 shapes bound); the row's voice and SE cues bound (no effect request) |
| 302 ender | ✓ | **no branch** | ✓ | w0: 15@f0→0@f17; w2: 10@f12→0@f22; strike f12–17; effect 62/67 | clip + volumes bound (w1 N/A by source); **w0 movement bound** |
| 310 back kick | ✓ | ✓ | ✓ | w0/w1: phase model, approach 20/15, speed decel 1, strike ph2 f5–7, effect 62@f4; jump-cancel: ph2 f>12 && contact && jump → 40. w2: speed 30, decel 2 in f5–25, **−5 @f25** (backward slide), 0@f47, approach 10 until f30, strike f24–45, effect 68@f25 | clip + volumes bound; **movement + jump-cancel implemented + verified** (w0/w1 phase walk and contact cancel; w2's frame-driven kicks incl. the −5 backward slide) |
| 311 side kick | ✓ | ✓ | ✓ | w0: decel 0.2, approach 10 until f20, strike ph2 f5–7 (effect 62@f12). w1: speed 20@f0, approach 9 until f10, decel 2 after f17, strike f12–18, effect 67@f12. w2: guard test BEFORE frame-0 clear, speed 0→20@f27→0@f47, strike f32–49, effect 68@f35 | clip + volumes bound; **movement implemented + verified** (w0 .2 decay/stop-at-25, w1 approach-9/late bleed, w2's 27/47 speed steps) |
| 320 air chase | ✓ | ✓ | ✓ | policy(0,we): initial speed 12.5, strength 230→125 decay 4 (w2 140 fixed), attack distance 40000 (w2 490000), approach after 10; w2: gravity after 50, land after 55, voice f32, strike f32–39, frame skip 13→22 | clip + volumes bound; **chase body implemented + verified** (strength latch/decay, angle steering, hang→fall, 329 landing; w2's fixed strength and frame skip included); pitch/pivot render sign pending the live gate |
| 329 landing recovery | ✓ | ✓ | ✓ | after 320 landing; dash-recovery body | clip bound; **329/333 recovery bodies implemented + verified** (zeroed motion, gauge 40/1000 a tick) |
| 330 dash lunge | ✓ | ✓ | ✓ | w0: speed 30 @ph1, decel 2, strike ph2 f5–10, effect 62@f6. w1: **hop** (vertical 15, gravity .75), strike ph0 f>10 / ph1 f<20. w2: approach 3 until f28, decel 1.5/2, speed 40 @f28, strike f28–34 | clip + volumes bound; **hop implemented + verified** (vertical 15, gravity .75, landing ends phase 3); w0 lunge/w2 rush bound |
| 331 side dash attack | ✓ | ✓ | ✓ | w0/w1: approach 20 while strength (by dash distance), ph1 exit, strike per volume. w2: approach 10 preserving movement, strike f26–109, speed 10@f35 | clip + volumes bound; **movement implemented + verified** (331's strength latch via the counter, approach windows, phase-1 exit; 340's per-weapon approach/stop) |
| 332 air-dash dive | ✓ | ✓ | — | keiichi_dive family: dive angle clamp [−20,−5]°, speed 25, pitch/pivot, contact → 334 (clears contact, resets capacity), disable contact after f22, ph2 fall | clip + volumes bound (user-confirmed pose); **dive body implemented + verified** (clamped launch angle, contact rebound into 334 with the .35 gravity carry, 333 landing, contact cut past frame 22) |
| 333 dash recovery | ✓ | ✓ | ✓ | recovery body (gauge/turn restore) | clip bound; **329/333 recovery bodies implemented + verified** (zeroed motion, gauge 40/1000 a tick) |
| 334 dash followup | ✓ | ✓ | ✓ | after 332 contact | clip bound; **329/333 recovery bodies implemented + verified** (zeroed motion, gauge 40/1000 a tick) |
| 340 landing melee | ✓ | ✓ | ✓ | w0/w2: speed 15@f0→0@f15, approach 18 until f10, strike f16–24, effect 61@f15. w1: speed 10, approach 6 until f8, strike f10–16, effect 67@f12 | clip + volumes bound; **movement implemented + verified** (331's strength latch via the counter, approach windows, phase-1 exit; 340's per-weapon approach/stop) |
| 341 landing followup | ✓ | — | ✓ | w0: from 340, leap: ph1 vertical 18, gravity .75, strike ph1 f<20, landing → ph3. w2: same shape (speed 10) | **leap implemented + verified** (vertical 18, gravity .75, landing ends phase 3 zeroed) |
| 350 awakened melee | ✓ | ✓ | — | w1: **strike f21–64**, speed 8.5@f20→0@f73, sounds 68@25/45/65, contact window f21–64, no launch. w0: hidden props, 8 effect-61 beats, particle scatters 320/350/340, voices 32/33, **frames 1..9 replayed** by the clock rewind, gauge latch @f50. w2's 350 is the full-charge SHOT (clock jump 42→95, world row 8 @116) | **w0/w1 bodies execution implemented + automated verification** (incl. the stall window fix); admission still requires the boosted gate |
| 392 guard-hit exit / 43 air exit / 40 jump | — | — | — | the exit states themselves | 43 modeled as air-attack fallthrough; **392 implemented as the attacker-side exit with the corrected per-weapon row table (301/310/311/331/340 everywhere, 302/330 w0+w2 only; 300/320/332/341/350 have no branch) and its counter→phase-1 body**, driven through the real update (300 and 320 keep their row on a guarded connect, a chained 301 exits to 392); 40 via try_jump |

The shared movement slice has landed: attack-state movement (speed profiles,
approach/turn, the vertical channel with per-move gravity, landing transitions,
body-driven exits, the chase/dive feedback bodies) is implemented and
input-driven-verified per weapon above. The audio/visual layer landed with it. Two
distinct call paths were separated, and conflating them had been the earlier mistake:

* **melee voice** — FUN_004223d0/FUN_00422490; the ids ARE the voice vocabulary's
  indices (the original's 40-name table at 0x6b73b0), so FUN_004223d0(1,10,0) =
  attackA, (0xd,10,0) = guarded, FUN_00422490(0x20,...) = specialA. Dispatched as a
  `MeleeVoice` event, and a row whose cue policy is recovered stands the fallback
  swing voice down. The close-target cascade (0/15/5) still needs the pairing tracker.
* **SE** — FUN_0042c8b0 (positional) / FUN_0042c880: the argument is a
  `data/se/%03d.wav` id played at the actor's own position (FUN_0064b060 →
  FUN_0064ae70 → FUN_0065a260's 3D mixer). Dispatched on the SFX bus; the port's sink
  is not spatial, so the 3D placement is a recorded gap.
* **effect** — `(*actor+0xc)(id,x,y,z,heading,pitch)` is the actor-side effect request
  (FUN_00421aa0 → FUN_00435990 → the effect manager's create with that pose). The id
  indexes data/effect by `id / 10` (FUN_0042eba0's 100 slots), so the 350 beats'
  320/340/350 resolve to 032/034/035.dat. The effect spawns at the actor's position;
  the pose is carried on the frame but the port's card queue is position-only, so the
  orientation is not applied yet.

The guard-hit exit 392 is implemented, and the live pose gate remains.

## 3. Shooting admission and states (all three weapons)

Tap admission (short release, primary magazine charged), from the recovered routing:

| Situation | w0 | w1 | w2 | Source |
|---|---|---|---|---|
| idle (0) | 400 | 400 | 400 | ordinary tap |
| walking (10) | **401** | **401** | 400 | `roster_walk_shot_admission` (Rena branch, 401 gate) |
| dash 20 | **401** (gate 402) | 401 | 400 | `roster_ground_shot_admission` |
| dash 23 (left) | **405** | 401 | 400 | idem |
| dash 24 (right) | **406** | 401 | 400 | idem |
| dash 27 (back) | **407** | 401 | 400 | idem |
| air | 402 | 402 | 402 | air tap |
| air, in dash row 30 phase<2 + direction | **408** | 402 | 402 | `roster_air_dash_fast_shot(0,0,phase)` |
| charge release (grounded) | 450 | 450 | 450 | single charge state |
| charge release (air) | 460 | 460 | 460 | idem |
| red/full charge | 360/370 | 360/370 | 350/360 | full-charge family below |

Execution contracts (mobile/full-charge references, cross-checked with the handlers):

| State | w0 | w1 | w2 | Notes | Port status |
|---|---|---|---|---|---|
| 400 | row 0/6 @12, ±30 | rows 6 / 0+9 @18; **melee strike f8–18**; speed 45 @f7 | attachment @35 + 10-pellet ring (pitch rand%30+20, yaw 90−rand%180) | voices 27/30 (last round), 29 (w2) | bound (ledger §5) |
| 401 | like 400 @12 | row 6 / 0 @18 (powered = single 0), strike f8–18, turn 20→f15, speed 30@f7→0@f15 | → 400 | w1 powered differs from 400 (one request, not two) | **landed**: admission + program rules for w0/w1; w1's powered single request bound; w0 verified to fire exactly one request; the melee-strike window f8–18 (w1) remains pending |
| 402 | row 1/7 @13, ±30 | 3-phase dive ({12,1,35}, phase 1 HELD), phase2 f5 rows 6 / 0+9, dive arc (vertical −40, speed ≤10) | 2-phase, ph0 clock clamps at 17, landing <15 → 403 else ph1@25, f35 attachment + ring (pitch rand%50+30) | landing → 403/409 | **execution implemented + automated verification** for all three weapons (w0 grounded tick>0 → 403; w1 three-phase dive with the geometric closing speed; w2 early/late landing branch, clock clamp/seek and the ten-request ring) |
| 403/409/469 | recovery: recharge +40 (+5 when status<1), cap 1000 | idem | idem | air-shot landings | **execution implemented + automated verification**: motion zeroed every tick (no guard), charge gauge +40 capped 1000; the 402/460/408 landings now actually reach 403/409/469 through the shot-state landing branch |
| 405/406 | like 400 @12/13, movement −90/+90 | — | — | lateral dash shots | **landed**: admission + program rules mirroring 400; verified selecting 405/406 from the left/right dash states |
| 407 | @13: rows 4 (yaw+75,pitch30) + 9 (yaw−75) normal; + 13/14 (±85, pitch20) powered | — | — | back dash shot, movement 180 | **execution implemented + automated verification**: the back-dash situation is now driven end-to-end (row-27 dash → tap → 407 → the row-4/row-9 pair at tick 13) |
| 408 | @12 rows 0/6 (the ground rows, one tick early) | — | — | air-dash fast shot | **execution implemented + automated verification**: the air-dash→408 sequence is driven end-to-end (row-30 dash with a held direction → release → 408 → the single row-0 request at tick 12) |
| 450/460 | bound (ledger) | bound (model2 prop + 450/460 sweep) | bound | — | bound; the landings reach 469 through the shot-state landing branch |
| 469 | recovery (recharge) | idem | idem | after air charges | **execution implemented + automated verification**: motion zeroed every tick, charge gauge +40 capped 1000 |
| 350 | awakened MELEE (w0/w1) | — | full shot: clock jump 42→95, row 8 @116 (fwd 150, height 70, yaw+1, ±40) | w2 only as shot | **w0/w1 bodies execution implemented + automated verification** (incl. the frames-1..9 clock replay, the voices/SE/effect beats and the boosted admission); w2 bound (ledger) |
| 360 | red pair ph2@2 (rows 11/12, ±70/70/70, yaw ±1) + freeze @13 | row 8 @16, fixed 70° pitch | **air** second charge (same clock jump as 350) | w2's 360 is the AIR variant | w0/w1 bound; **w2's air 360 also bound** (speed/vertical ×0.1, gravity .05, the same jump/launch, landing → 469) |
| 370 | w0 backflip (speed −9.5, vertical 10) + pair; w1 air @16 | | — | w2 has NO 370 | w0/w1 bound (air) |

## 4. Animation service facts (scoped for this group)

* Two clocks exist, one per channel: `+0xae04` / `+0xae08` (`param_1[0x2b81]` /
  `[0x2b82]`). `FUN_00421100` (phase entry) zeroes BOTH; the handler epilogue increments
  BOTH; `FUN_0041f580:156` reads `+0xae04` for one channel and `+0xae08` for the other.
  **Verified: the two clocks never diverge on a recovered attack path.** Every confirmed
  seek writes both — weapon 2's 320 windup skip (`param_1[0x2b81] = 0x16; param_1[0x2b82]
  = 0x16`, FUN_00438310:952-954), weapon 0's 350 stall and rewind (FUN_0043ffc0:1458-59,
  1467-68), weapon 1's and 2's 350/360 seeks to 95, and Mion 0's 0xbc/0xbd and Mion 2's
  teleport all write the pair together. An earlier note here claimed the 320 skip wrote
  the secondary clock alone; a partial grep produced that, the full body contradicts it,
  and the note is retracted. The port's single `m_moveElapsedTicks` (which drives both the
  rule ticks and the animation playhead) is therefore exact for these paths.
  **The only lone-clock sites are outside them:** FUN_0046a190:2346 (Keiichi 0) resets
  `+0x2b82` on its own and immediately calls FUN_00421410(0,0), a channel-0 animation
  rebind rather than a phase seek. The residual dual-clock question is the animation
  SERVICE's per-channel time selection, not the attack bodies.
* Two channels exist (0/1); the port models one clock per move plus its recovered blend.
  For **Rena only weapon slot 2** has a recovered blend compatibility (`permits_blend`:
  clip 1 → 31/34/39) — the `+0x20` vtable profile. Weapons 0/1 bind instantly; no
  dual-channel behavior is claimed for them.
* Rena is NOT in `roster_walk_shot_recovered` (the layered lower-body walk-shot roster),
  so the walking shot 401 does not need an independent lower channel for this group.
* The chase/dive lean is FUN_00420b30's `T(0,-pivot,0) * Rx(pitch) * Ry(yaw) *
  T(position+pivot)`: `+0x2c` is a PITCH (RotationX) and `+0x2d8` a pivot HEIGHT, not two
  yaw terms. The port now builds exactly that (donor `actor_world_pose.hpp:14`), pinned
  by `melee_admission_test`'s matrix check.
* **Visible weapon:** FUN_00434a70(slot, model) re-points a prop slot at another of the
  item's attachment models and the original draws whichever model the slot names (Rena
  1's 450/460 bind slot 0 from model 0 = 11.x to model 2 = 12.x). `Fighter::draws_item_model`
  is the shared predicate the render gate and the tests read, so the visible weapon and
  the launch muzzle now come from the same binding.

## 5. Verification plan per acceptance rules

1. **Admission table test (data-free):** synthetic CharacterMoves with the Rena row
   inventory; drive every (weapon, source state, phase, grounded, x/z, flags) cell of
   the recovered table through the real `Fighter` attack press and assert the selected
   move id. Independent expected table, not read-back.
2. **Real-input integration:** real Rena tables via the install-backed fixtures —
   press sequences (idle tap, walk attack, dash attacks per direction, air attack,
   air-dash attack, chains) asserting `attack_move_id()`, phase entry and clip binding.
3. **Shot admission test:** walk/dash/idle/air-dash release situations assert the
   selected shot state id and its fire rules.
4. Full `ctest` (read its own summary), Windows/web cross-builds, silent captures of
   the changed attack routes.
5. Live visual parity stays a separate gate (D9): the matrix's status column never
   claims live parity from captures alone.

## 6. Remaining work (concrete, in order)

1. ~~Attack-state movement mechanism~~ — landed 2026-10-12 (vertical channel,
   landings, body-driven exits, chase/dive bodies; §2).
2. ~~320 chase arc, 332 dive + contact→334, 330/331 dash bodies~~ — landed
   2026-10-12; the pitch/pivot render SIGN and the live poses stay open (§ status
   vocabulary), as do melee voices/effects and the attacker-side 392 guard exit.
   **2026-10-12 review corrections:** the lean transform now applies FUN_00420b30's
   Rx(pitch) + pivot translation instead of folding both into the yaw (automated
   matrix witness); the guard-exit row table was corrected against the exhaustive
   `&2` scan; 320's contact window and weapon 0's 350 contact cut were added.
3. ~~402 weapon-specific phase models and the 403/409/469 recharge bodies~~ —
   landed 2026-10-12: weapon 1's three-phase dive (geometric closing speed) and
   weapon 2's clamp/seek landing branches plus its ten-request attachment ring are
   bound; the recoveries zero motion every tick and refill the charge gauge. The
   `+0x20d` field is resolved: it is `param_1[0x20d]` = byte **+0x834**, the
   fighter-level special/charge gauge — battle init 1000 (FUN_004219a0), +1/tick
   under an armed hyper flag (FUN_0041f580:96-99), +40/+5 in the recoveries,
   -500 on a special spend (FUN_00508a60:91); consumed by the melee/shot admission
   gates, the 390/393 guard exits and the awakened-melee `500 <` threshold. It is
   NOT the item-data magazine.
4. ~~Secondary-clock ownership~~ — **resolved 2026-10-12: no divergence exists on the
   recovered attack paths.** All seeks write both clocks together and the phase entry /
   epilogue move both, so the port's single clock is exact here (§4). The remaining
   dual-clock matter is the animation service's per-channel time selection, not the
   attack bodies.
5. **Visible weapon:** ~~Rena+1's model-2 prop~~ — landed 2026-10-12
   (`draws_item_model`, §4). Remaining: the actual model-2 mesh in a live frame is still
   a capture/live-parity question, and other combos' slot→model bindings are not audited.
6. **Voices, SEs and effects:** the melee voice cues, the FUN_0042c8b0/0042c880 SEs
   and the actor effect requests are produced and consumed (the last at the actor's
   position, ids resolving through data/effect's `id / 10`), pinned by
   `combat_audio_test` and `melee_admission_test`. Still open: the close-target voice
   cascade (0/15/5, needs the pairing tracker), the SE's 3D placement, and the effect
   card's orientation from the request's heading/pitch.
7. Then Mion+0/+1/+2 with the same matrix discipline.
