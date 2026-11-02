#pragma once
// The title backdrop's choices (issue #98): which stage, if any, is drawn live behind the
// title menu in place of the original's still painting.
//
// A table, not a free string, because the Options row cycles it: the persisted value and
// the row must agree, and only these have labels. The original has no such row — its title
// is data/title/back00 and nothing else — so every word here is the port's (PORT RULE).
//
// Why the shrine: the original's backdrop is itself a painted shrine approach
// (docs/reference/README.md), so these candidates continue the subject the title already
// has. --title-backdrop=stageNN accepts any stage directory for a one-off comparison; a
// value the table does not carry then shows its directory name in the row.
#include <string>

#include "frontend/menu_panel.h"   // Words, say

namespace ui {

struct TitleBackdropChoice {
    const char* stage;     // "" is the original art; otherwise a stage directory name
    const char* nameJa;
    const char* nameEn;
};

inline constexpr TitleBackdropChoice kTitleBackdrops[] = {
    {"",        "元のタイトル", "ORIGINAL"},
    {"stage03", "神社 昼",       "SHRINE DAY"},      // data/stage03 shrine_grounds_day
    {"stage13", "神社 夕",       "SHRINE SUNSET"},   // data/stage13
    {"stage06", "神社上 昼",     "UPPER DAY"},       // data/stage06 shrine_upper_day
    {"stage16", "神社上 夕",     "UPPER SUNSET"},    // data/stage16
};
inline constexpr int kTitleBackdropCount =
    (int)(sizeof(kTitleBackdrops) / sizeof(kTitleBackdrops[0]));

// Index in the table, or -1 for a stage it does not carry (a hand-edited file, or
// --title-backdrop= with a stage the row has no label for).
inline int titleBackdropIndex(const std::string& stage) {
    for (int i = 0; i < kTitleBackdropCount; ++i)
        if (stage == kTitleBackdrops[i].stage) return i;
    return -1;
}

// The row's value: the choice's own label, or the directory name when the value is a stage
// the list does not carry. Never empty.
inline std::string titleBackdropLabel(const std::string& stage) {
    const int index = titleBackdropIndex(stage);
    if (index < 0) return stage;
    return say(Words{kTitleBackdrops[index].nameJa, kTitleBackdrops[index].nameEn});
}

// The value `direction` (+1 right, -1 left) from `stage`. A value outside the table snaps
// onto the first entry for a right press and the last for a left one, so one press always
// reaches a labelled choice.
inline std::string cycleTitleBackdrop(const std::string& stage, int direction) {
    const int index = titleBackdropIndex(stage);
    const int step = direction < 0 ? -1 : 1;
    if (index < 0) return kTitleBackdrops[step > 0 ? 0 : kTitleBackdropCount - 1].stage;
    return kTitleBackdrops[(index + step + kTitleBackdropCount) % kTitleBackdropCount].stage;
}

}  // namespace ui
