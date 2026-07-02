/**
 * scene_stubs.c — Render implementations for stub scenes
 *
 * These scenes are not yet fully ported from the original. Each shows
 * a colored background + scene name + instructions.
 *
 * The scenes implemented here:
 *   - Select (SCENE_SELECT = 1)  — character select
 *   - VS Load (SCENE_VS_LOAD = 2) — VS loading screen
 *   - Battle (SCENE_BATTLE = 3)   — battle scene (very stub)
 *   - Network (SCENE_CONNECT = 7) — DirectPlay replacement would go here
 *
 * Original mapping:
 *   - These correspond to cases 1, 2, 3 of LoadNextScene (FUN_00406310)
 *   - Case 7 is from NetworkMenuDispatcher (FUN_00412ac0)
 */

#include "engine.h"
#include "scene_defs.h"
#include "d3d_utils.h"
#include <stdio.h>

/* Shared font for all stub scenes */
static ID3DXFont *g_stub_font = NULL;

bool InitStubScenes(EngineState *state)
{
    if (g_stub_font) return true;  /* already initialized */

    HRESULT hr = D3DXCreateFontA(
        state->device,
        28, 0, FW_NORMAL, 0, FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE,
        "MS Gothic",
        &g_stub_font);

    return SUCCEEDED(hr);
}

void ShutdownStubScenes(void)
{
    if (g_stub_font) {
        IUnknown *unk = (IUnknown *)g_stub_font;
        unk->lpVtbl->Release(unk);
        g_stub_font = NULL;
    }
}

/* Common render helper for stub scenes */
static void RenderStubCommon(EngineState *state, const char *scene_name,
                              const char *description, D3DCOLOR bg_color)
{
    if (!BeginScene(state)) return;

    ClearScreen(state, bg_color);

    if (g_stub_font) {
        /* Scene name in white, large, centered top */
        RECT name_rect = {0, 80, DAYBREAK_WINDOW_WIDTH, 130};
        g_stub_font->lpVtbl->DrawTextA(g_stub_font, NULL, scene_name,
            -1, &name_rect, DT_CENTER | DT_VCENTER,
            COLOR_ARGB(0xff, 0xff, 0xff, 0xff));

        /* Description in light gray, centered middle */
        RECT desc_rect = {100, 220, DAYBREAK_WINDOW_WIDTH - 100, 320};
        g_stub_font->lpVtbl->DrawTextA(g_stub_font, NULL, description,
            -1, &desc_rect, DT_CENTER | DT_VCENTER | DT_WORDBREAK,
            COLOR_ARGB(0xff, 0xc0, 0xc0, 0xc0));

        /* Hint at bottom */
        RECT hint_rect = {0, DAYBREAK_WINDOW_HEIGHT - 60,
                          DAYBREAK_WINDOW_WIDTH, DAYBREAK_WINDOW_HEIGHT - 30};
        g_stub_font->lpVtbl->DrawTextA(g_stub_font, NULL,
            "Press X to return to title   |   ESC to quit",
            -1, &hint_rect, DT_CENTER | DT_VCENTER,
            COLOR_ARGB(0xff, 0x80, 0x80, 0x80));
    }

    EndSceneAndPresent(state);
}

/* ============================================================
 * Select scene (SCENE_SELECT = 1)
 * Original: case 1 of LoadNextScene — calls FUN_00406850 for both players
 * ============================================================ */

void RenderSelectScene(EngineState *state)
{
    RenderStubCommon(state,
        "Character Select (Stub)",
        "Original: case 1 of LoadNextScene\n"
        "Calls FUN_00406850(0) and FUN_00406850(1)\n"
        "for player 1 and player 2 cursor update.\n\n"
        "Not yet ported — needs bitmap font system.",
        COLOR_ARGB(0xff, 0x20, 0x30, 0x40));  /* dark blue-green */
}

/* ============================================================
 * VS Load scene (SCENE_VS_LOAD = 2)
 * Original: case 2 — uses critical section (FUN_0065d670/6a0)
 * ============================================================ */

void RenderVSScene(EngineState *state)
{
    RenderStubCommon(state,
        "VS Loading (Stub)",
        "Original: case 2 of LoadNextScene\n"
        "Uses EnterCriticalSection/LeaveCriticalSection\n"
        "while loading character data.\n\n"
        "Not yet ported — needs asset loading system.",
        COLOR_ARGB(0xff, 0x40, 0x20, 0x20));  /* dark red */
}

/* ============================================================
 * Battle scene (SCENE_BATTLE = 3, SCENE_BATTLE_RUN = 8)
 * Original: case 3 — sets up random character selection, returns 8
 * ============================================================ */

void RenderBattleScene(EngineState *state)
{
    RenderStubCommon(state,
        "Battle Scene (Stub)",
        "Original: case 3 of LoadNextScene + RenderBattle (FUN_004072b0)\n"
        "256 lines of decompiled code — the largest scene.\n"
        "Handles HUD, characters, projectiles, effects.\n\n"
        "Not yet ported — needs mesh loading + animation.",
        COLOR_ARGB(0xff, 0x40, 0x20, 0x40));  /* dark purple */
}

/* ============================================================
 * Network scene (SCENE_CONNECT = 7)
 * Original: from NetworkMenuDispatcher (FUN_00412ac0) case 7
 * ============================================================ */

void RenderNetworkScene(EngineState *state)
{
    RenderStubCommon(state,
        "Network Multiplayer (Stub)",
        "Original: NetworkMenuDispatcher case 7 (Connecting)\n"
        "DirectPlay 8 — deprecated since Windows 8.\n\n"
        "A modern port would replace DirectPlay with:\n"
        "  - Steamworks API\n"
        "  - Epic Online Services\n"
        "  - Custom UDP implementation\n\n"
        "See binary_data/network_analysis/FASE11_REPORT.md for full details.",
        COLOR_ARGB(0xff, 0x20, 0x40, 0x20));  /* dark green */
}
