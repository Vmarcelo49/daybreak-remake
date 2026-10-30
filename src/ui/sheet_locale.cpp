#include "ui/sheet_locale.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <map>
#include <sstream>

#include <SDL3/SDL.h>

#include "ui/caption.h"
#include "ui/text.h"

namespace ui {
namespace {

constexpr const char* kFontFile = "Goldman-Bold.ttf";
constexpr float kRasterCell = 96.f;
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
TextLayer gLayer;

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

Mask rasterLine(const std::string& line) {
    const TextLayout layout = gLayer.layout(line.c_str());
    std::vector<GlyphQuad> quads;
    const int margin = 8;
    gLayer.buildQuads(layout, 0.f, 0.f, 1.f, quads);
    float right = 0.f, top = 1e9f, bottom = -1e9f;
    for (const GlyphQuad& q : quads) {
        right = std::max(right, q.x + q.w);
        top = std::min(top, q.y);
        bottom = std::max(bottom, q.y + q.h);
    }
    Mask out;
    if (quads.empty()) return out;
    const float height = bottom - top;
    const int lean = static_cast<int>(std::ceil(kShear * height));
    out.w = static_cast<int>(std::ceil(right)) + lean + margin * 2;
    out.h = static_cast<int>(std::ceil(height)) + margin * 2;
    out.a.assign(static_cast<size_t>(out.w) * out.h, 0.f);
    const std::vector<uint8_t>& atlas = gLayer.atlasRGBA();
    const int aw = gLayer.atlasWidth(), ah = gLayer.atlasHeight();
    for (const GlyphQuad& q : quads) {
        const int gw = static_cast<int>(std::lround(q.w)), gh = static_cast<int>(std::lround(q.h));
        const int ax = static_cast<int>(std::lround(q.u0 * aw)), ay = static_cast<int>(std::lround(q.v0 * ah));
        for (int y = 0; y < gh; ++y) {
            const float yFromBottom = bottom - (q.y + y);
            const int dy = static_cast<int>(std::lround(q.y + y - top)) + margin;
            const int shift = static_cast<int>(std::lround(kShear * yFromBottom));
            for (int x = 0; x < gw; ++x) {
                const int dx = static_cast<int>(std::lround(q.x)) + x + shift + margin;
                if (dx < 0 || dx >= out.w || dy < 0 || dy >= out.h) continue;
                const size_t from = (static_cast<size_t>(ay + y) * aw + (ax + x)) * 4 + 3;
                float& to = out.a[static_cast<size_t>(dy) * out.w + dx];
                to = std::max(to, atlas[from] / 255.f);
            }
        }
    }
    return out;
}

// Area average: the raster is always larger than the label.
std::vector<float> shrink(const Mask& m, int w, int h) {
    std::vector<float> out(static_cast<size_t>(w) * h, 0.f);
    for (int y = 0; y < h; ++y) {
        const int y0 = y * m.h / h, y1 = std::max(y0 + 1, (y + 1) * m.h / h);
        for (int x = 0; x < w; ++x) {
            const int x0 = x * m.w / w, x1 = std::max(x0 + 1, (x + 1) * m.w / w);
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

void paintLabel(const SheetLabel& label, const Style& style, uint8_t* rgba, int width, int height) {
    eraseRect(label, style.erase, rgba, width, height);
    const std::vector<std::string> lines = splitLines(label.text);
    const float rowHeight = label.h * style.fillRatio / static_cast<float>(lines.size());
    for (size_t row = 0; row < lines.size(); ++row) {
        const Mask raster = rasterLine(lines[row]);
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
    return loadCaptionFont(gLayer, kRasterCell, error, kFontFile, nullptr);
}

void localizeSheet(const std::string& stem, uint8_t* rgba, int width, int height) {
    if (gLabels.empty()) return;
    const std::string key = lowered(stem);
    for (const SheetLabel& label : gLabels)
        if (label.sheet == key) paintLabel(label, kStyles.at(label.style), rgba, width, height);
}

}  // namespace ui
