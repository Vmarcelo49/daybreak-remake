#pragma once
// update/package_manifest.h — the file list a release package owns (issue #100).
//
// The updater may only replace files its own package ships, because players extract a
// package into their game folder next to the copyrighted data. The package states that list
// in package-manifest.txt; this is the game's parser for it, exactly as strict as
// tools/package_manifest.py and docs/AUTO-UPDATE.md.
#include <cstdint>
#include <string>
#include <vector>

#include "update/manifest_status.h"

namespace update {

inline constexpr const char* kPackageManifestName = "package-manifest.txt";

struct PackageEntry {
    std::string path;
    std::string sha256;  // 64 lowercase hex characters
    std::uint64_t size = 0;
    bool executable = false;  // mode 'x' (Linux); always false on Windows
};

struct PackageManifest {
    int format = 1;
    std::string version;
    std::string target;  // "linux-x86_64" or "windows-x86_64"
    std::string launch;
    std::vector<PackageEntry> entries;

    static ParseStatus parse(const std::string& text, PackageManifest* out,
                             std::string* error);
    const PackageEntry* find(const std::string& path) const;
};

}  // namespace update
