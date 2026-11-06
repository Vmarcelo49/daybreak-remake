# Combat: hit geometry, bullets, input, movement and damage (PSP *Higurashi Daybreak Portable*)

Follow-up to [`fighter.md`](fighter.md) §10 ("what remains unknown"). Same method: **static reading only**
of `local-data/harness/psp/EBOOT.dec` (sha256 `80363ff7…94608597`, vaddr = file offset − 0xc0) and of the
game data extracted to `local-data/harness/psp/dump/`. **No emulation, no runtime instrumentation.**

Every statement is tagged:

* **[obs]** — read directly out of the decrypted image or the data files, with the address / offset quoted.
* **[inf]** — a reading that fits code *and* data but was not proven (no test distinguishes it yet).
* **[open]** — I could not decide; carried to §10.

New helper this study added: `scripts/scan_imm.py` (finds every load/store/immediate in `.text` that
references a given small constant — this is how the readers/writers of a struct offset were all found),
plus `~/tools/psp/scripts/Probe.java` (Ghidra: decompile-by-address / print xrefs, for functions the
earlier `DumpAll` run missed because Ghidra had not created them).

**Units.** The character GMO bounding box is ~150 wide × 149.5 tall (`x −59.49…+59.49`, `y …149.5`) ⇒
**1 world unit = 1 cm**, one fighter ≈ 1.5 m tall. [obs: `dump/g3d/chr170.gmo` chunks 0x8014/0x8016]

---

## 0. Corrections to `fighter.md`

These change how a port must read the data; everything else in `fighter.md` still stands.

| # | `fighter.md` said | Actual | Evidence |
|---|---|---|---|
| 1 | §5.3 "`FUN_000617dc(f,row)` = `+0x25e4 + row*0x94` plus special cases" | **The `.atp` index is the row's *handler id*, not the row**, whenever `map[row] < 350`: `uVar2 = f[0x25e0][row]; return f[0x25e4] + uVar2*0x94`. Only when `map[row] ≥ 350` is the row itself used. The embedded shot copies are selected by the *row* (0x154/0x155) because the row is what is compared. | `000617dc.c`; equivalently rows that alias (e.g. chr17a row 125 → hid 107) must read `atp[107]`. |
| 2 | §1.3 "`+0x996` = data slot 0/1" | `+0x996` (`+0x2658`) is the **hypermode/gauge level** (`0`…, `FUN_0006171c` = "level ≥ 2", ×3 damage multipliers at level ≥2). The data slot is `+0x95b` (`+0x256c`), compared in `FUN_00063634`. | `00063634.c`, `0006171c.c`, `000690ec.c:57` |
| 3 | §1.1 `+0x945` "def reached through `f->[0x945]`… where loaded not traced" | **`def` = `bin/chr.fpd[(char*4 + weapon) * 0x170]`** — `FUN_0000a818(char,weapon) = (char*4+weapon)*0x170 + DAT_00375f84`. `chr.fpd` is exactly 27 968 = 76 × 0x170 bytes, no header. `+0x2514` is set from `f[0x2518 + slot*4]` by `FUN_00063634`. Full field map in §2/§7. | `0000a818.c`, `00063634.c`, `dump/bin/chr.fpd` |
| 4 | §10.12 "costume table `0x1b3060`: the other 12 bytes not decoded" | Each 16-byte entry is `{char* gmo; u8 bone[12]}` = **twelve bone indices**, and they are the hurt/attach bone map (hip, head, neck, both weapon-control bones, both feet, facechange…). See §2. | `0006a8cc.c`, `00061264…00061294`, `00061d40` |
| 5 | §3.4 "94/95 = run" | Rows 94/95/96 are the **projectile rows**: their handlers spawn bullet ids 0/1/2 (`FUN_00070c58/00070bec/00070b88`). `FUN_0006f884` does select row `0x5e`/`0x5f` (= 94/95) but under a *counter* gate, not a stick gate — see §5.4. | `0006f884.c`, `00070c58.c`, `00070bec.c`, `00070b88.c` |
| 6 | §3.4 "340/341 = shot pseudo-rows" | True structurally (handler `0x79190` → `FUN_000790c4`), but **every one of the 76 `.atp` files has rows 340/341 all-zero**, so `FUN_000790c4` always fires bullet id 0. The real per-weapon projectiles are rows 94/95/96 (ids 0/1/2) and the 0x33 throw rows. | measured over all 76 `.atp` |

---

## 1. Hit geometry

### 1.1 Who consumes `.acv` section 2 (the 164-byte records)

The records are **not** stored as an array the code indexes by row arithmetic at the use site: `setRow`
installs a *descriptor pointer* and three readers go through it. [obs, `scan_imm.py 0x1994 0x1998`]

| Where | What |
|---|---|
| `FUN_0005d5d4` (`0x5d684`, `0x5d6ac`, `0x5d548`) | the parser: writes `f[0x1994+8*row] = {count, ptr}` (words `+0x9cb…` in row units = byte `+0x1994`, `+0x1998`) |
| `FUN_000654ac` (`0x65600`, `0x6560c`) | `setRow` installs `f[0x961] (+0x2584) = &f[0x1994+8*row]` |
| **`FUN_00069824`** (`+0x963`→`+0x258c`… cursor `+0x964`) | the **time stepper**: `rec = desc[1] + cursor*0xa4`; if `rec.time <= f[0x950]` → `cursor++` and `f[0x953] &= ~8` |
| **`FUN_00074148`** | **row/cancel decision** from the current record (fields `+0x14` flags, `+0x04/0x08/0x0c`, `+0x18/0x1c`) |
| **`FUN_0007469c`** | **motion / velocity application** from the current record (call `FUN_0007469c(f)` is the last step of the generic runner `FUN_00077cd8`) |

There is **no fourth reader**: `0x1994` appears in exactly 5 instructions in the whole image, all listed
above. So the record's role is (a) *when* a hit window is open, (b) *row transition / cancel* predicates,
(c) *movement/velocity*, and it does **not** carry the hit volume's shape — see §1.3.

### 1.2 The 164-byte (0xa4) record, field by field

Measured layout from `chr17a` row 31 (2 records) + every field the three consumers read. Two *identical
18-word blocks* follow a 5-word head, then a 3-word tail:

