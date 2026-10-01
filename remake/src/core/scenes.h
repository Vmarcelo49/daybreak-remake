// =============================================================================
//  scenes.h — concrete scene implementations.
//
//  Scene flow (mirrors the original game):
//    Bootstrap → Opening (op.mpg) → Title (menu)
//      → VS Mode → ModeSelect → CharacterSelect → Gameplay → Title
//      → Config (stub)
//      → Key Config (stub)
//      → Exit
//
//  Original scene IDs (LoadNextScene, FUN_00406310 — from mvp/scene_defs.h):
//    TITLE=0, SELECT=1, VS_LOAD=2, BATTLE=3, CONNECT=7, BATTLE_RUN=8.
//  Our classes cover a different (remake-specific) flow, but new scenes
//  that map 1:1 to original states should reuse these numbers in comments.
//  Related original offsets: GameState frame_counter +0x2e14,
//  current_scene +0x2e18, sub_scene +0x2e20; input globals joystick X/Y
//  0x006cae94/98, confirm 0x006cae9c, cancel 0x006caea0.
//
//  Stub-scene conventions (from mvp/scene_manager.c): a VS-style loading
//  scene auto-advances after ~180 frames; any stub returns to Title on
//  cancel (AttackB / X).
// =============================================================================
#pragma once

#include <memory>
#include <string>

#include "core/scene.h"
#include "render/arena_camera.h"
#include "render/ui_image.h"
#include "render/video_player.h"
#include "gameplay/fighter.h"

namespace daybreak {

class Scene_Bootstrap : public Scene {
public:
    const char* name() const override { return "Bootstrap"; }
    void on_enter(SceneContext& ctx) override;
    UpdateResult update(SceneContext& ctx, double dt) override;
    void render(SceneContext& ctx) override;
private:
    double m_elapsed = 0.0;
    bool   m_done = false;
};

class Scene_Opening : public Scene {
public:
    const char* name() const override { return "Opening"; }
    void on_enter(SceneContext& ctx) override;
    void on_exit(SceneContext& ctx) override;
    UpdateResult update(SceneContext& ctx, double dt) override;
    void render(SceneContext& ctx) override;
private:
    render::VideoPlayer m_video;
    bool                m_videoStarted = false;
    bool                m_skipRequested = false;
};

class Scene_Title : public Scene {
public:
    const char* name() const override { return "Title"; }
    void on_enter(SceneContext& ctx) override;
    void on_exit(SceneContext& ctx) override;
    UpdateResult update(SceneContext& ctx, double dt) override;
    void render(SceneContext& ctx) override;
private:
    render::UIImage m_background;
    bool            m_bgLoaded = false;
    int             m_selected = 0;
    double          m_elapsed = 0.0;

    // Menu items (mirrors the original game's title screen).
    static constexpr int kMenuItemCount = 4;
    const char* m_items[kMenuItemCount] = {
        "VS Mode", "Config", "Key Config", "Exit"
    };

    // Menu layout geometry from RenderTitle (FUN_00403470): 9 items at
    // X=180, Y=128+i*32.  Our menu is shorter, but text rendering (see
    // the TODO in scenes.cpp) must use this origin/stride so the layout
    // matches the original, and item targets follow its mapping
    // (0→Select, 1→Connect, 3/4→Battle, 8→quit; 2/5/6/7 no-op).
    // mvp's English labels are guesses from screenshots — the original
    // used a bitmap-font glyph sheet.
    static constexpr int kMenuX  = 180;
    static constexpr int kMenuY0 = 128;
    static constexpr int kMenuDY = 32;
};

class Scene_ModeSelect : public Scene {
public:
    const char* name() const override { return "ModeSelect"; }
    void on_enter(SceneContext& ctx) override;
    void on_exit(SceneContext& ctx) override;
    UpdateResult update(SceneContext& ctx, double dt) override;
    void render(SceneContext& ctx) override;
private:
    render::UIImage m_background;
    bool            m_bgLoaded = false;
    int             m_selected = 0;
    double          m_elapsed = 0.0;

    static constexpr int kModeCount = 3;
    const char* m_modes[kModeCount] = {
        "1P vs CPU", "2P vs CPU", "2v2 Team Battle"
    };
};

class Scene_CharacterSelect : public Scene {
public:
    const char* name() const override { return "CharacterSelect"; }
    void on_enter(SceneContext& ctx) override;
    void on_exit(SceneContext& ctx) override;
    UpdateResult update(SceneContext& ctx, double dt) override;
    void render(SceneContext& ctx) override;
private:
    render::UIImage m_background;
    render::UIImage m_portraits[4];  // p00-p03 portraits
    bool            m_bgLoaded = false;
    int             m_selected = 0;  // 0-3 (character index)
    double          m_elapsed = 0.0;

    // Character names (matching the .DAT paths).
    static constexpr int kCharCount = 4;
    const char* m_charNames[kCharCount] = {
        "rika", "takano", "akane", "rena"
    };
    const char* m_charModels[kCharCount] = {
        "data/rika/01.X", "data/takano/00.X",
        "data/akane/00.X", "data/rena/01.X"
    };
    const char* m_portraitAssets[kCharCount] = {
        "data/select/p00.cnv", "data/select/p01.cnv",
        "data/select/p02.cnv", "data/select/p03.cnv"
    };
};

class Scene_Gameplay : public Scene {
public:
    const char* name() const override { return "Gameplay"; }
    void on_enter(SceneContext& ctx) override;
    void on_exit(SceneContext& ctx) override;
    UpdateResult update(SceneContext& ctx, double dt) override;
    void render(SceneContext& ctx) override;

    // Set by CharacterSelect before transitioning.
    int m_p1CharIndex = 0;
    int m_p2CharIndex = 1;

private:
    gameplay::Fighter       m_fighters[2];
    XModel*                 m_models[2] = {};
    XModel*                 m_stageModels[7] = {};  // 00.X through 06.X
    int                     m_stageModelCount = 0;
    ArenaCamera             m_camera;
    CameraTarget            m_targets[2];
    double                  m_elapsed = 0.0;

    // Animation debug mode (F2 to toggle).
    // When active, Left/Right cycles through all AnimationSets on P1's model.
    // The fighter's state machine is bypassed — the selected animation plays directly.
    bool                    m_animDebug = false;
    int                     m_animIndex = 0;
};

} // namespace daybreak
