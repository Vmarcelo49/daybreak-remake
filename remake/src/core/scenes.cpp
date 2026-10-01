// =============================================================================
//  scenes.cpp — concrete scene implementations with CNV menu backgrounds.
// =============================================================================
#include "scenes.h"

#include <cstdio>
#include <cstring>
#include <fstream>

#include <SDL.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>

#include "assets/asset_manager.h"
#include "audio/audio_engine.h"
#include "file_parser/x_model_loader.h"
#include "input/input_manager.h"
#include "gameplay/fighter.h"

namespace daybreak {

static std::string extract_to_temp(assets::AssetManager* am, const char* asset_name,
                                    const char* suffix) {
    if (!am) return {};
    std::vector<uint8_t> bytes;
    if (!am->read_file(asset_name, bytes)) return {};
    char tempDir[MAX_PATH];
    GetTempPathA(MAX_PATH, tempDir);
    static int counter = 0;
    char path[MAX_PATH];
    std::snprintf(path, sizeof(path), "%sdaybreak_%06d%s", tempDir, counter++, suffix);
    std::ofstream f(path, std::ios::binary);
    if (!f.is_open()) return {};
    f.write(reinterpret_cast<const char*>(bytes.data()),
            static_cast<std::streamsize>(bytes.size()));
    return std::string(path);
}

static bool poll_and_check_quit(input::InputManager* input) {
    if (input) input->poll();
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) return true;
    }
    return false;
}

// Helper: navigate a menu list. Returns true if selection changed.
static bool menu_navigate(const input::PlayerInput& p1, int& selected, int count) {
    bool changed = false;
    if (p1.just_pressed[input::Action::Up]) {
        selected = (selected - 1 + count) % count;
        changed = true;
    }
    if (p1.just_pressed[input::Action::Down]) {
        selected = (selected + 1) % count;
        changed = true;
    }
    return changed;
}

// Helper: check if P1 confirmed.
// Captures show Z (= Jump) confirming in menus (team select, result
// advance). Title-screen key still unverified (menus were undrivable
// under Wine), so Guard stays as a fallback for now.
static bool menu_confirmed(const input::PlayerInput& p1) {
    return p1.just_pressed[input::Action::Jump] ||
           p1.just_pressed[input::Action::Guard];
}

// Helper: check if P1 cancelled.
// Captures show X (= AttackA/melee) cancelling on filled select slots
// (deselects back to character pick). Title-screen key unverified.
static bool menu_cancelled(const input::PlayerInput& p1) {
    return p1.just_pressed[input::Action::AttackA];
}

// ============================================================================
// Scene_Bootstrap
// ============================================================================
void Scene_Bootstrap::on_enter(SceneContext& ctx) {
    std::printf("[daybreak] Bootstrap: initializing...\n");
    m_elapsed = 0.0;
    m_done = false;
    if (ctx.audio) ctx.audio->init();
}

UpdateResult Scene_Bootstrap::update(SceneContext& ctx, double dt) {
    m_elapsed += dt;
    if (m_elapsed >= 0.5 && !m_done) {
        m_done = true;
        set_next(std::make_unique<Scene_Opening>());
        return UpdateResult::Transition;
    }
    return UpdateResult::Continue;
}

void Scene_Bootstrap::render(SceneContext& ctx) {
    if (!ctx.device) return;
    ctx.device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(10, 10, 40), 1.0f, 0);
}

// ============================================================================
// Scene_Opening
// ============================================================================
void Scene_Opening::on_enter(SceneContext& ctx) {
    m_videoStarted = false;
    m_skipRequested = false;
    std::string videoPath = extract_to_temp(ctx.assets, "movie/op.mpg", ".mpg");
    if (videoPath.empty()) {
        set_next(std::make_unique<Scene_Title>());
        return;
    }
    if (!m_video.open(videoPath) || !m_video.start(ctx.device)) {
        m_video.close();
        std::remove(videoPath.c_str());
        set_next(std::make_unique<Scene_Title>());
        return;
    }
    m_videoStarted = true;
}

void Scene_Opening::on_exit(SceneContext& ctx) {
    m_video.stop();
    m_video.close();
}

