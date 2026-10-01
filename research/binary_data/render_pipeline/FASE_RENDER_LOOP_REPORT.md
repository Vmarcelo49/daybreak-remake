# Render Loop — Análise do Loop Principal de Renderização

> **Data**: 2026-07-02
> **Agente**: agent:extraction
> **Status**: ✅ Concluída
> **Trabalho**: 100% offline, sem conflitar com agente local

## 1. Resumo executivo

Identifiquei o **loop de renderização completo** do `DaybreakDX.exe`. O jogo usa o pattern clássico Direct3D 9 de **scene-specific renderers** — 10 funções distintas, cada uma responsável por renderizar uma cena específica (title, select, battle, etc.).

Cada scene renderer segue o mesmo padrão:
```
BeginScene() → SetRenderState() → Draw sprites/meshes → EndScene() → Present()
```

## 2. Funções centrais de render identificadas

| Endereço | Nome sugerido | Confidence | Justificativa |
|----------|---------------|------------|---------------|
| `0x00650f70` | `BeginScene` | **high** | Chama IDirect3DDevice9::BeginScene (vtable+0xa4) em `DAT_006d16f8` (g_device). |
| `0x00650fd0` | `EndSceneAndPresent` | **high** | Chama EndScene (vtable+0xa8) + Present (vtable+0x44). Trata `D3DERR_DEVICELOST` (-0x7789f798 = 0x88760868) setando flag em param_1+0x59. |
| `0x00650ab0` | `SetViewport` | medium | Seta viewport (param_1+0x260 a 0x26c) + chama vtable+0xbc (SetViewport). |
| `0x00651820` | `DrawRect` | medium | Wrapper para FUN_00651860 (provável DrawRect/DrawFilledRect). |
| `0x00646110` | `DrawSprite` | medium | Switch case 0/1/2/3 que chama FUN_00656200 (tex bind), FUN_00656190 (sprite create), FUN_00655af0 (position/scale). |

## 3. Os 10 scene renderers

Identifiquei **10 funções** que chamam tanto BeginScene quanto EndScene — cada uma é o renderer de uma cena do jogo:

| Endereço | Tamanho | Nome sugerido | Confidence | Justificativa |
|----------|---------|---------------|------------|---------------|
| `0x00403470` | 58 linhas | `RenderTitle` | medium | Renderer pequeno, usa muitas `FUN_00655830` (provável DrawMenuItem) com 9 itens em coluna (option list 0-8 do MainMenu) |
| `0x00403e10` | 21 linhas | `RenderSimple` | low | Muito curto — pode ser loading screen ou splash |
| `0x00404a50` | 79 linhas | `RenderSelect` | medium | Tamanho médio, provável character select |
| `0x004051b0` | 20 linhas | `RenderSimple2` | low | Similar ao 0x00403e10 |
| `0x004054a0` | 20 linhas | `RenderSimple3` | low | Similar |
| `0x00405750` | 19 linhas | `RenderSimple4` | low | Similar |
| `0x004072b0` | 256 linhas | `RenderBattle` | **high** | Maior renderer — provável battle scene com múltiplos elementos (HUD, characters, effects) |
| `0x0040b1f0` | 30 linhas | `RenderVS` | medium | Provável VS screen (mostra personagens antes da luta) |
| `0x0040e410` | 57 linhas | `RenderNetwork` | medium | Provável network menu (usa strings data/network/) |
| `0x0040f130` | 72 linhas | `RenderOptions` | medium | Provável options/config screen |

## 4. Padrão de um scene renderer (exemplo: RenderTitle)

