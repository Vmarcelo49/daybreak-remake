# asset-tools — offline `.dat` / `.cnv` utilities

Relocated from the retired `mvp/hook/` tree (see
[`../../docs/decisions.md`](../../docs/decisions.md) D1). `mvp/` was deleted;
maintain these utilities here.

| Script | Purpose |
|---|---|
| `extract_dat.py` | Extract a `daybreakXX.dat` archive → `data/` tree (both XOR decodes, Shift-JIS names). |
| `dat_packer.py` | Reverse: `data/` tree → rebuilt `.dat`. Documented 6-step mod workflow inside. |
| `cnv_convert.py` | `.cnv` → `.bmp` / `.wav` (header sniffing: audio vs image). |
| `cnv_pack.py` | Reverse: `.bmp` / `.wav` → `.cnv` (rejects compressed BMP, 24→32bpp promotion). |

Usage details are in each script's header. These are optional inspection and
modding utilities: the product reads `.dat` bundles and decodes CNV textures
and PCM audio at runtime in `../../foundation/src/assets/` and
`../../foundation/src/audio/`. Offline conversion is not required to play.
Keep the original `.X` models; do not introduce a conversion pipeline (D3).
