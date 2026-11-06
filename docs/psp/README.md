# The PSP version, and where this port touches it

*Higurashi Daybreak Portable Mega Edition* (PSP, ULJM05557) is the only version that has
Satoshi Houjou, Miyoko Tanashi and Okonogi as playable fighters. This document is the map:
what the disc holds, how names and numbers work, where the extractor puts things, and which
document answers the next question. The deep studies are beside it — this is the entry point.

Nothing from the disc is tracked. The player supplies their own copy, the extractor reads it
and writes `psp-data/` beside the executable, and the repository holds only the file list
(`assets/psp/manifest.txt`: paths, sizes and SHA-256).

## The disc

| Layer | What it is |
|---|---|
| Image | ISO 9660, one volume descriptor, no Joliet, no Rock Ridge. The game's names are uppercase with `;1` versions |
| `PSP_GAME/USRDIR/` | the data root; `/PSP_GAME/SYSDIR/EBOOT.BIN` is the executable |
| `_pack/gzpack.pck` | **one archive with almost everything in it**, 326,807,872 bytes |

The pack is its own index:

```
u32 count                     (10772 on the dump studied)
count × { u32 nameHash, u32 packedBytes, u32 offset, u32 unknown }   rows sorted by nameHash
gzip payloads at `offset` from the first byte of the pack
nameHash = zlib.crc32(path, 0xFFFFFFFF)     path without a leading slash
```

So a file is found by hashing its name: the pack carries **no readable name table**. Three
consequences are worth knowing before writing anything against it:

* There are no format strings for character paths. Every `g3d/chr17a.gmo`, `activity/chr17a.acs`
  is a literal in the executable's `.rodata`, pointed at by a per-(character, weapon) resource
  table; only `/gra/gim/select/%s.gim`, `/gra/gim/result/%s.gim`, `/se/…` and `/adv/…` are built
  at run time.
* A path whose name hash is unknown is unreadable until somebody guesses the name. 7305 of the
  10772 entries are named; the rest are voices, adventure scripts and small UI art the fighters
  do not need.
* `csize` is the packed size, and the payload is a plain gzip stream. Nothing is encrypted.

`docs/psp/research/RESOURCES.md` has the full layout, the `_pack` variant containers
(`activity/chrNNx_voice.pck` and friends) and the resolved-path inventory.

## Names and numbers

**The PSP numbers its cast differently from the PC**, and in code it is 0-based:

| PSP | Fighter | PC `kCharacterDirs` index | | PSP | Fighter | PC index |
|---|---|---|---|---|---|---|
| 01 | Rena | 0 | | 11 | Takano | 7 |
| 02 | Keiichi | 2 | | 12 | Chie | 11 |
| 03 | Mion | 1 | | 13 | Kasai | 12 |
| 04 | Rika | 4 | | 14 | Akane | 13 |
| 05 | Satoko | 3 | | 15 | Natsumi | 15 |
| 06 | Shion | 5 | | 16 | Hanyu | 14 |
| 07 | Irie | 10 | | **17** | **Satoshi** | **16** |
| 08 | Akasaka | 9 | | **18** | **Miyoko** | **17** |
| 09 | Ohishi | 8 | | **19** | **Okonogi** | **18** |
| 10 | Tomitake | 6 | | | | |

The three new fighters are roster indices **16, 17 and 18** in this port (plan decision D-1).
The PC indices in the table are only for finding the closest PC fighter: the PSP order is not
the PC order, and a port that used the PC index as the PSP number would read the wrong files.
The mapping was measured by matching `.atp` attack records against the PC's `.dat` combat
records, and confirmed independently by byte-identical weapon models.

Per-fighter files, PSP number `NN`, weapon slot `x` = `a`..`d`, costume `k`:

| Path | What it is |
|---|---|
| `g3d/chrNNk.gmo` | one mesh file per costume: Satoshi 5 (`0`..`4`), Miyoko 7, Okonogi 3 |
| `g3d/chrmNN.gmo` | skeleton and every motion: 76 takes, 68 bones (Satoshi) or 77 |
| `g3d/chrtNN.gim` | the head pictures: eight expressions, hair, scalp — stored twice |
| `activity/chrNNx.acs`, `.acv` | the row event list and the hit/shape tables |
| `assault/chrNNx.atp` | 350 attack records |
| `activity/chrNNx_voice.pck`, `_se.pck`, `_eff.pck` | voices, sound effects, effect models |
| `g3d/wpnNNx.gmo` | weapon models; **Miyoko has none at all**, and `wpn17d`/`wpn19dr1/2` are copies of Keiichi's bat and Shion's whip |
| `gra/gim/select/…` | select bust-up, VS face, name plates, cut-ins (see `FRONTEND-ART.md`) |

