# PSP executable — code map

*Higurashi Daybreak Portable Mega Edition* (ULJM05557), decrypted `EBOOT.BIN`, sha256
`80363ff7…0608597` (see [README](README.md)). **Evidence:** static reading of the decrypted
image and a Ghidra decompile with the Allegrex language. Nothing was run.

- **[obs]** means read out of the code or data, with the address given.
- **[inf]** means it fits the code and data but was not proven.
- **[open]** means undecided.

The image is a PRX loaded at address 0, and a file offset is the virtual address + `0xc0`.
Addresses are virtual. The full notes these tables come from are kept locally under
`local-data/harness/psp/notes/` (`fighter.md`, `combat.md`, `art.md`).

## 1. Sections

| Section | vaddr | Size | Notes |
|---|---|---|---|
| `.text` | `0x000040` | `0x167edc` | 6441 functions after `.eh_frame` seeding; the fighter code is `0x5d000–0x7c000` (855 functions) |
| `.eh_frame` | `0x16a104` | `0x20e3c` | 4190 FDEs, absolute `pc_begin`, used to seed function starts |
| `.rodata` | `0x18d0c0` | `0x52c7c` | literal asset paths, handler/resource tables, float constants |
| `.data` | `0x1e3a80` | `0xe44c` | RTTI typeinfo, vtables |
| `.bss` | `0x1f1f00` | `0x26d321` | `shot_data`/`bullet_attack_data` are loaded into fixed addresses (§7) |

## 2. RTTI classes (89 names survive)

| Group | Classes |
|---|---|
| Battle | `Fighter`, `FighterObject`, `FighterCamera`, `Bullet`, `BulletManager`, `BulletTrace`, `Magazine`, `Effect`, `EffectManager`, `BattleManager`, `BattleTeamManager`, `BattleObject`, `BattleObjectManager`, `BattleStage`, `BattleSprite`, `BattleBalloon`, `BillBoardSprite`, `Gauge`, `DamageMeterAnimation`, `TwinAxis` |
| Modes | `Mode`, `ModeBattle`, `ModeVSSelect`, `ModeVSEnter`, `ModeStorySelect`, `ModeResult`, `ModeContinue`, `ModeTitle`, `ModeAdv`, `ModeTutorial`, `ModeMatching`, `ModeLoad`, `ModeSaveStep`, `ModeMovie`, `ModeEndMovie`, `ModeFigure`, `ModeBuy`, `ModeFont`, `ModeSound`, `ModeController`, `ModeInitialize`, `ModeMediaInstall`, `ModeDebug`, test modes (`ModeAdvTest`, `ModeWinTest`, `ModeMovieTest`, `ModeSoundTest`, `ModeNetTestPcp`, `ModeNetTestMatching`, `ModeNetTimeOut`, `ModeInvalid`) |
| Select / UI | `CharacterSelectInput`, `CharacterSelectSendData`, `CharSelectControllManager`, `CharSelectFaceImageManager`, `SelectDrawNickName`, `MenuMap`, `MenuMapVSS`, `MenuSelectButton`, `MenuSelectWord`, `SingleAxisMenu`, `FadeScreen`, `FontManager`, `FontInstance`, `MovieFadeControll` |
| Voice / sound | `SoundTable`, `CharacterEntryVoice`, `CharacterEntryVoiceVS`, `CharacterEntryVoiceStory`, `CharacterEntryVoiceInstance`, `CharacterEntryVoiceVSInstance` |
| Net / save / memory | `AdhocUdpCore`, `SaveDataManager`, `SaveInstance`, `UtilitySaveManager`, `UtilityDialogManager`, `HeapPool`, `FixedMemoryPool`, `VariableMemoryPool` |
| Model | `NetsuGmoModelCallBack`, `DrawArraysIterator`, `AdvController`, `Meszzylinder` (a base of `Magazine`) |

There is exactly **one** `Fighter` class and one `Bullet` class. Per-character behaviour lives in data,
plus a few `char == N` branches (§6).

