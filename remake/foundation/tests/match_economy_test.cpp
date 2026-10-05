// =============================================================================
//  match_economy_test.cpp — host test for the headless half of Phase 2 item 2c
//  (FULL-REPLACEMENT-PLAN.md §5): gameplay::MatchEconomy, the balloon / LIMIT /
//  KO-clock state of Scene_Gameplay (remake/src/core/scenes.cpp:701-721), and
//  gameplay::fillHudValues, the HUD value computation of its render()
//  (scenes.cpp:818-893).
//
//  No WebGPU, no SDL, no device. The test links match_economy.cpp only: the
//  mapping under test (fillHudValues) is inline in hud_fill.h, and hud_fill.cpp
//  — the game/hud_bridge.h -> ui/ -> webgpu.h seam — is compiled by the real
//  target instead (see the deliverable report).
//
//    g++ -std=c++20 -Wall -Wextra -I remake/foundation/src
//        -I remake/foundation/third_party/glm
//        remake/foundation/tests/match_economy_test.cpp
//        remake/foundation/src/gameplay/match_economy.cpp -o /tmp/match_economy_test
//    /tmp/match_economy_test          # prints MATCH_ECONOMY: ok|FAIL, exit 1 on mismatch
//
//  Every case prints expected vs got. Comparisons are exact: the timings used at
//  boundaries are binary-exact multiples of 1.0 / 0.5 s, and the balloon
//  arithmetic (21% steps to 105%) is exact in float, so a mismatch is a real
//  divergence from the reference, not rounding noise. The one accumulation case
//  that is not exact by construction (600 x 1/60) is compared bit-for-bit
//  against the same additions done by the test.
// =============================================================================

#include <cmath>
#include <cstdio>
#include <string>

#include "game/hud_values.h"
#include "gameplay/hud_fill.h"
#include "gameplay/match_economy.h"