UpdateResult Scene_Opening::update(SceneContext& ctx, double dt) {
    if (!m_videoStarted) return UpdateResult::Transition;
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) return UpdateResult::Quit;
        if (e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN ||
            e.type == SDL_JOYBUTTONDOWN) {
            m_skipRequested = true;
        }
    }
    m_video.update(dt);
    if (m_video.is_finished() || m_skipRequested) {
        set_next(std::make_unique<Scene_Title>());
        return UpdateResult::Transition;
    }
    return UpdateResult::Continue;
}

void Scene_Opening::render(SceneContext& ctx) {
    if (!ctx.device) return;
    ctx.device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
    if (m_videoStarted) m_video.render(ctx.device);
}

// ============================================================================
// Scene_Title — main menu with CNV background
// ============================================================================
void Scene_Title::on_enter(SceneContext& ctx) {
    std::printf("[daybreak] Title: loading background...\n");
    m_elapsed = 0.0;
    m_selected = 0;
    m_bgLoaded = false;

    // The original game uses data/select/bg00.bmp, but the actual file
    // in the .DAT is data/select/bg00.cnv (CNV format).  Our UIImage
    // auto-detects CNV and decodes it.
    if (ctx.assets && ctx.device) {
        m_bgLoaded = m_background.load_from_asset(ctx.assets, ctx.device,
                                                   "data/select/bg00.cnv");
        if (!m_bgLoaded) {
            // Fallback: try .bmp (might exist in some .DAT versions).
            m_bgLoaded = m_background.load_from_asset(ctx.assets, ctx.device,
                                                       "data/select/bg00.bmp");
        }
        if (m_bgLoaded) {
            std::printf("[daybreak] Title: background loaded (%dx%d)\n",
                        m_background.width(), m_background.height());
        }
    }
}

void Scene_Title::on_exit(SceneContext& ctx) {
    m_background.unload();
    m_bgLoaded = false;
}

UpdateResult Scene_Title::update(SceneContext& ctx, double dt) {
    m_elapsed += dt;
    if (poll_and_check_quit(ctx.input)) return UpdateResult::Quit;

    if (ctx.input) {
        const auto& p1 = ctx.input->player(0);

        if (menu_navigate(p1, m_selected, kMenuItemCount)) {
            std::printf("[daybreak] Title: → %s\n", m_items[m_selected]);
        }

        if (menu_confirmed(p1)) {
            switch (m_selected) {
                case 0: { // VS Mode
                    auto next = std::make_unique<Scene_ModeSelect>();
                    set_next(std::move(next));
                    return UpdateResult::Transition;
                }
                case 1: // Config (stub)
                    std::printf("[daybreak] Config not implemented yet\n");
                    break;
                case 2: // Key Config (stub)
                    std::printf("[daybreak] Key Config not implemented yet\n");
                    break;
                case 3: // Exit
                    return UpdateResult::Quit;
            }
        }
    }

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) return UpdateResult::Quit;
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
            return UpdateResult::Quit;
    }
    return UpdateResult::Continue;
}

void Scene_Title::render(SceneContext& ctx) {
    if (!ctx.device) return;
    ctx.device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(40, 10, 20), 1.0f, 0);
    if (m_bgLoaded) m_background.render_fullscreen(ctx.device);
}

// ============================================================================
// Scene_ModeSelect
// ============================================================================
void Scene_ModeSelect::on_enter(SceneContext& ctx) {
    std::printf("[daybreak] ModeSelect: select game mode\n");
    m_elapsed = 0.0;
    m_selected = 0;
    m_bgLoaded = false;

    if (ctx.assets && ctx.device) {
        m_bgLoaded = m_background.load_from_asset(ctx.assets, ctx.device,
                                                   "data/select/bg01.cnv");
        if (!m_bgLoaded) {
            m_bgLoaded = m_background.load_from_asset(ctx.assets, ctx.device,
                                                       "data/select/bg01.bmp");
        }
    }
}

void Scene_ModeSelect::on_exit(SceneContext& ctx) {
    m_background.unload();
    m_bgLoaded = false;
}