## 3. Fighter — key functions

| Address | Role | Evidence |
|---|---|---|
| `FUN_0006bda4` | constructor. Config record `{char, costume, weapon, kind, w4..w6}`; the first row is 15 | obs |
| `FUN_0005d4c0` | `weaponResource(char, weapon)` = `0x1b18a0 + weapon*0x50 + char*0x140` | obs |
| `FUN_0000a818` | `def(char, weapon)` = `chr.fpd + (char*4+weapon)*0x170` | obs |
| `FUN_0005d84c` | `setData(acv, acs, atp)` → `+0x25e8/+0x25ec/+0x25f0` | obs |
| `FUN_0005d5d4` | parses the four `.acv` sections | obs |
| `FUN_00063634` | selects data slot `+0x95b`, re-parses `.acs`/`.atp` | obs |
| `FUN_0005d9e4` | fills the 8 per-combo function pointers (`0x1b3e3c…0x1b3f18`); Okonogi a/c override `v0` | obs |
| `FUN_0006adcc` | **per-tick entry** (order in §4) | obs |
| `FUN_000674f4` | per tick: distance/angle to the player object → `f[0x939..0x93b]` | obs |
| `FUN_00069824` | row timer, `.acv` S1 row program, S2 record stepper | obs |
| `FUN_000654ac` | installs a row (handler, script descriptors, cursors, timer) | obs |
| `FUN_00068aa4` | **`setRow(row)`**: data-slot switch, per-character row sets, pre-hooks, then `FUN_000654ac` | obs |
| `FUN_00069070` | `setRow` + run the handler now | obs |
| `FUN_0006a240` | runs the row script; if it is exhausted, runs the handler | obs |
| `FUN_00077cd8` | **generic row runner**: priority chain guard → attack → S2 transition → command → dash → stick | obs |
| `FUN_0006f884`, `FUN_0006f9cc`, `FUN_0006f594` | row choice by gauge level, stick direction and the S3 chain table | obs |
| `FUN_00070280` | four-button command → rows 2/4/6/8 (bits `0x04/0x10/0x20/0x08` of `f+0x249c`) | obs |
| `FUN_00070484` | dash state machine (rows `0xce/0xe2` ground, `0xe0/0xec` air) | obs |
| `FUN_00074148` | S2-record-driven row/cancel decision | obs |
| `FUN_0007469c` | S2-record-driven velocity/facing/scale application | obs reads, inf meaning |
| `FUN_0006dd40` | motion selection (`+0x2486`) | obs |
| `FUN_0001af20` | motion sampling for the row timer | inf |
| `FUN_00072d68` | target/lock-on selection | obs |
| `FUN_00065a24` | "frozen?": hit-stop for rows `0x20..0x53`, pause, KO | obs |
| `FUN_0006ac00` | consumes the queued SE/effect registers | obs |
| `FUN_00068544` | plays an SE/voice id through the per-fighter table `+0x6ae8` | obs |
| `FUN_0000ccb8` | spawns an effect id at a position | obs |
| `FUN_000617dc`, `FUN_00060890` | `.atp` record for a row: `atp[map[row]]` (handler id), embedded shot records for rows 340/341 | obs |
| `FUN_0006b32c` | attack execution: picks the live slot nodes, calls `FUN_0006a8cc` | obs |
| `FUN_0006a8cc` | **hit test**: sphere around the attack bone against the victim hip point (§5) | obs |
| `FUN_000690ec` | registers a hit: power × multipliers → 0x1c-byte event in the victim's ring buffer | obs |
| `FUN_0006c4f8` | hit resolution: HP, gauge gain, reaction row, guard branch | obs |
| `FUN_0006472c` | gauge gain | obs |
| `FUN_00083f08` → `FUN_0007e964` → `FUN_0007e6a4` | per-tick input builder; Magazine charge stages | obs |

## 4. The tick, in order (`FUN_0006adcc`)

