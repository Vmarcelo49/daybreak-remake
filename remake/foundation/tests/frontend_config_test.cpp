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

    // --- persistence seam (issue #19): document <-> live settings ---
    settings::UserSettings document;
    document.volumes = {10,20,30,40};
    document.fullscreen = true;
    document.keyboard[fnd::input::Jump] = 7;
    document.gamepad[3][fnd::input::Guard] = 9;
    ui::applyUserSettings(settings, document);
    CHECK(settings.volumes.master==10 && settings.volumes.music==20);
    CHECK(settings.volumes.voice==30 && settings.volumes.sfx==40);
    CHECK(settings.fullscreen);
    CHECK(settings.keyboard[fnd::input::Jump]==7);
    CHECK(settings.gamepad[3][fnd::input::Guard]==9);
    // The stored resolution is the user's CHOICE, never the window's current pixel size:
    // a startup pixel-size event or a drag moves the index without changing the file.
    settings.resolutions = {{0,0},{1280,720},{1920,1080}};
    settings.resolutionChoice = {1280,720};
    settings.resolutionIndex = 0;   // the window is at the desktop size right now
    const settings::UserSettings saved = ui::toUserSettings(settings);
    CHECK(saved.resolution.width==1280 && saved.resolution.height==720);
    settings.resolutionChoice = {0,0};
    CHECK(ui::toUserSettings(settings).resolution == settings::DisplaySize{});
    // Cycling the row IS a choice, and it is the only thing that moves the preference.
    settings.resolutionChoice = {0,0};
    settings.resolutionIndex = 0;
    settings.resolutionAvailable = true;
    settings.applyResolution = [](const ui::DisplayResolution&) { return true; };
    CHECK(settings.cycleResolution(1) && settings.resolutionIndex == 1);
    CHECK(ui::toUserSettings(settings).resolution.width == 1280);
    settings.resolutionIndex = 3;   // an OS resize must not become the preference
    CHECK(ui::toUserSettings(settings).resolution.width == 1280);
    // A restart: the file's bytes come back into a fresh live state.
    std::string error; settings::LoadReport report;
    settings::UserSettings reloaded;
    CHECK(settings::parse(settings::serialize(saved), reloaded, error, report));
    CHECK(reloaded == saved);
    // Issue #10's schema migration reaches the live state: a v1 document (13-entry rows,
    // with the removed heavy binding) loads, drops that entry, and every other binding
    // lands on the right action.
    {
        std::string v1 = "version = 1\n[bindings]\nkeyboard = ";
        for (int a = 0; a < 13; ++a) v1 += (a ? "," : "") + std::to_string(200 + a);
        v1 += "\n";
        settings::UserSettings migrated;
        std::string migrationError;
        settings::LoadReport migrationReport;
        CHECK(settings::parse(v1, migrated, migrationError, migrationReport));
        CHECK(migrationReport.warnings == 1);
        ui::FrontendSettings fromV1;
        ui::applyUserSettings(fromV1, migrated);
        CHECK(fromV1.keyboard[fnd::input::Up] == 200);
        CHECK(fromV1.keyboard[fnd::input::AttackA] == 204);
        CHECK(fromV1.keyboard[fnd::input::Guard] == 206);   // the heavy entry was dropped
        CHECK(fromV1.keyboard[fnd::input::Pause] == 212);
        CHECK(ui::kBindingRowActions[4] == fnd::input::Jump);
        CHECK(sizeof(ui::kBindingRowActions) / sizeof(ui::kBindingRowActions[0]) ==
              (size_t)fnd::input::ActionCount);
        bool seen[fnd::input::ActionCount] = {};
        for (auto action : ui::kBindingRowActions) {
            CHECK(!seen[action]);
            seen[action] = true;
        }
        for (int a = 0; a < fnd::input::ActionCount; ++a) CHECK(seen[a]);
    }
    ui::FrontendSettings fresh;
    fresh.resolutions = settings.resolutions;
    fresh.resolutionIndex = 2;   // what the new display happened to default to
    ui::applyUserSettings(fresh, reloaded);
    CHECK(fresh.volumes.master==10 && fresh.volumes.sfx==40);
    CHECK(fresh.keyboard[fnd::input::Jump]==7 && fresh.gamepad[3][fnd::input::Guard]==9);
    CHECK(fresh.fullscreen);
    return 0;
}
