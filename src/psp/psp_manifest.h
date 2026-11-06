#pragma once
// psp/psp_manifest.h — the tracked list of PSP files the extractor collects.
//
// assets/psp/manifest.txt holds one line per file: pack path, inflated size, SHA-256. It
// is the single place the list lives, and it is what makes the extractor refuse a dump
// that is not the game it was written against. No game data, no single ISO build: only
// the bytes of the files this port reads are pinned.
#include <cstdint>
#include <string>
#include <vector>

namespace psp {

struct PspManifestEntry {
    std::string   path;      // inside PSP_GAME/USRDIR, no leading slash
    std::uint64_t size = 0;  // of the inflated payload
    std::string   sha256;    // lowercase hex
};

struct PspManifest {
    std::vector<PspManifestEntry> entries;

    // Throws std::runtime_error naming the line when a row is malformed. Blank lines and
    // lines starting with '#' are the comments the tracked file carries.
    static PspManifest parse(const std::string& text);
    static PspManifest load(const std::string& file);
};

// The manifest beside the executable ("<exeDir>/assets/psp/manifest.txt"), else the one in
// the working directory, which is how a build tree and its tests find it. Empty when
// neither exists.
std::string findPspManifest(const std::string& executableDir);

}  // namespace psp
