# PSP models → the port's `.X`

How `daybreak --extract-psp` turns a PSP fighter into the files this port draws and
simulates. The PSP data is described in [`README.md`](README.md); the extractor and its file
list are the first half of that command, this is the second.

Everything below is a **port rule** unless it says otherwise. The format facts (chunk
layout, vertex layout, bind matrices) are tier 3 — measurements of the shipped files; the
choices made on top of them are tier 6, provisional, and named as such.

## What it writes

```
psp-data/
  psp/g3d/chrmNN.gmo            raw, as the pack stores it (the motions and skeleton)
  psp/g3d/chrNNk.gmo            raw, costume k of character NN
  psp/g3d/chrtNN.gim            raw, the head pictures
  data/satoshi/00.X             costume 0
  data/satoshi_B/00.X           costume 1, data/<name>_C, _D, ... likewise
  data/satoshi/*.cnv            the textures the model's materials name
```

`data/<name>[_<letter>]/` is the core's own variant convention
(`src/battle/core/character_asset_files.hpp`: the frame table lives in `data/<name>/`, the
model in `data/<name>_<'A'+variant>/`), so costume *k* is written to `data/<name>` for k = 0
and `data/<name>_B`.. for k = 1.., exactly where the character loader looks.

| Fighter | PSP file | Costumes | Bones | Scale |
|---|---|---|---|---|
| Satoshi Houjou | chr17 | `chr170`..`chr174` (5) | 68 | 0.97 |
| Miyoko Tanashi | chr18 | `chr180`..`chr186` (7) | 77 | 0.86 |
| Okonogi | chr19 | `chr190`..`chr192` (3) | 77 | 1.14 |

The scale is the one [`../PSP-CHARACTERS-PLAN.md`](../PSP-CHARACTERS-PLAN.md) chose from the
height table (Okonogi with the grown men, Satoshi between Keiichi and Satoko, Miyoko with the
children).

## Reading the GMO

`tools/asset-tools/gmo_blender.py` is the reference parser for this format — its un-baked
import reproduces the file's raw pose to 0.0018 units — so `src/psp/gmo.cpp` follows it field
for field rather than reading the format a second way. Three details cost a debugging round
each and are worth stating:

* A chunk header is `{u16 type, u16 headerSize, u32 size}`, and **`headerSize` is not always
  the payload offset**. Named chunks (bone, mesh, array, material, texture, motion) carry
  their name between the header and the payload, so payload = offset + headerSize. The
  anonymous leaves (every `0x80xx` type: parent, translate, rotate, blend bones, material
  reference, …) leave `headerSize` at zero and put their values 8 bytes in, right after the
  chunk header.
* A chunk reference uses the **low 12 bits** as an index; the high bits repeat the target
  chunk's type. Every index in the format — palette entries, material references, texture
  references, motion targets — is masked.
* An embedded texture's `0x8013` chunk starts with a dword that is **not** the TGA's length
  (it reads two bytes short in every file). The reference importer ignores it and takes
  everything from 12 bytes into the chunk to its end; so does the writer.

Vertex data is the PSP GE's own layout: weight components, UV, colour, normal, position,
each member aligned to its own size and the stride to the largest
(`GmoModel::vertexLayout`). The character meshes use 1, 3, 7 and 8 `u8` weights — eight
influences on the body — with `f32` positions and UVs and `s8` normals.

The bind pose is the bone hierarchy itself: each bone's `0x8048` translation and `0x804b`
quaternion compose into its local matrix, and the mesh-owning bone's `0x8045` list holds the
matching inverse-bind matrices in the same order as its `0x8044` blend bones. The two agree
to the reference importer's 0.0018 units, which is why the .X frame matrices are the bones'
own locals and the `SkinWeights` offset matrices are the file's, with no transpose and no
re-fit anywhere. Both the GMO and the .X store matrices row-vector (translation in elements
12..14), which is also the form the core's `quaternion_matrix_scalar24` builds.

## The three decisions

### 1. Bone names

