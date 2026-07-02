# Onboarding — Agente Local de Recomposição

> **Seu papel**: processar funções `unreviewed` em `decompiled/`, sugerir nomes + dependências, popular `symbols/functions.json`.
>
> **Pré-requisito**: ter lido `CONTEXT.md` primeiro.
> **Você NÃO precisa do túnel MCP** — todo seu trabalho é offline.

## 1. TL;DR

```bash
# 1. Veja onde estamos
python3 tools/coverage_report.py

# 2. Pegue os top 10 hot_spots do JSON
cat progress/coverage.json | python3 -c "import json,sys; d=json.load(sys.stdin); [print(f'{h[\"address\"]} ({h[\"called_by_count\"]}x callers)') for h in d['hot_spots'][:10]]"

# 3. Para cada função:
cat decompiled/FUN_<addr>.c
# → analise, proponha nome, identifique dependências

# 4. Atualize symbols/functions.json (edite o JSON)
# 5. Adicione notas em symbols/notes.json se houver ambiguidade
# 6. Regenere e commite
python3 tools/generate_recomp.py
python3 tools/coverage_report.py
git add symbols/ progress/ recomp/
git commit -m "symbols: review N functions (<coverage>% coverage)"
git push origin main
```

## 2. Sua função exata

### 2.1 O que você faz
- Recebe funções `unreviewed` (em lotes de 10-50)
- Analisa o corpo decompilado em `decompiled/`
- Propõe:
  - `suggested_name`: nome significativo (PascalCase)
  - `confidence`: `low` / `medium` / `high`
  - `depends_on_unresolved`: endereços chamados que ainda não estão revisados
  - `notes`: ambiguidades, observações — vão para `symbols/notes.json`

### 2.2 O que você NÃO faz
- ❌ **Não chama `rename_function` no Ghidra** — isso é papel do operador após `status: locked`
- ❌ **Não edita arquivos em `recomp/`** — build output, regenerado por `tools/generate_recomp.py`
- ❌ **Não mexe no túnel MCP** — isso é papel do agente de extração
- ❌ **Não commita direto em `recomp/*.c`** — commits ali são automáticos do `generate_recomp.py`

## 3. Máquina de estados dos símbolos

```
unreviewed ──[você sugere]──▶ suggested ──[operador revisa]──▶ reviewed ──[estável]──▶ locked
     ▲                              │                              │
     │                              │                              │
     └──────────────────────────────┴──────────────────────────────┘
                                       (se signature_hash mudar)
                                       → marca como "stale"
```

| Estado | Quem seta | Pode renomear no recomp/? |
|--------|-----------|--------------------------|
| `unreviewed` | `ingest.py` (auto) | ❌ |
| `suggested` | **Você** (agente local) ou agente de extração | ❌ (só comentário) |
| `reviewed` | Operador humano | ✅ |
| `locked` | Operador humano | ✅ |
| `stale` | `ingest.py` (auto, hash mudou) | ❌ (volta pra trás) |

## 4. Schema de `symbols/functions.json`

```json
{
  "00406310": {
    "suggested_name": "LoadNextScene",
    "confidence": "high",
    "status": "reviewed",
    "source_file": "decompiled/LoadNextScene.c",
    "signature_hash": "a1b2c3d4e5f67890",
    "depends_on_unresolved": [],
    "notes_ref": "symbols/notes.json#LoadNextScene",
    "suggested_by": "agent:local",
    "reviewed_by": "operator",
    "last_updated": "2026-07-02T00:00:00Z",
    "tags": ["scene-manager", "state-machine"],
    "justification": "State machine dispatcher. Switch on pGameState+0x2e18."
  }
}
```

### 4.1 Campos obrigatórios
- `suggested_name`: PascalCase, sem prefixo `FUN_`
- `confidence`: `low` / `medium` / `high`
- `status`: `unreviewed` / `suggested` / `reviewed` / `locked` / `stale`
- `source_file`: caminho relativo do `.c` em `decompiled/`
- `signature_hash`: **NÃO calcule manualmente** — `ingest.py` faz isso
- `suggested_by`: use `"agent:local"` para suas sugestões
- `last_updated`: ISO 8601 com timezone

### 4.2 Campos opcionais mas recomendados
- `depends_on_unresolved`: lista de endereços (8 hex chars) chamados que ainda não estão revisados
- `tags`: lista de strings (ex: `["renderer", "d3d"]`)
- `justification`: 1-2 frases explicando a sugestão
- `notes_ref`: referência a entry em `symbols/notes.json`

## 5. Critérios de confiança

