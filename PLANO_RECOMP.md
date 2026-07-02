# Plano: Pipeline de Recomposição (`recomp/`) — daybreak-decomp

> Documento vivo — atualizado conforme o trabalho avança.
> Repo: https://github.com/giovanni-marchisio/daybreak-decomp
> Documento irmão: `PLANO.md` (extração/análise do binário no Ghidra)
>
> **Revisão 2 (2026-07-01)**: alinhado com `PLANO.md` revisão 2 — agora
> sugestões de nome podem vir de duas fontes (agente local deste pipeline e
> a Fase 10 do plano de extração), e o formato de arquivo de `decompiled/`
> passou a ter um requisito explícito de estabilidade. Ver seção 0.1.

## 0. Propósito deste documento

Este documento é o guia operacional para o(s) agente(s) responsáveis por transformar
os arquivos `.c` decompilados brutos (gerados continuamente em `/decompiled/`) em
código C legível e portável em `/recomp/`, sem comprometer a fidelidade ao binário
original enquanto a decompilação completa não estiver pronta.

**Objetivo final do projeto**: permitir ports modernos de Higurashi Daybreak Kai.
**Não é objetivo**: bit-matching contra o binário original.

Se qualquer instrução neste documento conflitar com uma decisão tomada em
`docs/conventions.md`, `docs/conventions.md` prevalece — ele é a fonte viva de
decisões técnicas, este documento é o plano estrutural.

### 0.1 Relação com `PLANO.md` (novo)

`PLANO.md` cobre a extração no Ghidra (descoberta, priorização, decompilação
em massa). Este documento cobre o que acontece depois que um `.c` bruto
existe em `decompiled/`. Os dois pipelines compartilham o mesmo
`symbols/functions.json` como fonte de verdade sobre nomes — **não são dois
sistemas de nomeação, é um só, alimentado por duas origens**:

1. **Este pipeline** (agente local + agente arquiteto), processando cada
   função a partir do corpo decompilado.
2. **`PLANO.md`, Fase 10**, quando o agente de extração identifica uma
   função com confiança suficiente durante a análise no Ghidra (ex: por
   contexto de call graph, strings próximas, cross-reference), aplica um
   plate comment no Ghidra **e** registra a mesma sugestão aqui, com
   `suggested_by: "agent:extraction"`.

Quando as duas origens sugerem nomes diferentes para a mesma função, isso
**não é um bug**, é sinal de que a função merece atenção — vira trabalho do
agente arquiteto (seção 4) resolver, não um erro a esconder.

**Requisito que `PLANO.md` precisa garantir** (Fase 8.5 de lá): todo arquivo
em `decompiled/` deve ter nome estável no formato `FUN_<endereço>_*.c` (ou
o nome real conhecido, ex: `LoadNextScene.c`, quando aplicável). Sem isso,
`signature_hash` (seção 5.1) não consegue rastrear a função entre execuções
do pipeline.

---

## 1. Princípio central: `recomp/` é build output, não fonte

Isso é a regra mais importante do projeto e a que mais evita retrabalho e bugs.

- `symbols/` (não `recomp/`) é a fonte da verdade sobre nomes, tipos e observações.
- `recomp/*.c` é **sempre regenerado** a partir de `decompiled/*.c` + `symbols/*.json`.
- Nenhum agente ou pessoa deve editar arquivos dentro de `recomp/` diretamente.
  Qualquer edição manual ali será **sobrescrita** na próxima geração e é
  considerada um bug de processo se acontecer.
- Consequência prática: se `/decompiled/` for atualizado (o pipeline de dump
  trouxe mais contexto sobre uma função), basta rodar o gerador de novo — os
  nomes e anotações já revisados **sobrevivem automaticamente**, porque vêm de
  `symbols/`, não do texto antigo de `recomp/`.
- A mesma regra vale em espelho do lado do Ghidra: a IDB do projeto não deve
  ser tratada como fonte de nomes reais antes de uma função estar `locked`
  (ver `PLANO.md`, Fase 10 revisada). `symbols/functions.json` é a única
  fonte de verdade sobre identidade de função em todo o projeto — tanto para
  o `recomp/` quanto para qualquer renomeação eventual no Ghidra.

```
decompiled/xyz.c  ──┐
                     ├──▶  generate_recomp.py  ──▶  recomp/xyz.c
symbols/*.json    ──┘
        ▲
        │ (também alimentado por)
PLANO.md, Fase 10 — plate comments no Ghidra + sugestão registrada aqui
```

---

## 2. Estrutura de repositório