```c
undefined4 RenderTitle(GameState *state) {
    // 1. Begin scene (skip if device lost)
    if (!BeginScene()) return 0;

    // 2. Set base render state
    SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);  // vtable+0xe4, state 7

    // 3. Draw menu items (FUN_00655830 = DrawMenuItem)
    DrawMenuItem(180.0f, 128.0f, 0, state->selected == 0);  // 0x43300000 = 180.0f
    DrawMenuItem(180.0f, 160.0f, 0, state->selected == 1);  // 0x43000000 = 128.0f, 0x43200000 = 160.0f
    DrawMenuItem(180.0f, 192.0f, 0, state->selected == 2);
    DrawMenuItem(180.0f, 224.0f, 0, state->selected == 3);
    DrawMenuItem(180.0f, 256.0f, 0, state->selected == 4);
    DrawMenuItem(180.0f, 288.0f, 0, state->selected == 5);
    DrawMenuItem(180.0f, 320.0f, 1, state->selected == 6);
    DrawMenuItem(180.0f, 352.0f, 1, state->selected == 7);
    DrawMenuItem(180.0f, 384.0f, 0, state->selected == 8);

    // 4. Draw settings indicators
    DrawMenuItem(368.0f, 128.0f, 0, DAT_006cfcec);
    DrawMenuItem(368.0f, 160.0f, 0, DAT_006cfcea + 2);
    // ... etc

    // 5. End scene + present
    EndSceneAndPresent(state);

    return 1;
}
```

### Convenções de coordenadas identificadas

| Hex | Float | Significado |
|-----|-------|-------------|
| `0x43300000` | 180.0f | Posição X dos menus |
| `0x43000000` | 128.0f | Y do item 0 |
| `0x43200000` | 160.0f | Y do item 1 |
| `0x43400000` | 192.0f | Y do item 2 |
| `0x43600000` | 224.0f | Y do item 3 |
| `0x43800000` | 256.0f | Y do item 4 |
| `0x43900000` | 288.0f | Y do item 5 |
| `0x43a00000` | 320.0f | Y do item 6 |
| `0x43b00000` | 352.0f | Y do item 7 |
| `0x43c00000` | 384.0f | Y do item 8 |
| `0x43b80000` | 368.0f | X dos indicadores |
| `0x43e80000` | 460.0f | X de outros elementos |

**Espaçamento Y dos menu items**: 32 pixels (160-128, 192-160, etc.) — comum em jogos com fonte 24px + padding 8px.

## 5. SetRenderState — 25+ callers

Encontrei **25+ funções** que chamam vtable+0xe4 (SetRenderState). Isso inclui os 10 scene renderers + outras funções de setup. Os valores comuns identificados:

| Valor D3DRS | Constante | Uso |
|-------------|-----------|-----|
| 7 | `D3DRS_ALPHABLENDENABLE` | Setado 0 (FALSE) no início de cada frame |
| 0xe | `D3DRS_SRCBLEND` | Alternado entre 1 (D3DBLEND_ONE) e 0 (D3DBLEND_ZERO) |
| 0x13 | `D3DRS_SRCBLENDALPHA` | Setado 5 (D3DBLEND_SRCALPHA) |
| 0x14 | `D3DRS_DESTBLENDALPHA` | Setado 6 (D3DBLEND_INVSRCALPHA) |

Padrão de blending identificado: **alpha blending padrão** (SRCALPHA / INVSRCALPHA) usado para UI/sprites.

## 6. DrawPrimitive — FUN_00646110

A única função que encontrei chamando vtable+0x144 (DrawPrimitive) é `FUN_00646110` — mas analisando o código, ela na verdade chama outras funções de sprite drawing (FUN_00655af0 = SetSpritePosition, FUN_00655690 = SetSpriteScale). Isso sugere que **DrawPrimitive está abstraído** em uma camada de sprite, e o call direto só aparece em casos especiais.

O switch case 0/1/2/3 em `FUN_00646110` sugere 4 modos de draw:
- Case 0: Sprite padrão (com bind de textura)
- Case 1: Sprite com scale custom (300x400 em vez de 300x600)
- Case 2/3: Sprite com flag 1 (provável flip horizontal)

