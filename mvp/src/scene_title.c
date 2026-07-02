/**
 * scene_title.c — Title screen renderer
 *
 * Translated from RenderTitle (FUN_00403470).
 *
 * Original behavior:
 *   1. BeginScene
 *   2. SetRenderState(ALPHABLENDENABLE, FALSE)
 *   3. DrawMenuItem(x, y, font_col, char) × 9 — main menu items
 *   4. DrawMenuItem for settings indicators (sound volume, etc.)
 *   5. EndScene + Present
 *
 * The original uses a bitmap font system (sprite sheet of glyphs).
 * The 9 menu items are at positions:
 *   X=180.0 (0x43300000), Y=128,160,192,224,256,288,320,352,384 (32px spacing)
 *
 * For MVP+3 we:
 *   1. Load data/title/back00.bmp, data/title/logo.bmp, data/title/title.bmp
 *      from the original game's data/ folder (if present)
 *   2. If BMPs not available, generate synthetic placeholders
 *   3. Draw the title screen background + logo + title
 *   4. Draw menu items using D3DXFont (real text instead of bitmap glyphs)
 *      with the SAME positions as the original (X=180, Y=128+i*32)
 *   5. Handle menu navigation with Up/Down (matches original joystick Y)
 *   6. Handle selection with Enter (matches original confirm button)
 *
 * Original menu items (inferred from RenderTitle char indices 0,2,4,8,10,12,...):
 *   The indices 0-14 are bitmap font character codes, not text.
 *   Looking at the game's title screen flow (LoadNextScene case 0):
 *     - DAT_006cae9c == 1 → confirm button → transitions to scene based on selection
 *     - The selection at param_1+0x3d0 ranges 0-8 (9 items)
 *   The actual menu items shown in the original game (from game screenshots):
 *     0: Start (1P vs CPU)
 *     1: Network (multiplayer)
 *     2: Network (LAN)
 *     3: Survival
 *     4: Training
 *     5: Option
 *     6: (?)
 *     7: (?)
 *     8: (?)
 *   We use these inferred labels.
 */

#include "engine.h"
#include "scene_defs.h"
#include "d3d_utils.h"
#include "dat_archive.h"
#include <stdio.h>

/* External globals — these are state from the original game.
 * For MVP, we keep them as local statics. */
static int g_menu_selection = 0;  /* param_1+0x3d0 in original */

/* Menu items shown on title screen.
 * The original uses bitmap font character indices (0,2,4,8,10,12,10,12,14)
 * which we can't render without the bitmap font asset.
 * These text labels are inferred from the game's behavior:
 *   - Item 0 → SCENE_SELECT (Start Game)
 *   - Item 1 → SCENE_CONNECT (Network)
 *   - Item 3 → SCENE_BATTLE (Stage Select / Battle)
 * The rest are settings/options that don't transition in the original. */
static const char *const MENU_ITEMS[9] = {
    "1P vs CPU",          /* item 0 — start game */
    "Network Game",       /* item 1 — multiplayer (DirectPlay) */
    "Watch Mode",         /* item 2 */
    "Training",           /* item 3 */
    "Survival",           /* item 4 */
    "Option",             /* item 5 */
    "Key Config",         /* item 6 */
    "Sound Test",         /* item 7 */
    "Exit",               /* item 8 */
};

/* Title screen assets — loaded from data/title/ if available */
static IDirect3DTexture9 *g_bg_texture = NULL;     /* data/title/back00.bmp */
static IDirect3DTexture9 *g_logo_texture = NULL;   /* data/title/logo.bmp */
static IDirect3DTexture9 *g_title_texture = NULL;  /* data/title/title.bmp */
static ID3DXFont *g_font = NULL;
static ID3DXSprite *g_sprite = NULL;

/* ============================================================
 * InitTitleScene — load font + textures
 * ============================================================ */

