// Issue #41: the character select's free cursor, pinned against the recovered rule in
// FUN_00409340's character-select case (research/decompiled/FUN_00409340.c:232-300).
//
// Device-free: SelectMenu::update is the whole instrument — no screen, no GPU, no install.
// The cursor's float state is read back through cursorX()/cursorY(), which exist so that the
// RATE, the CLAMPS and the MAGNET are observable and not just implied by which character ends
// up selected.
//
// The literals below are the recovered constants, not tuned values: 4.0/tick horizontal and
// 3.0/tick vertical (0x40800000 / 0x40400000), clamps [-200,200] (0xc3480000/0x43480000) and
// [-60,300] (0xc2700000/0x43960000), the magnet's <400 squared radius, and the selection's
// <900 (30 units) then <2500 (50 units) passes.
#include "ui/screen_select.h"
#include <cmath>
#include <cstdio>
#include <vector>

namespace {
// A held stick, one update per tick, exactly as the front end delivers it (main.cpp's
// tickFrontend): the press EDGE on the first tick and the HELD state on every tick of the hold.
// The recovered rule accumulates the held state (FUN_00409340:239-244 reads the stick every
// call), so a test that only set the edge would be modelling input no device can produce.
void hold(ui::SelectMenu& menu, ui::ScreenInput in, int ticks) {
    for (int i = 0; i < ticks; ++i) {
        if (i > 0) in.up = in.down = in.left = in.right = false;
        menu.update(in);
    }
}
bool near(float a, float b) { return std::fabs(a - b) < 0.001f; }
}  // namespace

