// =============================================================================
//  text_test.cpp — host parity test for the CJK text layer (ui/text.h).
//
//  Device-free: no WebGPU, no window, no SDL. It needs ONE file at run time, the
//  fetched Japanese font (docs/CJK-TEXT.md §5, option B) — and it SKIPS cleanly, exit
//  0, when that file is absent, the way tests/dat_bundle_bytes.cpp skips without an
//  install:
//
//      ./text_test                                   # $FOUNDATION_CJK_FONT, else the
//                                                    # third_party/fonts/ default
//      FOUNDATION_CJK_FONT=/tmp/font.otf ./text_test
//      ./text_test /tmp/font.otf                     # explicit
//
//  What it proves:
//   1. Glyph rasterization — a set of code points including CJK (`適当` and friends)
//      produces non-empty coverage, boxes inside the font's metrics, and the SAME bytes
//      from a second layer in the same process. The rasterizer is order-independent;
//      the packing is a pure function of the request sequence.
//   2. `\c` colour-code parsing — exact colour runs, final colour and consumed byte
//      count for well-formed codes, a malformed code (too few hex digits, where the
//      original reads past the NUL), a code at the end of the string, `\e` reset and an
//      unknown escape (FUN_0065dad0: only the backslash is consumed).
//   3. Shift-JIS -> UTF-8 -> glyph coverage for the strings the reference frames
//      actually show. The port's text path takes UTF-8; the game's own strings are
//      Shift-JIS, so the test runs the generated CP932 table (assets/sjis_table.h)
//      through the same lookup as xm::sjisToUtf8 and reports what reaches the layer.
//      The table has 315 entries and does NOT carry every menu character — that is
//      reported as a known gap with the exact CP932 codes, while the same strings as
//      UTF-8 literals (what the port's own HUD/menu code passes) must rasterize
//      completely.
//   4. Layout — measured width equals the sum of the glyph advances; font glyphs share
//      one baseline; a missing glyph advances exactly one bitmap cell (6 texels) and
//      never shifts the rest of the line; '\n' advances by exactly one line height.
//   5. Fallback — with no font loaded the layer reports "bitmap-only" and its
//      measurement and quads are BIT-FOR-BIT those of ui::measureText/ui::layoutText
//      (the pixel-identical requirement on today's HUD output).
//
//  Final line: "TEXT: ok (n checks)" or "TEXT: FAIL (n of m checks failed)". Exit 0 on
//  ok, 1 on any mismatch. Every mismatch prints expected vs got.
// =============================================================================
#include "assets/sjis_table.h"
#include "ui/font.h"
#include "ui/text.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace {

int g_failures = 0;
int g_checks = 0;

void fail(const std::string& msg) {
    std::printf("FAIL: %s\n", msg.c_str());
    ++g_failures;
}

void check(bool cond, const std::string& what) {
    ++g_checks;
    if (!cond) fail(what);
}

void checkEq(long long got, long long want, const std::string& what) {
    check(got == want, what + " (expected " + std::to_string(want) + ", got " +
                           std::to_string(got) + ")");
}

std::string f2s(float v) {
    char b[64];
    std::snprintf(b, sizeof b, "%.9g", (double)v);
    return b;
}

// Bit-for-bit float comparison: "matches ui::measureText" has to mean exactly that.
bool feq(float a, float b) { return std::memcmp(&a, &b, sizeof(float)) == 0; }

std::string hexOf(const void* data, size_t len) {
    static const char* kHex = "0123456789abcdef";
    const uint8_t* p = (const uint8_t*)data;
    std::string s;
    s.reserve(len * 2);
    for (size_t i = 0; i < len; ++i) {
        s += kHex[p[i] >> 4];
        s += kHex[p[i] & 0xF];
    }
    return s;
}
std::string hexOf(const std::string& s) { return hexOf(s.data(), s.size()); }

std::string utf8Of(uint32_t cp) {
    std::string s;
    if (cp < 0x80) {
        s += (char)cp;
    } else if (cp < 0x800) {
        s += (char)(0xC0 | (cp >> 6));
        s += (char)(0x80 | (cp & 0x3F));
    } else if (cp < 0x10000) {
        s += (char)(0xE0 | (cp >> 12));
        s += (char)(0x80 | ((cp >> 6) & 0x3F));
        s += (char)(0x80 | (cp & 0x3F));
    } else {
        s += (char)(0xF0 | (cp >> 18));
        s += (char)(0x80 | ((cp >> 12) & 0x3F));
        s += (char)(0x80 | ((cp >> 6) & 0x3F));
        s += (char)(0x80 | (cp & 0x3F));
    }
    return s;
}

int countCps(const char* s) {
    int n = 0;
    for (const char* p = s; p && *p;) {
        ui::utf8Next(p);
        ++n;
    }
    return n;
}

std::string cpName(uint32_t cp) {
    char b[32];
    std::snprintf(b, sizeof b, "U+%04X", cp);
    return b;
}

// CP932 codes print big-endian (0x934B is `適`), unlike a little-endian memory dump.
std::string codeName(uint16_t code) {
    char b[16];
    std::snprintf(b, sizeof b, "0x%02X%02X", (unsigned)(code >> 8), (unsigned)(code & 0xFF));
    return b;
}

std::string colorName(ui::TextColor c) {
    char b[32];
    std::snprintf(b, sizeof b, "%02X%02X%02X/a%02X", c.r, c.g, c.b, c.a);
    return b;
}

// ---------------------------------------------------------------------------
// SHA-256 (self-contained, FIPS vectors checked before use) — the atlas fingerprint the
// parent can compare between Linux, Windows/Wine and the browser. In-process byte
// comparisons prove determinism for one target; this hash is what makes a cross-target
// divergence (FMA contraction, x87 excess precision, a different font file) visible.
// ---------------------------------------------------------------------------
class Sha256 {
public:
    void update(const void* data, size_t len) {
        const uint8_t* p = (const uint8_t*)data;
        m_bits += (uint64_t)len * 8u;
        while (len > 0) {
            const size_t take = std::min(len, sizeof(m_buf) - m_len);
            std::memcpy(m_buf + m_len, p, take);
            m_len += take;
            p += take;
            len -= take;
            if (m_len == sizeof(m_buf)) {
                transform(m_buf);
                m_len = 0;
            }
        }
    }
    std::string hexdigest() {
        const uint64_t total = m_bits;
        m_buf[m_len++] = 0x80;
        if (m_len > 56) {
            std::memset(m_buf + m_len, 0, sizeof(m_buf) - m_len);
            transform(m_buf);
            m_len = 0;
        }
        std::memset(m_buf + m_len, 0, 56 - m_len);
        for (int i = 0; i < 8; ++i) m_buf[56 + i] = (uint8_t)(total >> (56 - 8 * i));
        transform(m_buf);
        m_len = 0;
        char out[65];
        for (int i = 0; i < 8; ++i) std::snprintf(out + i * 8, 9, "%08x", m_h[i]);
        return std::string(out, 64);
    }

private:
    static uint32_t rotr(uint32_t x, int n) { return (x >> n) | (x << (32 - n)); }
    void transform(const uint8_t* block) {
        static const uint32_t k[64] = {
            0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
            0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
            0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
            0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
            0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
            0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
            0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
            0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
            0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
            0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
            0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
        uint32_t w[64];
        for (int i = 0; i < 16; ++i) {
            w[i] = ((uint32_t)block[i * 4] << 24) | ((uint32_t)block[i * 4 + 1] << 16) |
                   ((uint32_t)block[i * 4 + 2] << 8) | (uint32_t)block[i * 4 + 3];
        }
        for (int i = 16; i < 64; ++i) {
            const uint32_t s0 = rotr(w[i - 15], 7) ^ rotr(w[i - 15], 18) ^ (w[i - 15] >> 3);
            const uint32_t s1 = rotr(w[i - 2], 17) ^ rotr(w[i - 2], 19) ^ (w[i - 2] >> 10);
            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }
        uint32_t a = m_h[0], b = m_h[1], c = m_h[2], d = m_h[3];
        uint32_t e = m_h[4], f = m_h[5], g = m_h[6], h = m_h[7];
        for (int i = 0; i < 64; ++i) {
            const uint32_t s1 = rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25);
            const uint32_t ch = (e & f) ^ (~e & g);
            const uint32_t t1 = h + s1 + ch + k[i] + w[i];
            const uint32_t s0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22);
            const uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            const uint32_t t2 = s0 + maj;
            h = g; g = f; f = e; e = d + t1;
            d = c; c = b; b = a; a = t1 + t2;
        }
        m_h[0] += a; m_h[1] += b; m_h[2] += c; m_h[3] += d;
        m_h[4] += e; m_h[5] += f; m_h[6] += g; m_h[7] += h;
    }
    uint32_t m_h[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                       0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
    uint64_t m_bits = 0;
    uint8_t  m_buf[64] = {};
    size_t   m_len = 0;
};

