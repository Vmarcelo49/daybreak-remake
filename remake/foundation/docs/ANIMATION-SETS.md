# Animation set indices and move-table binding

**Status:** the remake resolves source-supported states through the bound fighter's
`data/<char>/NN.dat` table and advances sections using the recovered set period and `+0x20`
gate. Grounded neutral melee → 300 and Up/Down ground dash → 20/27 are explicit port
inferences; the executable's initial-input selectors depend on player fields the port does not
model. Side/air dash, projectile, jump, and guard selectors remain unresolved and report
`anim_fallback()` rather than borrowing a guessed clip. Cross-fades are gated by the recovered
character-class callback; only Rena's slot-2 combo has a verified transition list.

| Evidence | What it establishes |
|---|---|
| `FUN_00421080` / `FUN_00421100` / `FUN_00421410` | A selected move binds its first phase's section tag to the animation controller. |
| `FUN_0041e180` plus `data/<char>/NN.dat` | The character-specific move ID, ordered phase tags, and effect records. |
| `FUN_0041f580` and `FUN_00421410` | Period-gated section advance and per-set blend weights; `+0x1c` seeds/normalizes class blends. |
| `--anim-player` on shipped `.X` rigs | What a controller set looks like; names are `Anim-1`…`Anim-124`. |

---

## 1. The naming is inverted — read the index, not the label

The loader reverses the animation array (`xmodel.h`, `std::reverse(m_.anims.begin(), …)`),
so **controller index 0 is `Anim-124`**. The original's `d3dx9_25.dll` enumerates in reverse
file order: set *i* is file set *N−1−i*, checked across all 124 sets of rika/01.X. Judge
every clip by what it shows, never by the number in its name.

## 2. The observed index map (rena, default weapon)

Transcribed from visual inspection. These are *controller* indices.

| Idx | Clip | Group |
|---|---|---|
| 0 | idle | base |
| 1 | walk | base |
| 2 | jump startup, on the ground | jump |
| 3 | jump startup, leaving the ground | jump |
| 4 | jump up momentum | jump |
| 5 | jump down momentum | jump |
| 6–10 | hit reaction, leans backwards | reactions |
| 11–12 | opens arms, unclear purpose | unclassified |
| 13 | dash startup | dash |
| 14 | dash loop | dash |
| 15 | dash recovery | dash |
| 16 | back dash | dash |
| 17 | back dash (skirt trails; reads as idle-body) | dash |
| 18 | landing, slight crouch | landing |
| 19 | side dash startup, left | side dash |
| 20 | side dash, left | side dash |
| 21 | unclear, side-dash family | side dash |
| 22 | side dash startup, right | side dash |
| 23 | raised-fist pose (Mario-style); input role unknown | unclassified |
| 24 | mirrored raised-fist pose; input role unknown | unclassified |
| 25 | hit taken while standing | reactions |
| 26 | thrown up, startup | knockdown |
| 27 | falling after 26 | knockdown |
| 28 | ground contact after 27 | knockdown |
| 29 | lying down | knockdown |
| 30 | getting up | knockdown |
| 31 | weapon swing startup (**nata**) | weapon |
| 32 | big weapon grab-and-spin (**iron clad**) | weapon |
| 33 | nata upswing; input role unknown | weapon |
| 34 | another weapon swing | weapon |
| 35 | hit taken from behind | reactions |
| 36–38 | behind-hit counterparts of 26–28 | knockdown |
| 39 | kick startup | kick |
| 40 | kick-like motion; input role unknown | kick-like |
| 41, 42, 58 | idle pose, no animation | idle |
| 43 | falling | landing |
| 44 | landing (exact sequence from 43) | landing |
| 45 | gut punch, contracts | reactions |
| 46 | head hit, extends | reactions |
| 47 | short spin, startup of something | unclassified |
| 48 | ground roll startup, after being thrown down | roll |
| 49 | roll | roll |
| 50 | recovery after roll | roll |
| 51 | lunge attack startup | lunge |
| 52 | lunge continuation | lunge |
| 53 | lunge finishing pose; input role unknown | lunge |
| 54 | jump forward startup | jump |
| 55 | flying pose, going forward | jump |
| 56 | small arm/leg swing | weapon |
| 57 | big overhead swing | weapon |