| Confidence | Quando usar | Exemplo |
|------------|-------------|---------|
| `high` | Função chama API Win32/DirectX cujo nome é óbvio, OU tem string identificador clara, OU segue padrão arquitetural confirmado | `Direct3DCreate9` é chamada → wrapper se chama `CreateD3DDevice` |
| `medium` | Padrão de código é reconhecível mas não 100% certo | Loop com `wsprintfA` + `fopen` + parsing → `FormatLogMessage` |
| `low` | Só palpite baseado em contexto | Função grande com muitos casts → `ProcessSomething` |

**Regra**: se você não conseguir justificar em 1 frase por que esse é o nome certo, é `low` ou `medium`, nunca `high`.

## 6. Fontes de informação offline

### 6.1 Para entender uma função específica
```bash
# Ver o código decompilado
cat decompiled/FUN_<addr>.c

# Ver quem chama essa função (callers)
grep "FUN_<addr>" binary_data/callgraph/full_call_graph.txt

# Ver quem essa função chama (callees)
grep "^FUN_<addr>@" binary_data/callgraph/full_call_graph.txt

# Ver se ela aparece em strings relacionadas
grep -l "<pattern>" binary_data/strings/*.txt
```

### 6.2 Para entender o contexto do binário
- `binary_data/imports.txt` — APIs Win32/DirectX importadas
- `binary_data/exports.txt` — exports (vazio neste binário)
- `binary_data/globals.txt` — variáveis globais
- `binary_data/data_items.txt` — items de dados definidos
- `binary_data/external_locations.txt` — símbolos externos
- `binary_data/strings/filter_*.txt` — strings categorizadas (22 filtros)

### 6.3 Para entender a estrutura do jogo
- `RELATORIO_COMPLETO.md` seção 6 — achados-chave
- `PLANO.md` seção 6 — entry path, render stack, estrutura de assets

## 7. Padrões de nomenclatura

Ver `docs/conventions.md` seção 4 para detalhes. Resumo:

### 7.1 Funções
- `PascalCase`: `LoadNextScene`, `CommonInit`, `RenderFrame`
- Nunca `snake_case` para funções
- Manter `FUN_<addr>` no código até `status: reviewed`

### 7.2 Sugestões por categoria

| Categoria | Padrão de nome | Exemplos |
|-----------|----------------|----------|
| Renderer/D3D | `Render*`, `Draw*`, `Begin*`, `End*` | `RenderFrame`, `DrawCharacter`, `BeginScene` |
| Input | `*Input*`, `*Key*`, `*Mouse*` | `ProcessKeyboard`, `ReadMouseState` |
| Audio | `*Sound*`, `*BGM*`, `*Voice*`, `*SE*` | `PlayBGM`, `StopVoice` |
| Scene/State | `*Scene*`, `*State*`, `*Mode*` | `LoadNextScene`, `UpdateGameState` |
| File I/O | `*File*`, `*Load*`, `*Save*`, `*Read*`, `*Write*` | `LoadMeshFromX`, `SaveConfig` |
| Memory | `*Alloc*`, `*Free*`, `*Init*` | `AllocateMesh`, `FreeTexture` |
| Math | `*Matrix*`, `*Vec*`, `*Transform*` | `BuildViewMatrix`, `TransformVertex` |
| Network | `*Net*`, `*Socket*`, `*Send*`, `*Recv*` | `NetSendUpdate`, `RecvPlayerState` |

## 8. Conflitos com o agente de extração

O agente de extração pode sugerir nomes diferentes dos seus para a mesma função. **Isso não é erro, é sinal**.

### 8.1 Como detectar
- Mesmo endereço com `suggested_by: "agent:extraction"` E `suggested_by: "agent:local"` divergem
- Ou: você quer mudar um nome que já está como `suggested`/`reviewed` vindo da extração

### 8.2 Como resolver
1. **Não sobrescreva silenciosamente** — mantenha ambas as sugestões em `symbols/notes.json`
2. Marque a entrada como `status: suggested` (não `reviewed`) com `confidence: medium` e `justification` explicando o conflito
3. Deixe para o operador humano decidir

### 8.3 Exemplo de nota de conflito
```json
{
  "LoadNextScene": [
    {
      "type": "conflict",
      "text": "agent:extraction suggested 'LoadNextScene' based on call graph + scene handlers. agent:local suggests 'SwitchScene' based on switch statement body. Operator decides.",
      "author": "agent:local",
      "resolved": false
    }
  ]
}
```

## 9. Convenções de commit

Use prefixo `symbols:` para seus commits:

```bash
git add symbols/ progress/ recomp/
git commit -m "symbols: review 10 functions (0.5% → 0.8% coverage)"
git push origin main
```

