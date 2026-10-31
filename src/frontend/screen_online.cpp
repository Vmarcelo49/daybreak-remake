#include "frontend/screen_online.h"

#include <algorithm>
#include <cstdio>
#include <random>
#include <vector>

#include "assets/asset_source.h"
#include "assets/stage_catalog.h"
#include "battle/weapon_definition.h"
#include "frontend/frontend_launch.h"
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

std::string upperWords(const char* text) {
    std::string out(text);
    for (char& c : out) c = c == '_' ? ' ' : c >= 'a' && c <= 'z' ? static_cast<char>(c - 'a' + 'A') : c;
    return out;
}

std::string characterLabel(int character) {
    const char* directory = frontendCharacterDirectory(character);
    return upperWords(directory ? directory : "?");
}

constexpr Words kHypermodes[3] = {{"オヤシロ", "OYASHIRO"}, {"友情", "FRIENDSHIP"}, {"カケラ", "KAKERA"}};

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
    plan.stage = 1;
    plan.variation = 0;
    context->lobby = std::make_unique<net::Lobby>(net::Lobby::host(context->socket, plan, installHash()));
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

namespace {

class OnlineMenuScreen : public PanelScreen {
public:
    OnlineMenuScreen(SpriteRenderer& batch, FrontendState& state, std::string& error) : state_(state) {
        if (uploadBackground(batch, "data/config/0001", {{240, 8, 320, 56}, {340, 250, 420, 150}}, background_, error)) loadFace(batch, error);
        auto& settings = frontendSettings();
        name_ = settings.playerName;
        address_ = settings.netLastHost.empty() ? "192.168.000.001:37564" : settings.netLastHost;
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
        const Words names[kRows] = {{"部屋を作る", "HOST A ROOM"}, {"部屋に入る", "JOIN A ROOM"}, {"相手の住所", "ADDRESS"},
                                    {"名前", "NAME"}, {"ポート", "PORT"}, {"入力遅延", "INPUT DELAY"}, {"戻る", "BACK"}};
        const std::string* values[kRows] = {nullptr, nullptr, &address_, &name_, &port_, nullptr, nullptr};
        for (int i = 0; i < kRows; ++i) {
            const float y = 130.f + 46.f * i;
            const bool selected = i == row_;
            if (selected) batch.pushSolid({116, y - 6.f, 568, 34}, kHighlight);
            label(batch, say(names[i]), 134, y, 20.f, selected ? kWhite : kPale);
            if (values[i]) drawText(batch, *values[i], y, selected);
            else if ((Row)i == Row::Delay) choice(batch, delay, y, selected);
        }
        if (!state_.onlineMessage.empty()) centred(batch, state_.onlineMessage.c_str(), 400, 460, 18.f, kGold);
        help(batch, edit_.active() ? say({"上下で文字、左右で桁、決定で終了", "Up and down change it, left and right move, confirm finishes."})
                                   : say({"住所はポートも含みます", "Join needs the host's address and port. Hosting may need your router to forward the port."}));
    }

private:
    enum class Row { Host, Join, Address, Name, Port, Delay, Back };
    static constexpr int kRows = 7;

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
    std::string name_, address_, port_;
    WheelEdit edit_;
    int row_ = 0, sound_ = -1;
};

class OnlineLobbyScreen : public PanelScreen {
public:
    OnlineLobbyScreen(SpriteRenderer& batch, FrontendState& state, std::string& error) : state_(state) {
        if (uploadBackground(batch, "data/config/0001", {{240, 8, 320, 56}, {340, 250, 420, 150}}, background_, error)) loadFace(batch, error);
        if (!state_.online) {
            error = "the online lobby has no room";
            return;
        }
        choice_.name = frontendSettings().playerName;
        choice_.character = 0;
        choice_.ready = isHost();
        state_.online->lobby->set_choice(choice_);
        state_.online->inMatch = false;
        row_ = actionRow();
    }
    bool loaded() const { return face_.atlasTexture() >= 0; }
    const char* name() const override { return "netplaylobby"; }
    int takeSound() override { const int cue = sound_; sound_ = -1; return cue; }

