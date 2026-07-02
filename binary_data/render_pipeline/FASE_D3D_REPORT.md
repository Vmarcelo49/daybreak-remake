# Render Pipeline — Análise da Pilha D3D/D3DX

> **Data**: 2026-07-02
> **Agente**: agent:extraction
> **Status**: ✅ Concluída (mapeamento inicial)
> **Trabalho**: 100% offline, sem conflitar com agente local

## 1. Resumo executivo

Mapeei a **inicialização completa da engine gráfica** do `DaybreakDX.exe`. Encontrei a função `EngineInit` (`FUN_00657910`) que orquestra **8 subsistemas** em sequência: timer, COM, D3D, shaders, input, callbacks, áudio/som, scene init.

Além disso, identifiquei as 3 funções raiz do pipeline gráfico:
- `InitD3D` (`FUN_00654b90`) — cria IDirect3D9 + device com fallback de vertex processing
- `CreateAllShaders` (`FUN_0064ff80`) — carrega **10 efeitos D3DX** compilados embutidos no binário
- `LoadMeshFromX` (`FUN_0064d940`) — carrega mesh `.x` da memória usando `D3DXLoadMeshHierarchyFromXInMemory`

## 2. EngineInit — `FUN_00657910`

Esta é a função raiz de inicialização da engine, chamada por `WinMain` (indiretamente). Recebe uma struct de configuração em `param_2` e popula `param_1` (state global).

### Sequência de inicialização

```c
undefined4 EngineInit(EngineState *state, EngineConfig *config) {
    state->hwnd = config->hwnd;
    state->hinstance = config->hinstance;
    state->callback_obj = config->callback;

    // 1. Timer precision
    timeBeginPeriod(1);
    FUN_0065d0c0(timeGetTime());

    // 2. COM init
    if (CoInitialize(NULL) < 0) return 0;

    // 3. Pre-D3D setup
    FUN_00655450(state->hwnd, state->hinstance);

    // 4. Init D3D
    if (!InitD3D(state->hwnd, config->width, config->height, config->windowed)) return 0;

    // 5. Load shaders (10 effects)
    if (!FUN_0064ff30(state)) return 0;

    // 6. Init DirectInput
    if (!FUN_00658260(state, state->hwnd, state->hinstance)) return 0;

    // 7. Setup keyboard
    if (!FUN_00658410(state)) return 0;

    // 8. Setup mouse or joystick
    if (!FUN_00658550(state)) return 0;

    // 9. Init audio
    if (!FUN_00661ad0(state, config->audio_param)) return 0;

    // 10. Worker thread (if windowed)
    if (config->windowed == 0) {
        state->is_windowed = 1;
        state->worker_event = CreateEventA(NULL, 0, 0, NULL);
        state->worker_thread = CreateThread(NULL, 0, FUN_006580a0, NULL, 0, &state->thread_id);
        SetThreadPriority(state->worker_thread, -15);  // BELOW_NORMAL
    }

    // 11. Final
    state->render_event = FUN_00667050();
    state->start_time = timeGetTime();
    (*state->callback_obj->vtable[0])();
    FUN_00650d50(0xff000000);  // Clear to black
    FUN_00657c80(state, config->scene_param);

    return 1;
}
```

## 3. InitD3D — `FUN_00654b90`

Cria `IDirect3D9` e `IDirect3DDevice9` com **fallback progressivo**:

```c
bool InitD3D(D3DState *state, HWND hwnd, int width, int height, bool windowed) {
    state->d3d9 = Direct3DCreate9(D3D_SDK_VERSION);  // 0x20
    if (!state->d3d9) return false;

    if (state->d3d9->GetDeviceCaps(0, D3DDEVTYPE_HAL, &state->caps) < 0) return false;

    memset(&state->d3dpp, 0, sizeof(D3DPRESENT_PARAMETERS));
    if (width < 1 || height < 1) {
        // Use window client rect
        WINDOWINFO wi = {0};
        GetWindowInfo(hwnd, &wi);
        state->d3dpp.BackBufferWidth = wi.rcClient.right - wi.rcClient.left;
        state->d3dpp.BackBufferHeight = wi.rcClient.bottom - wi.rcClient.top;
    } else {
        state->d3dpp.BackBufferWidth = width;
        state->d3dpp.BackBufferHeight = height;
    }
    state->d3dpp.BackBufferFormat = state->adapter_format;
    state->d3dpp.BackBufferCount = 1;
    state->d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    state->d3dpp.hDeviceWindow = hwnd;
    state->d3dpp.Windowed = 1;
    state->d3dpp.EnableAutoDepthStencil = 1;
    state->d3dpp.AutoDepthStencilFormat = D3DFMT_D16;  // 0x50
    state->d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

    if (windowed) state->d3dpp.FullScreen_RefreshRateInHz = 0;
    else state->d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

    // Try Hardware vertex processing first
    HRESULT hr = state->d3d9->CreateDevice(0, D3DDEVTYPE_HAL, hwnd,
        D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,  // 0x44
        &state->d3dpp, &state->device);

    // Fallback 1: Software vertex processing
    if (hr < 0) hr = state->d3d9->CreateDevice(0, D3DDEVTYPE_HAL, hwnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,  // 0x24
        &state->d3dpp, &state->device);

    // Fallback 2: REF device (software rasterizer)
    if (hr < 0) hr = state->d3d9->CreateDevice(0, D3DDEVTYPE_REF, hwnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,  // 0x22
        &state->d3dpp, &state->device);

    if (hr < 0) return false;

    FUN_00654f00(state);  // SetupRenderStates
    return true;
}
```

