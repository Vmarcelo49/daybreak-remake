#pragma once
// Online play on GekkoNet (docs/ONLINE-PLAN.md). The only code that talks to the library.
#include <array>
#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include "battle/core_battle.h"
#include "net/lobby.h"
#include "net/udp_socket.h"

struct GekkoSession;

namespace net {

struct SessionStats {
    unsigned updates = 0;
    unsigned rollbacks = 0;
    unsigned replayedTicks = 0;
    unsigned desyncs = 0;
    int firstDesyncFrame = -1;
    unsigned disconnects = 0;
    unsigned skippedTicks = 0;
    std::chrono::microseconds worstUpdate{0};
    std::chrono::microseconds totalUpdate{0};
};

// The selection screen's netcode: every peer runs the screen with the same held buttons on the same
// frame, waiting for everyone's. No rollback, since a menu forgives the wait and has nothing to predict.
class MenuLockstep {
public:
    static constexpr unsigned kInputDelay = 3;
    using Held = std::array<std::uint8_t, 4>;  // per peer, as bits from the caller

    MenuLockstep(UdpSocket& socket, Lobby& lobby, const MatchPlan& plan, std::uint8_t localPeer);
    ~MenuLockstep();
    MenuLockstep(const MenuLockstep&) = delete;
    MenuLockstep& operator=(const MenuLockstep&) = delete;

    // `onFrame` runs once per agreed frame, and `hash` tells the state after it, for peers to compare.
    void run(std::uint8_t localHeld, const std::function<void(const Held&)>& onFrame,
             const std::function<std::uint32_t()>& hash);
    // Keeps resending what a slower peer has not received, after this one has moved on.
    void linger();
    bool peer_left() const { return m_peerLeft; }
    bool desynced() const { return m_desynced; }

private:
    GekkoSession* m_session = nullptr;
    int m_localPeer = 0, m_peers = 0;
    bool m_peerLeft = false, m_desynced = false;
};

class Session final : public sim::TickDriver {
public:
    // Rolls back `distance` ticks on every update, and reports any replay that ends differently.
    static std::unique_ptr<Session> stress(sim::CoreBattle& battle, unsigned distance);
    // One peer of a match. Every slot of `plan` must already be in `battle`. `lobby` keeps answering a
    // peer that has not heard the start yet.
    static std::unique_ptr<Session> online(sim::CoreBattle& battle, UdpSocket& socket, Lobby& lobby, const MatchPlan& plan,
                                           std::uint8_t localPeer, unsigned inputDelay);
    ~Session() override;
    Session(const Session&) = delete;
    Session& operator=(const Session&) = delete;

    game::BattleFrame run(const sim::Inputs& inputs) override;
    const SessionStats& stats() const { return m_stats; }
    int frame() const { return m_frame; }
    // A wrong prediction can end a round that a correction brings back, so the game may leave only
    // once no rollback can reach the end.
    bool round_over_confirmed() const { return m_roundOverFrame >= 0 && m_frame > m_roundOverFrame + kPredictionWindow; }
    int round_over_frame() const { return m_roundOverFrame; }
    // Peers compare these. A frame old enough for no rollback to reach holds its final value.
    using HashLog = std::vector<std::pair<int, std::uint32_t>>;
    void log_hashes(HashLog* log) { m_hashLog = log; }
    // Test seam: the next saved state claims a wrong hash, as a real divergence would look.
    void corrupt_next_hash_for_test() { m_corruptNextHash = true; }

private:
    explicit Session(sim::CoreBattle& battle);

    // GekkoNet saves bytes, and a snapshot holds heap, so the bytes it keeps are an index into this
    // ring. Longer than any rollback, and also why a late spectator cannot join from these bytes.
    static constexpr unsigned kSlots = 16;
    static constexpr int kPredictionWindow = 8;

    sim::CoreBattle& m_battle;
    GekkoSession* m_session = nullptr;
    std::array<sim::CoreBattle::Snapshot, kSlots> m_slots{};
    SessionStats m_stats;
    bool m_corruptNextHash = false;
    int m_frame = 0;
    unsigned m_ticks = 0;
    int m_roundOverFrame = -1;
    HashLog* m_hashLog = nullptr;
    int m_localPlayer = -1;  // online: GekkoNet's handle for this machine
    std::array<int, 4> m_playerSlot{{0, 1, 2, 3}};  // GekkoNet's handle -> the battle's slot
    int m_players = 4;
};

}  // namespace net
