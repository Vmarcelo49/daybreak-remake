// psp/psp_select_art.cpp — the front-end sheets, from the PSP's own select art.
//
// The port is line for line the one tools/asset-tools/psp_select_art.py makes, because that is
// what defined the sheets and what the select, VS and result screens were judged against
// (docs/psp/FRONTEND-ART.md §2 is the contract, §4 the transforms). A player has no Python, so
// the extractor has to make them; keeping the arithmetic identical is what makes "the same
// picture" checkable rather than argued — the two write byte-identical files.
//
// What the PSP actually gives us, and where the rest comes from:
//
//   gra/gim/select/vs_enter_<name>.gim   176x132 INDEX8  the portrait: the versus screen's face
//   gra/gim/select/bustup_<name>.gim     224x130 INDEX8  two poses side by side; the winner
//   gra/gim/select/icon_on.gim           192x240 INDEX8  4x5 of 48x48, in PSP roster order
//
// The PSP ships no chibi body, no per-costume picture and no per-weapon picture: its own select
// screen is a list of text names beside those head icons (costume.gim and weapon.gim are text
// atlases). So the chibi and costume cells are the character's own roster icon on a drawn floor
// tile, and the weapon rows are lettered plates. Each of those is stated where it is drawn, and
// FRONTEND-ART.md §4/§7 records them as place-holders, not as recovered layout.
#include "psp/psp_select_art.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <ostream>
#include <stdexcept>

#include "battle/core/psp_roster.hpp"
#include "psp/gim.h"
#include "psp/psp_extract.h"
#include "psp/psp_model.h"
#include "psp/tga.h"

namespace fs = std::filesystem;

