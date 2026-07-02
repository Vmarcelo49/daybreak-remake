# Contexto do Projeto — daybreak-decomp

> **Leia isto primeiro se você é um novo agente.** Este arquivo é neutro em relação ao seu papel — descreve o estado do projeto, não o que você deve fazer.
> Depois de ler, consulte `AGENT_LOCAL_ONBOARDING.md` (recomposição) ou `AGENT_EXTRACTION_ONBOARDING.md` (extração no Ghidra) conforme seu papel.

## 1. O que é este projeto

Decompilação de `DaybreakDX.exe` (jogo *Higurashi Daybreak* da Twilight Frontier / 07th Expansion) com objetivo de port moderno. Não busca bit-matching contra o binário original.

- **Repo**: https://github.com/giovanni-marchisio/daybreak-decomp
- **Local**: `/home/z/my-project/FileVault/shared/daybreakdx-re/` (compartilhado via FileVault)
- **Binário alvo**: x86 32-bit PE, MSVC, image base `0x00400000`, ~2.86 MB

## 2. Estado atual (snapshot)

| Métrica | Valor |
|---------|-------|
| Funções no binário | 4,092 |
| Funções decompiladas (`decompiled/`) | 3,191 (77.98%) |
| Funções revisadas (`reviewed`/`locked`) | 5 |
| Funções com sugestão | 1 |
| Funções `unreviewed` | 3,184 |
| Pipeline `tools/` | ✅ implementado |
| Métrica oficial | `progress/coverage.json` |

**Diferença 4,092 → 3,191**: ~900 funções são thunks/externals não decompiláveis (teto do Ghidra neste binário).

## 3. Documentos de referência

| Documento | Conteúdo | Quando ler |
|-----------|----------|------------|
| `PLANO.md` | Plano de extração/análise, fases executadas e futuras | Sempre — visão geral |
| `PLANO_RECOMP.md` | Pipeline de recomposição em C legível | Se for trabalhar em `recomp/` |
| `docs/conventions.md` | Padrões de C, nomenclatura, commits | Antes de commitar |
| `RELATORIO_COMPLETO.md` | Achados-chave da análise (WinMain, scene mgr, etc.) | Para contexto técnico |
| `AGENT_LOCAL_ONBOARDING.md` | Onboarding do agente de recomposição | Se for agente local |
| `AGENT_EXTRACTION_ONBOARDING.md` | Onboarding do agente de extração | Se for agente de extração (MCP) |

## 4. Estrutura do repo

```
daybreak-decomp/
├── PLANO.md, PLANO_RECOMP.md, AGENT_*.md, CONTEXT.md (este)
├── PROGRESSO.md, RELATORIO_COMPLETO.md
├── INDEX.md / INDEX.json          (gerados pelo CI)
├── .gitignore, .clang-format
│
├── .github/                       (CI: gera INDEX.md/json a cada push)
│
├── decompiled/                    (3,191 .c brutos — read-only p/ recomp)
├── recomp/                        (3,191 .c GERADOS — nunca editar à mão)
│
├── symbols/                       (FONTE DE VERDADE)
│   ├── functions.json             (3,175 entradas, 5 revisadas)
│   ├── types.json                 (structs reconstruídas + hipóteses)
│   └── notes.json                 (observações + TODOs por função)
│
├── progress/
│   ├── coverage.json              (MÉTRICA OFICIAL)
│   └── last_ingest.json
│
├── tools/                         (pipeline)
│   ├── ingest.py                  (detecta mudanças em decompiled/)
│   ├── generate_recomp.py         (gera recomp/ a partir de symbols/)
│   └── coverage_report.py         (gera progress/coverage.json)
│
├── docs/conventions.md
│
├── binary_data/                   (dump bruto do MCP — referência)
│   ├── functions/                 (3,087 JSONs individuais)
│   ├── strings/                   (22 filtros diferentes)
│   ├── types/                     (14 categorias)
│   ├── callgraph/                 (1,000+ edges)
│   ├── segments/                  (⚠️ só Headers.bin — faltam .text/.rdata/.data)
│   └── *.txt                      (imports, exports, globals, etc.)
│
└── 01_*.txt — 06_*.txt            (dados brutos das fases 1-6)
```

## 5. Pipelines disponíveis

### 5.1 Atualizar estado (após mudanças em `decompiled/`)
```bash
python3 tools/ingest.py            # detecta mudanças, atualiza signature_hash
python3 tools/generate_recomp.py   # regenera recomp/
python3 tools/coverage_report.py   # atualiza progress/coverage.json
```

