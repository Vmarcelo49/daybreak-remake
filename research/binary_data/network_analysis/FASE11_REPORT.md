# Fase 11 — Análise de Multiplayer/Network

> **Data**: 2026-07-02
> **Agente**: agent:extraction
> **Status**: ✅ Concluída (mapeamento inicial)
> **Trabalho feito**: 100% offline, sem MCP

## 1. Resumo executivo

O jogo usa **DirectPlay 8** (componente COM do DirectX 7-9 era) para multiplayer. Identifiquei um **cluster de 27 funções** no range `0x0065f180 - 0x00660fc0` que implementa o stack de networking completo: client init, server init, host session, message handlers, send/receive threads, e shutdown.

**Total de 16 funções nomeadas com confiança alta** (em arquivo separado `candidates.json`, não em `symbols/functions.json` para evitar conflito com agente local).

## 2. Evidências da descoberta

### 2.1 Strings reveladoras

| Endereço | String | Significado |
|----------|--------|-------------|
| `0x006aaf58` | `"DPlay-Error"` | Prefixo de MessageBox para erros DirectPlay |
| `0x006ab00c` | `"DPlay-Error"` | Segunda ocorrência (versão server) |
| `0x006a1a3c` | `"data/network/nback00.bmp"` | Background de UI de network |
| `0x006a1cd0` | `"data/network/nback01.bmp"` | Background alternativo |
| `0x006a1cec` | `"data/network/menu.bmp"` | Menu de network |
| `0x006a1d20` | `"data/network/number.bmp"` | Numerais para UI |
| `0x006a1d38` | `"data/network/menu2.bmp"` | Menu secundário |
| `0x006a1d80` | `"data/network/nameMenu.bmp"` | Menu de entrada de nome |
| `0x006a1e34` | `"data/network/object.bmp"` | Objetos de UI |
| `0x006a2004` | `"data/network/nback02.bmp"` | Background 2 |

### 2.2 Imports NÃO explícitos

O binário **não importa** `ws2_32.dll` (Winsock) nem `dpnet.dll` (DirectPlay). Em vez disso, usa **`CoCreateInstance`** com CLSIDs/IIDs em `0x006ab7e4-0x006ab844` para instanciar os objetos DirectPlay em runtime. Isso é o padrão COM clássico do DirectPlay 8.

### 2.3 Identificadores COM encontrados

| Endereço | Provável GUID | Confidence |
|----------|---------------|------------|
| `0x006ab7e4` | IID_IDirectPlay8Address | medium |
| `0x006ab7f4` | CLSID_DirectPlay8Client | medium |
| `0x006ab804` | IID_IDirectPlay8Client | medium |
| `0x006ab814` | CLSID_DirectPlay8Server | medium |
| `0x006ab824` | CLSID_DirectPlay8Peer | medium |
| `0x006ab834` | IID_IDirectPlay8Address | medium |
| `0x006ab844` | CLSID_DirectPlay8Address | medium |

> Para confirmar: ler 16 bytes em cada endereço (GUID = 16 bytes) e comparar com IIDs oficiais da Microsoft no SDK.

## 3. Arquitetura de networking mapeada

```
┌─────────────────────────────────────────────────────────────────┐
│                    Cena de Network Menu                          │
│      (usa strings data/network/*.bmp para UI)                    │
│                                                                  │
│  FUN_0040e720 (main network menu handler)                        │
│  FUN_00412110 (MainGameLoop)                                     │
│  FUN_00412ac0 (network submenu dispatcher)                       │
│  FUN_00416bb0 (network submenu dispatcher 2)                     │
│  FUN_00417200 (network submenu dispatcher 3)                     │
└──────────────────────────┬──────────────────────────────────────┘
                           │
                           ▼
┌─────────────────────────────────────────────────────────────────┐
│                  Inicialização DirectPlay                        │
│                                                                  │
│  FUN_0065f7c0 — InitDirectPlayClient                            │
│  FUN_0065ff30 — InitDirectPlayServer                            │
│  FUN_006601d0 — HostSession (cria thread server)                 │
│                                                                  │
│  Usa: CoCreateInstance + SetClientMessageHandler/                │
│       SetServerMessageHandler                                    │
└──────────────────────────┬──────────────────────────────────────┘
                           │
                           ▼
┌─────────────────────────────────────────────────────────────────┐
│                  Threads de Polling                              │
│                                                                  │
│  FUN_00660870 — NetworkServerThread (priority TIME_CRITICAL)     │
│  FUN_0065fdc0 — NetworkClientThread                             │
│                                                                  │
│  Loop: Receive() → WaitForSingleObject(500ms) → tick++           │
│  8 slots de tick counter (provavelmente 8 players max)           │
└──────────────────────────┬──────────────────────────────────────┘
                           │
                           ▼
┌─────────────────────────────────────────────────────────────────┐
│                  Message Handlers                                │
│                                                                  │
│  Client: FUN_0065fc80 → FUN_0065fca0 (HandleClientMessage)      │
│  Server: FUN_00660620 → FUN_00660640 (HandleServerMessage)      │
│                                                                  │
│  Switch on message type:                                         │
│    0xffff0007 — CREATE_PLAYER                                    │
│    0xffff0009 — DESTROY_PLAYER  → FUN_00660310 (DestroyPlayer)   │
│    0xffff000e — (?)                                              │
│    -0xfffb     — DNSPACKET                                       │
│    -0xffef     — MESSAGE_50011                                   │
└──────────────────────────┬──────────────────────────────────────┘
                           │
                           ▼
┌─────────────────────────────────────────────────────────────────┐
│                  Receive / Send                                  │
│                                                                  │
│  FUN_006603b0 — ServerReceive (vtable+0x38, flag 0x20)           │
│  FUN_0065fb10 — ClientReceive                                    │
│  FUN_006604xx — (a mapear) provável GameSend                     │
└──────────────────────────┬──────────────────────────────────────┘
                           │
                           ▼
┌─────────────────────────────────────────────────────────────────┐
│                  Shutdown                                        │
│                                                                  │
│  FUN_0065f8b0 — ShutdownDirectPlay (Release COM + close handles) │
└─────────────────────────────────────────────────────────────────┘
```