1. Player index (vcall `+0x40`); only players 0–3 run.
2. `FUN_00072d68` target; `FUN_0006f290` perspective index; `FUN_000674f4` geometry to the player object.
3. Death plane: `y <= -1111.11` (`0x1e5748`) → `setRow(0x0e)`.
4. `FUN_00065a24` frozen? → if not, the row handler `0x1b08f4[map[row]].fn`.
5. `.acs` stepper at `0x6ae90..0x6af6c`: runs codes whose time ≤ the row timer (§3 of [DATA-TABLES](DATA-TABLES.md)).
6. `FUN_0006ac00`: dispatches the SE/effect registers.
7. Input: `FUN_00083f08(f+0x18d5, f, f+0x925, &pad)`.
8. `FUN_0007e4f4` extra update; signed dt stored at `+0xc5`.

The tick is **30 Hz**, and one tick advances the row timer by 1.0 (`0x1c25a4`). Script times are whole
motion frames, so a 60 Hz port steps the fighter on every other simulation step instead of halving times.

## 5. Combat formulas (obs unless marked)

```
hit     ⟺ |worldPos(attacker slot bone) − worldPos(victim hip bone)| ≤ def[0x40+4i] + def[0x3c]
             def[0x3c] = 60 and def[0x40..0x54] = 50,45,45,45,45,60 for all 76 combos (cm)
power   = atk[0x00] × atk[0x90] × def[0x28] (1000; def[0x2c] = 250 when f[0x99d] > 0)
          × buffs DAT_00382954 / DAT_00382958 × level multipliers DAT_003828ec/f0/f4
HP      : f[0x994] -= (int)(def[0x58] × fVar28)        (FUN_0006c4f8)
maxHP   = def[0x00] × hpPercent/100: Satoshi 8500, Miyoko 8500, Okonogi 11000, Keiichi 10000
gauge   = (HP_before / maxHP) × 100 into f[0x967]; level f[0x969] at 100.0 (0x1c25d4)
hitstop : def[0x38] = 40 (FUN_00066b64); script hit-stop 3 frames (0x1c2554)
```

The victim's bone map comes from the costume table `0x1b3060[(char*9+costume)*4]` =
`{char* gmo; u8 bone[12]}`. Byte 7 is the hip point used by the hit test: Satoshi 51, Miyoko 57,
Okonogi 67, Keiichi 57.

## 6. Character-specific code

| Address | What | Touches the new three? |
|---|---|---|
| `0x5e09c`, `0x64514` | alternate per-node weapon transform via `f[0x944] = 0x1b54f4[kind]` | **Okonogi (0x12) weapons a and c**; also Shion c/d |
| `0x5d9e4` | per-combo function-pointer overrides | Okonogi a/c (`v0 = 0x5e904`); Satoshi and Miyoko use the defaults |
| `0x617dc` | `.atp` redirections | chars 7, 8 only |
| `0x62e5c`, `0x6390c` | row-set predicates | char 8 weapon b only |
| `0x65d10` | hit-spark effect `0x84` mask `0x1e8ac`, `char < 0x11` | **Satoshi (0x10)** in; Miyoko and Okonogi out |
| `0x68aa4` | `setRow` row sets around the `+0x1b14` reaction lock | chars 7, 8, 0xe, **0x11 (Miyoko)**; Miyoko's sets not fully decoded [open] |
| `0x69ef0` | per-tick re-install for one combo | none of the three |
| `0x601c8` | bullet `0xd8` spawn in rows `0xce…0x11c` | Hanyuu only |

## 7. Bullets

| Item | Address / value |
|---|---|
| `shot_data.bin` → fixed `0x18e870`, 330 × 0x14 | `FUN_0001a49c(id)`; `+0x04` speed, `+0x08/+0x0c` spread angles, `+0x12` self index |
| `bullet_attack_data.bin` → fixed `0x190470`, 764 × 0x9c | `FUN_0001b40c(id)`; `.atp` shape, `+0x90` = shot index, `+0x98` effect id |
| spawn | rows 94/95/96 handlers `FUN_00070c58/00070bec/00070b88` → `FUN_00070acc(f, 0/1/2)`; `FUN_00070cd4` → bullet 0x33; `FUN_00070910` uses muzzle bone 5 |
| pool | `FUN_0001abf4`: 50 slots × 0x90 at `engine+0x42224`; setter `FUN_0002de5c` |
| update / homing / lifetime | **[open]** |

