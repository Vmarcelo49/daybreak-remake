// assets/asset_source.cpp — see asset_source.h for why this seam exists.
#include "asset_source.h"

#include <cstdio>
#include <filesystem>
#include <system_error>

namespace fnd::assets {
namespace {

namespace fs = std::filesystem;

std::string normalize(std::string p) {
    for (char& c : p)
        if (c == '\\') c = '/';
    while (p.size() > 1 && p.back() == '/') p.pop_back();
    return p;
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
