# daybreak-decomp

Decompilation of **Higurashi Daybreak** (`DaybreakDX.exe`) — Twilight Frontier / 07th Expansion.

This repo contains the **reverse-engineering artifacts** produced via Ghidra + GhidraMCP, automated by an AI agent (Super Z / GLM) operating through a Cloudflare tunnel.

## Repo layout

| Path | Description |
|------|-------------|
| [`PLANO.md`](PLANO.md) | Full decompilation plan (phases, target info, future work) |
| [`PROGRESSO.md`](PROGRESSO.md) | Live status of the ongoing work |
| [`docs/RELATORIO_COMPLETO.md`](docs/RELATORIO_COMPLETO.md) | Consolidated final report (312 lines) |
| [`decompiled/`](decompiled/) | 106 individual `.c` files (one per decompiled function) |
| [`extraction_phases/`](extraction_phases/) | Raw dumps from extraction phases 1–6 |
| ↳ `01_*.txt` | Phase 1 — Reconnaissance (entry, segments, imports, strings) |
| ↳ `02_*.txt` | Phase 2 — Function mapping (all 4,092 functions) |
| ↳ `03_*.txt` | Phase 3 — Prioritization (86 key functions) |
| ↳ `05_*.txt` | Phase 5 — Call graph analysis |
| ↳ `06_*.txt` | Phase 5b — Top hubs/dispatchers decompiled |

## Target summary

| Field | Value |
|-------|-------|
| Binary | `DaybreakDX.exe` |
| Format | PE32 (x86, Windows) |
| Image base | `0x00400000` |
| Functions | 4,092 |
| Decompiled | 106 (2.6%) |
| DirectX | D3D9 + D3DX + DirectInput8 |
| Renderer | Windowed 800x600, window class `"HigurashiDaybreak"` |

## Highlights

- **WinMain** identified at `0x0064d250` (registers window class `"HigurashiDaybreak"`)
- **Scene state machine** at `LoadNextScene` (`0x00406310`) — called via function pointer table at `0x006a16c0`
- **25 D3DX functions** mapped and tagged (`directx`, `d3dx`, `graphics`)
- **Top dispatcher** `FUN_00412110` with 32 callees — candidate for main game loop

## License

Reverse-engineering artifacts produced for **research and educational purposes only**. The original binary remains property of its respective copyright holders.
