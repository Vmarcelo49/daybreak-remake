// =============================================================================
//  fx_cards_test.cpp — host test for game/fx_cards.h (ROADMAP-PENDING.md B1):
//  the live effect-card set — spawn replaces by id, kill retires by id,
//  ttl expiry retires the rest, every card ages once per call.
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

    std::printf("%d checks, %d failed\n", g_checks, g_failed);
    std::printf(g_failed ? "FX_CARDS: FAIL\n" : "FX_CARDS: ok\n");
    return g_failed ? 1 : 0;
}
