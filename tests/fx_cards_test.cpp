// =============================================================================
//  fx_cards_test.cpp — host test for game/fx_cards.h (ROADMAP-PENDING.md B1,
//  issue #17): the live effect-card set — spawn replaces by id, kill retires by
//  id, ttl expiry retires the rest, every card ages once per call, and the set is
//  bounded with a counted drop. Per-instance identity is pinned directly: two
//  spawns in the same tick are two cards, and each one's ttl retires only itself.
//
//  No WebGPU, no SDL, no device. Header-only under test (glm + std); the
//  placement half (card set -> model matrices) stays in main.cpp with the
//  renderer wiring and is covered by captures, not here.
//
//    g++ -std=c++17 -Wall -Wextra -I remake/foundation/src
//        -I remake/foundation/third_party/glm
//        remake/foundation/tests/fx_cards_test.cpp -o /tmp/fx_cards_test
//    /tmp/fx_cards_test              # prints FX_CARDS: ok|FAIL
//
//  All time arithmetic uses binary-exact steps (0.25/0.5 s), so every boundary
//  below is exact and a mismatch is a real divergence, not rounding noise.
// =============================================================================

#include <cmath>
#include <cstdio>
#include <string>
#include <vector>

#include "game/effect_events.h"
#include "game/fx_cards.h"

namespace {

int g_checks = 0;
int g_failed = 0;

void check_int(const char* what, long long want, long long got) {
    ++g_checks;
    const bool ok = (want == got);
    if (!ok) ++g_failed;
    std::printf("  %-58s exp %-12lld got %-12lld %s\n", what, want, got, ok ? "ok" : "FAIL");
}

void check_near(const char* what, float want, float got, float tol) {
    ++g_checks;
    const bool ok = std::fabs(want - got) <= tol;
    if (!ok) ++g_failed;
    std::printf("  %-58s exp %-12.6g got %-12.6g %s\n", what, (double)want, (double)got,
                ok ? "ok" : "FAIL");
}

game::EffectEvent spawnEv(std::uint32_t id, int asset, float ttl) {
    game::EffectEvent e;
    e.type = game::EffectEvent::Type::Spawn;
    e.id = id;
    e.position = glm::vec3(10.f, 100.f, 20.f);
    e.asset = asset;
    e.ttlSeconds = ttl;
    return e;
}

game::EffectEvent killEv(std::uint32_t id) {
    game::EffectEvent e;
    e.type = game::EffectEvent::Type::Kill;
    e.id = id;
    return e;
}

}  // namespace

