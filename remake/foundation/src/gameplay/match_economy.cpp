#include "gameplay/match_economy.h"

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

void MatchEconomy::reset() {
    m_balloon[0] = m_balloon[1] = 0.0f;  // scenes.cpp:562
    m_koAt[0] = m_koAt[1] = -1.0;        // scenes.cpp:563
    m_elapsed = 0.0;                     // scenes.cpp:592
    m_stingUntil = -1.0;                 // scenes.cpp:593
    m_roundOver = false;
    m_roundOverSide = -1;
}

void MatchEconomy::tick(double dt) {
    m_elapsed += dt;  // scenes.cpp:610
}

MatchStepResult MatchEconomy::update(const bool alive[kSideCount]) {
    MatchStepResult r;
    if (m_roundOver) {
        r.roundOver = true;
        r.roundOverSide = m_roundOverSide;
        return r;
    }
    for (int i = 0; i < kSideCount; ++i) {
        if (!alive[i] && m_koAt[i] < 0.0) {
            m_koAt[i] = m_elapsed;
            m_balloon[i] += kBalloonPerKo;
            log(koLogLine(i, m_balloon[i], m_limit));
            if (balloonBursts(m_balloon[i], m_limit)) {
                log(burstLogLine(i));
                m_roundOver = true;
                m_roundOverSide = i;
                r.roundOver = true;
                r.roundOverSide = i;
                return r;  // the reference returns UpdateResult::Transition here
            }
            m_stingUntil = m_elapsed + kKoStingSec;
        }
        if (!alive[i] && m_koAt[i] >= 0.0 && m_elapsed - m_koAt[i] >= kRespawnSec) {
            r.respawned[i] = true;
            m_koAt[i] = -1.0;
            log(respawnLogLine(i));
        }
    }
    return r;
}

void MatchEconomy::log(const std::string& line) {
    if (!m_log) return;
    std::fprintf(m_log, "%s%s\n", kTracePrefix, line.c_str());
}

}  // namespace gameplay