UpdateResult Scene_ModeSelect::update(SceneContext& ctx, double dt) {
    m_elapsed += dt;
    if (poll_and_check_quit(ctx.input)) return UpdateResult::Quit;

    if (ctx.input) {
        const auto& p1 = ctx.input->player(0);

        if (menu_navigate(p1, m_selected, kModeCount)) {
            std::printf("[daybreak] ModeSelect: → %s\n", m_modes[m_selected]);
        }

        if (menu_confirmed(p1)) {
            auto next = std::make_unique<Scene_CharacterSelect>();
            set_next(std::move(next));
            return UpdateResult::Transition;
        }

        if (menu_cancelled(p1)) {
            set_next(std::make_unique<Scene_Title>());
            return UpdateResult::Transition;
        }
    }

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) return UpdateResult::Quit;
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
            set_next(std::make_unique<Scene_Title>());
            return UpdateResult::Transition;
        }
    }
    return UpdateResult::Continue;
}

void Scene_ModeSelect::render(SceneContext& ctx) {
    if (!ctx.device) return;
    ctx.device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(20, 20, 60), 1.0f, 0);
    if (m_bgLoaded) m_background.render_fullscreen(ctx.device);
}

// ============================================================================
// Scene_CharacterSelect — portraits + selection
// ============================================================================
void Scene_CharacterSelect::on_enter(SceneContext& ctx) {
    std::printf("[daybreak] CharacterSelect: loading portraits...\n");
    m_elapsed = 0.0;
    m_selected = 0;
    m_bgLoaded = false;

    if (ctx.assets && ctx.device) {
        m_bgLoaded = m_background.load_from_asset(ctx.assets, ctx.device,
                                                   "data/select/sbg00.cnv");
        if (!m_bgLoaded) {
            m_bgLoaded = m_background.load_from_asset(ctx.assets, ctx.device,
                                                       "data/select/bg00.cnv");
        }

        // Load character portraits (p00-p03).
        for (int i = 0; i < kCharCount; ++i) {
            m_portraits[i].load_from_asset(ctx.assets, ctx.device,
                                            m_portraitAssets[i]);
            if (m_portraits[i].is_loaded()) {
                std::printf("[daybreak] CharacterSelect: portrait %d loaded (%dx%d)\n",
                            i, m_portraits[i].width(), m_portraits[i].height());
            }
        }
    }
}

void Scene_CharacterSelect::on_exit(SceneContext& ctx) {
    m_background.unload();
    for (int i = 0; i < kCharCount; ++i) m_portraits[i].unload();
    m_bgLoaded = false;
}

UpdateResult Scene_CharacterSelect::update(SceneContext& ctx, double dt) {
    m_elapsed += dt;
    if (poll_and_check_quit(ctx.input)) return UpdateResult::Quit;

    if (ctx.input) {
        const auto& p1 = ctx.input->player(0);

        if (p1.just_pressed[input::Action::Left]) {
            m_selected = (m_selected - 1 + kCharCount) % kCharCount;
            std::printf("[daybreak] CharacterSelect: → %s\n", m_charNames[m_selected]);
        }
        if (p1.just_pressed[input::Action::Right]) {
            m_selected = (m_selected + 1) % kCharCount;
            std::printf("[daybreak] CharacterSelect: → %s\n", m_charNames[m_selected]);
        }

        if (menu_confirmed(p1)) {
            std::printf("[daybreak] CharacterSelect: P1 = %s, P2 = %s\n",
                        m_charNames[m_selected], m_charNames[(m_selected + 1) % kCharCount]);
            auto next = std::make_unique<Scene_Gameplay>();
            next->m_p1CharIndex = m_selected;
            next->m_p2CharIndex = (m_selected + 1) % kCharCount;
            set_next(std::move(next));
            return UpdateResult::Transition;
        }

        if (menu_cancelled(p1)) {
            set_next(std::make_unique<Scene_ModeSelect>());
            return UpdateResult::Transition;
        }
    }

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) return UpdateResult::Quit;
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
            set_next(std::make_unique<Scene_ModeSelect>());
            return UpdateResult::Transition;
        }
    }
    return UpdateResult::Continue;
}

void Scene_CharacterSelect::render(SceneContext& ctx) {
    if (!ctx.device) return;
    ctx.device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(30, 30, 50), 1.0f, 0);

    if (m_bgLoaded) m_background.render_fullscreen(ctx.device);

    for (int i = 0; i < kCharCount; ++i) {
        if (m_portraits[i].is_loaded()) {
            int x = 50 + i * 190;
            int y = 150;
            int pw = 160;
            int ph = 160;
            m_portraits[i].render_at(ctx.device, x, y, pw, ph);
        }
    }

    // TODO: render selection highlight + character name text.
}

