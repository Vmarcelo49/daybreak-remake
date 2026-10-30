#include "frontend/screen_story.h"

#include <algorithm>
#include <cstdio>
#include <map>
#include <utility>
#include <vector>

#include "assets/asset_source.h"
#include "assets/cnv.h"
#include "frontend/frontend_state.h"
#include "frontend/story_dialogue.h"
#include "hud/hud_atlas.h"
#include "ui/caption.h"

namespace ui {
namespace {

// FUN_0040f130's layout, in the 800x600 canvas.
constexpr float kPortraitY = 88.f, kPortraitSize = 512.f, kPortraitHotspot = 256.f;
constexpr UiRect kWindow{10.f, 440.f, 780.f, 150.f}, kWindowSource{0.f, 0.f, 780.f, 150.f};
constexpr UiRect kPrompt{720.f, 550.f, 64.f, 32.f}, kPromptSource{0.f, 160.f, 64.f, 32.f};
constexpr float kTextX = 20.f, kTextY = 450.f, kRowHeight = 34.f, kShadow = 3.f;
constexpr float kFontCell = 24.f;  // FUN_0065d7e0's 0x18
// The port's stand-in for ＭＳ ゴシック bold, which is not ours to ship.
constexpr const char* kStoryFont = "NotoSansCJKjp-Bold.otf";

std::vector<StoryCommand> loadScript(const std::string& path, std::string& error) {
    std::vector<uint8_t> bytes;
    if (!fnd::assets::assetSource().read(path, bytes) || bytes.empty()) {
        error = "story: cannot read " + path;
        return {};
    }
    return parseStoryScript(xm::sjisToUtf8(std::string(bytes.begin(), bytes.end())));
}

// FUN_006492f0 and the team-select's own picks: the human on panel 0, the ally beside them.
void prepareStoryFight(FrontendState& state) {
    const StoryLadder& story = state.story;
    const StoryFight& fight = story.current();
    for (int side = 0; side < 2; ++side) {
        FrontendSlot& member = state.slots[side];
        member.character = story.members[side];
        member.controller = side == 0 ? 0 : 4;

        FrontendSlot& enemy = state.slots[side + 2];
        enemy = FrontendSlot{};
        enemy.character = fight.enemies[side];
        enemy.weapon = storyEnemyWeapon(story.team, story.fight, enemy.character, state.nextRandom());
        enemy.hypermode = static_cast<int>(state.nextRandom() % 3);
    }
    state.stage = fight.stage;
    state.variation = 0;
    state.timeLimit = 0;
    state.health = state.gauge = state.blueBalloon = state.redBalloon = 100;
}

std::string withoutExtension(const std::string& path) {
    return path.substr(0, path.find_last_of('.'));
}

class StoryScreen final : public Screen {
public:
    StoryScreen(SpriteRenderer& batch, FrontendState& state, std::string& error)
        : batch_(batch), state_(state), error_(error),
          dialogue_(loadScript(state.story.active ? state.story.scriptPath() : state.storyScript, error)) {
        if (!error.empty()) return;
        if (!uploadCnvSheet(batch, "data/talk/window", window_, error)) return;
        if (!caption_.load(batch, kFontCell, error, kStoryFont, nullptr)) return;
        std::printf("[story] script %s\n", state.story.active ? state.story.scriptPath().c_str()
                                                              : state.storyScript.c_str());
        prepareAssets();
    }

    // The stack keeps calling update through the fade out, so a decision to leave is final.
    ScreenId update(const ScreenInput& in) override {
        if (leaving_ != ScreenId::StoryAdv) return leaving_;
        return leaving_ = step(in);
    }

    void draw(SpriteRenderer& batch) const override {
        const int background = textureFor(dialogue_.background());
        if (background >= 0) batch.pushTextured(background, {0, 0, 800, 600}, sourceUv(background, {0, 0, 800, 600}), {});
        drawFade(batch, dialogue_.backgroundFade());
        for (int slot : dialogue_.drawOrder()) drawPortrait(batch, slot);

        const UiColor translucent{1.f, 1.f, 1.f, 128.f / 255.f};
        batch.pushTextured(window_, kWindow, sourceUv(window_, kWindowSource), translucent);
        if (dialogue_.promptVisible())
            batch.pushTextured(window_, kPrompt, sourceUv(window_, kPromptSource), translucent);

        const auto rows = storyVisibleRows(dialogue_.line(), dialogue_.revealed());
        for (size_t row = 0; row < rows.size(); ++row) {
            const float y = kTextY + kRowHeight * static_cast<float>(row);
            caption_.draw(batch, rows[row].c_str(), kTextX + kShadow, y + kShadow, 1.f, {0, 0, 0, 1});
            caption_.draw(batch, rows[row].c_str(), kTextX, y, 1.f, {});
        }
        drawFade(batch, dialogue_.screenFade());
    }

