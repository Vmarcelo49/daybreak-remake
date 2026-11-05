// Online lobby (docs/ONLINE-PLAN.md, step 4): its packets come from strangers, so every malformed one
// has to be refused, and a host and joiners have to agree over a real socket.
#include <chrono>
#include <cstdio>
#include <cstring>
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

// A stub of server/rooms.go on a loopback socket, over the real clock. It keeps the little the lobby
// reads: a host's client ID is given a code, the same one while its room's lifetime has not run out
// since it last asked and a new one after that, and a join is refused unless its room still lives.
// The codes count up through the server's own alphabet, so a change is plain to see.
//
// The lifetime is the test's (roomLifetime is a minute, and two cases of real minutes is a slow
// suite): the rule is the same comparison, over a span a test can wait out.
class StubRooms {
public:
    explicit StubRooms(unsigned lifetimeMs = 6000) : kLifetimeMs(lifetimeMs) {}
    const unsigned kLifetimeMs;
    static constexpr std::uint8_t kFailNoRoom[3] = {'R', 'x', 1};

    static unsigned now_ms() {
        static const auto epoch = std::chrono::steady_clock::now();
        return static_cast<unsigned>(
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - epoch).count());
    }

    bool open() { return m_socket.open(0, m_error); }
    net::Address address() const {
        net::Address out;
        net::parse_address("127.0.0.1:" + std::to_string(m_socket.port()), out);
        return out;
    }
    unsigned hostRequests() const { return m_hostRequests; }
    unsigned joinRequests() const { return m_joinRequests; }
    // rooms.find: a code answers only while its room lives.
    bool resolves(const std::string& code) const {
        for (const Room& room : m_rooms)
            if (room.code == code && now_ms() - room.lastSeen < kLifetimeMs) return true;
        return false;
    }

    // Answers everything waiting. It takes no time itself: the lobby's own silence is what ages a room.
    void pump() {
        net::Address from;
        std::vector<std::uint8_t> packet;
        while (m_socket.receive(from, packet)) {
            if (packet.size() != 48 || std::memcmp(packet.data(), "DBR1", 4) != 0) continue;
            if (packet[4] == 'H') {
                ++m_hostRequests;
                const std::vector<std::uint8_t> out = answer_hosted(host(requested(packet), now_ms()));
                m_socket.send(from, out.data(), out.size());
            } else if (packet[4] == 'J') {
                ++m_joinRequests;
                if (!resolves(std::string(packet.data() + 17, packet.data() + 21)))
                    m_socket.send(from, kFailNoRoom, sizeof kFailNoRoom);
            }
        }
    }

private:
    struct Room {
        std::string code;
        std::uint32_t clientId = 0;
        unsigned lastSeen = 0;
    };

    static std::uint32_t requested(const std::vector<std::uint8_t>& packet) {
        return static_cast<std::uint32_t>(packet[7]) | static_cast<std::uint32_t>(packet[8]) << 8 |
               static_cast<std::uint32_t>(packet[9]) << 16 | static_cast<std::uint32_t>(packet[10]) << 24;
    }
    // protocol.go's answerHosted: the prefix, kindHosted, the code, then six bytes of public endpoint.
    // Only the code is read here, so the endpoint stays zero.
    std::vector<std::uint8_t> answer_hosted(const Room& room) const {
        std::vector<std::uint8_t> out;
        out.resize(2 + net::kRoomCodeLength + 6, 0);
        out[0] = 'R';
        out[1] = 'h';
        for (size_t i = 0; i < room.code.size(); ++i) out[2 + i] = static_cast<std::uint8_t>(room.code[i]);
        return out;
    }
    // protocol.go's codeAlphabet: no 0, 1, I or O, which read alike when shared aloud.
    static std::string next_code(unsigned count) {
        static constexpr char kAlphabet[] = "ABCDEFGHJKLMNPQRSTUVWXYZ23456789";
        constexpr size_t kLength = sizeof kAlphabet - 1;
        std::string code(net::kRoomCodeLength, kAlphabet[0]);
        for (size_t i = 0; i < code.size(); ++i, count /= kLength) code[i] = kAlphabet[count % kLength];
        return code;
    }
    // rooms.host: the same room while its last sighting is inside the lifetime, a new one otherwise.
    const Room& host(std::uint32_t clientId, unsigned now) {
        for (Room& room : m_rooms)
            if (room.clientId == clientId && now - room.lastSeen < kLifetimeMs) {
                room.lastSeen = now;
                return room;
            }
        // Reserved first: the room returned below must not be invalidated by the next one.
        if (m_rooms.size() == m_rooms.capacity()) m_rooms.reserve(m_rooms.capacity() ? m_rooms.capacity() * 2 : 8);
        ++m_codes;
        m_rooms.push_back({next_code(m_codes), clientId, now});
        return m_rooms.back();
    }

    net::UdpSocket m_socket;
    std::string m_error;
    std::vector<Room> m_rooms;  // never erased: an expired room is simply not found
    unsigned m_codes = 0;
    unsigned m_hostRequests = 0;
    unsigned m_joinRequests = 0;
};

// The host asks the server, which answers, over the truly opened sockets. The server looks first, so
// every request is answered inside the round it was made in. With `was`, it waits for another code.
void serve_until_code(net::Lobby& host, StubRooms& server, unsigned limitMs, const std::string& was = {}) {
    for (unsigned waited = 0; (host.room_code().empty() || host.room_code() == was) && waited < limitMs; waited += 100) {
        server.pump();
        host.poll(100);
    }
}

