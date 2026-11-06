# Where the PSP evidence lives

Issue #91 is **parked** (see [`../PSP-CHARACTERS-WORKLOG.md`](../PSP-CHARACTERS-WORKLOG.md)), so
this page says what was kept, where, and how to rebuild the rest.

## Tracked here

| Path | What |
|---|---|
| [`notes/`](notes/) | the full study notes behind the summaries: `formats.md`, `fighter.md`, `combat.md`, `art.md`, `integration.md`, `take_labels.md`, `take_map.md` |
| [`notes/rowtable.tsv`](notes/rowtable.tsv) | per (weapon, row): handler, baked runner arguments, `.atp` numbers, both scripts — the machine-readable spine of the row study |
| [`notes/take_labels.tsv`](notes/take_labels.tsv) | every PSP motion take of `chrm17/18/19` and `chrm02`, labelled by eye with confidence |
| [`notes/take_profile_*.tsv`](notes/) | posed root/feet/pitch/hands/air measurements per take |
| [`notes/pack_paths.txt`](notes/pack_paths.txt) | the 7305 named pack entries with sizes and sha256 |
| [`notes/gmo_census.tsv`](notes/gmo_census.tsv), [`notes/vertex_census.txt`](notes/vertex_census.txt) | GMO inventory and every vertex format in the pack |
| [`../../asset-tools/psp-research/`](../../../tools/asset-tools/psp-research/) | the Python readers that produced all of it |

Nothing here is game data: these are measurements, paths, hashes and our own scripts.

## Local only (never tracked; regenerate or keep on disk)

| Kept at `local-data/harness/psp/` | Size | Why it stays out |
|---|---|---|
| `decomp/`, `ghidra-proj/` | 27 + 56 MB | decompiled C of the PSP executable |
| `dump/`, `psp-data/`, `trackD-psp-data/` | 97 + 23 + 135 MB | inflated PSP files — the rights holders' data |
| `art/`, `png/`, `captures/` | 4 + 6 + 9 MB | decoded art and captures of our build over the game's art |
| `takes/` | 166 MB | rendered filmstrips of the game's motion takes |
| `chibi/` | 385 MB | the AI chibi exploration, paused; the owner continues it |

Regenerating the two heavy ones:

- **Decompile**: decrypt `PSP_GAME/SYSDIR/EBOOT.BIN` (LBA 48) with John-K `pspdecrypt`, import it
  into Ghidra 12.2 with the kotcrab `ghidra-allegrex` extension, seed functions from `.eh_frame`
  (vaddr `0x16a104`, `0x20e3c`, 4190 FDEs → 6441 functions), then dump. Steps in
  [`../research/README.md`](README.md).
- **Inflated files and art**: `psppack.py` / `get_file.py` for the pack, `gim.py` for images,
  `gmo.py` for models, `render_takes.py` for the filmstrips.
- **The converted tree**: `daybreak --extract-psp=<iso> --psp-data=<dir> --install=<game>`.

A snapshot of this folder was also packed outside the repository
(`~/daybreak-psp-evidence-*.tar.zst`) so it survives the worktrees being removed.