namespace psp {
namespace {

using Rgba = std::array<std::uint8_t, 4>;

// ---------------------------------------------------------------------------------------------
// The contract's own numbers (docs/psp/FRONTEND-ART.md §2). Every cell family shares 80x128 so
// the screens address a cell as (costume % 3, costume / 3) with no per-sheet constant.
// ---------------------------------------------------------------------------------------------
constexpr unsigned kPortraitWidth = 256, kPortraitHeight = 256;
constexpr unsigned kChibiWidth = 256, kChibiHeight = 256;
constexpr unsigned kCostumeWidth = 256, kCostumeHeight = 384;
constexpr unsigned kWeaponWidth = 512, kWeaponHeight = 256;
constexpr unsigned kWinWidth = 512, kWinHeight = 512;
constexpr unsigned kCellWidth = 80, kCellHeight = 128;
constexpr unsigned kWeaponRowHeight = 64;
constexpr unsigned kWeaponColumns = 2;
constexpr unsigned kWeaponColumnWidth = kWeaponWidth / kWeaponColumns;
static_assert(kWeaponHeight == kWeaponRowHeight * 4, "the weapon sheet is four rows of 256x64");

// The roster icon sheet (docs/psp/research/RESOURCES.md §7): 4 x 5 cells of 48x48.
constexpr unsigned kIconCell = 48, kIconColumns = 4, kIconRows = 5;

// The PC win sheets' own framing, measured on this install's data/win/00a and 13a: the figure's
// alpha bounds are 376x449 at (30,63) and 281x459 at (118,53), i.e. ~450 px tall and reaching
// the lower edge. A PSP bust-up is head and shoulders, so it is set a little shorter (420) and
// kept off the very edge (bottom 492) where the result screen's quote band (y >= 424 on screen)
// cuts it at the chest the way it cuts the PC figures.
constexpr unsigned kWinFigureHeight = 420;
constexpr unsigned kWinBottom = 492;

constexpr Rgba kWhite{255, 255, 255, 255};
// The floor tile the PC's own chibi and costume cells stand on, sampled from data/select/i00.cnv
// as the game draws it: a bright green diamond with a darker bevel.
constexpr Rgba kFloorFill{86, 210, 114, 255};
constexpr Rgba kFloorEdge{44, 148, 84, 255};
constexpr Rgba kPlateFill{24, 32, 48, 255};
constexpr Rgba kPlateBorder{96, 160, 220, 255};
constexpr Rgba kPlateText{235, 240, 250, 255};

// The 48x48 head icon the chibi and costume cells stand in front of is drawn smaller than the
// cell on purpose: it is the PSP's white-backed card, and at full cell width it reads as three
// white blocks in the diamond instead of a character standing on the floor.
constexpr double kChibiFaceWidth = 64, kChibiFaceHeight = 60;
constexpr int kChibiFaceBaseline = 86;   // measured from the cell's top edge

// ---------------------------------------------------------------------------------------------
// Pixels. The reference works in RGBA8 with a double-precision source-over blend; the one place
// the arithmetic is visible is a resampled edge, so it is reproduced exactly rather than
// re-derived (see the header).
// ---------------------------------------------------------------------------------------------
RgbaImage canvas(unsigned width, unsigned height) {
    RgbaImage image;
    image.width = width;
    image.height = height;
    image.rgba.assign((std::size_t)width * height * 4, 0);
    return image;
}

int clampByte(double value) {
    // Python's int(round(v)) wants half-to-even, which is what FE_TONEAREST is; the clamp is the
    // reference's max(0, min(255, ...)).
    const double rounded = std::nearbyint(value);
    if (!(rounded > 0.0)) return 0;
    if (rounded >= 255.0) return 255;
    return (int)rounded;
}

void putPixel(RgbaImage& image, int x, int y, Rgba colour) {
    if (x < 0 || y < 0 || (unsigned)x >= image.width || (unsigned)y >= image.height) return;
    std::uint8_t* at = image.rgba.data() + ((std::size_t)y * image.width + (unsigned)x) * 4;
    std::copy(colour.begin(), colour.end(), at);
}

void fillRect(RgbaImage& image, int x, int y, unsigned width, unsigned height, Rgba colour) {
    for (unsigned row = 0; row < height; ++row)
        for (unsigned column = 0; column < width; ++column)
            putPixel(image, x + (int)column, y + (int)row, colour);
}

void blendPixel(RgbaImage& image, int x, int y, const std::uint8_t* source) {
    if (x < 0 || y < 0 || (unsigned)x >= image.width || (unsigned)y >= image.height) return;
    std::uint8_t* at = image.rgba.data() + ((std::size_t)y * image.width + (unsigned)x) * 4;
    if (source[3] == 255) {
        std::copy(source, source + 4, at);
        return;
    }
    if (source[3] == 0) return;
    const double sourceAlpha = source[3] / 255.0;
    const double destAlpha = at[3] / 255.0;
    const double keep = 1.0 - sourceAlpha;
    const double outAlpha = sourceAlpha + destAlpha * keep;
    if (outAlpha <= 0.0) return;
    for (int channel = 0; channel < 3; ++channel) {
        // The multiplication order is the reference's: (dest * destAlpha) * keep.
        const double value = (source[channel] * sourceAlpha + at[channel] * destAlpha * keep) / outAlpha;
        at[channel] = (std::uint8_t)clampByte(value);
    }
    at[3] = (std::uint8_t)clampByte(outAlpha * 255.0);
}

void blit(RgbaImage& target, const RgbaImage& image, int x, int y) {
    for (unsigned row = 0; row < image.height; ++row) {
        const std::uint8_t* line = image.rgba.data() + (std::size_t)row * image.width * 4;
        for (unsigned column = 0; column < image.width; ++column)
            blendPixel(target, x + (int)column, y + (int)row, line + (std::size_t)column * 4);
    }
}

struct Box {
    unsigned x = 0, y = 0, w = 0, h = 0;
};

RgbaImage crop(const RgbaImage& image, Box box) {
    if (box.w == 0 || box.h == 0 || box.x + box.w > image.width || box.y + box.h > image.height)
        throw std::runtime_error("select art: a crop does not fit its picture");
    RgbaImage out = canvas(box.w, box.h);
    for (unsigned row = 0; row < box.h; ++row) {
        const std::uint8_t* from =
            image.rgba.data() + ((std::size_t)(box.y + row) * image.width + box.x) * 4;
        std::memcpy(out.rgba.data() + (std::size_t)row * box.w * 4, from, (std::size_t)box.w * 4);
    }
    return out;
}

// (x, y, w, h) of the non-transparent part, or the whole picture when it is empty.
Box alphaBounds(const RgbaImage& image) {
    unsigned left = image.width, top = image.height, right = 0, bottom = 0;
    bool found = false;
    for (unsigned y = 0; y < image.height; ++y)
        for (unsigned x = 0; x < image.width; ++x)
            if (image.rgba[((std::size_t)y * image.width + x) * 4 + 3] != 0) {
                left = std::min(left, x);
                top = std::min(top, y);
                right = std::max(right, x);
                bottom = std::max(bottom, y);
                found = true;
            }
    if (!found) return Box{0, 0, image.width, image.height};
    return Box{left, top, right - left + 1, bottom - top + 1};
}

// Drop isolated opaque texels. The roster icons carry a single white pixel in the cell's
// top-left corner — a marker, not art — and an alpha-bounds crop that includes it would scale
// the face into a quarter of the cell.
//
// The reference counts neighbours in the buffer it is already modifying, so a texel dropped
// earlier removes a neighbour for the texels after it. That is the filter's behaviour, and it
// is kept: the count is what the sheets were generated with.
RgbaImage denoiseAlpha(const RgbaImage& image) {
    RgbaImage out = image;
    for (unsigned y = 0; y < image.height; ++y)
        for (unsigned x = 0; x < image.width; ++x) {
            const std::size_t at = ((std::size_t)y * image.width + x) * 4;
            if (out.rgba[at + 3] == 0) continue;
            unsigned neighbours = 0;
            for (int dy = -1; dy <= 1; ++dy)
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dx == 0 && dy == 0) continue;
                    const int nx = (int)x + dx, ny = (int)y + dy;
                    if (nx < 0 || ny < 0 || (unsigned)nx >= image.width || (unsigned)ny >= image.height)
                        continue;
                    if (out.rgba[((std::size_t)ny * image.width + (unsigned)nx) * 4 + 3] != 0)
                        ++neighbours;
                }
            if (neighbours < 2) std::fill(out.rgba.begin() + (std::ptrdiff_t)at,
                                          out.rgba.begin() + (std::ptrdiff_t)at + 4, (std::uint8_t)0);
        }
    return out;
}

