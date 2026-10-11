// =============================================================================
//  fighter_script_test.cpp — host test for the ported fighter + projectile
//  gameplay (remake/foundation/src/gameplay/{fighter,projectile}.{h,cpp}).
//
//  Device-free and deterministic: no window, no WebGPU, no SDL, no clock, no
//  RNG. Every case drives the simulation at a fixed dt = 1/60 s with scripted
//  input edges (fnd::input::compute_edges, the same call the live poll path
//  makes) and prints expected vs got for every assertion.
//
//  Build from the repo root (glm ships in the foundation's third_party):
//    g++ -std=c++17 -Wall -Wextra -I remake/foundation/src
//        -I remake/foundation/third_party/glm
//        remake/foundation/src/gameplay/fighter.cpp
//        remake/foundation/src/gameplay/character_moves.cpp
//        remake/foundation/src/gameplay/weapon_definition.cpp
//        remake/foundation/src/gameplay/projectile.cpp
//        remake/foundation/src/physics/raycast.cpp
//        remake/foundation/tests/fighter_script_test.cpp -o /tmp/fighter_script_test
//    /tmp/fighter_script_test
//
//  Exit status: 0 when every check passed, 1 otherwise; the last line is
//  `FIGHTER_SCRIPT: ok` or `FIGHTER_SCRIPT: FAIL`.
//
//  Float policy: bit-exact comparisons are used only where the arithmetic is
//  exact (constants, single multiply/add, integers, frame counts from pure
//  add/subtract recurrences). Values accumulated over many frames are compared
//  against a double-precision expectation with a stated tolerance and the exact
//  float is printed, because -O2/-O3 FMA contraction can move the last bits of
//  an a*b+c accumulation. stamina() returns an int (as in the DX9 source), so
//  stamina checks are integer checks on the truncated value.
//
//  Source quirks found while deriving the expectations are pinned as tests:
//  the leap velocity kJumpSpeed is overwritten by the fly rise on the same frame, Kakera's HP
//  drain rounds to 0 at 60 Hz, and the Friendship gauge needs a 13th hit to
//  clamp to 1.0. These are in the DX9 source too. Guard release is corrected
//  for live play.
// =============================================================================

#include "assets/xmodel.h"
#include "combo_fixture.h"

#include "gameplay/fighter.h"
#include "gameplay/fixed_step.h"
#include "gameplay/match.h"
#include "gameplay/projectile.h"
#include "gameplay/character_moves.h"
#include "gameplay/weapon_definition.h"
#include "gameplay/move_behavior.h"
#include "gameplay/shooting_magazine.h"
#include "physics/raycast.h"

// Colour-layout cross-check only: DEBUG_PRIMS_GEOMETRY_ONLY keeps webgpu.h and
// gpu/gpu.h out of this TU (render/debug_prims.h:40-47), so the renderer's
// colour type can be compared with gameplay::Rgb without a device.
#define DEBUG_PRIMS_GEOMETRY_ONLY
#include "render/debug_prims.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

namespace {

using gameplay::Fighter;
using gameplay::FighterConstants;
using gameplay::FighterState;
using gameplay::Hypermode;
using gameplay::ProjectilePool;
using gameplay::Rgb;
using gameplay::ShotTier;

constexpr double kDt = 1.0 / 60.0;
const float      kStep = static_cast<float>(kDt);

int g_checks = 0;
int g_fails  = 0;
int g_skipped = 0;

struct TestCombo : test::Combo {
    bool ready = false;

    bool load(const std::filesystem::path& install, int character = 0, int slot = 0) {
        std::string error;
        fnd::assets::assetSource().openInstall(install.string());
        ready = test::Combo::load(character, slot, error);
        return ready;
    }

