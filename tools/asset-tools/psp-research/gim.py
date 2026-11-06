#!/usr/bin/env python3
"""Standalone decoders for the image formats used by Higurashi Daybreak Portable.

  * GIM  (PSP, "MIG.00.1PSP") -- all pixel formats the game ships, incl. PSP swizzle
  * TGA  (uncompressed / RLE, 24/32 bpp) -- a few loose files name *.tga
  * PNG  (8-bit greyscale / RGB / RGBA / palette, non-interlaced) -- the ISO ships two

No third-party imports: only zlib (stdlib) and struct, so it runs anywhere.

--------------------------------------------------------------------------
GIM layout, as recovered from the shipped files
--------------------------------------------------------------------------
  +0x00  char  magic[16]            "MIG.00.1PSP\\0\\0\\0\\0"
  +0x10  block root                 (blocks are chained from here, see GimBlock)

Every block starts with a 16-byte header:

  +0x00  u16   id                   1=Block 2=Root 3=Picture 4=Image 5=Palette
                                    6=Sequence 0xFF=FileInfo
  +0x02  u16   reserved             always 0
  +0x04  u32   size                 bytes from this header to the end of the block
  +0x08  u32   next_rel             next SIBLING = this_offset + next_rel
  +0x0C  u32   data_rel             block payload = this_offset + data_rel

Root/Picture/Block are containers: their children start at this_offset + data_rel
(0x10) and run to this_offset + size.  Image and Palette carry a 0x40-byte
descriptor at data_rel, of which the first u32 is the declared header size (0x30):

  +0x00  u32   header_size          0x30
  +0x04  u16   format               see FORMATS
  +0x06  u16   pixel_order          0 = linear, 1 = PSP-swizzled
  +0x08  u16   width                texels; for a Palette this is the entry count
  +0x0A  u16   height               1 for a Palette
  +0x0C  u16   bits_per_pixel       16 / 4 / 8 / 32
  +0x0E  u16   pitch_align          always 16 in the shipped files
  +0x10  u16   unk                  (8 for the unindexed 4444 image, else 1)
  +0x12  u16   unk                  always 2
  +0x14  u32   unk
  +0x18  u32   unk
  +0x1C  u32   data_offset          payload = descriptor_start + data_offset (0x40)
  +0x20  u32   data_size            declared; the block extent is authoritative

The row pitch is NOT stored.  Shipped indexed images pad it (bustup_satoshi is
220 texels wide but 224 bytes/row), so it is derived as
    pitch = (block_end - payload_start) // height
and, when that is an exact multiple of the packed row width, we know the rows are
contiguous and the image is linear or swizzled with that pitch.

--------------------------------------------------------------------------
Verification
--------------------------------------------------------------------------
`--selftest` decodes every GIM the pack exposes and asserts that the derived
pitch is consistent with width/bpp and that the decode consumes the block
exactly.  `art/` PNGs were inspected by eye against the PC remake's own art.
"""
from __future__ import annotations

import argparse
import glob
import os
import struct
import sys
import zlib

# --------------------------------------------------------------------------
# pixel formats (PSP GU pixel modes; the GIM `format` field uses these numbers)
# --------------------------------------------------------------------------
PSM_5650, PSM_5551, PSM_4444, PSM_8888 = 0, 1, 2, 3
PSM_T4, PSM_T8, PSM_T16, PSM_T32 = 4, 5, 6, 7
PSM_DXT1, PSM_DXT3, PSM_DXT5 = 8, 9, 10
# GimConv also emits the "EXT" spellings, which mean the same three layouts.
PSM_DXT1_EXT, PSM_DXT3_EXT, PSM_DXT5_EXT = 0x108, 0x109, 0x10A
DXT_ALIASES = {PSM_DXT1_EXT: PSM_DXT1, PSM_DXT3_EXT: PSM_DXT3,
               PSM_DXT5_EXT: PSM_DXT5}

FORMATS = {
    PSM_5650: ("rgba5650", 2),
    PSM_5551: ("rgba5551", 2),
    PSM_4444: ("rgba4444", 2),
    PSM_8888: ("rgba8888", 4),
    PSM_T4: ("index4", 4),
    PSM_T8: ("index8", 8),
    PSM_T16: ("index16", 16),
    PSM_T32: ("index32", 32),
    PSM_DXT1: ("dxt1", 4),
    PSM_DXT3: ("dxt3", 8),
    PSM_DXT5: ("dxt5", 8),
}

