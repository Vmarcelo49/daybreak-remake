#include "ui/sheet_locale.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <map>
#include <sstream>

#include <SDL3/SDL.h>

// STBTT_STATIC, as in text.cpp: each user keeps its own private copy of the vendor symbols.
#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#include "ui/text.h"

namespace ui {
namespace {

constexpr const char* kFontFile = "Goldman-Bold.ttf";
// A label rasterises at the smallest of these that covers it, and each glyph only once per size:
// the select screen alone has hundreds of labels, and it is built on every entry.
constexpr int kRasterEms[] = {96, 192, 384, 768};
constexpr float kShear = 0.25f;  // Goldman has no italic; the game's lettering leans this way

struct Rgb { float r, g, b; };
enum class Erase { Clear, Patch, Dark };
struct Style {
    Rgb top, bottom;
    float alpha;       // of the whole label: the dim state of a row
    float outline;     // black, in pixels, at a 32 px cap height; it scales with the label
    float edge;        // white, outside the outline
    float fillRatio;   // of the rect's height the text may take
    Erase erase;
    int align;         // -1 left, 0 centre, 1 right
};

const std::map<std::string, Style> kStyles = {
    {"label",  {{1, 1, 1}, {0.78f, 0.82f, 0.95f}, 1.f, 2.f, 1.2f, 0.62f, Erase::Clear, 0}},
    {"dim",    {{0.55f, 0.55f, 0.58f}, {0.4f, 0.4f, 0.44f}, 1.f, 2.f, 0.6f, 0.62f, Erase::Clear, 0}},
    {"gold",   {{1, 0.92f, 0.4f}, {1, 0.62f, 0.05f}, 1.f, 2.f, 0.8f, 0.62f, Erase::Clear, 0}},
    {"menu",   {{1, 1, 1}, {0.78f, 0.82f, 0.95f}, 1.f, 2.f, 1.2f, 1.0f, Erase::Clear, 0}},
    {"menudim", {{0.55f, 0.55f, 0.58f}, {0.4f, 0.4f, 0.44f}, 1.f, 2.f, 0.6f, 1.0f, Erase::Clear, 0}},
    {"left",   {{1, 1, 1}, {0.78f, 0.82f, 0.95f}, 1.f, 2.f, 1.2f, 0.72f, Erase::Clear, -1}},
    {"right",  {{1, 1, 1}, {0.78f, 0.82f, 0.95f}, 1.f, 2.f, 1.2f, 0.72f, Erase::Clear, 1}},
    {"small",  {{1, 1, 1}, {0.92f, 0.92f, 0.96f}, 1.f, 1.2f, 0.5f, 0.84f, Erase::Clear, 0}},
    {"blue",   {{0.55f, 0.65f, 1}, {0.05f, 0.1f, 0.85f}, 1.f, 2.f, 1.2f, 0.62f, Erase::Clear, 0}},
    {"red",    {{1, 0.5f, 0.45f}, {0.8f, 0.02f, 0.02f}, 1.f, 2.f, 1.2f, 0.62f, Erase::Clear, 0}},
    {"bluedim", {{0.25f, 0.3f, 0.55f}, {0.05f, 0.08f, 0.4f}, 1.f, 2.f, 0.5f, 0.62f, Erase::Clear, 0}},
    {"reddim", {{0.55f, 0.25f, 0.22f}, {0.4f, 0.03f, 0.03f}, 1.f, 2.f, 0.5f, 0.62f, Erase::Clear, 0}},
    {"sting",  {{1, 0.95f, 0.3f}, {0.9f, 0.05f, 0}, 1.f, 3.f, 1.6f, 0.42f, Erase::Clear, 0}},
    {"bluesting", {{0.65f, 0.75f, 1}, {0.05f, 0.1f, 0.9f}, 1.f, 3.f, 1.6f, 0.42f, Erase::Clear, 0}},
    {"redsting", {{1, 0.55f, 0.5f}, {0.85f, 0.02f, 0.02f}, 1.f, 3.f, 1.6f, 0.42f, Erase::Clear, 0}},
    {"tag",    {{1, 1, 1}, {0.85f, 0.85f, 0.9f}, 1.f, 1.f, 0.f, 0.86f, Erase::Dark, 0}},
    {"patch",  {{1, 1, 1}, {0.85f, 0.88f, 0.98f}, 1.f, 2.f, 0.6f, 0.68f, Erase::Patch, 0}},
    {"patchblue", {{0.75f, 0.85f, 1}, {0.2f, 0.4f, 1}, 1.f, 2.f, 1.2f, 0.7f, Erase::Patch, 0}},
    {"patchred", {{1, 0.8f, 0.6f}, {1, 0.25f, 0.1f}, 1.f, 2.f, 1.2f, 0.7f, Erase::Patch, 0}},
    {"patchleft", {{1, 1, 1}, {0.85f, 0.88f, 0.98f}, 1.f, 1.6f, 0.4f, 0.6f, Erase::Patch, -1}},
};

std::vector<SheetLabel> gLabels;
std::string gLanguage;
std::vector<uint8_t> gFontBytes;
stbtt_fontinfo gFont;

struct Glyph {
    int w = 0, h = 0, offsetX = 0, offsetY = 0, advance = 0;
    std::vector<uint8_t> coverage;
};
std::map<std::pair<int, char>, Glyph> gGlyphs;

const Glyph& glyphAt(int em, char c) {
    const auto key = std::make_pair(em, c);
    const auto found = gGlyphs.find(key);
    if (found != gGlyphs.end()) return found->second;
    Glyph glyph;
    const float scale = stbtt_ScaleForPixelHeight(&gFont, static_cast<float>(em));
    unsigned char* bitmap = stbtt_GetCodepointBitmap(&gFont, 0, scale, c, &glyph.w, &glyph.h, &glyph.offsetX, &glyph.offsetY);
    if (bitmap) glyph.coverage.assign(bitmap, bitmap + static_cast<size_t>(glyph.w) * glyph.h);
    stbtt_FreeBitmap(bitmap, nullptr);
    stbtt_GetCodepointHMetrics(&gFont, c, &glyph.advance, nullptr);
    return gGlyphs.emplace(key, std::move(glyph)).first->second;
}

std::string lowered(std::string text) {
    for (char& c : text)
        if (c >= 'A' && c <= 'Z') c = static_cast<char>(c - 'A' + 'a');
    return text;
}

std::vector<std::string> splitLines(const std::string& text) {
    std::vector<std::string> lines(1);
    for (size_t i = 0; i < text.size(); ++i) {
        if (text[i] == '\\' && i + 1 < text.size() && text[i + 1] == 'n') {
            lines.emplace_back();
            ++i;
        } else {
            lines.back() += text[i];
        }
    }
    return lines;
}

// One line of text as coverage at the raster size, with the lean applied.
struct Mask { int w = 0, h = 0; std::vector<float> a; };

Mask rasterLine(const std::string& line, float targetHeight) {
    int ascent = 0, descent = 0, gap = 0;
    stbtt_GetFontVMetrics(&gFont, &ascent, &descent, &gap);
    int em = kRasterEms[0];
    for (int candidate : kRasterEms) {
        em = candidate;
        if (static_cast<float>(em) >= targetHeight * 1.5f) break;
    }
    const float scale = stbtt_ScaleForPixelHeight(&gFont, static_cast<float>(em));
    const int baseline = static_cast<int>(std::ceil(ascent * scale));
    const int height = static_cast<int>(std::ceil((ascent - descent) * scale));

    // The labels are ASCII: the translated text never needs another face.
    const auto kern = [&](size_t i) {
        return i + 1 < line.size() ? stbtt_GetCodepointKernAdvance(&gFont, line[i], line[i + 1]) * scale : 0.f;
    };
    float pen = 0.f;
    for (size_t i = 0; i < line.size(); ++i) pen += glyphAt(em, line[i]).advance * scale + kern(i);
    Mask out;
    if (line.empty()) return out;
    const int margin = em / 32;
    const int lean = static_cast<int>(std::ceil(kShear * height));
    out.w = static_cast<int>(std::ceil(pen)) + lean + margin * 2;
    out.h = height + margin * 2;
    out.a.assign(static_cast<size_t>(out.w) * out.h, 0.f);
    pen = 0.f;
    for (size_t i = 0; i < line.size(); ++i) {
        const Glyph& glyph = glyphAt(em, line[i]);
        for (int y = 0; y < glyph.h; ++y) {
            const int row = baseline + glyph.offsetY + y;
            const int dy = row + margin;
            if (dy < 0 || dy >= out.h) continue;
            const int dxStart = static_cast<int>(std::lround(pen + glyph.offsetX + kShear * static_cast<float>(height - row))) + margin;
            float* to = out.a.data() + static_cast<size_t>(dy) * out.w;
            const uint8_t* from = glyph.coverage.data() + static_cast<size_t>(y) * glyph.w;
            for (int x = 0; x < glyph.w; ++x) {
                const int dx = dxStart + x;
                if (dx >= 0 && dx < out.w && from[x]) to[dx] = std::max(to[dx], from[x] / 255.f);
            }
        }
        pen += glyph.advance * scale + kern(i);
    }
    return out;
}

// Area average: the raster is larger than any label on a 4x sheet.
std::vector<float> shrink(const Mask& m, int w, int h) {
    std::vector<float> out(static_cast<size_t>(w) * h, 0.f);
    for (int y = 0; y < h; ++y) {
        const int y0 = static_cast<int>(static_cast<int64_t>(y) * m.h / h);
        const int y1 = std::max(y0 + 1, static_cast<int>(static_cast<int64_t>(y + 1) * m.h / h));
        for (int x = 0; x < w; ++x) {
            const int x0 = static_cast<int>(static_cast<int64_t>(x) * m.w / w);
            const int x1 = std::max(x0 + 1, static_cast<int>(static_cast<int64_t>(x + 1) * m.w / w));
            float sum = 0.f;
            for (int sy = y0; sy < y1 && sy < m.h; ++sy)
                for (int sx = x0; sx < x1 && sx < m.w; ++sx) sum += m.a[static_cast<size_t>(sy) * m.w + sx];
            out[static_cast<size_t>(y) * w + x] = sum / static_cast<float>((y1 - y0) * (x1 - x0));
        }
    }
    return out;
}

// Chamfer distance, in pixels, from each pixel to the coverage.
std::vector<float> distanceTo(const std::vector<float>& a, int w, int h) {
    constexpr float kOrtho = 1.f, kDiagonal = 1.414f, kFar = 1e6f;
    std::vector<float> d(a.size());
    for (size_t i = 0; i < a.size(); ++i) d[i] = a[i] >= 0.5f ? 0.f : kFar;
    const auto at = [&](int x, int y) -> float {
        return x < 0 || y < 0 || x >= w || y >= h ? kFar : d[static_cast<size_t>(y) * w + x];
    };
    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x) {
            float& v = d[static_cast<size_t>(y) * w + x];
            v = std::min({v, at(x - 1, y) + kOrtho, at(x, y - 1) + kOrtho, at(x - 1, y - 1) + kDiagonal, at(x + 1, y - 1) + kDiagonal});
        }
    for (int y = h - 1; y >= 0; --y)
        for (int x = w - 1; x >= 0; --x) {
            float& v = d[static_cast<size_t>(y) * w + x];
            v = std::min({v, at(x + 1, y) + kOrtho, at(x, y + 1) + kOrtho, at(x + 1, y + 1) + kDiagonal, at(x - 1, y + 1) + kDiagonal});
        }
    return d;
}

void blend(uint8_t* p, Rgb c, float alpha) {
    const float below = p[3] / 255.f;
    const float out = alpha + below * (1.f - alpha);
    if (out <= 0.f) return;
    const auto mix = [&](float front, uint8_t back) {
        return static_cast<uint8_t>(std::lround(std::clamp((front * alpha + back / 255.f * below * (1.f - alpha)) / out, 0.f, 1.f) * 255.f));
    };
    p[0] = mix(c.r, p[0]);
    p[1] = mix(c.g, p[1]);
    p[2] = mix(c.b, p[2]);
    p[3] = static_cast<uint8_t>(std::lround(out * 255.f));
}

void eraseRect(const SheetLabel& label, Erase mode, uint8_t* rgba, int width, int height) {
    const int x0 = std::max(0, label.x), y0 = std::max(0, label.y);
    const int x1 = std::min(width, label.x + label.w), y1 = std::min(height, label.y + label.h);
    for (int x = x0; x < x1; ++x) {
        // Patch: a background photo has no transparent state, so it blends across the hole.
        const uint8_t* above = rgba + (static_cast<size_t>(std::max(0, y0 - 1)) * width + x) * 4;
        const uint8_t* below = rgba + (static_cast<size_t>(std::min(height - 1, y1)) * width + x) * 4;
        for (int y = y0; y < y1; ++y) {
            uint8_t* p = rgba + (static_cast<size_t>(y) * width + x) * 4;
            if (mode == Erase::Clear) {
                p[3] = 0;
            } else if (mode == Erase::Dark) {
                p[0] = p[1] = p[2] = 16;
            } else {
                const float t = (y - y0 + 1.f) / (y1 - y0 + 1.f);
                for (int c = 0; c < 4; ++c) p[c] = static_cast<uint8_t>(std::lround(above[c] * (1.f - t) + below[c] * t));
            }
        }
    }
}

void paintLabel(SheetLabel label, const Style& style, int scale, uint8_t* rgba, int width, int height) {
    label.x *= scale;
    label.y *= scale;
    label.w *= scale;
    label.h *= scale;
    eraseRect(label, style.erase, rgba, width, height);
    const std::vector<std::string> lines = splitLines(label.text);
    const float rowHeight = label.h * style.fillRatio / static_cast<float>(lines.size());
    for (size_t row = 0; row < lines.size(); ++row) {
        const Mask raster = rasterLine(lines[row], rowHeight);
        if (raster.a.empty()) continue;
        // The natural size, narrowed before it is shrunk: a long label stays tall enough to read.
        constexpr float kMinimumSqueeze = 0.68f;
        const float pad = std::max(2.f, label.h * 0.06f);
        const float room = std::max(4.f, label.w - pad * 2.f);
        const float scale = rowHeight / static_cast<float>(raster.h);
        float scaleX = scale, scaleY = scale;
        const float natural = raster.w * scale;
        if (natural > room) {
            scaleX = room / raster.w;
            if (scaleX < scale * kMinimumSqueeze) scaleY = scaleX / kMinimumSqueeze;
        }
        const int w = std::max(1, static_cast<int>(std::lround(raster.w * scaleX)));
        const int h = std::max(1, static_cast<int>(std::lround(raster.h * scaleY)));
        const std::vector<float> cover = shrink(raster, w, h);
        const std::vector<float> distance = distanceTo(cover, w, h);

        const float unit = h / 32.f;
        const float outline = std::max(0.8f, style.outline * unit);
        const float edge = style.edge * unit;
        const int blockTop = label.y + static_cast<int>((label.h - rowHeight * lines.size()) / 2.f);
        const int top = blockTop + static_cast<int>(row * rowHeight + (rowHeight - h) / 2.f);
        const int left = style.align < 0 ? label.x + static_cast<int>(pad)
                       : style.align > 0 ? label.x + label.w - w - static_cast<int>(pad)
                                         : label.x + (label.w - w) / 2;
        const int reach = static_cast<int>(std::ceil(outline + edge + 2.f));
        for (int y = -reach; y < h + reach; ++y) {
            const int dy = top + y;
            if (dy < label.y || dy < 0 || dy >= label.y + label.h || dy >= height) continue;
            const float v = std::clamp(y / static_cast<float>(h), 0.f, 1.f);
            const Rgb fill{style.top.r + (style.bottom.r - style.top.r) * v,
                           style.top.g + (style.bottom.g - style.top.g) * v,
                           style.top.b + (style.bottom.b - style.top.b) * v};
            for (int x = -reach; x < w + reach; ++x) {
                const int dx = left + x;
                if (dx < label.x || dx < 0 || dx >= label.x + label.w || dx >= width) continue;
                float cov = 0.f, dist = 1e6f;
                if (x >= 0 && y >= 0 && x < w && y < h) {
                    const size_t i = static_cast<size_t>(y) * w + x;
                    cov = cover[i];
                    dist = distance[i];
                } else {
                    // Outside the mask: the distance to its nearest edge pixel.
                    const int cx = std::clamp(x, 0, w - 1), cy = std::clamp(y, 0, h - 1);
                    dist = distance[static_cast<size_t>(cy) * w + cx] + std::hypot(static_cast<float>(x - cx), static_cast<float>(y - cy));
                }
                uint8_t* p = rgba + (static_cast<size_t>(dy) * width + dx) * 4;
                if (edge > 0.f) blend(p, {1, 1, 1}, std::clamp(outline + edge + 0.5f - dist, 0.f, 1.f) * style.alpha);
                blend(p, {0, 0, 0}, std::clamp(outline + 0.5f - dist, 0.f, 1.f) * style.alpha);
                blend(p, fill, cov * style.alpha);
            }
        }
    }
}

// What the GPU's linear filter would show, so the art beside a label looks as it did. Sheets are
// mostly transparent once their labels are cleared, so those pixels take the early exit.
std::vector<uint8_t> enlarged(const uint8_t* rgba, int width, int height, int scale) {
    constexpr int kFraction = 256;
    const int w = width * scale, h = height * scale;
    std::vector<uint8_t> out(static_cast<size_t>(w) * h * 4, 0);
    struct Sample { int low, high, weight; };
    const auto samples = [scale](int size) {
        std::vector<Sample> table(static_cast<size_t>(size) * scale);
        for (int i = 0; i < size * scale; ++i) {
            const float at = std::max(0.f, (i + 0.5f) / scale - 0.5f);
            const int low = std::min(size - 1, static_cast<int>(at));
            table[i] = {low, std::min(size - 1, low + 1), static_cast<int>((at - low) * kFraction)};
        }
        return table;
    };
    const std::vector<Sample> columns = samples(width), rows = samples(height);
    for (int y = 0; y < h; ++y) {
        const Sample& sy = rows[y];
        const uint8_t* lowRow = rgba + static_cast<size_t>(sy.low) * width * 4;
        const uint8_t* highRow = rgba + static_cast<size_t>(sy.high) * width * 4;
        uint8_t* p = out.data() + static_cast<size_t>(y) * w * 4;
        for (int x = 0; x < w; ++x, p += 4) {
            const Sample& sx = columns[x];
            const uint8_t* c00 = lowRow + sx.low * 4;
            const uint8_t* c10 = lowRow + sx.high * 4;
            const uint8_t* c01 = highRow + sx.low * 4;
            const uint8_t* c11 = highRow + sx.high * 4;
            if (!(c00[3] | c10[3] | c01[3] | c11[3])) continue;
            const int w00 = (kFraction - sx.weight) * (kFraction - sy.weight), w10 = sx.weight * (kFraction - sy.weight);
            const int w01 = (kFraction - sx.weight) * sy.weight, w11 = sx.weight * sy.weight;
            const int64_t a00 = w00 * c00[3], a10 = w10 * c10[3], a01 = w01 * c01[3], a11 = w11 * c11[3];
            const int64_t alpha = a00 + a10 + a01 + a11;
            if (alpha <= 0) continue;
            for (int c = 0; c < 3; ++c) p[c] = static_cast<uint8_t>((a00 * c00[c] + a10 * c10[c] + a01 * c01[c] + a11 * c11[c]) / alpha);
            p[3] = static_cast<uint8_t>(alpha / (kFraction * kFraction));
        }
    }
    return out;
}

// Four times the sheet where the labels are large. The select screen loads sixteen weapon sheets and
// two full-screen photos on every entry, and at 4x those alone cost a second and over 400 MB.
int sheetScale(const std::string& key, int width) {
    constexpr int kFull = 4, kLight = 2;
    if (width > 512) return kLight;
    return key.rfind("data/select/w", 0) == 0 ? kLight : kFull;
}

std::vector<uint8_t> readFontFile(const char* name) {
    std::vector<std::string> paths;
    for (auto roots = fontSearchRoots(); *roots; ++roots) paths.push_back(std::string(*roots) + name);
    if (const char* base = SDL_GetBasePath()) paths.push_back(std::string(base) + "assets/fonts/" + name);
    for (const std::string& path : paths) {
        std::ifstream file(std::filesystem::u8path(path), std::ios::binary);
        if (file) return {std::istreambuf_iterator<char>(file), {}};
    }
    return {};
}

std::string readLocaleFile(const std::string& name) {
    std::vector<std::string> paths = {"assets/locale/" + name};
    if (const char* base = SDL_GetBasePath()) paths.push_back(std::string(base) + "assets/locale/" + name);
    for (const std::string& path : paths) {
        std::ifstream file(std::filesystem::u8path(path), std::ios::binary);
        if (file) return {std::istreambuf_iterator<char>(file), {}};
    }
    return {};
}

}  // namespace