namespace {

int g_checks = 0;
int g_failed = 0;

// --- reporting -------------------------------------------------------------

std::string fmtInt(long long v) {
    char b[32];
    std::snprintf(b, sizeof b, "%lld", v);
    return std::string(b);
}

std::string fmtFloat(float v) {
    char b[48];
    std::snprintf(b, sizeof b, "%.9g", static_cast<double>(v));
    return std::string(b);
}

std::string fmtDouble(double v) {
    char b[64];
    std::snprintf(b, sizeof b, "%.17g", v);
    return std::string(b);
}

std::string fmtBool(bool v) { return v ? "true" : "false"; }

std::string escape(const std::string& s) {
    std::string out;
    for (const char c : s) {
        if (c == '\n')      out += "\\n";
        else if (c == '\t') out += "\\t";
        else                out += c;
    }
    return out;
}

std::string fmtRgb(game::GameRgb c) {
    char b[96];
    std::snprintf(b, sizeof b, "{%.9g, %.9g, %.9g}", static_cast<double>(c.r),
                  static_cast<double>(c.g), static_cast<double>(c.b));
    return std::string(b);
}

void report(const char* what, bool ok, const char* want, const char* got) {
    std::printf("  [%s] %-56s want %s, got %s\n", ok ? "ok" : "FAIL", what, want, got);
    ++g_checks;
    if (!ok) ++g_failed;
}

void checkBool(const char* what, bool want, bool got) {
    report(what, want == got, fmtBool(want).c_str(), fmtBool(got).c_str());
}

void checkInt(const char* what, long long want, long long got) {
    report(what, want == got, fmtInt(want).c_str(), fmtInt(got).c_str());
}

// Exact float equality, printed with %.9g (round-trips a float).
void checkFloat(const char* what, float want, float got) {
    report(what, want == got, fmtFloat(want).c_str(), fmtFloat(got).c_str());
}

void checkDouble(const char* what, double want, double got) {
    report(what, want == got, fmtDouble(want).c_str(), fmtDouble(got).c_str());
}

void checkStr(const char* what, const std::string& want, const std::string& got) {
    report(what, want == got, escape(want).c_str(), escape(got).c_str());
}

void checkRgb(const char* what, game::GameRgb want, game::GameRgb got) {
    report(what, want.r == got.r && want.g == got.g && want.b == got.b,
           fmtRgb(want).c_str(), fmtRgb(got).c_str());
}

// A silent economy, so only the trace test writes to stdout.
gameplay::MatchEconomy quietEconomy() {
    gameplay::MatchEconomy eco;
    eco.setLogFile(nullptr);
    return eco;
}

// The killing blow that moves a standing victim straight into the downed reaction:
// the +1 the reference prints as the familiar 21% (FUN_00639160 @0x639325,
// FUN_0063ba80's default branch). Scene code calls take_damage() and the note is
// armed for it; the tests here arm it directly so the economy's own arithmetic is
// what is under test.
void noteDownedKill(gameplay::MatchEconomy& eco, int fighter, int overkillHp = 0,
                    bool shot = false) {
    eco.note_death(fighter, overkillHp,
                   gameplay::downedReactionBonus(gameplay::kReactionDowned, 0, true, shot),
                   shot);
}

// A freshly initialized fighter's HUD values (FighterConstants: kMaxHP 100,
// kMainMax 6, kChargeMax 2 — remake/src/gameplay/fighter.h:167-181).
gameplay::HudFighterValues freshFighter() {
    gameplay::HudFighterValues f;
    f.hp = 100;
    f.alive = true;
    f.mainWhole = 6;
    f.mainFrac = 1.0f;
    f.reloadOk = true;
    f.chargeWhole = 2;
    f.chargeFrac = 1.0f;
    f.shootHeld = false;
    f.chargeHoldFrac = 0.0f;
    f.chargeTier = game::HoldTier::Idle;
    f.hyperName = "FRIENDSHIP";
    f.hyperGauge = 0.0f;
    f.hyperActive = false;
    f.hyperReady = false;
    f.hyperSecondsLeft = 0.0f;
    f.hyperAura = game::GameRgb{130.f / 255.f, 220.f / 255.f, 255.f / 255.f};
    f.stamina = 100;
    f.staminaVisible = false;
    return f;
}

// --- economy ---------------------------------------------------------------

void testConstants() {
    std::printf("\n-- recovered constants (FUN_00639160:0x6393b5, FUN_00635d40:0x636e90)\n");
    checkInt("kSideCount", 2, gameplay::kSideCount);
    // The +21% the reference prints is 20 (0x14) plus the downed-reaction bonus; the
    // base alone is what the melee/shot credit sites push.
    checkFloat("kBalloonPerKo", 20.0f, gameplay::kBalloonPerKo);
    checkFloat("kBalloonLimit", 100.0f, gameplay::kBalloonLimit);
    checkInt("kBalloonSizeMin", 40, gameplay::kBalloonSizeMin);
    checkInt("kBalloonSizeMax", 200, gameplay::kBalloonSizeMax);
    checkInt("kBalloonSizeStep", 20, gameplay::kBalloonSizeStep);
    checkDouble("kKoStingSec", 2.0, gameplay::kKoStingSec);   // 0x78 frames at 60 Hz
    checkDouble("kRespawnSec", 3.0, gameplay::kRespawnSec);
    // FUN_00421930 returns capacity - balloon and FUN_00635d40 ends the round when it
    // is not > 0, i.e. the capacity itself already bursts.
    checkBool("balloonBursts(100, 100) — the capacity itself bursts", true,
              gameplay::balloonBursts(100.0f, 100.0f));
    checkBool("balloonBursts(99.999, 100)", false, gameplay::balloonBursts(99.999f, 100.0f));
    checkBool("balloonBursts(84, 100) — four KOs do not burst", false,
              gameplay::balloonBursts(84.0f, 100.0f));
    checkBool("balloonBursts(105, 100)", true, gameplay::balloonBursts(105.0f, 100.0f));
    checkBool("balloonBursts(40, 40) — the 40% handicap bursts there", true,
              gameplay::balloonBursts(40.0f, 40.0f));
    checkBool("balloonBursts(189, 200) — the 200% ceiling holds", false,
              gameplay::balloonBursts(189.0f, 200.0f));

    std::printf("  -- KO increment: 20 + overkill + reaction (FUN_00639160/FUN_00637950)\n");
    checkInt("koIncrementPercent(0, false, false) == 20", 20,
             gameplay::koIncrementPercent(0, false, false));
    checkInt("koIncrementPercent(0, true, false) == 21 (the observed +21%)", 21,
             gameplay::koIncrementPercent(0, true, false));
    // Melee: 20 + HP_below/10, uncapped (FUN_00639160 @0x6393a5: /1000 on 1/100 HP).
    checkInt("melee overkill 5 -> 20 + 0", 20, gameplay::koIncrementPercent(5, false, false));
    checkInt("melee overkill 25 -> 20 + 2", 22, gameplay::koIncrementPercent(25, false, false));
    checkInt("melee overkill 250 -> 20 + 25", 45, gameplay::koIncrementPercent(250, false, false));
    // Shots: 20 + min(HP_below/5, 5), +1 below 35 and +1 below 45
    // (FUN_00637950 @0x638cad-0x638d15).
    checkInt("shot overkill 4 -> 20 + 0", 20, gameplay::koIncrementPercent(4, false, true));
    checkInt("shot overkill 5 -> 20 + 1", 21, gameplay::koIncrementPercent(5, false, true));
    checkInt("shot overkill 30 -> the /5 term caps at +5", 25,
             gameplay::koIncrementPercent(30, false, true));
    checkInt("shot overkill 100 -> cap + both deep steps", 27,
             gameplay::koIncrementPercent(100, false, true));
    checkInt("shot overkill 36 -> cap 5 + the -35 step", 26,
             gameplay::koIncrementPercent(36, false, true));
    checkInt("shot overkill 46 -> cap 5 + both steps", 27,
             gameplay::koIncrementPercent(46, false, true));
    checkInt("shot overkill 46 + reaction -> 28", 28, gameplay::koIncrementPercent(46, true, true));

    std::printf("  -- FUN_0063ba80: hit category -> victim reaction move\n");
    checkInt("category 0 (unknown) -> the default 198", 198,
             gameplay::reactionMoveForHitCategory(0, false));
    checkInt("category 102 -> 192 (the bullet-001 level-1 dword)", 192,
             gameplay::reactionMoveForHitCategory(102, false));
    checkInt("category 100 -> 197", 197, gameplay::reactionMoveForHitCategory(100, false));
    checkInt("category 130 -> 193", 193, gameplay::reactionMoveForHitCategory(130, false));
    checkInt("airborne victim -> 199 whatever the category", 199,
             gameplay::reactionMoveForHitCategory(102, true));
    checkInt("the unrecovered 0x800 flag -> 191", 191,
             gameplay::reactionMoveForHitCategory(102, false, true));

    std::printf("  -- the reaction bonus and its one-shot latch\n");
    checkBool("downed blow on a standing victim: bonus", true,
              gameplay::downedReactionBonus(198, 0, true, false));
    checkBool("the latch is spent: no bonus", false,
              gameplay::downedReactionBonus(198, 0, false, false));
    checkBool("victim already in the downed reaction: no bonus", false,
              gameplay::downedReactionBonus(198, 198, true, false));
    checkBool("victim airborne (199): no bonus", false,
              gameplay::downedReactionBonus(198, 199, true, false));
    checkBool("melee does not exclude the grounded reaction", true,
              gameplay::downedReactionBonus(198, 196, true, false));
    checkBool("shots do exclude the grounded reaction", false,
              gameplay::downedReactionBonus(198, 196, true, true));
    checkBool("a non-downed blow reaction never scores", false,
              gameplay::downedReactionBonus(192, 0, true, false));
}

void testReset() {
    std::printf("\n-- reset() == on_enter (scenes.cpp:562-563, 592-593)\n");
    gameplay::MatchEconomy eco = quietEconomy();
    eco.tick(5.0);
    const bool dead[2] = {false, false};
    eco.update(dead);  // dirty the economy before the reset
    eco.reset();

    checkFloat("balloon[0]", 0.0f, eco.balloon(0));
    checkFloat("balloon[1]", 0.0f, eco.balloon(1));
    checkFloat("limit", 100.0f, eco.limit());
    checkFloat("capacity(0) — the default is the scene constructor's 100", 100.0f,
               eco.capacity(0));
    checkFloat("capacity(1)", 100.0f, eco.capacity(1));
    checkFloat("balloonDisplay(0) — FUN_00642c10 zeroes the eased track", 0.0f,
               eco.balloonDisplay(0));
    checkInt("balloonDelta(0)", 0, eco.balloonDelta(0));
    checkInt("balloonDeltaTicks(0)", 0, eco.balloonDeltaTicks(0));
    checkInt("kos(0)/kos(1)", 0, eco.kos(0) + eco.kos(1));
    checkInt("overkills(0)/overkills(1)", 0, eco.overkills(0) + eco.overkills(1));
    checkInt("respawns(0)/respawns(1)", 0, eco.respawns(0) + eco.respawns(1));
    checkBool("timed() — no limit set", false, eco.timed());
    checkDouble("timeLeft() with no limit", 0.0, eco.timeLeft());
    checkDouble("koAt[0]", -1.0, eco.koAt(0));
    checkDouble("koAt[1]", -1.0, eco.koAt(1));
    checkDouble("stingUntil", -1.0, eco.stingUntil());
    checkDouble("elapsed", 0.0, eco.elapsed());
    checkBool("koStingActive() (elapsed 0, stingUntil -1)", false, eco.koStingActive());
    checkBool("roundOver()", false, eco.roundOver());
    checkInt("roundOverSide() (no winner before the round ends)", -1, eco.roundOverSide());
    checkBool("roundEnd()", true, eco.roundEnd() == gameplay::RoundEnd::None);
}

void testOneKo() {
    std::printf("\n-- one KO: 20 + the reaction bonus = 21%%, koAt stamp, 2 s sting\n");
    gameplay::MatchEconomy eco = quietEconomy();
    eco.reset();

    eco.tick(1.0);
    const bool alive[2] = {false, true};
    // The killing blow's reaction moves the victim into the downed reaction, which is
    // the +1 the reference prints (FUN_00639160 @0x639325).
    eco.note_death(0, 0, true, false);
    const gameplay::MatchStepResult r = eco.update(alive);

    checkFloat("balloon[0] after 1 KO", 21.0f, eco.balloon(0));
    checkFloat("balloon[1] untouched", 0.0f, eco.balloon(1));
    checkDouble("koAt[0] == elapsed at the KO", 1.0, eco.koAt(0));
    checkDouble("koAt[1] still -1", -1.0, eco.koAt(1));
    checkDouble("stingUntil == koAt + 2.0", 3.0, eco.stingUntil());
    checkBool("respawned[0]", false, r.respawned[0]);
    checkBool("roundOver", false, r.roundOver);
    checkInt("roundOverSide (no round end yet)", -1, r.roundOverSide);
    checkInt("r.koCredits[0]", 21, r.koCredits[0]);
    checkInt("eco.kos(0)", 1, eco.kos(0));
    checkBool("koStingActive() at the KO instant", true, eco.koStingActive());

    const gameplay::MatchStepResult r2 = eco.update(alive);  // same dead frame again
    checkFloat("balloon[0] after a second dead frame", 21.0f, eco.balloon(0));
    checkDouble("koAt[0] after a second dead frame", 1.0, eco.koAt(0));
    checkInt("the credit is counted once", 1, eco.kos(0));
    checkBool("no respawn inside the 3 s window", false, r2.respawned[0]);

    // A death the scene reports nothing about credits the bare 20: the base literal
    // with no overkill and no reaction bonus.
    gameplay::MatchEconomy bare = quietEconomy();
    bare.reset();
    const gameplay::MatchStepResult rb = bare.update(alive);
    checkFloat("balloon[0] with no note", 20.0f, bare.balloon(0));
    checkInt("r.koCredits[0] with no note", 20, rb.koCredits[0]);

    // The overkill term is the HP the blow drove below zero, in the port's HP units.
    gameplay::MatchEconomy deep = quietEconomy();
    deep.reset();
    deep.note_death(0, 25, false, false);  // melee: 20 + 25/10
    deep.update(alive);
    checkFloat("balloon[0] for a 25-HP melee overkill", 22.0f, deep.balloon(0));

    gameplay::MatchEconomy shot = quietEconomy();
    shot.reset();
    shot.note_death(0, 46, true, true);  // shot: 20 + 5 + 1 + 1 + reaction
    shot.update(alive);
    checkFloat("balloon[0] for a deep shot kill", 28.0f, shot.balloon(0));
}

void testStingWindow() {
    std::printf("\n-- KO sting window: strict elapsed < stingUntil (scenes.cpp:889)\n");
    const bool dead[2] = {false, true};

    gameplay::MatchEconomy a = quietEconomy();
    a.reset();
    a.update(dead);  // KO at elapsed 0.0 -> stingUntil 2.0
    checkDouble("stingUntil (KO at 0.0)", 2.0, a.stingUntil());
    checkBool("at 0.000: active", true, a.koStingActive());
    a.tick(1.0);
    checkBool("at 1.000: active", true, a.koStingActive());
    a.tick(0.5);
    a.tick(0.25);
    a.tick(0.125);
    a.tick(0.0625);  // 1.9375, binary-exact
    checkDouble("elapsed", 1.9375, a.elapsed());
    checkBool("at 1.9375 (just before): active", true, a.koStingActive());
    a.tick(0.0625);  // 2.000 exactly
    checkDouble("elapsed", 2.0, a.elapsed());
    checkBool("at 2.000: NOT active (strict <)", false, a.koStingActive());
    a.tick(1.0);
    checkBool("at 3.000: still not active", false, a.koStingActive());

    gameplay::MatchEconomy b = quietEconomy();
    b.reset();
    b.update(dead);
    b.tick(1.999);
    checkDouble("elapsed (decimal 1.999)", 1.999, b.elapsed());
    checkBool("at 1.999: active", true, b.koStingActive());

    // A later KO re-arms (overwrites) the shared sting window (scenes.cpp:713).
    gameplay::MatchEconomy c = quietEconomy();
    c.reset();
    c.update(dead);  // KO side 0 at 0.0
    c.tick(1.0);
    const bool dead1[2] = {false, false};
    c.update(dead1);  // side 1 dies at 1.0: stingUntil moves 2.0 -> 3.0
    checkDouble("stingUntil re-armed by the second KO", 3.0, c.stingUntil());
    checkBool("sting survives the first KO's expiry", true, c.koStingActive());
}

void testRespawnBoundary() {
    std::printf("\n-- respawn at elapsed - koAt >= 3.0, gated on balloon headroom\n");
    const bool dead[2] = {false, true};

    gameplay::MatchEconomy a = quietEconomy();
    a.reset();
    noteDownedKill(a, 0);
    a.update(dead);  // KO at 0.0
    a.tick(2.999);
    checkDouble("elapsed (2.999)", 2.999, a.elapsed());
    gameplay::MatchStepResult r = a.update(dead);
    checkBool("2.999 s dead: respawned[0]", false, r.respawned[0]);
    checkDouble("koAt[0] still the KO stamp", 0.0, a.koAt(0));
    checkFloat("balloon[0] unchanged while dead", 21.0f, a.balloon(0));
    a.tick(0.001);
    std::printf("  (info) +0.001 s on 2.999 gives elapsed %.17g; >= 3.0 is %s\n",
                a.elapsed(), a.elapsed() >= 3.0 ? "true" : "false");
    r = a.update(dead);
    checkBool("respawn exactly when elapsed - koAt >= 3.0 (no epsilon)", a.elapsed() >= 3.0,
              r.respawned[0]);

    gameplay::MatchEconomy b = quietEconomy();
    b.reset();
    noteDownedKill(b, 0);
    b.update(dead);  // KO at 0.0
    b.tick(3.0);
    checkDouble("elapsed (3.000)", 3.0, b.elapsed());
    r = b.update(dead);
    checkBool("3.000 s dead: respawned[0]", true, r.respawned[0]);
    checkDouble("koAt[0] cleared to -1", -1.0, b.koAt(0));
    checkFloat("balloon[0] keeps the KO's 21%", 21.0f, b.balloon(0));
    checkInt("respawns(0) counted once", 1, b.respawns(0));
    checkBool("respawned is a one-shot flag", false, b.update(dead).respawned[0]);
    checkInt("respawns(0) still once", 1, b.respawns(0));

    // FUN_004219a0 restores nothing while the side has no balloon headroom left
    // (@0x4219aa-0x4219bd), so a bursted side's fighter stays down.
    gameplay::MatchEconomy c = quietEconomy();
    c.reset();
    const int handicap[2] = {40, 100};
    c.set_round_rules(0, handicap);
    noteDownedKill(c, 0);
    c.update(dead);  // 21 < 40
    c.tick(3.0);
    c.update(dead);  // respawn
    noteDownedKill(c, 0);
    const gameplay::MatchStepResult rc = c.update(dead);  // 42 >= 40 -> burst
    checkBool("the 40% handicap bursts on the second KO", true, rc.roundOver);
    checkInt("the other side wins a burst", 1, rc.roundOverSide);
    checkBool("a bursted side does not respawn", false, rc.respawned[0]);
    c.tick(10.0);
    checkBool("still no respawn after the burst", false, c.update(dead).respawned[0]);
}

void testKoAtBookkeeping() {
    std::printf("\n-- koAt bookkeeping across respawns (scenes.cpp:703, 715-719)\n");
    const bool dead[2] = {false, true};
    gameplay::MatchEconomy eco = quietEconomy();
    eco.reset();

    eco.tick(1.0);
    noteDownedKill(eco, 0);
    eco.update(dead);  // first death at 1.0
    checkDouble("koAt[0] after the first death", 1.0, eco.koAt(0));
    checkFloat("balloon[0]", 21.0f, eco.balloon(0));

    eco.tick(3.0);  // 4.0
    gameplay::MatchStepResult r = eco.update(dead);
    checkBool("respawned[0] at 4.0", true, r.respawned[0]);
    checkDouble("koAt[0] back to -1", -1.0, eco.koAt(0));

    eco.tick(0.5);  // 4.5
    noteDownedKill(eco, 0);
    r = eco.update(dead);  // second death
    checkDouble("koAt[0] re-stamped at 4.5", 4.5, eco.koAt(0));
    checkFloat("balloon[0] after 2 KOs", 42.0f, eco.balloon(0));
    checkDouble("stingUntil re-armed to 6.5", 6.5, eco.stingUntil());
    checkBool("respawned[0] on the death frame", false, r.respawned[0]);

    // Quirk pinned from scenes.cpp:703: the just-died branch needs koAt < 0, so a
    // fighter revived by anything other than this 3 s respawn keeps its stale
    // stamp and its next death adds no balloon.
    gameplay::MatchEconomy q = quietEconomy();
    q.reset();
    q.tick(1.0);
    noteDownedKill(q, 0);
    q.update(dead);  // death: koAt 1.0, balloon 21
    const bool alive1[2] = {true, true};
    q.tick(0.5);  // 1.5: still inside the 3 s window
    q.update(alive1);  // out-of-band revive
    checkDouble("koAt[0] survives an out-of-band revive", 1.0, q.koAt(0));
    q.tick(0.5);  // 2.0
    r = q.update(dead);  // dies again while koAt >= 0
    checkFloat("no balloon for that second death", 21.0f, q.balloon(0));
    checkDouble("koAt[0] not re-stamped", 1.0, q.koAt(0));
    checkBool("no respawn flag either", false, r.respawned[0]);
}

void testFiveKosBurst() {
    std::printf("\n-- 21%% per KO, round over at LIMIT (scenes.cpp:705-712)\n");
    const bool dead[2] = {false, true};
    gameplay::MatchEconomy eco = quietEconomy();
    eco.reset();

    for (int k = 1; k <= 5; ++k) {
        eco.tick(1.0);  // alive stretch between deaths
        noteDownedKill(eco, 0);
        const gameplay::MatchStepResult r = eco.update(dead);
        checkFloat(("balloon[0] after KO " + std::to_string(k)).c_str(), 21.0f * k,
                   eco.balloon(0));
        checkBool(("roundOver after KO " + std::to_string(k)).c_str(), k == 5, r.roundOver);
        if (k == 5) {
            checkInt("roundOverSide is the WINNER (the other side)", 1, r.roundOverSide);
            checkBool("the bursted side does not respawn", false, r.respawned[0]);
            checkBool("economy inert after the burst", true, eco.update(dead).roundOver);
            break;
        }
        checkInt(("roundOverSide (no burst at KO " + std::to_string(k) + ")").c_str(), -1,
                 r.roundOverSide);
        eco.tick(3.0);  // dead time
        const gameplay::MatchStepResult rr = eco.update(dead);
        checkBool(("respawned[0] after KO " + std::to_string(k)).c_str(), true,
                  rr.respawned[0]);
    }
    checkFloat("balloon[0] at the burst == 5 * 21", 105.0f, eco.balloon(0));
    checkBool("roundOver() sticky on the economy", true, eco.roundOver());
    checkInt("roundOverSide() sticky", 1, eco.roundOverSide());
    checkBool("roundEnd() is Burst", true, eco.roundEnd() == gameplay::RoundEnd::Burst);
}

void testElapsedAccumulation() {
    std::printf("\n-- elapsed: one += dt per tick (scenes.cpp:610)\n");
    gameplay::MatchEconomy eco = quietEconomy();
    eco.reset();

    const double kDt = 1.0 / 60.0;
    double want = 0.0;
    for (int frame = 0; frame < 600; ++frame) {
        eco.tick(kDt);
        want += kDt;
    }
    checkDouble("elapsed after 600 ticks at 1/60", want, eco.elapsed());
    std::printf("  (info) 600 x 1/60 accumulated = %.17g (exact 10.0 = %.17g), delta %.3g\n",
                eco.elapsed(), 10.0, std::fabs(eco.elapsed() - 10.0));
    checkBool("within 1e-12 of 10 s", true, std::fabs(eco.elapsed() - 10.0) < 1e-12);

    gameplay::MatchEconomy one = quietEconomy();
    one.reset();
    one.tick(kDt);
    checkDouble("one tick stores exactly dt", kDt, one.elapsed());
}

void testSidesIndependent() {
    std::printf("\n-- both sides independent (scenes.cpp:702-721)\n");
    gameplay::MatchEconomy eco = quietEconomy();
    eco.reset();

    eco.tick(1.0);
    bool alive[2] = {false, true};
    noteDownedKill(eco, 0);
    eco.update(alive);  // side 0 dies at 1.0
    checkFloat("balloon[0]", 21.0f, eco.balloon(0));
    checkFloat("balloon[1] untouched by side 0's KO", 0.0f, eco.balloon(1));
    checkDouble("koAt[0]", 1.0, eco.koAt(0));
    checkDouble("koAt[1]", -1.0, eco.koAt(1));

    eco.tick(3.0);  // 4.0
    alive[1] = false;
    noteDownedKill(eco, 1);
    const gameplay::MatchStepResult r = eco.update(alive);
    checkBool("side 0 respawns (3.0 s dead)", true, r.respawned[0]);
    checkBool("side 1 does not respawn (just died)", false, r.respawned[1]);
    checkDouble("koAt[0] cleared", -1.0, eco.koAt(0));
    checkDouble("koAt[1] stamped at 4.0", 4.0, eco.koAt(1));
    checkFloat("balloon[0] keeps side 0's KO", 21.0f, eco.balloon(0));
    checkFloat("balloon[1] gets side 1's KO", 21.0f, eco.balloon(1));

    eco.tick(3.0);  // 7.0
    alive[0] = true;  // side 0 alive again
    eco.update(alive);  // side 1 respawns at 7.0
    checkDouble("koAt[1] cleared at 7.0", -1.0, eco.koAt(1));
    checkFloat("balloon[0] unchanged", 21.0f, eco.balloon(0));

    eco.tick(1.0);  // 8.0
    alive[0] = false;
    alive[1] = true;
    noteDownedKill(eco, 0);
    eco.update(alive);  // side 0 dies a second time
    checkFloat("balloon[0] after side 0's second KO", 42.0f, eco.balloon(0));
    checkFloat("balloon[1] unchanged by side 0", 21.0f, eco.balloon(1));
    checkDouble("koAt[1] stays -1", -1.0, eco.koAt(1));
    checkBool("roundOver never fired (42 / 21 %)", false, eco.roundOver());
}

void testLogStrings() {
    std::printf("\n-- trace strings verbatim (scenes.cpp:706-719)\n");
    checkStr("koLogLine(0, 21, 100)", "KO! side=0 balloon=21% (LIMIT 100%)",
             gameplay::koLogLine(0, 21.0f, 100.0f));
    checkStr("koLogLine(1, 42, 100)", "KO! side=1 balloon=42% (LIMIT 100%)",
             gameplay::koLogLine(1, 42.0f, 100.0f));
    checkStr("koLogLine(0, 105, 100)", "KO! side=0 balloon=105% (LIMIT 100%)",
             gameplay::koLogLine(0, 105.0f, 100.0f));
    checkStr("burstLogLine(0)", "side 0 balloon burst — round over",
             gameplay::burstLogLine(0));
    checkStr("burstLogLine(1)", "side 1 balloon burst — round over",
             gameplay::burstLogLine(1));
    checkStr("respawnLogLine(0)", "side 0 respawned", gameplay::respawnLogLine(0));
    checkStr("respawnLogLine(1)", "side 1 respawned", gameplay::respawnLogLine(1));
    checkStr("overkillLogLine(0, 22, 100, 1)", "Overkill! side=0 +1 balloon=22% (LIMIT 100%)",
             gameplay::overkillLogLine(0, 22.0f, 100.0f, 1));
    checkStr("timeoutLogLine(1, 21, 42, 30, 90)",
             "time up — side 1 wins (balloon 21%/42%, HP 30/90)",
             gameplay::timeoutLogLine(1, 21.0f, 42.0f, 30, 90));

    // The helpers must reproduce the reference's own printf conversions.
    char ref[96];
    std::snprintf(ref, sizeof ref, "KO! side=%d balloon=%.0f%% (LIMIT %.0f%%)", 0, 21.0, 100.0);
    checkStr("koLogLine == the reference format string", ref,
             gameplay::koLogLine(0, 21.0f, 100.0f));
    std::snprintf(ref, sizeof ref, "side %d balloon burst — round over", 1);
    checkStr("burstLogLine == the reference format string", ref,
             gameplay::burstLogLine(1));
    std::snprintf(ref, sizeof ref, "side %d respawned", 1);
    checkStr("respawnLogLine == the reference format string", ref,
             gameplay::respawnLogLine(1));

    // FILE* sink: console lines carry "[daybreak] " and a newline, so a trace
    // diffed against the DX9 console matches byte for byte.
    std::FILE* f = std::tmpfile();
    if (f == nullptr) {
        report("tmpfile() for the trace sink", false, "a FILE*", "nullptr");
        return;
    }
    const bool dead[2] = {false, true};
    gameplay::MatchEconomy eco;
    eco.setLogFile(f);
    eco.reset();
    for (int k = 1; k <= 5; ++k) {
        eco.tick(1.0);
        noteDownedKill(eco, 0);
        eco.update(dead);
        if (k < 5) {
            eco.tick(3.0);
            eco.update(dead);
        }
    }
    std::fflush(f);
    std::rewind(f);
    char got[1024] = {0};
    const size_t n = std::fread(got, 1, sizeof got - 1, f);
    got[n] = '\0';
    std::fclose(f);

    const std::string want =
        "[daybreak] KO! side=0 balloon=21% (LIMIT 100%)\n"
        "[daybreak] side 0 respawned\n"
        "[daybreak] KO! side=0 balloon=42% (LIMIT 100%)\n"
        "[daybreak] side 0 respawned\n"
        "[daybreak] KO! side=0 balloon=63% (LIMIT 100%)\n"
        "[daybreak] side 0 respawned\n"
        "[daybreak] KO! side=0 balloon=84% (LIMIT 100%)\n"
        "[daybreak] side 0 respawned\n"
        "[daybreak] KO! side=0 balloon=105% (LIMIT 100%)\n"
        "[daybreak] side 0 balloon burst — round over\n";
    checkStr("FILE* trace of the whole 5-KO match", want, std::string(got));
    checkInt("trace byte count", static_cast<long long>(want.size()),
             static_cast<long long>(n));
}

// --- issue #11: capacity, timeout, simultaneous outcomes, overkill ---------

void testCapacityExtremes() {
    std::printf("\n-- capacity extremes: the handicap IS the LIMIT\n");
    const bool dead[2] = {false, true};

    // 40% (the settings screen's minimum): two 21% KOs already burst.
    gameplay::MatchEconomy small = quietEconomy();
    small.reset();
    const int smallSizes[2] = {gameplay::kBalloonSizeMin, 100};
    small.set_round_rules(0, smallSizes);
    checkFloat("capacity(0) at the 40% handicap", 40.0f, small.capacity(0));
    checkFloat("limit() is the left corner's capacity", 40.0f, small.limit());
    noteDownedKill(small, 0);
    checkBool("one 21% KO does not burst 40%", false, small.update(dead).roundOver);
    small.tick(3.0);
    small.update(dead);  // respawn
    noteDownedKill(small, 0);
    const gameplay::MatchStepResult rSmall = small.update(dead);
    checkBool("the second 21% KO bursts 40%", true, rSmall.roundOver);
    checkFloat("balloon[0] keeps the raw total (42 > 40)", 42.0f, small.balloon(0));
    checkInt("the bursted side loses", 1, rSmall.roundOverSide);
    checkBool("roundEnd is Burst", true, rSmall.roundEnd == gameplay::RoundEnd::Burst);

    // 200% (the maximum): ten KOs are needed.
    gameplay::MatchEconomy big = quietEconomy();
    big.reset();
    const int bigSizes[2] = {gameplay::kBalloonSizeMax, 100};
    big.set_round_rules(0, bigSizes);
    checkFloat("capacity(0) at the 200% handicap", 200.0f, big.capacity(0));
    for (int k = 1; k <= 9; ++k) {
        noteDownedKill(big, 0);
        const gameplay::MatchStepResult r = big.update(dead);
        checkBool(("no burst at KO " + std::to_string(k) + " of 189%").c_str(), false,
                  r.roundOver);
        big.tick(3.0);
        big.update(dead);
    }
    checkFloat("nine KOs reach 189%", 189.0f, big.balloon(0));
    noteDownedKill(big, 0);
    checkBool("the tenth KO bursts 200%", true, big.update(dead).roundOver);
    checkInt("kos(0) counted ten times", 10, big.kos(0));

    // Out-of-range input clamps; an unset (0) side falls back to 100.
    gameplay::MatchEconomy clamped = quietEconomy();
    clamped.reset();
    const int odd[2] = {20, 0};
    clamped.set_round_rules(0, odd);
    checkFloat("20 clamps up to 40", 40.0f, clamped.capacity(0));
    checkFloat("0 falls back to the 100 default", 100.0f, clamped.capacity(1));
}

void testTimeoutRules() {
    std::printf("\n-- timed round: lower balloon, then HP total, then the generator\n");
    const bool alive[2] = {true, true};
    const int evenSizes[2] = {100, 100};

    // The LOWER balloon wins (FUN_00635d40 @0x636e9c-0x636ee9).
    {
        gameplay::MatchEconomy eco = quietEconomy();
        eco.reset();
        eco.set_round_rules(10, evenSizes);
        checkBool("timed()", true, eco.timed());
        checkDouble("timeLeft() right after the rules", 10.0, eco.timeLeft());
        const bool oneDead[2] = {false, true};
        eco.tick(1.0);
        noteDownedKill(eco, 0);
        eco.update(oneDead);  // side 0 takes a KO
        eco.tick(3.0);
        eco.update(alive);  // side 0 respawns
        checkFloat("balloon[0]", 21.0f, eco.balloon(0));
        eco.tick(6.0);  // elapsed 10.0 -> the limit
        checkDouble("timeLeft() at the limit", 0.0, eco.timeLeft());
        const int hp[2] = {100, 100};
        const gameplay::MatchStepResult r = eco.update(alive, hp);
        checkBool("round over at the limit", true, r.roundOver);
        checkInt("the LOWER balloon wins: side 1", 1, r.roundOverSide);
        checkBool("roundEnd is Timeout", true, r.roundEnd == gameplay::RoundEnd::Timeout);
        checkBool("roundOver() sticky", true, eco.roundOver());
        checkInt("roundOverSide() sticky", 1, eco.roundOverSide());
    }

    // Equal balloons fall through to the HP totals (@0x636ef4-0x636f8a).
    {
        gameplay::MatchEconomy eco = quietEconomy();
        eco.reset();
        eco.set_round_rules(5, evenSizes);
        eco.tick(5.0);
        const int hp0Wins[2] = {80, 40};
        const gameplay::MatchStepResult r = eco.update(alive, hp0Wins);
        checkInt("equal balloons: the higher HP total wins (side 0)", 0, r.roundOverSide);
    }
    {
        gameplay::MatchEconomy eco = quietEconomy();
        eco.reset();
        eco.set_round_rules(5, evenSizes);
        eco.tick(5.0);
        const int hp1Wins[2] = {10, 90};
        checkInt("equal balloons and HP 10/90: side 1 wins", 1,
                 eco.update(alive, hp1Wins).roundOverSide);
    }

    // Balloons and HP both equal: the generator decides, deterministically per seed
    // (@0x636fc4-0x636fce). The same seed must agree; different seeds must be able to
    // disagree, so the tie is not silently biased.
    {
        const int hp[2] = {50, 50};
        gameplay::MatchEconomy a = quietEconomy();
        a.reset();
        a.set_round_rules(5, evenSizes);
        a.set_rng_seed(0x1234567);
        a.tick(5.0);
        const int wa = a.update(alive, hp).roundOverSide;

        gameplay::MatchEconomy b = quietEconomy();
        b.reset();
        b.set_round_rules(5, evenSizes);
        b.set_rng_seed(0x1234567);
        b.tick(5.0);
        const int wb = b.update(alive, hp).roundOverSide;
        checkInt("same seed resolves the same tie", wa, wb);
        checkBool("the tiebreak still produces a side", true, wa == 0 || wa == 1);

        int seen[2] = {0, 0};
        for (uint64_t seed = 1; seed <= 32; ++seed) {
            gameplay::MatchEconomy c = quietEconomy();
            c.reset();
            c.set_round_rules(5, evenSizes);
            c.set_rng_seed(seed);
            c.tick(5.0);
            const int w = c.update(alive, hp).roundOverSide;
            if (w == 0 || w == 1) ++seen[w];
        }
        checkBool("32 seeds produce both outcomes (the RNG is live)", true,
                  seen[0] > 0 && seen[1] > 0);
    }

    // No HP array: the tie still resolves (the generator), never a draw.
    {
        gameplay::MatchEconomy eco = quietEconomy();
        eco.reset();
        eco.set_round_rules(5, evenSizes);
        eco.tick(5.0);
        const gameplay::MatchStepResult r = eco.update(alive);
        checkBool("a tie with no HP array still names a side", true,
                  r.roundOverSide == 0 || r.roundOverSide == 1);
    }

    // The timeout is decided BEFORE any KO bookkeeping of that frame: a fighter that
    // dies on the decision frame is not credited (the original returns from case 2's
    // timeout branch before its per-fighter scan — FUN_00635d40 @0x636e90-0x637079).
    {
        gameplay::MatchEconomy eco = quietEconomy();
        eco.reset();
        eco.set_round_rules(5, evenSizes);
        eco.tick(5.0);
        const bool oneDied[2] = {false, true};
        noteDownedKill(eco, 0);
        const int hp[2] = {0, 100};
        const gameplay::MatchStepResult r = eco.update(oneDied, hp);
        checkBool("the timeout still fires", true, r.roundOver);
        checkInt("no KO credit on the decision frame", 0, r.koCredits[0]);
        checkFloat("balloon[0] unchanged", 0.0f, eco.balloon(0));
        checkInt("kos(0) unchanged", 0, eco.kos(0));
    }

    // A limit of 0 is ∞ (the scene's default, FUN_00633ca0 @0x634432).
    {
        gameplay::MatchEconomy eco = quietEconomy();
        eco.reset();
        eco.set_round_rules(0, evenSizes);
        eco.tick(100000.0);
        checkBool("no limit: never times out", false, eco.update(alive).roundOver);
        checkBool("timed() false", false, eco.timed());
    }
}

void testPerSideLimit() {
    std::printf("\n-- the LIMIT is per side and independent of the timer\n");
    gameplay::MatchEconomy eco = quietEconomy();
    eco.reset();
    const int sizes[2] = {60, 140};
    eco.set_round_rules(0, sizes);
    checkFloat("capacity(0)", 60.0f, eco.capacity(0));
    checkFloat("capacity(1)", 140.0f, eco.capacity(1));
    checkFloat("limit() reports the left corner", 60.0f, eco.limit());

    const bool dead0[2] = {false, true};
    noteDownedKill(eco, 0);
    checkBool("side 0's 21% does not burst its own 60%", false, eco.update(dead0).roundOver);
    const bool dead1[2] = {true, false};
    noteDownedKill(eco, 1);
    const gameplay::MatchStepResult r = eco.update(dead1);
    checkFloat("side 1 sits at 21 of its own 140", 21.0f, eco.balloon(1));
    checkBool("no burst for either side", false, r.roundOver);
    checkInt("kos(0)", 1, eco.kos(0));
    checkInt("kos(1)", 1, eco.kos(1));
}

void testSimultaneousDeaths() {
    std::printf("\n-- simultaneous deaths: every participant credited once\n");
    // 2v2: fighters 0 and 1 on side 0, 2 and 3 on side 1.
    const int side[4] = {0, 0, 1, 1};
    const bool bothDie[4] = {false, true, false, true};

    gameplay::MatchEconomy eco = quietEconomy();
    eco.reset();
    const int sizes[2] = {100, 100};
    eco.set_round_rules(0, sizes);
    noteDownedKill(eco, 0);
    noteDownedKill(eco, 2);
    const gameplay::MatchStepResult r = eco.update(bothDie, side, 4);
    checkFloat("side 0 credited once", 21.0f, eco.balloon(0));
    checkFloat("side 1 credited once", 21.0f, eco.balloon(1));
    checkInt("r.koCredits[0]", 21, r.koCredits[0]);
    checkInt("r.koCredits[2]", 21, r.koCredits[2]);
    checkInt("no credit for the living partners", 0, r.koCredits[1] + r.koCredits[3]);
    checkInt("kos(0) == 1", 1, eco.kos(0));
    checkInt("kos(1) == 1", 1, eco.kos(1));
    checkBool("no round end at 21/21", false, r.roundOver);

    // The same frame again credits nothing new (the koAt stamps hold).
    const gameplay::MatchStepResult again = eco.update(bothDie, side, 4);
    checkFloat("balloon[0] unchanged on the second dead frame", 21.0f, eco.balloon(0));
    checkFloat("balloon[1] unchanged", 21.0f, eco.balloon(1));
    checkInt("kos(0) still 1", 1, eco.kos(0));
    checkBool("no respawn yet", false, again.respawned[0] || again.respawned[2]);

    // Both respawn on the same frame after the KO clock, each on its own side.
    eco.tick(3.0);
    const gameplay::MatchStepResult resp = eco.update(bothDie, side, 4);
    checkBool("fighter 0 respawns", true, resp.respawned[0]);
    checkBool("fighter 2 respawns", true, resp.respawned[2]);
    checkInt("respawns(0)", 1, eco.respawns(0));
    checkInt("respawns(1)", 1, eco.respawns(1));
    checkFloat("the balloons keep their 21s", 42.0f, eco.balloon(0) + eco.balloon(1));
}

void testBothSideBursts() {
    std::printf("\n-- both sides burst in the same frame: the ordering is explicit\n");
    const int side[4] = {0, 0, 1, 1};
    const int sizes[2] = {40, 40};

    // 40% handicaps: one 21% KO each, then a second KO each in the same frame bursts
    // both. The original scans slots 0..3 and each bursting slot overwrites the
    // decision (FUN_00635d40 @0x6370a7-0x637171), so the HIGHEST index decides.
    {
        gameplay::MatchEconomy eco = quietEconomy();
        eco.reset();
        eco.set_round_rules(0, sizes);
        const bool first[4] = {false, true, false, true};
        noteDownedKill(eco, 0);
        noteDownedKill(eco, 2);
        checkBool("the first pair does not burst", false, eco.update(first, side, 4).roundOver);
        eco.tick(3.0);
        eco.update(first, side, 4);  // both respawn
        noteDownedKill(eco, 0);
        noteDownedKill(eco, 2);
        const gameplay::MatchStepResult r = eco.update(first, side, 4);
        checkBool("both sides burst", true, r.roundOver);
        checkInt("the highest bursting index (2, side 1) loses -> side 0 wins", 0,
                 r.roundOverSide);
        checkFloat("side 0 at 42", 42.0f, eco.balloon(0));
        checkFloat("side 1 at 42", 42.0f, eco.balloon(1));
    }

    // Side 0 bursts alone: its own fighter's index decides and the other side wins.
    {
        gameplay::MatchEconomy eco = quietEconomy();
        eco.reset();
        eco.set_round_rules(0, sizes);
        const bool s0dead[4] = {false, false, true, true};
        noteDownedKill(eco, 0);
        noteDownedKill(eco, 1);
        const gameplay::MatchStepResult r = eco.update(s0dead, side, 4);
        checkBool("side 0 bursts on its own (42 >= 40)", true, r.roundOver);
        checkInt("side 1 wins", 1, r.roundOverSide);
    }

    // Side 1 already at 21, then side 1's fighter 3 and side 0's fighter 1 die in the
    // same frame: index 3 is higher, so side 0 wins even though side 0's credit is
    // listed second.
    {
        gameplay::MatchEconomy eco = quietEconomy();
        eco.reset();
        eco.set_round_rules(0, sizes);
        const bool s1first[4] = {true, true, false, true};
        noteDownedKill(eco, 2);
        eco.update(s1first, side, 4);
        eco.tick(3.0);
        eco.update(s1first, side, 4);  // fighter 2 respawns
        checkFloat("side 1 at 21", 21.0f, eco.balloon(1));
        const bool mixed[4] = {false, false, false, true};
        noteDownedKill(eco, 3);
        noteDownedKill(eco, 1);
        const gameplay::MatchStepResult r = eco.update(mixed, side, 4);
        checkBool("both sides over capacity", true, r.roundOver);
        checkInt("index 3 (side 1) decides: side 0 wins", 0, r.roundOverSide);
    }
}

void testOverkillCredits() {
    std::printf("\n-- Overkill: +1 per hit on a body that is already down\n");
    const int side[4] = {0, 0, 1, 1};
    const bool downed[4] = {false, true, true, true};
    gameplay::MatchEconomy eco = quietEconomy();
    eco.reset();
    const int sizes[2] = {100, 100};
    eco.set_round_rules(0, sizes);
    noteDownedKill(eco, 0);
    eco.update(downed, side, 4);  // 21%, koAt stamped
    checkFloat("the KO credit", 21.0f, eco.balloon(0));

    // Three separate hits on the downed body: exactly +1 each, no new KO credit.
    eco.note_overkill_hit(0);
    eco.note_overkill_hit(0);
    eco.note_overkill_hit(0);
    const gameplay::MatchStepResult r = eco.update(downed, side, 4);
    checkFloat("balloon[0] after three overkill hits", 24.0f, eco.balloon(0));
    checkInt("r.overkillCredits[0]", 3, r.overkillCredits[0]);
    checkInt("kos(0) not incremented by overkill", 1, eco.kos(0));
    checkInt("overkills(0)", 3, eco.overkills(0));
    checkInt("no new KO credit", 0, r.koCredits[0]);
    checkDouble("the KO clock is untouched", 0.0, eco.koAt(0));
    checkBool("no respawn from overkill", false, r.respawned[0]);

    // The window closes with the respawn: the fighter is alive again, so a stray
    // overkill note adds nothing.
    eco.tick(3.0);
    const gameplay::MatchStepResult resp = eco.update(downed, side, 4);
    checkBool("respawn after the KO clock", true, resp.respawned[0]);
    checkInt("respawns(0)", 1, eco.respawns(0));
    eco.note_overkill_hit(0);
    const bool allAlive[4] = {true, true, true, true};
    const gameplay::MatchStepResult after = eco.update(allAlive, side, 4);
    checkFloat("an overkill note on a living fighter adds nothing", 24.0f, eco.balloon(0));
    checkInt("no KO credit for the living fighter", 0, after.koCredits[0]);
    checkInt("overkills(0) unchanged", 3, eco.overkills(0));
    checkInt("no overkill credit reported", 0, after.overkillCredits[0]);
    checkInt("and no burst", 0, after.roundOver ? 1 : 0);

    // Overkill can burst the balloon: that is the whole point of the mechanic.
    gameplay::MatchEconomy burst = quietEconomy();
    burst.reset();
    const int small[2] = {40, 100};
    burst.set_round_rules(0, small);
    noteDownedKill(burst, 0);
    burst.update(downed, side);  // 21
    for (int i = 0; i < 19; ++i) burst.note_overkill_hit(0);  // 21 + 19 = 40
    const gameplay::MatchStepResult rb = burst.update(downed, side);
    checkFloat("the overkill hits reach the 40% capacity", 40.0f, burst.balloon(0));
    checkBool("the overkill itself ends the round", true, rb.roundOver);
    checkInt("the downed fighter's side loses", 1, rb.roundOverSide);
    checkInt("the burst is from overkill, not a KO", 0, rb.koCredits[0]);
    checkInt("overkills(0) counted 19", 19, burst.overkills(0));
}

void testCreditAudit() {
    std::printf("\n-- a full match credits every KO exactly once\n");
    const int side[4] = {0, 0, 1, 1};
    gameplay::MatchEconomy eco = quietEconomy();
    eco.reset();
    const int sizes[2] = {100, 100};
    eco.set_round_rules(0, sizes);

    bool alive[4] = {true, true, true, true};
    int deaths[2] = {0, 0};
    // Alternate deaths until the round ends; each death is reported to the economy
    // exactly once by the liveness array, and the audit must match that count.
    for (int round = 0; round < 40 && !eco.roundOver(); ++round) {
        const int victim = (round % 2 == 0) ? 0 : 2;
        alive[victim] = false;
        ++deaths[side[victim]];
        noteDownedKill(eco, victim);
        const gameplay::MatchStepResult r = eco.update(alive, side, 4);
        if (r.roundOver) break;
        eco.tick(3.0);
        const gameplay::MatchStepResult rr = eco.update(alive, side, 4);
        checkBool("the KO'd fighter respawned out of the window", true, rr.respawned[victim]);
        alive[victim] = true;
    }
    checkBool("the match reached a round end", true, eco.roundOver());
    checkInt("kos(0) == the deaths reported for side 0", deaths[0], eco.kos(0));
    checkInt("kos(1) == the deaths reported for side 1", deaths[1], eco.kos(1));
    checkBool("the winner is a real side", true,
              eco.roundOverSide() == 0 || eco.roundOverSide() == 1);
    checkInt("the loser is the side that ran out of balloon",
             1 - eco.roundOverSide(),
             eco.balloon(0) >= eco.capacity(0) ? 0 : 1);
}

void testBalloonPresentation() {
    std::printf("\n-- balloon presentation: the 0.5/frame inflate and the 60-frame popup\n");
    gameplay::MatchEconomy eco = quietEconomy();
    eco.reset();
    const bool dead[2] = {false, true};
    noteDownedKill(eco, 0);
    eco.update(dead);
    checkFloat("the value jumps at once", 21.0f, eco.balloon(0));
    checkFloat("the display starts at 0", 0.0f, eco.balloonDisplay(0));
    // FUN_006431d0 arms a 60-frame readout with the credited amount.
    checkInt("balloonDelta(0) is the credit", 21, eco.balloonDelta(0));

    eco.tick(0.25);
    checkFloat("after one frame the display has moved 0.5", 0.5f, eco.balloonDisplay(0));
    eco.tick(0.25);
    checkFloat("after two frames", 1.0f, eco.balloonDisplay(0));
    for (int i = 0; i < 4; ++i) eco.tick(0.25);
    checkFloat("after six frames", 3.0f, eco.balloonDisplay(0));
    // 42 frames of 0.5% reach 21%.
    for (int i = 0; i < 36; ++i) eco.tick(0.25);
    checkFloat("the display converges on the credited value", 21.0f, eco.balloonDisplay(0));
    for (int i = 0; i < 80; ++i) eco.tick(0.25);
    checkFloat("and stays there", 21.0f, eco.balloonDisplay(0));
}

// --- HUD values ------------------------------------------------------------

void testHudFreshMatch() {
    std::printf("\n-- fillHudValues: fresh match (scenes.cpp:818-893)\n");
    gameplay::MatchEconomy eco = quietEconomy();
    eco.reset();
    gameplay::HudFillInput in;
    in.p1 = freshFighter();

    const game::GameHudValues v = gameplay::fillHudValues(eco, in);
    checkFloat("balloon[0] (left corner)", 0.0f, v.balloon[0]);
    checkFloat("balloon[1] (right corner)", 0.0f, v.balloon[1]);
    checkBool("limit == the economy's", true, v.limit == eco.limit());
    checkFloat("limit", 100.0f, v.limit);
    checkInt("mainWhole", 6, v.mainWhole);
    checkFloat("mainFrac", 1.0f, v.mainFrac);
    checkBool("reloading == !reload_ok", false, v.reloading);
    checkInt("chargeWhole", 2, v.chargeWhole);
    checkFloat("chargeFrac", 1.0f, v.chargeFrac);
    checkBool("holdVisible (C not held)", false, v.holdVisible);
    checkFloat("holdFrac", 0.0f, v.holdFrac);
    checkBool("holdTier Idle", true, v.holdTier == game::HoldTier::Idle);
    checkFloat("hp", 100.0f, v.hp);
    checkStr("hyperName", "FRIENDSHIP", v.hyperName);
    checkFloat("hyperGauge", 0.0f, v.hyperGauge);
    checkBool("hyperActive", false, v.hyperActive);
    checkBool("hyperReady", false, v.hyperReady);
    checkFloat("hyperSecondsLeft", 0.0f, v.hyperSecondsLeft);
    checkRgb("hyperAura", in.p1.hyperAura, v.hyperAura);
    checkBool("staminaVisible", false, v.staminaVisible);
    checkFloat("staminaFrac == stamina/100", 1.0f, v.staminaFrac);
    checkBool("koVisible", false, v.koVisible);
}

void testHudLowHpHighBalloon() {
    std::printf("\n-- fillHudValues: low HP / 84%% balloon / reload / red hold\n");
    const bool dead[2] = {false, true};
    gameplay::MatchEconomy eco = quietEconomy();
    eco.reset();
    for (int k = 1; k <= 4; ++k) {
        eco.tick(1.0);
        noteDownedKill(eco, 0);
        eco.update(dead);  // KO k: balloon 21k
        if (k < 4) {
            eco.tick(3.0);
            eco.update(dead);  // respawn for the next death
        }
    }
    checkFloat("balloon[0] == 4 * 21", 84.0f, eco.balloon(0));
    checkBool("84 < LIMIT: no burst", false, eco.roundOver());
    checkFloat("16 % of LIMIT left before the burst", 16.0f, eco.limit() - eco.balloon(0));

    gameplay::HudFillInput in;
    in.p1 = freshFighter();
    in.p1.hp = 7;
    in.p1.mainWhole = 1;
    in.p1.mainFrac = 0.17f;
    in.p1.reloadOk = false;
    in.p1.chargeWhole = 0;
    in.p1.chargeFrac = 0.05f;
    in.p1.shootHeld = true;
    in.p1.alive = true;
    in.p1.chargeHoldFrac = 0.92f;
    in.p1.chargeTier = game::HoldTier::Red;
    in.p1.stamina = 33;
    in.p1.staminaVisible = true;
    in.p1.hyperName = "OYASHIRO";
    in.p1.hyperGauge = 0.62f;
    in.p1.hyperActive = true;
    in.p1.hyperSecondsLeft = 12.4f;
    in.p1.hyperAura = game::GameRgb{1.0f, 110.f / 255.f, 220.f / 255.f};

    const game::GameHudValues v = gameplay::fillHudValues(eco, in);
    checkFloat("balloon[0] comes from the economy", 84.0f, v.balloon[0]);
    checkFloat("balloon[1] (other side untouched)", 0.0f, v.balloon[1]);
    checkFloat("limit", 100.0f, v.limit);
    checkInt("mainWhole (whole stock left)", 1, v.mainWhole);
    checkFloat("mainFrac raw (fractional, not pre-rounded)", 0.17f, v.mainFrac);
    checkBool("reloading (reload_ok() false -> RELOAD tag)", true, v.reloading);
    checkInt("chargeWhole", 0, v.chargeWhole);
    checkFloat("chargeFrac raw", 0.05f, v.chargeFrac);
    checkBool("holdVisible (C held + alive)", true, v.holdVisible);
    checkFloat("holdFrac raw", 0.92f, v.holdFrac);
    checkBool("holdTier Red", true, v.holdTier == game::HoldTier::Red);
    checkFloat("hp (0..100; the composer divides)", 7.0f, v.hp);
    checkStr("hyperName", "OYASHIRO", v.hyperName);
    checkFloat("hyperGauge raw", 0.62f, v.hyperGauge);
    checkBool("hyperActive", true, v.hyperActive);
    checkFloat("hyperSecondsLeft raw", 12.4f, v.hyperSecondsLeft);
    checkRgb("hyperAura", in.p1.hyperAura, v.hyperAura);
    checkBool("staminaVisible", true, v.staminaVisible);
    checkFloat("staminaFrac == 33/100", 0.33f, v.staminaFrac);
    checkBool("koVisible (4th KO landed this frame: sting running)", true, v.koVisible);

    // Text path: the composer's own conversions on the values filled above
    // (ui/hud.cpp:77-83), which are the reference's printf conversions.
    char text[48];
    std::snprintf(text, sizeof text, "%.0f%%", v.balloon[0]);
    checkStr("left-corner balloon text", "84%", text);
    std::snprintf(text, sizeof text, "LIMIT %.0f%%", v.limit);
    checkStr("left-corner LIMIT text", "LIMIT 100%", text);
    std::snprintf(text, sizeof text, "%s %.0fs", v.hyperName.c_str(), v.hyperSecondsLeft);
    checkStr("hyper active label text (composer's format)", "OYASHIRO 12s", text);

    // 2.0 s after the 4th KO the sting window closes (strict <, scenes.cpp:889).
    eco.tick(2.0);
    checkBool("koVisible 2.0 s after the 4th KO", false,
              gameplay::fillHudValues(eco, in).koVisible);
    checkFloat("balloon[0] unaffected by the wait", 84.0f, eco.balloon(0));
}

void testHudChargeTiers() {
    std::printf("\n-- fillHudValues: charge tiers + hold gate (scenes.cpp:845-853)\n");
    gameplay::MatchEconomy eco = quietEconomy();
    eco.reset();
    gameplay::HudFillInput in;
    in.p1 = freshFighter();
    in.p1.shootHeld = true;
    in.p1.chargeHoldFrac = 0.31f;

    struct Case {
        const char* name;
        game::HoldTier tier;
    };
    const Case cases[3] = {{"tier Idle (below yellow)", game::HoldTier::Idle},
                           {"tier Yellow", game::HoldTier::Yellow},
                           {"tier Red", game::HoldTier::Red}};
    for (const Case& c : cases) {
        in.p1.chargeTier = c.tier;
        const game::GameHudValues v = gameplay::fillHudValues(eco, in);
        checkBool(c.name, true, v.holdTier == c.tier);
        checkFloat((std::string(c.name) + ": holdFrac").c_str(), 0.31f, v.holdFrac);
        checkBool((std::string(c.name) + ": holdVisible (C held + alive)").c_str(), true,
                  v.holdVisible);
    }

    // scenes.cpp:845-846 also gates the meter on is_alive().
    in.p1.alive = false;
    checkBool("dead fighter: meter hidden with C held", false,
              gameplay::fillHudValues(eco, in).holdVisible);
    in.p1.alive = true;
    in.p1.shootHeld = false;
    checkBool("C released: meter hidden", false,
              gameplay::fillHudValues(eco, in).holdVisible);
    checkBool("tier still crosses while hidden (composer draws nothing)", true,
              gameplay::fillHudValues(eco, in).holdTier == game::HoldTier::Red);
}

void testHudHyperAndStamina() {
    std::printf("\n-- fillHudValues: hyper label states, stamina, KO sting\n");
    const bool dead[2] = {false, true};
    gameplay::MatchEconomy eco = quietEconomy();
    eco.reset();
    gameplay::HudFillInput in;
    in.p1 = freshFighter();

    // Active: the composer writes "name %.0fs" in the aura colour (ui/hud.cpp:102-106).
    in.p1.hyperName = "OYASHIRO";
    in.p1.hyperGauge = 1.0f;
    in.p1.hyperActive = true;
    in.p1.hyperReady = false;
    in.p1.hyperSecondsLeft = 14.0f;
    in.p1.hyperAura = game::GameRgb{255.f / 255.f, 110.f / 255.f, 220.f / 255.f};
    game::GameHudValues v = gameplay::fillHudValues(eco, in);
    checkBool("active: hyperActive", true, v.hyperActive);
    checkBool("active: hyperReady false", false, v.hyperReady);
    checkStr("active: hyperName", "OYASHIRO", v.hyperName);
    checkFloat("active: hyperSecondsLeft", 14.0f, v.hyperSecondsLeft);
    checkFloat("active: hyperGauge (drains with the timer)", 1.0f, v.hyperGauge);
    checkRgb("active: aura is the mode aura", in.p1.hyperAura, v.hyperAura);

    // Ready: full gauge, S fires it -> "name  READY (S)" (ui/hud.cpp:107-111).
    in.p1.hyperActive = false;
    in.p1.hyperReady = true;
    in.p1.hyperSecondsLeft = 0.0f;
    v = gameplay::fillHudValues(eco, in);
    checkBool("ready: hyperReady", true, v.hyperReady);
    checkBool("ready: hyperActive false", false, v.hyperActive);
    char text[64];
    std::snprintf(text, sizeof text, "%s  READY (S)", v.hyperName.c_str());
    checkStr("ready label text (two spaces, scenes.cpp:869)", "OYASHIRO  READY (S)", text);

    // Idle: partial gauge -> bare name (ui/hud.cpp:112-116); the composer picks grey.
    in.p1.hyperReady = false;
    in.p1.hyperGauge = 0.37f;
    in.p1.hyperName = "FRIENDSHIP";
    v = gameplay::fillHudValues(eco, in);
    checkBool("idle: neither active nor ready", true, !v.hyperActive && !v.hyperReady);
    checkFloat("idle: hyperGauge raw", 0.37f, v.hyperGauge);
    checkStr("idle label text", "FRIENDSHIP", v.hyperName);

    // Stamina: the caller resolves the Contextual gate (scenes.cpp:879-882).
    in.p1.staminaVisible = false;
    in.p1.stamina = 0;
    v = gameplay::fillHudValues(eco, in);
    checkBool("stamina hidden on the ground", false, v.staminaVisible);
    checkFloat("staminaFrac still crosses", 0.0f, v.staminaFrac);
    in.p1.staminaVisible = true;
    in.p1.stamina = 55;
    v = gameplay::fillHudValues(eco, in);
    checkBool("stamina visible while dashing/guarding/airborne", true, v.staminaVisible);
    checkFloat("staminaFrac == 55/100", 0.55f, v.staminaFrac);

    // KO sting: the flag is the economy's window, true from the KO frame on.
    checkBool("no KO: koVisible false", false, v.koVisible);
    eco.update(dead);  // KO at elapsed 0.0
    v = gameplay::fillHudValues(eco, in);
    checkBool("KO frame: koVisible true", true, v.koVisible);
    eco.tick(1.0);
    checkBool("1.0 s into the sting: koVisible true", true,
              gameplay::fillHudValues(eco, in).koVisible);
    eco.tick(1.0);  // 2.0 == stingUntil
    checkBool("2.0 s after the KO: koVisible false (strict <)", false,
              gameplay::fillHudValues(eco, in).koVisible);
}

void testHudRounding() {
    std::printf("\n-- rounding: raw floats reach the composer's own %%.0f\n");
    // The reference computes the HP bar fill as hp/100.0 (double, scenes.cpp:857)
    // and the composer as hp/100.f (ui/hud.cpp:98). Identical for every legal HP.
    int mismatches = 0;
    for (int hp = 0; hp <= 100; ++hp) {
        const float viaFloat = static_cast<float>(hp) / 100.f;
        const float viaDouble = static_cast<float>(hp / 100.0);
        if (viaFloat != viaDouble) ++mismatches;
    }
    checkInt("hp/100 float vs reference double mismatch count (HP 0..100)", 0, mismatches);

    // Balloon/limit text: no pre-rounding anywhere, so the only "%.0f" is the
    // composer's — the same conversion the reference's printf applied.
    gameplay::MatchEconomy eco = quietEconomy();
    eco.reset();
    gameplay::HudFillInput in;
    in.p1 = freshFighter();
    const game::GameHudValues v = gameplay::fillHudValues(eco, in);
    checkBool("balloon crosses as the raw float", true, v.balloon[0] == eco.balloon(0));

    char composer[32];
    char reference[32];
    for (const float percent : {0.0f, 20.5f, 21.0f, 84.0f, 99.5f, 105.0f}) {
        std::snprintf(composer, sizeof composer, "%.0f%%", percent);
        std::snprintf(reference, sizeof reference, "%.0f%%", static_cast<double>(percent));
        checkStr(("composer text == reference text at " + fmtFloat(percent) + "%").c_str(),
                 reference, composer);
    }
    std::printf("  (info) libc %%.0f on 20.5f -> \"%.0f\" and on 21.5f -> \"%.0f\""
                " (ties-to-even, same call as the reference)\n",
                20.5f, 21.5f);
}

}  // namespace

int main() {
    std::printf("match economy + HUD fill test (no WebGPU, no SDL)\n");

    testConstants();
    testReset();
    testOneKo();
    testStingWindow();
    testRespawnBoundary();
    testKoAtBookkeeping();
    testFiveKosBurst();
    testElapsedAccumulation();
    testSidesIndependent();
    testLogStrings();
    testCapacityExtremes();
    testTimeoutRules();
    testPerSideLimit();
    testSimultaneousDeaths();
    testBothSideBursts();
    testOverkillCredits();
    testCreditAudit();
    testBalloonPresentation();
    testHudFreshMatch();
    testHudLowHpHighBalloon();
    testHudChargeTiers();
    testHudHyperAndStamina();
    testHudRounding();

    std::printf("\nchecks: %d, failures: %d\n", g_checks, g_failed);
    std::printf("MATCH_ECONOMY: %s\n", g_failed == 0 ? "ok" : "FAIL");
    return g_failed == 0 ? 0 : 1;
}