```
daybreak-decomp/
├── decompiled/              # saída bruta do pipeline de dump (read-only p/ agentes de recomp)
├── recomp/                  # C legível, GERADO — nunca editar à mão
├── symbols/
│   ├── functions.json       # endereço/assinatura → nome sugerido, status, confiança
│   ├── types.json           # structs/unions/enums reconstruídos
│   └── notes.json           # observações, ambiguidades, TODOs por função
├── progress/
│   └── coverage.json        # gerado automaticamente a cada rodada
├── tools/
│   ├── ingest.py             # detecta mudanças em decompiled/, dispara agentes
│   ├── generate_recomp.py    # lê decompiled/ + symbols/ → escreve recomp/
│   └── coverage_report.py
└── docs/
    └── conventions.md        # padrão de C, formatação, convenções de commit
```

---

## 3. Regras invioláveis para qualquer agente que gere código em `recomp/`

1. **Comportamento idêntico ao original.** Refatoração de fluxo de controle,
   ordem de operações ou efeitos colaterais só é permitida se o resultado for
   C compilável **funcionalmente indistinguível** do `.c` decompilado de origem.
2. **Nomes reais só via comentário até a decompilação estar completa.**
   Enquanto existir qualquer função referenciada que ainda não esteja em
   `/decompiled/`, os identificadores no código (`FUN_00401230`, `iVar1`,
   `param_1`) permanecem como estão. Nomes sugeridos entram como comentário:
   ```c
   // nome sugerido: ParseAnimationHeader (confidence: medium)
   void FUN_00401230(int param_1, char *param_2) {
       // count
       int iVar1 = 0;
       ...
   }
   ```
3. **Não invente lógica.** Ambiguidade (cast incerto, union confusa,
   otimização que distorceu a leitura) vira comentário `// TODO(decomp): ...`,
   nunca uma suposição silenciosa.
4. **Uma função nunca é `locked` se depende de função ainda não decompilada.**
   Marque a dependência em `notes.json` e mantenha `status` em algo revisável
   (`suggested`/`reviewed`), nunca `locked`.
5. **Toda sugestão de nome é rastreável.** Todo campo em `symbols/functions.json`
   registra quem sugeriu, quem revisou (se houver) e o hash da assinatura da
   função no momento da sugestão (ver seção 5). "Quem sugeriu" inclui a
   origem — agente local deste pipeline ou agente de extração (`PLANO.md`).

---

## 4. Papéis no pipeline

| Etapa | Executor | Tipo de decisão |
|---|---|---|
| Detectar arquivo novo/alterado em `decompiled/` | script determinístico | mecânica, sem IA |
| Sugerir nomes de função/variável, comentar ambiguidades | agente local (execução em lote, tolera erro) **ou** agente de extração via `PLANO.md` Fase 10 | análise local, alto volume |
| Resolver conflitos entre sugestões (nomes duplicados, sugestões divergentes entre as duas origens, renomeação que quebra dependência em outro arquivo, decisão que exige visão do projeto inteiro) | agente arquiteto/poderoso | decisão de escopo global |
| Gerar `recomp/*.c` final | script determinístico lendo `symbols/` | mecânica, 100% reprodutível |
| Validar (compila? bate convenções?) | CI | gate automático antes de merge |

**Regra de ouro**: qualquer etapa que possa ser determinística deve ser
determinística. IA só decide onde há ambiguidade real (nomear algo, resolver
conflito). Isso é o que garante que regenerar `recomp/` produza sempre o mesmo
resultado a partir do mesmo `symbols/`.

---

## 5. Formato de dados

### 5.1 `symbols/functions.json`

```json
{
  "FUN_00401230": {
    "suggested_name": "ParseAnimationHeader",
    "confidence": "medium",
    "status": "reviewed",
    "source_file": "decompiled/anim.c",
    "signature_hash": "a1b2c3d4...",
    "depends_on_unresolved": [],
    "notes_ref": "notes.json#FUN_00401230",
    "suggested_by": "agent:qwen3-coder-30b",
    "reviewed_by": "marcelo",
    "last_updated": "2026-07-01T00:00:00Z"
  },
  "FUN_00401890": {
    "suggested_name": "UpdateCharacterState",
    "confidence": "low",
    "status": "suggested",
    "source_file": "decompiled/char_ctrl.c",
    "signature_hash": "9f8e7d6c...",
    "depends_on_unresolved": ["FUN_004025a0"],
    "notes_ref": "notes.json#FUN_00401890",
    "suggested_by": "agent:qwen3-coder-30b",
    "reviewed_by": null,
    "last_updated": "2026-07-01T00:00:00Z"
  },
  "FUN_00412110": {
    "suggested_name": "MainGameLoop",
    "confidence": "low",
    "status": "suggested",
    "source_file": "decompiled/FUN_00412110_06_dispatcher.c",
    "signature_hash": "77aa88bb...",
    "depends_on_unresolved": [],
    "notes_ref": "notes.json#FUN_00412110",
    "suggested_by": "agent:extraction",
    "reviewed_by": null,
    "last_updated": "2026-07-01T00:00:00Z"
  }
}
```

