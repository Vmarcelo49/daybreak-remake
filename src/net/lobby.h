#pragma once
// Who plays what, agreed before a match. The lobby has no acknowledgements: each side keeps sending
// its whole current state until the other's state shows it arrived, so a lost packet costs a resend.
#include <array>
#include <cstdint>
#include <string>
#include <vector>

#include "net/udp_socket.h"

namespace net {

constexpr std::uint16_t kProtocolVersion = 4;
constexpr std::uint8_t kLobbyPacket = 'L';
constexpr std::uint8_t kGamePacket = 'G';
constexpr std::uint8_t kServerPacket = 'R';
constexpr size_t kRoomCodeLength = 4;
constexpr size_t kMaxNameLength = 12;
constexpr std::uint16_t kDefaultPort = 37564;  // the original's (docs/game-spec.md)

enum class Refusal : std::uint8_t { None, WrongVersion, WrongGameData, RoomFull, HostLeft, NoSuchRoom, TooManyTries };
const char* refusal_text(Refusal refusal);

struct PlanSlot {
    int character = 0, weapon = 0, costume = 0;
    unsigned specialMode = 1;
    int peer = -1;  // the human who plays it, or -1 for COM
};

// What the room agrees on, and what every peer then fills in for itself. The lobby sends only who
// is here. The stage, rules and slots come from the selection screen, which every peer runs with the
// same inputs, so they need no packet.
struct MatchPlan {
    std::uint32_t token = 0;  // proves a packet belongs to this match
    std::uint32_t seed = 1;
    unsigned stage = 1, variation = 0;
    unsigned timeLimitSeconds = 0;
    std::array<int, 4> rules{{100, 100, 100, 100}};
    std::array<PlanSlot, 4> slots{};
    std::uint8_t peerCount = 1;
    std::array<Address, 4> peers{};  // as the host reaches them; peer 0 is the host, as each joiner did
    std::array<Address, 4> publics{}, privates{};  // where else a peer may be reached
    std::array<std::uint32_t, 4> clientIds{};
    std::array<std::uint8_t, 4> links{};  // per peer, a bit for each other peer it has reached
    std::array<std::string, 4> names{};
    std::array<bool, 4> ready{};
    std::array<std::uint16_t, 4> pingMs{};  // to the host, as each joiner measures it
    bool started = false;
};

// What one player says in the lobby.
struct LocalChoice {
    std::string name;
    bool ready = false;
};

// A joiner's whole state, as a hello packet says it.
struct Hello {
    std::uint16_t version = kProtocolVersion;
    std::uint64_t gameData = 0;
    bool started = false;
    LocalChoice choice;
    std::uint16_t sequence = 0;
    std::uint16_t pingMs = 0;
    std::uint32_t clientId = 0;
    Address publicAddress, privateAddress;
    std::uint8_t links = 0;
};

// The wire format, device-free so hostile bytes are testable. Decoders refuse anything malformed.
std::vector<std::uint8_t> encode_hello(const Hello& hello);
bool decode_hello(const std::vector<std::uint8_t>& packet, Hello& hello);
std::vector<std::uint8_t> encode_plan(const MatchPlan& plan, std::uint8_t yourPeer, std::uint16_t echo);
bool decode_plan(const std::vector<std::uint8_t>& packet, MatchPlan& plan, std::uint8_t& yourPeer, std::uint16_t& echo);
std::vector<std::uint8_t> encode_refusal(Refusal refusal);
bool decode_refusal(const std::vector<std::uint8_t>& packet, Refusal& refusal);
std::vector<std::uint8_t> encode_bye();
bool decode_bye(const std::vector<std::uint8_t>& packet);

// A cheap fingerprint of the install's bundles: sizes, and each one's first and last megabyte. An
// in-game desync still catches what this misses. 0 when none could be read.
std::uint64_t game_data_hash(const std::string& gameDir);

class Lobby {
public:
    // `server` is the rendezvous server, for a room code. A zero port means none.
    static Lobby host(UdpSocket& socket, MatchPlan plan, std::uint64_t gameData, Address server = {});
    static Lobby join(UdpSocket& socket, Address host, std::uint64_t gameData);
    static Lobby join_code(UdpSocket& socket, Address server, const std::string& code, std::uint64_t gameData);

