# One PSP Fighter body — implementation reference

Reverse-engineering notes for porting the *Higurashi Daybreak Portable* (PSP, ULJM05557) fighter
into the PC remake as **one data-driven body** that reads `activity/chrNNx.acs`,
`activity/chrNNx.acv` and `assault/chrNNx.atp`.

Method: **static reading only** — no emulation, no runtime instrumentation. Every claim is
either **[observed]** (read directly out of the decrypted EBOOT / the game data, with the
address or file offset quoted) or **[inferred]** (a reading that fits the code and the data but
was not proven). Anything I could not decide is listed in §10.

Material used (all local, nothing committed):

| Thing | Path / value |
|---|---|
| Decrypted PRX image (vaddr 0) | `local-data/harness/psp/EBOOT.dec`, sha256 `80363ff749cfb7aee216f8390eff6f5a873b5d51c2dcf804be6cd30094608597` |
| file offset of a vaddr | `vaddr + 0xc0` for `.text`/`.rodata`/`.data` |
| Decompile | `local-data/harness/psp/decomp/<vaddr8>.c`, index `decomp/_index.txt` |
| Helpers written for this study | `local-data/harness/psp/scripts/{eboot,mips,acs,acv,atp,rowtable,rows,find_calls,rowpred,cov_codes}.py` |
| Extracted data | `local-data/harness/psp/dump/` (`get_file.py <path-in-pack>`) |
| Machine-readable row table | `local-data/harness/psp/notes/rowtable.tsv` (weapons `01a-d`, `16a-d`, `17a-d`, `18a-d`, `19a-d`, 350 rows each) |
| Extracted reference data | `local-data/harness/psp/dump/activity_chr01a.acs` etc. |

**File number vs character index.** The resource table names files `chrNNx.*` with `NN` = 1..19, and
the fighter stores `index = NN - 1`. So `activity/chr17a.acs` is **Satoshi**, `chr18a` Miyoko,
`chr19a` Okonogi, while `chr16a` is Natsumi (index 15). Examples in this document that quote
`chr16a` numbers use Natsumi as an *ordinary old character reference*: her file layout is identical
to the three new characters' (verified for all 12 of `chr17a-d`, `chr18a-d`, `chr19a-d`: `.acv` =
4 sections × 350 rows, `.atp` = 51 816 bytes = 350 × 0x94 + 16, `.acs` = 3 496-3 568 bytes).

Character index in code = file number − 1: **16 Satoshi, 17 Miyoko, 18 Okonogi**; 0 = Keiichi,
1 = Rena, 2 = Mion, 3 = Satoko, 4 = Rika, 5 = Shion, 6 = Tomitake, 7 = Takano, 8 = Ooishi,
9 = Akasaka, 10 = Irie, 11 = Chie, 12 = Kasai, 13 = Akane, 14 = Hanyuu, 15 = Natsumi. [observed:
`0x1b18a0` rows are `chr01a..chr19d` in file order (index 16 → `chr17a.*`); the fighter stores the
index at `+0x398`]

---

## 0. The shape of it

There is exactly **one** `Fighter` class and **one** `Bullet` class (RTTI strings `6Bullet`,
`13BulletManager` at `0x1e0eec` / `0x1e0b4c`). One body covers all 19 characters × 4 weapons.
Per-combo behaviour lives entirely in data:

```
 chrNNx.acv  ──S4──►  350 × u32   row -> handler id (0..478), 0xffffffff = row unused
             ──S1──►  350 event lists (row program, time+flags)      -> per-row transitions/hits
             ──S2──►  350 record lists (164-byte timed records)      -> hit windows
             ──S3──►  2 sub-tables (350 × 16 bytes, 350 × u32)       -> chain/cancel data (semantics open)
 chrNNx.acs  ──────►  350 event lists (row "voice/effect/hit" codes) -> per-handler event script
 chrNNx.atp  ──────►  350 records × 0x94 bytes (attack parameters)   -> power, hit flags, motion id
 0x1b08f4    ──────►  479 × {fn, flags} handler table, indexed by the .acv S4 value
```

Key function addresses (all [observed]):

| Address | Role |
|---|---|
| `FUN_0006bda4` | Fighter constructor / re-init (9 args) |
| `FUN_0005d84c` | `setData(acv, acs, atp)` — stores the three loaded blobs |
| `FUN_0005d5d4` | parse `.acv` (4 sections) into the fighter |
| `FUN_00063634` | select data slot (0/1) and re-parse; parse `.acs` and `.atp` |
| `FUN_000654ac` | install row (raw): sets handler, script pointers, timer |
| `FUN_00068aa4` | **`setRow(row)`** — the public row change (hooks + `FUN_000654ac`) |
| `FUN_00069070` | `setRow` + immediately run the new row handler |
| `FUN_0006a240` | run the current row script; if exhausted, run the handler |
| `FUN_0006adcc` | **per-tick entry point** |
| `FUN_00069824` | per-tick part 2: row timer, per-row scripts (S1 + S2) |
| `FUN_0006ac00` | consume the queued event registers (deferred SE/effect) |
| `FUN_00068544` | execute a "voice/SE" code (bit 31 set) |
| `FUN_00077cd8` | **generic row runner** (192 of the 479 handlers are wrappers of it) |
| `FUN_0006c4f8` | hit resolution: range, gauge, hit-reaction row choice |
| `FUN_000690ec` | register a hit event (damage multiplier, attacker/victim, position) |
| `FUN_0006b32c` | attack execution for the current row: pick attack node, call `FUN_0006a8cc` |
| `FUN_0006a8cc` | attack with one node → `FUN_000690ec` |
| `FUN_000617dc` | get the `.atp` record for a row (with special cases) |
| `FUN_00060890` | get the `.atp` record for a row (plain) |
| `FUN_0005d4c0` | `weaponResource(char, weapon)` → `0x1b18a0 + weapon*0x50 + char*0x140` |
| `FUN_0006dd40` | animation/motion selection (`FighterMotion::set`) |
| `FUN_00065a24` | "frozen?" (hit-stop, pause, KO) — gates the row handler |
| `FUN_00072d68` | target/lock-on selection |

### 0.1 Minimum viable body — what to implement, in order

1. **Parse the three files** (§5): container header, `.acv`'s 4 sections, `.acs` 350 lists,
   `.atp` 350 × `0x94`. Index everything by row (and by handler id for the `.acs`).
2. **Fighter state**: position, velocity, facing, char/weapon, `row`, `rowTimer`, the seven event
   registers, three script cursors, HP (`+0x994`), gauge (`+0x967`/`+0x969`), three attack nodes
   (§1.1).
3. **`setRow(row)`** (§3.2): reset cursors and timer, install the handler id, seed `+0x951` with
   the row's first `.acs` code, re-target the animation.
4. **The tick** (§2): timers + row programs (§4.1) → row handler → event registers → input → dt.
5. **The generic runner** (§4.4) as the handler for the 192 wrapper rows, with each wrapper's baked
   arguments (column `generic_args` in `notes/rowtable.tsv`).
6. **The `.acs` dispatcher** (§4.2): main register, two mask registers, SE id, effect id.
7. **Hit registration** (§5.3): `.atp` power × `+0x90` × defence multipliers → hit event; range
   test; gauge accumulation; reaction-row choice from `0x1b1848` / `0x1b1870`.
8. Ignore data slot 1 (§5.4). `+0x944` (`0x1b54f4`) is only reached by char 7/8 and by the new
   characters' weapons `a`/`c` (§7.1, §7.4), so leave it a stub at first.

---

## 1. The Fighter object

### 1.1 Layout (byte offsets)

The object is at least `0x6c58+` bytes; `+0x18d5*4 = 0x6354` is an embedded sub-object and
`+0x1b16*4 = 0x6c58` another. Offsets below are **byte** offsets. [observed in the constructor
`FUN_0006bda4` unless marked]

