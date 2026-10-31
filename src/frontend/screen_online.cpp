#include "frontend/screen_online.h"

#include <algorithm>
#include <cstdio>
#include <random>

#include "assets/asset_source.h"
#include "frontend/frontend_settings.h"
#include "frontend/menu_panel.h"

namespace ui {

namespace {

const std::uint64_t kNoGameData = 0;

std::uint64_t installHash() {
    const std::string& install = fnd::assets::assetSource().installDir();
    return install.empty() ? kNoGameData : net::game_data_hash(install);
}

constexpr char kNameLetters[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_";
constexpr char kDigits[] = "0123456789";
constexpr char kCodeLetters[] = "ABCDEFGHJKLMNPQRSTUVWXYZ23456789";  // server/protocol.go's alphabet

// The rendezvous server the settings name, or a zero port.
net::Address settingsServer() {
    net::Address server;
    if (!net::parse_address(frontendSettings().netServer, server) || server.ip == 0) return {};
    return server;
}

// Text edited with the menu's own buttons, so a pad can do it too: left and right pick a place, and
// up and down turn its character on a wheel.
struct WheelEdit {
    std::string* text = nullptr;
    const char* wheel = nullptr;
    size_t cursor = 0;

    bool active() const { return text != nullptr; }
    void begin(std::string& value, const char* letters, size_t minimumLength) {
        text = &value;
        wheel = letters;
        cursor = 0;
        if (value.size() < minimumLength) value.resize(minimumLength, letters[0]);
    }
    bool editable(size_t place) const { return std::string(wheel).find((*text)[place]) != std::string::npos; }
    void update(const ScreenInput& in) {
        const int step = in.left ? -1 : in.right ? 1 : 0;
        if (step) {
            const int size = (int)text->size();
            int place = (int)cursor;
            do place = (place + step + size) % size; while (!editable((size_t)place));
            cursor = (size_t)place;
        }
        if (in.up || in.down) {
            const std::string letters(wheel);
            const int at = (int)letters.find((*text)[cursor]);
            const int count = (int)letters.size();
            (*text)[cursor] = letters[(size_t)((at + (in.up ? 1 : -1) + count) % count)];
        }
    }
};

std::string trimmedRight(std::string text) {
    while (!text.empty() && text.back() == ' ') text.pop_back();
    return text;
}

}  // namespace

void onlineMatchNumbers(std::uint32_t& token, std::uint32_t& seed) {
    std::random_device random;
    token = random();
    seed = random();
}

bool beginOnlineHost(FrontendState& state, int port, std::string& error) {
    auto context = std::make_shared<OnlineContext>();
    if (!context->socket.open(static_cast<std::uint16_t>(port), error)) return false;
    net::MatchPlan plan;
    onlineMatchNumbers(plan.token, plan.seed);
    context->lobby = std::make_unique<net::Lobby>(net::Lobby::host(context->socket, plan, installHash(), settingsServer()));
    state.online = std::move(context);
    return true;
}

bool beginOnlineJoin(FrontendState& state, const std::string& address, std::string& error) {
    net::Address host;
    if (!net::parse_address(address, host)) {
        error = "That address cannot be read.";
        return false;
    }
    auto context = std::make_shared<OnlineContext>();
    if (!context->socket.open(0, error)) return false;
    context->lobby = std::make_unique<net::Lobby>(net::Lobby::join(context->socket, host, installHash()));
    state.online = std::move(context);
    return true;
}

bool beginOnlineCode(FrontendState& state, const std::string& code, std::string& error) {
    const net::Address server = settingsServer();
    if (server.port == 0) {
        error = "A room code needs a server. Set one below.";
        return false;
    }
    auto context = std::make_shared<OnlineContext>();
    if (!context->socket.open(0, error)) return false;
    context->lobby = std::make_unique<net::Lobby>(net::Lobby::join_code(context->socket, server, code, installHash()));
    state.online = std::move(context);
    return true;
}

namespace {

class OnlineMenuScreen : public PanelScreen {
public:
    OnlineMenuScreen(SpriteRenderer& batch, FrontendState& state, std::string& error) : state_(state) {
        if (uploadBackground(batch, "data/config/0001", {{240, 8, 320, 56}, {340, 250, 420, 150}}, background_, error)) loadFace(batch, error);
        auto& settings = frontendSettings();
        name_ = settings.playerName;
        address_ = settings.netLastHost.empty() ? "192.168.000.001:37564" : settings.netLastHost;
        server_ = settings.netServer.empty() ? "000.000.000.000:37565" : settings.netServer;
        char port[8];
        std::snprintf(port, sizeof port, "%05d", settings.netPort);
        port_ = port;
        state_.online.reset();
    }
    bool loaded() const { return face_.atlasTexture() >= 0; }
    const char* name() const override { return "netplay"; }
    int takeSound() override { const int cue = sound_; sound_ = -1; return cue; }

