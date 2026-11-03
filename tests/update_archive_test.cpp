#include "update_test_suites.h"

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "update/archive.h"

namespace {

using update_test::check;
using update_test::expect;
using update_test::expectEqual;

// --- fixture builders ---------------------------------------------------------------
//
// The archives are built here rather than by a script so the suite is hermetic and the
// Windows self-test runs the same cases: stored deflate blocks are valid method-8 data and
// need no compressor, and CRC32 is the same polynomial zlib uses.

std::uint32_t crc32Of(const std::vector<std::uint8_t>& data) {
    std::uint32_t crc = 0xFFFFFFFFu;
    for (const std::uint8_t byte : data) {
        crc ^= byte;
        for (int bit = 0; bit < 8; ++bit) {
            crc = (crc >> 1) ^ (0xEDB88320u & (0u - (crc & 1u)));
        }
    }
    return ~crc;
}

// RFC 1951 stored blocks: valid deflate, so a gzip member and a method-8 zip can both be
// built without a compressor.
std::vector<std::uint8_t> storedDeflate(const std::vector<std::uint8_t>& raw) {
    std::vector<std::uint8_t> out;
    std::size_t offset = 0;
    do {
        const std::size_t take =
            std::min<std::size_t>(raw.size() - offset, 65535);
        const bool last = offset + take >= raw.size();
        out.push_back(last ? 1 : 0);
        out.push_back(static_cast<std::uint8_t>(take & 0xFF));
        out.push_back(static_cast<std::uint8_t>(take >> 8));
        out.push_back(static_cast<std::uint8_t>((~take) & 0xFF));
        out.push_back(static_cast<std::uint8_t>(((~take) >> 8) & 0xFF));
        out.insert(out.end(), raw.begin() + static_cast<std::ptrdiff_t>(offset),
                   raw.begin() + static_cast<std::ptrdiff_t>(offset + take));
        offset += take;
    } while (offset < raw.size());
    return out;
}

std::vector<std::uint8_t> gzipOf(const std::vector<std::uint8_t>& raw) {
    std::vector<std::uint8_t> out = {0x1F, 0x8B, 8, 0, 0, 0, 0, 0, 0, 0xFF};
    const std::vector<std::uint8_t> body = storedDeflate(raw);
    out.insert(out.end(), body.begin(), body.end());
    const std::uint32_t crc = crc32Of(raw);
    for (int index = 0; index < 4; ++index) {
        out.push_back(static_cast<std::uint8_t>(crc >> (8 * index)));
    }
    const std::uint32_t size = static_cast<std::uint32_t>(raw.size());
    for (int index = 0; index < 4; ++index) {
        out.push_back(static_cast<std::uint8_t>(size >> (8 * index)));
    }
    return out;
}

struct TarMember {
    std::string name;
    std::vector<std::uint8_t> data;
    std::uint32_t mode = 0644;
    char type = '0';
    std::string linkName;
};

void writeOctal(std::uint8_t* field, std::size_t size, std::uint64_t value) {
    char buffer[32] = {};
    std::snprintf(buffer, sizeof buffer, "%0*llo", static_cast<int>(size - 1),
                  static_cast<unsigned long long>(value));
    std::memcpy(field, buffer, size - 1);
    field[size - 1] = 0;
}

std::vector<std::uint8_t> tarHeader(const TarMember& member,
                                    const std::string& magic) {
    std::vector<std::uint8_t> header(512, 0);
    std::memcpy(header.data(), member.name.data(),
                std::min<std::size_t>(member.name.size(), 100));
    writeOctal(header.data() + 100, 8, member.mode);
    writeOctal(header.data() + 108, 8, 0);
    writeOctal(header.data() + 116, 8, 0);
    writeOctal(header.data() + 124, 12, member.data.size());
    writeOctal(header.data() + 136, 12, 0);
    std::memset(header.data() + 148, ' ', 8);
    header[156] = static_cast<std::uint8_t>(member.type);
    if (!member.linkName.empty()) {
        std::memcpy(header.data() + 157, member.linkName.data(),
                    std::min<std::size_t>(member.linkName.size(), 100));
    }
    std::memcpy(header.data() + 257, magic.data(),
                std::min<std::size_t>(magic.size(), 8));
    std::uint64_t checksum = 0;
    for (const std::uint8_t byte : header) checksum += byte;
    writeOctal(header.data() + 148, 8, checksum);
    return header;
}

std::vector<std::uint8_t> tarOf(const std::vector<TarMember>& members,
                                const std::string& magic = std::string("ustar\0" "00", 8)) {
    std::vector<std::uint8_t> out;
    for (const TarMember& member : members) {
        const std::vector<std::uint8_t> header = tarHeader(member, magic);
        out.insert(out.end(), header.begin(), header.end());
        if (member.type == '0' || member.type == 0) {
            out.insert(out.end(), member.data.begin(), member.data.end());
            out.insert(out.end(), (512 - member.data.size() % 512) % 512, 0);
        }
    }
    out.insert(out.end(), 1024, 0);
    return out;
}

TarMember directory(const std::string& name) {
    TarMember member;
    member.name = name;
    member.type = '5';
    member.mode = 0755;
    return member;
}

TarMember file(const std::string& name, const std::string& text,
               std::uint32_t mode = 0644) {
    TarMember member;
    member.name = name;
    member.data.assign(text.begin(), text.end());
    member.mode = mode;
    return member;
}

const std::string kTop = "daybreak-1.0.0-linux-x86_64";
const std::string kLauncherText = "#!/bin/sh\nexit 0\n";

std::vector<TarMember> validTar() {
    return {
        directory(kTop + "/"),
        directory(kTop + "/lib/"),
        file(kTop + "/daybreak", kLauncherText, 0755),
        file(kTop + "/lib/libdaybreak.so", "library"),
    };
}

std::vector<std::uint8_t> bytesOf(const std::string& text) {
    return std::vector<std::uint8_t>(text.begin(), text.end());
}

struct ZipMember {
    std::string name;
    std::vector<std::uint8_t> data;
    std::uint16_t method = 8;
    std::uint16_t flags = 0;
    std::uint32_t external = 0100644u << 16;
    std::vector<std::uint8_t> extraCentral;
    std::vector<std::uint8_t> extraLocal;
    std::string localName;  // empty means the same as `name`
    bool wrongCrc = false;
    bool declareBomb = false;
    std::uint16_t diskStart = 0;
};

void appendLe(std::vector<std::uint8_t>* out, std::uint32_t value, int bytes) {
    for (int index = 0; index < bytes; ++index) {
        out->push_back(static_cast<std::uint8_t>(value >> (8 * index)));
    }
}

std::vector<std::uint8_t> zipOf(const std::vector<ZipMember>& members) {
    std::vector<std::uint8_t> local;
    std::vector<std::uint8_t> central;
    for (const ZipMember& member : members) {
        const std::vector<std::uint8_t> compressed =
            member.method == 8 ? storedDeflate(member.data) : member.data;
        const std::uint32_t crc = member.wrongCrc ? 0xDEADBEEFu : crc32Of(member.data);
        const std::uint32_t compressedSize = static_cast<std::uint32_t>(compressed.size());
        const std::uint32_t uncompressedSize =
            member.declareBomb ? 10u * 1024u * 1024u
                               : static_cast<std::uint32_t>(member.data.size());
        const std::string localName =
            member.localName.empty() ? member.name : member.localName;
        const std::uint32_t localOffset = static_cast<std::uint32_t>(local.size());

        appendLe(&local, 0x04034B50u, 4);           // signature
        appendLe(&local, 20, 2);                     // version needed
        appendLe(&local, member.flags, 2);
        appendLe(&local, member.method, 2);
        appendLe(&local, 0, 2);                      // time
        appendLe(&local, 0, 2);                      // date
        appendLe(&local, crc, 4);
        appendLe(&local, compressedSize, 4);
        appendLe(&local, uncompressedSize, 4);
        appendLe(&local, static_cast<std::uint32_t>(localName.size()), 2);
        appendLe(&local, static_cast<std::uint32_t>(member.extraLocal.size()), 2);
        local.insert(local.end(), localName.begin(), localName.end());
        local.insert(local.end(), member.extraLocal.begin(), member.extraLocal.end());
        local.insert(local.end(), compressed.begin(), compressed.end());

        appendLe(&central, 0x02014B50u, 4);          // signature
        appendLe(&central, 20, 2);                   // version made by
        appendLe(&central, 20, 2);                   // version needed
        appendLe(&central, member.flags, 2);
        appendLe(&central, member.method, 2);
        appendLe(&central, 0, 2);
        appendLe(&central, 0, 2);
        appendLe(&central, crc, 4);
        appendLe(&central, compressedSize, 4);
        appendLe(&central, uncompressedSize, 4);
        appendLe(&central, static_cast<std::uint32_t>(member.name.size()), 2);
        appendLe(&central, static_cast<std::uint32_t>(member.extraCentral.size()), 2);
        appendLe(&central, 0, 2);                    // comment
        appendLe(&central, member.diskStart, 2);
        appendLe(&central, 0, 2);                    // internal attributes
        appendLe(&central, member.external, 4);
        appendLe(&central, localOffset, 4);
        central.insert(central.end(), member.name.begin(), member.name.end());
        central.insert(central.end(), member.extraCentral.begin(),
                       member.extraCentral.end());
    }
    std::vector<std::uint8_t> out = local;
    const std::uint32_t centralOffset = static_cast<std::uint32_t>(out.size());
    out.insert(out.end(), central.begin(), central.end());
    appendLe(&out, 0x06054B50u, 4);                  // EOCD signature
    appendLe(&out, 0, 2);                            // disk
    appendLe(&out, 0, 2);                            // central disk
    appendLe(&out, static_cast<std::uint32_t>(members.size()), 2);
    appendLe(&out, static_cast<std::uint32_t>(members.size()), 2);
    appendLe(&out, static_cast<std::uint32_t>(central.size()), 4);
    appendLe(&out, centralOffset, 4);
    appendLe(&out, 0, 2);                            // comment length
    return out;
}

std::vector<ZipMember> validZip() {
    ZipMember manifest;
    manifest.name = "package-manifest.txt";
    manifest.data = bytesOf("format = 1\n");
    ZipMember executable;
    executable.name = "DaybreakRemake.exe";
    executable.data = bytesOf("MZ");
    ZipMember library;
    library.name = "SDL3.dll";
    library.data = bytesOf("dll");
    return {manifest, executable, library};
}

void testValidTarGz() {
    std::string error;
    std::unique_ptr<update::Archive> archive =
        update::Archive::openTarGz(gzipOf(tarOf(validTar())), &error);
    check(archive != nullptr, "a valid ustar.gz opens: " + error);
    if (archive == nullptr) return;
    expectEqual(archive->entries().size(), 3, "directories are entries, the root is not");
    const update::ArchiveEntry* launcher = archive->find("daybreak");
    check(launcher != nullptr && launcher->executable &&
              launcher->size == kLauncherText.size(),
          "the launcher entry carries its exec bit and size");
    std::string content;
    check(archive->extract("daybreak",
                           [&content](const std::uint8_t* data, std::size_t size) {
                               content.append(reinterpret_cast<const char*>(data), size);
                               return true;
                           },
                           &error),
          "extract streams a member: " + error);
    expect(content, kLauncherText, "extracted bytes match");
    check(!archive->extract("nope", [](const std::uint8_t*, std::size_t) { return true; },
                            &error),
          "extracting an absent entry fails");
}

void testValidZip() {
    std::string error;
    std::unique_ptr<update::Archive> archive =
        update::Archive::openZip(zipOf(validZip()), &error);
    check(archive != nullptr, "a valid zip opens: " + error);
    if (archive == nullptr) return;
    std::string content;
    check(archive->extract("DaybreakRemake.exe",
                           [&content](const std::uint8_t* data, std::size_t size) {
                               content.append(reinterpret_cast<const char*>(data), size);
                               return true;
                           },
                           &error),
          "extract inflates a deflate entry: " + error);
    expect(content, "MZ", "inflated bytes match");

    std::vector<ZipMember> stored = validZip();
    for (ZipMember& member : stored) member.method = 0;
    std::unique_ptr<update::Archive> storedArchive =
        update::Archive::openZip(zipOf(stored), &error);
    check(storedArchive != nullptr, "a stored zip opens: " + error);
    if (storedArchive != nullptr) {
        std::string text;
        check(storedArchive->extract("SDL3.dll",
                                     [&text](const std::uint8_t* data, std::size_t size) {
                                         text.append(reinterpret_cast<const char*>(data),
                                                     size);
                                         return true;
                                     },
                                     &error),
              "extract reads a stored entry");
        expect(text, "dll", "stored bytes match");
    }
}

void testTarRefusals() {
    std::string error;
    const auto refused = [&error](std::vector<std::uint8_t> archive,
                                  const std::string& what) {
        std::unique_ptr<update::Archive> opened =
            update::Archive::openTarGz(std::move(archive), &error);
        check(opened == nullptr, what + " is refused");
        check(!error.empty(), what + " explains itself");
    };

    refused(gzipOf(tarOf({file("rootfile", "x")})), "a file at the archive root");
    refused(gzipOf(tarOf({directory("a/"), directory("b/")})), "two top-level directories");
    refused(gzipOf(tarOf({file("../evil", "x")})), "a traversal path");
    refused(gzipOf(tarOf({file(kTop + "/CON", "x")})), "a Windows device name");
    refused(gzipOf(tarOf({file(kTop + "/A.txt", "x"), file(kTop + "/a.txt", "y")})),
            "a case collision");

    TarMember symlink;
    symlink.name = kTop + "/link";
    symlink.type = '2';
    symlink.linkName = "daybreak";
    refused(gzipOf(tarOf({symlink})), "a symlink member");

    TarMember hardlink;
    hardlink.name = kTop + "/link";
    hardlink.type = '1';
    hardlink.linkName = kTop + "/daybreak";
    refused(gzipOf(tarOf({hardlink})), "a hard link member");

    TarMember pax;
    pax.name = kTop + "/pax";
    pax.type = 'x';
    refused(gzipOf(tarOf({pax})), "a pax extended header");

    TarMember sparse;
    sparse.name = kTop + "/sparse";
    sparse.type = 'S';
    refused(gzipOf(tarOf({sparse})), "a sparse member");

    refused(gzipOf(tarOf({file(kTop + "/a", "x")},
                         std::string("ustar  \0", 8))),
            "a GNU-format archive");

    std::vector<std::uint8_t> corrupted = gzipOf(tarOf(validTar()));
    corrupted[corrupted.size() - 30] ^= 0xFF;  // inside the deflate payload
    refused(corrupted, "a corrupted deflate payload");

    std::vector<std::uint8_t> truncated = gzipOf(tarOf(validTar()));
    truncated.resize(truncated.size() - 8);
    refused(truncated, "a truncated gzip trailer");

    std::vector<std::uint8_t> trailing = gzipOf(tarOf(validTar()));
    trailing.push_back('j');
    refused(trailing, "data after the gzip member");
}

void testZipRefusals() {
    std::string error;
    const auto refused = [&error](std::vector<std::uint8_t> archive,
                                  const std::string& what) {
        std::unique_ptr<update::Archive> opened =
            update::Archive::openZip(std::move(archive), &error);
        check(opened == nullptr, what + " is refused");
        check(!error.empty(), what + " explains itself");
    };

    {
        std::vector<ZipMember> members = validZip();
        members[1].method = 12;  // bzip2
        refused(zipOf(members), "a bzip2 entry");
    }
    {
        std::vector<ZipMember> members = validZip();
        members[1].flags = 0x0001;
        refused(zipOf(members), "an encrypted entry");
    }
    {
        std::vector<ZipMember> members = validZip();
        members[1].extraCentral = {0x01, 0x00, 0x10, 0x00};  // zip64 field header
        members[1].extraCentral.resize(4 + 16, 0);
        refused(zipOf(members), "a zip64 extra field");
    }
    {
        std::vector<ZipMember> members = validZip();
        members[1].localName = "Other.exe";
        refused(zipOf(members), "a mismatched local header name");
    }
    {
        std::vector<ZipMember> members = validZip();
        members[1].external = 0120777u << 16;  // symlink
        refused(zipOf(members), "a symlink entry");
    }
    {
        std::vector<ZipMember> members = validZip();
        members[1].diskStart = 1;
        refused(zipOf(members), "an entry on another disk");
    }
    {
        std::vector<ZipMember> members = validZip();
        members[1].declareBomb = true;
        refused(zipOf(members), "a zip bomb ratio");
    }
    {
        std::vector<ZipMember> members = validZip();
        members[1].name = "CON";
        refused(zipOf(members), "a Windows device name");
    }
    {
        std::vector<std::uint8_t> truncated = zipOf(validZip());
        truncated.resize(truncated.size() / 2);
        refused(truncated, "a truncated zip");
    }
    {
        std::vector<ZipMember> members = validZip();
        members[1].wrongCrc = true;
        std::unique_ptr<update::Archive> opened =
            update::Archive::openZip(zipOf(members), &error);
        check(opened != nullptr, "a wrong CRC still opens (the index is intact)");
        if (opened != nullptr) {
            const bool extracted = opened->extract(
                "DaybreakRemake.exe",
                [](const std::uint8_t*, std::size_t) { return true; }, &error);
            check(!extracted, "extraction fails on a wrong CRC");
            check(error.find("CRC") != std::string::npos,
                  "the CRC failure says so: " + error);
        }
    }
}

}  // namespace

int runUpdateArchiveTests() {
    testValidTarGz();
    testValidZip();
    testTarRefusals();
    testZipRefusals();
    return update_test::report("update_archive_test");
}

#ifndef DAYBREAK_UPDATE_SELFTEST
int main() {
    return runUpdateArchiveTests();
}
#endif