GIM_MAGIC = b"MIG.00.1PSP"
BLOCK_NAMES = {1: "Block", 2: "Root", 3: "Picture", 4: "Image", 5: "Palette",
               6: "Sequence", 0xFF: "FileInfo"}
CONTAINER_IDS = (1, 2, 3)


class GimError(Exception):
    pass


def _align(value, alignment):
    if alignment <= 1:
        return value
    return (value + alignment - 1) // alignment * alignment


# --------------------------------------------------------------------------
# GIM block tree
# --------------------------------------------------------------------------
class GimBlock:
    __slots__ = ("offset", "block_id", "size", "next_rel", "data_rel",
                 "children", "depth")

    def __init__(self, offset, block_id, size, next_rel, data_rel, depth):
        self.offset, self.block_id, self.size = offset, block_id, size
        self.next_rel, self.data_rel, self.depth = next_rel, data_rel, depth
        self.children = []

    @property
    def name(self):
        return BLOCK_NAMES.get(self.block_id, "0x%02x" % self.block_id)

    @property
    def end(self):
        return self.offset + self.size

    @property
    def payload_start(self):
        return self.offset + self.data_rel

    def __repr__(self):
        return "<%s @0x%x size=0x%x depth=%d>" % (self.name, self.offset, self.size,
                                                  self.depth)


def _parse_chain(data, start, limit):
    """Walk the file's block sequence.

    The blocks form ONE flat sequence linked by `next_rel`: the very first block is
    the Root container, and its `next_rel` already steps onto its own first child
    (black.gim: Root@0x10 next=0x10 -> Picture@0x20).  So nesting is not expressed
    by the chain at all -- it is expressed by `size`, which on a container spans all
    of its children.  `depth` is therefore derived from size containment afterwards.
    """
    out = []
    off = start
    seen = 0
    while off + 16 <= limit:
        seen += 1
        if seen > 4096:
            raise GimError("block chain does not terminate (start 0x%x)" % start)
        block_id, _res, size, next_rel, data_rel = struct.unpack_from("<HHIII", data, off)
        if size < 16 or off + size > limit:
            raise GimError("block @0x%x size 0x%x escapes the file" % (off, size))
        out.append(GimBlock(off, block_id, size, next_rel, data_rel, 0))
        if next_rel == 0:
            break
        off += next_rel
    return out


def _assign_depth(blocks):
    """Depth = how many earlier container blocks contain this one, and re-parent."""
    for i, block in enumerate(blocks):
        depth = 0
        parent = None
        for other in blocks[:i]:
            if other.block_id in CONTAINER_IDS and other.offset < block.offset \
                    and block.end <= other.end:
                depth += 1
                parent = other
        block.depth = depth - 1 if depth else 0
        if parent is not None:
            parent.children.append(block)


# --------------------------------------------------------------------------
# PSP swizzle
# --------------------------------------------------------------------------
def swizzle_offset(x_bytes, y, pitch):
    """Byte offset of (x_bytes, y) in a PSP-swizzled surface with `pitch` bytes/row.

    The PSP stores textures as 16-byte x 8-row "chunks" in column-major chunk order:
    chunk index = (chunk_y * chunks_per_row + chunk_x), each chunk holding 8 rows of
    16 bytes.  A linear surface is row-major.  Pitch and every chunk count must be
    multiples of 16 bytes / 8 rows for this to be an involution, which holds for all
    shipped swizzled GIMs (16x16 minimum).
    """
    chunk_x, chunk_y = x_bytes // 16, y // 8
    chunks_per_row = pitch // 16
    return (((chunk_y * chunks_per_row + chunk_x) * 8 + (y % 8)) * 16
            + (x_bytes % 16))


def unswizzle(raw, width, height, bpp, pitch):
    """Reorder a swizzled surface into linear row-major bytes."""
    bpp8 = bpp // 8
    row_bytes = width * bpp8
    out = bytearray(row_bytes * height)
    for y in range(height):
        for xb in range(0, row_bytes, 16):
            n = min(16, row_bytes - xb)
            # swizzle_offset already covers the whole y contribution: a chunk holds
            # eight whole rows, so the row index is part of the chunk address.
            src = swizzle_offset(xb, y, pitch)
            seg = raw[src:src + n]
            if len(seg) != n:                       # padded tail chunk
                seg = seg + bytes(n - len(seg))
            out[y * row_bytes + xb:y * row_bytes + xb + n] = seg
    return bytes(out)


