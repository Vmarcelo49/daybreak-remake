#pragma once
#include <array>
#include <functional>
#include <vector>
#include "audio/audio.h"
#include "input/input.h"
#include "settings/user_settings.h"
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
    // The game folder a run opened (issue #36). NOT a UI field and never drawn: it rides
    // along here because the host rebuilds the persisted document from this live state
    // every frame (toUserSettings), and a field that does not come back would be erased by
    // the first save after a launch that remembered it. The host sets it when it opens a
    // folder; applyUserSettings() carries the loaded value in.
    std::string installDir;
    std::string language;   // empty is the game's own Japanese
    std::string playerName = "PLAYER";
    int netPort = 37564, netInputDelay = 2;
    std::string netLastHost, netServer = settings::kDefaultServer;
    // The Options screen's toon-rendering row (issue #21). Live state: main syncs it into
    // the renderer's appearance every frame, so flipping the row needs no restart, and
    // toUserSettings() carries it into the persisted document.
    bool toonRendering = false;
    // The Options screen's shadow row (issue #21 row 1, 影の表示). Live state on the same
    // terms as the toon row above.
    bool shadowRendering = false;
    // The Options screen's title-backdrop row (issue #98): which stage, if any, is drawn
    // live behind the title menu. The default is the composed shrine by day; empty is the
    // original's static art. Live state on the same terms as the two rows above — the title
    // is rebuilt when it is next constructed, so a flip takes effect on returning to it,
    // and toUserSettings() persists it.
    std::string titleBackdrop = "stage03";
    // The user's selection from the Options resolution row; {0,0} is desktop. This is
    // what gets persisted, and it changes ONLY when the row is cycled — the window's
    // actual pixel size lives in currentResolution/resolutionIndex, which the OS changes
    // on its own (a startup pixel-size event, a drag, a fullscreen transition). Storing
    // the index instead would let a launch overwrite "desktop" with the current size.
    DisplayResolution resolutionChoice;
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
    // The SDL_GamepadType of the pad in a player slot, -1 when the slot has none: the
    // Controls screen names buttons after the pad's family and lets any pad rebind a slot
    // that has none (issue #102).
    std::function<int(int)> padTypeForSlot;
};
FrontendSettings& frontendSettings();

// --- persistence seam (issue #19) --------------------------------------------------
// The document owns what is written to disk; these two copy the parts of it that are
// plain live state. The display preference is deliberately NOT part of applyUserSettings:
// turning a stored pixel size into a window size needs the current display's resolution
// list, which only exists after the frontend has built it, so the host applies that half
// (settings::chooseResolutionIndex + applyResolution/applyFullscreen).
void applyUserSettings(FrontendSettings& settings, const settings::UserSettings& document);
// The live state as a document. The stored resolution is `resolutionChoice` (the user's
// pick from the Options row, {0,0} for desktop), never the window's current pixel size.
// Pad identity is device state and stays with the host, which fills padGuid/padName in
// before saving.
settings::UserSettings toUserSettings(const FrontendSettings& settings);
// The Controls screen's columns: 0 is the keyboard, 1..4 the pad bindings of players 1..4.
inline constexpr int kBindingColumns = 5;
// The SDL event pump supplies physical input while the binding screen is armed. A pad press
// names the slot of the pad it came from, -1 for a pad that has no slot yet.
void submitBindingInput(bool keyboard, int padSlot, int code);
bool bindingCaptureActive();
bool bindingCaptureForKeyboard();
void armBindingCapture(int column, int action);
void cancelBindingCapture();
}