// ============================================================================
// Scene_Gameplay
// ============================================================================
void Scene_Gameplay::on_enter(SceneContext& ctx) {
    std::printf("[daybreak] Gameplay: P1=%d P2=%d, loading fighters + BGM...\n",
                m_p1CharIndex, m_p2CharIndex);

    static const char* char_models[] = {
        "data/rika/01.X", "data/takano/00.X",
        "data/akane/00.X", "data/rena/01.X"
    };
    static const char* char_bgm = "data/bgm/01.ogg";

    if (ctx.assets) {
        int p1 = m_p1CharIndex % 4;
        int p2 = m_p2CharIndex % 4;
        m_models[0] = ctx.assets->load_x(char_models[p1]);
        m_models[1] = ctx.assets->load_x(char_models[p2]);

        // Load stage meshes (stage21: 00.X through 06.X).
        // These are the visible geometry — collision meshes are separate.
        const char* stage_parts[] = {
            "data/stage21/00.X", "data/stage21/01.X", "data/stage21/02.X",
            "data/stage21/03.X", "data/stage21/04.X", "data/stage21/05.X",
            "data/stage21/06.X"
        };
        for (int i = 0; i < 7; ++i) {
            m_stageModels[i] = ctx.assets->load_x(stage_parts[i]);
            if (m_stageModels[i]) {
                ++m_stageModelCount;
                std::printf("[daybreak] Stage: loaded %s (%d anims)\n",
                            stage_parts[i], m_stageModels[i]->num_animation_sets());
            }
        }
        std::printf("[daybreak] Stage: %d meshes loaded\n", m_stageModelCount);

        // Projectile channel for shots (fcn.004011f0's collision_tama.x).
        // Optional: shots fly to expiry when the stage ships none.
        m_tamaCollision = ctx.assets->load_x("data/stage21/collision_tama.x");
        std::printf("[daybreak] Stage: tama collision %s\n",
                    m_tamaCollision ? "loaded" : "missing (open field)");
        m_shots.clear();
    }

    // Spawn positions from env.dat (stage01):
    // Fighter 1: (1393, -463, 200) → scaled to our coordinate system
    // Fighter 2: (-2200, -1363, 200)
    // Using the raw values — the stage .X files use the same coordinate space.
    if (m_models[0]) {
        m_spawnPos[0] = D3DXVECTOR3(1393.0f, 200.0f, -463.0f);
        m_spawnFacing[0] = 0.0f;
        m_fighters[0].init(m_models[0], m_spawnPos[0], m_spawnFacing[0]);
    }
    if (m_models[1]) {
        m_spawnPos[1] = D3DXVECTOR3(-2200.0f, 200.0f, -1363.0f);
        m_spawnFacing[1] = 3.14159f;
        m_fighters[1].init(m_models[1], m_spawnPos[1], m_spawnFacing[1]);
    }
    m_balloon[0] = m_balloon[1] = 0.0f;
    m_koAt[0] = m_koAt[1] = -1.0;

    m_fighters[0].sync_target(m_targets[0]);
    m_fighters[1].sync_target(m_targets[1]);
    m_camera.set_target_pool({&m_targets[0], &m_targets[1]});
    m_camera.set_active_target(0);

    if (ctx.audio && ctx.assets) {
        std::vector<uint8_t> bgmBytes;
        if (ctx.assets->read_file(char_bgm, bgmBytes)) {
            char tempDir[MAX_PATH];
            GetTempPathA(MAX_PATH, tempDir);
            static int bgmCounter = 0;
            char bgmPath[MAX_PATH];
            std::snprintf(bgmPath, sizeof(bgmPath), "%sdaybreak_bgm_%06d.ogg",
                          tempDir, bgmCounter++);
            std::ofstream f(bgmPath, std::ios::binary);
            if (f.is_open()) {
                f.write(reinterpret_cast<const char*>(bgmBytes.data()),
                        static_cast<std::streamsize>(bgmBytes.size()));
                f.close();
                static audio::Music bgm;
                if (bgm.load_from_file(bgmPath)) {
                    ctx.audio->play_music(bgm, -1);
                    ctx.audio->set_music_volume(64);
                }
            }
        }
    }
    m_elapsed = 0.0;
    m_stingUntil = -1.0;
    m_hudReady = ctx.device ? m_hud.init(ctx.device) : false;
}

