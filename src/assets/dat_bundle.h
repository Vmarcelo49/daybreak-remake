// =============================================================================
//  dat_bundle.h — Higurashi Daybreak .DAT bundle reader + multi-bundle lookup.
//
//  Ported from remake/src/file_parser/dat_bundle.{h,cpp} (the DX9 side), which
//  ports the read-side of github.com/Vmarcelo49/higurashi-daybreak-in-go
//  (archive/bundle.go + archive/tableData.go + archive/helpers.go) to C++.
//  Write/patch operations are intentionally NOT ported — the game only needs to
//  read the original .DAT files at runtime.
//
//  Original exe sites this reproduces:
//    0x00662d10  open .DAT: read uint16 count, read count*0x10c table bytes,
//                XOR-decrypt the table (key=100, inc=100), then per entry copy
//                the 260-byte name (0x006631b0) and record size/offset.
//    0x00663030  read one payload: seek to the entry offset, read `length`
//                bytes, XOR every byte with (offset >> 1) | 8.  Clamps the read
//                to the file end, which is why a short/oversized entry fails
//                cleanly instead of reading garbage.
//    0x00662f70  "does this bundle contain the name" — the probe the exe's file
//                object walks its bundle list with before reading (0x00653540).
//    0x00663c20  the name comparison used by that bundle index: __stricmp, i.e.
//                the exe matches bundle names case-insensitively.
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
//  Reference behavior preserved verbatim:
//    - Table block is always decrypted with index = 0.
//    - Filename is decoded from Shift-JIS (CP932) to UTF-8.
//    - Each file's payload is XOR-decrypted on read.
//    - find()/find_by_name() return the first table entry with a byte-equal
//      name; a missing name returns nullptr.
//
//  Reference behavior intentionally NOT ported:
//    - CNV -> BMP / WAV conversion (raw bytes are delivered; the caller decides).
//    - Patch / single-patch / update operations.
//
//  Additions over the DX9 port (all additive, none change valid-input results):
//    - lastError() carries a human-readable reason for every false return.
//    - rawName keeps the undecoded CP932 slot bytes, so names can be re-decoded
//      with a different table without reopening the bundle (see NameDecoder).
//    - findAsciiCaseInsensitive() exposes the exe's __stricmp (0x00663c20)
//      lookup explicitly instead of silently changing find() semantics.
//    - read() rejects an entry whose offset+length runs past end-of-file before
//      allocating, instead of throwing std::bad_alloc on a corrupt table.  For
//      length > 0 that is exactly the case where the DX9 read comes back short
//      and returns false anyway; zero-length entries are left untouched (the
//      DX9 path returns true for them at any offset).
// =============================================================================
#pragma once

#include <cstddef>
#include <cstdint>
#include <fstream>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace fnd::assets {

// Decodes one 260-byte name slot into UTF-8.  `bytes` is the slot content up to
// the first NUL, so a decoder never sees the padding.  The default decoder is
// the foundation's generated CP932 table (sjis_table.h, via the same lookup
// cnv.h's sjisToUtf8 uses): ASCII passes through, table hits decode, unmapped
// sequences pass their raw bytes through.  That table is partial — 315 entries,
// covering what the shipped .X texture references need — so ~0.8% of bundle
// entry names (98/12345 across the six shipped bundles, all but one .cnv) decode
// differently from a full CP932 conversion.  Keeping the same decoder as the
// asset layer is deliberate: it is what makes a bundle lookup resolve exactly
// the names the filesystem path resolves.  A caller that wants full-CP932 names
// can pass its own decoder (e.g. one wrapping a complete table) per open().
using NameDecoder = std::function<std::string(const uint8_t* bytes, std::size_t size)>;

// One entry in the .DAT file table.
struct DatEntry {
    uint32_t index  = 0;     // 0-based position in the table
    uint32_t offset = 0;     // absolute offset in the .DAT
    uint32_t length = 0;     // payload length in bytes
    std::string name;        // UTF-8 filename (decoded from Shift-JIS by the decoder)
    std::vector<uint8_t> rawName;   // the slot's bytes up to the first NUL (CP932)
};

// In-memory representation of one opened .DAT file.
//
// Not thread-safe: read() seeks the shared stream, so concurrent reads on one
// bundle must be serialized by the caller (same constraint as the DX9 port).
class DatBundle {
public:
    DatBundle() = default;
    ~DatBundle();

    DatBundle(const DatBundle&)            = delete;
    DatBundle& operator=(const DatBundle&) = delete;
    // The DX9 port deletes moves as well; DatBundleSet below stores bundles by
    // value in exe order, so the default (noexcept) move is kept.
    DatBundle(DatBundle&&) noexcept            = default;
    DatBundle& operator=(DatBundle&&) noexcept = default;

    // Opens `path` and parses the file table.  Returns false on any error (file
    // not found, short read, table larger than the file).  On success, entries()
    // is populated and the file handle stays open for read().
    bool open(const std::string& path, NameDecoder decode = {});

