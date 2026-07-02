# Plano de Decompilação — DaybreakDX.exe

> Documento vivo — atualizado conforme o trabalho avança.
> Repo: https://github.com/giovanni-marchisio/daybreak-decomp
>
> **Revisão 2 (2026-07-01)**: integração formal com o pipeline de recomp
> (`PLANO_RECOMP.md`), correções de segurança e mudança de estratégia na
> Fase 10 (renomeação). Ver seção 0 para o resumo do que mudou.

## 0. O que mudou nesta revisão e por quê

Este projeto tem dois planos que precisam operar como um único sistema, não
dois silos:

- **Este documento (`PLANO.md`)** cobre a extração/análise no Ghidra: como
  descobrir, priorizar e decompilar funções do binário.
- **`PLANO_RECOMP.md`** cobre o que acontece depois: como transformar o `.c`
  bruto em código legível e portável, com nomes rastreáveis via
  `symbols/functions.json`.

A regra que une os dois projetos, definida desde o início, é:

> Nomes de métodos, variáveis e afins só podem existir como **comentário**
> até toda a decompilação do binário estar completa.

Isso vale tanto para o `recomp/` quanto para o projeto do Ghidra em si — e é
o principal ponto que esta revisão corrige (ver Fase 10).

Resumo das mudanças:

1. **Fase 10 reescrita**: `rename_function` (renomeação real na IDB do
   Ghidra) trocado por plate comments + entrada em `symbols/functions.json`,
   mantendo uma única fonte de verdade sobre nomes.
2. **Segurança do túnel MCP** documentada como risco explícito, com
   mitigação sugerida.
3. **Escopo de push direto na `main`** restrito explicitamente a artefatos
   de análise (`decompiled/`, `NN_*.txt/json`) — `recomp/` segue fluxo de
   revisão à parte, definido em `PLANO_RECOMP.md`.
4. **Nova Fase 8.5 (Handoff)**: todo lote decompilado aqui alimenta
   automaticamente o pipeline de recomp.
5. **Métrica de coverage unificada**: `progress/coverage.json` (definido em
   `PLANO_RECOMP.md`) passa a ser a fonte oficial de progresso; a tabela da
   seção 7 deste documento vira snapshot histórico, não fonte viva.
6. **Estimativa de tempo recalibrada** após o primeiro lote grande da Fase 8,
   em vez de extrapolação linear da amostra prioritária.

---

## 1. Alvo

| Campo | Valor |
|-------|-------|
| **Binário** | `DaybreakDX.exe` |
| **Caminho original** | `/mnt/hdexterno/Games/Higurashi Daybreak/DaybreakDX.exe` |
| **Jogo** | Higurashi Daybreak (Twilight Frontier / 07th Expansion) |
| **Formato** | Portable Executable (PE) |
| **Arquitetura** | x86 32-bit LE |
| **Compilador** | MSVC (Windows) |
| **Image base** | `0x00400000` |
| **Tamanho em memória** | ~2.86 MB |
| **Total de funções** | 4,092 |
| **Símbolos** | 39,002 |
| **Tipos de dados** | 464 |

## 2. Stack de análise

- **Engine de RE**: Ghidra 11.x com projeto carregado
- **Plugin MCP**: GhidraMCP v1.28.1 (192 ferramentas)
- **Transporte**: Streamable HTTP via `mcp-proxy` na porta 8081
- **Túnel público**: Cloudflare Quick Tunnel (`trycloudflare.com`)
- **Cliente**: Super Z (GLM) invocando o MCP via `curl`/Python
- **File server**: FileVault (próprio) para compartilhar artefatos com o operador

### 2.1 Nota de segurança sobre o túnel (novo)

O túnel expõe as 192 ferramentas do GhidraMCP publicamente, incluindo
operações de **escrita** (renomeação, comentários, potencialmente edição de
bytes), não só leitura. Uma URL `trycloudflare.com` é efêmera mas não é
secreta por design — qualquer pessoa que capture a URL enquanto o túnel está
ativo pode interagir com o projeto.

**Ação requerida**: confirmar se o `mcp-proxy` está configurado com
autenticação por token nesta topologia. Se não estiver:
- Restringir a superfície exposta a ferramentas read-only quando o túnel
  estiver ativo, ou