std::vector<SheetLabel> parseSheetLabels(const std::string& text, std::string& error) {
    std::vector<SheetLabel> labels;
    std::istringstream lines(text);
    std::string line;
    int number = 0;
    const auto trim = [](std::string s) {
        const size_t a = s.find_first_not_of(" \t\r"), b = s.find_last_not_of(" \t\r");
        return a == std::string::npos ? std::string() : s.substr(a, b - a + 1);
    };
    while (std::getline(lines, line)) {
        ++number;
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;
        const size_t a = line.find('|'), b = line.find('|', a + 1), c = line.find('|', b + 1);
        SheetLabel label;
        if (a != std::string::npos && b != std::string::npos && c != std::string::npos) {
            label.sheet = lowered(trim(line.substr(0, a)));
            label.style = trim(line.substr(b + 1, c - b - 1));
            label.text = trim(line.substr(c + 1));
            std::istringstream rect(line.substr(a + 1, b - a - 1));
            rect >> label.x >> label.y >> label.w >> label.h;
            if (rect && !label.sheet.empty()) {
                labels.push_back(std::move(label));
                continue;
            }
        }
        if (error.empty()) error = "line " + std::to_string(number) + ": expected sheet | x y w h | style | text";
    }
    return labels;
}

bool setSheetLanguage(const std::string& language, std::string& error) {
    if (language.empty() || language == "ja") {
        gLabels.clear();
        gLanguage.clear();
        return true;
    }
    const std::string text = readLocaleFile(language + ".txt");
    if (text.empty()) {
        error = "no translation found at assets/locale/" + language + ".txt";
        return false;
    }
    std::string failure;
    gLabels = parseSheetLabels(text, failure);
    if (!failure.empty()) {
        error = language + ".txt, " + failure;
        return false;
    }
    for (const SheetLabel& label : gLabels)
        if (!kStyles.count(label.style)) {
            error = language + ".txt: unknown style " + label.style;
            return false;
        }
    gFontBytes = readFontFile(kFontFile);
    if (gFontBytes.empty() || !stbtt_InitFont(&gFont, gFontBytes.data(), 0)) {
        error = std::string("cannot read ") + kFontFile + " from assets/fonts";
        return false;
    }
    gLanguage = language;
    return true;
}

const std::string& sheetLanguage() { return gLanguage; }

bool localizeSheet(const std::string& stem, const uint8_t* rgba, int width, int height, LocalizedSheet& out) {
    const std::string key = lowered(stem);
    const auto named = [&](const SheetLabel& label) { return label.sheet == key; };
    if (std::none_of(gLabels.begin(), gLabels.end(), named)) return false;
    const int scale = sheetScale(key, width);
    out.width = width * scale;
    out.height = height * scale;
    // Clearing a label before enlarging saves the work on pixels it would throw away.
    std::vector<uint8_t> source(rgba, rgba + static_cast<size_t>(width) * height * 4);
    for (const SheetLabel& label : gLabels)
        if (named(label) && kStyles.at(label.style).erase == Erase::Clear) eraseRect(label, Erase::Clear, source.data(), width, height);
    out.rgba = enlarged(source.data(), width, height, scale);
    for (const SheetLabel& label : gLabels)
        if (named(label)) paintLabel(label, kStyles.at(label.style), scale, out.rgba.data(), out.width, out.height);
    return true;
}

}  // namespace ui
