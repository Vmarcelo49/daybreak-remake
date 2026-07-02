# Fase 9 — Análise da "tabela" em 0x006a16c0

> **Data**: 2026-07-02
> **Agente**: agent:extraction
> **Status**: ✅ Concluído

## 1. Hipótese original (revisada)

Antes da análise, a hipótese era que `0x006a16c0` seria uma **tabela de scene handlers** no formato `{ scene_id, init_fn, update_fn, draw_fn, cleanup_fn }`.

## 2. Verificação via MCP

Foram lidos 256 bytes a partir de `0x006a16c0` (16 chunks de 16 bytes via `read_memory`).

### Dump dos primeiros 64 bytes (interpretados como uint32 little-endian):

```
0x006a16c0: 0x00406310  ← .text (ponteiro para LoadNextScene!)
0x006a16c4: 0x41a00000  ← float 20.0f
0x006a16c8: 0x00000000  ← NULL
0x006a16cc: 0x3e4ccccd  ← float 0.2f
0x006a16d0: 0x3f800000  ← float 1.0f
0x006a16d4: 0x43c80000  ← float 400.0f
0x006a16d8: 0x43480000  ← float 200.0f
0x006a16dc: 0x43ff0000  ← float 510.0f
0x006a16e0: 0x42c80000  ← float 100.0f
0x006a16e4: 0x41000000  ← float 8.0f
0x006a16e8: 0x42dc0000  ← float 110.0f
0x006a16ec: 0x441a8000  ← float 610.0f
0x006a16f0: 0x43020000  ← float 130.0f
0x006a16f4: 0x44188000  ← float 600.0f  ← altura da janela!
0x006a16f8: 0x42480000  ← float 50.0f
0x006a16fc: 0x43520000  ← float 210.0f
```

### Após offset 0x40 (64 bytes): strings

```
0x006a1724: "data/select/bg00.bmp"  (null-terminated)
0x006a173c: "data/select/bg01.bmp"  (null-terminated)
0x006a1754: "data/select/sbg00.bmp"
0x006a176c: "data/select/p00.bmp"
0x006a1780: "data/select/p01.bmp"
0x006a1794: "data/select/p02.bmp"
0x006a17a8: "data/select/pbg00.bmp"
...
```

## 3. Conclusão

**A hipótese original estava errada.** `0x006a16c0` **não é uma tabela de scene handlers** — é uma **struct de configuração global** que contém:

1. **Offset 0**: ponteiro para `LoadNextScene` (dispatcher)
2. **Offset 4-63**: valores float (provavelmente coordenadas/tamanhos da UI de seleção — 800x600 nativo, 50/100/130 são offsets comuns de layout)
3. **Offset 64+**: strings de paths de assets de seleção de personagem

## 4. Estrutura inferida: `SceneDispatcherConfig`

```c
struct SceneDispatcherConfig {
    void (*load_next_scene)(GameState* gs);  // 0x00: = LoadNextScene
    float field_04;                          // 0x04: = 20.0f
    void* field_08;                          // 0x08: = NULL
    float field_0c;                          // 0x0c: = 0.2f
    float field_10;                          // 0x10: = 1.0f
    float ui_offset_x;                       // 0x14: = 400.0f (centro X?)
    float ui_offset_y;                       // 0x18: = 200.0f
    float ui_width;                          // 0x1c: = 510.0f
    float field_20;                          // 0x20: = 100.0f
    float field_24;                          // 0x24: = 8.0f
    float field_28;                          // 0x28: = 110.0f
    float field_2c;                          // 0x2c: = 610.0f
    float field_30;                          // 0x30: = 130.0f
    float window_height;                     // 0x34: = 600.0f (altura da janela!)
    float field_38;                          // 0x38: = 50.0f
    float field_3c;                          // 0x3c: = 210.0f
    char asset_paths[];                      // 0x40+: strings null-terminated
};
```

`confidence: medium` — os offsets float são inferidos mas os campos de string são confirmados.

