#include "net/lobby.h"

#include <algorithm>
#include <cstring>
#include <fstream>
#include <random>

namespace net {

namespace {

constexpr unsigned kResendMs = 100;
constexpr unsigned kProbeMs = 200;
constexpr unsigned kServerMs = 1000;
constexpr unsigned kOpeningMs = 3000;
enum Kind : std::uint8_t { KindHello = 1, KindPlan = 2, KindRefused = 3, KindBye = 4, KindLinkPing = 5, KindLinkPong = 6, KindOpen = 7 };

// server/protocol.go is the other side of these.
constexpr std::uint8_t kServerMagic[4] = {'D', 'B', 'R', '1'};
constexpr std::uint16_t kServerVersion = 1;
constexpr size_t kServerRequestSize = 48;
constexpr std::uint8_t kServerHost = 'H', kServerJoin = 'J', kServerHosted = 'h', kServerRoom = 'j', kServerJoiner = 'n', kServerError = 'x';


template <class T>
void put(std::vector<std::uint8_t>& out, T value) {
    for (size_t i = 0; i < sizeof(T); ++i) out.push_back(static_cast<std::uint8_t>(static_cast<std::uint64_t>(value) >> (8 * i)));
}

void put_name(std::vector<std::uint8_t>& out, const std::string& name) {
    for (size_t i = 0; i < kMaxNameLength; ++i) out.push_back(i < name.size() ? static_cast<std::uint8_t>(name[i]) : 0);
}

void put_address(std::vector<std::uint8_t>& out, const Address& address) {
    put<std::uint32_t>(out, address.ip);
    put<std::uint16_t>(out, address.port);
}

void put_server_endpoint(std::uint8_t* out, const Address& address) {
    std::memcpy(out, &address.ip, 4);
    out[4] = static_cast<std::uint8_t>(address.port >> 8);
    out[5] = static_cast<std::uint8_t>(address.port);
}

Address get_server_endpoint(const std::uint8_t* in) {
    Address address;
    std::memcpy(&address.ip, in, 4);
    address.port = static_cast<std::uint16_t>((in[4] << 8) | in[5]);
    return address;
}

std::uint32_t new_client_id() {
    std::random_device random;
    return random() | 1u;
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
    Address address() {
        Address out;
        out.ip = get<std::uint32_t>();
        out.port = get<std::uint16_t>();
        return out;
    }
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

}  // namespace

const char* refusal_text(Refusal refusal) {
    switch (refusal) {
        case Refusal::WrongVersion: return "This player has a different version of the game.";
        case Refusal::WrongGameData: return "This player has different game data.";
        case Refusal::RoomFull: return "The room is full, or its match has started.";
        case Refusal::HostLeft: return "The host closed the room.";
        case Refusal::NoSuchRoom: return "No room has that code.";
        case Refusal::TooManyTries: return "Too many tries. Wait a minute and try again.";
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
    put_name(out, hello.choice.name);
    put<std::uint16_t>(out, hello.sequence);
    put<std::uint16_t>(out, hello.pingMs);
    put<std::uint32_t>(out, hello.clientId);
    put_address(out, hello.publicAddress);
    put_address(out, hello.privateAddress);
    put<std::uint8_t>(out, hello.links);
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
    out.choice.name = in.name();
    out.sequence = in.get<std::uint16_t>();
    out.pingMs = in.get<std::uint16_t>();
    out.clientId = in.get<std::uint32_t>();
    out.publicAddress = in.address();
    out.privateAddress = in.address();
    out.links = in.get<std::uint8_t>();
    if (!in.ok || in.at != packet.size()) return false;
    hello = out;
    return true;
}

std::vector<std::uint8_t> encode_plan(const MatchPlan& plan, std::uint8_t yourPeer, std::uint16_t echo) {
    std::vector<std::uint8_t> out{kLobbyPacket, KindPlan};
    put<std::uint8_t>(out, yourPeer);
    put<std::uint16_t>(out, echo);
    put<std::uint32_t>(out, plan.token);
    put<std::uint32_t>(out, plan.seed);
    put<std::uint8_t>(out, plan.peerCount);
    for (size_t i = 0; i < plan.peers.size(); ++i) {
        put_address(out, plan.peers[i]);
        put_address(out, plan.publics[i]);
        put_address(out, plan.privates[i]);
        put<std::uint32_t>(out, plan.clientIds[i]);
        put<std::uint8_t>(out, plan.links[i]);
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
    out.peerCount = in.get<std::uint8_t>();
    for (size_t i = 0; i < out.peers.size(); ++i) {
        out.peers[i] = in.address();
        out.publics[i] = in.address();
        out.privates[i] = in.address();
        out.clientIds[i] = in.get<std::uint32_t>();
        out.links[i] = in.get<std::uint8_t>();
        out.names[i] = in.name();
        out.ready[i] = in.get<std::uint8_t>() != 0;
        out.pingMs[i] = in.get<std::uint16_t>();
    }
    out.started = in.get<std::uint8_t>() != 0;
    if (!in.ok || in.at != packet.size()) return false;
    if (out.peerCount < 2 || out.peerCount > 4 || yourPeer >= out.peerCount) return false;
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

Lobby Lobby::host(UdpSocket& socket, MatchPlan plan, std::uint64_t gameData, Address server) {
    Lobby lobby(socket, gameData);
    lobby.m_isHost = true;
    lobby.m_plan = plan;
    lobby.m_plan.started = false;
    lobby.m_plan.peerCount = 1;
    lobby.m_clientId = new_client_id();
    lobby.m_plan.clientIds[0] = lobby.m_clientId;
    lobby.m_private = socket.local_address();
    lobby.m_plan.privates[0] = lobby.m_private;
    lobby.m_server = server;
    return lobby;
}

Lobby Lobby::join(UdpSocket& socket, Address host, std::uint64_t gameData) {
    Lobby lobby(socket, gameData);
    lobby.m_hostCandidates = {host};
    lobby.m_clientId = new_client_id();
    lobby.m_private = socket.local_address();
    return lobby;
}

Lobby Lobby::join_code(UdpSocket& socket, Address server, const std::string& code, std::uint64_t gameData) {
    Lobby lobby(socket, gameData);
    lobby.m_server = server;
    lobby.m_wantedCode = code;
    lobby.m_clientId = new_client_id();
    lobby.m_private = socket.local_address();
    return lobby;
}

void Lobby::apply_choice(std::uint8_t peer, const LocalChoice& choice) {
    m_plan.names[peer] = choice.name;
    m_plan.ready[peer] = choice.ready;
}

void Lobby::set_choice(const LocalChoice& choice) {
    m_choice = choice;
    if (m_isHost) apply_choice(0, choice);
}

void Lobby::remove_peer(std::uint8_t peer) {
    for (std::uint8_t i = peer; i + 1 < m_plan.peerCount; ++i) {
        m_plan.peers[i] = m_plan.peers[i + 1];
        m_plan.publics[i] = m_plan.publics[i + 1];
        m_plan.privates[i] = m_plan.privates[i + 1];
        m_plan.clientIds[i] = m_plan.clientIds[i + 1];
        m_plan.names[i] = m_plan.names[i + 1];
        m_plan.ready[i] = m_plan.ready[i + 1];
        m_plan.pingMs[i] = m_plan.pingMs[i + 1];
        m_acked[i] = m_acked[i + 1];
        m_sincePeer[i] = m_sincePeer[i + 1];
        m_echo[i] = m_echo[i + 1];
    }
    const std::uint8_t last = --m_plan.peerCount;
    m_plan.peers[last] = {};
    m_plan.publics[last] = {};
    m_plan.privates[last] = {};
    m_plan.clientIds[last] = 0;
    m_plan.links[last] = 0;
    m_plan.names[last].clear();
    m_plan.ready[last] = false;
    m_plan.pingMs[last] = 0;
    m_acked[last] = false;
}

std::uint8_t Lobby::own_links() const {
    std::uint8_t mask = 0;
    for (std::uint8_t i = 0; i < m_plan.peerCount; ++i)
        for (const Link& link : m_links)
            if (i != m_localPeer && link.clientId == m_plan.clientIds[i] && link.sinceHeard < kSilenceMs) mask |= static_cast<std::uint8_t>(1u << i);
    return mask;
}

bool Lobby::full_mesh() const {
    for (std::uint8_t i = 0; i < m_plan.peerCount; ++i)
        for (std::uint8_t j = 0; j < m_plan.peerCount; ++j)
            if (i != j && !(m_plan.links[i] & (1u << j))) return false;
    return true;
}

bool Lobby::can_start() const {
    if (!m_isHost || m_plan.started || m_plan.peerCount < 2) return false;
    for (std::uint8_t i = 0; i < m_plan.peerCount; ++i)
        if (!m_plan.ready[i]) return false;
    return full_mesh();
}

MatchPlan Lobby::plan_for_match() const {
    MatchPlan out = m_plan;
    for (std::uint8_t i = 0; i < m_plan.peerCount; ++i)
        for (const Link& link : m_links)
            if (i != m_localPeer && link.clientId == m_plan.clientIds[i]) out.peers[i] = link.address;
    return out;
}

std::string Lobby::link_problem() const {
    if (m_sinceAllReady < kLinkProblemMs) return {};
    for (std::uint8_t i = 0; i < m_plan.peerCount; ++i)
        for (std::uint8_t j = 0; j < m_plan.peerCount; ++j)
            if (i != j && !(m_plan.links[i] & (1u << j))) return m_plan.names[i] + " cannot reach " + m_plan.names[j] + ".";
    return {};
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
    hello.clientId = m_clientId;
    hello.publicAddress = m_public;
    hello.privateAddress = m_private;
    hello.links = own_links();
    m_sentAt[m_sequence % kPingSlots] = m_clock;
    const auto out = encode_hello(hello);
    if (m_heardHost) m_socket->send(m_host, out.data(), out.size());
    else for (const Address& candidate : m_hostCandidates) m_socket->send(candidate, out.data(), out.size());
}

void Lobby::send_to_server() {
    std::vector<std::uint8_t> out(kServerRequestSize, 0);
    std::memcpy(out.data(), kServerMagic, sizeof kServerMagic);
    out[4] = m_isHost ? kServerHost : kServerJoin;
    out[5] = static_cast<std::uint8_t>(kServerVersion);
    out[6] = static_cast<std::uint8_t>(kServerVersion >> 8);
    for (size_t i = 0; i < 4; ++i) out[7 + i] = static_cast<std::uint8_t>(m_clientId >> (8 * i));
    put_server_endpoint(out.data() + 11, m_private);
    if (!m_isHost) std::memcpy(out.data() + 17, m_wantedCode.data(), std::min(m_wantedCode.size(), kRoomCodeLength));
    m_socket->send(m_server, out.data(), out.size());
}

void Lobby::handle_server(const std::vector<std::uint8_t>& packet) {
    if (packet.size() < 3) return;
    const std::uint8_t kind = packet[1];
    if (kind == kServerError) {
        if (packet[2] == 1) m_refused = Refusal::NoSuchRoom;
        else if (packet[2] == 2) m_refused = Refusal::WrongVersion;
        else if (packet[2] == 3) m_refused = Refusal::TooManyTries;
    } else if (m_isHost && kind == kServerHosted && packet.size() == 2 + kRoomCodeLength + 6) {
        const std::string code(packet.begin() + 2, packet.begin() + 2 + kRoomCodeLength);
        if (std::all_of(code.begin(), code.end(), [](char c) { return c >= '2' && c <= 'Z'; })) m_code = code;
        m_public = get_server_endpoint(packet.data() + 2 + kRoomCodeLength);
        m_plan.publics[0] = m_public;
    } else if (m_isHost && kind == kServerJoiner && packet.size() == 2 + 12) {
        if (m_openings.size() < 8)
            m_openings.push_back({get_server_endpoint(packet.data() + 2), get_server_endpoint(packet.data() + 8), kOpeningMs});
    } else if (!m_isHost && kind == kServerRoom && packet.size() == 2 + 18) {
        m_hostCandidates = {get_server_endpoint(packet.data() + 2), get_server_endpoint(packet.data() + 8)};
        m_public = get_server_endpoint(packet.data() + 14);
    }
}

// Every peer keeps knocking on everywhere another may be. Sending opens this side's router, and the
// first answer says which address works.
void Lobby::send_link_probes() {
    std::vector<std::uint8_t> ping{kLobbyPacket, KindLinkPing};
    put<std::uint32_t>(ping, m_plan.token);
    put<std::uint32_t>(ping, m_clientId);
    for (std::uint8_t i = 0; i < m_plan.peerCount; ++i) {
        if (i == m_localPeer || m_plan.clientIds[i] == 0) continue;
        const Link* known = nullptr;
        for (const Link& link : m_links)
            if (link.clientId == m_plan.clientIds[i] && link.sinceHeard < kSilenceMs) known = &link;
        if (known) {
            m_socket->send(known->address, ping.data(), ping.size());
            continue;
        }
        for (const Address& candidate : {m_plan.peers[i], m_plan.publics[i], m_plan.privates[i]})
            if (candidate.port != 0) m_socket->send(candidate, ping.data(), ping.size());
    }
    const std::vector<std::uint8_t> open{kLobbyPacket, KindOpen};
    for (const Opening& opening : m_openings) {
        for (const Address& candidate : {opening.publicAddress, opening.privateAddress})
            if (candidate.port != 0) m_socket->send(candidate, open.data(), open.size());
    }
}

bool Lobby::handle_link(const Address& from, const std::vector<std::uint8_t>& packet) {
    if (packet.size() < 2) return false;
    if (packet[1] == KindOpen) return true;
    if (packet[1] != KindLinkPing && packet[1] != KindLinkPong) return false;
    Reader in{packet, 2};
    const auto token = in.get<std::uint32_t>();
    const auto clientId = in.get<std::uint32_t>();
    if (!in.ok || in.at != packet.size() || token != m_plan.token || token == 0) return true;
    if (packet[1] == KindLinkPing) {
        std::vector<std::uint8_t> pong{kLobbyPacket, KindLinkPong};
        put<std::uint32_t>(pong, token);
        put<std::uint32_t>(pong, m_clientId);
        m_socket->send(from, pong.data(), pong.size());
        return true;
    }
    for (Link& link : m_links) {
        if (link.clientId != clientId) continue;
        // The first address that worked stays, since a private one may also answer after a public one.
        if (link.sinceHeard >= kSilenceMs) link.address = from;
        link.sinceHeard = 0;
        return true;
    }
    if (m_links.size() < 16) m_links.push_back({clientId, from, 0});
    return true;
}

void Lobby::send_plan(std::uint8_t peer) {
    const auto out = encode_plan(m_plan, peer, m_echo[peer]);
    m_socket->send(m_plan.peers[peer], out.data(), out.size());
}

void Lobby::handle(const Address& from, const std::vector<std::uint8_t>& packet) {
    if (handle_link(from, packet)) return;
    if (!m_isHost) {
        bool fromHost = m_heardHost && from == m_host;
        if (!m_heardHost)
            for (const Address& candidate : m_hostCandidates) fromHost = fromHost || candidate == from;
        if (!fromHost) return;
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
        m_heardHost = true;
        m_host = from;
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
    if (decode_bye(packet)) {
        for (std::uint8_t i = 1; i < m_plan.peerCount && !known; ++i)
            if (m_plan.peers[i] == from) known = i;
        if (known && !m_plan.started) remove_peer(known);
        return;
    }
    Hello hello;
    if (!decode_hello(packet, hello)) return;
    // By ID, not address: a joiner tries two addresses of ours, which can show it as two of its own.
    for (std::uint8_t i = 1; i < m_plan.peerCount && !known; ++i)
        if (m_plan.clientIds[i] == hello.clientId) known = i;
    const auto refuse = [&](Refusal why) {
        const auto out = encode_refusal(why);
        m_socket->send(from, out.data(), out.size());
    };
    if (hello.version != kProtocolVersion) return refuse(Refusal::WrongVersion);
    if (hello.gameData != m_gameData) return refuse(Refusal::WrongGameData);
    if (!known) {
        if (m_plan.started || m_plan.peerCount >= 4) return refuse(Refusal::RoomFull);
        known = m_plan.peerCount++;
        m_plan.clientIds[known] = hello.clientId;
        m_acked[known] = false;
    }
    m_plan.peers[known] = from;
    m_plan.publics[known] = hello.publicAddress;
    m_plan.privates[known] = hello.privateAddress;
    m_plan.links[known] = hello.links;
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
    while (m_socket->receive(from, packet)) {
        if (packet.empty()) continue;
        if (packet[0] == kLobbyPacket) handle(from, packet);
        else if (packet[0] == kServerPacket && m_server.port != 0 && from == m_server) handle_server(packet);
    }
    m_sinceSend += elapsedMs;
    m_sinceHeard += elapsedMs;
    m_sinceServer += elapsedMs;
    m_sinceProbe += elapsedMs;
    for (Link& link : m_links) link.sinceHeard += elapsedMs;
    if (m_isHost) m_plan.links[0] = own_links();

    // A host keeps its room alive. A joiner asks until it is answered.
    const bool wantServer = m_server.port != 0 && (m_isHost ? !m_plan.started : m_hostCandidates.empty() && m_refused == Refusal::None);
    if (wantServer && (m_sinceServer >= kServerMs || m_sinceServer == elapsedMs)) {
        m_sinceServer = 0;
        send_to_server();
    }
    if (m_sinceProbe >= kProbeMs) {
        m_sinceProbe = 0;
        send_link_probes();
        for (Opening& opening : m_openings) opening.leftMs -= std::min(opening.leftMs, kProbeMs);
        m_openings.erase(std::remove_if(m_openings.begin(), m_openings.end(), [](const Opening& o) { return o.leftMs == 0; }), m_openings.end());
    }
    bool allReady = m_plan.peerCount >= 2;
    for (std::uint8_t i = 0; i < m_plan.peerCount; ++i) allReady = allReady && m_plan.ready[i];
    m_sinceAllReady = allReady ? m_sinceAllReady + elapsedMs : 0;

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
