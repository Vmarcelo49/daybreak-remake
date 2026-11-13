#include "net/battle_outcome.h"
#include "net/lobby.h"

#include <cstdio>
#include <cstdlib>

namespace {
void check(bool condition, const char* why) {
    if (!condition) { std::fprintf(stderr, "FAIL: %s\n", why); std::exit(1); }
}
void pump(net::UdpSocket& socket, net::BattleOutcome& outcome, bool drop = false) {
    net::Address from;
    std::vector<std::uint8_t> packet;
    while (socket.receive(from, packet)) if (!drop) outcome.handle(from, packet);
}
}

int main() {
    net::UdpSocket a, b;
    std::string error;
    check(a.open(0, error) && b.open(0, error), "open sockets");
    net::MatchPlan plan;
    plan.token = 12345;
    plan.peerCount = 2;
    check(net::parse_address("127.0.0.1:" + std::to_string(a.port()), plan.peers[0]), "address a");
    check(net::parse_address("127.0.0.1:" + std::to_string(b.port()), plan.peers[1]), "address b");
    {
        net::BattleOutcome one(a, plan, 0), two(b, plan, 1);
        std::vector<std::uint8_t> forged(20, 0);
        forged[0] = net::kOutcomePacket;
        forged[1] = static_cast<std::uint8_t>(plan.token);
        forged[2] = static_cast<std::uint8_t>(plan.token >> 8);
        forged[5] = 1;
        forged[6] = 3;
        one.handle(plan.peers[0], forged);
        check(one.state() == net::BattleOutcome::State::Playing, "reject abort from an unknown address");
        forged[1] ^= 1;
        one.handle(plan.peers[1], forged);
        check(one.state() == net::BattleOutcome::State::Playing, "reject another match token");
        one.propose(100, 42);
        pump(b, two, true);
        for (int i = 0; i < 5; ++i) { one.tick(100); pump(b, two, true); }
        check(one.state() == net::BattleOutcome::State::Pending, "no result before peer agrees");
        two.propose(100, 42);
        for (int i = 0; i < 10; ++i) {
            one.tick(100); two.tick(100); pump(a, one); pump(b, two);
        }
        check(one.state() == net::BattleOutcome::State::Valid && two.state() == net::BattleOutcome::State::Valid,
              "loss and asymmetric progress recover");
    }
    {
        net::BattleOutcome one(a, plan, 0), two(b, plan, 1);
        pump(a, one, true); pump(b, two, true);
        one.propose(100, 42); two.propose(100, 43);
        for (int i = 0; i < 5; ++i) { one.tick(100); two.tick(100); pump(a, one); pump(b, two); }
        check(one.state() == net::BattleOutcome::State::Desync && two.state() == net::BattleOutcome::State::Desync,
              "different final transcripts invalidate both peers");
    }
    {
        net::BattleOutcome one(a, plan, 0), two(b, plan, 1);
        pump(a, one, true); pump(b, two, true);
        one.abort(); pump(b, two);
        check(two.state() == net::BattleOutcome::State::Desync, "asymmetric abort propagates");
        pump(a, one, true);
        check(!one.abort_acknowledged(), "lost abort acknowledgement remains pending");
        one.tick(100); pump(b, two); pump(a, one);
        check(one.abort_acknowledged(), "abort retransmission receives acknowledgement");
    }
    {
        net::BattleOutcome one(a, plan, 0), two(b, plan, 1);
        pump(a, one, true); pump(b, two, true);
        one.propose(100, 42); two.propose(100, 42);
        // Deliver the offers, then lose one peer's seals until its partner times out.
        pump(a, one); pump(b, two);
        for (int i = 0; i < 98; ++i) {
            one.tick(100); two.tick(100); pump(a, one, true); pump(b, two);
        }
        check(two.state() == net::BattleOutcome::State::Valid, "peer reached result before the asymmetric timeout");
        one.tick(200); pump(b, two);
        check(one.state() == net::BattleOutcome::State::Timeout, "missing seal fails closed");
        one.tick(100); pump(b, two);
        check(two.state() == net::BattleOutcome::State::Desync, "late timeout invalidates an already sealed peer");
    }
    {
        net::BattleOutcome one(a, plan, 0), two(b, plan, 1);
        pump(a, one, true); pump(b, two, true);
        one.propose(101, 42); two.propose(100, 42);
        pump(a, one); pump(b, two);
        check(one.state() == net::BattleOutcome::State::Desync && two.state() == net::BattleOutcome::State::Desync,
              "different round-end frames cannot certify a result");
    }
    {
        net::BattleOutcome one(a, plan, 0);
        one.propose(100, 42); one.tick(10000);
        check(one.state() == net::BattleOutcome::State::Timeout, "missing peer fails closed");
    }
    std::puts("battle_outcome_test: ok");
}
