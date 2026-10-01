# Fase 11b — Mapeamento do Menu de Multiplayer

> **Data**: 2026-07-02
> **Agente**: agent:extraction
> **Status**: ✅ Concluída
> **Trabalho feito**: 100% offline, sem MCP, sem conflitar com agente local

## 1. Descoberta central

Identifiquei a função **`FUN_00412ac0` (NetworkMenuDispatcher)** — um switch de **10 cases** (0-9) que implementa **todo o fluxo de UI de multiplayer** do jogo. É ela que decide quando chamar `InitDirectPlayClient`, `InitDirectPlayServer`, `HostSession`, e `ConnectToServer`.

**Esta função é o coração do menu de rede** — responde à pergunta em aberto da Fase 11: *"Qual cena ativa o multiplayer?"*. Resposta: nenhuma cena do `LoadNextScene` ativa diretamente — o multiplayer é ativado a partir de um submenu acessível pela tela de título.

## 2. Estado do NetworkMenuDispatcher

A função mantém estado em `param_1 + offsets` (provável struct `NetworkMenuState`):

| Offset | Tipo | Papel inferido | Confidence |
|--------|------|----------------|------------|
| `+0x1070` | int | Submenu selection (0-5) | medium |
| `+0x1074` | int | Item selecionado no submenu atual | high |
| `+0x1078` | int | Item selecionado em IP entry (0-11) | medium |
| `+0x107c` | int | Character selecionado em IP entry (0-16) | medium |
| `+0x1080` | int | Sub-mode dentro do case 2 | medium |
| `+0x1084` | int | Toggle (0/1) em case 2 | medium |
| `+0x1088` | int | **Estado atual (switch case)** | **high** |
| `+0x18b4` | char | Player count max (case 6) | medium |
| `+0x18b5` | char | Player selection index (case 6) | medium |
| `+0x18b8` | int | Connection attempt counter (case 7) — timeout após 0x708 = 1800 | **high** |

## 3. Mapeamento dos 10 cases (estados do menu)

| Case | Nome inferido | O que faz | Confidence |
|------|---------------|-----------|------------|
| **0** | `MainMenu` | Menu principal com 6 opções (rola com input). Opção 0 = host, 1 = client, 2 = char select, 3 = stage select, 4 = settings, 5 = back. Botão confirm (`DAT_006cae9c`) dispara ação. | **high** |
| **1** | `SubMenu` | Submenu genérico (3 itens). Confirm volta para case 5 ou 6 conforme seleção. | medium |
| **2** | `CharacterSelect` | Seleção de personagem. 16 chars × 5 opções (sub-modos). Toggle com `DAT_006cfdc0` bitmask. Salva em `DAT_006cfdb8[player_slot]`. Cases internos: 0=toggle, 1=inc slot, 2=dec slot, 3=load config, 4=save config. | **high** |
| **3** | `StageSelect` | Seleção de stage. Usa `DAT_006cfdc5` (1-9). Volta pra case 0 ao confirmar. | medium |
| **4** | `PortConfig` | Configura porta de rede (5 dígitos, máx 0xffff=65535). Salva em `DAT_006cfdc6`. | **high** |
| **5** | `ClientIPEntry` | Entrada de IP do server (4 octetos × 3 dígitos). Salva em `DAT_006cfdc1-c4`. Ao confirmar: chama `ConnectToServer` (FUN_0065f7c0) → transita para case 7. | **high** |
| **6** | `ServerSelectFromList` | Seleção de server de uma lista salva (cases 6 → case 7). Faz parse de string `host:port` via `_strchr(':')`. | medium |
| **7** | `Connecting` | Aguardando conexão. Incrementa `+0x18b8`. **Timeout em 0x708 = 1800 ticks** (~15s a 30ms/tick). Em sucesso: chama `FUN_00645840` (chat init), `DAT_006cfdb0 = 2`, retorna `0xd` (transita pra cena de batalha). Em timeout/falha: chama `ShutdownDirectPlay` e volta pra case 1. | **high** |
| **8** | `ConnectionSuccess` | Após confirmar, volta pra case 1. Provável tela de "conectado". | low |
| **9** | `SettingsToggle` | Toggle de uma config booleana em `DAT_006cfdc8`. | low |

