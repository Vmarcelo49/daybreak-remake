# Animation set indices and the state → set mapping

**Status:** steps 1–5 applied as far as the evidence goes — `CharacterMoves` exposes
each phase's set index, `state_to_anim_set` retargets Walk→1 (move 10) and Run→13
(move 20), and bound fighters resolve each swing to the situation's own weapon
move (sets, reach, damage, stun from the 300-family hit entries). AttackA/B/C
table rows stay as marked placeholders for the table-free path. The NN↔weapon
join is closed since: NN.dat number IS the weapon slot and file offset `0x114`
carries the weapon id (verified 46/46 against `kWeaponIds`), so battles load
the slot's own table. Open follow-ups are the phase-duration source, the
attack-sphere centre, the selector flags, and the vtable+0x20 handler hits.
The table history below is kept because it is
the evidence for those.

Built from three sources, kept separate on purpose because they have different confidence:

| Source | What it gives | Confidence |
|---|---|---|
| Visual inspection of `data/rena/01.X` in `--anim-player` | what each index *is* | direct observation |
| `research/decompiled/` (`FUN_00421100`, `FUN_00421410`, `FUN_004211f0`, `FUN_0041f580`) | how a set is chosen per layer | code |
| `data/<char>/NN.dat` via `character_moves.cpp` | move id → phase → index | parse, cross-checked below |

---

## 1. The naming is inverted — read the index, not the label

The loader reverses the animation array (`xmodel.h`, `std::reverse(m_.anims.begin(), …)`),
so **controller index 0 is `Anim-124`**. This is measured, not assumed: the original's own
`d3dx9_25.dll` enumerates in reverse file order, set *i* = file set *N−1−i*, verified across
all 124 sets of rika/01.X. So the `Anim-N` label is anti-correlated with position. Judge
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
| 23 | jump attack (Mario-style, fist up) | air attack |
| 24 | mirror of 23, left | air attack |
| 25 | hit taken while standing | reactions |
| 26 | thrown up, startup | knockdown |
| 27 | falling after 26 | knockdown |
| 28 | ground contact after 27 | knockdown |
| 29 | lying down | knockdown |
| 30 | getting up | knockdown |
| 31 | weapon swing startup (**nata**) | weapon |
| 32 | big weapon grab-and-spin (**iron clad**) | weapon |
| 33 | nata, up + attack | weapon |
| 34 | another weapon swing | weapon |
| 35 | hit taken from behind | reactions |
| 36–38 | behind-hit counterparts of 26–28 | knockdown |
| 39 | kick startup | kick |
| 40 | the kick (side dash + attack, nata) | kick |
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
| 53 | the lunge (dash forward + attack, nata) | lunge |
| 54 | jump forward startup | jump |
| 55 | flying pose, going forward | jump |
| 56 | small arm/leg swing | weapon |
| 57 | big overhead swing | weapon |

**The block is contiguous and semantic**: base (0–1), jump (2–5), reactions (6–10), dash
(13–17), side dash (19–22), air attack (23–24), knockdown (25–30), weapon (31–34), back-hit
mirrors (35–38), kick (39–40), fall/land (43–44), roll (48–50), lunge (51–53), overhead
(56–57). This is a hand-authored table, not a hash — which is what makes it usable.

## 3. There is no unarmed attack — every attack is a weapon attack

**This is the correction that invalidates the melee design in issue #10.** No character has a
bare punch; all attack with an equipped weapon, and only rare kicks. Consequences:

- A clip that looks like "a neutral standing pose with hands together" is a character
  **holding their weapon**, not an unarmed idle. That is what index 2 actually is, and it is
  why it was misread.
- The weapon groups above (31–34 nata/iron-clad, 39–40 kick, 51–53 lunge, 56–57 overhead)
  are **weapon- and character-specific**, exactly as `fighter.h` already warns for the
  weapon-specific moves (300+), whose set indices differ per character.
- Therefore **`AttackA` cannot resolve to one fixed set index.** It must resolve to the
  *equipped weapon's* attack set. The mapping needs a weapon dimension.

