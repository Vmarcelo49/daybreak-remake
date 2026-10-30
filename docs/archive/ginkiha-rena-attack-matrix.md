# Rena attack matrix — evidence-based status for the full attack port

2026-10-13 · branch `main` · companion to [the attack-animation plan](ginkiha-attack-animation-plan.md),
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

**Recovery gauge field (corrected evidence, 2026-10-13).** `+0x20d` is actor
`+0x834`; recoveries 403/409/469 add +40 if actor status slot 6 (`actor[0x1fd]`,
byte `+0x7f4`) is clear, otherwise +5, capped at 1000. `FUN_00637950:383-421`
can write the paired status duration/power on a successful projectile hit whose
`attackFlags` contains `0x1000` (duration `combat[2]`, power `combat[1]`); the actor
reset clears the nine-word status array (`FUN_004219a0:12-22`). In `FUN_00634f60`
the body executor reads the timer before the later status decrement, and projectile
collision follows both, so a hit can affect the next recovery tick. A bounded scan of
shipped Rena actor DATs 00/01/02 (276/254/243 contact records) and bullet folders 001/003/033
(20/20/16 records) found no `0x1000` status-6 records. This establishes the generic
producer and the recovery consumer, not a natural Rena hit route; scene-object
`scene+0x7f4` remains a separate field.

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
(§1 conventions) and its chord is the source's own two-latch one, not a single press
(§1). The positional-SE request, listener pose and SDL playback path are now implemented
and covered by automated tests; the remaining source-parity gap is DirectSound's exact
spatial DSP versus the port's documented approximation. The two visual gates remain
unavailable in this environment.

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
  swing voice down. **The close-target cascade (0/15/5) is bound.** The selection is
  `battle_melee_voice`'s — inside `dist^2 < 90000` (40000 in the 320 body, 160000 in
  weapon 2's 330) and `|+0x19| < 30`, the FIRST set flag of `[+0xaec3, +0xaebe,
  +0xaeb9]` wins, giving voice 0 / 15 / 5 at priority 12, otherwise the ordinary voice
  at priority 10 (`FUN_0043ffc0:601-627` and its twins; the Ginkiha donor takes the
  three flags as INPUTS). The producer turned out to be decidable from state the port
  already owns, so the earlier "needs a pairing tracker / cleaner dump" note was
  withdrawn:
    - attention actor = a valid combat lock (`+0x304`) else the aim selection
      (`+0x300`, init 0 for everybody) — the two writers of `+0x308`;
    - the target counts as engaged when it attends back or I hold a lock;
    - the yaw test is its effort heading (`+0x5c` + `+0x64`) against mine, wrapped to
      +-180 and compared at 90;
    - `+0xaec3` needs a REACTION state (100..299, FUN_004236c0), and `can_act` refuses
      attacks out of one — ADDATTACK is unreachable through an attack row;
    - `+0xaeb9`/`+0xaebe` need the same test, the second adding an attack-or-shot
      state (FUN_0042e950).
  One consequence worth recording: the cascade always runs inside the attack row, so by
  then the previous tick's state IS that row — BACKATTACK never outranks intercept at
  any row this port binds, which makes intercept-vs-ordinary the reachable pair. The
  dump's contradictory inner nesting is genuinely dead in both branches, so it is
  reproduced as dead (the arms stay in the source's order for a row bound at its entry
  tick).
  Two terms stay unmodelled and are recorded at the producer: the per-slot device code
  `+0x7d8` only ever disjuncts the unreachable arm, and the battle-offset yaw `+0x19`
  the cascade's gate also reads is not carried by this port, so the gate is distance
  alone. `melee_admission_test` drives a real 1v1 Match for both directions.
* **SE** — positional `FUN_0042c8b0(id, actor)` carries actor `+0x14` through
  `FUN_0064b060` → `FUN_0064ae70` → `FUN_0065a260`; the raw caller makes the source-position
  `SetPosition` call on `IDirectSound3DBuffer` (+0x4c), deferred. The listener path is now
  source-backed too: per-frame `FUN_006358c0` / `FUN_0063dad0` set `IDirectSound3DListener`
  position to the selected actor's XYZ with **+150 Y**, set orientation from the yaw sine
  table, then commit deferred settings; the raw call is at `DaybreakDX.exe` VA 0x635c20–0x635c6d.
  `FUN_00633ca0` initializes distance factor .01 / rolloff .0002, and battle-stage setup
  (`FUN_00648ad0` / `FUN_006492f0`) sets distance factor .01 / rolloff .0005. New 3D SE
  buffers set min distance 3.0 (`FUN_006676d0`); no call to the exposed min/max setter
  `FUN_00667820` was found, so max distance remains the DirectSound default. The C++ event
  captures positional/non-positional body form, source coordinates, the primary-view listener
  pose and yaw-derived orientation; the SDL path applies per-event stereo panning and
  attenuation. **Port rule:** one listener in split screen uses the primary view; the original's alternate special-control actor branch is not modeled. **Audio
  parity remains open:** DirectSound owns the exact spatial-mix law; SDL uses an explicitly
  approximate equal-power pan/rolloff implementation, so source placement is executed and
  tested but not live-equal.
* **effect** — `(*actor+0xc)(id,x,y,z,heading,pitch)` is the actor-side effect request
  (FUN_00421aa0 → FUN_00435990 → the effect manager's create with that pose). The id
  indexes data/effect by `id / 10` (FUN_0042eba0's 100 slots), so the 350 beats'
  320/340/350 resolve to 032/034/035.dat. **The pose is now carried and composed:**
  FUN_00436150 rotates each instance by its request direction (RotationZ then
  RotationY then translation), the queue carries that direction, and placement builds
  the matrix with the same `game::shotModelMatrix` helper the shots use — one
  convention, not two. The unposed callers are untouched because a zero direction
  composes to the old translation-only matrix.
  Two limits stay recorded: whether a card SHOWS its yaw is the renderer's per-draw
  billboard gate (the 350's ring is a billboarded card, so the observation is "correctly
  undamaged", not a new orientation on it), and the direction is built from the cue's
  angles — the request's own pair, not a re-derived one.

The guard-hit exit 392 is implemented, and the live pose gate remains.

## 3. Shooting admission and states (all three weapons)

Tap admission (short release, primary magazine charged), from the recovered routing:

| Situation | w0 | w1 | w2 | Source |
|---|---|---|---|---|
| idle (0) | 400 | 400 | 400 | ordinary tap |
| walking (10) | **401** | **401** | 400 | `roster_walk_shot_admission` (Rena branch, 401 gate) |
| dash 20 | **401** (gate 402) | 401 | 400 | `roster_ground_shot_admission` |
| dash 23 (right) | **405** | 401 | 400 | idem |
| dash 24 (left) | **406** | 401 | 400 | idem |
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
| 401 | like 400 @12 | row 6 / 0 @18 (powered = single 0), mobile turn 20→f15, speed 30@f7→0@f15 | → 400 | w1 powered differs from 400 (one request, not two) | **landed**: admission + program rules for w0/w1; w1's powered single request bound; w0 verified to fire exactly one request; 401 is a mobile-shot row, with no melee-contact volume in `FUN_00448220:1722-1776` |
| 402 | row 1/7 @13, ±30 | 3-phase dive ({12,1,35}, phase 1 HELD), phase2 f5 rows 6 / 0+9, dive arc (vertical −40, speed ≤10) | 2-phase, ph0 clock clamps at 17, landing <15 → 403 else ph1@25, f35 attachment + ring (pitch rand%50+30) | landing → 403/409 | **execution implemented + automated verification** for all three weapons, driven by REAL input (jump → airborne Shoot tap): w0 fires its one row-1 request at frame 13 with the ±30-clamped pitch; w1's phase 1 keeps the closing speed in [0,10] and fires row 6 at phase-2 frame 5; w2 fires one attachment row-0 at phase-1 frame 35 plus the ten-request ring on rows 1/3, each pitch in [30,80) and each draw its own. The landing exits to 403/409 are covered separately |
| 403/409/469 | recovery: +40 if actor `+0x1fd < 1`, else +5; cap 1000 | idem | idem | air-shot landings | **execution implemented + automated verification** for motion reset and both refill values using a direct slot-6 test seam; natural Rena reachability remains unresolved. Generic projectile-hit writer `FUN_00637950` is implemented for `attackFlags & 0x1000`; scanned shipped Rena DAT contacts lack that bit (bounded negative). Scene-relative `scene+0x7f4` is separate. |
| 405/406 | like 400 @12/13, movement rides the committed dash direction | — | — | lateral dash shots (405 from row 23, 406 from row 24) | **landed**: admission + program rules mirroring 400; verified selecting 405/406 from the row-23/row-24 dash states |
| 407 | @13: rows 4 (yaw+75,pitch30) + 9 (yaw−75) normal; + 13/14 (±85, pitch20) powered | — | — | back dash shot, movement 180 | **execution implemented + automated verification**: the back-dash situation is now driven end-to-end (row-27 dash → tap → 407 → the row-4/row-9 pair at tick 13) |
| 408 | @12 rows 0/6 (the ground rows, one tick early) | — | — | air-dash fast shot | **execution implemented + automated verification**: the air-dash→408 sequence is driven end-to-end (row-30 dash with a held direction → release → 408 → the single row-0 request at tick 12) |
| 450/460 | bound (ledger) | bound (model2 prop + 450/460 sweep) | bound | — | bound; the landings reach 469 through the shot-state landing branch |
| 469 | recovery (recharge) | idem | idem | after air charges | **execution implemented + automated verification**: motion zeroed every tick; +40/+5 slot-6 refill logic and cap are tested, but natural Rena +5 reachability is unproven (see recovery note above) |
| 350 | awakened MELEE (w0/w1) | — | full shot: clock jump 42→95, row 8 @116 (fwd 150, height 70, yaw+1, ±40) | w2 only as shot | **w0/w1 bodies execution implemented + automated verification** (incl. the frames-1..9 clock replay, the voices/SE/effect beats and the boosted admission); w2 bound (ledger) |
| 360 | red pair ph2@2 (rows 11/12, ±70/70/70, yaw ±1) + freeze @13 | row 8 @16, fixed 70° pitch | **air** second charge (same clock jump as 350) | w2's 360 is the AIR variant | w0/w1 bound; **w2's air 360 also bound** (speed/vertical ×0.1, gravity .05, the same jump/launch, landing → 469) |
| 370 | w0 backflip (speed −9.5, vertical 10) + pair; w1 air @16 | | — | w2 has NO 370 | w0/w1 bound (air) |

### 3.1 Correction: the mobile/dash shot windows (2026-10-12)

Re-reading FUN_0043ffc0's own case bodies showed that several of the mobile/dash shot
windows had been bound from the wrong reading of the same lines — the prop unbind is
`threshold < tick`, i.e. it starts the tick AFTER the recorded number, and each row's
approach rate and bleed window are the handler's own:

| State | Before | Corrected | Corpus |
|---|---|---|---|
| 401 | bleed .5 from tick 0; unbind from 12 | bleed **.25** from tick 0; unbind from **14** | 1938-1941 / 1934 |
| 405, 406 | turn 20 for ticks 0..11; bleed .5 from tick 0; unbind from 12 | turn **15** for ticks **0..9**; bleed **.5 only after tick 10**; unbind from **14** | 2111/2166, 2118/2173, 2114/2169 |
| 407 | turn 15 for ticks 0..9; unbind from 13 | turn **9** for ticks 0..9 **plus 15 on every phase-0 tick** (two original `FUN_0042db10` calls, so early ticks rotate 9 then 15); unbind from **14** | 2221-2222, 2232-2233, 2224 |
| 408 | unbind from 13 | unbind from **14** | 2282 |

400 and 402 were already correct (`0xb < tick` → 12, `0xc < tick` → 13), which is the
check that fixes the convention: the port's `Hide` rule window is inclusive, so a
`threshold < tick` condition becomes `first = threshold + 1`. The corrected values are
pinned by `melee_admission_test`'s window section, so a future edit cannot silently
revert them.

The same pass over the MELEE rows found three more gaps, all in weapon 0's table:

| State | Missing | Corpus |
|---|---|---|
| 310 | phase-0 entry snap 180° before the 20° approach; the phase-2 contact/ribbon span | 756-765 + 772-774; 791 (`tick < 5 \|\| 7 < tick` clears, so 5..7 arms) |
| 311 | the ungated tick-0 180° snap | 824-829 (weapon 2's table already had it) |
| 341 | the phase-1 contact/ribbon span, 0..19 | 1365 (`phase == 1 && tick < 0x14`) |

They are pinned in the same section. Note for 311: its body calls neither
`FUN_00434b30` nor `FUN_00434bd0`, so the port correctly carries no `Active` span for
it — its volume comes from the NN record's own combat flag, and §2's "strike ph2
f5–7" line for 311 describes that record data, not a body span.

### 3.2 Correction: side-dash input rows were mirrored (2026-10-13)

Gameplay prints showed double-tap Left entering row 23 (set 22, `Anim-102`)
and Right entering row 24 (set 19, `Anim-105`). The direction history yields
command 3 for x=-1 (Left) and 4 for x=+1 (Right), and every admission switch
routes command 3 -> row 24 and command 4 -> row 23 (`FUN_00445ee0:86-95`
branches `+0x830==3 -> 0x18` / `==4 -> 0x17`, REA function identity
`ev_bf410cc0` on the SHA-verified executable; donor `rena_dash.hpp:11`,
`battle_roster_air_dash_admission.hpp:8`, `dash_melee_native_control.hpp:82`).
So Left must play row 24 (sets 19/20/21) and Right row 23 (sets 22/23/24) —
the port had them backwards. `Fighter::dash_move_for` now maps Left -> 24 /
Right -> 23; movement vectors are unchanged (they already followed the
lock-relative input). Pinned by the directional-dash animation-set checks in
`melee_rules_test` and the Rena+0 double-tap cases in `fighter_script_test`,
plus the row-23/405 and row-24/406 tap-shot routing in `melee_admission_test`.

The same audit then covered the other two handlers, and **neither weapon 1 nor weapon 2
had a single `Active` rule**, so their props never armed at all:

| Combo | Spans now bound (tick-only, so phase `-1`) |
|---|---|
| Rena+1 (`FUN_00448220`) | 301 → 10..16, 310 → 5..7, 311 → 12..18 |
| Rena+2 (`FUN_00438310`) | 310 → 24..45, 311 → 32..49, 330 → 28..34, 331 → 26..109, 340 → 16..24 |

Two were deliberately left unbound and are recorded, not guessed: weapon 2's 301/302
windows exist in its handler but `rena_melee_admission` gives weapon 2 no such branch,
so the rows are unreachable; and both weapons' 320/350 families already model their
contact span through `ContactOff` (weapon 1's 350 is exactly the corpus's 21..64), so
reconciling their `Active` half needs the phase structure read first.

**That sweep under-reported, and a brace-aware re-pass fixed it.** The first extraction
looked only a few lines back for the enclosing condition, so every `FUN_00434b30` site
whose `if` wraps across lines was misread as "the else of a window" and skipped. Re-running
over all three handlers with six lines of context found four more armed spans:

| Combo | Spans added |
|---|---|
| Rena+1 | 300 → phase-2 frames 3..10 (`FUN_00448220:670-673`); 330 → phase 0 from frame 11 **plus all of phase 1** (1077-1080, a two-part condition the old pass flattened) |
| Rena+2 | 300 → phase-1 frames 25..34 (`FUN_00438310:633-636`); 341 → all of phase 1 (1371-1374) |

The same pass confirmed every span the port already carried (weapon 0's six, weapon 1's
301/310/311, weapon 2's 310/311/330/331/340), so the melee prop-latch class is now
closed for the group. Unreachable rows stay unbound on purpose: weapon 2's 301/302 (its
admission has no such branch) and weapon 1's 341 (weapon 0 only, per §1).

**Weapon 2's chase was not a copy of weapons 0/1, and reading it in full corrected
three things** (`FUN_00438310:952-992`): its phase-2 clock **jumps 13 → 22** on both
counters, which the port did not model at all (so gravity .5 from 51 and the 329 landing
from 56 — both already correct — arrived about nine ticks late); its approach turns
**2°/tick while the clock is under 32**, a rule the table did not carry; and its
contact/ribbon window is **frames 32..39**, not the 0..7 copied from w0/w1's `tick < 8` —
that copy would have kept the chase's hit volume live through its windup instead of its
strike. The strike cue (SE 62 + voice 1 at clock 32) was already right.

The chase was the last armed span: `FUN_00434b30` arms `+0xfc` **and** the prop's ribbon
latch together, and 320's contact half was already modeled through `ContactOff`
(phases 0/1 all, phase 2 from frame 8), so its ribbon half was missing. The body's window
is `tick < 8` inside phase 2 (`FUN_0043ffc0:985-990` and its `FUN_00448220` twin), now
bound for weapons 0 and 1. Weapon 2's chase has the SAME gap in its own numbers: its
window is `tick < 32 || 39 < tick` inside phase 2 (`FUN_00438310:988-992`), and once that
phase placement was read its 32..39 span was bound too — so the class is closed for all
three weapons.

**Reading note that retracts an earlier "remaining" item:** the decompiler renders a call
made inside a condition as a comma expression — `if (PH == 0 && (FUN_0042db10(0,3),
tick == 0))` means the 3° turn runs on **every** phase-0 tick (it is evaluated before the
`tick == 0` test) and only the *body* is tick-0-gated. So weapon 2's phase-0 `Turn 3` is
correct as bound, and the same form explains weapon 1's phase-1 `Turn 15` (every phase-1
tick, which lasts one tick because the exit follows it). The earlier note listing weapon
2's `300` phase-0 width as a delta was wrong and is withdrawn.

The turn pass then covered weapon 1's entry steps, which had the same shape as weapon
0's before its own correction: 310 was missing its phase-0 180° snap (`FUN_00448220`
736-742), 311 its tick-0 180° (795-802), and 400/401 their second tick-0 step (15° and
5°) on top of the shared 20° for ticks 0..14 (1681-1690, 1738-1746).

**Correction to that note (same day):** reading `advance_rena_dive` before acting on it
showed the claim above was wrong. Weapon 0's and weapon 1's 332 were *not* missing a
body: the C++ dive policy (`advance_rena_dive`, `kRenaDive`) is bound and dispatched for
both (`moveId == 332 || moveId == 334`), it carries the corpus's own values (launch 25
u/tick, elevation clamped [-20,-5], contact rebound to 334 at 10 / −7 / gravity .35, the
volume cut past frame 22, the phase-2 hand-off at frame 40), and both tables already
queue the phase-1 tick-0 voice (`FUN_00422490(3,0,10,0)`). What the tables genuinely
lacked was 332's **landing branch**: grounded with `0 < phase` hands to 333
(`FUN_0043ffc0:1161-1165`), so without it a plain dive stayed in 332 on the ground
instead of entering the 333 recovery. That rule is now bound for both weapons, and the
witness is falsifiable — removing it makes the new assertion fail.

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
   selected shot state id and its fire rules. The AIR TAPS are additionally driven
   through real input for all three weapons (fighter_script_test §47): the expected
   item rows, firing frames and phases are asserted per weapon, including the w1
   dive's closing-speed clamp and the w2 ring's pitch range and fan-out. The weapon
   RIBBON is verified against its Active windows (§48): it grows only inside 300's
   phase-2 frames 3..10 and decays to empty afterwards.
4. Full `ctest` (read its own summary), Windows/web cross-builds, silent captures of
   the changed attack routes.
5. Live visual parity stays a separate gate (D9): the matrix's status column never
   claims live parity from captures alone.

## 6. Remaining work (concrete, in order)

1. ~~Attack-state movement mechanism~~ — landed 2026-10-12 (vertical channel,
   landings, body-driven exits, chase/dive bodies; §2).
2. ~~320 chase arc, 332 dive + contact→334, 330/331 dash bodies~~ — landed
   2026-10-12; the pitch/pivot render sign and live poses stay open (§ status vocabulary).
   The melee voice/effect paths and attacker-side 392 guard exit were subsequently bound
   and tested (§2 / §7), so they are not remaining implementation gaps.
   **2026-10-12 review corrections:** the lean transform now applies FUN_00420b30's
   Rx(pitch) + pivot translation instead of folding both into the yaw (automated
   matrix witness); the guard-exit row table was corrected against the exhaustive
   `&2` scan; 320's contact window and weapon 0's 350 contact cut were added.
3. **402 / 403/409/469:** weapon-specific air-tap bodies, landing branches, and recovery
   motion resets are implemented and tested; `+0x20d` is `param_1[0x20d]` = byte **+0x834**,
   the fighter's special/charge gauge (battle init 1000, +1/tick under armed hyper, -500 on
   a special spend). Recovery refill is +40 when actor `+0x1fd < 1`, else +5; the port covers
   +40. `+0x1fd` is actor-relative byte `+0x7f4`; its producer and reachability during Rena
   recovery are unresolved. Scene-relative `scene+0x7f4` is distinct, so do not conflate it
   with the actor field or claim the +5 path as implemented. The `+0x834` field is not the
   item-data magazine.
4. ~~Secondary-clock ownership~~ — **resolved 2026-10-12: no divergence exists on the
   recovered attack paths.** All seeks write both clocks together and the phase entry /
   epilogue move both, so the port's single clock is exact here (§4). The remaining
   dual-clock matter is the animation service's per-channel time selection, not the
   attack bodies.
5. **Visible weapon:** ~~Rena+1's model-2 prop~~ — landed 2026-10-12
   (`draws_item_model`, §4). Remaining: the actual model-2 mesh in a live frame is still
   a capture/live-parity question, and other combos' slot→model bindings are not audited.
6. ~~**Voices, SEs and effects**~~ — the melee voice cues, FUN_0042c8b0/0042c880 SEs
   and actor effect requests are produced and consumed (the latter at actor position and
   pose), pinned by `combat_audio_test`, `melee_admission_test`, `ginkiha_tables_test` and
   `fx_cards_test`. `fighter_script_test` now drives each Rena ground tap/charge and pins
   its SE id, source form, tick and call-time actor position. Positional SEs also carry
   listener state through the event queue; `combat_audio_test` pins source/listener
   propagation, pan/attenuation math and queued SDL playback. The close-target voice cascade
   is BOUND (§2: its unreachable arms and unmodelled producer terms remain recorded there).
   Exact DirectSound live audio parity is not claimed.
7. Then Mion+0/+1/+2 with the same matrix discipline.

## 7. Group acceptance decision

The boosted 350 admission's two-latch chord (`FUN_00445ee0:117-118`) and the close-target
voice cascade's producer (§2) are bound, with input- or Match-driven witnesses. The effect
request's pose flows through the queue and composes with the recovered `FUN_00436150`
convention (`fx_cards_test` plus a scripted 350 capture). The cascade's arms were also
reduced by reading: addattack needs a reaction state that `can_act` refuses and backattack
is outranked by intercept inside every bound row, so intercept-vs-ordinary is the reachable
pair.

**Current acceptance state: Rena remains in progress; do not advance to Mion.** The
source-positioned SE path now carries source coordinates, the recovered single-listener
pose, and source-form metadata through the event queue. The SDL backend implements an
explicitly approximate pan/attenuation path; focused tests cover metadata, pan direction,
attenuation endpoints, dispatch routing, and queued playback. This is **execution
implemented + automated verification**, not **live parity**: the original delegates 3D
mixing to DirectSound, while SDL uses a documented port approximation.

Two runtime implementation areas remain open beyond the matrix's covered melee/shot
bodies: item-specific projectile lifecycles for the reachable item001/item003/item033
registrations, and Rena dash runtime integration. A source-backed 15-sample history and
pure admission helper now have 46 checks over Rena+0/+1/+2, including +0x834, flags28,
priority, air row30 and grounded row28 branches. This is **selection logic**, not an
input-connected dash implementation: dash history is not yet fed by Fighter input, the
handler's ground/air phase motion and gauge drain are not executed, and row28 is not wired
as a reachable transition. These remain implementation gaps, not parity-only gaps.
Recovery +5's generic producer and consumer are source-backed and the consumer is tested;
a bounded scan found no status-slot-6 (`attackFlags & 0x1000`) contacts in shipped Rena actor
or bullet DATs, so natural Rena reachability remains unresolved. Scene-object `+0x7f4` is
separate. The two visual gates remain unresolved: (1) 320/332 lean sign and (2) Rena+1
model-2 frame lack comparable original captures. No path in this matrix has **live parity**;
Mion remains deferred.
The Rena+2 320 seek was already implemented in `Fighter::advance_rena_chase` through
`ChasePolicy::skipAttackFrames` before the later duplicate `ClockSeek` rule was added.
The claim that the seek had been absent (and gravity nine ticks late) is withdrawn.
The redundant rule has been removed. A real-input behavioral regression now observes
13 → 22 → 23 (including the common clock increment), contact only at executed ticks
32..39, and landing recovery 329 without forcing phases. This verifies execution,
not merely the presence of a rule. The contact-window and ribbon fixes remain valid.

### Historical acceptance statements (superseded)

**The 2026-10-12 "reopened" statement (historical; superseded by the current decision above).**

The three required categories the review named are resolved for Rena+0/+1/+2: **clocks**
(the two actor clocks never diverge on a recovered path, §4), **props** (the slot→item-model
binding drives both the muzzle and the drawn mesh, §4) and **required effects** (the
FUN_0042c8b0/0042c880 SEs and the `(*actor+0xc)` effect requests keep their own id spaces,
are produced on the body's frames and consumed; the ids resolve through data/effect's
`id / 10`). Every reachable exit (403/409/469 recoveries, 392 guard knockback, 329/333/334,
the landing branches) is implemented and exercised. Selection, execution and automated
verification therefore hold for the paths this matrix lists, with real-input witnesses for
the admission, the air taps, the dive/ring, the ribbon windows, the boosted 350 and the
guard exit.

**Live parity is still held by no path.** The two visual gates (lean sign render, model-2
frame) lack comparable original reference frames in this environment (§ status vocabulary's
exact limitation). The spatial-SE implementation has automated evidence, but the SDL mix is
an approximation to DirectSound's platform-owned 3D DSP; no live original audio comparison
is claimed (§2). Thus spatial SEs can carry **execution implemented + automated
verification**, while **live parity** remains open. The cascade, chord and effect pose that
older statements listed as caveats are bound now; the current decision above governs.
