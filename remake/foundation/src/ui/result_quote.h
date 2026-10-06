#pragma once
// ui/result_quote.h — which victory script and voice a round ends on.
//
// WHY this is a separate, device-free derivation: the original's choice is a small, fully
// recovered rule over the round's outcome and the winning side's two selections
// (FUN_00635d40 @0x636d7a-0x636e0a, plus the persona gate FUN_00409340:180-186), and every
// screen and test should get the same answer without a GPU.
//
// The recovered rule, in the original's own order:
//   1. Persona substitution. A winner whose character is 0 (Rena) or 4 (Rika) AND whose
//      weapon slot is 2 reads the alternate persona: script id 16 resp. 17, and the 'b'
//      winner art (data/win/%02db) instead of data/win/%02da (FUN_00635d40:255-273; the same
//      pair is what selects the B-variant entry voice in FUN_00409340:180-186).
//   2. The pair is sorted (min,max) and the file is data/scenario/win/<min>-<max>-<grade>.txt.
//   3. The grade 1..4 is the round's margin: min(winnerCapacity, loserBalloon) - winnerBalloon
//      < 30 -> 3 (4 when BOTH winners ended below half HP), < 50 -> 2, else 1
//      (FUN_00635d40:288-318). The values are balloon percentages, the units the balloon and
//      the LIMIT setting share.
//   4. When that pair script does not load, the original falls back to a SINGLE script: the
//      one belonging to whichever of the two ids is 16 or 17, else 17 (FUN_00635d40:323-346).
//      The shipped tree has exactly two single scripts, 16.txt and 17.txt, and no pair file
//      for 29 of the 16/17 combinations — this is the branch those gaps need.
//
// A file holds SEVERAL VOICE/quote alternatives (00-01-1.txt has two, 16.txt three); the
// original picks one with `rand % (entries)` (FUN_00635d40:347-353). The port's pick is
// deterministic per round (see resultQuoteEntryIndex) so captures reproduce.
#include <cstdint>
#include <string>
#include <vector>

namespace ui {

// One VOICE/quote alternative from a win script.
struct ResultQuoteEntry {
    std::string voice;   // the VOICE directive's file name, e.g. "W00-01-1.wav"
    std::string text;    // the quote line, colour escapes included
};

// Every alternative in a win script, in file order. Empty when the file has no quote line.
std::vector<ResultQuoteEntry> parseResultQuotes(const std::string& utf8);

// Which alternative a round uses. The original's `rand % entries`; the port seeds it from the
// round (side + frame) so a capture and a replay pick the same line.
int resultQuoteEntryIndex(int entries, int winnerSide, uint64_t matchFrame);

// FUN_00635d40:255-273 + FUN_00409340:180-186: the persona id for one winner, or its own
// character index when it has no persona variant.
inline int resultPersonaId(int character, int weapon) {
    if (character == 0 && weapon == 2) return 16;
    if (character == 4 && weapon == 2) return 17;
    return character;
}

// FUN_00635d40:288-318: the outcome grade, from the margin and the winners' HP. `margin` is
// min(winnerCapacity, loserBalloon) - winnerBalloon, in balloon percentage points.
inline int resultOutcomeGrade(int margin, bool winnersBelowHalfHp) {
    if (margin < 30) return winnersBelowHalfHp ? 4 : 3;
    return margin < 50 ? 2 : 1;
}

// FUN_00635d40:323-346: the single script to use when the pair script is missing.
inline int resultFallbackSingleId(int pairA, int pairB) {
    const int lo = pairA < pairB ? pairA : pairB;
    const int hi = pairA < pairB ? pairB : pairA;
    if (lo < 0x10) return hi == 0x10 ? 0x10 : 0x11;
    if (lo == 0x11) return 0x11;
    if (hi == 0x10) return 0x10;
    return 0x11;
}

// One winning slot as the quote rule sees it.
struct WinnerSlot {
    int character = -1;   // roster index, or the persona id already substituted
    int weapon = 0;
    bool persona = false; // the 'b' art and the persona id apply
};

struct WinnerQuotePlan {
    WinnerSlot winners[2];                 // slot 0/1 in panel order, persona substituted
    int pairA = -1, pairB = -1;            // sorted ids used in the file name
    int grade = 1;
    // Files to try in order: the pair script, then the recovered single-script fallback.
    // `pairScript` and `fallbackScript` are the same paths, kept apart so callers can log
    // which one answered.
    std::string pairScript, fallbackScript;
};

// FUN_00635d40:255-273 loads one winner sheet per winning slot, so the art a side needs is
// one portrait per MEMBER (a 2v2 shows both winners, a one-member side shows its one) — not
// the two slots the quote pair always fills. Capped at the original's two slots.
inline int winnerPortraitCount(int memberCount) {
    if (memberCount <= 0) return 0;
    return memberCount > 2 ? 2 : memberCount;
}

// Builds the plan for a winning side. `characters`/`weapons` are the side's slots in panel
// order; a one-member side (the port's 1v1) repeats that member, which is the documented port
// rule — the original always has two fighters per side, and every character ships a self-pair
// script (00-00-1..4 .. 15-15-1..4), so the repeated pair is a real shipped script.
WinnerQuotePlan planWinnerQuote(const int characters[2], const int weapons[2], int memberCount,
                                int margin, bool winnersBelowHalfHp);

// Formats data/scenario/win/<a>-<b>-<grade>.txt.
std::string resultPairScriptPath(int a, int b, int grade);
// Formats data/scenario/win/<id>.txt.
std::string resultSingleScriptPath(int id);

}  // namespace ui