int main() {
    int failures = 0;
    auto check = [&](bool value, const char* name) {
        if (!value) { std::fprintf(stderr, "FAIL %s\n", name); ++failures; }
    };
    ui::ScreenInput confirm; confirm.confirm = true;
    ui::ScreenInput left;    left.left = true; left.leftHeld = true;
    ui::ScreenInput right;   right.right = true; right.rightHeld = true;
    ui::ScreenInput up;      up.up = true; up.upHeld = true;
    ui::ScreenInput down;    down.down = true; down.downHeld = true;
    ui::ScreenInput centred;   // no direction: the magnet's own condition

    // --- The seed: the team confirm opens the character phase ON character 0 -------------
    {
        ui::FrontendState state;
        ui::SelectMenu menu(state);
        menu.update(confirm);
        check(menu.phase() == ui::SelectPhase::Character, "the team confirm opens the character phase");
        check(state.slots[0].character == 0, "an empty panel opens on character 0");
        check(near(menu.cursorX(), ui::kSelectRosterX[0] * 48.f) &&
              near(menu.cursorY(), ui::kSelectRosterY[0] * 36.f),
              "the cursor is seeded onto that character's own position");
    }

    // --- The rate: 4.0 units/tick horizontally, 3.0 vertically (FUN_00409340:239-244) ----
    {
        ui::FrontendState state;
        ui::SelectMenu menu(state);
        menu.update(confirm);
        hold(menu, left, 1);
        check(near(menu.cursorX(), -4.f) && near(menu.cursorY(), 216.f),
              "one held tick slides 4.0 units left and nothing vertically");
        hold(menu, right, 3);
        check(near(menu.cursorX(), 8.f), "right slides 4.0 units per tick");
        hold(menu, up, 1);
        check(near(menu.cursorY(), 213.f), "one held tick slides 3.0 units up");
        hold(menu, down, 3);
        check(near(menu.cursorY(), 222.f), "down slides 3.0 units per tick");
        // Both axes are read in the SAME call, each at its own rate.
        ui::ScreenInput upLeft;
        upLeft.up = upLeft.upHeld = true;
        upLeft.left = upLeft.leftHeld = true;
        const float fromX = menu.cursorX(), fromY = menu.cursorY();
        hold(menu, upLeft, 4);
        check(near(menu.cursorX(), fromX - 16.f) && near(menu.cursorY(), fromY - 12.f),
              "four diagonal ticks move 16.0 horizontally and 12.0 vertically");
    }

    // --- The clamps: [-200,200] and [-60,300] (FUN_00409340:245-256) ---------------------
    {
        ui::FrontendState state;
        ui::SelectMenu menu(state);
        menu.update(confirm);
        hold(menu, left, 100);   // 400 units of travel into a 200-unit bound
        check(near(menu.cursorX(), -200.f), "the cursor clamps at -200.0 (0xc3480000)");
        hold(menu, left, 10);
        check(near(menu.cursorX(), -200.f), "and stays clamped while the stick is still held");
        hold(menu, right, 200);
        check(near(menu.cursorX(), 200.f), "and at +200.0 (0x43480000)");
        hold(menu, up, 200);
        check(near(menu.cursorY(), -60.f), "the cursor clamps at -60.0 vertically (0xc2700000)");
        hold(menu, down, 300);
        check(near(menu.cursorY(), 300.f), "and at +300.0 (0x43960000)");
    }

    // --- The magnet: <20 units, only while the stick is centred (:257-270) ---------------
    {
        ui::FrontendState state;
        ui::SelectMenu menu(state);
        menu.update(confirm);
        hold(menu, left, 3);      // (-12, 216): inside the 20-unit window of character 0
        check(near(menu.cursorX(), -12.f) && state.slots[0].character == 0,
              "the magnet does not fire while a direction is held");
        menu.update(centred);
        check(near(menu.cursorX(), 0.f) && near(menu.cursorY(), 216.f),
              "releasing snaps the cursor exactly onto the current character");
        hold(menu, left, 5);      // (-20, 216): 400 is not < 400
        menu.update(centred);
        check(near(menu.cursorX(), -20.f), "20.0 units away is outside the magnet's <400 window");
        // The magnet measures to the SELECTED character's own position, so the release lands on
        // that icon exactly — here Keiichi's, three units away, not the cursor's own coordinate.
        ui::FrontendState keiichi;
        ui::SelectMenu keiichiMenu(keiichi);
        keiichiMenu.update(confirm);
        hold(keiichiMenu, left, 12);   // 12 ticks: the 30-unit pass still has Rena (48 units)
        hold(keiichiMenu, up, 3);      // 3 more: Keiichi is 27 units away -> selected
        check(keiichi.slots[0].character == 2, "the 30-unit pass picks Keiichi as the cursor closes");
        hold(keiichiMenu, up, 8);      // onto Keiichi's own row
        keiichiMenu.update(centred);
        check(near(keiichiMenu.cursorX(), ui::kSelectRosterX[2] * 48.f) &&
              near(keiichiMenu.cursorY(), ui::kSelectRosterY[2] * 36.f),
              "and the release snaps onto HIS position, not onto Rena's");
    }

    // --- The selection: <30 units, else <50, else nothing (:272-300) ---------------------
    {
        ui::FrontendState state;
        ui::SelectMenu menu(state);
        menu.update(confirm);
        // Exactly on Keiichi (character 2): the 30-unit pass selects him.
        hold(menu, left, 12);
        hold(menu, up, 12);
        check(state.slots[0].character == 2, "a character inside 30 units is selected");
        // Akane (character 13) at 47.5 units, with no other icon inside 50: only the second,
        // 50-unit pass can explain the selection (the 30-unit pass found nothing, :292-300).
        hold(menu, right, 1);    // (-48,180) -> (-44,180)
        hold(menu, up, 66);      // -> (-44,-18): 47.5 units from Akane, >50 from every other
        check(near(menu.cursorX(), -44.f) && near(menu.cursorY(), -18.f),
              "the cursor sits where the 50-unit check was measured");
        check(state.slots[0].character == 13,
              "a character between 30 and 50 units is still selected (the 50-unit pass)");
        // Off the diamond: nothing within 50 units, and the panel ROLLS A RANDOM CHARACTER
        // rather than being left unset — the original's random pick (FUN_00409340:305-317),
        // which the portrait shows changing before the press.
        hold(menu, right, 70);   // -> (200,-18), the horizontal clamp, far from every icon
        check(near(menu.cursorX(), 200.f), "the cursor is at the clamp");
        check(menu.cursorOffGrid(), "nothing is within 50 units: the cursor is off the diamond");
        // The SLOT stays empty — that is what keeps every chibi still, since the chibi draw
        // animates any character a slot matches (FUN_0040b2b0:106-131) — while the PORTRAIT
        // rolls, which is what the player sees.
        check(state.slots[0].character == -1,
              "off the diamond the SLOT is empty, so no chibi animates");
        check(menu.shown(0) >= 0 && menu.shown(0) < 16,
              "but the portrait is showing a rolled character");
        hold(menu, down, 100);   // -> (200,282)
        check(menu.cursorOffGrid(), "and stays off the diamond over far empty space");
        check(state.slots[0].character == -1, "the slot stays empty while rolling");
        check(menu.shown(0) >= 0, "and the portrait keeps rolling");
    }

    // --- The confirm off the diamond takes the shown character; the SE fires on change only -
    {
        ui::FrontendState state;
        ui::SelectMenu menu(state);
        int sound = -1;
        menu.updateFrame(confirm, &sound);
        check(sound == 0, "the team confirm plays the confirm SE (FUN_0064aed0(0))");
        // A 30-tick hold walks the cursor off the roster: character 0 is first within 50 units
        // until the cursor is more than 50 away, and then the panel rolls instead (:294 -> -1
        // is NOT what the screen shows; the roll is what the player sees).
        std::vector<int> se, character, offGrid;
        auto step = [&](ui::ScreenInput in, int ticks) {
            for (int i = 0; i < ticks; ++i) {
                if (i > 0) in.up = in.down = in.left = in.right = false;
                int tickSound = -1;
                menu.updateFrame(in, &tickSound);
                se.push_back(tickSound);
                character.push_back(state.slots[0].character);
                offGrid.push_back(menu.cursorOffGrid() ? 1 : 0);
            }
        };
        step(left, 30);   // -> (-120, 216): empty space
        step(up, 36);     // -> (-120, 108): back onto characters on the way
        int mismatches = 0, changes = 0, silentEmpty = 0, rolls = 0;
        for (size_t i = 0; i < se.size(); ++i) {
            const int previous = i == 0 ? 0 : character[i - 1];
            // The roll is silent (returning Changed would play the cursor SE once per tick);
            // the SE belongs to a real selection change, which only happens ON the diamond.
            const bool expectSe = !offGrid[i] && character[i] >= 0 && character[i] != previous;
            if ((se[i] == 2) != expectSe) ++mismatches;
            if (expectSe) ++changes;
            if (offGrid[i]) ++rolls;
            if (offGrid[i] && se[i] == 2) ++silentEmpty;
        }
        check(mismatches == 0, "the menu SE fires on exactly the ticks where the selection changes");
        // Not "several": the off-diamond roll may ALREADY be showing the character the cursor
        // lands back on, and then the return is not a change and fires no SE (the original's
        // own `if (character != hit)` guard). Measured 2 on this ladder, 19 ticks of rolling.
        check(changes >= 2, "the ladder changed the selection more than once");
        check(silentEmpty == 0, "and the off-diamond roll is silent, once per tick");
        check(rolls > 0, "the hold did spend ticks off the diamond");
        // Off the diamond, the confirm takes the character the portrait stopped on and rolls a
        // costume the character owns, going straight to Hypermode as the original does (:317).
        ui::FrontendState empty;
        ui::SelectMenu emptyMenu(empty);
        // On ENTRY nothing is picked and nothing has rolled, so every panel's portrait is
        // blank. The roll's field is -1 for "not rolled yet", not 0 — 0 is Rena, and
        // value-initialising it showed Rena on all four panels the moment the screen opened.
        for (int p = 0; p < 4; ++p)
            check(emptyMenu.shown(p) == -1, "a fresh panel's portrait is blank, not Rena");
        emptyMenu.update(confirm);
        hold(emptyMenu, left, 30);
        check(emptyMenu.cursorOffGrid(), "the cursor can rest off the diamond");
        const int shown = emptyMenu.shown(0);
        check(shown >= 0 && shown < 16, "and the panel is showing a rolled character");
        check(empty.slots[0].character == -1, "with the slot still empty before the press");
        int pickSound = -1;
        emptyMenu.updateFrame(confirm, &pickSound);
        check(pickSound == 0, "a confirm off the diamond is still a keypress");
        check(emptyMenu.phase() == ui::SelectPhase::Hypermode,
              "and it advances to Hypermode, skipping Weapon as the original does");
        check(empty.slots[0].character == shown,
              "the confirm KEEPS the character the portrait stopped on");
        check(empty.slots[0].costume >= 0 &&
                  empty.slots[0].costume < ui::kSelectCostumes[shown],
              "and rolls a costume the character owns");
        // A fresh panel: moving back onto an icon selects it normally, and its confirm still
        // goes to Weapon rather than Hypermode.
        ui::FrontendState back;
        ui::SelectMenu backMenu(back);
        backMenu.update(confirm);
        hold(backMenu, left, 30);
        hold(backMenu, right, 30);   // back onto character 0
        check(back.slots[0].character == 0, "moving back onto an icon selects it again");
        backMenu.update(confirm);
        check(backMenu.phase() == ui::SelectPhase::Weapon,
              "and a confirm ON the diamond still goes to Weapon");
    }

    // --- Issue #41's actual complaint: the off-grid icons are reachable ------------------
    // Shion (5) at (-48, 108) and Akasaka (9) at (48, 108) are the two icons the discrete
    // walk made hard to reach. From character 0's seed (0, 216) each needs 12 horizontal
    // ticks (48 / 4.0) and 36 vertical ticks (108 / 3.0) — a slide, not a grid jump.
    {
        ui::FrontendState shion;
        ui::SelectMenu shionMenu(shion);
        shionMenu.update(confirm);
        hold(shionMenu, left, 30);   // (-120, 216): off the top-left of the diamond
        check(shionMenu.cursorOffGrid(), "the cursor can slide into empty space mid-move");
        check(shion.slots[0].character == -1, "and the slot is empty there, so no chibi animates");
        check(shionMenu.shown(0) >= 0, "while the portrait rolls a character");
        float nearest = 1e9f;
        for (int i = 0; i < 16; ++i) {
            const float dx = ui::kSelectRosterX[i] * 48.f - shionMenu.cursorX();
            const float dy = ui::kSelectRosterY[i] * 36.f - shionMenu.cursorY();
            nearest = std::fmin(nearest, std::sqrt(dx * dx + dy * dy));
        }
        check(nearest > 50.f, "where nothing is within the 50-unit radius");
        hold(shionMenu, right, 18);  // -> (-48, 216)
        hold(shionMenu, up, 36);     // -> (-48, 108): Shion's own position
        check(shion.slots[0].character == 5, "Shion is selectable by sliding the cursor onto her");
        check(near(shionMenu.cursorX(), ui::kSelectRosterX[5] * 48.f) &&
              near(shionMenu.cursorY(), ui::kSelectRosterY[5] * 36.f),
              "and the cursor is exactly on her icon");
        ui::FrontendState akasaka;
        ui::SelectMenu akasakaMenu(akasaka);
        akasakaMenu.update(confirm);
        hold(akasakaMenu, right, 12);
        hold(akasakaMenu, up, 36);
        check(akasaka.slots[0].character == 9, "Akasaka is selectable by sliding the cursor onto him");
        check(near(akasakaMenu.cursorX(), ui::kSelectRosterX[9] * 48.f) &&
              near(akasakaMenu.cursorY(), ui::kSelectRosterY[9] * 36.f),
              "and the cursor is exactly on his icon");
    }

    // --- The magnet is what lands the cursor on the icon, not a rounding of the hold -----
    // A 35-tick vertical hold stops 3 units short of Shion's own coordinate; releasing hands
    // the cursor to the <20-unit magnet, which puts it exactly on her — the "release lets it
    // settle" half of issue #41's criterion 1.
    {
        ui::FrontendState state;
        ui::SelectMenu menu(state);
        menu.update(confirm);
        hold(menu, left, 30);
        hold(menu, right, 18);
        hold(menu, up, 35);
        check(near(menu.cursorY(), 111.f), "35 ticks of 3.0 stop three units short of Shion");
        check(state.slots[0].character == 5, "which is already inside her 30-unit radius");
        menu.update(centred);
        check(near(menu.cursorX(), -48.f) && near(menu.cursorY(), 108.f),
              "and the release snaps the cursor exactly onto her icon");
    }

    std::printf("select_cursor_test: %d failures\n", failures);
    return failures ? 1 : 0;
}
