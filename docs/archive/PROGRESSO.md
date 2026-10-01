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
├── PLANO.md, PROGRESSO.md
├── docs/                          (CONTEXT, PLANO_RECOMP, AGENT_*, RELATORIO_*, conventions)
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
└── extraction_phases/            # dados brutos das fases 1-6 (01_*.txt — 06_*.txt)
```

## Túnel MCP — pode ser fechado

Todas as fases que precisavam de MCP (1-12, exceto 10 e 11) estão concluídas. O trabalho restante pode ser feito 100% offline.

URL atual: `https://jewel-illustrations-have-willing.trycloudflare.com` (pode encerrar).

---

## Fase 11 — Análise de Multiplayer/Network (CONCLUÍDA)

**Stack**: DirectPlay 8 (COM-based, via CoCreateInstance)
**Cluster**: 27 funções em 0x0065f180 - 0x00660fc0
**Funções nomeadas**: 16 (11 high, 5 medium) — ver `binary_data/network_analysis/candidates.json`

### Descobertas-chave

- **3 modos**: Client, Server, Peer (todos usam DirectPlay 8)
- **8 slots de tick counter** — sugere até 8 players
- **Threads de polling** com `WaitForSingleObject(500ms)`
- **Server thread** com prioridade `THREAD_PRIORITY_TIME_CRITICAL`
- **Protocolo de aplicação** ainda não mapeado (cluster `FUN_006604xx` precisa de análise)

### Arquivos

- `binary_data/network_analysis/FASE11_REPORT.md` — relatório completo com diagrama
- `binary_data/network_analysis/candidates.json` — 16 sugestões prontas para o agente local promover para `symbols/functions.json`

### Próximos passos

| # | Quem | Ação |
|---|------|------|
| 1 | Agente local | Promover 11 sugestões `high confidence` de `candidates.json` para `symbols/functions.json` |
| 2 | Agente local | Decompilar `FUN_006604xx` (GameSend functions) |
| 3 | Operador | Revisar e promover as sugestões para `reviewed` |

**Nota**: Este trabalho foi feito 100% offline, sem MCP. As sugestões estão em arquivo separado (`candidates.json`) para NÃO conflitar com o trabalho do agente local em `symbols/functions.json`.

---

## Fase 11b — Mapeamento do Menu de Multiplayer (CONCLUÍDA)

**Função chave**: `FUN_00412ac0` (NetworkMenuDispatcher) — switch de 10 cases
**Resultado**: identifiquei TODO o fluxo de UI de multiplayer

### 10 cases do NetworkMenuDispatcher mapeados

| Case | Nome | Função |
|------|------|--------|
| 0 | MainMenu | Seleção de modo (host/client/char/stage/settings/back) |
| 1 | SubMenu | Submenu genérico |
| 2 | CharacterSelect | Seleção de personagem (16 chars × 5 sub-modes, 8 slots) |
| 3 | StageSelect | Seleção de stage (1-9) |
| 4 | PortConfig | Configura porta (5 dígitos, máx 65535) |
| 5 | ClientIPEntry | Entrada de IP (4 octetos × 3 dígitos) |
| 6 | ServerSelectFromList | Seleção de server salvo (parse 'host:port') |
| 7 | Connecting | Aguardando conexão (timeout 1800 ticks ~15s) |
| 8 | ConnectionSuccess | Pós-conexão |
| 9 | SettingsToggle | Toggle de config |

### 10 novas funções identificadas (adicionadas a candidates.json)

- `NetworkMenuDispatcher` (00412ac0) — high
- `ConnectToServer` (0065f9e0) — high
- `SaveConfigFile` (006488d0) — high (descobriu `config.dat`!)
- `LoadConfigFile` (006486c0) — high
- `AbsInt` (0066b65c) — high
- `WcslenWrapper` (0066cec4) — high
- `SetNetworkMessageCallback` (0065f780) — medium
- `CancelPendingConnection` (0065fae0) — medium
- `InitChatUI` (00645840) — medium (carrega data/chat/*.bmp)
- `CheckConnectionSuccess` (004146e0) — medium

### Total acumulado: 26 sugestões (21 high, 5 medium)

Ver `binary_data/network_analysis/FASE11B_REPORT.md` para detalhes.