```
+0x00 f32 time              motion frames; compared with f[0x950] (row timer)   [obs 69824]
+0x04 f32 rangeA0           distance gate, ±0.1 deadzone (DAT_001c2688/68c)     [obs 74148]
+0x08 f32 rangeA1           second distance gate (0 ⇒ unused)                   [obs 74148]
+0x0c f32 rangeA2           third distance gate                                [obs 74148]
+0x10 f32                  (read only as "!= -5000" ⇒ "parse this block")      [obs 7469c]
--- block A: +0x14 …+0x53  ----------------------------------------------------
+0x14 u32 A.flags           bit0 = "no transition"; bit2 = "go to param_4";
                            bit3 = invert the ground arg; bit5 = "do the angle test";
                            bit1 = "don't touch the lateral speed"
+0x18 f32 A.t1              gate vs f[0x939] (π = "any")                         [obs 74148/7469c]
+0x1c f32 A.ang             angle gate vs f[0x93b] (π = any; <π = ±tolerance)     [obs 7469c]
+0x20 f32 A.v0              target value for f[+0x14]  (or A.t1 if nonzero & window shut)
+0x24 f32 A.v1
+0x28 f32 A.v2
+0x2c f32 A.v3
+0x30 f32 A.v4
+0x34 f32 A.v5
+0x38…+0x4c                 unused / zero in every sampled record
+0x50 f32                   −5000 sentinel = "absent"
+0x54 f32
+0x58 f32                   −5000 sentinel
--- block B: +0x5c …+0x9b (same shape) -----------------------------------------
+0x5c u32 B.flags           same bit meanings as A.flags (seen: 1, 0x1200, 0x13301, 0x500, 0x610…)
+0x60 f32 B.t1              gate vs f[0x939]; 0 ⇒ threshold 1.0
+0x64 f32 B.ang             angle gate vs f[0x93b]
+0x68 f32 B.v0
+0x6c f32 B.v1
+0x70 f32 B.v2
+0x74 f32 B.v3
+0x78 f32 B.v4
+0x7c f32 B.v5
+0x80 u32 B.v6
+0x84 f32 B.v7
+0x88 u32 B.v8
+0x8c f32 B.v9
+0x90 f32 B.clampLo         lower clamp for f[+0x14]
+0x94 f32 B.clampHi         upper clamp for f[+0x14]
+0x98 f32 B.target          target for f[+0x14] while the hit window is *shut*
+0x9c f32 B.add             per-frame additive to f[+0x18] when airborne
+0xa0 f32 B.sentinel        −5000 in every sampled record
```

Sentinels seen in the data [obs]: `-5000.0` (`0xc59c4000`) = "empty", `π` (`0x40490fdb`) = "any angle",
`1e12` (`0x5368d4a5`) = "never", `9.8765e17` (`0x5d5b4da6`) = "never" (list terminator, also in `.acv` S1).

`f[0x939..0x93b]` (words 0x939/0x93a/0x93b, bytes `+0x24e4/8/c`) are recomputed **every tick** by
`FUN_000674f4`: with `p = FUN_0000a4e8(engine, playerIndex)` (the per-player object),
`v = p->pos(+8) − f->pos(+8)`, then `f[0x939] = length(v)`, `(f[0x93a], f[0x93b]) = FUN_000f7968(v)`
(two angles/derived values — **[open]**, exact pair not decoded). So the two gates in A/B are *distance to
the player object* and *angle to it*; their effect is "use block A instead of block B" (i.e. per-record
variants selected by viewer-relative geometry) **[inf]**.

Observed effect of the gates on motion — `FUN_0007469c` (all [obs] reads, [inf] meaning):

```
b = current record
useB = (b+0x5c != 0) && ( b.t1 >= (b.t1>0 ? f[0x939] : 1.0) )
              && ( b+0x68 > 0 ) && ( b+0x68 >= π || |f[+0x30] − f[0x93b]| <= b+0x68 )
blk  = useB ? b+0x5c : b+0x14
windowOpen = (f[0x953] & 8) != 0           // cleared by FUN_00069824 when a record's time passes
if (!windowOpen && b+0x98 != -5000) v14 = b+0x98
if (blk gate ok) {
    spd = windowOpen ? b+0x80 : b+0x88        // (u32 read as float)
    tgt = windowOpen ? b+0x84 : b+0x8c
    f+0x30           = approach(f+0x30, f[0x93b], tgt)     // FUN_000f6f24 = move-toward-by
    if (!(blk.flags & 2)) { f+0x14 = approach(f+0x14, f[0x93a], spd); f+0x18 = approach(f+0x18, f[0x93b], tgt) }
}
f+0x14 = clamp(f+0x14, b+0x90, b+0x94)         // min/max; 0,0 = "no clamp"
f+0x18 += (airborne ? +1 : −1) * b+0x9c        // DAT_001c2690/9c = ±1.0
f+0x5c *= b+0x74 (if ≠0) ; f+0x5c = clampadd(f+0x5c, b+0x6c, b+0x70)   // FUN_0005f240
f+0x84 += b+0x7c ; f+0x84 changed by b+0x78 (only when b+0x78 != −5000)
```

`f+0x14`/`f+0x18` are the fighter's two planar velocity components, `f+0x30` a facing/aim scalar, `f+0x5c` a
scale applied to the model, `f+0x84` an animation advance. **[inf]** (fit is strong: the only writer of
`+0x5c` outside this function is `FUN_0005f240`, a clamp, and `+0x84` is only ever `+=` here.)

### 1.3 The collision test — sphere around a bone, against one bone

Melee attacks do **not** use the 164-byte record for their volume. The chain is:

```
row handler → FUN_0006b32c(attacker, target)                // "attack execution"
   for each selected attack slot i (mask bits in f[0x951], table 0x1b54ec/0x1b54f0):
       node = f[0x1a+i]                                      // 3 weapon nodes, +0x68/0x6c/0x70
       bone = *(u8*)(weaponRes + 0x2c + 0x0a + 12*i)          // the slot's 3rd bone byte
       p    = FUN_00137710(node, bone)                       // bone matrix, index & 0xFFF
       FUN_0006a8cc(def[0x40 + 4*i], attacker, victim, p)
```

and `FUN_0006a8cc` is the whole test [obs, `0x6a920…0x6a9a4`]:

```
A = worldPos(attack node bone)          // node matrix +0x30/+0x34/+0x38 (translation)
B = worldPos(victim's hip bone)         // FUN_00137710(victim->model(+0x60),
                                        //   *(u8*)(*(u32*)(victim+0x2728) + 7))
d = |A − B|                             // FUN_00151644 subtract, FUN_000f6044 length
if (d > reach[i] + BODY_R) return 0     // reach[i] = def[0x40 + 4*i], BODY_R = def[0x3c]
```

**Formula** (all [obs], constants from `bin/chr.fpd`, cm units):

```
hit  ⟺  | worldPos(attacker weapon bone)  −  worldPos(victim hip bone) |  ≤  def[+0x40+4i] + def[+0x3c]

def[+0x3c] = 60.0     for every one of the 76 combinations   (body/hit radius)
def[+0x40..0x54] = 50, 45, 45, 45, 45, 60  for every combination   (per-slot reach)
→ effective hit sphere radii: 110, 105, 105, 105, 105, 120 cm
```