| Offset | Type | Meaning |
|---|---|---|
| `+0x00` | ptr | vtable. Virtuals used: `+0x28`, `+0x40` = **player index** (0..3), `+0x48`, `+0x4c` |
| `+0x08` | f32 | position X (set from spawn triple) |
| `+0x0c` | f32 | position Y |
| `+0x10` | f32 | position Z |
| `+0x14`,`+0x18`,`+0x1c` | f32? | not positively identified (never set in the constructor) |
| `+0x20`,`+0x24` | f32 | aim yaw / pitch of the aim sub-object (see `+0x18d5`) |
| `+0x8c` (int `0x23`) | f32 | **facing / mirror factor**. ~10 handlers turn the fighter with `*(float*)(f+0x8c) = -*(float*)(f+0x8c)` (`FUN_00072750`, `FUN_0007283c`, `FUN_0007294c`, `FUN_000729d8`, `FUN_00072acc`, `FUN_00073010`, `FUN_000730a0`, …), and it is passed by address as the direction argument of the motion helper `FUN_00071918` (which writes it at `0x71918`+0x8c). `FUN_0006c4f8` also writes it on a hit (turn to the attacker). [observed] |
| `+0x90`,`+0x94` (ints `0x24`,`0x25`) | f32 | two more floats written together with `+0x8c` by `FUN_0006c4f8` (`= fVar31`, `= 0`); meaning open — most likely the hit's push direction (X/Z) [inferred] |
| `+0x64`,`+0x68`,`+0x6c` (ints `0x19..0x1b`) | ptr | 3 "attack node" objects (`FUN_00009d28(node, row+4)`) — the 3 weapon sub-models / hands |
| `+0x31c` | u32 | `(playerIndex < 2)` — team/side flag |
| `+0x398` | u32 | **character index** 0..18 |
| `+0x39c` | u32 | costume index |
| `+0x3a0` | u32 | **weapon slot** 0..3 (`a`..`d`) |
| `+0x3a4` | u32 | config `kind` — selects a per-combo function pointer table `0x1b54f4` |
| `+0x3a8..0x3b0` | u32 | config words 4..6 (copied from the config record) |
| `+0x3b4 + 8*row` | `{u32 n, ptr}` | **row program** list from `.acv` S1 (`n` × `{f32 time, u32 flags}`) |
| `+0xea4 + 8*hid` | `{u32 n, ptr}` | **row event script** from `.acs` (`n` × `{f32 time, u32 code}`), indexed by *handler id* |
| `+0x1994 + 8*row` | `{u32 n, ptr}` | **row hit-window list** from `.acv` S2 (`n` × 164-byte record) |
| `+0x2485` | u8 | player index (cached, authoritative copy) |
| `+0x2486` | u8 | current motion id (written by `FUN_0006dd40`) |
| `+0x2487` | u8 | init `0xff` |
| `+0x2494..0x24c0` | | weapon-attach matrix (copied in `FUN_00064514`) |
| `+0x24d9` | u8 | respawn/round state machine flag (1 → 2) |
| `+0x24da` | u8 | **grounded flag** (0 = airborne). Selects land row vs air row in `FUN_00077cd8` [inferred] |
| `+0x2520` | u32 | event register bank base (`idx 0x948`); see §4.2 |
| `+0x2524` | u32 | `0x949` loop counter for `0x400/0x800` codes |
| `+0x2528` | u32 | `0x94a` animation advance counter |
| `+0x252c` | u32 | `0x94b` **main code** (last family-0 event) |
| `+0x2530` | u32 | `0x94c` code family 1 register |
| `+0x2534` | u32 | `0x94d` code family 2 register |
| `+0x2538` | u32 | `0x94e` **pending SE code** (negative = pending) |
| `+0x253c` | u32 | `0x94f` **pending effect code** |
| `+0x2540` | f32 | `0x950` **row timer** (motion frames; `+1.0` per tick) |
| `+0x2544` | u32 | `0x951` current row-program code (from `.acv` S1) |
| `+0x254c` | u32 | `0x953` row flags (bit 4 = "script active", bit 5 = "script done", bit 3 = hit-window) |
| `+0x2554..0x2560` | u32 | `0x955..0x958` queued motion ids |
| `+0x2568` | u32 | `0x95a` **current row** (0..349) |
| `+0x256c` | u32 | `0x95b` data slot 0/1 (see §1.3) |
| `+0x2570` | ptr | `0x95c` → the `0x1b08f4` entry used |
| `+0x2574` | ptr | `0x95d` **current row handler** |
| `+0x2578` | u32 | `0x95e` handler flags (bit 0 = "virtual dispatch", see below) |
| `+0x257c` | ptr | `0x95f` → row program descriptor (`.acv` S1) |
| `+0x2580` | ptr | `0x960` → row event script descriptor (`.acs`) |
| `+0x2584` | ptr | `0x961` → row hit-window descriptor (`.acv` S2) |
| `+0x2588` | u32 | `0x962` row-program cursor |
| `+0x258c` | u32 | `0x963` event-script cursor |
| `+0x2590` | u32 | `0x964` hit-window cursor |
| `+0x2594` | f32 | `0x965` timer (max of the "duration" codes) |
| `+0x2598` | f32 | `0x966` timer |
| `+0x259c` | f32 | `0x967` **gauge accumulator** (0..100) |
| `+0x25a4` | u32 | `0x969` **gauge level** (power-up count) |
| `+0x25ac` | f32 | `0x96b` timer (invulnerability / "no attack" timer) |
| `+0x25b4` | u32 | `0x96d` counter (input lock after respawn etc.) |
| `+0x25d8` | u32 | `0x976` row-change guard; `-1` = none (compared with `DAT_003828c0`) |
| `+0x25dc` | u8 | `0x977` previous handler id (compared to the new one on row change) |
| `+0x25e0` | ptr | `0x978` → **350-entry row→handler map** (`.acv` S4) |
| `+0x25e4` | ptr | `.atp` payload (350 × `0x94`) — the row record array |
| `+0x25e8` | ptr | loaded `.acv` blob |
| `+0x25ec` | ptr | loaded `.acs` blob |
| `+0x25f0` | ptr | loaded `.atp` blob |
| `+0x25f4` | ptr | special object, only char 8 + weapon 1 (`FUN_0005f444`) |
| `+0x2604` | object | `.acv` S3 container (`FUN_0007d288`/`FUN_0007d034` fill it; `FUN_0007d534(.,row)` on row change; `FUN_0007d488(.,row)` queries) |
| `+0x265c`,`+0x2660` | u32 | run-row variant index / threshold (used with rows `0x5e`/`0x5f`) |
| `+0x27f0` | records | embedded `0x94`-byte attack records (runtime copies) |
| `+0x6b04`,`+0x6b98` | records | fixed `0x94`-byte records for pseudo-rows `0x154` and `0x155` (the shot rows) |
| `+0x6ae8` | ptr | sound/voice resource table (16-bit id → resource), read by `FUN_00068544` |
| `+0x6c2c` | u32 | set from `DAT_003829a8` on entering rows `0x149` (see §3.4) |
| `+0x6c50`,`+0x6c54` | u32,u8 | counter / flag pair used with the data-slot switch |
| `+0x18d5` (`0x6354`) | object | animation/motion + input sub-object: `FUN_000849a8(f,row)`, `FUN_00086d40(f,fighter,row)`, `FUN_00086c4c(f,char,weapon)`, `FUN_00085e0c(f,fighter,row)`, `FUN_00083f08(f,fighter,input,&btn)` |
| `+0x18f5` (`0x63d4`) | object | animation player: `FUN_0001af20(row_time, f+0x18f5, f, row)` |
| `+0x1b16` (`0x6c58`) | object | per-fighter counters/status; `FUN_0009d0d0` init, `FUN_0009d344/d3e4/d40c/d434/d45c/d484/d1dc/d204/d22c/d254/d2a4/d4ac/d4fc` events |

Handler dispatch [observed, `FUN_0006adcc` + `FUN_0006a240` + `FUN_00069070`]: the handler is
called as `(*f->handler)()` with no arguments. If bit 0 of the flags `0x95e` is set it is
`(*(code**)(handler + f->[flags>>1]))()` — a per-instance method-table offset. **In this build all
479 table entries have flags = 0**, so every handler is a plain 1-arg call. (Keep the flag path in
mind only if a future dump has non-zero flags.)

### 1.2 Constructor `FUN_0006bda4`

Signature (from the call shape): `Fighter*(f, configTable, cfgA, cfgB, p5, p6, p7, float spawn[3], u8 costume2)`.
`config` records are `0x1c` bytes, selected by player index:
`{u32 char, u32 costume, u32 weapon, u32 kind, u32 w4, u32 w5, u32 w6}`.

Sequence [observed]:
1. Clear event registers `0x948..0x96b`, timers, row = `-1`, `0x977 = 0xff`.
2. `+0x31c = (playerIndex < 2)`.
3. `+0x95d/+0x95e = DAT_001b4794 / DAT_001b4798` (default row handler).
4. `+0x944 = 0x1b54f4[kind]` — a per-combo **function pointer** (used as the weapon-transform
   callback in `FUN_00064514`). Table at `0x1b54f4`; first entries `0x5eca8, 0x5ef44, 0x616e4, 0x5ef94, 0x6d9b4, …`.
5. `+0x398/0x39c/0x3a0/0x3a4/0x3a8..0x3b0` = the config record; `+0x3a0` clamped by `FUN_00063634`.
6. costume resource pointer `+0x9ca` = `&0x1b3060[(char*9+costume)*4]` (19 × 9 pointers, 16 bytes each).
7. weapon resource pointer `+0x9cb` = `FUN_0005d4c0(char, weapon)` (see §1.3).
8. `FUN_00063634(f, 0)` → parse data slot 0.
9. Position `+0x8/+0xc/+0x10` = spawn triple; `+0x994` (**HP**) =
   `def->baseHP * global->hpPercent / 100`; `+0x995` = `def->[0x17]`; `+0x997` = config w4.
10. `+0xe6..0xec` = char, costume, weapon, kind, w4..w6 (byte copies for quick compare).
11. Per-character scale table copy for char 7 / weapon 2 (`0x1b3e24`), see §7.
12. `FUN_0005d9e4(&locals, config, …)` → 8 derived ints into `+0x93e,0x93f,0x942,0x943,0x923,0x924,0x940,0x941`.
13. `FUN_0005a128(f, char, weapon)`; `FUN_00086c4c(f+0x18d5, char, weapon)`.
14. `FUN_0001a0ac(f+0xada)` (aim object), `FUN_0007d2fc(f+0x2604)` (S3 container reset).
15. **`FUN_000654ac(f, 0xf)` — the first row is 15 (`0x0f`)**.
16. `FUN_0009d0d0(f+0x1b16)`, `+0x2487 = 0xff`, `+0x6c2c = 0`, `+0x9f4 = 0`.
17. Special case char 8 + weapon 2: 8 extra `FUN_00009d28` calls on `+0x6c30…`.

### 1.3 Per-weapon files and how they are loaded

Table `0x1b18a0`, indexed `[char*4 + weapon]`, stride `0x50` (20 words). Reader:
`FUN_0005d4c0(char, weapon)` = `0x1b18a0 + weapon*0x50 + char*0x140`, returns 0 if out of range.
[observed; the table is dumped in full at the end of this section]

