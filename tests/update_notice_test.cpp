// tests/update_notice_test.cpp — the title's update notice and the failure reasons,
// device-free (issue #100, step 4). The title screen needs a GPU; every choice, its side
// effect (Skip writes [update] skip_version) and the failure mapping live in plain types
// this test drives directly.
#include "update_test_suites.h"

#include <string>

#include "frontend/frontend_settings.h"
#include "frontend/screen_update.h"
#include "frontend/update_notice.h"
#include "ui/sheet_locale.h"

namespace {

using namespace ui;
using update_test::check;

UpdateNotice available() {
    UpdateNotice notice;
    notice.kind = UpdateNoticeKind::Available;
    notice.version = "2.0.0";
    notice.notes = "https://github.com/Vmarcelo49/daybreak-remake/releases/tag/v2.0.0";
    return notice;
}

// Presses `right` n times and returns the menu to the given choice.
void moveTo(UpdateNoticeMenu& menu, int choice) {
    ScreenInput in;
    in.right = true;
    for (int i = 0; i < choice; ++i) menu.update(in);
    check(menu.selected() == choice, "the notice moves right to choice " + std::to_string(choice));
}

}  // namespace

int main() {
    // The line names the version, in whichever language is active.
    {
        const UpdateNotice notice = available();
        check(updateNoticeLine(notice).find("2.0.0") != std::string::npos,
              "the available line names the version");
        check(updateNoticeChoiceCount(notice) == 4, "Available has four choices");
        for (int i = 0; i < 4; ++i) {
            check(std::string(updateNoticeChoiceLabel(notice, i)).size() > 0,
                  "choice " + std::to_string(i) + " has a label");
        }
    }

    // The menu is inert until the player moves into it.
    {
        UpdateNoticeMenu menu;
        menu.set(available());
        check(menu.visible(), "a set notice is visible");
        ScreenInput confirm;
        confirm.confirm = true;
        check(menu.update(confirm) == UpdateNoticeAction::None,
              "confirm does nothing while the title menu has focus");
        menu.focus(true);
        check(menu.update(confirm) == UpdateNoticeAction::Update,
              "confirm on Update opens the update screen");
    }

    // Right and left move the selection and wrap.
    {
        UpdateNoticeMenu menu;
        menu.set(available());
        menu.focus(true);
        ScreenInput right;
        right.right = true;
        menu.update(right);
        check(menu.selected() == 1, "right moves the selection");
        ScreenInput left;
        left.left = true;
        menu.update(left);
        check(menu.selected() == 0, "left moves it back");
        left.left = true;
        menu.update(left);
        check(menu.selected() == 3, "left wraps to the last choice");
    }

    // Each choice means what it says.
    {
        UpdateNoticeMenu menu;
        menu.set(available());
        menu.focus(true);
        moveTo(menu, 1);
        ScreenInput confirm;
        confirm.confirm = true;
        check(menu.update(confirm) == UpdateNoticeAction::Notes,
              "Release notes opens the page");
    }
    {
        UpdateNoticeMenu menu;
        menu.set(available());
        menu.focus(true);
        moveTo(menu, 2);
        ScreenInput confirm;
        confirm.confirm = true;
        check(menu.update(confirm) == UpdateNoticeAction::Later, "Later is Later");
        check(!menu.visible(), "Later hides the notice until the next launch");
    }
    {
        frontendSettings().updateSkipVersion.clear();
        UpdateNoticeMenu menu;
        menu.set(available());
        menu.focus(true);
        moveTo(menu, 3);
        ScreenInput confirm;
        confirm.confirm = true;
        check(menu.update(confirm) == UpdateNoticeAction::Skip, "Skip is Skip");
        check(frontendSettings().updateSkipVersion == "2.0.0",
              "Skip writes [update] skip_version");
        check(!menu.visible(), "Skip hides the notice");
    }

    // ManualOnly and Unavailable offer the release page only.
    {
        UpdateNotice manual;
        manual.kind = UpdateNoticeKind::ManualOnly;
        manual.notes = "https://example.invalid/releases";
        check(updateNoticeChoiceCount(manual) == 1, "ManualOnly has one choice");
        UpdateNoticeMenu menu;
        menu.set(manual);
        menu.focus(true);
        ScreenInput confirm;
        confirm.confirm = true;
        check(menu.update(confirm) == UpdateNoticeAction::Notes,
              "ManualOnly's choice opens the release page");
        UpdateNotice unavailable;
        unavailable.kind = UpdateNoticeKind::Unavailable;
        check(updateNoticeChoiceCount(unavailable) == 1, "Unavailable has one choice");
    }

    // Updated has no choices at all: it is one line.
    {
        UpdateNotice updated;
        updated.kind = UpdateNoticeKind::Updated;
        updated.version = "2.0.0";
        updated.updatedFrom = "1.0.0";
        check(updateNoticeChoiceCount(updated) == 0, "Updated has no choices");
        check(updateNoticeLine(updated).find("2.0.0") != std::string::npos,
              "Updated names the new version");
    }

    // The failure categories the screen shows, mapped from the engine's messages.
    {
        check(updateFailureReason("untrusted update manifest: bad signature") ==
                  UpdateFailureReason::NotSigned,
              "an untrusted manifest is 'not signed by us'");
        check(updateFailureReason("not enough free space for the update") ==
                  UpdateFailureReason::NoSpace,
              "the space check maps to 'not enough space'");
        check(updateFailureReason(
                  "refusing to overwrite player-notes.txt: the installed package does not "
                  "own it") == UpdateFailureReason::FileInTheWay,
              "an unowned file maps to 'a file is in the way'");
        check(updateFailureReason("the archive does not match the manifest's sha256") ==
                  UpdateFailureReason::DamagedDownload,
              "a hash mismatch maps to 'the download was damaged'");
        check(updateFailureReason("cannot write /games/.daybreak-update/2.0.0/archive") ==
                  UpdateFailureReason::NotWritable,
              "a write failure maps to 'the game folder isn't writable'");
        check(updateFailureReason("HTTP 404 from the server") ==
                  UpdateFailureReason::NoAnswer,
              "a 404 maps to 'GitHub didn't answer'");
        check(updateFailureReason("could not connect to the server") ==
                  UpdateFailureReason::NoConnection,
              "a connection failure maps to 'no connection'");
        for (const UpdateFailureReason reason :
             {UpdateFailureReason::NoConnection, UpdateFailureReason::NoAnswer,
              UpdateFailureReason::DamagedDownload, UpdateFailureReason::NotSigned,
              UpdateFailureReason::NotWritable, UpdateFailureReason::FileInTheWay,
              UpdateFailureReason::NoSpace}) {
            check(std::string(updateFailureReasonText(reason)).size() > 0,
                  "every failure reason has text");
        }
    }

    return update_test::report("update_notice_test");
}
