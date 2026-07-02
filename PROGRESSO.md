# Progresso da Análise — DaybreakDX.exe

Última atualização: 2026-07-02
Repo: https://github.com/giovanni-marchisio/daybreak-decomp

## Status atual: ✅ Fases 1-7 CONCLUÍDAS + deploy no GitHub

## Resumo rápido

| Métrica | Valor |
|---------|-------|
| Funções no binário | 4,092 |
| Funções decompiladas | **106 / 4,092** (2.6%) |
| Código C gerado | ~2.2 MB em 106 arquivos |
| Tags aplicadas | 35+ |
| Plate comments | 3 |
| Erros | 0 |

## Estrutura deste diretório

```
daybreakdx-re/
├── PROGRESSO.md                  ← você está aqui
├── RELATORIO_COMPLETO.md         ← relatório final consolidado
├── decompiled/                   ← 106 arquivos .c individuais
│   ├── entry.c                   (entry point CRT)
│   ├── FUN_0064d250_entry_sub.c  (WinMain)
│   ├── CommonInit.c
│   ├── LoadNextScene.c
│   ├── D3DX*.c                   (25 funções DirectX)
│   └── FUN_*.c                   (top hubs/dispatchers)
├── 01_*.txt                      (reconhecimento inicial)
├── 02_*.txt                      (mapeamento de funções)
├── 03_*.txt/json                 (priorização)
├── 04_*.json                     (progresso de decompilação)
├── 05_*.txt                      (análise de call graph)
└── 06_*.txt                      (top hubs/dispatchers decompilados)
```

## Fases executadas

- [x] **Fase 1**: Reconhecimento (imports, exports, entry, segments, strings)
- [x] **Fase 2**: Mapeamento — listar todas as 4,092 funções
- [x] **Fase 3**: Priorização — selecionar 86 funções-chave
- [x] **Fase 4**: Decompilação das 86 funções em batches
- [x] **Fase 5**: Análise de call graph completo
- [x] **Fase 5b**: Decompilação dos top 10 dispatchers e top 10 hubs
- [x] **Fase 6**: Documentação (tags + plate comments nas funções-chave)
- [x] **Fase 7**: Relatório consolidado

## Próximos passos planejados

- [ ] Decompilar as ~4,000 FUN_* restantes (consumo estimado: ~6h)
- [ ] Analisar tabela de scene handlers em `0x006a16c0`
- [ ] Renomear FUN_* identificadas no Ghidra
- [ ] Buscar strings de network/multiplayer
- [ ] Decompilar maiores dispatchers restantes

## Funções-chave já documentadas

| Endereço | Nome | Tag(s) | Plate comment |
|----------|------|--------|---------------|
| `0x0066c906` | `entry` | entry-point, program-start, crt | — |
| `0x0064d250` | `FUN_0064d250` (WinMain) | win-main, window-creation | ✅ |
| `0x00406310` | `LoadNextScene` | scene-manager, state-machine | ✅ |
| `0x00543c70` | `CommonInit` | init, bootstrap | ✅ |
| `0x00669cd2`-`0x00669d62` | 25 funções D3DX | directx, d3dx, graphics | — |
| `0x00412110` | `FUN_00412110` (top dispatcher) | dispatcher, call-graph-hub | — |

## Como acompanhar pelo navegador

Abra no navegador:
```
https://ryan-alcohol-placement-suites.trycloudflare.com/?token=c08ee2c9cc3dad43122b9a933150cc62b9930abd65c64e368e775a3ce6d002c7
```

Navegue para `daybreakdx-re/` e clique em qualquer arquivo `.c` ou `.md` para ver o conteúdo.

## Como baixar tudo de uma vez

```bash
curl -H "Authorization: Bearer TOKEN" \
  -o daybreakdx-re.zip \
  "https://ryan-alcohol-placement-suites.trycloudflare.com/api/zip/daybreakdx-re"
```