So the hit volume is a **sphere of radius ≈1.1 m centred on the weapon/hand bone** — the attacker's own
body radius is part of the sum; the victim contributes a *point* (its hip). No capsule, no box, no per-bone
hurt volumes. The victim's own radius is not used by this test (it is baked into `def[+0x3c]`, which is the
same for both fighters because it is the *attacker's* def that is read).

What actually *gates* the attack in time is `f[0x966]` (>0 ⇒ `FUN_0006b32c` returns early), `f[0x951] & 4`,
`f[0x1b0b]` (>0 ⇒ return) and the hit-window bit `f[0x953] & 8`, plus the mask bits in `f[0x951]` that pick
which of the six slots is live. [obs]

After a hit `FUN_0006a8cc` also:
* adds `attackRecord[+0x90]` (=1.0) or `DAT_001c25b8` (=1.0) as the damage scale — §7;
* `FUN_000601c8(f)` for rows 0xce…0x11c of char 0xe (Hanyuu) only — a bullet spawn (id 0xd8). [obs]

`.atp` record used = `FUN_000617dc(attacker, 0x15e)` ⇒ **`atp[handler_id_of_current_row]`** (§0.1). Its
`+0x88` relation mask is tested against `{1 enemy, 2 ally, 4 self}`.

---

## 2. Hurtbox / body: where the victim's hurt volume lives

There is no hurt *volume*; there is a **bone map per (character, costume)**. `f[+0x2728]` = word `0x9ca` =
`&0x1b3060[(char*9 + costume)*4]`, a 16-byte record `{char* gmo path; u8 bone[12]}`. [obs, constructor
`0006bda4.c:140`; readers `0006a8cc.c`, `00061264/70/7c/88/94.c`, `00061d40.c`, `000628fc.c`]

| byte | role | Satoshi (`chr17*`) | Miyoko (`chr18*`) | Okonogi (`chr19*`) | Keiichi (`chr01*`) |
|---|---|---|---|---|---|
| `+4` | bone `facechange` | 3 | 3 | 3 | 3 |
| `+5` | bone | 6 | 6 | 6 | 6 |
| `+6` | lower bound of the "upper body" bone range | 6 | 6 | 6 | 6 |
| **`+7`** | **`lefthip` — the point the hit test uses** (and the upper bound in `FUN_00061d40`) | **51** | **57** | **67** | **57** |
| `+8` | `head` | 21 | 21 | 24 | 21 |
| `+9` | `neck` | 20 | 20 | 23 | 20 |
| `+10` | `wapon_controll_l` | 19 | 19 | 19 | 19 |
| `+11` | `wapon_controll_r` | 45 | 51 | 51 | 51 |
| `+12` | `leftfoot` | 53 | 59 | 69 | 59 |
| `+13` | `rightfoot` | 48 | 54 | 74 | 54 |
| `+14` | small int (2 / 3 / 0 / 1) — [open] | 2 | 3 | 1 | 2 |
| `+15` | 0 | 0 | 0 | 0 | 0 |

Bone indices verified against the GMO bone lists (`g3d/chr170/180/190.gmo`, and `chr010.gmo` for the
cross-check): `19 = wapon_controll_l`, `51 = wapon_controll_r` for 18x/19x and `45` for 17x (different
skeleton), `leftfoot/rightfoot` line up in all four. [obs]

**The only body radius/height constants** are in `bin/chr.fpd` (byte offsets):

| off | meaning | Satoshi | Miyoko | Okonogi | Keiichi |
|---|---|---|---|---|---|
| `+0x00` int | **base HP** | 8500 | 8500 | 11000 | 10000 |
| `+0x04/+0x08/+0x0c` int | three damage thresholds (vs `f[0x998]`) | 850/850/850 | idem | idem | idem |
| `+0x10` f32 | damage-taken scale | 0.75 | 0.75 | 0.75 | 0.75 |
| `+0x14` f32 | attack scale | 1.11 | 1.11 | 1.11 | 1.11 |
| `+0x18` f32 | defence scale | 0.44 | 0.44 | 0.44 | 0.44 |
| `+0x28` f32 | **damage unit** (`attackPower × this`) | 1000 | 1000 | 1000 | 1000 |
| `+0x2c` f32 | the same when `f[0x99d] > 0` | 250 | 250 | 250 | 250 |
| `+0x30` f32 | guard damage fraction | 1 | 1 | 1 | 1 |
| `+0x34` f32 | **body scale** (×0.94…1.11) | 1.03 | 0.94 | 1.11 | 1.00 |
| `+0x38` f32 | hit-stop frames | 40 | 40 | 40 | 40 |
| `+0x3c` f32 | **body/hit radius** | 60 | 60 | 60 | 60 |
| `+0x40…+0x54` f32 | six attack reaches | 50,45,45,45,45,60 | idem | idem | idem |
| `+0x58` f32 | damage multiplier (guard/reversal?) | 1 | 1 | 1 | 1 |
| `+0x5c` int | gauge scale / max (`f[0x995]`) | 1000 | 1000 | 1000 | 1000 |
| `+0x60` int / `+0x64` int | 85 / 10 | | | | |
| `+0x68…+0x7c` int | six per-direction reaction values | −17,−24,−27,−20,−20,−5 | −17,−22,−22,−20,−22,−4 | −18,−23,−29,−22,−24,−6 | −17,−22,−27,−20,−23,−6 |

**Push-out between two fighters: not found.** No fighter-fighter separation code was located (the hit path
never needs it, and `+0x3c` is only read by `FUN_0006a8cc`). If the PSP build pushes bodies apart it is
inside the per-player object code, not the Fighter. **[open]**

---

## 3. Bullets

### 3.1 The two shared tables are loaded at *fixed addresses*

| file | size | record | count | load target (vaddr) | produced by |
|---|---|---|---|---|---|
| `bin/shot_data.bin` | 6 600 | **0x14 (20)** | **330** | **0x18e870** | `FUN_0001a49c(id)` = `id*0x14 + 0x18e870`, guard `id < 0x146` (326) |
| `bin/bullet_attack_data.bin` | 119 184 | **0x9c (156)** | **764** | **0x190470** | `FUN_0001b40c(id)` = `id*0x9c + 0x190470`, guard `id < 0x2fc` (764) |

119 184 = 764 × 156 exactly; 6 600 = 330 × 20 exactly. [obs: divisibility + `scan_imm 0xe870` +
`FUN_0001b40c/0001b608/0001b65c/0001a49c`] The `.rodata` at those addresses holds a *pre-load skeleton*
table (`{k, 0, -65536, 0, -1}`-shaped records) and `FUN_00019efc` calls `FUN_00121f58(&DAT_00190470)` — a
dcache writeback of the 119 KB range — which only makes sense if the loader writes into it. [obs for the
call and the skeleton; inf for "the loader overwrites it"]

### 3.2 `shot_data` record (0x14)

