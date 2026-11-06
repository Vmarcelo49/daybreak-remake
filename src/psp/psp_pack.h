#pragma once
// psp/psp_pack.h — the PSP build's one archive, gzpack.pck, read through an ISO.
//
// Layout (measured on Higurashi Daybreak Portable Mega Edition, see docs/psp/README.md):
//   u32 count, then count x { u32 nameHash, u32 packedBytes, u32 offset, u32 unknown },
//   the rows sorted by nameHash, then the gzip payloads at `offset` from the pack start.
// A file's nameHash is zlib's crc32 of its path seeded with 0xFFFFFFFF and *without* the
// final inversion, i.e. the value Python's zlib.crc32(path, 0xFFFFFFFF) returns; the path
// carries no leading slash. Knowing the path is therefore enough to find a file, and the
// pack carries no readable name table at all.
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "psp/iso9660.h"

namespace psp {

struct PspPackEntry {
    std::uint32_t hash = 0;
    std::uint32_t packedBytes = 0;
    std::uint32_t offset = 0;   // from the first byte of the pack
    std::uint32_t unknown = 0;
};

// The pack's name hash: CRC-32 started at zero and finalised with one XOR, i.e. the
// value zlib.crc32(path, 0xFFFFFFFF) returns. Kept as its own function so the reader and
// any test agree by construction.
std::uint32_t packNameHash(const std::string& path);

class PspPack {
public:
    // Throws std::runtime_error when the pack is absent, truncated or not a pack index.
    static PspPack open(const IsoImage& iso, const std::string& packPath);

    const PspPackEntry* find(const std::string& path) const;

    // Inflates one entry into `out`. Returns false and fills `error` on a broken stream or
    // a payload that inflates to something other than the index's size.
    bool inflate(const PspPackEntry& entry, std::vector<std::uint8_t>& out,
                 std::string& error) const;

    std::size_t size() const { return entries_.size(); }
    const std::string& path() const { return path_; }

private:
    const IsoImage*                          iso_ = nullptr;
    std::string                              path_;
    std::uint64_t                            packOffset_ = 0;
    std::vector<PspPackEntry>                entries_;
    std::unordered_map<std::uint32_t, std::size_t> byHash_;
};

}  // namespace psp
