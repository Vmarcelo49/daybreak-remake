// Issue #20: the recovered victory-quote rule and the earned-title names.
//
// Device-free for the rules themselves; the title NAMES come from the installed exe's own table
// (VA 0x6b7308), so the one check that reads them skips when the install is absent — the same
// convention the other asset-backed tests use.
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#define CHECK(condition) do { if (!(condition)) { std::fprintf(stderr,"%s:%d: %s\n",__FILE__,__LINE__,#condition); return 1; } } while (false)

#include "frontend/result_title.h"
#include "frontend/result_quote.h"
#include "ui/sheet_locale.h"

namespace fs = std::filesystem;

static fs::path findInstall() {
    if (const char* env = std::getenv("GAME_DIR")) return fs::path(env);
    fs::path game = fs::path("Higurashi-Daybreak");
    for (const fs::path& d : {fs::absolute(fs::path(".")), fs::current_path()}) {
        for (fs::path r = d; !r.empty(); r = r.parent_path()) {
            std::error_code ec;
            if (fs::is_directory(r / "src" / "assets", ec)) {
                game = r / "Higurashi-Daybreak";
                break;
            }
            if (r == r.parent_path()) break;
        }
        std::error_code ec;
        if (fs::is_directory(game / "data", ec)) return game;
    }
    return fs::path();
}

