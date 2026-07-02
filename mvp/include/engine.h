/**
 * engine.h — Public types and function declarations for daybreak_mvp
 *
 * Translated from DaybreakDX.exe decompilation:
 *   - EngineInit (FUN_00657910)
 *   - EngineState struct (inferred from offsets in EngineInit)
 *
 * See: binary_data/render_pipeline/FASE_D3D_REPORT.md
 */
#ifndef DAYBREAK_ENGINE_H
#define DAYBREAK_ENGINE_H

#include <stdint.h>
#include <stdbool.h>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

/* ============================================================
 * Constants (from original binary)
 * ============================================================ */

#define DAYBREAK_WINDOW_CLASS    "HigurashiDaybreak"
#define DAYBREAK_WINDOW_TITLE    "Higurashi Daybreak (MVP port)"
#define DAYBREAK_WINDOW_WIDTH    800
#define DAYBREAK_WINDOW_HEIGHT   600

/* D3D constants used in original (see FASE_D3D_REPORT.md) */
#define D3D_SDK_VERSION_9        0x20  /* matches Direct3DCreate9(0x20) */

#define CREATEFLAGS_HARDWARE     0x44  /* D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED */
#define CREATEFLAGS_SOFTWARE     0x24  /* D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED */
#define CREATEFLAGS_REF          0x22  /* D3DCREATE_SOFTWARE_VERTEXPROCESSING (REF device) */

#define NUM_SHADERS              10    /* D3DXCreateEffect count in FUN_0064ff80 */

/* ============================================================
 * Types
 * ============================================================ */

/**
 * EngineState — partial reconstruction of the state struct used by EngineInit.
 * Original offsets in comments (from FASE_D3D_REPORT.md).
 *
 * Not all fields are known — MVP only uses what's needed to render a clear screen.
 */
typedef struct EngineState {
    HWND                 hwnd;            /* +0x00 */
    HINSTANCE            hinstance;       /* +0x04 */
    IDirect3D9          *d3d9;            /* +0x1c */
    IDirect3DDevice9    *device;          /* +0x20 */
    D3DPRESENT_PARAMETERS d3dpp;          /* +0x24 (size 0x38) */
    D3DCAPS9             caps;            /* +0x5c */
    DWORD                adapter_format;  /* +0x68 */
    bool                 windowed;        /* +0x17 (in EngineState, derived from param_2+5) */
    bool                 device_lost;     /* +0x59 (set by EndSceneAndPresent on D3DERR_DEVICELOST) */

    /* Input */
    LPDIRECTINPUT8       dinput;          /* +0x02 of InputState */
    LPDIRECTINPUTDEVICE8 keyboard;        /* +0x03 of InputState */

    /* Shaders (10 effects) */
    ID3DXEffect         *effects[NUM_SHADERS];

    /* Timing */
    DWORD                start_time;      /* +0x04 */
    DWORD                last_frame_time;
} EngineState;

/* ============================================================
 * Function declarations
 * ============================================================ */

/* main.c */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern bool g_should_quit;  /* set by WM_KEYDOWN VK_ESCAPE in main.c */

/* engine_init.c */
bool EngineInit(EngineState *state, HWND hwnd, HINSTANCE hinstance,
                int width, int height, bool windowed);

/* d3d_init.c */
bool InitD3D(EngineState *state, HWND hwnd, int width, int height, bool windowed);

/* shader_load.c */
bool CreateAllShaders(EngineState *state);
void DestroyAllShaders(EngineState *state);

/* input_init.c */
bool InitDirectInput(EngineState *state, HINSTANCE hinstance);
bool InitKeyboard(EngineState *state);
void ReadKeyboardState(EngineState *state, uint8_t keys[256]);
void ShutdownInput(EngineState *state);

/* render_loop.c */
bool BeginScene(EngineState *state);
void EndSceneAndPresent(EngineState *state);
void ClearScreen(EngineState *state, D3DCOLOR color);
int  RunMainLoop(EngineState *state);

/* scene_title.c — MVP+1 first real scene */
bool InitTitleScene(EngineState *state);
void ShutdownTitleScene(void);
int  UpdateTitleScene(EngineState *state, const uint8_t keys[256]);
void RenderTitleScene(EngineState *state);

/* ============================================================
 * Error reporting (used by all modules)
 * ============================================================ */

void ShowError(const char *message, const char *title);

#endif /* DAYBREAK_ENGINE_H */