Campos-chave:
- `signature_hash`: hash calculado sobre o corpo bruto da função em
  `decompiled/` (ignorando nomes de variáveis geradas automaticamente). Se o
  hash mudar entre rodadas, a sugestão está **desatualizada** e `status` deve
  voltar para `"stale"` até nova revisão. Depende de nome de arquivo estável
  em `decompiled/` (ver seção 0.1).
- `status`: máquina de estados —
  `unreviewed → suggested → reviewed → locked`, com `stale` como estado de
  exceção alcançável a partir de `reviewed`/`locked` quando o hash muda.
- `depends_on_unresolved`: lista de outras funções ainda não decompiladas.
  Não-vazio bloqueia `status: locked`.
- `suggested_by`: identifica a origem da sugestão. Valores esperados incluem
  `agent:<nome-do-modelo>` (pipeline de recomp) e `agent:extraction`
  (Fase 10 de `PLANO.md`, via plate comment no Ghidra). Duas entradas para o
  mesmo símbolo vindas de origens diferentes não devem ser mescladas
  silenciosamente — cabe ao agente arquiteto decidir qual prevalece ou
  reconciliar as duas.

### 5.2 `symbols/notes.json`

```json
{
  "FUN_00401230": [
    {
      "type": "ambiguity",
      "text": "param_2 pode ser union entre float e int; comportamento no branch 0x14 sugere reinterpretação de bits.",
      "author": "agent:qwen3-coder-30b",
      "resolved": false
    }
  ]
}
```

### 5.3 `progress/coverage.json` (gerado, não editado manualmente)

```json
{
  "generated_at": "2026-07-01T00:00:00Z",
  "total_functions_decompiled": 812,
  "functions_named_reviewed_or_locked": 340,
  "coverage_percent": 41.9,
  "hot_spots": [
    { "symbol": "FUN_00402ab0", "called_by_count": 47, "status": "unreviewed" }
  ],
  "stale_count": 12
}
```

`hot_spots` = funções com muitas dependentes e ainda sem revisão — priorizar
essas no próximo lote do agente arquiteto.

Esta é a **fonte oficial de progresso do projeto como um todo** — inclusive
para o que é reportado em `PLANO.md`, que passou a tratar sua própria tabela
de métricas como snapshot histórico, não como fonte viva.

---

## 6. Convenções técnicas fechadas

- **Padrão de C**: C11. Justificativa: comentários `//`, declaração de
  variável em qualquer ponto do bloco (compatível com como decompiladores
  geram código), `stdint.h` para tipos de tamanho fixo, `_Static_assert` para
  travar suposições de tamanho de struct, anonymous unions para representar
  type punning sem inventar nomes de union. Como não há objetivo de
  bit-matching, não há motivo para travar no compilador/padrão original do
  jogo.
- **Formatação**: `clang-format` fixo via `.clang-format` no repo, aplicado
  automaticamente por `generate_recomp.py`. Ninguém formata manualmente.
- **Convenção de commit** (para commits automáticos do pipeline):
  `recomp(<arquivo>): <n> funções atualizadas (<coverage>% coverage)`.
  Commits de revisão manual usam mensagem livre, mas idealmente referenciando
  o(s) símbolo(s) revisado(s). O prefixo `recomp:` é reservado a este
  pipeline — commits do pipeline de extração usam os prefixos definidos em
  `PLANO.md` seção 8.
- **Branch**: pipeline automatizado commita em `recomp-auto`; merge para
  `main` só após revisão pontual humana ou do agente arquiteto. Isso vale
  estritamente para `recomp/` — `PLANO.md` define separadamente o que pode
  ir direto para `main` (artefatos de extração/análise).

---

## 7. Exemplo de fluxo ponta a ponta

1. `ingest.py` detecta que `decompiled/anim.c` mudou (novo hash de arquivo).
2. Para cada função nova/alterada em `anim.c`, calcula `signature_hash` e
   compara com o que está em `functions.json`. Se mudou ou não existe, marca
   para reprocessamento.
