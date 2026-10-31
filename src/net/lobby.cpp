#include "net/lobby.h"

#include <cstring>
#include <fstream>

namespace net {

namespace {

constexpr unsigned kResendMs = 100;
enum Kind : std::uint8_t { Hello = 1, Plan = 2, Refused = 3 };
constexpr size_t kHelloSize = 2 + 2 + 8 + 1;

template <class T>
void put(std::vector<std::uint8_t>& out, T value) {
    for (size_t i = 0; i < sizeof(T); ++i) out.push_back(static_cast<std::uint8_t>(static_cast<std::uint64_t>(value) >> (8 * i)));
}

// Reads little-endian fields, and fails once the packet runs out.
struct Reader {
    const std::vector<std::uint8_t>& bytes;
    size_t at = 0;
    bool ok = true;
    template <class T>
    T get() {
        if (at + sizeof(T) > bytes.size()) {
            ok = false;
            return T{};
        }
        std::uint64_t value = 0;
        for (size_t i = 0; i < sizeof(T); ++i) value |= static_cast<std::uint64_t>(bytes[at + i]) << (8 * i);
        at += sizeof(T);
        return static_cast<T>(value);
    }
};

}  // namespace

const char* refusal_text(Refusal refusal) {
    switch (refusal) {
        case Refusal::WrongVersion: return "This player has a different version of the game.";
        case Refusal::WrongGameData: return "This player has different game data.";
        case Refusal::RoomFull: return "The room is full.";
        case Refusal::None: break;
    }
    return "";
}

std::vector<std::uint8_t> encode_hello(std::uint64_t gameData, bool started) {
    std::vector<std::uint8_t> out{kLobbyPacket, Hello};
    put<std::uint16_t>(out, kProtocolVersion);
    put<std::uint64_t>(out, gameData);
    put<std::uint8_t>(out, started);
    return out;
}

bool decode_hello(const std::vector<std::uint8_t>& packet, std::uint16_t& version, std::uint64_t& gameData, bool& started) {
    if (packet.size() != kHelloSize || packet[0] != kLobbyPacket || packet[1] != Hello) return false;
    Reader in{packet, 2};
    version = in.get<std::uint16_t>();
    gameData = in.get<std::uint64_t>();
    started = in.get<std::uint8_t>() != 0;
    return in.ok;
}

std::vector<std::uint8_t> encode_plan(const MatchPlan& plan, std::uint8_t yourPeer) {
    std::vector<std::uint8_t> out{kLobbyPacket, Plan};
    put<std::uint8_t>(out, yourPeer);
    put<std::uint32_t>(out, plan.token);
    put<std::uint32_t>(out, plan.seed);
    put<std::uint8_t>(out, static_cast<std::uint8_t>(plan.stage));
    put<std::uint16_t>(out, static_cast<std::uint16_t>(plan.timeLimitSeconds));
    for (int rule : plan.rules) put<std::uint16_t>(out, static_cast<std::uint16_t>(rule));
    for (const PlanSlot& slot : plan.slots) {
        put<std::uint8_t>(out, static_cast<std::uint8_t>(slot.character));
        put<std::uint8_t>(out, static_cast<std::uint8_t>(slot.weapon));
        put<std::uint8_t>(out, static_cast<std::uint8_t>(slot.costume));
        put<std::uint8_t>(out, static_cast<std::uint8_t>(slot.specialMode));
        put<std::int8_t>(out, static_cast<std::int8_t>(slot.peer));
    }
    put<std::uint8_t>(out, plan.peerCount);
    for (const Address& peer : plan.peers) {
        put<std::uint32_t>(out, peer.ip);
        put<std::uint16_t>(out, peer.port);
    }
    put<std::uint8_t>(out, plan.started);
    return out;
}

bool decode_plan(const std::vector<std::uint8_t>& packet, MatchPlan& plan, std::uint8_t& yourPeer) {
    if (packet.size() < 2 || packet[0] != kLobbyPacket || packet[1] != Plan) return false;
    Reader in{packet, 2};
    MatchPlan out;
    yourPeer = in.get<std::uint8_t>();
    out.token = in.get<std::uint32_t>();
    out.seed = in.get<std::uint32_t>();
    out.stage = in.get<std::uint8_t>();
    out.timeLimitSeconds = in.get<std::uint16_t>();
    for (int& rule : out.rules) rule = in.get<std::uint16_t>();
    for (PlanSlot& slot : out.slots) {
        slot.character = in.get<std::uint8_t>();
        slot.weapon = in.get<std::uint8_t>();
        slot.costume = in.get<std::uint8_t>();
        slot.specialMode = in.get<std::uint8_t>();
        slot.peer = in.get<std::int8_t>();
    }
    out.peerCount = in.get<std::uint8_t>();
    for (Address& peer : out.peers) {
        peer.ip = in.get<std::uint32_t>();
        peer.port = in.get<std::uint16_t>();
    }
    out.started = in.get<std::uint8_t>() != 0;
    if (!in.ok || in.at != packet.size()) return false;
    if (out.peerCount < 2 || out.peerCount > 4 || yourPeer >= out.peerCount) return false;
    std::array<bool, 4> played{};
    for (const PlanSlot& slot : out.slots) {
        if (slot.peer < -1 || slot.peer >= out.peerCount) return false;
        if (slot.peer >= 0) {
            if (played[static_cast<size_t>(slot.peer)]) return false;
            played[static_cast<size_t>(slot.peer)] = true;
        }
    }
    for (std::uint8_t i = 0; i < out.peerCount; ++i)
        if (!played[i]) return false;
    plan = out;
    return true;
}

std::vector<std::uint8_t> encode_refusal(Refusal refusal) {
    return {kLobbyPacket, Refused, static_cast<std::uint8_t>(refusal)};
}

bool decode_refusal(const std::vector<std::uint8_t>& packet, Refusal& refusal) {
    if (packet.size() != 3 || packet[0] != kLobbyPacket || packet[1] != Refused) return false;
    if (packet[2] == 0 || packet[2] > static_cast<std::uint8_t>(Refusal::RoomFull)) return false;
    refusal = static_cast<Refusal>(packet[2]);
    return true;
}

std::uint64_t game_data_hash(const std::string& gameDir) {
    constexpr std::streamoff kSample = 1 << 20;
    std::uint64_t digest = 1469598103934665603ull;
    const auto mix = [&digest](const char* data, size_t size) {
        for (size_t i = 0; i < size; ++i) digest = (digest ^ static_cast<unsigned char>(data[i])) * 1099511628211ull;
    };
    std::vector<char> buffer(static_cast<size_t>(kSample));
    bool any = false;
    for (const char* name : {"daybreak00.dat", "daybreak01.dat", "daybreak02.dat", "daybreak03.dat", "daybreak04.dat",
                             "daybreak05.dat", "daybreak06.dat", "daybreak07.dat"}) {
        std::ifstream file(gameDir + "/" + name, std::ios::binary | std::ios::ate);
        if (!file) continue;
        any = true;
        const std::streamoff size = file.tellg();
        mix(reinterpret_cast<const char*>(&size), sizeof size);
        const std::streamoff tail = size > kSample ? size - kSample : 0;
        for (const std::streamoff offset : {std::streamoff(0), tail}) {
            file.seekg(offset);
            file.read(buffer.data(), kSample);
            mix(buffer.data(), static_cast<size_t>(file.gcount()));
            file.clear();
        }
    }
    return any ? digest : 0;
}

Lobby Lobby::host(UdpSocket& socket, MatchPlan plan, std::uint64_t gameData) {
    Lobby lobby(socket, gameData);
    lobby.m_isHost = true;
    lobby.m_plan = plan;
    lobby.m_plan.started = false;
    lobby.m_started[0] = true;
    return lobby;
}

Lobby Lobby::join(UdpSocket& socket, Address host, std::uint64_t gameData) {
    Lobby lobby(socket, gameData);
    lobby.m_host = host;
    return lobby;
}

void Lobby::handle(const Address& from, const std::vector<std::uint8_t>& packet) {
    if (!m_isHost) {
        if (!(from == m_host)) return;
        Refusal refusal;
        if (decode_refusal(packet, refusal)) {
            if (!m_ready) m_refused = refusal;
            return;
        }
        MatchPlan plan;
        std::uint8_t peer;
        if (!decode_plan(packet, plan, peer)) return;
        m_plan = plan;
        m_localPeer = peer;
        m_plan.peers[0] = m_host;
        if (plan.started) {
            m_ready = true;
            m_socket->send(m_host, encode_hello(m_gameData, true).data(), kHelloSize);
        }
        return;
    }

    std::uint16_t version;
    std::uint64_t gameData;
    bool started;
    if (!decode_hello(packet, version, gameData, started)) return;
    const auto refuse = [&](Refusal why) {
        const auto out = encode_refusal(why);
        m_socket->send(from, out.data(), out.size());
    };
    if (version != kProtocolVersion) return refuse(Refusal::WrongVersion);
    if (gameData != m_gameData) return refuse(Refusal::WrongGameData);

    std::uint8_t peer = 0;
    for (std::uint8_t i = 1; i < m_plan.peerCount && !peer; ++i)
        if (m_plan.peers[i] == from) peer = i;
    if (!peer) {
        for (std::uint8_t i = 1; i < m_plan.peerCount && !peer; ++i)
            if (m_plan.peers[i].port == 0) peer = i;
        if (!peer) return refuse(Refusal::RoomFull);
        m_plan.peers[peer] = from;
    }
    if (started) m_started[peer] = true;
}

void Lobby::send_state() {
    if (!m_isHost) {
        if (!m_ready) m_socket->send(m_host, encode_hello(m_gameData, false).data(), kHelloSize);
        return;
    }
    bool full = true;
    for (std::uint8_t i = 1; i < m_plan.peerCount; ++i) full = full && m_plan.peers[i].port != 0;
    m_plan.started = full;
    for (std::uint8_t i = 1; i < m_plan.peerCount; ++i) {
        if (m_plan.peers[i].port == 0) continue;
        const auto out = encode_plan(m_plan, i);
        m_socket->send(m_plan.peers[i], out.data(), out.size());
    }
    bool everyone = full;
    for (std::uint8_t i = 1; i < m_plan.peerCount; ++i) everyone = everyone && m_started[i];
    m_ready = everyone;
}

void Lobby::poll(unsigned elapsedMs) {
    Address from;
    std::vector<std::uint8_t> packet;
    while (m_socket->receive(from, packet))
        if (!packet.empty() && packet[0] == kLobbyPacket) handle(from, packet);
    m_sinceSend += elapsedMs;
    if (m_sinceSend >= kResendMs) {
        m_sinceSend = 0;
        send_state();
    }
}

}  // namespace net
