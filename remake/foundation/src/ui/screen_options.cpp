#include "ui/screen_options.h"
#include "ui/frontend_settings.h"
#include "ui/hud_atlas.h"
#include "ui/caption.h"
#include <algorithm>
#include <cstdio>
#include <SDL3/SDL.h>
namespace ui {
namespace {
class ConfigScreen : public Screen {
public:
    ConfigScreen(SpriteRenderer& batch, bool keys, std::string& error) : keys_(keys) {
        char path[64];
        for (int i = 0; i < 3; ++i) {
            std::snprintf(path, sizeof(path), "data/%s/%04d", keys ? "keyconfig" : "config", (keys ? (i == 2 ? 4 : i) : i + 1));
            if (!uploadCnvSheet(batch, path, sheets_[i], error)) return;
        }
        captions_.load(batch,14.f,error);
    }
    ~ConfigScreen() override { if (keys_) cancelBindingCapture(); }
    bool loaded() const { return captions_.atlasTexture() >= 0; }
    int takeSound() override { const int cue=sound_; sound_=-1; return cue; }
    const char* name() const override { return keys_ ? "keyconfig" : "options"; }
    ScreenId update(const ScreenInput& in) override {
        const auto stay = keys_ ? ScreenId::KeyConfig : ScreenId::Options;
        if(in.cancel) sound_=1;
        else if(in.confirm) sound_=0;
        else if(in.up||in.down||in.left||in.right) sound_=2;
        if (keys_ && bindingCaptureActive()) { if (in.cancel) cancelBindingCapture(); return stay; }
        if (in.cancel) return ScreenId::Title;
        const int rows = keys_ ? fnd::input::ActionCount + 1 : 10;
        if (in.up) row_ = (row_ + rows - 1) % rows;
        else if (in.down) row_ = (row_ + 1) % rows;
        if (in.confirm && row_ == rows - 1) return ScreenId::Title;
        auto& settings = frontendSettings();
        if (keys_) {
            if (in.left) player_ = (player_ + 3) % 4;
            if (in.right) player_ = (player_ + 1) % 4;
            if (in.confirm) armBindingCapture(player_,kBindingRowActions[row_]);
        } else if (row_ == 0 && (in.left || in.right || in.confirm)) {
            // Row 0 is the toon-rendering toggle (issue #21, DAT_006cfcec): left/right
            // flips it like the other option rows. The renderer's appearance follows
            // frontendSettings() every frame, so the change is in the next drawn frame —
            // no restart, and nothing re-uploads.
            settings.toonRendering = !settings.toonRendering;
        } else if (row_ == 1 && (in.left || in.right || in.confirm)) {
            // Row 1 is the shadow row (issue #21 row 1, 影の表示 / DAT_006cfcea): the same
            // live flip as row 0 — main.cpp's per-frame sync pushes it into the renderer's
            // appearance, so the next drawn frame has it and nothing re-uploads.
            settings.shadowRendering = !settings.shadowRendering;
        } else if (row_ == 3 && (in.left || in.right || in.confirm)) {
            settings.fullscreen = !settings.fullscreen;
            if (settings.applyFullscreen) settings.applyFullscreen(settings.fullscreen);
        } else if (row_ == 8 && (in.left || in.right || in.confirm)) {
            settings.cycleResolution(in.left ? -1 : 1);
        } else if (row_ >= 4 && row_ <= 7 && (in.left || in.right)) {
            int* sliders[] = {&settings.volumes.master,&settings.volumes.music,&settings.volumes.voice,&settings.volumes.sfx};
            *sliders[row_-4] = std::clamp(*sliders[row_-4] + (in.right ? 5 : -5),0,100);
            if (settings.applyVolumes) settings.applyVolumes(settings.volumes);
        }
        return stay;
    }
    void draw(SpriteRenderer& batch) const override {
        batch.pushSprite(sheets_[0],{0,0,800,600},0,0,0,0);
        const auto& settings = frontendSettings();
        if (!keys_) {
            // FUN_00403470: label, state columns, cursor and volume knobs.
            constexpr float ys[] = {128,160,192,224,256,288,320,352,384,416};
            constexpr int labelRows[] = {0,2,4,8,10,12,10,12,-1,14};
            for (int i=0;i<10;++i) {
                if (i == 8) {
                    captions_.draw(batch,"RESOLUTION",176,ys[i]+8,1.f,
                        row_ == i ? UiColor{1.f,0.8f,0.3f,1.f} : UiColor{},1.f);
                } else batch.pushSprite(sheets_[1],{i==6||i==7 ? 192.f : 0.f,(float)(labelRows[i]+(i==row_))*32,192,32},0,0,176,ys[i]);
            }
            char resolution[64];
            if (!settings.resolutionAvailable) {
#if defined(__EMSCRIPTEN__)
                std::snprintf(resolution,sizeof(resolution),"BROWSER SIZE");
#else
                std::snprintf(resolution,sizeof(resolution),"FIXED CAPTURE");
#endif
            } else if (settings.resolutionIndex == 0)
                std::snprintf(resolution,sizeof(resolution),"DESKTOP %d x %d",settings.displayResolution.width,settings.displayResolution.height);
            else {
                const auto size = settings.resolutions[settings.resolutionIndex];
                std::snprintf(resolution,sizeof(resolution),"%d x %d",size.width,size.height);
            }
            text(batch,resolution,368,ys[8]+8,2);
            batch.pushSprite(sheets_[1],{256,448,32,32},0,0,144,ys[row_]);
            // Row 0 draws its real state in the original's own cells (FUN_00403470:25-26):
            // the cell row is the toggle value at x=368 and its complement at x=464, so the
            // pair always shows one bold and one plain option and inverts when it flips.
            // The sheet's even cell row is the bold art (有効 at 368 with the toggle off),
            // which is the original's own choice of which of the two reads bold.
            batch.pushSprite(sheets_[1],{192,settings.toonRendering ? 32.f : 0.f,96,32},0,0,368,ys[0]);
            batch.pushSprite(sheets_[1],{288,settings.toonRendering ? 0.f : 32.f,128,32},0,0,464,ys[0]);
            // Row 1 (影の表示) is the same pair one strip pair further down the sheet:
            // FUN_00403470:27-28 gives the row the cells at index 2 and 3, and the sheet's
            // 32px strips are the toon row's pair at v=0/32, the shadow row's at v=64/96
            // and the texture row's (普通/低) at v=128/160 — which is where the last two
            // strips sit in data/config/0002.cnv. Same u columns as row 0: the sheet keeps
            // the bold value in the x=192 column and its complement at x=288.
            batch.pushSprite(sheets_[1],{192,settings.shadowRendering ? 96.f : 64.f,96,32},0,0,368,ys[1]);
            batch.pushSprite(sheets_[1],{288,settings.shadowRendering ? 64.f : 96.f,128,32},0,0,464,ys[1]);
            // Row 2 keeps the generic message: texture resolution is still an
            // unimplemented slice of issue #21.
            text(batch,"UNAVAILABLE",550,ys[2],1.5f);
            batch.pushSprite(sheets_[1],{192,settings.fullscreen ? 256.f : 288.f,96,32},0,0,368,224);
            batch.pushSprite(sheets_[1],{288,settings.fullscreen ? 288.f : 256.f,128,32},0,0,464,224);
            const int values[] = {settings.volumes.master,settings.volumes.music,settings.volumes.voice,settings.volumes.sfx};
            for(int i=0;i<4;++i) batch.pushSprite(sheets_[1],{192,448,96,32},0,0,368+values[i]*1.6f,ys[i+4]);
            if (row_ == 0) text(batch,"LEFT/RIGHT: TOON SHADING ON/OFF",176,550,2);
            else if (row_ == 1) text(batch,"LEFT/RIGHT: CHARACTER SHADOWS ON/OFF",160,550,2);
            else if (row_ < 3) text(batch,"SETTING NOT AVAILABLE",208,550,2);
            else if (row_ == 8) text(batch,settings.resolutionAvailable ? "LEFT/RIGHT: CHANGE RESOLUTION" : "SIZE FOLLOWS THE VIEWPORT",144,550,2);
            else batch.pushSprite(sheets_[2],{0,(row_ == 9 ? 9 : row_ + 1)*48.f,512,48},0,0,144,528);
        } else {
            // FUN_00404a50: retain the baked labels and their 32px row pitch.
            for (int a = 0; a < fnd::input::ActionCount; ++a) {
                const float y = 128 + a * 32.f;
                if (a == row_) batch.pushSolid({332 + player_ * 64.f,y,60,32},{0.15f,0.3f,0.6f,0.7f});
                for (int p = 0; p < 4; ++p) {
                    const int code = p == 0 ? settings.keyboard[kBindingRowActions[a]] : settings.gamepad[p][kBindingRowActions[a]];
                    const float x = 336 + p * 64.f;
                    if (p == 0 && code >= 0) {
                        const int cell = keyboardCell(code);
                        if (cell >= 0) batch.pushSprite(sheets_[1],{(cell % 16)*32.f,(cell / 16)*32.f,32,32},0,0,x,y);
                        else text(batch,SDL_GetScancodeName(static_cast<SDL_Scancode>(code)),x,y+8,1);
                    } else {
                        const std::string label = gamepadLabel(code);
                        text(batch,label.c_str(),x,y+8,2);
                    }
                }
            }
            for (int p = 0; p < 4; ++p)
                batch.pushSprite(sheets_[2],{160 + p*64.f,player_ == p && row_ != 13 ? 448.f : 416.f,64,32},0,0,320+p*64.f,96);
            batch.pushSprite(sheets_[2],{0,row_ == 13 ? 448.f : 416.f,96,32},0,0,160,96);
            text(batch,bindingCaptureActive()?"PRESS A KEY / PAD BUTTON; ESC CANCELS":"CONFIRM: REBIND   LEFT/RIGHT: PLAYER   CANCEL: BACK",112,550,2);

        }
    }
private:
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
    static int keyboardCell(int code) {
        // FUN_00404a50 indexes this sheet by DirectInput scan code; SDL codes differ.
        constexpr int letters[] = {0x1e,0x30,0x2e,0x20,0x12,0x21,0x22,0x23,0x17,0x24,0x25,0x26,0x32,0x31,0x18,0x19,0x10,0x13,0x1f,0x14,0x16,0x2f,0x11,0x2d,0x15,0x2c};
        if (code >= SDL_SCANCODE_A && code <= SDL_SCANCODE_Z) return letters[code - SDL_SCANCODE_A];
        if (code >= SDL_SCANCODE_1 && code <= SDL_SCANCODE_9) return 2 + code - SDL_SCANCODE_1;
        switch (code) {
        case SDL_SCANCODE_0: return 0x0b;
        case SDL_SCANCODE_UP: return 0xc8;
        case SDL_SCANCODE_DOWN: return 0xd0;
        case SDL_SCANCODE_LEFT: return 0xcb;
        case SDL_SCANCODE_RIGHT: return 0xcd;
        case SDL_SCANCODE_RETURN: return 0x1c;
        case SDL_SCANCODE_ESCAPE: return 0x01;
        case SDL_SCANCODE_SPACE: return 0x39;
        default: return -1;
        }
    }
    void text(SpriteRenderer& batch,const char* value,float x,float y,float scale) const {
        captions_.draw(batch,value,x,y,scale*.5f,{},1.f);
    }
    mutable CaptionText captions_;
    bool keys_; int sound_=-1; int row_=0,player_=0; int sheets_[3]={-1,-1,-1};
};
std::unique_ptr<Screen> create(SpriteRenderer& b,bool keys,std::string& error) {
    auto result=std::make_unique<ConfigScreen>(b,keys,error); if(!result->loaded()) return {}; return result;
}
}
std::unique_ptr<Screen> makeOptionsScreen(SpriteRenderer& b,std::string& e) { return create(b,false,e); }
std::unique_ptr<Screen> makeKeyConfigScreen(SpriteRenderer& b,std::string& e) { return create(b,true,e); }
}
