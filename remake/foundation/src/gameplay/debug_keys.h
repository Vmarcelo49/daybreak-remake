#pragma once
// gameplay/debug_keys.h — the original's in-battle debug keys (issue #48), device-free.
//
// RECOVERED, not invented. All five keys live in FUN_00634f60 (the battle scene's per-frame
// update) and read key STATE through FUN_006586d0(dik), so the codes below are DirectInput
// scancodes:
//
//   key     DIK    recovered effect (FUN_00634f60)
//   Escape  0x01   :50-52   scene+0x4a40 = 1 — the battle's leave/abort flag
//   F2      0x3c   :148-155 [fighter+0x860] = 0 for all four slots — the COM/AI enable flag,
//                           which is what stops a COM moving and attacking
//   F3      0x3d   :156-170 [fighter+0x860] = 1, but ONLY where `3 < DAT_006cfaf8/fafc/
//                           fb00/fb04` (the per-slot controller/type array): a human slot is
//                           never handed to the AI by this key
//   F1      0x3b   :171-183 scene+0x12b0 = 0 and scene+0x12bc = 0 (the two sides' balloon
//                           percentages), then +0x7a8 = +0x7a4 = 10000 for all four fighters
//                           (max HP and HP — the full-HP restore)
//   F4      0x3e   :184-204 every fighter's gauge, selected by its per-slot byte
//                           [fighter+0x318]: 1 -> +0x83c = +0x32c, 2 -> +0x840 = +0x324,
//                           otherwise -> +0x838 = +0x324
//
// The gate is `if (DAT_006cfce9 == '\0') { ... }`, and DAT_006cfce9 is written by the title
// screen's item switch (FUN_00410f60:105-120): item 0 (story) sets 1, item 1 (versus) sets 0,
// every other item sets 0. The keys are therefore live in a non-story battle and dead in
// story mode.
//
// PORT RULES (the two places this port cannot be the original):
//
// 1. The gate. The port has no story mode, so "always active in a battle" is the faithful
//    equivalent: the host samples these keys only where a battle ticks. The port's own
//    --no-debug-keys switch is an extra, deliberately NOT the recovered gate: it exists so an
//    evidence run that DOES read physical devices cannot have a stray F-key move it. It is
//    passed in as `enabled` so the rule lives in one place (see applyDebugKeys).
// 2. F4's selector. The original picks ONE of three gauges per fighter from the per-slot byte
//    +0x318 (written at load by FUN_0064ab30 from scene+0x5328, via FUN_0041dc80). The port
//    carries no such selector, so the key fills every meter the port models — the MAIN and
//    CHARGE stocks and the hypermode gauge — which is the union of the original's three arms.
//    The mapping is evidence-pinned per arm: +0x838 is written by the level-1 attack start
//    (FUN_00421fe0) and is the port's MAIN pool, +0x83c by the level-2 start (FUN_004220e0)
//    and is the port's CHARGE pool, and +0x840 by the hyper activation (FUN_00422160, which
//    also restores HP) and is the port's hypermode gauge.
//
// What the port CAN be exact about, and is: F1's two scene counters. scene+0x12b0/+0x12bc are
// the balloon entries' `+0x04 int balloon %` fields (entries at scene+0x12ac/+0x12b8, 12 bytes
// each), credited by FUN_00639650 and read by FUN_00635d40 to name the round's winner, so they
// are this port's MatchEconomy::balloon(0)/balloon(1) — not an invented counter.

#include "gameplay/match.h"

namespace gameplay {

// The DIK scancodes FUN_006586d0 is called with. The port's keyboard is read by SDL scancode
// (input/input_sdl3.h pins the five SDL values for the same physical keys), so these are the
// RECOVERED codes and the host translates; keeping them named here is what makes the map
// checkable against FUN_00634f60.
inline constexpr int kDikEscape = 0x01;
inline constexpr int kDikF1     = 0x3b;
inline constexpr int kDikF2     = 0x3c;
inline constexpr int kDikF3     = 0x3d;
inline constexpr int kDikF4     = 0x3e;

// F3's ownership test: `3 < the slot's controller/type field`. The selection screen fills the
// array (FUN_0040d130:70 writes 4 into an unset slot, :88 copies a human panel's controller,
// :108 tests `< 4`), and 4 is COM in the port too (ui/frontend_state.h: "controller 4 is COM").
inline constexpr int kComControllerType = 4;

// One tick's held key set. The original reads state, not edges, every frame, and every one of
// the five effects is idempotent — so a held key re-applies, which is what a scripted tap
// has to reproduce with a single held tick.
struct DebugKeysHeld {
    bool escape = false;
    bool f1     = false;
    bool f2     = false;
    bool f3     = false;
    bool f4     = false;
};

// Applies ONE simulation tick's held keys to `match`, in the original's own order (Escape,
// then F2, F3, F1, F4). `comOwned[i]` is fighter i's ownership bit — the slot's controller
// field is >= kComControllerType — and is the recovered gate on F3.
//
// `enabled` is the port's gate (--no-debug-keys). With it false nothing is read and nothing
// changes, whatever the key set says: that is the arm an evidence run takes so a physical
// F-key cannot silently alter its capture.
//
// Returns true when Escape asked the battle to leave (the original's scene+0x4a40 = 1); the
// host resolves that through its existing leave path. Escape also ignores the pause state in
// the original — it is read before the pause gate there — while this port only samples keys
// where a battle ticks, so a paused battle does not take it (see docs/DEBUG-KEYS.md).
bool applyDebugKeys(Match& match, const DebugKeysHeld& keys, const bool comOwned[4],
                    bool enabled = true);

}  // namespace gameplay
