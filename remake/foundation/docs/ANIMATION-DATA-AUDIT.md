# Animation data audit — 2026-10-07

> **Status.** This is the **pre-implementation** audit for issues #52, #53, #54, #31
> and #26, kept as the before picture. "Before fix" columns describe the tree at
> `db6a083`, not the current one. Post-implementation corrections and coverage live in
> §10; the authoritative inventory of what is still substitute behaviour is §11.
> Nothing here establishes that all 46 combos' attacks or shots now work.

This is the **pre-implementation** audit for issues #52, #53, #54, #31 and #26.
The checkout was clean when the audit started. The hypothesis is partly confirmed:
the remake drops and misinterprets data, but the original also has executable
character/weapon behavior. NN.dat alone cannot specify the entire game.

## Issue observations and overlaps

| Issue | Concrete observation / reproduction | Combo and overlap |
|---|---|---|
| [52](https://github.com/Vmarcelo49/daybreak-decomp/issues/52) | Hold up toward the locked opponent; hold back to turn away through a short arc; try all eight directions. Both human and COM should turn by the shortest route. Camera should follow facing. | All combos; locomotion and attack facing. The original body incorrectly said facing has no tick writer. Its correction identifies `update_facing`, which continuously pulls toward the opponent. |
| [53](https://github.com/Vmarcelo49/daybreak-decomp/issues/53) | Press melee: slice is too fast, no forward travel, no weapon slice effect. Press again for second and third attacks. The second hit or block should invoke the sideways action camera. | Rena 0; phase timing, timed hitboxes, weapon trails, chain selection, camera. |
| [54](https://github.com/Vmarcelo49/daybreak-decomp/issues/54) | Tap shoot, release first charge, release second charge: expected one nata, one grenade, two natas, with corresponding throw animations. | Rena 0. The correction cites Rika's syringe (`bullet/007/50.X`) and the +X-authored darts/beams as model-axis evidence. The old claim that projectile models are absent is withdrawn. |
| [31](https://github.com/Vmarcelo49/daybreak-decomp/issues/31) | Attack airborne: resolved move 340/set 88 becomes set 0 in presentation; a grounded dummy 40 units away is legitimately outside a recovered 3D sphere. | Rena 0 anchors; selector, combo binding and fallback diagnostics. Current source carries 340 through `state_move_id`, so the issue's older lost-selector mechanism is already fixed. A missing row still falls back. |
| [26](https://github.com/Vmarcelo49/daybreak-decomp/issues/26) | Older Walk→13, Run→54, Attack→2 mappings were wrong; every attack has a weapon. Validate weapon-specific rows with the animation player. Current scope claims vtable+0x20 generates missing 40/41/42 and 400-family hits. | Rena 0 clip map; Rena 2 blend callback; all 46 legal combos. The raw-set table and missing weapon dimension are already fixed. The current vtable claim is disproved below. |

The shared failure is that a simplified port state and a single flattened combat
window replace the original move/section/record execution. Animation, collision,
movement, trails and projectiles consequently use different clocks and selectors.

## Evidence and source identity

* Read all five issue bodies **and comments** before code inspection.
* Read the current parsers, fighter, projectile, scene and effect consumers.
* Used the open **original** `DaybreakDX.exe` through the Ghidra bridge at port
  8089. The offline `research/decompiled` corpus is from a patched executable;
  apparent absences there are not evidence of absence in the original.
* Read all 46 shipped NN.dat files through bundle priority
  `07/04/00/05/02/06`, matching `AssetSource`, rather than relying on the
  extraction tree's last-writer copies. Every file ended at its exact declared
  trailer boundary: 5,847 distinct moves, 9,931 phases, 12,214 timed records,
  5,879 animation-set rows and 7,921 texture events.
* All nonempty timed-record names are skeleton names: Bip00, Head, Spine,
  Prop1/Prop2, hands, forearms, calves and toes. There are 10,401 empty names.
  These names do not identify effect assets.

The original loader assembly at **0x41e834–0x41e84a** calls `GetPeriod`, performs
`FDIV [0x6a2434]`, then calls the x87 integer-round helper and stores the result.
The divisor bytes at 0x6a2434 are `6f 12 83 3c` = **0.016f**. The saved loader
decompilation omits this division. Therefore a set's frame period is
`round(GetPeriod()/0.016f)`, not `round(GetPeriod())`.

Original `FUN_0064e6c0` calls `D3DXFrameFind`, returning a frame matrix pointer.
Original loader instructions at 0x41e67d, 0x41e69f, 0x41e6c1, 0x41e751,
0x41e773 and 0x41e795 use **FILD**, converting signed integer file values to
floats. They do not reinterpret IEEE float bits.

Original Rena 0's constructor `FUN_0064c840` installs vtable 0x6a4e10. Its
slot +0x18 is `FUN_0043ffc0` (move execution), +0x1c is `FUN_00445ee0`
(input selection), and **+0x20 is `FUN_00423310`, which returns false**.
`FUN_00421410` uses that last slot to authorize animation blending. It does
not generate melee geometry. Moves 40/41/42 are jump, and the 400 family is
shooting in `FUN_0043ffc0`, so the present issue #26 description is misleading.

## NN.dat field inventory

All integers below are four-byte little-endian values. Runtime offsets are
original structure offsets, **not file offsets**. Counts introduce variable
vectors; the stream has no padding between its records.

### Header and moves

| File order / width | Original meaning | Parser before fix | Runtime before fix |
|---|---|---|---|
| Tag, 4 | Leading format word; loader reads and does not branch on it here | Read/discarded | Unused |
| Model name, 260 | `.X` filename joined to the selected costume directory | Move parser skips; scene separately reads | Scene loads first usable NN.dat name rather than taking the equipped slot explicitly |
| Header 0/1, 4 each → player+0x324/+0x328 | First mode activation thresholds/duration; consumed by `FUN_0043f4d0`, `FUN_00421fe0`, `FUN_00422160` | Discarded | Wiki/port hypermode substitutes |
| Header 2, 4 | Loader local; downstream meaning not established | Discarded | Unused |
| Header 3, 4, file+0x114 | Equipped item ID, passed to `FUN_00433eb0` | Correct | Combo validation and item load |
| Header 4/5, 4 each → player+0x32c/+0x330 | Other mode activation thresholds/duration; `FUN_0043f4d0`, `FUN_004220e0` | Discarded | Wiki/port substitutes |
| Move count, 4 | Number of serialized rows | Correct, bounded | Iteration |
| Move ID, 4 | Index into `player+0x880+id*0x1c`; repeated IDs overwrite | Correct overwrite semantics | Lookup by ID |
| Row+0, 4 | Incoming move's selection value, compared against current row+4 by selectors | Named `recordFlags`; read | Ignored |
| Row+4, 4 | Current move's cancel threshold, compared to destination row+0 | Read as `cancelWindow` | Ignored; issue claims this is a frame window, but comparisons use **destination move rows**, not elapsed counters |
| Section count, 4 | Ordered phase vector | Correct, bounded | Phase cursor |
| Section tag, 4 | Controller animation set index for that combo | Correct | Used with silent set-0 fallback on missing/invalid selectors |
| Entry count, 4 | Ordered, timed state records for that phase | Correct stream consumption; capped storage | Only first combat record is used |

For example `0x296c = 0x880 + 301*0x1c`, so Rena's
`currentRow[4] <= player[0x296c]` condition permits **300→301**, not a comparison
to an elapsed timer. `0x2988` likewise names row 302. Row 300 values are 10/20,
301 values 20/30, 302 values 30/50 in the winning bundle. The issue's proposed
300→311 normal chain confuses a directional branch with the ordinary chain.

### Timed state/hitbox record (154 file bytes → 128 runtime bytes)

| File field | Runtime offset | Original use / ambiguity | Before fix |
|---|---:|---|---|
| Bone name[30] | +0 | Matrix pointer from `D3DXFrameFind` | Misnamed `effectName`; never resolved |
| Frame, i32 | +4 | Phase-local cursor threshold, `FUN_004212f0` | Read, used as move-global startup |
| 3 signed integers converted to float | +0xc/+0x10/+0x14 | Bone-local first collision anchor; `FUN_00420880` transforms it | Float-bit read and discarded |
| Radius, i32 | +0x24 | Attack sphere/capsule radius | Read from first combat entry only |
| Combat[0..19], 80 bytes | +0x30..+0x7c | Combat/response block; individual map below | Only selected columns retained |
| State/input word, i32 | +0x28 | Bits read by state selectors and hit/guard logic | Discarded |
| Direction/attack word, i32 | +0x2c | Direction mask/unblockable and other flags; precise remaining bits need recovery | Discarded |
| Shape, i32 | +8 | Zero sphere; nonzero capsule between two transformed anchors | Discarded |
| 3 signed integers converted to float | +0x18/+0x1c/+0x20 | Second collision anchor; `FUN_00420880` | Float-bit read and discarded |

`FUN_004212f0` selects the current record once its next frame threshold is reached.
The selected record remains active until replaced. Empty and noncombat entries
also change state words; they are not generic sound or pose effect events.

| Combat index / runtime offset | Evidence-backed interpretation / remaining ambiguity |
|---|---|
| 0 / +0x30 | Base HP power, `FUN_00639160` damage chain |
| 1 / +0x34 | Retain raw; meaning not established in this audit (zero across surveyed NN.dat entries) |
| 2 / +0x38 | Retain raw; occasional 300, consumer interpretation unresolved |
| 3 / +0x3c | Retain raw; small values, consumer interpretation unresolved |
| 4 / +0x40 | Retain raw; zero in surveyed NN.dat entries |
| 5 / +0x44 | Victim gauge feed; **not HP damage** |
| 6 / +0x48 | Reflection/damage-path scalar; exact nonshot role needs consumer verification |
| 7 / +0x4c | Gauge-path scalar A |
| 8 / +0x50 | Gauge-path scalar B |
| 9 / +0x54 | Attacker hitstop/stun scalar |
| 10 / +0x58 | Defender hitstop/stun scalar |
| 11 / +0x5c | Retain raw; distinct scalar, not an animation selector |
| 12 / +0x60 | Retain raw; distinct scalar, not an animation selector |
| 13 / +0x64 | Hit reaction category, passed through `FUN_0063ba80` |
| 14 / +0x68 | Alternate hit-resolution field; exact branch remains unresolved |
| 15 / +0x6c | Hit sound ID; **not projectile ID** |
| 16 / +0x70 | Impact effect ID, resolved through effect descriptor table |
| 17 / +0x74 | Signed release/reaction offset A; bullet charge consumer writes player+0x87c |
| 18 / +0x78 | Signed release/reaction offset B; bullet charge consumer writes player+0x878 |
| 19 / +0x7c | Retain raw; zero across surveyed NN.dat entries |

Raw unresolved fields must be retained with offset names and evidence, rather than
assigned invented animation/effect meanings. `parseBulletParameter` uses the same
record shape, so its transform type error and first-record flattening need the
same correction.

### Animation trailer

| File field / width | Original use | Before fix |
|---|---|---|
| Animation-set count, 4 | One row per controller index | Correct |
| Blend metadata, 4 → set+0x1c | Old countdown/new blend normalization, allowed by class callback | Correct |
| Counter gate, 4 → set+0x20 | Nonzero continues elapsed beyond period; zero permits generic phase completion | Correctly read; generic period comparison missing `/0.016` |
| Texture-event count, 4 | Number of texture replacement intervals | Read, payload skipped |
| Start/end/repeat, 12 | Active interval `[start,end)`; elapsed modulo repeat when positive, `FUN_0041f580` | Discarded |
| Source texture name[60] | Index lookup by texture name, `FUN_0064e7c0` | Discarded |
| Replacement texture name[60] | Existing or newly loaded texture index, `FUN_0064ecd0` | Discarded |

The trailer event size is correctly **132 bytes**. These records animate faces,
eyes, weapon visibility and other material textures. There are no effect-spawn
IDs in this trailer. The set's elapsed also drives controller position as
`elapsed*0.016` in `FUN_0041f580`; the port instead accumulates host `dt`.

## Item and bullet lookup audit

The four integers in each item bullet row are magazine index, **pool capacity**,
bullet file type and variant/status. `FUN_005f80c0` receives `type*10+status`;
the row index passed by a weapon launch helper is a different namespace.
The `shotNum` interpretation as volley count is unproven and conflicts with
Rena's executable emitting one bullet from a row whose value is 4.

Rena 0 item 001 row 0 is `(0,4,0,0)`, row 2 is `(1,3,2,0)`. Normal shoot
move 400 emits **row 0 at phase tick 12**, charged move 450 emits **row 2 at
tick 13** (`FUN_0043ffc0` → `FUN_00434fd0` → `FUN_00435000`). Row 0 loads
`bullet/001/000.dat` → `03.X`; row 2 loads `002.dat` → `05.X`. Higher charge
and weapon-specific launches require their own recovered handler rules;
they cannot be deduced from magazine membership or smallest type.

Before fix, `main.cpp::loadBulletParameter` and `Fighter::shot_count` duplicate
the same lowest-type selection. Every non-tap tier shares one parameter/model.
`fire_shot` launches immediately from `(forward*60, height100)`, with a 20-tick
port state and no recovered firing move. A shot's orientation uses velocity and
no handler roll; `shot_visual.h` correctly labels this remaining port rule.

## Hardcoded / substitute inventory before implementation

| Location | Substitute and consequence |
|---|---|
| `fighter.h::FighterConstants` | Shared walk420/run900/airdash1200, modal handler values ×60; phase-specific acceleration/decay and combo identity discarded. `kTurnSpeed=8` opponent lerp has no original provenance. |
| `fighter.cpp::update_facing` | Always face opponent in every state, including idle/hit; prevents input-driven turnaround. |
| `update_movement` | Raw facing-relative stick translation; airborne multiplier0.7; dash direction locked for full fixed window. No arc from current-facing travel. |
| `update` | Inertial decay0.8 applied to attacks and all nonmovable states; no recovered attack displacement. |
| `try_dash` / `dash_move_for` | Fixed20-tick dash; only ground Up20/Down27, side/air unresolved; air hangs for window. |
| `try_jump` / `jump_chain_move` | Shared720 launch,1800 gravity,720 hold rise,420 ceiling,1.2s budget; one startup tick substitutes for move40 completion. Apex threshold360 derives original6/tick but is scaled using60. |
| `state_to_move_id` / `resolve_attack_move` | Port state mapping and blanket neutral300/dash330/air340. No full input/cancel selector. |
| `advance_animation_phase` | `round(periodSeconds)` compared to ticks; clock increments only when another phase exists. Loop=true is universal. |
| `update` animation clock | Accumulated/clamped dt rather than source elapsed×0.016; phases and poses can disagree. |
| `resolve_swing` | First combat entry anywhere in move; phase-local frame flattened globally; remaining entries ignored; legacy8 active/17 recovery fallback. |
| `try_melee_hit` / `hitbox_debug` | Attack sphere at chest; static bind-pose victim anchors; capsule and bone-local offsets ignored. |
| `set_state` / `can_act` | No second melee press while attacking; timer expires move before data-defined end. |
| `fire_shot` / `shot_count` / `loadBulletParameter` | Immediate shot, fixed muzzle, fixed20-tick state, lowest-type row, pool-size-as-volley, only2 model slots for4 tiers. |
| `Controller` binding | Universal looping pending `.X` playback verification; class blends recovered only for Rena2. |
| `Scene::loadCharacter` | Model chosen from first usable NN.dat instead of explicit selected slot. |
| effect/camera consumers | No weapon ribbon producer; attack impact uses port effect choice; no action-camera flag from chain handler. |

Walking and forward dash are useful **regression baselines**, not parser proof.
The verified fix must preserve their ability to play the correct bound rows
and travel correctly, while documenting any measured change required by the
original period conversion and recovered handler speeds. Exact preservation
of a one-tick startup bug would conflict with reproducing original timing.

## Implementation boundary

The user authorized recovering executable rules into declarative behavior data
after this audit. Runtime execution should share one move clock and record
cursor, use exact combo rows and transformed bone anchors, and consume recovered
behavior programs for movement, trails, selection and projectile launches.
No visual inference or per-combo symptom patch is evidence. Fields whose uses
remain ambiguous stay raw and explicitly recorded. Tests must read the same
bundle-winning assets as runtime and distinguish synthetic fixtures from them.

## 10. Post-implementation corrections

These supersede the corresponding "before fix" readings above. Each was verified in the
original executable through the Ghidra bridge; addresses are original VAs.

### 10.1 The executor's phase and tick fields

`FUN_0043ffc0` reads **phase** at `this+0xadf4` and **tick** at `this+0xae04`
(case 0x168: `0x443854 CMP [ECX+0xadf4],0`, `0x4438b6 CMP [EAX+0xae04],0x2`,
`0x443aef CMP [ECX+0xae04],0xd`). `this+0xadf8`/`this+0xae08` are the sibling
track-0 counters that `FUN_00421100` writes alongside them. An earlier reading
placed the decompiler's `param_1[0x2b7d]`/`[0x2b81]` at `0xadf8`/`0xae08`; that is
refuted by the instructions above. The tick increments once per call at the tail
(`0x445ce9 ADD ECX,0x1`) and every transition path jumps to `0x445d4c`, which skips it.

Consequence for `move_behavior.h`: the guard pairs are `[0xadf4]==phase` and
`[0xae04]==tick`, which is exactly how the port matches a `MoveRule`. Three table
entries were wrong under the old reading and are corrected: **360** and **370**'s ten-update
hold is phase **2** tick 13 (`0x443aef`, `0x443e8b`, both inside the `[0xadf4]==2`
branch), not phase 0; and **402**'s airborne tap launches at tick **13**
(`0x444c7a CMP [EDX+0xae04],0xd`), not 12.

### 10.2 The attachment system has no visibility flag

`FUN_00434a70` is `__thiscall FUN_00434a70(int slot, int propId)` with `RET 8`. Slot
identity is the **prop id** at `manager+0x18+slot*4`; `propId < 0` clears it
(`0x434a95`), a non-negative id is gated by the per-prop availability byte at
`manager+0x0c+propId` (`0x434a9f`), and a successful bind writes the slot's bone matrix
into the prop (`0x434aca`) and runs one ribbon update (`0x434b0b`). "Visible" is therefore
derived — `id >= 0 && available[id]` — and there is no per-slot boolean.

The executor's prologue re-binds slot0<-prop0 and slot1<-prop1 and then calls
`FUN_00434bd0` to deactivate both (`0x43fff4`, `0x440006`, `0x440014`), so both bindings
and the active latch are recomputed from scratch every frame. Nine state bodies clear a
slot with `FUN_00434a70(slot,-1)`; only four have a tick guard, and only two of those are
the moves the issues name: state 400 (our move 400) hides at tick > 11 (`0x444850`) and
state 0x192 (our 402) hides at tick > 12 (`0x444c34`). Moves 450 and 460 contain no such
call at all, so their attachment stays bound and the grenade leaves the muzzle anchor.

`FUN_00435000` transforms the bound slot's muzzle anchor with `D3DXVec3Transform` and
falls back to the bone origin only when the prop id is -1 (`0x4350a2 JL -> 0x4350f1`).
`FUN_00434fd0` always passes slot 0. `FUN_00435450`, the explicit-position spawner the two
red nata rows use, reads no anchor.

### 10.3 Item anchors are three points, not a transform

The nine signed integers per attachment record land at `WeaponSlot::muzzle`,
`::ribbonRoot` and `::ribbonTip`. The first triple goes to the manager's per-prop muzzle
table; the other two are the ribbon prop's two anchors, transformed per frame with
`D3DXVec4Transform` in `FUN_00430120`. The earlier "position + two rotations" reading is
withdrawn.

### 10.4 The ribbon shifts on change, not on every call

`FUN_0042fff0` compares the refreshed tip sample against its accepted copy with
`FUN_00430670` (four float comparisons, `0x43001d`) and only then shifts the history and
grows the length by 5 (cap 40). The decay of 2 sits *outside* that branch and runs on
every call. The port's update previously shifted and grew unconditionally, which stacked
duplicate samples under a held weapon.

## 11. Remaining substitute behaviour after this pass

Still port rules or unrecovered, by file:

- `move_behavior.h` carries the walk and forward-dash profiles for all 46 base combos and
  the recovered **Rena 0** (`0x43ffc0`) move program only. The other 45 combat handlers
  still use the documented compatibility fallbacks for attacks and shots.
- Recovered-but-unimplemented Rena 0 behaviour: the **facing** relaxations
  (`FUN_0042db10`/`FUN_0042dc20`). An earlier draft of this section called them
  "bank/lean" and dismissed them as unrelated to facing. That was a guess and it was
  wrong: the two fields they drive are angular components of the yaw.
  `FUN_004202b0` moves the fighter by `cos(this+0x5c + this+0x60 + this+0x64) * speed`
  and `FUN_00420b30` builds the root Y rotation from the same sum, so both the movement
  direction and the visual facing read them. `FUN_0042dd90` (called every frame from
  `FUN_004202b0`, no arguments) computes the bearing to the opponent through
  `FUN_00423580` and writes it to `this+0x5c` while carrying the previous value's delta
  into `this+0x64`. `FUN_0042db10(this, target, rate)` walks `this+0x64` toward `target`
  in 360-degree wrapped space and snaps to it once the wrapped difference is within
  `rate`; `FUN_0042dc20` does the same and additionally counter-rotates `this+0x60` by the
  applied delta. What the per-move calls mean for the COMBO (`this+0x64` is the fighter's
  own accumulated angle, so the "target 0" argument is not an absolute world yaw) is the
  open part — see §11.3. Until it is resolved, these moves keep the port's stale facing.
  370's phase-2 tick-2 field writes; 460's tick-0 `this+0x54 *= 0.5`; the 402->403 and
  360/370/460->469 transitions; and states that re-bind slots to props other than 0/1 are
  likewise still unimplemented.
- The port's move clock is one tick ahead of the rule numbering at evaluation time: the
  move binds on the release tick and `advance_animation_phase` increments at the end of
  that same update, so `Fighter::execute_move_program` sees rule tick N while
  `phase_elapsed()` returns N+1. `animation_data_test.cpp` measures against the rule
  numbering to keep its assertions meaningful.
- Jump, side/back/air dash, reload/charge conversion and the flight budget retain the port
  constants they had.
- `applyWeaponVisibility` in `src/main.cpp` is the draw-side consumer of the bind state.
  It runs from the per-frame placement paths (versus and match); a scene whose placement
  is baked once keeps its attachments drawn.
- Move 460 (airborne charged shot) is unreachable with Rena 0: her magazine charges yellow
  at `chargeMax/tickRate` = 0.9375 s, longer than the leap, so a normal air release fires
  the tap tier. Its rule is verified against the table, not exercised in play.
- Full billboard flag `0x1000`, projectile reflection `0x100`, the remaining combat-column
  consumers, animation metadata for the extra `.X` sets, and the `has_combat()` radius/HP
  gate remain open as the handoff records.

### 11.1 Highest-priority open question: the combat-record gate

`MoveEntry::has_combat()` is `hitRadius > 0 && baseDamage > 0`, and it is what decides
whether a phase has an active hit volume at all (`Fighter::melee_in_active`, the melee
loop in `match.cpp`, and the projectile contact loop).

**Recount on the winning bundle bytes** (the copies the runtime actually reads, not the
extracted tree — a temporary scan inside `animation_data_test`, since the numbers differ):
of **12,161 stored records across all 46 combos, 113 have `radius > 0 && combat[0] == 0`**.
The extracted-tree figure quoted earlier (121/50 files) is superseded. The 113 are not a
long tail — they are concentrated:

- **moves 500 and 501 of every combo** (2 records each, 96 in total): radius 150, power 0,
  gauge 0, `combat[13] == combat[14] == 113`, `combat[15] == combat[16] == 10`, shape 0.
  Every character carries the identical values, which is the signature of shared reaction
  or template data rather than an attack volume.
- **Mion 310** (all three weapons): radius 10, shape 1 (capsule), effect 30 — a real
  character-specific attack row with no HP power.
- **Mion 370 phase 1** and **Rika 370 phase 0**: radius 60/36, shape 0, everything else
  zero, carrying state flags `0x2400` / attack flags `0x20008` / `0x24008`.

So the "115 moves can never hit" figure is misleading in the other direction too: the bulk
is the 500/501 pair, and the radius>0 rows that remain are mostly (a) genuine non-HP hit
volumes such as Mion 310 phase 0 (`radius 10, power 0, reaction 113, effect 30`, with the
move's damaging record in a later phase) and (b) Mion 370 phase 1 / Rika 370 phase 0.

**The characters' ordinary attacks are not zero-power.** An earlier draft of this section
implied they were, from a scan that read each phase's FIRST record. `radius` is 0 on those
lead-in records, so they are not hit volumes at all, and the damaging row sits later in the
phase: Rena 300 phase 2 entry 1 is `radius 20, power 1500, gauge 50, reaction 100`, and
Akane 300 is the same at `frame 3`. Reading a phase's first record instead of its hit rows is
what produced the false "most attacks are zero-power" impression; do not repeat it.

**RESOLVED.** The original's predicate was recovered from the ORIGINAL executable and
byte-verified: `FUN_00637950` (the record-driven contact resolver, sole caller
`FUN_00637680`, one call per frame from the battle update `FUN_00634f60`) tests **radius**:

```
006379DA  8B 4D 08         MOV  ECX,[EBP+0x8]      ; the volume object
006379DD  8B 51 10         MOV  EDX,[ECX+0x10]     ; volume->currentRecord
006379E0  83 7A 24 00      CMP  dword [EDX+0x24],0 ; ★ record+0x24 = radius
006379E4  75 05            JNZ  006379EB
006379E6  E9 AD 15 00 00   JMP  00638F98           ; radius==0 -> epilogue, no test
```

`combat[0]` is read exactly twice in the whole 1501-instruction resolver, both inside the
HP math (`0x638a32`, `0x638a6e`) and never as a branch. Every downstream consumer is
reached when power is 0: impact effect (`combat[16]` → `0x63811a`), attacker/victim hitstop
(`combat[9]`/`[10]` → `0x638503`/`0x638515`), knockback (`combat[17]`/`[18]` → `0x638633`),
reaction (`combat[13]`/`[14]` → `0x6386ff` → `FUN_00421080`), mode gauges
(`combat[5]`/`[6]`/`[7]` → `0x638321`/`0x6383e6`/`0x638493`) and the stagger gauge
(`0x6385ec`). Reading 1 above is correct; reading 2 is refuted. Only HP damage is 0.

The port now matches: `MoveEntry::has_combat()` is `hitRadius != 0` (the original compares
the dword against zero, not signed-greater; no shipped record has a negative radius, so the
two agree on this data). The runtime conditions the original applies *in addition* to the
record — the per-target allowance `this+0x90[slot] > 0` / `this+0x88[slot] == 0`, armed per
attack by `FUN_0042c840(this,1)`, plus the `record+0x2c` bits `0x10000`/`0x20000`/`0x8000`
— are not yet ported and are the next layer of this work.

### 11.1.1 The zero-power contact path (implemented)

Recovering the predicate was not sufficient on its own: two later stages still assumed a
contact implies HP damage, and both had to be fixed before a zero-power record could behave.

- **`Fighter::take_damage()` clamped every hit to 1 HP** (`amount = std::max(1, amount)`,
  and the guard branch used `std::max(1, amount / 5)`). A record with power 0 therefore took
  1 HP, and both melee (`try_melee_hit`) and projectiles reach that line. The clamp is gone;
  the amount now floors at 0, and the guard branch no longer resurrects a zero hit. This is
  the change that makes "power 0" mean no HP.
- **What a zero-power contact still does**, all verified through the real contact path:
  enters the victim's hitstun with the record's own `defenderHitstun`, applies the record's
  reaction (`combat[13]`, fed to `FUN_0063ba80`), spawns the record's impact effect
  (`combat[16]`), and records no HP and no damage statistics.
- **Gauge: deliberately NOT wired from the record.** `combat[5]`/`[6]` are the original's
  internal **mode gauges** (`FUN_00637950` writes `+0x838`/`+0x840`/`+0x83C`, 0..100
  accumulators with their own thresholds), whereas this port's `gain_gauge()` feeds
  `m_gauge`, the player-selected **hypermode** bar. Those are different mechanics with
  different consumers, and `gain_gauge` also multiplies by `m_gaugeRate`. Routing the
  recovered columns into it would report the right number through the wrong system, so the
  damage-derived hyper credit stands until the port has mode-gauge accumulators. An earlier
  revision of this pass did route them and was reverted for exactly this reason.
- **Knockback (`combat[17]`/`[18]`) is still not applied.** The original writes them into a
  launch-velocity field (`+0x87c`/`+0x878`), not into the port's `m_velocity`, and nothing in
  the corpus fixes the conversion. Applying a guessed scale would be invented motion.
- **The per-swing allowance stays where it is.** `FUN_00637950` consumes `this+0x90[slot] on
  contact; the port splits that into `note_melee_hit()` writing the flag and the scene's
  `already_hit_this_swing(j)` gate (`match.cpp:143`). `try_melee_hit()` itself does NOT
  consult it, and a test that assumes it does is asserting the wrong seam.
- **Coverage, verified to be real coverage.** Both defects were re-introduced one at a time
  and the tests re-run, so the assertions are known to bite rather than merely passing:
  - restoring the old predicate (`hitRadius > 0 && baseDamage > 0`) fails 6 checks across
    the melee and projectile tests — the record stops being checkable at all;
  - restoring the old clamp (`std::max(1, amount)`) fails 5 checks — the victim loses the
    1 HP it should not, on both paths.
  - `animation_data_test.cpp`'s `zero_power_contact()` installs a reshaped zero-power record
    into an equipped combo's row (`CharacterMoves::install_move_phase0_record`, test-only)
    and drives the **real** collision and resolution: HP, `damageTaken` and `damageDealt`
    must not move, the hyper bar must not move, the victim must enter `Hit`, and the stun
    must last exactly the record's `defenderHitstun`.
  - `zero_power_projectile()` does the same through the pool, with the row's own bullet
    model bound — without a model a shot takes the legacy XZ fallback
    (`projectile.cpp:185`) and never reads the record, which would make the test vacuous.
  - `melee_rules_test.cpp`'s `testRepeatContactSuppression()` proves the per-swing allowance
    **through `Match`**, re-placing the victim inside the live volume on every one of the
    swing's 6 active frames. Removing the scene's `already_hit_this_swing` gate makes it
    report 5 contacts and 60 HP instead of 1 contact and 92 HP, so the assertion is on the
    seam that actually suppresses the repeat, not on the flag helpers.
  - `fighter_script_test.cpp` case 10 pins the zero-power contact and the guard interaction:
    guarding 3 damage still takes its historical 1, guarding 20 still takes a fifth, and a
    zero-power contact takes nothing even guarded. Each case re-enters `Guard`, because a
    landed hit leaves it for `Hit`.
- Record-column plumbing was **removed rather than left unused**: with the gauge and
  knockback consumers still unported, a struct carrying those columns would have been dead
  weight, so they are documented here instead of threaded through `take_damage`.

Still open from the same investigation, and **not** silently absorbed:

- **The combat column labels in `combat_record.h` may be shifted by one.** The resolver was
  traced column by column and the assignment it supports is `[5]`/`[6]`/`[7]` = gauge
  accumulators, `[8]` = a further gauge, `[9]`/`[10]` = hitstop, `[13]`/`[14]` = reaction,
  `[16]` = impact effect, `[17]`/`[18]` = knockback — which agrees with the port for
  `[9]`/`[10]`/`[13]`/`[16]`/`[17]`/`[18]` but disputes the port's `hpDamage`/`reflectDamage`/
  `gaugeGainA`/`gaugeGainB` names on `[5]`/`[6]`/`[7]`/`[8]`. Reconcile against the original
  consumers before renaming anything; the names are load-bearing in the HUD and damage code.
- The per-attack allowance arming in the other 45 move programs is unrecovered (only Rena's
  `FUN_0043ffc0` sites were verified), and the flag bits above are known by test site only.
- The volume-vs-volume clash test `FUN_00638fd0` (engaged by `record+0x28` bit `0x10000`)
  is a separate mechanism with no radius test; the port does not have it.

### 11.2 Other verified open items from the independent review

- The port's fixed step is 64 Hz (`FixedStep::tickRate`) while the recovered handler values
  are per original 60 Hz update, so live locomotion runs ~6.7 % fast and the pose clock
  (`elapsed × 0.016`) disagrees with movement by ~2.4 %. The tests step at 1/60 and cannot
  see it. Scaling displacement or moving the simulation to 60 Hz is a design decision, not
  a data fix.
- Attacks for the 45 combos without a recovered move program no longer turn toward the
  opponent: `update_facing` is gated on `!locomotion(m_moves)`, which is now false for
  every shipped combo, and only Rena 0's rules carry a facing turn.
- Duplicated damage math: `projectile.cpp` scales `baseDamage * (hp/20000)` inline where
  `fighter.cpp` uses `portDamage(shotPoolDamage(...), maxHP)`; the two disagree for odd
  `baseDamage` and the `20000` duplicates `kPoolScale × 2`.
- Projectile lifetime is compared before the tick increments (`ticks > lifetime`), which
  moves a shot `lifetime + 1` times; the original's comparison order is unverified.
- A move program sets the state timer to 0, and a row that resolves to no usable set would
  leave the state with no exit (soft-lock); unreachable with the shipped rows but unbounded.
- Moves 360/370's and 400/402/450/460's `FUN_0042db10`/`FUN_0042dc20` facing relaxations
  are still not encoded. They are yaw, not bank (see the correction in §11); what remains
  open is the combo's accumulated-angle semantics, in §11.3.

### 11.3 Facing: recovered, and the port's gate is not the regression

Recovered from the ORIGINAL with authoritative xrefs (`/get_function_xrefs` is the endpoint
that matters here; the offline corpus cannot establish callers). All three fields are
**degrees** of yaw about +Y, and they are different things:

- **`this+0x5c` = the bearing to the target `this+0x38`**, refreshed every frame by
  `FUN_0042dd90` as `atan2(target.z - z, target.x - x) * 180/pi` (`FUN_00423580` is the CRT
  `atan2`, radians, zero = +X, positive toward +Z). No per-character move program writes it.
- **`this+0x64` = the unrealised turn lag.** `dd90` does `0x64 += (0x5c_old - bearing)` and
  then `0x5c = bearing`, which leaves **`0x5c + 0x64` bit-invariant**. Only a move program's
  `FUN_0042db10`/`FUN_0042dc20` (or the one-shot re-target `FUN_00421670`, or a spawn/restore)
  changes it.
- **`this+0x60` = the movement-direction offset** relative to the facing. The programs store
  the eight compass values `{0, ±45, ±90, ±135, 180}` into it. `dc20` mirrors the negated
  `0x64` delta into `0x60`, so `0x60 + 0x64` — and therefore the movement direction — is
  preserved while the facing rotates; `db10` leaves `0x60` alone, so movement follows.
- **`this+0x30` = a visual-only yaw offset**, never written by fighter code (the state setter
  `FUN_00421080` zeroes it on every state change); treat it as 0.

The two sums are therefore **not the same angle**, which is the reconciliation the earlier
draft was missing:

```
movement direction : (cos S, 0, sin S) * this+0x54,  S   = 0x5c + 0x60 + 0x64   (0x42030a/0x42034c)
visual root Y      : D3DXMatrixRotationY(-(S_v + 90 deg) * pi/180), S_v = 0x5c + 0x64 + 0x30
                     (0x420dd0-0x420de8; the divisor is 180.0, the multiplier is -pi)
```

In the port's convention (`(sin m, cos m)` movement and `RotY(m + pi)` root) that is
`m_translation = 90 deg - S` and `m_rendered = 90 deg - S_v`; they coincide only when
`0x60 == 0x30`. The port's `m_inputFacing = atan2(opp.x - x, opp.z - z)` equals `90 deg - 0x5c`,
i.e. it is the raw turn target, matching `dd90`'s output.

**The consequence corrects the earlier claim that the missing handler rules are a facing
regression.** Because `dd90`'s rewrite leaves both sums invariant, a fighter whose handler
never calls `db10`/`dc20` **does not turn at all** in the original — it holds its displayed
yaw and its walk direction while `0x5c` tracks the opponent underneath. So the port's gated-off
`update_facing` is closer to the original than the old legacy turn was: a shared per-frame
turn toward the opponent is *not* what the original does. What the port actually lacks is the
**turn rate per unrecovered state** (`db10(target = 0, rate)` with rates 2..20/180 deg per
call, and the 8-way stick turn `FUN_00421780` drawing its rate from `this+0x874`, which the
programs also write), plus the "no turn" state being a legitimate outcome rather than a gap.

Remaining unknowns: who writes `0x30` (none found in fighter code), what the `0x63xxxx`
consumer of `(0x5c + 0x64)` at handle `this+0x684` is (per-fighter 3D audio and a camera
object both take these angles), and the meaning of a negative `+0xa0` (movement and facing
freeze indefinitely). Encoding must not resume until `0x60`'s strafe/backpedal states exist in
the port, or the movement/visual split cannot be represented.

### 11.4 The release capture: what is and is not established

Measured on 2026-10-07 with the recipe from `RELEASE-CHECKLIST.md` §3.1
(`--screen=title --local-players=2 --script=tests/scripts/frontend-1v1-rematch.txt
--headless --out=… --size=1280x720 --frames=15500`):

| tree | digest (sha256, first 8 bytes) |
|---|---|
| `RELEASE-CHECKLIST.md` §3.1 as banked | `8cc49e6c…` |
| worktree at the session's start commit `db6a083`, clean checkout | `75294efd…` |
| the post-checkpoint tree, two consecutive runs | `6ba7b2ca…`, `6ba7b2ca…` |
| that tree with **every rule this pass changed reverted** | `6ba7b2ca…` |

Established:

- **The capture is reproducible** on a fixed tree and environment — two consecutive runs
  hash identically — so a digest is a usable gate once those are pinned.
- **This pass's rule changes do not move it.** Reverting the corrected tick/phase table,
  the launch timings, the attachment rules and the ribbon semantics leaves `6ba7b2ca…`
  unchanged, so they are not what differs.
- **The changed pixels are global.** `75294efd…` vs `6ba7b2ca…`: 48.1 % of pixels differ,
  spread evenly across every row band (43.6–50.0 % per eighth of the frame), maximum
  channel-sum delta 765/765. A single mesh, attachment or effect would be local; this is
  consistent with a view/projection change, but consistency is not attribution.

NOT established, and previously overstated here:

- **A different digest between two trees does NOT show that either was dirty.** The
  `db6a083` worktree is a clean checkout, but its *build* was not identical to the
  environment the banked digest came from: it was configured in a separate directory,
  and the CJK caption font had to be staged by hand before the run would produce a frame
  at all. Settings (resolution, toggles, saved user settings), assets, compiler/flags and
  the rendering environment must all match before two digests are comparable. The banked
  `8cc49e6c…` therefore has **no established relationship** to any tree here yet.
- **A commit timestamp is correlation, not causation.** Committing files does not change
  the files, and it cannot change an executable that is already running or already
  built. The observed time agreement between the checkpoint commit and the first capture
  run is noted and adds nothing; the earlier sentence inferring a dirty baseline from it
  is withdrawn.

Next step before any re-banking: reproduce the banked digest by matching the environment
(recorded settings and build configuration), then attribute the difference with a proper
bisect of the prior work — one variable at a time. Until then §3.1's digest must not be
updated.