// Box-filter resample: one box average for both directions, which is what keeps an upscaled
// 176x132 portrait from turning into 2x2 blocks. Colours are averaged premultiplied by alpha and
// the alpha is the box's own mean, so an edge stays an edge.
RgbaImage scaled(const RgbaImage& image, unsigned width, unsigned height) {
    RgbaImage out = canvas(width, height);
    for (unsigned y = 0; y < height; ++y) {
        const unsigned y0 = y * image.height / height;
        const unsigned y1 = std::max(y0 + 1, (y + 1) * image.height / height);
        for (unsigned x = 0; x < width; ++x) {
            const unsigned x0 = x * image.width / width;
            const unsigned x1 = std::max(x0 + 1, (x + 1) * image.width / width);
            std::uint64_t red = 0, green = 0, blue = 0, alpha = 0, samples = 0;
            for (unsigned sy = y0; sy < y1; ++sy) {
                const std::uint8_t* line = image.rgba.data() + (std::size_t)sy * image.width * 4;
                for (unsigned sx = x0; sx < x1; ++sx) {
                    const std::uint8_t* src = line + (std::size_t)sx * 4;
                    const std::uint64_t a = src[3];
                    red += src[0] * a;
                    green += src[1] * a;
                    blue += src[2] * a;
                    alpha += a;
                    ++samples;
                }
            }
            if (alpha == 0) continue;
            std::uint8_t* dst = out.rgba.data() + ((std::size_t)y * width + x) * 4;
            dst[0] = (std::uint8_t)(red / alpha);
            dst[1] = (std::uint8_t)(green / alpha);
            dst[2] = (std::uint8_t)(blue / alpha);
            dst[3] = (std::uint8_t)(alpha / samples);
        }
    }
    return out;
}

