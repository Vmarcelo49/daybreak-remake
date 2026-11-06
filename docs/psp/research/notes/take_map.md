# PC animation set -> PSP motion take: what was measured, and what could not be

Task: the PSP-only fighters borrow a PC combo's recovered code (Satoshi -> Keiichi 0,
Miyoko -> Satoko 0, Okonogi -> Tomitake 0), and that code plays *PC* animation set
indices. A PSP fighter must instead play one of the 76 motion takes of its own
`g3d/chrmNN.gmo`. This note asks whether the two index spaces can be tied together, and
delivers the best table the available evidence supports.

**Answer in one line:** no evidence ties a PC set to a PSP take with identity confidence.
The similarity route (B) was implemented and measured and does **not** pass its own
known-answer test; the decode route (A) did not fall out of the static study, and one
field the earlier notes relied on turned out to be something else (§5). The tables
delivered here are a **duration-first stand-in**, marked `fallback`, and they are
byte-for-byte reproducible with the scripts listed in §8.

Nothing below ran the PSP. Tiers are [obs] (read out of shipped data or the decrypted
image), [inf] (fits, not proven), [open].

---

## 1. Deliverables

| File | What |
|---|---|
| `take_map_keiichi.tsv` | Keiichi 0's 102 referenced sets -> **Satoshi's** `chrm17.gmo` takes |
| `take_map_satoko.tsv` | Satoko 0's 96 referenced sets -> **Miyoko's** `chrm18.gmo` takes |
| `take_map_tomitake.tsv` | Tomitake 0's 103 referenced sets -> **Okonogi's** `chrm19.gmo` takes |
| `take_index_agreement.tsv` | per take index, the same-index distance on three PSP character pairs |

Columns (tab separated, header row):

```
pc_set_index        controller animation set index as it appears in data/<char>/00.dat
pc_set_name         the .X AnimationSet name behind it (the loader stores the array
                    reversed: controller index i is file set N-1-i, §3)
pc_frames           the set's length in PC update frames, ticks/76.8
pc_states_using_it  the PC move ids (00.dat state ids) whose phases name that set
psp_take_index      the PSP motion take index written into the table
psp_take_name       its GMO motion chunk name ("Take 001-00NN")
psp_frames          its length in PSP motion frames (30 per second)
score               0..1, see §6; higher is better
method              "A decoded" | "B similarity" | "fallback" -- every row here is "fallback"
pc_seconds          the set's length in seconds (ticks/4800, the .X tick rate)
psp_seconds         the take's length in seconds (frames/30)
score_duration      duration term of the score
score_spread        per-bone motion-spread term
score_shape         joint-angle shape term
same_person_take_index   what the same rule picks on the dispatch character's own PSP model
                         (chrm02/chrm05a/chrm10), as a cross-check
same_person_agrees  1 when both models pick the same take
confidence          medium | low-medium | low (from the two columns above, §6)
```

## 2. Coverage

Every animation set the weapon-0 frame table references is covered; there is no gap.

| dispatch | 00.dat | sets referenced | usable takes in the target model |
|---|---|---|---|
| Keiichi 0 | `data/keiichi/00.dat`, 125 states | 102 | 53 of 76 (`chrm17.gmo`) |
| Satoko 0 | `data/satoko/00.dat`, 125 states | 96 | 39 of 76 (`chrm18.gmo`) |
| Tomitake 0 | `data/tomitake/00.dat`, 125 states | 103 | 42 of 76 (`chrm19.gmo`) |

"Usable" = the take has rotation curves on at least 15 of the mapped bones and a non-zero
range. The other takes are the `Dummy` slots (their names say so); a `Dummy` take has no
curves at all, so it cannot be played.

The PSP models were picked as the *target* (Satoshi/Miyoko/Okonogi) rather than the
same-person model, so the table needs no assumption about a shared take vocabulary. §4
measures that assumption anyway.

## 3. The PC side: index -> file set

`data/<char>/00.dat`: `{magic, model[260], 6 params, states}` and each state is
`{id, a, b, phases}` with each phase `{set, frames}` — the same layout the core's
`actor_frame_data.hpp` reads [obs]. Confirmed on all three files: state 0 names set 0,
state 10 names set 1, state 300 names set 31 for Keiichi.

