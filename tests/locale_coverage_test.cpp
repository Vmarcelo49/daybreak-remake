// Issue #96: independently enumerate the UI cells the current screens can draw.
// This maintained manifest checks listed cells and translations; it cannot prove draw reachability.
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <set>
#include <string>
#include <tuple>
#include <vector>

#include "battle/weapon_definition.h"
#include "frontend/result_title.h"
#include "frontend/screen_title.h"
#include "ui/sheet_locale.h"

#define CHECK(x) do { if (!(x)) { std::fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #x); return 1; } } while (false)

using Key = std::tuple<std::string, int, int, int, int>;

int main() {
    const auto path = std::filesystem::path(__FILE__).parent_path().parent_path() / "assets/locale/en.txt";
    std::ifstream file(path);
    CHECK(file.good());
    const std::string contents{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
    std::string error;
    const auto labels = ui::parseSheetLabels(contents, error);
    CHECK(error.empty());
    std::set<Key> expected;
    bool manifestDuplicate = false;
    auto add = [&](const std::string& sheet, int x, int y, int w, int h) {
        if (!expected.emplace(sheet, x, y, w, h).second) manifestDuplicate = true;
    };
    for (int i = 0; i < gameplay::kResultTitleCount; ++i) add("result/title", i, 0, 0, 0);
    // TitleScreen::draw uses this cell stride for all selected/unselected rows.
    for (int y = 0; y < ui::kTitleItemCount; ++y) for (int x = 0; x < 2; ++x)
        add("data/title/title", x * (int)ui::kTitleItemSrc.w, y * (int)ui::kTitleItemStride,
            (int)ui::kTitleItemSrc.w, (int)ui::kTitleItemSrc.h);
    for (int i = 0; i < 6; ++i) add("data/object/p03", 26 + (i % 4) * 128, 20 + (i / 4) * 64, 84, 26);
    for (const char* sheet : {"data/object/p04", "data/object/p05", "data/object/p08"})
        for (int y : {0, 256}) add(sheet, 0, y, 512, 256);
    add("data/object/p09", 0, 256, 512, 256);
    add("data/object/system", 0, 128, 416, 64);
    for (int y : {192, 256}) for (int x : {0, 256}) add("data/object/system", x, y, 256, 64);
    add("data/object/system", 0, 320, 288, 64);
    for (int i = 0; i < 3; ++i) add("data/select/p00", 320, i * 64, 192, 64);
    for (int y : {0, 64, 128}) add("data/select/p01", 0, y, 256, 64);
    for (int x : {256, 384}) add("data/select/p01", x, 64, 128, 64);
    add("data/select/p01", 384, 128, 128, 64);
    for (int y : {320, 384, 448}) for (int x : {0, 256}) add("data/select/p01", x, y, 256, 64);
    for (int y : {0, 64}) for (int x : {0, 256}) add("data/select/p02", x, y, 256, 64);
    for (int y : {128, 192, 256}) add("data/select/p02", 0, y, 256, 64);
    for (int i = 0; i < 16; ++i) add("data/select/p03", (i / 8) * 256, (i % 8) * 64, 256, 64);
    for (int i = 0; i < 16; ++i) {
        char sheet[32];
        std::snprintf(sheet, sizeof sheet, "data/select/w%02d", i);
        for (int y = 0; y < gameplay::weaponCountForCharacter(i); ++y)
            for (int x : {0, 256}) add(sheet, x, y * 64, 256, 64);
    }
    for (const char* sheet : {"data/select/pbg00", "data/select/pbg02"}) {
        for (int i = 0; i < 7; ++i) add(sheet, 0, i * 64, 320, 64);
        for (int i = 1; i <= 3; ++i) add(sheet, 384, i * 64, 128, 64);
    }
    add("data/teamselect/bg00", 300, 6, 200, 50);
    for (int x : {121, 531}) for (int y : {86, 411}) add("data/select/bg00", x, y, 158, 100);
    for (int team = 0; team < 10; ++team) {
        const std::string sheet = team < 6 ? "data/teamselect/p00" : "data/teamselect/p01";
        const int cell = team < 6 ? team : team - 6;
        const int x = cell / 3 * 256, y = cell % 3 * 160;
        add(sheet, x, y + 4, 256, 46);
        add(sheet, x, y + 50, 256, 46);
        add(sheet, x + 6, y + 104, 220, 38);
    }
    CHECK(!manifestDuplicate);
    std::set<Key> actual;
    for (const auto& label : labels) {
        const Key key{label.sheet, label.x, label.y, label.w, label.h};
        CHECK(actual.insert(key).second);
        if (!expected.count(key)) {
            std::fprintf(stderr, "unused locale key: %s %d %d %d %d\n", label.sheet.c_str(), label.x, label.y, label.w, label.h);
            return 1;
        }
        CHECK((label.sheet == "result/title") == (label.style == "text"));
        CHECK(!label.text.empty());
        for (unsigned char c : label.text) CHECK(c >= 32 && c < 127);
    }
    for (const auto& key : expected) {
        if (!actual.count(key)) {
            std::fprintf(stderr, "missing locale key: %s %d %d %d %d\n", std::get<0>(key).c_str(), std::get<1>(key),
                         std::get<2>(key), std::get<3>(key), std::get<4>(key));
            return 1;
        }
    }
    std::printf("locale_coverage_test: %zu explicitly enumerated keys covered\n", actual.size());
    return 0;
}
