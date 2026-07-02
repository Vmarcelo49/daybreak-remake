# Plano de Decompilação — DaybreakDX.exe

> Documento vivo. Repo: https://github.com/giovanni-marchisio/daybreak-decomp
> Documento irmão: `PLANO_RECOMP.md` (pipeline de recomposição)
>
> **Revisão 3 (2026-07-02)**: plano realinhado com a realidade — decompilação em massa completa (3.191 funções), pipeline `tools/` implementado e funcional, dois agentes Super Z disponíveis para trabalho paralelo.

## 0. Estado atual (snapshot vivo)

| Métrica | Valor |
|---------|-------|
| Funções no binário | 4,092 |
| Funções decompiladas (`decompiled/`) | 3,191 (77.98%) |
| Funções curadas (status: reviewed/locked) | 5 |
| Funções com sugestão (status: suggested) | 1 |
| Funções unreviewed | 3,184 |
| Pipeline `tools/` | ✅ implementado |
| Métrica oficial | `progress/coverage.json` |

> **Diferença 4,092 → 3,191**: ~900 funções são thunks, externals e stubs que o decompiler não consegue processar (`errors.json` no histórico). É o teto de cobertura com Ghidra 11.x + este binário.

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
- **Túnel público**: Cloudflare Quick Tunnel (`trycloudflare.com`) — URL efêmera
- **Cliente**: Super Z (GLM) invocando o MCP via `curl`/Python
- **File server**: FileVault (próprio) para compartilhar artefatos com o operador
- **Deploy**: SSH deploy key + `git push` direto na `main`

### 2.1 Nota de segurança sobre o túnel

**Estado**: risco aceito explicitamente pelo operador durante sessões ativas de trabalho.

O túnel expõe as 192 ferramentas do GhidraMCP publicamente, incluindo operações de escrita (renomeação, comentários, edição de bytes). URL `trycloudflare.com` é efêmera mas não é secreta por design — qualquer um que capture a URL enquanto o túnel está ativo pode interagir com o projeto.

**Mitigação em uso**:
- Subir o túnel **só durante sessão ativa de trabalho**, derrubar ao finalizar
- Não aplicar plate comments/tags sensíveis durante a sessão pública sem revisão
- Em sessões futuras, considerar wrapper Express com Bearer token (já documentado em `daybreakdx-re/PLANO_RECOMP.md` original)

## 3. Segmentos (memory layout)

```
Headers : 0x00400000 - 0x00400fff
.text   : 0x00401000 - 0x006a0fff   (código executável)
.rdata  : 0x006a1000 - 0x006b6fff   (somente leitura / strings)
.data   : 0x006b7000 - 0x006d9d07   (read/write)
.rsrc   : 0x006da000 - 0x006dafff   (resources)
tdb     : 0xffdff000 - 0xffdfffff   (TIB/TEB)
```

## 4. Fases executadas

### Fase 1 — Reconhecimento ✅
- [x] Entry points, segmentos, exports, imports, strings
- **Arquivos**: `extraction_phases/01_*.txt`, `binary_data/{imports,exports,entry_points,segments_list}.txt`

### Fase 2 — Mapeamento ✅
- [x] Listar todas as 4,092 funções com flags (thunk/external)
- [x] Isolar 1,005 funções nomeadas + 3,087 `FUN_*` não-nomeadas
- **Arquivos**: `02_*.txt`, `binary_data/globals.txt`, `binary_data/data_items.txt`

### Fase 3 — Priorização ✅
- [x] Selecionar 86 funções-chave (entry, WinMain, scene mgr, DirectX, init)
- **Arquivos**: `03_priority_functions.{txt,json}`

### Fase 4 — Decompilação das prioritárias ✅
- [x] 86/86 funções decompiladas — zero erros
- **Arquivos**: `decompiled/*.c` (lote curado inicial)

### Fase 5 — Call graph analysis ✅
- [x] `get_full_call_graph` (1,000+ edges)
- [x] Top 20 hubs + top 20 dispatchers identificados
- [x] Xrefs para LoadNextScene / CommonInit confirmam padrão de tabela
- **Arquivos**: `05_*.txt`, `binary_data/callgraph/full_call_graph.txt`

### Fase 5b — Decompilação de top hubs/dispatchers ✅
- [x] Top 10 dispatchers + top 10 hubs decompilados
- **Arquivos**: `06_top_dispatchers.txt`, `06_top_hubs.txt`

### Fase 6 — Documentação no Ghidra ✅
- [x] 35+ tags aplicadas (entry-point, win-main, scene-manager, dispatcher, directx, …)
- [x] 3 plate comments (WinMain, LoadNextScene, CommonInit)
- **Padrão estabelecido**: anotar via tag/plate comment, **nunca** via `rename_function` (ver Fase 10)

### Fase 7 — Relatório consolidado ✅
- [x] `RELATORIO_COMPLETO.md` (312 linhas)

