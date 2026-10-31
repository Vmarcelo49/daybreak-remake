#pragma once
// Online play's menu and lobby (docs/ONLINE-PLAN.md, step 6). Screens of our own, not ports of the
// original's FUN_00412110 and FUN_00414750, whose protocol this does not speak.
#include <memory>
#include <string>

#include "frontend/frontend_state.h"
#include "frontend/screen.h"
#include "net/lobby.h"

namespace ui {

struct OnlineContext {
    net::UdpSocket socket;
    std::unique_ptr<net::Lobby> lobby;
    net::MatchPlan matchPlan;  // the match being played, fixed when it starts
    bool inMatch = false;
};

// Opens a room or joins one, leaving state.online set. False with `error` when the port cannot be
// bound or the address cannot be read.
bool beginOnlineHost(FrontendState& state, int port, std::string& error);
bool beginOnlineJoin(FrontendState& state, const std::string& address, std::string& error);
// A fresh random pair for the match's token and seed.
void onlineMatchNumbers(std::uint32_t& token, std::uint32_t& seed);

std::unique_ptr<Screen> makeOnlineMenuScreen(SpriteRenderer& batch, FrontendState& state, std::string& error);
std::unique_ptr<Screen> makeOnlineLobbyScreen(SpriteRenderer& batch, FrontendState& state, std::string& error);

}  // namespace ui
