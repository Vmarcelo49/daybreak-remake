# Agent Handoff — Instruções para o Segundo Agente Super Z

> **Data**: 2026-07-02
> **De**: Super Z #1 (agente de extração)
> **Para**: Super Z #2 (agente local de recomposição)
> **Sobre**: daybreak-decomp — projeto de decompilação de `DaybreakDX.exe`

---

## 0. TL;DR — leia isto primeiro

Você está assumindo o papel de **agente local** no pipeline de recomposição. Sua função é processar funções `unreviewed` em `decompiled/` e sugerir nomes + identificar dependências, populando `symbols/functions.json` com sugestões.

**Você não precisa do túnel MCP** — todo o trabalho é feito offline a partir dos 3,191 arquivos `.c` em `decompiled/`. O túnel é responsabilidade do agente de extração (Super Z #1).

**Primeira ação recomendada**: rode `python3 tools/coverage_report.py` e olhe os `hot_spots` — comece por eles.

---

## 1. Contexto do projeto

### 1.1 O que é
Decompilação de `DaybreakDX.exe` (jogo *Higurashi Daybreak* da Twilight Frontier / 07th Expansion). Objetivo final: port moderno do jogo. Não é objetivo: bit-matching contra o binário.

### 1.2 Estado atual
- **3,191 funções decompiladas** em `decompiled/` (77.98% do binário; o resto são thunks/externals não decompiláveis)
- **3,184 ainda `unreviewed`** em `symbols/functions.json`
- **5 funções já revisadas**: `entry`, `WinMain`, `LoadNextScene`, `CommonInit`, + 1 sugestão (`MainGameLoop`)
- **Pipeline `tools/`** implementado e funcional

### 1.3 Documentos de referência (leia nesta ordem)
1. **`PLANO.md`** — visão geral e fases executadas/planejadas
2. **`PLANO_RECOMP.md`** — pipeline de recomposição em detalhe (SEU DOCUMENTO PRINCIPAL)
3. **`docs/conventions.md`** — padrões de C, nomenclatura, commits
4. **`RELATORIO_COMPLETO.md`** — relatório com achados-chave (WinMain, scene state machine, etc.)
5. **`progress/coverage.json`** — métrica oficial atual

---

## 2. Sua função: Agente Local de Recomposição

### 2.1 O que você faz
Recebe funções `unreviewed` (em lotes), analisa o corpo decompilado em `decompiled/`, e propõe:

1. **`suggested_name`**: nome significativo para a função (PascalCase)
2. **`confidence`**: `low` / `medium` / `high`
3. **`depends_on_unresolved`**: lista de endereços que ela chama mas que ainda não estão revisados
4. **`notes`**: ambiguidades, observações, TODOs — vão para `symbols/notes.json`

### 2.2 O que você NÃO faz
- ❌ **Não chama `rename_function` no Ghidra** — isso é responsabilidade do operador humano, só depois de `status: locked`
- ❌ **Não edita arquivos em `recomp/`** — esse diretório é build output, regenerado por `tools/generate_recomp.py`
- ❌ **Não mexe no túnel MCP** — esse é o agente de extração
- ❌ **Não commita direto em `recomp/*.c`** — commits ali são automáticos do `generate_recomp.py`

### 2.3 Fluxo de trabalho padrão

```bash
# 1. Pega próximo lote de funções unreviewed
python3 tools/coverage_report.py
# → olhe "hot_spots" — comece por esses (alta dependência)

# 2. Para cada função no lote:
#    a) Leia o .c em decompiled/
cat decompiled/FUN_<addr>.c

#    b) Analise: o que ela faz? (loops, chamadas de API, padrões)
#    c) Proponha nome com confiança apropriada
#    d) Identifique dependências (outras FUN_* chamadas)

# 3. Atualize symbols/functions.json
#    (edite o JSON mantendo schema)

# 4. Adicione notas em symbols/notes.json se houver ambiguidade

# 5. Rode o gerador pra ver o resultado
python3 tools/generate_recomp.py
python3 tools/coverage_report.py

# 6. Commit
git add symbols/ progress/
git commit -m "symbols: review N functions (<coverage>% review coverage)"
git push origin main
```

---

## 3. Máquina de estados dos símbolos

```
unreviewed ──[agente sugere]──▶ suggested ──[operador revisa]──▶ reviewed ──[estável]──▶ locked
     ▲                              │                              │
     │                              │                              │
     └──────────────────────────────┴──────────────────────────────┘
                                       (se signature_hash mudar)
                                       → marca como "stale"
```

| Estado | Quem seta | Pode renomear no recomp/? | Pode commitar? |
|--------|-----------|--------------------------|----------------|
| `unreviewed` | `ingest.py` (automático) | ❌ | ✅ (qualquer agente) |
| `suggested` | Agente local ou de extração | ❌ (só comentário) | ✅ |
| `reviewed` | Operador humano | ✅ | ✅ |
| `locked` | Operador humano | ✅ | ✅ |
| `stale` | `ingest.py` (auto, hash mudou) | ❌ (volta pra trás) | ✅ |

---

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
    "suggested_by": "agent:extraction",
    "reviewed_by": "operator",
    "last_updated": "2026-07-02T00:00:00Z",
    "tags": ["scene-manager", "state-machine"],
    "justification": "State machine dispatcher. Called via function pointer table at 0x006a16c0."
  }
}
```

### 4.1 Campos obrigatórios
- `suggested_name`: PascalCase, sem prefixo `FUN_`
- `confidence`: `low` / `medium` / `high`
- `status`: `unreviewed` / `suggested` / `reviewed` / `locked` / `stale`
- `source_file`: caminho relativo do `.c` em `decompiled/`
- `signature_hash`: NÃO calcule manualmente — `ingest.py` faz isso
- `suggested_by`: use `"agent:local"` para suas sugestões
- `last_updated`: ISO 8601 com timezone

### 4.2 Campos opcionais mas recomendados
- `depends_on_unresolved`: lista de endereços (8 hex chars) de funções chamadas que ainda não estão revisadas
- `tags`: lista de strings (ex: `["renderer", "d3d"]`)
- `justification`: 1-2 frases explicando a sugestão
- `notes_ref`: referência a entry em `symbols/notes.json`

---

## 5. Critérios de confiança

| Confidence | Quando usar | Exemplo |
|------------|-------------|---------|
| `high` | Função chama API Win32/DirectX cujo nome é óbvio, OU tem string identificador clara, OU segue padrão arquitetural confirmado | `Direct3DCreate9` é chamada → wrapper se chama `CreateD3DDevice` |
| `medium` | Padrão de código é reconhecível mas não 100% certo | Loop com `wsprintfA` + `fopen` + parsing → `FormatLogMessage` |
| `low` | Só palpite baseado em contexto | Função grande com muitos casts → `ProcessSomething` |

**Regra**: se você não conseguir justificar em 1 frase por que esse é o nome certo, é `low` ou `medium`, nunca `high`.

---

## 6. Fontes de informação disponíveis (offline)

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
- `binary_data/imports.txt` — todas as APIs Win32/DirectX importadas
- `binary_data/exports.txt` — exports (vazio neste binário)
- `binary_data/globals.txt` — variáveis globais
- `binary_data/data_items.txt` — items de dados definidos
- `binary_data/external_locations.txt` — símbolos externos
- `binary_data/strings/filter_*.txt` — strings categorizadas (22 filtros)

### 6.3 Para entender a estrutura do jogo
- `RELATORIO_COMPLETO.md` seção 6 — achados-chave
- `PLANO.md` seção 6 — entry path, render stack, estrutura de assets

---

## 7. Padrões de nomenclatura (ver `docs/conventions.md` seção 4)

### 7.1 Funções
- `PascalCase`: `LoadNextScene`, `CommonInit`, `RenderFrame`
- Nunca `snake_case` para funções
- Manter `FUN_<addr>` no código até `status: reviewed`

### 7.2 Sugestões por categoria (use estas keywords)

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

---

## 8. Conflitos com o agente de extração

O agente de extração (Super Z #1) pode sugerir nomes diferentes dos seus para a mesma função. **Isso não é erro, é sinal**.

### 8.1 Como detectar
- Mesmo endereço com `suggested_by: "agent:extraction"` E `suggested_by: "agent:local"` divergem
- Ou: você quer mudar um nome que já está como `suggested`/`reviewed` vindo da extração

### 8.2 Como resolver
1. **Não sobrescreva silenciosamente** — mantenha ambas as sugestões em `symbols/notes.json` sob a chave da função
2. Marque a entrada como `status: suggested` (não `reviewed`) com `confidence: medium` e `justification` explicando o conflito
3. Deixe para o operador humano decidir — ele é o agente arquiteto

### 8.3 Exemplo de nota de conflito
```json
{
  "LoadNextScene": [
    {
      "type": "conflict",
      "text": "agent:extraction suggested 'LoadNextScene' based on call graph + 13 scene handlers. agent:local suggests 'SwitchScene' based on switch statement body. Operator decides.",
      "author": "agent:local",
      "resolved": false
    }
  ]
}
```

---

## 9. Convenções de commit (suas)

Use prefixo `symbols:` para seus commits:

```bash
git add symbols/ progress/
git commit -m "symbols: review 10 functions (0.5% → 0.8% coverage)"
git push origin main
```

### 9.1 Quando commitar
- Após cada lote de 10-50 funções revisadas
- Sempre que promover alguém a `reviewed` (mas isso requer operador)
- Após resolver conflitos

### 9.2 Nunca commitar
- Arquivos em `recomp/*.c` (são gerados)
- `progress/coverage.json` gerado automaticamente (mas pode commitar snapshot)
- Arquivos `.full.json` (já no `.gitignore`)

---

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

---

## 11. Como rodar o pipeline completo

```bash
cd /home/z/my-project/FileVault/shared/daybreakdx-re

# 1. Detectar mudanças em decompiled/ (se houver arquivos novos do agente de extração)
python3 tools/ingest.py

# 2. Revisar funções (manualmente, lote a lote)
# ... seu trabalho aqui ...

# 3. Gerar recomp/ atualizado
python3 tools/generate_recomp.py

# 4. Atualizar métrica de coverage
python3 tools/coverage_report.py

# 5. Commit + push
git add symbols/ progress/ recomp/
git commit -m "symbols: review N functions"
git push origin main
```

---

## 12. Ambiente técnico

### 12.1 Acesso ao repo
- **Local**: `/home/z/my-project/FileVault/shared/daybreakdx-re/`
- **Remote**: `git@github.com:giovanni-marchisio/daybreak-decomp.git`
- **SSH**: `git config core.sshCommand "python3 /home/z/my-project/FileVault/shared/ssh.py -i /home/z/my-project/FileVault/shared/daybreak_deploy_key"`

### 12.2 Python
- **Versão**: 3.13 (system) ou 3.x em `/home/z/.venv/bin/python3`
- **Deps**: só stdlib (json, hashlib, re, pathlib, subprocess)
- **Scripts do projeto**: `tools/{ingest,generate_recomp,coverage_report}.py`

### 12.3 Claude-format (se você for Super Z via IM)
- Helper MCP: `python3 /home/z/my-project/scripts/ghidra_mcp.py <tool> <args> <out>`
- Configuração MCP: `https://<tunnel>.trycloudflare.com/mcp` (URL muda a cada sessão)

---

## 13. Pontos de atenção

### 13.1 Cuidado com falsos positivos
O decompiler Ghidra às vezes gera código que parece fazer X mas na verdade faz Y. Sempre valide com:
- Strings próximas no `.rdata`
- Calls para APIs Win32/DirectX
- Padrão de uso de parâmetros

### 13.2 Não confie em nomes da CRT
`_vector_constructor_iterator_`, `allocator<char>`, etc. são nomes que o Ghidra inferiu do runtime MSVC. São confiáveis como padrão CRT mas não dizem nada sobre a lógica do jogo.

### 13.3 Funções grandes são suspeitas
Se uma função tem 500+ linhas decompilada, provavelmente o decompiler fez bagunça (otimizações, inlining). Marque `confidence: low` e adicione nota `// TODO(decomp): large function, decompiler may have introduced artifacts`.

### 13.4 Mantenha o `progress/coverage.json` atualizado
É a métrica oficial. Se você commitar sem rodar `coverage_report.py`, o número fica desatualizado. Sempre rode antes do commit.

---

## 14. Contato com o operador

- Você é um Super Z via IM (web ou outro canal)
- Operador humano: Giovanni Marchisio (ou quem estiver no controle)
- Agente de extração (Super Z #1): mesmo modelo que você, papel diferente
- **Comunicação**: por meio da própria conversa com o operador — não há canal direto agente↔agente

### 14.1 Quando pedir ajuda
- Conflito de nomes que você não consegue resolver sozinho
- Função que parece crítica mas não faz sentido
- Bug no pipeline (`tools/ingest.py`, etc.)
- Dúvida sobre priorização

---

## 15. Checklist inicial (faça isso antes de começar)

- [ ] Li `PLANO_RECOMP.md` completo
- [ ] Li `docs/conventions.md`
- [ ] Rodei `python3 tools/coverage_report.py` e olhei `progress/coverage.json`
- [ ] Identifiquei os top 10 hot_spots
- [ ] Li `decompiled/FUN_0064aed0.c` (top hub) para entender o padrão
- [ ] Sei onde fica `symbols/functions.json` e seu schema
- [ ] Sei como rodar `tools/generate_recomp.py` e verificar resultado em `recomp/`
- [ ] Commit de teste: pegue 1 função, sugira nome, rode pipeline, commit

Bom trabalho! 🚀