    void bind(Fighter& fighter) const {
        if (!ready) return;
        test::Combo::bind(fighter);
    }
};

TestCombo g_testCombo;
TestCombo g_mionCombo;
TestCombo g_mion1Combo;
TestCombo g_rikaCombo;
TestCombo g_tomitakeCombo;
TestCombo g_keiichiCombo;
TestCombo g_keiichi0Combo;
TestCombo g_keiichi1Combo;
TestCombo g_chieCombo;
TestCombo g_kasaiCombo;
TestCombo g_takanoCombo;
TestCombo g_irieCombo;
TestCombo g_mion2Combo;
TestCombo g_rika2Combo;
TestCombo g_satokoCombo;
TestCombo g_satoko1Combo;
TestCombo g_rika0Combo;
TestCombo g_rena1Combo;
TestCombo g_rena2Combo;
TestCombo g_akane2Combo;
TestCombo g_natsumi0Combo;
TestCombo g_satoko2Combo;

std::filesystem::path findInstall(const char* executable) {
    const int itemId = gameplay::kWeaponIds[0][0];
    const std::string itemName =
        (itemId < 10 ? "00" : itemId < 100 ? "0" : "") + std::to_string(itemId) + ".dat";
    const auto containsCombo = [&itemName](const std::filesystem::path& root) {
        std::error_code ec;
        return std::filesystem::is_regular_file(root / "data" / "rena" / "00.dat", ec) &&
               std::filesystem::is_regular_file(root / "data" / "item" / itemName, ec);
    };
    std::vector<std::filesystem::path> starts;
    std::error_code ec;
    if (const char* configured = std::getenv("GAME_DIR")) {
        const std::filesystem::path candidate(configured);
        if (containsCombo(candidate)) return candidate;
    }
    starts.push_back(std::filesystem::current_path(ec));
    if (executable && *executable)
        starts.push_back(std::filesystem::absolute(executable, ec).parent_path());
    for (const auto& start : starts) {
        for (auto dir = start; !dir.empty(); dir = dir.parent_path()) {
            const auto nested = dir / "Higurashi-Daybreak";
            if (containsCombo(dir)) return dir;
            if (containsCombo(nested))
                return dir / "Higurashi-Daybreak";
            const auto parent = dir.parent_path();
            if (parent == dir) break;
        }
    }
    return {};
}

void skip_case(const char* what) {
    ++g_skipped;
    std::printf("  %-52s SKIP (matching Rena 0 combo unavailable)\n", what);
}

void bind_test_combo(Fighter& fighter) { g_testCombo.bind(fighter); }

// ---------------------------------------------------------------------------
// Check helpers — every one prints expected vs got.
// ---------------------------------------------------------------------------
void check_int(const char* what, long long expected, long long got) {
    const bool pass = (expected == got);
    ++g_checks;
    if (!pass) ++g_fails;
    std::printf("  %-52s exp %-14lld got %-14lld %s\n", what, expected, got,
                pass ? "ok" : "FAIL");
}

void check_bool(const char* what, bool expected, bool got) {
    const bool pass = (expected == got);
    ++g_checks;
    if (!pass) ++g_fails;
    std::printf("  %-52s exp %-14s got %-14s %s\n", what, expected ? "true" : "false",
                got ? "true" : "false", pass ? "ok" : "FAIL");
}

void check_u32(const char* what, std::uint32_t expected, std::uint32_t got) {
    const bool pass = (expected == got);
    ++g_checks;
    if (!pass) ++g_fails;
    std::printf("  %-52s exp 0x%08x     got 0x%08x     %s\n", what, expected, got,
                pass ? "ok" : "FAIL");
}

void check_str(const char* what, const char* expected, const char* got) {
    const bool pass = std::strcmp(expected, got) == 0;
    ++g_checks;
    if (!pass) ++g_fails;
    std::printf("  %-52s exp %-14s got %-14s %s\n", what, expected, got,
                pass ? "ok" : "FAIL");
}

// Bit-exact float compare: the printed bit patterns are the evidence.
void check_bits(const char* what, float expected, float got) {
    std::uint32_t eb = 0, gb = 0;
    std::memcpy(&eb, &expected, sizeof eb);
    std::memcpy(&gb, &got, sizeof gb);
    const bool pass = (eb == gb);
    ++g_checks;
    if (!pass) ++g_fails;
    std::printf("  %-52s exp %.9g [%08x] got %.9g [%08x] %s\n", what,
                static_cast<double>(expected), eb, static_cast<double>(got), gb,
                pass ? "ok" : "FAIL");
}

// Tolerance compare for accumulated floats; the exact float is printed.
void check_near(const char* what, double expected, double got, double tol) {
    const bool pass = std::fabs(expected - got) <= tol;
    ++g_checks;
    if (!pass) ++g_fails;
    std::printf("  %-52s exp %.9g got %.9g |d|=%.3g tol=%.0e %s\n", what, expected,
                got, std::fabs(expected - got), tol, pass ? "ok" : "FAIL");
}

void section(const char* title) { std::printf("\n== %s ==\n", title); }

// ---------------------------------------------------------------------------
// Scripted input + frame stepping
// ---------------------------------------------------------------------------
struct Input {
    fnd::input::PlayerState p{};
    void set(int action, bool down) { p.down[action] = down; }
    void clear() {
        for (int a = 0; a < fnd::input::ActionCount; ++a) p.down[a] = false;
    }
};

// One simulation frame for one fighter: derive this frame's edges exactly like
// the foundation's poll path (input.h:56-64) and then update.
void tick(Fighter& f, Input& in, Fighter* opp = nullptr) {
    fnd::input::compute_edges(in.p);
    f.update(&in.p, opp, kDt);
}

// Charge is a source counter, not dt accumulation or the MAIN magazine threshold.
void hold_yellow(Fighter& fighter, Input& input) {
    input.set(fnd::input::Action::Shoot, true);
    int limit = 1000;
    while (fighter.charge_tier() == ShotTier::Tap && limit-- > 0) tick(fighter, input);
    check_bool("Charge driver reaches Yellow", true, fighter.charge_tier() == ShotTier::Yellow);
}

void settle(Fighter& f, int frames = FighterConstants::kBattleStartFrames) {
    for (int i = 0; i < frames; ++i) f.update(nullptr, nullptr, kDt);
}

// A fresh fighter at `pos` facing +Z, already out of the BattleStart pose.
Fighter make_idle_fighter(const glm::vec3& pos) {
    Fighter f;
    f.init(nullptr, nullptr, pos, 0.0f);
    bind_test_combo(f);
    settle(f);
    return f;
}

// A tiny model with one named animation set per entry of `names`.
xm::Model make_anim_model(const std::vector<std::string>& names) {
    xm::Model m;
    for (const std::string& n : names) {
        xm::AnimSet a;
        a.name = n;
        a.duration = 60.0f;
        m.anims.push_back(a);
    }
    return m;
}

int count_live_sparks(const ProjectilePool& pool) {
    int n = 0;
    for (const auto& s : pool.sparks()) n += s.alive ? 1 : 0;
    return n;
}

// ===========================================================================
//  Case 1 — idle → walk (kWalkSpeed 80 u/s)
// ===========================================================================
void test_idle_walk() {
    section("1. idle -> walk (kWalkSpeed = 80 u/s)");
    Fighter f;
    f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    check_int("state at init", static_cast<int>(FighterState::BattleStart),
              static_cast<int>(f.state()));
    check_int("hp at init", 100, f.hp());
    check_int("stamina at init", 100, f.stamina());
    check_int("main whole at init", 6, f.main_whole());
    check_int("charge whole at init", 2, f.charge_whole());
    check_bits("main_frac at init", 1.0f, f.main_frac());
    check_bits("charge_frac at init", 1.0f, f.charge_frac());
    check_int("kBattleStartFrames", 60, FighterConstants::kBattleStartFrames);

    // 59 frames of BattleStart, then frame 60 expires the pose into Idle.
    for (int i = 0; i < 59; ++i) f.update(nullptr, nullptr, kDt);
    check_int("state after 59 frames (still BattleStart)",
              static_cast<int>(FighterState::BattleStart),
              static_cast<int>(f.state()));
    f.update(nullptr, nullptr, kDt);
    check_int("state after 60 frames (pose expired)", static_cast<int>(FighterState::Idle),
              static_cast<int>(f.state()));

    // Hold Up for 61 frames: up is facing-forward (lock-on movement — the camera
    // sits behind the facing, so screen-up is toward the opponent; at yaw 0 that
    // is +Z, validated against FUN_004235d0's relative-angle sectors).
    Input in;
    in.set(fnd::input::Action::Up, true);
    tick(f, in);   // first walk frame
    const float z1 = f.position().z;
    check_int("state while holding Up", static_cast<int>(FighterState::Walk),
              static_cast<int>(f.state()));
    check_bits("first walk frame dz", 420.0f * kStep, z1 - 0.0f);
    for (int i = 0; i < 60; ++i) tick(f, in);
    const float z61 = f.position().z;
    check_near("z after 61 walk frames", 420.0 * 61 * kDt, z61, 1e-3);
    check_near("measured speed over 60 frames (u/s)", 420.0,
               (z61 - z1) / (60.0 * kDt), 1e-3);
    check_bits("x untouched by pure facing-forward walk", 0.0f, f.position().x);

    in.set(fnd::input::Action::Up, false);
    tick(f, in);
    check_int("state after releasing Up", static_cast<int>(FighterState::Idle),
              static_cast<int>(f.state()));
    check_bits("velocity zeroed on release (position frozen)", z61, f.position().z);

    // The reported lock-on bug: forward must close on the locked opponent,
    // wherever it stands — not march world -Z. Facing +X with the opponent
    // down +X, holding Up walks +X and shrinks the gap.
    Fighter hunter;
    hunter.init(nullptr, nullptr, glm::vec3(0, 0, 0), 1.5707964f);
    settle(hunter);
    Fighter prey = make_idle_fighter(glm::vec3(500, 0, 0));
    Input fwd;
    fwd.set(fnd::input::Action::Up, true);
    for (int i = 0; i < 61; ++i) tick(hunter, fwd, &prey);
    check_near("forward walks +X when facing +X", 420.0 * 61 * kDt,
               hunter.position().x, 1e-3);
    check_near("no sideways drift while closing", 0.0, hunter.position().z, 1e-4);
    check_near("facing stays locked on the opponent", 1.5707964,
               hunter.facing_yaw(), 1e-6);
    check_near("the gap to the opponent shrinks by the walked distance",
               500.0 - 420.0 * 61 * kDt,
               500.0 - hunter.position().x, 1e-3);

    // Stick deflection past the deadzone walks too (same 8000 threshold).
    Fighter s = make_idle_fighter(glm::vec3(0, 0, 0));
    Input si;
    si.p.stick_x = 32767;
    tick(s, si);
    check_int("stick past the deadzone enters Walk", static_cast<int>(FighterState::Walk),
              static_cast<int>(s.state()));
    if (g_testCombo.ready) {
        check_near("full stick follows its nineteen-degree turn arc",
                   7.2 * std::sin(glm::radians(19.f)), s.position().x, 1e-6);
        check_near("full stick preserves recovered walk distance", 7.2,
                   glm::length(s.position()), 1e-5);
    } else {
        // The data-free CI path exercises the legacy fallback, not a recovered
        // character handler: right-stick movement uses the fallback 7 units/tick.
        check_near("fallback full stick uses kWalkSpeed", 420.0 * kStep,
                   s.position().x, 1e-6);
        check_near("fallback full stick distance", 420.0 * kStep,
                   glm::length(s.position()), 1e-5);
    }
    si.p.stick_x = 4000;   // inside the 8000 deadzone
    tick(s, si);
    check_int("stick inside the deadzone is rest", static_cast<int>(FighterState::Idle),
              static_cast<int>(s.state()));
}

// ===========================================================================
//  Case 2 — run/dash: double-tap, kRunSpeed 200, kDashStamina 20,
//           air dash 260 once per airtime
// ===========================================================================
void test_dash() {
    section("2. dash (double-tap, 200 u/s, 20 stamina, once per airtime)");
    Fighter f = make_idle_fighter(glm::vec3(0, 0, 0));
    Input in;

    // tap, release, tap → the second tap is 2 frames after the first
    // (2*dt = 0.0333 <= kDoubleTapSec 0.30).
    in.set(fnd::input::Action::Up, true);
    tick(f, in);
    check_int("single tap does not dash", static_cast<int>(FighterState::Walk),
              static_cast<int>(f.state()));
    in.set(fnd::input::Action::Up, false);
    tick(f, in);
    const float z_before = f.position().z;
    in.set(fnd::input::Action::Up, true);
    tick(f, in);
    check_int("second tap within window dashes", static_cast<int>(FighterState::Run),
              static_cast<int>(f.state()));
    check_bool("dash is airborne flag", false, f.airborne());

    // Up maps to facing-forward = +Z (fighter.cpp:579), the same basis the walk
    // uses now: a tap and a hold agree about where "up" goes, so a dash fired
    // while walking keeps the line instead of reversing it.
    check_near(g_testCombo.ready ? "recovered ground dash first-frame distance"
                                 : "fallback ground dash first-frame distance",
               g_testCombo.ready ? 17.0 : 900.0 * kDt,
               f.position().z - z_before, 1e-5);
    // The fallback spends a trigger cost and gets one tick of grounded regen;
    // the recovered handler instead spends its per-update cost.
    check_int(g_testCombo.ready ? "recovered dash drains per update without trigger cost"
                                : "fallback dash spends trigger stamina then regenerates",
              g_testCombo.ready ? 98 : 81, f.stamina());

    // Both paths keep the direction committed during these twenty updates.
    const float z_dash0 = f.position().z;
    for (int i = 0; i < 19; ++i) tick(f, in);
    const float z_dash19 = f.position().z;
    const double dashStep = g_testCombo.ready ? 17.0 : 900.0 * kDt;
    check_near(g_testCombo.ready ? "recovered dash travel over twenty held updates"
                                 : "fallback dash travel over twenty held updates",
               dashStep * 20, z_dash19 - z_before, 1e-3);
    check_near(g_testCombo.ready ? "recovered dash speed at this tick rate"
                                 : "fallback dash speed at this tick rate",
               dashStep / kDt, (z_dash19 - z_dash0) / (19.0 * kDt), 1.0);
    in.set(fnd::input::Action::Up,false);
    tick(f, in);
    check_int(g_testCombo.ready ? "release selects recovered dash phase"
                                : "fallback dash has no animation phase",
              g_testCombo.ready ? 2 : 0, f.move_phase());
    for (int i = 0; i < 180 && f.state() == FighterState::Run; ++i) tick(f,in);
    check_int("dash completes its actual recovery period and hold", static_cast<int>(FighterState::Idle),
              static_cast<int>(f.state()));
    // Stamina regenerates back to the cap while grounded and actionable.
    for (int i = 0; i < 100; ++i) tick(f, in);
    check_int("stamina back at cap after dash", 100, f.stamina());

    // An exhausted hold breaks Guard before stamina can fund another dash.
    Fighter g = make_idle_fighter(glm::vec3(0, 0, 0));
    Input gi;
    gi.set(fnd::input::Action::Guard, true);
    for (int i = 0; i < 300; ++i) {
        tick(g, gi);
        if (g.state() != FighterState::Guard) break;
    }
    check_int("guard drained stamina to 0", 0, g.stamina());
    gi.set(fnd::input::Action::Guard, false);
    g.take_damage(5, nullptr);            // Hit: 15 frames with no regen
    for (int i = 0; i < 15; ++i) tick(g, gi);
    check_int("out of Guard through damage", static_cast<int>(FighterState::Idle),
              static_cast<int>(g.state()));
    check_bool("stamina still below kDashStamina", g.stamina() < 20, true);
    gi.set(fnd::input::Action::Up, true);
    tick(g, gi);
    gi.set(fnd::input::Action::Up, false);
    tick(g, gi);
    gi.set(fnd::input::Action::Up, true);
    tick(g, gi);
    if (g_testCombo.ready) {
        check_int("a partial pool can fund the source's per-update dash drain",
                  static_cast<int>(FighterState::Run), static_cast<int>(g.state()));
        check_bool("recovered dash does not spend a trigger cost", true, g.stamina() < 20);
    } else {
        check_int("fallback dash is refused below its stamina threshold",
                  static_cast<int>(FighterState::Walk), static_cast<int>(g.state()));
        check_bool("refused fallback dash leaves stamina unchanged", true, g.stamina() < 20);
    }

    // Air dash: jump, then double-tap while airborne.
    Fighter a = make_idle_fighter(glm::vec3(0, 0, 0));
    Input ai;
    ai.set(fnd::input::Action::Jump, true);
    tick(a, ai);
    check_bool("airborne after jump", true, a.airborne());
    ai.set(fnd::input::Action::Jump, false);
    tick(a, ai);
    ai.set(fnd::input::Action::Up, true);
    tick(a, ai);
    ai.set(fnd::input::Action::Up, false);
    tick(a, ai);
    const float y_air = a.position().y;
    const float z_air = a.position().z;
    const int stamina_before_air = a.stamina();
    ai.set(fnd::input::Action::Up, true);
    tick(a, ai);
    check_int("air dash enters Run", static_cast<int>(FighterState::Run),
              static_cast<int>(a.state()));
    check_bool("air dash keeps the fighter airborne", true, a.airborne());
    check_bits("air dash hangs (y frozen)", y_air, a.position().y);
    check_bits("air dash first-frame dz", 1200.0f * kStep, a.position().z - z_air);
    const int stamina_after_air = a.stamina();
    check_int("air dash spend is kDashStamina", stamina_before_air - 20,
              stamina_after_air);

    // Second double-tap in the same airtime: refused, no spend, state kept.
    ai.set(fnd::input::Action::Up, false);
    tick(a, ai);
    ai.set(fnd::input::Action::Up, true);
    tick(a, ai);
    check_int("second air dash refused (state kept)", static_cast<int>(FighterState::Run),
              static_cast<int>(a.state()));
    check_int("second air dash spends no stamina", stamina_after_air, a.stamina());

    // The dash window ends mid-air → back to Jump, gravity resumes.
    ai.set(fnd::input::Action::Up, false);
    for (int i = 0; i < 19; ++i) tick(a, ai);
    check_int("air dash expires into Jump", static_cast<int>(FighterState::Jump),
              static_cast<int>(a.state()));
    const float y_hang = a.position().y;
    tick(a, ai);
    check_bool("gravity resumes after the air dash", a.position().y < y_hang, true);
}

// ===========================================================================
//  Case 3 — neutral attack move and hit behavior from Rena 0 + item 1
// ===========================================================================
void test_attacks() {
    section("3. Rena 0 neutral attack uses its weapon-bound move row");
    if (!g_testCombo.ready) return skip_case("Rena 0 neutral attack");

    const gameplay::CharacterMove* move = g_testCombo.moves.find(300);
    check_bool("Rena 0 slot-0 table contains neutral move 300", true, move != nullptr);
    check_int("move 300 starts on phase tag 31", 31,
              move ? move->first_set_index() : -1);

    Fighter attacker = make_idle_fighter(glm::vec3(0, 0, 0));
    Fighter target = make_idle_fighter(glm::vec3(0, 0, 40));
    Input in;
    in.set(fnd::input::Action::AttackA, true);
    tick(attacker, in);
    in.set(fnd::input::Action::AttackA, false);
    check_int("neutral attack enters AttackA", static_cast<int>(FighterState::AttackA),
              static_cast<int>(attacker.state()));
    check_int("grounded neutral attack uses the port's move-300 candidate", 300,
              attacker.attack_move_id());
    bool hit = attacker.try_melee_hit(target);
    for (int i = 0; !hit && i < 240 && attacker.state() == FighterState::AttackA; ++i) {
        tick(attacker, in);
        if (attacker.melee_in_active()) test::Combo::placeAtAttack(attacker,target);
        hit = attacker.try_melee_hit(target);
    }
    check_bool("Rena 0's weapon move connects inside its recovered sphere", true, hit);
    check_bool("the weapon move applies its parsed HP damage", true, target.hp() < 100);

    // There is no second melee action to test: the enum has one attack key (issue #10), and
    // the heavy stand-in's state and damage value are gone.
}

// ===========================================================================
//  Case 4 — hit stun 15 frames, blocked movement (friction), re-hit resets
// ===========================================================================
void test_hit_stun() {
    section("4. hit stun (15 frames, movement locked)");
    Fighter b = make_idle_fighter(glm::vec3(0, 0, 0));
    b.take_damage(5, nullptr);
    check_int("state after damage", static_cast<int>(FighterState::Hit),
              static_cast<int>(b.state()));
    check_int("hp after 5 damage", 95, b.hp());
    for (int i = 0; i < 14; ++i) b.update(nullptr, nullptr, kDt);
    check_int("still stunned at frame 14", static_cast<int>(FighterState::Hit),
              static_cast<int>(b.state()));
    b.update(nullptr, nullptr, kDt);
    check_int("stun ends at frame 15", static_cast<int>(FighterState::Idle),
              static_cast<int>(b.state()));

    // Re-hit during the stun resets the timer.
    b.take_damage(5, nullptr);
    for (int i = 0; i < 10; ++i) b.update(nullptr, nullptr, kDt);
    b.take_damage(5, nullptr);
    int frames = 0;
    while (b.state() == FighterState::Hit && frames < 100) {
        b.update(nullptr, nullptr, kDt);
        ++frames;
    }
    check_int("re-hit restarts the 15-frame stun", 15, frames);

    // Guarded damage: amount/5 with a floor of 1. The first hit leaves Guard
    // (the stun transition), so the later hits are unguarded — see case 5.
    Fighter g = make_idle_fighter(glm::vec3(0, 0, 0));
    Input in;
    in.set(fnd::input::Action::Guard, true);
    tick(g, in);
    check_int("guard state", static_cast<int>(FighterState::Guard),
              static_cast<int>(g.state()));
    g.take_damage(12, nullptr);
    check_int("guard reduces 12 -> 12/5", 100 - 2, g.hp());
    check_int("a guarded hit still stuns (leaves Guard)",
              static_cast<int>(FighterState::Hit), static_cast<int>(g.state()));
    g.take_damage(5, nullptr);
    check_int("second hit is unguarded (state is Hit)", 98 - 5, g.hp());
    g.take_damage(1, nullptr);
    check_int("damage floor is 1", 93 - 1, g.hp());
}

// ===========================================================================
//  Case 5 — live Guard lifecycle at the selected 64 Hz simulation cadence
// ===========================================================================
void test_guard_drain() {
    section("5. Guard release, exhaustion and interruptions at 64 Hz");
    auto step = [](Fighter& f, Input& in) {
        fnd::input::compute_edges(in.p);
        f.update(&in.p, nullptr, gameplay::FixedStep::seconds);
    };
    auto guarding = [&]() {
        Fighter f = make_idle_fighter(glm::vec3(0));
        Input in;
        in.set(fnd::input::Guard, true);
        step(f, in);
        return f;
    };
    std::vector<int> interruptActions = {fnd::input::Right, fnd::input::Jump};
    if (g_testCombo.ready) {
        interruptActions.push_back(fnd::input::Action::AttackA);
        interruptActions.push_back(fnd::input::Action::Shoot);
    } else {
        skip_case("guard release to attack/shoot");
    }
    for (auto action : interruptActions) {
        Fighter f = guarding();
        Input in;
        in.set(action, true);
        step(f, in);
        if (action == fnd::input::Shoot) {
            in.clear();
            step(f, in);
        }
        const auto expected = action == fnd::input::Right ? FighterState::Walk :
            action == fnd::input::Jump ? FighterState::Jump :
            action == fnd::input::Shoot ? FighterState::ShootA : FighterState::AttackA;
        check_int("release permits next action immediately", static_cast<int>(expected),
                  static_cast<int>(f.state()));
    }
    Fighter f = make_idle_fighter(glm::vec3(0));
    Input in;
    in.set(fnd::input::Guard, true);
    for (int i = 0; i < 64; ++i) step(f, in);
    check_int("one second held drains 25 stamina", 75, f.stamina());
    check_int("held Guard persists", static_cast<int>(FighterState::Guard), static_cast<int>(f.state()));
    in.clear();
    step(f, in);
    check_int("release returns to Idle", static_cast<int>(FighterState::Idle), static_cast<int>(f.state()));
    for (int i = 0; i < 64; ++i) step(f, in);
    check_int("released Guard regenerates to cap", 100, f.stamina());

    in.set(fnd::input::Guard, true);
    for (int i = 0; i < 256; ++i) step(f, in);
    check_int("four seconds drain stamina to zero", 0, f.stamina());
    check_int("exhaustion exits Guard on the draining tick", static_cast<int>(FighterState::Idle), static_cast<int>(f.state()));
    for (int i = 0; i < 128; ++i) step(f, in);
    check_int("holding exhausted Guard cannot re-enter", static_cast<int>(FighterState::Idle), static_cast<int>(f.state()));
    check_int("exhausted hold allows stamina recovery", 100, f.stamina());
    in.clear();
    step(f, in);
    in.set(fnd::input::Guard, true);
    step(f, in);
    check_int("fresh hold can guard again", static_cast<int>(FighterState::Guard), static_cast<int>(f.state()));
    f.reset(glm::vec3(0), 0);
    settle(f);
    step(f, in);
    check_int("round reset permits Guard", static_cast<int>(FighterState::Guard), static_cast<int>(f.state()));

    Fighter lost = guarding();
    lost.update(nullptr, nullptr, gameplay::FixedStep::seconds);
    check_int("missing controller input releases Guard", static_cast<int>(FighterState::Idle), static_cast<int>(lost.state()));
    Fighter air = make_idle_fighter(glm::vec3(0));
    Input ai;
    ai.set(fnd::input::Jump, true);
    step(air, ai);
    ai.clear();
    ai.set(fnd::input::Guard, true);
    step(air, ai);
    check_bool("airborne Guard entered", air.state() == FighterState::Guard, true);
    ai.clear();
    step(air, ai);
    check_bool("airborne release returns to Jump", air.state() == FighterState::Jump && air.airborne(), true);

    Fighter hit = guarding();
    hit.take_damage(5);
    in.clear();
    step(hit, in);
    check_int("release cannot cancel hitstun", static_cast<int>(FighterState::Hit), static_cast<int>(hit.state()));
    in.set(fnd::input::Guard, true);
    step(hit, in);
    check_int("held Guard cannot cancel hitstun", static_cast<int>(FighterState::Hit), static_cast<int>(hit.state()));
    hit.take_damage(1000);
    in.clear();
    step(hit, in);
    check_int("release cannot cancel KO", static_cast<int>(FighterState::KO), static_cast<int>(hit.state()));
}

// ===========================================================================
//  Case 6 — jump / gravity / landing and the fly budget
// ===========================================================================
void test_air() {
    section("6. jump/gravity/landing (kGravity 1800, kJumpSpeed 720, fly 1.2 s)");
    check_bits("kGravity", 1800.0f, FighterConstants::kGravity);
    check_bits("kJumpSpeed", 720.0f, FighterConstants::kJumpSpeed);
    check_bits("kFlyRise", 720.0f, FighterConstants::kFlyRise);
    check_bits("kFlyTimeSec", 1.2f, FighterConstants::kFlyTimeSec);
    check_bits("kFlyMaxAlt", 420.0f, FighterConstants::kFlyMaxAlt);

    Fighter f = make_idle_fighter(glm::vec3(0, 0, 0));
    Input in;
    in.set(fnd::input::Action::Jump, true);
    tick(f, in);
    check_bool("airborne on the leap frame", true, f.airborne());
    check_int("leap state", static_cast<int>(FighterState::Jump),
              static_cast<int>(f.state()));
    // try_jump writes kJumpSpeed, then the same frame's fly-rise branch overwrites
    // it — but both are 720 now (the leap matches the 0x29 fly-takeoff vy 12/tick),
    // so the overwrite is unobservable and the first frame rises 720*dt either way.
    check_bits("leap frame rise", 720.0f * kStep, f.position().y);
    check_int("leap spends kJumpStamina and one fly tick", 89, f.stamina());

    // Powered climb: frames rising at kFlyRise * dt, until the kFlyMaxAlt ceiling
    // caps the climb (720 u/s reaches 420 in 35 frames; the 1.2 s budget would
    // allow ~73). The ceiling hold is by design — budget outlasts the climb.
    int rise_frames = 1;   // the leap frame above
    float prev_y = f.position().y;
    float peak_y = prev_y;
    int peak_frame = 1;
    int land_frame = -1;
    for (int i = 2; i <= 200 && land_frame < 0; ++i) {
        tick(f, in);
        const float dy = f.position().y - prev_y;
        if (std::fabs(dy - 720.0f * kStep) < 1e-4) ++rise_frames;
        if (f.position().y > peak_y) { peak_y = f.position().y; peak_frame = i; }
        if (!f.airborne()) land_frame = i;
        prev_y = f.position().y;
    }
    check_int("powered rise frames before the ceiling", 35, rise_frames);
    check_int("peak-altitude frame", 35, peak_frame);
    check_bits("the ceiling caps the climb at kFlyMaxAlt", 420.0f, peak_y);
    check_int("landing frame after the leap", 114, land_frame);
    check_bits("landing snaps y to groundY", 0.0f, f.position().y);
    check_bool("grounded after landing", false, f.airborne());
    check_int("landing state", static_cast<int>(FighterState::Idle),
              static_cast<int>(f.state()));
    check_int("stamina after flight (no airborne regen)", 53, f.stamina());

    // The fly budget resets on landing: jump again and the climb caps at 420 again.
    in.set(fnd::input::Action::Jump, false);
    tick(f, in);
    in.set(fnd::input::Action::Jump, true);
    tick(f, in);
    float peak2 = f.position().y;
    for (int i = 2; i <= 100; ++i) {
        tick(f, in);
        peak2 = std::max(peak2, f.position().y);
        if (!f.airborne()) break;
    }
    check_bits("second flight caps at the ceiling again", 420.0f, peak2);

    // Gravity while airborne and not flying: vy loses kGravity*dt per frame.
    Fighter g = make_idle_fighter(glm::vec3(0, 0, 0));
    Input gi;
    gi.set(fnd::input::Action::Jump, true);
    tick(g, gi);
    gi.set(fnd::input::Action::Jump, false);
    tick(g, gi);
    const float dy1 = g.position().y - 720.0f * kStep;
    tick(g, gi);
    const float dy2 = g.position().y - 720.0f * kStep - dy1;
    check_near("gravity step 1", 690.0 * kDt, dy1, 1e-5);
    check_near("gravity step 2", 660.0 * kDt, dy2, 1e-5);

    // Air control scales walk speed by kAirControl while airborne.
    Fighter h = make_idle_fighter(glm::vec3(0, 0, 0));
    Input hi;
    hi.set(fnd::input::Action::Jump, true);
    tick(h, hi);
    hi.set(fnd::input::Action::Jump, false);
    tick(h, hi);
    const float x0 = h.position().x;
    hi.set(fnd::input::Action::Right, true);
    tick(h, hi);
    check_near(g_testCombo.ready ? "air control scales recovered walk distance by 0.7"
                                 : "fallback air control scales kWalkSpeed by 0.7",
               g_testCombo.ready ? 7.2 * 0.7 : 420.0 * 0.7 * kDt,
               h.position().x - x0, 1e-5);
    check_bits("kAirControl", 0.7f, FighterConstants::kAirControl);
}

// ===========================================================================
//  Case 7 — callback-time ammo, charge counters and provisional EX entry
// ===========================================================================
void test_shots() {
    section("7. Callback-time shooting and charge counters (Rena 0 + item 1)");
    if (!g_testCombo.ready) return skip_case("Rena 0 shooting paths");
    Fighter f = make_idle_fighter({});
    Input in;
    in.set(fnd::input::Action::Shoot, true);
    tick(f, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(f, in);
    check_int("Tap selection enters move400", 400, f.shot_move_id());
    check_int("Selecting a programmed shot spends no MAIN", 6, f.main_whole());
    check_bool("Selection has no admitted projectile", false, f.take_pending_shot().armed);
    for (int i = 0; i < 12; ++i) tick(f, in);
    const auto tap = f.take_pending_shot();
    check_bool("Tick12 callback admits the normal tap", true, tap.armed);
    check_int("Tap callback uses row0", 0, tap.bulletRow);
    check_int("Tap callback consumes one MAIN round", 5, f.main_whole());
    check_near("Tap callback precedes one original refill tick", 5.0 + 1.0 / 300.0,
               f.main_frac() * 6, 1e-5);
    check_bool("Zero row interval has no artificial reloadNG", true, f.reload_ok());

    int shotStateTicks = 12;
    while (f.state() == FighterState::ShootA && shotStateTicks < 100) {
        tick(f, in);
        ++shotStateTicks;
    }
    const int set = g_testCombo.moves.first_set_index(400);
    const int period = static_cast<int>(std::nearbyint(g_testCombo.model.anims[set].duration /
        g_testCombo.model.ticksPerSecond / gameplay::kOriginalAnimationTick));
    check_int("Tap still finishes on its actual clip period", period - 1, shotStateTicks);
    check_int("Tap still returns to Idle", static_cast<int>(FighterState::Idle), static_cast<int>(f.state()));

    Fighter charged = make_idle_fighter({});
    Input ci;
    ci.set(fnd::input::Action::Shoot, true);
    for (int i = 0; i < 29; ++i) tick(charged, ci);
    check_int("Initial29 updates remain Tap", static_cast<int>(ShotTier::Tap), static_cast<int>(charged.charge_tier()));
    tick(charged, ci);
    check_int("Initial30 updates reach Yellow", static_cast<int>(ShotTier::Yellow), static_cast<int>(charged.charge_tier()));
    check_near("Yellow charge fraction uses initial30 plus secondary180", 30.0 / 210.0,
               charged.charge_hold_frac(), 1e-6);
    ci.set(fnd::input::Action::Shoot, false);
    tick(charged, ci);
    check_int("Yellow selection binds move450", 450, charged.shot_move_id());
    check_int("Yellow selection spends no CHARGE", 2, charged.charge_whole());
    for (int i = 0; i < 13; ++i) tick(charged, ci);
    const auto yellow = charged.take_pending_shot();
    check_bool("Tick13 admits Yellow row2", true, yellow.armed && yellow.bulletRow == 2);
    check_int("Yellow row2 consumes secondary magazine", 1, charged.charge_whole());
    check_int("Yellow row2 leaves primary magazine untouched", 6, charged.main_whole());

    Fighter red = make_idle_fighter({});
    Input ri;
    ri.set(fnd::input::Action::Shoot, true);
    for (int i = 0; i < 209; ++i) tick(red, ri);
    check_int("Before secondary180 threshold remains Yellow", static_cast<int>(ShotTier::Yellow), static_cast<int>(red.charge_tier()));
    tick(red, ri);
    check_int("Initial30 plus secondary180 reaches Red", static_cast<int>(ShotTier::Red), static_cast<int>(red.charge_tier()));
    check_bits("Red charge meter reaches full", 1.f, red.charge_hold_frac());
    ri.set(fnd::input::Action::Shoot, false);
    tick(red, ri);
    check_int("Red selects move360 without eager spending", 360, red.shot_move_id());
    check_int("Unmetered red rows preserve CHARGE stock", 2, red.charge_whole());
    int redRequests = 0;
    for (int i = 0; i < 150; ++i) {
        tick(red, ri);
        for (auto shot = red.take_pending_shot(); shot.armed; shot = red.take_pending_shot()) {
            ++redRequests;
            check_bool("Red request is one of original unmetered rows11/12", true,
                       shot.bulletRow == 11 || shot.bulletRow == 12);
        }
    }
    check_int("Red path admits twin unmetered requests", 2, redRequests);
    check_int("Red request admission preserves primary stock", 6, red.main_whole());
    check_int("Red request admission preserves secondary stock", 2, red.charge_whole());

    // EX selection is still a provisional port path; preserve its input/event coverage.
    Fighter exOwner = make_idle_fighter({});
    exOwner.set_hyper_gauge(1.f);
    Input xi;
    xi.set(fnd::input::Action::Special, true);
    tick(exOwner, xi);
    check_bool("Full gauge Special still activates hypermode", true, exOwner.hyper_active());
    xi.set(fnd::input::Action::Special, false);
    tick(exOwner, xi);
    xi.set(fnd::input::Action::Special, true);
    tick(exOwner, xi);
    const auto ex = exOwner.take_pending_shot();
    check_bool("Active-mode Special still arms provisional EX", true, ex.armed);
    check_int("Provisional EX still carries its tier", static_cast<int>(ShotTier::Ex), static_cast<int>(ex.tier));
    check_int("Provisional EX still enters ShotFinal", static_cast<int>(FighterState::ShotFinal), static_cast<int>(exOwner.state()));
    check_int("Provisional EX admits its selected secondary row", 1, exOwner.charge_whole());

}

void test_ammo() {
    section("8. Original refill and row admission (Rena 0 + item 1)");
    if (!g_testCombo.ready) return skip_case("Rena 0 ammo fixture");
    const auto fireTap = [](Fighter& fighter, Input& input) {
        input.set(fnd::input::Action::Shoot, true);
        tick(fighter, input);
        input.set(fnd::input::Action::Shoot, false);
        tick(fighter, input);
        for (int i = 0; i < 12; ++i) tick(fighter, input);
        return fighter.take_pending_shot();
    };
    Fighter plain = make_idle_fighter({});
    Input in;
    check_bool("Ammo refill witness actually admits a shot", true, fireTap(plain, in).armed);
    const float before = plain.main_frac() * 6.f;
    for (int i = 0; i < 30; ++i) tick(plain, in);
    check_near("Normal refill adds30/300 of a MAIN round", 0.1, plain.main_frac() * 6 - before, 1e-5);
    for (int i = 0; i < 268; ++i) tick(plain, in);
    check_int("MAIN remains five rounds before threshold300", 5, plain.main_whole());
    tick(plain, in);
    check_int("MAIN returns to six at threshold300", 6, plain.main_whole());

    Fighter friendship = make_idle_fighter({});
    friendship.set_hypermode(Hypermode::Friendship);
    friendship.set_hyper_gauge(1.f);
    Input hi;
    hi.set(fnd::input::Action::Special, true);
    tick(friendship, hi);
    hi.set(fnd::input::Action::Special, false);
    tick(friendship, hi);
    check_bool("Friendship witness is active", true, friendship.hyper_active());
    check_bool("Friendship witness actually admits a shot", true, fireTap(friendship, hi).armed);
    const float boostedBefore = friendship.main_frac() * 6.f;
    for (int i = 0; i < 30; ++i) tick(friendship, hi);
    check_near("Friendship refillStep3 adds90/300 of a round", 0.3,
               friendship.main_frac() * 6 - boostedBefore, 1e-5);

    std::array<gameplay::ShootingMagazine, 2> magazines = {
        gameplay::ShootingMagazine::from_definition(g_testCombo.weapon.magazines[0]),
        gameplay::ShootingMagazine::from_definition(g_testCombo.weapon.magazines[1])};
    check_bool("Row0 admits against primary magazine", true,
               gameplay::admit_shooting_row(g_testCombo.weapon, 0, magazines));
    check_bool("Row2 admits against secondary magazine", true,
               gameplay::admit_shooting_row(g_testCombo.weapon, 2, magazines));
    check_int("Mixed rows consume primary once", 5, magazines[0].rounds);
    check_int("Mixed rows consume secondary once", 1, magazines[1].rounds);
    magazines[0].rounds = magazines[1].rounds = 0;
    check_bool("Metered row rejects empty primary", false,
               gameplay::admit_shooting_row(g_testCombo.weapon, 0, magazines));
    check_bool("Negative magazine row11 bypasses both empty stocks", true,
               gameplay::admit_shooting_row(g_testCombo.weapon, 11, magazines));
    check_int("Unmetered row does not mutate primary", 0, magazines[0].rounds);
    check_int("Unmetered row does not mutate secondary", 0, magazines[1].rounds);
    bool invalidRowRejected = false;
    try { gameplay::admit_shooting_row(g_testCombo.weapon, g_testCombo.weapon.bulletCount, magazines); }
    catch (const std::out_of_range&) { invalidRowRejected = true; }
    check_bool("Invalid callback row fails explicitly", true, invalidRowRejected);

    // Failed pool creation follows consumption (FUN_00435450), with no refund.
    Fighter owner = make_idle_fighter({});
    ProjectilePool pool;
    for (int i = 0; i < g_testCombo.weapon.bullets[0].poolCapacity; ++i)
        check_bool("Pool saturation witness spawns real row0", true,
                   pool.spawn({}, {0, 0, 1}, ShotTier::Tap, &owner, 0));
    Input oi;
    const auto rejected = fireTap(owner, oi);
    check_bool("Live callback admits before rejected pool creation", true, rejected.armed);
    check_bool("Per-row full pool rejects creation", false,
               pool.spawn(rejected.pos, rejected.dir, rejected.tier, &owner, rejected.bulletRow, rejected.target));
    check_int("Pool failure does not refund the live consumed round", 5, owner.main_whole());

    Fighter exhausted = make_idle_fighter({});
    Input ei;
    for (int charge = 0; charge < 2; ++charge) {
        hold_yellow(exhausted, ei);
        ei.set(fnd::input::Action::Shoot, false);
        tick(exhausted, ei);
        for (int tickIndex = 0; tickIndex < 13; ++tickIndex) tick(exhausted, ei);
        check_bool("Secondary depletion witness admits row2", true, exhausted.take_pending_shot().armed);
        int limit = 100;
        while (exhausted.state() != FighterState::Idle && limit-- > 0) tick(exhausted, ei);
    }
    check_int("Secondary depletion witness is empty", 0, exhausted.charge_whole());
    check_bool("Empty secondary does not prevent primary tap selection", true, exhausted.can_fire(ShotTier::Tap));
    check_bool("Empty secondary rejects charged selection", false, exhausted.can_fire(ShotTier::Yellow));
    check_bool("C release with empty secondary still admits a primary tap", true, fireTap(exhausted, ei).armed);
    check_int("Empty secondary tap consumes only primary", 5, exhausted.main_whole());

    friendship.fill_gauges();
    check_int("F4 fills migrated MAIN stock", 6, friendship.main_whole());
    check_int("F4 fills migrated CHARGE stock", 2, friendship.charge_whole());
    friendship.reset({}, 0.f);
    check_int("Reset fills migrated MAIN stock", 6, friendship.main_whole());
}

// ===========================================================================
//  Case 9 — hypermode: gauge fill, duration, modifiers, stun rules, death save
// ===========================================================================
void test_hypermode() {
    section("9. hypermode (Friendship / Oyashiro / Kakera)");
    const gameplay::HypermodeParams fr = gameplay::hypermode_params(Hypermode::Friendship);
    const gameplay::HypermodeParams oy = gameplay::hypermode_params(Hypermode::Oyashiro);
    const gameplay::HypermodeParams ka = gameplay::hypermode_params(Hypermode::Kakera);
    check_u32("Friendship aura", 0xFF82DCFFu, fr.aura);
    check_u32("Oyashiro aura", 0xFFFF6EDCu, oy.aura);
    check_u32("Kakera aura", 0xFF96FFA0u, ka.aura);
    check_near("Friendship fillPerDamageDealt", 1.0 / 60.0, fr.fillPerDamageDealt, 1e-9);
    check_near("Oyashiro fillPerDamageTaken", 1.0 / 50.0, oy.fillPerDamageTaken, 1e-9);
    check_near("Kakera fillPerDamageTaken", 1.0 / 90.0, ka.fillPerDamageTaken, 1e-9);
    check_bits("Friendship durationSec", 15.0f, fr.durationSec);
    check_bits("Oyashiro durationSec", 15.0f, oy.durationSec);
    check_bits("Kakera durationSec", 25.0f, ka.durationSec);
    check_bits("Friendship damageTakenMul", 1.0f, fr.damageTakenMul);
    check_bits("Oyashiro damageTakenMul", 0.75f, oy.damageTakenMul);
    check_bits("Oyashiro damageDealtMul", 1.5f, oy.damageDealtMul);
    check_bits("Kakera damageTakenMul", 0.20f, ka.damageTakenMul);
    check_bits("Kakera damageDealtMul", 1.5f, ka.damageDealtMul);
    check_bool("Kakera autoOnDeath", true, ka.autoOnDeath);
    check_bool("Kakera stunImmune", true, ka.stunImmune);
    check_bool("Oyashiro stunEveryOtherHit", true, oy.stunEveryOtherHit);
    check_bool("Friendship has no stun rule", false, fr.stunImmune);
    check_bool("Oyashiro has no stun immunity", false, oy.stunImmune);
    check_bits("Friendship mainRechargeMul", 1.6f, fr.mainRechargeMul);
    check_bits("Friendship chargeRechargeMul", 1.6f, fr.chargeRechargeMul);
    check_bits("Kakera recharge unmodified", 1.0f, ka.mainRechargeMul);

    // --- Friendship: gauge fills by damage dealt (1/60 per HP) ---
    {
        Fighter a = make_idle_fighter(glm::vec3(0, 0, 0));
        Fighter b = make_idle_fighter(glm::vec3(0, 0, 100));
        check_bits("gauge starts empty", 0.0f, a.hyper_gauge());
        b.take_damage(5, &a);
        check_near("Friendship gauge after dealing 5", 5.0 / 60.0, a.hyper_gauge(), 1e-7);
        check_bits("Friendship takes no gauge from damage taken", 0.0f, b.hyper_gauge());
        check_bool("not ready at 5/60", false, a.hyper_ready());
        for (int i = 0; i < 11; ++i) b.take_damage(5, &a);
        // 12 additions of 5*(1/60) sum to 0.99999988 in float, just under the
        // 1.0 clamp; the 13th hit clamps it. Same arithmetic as the DX9 build.
        check_near("gauge after 12 hits is 1.0 - 1ulp", 1.0 - 1.1920929e-7,
                   a.hyper_gauge(), 1e-9);
        check_bool("not ready at 0.99999988", false, a.hyper_ready());
        b.take_damage(5, &a);
        check_bits("gauge clamps to 1 on the 13th hit", 1.0f, a.hyper_gauge());
        check_bool("ready at a full gauge", true, a.hyper_ready());
    }

    // --- Friendship: activation, 15 s duration, gauge lock while active ---
    {
        Fighter f = make_idle_fighter(glm::vec3(0, 0, 0));
        f.set_hypermode(Hypermode::Friendship);
        f.set_hyper_gauge(1.0f);
        Input in;
        in.set(fnd::input::Action::Special, true);
        tick(f, in);
        check_bool("activated on S", true, f.hyper_active());
        check_bits("gauge spent on activation", 0.0f, f.hyper_gauge());
        check_bits("duration set to 15 s", 15.0f, f.hyper_seconds_left());
        check_bool("not ready while active", false, f.hyper_ready());
        in.set(fnd::input::Action::Special, false);
        for (int i = 0; i < 900; ++i) tick(f, in);
        check_bool("still active at frame 900", true, f.hyper_active());
        tick(f, in);
        check_bool("expires at frame 901", false, f.hyper_active());
        check_bits("timer floored at 0 on expiry", 0.0f, f.hyper_seconds_left());

        // An active mode cannot refill its own gauge.
        Fighter g = make_idle_fighter(glm::vec3(0, 0, 0));
        g.set_hypermode(Hypermode::Friendship);
        g.set_hyper_gauge(1.0f);
        Input gi;
        gi.set(fnd::input::Action::Special, true);
        tick(g, gi);
        gi.set(fnd::input::Action::Special, false);
        Fighter v = make_idle_fighter(glm::vec3(0, 0, 100));
        v.take_damage(5, &g);
        check_bits("no gauge while active", 0.0f, g.hyper_gauge());
        // ... and taking damage while active does not fill it either.
        g.take_damage(5, &v);
        check_bits("no gauge from damage taken while active", 0.0f, g.hyper_gauge());
    }

    // --- Friendship: no damage-taken modifier, no stun immunity ---
    {
        Fighter a = make_idle_fighter(glm::vec3(0, 0, 0));
        a.set_hypermode(Hypermode::Friendship);
        a.set_hyper_gauge(1.0f);
        Input in;
        in.set(fnd::input::Action::Special, true);
        tick(a, in);
        in.set(fnd::input::Action::Special, false);
        Fighter b = make_idle_fighter(glm::vec3(0, 0, 400));
        a.take_damage(5, &b);
        check_int("Friendship takes unmodified damage", 95, a.hp());
        check_bool("Friendship does not stun-immune", true,
                   a.state() == FighterState::Hit);
    }

    // --- Oyashiro: gauge by damage taken, activation knockback, stun rule ---
    {
        Fighter a = make_idle_fighter(glm::vec3(0, 0, 0));
        Fighter b = make_idle_fighter(glm::vec3(0, 0, 100));
        a.set_hypermode(Hypermode::Oyashiro);   // the attacker is Oyashiro too
        b.set_hypermode(Hypermode::Oyashiro);
        b.take_damage(5, &a);
        check_near("Oyashiro gauge after taking 5", 5.0 / 50.0, b.hyper_gauge(), 1e-7);
        check_bits("Oyashiro gains nothing from damage dealt", 0.0f, a.hyper_gauge());
        for (int i = 0; i < 9; ++i) b.take_damage(5, &a);
        check_bits("Oyashiro gauge clamps to 1 after 10 hits", 1.0f, b.hyper_gauge());
        check_bool("Oyashiro ready", true, b.hyper_ready());
        check_int("Oyashiro HP after 10 unmodified hits", 50, b.hp());

        // Each of those hits stunned B; the state machine only runs while
        // can_act(), so wait the stun out before pressing S.
        while (b.state() == FighterState::Hit) b.update(nullptr, nullptr, kDt);
        check_int("stun cleared before activation", static_cast<int>(FighterState::Idle),
                  static_cast<int>(b.state()));

        // Activation burst: the opponent is knocked back at kRunSpeed, no
        // damage, and the Hit state carries the push.
        const int a_hp_before = a.hp();
        Input in;
        in.set(fnd::input::Action::Special, true);
        tick(b, in, &a);   // the burst needs the opponent
        check_bool("Oyashiro activated", true, b.hyper_active());
        check_int("Oyashiro burst deals no damage", a_hp_before, a.hp());
        check_int("Oyashiro burst stuns the opponent", static_cast<int>(FighterState::Hit),
                  static_cast<int>(a.state()));
        const float az = a.position().z;
        a.update(nullptr, nullptr, kDt);
        // Pushed away from the activator: A sits on B's +Z side, so the burst
        // sends it toward -Z at kRunSpeed with the Hit state's 0.8 friction.
        check_near("knockback carries away at 0.8 friction", -900.0 * 0.8 * kDt,
                   a.position().z - az, 1e-4);
        in.set(fnd::input::Action::Special, false);

        // Alternate-hit stun: hits 1 and 3 stun, 2 and 4 do not. B is the
        // victim here (take_damage on B with A as the source).
        const int hp_start = b.hp();
        for (int hit = 1; hit <= 4; ++hit) {
            b.set_state(FighterState::Idle);
            b.take_damage(5, &a);
            const bool stunned = (b.state() == FighterState::Hit);
            check_bool(hit % 2 == 1 ? "Oyashiro hit 1/3 stuns"
                                    : "Oyashiro hit 2/4 skips the stun",
                       hit % 2 == 1, stunned);
        }
        check_int("Oyashiro damage taken x0.75 (lround(3.75) = 4) x4 hits",
                  hp_start - 16, b.hp());
    }

    // --- Oyashiro: damage dealt x1.5 ---
    {
        Fighter a = make_idle_fighter(glm::vec3(0, 0, 0));
        a.set_hypermode(Hypermode::Oyashiro);
        a.set_hyper_gauge(1.0f);
        Input in;
        in.set(fnd::input::Action::Special, true);
        tick(a, in);
        in.set(fnd::input::Action::Special, false);
        Fighter b = make_idle_fighter(glm::vec3(0, 0, 400));   // out of burst range
        b.take_damage(5, &a);
        check_int("Oyashiro deals lround(5*1.5) = 8", 100 - 8, b.hp());
    }

    // --- Kakera: manual activation is impossible ---
    {
        Fighter f = make_idle_fighter(glm::vec3(0, 0, 0));
        f.set_hypermode(Hypermode::Kakera);
        f.set_hyper_gauge(1.0f);
        Input in;
        in.set(fnd::input::Action::Special, true);
        tick(f, in);
        check_bool("Kakera cannot activate manually", false, f.hyper_active());
        check_bits("Kakera gauge kept", 1.0f, f.hyper_gauge());
    }

    // --- Kakera: death save + stun immunity + damage reduction + HP drain ---
    {
        Fighter f = make_idle_fighter(glm::vec3(0, 0, 0));
        f.set_hypermode(Hypermode::Kakera);
        f.set_hyper_gauge(1.0f);
        f.set_hp(3);
        f.take_damage(5, nullptr);
        check_int("Kakera death save restores HP", 100, f.hp());
        check_bool("Kakera save activates the mode", true, f.hyper_active());
        check_bits("Kakera save spends the gauge", 0.0f, f.hyper_gauge());
        check_bits("Kakera save sets the 25 s timer", 25.0f, f.hyper_seconds_left());
        check_bool("Kakera save does not KO", true, f.is_alive());

        // Damage taken while active is x0.20 (lround(5*0.2) = 1).
        f.take_damage(5, nullptr);
        check_int("Kakera takes lround(5*0.2) = 1", 99, f.hp());
        // Stun immunity: the hit never enters Hit.
        f.set_state(FighterState::Idle);
        f.take_damage(5, nullptr);
        check_bool("Kakera never stunned while active",
                   f.state() != FighterState::Hit, true);
        // Damage dealt while active is x1.5.
        Fighter v = make_idle_fighter(glm::vec3(0, 0, 400));
        v.take_damage(5, &f);
        check_int("Kakera deals lround(5*1.5) = 8", 100 - 8, v.hp());

        // HP drain is int(3.96*dt + 0.5) = int(0.566) = 0 per frame at 60 Hz,
        // so the mode never drains and never self-terminates through HP; the
        // 25 s timer is the only exit.
        const int hp_before = f.hp();
        for (int i = 0; i < 600; ++i) f.update(nullptr, nullptr, kDt);
        check_int("Kakera HP drain is a no-op at 60 Hz", hp_before, f.hp());
        check_bool("Kakera still active after 10 s", true, f.hyper_active());
        int frames = 0;
        while (f.hyper_active() && frames < 3000) { f.update(nullptr, nullptr, kDt); ++frames; }
        check_int("Kakera frames left after the 600-frame run (1501 - 600)", 901, frames);
        check_int("Kakera ends alive, undrained", hp_before, f.hp());
    }

    // --- Kakera: no save without a full gauge ---
    {
        Fighter f = make_idle_fighter(glm::vec3(0, 0, 0));
        f.set_hypermode(Hypermode::Kakera);
        f.set_hyper_gauge(0.5f);
        f.set_hp(3);
        f.take_damage(5, nullptr);
        check_int("no save at half gauge -> HP 0", 0, f.hp());
        check_int("no save at half gauge -> KO", static_cast<int>(FighterState::KO),
                  static_cast<int>(f.state()));
    }

    // --- render data: aura colour/radius from the deterministic pulse ---
    {
        Fighter f;
        f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
        f.set_hypermode(Hypermode::Oyashiro);
        // m_time == 0 -> pulse 0.5 -> alpha 90, radius 58.
        check_u32("aura colour at t=0 (alpha 90)", 0x5AFF6EDCu, f.aura_color());
        check_bits("aura radius at t=0", 58.0f, f.aura_radius());
        check_bits("aura centre is model-space (0,58,0)", 58.0f, f.aura_center_local().y);
        check_bool("aura hidden when not active", false, f.aura_active());
        // Leave the BattleStart pose without advancing the clock, so the
        // pulse after one tick is a known function of m_time == dt.
        f.set_state(FighterState::Idle);
        f.set_hyper_gauge(1.0f);
        Input in;
        in.set(fnd::input::Action::Special, true);
        tick(f, in);
        check_bool("aura visible while active", true, f.aura_active());
        const float pulse = 0.5f + 0.5f * std::sin(kStep * 8.0f);
        const int alpha = static_cast<int>(70.0f + 40.0f * pulse);
        check_u32("aura alpha follows the pulse (t = dt)",
                  gameplay::packArgb(static_cast<std::uint8_t>(alpha), 255, 110, 220),
                  f.aura_color());
        check_bits("aura radius follows the pulse (t = dt)", 56.0f + 4.0f * pulse,
                   f.aura_radius());
    }
}

// ===========================================================================
//  Case 10 — KO / HP floor / respawn-relevant reset
// ===========================================================================
void test_ko() {
    section("10. KO + HP floor + reset (respawn path)");
    Fighter f = make_idle_fighter(glm::vec3(0, 0, 0));
    f.set_hp(0);
    check_int("set_hp floors at 1", 1, f.hp());
    f.set_hp(-9);
    check_int("set_hp floors negative at 1", 1, f.hp());
    f.set_hp(1000);
    check_int("set_hp caps at kMaxHP", 100, f.hp());
    // FUN_00637950's entry test is radius != 0 and combat[0] is read only inside the HP
    // math (0x6379e0 / 0x638a32), so a contact with no HP power takes no HP. The port
    // used to clamp every hit to 1, which turned those records into 1-HP hits.
    f.take_damage(0, nullptr);
    check_int("a zero-power hit takes no HP", 100, f.hp());
    check_int("and it records no damage taken", 0, f.stats().damageTaken);
    // The record's own columns still apply: a radius != 0 record with power 0 is a real
    // contact, so it still stuns. The HP number is not the gate.
    check_int("a zero-power contact still stuns its victim",
              static_cast<int>(FighterState::Hit), static_cast<int>(f.state()));

    // The guard branch keeps its floor for POSITIVE amounts: blocking 1..4 still lands 1,
    // which is the pre-existing behaviour the zero-power fix must not disturb. Only a
    // zero-power contact stays at 0 behind a guard.
    {
        Fighter guarded = make_idle_fighter(glm::vec3(0, 0, 0));
        // A landed hit leaves Guard for Hit, so each case re-enters the guard.
        guarded.set_state(FighterState::Guard);
        guarded.set_hp(100);
        guarded.take_damage(3, nullptr);
        check_int("guarding 3 damage still takes its historical 1", 99, guarded.hp());
        guarded.set_hp(100);
        guarded.set_state(FighterState::Guard);
        guarded.take_damage(20, nullptr);
        check_int("guarding 20 damage still takes a fifth", 96, guarded.hp());
        guarded.set_hp(100);
        guarded.set_state(FighterState::Guard);
        guarded.take_damage(0, nullptr);
        check_int("but a zero-power contact takes nothing even guarded", 100, guarded.hp());
    }

    f.set_hp(1);
    f.take_damage(1, nullptr);
    check_int("lethal damage floors HP at 0", 0, f.hp());
    check_int("lethal damage enters KO", static_cast<int>(FighterState::KO),
              static_cast<int>(f.state()));
    check_bool("KO clears is_alive", false, f.is_alive());
    for (int i = 0; i < 120; ++i) f.update(nullptr, nullptr, kDt);
    check_int("KO is permanent (no self-revival)", static_cast<int>(FighterState::KO),
              static_cast<int>(f.state()));
    f.take_damage(5, nullptr);
    check_int("KO'd fighter cannot go below 0", 0, f.hp());
    check_int("KO'd fighter stays KO", static_cast<int>(FighterState::KO),
              static_cast<int>(f.state()));
    f.set_hyper_gauge(0.0f);
    Fighter src = make_idle_fighter(glm::vec3(0, 0, 100));
    f.take_damage(5, &src);
    check_bits("dead fighter earns no gauge", 0.0f, f.hyper_gauge());

    // reset() is the round/respawn path.
    f.reset(glm::vec3(50, 0, -50), 1.0f);
    check_int("reset restores HP", 100, f.hp());
    check_int("reset state is BattleStart", static_cast<int>(FighterState::BattleStart),
              static_cast<int>(f.state()));
    check_bool("reset clears airborne", false, f.airborne());
    check_int("reset restores MAIN", 6, f.main_whole());
    check_int("reset restores CHARGE", 2, f.charge_whole());
    check_bits("reset clears the hyper gauge", 0.0f, f.hyper_gauge());
    check_bool("reset clears hypermode active", false, f.hyper_active());
    check_bits("reset places the fighter", -50.0f, f.position().z);
    check_bits("reset sets facing", 1.0f, f.facing_yaw());
    for (int i = 0; i < 59; ++i) f.update(nullptr, nullptr, kDt);
    check_int("BattleStart still counting at frame 59",
              static_cast<int>(FighterState::BattleStart), static_cast<int>(f.state()));
    f.update(nullptr, nullptr, kDt);
    check_int("BattleStart expires at frame 60", static_cast<int>(FighterState::Idle),
              static_cast<int>(f.state()));
}

// ===========================================================================
//  Case 11 — facing/turn toward the opponent (kTurnSpeed 8 rad/s lerp)
// ===========================================================================
void test_facing() {
    section("11. facing (absolute idle yaw and input-relative shortest turn)");
    Fighter a = make_idle_fighter(glm::vec3(0, 0, 0));
    Fighter b = make_idle_fighter(glm::vec3(100, 0, 0));
    a.update(nullptr, &b, kDt);
    if (g_testCombo.ready) {
        check_near("recovered handler preserves idle yaw", 0.0, a.facing_yaw(), 1e-5);
        for (int i = 0; i < 29; ++i) a.update(nullptr, &b, kDt);
        check_near("recovered handler keeps its absolute idle yaw", 0.0,
                   a.facing_yaw(), 0.03);
        Input walk; walk.set(fnd::input::Action::Up, true);
        tick(a, walk, &b);
        check_near("recovered walk turns nineteen degrees",
                   glm::radians(19.f), a.facing_yaw(), 1e-5);
    } else {
        // Without a roster handler, CI uses the legacy opponent-facing fallback.
        const double target = std::atan2(100.0, 0.0);
        check_near("fallback turns toward opponent", target * 8.0 * kDt,
                   a.facing_yaw(), 1e-5);
        for (int i = 0; i < 29; ++i) a.update(nullptr, &b, kDt);
        const double residual = std::pow(1.0 - 8.0 * kDt, 30.0);
        check_near("fallback facing approaches opponent", target * (1.0 - residual),
                   a.facing_yaw(), 0.03);
    }

    // yaw=0 faces +Z: an opponent straight ahead keeps yaw at 0.
    Fighter c = make_idle_fighter(glm::vec3(0, 0, 0));
    Fighter d = make_idle_fighter(glm::vec3(0, 0, 100));
    c.update(nullptr, &d, kDt);
    check_bits("opponent on +Z keeps yaw 0", 0.0f, c.facing_yaw());

    // Dead opponents are ignored.
    Fighter e = make_idle_fighter(glm::vec3(0, 0, 0));
    Fighter dead = make_idle_fighter(glm::vec3(100, 0, 0));
    dead.set_hp(1);
    dead.take_damage(5, nullptr);
    e.update(nullptr, &dead, kDt);
    check_bits("dead opponent does not steer facing", 0.0f, e.facing_yaw());

    // Render data: world matrix = translate * rotateY(facing + 180°) (FUN_00420b30;
    // see modelMatrix() — the shipped rigs are authored facing -Z).
    Fighter m;
    m.init(nullptr, nullptr, glm::vec3(10, 20, 30), 0.0f);
    const glm::mat4 ident = m.modelMatrix();
    check_bits("modelMatrix translation x", 10.0f, ident[3][0]);
    check_bits("modelMatrix translation y", 20.0f, ident[3][1]);
    check_bits("modelMatrix translation z", 30.0f, ident[3][2]);
    Fighter m2;
    m2.init(nullptr, nullptr, glm::vec3(0, 0, 0), 1.5707964f);
    const glm::mat4 rot = m2.modelMatrix();
    // D3DXMatrixRotationY(+90° + 180°) in the row-vector convention maps +Z to -X;
    // glm::rotate(theta, +Y) is the same matrix in the column-vector convention.
    // +Z is the rig's BACK, so -Z (its front, measured on the shipped SkinWeights)
    // is what must land on the movement forward: yaw 90° faces +X.
    const glm::vec3 p = glm::vec3(rot * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
    check_near("modelMatrix rotateY(90+180): +Z maps to -X", -1.0, p.x, 1e-6);
    check_near("modelMatrix rotateY(90+180): +Z maps to 0 on Y", 0.0, p.y, 1e-6);
    check_near("modelMatrix rotateY(90+180): +Z maps to 0 on Z", 0.0, p.z, 1e-6);
    const glm::vec3 front = glm::vec3(rot * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
    check_near("modelMatrix rotateY(90+180): rig front -Z maps to the +X facing", 1.0,
               front.x, 1e-6);
    const glm::vec3 q = glm::vec3(rot * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
    check_near("modelMatrix rotateY(90+180): +X maps to +Z", 1.0, q.z, 1e-6);
}

// ===========================================================================
//  Case 12 — animation binding through a character move table
// ===========================================================================
// This small parsed table uses distinct set tags to prove that runtime binding
// follows move ID → phase tag. It intentionally makes no claim about attack
// selectors; those need a character+weapon combo and are covered in melee_rules_test.
void append_u32(std::vector<std::uint8_t>& bytes, std::uint32_t value) {
    for (int i = 0; i < 4; ++i)
        bytes.push_back(static_cast<std::uint8_t>((value >> (8 * i)) & 0xff));
}

bool make_animation_test_moves(gameplay::CharacterMoves& moves) {
    std::vector<std::uint8_t> bytes;
    append_u32(bytes, 1);                  // file tag
    bytes.resize(bytes.size() + 0x104, 0); // model path block
    for (int i = 0; i < 6; ++i) append_u32(bytes, i == 3 ? 1 : 0);
    struct Entry { int move; int set; };
    const Entry entries[] = {
        {0, 0}, {10, 1}, {194, 43}, {103, 95}, {196, 28}, {203, 97},
    };
    append_u32(bytes, static_cast<std::uint32_t>(sizeof(entries) / sizeof(entries[0])));
    for (const Entry& e : entries) {
        append_u32(bytes, static_cast<std::uint32_t>(e.move)); // move id
        append_u32(bytes, 0);                                // flags
        append_u32(bytes, 0);                                // cancel window
        append_u32(bytes, 1);                                // one phase
        append_u32(bytes, static_cast<std::uint32_t>(e.set)); // section tag
        append_u32(bytes, 0);                                // no effect records
    }
    append_u32(bytes, 124);
    for (int set = 0; set < 124; ++set) {
        append_u32(bytes, 0);            // animation-set +0x1c metadata
        append_u32(bytes, set == 14 ? 1 : 0); // +0x20 gate blocks set 14
        append_u32(bytes, 0);            // no animation-event payloads
    }
    std::string error;
    return moves.parse(bytes.data(), bytes.size(), error);
}

void test_anim_binding() {
    section("12. animation binding (state -> move -> character table tag)");

    std::vector<std::string> names;
    for (int i = 0; i < 124; ++i) names.push_back("Anim-" + std::to_string(124 - i));
    const xm::Model model = make_anim_model(names);
    xm::Controller ctrl;
    ctrl.bind(&model);
    auto moves = std::make_unique<gameplay::CharacterMoves>();
    check_bool("synthetic move table parses", true, make_animation_test_moves(*moves));
    check_int("the set trailer stays aligned after move records", 124,
              moves->animation_set_count());
    check_int("set 14 retains its nonzero auto-advance gate", 1,
              moves->animation_set_phase_gate(14));
    check_int("set transition metadata is parsed", 0,
              moves->animation_set_transition_duration(14));
    check_int("missing set metadata is explicit", -1,
              moves->animation_set_phase_gate(124));
    check_int("missing transition metadata is explicit", -1,
              moves->animation_set_transition_duration(124));

    Fighter f;
    f.set_moves(moves.get());
    f.init(&model, &ctrl, glm::vec3(0, 0, 0), 0.0f);
    check_int("round reset resolves move 194 from NN.dat", 43, ctrl.trackAnimationSet(0));
    check_bool("round reset uses a data row", false, f.anim_fallback());
    check_str("set 43 keeps its model name", "Anim-81", f.anim_set_name());
    check_bool("model() is exposed", true, f.model() == &model);

    struct Row { FighterState state; int set; const char* name; };
    const Row rows[] = {
        {FighterState::Idle,       0,  "Anim-124"},
        {FighterState::Walk,       1,  "Anim-123"},
        {FighterState::Hit,        95, "Anim-29"},
        {FighterState::Knockdown,  28, "Anim-96"},
        {FighterState::KO,         97, "Anim-27"},
    };
    for (const Row& r : rows) {
        Fighter fr;
        fr.set_moves(moves.get());
        fr.init(&model, &ctrl, glm::vec3(0, 0, 0), 0.0f);
        fr.set_state(r.state);
        check_int("selected phase tag starts on track 1", r.set, ctrl.trackAnimationSet(1));
        check_int("animation query agrees with table", r.set, fr.anim_set_index());
        check_str("set name comes from the model", r.name, fr.anim_set_name());
        check_bool("resolved table row has no fallback", false, fr.anim_fallback());
    }

    // The default class callback rejects these changes, so the source resets
    // both tracks immediately. Hit is a recovered move row.
    f.init(&model, &ctrl, glm::vec3(0, 0, 0), 0.0f);
    f.set_state(FighterState::Idle);
    f.set_state(FighterState::Walk);
    check_int("rejected blend binds walk on track 0", 1, ctrl.trackAnimationSet(0));
    check_int("rejected blend binds walk on track 1", 1, ctrl.trackAnimationSet(1));
    f.set_state(FighterState::Hit);
    check_int("rejected blend binds hit on track 0", 95, ctrl.trackAnimationSet(0));
    check_int("rejected blend binds hit on track 1", 95, ctrl.trackAnimationSet(1));

    // Guard has no selector at all: the source's block path binds no move, so the
    // clip that was already playing stays bound and is not reported as a miss.
    f.set_state(FighterState::Hit);
    f.set_state(FighterState::Guard);
    check_int("guard holds the playing clip", 95, ctrl.trackAnimationSet(0));
    check_int("guard holds it on both tracks", 95, ctrl.trackAnimationSet(1));
    check_bool("guard is not a fallback", false, f.anim_fallback());
    check_bool("guard reports the no-selector hold", true, f.anim_no_selector());
    // Jump and TagOut do have selectors and this table ships no row for either, so
    // they are misses: set 0, and the fallback stays visible.
    for (FighterState state : {FighterState::Jump, FighterState::TagOut}) {
        f.set_state(state);
        check_int("unresolved selector uses set 0", 0, ctrl.trackAnimationSet(1));
        check_int("unresolved selector resets track 0", 0, ctrl.trackAnimationSet(0));
        check_bool("unresolved selector reports fallback", true, f.anim_fallback());
        check_bool("unresolved selector is not a hold", false, f.anim_no_selector());
    }

    const xm::Model shortModel = make_anim_model({"a", "b"});
    xm::Controller shortCtrl;
    shortCtrl.bind(&shortModel);
    Fighter g;
    g.set_moves(moves.get());
    g.init(&shortModel, &shortCtrl, glm::vec3(0, 0, 0), 0.0f);
    check_int("out-of-range data tag uses set 0", 0, shortCtrl.trackAnimationSet(0));
    check_bool("out-of-range tag reports fallback", true, g.anim_fallback());
    g.set_state(FighterState::Idle);
    check_int("in-range data tag binds", 0, shortCtrl.trackAnimationSet(0));
    check_bool("valid row clears fallback", false, g.anim_fallback());

    const xm::Model empty;
    xm::Controller emptyCtrl;
    emptyCtrl.bind(&empty);
    Fighter h;
    h.init(&empty, &emptyCtrl, glm::vec3(0, 0, 0), 0.0f);
    check_int("no sets -> no track bound", -1, emptyCtrl.trackAnimationSet(0));
    check_str("no sets -> no name", "", h.anim_set_name());
    Fighter none;
    none.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    check_bool("null model is accepted", true, none.model() == nullptr);

    Fighter k;
    k.set_moves(moves.get());
    k.init(&model, &ctrl, glm::vec3(0, 0, 0), 0.0f);
    k.update(nullptr, nullptr, kDt);
    check_near("pose().animTime follows elapsed times the original tick",gameplay::kOriginalAnimationTick,k.pose().animTime,1e-6);
    check_bits("pose().position.x", 0.0f, k.pose().position.x);
    check_bool("pose().alive", true, k.pose().alive);
    check_near("pose().facingYaw", 0.0, k.pose().facingYaw, 0.0);
    k.set_hp(1);
    k.take_damage(5, nullptr);
    check_bool("pose().alive clears on KO", false, k.pose().alive);
    render::ArenaTarget target;
    h.sync_target(target);
    check_bits("sync_target position", 0.0f, target.position.x);
    check_near("sync_target facingYaw", 0.0, target.facingYaw, 0.0);

    static_assert(sizeof(Rgb) == sizeof(render::DebugColor),
                  "gameplay::Rgb and render::DebugColor must be the same width");
    check_u32("Rgb layout matches render::packColor",
              render::packColor(130, 220, 255), gameplay::packRgb(130, 220, 255));
    check_u32("Rgb alpha matches render::packColor",
              render::packColor(10, 20, 30, 90), gameplay::packArgb(90, 10, 20, 30));
}

// ===========================================================================
//  Case 13 — ProjectilePool: caps, tiers, owner, wall, expiry
// ===========================================================================
xm::Model make_wall_model() {
    // A 200x200 quad in the z = 100 plane, as one frame-less mesh — the layout
    // collision_tama.X parses to (raycast.h:118-124).
    xm::Model m;
    xm::Mesh mesh;
    mesh.name = "tama_wall";
    mesh.frame = -1;
    const glm::vec3 c[4] = {{-100, -100, 100}, {100, -100, 100},
                            {100, 100, 100},   {-100, 100, 100}};
    for (int i = 0; i < 4; ++i) {
        xm::Vertex v{};
        v.pos = c[i];
        v.normal = glm::vec3(0, 0, -1);
        mesh.vertices.push_back(v);
    }
    mesh.indices = {0, 1, 2, 0, 2, 3};
    mesh.submeshes.push_back(xm::Submesh{0, 6, 0});
    m.meshes.push_back(mesh);
    return m;
}

void test_projectile_pool() {
    section("13. ProjectilePool (caps, tiers, owner, wall, expiry)");
    check_int("kMaxShots", 32, static_cast<long long>(ProjectilePool::kMaxShots));
    check_int("kMaxSparks", 32, static_cast<long long>(ProjectilePool::kMaxSparks));

    // --- tier table ---
    {
        struct Expect { ShotTier tier; float speed; int damage; float life;
                        float radius; int reload; std::uint32_t color; };
        const Expect table[4] = {
            {ShotTier::Tap,    650.0f,  4, 2.5f, 55.0f, 15, 0xFF96C8FFu},
            {ShotTier::Yellow, 550.0f,  9, 2.5f, 65.0f, 30, 0xFFFFE650u},
            {ShotTier::Red,    460.0f, 16, 3.0f, 80.0f, 45, 0xFFFF5A3Cu},
            {ShotTier::Ex,     520.0f, 22, 3.0f, 90.0f, 60, 0xFFFF5AFFu},
        };
        for (const Expect& e : table) {
            const gameplay::ShotParams p = gameplay::shot_params(e.tier);
            check_bits("tier speed", e.speed, p.speed);
            check_int("tier damage", e.damage, p.damage);
            check_bits("tier life", e.life, p.lifeSec);
            check_bits("tier hitRadius", e.radius, p.hitRadius);
            check_int("tier reloadFrames", e.reload, p.reloadFrames);
            check_u32("tier colour", e.color, p.color);
        }
        check_bits("tap mainCost", 1.0f, gameplay::shot_params(ShotTier::Tap).mainCost);
        check_bits("yellow chargeCost", 1.0f,
                   gameplay::shot_params(ShotTier::Yellow).chargeCost);
        check_bits("red chargeCost", 2.0f,
                   gameplay::shot_params(ShotTier::Red).chargeCost);
        check_bits("ex chargeCost", 1.0f,
                   gameplay::shot_params(ShotTier::Ex).chargeCost);
    }

    // --- spawn caps ---
    {
        ProjectilePool pool;
        int spawned = 0;
        for (int i = 0; i < 40; ++i) {
            if (pool.spawn(glm::vec3(static_cast<float>(i) * 10.0f, 0, 0),
                           glm::vec3(0, 0, 1), ShotTier::Tap, nullptr)) {
                ++spawned;
            }
        }
        check_int("shot pool caps at 32", 32, spawned);
        check_int("live_shots at the cap", 32, pool.live_shots());
        int sparks = 0;
        for (int i = 0; i < 40; ++i) {
            pool.spawn_spark(glm::vec3(0, 0, 0));
            sparks = count_live_sparks(pool);
        }
        check_int("spark pool caps at 32", 32, sparks);
        pool.clear();
        check_int("clear frees all shots", 0, pool.live_shots());
        check_int("clear frees all sparks", 0, count_live_sparks(pool));
    }

    // --- tier speed/damage/life through the pool; these are port profiles, not RE tier links ---
    if (g_testCombo.ready) {
        ProjectilePool pool;
        Fighter shooter = make_idle_fighter(glm::vec3(0, 0, 0));
        Fighter victim = make_idle_fighter(glm::vec3(0, 0, 10));
        check_bool("spawn returns true", true,
                   pool.spawn(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), ShotTier::Tap,
                              &shooter));
        const auto& s = pool.shots()[0];
        check_bits("spawned vel = dir * tier speed", 650.0f, s.vel.z);
        check_bits("spawned life = tier lifeSec", 2.5f, s.life);
        check_int("spawned tier", static_cast<int>(ShotTier::Tap),
                  static_cast<int>(s.tier));
        check_bits("shot cube size (DX9 render constant)", 16.0f,
                   gameplay::Projectile::kCubeSize);
        check_u32("shot cube colour = tier colour", 0xFF96C8FFu, s.color());
        check_bits("shot spawns at age 0", 0.0f, s.age);
        pool.update(kDt, &victim, 1, nullptr, nullptr);
        check_int("tap shot deals 4 damage", 96, victim.hp());
        check_int("shot freed on the hit", 0, pool.live_shots());
        check_int("hit spawns one spark", 1, count_live_sparks(pool));
        const auto& spark = pool.sparks()[0];
        check_bits("fighter-hit spark life is 0.35", 0.35f, spark.life);
        check_bits("spark aged one frame in the same update", kStep, spark.age);
        check_bits("fresh spark pos = shot pos", s.pos.z, spark.pos.z);
        // The spark's render arguments follow the DX9 fade formulas exactly.
        const float t = spark.age / spark.life;
        check_near("spark size follows 14 + 46*t", 14.0 + 46.0 * t, spark.size(), 1e-5);
        const int alpha = static_cast<int>(255.0f * (1.0f - t));
        const int green = static_cast<int>(240.0f - 120.0f * t);
        check_u32("spark colour follows the DX9 fade",
                  gameplay::packArgb(static_cast<std::uint8_t>(alpha), 255,
                                     static_cast<std::uint8_t>(green), 120),
                  spark.color());
    } else {
        skip_case("bound shooter and victim projectile hit");
    }

    // --- a fresh (age 0) spark: the DX9 render arguments, bit-exact ---
    {
        ProjectilePool pool;
        pool.spawn_spark(glm::vec3(0, 0, 0), 0.3f);
        const auto& spark = pool.sparks()[0];
        check_bits("age-0 spark size", 14.0f, spark.size());
        check_u32("age-0 spark colour (alpha 255, g 240, b 120)", 0xFFFFF078u,
                  spark.color());
        check_bits("age-0 spark life frac", 0.0f, spark.life_frac());
    }

    // --- a combo-bound owner never self-hits while the same shot hits its opponent ---
    if (g_testCombo.ready) {
        ProjectilePool pool;
        Fighter pair[2];
        bind_test_combo(pair[0]);
        bind_test_combo(pair[1]);
        pair[0].init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
        pair[1].init(nullptr, nullptr, glm::vec3(0, 0, 10), 0.0f);
        settle(pair[0]);
        settle(pair[1]);
        pool.spawn(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), ShotTier::Tap, &pair[0]);
        pool.update(kDt, pair, 2, nullptr, nullptr);
        check_int("owner takes no damage from its own shot", 100, pair[0].hp());
        check_int("bound opponent takes the shot's port-profile damage", 96, pair[1].hp());
        check_int("shot is freed on the opponent hit", 0, pool.live_shots());
    } else {
        skip_case("bound owner/opponent projectile hit");
    }

    // --- wall hit on a synthetic tama mesh ---
    if (g_testCombo.ready) {
        const xm::Model wall = make_wall_model();
        const game::physics::ModelIndex index = game::physics::buildModelIndex(wall);
        check_int("wall index has one mesh", 1,
                  static_cast<long long>(index.meshOrder.size()));

        ProjectilePool pool;
        Fighter shooter = make_idle_fighter(glm::vec3(0, 0, 0));
        // Behind the wall and far enough that the shot cannot reach it: the
        // Tap hit radius is 55 and the wall sits at z = 100.
        Fighter behind = make_idle_fighter(glm::vec3(0, 0, 300));
        pool.spawn(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), ShotTier::Tap, &shooter);
        int frames = 0;
        while (pool.live_shots() > 0 && frames < 200) {
            pool.update(kDt, &behind, 1, &wall, &index);
            ++frames;
        }
        check_int("shot hits the wall on frame 10 (650 u/s, 100 units)", 10, frames);
        check_int("wall frees the shot", 0, pool.live_shots());
        check_int("wall hit spawns one spark", 1, count_live_sparks(pool));
        check_near("spark sits on the wall plane", 100.0,
                   pool.sparks()[0].pos.z, 1e-3);
        check_bits("wall spark life is 0.3", 0.3f, pool.sparks()[0].life);
        check_int("wall hit deals no fighter damage (wall checked first)", 100,
                  behind.hp());

        // A shot that misses the wall (above it) keeps flying and expires
        // silently: the wall is a mesh query, not a plane.
        ProjectilePool miss;
        miss.spawn(glm::vec3(0, 300, 0), glm::vec3(0, 0, 1), ShotTier::Tap, &shooter);
        for (int i = 0; i < 20; ++i) miss.update(kDt, nullptr, 0, &wall, &index);
        check_int("shot above the wall survives past it", 1, miss.live_shots());
        check_int("no spark for the miss", 0, count_live_sparks(miss));

        // A null model/index pair means "no wall geometry" (the open-field
        // fallback) and must not dereference anything.
        ProjectilePool open;
        open.spawn(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), ShotTier::Tap, &shooter);
        for (int i = 0; i < 20; ++i) open.update(kDt, nullptr, 0, nullptr, nullptr);
        check_int("null tama model leaves the shot flying", 1, open.live_shots());
    } else {
        skip_case("bound shooter projectile wall collision");
    }

    // --- expiry frees silently; sparks age out ---
    {
        ProjectilePool pool;
        pool.spawn(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), ShotTier::Tap, nullptr);
        for (int i = 0; i < 150; ++i) pool.update(kDt, nullptr, 0, nullptr, nullptr);
        check_int("tap shot alive at frame 150", 1, pool.live_shots());
        pool.update(kDt, nullptr, 0, nullptr, nullptr);
        check_int("tap shot expires at frame 151", 0, pool.live_shots());
        check_int("expiry is silent (no spark)", 0, count_live_sparks(pool));

        ProjectilePool sparks;
        sparks.spawn_spark(glm::vec3(0, 0, 0), 0.3f);
        for (int i = 0; i < 17; ++i) sparks.update(kDt, nullptr, 0, nullptr, nullptr);
        check_int("spark alive at frame 17", 1, count_live_sparks(sparks));
        sparks.update(kDt, nullptr, 0, nullptr, nullptr);
        check_int("spark expires at frame 18", 0, count_live_sparks(sparks));

        // A zero/negative spark life falls back to 0.3.
        ProjectilePool deflt;
        deflt.spawn_spark(glm::vec3(0, 0, 0), 0.0f);
        check_bits("spawn_spark(0) falls back to 0.3 s", 0.3f,
                   deflt.sparks()[0].life);
    }

