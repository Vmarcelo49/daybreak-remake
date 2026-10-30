// Random-input stress for one combo (docs/DIRECTION.md, M2): checks invariants every tick and
// reports which of the combo's declared rows were reached. One JSON object on stdout; run per
// combo through scripts/sim_trust.py. Same arguments, same result.
#include "battle/battle.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <map>
#include <random>
#include <set>
#include <string>
#include <vector>

namespace {

// Thresholds are suspicion levels, not recovered limits: a hit is something to read, not
// automatically a defect.
constexpr unsigned kStuckRowTicks = 1800;   // 30 s in one row that is not standing or walking
constexpr unsigned kFrozenClockTicks = 600; // 10 s with row, section and clock all unchanged
constexpr float kWorldBound = 200000.f;
constexpr int kMaxReports = 12;

struct Report {
    std::string kind;
    unsigned seed, tick, slot, row;
    double value;
};

// One fuzzed controller: holds a direction and a button set for a random span. Weighted so
// that presses, holds, chords and dash double-taps all happen, none dominating.
class Fuzzer {
public:
    explicit Fuzzer(std::uint32_t seed) : m_random(seed) {}
    sim::SlotInput next() {
        if (m_left == 0) pick();
        --m_left;
        return m_current;
    }

private:
    int roll(int low, int high) { return std::uniform_int_distribution<int>(low, high)(m_random); }
    void pick() {
        sim::SlotInput input;
        const int shape = roll(0, 99);
        if (shape < 25) {
            m_left = static_cast<unsigned>(roll(1, 6));   // taps, including direction double-taps
        } else if (shape < 80) {
            m_left = static_cast<unsigned>(roll(6, 40));
        } else {
            m_left = static_cast<unsigned>(roll(40, 240));  // long holds reach charges and guards
        }
        if (roll(0, 99) < 65) {
            input.x = roll(-1, 1);
            input.z = roll(-1, 1);
        }
        for (const unsigned button : {sim::Jump, sim::Melee, sim::Shoot, sim::Target, sim::Guard})
            if (roll(0, 99) < (button == sim::Target ? 3 : 18)) input.buttons |= button;
        m_current = input;
    }
    std::mt19937 m_random;
    sim::SlotInput m_current;
    unsigned m_left = 0;
};

struct Watch {
    unsigned row = ~0u, section = ~0u, frame = ~0u, rowTicks = 0, clockTicks = 0;
};

std::string find_game() {
    namespace fs = std::filesystem;
    if (const char* configured = std::getenv("GAME_DIR")) return configured;
    for (auto path = fs::current_path();; path = path.parent_path()) {
        for (const auto& candidate : {path, path / "Higurashi-Daybreak"})
            if (fs::exists(candidate / "daybreak00.dat")) return candidate.string();
        if (path == path.parent_path()) return {};
    }
}

}  // namespace

