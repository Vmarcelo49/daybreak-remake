#pragma once
// gameplay/result_title.h — the earned title a fighter's round earns.
//
// WHY: the original's report draws one earned title per participant, composed from the four
// fighters' own battle records into one text texture and drawn line by line
// (FUN_00635d40:372-391 composes, FUN_0063a740:64-85 draws row i). The names are a 41-entry
// string table at VA 0x6b7308 (FUN_00430860 returns one), and FUN_00430880 @0x430880 picks the
// index from the fighter's record at fighter+0xaedc.
//
// The record's fields, and the writer each one was read from:
//   +0x04 own team's balloon capacity      FUN_00634980 (round init)
//   +0x08 the opponents' capacity          FUN_00634980
//   +0x0c capacity - balloon               FUN_00635d40 (round end): < 1 means this fighter
//                                          was out of budget (KO'd), which is the chain's
//                                          branch selector
//   +0x10/+0x14 damage dealt to the fighter's own locked target / to others   FUN_00639160,
//   +0x18/+0x1c damage taken from its locked target / from others             FUN_00637950
//   +0x24/+0x28 hits taken from its locked target / from others               FUN_00423000,
//   +0x2c/+0x30 hits dealt to a mutually locked fighter / to others           FUN_004230e0
//   +0x34 hits this fighter landed on the LOCAL (1P) fighter's fighter
//   +0x38 shot hits landed, +0x3c melee hits landed (FUN_004230e0 / FUN_00423000)
//   +0x40/+0x44 damage events dealt to its locked target / to others          FUN_00639160,
//   +0x4c/+0x50 damage events taken from its locked target / from others      FUN_00637950
// Damage is in balloon percentage points, the unit the capacity shares (FUN_00639160 scales
// the blow by the capacity before crediting it), so the chain's `capacity * N / 100` thresholds
// are percentages of a full balloon.
//
// NOT RECOVERED, and therefore never guessed: the fields +0x20, +0x48, +0x54, +0x58, +0x5c,
// +0x60, +0x64, +0x68, +0x6c, +0x70, +0x74, +0x78 and the +0x7c/+0x80 frame pair. Every
// condition that reads one is marked UNRESOLVED below; when the chain reaches one,
// resultTitleIndex reports `resolved = false` and returns the chain's OWN final fallback (the
// same index the original reaches when nothing matches) instead of inventing a title. The
// caller is expected to log that, and docs/ROADMAP-PENDING.md lists the blocked conditions.
#include <cstdint>
#include <string>
#include <vector>

namespace gameplay {

// The title the original grants for the "penalty game" (index 0x28): every branch rolls for it
// with a small percentage, and earning it sets a session flag (FUN_00635d40:377-380).
inline constexpr int kResultTitlePenalty = 40;
inline constexpr int kResultTitleFallback = 26;   // 0x1a: the chain's own final return
inline constexpr int kResultTitleCount = 41;

// One fighter's battle record, in the fields this port can fill. Everything is an int; the
// original's two float accumulators are unresolved and absent on purpose.
struct ResultRecord {
    int teamCapacity = 0;      // +0x04
    int enemyCapacity = 0;     // +0x08
    bool koed = false;         // +0x0c < 1 (the port maps the economy's per-fighter KO clock)
    int damageToTarget = 0;    // +0x10
    int damageToOthers = 0;    // +0x14
    int damageFromTarget = 0;  // +0x18
    int damageFromOthers = 0;  // +0x1c
    int hitsFromTarget = 0;    // +0x24
    int hitsFromOthers = 0;    // +0x28
    int hitsToTarget = 0;      // +0x2c
    int hitsToOthers = 0;      // +0x30
    int hitsOnLocalPlayer = 0; // +0x34
    int shotHits = 0;          // +0x38
    int meleeHits = 0;         // +0x3c
    int eventsToTarget = 0;    // +0x40
    int eventsToOthers = 0;    // +0x44
    int eventsFromTarget = 0;  // +0x4c
    int eventsFromOthers = 0;  // +0x50

    int damageDealt() const { return damageToTarget + damageToOthers; }
    int damageTaken() const { return damageFromTarget + damageFromOthers; }
    int hitsDealt() const { return hitsToTarget + hitsToOthers; }
    int hitsTaken() const { return hitsFromTarget + hitsFromOthers; }
    int eventsDealt() const { return eventsToTarget + eventsToOthers; }
    int eventsTaken() const { return eventsFromTarget + eventsFromOthers; }
};

// FUN_00430880 @0x430880. `rng` is the caller's random state for the branches that roll for
// the penalty title (the original calls FUN_0065d150 there). `resolved` is false when the
// chain reached a condition whose field is not recovered; the returned index is then the
// chain's own fallback, not a claim about the original's answer.
int resultTitleIndex(const ResultRecord& record, uint32_t& rng, bool* resolved = nullptr);

// The recovered name table (VA 0x6b7308, 41 entries). Loaded from the installed exe so the
// game's own text stays out of this repository (assets/exe_strings.h).
struct ResultTitleTable {
    std::vector<std::string> titles;
    bool loaded() const { return titles.size() == (size_t)kResultTitleCount; }
    const char* text(int index) const {
        return index >= 0 && index < (int)titles.size() ? titles[(size_t)index].c_str() : "";
    }
};

// `exePath` is the installed DaybreakDX.exe.
bool loadResultTitles(const std::string& exePath, ResultTitleTable& out, std::string& error);

}  // namespace gameplay
