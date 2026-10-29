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
// Identity (issue #17). A card's `id` is the id of the EVENT INSTANCE that spawned
// it: the host allocates one per spawn from a monotonic counter, so two hits in the
// same tick are two ids and each retires on its own ttl. The old discipline reused
// ids as a FIFO and kill-chained "the previous card" on every new hit, which retired
// unrelated effects whenever hits overlapped; that is gone. Re-spawning an id that is
// still live refreshes that instance in place (a repeated emitter re-arming itself).
//
// Bounded population (issue #17). `cap` bounds the live set and every refused spawn is
// counted in the tally, the same discipline SpriteRenderer's quad pool uses. The
// default is a PORT RULE sized from the recovered emitters: the heaviest one, the
// burning aura (FUN_0042e110 spawns effect 380 every 7 frames, and 038.dat's model
// animates for 0.833 s = 50 ticks at 60 Hz), holds 8 cards per burning fighter, so a
// four-fighter 2v2 with every fighter burning is 32; the transient muzzle/impact cards
// add a few per fighter on top. 128 is ~4x that worst case, and the tally proves the
// bound is never silently exceeded.
//
// Every live card ages once per call, including newborns — so a card lives ttl minus
// one tick. That one-tick shorting is pinned, not fixed: captures depend on it.
// glm + std only.
#include <algorithm>
#include <cstdint>
#include <glm/glm.hpp>
#include <vector>

#include "game/effect_events.h"

namespace game {

// The recovered worst case (see the header note) with headroom; a port rule.
inline constexpr std::size_t kMaxLiveFxCards = 128;

// One live card: the asset-table index to draw, where, and how long it has left.
struct LiveFxCard {
    std::uint32_t id = 0;
    int           asset = 0;
    glm::vec3     position{0.f};
    float         ttl = 0.f;
    float         age = 0.f;
    // The direction the spawn request posed, forwarded from the event (see
    // effect_events.h). A zero direction is the unposed case, which composes to a
    // translation-only matrix exactly as before.
    glm::vec3     direction{0.f};
};

// What one update did, so a run can prove the population stayed bounded.
struct FxCardTally {
    std::uint32_t spawned = 0;   // cards created
    std::uint32_t dropped = 0;   // spawns refused because the set was at `cap`
    std::uint32_t expired = 0;   // cards retired by their own ttl
    std::uint32_t killed  = 0;   // cards retired by an explicit kill event
};

// Apply drained events to the live set in queue order, then age every card by
// dt and expire the spent ones. Kill-by-unknown-id is a no-op; a spawn with an
// asset index the table does not carry is kept (placement skips it) so a bad
// push site stays visible in the set rather than vanishing silently.
inline FxCardTally updateLiveFxCards(std::vector<LiveFxCard>& live,
                                     const std::vector<EffectEvent>& events, float dt,
                                     std::size_t cap = kMaxLiveFxCards) {
    FxCardTally tally;
    for (const EffectEvent& e : events) {
        if (e.type == EffectEvent::Type::Kill) {
            const std::size_t before = live.size();
            live.erase(std::remove_if(live.begin(), live.end(),
                                      [&](const LiveFxCard& c) { return c.id == e.id; }),
                       live.end());
            tally.killed += (std::uint32_t)(before - live.size());
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
            slot->direction = e.direction;
        } else if (live.size() < cap) {
            live.push_back(LiveFxCard{e.id, e.asset, e.position, e.ttlSeconds, 0.f,
                                      e.direction});
            ++tally.spawned;
        } else {
            ++tally.dropped;
        }
    }
    for (LiveFxCard& c : live) c.age += dt;
    const std::size_t before = live.size();
    live.erase(std::remove_if(live.begin(), live.end(),
                              [](const LiveFxCard& c) { return c.age >= c.ttl; }),
               live.end());
    tally.expired = (std::uint32_t)(before - live.size());
    return tally;
}

}  // namespace game
