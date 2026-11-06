// psp/xfile.cpp — binary .X token emission.
#include "psp/xfile.h"

#include <cstring>
#include <stdexcept>

namespace psp {
namespace {

enum Token : std::uint16_t {
    kName = 1, kString = 2, kIntList = 6, kFloatList = 7, kOBrace = 10, kCBrace = 11,
    kSemi = 20,
};

const char kHeader[16] = {'x', 'o', 'f', ' ', '0', '3', '0', '3',
                          'b', 'i', 'n', ' ', '0', '0', '3', '2'};

}  // namespace

XFile::XFile() { bytes_.assign(kHeader, kHeader + sizeof kHeader); }

void XFile::u16(std::uint32_t value) {
    bytes_.push_back((std::uint8_t)(value & 0xFF));
    bytes_.push_back((std::uint8_t)((value >> 8) & 0xFF));
}

void XFile::u32(std::uint32_t value) {
    for (unsigned i = 0; i < 4; ++i) bytes_.push_back((std::uint8_t)((value >> (8 * i)) & 0xFF));
}

void XFile::name(const std::string& text) {
    // The length is the byte count with no terminator: the shipped files carry no NUL and
    // both readers take the raw bytes as the name (the core appends nothing).
    u16(kName);
    u32((std::uint32_t)text.size());
    bytes_.insert(bytes_.end(), text.begin(), text.end());
}

void XFile::beginObject(const std::string& type, const std::string& instance) {
    name(type);
    if (!instance.empty()) name(instance);
    u16(kOBrace);
    ++depth_;
}

void XFile::endObject() {
    if (!depth_) throw std::logic_error("xfile: no object to close");
    u16(kCBrace);
    --depth_;
}

void XFile::reference(const std::string& name_) {
    u16(kOBrace);
    name(name_);
    u16(kCBrace);
}

void XFile::intList(const std::vector<std::uint32_t>& values) {
    u16(kIntList);
    u32((std::uint32_t)values.size());
    for (std::uint32_t value : values) u32(value);
}

void XFile::intList(std::initializer_list<std::uint32_t> values) {
    intList(std::vector<std::uint32_t>(values));
}

void XFile::floatList(const float* values, std::size_t count) {
    u16(kFloatList);
    u32((std::uint32_t)count);
    for (std::size_t i = 0; i < count; ++i) {
        std::uint32_t bits = 0;
        std::memcpy(&bits, values + i, 4);
        u32(bits);
    }
}

void XFile::floatList(const std::vector<float>& values) { floatList(values.data(), values.size()); }

void XFile::string(const std::string& text) {
    u16(kString);
    u32((std::uint32_t)text.size());
    bytes_.insert(bytes_.end(), text.begin(), text.end());
    u16(kSemi);
}

std::vector<std::uint8_t> XFile::take() {
    if (depth_) throw std::logic_error("xfile: unclosed object");
    return std::move(bytes_);
}

}  // namespace psp
