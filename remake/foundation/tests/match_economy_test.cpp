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
    std::printf("\n-- constants (scenes.cpp:705-716; spec §3.5)\n");
    checkInt("kSideCount", 2, gameplay::kSideCount);
    checkFloat("kBalloonPerKo", 21.0f, gameplay::kBalloonPerKo);
    checkFloat("kBalloonLimit", 100.0f, gameplay::kBalloonLimit);
    checkDouble("kKoStingSec", 2.0, gameplay::kKoStingSec);
    checkDouble("kRespawnSec", 3.0, gameplay::kRespawnSec);
    // scenes.cpp:708 compares >=, so LIMIT itself already bursts.
    checkBool("balloonBursts(100, 100) — the LIMIT itself bursts", true,
              gameplay::balloonBursts(100.0f, 100.0f));
    checkBool("balloonBursts(99.999, 100)", false, gameplay::balloonBursts(99.999f, 100.0f));
    checkBool("balloonBursts(84, 100) — four KOs do not burst", false,
              gameplay::balloonBursts(84.0f, 100.0f));
    checkBool("balloonBursts(105, 100)", true, gameplay::balloonBursts(105.0f, 100.0f));
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
    checkDouble("koAt[0]", -1.0, eco.koAt(0));
    checkDouble("koAt[1]", -1.0, eco.koAt(1));
    checkDouble("stingUntil", -1.0, eco.stingUntil());
    checkDouble("elapsed", 0.0, eco.elapsed());
    checkBool("koStingActive() (elapsed 0, stingUntil -1)", false, eco.koStingActive());
    checkBool("roundOver()", false, eco.roundOver());
    checkInt("roundOverSide()", -1, eco.roundOverSide());
}

void testOneKo() {
    std::printf("\n-- one KO: +21%%, koAt stamp, 2 s sting (scenes.cpp:703-713)\n");
    gameplay::MatchEconomy eco = quietEconomy();
    eco.reset();

    eco.tick(1.0);
    const bool alive[2] = {false, true};
    const gameplay::MatchStepResult r = eco.update(alive);

    checkFloat("balloon[0] after 1 KO", 21.0f, eco.balloon(0));
    checkFloat("balloon[1] untouched", 0.0f, eco.balloon(1));
    checkDouble("koAt[0] == elapsed at the KO", 1.0, eco.koAt(0));
    checkDouble("koAt[1] still -1", -1.0, eco.koAt(1));
    checkDouble("stingUntil == koAt + 2.0", 3.0, eco.stingUntil());
    checkBool("respawned[0]", false, r.respawned[0]);
    checkBool("roundOver", false, r.roundOver);
    checkInt("roundOverSide", -1, r.roundOverSide);
    checkBool("koStingActive() at the KO instant", true, eco.koStingActive());

    const gameplay::MatchStepResult r2 = eco.update(alive);  // same dead frame again
    checkFloat("balloon[0] after a second dead frame", 21.0f, eco.balloon(0));
    checkDouble("koAt[0] after a second dead frame", 1.0, eco.koAt(0));
    checkBool("no respawn inside the 3 s window", false, r2.respawned[0]);
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
    std::printf("\n-- respawn at elapsed - koAt >= 3.0 (scenes.cpp:715-720)\n");
    const bool dead[2] = {false, true};

    gameplay::MatchEconomy a = quietEconomy();
    a.reset();
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
    b.update(dead);  // KO at 0.0
    b.tick(3.0);
    checkDouble("elapsed (3.000)", 3.0, b.elapsed());
    r = b.update(dead);
    checkBool("3.000 s dead: respawned[0]", true, r.respawned[0]);
    checkDouble("koAt[0] cleared to -1", -1.0, b.koAt(0));
    checkFloat("balloon[0] keeps the KO's 21%", 21.0f, b.balloon(0));
    checkBool("respawned is a one-shot flag", false, b.update(dead).respawned[0]);
}

void testKoAtBookkeeping() {
    std::printf("\n-- koAt bookkeeping across respawns (scenes.cpp:703, 715-719)\n");
    const bool dead[2] = {false, true};
    gameplay::MatchEconomy eco = quietEconomy();
    eco.reset();

    eco.tick(1.0);
    eco.update(dead);  // first death at 1.0
    checkDouble("koAt[0] after the first death", 1.0, eco.koAt(0));
    checkFloat("balloon[0]", 21.0f, eco.balloon(0));

    eco.tick(3.0);  // 4.0
    gameplay::MatchStepResult r = eco.update(dead);
    checkBool("respawned[0] at 4.0", true, r.respawned[0]);
    checkDouble("koAt[0] back to -1", -1.0, eco.koAt(0));

    eco.tick(0.5);  // 4.5
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
        const gameplay::MatchStepResult r = eco.update(dead);
        checkFloat(("balloon[0] after KO " + std::to_string(k)).c_str(), 21.0f * k,
                   eco.balloon(0));
        checkBool(("roundOver after KO " + std::to_string(k)).c_str(), k == 5, r.roundOver);
        if (k == 5) {
            checkInt("roundOverSide", 0, r.roundOverSide);
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
    checkInt("roundOverSide() sticky", 0, eco.roundOverSide());
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
    eco.update(alive);  // side 0 dies at 1.0
    checkFloat("balloon[0]", 21.0f, eco.balloon(0));
    checkFloat("balloon[1] untouched by side 0's KO", 0.0f, eco.balloon(1));
    checkDouble("koAt[0]", 1.0, eco.koAt(0));
    checkDouble("koAt[1]", -1.0, eco.koAt(1));

    eco.tick(3.0);  // 4.0
    alive[1] = false;
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
    testHudFreshMatch();
    testHudLowHpHighBalloon();
    testHudChargeTiers();
    testHudHyperAndStamina();
    testHudRounding();

    std::printf("\nchecks: %d, failures: %d\n", g_checks, g_failed);
    std::printf("MATCH_ECONOMY: %s\n", g_failed == 0 ? "ok" : "FAIL");
    return g_failed == 0 ? 0 : 1;
}
