// Issue #96: verify every translated rectangle against the bundle-first game sheets.
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

#include "assets/asset_source.h"
#include "assets/cnv.h"
#include "ui/sheet_locale.h"

#define CHECK(x) do { if (!(x)) { std::fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #x); return 1; } } while (false)

int main() {
    namespace fs = std::filesystem;
    fs::path root = fs::path(__FILE__).parent_path().parent_path();
    const char* game = std::getenv("GAME_DIR");
    const fs::path install = game ? fs::path(game) : root / "Higurashi-Daybreak";
    if (!fs::is_directory(install / "data")) {
        std::puts("SKIP: game install not found");
        return 77;
    }
    CHECK(fnd::assets::assetSource().openInstall(install.string()));
    // Parse the copy the runtime loads (CWD, beside the binary), falling back to the source.
    std::ifstream file("assets/locale/en.txt");
    if (!file.good()) file.open(root / "assets/locale/en.txt");
    CHECK(file.good());
    const std::string contents{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
    std::string error;
    const auto labels = ui::parseSheetLabels(contents, error);
    CHECK(error.empty());
    CHECK(ui::setSheetLanguage("en", error));
    std::map<std::string, std::vector<ui::SheetLabel>> sheets;
    for (const auto& label : labels) if (label.style != "text") sheets[label.sheet].push_back(label);
    for (const auto& [stem, entries] : sheets) {
        std::vector<uint8_t> bytes;
        CHECK(fnd::assets::assetSource().read(stem + ".cnv", bytes));
        const auto original = xm::decodeCnvImage(bytes.data(), bytes.size());
        ui::LocalizedSheet localized;
        CHECK(ui::localizeSheet(stem, original.rgba.data(), (int)original.width, (int)original.height,
                                (int)original.width, localized));
        CHECK(localized.width % (int)original.width == 0);
        const int scale = localized.width / (int)original.width;
        CHECK(localized.height == (int)original.height * scale);
        for (const auto& label : entries) {
            CHECK(label.x + label.w <= (int)original.width && label.y + label.h <= (int)original.height);
            // This checks that each cell changes; it does not prove the new text is readable.
            bool changed = false;
            for (int y = label.y * scale; y < (label.y + label.h) * scale && !changed; ++y)
                for (int x = label.x * scale; x < (label.x + label.w) * scale; ++x) {
                    const auto* p = &localized.rgba[((size_t)y * localized.width + x) * 4];
                    const auto* q = &original.rgba[((size_t)(y / scale) * original.width + x / scale) * 4];
                    if (p[0] != q[0] || p[1] != q[1] || p[2] != q[2] || p[3] != q[3]) {
                        changed = true;
                        break;
                    }
                }
            if (!changed) {
                std::fprintf(stderr, "unchanged translation cell: %s %d,%d\n", stem.c_str(), label.x, label.y);
                return 1;
            }
        }
    }
    std::printf("locale_sheets_test: %zu bundle-first sheets checked\n", sheets.size());
    return 0;
}
