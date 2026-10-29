#include "gameplay/fixed_step.h"
#include "gameplay/live_debug.h"
#include "synthetic_combo.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <sstream>
#if defined(__linux__)
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#endif

int main() {
#if defined(__linux__)
    gameplay::Match match;
    gameplay::MatchConfig config;
    test::synthetic::Combo combo;
    if (!combo.ok) return 3;
    config.weapon[0] = config.weapon[1] = combo.weapon.get();
    config.moves[0] = config.moves[1] = &combo.moves;
    const xm::Model* models[4]{}; xm::Controller* anims[4]{};
    match.reset(config, models, anims, nullptr, nullptr);
    gameplay::LiveDebug debug;
    std::string error;
    if (!debug.start(error)) return 1;
    std::ifstream manifest(debug.directory() + "/session");
    std::string pid, token; std::getline(manifest, pid); std::getline(manifest, token);
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    sockaddr_un address{}; address.sun_family = AF_UNIX;
    const auto path = debug.directory() + "/control.sock";
    std::copy(path.begin(), path.end(), address.sun_path);
    if (connect(fd, reinterpret_cast<sockaddr*>(&address), sizeof(address))) return 2;
    uint64_t tick = 0, renders = 0;
    auto command = [&](std::string text, bool complete = true) {
        text += '\n'; send(fd, text.data(), text.size(), 0);
        debug.poll(tick, renders, match);
        if (!complete) return std::string{};
        char buffer[16384]; const auto n = recv(fd, buffer, sizeof(buffer), 0);
        return n > 0 ? std::string(buffer, static_cast<size_t>(n)) : std::string{};
    };
    auto require = [](bool ok) { if (!ok) std::abort(); };
    require(command("HELLO " + token).find("true") != std::string::npos);
    require(debug.paused());
    for (int i = 0; i < 100; ++i) { ++renders; require(!debug.wants_tick()); debug.presented(tick, renders, match); }
    require(tick == 0);
    require(command("INPUT 0 1 Jump").find("first_tick\":1") != std::string::npos);
    require(command("INPUT 0 1 -").find("first_tick\":2") != std::string::npos);
    require(command("INPUT 0 1 Attack").find("first_tick\":3") != std::string::npos);
    command("STEP 3", false);
    for (int i = 0; i < 3; ++i) {
        require(debug.wants_tick());
        const fnd::input::PlayerState* inputs[4]; debug.inputs(++tick, inputs);
        require(i != 0 || inputs[0]->just_pressed[fnd::input::Jump]);
        require(i != 1 || inputs[0]->just_released[fnd::input::Jump]);
        require(i != 2 || inputs[0]->just_pressed[fnd::input::AttackA]);
        debug.after_tick(tick, match, match.step(inputs, gameplay::FixedStep::seconds));
        ++renders; debug.presented(tick, renders, match);
    }
    require(!debug.wants_tick());
    char buffer[16384]; auto n = recv(fd, buffer, sizeof(buffer), 0);
    require(n > 0 && std::string(buffer, static_cast<size_t>(n)).find("\"tick\":3") != std::string::npos);
    const auto status = command("STATUS");
    require(status.find("\"contact\":false") != std::string::npos);
    require(status.find("\"volume\":") != std::string::npos);
    require(status.find("\"tag\":") != std::string::npos);
    require(command("BREAK state 0 -1 -1 -1").find("true") != std::string::npos);
    require(command("EVAL arbitrary").find("error") != std::string::npos);
    close(fd); debug.poll(tick, renders, match);
    require(debug.paused() && !debug.wants_tick());
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    require(connect(fd, reinterpret_cast<sockaddr*>(&address), sizeof(address)) == 0);
    command("HELLO stale-session", false);
    require(debug.paused()); close(fd);
#endif
    return 0;
}
