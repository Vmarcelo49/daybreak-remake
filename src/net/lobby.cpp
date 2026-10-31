#include "net/lobby.h"

#include <cstring>
#include <fstream>

namespace net {

namespace {

constexpr unsigned kResendMs = 100;
enum Kind : std::uint8_t { KindHello = 1, KindPlan = 2, KindRefused = 3, KindBye = 4 };

template <class T>
void put(std::vector<std::uint8_t>& out, T value) {
    for (size_t i = 0; i < sizeof(T); ++i) out.push_back(static_cast<std::uint8_t>(static_cast<std::uint64_t>(value) >> (8 * i)));
}

void put_name(std::vector<std::uint8_t>& out, const std::string& name) {
    for (size_t i = 0; i < kMaxNameLength; ++i) out.push_back(i < name.size() ? static_cast<std::uint8_t>(name[i]) : 0);
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
    // Plain ASCII only, since a name reaches every other player's screen.
    std::string name() {
        std::string out;
        bool ended = false;
        for (size_t i = 0; i < kMaxNameLength; ++i) {
            const auto c = get<std::uint8_t>();
            if (c == 0) ended = true;
            else if (ended || c < 0x20 || c > 0x7e) ok = false;
            else out.push_back(static_cast<char>(c));
        }
        return out;
    }
};

// The menus' ranges. Whether a weapon exists for a character is checked when the match loads.
bool sane_choice(int character, int weapon, int costume, unsigned specialMode) {
    return character >= 0 && character < 16 && weapon >= 0 && weapon < 3 && costume >= 0 && costume < 8 && specialMode < 3;
}

}  // namespace

const char* refusal_text(Refusal refusal) {
    switch (refusal) {
        case Refusal::WrongVersion: return "This player has a different version of the game.";
        case Refusal::WrongGameData: return "This player has different game data.";
        case Refusal::RoomFull: return "The room is full, or its match has started.";
        case Refusal::HostLeft: return "The host closed the room.";
        case Refusal::None: break;
    }
    return "";
}

std::vector<std::uint8_t> encode_hello(const Hello& hello) {
    std::vector<std::uint8_t> out{kLobbyPacket, KindHello};
    put<std::uint16_t>(out, hello.version);
    put<std::uint64_t>(out, hello.gameData);
    put<std::uint8_t>(out, hello.started);
    put<std::uint8_t>(out, hello.choice.ready);
    put<std::uint8_t>(out, static_cast<std::uint8_t>(hello.choice.character));
    put<std::uint8_t>(out, static_cast<std::uint8_t>(hello.choice.weapon));
    put<std::uint8_t>(out, static_cast<std::uint8_t>(hello.choice.costume));
    put<std::uint8_t>(out, static_cast<std::uint8_t>(hello.choice.specialMode));
    put_name(out, hello.choice.name);
    put<std::uint16_t>(out, hello.sequence);
    put<std::uint16_t>(out, hello.pingMs);
    return out;
}

bool decode_hello(const std::vector<std::uint8_t>& packet, Hello& hello) {
    if (packet.size() < 2 || packet[0] != kLobbyPacket || packet[1] != KindHello) return false;
    Reader in{packet, 2};
    Hello out;
    out.version = in.get<std::uint16_t>();
    out.gameData = in.get<std::uint64_t>();
    out.started = in.get<std::uint8_t>() != 0;
    out.choice.ready = in.get<std::uint8_t>() != 0;
    out.choice.character = in.get<std::uint8_t>();
    out.choice.weapon = in.get<std::uint8_t>();
    out.choice.costume = in.get<std::uint8_t>();
    out.choice.specialMode = in.get<std::uint8_t>();
    out.choice.name = in.name();
    out.sequence = in.get<std::uint16_t>();
    out.pingMs = in.get<std::uint16_t>();
    if (!in.ok || in.at != packet.size()) return false;
    if (!sane_choice(out.choice.character, out.choice.weapon, out.choice.costume, out.choice.specialMode)) return false;
    hello = out;
    return true;
}

std::vector<std::uint8_t> encode_plan(const MatchPlan& plan, std::uint8_t yourPeer, std::uint16_t echo) {
    std::vector<std::uint8_t> out{kLobbyPacket, KindPlan};
    put<std::uint8_t>(out, yourPeer);
    put<std::uint16_t>(out, echo);
    put<std::uint32_t>(out, plan.token);
    put<std::uint32_t>(out, plan.seed);
    put<std::uint8_t>(out, static_cast<std::uint8_t>(plan.stage));
    put<std::uint8_t>(out, static_cast<std::uint8_t>(plan.variation));
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
    for (size_t i = 0; i < plan.peers.size(); ++i) {
        put<std::uint32_t>(out, plan.peers[i].ip);
        put<std::uint16_t>(out, plan.peers[i].port);
        put_name(out, plan.names[i]);
        put<std::uint8_t>(out, plan.ready[i]);
        put<std::uint16_t>(out, plan.pingMs[i]);
    }
    put<std::uint8_t>(out, plan.started);
    return out;
}

bool decode_plan(const std::vector<std::uint8_t>& packet, MatchPlan& plan, std::uint8_t& yourPeer, std::uint16_t& echo) {
    if (packet.size() < 2 || packet[0] != kLobbyPacket || packet[1] != KindPlan) return false;
    Reader in{packet, 2};
    MatchPlan out;
    yourPeer = in.get<std::uint8_t>();
    echo = in.get<std::uint16_t>();
    out.token = in.get<std::uint32_t>();
    out.seed = in.get<std::uint32_t>();
    out.stage = in.get<std::uint8_t>();
    out.variation = in.get<std::uint8_t>();
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
    for (size_t i = 0; i < out.peers.size(); ++i) {
        out.peers[i].ip = in.get<std::uint32_t>();
        out.peers[i].port = in.get<std::uint16_t>();
        out.names[i] = in.name();
        out.ready[i] = in.get<std::uint8_t>() != 0;
        out.pingMs[i] = in.get<std::uint16_t>();
    }
    out.started = in.get<std::uint8_t>() != 0;
    if (!in.ok || in.at != packet.size()) return false;
    if (out.peerCount < 2 || out.peerCount > 4 || yourPeer >= out.peerCount) return false;
    std::array<bool, 4> played{};
    for (const PlanSlot& slot : out.slots) {
        if (slot.peer < -1 || slot.peer >= out.peerCount) return false;
        if (!sane_choice(slot.character, slot.weapon, slot.costume, slot.specialMode)) return false;
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
    return {kLobbyPacket, KindRefused, static_cast<std::uint8_t>(refusal)};
}

bool decode_refusal(const std::vector<std::uint8_t>& packet, Refusal& refusal) {
    if (packet.size() != 3 || packet[0] != kLobbyPacket || packet[1] != KindRefused) return false;
    if (packet[2] == 0 || packet[2] > static_cast<std::uint8_t>(Refusal::HostLeft)) return false;
    refusal = static_cast<Refusal>(packet[2]);
    return true;
}

std::vector<std::uint8_t> encode_bye() { return {kLobbyPacket, KindBye}; }

bool decode_bye(const std::vector<std::uint8_t>& packet) {
    return packet.size() == 2 && packet[0] == kLobbyPacket && packet[1] == KindBye;
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
    lobby.m_plan.peerCount = 1;
    for (PlanSlot& slot : lobby.m_plan.slots) slot.peer = -1;
    lobby.m_plan.slots[static_cast<size_t>(kPeerSlot[0])].peer = 0;
    return lobby;
}

Lobby Lobby::join(UdpSocket& socket, Address host, std::uint64_t gameData) {
    Lobby lobby(socket, gameData);
    lobby.m_host = host;
    return lobby;
}

void Lobby::apply_choice(std::uint8_t peer, const LocalChoice& choice) {
    PlanSlot& slot = m_plan.slots[static_cast<size_t>(kPeerSlot[peer])];
    slot.character = choice.character;
    slot.weapon = choice.weapon;
    slot.costume = choice.costume;
    slot.specialMode = choice.specialMode;
    slot.peer = peer;
    m_plan.names[peer] = choice.name;
    m_plan.ready[peer] = choice.ready;
}

void Lobby::set_choice(const LocalChoice& choice) {
    m_choice = choice;
    if (m_isHost) apply_choice(0, choice);
}

void Lobby::remove_peer(std::uint8_t peer) {
    // The last player's slot becomes a COM, and later players move down into the gap.
    for (std::uint8_t i = peer; i + 1 < m_plan.peerCount; ++i) {
        const PlanSlot& next = m_plan.slots[static_cast<size_t>(kPeerSlot[i + 1])];
        PlanSlot& slot = m_plan.slots[static_cast<size_t>(kPeerSlot[i])];
        slot = next;
        slot.peer = i;
        m_plan.peers[i] = m_plan.peers[i + 1];
        m_plan.names[i] = m_plan.names[i + 1];
        m_plan.ready[i] = m_plan.ready[i + 1];
        m_plan.pingMs[i] = m_plan.pingMs[i + 1];
        m_acked[i] = m_acked[i + 1];
        m_sincePeer[i] = m_sincePeer[i + 1];
        m_echo[i] = m_echo[i + 1];
    }
    const std::uint8_t last = --m_plan.peerCount;
    m_plan.slots[static_cast<size_t>(kPeerSlot[last])].peer = -1;
    m_plan.peers[last] = {};
    m_plan.names[last].clear();
    m_plan.ready[last] = false;
    m_plan.pingMs[last] = 0;
    m_acked[last] = false;
}

bool Lobby::can_start() const {
    if (!m_isHost || m_plan.started || m_plan.peerCount < 2) return false;
    for (std::uint8_t i = 0; i < m_plan.peerCount; ++i)
        if (!m_plan.ready[i]) return false;
    return true;
}

void Lobby::start() {
    if (can_start()) m_plan.started = true;
}

void Lobby::next_match(std::uint32_t token, std::uint32_t seed) {
    m_playedToken = m_plan.token;
    m_ready = false;
    m_choice.ready = false;
    m_sinceHeard = 0;
    m_sincePeer = {};
    m_acked = {};
    if (!m_isHost) return;
    m_plan.token = token;
    m_plan.seed = seed;
    m_plan.started = false;
    m_plan.ready = {};
}

void Lobby::leave() {
    if (m_isHost) {
        const auto out = encode_refusal(Refusal::HostLeft);
        for (std::uint8_t i = 1; i < m_plan.peerCount; ++i) m_socket->send(m_plan.peers[i], out.data(), out.size());
    } else {
        const auto out = encode_bye();
        m_socket->send(m_host, out.data(), out.size());
    }
}

void Lobby::send_hello(bool started) {
    Hello hello;
    hello.gameData = m_gameData;
    hello.started = started;
    hello.choice = m_choice;
    hello.sequence = ++m_sequence;
    hello.pingMs = m_plan.pingMs[m_localPeer];
    m_sentAt[m_sequence % kPingSlots] = m_clock;
    const auto out = encode_hello(hello);
    m_socket->send(m_host, out.data(), out.size());
}

void Lobby::send_plan(std::uint8_t peer) {
    const auto out = encode_plan(m_plan, peer, m_echo[peer]);
    m_socket->send(m_plan.peers[peer], out.data(), out.size());
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
        std::uint16_t echo;
        if (!decode_plan(packet, plan, peer, echo)) return;
        m_sinceHeard = 0;
        m_plan = plan;
        m_localPeer = peer;
        m_plan.peers[0] = m_host;
        // The newest answer tells the time to the host and back, and the host passes it around.
        m_plan.pingMs[peer] = static_cast<std::uint16_t>(m_clock - m_sentAt[echo % kPingSlots]);
        if (plan.started && plan.token != m_playedToken) {
            m_ready = true;
            send_hello(true);
        }
        return;
    }

    std::uint8_t known = 0;
    for (std::uint8_t i = 1; i < m_plan.peerCount && !known; ++i)
        if (m_plan.peers[i] == from) known = i;
    if (decode_bye(packet)) {
        if (known && !m_plan.started) remove_peer(known);
        return;
    }
    Hello hello;
    if (!decode_hello(packet, hello)) return;
    const auto refuse = [&](Refusal why) {
        const auto out = encode_refusal(why);
        m_socket->send(from, out.data(), out.size());
    };
    if (hello.version != kProtocolVersion) return refuse(Refusal::WrongVersion);
    if (hello.gameData != m_gameData) return refuse(Refusal::WrongGameData);
    if (!known) {
        if (m_plan.started || m_plan.peerCount >= 4) return refuse(Refusal::RoomFull);
        known = m_plan.peerCount++;
        m_plan.peers[known] = from;
        m_acked[known] = false;
    }
    m_sincePeer[known] = 0;
    m_echo[known] = hello.sequence;
    m_plan.pingMs[known] = hello.pingMs;
    if (!m_plan.started) apply_choice(known, hello.choice);
    if (hello.started && m_plan.started) m_acked[known] = true;
    // At once, not on the resend timer, or the joiner's ping would measure the timer.
    send_plan(known);
}

void Lobby::poll(unsigned elapsedMs) {
    m_clock += elapsedMs;
    Address from;
    std::vector<std::uint8_t> packet;
    while (m_socket->receive(from, packet))
        if (!packet.empty() && packet[0] == kLobbyPacket) handle(from, packet);
    m_sinceSend += elapsedMs;
    m_sinceHeard += elapsedMs;

    if (m_isHost && !m_plan.started) {
        for (std::uint8_t i = 1; i < m_plan.peerCount;) {
            m_sincePeer[i] += elapsedMs;
            if (m_sincePeer[i] >= kSilenceMs) remove_peer(i);
            else ++i;
        }
    }
    if (m_sinceSend >= kResendMs) {
        m_sinceSend = 0;
        if (!m_isHost) {
            if (!m_ready) send_hello(false);
        } else {
            for (std::uint8_t i = 1; i < m_plan.peerCount; ++i) send_plan(i);
            if (m_plan.started) {
                bool everyone = true;
                for (std::uint8_t i = 1; i < m_plan.peerCount; ++i) everyone = everyone && m_acked[i];
                m_ready = everyone;
            }
        }
    }
}

}  // namespace net
