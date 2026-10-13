#pragma once

#include <array>
#include <utility>

namespace gameplay {

// FUN_0041dcb0 seeds fifteen zero input samples; FUN_0041efe0 pushes the current
// source-axis pair and scans each cardinal direction independently, with later matches
// winning. Callers translate input axes to the original's sign convention (forward z=-1).
class DashHistory {
public:
    static constexpr unsigned kSamples = 15;

    unsigned push(int x, int z) {
        std::move(m_frames.begin() + 1, m_frames.end(), m_frames.begin());
        m_frames.back() = {x, z};
        unsigned command = 0;
        for (unsigned dir = 1; dir <= 4; ++dir) {
            const unsigned axis = dir <= 2 ? 1u : 0u;
            const int sign = (dir == 1 || dir == 3) ? -1 : 1;
            unsigned stage = 0;
            for (const auto& frame : m_frames) {
                if (frame[axis] == sign && stage == 2) command = dir;
                else if (frame[axis] == 0 && stage == 1) stage = 2;
                else if (frame[axis] == sign && stage == 0) stage = 1;
            }
        }
        return command;
    }

    void reset() { m_frames = {}; }

private:
    std::array<std::array<int, 2>, kSamples> m_frames{};
};

} // namespace gameplay
