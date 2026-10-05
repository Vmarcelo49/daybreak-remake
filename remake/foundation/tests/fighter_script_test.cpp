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
//    g++ -std=c++20 -Wall -Wextra -I remake/foundation/src
//        -I remake/foundation/third_party/glm
//        remake/foundation/src/gameplay/fighter.cpp
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

#define XMODEL_IMPLEMENTATION   // this TU compiles the asset layer (as raycast_analytic does)

#include "assets/xmodel.h"

#include "gameplay/fighter.h"
#include "gameplay/fixed_step.h"
#include "gameplay/projectile.h"
#include "physics/raycast.h"

// Colour-layout cross-check only: DEBUG_PRIMS_GEOMETRY_ONLY keeps webgpu.h and
// gpu/gpu.h out of this TU (render/debug_prims.h:40-47), so the renderer's
// colour type can be compared with gameplay::Rgb without a device.
#define DEBUG_PRIMS_GEOMETRY_ONLY
#include "render/debug_prims.h"

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
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

// BattleStart is a 60-frame pose; with no input the fighter lands in Idle.
void settle(Fighter& f, int frames = FighterConstants::kBattleStartFrames) {
    for (int i = 0; i < frames; ++i) f.update(nullptr, nullptr, kDt);
}

// Presses AttackA, then advances `extra` further frames. The swing's timer is
// kAttackFrames at the press frame, so elapsed == extra afterwards.
void press_attack(Fighter& f, Input& in, int extra) {
    in.set(fnd::input::Action::AttackA, true);
    tick(f, in);
    in.set(fnd::input::Action::AttackA, false);
    for (int i = 0; i < extra; ++i) tick(f, in);
}