- Limitar a janela de tempo em que o túnel fica no ar (subir só durante a
  sessão ativa de trabalho, derrubar depois), ou
- Aceitar o risco explicitamente e documentar aqui a justificativa.

Enquanto isso não for decidido, tratar como risco aberto, não como detalhe
de infraestrutura.

## 3. Segmentos (memory layout)

```
Headers : 0x00400000 - 0x00400fff
.text   : 0x00401000 - 0x006a0fff   (código executável)
.rdata  : 0x006a1000 - 0x006b6fff   (somente leitura / strings)
.data   : 0x006b7000 - 0x006d9d07   (read/write)
.rsrc   : 0x006da000 - 0x006dafff   (resources)
tdb     : 0xffdff000 - 0xffdfffff   (TIB/TEB)
```

## 4. Fases planejadas

### Fase 1 — Reconhecimento ✅
- [x] Entry points
- [x] Segmentos
- [x] Exports
- [x] Imports (superfície de API)
- [x] Strings (amostra inicial)

**Arquivos**: `01_*.txt`

### Fase 2 — Mapeamento ✅
- [x] Listar todas as 4.092 funções com flags (thunk/external)
- [x] Isolar 1.005 funções nomeadas
- [x] Isolar 3.087 `FUN_*` não-nomeadas

**Arquivos**: `02_*.txt`, `02_named_functions.txt`

### Fase 3 — Priorização ✅
- [x] Selecionar funções por critérios:
  - Entry point
  - Funções nomeadas com keywords (Load, Init, Render, Draw, Game, Update, Scene, etc.)
  - Top funções nomeadas restantes
- [x] Total: 86 funções prioritárias

**Arquivos**: `03_priority_functions.{txt,json}`

### Fase 4 — Decompilação das prioritárias ✅
- [x] Batch decompile (`batch_decompile` com batches de 5)
- [x] 86/86 funções decompiladas — **zero erros**

**Arquivos**: `decompiled/*.c` + `04_decompile_progress.json` + `04_decompile_errors.json`

### Fase 5 — Call graph analysis ✅
- [x] `get_full_call_graph` (1.000 edges amostrados)
- [x] Identificar top 20 hubs (mais chamadas recebidas)
- [x] Identificar top 20 dispatchers (mais chamadas feitas)
- [x] Buscar callers de LoadNextScene / CommonInit (via xref em tabela)

**Arquivos**: `05_*.txt`, `05_callgraph_analysis.json`

### Fase 5b — Decompilação de top hubs/dispatchers ✅
- [x] Top 10 dispatchers (0x00412110, 0x004020a0, 0x00414750, …)
- [x] Top 10 hubs internos (0x0064aed0, 0x004039d0, …)

**Arquivos**: `06_top_dispatchers.txt`, `06_top_hubs.txt`, `decompiled/FUN_*_06_*.c`

### Fase 6 — Documentação no Ghidra ✅
- [x] 35+ tags aplicadas (entry-point, win-main, scene-manager, dispatcher, directx, …)
- [x] 3 plate comments (WinMain, LoadNextScene, CommonInit)

**Nota**: este é o padrão correto a manter — anotar via tag/plate comment,
nunca via renomeação real, enquanto a decompilação não estiver completa (ver
Fase 10 revisada).

### Fase 7 — Relatório consolidado ✅
- [x] `RELATORIO_COMPLETO.md` (312 linhas, 13.7 KB)

---

## 5. Fases futuras (planejadas, não executadas)

### Fase 8 — Decompilação em massa das ~4.000 `FUN_*` restantes
- **Objetivo**: Cobertura 100% do binário
- **Estratégia**: batches de 10 funções a cada chamada MCP
- **Custo estimado**: ordem de grandeza de horas de túnel; ver nota de
  recalibração abaixo — não tratar a extrapolação linear da amostra
  prioritária como estimativa confiável.
- **Risco**: decompiler pode falhar em algumas funções (thunks, código
  obfuscado, rotinas grandes de D3D/física que podem estourar timeout ou
  gerar pseudocódigo degenerado) — esses casos vão pra `errors.json`

