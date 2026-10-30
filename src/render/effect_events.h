#pragma once
// Effect-spawn event queue: how gameplay tells the renderer which effect
// cards to draw and kill, without the renderer knowing combat rules.
//
// WHY a drained queue, not callbacks: effect passes already draw cards by
// role (scene_renderer's additive/unculled effect pass, Track R2), but the
// demo loads them from --effect file arguments — verification scaffolding,
// not gameplay. The real driver is combat (muzzle flashes, hit sparks:
// remake/src/core/scenes.cpp arms PendingShot and calls
// m_shots.spawn/spawn_spark; projectile.h owns lifetimes). The game pushes
// one event per spawn/kill; the renderer drains the queue once per frame and
// owns the live card set after that. FIFO keeps same-frame ordering
// deterministic (a kill never overtakes its spawn). Gameplay decides what
// spawns — this header only carries the decision. glm + std only.
#include <cstdint>
#include <glm/glm.hpp>
#include <vector>

namespace game {

// One effect event. Spawn carries everything the renderer needs to instance
// a card (world position + which effect asset to draw + lifetime); kill
// retires a live card by id (hit-spark expiry, projectile.h lifetimes).
// `id` is an EVENT INSTANCE id: the spawner allocates one per spawn from a
// monotonic counter (issue #17), so two hits in the same tick are two instances and
// each retires on its own ttl — never a reused FIFO slot. `asset` indexes the
// renderer's effect-asset table — never a file path, so no asset-layer dependency
// leaks into gameplay code.
struct EffectEvent {
    enum class Type : std::uint8_t { Spawn, Kill };

    Type      type = Type::Spawn;
    std::uint32_t id = 0;          // game-assigned; unique per live card
    glm::vec3 position{0.f};       // spawn origin, Y-up game units (spawn only)
    int       asset = 0;           // effect-asset table index (spawn only)
    float     ttlSeconds = 0.f;    // renderer-side expiry (spawn only)
    // The direction the request posed the effect with (spawn only), zero when the
    // caller has none. FUN_00421aa0 builds it from the request's own (heading, pitch)
    // and the effect instance's draw composes it into its matrix (FUN_00436150:
    // RotationZ then RotationY then translation — the same order render/shot_visual.h
    // recovers for the shots). Carrying it is what lets a posed effect keep its pose;
    // the port's draw used to translate only, which dropped it.
    glm::vec3 direction{0.f};
};

// Dumb FIFO the renderer drains once per frame. `drain()` moves the pending
// events out and clears — the renderer owns them afterwards, so a second
// drain in the same frame is empty by construction. Unbounded by design: the
// per-frame drain bounds it in practice, and a cap would silently drop hits.
class EffectEventQueue {
public:
    void pushSpawn(std::uint32_t id, const glm::vec3& position, int asset, float ttlSeconds,
                  const glm::vec3& direction = glm::vec3(0.f)) {
        pending_.push_back(EffectEvent{EffectEvent::Type::Spawn, id, position, asset,
                                       ttlSeconds, direction});
    }

    void pushKill(std::uint32_t id) {
        pending_.push_back(EffectEvent{EffectEvent::Type::Kill, id, {}, 0, 0.f});
    }

    std::vector<EffectEvent> drain() {
        std::vector<EffectEvent> out;
        out.swap(pending_);
        return out;
    }

    bool   empty() const { return pending_.empty(); }
    size_t pending() const { return pending_.size(); }

private:
    std::vector<EffectEvent> pending_;
};

}  // namespace game