// The host looks at its socket itself, as a lobby with no match does.
void drain_as_lobby(net::Lobby& host) {
    for (int i = 0; i < 4; ++i) host.poll(0);
}

// Issue #110: one room through one match, both ways round. With the keepalive the code the room
// started with is still the one the server gives after it, and the one a player can still join by.
// Without it, which is how the bug was found, the host comes back to a new code and the old one is
// dead: the host's own silence let the room expire at the server.
void test_room_survives_a_match() {
    const auto after_a_match = [](bool keepalive, std::string& before, std::string& after, StubRooms& server) {
        net::UdpSocket hostSocket, joinerSocket;
        std::string error;
        check(hostSocket.open(0, error) && joinerSocket.open(0, error), "open: " + error);
        auto host = net::Lobby::host(hostSocket, sample_plan(), 42, server.address());
        serve_until_code(host, server, 3000);
        before = host.room_code();
        check(!before.empty() && server.resolves(before), "the host never got a code: " + before);

        // The match: the session owns the socket, so the lobby neither polls nor sends anything it is
        // not told to, and the server hears nothing for longer than a room lives.
        const auto until = std::chrono::steady_clock::now() + std::chrono::milliseconds(server.kLifetimeMs + 1000);
        while (std::chrono::steady_clock::now() < until) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            if (keepalive) host.keep_alive(100);
            server.pump();
        }
        host.next_match(111, 222);
        serve_until_code(host, server, 3000, before);
        after = host.room_code();

        // Back in the room, a player joins by whatever code the host is showing now.
        auto joiner = net::Lobby::join_code(joinerSocket, server.address(), after, 42);
        for (unsigned waited = 0; waited < 3000 && joiner.refused() == net::Refusal::None &&
                                  joiner.join_stage() != net::JoinStage::Joined; waited += 100) {
            joiner.poll(100);
            server.pump();
        }
        check(joiner.refused() != net::Refusal::NoSuchRoom, "a join by the shown code found no room");
    };

    {
        StubRooms server;
        check(server.open(), "the stub server did not open");
        std::string before, after;
        after_a_match(true, before, after, server);
        check(after == before, "the code changed over a match: " + before + " -> " + after);
        check(server.resolves(before), "the server no longer resolves the original code: " + before);
    }
    {
        StubRooms server;
        check(server.open(), "the stub server did not open");
        std::string before, after;
        after_a_match(false, before, after, server);
        check(after != before, "a room nobody kept alive kept its code: " + before);
        check(!server.resolves(before), "the old code still resolves after expiry: " + before);
        check(server.resolves(after), "the new code does not resolve: " + after);
    }
}

// Issue #110's review: how often a lobby asks the server. A host keeps its room, so it asks at once
// and then once a second — not once per poll, which a host in a lobby did when "the first ask" was
// read off the timer ("m_sinceServer == elapsedMs" is true on every poll of a constant step).
void test_server_requests_are_paced() {
    StubRooms server;
    check(server.open(), "the stub server did not open");
    net::UdpSocket hostSocket, joinerSocket;
    std::string error;
    check(hostSocket.open(0, error) && joinerSocket.open(0, error), "open: " + error);

    // Two seconds of the frame loop's own 16 ms poll.
    auto host = net::Lobby::host(hostSocket, sample_plan(), 42, server.address());
    for (int tick = 0; tick < 125; ++tick) {
        host.poll(16);
        server.pump();
    }
    const unsigned asked = server.hostRequests();
    check(asked >= 2 && asked <= 3, "the host asked the server " + std::to_string(asked) + " times in 2 s");

    // A joiner is answered no later than its first poll: waiting out the timer would hold up the join.
    auto joiner = net::Lobby::join_code(joinerSocket, server.address(), "ABCD", 42);
    const unsigned before = server.joinRequests();
    joiner.poll(16);
    server.pump();
    check(server.joinRequests() == before + 1, "the joiner did not ask on its first poll");
}

// A joiner and a room without a server have nothing to keep alive.
void test_keepalive_is_a_no_op_elsewhere() {
    StubRooms server;
    check(server.open(), "the stub server did not open");
    net::UdpSocket joinerSocket, hostSocket;
    std::string error;
    check(joinerSocket.open(0, error) && hostSocket.open(0, error), "open: " + error);

    // The socket stays open and the server listening, so a send from either would arrive.
    auto joiner = net::Lobby::join_code(joinerSocket, server.address(), "ABCD", 42);
    for (int i = 0; i < 300; ++i) {
        joiner.keep_alive(16);
        server.pump();
    }
    // Nor is it answered: a keepalive that read its socket would take the join from its own poll.
    check(joiner.join_stage() == net::JoinStage::AskingServer, "a joiner was answered by its keepalive");

    auto local = net::Lobby::host(hostSocket, sample_plan(), 42, {});
    for (int i = 0; i < 300; ++i) {
        local.keep_alive(16);
        server.pump();
    }
    check(!local.uses_server() && local.room_code().empty(), "a host without a server kept something alive");
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
    test_room_survives_a_match();
    test_keepalive_is_a_no_op_elsewhere();
    test_server_requests_are_paced();
    if (failures) {
        std::printf("net_lobby_test: %d failure(s)\n", failures);
        return 1;
    }
    std::printf("net_lobby_test: ok\n");
    return 0;
}