| off | type | meaning | observed range |
|---|---|---|---|
| `+0x00` u32 | packed parameter (e.g. `0x00230056`, `0x00000059`, `0x000901ef`) | [open] — varies with the pattern, not monotonic | |
| `+0x04` f32 | **speed** (world units per tick) | 0, 1, 2, 5, 8, 10, 12, 14, 15 |
| `+0x08` f32 | **spread lower angle** (rad) | −0.5236 (−30°), −0.7854 (−45°), −0.6981 (−40°) |
| `+0x0c` f32 | **spread upper angle** (rad) | mirror of `+0x08` |
| `+0x10` u16 | flags (`0xff12`, `0xff02`, `0x0500`, `0x3301`, `0x0610`…) | |
| `+0x12` u16 | **self index** — equals the record number where populated | 0…325 |

`FUN_0001b65c(id)` (the "is this bullet real" test) additionally requires `shot[+0x10] != 0xff` and
`shot[+0x11] != 0xff`, so the `…ff12`-style records are rejected as bullets. [obs]

### 3.3 `bullet_attack_data` record (0x9c)

`+0x00 … +0x93` is **byte-for-byte the `.atp` record shape** (power `+0x00`, `+0x04/+0x08`, packed
`{u8,u8,100,u8}` at `+0x14`, hit type at `+0x18`, stun `+0x1c`, `+0x20` value, attribute bits `+0x24`,
relation mask `+0x88`, motion at `+0x8c`), with two differences:

* **`+0x90` is not 1.0 here — it is the shot index** into `shot_data` (`< 0x146`). [obs, `FUN_0001b608`]
* the trailing 8 bytes: **`+0x94` u32 (unused in the samples), `+0x98` u16 = effect id, `+0x9a` u16 = self
  index**. `FUN_0001b440` spawns effect `+0x98` through `FUN_0000ccb8(engine, id, pos, 0, 1)`. [obs]

Samples used by the roster: id 0 → power 1.75, `+0x14 = 0x2864000a`, hit type 8, `+0x20` 35, attr
`0x00208000`, shot 33; id 1 identical but effect index 1; id 2 → shot 34; id 6 → power 2.7/1.0/1.0, attr
`0x00142000`, shot 48, effect 61; id 0x33 (51) → power 0.63/0.5/0.5, shot 37 (speed 14), effect 57;
id 0xd8 (216) → power 0/0/0, attr `0x00010000`, shot 130 (speed 8), effect 103. [obs]

### 3.4 Spawn path and kinematics

```
row handler (94/95/96, or a wrapper) → FUN_00070c58 / 00070bec / 00070b88  → FUN_00070acc(f, 0/1/2)
FUN_0007896c… (row 0x109 etc.)        → FUN_00070cd4(f)                  → bullet 0x33 (51)
FUN_0006ff18(f, dir)                  → bullet 6
FUN_000601c8(f)                       → bullet 0xd8 (216)   [only when f[+0x6c55] != 0]
row 0x154/0x155 → FUN_000790c4        → FUN_00070910(f, atpCur[+0x18])   (= 0 in all 76 weapons)
```

`FUN_00070910(f, id)` = the only spawn that uses a **muzzle bone**: bone `5` (`0xc` for char 0xb) of
`FUN_000609cc()`, else `(f+0x08, f+0x0c + DAT_001b0880, f+0x10)`; direction = the triple at
`f+0x2c/0x30/0x34`; bullet `0x3f` (63) gets its X mirrored (`|x + DAT_001c2620|`). [obs]

All of them end in `FUN_0001abf4(engine + 0x42224, id, &pos, &dir, playerIndex, teamOrPower)`:

```
for (slot = manager+4; ; slot += 0x90) {          // 50 slots, 0x90 bytes each  [obs: addiu s0,s0,144]
    if (slot[+0x04] == 0 && slot[+0x84] == 0) {
        vcall[+8](slot);                          // reset
        vcall[+16](slot, id, pos, dir, player, team);
        return slot;
    }
    if (++i == 50) return 0;
}
```

`FUN_0002de5c` (= slot vtable `+0x10`, reached from the Bullet vtable at `0x1e0f00` whose typeinfo slot holds
`0x1e0ee0` = "6Bullet") is the setter [obs]:

```
accept only if FUN_00019fa8(id) && FUN_0001a470(id)          // id < 764
bullet+0x08..0x13 = pos            bullet+0x14..0x1f = dir
bullet+0x75 = player index         bullet+0x76 = second byte (team/power byte)
bullet+0x80 = id
bullet+0xe8 = bullet_attack_data + id*0x9c
bullet+0xec = shot_data + shotIndex*0x14
bullet+0xc8 = attack[+0x90]        (= shot index)
FUN_00009cfc(bullet+0x60, shot[+0x00] + 2)
vcall[+0x64]; FUN_00019b24(bullet, shot); FUN_000540c0(bullet); FUN_0002d1e8(bullet, id, 0)
if (FUN_0001b65c(id)) FUN_0001b228(engine + 0x43e48, bullet)   // register with the per-frame list
bullet[+0x04] = 1                                              // active
if (attack[+0x24] & 0x4000) FUN_00009ca8(engine)
```

Bullet class members recoverable from the above: `+0x00 vtable`, `+0x04 active`, `+0x08 pos[3]`,
`+0x14 dir[3]`, `+0x60 sub-object`, `+0x75 owner`, `+0x76 team`, `+0x80 id`, `+0xc8 shot index`,
`+0xe8 attack record ptr`, `+0xec shot record ptr`. `FUN_0001b440` shows 4 further sub-slots at
`+0x378e + 16i` (`{u8 timer; matrix…}`) whose matrices get effect `attack[+0x98]` spawned when the timer is
non-zero — that is a *different, larger* object than the 0x90-byte pool slot, so **the pool slot is a
handle, not the whole Bullet** [inf].

Movement: the kinematics are `dir` (unit vector from the fighter) and `shot->speed`; homing, gravity,
lifetime and the per-frame integrator were **not** decoded. **[open]**

### 3.5 Per-weapon projectile table (all 12 files of the three, 2 rows each)

`atp[340]` and `atp[341]` are **all-zero in all 76 `.atp` files** [obs], so the `0x154/0x155` path always
yields bullet id 0. The per-weapon projectiles are the hard-coded ids in rows 94/95/96:

