/**
 * scene_defs.h — Scene IDs and game state constants
 *
 * From LoadNextScene (FUN_00406310) switch case analysis.
 * See: binary_data/scene_table/FASE9_REPORT.md
 */
#ifndef DAYBREAK_SCENE_DEFS_H
#define DAYBREAK_SCENE_DEFS_H

/* Scene IDs — values from LoadNextScene switch case */
typedef enum {
    SCENE_TITLE   = 0,   /* case 0: title screen + main menu */
    SCENE_SELECT  = 1,   /* case 1: character select */
    SCENE_VS_LOAD = 2,   /* case 2: VS loading screen */
    SCENE_BATTLE  = 3,   /* case 3: battle init (transitions to scene 8) */
    SCENE_CONNECT = 7,   /* case 7: network connecting (from NetworkMenuDispatcher) */
    SCENE_BATTLE_RUN = 8,/* returned from case 3 after battle setup */
} SceneId;

/* GameState offsets (from FASE9_REPORT.md) */
#define GAMESTATE_FRAME_COUNTER_OFFSET    0x2e14
#define GAMESTATE_CURRENT_SCENE_OFFSET    0x2e18
#define GAMESTATE_SUB_SCENE_OFFSET        0x2e20
#define GAMESTATE_PLAYER_STATES_OFFSET    0x2e28
#define GAMESTATE_SCENE_SPECIFIC_OFFSET   0x2ebc

/* Input globals (from FASE11B_REPORT.md) */
#define INPUT_JOYSTICK_X_OFFSET           0x006cae94
#define INPUT_JOYSTICK_Y_OFFSET           0x006cae98
#define INPUT_CONFIRM_BUTTON_OFFSET       0x006cae9c
#define INPUT_CANCEL_BUTTON_OFFSET        0x006caea0

/* Network state globals (from FASE11B_REPORT.md) */
#define NET_MODE_FLAG                     0x006cfdb0
#define NET_CHAR_SELECTION_SLOTS          0x006cfdb8
#define NET_ACTIVE_SLOTS_BITMASK          0x006cfdc0
#define NET_IP_ADDRESS_OFFSET             0x006cfdc1
#define NET_STAGE_SELECTED                0x006cfdc5
#define NET_PORT_OFFSET                   0x006cfdc6

#endif /* DAYBREAK_SCENE_DEFS_H */