## 5. Verdadeira estrutura de scene handlers

A "tabela" de scene handlers **está dentro de `LoadNextScene`** como um switch case:

```c
switch(*(int*)(pGameState + 0x2e18)) {  // current_scene_id
  case 0: // Title screen / main menu
    FUN_00657390();  // UpdateTitleInput? (recebe char*)
    // ... inicializa estado do player 1 e 2 ...
    FUN_0064aed0(0/1/2);  // SetSceneState?
    FUN_00408050(0, ...);  // InitPlayerSlot(0)?
    FUN_005b870("data/bgm/title.ogg");  // PlayTitleBGM
    break;

  case 1: // Character select
    FUN_00406850(0);  // UpdatePlayerSelectCursor(0)?
    FUN_00406850(1);  // UpdatePlayerSelectCursor(1)?
    break;

  case 2: // VS loading screen
    FUN_0065d670();  // EnterCriticalSection
    FUN_0065d6a0();  // LeaveCriticalSection
    break;

  case 3: // Battle init (scene 3 = fight)
    // Loop over 2 players, init random character selection
    FUN_0065d150();  // GetRandomNumber (chamado 3x por player)
    FUN_00648f30(stage_id);  // LoadStage(stage_id)?
    return 8;  // → transita para scene 8 (battle)
}
```

## 6. Mapeamento dos scene handlers identificados

| FUN_* | Papel inferido | Confidence | Justificativa |
|-------|----------------|------------|---------------|
| `FUN_00657390` | `UpdateTitleScreen` | medium | Chamada só no case 0; recebe `char*` (provável input string) |
| `FUN_0064aed0` | `SetSceneState` | medium | Chamada em case 0 com argumento 0/1/2 — state transition? Top hub (18 callers) |
| `FUN_00408050` | `InitPlayerSlot` | medium | Chamada com (0, char_id) e (1, char_id) — player 1 e 2 slot init |
| `FUN_0065b870` | `PlayBGM` | **high** | Chamada com `"data/bgm/title.ogg"` como arg — quase certeza |
| `FUN_00406850` | `UpdateCharacterSelect` | medium | Chamada em case 1 (select) com player_id |
| `FUN_0065d670` | `EnterCriticalSection` | **high** | Corpo vazio + `EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 4))` |
| `FUN_0065d6a0` | `LeaveCriticalSection` | **high** | Idem, com `LeaveCriticalSection` |
| `FUN_0065d150` | `GetRandomNumber` | medium | `uint FUN_0065d150(void)`, usado com `% 3` e `% 2` — RNG |
| `FUN_00648f30` | `LoadStage` | medium | Chamada no case 3 com stage_id; provável init de battle |
| `FUN_006584e0` | `UpdateInput` | low | Chamada sempre antes do switch; interage com vtable em +0x24 |
| `FUN_006585f0` | `UpdateInput2` | low | Idem |
| `FUN_006586d0` | `IsKeyPressed` | medium | `bool FUN_006586d0(int, byte)` — checa flag `& 0x80` em offset+0x20+key |
| `FUN_0064ad70` | `ToggleFlag` | low | `DAT_006cfced = '\x01' - (DAT_006cfced != '\0')` — toggle 0/1 |

## 7. Ação: registrar descobertas

Vou atualizar:
- `symbols/types.json` — baixar hipótese `SceneHandler` para `confidence: low` (errada), adicionar `SceneDispatcherConfig` com `confidence: medium`
- `symbols/notes.json` — adicionar nota sobre descoberta
- `symbols/functions.json` — adicionar sugestões para as FUN_* identificadas

## 8. Próximos passos

- [x] Confirmar natureza de `0x006a16c0` ✅
- [x] Mapear scene handlers via switch case de LoadNextScene ✅
- [x] Sugerir nomes para 13 FUN_* chamadas pelo dispatcher ✅
- [ ] Próximo: rodar Fase 12 (`detect_malware_behaviors`) — última chamada MCP
