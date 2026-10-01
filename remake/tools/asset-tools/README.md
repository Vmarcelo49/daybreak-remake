# asset-tools — offline `.dat` / `.cnv` utilities

Verbatim copies from the frozen `mvp/hook/` (see `docs/decisions.md` D1 —
`mvp/` is read-only; if these need changes, change them **here**).

| Script | Purpose |
|---|---|
| `extract_dat.py` | Extract a `daybreakXX.dat` archive → `data/` tree (both XOR decodes, Shift-JIS names). |
| `dat_packer.py` | Reverse: `data/` tree → rebuilt `.dat`. Documented 6-step mod workflow inside. |
| `cnv_convert.py` | `.cnv` → `.bmp` / `.wav` (header sniffing: audio vs image). |
| `cnv_pack.py` | Reverse: `.bmp` / `.wav` → `.cnv` (rejects compressed BMP, 24→32bpp promotion). |

Usage details are in the script headers and the old `mvp/hook/README.md`.
Runtime (in-game) CNV decoding is **not** implemented — convert offline
with these, or see the M8 texture-provider note in `docs/port-from-mvp-plan.md` P3.2.
