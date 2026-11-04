#include "frontend/screen_update.h"

#include <SDL3/SDL.h>

#include <algorithm>
#include <cstdio>
#include <filesystem>

#include "frontend/menu_panel.h"
#include "ui/sheet_locale.h"

namespace ui {
namespace {

bool japanese() { return sheetLanguage().empty(); }

bool contains(const std::string& text, const char* needle) {
    return text.find(needle) != std::string::npos;
}

}  // namespace

UpdateFailureReason updateFailureReason(const std::string& error) {
    // Ordered most specific first: the engine's messages name the check that failed.
    if (contains(error, "no trusted release key") || contains(error, "untrusted")) {
        return UpdateFailureReason::NotSigned;
    }
    if (contains(error, "free space")) return UpdateFailureReason::NoSpace;
    if (contains(error, "sha256") || contains(error, "size the manifest") ||
        contains(error, "does not match the manifest")) {
        return UpdateFailureReason::DamagedDownload;
    }
    if (contains(error, "does not own") || contains(error, "refusing to overwrite") ||
        contains(error, "in the way")) {
        return UpdateFailureReason::FileInTheWay;
    }
    if (contains(error, "cannot create") || contains(error, "cannot write") ||
        contains(error, "cannot rename") || contains(error, "cannot remove") ||
        contains(error, "read-only") || contains(error, "Permission denied")) {
        return UpdateFailureReason::NotWritable;
    }
    if (contains(error, "HTTP 4") || contains(error, "HTTP 5") ||
        contains(error, "not found")) {
        return UpdateFailureReason::NoAnswer;
    }
    if (contains(error, "HTTP") || contains(error, "connect") || contains(error, "resolve") ||
        contains(error, "timed out") || contains(error, "network") ||
        contains(error, "plain HTTP")) {
        return UpdateFailureReason::NoConnection;
    }
    return UpdateFailureReason::Other;
}

const char* updateFailureReasonText(UpdateFailureReason reason) {
    switch (reason) {
        case UpdateFailureReason::NoConnection:
            return japanese() ? "接続できませんでした" : "No connection";
        case UpdateFailureReason::NoAnswer:
            return japanese() ? "GitHub が応答しませんでした" : "GitHub didn't answer";
        case UpdateFailureReason::DamagedDownload:
            return japanese() ? "ダウンロードが破損しています" : "The download was damaged";
        case UpdateFailureReason::NotSigned:
            return japanese() ? "この更新は署名されていません"
                              : "The update isn't signed by us";
        case UpdateFailureReason::NotWritable:
            return japanese() ? "ゲームフォルダに書き込めません"
                              : "The game folder isn't writable";
        case UpdateFailureReason::FileInTheWay:
            return japanese() ? "ファイルが置き換えを妨げています" : "A file is in the way";
        case UpdateFailureReason::NoSpace:
            return japanese() ? "空き容量が足りません" : "Not enough space";
        case UpdateFailureReason::Other:
            return japanese() ? "更新に失敗しました" : "The update failed";
        case UpdateFailureReason::None:
            break;
    }
    return "";
}

UpdateScreen::UpdateScreen(SpriteRenderer& batch, const UpdateLaunch& launch,
                           std::string& error) {
    if (!loadFace(batch, error)) return;
    if (!launch.preview.empty()) {
        // The capture's phase, with no engine behind it.
        received_.store(12 * 1024 * 1024);
        total_.store(27 * 1024 * 1024);
        if (launch.preview == "verifying") {
            phase_.store(static_cast<int>(update::ApplyPhase::Verifying));
        } else if (launch.preview == "installing") {
            phase_.store(static_cast<int>(update::ApplyPhase::Installing));
        } else if (launch.preview == "restarting") {
            phase_.store(static_cast<int>(update::ApplyPhase::Installing));
            previewRestarting_ = true;
        } else if (launch.preview == "failed") {
            failed_ = true;
            failure_ = UpdateFailureReason::DamagedDownload;
        } else {
            phase_.store(static_cast<int>(update::ApplyPhase::Downloading));
        }
        return;
    }
    notes_ = launch.manifest.notes;
    currentVersion_ = launch.currentVersion.toString();
    update::ApplySettings settings;
    settings.root = std::filesystem::u8path(launch.root);
    settings.manifest = launch.manifest;
    settings.manifestUrl = launch.manifestUrl;
    settings.cancelled = [this]() { return cancel_.load(); };
    settings.phase = [this](update::ApplyPhase phase) {
        phase_.store(static_cast<int>(phase));
    };
    settings.progress = [this](std::uint64_t done, std::uint64_t total) {
        received_.store(done);
        total_.store(total);
        return !cancel_.load();
    };
    // One worker for the whole attempt; the frame loop only reads the atomics.
    worker_ = std::thread([this, settings]() {
        update::ApplyResult result = update::apply(settings);
        std::lock_guard<std::mutex> lock(mutex_);
        result_ = std::move(result);
        finished_.store(true);
    });
}

UpdateScreen::~UpdateScreen() {
    cancel_.store(true);
    if (worker_.joinable()) worker_.join();
}

ScreenId UpdateScreen::update(const ScreenInput& in) {
    if (finished_.load() && !failed_ && !relaunchReady_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (result_.status == update::ApplyStatus::Ok) {
            launchPath_ = result_.launch;
            relaunchReady_ = true;
        } else if (result_.status == update::ApplyStatus::Cancelled) {
            return ScreenId::Title;
        } else {
            failed_ = true;
            failure_ = updateFailureReason(result_.error);
            // One line for the player's log and for the end-to-end test.
            std::printf("[update] failed: %s (%s)\n", updateFailureReasonText(failure_),
                        result_.error.c_str());
        }
    }
    if (failed_) {
        if (in.left || in.right) {
            choice_ = 1 - choice_;
            sound_ = 2;
        }
        if (in.cancel) return ScreenId::Title;
        if (in.confirm) {
            if (choice_ == 0) return ScreenId::Title;
            openUrl(notes_.c_str());
        }
        return ScreenId::Update;
    }
    // Cancel is allowed until the commit point (the engine's Installing phase).
    if (in.cancel && !relaunchReady_ &&
        phase_.load() != static_cast<int>(update::ApplyPhase::Installing)) {
        cancel_.store(true);
        sound_ = 1;
    }
    return ScreenId::Update;
}

bool UpdateScreen::wantsRelaunch(std::string* launch, std::string* from) {
    if (!relaunchReady_) return false;
    *launch = launchPath_;
    *from = currentVersion_;
    relaunchReady_ = false;
    return true;
}

void UpdateScreen::draw(SpriteRenderer& batch) const {
    batch.pushSolid({0, 0, 800, 600}, {0.02f, 0.02f, 0.05f, 1.f});
    if (failed_) {
        drawFailure(batch);
        return;
    }
    drawProgress(batch);
}

void UpdateScreen::drawProgress(SpriteRenderer& batch) const {
    frame(batch, {"アップデート", "UPDATE"}, 190, 400);
    const int phase = phase_.load();
    const bool restarting = relaunchReady_ || previewRestarting_;
    const char* phaseText = restarting
        ? say({"再起動しています…", "Restarting…"})
        : phase == static_cast<int>(update::ApplyPhase::Downloading)
            ? say({"ダウンロード中", "Downloading"})
            : phase == static_cast<int>(update::ApplyPhase::Verifying)
                ? say({"確認中", "Verifying"})
                : say({"インストール中", "Installing"});
    centred(batch, phaseText, 400, 252, 28.f, kWhite);
    if (phase == static_cast<int>(update::ApplyPhase::Downloading) ||
        phase == static_cast<int>(update::ApplyPhase::Verifying)) {
        const std::uint64_t done = received_.load();
        const std::uint64_t total = total_.load();
        char line[64];
        if (total > 0) {
            std::snprintf(line, sizeof line, "%.1f / %.1f MB", double(done) / 1048576.0,
                          double(total) / 1048576.0);
        } else {
            std::snprintf(line, sizeof line, "%s", "");
        }
        centred(batch, line, 400, 296, 20.f, kPale);
        const float fraction = total > 0
            ? std::clamp(float(done) / float(total), 0.f, 1.f)
            : 0.f;
        batch.pushSolid({230, 332, 340, 12}, kTrack);
        batch.pushSolid({230, 332, 340.f * fraction, 12}, kGold);
    }
    const bool cancellable = !restarting &&
        phase != static_cast<int>(update::ApplyPhase::Installing);
    help(batch, cancellable
        ? say({"戻る／Esc でキャンセル", "Back or Esc cancels"})
        : say({"インストール中はキャンセルできません",
               "Once installing starts it cannot be cancelled"}));
}

void UpdateScreen::drawFailure(SpriteRenderer& batch) const {
    frame(batch, {"アップデート", "UPDATE"}, 180, 480);
    centred(batch, say({"更新できませんでした", "The update could not be installed"}), 400,
            248, 24.f, kWhite);
    centred(batch, updateFailureReasonText(failure_), 400, 294, 20.f, kGold);
    centred(batch, say({"以前のバージョンはそのまま動きます",
                        "The old version keeps working"}),
            400, 334, 17.f, kPale);
    const char* choices[] = {say({"戻る", "Back"}),
                             say({"公開ページを開く", "Open release page"})};
    for (int i = 0; i < 2; ++i) {
        const float y = 394.f + 36.f * i;
        centred(batch, choices[i], 400, y, 18.f, choice_ == i ? kGold : kPale);
        if (choice_ == i) {
            const float width = widthOf(choices[i], 18.f);
            batch.pushSolid({400.f - width / 2.f, y + 24.f, width, 2.f}, kGold);
        }
    }
    help(batch, say({"←→ で選択 ／ 決定で実行", "Left and right choose; confirm runs"}));
}

std::unique_ptr<Screen> makeUpdateScreen(SpriteRenderer& batch, const UpdateLaunch& launch,
                                         std::string& error) {
    auto screen = std::make_unique<UpdateScreen>(batch, launch, error);
    if (!error.empty()) return nullptr;
    return screen;
}

}  // namespace ui