| +off | Meaning | Example (chr01a) |
|---|---|---|
| `+0x00` | u32 flags (0 or 1) | 1 |
| `+0x04` | **motion/skeleton GMO** `g3d/chrmNNx.gmo` | `/g3d/chrm01a.gmo` |
| `+0x08` | head-picture GIM `g3d/chrtNN.gim` | `/g3d/chrt01.gim` |
| `+0x0c` | **`.acv`** | `/activity/chr01a.acv` |
| `+0x10` | **`.acs`** | `/activity/chr01a.acs` |
| `+0x14` | **`.atp`** | `/assault/chr01a.atp` |
| `+0x18` | voice pack | `/activity/chr01a_voice.pck` |
| `+0x1c` | alternate voice pack — non-zero only for files 07,08,09,10,13,17,19 (`chr57a`, `chr58a`, `chr59a`, `chr60a`, `chr63a`, `chr67a`, `chr69a`) | `/activity/chr67a_voice.pck` for Satoshi (idx 16); `0` for Miyoko |
| `+0x20` | SE pack | `/activity/chr01a_se.pck` |
| `+0x24` | shared effect pack `chrNN_eff.pck` | `/activity/chr01_eff.pck` |
| `+0x28` | weapon effect pack | `/activity/chr01a_eff.pck` |
| `+0x2c`,`+0x38`,`+0x44` | 3 × `{char* model, u32 tag, u32 triple}` | **sub-model / attach slots, 12 bytes each.** `model` = `wpn*.gmo` path, `tag` = `0x800040ff` (slot in use) / `0x80ff0000` (empty), `triple` = 3 bone ids (`{0x00ffffff}` = none). Byte 2 of `triple` is read as a bone by `FUN_0006b32c` (`*(char*)(entry + 0xa + i*0xc + 0x2c)`). The **first slot's `model` doubles as the weapon model** (it is what the old notes called `+0x2c`) |

Loading path [observed for the string plumbing, inferred for the order]: the scene loader resolves
`FUN_0005d4c0(slotChar, slotWeapon)` (callers at `FUN_0000bae4`, `FUN_0000ef88`, `FUN_0000f484`,
`FUN_0000f590`, `FUN_0000fdd4`, `FUN_0000fef0`, `FUN_00010068`) and reads the three path strings at
`+0x0c/+0x10/+0x14`. The Fighter receives the three loaded buffers through the virtual
`FUN_0005d84c(f, config, acv, acs, atp)` → `+0x25e8/0x25ec/0x25f0`. Path format strings are the
literal per-weapon strings in the table itself (there is **no** `%s`/`%02d` built path for
`chrNNx`; every one of the 76 files is spelled out — the only format-ish strings near them are
`disc0:/PSP_GAME/USRDIR/%s` at `0x1ca42c` and `/activity/chr00a_se.pck` at `0x1c39f4`).
Shared files are literal too: `/activity/static_param.bin` `0x1c5ee8`, `/bin/bullet_attack_data.bin`
`0x1c5f04`, `/bin/com_param.bin` `0x1c5f20`, `/bin/chr.fpd` `0x1c5f34`, `/bin/gauge_data.bin`
`0x1c5f44`, `/bin/shot_data.bin` `0x1c5f58`.

**Data slot 0/1.** `+0x25e8/0x25ec/0x25f0` are *containers*; `FUN_00063634(f, slot)` re-selects
block `slot` of each and re-parses. `FUN_00068aa4` calls `FUN_00063634(f,0)` or `(f,1)` when the
row being entered is one of `{0, 14, 16}` (`1 << row & 0x14001`) and the slot field `+0x996` is
< 2 — i.e. entering the idle/death/row-16 group re-reads a **second data set**. **All 12 files of
Satoshi, Miyoko and Okonogi contain exactly one block** (`hdr[1] = 1`), so for them slot 1 is never
valid; the only weapon in the pack whose three files carry two blocks is `chr16b` (Natsumi `b`), and
`chr16d` uses an older flat layout (§5.4). **A port should implement slot 0 only and treat `+0x996`
as always 0** for the new characters. [observed: per-file headers and block walks over all 19×4
weapons]

---

## 2. Per-tick order (`FUN_0006adcc`)

`FUN_0006adcc(f)` is the whole per-fighter tick. Called once per logic tick (see §9: 30 Hz).
Order, all [observed]:

1. `i = vcall_0x40(f)` = player index. `if (i < 0) return;` then `if (i > 3) return;` — only
   players 0..3 are simulated.
2. `FUN_00072d68(f)` — **target/lock-on**: picks the current opponent (`+0x922`), retries other
   slots when the current target is invalid; special case char 8 + weapon 1 with `+0x25f4`.
3. `FUN_0006f290(f)` — rotates a per-fighter index `(x+1) % 6` when a global flag bit is set, then
   `FUN_00061fbc(f)` (camera/perspective bookkeeping) [inferred from shape].
4. `FUN_000674f4(f)` — 244-byte helper, animation-side update [not decoded].
5. `if (f->posY <= -1111.11) { FUN_000637f8(f); setRow(f, 0xe); }` — `DAT_001e5748 = -1111.11`
   is the **death plane**; row `0x0e` = the "fell out / KO" row.
