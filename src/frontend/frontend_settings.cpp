#include "frontend/frontend_settings.h"
#include "input/input_sdl3.h"
namespace ui {
namespace { int captureColumn = -1, captureAction = -1; }
FrontendSettings::FrontendSettings() {
    for (int a = 0; a < fnd::input::ActionCount; ++a) keyboard[a] = fnd::input::sdl3::kP1ScancodeByAction[a];
    for (auto& pad : gamepad) for (int a = 0; a < fnd::input::ActionCount; ++a) pad[a] = fnd::input::sdl3::kPadButtonByAction[a];
}
bool FrontendSettings::cycleResolution(int direction) {
    if (!resolutionAvailable || !applyResolution || resolutions.empty() || direction == 0) return false;
    const int count = static_cast<int>(resolutions.size());
    for (int attempt = 1; attempt < count; ++attempt) {
        const int candidate = (resolutionIndex + (direction > 0 ? attempt : -attempt) + count) % count;
        if (applyResolution(resolutions[candidate])) {
            resolutionIndex = candidate;
            resolutionChoice = resolutions[candidate];
            return true;
        }
    }
    return false;
}
FrontendSettings& frontendSettings() { static FrontendSettings settings; return settings; }

void applyUserSettings(FrontendSettings& settings, const settings::UserSettings& document) {
    settings.volumes = document.volumes;
    settings.keyboard = document.keyboard;
    settings.gamepad = document.gamepad;
    settings.fullscreen = document.fullscreen;
    settings.toonRendering = document.toonRendering;
    settings.installDir = document.installDir;
    settings.language = document.language;
    settings.playerName = document.playerName;
    settings.netPort = document.netPort;
    settings.netInputDelay = document.netInputDelay;
    settings.netLastHost = document.netLastHost;
    settings.netServer = document.netServer;
    settings.shadowRendering = document.shadowRendering;
    settings.titleBackdrop = document.titleBackdrop;
}

settings::UserSettings toUserSettings(const FrontendSettings& settings) {
    settings::UserSettings document;
    document.volumes = settings.volumes;
    document.keyboard = settings.keyboard;
    document.gamepad = settings.gamepad;
    document.fullscreen = settings.fullscreen;
    document.toonRendering = settings.toonRendering;
    document.shadowRendering = settings.shadowRendering;
    document.titleBackdrop = settings.titleBackdrop;
    document.resolution = {settings.resolutionChoice.width, settings.resolutionChoice.height};
    document.installDir = settings.installDir;
    document.language = settings.language;
    document.playerName = settings.playerName;
    document.netPort = settings.netPort;
    document.netInputDelay = settings.netInputDelay;
    document.netLastHost = settings.netLastHost;
    document.netServer = settings.netServer;
    return document;
}
bool bindingCaptureActive() { return captureColumn >= 0; }
bool bindingCaptureForKeyboard() { return captureColumn == 0; }
void armBindingCapture(int column, int action) {
    if (column >= 0 && column < kBindingColumns && action >= 0 && action < fnd::input::ActionCount) {
        captureColumn = column; captureAction = action;
    }
}
void cancelBindingCapture() { captureColumn = captureAction = -1; }
void submitBindingInput(bool keyboard, int padSlot, int code) {
    if (!bindingCaptureActive() || code < 0) return;
    if (code > (keyboard ? settings::kMaxScancode : settings::kMaxPadButton)) return;
    // The keyboard binds only its own column. A pad binds the player column it was armed
    // for when it is that player's pad; when that player has no pad, any pad may set it up,
    // since slots are taken by the first press and a player rebinding before joining has
    // no other way in.
    const int slot = captureColumn - 1;
    if (keyboard != (slot < 0)) return;
    if (!keyboard && padSlot != slot) {
        const auto& typeOf = frontendSettings().padTypeForSlot;
        if (typeOf && typeOf(slot) >= 0) return;
    }
    auto& target = keyboard ? frontendSettings().keyboard : frontendSettings().gamepad[slot];
    // One physical button has one action; displace its previous assignment.
    for (int& binding : target) if (binding == code) binding = -1;
    target[captureAction] = code;
    if (frontendSettings().applyBindings) frontendSettings().applyBindings();
    cancelBindingCapture();
}
}