int main() {
    std::printf("== fx_cards: live set lifecycle ==\n");

    // 1. A spawn lands with its fields carried over.
    {
        std::vector<game::LiveFxCard> live;
        game::updateLiveFxCards(live, {spawnEv(7, 0, 12.f)}, 0.25f);
        check_int("spawn adds one card", 1, (long long)live.size());
        check_int("spawn keeps the id", 7, (long long)live[0].id);
        check_int("spawn keeps the asset", 0, (long long)live[0].asset);
        check_near("spawn keeps the position", 100.f, live[0].position.y, 1e-6f);
        check_near("newborn ages in its spawn frame", 0.25f, live[0].age, 1e-6f);
    }

    // 1b. The request's pose survives the queue: FUN_00421aa0's direction is carried
    // on the event, a re-spawn refreshes it, and an unposed spawn leaves it zero (which
    // composes to the translation-only matrix the placement builds from it).
    {
        std::vector<game::LiveFxCard> live;
        game::EffectEvent posed = spawnEv(9, 1, 4.f);
        posed.direction = glm::vec3(0.5f, 0.f, -0.25f);
        game::updateLiveFxCards(live, {posed}, 0.25f);
        check_near("spawn keeps the requested direction x", 0.5f,
                   live[0].direction.x, 1e-6f);
        check_near("spawn keeps the requested direction z", -0.25f,
                   live[0].direction.z, 1e-6f);
        // A repeated emitter re-arming itself re-poses the existing instance.
        game::EffectEvent reposed = spawnEv(9, 1, 4.f);
        reposed.direction = glm::vec3(0.f, 1.f, 0.f);
        game::updateLiveFxCards(live, {reposed}, 0.25f);
        check_int("a re-spawn refreshes in place", 1, (long long)live.size());
        check_near("a re-spawn re-poses the instance", 1.f, live[0].direction.y, 1e-6f);
        // And the direction is default-zero, so the unposed callers are unchanged.
        game::updateLiveFxCards(live, {spawnEv(11, 1, 4.f)}, 0.25f);
        check_near("an unposed spawn keeps the direction zero", 0.f,
                   live[1].direction.x * live[1].direction.y * live[1].direction.z,
                   1e-6f);
    }

    // 2. Same-id spawn replaces: fields refresh, age resets, count stays 1.
    {
        std::vector<game::LiveFxCard> live;
        game::updateLiveFxCards(live, {spawnEv(7, 0, 12.f)}, 0.25f);
        game::updateLiveFxCards(live, {spawnEv(7, 2, 5.f)}, 0.25f);
        check_int("re-spawn keeps one card", 1, (long long)live.size());
        check_int("re-spawn updates the asset", 2, (long long)live[0].asset);
        check_near("re-spawn resets the age then ages once", 0.25f, live[0].age, 1e-6f);
    }

    // 3. Kill retires by id; unknown ids are a no-op.
    {
        std::vector<game::LiveFxCard> live;
        game::updateLiveFxCards(live, {spawnEv(7, 0, 12.f), spawnEv(8, 0, 12.f)}, 0.25f);
        game::updateLiveFxCards(live, {killEv(7)}, 0.25f);
        check_int("kill retires its id", 1, (long long)live.size());
        check_int("kill keeps the other card", 8, (long long)live[0].id);
        game::updateLiveFxCards(live, {killEv(99)}, 0.25f);
        check_int("kill-by-unknown-id is a no-op", 1, (long long)live.size());
    }

    // 4. Queue order within a frame: spawn-then-kill vanishes, kill-then-spawn stays.
    {
        std::vector<game::LiveFxCard> live;
        game::updateLiveFxCards(live, {spawnEv(7, 0, 12.f), killEv(7)}, 0.25f);
        check_int("spawn-then-kill leaves nothing", 0, (long long)live.size());
        game::updateLiveFxCards(live, {killEv(7), spawnEv(7, 0, 12.f)}, 0.25f);
        check_int("kill-then-spawn leaves the card", 1, (long long)live.size());
    }

    // 5. ttl expiry on exact boundaries (0.25 s steps, ttl 1 s).
    {
        std::vector<game::LiveFxCard> live;
        game::updateLiveFxCards(live, {spawnEv(7, 0, 1.f)}, 0.25f);   // age 0.25
        game::updateLiveFxCards(live, {}, 0.25f);                      // 0.50
        game::updateLiveFxCards(live, {}, 0.25f);                      // 0.75
        check_int("card alive before its ttl", 1, (long long)live.size());
        game::updateLiveFxCards(live, {}, 0.25f);                      // 1.00 >= 1
        check_int("card expires exactly at its ttl", 0, (long long)live.size());
    }

    // 6. Zero dt freezes aging; zero ttl with positive dt expires at once.
    {
        std::vector<game::LiveFxCard> live;
        game::updateLiveFxCards(live, {spawnEv(7, 0, 12.f)}, 0.f);
        check_near("zero dt ages nothing", 0.f, live[0].age, 0.f);
        std::vector<game::LiveFxCard> quick;
        game::updateLiveFxCards(quick, {spawnEv(9, 0, 0.f)}, 0.25f);
        check_int("zero ttl expires on its spawn frame", 0, (long long)quick.size());
    }

    // 7. Unmapped asset indices are kept (placement skips them visibly).
    {
        std::vector<game::LiveFxCard> live;
        game::updateLiveFxCards(live, {spawnEv(7, 99, 12.f)}, 0.25f);
        check_int("bad-asset spawn stays in the set", 1, (long long)live.size());
        check_int("bad-asset index passthrough", 99, (long long)live[0].asset);
    }

    // 8. Per-instance identity (issue #17): two hits in the SAME tick are two
    //    instances with their own ttls, and each expires only itself. The old
    //    kill-chaining discipline retired the first card when the second landed.
    {
        std::vector<game::LiveFxCard> live;
        game::updateLiveFxCards(live, {spawnEv(100, 0, 1.f), spawnEv(101, 0, 2.f)}, 0.25f);
        check_int("two same-tick hits are two cards", 2, (long long)live.size());
        check_int("the first keeps its own id", 100, (long long)live[0].id);
        check_int("the second keeps its own id", 101, (long long)live[1].id);
        game::updateLiveFxCards(live, {}, 0.25f);   // 0.50
        game::updateLiveFxCards(live, {}, 0.25f);   // 0.75
        check_int("neither has expired early", 2, (long long)live.size());
        game::updateLiveFxCards(live, {}, 0.25f);   // 1.00: only id 100 is spent
        check_int("the shorter-lived card expires alone", 1, (long long)live.size());
        check_int("the longer-lived card is untouched", 101, (long long)live[0].id);
        game::updateLiveFxCards(live, {}, 1.0f);    // 2.00: the second follows
        check_int("the second expires on its own ttl", 0, (long long)live.size());
    }

    // 9. A live instance re-armed by the same id refreshes in place (a repeated
    //    emitter), and does not duplicate.
    {
        std::vector<game::LiveFxCard> live;
        game::updateLiveFxCards(live, {spawnEv(5, 0, 1.f)}, 0.25f);
        game::updateLiveFxCards(live, {spawnEv(5, 1, 4.f)}, 0.25f);
        check_int("re-arming an id keeps one card", 1, (long long)live.size());
        check_int("re-arming refreshes the asset", 1, (long long)live[0].asset);
        game::updateLiveFxCards(live, {}, 1.0f);
        check_int("the refreshed ttl governs", 1, (long long)live.size());
    }

    // 10. Bounded population with a counted drop (issue #17): the cap holds and
    //     every refused spawn is counted rather than silently lost.
    {
        std::vector<game::LiveFxCard> live;
        std::vector<game::EffectEvent> flood;
        for (std::uint32_t i = 0; i < 40; ++i) flood.push_back(spawnEv(i, 0, 10.f));
        const game::FxCardTally t = game::updateLiveFxCards(live, flood, 0.25f, 16);
        check_int("the cap bounds the live set", 16, (long long)live.size());
        check_int("accepted spawns are counted", 16, (long long)t.spawned);
        check_int("refused spawns are counted", 24, (long long)t.dropped);
        const game::FxCardTally t2 = game::updateLiveFxCards(live, {killEv(3)}, 0.25f, 16);
        check_int("an explicit kill is counted", 1, (long long)t2.killed);
        check_int("a kill frees a slot", 15, (long long)live.size());
    }

    // 11. The tally separates ttl expiry from explicit kills.
    {
        std::vector<game::LiveFxCard> live;
        game::FxCardTally t = game::updateLiveFxCards(live, {spawnEv(1, 0, 0.5f)}, 0.25f);
        check_int("a fresh spawn is counted", 1, (long long)t.spawned);
        t = game::updateLiveFxCards(live, {}, 0.25f);
        check_int("expiry is counted, not killed", 1, (long long)t.expired);
        check_int("expiry is not a kill", 0, (long long)t.killed);
        t = game::updateLiveFxCards(live, {killEv(2)}, 0.25f);
        check_int("an unknown kill counts nothing", 0, (long long)t.killed);
    }

    // 12. The card animation clock (game/fx_cards.h). RECOVERED rule: a card's lifetime IS
    // its clip's length (EffectEntry::lifetimeSeconds comes from the model's own
    // AnimationSet), and the original drives the clip with age * 0.016 — so at birth the
    // card is on its first frame, halfway through its life on the middle of the clip, and
    // at expiry on the last. The edges are what this pins: a zero lifetime or a model with
    // no animation must yield 0 rather than a division by zero, and a past-expiry age must
    // clamp instead of overshooting the clip.
    {
        check_near("birth is the first frame", 0.0,
                   static_cast<float>(game::cardAnimationSeconds(0.f, 2.f, 1.5)), 1e-6f);
        check_near("half life is half the clip", 0.75,
                   static_cast<float>(game::cardAnimationSeconds(1.f, 2.f, 1.5)), 1e-6f);
        check_near("expiry is the last frame", 1.5,
                   static_cast<float>(game::cardAnimationSeconds(2.f, 2.f, 1.5)), 1e-6f);
        check_near("a past-expiry age clamps", 1.5,
                   static_cast<float>(game::cardAnimationSeconds(9.f, 2.f, 1.5)), 1e-6f);
        check_near("a zero lifetime yields no time", 0.0,
                   static_cast<float>(game::cardAnimationSeconds(1.f, 0.f, 1.5)), 1e-6f);
        check_near("a model with no clip yields no time", 0.0,
                   static_cast<float>(game::cardAnimationSeconds(1.f, 2.f, 0.0)), 1e-6f);
        check_near("a negative age cannot rewind", 0.0,
                   static_cast<float>(game::cardAnimationSeconds(-1.f, 2.f, 1.5)), 1e-6f);
        check_near("matching lifetime is the age", 0.4,
                   static_cast<float>(game::cardAnimationSeconds(0.4f, 0.4f, 0.4)), 1e-6f);
    }

    std::printf("%d checks, %d failed\n", g_checks, g_failed);
    std::printf(g_failed ? "FX_CARDS: FAIL\n" : "FX_CARDS: ok\n");
    return g_failed ? 1 : 0;
}
