#pragma once
// update/update_manifest.h — the signed release manifest the updater downloads (issue #100).
//
// One small text file per release, at releases/latest/download/update-manifest.txt: the
// version, where the notes are, and for each platform the archive's name, size and sha256.
// The file's bytes are what the signature covers, so this parser is strict about the exact
// shape tools/make_update_manifest.py writes (docs/AUTO-UPDATE.md).
#include <cstdint>
#include <string>

#include "update/manifest_status.h"
#include "update/version.h"

namespace update {

struct UpdateArchive {
    std::string archive;
    std::uint64_t size = 0;
    std::string sha256;  // 64 lowercase hex characters
};

struct UpdateManifest {
    int format = 1;
    Version version;
    std::string notes;
    UpdateArchive linuxArchive;
    UpdateArchive windowsArchive;

    static ParseStatus parse(const std::string& text, UpdateManifest* out,
                             std::string* error);
};

}  // namespace update
