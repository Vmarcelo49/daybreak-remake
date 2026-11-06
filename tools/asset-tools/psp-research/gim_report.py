"""GIM header decode + PNG export.

A GIM is a chunked container: 11-byte magic "MIG.00.1PSP", 0x10-byte-aligned header,
then nested chunks (u16 id, u16 reserved, u32 size, u32 next, u32 data offset):
  0x02 = container, 0x03 = picture, 0x04 = image, 0x05 = palette.
Image header words (all u16, at chunk+0x10): blockid, blocks, fmt, order, width, height,
bpp, pitch_align.  box = (blocks - 1) * 8 + 8 rows.
"""
import os
import struct
import sys

from PIL import Image

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gmo  # repository parser: decode_gim()

HERE = os.path.dirname(os.path.abspath(__file__))
DUMP = os.path.normpath(os.path.join(HERE, "..", "dump"))
PNG = os.path.normpath(os.path.join(HERE, "..", "png"))

FMT = {0: "RGBA5650", 1: "RGBA5551", 2: "RGBA4444", 3: "RGBA8888",
       4: "INDEX4", 5: "INDEX8", 6: "INDEX16", 7: "INDEX32"}


def walk_gim(d):
    """Top-level pictures of a GIM: list of dicts with image and palette headers."""
    pictures = []

    def descend(at, end):
        while at + 16 <= end:
            kind = struct.unpack_from("<H", d, at)[0]
            size, following, inner = struct.unpack_from("<III", d, at + 4)
            if size < 16:
                return
            if kind == 2:
                descend(at + inner, at + size)
            elif kind == 3:
                pictures.append({"image": None, "palette": None, "chunks": []})
                descend(at + inner, at + size)
            elif kind in (4, 5) and pictures:
                pictures[-1]["image" if kind == 4 else "palette"] = at + inner
                pictures[-1]["chunks"].append(kind)
            at += following or size

    descend(0x10, len(d))
    return pictures


def image_header(d, at):
    blockid, blocks, fmt, order, w, h, bpp, align = struct.unpack_from("<8H", d, at)
    pixels = struct.unpack_from("<I", d, at + 0x1c)[0]
    return {
        "blockid": blockid, "blocks": blocks, "fmt": fmt, "fmt_name": FMT.get(fmt, "?"),
        "order": order, "width": w, "height": h, "bpp": bpp, "pitch_align": align,
        "data_off": pixels, "rows": (blocks - 1) * 8 + 8,
    }


def palette_header(d, at):
    blockid, blocks, fmt, order = struct.unpack_from("<4H", d, at)
    count = struct.unpack_from("<H", d, at + 8)[0]
    pixels = struct.unpack_from("<I", d, at + 0x1c)[0]
    return {"fmt": fmt, "fmt_name": FMT.get(fmt, "?"), "order": order, "count": count,
            "data_off": pixels}


def describe(path, outdir):
    d = open(path, "rb").read()
    if d[:11] != b"MIG.00.1PSP":
        return None
    pics = walk_gim(d)
    rows = []
    for i, p in enumerate(pics):
        img = image_header(d, p["image"]) if p["image"] is not None else None
        pal = palette_header(d, p["palette"]) if p["palette"] is not None else None
        rows.append((i, img, pal))
    return rows


def export(path, outdir, stem):
    d = open(path, "rb").read()
    pics = walk_gim(d)
    made = []
    os.makedirs(outdir, exist_ok=True)
    for i in range(len(pics)):
        try:
            w, h, px = gmo.decode_gim(d, i)
        except Exception as e:  # noqa: BLE001
            made.append((i, None, "%s_%02d FAILED %s" % (stem, i, e)))
            continue
        im = Image.frombytes("RGBA", (w, h), px)
        name = os.path.join(outdir, "%s_%02d.png" % (stem, i))
        im.save(name)
        made.append((i, im.copy(), name))
    return made


def main():
    targets = []
    for nn in range(1, 20):
        targets.append(("g3d/chrt%02d.gim" % nn, "chrt%02d" % nn))
    names = ["bustup_%s" % c for c in
             ("akane", "akasaka", "chie", "hanyuu", "irie", "kasai", "keiichi", "mion",
              "miyoko", "natsumi", "okonogi", "ooishi", "rena", "rika", "satoko",
              "satoshi", "sion", "takano", "tomitake")]
    names += ["vs_enter_%s" % c for c in
              ("akane", "akasaka", "chie", "hanyu", "hanyu_2", "kasai", "keiichi",
               "kyosuke", "mion", "miyo", "miyoko", "natumi", "okonogi", "ooishi",
               "rena", "rika", "satoko", "satoshi", "shion", "takano", "tomi",
               "vs", "chara_name00", "chara_name01", "tomi_take")]
    names += ["vs_bg0", "vs_bg1", "vs_bg_blue", "vs_bg_center", "vs_bg_impact",
              "vs_bg_red", "vs_bg_thunder", "vs_head_icon", "vs_info_mes01",
              "vs_label_akagumi", "vs_label_aogumi", "char_name", "costume", "weapon",
              "new_weapon", "bukibase", "st_bg0", "st_bg1"]
    targets += [("gra/gim/select/%s.gim" % n, "sel_" + n) for n in names]
    cutins = [("gra/cutin/ci_%s_0%d.gim" % (c, i), "cutin_%s_0%d" % (c, i))
              for c in ("satoshi", "miyoko", "okonogi") for i in (1, 2)]
    targets += cutins

    log = []
    for rel, stem in targets:
        p = os.path.join(DUMP, rel)
        if not os.path.exists(p):
            log.append("%-40s MISSING" % rel)
            continue
        rows = describe(p, None)
        log.append("%-40s %d picture(s)" % (rel, len(rows)))
        for i, img, pal in rows:
            if img:
                log.append("   pic %d: fmt=%d(%s) order=%d %dx%d bpp=%d blocks=%d rows=%d align=%d"
                           % (i, img["fmt"], img["fmt_name"], img["order"], img["width"],
                              img["height"], img["bpp"], img["blocks"], img["rows"],
                              img["pitch_align"]))
            if pal:
                log.append("   pic %d palette: fmt=%d(%s) entries=%d order=%d"
                           % (i, pal["fmt"], pal["fmt_name"], pal["count"], pal["order"]))
    with open(os.path.join(HERE, "..", "notes", "gim_report.txt"), "w") as f:
        f.write("\n".join(log) + "\n")
    print("\n".join(log[:40]))
    print("... %d lines" % len(log))


if __name__ == "__main__":
    main()
