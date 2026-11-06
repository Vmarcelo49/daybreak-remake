# PSP version — data tables

**Evidence:** static reading of the PSP data and the decrypted executable. Tags: **[obs]** means read
out of code or data, **[inf]** means it fits but was not proven, **[open]** means undecided. Readers
for every table (`acs.py`, `acv.py`, `atp.py`, `rowtable.py`) and the per-row dump `rowtable.tsv`
are kept locally under `local-data/harness/psp/`. No game data is reproduced here.

The `.acv` sections are numbered **S1–S4** in file order. Some local notes number them 0–3.

## 1. Common container

```
u32 total_size, u32 block_count (1; 2 only for Natsumi b), then blocks:
    { u32 size_including_this_header, u32 count, payload }   walked by size
```

`.acs` has 1 block of 350 lists, `.atp` has 1 block of 350 records and `.acv` has 4 sections
[obs, parser `FUN_0005d5d4`]. All twelve files of the three new fighters use this standard layout. The
exceptions are Natsumi's `chr16b` (two data slots) and `chr16d` (an old 242-row layout).

## 2. `.acs` — event lists

```
350 × { u32 bytes (= 8 + 8n), u32 n, n × { f32 time (motion frames, 30 fps), u32 code } }
```

List *i* is the script of **handler id** *i* (installed at `f+0xea4+8*hid`). The row → handler map is
mostly the identity, so in practice list *i* ≈ row *i*. Codes decode as family = `(code & 0x7fffffff) >> 24`
[obs, `0x6ae90`]:

| Family | Codes | Effect |
|---|---|---|
| 0 | `0x8000GGNN` (`GG` = 01/02/04/08 group; `NN` = 00 start, ff end, small index) | main register `+0x94b`. Bits `0x400`/`0x800` drive a loop counter; `0x800002xx` advances the animation [obs]; group/index meaning [inf] |
| 0 | `0x01000000`, `0x02000000` | registers 1, 2 off |
| 1, 2 | `0x8100000x`, `0x8200000x` | registers `+0x94c`, `+0x94d` on; they select hit variants (masks `0x400000`/`0x800000`) [inf] |
| 3 | `0x8308xxxx`, `0x830f0000` | **SE/voice** id = `code & 0xffff`, through the fighter's sound table [obs] |
| 4 | `0x8400xxxx` | **effect** id = `code & 0xffff`, spawned at the fighter [obs] |

There are 71 distinct codes over the 76 files. `0x80000401` occurs only in Miyoko's four files.
`0x840000e4` (effect 228, the muzzle flash) occurs only in Okonogi's handgun, 7 times. Both go through
the normal dispatcher.

## 3. `.acv` — four sections

| Section | Shape | Stored at | Role |
|---|---|---|---|
| S1 | 350 × `{bytes, n, n × {f32 time, u32 flags}}` | `f+0x3b4+8*row` | **row program**. `flags & 0xc0000000` and `0xa0000000` set two duration timers; `0x400000`/`0x800000` enable the hit variants; `time == 2e11` triggers a chain query [obs]. Other bits [open] |
| S2 | 350 × `{bytes, n, n × 164-byte record}` | `f+0x1994+8*row` | **timed motion/transition records** (below) |
| S3 | 2 rows: 350 × 16 bytes `{u16×4, f32 0.1, u32 0}`, 350 × u32 | `f+0x2604` | **chain/cancel predicate** queried by `FUN_0007d488` [obs use, open meaning] |
| S4 | 350 × u32 | `f+0x25e0` | **row → handler id** (0..478; `0xffffffff` = row unused) |

### S2 record (0xa4 bytes)

Readers are `FUN_00069824` (time), `FUN_00074148` (transition) and `FUN_0007469c` (motion).
**It is not hit geometry** [obs: these are the only readers of `+0x1994`].

| Offset | Field |
|---|---|
| `+0x00` | f32 time in frames; when passed, the record's window closes |
| `+0x04..+0x0c` | three distance gates (±0.1 dead zone) |
| `+0x14` | block A flags: bit0 no transition, bit1 keep lateral speed, bit2 go to the given row, bit3 invert ground, bit5 do the angle test |
| `+0x18`, `+0x1c` | A gates: distance vs `f[0x939]` and angle vs `f[0x93b]` (π = any) |
| `+0x20..+0x34` | A target values |
| `+0x5c..+0x9b` | block B, same shape plus: `+0x80/+0x84` speed/target while the window is open, `+0x88/+0x8c` while it is shut, `+0x90/+0x94` clamps on `f+0x14`, `+0x98` target while shut, `+0x9c` per-frame vertical additive |
| sentinels | −5000 absent, π any angle, 1e12 / 9.8765e17 never |

`f+0x14`/`f+0x18` are planar velocity, `f+0x30` facing/aim, `f+0x5c` model scale and `f+0x84` animation
advance [inf]. Movement, including jump arcs, is data in these records plus root motion. No code
constant drives it.

## 4. `.atp` — attack records

```
header {total, 1, payload, 350}; 350 × 0x94-byte records; the record for a row is atp[S4[row]]
```

