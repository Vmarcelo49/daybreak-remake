#pragma once
// update/archive.h — the two archive shapes a release ships, read exactly as
// tools/make_update_manifest.py accepts them (docs/AUTO-UPDATE.md).
//
// Linux is a single-member gzip of a POSIX ustar archive; Windows is a flat zip with
// methods 0 and 8, no encryption and no zip64. Anything else is refused with a specific
// error, because a release the tool accepted but this cannot read would be an update
// nobody can apply. Extraction goes to a caller's sink; writing files is step 3's job.
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace update {

struct ArchiveEntry {
    std::string path;
    bool isDirectory = false;
    bool executable = false;  // ustar mode's exec bit; always false in a zip
    std::uint64_t size = 0;
};

using ArchiveSink = std::function<bool(const std::uint8_t*, std::size_t)>;

class Archive {
public:
    // `bytes` is the archive file as downloaded; the reader keeps what it needs.
    static std::unique_ptr<Archive> openTarGz(std::vector<std::uint8_t> bytes,
                                              std::string* error);
    static std::unique_ptr<Archive> openZip(std::vector<std::uint8_t> bytes,
                                            std::string* error);

    const std::vector<ArchiveEntry>& entries() const { return entries_; }
    const ArchiveEntry* find(const std::string& path) const;

    // Streams one regular file to `sink`; false + `error` on a CRC or size mismatch.
    bool extract(const std::string& path, const ArchiveSink& sink,
                 std::string* error) const;

private:
    enum class Kind { TarGz, Zip };

    struct Stored {
        std::size_t dataOffset = 0;
        std::size_t compressedSize = 0;
        std::size_t uncompressedSize = 0;
        std::uint32_t crc32 = 0;
        std::uint16_t method = 0;
        bool isDirectory = false;
    };

    Kind kind_ = Kind::TarGz;
    std::vector<std::uint8_t> bytes_;  // decompressed tar, or the zip file itself
    std::vector<ArchiveEntry> entries_;
    std::vector<Stored> stored_;
};

}  // namespace update
