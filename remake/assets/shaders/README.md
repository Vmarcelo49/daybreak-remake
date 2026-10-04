# shaders — D3DX effects extracted from DaybreakDX.exe

Relocated verbatim from the retired `mvp/shaders/` tree (see
[`../../docs/decisions.md`](../../docs/decisions.md) D1). `mvp/` was deleted.

10 compiled D3DX effect blobs loaded by `CreateAllShaders`
(`FUN_0064ff80`; original `.rdata` addresses in the old
`mvp/shaders/README.md`). All start with the effect signature
`01 09 FE FE`.

| File | Size |
|---|---|
| `effect_0.bin` … `effect_9.bin` | 3436, 3640, 812, 1964, 1744, 1920, 1932, 3436, 1172, 1164 |

Note: `effect_0` and `effect_7` share the same size (3436) but differ in
content (different hashes) — both slots are kept.

Copyright Twilight Frontier / 07th Expansion — fair use for
interoperability; do not redistribute separately.
Loader: the DX9 `src/render/effect_system.*` was deleted in the Phase 5 cutover;
these dumps are kept as evidence of the original's effect bytecode. The WebGPU
product uses its own WGSL shaders in `../../foundation/src/shaders/`. These
blobs are not runtime dependencies.
