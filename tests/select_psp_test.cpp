// The select diamond with the PSP three on it: where they sit, that the free cursor reaches them,
// and that nothing about the PC sixteen's own cells moved.
//
// Device-free: SelectMenu is the whole instrument (no screen, no GPU, no install), exactly as
// select_cursor_test.cpp drives it. The literals for the first sixteen cells are the recovered
// tables; the three appended ones are a PORT EXTENSION and are pinned here so the day they move,
// the regression is a failing test and not a moved chibi in a capture.
#include <algorithm>
#include <cmath>
#include <cstdio>

#include "frontend/screen_select.h"

#define CHECK(x) do { if (!(x)) { std::fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #x); return 1; } } while (false)

namespace {

// Held stick, one update per tick: the press edge on the first tick and the held state after it,
// the way main.cpp's front-end loop delivers a real device.
void hold(ui::SelectMenu& menu, ui::ScreenInput in, int ticks) {
    for (int i = 0; i < ticks; ++i) {
        if (i > 0) in.up = in.down = in.left = in.right = false;
        menu.update(in);
    }
}

// Every icon's position in the free cursor's units: the cell times the 48x36 pitch
// (screen_select.cpp's rosterPos).
float cellX(int i) { return ui::kSelectRosterX[i] * 48.f; }
float cellY(int i) { return ui::kSelectRosterY[i] * 36.f; }

float distance(int a, int b) {
    const float dx = cellX(a) - cellX(b);
    const float dy = cellY(a) - cellY(b);
    return std::sqrt(dx * dx + dy * dy);
}

}  // namespace

int main() {
    // --- the PC sixteen's cells are bit-identical to the recovered tables --------------------
    const int x[16] = {0, -2, -1, 0, 1, -1, -1, -2, 0, 1, 2, 2, 1, 0, 3, -3};
    const int y[16] = {6, 4, 5, 4, 5, 3, 1, 2, 2, 3, 4, 2, 1, 0, 3, 3};
    const int order[16] = {14, 15, 13, 12, 6, 11, 8, 7, 9, 5, 10, 3, 1, 4, 2, 0};
    const int costumes[16] = {5, 5, 3, 5, 5, 5, 2, 4, 2, 2, 3, 3, 1, 2, 4, 5};
    CHECK(ui::kSelectRosterCount == gameplay::kRosterCharacterCount);
    for (int i = 0; i < 16; ++i) {
        CHECK(ui::kSelectRosterX[i] == x[i] && ui::kSelectRosterY[i] == y[i]);
        CHECK(ui::kSelectRosterOrder[i] == order[i] && ui::kSelectCostumes[i] == costumes[i]);
    }
    // The three are appended, so the sixteen are drawn first and their reveal timing is untouched.
    CHECK(ui::kSelectRosterOrder[16] == 16 && ui::kSelectRosterOrder[17] == 17 &&
          ui::kSelectRosterOrder[18] == 18);
    // Costumes: the PSP's own model counts.
    CHECK(ui::kSelectCostumes[16] == 5 && ui::kSelectCostumes[17] == 7 && ui::kSelectCostumes[18] == 3);

    // --- the cells the three occupy are reachable, and no PC icon is one of them -------------
    // The recovered passes are a 30-unit select radius with a <50-unit fallback, so two icons one
    // lattice step apart (48 x, 36 y) would leave a band where the earlier roster index wins.
    for (int i = 16; i < ui::kSelectRosterCount; ++i) {
        bool overlaps = false;
        for (int j = 0; j < ui::kSelectRosterCount; ++j) {
            if (j == i) continue;
            if (distance(i, j) < 50.f) overlaps = true;
        }
        CHECK(!overlaps);
        // Inside the free cursor's own clamps ([-200,200] x [-60,300], FUN_00409340:246-251), so
        // the stick can put the cursor exactly on the icon and the magnet then holds it there.
        CHECK(std::fabs(cellX(i)) <= 200.f && cellY(i) >= -60.f && cellY(i) <= 300.f);
    }

    ui::ScreenInput confirm; confirm.confirm = true;
    ui::ScreenInput up; up.up = true; up.upHeld = true;
    ui::ScreenInput left; left.left = true; left.leftHeld = true;

    // --- mounted: the three are offered and the cursor selects them --------------------------
    gameplay::setPspRosterMounted(true);
    for (int character = 16; character < 19; ++character) {
        ui::FrontendState state;
        ui::SelectMenu menu(state);
        CHECK(ui::selectableRosterCount(state) == 19);
        menu.update(confirm);                       // team -> character phase, seeded on index 0
        CHECK(menu.phase() == ui::SelectPhase::Character);
        CHECK(state.slots[0].character == 0);
        // From the seed cell to the icon's own cell: 4.0 units/tick across and 3.0 up
        // (FUN_00409340:239-244), so each axis takes its own number of whole ticks and the two run
        // together. The distances here are exact multiples, which keeps the arrival off the magnet.
        const float dx = cellX(character) - cellX(0);
        const float dy = cellY(character) - cellY(0);
        const int acrossTicks = (int)std::ceil(std::fabs(dx) / 4.f);
        const int verticalTicks = (int)std::ceil(std::fabs(dy) / 3.f);
        for (int i = 0; i < std::max(acrossTicks, verticalTicks); ++i) {
            ui::ScreenInput in;
            if (i < acrossTicks) {
                if (dx < 0) in.left = in.leftHeld = true;
                else if (dx > 0) in.right = in.rightHeld = true;
            }
            if (i < verticalTicks) {
                if (dy < 0) in.up = in.upHeld = true;
                else if (dy > 0) in.down = in.downHeld = true;
            }
            menu.update(in);
        }
        CHECK(state.slots[0].character == character);
        CHECK(!menu.cursorOffGrid());
        CHECK(std::fabs(menu.cursorX() - cellX(character)) < 1.f);
        CHECK(std::fabs(menu.cursorY() - cellY(character)) < 1.f);
        // ... and the confirm takes it, with four weapon slots to choose from.
        menu.update(confirm);
        CHECK(menu.phase() == ui::SelectPhase::Weapon);
        CHECK(gameplay::rosterWeaponCount(state.slots[0].character) == 4);
        state.slots[0].weapon = 3;
        menu.update(confirm);                       // weapon -> hypermode
        CHECK(menu.phase() == ui::SelectPhase::Hypermode);
    }

    // --- unmounted: the same cells are off the diamond, so the three cannot be picked --------
    gameplay::setPspRosterMounted(false);
    {
        ui::FrontendState state;
        ui::SelectMenu menu(state);
        CHECK(ui::selectableRosterCount(state) == 16);
        menu.update(confirm);
        // Straight up from the seed cell: 3.0 units/tick takes the cursor past the diamond's top
        // vertex to its own clamp (-60), where nothing is inside either selection radius.
        hold(menu, up, 120);
        CHECK(menu.cursorOffGrid());
        CHECK(state.slots[0].character == -1);      // off the grid: the portrait rolls, nothing taken
    }

    // --- online keeps the PC sixteen even with the data mounted ------------------------------
    {
        gameplay::setPspRosterMounted(true);
        ui::FrontendState state;
        state.onlineHumans = 2;
        CHECK(ui::selectableRosterCount(state) == 16);
        gameplay::setPspRosterMounted(false);
    }
}
