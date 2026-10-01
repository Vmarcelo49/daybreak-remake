// =============================================================================
//  scene_manager.h — owns the active scene and handles transitions.
//
//  The SceneManager is the glue between the main loop and the scenes.
//  It holds:
//    - The current scene (unique_ptr, swapped on transition)
//    - The shared SceneContext (device, assets, viewport size)
//
//  Main loop pattern:
//    SceneManager mgr(ctx);
//    mgr.start(std::make_unique<Scene_Opening>());
//    while (mgr.is_running()) {
//        double dt = compute_delta_time();
//        UpdateResult r = mgr.update(dt);
//        if (r == UpdateResult::Quit) break;
//        mgr.render();
//    }
//
//  When a scene returns Transition, the manager takes its next-scene
//  factory, calls on_exit on the old scene, on_enter on the new, and
//  swaps them.  This keeps transitions atomic (no half-state).
// =============================================================================
#pragma once

#include <memory>

#include "scene.h"

namespace daybreak {

class SceneManager {
public:
    explicit SceneManager(SceneContext ctx) : m_ctx(ctx) {}

    // Sets the initial scene and calls its on_enter.
    void start(std::unique_ptr<Scene> initial);

    // True if there's an active scene and the game should keep running.
    bool is_running() const { return m_current != nullptr; }

    // Updates the active scene.  If the scene returns Transition, swaps
    // to the next scene (calls on_exit + on_enter).  If it returns Quit,
    // clears the active scene (is_running becomes false).
    UpdateResult update(double dt);

    // Renders the active scene (single full-screen viewport for now;
    // split-screen is handled by the gameplay scene itself, which calls
    // render() multiple times with different D3DVIEWPORT9 settings).
    void render();

    // Re-enters the active scene (on_exit + on_enter).  Used after a
    // D3D device Reset, which destroys D3DPOOL_DEFAULT resources
    // (UIImage textures/vertex buffers, video textures) that only
    // scene on_enter rebuilds.
    void reset_current();

    // Force-quit (e.g. window close).
    void quit() { m_current.reset(); }

    const SceneContext& context() const { return m_ctx; }
    Scene* current() const { return m_current.get(); }

private:
    SceneContext              m_ctx;
    std::unique_ptr<Scene>    m_current;
};

} // namespace daybreak
