// =============================================================================
//  dat_bundle.cpp — see header for the format reference and design notes.
// =============================================================================
#include "dat_bundle.h"

#include "dat_crypto.h"
#include "text_codec.h"

#include <algorithm>
#include <cstring>
#include <sstream>

namespace daybreak::file_parser {

namespace {

// Fixed-size layout of one decrypted 268-byte table entry.
constexpr std::size_t kEntrySize     = 268;
constexpr std::size_t kFilenameBytes = 260;
constexpr std::size_t kLengthOffset  = 260;
constexpr std::size_t kOffsetOffset  = 264;

static_assert(kLengthOffset + 4 == kOffsetOffset, "layout mismatch");
static_assert(kOffsetOffset + 4 == kEntrySize,    "layout mismatch");

// Little-endian readers (the .DAT format is always LE; we don't depend on
// host endianness).
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

} // namespace

DatBundle::~DatBundle() { close(); }

bool DatBundle::open(const std::string& path) {
    close();
    m_path = path;

    auto stream = std::make_unique<std::ifstream>(
        path, std::ios::binary | std::ios::in);
    if (!stream->is_open()) return false;

    // 1. Read numFiles (uint16 LE).
    uint8_t hdr[2];
    stream->read(reinterpret_cast<char*>(hdr), sizeof(hdr));
    if (stream->gcount() != static_cast<std::streamsize>(sizeof(hdr))) {
        return false;
    }
    const uint16_t num_files = read_u16_le(hdr);

    // 2. Read the encrypted table block.
    const std::size_t table_bytes = static_cast<std::size_t>(num_files) * kEntrySize;
    std::vector<uint8_t> table(table_bytes);
    stream->read(reinterpret_cast<char*>(table.data()),
                 static_cast<std::streamsize>(table_bytes));
    if (static_cast<std::size_t>(stream->gcount()) != table_bytes) {
        return false;
    }

    // 3. Decrypt the table with index = 0 (matches the Go reference,
    //    which always calls DecryptFileTableBlock(0, ...)).
    dat_crypto::file_table_xor(0u, table);

    // 4. Parse entries.
    m_entries.clear();
    m_entries.reserve(num_files);
    for (uint16_t i = 0; i < num_files; ++i) {
        const uint8_t* e = table.data() + static_cast<std::size_t>(i) * kEntrySize;

        DatFileEntry entry;
        entry.index  = i;
        entry.name   = text_codec::shift_jis_buffer_to_utf8(e, kFilenameBytes);
        entry.length = read_u32_le(e + kLengthOffset);
        entry.offset = read_u32_le(e + kOffsetOffset);
        m_entries.push_back(std::move(entry));
    }

    m_stream = std::move(stream);
    return true;
}

void DatBundle::close() {
    if (m_stream) {
        m_stream->close();
        m_stream.reset();
    }
    m_entries.clear();
    m_path.clear();
}

const DatFileEntry* DatBundle::find_by_index(uint32_t index) const {
    if (index >= m_entries.size()) return nullptr;
    return &m_entries[index];
}

const DatFileEntry* DatBundle::find_by_name(const std::string& name) const {
    for (const auto& e : m_entries) {
        if (e.name == name) return &e;
    }
    return nullptr;
}

bool DatBundle::read_file(const DatFileEntry& entry,
                          std::vector<uint8_t>& out) const {
    if (!m_stream) return false;

    out.resize(entry.length);

    m_stream->clear();
    m_stream->seekg(static_cast<std::streamoff>(entry.offset), std::ios::beg);
    if (!m_stream->good()) return false;

    m_stream->read(reinterpret_cast<char*>(out.data()),
                   static_cast<std::streamsize>(entry.length));
    if (static_cast<std::size_t>(m_stream->gcount()) != entry.length) {
        out.clear();
        return false;
    }

    dat_crypto::file_data_xor(entry.offset, out);
    return true;
}

std::string format_entry(const DatFileEntry& entry) {
    std::ostringstream ss;
    ss << "   index: " << entry.index
       << ", offset: " << entry.offset
       << ", length: " << entry.length
       << ", name: " << entry.name;
    return ss.str();
}

} // namespace daybreak::file_parser
