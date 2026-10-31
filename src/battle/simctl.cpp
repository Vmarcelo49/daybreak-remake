// Headless driver for the vendored simulation: run any roster, optionally with a script, and
// write per-tick traces. Runs at many times real time, with no window, audio or device.
#include "battle/battle.h"
#include "battle/debug_tools.h"
#include "battle/script.h"

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
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
    "  --special-mode M every slot's hypermode: 0 Oyashiro, 1 Friendship, 2 Kakera (default 1)\n"
    "  --script FILE  input plan (see src/battle/script.h)\n"
    "  --trace FILE   write one JSON line per tick\n"
    "  --busy         humans press everything, repeatably, instead of a script\n"
    "  --hash-log F   write stateHash per tick, to find where two builds part\n"
    "  --debug-keys K test keys by tick, e.g. f2@0,f4@300 (docs/DEBUG-KEYS.md)\n"
    "  --events FILE  what happened, one line per change: rows, hits, status, new bullets (- for stdout)\n"
    "  --bullets C:W  print the combo's bullets as its data declares them, and exit; names are CP932\n"
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

// Every button in shifting combinations, so a comparison between builds reaches most of the code.
sim::Inputs busy_inputs(unsigned tick) {
    sim::Inputs inputs{};
    for (unsigned i = 0; i < 4; ++i) {
        const unsigned bits = ((tick / (7u + i * 5u)) * 2654435761u + i * 40503u) >> 16;
        inputs[i].x = static_cast<int>(bits & 3u) - 1;
        inputs[i].z = static_cast<int>((bits >> 2) & 3u) - 1;
        if (bits & 0x10u) inputs[i].buttons |= sim::Shoot;
        if (bits & 0x20u) inputs[i].buttons |= sim::Melee;
        if ((bits & 0xc0u) == 0xc0u) inputs[i].buttons |= sim::Jump;
        if ((bits & 0x300u) == 0x300u) inputs[i].buttons |= sim::Guard;
        if ((bits & 0xc00u) == 0xc00u) inputs[i].buttons |= sim::Target;
        if ((bits & 0x3000u) == 0x3000u) inputs[i].buttons |= sim::Tactics;
    }
    return inputs;
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

void print_bullets(const std::string& gameDir, const sim::Slot& combo) {
    for (const sim::BulletInfo& bullet : sim::weapon_bullets(gameDir, combo.character, combo.weapon)) {
        std::printf("%2d mag=%2d reg=%3d model=%-8s %s\n", bullet.slot, bullet.magazine, bullet.registration,
                    bullet.model.c_str(), bullet.name.c_str());
        for (const sim::BulletInfo::Hit& hit : bullet.hits)
            std::printf("     from=%d radius=%d shape=%d damage=%d flags=%#x status=%#x power=%d duration=%d\n", hit.start,
                        hit.extent, hit.shape, hit.damage, hit.flags, hit.status, hit.statusPower, hit.statusDuration);
    }
}

// The changes worth reading from a tick, so a combo's behaviour fits on a screen.
class EventLog {
public:
    explicit EventLog(std::ostream& out) : m_out(out) {}

    void record(const sim::Battle& battle) {
        const unsigned tick = battle.tick() - 1;
        for (unsigned i = 0; i < 4; ++i) {
            const sim::DebugFighter f = battle.debug_fighter(i);
            Seen& seen = m_seen[i];
            if (f.state != seen.state)
                m_out << "t=" << tick << " slot" << i << " row " << seen.state << " -> " << f.state << '\n';
            if (f.hp != seen.hp && m_started)
                m_out << "t=" << tick << " slot" << i << " hp " << seen.hp << " -> " << f.hp << '\n';
            if (f.trapRank != seen.rank && m_started)
                m_out << "t=" << tick << " slot" << i << " trap level " << seen.rank << " -> " << f.trapRank << '\n';
            if (f.special != seen.special && m_started)
                m_out << "t=" << tick << " slot" << i << " hypermode " << (f.special ? "on" : "off") << '\n';
            for (size_t s = 0; s < f.status.size(); ++s)
                if ((f.status[s] != 0) != (seen.status[s] != 0) && m_started)
                    m_out << "t=" << tick << " slot" << i << " status " << s << (f.status[s] ? " on for " : " off")
                          << (f.status[s] ? std::to_string(f.status[s]) : "") << '\n';
            seen = {f.state, f.hp, f.trapRank, f.special, f.status};
        }
        std::map<std::array<int, 3>, int> live;
        battle.for_each_projectile([&](const sim::ProjectileState& shot) { ++live[{shot.owner, shot.item, shot.row}]; });
        for (const auto& [key, count] : live) {
            const auto before = m_live.find(key);
            if (before == m_live.end() || count > before->second)
                m_out << "t=" << tick << " slot" << key[0] << " bullet " << key[1] << ':' << key[2] << " live=" << count << '\n';
        }
        m_live = std::move(live);
        m_started = true;
    }

private:
    struct Seen {
        unsigned state = ~0u;
        int hp = 0, rank = 0;
        bool special = false;
        std::array<int, 8> status{};
    };
    std::ostream& m_out;
    std::array<Seen, 4> m_seen{};
    std::map<std::array<int, 3>, int> m_live;
    bool m_started = false;
};

}  // namespace

