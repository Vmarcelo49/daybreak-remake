// assets/asset_source.cpp's extra data roots: the mount that lets the converted PSP data
// (psp-data/, D-3a) join a bundle install.
//
// The roots are ordinary folders this test writes under the system temp directory, so the
// device-free half runs anywhere the host suite does. What it pins is the ORDER — the install's
// bundles first, then the caller's own path, then the mounted roots — and the fact that a root
// answers to the install-relative key, which is why `read("data/select/16.cnv")` finds
// `<root>/data/select/16.cnv` without any reader learning a second path syntax.
//
// The bundle half needs a real game install and skips itself (exit 77) without one, like the
// other install-backed tests.
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <vector>

#include "assets/asset_source.h"
#include "assets/cnv.h"

#define CHECK(x) do { if (!(x)) { std::fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #x); return 1; } } while (false)

namespace fs = std::filesystem;
using fnd::assets::AssetSource;

namespace {

std::string writeRoot(const fs::path& base, const std::string& name, const std::string& key,
                      const std::string& contents) {
    const fs::path file = base / name / fs::u8path(key);
    fs::create_directories(file.parent_path());
    std::FILE* out = std::fopen(file.string().c_str(), "wb");
    if (!out) return {};
    std::fwrite(contents.data(), 1, contents.size(), out);
    std::fclose(out);
    return (base / name).u8string();
}

bool reads(AssetSource& source, const std::string& path, const std::string& expected) {
    std::vector<uint8_t> bytes;
    if (!source.read(path, bytes)) return false;
    return std::string(bytes.begin(), bytes.end()) == expected;
}

bool readBytes(AssetSource& source, const std::string& path, std::vector<uint8_t>& out) {
    out.clear();
    return source.read(path, out);
}

// The same discovery the other install-backed tests use (tests/combo_fixture.h's gameInstall).
std::string gameInstall() {
    if (const char* configured = std::getenv("GAME_DIR"))
        if (fs::exists(fs::path(configured) / "daybreak00.dat")) return configured;
    for (auto path = fs::current_path(); !path.empty(); path = path.parent_path()) {
        for (const auto& candidate : {path, path / "Higurashi-Daybreak"})
            if (fs::exists(candidate / "daybreak00.dat")) return candidate.string();
        if (path == path.parent_path()) break;
    }
    return {};
}

}  // namespace

int main() {
    AssetSource& source = AssetSource::instance();
    const fs::path base = fs::temp_directory_path() / "daybreak-asset-root-test";
    std::error_code ec;
    fs::remove_all(base, ec);

    const std::string first = writeRoot(base, "first", "data/select/16.cnv", "first");
    const std::string second = writeRoot(base, "second", "data/select/w18.cnv", "second-only");
    // The same key in the second root, so the order between two roots is observable.
    CHECK(!writeRoot(base, "second", "data/select/16.cnv", "second").empty());
    CHECK(!first.empty() && !second.empty());

    // Nothing mounted: the roots answer nothing, which is the state every checkout without
    // psp-data is in.
    CHECK(source.dataRoots().empty());
    CHECK(!source.exists("data/select/16.cnv"));
    std::vector<uint8_t> bytes;
    CHECK(!source.read("data/select/16.cnv", bytes));

    // A folder that is not one is refused rather than mounted empty, so the caller can name the
    // path it was given.
    CHECK(!source.mountDataRoot((base / "missing").u8string()));
    CHECK(!source.mountDataRoot(""));
    CHECK(source.dataRoots().empty());

    CHECK(source.mountDataRoot(first));
    CHECK(source.mountDataRoot(second));
    CHECK(source.dataRoots().size() == 2);
    // The earlier root wins a key both carry, exactly as an earlier bundle does.
    CHECK(reads(source, "data/select/16.cnv", "first"));
    // A key only the later root carries is still found, and by absolute path too.
    CHECK(reads(source, "data/select/w18.cnv", "second-only"));
    CHECK(reads(source, first + "/data/select/16.cnv", "first"));
    CHECK(source.exists("data/select/16.cnv"));

    // Mounting the same folder twice is not two roots.
    CHECK(source.mountDataRoot(first));
    CHECK(source.dataRoots().size() == 2);

    // Directory listing: bundle-style keys, sorted inside a root, each one readable.
    const std::vector<std::string> listed = source.listDir("data/select");
    CHECK(listed.size() == 2);
    CHECK(listed[0] == "data/select/16.cnv" && listed[1] == "data/select/w18.cnv");
    for (const std::string& key : listed) CHECK(source.exists(key));

    // With the install open, its bundles answer first: a root carrying the same game path must
    // not be able to replace a shipped texture. `data/select/00.cnv` is the install's own Rena
    // portrait, a CNV image, so the bytes that come back are identifiable and are not the junk
    // the root holds under that name.
    const std::string junk = "not-a-cnv-at-all";
    const std::string game = gameInstall();
    if (!game.empty()) {
        CHECK(!writeRoot(base, "shadow", "data/select/00.cnv", junk).empty());
        CHECK(source.mountDataRoot((base / "shadow").u8string()));
        CHECK(source.openInstall(game));
        CHECK(source.bundlesOpen());
        CHECK(readBytes(source, "data/select/00.cnv", bytes));
        CHECK(std::string(bytes.begin(), bytes.end()) != junk);
        CHECK(xm::isCnvImage(bytes.data(), bytes.size()));
        // A root-only name is still reachable with bundles open.
        CHECK(reads(source, "data/select/w18.cnv", "second-only"));
        source.closeInstall();
    }

    source.clearDataRoots();
    CHECK(source.dataRoots().empty());
    CHECK(!source.exists("data/select/16.cnv"));
    CHECK(!source.read("data/select/w18.cnv", bytes));
    CHECK(source.listDir("data/select").empty());

    fs::remove_all(base, ec);
    if (game.empty()) {
        std::printf("asset_source_mount_test: SKIP the bundle-order half (no game install; "
                    "GAME_DIR or Higurashi-Daybreak)\n");
        return 77;
    }
    std::printf("asset_source_mount_test: extra data roots mount, order, list, clear and lose "
                "to the install's bundles\n");
    return 0;
}
