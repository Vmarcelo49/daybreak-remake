// The front-end sheets the C++ extractor writes for the three PSP fighters (issue #91, Track D).
//
// docs/psp/FRONTEND-ART.md §2 is the contract: five file families at the PC sheets' own sizes and
// cell grids, so the select, VS and result screens read them with no per-character branch and no
// knowledge of the PSP. This test is the install-backed half of that claim (evidence tier 4): it
// extracts from the player's own disc, then reads every sheet through the product's own CNV
// decoder and checks the size, the cell grid, and that each cell the screens draw from carries
// pixels — the white flash cell included, which the reveal shows while a slot's ramp is below 1.0.
//
// Skips with code 77 when there is no ISO to read: the disc is the player's, never the
// repository's.
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "assets/cnv.h"
#include "psp/psp_extract.h"
#include "psp/psp_manifest.h"

namespace fs = std::filesystem;

namespace {

int failures = 0;

void check(bool ok, const std::string& what) {
    if (!ok) {
        std::printf("  FAIL %s\n", what.c_str());
        ++failures;
    }
}

std::vector<std::uint8_t> readBytes(const fs::path& path) {
    std::vector<std::uint8_t> bytes;
    std::FILE* file = std::fopen(path.string().c_str(), "rb");
    if (!file) return bytes;
    std::fseek(file, 0, SEEK_END);
    const long size = std::ftell(file);
    std::fseek(file, 0, SEEK_SET);
    if (size > 0) {
        bytes.resize((std::size_t)size);
        if (std::fread(bytes.data(), 1, bytes.size(), file) != bytes.size()) bytes.clear();
    }
    std::fclose(file);
    return bytes;
}

// A cell of a sheet, in pixels from its top-left corner.
struct Cell {
    unsigned x = 0, y = 0, w = 0, h = 0;
};

bool inside(const xm::CnvImage& image, const Cell& cell) {
    return cell.x + cell.w <= image.width && cell.y + cell.h <= image.height;
}

unsigned opaquePixels(const xm::CnvImage& image, const Cell& cell) {
    if (!inside(image, cell)) return 0;
    unsigned count = 0;
    for (unsigned y = cell.y; y < cell.y + cell.h; ++y)
        for (unsigned x = cell.x; x < cell.x + cell.w; ++x)
            if (image.rgba[((std::size_t)y * image.width + x) * 4 + 3] != 0) ++count;
    return count;
}

// The reveal's flash cell: 100 % opaque white, which is what makes a slot mid-ramp read as a
// white silhouette rather than a hole.
bool opaqueWhite(const xm::CnvImage& image, const Cell& cell) {
    if (!inside(image, cell)) return false;
    for (unsigned y = cell.y; y < cell.y + cell.h; ++y)
        for (unsigned x = cell.x; x < cell.x + cell.w; ++x) {
            const std::uint8_t* px = image.rgba.data() + ((std::size_t)y * image.width + x) * 4;
            if (px[0] != 255 || px[1] != 255 || px[2] != 255 || px[3] != 255) return false;
        }
    return true;
}

// The sheet as the screens see it: through the product's own decoder, which is also what rejects
// a file with the wrong header, the wrong payload size or a compressed payload.
bool load(const fs::path& path, const char* label, xm::CnvImage& image) {
    const std::vector<std::uint8_t> bytes = readBytes(path);
    check(!bytes.empty(), std::string(label) + " was not written");
    if (bytes.empty()) return false;
    try {
        image = xm::decodeCnvImage(bytes.data(), bytes.size());
    } catch (const std::exception& failure) {
        check(false, std::string(label) + " does not decode as a CNV: " + failure.what());
        return false;
    }
    return true;
}

void checkSize(const xm::CnvImage& image, unsigned width, unsigned height, const char* label) {
    check(image.width == width && image.height == height,
          std::string(label) + " is " + std::to_string(image.width) + "x" +
              std::to_string(image.height) + ", the contract is " + std::to_string(width) + "x" +
              std::to_string(height));
}

// One row of a weapon sheet: the row list's 256x64 cell and the plate under it.
void checkWeaponRow(const xm::CnvImage& image, unsigned row, const char* label) {
    const Cell list{0, row * 64, 256, 64};
    const Cell plate{256, row * 64, 256, 64};
    check(opaquePixels(image, list) > 0,
          std::string(label) + " row " + std::to_string(row) + " has no letter in its list cell");
    check(opaquePixels(image, plate) > 0,
          std::string(label) + " row " + std::to_string(row) + " has no item id in its plate cell");
}

}  // namespace

