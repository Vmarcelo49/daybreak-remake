// platform/web_assets.cpp — see the header for why these parts are host-compilable.
#include "platform/web_assets.h"

#include <cstdio>
#include <cstring>

namespace plat {
namespace {

bool isHexDigest(const std::string& s) {
    if (s.size() != 64) return false;
    for (char c : s)
        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'))) return false;
    return true;
}

bool parseU64(const std::string& s, uint64_t& out) {
    if (s.empty()) return false;
    uint64_t value = 0;
    for (char c : s) {
        if (c < '0' || c > '9') return false;
        value = value * 10 + uint64_t(c - '0');
    }
    out = value;
    return true;
}

std::vector<std::string> splitTabs(const std::string& line) {
    std::vector<std::string> out;
    std::size_t start = 0;
    while (true) {
        const std::size_t tab = line.find('\t', start);
        if (tab == std::string::npos) {
            out.push_back(line.substr(start));
            break;
        }
        out.push_back(line.substr(start, tab - start));
        start = tab + 1;
    }
    return out;
}

// ---------------------------------------------------------------------------
// SHA-256 (FIPS 180-4). ~70 lines is cheaper than a dependency here: the web client
// must validate what the server sent, and the native build must not grow a crypto
// library to do it. The host test pins it to the published vectors.
// ---------------------------------------------------------------------------
struct Sha256 {
    uint32_t h[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                     0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
    uint64_t bits = 0;
    uint8_t  buf[64] = {};
    std::size_t len = 0;

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
            w[i] = (uint32_t(block[i * 4]) << 24) | (uint32_t(block[i * 4 + 1]) << 16) |
                   (uint32_t(block[i * 4 + 2]) << 8) | uint32_t(block[i * 4 + 3]);
        }
        for (int i = 16; i < 64; ++i) {
            const uint32_t s0 = rotr(w[i - 15], 7) ^ rotr(w[i - 15], 18) ^ (w[i - 15] >> 3);
            const uint32_t s1 = rotr(w[i - 2], 17) ^ rotr(w[i - 2], 19) ^ (w[i - 2] >> 10);
            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }
        uint32_t a = h[0], b = h[1], c = h[2], d = h[3];
        uint32_t e = h[4], f = h[5], g = h[6], hh = h[7];
        for (int i = 0; i < 64; ++i) {
            const uint32_t s1 = rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25);
            const uint32_t ch = (e & f) ^ (~e & g);
            const uint32_t t1 = hh + s1 + ch + k[i] + w[i];
            const uint32_t s0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22);
            const uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            const uint32_t t2 = s0 + maj;
            hh = g; g = f; f = e; e = d + t1;
            d = c; c = b; b = a; a = t1 + t2;
        }
        h[0] += a; h[1] += b; h[2] += c; h[3] += d;
        h[4] += e; h[5] += f; h[6] += g; h[7] += hh;
    }

    void update(const uint8_t* data, std::size_t size) {
        bits += uint64_t(size) * 8u;
        while (size > 0) {
            const std::size_t take = (size < sizeof(buf) - len) ? size : sizeof(buf) - len;
            std::memcpy(buf + len, data, take);
            len += take;
            data += take;
            size -= take;
            if (len == sizeof(buf)) {
                transform(buf);
                len = 0;
            }
        }
    }

    std::string hex() {
        const uint64_t total = bits;
        buf[len++] = 0x80;
        if (len > 56) {
            std::memset(buf + len, 0, sizeof(buf) - len);
            transform(buf);
            len = 0;
        }
        std::memset(buf + len, 0, 56 - len);
        for (int i = 0; i < 8; ++i) buf[56 + i] = uint8_t(total >> (56 - 8 * i));
        transform(buf);
        len = 0;

        char out[65];
        for (int i = 0; i < 8; ++i) std::snprintf(out + i * 8, 9, "%08x", h[i]);
        return std::string(out, 64);
    }
};

}  // namespace

std::size_t WebAssetManifest::gateCount() const {
    std::size_t n = 0;
    for (const WebAssetEntry& e : entries)
        if (e.gate) ++n;
    return n;
}

