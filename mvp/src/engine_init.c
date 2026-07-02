/**
 * engine_init.c — EngineInit (translated from FUN_00657910)
 *
 * Original sequence (from FASE_D3D_REPORT.md):
 *   1. timeBeginPeriod(1) + InitTimer
 *   2. CoInitialize
 *   3. PreInitSetup (FUN_00655450) — skipped in MVP (window already created)
 *   4. InitD3D
 *   5. InitShaders (CreateAllShaders)
 *   6. InitDirectInput + InitKeyboard
 *   7. InitMouseOrJoystick — skipped in MVP
 *   8. InitAudio — skipped in MVP (no DirectMusic)
 *   9. CreateWorkerThread — skipped in MVP
 *   10. CreateRenderSyncEvent — skipped in MVP
 *   11. Initial callback — skipped in MVP
 *   12. ClearScreen(black)
 *   13. InitScene — skipped in MVP
 */

#include "engine.h"
#include "d3d_utils.h"
#include <objbase.h>
#include <mmsystem.h>

bool EngineInit(EngineState *state, HWND hwnd, HINSTANCE hinstance,
                int width, int height, bool windowed)
{
    memset(state, 0, sizeof(*state));
    state->hwnd = hwnd;
    state->hinstance = hinstance;
    state->windowed = windowed;
    state->device_lost = false;

    /* 1. Timer precision (1ms) — matches original timeBeginPeriod(1) */
    timeBeginPeriod(1);
    state->start_time = timeGetTime();
    state->last_frame_time = state->start_time;

    /* 2. COM init — required by DirectPlay + DirectMusic (stubs) + D3DX */
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr)) {
        ShowError("CoInitialize failed", "Fatal");
        return false;
    }

    /* 3. PreInitSetup — skipped (window already created by main.c) */

    /* 4. Init D3D */
    if (!InitD3D(state, hwnd, width, height, windowed)) {
        return false;  /* error already shown by InitD3D */
    }

    /* 5. Load shaders (10 D3DX effects) */
    if (!CreateAllShaders(state)) {
        return false;  /* error already shown */
    }

    /* 6. Init DirectInput + keyboard */
    if (!InitDirectInput(state, hinstance)) {
        return false;
    }
    if (!InitKeyboard(state)) {
        return false;
    }

    /* 6.5 Init stub scenes font (used by Select/VS/Battle/Network stubs) */
    extern bool InitStubScenes(EngineState *state);
    if (!InitStubScenes(state)) {
        /* Non-fatal — stubs will just show colored backgrounds */
    }

    /* 7. InitMouseOrJoystick — SKIPPED in MVP */

    /* 8. InitAudio — SKIPPED in MVP (DirectMusic stub) */

    /* 9. CreateWorkerThread — SKIPPED in MVP */

    /* 10. CreateRenderSyncEvent — SKIPPED in MVP (single-threaded render) */

    /* 11. Initial callback — SKIPPED in MVP (no scene system yet) */

    /* 12. Clear screen to black — matches FUN_00650d50(0xff000000) */
    ClearScreen(state, COLOR_BLACK);

    /* 13. InitScene — SKIPPED in MVP */

    return true;
}
