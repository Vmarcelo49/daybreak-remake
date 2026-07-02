# Progresso da Análise — DaybreakDX.exe

Última atualização: 2026-07-02 (Revisão 3)
Repo: https://github.com/giovanni-marchisio/daybreak-decomp

## Status: ✅ Pipeline completo + 2 agentes prontos para trabalho paralelo

## Métrica oficial

Ver `progress/coverage.json` (gerado por `tools/coverage_report.py`).

| Métrica | Snapshot |
|---------|----------|
| Funções no binário | 4,092 |
| Funções decompiladas | 3,191 (77.98%) |
| Revisadas (reviewed/locked) | 5 (0.16%) |
| Com sugestão | 1 |
| Unreviewed | 3,184 |
| Erros | 0 |

## Estrutura final

```
daybreak-decomp/
├── PLANO.md                       (extração/análise — rev 3)
├── PLANO_RECOMP.md                (pipeline de recomposição)
├── AGENT_HANDOFF.md               (instruções para segundo agente)
├── PROGRESSO.md                   (este arquivo)
├── RELATORIO_COMPLETO.md
├── INDEX.md / INDEX.json          (gerados pelo CI)
│
├── decompiled/                    (3,191 .c brutos)
├── recomp/                        (3,191 .c GERADOS — não editar)
├── symbols/                       (FONTE DE VERDADE)
│   ├── functions.json             (3,175 entradas)
│   ├── types.json
│   └── notes.json
├── progress/
│   ├── coverage.json              (MÉTRICA OFICIAL)
│   └── last_ingest.json
├── tools/                         (pipeline scripts)
├── docs/conventions.md
├── .clang-format
│
├── binary_data/                   (dump bruto do MCP)
│   ├── functions/ (3,087 JSONs)
│   ├── strings/ types/ callgraph/ segments/
│   └── *.txt (imports, exports, globals, etc.)
│
└── 01_*.txt — 06_*.txt            (dados brutos das fases 1-6)
```

## Próximos passos

| # | Quem | Ação |
|---|------|------|
| 1 | Agente de extração (Super Z #1) | Fase 9: analisar tabela em 0x006a16c0 |
| 2 | Agente local (Super Z #2) | Processar lotes de unreviewed (começar pelos hot_spots) |
| 3 | Operador | Promover suggested → reviewed após análise |
| 4 | Ambos | Fase 11: análise de multiplayer/network |

Ver `AGENT_HANDOFF.md` para instruções detalhadas do segundo agente.