    ScreenId update(const ScreenInput& in) override {
        if (in.cancel) sound_ = 1;
        else if (in.confirm) sound_ = 0;
        else if (in.up || in.down || in.left || in.right) sound_ = 2;

        auto& settings = frontendSettings();
        if (edit_.active()) {
            if (in.confirm || in.cancel) {
                edit_ = {};
                settings.playerName = trimmedRight(name_).substr(0, net::kMaxNameLength);
                settings.netLastHost = address_;
                settings.netServer = server_;
                settings.netPort = std::clamp(std::atoi(port_.c_str()), 1, 65535);
            } else {
                edit_.update(in);
            }
            return ScreenId::NetplayMenu;
        }
        if (in.cancel) return ScreenId::Title;
        if (in.up) row_ = (row_ + kRows - 1) % kRows;
        else if (in.down) row_ = (row_ + 1) % kRows;
        if ((Row)row_ == Row::Delay && (in.left || in.right))
            settings.netInputDelay = std::clamp(settings.netInputDelay + (in.right ? 1 : -1), 0, 8);
        if (!in.confirm) return ScreenId::NetplayMenu;

        std::string failure;
        switch ((Row)row_) {
        case Row::Host:
            if (beginOnlineHost(state_, settings.netPort, failure)) return ScreenId::NetplayLobby;
            state_.onlineMessage = failure;
            break;
        case Row::Join:
            settings.netLastHost = address_;
            if (beginOnlineJoin(state_, address_, failure)) return ScreenId::NetplayLobby;
            state_.onlineMessage = failure;
            break;
        case Row::Code:
            if (beginOnlineCode(state_, code_, failure)) return ScreenId::NetplayLobby;
            state_.onlineMessage = failure;
            break;
        case Row::CodeText: edit_.begin(code_, kCodeLetters, net::kRoomCodeLength); break;
        case Row::Server: edit_.begin(server_, kDigits, 21); break;
        case Row::Address: edit_.begin(address_, kDigits, 21); break;
        case Row::Name: edit_.begin(name_, kNameLetters, net::kMaxNameLength); break;
        case Row::Port: edit_.begin(port_, kDigits, 5); break;
        case Row::Delay: break;
        case Row::Back: return ScreenId::Title;
        }
        return ScreenId::NetplayMenu;
    }

