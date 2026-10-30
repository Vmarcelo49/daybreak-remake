#include "battle/match_economy.h"

#include <algorithm>

namespace gameplay {

std::string koLogLine(int side, float balloon, float limit) {
    char buf[96];
    std::snprintf(buf, sizeof buf, "KO! side=%d balloon=%.0f%% (LIMIT %.0f%%)",
                  side, static_cast<double>(balloon), static_cast<double>(limit));
    return std::string(buf);
}

std::string burstLogLine(int side) {
    char buf[64];
    // Verbatim from scenes.cpp:709, em dash included.
    std::snprintf(buf, sizeof buf, "side %d balloon burst — round over", side);
    return std::string(buf);
}

std::string respawnLogLine(int side) {
    char buf[48];
    std::snprintf(buf, sizeof buf, "side %d respawned", side);
    return std::string(buf);
}

std::string overkillLogLine(int side, float balloon, float limit, int amount) {
    char buf[96];
    std::snprintf(buf, sizeof buf, "Overkill! side=%d +%d balloon=%.0f%% (LIMIT %.0f%%)",
                  side, amount, static_cast<double>(balloon), static_cast<double>(limit));
    return std::string(buf);
}

std::string timeoutLogLine(int winner, float balloon0, float balloon1, int hp0, int hp1) {
    char buf[112];
    std::snprintf(buf, sizeof buf,
                  "time up — side %d wins (balloon %.0f%%/%.0f%%, HP %d/%d)",
                  winner, static_cast<double>(balloon0), static_cast<double>(balloon1), hp0,
                  hp1);
    return std::string(buf);
}

void MatchEconomy::reset() {
    // FUN_00634760 (0x634760) is the battle reset: it clears the balloon values
    // (@0x634815-0x634828 via FUN_00642c10), the per-side display track, the winner
    // (scene+0x442c/@0x634790), the phase counter and the KO timers, and rebuilds the
    // countdown from the limit (@0x6347d1-0x6347dd).
    m_balloon[0] = m_balloon[1] = 0.0f;  // scenes.cpp:562
    for (int i = 0; i < kSideCount; ++i) {
        m_balloonDisplay[i] = 0.0f;  // FUN_00642c10 @0x642c10
        m_balloonDelta[i] = 0;
        m_balloonDeltaTicks[i] = 0;
        m_kos[i] = m_overkills[i] = m_respawns[i] = 0;
    }
    for (double& koAt : m_koAt) koAt = -1.0;  // scenes.cpp:563; port extension tracks each panel
    for (DeathNote& n : m_death) n = DeathNote{};
    for (int& hits : m_overkillHits) hits = 0;
    m_elapsed = 0.0;      // scenes.cpp:592
    m_stingUntil = -1.0;  // scenes.cpp:593
    m_roundOver = false;
    m_roundOverSide = -1;
    m_roundEnd = RoundEnd::None;
    m_timeLeft = m_timeLimit > 0 ? static_cast<double>(m_timeLimit) : 0.0;
}

void MatchEconomy::set_round_rules(int timeLimit, const int balloonSize[2]) {
    m_timeLimit = timeLimit > 0 ? timeLimit : 0;
    m_timeLeft = static_cast<double>(m_timeLimit);
    for (int i = 0; i < kSideCount; ++i) {
        // The settings screen steps the capacity by 20 within 40..200 and WRAPS at the
        // ends (FUN_0040acb0 @0x40af57-0x40afe2); the simulation clamps instead, so a
        // caller cannot inherit a wrap that would silently give a side 200% for asking
        // for 20%. Out-of-range and unset values fall back to the 100 default
        // (FUN_00633ca0 @0x634442-0x634452).
        int size = balloonSize[i];
        if (size <= 0) size = static_cast<int>(kBalloonLimit);
        m_capacity[i] = static_cast<float>(std::min(std::max(size, kBalloonSizeMin),
                                                    kBalloonSizeMax));
    }
}

void MatchEconomy::tick(double dt) {
    m_elapsed += dt;  // scenes.cpp:610
    if (m_timeLimit > 0) m_timeLeft -= dt;
    // FUN_006430f0 (0x6430f0), once per frame: the delta readout's 60-frame timer
    // counts down, and the displayed value eases toward the credited one by 0.5.
    for (int i = 0; i < kSideCount; ++i) {
        if (m_balloonDeltaTicks[i] > 0) --m_balloonDeltaTicks[i];
        if (m_balloonDisplay[i] < m_balloon[i]) {
            m_balloonDisplay[i] = std::min(m_balloonDisplay[i] + 0.5f, m_balloon[i]);
        } else if (m_balloon[i] < m_balloonDisplay[i]) {
            m_balloonDisplay[i] = std::max(m_balloonDisplay[i] - 0.5f, m_balloon[i]);
        }
    }
}

void MatchEconomy::note_death(int fighter, int overkillHp, bool reactionBonus, bool shot) {
    if (fighter < 0 || fighter >= kMatchFighterCount) return;
    DeathNote& n = m_death[fighter];
    n.armed = true;
    n.overkillHp = overkillHp > 0 ? overkillHp : 0;
    n.reactionBonus = reactionBonus;
    n.shot = shot;
}

void MatchEconomy::note_overkill_hit(int fighter) {
    if (fighter < 0 || fighter >= kMatchFighterCount) return;
    ++m_overkillHits[fighter];
}

bool MatchEconomy::sideHpTotals(const bool alive[kMatchFighterCount],
                                const int side[kMatchFighterCount], int fighterCount,
                                const int hp[kMatchFighterCount],
                                int out[kSideCount]) const {
    if (hp == nullptr) return false;
    out[0] = out[1] = 0;
    for (int i = 0; i < fighterCount; ++i) {
        const int team = side[i];
        if (team < 0 || team >= kSideCount) continue;
        // A dead fighter has no HP left; the original's own sum reads a clamped field
        // (0 after the KO branch), so the liveness gate is a no-op there and keeps a
        // caller that reports raw HP honest.
        out[team] += alive[i] ? hp[i] : 0;
    }
    return true;
}

MatchStepResult MatchEconomy::update(const bool alive[kSideCount], const int hp[kSideCount]) {
    // The 1v1 reference maps one fighter per side; the wide form still receives the
    // arrays so its slot loop and the HP sums are the same code path.
    bool wide[kMatchFighterCount];
    int side[kMatchFighterCount];
    int wideHp[kMatchFighterCount];
    for (int i = 0; i < kMatchFighterCount; ++i) {
        wide[i] = i < kSideCount ? alive[i] : true;
        side[i] = i < kSideCount ? i : -1;
        wideHp[i] = (hp != nullptr && i < kSideCount) ? hp[i] : 0;
    }
    return updateImpl(wide, side, kSideCount, hp != nullptr ? wideHp : nullptr);
}

MatchStepResult MatchEconomy::update(const bool alive[kMatchFighterCount],
                                     const int side[kMatchFighterCount], int fighterCount,
                                     const int hp[kMatchFighterCount]) {
    return updateImpl(alive, side, fighterCount, hp);
}

MatchStepResult MatchEconomy::updateImpl(const bool alive[kMatchFighterCount],
                                        const int side[kMatchFighterCount], int fighterCount,
                                        const int hp[kMatchFighterCount]) {
    MatchStepResult r;
    if (m_roundOver) {
        r.roundOver = true;
        r.roundOverSide = m_roundOverSide;
        r.roundEnd = m_roundEnd;
        return r;
    }

    // 1. The timed round, decided BEFORE any KO bookkeeping — FUN_00635d40 gates on the
    //    limit being set (@0x636df1-0x636dfe) and on the countdown having reached zero
    //    (@0x636e04-0x636e11), then compares balloons lower-first, then the HP totals,
    //    then the generator (@0x636e90-0x636fd0). No branch leaves the winner unset.
    if (m_timeLimit > 0 && m_timeLeft <= 0.0) {
        int hpTotal[kSideCount] = {0, 0};
        const bool haveHp = sideHpTotals(alive, side, fighterCount, hp, hpTotal);
        int winner;
        if (m_balloon[0] < m_balloon[1]) {
            winner = 0;
        } else if (m_balloon[1] < m_balloon[0]) {
            winner = 1;
        } else if (haveHp && hpTotal[0] != hpTotal[1]) {
            winner = hpTotal[0] > hpTotal[1] ? 0 : 1;
        } else {
            winner = m_rng.below(kSideCount);
        }
        m_roundOver = true;
        m_roundOverSide = winner;
        m_roundEnd = RoundEnd::Timeout;
        r.roundOver = true;
        r.roundOverSide = winner;
        r.roundEnd = RoundEnd::Timeout;
        log(timeoutLogLine(winner, m_balloon[0], m_balloon[1], hpTotal[0], hpTotal[1]));
        return r;
    }

    // 2. Credits and respawns, every participant in one pass. The original scans the
    //    KO'd fighters in slot order and lets each one whose side has run out of
    //    balloon headroom overwrite the decision (FUN_00635d40 @0x6370a7-0x6371b8),
    //    so when two sides reach their capacity in the same frame the LAST slot in
    //    index order decides. That is made explicit here — the winner comes from the
    //    highest participating index, never from the order this loop happens to run.
    int burstParticipant = -1;
    if (fighterCount > kMatchFighterCount) fighterCount = kMatchFighterCount;
    for (int i = 0; i < fighterCount; ++i) {
        const int team = side[i];
        if (team < 0 || team >= kSideCount) continue;
        const bool dead = !alive[i];

        if (dead && m_koAt[i] < 0.0) {
            // Just died: credit the VICTIM's own side (FUN_00639650's caller passes
            // [victim+0xc], i.e. the victim's balloon entry). The increment is 20 plus
            // the killing blow's overkill and reaction terms when the scene reported
            // them, and the bare 20 otherwise.
            const DeathNote& n = m_death[i];
            const int amount = koIncrementPercent(n.armed ? n.overkillHp : 0,
                                                  n.armed && n.reactionBonus,
                                                  n.armed && n.shot);
            m_koAt[i] = m_elapsed;
            m_balloon[team] += static_cast<float>(amount);
            ++m_kos[team];
            r.koCredits[i] = amount;
            // FUN_006431d0 @0x6431d0 arms the "+N%" readout with the credit and a
            // 60-frame window.
            m_balloonDelta[team] = amount;
            m_balloonDeltaTicks[team] = kBalloonDeltaTicks;
            log(koLogLine(team, m_balloon[team], m_capacity[team]));
            // The KO presentation window is armed only while the side still has
            // headroom (FUN_00635d40 @0x637173-0x6371b8). The original re-arms its
            // per-fighter 0x5a-frame timer every frame the fighter stays down and uses
            // 0x78 on this credit frame only; the port keeps one shared window of
            // kKoStingSec and does not model the 0x78 respawn presentation.
            if (!balloonBursts(m_balloon[team], m_capacity[team])) {
                m_stingUntil = m_elapsed + kKoStingSec;
            }
        }
        // Overkill: each hit on a body that is already down credits +1 to that body's
        // side (FUN_00637950 @0x638e0d-0x638e37: `local_90 + 1`, and local_90 is 0 for
        // an already-dead victim because its reaction set is excluded).
        if (dead && m_overkillHits[i] > 0) {
            const int hits = m_overkillHits[i];   // exactly +1 balloon per hit
            m_balloon[team] += static_cast<float>(hits);
            m_overkills[team] += hits;
            r.overkillCredits[i] = hits;
            m_balloonDelta[team] = hits;
            m_balloonDeltaTicks[team] = kBalloonDeltaTicks;
            log(overkillLogLine(team, m_balloon[team], m_capacity[team], hits));
        }

        if (dead && balloonBursts(m_balloon[team], m_capacity[team])) {
            burstParticipant = i;
            continue;  // a bursted side does not respawn (FUN_004219a0's gate)
        }
        if (dead && m_koAt[i] >= 0.0 && m_elapsed - m_koAt[i] >= kRespawnSec) {
            // FUN_004219a0 restores nothing while `capacity - balloon < 1`
            // (@0x4219aa-0x4219bd); the burst branch above is that same gate.
            r.respawned[i] = true;
            m_koAt[i] = -1.0;
            ++m_respawns[team];
            log(respawnLogLine(team));
        }
    }

    if (burstParticipant >= 0) {
        // The loser is the deciding participant's side; the winner is the other one.
        const int loser = side[burstParticipant];
        m_roundOver = true;
        m_roundOverSide = 1 - loser;
        m_roundEnd = RoundEnd::Burst;
        r.roundOver = true;
        r.roundOverSide = m_roundOverSide;
        r.roundEnd = RoundEnd::Burst;
        log(burstLogLine(loser));
    }

    // The notes are one-frame events: a death or hit that update() did not consume is
    // dropped rather than credited later against an unrelated frame.
    for (DeathNote& n : m_death) n = DeathNote{};
    for (int& hits : m_overkillHits) hits = 0;
    return r;
}

void MatchEconomy::log(const std::string& line) {
    if (!m_log) return;
    std::fprintf(m_log, "%s%s\n", kTracePrefix, line.c_str());
}

}  // namespace gameplay
