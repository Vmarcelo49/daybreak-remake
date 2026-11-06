"""Resolve as many of gzpack.pck's 10772 hashes to paths as possible, then classify
the rest by payload magic.

Outputs (all under local-data/harness/psp/notes/):
  resolved.tsv   path \t csize \t usize \t sha256
  unresolved.tsv hash \t csize \t magic \t usize   (paths we could not guess)
"""
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from psppack import Pack, crc, sha256

HERE = os.path.dirname(os.path.abspath(__file__))
NOTES = os.path.normpath(os.path.join(HERE, "..", "notes"))
EBOOT = os.path.normpath(os.path.join(HERE, "..", "EBOOT.dec"))

CHARS = [
    "rena", "mion", "keiichi", "satoko", "rika", "shion", "tomitake", "takano",
    "ooishi", "akasaka", "irie", "chie", "kasai", "akane", "hanyuu", "natsumi",
    "satoshi", "miyoko", "okonogi",
]
# spelling variants that appear in the EBOOT's own name pool
CHARS_ALT = CHARS + ["sion", "oishi", "hanyu", "hanyuu"]


def eboot_strings():
    """Re-extract printable ASCII runs (>=4) with their file offsets."""
    data = open(EBOOT, "rb").read()
    out = []
    for m in re.finditer(rb"[\x20-\x7e]{4,}", data):
        out.append((m.start(), m.group().decode("ascii")))
    return out, data


def build_candidates():
    """Every path we can justify guessing, as (family, path)."""
    strs, data = eboot_strings()
    cand = {}

    def add(family, path):
        if path not in cand:
            cand[path] = family

    # ---- 1. literal paths in the EBOOT (drop the leading slash) --------------
    for off, s in strs:
        if s.startswith("/") and re.fullmatch(r"/[A-Za-z0-9_/%.]+", s):
            add("eboot-literal", s.lstrip("/"))

    # ---- 2. /gra/gim/select/<name>.gim -- the %s pool lives right there -----
    pool = set()
    for off, s in strs:
        if 1888280 <= off <= 1888810 and re.fullmatch(r"[A-Za-z0-9_]{2,40}", s):
            pool.add(s)
    for p in list(pool):
        pool.add(p + "_2")
    # every identifier anywhere in the EBOOT is a cheap extra guess
    for off, s in strs:
        if re.fullmatch(r"[A-Za-z0-9_]{2,40}", s):
            pool.add(s)
    for c in CHARS_ALT:
        pool.update({c, "bustup_" + c, "bustup_" + c + "_2", "bustup_" + c + "_3",
                     "name_" + c, "face_" + c, "chara_" + c, "sel_" + c})
    for name in sorted(pool):
        for d in ("select", "result"):
            add("gra-namepool", "gra/gim/%s/%s.gim" % (d, name))

    # ---- 3. g3d: models, motions, textures, effects ------------------------
    for nn in range(0, 40):
        for k in "0123456789":
            add("chr-model", "g3d/chr%02d%s.gmo" % (nn, k))
        for w in ("a", "b", "c", "d"):
            add("chrm-motion", "g3d/chrm%02d%s.gmo" % (nn, w))
        add("chrm-motion", "g3d/chrm%02d.gmo" % nn)
        add("chrt-tex", "g3d/chrt%02d.gim" % nn)
        for w in ("a", "b", "c", "d", "e", "f", "z"):
            add("wpn-model", "g3d/wpn%02d%s.gmo" % (nn, w))
            for s in ("r1", "r2", "l1", "l2"):
                add("wpn-model", "g3d/wpn%02d%s%s.gmo" % (nn, w, s))
        for w in ("r", "l"):
            add("wpn-model", "g3d/wpn%02dn%s.gmo" % (nn, w))
        for w in ("a", "b", "c", "d"):
            for s in ("1", "2", "3"):
                add("wpn-model", "g3d/wpn%02d%s%s.gmo" % (nn, w, s))
                add("wpn-model", "g3d/wpn%02d%s%s.gmo" % (nn, s, w))
        for c in ("a", "b", "c"):
            add("wpn-model", "g3d/wpn%02d%s%s.gmo" % (nn, c, ""))
        add("map-model", "g3d/map%02d.gmo" % nn)
        for c in ("", "a", "b", "c", "d", "e"):
            add("eff-model", "g3d/eff%03d%s.gmo" % (nn, c))
        for c in ("a", "b", "c", "d", "e", "f"):
            add("eff-model", "g3d/eff0%03d%s.gmo" % (nn, c))
        for c in ("a", "b", "c", "d"):
            add("eff-model", "g3d/eff%02d%s.gmo" % (nn, c))
    for nn in range(0, 1000):
        add("eff-model", "g3d/eff%03d.gmo" % nn)
        for c in "abcdef":
            add("eff-model", "g3d/eff%03d%s.gmo" % (nn, c))
    for nn in range(0, 400):
        for c in "abcdef":
            add("eff-model", "g3d/eff%04d%s.gmo" % (nn, c))

    # ---- 4. activity / assault --------------------------------------------
    for nn in range(0, 40):
        for w in ("a", "b", "c", "d", "e", "z"):
            add("acs", "activity/chr%02d%s.acs" % (nn, w))
            add("acv", "activity/chr%02d%s.acv" % (nn, w))
            add("atp", "assault/chr%02d%s.atp" % (nn, w))
            add("voice", "activity/chr%02d%s_voice.pck" % (nn, w))
            add("se-pck", "activity/chr%02d%s_se.pck" % (nn, w))
            add("eff-pck", "activity/chr%02d%s_eff.pck" % (nn, w))
            add("voice", "activity/chr%02d%s_vce.pck" % (nn, w))
        for k in ("", "0"):
            add("eff-pck", "activity/chr%02d%s_eff.pck" % (nn, k))
        add("shared", "activity/chr%02d.acs" % nn)
        add("shared", "activity/chr%02d.acv" % nn)

    # ---- 5. audio ---------------------------------------------------------
    for n in range(0, 1000):
        add("se-vag", "se/se%03d.vag" % n)
    for a in range(0, 40):
        for b in range(0, 40):
            for c in range(0, 120):
                add("se-vag", "se/W%02d_%02d_%03d.vag" % (a, b, c))
    for n in range(0, 200):
        add("bgm", "bgm/bm%02d.at3" % n)

    # ---- 5b. adventure scripts (named by the EBOOT's own format strings) --
    for a in range(1, 90):
        for b in range(0, 4):
            add("adv", "adv/D%02d_%d.buf" % (a, b))
            add("adv", "adv/load_D%02d_%d.buf" % (a, b))
        for b in range(0, 10):
            add("adv", "adv/win_cord_%02d_%02d.buf" % (a, b))
            add("adv", "adv/win_cord_14_%02d.buf" % (a,))
        for b in range(0, 10):
            for c in range(0, 10):
                add("adv", "adv/win_cord_%02d_%02d_%02d.buf" % (a, b, c))
                add("adv", "adv/win_cord_batu_%02d_%02d.buf" % (a, b))
    # ---- 5c. adv object pictures (obj_<name>.gim) ------------------------
    for c in CHARS_ALT:
        for i in range(0, 12):
            add("adv-obj", "gra/gim/adv/obj_%s_%d.gim" % (c, i))
            add("adv-obj", "gra/gim/adv/obj_%s_%dr.gim" % (c, i))
            add("adv-obj", "gra/gim/adv/obj_%s_%d.gim" % (c, i))
        add("adv-obj", "gra/gim/adv/obj_%s.gim" % c)
    for i in range(0, 40):
        add("adv-obj", "gra/gim/adv/obj_back%02d.gim" % i)
    add("movie", "movie/demo01.pmf")

    # ---- 6. shared tables and misc ---------------------------------------
    for d in ("bin", "data", "activity", "assault", "_pack", "module", "adv"):
        for n in ("static_param.bin", "bullet_attack_data.bin", "com_param.bin",
                  "chr.fpd", "gauge_data.bin", "shot_data.bin"):
            add("shared", "%s/%s" % (d, n))
    return cand