    // Closes the file handle and clears the entry list.  Safe to call multiple
    // times; safe to call on an unopened bundle.  lastError() is not cleared
    // (so a caller can inspect why an open() failed).
    void close();

    // True if open() succeeded and close() has not been called since.
    bool isOpen() const { return m_stream != nullptr; }

    // Path handed to the last successful open().
    const std::string& path() const { return m_path; }

    // Size of the .DAT in bytes (0 when not open).
    uint64_t fileSize() const { return m_fileSize; }

    // Read-only access to the parsed file table.
    const std::vector<DatEntry>& entries() const { return m_entries; }

    // Look up by decoded name, byte-exact, first table entry wins (DX9
    // find_by_name semantics).  Returns nullptr if not found.
    //
    // This is case-sensitive: "data/stage21/00.x" does NOT match an entry stored
    // as "data/stage21/00.X".  That is the DX9 port's behavior, but not the
    // exe's — see findAsciiCaseInsensitive().
    const DatEntry* find(const std::string& name) const;

    // Look up by decoded name with MSVC __stricmp semantics (0x00663c20): ASCII
    // A-Z/a-z compare equal, every byte >= 0x80 compares exactly (that is what
    // _stricmp does in the "C" locale, which is the locale the game runs in).
    // First table entry wins, matching the exe's tree probe (0x00662f70).
    //
    // Use this when reproducing an exe-built lookup path — e.g. the foundation's
    // loadStage() probes both "%02d.X" and "%02d.x" by hand because the original
    // Win32 path lookup folded case; that probe is this function.
    const DatEntry* findAsciiCaseInsensitive(const std::string& name) const;

    // Read + decrypt a file's payload into `out`.  Returns false on error; `out`
    // is resized to the entry's length on success.  On failure `out` is left
    // empty (except for a zero-length entry, which succeeds with an empty `out`).
    bool read(const DatEntry& entry, std::vector<uint8_t>& out) const;

    // Reason for the last failed open()/read().  Empty after a success.
    const std::string& lastError() const { return m_lastError; }

private:
    std::unique_ptr<std::ifstream> m_stream;
    std::string                    m_path;
    uint64_t                       m_fileSize = 0;
    std::vector<DatEntry>          m_entries;
    mutable std::string            m_lastError;
};

// ---------------------------------------------------------------------------
// Multi-bundle lookup.
//
// The exe opens six bundles and searches them in a fixed order, first match
// wins: remake/tests/parity-baseline/logs/asset-*.log shows the DX9 port
// reporting "opened daybreak00.dat .. daybreak07.dat" in this exact order and
// then the daybreak00 entry for data/rika/01.X, which also exists in
// daybreak04.dat with different bytes (9675158 vs 9893738).  983 names are
// shipped by more than one bundle; 445 of those groups differ in content, so
// the order is load-bearing, not cosmetic.
//
// Bundle slots are fixed: bundles()[i] is always the file bundleFileName(i)
// names, even when that file is absent (isOpen() false, entries() empty).
// ---------------------------------------------------------------------------
class DatBundleSet {
public:
    static constexpr std::size_t kBundleCount = 6;

    // Exe/AssetManager search order.  daybreak01.dat is not in the game's list.
    static const char* bundleFileName(std::size_t i);

    // Opens every bundle under `gameDir`.  Returns the number opened; absent
    // files are recorded in missing() and do not fail the call (the exe tolerates
    // a missing bundle the same way).  Any previously opened set is closed first.
    std::size_t openAll(const std::string& gameDir, NameDecoder decode = {});

    const std::vector<DatBundle>& bundles() const { return m_bundles; }
    const DatBundle* bundle(std::size_t i) const;
    const std::vector<std::string>& missing() const { return m_missing; }
    std::size_t entryCount() const;

    // First entry with this decoded name, scanning bundles in order.  When
    // `owner` is non-null it receives the bundle the entry came from, which is
    // what read() on a DatEntry needs (an entry pointer alone is not enough).
    const DatEntry* find(const std::string& name, const DatBundle** owner = nullptr) const;
    const DatEntry* findAsciiCaseInsensitive(const std::string& name,
                                             const DatBundle** owner = nullptr) const;

    // Existence probe (no read).
    bool has(const std::string& name) const;

    // Find + read in one call; false when no bundle has the name or the read
    // fails.  lastError() explains which.
    bool read(const std::string& name, std::vector<uint8_t>& out) const;

    // Entries directly inside `dir` (no deeper '/'), in bundle order then table
    // order, first bundle wins for duplicate names.  `dir` may be empty (top
    // level) and may end with '/'.  This is the bundle-side replacement for
    // fs::directory_iterator in the scene loaders.
    std::vector<const DatEntry*> listDir(const std::string& dir) const;

    const std::string& lastError() const { return m_lastError; }

private:
    std::vector<DatBundle>   m_bundles;
    std::vector<std::string> m_missing;
    mutable std::string      m_lastError;
};

}  // namespace fnd::assets
