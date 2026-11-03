#include "update_test_suites.h"

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

#include "update/crypto.h"
#include "update/package_manifest.h"
#include "update/paths.h"
#include "update/update_manifest.h"
#include "update/version.h"

namespace {

using update_test::check;
using update_test::expect;
using update_test::expectEqual;

std::string replaceFirst(std::string text, const std::string& from,
                         const std::string& to) {
    const std::size_t at = text.find(from);
    if (at != std::string::npos) text.replace(at, from.size(), to);
    return text;
}

std::string packageManifest(const std::string& version, const std::string& target,
                            const std::string& launch, const std::string& body) {
    return "format = 1\nversion = " + version + "\ntarget = " + target +
           "\nlaunch = " + launch + "\n[files]\n" + body;
}

const std::string kHashA(64, 'a');
const std::string kHashB(64, 'b');
const std::string kHashC(64, 'c');

const std::string kValidLinux = packageManifest(
    "0.2.1", "linux-x86_64", "daybreak",
    kHashB + "  5  x  daybreak\n" + kHashA + "  5  -  daybreak-bin\n");

const std::string kValidWindows = packageManifest(
    "0.2.1", "windows-x86_64", "DaybreakRemake.exe",
    kHashA + "  3  -  DaybreakRemake.exe\n" + kHashB + "  2  -  SDL3.dll\n");

const std::string kValidUpdate =
    "format = 1\n"
    "version = 1.0.0\n"
    "notes = https://github.com/Vmarcelo49/daybreak-remake/releases/tag/v1.0.0\n"
    "[linux-x86_64]\n"
    "archive = daybreak-1.0.0-linux-x86_64.tar.gz\n"
    "size = 19876543\n"
    "sha256 = " + kHashA + "\n"
    "[windows-x86_64]\n"
    "archive = daybreak-1.0.0-2d33582-windows-x86_64.zip\n"
    "size = 19876544\n"
    "sha256 = " + kHashB + "\n";

void testVersion() {
    update::Version version;
    std::string error;
    check(update::Version::parse("1.2.3", &version, &error), "1.2.3 parses");
    expectEqual(version.major, 1, "major");
    expectEqual(version.minor, 2, "minor");
    expectEqual(version.patch, 3, "patch");
    expect(version.toString(), "1.2.3", "toString");

    for (const char* bad : {"1.2", "1.2.3.4", "01.2.3", "1.02.3", "1.2.03", "v1.2.3",
                            "1.2.3-rc1", "1.2.3 ", "", "1..3", "1.2.x", "-1.2.3"}) {
        update::Version ignored;
        check(!update::Version::parse(bad, &ignored, &error),
              std::string("rejects version '") + bad + "'");
    }
    update::Version big;
    check(update::Version::parse("4294967295.0.0", &big, &error), "uint32 maximum");
    check(!update::Version::parse("4294967296.0.0", &big, &error), "overflow rejected");

    update::Version a;
    update::Version b;
    update::Version c;
    update::Version::parse("1.2.3", &a, &error);
    update::Version::parse("1.2.4", &b, &error);
    update::Version::parse("1.3.0", &c, &error);
    check(a < b && b < c, "versions order");
    check(!(b < a) && a == a && a != b, "equality and inequality");
}

void testPaths() {
    std::string error;
    for (const char* good : {"a", "a/b", "assets/fonts/x.otf", "LICENSES/GPL-3.0.txt",
                             "A-b_c.d+e~f", "dir/.hidden", "caf\xc3\xa9/x"}) {
        check(update::paths::validRelative(good, &error),
              std::string("accepts '") + good + "' (" + error + ")");
    }
    for (const char* bad : {"", "/abs", "a\\b", "C:evil", "a/../b", "a/./b", "a//b",
                            "a.", "a ", "a/b.", "a/b ", "CON", "con.txt", "aux/x",
                            "COM1", "LPT9.log", "a<b", "a>b", "a:b", "a\"b", "a|b",
                            "a?b", "a*b", "a\x01" "b", "caf\xe9/x"}) {
        check(!update::paths::validRelative(bad, &error),
              std::string("rejects '") + bad + "'");
    }
    check(!update::paths::validSet({"A.txt", "a.txt"}, &error),
          "rejects a case collision");
    check(update::paths::validSet({"a.txt", "b.txt"}, &error),
          "accepts distinct names");
    check(!update::paths::validSet({"a", "a/b"}, &error),
          "rejects a file that is also a directory");
    check(update::paths::validSet({"a/b", "a/c"}, &error), "accepts siblings");
}

void testPackageManifest() {
    update::PackageManifest manifest;
    std::string error;
    check(update::PackageManifest::parse(kValidLinux, &manifest, &error) ==
              update::ParseStatus::Ok,
          "valid linux manifest parses: " + error);
    expectEqual(manifest.entries.size(), 2, "two entries");
    expect(manifest.version, "0.2.1", "version");
    expect(manifest.target, "linux-x86_64", "target");
    const update::PackageEntry* launch = manifest.find("daybreak");
    check(launch != nullptr && launch->executable, "the launch entry is executable");
    check(manifest.find("nope") == nullptr, "find returns null for an absent path");

    update::PackageManifest windows;
    check(update::PackageManifest::parse(kValidWindows, &windows, &error) ==
              update::ParseStatus::Ok,
          "valid windows manifest parses: " + error);

    update::PackageManifest ignored;
    check(update::PackageManifest::parse(replaceFirst(kValidLinux, "format = 1",
                                                      "format = 2"),
                                         &ignored, &error) ==
              update::ParseStatus::UnknownFormat,
          "an unknown format is its own status");

    std::string crlf;
    for (const char character : kValidLinux) {
        if (character == '\n') crlf += '\r';
        crlf += character;
    }
    check(update::PackageManifest::parse(crlf, &ignored, &error) ==
              update::ParseStatus::Invalid,
          "CRLF is rejected");

    std::string noNewline = kValidLinux;
    noNewline.pop_back();
    check(update::PackageManifest::parse(noNewline, &ignored, &error) ==
              update::ParseStatus::Invalid,
          "a missing final newline is rejected");

    check(update::PackageManifest::parse(
              replaceFirst(kValidLinux, kHashA, kHashA.substr(1) + "g"), &ignored,
              &error) == update::ParseStatus::Invalid,
          "a non-hex hash is rejected");
    check(update::PackageManifest::parse(
              replaceFirst(kValidLinux, "  5  -  daybreak-bin", "  05  -  daybreak-bin"),
              &ignored, &error) == update::ParseStatus::Invalid,
          "a leading zero size is rejected");
    check(update::PackageManifest::parse(
              packageManifest("0.2.1", "linux-x86_64", "daybreak",
                              kHashA + "  5  -  b\n" + kHashB + "  5  x  a\n"),
              &ignored, &error) == update::ParseStatus::Invalid,
          "unsorted entries are rejected");
    check(update::PackageManifest::parse(
              packageManifest("0.2.1", "linux-x86_64", "daybreak",
                              kHashA + "  5  x  a\n" + kHashA + "  5  -  a\n"),
              &ignored, &error) == update::ParseStatus::Invalid,
          "a duplicate entry is rejected");
    check(update::PackageManifest::parse(
              replaceFirst(kValidLinux, "launch = daybreak", "launch = nope"), &ignored,
              &error) == update::ParseStatus::Invalid,
          "a launch that is not listed is rejected");
    check(update::PackageManifest::parse(
              packageManifest("0.2.1", "linux-x86_64", "run",
                              kHashA + "  5  -  run\n"),
              &ignored, &error) == update::ParseStatus::Invalid,
          "a non-executable launch on Linux is rejected");
    check(update::PackageManifest::parse(
              packageManifest("0.2.1", "windows-x86_64", "run",
                              kHashA + "  5  x  run\n"),
              &ignored, &error) == update::ParseStatus::Invalid,
          "a windows manifest with mode 'x' is rejected");
    check(update::PackageManifest::parse(
              packageManifest("0.2.1", "linux-x86_64", "a",
                              kHashA + "  5  x  a\n" + kHashB + "  5  -  package-manifest.txt\n"),
              &ignored, &error) == update::ParseStatus::Invalid,
          "a manifest listing itself is rejected");
    check(update::PackageManifest::parse(
              packageManifest("0.2.1", "linux-x86_64", "a",
                              kHashA + "  5  x  ../evil\n"),
              &ignored, &error) == update::ParseStatus::Invalid,
          "a traversal path is rejected");
    check(update::PackageManifest::parse(
              replaceFirst(kValidLinux, "[files]\n", "[files]\n\n"), &ignored,
              &error) == update::ParseStatus::Invalid,
          "a blank line is rejected");
}

void testUpdateManifest() {
    update::UpdateManifest manifest;
    std::string error;
    check(update::UpdateManifest::parse(kValidUpdate, &manifest, &error) ==
              update::ParseStatus::Ok,
          "valid update manifest parses: " + error);
    expect(manifest.version.toString(), "1.0.0", "version");
    expect(manifest.linuxArchive.archive, "daybreak-1.0.0-linux-x86_64.tar.gz",
           "linux archive");
    expectEqual(manifest.linuxArchive.size, 19876543, "linux size");
    expect(manifest.windowsArchive.sha256, kHashB, "windows sha256");

    update::UpdateManifest ignored;
    check(update::UpdateManifest::parse(replaceFirst(kValidUpdate, "format = 1",
                                                     "format = 7"),
                                        &ignored, &error) ==
              update::ParseStatus::UnknownFormat,
          "an unknown update-manifest format is its own status");
    check(update::UpdateManifest::parse(replaceFirst(kValidUpdate, "version = 1.0.0",
                                                     "version = 1.0"),
                                        &ignored, &error) ==
              update::ParseStatus::Invalid,
          "a non-semver version is rejected");
    check(update::UpdateManifest::parse(kValidUpdate + "\n", &ignored, &error) ==
              update::ParseStatus::Invalid,
          "an extra line is rejected");
    check(update::UpdateManifest::parse(
              replaceFirst(kValidUpdate, "notes = https://", "notes = http://"), &ignored,
              &error) == update::ParseStatus::Invalid,
          "a non-https notes URL is rejected");
    check(update::UpdateManifest::parse(
              replaceFirst(kValidUpdate, "sha256 = " + kHashA, "sha256 = " + kHashA.substr(1)),
              &ignored, &error) == update::ParseStatus::Invalid,
          "a short sha256 is rejected");
    check(update::UpdateManifest::parse(
              replaceFirst(kValidUpdate, "[linux-x86_64]", "[windows-x86_64]"), &ignored,
              &error) == update::ParseStatus::Invalid,
          "a swapped section header is rejected");
    std::string noNewline = kValidUpdate;
    noNewline.pop_back();
    check(update::UpdateManifest::parse(noNewline, &ignored, &error) ==
              update::ParseStatus::Invalid,
          "an update manifest without a final newline is rejected");
}

void testSha256() {
    const auto digest = [](const std::string& text) {
        return update::sha256Hex(text.data(), text.size());
    };
    expect(digest(""), "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
           "SHA-256 of the empty string");
    expect(digest("abc"), "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad",
           "SHA-256 of abc");
    expect(digest("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"),
           "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1",
           "SHA-256 of the 448-bit FIPS message");

    // One million 'a', fed through the streaming API in awkward chunks.
    update::Sha256 hash;
    const std::string chunk(1000, 'a');
    for (int index = 0; index < 1000; ++index) {
        hash.update(chunk.data(), chunk.size());
    }
    std::uint8_t raw[32];
    hash.final(raw);
    expect(update::toHex(raw, sizeof raw),
           "cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0",
           "SHA-256 of one million 'a'");

    update::Sha256 pieces;
    const std::string message = "the quick brown fox jumps over the lazy dog";
    std::size_t offset = 0;
    for (const std::size_t step : {1u, 3u, 7u, 5u, 11u}) {
        const std::size_t take = std::min(step, message.size() - offset);
        pieces.update(message.data() + offset, take);
        offset += take;
    }
    pieces.update(message.data() + offset, message.size() - offset);
    std::uint8_t streamed[32];
    pieces.final(streamed);
    expect(update::toHex(streamed, sizeof streamed),
           "05c6e08f1d9fdafa03147fcb8f82f124c76d2f70e3d989dc8aadb5e7d7450bec",
           "streaming in odd chunks matches");
}

}  // namespace

int runUpdateLogicTests() {
    testVersion();
    testPaths();
    testPackageManifest();
    testUpdateManifest();
    testSha256();
    return update_test::report("update_logic_test");
}

#ifndef DAYBREAK_UPDATE_SELFTEST
int main() {
    return runUpdateLogicTests();
}
#endif
