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
    plan.peerCount = 2;
    net::parse_address("10.1.2.3:4000", plan.peers[1]);
    plan.names = {"first", "second", "", ""};
    net::parse_address("198.51.100.7:4100", plan.publics[1]);
    net::parse_address("192.168.1.7:4000", plan.privates[1]);
    plan.clientIds = {11, 22, 0, 0};
    plan.links = {2, 1, 0, 0};
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
    check(peer == 1 && echo == 500 && decoded.token == plan.token && decoded.seed == 77 && decoded.started, "plan header");
    check(decoded.peers[1] == plan.peers[1] && decoded.names[1] == "second" && decoded.ready[1] && decoded.pingMs[1] == 80, "plan peers");
    check(decoded.publics[1] == plan.publics[1] && decoded.privates[1] == plan.privates[1] && decoded.clientIds[1] == 22 && decoded.links[1] == 1, "plan links");

    net::Hello hello;
    hello.gameData = 99;
    hello.started = true;
    hello.choice = {"me", true};
    hello.sequence = 9;
    hello.pingMs = 33;
    hello.clientId = 44;
    hello.links = 5;
    net::parse_address("198.51.100.7:4100", hello.publicAddress);
    net::parse_address("192.168.1.7:4000", hello.privateAddress);
    net::Hello read;
    check(net::decode_hello(net::encode_hello(hello), read), "a good hello is refused");
    check(read.version == net::kProtocolVersion && read.gameData == 99 && read.started && read.sequence == 9 && read.pingMs == 33, "hello fields");
    check(read.choice.name == "me" && read.choice.ready, "hello choice");
    check(read.clientId == 44 && read.links == 5 && read.publicAddress == hello.publicAddress && read.privateAddress == hello.privateAddress, "hello addresses");
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

    const auto changed = [&](int count, int you) {
        net::MatchPlan bad = sample_plan();
        bad.peerCount = static_cast<std::uint8_t>(count);
        return net::encode_plan(bad, static_cast<std::uint8_t>(you), 0);
    };
    check(!net::decode_plan(changed(2, 2), decoded, peer, echo), "your peer past the count");
    check(!net::decode_plan(changed(5, 0), decoded, peer, echo), "too many peers");
    check(!net::decode_plan(changed(1, 0), decoded, peer, echo), "too few peers");
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
    net::LocalChoice hostChoice{"host", true};
    host.set_choice(hostChoice);

    auto a = net::Lobby::join(aSocket, hostAddress, 42);
    net::LocalChoice aChoice{"a", false};
    a.set_choice(aChoice);
    settle({&host, &a}, [&] { return a.plan().peerCount == 2 && a.plan().names[1] == "a"; });
    check(a.local_peer() == 1 && a.plan().seed == plan.seed, "the joiner got the plan");
    check(!host.can_start(), "a player who is not ready held the start");

    // A third player arrives, then leaves, and a fourth takes the place.
    auto b = net::Lobby::join(bSocket, hostAddress, 42);
    b.set_choice({"b", true});
    settle({&host, &a, &b}, [&] { return host.plan().peerCount == 3; });
    b.leave();
    settle({&host, &a}, [&] { return host.plan().peerCount == 2 && a.plan().peerCount == 2; });

    aChoice.ready = true;
    a.set_choice(aChoice);
    settle({&host, &a}, [&] { return host.can_start(); });
    check(host.can_start(), "everyone is ready");
    {
        const net::MatchPlan seen = a.plan_for_match();
        check(seen.peers[0] == hostAddress, "the joiner plays to the address that answered");
    }
    check(host.link_problem().empty(), "no problem to report");

    // A player nobody can reach holds the start, and the lobby says who.
    {
        net::UdpSocket silentHostSocket, loneSocket;
        check(silentHostSocket.open(0, error) && loneSocket.open(0, error), "open: " + error);
        net::Address silentAddress;
        net::parse_address("127.0.0.1:" + std::to_string(silentHostSocket.port()), silentAddress);
        auto silentHost = net::Lobby::host(silentHostSocket, plan, 42);
        silentHost.set_choice({"host", true});
        // A hello forged with no link and a dead address: it never answers a probe.
        net::Hello forged;
        forged.gameData = 42;
        forged.clientId = 99;
        forged.choice = {"ghost", true};
        const auto packet = net::encode_hello(forged);
        loneSocket.send(silentAddress, packet.data(), packet.size());
        settle({&silentHost}, [&] { return silentHost.plan().peerCount == 2; });
        for (int i = 0; i < 110 && silentHost.link_problem().empty(); ++i) {
            silentHost.poll(100);
            // Stays in the room, still not reachable by probe: this socket never answers them.
            loneSocket.send(silentAddress, packet.data(), packet.size());
        }
        check(!silentHost.can_start(), "an unreachable player did not hold the start");
        check(silentHost.link_problem() == "host cannot reach ghost.", "the lobby named: " + silentHost.link_problem());
    }

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
    for (int i = 0; i < 110; ++i) nobody.poll(100);
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
