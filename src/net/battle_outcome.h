#pragma once

#include "net/udp_socket.h"

#include <array>
#include <chrono>
#include <cstdint>
#include <vector>

namespace net {

struct MatchPlan;

// A retransmitted control channel survives the GekkoNet battle session. Offers
// contain the round-end frame and a digest of all confirmed frames through it.
// A peer seals only after seeing every matching offer, and accepts only after
// seeing every seal. Aborts are acknowledged and retried per peer. Missing peers
// time out; decisions linger for retransmission.
// Like any UDP protocol this cannot guarantee delivery across a permanent partition.
class BattleOutcome {
public:
    enum class State { Playing, Pending, Valid, Desync, Timeout };
    BattleOutcome(UdpSocket& socket, const MatchPlan& plan, std::uint8_t localPeer);
    void propose(int frame, std::uint64_t digest);
    void abort();
    void handle(const Address& from, const std::vector<std::uint8_t>& packet);
    void tick(unsigned elapsedMs);
    void update_clock();
    State state() const { return m_state; }
    bool abort_acknowledged() const;

private:
    void send();
    void acknowledge(std::uint8_t peer);
    void evaluate();
    UdpSocket* m_socket;
    std::uint32_t m_token;
    std::uint8_t m_localPeer, m_peers;
    std::array<Address, 4> m_addresses, m_publics, m_privates;
    std::array<bool, 4> m_offered{}, m_sealed{}, m_abortAcknowledged{};
    std::array<int, 4> m_frames{};
    std::array<std::uint64_t, 4> m_digests{};
    State m_state = State::Playing;
    unsigned m_pendingMs = 0, m_sendMs = 100, m_lingerMs = 0;
    bool m_sendNow = false;
    std::chrono::steady_clock::time_point m_lastTick = std::chrono::steady_clock::now();
};

}  // namespace net