    // --- red port tier profile: hit radius and damage against bound fighters ---
    if (g_testCombo.ready) {
        ProjectilePool pool;
        Fighter shooter = make_idle_fighter(glm::vec3(0, 0, 0));
        Fighter victim = make_idle_fighter(glm::vec3(0, 0, 70));
        pool.spawn(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), ShotTier::Red, &shooter);
        pool.update(kDt, &victim, 1, nullptr, nullptr);
        check_int("red shot hits at 70 units (shot at 7.7, radius 80)", 100 - 16,
                  victim.hp());
        ProjectilePool far;
        Fighter out = make_idle_fighter(glm::vec3(0, 0, 90));
        far.spawn(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), ShotTier::Red, nullptr);
        far.update(kDt, &out, 1, nullptr, nullptr);
        check_int("red shot misses at 90 units (shot at 7.7, radius 80)", 100,
                  out.hp());
    } else {
        skip_case("bound fighters against red port tier profile");
    }

    // --- a KO'd fighter takes the hit: that is Overkill (issue #11) ---
    // The shot is fired by a real fighter rather than a null owner (a character+weapon
    // case, AGENTS rule 7): the tier parameters come from that owner, and with no
    // weapon bound here they are the shared tuning and the unspecified hit category.
    if (g_testCombo.ready) {
        ProjectilePool pool;
        Fighter shooter = make_idle_fighter(glm::vec3(0, 0, 0));
        Fighter dead = make_idle_fighter(glm::vec3(0, 0, 0));
        dead.set_hp(1);
        dead.take_damage(5, &shooter);
        check_bits("the KO leaves the fighter down (hp 0)", 0, dead.hp());
        check_bits("no Overkill credit before a hit lands", 0, dead.take_overkill_hits());
        pool.spawn(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), ShotTier::Tap, &shooter);
        pool.update(kDt, &dead, 1, nullptr, nullptr);
        check_int("the downed body stays at 0 HP", 0, dead.hp());
        check_int("the shot is consumed by the downed body", 0, pool.live_shots());
        // The credit is exactly one per hit and is drained once (FUN_00637950
        // @0x638e0d-0x638e37); the scene decides the side.
        check_int("one Overkill credit for one hit", 1, dead.take_overkill_hits());
        check_int("the credit drains (counted once)", 0, dead.take_overkill_hits());
        // One blow, one credit: the shot that KILLS arms the KO credit and must not
        // also count as an Overkill hit (FUN_00637950 branches on the victim's HP
        // before the damage, @0x638c20-0x638c35).
        Fighter lethaled = make_idle_fighter(glm::vec3(0, 0, 0));
        lethaled.set_hp(1);
        const Fighter::DamageResult killing =
            lethaled.take_damage(4, &shooter, -1, 0, /*shot=*/true);
        check_bool("the killing blow reports Ko", true,
                   killing == Fighter::DamageResult::Ko);
        check_bool("the killing blow arms the KO credit", true, lethaled.pending_ko());
        check_int("and scores no Overkill hit", 0, lethaled.take_overkill_hits());
        // The overkill term is the UNCLAMPED shortfall: 1 HP - 4 damage = 3 below zero
        // (FUN_00639160 @0x639399-0x6393a5 reads the raw field, which the port clamps
        // for HP but keeps here).
        const Fighter::KoCredit credit = lethaled.take_ko_credit();
        check_int("the KO credit carries the unclamped overkill term", 3,
                  credit.overkillHp);
        check_bool("a shot kill takes the shot branch", true, credit.shot);
        check_bool("the KO credit is drained once", false, lethaled.pending_ko());
        // A hit on a LIVING fighter is not Overkill, and melee never offers a dead
        // target at all (FUN_00639160 credits nothing for an already-dead body).
        Fighter alive = make_idle_fighter(glm::vec3(0, 0, 0));
        alive.take_damage(5, &shooter, -1, 0, /*shot=*/true);
        check_bits("a living fighter scores no Overkill credit", 0, alive.take_overkill_hits());
    } else {
        skip_case("bound shooter and Overkill on a KO fighter");
    }

    // --- a shot with an owner applies that owner's hypermode damage ---
    {
        ProjectilePool pool;
        Fighter shooter = make_idle_fighter(glm::vec3(0, 0, 0));
        shooter.set_hypermode(Hypermode::Oyashiro);
        shooter.set_hyper_gauge(1.0f);
        Input in;
        in.set(fnd::input::Action::Special, true);
        tick(shooter, in);   // activate (no opponent in range)
        in.set(fnd::input::Action::Special, false);
        check_bool("shooter hypermode active", true, shooter.hyper_active());
        Fighter victim = make_idle_fighter(glm::vec3(0, 0, 10));
        pool.spawn(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), ShotTier::Tap, &shooter);
        pool.update(kDt, &victim, 1, nullptr, nullptr);
        check_int("owner's x1.5 hypermode scales shot damage (lround(4*1.5) = 6)",
                  100 - 6, victim.hp());
    }
}