int main(int argc, char** argv) {
    if (argc < 5) {
        std::fputs("usage: simfuzz CHARACTER WEAPON RUNS TICKS [FIRST_SEED [DUMP_FROM DUMP_TO]]\n", stderr);
        return 2;
    }
    const int character = std::atoi(argv[1]), weapon = std::atoi(argv[2]);
    const unsigned runs = static_cast<unsigned>(std::atoi(argv[3])), ticks = static_cast<unsigned>(std::atoi(argv[4]));
    const unsigned firstSeed = argc > 5 ? static_cast<unsigned>(std::atoi(argv[5])) : 1;
    // Replaying a report: per-tick state on stderr, with the inputs that produced it.
    const unsigned dumpFrom = argc > 7 ? static_cast<unsigned>(std::atoi(argv[6])) : ~0u;
    const unsigned dumpTo = argc > 7 ? static_cast<unsigned>(std::atoi(argv[7])) : 0;
    const std::string game = find_game();
    if (game.empty()) {
        std::fputs("simfuzz: no game install\n", stderr);
        return 77;
    }

    std::set<unsigned> reached;
    std::set<std::pair<unsigned, unsigned>> edges;
    unsigned longestRoll = 0;           // row 124's section 1, in ticks
    float rollStepMin = 1e9f, rollStepMax = 0.f;
    std::vector<unsigned> declared;
    std::map<std::string, unsigned> counts;
    std::vector<Report> reports;
    const auto report = [&](const std::string& kind, unsigned seed, unsigned tick, unsigned slot, unsigned row, double value) {
        if (counts[kind]++ == 0 || static_cast<int>(reports.size()) < kMaxReports) reports.push_back({kind, seed, tick, slot, row, value});
    };
    unsigned long long totalTicks = 0;
    unsigned finished = 0;
    std::string fatal;

    for (unsigned run = 0; run < runs; ++run) {
        const unsigned seed = firstSeed + run;
        // Vary the opposition by seed: fuzzed humans on both teams, CPU partners.
        sim::BattleConfig config;
        config.gameDir = game;
        config.seed = seed;
        config.stage = 1 + seed % 6;
        std::mt19937 rosterRandom(seed * 7919u + static_cast<unsigned>(character * 3 + weapon));
        const auto other = [&](bool cpu) {
            const int c = std::uniform_int_distribution<int>(0, sim::character_count() - 1)(rosterRandom);
            const int w = std::uniform_int_distribution<int>(0, sim::weapon_count(c) - 1)(rosterRandom);
            return sim::Slot{c, w, cpu};
        };
        config.slots = {sim::Slot{character, weapon, false}, other(true), other(false), other(true)};
        Fuzzer fuzz0(seed * 2 + 1), fuzz2(seed * 2 + 2);
        std::array<Watch, 4> watch{};
        std::array<int, 4> startHp{};
        unsigned previousRow = ~0u, rollTicks = 0;
        std::array<float, 3> previousPosition{};
        unsigned tick = 0;
        try {
            sim::Battle battle(config);
            if (declared.empty()) declared = battle.declared_rows(0);
            for (unsigned slot = 0; slot < 4; ++slot) startHp[slot] = battle.actor(slot).hp;
            for (; tick < ticks && !battle.match_finished(); ++tick) {
                sim::Inputs inputs{};
                inputs[0] = fuzz0.next();
                inputs[2] = fuzz2.next();
                battle.step(inputs);
                ++totalTicks;
                if (tick >= dumpFrom && tick < dumpTo)
                    for (unsigned slot = 0; slot < 4; ++slot) {
                        const sim::ActorState a = battle.actor(slot);
                        std::fprintf(stderr, "%u s%u row=%u sec=%u frame=%u hp=%d gauge=%d gr=%d pos=%.1f,%.1f,%.1f in=%d,%d,%u\n", tick,
                                     slot, a.state, a.phase, a.frame, a.hp, a.gauge, a.grounded ? 1 : 0, a.position[0],
                                     a.position[1], a.position[2], inputs[slot].x, inputs[slot].z, inputs[slot].buttons);
                    }
                const bool live = battle.scene_phase() == 2;
                for (unsigned slot = 0; slot < 4; ++slot) {
                    const sim::ActorState a = battle.actor(slot);
                    if (slot == 0) {
                        reached.insert(a.state);
                        if (previousRow != ~0u && previousRow != a.state) edges.insert({previousRow, a.state});
                        // The first tick of a section still carries the previous one's speed.
                        const bool rolling = a.state == 124 && a.phase == 1;
                        if (rolling && rollTicks > 0 && a.grounded) {
                            const float dx = a.position[0] - previousPosition[0], dz = a.position[2] - previousPosition[2];
                            const float step = std::sqrt(dx * dx + dz * dz);
                            rollStepMin = std::min(rollStepMin, step);
                            rollStepMax = std::max(rollStepMax, step);
                        }
                        rollTicks = rolling ? rollTicks + 1 : 0;
                        longestRoll = std::max(longestRoll, rollTicks);
                        previousRow = a.state;
                        previousPosition = a.position;
                    }
                    bool finite = std::isfinite(a.heading);
                    for (float axis : a.position) finite = finite && std::isfinite(axis);
                    if (!finite) report("non_finite", seed, tick, slot, a.state, 0);
                    else if (std::fabs(a.position[0]) > kWorldBound || std::fabs(a.position[2]) > kWorldBound ||
                             std::fabs(a.position[1]) > kWorldBound)
                        report("out_of_world", seed, tick, slot, a.state, a.position[1]);
                    if (a.hp < 0 || a.hp > startHp[slot]) report("hp_range", seed, tick, slot, a.state, a.hp);
                    if (a.gauge < 0 || a.gauge > 1000) report("gauge_range", seed, tick, slot, a.state, a.gauge);
                    Watch& w = watch[slot];
                    w.rowTicks = a.state == w.row ? w.rowTicks + 1 : 0;
                    const bool sameClock = a.state == w.row && a.phase == w.section && a.frame == w.frame;
                    w.clockTicks = sameClock ? w.clockTicks + 1 : 0;
                    w.row = a.state;
                    w.section = a.phase;
                    w.frame = a.frame;
                    if (!live || a.hp <= 0) continue;
                    const bool ordinary = a.state == 0 || a.state == 10;
                    if (!ordinary && w.rowTicks == kStuckRowTicks) report("stuck_row", seed, tick, slot, a.state, w.rowTicks);
                    if (!ordinary && w.clockTicks == kFrozenClockTicks) report("frozen_clock", seed, tick, slot, a.state, a.frame);
                }
            }
            if (battle.match_finished()) ++finished;
        } catch (const std::exception& error) {
            ++counts["exception"];
            fatal = error.what();
            reports.push_back({"exception:" + fatal, seed, tick, 0, 0, 0});
        }
    }

    std::printf("{\"combo\":\"%s+%d\",\"character\":%d,\"weapon\":%d,\"runs\":%u,\"ticks\":%llu,\"finished\":%u,\"counts\":{",
                sim::character_name(character).c_str(), weapon, character, weapon, runs, totalTicks, finished);
    bool first = true;
    for (const auto& entry : counts) {
        std::printf("%s\"%s\":%u", first ? "" : ",", entry.first.c_str(), entry.second);
        first = false;
    }
    std::printf("},\"reports\":[");
    for (size_t i = 0; i < reports.size(); ++i) {
        std::string kind;
        for (char c : reports[i].kind) if (c != '"' && c != '\\') kind += c;
        std::printf("%s{\"kind\":\"%s\",\"seed\":%u,\"tick\":%u,\"slot\":%u,\"row\":%u,\"value\":%g}", i ? "," : "",
                    kind.c_str(), reports[i].seed, reports[i].tick, reports[i].slot, reports[i].row, reports[i].value);
    }
    std::printf("],\"roll\":{\"longest\":%u,\"stepMin\":%g,\"stepMax\":%g},\"edges\":[", longestRoll, rollStepMin, rollStepMax);
    first = true;
    for (const auto& edge : edges) {
        std::printf("%s[%u,%u]", first ? "" : ",", edge.first, edge.second);
        first = false;
    }
    std::printf("],\"declared\":[");
    for (size_t i = 0; i < declared.size(); ++i) std::printf("%s%u", i ? "," : "", declared[i]);
    std::printf("],\"reached\":[");
    first = true;
    for (unsigned row : reached) {
        std::printf("%s%u", first ? "" : ",", row);
        first = false;
    }
    std::puts("]}");
    return 0;
}