> **Nota de recalibração**: as 106 funções processadas até agora (~10 min)
> foram selecionadas por prioridade (nomeadas, keywords conhecidas) e
> tendem a ser mais simples de decompilar corretamente que a média. Não
> extrapolar linearmente para as ~3.987 restantes. Recalibrar a estimativa
> de tempo/erro após os primeiros 500-1.000 casos processados na Fase 8, e
> atualizar esta seção com o número real.

### Fase 8.5 — Handoff para o pipeline de recomp (novo)

Todo lote decompilado na Fase 8 (e, retroativamente, tudo que já existe em
`decompiled/`) é **input direto** do pipeline descrito em `PLANO_RECOMP.md`.
Nenhuma ação manual deveria ser necessária para essa transição — é o que
torna o projeto sustentável em vez de exigir handoff manual toda vez.

- **Gatilho**: a cada batch novo escrito em `decompiled/`, `tools/ingest.py`
  (do pipeline de recomp) detecta a mudança por hash de arquivo e agenda
  reprocessamento das funções afetadas.
- **Responsabilidade desta fase**: garantir que cada `.c` gerado em
  `decompiled/` tenha nome de arquivo estável e prefixo de endereço
  (`FUN_<addr>_*.c`), para que o `signature_hash` do pipeline de recomp
  consiga rastrear a função entre execuções.
- **Saída esperada**: nenhuma — este é um passo de infraestrutura, não de
  análise. Se `ingest.py` não conseguir mapear um arquivo novo (nome
  inconsistente, função sem endereço claro), isso deve gerar um erro visível
  aqui, não silenciosamente ficar de fora do coverage.

### Fase 9 — Análise da tabela de scene handlers
- **Endereço alvo**: `0x006a16c0` (ponteiro de função para `LoadNextScene`)
- **Hipótese**: Tabela contendo `{ scene_id, init_fn, update_fn, draw_fn, cleanup_fn }` para cada cena do jogo
- **Ação**: Ler os bytes ao redor com `read_memory`, tentar parsear como array de structs, identificar cada cena
- **Registro**: mesmo antes de confirmação, registrar a hipótese de struct em
  `symbols/types.json` (pipeline de recomp) com `confidence: low`, para não
  se perder caso a análise seja retomada depois por outro agente.

### Fase 10 — Anotação de identidade das funções (revisado)

**Esta fase foi redesenhada.** A versão anterior usava `rename_function`
para renomear diretamente no projeto Ghidra assim que uma função era
identificada. Isso contradiz a regra central do projeto (nomes reais só via
comentário até a decompilação estar completa) e cria uma segunda fonte de
verdade sobre nomes, paralela ao `symbols/functions.json` — as duas
inevitavelmente divergem com o tempo.

**Novo processo**:

1. Quando uma função tem seu comportamento identificado com confiança
   suficiente, aplicar um **plate comment** no Ghidra com o nome sugerido e
   a justificativa (mesmo padrão já usado corretamente na Fase 6 para
   WinMain/LoadNextScene/CommonInit). **Não chamar `rename_function`.**
2. Registrar a mesma sugestão em `symbols/functions.json` (pipeline de
   recomp), com `status: suggested` e `suggested_by` identificando este
   agente de extração.
3. A promoção de `suggested` → `reviewed` → `locked` acontece no pipeline de
   recomp, não aqui — esta fase só alimenta sugestões, não decide nomes
   finais.
4. A renomeação real na IDB do Ghidra (se algum dia fizer sentido, por
   conveniência de navegação humana) só deve acontecer **depois** que a
   função estiver `locked` no `symbols/functions.json`, e mesmo assim é
   opcional — o `recomp/` gerado é o artefato que importa, não a IDB.

**Critério**: toda entrada em `symbols/functions.json` criada por este
agente deve incluir o `signature_hash` da função no momento da sugestão (ver
`PLANO_RECOMP.md` seção 5.1), para permitir detecção automática de
desatualização se o decompilador gerar uma versão diferente da função depois.

### Fase 11 — Análise de multiplayer/network
- **Contexto**: Daybreak tem modo versus (network)
- **Ação**:
  - Buscar imports de `ws2_32.dll` (Winsock)
  - `search_strings` por `socket`, `connect`, `127.0.0.1`, portas
  - Decompile das funções que chamam `send`/`recv`/`connect`