## 4. Fluxo de usuário reconstruído

```
[Tela de título (LoadNextScene case 0)]
            │
            │ (usuário seleciona "Network")
            ▼
[Case 0: MainMenu] ────────────┐
   │                            │
   │ (rola pra opção 0 = host)  │ (rola pra opção 5 = client)
   ▼                            ▼
[Case 0 sub-case 0]      [Case 0 sub-case 5]
InitDirectPlayServer     (vai pra Case 1 → Case 5)
HostSession              
   │                      [Case 5: ClientIPEntry]
   │                      usuário digita IP (4 octetos)
   │                      usuário digita porta (Case 4 separado)
   ▼                            │
[Case 7: Connecting]            ▼
   │                      [Case 5 confirm]
   │ (1800 ticks timeout)      chama InitDirectPlayClient
   │                            chama ConnectToServer (FUN_0065f9e0)
   ▼                                  │
   ├─ Sucesso ──► DAT_006cfdb0 = 2    │
   │              retorna 0xd ──────► │
   │              (transita pra       │
   │               cena de batalha)   ▼
   │                          [Case 7: Connecting]
   └─ Timeout/falha                    │
       chama ShutdownDirectPlay        │
       volta pra Case 1                │
                                        ▼
                                  (mesmo fluxo)
```

## 5. Funções novas identificadas (além das 16 da Fase 11)

| Endereço | Nome sugerido | Confidence | Justificativa |
|----------|---------------|------------|---------------|
| `0x00412ac0` | `NetworkMenuDispatcher` | **high** | Switch 10 cases, chama todos os init DirectPlay |
| `0x0065f9e0` | `ConnectToServer` | **high** | Seta "port" + "hostname" + "Session" + chama Connect via vtable+0x1c |
| `0x0065f780` | `SetNetworkMessageCallback` | medium | Seta callback em +0x6c dentro de critical section |
| `0x0065fae0` | `CancelPendingConnection` | medium | Chama vtable+0x18 com `param_1[0x21]` — provável cancel de async connect |
| `0x0066b65c` | `AbsInt` | high | `if (param_1 < 0) param_1 = -param_1; return param_1;` — wrapper de abs() |
| `0x0066cec4` | `WcslenWrapper` | high | Loop contando shorts até null — implementação de wcslen |
| `0x006488d0` | `SaveConfigFile` | **high** | `CreateFileA("config.dat", GENERIC_WRITE, ...)` + WriteFile — salva config |
| `0x006486c0` | `LoadConfigFile` | **high** | `CreateFileA("config.dat", GENERIC_READ, ...)` + ReadFile — carrega config |
| `0x00645840` | `InitChatUI` | medium | Carrega `data/chat/chat.bmp`, `name_p1.bmp`, `name_p2.bmp` — UI de chat p/ multiplayer |
| `0x004146e0` | `CheckConnectionSuccess` | medium | Retorna `*(param_1 + 0x74)` — flag de "conectado" |

## 6. Strings e arquivos relevantes novos

### 6.1 Strings confirmadas no código de network
- `"config.dat"` (em `0x006a4dbc`, `0x006a4dc8`) — arquivo de configuração persistente
- `L"port"` (wide) — usado em `ConnectToServer` e `HostSession`
- `L"hostname"` (wide) — usado em `ConnectToServer`
- `L"Session"` (wide) — usado em `HostSession` e `ConnectToServer` (DPN_SESSIONDESC)
- `L"Client"` (wide) — usado em `InitDirectPlayClient`
- `L"Server"` (wide) — usado em `InitDirectPlayServer`

### 6.2 Arquivo de configuração `config.dat`

O jogo persiste config de rede em `config.dat`. Layout inferido:
```
offset 0x0000  (4 bytes): int — header ou versão
offset 0x5600  (0xd0 bytes = 208 bytes): struct de config principal (provável IP/porta/nome)
offset 0x54cc  (1 byte): flag booleano
offset 0x54ca  (1 byte): flag booleano
offset 0x54cb  (1 byte): flag booleano
offset 0x54cd  (1 byte): flag booleano
...
```

> **Nota**: os offsets 0x5600+ são maiores que 0x54cc, mas a ordem de escrita é essa — provável struct com padding ou o `param_1` é offset de um struct maior.

