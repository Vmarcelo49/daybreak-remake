# Character iteration 1 — Rena+0 / Rena+1 / Rena+2

2026-10-11. Companion: [coverage ledger](ginkiha-shooting-coverage.md).

All three legal weapons were investigated together. This iteration corrects ground
request behavior and geometry; it does **not** declare any combo audited complete.
The supplied non-Rena body header omits these functions, but the original handlers
are available in `research/decompiled/`. Absence from the header is not an evidence gap.

## Original-handler contracts and changes

| Combo/path | Primary source | Request behavior now verified |
|---|---|---|
| Rena+0 ground tap | `FUN_0043ffc0.c:1866–1934` | Tick12: row0 normally / row6 powered. Integer elevation scratch clamped ±30; clearing the props selects the posed Prop1 zero-point fallback. A target at height60/distance500 verifies truncation to6°, rather than unquantized elevation. |
| Rena+0 first charge | `FUN_0043ffc0.c:2340–2377` | Tick13: row2 normally / row8 powered, fixed45°; actual slot0 DAT muzzle independently checked. |
| Rena+0 second charge | `FUN_0043ffc0.c:1472–1552` | Phase2/tick2: ordered world rows11/12 at right−70/+70, forward70, height70 in the remake's basis; legacy yaw offsets+1/−1 become remake offsets−1/+1. Phase2/tick13 holds ten updates, then advances and resets its scratch. |
| Rena+1 ground tap | `FUN_00448220.c:1666–1721` | Tick18: row6 normally, rows0 then9 powered. Horizontal rush45 begins at tick7 and ends at tick15. The old bridge-derived fan was the wrong attack. |
| Rena+1 first charge | `FUN_00448220.c:2148–2187` | Fifteen requests at ticks12–26: row1 normally / row3 powered. Counter increases by4 before each yaw-only draw: legacy yaw offset=counter−35+rand%10, pitch0. Attachment slot0 selects item model2's DAT muzzle. |
| Rena+2 ground tap | `FUN_00438310.c:1723–1802` | Phase1/tick35: one attachment row0/2, then ten world rows1/3 at forward200/height30. Each ring pellet draws pitch=rand%30+20, then legacy yaw offset=90−rand%180. The missing90° term is corrected; phase1 rush30 runs ticks25–34. |
| Rena+2 first charge | `FUN_00438310.c:2254–2308` | Tick40: right-hand row4 normally / row5 powered, integer elevation clamped ±40. Previously unbound. |

The attachment/model distinction is a shared launch capability: `FUN_00434a70`
selects a model for slot0/1, and `FUN_00435000` indexes that model's DAT muzzle.
`ShotOriginSpec::itemModel` now records the explicit model choice independently of
attachment slot; existing rules retain their slot default. Visual prop swapping is
not implemented by this descriptor and remains a separate integration task. Item3's
model0/model2 muzzle coordinates are equal; a separate in-memory fixture variant
gives them distinct coordinates and verifies that the resolver really selects model2.

The red freeze tests the counter **before** incrementing and returning in the source.
A port Hold reading the incremented counter must accept values1–10, then allow the
following visit to advance; using `<10` held only nine updates. The whole natural
move now checks eleven visits to phase2/tick13 and exactly one world pair.

## Verification boundary

`fighter_script_test` section46 runs all three ground taps and first charges in both
normal/powered contexts. It checks complete request sequences, rows, firing ticks,
per-shot RNG values using independent `std::mt19937`, next unused draws, and actual
origins from independently transformed posed bones / DAT muzzles / world offsets.
The Rena+0 second-charge witness traverses the real move phases rather than forcing
phase2. It checks row order, world geometry, angle signs and the complete freeze.

The branches are supplied through controlled shooting context. These witnesses do
not establish the original producer of every mode/aim predicate. They also do not
claim original global RNG stream alignment or 46/46 shooting completion.

Rebuilt fighter suite: **1761 checks, zero failures/skips**. Full rebuilt Linux CTest passed **67/67**, zero failures/skips (175.40s). Windows
and web cross-builds passed; neither cross target was executed.

Native captures loaded Rena+0/item001, Rena+1/item003 and Rena+2/item033, each paired
with a real Rena+0 opponent, with scripted taps over240 frames and `RESULT: ok`.
All ran with `--no-audio`. These were captures, not live interpolation or parity runs.
The explicit weapon selector is the supported relative `data/bullet/NNN` spec;
prefixing that selector with the install directory does not resolve a roster weapon.

## Concrete remaining work for this character group

- The current MovePrograms select real input/request paths for Rena+0/item001,
  Rena+1/item003, and Rena+2/item033, but the downstream per-item projectile lifecycle
  is not donor-equivalent yet. The flat `ProjectileBehavior` table covers only item001
  registrations 000/010/020/030/110/120/150/160/170 and lacks reachable item001
  registrations 040/060/070/080/090/130/140; there are no item003/item033 entries, and
  generic motion does not encode their age-specific direct-velocity transitions, RNG,
  contact/reflect logic, child shots, particles, sound, and fade behavior. Implement the
  finite item-specific switches and explicit event/child routing for all rows reachable
  from the three Rena MovePrograms.
