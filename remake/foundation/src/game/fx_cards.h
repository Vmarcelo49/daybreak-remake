#pragma once
// Live effect-card set: who owns the cards the renderer draws from the event
// queues, and when they die.
//
// WHY a separate header: the spawn/kill/ttl rules are renderer-side bookkeeping
// with no scene dependency, so they are unit-tested here instead of through
// captures (see tests/fx_cards_test.cpp). The placement half — card set to
// model matrices each frame — stays with the renderer wiring in main.cpp,
// which owns the asset table and the matrix upload.
//
// Lifecycle, matching the queue's contract (game/effect_events.h): a spawn
// replaces a live card of the same id (the push sites reuse ids as a FIFO —
// match mode kill-chains hit N-1 when hit N lands), a kill retires by id, and
// ttl expiry retires the rest. Every live card ages once per call, including
// newborns — so a card lives ttl minus one tick. That one-tick shorting is
// pinned, not fixed: captures depend on it. glm + std only.
#include <algorithm>
#include <cstdint>
#include <glm/glm.hpp>
#include <vector>

#include "game/effect_events.h"

namespace game {

// One live card: the asset-table index to draw, where, and how long it has left.
struct LiveFxCard {
    std::uint32_t id = 0;
    int           asset = 0;
    glm::vec3     position{0.f};
    float         ttl = 0.f;
    float         age = 0.f;
};

// Apply drained events to the live set in queue order, then age every card by
// dt and expire the spent ones. Kill-by-unknown-id is a no-op; a spawn with an
// asset index the table does not carry is kept (placement skips it) so a bad
// push site stays visible in the set rather than vanishing silently.
inline void updateLiveFxCards(std::vector<LiveFxCard>& live,
                             const std::vector<EffectEvent>& events, float dt) {
    for (const EffectEvent& e : events) {
        if (e.type == EffectEvent::Type::Kill) {
            live.erase(std::remove_if(live.begin(), live.end(),
                                      [&](const LiveFxCard& c) { return c.id == e.id; }),
                       live.end());
            continue;
        }
        LiveFxCard* slot = nullptr;
        for (LiveFxCard& c : live)
            if (c.id == e.id) {
                slot = &c;
                break;
            }
        if (slot) {
            slot->asset = e.asset;
            slot->position = e.position;
            slot->ttl = e.ttlSeconds;
            slot->age = 0.f;
        } else {
            live.push_back(LiveFxCard{e.id, e.asset, e.position, e.ttlSeconds, 0.f});
        }
    }
    for (LiveFxCard& c : live) c.age += dt;
    live.erase(std::remove_if(live.begin(), live.end(),
                              [](const LiveFxCard& c) { return c.age >= c.ttl; }),
               live.end());
}

}  // namespace game
