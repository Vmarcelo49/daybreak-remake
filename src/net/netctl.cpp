// A headless online peer: real sockets and the real battle, with no window, audio or device.
// Its busy hands are repeatable, so tests can compare what peers end up with.
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

#include "net/lobby.h"
#include "net/session.h"

namespace {

const char kUsage[] =
    "usage: netctl (--host PORT --peers N | --join IP:PORT | --join-code CODE) [options]\n"
    "  --server IP:PORT the rendezvous server: a host prints its room code, and --join-code needs it\n"
    "  --game DIR       install holding daybreak00.dat (default: $GAME_DIR or a parent directory)\n"
    "  --ticks N        frames to play (default 3600)\n"
    "  --seed N         host: battle seed (default 1)\n"
    "  --time-limit S   round limit in seconds, the same for every peer (default: the match's own)\n"
    "  --delay N        input delay in frames (default 2)\n"
    "  --proxy IP:PORT  send everything through tools/net_proxy.py\n"
    "  --log FILE       write `frame hash` per frame, for comparing peers\n"
    "  --game-hash N    claim this hash of the game data, to test a refusal\n"
    "Exit code: 0 played, 1 failed, 3 refused.\n";

std::string find_game(const std::string& explicitDir) {
    if (!explicitDir.empty()) return explicitDir;
    if (const char* configured = std::getenv("GAME_DIR")) return configured;
    namespace fs = std::filesystem;
    for (auto path = fs::current_path();; path = path.parent_path()) {
        for (const auto& candidate : {path, path / "Higurashi-Daybreak"})
            if (fs::exists(candidate / "daybreak00.dat")) return candidate.string();
        if (path == path.parent_path()) return {};
    }
}

sim::SlotInput busy_hands(unsigned tick, unsigned peer) {
    const unsigned bits = ((tick / (11u + peer * 3u)) * 2654435761u + peer * 40503u) >> 20;
    sim::SlotInput input;
    input.x = static_cast<int>(bits & 3u) - 1;
    input.z = static_cast<int>((bits >> 2) & 3u) - 1;
    if (bits & 16u) input.buttons |= sim::Shoot;
    if (bits & 32u) input.buttons |= sim::Melee;
    return input;
}

net::MatchPlan default_plan(std::uint32_t seed, unsigned timeLimit) {
    net::MatchPlan plan;
    plan.token = seed * 2654435761u + static_cast<std::uint32_t>(std::chrono::steady_clock::now().time_since_epoch().count());
    plan.seed = seed;
    plan.timeLimitSeconds = timeLimit;
    return plan;
}

sim::BattleConfig battle_config(const net::MatchPlan& plan, const std::string& game) {
    sim::BattleConfig config;
    config.gameDir = game;
    config.stage = plan.stage;
    config.seed = plan.seed;
    config.timeLimitSeconds = plan.timeLimitSeconds;
    config.rules = plan.rules;
    for (size_t i = 0; i < plan.slots.size(); ++i) {
        const net::PlanSlot& slot = plan.slots[i];
        config.slots[i] = {slot.character, slot.weapon, slot.peer < 0, slot.costume, slot.specialMode};
    }
    return config;
}

}  // namespace