// One cell's floor: the green diamond the PC's own 80x128 cells have, at the same place in the
// cell (centre y + 102, 25 rows tall), so a PSP icon stands where a PC chibi stands.
void drawFloor(RgbaImage& image, int x0, int y0) {
    const int centreX = x0 + (int)kCellWidth / 2;
    const int centreY = y0 + 102;
    const int halfWidth = ((int)kCellWidth - 4) / 2;
    constexpr int halfHeight = 25;
    for (int row = -halfHeight; row <= halfHeight; ++row) {
        const int span = (int)((1.0 - std::abs(row) / (double)halfHeight) * halfWidth);
        for (int column = -span; column <= span; ++column) {
            const bool edge = std::abs(row) >= halfHeight - 1 || std::abs(column) >= span - 1;
            putPixel(image, centreX + column, centreY + row, edge ? kFloorEdge : kFloorFill);
        }
    }
}

// 7-segment glyphs: enough for the slot letters (A-D) and the item id's digits, which is all a
// place-holder plate needs. Segments: a top, b top-right, c bottom-right, d bottom, e
// bottom-left, f top-left, g middle.
const char* segmentsOf(char character) {
    switch (character >= 'a' && character <= 'z' ? (char)(character - 'a' + 'A') : character) {
        case '0': return "abcdef";
        case '1': return "bc";
        case '2': return "abged";
        case '3': return "abgcd";
        case '4': return "fgbc";
        case '5': return "afgcd";
        case '6': return "afgecd";
        case '7': return "abc";
        case '8': return "abcdefg";
        case '9': return "abfgcd";
        case 'A': return "abcefg";
        case 'B': return "fgecd";
        case 'C': return "afed";
        case 'D': return "bged";
        case '-': return "g";
        default: return "";
    }
}

void drawSegmentText(RgbaImage& image, int x, int y, const std::string& text, int scale, Rgba colour) {
    struct Bar {
        char name;
        int x, y, w, h;
    };
    const Bar bars[] = {
        {'a', scale, 0, 3 * scale, scale},
        {'g', scale, 4 * scale, 3 * scale, scale},
        {'d', scale, 8 * scale, 3 * scale, scale},
        {'f', 0, scale, scale, 3 * scale},
        {'b', 4 * scale, scale, scale, 3 * scale},
        {'e', 0, 5 * scale, scale, 3 * scale},
        {'c', 4 * scale, 5 * scale, scale, 3 * scale},
    };
    int cursor = x;
    for (char character : text) {
        const std::string segments = segmentsOf(character);
        for (const Bar& bar : bars)
            if (segments.find(bar.name) != std::string::npos)
                fillRect(image, cursor + bar.x, y + bar.y, (unsigned)bar.w, (unsigned)bar.h, colour);
        cursor += 5 * scale + 2 * scale;
    }
}

// ---------------------------------------------------------------------------------------------
// The five sheets
// ---------------------------------------------------------------------------------------------

// data/select/NN.cnv: the vs_enter art, cropped to its own alpha bounds, undistorted, pasted
// bottom-centre — the pivot the select and VS screens draw a portrait from.
RgbaImage buildPortrait(const RgbaImage& art) {
    const RgbaImage subject = crop(art, alphaBounds(art));
    const double scale = std::min((double)kPortraitWidth / subject.width,
                                  (double)kPortraitHeight / subject.height);
    const unsigned width = std::max(1u, (unsigned)(subject.width * scale));
    const unsigned height = std::max(1u, (unsigned)(subject.height * scale));
    RgbaImage out = canvas(kPortraitWidth, kPortraitHeight);
    blit(out, scaled(subject, width, height), (int)((kPortraitWidth - width) / 2),
         (int)(kPortraitHeight - height));
    return out;
}

