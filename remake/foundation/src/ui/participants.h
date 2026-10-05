#pragma once
// The participant roster of a local versus launch, and the screen geometry that lays it out.
//
// WHY this exists: the front end has always known all four selections (panel 0/1 blue, 2/3
// red, FUN_00409340's geometry), but VS, the battle HUD and the results were written when
// only the two *primary* panels (0 and 2, `kFrontendBattleSlots`) could reach a match. This
// header is the one place that turns the four slots into an ordered participant list, so the
// three screens cannot disagree about who is fighting — and so the ordering is testable
// without a device.
//
// Panel, team, fighter index and controller are four DIFFERENT index spaces and stay
// separate here (gameplay/target_lock.h makes the same point for targets):
//   * `panel`      0..3, the selection grid (0/1 blue, 2/3 red);
//   * `team`       0 blue / 1 red, derived from the panel (FUN_00409340);
//   * `fighter`    the index in MatchConfig order (the launch's own order), host-filled;
//   * `controller` 0..3 local human, 4 = COM — FUN_0040d130's sentinel.
//
// The layout numbers are the original's own:
//   * VS: FUN_00411cb0 @0x411cb0 draws four portraits at (500,295), (700,295), (300,600),
//     (100,600) (minus/plus the slide offsets `+0x5d0..+0x5dc`, FUN_00411ae0:12-21) and four
//     name cells at (150,200), (200,250), (600,350), (650,400) — the versus branch
//     (`DAT_006cfdb0 == 0`), each name cell selected as (charIndex/8, charIndex%8) of the
//     name sheet.
//   * Result report: FUN_0063a740 @0x63a740:64-85 draws rows i = 0..3 at y = 100 + 72*i, the
//     1P/2P/3P/4P/com badge at x = 150 (cell `DAT_006cfaf8[i]`, i.e. that panel's controller)
//     and the name cell at (150, y + 32); the text column is x = 280.
//   * The victory sting is two layers at (400,200) and (400,400) (FUN_0063a130:89-98), the
//     second armed when the first has 0x78 of its 0xb4 frames left (FUN_00635d40:196-205).
//
// Device-free (std only plus the header-only gameplay tables): every screen and every host
// test reads the same arithmetic.
#include <cstdint>

#include "gameplay/weapon_definition.h"   // kWeaponIds / comboSlotLabel (header-only)
#include "ui/frontend_state.h"

namespace ui {

// Four selection panels, four participants at most (FUN_00409340).
inline constexpr int kParticipantCount = 4;

struct Participant {
    int panel = -1;         // 0..3; -1 = absent
    int team = 0;           // 0 blue (panels 0/1), 1 red (2/3)
    int character = -1;     // roster index; -1 = absent
    int weapon = 0;         // weapon slot within the character
    int weaponId = 0;       // data/item id the launch resolved
    int controller = 4;     // 0..3 human, 4 = COM
    int fighter = -1;       // MatchConfig index, filled by the host from the launch