void Scene_Gameplay::on_exit(SceneContext& ctx) {
    if (ctx.audio) ctx.audio->stop_music();
    m_hud.unload();
    m_hudReady = false;
    m_models[0] = nullptr;
    m_models[1] = nullptr;
    m_tamaCollision = nullptr;
    m_shots.clear();
    for (int i = 0; i < 7; ++i) m_stageModels[i] = nullptr;
    m_stageModelCount = 0;
}

UpdateResult Scene_Gameplay::update(SceneContext& ctx, double dt) {
    m_elapsed += dt;
    if (ctx.input) ctx.input->poll();

    const auto& p1 = ctx.input ? ctx.input->player(0) : input::PlayerInput{};

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) return UpdateResult::Quit;
        if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                set_next(std::make_unique<Scene_Title>());
                return UpdateResult::Transition;
            }
            // F2 = toggle animation debug mode.
            if (e.key.keysym.sym == SDLK_F2) {
                m_animDebug = !m_animDebug;
                if (m_animDebug && m_models[0]) {
                    int n = m_models[0]->num_animation_sets();
                    std::printf("[daybreak] ANIM DEBUG: ON (%d animation sets)\n", n);
                    for (int i = 0; i < n && i < 10; ++i) {
                        std::printf("  [%d] %s\n", i, m_models[0]->animation_set_name(i).c_str());
                    }
                    if (n > 10) std::printf("  ... (%d more)\n", n - 10);
                    m_animIndex = 0;
                    m_models[0]->switch_to_animation(0);
                } else {
                    std::printf("[daybreak] ANIM DEBUG: OFF\n");
                }
            }
        }
    }

    if (ctx.input) {
        // Target switch: Guard + AttackB.
        if (p1.just_pressed[input::Action::Guard] && p1.down[input::Action::AttackB]) {
            m_camera.cycle_target(true);
        }
        if (p1.stick_rx != 0) {
            m_camera.nudge_orbit(p1.stick_rx * 0.00001f);
        }
        const uint8_t* kb = SDL_GetKeyboardState(nullptr);
        if (kb[SDL_SCANCODE_Q]) m_camera.nudge_orbit(-0.05f);
        if (kb[SDL_SCANCODE_E]) m_camera.nudge_orbit(0.05f);
    }

    // Animation debug mode: cycle through AnimationSets with Left/Right.
    if (m_animDebug && m_models[0]) {
        int n = m_models[0]->num_animation_sets();
        if (n > 0) {
            if (p1.just_pressed[input::Action::Left]) {
                m_animIndex = (m_animIndex - 1 + n) % n;
                m_models[0]->switch_to_animation(m_animIndex);
                std::printf("[daybreak] ANIM [%d/%d] %s\n",
                            m_animIndex, n,
                            m_models[0]->animation_set_name(m_animIndex).c_str());
            }
            if (p1.just_pressed[input::Action::Right]) {
                m_animIndex = (m_animIndex + 1) % n;
                m_models[0]->switch_to_animation(m_animIndex);
                std::printf("[daybreak] ANIM [%d/%d] %s\n",
                            m_animIndex, n,
                            m_models[0]->animation_set_name(m_animIndex).c_str());
            }
            // In debug mode, skip the fighter state machine — just advance the animation.
            if (m_models[0]) m_models[0]->update(dt);
            if (m_models[1]) m_models[1]->update(dt);
        }
    } else {
        const input::PlayerInput* p1_input = ctx.input ? &ctx.input->player(0) : nullptr;
        m_fighters[0].update(p1_input, &m_fighters[1], dt);
        m_fighters[1].update(nullptr, &m_fighters[0], dt);

        // Melee resolution, both directions.
        m_fighters[0].try_melee_hit(m_fighters[1]);
        m_fighters[1].try_melee_hit(m_fighters[0]);

        // Shots: drain C-release handoffs into the pool (P2's dummy passes
        // nullptr input so it never arms — P1 exercises shots against it),
        // then advance live shots vs fighters + the tama channel.
        for (int i = 0; i < 2; ++i) {
            gameplay::PendingShot shot = m_fighters[i].take_pending_shot();
            if (shot.armed && m_fighters[i].is_alive()) {
                if (m_shots.spawn(shot.pos, shot.dir, shot.tier, &m_fighters[i])) {
                    m_shots.spawn_spark(shot.pos, 0.2f);  // muzzle flash
                }
            }
        }
        D3DXFRAME* tamaRoot = m_tamaCollision ? m_tamaCollision->root_frame()
                                             : nullptr;
        m_shots.update(dt, m_fighters, 2, tamaRoot);

        // KO → balloon → respawn / round-over bookkeeping.
        for (int i = 0; i < 2; ++i) {
            if (!m_fighters[i].is_alive() && m_koAt[i] < 0.0) {
                m_koAt[i] = m_elapsed;
                m_balloon[i] += 21.0f;
                std::printf("[daybreak] KO! side=%d balloon=%.0f%% (LIMIT %.0f%%)\n",
                            i, m_balloon[i], m_limit);
                if (m_balloon[i] >= m_limit) {
                    std::printf("[daybreak] side %d balloon burst — round over\n", i);
                    set_next(std::make_unique<Scene_Title>());
                    return UpdateResult::Transition;
                }
                m_stingUntil = m_elapsed + 2.0;  // "KO!" sting (ASCII stand-in)
            }
            if (!m_fighters[i].is_alive() && m_koAt[i] >= 0.0 &&
                m_elapsed - m_koAt[i] >= 3.0) {
                m_fighters[i].reset(m_spawnPos[i], m_spawnFacing[i]);
                m_koAt[i] = -1.0;
                std::printf("[daybreak] side %d respawned\n", i);
            }
        }
    }

    m_fighters[0].sync_target(m_targets[0]);
    m_fighters[1].sync_target(m_targets[1]);

    XModel* cam_model = m_models[0];
    if (cam_model && cam_model->root_frame()) {
        m_camera.update(dt, cam_model->root_frame());
    }

    return UpdateResult::Continue;
}