3. Agente local (Ollama) recebe o corpo da função + contexto do arquivo,
   sugere nome e possíveis ambiguidades, escreve em `functions.json` com
   `status: suggested` e em `notes.json` se houver ambiguidade.
   - Em paralelo, o agente de extração (`PLANO.md`, Fase 10) pode ter
     registrado sua própria sugestão para a mesma função a partir do
     contexto do Ghidra (call graph, strings, xrefs) — ambas ficam visíveis
     para a próxima etapa.
4. Agente arquiteto roda periodicamente sobre todas as entradas `suggested`,
   verificando conflitos de nome entre arquivos, divergência entre as duas
   origens de sugestão, e coerência semântica com o restante do projeto.
   Promove para `reviewed` ou marca para nova sugestão.
5. `generate_recomp.py` roda, lê `decompiled/anim.c` + `functions.json` +
   `notes.json`, gera `recomp/anim.c` com comentários de nome sugerido e
   TODOs, formata com `clang-format`.
6. CI valida: compila isoladamente (com stubs se necessário) e roda um diff
   estrutural simplificado entre `decompiled/anim.c` e `recomp/anim.c` para
   garantir que a lógica não mudou.
7. `coverage_report.py` atualiza `progress/coverage.json`.
8. Commit automático em `recomp-auto` com a mensagem padronizada.

---

## 8. Riscos e mitigação

| Risco | Mitigação |
|---|---|
| Colisão de nomes entre agentes rodando em paralelo | `functions.json` como single source of truth; agente arquiteto resolve conflitos antes de `reviewed` |
| Duas origens (extração e recomp) sugerindo nomes diferentes para a mesma função | Tratado como sinal, não erro — `suggested_by` distingue a origem; agente arquiteto reconcilia |
| Drift silencioso (função revisada fica desatualizada quando `decompiled/` muda) | `signature_hash` + status `stale` automático |
| Alucinação de lógica durante "limpeza" do código | Regra 1 e 3 da seção 3 + diff estrutural no CI |
| Perda de progresso ao regenerar `recomp/` | Resolvido por design: `recomp/` nunca é fonte, sempre regenerado a partir de `symbols/` |
| Função marcada como pronta mas depende de algo não decompilado | Campo `depends_on_unresolved` bloqueia `status: locked` |
| Nome de arquivo instável em `decompiled/` quebra rastreamento de `signature_hash` | Requisito explícito em `PLANO.md` Fase 8.5: nomes no formato `FUN_<addr>_*.c` |

---

## 9. Roadmap (marcos, não datas)

1. **Fundação**
   - Criar estrutura de pastas (`symbols/`, `progress/`, `tools/`, `docs/`).
   - `generate_recomp.py` v0: apenas copia `decompiled/` → `recomp/` sem
     nenhuma inteligência (baseline funcional, prova de que o gerador roda).
   - `functions.json`, `notes.json`, `coverage.json` vazios com schema
     validado.

2. **Pipeline de sugestão**
   - `ingest.py` detectando mudanças via hash de arquivo.
   - Agente local processando funções novas/alteradas em lote, populando
     `functions.json` com `status: suggested`.
   - Confirmar que sugestões vindas de `PLANO.md` Fase 10 (plate comments no
     Ghidra) também chegam em `functions.json` no mesmo formato — via export
     manual inicialmente, automatizável depois.

3. **Loop de revisão**
   - Agente arquiteto (ou você) revisando lotes de sugestões, promovendo para
     `reviewed`, resolvendo conflitos entre arquivos e entre origens.

4. **Dashboard de coverage**
   - `coverage_report.py` publicando `progress/coverage.json`, opcionalmente
     como página estática (GitHub Pages) para acompanhar sem terminal.

5. **Hardening**
   - CI com verificação de compilação isolada.
   - Diff estrutural (`decompiled/` vs `recomp/`) para pegar mudança de
     lógica introduzida acidentalmente.
   - Alerta automático para `stale_count` crescendo (sinal de que `decompiled/`
     está mudando mais rápido do que o loop de revisão consegue acompanhar).

---

## 10. Perguntas em aberto para o agente arquiteto decidir na implementação

- Formato exato do diff estrutural do CI (AST simplificado? comparação de
  grafo de fluxo de controle?).
- Se `depends_on_unresolved` deve ser recalculado automaticamente a cada
  rodada de `ingest.py` ou só quando o agente local reprocessa a função.
- Estratégia de lote para o agente arquiteto (processar tudo que está
  `suggested` a cada rodada vs. priorizar por `hot_spots`).
- Como automatizar o export de plate comments do Ghidra (`PLANO.md` Fase 10)
  para `symbols/functions.json`, hoje descrito como processo manual inicial
  — provável candidato a script MCP que lê plate comments e escreve JSON.