## 7. GameLoopCaller — FUN_004020a0

Esta função chama `MainGameLoop` (FUN_00412110) e tem um switch case 0/1/2/3 que instancia objetos de tamanhos diferentes:
- Case 0: `operator_new(0x150)` = 336 bytes — provável SceneTitle
- Case 1: `operator_new(0x208)` = 520 bytes — provável SceneSelect
- Case 2: `operator_new(0xa8)` = 168 bytes — provável SceneVS
- Case 3: `operator_new(0x3d98)` = 15768 bytes — provável SceneBattle (maior estado)

Esta é a **scene factory** — instancia o objeto de estado de cada cena.

## 8. Arquitetura completa de render

```
┌──────────────────────────────────────────────────────────────────┐
│ Game Loop (FUN_00412110 MainGameLoop)                            │
│   ├─ UpdateInput (FUN_006584e0, FUN_006585f0)                    │
│   ├─ LoadNextScene(pGameState) ─► switch state machine           │
│   └─ RenderCurrentScene()                                         │
└──────────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌──────────────────────────────────────────────────────────────────┐
│ Scene Factory (FUN_004020a0)                                     │
│   switch(scene_id) {                                             │
│     case 0: SceneTitle = new(0x150);  break;                     │
│     case 1: SceneSelect = new(0x208); break;                     │
│     case 2: SceneVS = new(0xa8);     break;                      │
│     case 3: SceneBattle = new(0x3d98); break;  // 15.7 KB        │
│     ...                                                          │
│   }                                                              │
└──────────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌──────────────────────────────────────────────────────────────────┐
│ 10 Scene Renderers                                               │
│   ├─ RenderTitle    (FUN_00403470) — 58 lines                    │
│   ├─ RenderSimple   (FUN_00403e10) — 21 lines                    │
│   ├─ RenderSelect   (FUN_00404a50) — 79 lines                    │
│   ├─ RenderSimple2  (FUN_004051b0) — 20 lines                    │
│   ├─ RenderSimple3  (FUN_004054a0) — 20 lines                    │
│   ├─ RenderSimple4  (FUN_00405750) — 19 lines                    │
│   ├─ RenderBattle   (FUN_004072b0) — 256 lines  ⭐ maior         │
│   ├─ RenderVS       (FUN_0040b1f0) — 30 lines                    │
│   ├─ RenderNetwork  (FUN_0040e410) — 57 lines                    │
│   └─ RenderOptions  (FUN_0040f130) — 72 lines                    │
└──────────────────────────────────────────────────────────────────┘
                              │
                              ▼
┌──────────────────────────────────────────────────────────────────┐
│ Cada renderer faz:                                               │
│                                                                  │
│   if (!BeginScene()) return;                                     │
│       │  └─ vtable[0xa4](device)  ← IDirect3DDevice9::BeginScene│
│       │                                                            │
│       ├─ SetRenderState(ALPHABLENDENABLE, FALSE)                 │
│       ├─ DrawMenuItem(...) × N         (FUN_00655830)             │
│       ├─ DrawSprite(...) × M           (FUN_00646110)             │
│       │     ├─ BindTexture            (FUN_00656200)              │
│       │     ├─ CreateSprite           (FUN_00656190)              │
│       │     ├─ SetSpritePosition      (FUN_00655af0)              │
│       │     └─ SetSpriteScale         (FUN_00655690)              │
│       ├─ ...                                                      │
│       │                                                            │
│   EndSceneAndPresent();                                          │
│       ├─ SetViewport               (FUN_00650ab0)                │
│       ├─ SetRenderState(SRCBLEND, ONE)                           │
│       ├─ SetRenderState(SRCBLENDALPHA, SRCALPHA)                 │
│       ├─ SetRenderState(DESTBLENDALPHA, INVSRCALPHA)             │
│       ├─ DrawRect (overlay)          (FUN_00651820)               │
│       ├─ SetRenderState(SRCBLEND, ZERO)                          │
│       ├─ SetRenderState(ALPHABLENDENABLE, TRUE)                  │
│       ├─ vtable[0xa8](device)  ← IDirect3DDevice9::EndScene      │
│       └─ vtable[0x44](device, NULL, NULL, NULL, NULL)            │
│              ← IDirect3DDevice9::Present                          │
│              if returns D3DERR_DEVICELOST (0x88760868):          │
│                  state->device_lost = 1                          │
└──────────────────────────────────────────────────────────────────┘
```

