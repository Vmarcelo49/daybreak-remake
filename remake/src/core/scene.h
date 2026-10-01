// =============================================================================
//  scene.h — base class for game scenes (state machine pattern).
// =============================================================================
#pragma once

#include <d3d9.h>

#include <memory>
#include <string>

namespace daybreak {

namespace assets { class AssetManager; }
namespace audio  { class AudioEngine; }
namespace input  { class InputManager; }
namespace render { class EffectSystem; }

// Shared resources passed to every scene.  Owned by App, not by scenes.
struct SceneContext {
    IDirect3DDevice9*         device      = nullptr;
    assets::AssetManager*     assets      = nullptr;
    audio::AudioEngine*       audio       = nullptr;
    input::InputManager*       input       = nullptr;
    render::EffectSystem*     effects     = nullptr;
    int                       viewport_w  = 800;
    int                       viewport_h  = 600;
};

enum class UpdateResult {
    Continue,
    Transition,
    Quit,
};

class SceneManager;

class Scene {
public:
    virtual ~Scene() = default;
    virtual void on_enter(SceneContext& ctx) {}
    virtual void on_exit(SceneContext& ctx) {}
    virtual UpdateResult update(SceneContext& ctx, double dt) { return UpdateResult::Continue; }
    virtual void render(SceneContext& ctx) {}
    virtual const char* name() const { return "Scene"; }
    std::unique_ptr<Scene> take_next_scene() { return std::move(m_next); }
protected:
    void set_next(std::unique_ptr<Scene> next) { m_next = std::move(next); }
private:
    std::unique_ptr<Scene> m_next;
};

} // namespace daybreak
