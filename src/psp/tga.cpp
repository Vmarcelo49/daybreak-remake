// psp/tga.cpp — TGA decode and the remake's .cnv writer.
#include "psp/tga.h"

#include <cstring>
#include <stdexcept>

namespace psp {
namespace {

std::uint32_t rd16(const std::uint8_t* p) { return (std::uint32_t)p[0] | ((std::uint32_t)p[1] << 8); }

void putBgraOrRgba(std::uint8_t* out, const std::uint8_t* colour, unsigned bytes, bool bgr) {
    // TGA stores blue first; the palette in these files is BGR(A) as well.
    if (bgr) {
        out[0] = colour[2];
        out[1] = colour[1];
        out[2] = colour[0];
    } else {
        out[0] = colour[0];
        out[1] = colour[1];
        out[2] = colour[2];
    }
    out[3] = bytes >= 4 ? colour[3] : 0xFF;
}

}  // namespace

RgbaImage decodeTga(const std::vector<std::uint8_t>& bytes) {
    if (bytes.size() < 18) throw std::runtime_error("tga: shorter than its header");
    const std::uint8_t* d = bytes.data();
    const unsigned idLength = d[0];
    const unsigned colourMapType = d[1];
    const unsigned kind = d[2];
    const unsigned mapFirst = rd16(d + 3);
    const unsigned mapCount = rd16(d + 5);
    const unsigned mapBits = d[7];
    const unsigned width = rd16(d + 12);
    const unsigned height = rd16(d + 14);
    const unsigned bits = d[16];
    const unsigned descriptor = d[17];
    const bool rightToLeft = (descriptor & 0x10) != 0;
    const bool topDown = (descriptor & 0x20) != 0;

    if (!width || !height) throw std::runtime_error("tga: zero image size");
    std::size_t at = 18 + idLength;

    std::vector<std::uint8_t> palette;
    unsigned paletteStep = 0;
    if (colourMapType == 1) {
        if (mapBits != 15 && mapBits != 16 && mapBits != 24 && mapBits != 32)
            throw std::runtime_error("tga: " + std::to_string(mapBits) + "-bit palette");
        paletteStep = mapBits / 8;
        const std::size_t size = (std::size_t)mapCount * paletteStep;
        if (at + size > bytes.size()) throw std::runtime_error("tga: palette runs past the file");
        palette.assign(d + at, d + at + size);
        at += size;
    }

    const bool rle = kind >= 9;
    const unsigned base = rle ? kind - 8 : kind;
    if (base != 1 && base != 2 && base != 3)
        throw std::runtime_error("tga: image kind " + std::to_string(kind));
    const unsigned sourceStep = base == 3 ? 1 : bits / 8;
    if (sourceStep == 0 || (base == 1 && colourMapType != 1))
        throw std::runtime_error("tga: colour map missing or bits per pixel 0");

    auto sourcePixel = [&](std::size_t index) {
        if (at + (index + 1) * sourceStep > bytes.size())
            throw std::runtime_error("tga: pixel data runs past the file");
        return d + at + index * sourceStep;
    };

    RgbaImage image;
    image.width = width;
    image.height = height;
    image.rgba.assign((std::size_t)width * height * 4, 0);
    const std::size_t pixels = (std::size_t)width * height;

    auto write = [&](std::size_t index, const std::uint8_t* colour) {
        std::uint8_t* out = image.rgba.data() + index * 4;
        if (base == 1) {
            const unsigned entry = (colour[0] | (sourceStep > 1 ? (unsigned)colour[1] << 8 : 0u));
            const unsigned slot = entry >= mapFirst ? entry - mapFirst : 0u;
            if ((slot + 1) * paletteStep > palette.size())
                throw std::runtime_error("tga: palette index past the colour map");
            putBgraOrRgba(out, palette.data() + slot * paletteStep, paletteStep, true);
        } else if (base == 3) {
            out[0] = out[1] = out[2] = colour[0];
            out[3] = 0xFF;
        } else {
            if (sourceStep == 2) {   // 16-bit 5551
                const std::uint32_t value = rd16(colour);
                out[0] = (std::uint8_t)(((value >> 10) & 31) * 255 / 31);
                out[1] = (std::uint8_t)(((value >> 5) & 31) * 255 / 31);
                out[2] = (std::uint8_t)((value & 31) * 255 / 31);
                out[3] = (value & 0x8000) ? 0xFF : 0x00;
                return;
            }
            putBgraOrRgba(out, colour, sourceStep, true);
        }
    };

    std::size_t written = 0;
    while (written < pixels) {
        std::size_t run = 1;
        bool repeat = false;
        if (rle) {
            if (at >= bytes.size()) throw std::runtime_error("tga: RLE packet runs past the file");
            const unsigned packet = d[at++];
            run = (packet & 0x7F) + 1;
            repeat = (packet & 0x80) != 0;
        }
        if (written + run > pixels) run = pixels - written;
        if (repeat) {
            const std::uint8_t* colour = sourcePixel(0);
            std::uint8_t stored[4] = {colour[0], colour[1], colour[2],
                                      sourceStep >= 4 ? colour[3] : (std::uint8_t)0xFF};
            for (std::size_t i = 0; i < run; ++i) write(written + i, stored);
            at += sourceStep;
        } else {
            for (std::size_t i = 0; i < run; ++i) write(written + i, sourcePixel(i));
            at += run * sourceStep;
        }
        written += run;
    }

    // TGA's default origin is the bottom-left. Flip once here so every consumer (and the
    // .cnv writer, which stores rows from the top) deals in one orientation.
    if (!topDown) {
        const std::size_t stride = (std::size_t)width * 4;
        std::vector<std::uint8_t> row(stride);
        for (unsigned y = 0; y < height / 2; ++y) {
            std::uint8_t* a = image.rgba.data() + y * stride;
            std::uint8_t* b = image.rgba.data() + ((size_t)height - 1 - y) * stride;
            std::memcpy(row.data(), a, stride);
            std::memcpy(a, b, stride);
            std::memcpy(b, row.data(), stride);
        }
    }
    if (rightToLeft) {
        for (unsigned y = 0; y < height; ++y) {
            std::uint32_t* row = reinterpret_cast<std::uint32_t*>(image.rgba.data() + (size_t)y * width * 4);
            for (unsigned x = 0; x < width / 2; ++x) {
                const std::uint32_t value = row[x];
                row[x] = row[width - 1 - x];
                row[width - 1 - x] = value;
            }
        }
    }
    return image;
}

std::vector<std::uint8_t> encodeCnv(const RgbaImage& image) {
    if (image.empty()) throw std::runtime_error("cnv: nothing to write");
    std::vector<std::uint8_t> out(17 + image.rgba.size(), 0);
    auto put32 = [&](std::size_t at, std::uint32_t value) {
        out[at] = (std::uint8_t)(value & 0xFF);
        out[at + 1] = (std::uint8_t)((value >> 8) & 0xFF);
        out[at + 2] = (std::uint8_t)((value >> 16) & 0xFF);
        out[at + 3] = (std::uint8_t)((value >> 24) & 0xFF);
    };
    out[0] = 32;   // declared bpp; the reader trusts the payload, as the shipped files force
    put32(1, image.width);
    put32(5, image.height);
    put32(9, image.width);
    put32(13, 0);   // stored, like every image the game ships
    for (std::size_t i = 0; i < image.rgba.size(); i += 4) {
        out[17 + i + 0] = image.rgba[i + 2];
        out[17 + i + 1] = image.rgba[i + 1];
        out[17 + i + 2] = image.rgba[i + 0];
        out[17 + i + 3] = image.rgba[i + 3];
    }
    return out;
}

}  // namespace psp
