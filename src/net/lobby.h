#pragma once
// Who plays what, agreed before a match. The lobby has no acknowledgements: each side keeps sending
// its whole current state until the other's state shows it arrived, so a lost packet costs a resend.
#include <array>
#include <cstdint>
#include <string>
#include <vector>

#include "net/udp_socket.h"

namespace net {

constexpr std::uint16_t kProtocolVersion = 1;
constexpr std::uint8_t kLobbyPacket = 'L';
constexpr std::uint8_t kGamePacket = 'G';

enum class Refusal : std::uint8_t { None, WrongVersion, WrongGameData, RoomFull };
const char* refusal_text(Refusal refusal);

struct PlanSlot {
    int character = 0, weapon = 0, costume = 0;
    unsigned specialMode = 1;
    int peer = -1;  // the human who plays it, or -1 for COM
};

// What every peer must start from.
struct MatchPlan {
    std::uint32_t token = 0;  // proves a packet belongs to this match
    std::uint32_t seed = 1;
    unsigned stage = 1;
    unsigned timeLimitSeconds = 0;
    std::array<int, 4> rules{{100, 100, 100, 100}};
    std::array<PlanSlot, 4> slots{};
    std::uint8_t peerCount = 0;
    std::array<Address, 4> peers{};  // peer 0 is the host, whose address each joiner dialed
    bool started = false;
};

// The wire format, device-free so hostile bytes are testable. Decoders refuse anything malformed.
std::vector<std::uint8_t> encode_hello(std::uint64_t gameData, bool started);
bool decode_hello(const std::vector<std::uint8_t>& packet, std::uint16_t& version, std::uint64_t& gameData, bool& started);
std::vector<std::uint8_t> encode_plan(const MatchPlan& plan, std::uint8_t yourPeer);
bool decode_plan(const std::vector<std::uint8_t>& packet, MatchPlan& plan, std::uint8_t& yourPeer);
std::vector<std::uint8_t> encode_refusal(Refusal refusal);
bool decode_refusal(const std::vector<std::uint8_t>& packet, Refusal& refusal);

// A cheap fingerprint of the install's bundles: sizes, and each one's first and last megabyte. An
// in-game desync still catches what this misses. 0 when none could be read.
std::uint64_t game_data_hash(const std::string& gameDir);

class Lobby {
public:
    // `plan.slots` names the humans as peers 0..n-1, and the host fills in the rest.
    static Lobby host(UdpSocket& socket, MatchPlan plan, std::uint64_t gameData);
    static Lobby join(UdpSocket& socket, Address host, std::uint64_t gameData);

    // Reads what arrived and resends what is due. `elapsedMs` is since the last call.
    void poll(unsigned elapsedMs);
    // A packet the session passed on, because the lobby's traffic continues after a peer starts.
    void handle(const Address& from, const std::vector<std::uint8_t>& packet);

    bool ready() const { return m_ready; }
    Refusal refused() const { return m_refused; }
    const MatchPlan& plan() const { return m_plan; }
    std::uint8_t local_peer() const { return m_localPeer; }

private:
    Lobby(UdpSocket& socket, std::uint64_t gameData) : m_socket(&socket), m_gameData(gameData) {}
    void send_state();

    UdpSocket* m_socket;
    std::uint64_t m_gameData;
    bool m_isHost = false;
    Address m_host;
    MatchPlan m_plan;
    std::uint8_t m_localPeer = 0;
    std::array<bool, 4> m_started{};
    bool m_ready = false;
    Refusal m_refused = Refusal::None;
    unsigned m_sinceSend = 0;
};

}  // namespace net
