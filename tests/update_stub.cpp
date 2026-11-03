// tests/update_stub.cpp — the step-1 + step-2 + step-3 chain without the game (issue #100).
//
// Installed in a fake package as its `daybreak` entry point. It checks, applies and
// relaunches; the relaunched copy is the new package's stub, which prints the version it
// now is and the version it was updated from. tests/update_apply_test.cpp drives it.
#include <array>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <cstring>
#include <filesystem>
#include <string>
#include <vector>

#include "platform/http.h"
#include "update/package_manifest.h"
#include "update/updater.h"

namespace {

std::string valueOf(const std::string& argument, const std::string& flag) {
    if (argument.rfind(flag, 0) != 0) return std::string();
    return argument.substr(flag.size());
}

std::array<std::uint8_t, 32> parseKey(const std::string& hex) {
    std::array<std::uint8_t, 32> key{};
    for (std::size_t index = 0; index < key.size(); ++index) {
        if (index * 2 + 1 >= hex.size()) break;
        key[index] = static_cast<std::uint8_t>(
            std::stoi(hex.substr(index * 2, 2), nullptr, 16));
    }
    return key;
}

std::string installedVersion(const std::filesystem::path& root) {
    std::ifstream input(root / update::kPackageManifestName, std::ios::binary);
    if (!input) return "?";
    std::string text((std::istreambuf_iterator<char>(input)),
                     std::istreambuf_iterator<char>());
    update::PackageManifest manifest;
    std::string error;
    if (update::PackageManifest::parse(text, &manifest, &error) != update::ParseStatus::Ok) {
        return "?";
    }
    return manifest.version;
}

}  // namespace

int main(int argc, char** argv) {
    std::filesystem::path root;
    std::string manifestUrl;
    std::string keyHex;
    std::string current;
    std::string updatedFrom;
    std::vector<std::string> forwarded;
    for (int index = 1; index < argc; ++index) {
        const std::string argument = argv[index];
        if (!valueOf(argument, "--root=").empty()) {
            root = std::filesystem::u8path(valueOf(argument, "--root="));
        } else if (!valueOf(argument, "--manifest=").empty()) {
            manifestUrl = valueOf(argument, "--manifest=");
        } else if (!valueOf(argument, "--key=").empty()) {
            keyHex = valueOf(argument, "--key=");
        } else if (!valueOf(argument, "--current=").empty()) {
            current = valueOf(argument, "--current=");
        } else if (argument.rfind("--updated-from=", 0) == 0) {
            updatedFrom = valueOf(argument, "--updated-from=");
        }
        // Everything, including this stub's own flags, is handed to the new build; the
        // real game forwards its own command line the same way.
        forwarded.push_back(argument);
    }
    if (root.empty()) {
        std::fprintf(stderr, "update_stub: --root is required\n");
        return 2;
    }
    if (!updatedFrom.empty()) {
        std::printf("update_stub: version %s updated-from %s\n",
                    installedVersion(root).c_str(), updatedFrom.c_str());
        return 0;
    }

    update::CheckSettings settings;
    settings.manifestUrl = manifestUrl;
    update::Version currentVersion;
    std::string error;
    if (!update::Version::parse(current, &currentVersion, &error)) {
        std::fprintf(stderr, "update_stub: --current is not X.Y.Z\n");
        return 2;
    }
    settings.currentVersion = currentVersion;
    settings.keys.push_back(parseKey(keyHex));
    const update::CheckResult check = update::check(settings);
    if (check.status != update::CheckStatus::Available) {
        std::printf("update_stub: no update (%d) %s\n", static_cast<int>(check.status),
                    check.error.c_str());
        return 0;
    }

    update::ApplySettings applySettings;
    applySettings.root = root;
    applySettings.manifest = update::UpdateManifest{};
    {
        // Re-parse the manifest the check accepted: the stub keeps the bytes simple by
        // fetching them again through the same URL.
        plat::HttpRequest request;
        request.url = manifestUrl;
        request.maxBytes = 64 * 1024;
        std::string text;
        const plat::HttpResult result = plat::httpGet(
            request,
            [&text](const std::uint8_t* data, std::size_t size) {
                text.append(reinterpret_cast<const char*>(data), size);
                return true;
            },
            nullptr);
        if (result.error != plat::HttpError::None ||
            update::UpdateManifest::parse(text, &applySettings.manifest, &error) !=
                update::ParseStatus::Ok) {
            std::fprintf(stderr, "update_stub: cannot read the manifest: %s\n",
                         error.c_str());
            return 2;
        }
    }
    applySettings.manifestUrl = manifestUrl;
    const update::ApplyResult applied = update::apply(applySettings);
    if (applied.status != update::ApplyStatus::Ok) {
        std::fprintf(stderr, "update_stub: apply failed: %s\n", applied.error.c_str());
        return 1;
    }
    std::printf("update_stub: applied %s, relaunching %s\n", applied.version.toString().c_str(),
                applied.launch.c_str());
    std::fflush(stdout);
    if (!update::relaunch(root, applied.launch, forwarded, current, &error)) {
        std::fprintf(stderr, "update_stub: relaunch failed: %s\n", error.c_str());
        return 1;
    }
    return 0;
}
