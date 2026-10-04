#include "ui/frontend_settings.h"
#include "ui/frontend_state.h"
#include "ui/soft_keyboard.h"
#include "ui/screen_options.h"
#include <cstdio>
#define CHECK(x) do { if(!(x)) { std::fprintf(stderr,"failure: %s\n",#x); return 1; } } while(0)
int main() {
    CHECK(ui::kFrontendBattleSlots[0] == 0 && ui::kFrontendBattleSlots[1] == 2);
    auto& settings=ui::frontendSettings(); int changes=0; settings.applyBindings=[&]{++changes;};
    ui::armBindingCapture(0,fnd::input::Jump);
    ui::submitBindingInput(true,0,512); CHECK(ui::bindingCaptureActive());
    ui::submitBindingInput(true,4,6); CHECK(ui::bindingCaptureActive());
    ui::submitBindingInput(true,0,6); CHECK(!ui::bindingCaptureActive());
    CHECK(settings.keyboard[fnd::input::Jump]==6); CHECK(settings.keyboard[fnd::input::Shoot]==-1); CHECK(changes==1);
    ui::armBindingCapture(2,fnd::input::Jump); ui::submitBindingInput(false,1,3); CHECK(ui::bindingCaptureActive());
    ui::submitBindingInput(false,2,3); CHECK(settings.gamepad[2][fnd::input::Jump]==3); CHECK(changes==2);
    bool rowSeen[fnd::input::ActionCount] = {};
    for (auto action : ui::kBindingRowActions) {
        CHECK(!rowSeen[action]);
        rowSeen[action] = true;
    }
    CHECK(ui::kBindingRowActions[4] == fnd::input::Jump);
    CHECK(ui::kBindingRowActions[5] == fnd::input::AttackA);
    CHECK(ui::kBindingRowActions[7] == fnd::input::LockSwitch);
    ui::FrontendSettings display;
    display.resolutions = {{0,0},{800,600},{1920,1080},{3440,1440}};
    display.resolutionIndex = 1;
    int resizeCalls = 0;
    display.applyResolution = [&](const ui::DisplayResolution& size) {
        ++resizeCalls;
        return size.width != 1920;
    };
    CHECK(!display.cycleResolution(1) && resizeCalls == 0);
    display.resolutionAvailable = true;
    CHECK(display.cycleResolution(1) && display.resolutionIndex == 3 && resizeCalls == 2);
    CHECK(display.cycleResolution(1) && display.resolutionIndex == 0);
    CHECK(display.cycleResolution(-1) && display.resolutionIndex == 3);
    display.applyResolution = [&](const ui::DisplayResolution&) { ++resizeCalls; return false; };
    CHECK(!display.cycleResolution(1) && display.resolutionIndex == 3);
    display.resolutions = {{0,0}}; display.resolutionIndex = 0;
    CHECK(!display.cycleResolution(1));
    CHECK(!display.cycleResolution(0));
    ui::SoftKeyboard keyboard; ui::PlayerName name; keyboard.begin(name);
    ui::ScreenInput confirm; confirm.confirm=true;
    for(int i=0;i<10;++i) keyboard.update(confirm); CHECK(keyboard.value().length==8);
    ui::ScreenInput up; up.up=true; keyboard.update(up); CHECK(keyboard.row()==16);
    ui::ScreenInput right; right.right=true; keyboard.update(right); keyboard.update(right);
    keyboard.update(confirm); CHECK(keyboard.value().length==7);
    keyboard.update(right); CHECK(keyboard.update(confirm)==ui::KeyboardResult::Cancelled);
    keyboard.update(right); CHECK(keyboard.update(confirm)==ui::KeyboardResult::Accepted);
    ui::ScreenInput cancel; cancel.cancel=true; CHECK(keyboard.update(cancel)==ui::KeyboardResult::Cancelled);
    ui::PlayerName stale;
    stale.length=1; stale.cells[0]=42; stale.pages[0]=1;
    keyboard.begin(stale);
    keyboard.update(up); keyboard.update(right); keyboard.update(right);
    keyboard.update(confirm);
    CHECK(keyboard.value().length==0 && keyboard.value().pages[0]==0);
    ui::ScreenInput left; left.left=true;
    keyboard.update(left); keyboard.update(confirm);
    CHECK(keyboard.value().length==1 && keyboard.value().pages[0]==0 && keyboard.value().cells[0]==0);
    return 0;
}
