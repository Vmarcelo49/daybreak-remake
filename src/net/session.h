#pragma once
// Online play on GekkoNet (docs/ONLINE-PLAN.md). The only code that talks to the library.
#include <array>
#include <chrono>
#include <cstdint>
#include <memory>

#include "battle/core_battle.h"

struct GekkoSession;

namespace net {

struct SessionStats {
    unsigned updates = 0;
    unsigned rollbacks = 0;
    unsigned replayedTicks = 0;
    unsigned desyncs = 0;
    int firstDesyncFrame = -1;
    std::chrono::microseconds worstUpdate{0};
    std::chrono::microseconds totalUpdate{0};
};

class Session final : public sim::TickDriver {
public:
    // Rolls back `distance` ticks on every update, and reports any replay that ends differently.
    static std::unique_ptr<Session> stress(sim::CoreBattle& battle, unsigned distance);
    ~Session() override;
    Session(const Session&) = delete;
    Session& operator=(const Session&) = delete;

    game::BattleFrame run(const sim::Inputs& inputs) override;
    const SessionStats& stats() const { return m_stats; }
    // Test seam: the next saved state claims a wrong hash, as a real divergence would look.
    void corrupt_next_hash_for_test() { m_corruptNextHash = true; }

private:
    explicit Session(sim::CoreBattle& battle);

    // GekkoNet saves bytes, and a snapshot holds heap, so the bytes it keeps are an index into this
    // ring. Longer than any rollback, and also why a late spectator cannot join from these bytes.
    static constexpr unsigned kSlots = 16;

    sim::CoreBattle& m_battle;
    GekkoSession* m_session = nullptr;
    std::array<sim::CoreBattle::Snapshot, kSlots> m_slots{};
    SessionStats m_stats;
    bool m_corruptNextHash = false;
};

}  // namespace net