void Scene_Gameplay::render(SceneContext& ctx) {
    if (!ctx.device) return;
    ctx.device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                      D3DCOLOR_XRGB(40, 42, 54), 1.0f, 0);
    if (!m_models[0]) return;

    if (SUCCEEDED(ctx.device->BeginScene())) {
        D3DXMATRIX proj = m_camera.proj_matrix(ctx.viewport_w, ctx.viewport_h);
        ctx.device->SetTransform(D3DTS_VIEW, &m_camera.view_matrix());
        ctx.device->SetTransform(D3DTS_PROJECTION, &proj);

        ctx.device->SetRenderState(D3DRS_LIGHTING, TRUE);
        ctx.device->SetRenderState(D3DRS_AMBIENT,
            D3DCOLOR_COLORVALUE(0.35f, 0.35f, 0.35f, 1.0f));
        ctx.device->SetRenderState(D3DRS_ZENABLE, TRUE);
        ctx.device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
        ctx.device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
        ctx.device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

        D3DLIGHT9 light{};
        light.Type = D3DLIGHT_DIRECTIONAL;
        light.Diffuse = { 0.85f, 0.85f, 0.85f, 1.0f };
        light.Ambient = { 0.20f, 0.20f, 0.20f, 1.0f };
        light.Direction = { 0.5f, -1.0f, 0.5f };
        ctx.device->SetLight(0, &light);
        ctx.device->LightEnable(0, TRUE);

        // Render stage meshes first (no world transform — identity).
        D3DXMATRIX id;
        D3DXMatrixIdentity(&id);
        ctx.device->SetTransform(D3DTS_WORLD, &id);
        for (int i = 0; i < 7; ++i) {
            if (m_stageModels[i]) m_stageModels[i]->render(ctx.device);
        }

        m_fighters[0].render(ctx.device);
        m_fighters[1].render(ctx.device);
        m_shots.render(ctx.device);

        // HUD (after 3D, same scene). Layout from battle-hud.webp.
        if (!m_hudReady) m_hudReady = m_hud.init(ctx.device);
        if (m_hudReady) {
            const int W = ctx.viewport_w;
            const int H = ctx.viewport_h;
            m_hud.begin(ctx.device);
            // Balloon + LIMIT, top corners.
            m_hud.text(20, 8, D3DCOLOR_XRGB(255, 255, 255), "%.0f%%", m_balloon[0]);
            m_hud.text(20, 34, D3DCOLOR_XRGB(160, 200, 255), "LIMIT %.0f%%", m_limit);
            m_hud.text(W - 120, 8, D3DCOLOR_XRGB(255, 255, 255), "%.0f%%", m_balloon[1]);
            m_hud.text(W - 120, 34, D3DCOLOR_XRGB(255, 160, 160), "LIMIT %.0f%%", m_limit);
            m_hud.text(4, 4, D3DCOLOR_XRGB(255, 255, 0), "0");
            // Bottom-right: MAIN / CHARGE fractional stocks (P1). Bar fill is
            // the recharge readout itself (ammo-bar.webp); digits are whole
            // stock left. A RELOAD tag shows the reloadNG gate between volleys.
            const gameplay::Fighter& p1f = m_fighters[0];
            const char* reloadTag = p1f.reload_ok() ? "" : " RELOAD";
            m_hud.text(W - 220, H - 104, D3DCOLOR_XRGB(255, 255, 255), "%d MAIN%s",
                       p1f.main_whole(), reloadTag);
            m_hud.bar(W - 220, H - 80, 180, 12, p1f.main_frac(),
                      D3DCOLOR_XRGB(90, 140, 255), D3DCOLOR_XRGB(20, 20, 30));
            m_hud.text(W - 220, H - 62, D3DCOLOR_XRGB(255, 255, 255), "%d CHARGE",
                       p1f.charge_whole());
            m_hud.bar(W - 220, H - 38, 180, 12, p1f.charge_frac(),
                      D3DCOLOR_XRGB(90, 255, 150), D3DCOLOR_XRGB(20, 20, 30));
            // Charge meter while C is held: fills to red, tier colors at the
            // two hold thresholds (spec §3.1 yellow/red charge attacks).
            if (ctx.input && ctx.input->player(0).down[input::Action::Shoot] &&
                p1f.is_alive()) {
                const gameplay::ShotTier tier = p1f.charge_tier();
                const D3DCOLOR tierColor =
                    tier == gameplay::ShotTier::Red    ? D3DCOLOR_XRGB(255, 70, 50)
                    : tier == gameplay::ShotTier::Yellow ? D3DCOLOR_XRGB(255, 230, 80)
                                                         : D3DCOLOR_XRGB(120, 120, 120);
                m_hud.bar(W - 220, H - 118, 180, 8, p1f.charge_hold_frac(),
                          tierColor, D3DCOLOR_XRGB(20, 20, 30));
            }
            m_hud.text(W - 220, H - 140, D3DCOLOR_XRGB(255, 255, 255), "HP");
            m_hud.bar(W - 180, H - 140, 160, 14,
                      m_fighters[0].hp() / 100.0f,
                      D3DCOLOR_XRGB(255, 220, 60), D3DCOLOR_XRGB(20, 20, 30));
            // Bottom-left: limit gauge (empty until super meter exists).
            m_hud.text(20, H - 40, D3DCOLOR_XRGB(255, 255, 255), "OYASHIRO");
            m_hud.bar(20, H - 64, 180, 12, 0.0f,
                      D3DCOLOR_XRGB(255, 255, 255), D3DCOLOR_XRGB(20, 20, 30));
            // Stamina: contextual — dashing, blocking, or airborne
            // (battle-stamina.webp: the bar appears on use, jump spends it).
            gameplay::FighterState st = m_fighters[0].state();
            if (st == gameplay::FighterState::Run ||
                st == gameplay::FighterState::Guard ||
                st == gameplay::FighterState::Jump) {
                m_hud.text(W / 2 - 100, H - 60, D3DCOLOR_XRGB(255, 255, 255), "STAMINA");
                m_hud.bar(W / 2 - 100, H - 38, 200, 12,
                          m_fighters[0].stamina() / 100.0f,
                          D3DCOLOR_XRGB(255, 255, 255), D3DCOLOR_XRGB(20, 20, 30));
            }
            // KO sting.
            if (m_elapsed < m_stingUntil) {
                m_hud.centered(220, 100, D3DCOLOR_XRGB(255, 60, 60), "KO!");
            }
            m_hud.end();
        }
        ctx.device->EndScene();
    }
}

} // namespace daybreak
