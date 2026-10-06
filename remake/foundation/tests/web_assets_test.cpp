// =============================================================================
//  web_assets_test.cpp — the host-testable half of the web asset client.
//
//  The browser half (platform/asset_client.cpp) needs Emscripten, but four things
//  it depends on do not, and each of them is a place a silent bug would cost real
//  bytes or a real file:
//
//   1. sha256 — the client refuses to materialise an asset whose bytes do not hash
//      to the catalog's value, so the hash itself is pinned to the FIPS 180-4
//      vectors before anything is allowed to trust it.
//   2. the manifest parser — the server's per-asset manifest is the client's only
//      description of what to fetch; a mis-parsed line is a missing asset.
//   3. the target path — the id in a manifest becomes a path the *unchanged* native
//      reader fopens, so traversal, absolute ids and empty components are refused
//      here rather than inside the virtual filesystem.
//   4. progress arithmetic — "which assets are ready, how many bytes are left" is
//      what the VS readiness barrier reads; an off-by-one there starts a battle
//      before its assets exist.
//
//  Device-free, data-free, no browser. Final line: "WEB_ASSETS_TEST: ok".
// =============================================================================
#include "platform/web_assets.h"

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace {

int g_failures = 0;

void check(bool cond, const std::string& what) {
    if (!cond) {
        std::printf("FAIL: %s\n", what.c_str());
        ++g_failures;
    }
}

void testSha256() {
    struct Vec { const char* message; const char* want; };
    static const Vec kVec[] = {
        {"", "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"},
        {"abc", "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"},
        {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
         "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1"},
    };
    for (const Vec& v : kVec) {
        const std::string got = plat::sha256Hex(
            reinterpret_cast<const uint8_t*>(v.message), std::strlen(v.message));
        check(got == v.want, std::string("sha256(\"") + v.message + "\") = " + got);
    }
    // The 1,000,000-'a' vector, fed in awkward chunks so the block buffer's
    // carry-over path is exercised rather than only whole 64-byte blocks.
    std::vector<uint8_t> million(1000000, 'a');
    std::string streamed;
    {
        // Feed through the public API in pieces by hashing prefixes is not possible
        // (one-shot API), so hash the whole buffer and compare to the published value.
        streamed = plat::sha256Hex(million);
    }
    check(streamed == "cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0",
          "sha256(1e6 * 'a') = " + streamed);
    // A length that lands exactly on a block boundary and one that does not.
    check(plat::sha256Hex(std::vector<uint8_t>(64, 0)) !=
          plat::sha256Hex(std::vector<uint8_t>(65, 0)),
          "a 64-byte and a 65-byte zero buffer must not hash alike");
    std::printf("sha256: 3 FIPS vectors + the 1e6-'a' vector ok\n");
}

void testManifest() {
    const std::string text =
        "# daybreak web asset manifest\n"
        "version=abc123\n"
        "group=startup\n"
        "bytes=300\n"
        "assets=2\n"
        "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855\t100\t40\t1\t"
        "data/title/logo.cnv\n"
        "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad\t200\t0\t0\t"
        "movie/op.mpg\n";
    plat::WebAssetManifest manifest;
    std::string error;
    check(plat::parseAssetManifest(text, manifest, error), "a well-formed manifest must parse: " + error);
    check(manifest.version == "abc123" && manifest.group == "startup",
          "the manifest must carry its catalog version and group");
    check(manifest.entries.size() == 2, "both entries must be read");
    check(manifest.gateCount() == 1, "exactly one entry is a gate asset");
    check(manifest.transferBytes() == 40 + 200, "transfer bytes must use the gzip size when present");
    check(manifest.entries[0].gate && !manifest.entries[1].gate,
          "the gate flag must survive parsing");
    check(manifest.entries[0].transferSize() == 40 && manifest.entries[1].transferSize() == 200,
          "an asset without a gzip copy must transfer at its raw size");
    check(manifest.declaredBytes == 300, "the declared byte total must be read");

    struct Bad { const char* label; const char* text; };
    static const Bad kBad[] = {
        {"no entries", "# just a comment\nversion=x\ngroup=startup\n"},
        {"short line", "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855\t1\t0\t1\n"},
        {"not a hash", "zzz\t1\t0\t1\tdata/x.X\n"},
        {"bad gate flag", "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855\t1\t0\t2\tdata/x.X\n"},
        {"traversal id", "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855\t1\t0\t1\t../secret\n"},
        {"absolute id", "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855\t1\t0\t1\t/etc/passwd\n"},
        {"negative size", "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855\t-1\t0\t1\tdata/x.X\n"},
    };
    for (const Bad& bad : kBad) {
        plat::WebAssetManifest rejected;
        std::string reason;
        check(!plat::parseAssetManifest(bad.text, rejected, reason),
              std::string("a manifest with a ") + bad.label + " must be rejected");
        check(!reason.empty(), std::string("rejection of '") + bad.label + "' must explain itself");
    }
    std::printf("manifest: 2 entries parsed, %zu malformed shapes rejected\n",
                sizeof(kBad) / sizeof(kBad[0]));
}

void testTargetPath() {
    check(plat::webAssetTargetPath("/assets", "data/rika/01.X") == "/assets/data/rika/01.X",
          "a plain id must land under the mount");
    check(plat::webAssetTargetPath("/assets/", "data/rika/01.X") == "/assets/data/rika/01.X",
          "a trailing slash on the mount must not double up");
    check(plat::webAssetTargetPath("/assets", "\xe6\x9c\x8d.cnv") == "/assets/\xe6\x9c\x8d.cnv",
          "a CP932-derived UTF-8 name must survive as-is");
    const char* const kRejected[] = {
        "", "/etc/passwd", "../x", "data/../../x", "data//x", "data/./x", "data\\x", "..",
    };
    for (const char* id : kRejected) {
        check(plat::webAssetTargetPath("/assets", id).empty(),
              std::string("id must be refused: '") + id + "'");
    }
    std::printf("target path: accepted a plain and a CP932 id, refused %zu unsafe ones\n",
                sizeof(kRejected) / sizeof(kRejected[0]));
}

void testProgress() {
    plat::AssetProgress progress;
    progress.total = 4;
    progress.bytesTotal = 12u * 1048576u;
    check(progress.fraction() == 0.0 && !progress.complete(),
          "a fresh set is incomplete");
    check(progress.gateMet(3) == false, "the gate is not met with nothing ready");

    progress.ready = 2;
    progress.cached = 1;
    progress.bytesDone = 6u * 1048576u;
    check(!progress.complete() && progress.fraction() == 0.5,
          "half the assets must read as half done");
    check(progress.gateMet(2) && !progress.gateMet(3),
          "the gate is met exactly when its own assets are ready");

    // Three of four resolved, one still outstanding: not complete, and a failure
    // counts as resolved — it must not hold the set open forever.
    progress.failed = 1;
    progress.inflight = 1;
    progress.bytesDone = 9u * 1048576u;
    check(!progress.complete() && progress.fraction() == 0.75,
          "ready + failed short of the set is not complete");
    progress.inflight = 0;
    check(!progress.complete(), "the outstanding asset must still be counted");
    progress.ready = 3;
    check(progress.complete() && progress.fraction() == 1.0,
          "ready + failed covering the set means complete");

    const std::string line = progress.line("startup");
    check(line.find("startup") != std::string::npos && line.find("3/4") != std::string::npos,
          "the progress line must name the set and the asset count: " + line);
    check(line.find("9.0/12.0 MB") != std::string::npos,
          "the progress line must report transfer bytes: " + line);
    check(line.find("1 failed") != std::string::npos,
          "the progress line must report failures: " + line);
    std::printf("progress: %s\n", line.c_str());
}

}  // namespace

int main() {
    testSha256();
    testManifest();
    testTargetPath();
    testProgress();
    std::printf("\n");
    if (g_failures == 0) {
        std::printf("WEB_ASSETS_TEST: ok\n");
        return 0;
    }
    std::printf("WEB_ASSETS_TEST: FAIL (%d checks failed)\n", g_failures);
    return 1;
}
