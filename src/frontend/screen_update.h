#pragma once
// frontend/screen_update.h — the player-facing install screen (issue #100, step 4).
//
// The apply runs on this screen's own worker so no frame blocks: the screen draws the
// phase and the bytes the engine reports, and Back/Esc cancels until the commit point.
// Everything the screen needs is handed in; it never touches the network itself.
#include <atomic>
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "frontend/menu_panel.h"
#include "frontend/screen.h"
#include "update/updater.h"

namespace ui {

// The engine reports failure categories in its message; this is the one place that turns
// them into the plain-language reasons the screen shows.
enum class UpdateFailureReason {
    None,
    NoConnection,
    NoAnswer,
    DamagedDownload,
    NotSigned,
    NotWritable,
    FileInTheWay,
    NoSpace,
    Other,
};
UpdateFailureReason updateFailureReason(const std::string& error);
const char* updateFailureReasonText(UpdateFailureReason reason);

struct UpdateLaunch {
    std::string root;
    update::UpdateManifest manifest;
    std::string manifestUrl;
    update::Version currentVersion;
    // A capture/test-only mode: no worker, no network, a fixed phase for a screenshot.
    // Empty is a real attempt; otherwise downloading, verifying, installing, restarting
    // or failed.
    std::string preview;
};

// One update attempt. A failed attempt leaves the old version running and the screen on
// its failure panel until the player leaves.
class UpdateScreen : public PanelScreen {
public:
    UpdateScreen(SpriteRenderer& batch, const UpdateLaunch& launch, std::string& error);
    ~UpdateScreen() override;

    ScreenId update(const ScreenInput& in) override;
    void draw(SpriteRenderer& batch) const override;
    const char* name() const override { return "update"; }
    bool wantsRelaunch(std::string* launch, std::string* from) override;
    int takeSound() override { const int cue = sound_; sound_ = -1; return cue; }

    // Test seams: the state the screen is showing, without a device.
    bool failed() const { return failed_; }
    bool relaunchReady() const { return relaunchReady_; }
    UpdateFailureReason failure() const { return failure_; }
    int choice() const { return choice_; }

private:
    void drawProgress(SpriteRenderer& batch) const;
    void drawFailure(SpriteRenderer& batch) const;

    std::string notes_;
    std::string currentVersion_;
    std::thread worker_;
    std::atomic<bool> cancel_{false};
    std::atomic<bool> finished_{false};
    std::atomic<int> phase_{0};
    std::atomic<std::uint64_t> received_{0};
    std::atomic<std::uint64_t> total_{0};
    std::mutex mutex_;
    update::ApplyResult result_;
    bool failed_ = false;
    bool previewRestarting_ = false;
    UpdateFailureReason failure_ = UpdateFailureReason::None;
    bool relaunchReady_ = false;
    std::string launchPath_;
    int choice_ = 0;  // 0 = Back, 1 = Open release page
    int sound_ = -1;
};

std::unique_ptr<Screen> makeUpdateScreen(SpriteRenderer& batch, const UpdateLaunch& launch,
                                         std::string& error);

}  // namespace ui
