#pragma once
// psp/xfile.h — the binary ".x" token writer the converted fighters are stored in.
//
// Both readers this port has are token readers, and they do not accept the same set:
// the vendored core's XBinaryReader takes only "xof 0303bin 0032" (text is rejected
// outright), while the product's loader wants declared template members flattened into
// INTEGER_LIST / FLOAT_LIST runs rather than single-value tokens. Binary with list tokens
// is therefore the one encoding that satisfies both, which is why the conversion emits it
// instead of the far easier text form.
//
// Object shape: NAME(type) [NAME(instance)] OBRACE <values> <children> CBRACE. A data
// reference is OBRACE NAME(name) CBRACE. Strings are STRING + SEMICOLON, numbers are
// always lists, and a run must be exhausted before the kind changes.
#include <cstdint>
#include <initializer_list>
#include <string>
#include <vector>

namespace psp {

class XFile {
public:
    XFile();

    void beginObject(const std::string& type, const std::string& name = {});
    void endObject();
    void reference(const std::string& name);

    void intList(const std::vector<std::uint32_t>& values);
    void intList(std::initializer_list<std::uint32_t> values);
    void floatList(const std::vector<float>& values);
    void floatList(const float* values, std::size_t count);
    void string(const std::string& text);

    // The finished file. The writer must be back at depth zero.
    std::vector<std::uint8_t> take();

private:
    void u16(std::uint32_t value);
    void u32(std::uint32_t value);
    void name(const std::string& text);

    std::vector<std::uint8_t> bytes_;
    unsigned                  depth_ = 0;
};

}  // namespace psp
