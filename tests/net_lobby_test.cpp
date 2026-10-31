// Online lobby (docs/ONLINE-PLAN.md, step 4): its packets come from strangers, so every malformed one
// has to be refused, and a host and joiners have to agree over a real socket.
#include <chrono>
#include <cstdio>
#include <string>
#include <thread>

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
    plan.stage = 2;
    plan.variation = 1;
    plan.timeLimitSeconds = 300;
    plan.rules = {100, 150, 80, 120};
    plan.peerCount = 2;
    plan.slots[0] = {3, 1, 2, 0, 0};
    plan.slots[1] = {4, 2, 0, 2, -1};
    plan.slots[2] = {5, 0, 0, 1, 1};
    plan.slots[3] = {6, 0, 0, 1, -1};
    net::parse_address("10.1.2.3:4000", plan.peers[1]);
    plan.names = {"first", "second", "", ""};
    plan.ready = {true, true, false, false};
    plan.pingMs = {0, 80, 0, 0};
    plan.started = true;
    return plan;
}

void test_round_trips() {
    const net::MatchPlan plan = sample_plan();
    net::MatchPlan decoded;
    std::uint8_t peer = 0;
    std::uint16_t echo = 0;
    check(net::decode_plan(net::encode_plan(plan, 1, 500), decoded, peer, echo), "a good plan is refused");
    check(peer == 1 && echo == 500 && decoded.token == plan.token && decoded.seed == 77 && decoded.stage == 2 && decoded.variation == 1, "plan header");
    check(decoded.timeLimitSeconds == 300 && decoded.rules == plan.rules && decoded.started, "plan rules");
    check(decoded.slots[2].character == 5 && decoded.slots[2].peer == 1 && decoded.slots[1].peer == -1, "plan slots");
    check(decoded.peers[1] == plan.peers[1] && decoded.names[1] == "second" && decoded.ready[1] && decoded.pingMs[1] == 80, "plan peers");

    net::Hello hello;
    hello.gameData = 99;
    hello.started = true;
    hello.choice = {"me", 7, 2, 1, 2, true};
    hello.sequence = 9;
    hello.pingMs = 33;
    net::Hello read;
    check(net::decode_hello(net::encode_hello(hello), read), "a good hello is refused");
    check(read.version == net::kProtocolVersion && read.gameData == 99 && read.started && read.sequence == 9 && read.pingMs == 33, "hello fields");
    check(read.choice.name == "me" && read.choice.character == 7 && read.choice.weapon == 2 && read.choice.costume == 1 && read.choice.specialMode == 2 && read.choice.ready, "hello choice");
    net::Refusal refusal;
    check(net::decode_refusal(net::encode_refusal(net::Refusal::HostLeft), refusal) && refusal == net::Refusal::HostLeft, "refusal");
    check(net::decode_bye(net::encode_bye()), "bye");
}

void test_malformed() {
    const auto plan = net::encode_plan(sample_plan(), 1, 0);
    net::MatchPlan decoded;
    std::uint8_t peer;
    std::uint16_t echo;
    for (size_t size = 0; size < plan.size(); ++size) {
        const std::vector<std::uint8_t> cut(plan.begin(), plan.begin() + static_cast<long>(size));
        check(!net::decode_plan(cut, decoded, peer, echo), "a cut plan of " + std::to_string(size) + " bytes");
    }
    auto longer = plan;
    longer.push_back(0);
    check(!net::decode_plan(longer, decoded, peer, echo), "a plan with trailing bytes");

    const auto changed = [&](int slot, int peerValue, int count, int you) {
        net::MatchPlan bad = sample_plan();
        if (slot >= 0) bad.slots[static_cast<size_t>(slot)].peer = peerValue;
        bad.peerCount = static_cast<std::uint8_t>(count);
        return net::encode_plan(bad, static_cast<std::uint8_t>(you), 0);
    };
    check(!net::decode_plan(changed(-1, 0, 2, 2), decoded, peer, echo), "your peer past the count");
    check(!net::decode_plan(changed(-1, 0, 5, 0), decoded, peer, echo), "too many peers");
    check(!net::decode_plan(changed(-1, 0, 1, 0), decoded, peer, echo), "too few peers");
    check(!net::decode_plan(changed(2, 0, 2, 0), decoded, peer, echo), "one peer in two slots");
    check(!net::decode_plan(changed(2, -1, 2, 0), decoded, peer, echo), "a peer with no slot");
    check(!net::decode_plan(changed(2, 9, 2, 0), decoded, peer, echo), "a slot for an unknown peer");
    net::MatchPlan badFighter = sample_plan();
    badFighter.slots[0].character = 16;
    check(!net::decode_plan(net::encode_plan(badFighter, 1, 0), decoded, peer, echo), "a character past the roster");
    net::MatchPlan badName = sample_plan();
    badName.names[1] = "bad\nname";
    check(!net::decode_plan(net::encode_plan(badName, 1, 0), decoded, peer, echo), "a control character in a name");

    net::Hello good;
    good.choice.name = "me";
    const auto hello = net::encode_hello(good);
    net::Hello read;
    for (size_t size = 0; size < hello.size(); ++size)
        check(!net::decode_hello({hello.begin(), hello.begin() + static_cast<long>(size)}, read), "a cut hello");
    check(!net::decode_hello(plan, read), "a plan read as a hello");
    net::Hello badChoice = good;
    badChoice.choice.weapon = 3;
    check(!net::decode_hello(net::encode_hello(badChoice), read), "a weapon past the menu");
    net::Refusal refusal;
    check(!net::decode_refusal({net::kLobbyPacket, 3, 0}, refusal), "a refusal of nothing");
    check(!net::decode_refusal({net::kLobbyPacket, 3, 200}, refusal), "an unknown refusal");
}