std::string sha256Of(const void* data, size_t len) {
    Sha256 h;
    h.update(data, len);
    return h.hexdigest();
}

void sha256SelfTest() {
    struct Vec { const char* msg; const char* want; };
    static const Vec kVec[3] = {
        {"", "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"},
        {"abc", "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"},
        {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
         "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1"},
    };
    int before = g_failures;
    for (const Vec& v : kVec)
        check(sha256Of(v.msg, std::strlen(v.msg)) == v.want, "sha256 self-test");
    std::printf("sha256 self-test: %s (3 FIPS vectors)\n",
                g_failures == before ? "ok" : "FAIL");
}

// ---------------------------------------------------------------------------
// Shift-JIS -> UTF-8 oracle. Identical algorithm to assets/cnv.h's xm::sjisToUtf8 (lead
// bytes 0x81..0x9F and 0xE0..0xFC, binary search over the generated table, unknown codes
// appended as their raw bytes), reimplemented here so this test links no asset source.
// The real function lives in foundation_assets/assets.cpp; section 4 reports what it
// hands the layer, which is what matters for the HUD.
// ---------------------------------------------------------------------------
std::vector<uint16_t> sjisCodes(const std::string& in) {
    std::vector<uint16_t> codes;
    size_t i = 0;
    while (i < in.size()) {
        const uint8_t b = (uint8_t)in[i];
        if (b < 0x80) {
            codes.push_back(b);
            ++i;
            continue;
        }
        if (((b >= 0x81 && b <= 0x9F) || (b >= 0xE0 && b <= 0xFC)) && i + 1 < in.size()) {
            codes.push_back((uint16_t)((b << 8) | (uint8_t)in[i + 1]));
            i += 2;
            continue;
        }
        codes.push_back(b);
        ++i;
    }
    return codes;
}

const xm::detail::SjisEntry* sjisLookup(uint16_t code) {
    const xm::detail::SjisEntry* lo = xm::detail::kSjisTable;
    const xm::detail::SjisEntry* hi = lo + xm::detail::kSjisTableSize;
    const xm::detail::SjisEntry* it = std::lower_bound(
        lo, hi, code, [](const xm::detail::SjisEntry& e, uint16_t c) { return e.code < c; });
    return (it != hi && it->code == code) ? it : nullptr;
}

std::string sjisToUtf8Oracle(const std::string& in) {
    std::string out;
    size_t i = 0;
    while (i < in.size()) {
        const uint8_t b = (uint8_t)in[i];
        if (b < 0x80) {
            out += (char)b;
            ++i;
            continue;
        }
        uint16_t code = b;
        size_t take = 1;
        if ((b >= 0x81 && b <= 0x9F) || (b >= 0xE0 && b <= 0xFC)) {
            if (i + 1 >= in.size()) {
                out += (char)b;
                ++i;
                continue;
            }
            code = (uint16_t)((b << 8) | (uint8_t)in[i + 1]);
            take = 2;
        }
        if (const xm::detail::SjisEntry* e = sjisLookup(code)) out.append((const char*)e->utf8, e->len);
        else out.append(in, i, take);
        i += take;
    }
    return out;
}

// ---------------------------------------------------------------------------
// Font file discovery
// ---------------------------------------------------------------------------
fs::path findUpwards(const fs::path& start, const fs::path& relative) {
    std::error_code ec;
    fs::path p = start;
    for (int depth = 0; depth < 12 && !p.empty(); ++depth) {
        const fs::path candidate = p / relative;
        if (fs::exists(candidate, ec)) return candidate;
        const fs::path parent = p.parent_path();
        if (parent == p) break;
        p = parent;
    }
    return {};
}

// The layer's integer metric rule, recomputed here: round(v * px * 64 / em) in int64.
int32_t expectFixed64(int v, int px, int em) {
    const int64_t num = (int64_t)v * px * 64;
    const int64_t den = em;
    return (int32_t)(num >= 0 ? (num + den / 2) / den : -((-num + den / 2) / den));
}

bool readFile(const fs::path& path, std::vector<uint8_t>& out) {
    std::ifstream f(path, std::ios::binary);
    if (!f) return false;
    f.seekg(0, std::ios::end);
    const std::streamoff n = f.tellg();
    if (n <= 0) return false;
    f.seekg(0, std::ios::beg);
    out.resize((size_t)n);
    f.read((char*)out.data(), n);
    out.resize((size_t)f.gcount());
    return !out.empty();
}

int32_t advanceSum(const ui::TextLayout& l) {
    int32_t sum = 0;
    for (const ui::TextLayout::Item& it : l.items) sum += it.advance64;
    return sum;
}

void printLayout(const char* label, const ui::TextLayout& l, float scale) {
    std::printf("    %-9s items=%-3zu substituted=%-2d lines=%d advance=%d (%.2f px) "
                "width=%d (%.2f px)\n",
                label, l.items.size(), l.substituted, l.lines, advanceSum(l),
                (double)ui::pixels(advanceSum(l), scale), l.width64, (double)l.width(scale));
}

// The strings the reference frames show (docs/CJK-TEXT.md §2), as the game stores them
// (raw Shift-JIS bytes) and as the port's own code would pass them (UTF-8 literals).
struct GameString {
    const char* name;   // UTF-8 literal
    const char* sjis;   // the same text as the game's data spells it
    const char* utf8;   // the same text, already UTF-8
    const char* where;
};
const GameString kGameStrings[] = {
    {"適当", "\x93K\x93\x96", "\xe9\x81\xa9\xe5\xbd\x93", "in-battle HUD label"},
    {"ストーリー", "\x83X\x83g\x81[\x83\x8a\x81[",
     "\xe3\x82\xb9\xe3\x83\x88\xe3\x83\xbc\xe3\x83\xaa\xe3\x83\xbc", "title menu 1"},
    {"対戦", "\x91\xce\x90\xed", "\xe5\xaf\xbe\xe6\x88\xa6", "title menu 2"},
    {"通信対戦", "\x92\xca\x90M\x91\xce\x90\xed", "\xe9\x80\x9a\xe4\xbf\xa1\xe5\xaf\xbe\xe6\x88\xa6",
     "title menu 3"},
    {"環境設定", "\x8a\xc2\x8b\xab\x90\xdd\x92\xe8",
     "\xe7\x92\xb0\xe5\xa2\x83\xe8\xa8\xad\xe5\xae\x9a", "title menu 4"},
    {"操作設定", "\x91\x80\x8d\xec\x90\xdd\x92\xe8",
     "\xe6\x93\x8d\xe4\xbd\x9c\xe8\xa8\xad\xe5\xae\x9a", "title menu 5"},
    {"終了", "\x8fI\x97\xb9", "\xe7\xb5\x82\xe4\xba\x86", "title menu 6"},
    {"撃破", "\x8c\x82\x94j", "\xe6\x92\x83\xe7\xa0\xb4", "KO banner (art; rasterization case)"},
    {"恐怖のオヤシロモード", "\x8b\xb0\x95|\x82\xcc\x83I\x83\x84\x83V\x83\x8d\x83\x82\x81[\x83h",
     "\xe6\x81\x90\xe6\x80\x96\xe3\x81\xae\xe3\x82\xaa\xe3\x83\xa4\xe3\x82\xb7\xe3\x83\xad"
     "\xe3\x83\xa2\xe3\x83\xbc\xe3\x83\x89",
     "hypermode select"},
};
const size_t kGameStringCount = sizeof(kGameStrings) / sizeof(kGameStrings[0]);

}  // namespace