int main(int argc, char** argv) try {
    sim::BattleConfig config;
    std::string gameDir, scriptPath, tracePath, hashLogPath, eventsPath;
    std::vector<sim::ScheduledKey> debugKeys;
    bool listBullets = false;
    sim::Slot bulletsCombo;
    bool busy = false;
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
            for (; rosterCount < 4; ++rosterCount) {
                const unsigned mode = config.slots[rosterCount].specialMode;
                config.slots[rosterCount] = parse_slot(value());
                config.slots[rosterCount].specialMode = mode;
            }
        } else if (arg == "--game") gameDir = value();
        else if (arg == "--stage") config.stage = static_cast<unsigned>(std::stoul(value()));
        else if (arg == "--ticks") ticks = static_cast<unsigned>(std::stoul(value()));
        else if (arg == "--seed") config.seed = static_cast<std::uint32_t>(std::stoul(value()));
        else if (arg == "--time-limit") config.timeLimitSeconds = static_cast<unsigned>(std::stoul(value()));
        else if (arg == "--special-mode") {
            const unsigned mode = static_cast<unsigned>(std::stoul(value()));
            for (sim::Slot& slot : config.slots) slot.specialMode = mode;
        } else if (arg == "--script") scriptPath = value();
        else if (arg == "--trace") tracePath = value();
        else if (arg == "--busy") busy = true;
        else if (arg == "--hash-log") hashLogPath = value();
        else if (arg == "--debug-keys") debugKeys = sim::parse_debug_keys(value());
        else if (arg == "--events") eventsPath = value();
        else if (arg == "--bullets") { bulletsCombo = parse_slot(value()); listBullets = true; }
        else throw std::invalid_argument("unknown argument " + arg);
    }
    if (rosterCount != 4 && !listBullets) {
        std::fputs(kUsage, stderr);
        return 2;
    }
    config.gameDir = find_game(gameDir);
    if (config.gameDir.empty()) throw std::runtime_error("no game install found; pass --game or set GAME_DIR");
    if (listBullets) {
        print_bullets(config.gameDir, bulletsCombo);
        return 0;
    }

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

    std::ofstream hashLog;
    if (!hashLogPath.empty()) {
        hashLog.open(hashLogPath);
        if (!hashLog) throw std::runtime_error("cannot write " + hashLogPath);
    }

    std::ofstream eventsFile;
    if (!eventsPath.empty() && eventsPath != "-") {
        eventsFile.open(eventsPath);
        if (!eventsFile) throw std::runtime_error("cannot write " + eventsPath);
    }
    std::optional<EventLog> events;
    if (!eventsPath.empty()) events.emplace(eventsPath == "-" ? std::cout : eventsFile);

    sim::Battle battle(config);
    std::set<unsigned> states[4];
    int minHp[4] = {1 << 30, 1 << 30, 1 << 30, 1 << 30};
    for (unsigned t = 0; t < ticks; ++t) {
        battle.step(busy ? busy_inputs(t) : sim::script_inputs(script, t));
        const unsigned keys = sim::debug_keys_at(debugKeys, t);
        battle.apply_debug_keys(keys);
        if (keys & sim::DebugReport)
            for (unsigned i = 0; i < 4; ++i) std::cout << sim::debug_report(battle, i) << '\n';
        if (events) events->record(battle);
        for (unsigned i = 0; i < 4; ++i) {
            const sim::ActorState a = battle.actor(i);
            states[i].insert(a.state);
            minHp[i] = std::min(minHp[i], a.hp);
        }
        if (trace.is_open()) write_trace(trace, battle);
        if (hashLog.is_open()) hashLog << t << ' ' << battle.stateHash() << '\n';
    }
    std::printf("{\"state_hash\":\"%016llx\",\"ticks\":%u,\"hash\":\"%016llx\",\"phase\":%u,\"finished\":%d,\"actors\":[", static_cast<unsigned long long>(battle.stateHash()), battle.tick(),
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
