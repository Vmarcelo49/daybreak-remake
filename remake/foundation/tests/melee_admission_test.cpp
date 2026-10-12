// The recovered Rena-group melee integration (melee_admission.h + the movement
// bodies in fighter.cpp/move_behavior.h):
//   1. the dispatcher table pinned case-by-case against the recovered source
//      (battle_rena_melee_admission.hpp = FUN_00445ee0/44d850/43ded0 branches);
//   2. the Fighter wiring driven by real input edges through synthetic tables;
//   3. install-backed input sequences through the shipped Rena tables;
//   4. the recovered attack-state movement bodies (speed profiles, vertical
//      channel, landings, the chase/dive arcs) through synthetic timelines whose
//      phase periods land inside the test horizon.
// The expected values below are transcribed from the recovered selector and the
// recovered execution bodies (the Ginkiha reference cross-checked with the
// original handlers), not read back from the implementation under test.

#include "combo_fixture.h"
#include "gameplay/fighter.h"
#include "gameplay/melee_admission.h"
#include "gameplay/move_behavior.h"

#include <cmath>
#include <cstdio>
#include <cstring>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace {
using gameplay::AttackAdmissionInput;
using gameplay::AttackAdmissionTable;
using gameplay::CharacterMoves;
using gameplay::Fighter;
using gameplay::FighterState;
using gameplay::WeaponDefinition;
namespace input = fnd::input;

int checks = 0, failures = 0, skipped = 0;
void check(bool condition, const char* name) {
    ++checks;
    if (!condition) ++failures;
    std::printf("  %-58s %s\n", name, condition ? "ok" : "FAIL");
}
void checkFloat(float expected, float actual, float tolerance, const char* name) {
    ++checks;
    const bool same = std::abs(expected - actual) <= tolerance;
    if (!same) ++failures;
    std::printf("  %-60s %s", name, same ? "ok" : "FAIL");
    if (!same) std::printf("  (expected %.3f, got %.3f)", expected, actual);
    std::printf("\n");
}

void checkInt(int expected, int actual, const char* name) {
    ++checks;
    const bool same = expected == actual;
    if (!same) ++failures;
    std::printf("  %-58s %s", name, same ? "ok" : "FAIL");
    if (!same) std::printf("  (expected %d, got %d)", expected, actual);
    std::printf("\n");
}
void skip(const char* name) {
    ++skipped;
    std::printf("  %-58s SKIP\n", name);
}
void section(const char* title) { std::printf("\n-- %s\n", title); }

void tick(Fighter& f, const input::PlayerState& in) {
    input::PlayerState copy = in;
    input::compute_edges(copy);
    f.update(&copy, nullptr, 1.0 / 64.0);
}

// ---------------------------------------------------------------------------
// Synthetic NN.dat-shaped table with per-row priority/cancelThreshold and a
// stateFlags-carrying first entry (synthetic_combo.h's byte layout).
void putU32(std::vector<std::uint8_t>& b, int v) {
    const auto u = static_cast<std::uint32_t>(v);
    for (int i = 0; i < 4; ++i) b.push_back(static_cast<std::uint8_t>((u >> (8 * i)) & 0xffu));
}
void putF32(std::vector<std::uint8_t>& b, float v) {
    int i = 0;
    std::memcpy(&i, &v, 4);
    putU32(b, i);
}
void putName(std::vector<std::uint8_t>& b, const char* s, int width) {
    const auto n = std::strlen(s);
    for (int i = 0; i < width; ++i)
        b.push_back(i < static_cast<int>(n) ? static_cast<std::uint8_t>(s[i]) : 0u);
}

struct AdmitEntry {
    int frame = 0;
    int stateFlags = 0;
    int hitRadius = 0;
};
struct AdmitPhase {
    int set = 0;
    std::vector<AdmitEntry> entries;
};
void addAdmitPhase(std::vector<std::uint8_t>& b, const AdmitPhase& p) {
    putU32(b, p.set);
    putU32(b, static_cast<int>(p.entries.size()));
    for (const AdmitEntry& e : p.entries) {
        putName(b, "", 30);
        putU32(b, e.frame);
        putF32(b, 0.f); putF32(b, 0.f); putF32(b, 0.f);
        putU32(b, e.hitRadius);
        for (int c = 0; c < 20; ++c) putU32(b, 0);
        putU32(b, e.stateFlags);
        putU32(b, 0);
        putU32(b, 0);
        putF32(b, 0.f); putF32(b, 0.f); putF32(b, 0.f);
    }
}
void addAdmitMove(std::vector<std::uint8_t>& b, int id, int priority,
                  int threshold, const std::vector<AdmitPhase>& phases) {
    putU32(b, id);
    putU32(b, priority);
    putU32(b, threshold);
    putU32(b, static_cast<int>(phases.size()));
    for (const auto& p : phases) addAdmitPhase(b, p);
}

// Table shape knobs for the rejection fixtures: a failing gate, a missing
// destination row, or a blocked air row — each one declines admission through
// the real dispatcher while keeping the fixture a valid character+weapon pair.
struct TableShape {
    int idleThreshold = 0;   // row 0's cancel threshold — above 10 it fails the neutral gate
    int dropRow = -1;        // a row omitted entirely (missing destination row)
    int blockedAirRow = -1;  // an airborne row given a threshold that fails the 320 gate
};

// Section counts that let rule-driven phase walks resolve: a 300 with two
// sections cannot enter the phase its Approach exit names. Locomotion and air
// rows keep two (row 30 keeps its three for the dash phase gate).
int admitSections(int id) {
    switch (id) {
        case 300: case 301: case 302: case 310: case 311: case 331:
        case 320: case 332: case 340: return 3;
        case 330: case 341: return 4;
        case 329: case 333: case 334: return 2;
        default: return 2;
    }
}

// The Rena melee row inventory with passing gates (priority 10, threshold 0).
// The chain rows' first record opens the 0x100 window, as the shipped tables do.
// `extraRows` appends shot/recovery ids (392/400/402/403/409/469) for the cases
// that need them; the base list is untouched so the older indices keep their sets.
std::vector<std::uint8_t> admissionTable(int weaponId, TableShape shape = {},
                                         const std::vector<int>& extraRows = {}) {
    std::vector<std::uint8_t> b;
    putU32(b, 0x00010000);
    putName(b, "data/rena/00.X", 0x104);
    putU32(b, 0); putU32(b, 0); putU32(b, 0);
    putU32(b, weaponId);
    putU32(b, 0); putU32(b, 0);
    std::vector<int> rows = {0, 10, 20, 23, 24, 27, 30, 40, 41, 42, 44,
                             300, 301, 302, 310, 311, 320, 329, 330, 331,
                             332, 333, 334, 340, 341};
    for (int id : extraRows) rows.push_back(id);
    int rowCount = 0;
    for (int id : rows)
        if (shape.dropRow != id) ++rowCount;
    putU32(b, rowCount);
    int set = 1;
    for (int id : rows) {
        if (shape.dropRow == id) continue;
        const bool chainRow = id == 300 || id == 301 || id == 302;
        const int threshold = (id == 0 ? shape.idleThreshold : 0) +
                              (id == shape.blockedAirRow ? 100 : 0);
        const int sections = id == 30 ? 3 : admitSections(id);
        std::vector<AdmitPhase> phases;
        for (int p = 0; p < sections; ++p)
            phases.push_back(AdmitPhase{set++, {{0, chainRow && p == 0 ? 0x100 : 0}}});
        addAdmitMove(b, id, 10, threshold, phases);
    }
    putU32(b, 124);
    for (int i = 0; i < 124; ++i) { putU32(b, 0); putU32(b, 0); putU32(b, 0); }
    return b;
}

WeaponDefinition slotWeapon(int itemId, int bulletRows = 0) {
    WeaponDefinition w;
    w.id = itemId;
    w.slotCount = 2;
    w.bulletCount = bulletRows;
    w.magazines[0] = gameplay::MagazineDefinition{6, 2, 300, 0, 60, 1};
    w.magazines[1] = gameplay::MagazineDefinition{2, 2, 300, 0, 180, 2};
    if (bulletRows > 0) {
        w.bullets = new gameplay::BulletDefinition[static_cast<size_t>(bulletRows)]{};
        for (int i = 0; i < bulletRows; ++i) w.bullets[i].magazine = 0;
    }
    return w;
}

// A table+weapon pair; every fighter binds a fresh rig so cases never inherit
// each other's animation/stamina/phase state. `setTicks` overrides specific
// sets' periods (in ticks) so the NN-period-driven phase advances land inside a
// test's horizon — the movement bodies' phase walks need them.
struct Fixture {
    CharacterMoves moves;
    WeaponDefinition weapon;
    std::vector<std::unique_ptr<xm::Model>> models;
    std::vector<std::unique_ptr<xm::Controller>> controllers;
    std::vector<std::pair<int, int>> setTicks;
    bool ok = false;
    std::string error;
    explicit Fixture(int itemId, TableShape shape = {},
                     const std::vector<int>& extraRows = {}, int bulletRows = 0,
                     int character = 0) {
        const auto bytes = admissionTable(itemId, shape, extraRows);
        ok = moves.parse(bytes.data(), bytes.size(), error);
        moves.set_character_index(character);
        weapon = slotWeapon(itemId, bulletRows);
        ok = ok && moves.weapon_id() == itemId;
    }
    Fighter& make() {
        auto model = std::make_unique<xm::Model>();
        auto controller = std::make_unique<xm::Controller>();
        model->anims.clear();
        model->ticksPerSecond = 4800.0f;
        for (int i = 0; i < 124; ++i) {
            xm::AnimSet a;
            a.name = "Anim-" + std::to_string(124 - i);
            a.duration = 480000.0f;
            model->anims.push_back(a);
        }
        for (const auto& [set, ticks] : setTicks)
            if (set >= 0 && static_cast<size_t>(set) < model->anims.size())
                model->anims[static_cast<size_t>(set)].duration = ticks * 76.8f;
        controller->bind(model.get());
        auto* f = new Fighter();
        f->init(model.get(), controller.get(), glm::vec3(0.f), 0.0f);
        f->set_moves(&moves);
        f->set_weapon(&weapon);
        input::PlayerState idle;
        for (int i = 0; i < 70; ++i) tick(*f, idle);
        fighters.emplace_back(f);
        models.push_back(std::move(model));
        controllers.push_back(std::move(controller));
        return *fighters.back();
    }
    std::vector<std::unique_ptr<Fighter>> fighters;
};

void doubleTap(Fighter& f, int action) {
    input::PlayerState in{};
    in.down[action] = true;  tick(f, in);
    in.down[action] = false; tick(f, in);
    in.down[action] = true;  tick(f, in);
    in.down[action] = false; tick(f, in);
}

input::PlayerState pressWith(int attack, int held = -1) {
    input::PlayerState in{};
    in.down[attack] = true;
    if (held >= 0) in.down[held] = true;
    return in;
}

// ---------------------------------------------------------------------------
struct TableCase {
    int weapon, state, phase;
    bool grounded, normal;
    int x, z;
    int expected;
    const char* name;
    bool boosted = false;   // armed special (+0x845/+0x848), Mion's branches only
    unsigned contact = 0;   // melee contact bits, required by the boosted form
};

void runTableCases(const CharacterMoves& moves, const TableCase* cases, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        const TableCase& c = cases[i];
        AttackAdmissionInput in;
        in.weaponSlot = c.weapon;
        in.state = c.state;
        in.phase = c.phase;
        in.grounded = c.grounded;
        in.x = c.x;
        in.z = c.z;
        in.normalFlag = c.normal;
        in.contact = c.contact;
        in.boosted = c.boosted;
        checkInt(c.expected, gameplay::rena_melee_admission(in, AttackAdmissionTable{&moves}),
                 c.name);
    }
}