The core looks bones up **by name**, and the names it looks for are the PC rigs'. The two it
cannot do without are the ones that throw when missing: `Bip01_R_Hand` and `Bip01_L_Hand`
(`core/projectile_manager_services.hpp`, `core/shoot_native_world.inc.hpp`). Next come
`Bip01_Prop1`/`Bip01_Prop2` for weapon attachment and projectile muzzles, `Bip01_Spine` for
spine yaw, and the `Bip01` **prefix** itself, which is how the core splits a lower-body
animation channel from an upper-body one (`core/actor_sampled_pose.hpp:35`).

The PSP rig's own split says the same thing, so the rename copies the PC rigs rather than
inventing a mapping: measured on `data/keiichi/00.X`, the PC's legs and pelvis are `Bip00_*`
and its spine, arms, hands and props are `Bip01_*`.

| PSP bone | .X bone | | PSP bone | .X bone |
|---|---|---|---|---|
| `root` | `Bip00` | | `spine1` | `Bip01_Spine` |
| `lefthip` | `Bip00_L_Thigh` | | `spine2` | `Bip01_Spine1` |
| `leftknee` | `Bip00_L_Calf` | | `neck` | `Bip01_Neck` |
| `leftfoot` | `Bip00_L_Foot` | | `head` | `Bip01_Head` |
| `lefttoe1` | `Bip00_L_Toe0` | | `leftcollar` | `Bip01_L_Clavicle` |
| `righthip` | `Bip00_R_Thigh` | | `leftshoulder` | `Bip01_L_UpperArm` |
| `rightknee` | `Bip00_R_Calf` | | `leftelbow` | `Bip01_L_Forearm` |
| `rightfoot` | `Bip00_R_Foot` | | `lefthand` | `Bip01_L_Hand` |
| `righttoe1` | `Bip00_R_Toe0` | | `rightcollar` | `Bip01_R_Clavicle` |
| | | | `rightshoulder` | `Bip01_R_UpperArm` |
| | | | `rightelbow` | `Bip01_R_Forearm` |
| | | | `righthand` | `Bip01_R_Hand` |
| | | | `weapon_r` | `Bip01_Prop1` |
| | | | `weapon_l` | `Bip01_Prop2` |

Every other bone keeps its PSP name: `RootNode`, `<name>_all`, `facechange`, `skelton`, the
hair chains (`uphair*`, `downhair*`, `left/rightuphair*`), `tie*`, `clothes*`, the skirt chains,
`left/rightmant*`, `thumb*`, `finger*`, `toe2`, `backribbon*` and `wapon_controll_l/r`. None of
them has a PC counterpart and the core never looks one up by name. The one bone that keeps
neither its name nor a new one is `mesh` — the mesh-owning frame is written **unnamed**, for the
reason in "Two frames-side details" below.

Two consequences worth knowing:

* The upper body lands on core channel 1 and the legs on channel 0, so an upper-body-only
  bind (walking while shooting, `development_animated_combat.hpp`) moves the PSP fighter's
  arms over the walk exactly as it does the PC cast's.
* The fingers, hair and skirt stay on channel 0 even though they hang off channel-1 parents.
  During an upper-body-only bind they hold their last channel-0 pose instead of following the
  hand, which is what the PC rigs do too for their channel-0 chains.

### 2. Take order

The core registers animation sets **in reverse document order**
(`core/battle_actor_assets.hpp`: `for (auto it = roots.rbegin(); …)`) and so does the
renderer's loader (`src/assets/xmodel.h` `finish()`). Both are reproducing `d3dx9_25.dll`,
which prepends each set it creates.

The writer therefore emits **take N-1 first and take 0 last**, so that index *i* in either
reader is PSP take *i*. The DAT frame tables this branch's sibling track writes can then name
a take by index and mean the same thing the PSP means.

`chrmNN.gmo` holds 76 takes each, but many of them animate nothing (23 empty for Satoshi, 37
for Miyoko, 34 for Okonogi: their range is `0..0` and they have no curves). Both readers
**drop a set with no tracks**, which would shift every later index, so an empty take is
written with one constant key on the root bone: it occupies its index and poses the bind.