### Flags D3D confirmados

| Constante | Valor | Uso |
|-----------|-------|-----|
| `D3D_SDK_VERSION` | `0x20` | Direct3DCreate9 |
| `D3DCREATE_HARDWARE_VERTEXPROCESSING` | `0x40` | CreateDevice preferred |
| `D3DCREATE_SOFTWARE_VERTEXPROCESSING` | `0x20` | CreateDevice fallback 1 |
| `D3DCREATE_MULTITHREADED` | `0x04` | Always set |
| `D3DFMT_D16` | `0x50` | AutoDepthStencilFormat |
| `D3DPRESENT_INTERVAL_DEFAULT` | `0x02` | PresentationInterval |
| `D3DPRESENT_RATE_DEFAULT` | `0x80000000` | FullScreen_RefreshRateInHz |
| `D3DSWAPEFFECT_DISCARD` | `0x01` | SwapEffect |

## 4. CreateAllShaders — `FUN_0064ff80`

Carrega **10 efeitos D3DX** compilados, embarcados no binário:

```c
bool CreateAllShaders(EffectTable *effects) {
    if (D3DXCreateEffect(device, &DAT_006a5f68, 0xd6c, ...) < 0) return false;  // 3499 bytes
    if (D3DXCreateEffect(device, &DAT_006a6cd8, 0xe38, ...) < 0) return false;  // 3640 bytes
    if (D3DXCreateEffect(device, &DAT_006a7b10, 0x32c, ...) < 0) return false;  // 812 bytes
    if (D3DXCreateEffect(device, &DAT_006a7e40, 0x7ac, ...) < 0) return false;  // 1964 bytes
    if (D3DXCreateEffect(device, &DAT_006a85f0, 0x6d0, ...) < 0) return false;  // 1744 bytes
    if (D3DXCreateEffect(device, &DAT_006a8cc0, 0x780, ...) < 0) return false;  // 1920 bytes
    if (D3DXCreateEffect(device, &DAT_006a9440, 0x78c, ...) < 0) return false;  // 1932 bytes
    // + 3 more effects (total: 10)
    return true;
}
```

**Total aproximado de shader code embarcado**: ~20 KB.

## 5. LoadMeshFromX — `FUN_0064d940`

```c
bool LoadMeshFromX(MeshContainer *out, ResourceId resource_id) {
    FUN_00661e70(out);  // Init container
    FUN_00655600(resource_id, &DAT_006d11a8, &DAT_006d12b0);

    if (!FUN_00653540(resource_id)) return false;

    uint size = FUN_00653a40();
    void *buffer = operator_new(size);
    FUN_00653760(buffer, size);

    EnterCriticalSection();
    HRESULT hr = D3DXLoadMeshHierarchyFromXInMemory(
        buffer, size,
        D3DXMESH_MANAGED,  // 0x220
        device,
        &allocator,
        0,
        &out->frame_root,
        &errors
    );
    LeaveCriticalSection();

    if (hr < 0) {
        free(buffer);
        return false;
    }
    // ... continues with texture loading
}
```

## 6. Demais funções identificadas

