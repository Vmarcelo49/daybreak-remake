// tests/update_selftest.cpp — the update suites as one binary for the Windows build, plus
// the one opt-in live check.
//
// CTest does not run in the MinGW cross-build, so the same three suites (compiled with
// DAYBREAK_UPDATE_SELFTEST, which removes their own mains) run here on a real machine.
// `--live <url>` is the only check that touches the network: it fetches a real release
// asset through the real redirect chain and prints its size and SHA-256. It is never part
// of CTest, and the owner runs it on Windows (docs/AUTO-UPDATE.md).
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>

#include "platform/http.h"
#include "update/crypto.h"
#include "update_test_suites.h"

namespace {

int live(const std::string& url) {
    plat::HttpRequest request;
    request.url = url;
    request.maxBytes = 256ull * 1024 * 1024;
    update::Sha256 hash;
    std::uint64_t received = 0;
    std::uint64_t total = 0;
    const plat::HttpResult result = plat::httpGet(
        request,
        [&hash, &received](const std::uint8_t* data, std::size_t size) {
            hash.update(data, size);
            received += size;
            return true;
        },
        [&total](std::uint64_t, std::uint64_t announced) {
            total = announced;
            return true;
        });
    if (result.error != plat::HttpError::None) {
        std::fprintf(stderr, "update_selftest: live fetch failed: %s\n",
                     result.message.c_str());
        return 1;
    }
    std::uint8_t digest[32];
    hash.final(digest);
    std::printf(
        "update_selftest: live fetch ok: %llu bytes (announced %llu), sha256 %s\n",
        static_cast<unsigned long long>(received),
        static_cast<unsigned long long>(total),
        update::toHex(digest, sizeof digest).c_str());
    return 0;
}

}  // namespace

int main(int argc, char** argv) {
    if (argc == 3 && std::strcmp(argv[1], "--live") == 0) return live(argv[2]);
    if (argc != 1) {
        std::fprintf(stderr, "usage: update_selftest [--live <url>]\n");
        return 2;
    }
    int failures = 0;
    failures += runUpdateLogicTests();
    failures += runUpdateCryptoTests(0, nullptr);
    failures += runUpdateArchiveTests();
    return failures == 0 ? 0 : 1;
}