The loader reverses the `.X` animation array (`docs/ANIMATION-SETS.md` §1), so controller
index *i* is file set *N-1-i* with N = 124 sets in each of the three models. Sanity check
that the reversal is the right way round: Keiichi controller 0 is the long idle and lands
on file set `Anim-124` (80 keys, 82.3 frames), controller 1 is walk on `Anim-123`
(34 keys, 34.4 frames) [obs + doc].

## 4. Does take index *i* mean the same move on another PSP character?

Measured, not assumed, and it is the one thing this study can answer positively.
Method: joint positions from forward kinematics, expressed in a frame built from the two
hip joints and the hips->neck axis and scaled by hips->neck, sampled at 16 normalised
times; the distance is the weighted mean joint displacement. Bone roll, rest pose and
body scale all cancel. `scripts/take_index_check.py`.

| pair | takes with curves in both | same index is the best match | median same-index distance |
|---|---|---|---|
| chrm02 (Keiichi) vs chrm17 (Satoshi) | 40 | **31 (78%)** | 0.170 |
| chrm05a (Satoko) vs chrm18 (Miyoko) | 37 | **24 (65%)** | 0.312 |
| chrm10 (Tomitake) vs chrm19 (Okonogi) | 39 | **14 (36%)** | 0.562 |

Chance would be about 1/40 = 2.5%. With the joint-angle variant of the same test
(`--mode angle`) the counts are 29, 24 and 14, and 20, 18 and 11 takes respectively agree
within 0.05. So: **the take index carries the move identity for a clear majority of the
populated slots, but not for all of them** — the `Dummy` positions differ per character
and some populated slots hold character-specific motions. [obs]

Consequence for the port: a table built against the same-person model can be reused on
the target model with roughly the accuracy of that table, and a table built directly
against the target is strictly better. This deliverable builds directly against the
target; the same-person result is carried as `same_person_take_index` for comparison.
It agrees on 62/102, 69/96 and 49/103 rows — the disagreement is mostly duration
availability (chrm17 has 53 usable takes, chrm02 only 40).

## 5. Route A (decode the PSP's row -> motion mapping): not cracked

What the earlier corpus says, and what re-reading the decompiled functions changed:

| Address | Earlier reading | What the code shows now |
|---|---|---|
| `FUN_0006dd40` / `+0x2486` | "motion selection", `+0x2486` = current motion id (`fighter.md`) | `+0x2486` receives `param_1[0x955]` or `param_1[0x956]`, and `FUN_0006e8dc` stores the *player index* in those words (`piVar1[0x956] = (**(*param_1+0x40))()`), while `[0x957]/[0x958]` carry the **row** it passes to `setRow` (guarded by `0x15d < row`). So `+0x2486` is a player index, not a motion id. [obs, `decomp/0006dd40.c`, `decomp/0006e8dc.c`] |
| `FUN_0001a228` | "row -> motion table" | It walks a per-character record list `DAT_0018e650[char]` of 0xc-byte entries and matches `*(short*)(entry+8)` against an **effect** id (0x212..0x241 with per-id helper calls), filtered by a bitmask of `entry[6] >> param_2`. This is the effect record lookup, not motions. [obs, `decomp/0001a228.c`] |
| `.atp +0x8c` | "motion take id inside chrmNN.gmo" | Over the 20 dumped `.atp` files: 715 non-zero rows, values `181..186, 200..203, 215, 237`, with 237 on 324 of them. That vocabulary is far too small for a 76-slot take table and 237 cannot be a take index. Its role is [open]. |
| the current take index | -- | No field in `Fighter` was found that is consumed as a GMO take index. The model side (the class behind `FUN_00137710`, the bone-matrix getter) was not located as an animation player in the time available. |

So route A needs one more specific thing: the model-side call that turns "play motion X"
into a take index, i.e. the function that reads the GMO's motion list with an index. The
Fighter's `+0x18d5` sub-object (`FUN_000849a8`, `FUN_00086d40`, `FUN_00085e0c`) is the
most likely place to start; it was not read.