// One 80x128 cell: the face standing on the floor tile, its chin just above the tile's top
// vertex, the way a PC chibi stands on its own tile.
void chibiCell(RgbaImage& image, int cellX, int cellY, const RgbaImage& head) {
    drawFloor(image, cellX, cellY);
    const RgbaImage face = crop(head, alphaBounds(head));
    const double scale = std::min(kChibiFaceWidth / face.width, kChibiFaceHeight / face.height);
    const unsigned width = std::max(1u, (unsigned)(face.width * scale));
    const unsigned height = std::max(1u, (unsigned)(face.height * scale));
    blit(image, scaled(face, width, height), cellX + ((int)kCellWidth - (int)width) / 2,
         cellY + kChibiFaceBaseline - (int)height);
}

// data/select/iNN.cnv: the 3x2 grid the select screen walks. Cells (0,0) is the settled icon,
// (1,0) (2,0) (0,1) (1,1) the idle cycle a selected character animates, and (2,1) the 100 %
// opaque white cell the entry reveal flashes (screen_select.h's SelectChibiCell documents all
// six). The PSP has no chibi body, so each art cell is the character's own roster icon rather
// than a walk frame.
RgbaImage buildChibi(const RgbaImage& head) {
    RgbaImage out = canvas(kChibiWidth, kChibiHeight);
    for (int column = 0; column < 3; ++column)
        for (int row = 0; row < 2; ++row) {
            if (column == 2 && row == 1) continue;
            chibiCell(out, column * (int)kCellWidth, row * (int)kCellHeight, head);
        }
    fillRect(out, 2 * (int)kCellWidth, (int)kCellHeight, kCellWidth, kCellHeight, kWhite);
    return out;
}

// data/select/cosNN.cnv: one cell per costume, row-major from (0,0). The PSP ships no
// per-costume picture (its costume chooser is a text list), so every cell is the same roster
// icon. The COUNT is real — the PSP's chr17N/chr18N/chr19N model variants — which is what the
// screen's costume cycle and the launch's data/<dir>:<costume> need; only the picture is a
// place-holder.
RgbaImage buildCostumes(const RgbaImage& head, unsigned costumes) {
    if (costumes > 9) throw std::runtime_error("select art: " + std::to_string(costumes) +
                                               " costume cells do not fit the 3x3 sheet");
    RgbaImage out = canvas(kCostumeWidth, kCostumeHeight);
    for (unsigned index = 0; index < costumes; ++index)
        chibiCell(out, (int)(index % 3) * (int)kCellWidth, (int)(index / 3) * (int)kCellHeight, head);
    return out;
}

// data/win/NNa.cnv: the result screen's winner portrait, drawn whole at (144,60) in a 1v1 and at
// (-32,60)/(352,60) in a 2v2, never mirrored. The source is the RIGHT half of the bust-up — the
// PSP's second pose, smiling or eyes closed, a winning face for all three — cropped to its own
// alpha bounds and resized by ONE uniform factor so the figure is about the PC sheets' height,
// centred and standing on their baseline. Only the 'a' sheet: 'b' is the Rena/Rika weapon-2
// persona and no PSP fighter has one.
RgbaImage buildWin(const RgbaImage& sheet) {
    const unsigned half = sheet.width / 2;
    RgbaImage pose = crop(sheet, Box{half, 0, sheet.width - half, sheet.height});
    pose = crop(pose, alphaBounds(pose));
    const double scale = std::min((double)kWinFigureHeight / pose.height,
                                  (double)(kWinWidth - 16) / pose.width);
    const unsigned width = std::max(1u, (unsigned)std::nearbyint(pose.width * scale));
    const unsigned height = std::max(1u, (unsigned)std::nearbyint(pose.height * scale));
    RgbaImage out = canvas(kWinWidth, kWinHeight);
    blit(out, scaled(pose, width, height), (int)((kWinWidth - width) / 2),
         (int)(kWinBottom - height));
    return out;
}

