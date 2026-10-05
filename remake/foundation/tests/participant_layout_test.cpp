// Issue #13: the participant roster and the screen geometry every four-fighter screen reads.
// Device-free — the roster derivation, the VS slot layout, the result rows and the victory
// layer's transition are pure functions, so a 1v1, a 2v1 and a 2v2 can all be pinned without a
// GPU (the screens themselves are covered by the asset-backed run reported with the issue).
#include <cstdio>
#include <cstring>
#define CHECK(condition) do { if (!(condition)) { std::fprintf(stderr,"%s:%d: %s\n",__FILE__,__LINE__,#condition); return 1; } } while (false)
#include "ui/participants.h"
#include "ui/screen_result.h"

static ui::FrontendState twoVsTwo() {
    ui::FrontendState state;
    const int characters[4] = {0, 2, 4, 1};
    for (int panel = 0; panel < 4; ++panel) {
        state.slots[panel].character = characters[panel];
        state.slots[panel].weapon = panel % 2;
        state.slots[panel].controller = panel;
    }
    return state;
}

int main() {
    // A 1v1 is panels 0 and 2 — the two PRIMARY panels the old code assumed — and nothing else.
    ui::FrontendState solo;
    solo.slots[0].character = 0;
    solo.slots[0].controller = 0;
    solo.slots[0].weapon = 1;
    solo.slots[2].character = 4;
    solo.slots[2].controller = 4;
    ui::Participant roster[ui::kParticipantCount];
    int count = ui::buildParticipants(solo.slots.data(), roster);
    CHECK(count == 2);
    CHECK(roster[0].panel == 0 && roster[0].team == 0 && roster[0].human());
    CHECK(roster[1].panel == 2 && roster[1].team == 1 && !roster[1].human());
    CHECK(roster[0].weaponId == gameplay::kWeaponIds[0][1]);
    CHECK(roster[0].combo() == gameplay::comboSlotLabel(0, 1));
    CHECK(std::strcmp(ui::controllerLabel(roster[0].controller), "1P") == 0);
    CHECK(std::strcmp(ui::controllerLabel(roster[1].controller), "COM") == 0);
    // The absent panels are not participants: no third entry, no ghost team.
    CHECK(!roster[2].present() && roster[2].panel == -1);
    // A 1v1 draws the two centred portraits the port already shipped, not a hole where the
    // original's second COM slot would be.
    ui::VsSlot soloSlots[ui::kParticipantCount];
    ui::vsSlotsFor(roster, count, soloSlots);
    CHECK(soloSlots[0].portraitX == 600.f && soloSlots[1].portraitX == 200.f);
    CHECK(soloSlots[0].nameX == 150.f && soloSlots[1].nameX == 650.f);

    // A 2v2 is all four panels, two per team, in panel order.
    ui::FrontendState state = twoVsTwo();
    count = ui::buildParticipants(state.slots.data(), roster);
    CHECK(count == 4);
    for (int i = 0; i < 4; ++i) {
        CHECK(roster[i].panel == i);
        CHECK(roster[i].team == (i < 2 ? 0 : 1));
        CHECK(roster[i].controller == i);
        CHECK(roster[i].human());
    }
    int members[ui::kParticipantCount];
    CHECK(ui::teamMembers(roster, count, 0, members) == 2 && members[0] == 0 && members[1] == 1);
    CHECK(ui::teamMembers(roster, count, 1, members) == 2 && members[0] == 2 && members[1] == 3);
    // The four recovered versus slots: names at (150,200) (200,250) (600,350) (650,400) and
    // portraits at (500,295) (700,295) (300,600) (100,600) — FUN_00411cb0's versus branch.
    ui::VsSlot slots[ui::kParticipantCount];
    ui::vsSlotsFor(roster, count, slots);
    CHECK(slots[0].nameX == 150.f && slots[0].nameY == 200.f && slots[0].portraitX == 500.f && slots[0].portraitY == 295.f);
    CHECK(slots[1].nameX == 200.f && slots[1].nameY == 250.f && slots[1].portraitX == 700.f && slots[1].portraitY == 295.f);
    CHECK(slots[2].nameX == 600.f && slots[2].nameY == 350.f && slots[2].portraitX == 300.f && slots[2].portraitY == 600.f);
    CHECK(slots[3].nameX == 650.f && slots[3].nameY == 400.f && slots[3].portraitX == 100.f && slots[3].portraitY == 600.f);
    // Each slot slides on its own offset (30/20/20/30 px per frame, FUN_00411ae0:12-21).
    CHECK(slots[0].slide == 0 && slots[1].slide == 1 && slots[2].slide == 2 && slots[3].slide == 3);

    // A 2v1 (three participants) keeps the recovered pair for the full team and the centred
    // single slot for the team with one member.
    ui::FrontendState uneven;
    uneven.slots[0].character = 0;
    uneven.slots[1].character = 2;
    uneven.slots[2].character = 4;
    count = ui::buildParticipants(uneven.slots.data(), roster);
    CHECK(count == 3);
    ui::vsSlotsFor(roster, count, slots);
    CHECK(slots[0].portraitX == 500.f && slots[1].portraitX == 700.f);
    CHECK(slots[2].portraitX == 200.f && slots[2].nameX == 650.f);

    // The result report's rows: FUN_0063a740:64-85's y = 100 + 72*i, badge at x 150, text at
    // x 280, name cell 32 px lower.
    for (int i = 0; i < 4; ++i) {
        const ui::ResultRow row = ui::resultRow(i);
        CHECK(row.badgeY == 100.f + 72.f * (float)i);
        CHECK(row.badgeX == 150.f && row.textX == 280.f);
        CHECK(row.nameY == row.badgeY + 32.f && row.textY == row.badgeY);
    }
    // One row appears every 30 frames after a 30-frame lead-in, and never more than four.
    CHECK(ui::resultRowsRevealed(0) == 0 && ui::resultRowsRevealed(29) == 0);
    CHECK(ui::resultRowsRevealed(30) == 0 && ui::resultRowsRevealed(59) == 0);
    CHECK(ui::resultRowsRevealed(60) == 1);
    CHECK(ui::resultRowsRevealed(120) == 3);
    CHECK(ui::resultRowsRevealed(150) == 4 && ui::resultRowsRevealed(1000) == 4);

    // The victory sting's second layer is armed when the first has 0x78 of its 0xb4 frames
    // left, i.e. 60 frames in (FUN_00635d40:196-205, drawn at (400,400) by FUN_0063a130).
    ui::ResultTimeline timeline;
    for (int frame = 0; frame < 60; ++frame) {
        CHECK(!timeline.victorySecondLayer());
        CHECK(!timeline.update(false));
    }
    CHECK(timeline.victorySecondLayer());
    CHECK(timeline.phase() == ui::ResultPhase::Victory);

    std::puts("participant_layout_test: roster, VS slots, result rows and victory layers ok");
    return 0;
}
