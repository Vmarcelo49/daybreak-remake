# PSP research tools

Small Python readers and measurement scripts written for issue #91 (the PSP fighters). They are
kept because they read the PSP data without any of the remake's code, which makes them the fastest
way to answer a question about it later.

They are **not** part of the build and nothing runs them automatically. They need the owner's ISO
and are launched from a folder of extracted files.

| Script | What it does |
|---|---|
| `psppack.py`, `get_file.py`, `enumerate_paths.py`, `classify.py` | read `gzpack.pck` from the ISO, name its entries, classify every payload |
| `gim.py`, `gim_report.py`, `extract_art.py`, `export_art.py` | GIM (and TGA/PNG) to PNG; the padded-pitch rule is in `docs/psp/research/RESOURCES.md` §8 |
| `gmo.py`, `gmo_tree.py`, `gmo_report.py`, `vertex_census.py` | GMO chunk tree, meshes, motions; wraps `tools/asset-tools/gmo_blender.py` |
| `acs.py`, `acv.py`, `atp.py`, `rowtable.py`, `dump_rows.py`, `cov_codes.py`, `rows.py`, `dump_rows.py` | the three moveset tables |
| `eboot.py`, `mips.py`, `find_calls.py`, `scan_imm.py` | read the decrypted `EBOOT.BIN`; `scan_imm.py` finds every reader/writer of a struct offset |
| `xanim.py`, `pc_frametable.py` | PC `.X` animation sets and `NN.dat` frame tables |
| `takecore.py`, `match_takes.py`, `build_take_map.py` | the failed per-set similarity study (`docs/psp/research/notes/take_map.md`) |
| `measure_takes.py`, `render_takes.py`, `make_sheets.py`, `detail_takes.py` | Blender filmstrips of every motion take |
| `write_labels.py`, `take_inventory.py`, `index_agreement.py` | the per-take labels (`docs/psp/research/notes/take_labels.tsv`) |
| `pck_report.py`, `tables_report.py` | container and format inventories |

The measured results they produced are in [`docs/psp/research/notes/`](../../../docs/psp/research/notes/);
the curated summary is [`docs/psp/research/`](../../../docs/psp/research/README.md).
