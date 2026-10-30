#include "frontend/result_quote.h"

#include <algorithm>
#include <cstdio>
#include <sstream>

namespace ui {

std::vector<ResultQuoteEntry> parseResultQuotes(const std::string& utf8) {
    std::vector<ResultQuoteEntry> entries;
    std::istringstream lines(utf8);
    std::string line;
    ResultQuoteEntry current;
    bool haveVoice = false;
    while (std::getline(lines, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty() || line[0] == '#') continue;
        if (line.compare(0, 6, "VOICE ") == 0 || line.compare(0, 6, "voice ") == 0) {
            // A new alternative starts at each VOICE directive; the previous one is complete
            // once its quote line has been seen.
            if (haveVoice && !current.text.empty()) entries.push_back(current);
            current = ResultQuoteEntry{};
            current.voice = line.substr(6);
            haveVoice = true;
            continue;
        }
        if (current.text.empty()) current.text = line;
    }
    if (haveVoice && !current.text.empty()) entries.push_back(current);
    return entries;
}

int resultQuoteEntryIndex(int entries, int winnerSide, uint64_t matchFrame) {
    if (entries <= 0) return -1;
    // Deterministic stand-in for the original's `rand % entries` (FUN_00635d40:347-353): the
    // round's own numbers, so a capture and a replay pick the same alternative.
    const uint64_t mixed = matchFrame * 6364136223846793005ull + (uint64_t)(winnerSide + 1) * 1442695040888963407ull;
    return (int)((mixed >> 33) % (uint64_t)entries);
}

std::string resultPairScriptPath(int a, int b, int grade) {
    char path[96];
    std::snprintf(path, sizeof(path), "data/scenario/win/%02d-%02d-%d.txt", a, b, grade);
    return path;
}

std::string resultSingleScriptPath(int id) {
    char path[64];
    std::snprintf(path, sizeof(path), "data/scenario/win/%02d.txt", id);
    return path;
}

WinnerQuotePlan planWinnerQuote(const int characters[2], const int weapons[2], int memberCount,
                                int margin, bool winnersBelowHalfHp) {
    WinnerQuotePlan plan;
    const int members = std::clamp(memberCount, 1, 2);
    for (int i = 0; i < 2; ++i) {
        // A one-member side repeats its member: the port's 1v1 (documented port rule — the
        // original always fields two per side, and the self-pair scripts ship).
        const int source = members == 1 ? 0 : i;
        WinnerSlot& slot = plan.winners[i];
        slot.character = resultPersonaId(characters[source], weapons[source]);
        slot.weapon = weapons[source];
        slot.persona = slot.character != characters[source];
    }
    const int lo = std::min(plan.winners[0].character, plan.winners[1].character);
    const int hi = std::max(plan.winners[0].character, plan.winners[1].character);
    plan.pairA = lo;
    plan.pairB = hi;
    plan.grade = resultOutcomeGrade(margin, winnersBelowHalfHp);
    plan.pairScript = resultPairScriptPath(lo, hi, plan.grade);
    plan.fallbackScript = resultSingleScriptPath(resultFallbackSingleId(lo, hi));
    return plan;
}

}  // namespace ui
