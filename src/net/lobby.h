#pragma once
// Who plays what, agreed before a match. The lobby has no acknowledgements: each side keeps sending
// its whole current state until the other's state shows it arrived, so a lost packet costs a resend.
#include <array>
#include <cstdint>
#include <string>
#include <vector>

#include "net/udp_socket.h"

namespace net {

constexpr std::uint16_t kProtocolVersion = 2;
constexpr std::uint8_t kLobbyPacket = 'L';
constexpr std::uint8_t kGamePacket = 'G';
constexpr size_t kMaxNameLength = 12;
constexpr std::uint16_t kDefaultPort = 37564;  // the original's (docs/game-spec.md)

enum class Refusal : std::uint8_t { None, WrongVersion, WrongGameData, RoomFull, HostLeft };
const char* refusal_text(Refusal refusal);

struct PlanSlot {
    int character = 0, weapon = 0, costume = 0;
    unsigned specialMode = 1;
    int peer = -1;  // the human who plays it, or -1 for COM
};

// What every peer must start from. Peers fill the teams in turn, so two players face each other.
constexpr std::array<int, 4> kPeerSlot{{0, 2, 1, 3}};

struct MatchPlan {
    std::uint32_t token = 0;  // proves a packet belongs to this match
    std::uint32_t seed = 1;
    unsigned stage = 1, variation = 0;
    unsigned timeLimitSeconds = 0;
    std::array<int, 4> rules{{100, 100, 100, 100}};
    std::array<PlanSlot, 4> slots{};
    std::uint8_t peerCount = 1;
    std::array<Address, 4> peers{};  // peer 0 is the host, whose address each joiner dialed
    std::array<std::string, 4> names{};
    std::array<bool, 4> ready{};
    std::array<std::uint16_t, 4> pingMs{};  // to the host, as each joiner measures it
    bool started = false;
};

// What one player chooses for themselves.
struct LocalChoice {
    std::string name;
    int character = 0, weapon = 0, costume = 0;
    unsigned specialMode = 1;
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
    static Lobby host(UdpSocket& socket, MatchPlan plan, std::uint64_t gameData);
    static Lobby join(UdpSocket& socket, Address host, std::uint64_t gameData);

    // Reads what arrived and resends what is due. `elapsedMs` is since the last call.
    void poll(unsigned elapsedMs);
    // A packet the session passed on, because the lobby's traffic continues after a peer starts.
    void handle(const Address& from, const std::vector<std::uint8_t>& packet);

    void set_choice(const LocalChoice& choice);
    bool is_host() const { return m_isHost; }
    // Host only: the stage, rules and COM slots of the next match.
    MatchPlan& edit_plan() { return m_plan; }
    bool can_start() const;
    void start();

    // Once a match is over: the room stays, and everyone chooses again.
    void next_match(std::uint32_t token, std::uint32_t seed);
    // Tells the others at once. Silence would also reach them, after a timeout.
    void leave();

    bool ready() const { return m_ready; }
    Refusal refused() const { return m_refused; }
    bool host_lost() const { return !m_isHost && m_sinceHeard >= kSilenceMs; }
    const MatchPlan& plan() const { return m_plan; }
    std::uint8_t local_peer() const { return m_localPeer; }

private:
    static constexpr unsigned kSilenceMs = 5000;
    static constexpr unsigned kPingSlots = 32;

    Lobby(UdpSocket& socket, std::uint64_t gameData) : m_socket(&socket), m_gameData(gameData) {}
    void send_hello(bool started);
    void send_plan(std::uint8_t peer);
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
    bool m_ready = false;
    Refusal m_refused = Refusal::None;
    unsigned m_sinceSend = 0;
    unsigned m_sinceHeard = 0;
};

}  // namespace net
