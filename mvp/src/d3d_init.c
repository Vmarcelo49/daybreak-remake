/**
 * d3d_init.c — InitD3D (translated from FUN_00654b90)
 *
 * Uses MinGW COM-style macros (IDirect3D9_Method(p, args)) for C compatibility.
 *
 * Original behavior:
 *   1. Direct3DCreate9(D3D_SDK_VERSION = 0x20)
 *   2. GetDeviceCaps(0, D3DDEVTYPE_HAL, &caps)
 *   3. Setup D3DPRESENT_PARAMETERS
 *   4. CreateDevice with 3-fallback chain:
 *      a) D3DDEVTYPE_HAL + D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED (0x44)
 *      b) D3DDEVTYPE_HAL + D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED (0x24)
 *      c) D3DDEVTYPE_REF + D3DCREATE_SOFTWARE_VERTEXPROCESSING (0x22)  [last resort]
 *   5. SetupRenderStates (FUN_00654f00) — TODO: not yet decompiled
 */

#include "engine.h"
#include "d3d_utils.h"

bool InitD3D(EngineState *state, HWND hwnd, int width, int height, bool windowed)
{
    /* 1. Create IDirect3D9 */
    state->d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
    if (!state->d3d9) {
        ShowError("Direct3DCreate9 failed. DirectX 9 may not be available.",
                  "D3D Init Error");
        return false;
    }

    /* 2. Get adapter caps */
    HRESULT hr = IDirect3D9_GetDeviceCaps(state->d3d9,
                                          D3DADAPTER_DEFAULT,
                                          D3DDEVTYPE_HAL,
                                          &state->caps);
    if (FAILED(hr)) {
        ShowError("GetDeviceCaps failed for HAL device",
                  "D3D Init Error");
        return false;
    }

    /* 3. Get current display mode (for back buffer format) */
    D3DDISPLAYMODE display_mode;
    hr = IDirect3D9_GetAdapterDisplayMode(state->d3d9,
                                          D3DADAPTER_DEFAULT,
                                          &display_mode);
    if (FAILED(hr)) {
        ShowError("GetAdapterDisplayMode failed",
                  "D3D Init Error");
        return false;
    }
    state->adapter_format = display_mode.Format;

    /* 4. Setup presentation parameters */
    memset(&state->d3dpp, 0, sizeof(D3DPRESENT_PARAMETERS));
    state->d3dpp.BackBufferWidth = (width < 1) ? DAYBREAK_WINDOW_WIDTH : width;
    state->d3dpp.BackBufferHeight = (height < 1) ? DAYBREAK_WINDOW_HEIGHT : height;
    state->d3dpp.BackBufferFormat = state->adapter_format;
    state->d3dpp.BackBufferCount = 1;
    state->d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
    state->d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    state->d3dpp.hDeviceWindow = hwnd;
    state->d3dpp.Windowed = windowed ? TRUE : FALSE;
    state->d3dpp.EnableAutoDepthStencil = TRUE;
    state->d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    state->d3dpp.Flags = 0;
    state->d3dpp.FullScreen_RefreshRateInHz = windowed ? 0 : D3DPRESENT_RATE_DEFAULT;
    state->d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

    /* 5. CreateDevice with 3-fallback chain (matches original) */
    hr = IDirect3D9_CreateDevice(state->d3d9,
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        hwnd,
        CREATEFLAGS_HARDWARE,  /* 0x44 — HW vertex processing + multithreaded */
        &state->d3dpp,
        &state->device);

    if (FAILED(hr)) {
        /* Fallback 1: Software vertex processing */
        hr = IDirect3D9_CreateDevice(state->d3d9,
            D3DADAPTER_DEFAULT,
            D3DDEVTYPE_HAL,
            hwnd,
            CREATEFLAGS_SOFTWARE,  /* 0x24 */
            &state->d3dpp,
            &state->device);
    }

    if (FAILED(hr)) {
        /* Fallback 2: Reference rasterizer (software, slow but always works) */
        hr = IDirect3D9_CreateDevice(state->d3d9,
            D3DADAPTER_DEFAULT,
            D3DDEVTYPE_REF,
            hwnd,
            CREATEFLAGS_REF,  /* 0x22 */
            &state->d3dpp,
            &state->device);
    }

    if (FAILED(hr)) {
        ShowError("CreateDevice failed in all 3 modes (HAL/HW, HAL/SW, REF).\n"
                  "DirectX 9 may not be installed.",
                  "D3D Init Error");
        return false;
    }

    /* 6. SetupRenderStates — TODO: original calls FUN_00654f00(state) here.
     * For MVP, we set the minimum render states we know are used:
     *   - D3DRS_ALPHABLENDENABLE = FALSE (set by every scene renderer)
     */
    hr = IDirect3DDevice9_SetRenderState(state->device,
                                          D3DRS_ALPHABLENDENABLE, FALSE);
    if (FAILED(hr)) {
        /* Non-fatal — continue */
    }

    return true;
}