### Fase 12 — Detecção de anti-analysis
- **Ação**: Rodar `detect_malware_behaviors` e `find_anti_analysis_techniques`
- **Expectativa**: Provavelmente retorna vazio (não é malware), mas confirma

### Fase 13 — Cross-version documentation archive
- **Ação**: `archive_ingest_program` para bulk-ingest de toda documentação gerada
- **Objetivo**: Manter base reutilizável para versões futuras do jogo

---

## 6. Achados-chave até agora

### 6.1 Entry path completo identificado

```
entry (0x0066c906)  ← CRT init (MSVC)
  └─ __heap_init, __mtinit, __ioinit, __cinit, __setargv, __setenvp
  └─ chama FUN_0064d250 (WinMain-equivalent)

FUN_0064d250 (WinMain)  ← janela principal
  └─ GetModuleFileNameA → descobre cwd
  └─ GetSystemMetrics → calcula bordas
  └─ WNDCLASSEXA: lpszClassName = "HigurashiDaybreak"
  └─ Tamanho da janela: 800x600 (resolução nativa)
  └─ Cria a janela principal

CommonInit (0x00543c70)  ← bootstrap
  └─ D3D device, DirectInput, áudio (chamado via tabela)

Game loop (cena atual):
  LoadNextScene(pGameState)  ← state machine dispatcher
    └─ Chamado via ponteiro em 0x006a16c0 (não call direto)
    └─ 13 scene-handlers como callees
```

### 6.2 Render stack identificada

| Camada | APIs |
|--------|------|
| **Graphics API** | Direct3D 9 (`Direct3DCreate9`) |
| **Math lib** | D3DX (25 funções mapeadas) |
| **Input** | DirectInput 8 (`DirectInput8Create`) |
| **Mesh format** | `.x` files (`D3DXLoadMeshHierarchyFromXInMemory`) |
| **Collision** | `D3DXIntersect` (ray-mesh) |
| **Audio** | Não visto ainda (provavelmente DirectMusic/Miles) |

### 6.3 Estrutura de assets

```
data/                 ← assets principais
├── bgm/              ← trilha sonora (.ogg)
├── voice/            ← vozes (.wav)
├── select/           ← UI seleção de personagens (.bmp)
├── teamselect/       ← UI seleção de times
├── keyconfig/        ← config de teclas
├── object/           ← sprites
└── stage15           ← dados de stage

Cdata/                ← assets alternativos (compat?)
├── config/
└── select/

Cmovie/               ← cutscenes FMV
├── op.mpg
└── prologue.mpg

%02d.x                ← meshes por índice
collision.x           ← mesh de colisão
collision_camera.x    ← mesh de câmera
collision_tama.x      ← mesh de projéteis (tama = 弾)
env.dat               ← environment data
```

### 6.4 Top 5 dispatchers (candidatos a game loop)

| Endereço | Out-degree | Hipótese |
|----------|------------|----------|
| `0x00412110` | 32 | Game loop principal ou update de cena |
| `0x004020a0` | 23 | Handler de cena específica |
| `0x00414750` | 23 | Handler de cena específica |
| `0x00412ac0` | 22 | Handler de cena específica |
| `0x0040f4c0` | 22 | Handler de cena específica |

---

## 7. Métricas (snapshot histórico — não é mais a fonte viva)

> A partir desta revisão, a métrica oficial de progresso é
> `progress/coverage.json`, gerado automaticamente pelo pipeline de recomp
> (ver `PLANO_RECOMP.md` seção 5.3). A tabela abaixo reflete o estado no
> momento em que este documento foi escrito e não é atualizada em tempo
> real — mantida aqui como registro histórico do início do projeto.

| Métrica | Valor no snapshot |
|---------|--------------------|
| Funções no binário | 4,092 |
| Funções decompiladas | 106 (2.6%) |
| Volume de código C | ~2.2 MB |
| Tags aplicadas no Ghidra | 35+ |
| Plate comments aplicados | 3 |
| Endpoints MCP usados | 13 |
| Erros de decompilação | 0 |
| Tempo decorrido | ~10 min |

---

## 8. Convenções de commit

