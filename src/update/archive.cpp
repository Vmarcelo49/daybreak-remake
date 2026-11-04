#include "update/archive.h"

#include <algorithm>
#include <cstring>

#include "update/paths.h"
#include "zlib.h"

namespace update {
namespace {

constexpr std::size_t kBlock = 512;
constexpr std::size_t kMaxEntries = 10000;
constexpr std::uint64_t kMaxTotalUncompressed = 1024ull * 1024 * 1024;
constexpr std::uint64_t kMaxRatio = 200;
constexpr std::size_t kGzipLimit = 2ull * 1024 * 1024 * 1024;

bool fail(std::string* error, const std::string& message) {
    if (error != nullptr) *error = message;
    return false;
}

std::uint16_t readLe16(const std::uint8_t* data) {
    return static_cast<std::uint16_t>(data[0] | (data[1] << 8));
}

std::uint32_t readLe32(const std::uint8_t* data) {
    return static_cast<std::uint32_t>(data[0]) |
           (static_cast<std::uint32_t>(data[1]) << 8) |
           (static_cast<std::uint32_t>(data[2]) << 16) |
           (static_cast<std::uint32_t>(data[3]) << 24);
}

bool allZeroFrom(const std::vector<std::uint8_t>& data, std::size_t from) {
    for (std::size_t index = from; index < data.size(); ++index) {
        if (data[index] != 0) return false;
    }
    return true;
}

std::string cString(const std::uint8_t* field, std::size_t size) {
    std::size_t length = 0;
    while (length < size && field[length] != 0) ++length;
    return std::string(reinterpret_cast<const char*>(field), length);
}

// Octal fields only: POSIX ustar has no base-256 encoding, and GNU/pax are refused before
// this is reached.
bool parseOctal(const std::uint8_t* field, std::size_t size, const char* what,
                std::uint64_t* out, std::string* error) {
    std::size_t end = size;
    while (end > 0 && (field[end - 1] == 0 || field[end - 1] == ' ')) --end;
    std::size_t begin = 0;
    while (begin < end && field[begin] == ' ') ++begin;
    if (begin == end) {
        *out = 0;
        return true;
    }
    if ((field[begin] & 0x80) != 0) {
        return fail(error, std::string(what) + " uses base-256 encoding, not POSIX ustar");
    }
    std::uint64_t value = 0;
    for (std::size_t index = begin; index < end; ++index) {
        if (field[index] < '0' || field[index] > '7') {
            return fail(error, std::string(what) + " is not an octal number");
        }
        value = value * 8 + static_cast<std::uint64_t>(field[index] - '0');
    }
    *out = value;
    return true;
}

struct ParsedEntry {
    std::string path;
    bool isDirectory = false;
    bool executable = false;
    std::uint64_t size = 0;
    std::size_t dataOffset = 0;
    std::size_t compressedSize = 0;
    std::uint32_t crc32 = 0;
    std::uint16_t method = 0;
};

// --- gzip -------------------------------------------------------------------------

bool gunzip(const std::vector<std::uint8_t>& input, std::vector<std::uint8_t>* out,
            std::string* error) {
    if (input.size() < 18 || input[0] != 0x1F || input[1] != 0x8B) {
        return fail(error, "gzip: not a gzip file");
    }
    if (input[2] != 8) return fail(error, "gzip: the compression method is not deflate");

    z_stream stream{};
    if (inflateInit2(&stream, 15 + 16) != Z_OK) {
        return fail(error, "gzip: zlib could not start");
    }
    std::vector<std::uint8_t> buffer(1 << 16);
    std::size_t offset = 0;
    bool finished = false;
    while (!finished) {
        if (stream.avail_in == 0 && offset < input.size()) {
            const std::size_t take =
                std::min<std::size_t>(input.size() - offset, 1u << 30);
            stream.next_in = const_cast<Bytef*>(input.data() + offset);
            stream.avail_in = static_cast<uInt>(take);
            offset += take;
        }
        stream.next_out = buffer.data();
        stream.avail_out = static_cast<uInt>(buffer.size());
        const int status = inflate(&stream, Z_NO_FLUSH);
        if (status == Z_STREAM_END) {
            finished = true;
        } else if (status != Z_OK) {
            const std::string message =
                stream.msg != nullptr ? stream.msg : zError(status);
            inflateEnd(&stream);
            return fail(error, "gzip: " + message);
        } else if (stream.avail_in == 0 && offset >= input.size() &&
                   stream.avail_out == buffer.size()) {
            inflateEnd(&stream);
            return fail(error, "gzip: truncated stream");
        }
        const std::size_t produced = buffer.size() - stream.avail_out;
        if (produced > 0) {
            if (out->size() + produced > kGzipLimit) {
                inflateEnd(&stream);
                return fail(error, "gzip: decompressed data is too large");
            }
            out->insert(out->end(), buffer.begin(), buffer.begin() + produced);
        }
    }
    const bool trailing = stream.avail_in > 0 || offset < input.size();
    inflateEnd(&stream);
    if (trailing) {
        return fail(error, "gzip: data after the member (exactly one member is allowed)");
    }
    return true;
}

// --- ustar ------------------------------------------------------------------------

bool parseTar(const std::vector<std::uint8_t>& raw, std::vector<ParsedEntry>* parsed,
              std::string* error) {
    if (raw.size() % kBlock != 0) {
        return fail(error, "tar: data is not a multiple of 512 bytes");
    }
    std::size_t offset = 0;
    bool ended = false;
    while (offset < raw.size()) {
        const std::uint8_t* header = raw.data() + offset;
        bool zero = true;
        for (std::size_t index = 0; index < kBlock; ++index) {
            if (header[index] != 0) {
                zero = false;
                break;
            }
        }
        if (zero) {
            if (!allZeroFrom(raw, offset)) {
                return fail(error, "tar: data after the end-of-archive blocks");
            }
            ended = true;
            break;
        }
        std::uint64_t storedChecksum = 0;
        if (!parseOctal(header + 148, 8, "the header checksum", &storedChecksum, error)) {
            return false;
        }
        std::uint64_t actualChecksum = 0;
        for (std::size_t index = 0; index < kBlock; ++index) {
            const bool inChecksum = index >= 148 && index < 156;
            actualChecksum += inChecksum ? 0x20 : header[index];
        }
        if (storedChecksum != actualChecksum) {
            return fail(error, "tar: header checksum mismatch");
        }
        if (std::memcmp(header + 257, "ustar", 5) != 0 || header[262] != 0 ||
            header[263] != '0' || header[264] != '0') {
            return fail(error,
                        "tar: not a POSIX ustar archive; GNU and pax extensions are not "
                        "supported");
        }
        const std::uint8_t type = header[156];
        const std::string name = cString(header, 100);
        const std::string prefix = cString(header + 345, 155);
        if (name.empty()) return fail(error, "tar: a member has an empty name");
        const std::string full = prefix.empty() ? name : prefix + "/" + name;

        std::uint64_t size = 0;
        if (!parseOctal(header + 124, 12, "a member size", &size, error)) return false;
        std::uint64_t mode = 0;
        if (!parseOctal(header + 100, 8, "a member mode", &mode, error)) return false;

        if (type == '1') {
            return fail(error, "tar: " + full +
                                   " is a hard link; only regular files and directories "
                                   "are supported");
        }
        if (type == '2') {
            return fail(error, "tar: " + full +
                                   " is a symlink; only regular files and directories "
                                   "are supported");
        }
        if (type == '5') {
            if (size != 0) return fail(error, "tar: directory " + full + " has a size");
            ParsedEntry entry;
            entry.path = full;
            while (!entry.path.empty() && entry.path.back() == '/') entry.path.pop_back();
            entry.isDirectory = true;
            parsed->push_back(entry);
            offset += kBlock;
            continue;
        }
        if (type != '0' && type != 0) {
            return fail(error, "tar: " + full +
                                   " has a member type other than a regular file (0) or "
                                   "directory (5)");
        }
        if (!full.empty() && full.back() == '/') {
            return fail(error, "tar: file " + full + " has a trailing slash");
        }
        if (offset + kBlock + size > raw.size()) {
            return fail(error, "tar: " + full + " is truncated");
        }
        ParsedEntry entry;
        entry.path = full;
        entry.size = size;
        entry.executable = (mode & 0111) != 0;
        entry.dataOffset = offset + kBlock;
        parsed->push_back(entry);
        offset += kBlock + ((static_cast<std::size_t>(size) + kBlock - 1) / kBlock) * kBlock;
    }
    if (!ended) return fail(error, "tar: no end-of-archive blocks");
    return true;
}

// --- zip --------------------------------------------------------------------------

bool hasZip64Extra(const std::uint8_t* extra, std::size_t size) {
    std::size_t position = 0;
    while (position + 4 <= size) {
        const std::uint16_t tag = readLe16(extra + position);
        const std::uint16_t length = readLe16(extra + position + 2);
        if (tag == 0x0001) return true;
        position += 4 + length;
    }
    return false;
}

bool asciiOnly(const std::string& text) {
    for (const char character : text) {
        if (static_cast<unsigned char>(character) >= 0x80) return false;
    }
    return true;
}

bool parseZip(const std::vector<std::uint8_t>& data, std::vector<ParsedEntry>* parsed,
              std::string* error) {
    if (data.size() < 22) return fail(error, "zip: too small to be a zip");
    const std::size_t searchFrom =
        data.size() > 65535 + 22 ? data.size() - (65535 + 22) : 0;
    std::size_t eocd = std::string::npos;
    for (std::size_t index = data.size() - 22 + 1; index > searchFrom;) {
        --index;
        if (data[index] == 'P' && data[index + 1] == 'K' && data[index + 2] == 5 &&
            data[index + 3] == 6) {
            eocd = index;
            break;
        }
    }
    if (eocd == std::string::npos) {
        return fail(error, "zip: no end-of-central-directory record");
    }
    const std::uint16_t disk = readLe16(data.data() + eocd + 4);
    const std::uint16_t centralDisk = readLe16(data.data() + eocd + 6);
    const std::uint16_t entriesOnDisk = readLe16(data.data() + eocd + 8);
    const std::uint16_t entriesTotal = readLe16(data.data() + eocd + 10);
    const std::uint32_t centralSize = readLe32(data.data() + eocd + 12);
    const std::uint32_t centralOffset = readLe32(data.data() + eocd + 16);
    const std::uint16_t commentLength = readLe16(data.data() + eocd + 20);
    if (eocd + 22 + commentLength != data.size()) {
        return fail(error, "zip: the archive comment runs past the end of the file");
    }
    if (disk != 0 || centralDisk != 0 || entriesOnDisk != entriesTotal) {
        return fail(error, "zip: multi-disk archives are not supported");
    }
    if (entriesTotal == 0xFFFF || centralSize == 0xFFFFFFFF ||
        centralOffset == 0xFFFFFFFF) {
        return fail(error, "zip: zip64 archives are not supported");
    }
    if (entriesTotal > kMaxEntries) {
        return fail(error, "zip: too many entries");
    }

    std::uint64_t totalUncompressed = 0;
    std::size_t position = centralOffset;
    for (std::uint16_t index = 0; index < entriesTotal; ++index) {
        if (position + 46 > data.size()) {
            return fail(error, "zip: truncated central directory");
        }
        const std::uint8_t* central = data.data() + position;
        if (std::memcmp(central, "PK\x01\x02", 4) != 0) {
            return fail(error, "zip: bad central directory signature");
        }
        const std::uint16_t flags = readLe16(central + 8);
        const std::uint16_t method = readLe16(central + 10);
        const std::uint32_t crc = readLe32(central + 16);
        const std::uint32_t compressedSize = readLe32(central + 20);
        const std::uint32_t uncompressedSize = readLe32(central + 24);
        const std::uint16_t nameLength = readLe16(central + 28);
        const std::uint16_t extraLength = readLe16(central + 30);
        const std::uint16_t entryComment = readLe16(central + 32);
        const std::uint16_t diskStart = readLe16(central + 34);
        const std::uint32_t external = readLe32(central + 38);
        const std::uint32_t localOffset = readLe32(central + 42);
        const std::size_t nameStart = position + 46;
        const std::size_t extraStart = nameStart + nameLength;
        const std::size_t next = extraStart + extraLength + entryComment;
        if (next > data.size()) {
            return fail(error, "zip: truncated central directory entry");
        }
        const std::string rawName(reinterpret_cast<const char*>(data.data() + nameStart),
                                  nameLength);
        if (flags & 0x0001) {
            return fail(error, "zip: '" + rawName +
                                   "' is encrypted; encrypted entries are not supported");
        }
        if ((flags & 0x0800) == 0 && !asciiOnly(rawName)) {
            return fail(error, "zip: '" + rawName +
                                   "' is not ASCII and the entry does not set the UTF-8 "
                                   "flag");
        }
        if (method != 0 && method != 8) {
            return fail(error, "zip: '" + rawName + "' uses compression method " +
                                   std::to_string(method) +
                                   "; only 0 (stored) and 8 (deflate) are supported");
        }
        if (hasZip64Extra(data.data() + extraStart, extraLength)) {
            return fail(error, "zip: '" + rawName +
                                   "' has a zip64 extra field; zip64 is not supported");
        }
        if (diskStart != 0) {
            return fail(error, "zip: '" + rawName + "' starts on another disk");
        }
        if (((external >> 16) & 0170000) == 0120000) {
            return fail(error, "zip: '" + rawName +
                                   "' is a symlink; only regular files and directories "
                                   "are supported");
        }
        if (localOffset + 30 > data.size() ||
            std::memcmp(data.data() + localOffset, "PK\x03\x04", 4) != 0) {
            return fail(error, "zip: '" + rawName + "' has no local header");
        }
        const std::uint8_t* local = data.data() + localOffset;
        const std::uint16_t localFlags = readLe16(local + 6);
        const std::uint16_t localMethod = readLe16(local + 8);
        const std::uint16_t localNameLength = readLe16(local + 26);
        const std::uint16_t localExtraLength = readLe16(local + 28);
        const std::size_t localNameStart = localOffset + 30;
        const std::size_t localExtraStart = localNameStart + localNameLength;
        const std::size_t dataStart = localExtraStart + localExtraLength;
        if (dataStart > data.size()) {
            return fail(error, "zip: '" + rawName + "' has a truncated local header");
        }
        const std::string localName(
            reinterpret_cast<const char*>(data.data() + localNameStart),
            localNameLength);
        if (localName != rawName) {
            return fail(error, "zip: '" + rawName +
                                   "' has a different name in its local header");
        }
        if (hasZip64Extra(data.data() + localExtraStart, localExtraLength)) {
            return fail(error, "zip: '" + rawName +
                                   "' has a zip64 local extra field; zip64 is not "
                                   "supported");
        }
        if (localMethod != method || (localFlags & 0x0001) != 0) {
            return fail(error, "zip: '" + rawName + "' has an inconsistent local header");
        }
        if (dataStart + compressedSize > data.size()) {
            return fail(error, "zip: '" + rawName + "' is truncated");
        }

        std::string name = rawName;
        if (name.compare(0, 2, "./") == 0) name = name.substr(2);
        const bool isDirectory = !name.empty() && name.back() == '/';
        if (isDirectory) name.pop_back();
        if (name.empty()) return fail(error, "zip: a member has an empty name");
        if (method == 0 && compressedSize != uncompressedSize) {
            return fail(error, "zip: stored entry '" + name + "' has mismatched sizes");
        }
        if (method == 8 && (compressedSize == 0 || uncompressedSize > kMaxRatio * compressedSize)) {
            return fail(error, "zip: '" + name + "' inflates beyond 200:1 (a zip bomb?)");
        }
        if (!isDirectory) {
            totalUncompressed += uncompressedSize;
            if (totalUncompressed > kMaxTotalUncompressed) {
                return fail(error, "zip: uncompressed data is too large");
            }
        }

        ParsedEntry entry;
        entry.path = name;
        entry.isDirectory = isDirectory;
        entry.size = uncompressedSize;
        entry.dataOffset = dataStart;
        entry.compressedSize = compressedSize;
        entry.crc32 = crc;
        entry.method = method;
        parsed->push_back(entry);
        position = next;
    }
    if (position != static_cast<std::size_t>(centralOffset) + centralSize) {
        return fail(error, "zip: central directory size does not match the end record");
    }
    return true;
}

bool validatePaths(std::vector<ParsedEntry>* parsed, std::string* error) {
    std::vector<std::string> files;
    for (ParsedEntry& entry : *parsed) {
        std::string pathError;
        if (!paths::validRelative(entry.path, &pathError)) {
            return fail(error, pathError);
        }
        if (!entry.isDirectory) files.push_back(entry.path);
    }
    std::string setError;
    if (!paths::validSet(files, &setError)) return fail(error, setError);
    return true;
}

}  // namespace

std::unique_ptr<Archive> Archive::openTarGz(std::vector<std::uint8_t> bytes,
                                            std::string* error) {
    std::vector<std::uint8_t> tar;
    if (!gunzip(bytes, &tar, error)) return nullptr;
    std::vector<ParsedEntry> parsed;
    if (!parseTar(tar, &parsed, error)) return nullptr;

    // Exactly one top-level directory, and it is the package root: the manifest paths are
    // relative to it (docs/AUTO-UPDATE.md).
    std::vector<ParsedEntry> relative;
    std::string top;
    for (ParsedEntry& entry : parsed) {
        std::string name = entry.path;
        if (name.compare(0, 2, "./") == 0) name = name.substr(2);
        if (name.empty()) {
            fail(error, "tar: a member has an empty name");
            return nullptr;
        }
        // The full member name is checked before the top-level directory is stripped, or
        // "../evil" would lose the ".." with the prefix and look like a plain "evil".
        std::string pathError;
        if (!paths::validRelative(name, &pathError)) {
            fail(error, pathError);
            return nullptr;
        }
        const std::size_t slash = name.find('/');
        const std::string component =
            slash == std::string::npos ? name : name.substr(0, slash);
        if (top.empty()) {
            top = component;
        } else if (component != top) {
            fail(error, "tar: expected one top-level directory");
            return nullptr;
        }
        if (slash == std::string::npos) {
            if (!entry.isDirectory) {
                fail(error, "tar: the top-level entry is not a directory");
                return nullptr;
            }
            continue;  // the package root itself is not an entry
        }
        entry.path = name.substr(slash + 1);
        if (entry.path.empty()) {
            fail(error, "tar: empty member name");
            return nullptr;
        }
        relative.push_back(entry);
    }
    if (top.empty()) {
        fail(error, "tar: the archive is empty");
        return nullptr;
    }
    if (!validatePaths(&relative, error)) return nullptr;

    auto archive = std::unique_ptr<Archive>(new Archive());
    archive->kind_ = Kind::TarGz;
    archive->bytes_ = std::move(tar);
    for (const ParsedEntry& entry : relative) {
        ArchiveEntry visible;
        visible.path = entry.path;
        visible.isDirectory = entry.isDirectory;
        visible.executable = entry.executable;
        visible.size = entry.size;
        archive->entries_.push_back(visible);
        Stored stored;
        stored.dataOffset = entry.dataOffset;
        stored.compressedSize = entry.compressedSize;
        stored.uncompressedSize = static_cast<std::size_t>(entry.size);
        stored.crc32 = entry.crc32;
        stored.method = entry.method;
        stored.isDirectory = entry.isDirectory;
        archive->stored_.push_back(stored);
    }
    return archive;
}

std::unique_ptr<Archive> Archive::openZip(std::vector<std::uint8_t> bytes,
                                          std::string* error) {
    std::vector<ParsedEntry> parsed;
    if (!parseZip(bytes, &parsed, error)) return nullptr;
    if (!validatePaths(&parsed, error)) return nullptr;

    auto archive = std::unique_ptr<Archive>(new Archive());
    archive->kind_ = Kind::Zip;
    archive->bytes_ = std::move(bytes);
    for (const ParsedEntry& entry : parsed) {
        ArchiveEntry visible;
        visible.path = entry.path;
        visible.isDirectory = entry.isDirectory;
        visible.size = entry.size;
        archive->entries_.push_back(visible);
        Stored stored;
        stored.dataOffset = entry.dataOffset;
        stored.compressedSize = entry.compressedSize;
        stored.uncompressedSize = static_cast<std::size_t>(entry.size);
        stored.crc32 = entry.crc32;
        stored.method = entry.method;
        stored.isDirectory = entry.isDirectory;
        archive->stored_.push_back(stored);
    }
    return archive;
}

const ArchiveEntry* Archive::find(const std::string& path) const {
    for (const ArchiveEntry& entry : entries_) {
        if (entry.path == path) return &entry;
    }
    return nullptr;
}

bool Archive::extract(const std::string& path, const ArchiveSink& sink,
                      std::string* error) const {
    std::size_t index = 0;
    for (; index < entries_.size(); ++index) {
        if (entries_[index].path == path) break;
    }
    if (index == entries_.size()) return fail(error, "no such entry: " + path);
    const Stored& stored = stored_[index];
    if (stored.isDirectory) return fail(error, path + " is a directory");

    if (kind_ == Kind::TarGz) {
        const std::size_t end = stored.dataOffset + stored.uncompressedSize;
        if (end > bytes_.size()) return fail(error, path + " is truncated");
        if (!sink(bytes_.data() + stored.dataOffset, stored.uncompressedSize)) {
            return fail(error, path + ": the sink rejected the data");
        }
        return true;
    }

    if (stored.method == 0) {
        const std::size_t end = stored.dataOffset + stored.compressedSize;
        if (end > bytes_.size()) return fail(error, path + " is truncated");
        const std::uint32_t crc =
            static_cast<std::uint32_t>(crc32(0, bytes_.data() + stored.dataOffset,
                                             static_cast<uInt>(stored.compressedSize)));
        if (crc != stored.crc32) return fail(error, path + ": CRC32 mismatch");
        if (!sink(bytes_.data() + stored.dataOffset, stored.compressedSize)) {
            return fail(error, path + ": the sink rejected the data");
        }
        return true;
    }

    z_stream stream{};
    if (inflateInit2(&stream, -15) != Z_OK) return fail(error, "zlib could not start");
    stream.next_in = const_cast<Bytef*>(bytes_.data() + stored.dataOffset);
    stream.avail_in = static_cast<uInt>(stored.compressedSize);
    std::vector<std::uint8_t> buffer(1 << 16);
    std::uint64_t total = 0;
    std::uint32_t crc = 0;
    bool done = false;
    while (!done) {
        stream.next_out = buffer.data();
        stream.avail_out = static_cast<uInt>(buffer.size());
        const int status = inflate(&stream, Z_NO_FLUSH);
        const std::size_t produced = buffer.size() - stream.avail_out;
        if (produced > 0) {
            total += produced;
            if (total > stored.uncompressedSize) {
                inflateEnd(&stream);
                return fail(error, path + " inflates beyond its declared size");
            }
            crc = static_cast<std::uint32_t>(
                crc32(crc, buffer.data(), static_cast<uInt>(produced)));
            if (!sink(buffer.data(), produced)) {
                inflateEnd(&stream);
                return fail(error, path + ": the sink rejected the data");
            }
        }
        if (status == Z_STREAM_END) {
            done = true;
        } else if (status != Z_OK) {
            const std::string message =
                stream.msg != nullptr ? stream.msg : zError(status);
            inflateEnd(&stream);
            return fail(error, path + ": " + message);
        } else if (stream.avail_in == 0 && produced == 0) {
            inflateEnd(&stream);
            return fail(error, path + ": truncated deflate stream");
        }
    }
    const bool trailing = stream.avail_in > 0;
    inflateEnd(&stream);
    if (trailing) return fail(error, path + ": data after the deflate stream");
    if (total != stored.uncompressedSize) {
        return fail(error, path + ": size does not match the directory");
    }
    if (crc != stored.crc32) return fail(error, path + ": CRC32 mismatch");
    return true;
}

}  // namespace update