    ScreenId update(const ScreenInput& in) override {
        net::Lobby& lobby = *state_.online->lobby;
        if (lobby.refused() != net::Refusal::None) return close(net::refusal_text(lobby.refused()));
        if (lobby.host_lost()) return close(say({"部屋から応答がありません。", "The room stopped answering."}));
        if (lobby.ready()) return begin_match();

        if (in.cancel) sound_ = 1;
        else if (in.confirm) sound_ = 0;
        else if (in.up || in.down || in.left || in.right) sound_ = 2;

        if (in.cancel) return leave();
        const int rows = rowCount();
        if (in.up) row_ = (row_ + rows - 1) % rows;
        else if (in.down) row_ = (row_ + 1) % rows;

        const int dx = in.left ? -1 : in.right ? 1 : 0;
        // A player who said ready has chosen. The host's start stands for its own ready.
        const bool frozen = !isHost() && choice_.ready;
        if (dx && !frozen) {
            if (row_ == 0) {
                choice_.character = (choice_.character + dx + 16) % 16;
                choice_.weapon = std::min(choice_.weapon, gameplay::weaponCountForCharacter(choice_.character) - 1);
            } else if (row_ == 1) {
                const int count = gameplay::weaponCountForCharacter(choice_.character);
                choice_.weapon = (choice_.weapon + dx + count) % count;
            } else if (row_ == 2) {
                choice_.specialMode = (choice_.specialMode + (unsigned)dx + 3u) % 3u;
            }
            lobby.set_choice(choice_);
        }
        if (dx && isHost()) edit_rules(dx);
        if (in.confirm) {
            if (row_ == rows - 1) return leave();
            if (row_ == actionRow()) {
                if (isHost()) start();
                else {
                    choice_.ready = !choice_.ready;
                    lobby.set_choice(choice_);
                }
            }
        }
        return ScreenId::NetplayLobby;
    }

    void draw(SpriteRenderer& batch) const override {
        batch.pushSprite(background_, {0, 0, 800, 600}, 0, 0, 0, 0);
        frame(batch, {"通信対戦 ロビー", "ONLINE LOBBY"}, 20, 560);
        const net::MatchPlan& plan = state_.online->lobby->plan();
        const char* com = "COM";
        for (int i = 0; i < 4; ++i) {
            const float y = 88.f + 30.f * (float)i;
            const net::PlanSlot& slot = plan.slots[(size_t)i];
            batch.pushSolid({116, y - 4.f, 8, 26}, i < 2 ? UiColor{0.3f, 0.5f, 1.f, 1.f} : UiColor{1.f, 0.3f, 0.3f, 1.f});
            const bool mine = slot.peer == state_.online->lobby->local_peer();
            const UiColor color = mine ? kWhite : kPale;
            const char* who = slot.peer < 0 ? com : plan.names[(size_t)slot.peer].c_str();
            label(batch, who, 134, y, 18.f, color);
            if (slot.peer >= 0) {
                char fighter[64];
                std::snprintf(fighter, sizeof fighter, "%s  %d", characterLabel(slot.character).c_str(), slot.weapon + 1);
                label(batch, fighter, 300, y, 18.f, color);
                if (plan.ready[(size_t)slot.peer]) label(batch, say({"準備完了", "READY"}), 490, y, 18.f, kGold);
                if (slot.peer > 0) {
                    char ping[24];
                    std::snprintf(ping, sizeof ping, "%d ms", (int)plan.pingMs[(size_t)slot.peer]);
                    label(batch, ping, 600, y, 18.f, kPale);
                }
            }
        }
        batch.pushSolid({130, 212, 540, 2}, kGold);

        char weapon[24];
        std::snprintf(weapon, sizeof weapon, "%d", choice_.weapon + 1);
        drawRow(batch, 0, say({"キャラクター", "CHARACTER"}), characterLabel(choice_.character).c_str());
        drawRow(batch, 1, say({"武器", "WEAPON"}), weapon);
        drawRow(batch, 2, say({"ハイパーモード", "HYPERMODE"}), say(kHypermodes[choice_.specialMode]));
        if (isHost()) {
            char limit[32], health[32];
            const std::string stage = stageChoice_ == 0 ? say({"ランダム", "RANDOM"}) : upperWords(assets::kStages[stageChoice_ - 1].name);
            if (plan.timeLimitSeconds == 0) std::snprintf(limit, sizeof limit, "%s", say({"無制限", "NO LIMIT"}));
            else std::snprintf(limit, sizeof limit, "%u", plan.timeLimitSeconds);
            std::snprintf(health, sizeof health, "%d%%", plan.rules[0]);
            drawRow(batch, 3, say({"ステージ", "STAGE"}), stage.c_str());
            drawRow(batch, 4, say({"制限時間", "TIME LIMIT"}), limit);
            drawRow(batch, 5, say({"体力値", "HEALTH"}), health);
        }
        const bool ready = !isHost() && choice_.ready;
        drawCentred(batch, actionRow(), isHost() ? say({"戦闘開始", "START"}) : ready ? say({"準備完了を取消", "NOT READY"}) : say({"準備完了", "READY"}));
        drawCentred(batch, rowCount() - 1, say({"部屋を出る", "LEAVE"}));

        const net::Lobby& lobby = *state_.online->lobby;
        const char* status;
        if (isHost()) status = plan.peerCount < 2 ? say({"相手を待っています", "Waiting for another player."})
                             : lobby.can_start() ? say({"全員の準備が完了しました", "Everyone is ready."})
                                                 : say({"全員の準備を待っています", "Waiting for everyone to be ready."});
        else status = plan.peerCount < 2 ? say({"接続しています", "Connecting."}) : say({"ホストの開始を待っています", "Other players can see your IP address."});
        help(batch, status);
    }

private:
    bool isHost() const { return state_.online->lobby->is_host(); }
    int actionRow() const { return isHost() ? 6 : 3; }
    int rowCount() const { return actionRow() + 2; }

