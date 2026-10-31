// Online play (docs/ONLINE-PLAN.md, step 3): GekkoNet's stress session rolling back the real battle.
// Tier 4 at most: agreement with itself, and nothing about the original.
#include "net/session.h"

#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <vector>

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

sim::Inputs busy_inputs(unsigned tick) {
    sim::Inputs inputs{};
    for (unsigned i = 0; i < 4; ++i) {
        const unsigned bits = (tick / (11u + i * 3u) * 2654435761u + i * 40503u) >> 20;
        inputs[i].x = static_cast<int>(bits & 3u) - 1;
        inputs[i].z = static_cast<int>((bits >> 2) & 3u) - 1;
        if (bits & 16u) inputs[i].buttons |= sim::Shoot;
        if (bits & 32u) inputs[i].buttons |= sim::Melee;
    }
    return inputs;
}

sim::BattleConfig make_config(const std::string& game, bool humans) {
    sim::BattleConfig config;
    config.gameDir = game;
    for (unsigned i = 0; i < 4; ++i) config.slots[i] = {static_cast<int>(i), 0, !humans};
    config.timeLimitSeconds = 30;
    return config;
}

constexpr unsigned kTicks = 30 * 60 + 2400;
// A 60 Hz frame, less what docs/PERFORMANCE.md measured the four-view renderer needing.
constexpr double kUpdateBudgetMs = 16.7 - 5.3;
constexpr std::array<const gameplay::CharacterMoves*, 4> kNoMoves{};
constexpr std::array<const gameplay::WeaponDefinition*, 4> kNoWeapons{};

// A full match with an 8-tick rollback on every update ends where a plain match does.
void test_full_match(const std::string& game, bool humans) {
    sim::CoreBattle plain, stressed;
    plain.start(make_config(game, humans), kNoMoves, kNoWeapons);
    stressed.start(make_config(game, humans), kNoMoves, kNoWeapons);
    const auto session = net::Session::stress(stressed, 8);

    unsigned rounds = 0, over = 0;
    for (unsigned t = 0; t < kTicks; ++t) {
        const sim::Inputs inputs = busy_inputs(t);
        const auto a = plain.advance(inputs);
        const auto spent = session->stats().totalUpdate;
        const auto b = session->run(inputs);
        const double ms = (session->stats().totalUpdate - spent).count() / 1000.0;
        over += ms > kUpdateBudgetMs;
        rounds += b.roundOver;
        if (plain.state_hash() != stressed.state_hash()) {
            check(false, "diverged from a plain match at tick " + std::to_string(t));
            return;
        }
        if (a.soundCues.size() != b.soundCues.size() || a.effectSpawns.size() != b.effectSpawns.size() ||
            a.voiceCues.size() != b.voiceCues.size()) {
            check(false, "the events differ at tick " + std::to_string(t));
            return;
        }
    }
    const auto& stats = session->stats();
    std::printf("humans=%d: %u updates, %u rollbacks, %u replayed ticks, %u desyncs, %.2f ms mean, %.2f ms worst, %u over budget\n", humans,
                stats.updates, stats.rollbacks, stats.replayedTicks, stats.desyncs,
                stats.totalUpdate.count() / 1000.0 / stats.updates, stats.worstUpdate.count() / 1000.0, over);
    check(stats.desyncs == 0, "desync at frame " + std::to_string(stats.firstDesyncFrame));
    check(stats.rollbacks > kTicks / 2, "too few rollbacks to mean anything");
    check(rounds == 1, "the round must end once");
}

// The detection itself: a replay that ends differently has to be caught.
void test_desync_is_caught(const std::string& game) {
    sim::CoreBattle battle;
    battle.start(make_config(game, true), kNoMoves, kNoWeapons);
    const auto session = net::Session::stress(battle, 8);
    for (unsigned t = 0; t < 120; ++t) session->run(busy_inputs(t));
    check(session->stats().desyncs == 0, "a desync before anything was broken");
    session->corrupt_next_hash_for_test();
    for (unsigned t = 120; t < 140; ++t) session->run(busy_inputs(t));
    std::printf("a wrong hash: %u desyncs, first at frame %d\n", session->stats().desyncs, session->stats().firstDesyncFrame);
    check(session->stats().desyncs > 0, "changed state went unnoticed");
}

}  // namespace

int main() {
    const std::string game = find_game();
    if (game.empty()) {
        std::printf("SKIP: no install\n");
        return 77;
    }
    test_desync_is_caught(game);
    test_full_match(game, true);
    test_full_match(game, false);
    if (failures) {
        std::printf("net_stress_test: %d failure(s)\n", failures);
        return 1;
    }
    std::printf("net_stress_test: ok\n");
    return 0;
}