- **`feat:`** nova função decompilada ou nova fase iniciada
- **`docs:`** atualização de relatório ou progresso
- **`fix:`** correção em arquivo existente
- **`chore:`** ajustes de config (`.gitignore`, scripts)
- **`refactor:`** renomeação ou reorganização de arquivos
- **`recomp:`** reservado para commits automáticos do pipeline de recomp
  (`PLANO_RECOMP.md`) — não usar este prefixo para commits de extração, para
  manter os dois pipelines distinguíveis no histórico.

### 8.1 Escopo de push direto na `main` (clarificado)

Push direto na `main` via deploy key é aceitável **apenas** para artefatos
de análise/extração:

- `decompiled/*.c`
- `NN_*.txt`, `NN_*.json` (reconhecimento, mapeamento, call graph, etc.)
- `RELATORIO_COMPLETO.md`, `PROGRESSO.md`

**Nunca** para `recomp/*.c` — esses arquivos seguem o fluxo de revisão
definido em `PLANO_RECOMP.md` (branch `recomp-auto` + merge após revisão).
Se algum script de automação futuro tocar em `recomp/`, ele deve abrir PR,
não commitar direto.

---

## 9. Estrutura do repo

```
daybreak-decomp/
├── README.md                   (criado pelo operador)
├── PLANO.md                    (este arquivo — extração/análise)
├── PLANO_RECOMP.md             (pipeline de recomposição em C legível)
├── PROGRESSO.md                (status em tempo real)
├── RELATORIO_COMPLETO.md       (relatório final consolidado)
├── .gitignore
│
├── decompiled/                 (.c brutos, um por função, alimentados continuamente)
│   ├── entry.c
│   ├── FUN_0064d250_entry_sub.c     ← WinMain
│   ├── CommonInit.c
│   ├── LoadNextScene.c
│   ├── D3DX*.c                      ← 25 funções DirectX
│   ├── FUN_00412110_*.c             ← top dispatcher
│   └── ...
│
├── recomp/                     (GERADO pelo pipeline de recomp — nunca editar à mão)
├── symbols/                    (fonte de verdade sobre nomes — ver PLANO_RECOMP.md)
│   ├── functions.json
│   ├── types.json
│   └── notes.json
├── progress/
│   └── coverage.json           (fonte oficial de progresso, gerada automaticamente)
│
├── 01_*.txt                    (reconhecimento inicial)
├── 02_*.txt                    (mapeamento de funções)
├── 03_*.txt                    (priorização)
├── 04_*.json                   (progresso/erros de decompilação)
├── 05_*.txt                    (call graph analysis)
└── 06_*.txt                    (top hubs/dispatchers)
```

---

## 10. Como reproduzir / continuar

### Setup do ambiente
1. Ghidra 11.x + plugin GhidraMCP instalado
2. Projeto aberto com `DaybreakDX.exe` carregado e analisado
3. `mcp-proxy` expondo o bridge Python em `localhost:8081`
4. `cloudflared tunnel --url http://localhost:8081` (ou porta do wrapper) —
   ver nota de segurança na seção 2.1 antes de deixar o túnel ativo sem
   supervisão
5. Token de sessão MCP obtido via `initialize`

### Cliente (este agente)
1. Helper: `python3 /home/z/my-project/scripts/ghidra_mcp.py <tool> <args> <out>`
2. Para decompilar em massa: `python3 /home/z/my-project/scripts/decompile_priority.py`
3. Para análise de call graph: `python3 /home/z/my-project/scripts/analyze_callgraph.py`
4. Para gerar relatório: `python3 /home/z/my-project/scripts/build_report.py`
5. **Novo**: após cada batch, `tools/ingest.py` (pipeline de recomp) deve
   rodar automaticamente — se estiver rodando manualmente por enquanto,
   documentar aqui até virar um hook automático (ex: git post-commit, ou
   cron simples no VPS).

### Deploy (este repo)
- Push direto na `main` via SSH deploy key (sem senha) — **restrito ao
  escopo definido na seção 8.1**
- `git config core.sshCommand "python3 /home/z/my-project/FileVault/shared/ssh.py -i /home/z/my-project/FileVault/shared/daybreak_deploy_key"`
- **Nota de segurança**: confirmar que o caminho da chave de deploy
  (`FileVault/shared/daybreak_deploy_key`) não está dentro de nenhuma pasta
  sincronizada com o repositório, para evitar commit acidental da chave.
