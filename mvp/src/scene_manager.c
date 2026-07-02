/**
 * scene_manager.c — Scene state machine dispatcher
 *
 * Translated from LoadNextScene (FUN_00406310).
 *
 * Original behavior:
 *   - Increments frame counter at pGameState+0x2e14
 *   - Calls UpdateInput, UpdateInputState, IsKeyPressed (for pause toggle)
 *   - Switch on pGameState+0x2e18 (current_scene_id):
 *     case 0: Title screen — handles menu navigation, transitions to scene 1
 *     case 1: Select — calls FUN_00406850 for both players
 *     case 2: VS loading — uses critical section
 *     case 3: Battle init — sets up random character selection
 *   - Returns: 5 (continue) or 8 (transition to battle scene)
 *
 * For MVP+2 we implement a simplified version:
 *   - State machine using SceneId enum from scene_defs.h
 *   - Each scene has its own Init/Update/Render functions
 *   - LoadNextScene dispatches based on current_scene
 */

#include "engine.h"
#include "scene_defs.h"
#include "d3d_utils.h"
#include <stdio.h>

/* Global game state (simplified from original GameState struct) */
typedef struct GameState {
    int frame_counter;       /* +0x2e14 */
    int current_scene_id;    /* +0x2e18 */
    int sub_scene_id;        /* +0x2e20 */
    int selected_character;  /* per-player would be at +0x2e28-0x2ea8 */
    int selected_stage;      /* would be at DAT_006cfdc5 */
} GameState;

static GameState g_game_state = {0};

/* ============================================================
 * Scene function pointers
 * ============================================================ */

typedef struct Scene {
    bool  (*init)(EngineState *state);
    void  (*shutdown)(void);
    int   (*update)(EngineState *state, const uint8_t keys[256]);
    void  (*render)(EngineState *state);
} Scene;

/* Forward declarations — implemented in scene_*.c files */
extern bool  InitTitleScene(EngineState *state);
extern void  ShutdownTitleScene(void);
extern int   UpdateTitleScene(EngineState *state, const uint8_t keys[256]);
extern void  RenderTitleScene(EngineState *state);

/* Stub scenes for unimplemented ones */
static bool  StubInit(EngineState *state) { (void)state; return true; }
static void  StubShutdown(void) {}
static int   StubUpdate(EngineState *state, const uint8_t keys[256]) {
    (void)state;
    /* ESC handled in main loop; X goes back to title */
    if (keys[DIK_X] & 0x80) return SCENE_TITLE;
    return -1;
}
static void  StubRender(EngineState *state, const char *scene_name) {
    if (!BeginScene(state)) return;
    ClearScreen(state, COLOR_ARGB(0xff, 0x20, 0x20, 0x20));
    /* Text rendering would go here */
    EndSceneAndPresent(state);
    (void)scene_name;
}

/* Select scene stub */
static int SelectUpdate(EngineState *state, const uint8_t keys[256]) {
    (void)state;
    static bool prev_x = false;
    bool x = (keys[DIK_X] & 0x80) != 0;
    if (x && !prev_x) return SCENE_TITLE;
    prev_x = x;
    return -1;
}
static void SelectRender(EngineState *state) {
    StubRender(state, "Select");
}

/* VS scene stub */
static int VSUpdate(EngineState *state, const uint8_t keys[256]) {
    (void)state;
    return -1;
}
static void VSRender(EngineState *state) {
    StubRender(state, "VS Loading");
}

/* Battle scene stub */
static int BattleUpdate(EngineState *state, const uint8_t keys[256]) {
    (void)state;
    static bool prev_x = false;
    bool x = (keys[DIK_X] & 0x80) != 0;
    if (x && !prev_x) return SCENE_TITLE;
    prev_x = x;
    return -1;
}
static void BattleRender(EngineState *state) {
    StubRender(state, "Battle");
}

/* Network scene stub */
static int NetworkUpdate(EngineState *state, const uint8_t keys[256]) {
    (void)state;
    static bool prev_x = false;
    bool x = (keys[DIK_X] & 0x80) != 0;
    if (x && !prev_x) return SCENE_TITLE;
    prev_x = x;
    return -1;
}
static void NetworkRender(EngineState *state) {
    StubRender(state, "Network (stub — DirectPlay not ported)");
}

