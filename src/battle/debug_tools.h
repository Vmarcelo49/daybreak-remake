#pragma once
// What simctl and the game share for debugging a battle: scheduled test keys and the state report.
#include "battle/battle.h"

#include <cstdio>
#include <stdexcept>
#include <string>
#include <vector>

namespace sim {

struct ScheduledKey {
    unsigned tick = 0, key = 0;
};

// "f2@0,f4@300": keys by name, each held for the one tick after that tick's update.
inline std::vector<ScheduledKey> parse_debug_keys(const std::string& text) {
    std::vector<ScheduledKey> keys;
    for (size_t at = 0; at < text.size();) {
        size_t end = text.find(',', at);
        if (end == std::string::npos) end = text.size();
        const std::string item = text.substr(at, end - at);
        at = end + 1;
        unsigned number = 0, tick = 0;
        if (std::sscanf(item.c_str(), "f%u@%u", &number, &tick) != 2 || number < 1 || number > 6)
            throw std::invalid_argument("debug key '" + item + "': expected f1..f6@tick");
        keys.push_back({tick, 1u << (number - 1)});
    }
    return keys;
}

inline unsigned debug_keys_at(const std::vector<ScheduledKey>& keys, unsigned tick) {
    unsigned held = 0;
    for (const ScheduledKey& key : keys)
        if (key.tick == tick) held |= key.key;
    return held;
}

inline std::string debug_report(const Battle& battle, unsigned slot) {
    const DebugFighter f = battle.debug_fighter(slot);
    char line[256];
    std::snprintf(line, sizeof line,
                  "t=%u slot=%u %s+%d row=%u/%u/%u hp=%d gauge=%d cpu=%d hyper=%d %d/%d rounds=%d,%d trap=%d(%d) status=",
                  battle.tick(), slot, character_name(f.character).c_str(), f.weapon, f.state, f.phase, f.frame, f.hp,
                  f.gauge, f.cpu ? 1 : 0, f.special ? 1 : 0, f.specialCharge, f.specialLimit, f.rounds[0], f.rounds[1],
                  f.trapRank, f.trapRankTimer);
    std::string out = line;
    for (size_t i = 0; i < f.status.size(); ++i) out += (i ? "," : "") + std::to_string(f.status[i]);
    return out;
}

}  // namespace sim