**Slices after the takes.** A borrowed PC frame table plays one animation set per *phase*, and a
phase is a fraction of a move; a PSP take is the whole move. So the moveset converter plans, per
fighter, which span of which take each phase plays (`docs/psp/COMBAT.md` §3.1), and this writer
appends those spans as extra sets after the 76 takes: `Slice-<i>`, written before the takes and
last slice first, so that in either reader set 76+*i* is slice *i* and sets 0..75 are still exactly
the takes. A slice's keys are the take's own key frames over its span, re-timed to start at 0,
because a set's length is its last key time. The extractor makes the plan once and gives the same
one to both converters; without the PC install there is no plan, and the model carries its 76
takes alone.

### 3. Scale and a half turn, on the root frame

Both are applied to the **root frame's matrix**, as one right multiplication:

```
root local' = root local × F        F = diag(−s, +s, −s, 1)      (row-vector, translation in 12..14)
```

`s` is the fighter's draw scale: **Satoshi 0.97, Miyoko 0.86, Okonogi 1.14**. `F` is a uniform
scale of `s` and a 180° turn about Y; they commute, so one matrix carries both. Because the
root is the parent of every bone, everything below — the drawn mesh *and* every bone-anchored
hit shape — is scaled and turned together. The plan's open question ("whether hit shapes and
movement scale with the drawn model") is answered here as: the geometry does, movement does
not — movement is the combat code's and is untouched.

Two properties make this safe rather than a hack:

* **No motion animates the root.** Measured over all 76 takes of all three motion files: bones
  0 (`RootNode`), 1 (`<name>_all`) and 2 (`mesh`) carry no curves at all, so no animation key
  can overwrite the scaled root. (The writer still applies `F` to the root's animation keys if
  a motion ever does animate it, so the rule cannot silently lapse.)
* **The turn is measured.** The PSP version is authored facing **+Z** and every PC rig faces
  **−Z**. With the model viewer's `--camera=front` (the eye on −Z, the side a PC rig faces) a
  PC fighter looks at the camera and a converted PSP one shows its back; the PSP data says the
  same thing independently — `chr190.gmo`'s face mesh sits at z +9.9 with a mean normal of
  +0.9 in z. Without the turn every PSP fighter fights backwards.

What the scale does *not* do: change the bind pose's proportions (it is uniform), move the feet
off y = 0 (they sit at 0), or touch the weapon models (not converted yet).

## Two frames-side details the core needs

Both were found by running a converted fighter through a whole match, and both are about
matching a PC rig's conventions rather than about the PSP data:

* **The mesh-owning frame is written without a name.** A PC frame table anchors a state's hit
  record on an empty bone name when that state has no hitbox, and the core resolves the name
  through `ActorSkeleton::find`, which answers 0 for a name nothing has. 0 means "missing bone"
  to `snapshot_body_contact_geometry` and it throws inside the tick. The PC rigs answer that
  lookup because they carry unnamed frames (their mesh owners, 24 of Keiichi's 51); the
  converted rig does the same by leaving the `mesh` frame's instance name empty, so the same
  records bind to it and its world transform — the rig's root — is the anchor.
* **An empty take is a two-key hold, not one key.** A set's length is its last key's time, so a
  single key means a zero-length animation, and the row timers that scale a phase to its
  animation's length divide by it. Two keys one 30 Hz frame apart is the one-frame take the PSP
  actually has (`range 0..0`), read at the core's 60 Hz as two frames.

## Animation encoding

Each take becomes one `AnimationSet`; each animated bone becomes one `Animation` with a
reference to the bone and one `AnimationKey` of matrix keys (key type 4, sixteen floats) —
the form both readers accept without a controller quirk.

* **Sampling.** The take's curves (`0x000c`: format, dimensions, key count, then time and
  values per key) are sampled at **every integer frame** of the take's range and written as
  one matrix key each. The low nibble of the curve format is the interpolation: 0 constant
  (stepped, so per-frame sampling is what reproduces it), 1 linear, 4 slerp (shortest arc,
  the reference importer's rule). The files also set high bits (`0x4400`) that no consumer
  reads.
* **Clock.** `AnimTicksPerSecond` is 4800, the PC models' own base, and a key at frame *f* is
  `f * 4800 / fps` ticks (160 at 30 fps). The core divides key times by that number, so a
  take plays at the rate the PSP plays it.
* **Missing channels.** A bone with only a translation curve keeps its bind rotation and vice
  versa; a bone with neither is not written at all, so it holds its bind pose.
* **Scale curves (`0x42`) are skipped.** All of them are on the two `wapon_controll_*` helper
  bones and toggle between 0 and 1; a zero-scale matrix is a degenerate key for both readers,
  nothing is drawn on those bones, and the reference importer leaves them out too.

## Textures

`Material` face colour is white with no power. The PSP's own materials carry a 0.2 ambient
term that belongs to its fixed-function setup; this renderer shades with the diffuse colour,
so keeping 0.2 would draw the fighter five times too dark.

The four materials name the file's own textures. The body is a colour-mapped TGA embedded in
the costume GMO; the face, head and hair are pictures inside `chrtNN.gim`. Both are decoded
to RGBA and written as the port's `.cnv` container in the model's own folder, and the
material names the texture with a `.bmp` suffix because that is what `TextureCache` swaps for
`.cnv` (the PC data ships nothing else).

`chrtNN.gim` holds the ten pictures the model needs **stored twice** (twenty GIM pictures);
the writer reads the container's pictures and picks by material name: `*_face` → picture 0,
`*_hair` → 8, `*_head` → 9 (the eight expressions, then hair, then the scalp with the ear —
the reference importer's `HEAD_PICTURES`, measured on Okonogi). The shipped names disagree on
how many underscores separate the character number from the part (`chr19__face` but
`chr17_face` and `chr186_body`), so the test is on the last part, not on a spelling.

Two GIM rules are easy to get wrong and are explicit in `src/psp/gim.cpp`: a **swizzled**
image (`order == 1`) is stored as 16-byte columns by 8 rows, not as rows; an unswizzled one
has its row pitch padded to the header's alignment.

## What this does not convert

* **Weapons.** `wpn*.gmo` files use an unweighted vertex type no GMO reader in this tree
  handles yet (`0x180011a3`), and the PSP has no `wpn18*` at all: Miyoko's four weapons have
  no model. Weapon props are a later step.
* **Movesets.** `.acs`/`.acv`/`.atp` and the frame tables they become are the sibling track's
  converter (`data/<name>/0W.dat`, `data/item/1NN.dat`). It registers on the extractor's
  converter seam (`src/psp/psp_convert.cpp`) and reads the same `psp-data/psp/` files.
* **Select, VS and result art.** The raw GIMs are collected; turning them into the sheets the
  screens cut is the frontend track's work.
* **Expressions.** The model's four materials are static. Switching the face picture per
  expression at run time needs the texture-remap events the DAT carries, which arrive with
  the frame tables.

## Evidence

| Claim | Tier |
|---|---|
| GMO chunk, bone, mesh, motion and texture layouts | 3 — measured against the shipped files and the repository's reference importer |
| The 0.0018-unit agreement of the reference import | 3 — that importer against the raw values, not against the game |
| Bone names the core looks up, and that a missing hand bone throws | 3 — read in `src/battle/core` |
| PSP rigs face +Z, PC rigs face −Z | 5 — a capture of this build with `--camera=front`, plus the face mesh's normals in the file |
| A converted model draws correctly, textured, at the plan's scale | 5 — captures of all three fighters beside PC Keiichi (`docs/psp/README.md` reproduces the command) |
| Both readers accept every converted file; 76 sets without the install (more, with its slices); every set samples | 4 — `psp_model_test` against the player's own ISO |
| Bone renames, take order, scale on the root, 30 Hz keys | 6 — port rules, chosen so the PC's readers and rig conventions apply unchanged |
| The unnamed mesh frame and the two-key empty take are needed | 5 — a `--match` capture and `tests/psp_match_test` with the converted model: without them the filter throws inside the tick and three of twelve combos never reach a shot row |