| weapon | rows 94/95/96 handler | bullet ids | attack record | → shot idx | speed | spread | effect |
|---|---|---|---|---|---|---|---|
| chr17a, 17b, 17c, 17d | `70c58` / `70bec` / `70b88` | 0 / 1 / 2 | power 1.75, 1.75, 1.75; attr `0x00208000`; hit type 8 | 33 / 33 / 34 | 1 / 1 / 2 | ±40° | 57 |
| chr18a, 18b, 18c, 18d | same | 0 / 1 / 2 | same | 33 / 33 / 34 | 1 / 1 / 2 | ±40° | 57 |
| chr19a, 19c | same | 0 / 1 / 2 | same | 33 / 33 / 34 | 1 / 1 / 2 | ±40° | 57 |
| chr19b (handgun) | same (+ rows 207/209/211/213/215/217/219/221/223 → hid 207, rows 227…235 → hid 227) | 0 / 1 / 2 | same | 33/33/34 | 1/1/2 | ±40° | 57 |
| chr19d | same (+ 226…237, 285/286) | 0 / 1 / 2 | same | 33/33/34 | 1/1/2 | ±40° | 57 |

So **no new fighter's weapon has a distinct bullet**: the three of them share ids 0/1/2 with the rest of the
cast, and the differences between their weapons live entirely in the *melee* rows (§8). [obs]

---

## 4. Magazines / ammo

There **is** a `Magazine` class (RTTI `8Magazine`, name at `0x1e1278`, typeinfo `0x1e126c`
`{&vtable, "8Magazine"}`, base `12Messy…linder` at `0x1e1250`; the class vtable with
`FUN_0007dd0c, FUN_0007dd1c, 0x7dd24, 0x7dd84, FUN_0007dd8c, FUN_0007ddd4, FUN_0007de5c, FUN_0007de64,
FUN_0007de9c, FUN_0007def8, …` starts at `0x1e128c`). [obs]