uint64_t WebAssetManifest::transferBytes() const {
    uint64_t n = 0;
    for (const WebAssetEntry& e : entries) n += e.transferSize();
    return n;
}

bool parseAssetManifest(const std::string& text, WebAssetManifest& out, std::string& error) {
    out = WebAssetManifest{};
    std::size_t start = 0;
    while (start <= text.size()) {
        std::size_t end = text.find('\n', start);
        if (end == std::string::npos) end = text.size();
        std::string line = text.substr(start, end - start);
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (end == text.size()) start = text.size() + 1;
        else start = end + 1;

        if (line.empty() || line[0] == '#') continue;
        if (line.rfind("version=", 0) == 0) {
            out.version = line.substr(8);
            continue;
        }
        if (line.rfind("group=", 0) == 0) {
            out.group = line.substr(6);
            continue;
        }
        if (line.rfind("assets=", 0) == 0) continue;      // count is derived, not trusted
        if (line.rfind("bytes=", 0) == 0) {
            if (!parseU64(line.substr(6), out.declaredBytes)) {
                error = "manifest: bad bytes= line: " + line;
                return false;
            }
            continue;
        }
        const std::vector<std::string> f = splitTabs(line);
        if (f.size() != 5) {
            error = "manifest: expected 5 tab-separated fields, got " +
                    std::to_string(f.size()) + ": " + line;
            return false;
        }
        WebAssetEntry entry;
        entry.sha256 = f[0];
        entry.id = f[4];
        if (!isHexDigest(entry.sha256)) {
            error = "manifest: not a sha256: " + entry.sha256 + " (" + entry.id + ")";
            return false;
        }
        if (!parseU64(f[1], entry.size) || !parseU64(f[2], entry.gzipSize)) {
            error = "manifest: bad size for " + entry.id;
            return false;
        }
        if (f[3] != "0" && f[3] != "1") {
            error = "manifest: gate flag must be 0 or 1 for " + entry.id;
            return false;
        }
        entry.gate = f[3] == "1";
        if (webAssetTargetPath("/", entry.id).empty()) {
            error = "manifest: id is not a safe relative path: " + entry.id;
            return false;
        }
        out.entries.push_back(std::move(entry));
    }
    if (out.entries.empty()) {
        error = "manifest: no entries";
        return false;
    }
    return true;
}

std::string sha256Hex(const uint8_t* data, std::size_t size) {
    Sha256 hash;
    hash.update(data, size);
    return hash.hex();
}

std::string webAssetTargetPath(const std::string& mount, const std::string& id) {
    if (id.empty() || id.size() > 512) return {};
    if (id.front() == '/' || id.front() == '\\') return {};
    if (id.find('\\') != std::string::npos) return {};       // one separator, always '/'
    if (id.find('\0') != std::string::npos) return {};
    // No traversal, and no empty or "." components: the id becomes a path the native
    // reader will open, so it must be a plain relative path and nothing else.
    std::size_t start = 0;
    while (start <= id.size()) {
        const std::size_t slash = id.find('/', start);
        const std::string part =
            id.substr(start, slash == std::string::npos ? std::string::npos : slash - start);
        if (part.empty() || part == "." || part == "..") return {};
        if (slash == std::string::npos) break;
        start = slash + 1;
    }
    std::string mountPath = mount;
    while (mountPath.size() > 1 && mountPath.back() == '/') mountPath.pop_back();
    return mountPath + "/" + id;
}

std::string AssetProgress::line(const std::string& label) const {
    char text[192];
    const double doneMb = double(bytesDone) / 1048576.0;
    const double totalMb = double(bytesTotal) / 1048576.0;
    std::snprintf(text, sizeof(text), "[delivery] %s %zu/%zu assets, %.1f/%.1f MB%s",
                  label.c_str(), ready, total, doneMb, totalMb, cached ? " (cache)" : "");
    std::string out(text);
    if (failed) {
        char tail[48];
        std::snprintf(tail, sizeof(tail), " %zu failed", failed);
        out += tail;
    }
    return out;
}

}  // namespace plat