/* Scene table — indexed by SceneId */
static Scene g_scenes[] = {
    /* SCENE_TITLE (0) */
    { InitTitleScene, ShutdownTitleScene, UpdateTitleScene, RenderTitleScene },
    /* SCENE_SELECT (1) */
    { StubInit, StubShutdown, SelectUpdate, SelectRender },
    /* SCENE_VS_LOAD (2) */
    { StubInit, StubShutdown, VSUpdate, VSRender },
    /* SCENE_BATTLE (3) */
    { StubInit, StubShutdown, BattleUpdate, BattleRender },
    /* placeholder 4-6 */
    { StubInit, StubShutdown, StubUpdate, NULL },
    { StubInit, StubShutdown, StubUpdate, NULL },
    { StubInit, StubShutdown, StubUpdate, NULL },
    /* SCENE_CONNECT (7) */
    { StubInit, StubShutdown, NetworkUpdate, NetworkRender },
    /* SCENE_BATTLE_RUN (8) */
    { StubInit, StubShutdown, BattleUpdate, BattleRender },
};

#define NUM_SCENES (sizeof(g_scenes) / sizeof(g_scenes[0]))

/* ============================================================
 * SceneManager — public API
 * ============================================================ */

static Scene *g_current_scene = NULL;
static int g_current_scene_id = -1;
static bool g_scene_initialized = false;

void SceneManager_Init(void)
{
    g_game_state.frame_counter = 0;
    g_game_state.current_scene_id = SCENE_TITLE;
    g_game_state.sub_scene_id = 0;
    g_game_state.selected_character = 0;
    g_game_state.selected_stage = 1;  /* stage 1 by default */
    g_current_scene = NULL;
    g_current_scene_id = -1;
    g_scene_initialized = false;
}

void SceneManager_Shutdown(EngineState *state)
{
    (void)state;
    if (g_scene_initialized && g_current_scene && g_current_scene->shutdown) {
        g_current_scene->shutdown();
    }
    g_scene_initialized = false;
    g_current_scene = NULL;
}

/**
 * LoadNextScene — translated from FUN_00406310
 * Returns: true if scene changed, false otherwise.
 *
 * Original increments frame_counter then dispatches on current_scene_id.
 * For MVP, we just track frame counter and transition when scene changes.
 */
bool LoadNextScene(EngineState *state, int new_scene_id)
{
    g_game_state.frame_counter++;

    if (new_scene_id < 0 || new_scene_id >= (int)NUM_SCENES) {
        return false;  /* invalid scene */
    }

    if (new_scene_id == g_current_scene_id) {
        return false;  /* no change */
    }

    /* Shutdown current scene */
    if (g_scene_initialized && g_current_scene && g_current_scene->shutdown) {
        g_current_scene->shutdown();
    }
    g_scene_initialized = false;

    /* Switch to new scene */
    g_current_scene_id = new_scene_id;
    g_game_state.current_scene_id = new_scene_id;
    g_current_scene = &g_scenes[new_scene_id];

    /* Init new scene */
    if (g_current_scene->init) {
        if (!g_current_scene->init(state)) {
            /* Init failed — fall back to title */
            if (new_scene_id != SCENE_TITLE) {
                return LoadNextScene(state, SCENE_TITLE);
            }
        }
    }
    g_scene_initialized = true;

    return true;
}

/**
 * SceneManager_Update — call current scene's update function.
 * Returns next scene ID if scene wants to transition, or -1 to stay.
 */
int SceneManager_Update(EngineState *state, const uint8_t keys[256])
{
    if (!g_scene_initialized || !g_current_scene || !g_current_scene->update) {
        return -1;
    }
    return g_current_scene->update(state, keys);
}

/**
 * SceneManager_Render — call current scene's render function.
 */
void SceneManager_Render(EngineState *state)
{
    if (!g_scene_initialized || !g_current_scene) {
        /* Fallback: clear screen */
        if (BeginScene(state)) {
            ClearScreen(state, COLOR_BLACK);
            EndSceneAndPresent(state);
        }
        return;
    }

    if (g_current_scene->render) {
        g_current_scene->render(state);
    } else {
        /* Scene has no render — show stub */
        if (BeginScene(state)) {
            ClearScreen(state, COLOR_ARGB(0xff, 0x20, 0x20, 0x20));
            EndSceneAndPresent(state);
        }
    }
}

int SceneManager_GetCurrentScene(void)
{
    return g_current_scene_id;
}
