// psp/iso9660.cpp — the ISO9660 subset the PSP pack lives in.
#include "psp/iso9660.h"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <stdexcept>

namespace psp {
namespace {

constexpr std::uint64_t kSector = 2048;
constexpr std::uint64_t kVolumeDescriptors = 16;
// A malformed image must not make us walk a directory forever: the game's ISO has three
// levels and both of its directories are far under this.
constexpr std::uint64_t kMaxDirectoryBytes = 64u << 20;

std::uint32_t le32(const std::uint8_t* p) {
    return (std::uint32_t)p[0] | ((std::uint32_t)p[1] << 8) | ((std::uint32_t)p[2] << 16) |
           ((std::uint32_t)p[3] << 24);
}

// ISO9660 stores names uppercase with a ";1" version suffix. Folding once here keeps the
// caller's all-lowercase pack paths working, which is how the paths are written everywhere
// else in this tree (the pack index hashes the lowercase spelling).
std::string normalise(std::string name) {
    const size_t semicolon = name.find(';');
    if (semicolon != std::string::npos) name.resize(semicolon);
    for (char& c : name) c = (char)std::toupper((unsigned char)c);
    return name;
}

}  // namespace

IsoImage IsoImage::open(const std::string& path) {
    IsoImage image;
    image.path_ = path;
    image.file_.open(path, std::ios::binary);
    if (!image.file_) throw std::runtime_error("cannot open " + path);

    std::vector<std::uint8_t> descriptor;
    if (!image.seekRead(kVolumeDescriptors * kSector, kSector, descriptor))
        throw std::runtime_error(path + ": too small to hold an ISO9660 volume descriptor");
    if (std::memcmp(descriptor.data() + 1, "CD001", 5) != 0)
        throw std::runtime_error(path + ": not an ISO9660 image (no CD001 signature)");
    if (descriptor[0] != 1)
        throw std::runtime_error(path + ": no ISO9660 primary volume descriptor");

    // The root directory record is an in-line directory record at offset 156.
    const std::uint8_t* record = descriptor.data() + 156;
    if (record[0] < 34) throw std::runtime_error(path + ": primary volume descriptor has no root");
    image.root_.offset = (std::uint64_t)le32(record + 2) * kSector;
    image.root_.size = le32(record + 10);
    image.root_.directory = true;
    return image;
}

bool IsoImage::seekRead(std::uint64_t offset, std::uint64_t size,
                        std::vector<std::uint8_t>& out) const {
    if (offset > (std::uint64_t)-1 - size) return false;
    out.assign((size_t)size, 0);
    file_.clear();
    file_.seekg((std::streamoff)offset, std::ios::beg);
    if (!file_) return false;
    file_.read(reinterpret_cast<char*>(out.data()), (std::streamsize)size);
    return (std::uint64_t)file_.gcount() == size;
}

bool IsoImage::children(const Record& directory,
                        std::vector<std::pair<std::string, Record>>& out) const {
    out.clear();
    if (!directory.directory || directory.size > kMaxDirectoryBytes) return false;
    std::vector<std::uint8_t> bytes;
    if (!seekRead(directory.offset, directory.size, bytes)) return false;
    size_t at = 0;
    while (at < bytes.size()) {
        const std::uint8_t length = bytes[at];
        if (length == 0) {
            // A zero length marks the rest of this sector as padding; the next record
            // starts at the next sector boundary.
            const size_t next = (at / kSector + 1) * kSector;
            if (next <= at) return false;
            at = next;
            continue;
        }
        if (at + length > bytes.size() || length < 34) return false;
        const std::uint8_t* record = bytes.data() + at;
        const std::uint8_t nameLength = record[32];
        if (33 + (size_t)nameLength > length) return false;
        std::string name(reinterpret_cast<const char*>(record + 33), nameLength);
        // 0x00 and 0x01 are the "." and ".." entries.
        if (!(nameLength == 1 && (record[33] == 0 || record[33] == 1))) {
            Record entry;
            entry.offset = (std::uint64_t)le32(record + 2) * kSector;
            entry.size = le32(record + 10);
            entry.directory = (record[25] & 0x02) != 0;
            out.emplace_back(normalise(name), entry);
        }
        at += length;
    }
    return true;
}

bool IsoImage::lookup(const std::string& path, Record& out) const {
    std::string rest;
    for (char c : path) {
        if (c == '\\') rest += '/';
        else rest += c;
    }
    while (!rest.empty() && rest.front() == '/') rest.erase(rest.begin());
    while (!rest.empty() && rest.back() == '/') rest.pop_back();
    if (rest.empty()) return false;

    Record current = root_;
    std::vector<std::pair<std::string, Record>> entries;
    size_t at = 0;
    while (at <= rest.size()) {
        const size_t slash = rest.find('/', at);
        const std::string component = normalise(rest.substr(at, slash - at));
        if (component.empty()) return false;
        if (!children(current, entries)) return false;
        bool found = false;
        for (const auto& entry : entries)
            if (entry.first == component) {
                current = entry.second;
                found = true;
                break;
            }
        if (!found) return false;
        if (slash == std::string::npos) break;
        at = slash + 1;
    }
    out = current;
    return true;
}

bool IsoImage::find(const std::string& path, std::uint64_t& offset, std::uint64_t& size) const {
    Record record;
    if (!lookup(path, record) || record.directory) return false;
    offset = record.offset;
    size = record.size;
    return true;
}

bool IsoImage::read(const std::string& path, std::uint64_t offset, std::uint64_t size,
                    std::vector<std::uint8_t>& out) const {
    std::uint64_t base = 0, length = 0;
    if (!find(path, base, length)) return false;
    if (offset > length || size > length - offset) return false;
    return seekRead(base + offset, size, out);
}

}  // namespace psp
