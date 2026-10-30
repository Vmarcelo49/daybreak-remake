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

// False, with `error` set, when the file or the font cannot be read.
bool setSheetLanguage(const std::string& language, std::string& error);

struct SheetLabel {
    std::string sheet;  // lower case, without an extension
    int x = 0, y = 0, w = 0, h = 0;
    std::string style, text;
};
// Device-free so the file format is testable. Malformed lines are reported in `error`.
std::vector<SheetLabel> parseSheetLabels(const std::string& text, std::string& error);

// Paints this sheet's labels into its RGBA pixels. `stem` is the path the screen asked for.
void localizeSheet(const std::string& stem, uint8_t* rgba, int width, int height);

}  // namespace ui
