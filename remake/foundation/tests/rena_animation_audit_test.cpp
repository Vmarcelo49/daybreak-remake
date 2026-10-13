// Rena+0/+1/+2 animation audit (issue #71): drive each checklist situation
// with real input and print the playing animation index.
//
// For every situation this pins state -> NN.dat move row -> phase animation-set
// tag (FUN_0041e180 loader, FUN_00421100/FUN_00421410 binder; REA function
// identity ev_dcab64f2 on the SHA-verified executable). Expected rows come from
// the recovered dispatchers (FUN_00445ee0 input selector, FUN_0044d850/
// FUN_0043ded0 situation selectors) and the donor implementation under
// .local-analysis/daybreak-rebuild/DaybreakRebuild-20261010/source/src/.
// Where the port has no recovered binding the test pins the fallback as a
// known-open gap instead of asserting an invented clip. Nothing here claims
// live parity: issue #71 requires a live match compared against the original,
// so passing here is necessary but not sufficient for any checklist box.
#include "combo_fixture.h"
#include "gameplay/fighter.h"
#include "gameplay/projectile.h"

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

namespace {
using gameplay::Fighter;
using gameplay::FighterState;
using gameplay::ShotTier;
namespace input = fnd::input;

int checks = 0, failures = 0, skipped = 0;

void check(bool condition, const char* name) {
    ++checks;
    if (!condition) ++failures;
    std::printf("  %-64s %s\n", name, condition ? "ok" : "FAIL");
}

void checkInt(int expected, int actual, const char* name) {
    ++checks;
    const bool same = expected == actual;
    if (!same) ++failures;
    std::printf("  %-64s %s", name, same ? "ok" : "FAIL");
    if (!same) std::printf("  (expected %d, got %d)", expected, actual);
    std::printf("\n");
}

void skip(const char* name) {
    ++skipped;
    std::printf("  %-64s SKIP\n", name);
}

void section(const char* title) { std::printf("\n== %s ==\n", title); }

struct Input {
    fnd::input::PlayerState p{};
    void set(int action, bool down) { p.down[action] = down; }
};

void tick(Fighter& f, Input& in, Fighter* opp = nullptr) {
    fnd::input::compute_edges(in.p);
    f.update(&in.p, opp, 1.0 / 64.0);
}

void settle(Fighter& f, int frames = 70) {
    for (int i = 0; i < frames; ++i) f.update(nullptr, nullptr, 1.0 / 64.0);
}

void doubleTap(Fighter& f, Input& in, int action) {
    in.set(action, true);
    tick(f, in);
    in.set(action, false);
    tick(f, in);
    in.set(action, true);
    tick(f, in);
    in.set(action, false);
}

// The bound clip must be the NN.dat row's own phase tag, never a borrowed row
// or the set-0 fallback. Prints the full triple for the audit log.
void expectClip(Fighter& f, const test::Combo& combo, const char* comboLabel,
                const char* item, int expectedMove) {
    const int expectedSet = combo.moves.first_set_index(expectedMove);
    char label[160];
    std::snprintf(label, sizeof label, "%s %s opens on set %d", comboLabel, item, expectedSet);
    checkInt(expectedSet, f.anim_set_index(), label);
    std::snprintf(label, sizeof label, "%s %s clip is not a fallback", comboLabel, item);
    check(!f.anim_fallback(), label);
    std::printf("    [print] %s %s -> anim_idx=%d name=%s fallback=%d\n", comboLabel, item,
                f.anim_set_index(), f.anim_set_name(), f.anim_fallback() ? 1 : 0);
}

void auditCombo(int slot) {
    const char* comboLabel =
        slot == 0 ? "Rena+0" : slot == 1 ? "Rena+1" : "Rena+2";
    char sectionTitle[96];
    std::snprintf(sectionTitle, sizeof sectionTitle,
                  "%s animation clips by situation (issue #71)", comboLabel);
    section(sectionTitle);

    test::Combo combo;
    std::string error;
    if (!combo.load(0, slot, error)) {
        skip(comboLabel);
        return;
    }

    // Battle entry: raw init binds the reset row before any input settles it.
    {
        Fighter g;
        g.init(&combo.model, combo.controller(), glm::vec3(0.f), 0.f);
        combo.bind(g);
        checkInt(static_cast<int>(FighterState::BattleStart), static_cast<int>(g.state()),
                 "entry starts in BattleStart");
        checkInt(combo.moves.first_set_index(194), g.anim_set_index(),
                 "entry binds the reset row-194 clip");
    }

    // Idle stance.
    {
        Fighter f;
        combo.init(f, glm::vec3(0.f), 0.f);
        checkInt(static_cast<int>(FighterState::Idle), static_cast<int>(f.state()),
                 "idle settles to Idle");
        expectClip(f, combo, comboLabel, "idle stance", 0);
    }

    // Walking (hold Right).
    {
        Fighter f;
        combo.init(f, glm::vec3(0.f), 0.f);
        Input in;
        in.set(input::Action::Right, true);
        for (int i = 0; i < 30; ++i) tick(f, in);
        checkInt(static_cast<int>(FighterState::Walk), static_cast<int>(f.state()),
                 "held direction walks");
        expectClip(f, combo, comboLabel, "walking", 10);
    }

    // Ground dashes: all four directions. Side rows are command-mapped
    // (FUN_00445ee0:86-95): Left -> row 24, Right -> row 23.
    {
        const struct {
            int action;
            int move;
            const char* name;
        } cases[] = {
            {input::Action::Up, 20, "ground dash forward"},
            {input::Action::Down, 27, "ground dash backward"},
            {input::Action::Left, 24, "ground dash left"},
            {input::Action::Right, 23, "ground dash right"},
        };
        for (const auto& c : cases) {
            Fighter f;
            combo.init(f, glm::vec3(0.f), 0.f);
            Input in;
            doubleTap(f, in, c.action);
            char label[128];
            std::snprintf(label, sizeof label, "%s %s enters Run", comboLabel, c.name);
            checkInt(static_cast<int>(FighterState::Run), static_cast<int>(f.state()), label);
            char item[96];
            std::snprintf(item, sizeof item, "%s (row %d)", c.name, c.move);
            checkInt(c.move, f.dash_move_id(), item);
            expectClip(f, combo, comboLabel, item, c.move);
        }
    }

    // Stationary jump: ascent clip, in-flight chain clips, landing.
    {
        Fighter f;
        combo.init(f, glm::vec3(0.f), 0.f);
        Input in;
        in.set(input::Action::Jump, true);
        tick(f, in);
        in.set(input::Action::Jump, false);
        checkInt(static_cast<int>(FighterState::Jump), static_cast<int>(f.state()),
                 "jump press leaves the ground");
        checkInt(combo.moves.first_set_index(40), f.anim_set_index(),
                 "jump ascent opens on row-40 clip");
        std::vector<int> flightSets;
        for (int i = 0; i < 120 && f.state() == FighterState::Jump; ++i) {
            tick(f, in);
            // The touchdown tick rebinds Idle's own clip; only sample airborne frames.
            if (f.state() == FighterState::Jump) flightSets.push_back(f.anim_set_index());
        }
        checkInt(static_cast<int>(FighterState::Idle), static_cast<int>(f.state()),
                 "jump lands back to Idle");
        bool chainOnly = true;
        for (int s : flightSets)
            chainOnly = chainOnly && (s == 2 || s == 3 || s == 4 || s == 5 || s == 43);
        check(chainOnly, "in-flight clips stay inside the 40/41/42 chain sets");
        check(!f.anim_fallback(), "jump never falls back");
        std::printf("    [print] %s jump flight sets:", comboLabel);
        for (int s : flightSets) std::printf(" %d", s);
        std::printf("\n");
    }

    // Air dashes: all four directions. Only Rena+0 has a recovered airborne
    // row (30); Rena+1/+2 currently fall back (known-open gap).
    {
        const struct {
            int action;
            const char* name;
        } cases[] = {
            {input::Action::Up, "air dash forward"},
            {input::Action::Down, "air dash backward"},
            {input::Action::Left, "air dash left"},
            {input::Action::Right, "air dash right"},
        };
        for (const auto& c : cases) {
            Fighter f;
            combo.init(f, glm::vec3(0.f), 0.f);
            Input in;
            in.set(input::Action::Jump, true);
            tick(f, in);
            in.set(input::Action::Jump, false);
            for (int i = 0; i < 12; ++i) tick(f, in);
            doubleTap(f, in, c.action);
            char label[128];
            std::snprintf(label, sizeof label, "%s %s enters Run", comboLabel, c.name);
            checkInt(static_cast<int>(FighterState::Run), static_cast<int>(f.state()), label);
            if (slot == 0) {
                checkInt(30, f.dash_move_id(), "Rena+0 air dash binds row 30");
                expectClip(f, combo, comboLabel, c.name, 30);
            } else {
                std::snprintf(label, sizeof label, "%s %s has no recovered air row (known gap)",
                              comboLabel, c.name);
                check(f.anim_fallback(), label);
                std::printf("    [print] %s %s -> anim_idx=%d fallback=1 (OPEN)\n",
                            comboLabel, c.name, f.anim_set_index());
            }
        }
    }

    // Neutral attack chain, first hit.
    {
        Fighter f;
        combo.init(f, glm::vec3(0.f), 0.f);
        Input in;
        in.set(input::Action::AttackA, true);
        tick(f, in);
        in.set(input::Action::AttackA, false);
        checkInt(300, f.attack_move_id(), "neutral press admits 300");
        expectClip(f, combo, comboLabel, "neutral attack 300", 300);
    }

    // Directional attacks: back-held 310, lateral-held 311.
    {
        Fighter f;
        combo.init(f, glm::vec3(0.f), 0.f);
        Input in;
        in.set(input::Action::Down, true);
        in.set(input::Action::AttackA, true);
        tick(f, in);
        in.set(input::Action::AttackA, false);
        in.set(input::Action::Down, false);
        checkInt(310, f.attack_move_id(), "back-held press admits 310");
        expectClip(f, combo, comboLabel, "back attack 310", 310);
    }
    {
        Fighter f;
        combo.init(f, glm::vec3(0.f), 0.f);
        Input in;
        in.set(input::Action::Left, true);
        in.set(input::Action::AttackA, true);
        tick(f, in);
        in.set(input::Action::AttackA, false);
        in.set(input::Action::Left, false);
        checkInt(311, f.attack_move_id(), "lateral-held press admits 311");
        expectClip(f, combo, comboLabel, "side attack 311", 311);
    }

    // Attack after a forward ground dash.
    {
        Fighter f;
        combo.init(f, glm::vec3(0.f), 0.f);
        Input in;
        doubleTap(f, in, input::Action::Up);
        in.set(input::Action::AttackA, true);
        tick(f, in);
        in.set(input::Action::AttackA, false);
        checkInt(330, f.attack_move_id(), "forward-dash press admits 330");
        expectClip(f, combo, comboLabel, "dash attack 330", 330);
    }

    // Aerial attack after a normal jump.
    {
        Fighter f;
        combo.init(f, glm::vec3(0.f), 0.f);
        Input in;
        in.set(input::Action::Jump, true);
        tick(f, in);
        in.set(input::Action::Jump, false);
        for (int i = 0; i < 12; ++i) tick(f, in);
        in.set(input::Action::AttackA, true);
        tick(f, in);
        in.set(input::Action::AttackA, false);
        checkInt(320, f.attack_move_id(), "airborne press admits 320");
        expectClip(f, combo, comboLabel, "air attack 320", 320);
    }

    // Ground + air tap shots.
    {
        Fighter f;
        combo.init(f, glm::vec3(0.f), 0.f);
        Input in;
        in.set(input::Action::Shoot, true);
        tick(f, in);
        in.set(input::Action::Shoot, false);
        tick(f, in);
        checkInt(400, f.shot_move_id(), "ground tap binds 400");
        expectClip(f, combo, comboLabel, "ground tap shot 400", 400);
    }
    {
        Fighter f;
        combo.init(f, glm::vec3(0.f), 0.f);
        Input in;
        in.set(input::Action::Jump, true);
        tick(f, in);
        in.set(input::Action::Jump, false);
        for (int i = 0; i < 12; ++i) tick(f, in);
        in.set(input::Action::Shoot, true);
        tick(f, in);
        in.set(input::Action::Shoot, false);
        tick(f, in);
        checkInt(402, f.shot_move_id(), "air tap binds 402");
        expectClip(f, combo, comboLabel, "air tap shot 402", 402);
    }

    // Ground charge-1 shot (Yellow tier -> 450).
    {
        Fighter f;
        combo.init(f, glm::vec3(0.f), 0.f);
        Input in;
        in.set(input::Action::Shoot, true);
        int guard = 0;
        while (f.charge_tier() == ShotTier::Tap && guard++ < 1000) tick(f, in);
        check(f.charge_tier() == ShotTier::Yellow, "charge hold reaches Yellow");
        in.set(input::Action::Shoot, false);
        tick(f, in);
        checkInt(450, f.shot_move_id(), "charge-1 release binds 450");
        expectClip(f, combo, comboLabel, "charge-1 shot 450", 450);
    }

    // Guard holds the playing clip (no selector in the source).
    {
        Fighter f;
        combo.init(f, glm::vec3(0.f), 0.f);
        Input in;
        in.set(input::Action::Guard, true);
        tick(f, in);
        checkInt(static_cast<int>(FighterState::Guard), static_cast<int>(f.state()),
                 "guard press enters Guard");
        check(!f.anim_fallback(), "guard holds its clip without fallback");
        std::printf("    [print] %s guard -> anim_idx=%d name=%s\n", comboLabel,
                    f.anim_set_index(), f.anim_set_name());
        in.set(input::Action::Guard, false);
    }

    // Damage reaction.
    {
        Fighter f;
        combo.init(f, glm::vec3(0.f), 0.f);
        f.take_damage(5, nullptr, -1, 0, false);
        checkInt(static_cast<int>(FighterState::Hit), static_cast<int>(f.state()),
                 "damage enters Hit");
        expectClip(f, combo, comboLabel, "damage reaction 103", 103);
    }

    // KO.
    {
        Fighter f;
        combo.init(f, glm::vec3(0.f), 0.f);
        f.set_hp(1);
        f.take_damage(50, nullptr, -1, 0, false);
        checkInt(static_cast<int>(FighterState::KO), static_cast<int>(f.state()),
                 "lethal damage enters KO");
        expectClip(f, combo, comboLabel, "KO 203", 203);
    }
}
}  // namespace

int main() {
    for (int slot = 0; slot < 3; ++slot) auditCombo(slot);
    std::printf("\n%d checks, %d failed, %d skipped\n", checks, failures, skipped);
    std::printf("RENA_ANIMATION_AUDIT: %s\n", failures ? "FAIL" : "ok");
    return failures ? EXIT_FAILURE : EXIT_SUCCESS;
}