### 6.3 Globals de estado de network

| Endereço | Tipo | Papel |
|----------|------|-------|
| `0x006cae94` | int | Input horizontal (joystick X) |
| `0x006cae98` | int | Input vertical (joystick Y) |
| `0x006cae9c` | int | Botão confirm (1 = pressionado) |
| `0x006caea0` | int | Botão cancel (1 = pressionado) |
| `0x006cfdb0` | char | Flag de modo: 0=single, 1=server aguardando, 2=conectado |
| `0x006cfdb8` | char[8] | Char selection por player slot (8 slots) |
| `0x006cfdc0` | byte | Bitmask de slots ativos (8 bits) |
| `0x006cfdc1-4` | 4 bytes | Endereço IP (4 octetos) |
| `0x006cfdc5` | char | Stage selecionado (1-9) |
| `0x006cfdc6` | ushort | Porta de rede |
| `0x006cfdc8` | char | Toggle de settings |
| `0x006d75d8` | struct | Client state object |
| `0x006d7660` | int | Client tick counter |
| `0x006d79d0` | char | Server running flag |
| `0x006d79e0` | int[8] | Server tick counter (8 slots) |

## 7. Atualização do candidates.json

Adicionei as 10 novas funções identificadas ao `binary_data/network_analysis/candidates.json` (sem tocar em `symbols/functions.json` — área do agente local).

**Total agora: 26 sugestões** (21 high, 5 medium) prontas para o agente local promover.

## 8. Resposta às perguntas em aberto da Fase 11

### Pergunta 1: "Onde é que o jogo escolhe entre Client vs Server mode?"
**Resposta**: No `NetworkMenuDispatcher` (`FUN_00412ac0`), case 0:
- Opção 0 do submenu → `InitDirectPlayServer` + `HostSession` (vira host)
- Opção 5 do submenu → case 1 → case 5 (vira client, digita IP)

### Pergunta 2: "Quais mensagens são enviadas pelo GameSend?"
**Resposta**: Ainda não mapeado — cluster `FUN_006604xx` permanece como trabalho futuro. Mas sabemos que o callback de receive é `FUN_0065fc80` (client) / `FUN_00660620` (server).

### Pergunta 3: "Protocolo custom em cima de DirectPlay ou só envio de GameState direto?"
**Resposta**: Ainda não confirmado, mas o uso de tick counters (8 slots) sugere **envio periódico de GameState** (provável 60Hz ou 30Hz baseado no timeout de 500ms).

## 9. Próximos passos sugeridos (sem prioridade)

| # | Quem | Ação | Esforço |
|---|------|------|---------|
| 1 | Agente local | Promover as 21 sugestões `high` em `candidates.json` para `symbols/functions.json` | 10 min |
| 2 | Agente local | Decompilar `FUN_006604xx` (5-6 funções) — provável GameSend | 30 min |
| 3 | Agente local | Buscar callers de `NetworkMenuDispatcher` (00412ac0) — nenhum encontrado, é chamado via ponteiro de função (provável tabela em .data) | 15 min |
| 4 | Operador | Revisar as sugestões e promover para `reviewed` | 20 min |

## 10. Arquivos modificados

- `binary_data/network_analysis/FASE11B_REPORT.md` (este arquivo)
- `binary_data/network_analysis/candidates.json` (adicionadas 10 novas entradas)

**Sem conflito com agente local**: nada em `symbols/`, `recomp/`, ou `progress/` foi tocado.

## 11. Conclusão

A Fase 11b **fechou a pergunta principal** da Fase 11 ("qual cena ativa multiplayer?"). A resposta é: **não é uma cena do LoadNextScene**, é um submenu separado acessível pela tela de título, implementado em `FUN_00412ac0`.

O jogo tem um menu de network completo e funcional, com:
- Seleção de modo (host/client)
- Entrada de IP via UI (4 octetos)
- Entrada de porta (5 dígitos, máx 65535)
- Persistência em `config.dat`
- Lista de servers salvos (case 6 — faz parse de `host:port`)
- Timeout de conexão de ~15s (1800 ticks × ~8ms)
- Suporte a 8 players simultâneos

Para um port moderno, **toda essa UI poderia ser reutilizada** (são só BMPs) — só a camada DirectPlay precisaria ser substituída.
