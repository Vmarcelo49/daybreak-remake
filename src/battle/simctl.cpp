// Headless driver for the vendored simulation: run any roster, optionally with a script, and
// write per-tick traces. Runs at many times real time, with no window, audio or device.
#include "battle/battle.h"
#include "battle/script.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>

namespace {

const char kUsage[] =
    "usage: simctl --roster C:W[:human] x4 [options]\n"
    "  C is a character name or core index, W a weapon slot. Slots 0-1 and 2-3 are teams.\n"
    "  --game DIR     install holding daybreak00.dat (default: $GAME_DIR or a parent directory)\n"
    "  --stage N      stage index (default 1)\n"
    "  --ticks N      updates to run (default 3600)\n"
    "  --seed N       battle RNG seed (default 1)\n"
    "  --time-limit S round time limit in seconds (default: the match's own)\n"
    "  --script FILE  input plan (see src/battle/script.h)\n"
    "  --trace FILE   write one JSON line per tick\n"
    "  --list         print every legal combo and exit\n";

std::string find_game(const std::string& explicitDir) {
    if (!explicitDir.empty()) return explicitDir;
    if (const char* configured = std::getenv("GAME_DIR")) return configured;
    namespace fs = std::filesystem;
    for (auto path = fs::current_path();; path = path.parent_path()) {
        for (const auto& candidate : {path, path / "Higurashi-Daybreak"})
            if (fs::exists(candidate / "daybreak00.dat")) return candidate.string();
        if (path == path.parent_path()) return {};
    }
}

sim::Slot parse_slot(const std::string& text) {
    const auto first = text.find(':');
    if (first == std::string::npos) throw std::invalid_argument("roster entry needs C:W: " + text);
    const std::string name = text.substr(0, first);
    const auto second = text.find(':', first + 1);
    sim::Slot slot;
    slot.weapon = std::stoi(text.substr(first + 1, second - first - 1));
    slot.cpu = second == std::string::npos || text.substr(second + 1) != "human";
    slot.character = -1;
    for (int c = 0; c < sim::character_count(); ++c)
        if (sim::character_name(c) == name) slot.character = c;
    if (slot.character < 0) slot.character = std::stoi(name);
    return slot;
}

void write_trace(std::ostream& out, const sim::Battle& battle) {
    out << "{\"tick\":" << battle.tick() << ",\"phase\":" << battle.scene_phase()
        << ",\"projectiles\":" << battle.live_projectiles() << ",\"actors\":[";
    for (unsigned i = 0; i < 4; ++i) {
        const sim::ActorState a = battle.actor(i);
        out << (i ? "," : "") << "{\"state\":" << a.state << ",\"section\":" << a.phase << ",\"frame\":" << a.frame
            << ",\"hp\":" << a.hp << ",\"gauge\":" << a.gauge << ",\"grounded\":" << (a.grounded ? 1 : 0)
            << ",\"x\":" << a.position[0] << ",\"y\":" << a.position[1] << ",\"z\":" << a.position[2]
            << ",\"heading\":" << a.heading << "}";
    }
    out << "]}\n";
}

}  // namespace

int main(int argc, char** argv) try {
    sim::BattleConfig config;
    std::string gameDir, scriptPath, tracePath;
    unsigned ticks = 3600, rosterCount = 0;
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        const auto value = [&]() -> std::string {
            if (++i >= argc) throw std::invalid_argument(arg + " needs a value");
            return argv[i];
        };
        if (arg == "--list") {
            for (int c = 0; c < sim::character_count(); ++c)
                for (int w = 0; w < sim::weapon_count(c); ++w) std::printf("%s:%d\n", sim::character_name(c).c_str(), w);
            return 0;
        } else if (arg == "--roster") {
            for (; rosterCount < 4; ++rosterCount) config.slots[rosterCount] = parse_slot(value());
        } else if (arg == "--game") gameDir = value();
        else if (arg == "--stage") config.stage = static_cast<unsigned>(std::stoul(value()));
        else if (arg == "--ticks") ticks = static_cast<unsigned>(std::stoul(value()));
        else if (arg == "--seed") config.seed = static_cast<std::uint32_t>(std::stoul(value()));
        else if (arg == "--time-limit") config.timeLimitSeconds = static_cast<unsigned>(std::stoul(value()));
        else if (arg == "--script") scriptPath = value();
        else if (arg == "--trace") tracePath = value();
        else throw std::invalid_argument("unknown argument " + arg);
    }
    if (rosterCount != 4) {
        std::fputs(kUsage, stderr);
        return 2;
    }
    config.gameDir = find_game(gameDir);
    if (config.gameDir.empty()) throw std::runtime_error("no game install found; pass --game or set GAME_DIR");

    std::vector<sim::ScriptSpan> script;
    if (!scriptPath.empty()) {
        std::ifstream in(scriptPath);
        if (!in) throw std::runtime_error("cannot read " + scriptPath);
        script = sim::parse_script(in);
    }
    std::ofstream trace;
    if (!tracePath.empty()) {
        trace.open(tracePath);
        if (!trace) throw std::runtime_error("cannot write " + tracePath);
    }

    sim::Battle battle(config);
    std::set<unsigned> states[4];
    int minHp[4] = {1 << 30, 1 << 30, 1 << 30, 1 << 30};
    for (unsigned t = 0; t < ticks; ++t) {
        battle.step(sim::script_inputs(script, t));
        for (unsigned i = 0; i < 4; ++i) {
            const sim::ActorState a = battle.actor(i);
            states[i].insert(a.state);
            minHp[i] = std::min(minHp[i], a.hp);
        }
        if (trace.is_open()) write_trace(trace, battle);
    }
    std::printf("{\"ticks\":%u,\"hash\":\"%016llx\",\"phase\":%u,\"finished\":%d,\"actors\":[", battle.tick(),
                static_cast<unsigned long long>(battle.hash()), battle.scene_phase(), battle.match_finished() ? 1 : 0);
    for (unsigned i = 0; i < 4; ++i) {
        const sim::Slot& slot = config.slots[i];
        std::printf("%s{\"combo\":\"%s+%d\",\"cpu\":%d,\"minHp\":%d,\"states\":[", i ? "," : "",
                    sim::character_name(slot.character).c_str(), slot.weapon, slot.cpu ? 1 : 0, minHp[i]);
        bool first = true;
        for (unsigned state : states[i]) {
            std::printf("%s%u", first ? "" : ",", state);
            first = false;
        }
        std::printf("]}");
    }
    std::puts("]}");
    return 0;
} catch (const std::exception& error) {
    std::fprintf(stderr, "simctl: %s\n", error.what());
    return 1;
}
