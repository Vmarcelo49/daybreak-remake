// psp/gim.cpp — GIM container walk and pixel decode.
#include "psp/gim.h"

#include <cstring>
#include <stdexcept>
#include <string>

namespace psp {
namespace {

std::uint32_t rd16(const std::uint8_t* p) { return (std::uint32_t)p[0] | ((std::uint32_t)p[1] << 8); }
std::uint32_t rd32(const std::uint8_t* p) {
    return (std::uint32_t)p[0] | ((std::uint32_t)p[1] << 8) | ((std::uint32_t)p[2] << 16) |
           ((std::uint32_t)p[3] << 24);
}

struct Block {
    std::uint32_t image = 0;    // payload offset of the 0x04 block
    std::uint32_t palette = 0;  // payload offset of the 0x05 block, 0 when absent
};

class Walker {
public:
    explicit Walker(const std::vector<std::uint8_t>& bytes) : bytes_(bytes) {}

    std::vector<Block> pictures;

    void run() {
        if (bytes_.size() < 0x20) throw std::runtime_error("gim: shorter than its header");
        descend(0x10, bytes_.size(), 0);
    }

private:
    void descend(std::size_t at, std::size_t end, unsigned depth) {
        if (depth > 16) throw std::runtime_error("gim: container nesting too deep");
        while (at + 16 <= end) {
            const std::uint32_t kind = rd16(bytes_.data() + at);
            const std::uint32_t size = rd32(bytes_.data() + at + 4);
            const std::uint32_t following = rd32(bytes_.data() + at + 8);
            const std::uint32_t inner = rd32(bytes_.data() + at + 12);
            if (size < 16 || at + size > end) return;   // the reference walker stops here too
            if (inner > size) throw std::runtime_error("gim: block header points past its block");
            if (kind == 2) {
                descend(at + inner, at + size, depth + 1);
            } else if (kind == 3) {
                pictures.emplace_back();
                descend(at + inner, at + size, depth + 1);
            } else if ((kind == 4 || kind == 5) && !pictures.empty() && inner + 5 * 4 <= size) {
                Block& picture = pictures.back();
                // The payload header sits `inner` bytes into the block; the block start is
                // what the offsets below are relative to, which is how the reference reads.
                (kind == 4 ? picture.image : picture.palette) = (std::uint32_t)(at + inner);
            }
            at += following ? following : size;
        }
    }

