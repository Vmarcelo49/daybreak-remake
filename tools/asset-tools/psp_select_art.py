#!/usr/bin/env python3
"""Build the select and VS sheets the remake reads for the three PSP fighters.

WHAT THIS IS
    The reference generator behind docs/psp/FRONTEND-ART.md. It reads the 2D art out of the
    user's own Higurashi Daybreak Portable ISO (or an already-extracted copy of its pack), crops
    and repacks it into the remake's own sheet layout, and writes the result under `psp-data/` at
    the product's own paths. Nothing it reads or writes is tracked: the art belongs to the rights
    holders, the paths belong to this repository.

    Track A's extractor (`daybreak --extract-psp <iso>`) is expected to produce the same files;
    this script is what defines them until it does, and what the art contract in
    docs/psp/FRONTEND-ART.md §2 describes.

WHAT IT WRITES  (roster indices 16 Satoshi, 17 Miyoko, 18 Okonogi)

    <out>/data/select/NN.cnv        256x256   one portrait, pivot bottom-centre
    <out>/data/select/iNN.cnv       256x256   3x2 grid of 80x128 chibi cells
    <out>/data/select/cosNN.cnv     256x384   3x3 grid of 80x128 costume cells
    <out>/data/select/wNN.cnv       512x256   4 rows of 256x64, one per weapon slot a..d

    Every file is a CNV image (`src/assets/cnv.h`): a 17-byte header — u8 bpp, u32 field1, u32
    height, u32 width, u32 compressed size (0) — then width*height BGRA, top row first. The
    product decodes exactly that, so no PNG path is involved and no texture pack is needed.

WHERE THE PIXELS COME FROM

    gra/gim/select/vs_enter_<name>.gim      176x132   the portrait (one pose)
    gra/gim/select/icon_on.gim              192x240   4x5 grid of 48x48 head icons, 19 used

    The PSP has no chibi body, no per-costume picture and no per-weapon picture: its own select
    screen is a list of text names next to those head icons. So the chibi and costume cells are
    the character's own PSP roster icon standing on a procedurally drawn floor tile — the diamond
    floor the PC's own i/cos sheets have — and the weapon rows are lettered place-holders. Each
    of those is stated where it is drawn, below, and in the contract doc.

USAGE

    python3 tools/asset-tools/psp_select_art.py --iso=<Higurashi PSP.iso> [--out=psp-data]
    python3 tools/asset-tools/psp_select_art.py --pack=<PSP_GAME/USRDIR/_pack/gzpack.pck>
    python3 tools/asset-tools/psp_select_art.py --dump=<dir with gra/gim/select/*.gim>

    --preview=<dir>  also write PNG previews of every sheet (for the eye, never for the product)
    --only=NN        build one roster index only (16, 17 or 18)

PROVENANCE
    The pack layout and the GIM decoder are the ones the PSP art study recovered:
    `local-data/harness/psp/notes/art.md` §1 and §3 (the padded pitch is the real row, the
    palette is not reliably before its image, name_hash is crc32(path, 0xFFFFFFFF)). The decoder
    here is the subset those notes needed — index4/index8, 4444/5551/5650/8888 — and it reports
    any other format instead of guessing. DXT is not needed by any select-family sheet.
"""

from __future__ import annotations

import argparse
import gzip
import os
import struct
import sys
import zlib

# --------------------------------------------------------------------------------------------
# The contract: roster index -> the art that names it, and how many costume cells it needs.
# The three come from the PSP build's own chr17/chr18/chr19 (docs/PSP-CHARACTERS-WORKLOG.md).
# --------------------------------------------------------------------------------------------
PORTRAIT_RECT = (256, 256)     # data/select/NN.cnv
CHIBI_RECT = (256, 256)        # data/select/iNN.cnv
COSTUME_RECT = (256, 384)      # data/select/cosNN.cnv
WEAPON_RECT = (512, 256)       # data/select/wNN.cnv
CHIBI_CELL = (80, 128)         # every cell family uses the same 80x128 cell
WEAPONS_PER_SHEET = WEAPON_RECT[1] // 64

CHARACTERS = (
    # roster index, pack name, weapon id of slot a, costume cells
    (16, "satoshi", 101, 5),
    (17, "miyoko", 105, 7),
    (18, "okonogi", 109, 3),
)