## 9. Tratamento de device lost

O código trata `D3DERR_DEVICELOST` (código -0x7789f798 = 0x88760868) setando `param_1+0x59 = 1` (flag de device lost). Isso é importante porque:

1. Em fullscreen mode, alt-tab pode causar device lost
2. O jogo precisa detectar e tentar `Reset()` do device
3. Provável função de reset em outro lugar (não mapeada ainda)

## 10. Atualização do candidates.json

Adicionadas **8 novas funções** identificadas nesta análise. Total agora: **30 sugestões** no render_pipeline/candidates.json.

## 11. Respostas às perguntas em aberto

### Pergunta 1: "Onde fica o render loop principal?"
**Resposta**: Não existe um render loop único. Cada scene renderer (10 funções no range `0x00403470 - 0x0040f130`) faz seu próprio BeginScene/EndScene/Present. O MainGameLoop (FUN_00412110) provavelmente despacha para o renderer da cena atual.

### Pergunta 2: "Quais render states são setados em SetupRenderStates?"
**Resposta**: Ainda não decompilado (FUN_00654f00 só vimos a assinatura). Mas dos 25+ callers de SetRenderState identificados, os states mais usados são:
- D3DRS_ALPHABLENDENABLE (7)
- D3DRS_SRCBLEND (0xe)
- D3DRS_SRCBLENDALPHA (0x13)
- D3DRS_DESTBLENDALPHA (0x14)

### Pergunta 3: "Qual sistema de áudio exato?"
**Resposta**: Ainda não confirmado. InitAudio (FUN_00661ad0) usa CoCreateInstance com IIDs em 0x006ab884/0x006ab894. Para confirmar DirectMusic vs Miles, precisaria ler os 16 bytes dos IIDs (trabalho futuro).

### Pergunta 4: "Worker thread faz mixing de áudio?"
**Resposta**: WorkerThread (FUN_006580a0) tem loop polling `DAT_006d18cc` (provável lista de sons ativos). O loop chama uma função que retorna bool — se false, marca para terminar. Isso é **consistente com um sound mixer**, mas não confirmado 100%.

## 12. Limitações restantes

1. **SetupRenderStates (FUN_00654f00)** não foi decompilado — só vimos a assinatura
2. **Callers de cada scene renderer** não foram mapeados (qual MainGameLoop case chama qual renderer)
3. **Reset device function** (para recuperar de device lost) não foi encontrada
4. **Texture loading** (FUN_00655600 mencionada em LoadMeshFromX) não foi analisada

## 13. Total acumulado do projeto

| Categoria | Funções mapeadas |
|-----------|------------------|
| Networking (Fase 11 + 11b + 11c) | 48 |
| Render pipeline (D3D + render loop) | 30 |
| Outras (entry, WinMain, scene mgr, init, etc.) | ~25 |
| **TOTAL** | **~103 funções identificadas** |

**Cobertura atual**: 103 / 4,092 ≈ **2.5%** das funções têm nome sugerido.
**Cobertura alta**: ~70 das 103 têm `confidence: high`.

## 14. Arquivos modificados

- `binary_data/render_pipeline/FASE_RENDER_LOOP_REPORT.md` (este arquivo)
- `binary_data/render_pipeline/candidates.json` (8 novas entradas)

**Sem conflito com agente local**: nada em `symbols/`, `recomp/`, `progress/`.