### Fase 8 — Decompilação em massa das `FUN_*` restantes ✅
- [x] 3,087/3,087 funções decompiladas em batches via `mass_decompile.py`
- [x] Zero erros
- [x] Dump completo de strings, tipos, call graph, imports, globals, data items
- **Arquivos**: `binary_data/functions/*.json` (3,087 JSONs), `decompiled/FUN_*.c` (3,087 arquivos `.c`)

### Fase 8.5 — Handoff para o pipeline de recomp ✅
- [x] Conversão JSON → `.c` em `decompiled/` no formato estável `FUN_<addr>.c`
- [x] `tools/ingest.py` implementado e rodando
- [x] `symbols/functions.json` populado com 5 sugestões iniciais + `signature_hash`
- [x] `tools/generate_recomp.py` gerando `recomp/*.c` (3,191 arquivos)
- [x] `progress/coverage.json` como métrica oficial
- **Arquivos**: `tools/{ingest,generate_recomp,coverage_report}.py`, `symbols/*.json`, `progress/coverage.json`, `recomp/`

---

## 5. Fases futuras (planejadas, NÃO executadas)

### Fase 9 — Análise da tabela de scene handlers
- **Endereço alvo**: `0x006a16c0` (ponteiro de função para `LoadNextScene`)
- **Hipótese**: tabela `{ scene_id, init_fn, update_fn, draw_fn, cleanup_fn }` por cena
- **Ação**:
  - Ler bytes da `.rdata` em `0x006a16c0` (já temos `binary_data/segments/`)
  - Parsear como array de structs
  - Identificar cada cena por nome (cruzar com strings em `binary_data/strings/`)
- **Registro**: hipótese de struct já em `symbols/types.json` com `confidence: low`

### Fase 10 — Anotação de identidade das funções (REVISADA)
**Esta fase está em andamento contínuo, não é mais um step único.**

**Processo** (alinhado com `PLANO_RECOMP.md` seção 0.1):
1. Quando uma função tem comportamento identificado, aplicar **plate comment** no Ghidra (não `rename_function`)
2. Registrar sugestão em `symbols/functions.json` com `suggested_by: "agent:extraction"` e `signature_hash`
3. Estado flui: `unreviewed → suggested → reviewed → locked`
4. Renomeação real na IDB Ghidra só após `locked` (opcional — o `recomp/` gerado é o que importa)

**Quem executa**:
- **Agente de extração** (este agente): sugere com base em call graph, strings, xrefs
- **Agente local** (segundo Super Z): sugere com base no corpo da função decompilada
- **Operador humano**: revisa e promove para `reviewed`/`locked`

### Fase 11 — Análise de multiplayer/network
- **Contexto**: Daybreak tem modo versus (network)
- **Ação**:
  - Buscar imports de `ws2_32.dll` em `binary_data/imports.txt`
  - `grep` por `socket|connect|send|recv|127.0.0.1` em `binary_data/strings/`
  - Decompile das funções que chamam APIs de rede
- **Tudo offline** — não precisa de túnel MCP

### Fase 12 — Detecção de anti-analysis
- **Ação**: Rodar `detect_malware_behaviors` e `find_anti_analysis_techniques` via MCP (última sessão antes de fechar túnel)
- **Expectativa**: provavelmente retorna vazio, mas confirma

### Fase 13 — Cross-version documentation archive (opcional)
- **Ação**: `archive_ingest_program` para bulk-ingest de toda documentação gerada
- **Objetivo**: manter base reutilizável para versões futuras do jogo
- **Quando**: só se uma versão diferente do binário surgir

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
Cmovie/               ← cutscenes FMV (.mpg)

