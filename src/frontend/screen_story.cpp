#include "frontend/screen_story.h"

#include <cstdio>
#include <map>
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

std::string withoutExtension(const std::string& path) {
    return path.substr(0, path.find_last_of('.'));
}

class StoryScreen final : public Screen {
public:
    StoryScreen(SpriteRenderer& batch, FrontendState& state, std::string& error)
        : batch_(batch), state_(state), error_(error), dialogue_(loadScript(state.storyScript, error)) {
        if (!error.empty()) return;
        if (!uploadCnvSheet(batch, "data/talk/window", window_, error)) return;
        if (!caption_.load(batch, kFontCell, error, kStoryFont, nullptr)) return;
        std::printf("[story] script %s\n", state.storyScript.c_str());
        prepareAssets();
    }

    ScreenId update(const ScreenInput& in) override {
        if (in.escape) return ScreenId::Title;
        const auto result = dialogue_.update(in.confirm, in.start);
        prepareAssets();
        if (result != StoryDialogue::Result::Running) return ScreenId::Title;
        return ScreenId::StoryAdv;
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

private:
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
    int window_ = -1;
};

}  // namespace

std::unique_ptr<Screen> makeStoryScreen(SpriteRenderer& batch, FrontendState& state, std::string& error) {
    auto screen = std::make_unique<StoryScreen>(batch, state, error);
    if (!error.empty()) return nullptr;
    return screen;
}

}  // namespace ui
