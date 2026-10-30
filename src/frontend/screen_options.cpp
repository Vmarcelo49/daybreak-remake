#include "frontend/screen_options.h"
#include "frontend/frontend_settings.h"
#include "assets/asset_source.h"
#include "assets/cnv.h"
#include "ui/caption.h"
#include "ui/sheet_locale.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <initializer_list>
#include <vector>
#include <SDL3/SDL.h>
namespace ui {
namespace {
// A screen of our own over the original's backgrounds, not a port of FUN_00403470/FUN_00404a50: the
// baked labels mixed faces with the runtime captions. Every word here is one face.
constexpr const char* kFace = "Goldman-Bold.ttf";
constexpr float kFaceCell = 64.f;
constexpr int kKeyConfigBackRow = fnd::input::ActionCount;

constexpr UiColor kWhite{1.f, 1.f, 1.f, 1.f};
constexpr UiColor kPale{0.72f, 0.76f, 0.86f, 1.f};
constexpr UiColor kGold{1.f, 0.82f, 0.3f, 1.f};
constexpr UiColor kPanel{0.03f, 0.04f, 0.09f, 0.72f};
constexpr UiColor kHighlight{0.16f, 0.32f, 0.72f, 0.85f};
constexpr UiColor kTrack{1.f, 1.f, 1.f, 0.18f};

struct Words { const char* ja; const char* en; };
const char* say(const Words& words) { return sheetLanguage().empty() ? words.ja : words.en; }

enum class OptionRow { Toon, Shadow, Fullscreen, Resolution, Master, Music, Voice, Sfx, Back, Count };
constexpr int kOptionRowCount = (int)OptionRow::Count;
constexpr float kOptionY[kOptionRowCount] = {132, 170, 208, 246, 332, 370, 408, 446, 498};
constexpr Words kOptionNames[kOptionRowCount] = {
    {"トゥーンレンダリング", "TOON SHADING"}, {"影の表示", "SHADOWS"}, {"画面モード", "SCREEN MODE"}, {"解像度", "RESOLUTION"},
    {"全体の音量", "MASTER"}, {"音楽の音量", "MUSIC"}, {"音声の音量", "VOICE"}, {"効果音の音量", "EFFECTS"}, {"終了", "BACK"},
};
constexpr Words kOptionHelp[kOptionRowCount] = {
    {"←→ でトゥーンレンダリングを切り替えます", "Left and right switch the cartoon outlines and shading."},
    {"←→ で影の表示を切り替えます", "Left and right switch the character shadows."},
    {"←→ で画面モードを切り替えます", "Left and right switch the window and fullscreen."},
    {"←→ で解像度を変更します", "Left and right change the resolution."},
    {"←→ で全体の音量を調整します", "Left and right set the overall volume."},
    {"←→ で音楽の音量を調整します", "Left and right set the music volume."},
    {"←→ で音声の音量を調整します", "Left and right set the voice volume."},
    {"←→ で効果音の音量を調整します", "Left and right set the effects volume."},
    {"設定を終了します", "Return to the title."},
};
constexpr Words kBindingNames[fnd::input::ActionCount] = {
    {"上", "UP"}, {"下", "DOWN"}, {"左", "LEFT"}, {"右", "RIGHT"}, {"ジャンプ／決定", "JUMP / OK"}, {"格闘／キャンセル", "MELEE / CANCEL"},
    {"射撃", "SHOOT"}, {"ロック切り替え", "LOCK SWITCH"}, {"特殊", "SPECIAL"}, {"ガード", "GUARD"}, {"作戦", "TACTICS"}, {"ポーズ", "PAUSE"},
};

// The backgrounds carry their old title and rows in the photo: each column blends across the hole.
bool uploadBackground(SpriteRenderer& batch, const char* stem, std::initializer_list<UiRect> holes, int& slot, std::string& error) {
    std::vector<uint8_t> bytes;
    if (!fnd::assets::assetSource().read(std::string(stem) + ".cnv", bytes)) {
        error = std::string(stem) + ".cnv is in no open bundle and on no filesystem path";
        return false;
    }
    xm::CnvImage image = xm::decodeCnvImage(bytes.data(), bytes.size());
    const int w = (int)image.width, h = (int)image.height;
    for (const UiRect& hole : holes) {
        const int x0 = std::max(0, (int)hole.x), x1 = std::min(w, (int)(hole.x + hole.w));
        const int y0 = std::max(1, (int)hole.y), y1 = std::min(h - 1, (int)(hole.y + hole.h));
        for (int x = x0; x < x1; ++x) {
            const uint8_t* above = image.rgba.data() + ((size_t)(y0 - 1) * w + x) * 4;
            const uint8_t* below = image.rgba.data() + ((size_t)y1 * w + x) * 4;
            for (int y = y0; y < y1; ++y) {
                const float t = (y - y0 + 1.f) / (y1 - y0 + 1.f);
                uint8_t* p = image.rgba.data() + ((size_t)y * w + x) * 4;
                for (int c = 0; c < 4; ++c) p[c] = (uint8_t)std::lround(above[c] * (1.f - t) + below[c] * t);
            }
        }
    }
    slot = batch.addTexture(image.width, image.height, image.rgba.data(), error);
    return slot >= 0;
}

class ConfigScreen : public Screen {
public:
    ConfigScreen(SpriteRenderer& batch, bool keys, std::string& error) : keys_(keys) {
        const bool ok = keys ? uploadBackground(batch, "data/keyconfig/0000", {{240, 8, 320, 56}, {120, 92, 560, 420}}, background_, error)
                             : uploadBackground(batch, "data/config/0001", {{240, 8, 320, 56}, {340, 250, 270, 140}}, background_, error);
        if (ok) face_.load(batch, kFaceCell, error, kFace, kCaptionFallbackFile);
    }
    ~ConfigScreen() override { if (keys_) cancelBindingCapture(); }
    bool loaded() const { return face_.atlasTexture() >= 0; }
    int takeSound() override { const int cue=sound_; sound_=-1; return cue; }
    const char* name() const override { return keys_ ? "keyconfig" : "options"; }
    ScreenId update(const ScreenInput& in) override {
        const auto stay = keys_ ? ScreenId::KeyConfig : ScreenId::Options;
        if(in.cancel) sound_=1;
        else if(in.confirm) sound_=0;
        else if(in.up||in.down||in.left||in.right) sound_=2;
        if (keys_ && bindingCaptureActive()) { if (in.cancel) cancelBindingCapture(); return stay; }
        if (in.cancel) return ScreenId::Title;
        const int rows = keys_ ? kKeyConfigBackRow + 1 : kOptionRowCount;
        if (in.up) row_ = (row_ + rows - 1) % rows;
        else if (in.down) row_ = (row_ + 1) % rows;
        if (in.confirm && row_ == rows - 1) return ScreenId::Title;
        auto& settings = frontendSettings();
        if (keys_) {
            if (in.left) player_ = (player_ + 3) % 4;
            if (in.right) player_ = (player_ + 1) % 4;
            if (in.confirm) armBindingCapture(player_,kBindingRowActions[row_]);
        } else if (in.left || in.right || in.confirm) {
            switch ((OptionRow)row_) {
            case OptionRow::Toon:
                // The renderer's appearance follows frontendSettings() every frame, so the change
                // is in the next drawn frame, and nothing re-uploads.
                settings.toonRendering = !settings.toonRendering;
                break;
            case OptionRow::Shadow:
                settings.shadowRendering = !settings.shadowRendering;
                break;
            case OptionRow::Fullscreen:
                settings.fullscreen = !settings.fullscreen;
                if (settings.applyFullscreen) settings.applyFullscreen(settings.fullscreen);
                break;
            case OptionRow::Resolution:
                if (settings.resolutionAvailable) settings.cycleResolution(in.left ? -1 : 1);
                break;
            case OptionRow::Master:
            case OptionRow::Music:
            case OptionRow::Voice:
            case OptionRow::Sfx: {
                // Volumes act on left/right only.
                if (!in.left && !in.right) break;
                int* sliders[] = {&settings.volumes.master,&settings.volumes.music,&settings.volumes.voice,&settings.volumes.sfx};
                int& volume = *sliders[row_ - (int)OptionRow::Master];
                volume = std::clamp(volume + (in.right ? 5 : -5),0,100);
                if (settings.applyVolumes) settings.applyVolumes(settings.volumes);
                break;
            }
            default: break;
            }
        }
        return stay;
    }
    void draw(SpriteRenderer& batch) const override {
        batch.pushSprite(background_,{0,0,800,600},0,0,0,0);
        if (keys_) drawKeyConfig(batch);
        else drawOptions(batch);
    }
private:
    void label(SpriteRenderer& batch, const char* value, float x, float y, float size, UiColor color = kWhite) const {
        face_.draw(batch, value, x, y, size / kFaceCell, color, 1.2f);
    }
    float widthOf(const char* value, float size) const { return face_.width(value) * size / kFaceCell; }
    void centred(SpriteRenderer& batch, const char* value, float x, float y, float size, UiColor color = kWhite) const {
        label(batch, value, x - widthOf(value, size) / 2.f, y, size, color);
    }
    // One value between arrows, so every row reads the same way.
    void choice(SpriteRenderer& batch, const char* value, float y, bool selected) const {
        constexpr float kCentre = 540.f, kReach = 130.f;
        centred(batch, value, kCentre, y, 20.f, selected ? kWhite : kPale);
        if (selected) {
            label(batch, "<", kCentre - kReach, y, 20.f, kGold);
            label(batch, ">", kCentre + kReach - 8.f, y, 20.f, kGold);
        }
    }
    void slider(SpriteRenderer& batch, int value, float y, bool selected) const {
        constexpr float kLeft = 410.f, kWidth = 200.f;
        batch.pushSolid({kLeft, y + 8.f, kWidth, 8.f}, kTrack);
        batch.pushSolid({kLeft, y + 8.f, kWidth * value / 100.f, 8.f}, selected ? kGold : kPale);
        char percent[16];
        std::snprintf(percent, sizeof percent, "%d%%", value);
        label(batch, percent, kLeft + kWidth + 16.f, y, 20.f, selected ? kWhite : kPale);
    }
    void frame(SpriteRenderer& batch, const Words& title, float top, float bottom) const {
        batch.pushSolid({100, top, 600, bottom - top}, kPanel);
        centred(batch, say(title), 400, top + 12.f, 34.f, kGold);
        batch.pushSolid({130, top + 58.f, 540, 2}, kGold);
    }
    void help(SpriteRenderer& batch, const char* value) const {
        batch.pushSolid({0, 548, 800, 36}, kPanel);
        centred(batch, value, 400, 555, 16.f, kPale);
    }
    void drawOptions(SpriteRenderer& batch) const {
        const auto& settings = frontendSettings();
        frame(batch, {"環境設定", "OPTIONS"}, 40, 540);
        label(batch, say({"映像", "GRAPHICS"}), 130, 104, 16.f, kGold);
        label(batch, say({"音量", "SOUND"}), 130, 304, 16.f, kGold);
        const Words on{"有効", "ON"}, off{"無効", "OFF"};
        for (int i = 0; i < kOptionRowCount; ++i) {
            const float y = kOptionY[i];
            const bool selected = i == row_;
            if (selected) batch.pushSolid({116, y - 6.f, 568, 34}, kHighlight);
            if ((OptionRow)i == OptionRow::Back) {
                centred(batch, say(kOptionNames[i]), 400, y, 20.f, selected ? kWhite : kPale);
                continue;
            }
            label(batch, say(kOptionNames[i]), 134, y, 20.f, selected ? kWhite : kPale);
        }
        const auto isRow = [&](OptionRow r) { return row_ == (int)r; };
        choice(batch, say(settings.toonRendering ? on : off), kOptionY[(int)OptionRow::Toon], isRow(OptionRow::Toon));
        choice(batch, say(settings.shadowRendering ? on : off), kOptionY[(int)OptionRow::Shadow], isRow(OptionRow::Shadow));
        choice(batch, say(settings.fullscreen ? Words{"フルスクリーン", "FULLSCREEN"} : Words{"ウィンドウ", "WINDOW"}),
               kOptionY[(int)OptionRow::Fullscreen], isRow(OptionRow::Fullscreen));
        char resolution[64];
        if (!settings.resolutionAvailable) {
#if defined(__EMSCRIPTEN__)
            std::snprintf(resolution, sizeof resolution, "%s", say({"ブラウザに合わせる", "BROWSER SIZE"}));
#else
            std::snprintf(resolution, sizeof resolution, "%s", say({"固定", "FIXED"}));
#endif
        } else if (settings.resolutionIndex == 0) {
            std::snprintf(resolution, sizeof resolution, "%d x %d", settings.displayResolution.width, settings.displayResolution.height);
        } else {
            const auto size = settings.resolutions[settings.resolutionIndex];
            std::snprintf(resolution, sizeof resolution, "%d x %d", size.width, size.height);
        }
        choice(batch, resolution, kOptionY[(int)OptionRow::Resolution], isRow(OptionRow::Resolution));
        const int values[] = {settings.volumes.master, settings.volumes.music, settings.volumes.voice, settings.volumes.sfx};
        for (int i = 0; i < 4; ++i) {
            const int row = (int)OptionRow::Master + i;
            slider(batch, values[i], kOptionY[row], row_ == row);
        }
        help(batch, say(kOptionHelp[row_]));
    }
    void drawKeyConfig(SpriteRenderer& batch) const {
        const auto& settings = frontendSettings();
        frame(batch, {"操作設定", "CONTROLS"}, 14, 542);
        constexpr float kFirstRow = 104.f, kPitch = 31.f, kColumn = 330.f, kColumnWidth = 88.f;
        static const char* const kPlayers[4] = {"1P", "2P", "3P", "4P"};
        for (int p = 0; p < 4; ++p)
            centred(batch, kPlayers[p], kColumn + kColumnWidth * (p + 0.5f), 78, 18.f, player_ == p ? kGold : kPale);
        for (int a = 0; a < fnd::input::ActionCount; ++a) {
            const float y = kFirstRow + a * kPitch;
            const bool selected = a == row_;
            if (selected) {
                batch.pushSolid({116, y - 4.f, 568, 28}, {1.f, 1.f, 1.f, 0.08f});
                batch.pushSolid({kColumn + player_ * kColumnWidth, y - 4.f, kColumnWidth, 28}, kHighlight);
            }
            label(batch, say(kBindingNames[a]), 134, y, 17.f, selected ? kWhite : kPale);
            for (int p = 0; p < 4; ++p) {
                const int code = p == 0 ? settings.keyboard[kBindingRowActions[a]] : settings.gamepad[p][kBindingRowActions[a]];
                const std::string name = p == 0 ? keyName(code) : gamepadLabel(code);
                centred(batch, name.c_str(), kColumn + kColumnWidth * (p + 0.5f), y + 2.f, 14.f, selected && p == player_ ? kWhite : kPale);
            }
        }
        const float backY = kFirstRow + fnd::input::ActionCount * kPitch + 2.f;
        const bool backSelected = row_ == kKeyConfigBackRow;
        if (backSelected) batch.pushSolid({116, backY - 4.f, 568, 28}, kHighlight);
        centred(batch, say({"終了", "BACK"}), 400, backY, 17.f, backSelected ? kWhite : kPale);
        help(batch, bindingCaptureActive() ? say({"キーまたはボタンを押してください ／ ESC で中止", "Press a key or pad button. Esc cancels."})
                                           : say({"決定で変更 ／ ←→ でプレイヤー選択", "Confirm to rebind. Left and right pick the player."}));
    }
    static std::string keyName(int code) {
        if (code < 0) return "--";
        const char* name = SDL_GetScancodeName(static_cast<SDL_Scancode>(code));
        return name && *name ? name : "#" + std::to_string(code);
    }
    static std::string gamepadLabel(int code) {
        switch (code) {
        case SDL_GAMEPAD_BUTTON_SOUTH: return "A";
        case SDL_GAMEPAD_BUTTON_EAST: return "B";
        case SDL_GAMEPAD_BUTTON_WEST: return "X";
        case SDL_GAMEPAD_BUTTON_NORTH: return "Y";
        case SDL_GAMEPAD_BUTTON_BACK: return "BACK";
        case SDL_GAMEPAD_BUTTON_GUIDE: return "GUID";
        case SDL_GAMEPAD_BUTTON_START: return "STRT";
        case SDL_GAMEPAD_BUTTON_LEFT_STICK: return "L3";
        case SDL_GAMEPAD_BUTTON_RIGHT_STICK: return "R3";
        case SDL_GAMEPAD_BUTTON_LEFT_SHOULDER: return "LB";
        case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER: return "RB";
        case SDL_GAMEPAD_BUTTON_DPAD_UP: return "UP";
        case SDL_GAMEPAD_BUTTON_DPAD_DOWN: return "DOWN";
        case SDL_GAMEPAD_BUTTON_DPAD_LEFT: return "LEFT";
        case SDL_GAMEPAD_BUTTON_DPAD_RIGHT: return "RGHT";
        default: return code < 0 ? "--" : "#" + std::to_string(code);
        }
    }
    mutable CaptionText face_;
    bool keys_; int sound_=-1; int row_=0,player_=0; int background_=-1;
};
std::unique_ptr<Screen> create(SpriteRenderer& b,bool keys,std::string& error) {
    auto result=std::make_unique<ConfigScreen>(b,keys,error); if(!result->loaded()) return {}; return result;
}
}
std::unique_ptr<Screen> makeOptionsScreen(SpriteRenderer& b,std::string& e) { return create(b,false,e); }
std::unique_ptr<Screen> makeKeyConfigScreen(SpriteRenderer& b,std::string& e) { return create(b,true,e); }
}