SELECT_DIR = "gra/gim/select/"
ICON_SHEET = SELECT_DIR + "icon_on.gim"
ICON_GRID = (4, 5)             # 4x5 of 48x48, packed in roster order (art.md §2/§6)
ICON_CELL = 48


class ArtError(Exception):
    pass


# ============================================================================================
# gzpack.pck — u32 count, then count rows of {u32 crc32(path), u32 csize, u32 offset, u32 unk}
# ============================================================================================
def pack_name_hash(path):
    """The pack's key: zlib's crc32 seeded with 0xFFFFFFFF over the path, no leading slash."""
    return zlib.crc32(path.encode("ascii"), 0xFFFFFFFF)


class Pack:
    """Random access to gzpack.pck, from the ISO itself or from an extracted copy."""

    def __init__(self, read_at, size):
        self._read_at = read_at
        header = read_at(0, 4)
        if len(header) < 4:
            raise ArtError("pack: shorter than its own count field")
        count = struct.unpack("<I", header)[0]
        if count == 0 or 4 + count * 16 > size:
            raise ArtError("pack: %d rows do not fit in %d bytes" % (count, size))
        self.rows = {}
        table = read_at(4, count * 16)
        for i in range(count):
            name_hash, csize, offset, _unk = struct.unpack_from("<4I", table, i * 16)
            self.rows[name_hash] = (csize, offset)

    def has(self, path):
        return pack_name_hash(path) in self.rows

    def get(self, path):
        row = self.rows.get(pack_name_hash(path))
        if row is None:
            return None
        csize, offset = row
        blob = self._read_at(offset, csize)
        if blob[:2] == b"\x1f\x8b":
            return gzip.decompress(blob)
        return blob


def pack_from_file(path):
    size = os.path.getsize(path)

    def read_at(offset, length):
        with open(path, "rb") as stream:
            stream.seek(offset)
            return stream.read(length)

    return Pack(read_at, size)


# ============================================================================================
# ISO 9660 — just enough to find the pack inside the disc image
# ============================================================================================
ISO_SECTOR = 2048
PACK_PATH = ("PSP_GAME", "USRDIR", "_pack", "GZPACK.PCK")