### 9.1 Quando commitar
- Após cada lote de 10-50 funções revisadas
- Sempre que promover alguém a `reviewed` (mas isso requer operador)
- Após resolver conflitos

### 9.2 Nunca commitar
- Arquivos em `recomp/*.c` diretamente (são gerados)
- `*.full.json` (no `.gitignore`)
- Chaves SSH ou credenciais

## 10. Primeiro lote recomendado

Comece com os **top hot_spots** (funções mais chamadas ainda `unreviewed`). Rode:

```bash
python3 tools/coverage_report.py
# Veja o campo "hot_spots" no JSON
```

### 10.1 Sugestão de primeiros 10 para revisar

| Endereço | Por que priorizar |
|----------|-------------------|
| `0064aed0` | Top hub interno (18 callers) — provavelmente allocator ou string util |
| `004039d0` | 16 callers — pode ser helper de GameState |
| `00415ec0` | 16 callers — pode ser math helper |
| `00403a50` | 15 callers |
| `00415d30` | 15 callers |
| `00656200` | 15 callers |
| `00657390` | 15 callers |
| `00655af0` | 15 callers |
| `00401000` | 15 callers — `vector_constructor_iterator` (já nomeado pela CRT) |
| `006560c0` | 15 callers |

**Estratégia**: funções muito chamadas costumam ser **utils** (alloc, free, string ops, math). Identificar elas primeiro facilita entender as funções que as chamam.

### 10.2 Lotes subsequentes
- Após os hubs: processe os dispatchers (já temos `FUN_00412110` como `MainGameLoop` sugerido)
- Após dispatchers: processe funções referenciadas por strings de arquivo (`.x`, `.dat`, `.bmp`)
- Por último: funções leaf (sem callees) — são as mais difíceis de nomear sem contexto

## 11. Fluxo completo de uma sessão

```bash
cd /home/z/my-project/FileVault/shared/daybreakdx-re

# 1. Sincroniza com remote (caso agente de extração tenha commitado)
git pull --rebase origin main

# 2. Detectar mudanças em decompiled/ (se houver arquivos novos)
python3 tools/ingest.py

# 3. Veja progresso atual
python3 tools/coverage_report.py

# 4. Pegue um lote de funções unreviewed (comece pelos hot_spots)
# 5. Para cada função:
#    a) Leia o .c em decompiled/
#    b) Analise: o que ela faz?
#    c) Proponha nome + confidence
#    d) Identifique dependências (chamadas a outras FUN_*)
# 6. Atualize symbols/functions.json (edite o JSON mantendo schema)
# 7. Adicione notas em symbols/notes.json se houver ambiguidade

# 8. Regenere recomp/ e coverage
python3 tools/generate_recomp.py
python3 tools/coverage_report.py

# 9. Commit + push
git add symbols/ progress/ recomp/
git commit -m "symbols: review N functions (<coverage>% coverage)"
git push origin main
```

## 12. Pontos de atenção

1. **Cuidado com falsos positivos** — o Ghidra às vezes gera código que parece fazer X mas faz Y. Valide com strings próximas, calls para APIs, padrão de uso de parâmetros.
2. **Não confie em nomes da CRT** — `_vector_constructor_iterator_`, `allocator<char>`, etc. são inferências do MSVC, não dizem nada sobre a lógica do jogo.
3. **Funções grandes são suspeitas** — se 500+ linhas, marque `confidence: low` e adicione `// TODO(decomp): large function, decompiler may have introduced artifacts`.
4. **Mantenha `progress/coverage.json` atualizado** — rode `coverage_report.py` antes de cada commit.

## 13. Quando pedir ajuda ao operador

- Conflito de nomes que você não consegue resolver sozinho
- Função que parece crítica mas não faz sentido
- Bug no pipeline (`tools/ingest.py`, etc.)
- Dúvida sobre priorização

## 14. Checklist inicial

- [ ] Li `CONTEXT.md` primeiro
- [ ] Li `PLANO_RECOMP.md` completo
- [ ] Li `docs/conventions.md`
- [ ] Rodei `python3 tools/coverage_report.py` e olhei `progress/coverage.json`
- [ ] Identifiquei os top 10 hot_spots
- [ ] Li `decompiled/FUN_0064aed0.c` (top hub) para entender o padrão
- [ ] Sei onde fica `symbols/functions.json` e seu schema
- [ ] Sei como rodar `tools/generate_recomp.py` e verificar resultado em `recomp/`
- [ ] Commit de teste: pegue 1 função, sugira nome, rode pipeline, commit
