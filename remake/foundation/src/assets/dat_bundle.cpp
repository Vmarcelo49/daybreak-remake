// =============================================================================
//  dat_bundle.cpp — see header for the format reference and design notes.
// =============================================================================
#include "dat_bundle.h"

#include "dat_crypto.h"
#include "sjis_table.h"   // foundation's generated CP932 -> UTF-8 table

#include <algorithm>
#include <filesystem>

namespace fnd::assets {

namespace {

// Fixed-size layout of one decrypted 268-byte table entry.
constexpr std::size_t kEntrySize     = 268;
constexpr std::size_t kFilenameBytes = 260;
constexpr std::size_t kLengthOffset  = 260;
constexpr std::size_t kOffsetOffset  = 264;

static_assert(kLengthOffset + 4 == kOffsetOffset, "layout mismatch");
static_assert(kOffsetOffset + 4 == kEntrySize,    "layout mismatch");

// Little-endian readers (the .DAT format is always LE; we do not depend on host
// endianness).
uint16_t read_u16_le(const uint8_t* p) {
    return static_cast<uint16_t>(p[0]) |
           (static_cast<uint16_t>(p[1]) << 8);
}
uint32_t read_u32_le(const uint8_t* p) {
    return static_cast<uint32_t>(p[0]) |
           (static_cast<uint32_t>(p[1]) << 8) |
           (static_cast<uint32_t>(p[2]) << 16) |
           (static_cast<uint32_t>(p[3]) << 24);
}

// The foundation's Shift-JIS decoder: ASCII passes through, a 2-byte CP932 code
// found in sjis_table.h is emitted as its UTF-8 sequence, anything else is
// copied verbatim (so the result can contain non-UTF-8 bytes).  Same walk and
// same table cnv.h's sjisToUtf8 uses, so a bundle name and a .X texture
// reference spelled in the same bytes resolve to the same string.
std::string decode_sjis_table(const uint8_t* bytes, std::size_t size) {
    std::string out;
    out.reserve(size + size / 2);

    const xm::detail::SjisEntry* const lo = xm::detail::kSjisTable;
    const xm::detail::SjisEntry* const hi = lo + xm::detail::kSjisTableSize;

    std::size_t i = 0;
    while (i < size) {
        const uint8_t b = bytes[i];
        if (b < 0x80) {
            out += static_cast<char>(b);
            ++i;
            continue;
        }
        uint16_t code = b;
        std::size_t take = 1;
        if ((b >= 0x81 && b <= 0x9F) || (b >= 0xE0 && b <= 0xFC)) {
            if (i + 1 >= size) {          // truncated lead byte: pass it through
                out += static_cast<char>(b);
                ++i;
                continue;
            }
            code = static_cast<uint16_t>((b << 8) | bytes[i + 1]);
            take = 2;
        }
        const xm::detail::SjisEntry* it = std::lower_bound(
            lo, hi, code,
            [](const xm::detail::SjisEntry& e, uint16_t c) { return e.code < c; });
        if (it != hi && it->code == code) {
            out.append(reinterpret_cast<const char*>(it->utf8), it->len);
        } else {
            out.append(reinterpret_cast<const char*>(bytes + i), take);
        }
        i += take;
    }
    return out;
}

// One directory level join; matches scene.h's detail::joinPath behavior.
std::string join_path(const std::string& dir, const std::string& name) {
    if (dir.empty()) return name;
    const char last = dir.back();
    if (last == '/' || last == '\\') return dir + name;
    return dir + "/" + name;
}

}  // namespace

DatBundle::~DatBundle() { close(); }

bool DatBundle::open(const std::string& path, NameDecoder decode) {
    close();
    m_lastError.clear();

    auto stream = std::make_unique<std::ifstream>(std::filesystem::u8path(path), std::ios::binary | std::ios::in);
    if (!stream->is_open()) {
        m_lastError = "open: cannot open " + path;
        return false;
    }

    // Size up front: read() uses it to reject offsets past end-of-file before
    // allocating, which is the same set of inputs the DX9 short-read check
    // rejects (0x00663030 clamps every read to the file end).
    stream->seekg(0, std::ios::end);
    const std::streamoff end = stream->tellg();
    stream->seekg(0, std::ios::beg);
    if (end < 0 || !stream->good()) {
        m_lastError = "open: cannot size " + path;
        return false;
    }
    const uint64_t file_size = static_cast<uint64_t>(end);

    // 1. Read numFiles (uint16 LE).
    uint8_t hdr[2];
    stream->read(reinterpret_cast<char*>(hdr), sizeof(hdr));
    if (stream->gcount() != static_cast<std::streamsize>(sizeof(hdr))) {
        m_lastError = "open: short header in " + path + " (" +
                      std::to_string(stream->gcount()) + "/2 bytes)";
        return false;
    }
    const uint16_t num_files = read_u16_le(hdr);

    // 2. Read the encrypted table block.
    const std::size_t table_bytes = static_cast<std::size_t>(num_files) * kEntrySize;
    std::vector<uint8_t> table(table_bytes);
    stream->read(reinterpret_cast<char*>(table.data()),
                 static_cast<std::streamsize>(table_bytes));
    if (static_cast<std::size_t>(stream->gcount()) != table_bytes) {
        m_lastError = "open: table truncated in " + path + " (" +
                      std::to_string(stream->gcount()) + "/" +
                      std::to_string(table_bytes) + " bytes; numFiles=" +
                      std::to_string(num_files) + ")";
        return false;
    }

    // 3. Decrypt the table with index = 0 (matches the Go reference, which
    //    always calls DecryptFileTableBlock(0, ...), and the exe's key=100,
    //    inc=100 loop at 0x00662d10).
    dat_crypto::file_table_xor(0u, table);

    // 4. Parse entries.
    m_entries.clear();
    m_entries.reserve(num_files);
    for (uint16_t i = 0; i < num_files; ++i) {
        const uint8_t* e = table.data() + static_cast<std::size_t>(i) * kEntrySize;

        std::size_t name_len = 0;
        while (name_len < kFilenameBytes && e[name_len] != 0) ++name_len;

        DatEntry entry;
        entry.index  = i;
        entry.rawName.assign(e, e + name_len);
        entry.name   = decode ? decode(e, name_len) : decode_sjis_table(e, name_len);
        entry.length = read_u32_le(e + kLengthOffset);
        entry.offset = read_u32_le(e + kOffsetOffset);
        m_entries.push_back(std::move(entry));
    }

    m_stream   = std::move(stream);
    m_path     = path;
    m_fileSize = file_size;
    return true;
}

void DatBundle::close() {
    if (m_stream) {
        m_stream->close();
        m_stream.reset();
    }
    m_entries.clear();
    m_path.clear();
    m_fileSize = 0;
}

const DatEntry* DatBundle::find(const std::string& name) const {
    for (const auto& e : m_entries) {
        if (e.name == name) return &e;
    }
    return nullptr;
}

const DatEntry* DatBundle::findAsciiCaseInsensitive(const std::string& name) const {
    // Per-byte ASCII fold.  _stricmp() in the "C" locale only folds A-Z, and
    // leaves every byte >= 0x80 alone, so a CP932 double-byte name compares
    // exactly — which is what the exe's tree does at 0x00663c20.
    const auto fold = [](unsigned char c) -> unsigned char {
        return (c >= 'A' && c <= 'Z') ? static_cast<unsigned char>(c - 'A' + 'a') : c;
    };
    for (const auto& e : m_entries) {
        if (e.name.size() != name.size()) continue;
        bool same = true;
        for (std::size_t i = 0; i < name.size(); ++i) {
            if (fold(static_cast<unsigned char>(e.name[i])) !=
                fold(static_cast<unsigned char>(name[i]))) {
                same = false;
                break;
            }
        }
        if (same) return &e;
    }
    return nullptr;
}

bool DatBundle::read(const DatEntry& entry, std::vector<uint8_t>& out) const {
    if (!m_stream) {
        m_lastError = "read: bundle not open";
        return false;
    }

    // Bounds first: a corrupt table can claim a length of ~4 GiB, which the DX9
    // path would try to allocate (std::bad_alloc / length_error) before its
    // read ever failed.  For length > 0 this check rejects exactly the inputs
    // whose read comes back short; length == 0 is left to the read, which is
    // what the DX9 path returns true for.
    if (entry.length > 0 &&
        static_cast<uint64_t>(entry.offset) + entry.length > m_fileSize) {
        m_lastError = "read: entry " + std::to_string(entry.index) + " (" +
                      entry.name + ") out of bounds: offset " +
                      std::to_string(entry.offset) + " + length " +
                      std::to_string(entry.length) + " > file size " +
                      std::to_string(m_fileSize);
        out.clear();
        return false;
    }

    out.resize(entry.length);

    m_stream->clear();
    m_stream->seekg(static_cast<std::streamoff>(entry.offset), std::ios::beg);
    if (!m_stream->good()) {
        out.clear();
        m_lastError = "read: seek to " + std::to_string(entry.offset) +
                      " failed for " + entry.name;
        return false;
    }

    if (entry.length > 0) {
        m_stream->read(reinterpret_cast<char*>(out.data()),
                       static_cast<std::streamsize>(entry.length));
        if (static_cast<std::size_t>(m_stream->gcount()) != entry.length) {
            m_lastError = "read: short read for " + entry.name + " (" +
                          std::to_string(m_stream->gcount()) + "/" +
                          std::to_string(entry.length) + " bytes)";
            out.clear();
            return false;
        }
        dat_crypto::file_data_xor(entry.offset, out);
    }
    return true;
}

// ---------------------------------------------------------------------------
// DatBundleSet
// ---------------------------------------------------------------------------

// Bundle order is *precedence* order, not file-number order: a name that ships in more
// than one archive resolves to the one registered earliest, and the exe registers
// daybreak07, then daybreak04, then daybreak00 (0x64d4d4 / 0x64d4ee / 0x64d4fe) before the
// rest. Its own name table (.rdata 0x6a5598: daybreak00, 04, 07, 05, 02, 06 — 01 and 03 do
// not appear) is the *open* sequence, which is a different thing and is not what decides a
// duplicate; a Wine file trace shows that same open order.
//
// This was the other way round here (00, 02, 04, 05, 06, 07) and it is measurably wrong:
// `data/object/P01.cnv` ships in daybreak00 (sha1 6830e6ee, fan captions baked into the
// wedges) and daybreak04 (6ebc4967, captions split into a three-row strip). The original's
// own screen battle-hud.webp matches daybreak04's art against a daybreak00 control — fan
// quad mean |diff| 3.20 vs 10.39, caption quad 2.65 vs 100.51 — so 04 must beat 00, and
// resolving P01 to 00 drew the wrong fan and no caption strip.
//
// The first three entries are the RE'd registration order. The tail (05, 02, 06) follows
// the name table because their registration sites were not traced; no shipped name is
// known to be duplicated across just those three, so the tail order is untested rather
// than verified.
const char* DatBundleSet::bundleFileName(std::size_t i) {
    static const char* const kOrder[kBundleCount] = {
        "daybreak07.dat", "daybreak04.dat", "daybreak00.dat",
        "daybreak05.dat", "daybreak02.dat", "daybreak06.dat",
    };
    return i < kBundleCount ? kOrder[i] : "";
}

std::size_t DatBundleSet::openAll(const std::string& gameDir, NameDecoder decode) {
    m_bundles.clear();
    m_missing.clear();
    m_lastError.clear();
    m_bundles.resize(kBundleCount);

    std::size_t opened = 0;
    for (std::size_t i = 0; i < kBundleCount; ++i) {
        const std::string file = bundleFileName(i);
        if (m_bundles[i].open(join_path(gameDir, file), decode)) {
            ++opened;
        } else {
            m_missing.push_back(file);
            if (!m_lastError.empty()) m_lastError += "; ";
            m_lastError += m_bundles[i].lastError();
        }
    }
    return opened;
}

const DatBundle* DatBundleSet::bundle(std::size_t i) const {
    return i < m_bundles.size() ? &m_bundles[i] : nullptr;
}

std::size_t DatBundleSet::entryCount() const {
    std::size_t n = 0;
    for (const DatBundle& b : m_bundles) n += b.entries().size();
    return n;
}

const DatEntry* DatBundleSet::find(const std::string& name,
                                   const DatBundle** owner) const {
    for (const DatBundle& b : m_bundles) {
        if (!b.isOpen()) continue;
        if (const DatEntry* e = b.find(name)) {
            if (owner) *owner = &b;
            return e;
        }
    }
    if (owner) *owner = nullptr;
    m_lastError = "find: no bundle contains '" + name + "'";
    return nullptr;
}

const DatEntry* DatBundleSet::findAsciiCaseInsensitive(const std::string& name,
                                                       const DatBundle** owner) const {
    for (const DatBundle& b : m_bundles) {
        if (!b.isOpen()) continue;
        if (const DatEntry* e = b.findAsciiCaseInsensitive(name)) {
            if (owner) *owner = &b;
            return e;
        }
    }
    if (owner) *owner = nullptr;
    m_lastError = "findAsciiCaseInsensitive: no bundle contains '" + name + "'";
    return nullptr;
}

bool DatBundleSet::has(const std::string& name) const {
    return find(name) != nullptr;
}

bool DatBundleSet::read(const std::string& name, std::vector<uint8_t>& out) const {
    const DatBundle* owner = nullptr;
    const DatEntry* entry = find(name, &owner);
    if (!entry || !owner) {
        out.clear();
        return false;   // find() already set lastError
    }
    if (!owner->read(*entry, out)) {
        m_lastError = owner->lastError();
        return false;
    }
    return true;
}

std::vector<const DatEntry*> DatBundleSet::listDir(const std::string& dir) const {
    std::string prefix = dir;
    while (!prefix.empty() && (prefix.back() == '/' || prefix.back() == '\\')) {
        prefix.pop_back();
    }
    if (!prefix.empty()) prefix += '/';

    std::vector<const DatEntry*> out;
    std::vector<std::string> taken;   // names claimed by an earlier bundle
    for (const DatBundle& b : m_bundles) {
        if (!b.isOpen()) continue;
        for (const DatEntry& e : b.entries()) {
            if (e.name.empty()) continue;
            if (!prefix.empty()) {
                // Must be strictly inside `prefix` and have no deeper '/'.
                if (e.name.size() <= prefix.size()) continue;
                if (e.name.compare(0, prefix.size(), prefix) != 0) continue;
            }
            if (e.name.find('/', prefix.size()) != std::string::npos) continue;
            if (std::find(taken.begin(), taken.end(), e.name) != taken.end()) continue;
            taken.push_back(e.name);
            out.push_back(&e);
        }
    }
    return out;
}

}  // namespace fnd::assets
