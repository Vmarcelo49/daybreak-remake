#pragma once
// psp/tga.h — the tiny TGA the PSP embeds in a GMO, read into RGBA8.
//
// Every character body texture in the PSP data is a colour-mapped 8-bit TGA with a 16 or
// 24-bit palette, uncompressed. The reader still handles the true-colour and RLE forms,
// because a costume this port has not seen could use one, and a decode that refuses a
// legal TGA is a worse failure than one that reads it.
#include <cstdint>
#include <string>
#include <vector>

namespace psp {

struct RgbaImage {
    std::uint32_t              width = 0, height = 0;
    std::vector<std::uint8_t>  rgba;   // rows from the top

    bool empty() const { return rgba.empty(); }
};

// Throws std::runtime_error with the reason when the payload is not a TGA this can read.
RgbaImage decodeTga(const std::vector<std::uint8_t>& bytes);

// The remake's own texture container: u8 declared bpp, u32 field1, height, width,
// compressed size (0 = stored), then BGRA rows from the top. Written here rather than in
// the renderer so the converter owns the whole file (assets/cnv.h reads it back).
std::vector<std::uint8_t> encodeCnv(const RgbaImage& image);

}  // namespace psp