    const char* name() const override { return "story"; }
    std::string takeVoice() override { return dialogue_.takeVoice(); }
    std::string takeMusic() override { return dialogue_.takeMusic(); }
    bool takeMusicStop() override { return dialogue_.takeMusicStop(); }

private:
    ScreenId step(const ScreenInput& in) {
        if (in.escape) return ScreenId::Title;
        const auto result = dialogue_.update(in.confirm, in.start);
        prepareAssets();
        if (result == StoryDialogue::Result::Running) return ScreenId::StoryAdv;
        if (!state_.story.active) return ScreenId::Title;
        StoryLadder& story = state_.story;
        // FUN_0040eb30:68-82 and :120-130.
        if (result == StoryDialogue::Result::ScriptEnded) {
            if (story.part == 0) {
                story.part = 1;
                prepareStoryFight(state_);
                return ScreenId::VsIntro;
            }
            story.part = 0;
            ++story.fight;
            dialogue_.beginInterlude();
            return ScreenId::StoryAdv;
        }
        if (story.fight >= kStoryFights) return ScreenId::Title;
        std::string failure;
        dialogue_.load(loadScript(story.scriptPath(), failure));
        if (!failure.empty()) {
            error_ = failure;
            return ScreenId::Title;
        }
        prepareAssets();
        return ScreenId::StoryAdv;
    }

    void prepareAssets() {
        ensureTexture(dialogue_.background());
        for (int slot = 0; slot < kStorySlots; ++slot) ensureTexture(dialogue_.portrait(slot));
        std::string failure;
        if (dialogue_.line() != preparedLine_) {
            preparedLine_ = dialogue_.line();
            caption_.prepare(batch_, {preparedLine_}, failure);
        }
        if (!failure.empty() && error_.empty()) error_ = failure;
    }

    void ensureTexture(const std::string& path) {
        if (path.empty() || textures_.count(path)) return;
        int slot = -1;
        std::string failure;
        if (!uploadCnvSheet(batch_, withoutExtension(path).c_str(), slot, failure)) {
            std::fprintf(stderr, "[story] %s\n", failure.c_str());
            slot = -1;
        }
        textures_[path] = slot;
    }

    int textureFor(const std::string& path) const {
        const auto found = textures_.find(path);
        return found == textures_.end() ? -1 : found->second;
    }

    UiRect sourceUv(int texture, const UiRect& source) const {
        uint32_t w = 0, h = 0;
        if (!batch_.textureSize(texture, w, h) || !w || !h) return {0, 0, 1, 1};
        return {source.x / w, source.y / h, source.w / w, source.h / h};
    }

    void drawFade(SpriteRenderer& batch, int alpha) const {
        if (alpha > 0) batch.pushSolid({0, 0, 800, 600}, {0, 0, 0, alpha / 255.f});
    }

    void drawPortrait(SpriteRenderer& batch, int slot) const {
        const int texture = textureFor(dialogue_.portrait(slot));
        if (texture < 0) return;
        UiRect uv = sourceUv(texture, {0, 0, kPortraitSize, kPortraitSize});
        // FUN_0040f4c0:73-74: the two right-hand slots and up face the other way.
        if (slot > 1) {
            uv.x += uv.w;
            uv.w = -uv.w;
        }
        batch.pushTextured(texture, {dialogue_.portraitX(slot) - kPortraitHotspot, kPortraitY, kPortraitSize, kPortraitSize}, uv, {});
    }

    SpriteRenderer& batch_;
    FrontendState& state_;
    std::string& error_;
    StoryDialogue dialogue_;
    mutable CaptionText caption_;
    std::map<std::string, int> textures_;
    std::string preparedLine_;
    ScreenId leaving_ = ScreenId::StoryAdv;
    int window_ = -1;
};

class StoryRetryScreen final : public Screen {
public:
    StoryRetryScreen(SpriteRenderer& batch, std::string& error) {
        uploadCnvSheet(batch, "data/object/system", sheet_, error);
    }