int main() {
    // --- the quote rule -----------------------------------------------------
    // FUN_00635d40:255-273 + FUN_00409340:180-186: the persona variant is character 0 or 4
    // with weapon slot 2, and it substitutes ids 16/17.
    CHECK(ui::resultPersonaId(0, 2) == 16);
    CHECK(ui::resultPersonaId(4, 2) == 17);
    CHECK(ui::resultPersonaId(0, 1) == 0);
    CHECK(ui::resultPersonaId(4, 0) == 4);
    CHECK(ui::resultPersonaId(2, 2) == 2);

    // FUN_00635d40:288-318: the grade from the margin and the winners' HP.
    CHECK(ui::resultOutcomeGrade(29, false) == 3);
    CHECK(ui::resultOutcomeGrade(29, true) == 4);
    CHECK(ui::resultOutcomeGrade(30, true) == 2);
    CHECK(ui::resultOutcomeGrade(49, true) == 2);
    CHECK(ui::resultOutcomeGrade(50, false) == 1);
    CHECK(ui::resultOutcomeGrade(0, false) == 3);

    // FUN_00635d40:323-346: the single-script fallback rule.
    CHECK(ui::resultFallbackSingleId(0, 1) == 17);
    CHECK(ui::resultFallbackSingleId(0, 16) == 16);
    CHECK(ui::resultFallbackSingleId(16, 0) == 16);
    CHECK(ui::resultFallbackSingleId(5, 17) == 17);
    CHECK(ui::resultFallbackSingleId(17, 17) == 17);
    CHECK(ui::resultFallbackSingleId(16, 17) == 17);   // the original's random branch, pinned

    // A 2v2 plan: both winners in panel order, sorted pair, the pair script and the fallback.
    {
        const int characters[2] = {2, 0};
        const int weapons[2] = {0, 0};
        const ui::WinnerQuotePlan plan = ui::planWinnerQuote(characters, weapons, 2, 42, false);
        CHECK(plan.pairA == 0 && plan.pairB == 2);
        CHECK(plan.grade == 2);
        CHECK(plan.pairScript == "data/scenario/win/00-02-2.txt");
        CHECK(plan.fallbackScript == "data/scenario/win/17.txt");
        CHECK(!plan.winners[0].persona && !plan.winners[1].persona);
    }
    // The persona variant changes both the id used for the file name and the art flag.
    {
        const int characters[2] = {0, 4};
        const int weapons[2] = {2, 2};
        const ui::WinnerQuotePlan plan = ui::planWinnerQuote(characters, weapons, 2, 60, false);
        CHECK(plan.winners[0].character == 16 && plan.winners[0].persona);
        CHECK(plan.winners[1].character == 17 && plan.winners[1].persona);
        CHECK(plan.pairA == 16 && plan.pairB == 17);
        CHECK(plan.grade == 1);
        CHECK(plan.pairScript == "data/scenario/win/16-17-1.txt");
        CHECK(plan.fallbackScript == "data/scenario/win/17.txt");
    }
    // A one-member side repeats its member: the port's 1v1, and the self-pair scripts ship.
    {
        const int characters[2] = {4, -1};
        const int weapons[2] = {0, 0};
        const ui::WinnerQuotePlan plan = ui::planWinnerQuote(characters, weapons, 1, 10, false);
        CHECK(plan.pairA == 4 && plan.pairB == 4);
        CHECK(plan.pairScript == "data/scenario/win/04-04-3.txt");
    }
    // A one-member PERSONA side lands on the persona id's own single script, because no
    // 17-17 pair ships (the missing-pair list in the issue's evidence).
    {
        const int characters[2] = {4, -1};
        const int weapons[2] = {2, 0};
        const ui::WinnerQuotePlan plan = ui::planWinnerQuote(characters, weapons, 1, 10, false);
        CHECK(plan.pairA == 17 && plan.pairB == 17);
        CHECK(plan.fallbackScript == "data/scenario/win/17.txt");
    }

    // A win script holds several VOICE alternatives; the original picks one at random.
    {
        const std::string script =
            "# comment\r\nVOICE W00-01-1.wav\r\nfirst line\r\nsecond line\r\n"
            "VOICE W00-01-2.wav\r\nthird line\r\n";
        const std::vector<ui::ResultQuoteEntry> entries = ui::parseResultQuotes(script);
        CHECK(entries.size() == 2);
        CHECK(entries[0].voice == "W00-01-1.wav" && entries[0].text == "first line");
        CHECK(entries[1].voice == "W00-01-2.wav" && entries[1].text == "third line");
        CHECK(ui::parseResultQuotes("").empty());
        const int pick = ui::resultQuoteEntryIndex((int)entries.size(), 1, 3600);
        CHECK(pick >= 0 && pick < 2);
        CHECK(ui::resultQuoteEntryIndex(0, 0, 0) == -1);
    }

    // The locale must have exactly one nonempty ASCII translation for every title index.
    {
        // Parse the copy the runtime loads (CWD, beside the binary), falling back to the source.
        fs::path locale = "assets/locale/en.txt";
        std::ifstream file(locale);
        if (!file.good()) {
            locale = fs::path(__FILE__).parent_path().parent_path() / locale;
            file.open(locale);
        }
        CHECK(file.good());
        const std::string contents{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
        std::string error;
        const auto labels = ui::parseSheetLabels(contents, error);
        CHECK(error.empty());
        int seen[gameplay::kResultTitleCount] = {};
        for (const auto& label : labels) {
            if (label.sheet != "result/title") continue;
            CHECK(label.style == "text" && label.y == 0 && label.w == 0 && label.h == 0);
            CHECK(label.x >= 0 && label.x < gameplay::kResultTitleCount);
            CHECK(!label.text.empty());
            for (unsigned char c : label.text) CHECK(c >= 32 && c < 127);
            ++seen[label.x];
        }
        for (int count : seen) CHECK(count == 1);
        CHECK(ui::setSheetLanguage("en", error));
        gameplay::ResultTitleTable fake;
        fake.titles.resize(gameplay::kResultTitleCount, "日本語");
        for (int i = 0; i < gameplay::kResultTitleCount; ++i) {
            CHECK(!ui::localeText("result/title", i).empty());
            CHECK(gameplay::resultTitleForLanguage(fake, i) == ui::localeText("result/title", i));
        }
        CHECK(gameplay::resultTitleForLanguage(fake, 0, true, "") == "UNKNOWN TITLE");
        CHECK(gameplay::resultTitleForLanguage(fake, 0, false, "") == "日本語");
        CHECK(gameplay::resultTitleForLanguage(fake, -1, true, "").empty());
        CHECK(ui::localeText("result/title", -1).empty());
        CHECK(ui::localeText("result/title", gameplay::kResultTitleCount).empty());
        CHECK(!ui::setSheetLanguage("missing-locale", error));
        CHECK(ui::sheetLanguage() == "en");
        CHECK(!ui::localeText("result/title", 6).empty());
        CHECK(ui::setSheetLanguage("ja", error));
        CHECK(ui::localeText("result/title", 0).empty());
        CHECK(gameplay::resultTitleForLanguage(fake, 0) == "日本語");
    }

    // --- the shipped title table (asset-backed, skipped without the install) ---
    const fs::path install = findInstall();
    if (!install.empty()) {
        gameplay::ResultTitleTable table;
        std::string error;
        CHECK(gameplay::loadResultTitles((install / "DaybreakDX.exe").string(), table, error));
        CHECK(table.loaded());
        CHECK(table.titles.size() == (size_t)gameplay::kResultTitleCount);
        // The reference print's winning 1P row: ひぐらしマスター is index 6.
        CHECK(std::string(table.text(6)) == "ひぐらしマスター");
        CHECK(std::string(table.text(gameplay::kResultTitlePenalty)) == "罰ゲーム決定");
        CHECK(std::string(table.text(999)).empty());
    } else {
        std::puts("result_title_test: install not found, title-table checks skipped");
    }

    std::puts("result_title_test: quote rule and title names ok");
    return 0;
}
