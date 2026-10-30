#pragma once
// battle/rng.h — the simulation's one random source.
//
// WHY this exists (issue #11): the original resolves a timed-round tie with
// FUN_0065d150 (0x65d150) — MT19937 (624-word state; the 0x26f/0x270 reload and the
// 0x13a58ad/0x1df8c/0x9908b0df tempering are the canonical ones) — and the port
// needs that coin flip to be reproducible from a seed instead of libc rand. The
// state is an explicit 64-bit integer, so a snapshot is a copy, a replay of the same
// seed produces the same round, and issue #3's rollback work can serialize it
// without touching this file.
//
// PORT RULE: splitmix64 output, not MT19937. The original's *sequence* is not part of
// any recoverable rule (the game draws from the same generator for spawns, AI and
// cosmetics, in an order this port does not reproduce), and matching MT19937 would
// buy sequence parity only against a call ordering the port does not have. What is
// recovered and preserved is the *policy*: a deterministic generator seeded per
// match, consumed once per unresolved tie. Label it provisional and let the rollback
// milestone adopt or replace it — the call sites are the economy's tiebreak only.
#include <cstdint>

namespace gameplay {

class MatchRng {
public:
    // 0x9e3779b97f4a7c15 is the splitmix64 golden-ratio increment; any non-zero seed
    // is valid, and 0 is remapped so a zero-initialized MatchConfig still advances.
    static constexpr uint64_t kDefaultSeed = 0x9e3779b97f4a7c15ull;

    MatchRng() = default;
    explicit MatchRng(uint64_t seed) { set_state(seed); }

    uint64_t state() const { return m_state; }
    void set_state(uint64_t seed) { m_state = seed ? seed : kDefaultSeed; }

    uint32_t next_u32() {
        m_state += kDefaultSeed;
        uint64_t z = m_state;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ull;
        z = (z ^ (z >> 27)) * 0x94d049bb133111ebull;
        z ^= z >> 31;
        return static_cast<uint32_t>(z >> 32);
    }

    // Uniform enough for a two-way choice, and used exactly that way: the original's
    // own tiebreak is `FUN_0065d150() % 2` (FUN_00635d40 @0x636fc4-0x636fce).
    int below(int bound) { return bound > 0 ? static_cast<int>(next_u32() % static_cast<uint32_t>(bound)) : 0; }

private:
    uint64_t m_state = kDefaultSeed;
};

}  // namespace gameplay
