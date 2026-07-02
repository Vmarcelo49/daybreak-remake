/**
 * scene_title.c — Title screen renderer
 *
 * Translated from RenderTitle (FUN_00403470).
 *
 * Original behavior:
 *   - BeginScene
 *   - SetRenderState(ALPHABLENDENABLE, FALSE)
 *   - For each menu item (0-8):
 *       DrawMenuItem(x=180.0, y=128+i*32, font_col=0, char=item_id)
 *   - DrawMenuItem for settings indicators
 *   - EndScene + Present
 *
 * For MVP+1 we don't port the bitmap font system (would require porting
 * DrawMenuItem at FUN_00655830 which is complex). Instead we use D3DXFont
 * to draw real text. This proves the rendering pipeline works end-to-end.
 *
 * Original positions preserved:
 *   X=180.0 (0x43300000), Y=128,160,192,...,384 (32px spacing)
 *   Settings column: X=368.0 (0x43b80000)
 *   Last column: X=460.0 (0x43e80000)
 */

#include "engine.h"
#include "scene_defs.h"
#include "d3d_utils.h"
#include <stdio.h>

/* External globals — these are state from the original game.
 * For MVP, we keep them as local statics. */
static int g_menu_selection = 0;  /* param_1+0x3d0 in original */

/* Menu items shown on title screen (9 items, matching original case 0 of LoadNextScene) */
static const char *const MENU_ITEMS[9] = {
    "Start Game",         /* item 0 */
    "Network Game",       /* item 1 — goes to NetworkMenuDispatcher */
    "Character Select",   /* item 2 */
    "Stage Select",       /* item 3 */
    "Settings",           /* item 4 */
    "Back",               /* item 5 */
    "Option 7",           /* item 6 */
    "Option 8",           /* item 7 */
    "Option 9",           /* item 8 */
};

static ID3DXFont *g_font = NULL;
static ID3DXSprite *g_sprite = NULL;
static IDirect3DTexture9 *g_bg_texture = NULL;

/* ============================================================
 * InitTitleScene — load font + background texture
 * ============================================================ */

bool InitTitleScene(EngineState *state)
{
    /* Create D3DX font for text rendering.
     * Original used bitmap font from a sprite sheet — we use Windows font. */
    HRESULT hr = D3DXCreateFontA(
        state->device,
        24,                          /* height */
        0,                           /* width (auto) */
        FW_NORMAL,                   /* weight */
        0,                           /* mip levels */
        FALSE,                       /* italic */
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE,
        "MS Gothic",
        &g_font);

    if (FAILED(hr)) {
        ShowError("Failed to create font", "Title Init");
        return false;
    }

    /* Create sprite object for batched drawing */
    hr = D3DXCreateSprite(state->device, &g_sprite);
    if (FAILED(hr)) {
        ShowError("Failed to create sprite", "Title Init");
        return false;
    }

    /* Try to load background texture if available */
    hr = D3DXCreateTextureFromFileA(state->device,
                                     "data/title/back00.bmp",
                                     &g_bg_texture);
    if (FAILED(hr)) {
        /* Non-fatal — we'll just clear to a color */
        g_bg_texture = NULL;
    }

    return true;
}

/* ============================================================
 * ShutdownTitleScene — release resources
 * ============================================================ */

void ShutdownTitleScene(void)
{
    if (g_bg_texture) {
        IDirect3DTexture9_Release(g_bg_texture);
        g_bg_texture = NULL;
    }
    if (g_sprite) {
        ID3DXSprite_Release(g_sprite);
        g_sprite = NULL;
    }
    if (g_font) {
        /* ID3DXFont extends IUnknown */
        IUnknown *unk = (IUnknown *)g_font;
        unk->lpVtbl->Release(unk);
        g_font = NULL;
    }
}

/* ============================================================
 * UpdateTitleScene — handle input for menu navigation
 *
 * Returns: scene ID to transition to, or -1 to stay on title.
 * Original case 0 of LoadNextScene handles this.
 * ============================================================ */