    const std::vector<std::uint8_t>& bytes_;
};

// The 16-bit colour forms a GIM palette can use, from the reference implementation.
void colour16(std::uint32_t value, std::uint32_t kind, std::uint8_t* out) {
    switch (kind) {
        case 0:   // RGBA 5551 with 5-bit channels, blue in the low bits
            out[0] = (std::uint8_t)(((value) & 31) * 255 / 31);
            out[1] = (std::uint8_t)(((value >> 5) & 63) * 255 / 63);
            out[2] = (std::uint8_t)(((value >> 11) & 31) * 255 / 31);
            out[3] = 0xFF;
            return;
        case 1:
            out[0] = (std::uint8_t)((value & 31) * 255 / 31);
            out[1] = (std::uint8_t)(((value >> 5) & 31) * 255 / 31);
            out[2] = (std::uint8_t)(((value >> 10) & 31) * 255 / 31);
            out[3] = (value >> 15) ? 0xFF : 0x00;
            return;
        case 2:
            out[0] = (std::uint8_t)((value & 15) * 17);
            out[1] = (std::uint8_t)(((value >> 4) & 15) * 17);
            out[2] = (std::uint8_t)(((value >> 8) & 15) * 17);
            out[3] = (std::uint8_t)((value >> 12) * 17);
            return;
        default:
            throw std::runtime_error("gim: colour format " + std::to_string(kind));
    }
}

RgbaImage decodePicture(const std::vector<std::uint8_t>& bytes, const Block& block) {
    const std::uint8_t* header = bytes.data() + block.image;
    if ((std::size_t)block.image + 0x20 > bytes.size()) throw std::runtime_error("gim: image header past the file");
    const std::uint32_t kind = rd16(header + 4);
    const std::uint32_t order = rd16(header + 6);
    const std::uint32_t width = rd16(header + 8);
    const std::uint32_t height = rd16(header + 10);
    const std::uint32_t bits = rd16(header + 12);
    const std::uint32_t align = rd16(header + 14);
    if (!width || !height || !bits) throw std::runtime_error("gim: image with no size or bits");
    if (kind != 3 && kind != 4 && kind != 5) throw std::runtime_error("gim: pixel format " + std::to_string(kind));

    const std::uint32_t dataOffset = rd32(header + 0x1C);
    const std::size_t raw = (std::size_t)block.image + dataOffset;
    if (raw > bytes.size()) throw std::runtime_error("gim: pixel data past the file");

    // Row pitch: swizzled images are always 16-byte aligned, unswizzled ones follow the
    // block's alignment field.
    std::uint32_t pitch = (width * bits + 7) / 8;
    if (order == 1) pitch = (pitch + 15) & ~15u;
    else if (align) pitch = (pitch + align - 1) & ~(align - 1);
    if (!pitch) throw std::runtime_error("gim: zero row pitch");
    // The padded row pitch is the real row, not the header's width: the art continues into the
    // padding, so the decoded width is the pitch in texels. Measured on the select family
    // (docs/psp/research/RESOURCES.md §8): vs_enter_satoshi declares 168 and is 176 wide,
    // bustup_satoshi declares 220 and is 224. Decoding at the declared width keeps the picture
    // but cuts the last 8 or 4 columns, which is where a shoulder and a sleeve live.
    const std::uint32_t decodedWidth = pitch * 8 / bits;

    std::vector<std::uint8_t> rows;
    if (order == 1) {
        // 16-byte columns by 8 rows: the PSP GE's swizzle.
        const std::uint32_t rowBlocks = (height + 7) & ~7u;
        rows.assign((std::size_t)pitch * rowBlocks, 0);
        std::size_t source = raw;
        for (std::uint32_t band = 0; band < (height + 7) / 8; ++band) {
            for (std::uint32_t x = 0; x < pitch; x += 16) {
                for (std::uint32_t y = 0; y < 8; ++y) {
                    if (source + 16 > bytes.size()) throw std::runtime_error("gim: swizzled data past the file");
                    const std::size_t target = ((std::size_t)band * 8 + y) * pitch + x;
                    std::memcpy(rows.data() + target, bytes.data() + source, 16);
                    source += 16;
                }
            }
        }
    } else {
        const std::size_t need = (std::size_t)pitch * height;
        if (raw + need > bytes.size()) throw std::runtime_error("gim: pixel data past the file");
        rows.assign(bytes.begin() + (std::ptrdiff_t)raw, bytes.begin() + (std::ptrdiff_t)(raw + need));
    }

    std::vector<std::uint8_t> palette;
    if (kind == 4 || kind == 5) {
        if (!block.palette) throw std::runtime_error("gim: indexed image without a palette");
        const std::uint8_t* header = bytes.data() + block.palette;
        if ((std::size_t)block.palette + 0x20 > bytes.size()) throw std::runtime_error("gim: palette header past the file");
        // Five u16 form the palette header: format and entry count at offsets 4 and 8,
        // exactly as the reference reader unpacks them.
        const std::uint32_t paletteKind = rd16(header + 4);
        const std::uint32_t paletteWidth = rd16(header + 8);
        const std::uint32_t paletteOffset = rd32(header + 0x1C);
        const std::size_t source = (std::size_t)block.palette + paletteOffset;
        const std::size_t step = paletteKind == 3 ? 4u : 2u;
        if (source + (std::size_t)paletteWidth * step > bytes.size())
            throw std::runtime_error("gim: palette past the file");
        palette.resize((std::size_t)paletteWidth * 4);
        for (std::uint32_t i = 0; i < paletteWidth; ++i) {
            std::uint8_t* entry = palette.data() + i * 4;
            if (paletteKind == 3) std::memcpy(entry, bytes.data() + source + i * 4, 4);
            else colour16(rd16(bytes.data() + source + i * 2), paletteKind, entry);
        }
    }

    RgbaImage image;
    image.width = decodedWidth;
    image.height = height;
    image.rgba.assign((std::size_t)decodedWidth * height * 4, 0);
    for (std::uint32_t y = 0; y < height; ++y) {
        const std::uint8_t* line = rows.data() + (std::size_t)y * pitch;
        for (std::uint32_t x = 0; x < decodedWidth; ++x) {
            std::uint8_t* out = image.rgba.data() + ((std::size_t)y * decodedWidth + x) * 4;
            if (kind == 3) {
                std::memcpy(out, line + x * 4, 4);
            } else if (kind == 5) {
                const unsigned index = line[x];
                if ((std::size_t)(index + 1) * 4 > palette.size()) throw std::runtime_error("gim: palette index past the table");
                std::memcpy(out, palette.data() + (std::size_t)index * 4, 4);
            } else {   // kind 4: 4-bit indices, low nibble first
                const unsigned index = (line[x / 2] >> (4 * (x & 1))) & 15u;
                if ((std::size_t)(index + 1) * 4 > palette.size()) throw std::runtime_error("gim: palette index past the table");
                std::memcpy(out, palette.data() + (std::size_t)index * 4, 4);
            }
        }
    }
    return image;
}

}  // namespace

std::vector<RgbaImage> decodeGim(const std::vector<std::uint8_t>& bytes) {
    Walker walker(bytes);
    walker.run();
    std::vector<RgbaImage> pictures;
    pictures.reserve(walker.pictures.size());
    for (const Block& block : walker.pictures) {
        if (!block.image) throw std::runtime_error("gim: picture without an image block");
        pictures.push_back(decodePicture(bytes, block));
    }
    return pictures;
}

}  // namespace psp
