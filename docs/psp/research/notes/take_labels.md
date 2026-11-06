# What each PSP motion take is: labels, method, and what is still open

Task: say what every take in `g3d/chrm17.gmo` (Satoshi), `chrm18.gmo` (Miyoko),
`chrm19.gmo` (Okonogi) and `chrm02.gmo` (Keiichi, the cross-check) *is*, from rendered
filmstrips plus numbers read out of the files. Nothing here ran the PSP: every claim is
either read out of shipped data [obs] or inferred from the render [inf]. The deliverable
is `notes/take_labels.tsv`; the sheets are `takes/<rig>_sheet<N>.png`.

**Answer in one line:** takes 0-15 form a shared block whose meaning is solid (jump,
bow, crouch, knockdown/getup, launched knockdown, down, turn, face-down knockdown, swing,
run, getup, idle, walk/run cycles), the lateral and air takes are readable, and roughly a
third of the takes per rig - mostly short in-place upper-body gestures from index 24 up -
can only be described by what they look like, not named as a move.

---

## 1. Deliverable

`notes/take_labels.tsv`, tab separated, one row per motion chunk, all 76 per rig:

```
fighter      17 | 18 | 19 | 02
take_index   0-based position in the GMO's motion list (the "00NN" in the chunk name
             is NOT the index: take 0 is named "Take 001" and take 1 is "Take 001-0000")
take_name    the chunk's own name
frames       motion frame range, end - start + 1, at 30 fps
root_dx      total root translation over the take, model units
root_dy      +Y is up, so this is the vertical displacement
root_dz      +Z is the model's forward, so this is forward/back
label        what the take is
confidence   high | medium | low-medium | low
notes        the observation behind the label
```

`root_*` is the last frame's `root` bone position minus the first, measured on the posed
rig in model space (`scripts/measure_takes.py`). It is **not** read off the raw curve:
`chrm18`/`chrm19` rotate the root's parent chain, so their curve values are in a rotated
bone frame (chrm18 take 0's curve moves 13 units on Y while the character actually rises
132). `notes/take_root_motion.tsv` keeps the raw curve numbers for comparison, and its
`dx/dy/dz` columns are in that bone frame - do not read them as model axes.

Non-dummy takes, by confidence:

| fighter | non-dummy | high | medium | low-medium | low |
|---|---|---|---|---|---|
| 17 Satoshi | 53 | 16 | 17 | 1 | 19 |
| 18 Miyoko | 39 | 7 | 13 | 3 | 16 |
| 19 Okonogi | 42 | 7 | 12 | 5 | 18 |
| 02 Keiichi | 40 | 7 | 12 | 3 | 18 |

All 23/37/34/36 dummy takes are labelled `dummy (no curves)` with high confidence: their
motion chunk has no bindings at all, so nothing can play them.

## 2. How the numbers were made

`scripts/take_inventory.py` reads the raw motion chunks; `scripts/measure_takes.py` builds
each take's action with the repository importer (`tools/asset-tools/gmo_blender.py`), steps
every frame, and records the posed root, both feet, the head, torso pitch, hand travel and
airborne frames; `scripts/render_takes.py` renders six evenly spaced frames per take at
320x400 in a fixed orthographic right-profile window (file +Z forward points to image
right, +Y up, ground filled below y=0, height ticks every 50 units, a thin line at z=0);
`scripts/make_sheets.py` cuts them to 160x200 and assembles labelled contact sheets;
`scripts/detail_takes.py` re-renders a few takes at 240x300 with 8-12 frames when six were
not enough.