int UpdateTitleScene(EngineState *state, const uint8_t keys[256])
{
    /* Original input globals (from FASE11B_REPORT.md):
     *   0x006cae94: joystick X (left/right)
     *   0x006cae98: joystick Y (up/down)
     *   0x006cae9c: confirm button
     *   0x006caea0: cancel button
     *
     * For MVP, we map DirectInput keyboard directly. */

    static bool prev_up = false, prev_down = false, prev_confirm = false, prev_cancel = false;

    bool up    = (keys[DIK_UPARROW]    & 0x80) != 0;
    bool down  = (keys[DIK_DOWNARROW]  & 0x80) != 0;
    bool conf  = (keys[DIK_RETURN]     & 0x80) != 0 || (keys[DIK_Z] & 0x80) != 0;
    bool canc  = (keys[DIK_BACKSPACE]  & 0x80) != 0 || (keys[DIK_X] & 0x80) != 0;

    /* Navigate up (with edge detection) */
    if (up && !prev_up) {
        g_menu_selection = (g_menu_selection + 8) % 9;  /* 9 items, wrap around */
    }
    /* Navigate down */
    if (down && !prev_down) {
        g_menu_selection = (g_menu_selection + 1) % 9;
    }

    /* Confirm — return scene ID based on selection */
    int result = -1;
    if (conf && !prev_confirm) {
        switch (g_menu_selection) {
        case 0: result = SCENE_SELECT;     break;  /* Start Game */
        case 1: result = SCENE_CONNECT;    break;  /* Network (stub) */
        case 2: result = SCENE_SELECT;     break;
        case 3: result = SCENE_BATTLE;     break;
        default: result = -1;              break;  /* Stay */
        }
    }

    /* Cancel — go back (no-op on title screen) */
    (void)canc;
    (void)prev_cancel;

    prev_up = up;
    prev_down = down;
    prev_confirm = conf;
    prev_cancel = canc;

    (void)state;
    return result;
}

/* ============================================================
 * RenderTitleScene — draw the title screen
 *
 * Translated from FUN_00403470 (RenderTitle).
 * Original positions:
 *   X=180.0 (0x43300000) — main menu column
 *   Y=128,160,192,224,256,288,320,352,384 (32px spacing for 9 items)
 *   Settings column: X=368.0 (0x43b80000)
 * ============================================================ */

void RenderTitleScene(EngineState *state)
{
    if (!BeginScene(state)) {
        return;
    }

    /* 1. Clear screen to dark blue background */
    ClearScreen(state, COLOR_ARGB(0xff, 0x10, 0x10, 0x30));

    /* 2. Draw background texture if available (covers full screen) */
    if (g_bg_texture && g_sprite) {
        ID3DXSprite_Begin(g_sprite, D3DXSPRITE_ALPHABLEND);
        D3DXVECTOR3 pos = {0.0f, 0.0f, 0.0f};
        ID3DXSprite_Draw(g_sprite, g_bg_texture, NULL, NULL, &pos,
                          COLOR_ARGB(0xff, 0xff, 0xff, 0xff));
        ID3DXSprite_End(g_sprite);
    }

    /* 3. Draw title text at top */
    if (g_font) {
        RECT title_rect = {0, 30, DAYBREAK_WINDOW_WIDTH, 90};
        g_font->lpVtbl->DrawTextA(g_font, NULL, "Higurashi Daybreak",
            -1, &title_rect, DT_CENTER | DT_VCENTER,
            COLOR_ARGB(0xff, 0xff, 0xff, 0xff));

        /* 4. Draw menu items — original positions X=180, Y=128+i*32 */
        for (int i = 0; i < 9; i++) {
            RECT item_rect = {180, 128 + i * 32, DAYBREAK_WINDOW_WIDTH, 160 + i * 32};
            DWORD color = (i == g_menu_selection)
                ? COLOR_ARGB(0xff, 0xff, 0xff, 0x00)   /* yellow for selected */
                : COLOR_ARGB(0xff, 0xc0, 0xc0, 0xc0);  /* light gray for others */
            g_font->lpVtbl->DrawTextA(g_font, NULL, MENU_ITEMS[i],
                -1, &item_rect, DT_LEFT | DT_VCENTER, color);
        }

        /* 5. Draw hint text at bottom */
        RECT hint_rect = {0, DAYBREAK_WINDOW_HEIGHT - 50,
                          DAYBREAK_WINDOW_WIDTH, DAYBREAK_WINDOW_HEIGHT - 20};
        g_font->lpVtbl->DrawTextA(g_font, NULL,
            "Up/Down: Navigate   Enter: Select   ESC: Quit",
            -1, &hint_rect, DT_CENTER | DT_VCENTER,
            COLOR_ARGB(0xff, 0x80, 0x80, 0x80));
    }

    /* 6. End scene + present */
    EndSceneAndPresent(state);
}