- Rena dash source input history and dash state execution are not complete. `try_dash`
  currently uses the port stamina/double-tap policy; donor selection uses a 15-sample
  history, fighter gauge `+0x834`, the current row's 0x100 window and priority gate. It
  includes the contact-driven state28 branch for Rena+0/+1 and airborne row30 for all three
  weapons; current row30 admission is Rena+0 only. Port the source-backed selector and
  per-state ground/air drain/motion without borrowing the actor recovery slot6 status field.
- Existing 402/403/469 MoveProgram paths are implemented and tested. The recovery +5
  consumer is implemented/tested with a direct actor-status seam; `FUN_00637950` generic
  projectile status production is also represented. However, bounded scans of Rena's
  shipped actor and bullet DAT contact records found no `attackFlags & 0x1000`, so do not
  claim a natural Rena path reaches +5. Scene `+0x7f4` is a different object field.
- Keep visual live-parity gates open: no comparable original capture is available here for
  the 320/332 lean sign or Rena+1 model-2 frame. The SDL spatial audio law is likewise an
  approximation, not live DirectSound parity.

## Iteration order

Continue with this same Rena trio for its remaining reachable paths, then Mion+0/+1/+2,
Keiichi+0/+1/+2, and the remaining characters in authoritative roster order. Each
iteration updates the three combo records together; Hanyu/Natsumi have two weapons.

## Rena+0 playable follow-up (2026-10-11)

The owner's manual test narrowed this iteration to Rena+0. This follow-up covers
presentation and targeting as well as shooting requests:

- Full charge360/370 turns toward the opponent during phases0/1 at15 degrees per
  update (`FUN_0043ffc0:1493–1495`). A sideways-target witness reaches90 degrees
  before the ordered red pair launches; the earlier geometry-only fixture had no target.
- Ground side dashes now select NN moves23/24 rather than leaving the idle pose.
  Rena+0's real model/table witness pins the directional start sets22/19. This fixes
  shared animation selection; it does not claim recovered side-dash physics for every combo.
- Target-relative dash entry: `FUN_004202b0` combines the directional input with its yaw
  reference, and `FUN_0042dd90` refreshes that reference from the selected target while
  compensating the body's relative yaw. The port now samples the current target bearing before
  input dispatch, commits ground back/side movement from that bearing, and presents rows27/23/24
  facing it. Forward move20 retains its phase-0 snap and phase-1 steer. Asset-backed
  Rena+0 cases cover back/left/right and a changed direction while already dashing; a Mion+0
  back-dash case checks the shared path at another bearing. The cases assert displacement and
  pose yaw. The requested backward air-dash attack
  exception is kept as a port rule: movement uses the target-relative vector while the visible
  actor yaw stays available to attack dispatch. The original source read here establishes the
  separate movement/body basis, not that specific air-attack selector; no live original dash
  comparison is claimed.
- Rena+0 emits ShotA27 for tap400/402, ShotB28 for charge450/460, and ShotFinal30
  when the appropriate magazine has one round before admission. The original's
  `+0x6dc` / `+0x720` are primary/secondary remaining-round fields here. The red
  pair360/370 emits one SpecialA32 with alternative2 for `rand%100<51`, otherwise1.
  Cues pass through Match even if the projectile pool rejects the request; unrelated
  combos retain their existing generic voice policy. Voice selection is checked silently.
- Projectile textures with nonblack content and at least75% exact-black border
  key exact black to alpha0 at GPU upload. This is a scoped port rendering policy,
  not a recovered original color-key flag. Actual Rena item1 nata rotation and Zippo
  flame textures satisfy it; solid nata/Zippo surfaces do not. Cached source pixels
  remain unchanged. The native tap capture shows the surrounding stage through the
  glow's former black padding; near-black painted outlines remain part of the texture.

VS/countdown changes are recorded separately in the audio-backend documentation.
Tests and manual verification runs remain silent. No combo-completeness promotion.

Follow-up validation: rebuilt fighter suite1783 checks, zero failures/skips. Native
CTest ran67 tests:66 passed initially; the sole failure was the old side-dash test
asserting idle fallback. After replacing that stale expectation with the directional
NN clips, its rebuilt rerun passed. Windows/web cross-builds passed. Muted native
Rena+0 tap capture and750-frame shooting run returned `RESULT: ok`; the standalone
capture path does not instantiate the frontend combat-audio dispatcher, so voice
claims rest on the source/mocked-dispatch and asset-backed Match tests, not that capture.
The intro slice passed three focused tests and silent capture/live/no-device checks.
No cross-target execution or audible voice comparison is claimed.