// A fresh fighter at `pos` facing +Z, already out of the BattleStart pose.
Fighter make_idle_fighter(const glm::vec3& pos) {
    Fighter f;
    f.init(nullptr, nullptr, pos, 0.0f);
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

    // Hold Up for 61 frames: up = -Z (fighter.cpp:307).
    Input in;
    in.set(fnd::input::Action::Up, true);
    tick(f, in);   // first walk frame
    const float z1 = f.position().z;
    check_int("state while holding Up", static_cast<int>(FighterState::Walk),
              static_cast<int>(f.state()));
    check_bits("first walk frame dz", -80.0f * kStep, z1 - 0.0f);
    for (int i = 0; i < 60; ++i) tick(f, in);
    const float z61 = f.position().z;
    check_near("z after 61 walk frames", -80.0 * 61 * kDt, z61, 1e-3);
    check_near("measured speed over 60 frames (u/s)", -80.0,
               (z61 - z1) / (60.0 * kDt), 1e-3);
    check_bits("x untouched by pure -Z walk", 0.0f, f.position().x);

    in.set(fnd::input::Action::Up, false);
    tick(f, in);
    check_int("state after releasing Up", static_cast<int>(FighterState::Idle),
              static_cast<int>(f.state()));
    check_bits("velocity zeroed on release (position frozen)", z61, f.position().z);

    // Stick deflection past the deadzone walks too (same 8000 threshold).
    Fighter s = make_idle_fighter(glm::vec3(0, 0, 0));
    Input si;
    si.p.stick_x = 32767;
    tick(s, si);
    check_int("stick past the deadzone enters Walk", static_cast<int>(FighterState::Walk),
              static_cast<int>(s.state()));
    check_near("full stick walks at kWalkSpeed", 80.0 * kDt, s.position().x, 1e-6);
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

    // Up maps to facing-forward = +Z (fighter.cpp:579), the opposite of the
    // walk direction for the same key — a source quirk, pinned here.
    check_bits("ground dash first-frame dz", 200.0f * kStep, f.position().z - z_before);
    // Stamina: 100 - 20 = 80, then the same frame's grounded regen (+60*dt)
    // runs because Run is an actionable state (fighter.cpp:124). stamina() is
    // an int, so the observable is 81.
    check_int("stamina after dash frame (100-20+regen)", 81, f.stamina());
    in.set(fnd::input::Action::Up, false);

    // The dash window is kDashFrames = 20 frames of committed motion.
    const float z_dash0 = f.position().z;
    for (int i = 0; i < 19; ++i) tick(f, in);
    const float z_dash19 = f.position().z;
    check_near("dash travel over 20 frames", 200.0 * 20 * kDt, z_dash19 - z_before, 1e-3);
    check_near("dash speed (u/s)", 200.0, (z_dash19 - z_dash0) / (19.0 * kDt), 1.0);
    tick(f, in);
    check_int("dash expires after kDashFrames", static_cast<int>(FighterState::Idle),
              static_cast<int>(f.state()));
    // Stamina regenerates back to the cap while grounded and actionable.
    for (int i = 0; i < 40; ++i) tick(f, in);
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
    check_int("no dash below kDashStamina", static_cast<int>(FighterState::Walk),
              static_cast<int>(g.state()));
    check_bool("refused dash spends nothing", g.stamina() < 20, true);

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
    check_bits("air dash first-frame dz", 260.0f * kStep, a.position().z - z_air);
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
//  Case 3 — attacks: 30 frames, light 5 / heavy 12, melee range 160 XZ,
//           active window from elapsed frame 5, one hit per swing
// ===========================================================================
void test_attacks() {
    section("3. attack windows (30 frames, 5/12 damage, 160 XZ range)");
    check_int("kAttackFrames", 30, FighterConstants::kAttackFrames);
    check_int("kLightDamage", 5, FighterConstants::kLightDamage);
    check_int("kHeavyDamage", 12, FighterConstants::kHeavyDamage);
    check_bits("kMeleeRange", 160.0f, FighterConstants::kMeleeRange);
    check_int("kHitStunFrames", 15, FighterConstants::kHitStunFrames);

    {
        Fighter a = make_idle_fighter(glm::vec3(0, 0, 0));
        Fighter b = make_idle_fighter(glm::vec3(0, 0, 100));
        Input in;
        in.set(fnd::input::Action::AttackA, true);
        tick(a, in);
        in.set(fnd::input::Action::AttackA, false);
        check_int("state after melee press", static_cast<int>(FighterState::AttackA),
                  static_cast<int>(a.state()));
        check_bool("hit refused at elapsed 0", false, a.try_melee_hit(b));
        int first_hit = -1;
        for (int k = 1; k <= 30; ++k) {
            tick(a, in);
            if (first_hit < 0 && a.try_melee_hit(b)) first_hit = k;
        }
        // Startup is a MeleeRules window now (5 ticks), not a bare elapsed>=5 test.
        check_int("first frame the swing can land (startup window over)", 4, first_hit);
        check_int("light melee damage", 100 - 5, b.hp());
        check_int("target state after the hit", static_cast<int>(FighterState::Hit),
                  static_cast<int>(b.state()));
        check_int("swing expired to Idle", static_cast<int>(FighterState::Idle),
                  static_cast<int>(a.state()));
        // The stun is exactly kHitStunFrames: count B down to Idle.
        int stun = 0;
        while (b.state() == FighterState::Hit && stun < 60) {
            b.update(nullptr, nullptr, kDt);
            ++stun;
        }
        // A melee inflicts its own active-window stun (port rule, melee_rules.h),
        // not the shared kHitStunFrames.
        check_int("stun length after a melee hit", 8, stun);
    }

    {
        // Range: inclusive at exactly kMeleeRange, exclusive just past it.
        // The recovered hitbox is a 3D sphere of (30 + radius) centred on the attacker's
        // chest height, so at ground level the horizontal reach is sqrt(160^2 - 84^2)
        // ~= 136 — NOT a flat 160, and NOT an arc. The target's head and chest anchors
        // are both tested (FUN_0063dad0:238-243).
        Fighter a1 = make_idle_fighter(glm::vec3(0, 0, 0));
        Fighter t1 = make_idle_fighter(glm::vec3(0, 0, 120));
        Input in1;
        press_attack(a1, in1, 5);
        check_bool("melee lands inside the sphere at 120", true, a1.try_melee_hit(t1));
        Fighter a2 = make_idle_fighter(glm::vec3(0, 0, 0));
        Fighter t2 = make_idle_fighter(glm::vec3(0, 0, 160.5f));
        Input in2;
        press_attack(a2, in2, 5);
        check_bool("melee misses past the sphere's ground-level reach", false,
                   a2.try_melee_hit(t2));
        Fighter a3 = make_idle_fighter(glm::vec3(0, 0, 0));
        Fighter t3 = make_idle_fighter(glm::vec3(0, 0, 130));
        Input in3;
        press_attack(a3, in3, 5);
        check_bool("melee lands at 130, still inside", true, a3.try_melee_hit(t3));
        // There is NO cone (FUN_0063b470 has no angle term), so behind is inside the
        // sphere on exactly the same terms as in front. An earlier draft asserted the
        // opposite from an invented 60-degree arc; the sphere is what the corpus supports.
        Fighter a4 = make_idle_fighter(glm::vec3(0, 0, 0));
        Fighter t4 = make_idle_fighter(glm::vec3(0, 0, -120));
        Input in4;
        press_attack(a4, in4, 5);
        check_bool("melee behind lands too (sphere, no angle term)", true,
                   a4.try_melee_hit(t4));
    }

    {
        // One hit per swing, and a new swing re-arms it.
        Fighter a = make_idle_fighter(glm::vec3(0, 0, 0));
        Fighter b = make_idle_fighter(glm::vec3(0, 0, 100));
        Input in;
        press_attack(a, in, 5);
        check_bool("swing 1 lands", true, a.try_melee_hit(b));
        // Match records the victim, which is what stops the second connection; the
        // Fighter-side query is the per-victim set (issue #10).
        a.note_melee_hit(1);
        check_bool("the swing now records victim 1 as hit", true,
                   a.already_hit_this_swing(1));
        check_bool("and a fresh victim is still hittable", false,
                   a.already_hit_this_swing(0));
        check_int("hp after one hit", 95, b.hp());
        // Re-pressing while still in AttackA resets the timer but not the
        // swing flag (set_state early-returns on an unchanged state).
        in.set(fnd::input::Action::AttackA, true);
        tick(a, in);
        in.set(fnd::input::Action::AttackA, false);
        check_bool("re-press mid-swing keeps the swing's hit set",
                   true, a.already_hit_this_swing(1));
        // Let the swing expire, then swing again: the flag is cleared.
        for (int i = 0; i < 31; ++i) tick(a, in);
        press_attack(a, in, 5);
        check_bool("new swing after expiry lands", true, a.try_melee_hit(b));
        check_int("hp after two hits", 90, b.hp());
    }

    {
        // The heavy-key stand-in is gone (issue #10): the original has one melee key
        // and no second heavy move, so AttackB must no longer start anything.
        Fighter a = make_idle_fighter(glm::vec3(0, 0, 0));
        Fighter b = make_idle_fighter(glm::vec3(0, 0, 100));
        Input in;
        in.set(fnd::input::Action::AttackB, true);
        tick(a, in);
        in.set(fnd::input::Action::AttackB, false);
        check_int("AttackB no longer starts an attack", static_cast<int>(FighterState::Idle),
                  static_cast<int>(a.state()));
    }
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
    for (auto action : {fnd::input::Right, fnd::input::Jump, fnd::input::AttackA,
                        fnd::input::Shoot}) {
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
    section("6. jump/gravity/landing (kGravity 900, kJumpSpeed 380, fly 1.2 s)");
    check_bits("kGravity", 900.0f, FighterConstants::kGravity);
    check_bits("kJumpSpeed", 380.0f, FighterConstants::kJumpSpeed);
    check_bits("kFlyRise", 40.0f, FighterConstants::kFlyRise);
    check_bits("kFlyTimeSec", 1.2f, FighterConstants::kFlyTimeSec);
    check_bits("kFlyMaxAlt", 420.0f, FighterConstants::kFlyMaxAlt);

    Fighter f = make_idle_fighter(glm::vec3(0, 0, 0));
    Input in;
    in.set(fnd::input::Action::Jump, true);
    tick(f, in);
    check_bool("airborne on the leap frame", true, f.airborne());
    check_int("leap state", static_cast<int>(FighterState::Jump),
              static_cast<int>(f.state()));
    // kJumpSpeed is written by try_jump and then overwritten in the same frame
    // by the fly-rise branch, because just_pressed implies down[Jump] is held
    // and the state is already Jump (fighter.cpp:140-151). The 380 u/s leap
    // velocity is therefore never observable for a held key; the first frame
    // rises at kFlyRise.
    check_bits("leap frame rise uses kFlyRise, not kJumpSpeed", 40.0f * kStep,
               f.position().y);
    check_bool("a 380 u/s leap would have risen 6.33 units", f.position().y < 6.0f, true);
    check_int("leap spends kJumpStamina and one fly tick", 89, f.stamina());

    // Fly budget: count frames whose rise is kFlyRise * dt (the increment is a
    // rounded float sum, so compare within 1e-5; the gravity increments differ
    // by >0.25).
    int fly_frames = 1;   // the leap frame above
    float prev_y = f.position().y;
    float peak_y = prev_y;
    int peak_frame = 1;
    int land_frame = -1;
    for (int i = 2; i <= 200 && land_frame < 0; ++i) {
        tick(f, in);
        const float dy = f.position().y - prev_y;
        if (std::fabs(dy - 40.0f * kStep) < 1e-5) ++fly_frames;
        if (f.position().y > peak_y) { peak_y = f.position().y; peak_frame = i; }
        if (!f.airborne()) land_frame = i;
        prev_y = f.position().y;
    }
    check_int("fly frames (kFlyTimeSec / dt, float-exact)", 73, fly_frames);
    check_int("peak-altitude frame", 75, peak_frame);
    check_near("peak altitude", 49.2500191, peak_y, 1e-4);
    check_bool("kFlyMaxAlt ceiling never reached by the fly budget",
               peak_y < FighterConstants::kFlyMaxAlt, true);
    check_int("landing frame after the leap", 96, land_frame);
    check_bits("landing snaps y to groundY", 0.0f, f.position().y);
    check_bool("grounded after landing", false, f.airborne());
    check_int("landing state", static_cast<int>(FighterState::Idle),
              static_cast<int>(f.state()));
    check_int("stamina after flight (no airborne regen)", 53, f.stamina());

    // The fly budget resets on landing: jump again and it flies for 73 frames.
    in.set(fnd::input::Action::Jump, false);
    tick(f, in);
    in.set(fnd::input::Action::Jump, true);
    tick(f, in);
    int fly_frames2 = 1;
    float y2 = f.position().y;
    for (int i = 2; i <= 100; ++i) {
        tick(f, in);
        if (std::fabs((f.position().y - y2) - 40.0f * kStep) < 1e-5) ++fly_frames2;
        y2 = f.position().y;
    }
    check_int("fly budget resets on landing", 73, fly_frames2);

    // Gravity while airborne and not flying: vy loses kGravity*dt per frame.
    Fighter g = make_idle_fighter(glm::vec3(0, 0, 0));
    Input gi;
    gi.set(fnd::input::Action::Jump, true);
    tick(g, gi);
    gi.set(fnd::input::Action::Jump, false);
    tick(g, gi);
    const float dy1 = g.position().y - 40.0f * kStep;
    tick(g, gi);
    const float dy2 = g.position().y - 40.0f * kStep - dy1;
    check_near("gravity step 1", 25.0 * kDt, dy1, 1e-5);
    check_near("gravity step 2", 10.0 * kDt, dy2, 1e-5);

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
    check_near("air control scales walk speed by 0.7", 80.0 * 0.7 * kDt,
               h.position().x - x0, 1e-5);
    check_bits("kAirControl", 0.7f, FighterConstants::kAirControl);
}

// ===========================================================================
//  Case 7 — shot tiers, hold thresholds, muzzle, reloadNG, EX
// ===========================================================================
void test_shots() {
    section("7. shot tiers + hold thresholds (0.45 s yellow, 1.10 s red)");
    check_bits("kYellowHoldSec", 0.45f, FighterConstants::kYellowHoldSec);
    check_bits("kRedHoldSec", 1.10f, FighterConstants::kRedHoldSec);
    check_int("kShotFrames", 20, FighterConstants::kShotFrames);
    check_bits("kMuzzleForward", 60.0f, FighterConstants::kMuzzleForward);
    check_bits("kMuzzleHeight", 100.0f, FighterConstants::kMuzzleHeight);

    // --- tap: press one frame, release the next ---
    {
        Fighter f = make_idle_fighter(glm::vec3(0, 0, 0));
        Input in;
        in.set(fnd::input::Action::Shoot, true);
        tick(f, in);
        check_int("tier while held 1 frame", static_cast<int>(ShotTier::Tap),
                  static_cast<int>(f.charge_tier()));
        in.set(fnd::input::Action::Shoot, false);
        tick(f, in);
        const gameplay::PendingShot shot = f.take_pending_shot();
        check_bool("tap arms a pending shot", true, shot.armed);
        check_int("tap tier", static_cast<int>(ShotTier::Tap),
                  static_cast<int>(shot.tier));
        check_bits("muzzle y = kMuzzleHeight", 100.0f, shot.pos.y);
        check_bits("muzzle z = kMuzzleForward (yaw 0 faces +Z)", 60.0f, shot.pos.z);
        check_bits("muzzle x", 0.0f, shot.pos.x);
        check_bits("shot dir x", 0.0f, shot.dir.x);
        check_bits("shot dir z", 1.0f, shot.dir.z);
        // The spend and the same frame's recharge both land before update()
        // returns (fire in the state machine, recharge at step 5b), so the
        // observable is 5 + 0.8*dt.
        check_near("tap spends 1 MAIN (plus one recharge tick)",
                   5.0 + 0.8 * kDt, f.main_frac() * 6.0, 1e-5);
        check_int("MAIN whole after tap", 5, f.main_whole());
        check_int("CHARGE untouched by a tap", 2, f.charge_whole());
        check_int("tap state", static_cast<int>(FighterState::ShootA),
                  static_cast<int>(f.state()));
        check_bool("pending disarmed by take_pending_shot", false,
                   f.take_pending_shot().armed);
        check_bool("reloadNG open on the firing frame", false, f.reload_ok());
        int frames = 0;
        while (!f.reload_ok() && frames < 100) { tick(f, in); ++frames; }
        check_int("tap reloadNG window (frames incl. firing frame)", 15, frames + 1);
        int pose_ticks = frames;
        while (f.state() == FighterState::ShootA && pose_ticks < 100) {
            tick(f, in);
            ++pose_ticks;
        }
        check_int("firing pose lasts kShotFrames ticks", 20, pose_ticks);
        check_int("firing pose expires to Idle", static_cast<int>(FighterState::Idle),
                  static_cast<int>(f.state()));
    }

    // --- hold thresholds, per tier ---
    {
        Fighter f = make_idle_fighter(glm::vec3(0, 0, 0));
        Input in;
        in.set(fnd::input::Action::Shoot, true);
        for (int i = 0; i < 26; ++i) tick(f, in);
        check_int("26 held frames (0.4333 s) is still Tap",
                  static_cast<int>(ShotTier::Tap), static_cast<int>(f.charge_tier()));
        tick(f, in);   // 27th
        check_int("27 held frames (0.4500 s) reaches Yellow",
                  static_cast<int>(ShotTier::Yellow), static_cast<int>(f.charge_tier()));
        check_near("charge_hold_frac at the yellow threshold", 27.0 * kDt / 1.10,
                   f.charge_hold_frac(), 1e-6);
        in.set(fnd::input::Action::Shoot, false);
        tick(f, in);
        const gameplay::PendingShot y = f.take_pending_shot();
        check_int("yellow tier fired", static_cast<int>(ShotTier::Yellow),
                  static_cast<int>(y.tier));
        check_near("yellow spends 1 CHARGE (plus one recharge tick)",
                   1.0 + 0.3 * kDt, f.charge_frac() * 2.0, 1e-6);
        check_int("yellow state", static_cast<int>(FighterState::ShootB),
                  static_cast<int>(f.state()));
        check_bool("yellow reloadNG open", false, f.reload_ok());
        int frames = 0;
        while (!f.reload_ok() && frames < 100) { tick(f, in); ++frames; }
        check_int("yellow reloadNG window", 30, frames + 1);
    }
    {
        Fighter f = make_idle_fighter(glm::vec3(0, 0, 0));
        Input in;
        in.set(fnd::input::Action::Shoot, true);
        for (int i = 0; i < 66; ++i) tick(f, in);
        check_int("66 held frames (1.0999 s) is still Yellow",
                  static_cast<int>(ShotTier::Yellow), static_cast<int>(f.charge_tier()));
        tick(f, in);   // 67th
        check_int("67 held frames reaches Red", static_cast<int>(ShotTier::Red),
                  static_cast<int>(f.charge_tier()));
        check_bits("charge_hold_frac clamps to 1", 1.0f, f.charge_hold_frac());
        in.set(fnd::input::Action::Shoot, false);
        tick(f, in);
        const gameplay::PendingShot r = f.take_pending_shot();
        check_int("red tier fired", static_cast<int>(ShotTier::Red),
                  static_cast<int>(r.tier));
        check_near("red spends 2 CHARGE (plus one recharge tick)",
                   0.0 + 0.3 * kDt, f.charge_frac() * 2.0, 1e-6);
        check_int("red state", static_cast<int>(FighterState::ShootC),
                  static_cast<int>(f.state()));
        int frames = 0;
        while (!f.reload_ok() && frames < 100) { tick(f, in); ++frames; }
        check_int("red reloadNG window", 45, frames + 1);
    }

    // --- muzzle follows facing (yaw 0 faces +Z) ---
    {
        Fighter f;
        f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 1.5707964f);   // +90°
        settle(f);
        Input in;
        in.set(fnd::input::Action::Shoot, true);
        tick(f, in);
        in.set(fnd::input::Action::Shoot, false);
        tick(f, in);
        const gameplay::PendingShot shot = f.take_pending_shot();
        check_near("muzzle x at yaw 90°", 60.0, shot.pos.x, 1e-3);
        check_near("muzzle z at yaw 90°", 0.0, shot.pos.z, 1e-3);
        check_near("dir x at yaw 90°", 1.0, shot.dir.x, 1e-6);
    }

    // --- reloadNG gates a second shot (silently dropped) ---
    {
        Fighter f = make_idle_fighter(glm::vec3(0, 0, 0));
        Input in;
        in.set(fnd::input::Action::Shoot, true);
        tick(f, in);
        in.set(fnd::input::Action::Shoot, false);
        tick(f, in);
        (void)f.take_pending_shot();
        const int whole_before = f.main_whole();
        in.set(fnd::input::Action::Shoot, true);
        tick(f, in);
        in.set(fnd::input::Action::Shoot, false);
        tick(f, in);
        check_bool("shot under reloadNG is dropped", false, f.take_pending_shot().armed);
        check_int("dropped shot spends no MAIN", whole_before, f.main_whole());
    }

    // --- no CHARGE stock: a red shot is dropped after the reload window ---
    {
        Fighter f = make_idle_fighter(glm::vec3(0, 0, 0));
        Input in;
        in.set(fnd::input::Action::Shoot, true);
        for (int i = 0; i < 67; ++i) tick(f, in);
        in.set(fnd::input::Action::Shoot, false);
        tick(f, in);
        (void)f.take_pending_shot();
        check_int("CHARGE emptied by the red shot", 0, f.charge_whole());
        while (!f.reload_ok()) tick(f, in);
        const int charge_whole = f.charge_whole();
        in.set(fnd::input::Action::Shoot, true);
        for (int i = 0; i < 67; ++i) tick(f, in);
        in.set(fnd::input::Action::Shoot, false);
        tick(f, in);
        check_bool("no CHARGE stock -> dropped", false, f.take_pending_shot().armed);
        check_int("no CHARGE spent by the dropped shot", charge_whole, f.charge_whole());
    }

    // --- EX move: Special while hypermode is active fires the Ex tier ---
    {
        Fighter f = make_idle_fighter(glm::vec3(0, 0, 0));
        f.set_hyper_gauge(1.0f);
        Input in;
        in.set(fnd::input::Action::Special, true);
        tick(f, in);
        check_bool("Special at a full bar activates hypermode", true, f.hyper_active());
        in.set(fnd::input::Action::Special, false);
        tick(f, in);
        in.set(fnd::input::Action::Special, true);
        tick(f, in);
        const gameplay::PendingShot ex = f.take_pending_shot();
        check_bool("EX move arms a shot", true, ex.armed);
        check_int("EX tier", static_cast<int>(ShotTier::Ex), static_cast<int>(ex.tier));
        check_int("EX state", static_cast<int>(FighterState::ShotFinal),
                  static_cast<int>(f.state()));
        check_near("EX spends 1 CHARGE (plus one x1.6 recharge tick)",
                   1.0 + 0.3 * 1.6 * kDt, f.charge_frac() * 2.0, 1e-6);
        int frames = 0;
        while (!f.reload_ok() && frames < 200) { tick(f, in); ++frames; }
        check_int("EX reloadNG window", 60, frames + 1);
    }
}

// ===========================================================================
//  Case 8 — ammo spend/recharge (MAIN 6 @ 0.8/s, CHARGE 2 @ 0.3/s)
// ===========================================================================
void test_ammo() {
    section("8. ammo spend/recharge (MAIN 6 / 0.8 per s, CHARGE 2 / 0.3 per s)");
    check_bits("kMainMax", 6.0f, FighterConstants::kMainMax);
    check_bits("kChargeMax", 2.0f, FighterConstants::kChargeMax);
    check_bits("kMainPerSec", 0.8f, FighterConstants::kMainPerSec);
    check_bits("kChargePerSec", 0.3f, FighterConstants::kChargePerSec);

    {
        Fighter f = make_idle_fighter(glm::vec3(0, 0, 0));
        Input in;
        in.set(fnd::input::Action::Shoot, true);
        tick(f, in);
        in.set(fnd::input::Action::Shoot, false);
        tick(f, in);
        // The firing frame already includes one recharge tick.
        const float v0 = f.main_frac() * 6.0f;
        check_near("MAIN right after a tap", 5.0 + 0.8 * kDt, v0, 1e-5);
        tick(f, in);
        check_near("MAIN refill per frame = 0.8*dt", 0.8 * kDt,
                   f.main_frac() * 6.0f - v0, 1e-5);
        for (int i = 0; i < 59; ++i) tick(f, in);
        check_near("MAIN after 60 more frames of refill", 5.0 + 61.0 * 0.8 * kDt,
                   f.main_frac() * 6.0, 1e-4);
        for (int i = 0; i < 200; ++i) tick(f, in);
        check_bits("MAIN refill clamps at kMainMax", 6.0f, f.main_frac() * 6.0f);
        check_int("MAIN whole back to 6", 6, f.main_whole());
    }
    {
        Fighter f = make_idle_fighter(glm::vec3(0, 0, 0));
        Input in;
        in.set(fnd::input::Action::Shoot, true);
        for (int i = 0; i < 27; ++i) tick(f, in);
        in.set(fnd::input::Action::Shoot, false);
        tick(f, in);
        check_near("CHARGE right after a yellow shot", 1.0 + 0.3 * kDt,
                   f.charge_frac() * 2.0, 1e-6);
        for (int i = 0; i < 60; ++i) tick(f, in);
        check_near("CHARGE after 60 more frames of refill", 1.0 + 61.0 * 0.3 * kDt,
                   f.charge_frac() * 2.0, 1e-4);
        for (int i = 0; i < 300; ++i) tick(f, in);
        check_bits("CHARGE refill clamps at kChargeMax", 2.0f, f.charge_frac() * 2.0f);
        check_int("CHARGE whole back to 2", 2, f.charge_whole());
    }

    // Friendship's recharge boost (mainRechargeMul / chargeRechargeMul = 1.6).
    {
        Fighter plain = make_idle_fighter(glm::vec3(0, 0, 0));
        Input in;
        in.set(fnd::input::Action::Shoot, true);
        tick(plain, in);
        in.set(fnd::input::Action::Shoot, false);
        tick(plain, in);
        const double plain_v0 = plain.main_frac() * 6.0;
        for (int i = 0; i < 30; ++i) tick(plain, in);
        const double plain_gain = plain.main_frac() * 6.0 - plain_v0;

        Fighter hyper = make_idle_fighter(glm::vec3(0, 0, 0));
        hyper.set_hypermode(Hypermode::Friendship);
        hyper.set_hyper_gauge(1.0f);
        Input hin;
        hin.set(fnd::input::Action::Special, true);
        tick(hyper, hin);
        hin.set(fnd::input::Action::Special, false);
        tick(hyper, hin);
        check_bool("Friendship active for the recharge test", true, hyper.hyper_active());
        hin.set(fnd::input::Action::Shoot, true);
        tick(hyper, hin);
        hin.set(fnd::input::Action::Shoot, false);
        tick(hyper, hin);
        const double hyper_v0 = hyper.main_frac() * 6.0;
        for (int i = 0; i < 30; ++i) tick(hyper, hin);
        const double hyper_gain = hyper.main_frac() * 6.0 - hyper_v0;
        check_near("plain MAIN gain over 30 frames", 0.4, plain_gain, 1e-4);
        check_near("Friendship MAIN gain over 30 frames (x1.6)", 0.64, hyper_gain, 1e-4);
        check_near("Friendship recharge ratio", 1.6, hyper_gain / plain_gain, 1e-3);
    }
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
        check_near("knockback carries away at 0.8 friction", -200.0 * 0.8 * kDt,
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
    f.take_damage(0, nullptr);
    check_int("damage floor is 1", 99, f.hp());

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
    section("11. facing (turn toward the opponent, kTurnSpeed 8 rad/s)");
    Fighter a = make_idle_fighter(glm::vec3(0, 0, 0));
    Fighter b = make_idle_fighter(glm::vec3(100, 0, 0));
    a.update(nullptr, &b, kDt);
    check_near("first-frame turn toward +X", (3.14159265 / 2.0) * 8.0 * kDt,
               a.facing_yaw(), 1e-5);
    // kTurnSpeed is a lerp factor, so the approach is exponential, not linear:
    // after 30 frames the residual is (1 - 8*dt)^30 = 1.4% of the target.
    for (int i = 0; i < 29; ++i) a.update(nullptr, &b, kDt);
    check_near("facing approaches +X exponentially", 3.14159265 / 2.0, a.facing_yaw(),
               0.03);
    check_bool("turning is monotonic toward the target",
               a.facing_yaw() < 3.14159265 / 2.0, true);

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
//  Case 12 — animation binding: the original's state → set index table
// ===========================================================================
// The shipped .X files name their sets "Anim-1"…"Anim-124" and the original
// binds INDICES (state → move id → the move's first phase; see the table above
// state_to_anim_set in gameplay/fighter.h). These checks pin the table's rows
// and, just as important, that the two fallbacks are reported rather than
// silently looking like a mapped state.
void test_anim_binding() {
    section("12. animation binding (state -> set index table + reported fallback)");

    // A shipped-shaped rig: 124 sets, named the way the .X files name them. The
    // model's index i is the D3DX set i (Parser::finish reverses file order), so
    // the names here are the reverse of the file's "Anim-1"…"Anim-124".
    std::vector<std::string> names;
    for (int i = 0; i < 124; ++i) names.push_back("Anim-" + std::to_string(124 - i));
    const xm::Model model = make_anim_model(names);
    xm::Controller ctrl;
    ctrl.bind(&model);

    Fighter f;
    f.init(&model, &ctrl, glm::vec3(0, 0, 0), 0.0f);
    // BattleStart is the round reset's pose: move 0xc2 (FUN_004219a0 at 0x4219a0
    // restores HP/inputs then plays it), whose single phase names set 43.
    check_int("BattleStart binds the round-reset pose (43)", 43, ctrl.trackAnimationSet(0));
    check_bool("BattleStart is a mapped state", false, f.anim_fallback());
    check_str("set 43's own name", "Anim-81", f.anim_set_name());
    check_bool("model() is exposed", true, f.model() == &model);

    struct Row { FighterState state; int set; const char* name; };
    const Row rows[] = {
        {FighterState::Idle,        0,  "Anim-124"},  // move 0 (reset 0x41de68)
        {FighterState::Walk,        13, "Anim-111"},  // move 0x14, forward walk
        {FighterState::Run,         54, "Anim-70"},   // move 0x1e, fastest chain
        {FighterState::AttackA,     2,  "Anim-122"},  // melee chain 0x28/0x29/0x2a
        {FighterState::AttackB,     3,  "Anim-121"},
        {FighterState::AttackC,     5,  "Anim-119"},
        {FighterState::Hit,         95, "Anim-29"},   // move 0x67 (cases 0xe7/0xca)
        {FighterState::Knockdown,   28, "Anim-96"},   // move 0xc4
        {FighterState::KO,          97, "Anim-27"},   // move 0xcb (cases 0xc9/0xcc)
        {FighterState::ShootA,      31, "Anim-93"},   // weapon shot moves 300/301/302
        {FighterState::ShootB,      33, "Anim-91"},
        {FighterState::ShootC,      34, "Anim-90"},
        {FighterState::ShotFinal,   69, "Anim-55"},   // move 0x1f7 (EX fallback)
    };
    for (const Row& r : rows) {
        // A fresh fighter per row: init() hard-cuts BattleStart (43) with a
        // full 60-frame state timer, so every row blends 43 -> target and no
        // expiry can inject an Idle blend mid-row (13 rows x 8 updates on one
        // fighter would overrun the timer).
        Fighter fr;
        fr.init(&model, &ctrl, glm::vec3(0, 0, 0), 0.0f);
        fr.set_state(r.state);
        // Move changes blend (FUN_004211f0/FUN_00421240 + FUN_0041f580
        // weights): the old set stays on track 0 while the new set starts on
        // track 1 from t=0, then kAnimBlendTicks updates commit both tracks.
        check_int("new set starts on track 1", r.set, ctrl.trackAnimationSet(1));
        check_int("old set holds on track 0 mid-blend", 43, ctrl.trackAnimationSet(0));
        check_near("blend opens at full old weight", 1.0f, ctrl.trackWeight(0), 1e-6);
        check_near("blend opens at zero new weight", 0.0f, ctrl.trackWeight(1), 1e-6);
        check_int("anim_set_index() agrees", r.set, fr.anim_set_index());
        check_str("anim_set_name() is the model's own name", r.name, fr.anim_set_name());
        check_bool("mapped state reports no fallback", false, fr.anim_fallback());
        for (int t = 0; t < FighterConstants::kAnimBlendTicks; ++t)
            fr.update(nullptr, nullptr, kDt);
        check_int("blend commits track 0", r.set, ctrl.trackAnimationSet(0));
        check_int("blend commits track 1", r.set, ctrl.trackAnimationSet(1));
        check_near("committed track 0 is full weight", 1.0f, ctrl.trackWeight(0), 1e-6);
        check_near("committed track 1 is full weight", 1.0f, ctrl.trackWeight(1), 1e-6);
    }

    // Chained blends on one fighter propagate the old set: Idle completes
    // 43 -> 0, Walk blends 0 -> 13, and an AttackA interruption 3 ticks in
    // only retargets track 1 (FUN_00421240 rebinds track 1 alone): track 0
    // keeps the old set and the weights continue from their live values, so
    // the pose never snaps. 19 updates total, inside the 60-frame state
    // timer, so no expiry interferes.
    f.set_state(FighterState::Idle);
    for (int t = 0; t < FighterConstants::kAnimBlendTicks; ++t)
        f.update(nullptr, nullptr, kDt);
    check_int("first blend settles on track 0", 0, ctrl.trackAnimationSet(0));
    f.set_state(FighterState::Walk);
    check_int("chained blend holds the previous set", 0, ctrl.trackAnimationSet(0));
    check_int("chained blend targets track 1", 13, ctrl.trackAnimationSet(1));
    for (int t = 0; t < 3; ++t) f.update(nullptr, nullptr, kDt);
    f.set_state(FighterState::AttackA);   // interrupts: track 1 -> 2, no snap
    check_int("interruption keeps the old set on track 0", 0, ctrl.trackAnimationSet(0));
    check_int("interruption retargets track 1", 2, ctrl.trackAnimationSet(1));
    check_near("weights continue through the interruption", 0.375f,
               ctrl.trackWeight(1), 1e-6);
    for (int t = 0; t < FighterConstants::kAnimBlendTicks; ++t)
        f.update(nullptr, nullptr, kDt);
    check_int("interrupted blend settles", 2, ctrl.trackAnimationSet(0));

    // The three states the table deliberately leaves open (see the "not settled"
    // list in fighter.h): they must play set 0 AND say so.
    for (FighterState s : {FighterState::Guard, FighterState::Jump, FighterState::TagOut}) {
        f.set_state(s);
        check_int("unmapped state falls back to set 0", 0, ctrl.trackAnimationSet(1));
        check_bool("unmapped state reports the fallback", true, f.anim_fallback());
        for (int t = 0; t < FighterConstants::kAnimBlendTicks; ++t)
            f.update(nullptr, nullptr, kDt);
    }

    // A model shorter than the table's index is the other fallback path.
    const xm::Model shortModel = make_anim_model({"a", "b"});
    xm::Controller shortCtrl;
    shortCtrl.bind(&shortModel);
    Fighter g;
    g.init(&shortModel, &shortCtrl, glm::vec3(0, 0, 0), 0.0f);   // BattleStart -> 43
    check_int("index past the model's sets falls back to 0", 0, shortCtrl.trackAnimationSet(0));
    check_bool("short model reports the fallback", true, g.anim_fallback());
    g.set_state(FighterState::Idle);                             // index 0 fits
    check_int("index 0 fits a short model", 0, shortCtrl.trackAnimationSet(0));
    check_bool("in-range index clears the fallback", false, g.anim_fallback());

    // A model with no sets at all must not bind anything.
    const xm::Model empty;
    xm::Controller emptyCtrl;
    emptyCtrl.bind(&empty);
    Fighter h;
    h.init(&empty, &emptyCtrl, glm::vec3(0, 0, 0), 0.0f);
    check_int("no sets -> no track bound", -1, emptyCtrl.trackAnimationSet(0));
    check_str("no sets -> no name", "", h.anim_set_name());

    // A fighter with no model at all must not crash or bind.
    Fighter none;
    none.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    check_bool("null model is accepted", true, none.model() == nullptr);

    // pose() reports the controller's playhead.
    Fighter k;
    k.init(&model, &ctrl, glm::vec3(0, 0, 0), 0.0f);
    k.update(nullptr, nullptr, kDt);
    check_near("pose().animTime advances with dt", kDt, k.pose().animTime, 1e-6);
    check_bits("pose().position.x", 0.0f, k.pose().position.x);
    check_bool("pose().alive", true, k.pose().alive);
    check_near("pose().facingYaw", 0.0, k.pose().facingYaw, 0.0);
    k.set_hp(1);
    k.take_damage(5, nullptr);
    check_bool("pose().alive clears on KO", false, k.pose().alive);
    // render::ArenaTarget sync keeps the camera path working.
    render::ArenaTarget target;
    h.sync_target(target);
    check_bits("sync_target position", 0.0f, target.position.x);
    check_near("sync_target facingYaw", 0.0, target.facingYaw, 0.0);

    // The renderer's colour type and gameplay::Rgb are the same bits.
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

    // --- tier speed/damage/life through the pool ---
    {
        ProjectilePool pool;
        Fighter victim = make_idle_fighter(glm::vec3(0, 0, 10));
        check_bool("spawn returns true", true,
                   pool.spawn(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), ShotTier::Tap,
                              nullptr));
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

    // --- owner never self-hits; the same shot hits a third party ---
    {
        ProjectilePool pool;
        Fighter owner = make_idle_fighter(glm::vec3(0, 0, 0));
        pool.spawn(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), ShotTier::Tap, &owner);
        pool.update(kDt, &owner, 1, nullptr, nullptr);
        check_int("owner takes no damage from its own shot", 100, owner.hp());
        check_int("the shot survives the pass over its owner", 1, pool.live_shots());
        // Same geometry, no owner: the shot connects, so the check above is
        // the exclusion and not a range miss.
        ProjectilePool pool2;
        Fighter victim = make_idle_fighter(glm::vec3(0, 0, 0));
        pool2.spawn(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), ShotTier::Tap, nullptr);
        pool2.update(kDt, &victim, 1, nullptr, nullptr);
        check_int("same shot with no owner deals 4", 96, victim.hp());
    }

    // --- wall hit on a synthetic tama mesh ---
    {
        const xm::Model wall = make_wall_model();
        const game::physics::ModelIndex index = game::physics::buildModelIndex(wall);
        check_int("wall index has one mesh", 1,
                  static_cast<long long>(index.meshOrder.size()));

        ProjectilePool pool;
        // Behind the wall and far enough that the shot cannot reach it: the
        // Tap hit radius is 55 and the wall sits at z = 100.
        Fighter behind = make_idle_fighter(glm::vec3(0, 0, 300));
        pool.spawn(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), ShotTier::Tap, nullptr);
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
        miss.spawn(glm::vec3(0, 300, 0), glm::vec3(0, 0, 1), ShotTier::Tap, nullptr);
        for (int i = 0; i < 20; ++i) miss.update(kDt, nullptr, 0, &wall, &index);
        check_int("shot above the wall survives past it", 1, miss.live_shots());
        check_int("no spark for the miss", 0, count_live_sparks(miss));

        // A null model/index pair means "no wall geometry" (the open-field
        // fallback) and must not dereference anything.
        ProjectilePool open;
        open.spawn(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), ShotTier::Tap, nullptr);
        for (int i = 0; i < 20; ++i) open.update(kDt, nullptr, 0, nullptr, nullptr);
        check_int("null tama model leaves the shot flying", 1, open.live_shots());
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

    // --- red tier: 16 damage, 80-unit hit radius ---
    {
        ProjectilePool pool;
        Fighter victim = make_idle_fighter(glm::vec3(0, 0, 70));
        pool.spawn(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), ShotTier::Red, nullptr);
        pool.update(kDt, &victim, 1, nullptr, nullptr);
        check_int("red shot hits at 70 units (shot at 7.7, radius 80)", 100 - 16,
                  victim.hp());
        ProjectilePool far;
        Fighter out = make_idle_fighter(glm::vec3(0, 0, 90));
        far.spawn(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), ShotTier::Red, nullptr);
        far.update(kDt, &out, 1, nullptr, nullptr);
        check_int("red shot misses at 90 units (shot at 7.7, radius 80)", 100,
                  out.hp());
    }

    // --- a KO'd fighter is skipped ---
    {
        ProjectilePool pool;
        Fighter dead = make_idle_fighter(glm::vec3(0, 0, 0));
        dead.set_hp(1);
        dead.take_damage(5, nullptr);
        pool.spawn(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), ShotTier::Tap, nullptr);
        pool.update(kDt, &dead, 1, nullptr, nullptr);
        check_int("downed fighters are skipped", 0, dead.hp());
        check_int("shot passes through the downed fighter", 1, pool.live_shots());
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
        ib.set(fnd::input::Action::AttackB, ph == 35);
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

void test_determinism() {
    section("14. determinism: same 600-frame script twice");
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

int main() {
    std::printf("fighter_script_test — ported fighter + projectile gameplay\n");
    std::printf("dt = 1/60 s (double %.17g, float step %.9g)\n", kDt,
                static_cast<double>(kStep));

    test_idle_walk();
    test_dash();
    test_attacks();
    test_hit_stun();
    test_guard_drain();
    test_air();
    test_shots();
    test_ammo();
    test_hypermode();
    test_ko();
    test_facing();
    test_anim_binding();
    test_projectile_pool();
    test_determinism();

    std::printf("\n%d checks, %d failed\n", g_checks, g_fails);
    std::printf("FIGHTER_SCRIPT: %s\n", g_fails == 0 ? "ok" : "FAIL");
    return g_fails == 0 ? 0 : 1;
}
