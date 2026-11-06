// psp/psp_pack.cpp — index lookup and gzip inflation for gzpack.pck.
#include "psp/psp_pack.h"

#include <array>
#include <cstring>
#include <stdexcept>

#include <zlib.h>

namespace psp {
namespace {

std::uint32_t rd32(const std::uint8_t* p) {
    return (std::uint32_t)p[0] | ((std::uint32_t)p[1] << 8) | ((std::uint32_t)p[2] << 16) |
           ((std::uint32_t)p[3] << 24);
}

// A packed index row per 16 bytes; the game's pack holds 10772 of them, so anything far
// larger is a file that is not this pack.
constexpr std::uint64_t kMaxEntries = 1u << 20;

const std::array<std::uint32_t, 256>& crcTable() {
    static const std::array<std::uint32_t, 256> table = [] {
        std::array<std::uint32_t, 256> t{};
        for (std::uint32_t i = 0; i < 256; ++i) {
            std::uint32_t c = i;
            for (int k = 0; k < 8; ++k) c = (c & 1) ? 0xEDB88320u ^ (c >> 1) : c >> 1;
            t[i] = c;
        }
        return t;
    }();
    return table;
}

}  // namespace

std::uint32_t packNameHash(const std::string& path) {
    // The pack's convention, measured against the disc: the CRC-32 register starts at zero,
    // runs with no pre-inversion, and is finalised with one XOR. That is exactly the value
    // Python's zlib.crc32(path, 0xFFFFFFFF) returns, which is how the pack's own tooling
    // builds the index; the path carries no leading slash.
    std::uint32_t crc = 0;
    const auto& table = crcTable();
    for (unsigned char c : path) crc = table[(crc ^ c) & 0xFF] ^ (crc >> 8);
    return crc ^ 0xFFFFFFFFu;
}

PspPack PspPack::open(const IsoImage& iso, const std::string& packPath) {
    PspPack pack;
    pack.iso_ = &iso;
    pack.path_ = packPath;
    std::uint64_t packBytes = 0;
    if (!iso.find(packPath, pack.packOffset_, packBytes))
        throw std::runtime_error(iso.path() + ": " + packPath + " is not in the image");

    std::vector<std::uint8_t> header;
    if (!iso.read(packPath, 0, 4, header) || header.size() != 4)
        throw std::runtime_error(packPath + ": cannot read the pack header");
    const std::uint64_t count = rd32(header.data());
    if (count == 0 || count > kMaxEntries)
        throw std::runtime_error(packPath + ": not a pack index (" + std::to_string(count) +
                                 " entries)");

    std::vector<std::uint8_t> index;
    if (!iso.read(packPath, 4, count * 16, index) || index.size() != count * 16)
        throw std::runtime_error(packPath + ": truncated pack index");
    pack.entries_.resize((size_t)count);
    pack.byHash_.reserve((size_t)count);
    for (std::size_t i = 0; i < (std::size_t)count; ++i) {
        const std::uint8_t* row = index.data() + i * 16;
        PspPackEntry& entry = pack.entries_[i];
        entry.hash = rd32(row);
        entry.packedBytes = rd32(row + 4);
        entry.offset = rd32(row + 8);
        entry.unknown = rd32(row + 12);
        pack.byHash_.emplace(entry.hash, i);
    }
    return pack;
}

const PspPackEntry* PspPack::find(const std::string& path) const {
    const auto found = byHash_.find(packNameHash(path));
    return found == byHash_.end() ? nullptr : &entries_[found->second];
}

bool PspPack::inflate(const PspPackEntry& entry, std::vector<std::uint8_t>& out,
                      std::string& error) const {
    std::vector<std::uint8_t> packed;
    if (!iso_->read(path_, entry.offset, entry.packedBytes, packed)) {
        error = "payload outside the pack";
        return false;
    }
    z_stream stream{};
    // 15 + 32: a real gzip header, which is what the pack stores, plus zlib's tolerance
    // for a bare zlib stream should some re-encode drop the gzip wrapper.
    if (inflateInit2(&stream, 15 + 32) != Z_OK) {
        error = "inflate initialization failed";
        return false;
    }
    out.clear();
    out.resize((size_t)entry.packedBytes * 4 + 4096);
    stream.next_in = packed.data();
    stream.avail_in = (uInt)packed.size();
    int status = Z_OK;
    for (;;) {
        stream.next_out = out.data() + stream.total_out;
        stream.avail_out = (uInt)(out.size() - stream.total_out);
        status = ::inflate(&stream, Z_FINISH);
        if (status == Z_STREAM_END) break;
        if (status != Z_OK && status != Z_BUF_ERROR) break;
        if (out.size() > (size_t)1 << 30) { status = Z_DATA_ERROR; break; }
        out.resize(out.size() * 2);
    }
    const std::size_t produced = (std::size_t)stream.total_out;
    inflateEnd(&stream);
    if (status != Z_STREAM_END) {
        out.clear();
        error = "gzip stream is corrupt or truncated";
        return false;
    }
    out.resize(produced);
    return true;
}

}  // namespace psp
