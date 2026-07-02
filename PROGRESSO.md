# Progresso da Análise — DaybreakDX.exe

Última atualização: 2026-07-02 (pós-Fase 9 + Fase 12)
Repo: https://github.com/giovanni-marchisio/daybreak-decomp

## Status: ✅ Fases 9 e 12 CONCLUÍDAS — túnel MCP pode ser fechado

## Métrica oficial

Ver `progress/coverage.json` (gerado por `tools/coverage_report.py`).

| Métrica | Snapshot |
|---------|----------|
| Funções no binário | 4,092 |
| Funções decompiladas | 3,191 (77.98%) |
| **Revisadas/locked** | **5** (0.16%) |
| **Com sugestão (agent:extraction)** | **18** |
| Unreviewed | 3,168 |
| Erros | 0 |

## Fase 9 — RESUMO

**Hipótese original**: `0x006a16c0` conteria uma tabela de scene handlers.

**Veredito**: ❌ **Hipótese DISPROVED** — `0x006a16c0` é uma **struct de configuração** (`SceneDispatcherConfig`), não uma tabela de ponteiros.

**Conteúdo real**:
- Offset 0: ponteiro para `LoadNextScene` (dispatcher)
- Offsets 4-63: floats de layout de UI (20.0, 1.0, 400.0, 200.0, 510.0, 100.0, ..., 600.0=altura janela)
- Offset 64+: strings de paths de assets (`data/select/bg00.bmp`, etc.)

**Estrutura de scene dispatch real**: switch case dentro de `LoadNextScene` em `pGameState+0x2e18` (current_scene_id), com 4 cases identificados:
- **case 0**: Title screen / main menu
- **case 1**: Character select
- **case 2**: VS loading screen
- **case 3**: Battle init (transita para scene 8)

**13 FUN_* mapeadas** com sugestões de nome (3 high, 7 medium, 3 low confidence):
- `PlayBGM` (high) — chamada com `"data/bgm/title.ogg"`
- `EnterGameCriticalSection` / `LeaveGameCriticalSection` (high) — wrappers Win32
- `GetRandomNumber`, `LoadStage`, `UpdateTitleScreen`, `SetSceneState`, `InitPlayerSlot`, `UpdateCharacterSelect`, `IsKeyPressed` (medium)
- `TogglePauseFlag`, `UpdateInput`, `UpdateInputState` (low)

Ver `binary_data/scene_table/FASE9_REPORT.md` para detalhes.

## Fase 12 — RESUMO

Foram rodadas 3 ferramentas anti-analysis via MCP:
- `detect_malware_behaviors` → 1 finding (false positive do CRT)
- `find_anti_analysis_techniques` → 86 findings (maioria false positive)
- `extract_iocs_with_context` → 156 IOCs (todos assets do jogo)

**Veredito**: ✅ binário limpo, sem anti-debug intencional.

Ver `binary_data/anti_analysis/FASE12_REPORT.md` para detalhes.

## Próximos passos

| # | Quem | Ação |
|---|------|------|
| 1 | Agente local (Super Z #2) | Processar lotes de unreviewed (começar pelos hot_spots) |
| 2 | Operador | Promover sugestões `agent:extraction` para `reviewed` conforme revisar |
| 3 | Operador | Fechar túnel MCP — não é mais necessário |
| 4 | Ambos | Fase 11: análise de multiplayer/network (offline) |

## Estrutura final

```
daybreak-decomp/
├── PLANO.md, PLANO_RECOMP.md, AGENT_*.md, CONTEXT.md, PROGRESSO.md
├── decompiled/                    (3,191 .c brutos)
├── recomp/                        (3,191 .c GERADOS)
├── symbols/                       (FONTE DE VERDADE)
│   ├── functions.json             (3,175 entradas, 23 com sugestão)
│   ├── types.json                 (hipóteses: GameState, SceneDispatcherConfig)
│   └── notes.json
├── progress/coverage.json
├── tools/                         (pipeline)
├── binary_data/
│   ├── functions/ (3,087 JSONs)
│   ├── strings/ types/ callgraph/
│   ├── segments/                  (Headers.bin)
│   ├── scene_table/               ⭐ NOVO: Fase 9 — dump 256 bytes + 13 callees
│   │   ├── 0x006a16c0_256bytes.bin
│   │   ├── FASE9_REPORT.md
│   │   └── callees/ (13 .c individuais)
│   └── anti_analysis/             ⭐ NOVO: Fase 12 — 3 reports
│       ├── malware_behaviors.txt
│       ├── anti_debug.txt
│       ├── iocs.txt
│       └── FASE12_REPORT.md
└── 01_*.txt — 06_*.txt
```

## Túnel MCP — pode ser fechado

Todas as fases que precisavam de MCP (1-12, exceto 10 e 11) estão concluídas. O trabalho restante pode ser feito 100% offline.

URL atual: `https://jewel-illustrations-have-willing.trycloudflare.com` (pode encerrar).