// data/select/wNN.cnv: four rows of 256x64, two columns of 256x64. The screen reads
// (0, row*64, 256, 64) for the row list and (256, row*64, 256, 64) for the plate under it —
// where the PC sheets hold the weapon's name and its description. The PSP has neither per
// weapon (its chooser is a text list), so this is a place-holder: the slot letter in the left
// column and the item id the launch will request in the right, so the four slots are at least
// distinguishable and traceable to their data.
RgbaImage buildWeapons(unsigned itemFirst) {
    RgbaImage out = canvas(kWeaponWidth, kWeaponHeight);
    for (unsigned row = 0; row < kWeaponHeight / kWeaponRowHeight; ++row) {
        const int y = (int)(row * kWeaponRowHeight);
        for (unsigned column = 0; column < kWeaponColumns; ++column) {
            const int x = (int)(column * kWeaponColumnWidth);
            // Inset plate with a two-tone border, so a missing sheet is not mistaken for this.
            fillRect(out, x + 8, y + 6, 240, 52, kPlateFill);
            fillRect(out, x + 8, y + 6, 240, 2, kPlateBorder);
            fillRect(out, x + 8, y + 56, 240, 2, kPlateBorder);
            fillRect(out, x + 8, y + 6, 2, 52, kPlateBorder);
            fillRect(out, x + 246, y + 6, 2, 52, kPlateBorder);
        }
        const std::string letter(1, (char)('A' + row));
        drawSegmentText(out, 8 + 16, y + 14, letter, 4, kPlateText);
        drawSegmentText(out, 256 + 8 + 16, y + 14, std::to_string(itemFirst + row), 4, kPlateText);
    }
    return out;
}

// ---------------------------------------------------------------------------------------------
// Files
// ---------------------------------------------------------------------------------------------
std::string joinPath(const std::string& directory, const std::string& rest) {
    if (directory.empty()) return rest;
    const char last = directory.back();
    return (last == '/' || last == '\\') ? directory + rest : directory + "/" + rest;
}

std::vector<std::uint8_t> readBytes(const std::string& path) {
    std::ifstream stream(fs::u8path(path), std::ios::binary);
    if (!stream) throw std::runtime_error("cannot read " + path);
    std::vector<std::uint8_t> bytes((std::istreambuf_iterator<char>(stream)),
                                    std::istreambuf_iterator<char>());
    if (bytes.empty()) throw std::runtime_error(path + " is empty");
    return bytes;
}

void writeBytes(const std::string& path, const std::vector<std::uint8_t>& bytes) {
    const fs::path file = fs::u8path(path);
    std::error_code error;
    if (!file.parent_path().empty()) fs::create_directories(file.parent_path(), error);
    std::ofstream stream(file, std::ios::binary | std::ios::trunc);
    if (!stream) throw std::runtime_error("cannot write " + path);
    stream.write(reinterpret_cast<const char*>(bytes.data()), (std::streamsize)bytes.size());
    if (!stream) throw std::runtime_error("cannot write " + path);
}

std::string numbered(const char* pattern, unsigned index) {
    char buffer[64];
    std::snprintf(buffer, sizeof buffer, pattern, index);
    return buffer;
}

// The first picture of one raw GIM. Every select-family file holds one image; the reader
// reports every picture it finds (the head atlas holds each of its ten twice), so the caller
// picks.
RgbaImage firstPicture(const std::string& dataDir, const std::string& path) {
    const std::vector<RgbaImage> pictures = decodeGim(readBytes(pspRawPath(dataDir, path)));
    if (pictures.empty()) throw std::runtime_error("select art: " + path + " holds no picture");
    return pictures.front();
}

