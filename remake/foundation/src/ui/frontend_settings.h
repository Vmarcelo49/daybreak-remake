#pragma once
#include <array>
#include <functional>
#include <vector>
#include "audio/audio.h"
#include "input/input.h"
namespace ui {
struct DisplayResolution {
    int width = 0, height = 0;
    bool operator==(const DisplayResolution& other) const { return width == other.width && height == other.height; }
};
struct FrontendSettings {
    FrontendSettings();
    fnd::audio::Volumes volumes;
    std::array<int, fnd::input::ActionCount> keyboard;
    std::array<std::array<int, fnd::input::ActionCount>, 4> gamepad;
    bool fullscreen = false;
    bool resolutionAvailable = false;
    std::vector<DisplayResolution> resolutions{{0, 0}};
    int resolutionIndex = 0;
    DisplayResolution displayResolution;
    DisplayResolution currentResolution;
    bool cycleResolution(int direction);
    std::function<void(const fnd::audio::Volumes&)> applyVolumes;
    std::function<void(bool)> applyFullscreen;
    std::function<bool(const DisplayResolution&)> applyResolution;
    std::function<void()> applyBindings;
};
FrontendSettings& frontendSettings();
// The SDL event pump supplies physical input while the binding screen is armed.
void submitBindingInput(bool keyboard, int player, int code);
bool bindingCaptureActive();
void armBindingCapture(int player, int action);
void cancelBindingCapture();
}