Axes were measured, not assumed: the toe bone lies at +Z of the foot bone (so +Z is
forward), the root sits at y~78 (so +Y is up), and `lefthand` is at +X (so +X is the
character's left).

## 3. The shared block, indices 0-15

The four rigs carry the same first block in the same order. A pose-signature check
(`scripts/index_agreement.py`, using the rig-agnostic body-frame joint positions from
`takecore.py`) finds every measured rig pair agreeing at indices 0-12, and 49.1% of
(pair, index) rows over all 76 indices put the same index first. So the first block's
labels rest on four rigs; from index 13 up each rig is judged on its own.

| idx | label | confidence |
|---|---|---|
| 0 | jump (crouch, rise, apex, fall, land) | high |
| 1 | bow / deep forward bend | medium |
| 2 | crouch (deep squat) | medium |
| 3 | knockdown -> down -> getup (kip-up) | high |
| 4 | duck / quick dodge | medium |
| 5 | knockdown: launched backward, lands on back | high |
| 6 | fall and stay down (KO / down state) | medium |
| 7 | knockdown to knees / sit | medium |
| 8 | turn 180 in place (direction change) | high |
| 9 | knockdown face-down with long backward slide | high |
| 10 | melee swing (light attack, in place) | medium |
| 11 | run cycle (in place) | medium |
| 12 | getup (from lying) | high |
| 13 | idle / stand (held still pose) | high |
| 14 | run cycle (fast, 16 frames) | medium |
| 15 | walk cycle | medium |

Take 8 is the clearest single measurement in the set: 11 frames, no root travel, and the
root bone's own rotation goes through a full 180 degrees.

## 4. The label vocabulary, and the movement basics

Labels are a controlled vocabulary of 32 strings so the table can be counted. The largest
one is `in-place motion, unidentified` (39 takes): short takes whose arms and torso move
while the feet stay planted. Naming those as moves needs the state machine that plays
them, which this study did not recover; the notes column says what is visible.

Movement basics per fighter, by take index:

| | 17 Satoshi | 18 Miyoko | 19 Okonogi | 02 Keiichi |
|---|---|---|---|---|
| idle / stand | 13 | 13 | 13 | 13 |
| walk cycle | 15 | 15 | 15 | 15 |
| run cycle | 11, 14, 17, 18, 20 | 11, 14, 20 | 11, 14, 20 | 11, 14, 20 |
| stop / brake from run | 19 | - | - | 19 |
| jump (full arc) | 0 | 0 | 0 | 0 |
| jump / leap pose | 16 | 16, 17, 18 | - | 16, 17, 18 |
| air idle | - | 32 | 49 | - |
| air fall / dive | 22 | 22 | 22 | 22 |
| air attack (jump kick) | 33, 34, 51 | - | 33 | 33, 34 |
| turn 180 | 8 | 8 | 8 | 8 |
| duck / dodge | 4 | 4 | 4 | 4 |
| crouch | 2 | 2 | 2 | 2 |
| dash / lunge forward | 25 | 25 | 25 | 25 |
| side step / flip (lateral) | 32 | - | 47, 48 | - |
| melee swing | 10 | 10 | 10 | 10 |
| melee lunge / thrust | 26 | - | 26 | 26 |
| knockdown + down + getup | 3 | 3 | 3 | 3 |
| knockdown (launched, on back) | 5 | 5 | 5 | 5 |
| knockdown (face down, slides) | 9 | 9 | 9 | 9 |
| knockdown (to knees/sit) | 7 | 7 | 7 | 7 |
| down / KO candidate | 6 | 6 | 6 | 6 |
| getup | 12 | 12 | 12 | 12 |
| hit reaction (flail) | 28 | - | - | 28 |
| taunt / gesture | 24, 35 | 26 | - | 24 |
| upper-body pose (legs static) | 48 | - | - | 48 |
| static placeholder | 52-60 | - | - | - |
| dive / roll and get up | 29 | 30 | - | - |
| drift back and rise | 27, 28 | 35, 45 | 27, 28, 36 | 27, 36 |

Guard, victory/intro/hypermode and a light hit flinch do not appear in this table because
they were not identified (see below).

## 5. What the labels cannot say, honestly

- **Guard is not identified.** No take is a held two-handed guard that can be separated
  from a taunt or a cast pose by eye. Candidates are the in-place upper-body holds
  (Satoshi 36/38/45/48, Miyoko 31/34/36, Okonogi 24/30/31, Keiichi 24/30/45), all `low`.
- **Victory / intro / hypermode is not identified.** Satoshi 43 (111 frames) and 41 (71),
  Miyoko 43, Okonogi 43, Keiichi 43 are long in-place sequences and are the best
  candidates, but a taunt and a victory pose look alike at this sampling.
- **Walk forward vs backward is not decidable from the file.** The locomotion takes are
  in-place cycles (zero net root travel); the game rotates the model, so one cycle serves
  every direction. Only the takes with real root travel name a direction: Satoshi 32 and
  Okonogi 47/48 travel on X (side dash), Okonogi 25 travels +55 on Z (forward lunge).
- **Light vs heavy hit reactions are not separated.** The knockdowns (5, 6, 7, 9) are
  clear; a short flinch was not isolated, and Satoshi/Keiichi 28 is labelled from its
  numbers (fastest hand travel in the table) rather than from a clean read.
- **Which of 5 and 6 is the KO** is a guess from shape (5 starts already recoiling, 6
  starts standing and stays down); both end on the ground.
- 19 of Satoshi's 53 takes, 16 of Miyoko's, 18 of Okonogi's and 18 of Keiichi's are `low`:
  short in-place takes whose arms and torso move while the feet stay planted; they carry
  the label `in-place motion, unidentified`. Naming them as moves would need the state
  machine that plays them, which this study did not recover.
- Satoshi 52-60 are nine **identical** static takes: every curve equal, 31 frames, no root
  curve. They are placeholders, not moves.

## 6. Cross-check against Keiichi

`chrm02` (Keiichi, 68 bones like Satoshi) is rendered as four sheets. Indices 0-15 read
the same as on the other three rigs, which is the check the labels lean on. The
similarity study that would have tied PC animation sets to these takes failed its own
known-answer test earlier (`notes/take_map.md`), so no PC move name is asserted here for
any PSP take.

## 7. Files

| File | What |
|---|---|
| `notes/take_labels.tsv` | the deliverable: label + confidence + numbers per take |
| `takes/chrm17_sheet1-5.png` | Satoshi filmstrips, 12 takes per sheet |
| `takes/chrm18_sheet1-4.png` | Miyoko |
| `takes/chrm19_sheet1-4.png` | Okonogi |
| `takes/chrm02_sheet1-4.png` | Keiichi, the cross-check |
| `takes/detail_*.png` | close-ups of takes that six frames did not settle |
| `takes/frames/<rig>/*.png` | every rendered frame, 320x400 |
| `notes/take_profile_<rig>.tsv` | per-take pose numbers (root, feet, pitch, hands, air) |
| `notes/take_root_motion.tsv` | raw curve values per take, in the bone frame |
| `notes/take_index_agreement_psp.tsv` | per (pair, index) pose distance and best match |
| `scripts/{take_inventory,measure_takes,render_takes,make_sheets,detail_takes,index_agreement,write_labels}.py` | reproduce the above |
