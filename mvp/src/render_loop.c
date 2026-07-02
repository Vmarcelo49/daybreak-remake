/**
 * render_loop.c — Main render loop with BeginScene/EndScene/Present
 *
 * Translated from:
 *   - BeginScene (FUN_00650f70) — wraps IDirect3DDevice9::BeginScene
 *   - EndSceneAndPresent (FUN_00650fd0) — wraps EndScene + Present,
 *     handles D3DERR_DEVICELOST
 *   - ClearScreen (FUN_00650d50) — wraps device->Clear
 *
 * Uses MinGW COM-style macros (IDirect3DDevice9_Method(p, args)) for C compatibility.
 */

#include "engine.h"
#include "scene_defs.h"
#include "d3d_utils.h"
#include <stdio.h>

/* g_should_quit declared extern in engine.h, defined in main.c */

/* ============================================================
 * BeginScene — translated from FUN_00650f70
 * ============================================================ */

bool BeginScene(EngineState *state)
{
    if (state->device_lost) {
        return false;
    }

    HRESULT hr = IDirect3DDevice9_BeginScene(state->device);
    if (SUCCEEDED(hr)) {
        return true;
    }

    if (hr == D3DERR_DEVICELOST) {
        state->device_lost = true;
    }
    return false;
}

/* ============================================================
 * EndSceneAndPresent — translated from FUN_00650fd0
 * ============================================================ */

void EndSceneAndPresent(EngineState *state)
{
    HRESULT hr = IDirect3DDevice9_EndScene(state->device);
    if (FAILED(hr)) {
        /* Non-fatal — continue to Present */
    }

    hr = IDirect3DDevice9_Present(state->device, NULL, NULL, NULL, NULL);

    if (hr == D3DERR_DEVICELOST) {
        state->device_lost = true;
    }
}

/* ============================================================
 * ClearScreen — translated from FUN_00650d50
 * ============================================================ */

void ClearScreen(EngineState *state, D3DCOLOR color)
{
    if (!state->device) {
        return;
    }

    HRESULT hr = IDirect3DDevice9_Clear(state->device,
        0, NULL,
        D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
        color,
        1.0f,
        0);

    if (FAILED(hr)) {
        /* Non-fatal */
    }
}

/* ============================================================
 * AttemptDeviceRecovery — handles D3DERR_DEVICELOST
 * ============================================================ */

static bool AttemptDeviceRecovery(EngineState *state)
{
    HRESULT hr = IDirect3DDevice9_TestCooperativeLevel(state->device);

    if (SUCCEEDED(hr)) {
        state->device_lost = false;
        return true;
    }

    if (hr == D3DERR_DEVICENOTRESET) {
        hr = IDirect3DDevice9_Reset(state->device, &state->d3dpp);
        if (SUCCEEDED(hr)) {
            state->device_lost = false;
            IDirect3DDevice9_SetRenderState(state->device,
                                              D3DRS_ALPHABLENDENABLE, FALSE);
            return true;
        }
    }

    return false;
}

/* ============================================================
 * RunMainLoop — main game loop
 * ============================================================ */

int RunMainLoop(EngineState *state)
{
    MSG msg = {0};
    uint8_t keys[256] = {0};

    /* Initialize scene manager and load first scene (title) */
    SceneManager_Init();
    if (!LoadNextScene(state, SCENE_TITLE)) {
        ShowError("Failed to load initial title scene.",
                  "Fatal");
        return 1;
    }

    while (!g_should_quit) {
        /* 1. Process all pending Windows messages */
        while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                g_should_quit = true;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
        if (g_should_quit) {
            break;
        }

        /* 2. Read keyboard state */
        ReadKeyboardState(state, keys);

        if (keys[DIK_ESCAPE] & 0x80) {
            g_should_quit = true;
            break;
        }

        /* 3. Handle device lost */
        if (state->device_lost) {
            if (!AttemptDeviceRecovery(state)) {
                Sleep(100);
                continue;
            }
        }

        /* 4. Update current scene — may request transition to another scene */
        int next_scene = SceneManager_Update(state, keys);
        if (next_scene >= 0) {
            LoadNextScene(state, next_scene);
        }

        /* 5. Render current scene */
        SceneManager_Render(state);

        /* 6. Cap to ~60 FPS (16.67ms per frame) */
        DWORD frame_time = timeGetTime() - state->last_frame_time;
        if (frame_time < 16) {
            Sleep(16 - frame_time);
        }
        state->last_frame_time = timeGetTime();
    }

    SceneManager_Shutdown(state);
    return (int)msg.wParam;
}

/* ============================================================
 * Error reporting helper — used by all modules
 * ============================================================ */

void ShowError(const char *message, const char *title)
{
    MessageBoxA(NULL, message, title ? title : "Error", MB_OK | MB_ICONERROR);
    fprintf(stderr, "[%s] %s\n", title ? title : "Error", message);
}
