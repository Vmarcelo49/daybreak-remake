#include "frontend/result_title.h"

#include "assets/exe_strings.h"
#include "ui/sheet_locale.h"

namespace gameplay {
bool loadResultTitles(const std::string& exePath, ResultTitleTable& out, std::string& error) {
    // VA 0x6b7308: the table FUN_00430860 indexes (`(&PTR_DAT_006b7308)[index]`), 41 entries
    // terminated by a null pointer.
    constexpr uint32_t kTitleTableVa = 0x6b7308;
    if (!fnd::assets::readExeStringTable(exePath, kTitleTableVa, out.titles, error)) return false;
    if (!out.loaded()) {
        error = "title table has " + std::to_string(out.titles.size()) + " entries, expected " +
                std::to_string(kResultTitleCount);
        return false;
    }
    return true;
}

std::string resultTitleForLanguage(const ResultTitleTable& table, int index,
                                   bool translated, const std::string& translation) {
    if (!translated) return table.text(index);
    return translation.empty() && index >= 0 && index < kResultTitleCount ? "UNKNOWN TITLE" : translation;
}

std::string resultTitleForLanguage(const ResultTitleTable& table, int index) {
    return resultTitleForLanguage(table, index, !ui::sheetLanguage().empty(), ui::localeText("result/title", index));
}

}  // namespace gameplay