**The block is a hand-authored visual grouping**, not an input map: base (0–1), jump (2–5),
reactions (6–10), dash (13–17), side-dash-looking clips (19–22), raised-fist pair (23–24),
knockdown (25–30), weapon (31–34), back-hit mirrors (35–38), kick-like motion (39–40),
fall/land (43–44), roll (48–50), lunge (51–53), overhead (56–57).

## 3. Every attack needs its weapon dimension

The same set index is not a universal attack mapping. Weapon move rows differ by character
and costume; runtime animation selection must use the exact character/weapon `NN.dat` table.
`kWeaponIds[16][3]` and the `NN.dat` header at file offset `0x114` establish the table's item
ID (verified for all 46 legal character/slot combinations). The attack hit records live in
weapon move phases; the `data/item` table alone does not establish an animation selector.

The remake's simplified combat input does not reproduce every original selector branch.
`FUN_00445ee0` directly shows context-gated transitions such as
300→301→302, 20→330/331, 23/24→330/331, and 329/333/44→340; the choice depends on input,
move cancel windows, direction fields, and other player flags. A blanket `dash→330`,
`air→340`, or “pick any present weapon move” rule drops those conditions. The remake uses
move 300 as its grounded-neutral default inference because it is a normal-attack target in the
recovered handler; the handler selects it only through conditional branches, so this does not
prove the fresh AttackA selector. Dash and aerial attack animation selectors stay unresolved
until the port carries their branch state. Voice keys `shotA/B/C` are loaded as audio paths by `FUN_00431e70`;
they do not identify firing animation sets. The numeric 300-chain and EX helper paths also
do not establish a universal projectile-animation link.

## 4. Current state bindings and confidence

The runtime resolves a state to a move ID, reads `CharacterMove::first_set_index()` from
that fighter's bound table, and validates the result against its model. It does not keep a
parallel raw set-index table.

| Port state/context | Move selector | Evidence and limit |
|---|---:|---|
| Idle | 0 | Player reset calls `FUN_00421080(0)` (`FUN_0041de68`). |
| Walk | 10 | Walk move row selected by the state dispatcher (`FUN_00428510`). |
| BattleStart | 194 | Round reset calls `FUN_00421080(0xc2)` (`FUN_004219a0`). |
| Hit / Knockdown / KO | 103 / 196 / 203 | Reaction dispatch rows in `FUN_00428510`; runtime uses each bound table's tag. |
| Up / Down ground dash | 20 / 27 | Port inference from the directional families. Source selection is gated by opaque state/cancel fields in `FUN_0043ded0`; `FUN_00438310` handles an already-selected move. Air dash does not reuse this inference. |
| Grounded neutral melee | 300 | Port default inference from a conditional normal-attack target in `FUN_0043ded0` / `FUN_00445ee0`; the fresh input selector is unresolved. |
| Side dash | unresolved | The table has moves 23 and 24, but current left/right inputs are not tied to either. |
| Dash/aerial melee, shot, jump, guard, TagOut | unresolved | Current inputs do not carry enough recovered selector state. |

For example, Rena 00.dat move 20 has phase tags `[13,14,15]`. The parser also reads every
animation-set trailer row: the `+0x1c` transition value, `+0x20` phase/counter gate, and event
count. This is why set 14 holds even when the period expires: its gate is nonzero. In
`FUN_0063dad0`, zero stops the source elapsed counter at the period while nonzero keeps that
counter advancing; `FUN_0041f580` passes the resulting raw time to the D3DX track. The trailer
does not establish whether the D3DX clip wraps or clamps. The remake keeps its controller's
default loop policy for both gate values until `.X` playback metadata or a D3DX playback-type
comparison is recovered.

## 5. Phase timing and section transitions

