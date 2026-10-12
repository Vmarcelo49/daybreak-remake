#include "exe_strings.h"

#include <cstring>

#include "asset_source.h"
#include "cnv.h"   // xm::sjisToUtf8

namespace fnd::assets {
namespace {

// A PE32 image held in memory, with the section table needed to turn a cited .rdata virtual
// address into a file position. Every field is bounds-checked against the buffer, so a
// truncated or non-PE file reports a reason instead of reading past the end.
struct PeImage {
    std::vector<uint8_t> data;
    struct Section {
        uint32_t va = 0, virtualSize = 0, rawOffset = 0, rawSize = 0;
    };
    std::vector<Section> sections;
    // The image base the section VAs are relative to. Cited addresses (0x6b7308) are absolute,
    // because that is how the disassembly prints them, so every lookup subtracts this first.
    uint32_t imageBase = 0;

    bool load(const std::string& path, std::string& error) {
        if (!assetSource().read(path, data)) {
            error = "cannot open " + path;
            return false;
        }
        return parse(error);
    }

    bool parse(std::string& error) {
        auto u16 = [&](size_t at) { return (uint16_t)(data[at] | (data[at + 1] << 8)); };
        auto u32 = [&](size_t at) {
            return (uint32_t)(data[at] | (data[at + 1] << 8) | (data[at + 2] << 16) |
                              ((uint32_t)data[at + 3] << 24));
        };
        if (data.size() < 0x40 || data[0] != 'M' || data[1] != 'Z') {
            error = "not a DOS/PE image";
            return false;
        }
        const size_t pe = u32(0x3c);
        if (pe + 24 > data.size() || std::memcmp(&data[pe], "PE\0\0", 4) != 0) {
            error = "no PE signature";
            return false;
        }
        if (u16(pe + 24) != 0x10b) {   // PE32: the original is x86
            error = "not a PE32 image";
            return false;
        }
        imageBase = u32(pe + 24 + 28);   // PE32 optional header: ImageBase
        const uint16_t optionalSize = u16(pe + 20);
        const uint16_t sectionCount = u16(pe + 6);
        const size_t sectionTable = pe + 24 + optionalSize;
        if (sectionTable + (size_t)sectionCount * 40 > data.size()) {
            error = "section table outside the file";
            return false;
        }
        for (uint16_t i = 0; i < sectionCount; ++i) {
            const size_t at = sectionTable + (size_t)i * 40;
            Section s;
            s.virtualSize = u32(at + 8);
            s.va = u32(at + 12);
            s.rawSize = u32(at + 16);
            s.rawOffset = u32(at + 20);
            sections.push_back(s);
        }
        return true;
    }

    // Virtual address -> file offset, or false when it is in no section (or only in a
    // section's uninitialised tail, which has no bytes in the file).
    bool offsetOf(uint32_t va, uint64_t& offset, std::string& error) const {
        if (va < imageBase) {
            error = "address is below the image base";
            return false;
        }
        va -= imageBase;
        for (const Section& s : sections) {
            const uint32_t size = s.virtualSize > s.rawSize ? s.virtualSize : s.rawSize;
            if (va < s.va || va >= s.va + size) continue;
            const uint64_t inSection = va - s.va;
            if (inSection + 4 > s.rawSize) {
                error = "address is in a section's uninitialised tail";
                return false;
            }
            offset = s.rawOffset + inSection;
            return true;
        }
        error = "address is in no section";
        return false;
    }
};

}  // namespace

bool readExeBytes(const std::string& exePath, uint32_t va, size_t count,
                  std::vector<uint8_t>& out, std::string& error) {
    out.clear();
    PeImage image;
    if (!image.load(exePath, error)) return false;
    uint64_t offset = 0;
    if (!image.offsetOf(va, offset, error)) return false;
    if (offset + count > image.data.size()) {
        error = "range runs past the end of the file";
        return false;
    }
    out.assign(image.data.begin() + (ptrdiff_t)offset,
               image.data.begin() + (ptrdiff_t)(offset + count));
    return true;
}

bool peVaToFileOffset(const std::string& exePath, uint32_t va, uint64_t& offset,
                      std::string& error) {
    PeImage image;
    if (!image.load(exePath, error)) return false;
    return image.offsetOf(va, offset, error);
}

bool readExeStringTable(const std::string& exePath, uint32_t tableVa,
                        std::vector<std::string>& out, std::string& error, int limit) {
    out.clear();
    PeImage image;
    if (!image.load(exePath, error)) return false;
    uint64_t tableOffset = 0;
    if (!image.offsetOf(tableVa, tableOffset, error)) return false;
    auto u32At = [&](uint64_t at, uint32_t& value) {
        if (at + 4 > image.data.size()) return false;
        value = (uint32_t)(image.data[at] | (image.data[at + 1] << 8) |
                           (image.data[at + 2] << 16) | ((uint32_t)image.data[at + 3] << 24));
        return true;
    };
    for (int i = 0; i < limit; ++i) {
        uint32_t stringVa = 0;
        if (!u32At(tableOffset + (uint64_t)i * 4, stringVa)) {
            error = "pointer table runs past the end of the file";
            return false;
        }
        if (stringVa == 0) return true;   // the table's own terminator
        uint64_t stringOffset = 0;
        if (!image.offsetOf(stringVa, stringOffset, error)) return false;
        if (stringOffset >= image.data.size()) {
            error = "string address past the end of the file";
            return false;
        }
        size_t end = (size_t)stringOffset;
        while (end < image.data.size() && image.data[end] != 0) ++end;
        if (end >= image.data.size()) {
            error = "string is not NUL-terminated";
            return false;
        }
        out.push_back(xm::sjisToUtf8(std::string((const char*)&image.data[stringOffset],
                                                 end - (size_t)stringOffset)));
    }
    error = "table is longer than the read limit";
    return false;
}

}  // namespace fnd::assets