| Offset | Field | PC equivalent / evidence |
|---|---|---|
| `+0x00` f32 | power | PC `combat[0] / 1000` (330 of 459 samples) |
| `+0x04` f32 | | PC `combat[5] / 100` (97% of those) |
| `+0x08` f32 | | PC `combat[6] / 100` (98%) |
| `+0x14` 4×u8 | `{b0, b1, 100, b3}` | b3 = PC `combat[8]` (95%) |
| `+0x18` u32 | hit type (8/9) [inf] | |
| `+0x1c` f32 | 5..35, stun [inf] | |
| `+0x20` f32 | 5..85 [inf] | |
| `+0x24` u32 | attribute bits; `0x400000` picks the B reaction rows | `FUN_0006c4f8` |
| `+0x88` u32 | relation mask {1 enemy, 2 ally, 4 self} | `FUN_0006b32c` |
| `+0x8c` u32 | motion take id inside `chrmNN.gmo` | |
| `+0x90` f32 | power scale (1.0) | `FUN_0006a8cc` |

Rows 340/341 are the shot pseudo-rows. Their records are copied into the fighter
(`+0x6b04/+0x6b98`), but they are **all zero in all 76 files**.

## 5. `bin/chr.fpd` — per-combo `def` (76 × 0x170)

`def(char, weapon) = chr.fpd + (char*4 + weapon)*0x170` [obs, `FUN_0000a818`].

| Offset | Field | Satoshi | Miyoko | Okonogi | Keiichi |
|---|---|---|---|---|---|
| `+0x00` int | base HP | 8500 | 8500 | 11000 | 10000 |
| `+0x04..0x0c` int | three damage thresholds | 850 ×3 | | | |
| `+0x10/14/18` f32 | taken / attack / defence scales | 0.75 / 1.11 / 0.44 | | | |
| `+0x28` / `+0x2c` f32 | damage unit (normal / when `f[0x99d] > 0`) | 1000 / 250 | | | |
| `+0x30` f32 | guard damage fraction | 1 | | | |
| `+0x34` f32 | body scale | 1.03 | 0.94 | 1.11 | 1.00 |
| `+0x38` f32 | hit-stop frames | 40 | | | |
| `+0x3c` f32 | body/hit radius (cm) | 60 | | | |
| `+0x40..0x54` f32 | six attack reaches | 50, 45, 45, 45, 45, 60 | | | |
| `+0x58` f32 | damage multiplier | 1 | | | |
| `+0x5c` int | gauge scale | 1000 | | | |
| `+0x68..0x7c` int | six per-direction reaction values | −17 −24 −27 −20 −20 −5 | −17 −22 −22 −20 −22 −4 | −18 −23 −29 −22 −24 −6 | −17 −22 −27 −20 −23 −6 |

Empty cells repeat the Satoshi value. One world unit is 1 cm: a fighter model is about 150 units tall.

## 6. Bullet tables

| File | Record | Loaded at | Fields |
|---|---|---|---|
| `bin/shot_data.bin` | 330 × 0x14 | `0x18e870` | `+0x00` packed [open], `+0x04` speed, `+0x08/+0x0c` spread angles (±30°/40°/45°), `+0x10` flags, `+0x12` self index |
| `bin/bullet_attack_data.bin` | 764 × 0x9c | `0x190470` | `.atp` record shape; `+0x90` = shot index, `+0x98` effect id, `+0x9a` self index |

Every weapon of the three uses bullet ids 0/1/2 (rows 94/95/96): power 1.75, shot indices
33/33/34, speeds 1/1/2, spread ±40°, effect 57. The weapons differ only in their melee rows.

## 7. Row vocabulary

- **11 rows** have `.acs` content in all 76 combos: 16, 17, 108–110, 172–177.
- **33-row `.atp` core** shared by every weapon: 94–96, 99, 102, 107–110, 112–119, 124–131, 163,
  164, 167, 168, 170, 172, 174, 176.
- Extras for the new three, by handler id:
  - Satoshi a/c: 237 (=286), 259–262
  - Miyoko a–d: 165
  - Okonogi b: 207 (rows 207–223 odd), 227 (227–235 odd)
  - Okonogi d: 226–237, 285
- Aliased rows read their primary's record, e.g. 125→107, 129→108, 115→114.
- Measured PC move id → PSP row: 300→107, 301→109, 302→110, 310→112, 311→114, 320→163, 330→124,
  331→126, 332→167, 340→172, 341→174.

Row meanings, the button bits and the full handler list are in [CODE-MAP](CODE-MAP.md).

## 8. Other shared files

| File | Status |
|---|---|
| `activity/static_param.bin` (732, two sections of 332 + 392) | not decoded |
| `bin/com_param.bin` (18,744) | CPU parameters [inf], not decoded |
| `bin/gauge_data.bin` (912) | no reader found |

## 9. Unknown

- Magazine capacity and reload rates per weapon: they come from an engine weapon record outside these files.
- `.acs` per-code semantics beyond the families.
- S1 bit meanings, S3 meaning, `.atp +0x18/+0x1c/+0x20`.
- `static_param`, `com_param`, `gauge_data`.