// Runs lobbies against each other over localhost until they settle.
template <class Done>
void settle(std::vector<net::Lobby*> lobbies, Done done) {
    for (int i = 0; i < 400 && !done(); ++i) {
        for (net::Lobby* lobby : lobbies) lobby->poll(10);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void test_over_sockets() {
    net::UdpSocket hostSocket, aSocket, bSocket, cSocket, dSocket, eSocket;
    std::string error;
    for (net::UdpSocket* socket : {&hostSocket, &aSocket, &bSocket, &cSocket, &dSocket, &eSocket})
        check(socket->open(0, error), "open: " + error);
    net::Address hostAddress;
    net::parse_address("127.0.0.1:" + std::to_string(hostSocket.port()), hostAddress);

    net::MatchPlan plan = sample_plan();
    auto host = net::Lobby::host(hostSocket, plan, 42);
    net::LocalChoice hostChoice{"host", 1, 0, 0, 1, true};
    host.set_choice(hostChoice);

    auto a = net::Lobby::join(aSocket, hostAddress, 42);
    net::LocalChoice aChoice{"a", 2, 1, 0, 2, false};
    a.set_choice(aChoice);
    settle({&host, &a}, [&] { return a.plan().peerCount == 2 && a.plan().names[1] == "a"; });
    check(a.local_peer() == 1 && a.plan().seed == plan.seed, "the joiner got the plan");
    check(host.plan().slots[2].character == 2 && host.plan().slots[2].peer == 1, "peers fill the teams in turn");
    check(!host.can_start(), "a player who is not ready held the start");

    // A third player arrives, then leaves, and a fourth takes the place.
    auto b = net::Lobby::join(bSocket, hostAddress, 42);
    b.set_choice({"b", 3, 0, 0, 1, true});
    settle({&host, &a, &b}, [&] { return host.plan().peerCount == 3; });
    check(host.plan().slots[1].peer == 2, "the third player's slot");
    b.leave();
    settle({&host, &a}, [&] { return host.plan().peerCount == 2 && a.plan().peerCount == 2; });
    check(host.plan().slots[1].peer == -1, "the slot of who left is a COM again");

    aChoice.ready = true;
    a.set_choice(aChoice);
    settle({&host, &a}, [&] { return host.can_start(); });
    check(host.can_start(), "everyone is ready");

    auto wrongData = net::Lobby::join(cSocket, hostAddress, 43);
    settle({&host, &a, &wrongData}, [&] { return wrongData.refused() != net::Refusal::None; });
    check(wrongData.refused() == net::Refusal::WrongGameData, "different game data was not refused");

    auto foreign = net::encode_hello(net::Hello{});
    foreign[2] = static_cast<std::uint8_t>(net::kProtocolVersion + 1);
    net::UdpSocket foreignSocket;
    check(foreignSocket.open(0, error), "open: " + error);
    foreignSocket.send(hostAddress, foreign.data(), foreign.size());
    net::Refusal refusal = net::Refusal::None;
    net::Address from;
    std::vector<std::uint8_t> packet;
    for (int i = 0; i < 400 && refusal == net::Refusal::None; ++i) {
        host.poll(10);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        while (foreignSocket.receive(from, packet)) net::decode_refusal(packet, refusal);
    }
    check(refusal == net::Refusal::WrongVersion, "a different version was not refused");

    host.start();
    settle({&host, &a}, [&] { return host.ready() && a.ready(); });
    check(host.ready() && a.ready(), "host and joiner did not start");
    check(a.plan().token == plan.token, "the joiner's match");

    auto late = net::Lobby::join(dSocket, hostAddress, 42);
    settle({&host, &a, &late}, [&] { return late.refused() != net::Refusal::None; });
    check(late.refused() == net::Refusal::RoomFull, "a match in progress took a player");

    // The room survives a match, and a stale start cannot begin the next one.
    host.next_match(111, 222);
    a.next_match(0, 0);
    settle({&host, &a}, [&] { return a.plan().token == 111 && !a.plan().ready[1]; });
    check(!a.ready() && !host.ready() && !a.plan().started, "the next match started by itself");
    check(a.plan().seed == 222 && !a.plan().ready[1], "the next match's plan");

    // A host that leaves is noticed at once.
    host.leave();
    settle({&a}, [&] { return a.refused() != net::Refusal::None; });
    check(a.refused() == net::Refusal::HostLeft, "the host left unnoticed");

    // And a host that is silent is noticed in time.
    auto nobody = net::Lobby::join(eSocket, net::Address{hostAddress.ip, 9}, 42);
    for (int i = 0; i < 60; ++i) nobody.poll(100);
    check(nobody.host_lost(), "silence went unnoticed");
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