It is **not** a per-weapon-file structure. Each player has **two** of them inside the input mapper
(`f+0x18d5`'s object, sub-objects at `+0x14` and `+0x24` = words 5 and 9 of that object) and they are the
**main ammo magazine** and the **charge-stage magazine** — exactly the pair the PC remake already models
(`src/battle/core/battle_magazine.hpp`, `battle_magazine_hud.hpp`, snapshot by `FUN_00642060` on the PC
build; `m_magazines[0]` main, `m_magazines[1]` charge). [obs for the two objects and their use; inf for the
identity of each]

Observed use in `FUN_00083f08`/`FUN_0007e964`/`FUN_0007e6a4` (the per-tick input builder):

```
fVar4 = dt * (1000.0 / (short(weaponParam+6) * mag[1]))   + mag[3]     // charge path
fVar4 = dt * (1000.0 /  short(weaponParam+8))             + mag[3]     // charged/other path
mag[3] compared against  i * vcall[+0x14](mag)   to pick the stage index 0..mag[1]-1
if (vcall[+0x10](mag) == 1)  outByte[0] = 1        // "first charge stage ready"
if (vcall[+0x10](mag) == 2)  outByte[1] = 1        // "second charge stage ready"
```

`DAT_001c27bc = 1000.0`, `DAT_001c2990/94/98 = 3.0/2.0/1.0`, `DAT_001c299c = 1000.0`. [obs]

**Where capacity/reload come from**: `mag[1]` (byte `+0x04`) = capacity, `mag[3]` (`+0x0c`) = the running
value, `(char)mag[4]` (`+0x10`) = a mode flag; the *rates* come from the per-weapon parameter object
`*(u32*)(inputMapper->[0x1c])`'s 16-bit fields `+6` and `+8` — i.e. **per weapon, from the engine's weapon
record, not from `.acv/.acs/.atp`** (none of the three files contains any ammo-like field).
**[obs for the reads; open for where that weapon record is loaded from]** The PSP numbers for the three
new fighters' 12 weapons are therefore still unknown; a port should take the PC remake's per-weapon values
until that object is located.

---

## 5. Input

### 5.1 Where the fighter reads its input

The button block `fighter.md` §3.5 left undecoded is **`f+0x2494`, a 0x28-byte struct filled once per
tick** by `FUN_00083f08(f+0x18d5, f, f+0x925, &pad)` → `FUN_0007e964` → `FUN_0007e6a4` → the Magazine
virtuals. The fighter *reads* the following fields (all [obs], via `scan_imm`):

| offset | type | reader | meaning |
|---|---|---|---|
| `+0x2494` u16 | | `FUN_00060328` = `(u16 & 0x7f) >> 6` | 2-bit direction/stick state |
| `+0x249c` u16 | | `*(u16*)(FUN_0005e3dc(f) + 8)` in `FUN_00070280` | **the four action buttons** |
| `+0x24a4` f32 | | `FUN_0005efc0(f)->[0x10]` in `FUN_0006f594` | stick axis value |
| `+0x24a8` f32 | | `FUN_0005efc0(f)->[0x14]` in `FUN_0006f594` | stick deadzone/threshold |
| `vtable+0x48` | u32 | `FUN_00077cd8` | attack-button flags: **bit 0 = attack pressed, bit 2 = second attack** |
| `+0x24a0`,`+0x24a2`, `+0x24ae…+0x24ba` | u16 | (cleared per tick; not read where found) | [open] |

**Button bit layout of `f+0x249c`** — proven by the row ids the bits produce [obs, `FUN_00070280`]:

| bit | row it starts | called from |
|---|---|---|
| `0x04` | **2** | `FUN_000703dc` / `FUN_00077520` = `FUN_00070280(f, def[0x70], 2, 4, 6, 8)` |
| `0x10` | **4** (and **10** in the generic runner) | same / `FUN_00077cd8` = `(…,0x15e,10,0x15e,0x15e)` |
| `0x20` | **6** | same |
| `0x08` | **8** | same |

Rows 0…11 are the **command/entry rows** (one specialised handler each: `FUN_00077520, 00077720, 00076534,
00077920, 000772cc, 0007960c, 00077428, 000795d0, 000774a4, 00079594, 000773ac, 00079648`); row 0's handler
is the one that dispatches the four bits above. The physical-DualShock mapping of those four bits is behind
the input-mapping objects (`FUN_0007e610`, `FUN_0007e67c`, `FUN_0007e450`, and the button-config data), which
was **not** decoded. **[open]** A port can treat them as jump/melee/shoot/guard in some order and calibrate
against the data (each bit's row 2/4/6/8 has its own `.acs`/`.acv` program, so the mapping is
distinguishable by playing the rows).

### 5.2 How a row is chosen (`FUN_0006f884`, `FUN_0006f9cc`, `FUN_00077cd8`)

`FUN_00077cd8(f, ground, a3, a4, rowA, rowB, rowC, rowD)` — the order, [obs]:

1. `rowC` (if `< 0x15e`, else `grounded ? 0x12 : 0`) via `FUN_0006a240(f, row)` — "let the row program
   decide".
2. **guard**: `vcall[+0x48] & 4` and current row ≠ 0x5c ⇒ `setRow(rowD)` when grounded, `setRow(0x1d)` in the
   air; later `if (FUN_0005f16c(f) && grounded && def[+0x6c] + f[0x995] >= 0) setRow(0xc)` with
   `FUN_00060260` as the extra gate. (row 12 = guard, `f[0x951]` bit 9 gates it)
3. `vcall[+0x48] & 1` and `rowD < 0x15e` ⇒ `setRow(rowD)`.
4. `FUN_00074148(f, grounded, 0x10, rowC, cutAllowed)` — **the S2-record-driven transition** (§1.2).
5. **four-button command**: `if (a3 && (ground) && FUN_000606e0(f)) FUN_00070280(f, def[+0x70], 0x15e, 10,
   0x15e, 0x15e)` ⇒ bit `0x10` starts **row 10**.
6. attack gate `FUN_0006a7d8` (needs gauge level ≥ 2 **and** `f[0x997]==1`):
   * grounded: `FUN_0006f884(f)` then `FUN_0006f9cc(f, 0xa3,0xa3,0xa3,0xa3,0xa3)`;
   * airborne: `FUN_0006f9cc(f, 0x6b, 0x70, (0x71 if FUN_0005e588(f,0x71)>=0 else 0x6b), 0x72, 0x73)`.
7. **dash**: `FUN_00070484(f, 0,1,0, rowB, ground?0xce:0xe0, ground?0xe2:0xec)`.
8. `if (FUN_0005f13c(f))` (= `(f[0x951] & 0x3f) >> 5` ≠ 0):
   * grounded: `FUN_0006f884(f)`, `FUN_0006f9cc(f, rowA,rowA,rowA,rowA,rowA)`;
   * airborne: `FUN_0006f9cc(f, rowA, 0x70, (0x71 ok ? 0x71 : rowA), 0x72, 0x73)`.
9. else `FUN_0006f884(f)`; finally `FUN_0007469c(f)` + `FUN_0001af20(rowTime, …)`.

`FUN_0006f884(f)` [obs]:

```
if (guards FUN_00061474/00060328/0005f004 all pass) {
   if (f[0x996] < 2) {                                  // gauge level < 2
      if (grounded && FUN_0005f648(f) <= f[0x998])
          setRow(f[0x997]==0 ? 0x5e : (f[0x997]==1 ? 0x5f : none))     // rows 94 / 95
   } else {                                            // gauge level >= 2
      p = f[+0x248c] (= v[4] of the per-combo table, §5.3)
      if (p == 0) setRow(grounded ? 0x62 : 0x65)
      else { if (f[+0x2490] & 1) p = *(p + f[f[+0x2490]>>1]);   // virtual dispatch
             row = (*p)();  if (row < 0x15e) setRow(row); }
   }
}
```

`FUN_0006f9cc(f, r1..r5)` = `FUN_0006f884` then `FUN_0006f594(f, r2..r6)` (pick by stick direction using the
`+0x24a4` value vs the `+0x24a8` threshold) then, for the grounded path, validate the pick with the
**`.acv` S3 chain table** `FUN_0007d488(f+0x2604, row)` and fall back to `r1`; finally
`FUN_00069070(f, row)`. [obs]

### 5.3 The per-combo 8-entry function-pointer table (this is where "code per combo" lives)

`FUN_0005d9e4(&v, configRec, extra)` fills eight pointers from tables around `0x1b3e3c…0x1b3f18`;
the constructor stores them at `f[0x93e]=v0, f[0x93f]=v1, f[0x942]=v2, f[0x943]=v3, f[0x923]=v4,
f[0x924]=v5, f[0x940]=v6, f[0x941]=v7`. Defaults: `v0=0x5e888, v2=0x5e7e0, v4=0x5e80c`, others 0. The
overrides selected by `switch (char) { case weapon … }`: chars 2, 3, 5, 6, 7, 8, 10, 11, 13, 15 and
**char 0x12 (Okonogi) weapons 0 and 2 → `v0=0x5e904, v1=0`** (also noted in `fighter.md` §7.1/7.4).
**Satoshi (0x10) and Miyoko (0x11) appear nowhere** ⇒ they run the default set. [obs]

`v0/v2/v4` are 3-argument routines `(f, a, b)` that set the per-node attack-variant words
`f[+0x24f0]`/`f[+0x24f4]` (0/1/2); `f[+0x248c]` is only used as the gauge-2 row chooser (§5.2), and
`FUN_0005fa0c` (v4 for some combos) instead maps the current row (99…106) to a variant. [obs]

### 5.4 `button combo → row` table

Proven rows (all [obs]; `HT` = the handler's baked generic arguments):

| input | row | notes |
|---|---|---|
| button bit `0x04` | 2 | entry row |
| button bit `0x10` | 4, and 10 from the runner | entry row / "command" row |
| button bit `0x20` | 6 | entry row |
| button bit `0x08` | 8 | entry row |
| guard held (`f[0x951]` bit 9, `def[+0x6c]+f[0x995] ≥ 0`) | 12 (0xc) | ground only |
| stick pushed (`FUN_0005f648(f) <= f[0x998]`, level < 2) | 94 / 95 (0x5e/0x5f) | the *projectile* rows (§3.4) — the "run" reading in `fighter.md` is wrong |
| stick pushed, level ≥ 2, no per-combo pointer | 0x62 (ground) / 0x65 (air) | walk/step |
| air attack attempt | 0x70,0x71,0x72,0x73 (+0x6b) | `FUN_0006f9cc` candidates |
| dash (`FUN_00070484`) | 0xce/0xe2 ground, 0xe0/0xec air | two variants each |
| attack row chain (`rowA`/`rowC` of the wrapper) | 99→100→103, 107→108→109→110, 112→116→120, 114→118→122, 116→120, 118→122 | see §8 — each row's wrapper names the next row in its `rowA`/`rowC` slot |
| jump chain | 107 (rowA 0x6d=109), 108 (rowA 0x6e=110), 109, 110 (rowA 0xb2=178, rowB 0x8c=140) | |
| `FUN_0006f884` level ≥ 2 per-combo row | `(*f[0x923])(f)` | per-combo function (`0x5e80c` default) |

`tap` vs `charge` for shots: the charge machinery is the Magazine pair (§4) — the second magazine counts
charge stages and `FUN_0007e6a4` publishes "stage 1 ready"/"stage 2 ready" in `f+0x925[0]`/`[1]`; those two
bytes are what distinguish a tap from a charged shot. The consumer of `f+0x925[0..1]` was not found.
**[open]**

---

## 6. Movement constants

Movement is **data-driven**, not a table of constants: `.acv` S2 block B supplies target speeds,
accelerations and clamps through `FUN_0007469c` (§1.2), and the per-combo scalars live in `bin/chr.fpd`.
There is **no** walk/run/jump/gravity constant in the fighter code:

* `fighter.md` §9's rodata scan (`150, 10000, 250000, −20, 5, 3, 0.999`) is *not* movement — `−20` is
  `DAT_001c25ac`, `250000` is a distance clamp, `0.999` a lerp, `3.0` the hit-stop frames.
* gravity: **not present as a constant.** Vertical motion comes from the S2 block-B additive `+0x9c`
  (applied to `f+0x18`) and from the motion (root) curves sampled by `FUN_0001af20`. [obs for the absence
  in `0x5d000…0x7c000`, inf for "the root motion carries it"]
* the only per-character numbers that look like speeds are `bin/chr.fpd +0x68…+0x7c` (six signed ints,
  −4…−29, table in §2) and `+0x34` (body scale). `+0x68…+0x7c` are read as *reaction/knockback* values
  (`def+0x6c` gates the guard; `def+0x70` is passed as `FUN_00070280`'s combo threshold). [obs reads,
  inf meaning]
* dash: `FUN_00070484(f, 0,1,0, row, rowGround, rowAir)` = the dash *state machine*; the speed/duration
  come from the rows it installs and their S2 records. Row ids: ground `0xce`/`0xe2`, air `0xe0`/`0xec`.
  [obs]
* jump: `FUN_00070484` for the initial impulse was not traced; rows 107/108/109/110 are the jump chain and
  their S2 records carry the vertical curve. [open]

Tick rate 30 Hz, 1 tick = 1 motion frame (`f[0x950] += 1.0`), so a `shot_data` speed of 1 means 30 units/s
= 0.3 m/s… **which is too slow for a bullet**, so `speed` is almost certainly a per-tick *unit* multiplied
by a scale inside the (undecoded) Bullet update. **[open]** — do not hard-code 30×speed until the integrator
is read.

---

## 7. HP, damage, guard, gauge

* **Max HP** = `def[+0x00] × globalHPPercent / 100`, `globalHPPercent = *(u8*)(FUN_000b683c() + 0x3a6)`,
  default 100 ⇒ Satoshi **8500**, Miyoko **8500**, Okonogi **11000**, Keiichi 10000. Stored as an *int* at
  `f[0x994]` (`+0x2650`). [obs: constructor `0x6c120`, `FUN_0006c4f8` line 637]
* **Attack power**: `.atp`/bullet `+0x00` × `+0x90`, then in `FUN_000690ec`:
  `dmg = param_1 × def[+0x28]` where `param_1` = the record's `+0x90` (1.0) and `def[+0x28]` = **1000**;
  replaced by `def[+0x2c]` (250) when `f[0x99d] > 0`; then ×`DAT_00382954` (attacker buff), ×`DAT_00382958`
  (victim debuff), and for gauge level ≥ 2 ×`DAT_003828ec/f0/f4` per `f[0x997]` = 0/1/2. [obs]
* The hit event record (0x1c bytes) is pushed into the victim's ring buffer
  (`victim[0x34]` base, stride 0x1c, index from `victim[0x35..0x37]`) with
  `+0x00 flags`, `+0x01 attacker slot`, `+0x05 (char)`(hit zone / iVar11), `+0x06 victim slot`,
  `+0x08/+0x0c/+0x10` position, `+0x14` `.atp` record pointer, `+0x18` the damage float; a second copy goes
  to the attacker's own buffer (reversal slot) with `+0x18 = damage` too and `+0x14 = 0`. [obs]
* **HP application** happens in `FUN_0006c4f8`: `f[0x994] -= (int)fVar30` where `fVar30` starts as
  `def[+0x58]` (1.0) and is multiplied by `fVar28`; the `.atp` power enters through `fVar28`. Then
  `FUN_0006472c(f, gaugeGain)` with **`gaugeGain = (HP_before / maxHP) × 100.0`** (`DAT_001c25d4 = 100`).
  [obs: lines 616-641 of `0006c4f8.c`]
* **Guard**: rows `0x3b…0x41` route through a separate branch of `FUN_0006c4f8` that rewrites the reaction
  row to `0x40`/`0x41` and uses `DAT_00382914` as the damage fraction (`def[+0x30]` = 1.0 otherwise).
  `f[0x951]` bit 9 = "guard active", `def[+0x6c] + f[0x995] >= 0` = "may guard". [obs reads, inf wiring]
* **Gauge**: accumulator `f[0x967]` (`+0x259c`), level `f[0x969]` (`+0x25a4`); on reaching
  `DAT_001c25d4 = 100.0` the level rises and the accumulator resets (`FUN_0006c4f8` 0x6c4f8 region 560-612).
  `bin/gauge_data.bin` (912 B) is **not** referenced by any function found: gauge rates are the two
  constants above plus the HP fraction. [obs]
* **Hit-stop**: `def[+0x38]` = 40 frames (`FUN_00066b64` → `FUN_0002a768(def[+0x38], …)`); the freeze
  counter is `f[0x966]`, and `DAT_001c2554 = 3.0` is the *script* hit-stop. [obs]

---

## 8. The populated rows of the twelve weapons

Rows are the `.acv`/`.acs` index. **The `.atp` record is `atp[handler_id]`** (§0.1) — the `hid` column is
what to index. Rows that alias (`125→107`, `129→108`, `115→114`, `119→118`, `127→126`, `131→130`,
`286→237`, `209…223→207`, `229…235→227`) read the *same* `.atp` record as their primary row.

`motion` = `.atp +0x8c` = the motion take id inside `g3d/chrm17/18/19.gmo` (76 takes each). `s2` = `.acv`
§2 record count for the row. `±` = dies per weapon (values in the per-weapon list below).

### 8.1 Shared vocabulary (identical row ids in all twelve files)

| row | hid | handler | motion 17a/17b/17c/17d · 18a…18d · 19a…19d | s2 | kind | how it is entered |
|---|---|---|---|---|---|---|
| 94 | 94 | `70c58` | 184 · 184 · 184 | 0 | **bullet id 0** | `FUN_0006f884` level<2 gate |
| 95 | 95 | `70bec` | 184 · 184 · 184 | 0 | **bullet id 1** | same (0x5f branch) |
| 96 | 96 | `70b88` | 184 · 184 · 184 | 0 | **bullet id 2** | air/`rowB` path |
| 99 | 99 | `7b268` | 237·237·237·237 · 237 · 237 | 1 | melee | `rowC=100` chain; counter row |
| 100 | 100 | `7b374` | 186·186·186·186 · 186 · — | 0 | melee | `rowC=0x67`(103) |
| 102 | 102 | `7b3d8` | 237 · 237 · 237 | 0 | melee | `rowC=0x67` |
| 107 | 107 | `78ac8` | 237·237·237·237 · 237 · 237 | 1 | melee (hit 1) | `rowC=0x6c`(108); jump/attack entry |
| 108 | 108 | `78a68` | 184·184·**203**·184 · 184 · 184 | 2 | melee (hit 2) | `rowA=0x6d`(109) |
| 109 | 109 | `78a88` | 185·185·**202**·185 · 185 · 184 | 2 | melee | `rowA=0x6e`(110) |
| 110 | 110 | `784e8` | 186·186·**203**·186 · — · 185 | 3 | melee | `rowA=0xb2`(178) |
| 112 | 112 | `78508` | 237·237·237·237 · 184 · 237 | 2 | melee | `rowC=0x74`(116) |
| 114 | 114 | `78548` | 237 · 237 · 237 | 2/3 | melee | `rowC=0x76`(118); row 115 aliases it |
| 116 | 116 | `78588` | 184·184·184·184 · 184 · 185 | 2/1 | melee | `rowC=0x78`(120) |
| 118 | 118 | `785c8` | 185 · 185 · 185 | 2/1/3 | melee | `rowC=0x7a`(122); row 119 aliases |
| 120 | 120 | `78608` | 184 · 184 · — | 2 | melee | chain end |
| 124 | 124 | `786c8` | 237·237·237·237 · 184 · 237 | 3/0 | melee | combo/`0x9e`…`0xa2` family |
| 126 | 126 | `78708` | 237 · 237 · 237 | 1/0/3 | melee | row 127 aliases |
| 130 | 130 | `78448` | 186·186·**203**·186 · 185 · 186 | 1/2/3 | melee | row 131 aliases |
| 163 | 163 | `78b08` | 237 · 237 · 237 | 2 | melee | wrapper `rowC` |
| 164 | 164 | `78b28` | 185 · 185 · 184 | 2/3 | melee | wrapper `rowC` |
| 167 | 167 | `78b48` | 237 · 237 · 237 | 2 | melee | wrapper |
| 168 | 168 | `78b68` | 184 · 184 · 184 | 2/3 | melee | wrapper |
| 172 | 172 | `78c44` | 185·185·**202**·185 · 184 · 185 | 3/2 | melee | wrapper |
| 174 | 174 | `78c64` | 186·186·**203**·186 · 184 · 186 | 2/3 | melee | wrapper |
| 176 | 176 | `78c84` | 237 · 185 · 237 | 0/3 | melee | wrapper |

### 8.2 Per-weapon extras

| weapon | extra populated rows (hid) | motion | s2 | kind |
|---|---|---|---|---|
| **chr17a** | 237 (=286), 259, 260, 261, 262 | 237 | 0/1 | melee/entry (hid 237 handler `7a568` = `FUN_00077cd8(f,0,0,1,0x15e,0xf2,0x110,0x15e)`) |
| **chr17b** | — (30 rows, the shared set minus 165/other extras) | | | |
| **chr17c** | 237 (=286), 259, 260, 261, 262 | 237 | 0/1 | as 17a; motion ids shifted for 108/109/110/118/119/130/131/172/174 (202/203) |
| **chr17d** | — | | | |
| **chr18a…d** | 165 (hid 165, `78c24`) | 185 | 0 | melee (Miyoko only) |
| **chr19a** | — | | | |
| **chr19b** (handgun) | 207 (=209,211,213,215,217,219,221,223), 227 (=229,231,233,235) | 237 | 2 / 1 | melee (hid 207 handler `7a488` = `FUN_00077cd8(f,1,0,1,0x15e,0xee,0x109,0x15e)`; hid 227 handler `7a548`) |
| **chr19c** | — | | | |
| **chr19d** | 226, 227 (=229,231,233,235), 228, 230, 232, 234, 236, 237 (=286), 285 | 237 | 0…2 | melee, handlers `7a8c8/7a548/7aa08/7aa48/7aa88/7aac8/7a8e8/7a568/7aee8` |

**No populated row of the twelve carries a bullet in its `.atp`**: every entry above with power > 0 is a
melee row resolved by §1.3; only rows 94/95/96 are projectiles and they spawn their bullet by handler, not
by `.atp`. χ = the `n` in "hit 1/2/3" is the `.acv` §2 record count, i.e. how many **timed** sub-windows the
row has, each with its own A/B blocks.

---

## 9. Practical summary for the port

```
# per (char, weapon):   def   = chr.fpd[(char*4+weapon)*0x170]
#                       cost  = 0x1b3060[(char*9+costume)*4]  → bone[12]
# per (row):            hid   = acv.S4[row];  atk = atp[hid]  (NOT atp[row])
# hit test:             d = |boneWorld(attacker.node_i, wpnBone) - boneWorld(victim.model, hipBone)|
#                       hit = d <= def[0x40+4i] + 60.0
# damage:               dmg = atk[0x00] * atk[0x90] * def[0x28 or 0x2c] * buffMultipliers
#                       victim.hp -= (int)(dmg * damageScale)
#                       gaugeGain = (hp/maxHp) * 100
# maxHp:                def[0x00] * hpPercent/100          (Satoshi/Miyoko 8500, Okonogi 11000)
# bullets:              shot_data[bullet_attack_data[id][0x90]] = {speed, ±angle}
# input:                f+0x249c bits 0x04/0x10/0x20/0x08 → rows 2/4/6/8; row 0 dispatches them
#                       vtable+0x48 bit0 = attack, bit2 = second attack
```

---

## 10. Still unknown (what a port must decide by judgement)

1. **`FUN_0007469c`'s exact field semantics.** The *reads* are listed in §1.2 and are solid; the *meaning*
   of `A/B.v0…v9` (which is lateral speed, which turn rate) is inferred from usage. A run of the game with
   one row stepping through frame by frame would fix all 18 fields.
2. **`FUN_000f7968` (the `f[0x93a]/f[0x93b]` pair)** — yaw/pitch vs something else. Not decoded.
3. **The Bullet update.** Not found (the pool slot is a handle whose real object is ≥ `0x37a0` bytes;
   `FUN_0001b440` shows the effect tracks). Speed unit, homing, gravity, lifetime, hit reaction all open.
   `FUN_0001b65c` is the only near-complete predicate we have.
4. **Graphical input→button mapping.** Which physical button is `f+0x249c` bit 0x04/0x08/0x10/0x20, and how
   the stick becomes `f+0x24a4`, is inside the input-mapper objects (`FUN_0007e450/0007e610/0007e67c`).
   Play-testing rows 2/4/6/8 identifies them.
5. **Magazine capacity/reload numbers** for the twelve weapons: the per-weapon parameter object
   `*(u32*)(inputMapper->[0x1c])` (shorts at `+6`, `+8`) was not located in the loaded data.
6. **`f+0x925[0..1]`** (the "charge stage ready" bytes) consumer not found ⇒ tap-vs-charge row selection is
   not proven.
7. **Push-out** between fighters (if it exists) is not in the Fighter class.
8. **`costume[+14]`** (2/3/0/1) and `costume[+5]` (always 6) unexplained.
9. **`shot_data[+0x00]`** (the packed first word) unexplained; the `-0.6981`/`±0.5236` spread angles and the
   speed are certain.
