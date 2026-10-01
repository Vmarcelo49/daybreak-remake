// =============================================================================
//  scenes.h — concrete scene implementations.
//
//  Scene flow (from captures — docs/reference/README.md, full loop):
//    Bootstrap → Opening (op.mpg) → Title (menu)
//      → TeamSelect → CharacterSelect → Weapon/Costume → Hypermode
//      → Controller (per slot) → Ready → Stage/Settings → VS sting
//      → Gameplay → Result (sting → quote → report) → back to TeamSelect
//      → Config (stub), Key Config (stub), Exit
//  NOTE: Scene_ModeSelect below is UNVERIFIED against the original —
//  captures go Title → TeamSelect directly. Keep it until versus entry
//  is re-checked; it may need merging into the Title→Team transition.
//
//  Original scene IDs (LoadNextScene, FUN_00406310 — via retired mvp):
//    TITLE=0, SELECT=1, VS_LOAD=2, BATTLE=3, CONNECT=7, BATTLE_RUN=8.
//  Our classes cover a different (remake-specific) flow, but new scenes
//  that map 1:1 to original states should reuse these numbers in comments.
//  Related original offsets: GameState frame_counter +0x2e14,
//  current_scene +0x2e18, sub_scene +0x2e20; input globals joystick X/Y
//  0x006cae94/98, confirm 0x006cae9c, cancel 0x006caea0.
//
//  Stub-scene conventions (from retired mvp's LoadNextScene port):
//  a VS-style loading scene auto-advances after ~180 frames; any stub
//  returns to Title on cancel.
// =============================================================================
#pragma once

#include <memory>
#include <string>

#include "core/scene.h"
#include "render/arena_camera.h"
#include "render/hud.h"
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

    // Menu items (remake-specific short menu; the original has 6 JP items:
    // Story/Versus/Netplay/Option/Controller/Exit — see
    // docs/reference/title-menu.webp).
    static constexpr int kMenuItemCount = 4;
    const char* m_items[kMenuItemCount] = {
        "VS Mode", "Config", "Key Config", "Exit"
    };

    // Menu layout geometry (UNVERIFIED — do not trust blindly): retired
    // mvp inferred 9 items at X=180, Y=128+i*32 from RenderTitle, but the
    // captured title screen shows 6 items at different positions
    // (items start y≈280, ~45px stride — see title-menu.webp). Re-measure
    // from the capture before text rendering lands (TODO in scenes.cpp).
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
    // Visual-validation override (-spawn x,y,z): P1 starts here instead of
    // the env.dat spawn, so the suite can explore per-stage viewpoints.
    bool m_useCustomSpawn = false;
    D3DXVECTOR3 m_customSpawn{};

private:
    gameplay::Fighter       m_fighters[2];
    XModel*                 m_models[2] = {};
    XModel*                 m_stageModels[7] = {};  // 00.X through 06.X
    int                     m_stageModelCount = 0;
    ArenaCamera             m_camera;
    CameraTarget            m_targets[2];
    double                  m_elapsed = 0.0;

    // Balloon economy (spec §3.5): per-side balloon %, LIMIT, KO clock.
    // Side i's balloon inflates when fighter i is KO'd; side loses past LIMIT.
    float                   m_balloon[2] = {0.0f, 0.0f};
    float                   m_limit = 100.0f;
    double                  m_koAt[2] = {-1.0, -1.0};  // -1 = alive
    D3DXVECTOR3             m_spawnPos[2] = {};
    float                   m_spawnFacing[2] = {0.0f, 0.0f};

    // Shots (spec §3.1): shared pool + the stage's projectile-only mesh.
    // collision_tama.x is optional — open stages fly shots to expiry.
    gameplay::ProjectilePool m_shots;
    XModel*                 m_tamaCollision = nullptr;

    // HUD + KO sting (ASCII "KO!" until JP text lands).
    render::Hud             m_hud;
    bool                    m_hudReady = false;
    double                  m_stingUntil = -1.0;

    // Animation debug mode (F2 to toggle).
    // When active, Left/Right cycles through all AnimationSets on P1's model.
    // The fighter's state machine is bypassed — the selected animation plays directly.
    bool                    m_animDebug = false;
    int                     m_animIndex = 0;
};

} // namespace daybreak
