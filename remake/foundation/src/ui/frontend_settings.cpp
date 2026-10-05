#include "ui/frontend_settings.h"
#include "input/input_sdl3.h"
namespace ui {
namespace { int capturePlayer = -1, captureAction = -1; }
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
}

settings::UserSettings toUserSettings(const FrontendSettings& settings) {
    settings::UserSettings document;
    document.volumes = settings.volumes;
    document.keyboard = settings.keyboard;
    document.gamepad = settings.gamepad;
    document.fullscreen = settings.fullscreen;
    document.toonRendering = settings.toonRendering;
    document.resolution = {settings.resolutionChoice.width, settings.resolutionChoice.height};
    return document;
}
bool bindingCaptureActive() { return capturePlayer >= 0; }
void armBindingCapture(int player, int action) {
    if (player >= 0 && player < 4 && action >= 0 && action < fnd::input::ActionCount) {
        capturePlayer = player; captureAction = action;
    }
}
void cancelBindingCapture() { capturePlayer = captureAction = -1; }
void submitBindingInput(bool keyboard, int player, int code) {
    if (!bindingCaptureActive() || player < 0 || player >= 4 || code < 0 || code >= (keyboard ? 512 : 26) || (keyboard ? capturePlayer != 0 : player != capturePlayer)) return;
    auto& target = keyboard ? frontendSettings().keyboard : frontendSettings().gamepad[player];
    // One physical button has one action; displace its previous assignment.
    for (int& binding : target) if (binding == code) binding = -1;
    target[captureAction] = code;
    if (frontendSettings().applyBindings) frontendSettings().applyBindings();
    cancelBindingCapture();
}
}