6. `frozen = FUN_00065a24(f)`.
   * `frozen == 0` → call the row handler: `(*f->handler)()`, then set `f->flags953 |= 0x39`.
   * `frozen != 0` → skip the row handler entirely; instead if `f->[0x9c9]` (byte, "pending
     reaction") and `f->[0x951] & 0x1000080 == 0x1000080`, run `FUN_0006f3cc` / `FUN_00070d80`,
     then the handler, then clear `f->[0x9ad]` and `f->[0x9c9]`.
7. **Event-script stepper** (the `while (1)` at `0x6ae90`): walks the `.acs` row script
   (`f->+0x960`, cursor `+0x963`) while `entry.time <= f->rowTime`, decoding each `u32 code` into
   the register bank (§4.2). Stops at the first entry whose time is in the future.
8. `FUN_0006ac00(f)` — consume the registers: promote `0x94e/0x94f` to the queued code slots and
   dispatch them (`FUN_00068544` = SE, `FUN_0000ccb8` = effect at position).
9. **Input**: `FUN_000b683c()` → pad manager, `FUN_000b69b0(pad,0xf)` → controller, `FUN_000fd914`
   → pad state. Then `FUN_00083f08(f+0x18d5, f, f+0x925, &buttons)` fills the button structure at
   `+0x925` and returns changed/pressed flags (`local_40[0]`, `local_40[1]`). On `+0x10` (the pad
   id) it also sets `f->[0x932] = 0x1c`, `f->[0x931] = -0x7fffffae` (a queued code) and may call
   `FUN_0005e4bc(f, 0x1b)` / `(f, 0x1c)`.
10. `if (f->[0x9a3] > 0 || paused) FUN_0007e4f4(f+0x18e2)` — per-fighter "extra" update [inferred].
11. **dt**: `dt = FUN_001536b8() - DAT_00382924` (a global time offset), clamped ≥ 0; stored as
    `f->[0xc5] = dt * 1.0` or `dt * -1.0` depending on the sign of the previous value. So `+0xc5`
    is a signed per-tick dt in the engine's time unit.
12. Debug print when `DAT_00378ccc & 4`.

Sub-steps that matter for behaviour (called from the row handlers, not from the tick):
`FUN_00069824(f)` (row timer + row programs, §4.1), `FUN_0007469c(f)` (animation apply),
`FUN_0001af20(rowTime, f+0x18f5, f, row)` (motion sampling), `FUN_0006c4f8` (hit resolution).

Where each stage runs [observed from the call graph]:

```
FUN_0006adcc
├─ vcall 0x40 (player index)
├─ FUN_00072d68   target select
├─ FUN_0006f290   perspective index
├─ FUN_000674f4   animation-side update
├─ (death-plane test)  FUN_000637f8 + setRow(0xe)
├─ FUN_00065a24 -> if not frozen: row handler (0x1b08f4[map[row]])
│    └─ e.g. FUN_00077cd8 -> FUN_0006a240 / FUN_00069070 / FUN_00074148 / FUN_0006f9cc /
│         FUN_00070484 / FUN_0007469c / FUN_0001af20
├─ .acs script stepper  -> register bank (0x948..)
├─ FUN_0006ac00   -> FUN_00068544 (SE) / FUN_0000ccb8 (effect)
├─ input: FUN_00083f08 (+0x925 button block)
├─ FUN_0007e4f4
└─ dt store (+0xc5)
```

`FUN_00069824(f)` (row timer + programs) is entered from the row handlers / helpers, and does:
timer advances (`0x950 += 1.0` unless frozen; `0x965`, `0x966`, `0x96b`, `0x96d`, `0x976`),
then the **S2 hit-window** loop (advance `0x964` past records whose time ≤ rowTime, clearing
`0x953` bit 3), then the **S1 row program** loop (advance `0x962`, writing `0x951` and `0x953`),
and finally `setRow` completion.

---

## 3. Row selection

### 3.1 The two indirections

* **350 rows** per weapon. `row` is 0..349; `0x15e` (350) is the "none" sentinel everywhere.
* `.acv` S4 gives `map[row] = handler id` (0..478) or `0xffffffff`. `FUN_000654ac` rejects the row
  if the id is negative; if the id is ≥ 350 it still installs it (the table is 479 entries).
* `0x1b08f4 + id*8` = `{handler fn, flags}`. 479 entries end at `0x1b17ec`; the next words are
  `0`, `1.0f`, … then small row tables and finally the weapon resource table at `0x1b18a0`.

Row coverage — measured per file (`scripts/rowtable.py`):

| weapon | rows valid | of those, generic-wrapper handlers | `.atp` rows with non-zero data |
|---|---|---|---|
| chr01a (Keiichi bat, reference) | 285 | 138 | 33 |
| chr17a (Satoshi bat) | 288 | 132 | 53 |
| chr17b (Satoshi b) | 284 | 135 | 35 |
| chr18a (Miyoko a) | 285 | 134 | 35 |
| chr19a (Okonogi scissors) | 283 | 136 | 33 |
| chr19b (Okonogi handgun) | 283 | 136 | 35 |

**The populated `.atp` rows are one shared vocabulary.** Every weapon uses the same core set
`{94, 95, 96, 99, 102, 107-110, 112-119, 124-131, 163, 164, 167, 168, 170, 172, 174, 176}` (33
rows: the 11 PC move ids in the plan's map plus the rows around them). Character extras:

* Keiichi `a`, Okonogi `a`: none.
* Satoshi `a`: `+ 100, 120, 226, 229, 231-237, 259-262, 285, 286, 328, 329, 339` (53 rows — the
  largest set in the pack).
* Miyoko `a`: `+ 100, 165`.
* Okonogi `b` (handgun): `+ 207, 227`.

So no new row semantics is needed for the three new fighters; they reuse the same 33 rows plus a
handful of extras. Invalid-row example (`chr16a`): 101 111 113 117 132-136 138 140-162 170 177 182
238-245 275-281 321 324 327 330 333 336 342-349.

### 3.2 `setRow` — `FUN_00068aa4(f, row)`

[observed] This is the only public row change. It:
1. Optionally re-selects the data slot (§1.3) for rows `{0, 14, 16}`.
2. Handles the `+0x1b14 / +0x1b15` "reaction lock" (10-frame counter) — this is where the two
   exclusive rows later get their guards (§7).
3. Per-character/per-weapon switch on `row` (§7): char 7 weapon 2 clears `+0x971` on rows
   `0xe2..0xec, 0x11d`; char 8 / char 0xe / char 0x11 have row-set special cases.
4. Sets `+0x6c2c = DAT_003829a8` when entering rows `0x149` for weapon 0 (char 8, char 0xe) or
   weapon 1 (char 8).
5. Pre-hooks by row *category*: `FUN_0007ee78(row)` (rows `{4,6,8}`), `FUN_0007eda0`,
   `FUN_0007eeac` (rows `{109,110,136,138,142,174,176,182,202,203}`), `FUN_0007ed68` (a 35-row
   set), `FUN_0008417c` (rows `{180,184,…,204}`), `FUN_00084230` (rows `{206,208,…,224,282}`),
   `FUN_000842a4` (rows `{226,228,…,236,285}`); each fires a `FUN_0009dxxx` status event and can
   veto the plain install.
6. `FUN_000654ac(f, row)` — the actual install:
   `hid = map[row]`; `+0x95a = row`; `+0x95c = &0x1b08f4[hid]`; `+0x95d = fn`; `+0x95e = flags`;
   `+0x95f = &{+0x3b4+8*row}`; `+0x960 = &{+0xea4+8*hid}`; `+0x961 = &{+0x1994+8*row}`;
   cursors `+0x962/+0x963/+0x964 = 0`; `+0x950 = 0`; `+0x953 = 0`; `+0x951` = the **first** event
   code of the `.acs` script (so a row can start with a code already active);
   `+0x94b..0x94f = 0`; then `FUN_0007d534(f+0x2604, row)`, `FUN_000849a8(f+0x18d5, row)`,
   `FUN_00086d40(f+0x18d5, f, row)`, vcall `+0x40`, `FUN_0001b790(f+0x18f5, f, char, weapon, row)`,
   `f->[0x29] = 0`.
7. After install: if the new handler id differs from `+0x977`, `+0x976 = -1`; then the
   `FUN_00085e0c` hit-window reset when `+0x935` overflows.

### 3.3 How the row is chosen

There is no single table; the choice is a **priority chain of attempts** inside the row handler.
The generic runner `FUN_00077cd8(f, ground, a3, a4, rowA, rowB, rowC, rowD)` is the template
(§6). Its decision order [observed]:

1. If `rowC < 350` → try `rowC`; else if `ground` → `rowC = (grounded ? 0x12 : 0)`.
2. Guard: air/ground guard via `FUN_0005f16c` → `FUN_00060260` → `setRow(0xc)` (row 12 = guard).
3. Combo window `FUN_00070280(f, def->[0x70], 0x15e, 10, …)`.
4. Air/ground attack attempts: `FUN_0006f884`, `FUN_0006f9cc(f, r1..r5)` — the 5 candidate rows
   baked into each wrapper are tried in order.
5. Dash/step: `FUN_00070484(f, 0,1,0, rowB, 0xce/0xe0, 0xe2/0xec)` (ground values
   `0xce/0xe2`, air values `0xe0/0xec`).
6. Run/walk: `FUN_0005f13c` → `FUN_0006f884` → `FUN_0006f9cc(f, rowA,…)`.
7. Finally `FUN_0007469c(f)` + `FUN_0001af20(rowTime, …)` — the row keeps playing.

`FUN_0006f9cc(f, r1..r5)`: `FUN_0006f884` first; then `FUN_0006f594(f, r1..r5)` picks the first
candidate that the per-row **chain table** (`FUN_0007d488(f+0x2604, row)`) accepts, i.e. the S3
table is the cancel/chain predicate. [observed call shape; S3 semantics open]

`FUN_00069070(f, row)` = `setRow` + run the handler immediately; used for the "must happen now"
transitions (guard, hurt, counter).

### 3.4 Row semantics (as far as established)

Ids below are **row ids** (not handler ids). "Evidence" says what the label rests on.

| Row (hex) | Meaning | Evidence |
|---|---|---|
| 0 | air / falling default | `FUN_00077cd8`: `rowC = (grounded ? 0x12 : 0)` |
| 4, 6, 8 | short "entry" rows (pre-hook `FUN_0007ee78`) | `FUN_0007ee78` |
| 12 (`0xc`) | **guard** | `FUN_00077cd8` → `FUN_00060260` → `setRow(f,0xc)` |
| 14 (`0xe`) | **KO / fell out of the world** | tick: `posY <= -1111.11` → `setRow(0xe)` |
| 15 (`0xf`) | **spawn / initialise fighter** | constructor: `FUN_000654ac(f,0xf)` |
| 16, 17 (`0x10`,`0x11`) | idle variants with a single `0x800004ff` event | `.acs` rows 16/17 hold exactly one `{0.0, 0x800004ff}` event in **all 76 files** (verified); `FUN_00068aa4` re-selects data on row 16 |
| 18 (`0x12`) | **ground idle** | `FUN_00077cd8` default |
| 32-43 (`0x20`-`0x2b`) | **hit reactions** (12 variants, paired by direction) | table `0x1b1870` = `{0x20,0x23,0x21,0x24,0x22,0x25,0x26,0x29,0x27,0x2a,0x28,0x2b}`; `FUN_00065a24` freezes rows `0x20..0x53` |
| 49-52 (`0x31`-`0x34`) | **hit / guard reactions** | table `0x1b1830` = `{0x31,0x32,0x33,0x34}` |
| 55,57 (`0x37`,`0x39`) | **hit reaction, front/back pair** | table `0x1b1848` idx 0/1 |
| 64,65 (`0x40`,`0x41`) | **hit reaction, variant B (flag 0x400000)** | table `0x1b1848-8` = `{0x40,0x41}`; also forced in `FUN_0006c4f8` for rows `0x3b..0x41` |
| 67-70 (`0x43`-`0x46`) | **down / slide / knockdown chain** | table `0x1b1848` idx 2..5 |
| 92 (`0x5c`) | **counter-hit / reversal reaction** | `FUN_000690ec`: on a counter, `setRow(defender,0x5c)` |
| 94,95 (`0x5e`,`0x5f`) | **run** (variant 0 / 1) | `FUN_0006f884`: `0x265c==0 ? 0x5e : 0x5f` |
| 99 (`0x63`) | **counter-attack row** | `FUN_000690ec`: `setRow(attacker,99)` |
| 101 (`0x65`) | walk/step | `FUN_0006f884` air-false branch |
| 107 (`0x6b`) | movement row (wrapper rowC = `0x6b`) | handler wrapper table |
| 108-111 (`0x6c`-`0x6f`) | **jump start chain** | wrappers: row 108 → `param_5 = 0x6d`, 109 → `0x6e`; `FUN_0006f9cc` chain `0x70,0x71,0x72,0x73` |
| 112-115 (`0x70`-`0x73`) | **jump / jump attack chain** | `FUN_00077cd8` → `FUN_0006f9cc(f,0x70,0x71,0x72,0x73)` |
| 116-119 (`0x74`-`0x77`) | air attack chain | wrappers |
| 0x9e-0xa2 | "continue/combo" rows | `FUN_00077cd8` (`0xa3` chain in `FUN_0006f9cc`) |
| 0xce/0xe0, 0xe2/0xec | **dash** (ground/air, two variants) | `FUN_00070484` arguments |
| 0xe2-0xe9, 0xea-0xed | **hit-stun variants** (even rows = "guard-ish", odd = "hit") | `FUN_000842a4` (odd `0xe2..0xec,0x11d`), `FUN_00084230` (even `0xce..0xe0,0x11a`) |
| 0xee-0x14f | **attack rows** (the bulk of the used range) | wrappers with `rowC` = the row itself; `.atp` records populated |
| 0x154, 0x155 | **shot pseudo-rows** (attack record lives inside the Fighter at `+0x6b04`, `+0x6b98`) | `FUN_000617dc` |
| 0x14a-0x14e, 0x150-0x153 | throw/special rows | wrappers; `0x149` sets `+0x6c2c` |

Individual attack row → PC move ids (from the plan's measured map, reproduced here as context):
300→107, 301→109, 302→110, 310→112, 311→114, 320→163, 330→124, 331→126, 332→167, 340→172,
341→174.

A machine-readable per-row dump (handler, class, baked arguments, `.acs` codes, `.acv` S1,
`.atp` power/flags/motion) for `chr01a-d`, `chr16a-d`, `chr17a-d`, `chr18a-d`, `chr19a-d` is in
`notes/rowtable.tsv` (20 weapons × 350 rows). Columns: `weapon, row, handler_id, handler_fn, class, generic_args,
motion, s2_recs, atp_pow, atp_a, atp_b, atp_w5, atp_w6, atp_7, atp_8, atp_9, atp_e0, acs, acv_s1`.

### 3.5 Input

The button block is built by `FUN_00083f08(f+0x18d5, f, f+0x925, &out)`. `+0x925` is a
`u16[16]`-ish struct (the fighter's per-tick button state; `FUN_0006adcc` and `FUN_00068aa4` pass
it). `FUN_0000a4e8(engine, playerIndex)` maps a player slot to the input device; the CPU opponent
comes from `bin/com_param.bin`. I did **not** decode the button bit layout — see §10.

---

## 4. Scripts, event codes and the generic runner

### 4.1 The two script languages

| Script | Source | Format | Consumer |
|---|---|---|---|
| **Row program** | `.acv` S1 → `+0x3b4+8*row` | `n × {f32 time, u32 flags}`, walked with stride `entry[0]` | `FUN_00069824` (writes `+0x951`, `+0x953`) |
| **Hit windows** | `.acv` S2 → `+0x1994+8*row` | `n × 164`-byte records, first field `f32 time` | `FUN_00069824` (advances `+0x964`) |
| **Event script** | `.acs` → `+0xea4+8*hid` | `n × {f32 time, u32 code}` | `FUN_0006adcc` stepper → register bank → `FUN_0006ac00` |
| Chain/cancel | `.acv` S3 → `+0x2604` | 2 sub-tables, 350 entries each (`16` bytes and `u32`) | `FUN_0007d488(f+0x2604,row)`, `FUN_0007d534` |

Time unit: **motion frames**, fed by `+0x950 += DAT_001c25a4 = 1.0` per tick. Times in the data
are whole frames (0, 1, 3, 5, 7, 10, 11, 15, 20, 40…). Special "time" values act as markers:

| Value | u32 bits | Meaning |
|---|---|---|
| `9.8765e17` | `0x5d5b4da6` | "never" — record present but does not fire (used as a list terminator in S2) |
| `2e11` | `0x523a43b7` | `DAT_001c25a8`: special marker compared with `==` in `FUN_00069824` (a "wait" entry) |
| `3e11` | `0x528bb2c9` | `DAT_001c25cc`: second marker (unresolved) |

### 4.2 `.acs` code families — all 71 codes

Decoder in `FUN_0006adcc` (`0x6ae90..0x6af6c`), [observed]:

```
fam = (code & 0x7fffffff) >> 24          // bits 30..24
if (fam == 0) {
    if (code & 0x800) f->cnt949++                        // "repeat" marker
    if (!(code & 0x400)) reg[0] = code                   // reg[0] = +0x94b main code
    else if (f->cnt949 > 0) reg[3] = reg[0]              // commit loop end
    else reg[0] = code
    reg[3] = code                                        // +0x94b
    f->flags953 &= ~0x20
} else {
    reg[fam] = code                                      // reg[1]=+0x94c … reg[4]=+0x94f
    f->flags953 &= ~0x20
}
```

`reg[0]` = `+0x94b` (main), `reg[1]` = `+0x94c`, `reg[2]` = `+0x94d`, `reg[3]` = `+0x94e`,
`reg[4]` = `+0x94f`. `FUN_0006ac00` then promotes the **negative** registers into the queued-code
slots `+0x931/+0x933` and dispatches them.

The 71 codes, by family (counts = occurrences over all 19 characters × 4 weapons' `.acs`):

| Family | Codes | What it does |
|---|---|---|
| 0 — `0x8000xxxx` *behaviour* | `80000100`, `80000103`, `80000104`, `800001ff`, `80000200`, `800002ff`, `80000400`, `80000401`, `800004ff`, `80000800`-`80000803` | main code register `+0x94b`. Layout `0x8000_GGNN`: `GG` = a *group* (01/02/04/08), `NN` = `00` start / `ff` end / small index. `0x800002xx` makes `FUN_0006dd40` advance the animation frame counter (`+0x94a`). Bits `0x400`/`0x800` drive the loop-counter path above. **`0x80000401` appears 4× and only in the new characters** (§7.9) |
| 1 — `0x01000000`, `0x81000000`, `0x81000001` | | register `+0x94c`. `0x01xxxxxx` vs `0x81xxxxxx` = the same slot with bit 31 set, i.e. an on/off pair. Consumed as a 2-word mask table `0x1b54ec = 0x400000`, `0x1b54f0 = 0x800000` by `FUN_0006b32c` [inferred: it selects hit variant 1 vs 2 — the same bits that appear in `.acv` S1 codes] |
| 2 — `0x02000000`, `0x82000000`, `0x82000001` | | register `+0x94d`, same on/off pairing |
| 3 — `0x8308xxxx` | `83080000`, `…03`, `…06`, `…09`, `…0c`, `…0f`, `…12`, `…13`, `…51`, `830f0000` | **SE/voice**. `id = code & 0xffff`; `FUN_00068544` maps it through the per-fighter table `+0x6ae8` (`[slot*0x158 + id*4]`) and calls `FUN_0000cb80(engine, player+0xc, resource, fighter+8, 0, prio)` = play sound at the fighter's position. Modifier bits in the code: `0x10000` (row `0x3b..0x41` → id 0x17), `0x20000` (→ id 0x16), `0x40000` (→ id 0x14), `0x80000` (force, skip the "local player" test), `0x100000`, `0x200000` |
| 4 — `0x8400xxxx` | `84000000`, `84000015`…`84000038`, `8400004c/4d/75/7c/84/85/96/9a/9d/a4/a5/a6/e4` (42 codes) | **effect**. `id = code & 0xffff`; `FUN_0006ac00` → `FUN_0000ccb8(engine, id, fighter+8, 0, 1)` = spawn effect id at the fighter |

Counts per family over all 76 `.acs` files (71 codes total): family 0 = 15 codes
(`80000100` 152×, `80000103` 9×, `80000104` 4×, `800001ff` 82×, `80000200` 60×, `800002ff` 109×,
`80000400` 298×, `80000401` 4×, `800004ff` 164×, `80000800` 4×, `80000801` 7×, `80000802` 4×,
`80000803` 6×, plus `01000000` 307× and `02000000` 319× which land in the same decoder family 0
but read as registers 1 and 2), 0x81 = 2, 0x82 = 2, 0x8308/0x830f = 10, 0x84 = 42.

Sanity check: the 76 `.acs` files use **71** distinct codes; the `.acv` S1 lists use **115**
different ones (small integers and flag words, e.g. `0x00fe000c` = 16 646 156 which does **not**
occur in any `.acs`), so the two languages are genuinely separate.

### 4.3 `.acv` S1 flags (row program) — partial

[observed, from `FUN_00069824` lines 200-260]
* `flags & 0xc0000000 == 0xc0000000` → copy `time` into `+0x965` if larger (a "duration").
* `flags & 0xa0000000 == 0xa0000000` → copy `time` into `+0x966` (a second duration).
* `flags & 0x400000` / `0x800000` → the two **hit-variant enables** used by `FUN_0006b32c`.
* `time == 2e11` → `FUN_0007d9dc(f+0x2604, f->[0x18])`, a chain query.
* Observed values also include `0x80/0x81/0xc0/0xc1/0x100/0x101/0x180/0x1a1/0x1c0/0x1c1/0x280/
  0x281/0x2c1/0x381/0x480/0x7e0/0x7e1/0x7e3/0x7e4/0x7e5/0x1002/0x2080/0x2280/0x4000/0x4081/…`
  — a bitfield whose individual meanings are **not** decoded (§10).

### 4.4 `FUN_00077cd8` — the generic runner

```
FUN_00077cd8(f, ground, a3, a4, rowA, rowB, rowC, rowD)
```
[observed] Order of attempts, each returning 1 = "a row was taken":
1. `rowC` (or `0x12`/`0` by ground state) via `FUN_0006a240`.
2. Guard (`FUN_0005f16c`), then `setRow(0xc)` when `def->[0x6c] + f->gaugeLevel > -1`.
3. `a3` block: if `ground && FUN_000606e0(f)` → `FUN_00070280(f, def->[0x70], 0x15e, 10, …)`;
   then `FUN_0006a7d8(f)` gates the attack attempts:
   * grounded → `FUN_0006f884`, `FUN_0006f9cc(f,0xa3,0xa3,0xa3,0xa3,0xa3)`
   * airborne → `FUN_0006f9cc(f, rowB, 0x70, (0x71 ok ? 0x71 : rowB), 0x72, 0x73)`
4. `FUN_00070484(f,0,1,0, rowB, ground?0xce:0xe0, ground?0xe2:0xec)` — dash.
5. `FUN_0005f13c(f)`: if `rowA < 350`: grounded → `FUN_0006f884` + `FUN_0006f9cc(f,rowA ×5)`;
   airborne → `FUN_0006f9cc(f,rowA,0x70,(0x71 ok?0x71:rowA),0x72,0x73)`.
6. `FUN_0007469c(f)`; `FUN_0001af20(f->rowTime, f+0x18f5, f, f->row)`.

---

## 5. Data formats

All three files are **little-endian, uncompressed** inside the pack, and all three use the same
container header:

```
+0x00 u32 total_size           (== file size)
+0x04 u32 version_or_blocks    (== 1 in every shipped file)
+0x08 ... blocks: { u32 block_size_including_this_header, u32 count, payload… }
        block_size runs from the block's own start, so the next block is at  block + block_size
```

`.acs` has **1** block, `.atp` has **1**, `.acv` has **4**.

### 5.1 `.acs` — 350 event lists

```
header  (0x10 bytes) = total, 1, block_size, 350
block   (350 entries, variable stride, walked by entry[0]):
    +0x00 u32 stride           (8 + 8*count)
    +0x04 u32 count
    +0x08 count × { f32 time; u32 code }
```
`FUN_0005d5d4` is *not* the `.acs` reader: `.acs` is read by `FUN_00063634` (blob `+0x25ec`) into
`+0xea4 + 8*hid` (entry `i` of the file → handler id `i`). Because the S4 map is mostly the
identity, "entry i = row i" is a good approximation, and it is exact for every row whose map value
equals the row.

### 5.2 `.acv` — 4 sections

```
header (0x10)  = total, 1, payload_size, section_count(=4)
0x10  S1  350 entries  → +0x3b4+8*row     row program      (variable stride 8+8n; 16/24/32/40 seen)
       S2  350 entries  → +0x1994+8*row   hit windows      (variable stride 8+164n; 172/336/500/664)
       S3  2 entries    → +0x2604         chain/cancel     (S3a: 350 × 16 bytes; S3b: 350 × u32)
       S4  350 × u32    → +0x25e0         row → handler id
```
Reader `FUN_0005d5d4(f, blob)` — starts at `blob+0x10`, walks each block by its size, and after the
4th block sets `+0x25e0 = block_end + 8`. [observed: disassembly at `0x5d5fc..0x5d674`, and the
section sizes match the files exactly for `chr01a` and `chr16a`]

S3 in detail [observed bytes, semantics **unresolved**]: `S3a` = 350 × 16 bytes of
`{u16, u16, u16, u16, f32 0.1, u32 0}`; row 0 of `chr16a` = `{0x010d, 0, 0, 0x0027, 0.1, 0}`.
`S3b` = 350 u32. `FUN_0007d288` / `FUN_0007d034` build the container; `FUN_0007d534(cont,row)` is
called on every row change; `FUN_0007d488(cont,row)` answers the chain test in `FUN_0006f9cc`.

S2 record (164 bytes = 41 words), [observed layout, semantics partly inferred]:

| +off | chr16a (Natsumi) row 107 / row 108 sample | Note |
|---|---|---|
| `+0x00` | `0x41000000` = 8.0 (row 108) / `0x5d5b4da6` = never (row 107) | **time** (frames) |
| `+0x04` | `0x46afc800` = 22496.0 | |
| `+0x14`, `+0x50`, `+0x58` | `0xc59c4000` = **-5000.0** | sentinel (absent) |
| `+0x1c`, `+0x44`, `+0x68` | `0x40490fdb` = **π** | angle |
| `+0x20`, `+0x6c` | 40.0 / 60.0 | angle in degrees? |
| `+0x60` | `0x491c4000` = 640000.0 | |
| `+0x6d`-ish | 0.698 / 0.244 / 0.349 | cos/sin-ish scalars |

These look like a **timed hit-box / hit-volume definition** (a time, an angle, an offset vector
whose "absent" value is -5000, and per-axis extents), but I did not find the consumer that reads
them field by field — only the time field is proven (compared with the row timer) and the -5000
sentinel is consistent with the "invalid" value used elsewhere in the engine. **Treat the geometry
as open (§10).**

### 5.3 `.atp` — 350 × 0x94 attack records

```
header (0x10) = total(=16+350*0x94), 1, payload(=350*0x94), 350
0x10.. 350 records of 0x94 bytes;  record(row) = base + row*0x94   → +0x25e4
```
`FUN_00060890(f,row)` = `+0x25e4 + row*0x94`; `FUN_000617dc(f,row)` = same, plus special cases
(§7.2). Field map, [observed] where a consumer is named:

| +off | word | Type | Meaning | Consumer |
|---|---|---|---|---|
| `+0x00` | 0 | f32 | **attack power multiplier** (PC `combat[0] / 1000`; 1.0-2.5 seen) | `FUN_0006c4f8`, `FUN_0006a8cc` |
| `+0x04` | 1 | f32 | PC `combat[5] / 100` (0.5-1.0 seen) | |
| `+0x08` | 2 | f32 | PC `combat[6] / 100` (0.5-1.0 seen) | |
| `+0x0c`,`+0x10` | 3,4 | f32? | zero in every sample | |
| `+0x14` | 5 | 4 × u8 | `{b0, b1, b2=100, b3}`; **b3 = PC `combat[8]`** (20 everywhere), `b2 = 100`, `b0`/`b1` vary per move (b0 3..0x1e, b1 0/0x20/0x28) | |
| `+0x18` | 6 | u32 | 8 or 9 in every sample — hit type / SE index [inferred] | |
| `+0x1c` | 7 | f32 | 5,10,15,20,25,30,35 — hit-stun or knockback strength [inferred] | |
| `+0x20` | 8 | f32 | 5,10,12,13,30,40,45,50,75,80,85 — looks like the **damage** value [inferred] | |
| `+0x24` | 9 | u32 | attribute bitfield: `0x00080000`, `0x00200000`, `0x00082000`, `0x00400000`, `0x00080020` | `FUN_0006c4f8`, `FUN_000690ec` |
| `+0x88` | 34 | u32 | **relation mask** tested against `{1 = enemy, 2 = ally, 4 = self}`; all records = 1 | `FUN_0006b32c`, `FUN_00067e70`, `FUN_0006a698` |
| `+0x8c` | 35 | u32 | **motion / animation id** (237, 185, 181…); 0 for non-attack rows | `FUN_0006b32c` region |
| `+0x90` | 36 | f32 | 1.0 — extra power scaling applied on top of `+0x00` | `FUN_0006a698`, `FUN_0006a8cc` |

Damage pipeline [observed]: `FUN_0006b32c` (attack execution) →
`FUN_0006a8cc(def->[0x40], f, target, node)` → `FUN_000690ec(power, f, target, victim, record, pos, 1, 1)`.
`FUN_000690ec`:
* `power = (record+0x00) * (record+0x90)` then multiplied by `def->[0x28]` (or `def->[0x2c]` when
  `f->[0x99d] > 0`), by `DAT_00382954` when `f->[0x9a9] > 0`, by `DAT_00382958` when
  `victim->[0x9ab] > 0`, and by `DAT_003828ec/f0/f4` when the gauge level `f->[0x996]` is 0/1/2.
* builds a hit event record (`0x1c` bytes) into the victim's ring buffer (`victim->[0x34]`,
  0x1c stride, index from `victim->[0x35..0x37]`) with
  `+0x00 flags (|0x400)`, `+0x04 attacker player`, `+0x05 = (char)`, `+0x06 victim player`,
  `+0x08` vec3 position, `+0x14` the `.atp` record pointer, `+0x18` the damage float.
* a hit is registered twice: once against the *victim* and once against the attacker's own
  "reversal" slot (self-hit for reflections like Miyoko's coin).
`FUN_0006c4f8` then does the range test (`DAT_001c25ec = 1.5708` rad cone), accumulates the
attacker's gauge `+0x967 += …` and, when it reaches `DAT_001c25d4 = 100.0`, increments the gauge
level `+0x969` and resets the accumulator; it also picks the hit-reaction row from
`0x1b1848`/`0x1b1870` by direction (`local_7c`) and the `0x400000` attribute bit.

**Guard**: rows `0x3b..0x41` are routed through a distinct branch that rewrites the reaction row
(`0x41` or `0x40`) and uses `DAT_00382914` as the damage/frame fraction — the guard reaction keeps
the same rows but with reduced pushback. [inferred from `FUN_0006c4f8` 0x6d4xx]

**Gauge gain**: `+0x967` (accumulator, 100 = level up), `+0x969` (level), and
`bin/gauge_data.bin` (912 bytes, no container header) presumably the per-character gauge rate —
not decoded.

### 5.4 Container variants in the pack (do not affect the new three)

I walked the headers of all 19 × 4 weapons [observed]:

* **Standard** (224 of 228 files): `hdr = (size, 1, payload, count)`, one block. This covers
  **every** `.acs`/`.acv`/`.atp` of cards 01-15 and **all 36 files of Satoshi, Miyoko and Okonogi**.
* **`chr16b` (Natsumi b) — two data slots**: `hdr[1] = 2`, and the file holds two consecutive
  blocks: `.acs` = 3 488 + 3 608 bytes (2 × 350 lists), `.atp` = 2 × 51 808 (2 × 350 records),
  `.acv` = 2 × full 4-section group (38 408 + 35 784). This is exactly what the `slot` argument of
  `FUN_00063634` selects.
* **`chr16d` (Natsumi d) — old flat layout**: `hdr = (21664, 4, 3992, 242)`; the four sections are
  at top level (`242 / 242 / 2 / 242` entries), i.e. **242 rows instead of 350**, and the matching
  `.atp` has `count = 272` rows (32 656 bytes) while its `.acs` still has 350. `FUN_0005d5d4`'s
  `+0x10`-based walk cannot parse this shape, so in this build Natsumi's `d` ends up with 1 valid
  row. It is leftover/unused content; it is also the only `.acv` where `hdr[1] != 1 and != 2`.

A robust reader should therefore: read `hdr[1]` as a *block count* when the block walk from `+0x8`
lands on the file end, and refuse (rather than guess) the `chr16d` shape.

---

## 6. The 479 handlers: 253 generic wrappers vs 226 specialized

* Table `0x1b08f4`: **479** entries `{fn, flags=0}`, `0x1b08f4..0x1b17ec`. [observed]
* **253** of them contain a call to `FUN_00077cd8`; of those, **192** are pure wrappers of the form
  `FUN_00077cd8(f, a, b, c, rowA, rowB, rowC, rowD); return;` with all parameters baked in.
  [observed; the plan's "192" is exactly this set]
* The remaining **226** do real work (54 of which are just `return 1`/flag setters in the low rows).

Per weapon, **rows** vs **handler ids** (rows alias onto ids, so the two counts differ). Distinct
handler ids reachable per weapon: 255-257, of which 108 are generic wrappers. Row-level counts are
in §3.1.

`notes/rowtable.tsv` covers `01a-d`, `16a-d`, `17a-d`, `18a-d`, `19a-d` (105 000 rows of detail).

Specialized handlers the new characters' populated rows hit — these are the ones a port must
implement beyond the generic runner (all are in the 350-row table, none is character-specific):

| Handler | Rows using it | What it does |
|---|---|---|
| `FUN_0006df70` | 21 | smallest handler (`return`), a no-op row |
| `FUN_0006e068` | 24 | jump/attack gate |
| `FUN_0006e11c` | 27 | charge/aim row (20-22 frame table) |
| `FUN_0006e210` | 26 | short row |
| `FUN_0006e25c`/`FUN_0006e304`/`FUN_0006e398` | 29/30/31 | slow-walk / turn rows |
| `FUN_0006e4b4`/`FUN_0006e4fc`/`FUN_0006e504`/`FUN_0006e50c` | 56/60/62/84 | air rows |
| `FUN_0006e574` | 178 | air row |
| `FUN_0006e720` | 97 | row |
| `FUN_0006e758`..`FUN_0006e7e8` | 321-339 | 19 tiny handlers (8-12 bytes of body, one per row) |
| `FUN_0006e7f0`..`FUN_0006e8a0` | 87-93 | 4 handlers, 44-56 bytes |
| `FUN_0006ecc0`..`FUN_0006efa8` | 32-43 | the **12 hit-reaction rows** (`0x20`-`0x2b`), 52-80 bytes each — different pushback directions |
| `FUN_0006fe74` | 18 | ground idle |
| `FUN_000701e0` | 25 | |
| `FUN_00070b88`/`FUN_00070bec`/`FUN_00070c58` | 96/95/94 | the run rows |
| `FUN_0007104c`/`FUN_00071054` | 171/166 | |
| `FUN_00071064`..`FUN_000713xx` | 295-320 | 26 identical 44-byte handlers (one per attack row) — all do the same thing |
| `FUN_00073c94`..`FUN_00073da4` | 12,13,20,22,23 | guard + reaction rows |
| `FUN_00073f18` | 14 | KO row |
| `FUN_00073fd8` | 16 | idle-with-event |
| `FUN_00076534`, `FUN_000772cc`, `FUN_000773ac`, `FUN_00077428`, `FUN_000774a4`, `FUN_00077520`, `FUN_00077720`, `FUN_00077920`, `FUN_00079594`, `FUN_000795d0`, `FUN_0007960c`, `FUN_00079648` | 0-11 | the 12 "entry" rows |
| `FUN_00077b98`, `FUN_00077ba0`, `FUN_00077c08` | 19, 17, 15 | spawn/init rows |
| `FUN_00072694` | 28 | row with an `0xa0000000` code |

The full list, per row, is in `notes/rowtable.tsv`; `scripts/dump_rows.py` prints the handler table
grouped.

---

## 7. Character-specific code

The engine has one `Fighter`, so every character difference is either data or one of these
`if (char == N && weapon == M)` special cases. Fields used: `+0x398` char, `+0x3a0` weapon,
`+0x2568` current row, `+0x2485` player index, `+0xe6/0xe8` byte copies.

### 7.1 `FUN_0005e09c` — "weapon transform is per-node"
`char == 5 && weapon in {2,3}` **or** `char == 0x12 (=18, Okonogi) && weapon in {0,2}` →
`FUN_00083dfc(row)`; otherwise 0. So **Okonogi, and Shion with weapons c/d, run an alternate
per-row node query.** This is the clearest "new character" hook: Okonogi uses weapons `a` and `c`
in this path.

### 7.2 `FUN_000617dc` — row → `.atp` record, with special cases
* Rows `0x154`/`0x155` → fixed records inside the Fighter (`+0x6b04`, `+0x6b98`).
* `char == 7 (Takano) && weapon == 2` → records from `+0x27f0 + f->[0x25c4]*0x94` (a per-fighter
  variant array) instead of the file; rows `0xe3,0xe5,…,0xec,0x11e` and
  `0xe4,0xe6,…,0x11d` are redirected for that combo.
* `char == 8 (Ooishi) && weapon == 2 && f->[0x3a0] == 2` → rows `0x8f` → `.atp+0x3e70` (row 108),
  `0x90` → `.atp+0x4a00` (row 128), `0x91` → `.atp+0x4b28` (row 130), `0x92` → `.atp+0x4bbc`
  (row 131): one combo borrows four other rows' records.
* `char == 0xe (Hanyuu)` appears in `FUN_00068aa4`'s row sets.

**None of the three new characters appear here**, i.e. they read the plain `.atp` rows — good news
for the port.

### 7.3 `FUN_00062e5c` / `FUN_0006390c` — row-set predicates
Both return 1 for a fixed global row set (`0x30`, `0x33..0x56`, `0x5c`, `0x5d`, `0x154`, `0x155`,
…) plus, for **char 8 + weapon 1 only**, a large extra set `0x10e..0x14e`. So the extra attack rows
are treated as the same category only for Ooishi's `b`. [observed]

### 7.4 `FUN_00064514` — weapon attach transform
Same selector as 7.1 (`char 5 wpn c/d`, `char 0x12 wpn a/c`): copies the result of the per-fighter
callback `f->[0x944]` into the weapon matrix `+0x2494..+0x24c0`, or zeroes it when
`f->[0x2594] > 0`. So the new character's weapon swings go through a *different* transform
routine than the rest of the cast — implement it as a per-combo override, not per character.

### 7.5 `FUN_00065d10` — hit-spark effect mask
```
uVar2 = 1 << (char & 31);
if (char < 0x11 && (uVar2 & 0x1e8ac || ((uVar2 & 1) && weapon == 1)))
        FUN_0000ccb8(engine, 0x84, f+8, 0, 1);      // spawn effect 0x84
```
`0x1e8ac` covers chars `{2,3,5,7,11,13,14,15,16}` (Mion, Satoko, Shion, Takano, Chie, Akane,
Hanyuu, Natsumi, **Satoshi**), plus char 0 with weapon `b`. **Miyoko (17) and Okonogi (18)
are excluded** (the `char < 0x11` bound). [observed]

### 7.6 `FUN_00068aa4` — `setRow` special cases
* `char == 7 && weapon == 2`: rows `0xe2..0xec, 0x11d` clear `f->[0x971]` before the normal
  install (Takano's takedown rows).
* `char == 8`: entering row `0xf6` (from `FUN_000401c8`/`FUN_000407f4`) plus the `+0x1b14/+0x1b15`
  reaction lock.
* `char == 0xe`, `char == 0x11 (17 = Miyoko)`: row-set special cases around the `+0x1b14` lock —
  see 7.8.
* Rows `0x149` for weapon `0` (chars 8, 0xe) or weapon `1` (char 8) set `f->[0x6c2c] =
  DAT_003829a8`.

### 7.7 `FUN_00069ef0` — per-tick special handling
Keyed by `piVar6[0xe8]` (weapon) and a local player index `== 8`; calls `FUN_0007004c(f,0/1)` (row
re-install) and `FUN_0009dxxx` status events. Effectively "re-run my row" for one combo's custom
loop. Not one of the new characters. [observed]

### 7.8 Where Miyoko actually appears
`0x68aa4` is `setRow`, so the plan's "she appears at `0x68aa4`" means: in the reaction-lock block
at the top of `setRow`, `char == 0x11` has its own row sets. Concretely, the top of `setRow`
takes the `+0x996` slot path only for a fixed row mask and otherwise just decrements `+0x1b14`;
chars `7`, `8`, `0xe`, `0x11` get extra row sets in the switch that follows. I could isolate the
`0x11` sets but not fully decode them — see §10.

### 7.9 The two codes exclusive to the new characters

Measured over all 76 `.acs` files files [observed]:

* **`0x80000401`** — 1 occurrence in each of `chr18a`, `chr18b`, `chr18c`, `chr18d`, and nowhere
  else: **Miyoko only** (file 18 = index 17).
* **`0x840000e4`** — 7 occurrences, all in `chr19b`, and nowhere else: **Okonogi's handgun
  (weapon `b`)**.

So they are not "the new characters' codes" as a group; each belongs to one weapon.

`0x80000401` = family 0, group `0x04`, index `01`. The group-4 family already has
`80000400` (start, 298×) and `800004ff` (end, 164×); index `01`/`03`/`04` forms exist in group 1
(`80000103` 9×, `80000104` 4×), so `0x80000401` is most plausibly "hit window group 4, variant 1"
— a third sub-state of a group that other weapons only use as on/off. Consumers are the normal
ones (`FUN_0006dd40` for the `0x200` advance path, `FUN_0006b32c` for the hit variants).
[observed: the code, the family and the consumers; inferred: what variant 1 does]

`0x840000e4` = family 4, id `0xe4` = **228**. 228 is above every effect id used outside
`chr19b` (max `0xa6` = 166), and the handgun fires seven times, so this is the muzzle-flash /
shot effect event, 7× per shot sequence. `FUN_0006ac00` → `FUN_0000ccb8(engine, 0xe4, fighter+8,
0, 1)`. [observed: dispatch + count; inferred: "muzzle flash"]

Neither code needs special code in the port: both flow through the normal dispatcher. What the
port must not do is silently drop an effect id it does not have (228 lives only in
`activity/chr19b_eff.pck`).

---

## 8. Bullets

What is established [observed]:

* One `Bullet` class (`6Bullet` RTTI at `0x1e0eec`), one `13BulletManager` (`0x1e0b4c`), one
  `11BulletTrace` (`0x1e1414`). The class descriptors live at `0x1e0ee4` / `0x1e0b44`;
  they are referenced only from a registry in the data section at `0x289fd0` / `0x289c58`.
* `bin/bullet_attack_data.bin` = **119 184 bytes of `.atp`-shaped 0x94-byte attack records**
  (the first record is byte-identical in layout to an `.atp` record: `1.75, 0.75, 0.75, 0, 0,
  0x2864000a, 8, …`). There is no container header; the file starts with record 0.
* `bin/shot_data.bin` = 6 600 bytes of small parameter records, no container header. The first
  floats are `0, 5.0, -0.5236, +0.5236, …` — i.e. **±30°** (0xbf060a92 = -0.5236 rad,
  0x3f060a92 = +0.5236 rad) and a speed/step of 5.0, repeated with different first words
  (`8`, `8`, `8`, `15`, …). 6600 = 330 × 20 or 275 × 24 — I could not pin the stride (see §10).
* Shots are rows: **row `0x154` (340) and `0x155` (341)** have their attack record stored *inside
  the Fighter object* at `+0x6b04` / `+0x6b98` (`FUN_000617dc`). Those two embedded records are
  refreshed **for all four players** by `FUN_00009db0`, which reads `FUN_00060890(f,0x154)` and
  `FUN_00060890(f,0x155)` from the `.atp` and calls `FUN_0005f3b8(player, rec154, rec155)`; that
  function is a plain 37-word (`0x94`-byte) copy into `+0x6b04` / `+0x6b98`. So the `.atp` rows
  340/341 are **templates for the two shot attacks**, and the live copy can change at runtime
  (weapon power-up). [observed: `FUN_00009db0` lines 96-102; `FUN_0005f3b8` copies 37 words twice]
* A shot is therefore fired by entering row `0x154`/`0x155`; the attack then runs through the same
  `FUN_0006b32c` → `FUN_0006a8cc` → `FUN_000690ec` path as a melee hit, using the embedded record.
* Bullet hits re-enter the same damage pipeline (`FUN_000690ec` / `FUN_0006c4f8`); nothing in the
  hit path is bullet-specific.

Bullet motion, homing, and the spawn call (`FUN_0009xxxx` family) were **not** decoded — §10.

---

## 9. Units and timing

| Quantity | Value | Evidence |
|---|---|---|
| Logic tick | **30 Hz**, and one tick = one motion frame | `+0x950 += DAT_001c25a4`, `DAT_001c25a4 = 1.0` (`0x1c25a4`); all script times are whole frames |
| Frame time used elsewhere | `dt = FUN_001536b8() - DAT_00382924`, stored at `+0xc5` | `FUN_0006adcc` 0x6afb0..0x6b010 |
| Distance unit | the `.gmo`/model unit; no scaling anywhere in the fighter code (positions are copied straight through) | constructor, `FUN_0006c4f8` |
| Death plane | **Y ≤ -1111.11** (`0xc48ae38d`) | `DAT_001e5748`, used in `FUN_0006adcc` |
| Gravity | **not found as a single constant.** No `-9.8`, no per-frame `-0.4`: vertical motion comes from the row programs and the motion (root) curves. The candidate "physics" constants near the fighter code are `0x1c2500 = 150.0`, `0x1c2568 = 10000.0`, `0x1c2598 = 250000.0`, `0x1c25e4 = 250000.0`, `0x1c25ac = -20.0`, `0x1c2550 = 5.0`, `0x1c2554 = 3.0`, `0x1c25d8 = 0.999` | rodata scan of all `DAT_001c2xxx` referenced by `0x5d000-0x7c000` |
| Hit-stop | rows `0x20..0x53` freeze the row handler for `3` frames (`DAT_001c2554 = 3.0`); `FUN_00065a24` also freezes on pause/KO | `FUN_00065a24` |
| Knockback/gauge | gauge accumulator `+0x967` 0..`100.0` (`0x1c25d4`) → level `+0x969` | `FUN_0006c4f8` |
| Angles | bullets/aim use ±0.5236 rad = ±30°, π used as a "full turn" marker | `bin/shot_data.bin`, `.acv` S2 records |
| HP | `def->baseHP * globalPercent / 100` (`DAT_001c25d4 = 100.0` is the same 100) | constructor |

The 60 Hz question for the port: everything time-keyed in the data is in 1/30 s units, so a 60 Hz
simulation should call the fighter tick every second sim step (or accumulate a 30 Hz phase). Do
**not** halve the script times.

---

## 10. What remains unknown

Honest list, ordered by how much it would hurt a port:

1. **Hit geometry.** The 164-byte `.acv` S2 records are timed and contain an angle (π), an absent
   sentinel (-5000) and several magnitudes, but I did not find the code that reads them field by
   field. So "shape, radius, bone/anchor, offsets" are **not** established. The only proven input
   to a hit is the `.atp` record (power + flags) plus the attack *node* (one of 3 weapon nodes) and
   the fighter positions.
2. **`.atp` fields 7 and 8.** `+0x1c` (5-35) and `+0x20` (5-85) are almost certainly hit-stun and
   damage, but neither is read in a function I decoded. `+0x14` byte 0 and 1, and `+0x18`
   (8/9), are likewise unchecked guesses.
3. **`.acv` S3 (chain/cancel) semantics.** The structure (350 × 16 bytes + 350 × u32) is certain;
   which u16 is which row and what the `0.1` float means is not.
4. **`.acv` S1 flag bits.** Only four are decoded (two durations, two hit-variant enables, one
   marker). The remaining ~30 values are a bitfield of unknown semantics — and this is where
   velocity, invulnerability and cancels most likely live.
5. **`.acs` code semantics beyond families.** The families and the SE/effect ids are proven; "hit
   window on/off", "set velocity", "change animation" are *not* proven for any individual code.
   Specifically the `0x8000_GGNN` group/index scheme is a hypothesis (start/end pairs at `00`/`ff`
   are consistent across 16 files).
6. **`0x80000401` / `0x840000e4`.** Their dispatch is known; which branch reacts to `0x80000401`
   and what effect 228 does is not.
7. **Bullets.** `shot_data.bin`'s record stride/fields, the Bullet update function, homing, and the
   spawn call from the shot rows are all open. `bullet_attack_data.bin` is confirmed to be
   0x94-byte attack records.
8. **Button layout at `+0x925`** and the input→row mapping per button: `FUN_00083f08` was not
   decoded, so "which button starts which attack row" is not known beyond the row chains.
9. **`FUN_0005d9e4`, `FUN_0005a128`, `FUN_000674f4`, `FUN_0007e4f4`, `FUN_0001b790`.** Five
   constructor/tick callees were not decoded; they fill 8 fields at `+0x93e..+0x943` and
   `+0x923/+0x924`, and (for `FUN_000674f4`) run an animation-side update each tick.
10. **Stats source.** `+0x994` HP comes from a `def` object reached through `f->[0x945]`
    (a per-combo definition, not one of the three files): `+0x28/+0x2c` attack multipliers,
    `+0x40` power, `[0x17]`, `[0x6c]`, `[0x70]`. Where that object is loaded from was not traced;
    `activity/static_param.bin` (732 bytes, 2 sections of 332 and 392) and `bin/com_param.bin`
    (18 744 bytes) are the candidates.
11. **`FUN_0006de64`-style "row 0x158 stride" tables** (`+0x6ae8`, stride `0x158`) — the SE/voice
    symbol table layout is known only as "id → resource pointer".
12. **Costume table `0x1b3060`** (19 × 9, 16 bytes per entry) is resolved as a `char*` per costume,
    but the other 12 bytes per entry (seen as `0x39060603`, `0x33131415`, `0x02363b`) are not
    decoded.

---

## Appendix A — verifying a claim quickly

```bash
cd local-data/harness/psp/scripts
python3 find_calls.py "FUN_000654ac("     # xrefs with the call line
python3 mips.py 0x63634 24                # disassemble (minimal MIPS32 decoder)
python3 dump_rows.py                      # the 350-entry handler table grouped
python3 acv.py  ../dump/activity_chr16a.acv
python3 acs.py  ../dump/activity_chr16a.acs
python3 atp.py  ../dump/assault_chr16a.atp 100 120
python3 rowtable.py 16 a 100 130          # per-row summary incl. baked wrapper args
python3 cov_codes.py                      # every .acs/.acv code + counts
python3 get_file.py activity/chr17a.acs   # fetch a file from the ISO pack
```

`notes/rowtable.tsv` is the machine-readable spine of §3/§5: one line per (weapon, row) with the
handler, its class, the baked generic-runner arguments, the `.atp` numbers and both scripts.
