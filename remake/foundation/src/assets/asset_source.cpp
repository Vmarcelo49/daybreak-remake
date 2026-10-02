// assets/asset_source.cpp — see asset_source.h for why this seam exists.
#include "asset_source.h"

#include <cstdio>
#include <filesystem>
#include <system_error>

namespace fnd::assets {
namespace {

namespace fs = std::filesystem;

// Lexical path normalization: backslashes to slashes, duplicate slashes collapsed,
// "." and ".." resolved. Needed because a caller can hand in a path like
// "<stage>/../bgm/01.ogg", whose bundle key is "data/bgm/01.ogg" — the archives store
// resolved names and matching is by string. Purely lexical: no filesystem access, so
// the result is identical on every target. The filesystem fallback still uses the
// caller's original string, where the OS resolves the path itself.
std::string normalize(std::string p) {
    for (char& c : p)
        if (c == '\\') c = '/';

    const bool absolute = !p.empty() && p.front() == '/';
    std::vector<std::string> parts;
    size_t start = 0;
    while (start <= p.size()) {
        const size_t slash = p.find('/', start);
        const std::string seg =
            p.substr(start, slash == std::string::npos ? std::string::npos : slash - start);
        if (seg == "..") {
            if (!parts.empty() && parts.back() != "..") parts.pop_back();
            else if (!absolute) parts.push_back("..");
        } else if (!seg.empty() && seg != ".") {
            parts.push_back(seg);
        }
        if (slash == std::string::npos) break;
        start = slash + 1;
    }

    std::string out = absolute ? "/" : std::string();
    for (size_t i = 0; i < parts.size(); ++i) {
        if (i) out += '/';
        out += parts[i];
    }
    if (out.empty()) out = absolute ? "/" : ".";
    return out;
}

// The filesystem half. Kept byte-for-byte equivalent to the fopen() path the asset layer
// used before this seam existed (which is what keeps tree-only setups rendering the same
// pixels), including "an empty file reads as a failure".
bool readFile(const std::string& path, std::vector<uint8_t>& out) {
    std::FILE* f = std::fopen(path.c_str(), "rb");
    if (!f) return false;
    std::fseek(f, 0, SEEK_END);
    const long n = std::ftell(f);
    std::fseek(f, 0, SEEK_SET);
    if (n <= 0) {
        std::fclose(f);
        return false;
    }
    out.resize((size_t)n);
    const size_t got = std::fread(out.data(), 1, (size_t)n, f);
    std::fclose(f);
    out.resize(got);
    return got > 0;
}

}  // namespace

AssetSource& AssetSource::instance() {
    static AssetSource source;
    return source;
}

bool AssetSource::openInstall(const std::string& installDir) {
    closeInstall();
    installDir_ = normalize(installDir);
    const size_t opened = bundles_.openAll(installDir_);
    bundlesOpen_ = opened > 0;
    if (!bundlesOpen_) installDir_.clear();
    return bundlesOpen_;
}

void AssetSource::closeInstall() {
    bundles_ = DatBundleSet{};
    installDir_.clear();
    bundlesOpen_ = false;
}

std::string AssetSource::findInstallDir(const std::string& path) {
    std::error_code ec;
    fs::path p = fs::path(path);
    if (!fs::is_directory(p, ec)) p = p.parent_path();
    for (int depth = 0; depth < 16 && !p.empty(); ++depth) {
        if (fs::exists(p / "daybreak00.dat", ec)) return normalize(p.string());
        const fs::path parent = p.parent_path();
        if (parent == p) break;
        p = parent;
    }
    return {};
}

std::string AssetSource::toKey(const std::string& path) const {
    std::string p = normalize(path);
    if (p.empty()) return {};

    if (!installDir_.empty()) {
        if (p == installDir_) return {};
        const std::string prefix = installDir_ + "/";
        if (p.compare(0, prefix.size(), prefix) == 0) return p.substr(prefix.size());
    }
    // Already a key (listDir returns these, and a caller may pass one directly).
    if (p.rfind("data/", 0) == 0 || p.rfind("movie/", 0) == 0) return p;
    // Last resort: an install-relative path with something in front of it. Only the two
    // top-level directories the archives actually use are recognized, so a path outside
    // the install gets no key rather than a wrong one.
    for (const char* marker : {"/data/", "/movie/"}) {
        const size_t at = p.find(marker);
        if (at != std::string::npos) return p.substr(at + 1);
    }
    return {};
}

bool AssetSource::exists(const std::string& path) const {
    if (bundlesOpen_) {
        const std::string key = toKey(path);
        if (!key.empty() &&
            (bundles_.find(key) != nullptr || bundles_.findAsciiCaseInsensitive(key) != nullptr))
            return true;
    }
    std::error_code ec;
    return fs::exists(fs::path(path), ec);
}

bool AssetSource::read(const std::string& path, std::vector<uint8_t>& out) const {
    if (bundlesOpen_) {
        const std::string key = toKey(path);
        if (!key.empty()) {
            // Exact first, then the exe's own comparison: its bundle index folds case
            // (__stricmp at 0x00663c20) and the shipped tables are inconsistent about it
            // — "collision_camera.X" on 11 stages and ".x" on two, rena/00.dat naming
            // "00.x" while the entry is "00.X". Without the fold, a bundle-only install
            // silently loads a partial stage.
            const DatBundle* owner = nullptr;
            const DatEntry*  entry = bundles_.find(key, &owner);
            if (!entry) entry = bundles_.findAsciiCaseInsensitive(key, &owner);
            if (entry && owner && owner->read(*entry, out)) return true;
        }
    }
    return readFile(path, out);
}

std::string AssetSource::resolve(const std::vector<std::string>& candidates) const {
    for (const std::string& c : candidates)
        if (exists(c)) return c;
    return {};
}

std::vector<std::string> AssetSource::listDir(const std::string& dir) const {
    std::vector<std::string> names;
    if (!bundlesOpen_) return names;

    std::string key = toKey(dir);
    if (key.empty()) return names;
    const std::string prefix = key + "/";

    // Bundle order, first match wins: the same rule find() uses, so a name present in two
    // bundles is listed once, pointing at the copy the loader would actually read.
    for (const DatBundle& b : bundles_.bundles()) {
        if (!b.isOpen()) continue;
        for (const DatEntry& e : b.entries()) {
            if (e.name.size() <= prefix.size()) continue;
            if (e.name.compare(0, prefix.size(), prefix) != 0) continue;
            if (e.name.find('/', prefix.size()) != std::string::npos) continue;   // nested
            bool seen = false;
            for (const std::string& s : names)
                if (s == e.name) {
                    seen = true;
                    break;
                }
            if (!seen) names.push_back(e.name);
        }
    }
    return names;
}

}  // namespace fnd::assets
