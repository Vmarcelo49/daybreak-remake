// Online rollback (docs/ONLINE-PLAN.md, step 1): rewinding and replaying a battle through a ring of
// snapshots must end exactly where a battle that never rewound does, through the end of the match.
// Tier 4 at most: this is agreement with itself, and says nothing about the original.
#include "battle/battle.h"

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <stdexcept>
#include <string>

namespace {

int failures = 0;
void check(bool condition, const std::string& name) {
    if (condition) return;
    ++failures;
    std::printf("FAIL: %s\n", name.c_str());
}

std::string find_game() {
    if (const char* configured = std::getenv("GAME_DIR")) return configured;
    namespace fs = std::filesystem;
    for (auto path = fs::current_path();; path = path.parent_path()) {
        if (fs::exists(path / "Higurashi-Daybreak" / "daybreak00.dat")) return (path / "Higurashi-Daybreak").string();
        if (path == path.parent_path()) return {};
    }
}

// Busy, repeatable hands: a small generator, so a different salt is a different prediction.
sim::Inputs busy_inputs(unsigned tick, unsigned salt) {
    sim::Inputs inputs{};
    for (unsigned i = 0; i < 4; ++i) {
        const unsigned held = (tick / (11u + i * 3u) + salt) * 2654435761u + i * 40503u;
        const unsigned bits = held >> 20;
        inputs[i].x = static_cast<int>(bits & 3u) - 1;
        inputs[i].z = static_cast<int>((bits >> 2) & 3u) - 1;
        if (bits & 16u) inputs[i].buttons |= sim::Shoot;
        if (bits & 32u) inputs[i].buttons |= sim::Melee;
        if ((bits & 192u) == 192u) inputs[i].buttons |= sim::Jump;
        if ((bits & 768u) == 768u) inputs[i].buttons |= sim::Guard;
        if ((bits & 3072u) == 3072u) inputs[i].buttons |= sim::Target;
        if ((bits & 12288u) == 12288u) inputs[i].buttons |= sim::Tactics;
    }
    return inputs;
}

constexpr unsigned kRing = 9, kMaxRollback = kRing - 1, kAfterEnd = 120, kTimeLimit = 60;

void run_match(const std::string& name, const sim::BattleConfig& config) {
    sim::Battle reference(config), rolled(config);
    sim::BattleSnapshot ring[kRing];
    unsigned rollbacks = 0, maxLive = 0, after = 0, tick = 0;
    int lowestHp = 1 << 30;

    for (; after < kAfterEnd && tick < kTimeLimit * 60u + 600u; ++tick) {
        const sim::Inputs inputs = busy_inputs(tick, 0);
        reference.step(inputs);
        rolled.saveState(ring[tick % kRing]);
        rolled.step(inputs);

        const unsigned depth = 1 + tick % kMaxRollback;
        if (tick + 1 >= depth) {
            const unsigned from = tick + 1 - depth;
            // A wrong prediction runs, and is then replaced by the inputs that really happened.
            rolled.loadState(ring[from % kRing]);
            for (unsigned t = from; t <= tick; ++t) rolled.step(busy_inputs(t, 1 + rollbacks));
            rolled.loadState(ring[from % kRing]);
            for (unsigned t = from; t <= tick; ++t) {
                rolled.saveState(ring[t % kRing]);
                rolled.step(busy_inputs(t, 0));
            }
            ++rollbacks;
        }
        if (rolled.stateHash() != reference.stateHash() || rolled.hash() != reference.hash()) {
            check(false, name + ": diverged at tick " + std::to_string(tick));
            return;
        }
        maxLive = std::max(maxLive, reference.live_projectiles());
        for (unsigned i = 0; i < 4; ++i) lowestHp = std::min(lowestHp, reference.actor(i).hp);
        if (reference.match_finished()) ++after;
    }
    std::printf("%s: %u ticks, %u rollbacks, up to %u projectiles, lowest hp %d, finished %d\n", name.c_str(), tick,
                rollbacks, maxLive, lowestHp, reference.match_finished());
    check(reference.match_finished(), name + ": the match never finished, so its end went untested");
    check(maxLive > 0, name + ": no projectile was ever alive");
    check(lowestHp < 1000, name + ": nobody was hurt");
}

sim::BattleConfig make_config(const std::string& game, std::array<sim::Slot, 4> slots, unsigned stage, std::uint32_t seed) {
    sim::BattleConfig config;
    config.gameDir = game;
    config.slots = slots;
    config.stage = stage;
    config.seed = seed;
    config.timeLimitSeconds = kTimeLimit;
    return config;
}

void test_every_field_counts(const sim::BattleConfig& config) {
    sim::Battle battle(config);
    for (unsigned t = 0; t < 300; ++t) battle.step(busy_inputs(t, 0));
    const std::uint64_t base = battle.stateHash();
    const unsigned fields = battle.stateFieldCount();
    check(fields > 100, "the hash lost its fields");
    for (unsigned i = 0; i < fields; ++i) {
        battle.flipStateFieldForTest(i);
        check(battle.stateHash() != base, "field " + std::to_string(i) + " does not reach the hash");
        battle.flipStateFieldForTest(i);
    }
    check(battle.stateHash() == base, "flipping twice did not restore the hash");
    std::printf("%u fields reach the hash\n", fields);
}

void test_hash_is_the_state(const sim::BattleConfig& config) {
    sim::Battle a(config), b(config);
    check(a.stateHash() == b.stateHash(), "two new battles differ");
    a.step(busy_inputs(0, 0));
    b.step(busy_inputs(0, 7));
    for (unsigned t = 1; t < 120; ++t) {
        a.step(busy_inputs(t, 0));
        b.step(busy_inputs(t, 7));
    }
    check(a.stateHash() != b.stateHash(), "different inputs gave the same state hash");
    sim::BattleSnapshot empty;
    bool refused = false;
    try {
        a.loadState(empty);
    } catch (const std::logic_error&) {
        refused = true;
    }
    check(refused, "an empty snapshot was loaded");
}

}  // namespace

int main() {
    const std::string game = find_game();
    if (game.empty()) {
        std::printf("SKIP: no install\n");
        return 77;
    }
    // Character and weapon are core indices. Rows cover humans only, one human, and all COM.
    const auto human = [](int c, int w) { sim::Slot s; s.character = c; s.weapon = w; s.cpu = false; return s; };
    const auto com = [](int c, int w) { sim::Slot s; s.character = c; s.weapon = w; return s; };
    const auto first = make_config(game, {human(0, 0), human(1, 1), human(2, 2), human(3, 0)}, 1, 1);
    test_every_field_counts(first);
    test_hash_is_the_state(first);
    run_match("4 humans", first);
    run_match("4 humans, others", make_config(game, {human(4, 1), human(5, 2), human(6, 0), human(7, 1)}, 2, 2));
    run_match("1 human", make_config(game, {human(8, 2), com(9, 0), com(10, 1), com(11, 2)}, 3, 3));
    run_match("all COM", make_config(game, {com(12, 0), com(13, 1), com(14, 1), com(15, 0)}, 21, 4));
    if (failures) {
        std::printf("rollback_stress_test: %d failure(s)\n", failures);
        return 1;
    }
    std::printf("rollback_stress_test: ok\n");
    return 0;
}