    void draw(SpriteRenderer& batch) const override {
        batch.pushSprite(background_, {0, 0, 800, 600}, 0, 0, 0, 0);
        frame(batch, {"通信対戦", "ONLINE"}, 40, 540);
        const auto& settings = frontendSettings();
        char delay[32];
        std::snprintf(delay, sizeof delay, "%d", settings.netInputDelay);
        const Words names[kRows] = {{"部屋を作る", "HOST A ROOM"}, {"コードで入る", "JOIN BY CODE"}, {"部屋のコード", "ROOM CODE"},
                                    {"住所で入る", "JOIN BY ADDRESS"}, {"相手の住所", "ADDRESS"}, {"名前", "NAME"}, {"ポート", "PORT"},
                                    {"入力遅延", "INPUT DELAY"}, {"サーバー", "SERVER"}, {"戻る", "BACK"}};
        const std::string* values[kRows] = {nullptr, nullptr, &code_, nullptr, &address_, &name_, &port_, nullptr, &server_, nullptr};
        for (int i = 0; i < kRows; ++i) {
            const float y = 112.f + 36.f * i;
            const bool selected = i == row_;
            if (selected) batch.pushSolid({116, y - 6.f, 568, 34}, kHighlight);
            label(batch, say(names[i]), 134, y, 20.f, selected ? kWhite : kPale);
            if (values[i]) drawText(batch, *values[i], y, selected);
            else if ((Row)i == Row::Delay) choice(batch, delay, y, selected);
        }
        if (!state_.onlineMessage.empty()) centred(batch, state_.onlineMessage.c_str(), 400, 508, 18.f, kGold);
        help(batch, edit_.active() ? say({"上下で文字、左右で桁、決定で終了", "Up and down change it, left and right move, confirm finishes."})
                                   : say({"コードにはサーバーが必要です。住所はポートも含みます", "A room code needs a server. Without one, the host may have to forward their port."}));
    }

private:
    enum class Row { Host, Code, CodeText, Join, Address, Name, Port, Delay, Server, Back };
    static constexpr int kRows = 10;

    void drawText(SpriteRenderer& batch, const std::string& value, float y, bool selected) const {
        const float x = 400.f;
        label(batch, value.c_str(), x, y, 20.f, selected ? kWhite : kPale);
        if (edit_.active() && edit_.text == &value) {
            const float before = widthOf(value.substr(0, edit_.cursor).c_str(), 20.f);
            const float width = widthOf(value.substr(edit_.cursor, 1).c_str(), 20.f);
            batch.pushSolid({x + before, y + 24.f, std::max(width, 8.f), 2.f}, kGold);
        }
    }

    FrontendState& state_;
    std::string name_, address_, port_, server_, code_ = "AAAA";
    WheelEdit edit_;
    int row_ = 0, sound_ = -1;
};

// Who is here and whether they are ready. Everything about the match is chosen on the selection
// screen, which starts by itself once everyone is ready.
class OnlineLobbyScreen : public PanelScreen {
public:
    OnlineLobbyScreen(SpriteRenderer& batch, FrontendState& state, std::string& error) : state_(state) {
        if (uploadBackground(batch, "data/config/0001", {{240, 8, 320, 56}, {340, 250, 420, 150}}, background_, error)) loadFace(batch, error);
        if (!state_.online) {
            error = "the online lobby has no room";
            return;
        }
        choice_.name = frontendSettings().playerName;
        state_.online->lobby->set_choice(choice_);
        state_.online->inMatch = false;
        state_.onlineHumans = 0;
    }
    bool loaded() const { return face_.atlasTexture() >= 0; }
    const char* name() const override { return "netplaylobby"; }
    int takeSound() override { const int cue = sound_; sound_ = -1; return cue; }

    ScreenId update(const ScreenInput& in) override {
        net::Lobby& lobby = *state_.online->lobby;
        if (lobby.refused() != net::Refusal::None) return close(net::refusal_text(lobby.refused()));
        if (lobby.host_lost()) return close(say({"部屋から応答がありません。", "The room stopped answering."}));
        if (lobby.is_host() && lobby.can_start()) lobby.start();
        if (lobby.ready()) return begin_selection();

        if (in.cancel) sound_ = 1;
        else if (in.confirm) sound_ = 0;
        else if (in.up || in.down) sound_ = 2;

        if (in.cancel) return leave();
        if (in.up || in.down) row_ = 1 - row_;
        if (in.confirm) {
            if (row_ == 1) return leave();
            choice_.ready = !choice_.ready;
            lobby.set_choice(choice_);
            state_.onlineMessage.clear();
        }
        return ScreenId::NetplayLobby;
    }

