#include "frontend/frontend_settings.h"
#include "input/input_sdl3.h"
#include <SDL3/SDL_timer.h>
namespace ui {
namespace {
int captureColumn = -1, captureAction = -1;
// SDL_GetTicksNS() at arming. A pad's confirm is read from its polled state in the frame it
// is pressed, but its BUTTON_DOWN event is dispatched at the start of the next frame, after
// the screen has armed the capture: without this the confirm bound itself (issue #102).
uint64_t captureArmedAtNs = 0;
}
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
    settings.updateCheck = document.updateCheck;
    settings.updateSkipVersion = document.updateSkipVersion;
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
    document.updateCheck = settings.updateCheck;
    document.updateSkipVersion = settings.updateSkipVersion;
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
void armBindingCapture(int column, int action) {
    if (column >= 0 && column < kBindingColumns && action >= 0 && action < fnd::input::ActionCount) {
        captureColumn = column; captureAction = action;
        captureArmedAtNs = SDL_GetTicksNS();
    }
}
void cancelBindingCapture() { captureColumn = captureAction = -1; }
void submitBindingInput(bool keyboard, int padSlot, int code, uint64_t pressedAtNs) {
    if (!bindingCaptureActive() || code < 0) return;
    if (pressedAtNs != 0 && pressedAtNs < captureArmedAtNs) return;
    if (code > (keyboard ? settings::kMaxScancode : settings::kMaxPadButton)) return;
    // The device pressed says which set changes: a key binds the keys, a pad press binds a
    // pad's (issue #102 — a pad player rebinding from the keys column got nothing). A pad
    // column binds when the press comes from that player's pad, or from any pad when that
    // player has none yet; from the keys column a pad binds its own player.
    int slot = captureColumn - 1;
    if (!keyboard) {
        const auto& typeOf = frontendSettings().padTypeForSlot;
        if (slot < 0) slot = padSlot;
        else if (padSlot != slot && typeOf && typeOf(slot) >= 0) return;
        if (slot < 0) return;   // a pad with no player yet has no bindings to change
    }
    auto& target = keyboard ? frontendSettings().keyboard
                            : frontendSettings().gamepad[static_cast<size_t>(slot)];
    // One physical button has one action; displace its previous assignment.
    for (int& binding : target) if (binding == code) binding = -1;
    target[captureAction] = code;
    if (frontendSettings().applyBindings) frontendSettings().applyBindings();
    cancelBindingCapture();
}
}
