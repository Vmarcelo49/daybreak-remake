# Plano de Decompilação — DaybreakDX.exe

> Documento vivo — atualizado conforme o trabalho avança.
> Repo: https://github.com/giovanni-marchisio/daybreak-decomp

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

### Fase 7 — Relatório consolidado ✅
- [x] `RELATORIO_COMPLETO.md` (312 linhas, 13.7 KB)

---

## 5. Fases futuras (planejadas, não executadas)

### Fase 8 — Decompilação em massa das ~4.000 `FUN_*` restantes
- **Objetivo**: Cobertura 100% do binário
- **Estratégia**: batches de 10 funções a cada chamada MCP
- **Custo estimado**: ~6h de túnel + ~50 MB de código C
- **Risco**: decompiler pode falhar em algumas funções (thunks, código obfuscado) — esses casos vão pra `errors.json`

### Fase 9 — Análise da tabela de scene handlers
- **Endereço alvo**: `0x006a16c0` (ponteiro de função para `LoadNextScene`)
- **Hipótese**: Tabela contendo `{ scene_id, init_fn, update_fn, draw_fn, cleanup_fn }` para cada cena do jogo
- **Ação**: Ler os bytes ao redor com `read_memory`, tentar parsear como array de structs, identificar cada cena

### Fase 10 — Renomeação em massa
- **Objetivo**: Renomear as `FUN_*` cujo comportamento foi identificado
- **Ferramenta**: `rename_function` (192 ferramentas MCP)
- **Critério**: Comentar o motivo da renomeação no plate comment

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

## 7. Métricas até agora

| Métrica | Valor |
|---------|-------|
| Funções no binário | 4,092 |
| Funções decompiladas | 106 (2.6%) |
| Volume de código C | ~2.2 MB |
| Tags aplicadas no Ghidra | 35+ |
| Plate comments aplicados | 3 |
| Endpoints MCP usados | 13 |
| Erros de decompilação | 0 |
| Tempo decorrido | ~10 min |
| Tempo estimado p/ 100% | ~6h adicionais |

---

## 8. Convenções de commit

- **`feat:`** nova função decompilada ou nova fase iniciada
- **`docs:`** atualização de relatório ou progresso
- **`fix:`** correção em arquivo existente
- **`chore:`** ajustes de config (`.gitignore`, scripts)
- **`refactor:`** renomeação ou reorganização de arquivos

---

## 9. Estrutura do repo

```
daybreak-decomp/
├── README.md                   (criado pelo operador)
├── PLANO.md                    (este arquivo)
├── PROGRESSO.md                (status em tempo real)
├── RELATORIO_COMPLETO.md       (relatório final consolidado)
├── .gitignore
│
├── decompiled/                 (106 arquivos .c individuais)
│   ├── entry.c
│   ├── FUN_0064d250_entry_sub.c     ← WinMain
│   ├── CommonInit.c
│   ├── LoadNextScene.c
│   ├── D3DX*.c                      ← 25 funções DirectX
│   ├── FUN_00412110_*.c             ← top dispatcher
│   └── ...
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
4. `cloudflared tunnel --url http://localhost:8081` (ou porta do wrapper)
5. Token de sessão MCP obtido via `initialize`

### Cliente (este agente)
1. Helper: `python3 /home/z/my-project/scripts/ghidra_mcp.py <tool> <args> <out>`
2. Para decompilar em massa: `python3 /home/z/my-project/scripts/decompile_priority.py`
3. Para análise de call graph: `python3 /home/z/my-project/scripts/analyze_callgraph.py`
4. Para gerar relatório: `python3 /home/z/my-project/scripts/build_report.py`

### Deploy (este repo)
- Push direto na `main` via SSH deploy key (sem senha)
- `git config core.sshCommand "python3 /home/z/my-project/FileVault/shared/ssh.py -i /home/z/my-project/FileVault/shared/daybreak_deploy_key"`