def magic_of(head):
    if head[:8] == b"OMG.00.1":
        return "GMO"
    if head[:11] == b"MIG.00.1PSP":
        return "GIM"
    if head[:4] == b"\x00\x00\x00\x00" and len(head) >= 16 and head[4:8] == b"\x00\x00\x00\x00":
        return "?"
    return "?"


def main():
    pack = Pack()
    cand = build_candidates()
    print("candidates:", len(cand))
    resolved = {}
    for path, family in cand.items():
        h = crc(path)
        if h in pack.rows:
            resolved[h] = (path, family)
    print("resolved:", len(resolved), "of", pack.count)

    rows = []
    for h, (path, family) in sorted(resolved.items(), key=lambda kv: kv[1][0]):
        raw = pack.raw(path)
        data = pack.get(path)
        rows.append((path, family, len(raw), len(data), sha256(data)))
    with open(os.path.join(NOTES, "resolved.tsv"), "w") as f:
        f.write("path\tfamily\tcsize\tusize\tsha256\n")
        for r in rows:
            f.write("\t".join(str(x) for x in r) + "\n")

    # classify what is left by magic
    left = [h for h in pack.rows if h not in resolved]
    with open(os.path.join(NOTES, "unresolved.tsv"), "w") as f:
        f.write("hash\tcsize\tmagic\tusize\n")
        f.flush()
        for h in sorted(left):
            cs, off, _ = pack.rows[h]
            head = pack.head(off, min(cs, 16))
            f.write("%08x\t%d\t%s\t-\n" % (h, cs, magic_of(head)))
    print("unresolved:", len(left))


if __name__ == "__main__":
    main()
