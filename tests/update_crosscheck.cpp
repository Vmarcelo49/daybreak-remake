// tests/update_crosscheck.cpp — the C++ half of the Python/C++ agreement test.
//
// tests/update_crosscheck_test.py builds synthetic manifests and archives, asks this binary
// and the Python tools the same question, and fails when the two disagree: the Python side
// writes what a release contains, so a difference would mean the game refuses something the
// release tool published (or accepts what it refused). It is a test tool, not shipped.
//
// An archive mode verdict is a *package* verdict, not a structural one: the release-side
// reader returns the package's own file list, so an archive with no package-manifest.txt is
// refused there, and the updater refuses it too (updater.cpp:581). The parser below is the
// updater's, so the two halves answer the same question.
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#include "update/archive.h"
#include "update/package_manifest.h"
#include "update/update_manifest.h"

namespace {

std::vector<std::uint8_t> readFile(const std::string& path) {
    std::ifstream input(path, std::ios::binary);
    return std::vector<std::uint8_t>(std::istreambuf_iterator<char>(input),
                                     std::istreambuf_iterator<char>());
}

std::string readText(const std::string& path) {
    const std::vector<std::uint8_t> bytes = readFile(path);
    return std::string(bytes.begin(), bytes.end());
}

int fail(const std::string& message) {
    std::fprintf(stderr, "%s\n", message.c_str());
    return 1;
}

// A package's manifest is at the archive's root: flat in the Windows zip, under the single
// top-level directory in the Linux tar.gz.
bool isPackageManifest(const std::string& path) {
    const std::size_t slash = path.find_last_of('/');
    return (slash == std::string::npos ? path : path.substr(slash + 1)) ==
           update::kPackageManifestName;
}

}  // namespace

int main(int argc, char** argv) {
    if (argc < 3) {
        std::fprintf(stderr,
                     "usage: update_crosscheck manifest|update-manifest <file>\n"
                     "       update_crosscheck archive tar|zip <file>\n");
        return 2;
    }
    const std::string mode = argv[1];
    if (mode == "manifest") {
        update::PackageManifest manifest;
        std::string error;
        return update::PackageManifest::parse(readText(argv[2]), &manifest, &error) ==
                       update::ParseStatus::Ok
                   ? 0
                   : fail(error);
    }
    if (mode == "update-manifest") {
        update::UpdateManifest manifest;
        std::string error;
        return update::UpdateManifest::parse(readText(argv[2]), &manifest, &error) ==
                       update::ParseStatus::Ok
                   ? 0
                   : fail(error);
    }
    if (mode == "archive" && argc >= 4) {
        const std::string kind = argv[2];
        std::string error;
        std::unique_ptr<update::Archive> archive =
            kind == "tar" ? update::Archive::openTarGz(readFile(argv[3]), &error)
                          : update::Archive::openZip(readFile(argv[3]), &error);
        if (archive == nullptr) return fail(error);
        std::string manifestText;
        bool haveManifest = false;
        for (const update::ArchiveEntry& entry : archive->entries()) {
            if (entry.isDirectory) continue;
            const bool isManifest = isPackageManifest(entry.path);
            const bool extracted = archive->extract(
                entry.path,
                [&manifestText, &haveManifest, isManifest](const std::uint8_t* data,
                                                           std::size_t size) {
                    if (isManifest) {
                        haveManifest = true;
                        manifestText.append(reinterpret_cast<const char*>(data), size);
                    }
                    return true;
                },
                &error);
            if (!extracted) return fail(entry.path + ": " + error);
        }
        if (!haveManifest) return fail("the archive has no package-manifest.txt");
        update::PackageManifest manifest;
        std::string parseError;
        if (update::PackageManifest::parse(manifestText, &manifest, &parseError) !=
            update::ParseStatus::Ok) {
            return fail(parseError);
        }
        return 0;
    }
    std::fprintf(stderr, "update_crosscheck: unknown mode %s\n", mode.c_str());
    return 2;
}
