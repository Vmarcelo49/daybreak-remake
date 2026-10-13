#pragma once

#include <array>
#include <cstdint>

namespace gameplay {

// The original's random stream, recovered from the binary rather than invented.
//
// FUN_0065d150 is the standard MT19937 tempering over a 624-word state: the twist reads
// mt[i+397] for i < 227 and mt[i-227] for the tail (`DAT_006d3804` and `DAT_006d2e44`
// are mt+397*4 and mt-227*4), selects the 0x9908b0df matrix word through the two-entry
// table at `DAT_006b77c0` by the low bit, and tempers with the canonical
// >>11, (<<7)&0x9d2c5680, (<<15)&0xefc60000, >>18 masks. FUN_0065d0c0 is init_genrand
// (`state[i] = 1812433253 * (state[i-1] ^ (state[i-1] >> 30)) + i`) and the re-seed path
// calls it with 0x1571, which is 5489 — MT19937's own default seed.
//
// Reproducing the algorithm is what lets the port match the bodies' *distribution, draw
// order and modulo ranges*; stream position still cannot match, because the original
// draws from one global stream in its own frame order and the port does not attempt
// bit-parity (AGENTS.md). Determinism here means "same seed, same spread sequence".
class SimulationRng {
public:
    static constexpr std::uint32_t kDefaultSeed = 5489u;  // FUN_0065d0c0's 0x1571
    static constexpr std::uint32_t kStateWords = 624u;
    static constexpr std::uint32_t kMiddleWord = 397u;

    SimulationRng() { reset(); }

    void seed(std::uint32_t value) {
        m_state[0] = value;
        for (std::uint32_t i = 1; i < kStateWords; ++i)
            m_state[i] = 1812433253u * (m_state[i - 1] ^ (m_state[i - 1] >> 30)) + i;
        m_index = kStateWords;
    }
    void reset() { seed(kDefaultSeed); }

    std::uint32_t next() {
        if (m_index >= kStateWords) twist();
        std::uint32_t value = m_state[m_index++];
        value ^= value >> 11;
        value ^= (value << 7) & 0x9d2c5680u;
        value ^= (value << 15) & 0xefc60000u;
        return value ^ (value >> 18);
    }

    // The bodies' `draw % bound`. A zero bound means the rule asked for no draw, so it
    // must consume nothing — an unset spread may not advance the stream.
    std::uint32_t modulo(std::uint32_t bound) {
        return bound ? next() % bound : 0u;
    }

private:
    void twist() {
        for (std::uint32_t i = 0; i < kStateWords; ++i) {
            const std::uint32_t merged = (m_state[i] & 0x80000000u) |
                                         (m_state[(i + 1u) % kStateWords] & 0x7fffffffu);
            std::uint32_t twisted = merged >> 1;
            if ((merged & 1u) != 0u) twisted ^= 0x9908b0dfu;
            m_state[i] = m_state[(i + kMiddleWord) % kStateWords] ^ twisted;
        }
        m_index = 0;
    }

    std::array<std::uint32_t, kStateWords> m_state{};
    std::uint32_t m_index = kStateWords;
};

}  // namespace gameplay
