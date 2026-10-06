#pragma once
// platform/web_assets.h — the parts of web asset delivery that are not the browser.
//
// Why this seam exists: the delivery client (platform/asset_client.cpp) can only be
// compiled for Emscripten, but most of what can be *wrong* in it is not
// browser-specific — the manifest parser, the hash the client validates against,
// the progress arithmetic, and the mapping from a logical asset id to the path the
// asset layer will later fopen(). Those live here so the host suite exercises them
// on every build (tests/web_assets_test.cpp) instead of only in a browser run.
//
// PORT DECISION, not recovered behaviour: the manifest format, the content-hash
// validation and the per-asset cache identity are this issue's design. The rules the
// ids themselves follow (precedence, case folding, the CP932 spellings) are recovered
// and live in the native asset source and in webdelivery/daybreak_web/bundles.py.
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace plat {

// One line of a delivery manifest: what to fetch, and what it must hash to.
struct WebAssetEntry {
    std::string id;              // logical path, e.g. "data/title/logo.cnv"
    std::string sha256;          // 64 lowercase hex digits
    uint64_t    size = 0;        // decoded payload size in bytes
    uint64_t    gzipSize = 0;    // wire size when the server precompressed it (0 = raw)
    bool        gate = false;    // required before the first usable screen

    // What a cold fetch of this asset costs on the wire.
    uint64_t transferSize() const { return gzipSize ? gzipSize : size; }
};

// A parsed manifest: the entries plus the catalog identity they came from.
struct WebAssetManifest {
    std::string version;         // the server's catalogVersion
    std::string group;           // "startup", "match:stage21:rena:0", ...
    uint64_t    declaredBytes = 0;
    std::vector<WebAssetEntry> entries;

    std::size_t gateCount() const;
    uint64_t    transferBytes() const;
};

// Parses the tab-separated manifest served by /api/manifest/*. Returns false and
// fills `error` on the first malformed line; `out` is then unusable. A manifest with
// no entries is an error: an empty group would silently mean "nothing to load".
bool parseAssetManifest(const std::string& text, WebAssetManifest& out, std::string& error);

// SHA-256 of `data`, lowercase hex. Validated against the FIPS 180-4 vectors by the
// host test before it is trusted for anything.
std::string sha256Hex(const uint8_t* data, std::size_t size);
inline std::string sha256Hex(const std::vector<uint8_t>& data) {
    return sha256Hex(data.data(), data.size());
}

// Every spelling of one asset's path that the delivered tree has to answer.
//
// The game resolves a name with MSVC __stricmp (0x00663c20) — the bundle index folds
// ASCII case — and the native layer reproduces that through the bundle lookup. The
// delivered tree is a plain filesystem, which does not fold, so the port's own probe
// spellings have to exist as paths. The first entry is the catalogued spelling; the
// rest are the variants this port actually probes, measured rather than guessed:
//
//   data/item/04.X        probed as data/item/04.x        (weapon mesh)
//   data/object/p00.cnv   probed as data/object/P00.cnv   (battle HUD atlas)
//   data/directX/toon.cnv probed as data/directx/toon.cnv (toon ramp candidates)
//
// This is a bounded set, not the whole case-equivalence class (which is exponential in
// the number of letters and could never be materialised): it covers the spellings the
// loaders in this tree use. A future delivery could resolve case-insensitively at lookup
// time instead, which is the general fix.
std::vector<std::string> webAssetCaseVariants(const std::string& id);

// Where one asset is materialised for the asset layer: `mount` + the logical id.
// Returns "" when the id is not a safe relative path — an id is server-supplied text,
// and the file it names is opened by the unchanged native reader, so this is the one
// place that decides what may be written into the virtual filesystem.
std::string webAssetTargetPath(const std::string& mount, const std::string& id);

// Progress over one requested set, in the two units that matter: assets (how far
// along) and bytes (how much of the transfer is done).
struct AssetProgress {
    std::size_t total = 0;       // assets in the set
    std::size_t ready = 0;       // validated and materialised
    std::size_t failed = 0;      // gave up after the retry budget
    std::size_t inflight = 0;    // requests outstanding right now
    std::size_t cached = 0;      // ready without a network request this session
    uint64_t    bytesTotal = 0;  // sum of transferSize over the set
    uint64_t    bytesDone = 0;   // sum over ready + failed

    // An empty set is NOT complete: before a manifest arrives, total is 0, and a
    // readiness barrier that read that as "done" would let a battle start with none of
    // its assets requested (measured in a browser run — the match group's request was
    // issued and the barrier returned immediately).
    bool complete() const { return total > 0 && ready + failed >= total; }
    bool gateMet(std::size_t gateTotal) const { return ready + failed >= gateTotal; }
    double fraction() const {
        return total == 0 ? 1.0 : double(ready + failed) / double(total);
    }
    // One line for the console/overlay: what the plan's "visible progress" means.
    std::string line(const std::string& label) const;
};

}  // namespace plat
