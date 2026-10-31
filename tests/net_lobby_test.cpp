// Online lobby (docs/ONLINE-PLAN.md, step 4): its packets come from strangers, so every malformed one
// has to be refused, and a host and joiners have to agree over a real socket.
#include <cstdio>
#include <string>

#include "net/lobby.h"

namespace {

int failures = 0;
void check(bool condition, const std::string& name) {
    if (condition) return;
    ++failures;
    std::printf("FAIL: %s\n", name.c_str());
}

net::MatchPlan sample_plan() {
    net::MatchPlan plan;
    plan.token = 0x12345678;
    plan.seed = 77;
    plan.stage = 21;
    plan.timeLimitSeconds = 300;
    plan.rules = {100, 150, 80, 120};
    plan.peerCount = 2;
    plan.slots[0] = {3, 1, 2, 0, 0};
    plan.slots[1] = {4, 2, 0, 2, -1};
    plan.slots[2] = {5, 0, 0, 1, 1};
    plan.slots[3] = {6, 0, 0, 1, -1};
    net::parse_address("10.1.2.3:4000", plan.peers[1]);
    plan.started = true;
    return plan;
}

void test_round_trips() {
    const net::MatchPlan plan = sample_plan();
    net::MatchPlan decoded;
    std::uint8_t peer = 0;
    check(net::decode_plan(net::encode_plan(plan, 1), decoded, peer), "a good plan is refused");
    check(peer == 1 && decoded.token == plan.token && decoded.seed == 77 && decoded.stage == 21, "plan header");
    check(decoded.timeLimitSeconds == 300 && decoded.rules == plan.rules && decoded.started, "plan rules");
    check(decoded.slots[2].character == 5 && decoded.slots[2].peer == 1 && decoded.slots[1].peer == -1, "plan slots");
    check(decoded.peers[1] == plan.peers[1], "plan peers");

    std::uint16_t version = 0;
    std::uint64_t data = 0;
    bool started = false;
    check(net::decode_hello(net::encode_hello(99, true), version, data, started), "a good hello is refused");
    check(version == net::kProtocolVersion && data == 99 && started, "hello fields");
    net::Refusal refusal;
    check(net::decode_refusal(net::encode_refusal(net::Refusal::RoomFull), refusal) && refusal == net::Refusal::RoomFull, "refusal");
}

void test_malformed() {
    const auto plan = net::encode_plan(sample_plan(), 1);
    net::MatchPlan decoded;
    std::uint8_t peer;
    for (size_t size = 0; size < plan.size(); ++size) {
        const std::vector<std::uint8_t> cut(plan.begin(), plan.begin() + static_cast<long>(size));
        check(!net::decode_plan(cut, decoded, peer), "a cut plan of " + std::to_string(size) + " bytes");
    }
    auto longer = plan;
    longer.push_back(0);
    check(!net::decode_plan(longer, decoded, peer), "a plan with trailing bytes");

    const auto changed = [&](int slot, int peerValue, int count, int you) {
        net::MatchPlan bad = sample_plan();
        if (slot >= 0) bad.slots[static_cast<size_t>(slot)].peer = peerValue;
        bad.peerCount = static_cast<std::uint8_t>(count);
        return net::encode_plan(bad, static_cast<std::uint8_t>(you));
    };
    check(!net::decode_plan(changed(-1, 0, 2, 2), decoded, peer), "your peer past the count");
    check(!net::decode_plan(changed(-1, 0, 5, 0), decoded, peer), "too many peers");
    check(!net::decode_plan(changed(-1, 0, 1, 0), decoded, peer), "too few peers");
    check(!net::decode_plan(changed(2, 0, 2, 0), decoded, peer), "one peer in two slots");
    check(!net::decode_plan(changed(2, -1, 2, 0), decoded, peer), "a peer with no slot");
    check(!net::decode_plan(changed(2, 9, 2, 0), decoded, peer), "a slot for an unknown peer");

    const auto hello = net::encode_hello(1, false);
    std::uint16_t version;
    std::uint64_t data;
    bool started;
    for (size_t size = 0; size < hello.size(); ++size)
        check(!net::decode_hello({hello.begin(), hello.begin() + static_cast<long>(size)}, version, data, started), "a cut hello");
    check(!net::decode_hello(plan, version, data, started), "a plan read as a hello");
    net::Refusal refusal;
    check(!net::decode_refusal({net::kLobbyPacket, 3, 0}, refusal), "a refusal of nothing");
    check(!net::decode_refusal({net::kLobbyPacket, 3, 200}, refusal), "an unknown refusal");
}

// Runs lobbies against each other over localhost until they settle.
template <class Done>
void settle(std::vector<net::Lobby*> lobbies, Done done) {
    for (int i = 0; i < 400 && !done(); ++i)
        for (net::Lobby* lobby : lobbies) lobby->poll(50);
}

void test_over_sockets() {
    net::UdpSocket hostSocket, aSocket, bSocket, cSocket;
    std::string error;
    check(hostSocket.open(0, error) && aSocket.open(0, error) && bSocket.open(0, error) && cSocket.open(0, error), "open: " + error);
    net::Address hostAddress;
    net::parse_address("127.0.0.1:" + std::to_string(hostSocket.port()), hostAddress);

    net::MatchPlan plan = sample_plan();
    plan.peers = {};
    auto host = net::Lobby::host(hostSocket, plan, 42);
    auto a = net::Lobby::join(aSocket, hostAddress, 42);
    settle({&host, &a}, [&] { return host.ready() && a.ready(); });
    check(host.ready() && a.ready(), "host and joiner did not start");
    check(a.local_peer() == 1 && a.plan().seed == plan.seed && a.plan().token == plan.token, "the joiner got the plan");

    auto wrongData = net::Lobby::join(bSocket, hostAddress, 43);
    settle({&host, &wrongData}, [&] { return wrongData.refused() != net::Refusal::None; });
    check(wrongData.refused() == net::Refusal::WrongGameData, "different game data was not refused");

    auto late = net::Lobby::join(cSocket, hostAddress, 42);
    settle({&host, &late}, [&] { return late.refused() != net::Refusal::None; });
    check(late.refused() == net::Refusal::RoomFull, "a full room was not refused");

    // Another build's hello, which no Lobby here can send.
    auto foreign = net::encode_hello(42, false);
    foreign[2] = static_cast<std::uint8_t>(net::kProtocolVersion + 1);
    net::UdpSocket foreignSocket;
    check(foreignSocket.open(0, error), "open: " + error);
    foreignSocket.send(hostAddress, foreign.data(), foreign.size());
    net::Refusal refusal = net::Refusal::None;
    net::Address from;
    std::vector<std::uint8_t> packet;
    for (int i = 0; i < 400 && refusal == net::Refusal::None; ++i) {
        host.poll(50);
        while (foreignSocket.receive(from, packet)) net::decode_refusal(packet, refusal);
    }
    check(refusal == net::Refusal::WrongVersion, "a different version was not refused");
}

}  // namespace

int main() {
    test_round_trips();
    test_malformed();
    test_over_sockets();
    if (failures) {
        std::printf("net_lobby_test: %d failure(s)\n", failures);
        return 1;
    }
    std::printf("net_lobby_test: ok\n");
    return 0;
}
