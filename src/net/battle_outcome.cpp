#include "net/battle_outcome.h"
#include "net/lobby.h"

namespace net {
namespace {
constexpr unsigned kResendMs = 100, kTimeoutMs = 10000;
constexpr std::size_t kPacketSize = 20;

void put(std::vector<std::uint8_t>& out, std::uint64_t value, unsigned bytes) {
    for (unsigned i = 0; i < bytes; ++i) out.push_back(static_cast<std::uint8_t>(value >> (i * 8)));
}
std::uint64_t get(const std::vector<std::uint8_t>& in, unsigned offset, unsigned bytes) {
    std::uint64_t value = 0;
    for (unsigned i = 0; i < bytes; ++i) value |= std::uint64_t(in[offset + i]) << (i * 8);
    return value;
}
}

BattleOutcome::BattleOutcome(UdpSocket& socket, const MatchPlan& plan, std::uint8_t localPeer)
    : m_socket(&socket), m_token(plan.token), m_localPeer(localPeer), m_peers(plan.peerCount),
      m_addresses(plan.peers), m_publics(plan.publics), m_privates(plan.privates) {}

void BattleOutcome::propose(int frame, std::uint64_t digest) {
    if (m_state != State::Playing) return;
    m_lastTick = std::chrono::steady_clock::now();
    m_state = State::Pending;
    m_offered[m_localPeer] = true;
    m_frames[m_localPeer] = frame;
    m_digests[m_localPeer] = digest;
    evaluate();
    send();
}

void BattleOutcome::abort() {
    if (m_state == State::Desync || m_state == State::Timeout) return;
    m_state = State::Desync;
    m_lastTick = std::chrono::steady_clock::now();
    m_lingerMs = 0;
    m_abortAcknowledged = {};
    send();
}

void BattleOutcome::evaluate() {
    if (m_state != State::Pending) return;
    for (std::uint8_t peer = 0; peer < m_peers; ++peer) {
        if (!m_offered[peer]) return;
        if (m_frames[peer] != m_frames[m_localPeer] || m_digests[peer] != m_digests[m_localPeer]) {
            abort();
            return;
        }
    }
    if (!m_sealed[m_localPeer]) {
        m_sealed[m_localPeer] = true;
        send();
    }
    for (std::uint8_t peer = 0; peer < m_peers; ++peer)
        if (!m_sealed[peer]) return;
    m_state = State::Valid;
    m_lastTick = std::chrono::steady_clock::now();
    m_lingerMs = 0;
}

void BattleOutcome::handle(const Address& from, const std::vector<std::uint8_t>& packet) {
    if (packet.size() != kPacketSize || packet[0] != kOutcomePacket || get(packet, 1, 4) != m_token) return;
    const auto peer = packet[5], kind = packet[6];
    if (peer >= m_peers || peer == m_localPeer || kind < 1 || kind > 4 || packet[7] != 0) return;
    if (!(from == m_addresses[peer] || from == m_publics[peer] || from == m_privates[peer])) return;
    if (kind == 4) {
        if (m_state == State::Desync || m_state == State::Timeout) m_abortAcknowledged[peer] = true;
        return;
    }
    if (kind == 3) {
        abort();
        acknowledge(peer);
        return;
    }
    // Once periodic retransmission stops, answer a still-waiting peer. During
    // the linger the periodic sends suffice and avoid peers echoing each other.
    if (m_state == State::Timeout || m_state == State::Desync) {
        m_abortAcknowledged[peer] = false;
        if (m_lingerMs >= kTimeoutMs) m_sendNow = true;
        return;
    }
    if (m_state == State::Valid && kind == 1 && m_lingerMs >= kTimeoutMs) m_sendNow = true;
    const auto frame = static_cast<std::uint32_t>(get(packet, 8, 4));
    if (frame > 0x7fffffffU) return;
    const auto digest = get(packet, 12, 8);
    if (m_offered[peer] && (m_frames[peer] != static_cast<int>(frame) || m_digests[peer] != digest)) {
        abort();
        return;
    }
    m_offered[peer] = true;
    m_frames[peer] = static_cast<int>(frame);
    m_digests[peer] = digest;
    if (kind == 2) m_sealed[peer] = true;
    evaluate();
}

bool BattleOutcome::abort_acknowledged() const {
    for (std::uint8_t peer = 0; peer < m_peers; ++peer)
        if (peer != m_localPeer && !m_abortAcknowledged[peer]) return false;
    return true;
}

void BattleOutcome::acknowledge(std::uint8_t peer) {
    std::vector<std::uint8_t> packet{kOutcomePacket};
    put(packet, m_token, 4);
    put(packet, m_localPeer, 1);
    put(packet, 4, 1);
    put(packet, 0, 1);
    put(packet, 0, 4);
    put(packet, 0, 8);
    m_socket->send(m_addresses[peer], packet.data(), packet.size());
}

void BattleOutcome::send() {
    if (m_state == State::Playing) return;
    const bool failed = m_state == State::Desync || m_state == State::Timeout;
    std::vector<std::uint8_t> packet{kOutcomePacket};
    put(packet, m_token, 4);
    put(packet, m_localPeer, 1);
    put(packet, failed ? 3 : m_sealed[m_localPeer] ? 2 : 1, 1);
    put(packet, 0, 1);
    put(packet, static_cast<std::uint32_t>(m_frames[m_localPeer]), 4);
    put(packet, m_digests[m_localPeer], 8);
    for (std::uint8_t peer = 0; peer < m_peers; ++peer)
        if (peer != m_localPeer && (!failed || !m_abortAcknowledged[peer]))
            m_socket->send(m_addresses[peer], packet.data(), packet.size());
    m_sendMs = 0;
    m_sendNow = false;
}

void BattleOutcome::update_clock() {
    const auto now = std::chrono::steady_clock::now();
    const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_lastTick).count();
    if (elapsed <= 0) return;
    m_lastTick += std::chrono::milliseconds(elapsed);
    tick(static_cast<unsigned>(elapsed > 10000 ? 10000 : elapsed));
}

void BattleOutcome::tick(unsigned elapsedMs) {
    if (m_state == State::Pending) {
        m_pendingMs += elapsedMs;
        if (m_pendingMs >= kTimeoutMs) {
            m_state = State::Timeout;
            m_lingerMs = 0;
        }
    } else if (m_state != State::Playing) {
        if (m_lingerMs >= kTimeoutMs && !m_sendNow) return;
        if (m_lingerMs < kTimeoutMs) m_lingerMs += elapsedMs;
    } else {
        return;
    }
    m_sendMs += elapsedMs;
    if (m_sendMs >= kResendMs) send();
}
}  // namespace net
