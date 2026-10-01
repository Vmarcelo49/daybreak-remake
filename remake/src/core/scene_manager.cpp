// =============================================================================
//  scene_manager.cpp — see scene_manager.h for design rationale.
// =============================================================================
#include "scene_manager.h"

#include <cstdio>

namespace daybreak {

void SceneManager::start(std::unique_ptr<Scene> initial) {
    if (!initial) return;
    m_current = std::move(initial);
    m_current->on_enter(m_ctx);
    std::printf("[daybreak] scene → %s\n", m_current->name());
}

UpdateResult SceneManager::update(double dt) {
    if (!m_current) return UpdateResult::Quit;

    UpdateResult r = m_current->update(m_ctx, dt);
    if (r == UpdateResult::Transition) {
        std::unique_ptr<Scene> next = m_current->take_next_scene();
        if (next) {
            m_current->on_exit(m_ctx);
            std::string oldName = m_current->name();
            m_current = std::move(next);
            m_current->on_enter(m_ctx);
            std::printf("[daybreak] scene %s → %s\n", oldName.c_str(), m_current->name());
        } else {
            std::fprintf(stderr, "[daybreak] scene returned Transition but no next scene set\n");
            r = UpdateResult::Continue;
        }
    } else if (r == UpdateResult::Quit) {
        m_current->on_exit(m_ctx);
        m_current.reset();
    }
    return r;
}

void SceneManager::render() {
    if (!m_current) return;
    m_current->render(m_ctx);
}

void SceneManager::reset_current() {
    if (!m_current) return;
    m_current->on_exit(m_ctx);
    m_current->on_enter(m_ctx);
}

} // namespace daybreak