%02d.x                ← meshes por índice
collision.x           ← mesh de colisão
collision_camera.x    ← mesh de câmera
collision_tama.x      ← mesh de projéteis (tama = 弾)
env.dat               ← environment data
```

### 6.4 Top 5 dispatchers (candidatos a game loop)

| Endereço | Out-degree | Hipótese | Status |
|----------|------------|----------|--------|
| `0x00412110` | 32 | Main game loop | `suggested` (MainGameLoop) |
| `0x004020a0` | 23 | Handler de cena | `unreviewed` |
| `0x00414750` | 23 | Handler de cena | `unreviewed` |
| `0x00412ac0` | 22 | Handler de cena | `unreviewed` |
| `0x0040f4c0` | 22 | Handler de cena | `unreviewed` |

---

## 7. Métricas

> **Fonte oficial**: `progress/coverage.json` (gerado por `tools/coverage_report.py`).
> A tabela abaixo é snapshot histórico da revisão 3.

| Métrica | Snapshot |
|---------|----------|
| Funções no binário | 4,092 |
| Funções decompiladas | 3,191 (77.98%) |
| Funções com nome revisado | 5 (0.16%) |
| Volume de código C em `decompiled/` | ~2.2 MB |
| Volume de código C em `recomp/` | ~2.5 MB |
| Tags aplicadas no Ghidra | 35+ |
| Plate comments aplicados | 3 |
| Erros de decompilação | 0 |

---

## 8. Convenções de commit

Ver `docs/conventions.md` seção 6 para detalhes. Resumo:

- `feat:` nova função decompilada ou nova fase
- `fix:` correção em arquivo existente
- `docs:` atualização de relatório ou progresso
- `chore:` ajustes de config
- `refactor:` renomeação ou reorganização
- `recomp:` reservado para commits automáticos do pipeline de recomp
- `symbols:` alterações em `symbols/*.json`

### 8.1 Escopo de push direto na `main`

- ✅ `decompiled/*.c`
- ✅ `binary_data/*`
- ✅ `symbols/*.json` (com revisão humana)
- ✅ `progress/*`
- ✅ `*.md`, `extraction_phases/*.txt`
- ❌ `recomp/*.c` — commit apenas via `tools/generate_recomp.py` ou PR manual

---

## 9. Estrutura do repo

```
daybreak-decomp/
├── README.md
├── PLANO.md                       (este arquivo — extração/análise)
├── PLANO_RECOMP.md                (pipeline de recomposição)
├── AGENT_LOCAL_ONBOARDING.md / AGENT_EXTRACTION_ONBOARDING.md               (instruções para segundo agente Super Z)
├── PROGRESSO.md                   (status em tempo real)
├── RELATORIO_COMPLETO.md          (relatório final consolidado)
├── INDEX.md / INDEX.json          (gerados pelo GitHub Action)
├── .gitignore, .clang-format
│
├── .github/
│   ├── workflows/build-index.yml  (CI: gera INDEX.md/json)
│   └── scripts/generate_index.py
│
├── decompiled/                    (3,191 .c brutos — read-only para recomp)
├── recomp/                        (3,191 .c GERADOS — nunca editar à mão)
│
├── symbols/                       (FONTE DE VERDADE)
│   ├── functions.json             (3,175 entradas, 5 revisadas)
│   ├── types.json                 (structs reconstruídas + hipóteses)
│   └── notes.json                 (observações + TODOs por função)
│
├── progress/
│   ├── coverage.json              (MÉTRICA OFICIAL de progresso)
│   └── last_ingest.json           (saída do último ingest.py)
│
├── tools/                         (pipeline scripts)
│   ├── ingest.py                  (detecta mudanças em decompiled/)
│   ├── generate_recomp.py         (gera recomp/ a partir de symbols/)
│   └── coverage_report.py         (gera progress/coverage.json)
│
├── docs/
│   └── conventions.md             (padrão de C, nomenclatura, commits)
│
├── binary_data/                   (dump bruto do MCP — referência)
│   ├── functions/                 (3,087 JSONs individuais)
│   ├── strings/                   (22 filtros diferentes)
│   ├── types/                     (14 categorias)
│   ├── callgraph/                 (1,000+ edges)
│   ├── segments/                  (Headers.bin + lista)
│   └── *.txt                      (imports, exports, globals, etc.)
│
├── extraction_phases/            (dados brutos das fases 1-6: 01_*.txt — 06_*.txt)
└── .chunks/                       (ignorado — workdir do FileVault)
```

---

## 10. Como reproduzir / continuar

### Setup do ambiente MCP (apenas se for re-extrair dados)
1. Ghidra 11.x + plugin GhidraMCP instalado
2. Projeto aberto com `DaybreakDX.exe` carregado e analisado
3. `mcp-proxy` expondo o bridge Python em `localhost:8081`
4. `cloudflared tunnel --url http://localhost:8081` — ver seção 2.1
5. Token de sessão MCP obtido via `initialize`

### Trabalho offline (caso padrão agora)
- **Helper MCP**: `python3 /home/z/my-project/scripts/ghidra_mcp.py <tool> <args> <out>`
- **Pipeline**: rodar `python3 tools/ingest.py --full` depois `python3 tools/generate_recomp.py` depois `python3 tools/coverage_report.py`
- **Busca em strings**: `grep -r "pattern" binary_data/strings/`
- **Busca em funções**: `grep -l "pattern" decompiled/*.c`

### Deploy
- Push direto na `main` via SSH deploy key
- `git config core.sshCommand "python3 /home/z/my-project/FileVault/shared/ssh.py -i /home/z/my-project/FileVault/shared/daybreak_deploy_key"`
- Chave NUNCA commitada (fora do repo, em `FileVault/shared/`)

---

## 11. Próximos passos priorizados

| # | Ação | Quem | Esforço |
|---|------|------|---------|
| 1 | **Fase 9**: analisar tabela em `0x006a16c0` | Agente de extração (Super Z) | 30 min |
| 2 | Processar lote de 50 funções `unreviewed` (top hot_spots) | Agente local (Super Z #2) | 1h |
| 3 | Promover `MainGameLoop` de `suggested` → `reviewed` após confirmar | Operador | 10 min |
| 4 | **Fase 11**: análise de multiplayer/network | Qualquer agente | 1h |
| 5 | Revisar e promover lotes de `suggested` → `reviewed` | Operador + Agente arquiteto | contínuo |
| 6 | **Fase 12**: rodar `detect_malware_behaviors` (última sessão MCP) | Agente de extração | 5 min |