def iso_find(read_at, size, path):
    """(offset, size) of one file by ISO 9660 name, case-insensitive, version suffix ignored."""
    pvd = read_at(16 * ISO_SECTOR, ISO_SECTOR)
    if pvd[1:6] != b"CD001":
        raise ArtError("iso: no ISO 9660 primary volume descriptor at sector 16")
    extent, length = _iso_record_span(pvd[156:])

    def walk(lba, data_length, depth):
        data = read_at(lba * ISO_SECTOR, data_length)
        pos = 0
        while pos < len(data):
            record = data[pos]
            if record == 0:                       # padding to the next sector
                pos = (pos // ISO_SECTOR + 1) * ISO_SECTOR
                continue
            entry = data[pos:pos + record]
            name_len = entry[32]
            name = entry[33:33 + name_len].decode("latin-1")
            entry_extent, entry_length = _iso_record_span(entry)
            pos += record
            if name in (".", ".."):
                continue
            stem = name.split(";")[0].upper()      # "GZPACK.PCK;1" is the usual spelling
            if stem == path[depth].upper():
                if depth + 1 == len(path):
                    return entry_extent * ISO_SECTOR, entry_length
                found = walk(entry_extent, entry_length, depth + 1)
                if found:
                    return found
        return None

    found = walk(extent, length, 0)
    if not found:
        raise ArtError("iso: %s is not in the image" % "/".join(path))
    return found


def _iso_record_span(record):
    extent = struct.unpack_from("<I", record, 2)[0]
    length = struct.unpack_from("<I", record, 10)[0]
    return extent, length


def pack_from_iso(path):
    size = os.path.getsize(path)

    def read_at(offset, length):
        with open(path, "rb") as stream:
            stream.seek(offset)
            return stream.read(length)

    offset, length = iso_find(read_at, size, PACK_PATH)

    def read_pack(relative, count):
        return read_at(offset + relative, count)

    return Pack(read_pack, length)


# ============================================================================================
# GIM — the PSP image container (art.md §3). Subset: the formats the select family ships.
# ============================================================================================
GIM_MAGIC = b"MIG.00.1PSP"
PSM_5650, PSM_5551, PSM_4444, PSM_8888 = 0, 1, 2, 3
PSM_T4, PSM_T8, PSM_T16, PSM_T32 = 4, 5, 6, 7
PSM_BYTES = {PSM_5650: 2, PSM_5551: 2, PSM_4444: 2, PSM_8888: 4,
             PSM_T4: 0, PSM_T8: 1, PSM_T16: 2, PSM_T32: 4}
PSM_BITS = {PSM_5650: 16, PSM_5551: 16, PSM_4444: 16, PSM_8888: 32,
            PSM_T4: 4, PSM_T8: 8, PSM_T16: 16, PSM_T32: 32}


def _align(value, alignment):
    if alignment <= 1:
        return value
    return (value + alignment - 1) // alignment * alignment


class GimBlock:
    __slots__ = ("offset", "block_id", "size", "data_rel", "depth")

    def __init__(self, offset, block_id, size, data_rel):
        self.offset, self.block_id, self.size, self.data_rel = offset, block_id, size, data_rel
        self.depth = 0

    @property
    def end(self):
        return self.offset + self.size

    @property
    def payload(self):
        return self.offset + self.data_rel


class GimImage:
    def __init__(self, width, height, rgba):
        self.width, self.height, self.rgba = width, height, rgba

    def crop(self, box):
        x, y, w, h = box
        out = bytearray(w * h * 4)
        for row in range(h):
            src = ((y + row) * self.width + x) * 4
            out[row * w * 4:(row + 1) * w * 4] = self.rgba[src:src + w * 4]
        return GimImage(w, h, bytes(out))


def _parse_blocks(data):
    """The file's one flat block chain; nesting is expressed by each container's size."""
    blocks = []
    offset = 0x10
    while offset + 16 <= len(data):
        block_id, _res, size, next_rel, data_rel = struct.unpack_from("<HHIII", data, offset)
        if size < 16 or offset + size > len(data):
            raise ArtError("gim: block @0x%x size 0x%x escapes the file" % (offset, size))
        block = GimBlock(offset, block_id, size, data_rel)
        # Depth: how many earlier containers enclose this block.
        block.depth = sum(1 for other in blocks
                          if other.block_id in (1, 2, 3) and other.offset < offset
                          and block.end <= other.end)
        blocks.append(block)
        if next_rel == 0:
            break
        offset += next_rel
    return blocks


def _unswizzle(raw, width, height, bpp, pitch):
    """PSP swizzle: 16-byte x 8-row chunks in column-major chunk order."""
    bytes_per_texel = max(1, bpp // 8)
    row_bytes = width * bytes_per_texel
    out = bytearray(row_bytes * height)
    chunks_per_row = pitch // 16
    for y in range(height):
        for xb in range(0, row_bytes, 16):
            take = min(16, row_bytes - xb)
            chunk = ((y // 8) * chunks_per_row + xb // 16) * 8 * 16 + (y % 8) * 16 + (xb % 16)
            segment = raw[chunk:chunk + take]
            if len(segment) != take:
                segment = segment + bytes(take - len(segment))
            out[y * row_bytes + xb:y * row_bytes + xb + take] = segment
    return bytes(out)


def _unpack_u16(raw, count, kind):
    out = bytearray(count * 4)
    for i in range(count):
        value = struct.unpack_from("<H", raw, i * 2)[0]
        if kind == PSM_4444:
            r, g, b, a = value & 0xF, (value >> 4) & 0xF, (value >> 8) & 0xF, (value >> 12) & 0xF
            out[i * 4:i * 4 + 4] = bytes((r * 17, g * 17, b * 17, a * 17))
        elif kind == PSM_5551:
            r, g, b = value & 0x1F, (value >> 5) & 0x1F, (value >> 10) & 0x1F
            a = 255 if (value >> 15) & 1 else 0
            out[i * 4:i * 4 + 4] = bytes(((r << 3) | (r >> 2), (g << 3) | (g >> 2),
                                          (b << 3) | (b >> 2), a))
        else:                                   # 5650: no alpha channel at all
            r, g, b = value & 0x1F, (value >> 5) & 0x1F, (value >> 10) & 0x1F
            out[i * 4:i * 4 + 4] = bytes(((r << 3) | (r >> 2), (g << 3) | (g >> 2),
                                          (b << 3) | (b >> 2), 255))
    return out


def _unpack_indexed(raw, count, bpp, palette):
    if not palette:
        raise ArtError("gim: indexed image without a palette")
    out = bytearray(count * 4)
    entries = len(palette) // 4
    for i in range(count):
        if bpp == 4:
            byte = raw[i >> 1]
            index = (byte >> 4) if (i & 1) == 0 else (byte & 0xF)
        elif bpp == 8:
            index = raw[i]
        elif bpp == 16:
            index = struct.unpack_from("<H", raw, i * 2)[0]
        else:
            index = struct.unpack_from("<I", raw, i * 4)[0]
        if index >= entries:
            raise ArtError("gim: palette index %d >= %d entries" % (index, entries))
        out[i * 4:i * 4 + 4] = palette[index * 4:index * 4 + 4]
    return out


def _descriptor(data, block):
    start = block.payload
    if start + 0x30 > len(data):
        raise ArtError("gim: descriptor @0x%x truncated" % start)
    (_size, _unused, fmt, order, width, height, bpp, width_align, height_align,
     _dims, _r0, _r1) = struct.unpack_from("<12H", data, start)
    plane_off = struct.unpack_from("<I", data, start + 0x1C)[0]
    return dict(start=start, fmt=fmt, order=order, width=width, height=height, bpp=bpp,
                width_align=width_align or 16, height_align=height_align or 1,
                plane=plane_off)


def _palette_of(blocks, image_block, data):
    """The Palette that belongs to an Image: it is not reliably stored before it (art.md §3)."""
    picture = None
    for block in blocks:
        if block.block_id != 3 or not (block.offset < image_block.offset
                                       and image_block.end <= block.end):
            continue
        if picture is None or block.size < picture.size:
            picture = block
    inside = [b for b in blocks if b.block_id == 5 and picture is not None
              and picture.offset < b.offset and b.end <= picture.end]
    if inside:
        return min(inside, key=lambda b: abs(b.offset - image_block.offset))
    before = [b for b in blocks if b.block_id == 5 and b.offset < image_block.offset]
    return max(before, key=lambda b: b.offset) if before else None


def decode_palette(blocks, image_block, data):
    block = _palette_of(blocks, image_block, data)
    if block is None:
        return None
    info = _descriptor(data, block)
    fmt = info["fmt"]
    if fmt not in PSM_BYTES or fmt in (PSM_T4, PSM_T8, PSM_T16, PSM_T32):
        raise ArtError("gim: palette format %d unsupported" % fmt)
    count = info["width"] * max(1, info["height"])
    start = info["start"] + info["plane"]
    raw = data[start:start + count * PSM_BYTES[fmt]]
    if len(raw) < count * PSM_BYTES[fmt]:
        raise ArtError("gim: palette truncated")
    if fmt == PSM_8888:
        return bytes(raw)
    return bytes(_unpack_u16(raw, count, fmt))


def decode_gim(data, path="<gim>"):
    """Every image in a GIM, in file order."""
    if data[:len(GIM_MAGIC)] != GIM_MAGIC:
        raise ArtError("%s: not a PSP GIM" % path)
    blocks = _parse_blocks(data)
    images = []
    for block in blocks:
        if block.block_id != 4:                 # Image
            continue
        info = _descriptor(data, block)
        fmt, bpp = info["fmt"], info["bpp"]
        if fmt not in PSM_BITS:
            raise ArtError("%s: pixel format %d unsupported (this generator covers index4/8, "
                           "4444/5551/5650/8888 — add the format before trusting a guess)"
                           % (path, fmt))
        row_bytes = (info["width"] * PSM_BITS[fmt] + 7) // 8
        pitch = _align(row_bytes, info["width_align"])
        stored_h = _align(info["height"], info["height_align"])
        # THE PADDED PITCH IS THE REAL ROW (art.md §3): vs_enter_satoshi declares 168x132 with a
        # 176-byte pitch and is in fact 176 wide. Decoding at the declared width shears it.
        width = pitch * 8 // PSM_BITS[fmt]
        start = info["start"] + info["plane"]
        need = pitch * stored_h
        raw = data[start:start + need]
        if len(raw) < need:
            raise ArtError("%s: image needs %d bytes at 0x%x, block holds %d"
                           % (path, need, start, block.end - start))
        if info["order"]:
            raw = _unswizzle(raw, width, stored_h, PSM_BITS[fmt], pitch)
        count = width * stored_h
        if fmt in (PSM_T4, PSM_T8, PSM_T16, PSM_T32):
            rgba = _unpack_indexed(raw, count, PSM_BITS[fmt],
                                   decode_palette(blocks, block, data))
        elif fmt == PSM_8888:
            rgba = bytearray(raw[:count * 4])
        else:
            rgba = _unpack_u16(raw, count, fmt)
        images.append(GimImage(width, stored_h, bytes(rgba)))
    if not images:
        raise ArtError("%s: no image block" % path)
    return images


# ============================================================================================
# Drawing: RGBA canvases, nearest/bilinear-free resampling, the floor tile, 7-segment letters
# ============================================================================================
class Canvas:
    def __init__(self, width, height, fill=(0, 0, 0, 0)):
        self.width, self.height = width, height
        self.rgba = bytearray(bytes(fill) * (width * height))

    def pixel(self, x, y, color):
        if 0 <= x < self.width and 0 <= y < self.height:
            at = (y * self.width + x) * 4
            self.rgba[at:at + 4] = bytes(color)

    def rect(self, x, y, w, h, color):
        for row in range(y, y + h):
            for col in range(x, x + w):
                self.pixel(col, row, color)

    def blend(self, x, y, color):
        if not (0 <= x < self.width and 0 <= y < self.height):
            return
        at = (y * self.width + x) * 4
        src = bytes(color)
        if src[3] == 255:
            self.rgba[at:at + 4] = src
            return
        if src[3] == 0:
            return
        sa = src[3] / 255.0
        da = self.rgba[at + 3] / 255.0
        out_a = sa + da * (1.0 - sa)
        if out_a <= 0.0:
            return
        for channel in range(3):
            value = (src[channel] * sa + self.rgba[at + channel] * da * (1.0 - sa)) / out_a
            self.rgba[at + channel] = max(0, min(255, int(round(value))))
        self.rgba[at + 3] = max(0, min(255, int(round(out_a * 255.0))))

    def blit(self, image, x, y):
        for row in range(image.height):
            for col in range(image.width):
                at = (row * image.width + col) * 4
                self.blend(x + col, y + row, image.rgba[at:at + 4])

def denoise_alpha(image):
    """Drop isolated opaque texels. The roster icons carry a single white pixel in the cell's
    top-left corner — a marker, not art — and an alpha-bounds crop that includes it would scale
    the face into a quarter of the cell."""
    out = bytearray(image.rgba)
    for y in range(image.height):
        for x in range(image.width):
            at = (y * image.width + x) * 4
            if out[at + 3] == 0:
                continue
            neighbours = 0
            for dy in (-1, 0, 1):
                for dx in (-1, 0, 1):
                    if dx == 0 and dy == 0:
                        continue
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < image.width and 0 <= ny < image.height:
                        if out[(ny * image.width + nx) * 4 + 3] != 0:
                            neighbours += 1
            if neighbours < 2:
                out[at:at + 4] = bytes((0, 0, 0, 0))
    return GimImage(image.width, image.height, bytes(out))


def alpha_bounds(image):
    """(x, y, w, h) of the non-transparent part, or the whole image when it is empty."""
    left, top, right, bottom = image.width, image.height, -1, -1
    for y in range(image.height):
        row = y * image.width * 4
        for x in range(image.width):
            if image.rgba[row + x * 4 + 3] != 0:
                left, top = min(left, x), min(top, y)
                right, bottom = max(right, x), max(bottom, y)
    if right < 0:
        return (0, 0, image.width, image.height)
    return (left, top, right - left + 1, bottom - top + 1)


def scaled(image, width, height):
    """Box-filtered resample. Down- and up-scaling both go through one box average, which is what
    keeps an upscaled 176x132 portrait from turning into 2x2 blocks."""
    out = Canvas(width, height)
    src = image.rgba
    for y in range(height):
        y0 = y * image.height // height
        y1 = max(y0 + 1, (y + 1) * image.height // height)
        for x in range(width):
            x0 = x * image.width // width
            x1 = max(x0 + 1, (x + 1) * image.width // width)
            r = g = b = a = 0
            samples = 0
            for sy in range(y0, y1):
                base = sy * image.width
                for sx in range(x0, x1):
                    at = (base + sx) * 4
                    alpha = src[at + 3]
                    r += src[at] * alpha
                    g += src[at + 1] * alpha
                    b += src[at + 2] * alpha
                    a += alpha
                    samples += 1
            if a == 0:
                continue
            out_at = (y * width + x) * 4
            out.rgba[out_at:out_at + 4] = bytes((r // a, g // a, b // a, a // samples))
    return out


# The floor tile the PC's own chibi and costume cells stand on, sampled from data/select/i00.cnv
# as the game draws it: a bright green diamond with a darker bevel.
FLOOR_FILL = (86, 210, 114, 255)
FLOOR_EDGE = (44, 148, 84, 255)


def draw_floor(canvas, x0, y0, cell=(80, 128)):
    """The green diamond at the bottom of one cell, the way the PC's 80x128 cells have it."""
    w, h = cell
    centre_x, centre_y = x0 + w // 2, y0 + 102
    half_w, half_h = (w - 4) // 2, 25
    for row in range(-half_h, half_h + 1):
        span = int((1.0 - abs(row) / float(half_h)) * half_w)
        for col in range(-span, span + 1):
            edge = abs(row) >= half_h - 1 or abs(col) >= span - 1
            canvas.pixel(centre_x + col, centre_y + row, FLOOR_EDGE if edge else FLOOR_FILL)


# 7-segment shapes: enough for the slot letters (A, b, C, d) and the item id's digits, which is
# all a place-holder plate needs. Segments: a top, b top-right, c bottom-right, d bottom,
# e bottom-left, f top-left, g middle.
SEGMENTS = {
    "0": "abcdef", "1": "bc", "2": "abged", "3": "abgcd", "4": "fgbc",
    "5": "afgcd", "6": "afgecd", "7": "abc", "8": "abcdefg", "9": "abfgcd",
    "A": "abcefg", "B": "fgecd", "C": "afed", "D": "bged", "-": "g", " ": "",
}


def draw_segment_text(canvas, x, y, text, scale, color):
    """Draw `text` in 7-segment glyphs; each glyph is 5x9 cells of `scale` pixels."""
    cursor = x
    for character in text:
        segments = SEGMENTS.get(character.upper(), "")
        width, height = 5 * scale, 9 * scale
        bars = {
            "a": (scale, 0, 3 * scale, scale),
            "g": (scale, 4 * scale, 3 * scale, scale),
            "d": (scale, 8 * scale, 3 * scale, scale),
            "f": (0, scale, scale, 3 * scale),
            "b": (4 * scale, scale, scale, 3 * scale),
            "e": (0, 5 * scale, scale, 3 * scale),
            "c": (4 * scale, 5 * scale, scale, 3 * scale),
        }
        for name in segments:
            bx, by, bw, bh = bars[name]
            canvas.rect(cursor + bx, y + by, bw, bh, color)
        cursor += width + 2 * scale
    return cursor - x


# ============================================================================================
# CNV output (src/assets/cnv.h): 17-byte header, then BGRA rows top-down
# ============================================================================================
def encode_cnv(canvas):
    header = struct.pack("<BIII", 32, canvas.width, canvas.height, canvas.width)
    header += struct.pack("<I", 0)
    pixels = bytearray(canvas.width * canvas.height * 4)
    for i in range(canvas.width * canvas.height):
        r, g, b, a = canvas.rgba[i * 4:i * 4 + 4]
        pixels[i * 4:i * 4 + 4] = bytes((b, g, r, a))
    return bytes(header) + bytes(pixels)


def encode_png(canvas):
    """A plain 8-bit RGBA PNG, for --preview only (the product never reads one)."""
    stride = canvas.width * 4
    raw = bytearray()
    for y in range(canvas.height):
        raw.append(0)
        raw += canvas.rgba[y * stride:(y + 1) * stride]

    def chunk(tag, payload):
        return (struct.pack(">I", len(payload)) + tag + payload +
                struct.pack(">I", zlib.crc32(tag + payload) & 0xFFFFFFFF))

    return (b"\x89PNG\r\n\x1a\n" +
            chunk(b"IHDR", struct.pack(">IIBBBBB", canvas.width, canvas.height, 8, 6, 0, 0, 0)) +
            chunk(b"IDAT", zlib.compress(bytes(raw), 9)) +
            chunk(b"IEND", b""))


# ============================================================================================
# Composition: one roster index's four sheets
# ============================================================================================
class Source:
    """Where a pack entry comes from: the pack itself, or a directory of extracted files."""

    def __init__(self, pack=None, dump=None):
        self.pack, self.dump = pack, dump

    def get(self, path):
        if self.pack is not None:
            data = self.pack.get(path)
            if data is not None:
                return data
        if self.dump is not None:
            local = os.path.join(self.dump, *path.split("/"))
            if os.path.exists(local):
                with open(local, "rb") as stream:
                    return stream.read()
        return None

    def image(self, path):
        data = self.get(path)
        if data is None:
            raise ArtError("%s is in neither the pack nor the dump" % path)
        images = decode_gim(data, path)
        return images[0]


def icon_cell(icon_sheet, roster_index):
    """The character's 48x48 head icon: the PSP packs them 4 across, in roster order."""
    columns, rows = ICON_GRID
    if not 0 <= roster_index < columns * rows:
        raise ArtError("roster index %d is outside the %dx%d icon sheet"
                       % (roster_index, columns, rows))
    x = (roster_index % columns) * ICON_CELL
    y = (roster_index // columns) * ICON_CELL
    if x + ICON_CELL > icon_sheet.width or y + ICON_CELL > icon_sheet.height:
        raise ArtError("icon cell (%d,%d) is outside the %dx%d sheet"
                       % (x, y, icon_sheet.width, icon_sheet.height))
    return icon_sheet.crop((x, y, ICON_CELL, ICON_CELL))


def build_portrait(source, name):
    """data/select/NN.cnv: the vs_enter art, its own alpha bounds, bottom-centre, undistorted."""
    art = source.image(SELECT_DIR + "vs_enter_%s.gim" % name)
    art = art.crop(alpha_bounds(art))
    canvas = Canvas(*PORTRAIT_RECT)
    scale = min(PORTRAIT_RECT[0] / art.width, PORTRAIT_RECT[1] / art.height)
    width = max(1, int(art.width * scale))
    height = max(1, int(art.height * scale))
    canvas.blit(scaled(art, width, height), (PORTRAIT_RECT[0] - width) // 2,
                PORTRAIT_RECT[1] - height)
    return canvas


def chibi_cell(canvas, cell_x, cell_y, head):
    """One 80x128 cell: the character's face standing on the floor tile, the way a PC chibi
    stands on its own tile. The face's chin sits just above the tile's top vertex."""
    draw_floor(canvas, cell_x, cell_y)
    crop = head.crop(alpha_bounds(head))
    # Smaller than the cell on purpose: the roster icon is a white-backed picture (the PSP's own
    # card), and at full cell width it reads as three white blocks in the diamond. Card-sized, it
    # reads as the character standing on the tile the way a PC chibi does.
    scale = min(64 / crop.width, 60 / crop.height)
    width = max(1, int(crop.width * scale))
    height = max(1, int(crop.height * scale))
    canvas.blit(scaled(crop, width, height),
                cell_x + (CHIBI_CELL[0] - width) // 2, cell_y + 86 - height)


def build_chibi(source, roster_index):
    """data/select/iNN.cnv: the 3x2 cell grid the select screen walks, with its white flash cell.

    Cells (art, in the select screen's own order): (0,0) settled, (1,0) (2,0) (0,1) (1,1) the idle
    cycle, and (2,1) the 100 % white cell the entry reveal flashes (screen_select.h's
    SelectChibiCell documents all six). The PSP has no chibi body, so each art cell is the
    character's own roster icon on the floor tile rather than a walk frame.
    """
    head = denoise_alpha(icon_cell(source.image(ICON_SHEET), roster_index))
    canvas = Canvas(*CHIBI_RECT)
    for column in range(3):
        for row in range(2):
            if (column, row) == (2, 1):
                continue
            chibi_cell(canvas, column * CHIBI_CELL[0], row * CHIBI_CELL[1], head)
    canvas.rect(2 * CHIBI_CELL[0], 1 * CHIBI_CELL[1], CHIBI_CELL[0], CHIBI_CELL[1],
                (255, 255, 255, 255))
    return canvas


def build_costumes(source, roster_index, costumes):
    """data/select/cosNN.cnv: one 80x128 cell per costume, row-major from (0,0).

    The PSP ships no per-costume picture — its costume chooser is a text list
    (gra/gim/select/costume.gim) — so every cell is the same roster icon on the floor tile. The
    COUNT is real (the PSP's chr17N/chr18N/chr19N model variants), which is what the select
    screen's costume cycle and the launch's data/<dir>:<costume> need; only the picture is a
    place-holder.
    """
    if costumes > 9:
        raise ArtError("%d costume cells do not fit the 3x3 sheet" % costumes)
    head = denoise_alpha(icon_cell(source.image(ICON_SHEET), roster_index))
    canvas = Canvas(*COSTUME_RECT)
    for index in range(costumes):
        chibi_cell(canvas, (index % 3) * CHIBI_CELL[0], (index // 3) * CHIBI_CELL[1], head)
    return canvas


def build_weapons(item_id_first, weapons=WEAPONS_PER_SHEET):
    """data/select/wNN.cnv: 4 rows of 256x64, row = weapon slot, two 256x64 columns.

    The screen reads (0, row*64, 256, 64) for the row list and (256, row*64, 256, 64) for the
    plate under it — the same two columns the PC sheets carry, where those hold the weapon's name
    and its description. The PSP has neither per weapon (its chooser is a text list), so this is
    a place-holder: the slot letter in the left column and the item id the launch will request in
    the right, so the four slots are at least distinguishable and traceable to their data.
    """
    canvas = Canvas(*WEAPON_RECT)
    for row in range(weapons):
        y = row * 64
        for column in (0, 1):
            x = column * 256
            # Inset plate with a two-tone border, so a missing sheet is not mistaken for this.
            canvas.rect(x + 8, y + 6, 240, 52, (24, 32, 48, 255))
            canvas.rect(x + 8, y + 6, 240, 2, (96, 160, 220, 255))
            canvas.rect(x + 8, y + 56, 240, 2, (96, 160, 220, 255))
            canvas.rect(x + 8, y + 6, 2, 52, (96, 160, 220, 255))
            canvas.rect(x + 246, y + 6, 2, 52, (96, 160, 220, 255))
        letter = chr(ord("A") + row)
        draw_segment_text(canvas, 8 + 16, y + 14, letter, 4, (235, 240, 250, 255))
        draw_segment_text(canvas, 256 + 8 + 16, y + 14, str(item_id_first + row), 4,
                          (235, 240, 250, 255))
    return canvas


# ============================================================================================
# CLI
# ============================================================================================
def main(argv=None):
    parser = argparse.ArgumentParser(
        description="Build the select/VS sheets for the three PSP fighters (Satoshi, Miyoko, "
                    "Okonogi) from the user's own PSP game data.")
    source_group = parser.add_mutually_exclusive_group(required=True)
    source_group.add_argument("--iso", help="Higurashi Daybreak Portable ISO image")
    source_group.add_argument("--pack", help="the ISO's PSP_GAME/USRDIR/_pack/gzpack.pck")
    source_group.add_argument("--dump", help="a directory of extracted files, at their pack paths "
                                             "(gra/gim/select/*.gim)")
    parser.add_argument("--out", default="psp-data",
                       help="where to write data/select/*.cnv (default: psp-data)")
    parser.add_argument("--preview", metavar="DIR",
                       help="also write PNG copies of every sheet there")
    parser.add_argument("--only", type=int, choices=[c[0] for c in CHARACTERS],
                       help="build one roster index only")
    args = parser.parse_args(argv)

    if args.iso:
        pack = pack_from_iso(args.iso)
    elif args.pack:
        pack = pack_from_file(args.pack)
    else:
        pack = None
    if args.dump and not os.path.isdir(args.dump):
        parser.error("--dump is not a directory: %s" % args.dump)
    source = Source(pack=pack, dump=args.dump)

    written = []
    try:
        for roster_index, name, item_first, costumes in CHARACTERS:
            if args.only is not None and args.only != roster_index:
                continue
            sheets = {
                "%02d" % roster_index: build_portrait(source, name),
                "i%02d" % roster_index: build_chibi(source, roster_index),
                "cos%02d" % roster_index: build_costumes(source, roster_index, costumes),
                "w%02d" % roster_index: build_weapons(item_first),
            }
            for stem, canvas in sheets.items():
                path = os.path.join(args.out, "data", "select", stem + ".cnv")
                os.makedirs(os.path.dirname(path), exist_ok=True)
                with open(path, "wb") as stream:
                    stream.write(encode_cnv(canvas))
                written.append(path)
                if args.preview:
                    os.makedirs(args.preview, exist_ok=True)
                    with open(os.path.join(args.preview, stem + ".png"), "wb") as stream:
                        stream.write(encode_png(canvas))
    except ArtError as error:
        print("psp_select_art: %s" % error, file=sys.stderr)
        return 1

    for path in written:
        print("wrote %s (%d bytes)" % (path, os.path.getsize(path)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
