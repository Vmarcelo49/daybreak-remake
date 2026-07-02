/**
 * main.c — WinMain + window creation
 *
 * Translated from:
 *   - entry (FUN_0066c906) — MSVC CRT entry, calls WinMain
 *   - WinMain (FUN_0064d250) — registers window class "HigurashiDaybreak"
 *
 * See:
 *   - decompiled/FUN_0064d250_entry_sub.c
 *   - RELATORIO_COMPLETO.md §6.1
 */

#include "engine.h"
#include "d3d_utils.h"
#include <stdio.h>

/* Globals — minimal, just for the window proc */
static EngineState g_engine = {0};
bool g_should_quit = false;  /* declared extern in engine.h */

/* ============================================================
 * Window class registration + window creation
 * Translated from FUN_0064d250 (WinMain)
 * ============================================================ */

static bool RegisterWindowClass(HINSTANCE hInstance)
{
    WNDCLASSEXA wc = {0};
    wc.cbSize = sizeof(WNDCLASSEXA);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszClassName = DAYBREAK_WINDOW_CLASS;

    if (!RegisterClassExA(&wc)) {
        ShowError("Failed to register window class", "Fatal");
        return false;
    }
    return true;
}

static HWND CreateMainWindow(HINSTANCE hInstance, int nCmdShow)
{
    /* Original calculates window size based on GetSystemMetrics.
     * For MVP, use AdjustWindowRect which is simpler and equivalent. */
    RECT rc = {0, 0, DAYBREAK_WINDOW_WIDTH, DAYBREAK_WINDOW_HEIGHT};
    DWORD style = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
    AdjustWindowRect(&rc, style, FALSE);

    int width = rc.right - rc.left;
    int height = rc.bottom - rc.top;

    HWND hwnd = CreateWindowExA(
        0,
        DAYBREAK_WINDOW_CLASS,
        DAYBREAK_WINDOW_TITLE,
        style,
        CW_USEDEFAULT, CW_USEDEFAULT,
        width, height,
        NULL, NULL, hInstance, NULL);

    if (!hwnd) {
        ShowError("Failed to create window", "Fatal");
        return NULL;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    return hwnd;
}

/* ============================================================
 * Window procedure
 * ============================================================ */

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) {
            g_should_quit = true;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        BeginPaint(hwnd, &ps);
        EndPaint(hwnd, &ps);
        break;
    }

    default:
        break;
    }
    return DefWindowProcA(hwnd, msg, wParam, lParam);
}

/* ============================================================
 * WinMain — entry point
 * ============================================================ */

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    (void)hPrevInstance;
    (void)lpCmdLine;

    /* Step 1: Register window class */
    if (!RegisterWindowClass(hInstance)) {
        return 1;
    }

    /* Step 2: Create main window */
    HWND hwnd = CreateMainWindow(hInstance, nCmdShow);
    if (!hwnd) {
        return 1;
    }

    /* Step 3: Initialize engine (D3D + shaders + input) */
    if (!EngineInit(&g_engine, hwnd, hInstance,
                    DAYBREAK_WINDOW_WIDTH, DAYBREAK_WINDOW_HEIGHT,
                    /*windowed=*/true)) {
        ShowError("EngineInit failed. Check DirectX 9 SDK installation.",
                  "Fatal");
        return 1;
    }

    /* Step 4: Run main loop */
    int exit_code = RunMainLoop(&g_engine);

    /* Step 5: Cleanup */
    if (g_engine.device) {
        IDirect3DDevice9_Release(g_engine.device);
    }
    if (g_engine.d3d9) {
        IDirect3D9_Release(g_engine.d3d9);
    }
    ShutdownInput(&g_engine);
    DestroyAllShaders(&g_engine);
    {
        extern void ShutdownStubScenes(void);
        ShutdownStubScenes();
    }
    ShutdownAllArchives();

    DestroyWindow(hwnd);
    UnregisterClassA(DAYBREAK_WINDOW_CLASS, hInstance);

    return exit_code;
}
