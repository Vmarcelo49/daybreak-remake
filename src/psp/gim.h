#pragma once
// psp/gim.h — the PSP's GIM image container, decoded to RGBA8.
//
// The head atlas chrtNN.gim holds twenty pictures: the ten the fighter needs (eight face
// expressions, hair, scalp with ear) stored twice. An importer that assumes ten silently
// reads the palette records it never uses, so the reader returns every picture it finds
// and the caller picks by index.
//
// Ported from local-data/harness/psp/scripts/gim.py, which decoded these files for the
// art study. Two rules in that reference are easy to get wrong and are kept explicit
// below: a swizzled image (order 1) is stored in 16-byte x 8-row blocks rather than rows,
// and an unswizzled one has its row pitch padded to the header's alignment.
#include <cstdint>
#include <vector>

#include "psp/tga.h"

namespace psp {

// Every picture in the container, in file order. Throws std::runtime_error when the
// container or one of its images is malformed.
std::vector<RgbaImage> decodeGim(const std::vector<std::uint8_t>& bytes);

}  // namespace psp
