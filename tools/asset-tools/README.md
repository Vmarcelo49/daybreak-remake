# Offline asset utilities

These retained helpers support archive inspection, modding, and regeneration of
the foundation's generated CP932 table. The former `mvp/` relocation is recorded
in [`../../docs/decisions.md`](../../docs/decisions.md) D1.

| Script | Purpose |
|---|---|
| `extract_dat.py` | Extract a `daybreakXX.dat` archive → `data/` tree (both XOR decodes, Shift-JIS names). |
| `dat_packer.py` | Reverse: `data/` tree → rebuilt `.dat`. Documented 6-step mod workflow inside. |
| `cnv_convert.py` | `.cnv` → `.bmp` / `.wav` (header sniffing: audio vs image). |
| `cnv_pack.py` | Reverse: `.bmp` / `.wav` → `.cnv` (rejects compressed BMP, promotes 24bpp to 32bpp). |
| `gen_sjis_table.py` | Regenerate `foundation/src/assets/sjis_table.h`; `--full` uses Python's CP932 codec. Asset-scanning mode imports `x2txt.py`, which is absent from the current tree. |

Usage details are in each script's header. These offline utilities are optional:
the product reads `.dat` bundles and decodes CNV textures and PCM audio at
runtime in `../../foundation/src/assets/` and `../../foundation/src/audio/`.
Keep the original `.X` models; do not introduce a conversion pipeline (D3).
