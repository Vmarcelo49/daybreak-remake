#pragma once
// ui/story_locale.h — display-time English story text, the #99 sibling of sheet_locale.h.
//
// The owner's 2026-11-19 decision keeps the translated story in the repository, in
// assets/locale/story_en.json, and leaves every script in the install untouched. This module
// owns that one file and the one lookup rule; the dialogue and result screens ask it for the
// text to display and never name the file themselves.
//
// A key is the script path under data/scenario/ plus '#ordinal':
//   D01-0.txt#0          dialogue, the 0-based text-command ordinal in file order
//   win/05-08-4.txt#0    victory quote, the 0-based quote-line ordinal in file order
// The ordinal is the unit both parsers already emit, so no file name has to be re-parsed at
// display time. Values are ASCII and keep the \n, \cRRGGBB and \e escapes the caption walkers
// understand; nothing here interprets them.
//
// The EN/JP switch stays owned by ui::setSheetLanguage (sheet_locale.h): it calls
// setStoryTranslationLanguage for us, so the Options toggle and --language cover both routes.
// Japanese mode loads nothing and returns the script's own line unchanged.
#include <cstddef>
#include <map>
#include <string>

namespace ui {

// Parses the flat JSON string->string map. Device-free so the shipped file and malformed
// fixtures are testable without a GPU or game data. `out` is left empty on error.
bool parseStoryTranslations(const std::string& json, std::map<std::string, std::string>& out,
                            std::string& error);

// "data/scenario/D01-0.txt" + 0 -> "D01-0.txt#0". Paths that do not start with that prefix
// keep their own spelling, which lets a synthetic test script use a stable key.
std::string storyTranslationKey(const std::string& scriptPath, int ordinal);

// Loads story_en.json for an English language code; "" or "ja" clears the map. A missing or
// malformed file is logged once, never fatal: the game runs with the original Japanese text.
bool setStoryTranslationLanguage(const std::string& language);

// The English value of `key`, or empty in Japanese mode, when absent, and after a load failure.
// A key that is absent while English is active is reported once, then falls back silently.
const std::string& storyTranslation(const std::string& key);

// The text a caption should show: the English entry when active, else `original`. Callers copy
// the result before the next lookup; the escapes are passed through byte for byte.
std::string storyDisplayText(const std::string& scriptPath, int ordinal, const std::string& original);

size_t storyTranslationCount();
size_t storyTranslationMissingCount();  // diagnostics: distinct absent keys reported so far

}  // namespace ui