    void drawRow(SpriteRenderer& batch, int row, const char* name, const char* value) const {
        const float y = 226.f + 36.f * (float)row;
        const bool selected = row == row_;
        if (selected) batch.pushSolid({116, y - 6.f, 568, 32}, kHighlight);
        label(batch, name, 134, y, 18.f, selected ? kWhite : kPale);
        choice(batch, value, y, selected);
    }
    void drawCentred(SpriteRenderer& batch, int row, const char* value) const {
        const float y = 226.f + 36.f * (float)row;
        const bool selected = row == row_;
        if (selected) batch.pushSolid({116, y - 6.f, 568, 32}, kHighlight);
        centred(batch, value, 400, y, 18.f, selected ? kWhite : kPale);
    }

    void edit_rules(int dx) {
        net::MatchPlan& plan = state_.online->lobby->edit_plan();
        const int stages = (int)(sizeof(assets::kStages) / sizeof(assets::kStages[0])) + 1;
        if (row_ == 3) stageChoice_ = (stageChoice_ + dx + stages) % stages;
        else if (row_ == 4) plan.timeLimitSeconds = (plan.timeLimitSeconds + (unsigned)(dx * 60) + 360u) % 360u;
        else if (row_ == 5) plan.rules[0] = std::clamp(plan.rules[0] + dx * 25, 50, 200);
    }

    void start() {
        net::Lobby& lobby = *state_.online->lobby;
        if (!lobby.can_start()) return;
        net::MatchPlan& plan = lobby.edit_plan();
        std::random_device random;
        const int stages = (int)(sizeof(assets::kStages) / sizeof(assets::kStages[0]));
        const assets::StageId& stage = assets::kStages[stageChoice_ == 0 ? random() % (unsigned)stages : (unsigned)(stageChoice_ - 1)];
        plan.stage = (unsigned)stage.scene;
        plan.variation = (unsigned)stage.timeOfDay;
        for (net::PlanSlot& slot : plan.slots) {
            if (slot.peer >= 0) continue;
            slot.character = (int)(random() % 16u);
            slot.weapon = (int)(random() % (unsigned)gameplay::weaponCountForCharacter(slot.character));
        }
        lobby.start();
    }

    ScreenId begin_match() {
        OnlineContext& online = *state_.online;
        online.matchPlan = online.lobby->plan();
        online.inMatch = true;
        const net::MatchPlan& plan = online.matchPlan;
        for (size_t panel = 0; panel < plan.slots.size(); ++panel) {
            const net::PlanSlot& slot = plan.slots[panel];
            state_.slots[panel] = {slot.character, slot.weapon, (int)slot.specialMode, slot.costume,
                                   slot.peer == online.lobby->local_peer() ? 0 : 4, true};
        }
        state_.stage = (int)plan.stage;
        state_.variation = (int)plan.variation;
        state_.timeLimit = (int)plan.timeLimitSeconds;
        state_.health = plan.rules[0];
        state_.gauge = plan.rules[1];
        state_.blueBalloon = plan.rules[2];
        state_.redBalloon = plan.rules[3];
        return ScreenId::VsIntro;
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
    int row_ = 0, sound_ = -1, stageChoice_ = 1;
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
