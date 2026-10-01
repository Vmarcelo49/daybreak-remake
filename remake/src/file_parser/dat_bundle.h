// =============================================================================
//  dat_bundle.h — Higurashi Daybreak .DAT bundle reader.
//
//  Ports the read-side of github.com/Vmarcelo49/higurashi-daybreak-in-go
//  (archive/bundle.go + archive/tableData.go + archive/helpers.go) to C++23.
//  Write/patch operations are intentionally NOT ported — daybreak only needs
//  to read the original game's .DAT files at runtime.
//
//  File layout (all little-endian):
//
//    offset 0:    uint16  numFiles
//    offset 2:    uint8   fileTable[numFiles * 268]   (XOR-encrypted, see dat_crypto)
//
//  Each 268-byte table entry (after decryption):
//
//    offset 0:    char    filename[260]   (Shift-JIS, null-padded)
//    offset 260:  uint32  length          (file size in bytes)
//    offset 264:  uint32  offset          (absolute offset in the .DAT)
//
//  File payloads are stored at their `offset` and are XOR-encrypted with a
//  single byte derived from the offset (see dat_crypto::file_data_key).
//
//  Reference Go behavior preserved verbatim:
//    - Table block is always decrypted with index = 0.
//    - Filename is decoded from Shift-JIS to UTF-8.
//    - Each file's payload is XOR-decrypted on read.
//
//  Reference Go behavior intentionally NOT ported:
//    - CNV -> BMP / WAV conversion (we deliver raw bytes; the asset manager
//      can decide what to do with them later).
//    - Patch / single-patch / update operations.
// =============================================================================
#pragma once

#include <cstdint>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

namespace daybreak::file_parser {

// One entry in the .DAT file table.  Filenames are stored as UTF-8.
struct DatFileEntry {
    uint32_t    index  = 0;     // 0-based position in the table
    uint32_t    offset = 0;     // absolute offset in the .DAT
    uint32_t    length = 0;     // payload length in bytes
    std::string name;           // UTF-8 filename (decoded from Shift-JIS)
};

// In-memory representation of an opened .DAT file.
class DatBundle {
public:
    DatBundle() = default;
    ~DatBundle();

    DatBundle(const DatBundle&)            = delete;
    DatBundle& operator=(const DatBundle&) = delete;
    DatBundle(DatBundle&&)                 = delete;
    DatBundle& operator=(DatBundle&&)      = delete;

    // Opens `path` and parses the file table.  Returns false on any error
    // (file not found, short read, decrypt failure).  On success, entries()
    // is populated and the underlying file handle stays open for read_file().
    bool open(const std::string& path);

    // Closes the file handle and clears the entry list.  Safe to call
    // multiple times; safe to call on an unopened bundle.
    void close();

    // True if open() succeeded and close() has not been called since.
    bool is_open() const { return m_stream != nullptr; }

    // Read-only access to the parsed file table.
    const std::vector<DatFileEntry>& entries() const { return m_entries; }

    // Look up an entry by index.  Returns nullptr if out of range.
    const DatFileEntry* find_by_index(uint32_t index) const;

    // Look up an entry by name (case-sensitive UTF-8).  Returns nullptr if
    // not found.
    const DatFileEntry* find_by_name(const std::string& name) const;

    // Read + decrypt a file's payload into `out`.  Returns false on error.
    // `out` is resized to the entry's length on success.
    bool read_file(const DatFileEntry& entry, std::vector<uint8_t>& out) const;

private:
    std::unique_ptr<std::ifstream> m_stream;
    std::string                    m_path;
    std::vector<DatFileEntry>      m_entries;
};

// Pretty-print one entry (for `-list` style output).
// Format matches the Go reference:
//   "   index: %d, offset: %d, length: %d, name: %s\n"
std::string format_entry(const DatFileEntry& entry);

} // namespace daybreak::file_parser