// ===========================================================================
//  Case 14 — determinism: the same 600-frame script twice, byte-identical
// ===========================================================================
void trace_put(std::vector<unsigned char>& out, const void* p, std::size_t n) {
    const unsigned char* b = static_cast<const unsigned char*>(p);
    out.insert(out.end(), b, b + n);
}
void trace_i32(std::vector<unsigned char>& out, int v) { trace_put(out, &v, sizeof v); }
void trace_f32(std::vector<unsigned char>& out, float v) { trace_put(out, &v, sizeof v); }

void record_frame(std::vector<unsigned char>& out, const Fighter& a, const Fighter& b,
                  const ProjectilePool& pool) {
    for (const Fighter* f : {&a, &b}) {
        trace_i32(out, static_cast<int>(f->state()));
        trace_i32(out, f->hp());
        trace_f32(out, f->position().x);
        trace_f32(out, f->position().y);
        trace_f32(out, f->position().z);
        trace_f32(out, f->facing_yaw());
        trace_f32(out, f->main_frac());
        trace_f32(out, f->charge_frac());
        trace_f32(out, f->hyper_gauge());
        trace_f32(out, f->hyper_seconds_left());
        trace_f32(out, f->charge_hold_frac());
        const int flags = (f->is_alive() ? 1 : 0) | (f->airborne() ? 2 : 0) |
                          (f->hyper_active() ? 4 : 0) | (f->reload_ok() ? 8 : 0);
        trace_i32(out, flags);
    }
    trace_i32(out, pool.live_shots());
    for (const auto& s : pool.shots()) {
        trace_i32(out, s.alive ? 1 : 0);
        trace_i32(out, static_cast<int>(s.tier));
        trace_f32(out, s.pos.x);
        trace_f32(out, s.pos.y);
        trace_f32(out, s.pos.z);
        trace_f32(out, s.age);
        trace_f32(out, s.life);
    }
    for (const auto& s : pool.sparks()) {
        trace_i32(out, s.alive ? 1 : 0);
        trace_f32(out, s.pos.x);
        trace_f32(out, s.pos.y);
        trace_f32(out, s.pos.z);
        trace_f32(out, s.age);
    }
}

// The deterministic script: a pure function of the frame index, no RNG, no
// clock. Two fighters fight, shoot, guard, jump, dash and use hypermode.
void run_script(std::vector<unsigned char>& trace) {
    // A contiguous pair, because ProjectilePool::update takes Fighter* + count
    // (the source's shape, projectile.cpp:47).
    Fighter pair[2];
    Fighter& a = pair[0];
    Fighter& b = pair[1];
    bind_test_combo(a);
    bind_test_combo(b);
    a.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    b.init(nullptr, nullptr, glm::vec3(0, 0, 300), 3.14159265f);
    a.set_hypermode(Hypermode::Friendship);
    b.set_hypermode(Hypermode::Oyashiro);
    ProjectilePool pool;
    Input ia;
    Input ib;

    for (int frame = 0; frame < 600; ++frame) {
        const int ph = frame % 60;
        ia.clear();
        ib.clear();
        ia.set(fnd::input::Action::Right, ph < 20);
        ia.set(fnd::input::Action::AttackA, ph == 25);
        ia.set(fnd::input::Action::Shoot, ph >= 30 && ph < 45);
        ia.set(fnd::input::Action::Guard, ph >= 50 && ph < 55);
        ia.set(fnd::input::Action::Jump, ph == 20 || ph == 21);
        ia.set(fnd::input::Action::Special, ph == 58);
        ib.set(fnd::input::Action::Left, ph >= 5 && ph < 25);
        ib.set(fnd::input::Action::Up, ph >= 40 && ph < 45);
        ib.set(fnd::input::Action::Shoot, ph >= 45 && ph < 52);
        if (frame == 100) a.set_hyper_gauge(1.0f);
        if (frame == 320) b.set_hyper_gauge(1.0f);

        fnd::input::compute_edges(ia.p);
        fnd::input::compute_edges(ib.p);
        a.update(&ia.p, &b, kDt);
        b.update(&ib.p, &a, kDt);
        if (a.try_melee_hit(b)) { /* damage already applied */ }
        if (b.try_melee_hit(a)) { /* damage already applied */ }

        const gameplay::PendingShot sa = a.take_pending_shot();
        if (sa.armed) pool.spawn(sa.pos, sa.dir, sa.tier, &a);
        const gameplay::PendingShot sb = b.take_pending_shot();
        if (sb.armed) pool.spawn(sb.pos, sb.dir, sb.tier, &b);

        pool.update(kDt, pair, 2, nullptr, nullptr);
        record_frame(trace, a, b, pool);
    }
}

std::uint32_t fnv1a(const std::vector<unsigned char>& bytes) {
    std::uint32_t h = 2166136261u;
    for (unsigned char c : bytes) {
        h ^= c;
        h *= 16777619u;
    }
    return h;
}

