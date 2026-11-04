#include "frontend/update_notice.h"

#include "frontend/frontend_settings.h"
#include "frontend/menu_panel.h"
#include "ui/sheet_locale.h"

namespace ui {
namespace {

bool japanese() { return sheetLanguage().empty(); }

}  // namespace

int updateNoticeChoiceCount(const UpdateNotice& notice) {
    switch (notice.kind) {
        case UpdateNoticeKind::Available: return 4;
        case UpdateNoticeKind::ManualOnly:
        case UpdateNoticeKind::Unavailable: return 1;
        default: return 0;
    }
}

const char* updateNoticeChoiceLabel(const UpdateNotice& notice, int choice) {
    if (notice.kind == UpdateNoticeKind::Available) {
        switch (choice) {
            case 0: return say({"更新", "Update"});
            case 1: return say({"更新情報", "Release notes"});
            case 2: return say({"あとで", "Later"});
            case 3: return say({"この版をスキップ", "Skip this version"});
            default: return "";
        }
    }
    if (notice.kind == UpdateNoticeKind::ManualOnly ||
        notice.kind == UpdateNoticeKind::Unavailable) {
        return say({"公開ページを開く", "Open release page"});
    }
    return "";
}

std::string updateNoticeLine(const UpdateNotice& notice) {
    switch (notice.kind) {
        case UpdateNoticeKind::Available:
            return japanese() ? "バージョン " + notice.version + " が公開されています"
                              : "Version " + notice.version + " is available";
        case UpdateNoticeKind::ManualOnly:
            return japanese() ? "この更新は手動でダウンロードしてください"
                              : "This update must be downloaded manually";
        case UpdateNoticeKind::Unavailable:
            return japanese() ? "更新には libcurl が必要です"
                              : "Updates need libcurl";
        case UpdateNoticeKind::Updated:
            return japanese() ? notice.version + " に更新しました"
                              : "Updated to " + notice.version;
        case UpdateNoticeKind::None:
            break;
    }
    return std::string();
}

void UpdateNoticeMenu::set(const UpdateNotice& notice) {
    if (notice_.kind == notice.kind && notice_.version == notice.version &&
        notice_.updatedFrom == notice.updatedFrom) {
        return;
    }
    notice_ = notice;
    selected_ = 0;
    hidden_ = false;
}

UpdateNoticeAction UpdateNoticeMenu::update(const ScreenInput& in) {
    if (!visible() || !focused_) return UpdateNoticeAction::None;
    const int count = updateNoticeChoiceCount(notice_);
    if (count == 0) return UpdateNoticeAction::None;
    if (in.left) {
        selected_ = (selected_ + count - 1) % count;
        return UpdateNoticeAction::None;
    }
    if (in.right) {
        selected_ = (selected_ + 1) % count;
        return UpdateNoticeAction::None;
    }
    if (!in.confirm) return UpdateNoticeAction::None;
    if (notice_.kind == UpdateNoticeKind::Available) {
        switch (selected_) {
            case 0: return UpdateNoticeAction::Update;
            case 1: return UpdateNoticeAction::Notes;
            case 2:
                hidden_ = true;
                return UpdateNoticeAction::Later;
            default:
                // The task's Skip writes the setting; the host's settings sync persists it
                // on the next flush, the same way an Options change does.
                frontendSettings().updateSkipVersion = notice_.version;
                hidden_ = true;
                return UpdateNoticeAction::Skip;
        }
    }
    return UpdateNoticeAction::Notes;
}

}  // namespace ui
