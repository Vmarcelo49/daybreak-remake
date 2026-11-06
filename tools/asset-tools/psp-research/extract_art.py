#!/usr/bin/env python3
"""Extract the 2D art this study needs from gzpack.pck and decode it to PNG.

  dump/art/<pack path>      raw payload as stored in the pack (gzip-inflated)
  art/<name>.png            decoded RGBA

Paths are resolved by CRC, so an entry that is not in the pack is reported, not
assumed.  Run with --all to decode every GIM the pack holds (used as a coverage
check for scripts/gim.py).
"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import gim                                                    # noqa: E402
from psppack import Pack                                      # noqa: E402

HERE = os.path.dirname(os.path.abspath(__file__))
BASE = os.path.normpath(os.path.join(HERE, ".."))
DUMP = os.path.join(BASE, "dump", "art")
ART = os.path.join(BASE, "art")

# The two families spell four characters differently, so the name lists are the
# ones actually stored in the pack (both read out of EBOOT.dec's string pool:
# bustup_* at 0x1cd088, vs_enter_* at 0x1cdf40).
BUSTUP = ["akane", "akasaka", "chie", "hanyuu", "irie", "kasai", "keiichi", "mion",
          "miyoko", "natsumi", "okonogi", "ooishi", "rena", "rika", "satoko",
          "satoshi", "sion", "takano", "tomitake"]
VS_ENTER = ["rena", "keiichi", "mion", "rika", "satoko", "shion", "kyosuke",
            "akasaka", "ooishi", "tomitake", "miyo", "chie", "kasai", "akane",
            "natumi", "hanyu", "satoshi", "miyoko", "okonogi"]
CUTIN_NAMES = ["akane", "akasaka", "chie", "hanyuu", "irie", "kasai", "keiichi",
               "mion", "miyoko", "natsumi", "okonogi", "ooishi", "rena", "rika",
               "satoko", "satoshi", "shion", "takano", "tomitake"]


def wanted():
    out = []
    for name in BUSTUP:
        out.append("gra/gim/select/bustup_%s.gim" % name)
    for name in VS_ENTER:
        out.append("gra/gim/select/vs_enter_%s.gim" % name)
    out += ["gra/gim/select/bustup_akane_2.gim",
            "gra/gim/select/bustup_hanyuu_2.gim",
            "gra/gim/select/vs_enter_hanyu_2.gim",
            "gra/gim/select/icon_on.gim", "gra/gim/select/icon_off.gim",
            "gra/gim/select/char_name.gim", "gra/gim/select/costume.gim",
            "gra/gim/select/weapon.gim", "gra/gim/select/bukibase.gim",
            "gra/gim/select/st_bg0.gim", "gra/gim/select/st_bg1.gim",
            "gra/gim/select/vs_enter_vs.gim", "gra/gim/select/vs_bg0.gim",
            "gra/gim/select/vs_bg_blue.gim", "gra/gim/select/vs_bg_red.gim",
            "gra/gim/select/vs_head_icon.gim",
            "gra/gim/select/vs_enter_chara_name00.gim",
            "gra/gim/select/vs_enter_chara_name01.gim"]
    for name in CUTIN_NAMES:
        for n in (1, 2, 3, 4, 5, 6):
            out.append("gra/cutin/ci_%s_%02d.gim" % (name, n))
        for n in (1, 2):
            out.append("gra/cutin/ci_%s_sub%02d.gim" % (name, n))
    for n in ("meter", "moji", "scope", "syouri", "caution"):
        out.append("gra/gim/ongame/%s.gim" % n)
    for n in ("back", "back_2", "hanko", "button", "key_word"):
        out.append("gra/gim/result/%s.gim" % n)
    return out


def fetch(pack, path):
    data = pack.get(path)
    if data is None:
        return None
    dest = os.path.join(DUMP, path)
    os.makedirs(os.path.dirname(dest), exist_ok=True)
    with open(dest, "wb") as f:
        f.write(data)
    return data


def emit(data, path, note=""):
    try:
        images = gim.GimFile(path, data).images
    except gim.GimError as exc:
        print("  DECODE FAIL %s: %s" % (path, exc))
        return []
    out = []
    for i, img in enumerate(images):
        stem = os.path.basename(path).rsplit(".", 1)[0]
        suffix = "" if len(images) == 1 else "_%d" % i
        dest = os.path.join(ART, stem + suffix + ".png")
        os.makedirs(ART, exist_ok=True)
        with open(dest, "wb") as f:
            f.write(gim.encode_png(img.width, img.height, img.rgba))
        out.append((dest, img))
        print("  %-46s %-22s -> %s" % (path, img.describe(), os.path.basename(dest)))
    del note
    return out


def main():
    pack = Pack()
    if "--all" in sys.argv:
        os.makedirs(os.path.join(DUMP, "gim_all"), exist_ok=True)
        n = bad = 0
        for h in pack.hashes:
            cs, off, _unk = pack.rows[h]
            head = pack.head(off, 16)
            data = pack.get_raw(h) if hasattr(pack, "get_raw") else None
            if data is None:
                pack.f.seek(off + 0)
                import gzip
                blob = pack.f.read(cs)
                data = gzip.decompress(blob) if blob[:2] == b"\x1f\x8b" else blob
            if data[:11] != b"MIG.00.1PSP":
                continue
            n += 1
            try:
                gim.GimFile("%08x.gim" % h, data)
            except gim.GimError as exc:
                bad += 1
                print("FAIL %08x: %s" % (h, exc))
            del head
        print("decoded %d GIM(s), %d failure(s)" % (n, bad))
        return 1 if bad else 0

    hit = miss = 0
    for path in wanted():
        data = fetch(pack, path)
        if data is None:
            miss += 1
            print("  MISSING %s" % path)
            continue
        hit += 1
        emit(data, path)
    print("fetched %d, missing %d" % (hit, miss))
    return 0


if __name__ == "__main__":
    sys.exit(main())