## 6. Route B (motion similarity): implemented, measured, and it does not hold

Four feature families were built on both rigs and scored against each other
(`scripts/takecore.py`, `scripts/match_takes.py`):

| feature | what it is | why it is rig-safe |
|---|---|---|
| `local` | local rotation delta from the rig's own bind pose | cancels the rest pose (PC A-pose vs PSP T-pose) |
| `global` | character-space rotation delta from bind (FK) | also cancels bone roll |
| `angle` | joint angles (knee, elbow, hip, shoulder, ankle, neck) from FK positions | scale- and roll-free |
| `pos` | joint positions in a hips-built body frame | scale- and roll-free |
| `var` / `shape` / `spread` | rotation magnitude since the clip's own first/mean sample; per-bone motion spread | invariant to any constant per-bone basis change |

Bone correspondence: `Bip00_Pelvis->spine1, Bip01_Spine->spine2, Bip01_Neck->neck,
Bip01_Head->head, Bip01_L/R_Clavicle->left/rightcollar, Bip01_L/R_UpperArm->left/rightshoulder,
Bip01_L/R_Forearm->left/rightelbow, Bip01_L/R_Hand->left/righthand,
Bip00_L/R_Thigh->left/righthip, Bip00_L/R_Calf->left/rightknee, Bip00_L/R_Foot->left/rightfoot`.

**Known-answer test.** Sets 0, 1, 2..5, 13..15 and 25..29 are reachable from states whose
meaning is the same in all three dispatch characters (state 0 idle, 10 walk, 40/41/42 jump,
20 dash, 23..28 dashes/reactions; `00.dat` names the set for every one of them), and §4
shows the take vocabulary is mostly shared. A metric that identifies *moves* must
therefore pick the same take index for the same set in all three characters.

Measured, candidates restricted to the takes all three same-person models populate, with
the shape/spread/duration weighting 0.45/0.35/0.20 (`scripts/match_takes.py`,
`scripts/build_take_map.py` internals):

| sets | Keiichi | Satoko | Tomitake | agreement |
|---|---|---|---|---|
| 0 (idle) | t13 | t13 | t06 | 2 of 3 |
| 1 (walk) | t04 | t12 | t32 | none |
| 3 (jump up 2) | t05 | t05 | t13 | 2 of 3 |
| 5 (jump down) | t12 | t12 | t12 | **all 3** |
| 13 (dash start) | t08 | t08 | t12 | 2 of 3 |
| 14 (dash loop) | t08 | t08 | t32 | 2 of 3 |
| 26, 27 (hit) | t07 / t07 | t02 / t07 | t07 / t25 | 2 of 3 |
| 28 (knockdown) | t30 | t36 | t36 | 2 of 3 |
| 2, 25, 29 | -- | -- | -- | none |

Of the 12 shared base sets, one maps to the same take in all three characters and seven
more in two of three. Across all 104 rows the three characters share, the mean gap
between the best and second-best candidate is **0.027 on a 0..1 score** — the ranking is
flat — and 44/104 rows have at least one agreeing pair (two independent draws from ~33
takes collide 3% of the time). That is not a mapping, so no row of this deliverable is
labelled `B similarity`.

One observation, not a validation: in the *delivered* tables (candidates = the target
model's own takes, §7) walk lands on take 22 for all three characters, and the same-person
cross-check also picks 22 for Keiichi and Satoko. One row out of 301 does not carry a
table, but it is the first thing to look at on screen.

**Why the two sides cannot be compared clip-for-clip** — a structural reason, measured:

| | median length | range |
|---|---|---|
| PC set (per phase) | **0.25 s** | 0.00 - 1.82 s |
| PSP take (whole move) | **1.00 s** | 0.30 - 3.10 s |

55-60% of the PC sets the borrowed code can play are *shorter than the shortest usable
PSP take*. A PC animation set is a *phase* of a move; a PSP take is the whole move. The
two index spaces do not have a common unit, which is exactly why every per-set similarity
score is flat. [obs]

## 7. What the tables therefore are

A deterministic stand-in, `method = fallback`, with three cues:

```
score = 0.60 * duration + 0.25 * spread + 0.15 * shape
duration = max(0, 1 - |log2(take_seconds / set_seconds)| / 2)     # length agreement
spread   = (1 + cos(per-bone motion spread)) / 2                    # which joints move
shape    = (1 + corr(mean-removed joint-angle trajectories)) / 2
```

Duration dominates because it is the only cue with a *recovered mechanism* behind it: the
phase advances when its tick counter passes the set's own length (`COMBAT.md` §3.1,
`FUN_0041f580`), so a take whose length disagrees with the phase's will cut the pose off
or hold it. `spread` then keeps a leg-heavy set off a take that only moves an arm.