Shared: `activity/static_param.bin`, `bin/{bullet_attack_data,com_param,gauge_data,shot_data}.bin`,
`bin/chr.fpd`.

## What the port does with it

```
player's ISO ──> daybreak --extract-psp <iso>  ──> psp-data/
                    │  raw files, hash-checked        psp/<pack path>   as the pack stores it
                    │  converters                     data/<name>/…     the remake's own formats
                    ▼
        renderer + simulation read psp-data/ through the same loaders as the PC cast
```

```bash
# everything at once: the raw files, the converted models, and the frame tables
daybreak --extract-psp /path/to/Higurashi_Daybreak_Portable.iso \
         --psp-data /somewhere/psp-data --install /path/to/Higurashi-Daybreak
```

`--install` is what the moveset converter needs: it starts from the PC dispatch combo's own
frame table. Without it the models are still written.

```
psp-data/
  psp/…                      every collected file, exactly as the disc stores it
  data/<name>[_B..]/00.X     the fighter's model: PSP skeleton, meshes, all 76 takes
  data/<name>[_B..]/*.cnv    its textures, decoded from the PSP's TGA and GIM
  data/<name>/0W.dat         the frame table for weapon W
  data/item/1NN.dat          the weapon item
  data/select/, data/win/    the front-end sheets (`FRONTEND-ART.md`)
```

Nothing is converted at run time, so every file is inspectable and diffable, and the
simulation and the renderer read the same bytes off the same mount.

## Where the rest is written down

| Question | Document |
|---|---|
| The disc, the pack, every container, the full path inventory | [`research/RESOURCES.md`](research/RESOURCES.md) |
| `.acs`/`.acv`/`.atp`, `chr.fpd`, row vocabulary | [`research/DATA-TABLES.md`](research/DATA-TABLES.md) |
| The executable: sections, RTTI classes, the `Fighter` tick | [`research/CODE-MAP.md`](research/CODE-MAP.md) |
| How a PSP fighter fights, and the port rules that make it | [`COMBAT.md`](COMBAT.md) |
| Select, VS and result art: the contract for the sheets | [`FRONTEND-ART.md`](FRONTEND-ART.md) |
| GMO → `.X`: bone names, take order, scale, textures | [`MODEL-CONVERSION.md`](MODEL-CONVERSION.md) |
| Why any of this is being done, and the decisions behind it | [`../PSP-CHARACTERS-PLAN.md`](../PSP-CHARACTERS-PLAN.md), [`../PSP-CHARACTERS-WORKLOG.md`](../PSP-CHARACTERS-WORKLOG.md) |

The raw studies that these documents summarise — a Ghidra dump of the decrypted executable, the
per-file inventories, the art contact sheets and the Python readers used to measure everything —
are kept locally and are not tracked.

## Checking it

```bash
# tier 4: the whole conversion, every file through both readers, all 76 sets sampled
DAYBREAK_PSP_ISO=/path/to/the.iso ctest --test-dir build/linux -R psp_model_test --output-on-failure

# tier 5: what a converted fighter looks like, beside a PC one
daybreak --headless --no-audio --install=<game> --model=<psp-data>/data/okonogi/00.X \
         --no-anim --camera=front --frames=10 --out=okonogi.ppm
daybreak --headless --no-audio --install=<game> --model=<game>/data/keiichi/00.X \
         --no-anim --camera=front --frames=10 --out=keiichi.ppm
```

`--camera=front` puts the eye on −Z, which is the side every PC rig faces. A converted PSP
fighter that shows its back there is facing the wrong way — that is exactly how the half turn
in `MODEL-CONVERSION.md` was found.

## What is still missing

* **Miyoko has no weapon model.** No `wpn18*` exists on the disc; her four weapons are invisible
  props until something is invented for them.
* **Weapon GMOs are unread.** They use an unweighted vertex type no GMO reader in this tree
  handles, so nothing hangs a weapon in a hand yet.
* **Expressions.** The model's four materials are static; switching the face picture needs the
  texture-remap events that come with the frame tables.
* **Hit geometry on the PSP side.** `.acv`'s 164-byte records are the hit windows, but shape and
  anchor are not decoded; the converted tables re-anchor them on a bone (`COMBAT.md` §2).
* **The PSP's own motion per row** is not decoded either, so the pose a row plays is a port rule.
* **Voices.** The `.pck` containers hold plain VAG audio and are collected, but nothing plays
  them yet.