void test_rika_repeating_tap() {
    section("17. Rika 1 repeating tap + twin-salvo charge (bodies shoot_body_4_1_*)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_rikaCombo.load(install, 4, 1))
        return skip_case("Rika 1 combo");
    // Bundle evidence: Rika 1 (handler 0x492f70) fires item row 0 on every even tick
    // 12..40 in the ground tap (shoot_body_4_1_400 L21772-21829; the usage matrix
    // agrees per phase), and rows 2+5 at tick 10 plus rows 3+6 at tick 30 in the
    // first ground charge (shoot_body_4_1_450 L23495-548, L23549-577, no-aim branch).
    // Her program is kRikaRules; the second charge stays provisional (no 360/370).
    Fighter f;
    f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_rikaCombo.bind(f);
    settle(f);
    Input in;
    in.set(fnd::input::Action::Shoot, true);
    tick(f, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(f, in);
    check_int("Rika tap enters ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    check_int("Rika tap binds move 400", 400, f.shot_move_id());
    // First burst tick: row 0 armed at tick 12 (same post-release counting as Rena's
    // tick-12 tap: 12 updates after the release update).
    for (int i = 0; i < 12; ++i) tick(f, in);
    gameplay::PendingShot shot = f.take_pending_shot();
    check_bool("Rika tap launches at tick 12", true, shot.armed);
    check_int("Rika tap selects item row zero", 0, shot.bulletRow);
    // Repetition: the next even tick fires again (the schedule, not a single anchor).
    tick(f, in);
    tick(f, in);
    shot = f.take_pending_shot();
    check_bool("Rika tap launches again at tick 14", true, shot.armed);
    check_int("Rika repeat selects item row zero", 0, shot.bulletRow);
    Fighter g;
    g.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_rikaCombo.bind(g);
    settle(g);
    hold_yellow(g, in);
    check_int("Rika hold reaches Yellow", static_cast<int>(ShotTier::Yellow),
              static_cast<int>(g.charge_tier()));
    in.set(fnd::input::Action::Shoot, false);
    tick(g, in);
    check_int("Rika charge enters ShootB", static_cast<int>(FighterState::ShootB),
              static_cast<int>(g.state()));
    check_int("Rika charge binds move 450", 450, g.shot_move_id());
    for (int i = 0; i < 10; ++i) tick(g, in);
    gameplay::PendingShot first = g.take_pending_shot();
    gameplay::PendingShot second = g.take_pending_shot();
    check_bool("Rika charge T10 salvo fires twice", true, first.armed && second.armed);
    check_int("Rika T10 first row is 2", 2, first.bulletRow);
    check_int("Rika T10 second row is 5", 5, second.bulletRow);
    // The charge twins are measured at forward 60 (0x42700000), lateral +-50
    // (0x42480000) and height +70 (0x428c0000) over the actor, aimed on the legacy
    // heading basis with NO yaw offset. The legacy adapter encodes Rena 0's red-charge
    // shape instead (forward 70, height 70, +-1 deg), which is why these need typed
    // specs — and why these numbers are the witness that they got them.
    check_near("T10 twin sits 60 ahead of the actor, not the adapter's 70", 60.f,
               first.pos.z, 1e-3f);
    check_near("T10 first twin sits 50 right of the heading", 50.f, first.pos.x, 1e-3f);
    check_near("T10 second twin sits 50 left of the heading", -50.f, second.pos.x, 1e-3f);
    check_near("both T10 twins sit 70 above the actor", 70.f, first.pos.y, 1e-3f);
    check_near("twin yaw tracks the heading with no +-1 deg nudge", 0.f, first.dir.x, 1e-4f);
    for (int i = 0; i < 20; ++i) tick(g, in);
    first = g.take_pending_shot();
    second = g.take_pending_shot();
    check_bool("Rika charge T30 salvo fires twice", true, first.armed && second.armed);
    check_int("Rika T30 first row is 3", 3, first.bulletRow);
    check_int("Rika T30 second row is 6", 6, second.bulletRow);
    // The tick-30 salvo is NOT a single visit. shoot_body_4_1_450 gates it on
    // `counter > 0 && counter % 10 == 0` and returns before write_clock while the
    // post-increment counter is below 60, so the clock stays pinned at tick 30 for 30
    // updates and the salvo fires at counter 30, 40 and 50 — three pairs. The pair at
    // 40 and 50 is what this loop counts; the 29 updates take the counter 31..60.
    int frozenRequests = 0;
    for (int i = 0; i < 29; ++i) {
        tick(g, in);
        for (gameplay::PendingShot s = g.take_pending_shot(); s.armed;
             s = g.take_pending_shot())
            ++frozenRequests;
    }
    check_int("frozen interval keeps firing the counter-gated pair", 4, frozenRequests);
    check_int("freeze releases the clock at counter 60", 31, g.phase_elapsed());
    check_int("counter ran to 60 over the freeze", 60, g.move_counter());

    // Powered branch: shoot_body_4_1_450 picks ONE pair per branch, so the tick-30
    // salvo becomes rows 4/7 while the tick-10 pair stays 2/5. Rows 3/6 therefore
    // carry kGateNormal: without it a powered fighter fires BOTH pairs, which is 10
    // requests over the charge instead of the body's 8.
    Fighter h;
    h.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_rikaCombo.bind(h);
    settle(h);
    h.set_hypermode(Hypermode::Oyashiro);
    h.set_hyper_gauge(1.f);
    Input hp;
    hp.set(fnd::input::Action::Special, true);
    tick(h, hp);
    hp.set(fnd::input::Action::Special, false);
    tick(h, hp);
    check_bool("Rika Oyashiro witness is active", true, h.hyper_active());
    gameplay::ShootingContext context;
    context.aimHold = true;
    h.set_shooting_context(context);
    check_bool("Rika powered gate holds", true, h.shoot_gate_powered());
    hold_yellow(h, hp);
    hp.set(fnd::input::Action::Shoot, false);
    tick(h, hp);
    check_int("Rika powered charge binds move 450", 450, h.shot_move_id());
    // 60 updates carry the move from entry to the end of the freeze (tick 10, tick 30,
    // then 30 frozen updates); a few extra ticks only confirm the salvo has stopped.
    std::vector<int> poweredRows;
    for (int i = 0; i < 65; ++i) {
        tick(h, hp);
        for (gameplay::PendingShot s = h.take_pending_shot(); s.armed;
             s = h.take_pending_shot())
            poweredRows.push_back(s.bulletRow);
    }
    check_int("powered charge requests the body's 8 shots", 8, (int)poweredRows.size());
    if (poweredRows.size() == 8) {
        check_int("powered tick-10 first row stays 2", 2, poweredRows[0]);
        check_int("powered tick-10 second row stays 5", 5, poweredRows[1]);
        check_int("powered frozen salvo first row is 4", 4, poweredRows[2]);
        check_int("powered frozen salvo second row is 7", 7, poweredRows[3]);
        check_int("powered frozen salvo repeats row 4", 4, poweredRows[4]);
        check_int("powered frozen salvo repeats row 7", 7, poweredRows[5]);
        check_int("powered frozen salvo third row 4", 4, poweredRows[6]);
        check_int("powered frozen salvo third row 7", 7, poweredRows[7]);
    }
    check_bool("no normal-branch rows 3/6 leak into the powered salvo", true,
               std::find(poweredRows.begin(), poweredRows.end(), 3) == poweredRows.end() &&
                   std::find(poweredRows.begin(), poweredRows.end(), 6) == poweredRows.end());
}


void test_rika_pitch_latch() {
    section("33. Rika 1 latches its pitch instead of re-deriving it per salvo");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_rikaCombo.load(install, 4, 1))
        return skip_case("Rika 1 pitch latch");
    // shoot_body_4_1_450 computes the elevation ONCE at tick 10 (FUN_0042da80 ->
    // FUN_0066b668 -> write_scratch(0x3c)) and reads that value back for the frozen
    // tick-30 salvos. Recomputing the elevation per launch would re-aim a salvo whose
    // target changed height mid-attack, so this drives a dummy that moves vertically
    // between the two.
    Fighter attacker;
    attacker.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_rikaCombo.bind(attacker);
    settle(attacker);
    Fighter victim;
    victim.init(nullptr, nullptr, glm::vec3(0, 300, 500), 0.0f);
    g_rikaCombo.bind(victim);
    settle(victim);
    attacker.set_hypermode(Hypermode::Oyashiro);
    attacker.set_hyper_gauge(1.f);
    Input sp;
    sp.set(fnd::input::Action::Special, true);
    tick(attacker, sp, &victim);
    sp.set(fnd::input::Action::Special, false);
    tick(attacker, sp, &victim);
    gameplay::ShootingContext context;
    context.aimHold = true;
    attacker.set_shooting_context(context);
    hold_yellow(attacker, sp);
    sp.set(fnd::input::Action::Shoot, false);
    tick(attacker, sp, &victim);
    check_int("Rika pitch-latch charge binds move 450", 450, attacker.shot_move_id());
    for (int i = 0; i < 10; ++i) tick(attacker, sp, &victim);
    const gameplay::PendingShot first = attacker.take_pending_shot();
    const gameplay::PendingShot second = attacker.take_pending_shot();
    check_bool("tick-10 twin arms with the dummy in place", true,
               first.armed && second.armed);
    // atan2(300, 500) = 30.96 deg, clamped to +-40 and truncated by the int scratch:
    // the latched pitch is exactly 30 degrees, so dir.y is sin(30).
    const float latched = std::sin(glm::radians(30.f));
    check_near("tick-10 pitch is the latched 30 degrees", latched, first.dir.y, 1e-4f);
    check_near("tick-10 second twin shares the latched pitch", latched, second.dir.y, 1e-4f);

    // Raise the dummy far enough that a re-derived elevation would clamp to 40 degrees
    // (atan2(900, 500) = 60.9). The frozen salvo must still carry the latched 30.
    victim.reset(glm::vec3(0, 900, 500), victim.facing_yaw());
    std::vector<float> frozen;
    for (int i = 0; i < 40 && frozen.size() < 6; ++i) {
        tick(attacker, sp, &victim);
        for (gameplay::PendingShot s = attacker.take_pending_shot(); s.armed;
             s = attacker.take_pending_shot())
            frozen.push_back(s.dir.y);
    }
    check_int("frozen interval fires three pairs", 6, (int)frozen.size());
    for (float pitch : frozen)
        check_near("frozen salvo keeps the latched 30 degrees, not the new 40", latched,
                   pitch, 1e-4f);
}

void test_rika_air_powered_charge() {
    section("34. Rika 1 air charge 460: both branches over the frozen interval");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_rikaCombo.load(install, 4, 1))
        return skip_case("Rika 1 air charge");
    const auto* program = gameplay::move_program(&g_rikaCombo.moves);
    check_int("Rika air charge maps the air column to state 460", 460,
              program ? program->shot[1][1] : -1);
    // Reaching the air charge takes two things the port's air model does not hand you
    // for free: the charge must survive the leap (a jump press returns before the
    // charge block, so one tick is lost and it then re-accrues), and the air window
    // must outlast the program (a plain leap is 47 updates, so Z is held and the fly
    // budget carries it to ~112).
    Fighter f;
    f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_rikaCombo.bind(f);
    settle(f);
    f.set_hypermode(Hypermode::Oyashiro);
    f.set_hyper_gauge(1.f);
    Input sp;
    sp.set(fnd::input::Action::Special, true);
    tick(f, sp);
    sp.set(fnd::input::Action::Special, false);
    tick(f, sp);
    check_bool("Oyashiro witness is active", true, f.hyper_active());
    gameplay::ShootingContext context;
    context.aimHold = true;
    f.set_shooting_context(context);
    sp.set(fnd::input::Action::Shoot, true);
    sp.set(fnd::input::Action::Jump, true);
    tick(f, sp);
    sp.set(fnd::input::Action::Jump, false);
    int chargeTicks = 0;
    while (f.charge_tier() != ShotTier::Yellow && f.airborne() && chargeTicks++ < 200)
        tick(f, sp);
    check_int("charge completes during the fly", static_cast<int>(ShotTier::Yellow),
              static_cast<int>(f.charge_tier()));
    check_bool("fighter is airborne with the charge held", true, f.airborne());
    sp.set(fnd::input::Action::Shoot, false);
    tick(f, sp);
    check_int("air release binds the air charge move 460", 460, f.shot_move_id());

    for (int i = 0; i < 10; ++i) tick(f, sp);
    const gameplay::PendingShot first = f.take_pending_shot();
    const gameplay::PendingShot second = f.take_pending_shot();
    check_bool("air charge T10 twin arms", true, first.armed && second.armed);
    check_int("air T10 first row is 2", 2, first.bulletRow);
    check_int("air T10 second row is 5", 5, second.bulletRow);
    check_near("air T10 twin sits 60 ahead of the actor", 60.f, first.pos.z, 1e-3f);
    check_near("air T10 first twin sits 50 right of the heading", 50.f, first.pos.x, 1e-3f);
    check_near("air T10 second twin sits 50 left of the heading", -50.f, second.pos.x,
               1e-3f);
    // The height offset is pinned exactly on the ground path (section 17), where the
    // actor is stationary. Here the actor is in free fall and moves after the rule pass,
    // so this asserts what the air path can show exactly: both twins share one height
    // above the moving actor.
    check_bool("air T10 twins share a height above the falling actor", true,
               std::abs(first.pos.y - second.pos.y) < 1e-3f &&
                   first.pos.y > f.position().y);

    // The whole frozen interval on the air copy: three counter-gated pairs, all
    // powered. The air rules are a separate array entry, so their gates are exactly
    // where a copy/paste slip would hide. The tick-10 pair is already taken above, so
    // this collects the six frozen requests.
    std::vector<int> rows;
    for (int i = 0; i < 60 && rows.size() < 8; ++i) {
        tick(f, sp);
        for (gameplay::PendingShot s = f.take_pending_shot(); s.armed;
             s = f.take_pending_shot())
            rows.push_back(s.bulletRow);
    }
    check_int("air frozen interval fires three pairs", 6, (int)rows.size());
    if (rows.size() == 6) {
        check_int("air frozen pair 1 is rows 4 then 7", 4, rows[0]);
        check_int("air frozen pair 1 second row is 7", 7, rows[1]);
        check_int("air frozen pair 2 is rows 4 then 7", 4, rows[2]);
        check_int("air frozen pair 2 second row is 7", 7, rows[3]);
        check_int("air frozen pair 3 is rows 4 then 7", 4, rows[4]);
        check_int("air frozen pair 3 second row is 7", 7, rows[5]);
    }
    check_bool("air normal rows 3/6 stay gated out over the whole interval", true,
               std::find(rows.begin(), rows.end(), 3) == rows.end() &&
                   std::find(rows.begin(), rows.end(), 6) == rows.end());
    check_bool("air charge never emits the normal pair", true,
               std::find(rows.begin(), rows.end(), 0) == rows.end() ||
                   rows[0] == 2);
    // Normal air branch: same flight, no Oyashiro and no ally hold, so the tick-30
    // salvo must be rows 3/6 rather than 4/7. The powered half above cannot show this;
    // without it the air copy is only half-witnessed.
    Fighter normal;
    normal.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_rikaCombo.bind(normal);
    settle(normal);
    check_bool("normal air driver starts with the gate closed", false,
               normal.shoot_gate_powered());
    Input normalIn;
    normalIn.set(fnd::input::Action::Shoot, true);
    normalIn.set(fnd::input::Action::Jump, true);
    tick(normal, normalIn);
    normalIn.set(fnd::input::Action::Jump, false);
    int normalChargeTicks = 0;
    while (normal.charge_tier() != ShotTier::Yellow && normal.airborne() &&
           normalChargeTicks++ < 200)
        tick(normal, normalIn);
    check_int("normal air charge completes during the fly",
              static_cast<int>(ShotTier::Yellow),
              static_cast<int>(normal.charge_tier()));
    check_bool("normal air driver still airborne", true, normal.airborne());
    normalIn.set(fnd::input::Action::Shoot, false);
    tick(normal, normalIn);
    check_int("normal air release binds 460", 460, normal.shot_move_id());
    for (int i = 0; i < 10; ++i) tick(normal, normalIn);
    const gameplay::PendingShot normalFirst = normal.take_pending_shot();
    const gameplay::PendingShot normalSecond = normal.take_pending_shot();
    check_bool("normal air T10 twin arms", true,
               normalFirst.armed && normalSecond.armed);
    check_int("normal air T10 first row is 2", 2, normalFirst.bulletRow);
    check_int("normal air T10 second row is 5", 5, normalSecond.bulletRow);
    std::vector<int> normalRows;
    for (int i = 0; i < 60 && normalRows.size() < 6; ++i) {
        tick(normal, normalIn);
        for (gameplay::PendingShot s = normal.take_pending_shot(); s.armed;
             s = normal.take_pending_shot())
            normalRows.push_back(s.bulletRow);
    }
    check_int("normal air frozen interval fires three pairs", 6, (int)normalRows.size());
    if (normalRows.size() == 6) {
        check_int("normal air frozen pair 1 is rows 3 then 6", 3, normalRows[0]);
        check_int("normal air frozen pair 1 second row is 6", 6, normalRows[1]);
        check_int("normal air frozen pair 2 is rows 3 then 6", 3, normalRows[2]);
        check_int("normal air frozen pair 2 second row is 6", 6, normalRows[3]);
        check_int("normal air frozen pair 3 is rows 3 then 6", 3, normalRows[4]);
        check_int("normal air frozen pair 3 second row is 6", 6, normalRows[5]);
    }
    check_bool("normal air never emits the powered rows 4/7", true,
               std::find(normalRows.begin(), normalRows.end(), 4) == normalRows.end() &&
                   std::find(normalRows.begin(), normalRows.end(), 7) == normalRows.end());
}

void test_tomitake_twin_tap() {
    section("18. Tomitake 2 twin tap + charge (bodies shoot_body_6_2_*)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_tomitakeCombo.load(install, 6, 2))
        return skip_case("Tomitake 2 combo");
    // Bundle evidence: Tomitake 2 (handler 0x527880) fires twin shots — rows 7+5 —
    // on every third tick 15..33 in the ground tap (shoot_body_6_2_400; the traces
    // record fire_attachment(0,7,...) twice per scheduled frame), and rows 4+0 at
    // tick 30 in the first ground charge after a 15-tick freeze at tick 28
    // (shoot_body_6_2_450). Her program is kTomitakeRules; charge 2 stays provisional.
    Fighter f;
    f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_tomitakeCombo.bind(f);
    settle(f);
    Input in;
    in.set(fnd::input::Action::Shoot, true);
    tick(f, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(f, in);
    check_int("Tomitake tap enters ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    check_int("Tomitake tap binds move 400", 400, f.shot_move_id());
    for (int i = 0; i < 15; ++i) tick(f, in);
    gameplay::PendingShot first = f.take_pending_shot();
    gameplay::PendingShot second = f.take_pending_shot();
    check_bool("Tomitake tap T15 salvo fires twice", true, first.armed && second.armed);
    check_int("Tomitake T15 first row is 7", 7, first.bulletRow);
    check_int("Tomitake T15 second row is 5", 5, second.bulletRow);
    // Repeat on the next scheduled tick: the schedule, not a single anchor.
    tick(f, in);
    tick(f, in);
    tick(f, in);
    first = f.take_pending_shot();
    second = f.take_pending_shot();
    check_bool("Tomitake tap T18 salvo fires twice", true, first.armed && second.armed);
    check_int("Tomitake T18 first row is 7", 7, first.bulletRow);
    check_int("Tomitake T18 second row is 5", 5, second.bulletRow);
    Fighter g;
    g.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_tomitakeCombo.bind(g);
    settle(g);
    hold_yellow(g, in);
    check_int("Tomitake hold reaches Yellow", static_cast<int>(ShotTier::Yellow),
              static_cast<int>(g.charge_tier()));
    in.set(fnd::input::Action::Shoot, false);
    tick(g, in);
    check_int("Tomitake charge enters ShootB", static_cast<int>(FighterState::ShootB),
              static_cast<int>(g.state()));
    check_int("Tomitake charge binds move 450", 450, g.shot_move_id());
    // Tick 28 freezes the clock for 15 updates, then tick 30 fires rows 4+0.
    for (int i = 0; i < 46; ++i) tick(g, in);
    first = g.take_pending_shot();
    second = g.take_pending_shot();
    check_bool("Tomitake charge T30 salvo fires twice", true, first.armed && second.armed);
    check_int("Tomitake T30 first row is 4", 4, first.bulletRow);
    check_int("Tomitake T30 second row is 0", 0, second.bulletRow);
}

void test_chie_scratch_burst() {
    section("21. Chie 2 scratch burst + single salvos (bodies shoot_body_11_2_*)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_chieCombo.load(install, 11, 2))
        return skip_case("Chie 2 combo");
    // Bundle evidence: Chie 2 (handler 0x566a40) fires item row 0 at ticks 15,18,21,24
    // in the ground tap (shoot_body_11_2_400: scratch counter fires while scratch%3==1)
    // and item row 2 once at tick 22 in the first ground charge (tick 15 in the air
    // charge — same rule shape, untested here like the other air paths).
    // Her program is kChieRules; the second charge stays provisional.
    Fighter f;
    f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_chieCombo.bind(f);
    settle(f);
    Input in;
    in.set(fnd::input::Action::Shoot, true);
    tick(f, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(f, in);
    check_int("Chie tap enters ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    check_int("Chie tap binds move 400", 400, f.shot_move_id());
    for (int i = 0; i < 15; ++i) tick(f, in);
    gameplay::PendingShot shot = f.take_pending_shot();
    check_bool("Chie tap launches at tick 15", true, shot.armed);
    check_int("Chie tap selects item row zero", 0, shot.bulletRow);
    tick(f, in);
    tick(f, in);
    tick(f, in);
    shot = f.take_pending_shot();
    check_bool("Chie tap launches again at tick 18", true, shot.armed);
    check_int("Chie repeat selects item row zero", 0, shot.bulletRow);
    Fighter g;
    g.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_chieCombo.bind(g);
    settle(g);
    hold_yellow(g, in);
    check_int("Chie hold reaches Yellow", static_cast<int>(ShotTier::Yellow),
              static_cast<int>(g.charge_tier()));
    in.set(fnd::input::Action::Shoot, false);
    tick(g, in);
    check_int("Chie charge enters ShootB", static_cast<int>(FighterState::ShootB),
              static_cast<int>(g.state()));
    check_int("Chie charge binds move 450", 450, g.shot_move_id());
    for (int i = 0; i < 22; ++i) tick(g, in);
    shot = g.take_pending_shot();
    check_bool("Chie charge launches at tick 22", true, shot.armed);
    check_int("Chie charge selects item row two", 2, shot.bulletRow);
}

void test_rika2_single_tick() {
    section("24. Rika 2 single tick + triple fan (bodies shoot_body_4_2_*)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_rika2Combo.load(install, 4, 2))
        return skip_case("Rika 2 combo");
    // Bundle evidence: Rika 2 (handler 0x49d890) fires item row 0 once at tick 15 in
    // the ground tap (same-tick Hold 30 freezes the clock after), and a fan of three
    // row-4 shots at tick 10 in the first ground charge (tag branches need an aim/tag
    // flag this model has no field for — skipped). Her program is kRika2Rules; the
    // second charge stays provisional.
    Fighter f;
    f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_rika2Combo.bind(f);
    settle(f);
    Input in;
    in.set(fnd::input::Action::Shoot, true);
    tick(f, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(f, in);
    check_int("Rika2 tap enters ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    check_int("Rika2 tap binds move 400", 400, f.shot_move_id());
    for (int i = 0; i < 15; ++i) tick(f, in);
    gameplay::PendingShot shot = f.take_pending_shot();
    check_bool("Rika2 tap launches at tick 15", true, shot.armed);
    check_int("Rika2 tap selects item row zero", 0, shot.bulletRow);
    Fighter g;
    g.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_rika2Combo.bind(g);
    settle(g);
    hold_yellow(g, in);
    check_int("Rika2 hold reaches Yellow", static_cast<int>(ShotTier::Yellow),
              static_cast<int>(g.charge_tier()));
    in.set(fnd::input::Action::Shoot, false);
    tick(g, in);
    check_int("Rika2 charge enters ShootB", static_cast<int>(FighterState::ShootB),
              static_cast<int>(g.state()));
    check_int("Rika2 charge binds move 450", 450, g.shot_move_id());
    // Drive by elapsed: phase changes reset the counter mid-move, so a fixed tick
    // count would miss the window (Mion-2 precedent). One extra tick after the loop:
    // the loop exits right after the tick that SET elapsed, whose rule pass saw less.
    int rika2Guard = 0;
    while (g.phase_elapsed() < 10 && rika2Guard++ < 120) tick(g, in);
    check_int("Rika2 charge reaches tick 10", 10, g.phase_elapsed());
    tick(g, in);
    int fanArmed = 0;
    bool fanRows = true;
    for (int i = 0; i < 3; ++i) {
        shot = g.take_pending_shot();
        if (shot.armed) ++fanArmed;
        if (shot.bulletRow != 4) fanRows = false;
    }
    check_int("Rika2 charge T10 fan fires three", 3, fanArmed);
    check_bool("Rika2 fan rows are all 4", true, fanRows);
    check_bool("Rika2 fan fires exactly three", false,
               g.take_pending_shot().armed);
}

void test_rena0_powered_branches() {
    section("37. Rena 0 powered branch on every launch site (handler 0x43ffc0)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_testCombo.load(install, 0, 0))
        return skip_case("Rena 0 combo");
    // FUN_0043ffc0 gates every launch on byte 0x845/word 0x848:
    //   tap 400 rows 0/6, air tap 402 rows 1/7, charge 450 rows 2/8 (fixed 45 deg),
    //   air charge 460 rows 2/8 (fixed 45 deg), second charge 360/370 rows 11/12
    //   (world origins, no branch split in the source).
    const auto* program = gameplay::move_program(&g_testCombo.moves);
    check_bool("Rena 0 program is bound", true,
               program && program->rules == gameplay::kRenaRules);
    // Tap: normal at tick 12, powered at the same tick with row 6.
    Fighter tap;
    tap.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_testCombo.bind(tap);
    settle(tap);
    tap.set_hypermode(Hypermode::Oyashiro);
    tap.set_hyper_gauge(1.f);
    Input in;
    in.set(fnd::input::Action::Special, true);
    tick(tap, in);
    in.set(fnd::input::Action::Special, false);
    tick(tap, in);
    check_bool("Oyashiro witness is active", true, tap.hyper_active());
    gameplay::ShootingContext context;
    context.aimHold = true;
    tap.set_shooting_context(context);
    check_bool("powered gate holds", true, tap.shoot_gate_powered());
    in.set(fnd::input::Action::Shoot, true);
    tick(tap, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(tap, in);
    check_int("Rena powered tap enters ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(tap.state()));
    for (int i = 0; i < 12; ++i) tick(tap, in);
    const gameplay::PendingShot poweredTap = tap.take_pending_shot();
    check_bool("powered tap fires its request", true, poweredTap.armed);
    check_int("powered tap switches to item row 6", 6, poweredTap.bulletRow);
    check_bool("powered tap schedules no extra shot", false,
               tap.take_pending_shot().armed);

    // Air charge: powered row 8 at the fixed 45 pitch.
    Fighter airCharge;
    airCharge.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_testCombo.bind(airCharge);
    settle(airCharge);
    airCharge.set_hypermode(Hypermode::Oyashiro);
    airCharge.set_hyper_gauge(1.f);
    Input air;
    air.set(fnd::input::Action::Special, true);
    tick(airCharge, air);
    air.set(fnd::input::Action::Special, false);
    tick(airCharge, air);
    airCharge.set_shooting_context(context);
    air.set(fnd::input::Action::Shoot, true);
    int guard = 0;
    while (airCharge.charge_tier() != ShotTier::Yellow && guard++ < 2000)
        tick(airCharge, air);
    check_int("charge reaches Yellow before the leap",
              static_cast<int>(ShotTier::Yellow),
              static_cast<int>(airCharge.charge_tier()));
    // Leap and HOLD Z: the plain-leap window (47 updates) is shorter than the
    // remaining program, so hold Z against the fly budget like the Rika air witness
    // does. The charge is re-lost for one tick (the jump returns before the charge
    // block) and then re-accrues, so keep C held through the air as well.
    air.set(fnd::input::Action::Jump, true);
    tick(airCharge, air);
    // Wait only until the charge re-accrues mid-flight, then release immediately: the
    // fly budget holds ~112 updates, which is more than the 60-update program needs,
    // but draining the whole flight first would land the fighter before the release.
    int airTicks = 0;
    while (airCharge.charge_tier() != ShotTier::Yellow && airCharge.airborne() &&
           airTicks++ < 200)
        tick(airCharge, air);
    check_bool("charge re-accrues during the flight", true,
               airTicks > 1 && airTicks < 200);
    check_bool("driver still airborne at the release", true, airCharge.airborne());
    air.set(fnd::input::Action::Shoot, false);
    tick(airCharge, air);
    check_int("air release binds move 460", 460, airCharge.shot_move_id());
    for (int i = 0; i < 12; ++i) tick(airCharge, air);
    const gameplay::PendingShot poweredAir = airCharge.take_pending_shot();
    check_bool("powered air charge fires its request", true, poweredAir.armed);
    check_int("powered air charge switches to item row 8", 8, poweredAir.bulletRow);
    check_near("air charge pitch is the body's fixed 45 degrees",
               std::sin(glm::radians(45.f)), poweredAir.dir.y, 1e-3f);

    // Second charge: counter-gated freeze rather than a plain hold. Draining the
    // whole frozen interval is the only way to count the requests faithfully.
    Fighter second;
    second.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_testCombo.bind(second);
    settle(second);
    // A Red-tier hold reaches the second charge; the fixture helper only drives to
    // Yellow, so keep holding until the tier rolls over.
    Input red;
    red.set(fnd::input::Action::Shoot, true);
    int redGuard = 0;
    while (second.charge_tier() != ShotTier::Red && redGuard++ < 4000)
        tick(second, red);
    check_int("Rena 0 reaches Red for the second charge",
              static_cast<int>(ShotTier::Red),
              static_cast<int>(second.charge_tier()));
    red.set(fnd::input::Action::Shoot, false);
    tick(second, red);
    check_int("second charge binds move 360", 360, second.shot_move_id());
    // The counter-gated freeze pins the clock while the counter climbs to 10; the
    // red twin at tick 2 fires once, and the freeze is released on the 11th update.
    int tick13Updates = 0;
    for (int i = 0; i < 40 && second.phase_elapsed() <= 13; ++i) {
        tick(second, red);
        ++tick13Updates;
        for (gameplay::PendingShot s = second.take_pending_shot(); s.armed;
             s = second.take_pending_shot()) {
            check_bool("red twin requests the world rows", true,
                       s.bulletRow == 11 || s.bulletRow == 12);
        }
    }
    // The counter starts at 0 on entry, so reaching the bound-10 gate at tick 13 takes
    // 13 updates (counter 1..13) plus nine more while the gate holds (counter 14..22,
    // released when it reaches 23): 22 updates to leave tick 13 behind.
    check_int("freeze releases after the counter reaches the gate bound", 22,
              tick13Updates);
    check_bool("the frozen tick stays pinned, not skipped", true,
               second.phase_elapsed() >= 13);
}

void test_keiichi2_tap_sweep() {
    section("43. Keiichi 2 sweeping tap (bodies shoot_body_2_2_400/402)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_keiichiCombo.load(install, 2, 2))
        return skip_case("Keiichi 2 combo");
    // The tap fires ONE slot-0 request a tick for eleven ticks (10..20), rows 0/1, and
    // each request aims `0x3a - 15 + draw%10` on the yaw with `draw%10 + 5` of pitch over
    // the clamped target elevation. 0x3a grows by 2 a tick, so the volley sweeps. The
    // yaw draw is taken FIRST, which is unique to this family.
    const auto* program = gameplay::move_program(&g_keiichiCombo.moves);
    check_bool("Keiichi 2 program is bound", true,
               program && program->rules == gameplay::kKeiichiRules);
    Fighter f;
    f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_keiichiCombo.bind(f);
    settle(f);
    Input in;
    in.set(fnd::input::Action::Shoot, true);
    tick(f, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(f, in);
    check_int("Keiichi 2 tap enters ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    std::vector<gameplay::PendingShot> shots;
    int guard = 0;
    while (shots.size() < 11 && guard++ < 60) {
        tick(f, in);
        for (gameplay::PendingShot s = f.take_pending_shot(); s.armed;
             s = f.take_pending_shot())
            shots.push_back(s);
    }
    check_int("the tap fires eleven requests", 11, (int)shots.size());
    if (shots.size() == 11) {
        bool allRowZero = true, allSlotZero = true;
        for (const auto& s : shots) {
            allRowZero &= s.bulletRow == 0;
            allSlotZero &= s.origin.attachmentSlot == 0;
        }
        check_bool("every normal tap request uses item row 0", true, allRowZero);
        check_bool("every normal tap request uses slot 0", true, allSlotZero);
        // The sweep: the yaw must move monotonically except for the +/-10 jitter, so the
        // first and last requests are far apart while consecutive ones stay close.
        auto yawOf = [](const gameplay::PendingShot& s) {
            return 90.f - glm::degrees(std::atan2(s.dir.x, s.dir.z));
        };
        const float first = yawOf(shots.front());
        const float last = yawOf(shots.back());
        check_bool("the tap sweeps across the arc", true, std::abs(last - first) > 8.f);
        bool stepSane = true;
        for (std::size_t i = 1; i < shots.size(); ++i) {
            const float step = yawOf(shots[i]) - yawOf(shots[i - 1]);
            stepSane &= std::abs(step) < 20.f;   // 2 deg of sweep plus <=9 of jitter
        }
        check_bool("consecutive sweep steps stay within the body's range", true, stepSane);
        // The pitch is `draw%10 + 5 + clamped elevation`; with no opponent the elevation
        // is 0, so every request pitches inside [5, 15) degrees.
        bool pitchInRange = true;
        for (const auto& s : shots) {
            const float deg = glm::degrees(std::asin(std::clamp(s.dir.y, -1.f, 1.f)));
            pitchInRange &= deg >= 4.9f && deg < 15.f;
        }
        check_bool("tap pitch stays inside the body's 5..15 range", true, pitchInRange);
        // Exact arithmetic, which pins the counter, the jitter and the DRAW ORDER at once.
        // The canonical stream's first four residues are 2, 2, 4, 5. The body writes 0x3b
        // (yaw) from the FIRST draw and 0x3c (pitch) from the second, so:
        //   tick 10, counter 2: yaw = 2 - 15 + 2 = -11, pitch = 0 + 2 + 5 = 7
        //   tick 11, counter 4: yaw = 4 - 15 + 4 =  -7, pitch = 0 + 5 + 5 = 10
        // Drawing pitch first would give -6 / 9 on the second request instead.
        check_near("first request yaws at counter 2 minus 15 plus draw 2", 90.f - 11.f,
                   yawOf(shots[0]), 0.2f);
        check_near("first request pitches at draw 2 plus 5",
                   std::sin(glm::radians(7.f)), shots[0].dir.y, 1e-3f);
        check_near("second request yaws at counter 4 minus 15 plus draw 4", 90.f - 7.f,
                   yawOf(shots[1]), 0.2f);
        check_near("second request pitches at draw 5 plus 5 (yaw is drawn first)",
                   std::sin(glm::radians(10.f)), shots[1].dir.y, 1e-3f);
    }

    // Powered: the same sweep on row 1.
    Fighter p;
    p.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_keiichiCombo.bind(p);
    settle(p);
    p.set_hypermode(Hypermode::Oyashiro);
    p.set_hyper_gauge(1.f);
    Input sp;
    sp.set(fnd::input::Action::Special, true);
    tick(p, sp);
    sp.set(fnd::input::Action::Special, false);
    tick(p, sp);
    gameplay::ShootingContext context;
    context.aimHold = true;
    p.set_shooting_context(context);
    sp.set(fnd::input::Action::Shoot, true);
    tick(p, sp);
    sp.set(fnd::input::Action::Shoot, false);
    tick(p, sp);
    std::vector<int> rows;
    guard = 0;
    while (rows.size() < 11 && guard++ < 60) {
        tick(p, sp);
        for (gameplay::PendingShot s = p.take_pending_shot(); s.armed;
             s = p.take_pending_shot())
            rows.push_back(s.bulletRow);
    }
    bool allRowOne = !rows.empty();
    for (int r : rows) allRowOne &= r == 1;
    check_int("powered tap fires eleven requests", 11, (int)rows.size());
    check_bool("powered tap uses item row 1 throughout", true, allRowOne);
}

void test_satoko1_periodic_world_shot() {
    section("44. Satoko 1 periodic +600 world shot (bodies shoot_body_3_1_*)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_satoko1Combo.load(install, 3, 1))
        return skip_case("Satoko 1 combo");
    // Bundle evidence: the countdown starts at 120, drops one a tick, and the request fires
    // whenever it is 1 mod 30 — so ticks 28, 58, 88 in the port's pre-increment numbering.
    // Every firing is ONE world request at the actor's own position 600 units UP, aimed
    // along the heading with pitch 0, row 6 normally and row 7 powered, in every state.
    //
    // Only the FIRST fire lands here: the port's tap move lasts about 40 ticks, while the
    // body's family runs ten states (400..409) and would fire five times. The port's shot
    // table maps two states per form, so the later fires need the state/duration model
    // widened — a separate gap, not a binding one. The tick-28 landing is what pins the
    // counter start and the 30-tick modulus: any other start or modulus moves it.
    const auto* program = gameplay::move_program(&g_satoko1Combo.moves);
    check_bool("Satoko 1 program is bound", true,
               program && program->rules == gameplay::kSatoko1Rules);
    Fighter f;
    f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_satoko1Combo.bind(f);
    settle(f);
    Input in;
    in.set(fnd::input::Action::Shoot, true);
    tick(f, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(f, in);
    check_int("Satoko 1 tap enters ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    std::vector<int> fireTicks;
    std::vector<int> rows;
    std::vector<float> heights;
    for (int i = 1; i <= 100; ++i) {
        tick(f, in);
        for (gameplay::PendingShot s = f.take_pending_shot(); s.armed;
             s = f.take_pending_shot()) {
            fireTicks.push_back(i);
            rows.push_back(s.bulletRow);
            heights.push_back(s.pos.y - f.position().y);
        }
    }
    check_int("Satoko 1 fires once in the tap's 40-tick state", 1, (int)fireTicks.size());
    if (!fireTicks.empty())
        check_int("Satoko 1 first fire lands on the body's tick 28", 28, fireTicks[0]);
    bool allRow6 = !rows.empty(), allHeight = !heights.empty();
    for (int r : rows) allRow6 &= r == 6;
    for (float h : heights) allHeight &= std::abs(h - 600.f) < 0.5f;
    check_bool("Satoko 1 normal fire uses item row 6", true, allRow6);
    check_bool("Satoko 1 fire sits 600 units above the actor", true, allHeight);
    // One slot-0 world request per firing, not a salvo.
    check_bool("Satoko 1 fires exactly one request per period", false,
               f.take_pending_shot().armed);

    // Powered: the same period on row 7.
    Fighter p;
    p.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_satoko1Combo.bind(p);
    settle(p);
    p.set_hypermode(Hypermode::Oyashiro);
    p.set_hyper_gauge(1.f);
    Input hp;
    hp.set(fnd::input::Action::Special, true);
    tick(p, hp);
    hp.set(fnd::input::Action::Special, false);
    tick(p, hp);
    gameplay::ShootingContext context;
    context.aimHold = true;
    p.set_shooting_context(context);
    hp.set(fnd::input::Action::Shoot, true);
    tick(p, hp);
    hp.set(fnd::input::Action::Shoot, false);
    tick(p, hp);
    std::vector<int> poweredRows;
    for (int i = 1; i <= 100; ++i) {
        tick(p, hp);
        for (gameplay::PendingShot s = p.take_pending_shot(); s.armed;
             s = p.take_pending_shot())
            poweredRows.push_back(s.bulletRow);
    }
    bool allRow7 = !poweredRows.empty();
    for (int r : poweredRows) allRow7 &= r == 7;
    check_int("powered Satoko 1 still fires once", 1, (int)poweredRows.size());
    check_bool("powered Satoko 1 uses item row 7", true, allRow7);
}

void test_simulation_rng_stream() {
    section("40. simulation RNG: MT19937 recovered from FUN_0065d150/FUN_0065d0c0");
    // The port reproduces the original's ALGORITHM, not its stream position. The pins
    // below are MT19937's own canonical seed-5489 vector, which is what the re-seed path
    // passes (0x1571), so a wrong twist, matrix word, temper mask or seed would all fail.
    gameplay::SimulationRng rng;
    const std::uint32_t expected[] = {3499211612u, 581869302u, 3890346734u,
                                      3586334585u, 545404204u};
    for (std::uint32_t want : expected)
        check_int("canonical MT19937 seed-5489 output", (long long)want,
                  (long long)rng.next());
    // Same seed, same sequence; a fresh instance restarts it.
    gameplay::SimulationRng again;
    for (std::uint32_t want : expected)
        check_int("a fresh stream repeats the sequence", (long long)want,
                  (long long)again.next());
    // An unset axis must consume no draw, or a deterministic rule would shift the stream
    // for every later spread in the match.
    gameplay::SimulationRng untouched;
    untouched.modulo(0);
    check_int("a zero modulus consumes no draw", (long long)expected[0],
              (long long)untouched.next());
}

void test_spread_draw_order() {
    section("41. spread draw order and ranges (pitch first, then yaw)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_mion1Combo.load(install, 1, 1))
        return skip_case("Mion 1 combo");
    // Mion 1's 450 draws pitch `(draw%100-50)*0.1` FIRST and yaw `(draw%200-100)*0.1`
    // second. On a fresh stream those are the canonical 3499211612 and 581869302, whose
    // residues are 12 and 102 — so the first request of the burst must pitch at
    // (12-50)*0.1 = -3.8 degrees and yaw at +0.2. Swapping the order would give
    // (12-100)*0.1 = -8.8 and (102-50)*0.1 = +5.2 and fail both.
    Fighter f;
    f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_mion1Combo.bind(f);
    settle(f);
    Input in;
    hold_yellow(f, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(f, in);
    check_int("Mion 1 charge binds move 450", 450, f.shot_move_id());
    for (int i = 0; i < 17; ++i) tick(f, in);
    const gameplay::PendingShot first = f.take_pending_shot();
    check_bool("burst fires its first request", true, first.armed);
    check_near("first burst request pitches at the canonical first draw",
               std::sin(glm::radians(-3.8f)), first.dir.y, 1e-3f);
    // The legacy basis builds the direction as (cos(yaw), .., sin(yaw)), so the yaw is
    // the complement of atan2(x, z). With no facing the base is 90 degrees and the +0.2
    // spread draw puts it at 90.2.
    const float legacyYaw = 90.f - glm::degrees(std::atan2(first.dir.x, first.dir.z));
    check_near("first burst request yaws at the canonical second draw", 90.2f,
               legacyYaw, 0.1f);
    // The remaining 14 iterations each re-draw, so the volley must fan out rather than
    // repeat one direction.
    std::vector<float> pitches;
    for (gameplay::PendingShot s = f.take_pending_shot(); s.armed;
         s = f.take_pending_shot())
        pitches.push_back(s.dir.y);
    check_int("the burst is fifteen requests", 14, (int)pitches.size());
    bool anyDifferent = false;
    for (float p : pitches) anyDifferent |= std::abs(p - first.dir.y) > 1e-4f;
    check_bool("later iterations draw their own spread", true, anyDifferent);
}

void test_rena2_ring() {
    section("42. Rena 2 world ring: one attachment plus ten spread worlds");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_rena2Combo.load(install, 0, 2))
        return skip_case("Rena 2 combo");
    // FUN_00438310.c:1757-1800: at phase 1 tick 35 state 400 fires one slot-0 attachment
    // request at fixed angles (rows 0/2) and then a ten-iteration world ring (rows 1/3)
    // at 200 forward / +30 high, each iteration drawing its own pitch and yaw.
    check_int("Rena 2 uses item 33", 33, g_rena2Combo.weapon.id);
    const auto* program = gameplay::move_program(&g_rena2Combo.moves);
    check_bool("Rena 2 program is bound", true,
               program && program->rules == gameplay::kRena2Rules);
    check_int("Rena 2 binds state 400", 400, program ? program->shot[0][0] : -1);
    check_int("Rena 2 claims nothing for 402", -1, program ? program->shot[0][1] : -2);

    Fighter f;
    f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_rena2Combo.bind(f);
    settle(f);
    Input in;
    in.set(fnd::input::Action::Shoot, true);
    tick(f, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(f, in);
    check_int("Rena 2 tap enters ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    std::vector<gameplay::PendingShot> shots;
    int guard = 0;
    while (shots.size() < 11 && guard++ < 80) {
        tick(f, in);
        for (gameplay::PendingShot s = f.take_pending_shot(); s.armed;
             s = f.take_pending_shot())
            shots.push_back(s);
    }
    check_int("the ring fires one attachment plus ten worlds", 11, (int)shots.size());
    if (shots.size() == 11) {
        check_int("the attachment request is row 0", 0, shots[0].bulletRow);
        check_bool("the attachment request has no spread", true,
                   std::abs(shots[0].dir.y) < 1e-4f);
        bool worldsRowOne = true;
        bool worldsSpread = false;
        for (std::size_t i = 1; i < shots.size(); ++i) {
            worldsRowOne &= shots[i].bulletRow == 1;
            if (std::abs(shots[i].dir.y - shots[1].dir.y) > 1e-4f) worldsSpread = true;
        }
        check_bool("every ring request uses item row 1", true, worldsRowOne);
        check_bool("the ten worlds draw their own spread", true, worldsSpread);
        // `rand%30 + 20` is absolute, so the ring pitches inside [20, 50) degrees.
        bool inRange = true;
        for (std::size_t i = 1; i < shots.size(); ++i) {
            const float degrees = glm::degrees(std::asin(
                std::clamp(shots[i].dir.y, -1.f, 1.f)));
            inRange &= degrees >= 19.9f && degrees <= 49.9f;
        }
        check_bool("ring pitch stays inside the body's 20..50 range", true, inRange);
    }
}

void test_rena1_normal_schedule() {
    section("27. Rena 1 tap fan + fixed-pitch charge (runtime-source helper)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_rena1Combo.load(install, 0, 1))
        return skip_case("Rena 1 combo");
    // battle_rena_mobile_shooting.hpp:181-184 requests one shot per frame 12..26
    // (15 rolls), row 1 normal / 3 powered, with yaw/pitch from a per-frame draw()%10.
    // The port has no per-tick draw service, so each frame fires its row with the pitch
    // the fixed path resolves; the spread is an explicit gap, not a claim.
    // The charge (line 187) is a single fixed-45 attachment shot, row 2/8.
    const auto* program = gameplay::move_program(&g_rena1Combo.moves);
    check_bool("Rena 1 move program is bound to its actual combo", true,
               program && program->rules == gameplay::kRena1Rules);
    check_int("Rena 1 tap maps to move 400", 400, program ? program->shot[0][0] : -1);
    check_int("Rena 1 air tap stays unbound", -1, program ? program->shot[0][1] : -2);
    check_int("Rena 1 first charge maps to move 450", 450, program ? program->shot[1][0] : -1);
    check_int("Rena 1 air charge stays unbound", -1, program ? program->shot[1][1] : -2);
    check_int("Rena 1 second charge stays unbound", -1, program ? program->shot[2][0] : -2);
    check_int("Rena 1 uses item 3", 3, g_rena1Combo.weapon.id);

    // Normal tap: 15 armed requests across frames 12..26, all row 1.
    Fighter tap;
    tap.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_rena1Combo.bind(tap);
    settle(tap);
    Input in;
    in.set(fnd::input::Action::Shoot, true);
    tick(tap, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(tap, in);
    check_int("Rena 1 tap enters ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(tap.state()));
    check_int("Rena 1 tap binds move 400", 400, tap.shot_move_id());
    int normalFired = 0;
    bool normalRows = true;
    for (int i = 0; i < 30; ++i) {
        tick(tap, in);
        for (gameplay::PendingShot s = tap.take_pending_shot(); s.armed;
             s = tap.take_pending_shot()) {
            ++normalFired;
            normalRows &= s.bulletRow == 1;
        }
    }
    check_int("normal tap fires the 15-frame fan", 15, normalFired);
    check_bool("normal fan uses item row 1 throughout", true, normalRows);
    check_bool("normal fan schedules nothing outside the window", false,
               tap.take_pending_shot().armed);

    // Powered tap: same window, row 3, with the gate selecting the other branch.
    Fighter poweredTap;
    poweredTap.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_rena1Combo.bind(poweredTap);
    settle(poweredTap);
    poweredTap.set_hypermode(Hypermode::Oyashiro);
    poweredTap.set_hyper_gauge(1.f);
    Input pw;
    pw.set(fnd::input::Action::Special, true);
    tick(poweredTap, pw);
    pw.set(fnd::input::Action::Special, false);
    tick(poweredTap, pw);
    check_bool("Oyashiro witness is active", true, poweredTap.hyper_active());
    gameplay::ShootingContext context;
    context.aimHold = true;
    poweredTap.set_shooting_context(context);
    pw.set(fnd::input::Action::Shoot, true);
    tick(poweredTap, pw);
    pw.set(fnd::input::Action::Shoot, false);
    tick(poweredTap, pw);
    int poweredFired = 0;
    bool poweredRows = true;
    for (int i = 0; i < 30; ++i) {
        tick(poweredTap, pw);
        for (gameplay::PendingShot s = poweredTap.take_pending_shot(); s.armed;
             s = poweredTap.take_pending_shot()) {
            ++poweredFired;
            poweredRows &= s.bulletRow == 3;
        }
    }
    check_int("powered tap fires the 15-frame fan", 15, poweredFired);
    check_bool("powered fan uses item row 3 throughout", true, poweredRows);

    // Charge: single fixed-45 shot at frame 13, row 2 normal / 8 powered.
    Fighter charged;
    charged.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_rena1Combo.bind(charged);
    settle(charged);
    hold_yellow(charged, in);
    check_int("Rena 1 hold reaches Yellow", static_cast<int>(ShotTier::Yellow),
              static_cast<int>(charged.charge_tier()));
    in.set(fnd::input::Action::Shoot, false);
    tick(charged, in);
    check_int("Rena 1 charge enters ShootB", static_cast<int>(FighterState::ShootB),
              static_cast<int>(charged.state()));
    check_int("Rena 1 first charge binds move 450", 450, charged.shot_move_id());
    for (int i = 0; i < 13; ++i) tick(charged, in);
    const gameplay::PendingShot charge = charged.take_pending_shot();
    check_bool("charge fires exactly one request at frame 13", true, charge.armed);
    check_int("charge uses item row 2", 2, charge.bulletRow);
    check_near("charge pitch is the body's fixed 45 degrees",
               std::sin(glm::radians(45.f)), charge.dir.y, 1e-3f);
    check_bool("charge schedules nothing else", false, charged.take_pending_shot().armed);

    Fighter poweredCharge;
    poweredCharge.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_rena1Combo.bind(poweredCharge);
    settle(poweredCharge);
    poweredCharge.set_hypermode(Hypermode::Oyashiro);
    poweredCharge.set_hyper_gauge(1.f);
    Input cpw;
    cpw.set(fnd::input::Action::Special, true);
    tick(poweredCharge, cpw);
    cpw.set(fnd::input::Action::Special, false);
    tick(poweredCharge, cpw);
    poweredCharge.set_shooting_context(context);
    hold_yellow(poweredCharge, cpw);
    cpw.set(fnd::input::Action::Shoot, false);
    tick(poweredCharge, cpw);
    for (int i = 0; i < 13; ++i) tick(poweredCharge, cpw);
    const gameplay::PendingShot poweredShot = poweredCharge.take_pending_shot();
    check_bool("powered charge fires its request", true, poweredShot.armed);
    check_int("powered charge uses item row 8", 8, poweredShot.bulletRow);
    check_near("powered charge keeps the fixed 45 degrees",
               std::sin(glm::radians(45.f)), poweredShot.dir.y, 1e-3f);
}

void test_akane2_world_origin_gap() {
    section("28. Akane 2 item-46 fixture deferred: world-origin shots");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_akane2Combo.load(install, 13, 2))
        return skip_case("Akane 2 combo");
    check_int("Akane 2 fixture binds item 46", 46, g_akane2Combo.weapon.id);
    check_int("Akane 2 item has eight bullet table entries", 8, g_akane2Combo.weapon.bulletCount);
    check_int("Akane 2 callback row 0 is item file type zero", 0,
              g_akane2Combo.weapon.bullets[0].type);
    check_int("Akane 2 row 0 is bound to primary magazine", 0,
              g_akane2Combo.weapon.bullets[0].magazine);
    check_bool("Akane 2 has no attachment-origin MoveProgram", true,
               gameplay::move_program(&g_akane2Combo.moves) == nullptr);
}

void test_shooting_magazine_contract() {
    section("31. Original magazine admission/refill (Rena 0 + item 1)");
    if (!g_testCombo.ready) return skip_case("Rena 0 magazine fixture");
    using gameplay::ShootingMagazine;
    const auto& definition = g_testCombo.weapon.magazines[0];
    ShootingMagazine stock = ShootingMagazine::from_definition(definition);
    check_int("Original stock starts at six rounds, not 1800 pool units", 6, stock.rounds);
    stock.reloadProgress = 7;
    check_bool("Full magazine admits its first callback", true, stock.consume());
    check_int("One callback consumes one round", 5, stock.rounds);
    check_int("First callback clears refill progress", 0, stock.reloadProgress);
    stock.reloadProgress = 17;
    check_bool("Zero-interval second callback in same tick is admitted", true, stock.consume());
    check_int("Non-full consumption retains refill progress", 17, stock.reloadProgress);
    for (std::uint32_t remaining = stock.rounds; remaining > 0; --remaining) stock.consume();
    check_int("Last callback clears refill progress", 0, stock.reloadProgress);
    stock.reloadProgress = 9;
    stock.cooldown = 2;
    check_bool("Empty stock rejects admission", false, stock.consume());
    check_int("Rejected admission retains refill progress", 9, stock.reloadProgress);
    check_int("Rejected admission retains cooldown", 2, stock.cooldown);

    stock = ShootingMagazine::from_definition(definition);
    stock.consume();
    for (int tick = 0; tick < definition.reloadTime - 1; ++tick) stock.tick();
    check_int("Mode 2 partial stock refills at threshold, not before", 5, stock.rounds);
    stock.tick();
    check_int("Mode 2 partial stock restores one round", 6, stock.rounds);
    for (std::uint32_t remaining = stock.rounds; remaining > 0; --remaining) stock.consume();
    for (int tick = 0; tick < definition.reloadTime * 3 - 1; ++tick) stock.tick();
    check_int("Mode 2 empty stock uses three-tick refill pulses", 0, stock.rounds);
    stock.tick();
    check_int("Mode 2 empty refill restores full capacity", 6, stock.rounds);
    check_bool("Empty refill sets recovered flag byte 0x100", true, (stock.flags & 0x100u) != 0);
    check_int("Empty refill retains progress in original display", 2100, stock.display);

    stock = ShootingMagazine::from_definition(definition);
    stock.shotInterval = 2;
    stock.cooldown = 1;
    check_bool("Interval rejects before its signed threshold", false, stock.consume());
    stock.tick();
    check_bool("Interval admits at its threshold", true, stock.consume());
    check_bool("Same-tick repeat cannot bypass a nonzero interval", false, stock.consume());
    stock.cooldown = 0xffffffffu;
    check_bool("Signed negative cooldown is rejected", false, stock.consume());

    for (unsigned mode : {0u, 1u}) {
        stock = ShootingMagazine::from_definition(definition);
        stock.mode = mode;
        for (std::uint32_t remaining = stock.rounds; remaining > 0; --remaining) stock.consume();
        for (int tick = 0; tick < definition.reloadTime; ++tick) stock.tick();
        check_int("Mode 0 refills full; mode 1 refills one round", mode == 0 ? 6 : 1, stock.rounds);
    }
    stock.flags = 0xabcd0101u;
    stock.initialHold = stock.laterHold = stock.chargeStage = 4;
    stock.tick();
    check_int("Charge flag preserves hold state for this tick", 4, stock.initialHold);
    check_bool("Tick consumes low flag byte", true, (stock.flags & 0xffu) == 0);
    stock.tick();
    check_int("Unheld tick clears initial hold", 0, stock.initialHold);
    check_int("Unheld tick clears later hold", 0, stock.laterHold);
    check_int("Unheld tick clears charge stage", 0, stock.chargeStage);
    stock.reloadProgress = 17;
    stock.cooldown = 2;
    stock.flags = 0xabcd0101u;
    stock.reset();
    check_int("Reset restores round capacity", 6, stock.rounds);
    check_int("Reset retains reload progress", 17, stock.reloadProgress);
    check_int("Reset retains cooldown", 2, stock.cooldown);
    check_bool("Reset clears only low flags word", true, stock.flags == 0xabcd0000u);
}

void test_satoko2_world_origin_fixture() {
    section("30. Satoko 2 item 38 twin world tap (bodies shoot_body_3_2_400/402)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_satoko2Combo.load(install, 3, 2))
        return skip_case("Satoko 2 combo");
    // FUN_00435450 supplies computed XYZ in all four audited bodies. A Prop1
    // program would lose the twin tap origins even though item 38 has no prop mesh.
    const auto& weapon = g_satoko2Combo.weapon;
    check_int("Satoko 2 NN.dat binds item 38", 38, g_satoko2Combo.moves.weapon_id());
    check_int("Satoko 2 fixture loads item 38", 38, weapon.id);
    check_int("Satoko 2 has fifteen registered bullet rows", 15, weapon.bulletCount);
    check_bool("Satoko 2 ships two empty attachment meshes", true,
               weapon.slotCount == 2 && weapon.slots[0].meshName.empty() &&
               weapon.slots[1].meshName.empty());
    const int rows[] = {0, 1, 4, 5};
    for (int row : rows) {
        check_int("Satoko 2 request operand has identity registration", row, weapon.bullets[row].type);
        check_bool("Satoko 2 request operand has a decoded bullet fixture", true,
                   g_satoko2Combo.hasBullet[static_cast<size_t>(row)]);
    }
    const auto* program = gameplay::move_program(&g_satoko2Combo.moves);
    check_bool("Satoko 2 tap program binds the typed world rules", true,
               program && program->rules == gameplay::kSatoko2Rules);
    check_int("Satoko 2 maps the normal grounded tap to state 400", 400,
              program ? program->shot[0][0] : -1);
    check_int("Satoko 2 maps the normal air tap to state 402", 402,
              program ? program->shot[0][1] : -1);
    check_int("Satoko 2 first charge stays pending (450/460 unmeasured here)", -1,
              program ? program->shot[1][0] : -2);
    check_int("Satoko 2 second charge stays pending", -1,
              program ? program->shot[2][0] : -2);

    // Normal tap: the twin at tick 20 is measured as forward 100, lateral -50/+50,
    // height +70 over the actor, aimed on the legacy heading basis. A fresh fighter
    // at the origin facing +Z with no opponent does not move or turn, so the two
    // worlds are exactly those offsets — and the attachment slots stay bound, which
    // is what distinguishes this from a Prop1 request.
    Fighter f;
    f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_satoko2Combo.bind(f);
    settle(f);
    Input in;
    in.set(fnd::input::Action::Shoot, true);
    tick(f, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(f, in);
    check_int("Satoko tap enters ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    check_int("Satoko tap binds state 400", 400, f.shot_move_id());
    for (int i = 0; i < 20; ++i) tick(f, in);
    const gameplay::PendingShot left = f.take_pending_shot();
    const gameplay::PendingShot right = f.take_pending_shot();
    check_bool("Satoko tap arms the twin request", true, left.armed && right.armed);
    check_int("normal twin uses item row 0", 0, left.bulletRow);
    check_int("normal twin second request also uses item row 0", 0, right.bulletRow);
    check_near("first twin sits 50 left of the heading", -50.f, left.pos.x, 1e-3f);
    check_near("second twin sits 50 right of the heading", 50.f, right.pos.x, 1e-3f);
    check_near("both twins sit 70 above the actor", 70.f, left.pos.y, 1e-3f);
    check_near("both twins sit 100 ahead of the actor", 100.f, left.pos.z, 1e-3f);
    check_bool("twin request is a world origin, not an attachment", true,
               left.origin.kind == gameplay::ShotOriginKind::ActorRelativeOffset);
    check_bool("twin request aims on the legacy heading basis", true,
               left.aim.kind == gameplay::ShotAimKind::ActorHeadingTargetElevation);
    check_bool("attachment slots stay bound through the tap", true,
               f.weapon_slot_bound(0) && f.weapon_slot_bound(1));
    check_bool("normal tap schedules exactly two requests", false,
               f.take_pending_shot().armed);

    // Powered branch: the gate is `byte(+0x845) && word(+0x848)` — the Oyashiro
    // special armed AND the aim-selection ally hold. A 1v1 fixture can never hold an
    // ally, so both halves are driven explicitly rather than through a live match.
    Fighter p;
    p.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_satoko2Combo.bind(p);
    settle(p);
    p.set_hypermode(Hypermode::Oyashiro);
    p.set_hyper_gauge(1.f);
    Input sp;
    sp.set(fnd::input::Action::Special, true);
    tick(p, sp);
    sp.set(fnd::input::Action::Special, false);
    tick(p, sp);
    check_bool("Oyashiro witness is active", true, p.hyper_active());
    check_bool("gate is closed without the ally hold", false, p.shoot_gate_powered());
    gameplay::ShootingContext context;
    context.aimHold = true;
    p.set_shooting_context(context);
    check_bool("gate opens with the ally hold", true, p.shoot_gate_powered());
    sp.set(fnd::input::Action::Shoot, true);
    tick(p, sp);
    sp.set(fnd::input::Action::Shoot, false);
    tick(p, sp);
    for (int i = 0; i < 20; ++i) tick(p, sp);
    const gameplay::PendingShot pl = p.take_pending_shot();
    const gameplay::PendingShot pr = p.take_pending_shot();
    check_bool("powered twin arms the request", true, pl.armed && pr.armed);
    check_int("powered twin switches to item row 1", 1, pl.bulletRow);
    check_int("powered twin second request also uses item row 1", 1, pr.bulletRow);
    check_bool("powered request keeps the measured lateral split", true,
               glm::dot(pl.pos - pr.pos, glm::vec3(1.f, 0.f, 0.f)) < 0.f);
}

void test_satoko2_powered_branch_live() {
    section("32. Satoko 2 powered branch in 1v1: the aim hold pins by default");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_satoko2Combo.load(install, 3, 2))
        return skip_case("Satoko 2 live match");
    // The fighter-level witness injects ShootingContext directly, which proves the gate
    // plumbing but not the producer. Here the hold is produced by Match's own aim-layer
    // maintenance from the recovered predicate: this fighter's aim target is the same
    // fighter player 0 is aiming at. At round start every aim is player 0
    // (FUN_00421670), so in 1v1 both holds pin on the first tick with NO gesture — the
    // powered branch is available by default, not team-play only. The control below
    // isolates the other half of the gate (the Oyashiro special).
    const xm::Model* models[4] = {&g_satoko2Combo.model, &g_satoko2Combo.model,
                                  &g_satoko2Combo.model, &g_satoko2Combo.model};
    xm::Controller* animations[4] = {g_satoko2Combo.controller(),
                                     g_satoko2Combo.controller(),
                                     g_satoko2Combo.controller(),
                                     g_satoko2Combo.controller()};

    // A shot program cannot re-enter while it is still playing (set_state returns
    // early for the same state), so each case gets its own match: settle, arm the
    // special, fire once, and read the request, the admission and the spawn separately.
    // Admission is observable because Satoko 2's rows 0 and 1 live in different
    // magazines (read from the item table, never hardcoded).
    struct VolleyOutcome {
        std::vector<int> rows;
        int mainSpent = -1;
        int chargeSpent = -1;
    };
    const int rowMagazine[2] = {g_satoko2Combo.weapon.bullets[0].magazine,
                                g_satoko2Combo.weapon.bullets[1].magazine};
    const auto firedVolley = [&](gameplay::Hypermode mode) {
        VolleyOutcome out;
        gameplay::MatchConfig cfg;
        cfg.fighterCount = 2;
        for (int i = 0; i < 2; ++i) {
            cfg.moves[i] = &g_satoko2Combo.moves;
            cfg.weapon[i] = &g_satoko2Combo.weapon;
            cfg.hyper[i] = mode;
            cfg.startGauge[i] = 1.0f;
        }
        gameplay::Match m;
        m.reset(cfg, models, animations, nullptr, nullptr);
        m.economy().setLogFile(nullptr);
        fnd::input::PlayerState idle{};
        for (int i = 0; i < 70; ++i) {
            fnd::input::compute_edges(idle);
            const fnd::input::PlayerState* none[4] = {nullptr, nullptr, nullptr, nullptr};
            m.step(none, gameplay::FixedStep::seconds);
        }
        // No lock gesture at all: the aims are still both player 0 from init.
        if (m.aim_selection(0) != 0 || m.aim_selection(1) != 0) return out;
        if (!m.aim_holds(0) || !m.aim_holds(1)) return out;
        fnd::input::PlayerState special{};
        special.down[fnd::input::Action::Special] = true;
        fnd::input::compute_edges(special);
        const fnd::input::PlayerState* specialInputs[4] = {&special, nullptr, nullptr,
                                                           nullptr};
        m.step(specialInputs, gameplay::FixedStep::seconds);
        for (bool& down : special.down) down = false;
        fnd::input::compute_edges(special);
        m.step(specialInputs, gameplay::FixedStep::seconds);
        const bool armed = m.fighter(0).hyper_active();
        const int mainBefore = m.fighter(0).main_whole();
        const int chargeBefore = m.fighter(0).charge_whole();
        fnd::input::PlayerState fire{};
        fire.down[fnd::input::Action::Shoot] = true;
        fnd::input::compute_edges(fire);
        const fnd::input::PlayerState* inputs[4] = {&fire, nullptr, nullptr, nullptr};
        m.step(inputs, gameplay::FixedStep::seconds);
        for (bool& down : fire.down) down = false;
        fnd::input::compute_edges(fire);
        // Count the SPAWN update, not every update a projectile survives: appending
        // each living projectile per update would let one twin satisfy a two-entry
        // assertion by living into the next tick. Both requests of a volley queue in
        // the same update and the scene drains them in the same step, so the spawn
        // update itself must carry both.
        bool spawned = false;
        for (int i = 0; i < 40 && !spawned; ++i) {
            m.step(inputs, gameplay::FixedStep::seconds);
            for (const auto& shot : m.shots().shots())
                if (shot.alive && shot.owner == &m.fighter(0)) {
                    spawned = true;
                    out.rows.push_back(shot.bulletRow);
                }
        }
        // Encode the arming outcome in the sentinel so a silent Special failure
        // cannot masquerade as a row assertion.
        if (!armed) {
            out.rows = std::vector<int>{-1};
            return out;
        }
        out.mainSpent = mainBefore - m.fighter(0).main_whole();
        out.chargeSpent = chargeBefore - m.fighter(0).charge_whole();
        return out;
    };

    const VolleyOutcome oyashiro = firedVolley(Hypermode::Oyashiro);
    check_int("1v1 Oyashiro tap fires the powered twin", 2, (int)oyashiro.rows.size());
    if (oyashiro.rows.size() == 2) {
        check_int("1v1 powered twin first row is 1", 1, oyashiro.rows[0]);
        check_int("1v1 powered twin second row is 1", 1, oyashiro.rows[1]);
    }
    if (rowMagazine[1] == 1) {
        check_int("powered twin spends two secondary rounds", 2, oyashiro.chargeSpent);
        check_int("powered twin leaves the primary stock alone", 0, oyashiro.mainSpent);
    } else if (rowMagazine[1] == 0) {
        // Item 38 bills both rows to the primary stock, so admission is identical and
        // only the spawned rows tell the branches apart. The spend is still asserted:
        // it proves the requests were admitted, not bypassed or dropped.
        check_int("powered twin spends two primary rounds", 2, oyashiro.mainSpent);
        check_int("powered twin leaves the secondary stock alone", 0, oyashiro.chargeSpent);
    }
    const VolleyOutcome friendship = firedVolley(Hypermode::Friendship);
    check_int("1v1 Friendship tap fires the normal twin", 2, (int)friendship.rows.size());
    if (friendship.rows.size() == 2) {
        check_int("1v1 normal twin first row is 0", 0, friendship.rows[0]);
        check_int("1v1 normal twin second row is 0", 0, friendship.rows[1]);
    }
    if (rowMagazine[0] == 0) {
        check_int("normal twin spends two primary rounds", 2, friendship.mainSpent);
        check_int("normal twin leaves the secondary stock alone", 0, friendship.chargeSpent);
    }
}

void test_satoko2_aim_shared_2v2() {
    section("34. Satoko 2 aim hold in 2v2: shared aims hold, different aims decay");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_satoko2Combo.load(install, 3, 2))
        return skip_case("Satoko 2 2v2 aim");
    // Sides {0,0,1,1}: blues 0/1 vs reds 2/3. Blues 0 and 1 both aim at red 2, so
    // fighter 1's aim matches player 0's and holds; red 3 aims at blue 0 while player
    // 0 aims at 2, so it decays. The combat locks follow the same gestures, but the
    // hold predicate never consults them — only the aim comparison feeds the gate.
    const xm::Model* models[4] = {&g_satoko2Combo.model, &g_satoko2Combo.model,
                                  &g_satoko2Combo.model, &g_satoko2Combo.model};
    xm::Controller* animations[4] = {g_satoko2Combo.controller(),
                                     g_satoko2Combo.controller(),
                                     g_satoko2Combo.controller(),
                                     g_satoko2Combo.controller()};
    gameplay::MatchConfig cfg;
    cfg.fighterCount = 4;
    cfg.side[0] = 0; cfg.side[1] = 0; cfg.side[2] = 1; cfg.side[3] = 1;
    for (int i = 0; i < 4; ++i) {
        cfg.moves[i] = &g_satoko2Combo.moves;
        cfg.weapon[i] = &g_satoko2Combo.weapon;
        cfg.hyper[i] = Hypermode::Oyashiro;
        cfg.startGauge[i] = 1.0f;
        cfg.spawn[i] = glm::vec3(i < 2 ? -1000.f : 1000.f, 0.f, (i % 2) * 500.f);
    }
    gameplay::Match m;
    m.reset(cfg, models, animations, nullptr, nullptr);
    m.economy().setLogFile(nullptr);
    fnd::input::PlayerState idle{};
    for (int i = 0; i < 70; ++i) {
        fnd::input::compute_edges(idle);
        const fnd::input::PlayerState* none[4] = {nullptr, nullptr, nullptr, nullptr};
        m.step(none, gameplay::FixedStep::seconds);
    }
    m.cycle_locked_target(0, true);
    m.cycle_locked_target(1, true);
    m.cycle_locked_target(3, true);
    check_int("player 0 aims at red 2", 2, m.aim_selection(0));
    check_int("blue 1 aims at the same red 2", 2, m.aim_selection(1));
    check_int("red 3 aims at blue 0 instead", 0, m.aim_selection(3));
    // The combat locks moved with the same gestures, which is the port's UX layer
    // doing its job; the projectile rows below are what prove the gate reads the aim.
    check_int("fighter 1 also locked red 2", 2, m.locked_target(1));
    for (int i = 0; i < 3; ++i) {
        fnd::input::compute_edges(idle);
        const fnd::input::PlayerState* none[4] = {nullptr, nullptr, nullptr, nullptr};
        m.step(none, gameplay::FixedStep::seconds);
    }
    check_bool("player 0 holds through its own selection", true, m.aim_holds(0));
    check_bool("the matching aim holds", true, m.aim_holds(1));
    check_bool("the mismatched aim is already decaying", true,
               m.aim_hold_ticks(3) < gameplay::kAllyHoldTicks &&
                   m.aim_hold_ticks(3) > 0);
    // Drain fighter 3's hold fully, then fire both: the holder takes the powered rows
    // while the diverter takes the normal ones, through the same scene drain.
    int guard = 0;
    while (m.aim_hold_ticks(3) > 0 && guard++ < 400) {
        fnd::input::compute_edges(idle);
        const fnd::input::PlayerState* none[4] = {nullptr, nullptr, nullptr, nullptr};
        m.step(none, gameplay::FixedStep::seconds);
    }
    check_int("the diverged hold drains to zero", 0, m.aim_hold_ticks(3));
    check_bool("the matching aim survives the whole drain", true, m.aim_holds(1));

    // Fire both through the same scene drain: the holder's twin is powered (row 1)
    // while the diverter's is normal (row 0). Separate matches are unnecessary here
    // because different fighters can each fire once.
    const auto fireOnce = [&](int fighter) {
        fnd::input::PlayerState special{};
        special.down[fnd::input::Action::Special] = true;
        fnd::input::compute_edges(special);
        const fnd::input::PlayerState* activate[4] = {nullptr, nullptr, nullptr, nullptr};
        activate[fighter] = &special;
        m.step(activate, gameplay::FixedStep::seconds);
        for (bool& down : special.down) down = false;
        fnd::input::compute_edges(special);
        m.step(activate, gameplay::FixedStep::seconds);
        if (!m.fighter(fighter).hyper_active()) return std::vector<int>{-1};
        fnd::input::PlayerState fire{};
        fire.down[fnd::input::Action::Shoot] = true;
        fnd::input::compute_edges(fire);
        const fnd::input::PlayerState* inputs[4] = {nullptr, nullptr, nullptr, nullptr};
        inputs[fighter] = &fire;
        m.step(inputs, gameplay::FixedStep::seconds);
        for (bool& down : fire.down) down = false;
        fnd::input::compute_edges(fire);
        std::vector<int> rows;
        bool spawned = false;
        for (int i = 0; i < 40 && !spawned; ++i) {
            m.step(inputs, gameplay::FixedStep::seconds);
            for (const auto& shot : m.shots().shots())
                if (shot.alive && shot.owner == &m.fighter(fighter)) {
                    spawned = true;
                    rows.push_back(shot.bulletRow);
                }
        }
        return rows;
    };
    const std::vector<int> holder = fireOnce(1);
    check_int("the matching fighter fires the powered twin", 2, (int)holder.size());
    if (holder.size() == 2) {
        check_int("shared-aim twin first row is 1", 1, holder[0]);
        check_int("shared-aim twin second row is 1", 1, holder[1]);
    }
    const std::vector<int> diverter = fireOnce(3);
    check_int("the diverged fighter fires the normal twin", 2, (int)diverter.size());
    if (diverter.size() == 2) {
        check_int("diverged twin first row is 0", 0, diverter[0]);
        check_int("diverged twin second row is 0", 0, diverter[1]);
    }
}

void test_keiichi0_hand_tap() {
    section("35. Keiichi 0 item 5 hand tap + charges (bodies shoot_body_2_0_*)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_keiichi0Combo.load(install, 2, 0))
        return skip_case("Keiichi 0 combo");
    // FUN_00435220 takes the Bip01_R_Hand matrix directly — not a prop muzzle, not the
    // root. Item 5's slots are bound (the body binds both), so a Prop1 request would
    // also succeed; the origin KIND below is what proves the hand path was taken.
    check_int("Keiichi 0 NN.dat binds item 5", 5, g_keiichi0Combo.moves.weapon_id());
    check_int("Keiichi 0 fixture loads item 5", 5, g_keiichi0Combo.weapon.id);
    const auto* program = gameplay::move_program(&g_keiichi0Combo.moves);
    check_bool("Keiichi 0 hand program is bound", true,
               program && program->rules == gameplay::kKeiichi0Rules);
    check_int("Keiichi 0 maps the tap to state 400", 400,
              program ? program->shot[0][0] : -1);
    check_int("Keiichi 0 maps the air tap to state 402", 402,
              program ? program->shot[0][1] : -1);
    check_int("Keiichi 0 maps the ground charge to state 450", 450,
              program ? program->shot[1][0] : -1);
    check_int("Keiichi 0 maps the air charge to state 460", 460,
              program ? program->shot[1][1] : -1);

    // Normal tap: one hand request at tick 13, row 0, from the posed right hand.
    Fighter f;
    f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_keiichi0Combo.bind(f);
    settle(f);
    Input in;
    in.set(fnd::input::Action::Shoot, true);
    tick(f, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(f, in);
    check_int("Keiichi tap enters ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    check_int("Keiichi tap binds state 400", 400, f.shot_move_id());
    for (int i = 0; i < 13; ++i) tick(f, in);
    const gameplay::PendingShot shot = f.take_pending_shot();
    check_bool("Keiichi tap arms exactly one request", true, shot.armed);
    check_int("normal tap uses item row 0", 0, shot.bulletRow);
    check_bool("tap request is a named-bone origin", true,
               shot.origin.kind == gameplay::ShotOriginKind::NamedBone);
    check_bool("tap request names the right hand", true,
               shot.origin.boneName != nullptr &&
                   std::string(shot.origin.boneName) == "Bip01_R_Hand");
    const float handOffset = std::hypot(shot.pos.x, shot.pos.y, shot.pos.z);
    check_bool("hand request leaves the actor root", true, handOffset > 20.f);
    check_bool("tap schedules no duplicate", false, f.take_pending_shot().armed);

    // The NamedBone path throws on a missing bone instead of substituting the root,
    // so the witness must show the lookup has something real to find — and that it
    // discriminates. (Driving the throw itself would need a rig-less fighter, but a
    // rig-less fighter never advances its animation tick, so that probe is vacuous;
    // the throw is a three-line explicit branch on this same lookup.)
    check_bool("rig contains the right-hand bone", true,
               g_keiichi0Combo.model.findFrame("Bip01_R_Hand") >= 0);
    check_bool("rig contains the left-hand bone", true,
               g_keiichi0Combo.model.findFrame("Bip01_L_Hand") >= 0);
    check_bool("bone lookup rejects a missing name", true,
               g_keiichi0Combo.model.findFrame("Bip01_NoSuchBone") < 0);

    // Powered tap: Oyashiro + aim hold switches the row to 3, same hand.
    Fighter p;
    p.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_keiichi0Combo.bind(p);
    settle(p);
    p.set_hypermode(Hypermode::Oyashiro);
    p.set_hyper_gauge(1.f);
    Input sp;
    sp.set(fnd::input::Action::Special, true);
    tick(p, sp);
    sp.set(fnd::input::Action::Special, false);
    tick(p, sp);
    check_bool("Oyashiro witness is active", true, p.hyper_active());
    gameplay::ShootingContext context;
    context.aimHold = true;
    p.set_shooting_context(context);
    check_bool("powered gate holds", true, p.shoot_gate_powered());
    sp.set(fnd::input::Action::Shoot, true);
    tick(p, sp);
    sp.set(fnd::input::Action::Shoot, false);
    tick(p, sp);
    for (int i = 0; i < 13; ++i) tick(p, sp);
    const gameplay::PendingShot powered = p.take_pending_shot();
    check_bool("powered tap arms the request", true, powered.armed);
    check_int("powered tap switches to item row 3", 3, powered.bulletRow);
    check_bool("powered tap keeps the right hand", true,
               powered.origin.kind == gameplay::ShotOriginKind::NamedBone &&
                   powered.origin.boneName != nullptr &&
                   std::string(powered.origin.boneName) == "Bip01_R_Hand");

    // Ground charge: left-hand row 1 at tick 4 (fixed angles), then the attachment
    // pair at tick 20 (rows 2 normal / 4 powered, stored pitch).
    Fighter g;
    g.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_keiichi0Combo.bind(g);
    settle(g);
    hold_yellow(g, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(g, in);
    check_int("Keiichi charge binds move 450", 450, g.shot_move_id());
    for (int i = 0; i < 4; ++i) tick(g, in);
    const gameplay::PendingShot left = g.take_pending_shot();
    check_bool("charge tick-4 left-hand request arms", true, left.armed);
    check_int("tick-4 uses item row 1", 1, left.bulletRow);
    check_bool("tick-4 names the left hand", true,
               left.origin.kind == gameplay::ShotOriginKind::NamedBone &&
                   left.origin.boneName != nullptr &&
                   std::string(left.origin.boneName) == "Bip01_L_Hand");
    for (int i = 0; i < 16; ++i) tick(g, in);
    const gameplay::PendingShot first = g.take_pending_shot();
    check_bool("charge tick-20 attachment request arms", true, first.armed);
    check_int("tick-20 normal row is 2", 2, first.bulletRow);
    check_bool("tick-20 uses the attachment origin", true,
               first.origin.kind == gameplay::ShotOriginKind::WeaponAttachment ||
                   first.origin.kind == gameplay::ShotOriginKind::BoundBoneFallback);
}

void test_keiichi1_hand_tap() {
    section("36. Keiichi 1 item 18 hand tap + world charges (bodies shoot_body_2_1_*)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_keiichi1Combo.load(install, 2, 1))
        return skip_case("Keiichi 1 combo");
    // Same tap shape as Keiichi 0 (hand R at tick 13) with powered row 1. The charges
    // differ: two world requests at tick 20 (row 9 plus row 2/3), both 50 left and
    // +40/+20 high, with the range-dependent pitch.
    check_int("Keiichi 1 NN.dat binds item 18", 18, g_keiichi1Combo.moves.weapon_id());
    check_int("Keiichi 1 fixture loads item 18", 18, g_keiichi1Combo.weapon.id);
    const auto* program = gameplay::move_program(&g_keiichi1Combo.moves);
    check_bool("Keiichi 1 hand program is bound", true,
               program && program->rules == gameplay::kKeiichi1Rules);
    check_int("Keiichi 1 maps the tap to state 400", 400,
              program ? program->shot[0][0] : -1);
    check_int("Keiichi 1 maps the air tap to state 402", 402,
              program ? program->shot[0][1] : -1);
    check_int("Keiichi 1 maps the ground charge to state 450", 450,
              program ? program->shot[1][0] : -1);
    check_int("Keiichi 1 maps the air charge to state 460", 460,
              program ? program->shot[1][1] : -1);

    Fighter f;
    f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_keiichi1Combo.bind(f);
    settle(f);
    Input in;
    in.set(fnd::input::Action::Shoot, true);
    tick(f, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(f, in);
    check_int("Keiichi tap enters ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    check_int("Keiichi tap binds state 400", 400, f.shot_move_id());
    for (int i = 0; i < 13; ++i) tick(f, in);
    const gameplay::PendingShot shot = f.take_pending_shot();
    check_bool("Keiichi tap arms exactly one request", true, shot.armed);
    check_int("normal tap uses item row 0", 0, shot.bulletRow);
    check_bool("tap request is a named-bone origin", true,
               shot.origin.kind == gameplay::ShotOriginKind::NamedBone);
    check_bool("tap request names the right hand", true,
               shot.origin.boneName != nullptr &&
                   std::string(shot.origin.boneName) == "Bip01_R_Hand");
    check_bool("tap schedules no duplicate", false, f.take_pending_shot().armed);

    // Powered tap switches to row 1; the air tap snaps rather than clamps, which the
    // row assertions below do not cover — the pitch section pins that separately.
    Fighter p;
    p.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_keiichi1Combo.bind(p);
    settle(p);
    p.set_hypermode(Hypermode::Oyashiro);
    p.set_hyper_gauge(1.f);
    Input sp;
    sp.set(fnd::input::Action::Special, true);
    tick(p, sp);
    sp.set(fnd::input::Action::Special, false);
    tick(p, sp);
    gameplay::ShootingContext context;
    context.aimHold = true;
    p.set_shooting_context(context);
    sp.set(fnd::input::Action::Shoot, true);
    tick(p, sp);
    sp.set(fnd::input::Action::Shoot, false);
    tick(p, sp);
    for (int i = 0; i < 13; ++i) tick(p, sp);
    const gameplay::PendingShot powered = p.take_pending_shot();
    check_bool("powered tap arms the request", true, powered.armed);
    check_int("powered tap switches to item row 1", 1, powered.bulletRow);

    // Ground charge: row 9 plus row 2 at tick 20, both 50 left and +40 high, with the
    // range pitch from the live target distance.
    Fighter g;
    g.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_keiichi1Combo.bind(g);
    settle(g);
    Fighter victim;
    victim.init(nullptr, nullptr, glm::vec3(0, 0, 500), 0.0f);
    g_keiichi1Combo.bind(victim);
    settle(victim);
    hold_yellow(g, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(g, in, &victim);
    check_int("Keiichi charge binds move 450", 450, g.shot_move_id());
    for (int i = 0; i < 20; ++i) tick(g, in, &victim);
    const gameplay::PendingShot first = g.take_pending_shot();
    const gameplay::PendingShot second = g.take_pending_shot();
    check_bool("charge tick-20 pair arms", true, first.armed && second.armed);
    check_int("unconditional request uses item row 9", 9, first.bulletRow);
    check_int("normal second request uses item row 2", 2, second.bulletRow);
    check_near("both sit 50 left of the heading", -50.f, first.pos.x, 1e-3f);
    check_near("both sit 40 above the actor", 40.f, first.pos.y, 1e-3f);
    check_near("both sit with no forward displacement", 0.f, first.pos.z, 1e-3f);
    // Base pitch atan2(0,500)=0 plus dist*40/5000 = 500*40/5000 = 4 degrees.
    check_near("range pitch adds the distance term", std::sin(glm::radians(4.f)),
               first.dir.y, 1e-3f);
}

void test_natsumi0_ground_tap() {
    section("29. Natsumi 0 state400 normal row 0 at 14F (bounded ground request schedule)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_natsumi0Combo.load(install, 15, 0))
        return skip_case("Natsumi 0 combo");
    const auto* program = gameplay::move_program(&g_natsumi0Combo.moves);
    check_bool("Natsumi 0 bounded program is bound to item 29", true,
               program && program->rules == gameplay::kNatsumi0Rules);
    check_int("Natsumi 0 uses item 29", 29, g_natsumi0Combo.weapon.id);
    check_int("Natsumi 0 program maps normal grounded tap to state 400", 400,
              program ? program->shot[0][0] : -1);
    check_int("Natsumi 0 does not yet claim air tap state 402", -1,
              program ? program->shot[0][1] : -2);

    Fighter fighter;
    fighter.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.f);
    g_natsumi0Combo.bind(fighter);
    settle(fighter);
    Input in;
    in.set(fnd::input::Action::Shoot, true);
    tick(fighter, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(fighter, in);
    check_int("Natsumi tap enters ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(fighter.state()));
    check_int("Natsumi tap binds state 400", 400, fighter.shot_move_id());
    check_bool("Natsumi tap begins with both attachment slots bound", true,
               fighter.weapon_slot_bound(0) && fighter.weapon_slot_bound(1));
    for (int i = 0; i < 14; ++i) tick(fighter, in);
    const gameplay::PendingShot shot = fighter.take_pending_shot();
    check_bool("Natsumi state400 schedules the tick-14 row-0 request", true, shot.armed);
    check_int("Natsumi normal tap selects item row 0", 0, shot.bulletRow);
    check_bool("Natsumi bounded request schedules no duplicate", false,
               fighter.take_pending_shot().armed);
    check_bool("Natsumi normal request clears both prop bindings", true,
               !fighter.weapon_slot_bound(0) && !fighter.weapon_slot_bound(1));
}

void test_rika0_twin_tick() {
    section("26. Rika 0 twin tick + twin salvos (bodies shoot_body_4_0_*)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_rika0Combo.load(install, 4, 0))
        return skip_case("Rika 0 combo");
    // Bundle evidence: Rika 0 (handler 0x484be0) fires twin rows 0 at tick 15 in the
    // ground tap (tag fires four — no flag field, skipped), and twin row-2 salvos at
    // ticks 15 AND 25 in both charges (pitch thirds 45/30 ground, 45/40 air), with
    // short freezes at tick 30 after the salvos (5 updates ground, 15 air).
    // Her program is kRika0Rules; the second charge stays provisional.
    Fighter f;
    f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_rika0Combo.bind(f);
    settle(f);
    Input in;
    in.set(fnd::input::Action::Shoot, true);
    tick(f, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(f, in);
    check_int("Rika0 tap enters ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    check_int("Rika0 tap binds move 400", 400, f.shot_move_id());
    for (int i = 0; i < 15; ++i) tick(f, in);
    gameplay::PendingShot first = f.take_pending_shot();
    gameplay::PendingShot second = f.take_pending_shot();
    check_bool("Rika0 tap T15 salvo fires twice", true, first.armed && second.armed);
    check_int("Rika0 T15 first row is 0", 0, first.bulletRow);
    check_int("Rika0 T15 second row is 0", 0, second.bulletRow);
    Fighter g;
    g.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_rika0Combo.bind(g);
    settle(g);
    hold_yellow(g, in);
    check_int("Rika0 hold reaches Yellow", static_cast<int>(ShotTier::Yellow),
              static_cast<int>(g.charge_tier()));
    in.set(fnd::input::Action::Shoot, false);
    tick(g, in);
    check_int("Rika0 charge enters ShootB", static_cast<int>(FighterState::ShootB),
              static_cast<int>(g.state()));
    check_int("Rika0 charge binds move 450", 450, g.shot_move_id());
    for (int i = 0; i < 15; ++i) tick(g, in);
    first = g.take_pending_shot();
    second = g.take_pending_shot();
    check_bool("Rika0 charge T15 salvo fires twice", true, first.armed && second.armed);
    check_int("Rika0 T15 rows are 2", 2, first.bulletRow);
    int guard = 0;
    while (g.phase_elapsed() < 25 && guard++ < 120) tick(g, in);
    tick(g, in);
    first = g.take_pending_shot();
    second = g.take_pending_shot();
    check_bool("Rika0 charge T25 salvo fires twice", true, first.armed && second.armed);
    check_int("Rika0 T25 rows are 2", 2, first.bulletRow);
}

void test_satoko_five_shot() {
    section("25. Satoko 0 five-shot tap + frozen twin salvos (bodies shoot_body_3_0_*)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_satokoCombo.load(install, 3, 0))
        return skip_case("Satoko 0 combo");
    // Bundle evidence: Satoko 0 (handler 0x4a9c40) fires FIVE row-0 shots at tick 17 in the
    // ground tap, EIGHT powered, each request drawing `draw%15` of pitch and
    // `(draw%240-120)*0.1` (`draw%300-150` powered) of lateral offset off the posed hand
    // (L12566-12636). Twin row-11 salvos spread by a 26-update frozen clock at tick 25 in
    // the first ground charge (four salvos at 25/31/37/43; the air charge freezes 21 for
    // four salvos at 25/31/37/43 — same rule shape, untested here like the other air
    // paths). Her program is kSatokoRules; the second charge stays provisional.
    Fighter f;
    f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_satokoCombo.bind(f);
    settle(f);
    Input in;
    in.set(fnd::input::Action::Shoot, true);
    tick(f, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(f, in);
    check_int("Satoko tap enters ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    check_int("Satoko tap binds move 400", 400, f.shot_move_id());
    for (int i = 0; i < 17; ++i) tick(f, in);
    int tapArmed = 0;
    bool tapRows = true, tapSlots = true, tapPitch = true;
    std::vector<glm::vec3> tapPositions;
    std::vector<float> tapPitches;
    for (int i = 0; i < 5; ++i) {
        gameplay::PendingShot shot = f.take_pending_shot();
        if (shot.armed) ++tapArmed;
        if (shot.bulletRow != 0) tapRows = false;
        if (shot.origin.attachmentSlot != 0) tapSlots = false;
        // pitch = clamped elevation (0 with no opponent) + draw%15, so [0, 15).
        const float deg = glm::degrees(std::asin(std::clamp(shot.dir.y, -1.f, 1.f)));
        if (deg < -0.1f || deg >= 15.f) tapPitch = false;
        tapPositions.push_back(shot.pos);
        tapPitches.push_back(deg);
    }
    check_int("Satoko tap T17 salvo fires five", 5, tapArmed);
    check_bool("Satoko salvo rows are all 0", true, tapRows);
    check_bool("Satoko salvo slot is the hand", true, tapSlots);
    check_bool("Satoko tap pitch stays inside the body's 0..15 band", true, tapPitch);
    // The fan: each request moves the hand origin by (draw%240-120)*0.1, so the five
    // positions differ from each other but stay inside 23.9 units of spread.
    bool fanSpread = false;
    float widest = 0.f;
    for (std::size_t i = 0; i < tapPositions.size(); ++i)
        for (std::size_t j = i + 1; j < tapPositions.size(); ++j) {
            const float d = glm::distance(tapPositions[i], tapPositions[j]);
            widest = std::max(widest, d);
            if (d > 0.01f) fanSpread = true;
        }
    check_bool("Satoko tap requests leave the hand at different offsets", true, fanSpread);
    check_bool("the lateral fan stays inside the body's 23.9-unit spread", true,
               widest <= 23.9f);
    // Exact arithmetic on the canonical stream, which pins the draw ORDER as well as the
    // values: residues 2, 2, 4, 5 give pitch1 = 2%15 = 2, lateral1 = (102-120)*0.1 = -1.8,
    // pitch2 = 3890346734%15 = 14 and lateral2 = (185-120)*0.1 = 6.5. Drawing the lateral
    // first would put r1 on the lateral and r2 on the pitch instead.
    if (tapPositions.size() == 5 && tapPitches.size() == 5) {
        check_near("Satoko tap first request pitches at draw 2 mod 15", 2.f, tapPitches[0],
                   0.05f);
        check_near("Satoko tap second request pitches at draw 3890346734 mod 15", 14.f,
                   tapPitches[1], 0.05f);
        check_near("Satoko tap offsets requests 1 and 2 by the 8.3 lateral delta", 8.3f,
                   glm::distance(tapPositions[0], tapPositions[1]), 0.15f);
    }
    check_bool("Satoko salvo fires exactly five", false,
               f.take_pending_shot().armed);

    // The powered branch widens the loop to eight and the lateral draw to 300 (29.9 units).
    Fighter h;
    h.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_satokoCombo.bind(h);
    settle(h);
    h.set_hypermode(Hypermode::Oyashiro);
    h.set_hyper_gauge(1.f);
    Input hp;
    hp.set(fnd::input::Action::Special, true);
    tick(h, hp);
    hp.set(fnd::input::Action::Special, false);
    tick(h, hp);
    gameplay::ShootingContext hyper;
    hyper.aimHold = true;
    h.set_shooting_context(hyper);
    hp.set(fnd::input::Action::Shoot, true);
    tick(h, hp);
    hp.set(fnd::input::Action::Shoot, false);
    tick(h, hp);
    for (int i = 0; i < 17; ++i) tick(h, hp);
    int poweredArmed = 0;
    bool poweredRows = true;
    float poweredWidest = 0.f;
    std::vector<glm::vec3> poweredPositions;
    for (int i = 0; i < 8; ++i) {
        gameplay::PendingShot shot = h.take_pending_shot();
        if (!shot.armed) continue;
        ++poweredArmed;
        if (shot.bulletRow != 0) poweredRows = false;
        poweredPositions.push_back(shot.pos);
    }
    for (std::size_t i = 0; i < poweredPositions.size(); ++i)
        for (std::size_t j = i + 1; j < poweredPositions.size(); ++j)
            poweredWidest = std::max(poweredWidest,
                                     glm::distance(poweredPositions[i], poweredPositions[j]));
    check_int("powered Satoko tap fires eight", 8, poweredArmed);
    check_bool("powered Satoko salvo keeps row 0", true, poweredRows);
    check_bool("the powered lateral fan stays inside 29.9 units", true,
               poweredWidest <= 29.9f);
    Fighter g;
    g.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_satokoCombo.bind(g);
    settle(g);
    hold_yellow(g, in);
    check_int("Satoko hold reaches Yellow", static_cast<int>(ShotTier::Yellow),
              static_cast<int>(g.charge_tier()));
    in.set(fnd::input::Action::Shoot, false);
    tick(g, in);
    check_int("Satoko charge enters ShootB", static_cast<int>(FighterState::ShootB),
              static_cast<int>(g.state()));
    check_int("Satoko charge binds move 450", 450, g.shot_move_id());
    // First salvo at tick 25, then the 26-update freeze, then tick 31: drive by
    // elapsed like the Keiichi/Mion-2 cases.
    int satokoGuard = 0;
    while (g.phase_elapsed() < 25 && satokoGuard++ < 150) tick(g, in);
    check_int("Satoko charge reaches tick 25", 25, g.phase_elapsed());
    tick(g, in);
    gameplay::PendingShot first = g.take_pending_shot();
    gameplay::PendingShot second = g.take_pending_shot();
    check_bool("Satoko charge T25 salvo fires twice", true, first.armed && second.armed);
    check_int("Satoko T25 first row is 11", 11, first.bulletRow);
    check_int("Satoko T25 second row is 11", 11, second.bulletRow);
    satokoGuard = 0;
    while (g.phase_elapsed() < 31 && satokoGuard++ < 150) tick(g, in);
    tick(g, in);
    first = g.take_pending_shot();
    second = g.take_pending_shot();
    check_bool("Satoko charge T31 salvo fires twice", true, first.armed && second.armed);
    check_int("Satoko T31 rows are 11", 11, first.bulletRow);
}

void test_mion2_single_shot() {
    section("23. Mion 2 single tap + burst charge (bodies shoot_body_1_2_*)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_mion2Combo.load(install, 1, 2))
        return skip_case("Mion 2 combo");
    // shoot_body_1_2_400 fires ONE slot-0 request at per-phase tick 10, rows 0/1, +-40
    // (the body force-writes its tick counter 10 -> 18, so ticks 11..17 never run and the
    // frame-18 anchor is that same single shot). The charge emits inside `if (phase == 1)`
    // on `tick > 14 && tick % 5 == 0 && counter < 10`, rows 2/3, +-45 — so the burst only
    // starts once phase 1 is reached, which is what this test now drives to.
    const auto* program = gameplay::move_program(&g_mion2Combo.moves);
    check_bool("Mion 2 program is bound", true,
               program && program->rules == gameplay::kMion2Rules);
    Fighter f;
    f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_mion2Combo.bind(f);
    settle(f);
    Input in;
    in.set(fnd::input::Action::Shoot, true);
    tick(f, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(f, in);
    check_int("Mion2 tap enters ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    check_int("Mion2 tap binds move 400", 400, f.shot_move_id());
    for (int i = 0; i < 10; ++i) tick(f, in);
    gameplay::PendingShot shot = f.take_pending_shot();
    check_bool("Mion2 tap launches at tick 10", true, shot.armed);
    check_int("Mion2 tap selects item row zero", 0, shot.bulletRow);
    check_int("Mion2 tap fires from attachment slot 0", 0, shot.origin.attachmentSlot);
    // Discriminating: the launch is a single request, so the jump destination at tick 18
    // must stay silent in the same activation.
    for (int i = 0; i < 8; ++i) tick(f, in);
    check_bool("Mion2 tap fires once (silent at tick 18)", false,
               f.take_pending_shot().armed);

    Fighter g;
    g.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_mion2Combo.bind(g);
    settle(g);
    hold_yellow(g, in);
    check_int("Mion2 hold reaches Yellow", static_cast<int>(ShotTier::Yellow),
              static_cast<int>(g.charge_tier()));
    in.set(fnd::input::Action::Shoot, false);
    tick(g, in);
    check_int("Mion2 charge enters ShootB", static_cast<int>(FighterState::ShootB),
              static_cast<int>(g.state()));
    check_int("Mion2 charge binds move 450", 450, g.shot_move_id());
    // The burst lives in phase 1, so nothing fires during the phase-0 wind-up.
    check_bool("Mion2 charge is silent in phase 0", false, g.take_pending_shot().armed);
    int guard = 0;
    gameplay::PendingShot burst{};
    while (!burst.armed && guard++ < 400) {
        tick(g, in);
        burst = g.take_pending_shot();
    }
    check_bool("Mion2 charge emits once phase 1 is reached", true, burst.armed);
    check_int("Mion2 burst runs in phase 1", 1, g.move_phase());
    check_int("Mion2 charge selects item row two", 2, burst.bulletRow);
    check_int("Mion2 burst emits from attachment slot 0", 0,
              burst.origin.attachmentSlot);
    // Cadence: the next emission is five ticks later in the same phase.
    const int firstEmit = g.phase_elapsed();
    guard = 0;
    gameplay::PendingShot repeat{};
    while (!repeat.armed && guard++ < 40) {
        tick(g, in);
        repeat = g.take_pending_shot();
    }
    check_bool("Mion2 burst repeats", true, repeat.armed);
    check_int("Mion2 repeat selects item row two", 2, repeat.bulletRow);
    check_int("Mion2 repeat sits five ticks after the first", 5,
              g.phase_elapsed() - firstEmit);
}

void test_irie_twin_tap() {
    section("22. Irie 1 twin tap + single charge (bodies shoot_body_10_1_*)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_irieCombo.load(install, 10, 1))
        return skip_case("Irie 1 combo");
    // Bundle evidence: Irie 1 (handler 0x57f600) fires twin rows 0+1 at tick 12 in
    // the ground tap (tag adds rows 2+3 — no flag field, skipped), and a single row-4
    // salvo at tick 22 in the first ground charge (tick 17 air charge — same rule
    // shape, untested here like the other air paths).
    // Her program is kIrieRules; the second charge stays provisional.
    Fighter f;
    f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_irieCombo.bind(f);
    settle(f);
    Input in;
    in.set(fnd::input::Action::Shoot, true);
    tick(f, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(f, in);
    check_int("Irie tap enters ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    check_int("Irie tap binds move 400", 400, f.shot_move_id());
    for (int i = 0; i < 12; ++i) tick(f, in);
    gameplay::PendingShot first = f.take_pending_shot();
    gameplay::PendingShot second = f.take_pending_shot();
    check_bool("Irie tap T12 salvo fires twice", true, first.armed && second.armed);
    check_int("Irie T12 first row is 0", 0, first.bulletRow);
    check_int("Irie T12 second row is 1", 1, second.bulletRow);
    Fighter g;
    g.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_irieCombo.bind(g);
    settle(g);
    hold_yellow(g, in);
    check_int("Irie hold reaches Yellow", static_cast<int>(ShotTier::Yellow),
              static_cast<int>(g.charge_tier()));
    in.set(fnd::input::Action::Shoot, false);
    tick(g, in);
    check_int("Irie charge enters ShootB", static_cast<int>(FighterState::ShootB),
              static_cast<int>(g.state()));
    check_int("Irie charge binds move 450", 450, g.shot_move_id());
    for (int i = 0; i < 22; ++i) tick(g, in);
    gameplay::PendingShot shot = g.take_pending_shot();
    check_bool("Irie charge launches at tick 22", true, shot.armed);
    check_int("Irie charge selects item row four", 4, shot.bulletRow);
}

void test_kasai_twin_burst() {
    section("22. Kasai 1 twin burst + fan charge (bodies shoot_body_12_1_*)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_kasaiCombo.load(install, 12, 1))
        return skip_case("Kasai 1 combo");
    // Bundle evidence: Kasai 1 (handler 0x5b9680) fires twin rows 2+0 at ticks 10
    // and 15 in the ground tap (base burst count 2; extended bursts need runtime
    // burst state — documented gap), and a fan of four row-4 shots at tick 18 in
    // the first ground charge (fan offsets share one trajectory here).
    // Her program is kKasaiRules; the second charge stays provisional.
    Fighter f;
    f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_kasaiCombo.bind(f);
    settle(f);
    Input in;
    in.set(fnd::input::Action::Shoot, true);
    tick(f, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(f, in);
    check_int("Kasai tap enters ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    check_int("Kasai tap binds move 400", 400, f.shot_move_id());
    for (int i = 0; i < 10; ++i) tick(f, in);
    gameplay::PendingShot first = f.take_pending_shot();
    gameplay::PendingShot second = f.take_pending_shot();
    check_bool("Kasai tap T10 salvo fires twice", true, first.armed && second.armed);
    check_int("Kasai T10 first row is 2", 2, first.bulletRow);
    check_int("Kasai T10 second row is 0", 0, second.bulletRow);
    for (int i = 0; i < 5; ++i) tick(f, in);
    first = f.take_pending_shot();
    second = f.take_pending_shot();
    check_bool("Kasai tap T15 salvo fires twice", true, first.armed && second.armed);
    check_int("Kasai T15 first row is 2", 2, first.bulletRow);
    check_int("Kasai T15 second row is 0", 0, second.bulletRow);
    Fighter g;
    g.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_kasaiCombo.bind(g);
    settle(g);
    hold_yellow(g, in);
    check_int("Kasai hold reaches Yellow", static_cast<int>(ShotTier::Yellow),
              static_cast<int>(g.charge_tier()));
    in.set(fnd::input::Action::Shoot, false);
    tick(g, in);
    check_int("Kasai charge enters ShootB", static_cast<int>(FighterState::ShootB),
              static_cast<int>(g.state()));
    check_int("Kasai charge binds move 450", 450, g.shot_move_id());
    for (int i = 0; i < 18; ++i) tick(g, in);
    int fanArmed = 0;
    bool fanRows = true;
    for (int i = 0; i < 4; ++i) {
        gameplay::PendingShot shot = g.take_pending_shot();
        if (shot.armed) ++fanArmed;
        if (shot.bulletRow != 4) fanRows = false;
    }
    check_int("Kasai charge T18 fan fires four", 4, fanArmed);
    check_bool("Kasai fan rows are all 4", true, fanRows);
}

void test_takano_triple_tap() {
    section("23. Takano 0 triple tap + single charge (bodies shoot_body_7_0_*)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_takanoCombo.load(install, 7, 0))
        return skip_case("Takano 0 combo");
    // Bundle evidence: Takano 0 (handler 0x531ce0) fires item row 0 at ticks 12, 15
    // and 18 in the ground tap (three single shots, not a repeating window), and item
    // row 1 once at tick 18 in the first ground charge (tick 17 in the air charge —
    // same rule shape, untested here like the other air paths).
    // Her program is kTakanoRules; the second charge stays provisional.
    Fighter f;
    f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_takanoCombo.bind(f);
    settle(f);
    Input in;
    in.set(fnd::input::Action::Shoot, true);
    tick(f, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(f, in);
    check_int("Takano tap enters ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    check_int("Takano tap binds move 400", 400, f.shot_move_id());
    for (int i = 0; i < 12; ++i) tick(f, in);
    gameplay::PendingShot shot = f.take_pending_shot();
    check_bool("Takano tap launches at tick 12", true, shot.armed);
    check_int("Takano tap selects item row zero", 0, shot.bulletRow);
    tick(f, in);
    tick(f, in);
    tick(f, in);
    shot = f.take_pending_shot();
    check_bool("Takano tap launches again at tick 15", true, shot.armed);
    check_int("Takano repeat selects item row zero", 0, shot.bulletRow);
    Fighter g;
    g.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_takanoCombo.bind(g);
    settle(g);
    hold_yellow(g, in);
    check_int("Takano hold reaches Yellow", static_cast<int>(ShotTier::Yellow),
              static_cast<int>(g.charge_tier()));
    in.set(fnd::input::Action::Shoot, false);
    tick(g, in);
    check_int("Takano charge enters ShootB", static_cast<int>(FighterState::ShootB),
              static_cast<int>(g.state()));
    check_int("Takano charge binds move 450", 450, g.shot_move_id());
    for (int i = 0; i < 18; ++i) tick(g, in);
    shot = g.take_pending_shot();
    check_bool("Takano charge launches at tick 18", true, shot.armed);
    check_int("Takano charge selects item row one", 1, shot.bulletRow);
}

void test_keiichi_dense_tap() {
    section("19. Keiichi 2 dense tap + single charge (bodies shoot_body_2_2_*)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_keiichiCombo.load(install, 2, 2))
        return skip_case("Keiichi 2 combo");
    // Bundle evidence: Keiichi 2 (handler 0x47b940) fires item row 0 on EVERY tick
    // 10..20 in the ground tap (shoot_body_2_2_400, 11 consecutive frames — the dense
    // burst shape), and item row 2 once at tick 13 in the first ground charge after
    // clock-rewind stalls at ticks 5 (+10f) and 32 (+15f) (shoot_body_2_2_450).
    // Her program is kKeiichiRules; the second charge stays provisional.
    Fighter f;
    f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_keiichiCombo.bind(f);
    settle(f);
    Input in;
    in.set(fnd::input::Action::Shoot, true);
    tick(f, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(f, in);
    check_int("Keiichi tap enters ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    check_int("Keiichi tap binds move 400", 400, f.shot_move_id());
    for (int i = 0; i < 10; ++i) tick(f, in);
    gameplay::PendingShot shot = f.take_pending_shot();
    check_bool("Keiichi tap launches at tick 10", true, shot.armed);
    check_int("Keiichi tap selects item row zero", 0, shot.bulletRow);
    // Dense, not anchored: the very next tick fires again.
    tick(f, in);
    shot = f.take_pending_shot();
    check_bool("Keiichi tap launches again at tick 11", true, shot.armed);
    check_int("Keiichi repeat selects item row zero", 0, shot.bulletRow);
    Fighter g;
    g.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_keiichiCombo.bind(g);
    settle(g);
    hold_yellow(g, in);
    check_int("Keiichi hold reaches Yellow", static_cast<int>(ShotTier::Yellow),
              static_cast<int>(g.charge_tier()));
    in.set(fnd::input::Action::Shoot, false);
    tick(g, in);
    check_int("Keiichi charge enters ShootB", static_cast<int>(FighterState::ShootB),
              static_cast<int>(g.state()));
    check_int("Keiichi charge binds move 450", 450, g.shot_move_id());
    check_bool("Keiichi 450 row present in table", true,
               g_keiichiCombo.moves.first_set_index(450) >= 0);
    // The tick-5 rewind stalls the move clock ~10 ticks: after 13 updates the move
    // has NOT reached tick 13 yet (elapsed < 13) and nothing launched.
    for (int i = 0; i < 13; ++i) tick(g, in);
    check_bool("Keiichi charge stalled before tick 13", true, g.phase_elapsed() < 13);
    check_bool("nothing launched during the stall", false,
               g.take_pending_shot().armed);
    int guard = 0;
    while (g.phase_elapsed() < 13 && guard++ < 80) tick(g, in);
    check_int("Keiichi charge reaches tick 13", 13, g.phase_elapsed());
    check_int("Keiichi still in ShootB at tick 13", static_cast<int>(FighterState::ShootB),
              static_cast<int>(g.state()));
    check_int("Keiichi shot row still 450 at tick 13", 450, g.shot_move_id());
    // One more update: the loop exits right after the tick that SET elapsed to 13,
    // whose rule pass still saw 12 — the tick-13 rules only run on the next update.
    tick(g, in);
    shot = g.take_pending_shot();
    check_bool("Keiichi charge launches at tick 13", true, shot.armed);
    check_int("Keiichi charge selects item row two", 2, shot.bulletRow);
}

void test_rika_shot_jump_cancel() {
    section("20. Rika 1 shot jump-cancel (bundle TSV, frame 25)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_rikaCombo.load(install, 4, 1))
        return skip_case("Rika 1 combo");
    // Second row of kShotJumpCancel: Rika 1 admits jump out of shot move 400 at
    // elapsed frame 25 into state 40 (TSV (0,25,256) → 40, runtime == expected).
    Fighter f;
    f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_rikaCombo.bind(f);
    settle(f);
    Input in;
    in.set(fnd::input::Action::Shoot, true);
    tick(f, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(f, in);
    check_int("Rika tap enters ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    int guard = 0;
    while (f.state() == FighterState::ShootA && f.phase_elapsed() < 24 && guard++ < 100)
        tick(f, in);
    check_int("Rika shot move still held at elapsed 24", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    in.set(fnd::input::Action::Jump, true);
    tick(f, in);
    check_int("Rika jump at elapsed 24 stays ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    in.set(fnd::input::Action::Jump, false);
    tick(f, in);
    guard = 0;
    while (f.state() == FighterState::ShootA && f.phase_elapsed() < 25 && guard++ < 100)
        tick(f, in);
    in.set(fnd::input::Action::Jump, true);
    tick(f, in);
    check_int("Rika jump at elapsed 25 leaves for Jump", static_cast<int>(FighterState::Jump),
              static_cast<int>(f.state()));
    in.set(fnd::input::Action::Jump, false);
}

void test_mion_slots_and_gates() {
    section("38. Mion 0 slots, powered rows and counter volleys (handler 0x4582a0)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_mionCombo.load(install, 1, 0))
        return skip_case("Mion 0 combo");
    // The powered gate switches the ROW only, never the slot: rows 0/4 on the taps and
    // 2/3 on the charges, all from FUN_00435000. Phase 3 (Mion 0's 400) and phase 2
    // (Mion 1's 400) fire slot 1, and only while the move has connected.

    // Powered ground tap: same phase-1 tick-2 window, row 4 instead of 0.
    Fighter p;
    p.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_mionCombo.bind(p);
    settle(p);
    p.set_hypermode(Hypermode::Oyashiro);
    p.set_hyper_gauge(1.f);
    Input sp;
    sp.set(fnd::input::Action::Special, true);
    tick(p, sp);
    sp.set(fnd::input::Action::Special, false);
    tick(p, sp);
    gameplay::ShootingContext context;
    context.aimHold = true;
    p.set_shooting_context(context);
    sp.set(fnd::input::Action::Shoot, true);
    tick(p, sp);
    sp.set(fnd::input::Action::Shoot, false);
    tick(p, sp);
    int guard = 0;
    gameplay::PendingShot powered{};
    while (!powered.armed && guard++ < 40) {
        tick(p, sp);
        powered = p.take_pending_shot();
    }
    check_bool("powered tap fires", true, powered.armed);
    check_int("powered tap switches to item row 4", 4, powered.bulletRow);
    check_int("powered tap keeps attachment slot 0", 0, powered.origin.attachmentSlot);

    // Air tap: three counter volleys, each firing BOTH slots with the same row.
    Fighter a;
    a.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_mionCombo.bind(a);
    settle(a);
    Input in;
    in.set(fnd::input::Action::Jump, true);
    tick(a, in);
    in.set(fnd::input::Action::Shoot, true);
    tick(a, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(a, in);
    check_int("air tap binds move 402", 402, a.shot_move_id());
    std::vector<int> rows;
    std::vector<int> slots;
    for (int i = 0; i < 40; ++i) {
        tick(a, in);
        for (gameplay::PendingShot s = a.take_pending_shot(); s.armed;
             s = a.take_pending_shot()) {
            rows.push_back(s.bulletRow);
            slots.push_back(s.origin.attachmentSlot);
        }
    }
    check_int("air tap fires the three dual-slot volleys", 6, (int)rows.size());
    bool allRowZero = !rows.empty();
    for (int r : rows) allRowZero &= (r == 0);
    check_bool("every air-tap volley uses row 0", true, allRowZero);
    int slot0 = 0, slot1 = 0;
    for (int sl : slots) (sl == 0 ? slot0 : slot1)++;
    check_int("air tap fires attachment slot 0 three times", 3, slot0);
    check_int("air tap fires attachment slot 1 three times", 3, slot1);

    // Ground charge: rows 2/3 and an ASYMMETRIC clamp (-40 low, +45 high). A target
    // parked far above drives the raw elevation past both ends.
    Fighter c;
    c.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_mionCombo.bind(c);
    settle(c);
    Fighter high;
    high.init(nullptr, nullptr, glm::vec3(0, 4000, 0), 0.0f);
    g_mionCombo.bind(high);
    settle(high);
    hold_yellow(c, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(c, in, &high);
    check_int("charge binds move 450", 450, c.shot_move_id());
    for (int i = 0; i < 17; ++i) tick(c, in, &high);
    const gameplay::PendingShot up = c.take_pending_shot();
    check_bool("charge fires against a high target", true, up.armed);
    check_int("charge uses item row 2", 2, up.bulletRow);
    // +45 degrees is the body's high bound; a symmetric +-40 clamp would stop at 40.
    check_near("high bound is the body's +45, not +40",
               std::sin(glm::radians(45.f)), up.dir.y, 2e-3f);

    // Powered charge row 3.
    Fighter pc;
    pc.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_mionCombo.bind(pc);
    settle(pc);
    pc.set_hypermode(Hypermode::Oyashiro);
    pc.set_hyper_gauge(1.f);
    sp.set(fnd::input::Action::Special, true);
    tick(pc, sp);
    sp.set(fnd::input::Action::Special, false);
    tick(pc, sp);
    pc.set_shooting_context(context);
    hold_yellow(pc, sp);
    sp.set(fnd::input::Action::Shoot, false);
    tick(pc, sp);
    for (int i = 0; i < 17; ++i) tick(pc, sp);
    const gameplay::PendingShot pcShot = pc.take_pending_shot();
    check_bool("powered charge fires", true, pcShot.armed);
    check_int("powered charge switches to item row 3", 3, pcShot.bulletRow);
}

void test_mion_slot1_contact_follow_up() {
    section("39. Mion slot-1 follow-up needs contact (bodies 1_0_400 phase 3, 1_1_400 phase 2)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_mionCombo.load(install, 1, 0))
        return skip_case("Mion 0 combo");
    // Both combos gate the slot-1 follow-up on `0 < w[0x1b7]` — the port's contact flag.
    // Without a connect the second fire must not happen; with one it must change slots.
    Input in;
    Fighter quiet;
    quiet.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_mionCombo.bind(quiet);
    settle(quiet);
    in.set(fnd::input::Action::Shoot, true);
    tick(quiet, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(quiet, in);
    int quietSlot1 = 0;
    for (int i = 0; i < 60; ++i) {
        tick(quiet, in);
        for (gameplay::PendingShot s = quiet.take_pending_shot(); s.armed;
             s = quiet.take_pending_shot())
            if (s.origin.attachmentSlot == 1) ++quietSlot1;
    }
    check_int("no slot-1 request without contact", 0, quietSlot1);

    Fighter struck;
    struck.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_mionCombo.bind(struck);
    settle(struck);
    struck.note_melee_hit(1);
    in.set(fnd::input::Action::Shoot, true);
    tick(struck, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(struck, in);
    int struckSlot1 = 0;
    int struckRows = 0;
    for (int i = 0; i < 60; ++i) {
        tick(struck, in);
        for (gameplay::PendingShot s = struck.take_pending_shot(); s.armed;
             s = struck.take_pending_shot()) {
            if (s.origin.attachmentSlot == 1) { ++struckSlot1; struckRows = s.bulletRow; }
        }
    }
    check_bool("a connected move fires the slot-1 follow-up", true, struckSlot1 > 0);
    check_int("slot-1 follow-up uses row 0 normally", 0, struckRows);
}

void test_mion_shot_tap() {
    section("16. Mion 0 tap + first charge (bundle bodies shoot_body_1_0_*)");
    const auto install = findInstall(nullptr);
    if (install.empty() || !g_mionCombo.load(install, 1, 0))
        return skip_case("Mion 0 combo");
    // shoot_body_1_0_400 fires in PHASE 1 at per-phase tick 2, slot 0, rows 0/4, with
    // the pitch scratch clamped +-40. The pre-slice program fired at elapsed tick 2 in
    // ANY phase, which is phase 0 in practice — a different frame. The charge
    // (shoot_body_1_0_450) fires rows 2/3 at tick 17, not row 0.
    const auto* program = gameplay::move_program(&g_mionCombo.moves);
    check_bool("Mion 0 program is bound", true,
               program && program->rules == gameplay::kMionRules);
    Fighter f;
    f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_mionCombo.bind(f);
    settle(f);
    Input in;
    in.set(fnd::input::Action::Shoot, true);
    tick(f, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(f, in);
    check_int("Mion tap enters ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    check_int("Mion tap binds move 400", 400, f.shot_move_id());
    // The tap must NOT fire during phase 0 — that was the old rule's bug.
    check_bool("Mion tap fires nothing in phase 0", false, f.take_pending_shot().armed);
    int guard = 0;
    gameplay::PendingShot shot;
    while (!shot.armed && f.state() == FighterState::ShootA && guard++ < 40) {
        tick(f, in);
        shot = f.take_pending_shot();
    }
    check_bool("Mion tap fires in phase 1", true, shot.armed);
    check_int("Mion tap fires at phase-1 tick 2", 1, f.move_phase());
    check_int("Mion tap selects item row 0", 0, shot.bulletRow);

    // First charge: hold past yellow, release, binds 450. Fires at tick 17, row 2.
    Fighter g;
    g.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    g_mionCombo.bind(g);
    settle(g);
    hold_yellow(g, in);
    check_int("Mion hold reaches Yellow", static_cast<int>(ShotTier::Yellow),
              static_cast<int>(g.charge_tier()));
    in.set(fnd::input::Action::Shoot, false);
    tick(g, in);
    check_int("Mion charge enters ShootB", static_cast<int>(FighterState::ShootB),
              static_cast<int>(g.state()));
    check_int("Mion charge binds move 450", 450, g.shot_move_id());
    for (int i = 0; i < 17; ++i) tick(g, in);
    shot = g.take_pending_shot();
    check_bool("Mion charge launches at tick 17", true, shot.armed);
    check_int("Mion charge selects item row 2", 2, shot.bulletRow);
    check_bool("Mion charge fires a single request", false, g.take_pending_shot().armed);
}

void test_pilot_shot_jump_cancel() {
    section("15. pilot Rena 0 shot jump-cancel (bundle TSV, frame 20)");
    if (!g_testCombo.ready) return skip_case("Rena 0 shot jump-cancel");
    // Bundle evidence (porting-support evidence TSVs, runtime == expected): Rena 0
    // admits jump out of shot move 400 at (phase 0, frame 20, flags 0x100) into state
    // 40, and frame 0 has no request. The table is kPilotShotJumpCancel (move_behavior.h),
    // admitted only for the pilot handler 0x43ffc0 — every other combo keeps today's
    // never-admitted mid-shot behavior, so this case also guards that non-regression.
    Fighter f = make_idle_fighter(glm::vec3(0, 0, 0));
    Input in;
    // Fire a tap: hold one frame, release the next — binds move 400 (ShootA).
    in.set(fnd::input::Action::Shoot, true);
    tick(f, in);
    in.set(fnd::input::Action::Shoot, false);
    tick(f, in);
    check_int("tap enters ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    check_int("tap binds move 400", 400, f.shot_move_id());
    // A jump press on the firing move (elapsed 0/1) is ignored: no request there.
    in.set(fnd::input::Action::Jump, true);
    tick(f, in);
    check_int("jump at elapsed <2 stays ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    in.set(fnd::input::Action::Jump, false);
    tick(f, in);
    // Drive to elapsed 19: still denied (the sampled request is frame 20).
    int guard = 0;
    while (f.state() == FighterState::ShootA && f.phase_elapsed() < 19 && guard++ < 80)
        tick(f, in);
    check_int("shot move still held at elapsed 19", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    check_int("elapsed reached 19", 19, f.phase_elapsed());
    in.set(fnd::input::Action::Jump, true);
    tick(f, in);
    check_int("jump at elapsed 19 stays ShootA", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    in.set(fnd::input::Action::Jump, false);
    tick(f, in);
    // Drive to elapsed 20: admitted — the fighter leaves for the jump chain.
    guard = 0;
    while (f.state() == FighterState::ShootA && f.phase_elapsed() < 20 && guard++ < 80)
        tick(f, in);
    check_int("shot move still held at elapsed 20", static_cast<int>(FighterState::ShootA),
              static_cast<int>(f.state()));
    in.set(fnd::input::Action::Jump, true);
    tick(f, in);
    check_int("jump at elapsed 20 leaves for Jump", static_cast<int>(FighterState::Jump),
              static_cast<int>(f.state()));
    in.set(fnd::input::Action::Jump, false);
}

void test_determinism() {
    section("14. determinism: same 600-frame script twice");
    if (!g_testCombo.ready) return skip_case("Rena 0 deterministic combat trace");
    std::vector<unsigned char> t1;
    std::vector<unsigned char> t2;
    run_script(t1);
    run_script(t2);
    check_int("trace 2 byte count matches trace 1",
              static_cast<long long>(t1.size()), static_cast<long long>(t2.size()));
    check_bool("traces are byte-identical", true, t1 == t2);
    check_u32("trace 2 FNV-1a matches trace 1", fnv1a(t1), fnv1a(t2));
    check_bool("trace is non-trivial (> 5000 bytes)", true, t1.size() > 5000);
    std::printf("  trace: %zu bytes, fnv1a 0x%08x\n", t1.size(), fnv1a(t1));
}

}  // namespace

int main(int argc, char** argv) {
    std::printf("fighter_script_test — ported fighter + projectile gameplay\n");
    std::printf("dt = 1/60 s (double %.17g, float step %.9g)\n", kDt,
                static_cast<double>(kStep));
    const auto install = findInstall(argc > 0 ? argv[0] : nullptr);
    if (!install.empty() && g_testCombo.load(install))
        std::printf("combat fixture: Rena 0 + item %d\n", g_testCombo.weapon.id);
    else
        std::printf("combat fixture unavailable; combo-dependent cases will skip\n");

    test_idle_walk();
    test_dash();
    test_attacks();
    test_hit_stun();
    test_guard_drain();
    test_air();
    test_shots();
    test_pilot_shot_jump_cancel();
    test_mion_shot_tap();
    test_mion_slots_and_gates();
    test_mion_slot1_contact_follow_up();
    test_rika_repeating_tap();
    test_rika_pitch_latch();
    test_rika_air_powered_charge();
    test_tomitake_twin_tap();
    test_keiichi_dense_tap();
    test_rika_shot_jump_cancel();
    test_chie_scratch_burst();
    test_kasai_twin_burst();
    test_takano_triple_tap();
    test_irie_twin_tap();
    test_mion2_single_shot();
    test_rika2_single_tick();
    test_satoko_five_shot();
    test_rika0_twin_tick();
    test_rena1_normal_schedule();
    test_keiichi2_tap_sweep();
    test_satoko1_periodic_world_shot();
    test_simulation_rng_stream();
    test_spread_draw_order();
    test_rena2_ring();
    test_rena0_powered_branches();
    test_akane2_world_origin_gap();
    test_natsumi0_ground_tap();
    test_satoko2_world_origin_fixture();
    test_satoko2_powered_branch_live();
    test_satoko2_aim_shared_2v2();
    test_keiichi0_hand_tap();
    test_keiichi1_hand_tap();
    test_shooting_magazine_contract();
    test_ammo();
    test_hypermode();
    test_ko();
    test_facing();
    test_anim_binding();
    test_projectile_pool();
    test_determinism();

    std::printf("\n%d checks, %d failed, %d skipped\n", g_checks, g_fails, g_skipped);
    std::printf("FIGHTER_SCRIPT: %s\n", g_fails == 0 ? "ok" : "FAIL");
    return g_fails == 0 ? 0 : 1;
}
