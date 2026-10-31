#include "net/session.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <gekkonet.h>
#include <stdexcept>
#include <vector>

namespace net {

namespace {

// One player's input on the wire: small, and the same bytes on every machine. `present` is 1 for a
// live player. GekkoNet feeds a dropped player zeros from a frame all peers agree on, so its 0 tells
// every peer the same tick to hand that slot to COM, even through a rollback.
struct WireInput {
    std::int8_t x, z;
    std::uint8_t buttons, present;
};
static_assert(sizeof(WireInput) == 4);

WireInput to_wire(const sim::SlotInput& input) {
    return {static_cast<std::int8_t>(input.x), static_cast<std::int8_t>(input.z), static_cast<std::uint8_t>(input.buttons), 1};
}

struct MenuWire {
    std::uint8_t held, present;
};

// GekkoNet's adapter has no context pointer, and a process plays one match.
UdpSocket* g_socket = nullptr;
Lobby* g_lobby = nullptr;
std::array<Address, 4> g_peers{};
std::uint8_t g_peerCount = 0;
std::uint32_t g_token = 0;
constexpr size_t kGameHeader = 1 + sizeof g_token;

constexpr unsigned kSkipEvery = 8;
// The first frames have no input yet, which reads as zeros: an input delay's worth, and a prediction
// before the first packet. By this frame a 0 can only mean a player left.
constexpr int kFirstLiveFrame = 60;

void adapter_send(GekkoNetAddress* address, const char* data, int length) {
    if (!g_socket || !address || address->size != sizeof(Address) || length < 0) return;
    std::vector<std::uint8_t> packet(kGameHeader + static_cast<size_t>(length));
    packet[0] = kGamePacket;
    std::memcpy(packet.data() + 1, &g_token, sizeof g_token);
    std::memcpy(packet.data() + kGameHeader, data, static_cast<size_t>(length));
    Address to;
    std::memcpy(&to, address->data, sizeof to);
    g_socket->send(to, packet.data(), packet.size());
}

GekkoNetResult** adapter_receive(int* length) {
    static std::vector<GekkoNetResult*> results;
    results.clear();
    Address from;
    std::vector<std::uint8_t> packet;
    while (g_socket && g_socket->receive(from, packet)) {
        if (packet.empty()) continue;
        if (packet[0] == kLobbyPacket) {
            if (g_lobby) g_lobby->handle(from, packet);
            continue;
        }
        // Only the match's own peers reach GekkoNet, and only with the match's token.
        if (packet[0] != kGamePacket || packet.size() < kGameHeader) continue;
        if (std::memcmp(packet.data() + 1, &g_token, sizeof g_token) != 0) continue;
        bool known = false;
        for (std::uint8_t i = 0; i < g_peerCount; ++i) known = known || g_peers[i] == from;
        if (!known) continue;
        auto* result = static_cast<GekkoNetResult*>(std::malloc(sizeof(GekkoNetResult)));
        result->addr.size = sizeof from;
        result->addr.data = std::malloc(sizeof from);
        std::memcpy(result->addr.data, &from, sizeof from);
        result->data_len = static_cast<unsigned>(packet.size() - kGameHeader);
        result->data = std::malloc(result->data_len ? result->data_len : 1);
        std::memcpy(result->data, packet.data() + kGameHeader, result->data_len);
        results.push_back(result);
    }
    *length = static_cast<int>(results.size());
    return results.data();
}

void adapter_free(void* data) { std::free(data); }

GekkoNetAdapter g_adapter{adapter_send, adapter_receive, adapter_free};

void merge(game::BattleFrame& into, game::BattleFrame&& frame) {
    const auto append = [](auto& to, auto& from) { to.insert(to.end(), from.begin(), from.end()); };
    append(into.effectSpawns, frame.effectSpawns);
    append(into.soundCues, frame.soundCues);
    append(into.voiceCues, frame.voiceCues);
    frame.effectSpawns = std::move(into.effectSpawns);
    frame.soundCues = std::move(into.soundCues);
    frame.voiceCues = std::move(into.voiceCues);
    frame.roundOver = frame.roundOver || into.roundOver;
    into = std::move(frame);
}

}  // namespace

Session::Session(sim::CoreBattle& battle) : m_battle(battle) {}

Session::~Session() {
    if (m_session) gekko_destroy(&m_session);
    if (m_localPlayer >= 0) g_socket = nullptr, g_lobby = nullptr;
}

std::unique_ptr<Session> Session::stress(sim::CoreBattle& battle, unsigned distance) {
    if (distance == 0 || distance + 2 > kSlots) throw std::invalid_argument("net: stress distance");
    std::unique_ptr<Session> session(new Session(battle));
    if (!gekko_create(&session->m_session, GekkoStressSession)) throw std::runtime_error("net: no session");
    GekkoConfig config{};
    config.num_players = 4;
    config.input_size = sizeof(WireInput);
    config.state_size = sizeof(std::uint32_t);
    config.desync_detection = true;
    config.check_distance = distance;
    gekko_start(session->m_session, &config);
    for (int i = 0; i < 4; ++i) gekko_add_actor(session->m_session, GekkoLocalPlayer, nullptr);
    return session;
}

MenuLockstep::MenuLockstep(UdpSocket& socket, Lobby& lobby, const MatchPlan& plan, std::uint8_t localPeer)
    : m_localPeer(localPeer), m_peers(plan.peerCount) {
    if (!gekko_create(&m_session, GekkoGameSession)) throw std::runtime_error("net: no session");
    g_socket = &socket;
    g_lobby = &lobby;
    g_peers = plan.peers;
    g_peerCount = plan.peerCount;
    // Its own token: a late packet of this session must not reach the battle's.
    g_token = plan.token ^ 0x4d454e55u;

    GekkoConfig config{};
    config.num_players = plan.peerCount;
    config.max_input_prediction_window = 0;
    config.input_size = sizeof(MenuWire);
    config.state_size = sizeof(std::uint32_t);
    config.desync_detection = true;
    gekko_start(m_session, &config);
    gekko_net_adapter_set(m_session, &g_adapter);
    for (std::uint8_t peer = 0; peer < plan.peerCount; ++peer) {
        if (peer == localPeer) {
            gekko_add_actor(m_session, GekkoLocalPlayer, nullptr);
            gekko_set_local_delay(m_session, peer, kInputDelay);
        } else {
            Address address = plan.peers[peer];
            GekkoNetAddress remote{&address, sizeof address};
            gekko_add_actor(m_session, GekkoRemotePlayer, &remote);
        }
    }
}

MenuLockstep::~MenuLockstep() {
    if (m_session) gekko_destroy(&m_session);
}

void MenuLockstep::linger() { gekko_network_poll(m_session); }

void MenuLockstep::run(std::uint8_t localHeld, const std::function<void(const Held&)>& onFrame,
                       const std::function<std::uint32_t()>& hash) {
    MenuWire wire{localHeld, 1};
    gekko_add_local_input(m_session, m_localPeer, &wire);
    int count = 0;
    GekkoGameEvent** events = gekko_update_session(m_session, &count);
    for (int i = 0; i < count; ++i) {
        const GekkoGameEvent& event = *events[i];
        if (event.type == GekkoAdvanceEvent) {
            Held held{};
            for (int peer = 0; peer < m_peers; ++peer) {
                MenuWire remote;
                std::memcpy(&remote, event.data.adv.inputs + static_cast<size_t>(peer) * sizeof remote, sizeof remote);
                held[static_cast<size_t>(peer)] = remote.held;
            }
            onFrame(held);
        } else if (event.type == GekkoSaveEvent) {
            *event.data.save.checksum = hash();
            *event.data.save.state_len = sizeof(std::uint32_t);
            std::memset(event.data.save.state, 0, sizeof(std::uint32_t));
        }
    }
    int sessionCount = 0;
    GekkoSessionEvent** sessionEvents = gekko_session_events(m_session, &sessionCount);
    for (int i = 0; i < sessionCount; ++i) {
        if (sessionEvents[i]->type == GekkoPlayerDisconnected) m_peerLeft = true;
        if (sessionEvents[i]->type == GekkoDesyncDetected) m_desynced = true;
    }
}

std::unique_ptr<Session> Session::online(sim::CoreBattle& battle, UdpSocket& socket, Lobby& lobby, const MatchPlan& plan,
                                         std::uint8_t localPeer, unsigned inputDelay) {
    std::unique_ptr<Session> session(new Session(battle));
    if (!gekko_create(&session->m_session, GekkoGameSession)) throw std::runtime_error("net: no session");
    g_socket = &socket;
    g_lobby = &lobby;
    g_peers = plan.peers;
    g_peerCount = plan.peerCount;
    g_token = plan.token;

    GekkoConfig config{};
    config.num_players = plan.peerCount;
    config.max_input_prediction_window = kPredictionWindow;
    config.input_size = sizeof(WireInput);
    config.state_size = sizeof(std::uint32_t);
    config.desync_detection = true;
    gekko_start(session->m_session, &config);
    gekko_net_adapter_set(session->m_session, &g_adapter);

    session->m_players = plan.peerCount;
    session->m_localPlayer = localPeer;
    for (size_t slot = 0; slot < plan.slots.size(); ++slot)
        if (plan.slots[slot].peer >= 0) session->m_playerSlot[static_cast<size_t>(plan.slots[slot].peer)] = static_cast<int>(slot);
    for (std::uint8_t peer = 0; peer < plan.peerCount; ++peer) {
        if (peer == localPeer) {
            gekko_add_actor(session->m_session, GekkoLocalPlayer, nullptr);
            gekko_set_local_delay(session->m_session, peer, static_cast<unsigned char>(inputDelay));
        } else {
            Address address = plan.peers[peer];
            GekkoNetAddress remote{&address, sizeof address};
            gekko_add_actor(session->m_session, GekkoRemotePlayer, &remote);
        }
    }
    return session;
}

game::BattleFrame Session::run(const sim::Inputs& inputs) {
    const auto start = std::chrono::steady_clock::now();
    game::BattleFrame frame;
    // Running ahead of the slowest peer only causes rollbacks, so give it a tick now and then. Not
    // every tick: the session measures who is ahead only while it advances.
    if (m_localPlayer >= 0 && ++m_ticks % kSkipEvery == 0 && gekko_frames_ahead(m_session) >= 1.f) {
        ++m_stats.skippedTicks;
        gekko_network_poll(m_session);
        return frame;
    }
    if (m_localPlayer >= 0) {
        WireInput wire = to_wire(inputs[static_cast<size_t>(m_playerSlot[static_cast<size_t>(m_localPlayer)])]);
        gekko_add_local_input(m_session, m_localPlayer, &wire);
    } else {
        for (int i = 0; i < m_players; ++i) {
            WireInput wire = to_wire(inputs[static_cast<size_t>(i)]);
            gekko_add_local_input(m_session, i, &wire);
        }
    }

    int count = 0;
    GekkoGameEvent** events = gekko_update_session(m_session, &count);
    for (int i = 0; i < count; ++i) {
        const GekkoGameEvent& event = *events[i];
        if (event.type == GekkoAdvanceEvent) {
            if (event.data.adv.rolling_back) ++m_stats.replayedTicks;
            sim::Inputs ticked{};
            for (int player = 0; player < m_players; ++player) {
                WireInput wire;
                std::memcpy(&wire, event.data.adv.inputs + static_cast<size_t>(player) * sizeof wire, sizeof wire);
                const int slot = m_playerSlot[static_cast<size_t>(player)];
                if (wire.present) ticked[static_cast<size_t>(slot)] = {wire.x, wire.z, wire.buttons};
                else if (event.data.adv.frame >= kFirstLiveFrame) m_battle.hand_slot_to_cpu(static_cast<unsigned>(slot));
            }
            merge(frame, m_battle.advance(ticked));
            m_frame = event.data.adv.frame + 1;
            if (!m_battle.economy().roundOver()) m_roundOverFrame = -1;
            else if (m_roundOverFrame < 0) m_roundOverFrame = event.data.adv.frame;
        } else if (event.type == GekkoSaveEvent) {
            const auto slot = static_cast<std::uint32_t>(event.data.save.frame + 1) % kSlots;
            m_battle.save_state(m_slots[slot]);
            const std::uint64_t hash = m_battle.state_hash();
            const auto folded = static_cast<std::uint32_t>(hash ^ (hash >> 32));
            *event.data.save.checksum = folded + (m_corruptNextHash ? 1u : 0u);
            m_corruptNextHash = false;
            *event.data.save.state_len = sizeof slot;
            std::memcpy(event.data.save.state, &slot, sizeof slot);
            if (m_hashLog) {
                // A rollback saves its frames again, and the last value stands.
                while (!m_hashLog->empty() && m_hashLog->back().first >= event.data.save.frame) m_hashLog->pop_back();
                m_hashLog->emplace_back(event.data.save.frame, folded);
            }
        } else if (event.type == GekkoLoadEvent) {
            std::uint32_t slot;
            std::memcpy(&slot, event.data.load.state, sizeof slot);
            m_battle.load_state(m_slots[slot]);
            ++m_stats.rollbacks;
        }
    }

    int sessionCount = 0;
    GekkoSessionEvent** sessionEvents = gekko_session_events(m_session, &sessionCount);
    for (int i = 0; i < sessionCount; ++i) {
        if (sessionEvents[i]->type == GekkoPlayerDisconnected) ++m_stats.disconnects;
        if (sessionEvents[i]->type != GekkoDesyncDetected) continue;
        const int desyncFrame = sessionEvents[i]->data.desynced.frame;
        if (m_stats.desyncs++ == 0) m_stats.firstDesyncFrame = desyncFrame;
    }

    const auto spent = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start);
    m_stats.worstUpdate = std::max(m_stats.worstUpdate, spent);
    m_stats.totalUpdate += spent;
    ++m_stats.updates;
    return frame;
}

}  // namespace net