int main(int argc, char** argv) try {
    int hostPort = -1;
    unsigned peers = 2, ticks = 3600, delay = 2, timeLimit = 0;
    std::uint32_t seed = 1;
    std::string join, joinCode, server, proxy, gameDir, logPath;
    long long forcedHash = -1;
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        const auto value = [&]() -> const char* {
            if (i + 1 >= argc) throw std::runtime_error("missing value for " + arg);
            return argv[++i];
        };
        if (arg == "--host") hostPort = std::atoi(value());
        else if (arg == "--peers") peers = static_cast<unsigned>(std::atoi(value()));
        else if (arg == "--join") join = value();
        else if (arg == "--join-code") joinCode = value();
        else if (arg == "--server") server = value();
        else if (arg == "--game") gameDir = value();
        else if (arg == "--ticks") ticks = static_cast<unsigned>(std::atoi(value()));
        else if (arg == "--seed") seed = static_cast<std::uint32_t>(std::atoll(value()));
        else if (arg == "--time-limit") timeLimit = static_cast<unsigned>(std::atoi(value()));
        else if (arg == "--delay") delay = static_cast<unsigned>(std::atoi(value()));
        else if (arg == "--proxy") proxy = value();
        else if (arg == "--log") logPath = value();
        else if (arg == "--game-hash") forcedHash = std::atoll(value());
        else {
            std::cout << kUsage;
            return arg == "--help" ? 0 : 1;
        }
    }
    if ((hostPort >= 0) + !join.empty() + !joinCode.empty() != 1 || peers < 2 || peers > 4) {
        std::cout << kUsage;
        return 1;
    }
    const std::string game = find_game(gameDir);
    if (game.empty()) throw std::runtime_error("no game install found; pass --game");

    std::string error;
    net::UdpSocket socket;
    if (!socket.open(hostPort < 0 ? 0 : static_cast<std::uint16_t>(hostPort), error)) throw std::runtime_error(error);
    if (!proxy.empty()) {
        net::Address address;
        if (!net::parse_address(proxy, address)) throw std::runtime_error("bad --proxy");
        socket.use_proxy(address);
    }
    const std::uint64_t gameHash = forcedHash >= 0 ? static_cast<std::uint64_t>(forcedHash) : net::game_data_hash(game);

    net::Address hostAddress;
    if (!join.empty() && !net::parse_address(join, hostAddress)) throw std::runtime_error("bad --join");
    net::Address serverAddress;
    if (!server.empty() && !net::parse_address(server, serverAddress)) throw std::runtime_error("bad --server");
    if (!joinCode.empty() && server.empty()) throw std::runtime_error("--join-code needs --server");
    net::Lobby lobby = hostPort >= 0 ? net::Lobby::host(socket, default_plan(seed, timeLimit), gameHash, serverAddress)
                       : !joinCode.empty() ? net::Lobby::join_code(socket, serverAddress, joinCode, gameHash)
                                           : net::Lobby::join(socket, hostAddress, gameHash);
    bool printedCode = false;
    net::LocalChoice choice;
    choice.name = "netctl";
    choice.ready = true;
    lobby.set_choice(choice);
    for (unsigned waited = 0; !lobby.ready(); waited += 5) {
        lobby.poll(5);
        if (!printedCode && !lobby.room_code().empty()) {
            printedCode = true;
            std::printf("{\"code\":\"%s\"}\n", lobby.room_code().c_str());
            std::fflush(stdout);
        }
        if (lobby.is_host() && lobby.plan().peerCount == peers) lobby.start();
        if (lobby.refused() != net::Refusal::None) {
            std::printf("{\"refused\":\"%s\"}\n", net::refusal_text(lobby.refused()));
            return 3;
        }
        if (waited > 60000) throw std::runtime_error("nobody answered in the lobby");
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    // What the selection screen would have decided, the same on every peer: the first weapon exists
    // for everyone, and the peers fill the teams in turn.
    net::MatchPlan plan = lobby.plan_for_match();
    plan.timeLimitSeconds = timeLimit;
    constexpr std::array<int, 4> kPeerSlot{{0, 2, 1, 3}};
    for (unsigned i = 0; i < 4; ++i) plan.slots[i].character = static_cast<int>(i);
    for (unsigned peer = 0; peer < plan.peerCount; ++peer) plan.slots[static_cast<size_t>(kPeerSlot[peer])].peer = static_cast<int>(peer);
    sim::CoreBattle battle;
    const std::array<const gameplay::CharacterMoves*, 4> moves{};
    const std::array<const gameplay::WeaponDefinition*, 4> weapons{};
    battle.start(battle_config(plan, game), moves, weapons);
    const auto session = net::Session::online(battle, socket, lobby, plan, lobby.local_peer(), delay);
    net::Session::HashLog log;
    if (!logPath.empty()) session->log_hashes(&log);

    using Clock = std::chrono::steady_clock;
    const auto tickLength = std::chrono::nanoseconds(1000000000 / 60);
    auto next = Clock::now();
    const auto deadline = next + std::chrono::seconds(ticks / 60 + 120);
    int roundOverFrame = -1;
    while (session->frame() < static_cast<int>(ticks) && Clock::now() < deadline) {
        sim::Inputs inputs{};
        for (size_t slot = 0; slot < plan.slots.size(); ++slot)
            if (plan.slots[slot].peer == lobby.local_peer())
                inputs[slot] = busy_hands(static_cast<unsigned>(session->frame()), lobby.local_peer());
        session->run(inputs);
        if (roundOverFrame < 0 && session->round_over_confirmed()) roundOverFrame = session->round_over_frame();
        next += tickLength;
        std::this_thread::sleep_until(next);
    }

    if (!logPath.empty()) {
        std::ofstream out(logPath);
        // The last frames may still be predictions.
        for (const auto& [frame, hash] : log)
            if (frame + 16 < session->frame()) out << frame << ' ' << hash << '\n';
    }
    const auto& stats = session->stats();
    std::string owners;
    for (unsigned i = 0; i < 4; ++i) owners += battle.slot_is_cpu(i) ? "C" : "H";
    std::printf("{\"peer\":%d,\"frames\":%d,\"rollbacks\":%u,\"replayed\":%u,\"desyncs\":%u,\"first_desync\":%d,"
                "\"disconnects\":%u,\"skipped\":%u,\"round_over\":%d,\"slots\":\"%s\",\"worst_ms\":%.2f}\n",
                lobby.local_peer(), session->frame(), stats.rollbacks, stats.replayedTicks, stats.desyncs, stats.firstDesyncFrame,
                stats.disconnects, stats.skippedTicks, roundOverFrame, owners.c_str(), stats.worstUpdate.count() / 1000.0);
    return session->frame() >= static_cast<int>(ticks) && stats.desyncs == 0 ? 0 : 1;
} catch (const std::exception& error) {
    std::fprintf(stderr, "netctl: %s\n", error.what());
    return 1;
}