    ScreenId update(const ScreenInput& in) override {
        if (leaving_ != ScreenId::Result) return leaving_;
        if (fade_ > 0) fade_ = std::max(0, fade_ - 5);
        if (in.left || in.right) {
            choice_ = 1 - choice_;
            sound_ = 2;
        } else if (in.confirm) {
            sound_ = 0;
            // PORT RULE: the original restarts the round in place (FUN_00634760); the port goes
            // back through VS, which rebuilds the same fight.
            leaving_ = choice_ == 0 ? ScreenId::VsIntro : ScreenId::GameOver;
            return leaving_;
        }
        return ScreenId::Result;
    }

    void draw(SpriteRenderer& batch) const override {
        const float shown = (255 - fade_) / 255.f;
        batch.pushSolid({0, 0, 800, 60}, {0, 0, 0, 1});
        batch.pushSolid({0, 424, 800, 176}, {0, 0, 0, 1});
        batch.pushSolid({0, 0, 800, 600}, {0, 0, 0, (0x80 - fade_ / 2) / 255.f});
        const UiColor tint{1, 1, 1, shown};
        batch.pushTextured(sheet_, {192, 168, 416, 64}, sourceUv(batch, {0, 128, 416, 64}), tint);
        drawOption(batch, 272, 0, choice_ == 0, tint);
        drawOption(batch, 400, 1, choice_ == 1, tint);
    }

    const char* name() const override { return "story retry"; }
    int takeSound() override { return std::exchange(sound_, -1); }

private:
    UiRect sourceUv(const SpriteRenderer& batch, const UiRect& source) const {
        uint32_t w = 0, h = 0;
        if (!batch.textureSize(sheet_, w, h) || !w || !h) return {0, 0, 1, 1};
        return {source.x / w, source.y / h, source.w / w, source.h / h};
    }
    void drawOption(SpriteRenderer& batch, float x, int row, bool chosen, const UiColor& tint) const {
        const UiRect source{chosen ? 0.f : 256.f, 192.f + row * 64.f, 256.f, 64.f};
        batch.pushTextured(sheet_, {x, 300, 256, 64}, sourceUv(batch, source), tint);
    }

    int sheet_ = -1;
    ScreenId leaving_ = ScreenId::Result;
    int fade_ = 255;
    int choice_ = 0;
    int sound_ = -1;
};

class GameOverScreen final : public Screen {
public:
    GameOverScreen(SpriteRenderer& batch, std::string& error) {
        uploadCnvSheet(batch, "data/object/gameover", sheet_, error);
    }
    ScreenId update(const ScreenInput& in) override {
        return in.confirm || in.cancel ? ScreenId::Title : ScreenId::GameOver;
    }
    void draw(SpriteRenderer& batch) const override {
        uint32_t w = 0, h = 0;
        if (!batch.textureSize(sheet_, w, h) || !w || !h) return;
        batch.pushTextured(sheet_, {0, 0, 800, 600}, {0, 0, 800.f / w, 600.f / h}, {});
    }
    const char* name() const override { return "game over"; }

private:
    int sheet_ = -1;
};

}  // namespace

bool beginStoryTeam(FrontendState& state, int team, std::string& error) {
    char path[48];
    std::snprintf(path, sizeof path, "data/scenario/team%02d.dat", team);
    std::vector<uint8_t> bytes;
    if (team < 0 || team >= kStoryTeams || !fnd::assets::assetSource().read(path, bytes) ||
        !parseStoryLadder(bytes, team, [&state] { return state.nextRandom(); }, state.story)) {
        error = std::string("story: cannot read ") + path;
        return false;
    }
    state.story.active = true;
    return true;
}

std::unique_ptr<Screen> makeStoryRetryScreen(SpriteRenderer& batch, FrontendState&, std::string& error) {
    auto screen = std::make_unique<StoryRetryScreen>(batch, error);
    if (!error.empty()) return nullptr;
    return screen;
}

std::unique_ptr<Screen> makeGameOverScreen(SpriteRenderer& batch, FrontendState&, std::string& error) {
    auto screen = std::make_unique<GameOverScreen>(batch, error);
    if (!error.empty()) return nullptr;
    return screen;
}

std::unique_ptr<Screen> makeStoryScreen(SpriteRenderer& batch, FrontendState& state, std::string& error) {
    auto screen = std::make_unique<StoryScreen>(batch, state, error);
    if (!error.empty()) return nullptr;
    return screen;
}

}  // namespace ui