`confidence` is `medium` when the same-person model agrees *and* the duration term is at
least 0.9, `low-medium` when only the duration term is at least 0.9, `low` otherwise.
Distribution over the 301 rows: **70 medium, 65 low-medium, 166 low**. Score
distribution: mean 0.66, 54 rows above 0.9, 100 below 0.5 — the low half is dominated by
the 166 sets shorter than 0.3 s, for which no PSP take is long enough to match (§6).

Rows worth eyeballing on the first integration, because they are the ones the metric
agrees on most strongly and the move is known on both sides:

| move | PC state | set | take | seconds |
|---|---|---|---|---|
| idle | 0 | 0 (`Anim-124`) | Keiichi 26, Satoko 11, Tomitake 13 | 1.32 s -> 1.33 / 1.07 / 1.63 |
| walk | 10 | 1 (`Anim-123`) | **22 in all three** | 0.55 s -> 0.57 / 0.60 / 0.60 |
| jump down | 42 | 5 (`Anim-119`) | 14, 14, 37 | 0.50 s -> 0.50 / 0.50 / 0.50 |
| dash loop | 20 (phase 2) | 14 (`Anim-110`) | 8 (Keiichi), 25 (Satoko), 8 (Tomitake) | 0.33 s -> 0.33 |

Walk landing on the same take (22) in all three characters, with the same-person
cross-check also picking 22 for Keiichi and Satoko, is the strongest single row in the
tables. It is still one row.

**A better shape for the port, if this is to be done properly:** map at the *move* level
(`00.dat` state id -> take) and give every phase of that move the same take, because a
take spans a whole move. The per-set tables here exist because that is what was asked
for; a move-level table would remove the granularity mismatch that makes §6 flat.

## 8. Reproducing

```bash
cd local-data/harness/psp/scripts             # paths are resolved from this directory
python3 build_take_map.py                     # writes ../notes/take_map_*.tsv
python3 take_index_check.py --mode pos        # writes ../notes/take_index_agreement.tsv
python3 take_index_check.py --mode angle
python3 match_takes.py keiichi --mode global --sets 0,1,2,5,13   # ad-hoc ranking
```

Readers added (all read shipped data only, no game binary):
`xanim.py` (binary `.X` object tree, frames, animation sets, ticks),
`pc_frametable.py` (`data/<char>/NN.dat` states -> phases -> set),
`takecore.py` (skeletons, FK, the feature families and the metric),
`take_index_check.py`, `build_take_map.py`, `match_takes.py`.
They reuse the existing `xdump.py` tokenizer and `gmo.py` (which wraps
`tools/asset-tools/gmo_blender.py`) rather than adding a second parser.

## 9. Open, in the order that would change the answer most

1. **The PSP model's motion API.** One function that consumes a take index would replace
   this entire note with an exact map. Start at the `+0x18d5` sub-object
   (`FUN_000849a8` / `FUN_00086d40` / `FUN_00085e0c`) and the class behind
   `FUN_00137710`.
2. **What `.atp +0x8c` is.** Its vocabulary is 181..186, 200..203, 215, 237 over 715 rows;
   if it is a move id, one anchor take would decode the whole table.
3. **Whether the PSP animations are retargets of the PC ones at all.** If they are
   independent re-authoring, no geometric method will ever link them and only route A can.
4. **A move-level PC table.** Needed for the port regardless of how the take mapping is
   decided (§7).
