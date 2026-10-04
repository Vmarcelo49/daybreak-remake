#pragma once
// Match economy (spec §3.5): per-side balloon %, the shared LIMIT, the KO clock
// and the KO sting — the state Scene_Gameplay keeps as m_balloon[2], m_limit,
// m_koAt[2], m_stingUntil and advances in its update() bookkeeping block
// (remake/src/core/scenes.cpp:701-721; reset at 562-563 and 592-593). Lifted
// out of the DX9 scene so the SDL3+WebGPU path runs and host-tests it with no
// device, and so the HUD values become a pure function of economy + fighters.
//
// Default rules preserve the reference's quirks; the front end additionally
// supplies a time limit and per-side balloon capacity. A caller inherits both:
//  * "just died" keys off koAt[i] < 0 (scenes.cpp:703), so a fighter revived by
//    anything other than this 3 s respawn keeps its stale koAt and its next
//    death adds no balloon;
//  * a burst returns UpdateResult::Transition on the spot (scenes.cpp:708-712),
//    so the other side's bookkeeping is skipped for that frame. update()
//    reproduces that early exit and reports it as roundOver; the caller must
//    transition and drop the rest of the frame.
// std only: no SDL, no WebGPU, no glm.
#include <cstdio>
#include <string>

namespace gameplay {

// Two sides, +21% balloon per KO, LIMIT 100% (spec §3.5; scenes.cpp:705, 708).
inline constexpr int    kSideCount    = 2;
inline constexpr int    kMatchFighterCount = 4;
inline constexpr float  kBalloonPerKo = 21.0f;
inline constexpr float  kBalloonLimit = 100.0f;
inline constexpr double kKoStingSec   = 2.0;  // "KO!" sting (ASCII stand-in)
inline constexpr double kRespawnSec   = 3.0;  // dead time before Fighter::reset

// scenes.cpp:708: the side loses when the balloon REACHES the LIMIT, not past
// it. Lifted as the predicate update() calls so the boundary is testable.
inline constexpr bool balloonBursts(float balloon, float limit) {
    return balloon >= limit;
}

// The reference's trace prefix (scenes.cpp:706-719). The *LogLine helpers below
// return the bare message; lines written through MatchEconomy::logFile() carry
// the prefix, so a trace diffed against the DX9 console matches byte for byte.
inline constexpr const char* kTracePrefix = "[daybreak] ";

// Exact formatted trace strings: the reference's own printf conversions (float
// promoted to double, "%.0f"), so the text matches to the digit.
std::string koLogLine(int side, float balloon, float limit);
std::string burstLogLine(int side);
std::string respawnLogLine(int side);

// What one update() step asks the caller to apply: Fighter::reset(spawnPos,
// facing) for a respawned side (the economy owns no positions), and the
// round-over transition.
struct MatchStepResult {
    bool respawned[kMatchFighterCount] = {false, false, false, false};
    bool roundOver = false;
    int  roundOverSide = -1;
};

class MatchEconomy {
public:
    MatchEconomy() = default;
    // Trace sink; stdout keeps the reference's console output, nullptr silences.
    explicit MatchEconomy(std::FILE* log) : m_log(log) {}

    // Scene_Gameplay::on_enter (scenes.cpp:562-563, 592-593). m_limit is NOT
    // reset — on_enter does not touch it either (member initializer, scenes.h:184).
    void reset();
    void set_round_rules(int timeLimit, const int balloonSize[2]);

    // One frame of the clock, exactly scenes.cpp:610. Call once per frame,
    // before update().
    void tick(double dt);

    // The bookkeeping block (scenes.cpp:701-721), side 0 then side 1: a fighter
    // that just died stamps koAt[i] = elapsed, adds the capacity-adjusted KO
    // increment (21% at default capacity) and arms the 2 s
    // sting; at or past LIMIT the round is over; a dead fighter 3 s past its KO
    // respawns (reported in the result, koAt back to -1).
    //
    // Inert once roundOver(): a burst ends the DX9 frame by transitioning
    // (scenes.cpp:710-711), so no post-burst frame exists in the reference —
    // pinning that keeps a caller which ignores roundOver from inventing one.
    MatchStepResult update(const bool alive[kSideCount]);
    MatchStepResult update(const bool alive[kMatchFighterCount], const int side[kMatchFighterCount]);

    // --- state the flow and the HUD read back ---
    float  balloon(int side) const { return m_balloon[side]; }
    float  limit() const { return m_limit; }
    double koAt(int fighter) const { return m_koAt[fighter]; }  // -1 = alive
    double stingUntil() const { return m_stingUntil; }    // -1 = never stung
    double elapsed() const { return m_elapsed; }
    // scenes.cpp:889 (m_elapsed < m_stingUntil): strict, so the sting is gone
    // exactly at stingUntil.
    bool   koStingActive() const { return m_elapsed < m_stingUntil; }
    bool   roundOver() const { return m_roundOver; }
    int    roundOverSide() const { return m_roundOverSide; }

    std::FILE* logFile() const { return m_log; }
    void setLogFile(std::FILE* f) { m_log = f; }

private:
    void log(const std::string& line);

    float  m_balloon[kSideCount] = {0.0f, 0.0f};
    float  m_limit = kBalloonLimit;
    float  m_koIncrement[2] = {kBalloonPerKo, kBalloonPerKo};
    int    m_timeLimit = 0;
    double m_koAt[kMatchFighterCount] = {-1.0, -1.0, -1.0, -1.0};
    double m_stingUntil = -1.0;
    double m_elapsed = 0.0;
    // No reference counterpart: DX9 leaves the scene on the burst frame.
    bool   m_roundOver = false;
    int    m_roundOverSide = -1;
    std::FILE* m_log = stdout;
};

}  // namespace gameplay
