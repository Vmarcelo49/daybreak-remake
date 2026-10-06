// gameplay/debug_keys.cpp — the five in-battle debug keys' effects. See debug_keys.h for the
// recovered map (FUN_00634f60's line ranges, the DIK codes and the gate) and for the two port
// rules; this TU is only the order and the writes.
#include "gameplay/debug_keys.h"

#include <cstdio>
#include <cstdlib>

namespace gameplay {
namespace {

// The ownership invariant F3 must not break, checked in EVERY build: `assert` compiles out
// under NDEBUG (the Linux/Windows release builds), and a human slot silently handed to the
// AI is a player losing control of their own fighter — worth stopping the run for.
[[noreturn]] void violated(const char* what) {
    std::fprintf(stderr, "[daybreak] debug keys: invariant violated: %s\n", what);
    std::abort();
}

}  // namespace

bool applyDebugKeys(Match& match, const DebugKeysHeld& keys, const bool comOwned[4],
                    bool enabled) {
    if (!enabled) return false;

    // Escape first, exactly where the original reads it (FUN_00634f60:50-52): it is a leave
    // REQUEST, not a simulation write, so the host resolves it through the same path the pause
    // menu's "return to selection" uses.
    const bool leave = keys.escape;

    // FUN_00634f60 loops the four fixed slots, so the key set touches all four whatever the
    // match's fighter count is; a 1v1's unused slots hold default state and nothing steps them.
    if (keys.f2) {
        // :148-155 — all four, unconditionally: the recovered write is not ownership-tested.
        // It does not need to be, because the flag has exactly one reader in this port (the
        // host's COM-input build) and that reader only runs for a slot no controller owns.
        for (int i = 0; i < 4; ++i) match.set_ai_enabled(i, false);
    }

    if (keys.f3) {
        // :156-170 — `3 < DAT_006cfaf8…`: only a genuinely COM-controlled slot is re-enabled.
        bool before[4];
        for (int i = 0; i < 4; ++i) before[i] = match.ai_enabled(i);
        for (int i = 0; i < 4; ++i) {
            if (comOwned[i]) match.set_ai_enabled(i, true);
        }
        for (int i = 0; i < 4; ++i) {
            if (!comOwned[i] && match.ai_enabled(i) != before[i])
                violated("F3 moved a human slot's AI flag");
        }
    }

    if (keys.f1) {
        // :171-183 — the two scene counters ARE the per-side balloon percentages
        // (scene+0x12b0/+0x12bc), and then max HP and HP are both written 10000, which in this
        // port's units is the fighter's own full capacity.
        match.economy().reset_balloons();
        for (int i = 0; i < 4; ++i) match.fighter(i).restore_full_hp();
    }

    if (keys.f4) {
        // :184-204 — one gauge per fighter in the original, chosen by its +0x318 byte; the
        // port carries no selector, so every meter it models is filled (debug_keys.h, port
        // rule 2, names the arm each meter corresponds to).
        for (int i = 0; i < 4; ++i) match.fighter(i).fill_gauges();
    }

    return leave;
}

}  // namespace gameplay