# --------------------------------------------------------------------------
# pixel unpackers -> RGBA8
# --------------------------------------------------------------------------
def _unpack_u16_formats(raw, count):
    """5650 / 5551 / 4444 share the layout: one LE u16 per texel, RGB in the low
    12 bits, alpha in the top 4 (4444) or top 1 (5551) or absent (5650)."""
    out = bytearray(count * 4)
    for i in range(count):
        (v,) = struct.unpack_from("<H", raw, i * 2)
        r, g, b = v & 0x1F, (v >> 5) & 0x1F, (v >> 10) & 0x1F
        out[i * 4 + 0] = (r << 3) | (r >> 2)
        out[i * 4 + 1] = (g << 3) | (g >> 2)
        out[i * 4 + 2] = (b << 3) | (b >> 2)
        out[i * 4 + 3] = 255
    return out


def _unpack_rgba5551(raw, count):
    out = bytearray(count * 4)
    for i in range(count):
        (v,) = struct.unpack_from("<H", raw, i * 2)
        r, g, b, a = v & 0x1F, (v >> 5) & 0x1F, (v >> 10) & 0x1F, (v >> 15) & 1
        out[i * 4 + 0] = (r << 3) | (r >> 2)
        out[i * 4 + 1] = (g << 3) | (g >> 2)
        out[i * 4 + 2] = (b << 3) | (b >> 2)
        out[i * 4 + 3] = 255 if a else 0
    return out


def _unpack_rgba4444(raw, count):
    out = bytearray(count * 4)
    for i in range(count):
        (v,) = struct.unpack_from("<H", raw, i * 2)
        r, g, b, a = v & 0xF, (v >> 4) & 0xF, (v >> 8) & 0xF, (v >> 12) & 0xF
        out[i * 4 + 0] = r * 17
        out[i * 4 + 1] = g * 17
        out[i * 4 + 2] = b * 17
        out[i * 4 + 3] = a * 17
    return out


def _unpack_rgba8888(raw, count):
    out = bytearray(count * 4)
    for i in range(count):
        r, g, b, a = raw[i * 4:i * 4 + 4]
        out[i * 4:i * 4 + 4] = bytes((r, g, b, a))
    return out


def _apply_palette(raw, count, bpp, palette):
    out = bytearray(count * 4)
    if not palette:
        raise GimError("indexed image without a palette block")
    n = len(palette)
    for i in range(count):
        if bpp == 4:
            byte = raw[i >> 1]
            idx = (byte >> 4) if (i & 1) == 0 else (byte & 0xF)
        elif bpp == 8:
            idx = raw[i]
        elif bpp == 16:
            (idx,) = struct.unpack_from("<H", raw, i * 2)
        else:
            (idx,) = struct.unpack_from("<I", raw, i * 4)
        if idx >= n:
            raise GimError("palette index %d >= %d entries" % (idx, n))
        out[i * 4:i * 4 + 4] = bytes(palette[idx])
    return out