All three new fighters' weapons use bullet ids 0/1/2 (shot indices 33/33/34) like the rest of the cast.
Their weapons differ in the melee rows.

## 8. Tables in `.rodata`

| Address | Content |
|---|---|
| `0x1b08f4` | 479 × `{handler fn, flags=0}`; 192 are pure `FUN_00077cd8` wrappers with baked rows |
| `0x1b1830`, `0x1b1840`, `0x1b1848`, `0x1b1870` | hit-reaction row tables |
| `0x1b18a0` | 19 × 4 weapon resources, stride 0x50: motion GMO, head GIM, `.acv`, `.acs`, `.atp`, voice, alt voice, SE, eff ×2, 3 attach slots `{wpn gmo, tag, bones}` |
| `0x1b3060` | 19 × 9 costume records `{gmo, bone[12]}` |
| `0x1b3e3c…0x1b3f18` | per-combo function-pointer tables |
| `0x1b54ec`, `0x1b54f0` | hit-variant masks `0x400000` / `0x800000` |
| `0x1b54f4` | per-combo weapon-transform callbacks |
| `0x1cccc` / `0x1cd004` region | the only `%s` image formats: `/gra/gim/result/%s.gim`, `/gra/gim/select/%s.gim` |

## 9. Constants

| Value | Address | Use |
|---|---|---|
| 1.0 | `0x1c25a4` | row-timer step per tick |
| 3.0 | `0x1c2554` | script hit-stop frames |
| 100.0 | `0x1c25d4` | gauge level threshold, HP percent |
| −1111.11 | `0x1e5748` | death plane |
| 1.5708 | `0x1c25ec` | hit cone in `FUN_0006c4f8` |
| −5000, π, 1e12, 9.8765e17 | data | "absent", "any angle", "never", list terminator |

There is no gravity, walk or jump constant in the fighter range. Motion comes from the `.acv` S2 records
(`FUN_0007469c`) and the root curves of the motion takes [obs absence, inf source].

## 10. Select / VS / art

| Address | Role |
|---|---|
| `FUN_000c9ed4` | loads select bust-ups into texture slots `0x0b+k`, giving roster order chr01..chr19 [obs] |
| `ModeVSSelect`, `ModeVSEnter`, `CharSelectFaceImageManager`, `SelectDrawNickName` | select/VS modes (vtables in `.data`) |

## 11. Open questions

1. The Bullet per-frame update: speed unit, homing, gravity, lifetime.
2. The physical-button mapping of `f+0x249c` bits `0x04/0x08/0x10/0x20` (behind `FUN_0007e450/0007e610/0007e67c`).
3. Where the per-weapon Magazine rates (`*(inputMapper[0x1c]) +6/+8`) are loaded from.
4. The consumer of `f+0x925[0..1]` (charge stage ready), which decides tap versus charged shot.
5. `FUN_000f7968` (`f[0x93a]/f[0x93b]`), and the exact meaning of the S2 block A/B fields.
6. `.acv` S1 flag bits beyond the durations and hit-variant bits; `.acv` S3 chain semantics.
7. Miyoko's row sets in `setRow` (`0x68aa4`); what `0x80000401` triggers.
8. Push-out between fighters (not in `Fighter`).
9. Costume byte `+14` (2/3/0/1) and `shot_data +0x00`.

**Corrections applied from `combat.md` §0** (they supersede `fighter.md`):

- The `.atp` index is the handler id, not the row.
- `+0x996` is the gauge level, not the data slot.
- `def` comes from `chr.fpd`.
- The costume table's 12 bytes are bone indices.
- Rows 94–96 are projectile rows, not run.
- `.atp` rows 340/341 are empty in all 76 files.