int main(int argc, char** argv) {
    const char* envFont = std::getenv("FOUNDATION_CJK_FONT");
    fs::path fontPath;
    if (argc > 1 && argv[1][0]) fontPath = fs::path(argv[1]);
    if (fontPath.empty() && envFont && *envFont) fontPath = fs::path(envFont);
    if (fontPath.empty()) {
        static const char* kRel[3] = {
            "remake/foundation/third_party/fonts/NotoSansCJKjp-Regular.otf",
            "third_party/fonts/NotoSansCJKjp-Regular.otf",
            "foundation/third_party/fonts/NotoSansCJKjp-Regular.otf",
        };
        for (const char* rel : kRel) {
            fontPath = findUpwards(fs::current_path(), rel);
            if (fontPath.empty())
                fontPath = findUpwards(fs::absolute(argv[0]).parent_path(), rel);
            if (!fontPath.empty()) break;
        }
    }

    std::vector<uint8_t> fontBytes;
    if (fontPath.empty() || !fs::exists(fontPath)) {
        // The pinned font is an optional fetch, so its absence is the suite's only
        // prerequisite: exit 77 and let CTest record a skip (audit finding B).
        std::printf("SKIP: no CJK font at '%s'\n",
                    fontPath.empty() ? "(unset)" : fontPath.string().c_str());
        std::printf("      pass one as argv[1], set FOUNDATION_CJK_FONT, or fetch the pinned\n"
                    "      font into third_party/fonts/ (see fetch_deps.sh)\n");
        std::printf("TEXT: skip\n");
        return 77;
    }
    if (!readFile(fontPath, fontBytes)) {
        // The file is there but unreadable: that is corrupt expected data, not a skip.
        std::printf("TEXT: FAIL: cannot read the font at '%s'\n", fontPath.string().c_str());
        return 1;
    }

    sha256SelfTest();
    const std::string fontSha = sha256Of(fontBytes.data(), fontBytes.size());
    std::printf("font: %s\n      %zu bytes sha256=%s\n", fontPath.string().c_str(),
                fontBytes.size(), fontSha.c_str());

    const float kDesignPx = 21.f;   // 21 px cell == the HUD's 7 px bitmap at scale 3
    const float kScale = 1.f;

    // ------------------------------------------------------------------ 1. the font
    std::printf("\n== 1. font + layer\n");
    ui::TextLayer layer;
    std::string err;
    check(!layer.fontLoaded(), "a fresh layer must report no font");
    check(std::strcmp(layer.mode(), "bitmap-only") == 0, "a fresh layer must be bitmap-only");
    if (!layer.loadFont(fontBytes, kDesignPx, err)) {
        fail("loadFont failed: " + err);
        std::printf("TEXT: FAIL (%d of %d checks failed)\n", g_failures, g_checks);
        return 1;
    }
    check(layer.fontLoaded(), "loadFont must report the font as loaded");
    check(std::strcmp(layer.mode(), "truetype") == 0, "a loaded layer must report truetype");
    check(layer.pixelHeight() == kDesignPx, "pixelHeight must round-trip");
    check(layer.atlasRGBA().size() == (size_t)layer.atlasWidth() * layer.atlasHeight() * 4,
          "atlas must be RGBA8, stride = width * 4");
    std::printf("mode=%s designPx=%.0f atlas=%ux%u bytes=%zu revision=%llu\n", layer.mode(),
                (double)layer.pixelHeight(), layer.atlasWidth(), layer.atlasHeight(),
                layer.atlasRGBA().size(), (unsigned long long)layer.atlasRevision());

    // Metrics: the layer's integer rule must match an independent recomputation from the
    // font's hhea values (Noto Sans CJK JP: ascent 1160, descent -288, lineGap 0).
    const int kAscent = 1160, kDescent = -288, kLineGap = 0;
    const int kEm = kAscent - kDescent;
    {
        const ui::TextLayout probe = layer.layout(utf8Of(0x9069).c_str());
        check(probe.items.size() == 1, "one code point must give one item");
        const int asPx = (int)std::ceil(ui::pixels(probe.ascent64, 1.f));
        const int dePx = (int)std::ceil(-ui::pixels(expectFixed64(kDescent, (int)kDesignPx, kEm), 1.f));
        std::printf("metrics (hhea, read by stb_truetype): ascent=%d descent=%d lineGap=%d em=%d\n",
                    kAscent, kDescent, kLineGap, kEm);
        std::printf("layer: ascent64=%d (%.3f px, ceil %d) lineHeight64=%d (%.3f px)\n",
                    probe.ascent64, (double)ui::pixels(probe.ascent64, 1.f), asPx,
                    probe.lineHeight64, (double)ui::pixels(probe.lineHeight64, 1.f));
        check(probe.ascent64 == expectFixed64(kAscent, (int)kDesignPx, kEm),
              "ascent64 must equal round(ascent * px * 64 / em): expected " +
                  std::to_string(expectFixed64(kAscent, (int)kDesignPx, kEm)) + ", got " +
                  std::to_string(probe.ascent64));
        check(probe.lineHeight64 == expectFixed64(kEm + kLineGap, (int)kDesignPx, kEm),
              "lineHeight64 must equal round((ascent - descent + lineGap) * px * 64 / em)");
        check(probe.items[0].y64 == probe.ascent64 + layer.glyphInfo(0x9069)->y0 * ui::kFixedOne,
              "a single-line glyph must hang off the baseline at ascent64");
        std::printf("used for the box checks below: ascent %d px, descent %d px\n", asPx, dePx);
    }

    // ------------------------------------------------------ 2. glyph rasterization
    std::printf("\n== 2. glyph rasterization (design %.0f px)\n", (double)kDesignPx);
    struct CpCase { uint32_t cp; bool cjk; bool tall; };
    static const CpCase kCps[] = {
        {0x0041, false, false}, {0x0067, false, false}, {0x0025, false, false},
        {0x0030, false, false}, {0x9069, true, true},   {0x5F53, true, true},
        {0x30B9, true, true},   {0x6483, true, true},   {0x6050, true, true},
        {0x30FC, true, false},  // the prolonged sound mark is a bar, not a body
        {0x306E, true, true},
    };
    const size_t kCpCount = sizeof(kCps) / sizeof(kCps[0]);

    ui::TextLayer again;   // second layer, same request sequence: byte-for-byte identical
    std::string err2;
    check(again.loadFont(fontBytes, kDesignPx, err2), "second layer must load: " + err2);

    std::printf("%-8s %6s %7s %-20s %-9s %5s %4s %s\n", "cp", "adv64", "adv_px", "box",
                "tile", "ink", "maxA", "cov[0..3]");
    for (const CpCase& c : kCps) {
        const std::string s = utf8Of(c.cp);
        const ui::TextLayout l = layer.layout(s.c_str());
        const ui::TextLayout l2 = again.layout(s.c_str());
        const ui::GlyphInfo* g = layer.glyphInfo(c.cp);
        const std::string name = cpName(c.cp);
        if (!g || !g->present) {
            fail(name + ": the font must have a glyph (stbtt_FindGlyphIndex != 0)");
            continue;
        }
        const int w = g->x1 - g->x0, h = g->y1 - g->y0;
        const std::vector<uint8_t> cov = layer.glyphCoverage(c.cp);
        size_t ink = 0;
        uint8_t maxA = 0;
        for (uint8_t v : cov) {
            if (v) ++ink;
            if (v > maxA) maxA = v;
        }
        const int asPx = (int)std::ceil(ui::pixels(l.ascent64, 1.f));
        const int dePx =
            (int)std::ceil(-ui::pixels(expectFixed64(kDescent, (int)kDesignPx, kEm), 1.f));
        std::printf("%-8s %6d %7.3f (%3d,%3d)-(%3d,%3d) %-9s %5zu %4u %s\n", name.c_str(),
                    g->advance64, (double)ui::pixels(g->advance64, 1.f), g->x0, g->y0, g->x1, g->y1,
                    ("(" + std::to_string(g->tileX) + "," + std::to_string(g->tileY) + ")").c_str(),
                    ink, maxA, hexOf(cov.data(), std::min<size_t>(cov.size(), 4)).c_str());
        check(cov.size() == (size_t)w * h, name + ": coverage must be w*h bytes");
        check(ink > 0, name + ": coverage must be non-empty");
        check(maxA > 0, name + ": max coverage must be > 0");
        check(w >= 1 && h >= 1, name + ": bitmap box must be non-empty");
        // Inside the font's metrics: a bearing cannot leave the em box, and the vertical
        // box cannot exceed the ascent/descent (+1 px of antialiasing slack).
        check(g->x0 >= -(int)kDesignPx / 2 && g->x1 <= 2 * (int)kDesignPx,
              name + ": horizontal box outside the em box");
        check(g->y0 >= -(asPx + 1) && g->y1 <= dePx + 1,
              name + ": vertical box outside ascent/descent: y0=" + std::to_string(g->y0) +
                  " y1=" + std::to_string(g->y1) + " (ascent " + std::to_string(asPx) +
                  ", descent " + std::to_string(dePx) + ")");
        if (c.cjk) {
            if (c.tall) check(h * 2 >= (int)kDesignPx,
                              name + ": CJK ink must be at least half the cell height");
            check(ink * 4 >= (size_t)w * h, name + ": CJK box must be substantially inked");
            check(g->advance64 * 2 >= (int32_t)kDesignPx * ui::kFixedOne,
                  name + ": CJK advance must be full-width-ish");
        }
        // Second run, byte-for-byte.
        const std::vector<uint8_t> cov2 = again.glyphCoverage(c.cp);
        check(cov == cov2, name + ": a second layer must rasterize identical bytes");
        check(l.items.size() == 1 && l2.items.size() == 1 &&
                  l.items[0].advance64 == l2.items[0].advance64,
              name + ": a second layer must report the same advance");
    }
    {
        // Atlas conventions. A freshly loaded layer must be a fully clear image (the
        // "unused texel = (0,0,0,0)" contract buildAtlasRGBA also has), and after
        // rasterization every *inked* texel must be pure white with coverage in alpha.
        // Texels inside a tile but with zero coverage stay white: with the linear
        // sampler ui/sprite.cpp sets, fading RGB to black at a glyph edge would tint the
        // antialiased pixels grey, so the whole tile is white and only alpha varies.
        ui::TextLayer fresh;
        std::string freshErr;
        check(fresh.loadFont(fontBytes, kDesignPx, freshErr), "fresh layer must load: " + freshErr);
        bool freshClear = true;
        for (uint8_t v : fresh.atlasRGBA())
            if (v) freshClear = false;
        check(freshClear, "a freshly loaded atlas must be all zero (RGB 0, A 0)");

        const std::vector<uint8_t>& a = layer.atlasRGBA();
        size_t inked = 0, coloredEmpty = 0;
        bool white = true;
        for (size_t i = 0; i + 3 < a.size(); i += 4) {
            if (a[i + 3] != 0) {
                ++inked;
                if (a[i] != 0xFF || a[i + 1] != 0xFF || a[i + 2] != 0xFF) white = false;
            } else if (a[i] || a[i + 1] || a[i + 2]) {
                ++coloredEmpty;   // must be 0 or 255: never a tinted value
                if (a[i] != 0xFF || a[i + 1] != 0xFF || a[i + 2] != 0xFF) white = false;
            }
        }
        std::printf("atlas: %zu inked texels of %zu (%ux%u), %zu transparent-white, "
                    "revision=%llu sha256=%s\n",
                    inked, (size_t)layer.atlasWidth() * layer.atlasHeight(), layer.atlasWidth(),
                    layer.atlasHeight(), coloredEmpty, (unsigned long long)layer.atlasRevision(),
                    sha256Of(a.data(), a.size()).c_str());
        check(inked > 0, "the atlas must hold the rasterized glyphs");
        check(white, "every atlas texel must be white (RGB 255) or fully clear (RGB 0)");
    }
    {
        // Same request sequence from scratch: byte-identical atlas, twice.
        ui::TextLayer a, b;
        std::string ea, eb;
        check(a.loadFont(fontBytes, kDesignPx, ea), "atlas-run A must load: " + ea);
        check(b.loadFont(fontBytes, kDesignPx, eb), "atlas-run B must load: " + eb);
        for (const CpCase& c : kCps) {
            a.layout(utf8Of(c.cp).c_str());
            b.layout(utf8Of(c.cp).c_str());
        }
        check(a.atlasWidth() == b.atlasWidth() && a.atlasHeight() == b.atlasHeight(),
              "the same sequence must produce the same atlas dimensions");
        check(a.atlasRGBA() == b.atlasRGBA(), "the same sequence must produce identical atlas bytes");
        check(a.atlasRevision() == b.atlasRevision(), "the same sequence must produce the same revision");
        check(a.glyphCoverage(0x9069) == b.glyphCoverage(0x9069),
              "the same sequence must produce identical glyph bytes");
        std::printf("determinism: two fresh layers, same sequence -> identical atlas "
                    "(%ux%u, revision %llu, %zu glyphs, %zu atlas-full drops)\n",
                    a.atlasWidth(), a.atlasHeight(), (unsigned long long)a.atlasRevision(),
                    a.cachedGlyphs(), a.atlasFullDrops());
    }
    {
        // Request order: the rasterizer is order-independent, the packing is not.
        ui::TextLayer reverse;
        std::string err3;
        check(reverse.loadFont(fontBytes, kDesignPx, err3), "reverse-order layer must load");
        for (size_t i = kCpCount; i-- > 0;) reverse.layout(utf8Of(kCps[i].cp).c_str());
        bool same = true;
        for (const CpCase& c : kCps)
            if (layer.glyphCoverage(c.cp) != reverse.glyphCoverage(c.cp)) same = false;
        check(same, "glyph bytes must not depend on the request order");
        std::printf("request order: per-glyph bytes identical when requested in reverse "
                    "(atlas %ux%u vs %ux%u — packing follows the sequence)\n",
                    layer.atlasWidth(), layer.atlasHeight(), reverse.atlasWidth(),
                    reverse.atlasHeight());
    }

    // ------------------------------------------------------- 2b. malformed UTF-8
    // font.h's contract: a malformed byte yields U+FFFD (drawn as '?'), and the walk never
    // runs past the sequence it claimed. The two forms a permissive decoder would accept —
    // an overlong encoding and a UTF-16 surrogate — are the ones the decoder has to reject
    // for that contract to be true.
    {
        struct Utf8Case { const char* label; std::string bytes; size_t consumed; uint32_t cp; };
        const Utf8Case kCases[] = {
            {"C0 80 overlong NUL", std::string("\xC0\x80", 2), 2, 0xFFFDu},
            {"C1 BF overlong", std::string("\xC1\xBF", 2), 2, 0xFFFDu},
            {"E0 80 80 overlong", std::string("\xE0\x80\x80", 3), 3, 0xFFFDu},
            {"F0 80 80 80 overlong", std::string("\xF0\x80\x80\x80", 4), 4, 0xFFFDu},
            {"ED A0 80 surrogate", std::string("\xED\xA0\x80", 3), 3, 0xFFFDu},
            {"ED BF BF surrogate", std::string("\xED\xBF\xBF", 3), 3, 0xFFFDu},
            {"C2 80 U+0080 (shortest form)", std::string("\xC2\x80", 2), 2, 0x80u},
            {"E0 A0 80 U+0800 (shortest form)", std::string("\xE0\xA0\x80", 3), 3, 0x800u},
            {"ED 9F BF U+D7FF (before surrogates)", std::string("\xED\x9F\xBF", 3), 3, 0xD7FFu},
            {"EE 80 80 U+E000 (after surrogates)", std::string("\xEE\x80\x80", 3), 3, 0xE000u},
            {"F0 90 80 80 U+10000", std::string("\xF0\x90\x80\x80", 4), 4, 0x10000u},
            {"F4 8F BF BF U+10FFFF", std::string("\xF4\x8F\xBF\xBF", 4), 4, 0x10FFFFu},
            {"E6 97 A5 U+65E5", std::string("\xE6\x97\xA5", 3), 3, 0x65E5u},
            {"truncated E6 97", std::string("\xE6\x97", 2), 2, 0xFFFDu},
            {"lone continuation 80", std::string("\x80", 1), 1, 0xFFFDu},
            {"C2 41 bad continuation", std::string("\xC2\x41", 2), 1, 0xFFFDu},
        };
        for (const Utf8Case& c : kCases) {
            const char* p = c.bytes.data();
            const uint32_t cp = ui::utf8Next(p);
            const size_t used = (size_t)(p - c.bytes.data());
            check(cp == c.cp && used == c.consumed,
                  std::string("utf8 ") + c.label + ": expected " + cpName(c.cp) + "/" +
                      std::to_string(c.consumed) + " bytes, got " + cpName(cp) + "/" +
                      std::to_string(used));
        }
        // A rejected sequence still advances exactly one cell, so the rest of the line is
        // not shifted: the same rule the unsupported-code-point case below pins. (The
        // literal is split so the compiler cannot read `\x80AB` as one escape.)
        const char* rejected = "\xC0\x80" "AB";
        ui::TextExtent e = ui::measureText(rejected, 3.f);
        check(feq(e.width, ui::measureText("?AB", 3.f).width),
              "an overlong byte measures exactly like the '?' it becomes");
        std::printf("utf8: %zu malformed/edge sequences decode to the documented code points\n",
                    sizeof(kCases) / sizeof(kCases[0]));
    }

    // -------------------------------------------------------------- 3. colour codes
    std::printf("\n== 3. \\c / \\e / \\n walker (FUN_0065dad0)\n");
    const ui::TextColor kWhite{255, 255, 255, 255};
    const ui::TextColor kRed{0xFF, 0x00, 0x00, 255};
    const ui::TextColor kGreen{0x00, 0xFF, 0x00, 255};
    const ui::TextColor kOrange{0xFF, 0x88, 0x00, 255};
    const ui::TextColor kBlue{0x00, 0x00, 0xFF, 255};
    const ui::TextColor kDark12{0x12, 0x00, 0x00, 255};
    struct RunCase {
        const char* text;
        std::vector<ui::ColorRun> runs;
        ui::TextColor final;
        size_t consumed;
        int newlines;
    };
    const RunCase kRunCases[] = {
        {"abc", {{0, 3, kWhite, 3}}, kWhite, 3, 0},
        {"a\\cFF0000b", {{0, 1, kWhite, 1}, {9, 1, kRed, 1}}, kRed, 10, 0},
        {"\\c00FF00ab", {{8, 2, kGreen, 2}}, kGreen, 10, 0},
        {"\\cff8800x\\ey", {{8, 1, kOrange, 1}, {11, 1, kWhite, 1}}, kWhite, 12, 0},
        // Malformed: the escape still consumes `c` + 6 bytes and missing digits are hex 0;
        // the walk stops at the terminator (the original reads past it).
        {"\\c12", {}, kDark12, 4, 0},
        {"A\\c12", {{0, 1, kWhite, 1}}, kDark12, 5, 0},
        // A colour code at the very end: the colour is set, nothing follows it.
        {"\\c0000FF", {}, kBlue, 8, 0},
        // Unknown escape: only the backslash is consumed, so `q` renders.
        {"x\\qy", {{0, 4, kWhite, 3}}, kWhite, 4, 0},
        // '\n' resets the pen, not the colour: one run spans the newline bytes.
        {"a\n\\cFF0000b\n", {{0, 1, kWhite, 1}, {10, 1, kRed, 1}}, kRed, 12, 2},
        // A multi-byte character after a backslash is not a command (FUN_0065e3a0 >= 2).
        {"\\\xe9\x81\xa9", {{1, 3, kWhite, 1}}, kWhite, 4, 0},
    };
    for (const RunCase& c : kRunCases) {
        const ui::ColorRuns got = ui::parseColorRuns(c.text, kWhite);
        std::string gotRuns, wantRuns;
        for (const ui::ColorRun& r : got.runs)
            gotRuns += "[" + std::to_string(r.byteOffset) + "," + std::to_string(r.byteLength) +
                       "," + colorName(r.color) + "," + std::to_string(r.glyphs) + "]";
        for (const ui::ColorRun& r : c.runs)
            wantRuns += "[" + std::to_string(r.byteOffset) + "," + std::to_string(r.byteLength) +
                        "," + colorName(r.color) + "," + std::to_string(r.glyphs) + "]";
        std::printf("  %-20s runs=%-48s final=%s consumed=%zu newlines=%d\n",
                    ("\"" + std::string(c.text) + "\"").c_str(), gotRuns.c_str(),
                    colorName(got.finalColor).c_str(), got.consumed, got.newlines);
        const std::string label = std::string("run case \"") + c.text + "\"";
        check(gotRuns == wantRuns, label + ": runs expected " + wantRuns + ", got " + gotRuns);
        check(got.finalColor == c.final, label + ": final colour expected " + colorName(c.final) +
                                             ", got " + colorName(got.finalColor));
        check(got.consumed == c.consumed, label + ": consumed expected " +
                                              std::to_string(c.consumed) + ", got " +
                                              std::to_string(got.consumed));
        check(got.newlines == c.newlines, label + ": newlines expected " +
                                              std::to_string(c.newlines) + ", got " +
                                              std::to_string(got.newlines));
    }
    check(ui::hexDigit('0') == 0 && ui::hexDigit('9') == 9 && ui::hexDigit('a') == 10 &&
              ui::hexDigit('F') == 15 && ui::hexDigit('g') == 0 && ui::hexDigit(0) == 0,
          "FUN_0065e450: hex digits, and 0 for everything else");

    // ------------------------------------------- 4. Shift-JIS -> UTF-8 -> glyphs
    std::printf("\n== 4. game strings (design %.0f px, scale %.0f)\n", (double)kDesignPx,
                (double)kScale);
    std::vector<uint16_t> unmappedAll;
    int lossyStrings = 0;
    for (size_t i = 0; i < kGameStringCount; ++i) {
        const GameString& gs = kGameStrings[i];
        const std::string sjis(gs.sjis);
        const std::string decoded = sjisToUtf8Oracle(sjis);
        const std::vector<uint16_t> codes = sjisCodes(sjis);
        std::string unmapped;
        int unmappedCount = 0;
        for (uint16_t code : codes) {
            if (sjisLookup(code)) continue;
            unmapped += " " + codeName(code);
            unmappedAll.push_back(code);
            ++unmappedCount;
        }
        if (unmappedCount > 0) ++lossyStrings;
        const ui::TextLayout viaSjis = layer.layout(decoded.c_str());
        const ui::TextLayout viaUtf8 = layer.layout(gs.utf8);
        const int cps = countCps(gs.utf8);
        std::printf("[%zu] %s  (%s)\n", i, gs.name, gs.where);
        std::printf("    sjis     %s  (%zu bytes -> %zu CP932 codes)\n", hexOf(sjis).c_str(),
                    sjis.size(), codes.size());
        std::printf("    decoded  %s  |%s|\n", hexOf(decoded).c_str(), decoded.c_str());
        printLayout("via sjis", viaSjis, kScale);
        printLayout("utf8 lit", viaUtf8, kScale);
        if (unmappedCount > 0)
            std::printf("    table    %d of %zu CP932 codes unmapped:%s\n", unmappedCount,
                        codes.size(), unmapped.c_str());
        // The layer's own contract: a UTF-8 literal (what the port's HUD/menu code passes)
        // rasterizes completely, one item per code point, width == advance sum.
        check(viaUtf8.substituted == 0, std::string("UTF-8 literal must rasterize completely: ") +
                                            gs.name + " (" + std::to_string(viaUtf8.substituted) +
                                            " substituted)");
        check((int)viaUtf8.items.size() == cps,
              std::string("one item per code point: ") + gs.name + " expected " +
                  std::to_string(cps) + ", got " + std::to_string(viaUtf8.items.size()));
        check(viaUtf8.width64 == advanceSum(viaUtf8),
              std::string("width must equal the advance sum: ") + gs.name);
        // The Shift-JIS path loses at least what the table cannot carry: each unmapped
        // code becomes raw bytes the layer substitutes.
        check(viaSjis.substituted >= unmappedCount,
              std::string("every unmapped CP932 code must show up as a substitution: ") + gs.name +
                  " expected >= " + std::to_string(unmappedCount) + ", got " +
                  std::to_string(viaSjis.substituted));
    }
    if (!unmappedAll.empty()) {
        std::sort(unmappedAll.begin(), unmappedAll.end());
        unmappedAll.erase(std::unique(unmappedAll.begin(), unmappedAll.end()), unmappedAll.end());
        std::printf("\nKNOWN GAP: assets/sjis_table.h (%d entries) leaves %d distinct CP932 codes "
                    "of these %zu\nstrings unmapped, so xm::sjisToUtf8 passes their raw bytes "
                    "through: the layer draws\nsubstitutions (%d of %zu strings affected). The "
                    "port's own UTF-8 literals are unaffected\n(all substituted=0 above). Codes "
                    "to add to tools/gen_sjis_table.py:",
                    xm::detail::kSjisTableSize, (int)unmappedAll.size(), kGameStringCount,
                    lossyStrings, kGameStringCount);
        for (uint16_t code : unmappedAll) std::printf(" %s", codeName(code).c_str());
        std::printf("\n");
    }

    // ---------------------------------------------------------------- 5. layout
    std::printf("\n== 5. layout and measurement\n");
    {
        const std::string mixed = "HP " + utf8Of(0x9069) + utf8Of(0x5F53) + " 100%";
        const ui::TextLayout l = layer.layout(mixed.c_str());
        std::printf("mixed \"%s\": items=%zu advance=%d width64=%d width(1)=%s width(3)=%s\n",
                    mixed.c_str(), l.items.size(), advanceSum(l), l.width64,
                    f2s(l.width(1.f)).c_str(), f2s(l.width(3.f)).c_str());
        check(advanceSum(l) == l.width64, "single-line width64 must equal the advance sum");
        check(feq(l.width(1.f), ui::pixels(l.width64, 1.f)),
              "width(1) must be pixels(width64, 1)");
        // With an integer (dyadic) scale every per-glyph product is exact, so the sum of
        // the pixel advances IS the measured width, bit for bit.
        float advSum3 = 0.f;
        for (const ui::TextLayout::Item& it : l.items) advSum3 += ui::pixels(it.advance64, 3.f);
        std::printf("sum of per-glyph advances @3 = %s, width(3) = %s\n", f2s(advSum3).c_str(),
                    f2s(l.width(3.f)).c_str());
        check(feq(advSum3, l.width(3.f)), "measured width must equal the sum of glyph advances");
        // A non-dyadic scale stays within one ulp: the layer scales the integer total once
        // instead of accumulating rounded per-glyph values.
        float advSum27 = 0.f;
        for (const ui::TextLayout::Item& it : l.items) advSum27 += ui::pixels(it.advance64, 2.7f);
        const float delta = std::fabs(advSum27 - l.width(2.7f));
        std::printf("non-dyadic scale 2.7: |sum - width| = %.9g (1 ulp = %.9g)\n", (double)delta,
                    (double)(l.width(2.7f) * 1.1920929e-7f));
        check(delta <= l.width(2.7f) * 1.2e-7f,
              "non-dyadic scales must stay within one float ulp of the advance sum");
        // One baseline: every font glyph satisfies y64 - y0*64 == ascent64.
        int offBaseline = 0, fontItems = 0;
        for (const ui::TextLayout::Item& it : l.items) {
            if (it.source != ui::GlyphSource::Font) continue;
            const ui::GlyphInfo* g = layer.glyphInfo(it.cp);
            if (!g) continue;
            ++fontItems;
            if (it.y64 - g->y0 * ui::kFixedOne != l.ascent64) ++offBaseline;
        }
        std::printf("baseline: %d font items, %d off the baseline (ascent64=%d)\n", fontItems,
                    offBaseline, l.ascent64);
        check(fontItems > 1 && offBaseline == 0,
              "every font glyph must sit on the line's baseline (ascent64)");
        // Every font quad must address a real rectangle inside the uploaded atlas: the
        // caller hands these UVs straight to SpriteRenderer::addTexture's texture.
        int bad = 0;
        for (const ui::TextLayout::Item& it : l.items) {
            if (it.source != ui::GlyphSource::Font) continue;
            const ui::GlyphInfo* g = layer.glyphInfo(it.cp);
            if (!g || !g->hasBitmap) continue;
            if (g->tileX < 0 || g->tileY < 0 ||
                g->tileX + (g->x1 - g->x0) > (int)layer.atlasWidth() ||
                g->tileY + (g->y1 - g->y0) > (int)layer.atlasHeight())
                ++bad;
        }
        std::vector<ui::GlyphQuad> quads;
        layer.buildQuads(l, 12.f, 34.f, 1.f, quads);
        for (const ui::GlyphQuad& q : quads) {
            if (q.source != ui::GlyphSource::Font) continue;
            if (!(q.u0 >= 0.f && q.u0 < q.u1 && q.u1 <= 1.f)) ++bad;
            if (!(q.v0 >= 0.f && q.v0 < q.v1 && q.v1 <= 1.f)) ++bad;
        }
        check(!quads.empty() && bad == 0,
              "every font quad must have UVs inside [0,1] and a tile inside the atlas");
        std::printf("quads: %zu for the mixed line, %d with out-of-range UVs or tiles\n",
                    quads.size(), bad);
    }
    {
        // A code point the font does not have: one bitmap cell of advance, no shift.
        const uint32_t kMissing = 0x1040;   // Myanmar: absent from Noto Sans CJK JP
        check(!layer.hasGlyph(kMissing), "the test font must lack U+1040");
        const std::string text = std::string("A") + utf8Of(kMissing) + "C";
        const ui::TextLayout l = layer.layout(text.c_str());
        std::vector<ui::GlyphQuad> quads;
        layer.buildQuads(l, 0.f, 0.f, 1.f, quads);
        std::printf("missing glyph: items=%zu substituted=%d quads=%zu adv=[%d,%d,%d] "
                    "x=[%d,%d,%d]\n",
                    l.items.size(), l.substituted, quads.size(), l.items[0].advance64,
                    l.items[1].advance64, l.items[2].advance64, l.items[0].x64, l.items[1].x64,
                    l.items[2].x64);
        check(l.items.size() == 3, "one item per code point");
        check(l.substituted == 1, "exactly one substitution");
        check(l.items[1].source == ui::GlyphSource::Bitmap, "a missing glyph comes from the atlas");
        check(l.items[1].advance64 == ui::kGlyphAdvance * ui::kFixedOne,
              "a missing glyph must advance exactly one bitmap cell");
        check(l.items[1].x64 == l.items[0].x64 + l.items[0].advance64,
              "the substitution must not shift the pen");
        check(l.items[2].x64 == l.items[1].x64 + l.items[1].advance64,
              "the rest of the line must keep its advance");
        check(l.width64 == advanceSum(l), "width must still equal the advance sum");
        check(quads.size() == 3, "the '?' substitution still draws a bitmap cell");
        std::vector<ui::TextQuad> bitmapQuads;
        ui::layoutText("?", 0.f, 0.f, 1.f, bitmapQuads);
        check(quads.size() == 3 && bitmapQuads.size() == 1 && feq(quads[1].u0, bitmapQuads[0].u0) &&
                  feq(quads[1].v0, bitmapQuads[0].v0) && feq(quads[1].u1, bitmapQuads[0].u1) &&
                  feq(quads[1].v1, bitmapQuads[0].v1),
              "the substitution quad must be the bitmap '?' cell");
    }
    {
        // '\n': one line height of advance, pen back to 0, width = widest line.
        const std::string text = std::string("AB\n") + utf8Of(0x9069);
        const ui::TextLayout l = layer.layout(text.c_str());
        const ui::GlyphInfo* gA = layer.glyphInfo('A');
        const ui::GlyphInfo* gCjk = layer.glyphInfo(0x9069);
        check(gA && gCjk, "the newline case needs both glyphs cached");
        if (gA && gCjk) {
            const int32_t line0Top = l.items[0].y64 - gA->y0 * ui::kFixedOne;
            const int32_t line1Top = l.items[2].y64 - gCjk->y0 * ui::kFixedOne;
            const int32_t lineW0 = l.items[0].advance64 + l.items[1].advance64;
            std::printf("newline: lines=%d items=%zu line0Top=%d line1Top=%d lineHeight64=%d "
                        "width64=%d lastLine64=%d y=[%d,%d,%d] x=[%d,%d,%d]\n",
                        l.lines, l.items.size(), line0Top, line1Top, l.lineHeight64, l.width64,
                        l.lastLine64, l.items[0].y64, l.items[1].y64, l.items[2].y64,
                        l.items[0].x64, l.items[1].x64, l.items[2].x64);
            check(l.lines == 2, "'\\n' must start a second line");
            check(l.items.size() == 3, "three glyph items");
            check(line1Top - line0Top == l.lineHeight64,
                  "the second line must be exactly one line height down: expected " +
                      std::to_string(l.lineHeight64) + ", got " + std::to_string(line1Top - line0Top));
            check(l.width64 == std::max(lineW0, l.items[2].advance64),
                  "width must be the widest of the two lines");
            check(l.lastLine64 == l.items[2].advance64, "lastLine64 must be the second line's width");
            check(l.items[2].x64 == gCjk->x0 * ui::kFixedOne,
                  "the second line must restart at the origin (plus the glyph's bearing): expected " +
                      std::to_string(gCjk->x0 * ui::kFixedOne) + ", got " +
                      std::to_string(l.items[2].x64));
        }
    }
    {
        // Empty input, spaces, controls, and the ASCII-from-bitmap switch.
        const ui::TextLayout empty = layer.layout("");
        const ui::TextLayout null = layer.layout(nullptr);
        check(empty.lines == 0 && empty.items.empty() && empty.width64 == 0,
              "an empty string has no lines");
        check(null.lines == 0 && null.items.empty(), "nullptr is an empty string");
        const ui::TextLayout spaced = layer.layout("A B");
        std::vector<ui::GlyphQuad> quads;
        layer.buildQuads(spaced, 0.f, 0.f, 1.f, quads);
        std::printf("space: items=%zu quads=%zu (a font space advances, it has no box)\n",
                    spaced.items.size(), quads.size());
        check(spaced.items.size() == 3 && quads.size() == 2, "a font space advances without a quad");
        const ui::TextLayout ctl = layer.layout("A\x01\x02" "B");
        check(ctl.items.size() == 2, "control bytes below 0x20 vanish without advancing");
        layer.setFontAscii(false);
        const ui::TextLayout asciiBitmap = layer.layout("A");
        const ui::TextLayout cjkFont = layer.layout(utf8Of(0x9069).c_str());
        std::printf("switches: fontAscii(false) -> A is a bitmap cell (%d units), CJK is font "
                    "(%d units)\n",
                    asciiBitmap.items[0].advance64, cjkFont.items[0].advance64);
        check(asciiBitmap.items.size() == 1 &&
                  asciiBitmap.items[0].source == ui::GlyphSource::Bitmap &&
                  asciiBitmap.items[0].advance64 == ui::kGlyphAdvance * ui::kFixedOne,
              "setFontAscii(false) must take ASCII from the bitmap atlas");
        check(cjkFont.items.size() == 1 && cjkFont.items[0].source == ui::GlyphSource::Font,
              "CJK still comes from the font with setFontAscii(false)");
        layer.setFontAscii(true);
        check(layer.fontAscii(), "fontAscii() must report the switch");
    }

    {
        // Negative cases: a broken or absent font must leave a working bitmap-only layer,
        // never a half-loaded one. This is the fetch_deps.sh failure mode (a truncated
        // download) and the reason the layer has a fallback at all.
        ui::TextLayer broken;
        std::string berr;
        check(broken.loadFont(fontBytes, 21.f, berr) && broken.fontLoaded(), "reload must work");
        std::vector<uint8_t> junk(64, 0x5A);
        check(!broken.loadFont(junk, 21.f, berr) && !broken.fontLoaded(),
              "a garbage buffer must fail to load");
        check(!berr.empty(), "a failed load must set an error string");
        check(std::strcmp(broken.mode(), "bitmap-only") == 0,
              "a failed load must report bitmap-only");
        check(broken.cachedGlyphs() == 0, "a failed load must clear the glyph cache");
        check(feq(broken.layout("A").width(3.f), ui::measureText("A", 3.f).width),
              "a failed load must leave the bitmap fallback measuring exactly");
        std::printf("negative: junk buffer -> loadFont=false, mode=%s, error=\"%s\"\n",
                    broken.mode(), berr.c_str());

        ui::TextLayer ranges;
        std::string rerr;
        check(!ranges.loadFont(fontBytes, 0.f, rerr), "design height 0 must be rejected");
        std::printf("negative: design height 0 -> error=\"%s\"\n", rerr.c_str());
        check(!ranges.loadFont(fontBytes, 4096.f, rerr), "an absurd design height must be rejected");
        check(!ranges.loadFont({}, 21.f, rerr), "empty font data must be rejected");
        check(std::strcmp(ranges.mode(), "bitmap-only") == 0,
              "rejected loads must leave the layer bitmap-only");
    }

    // -------------------------------------------------- 6b. the reference's metric mode
    // loadFontChain sizes a face from the LOGFONT cell height instead of stb's pixel
    // height, then reproduces what GDI reports for it: whole-pixel advances and a
    // baseline at tmAscent - tmExternalLeading. The HUD's Latin face and its exact
    // advance table live in tests/hud_text_test.cpp; here the CJK face proves the mode
    // itself, and a two-face chain proves the fallback across faces.
    std::printf("\n== 6b. loadFontChain: GDI cell metrics and face fallback\n");
    {
        ui::TextLayer chainLayer;
        std::string cerr2;
        ui::FontChain one;
        one.push_back(ui::FontFace{fontBytes, 22.f});
        check(chainLayer.loadFontChain(one, cerr2), "a one-face chain must load: " + cerr2);
        checkEq((int)chainLayer.pixelHeight(), 15,
                "cell 22 over Noto CJK (1160+288 of 1000) is an em of 15 px");
        checkEq(chainLayer.faceUnitsPerEm(0x9069 /* 適 */), 1000, "the CJK face's upem");
        const ui::TextLayout cjk = chainLayer.layout("\xe9\x81\xa9");   // 適
        check(cjk.items.size() == 1 && cjk.items[0].advance64 % ui::kFixedOne == 0,
              "an advance in the reference mode is a whole pixel");
        const ui::TextLayout latin = chainLayer.layout("A");
        check(latin.items.size() == 1 && latin.items[0].advance64 % ui::kFixedOne == 0,
              "ASCII in the reference mode is a whole pixel too");
        std::printf("  cell 22 -> em %.0f px, 'A' advance %d units, CJK advance %d units\n",
                    chainLayer.pixelHeight(), (int)latin.items[0].advance64,
                    (int)cjk.items[0].advance64);

        // GDI font linking, as a chain: the first face that has the code point supplies
        // it. Checked against the Latin face when it is on disk (the HUD's face).
        fs::path latinPath;
        static const char* kLatinName = "LiberationSans-Bold.ttf";
        for (const char* const* root = ui::fontSearchRoots(); root && *root; ++root) {
            latinPath = findUpwards(fs::current_path(), fs::path(*root) / kLatinName);
            if (!latinPath.empty()) break;
        }
        std::vector<uint8_t> latinBytes;
        if (latinPath.empty() || !readFile(latinPath, latinBytes)) {
            std::printf("  (no Latin face on disk: chain fallback not checked)\n");
        } else {
            ui::TextLayer linked;
            ui::FontChain both;
            both.push_back(ui::FontFace{latinBytes, 22.f});
            both.push_back(ui::FontFace{fontBytes, 22.f});
            check(linked.loadFontChain(both, cerr2), "the two-face chain must load: " + cerr2);
            checkEq(linked.faceCount(), 2, "two faces");
            checkEq(linked.faceUnitsPerEm('A'), 2048, "'A' must come from the Latin face");
            checkEq(linked.faceUnitsPerEm(0x9069), 1000, "CJK must come from the CJK face");
            const ui::TextLayout mixed = linked.layout("HP \xe9\x81\xa9");
            check(mixed.items.size() == 4, "HP + CJK is four items");
            checkEq((int)mixed.items[0].advance64, 14 * ui::kFixedOne, "H from the Latin face");
            checkEq((int)mixed.items[3].advance64, (int)cjk.items[0].advance64,
                    "the CJK glyph keeps the CJK face's advance");
            std::printf("  chain [Latin, CJK]: 'A' upem %d, CJK upem %d, \"HP 適\" width %d units\n",
                        linked.faceUnitsPerEm('A'), linked.faceUnitsPerEm(0x9069), mixed.width64);
        }
    }

    // ---------------------------------------------------------- 7. fallback parity
    std::printf("\n== 7. fallback: bitmap-only layer == ui::font\n");    ui::TextLayer plain;
    check(!plain.fontLoaded() && std::strcmp(plain.mode(), "bitmap-only") == 0,
          "with no font the layer must report bitmap-only");
    check(!plain.hasGlyph('A'), "no font means no font glyphs");
    check(plain.cachedGlyphs() == 0, "no font means an empty glyph cache");
    static const char* kAscii[] = {"", "HP", "LIMIT 100%", "%", "0", "READY (S)", "KO!",
                                   "MAIN RELOAD", "STAMINA", "abcdefghijklmnopqrstuvwxyz",
                                   "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", "~|{}[]<>?/^_`"};
    static const float kScales[] = {1.f, 2.f, 3.f, 0.5f};
    int compared = 0;
    for (const char* s : kAscii) {
        for (float scale : kScales) {
            const ui::TextLayout l = plain.layout(s);
            const ui::TextExtent e = ui::measureText(s, scale);
            const std::string label = std::string("fallback \"") + s + "\" @" + f2s(scale);
            check(feq(l.width(scale), e.width),
                  label + ": width expected " + f2s(e.width) + " (ui::measureText), got " +
                      f2s(l.width(scale)));
            check(l.lines == e.lines, label + ": lines expected " + std::to_string(e.lines) +
                                          ", got " + std::to_string(l.lines));
            check(feq(ui::pixels(l.lineHeight64, scale), (float)ui::kLineHeight * scale),
                  label + ": line height must be kLineHeight * scale");
            check(feq((float)l.lines * ui::pixels(l.lineHeight64, scale), e.height),
                  label + ": height expected " + f2s(e.height) + ", got " +
                      f2s((float)l.lines * ui::pixels(l.lineHeight64, scale)));
            std::vector<ui::GlyphQuad> mine;
            std::vector<ui::TextQuad> theirs;
            plain.buildQuads(l, 7.f, 11.f, scale, mine);
            ui::layoutText(s, 7.f, 11.f, scale, theirs);
            bool same = mine.size() == theirs.size();
            for (size_t i = 0; same && i < mine.size(); ++i) {
                same = feq(mine[i].x, theirs[i].x) && feq(mine[i].y, theirs[i].y) &&
                       feq(mine[i].w, theirs[i].w) && feq(mine[i].h, theirs[i].h) &&
                       feq(mine[i].u0, theirs[i].u0) && feq(mine[i].v0, theirs[i].v0) &&
                       feq(mine[i].u1, theirs[i].u1) && feq(mine[i].v1, theirs[i].v1);
            }
            check(same, label + ": quads must be bit-for-bit ui::layoutText's (" +
                            std::to_string(mine.size()) + " vs " + std::to_string(theirs.size()) +
                            ")");
            ++compared;
        }
    }
    std::printf("bit-for-bit vs ui::measureText/ui::layoutText: %d string*scale cases\n", compared);
    {
        // Unsupported code points in bitmap mode: one cell, '?' — the same advance
        // ui::measureText gives them.
        const std::string cjk = utf8Of(0x9069);
        const ui::TextLayout l = plain.layout(cjk.c_str());
        const ui::TextExtent e = ui::measureText(cjk.c_str(), 3.f);
        std::printf("bitmap-only CJK: items=%zu substituted=%d advance=%d width(3)=%s vs "
                    "ui::measureText=%s\n",
                    l.items.size(), l.substituted, l.items[0].advance64, f2s(l.width(3.f)).c_str(),
                    f2s(e.width).c_str());
        check(l.substituted == 1 && l.items[0].source == ui::GlyphSource::Bitmap,
              "an unsupported code point must substitute the bitmap '?'");
        check(feq(l.width(3.f), e.width), "the substitution must measure exactly like '?'");
    }
    {
        // The bitmap layer has no escape model, so parity is asserted on escape-free
        // strings. With an escape the CJK layer consumes it (FUN_0065dad0) while the
        // bitmap layer counts its characters as cells — that divergence is the point of
        // the ported walker, so it is reported, not hidden.
        struct Divergence { const char* text; size_t items; float width3; };
        const Divergence kCases[] = {
            {"A\\cFF0000B", 2, 36.f},        // `\c` + 6 hex: 8 of 10 bytes consumed
            {"x\\qy", 3, 54.f},             // unknown escape: only the backslash goes
            {"a\\", 1, 18.f},               // a trailing backslash ends the walk
        };
        for (const Divergence& d : kCases) {
            const ui::TextLayout l = plain.layout(d.text);
            const ui::TextExtent e = ui::measureText(d.text, 3.f);
            std::printf("escape divergence (documented): \"%s\" -> CJK layer %zu items, "
                        "width(3)=%s; ui::measureText counts %zu bytes, width=%s\n",
                        d.text, l.items.size(), f2s(l.width(3.f)).c_str(), std::strlen(d.text),
                        f2s(e.width).c_str());
            check(l.items.size() == d.items && feq(l.width(3.f), d.width3),
                  std::string("escape divergence case \"") + d.text + "\": expected " +
                      std::to_string(d.items) + " items and width " + f2s(d.width3) + ", got " +
                      std::to_string(l.items.size()) + " and " + f2s(l.width(3.f)));
        }
        check(plain.layout("A\\cFF0000B").items[1].color == kRed,
              "the escape must set the colour for the second item and not advance");
    }

    std::printf("\n");
    if (g_failures == 0) {
        std::printf("TEXT: ok (%d checks)\n", g_checks);
        return 0;
    }
    std::printf("TEXT: FAIL (%d of %d checks failed)\n", g_failures, g_checks);
    return 1;
}