`kWeaponIds[16][3]` (issue #9) gives rena `{1, 3, 33}`, and each `WeaponDefinition` already
carries its bullet, magazine and gauge parameters — the data issue #10's melee declared
unrecoverable. Reach and damage are **weapon data, not port rules**.

## 4. What the .dat indices get right, and the bug that remains

Move 20's phases are `[13, 14, 15]`. The table above says **13 = dash startup, 14 = dash loop,
15 = dash recovery** — three phases, in order, matching a dash's structure exactly. Three
coincidences in a row is not chance, so:

- the `.dat` parse reads **valid controller indices** ✓
- `Phase->[0x00]` is the animation **set index** ✓
- the bug is in the **state → move-id column** of `state_to_anim_set`, not in the index
  column ✗

That is a retargeting of move ids, not a re-derivation of indices — a much smaller fix than
rebuilding the parse.

## 5. Corrections to claims made earlier in this work

| Claim | Status | Evidence |
|---|---|---|
| Move record `+0x04` is a phase duration | **already retracted** | file constant with no writer in `.text`; read only as a cancel-window threshold (35 sites in `FUN_0043ded0`) |
| `Phase->[0x1C]` is the animation set index | **wrong, retracted** | `+0xAE14` is initialised from it, tested `-1 < …`, then decremented (`FUN_00421410:20,23,36`; `FUN_0041f580:160,172,177`) — a remaining-ticks countdown, so `+0x1C` is a **duration** |
| AttackA → set 2 | **wrong** | index 2 is jump startup; the body pose is a weapon stance, not an unarmed idle |
| Walk → set 13 | **wrong** | index 13 is dash startup |
| Run → set 54 | **wrong** | index 54 is jump-forward startup |
| Melee reach/damage are port rules | **wrong premise** | they are weapon data, already recovered by issue #9 |
| The attack animation was "missing" | **wrong** | it plays; earlier captures were taken with no melee input, during `BattleStart`, or on an idle frame |

## 6. The RE path for set selection (partially recovered)

```
FUN_00421100(player, layer)      // both attack layers 0 and 1
  └─ FUN_00421410(player, layer, moveId)
       ├─ vtable+0x20  per-character-class virtual — success/failure only
       ├─ player+0xADE4+layer*4 = current Phase*
       ├─ player+0xAE14+layer*4 = Phase->[0x1C]  (duration, countdown)
       └─ FUN_0064ebc0 → controller vtable+0x54
FUN_004211f0(player, moveId)
  player+0xadec = moveId
  player+0xade0 = player + 0x880 + moveId*0x1c     // the move record
```

**Not yet located: where the set index itself is chosen.** `FUN_00421410` stores the
duration, not the index; the index selection is downstream of the `0x54` controller virtual.
This is the one gap before the table can be re-derived from the corpus rather than from
observation.

Also noted: `FUN_00421410` divides by **0.016** (60 Hz) when converting to seconds, while the
simulation runs at 64 Hz. Any timing ported from the .dat needs that conversion checked
against the logic tick rate.

## 7. What a fix requires, in order

1. **Expose the phase set index in `character_moves.cpp`.** DONE for the index:
   each phase keeps its section tag (`MovePhase::setIndex`, `first_set_index()`),
   which the file layout verifies end-to-end (moves end `0xb564`, the 124-entry
   anim table lands exactly on EOF). NOT DONE: the phase *duration* — the file
   dword seeding the +0x1C countdown is still unpinned (it hides inside the
   phase-vector construction), and the anim-table frame records are facial
   `.bmp` swaps, not timing, so they must not be read as durations.
2. **Re-derive `state_to_anim_set` from move id → phase → index**, anchored on the verified
   move 20 → `[13,14,15]` dash correspondence. DONE for locomotion (Walk→1,
   Run→13); attack rows still pending step 3.
   Roster check: the locomotion/jump rows (10/20/23/24/27/28/30/40–44) carry
   IDENTICAL tags in all 16 characters × all NN files — with one exception,
   rena/02's move 20 is `[54,55,15]`, which the machine plays as-is (move ids
   outrank set expectations). Weapon rows vary per character/costume and are
   read from the bound table, never assumed.
3. **Add the weapon dimension** to attack-state resolution: `AttackA` must select the equipped
   weapon's set, using the per-character/per-weapon indices already flagged for moves 300+.
   DONE provisionally: `Fighter::resolve_attack_move` picks 330 (dash) / 340 (air) /
   300 (ground) from the bound table with family fallback, and the swing binds the
   move's first-phase set. Each row cites its evidence; the selector flags behind
   the choice (+0x84/+0x830) are still unrecovered. The NN↔weapon join behind
   the binding is closed: NN.dat number is the weapon slot and file offset
   `0x114` carries the id (46/46 against `kWeaponIds`), so the battle loads the
   slot's own table, never the rig costume's.
   Follow-up states now also resolve through the table: dashes play their
   direction's move (Up 20 / Down 27 / Left 24 / Right 23) and Jump plays 41
   rising / 43 falling, switching on the vertical-velocity sign. Forward/back
   are solid (case yaw offsets 0 and +180 in FUN_00438310); the Left/Right ORDER
   is open — the side cases set -0.05 and +90.0, which is NOT a clean ±90 pair,
   so the assignment follows only the observed startup sets and needs a
   playtest confirmation. Multi-phase
   moves play each phase once through (by clip length, holding the last) instead
   of looping the startup — the per-phase length is the clip's own duration,
   an approximation, since the original's countdown source is unrecovered.
4. **Un-port the melee constants.** Reach and damage move out of `melee_rules.h` and into the
   `WeaponDefinition` recovered by issue #9.
   DONE via the character table rather than the item file (that is where the hits
   live: 300-family phase combat blocks): radius, scaled hpDamage, defenderHitstun
   and startup/active from entry frames. Recovery tail (17) and the attack-sphere
   centre stay port rules, as do the 40/400-family hits.
5. **Re-validate the issue #10 melee tests**, which were written against a punch that does not
   exist.
   DONE: the legacy-swing tests stand as fallback coverage (a table-free fighter
   behaves exactly as before), and new data-driven sections pin the resolved
   moves, sets, reach, damage, stun and windows against rena/00.dat.

## 8. The tool that made this possible

`--anim-player` (`--model=<rig.X> --anim-player [--anim=N]`): one rig, no stage, arrows step
the index, WASD orbits, the set name and index are drawn top-left. It bypasses `matchInput`
deliberately — a clip browser wants raw keys, not the gameplay map where Up is double-tap dash.

This is the instrument for step 3: bound a weapon and step the indices to see the attack set
change with the equipment.