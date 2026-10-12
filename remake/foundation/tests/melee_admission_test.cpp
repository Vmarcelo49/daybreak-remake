// The recovered Rena-group attack admission (melee_admission.h):
//   1. the dispatcher table pinned case-by-case against the recovered source
//      (battle_rena_melee_admission.hpp = FUN_00445ee0/44d850/43ded0 branches);
//   2. the Fighter wiring driven by real input edges through synthetic tables;
//   3. install-backed input sequences through the shipped Rena tables.
// The expected values below are transcribed from the recovered selector, not
// read back from the implementation under test.

#include "combo_fixture.h"
#include "gameplay/fighter.h"
#include "gameplay/melee_admission.h"
#include "gameplay/move_behavior.h"

#include <cstdio>
#include <cstring>
#include <memory>
#include <string>
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

// The Rena melee row inventory with passing gates (priority 10, threshold 0).
// The chain rows' first record opens the 0x100 window, as the shipped tables do.
std::vector<std::uint8_t> admissionTable(int weaponId, int idleThreshold = 0,
                                         bool drop310 = false) {
    std::vector<std::uint8_t> b;
    putU32(b, 0x00010000);
    putName(b, "data/rena/00.X", 0x104);
    putU32(b, 0); putU32(b, 0); putU32(b, 0);
    putU32(b, weaponId);
    putU32(b, 0); putU32(b, 0);
    const int rows[] = {0, 10, 20, 23, 24, 27, 30, 40, 41, 42, 44,
                        300, 301, 302, 310, 311, 320, 329, 330, 331,
                        332, 333, 334, 340, 341};
    putU32(b, static_cast<int>(sizeof rows / sizeof rows[0]) - (drop310 ? 1 : 0));
    int set = 1;
    for (int id : rows) {
        if (drop310 && id == 310) continue;
        const bool chainRow = id == 300 || id == 301 || id == 302;
        const int threshold = id == 0 ? idleThreshold : 0;
        // Row 30 carries three phases so the air-dash phase gate is exercisable.
        if (id == 30) {
            addAdmitMove(b, id, 10, threshold,
                         {AdmitPhase{set++, {{0, 0}}},
                          AdmitPhase{set++, {{0, 0}}},
                          AdmitPhase{set++, {{0, 0}}}});
        } else {
            addAdmitMove(b, id, 10, threshold,
                         {AdmitPhase{set++, {{0, chainRow ? 0x100 : 0}}},
                          AdmitPhase{set++, {{8, 0}}}});
        }
    }
    putU32(b, 124);
    for (int i = 0; i < 124; ++i) { putU32(b, 0); putU32(b, 0); putU32(b, 0); }
    return b;
}

WeaponDefinition slotWeapon(int itemId) {
    WeaponDefinition w;
    w.id = itemId;
    w.slotCount = 2;
    w.bulletCount = 0;
    w.magazines[0] = gameplay::MagazineDefinition{6, 2, 300, 0, 60, 1};
    w.magazines[1] = gameplay::MagazineDefinition{2, 2, 300, 0, 180, 2};
    return w;
}

// A table+weapon pair; every fighter binds a fresh rig so cases never inherit
// each other's animation/stamina/phase state.
struct Fixture {
    CharacterMoves moves;
    WeaponDefinition weapon;
    std::vector<std::unique_ptr<xm::Model>> models;
    std::vector<std::unique_ptr<xm::Controller>> controllers;
    bool ok = false;
    std::string error;
    explicit Fixture(int itemId, int idleThreshold = 0, bool drop310 = false) {
        const auto bytes = admissionTable(itemId, idleThreshold, drop310);
        ok = moves.parse(bytes.data(), bytes.size(), error);
        moves.set_character_index(0);
        weapon = slotWeapon(itemId);
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
        in.contact = 0;
        checkInt(c.expected, gameplay::rena_melee_admission(in, AttackAdmissionTable{&moves}),
                 c.name);
    }
}

int run() {
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
        Fixture blocked(1, /*idleThreshold=*/100);
        const TableCase declined[] = {
            {0, 0, 0, true, true, 0, 0, -1, "failed neutral gate declines"},
        };
        runTableCases(blocked.moves, declined, 1);
        Fixture noKick(1, 0, /*drop310=*/true);
        const TableCase fallback[] = {
            {0, 0, 0, true, true, 0, -1, 300, "missing 310 row falls to 300"},
        };
        runTableCases(noKick.moves, fallback, 1);
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
