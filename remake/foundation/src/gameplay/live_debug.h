#pragma once

#include "gameplay/match.h"
#include <deque>
#include <string>

namespace gameplay {

// Development instrumentation owns no game clock: the host grants one tick at a
// time and reports completion only after presenting the resulting authoritative pose.
class LiveDebug {
public:
    ~LiveDebug();
    bool start(std::string& error);
    void poll(uint64_t tick, uint64_t renders, const Match& match);
    bool enabled() const { return m_socket >= 0; }
    bool stop_requested() const { return m_stop; }
    bool paused() const { return m_paused; }
    bool wants_tick() const { return !m_paused || m_budget > 0; }
    bool stepping() const { return m_budget > 0; }
    bool evidence_pending() const { return m_pending && m_budget == 0; }
    std::string evidence_path(uint64_t tick) const { return m_directory + "/tick-" + std::to_string(tick) + ".ppm"; }
    void inputs(uint64_t tick, const fnd::input::PlayerState* out[4]);
    void after_tick(uint64_t tick, const Match& match, const MatchFrame& frame);
    void presented(uint64_t tick, uint64_t renders, const Match& match);
    const std::string& directory() const { return m_directory; }
    std::string snapshot(uint64_t tick, uint64_t renders, const Match& match) const;
private:
    struct Event { uint64_t tick; int fighter; uint32_t mask; };
    struct Break { std::string kind; int fighter; int value; int character; int weapon; };
    void disconnect();
    void reply(const std::string& text);
    void command(const std::string& line, uint64_t tick, uint64_t renders, const Match& match);
    int m_socket = -1, m_client = -1;
    std::string m_directory, m_token, m_buffer;
    bool m_authenticated = false, m_paused = true, m_pending = false, m_stop = false;
    uint64_t m_budget = 0, m_effectTick = 0;
    std::string m_reason;
    std::deque<Event> m_events;
    std::vector<Break> m_breaks;
    fnd::input::PlayerState m_inputs[4]{};
    MatchFrame m_frame{};
    int m_state[4]{-1,-1,-1,-1}, m_move[4]{-1,-1,-1,-1}, m_set[4]{-1,-1,-1,-1}, m_phase[4]{-1,-1,-1,-1};
};
}