bool InitTitleScene(EngineState *state)
{
    HRESULT hr;

    /* Create D3DX font for text rendering.
     * Original used bitmap font from a sprite sheet. */
    hr = D3DXCreateFontA(
        state->device,
        24, 0, FW_NORMAL, 0, FALSE,
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

    /* Try to load original game assets.
     * These are loaded via the DatResource system which handles:
     *   1. Direct file (data/title/back00.bmp)
     *   2. Archive lookup (daybreakXX.dat) — future */
    g_bg_texture = LoadTextureFromFile(state, "data/title/back00.bmp");
    g_logo_texture = LoadTextureFromFile(state, "data/title/logo.bmp");
    g_title_texture = LoadTextureFromFile(state, "data/title/title.bmp");

    /* If back00 not found, try Cdata/title/ (alternate path from strings) */
    if (!g_bg_texture) {
        g_bg_texture = LoadTextureFromFile(state, "Cdata/title/back00.bmp");
    }

    return true;
}

/* ============================================================
 * ShutdownTitleScene — release resources
 * ============================================================ */

void ShutdownTitleScene(void)
{
    ReleaseTexture(g_bg_texture);     g_bg_texture = NULL;
    ReleaseTexture(g_logo_texture);   g_logo_texture = NULL;
    ReleaseTexture(g_title_texture);  g_title_texture = NULL;

    if (g_sprite) {
        ID3DXSprite_Release(g_sprite);
        g_sprite = NULL;
    }
    if (g_font) {
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
 *
 * Original input mapping (from FASE11B_REPORT.md):
 *   DAT_006cae94 = joystick X (left/right)
 *   DAT_006cae98 = joystick Y (up/down) — used for menu navigation
 *   DAT_006cae9c = confirm button (1 = pressed)
 *   DAT_006caea0 = cancel button (1 = pressed)
 * ============================================================ */

int UpdateTitleScene(EngineState *state, const uint8_t keys[256])
{
    static bool prev_up = false, prev_down = false, prev_confirm = false, prev_cancel = false;

    /* Map keyboard to virtual joystick (matches original DirectInput semantics) */
    bool up    = (keys[DIK_UPARROW]    & 0x80) != 0;
    bool down  = (keys[DIK_DOWNARROW]  & 0x80) != 0;
    bool conf  = (keys[DIK_RETURN]     & 0x80) != 0 || (keys[DIK_Z] & 0x80) != 0;
    bool canc  = (keys[DIK_BACKSPACE]  & 0x80) != 0 || (keys[DIK_X] & 0x80) != 0;

    /* Navigate up (with edge detection — original checks DAT_006cae98 == -1) */
    if (up && !prev_up) {
        g_menu_selection = (g_menu_selection + 8) % 9;  /* 9 items, wrap around */
    }
    /* Navigate down (original checks DAT_006cae98 == 1) */
    if (down && !prev_down) {
        g_menu_selection = (g_menu_selection + 1) % 9;
    }

    /* Confirm — return scene ID based on selection (original checks DAT_006cae9c == 1) */
    int result = -1;
    if (conf && !prev_confirm) {
        switch (g_menu_selection) {
        case 0: result = SCENE_SELECT;     break;  /* 1P vs CPU */
        case 1: result = SCENE_CONNECT;    break;  /* Network */
        case 2: result = -1;               break;  /* Watch — not implemented */
        case 3: result = SCENE_BATTLE;     break;  /* Training */
        case 4: result = SCENE_BATTLE;     break;  /* Survival */
        case 5: result = -1;               break;  /* Option */
        case 6: result = -1;               break;  /* Key Config */
        case 7: result = -1;               break;  /* Sound Test */
        case 8: g_should_quit = true;      break;  /* Exit */
        }
    }

    /* Cancel — no-op on title (would go to splash/attract in original) */
    (void)canc;
    (void)prev_cancel;
    (void)state;

    prev_up = up;
    prev_down = down;
    prev_confirm = conf;
    prev_cancel = canc;

    return result;
}

/* ============================================================
 * RenderTitleScene — draw the title screen
 *
 * Translated from FUN_00403470 (RenderTitle).
 *
 * Layout (matches original positions):
 *   - Background: data/title/back00.bmp (full screen 800x600)
 *   - Logo: data/title/logo.bmp (top center)
 *   - Title: data/title/title.bmp (below logo)
 *   - Menu items: X=180, Y=128,160,...,384 (32px spacing)
 *   - Hint: bottom of screen
 * ============================================================ */

void RenderTitleScene(EngineState *state)
{
    if (!BeginScene(state)) {
        return;
    }

    /* 1. Clear screen — original uses back00.bmp; we use dark blue as fallback */
    ClearScreen(state, COLOR_ARGB(0xff, 0x10, 0x10, 0x30));

    /* 2. Draw background texture if available (covers full screen) */
    if (g_bg_texture && g_sprite) {
        ID3DXSprite_Begin(g_sprite, D3DXSPRITE_ALPHABLEND);
        D3DXVECTOR3 pos = {0.0f, 0.0f, 0.0f};
        ID3DXSprite_Draw(g_sprite, g_bg_texture, NULL, NULL, &pos,
                          COLOR_ARGB(0xff, 0xff, 0xff, 0xff));
        ID3DXSprite_End(g_sprite);
    }

    /* 3. Draw logo (top center) — original asset: data/title/logo.bmp */
    if (g_logo_texture && g_sprite) {
        ID3DXSprite_Begin(g_sprite, D3DXSPRITE_ALPHABLEND);
        uint32_t tex_w, tex_h;
        GetTextureSize(g_logo_texture, &tex_w, &tex_h);
        /* Center horizontally, position at top */
        D3DXVECTOR3 pos = {
            (float)((DAYBREAK_WINDOW_WIDTH - (int)tex_w) / 2),
            20.0f,
            0.0f
        };
        ID3DXSprite_Draw(g_sprite, g_logo_texture, NULL, NULL, &pos,
                          COLOR_ARGB(0xff, 0xff, 0xff, 0xff));
        ID3DXSprite_End(g_sprite);
    }

    /* 4. Draw title text (below logo) — original asset: data/title/title.bmp */
    if (g_title_texture && g_sprite) {
        ID3DXSprite_Begin(g_sprite, D3DXSPRITE_ALPHABLEND);
        uint32_t tex_w, tex_h;
        GetTextureSize(g_title_texture, &tex_w, &tex_h);
        D3DXVECTOR3 pos = {
            (float)((DAYBREAK_WINDOW_WIDTH - (int)tex_w) / 2),
            90.0f,
            0.0f
        };
        ID3DXSprite_Draw(g_sprite, g_title_texture, NULL, NULL, &pos,
                          COLOR_ARGB(0xff, 0xff, 0xff, 0xff));
        ID3DXSprite_End(g_sprite);
    }

    /* 5. Draw text fallback (if no logo/title textures loaded) */
    if (g_font && (!g_logo_texture || !g_title_texture)) {
        if (!g_logo_texture) {
            RECT title_rect = {0, 30, DAYBREAK_WINDOW_WIDTH, 80};
            g_font->lpVtbl->DrawTextA(g_font, NULL, "Higurashi Daybreak Kai",
                -1, &title_rect, DT_CENTER | DT_VCENTER,
                COLOR_ARGB(0xff, 0xff, 0xff, 0xff));
        }
        if (!g_title_texture) {
            RECT sub_rect = {0, 80, DAYBREAK_WINDOW_WIDTH, 110};
            g_font->lpVtbl->DrawTextA(g_font, NULL, "ver1.11",
                -1, &sub_rect, DT_CENTER | DT_VCENTER,
                COLOR_ARGB(0xff, 0xc0, 0xc0, 0xc0));
        }
    }

    /* 6. Draw menu items — ORIGINAL POSITIONS (X=180, Y=128+i*32) */
    if (g_font) {
        for (int i = 0; i < 9; i++) {
            RECT item_rect = {180, 128 + i * 32, DAYBREAK_WINDOW_WIDTH, 160 + i * 32};
            DWORD color = (i == g_menu_selection)
                ? COLOR_ARGB(0xff, 0xff, 0xff, 0x00)   /* yellow for selected */
                : COLOR_ARGB(0xff, 0xc0, 0xc0, 0xc0);  /* light gray for others */

            /* Draw selection indicator (arrow) for selected item */
            if (i == g_menu_selection) {
                RECT arrow_rect = {150, 128 + i * 32, 180, 160 + i * 32};
                g_font->lpVtbl->DrawTextA(g_font, NULL, ">",
                    -1, &arrow_rect, DT_LEFT | DT_VCENTER, color);
            }

            g_font->lpVtbl->DrawTextA(g_font, NULL, MENU_ITEMS[i],
                -1, &item_rect, DT_LEFT | DT_VCENTER, color);
        }

        /* 7. Draw hint text at bottom */
        RECT hint_rect = {0, DAYBREAK_WINDOW_HEIGHT - 50,
                          DAYBREAK_WINDOW_WIDTH, DAYBREAK_WINDOW_HEIGHT - 20};
        g_font->lpVtbl->DrawTextA(g_font, NULL,
            "Up/Down: Navigate   Z/Enter: Select   X: Back   ESC: Quit",
            -1, &hint_rect, DT_CENTER | DT_VCENTER,
            COLOR_ARGB(0xff, 0x80, 0x80, 0x80));
    }

    /* 8. End scene + present */
    EndSceneAndPresent(state);
}