`FUN_00421100` binds phase zero; the port does the same. `FUN_0063dad0` increments the
elapsed counter while it is below the rounded set period, or keeps incrementing when the
active set's `+0x20` is nonzero. In `FUN_004c57f0` and `FUN_00438310`, the original advances
to the next phase only when the rounded period is strictly less than elapsed and the active
set's `+0x20` gate is zero. The remake reads that gate from the NN.dat trailer and gets the
period from the matching `.X` rig's animation set.

`FUN_0041e180` constructs each runtime period with D3DX `GetPeriod()` and the rig's source
tick rate; comparisons against the original's `d3dx9_25.dll` matched every set in Rena 00,
Rika 01, and Akane 00. The game rounds the period to an integer and compares it directly to
its update counter, so the port preserves that strict boundary even though the units are
unusual. It does not guess from the move record's `+0x04` or a separate clip-end callback.

`FUN_004212f0` advances a cursor through timed runtime records using elapsed move ticks and
record `+4` thresholds. The loader reads the effect record's `v04` into
`MoveEntry::activeFrame`, which is strong evidence for effect-event timing. The cursor's exact
container owner and a link from that cursor to changing animation section tags have not been
recovered. It is therefore not evidence to switch animation phases.

`FUN_00421410` points at the selected animation-set table entry
(`player + 0x75e0 + setIndex * 0x38`). Its `+0x1c` is class-blend metadata: the old set's
value seeds the countdown, while the new set's value is the weight-ramp denominator in
`FUN_0041f580`. `FUN_0064ab30` passes the selected character and weapon slot to
`FUN_00649790`; its `(0,2)` branch constructs `FUN_0064c880`, whose vtable slot `+0x20`
contains `FUN_0064c8a0`. That callback returns true only for set pairs 1→31, 1→34, and
1→39. The shipped roster mapping joins Rena slot 2 to item 33 (`Rena 2`), and its NN.dat
contains old value 10; targets 31 and 34 carry 20, while target 39 carries 10.
`FUN_00421100` calls `FUN_00421410` for both source
controller banks, so a rejected full bind resets each bank and the remake hard-binds both
of its pose tracks for these state/phase changes. The separate one-sided
`FUN_00421240` path changes bank 1 only and is not generalized by this port helper. The move
record's `+0x04` remains a cancel-window threshold, not a phase duration.

## 6. Corrections to earlier claims

| Earlier claim | Corrected finding |
|---|---|
| AttackA/B/C could use fixed sets 2/3/5 | Those are jump clips; the original attacks are weapon/context dependent. |
| Voice keys or `shotA/B/C` name animation sets | They are voice cues; the firing animation selector is not recovered. |
| `ShotFinal` can use set 69 because move 503 exists | The EX helper can choose state 503 in a linked action; no universal shot-animation link is shown. |
| Jump should switch 41→43 based on `vy` | Move tags 41/43 exist, but the remake's jump input/state is not tied to those selectors. |
| Left/Right can be assigned to moves 24/23 from startup appearance | The table tags are known; their mapping to current controls is not. |
| Every section advances after its `.X` clip duration | The source uses rounded D3DX period, strict `period < elapsed`, and the set's `+0x20` gate. |
| `Phase+0x1c` is the move phase duration | Trailer `+0x1c` is blend metadata; phase timing comes from D3DX period plus `+0x20`. |
| Every move change cross-fades for eight ticks | The class callback rejects most transitions; Rena slot 2 uses old/new `+0x1c` values. |
| Weapon reach/damage live only in `data/item` | Nonzero attack hit records are in character/weapon move phases; the equipment pairing still matters. |

## 7. Verification coverage

`fighter_script_test` checks the resolver's move-ID → table-tag path, immediate default-class
switches, and explicit fallback status. `melee_rules_test` binds matching character/weapon
tables, checks strict phase timing and the auto-advance gate, and verifies Rena slot 2's
metadata-driven cross-fade. It also checks unsupported jump and side-dash selectors remain
visible as fallbacks. `animation_pose_test` checks real rig ordering and pose invariants.

The animation browser remains `--anim-player` (`--model=<rig.X> --anim-player [--anim=N]`):
one rig, no stage, arrows step the set index, WASD orbits, and the set name/index are shown.