// The character's own 48x48 head icon. The sheet is packed in PSP roster order, which is the
// port's roster order for exactly these three: they are the PSP's 17th, 18th and 19th fighters,
// and D-1 put them at indices 16..18, so the icon index and the roster index are the same
// number. The PC sixteen's indices do NOT address this sheet, and nothing else may assume they
// do.
RgbaImage iconCell(const RgbaImage& sheet, unsigned index) {
    if (index >= kIconColumns * kIconRows)
        throw std::runtime_error("select art: roster index " + std::to_string(index) +
                                 " is outside the icon sheet");
    const unsigned x = (index % kIconColumns) * kIconCell;
    const unsigned y = (index / kIconColumns) * kIconCell;
    if (x + kIconCell > sheet.width || y + kIconCell > sheet.height)
        throw std::runtime_error("select art: the icon cell is outside the sheet");
    return crop(sheet, Box{x, y, kIconCell, kIconCell});
}

unsigned costumeCount(const std::string& name) {
    for (const PspFighter& fighter : pspFighters())
        if (fighter.name == name) return (unsigned)fighter.costumes.size();
    throw std::runtime_error("select art: no costume list for " + name);
}

void writeSheet(const std::string& dataDir, std::ostream& log, std::vector<std::string>& written,
                const std::string& relative, const RgbaImage& image, const std::string& source) {
    const std::vector<std::uint8_t> cnv = encodeCnv(image);
    writeBytes(joinPath(dataDir, relative), cnv);
    written.push_back(relative);
    log << "psp: " << relative << ' ' << image.width << 'x' << image.height << " <- " << source
        << '\n';
}

}  // namespace

std::vector<std::string> convertPspSelectArt(const std::string& dataDir, std::ostream& log) {
    std::vector<std::string> written;
    const std::string iconSheet = "gra/gim/select/icon_on.gim";
    const RgbaImage icons = firstPicture(dataDir, iconSheet);
    for (unsigned slot = 0; slot < daybreak::psp_character_names.size(); ++slot) {
        const unsigned index = daybreak::psp_character_first + slot;
        const std::string name(daybreak::psp_character_name(index));
        const std::string portraitSheet = "gra/gim/select/vs_enter_" + name + ".gim";
        const std::string bustupSheet = "gra/gim/select/bustup_" + name + ".gim";
        // denoiseAlpha runs on the icon cell, not on the whole sheet: the specks it drops are
        // inside a cell, and a cell's edge also borders another character's.
        const RgbaImage head = denoiseAlpha(iconCell(icons, index));
        const std::string iconCellName = iconSheet + " cell " + std::to_string(index);
        const unsigned costumes = costumeCount(name);
        const unsigned itemFirst = daybreak::psp_item_id(index, 0);

        writeSheet(dataDir, log, written, numbered("data/select/%02u.cnv", index),
                   buildPortrait(firstPicture(dataDir, portraitSheet)), portraitSheet);
        writeSheet(dataDir, log, written, numbered("data/select/i%02u.cnv", index),
                   buildChibi(head),
                   iconCellName + " (place-holder: the PSP ships no chibi art)");
        writeSheet(dataDir, log, written, numbered("data/select/cos%02u.cnv", index),
                   buildCostumes(head, costumes),
                   iconCellName + " x " + std::to_string(costumes) +
                       " costume cells (place-holder: the PSP ships no per-costume art)");
        writeSheet(dataDir, log, written, numbered("data/select/w%02u.cnv", index),
                   buildWeapons(itemFirst),
                   "place-holder plate: slot letters A-D and item ids " +
                       std::to_string(itemFirst) + ".." +
                       std::to_string(daybreak::psp_item_id(index, 3)) +
                       " (the PSP ships no per-weapon art)");
        writeSheet(dataDir, log, written, numbered("data/win/%02ua.cnv", index),
                   buildWin(firstPicture(dataDir, bustupSheet)),
                   bustupSheet + " right half (the smiling pose)");
    }
    return written;
}

}  // namespace psp