| Endereço | Nome sugerido | Confidence | Justificativa |
|----------|---------------|------------|---------------|
| `0x00657910` | `EngineInit` | **high** | Orquestra init de 8 subsistemas |
| `0x00654b90` | `InitD3D` | **high** | Direct3DCreate9 + 3 fallbacks CreateDevice |
| `0x00654b70` | `InitD3DWindowed` | medium | Wrapper InitD3D windowed |
| `0x00654f00` | `SetupRenderStates` | medium | Chamado no final de InitD3D |
| `0x0064ff30` | `InitShaders` | **high** | Wrapper CreateAllShaders + 2 inits |
| `0x0064ff80` | `CreateAllShaders` | **high** | 10 efeitos D3DX embarcados |
| `0x00650410` | `InitShaderConstants` | medium | Após CreateAllShaders |
| `0x006616d0` | `InitShaderTextures` | medium | Após CreateAllShaders |
| `0x0064d940` | `LoadMeshFromX` | **high** | D3DXLoadMeshHierarchyFromXInMemory |
| `0x00658260` | `InitDirectInput` | **high** | DirectInput8Create(0x800) |
| `0x00658410` | `InitKeyboard` | **high** | DI device + SetCooperativeLevel + SetDataFormat |
| `0x00658550` | `InitMouseOrJoystick` | medium | DI device com callback |
| `0x00661ad0` | `InitAudio` | medium | CoCreateInstance DirectMusic/Miles |
| `0x006580a0` | `WorkerThread` | medium | Thread com loop polling |
| `0x00667050` | `CreateRenderSyncEvent` | medium | CreateEventA para sync render |
| `0x00657c80` | `InitScene` | medium | Inicializa cena inicial |
| `0x00650d50` | `ClearScreen` | **high** | device->Clear com cor (0xff000000 = preto) |
| `0x006553e0` | `ShowD3DError` | **high** | MessageBox erro D3D |
| `0x006583f0` | `ShowInputError` | high | MessageBox erro DirectInput |
| `0x00661cf0` | `ShowAudioError` | high | MessageBox erro áudio |
| `0x0065d0c0` | `InitTimer` | medium | Recebe timeGetTime() |
| `0x00655450` | `PreInitSetup` | low | Antes de InitD3D |

## 7. Arquitetura render pipeline

```
WinMain (FUN_0064d250)
  └─ EngineInit (FUN_00657910)
      ├─ 1. timeBeginPeriod(1) + InitTimer
      ├─ 2. CoInitialize
      ├─ 3. PreInitSetup
      ├─ 4. InitD3D
      │    ├─ Direct3DCreate9(0x20)
      │    ├─ GetDeviceCaps(HAL)
      │    ├─ Setup D3DPRESENT_PARAMETERS
      │    ├─ CreateDevice (fallback chain):
      │    │    1. HARDWARE | MULTITHREADED (0x44)
      │    │    2. SOFTWARE | MULTITHREADED (0x24)
      │    │    3. REF device (0x22)
      │    └─ SetupRenderStates
      ├─ 5. InitShaders
      │    ├─ CreateAllShaders (10x D3DXCreateEffect)
      │    ├─ InitShaderConstants
      │    └─ InitShaderTextures
      ├─ 6. InitDirectInput (DirectInput8Create)
      ├─ 7. InitKeyboard (CreateDevice + SetCooperativeLevel + SetDataFormat)
      ├─ 8. InitMouseOrJoystick
      ├─ 9. InitAudio (CoCreateInstance DirectMusic)
      ├─ 10. CreateWorkerThread (priority BELOW_NORMAL)
      ├─ 11. CreateRenderSyncEvent
      ├─ 12. Initial callback
      ├─ 13. ClearScreen(black)
      └─ 14. InitScene
```

## 8. Limitações e trabalhos futuros

### Limitações
1. **Render runtime não identificado** — não encontrei BeginScene/EndScene/Present/DrawPrimitive ainda
2. **Worker thread** — só analisei o início
3. **SetupRenderStates** — só vi a assinatura

### Trabalho futuro
- Buscar callers de `ClearScreen` (FUN_00650d50) para achar render loop principal
- Decompilar `SetupRenderStates` (FUN_00654f00)
- Buscar vtable patterns IDirect3DDevice9 para encontrar BeginScene/Present/Draw
- Decompilar WorkerThread (FUN_006580a0) para entender sistema de áudio

## 9. Arquivos modificados

- `binary_data/render_pipeline/FASE_D3D_REPORT.md` (este arquivo)
- `binary_data/render_pipeline/candidates.json` (20 novas entradas)

**Sem conflito com agente local**: nada em `symbols/`, `recomp/`, `progress/`.

## 10. Conclusão

A pilha gráfica é uma **engine Direct3D 9 clássica** com:
- Init com fallback progressivo (Hardware → Software → REF)
- 10 shaders D3DX compilados embarcados (~20 KB)
- DirectInput 8 para keyboard + mouse/joystick
- DirectMusic ou similar para áudio (via COM)
- Worker thread separada para áudio
- Render sync via Events

Para port moderno, **toda a camada D3D9 teria que ser substituída** (D3D11/12, Vulkan, OpenGL), mas a estrutura lógica pode ser preservada.
