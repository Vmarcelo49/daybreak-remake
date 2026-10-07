#pragma once
// gameplay/battle_pause.h — the offline battle pause state (issue #15), device-free.
//
// RECOVERED, not invented. The original has a pause flag and a second toggle, both
// cleared by the battle reset (FUN_00634760 @0x634877 / @0x634881), and toggles the flag
// from the per-fighter pause action while the battle is live:
//
//   FUN_00634f60 (the battle per-frame):
//     @0x634fb3-0x634fbc  gate: only in the offline mode byte (DAT_006cfdb0 == 0)
//     @0x634fc2-0x634fcc  gate: only in the live battle phase (scene+0x4a3c == 2)
//     @0x634fdf-0x634fe6  the player's pause action state ([fighter+0x29c] == 1)
//     @0x634fe8-0x634fef  plays system SE 0x11 (FUN_0064aed0) — the pause cue
//     @0x634ff4-0x635006  flips scene+0x4430 (`1 - (x != 0)`)
//     @0x63500c-0x635064  while paused, any of the fighter's 7 action slots flips the
//                         second toggle scene+0x4431 (the prompt/banner switch)
//     @0x635093-0x6350aa  while scene+0x4430 is set, skip the battle frame counter
//                         (scene+0x1c) and the WHOLE update — fighter updates
//                         (FUN_0041f580), the round machine (FUN_00635d40), the balloon
//                         easing (FUN_006430f0), the camera/FX tail — and return the
//                         phase unchanged.
//
// So the original freezes exactly what this port freezes, and it keeps reading input while
// paused (the toggle lives before the gate), which is also what lets a player resume.
//
// PORT FEATURE (labelled as such): the four-row readable menu below — resume, rematch,
// return to selection, quit — and its captions. The original's recovered pause UI is the
// "PAUSE" banner drawn centered at (400,300) of the 800x600 canvas while paused with
// scene+0x4431 clear (FUN_0063a130 @0x63a08c-0x63a0b8; the cell is (256,64,256,64) of
// data/object/system.cnv) plus the same atlas's もう一度挑戦しますか？ prompt (0,128,416,64)
// with はい/いいえ cells (0,192,256,64) — i.e. a yes/no rematch prompt, and no
// return-to-selection row (leaving a battle goes through the result scene there).
// See docs/USER-SETTINGS.md's sibling doc docs/PAUSE.md for the full note.

namespace gameplay {

// What the menu asked the host to do this tick. `None` keeps the battle paused.
enum class PauseChoice { None, Resume, Rematch, ReturnToSelection, Quit };

// The rows a battle can offer. A front-end battle can return to the selection screen; the
// standalone --match harness has no menu stack behind it, so its last row is quit and the
// return row is absent. Row 0 is always Resume and the last row is always Quit.
constexpr int kPauseRowsWithSelection = 4;
constexpr int kPauseRowsStandalone = 3;

// ONE table, and both the label and the action come out of it. The menu is the port's, not
// a recovered one (docs/PAUSE.md: the original has a banner and a もう一度挑戦しますか？ yes/no
// prompt), so this row map IS the policy: row 0 Resume, row 1 Rematch, the LAST row Quit
// whatever the length, and row 2 the return row only in the menu that has one. `rows` is 4
// with a selection screen behind the battle and 3 without, so only that row comes and goes.
enum class PauseRowKind { Resume, Rematch, ReturnToSelection, Quit };
constexpr int kPauseRowKindCount = 4;
constexpr const char* kPauseRowLabels[kPauseRowKindCount] = {
    "Resume", "Rematch", "Return to selection", "Quit to desktop",
};

// The row's kind in a `rows`-row menu, or -1 for "no row" (the caller's default). These are
// the original branches one for one, plus the guard the old inline comment ("only reachable
// with four rows") already described: the shorter menu's row 2 is its LAST row and takes
// the quit branch like any other menu's.
constexpr int pauseRowKind(int row, int rows) {
    if (row == rows - 1) return static_cast<int>(PauseRowKind::Quit);
    if (row == 1) return static_cast<int>(PauseRowKind::Rematch);
    if (row == 2 && rows >= kPauseRowsWithSelection)
        return static_cast<int>(PauseRowKind::ReturnToSelection);
    return -1;
}

// The row labels, in menu order, for a menu of `rows` rows.
inline const char* pauseRowLabel(int row, int rows) {
    const int kind = pauseRowKind(row, rows);
    return kPauseRowLabels[kind < 0 ? static_cast<int>(PauseRowKind::Resume) : kind];
}

// The menu cursor. Edges only: the host feeds one tick's up/down/confirm/cancel, and the
// pause action itself is the host's toggle (the original's own key).
struct PauseMenu {
    int rows = kPauseRowsWithSelection;
    int row = 0;

    void reset() { row = 0; }

    // One step. Cancel is the universal back and resumes, which is what every other menu
    // in the port does with it; confirm takes the selected row.
    PauseChoice update(bool up, bool down, bool confirm, bool cancel) {
        if (cancel) return PauseChoice::Resume;
        if (rows < 2) rows = 2;
        if (row >= rows) row = rows - 1;
        if (up) row = (row + rows - 1) % rows;
        else if (down) row = (row + 1) % rows;
        if (!confirm) return PauseChoice::None;
        switch (pauseRowKind(row, rows)) {
            case static_cast<int>(PauseRowKind::Quit):   return PauseChoice::Quit;
            case static_cast<int>(PauseRowKind::Rematch): return PauseChoice::Rematch;
            case static_cast<int>(PauseRowKind::ReturnToSelection):
                return PauseChoice::ReturnToSelection;
            default: return PauseChoice::Resume;
        }
    }
};

}  // namespace gameplay
