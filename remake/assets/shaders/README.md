# shaders — D3DX effects extracted from DaybreakDX.exe

Verbatim copies from the frozen `mvp/shaders/` (see `docs/decisions.md` D1).

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
Loader: `src/render/effect_system.*` (P3.1 of `docs/port-from-mvp-plan.md`).