int main(int argc, char** argv) {
    const char* iso = std::getenv("DAYBREAK_PSP_ISO");
    if (!iso || !*iso) {
        std::puts("PSP_ART: skipped, DAYBREAK_PSP_ISO is not set");
        return 77;
    }
    if (!fs::exists(iso)) {
        std::printf("PSP_ART: skipped, DAYBREAK_PSP_ISO points at nothing (%s)\n", iso);
        return 77;
    }
    if (argc < 2) {
        std::puts("usage: psp_select_art_test <assets/psp/manifest.txt>");
        return 2;
    }

    // A scratch psp-data: the test must not disturb an extraction the player already has, and it
    // has to be able to run twice.
    const fs::path root = fs::temp_directory_path() / "daybreak-psp-art-test";
    std::error_code ignored;
    fs::remove_all(root, ignored);
    fs::create_directories(root, ignored);

    psp::PspExtractOptions options;
    options.isoPath = iso;
    options.dataDir = root.string();
    psp::PspManifest manifest = psp::PspManifest::load(argv[1]);
    options.manifest = &manifest;
    psp::registerAllPspConverters();
    std::printf("PSP_ART: extracting %zu files into %s\n", manifest.entries.size(), root.c_str());
    psp::PspExtractReport report;
    try {
        report = psp::extractPsp(options, std::cout);
    } catch (const std::exception& failure) {
        std::printf("PSP_ART: FAIL extraction: %s\n", failure.what());
        return 1;
    }

    // The contract's own numbers, per roster index (FRONTEND-ART.md §2, "Costume counts"). They
    // are spelled out here rather than read from the converter so that a drift in either the
    // contract or the generator fails this test.
    struct Fighter {
        const char* name;
        unsigned    costumes;
    };
    const Fighter fighters[] = {{"satoshi", 5}, {"miyoko", 7}, {"okonogi", 3}};
    const unsigned firstIndex = 16;

    for (unsigned slot = 0; slot < 3; ++slot) {
        const unsigned index = firstIndex + slot;
        char stem[32];
        const Fighter& fighter = fighters[slot];
        std::printf("  %u %s (%u costumes)\n", index, fighter.name, fighter.costumes);
        auto sheetPath = [&](const char* pattern) {
            std::snprintf(stem, sizeof stem, pattern, index);
            return root / "data" / stem;
        };

        // data/select/NN.cnv: one 256x256 portrait, pivot bottom-centre.
        xm::CnvImage portrait;
        if (load(sheetPath("select/%02u.cnv"), "portrait", portrait)) {
            checkSize(portrait, 256, 256, "portrait");
            check(opaquePixels(portrait, Cell{0, 0, 256, 256}) > 0, "portrait is empty");
            // Pivot bottom-centre: the figure has to reach the sheet's last row and stand in the
            // middle column, or the select panel and the VS screen draw it off its place.
            check(opaquePixels(portrait, Cell{0, 255, 256, 1}) > 0, "portrait does not reach the bottom row");
            check(opaquePixels(portrait, Cell{118, 0, 20, 256}) > 0, "portrait is not in the middle column");
        }

        // data/select/iNN.cnv: 3x2 of 80x128. Five art cells and the white flash cell — the grid
        // is 240 wide inside a 256-wide sheet, so the right 16 columns are outside every cell the
        // screen samples and hold nothing.
        xm::CnvImage chibi;
        if (load(sheetPath("select/i%02u.cnv"), "chibi", chibi)) {
            checkSize(chibi, 256, 256, "chibi");
            for (unsigned column = 0; column < 3; ++column)
                for (unsigned row = 0; row < 2; ++row) {
                    const Cell cell{column * 80, row * 128, 80, 128};
                    const std::string what = "chibi cell (" + std::to_string(column) + "," +
                                             std::to_string(row) + ")";
                    if (column == 2 && row == 1)
                        check(opaqueWhite(chibi, cell), what + " is not the reveal's opaque white");
                    else
                        check(opaquePixels(chibi, cell) > 0, what + " is empty");
                }
        }

        // data/select/cosNN.cnv: 3x3 of 80x128, one cell per costume, row-major. The cells past
        // the count must stay empty: the screen cycles 0..count-1 and an extra picture would be
        // a costume that cannot be launched.
        xm::CnvImage costumes;
        if (load(sheetPath("select/cos%02u.cnv"), "costumes", costumes)) {
            checkSize(costumes, 256, 384, "costumes");
            for (unsigned cellIndex = 0; cellIndex < 9; ++cellIndex) {
                const Cell cell{(cellIndex % 3) * 80, (cellIndex / 3) * 128, 80, 128};
                const std::string what = "costume cell " + std::to_string(cellIndex);
                if (cellIndex < fighter.costumes)
                    check(opaquePixels(costumes, cell) > 0, what + " is empty");
                else
                    check(opaquePixels(costumes, cell) == 0, what + " is drawn past the costume count");
            }
        }

        // data/select/wNN.cnv: four rows of 256x64, the row list in column 0 and the plate in
        // column 1. Both carry the place-holder's ink in every row.
        xm::CnvImage weapons;
        if (load(sheetPath("select/w%02u.cnv"), "weapons", weapons)) {
            checkSize(weapons, 512, 256, "weapons");
            for (unsigned row = 0; row < 4; ++row) checkWeaponRow(weapons, row, "weapons");
            // The place-holder's left column spells the slot letter, so the four rows differ.
            const Cell letters[4] = {{0, 0, 256, 64}, {0, 64, 256, 64}, {0, 128, 256, 64}, {0, 192, 256, 64}};
            for (unsigned row = 1; row < 4; ++row) {
                bool differs = false;
                for (unsigned y = 0; y < 64 && !differs; ++y)
                    for (unsigned x = 0; x < 256 && !differs; ++x) {
                        const std::uint8_t* a = weapons.rgba.data() +
                                                ((std::size_t)(letters[0].y + y) * weapons.width + x) * 4;
                        const std::uint8_t* b = weapons.rgba.data() +
                                                ((std::size_t)(letters[row].y + y) * weapons.width + x) * 4;
                        differs = a[0] != b[0] || a[1] != b[1] || a[2] != b[2] || a[3] != b[3];
                    }
                check(differs, "weapons row " + std::to_string(row) + " repeats row 0's letter");
            }
        }

        // data/win/NNa.cnv: 512x512, the figure centred and standing on the PC sheets' baseline
        // (bottom at 492), which is what puts the result screen's quote band at its chest.
        xm::CnvImage win;
        if (load(sheetPath("win/%02ua.cnv"), "win", win)) {
            checkSize(win, 512, 512, "win");
            unsigned lastRow = 0;
            unsigned lastRowPixels = 0;
            for (unsigned y = 0; y < win.height; ++y) {
                const unsigned count = opaquePixels(win, Cell{0, y, 512, 1});
                if (count) {
                    lastRow = y;
                    lastRowPixels = count;
                }
            }
            check(lastRowPixels > 0 && lastRow >= 480 && lastRow <= 492,
                  "win figure ends at row " + std::to_string(lastRow) + ", the baseline is 492");
            check(opaquePixels(win, Cell{192, 0, 128, 512}) > 0, "win figure is not centred");
            check(opaquePixels(win, Cell{0, 424, 512, 68}) > 0,
                  "win figure does not reach the quote band (y >= 424)");
        }

        // The extractor is the thing that wrote them, so its own report has to name them.
        for (const char* pattern : {"data/select/%02u.cnv", "data/select/i%02u.cnv",
                                    "data/select/cos%02u.cnv", "data/select/w%02u.cnv",
                                    "data/win/%02ua.cnv"}) {
            std::snprintf(stem, sizeof stem, pattern, index);
            bool listed = false;
            for (const std::string& written : report.converted) listed = listed || written == stem;
            check(listed, std::string(stem) + " is not in the extraction report");
        }
    }

    fs::remove_all(root, ignored);
    if (failures) {
        std::printf("PSP_ART: %d failure(s)\n", failures);
        return 1;
    }
    std::puts("PSP_ART: ok");
    return 0;
}
