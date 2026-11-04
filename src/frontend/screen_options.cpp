#include "frontend/screen_options.h"
#include "frontend/frontend_settings.h"
#include "frontend/menu_panel.h"
#include "frontend/title_backdrop.h"
#include "input/input_backend.h"
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
constexpr int kKeyConfigBackRow = fnd::input::ActionCount;

enum class OptionRow { Toon, Shadow, Fullscreen, Resolution, Language, TitleBackdrop, Master, Music, Voice, Sfx, Back, Count };
constexpr int kOptionRowCount = (int)OptionRow::Count;
// The SOUND block and BACK sit 34 and 6 lower than before the title-backdrop row existed
// (issue #98): the extra GRAPHICS row does not fit above the heading otherwise.
constexpr float kOptionY[kOptionRowCount] = {130, 164, 198, 232, 266, 300, 368, 402, 436, 470, 500};
constexpr float kSoundHeadingY = 342.f;
constexpr Words kOptionNames[kOptionRowCount] = {
    {"トゥーンレンダリング", "TOON SHADING"}, {"影の表示", "SHADOWS"}, {"画面モード", "SCREEN MODE"}, {"解像度", "RESOLUTION"}, {"言語", "LANGUAGE"},
    {"タイトル背景", "TITLE BACKGROUND"},
    {"全体の音量", "MASTER"}, {"音楽の音量", "MUSIC"}, {"音声の音量", "VOICE"}, {"効果音の音量", "EFFECTS"}, {"終了", "BACK"},
};
constexpr Words kOptionHelp[kOptionRowCount] = {
    {"←→ でトゥーンレンダリングを切り替えます", "Left and right switch the cartoon outlines and shading."},
    {"←→ で影の表示を切り替えます", "Left and right switch the character shadows."},
    {"←→ で画面モードを切り替えます", "Left and right switch the window and fullscreen."},
    {"←→ で解像度を変更します", "Left and right change the resolution."},
    {"←→ で言語を切り替えます", "Left and right change the language of the menus and the HUD."},
    {"←→ でタイトル画面の背景を切り替えます", "Left and right switch the title background between the original art and a live stage."},
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

class ConfigScreen : public PanelScreen {
public:
    ConfigScreen(SpriteRenderer& batch, bool keys, std::string& error) : keys_(keys) {
        const bool ok = keys ? uploadBackground(batch, "data/keyconfig/0000", {{240, 8, 320, 56}, {120, 92, 560, 420}}, background_, error)
                             : uploadBackground(batch, "data/config/0001", {{240, 8, 320, 56}, {340, 250, 270, 140}}, background_, error);
        if (ok) loadFace(batch, error);
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
            if (in.left) column_ = (column_ + kBindingColumns - 1) % kBindingColumns;
            if (in.right) column_ = (column_ + 1) % kBindingColumns;
            if (in.confirm) armBindingCapture(column_,kBindingRowActions[row_]);
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
            case OptionRow::Language: {
                // The two languages this build ships. A failed load keeps the current one.
                const std::string next = sheetLanguage().empty() ? "en" : "";
                std::string failure;
                if (setSheetLanguage(next, failure)) settings.language = next.empty() ? "ja" : next;
                else std::fprintf(stderr, "[options] %s\n", failure.c_str());
                break;
            }
            case OptionRow::TitleBackdrop:
                // One step per press, like the resolution row: the title is constructed
                // again the next time it is entered, and that is where the new stage loads.
                if (in.left || in.right)
                    settings.titleBackdrop = cycleTitleBackdrop(settings.titleBackdrop, in.right ? 1 : -1);
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
    void slider(SpriteRenderer& batch, int value, float y, bool selected) const {
        constexpr float kLeft = 410.f, kWidth = 200.f;
        batch.pushSolid({kLeft, y + 8.f, kWidth, 8.f}, kTrack);
        batch.pushSolid({kLeft, y + 8.f, kWidth * value / 100.f, 8.f}, selected ? kGold : kPale);
        char percent[16];
        std::snprintf(percent, sizeof percent, "%d%%", value);
        label(batch, percent, kLeft + kWidth + 16.f, y, 20.f, selected ? kWhite : kPale);
    }
    void drawOptions(SpriteRenderer& batch) const {
        const auto& settings = frontendSettings();
        frame(batch, {"環境設定", "OPTIONS"}, 40, 540);
        label(batch, say({"映像", "GRAPHICS"}), 130, 104, 16.f, kGold);
        label(batch, say({"音量", "SOUND"}), 130, kSoundHeadingY, 16.f, kGold);
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
        choice(batch, sheetLanguage().empty() ? "日本語" : "ENGLISH", kOptionY[(int)OptionRow::Language], isRow(OptionRow::Language));
        choice(batch, titleBackdropLabel(settings.titleBackdrop).c_str(), kOptionY[(int)OptionRow::TitleBackdrop],
               isRow(OptionRow::TitleBackdrop));
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
        // The keyboard is one device with one set of keys, wherever it sits; the pad
        // bindings belong to the player slot (input/input_backend.h).
        constexpr float kFirstRow = 104.f, kPitch = 31.f, kColumn = 320.f, kColumnWidth = 72.f;
        const char* const headings[kBindingColumns] = {say({"キー", "KEYS"}), "1P", "2P", "3P", "4P"};
        int padTypes[4];
        for (int p = 0; p < 4; ++p) padTypes[p] = settings.padTypeForSlot ? settings.padTypeForSlot(p) : -1;
        for (int c = 0; c < kBindingColumns; ++c)
            centred(batch, headings[c], kColumn + kColumnWidth * (c + 0.5f), 78, 18.f, column_ == c ? kGold : kPale);
        for (int a = 0; a < fnd::input::ActionCount; ++a) {
            const float y = kFirstRow + a * kPitch;
            const bool selected = a == row_;
            if (selected) {
                batch.pushSolid({116, y - 4.f, 568, 28}, {1.f, 1.f, 1.f, 0.08f});
                batch.pushSolid({kColumn + column_ * kColumnWidth, y - 4.f, kColumnWidth, 28}, kHighlight);
            }
            label(batch, say(kBindingNames[a]), 134, y, 17.f, selected ? kWhite : kPale);
            for (int c = 0; c < kBindingColumns; ++c) {
                const int action = kBindingRowActions[a];
                const std::string name = c == 0 ? keyName(settings.keyboard[action])
                                                : fnd::input::padInputLabel(settings.gamepad[c - 1][action], padTypes[c - 1]);
                centred(batch, name.c_str(), kColumn + kColumnWidth * (c + 0.5f), y + 2.f, 13.f,
                        selected && c == column_ ? kWhite : kPale);
            }
        }
        const float backY = kFirstRow + fnd::input::ActionCount * kPitch + 2.f;
        const bool backSelected = row_ == kKeyConfigBackRow;
        if (backSelected) batch.pushSolid({116, backY - 4.f, 568, 28}, kHighlight);
        centred(batch, say({"終了", "BACK"}), 400, backY, 17.f, backSelected ? kWhite : kPale);
        const char* capturing = bindingCaptureForKeyboard()
            ? say({"キーを押してください ／ ESC で中止", "Press a key. Esc cancels."})
            : say({"パッドのボタンを押してください ／ ESC で中止", "Press a pad button or trigger. Esc cancels."});
        help(batch, bindingCaptureActive() ? capturing
                                           : say({"決定で変更 ／ ←→ で列を選択", "Confirm to rebind. Left and right pick the column."}));
    }
    static std::string keyName(int code) {
        if (code < 0) return "--";
        const char* name = SDL_GetScancodeName(static_cast<SDL_Scancode>(code));
        return name && *name ? name : "#" + std::to_string(code);
    }
    bool keys_; int sound_=-1; int row_=0,column_=0; 
};
std::unique_ptr<Screen> create(SpriteRenderer& b,bool keys,std::string& error) {
    auto result=std::make_unique<ConfigScreen>(b,keys,error); if(!result->loaded()) return {}; return result;
}
}
std::unique_ptr<Screen> makeOptionsScreen(SpriteRenderer& b,std::string& e) { return create(b,false,e); }
std::unique_ptr<Screen> makeKeyConfigScreen(SpriteRenderer& b,std::string& e) { return create(b,true,e); }
}