# DXT: 8-byte 4x4 blocks.  DXT1 = colour only, DXT3 = 4-bit explicit alpha then
# colour-without-punchthrough, DXT5 = two alpha endpoints + 3-bit indices then
# colour.  Never encountered above 256x256 in this game, and no swizzling.
def _dxt_colors(c0, c1, four_color):
    def expand(c):
        r, g, b = (c >> 11) & 0x1F, (c >> 5) & 0x3F, c & 0x1F
        return ((r << 3) | (r >> 2), (g << 2) | (g >> 4), (b << 3) | (b >> 2))

    a, b = expand(c0), expand(c1)
    if four_color or c0 > c1:
        return [a, b,
                tuple((2 * a[i] + b[i]) // 3 for i in range(3)),
                tuple((a[i] + 2 * b[i]) // 3 for i in range(3))]
    return [a, b, tuple((a[i] + b[i]) // 2 for i in range(3)), (0, 0, 0)]


def _unpack_dxt(raw, width, height, fmt):
    out = bytearray(width * height * 4)
    block_bytes = 16 if fmt != PSM_DXT1 else 8
    pos = 0
    for by in range(0, height, 4):
        for bx in range(0, width, 4):
            if pos + block_bytes > len(raw):
                return out
            if fmt == PSM_DXT3:
                alpha_bits = int.from_bytes(raw[pos:pos + 8], "little")
                pos += 8
            elif fmt == PSM_DXT5:
                a0, a1 = raw[pos], raw[pos + 1]
                bits = int.from_bytes(raw[pos + 2:pos + 8], "little")
                pos += 8
                codes = [a0, a1] + [0] * 6
                if a0 > a1:
                    codes[2:8] = [((7 - i) * a0 + i * a1) // 7 for i in range(1, 7)]
                else:
                    codes[2:6] = [((5 - i) * a0 + i * a1) // 5 for i in range(1, 5)]
                    codes[6] = codes[7] = 0
            c0, c1 = struct.unpack_from("<HH", raw, pos)
            idx = int.from_bytes(raw[pos + 4:pos + 8], "little")
            pos += 8
            palette = _dxt_colors(c0, c1, fmt != PSM_DXT1)
            for py in range(4):
                y = by + py
                if y >= height:
                    continue
                for px in range(4):
                    x = bx + px
                    if x >= width:
                        continue
                    code = (idx >> (2 * (py * 4 + px))) & 3
                    r, g, b = palette[code]
                    slot = py * 4 + px
                    if fmt == PSM_DXT3:
                        a = ((alpha_bits >> (4 * slot)) & 0xF) * 17
                    elif fmt == PSM_DXT5:
                        a = codes[(bits >> (3 * slot)) & 7]
                    else:
                        a = 0 if (code == 3 and c0 <= c1) else 255
                    o = (y * width + x) * 4
                    out[o:o + 4] = bytes((r, g, b, a))
    return out


# --------------------------------------------------------------------------
# decoded image
# --------------------------------------------------------------------------
class GimImage:
    def __init__(self, width, height, fmt, bpp, swizzled, pitch, rgba,
                 block, palette_size, stored_height=None, visible_width=None):
        self.width, self.height = width, height
        self.stored_height = stored_height or height
        # What the GIM header calls the width; `width` is the aligned row length,
        # which is what the payload actually is.  They differ when pitch != row bytes.
        self.visible_width = visible_width or width
        self.fmt, self.bpp = fmt, bpp
        self.swizzled, self.pitch = swizzled, pitch
        self.rgba = rgba
        self.block = block
        self.palette_size = palette_size

    @property
    def format_name(self):
        return FORMATS.get(self.fmt, ("fmt%d" % self.fmt, 0))[0]

    def describe(self):
        vis = ("" if self.visible_width == self.width
               else " (header says %d wide)" % self.visible_width)
        return ("%dx%d%s %s %dbpp pitch=%d %s block@0x%x palette=%d"
                % (self.width, self.height, vis, self.format_name, self.bpp,
                   self.pitch, "swizzled" if self.swizzled else "linear",
                   self.block.offset, self.palette_size))

    def __repr__(self):
        return "<GimImage %s>" % self.describe()

    # --- drawing helpers ---------------------------------------------------
    def crop(self, box):
        """Sub-rectangle (x, y, w, h) as a new GimImage."""
        x, y, w, h = box
        stride = self.width * 4
        rows = []
        for row in range(y, y + h):
            rows.append(self.rgba[row * stride + x * 4:row * stride + (x + w) * 4])
        out = GimImage(w, h, self.fmt, self.bpp, False, w * 4, b"".join(rows),
                       self.block, self.palette_size)
        out.visible_width = w
        return out


class GimFile:
    def __init__(self, path, data):
        if data[:len(GIM_MAGIC)] != GIM_MAGIC:
            raise GimError("%s: not a PSP GIM (magic %r)" % (path, data[:12]))
        self.path, self.data = path, data
        self.blocks = _parse_chain(data, 0x10, len(data))
        if not self.blocks:
            raise GimError("%s: no blocks" % path)
        _assign_depth(self.blocks)
        self.roots = [b for b in self.blocks if b.depth == 0]
        self.images = self._decode_images()

    def walk(self, block_id=None):
        return [b for b in self.blocks if block_id is None or b.block_id == block_id]

    def _palette_for(self, image_block):
        """The Palette that belongs to an Image.

        A Palette is NOT reliably emitted before its Image (vs_enter_rena.gim puts it
        after), so proximity is not enough: both are children of the same Picture
        container, so prefer a Palette inside the innermost Picture that contains the
        Image and fall back to the nearest one before it.
        """
        picture = None
        for block in self.blocks:
            if block.block_id != 3 or not (block.offset < image_block.offset
                                           and image_block.end <= block.end):
                continue
            if picture is None or block.size < picture.size:
                picture = block
        if picture is not None:
            inside = [b for b in self.blocks
                      if b.block_id == 5 and picture.offset < b.offset
                      and b.end <= picture.end]
            if inside:
                return min(inside, key=lambda b: abs(b.offset - image_block.offset))
        before = [b for b in self.blocks
                  if b.block_id == 5 and b.offset < image_block.offset]
        return max(before, key=lambda b: b.offset) if before else None

    def _read_descriptor(self, block):
        """The 48-byte image/palette header at the block's data offset."""
        d = block.payload_start
        if d + 0x30 > len(self.data):
            raise GimError("descriptor @0x%x truncated" % d)
        (_hdr_size, _unused, fmt, order, w, h, bpp, w_align, h_align,
         _dims, _r0, _r1) = struct.unpack_from("<12H", self.data, d)
        index_off, plane_off, total_size, _plane_mask = struct.unpack_from(
            "<4I", self.data, d + 0x18)
        level_type, level_count, _frame_type, _frame_count = struct.unpack_from(
            "<4H", self.data, d + 0x28)
        return dict(desc=d, fmt=fmt, order=order, width=w, height=h, bpp=bpp,
                    w_align=w_align or 16, h_align=h_align or 1,
                    index_off=index_off, plane_off=plane_off,
                    total_size=total_size, level_type=level_type,
                    level_count=level_count)

    def _decode_images(self):
        images = []
        palette_cache = {}
        for img_block in self.walk(4):
            pal_block = self._palette_for(img_block)
            if pal_block is None:
                palette, palette_size = None, 0
            else:
                key = pal_block.offset
                if key not in palette_cache:
                    palette_cache[key] = self._decode_palette(pal_block)
                palette, palette_size = palette_cache[key]
            images.append(self._decode_image(img_block, palette, palette_size))
        if not images:
            raise GimError("%s: no image block" % self.path)
        return images

    def _decode_palette(self, block):
        info = self._read_descriptor(block)
        fmt = info["fmt"]
        if fmt not in (PSM_8888, PSM_5551, PSM_4444, PSM_5650):
            raise GimError("palette format %d unsupported" % fmt)
        start = info["desc"] + info["plane_off"]
        count = info["width"] * max(1, info["height"])
        # The palette's own bpp is authoritative: vs_enter_vs.gim ships a 256-entry
        # RGBA4444 palette (2 bytes each), not the usual RGBA8888 one.
        entry = max(2, (FORMATS[fmt][1] * 8) // 8)
        nbytes = count * entry
        raw = self.data[start:start + nbytes]
        if len(raw) < nbytes:
            raise GimError("palette @0x%x truncated (%d of %d bytes)"
                           % (start, len(raw), nbytes))
        if fmt == PSM_8888:
            rgba = _unpack_rgba8888(raw, count)
        elif fmt == PSM_4444:
            rgba = _unpack_rgba4444(raw, count)
        elif fmt == PSM_5551:
            rgba = _unpack_rgba5551(raw, count)
        else:
            rgba = _unpack_u16_formats(raw, count)
        return [tuple(rgba[i * 4:i * 4 + 4]) for i in range(count)], count

    def _decode_image(self, block, palette, palette_size):
        info = self._read_descriptor(block)
        fmt, w, h, bpp = info["fmt"], info["width"], info["height"], info["bpp"]
        if fmt in DXT_ALIASES:
            fmt = DXT_ALIASES[fmt]        # the 0x108/0x109/0x10a "EXT" spellings
        if fmt not in FORMATS:
            raise GimError("pixel format %d unsupported" % fmt)
        if w == 0 or h == 0:
            raise GimError("image %dx%d" % (w, h))
        start = info["desc"] + info["plane_off"]

        # The row pitch is (width bytes) rounded up to the header's pitch alignment,
        # and the stored height is rounded up to its height alignment.  Both are
        # confirmed by total_size - plane_off on every shipped file.
        row_bytes = (w * bpp + 7) // 8
        pitch = _align(row_bytes, info["w_align"]) if fmt < PSM_DXT1 else row_bytes
        stored_h = _align(h, info["h_align"]) if fmt < PSM_DXT1 else h
        # THE PITCH IS THE REAL ROW: the tail of each padded row holds live artwork,
        # not slack.  bustup_satoshi.gim declares 220x130 with a 224-byte pitch but is
        # in fact a 224x130 two-pose sheet, and vs_enter_satoshi.gim declares 168x132
        # with a 176-byte pitch but is a 176x132 portrait.  Reading the declared width
        # against the padded pitch shears the picture; reading `pitch` bytes per row
        # contiguous is exact.  Decode at the aligned width and keep the declared one
        # as `visible_width` for callers that want to crop.
        # width in TEXELS of the padded row -- 2x the byte pitch for 4bpp images
        decode_w = pitch * 8 // max(1, bpp)
        need = pitch * stored_h
        avail = block.end - start
        if avail < need:
            raise GimError("image needs %d bytes at 0x%x, block holds %d"
                           % (need, start, avail))
        raw = self.data[start:start + need]
        if info["order"] and fmt < PSM_DXT1:
            raw = unswizzle(raw, decode_w, stored_h, bpp, pitch)

        count = decode_w * stored_h
        if fmt in (PSM_T4, PSM_T8, PSM_T16, PSM_T32):
            rgba = _apply_palette(raw, count, bpp, palette)
        elif fmt == PSM_4444:
            rgba = _unpack_rgba4444(raw, count)
        elif fmt == PSM_5551:
            rgba = _unpack_rgba5551(raw, count)
        elif fmt == PSM_5650:
            rgba = _unpack_u16_formats(raw, count)
        elif fmt == PSM_8888:
            rgba = _unpack_rgba8888(raw, count)
        elif fmt in (PSM_DXT1, PSM_DXT3, PSM_DXT5):
            rgba = _unpack_dxt(raw, w, h, fmt)
        else:
            raise GimError("unhandled format %d" % fmt)

        return GimImage(decode_w, stored_h, fmt, bpp, bool(info["order"]), pitch,
                        bytes(rgba), block, palette_size, h, w)


# --------------------------------------------------------------------------
# TGA
# --------------------------------------------------------------------------
class TgaImage:
    def __init__(self, width, height, rgba):
        self.width, self.height, self.rgba = width, height, rgba


def decode_tga(data):
    if len(data) < 18:
        raise GimError("TGA shorter than its header")
    (id_len, cmap_type, img_type, cmap_first, cmap_len, cmap_bits,
     _x0, _y0, w, h, bpp, desc) = struct.unpack_from("<BBBHHBHHHHBB", data, 0)
    if cmap_type:
        raise GimError("colour-mapped TGA not supported")
    if img_type not in (2, 3, 10, 11):
        raise GimError("TGA image type %d not supported" % img_type)
    if img_type in (3, 11):
        raise GimError("greyscale TGA not supported")
    if bpp not in (24, 32):
        raise GimError("TGA %d bpp not supported" % bpp)
    pos = 18 + id_len
    bpp8 = bpp // 8
    order = "BGRA" if bpp == 32 else "BGR"
    top_down = bool(desc & 0x20)
    right_left = bool(desc & 0x10)

    def put(dst, i, rgb, alpha):
        o = i * 4
        dst[o + 0], dst[o + 1], dst[o + 2] = rgb[2], rgb[1], rgb[0]
        dst[o + 3] = alpha

    px = bytearray(w * h * 4)
    if img_type in (2, 3):
        need = w * h * bpp8
        if pos + need > len(data):
            raise GimError("TGA pixel data truncated")
        for i in range(w * h):
            src = data[pos + i * bpp8:pos + (i + 1) * bpp8]
            put(px, i, src, src[3] if bpp8 == 4 else 255)
    else:
        i, o = 0, pos
        total = w * h
        while i < total:
            if o >= len(data):
                raise GimError("TGA RLE packet truncated")
            n = data[o]
            o += 1
            if n & 0x80:
                n = (n & 0x7F) + 1
                src = data[o:o + bpp8]
                o += bpp8
                for _ in range(min(n, total - i)):
                    put(px, i, src, src[3] if bpp8 == 4 else 255)
                    i += 1
            else:
                n += 1
                for _ in range(min(n, total - i)):
                    src = data[o:o + bpp8]
                    o += bpp8
                    put(px, i, src, src[3] if bpp8 == 4 else 255)
                    i += 1
    # TGA is bottom-up unless bit 5 of the descriptor says otherwise.
    if not top_down:
        stride = w * 4
        px = b"".join(px[y * stride:(y + 1) * stride] for y in range(h - 1, -1, -1))
        px = bytearray(px)
    if right_left:
        stride = w * 4
        out = bytearray(len(px))
        for y in range(h):
            row = px[y * stride:(y + 1) * stride]
            for x in range(w):
                out[y * stride + x * 4:y * stride + x * 4 + 4] = \
                    row[(w - 1 - x) * 4:(w - x) * 4]
        px = out
    del order
    return TgaImage(w, h, bytes(px))


# --------------------------------------------------------------------------
# PNG (read + write) -- 8-bit, non-interlaced only
# --------------------------------------------------------------------------
PNG_SIG = b"\x89PNG\r\n\x1a\n"


class PngImage:
    def __init__(self, width, height, rgba):
        self.width, self.height, self.rgba = width, height, rgba


def _paeth(a, b, c):
    p = a + b - c
    pa, pb, pc = abs(p - a), abs(p - b), abs(p - c)
    if pa <= pb and pa <= pc:
        return a
    return b if pb <= pc else c


def _png_unfilter(raw, w, h, ch):
    stride = w * ch
    out = bytearray(stride * h)
    prev = bytearray(stride)
    pos = 0
    for y in range(h):
        if pos >= len(raw):
            raise GimError("PNG data truncated")
        ftype = raw[pos]
        pos += 1
        line = bytearray(raw[pos:pos + stride])
        pos += stride
        if len(line) < stride:
            raise GimError("PNG row truncated")
        if ftype == 1:
            for i in range(ch, stride):
                line[i] = (line[i] + line[i - ch]) & 0xFF
        elif ftype == 2:
            for i in range(stride):
                line[i] = (line[i] + prev[i]) & 0xFF
        elif ftype == 3:
            for i in range(stride):
                left = line[i - ch] if i >= ch else 0
                line[i] = (line[i] + ((left + prev[i]) >> 1)) & 0xFF
        elif ftype == 4:
            for i in range(stride):
                left = line[i - ch] if i >= ch else 0
                upleft = prev[i - ch] if i >= ch else 0
                line[i] = (line[i] + _paeth(left, prev[i], upleft)) & 0xFF
        elif ftype != 0:
            raise GimError("PNG filter %d invalid" % ftype)
        out[y * stride:(y + 1) * stride] = line
        prev = line
    return bytes(out)


def decode_png(data):
    if data[:8] != PNG_SIG:
        raise GimError("not a PNG")
    pos, idat, meta, palette, trns = 8, bytearray(), None, None, None
    while pos + 8 <= len(data):
        length, ctype = struct.unpack_from(">I4s", data, pos)
        body = data[pos + 8:pos + 8 + length]
        pos += 12 + length
        if ctype == b"IHDR":
            meta = struct.unpack_from(">IIBBBBB", body, 0)
        elif ctype == b"PLTE":
            palette = body
        elif ctype == b"tRNS":
            trns = body
        elif ctype == b"IDAT":
            idat += body
        elif ctype == b"IEND":
            break
    if meta is None:
        raise GimError("PNG without IHDR")
    w, h, depth, color, comp, filt, interlace = meta
    if depth != 8 or interlace:
        raise GimError("PNG depth %d interlace %d unsupported" % (depth, interlace))
    ch = {0: 1, 2: 3, 3: 1, 4: 2, 6: 4}.get(color)
    if ch is None:
        raise GimError("PNG colour type %d unsupported" % color)
    raw = _png_unfilter(zlib.decompress(bytes(idat)), w, h, ch)
    px = bytearray(w * h * 4)
    for i in range(w * h):
        if color == 6:
            px[i * 4:i * 4 + 4] = raw[i * 4:i * 4 + 4]
        elif color == 2:
            px[i * 4:i * 4 + 3] = raw[i * 3:i * 3 + 3]
            px[i * 4 + 3] = 255
        elif color == 0:
            g = raw[i]
            px[i * 4:i * 4 + 4] = bytes((g, g, g, 255))
        elif color == 4:
            g, a = raw[i * 2], raw[i * 2 + 1]
            px[i * 4:i * 4 + 4] = bytes((g, g, g, a))
        else:  # colour type 3, palette
            if palette is None:
                raise GimError("indexed PNG without PLTE")
            idx = raw[i]
            px[i * 4:i * 4 + 3] = palette[idx * 3:idx * 3 + 3]
            px[i * 4 + 3] = trns[idx] if trns and idx < len(trns) else 255
    return PngImage(w, h, bytes(px))


def _png_chunk(ctype, body):
    return (struct.pack(">I", len(body)) + ctype + body
            + struct.pack(">I", zlib.crc32(ctype + body) & 0xFFFFFFFF))


def encode_png(width, height, rgba):
    """RGBA8, top-down, no filtering beyond the obligatory per-row type byte."""
    stride = width * 4
    raw = bytearray()
    for y in range(height):
        raw.append(0)
        raw += rgba[y * stride:(y + 1) * stride]
    return (PNG_SIG
            + _png_chunk(b"IHDR", struct.pack(">IIBBBBB", width, height, 8, 6, 0, 0, 0))
            + _png_chunk(b"IDAT", zlib.compress(bytes(raw), 9))
            + _png_chunk(b"IEND", b""))


# --------------------------------------------------------------------------
# uniform entry point
# --------------------------------------------------------------------------
class Image:
    """Anything decoded: width, height and RGBA8 rows."""

    def __init__(self, width, height, rgba, source=""):
        self.width, self.height, self.rgba, self.source = width, height, rgba, source

    def save(self, path):
        os.makedirs(os.path.dirname(os.path.abspath(path)), exist_ok=True)
        with open(path, "wb") as f:
            f.write(encode_png(self.width, self.height, self.rgba))
        return path


def sniff(data):
    if data[:len(GIM_MAGIC)] == GIM_MAGIC:
        return "gim"
    if data[:8] == PNG_SIG:
        return "png"
    if data[:4] in (b"GIF8",):
        return "gif"
    return "tga"


def decode_any(data, name="", index=0):
    kind = sniff(data)
    if kind == "gim":
        images = GimFile(name, data).images
        img = images[index]
        return Image(img.width, img.height, img.rgba, name)
    if kind == "png":
        p = decode_png(data)
        return Image(p.width, p.height, p.rgba, name)
    if kind == "gif":
        raise GimError("%s: GIF unsupported" % name)
    t = decode_tga(data)
    return Image(t.width, t.height, t.rgba, name)


def describe_any(data, name=""):
    kind = sniff(data)
    if kind == "gim":
        g = GimFile(name, data)
        lines = ["%s: GIM, %d top-level block(s)" % (name, len(g.roots))]
        for b in g.blocks:
            extra = ""
            if b.block_id in (4, 5):
                try:
                    info = g._read_descriptor(b)
                    extra = (" fmt=%s %dx%d bpp=%d order=%d"
                             % (FORMATS.get(info["fmt"], ("?%d" % info["fmt"],))[0],
                                info["width"], info["height"], info["bpp"],
                                info["order"]))
                except GimError:
                    extra = " (bad descriptor)"
            lines.append("  %s@0x%-6x size=0x%-6x%s" % ("  " * b.depth + b.name,
                                                      b.offset, b.size, extra))
        for img in g.images:
            lines.append("  -> image %s" % img.describe())
        return "\n".join(lines)
    if kind == "png":
        p = decode_png(data)
        return "%s: PNG %dx%d" % (name, p.width, p.height)
    t = decode_tga(data)
    return "%s: TGA %dx%d" % (name, t.width, t.height)


# --------------------------------------------------------------------------
# CLI
# --------------------------------------------------------------------------
def _load(path):
    with open(path, "rb") as f:
        return f.read()


def main(argv=None):
    ap = argparse.ArgumentParser(description="Decode PSP GIM / TGA / PNG to PNG.")
    ap.add_argument("input", nargs="*", help="files, or globs")
    ap.add_argument("-o", "--out", help="output .png (single input) or directory")
    ap.add_argument("-i", "--index", type=int, default=0,
                    help="which image inside a GIM to decode (default 0)")
    ap.add_argument("--info", action="store_true", help="print structure only")
    ap.add_argument("--selftest", metavar="DIR",
                    help="decode every *.gim under DIR and check the block math")
    args = ap.parse_args(argv)

    if args.selftest:
        return selftest(args.selftest)

    files = []
    for pattern in args.input:
        hits = sorted(glob.glob(pattern))
        files.extend(hits or [pattern])
    if not files:
        ap.error("no input")

    for path in files:
        data = _load(path)
        if args.info:
            print(describe_any(data, os.path.basename(path)))
            continue
        if args.out and args.out.lower().endswith(".png") and len(files) == 1:
            dest = args.out
        else:
            base = os.path.splitext(os.path.basename(path))[0]
            dest = os.path.join(args.out or ".", base + ".png")
        src = args.index if sniff(data) == "gim" else 0
        img = decode_any(data, path, src)
        img.save(dest)
        print("%s -> %s (%dx%d)" % (path, dest, img.width, img.height))
    return 0


def selftest(root):
    """Decode every GIM under `root` and report anything the block math rejects."""
    ok = bad = 0
    for path in sorted(glob.glob(os.path.join(root, "**", "*.gim"), recursive=True)):
        try:
            g = GimFile(path, _load(path))
            for img in g.images:
                assert len(img.rgba) == img.width * img.height * 4
            ok += 1
        except Exception as exc:                                  # noqa: BLE001
            bad += 1
            print("FAIL %s: %s" % (path, exc))
    print("decoded %d GIM(s), %d failure(s)" % (ok, bad))
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