    bool present() const { return panel >= 0 && character >= 0; }
    bool human() const { return controller >= 0 && controller < 4; }
    // "Rena 1" — the combo label (AGENTS.md rule 7: a fighter is never bare).
    std::string combo() const { return gameplay::comboSlotLabel(character, weapon); }
};

// The roster in PANEL order, which is the order FUN_0040d130 copies the choices in
// (DAT_006cfb28/2c/30/34) and the order FUN_006396f0 keys its views and cells by. A slot
// with no character is absent, so a 1v1 yields two participants (panels 0 and 2), a 2v2
// four, and a 2v1 three — the roster is the selection, never a fixed pair.
inline int buildParticipants(const FrontendSlot slots[kParticipantCount],
                             Participant out[kParticipantCount]) {
    int count = 0;
    for (int panel = 0; panel < kParticipantCount; ++panel) {
        const FrontendSlot& slot = slots[panel];
        if (slot.character < 0) continue;
        Participant& p = out[count++];
        p.panel = panel;
        p.team = panel < 2 ? 0 : 1;
        p.character = slot.character;
        p.weapon = slot.weapon;
        p.weaponId = gameplay::kWeaponIds[slot.character][slot.weapon];
        p.controller = slot.controller;
    }
    return count;
}

// Members of one team, in roster order: `out` receives the roster indices.
inline int teamMembers(const Participant roster[kParticipantCount], int count, int team,
                       int out[kParticipantCount]) {
    int n = 0;
    for (int i = 0; i < count; ++i)
        if (roster[i].team == team) out[n++] = i;
    return n;
}

// "1P".."4P" for a local controller, "COM" for the sentinel (the same labels the tag atlas
// and the report badges use).
inline const char* controllerLabel(int controller) {
    switch (controller) {
        case 0: return "1P";
        case 1: return "2P";
        case 2: return "3P";
        case 3: return "4P";
        default: return "COM";
    }
}

inline const char* teamLabel(int team) { return team == 0 ? "BLUE" : "RED"; }

// One participant's VS slot: the name cell anchor and the portrait anchor (both are draw
// PIVOTS: the portrait's is (128,256), so its top-left is (portraitX-128, portraitY-256)).
struct VsSlot {
    float nameX = 0.f, nameY = 0.f;
    float portraitX = 0.f, portraitY = 0.f;
    int   slide = 0;        // which of FUN_00411ae0's four slide offsets this slot uses
};

// The four recovered versus slots, indexed by the participant's member index within its team
// (0 = the first member, 1 = the second). Team 0's portraits sit in the top band (y 295) and
// slide in from the right, team 1's in the bottom band (y 600) from the left.
inline constexpr VsSlot kVsSlots[2][2] = {
    {{150.f, 200.f, 500.f, 295.f, 0}, {200.f, 250.f, 700.f, 295.f, 1}},
    {{600.f, 350.f, 300.f, 600.f, 2}, {650.f, 400.f, 100.f, 600.f, 3}},
};

// A team with a single participant: the port keeps the centred portrait and the outer name
// cell the 1v1 flow already shipped (blue 600/200, red 200/600 for the portrait; (150,200)
// and (650,400) for the name) rather than leaving a hole where the original always had a
// second COM slot. PORT RULE — the original never has a one-member team.
inline VsSlot vsSlotForSingle(int team, int member) {
    (void)member;
    return team == 0 ? VsSlot{150.f, 200.f, 600.f, 295.f, 0}
                     : VsSlot{650.f, 400.f, 200.f, 600.f, 3};
}

// Fills `out` (roster order) with each participant's VS slot: the recovered per-team pair
// when the team has two members, the centred single-member slot otherwise.
inline void vsSlotsFor(const Participant roster[kParticipantCount], int count,
                       VsSlot out[kParticipantCount]) {
    for (int team = 0; team < 2; ++team) {
        int members[kParticipantCount];
        const int n = teamMembers(roster, count, team, members);
        for (int m = 0; m < n; ++m)
            out[members[m]] = n == 2 ? kVsSlots[team][m] : vsSlotForSingle(team, m);
    }
}

// One row of the result report (FUN_0063a740:64-85): the controller/COM badge sits at x = 200
// (0x43480000), the earned title at (300, y + 32) — the composed title texture's line cell,
// drawn at 0x43960000 = 300 — and rows step by 72 from y = 100. The port's combo and
// statistics lines hang off the same column.
struct ResultRow {
    float badgeX = 200.f, badgeY = 0.f;
    float textX = 300.f, textY = 0.f;
    float titleY = 0.f;
    float statsY = 0.f;
};

inline constexpr float kResultRowTop = 100.f;
inline constexpr float kResultRowStep = 72.f;

inline ResultRow resultRow(int row) {
    const float y = kResultRowTop + kResultRowStep * (float)row;
    return ResultRow{200.f, y, 300.f, y, y + 32.f, y + 50.f};
}

// The report reveals rows progressively: FUN_0063a740:69 draws row i while
// `i < (progress - 30) / 30`, i.e. one new row every 30 frames after a 30-frame lead-in.
inline int resultRowsRevealed(int progress) {
    if (progress < 30) return 0;
    const int rows = (progress - 30) / 30;
    return rows > kParticipantCount ? kParticipantCount : rows;
}

}  // namespace ui
