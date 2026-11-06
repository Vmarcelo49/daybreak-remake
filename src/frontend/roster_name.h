#pragma once
// frontend/roster_name.h — what a select or VS name plate says for the characters that are not in
// the shared p03 atlas.
//
// WHY this exists: the PC sixteen each own a 256x64 name cell in data/select/p03, a 2-column x
// 8-row atlas, and the locale file repaints those cells with the English spelling
// (assets/locale/en.txt `data/select/p03`). Roster indices 16..18 — the PSP three — fall outside
// that atlas, so those two screens draw their names with the caption face (src/ui/caption)
// instead, and this header is the one place that decides the text: the locale file's reading when
// a language is set, otherwise the game's own name. One function, so the select plate and the VS
// plate cannot spell a fighter two ways.
#include <string>

#include "battle/weapon_definition.h"
#include "ui/sheet_locale.h"

namespace ui {

// Runtime-text key of a roster name, indexed by roster character index.
inline constexpr const char* kRosterNameKey = "select/name";

// The name plate text for a roster index outside the p03 atlas, or "" for 0..15 (which have cells)
// and for an index no table defines.
//
// English falls back to the romanized reading rather than to a placeholder: a name is not a title,
// so showing the character's own name beats labelling them unknown. A missing caption font drops
// the text entirely and the portrait still identifies the fighter.
inline std::string rosterNameText(int character) {
    const gameplay::PspRosterEntry* entry = gameplay::pspRosterEntry(character);
    if (!entry) return {};
    if (!sheetLanguage().empty()) {
        const std::string& translated = localeText(kRosterNameKey, character);
        return translated.empty() ? std::string(entry->reading) : translated;
    }
    return entry->name;
}

}  // namespace ui