// Mion's melee branch is common to her three dispatchers, so one table drives it.
void runMionCases(const CharacterMoves& moves, const TableCase* cases, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        const TableCase& c = cases[i];
        AttackAdmissionInput in;
        in.weaponSlot = c.weapon;
        in.state = c.state;
        in.phase = c.phase;
        in.grounded = c.grounded;
        in.x = c.x;
        in.z = c.z;
        in.normalFlag = c.normal;
        in.contact = c.contact;
        in.boosted = c.boosted;
        const int viaTable = gameplay::mion_melee_admission(in, AttackAdmissionTable{&moves});
        checkInt(c.expected, viaTable, c.name);
        // The shared entry must route character 1 here unchanged.
        checkInt(c.expected,
                 gameplay::melee_admission_for(1, in, AttackAdmissionTable{&moves}),
                 "melee_admission_for(1) agrees");
    }
}

int run() {
    section("Mion melee admission — common dispatcher branch");
    {
        // Item 2 is Mion weapon 0 (kWeaponIds[1]); character 1 so the item resolves to
        // slot 0, and 312 ships via extraRows because only Mion uses it.
        Fixture mion(2, {}, {312}, 0, 1);
        if (!mion.ok) { check(false, "synthetic Mion table parses"); return 1; }
        check(gameplay::attack_admission_recovered(1),
              "the Mion group is on the recovered path");
        const TableCase cases[] = {
            {0, 0, 0, true, true, 0, 0, 300, "Mion idle neutral -> 300"},
            {0, 10, 0, true, true, 0, 0, 300, "Mion walk neutral -> 300"},
            {0, 20, 0, true, true, 0, 0, 330, "Mion forward dash -> 330"},
            {0, 20, 0, true, true, 1, 0, 331, "Mion lateral in the forward dash -> 331"},
            {0, 23, 0, true, true, 0, -1, 330, "Mion back-held side dash -> 330"},
            {0, 23, 0, true, true, 0, 0, 331, "Mion side dash -> 331"},
            {0, 24, 0, true, true, 0, 0, 331, "Mion other side dash -> 331"},
            {0, 0, 0, true, true, 0, -1, 310, "Mion back input -> 310"},
            {0, 0, 0, true, true, 1, 0, 312, "Mion lateral input -> 312, not 311"},
            {0, 329, 0, true, true, 0, 0, 340, "Mion landing row -> 340"},
            {0, 333, 0, true, true, 0, 0, 340, "Mion dash-recovery row -> 340"},
            {0, 44, 0, true, true, 0, 0, 340, "Mion row 44 source -> 340"},
            {0, 340, 0, true, true, 0, 0, 341, "Mion 340 -> 341"},
            {0, 300, 0, true, true, 0, 0, 301, "Mion 300 -> 301"},
            {0, 301, 0, true, true, 0, 0, 300, "Mion 301 has no 302 follow-up"},
            {0, 0, 0, false, true, 0, 0, 320, "Mion airborne press -> 320"},
            {0, 30, 0, false, true, 1, 0, 320, "Mion air dash still resolves 320 (no 332)"},
            {2, 0, 0, true, true, 0, 0, 300, "Mion+2 shares the same branch"},
            {2, 0, 0, true, true, 1, 0, 312, "Mion+2 lateral -> 312 (no per-weapon delta)"},
            {2, 0, 0, false, false, 0, 0, -1, "Mion+2 unarmed air press -> declined"},
        };
        runMionCases(mion.moves, cases, std::size(cases));

        // The boosted form needs a contact, and re-enters a row the ordinary gate
        // refuses unless the current row is already in the ordinary combo set.
        const TableCase boosted[] = {
            {0, 0, 0, true, false, 0, 0, -1, "boosted without contact -> declined", true, 0},
            {0, 0, 0, true, false, 0, -1, 310, "boosted back input -> 310", true, 1},
            {0, 0, 0, true, false, 1, 0, 312, "boosted lateral input -> 312", true, 1},
            {0, 329, 0, true, false, 0, 0, 340, "boosted landing -> 340", true, 1},
            {0, 0, 0, true, false, 0, 0, 300, "boosted neutral -> 300", true, 1},
            {0, 0, 0, false, false, 0, 0, 320, "boosted airborne -> 320", true, 1},
        };
        runMionCases(mion.moves, boosted, std::size(boosted));

        // The `state != <row>` half of the boosted pair only matters when the ordinary
        // gate refuses: with row 310's cancel threshold above the target priority the
        // boosted branch must skip 310 (and the neutral fallback admits 300), while the
        // air branch has no fallback and declines 320 outright.
        Fixture hold310(2, TableShape{0, -1, 310}, {312}, 0, 1);
        if (hold310.ok) {
            const TableCase held[] = {
                {0, 310, 0, true, false, 0, -1, 300,
                 "boosted skips the held 310 and admits 300 instead", true, 1},
            };
            runMionCases(hold310.moves, held, std::size(held));
        }
        Fixture hold320(2, TableShape{0, -1, 320}, {312}, 0, 1);
        if (hold320.ok) {
            const TableCase held[] = {
                {0, 320, 0, false, false, 0, 0, -1,
                 "boosted cannot re-enter 320 while the gate refuses", true, 1},
            };
            runMionCases(hold320.moves, held, std::size(held));
        }
    }

    section("admission table — recovered dispatcher branches");
    {
        Fixture full(1);
        if (!full.ok) { check(false, "synthetic table parses"); return 1; }
        const TableCase cases[] = {
            {0, 0, 0, true, true, 0, 0, 300, "idle neutral -> 300"},
            {0, 10, 0, true, true, 0, 0, 300, "walk neutral -> 300"},
            {0, 20, 0, true, true, 0, 0, 330, "forward dash -> 330"},
            {0, 23, 0, true, true, 0, 0, 331, "left dash -> 331"},
            {0, 24, 0, true, true, 0, 0, 331, "right dash -> 331"},
            {0, 27, 0, true, true, 0, 0, 300, "back dash neutral -> 300"},
            {0, 0, 0, true, true, 0, -1, 310, "back input -> 310"},
            {0, 0, 0, true, true, 1, 0, 311, "lateral input -> 311"},
            {0, 20, 0, true, true, 0, -1, 330, "dash branch outranks the kick"},
            {0, 20, 0, true, true, 1, 0, 331, "lateral during forward dash -> 331"},
            {0, 23, 0, true, true, 0, -1, 330, "back during side dash -> 330"},
            {0, 0, 0, true, false, 0, 0, -1, "non-actionable idle declines"},
            {0, 300, 0, true, true, 0, 0, 301, "w0 chain 300 -> 301"},
            {1, 300, 0, true, true, 0, 0, 301, "w1 chain 300 -> 301"},
            {2, 300, 0, true, true, 0, 0, -1, "w2 has no chain out of 300"},
            {0, 301, 0, true, true, 0, 0, 302, "w0 chain 301 -> 302"},
            {1, 301, 0, true, true, 0, 0, 300, "w1 has no 302: restart 300"},
            {2, 301, 0, true, true, 0, 0, 300, "w2 restart 300"},
            {0, 302, 0, true, true, 0, 0, 300, "302 cycles back to 300"},
            {0, 300, 0, true, true, 1, 0, 311, "lateral input outranks the chain"},
            {0, 300, 0, true, false, 0, 0, -1, "no 0x100 window: chain declines"},
            {0, 329, 0, true, true, 0, 0, 340, "dash-recovery source -> 340"},
            {1, 333, 0, true, true, 0, 0, 340, "recovery source -> 340"},
            {0, 44, 0, true, true, 0, 0, 340, "air-fall source -> 340"},
            {2, 329, 0, true, true, 0, 0, 300, "w2 has no 340 route"},
            {0, 340, 0, true, true, 0, 0, 341, "w0 landing followup -> 341"},
            {1, 340, 0, true, true, 0, 0, 300, "w1 has no 341"},
            {2, 340, 0, true, true, 0, 0, 300, "w2 has no 341"},
            {0, 41, 0, false, true, 0, 0, 320, "ordinary air -> 320"},
            {1, 42, 0, false, true, 0, 0, 320, "falling air -> 320"},
            {2, 41, 0, false, true, 0, 0, 320, "w2 ordinary air -> 320"},
            {0, 30, 0, false, true, 0, 0, 332, "w0 air-dash phase 0 -> 332"},
            {1, 30, 1, false, true, 0, 0, 332, "w1 air-dash phase 1 -> 332"},
            {2, 30, 0, false, true, 0, 0, 320, "w2 has no dive: 320"},
            {0, 30, 2, false, true, 0, 0, 320, "past the dash phase gate: 320"},
            {0, 41, 0, false, false, 0, 0, -1, "non-actionable air declines"},
            {2, 0, 0, true, true, 0, -1, 310, "w2 may ENTER 310"},
            {2, 310, 0, true, true, 0, -1, 300, "w2 may not RE-ENTER 310"},
            {2, 0, 0, true, true, 1, 0, 311, "w2 may ENTER 311"},
            {2, 311, 0, true, true, 1, 0, 300, "w2 may not RE-ENTER 311"},
            {2, 27, 0, true, true, 0, -1, 310, "w2 back dash + back -> 310"},
            {1, 0, 0, true, true, 0, -1, 310, "w1 back kick"},
        };
        runTableCases(full.moves, cases, sizeof cases / sizeof cases[0]);
    }
    {
        section("admission table — gates and missing rows");
        TableShape blocked; blocked.idleThreshold = 100;
        Fixture gateFailed(1, blocked);
        const TableCase declined[] = {
            {0, 0, 0, true, true, 0, 0, -1, "failed neutral gate declines"},
        };
        runTableCases(gateFailed.moves, declined, 1);
        TableShape noKick; noKick.dropRow = 310;
        Fixture kickless(1, noKick);
        const TableCase fallback[] = {
            {0, 0, 0, true, true, 0, -1, 300, "missing 310 row falls to 300"},
        };
        runTableCases(kickless.moves, fallback, 1);
    }

    section("Fighter wiring — synthetic input edges (Rena+0)");
    {
        Fixture fx(1);
        input::PlayerState in{};

        in = pressWith(input::Action::AttackA); tick(fx.make(), in);
        checkInt(300, fx.fighters.back()->attack_move_id(), "idle press selects 300");

        in = pressWith(input::Action::AttackA, input::Action::Down); tick(fx.make(), in);
        checkInt(310, fx.fighters.back()->attack_move_id(), "back-held press selects 310");

        in = pressWith(input::Action::AttackA, input::Action::Right); tick(fx.make(), in);
        checkInt(311, fx.fighters.back()->attack_move_id(), "lateral-held press selects 311");

        Fighter& dash = fx.make();
        doubleTap(dash, input::Action::Up);
        in = pressWith(input::Action::AttackA); tick(dash, in);
        checkInt(330, dash.attack_move_id(), "forward-dash attack selects 330");

        Fighter& dashSide = fx.make();
        doubleTap(dashSide, input::Action::Up);
        in = pressWith(input::Action::AttackA, input::Action::Right); tick(dashSide, in);
        checkInt(331, dashSide.attack_move_id(), "lateral during forward dash selects 331");

        Fighter& side = fx.make();
        doubleTap(side, input::Action::Left);
        in = pressWith(input::Action::AttackA); tick(side, in);
        checkInt(331, side.attack_move_id(), "side-dash attack selects 331");

        Fighter& sideBack = fx.make();
        doubleTap(sideBack, input::Action::Left);
        in = pressWith(input::Action::AttackA, input::Action::Down); tick(sideBack, in);
        checkInt(330, sideBack.attack_move_id(), "back-held side dash selects 330");

        Fighter& air = fx.make();
        in = pressWith(input::Action::Jump); tick(air, in);
        in.down[input::Action::Jump] = false;
        for (int i = 0; i < 12; ++i) tick(air, in);
        check(air.state() == FighterState::Jump, "fighter is airborne");
        in = pressWith(input::Action::AttackA); tick(air, in);
        checkInt(320, air.attack_move_id(), "ordinary air attack selects 320");

        Fighter& dive = fx.make();
        in = pressWith(input::Action::Jump); tick(dive, in);
        in.down[input::Action::Jump] = false;
        for (int i = 0; i < 12; ++i) tick(dive, in);
        doubleTap(dive, input::Action::Up);
        check(dive.state() == FighterState::Run && dive.air_dash_context(),
              "air dash entered row 30");
        in = pressWith(input::Action::AttackA); tick(dive, in);
        checkInt(332, dive.attack_move_id(), "air-dash attack selects 332");
    }

    section("Fighter wiring — chains through the dispatcher");
    {
        Fixture w0(1), w1(3), w2(33);
        auto chainCycle = [](Fixture& fx, const int* expected, int count, const char* name) {
            Fighter& f = fx.make();
            input::PlayerState press{};
            press.down[input::Action::AttackA] = true;
            tick(f, press);
            press.down[input::Action::AttackA] = false;
            for (int i = 0; i < count; ++i) {
                // Release one tick, press the next: the 0x100 window of the
                // synthetic chain rows is open from entry.
                tick(f, press);
                press.down[input::Action::AttackA] = true;
                tick(f, press);
                checkInt(expected[i], f.attack_move_id(), name);
                press.down[input::Action::AttackA] = false;
            }
        };
        const int w0Chain[] = {301, 302, 300};
        chainCycle(w0, w0Chain, 3, "w0 chain 300->301->302->300");
        const int w1Chain[] = {301, 300};
        chainCycle(w1, w1Chain, 2, "w1 chain 300->301->300 (no 302)");

        Fighter& c = w2.make();
        input::PlayerState press{};
        press.down[input::Action::AttackA] = true;
        tick(c, press);
        press.down[input::Action::AttackA] = false;
        for (int i = 0; i < 6; ++i) {
            tick(c, press);
            press.down[input::Action::AttackA] = true;
            tick(c, press);
            checkInt(300, c.attack_move_id(), "w2 stays in 300 (no chain)");
            press.down[input::Action::AttackA] = false;
        }
    }

    // A declined press is a no-op through the real Fighter input path, not a
    // legacy-swing fallback: FUN_00445ee0's rejected branches take no action.
    // Each case presses through Fighter::update's input dispatch and asserts the
    // previous action, its animation binding and its timeline all survive.
    section("Fighter wiring — rejected admission preserves the action");
    {
        // Failed priority/cancel gate: row 0's cancel threshold (100) exceeds
        // every candidate row's priority (10), so the idle press declines.
        {
            TableShape shape; shape.idleThreshold = 100;
            Fixture gateFailed(1, shape);
            Fighter& f = gateFailed.make();
            const int idleSet = f.anim_set_index();
            const int elapsedIdle = f.phase_elapsed();
            input::PlayerState in = pressWith(input::Action::AttackA);
            tick(f, in);
            check(f.state() == FighterState::Idle, "declined press keeps Idle");
            check(f.attack_move_id() < 0, "declined press selects no move");
            check(!f.pending_swing_start(), "declined press arms no swing edge");
            check(!f.anim_fallback() && f.anim_set_index() == idleSet,
                  "declined press leaves the bound idle clip alone");
            check(!f.aerial_attack(), "declined press leaves aerial metadata clear");
            check(f.phase_elapsed() == elapsedIdle + 1,
                  "declined press advances the idle timeline by exactly one tick");
            in.down[input::Action::AttackA] = false;
            tick(f, in);
            check(f.state() == FighterState::Idle && f.phase_elapsed() == elapsedIdle + 2 &&
                  !f.pending_swing_start(),
                  "the tick after a decline advances normally");
        }
        // Missing destination row: the table ships no row 300 at all.
        {
            TableShape shape; shape.dropRow = 300;
            Fixture rowless(1, shape);
            Fighter& f = rowless.make();
            const int idleSet = f.anim_set_index();
            input::PlayerState in = pressWith(input::Action::AttackA);
            tick(f, in);
            check(f.state() == FighterState::Idle, "missing destination row declines");
            check(f.attack_move_id() < 0 && !f.pending_swing_start(),
                  "missing row arms neither move nor swing");
            check(!f.anim_fallback() && f.anim_set_index() == idleSet,
                  "missing row never binds a fallback clip");
            in.down[input::Action::AttackA] = false;
            tick(f, in);
            check(f.state() == FighterState::Idle, "still Idle after the declined tick");
        }
        // Positive control on the same wiring: with the gate passing, the press
        // still enters the expected attack, binds its own clip and arms the swing.
        {
            Fixture fine(1);
            Fighter& f = fine.make();
            input::PlayerState in = pressWith(input::Action::AttackA);
            tick(f, in);
            check(f.state() == FighterState::AttackA && f.attack_move_id() == 300,
                  "admitted press still enters AttackA on row 300");
            check(f.pending_swing_start(), "admitted press arms the swing edge");
            check(!f.anim_fallback() && f.anim_set_index() >= 0,
                  "admitted press binds the move's own clip");
        }
        // Declined AIR press (falling row 42's gate blocks 320) must not touch
        // the Rena+0 air-attack facing rule or the aerial-attack metadata, and
        // must leave the jump's clip and timeline running.
        {
            TableShape shape; shape.blockedAirRow = 42;
            Fixture airBlocked(1, shape);
            Fighter& f = airBlocked.make();
            Fighter& foe = airBlocked.make();
            foe.reset(glm::vec3(1000.f, 0.f, 0.f), 0.f);  // bearing +pi/2 from the fighter
            input::PlayerState in = pressWith(input::Action::Jump);
            tick(f, in);
            in.down[input::Action::Jump] = false;
            // 16 ticks: vy = 720 - 1800*16/64 = 270 < 360, so the air chain sits on
            // the falling row 42 (its phase-0 clip is set 20 in this table) — the
            // row whose threshold blocks the 320 gate.
            for (int i = 0; i < 16; ++i) tick(f, in);
            check(f.state() == FighterState::Jump && f.anim_set_index() == 20,
                  "air fixture is airborne on the falling row");
            const float facingBefore = f.facing_yaw();
            const int airSet = f.anim_set_index();
            const int elapsedBefore = f.phase_elapsed();
            in = pressWith(input::Action::AttackA);
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);  // opponent present: inputFacing is +pi/2
            check(f.state() == FighterState::Jump, "declined air press keeps the jump");
            check(f.attack_move_id() < 0 && !f.pending_swing_start(),
                  "declined air press arms nothing");
            check(!f.aerial_attack(), "declined air press leaves aerial metadata clear");
            check(std::abs(std::remainder(f.facing_yaw() - facingBefore,
                                          glm::two_pi<float>())) < 1e-5f,
                  "declined air press keeps the body yaw (no facing snap to the target)");
            check(!f.anim_fallback() && f.anim_set_index() == airSet,
                  "declined air press leaves the air clip bound");
            check(f.phase_elapsed() == elapsedBefore + 1,
                  "declined air press advances the jump timeline by exactly one tick");
        }
        // Chain requests get the same contract: a w2 chain press inside row 300
        // (no 301 family for the weapon) declines without disturbing the running
        // attack's move, phase, clip or timeline.
        {
            Fixture w2(33);
            Fighter& f = w2.make();
            input::PlayerState press{};
            press.down[input::Action::AttackA] = true;
            tick(f, press);
            press.down[input::Action::AttackA] = false;
            checkInt(300, f.attack_move_id(), "w2 enters row 300 before the chain press");
            check(f.take_swing_start(), "the entry edge armed once (drained here as Match would)");
            const int setBefore = f.anim_set_index();
            const int phaseBefore = f.move_phase();
            for (int i = 0; i < 3; ++i) tick(f, press);  // let the row's clock run
            const int elapsedBefore = f.phase_elapsed();
            press.down[input::Action::AttackA] = true;
            tick(f, press);
            check(f.state() == FighterState::AttackA && f.attack_move_id() == 300,
                  "declined chain press keeps the running attack");
            check(f.move_phase() == phaseBefore && f.anim_set_index() == setBefore &&
                  !f.anim_fallback(), "declined chain press preserves phase and clip");
            check(!f.pending_swing_start(),
                  "declined chain press arms no second swing edge");
            check(f.phase_elapsed() == elapsedBefore + 1,
                  "declined chain press advances the timeline by exactly one tick");
            press.down[input::Action::AttackA] = false;
            tick(f, press);
            check(f.state() == FighterState::AttackA,
                  "the tick after a declined chain stays in the attack");
        }
    }

    // The recovered attack-state movement bodies, driven through real input on
    // synthetic timelines whose phase periods land inside the horizon. Expected
    // values are transcribed from the Ginkiha execution headers cross-checked
    // with FUN_0043ffc0/448220/438310, never read back from the implementation.
    section("attack-state movement — profiles, vertical channel, landings");
    {
        // 300 (weapon 0): the distance-switched lunge and the phase walk.
        {
            Fixture fx(1);
            fx.setTicks = {{24, 6}};  // 300's phase-0 set: the windup ends fast
            Fighter& f = fx.make();
            Fighter& foe = fx.make();
            foe.reset(glm::vec3(900.f, 0.f, 0.f), 0.f);  // 810000 >= 640000: far
            input::PlayerState in = pressWith(input::Action::AttackA);
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            checkInt(300, f.attack_move_id(), "movement fixture enters 300");
            check(std::abs(f.move_speed() - 15.f) < 0.01f,
                  "300 lunge reads 15 against a far target (>= 640000)");
            Fighter& near = fx.make();
            Fighter& nearFoe = fx.make();
            nearFoe.reset(glm::vec3(500.f, 0.f, 0.f), 0.f);  // 250000 < 640000
            input::PlayerState nin = pressWith(input::Action::AttackA);
            input::compute_edges(nin);
            near.update(&nin, &nearFoe, 1.0 / 64.0);
            check(std::abs(near.move_speed() - 25.f) < 0.01f,
                  "300 lunge reads 25 against a near target (< 640000)");
            // The phase walk: period-driven 0 -> 1, then the approach exit into 2.
            in.down[input::Action::AttackA] = false;
            for (int i = 0; i < 30 && f.move_phase() != 2; ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
            }
            check(f.move_phase() == 2, "300 reaches phase 2 (windup period then approach exit)");
            const float bleed = f.move_speed();
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            check(std::abs(f.move_speed() - (bleed - 1.5f)) < 0.01f,
                  "300 phase 2 bleeds 1.5 a tick");
        }
        // 310 (weapon 0): the phase walk and the contact jump-cancel.
        {
            Fixture fx(1);
            fx.setTicks = {{33, 6}};  // 310's phase-0 set
            Fighter& f = fx.make();
            Fighter& foe = fx.make();
            foe.reset(glm::vec3(300.f, 0.f, 0.f), 0.f);
            input::PlayerState in = pressWith(input::Action::AttackA, input::Action::Down);
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            checkInt(310, f.attack_move_id(), "back-held press enters 310");
            check(std::abs(f.move_speed() - 30.f) < 0.01f, "310 enters with speed 30");
            in.down[input::Action::AttackA] = false;
            in.down[input::Action::Down] = false;
            for (int i = 0; i < 20 && f.move_phase() != 2; ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
            }
            check(f.move_phase() == 2, "310 walks phases 0-1-2 (phase 1 exits on its tick)");
            for (int i = 0; i < 15; ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
            }
            // A connected hit with jump held past frame 12 leaves the kick.
            f.note_melee_hit(0);
            in.down[input::Action::Jump] = true;
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            check(f.state() == FighterState::Jump && f.airborne(),
                  "310 jump-cancels into the air chain on contact + held jump");
        }
        // 311 (weapon 0): the entry rush and its decay.
        {
            Fixture fx(1);
            Fighter& f = fx.make();
            Fighter& foe = fx.make();
            foe.reset(glm::vec3(300.f, 0.f, 0.f), 0.f);
            input::PlayerState in = pressWith(input::Action::AttackA, input::Action::Right);
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            checkInt(311, f.attack_move_id(), "lateral press enters 311");
            checkFloat(20.f, f.move_speed(), 0.01f, "311 enters with speed 20");
            in.down[input::Action::AttackA] = false;
            in.down[input::Action::Right] = false;
            for (int i = 0; i < 5; ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
            }
            checkFloat(19.f, f.move_speed(), 0.05f, "311 bleeds 0.2 a tick after entry");
            for (int i = 0; i < 22; ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
            }
            check(f.move_speed() == 0.f, "311 stops fully at frame 25");
        }
        // 320 chase (weapon 0): strength latch, hang, arc, fall, 329 landing.
        {
            Fixture fx(1);
            fx.setTicks = {{39, 6}, {40, 30}};  // 320's windup/approach sets
            Fighter& f = fx.make();
            Fighter& foe = fx.make();
            foe.reset(glm::vec3(600.f, 0.f, 0.f), 0.f);
            input::PlayerState in = pressWith(input::Action::Jump);
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            in.down[input::Action::Jump] = false;
            for (int i = 0; i < 12; ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
            }
            in = pressWith(input::Action::AttackA);
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            checkInt(320, f.attack_move_id(), "airborne press enters the 320 chase");
            check(f.chase_strength() == 226, "chase latches 230 and decays 4 on the first tick");
            check(f.attack_gravity() == 0.f, "chase hangs (gravity 0) before phase 2");
            check(f.body_pivot_height() == 70.f, "chase leans with pivot 70");
            // The first arc tick steers to the target angle: the bearing from the
            // (elevated) fighter to the target plus the body's +10 bias, split at
            // strength 23 — computed here from the live geometry, not read back.
            const glm::vec3 toFoe = foe.position() - f.position();
            const float targetAngle = glm::degrees(std::atan2(
                static_cast<double>(toFoe.y),
                static_cast<double>(std::hypot(toFoe.x, toFoe.z)))) + 10.f;
            checkFloat(std::cos(glm::radians(targetAngle)) * 23.f, f.move_speed(), 0.3f,
                       "chase's first arc tick steers at the target angle");
            checkFloat(targetAngle + 20.f, f.body_pitch(), 1.5f,
                       "chase lean = flight angle + 20");
            const float startDistance = glm::distance(f.position(), foe.position());
            in.down[input::Action::AttackA] = false;
            for (int i = 0; i < 10; ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
            }
            check(glm::distance(f.position(), foe.position()) < startDistance - 100.f,
                  "the chase closes on the target");
            int phase2Tick = -1;
            for (int i = 0; i < 90 && phase2Tick < 0; ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
                if (f.move_phase() == 2) phase2Tick = i;
            }
            check(phase2Tick >= 0, "chase reaches phase 2 (approach exit or timeout)");
            for (int i = 0; i < 8; ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
            }
            check(f.attack_gravity() == 0.5f, "phase 2 falls at the body's 0.5 gravity");
            int landingTick = -1;
            for (int i = 0; i < 90 && landingTick < 0; ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
                if (!f.airborne() && f.attack_move_id() == 329) landingTick = i;
            }
            check(landingTick >= 0, "the chase lands into the 329 recovery");
            for (int i = 0; i < 6; ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
            }
            checkFloat(0.f, f.move_speed(), 0.f, "329 zeroes the motion");
            check(f.hyper_gauge() > 0.2f,
                  "329 refills the gauge (40/1000 a tick)");
        }
        // FUN_00438310:952-992: observe the executed clock and contact window, not
        // a duplicate ClockSeek rule (the C++ chase body owns the seek).
        {
            Fixture fx(33);
            fx.setTicks = {{39, 6}, {40, 30}};
            Fighter& f = fx.make();
            Fighter& foe = fx.make();
            foe.reset(glm::vec3(600.f, 0.f, 0.f), 0.f);
            input::PlayerState in = pressWith(input::Action::Jump);
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            in.down[input::Action::Jump] = false;
            for (int i = 0; i < 12; ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
            }
            in.down[input::Action::AttackA] = true;
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            checkInt(320, f.attack_move_id(), "Rena+2 jump/attack enters chase 320");
            in.down[input::Action::AttackA] = false;
            bool sawSeek = false, sawStrike = false, sawRecovery = false;
            bool contactMatches = true;
            for (int i = 0; i < 180 && !sawRecovery; ++i) {
                const int phase = f.move_phase();
                const int before = f.phase_elapsed();
                const int row = f.attack_move_id();
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
                if (row == 320 && phase == 2 && f.attack_move_id() == 320) {
                    const int executed = before == 13 ? 22 : before;
                    if (before == 13) {
                        sawSeek = true;
                        checkInt(23, f.phase_elapsed(),
                                 "Rena+2 chase seeks 13 to 22 then advances once");
                    }
                    const bool armed = executed >= 32 && executed <= 39;
                    contactMatches &= f.contact_disabled() != armed;
                    sawStrike |= armed;
                }
                sawRecovery = f.attack_move_id() == 329;
            }
            check(sawSeek, "Rena+2 chase naturally reaches the seek");
            check(sawStrike && contactMatches,
                  "Rena+2 chase contact arms only during executed ticks 32..39");
            check(sawRecovery, "Rena+2 complete chase reaches landing recovery 329");
        }
        // 330 (weapon 1): the hop — vertical 15, gravity .75, landing ends phase 3.
        {
            Fixture fx(3);
            fx.setTicks = {{44, 6}};  // 330's phase-0 set
            Fighter& f = fx.make();
            Fighter& foe = fx.make();
            foe.reset(glm::vec3(400.f, 0.f, 0.f), 0.f);
            doubleTap(f, input::Action::Up);
            input::PlayerState in = pressWith(input::Action::AttackA);
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            checkInt(330, f.attack_move_id(), "dash attack enters the 330 hop");
            in.down[input::Action::AttackA] = false;
            int hopTick = -1;
            for (int i = 0; i < 15 && hopTick < 0; ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
                if (f.move_phase() == 1) hopTick = i;
            }
            check(hopTick >= 0, "the hop's phase 1 arrives with the windup period");
            // The phase change lands at the END of that update; the hop's own rules
            // fire on phase 1's first full tick.
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            check(f.airborne(), "the hop lifts off (vertical 15)");
            check(f.attack_gravity() == 0.75f, "the hop falls at the body's 0.75 gravity");
            const float rise = f.position().y;
            for (int i = 0; i < 3; ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
            }
            check(f.position().y > rise, "the hop still rises on the following ticks");
            int landingTick = -1;
            for (int i = 0; i < 90 && landingTick < 0; ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
                if (!f.airborne() && f.move_phase() == 3) landingTick = i;
            }
            check(landingTick >= 0 && f.move_speed() == 0.f,
                  "the hop's landing ends phase 3 with the motion zeroed");
        }
        // 332 dive (weapon 0): launch arc, contact rebound into 334, 333 landing.
        {
            Fixture fx(1);
            fx.setTicks = {{51, 6}};  // 332's phase-0 set
            Fighter& f = fx.make();
            Fighter& foe = fx.make();
            foe.reset(glm::vec3(500.f, 0.f, 0.f), 0.f);
            input::PlayerState in = pressWith(input::Action::Jump);
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            in.down[input::Action::Jump] = false;
            for (int i = 0; i < 12; ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
            }
            doubleTap(f, input::Action::Up);
            check(f.state() == FighterState::Run && f.air_dash_context(),
                  "dive fixture enters the air dash");
            in = pressWith(input::Action::AttackA);
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            checkInt(332, f.attack_move_id(), "air-dash press enters the 332 dive");
            check(f.move_speed() == 0.f, "the dive starts from rest");
            in.down[input::Action::AttackA] = false;
            int diveTick = -1;
            for (int i = 0; i < 15 && diveTick < 0; ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
                if (f.move_phase() == 1) diveTick = i;
            }
            check(diveTick >= 0, "the dive's phase 1 arrives with the windup period");
            // The phase change lands at the END of that update; the launch fires on
            // phase 1's first full tick. The angle is the live elevation clamped
            // into [-20,-5] (the fixture dives from jump height), split at 25.
            const glm::vec3 launchGap = foe.position() - f.position();
            const float launchAngle = std::clamp(
                static_cast<float>(glm::degrees(std::atan2(
                    static_cast<double>(launchGap.y),
                    static_cast<double>(std::hypot(launchGap.x, launchGap.z))))),
                -20.f, -5.f);
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            checkFloat(std::cos(glm::radians(launchAngle)) * 25.f, f.move_speed(), 0.1f,
                       "dive launch splits cos(angle)*25 along the clamped angle");
            check(f.body_pivot_height() == 70.f && f.body_pitch() <= 0.f,
                  "dive leans with pivot 70 and a nonpositive pitch");
            // Contact inside the window rebounds into 334.
            f.note_melee_hit(0);
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            checkInt(334, f.attack_move_id(), "dive contact rebounds into 334");
            check(f.attack_gravity() == 0.35f && f.airborne(),
                  "the rebound rises at gravity 0.35");
            int fallTick = -1;
            for (int i = 0; i < 20 && fallTick < 0; ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
                if (f.move_phase() == 1) fallTick = i;
            }
            check(fallTick >= 0, "the rebound hands to its fall phase under 6 u/tick");
            int landingTick = -1;
            for (int i = 0; i < 90 && landingTick < 0; ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
                if (!f.airborne() && f.attack_move_id() == 333) landingTick = i;
            }
            check(landingTick >= 0, "the rebound's landing exits into the 333 recovery");

            // The dive's own landing (no contact): grounded in phase 1/2 hands to 333
            // (FUN_0043ffc0:1161-1165 — the guard is `0 < phase`, so phase 0 stays up).
            Fixture plain(1);
            plain.setTicks = {{51, 6}};
            Fighter& d = plain.make();
            Fighter& dfoe = plain.make();
            dfoe.reset(glm::vec3(500.f, 0.f, 0.f), 0.f);
            input::PlayerState dip = pressWith(input::Action::Jump);
            input::compute_edges(dip);
            d.update(&dip, &dfoe, 1.0 / 64.0);
            dip.down[input::Action::Jump] = false;
            for (int i = 0; i < 12; ++i) {
                input::compute_edges(dip);
                d.update(&dip, &dfoe, 1.0 / 64.0);
            }
            doubleTap(d, input::Action::Up);
            dip = pressWith(input::Action::AttackA);
            input::compute_edges(dip);
            d.update(&dip, &dfoe, 1.0 / 64.0);
            checkInt(332, d.attack_move_id(), "the plain dive fixture enters 332");
            dip.down[input::Action::AttackA] = false;
            int ownLanding = -1;
            for (int i = 0; i < 200 && ownLanding < 0; ++i) {
                input::compute_edges(dip);
                d.update(&dip, &dfoe, 1.0 / 64.0);
                if (!d.airborne() && d.attack_move_id() == 333) ownLanding = i;
            }
            check(ownLanding >= 0, "332's own landing exits into the 333 recovery");
        }
        // 300 (weapon 2): the standing spin — no approach speed, the phase-1 rush
        // at 45, and the double-speed clock through frames 16..28.
        {
            Fixture fx(33);
            fx.setTicks = {{24, 6}};  // 300's phase-0 set
            Fighter& f = fx.make();
            Fighter& foe = fx.make();
            foe.reset(glm::vec3(600.f, 0.f, 0.f), 0.f);
            input::PlayerState in = pressWith(input::Action::AttackA);
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            checkInt(300, f.attack_move_id(), "w2 neutral press enters the spin");
            check(f.move_speed() == 0.f, "the spin does not lunge at entry");
            in.down[input::Action::AttackA] = false;
            float rushSpeed = -1.f;
            for (int i = 0; i < 15 && rushSpeed < 0.f; ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
                if (f.move_phase() == 1 && f.move_speed() > 40.f) rushSpeed = f.move_speed();
            }
            check(rushSpeed > 42.9f && rushSpeed <= 43.01f,
                  "the spin's phase-1 rush reads 45, decaying 2 inside the same tick");
            bool sawDoubleClock = false;
            int previousElapsed = f.phase_elapsed();
            for (int i = 0; i < 40; ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
                const int elapsed = f.phase_elapsed();
                if (previousElapsed >= 15 && previousElapsed <= 28 && elapsed == previousElapsed + 2)
                    sawDoubleClock = true;
                previousElapsed = elapsed;
            }
            check(sawDoubleClock, "the spin's clock runs double through frames 16..28");
        }
    }

    section("shared-mechanism review — guard exits, windows, lean transform");
    {
        // (1) The guard-exit table. The expected values are the exhaustive
        // `FUN_0042c7b0() & 2` scan of the three handlers: 301/310/311/331/340 in
        // every weapon, 302/330 in weapons 0 and 2 only, and NO exit at all for
        // 300/320/329/332/333/334/341/350.
        struct GuardCase { int weapon, row, expected; };
        static const GuardCase kGuard[] = {
            {0,301,392},{0,302,392},{0,310,392},{0,311,392},{0,330,392},{0,331,392},{0,340,392},
            {0,300,-1},{0,320,-1},{0,329,-1},{0,332,-1},{0,333,-1},{0,334,-1},{0,341,-1},{0,350,-1},
            {1,301,392},{1,310,392},{1,311,392},{1,331,392},{1,340,392},
            {1,302,-1},{1,330,-1},{1,320,-1},{1,332,-1},{1,350,-1},
            {2,301,392},{2,302,392},{2,310,392},{2,311,392},{2,330,392},{2,331,392},{2,340,392},
            {2,300,-1},{2,320,-1},{2,350,-1},
        };
        int guardMismatches = 0;
        for (const GuardCase& c : kGuard)
            if (gameplay::rena_guard_exit_row(c.weapon, c.row) != c.expected) ++guardMismatches;
        checkInt(0, guardMismatches, "guard-exit table matches the 35-site &2 scan");

        // (2) The rule-window contracts corrected by this review, asserted against
        // the shipped programs. The numbers are the bodies' own guards: the 350
        // stall spans 0<tick<10 on the update parity, the 403/409/469 recoveries
        // zero every tick with no guard at all, 392 walks its scratch past 20 into
        // phase 1, 320 arms the contact volume only in phase 2 ticks 0..7, weapon
        // 0's 350 never re-arms it, and 450 re-binds attachment slot 0 to model 2.
        Fixture w0(1), w1(3), w2(33);
        check(w0.ok && w1.ok && w2.ok, "three weapon fixtures parse");
        const gameplay::MoveProgram* p0 = gameplay::move_program(&w0.moves);
        const gameplay::MoveProgram* p1 = gameplay::move_program(&w1.moves);
        const gameplay::MoveProgram* p2 = gameplay::move_program(&w2.moves);
        check(p0 != nullptr && p1 != nullptr && p2 != nullptr,
              "three weapon programs resolve");
        const auto findRule = [](const gameplay::MoveProgram* program, int move,
                                 gameplay::MoveOp op, int phase,
                                 int first = -999) -> const gameplay::MoveRule* {
            if (!program) return nullptr;
            for (size_t i = 0; i < program->count; ++i) {
                const gameplay::MoveRule& r = program->rules[i];
                if (r.move == move && r.operation == op && r.phase == phase &&
                    (first == -999 || r.first == first))
                    return &r;
            }
            return nullptr;
        };
        const auto recoveryEveryTick = [&](const gameplay::MoveProgram* program, int move,
                                           const char* name) {
            bool ok = true;
            for (gameplay::MoveOp op : {gameplay::MoveOp::Speed, gameplay::MoveOp::Vertical,
                                        gameplay::MoveOp::Gravity}) {
                const gameplay::MoveRule* r = findRule(program, move, op, -1);
                ok = ok && r && r->first == 0 && r->last == 9999;
            }
            check(ok, name);
        };
        recoveryEveryTick(p0, 403, "w0 403 zeroes motion every tick");
        recoveryEveryTick(p0, 409, "w0 409 zeroes motion every tick");
        recoveryEveryTick(p0, 469, "w0 469 zeroes motion every tick");
        recoveryEveryTick(p1, 403, "w1 403 zeroes motion every tick");
        recoveryEveryTick(p1, 469, "w1 469 zeroes motion every tick");
        recoveryEveryTick(p2, 403, "w2 403 zeroes motion every tick");
        recoveryEveryTick(p2, 469, "w2 469 zeroes motion every tick");
        const gameplay::MoveRule* stall = findRule(p0, 350, gameplay::MoveOp::ClockSkip, 0);
        check(stall && stall->first == 1 && stall->last == 9 &&
                  (stall->gate & gameplay::kGateCounterMod) != 0 && stall->gateValue == 2,
              "350's stall runs body ticks 1..9 on the update parity");
        const gameplay::MoveRule* start = findRule(p0, 350, gameplay::MoveOp::CounterSet, 0, 0);
        const gameplay::MoveRule* settle = findRule(p0, 350, gameplay::MoveOp::CounterSet, 0, 10);
        check(start && start->value == 1.f && settle && settle->value == 0.f,
              "350's alternator starts at 1 and settles to 0 at tick 10");
        for (const auto* program : {p0, p1, p2}) {
            const gameplay::MoveRule* exit = findRule(program, 392, gameplay::MoveOp::PhaseExit, 0);
            check(exit && (exit->gate & gameplay::kGateCounterAbove) != 0 &&
                      exit->gateValue2 == 20,
                  "392 hands to phase 1 past scratch 20");
            // Weapons 0/1 cut contact throughout phases 0/1 and from phase-2 frame 8
            // (their bodies arm `tick < 8`); weapon 2's chase has its own phase-2 window,
            // frames 32..39, so its two rules bracket that instead (FUN_00438310:988-992).
            const bool w2 = program == p2;
            for (int phase = 0; phase < 3; ++phase) {
                const gameplay::MoveRule* cut =
                    findRule(program, 320, gameplay::MoveOp::ContactOff, phase);
                bool ok = false;
                if (phase == 0 || phase == 1) {
                    ok = cut && cut->first == 0 && cut->last == 9999;
                } else if (w2) {
                    ok = findRule(program, 320, gameplay::MoveOp::ContactOff, 2, 0) &&
                         findRule(program, 320, gameplay::MoveOp::ContactOff, 2, 40);
                } else {
                    ok = cut && cut->first == 8 && cut->last == 9999;
                }
                check(ok, w2 ? "320 (w2) cuts contact outside frames 32..39"
                             : "320 cuts contact outside the body's phase-2 0..7 window");
            }
        }
        const gameplay::MoveRule* w0hit = findRule(p0, 350, gameplay::MoveOp::ContactOff, -1);
        check(w0hit && w0hit->first == 0 && w0hit->last == 9999,
              "weapon 0's 350 never re-arms the contact volume");
        const gameplay::MoveRule* w2speed = findRule(p2, 402, gameplay::MoveOp::Speed, 0);
        check(w2speed && w2speed->first == 0 && w2speed->last == 9999,
              "w2 402 re-asserts speed 20 every phase-0 frame");
        const gameplay::MoveRule* w1prop = findRule(p1, 450, gameplay::MoveOp::PropModel, -1);
        check(w1prop && w1prop->value == 0.f && w1prop->second == 2.f,
              "w1 450 binds slot 0 to item model 2");
        const gameplay::MoveRule* w2ring = nullptr;
        for (size_t i = 0; p2 && i < p2->count; ++i)
            if (p2->rules[i].move == 402 && p2->rules[i].operation == gameplay::MoveOp::Launch &&
                p2->rules[i].repeats == 10)
                w2ring = &p2->rules[i];
        check(w2ring && w2ring->phase == 1, "w2 402's ring fires ten requests");

        // The mobile/dash shot bodies' own windows (FUN_0043ffc0's case bodies): the
        // prop unbind happens the tick AFTER the recorded threshold, and each row's
        // approach rate and bleed window are the handler's own numbers — 401 bleeds
        // 0.25 in phase 0 (1938-1941), 405/406 approach 15 for ticks 0..9 (2111/2166)
        // and bleed 0.5 only after tick 10 (2118/2173), 407 turns 9 early plus 15 for
        // every phase-0 tick (2221/2232), and 401/404..408 unbind after tick 13
        // (1934/1984/2059/2114/2169/2224/2282).
        const gameplay::MoveRule* w0bleed401 =
            findRule(p0, 401, gameplay::MoveOp::Decelerate, 0);
        const gameplay::MoveRule* w0hide401 = findRule(p0, 401, gameplay::MoveOp::Hide, -1, 14);
        check(w0bleed401 && w0bleed401->first == 0 && w0bleed401->value == 0.25f &&
              w0hide401 && w0hide401->value == 0.f,
              "w0 401 bleeds 0.25 a phase-0 tick and unbinds from tick 14");
        const gameplay::MoveRule* w0turn405 = findRule(p0, 405, gameplay::MoveOp::Turn, 0, 0);
        const gameplay::MoveRule* w0bleed405 =
            findRule(p0, 405, gameplay::MoveOp::Decelerate, 0);
        check(w0turn405 && w0turn405->last == 9 && w0turn405->value == 15.f,
              "w0 405 approaches 15 degrees for ticks 0..9");
        check(w0bleed405 && w0bleed405->first == 11 && w0bleed405->value == 0.5f,
              "w0 405 bleeds 0.5 a tick only after tick 10");
        // Both 407 turn rules start at tick 0, so tell them apart by their last tick.
        const gameplay::MoveRule* w0turn407a = nullptr;
        const gameplay::MoveRule* w0turn407b = nullptr;
        for (size_t i = 0; p0 && i < p0->count; ++i) {
            const gameplay::MoveRule& r = p0->rules[i];
            if (r.move != 407 || r.operation != gameplay::MoveOp::Turn || r.phase != 0)
                continue;
            if (r.last == 9) w0turn407a = &r;
            if (r.last == 9999) w0turn407b = &r;
        }
        check(w0turn407a && w0turn407a->value == 9.f && w0turn407b &&
              w0turn407b->value == 15.f,
              "w0 407 turns 9 degrees early and 15 for every later phase-0 tick");
        const gameplay::MoveRule* w0hide408 = findRule(p0, 408, gameplay::MoveOp::Hide, -1, 14);
        check(w0hide408 != nullptr, "w0 408 unbinds its props from tick 14");

        // The melee bodies' own entry snaps and contact/ribbon spans: 300/310/311 all
        // snap 180 degrees at their entry (FUN_0043ffc0:590/762/829), 310's window is
        // phase-2 ticks 5..7 (line 791) and 341's is phase-1 ticks 0..19 (line 1365).
        const gameplay::MoveRule* w0snap310 = findRule(p0, 310, gameplay::MoveOp::Turn, 0, 0);
        check(w0snap310 && w0snap310->value == 180.f,
              "w0 310 snaps 180 degrees on entry before its 20-degree approach");
        const gameplay::MoveRule* w0active310 = findRule(p0, 310, gameplay::MoveOp::Active, -1, 5);
        check(w0active310 && w0active310->last == 7,
              "w0 310's contact/ribbon span is phase-2 ticks 5..7");
        const gameplay::MoveRule* w0snap311 = findRule(p0, 311, gameplay::MoveOp::Turn, -1, 0);
        check(w0snap311 && w0snap311->value == 180.f &&
              w0snap311->last == 0,
              "w0 311 snaps 180 degrees at tick 0");
        const gameplay::MoveRule* w0active341 = findRule(p0, 341, gameplay::MoveOp::Active, 1, 0);
        check(w0active341 && w0active341->last == 19,
              "w0 341's contact/ribbon span is phase-1 ticks 0..19");

        // Weapons 1 and 2's own body spans (FUN_00448220 / FUN_00438310): each row's
        // `(tick < N) || (M < tick)` clears the prop latch, so the else arms it. Every
        // window is tick-only (no phase guard), which is why `-1` is the phase.
        const auto spanAt = [](const gameplay::MoveProgram* program, int move, int first)
            -> const gameplay::MoveRule* {
            if (!program) return nullptr;
            for (size_t i = 0; i < program->count; ++i) {
                const gameplay::MoveRule& r = program->rules[i];
                if (r.move == move && r.operation == gameplay::MoveOp::Active &&
                    r.first == first)
                    return &r;
            }
            return nullptr;
        };
        const gameplay::MoveRule* w1span301 = spanAt(p1, 301, 10);
        const gameplay::MoveRule* w1span310 = spanAt(p1, 310, 5);
        const gameplay::MoveRule* w1span311 = spanAt(p1, 311, 12);
        check(w1span301 && w1span301->last == 16 &&
              w1span310 && w1span310->last == 7 &&
              w1span311 && w1span311->last == 18,
              "w1 301/310/311 arm their props for 10..16 / 5..7 / 12..18");
        // Weapon 1's own entry snaps and tick-0 steps (FUN_00448220:736-742, 795-802,
        // 1681-1690, 1738-1746). Both 400 and 401 turn 20 for ticks 0..14 and add a
        // second step at tick 0 — 15 and 5 respectively — which the single rule missed.
        const auto turnAt = [](const gameplay::MoveProgram* program, int move, int phase,
                               int first) -> const gameplay::MoveRule* {
            if (!program) return nullptr;
            for (size_t i = 0; i < program->count; ++i) {
                const gameplay::MoveRule& r = program->rules[i];
                if (r.move == move && r.operation == gameplay::MoveOp::Turn &&
                    r.phase == phase && r.first == first)
                    return &r;
            }
            return nullptr;
        };
        const gameplay::MoveRule* w1snap310 = turnAt(p1, 310, 0, 0);
        const gameplay::MoveRule* w1snap311 = turnAt(p1, 311, -1, 0);
        // Both tick-0 rules share first == 0 with the 0..14 rule, so pick by `last`.
        const auto turnEndingAt = [](const gameplay::MoveProgram* program, int move,
                                     int last) -> const gameplay::MoveRule* {
            if (!program) return nullptr;
            for (size_t i = 0; i < program->count; ++i) {
                const gameplay::MoveRule& r = program->rules[i];
                if (r.move == move && r.operation == gameplay::MoveOp::Turn &&
                    r.phase == -1 && r.last == last)
                    return &r;
            }
            return nullptr;
        };
        const gameplay::MoveRule* w1step400 = turnEndingAt(p1, 400, 0);
        const gameplay::MoveRule* w1step401 = turnEndingAt(p1, 401, 0);
        check(w1snap310 && w1snap310->value == 180.f,
              "w1 310 snaps 180 degrees on its phase-0 entry");
        check(w1snap311 && w1snap311->value == 180.f && w1snap311->last == 0,
              "w1 311 snaps 180 degrees at its tick 0");
        check(w1step400 && w1step400->value == 15.f && w1step400->last == 0 &&
              w1step401 && w1step401->value == 5.f && w1step401->last == 0,
              "w1 400/401 add their own tick-0 step (15 / 5)");
        const gameplay::MoveRule* w2span310 = spanAt(p2, 310, 24);
        const gameplay::MoveRule* w2span311 = spanAt(p2, 311, 32);
        const gameplay::MoveRule* w2span330 = spanAt(p2, 330, 28);
        const gameplay::MoveRule* w2span331 = spanAt(p2, 331, 26);
        const gameplay::MoveRule* w2span340 = spanAt(p2, 340, 16);
        check(w2span310 && w2span310->last == 45 &&
              w2span311 && w2span311->last == 49 &&
              w2span330 && w2span330->last == 34 &&
              w2span331 && w2span331->last == 109 &&
              w2span340 && w2span340->last == 24,
              "w2 310/311/330/331/340 arm their props for their own frame spans");
        // A second, brace-aware pass over every FUN_00434b30 site (the first pass
        // missed the sites whose condition wraps across lines): weapon 1's 300 span is
        // phase-2 3..10 and its 330 is phase 0 from 11 plus all of phase 1; weapon 2's
        // 300 is phase-1 25..34 and its 341 is all of phase 1.
        const gameplay::MoveRule* w1span300 = spanAt(p1, 300, 3);
        const gameplay::MoveRule* w1span330a = spanAt(p1, 330, 11);
        const gameplay::MoveRule* w1span330b = spanAt(p1, 330, 0);
        const gameplay::MoveRule* w2span300 = spanAt(p2, 300, 25);
        const gameplay::MoveRule* w2span341 = spanAt(p2, 341, 0);
        check(w1span300 && w1span300->phase == 2 && w1span300->last == 10,
              "w1 300 arms its props for phase-2 frames 3..10");
        check(w1span330a && w1span330a->phase == 0 && w1span330a->last == 9999 &&
              w1span330b && w1span330b->phase == 1 && w1span330b->last == 19,
              "w1 330 arms phase 0 from frame 11 and all of phase 1");
        check(w2span300 && w2span300->phase == 1 && w2span300->last == 34,
              "w2 300 arms its props for phase-1 frames 25..34");
        check(w2span341 && w2span341->phase == 1 && w2span341->last == 19,
              "w2 341 arms its props for all of phase 1");
        // The chase's ribbon half: its contact span was already modeled through
        // ContactOff (phases 0/1 all, phase 2 from frame 8), so the armed window is
        // phase 2 frames 0..7 for weapons 0 and 1. Weapon 2's chase uses the different
        // 32..39 window and its phase placement is still unread, so it stays parked.
        const gameplay::MoveRule* w0chaseSpan = spanAt(p0, 320, 0);
        const gameplay::MoveRule* w1chaseSpan = spanAt(p1, 320, 0);
        check(w0chaseSpan && w0chaseSpan->phase == 2 && w0chaseSpan->last == 7,
              "w0 320 arms its props for phase-2 frames 0..7");
        check(w1chaseSpan && w1chaseSpan->phase == 2 && w1chaseSpan->last == 7,
              "w1 320 arms its props for phase-2 frames 0..7");
        // Weapon 2's chase reads the same shape with its own numbers: the clock JUMPS
        // 13 -> 22 (FUN_00438310:952-955), the approach turns 2 while the clock is under
        // 32 (957-959), the strike cue is at 32 (960), and the contact/ribbon window is
        // frames 32..39 (988-992) — not the 0..7 that had been copied from w0/w1.
        const gameplay::MoveRule* w2turn = findRule(p2, 320, gameplay::MoveOp::Turn, 2, 0);
        const gameplay::MoveRule* w2offEarly =
            findRule(p2, 320, gameplay::MoveOp::ContactOff, 2, 0);
        const gameplay::MoveRule* w2offLate =
            findRule(p2, 320, gameplay::MoveOp::ContactOff, 2, 40);
        const gameplay::MoveRule* w2chaseSpan = spanAt(p2, 320, 32);
        check(w2turn && w2turn->last == 31 && w2turn->value == 2.f,
              "w2 320 approaches 2 degrees while the clock is under 32");
        check(w2offEarly && w2offEarly->last == 31 && w2offLate && w2offLate->first == 40,
              "w2 320's contact is off outside frames 32..39");
        check(w2chaseSpan && w2chaseSpan->phase == 2 && w2chaseSpan->last == 39,
              "w2 320 arms its props for phase-2 frames 32..39");

        // The jumped clock keeps the two late windows where the body puts them.
        const gameplay::MoveRule* w2gravity =
            findRule(p2, 320, gameplay::MoveOp::Gravity, 2, 51);
        const gameplay::MoveRule* w2land =
            findRule(p2, 320, gameplay::MoveOp::LandExit, 2, 56);
        check(w2gravity && w2gravity->value == 0.5f,
              "w2 320's fall gravity starts at clock 51");
        check(w2land && w2land->value == 329.f,
              "w2 320's landing exit starts at clock 56");

        // (3) Behavioural: 320's contact volume is cut from the entry tick, before
        // phase 2 arms it (the body calls FUN_00434bd0 in every non-armed tick).
        {
            Fixture fx(1);
            fx.setTicks = {{39, 6}, {40, 30}};
            Fighter& f = fx.make();
            Fighter& foe = fx.make();
            foe.reset(glm::vec3(600.f, 0.f, 0.f), 0.f);
            input::PlayerState in = pressWith(input::Action::Jump);
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            in.down[input::Action::Jump] = false;
            for (int i = 0; i < 12; ++i) { input::compute_edges(in); f.update(&in, &foe, 1.0 / 64.0); }
            in = pressWith(input::Action::AttackA);
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            checkInt(320, f.attack_move_id(), "contact fixture enters the 320 chase");
            check(f.contact_disabled(), "320's phase 0 has the contact volume cut");

            // (4) The world transform, rebuilt independently from FUN_00420b30's
            // field roles (T(0,-pivot,0) * Rx(pitch) * Ry(yaw) * T(position+pivot),
            // donor actor_world_pose.hpp:14) from the fighter's public pose. The
            // earlier cut folded pitch and pivot into the Y angle and fails this.
            in.down[input::Action::AttackA] = false;
            for (int i = 0; i < 4; ++i) { input::compute_edges(in); f.update(&in, &foe, 1.0 / 64.0); }
            const glm::vec3 pos = f.position();
            const float pivot = f.body_pivot_height();
            const glm::mat4 expected =
                glm::translate(glm::mat4(1.f), pos + glm::vec3(0.f, pivot, 0.f)) *
                glm::rotate(glm::mat4(1.f), f.facing_yaw() + glm::pi<float>(),
                            glm::vec3(0.f, 1.f, 0.f)) *
                glm::rotate(glm::mat4(1.f), glm::radians(f.body_pitch()), glm::vec3(1.f, 0.f, 0.f)) *
                glm::translate(glm::mat4(1.f), glm::vec3(0.f, -pivot, 0.f));
            const glm::mat4 got = f.modelMatrix();
            float maxDiff = 0.f;
            for (int c = 0; c < 4; ++c)
                for (int r = 0; r < 4; ++r)
                    maxDiff = std::max(maxDiff, std::abs(expected[c][r] - got[c][r]));
            checkFloat(0.f, maxDiff, 1e-4f,
                       "model matrix is T(pivot)*Ry*Rx(pitch)*T(-pivot)");
            const glm::vec4 pivotWorld = got * glm::vec4(0.f, pivot, 0.f, 1.f);
            check(std::abs(pivotWorld.x - pos.x) < 1e-3f &&
                      std::abs(pivotWorld.y - (pos.y + pivot)) < 1e-3f &&
                      std::abs(pivotWorld.z - pos.z) < 1e-3f,
                  "the pivot height is the rotation center (its own point is fixed)");
            const glm::vec4 yAxis = got * glm::vec4(0.f, pivot + 1.f, 0.f, 1.f) - pivotWorld;
            check(std::abs(yAxis.y - std::cos(glm::radians(f.body_pitch()))) < 1e-3f,
                  "body pitch tilts the local Y axis (it is not a yaw term)");
            // The rig faces -Z, so the face direction is M*(0,0,-1). With the pitch as a
            // glm::rotate around +X its Y component is exactly sin(pitch) — the derivation
            // for the SIGN (donor tilt point map == glm Rx), and zero under the old
            // pitch-in-yaw fold, which is what makes this a regression guard rather than
            // a preference.
            const glm::vec3 face = glm::mat3(got) * glm::vec3(0.f, 0.f, -1.f);
            checkFloat(std::sin(glm::radians(f.body_pitch())), face.y, 1e-3f,
                       "the lean is a RotationX: the face rises by sin(pitch)");
        }

        // (5) The landing branch now covers shot rows too: an air tap that reaches
        // the ground hands to the 403 recovery instead of finishing its clip.
        {
            Fixture fx(1, {}, {400, 402, 403, 469}, 12);
            Fighter& f = fx.make();
            Fighter& foe = fx.make();
            foe.reset(glm::vec3(600.f, 0.f, 0.f), 0.f);
            input::PlayerState in = pressWith(input::Action::Jump);
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            in.down[input::Action::Jump] = false;
            for (int i = 0; i < 12; ++i) { input::compute_edges(in); f.update(&in, &foe, 1.0 / 64.0); }
            in = pressWith(input::Action::Shoot);
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            in.down[input::Action::Shoot] = false;
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            checkInt(402, f.shot_move_id(), "the air tap binds the 402 shot row");
            int landTick = -1;
            for (int i = 0; i < 400 && landTick < 0; ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
                if (!f.airborne()) landTick = i;
            }
            check(landTick >= 0, "the air tap reaches the ground");
            checkInt(403, f.shot_move_id(), "the air tap's landing enters the 403 recovery");
            for (int i = 0; i < 3; ++i) { input::compute_edges(in); f.update(&in, &foe, 1.0 / 64.0); }
            check(f.move_speed() == 0.f && f.attack_gravity() == 0.f,
                  "403 zeroes the carried motion and the fall (no tick guard)");
        }

        // (6) The melee voice/effect producer chain: 300's phase-2 entry queues voice
        // 1 and effect 60 through the same per-tick latch the scene drains. The
        // consumer mapping (audio cue table + effect catalog spawn) is the next
        // slice; this pins the recovered producer half so it cannot rot.
        {
            Fixture fx(1);
            fx.setTicks = {{24, 6}};
            Fighter& f = fx.make();
            Fighter& foe = fx.make();
            foe.reset(glm::vec3(900.f, 0.f, 0.f), 0.f);
            input::PlayerState in = pressWith(input::Action::AttackA);
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            checkInt(300, f.attack_move_id(), "cue fixture enters 300");
            in.down[input::Action::AttackA] = false;
            bool sawVoice = false, sawSe = false;
            for (int i = 0; i < 40 && !(sawVoice && sawSe); ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
                const auto voice = f.take_melee_voice();
                const auto sound = f.take_sound_effect();
                if (f.move_phase() == 2 && voice.event == 1) sawVoice = true;
                if (f.move_phase() == 2 && sound.id == 60) sawSe = true;
            }
            check(sawVoice, "300's phase-2 entry queues melee voice 1");
            check(sawSe, "300's phase-2 entry queues SE 60");
        }

        // (7) The boosted (special-gauge) admission: the awakened 350 is a TWO-LATCH
        // CHORD — `+0x284 && +0x288` (FUN_00445ee0:117-118), the melee latch plus the
        // second one the arming command also uses — with a hyper state armed and the
        // current row's chain window open. A lone attack press while armed is the
        // ORDINARY 300, and so is the chord without the armed state.
        {
            Fixture fx(1, {}, {350});
            Fighter& f = fx.make();
            Fighter& foe = fx.make();
            foe.reset(glm::vec3(300.f, 0.f, 0.f), 0.f);
            f.set_hypermode(gameplay::Hypermode::Oyashiro);
            f.set_hyper_gauge(1.f);
            input::PlayerState in;
            in.down[input::Action::Special] = true;
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            in.down[input::Action::Special] = false;
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            check(f.hyper_active(), "the boosted fixture arms the hyper state");
            // The chord: both latches held while the attack edge arrives.
            in.down[input::Action::Special] = true;
            in.down[input::Action::AttackA] = true;
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            checkInt(350, f.attack_move_id(), "the armed chord admits the 350 melee");

            // The 350 body's own presentation cues: an effect request at frame 7
            // (id 320 -> data/effect/032.dat) carrying the two rand%40-20 angles, and the
            // SE at frame 11 (FUN_0042c8b0(0x3d) -> data/se/061). The frame-7 beat runs
            // twice because the body's stall replays body ticks 1..9.
            in.down[input::Action::AttackA] = false;
            bool sawEffect = false, sawSe = false;
            for (int i = 0; i < 40 && !(sawEffect && sawSe); ++i) {
                input::compute_edges(in);
                f.update(&in, &foe, 1.0 / 64.0);
                const auto effect = f.take_effect();
                const auto sound = f.take_sound_effect();
                if (effect.id == 320)
                    sawEffect = effect.yaw >= -20.f && effect.yaw < 20.f &&
                                effect.pitch >= -20.f && effect.pitch < 20.f;
                if (sound.id == 61) sawSe = true;
            }
            check(sawEffect, "350's frame-7 beat requests effect 320 with its two draws");
            check(sawSe, "350's frame-11 beat requests SE 61");

            Fixture plain(1, {}, {350});
            Fighter& p = plain.make();
            Fighter& pfoe = plain.make();
            pfoe.reset(glm::vec3(300.f, 0.f, 0.f), 0.f);
            input::PlayerState plainIn = pressWith(input::Action::AttackA);
            input::compute_edges(plainIn);
            p.update(&plainIn, &pfoe, 1.0 / 64.0);
            checkInt(300, p.attack_move_id(),
                     "the same press without the armed state stays 300");

            // The chord's second latch is what separates the awakened row: an armed
            // fighter pressing the melee button ALONE takes the ordinary 300, because the
            // dispatcher's chord arm needs both latches.
            Fixture solo(1, {}, {350});
            Fighter& s = solo.make();
            Fighter& sfoe = solo.make();
            sfoe.reset(glm::vec3(300.f, 0.f, 0.f), 0.f);
            s.set_hypermode(gameplay::Hypermode::Oyashiro);
            s.set_hyper_gauge(1.f);
            input::PlayerState armIn;
            armIn.down[input::Action::Special] = true;
            input::compute_edges(armIn);
            s.update(&armIn, &sfoe, 1.0 / 64.0);
            armIn.down[input::Action::Special] = false;
            input::compute_edges(armIn);
            s.update(&armIn, &sfoe, 1.0 / 64.0);
            check(s.hyper_active(), "the solo fixture arms the hyper state");
            input::PlayerState soloIn = pressWith(input::Action::AttackA);
            input::compute_edges(soloIn);
            s.update(&soloIn, &sfoe, 1.0 / 64.0);
            checkInt(300, s.attack_move_id(),
                     "an armed lone attack press stays the ordinary 300");
        }

        // (8) The attacker-side guard exit driven through the real update: a guarded
        // connect on a row that carries the `& 2` branch hands the attacker to 392
        // (FUN_0043ffc0's 0x188 body), while 320 — which has no branch in any weapon —
        // keeps its row. The row table itself is asserted above; this is the behaviour.
        {
            Fixture fx(1, {}, {392});
            // 300 carries no `& 2` branch: a guarded connect there keeps the row.
            Fighter& f = fx.make();
            input::PlayerState press{};
            press.down[input::Action::AttackA] = true;
            tick(f, press);
            checkInt(300, f.attack_move_id(), "guard fixture enters 300");
            f.note_melee_hit(0, true);  // the strike met a guard (FUN_0042c7b0 bit 2)
            press.down[input::Action::AttackA] = false;
            tick(f, press);
            checkInt(300, f.attack_move_id(), "300 has no guard branch, so it keeps the row");

            // 301 does, so the same guarded connect hands the attacker to 392.
            Fighter& g = fx.make();
            input::PlayerState chain{};
            chain.down[input::Action::AttackA] = true;
            tick(g, chain);
            chain.down[input::Action::AttackA] = false;
            tick(g, chain);
            chain.down[input::Action::AttackA] = true;
            tick(g, chain);
            checkInt(301, g.attack_move_id(), "guard fixture chains into 301");
            g.note_melee_hit(0, true);
            chain.down[input::Action::AttackA] = false;
            tick(g, chain);
            checkInt(392, g.attack_move_id(),
                     "a guarded connect on 301 exits the attacker into the 392 knockback");
        }
        {
            Fixture fx(1, {}, {392});
            fx.setTicks = {{39, 6}, {40, 30}};
            Fighter& f = fx.make();
            Fighter& foe = fx.make();
            foe.reset(glm::vec3(600.f, 0.f, 0.f), 0.f);
            input::PlayerState in = pressWith(input::Action::Jump);
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            in.down[input::Action::Jump] = false;
            for (int i = 0; i < 12; ++i) { input::compute_edges(in); f.update(&in, &foe, 1.0 / 64.0); }
            in = pressWith(input::Action::AttackA);
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            checkInt(320, f.attack_move_id(), "guard fixture enters the 320 chase");
            in.down[input::Action::AttackA] = false;
            f.note_melee_hit(0, true);
            input::compute_edges(in);
            f.update(&in, &foe, 1.0 / 64.0);
            checkInt(320, f.attack_move_id(),
                     "320 has no guard branch, so a guarded connect keeps the row");
        }

        // (9) The attack press is gated on the fighter-level special/charge gauge
        // (`0 < +0x834` on every recovered arm, and the ordinary arm's no-attack path
        // also tests `+0x834 < 1`): an empty gauge declines the press without entering
        // AttackA, like every other declined branch.
        {
            Fixture fx(1);
            Fighter& f = fx.make();
            f.set_charge_gauge(0);
            input::PlayerState in = pressWith(input::Action::AttackA);
            tick(f, in);
            checkInt(-1, f.attack_move_id(), "an empty charge gauge declines the attack press");
            check(f.state() != FighterState::AttackA,
                  "the declined press does not enter AttackA");
            check(f.charge_gauge() == 0, "the declined press leaves the gauge empty");

            Fixture ok(1);
            Fighter& g = ok.make();
            g.set_charge_gauge(1);
            input::PlayerState okIn = pressWith(input::Action::AttackA);
            tick(g, okIn);
            checkInt(300, g.attack_move_id(), "a positive gauge admits the ordinary 300");
        }
    }

    section("tap-shot state routing — recovered table");
    {
        checkInt(400, gameplay::rena_tap_shot_state(0, 0, true), "idle tap w0 -> 400");
        checkInt(401, gameplay::rena_tap_shot_state(0, 10, true), "walking tap w0 -> 401");
        checkInt(401, gameplay::rena_tap_shot_state(0, 20, true), "forward-dash tap w0 -> 401");
        checkInt(405, gameplay::rena_tap_shot_state(0, 23, true), "left-dash tap w0 -> 405");
        checkInt(406, gameplay::rena_tap_shot_state(0, 24, true), "right-dash tap w0 -> 406");
        checkInt(407, gameplay::rena_tap_shot_state(0, 27, true), "back-dash tap w0 -> 407");
        checkInt(401, gameplay::rena_tap_shot_state(1, 23, true), "dash tap w1 -> 401");
        checkInt(400, gameplay::rena_tap_shot_state(2, 10, true), "walking tap w2 -> 400");
        checkInt(402, gameplay::rena_tap_shot_state(2, 41, false), "air tap -> 402");
        check(gameplay::rena_air_dash_fast_shot(0, 30, 0, true), "w0 air-dash fast shot (phase 0)");
        check(!gameplay::rena_air_dash_fast_shot(0, 30, 2, true), "fast shot closed past phase 2");
        check(!gameplay::rena_air_dash_fast_shot(1, 30, 0, true), "w1 has no fast shot");
        check(!gameplay::rena_air_dash_fast_shot(0, 41, 0, true), "fast shot needs the dash row");
    }

    // -----------------------------------------------------------------------
    section("install-backed admission through the shipped Rena tables");
    {
        if (test::gameInstall().empty()) {
            skip("no game install: real-data admission cases");
        } else {
            // A persistent input state, so compute_edges derives real press/release
            // edges: a fresh copy per tick would re-fire every held button and
            // phantom double-taps would swallow the shoot release.
            struct Driver {
                Fighter& f;
                input::PlayerState st{};
                void step() {
                    input::compute_edges(st);
                    f.update(&st, nullptr, 1.0 / 64.0);
                }
                void press(int a)  { st.down[a] = true;  step(); }
                void release(int a) { st.down[a] = false; step(); }
                void settle(int n) {
                    st = input::PlayerState{};
                    for (int i = 0; i < n; ++i) step();
                }
                // Long attacks (Rena+2's frame-49 kick, the 331 approach) and
                // time-valued magazine refills outlast fixed settles: run until
                // the fighter is idle again, bounded.
                void settleIdle() {
                    st = input::PlayerState{};
                    for (int i = 0; i < 500 && f.state() != FighterState::Idle; ++i) step();
                    for (int i = 0; i < 5; ++i) step();
                }
            };

            for (int slot = 0; slot < 3; ++slot) {
                test::Combo combo;
                std::string error;
                char label[64];
                std::snprintf(label, sizeof label, "Rena+%d table loads", slot);
                if (!combo.load(0, slot, error)) {
                    std::printf("  load error: %s\n", error.c_str());
                    check(false, label);
                    continue;
                }
                check(true, label);
                Fighter& f = *new Fighter();
                combo.bind(f);
                Driver d{f};

                std::snprintf(label, sizeof label, "Rena+%d idle press -> 300", slot);
                d.press(input::Action::AttackA);
                checkInt(300, f.attack_move_id(), label);
                d.settleIdle();

                std::snprintf(label, sizeof label, "Rena+%d back press -> 310", slot);
                d.st.down[input::Action::Down] = true; d.step();
                d.press(input::Action::AttackA);
                checkInt(310, f.attack_move_id(), label);
                d.settleIdle();

                std::snprintf(label, sizeof label, "Rena+%d lateral press -> 311", slot);
                d.st.down[input::Action::Right] = true; d.step();
                d.press(input::Action::AttackA);
                checkInt(311, f.attack_move_id(), label);
                d.settleIdle();

                std::snprintf(label, sizeof label, "Rena+%d dash attack -> 330", slot);
                d.press(input::Action::Up); d.release(input::Action::Up);
                d.press(input::Action::Up);
                d.press(input::Action::AttackA);
                checkInt(330, f.attack_move_id(), label);
                d.settleIdle();

                std::snprintf(label, sizeof label, "Rena+%d side-dash attack -> 331", slot);
                d.press(input::Action::Left); d.release(input::Action::Left);
                d.press(input::Action::Left);
                d.press(input::Action::AttackA);
                checkInt(331, f.attack_move_id(), label);
                d.settleIdle();

                std::snprintf(label, sizeof label, "Rena+%d air attack -> 320", slot);
                d.settleIdle();
                d.press(input::Action::Jump); d.release(input::Action::Jump);
                for (int i = 0; i < 12; ++i) d.step();
                check(f.state() == FighterState::Jump, "fighter is airborne (real table)");
                d.press(input::Action::AttackA);
                checkInt(320, f.attack_move_id(), label);
                d.settle(400);
                delete &f;
            }

            // Chain families differ per weapon: w0 walks the full 300->301->302,
            // w1 stops at 301, w2 never leaves 300. Press cycles continue until the
            // 0x100 windows open (the shipped rows open them mid-move).
            for (int slot = 0; slot < 3; ++slot) {
                test::Combo combo;
                std::string error;
                if (!combo.load(0, slot, error)) continue;
                Fighter& f = *new Fighter();
                combo.bind(f);
                Driver d{f};
                d.press(input::Action::AttackA);
                d.release(input::Action::AttackA);
                bool saw301 = false, saw302 = false;
                for (int i = 0; i < 60; ++i) {
                    d.settle(3);
                    d.press(input::Action::AttackA);
                    d.release(input::Action::AttackA);
                    if (f.attack_move_id() == 301) saw301 = true;
                    if (f.attack_move_id() == 302) saw302 = true;
                }
                char label[64];
                std::snprintf(label, sizeof label, "Rena+%d chain reaches 301", slot);
                check(slot < 2 ? saw301 : !saw301, label);
                std::snprintf(label, sizeof label, "Rena+%d reaches 302 only for w0", slot);
                check(slot == 0 ? saw302 : !saw302, label);
                delete &f;
            }

            // Tap-shot routing through the real programs and tables. The held
            // direction persists across the release edge: the admission reads the
            // situation at the release, while the fighter is still walking/dashing.
            for (int slot = 0; slot < 3; ++slot) {
                test::Combo combo;
                std::string error;
                if (!combo.load(0, slot, error)) continue;
                Fighter& f = *new Fighter();
                combo.bind(f);
                Driver d{f};
                char label[64];

                std::snprintf(label, sizeof label, "Rena+%d idle tap shot -> 400", slot);
                d.press(input::Action::Shoot); d.release(input::Action::Shoot);
                checkInt(400, f.shot_move_id(), label);
                d.settle(700);

                std::snprintf(label, sizeof label, "Rena+%d walking tap shot", slot);
                d.st.down[input::Action::Up] = true;
                for (int i = 0; i < 12 && f.state() != FighterState::Walk; ++i) d.step();
                d.press(input::Action::Shoot);
                d.release(input::Action::Shoot);
                checkInt(slot == 2 ? 400 : 401, f.shot_move_id(), label);
                d.settle(700);

                std::snprintf(label, sizeof label, "Rena+%d forward-dash tap shot", slot);
                d.press(input::Action::Up); d.release(input::Action::Up);
                d.press(input::Action::Up);
                d.press(input::Action::Shoot);
                d.release(input::Action::Shoot);
                checkInt(slot == 2 ? 400 : 401, f.shot_move_id(), label);
                d.settle(700);

                std::snprintf(label, sizeof label, "Rena+%d left-dash tap shot", slot);
                d.press(input::Action::Left); d.release(input::Action::Left);
                d.press(input::Action::Left);
                d.press(input::Action::Shoot);
                d.release(input::Action::Shoot);
                checkInt(slot == 0 ? 405 : slot == 1 ? 401 : 400, f.shot_move_id(), label);
                d.settle(700);

                std::snprintf(label, sizeof label, "Rena+%d right-dash tap shot", slot);
                d.press(input::Action::Right); d.release(input::Action::Right);
                d.press(input::Action::Right);
                d.press(input::Action::Shoot);
                d.release(input::Action::Shoot);
                checkInt(slot == 0 ? 406 : slot == 1 ? 401 : 400, f.shot_move_id(), label);
                d.settle(700);
                delete &f;
            }

            // The back-dash tap (407) end-to-end: the dash situation selects the
            // state, and its body fires the row-4/row-9 pair at tick 13.
            {
                test::Combo combo;
                std::string error;
                if (combo.load(0, 0, error)) {
                    Fighter& f = *new Fighter();
                    combo.bind(f);
                    Driver d{f};
                    d.press(input::Action::Down); d.release(input::Action::Down);
                    d.press(input::Action::Down);           // back dash -> row 27
                    check(f.state() == FighterState::Run, "back dash entered row 27");
                    d.press(input::Action::Shoot);
                    d.release(input::Action::Shoot);        // tap during the dash
                    checkInt(407, f.shot_move_id(), "back-dash tap selects 407");
                    int launches = 0, firstRow = -1, secondRow = -1;
                    for (int i = 0; i < 25; ++i) {
                        d.step();
                        for (auto shot = f.take_pending_shot(); shot.armed;
                             shot = f.take_pending_shot()) {
                            if (launches == 0) firstRow = shot.bulletRow;
                            else if (launches == 1) secondRow = shot.bulletRow;
                            ++launches;
                        }
                    }
                    checkInt(2, launches, "407 fires its two-request pair");
                    checkInt(4, firstRow, "407's first request is row 4");
                    checkInt(9, secondRow, "407's second request is row 9");
                    delete &f;
                }
            }
            // The air-dash fast shot (408) end-to-end: only Rena+0, only while the
            // dash row still has phases left and a direction is held at the release;
            // the body fires the ground row-0 request one tick early, at tick 12.
            {
                test::Combo combo;
                std::string error;
                if (combo.load(0, 0, error)) {
                    Fighter& f = *new Fighter();
                    combo.bind(f);
                    Driver d{f};
                    d.press(input::Action::Jump); d.release(input::Action::Jump);
                    for (int i = 0; i < 12; ++i) d.step();
                    check(f.state() == FighterState::Jump, "408 fixture is airborne");
                    d.press(input::Action::Up); d.release(input::Action::Up);
                    d.press(input::Action::Up);           // air dash -> row 30
                    check(f.state() == FighterState::Run && f.air_dash_context(),
                          "air dash entered row 30");
                    d.st.down[input::Action::Shoot] = true; d.step();
                    d.st.down[input::Action::Shoot] = false; d.step();  // held-direction release
                    checkInt(408, f.shot_move_id(), "air-dash release with direction selects 408");
                    int launches = 0, firstRow = -1;
                    for (int i = 0; i < 25; ++i) {
                        d.step();
                        for (auto shot = f.take_pending_shot(); shot.armed;
                             shot = f.take_pending_shot()) {
                            if (launches == 0) firstRow = shot.bulletRow;
                            ++launches;
                        }
                    }
                    checkInt(1, launches, "408 fires the single row-0 request");
                    checkInt(0, firstRow, "408's request is the ground row 0");
                    delete &f;
                }
            }

            // The walking shot fires exactly its program body (w0: one row-0/6
            // request at tick 12) and w0 ships the 408 fast-shot row.
            {
                test::Combo combo;
                std::string error;
                if (combo.load(0, 0, error)) {
                    check(combo.moves.has(408), "w0 ships the 408 fast-shot row");
                    Fighter& f = *new Fighter();
                    combo.bind(f);
                    Driver d{f};
                    d.st.down[input::Action::Up] = true;
                    for (int i = 0; i < 12 && f.state() != FighterState::Walk; ++i) d.step();
                    d.press(input::Action::Shoot);
                    d.release(input::Action::Shoot);
                    checkInt(401, f.shot_move_id(), "w0 walking shot selects 401");
                    int launches = 0;
                    for (int i = 0; i < 20; ++i) {
                        d.step();
                        while (f.take_pending_shot().armed) ++launches;
                    }
                    checkInt(1, launches, "w0 walking shot fires one request");
                    delete &f;
                }
            }
        }
    }

    std::printf("\nADMISSION: %d checks, %d failed, %d skipped\n", checks, failures, skipped);
    return failures ? 1 : 0;
}
}  // namespace

int main() { return run(); }
