#pragma once
// frontend/update_notice.h — what the title says about an update (issue #100, step 4).
//
// Device-free on purpose: the title draws it, but every choice and its side effect (Skip
// writes [update] skip_version) is a plain state machine the frontend test drives without
// a GPU. The task says a failed check, UpToDate, Skipped and an untrusted signature show
// nothing, so those never reach this type at all.
#include <cstdint>
#include <string>

#include "frontend/screen.h"

namespace ui {

enum class UpdateNoticeKind : std::uint8_t {
    None,
    Available,    // "Version X.Y.Z is available": Update / Notes / Later / Skip
    ManualOnly,   // the manifest is a newer format: Open release page
    Unavailable,  // this build has no HTTP client (no libcurl): Open release page
    Updated,      // the relaunched build says "Updated to Y"; no choices
};

struct UpdateNotice {
    UpdateNoticeKind kind = UpdateNoticeKind::None;
    std::string version;     // Available, Updated
    std::string notes;       // the release page URL
    std::string updatedFrom; // Updated: the version this build replaced

    bool active() const { return kind != UpdateNoticeKind::None; }
};

enum class UpdateNoticeAction : std::uint8_t {
    None,
    Update,   // open the update screen
    Notes,    // SDL_OpenURL(notes); the screen does the opening
    Later,    // hide until the next launch
    Skip,     // write skip_version and hide
};

// The choices, left to right; Updated has none and the title only draws its line.
int updateNoticeChoiceCount(const UpdateNotice& notice);
const char* updateNoticeChoiceLabel(const UpdateNotice& notice, int choice);
// The line above the choices, in the active language.
std::string updateNoticeLine(const UpdateNotice& notice);

// The title's notice: which choice is selected and what a confirm means. `update` is
// called only while the notice has focus; the title menu keeps its own machine.
class UpdateNoticeMenu {
public:
    void set(const UpdateNotice& notice);
    const UpdateNotice& notice() const { return notice_; }
    bool visible() const { return notice_.active() && !hidden_; }
    void hide() { hidden_ = true; }
    void focus(bool on) { focused_ = on; }
    bool focused() const { return focused_; }
    int selected() const { return selected_; }

    UpdateNoticeAction update(const ScreenInput& in);

private:
    UpdateNotice notice_;
    int selected_ = 0;
    bool hidden_ = false;
    bool focused_ = false;
};

}  // namespace ui