### 5.2 Buscar no dump offline
```bash
# Buscar em todas as strings
grep -r "pattern" binary_data/strings/

# Buscar em todos os .c decompilados
grep -l "pattern" decompiled/*.c

# Ver quem chama uma função (callers)
grep "FUN_<addr>" binary_data/callgraph/full_call_graph.txt

# Ver quem uma função chama (callees)
grep "^FUN_<addr>@" binary_data/callgraph/full_call_graph.txt
```

### 5.3 Deploy
```bash
git config core.sshCommand "python3 /home/z/my-project/FileVault/shared/ssh.py -i /home/z/my-project/FileVault/shared/daybreak_deploy_key"
git push origin main
```

Push direto na `main` aceito apenas para: `decompiled/`, `binary_data/`, `symbols/`, `progress/`, `*.md`, `NN_*.txt`.
**Nunca** commitar: `recomp/*.c` (gerado), chaves, `.env`, `*.full.json`.

## 6. Funções-chave já identificadas

| Endereço | Nome | Status | Papel |
|----------|------|--------|-------|
| `0x0066c906` | `entry` | locked | MSVC CRT entry → chama WinMain |
| `0x0064d250` | `WinMain` | reviewed | Cria window class "HigurashiDaybreak" 800x600 |
| `0x00406310` | `LoadNextScene` | reviewed | Switch-based scene dispatcher (caso 0,1,2,3...) |
| `0x00543c70` | `CommonInit` | reviewed | Bootstrap D3D, DirectInput, áudio |
| `0x00412110` | `MainGameLoop` | suggested | Top dispatcher (32 out-edges), candidato a game loop |

**Importante**: A hipótese original de "tabela de scene handlers em 0x006a16c0" estava parcialmente errada. O xref `From 006a16c0 [DATA]` indica que 0x006a16c0 é só um **ponteiro para LoadNextScene**, não uma tabela. A "tabela" real é o `switch(*(pGameState + 0x2e18))` dentro da função. Detalhes em `symbols/notes.json`.

## 7. Próximas ações priorizadas

| # | Quem | Ação | Precisa MCP? |
|---|------|------|--------------|
| 1 | Agente de extração | **Fase 9**: confirmar natureza de `0x006a16c0` e mapear scene handlers via switch case | Parcial — dá pra fazer 80% offline |
| 2 | Agente local | Processar lotes de `unreviewed` (top 10 hot_spots em `progress/coverage.json`) | ❌ Não |
| 3 | Operador | Promover `MainGameLoop` de `suggested` → `reviewed` | ❌ Não |
| 4 | Ambos | **Fase 11**: análise de multiplayer/network | ❌ Não (busca em strings) |
| 5 | Agente de extração | **Fase 12**: rodar `detect_malware_behaviors` (última sessão MCP) | ✅ Sim |

## 8. Ambiente técnico

- **Python**: 3.13 system, ou 3.x em `/home/z/.venv/bin/python3`
- **Deps do pipeline**: só stdlib (json, hashlib, re, pathlib, subprocess)
- **Túnel MCP**: `https://<random>.trycloudflare.com/mcp` (URL muda a cada sessão — pedir ao operador)
- **Helper MCP**: `python3 /home/z/my-project/scripts/ghidra_mcp.py <tool> <args> <out>`
- **Ghidra**: 11.x com plugin GhidraMCP v1.28.1 (192 ferramentas)

## 9. Pontos de atenção para qualquer agente

1. **Não confie em nomes da CRT** (`_vector_constructor_iterator_`, `allocator<char>`, etc.) — são inferências do MSVC runtime, não dizem nada sobre lógica do jogo.
2. **Funções grandes (500+ linhas)** costumam ter artefatos do decompiler — marque `confidence: low`.
3. **Sempre rode `coverage_report.py`** antes de commitar — mantém a métrica oficial atualizada.
4. **Nunca edite `recomp/*.c`** — é build output, regenerado por `tools/generate_recomp.py`.
5. **Conflito de nomes entre agentes** não é erro — vira nota em `symbols/notes.json` e operador decide.

## 10. Checklist para qualquer agente novo

- [ ] Li `CONTEXT.md` (este arquivo)
- [ ] Li `PLANO.md` seção 5 (fases futuras) e seção 6 (achados-chave)
- [ ] Li `docs/conventions.md`
- [ ] Rodei `python3 tools/coverage_report.py` e olhei `progress/coverage.json`
- [ ] Identifiquei meu papel (local ou extração) e li o onboarding correspondente
- [ ] Sei onde fica `symbols/functions.json` e seu schema