    // Reads what arrived and resends what is due. `elapsedMs` is since the last call.
    void poll(unsigned elapsedMs);
    // A packet the session passed on, because the lobby's traffic continues after a peer starts.
    void handle(const Address& from, const std::vector<std::uint8_t>& packet);

    void set_choice(const LocalChoice& choice);
    bool is_host() const { return m_isHost; }
    bool can_start() const;
    void start();
    // Every peer's address as this machine reached it, for the match.
    MatchPlan plan_for_match() const;
    // Empty until a server has given one.
    const std::string& room_code() const { return m_code; }
    // Who cannot reach whom, once everyone is ready and has had time to connect. Empty otherwise.
    std::string link_problem() const;

    // Once a match is over: the room stays, and everyone chooses again.
    void next_match(std::uint32_t token, std::uint32_t seed);
    // Tells the others at once. Silence would also reach them, after a timeout.
    void leave();

    bool ready() const { return m_ready; }
    Refusal refused() const { return m_refused; }
    bool host_lost() const { return !m_isHost && m_sinceHeard >= (m_heardHost ? kSilenceMs : kFirstContactMs); }
    const MatchPlan& plan() const { return m_plan; }
    std::uint8_t local_peer() const { return m_localPeer; }

private:
    static constexpr unsigned kSilenceMs = 5000;
    static constexpr unsigned kFirstContactMs = 10000;
    static constexpr unsigned kLinkProblemMs = 10000;
    static constexpr unsigned kPingSlots = 32;

    Lobby(UdpSocket& socket, std::uint64_t gameData) : m_socket(&socket), m_gameData(gameData) {}
    void send_hello(bool started);
    void send_plan(std::uint8_t peer);
    void send_to_server();
    void send_link_probes();
    void handle_server(const std::vector<std::uint8_t>& packet);
    bool handle_link(const Address& from, const std::vector<std::uint8_t>& packet);
    std::uint8_t own_links() const;
    bool full_mesh() const;
    void apply_choice(std::uint8_t peer, const LocalChoice& choice);
    void remove_peer(std::uint8_t peer);

    UdpSocket* m_socket;
    std::uint64_t m_gameData;
    bool m_isHost = false;
    Address m_host;
    MatchPlan m_plan;
    std::uint8_t m_localPeer = 0;
    LocalChoice m_choice;
    std::array<bool, 4> m_acked{};
    std::array<unsigned, 4> m_sincePeer{};
    std::array<std::uint16_t, 4> m_echo{};
    std::array<unsigned, kPingSlots> m_sentAt{};
    std::uint16_t m_sequence = 0;
    std::uint32_t m_playedToken = 0;
    unsigned m_clock = 0;
    // The reachable address of each peer we have heard from, by client ID.
    struct Link {
        std::uint32_t clientId = 0;
        Address address;
        unsigned sinceHeard = 0;
    };
    std::vector<Link> m_links;
    // A joiner the host is opening its router to.
    struct Opening {
        Address publicAddress, privateAddress;
        unsigned leftMs = 0;
    };
    std::vector<Opening> m_openings;
    std::uint32_t m_clientId = 0;
    Address m_server, m_public, m_private;
    std::vector<Address> m_hostCandidates;
    std::string m_code, m_wantedCode;
    bool m_heardHost = false;
    unsigned m_sinceServer = 0, m_sinceProbe = 0, m_sinceAllReady = 0;
    bool m_ready = false;
    Refusal m_refused = Refusal::None;
    unsigned m_sinceSend = 0;
    unsigned m_sinceHeard = 0;
};

}  // namespace net