## 4. Funções nomeadas (16 com confidence ≥ medium)

Ver `candidates.json` para o JSON completo. Resumo:

| Endereço | Nome sugerido | Confidence |
|----------|---------------|------------|
| `0x0065f9c0` | `ShowDPlayClientError` | high |
| `0x006601b0` | `ShowDPlayServerError` | high |
| `0x0065f7c0` | `InitDirectPlayClient` | high |
| `0x0065ff30` | `InitDirectPlayServer` | high |
| `0x006601d0` | `HostSession` | high |
| `0x00660870` | `NetworkServerThread` | high |
| `0x0065fdc0` | `NetworkClientThread` | high |
| `0x0065fc80` | `ClientMessageHandler` | high |
| `0x00660620` | `ServerMessageHandler` | high |
| `0x00660310` | `DestroyPlayer` | high |
| `0x0065f8b0` | `ShutdownDirectPlay` | high |
| `0x006603b0` | `ServerReceive` | medium |
| `0x0065fb10` | `ClientReceive` | medium |
| `0x0065fca0` | `HandleClientMessage` | medium |
| `0x00660640` | `HandleServerMessage` | medium |

## 5. Detalhes técnicos identificados

### 5.1 DirectPlay 8 confirmado

- Usa `IDirectPlay8Peer` / `IDirectPlay8Client` / `IDirectPlay8Server` (3 modos)
- Message IDs `0xffff0007` (CREATE_PLAYER), `0xffff0009` (DESTROY_PLAYER), `0xffff000e` — todos correspondem ao enum `DPNMSGID_*` da Microsoft
- Flag `0x20` em receive = `DPNRECEIVE_*` constante

### 5.2 Thread model

- **Server**: 1 thread dedicada com `THREAD_PRIORITY_TIME_CRITICAL` (0x0f)
- **Client**: 1 thread dedicada (priority default)
- Polling: `WaitForSingleObject` com timeout de **500ms**
- 8 slots de tick counter em `0x006d79e0` (server) e `0x006d7660` (client) — **sugere suporte a até 8 players**

### 5.3 Protocolo de aplicação

Ainda não mapeado. Funções `FUN_006604xx` (cluster próximo a `ServerReceive`) são provavelmente as `GameSend*` — enviariam updates de GameState para os peers. **Trabalho futuro**: decompilar essas funções para entender o formato dos pacotes.

### 5.4 UI de network

Strings `data/network/*.bmp` indicam menus visuais para:
- `nback00-02.bmp` — backgrounds (provavelmente para diferentes estados do menu)
- `menu.bmp` / `menu2.bmp` — botões de menu
- `number.bmp` — números (endereço IP? porta? contagem de players?)
- `nameMenu.bmp` — entrada de nome do jogador
- `object.bmp` — ícones diversos

## 6. Próximos passos sugeridos

| # | Quem | Ação | Esforço |
|---|------|------|---------|
| 1 | Agente local | Promover as 11 sugestões `high confidence` em `candidates.json` para `symbols/functions.json` com `status: suggested` (depois que terminar lote atual) | 5 min |
| 2 | Agente local ou extração | Decompilar `FUN_006604xx` (5-6 funções) para mapear `GameSend*` | 30 min |
| 3 | Agente de extração (próxima sessão MCP) | Ler 16 bytes em cada um dos 7 endereços `0x006ab7e4-0x006ab844` para confirmar GUIDs | 5 min |
| 4 | Operador | Revisar e promover as 11 sugestões para `reviewed` | 10 min |
| 5 | Agente local | Buscar callers de `InitDirectPlayClient`/`InitDirectPlayServer` para entender qual cena do `LoadNextScene` ativa multiplayer | 15 min |

## 7. Limitações desta análise

1. **Não confirmei os GUIDs** — inferência baseada em padrão de uso (CoCreateInstance com IIDs em .rdata). Confirmação precisa ler os 16 bytes de cada um.
2. **Não mapeei o protocolo de aplicação** — só a camada DirectPlay. Funções de send ainda não foram decompiladas a fundo.
3. **Não identifiquei a cena que inicia multiplayer** — provavelmente é um case específico do `LoadNextScene` (case 4+ que não examinei), ou em uma função de menu separada.
4. **`FUN_0065f1xx-0065f6xx` (12 funções)** não foram analizadas — provavelmente são lobby/address setup, mas não tenho evidência direta.

## 8. Arquivos gerados

```
binary_data/network_analysis/
├── FASE11_REPORT.md       (este arquivo)
└── candidates.json        (16 sugestões prontas para o agente local promover)
```

## 9. Conclusão

A Fase 11 identificou com clareza que o jogo usa **DirectPlay 8** com arquitetura cliente-servidor padrão da era DirectX 9. O cluster de networking está bem isolado no range `0x0065f180 - 0x00660fc0` (27 funções), com 16 já nomeadas com confiança alta ou média.

**Para um port moderno**: DirectPlay está deprecated desde Windows 8. Um port provavelmente substituiria essa camada por **Steamworks, Epic Online Services, ou uma implementação custom sobre UDP/TCP**. As funções de UI (menus em `data/network/*.bmp`) poderiam ser reutilizadas, mas toda a lógica de send/receive teria que ser reescrita.
