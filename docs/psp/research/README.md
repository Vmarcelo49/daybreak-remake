# PSP version — research reference

What the static study of *Higurashi Daybreak Portable Mega Edition* (PSP, ULJM05557) established. It
was written for issue #91, which ports Satoshi, Miyoko and Okonogi, and for anyone who later needs
more from the PSP data.

| File | Covers |
|---|---|
| [RESOURCES.md](RESOURCES.md) | ISO and pack layout, path naming, PSP↔PC numbering, per-character files, 2D art, container formats |
| [DATA-TABLES.md](DATA-TABLES.md) | `.acs`, `.acv`, `.atp`, `chr.fpd`, bullet tables, row vocabulary |
| [CODE-MAP.md](CODE-MAP.md) | executable sections, RTTI classes, key functions, tick order, formulas, open questions |

How the port uses this is in [`../../PSP-CHARACTERS-WORKLOG.md`](../../PSP-CHARACTERS-WORKLOG.md) and the
other files in `docs/psp/`.

## Evidence tier

Everything here comes from **static reading of the PSP build**: its data files and a decompile of its
executable. Nothing was observed running, on PSP or in an emulator. It says nothing about the PC
game. Where a field's meaning is a reading rather than a proof, the tables say so.

## The dump studied

| Item | Identity |
|---|---|
| ISO | 931,201,024 bytes, sha256 `170b8a8e1aa546f549809243d68dd4c34e33f69e682ab669e820180830a7160c`, volume `HDBPME_101` |
| Decrypted `EBOOT.BIN` | 2,711,572 bytes, sha256 `80363ff749cfb7aee216f8390eff6f5a873b5d51c2dcf804be6cd30094608597` |

The port's extractor checks each needed file against a hash list, not the ISO hash, so any good dump works.

## Reproducing the tool chain

No root access is needed.

1. **JDK 25** (Temurin) — Ghidra 12.2 refuses older JDKs.
2. **Ghidra 12.2** + **kotcrab `ghidra-allegrex` v21.6** unzipped into `Ghidra/Extensions/`. It provides
   the Allegrex language and a PSP PRX loader.
3. **John-K `pspdecrypt`**, built from source (`make`, needs zlib and OpenSSL headers).
4. Copy `EBOOT.BIN` out of the ISO (LBA 48, 2,711,920 bytes) and run `pspdecrypt EBOOT.BIN -o EBOOT.dec`.
5. `analyzeHeadless <proj> <name> -import EBOOT.dec`; the loader picks "PSP Executable (ELF)" and Allegrex.
6. Seed functions from `.eh_frame` (vaddr `0x16a104`, size `0x20e3c`): 4190 FDEs with absolute
   `pc_begin`. This takes the function count from 3984 to **6441**, and to 855 in the fighter range
   `0x5d000–0x7c000`.
7. Address rule: the PRX image is at 0, so **file offset = vaddr + 0xc0**.

The Ghidra scripts used (a dump-all decompiler and the `.eh_frame` seeder) are short. They are kept
with the local notes.

## Local material (not tracked)

Kept under `local-data/harness/psp/`. It holds nothing from the game in git.

| Path | What |
|---|---|
| `notes/formats.md`, `fighter.md`, `combat.md`, `art.md`, `integration.md` | the full study notes these files summarise |
| `notes/pack_paths.txt` | every named pack path with size and sha256 |
| `notes/rowtable.tsv` | per (weapon, row): handler, baked runner arguments, `.atp` numbers, both scripts |
| `scripts/psppack.py`, `get_file.py` | read the pack from the ISO |
| `scripts/enumerate_paths.py`, `classify.py` | name the pack's hashes |
| `scripts/gim.py`, `extract_art.py`, `export_art.py` | GIM/TGA → PNG |
| `scripts/gmo.py`, `gmo_tree.py`, `gmo_report.py`, `vertex_census.py` | GMO via the repository's `tools/asset-tools/gmo_blender.py` |
| `scripts/acs.py`, `acv.py`, `atp.py`, `rowtable.py`, `dump_rows.py`, `cov_codes.py` | moveset tables |
| `scripts/eboot.py`, `mips.py`, `find_calls.py`, `scan_imm.py` | executable reading helpers |
| `decomp/` | one decompiled C file per function, with `_index.txt` |

## Known contradictions between the notes, resolved

- `fighter.md` read rows 94/95 as run. `combat.md` shows they are **projectile rows**.
- `fighter.md` indexed `.atp` by row. The index is the **handler id** (`S4[row]`).
- `fighter.md` had `+0x996` as the data slot. It is the **gauge level**; the slot is `+0x95b`.
- `formats.md` called `.acv` section 1 "hit geometry". `combat.md` shows those records drive motion and
  transitions. The hit volume is a sphere from `chr.fpd` around a bone ([CODE-MAP](CODE-MAP.md) §5).
