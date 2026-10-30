#pragma once
// ui/sheet_locale.h — translated labels, painted over a sheet's own pixels as it loads.
//
// The menus and the HUD draw text baked into the install's sheets, at coordinates the screens hold.
// So a translation keeps the sheet's layout and replaces only the labels, read from
// assets/locale/<language>.txt. No art enters the repository, and changing a label is one line.
//
// A line is `sheet | x y w h | style | text`, where `\n` breaks a line. With no language set, or for
// a sheet the file does not name, the sheet is untouched.
#include <cstdint>
#include <string>
#include <vector>

namespace ui {

// Empty or "ja" restores the game's own sheets. False, with `error` set, when the file or the font
// cannot be read. A screen picks the change up when its sheets next load.
bool setSheetLanguage(const std::string& language, std::string& error);
// Empty until a language is set: the game's own Japanese.
const std::string& sheetLanguage();

struct SheetLabel {
    std::string sheet;  // lower case, without an extension
    int x = 0, y = 0, w = 0, h = 0;
    std::string style, text;
};
// Device-free so the file format is testable. Malformed lines are reported in `error`.
std::vector<SheetLabel> parseSheetLabels(const std::string& text, std::string& error);

// A translated sheet is drawn larger than the original, so its text stays sharp when the 800x600
// canvas is scaled up. The screens keep using the original's coordinates.
struct LocalizedSheet {
    int width = 0, height = 0;
    std::vector<uint8_t> rgba;
};
// False when the file names no label on this sheet, so the caller keeps the original pixels.
// `stem` is the path the screen asked for.
// `logicalWidth` is the original's width: a pack's larger image is painted at its own scale.
bool localizeSheet(const std::string& stem, const uint8_t* rgba, int width, int height, int logicalWidth, LocalizedSheet& out);

}  // namespace ui