    void draw(SpriteRenderer& batch) const override {
        batch.pushSprite(background_, {0, 0, 800, 600}, 0, 0, 0, 0);
        frame(batch, {"通信対戦 ロビー", "ONLINE LOBBY"}, 40, 540);
        const net::Lobby& lobby = *state_.online->lobby;
        const net::MatchPlan& plan = lobby.plan();
        if (!lobby.room_code().empty()) {
            const std::string code = std::string(say({"部屋のコード  ", "ROOM CODE  "})) + lobby.room_code();
            centred(batch, code.c_str(), 400, 460, 28.f, kGold);
        }
        for (int peer = 0; peer < 4; ++peer) {
            const float y = 124.f + 46.f * (float)peer;
            if (peer >= plan.peerCount) {
                label(batch, say({"空き", "EMPTY"}), 134, y, 20.f, kTrack);
                continue;
            }
            const UiColor color = peer == lobby.local_peer() ? kWhite : kPale;
            label(batch, plan.names[(size_t)peer].c_str(), 134, y, 20.f, color);
            if (plan.ready[(size_t)peer]) label(batch, say({"準備完了", "READY"}), 400, y, 20.f, kGold);
            if (peer > 0) {
                char ping[24];
                std::snprintf(ping, sizeof ping, "%d ms", (int)plan.pingMs[(size_t)peer]);
                label(batch, ping, 560, y, 20.f, kPale);
            }
        }
        batch.pushSolid({130, 322, 540, 2}, kGold);
        drawRow(batch, 0, choice_.ready ? say({"準備完了を取消", "NOT READY"}) : say({"準備完了", "READY"}));
        drawRow(batch, 1, say({"部屋を出る", "LEAVE"}));
        const std::string problem = lobby.link_problem();
        if (!problem.empty()) help(batch, problem.c_str());
        else if (!state_.onlineMessage.empty()) help(batch, state_.onlineMessage.c_str());
        else if (plan.peerCount < 2) help(batch, say({"相手を待っています", "Waiting for another player."}));
        else help(batch, say({"全員の準備が完了すると始まります。IPアドレスは他の人に見えます", "It starts when everyone is ready. Other players can see your IP address."}));
    }

private:
    void drawRow(SpriteRenderer& batch, int row, const char* value) const {
        const float y = 350.f + 46.f * (float)row;
        const bool selected = row == row_;
        if (selected) batch.pushSolid({116, y - 6.f, 568, 34}, kHighlight);
        centred(batch, value, 400, y, 20.f, selected ? kWhite : kPale);
    }

    // The selection is the same on every machine from here: same starting state, same inputs.
    ScreenId begin_selection() {
        OnlineContext& online = *state_.online;
        online.matchPlan = online.lobby->plan_for_match();
        online.inMatch = true;
        state_.onlineHumans = online.matchPlan.peerCount;
        state_.randomState = online.matchPlan.seed;
        state_.timeLimit = 0;
        state_.health = state_.gauge = state_.blueBalloon = state_.redBalloon = 100;
        state_.penaltyDecided = {};
        state_.onlineMessage.clear();
        return ScreenId::Select;
    }
    ScreenId leave() {
        state_.online->lobby->leave();
        state_.onlineMessage.clear();
        return ScreenId::NetplayMenu;
    }
    ScreenId close(const char* why) {
        state_.onlineMessage = why;
        return ScreenId::NetplayMenu;
    }

    FrontendState& state_;
    net::LocalChoice choice_;
    int row_ = 0, sound_ = -1;
};

template <class ScreenType>
std::unique_ptr<Screen> makePanel(SpriteRenderer& batch, FrontendState& state, std::string& error) {
    auto screen = std::make_unique<ScreenType>(batch, state, error);
    if (!screen->loaded()) return nullptr;
    return screen;
}

}  // namespace

std::unique_ptr<Screen> makeOnlineMenuScreen(SpriteRenderer& batch, FrontendState& state, std::string& error) {
    return makePanel<OnlineMenuScreen>(batch, state, error);
}

std::unique_ptr<Screen> makeOnlineLobbyScreen(SpriteRenderer& batch, FrontendState& state, std::string& error) {
    return makePanel<OnlineLobbyScreen>(batch, state, error);
}

}  // namespace ui
