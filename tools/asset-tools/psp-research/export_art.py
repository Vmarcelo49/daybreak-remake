"""Export GIM pictures to PNG and build the contact sheets used to read the art.

Writes local-data/harness/psp/png/<stem>_<pic>.png and sheets in png/sheets/.
"""
import os
import sys

from PIL import Image, ImageDraw

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from gim_report import export

HERE = os.path.dirname(os.path.abspath(__file__))
DUMP = os.path.normpath(os.path.join(HERE, "..", "dump"))
PNG = os.path.normpath(os.path.join(HERE, "..", "png"))
SHEETS = os.path.join(PNG, "sheets")


def sheet(items, cols, label_h, out, scale=1, background=(32, 32, 40)):
    """items: list of (label, PIL.Image)"""
    if not items:
        return None
    w = max(im.width for _l, im in items) * scale
    h = max(im.height for _l, im in items) * scale
    rows = (len(items) + cols - 1) // cols
    canvas = Image.new("RGBA", (cols * w, rows * (h + label_h)), background + (255,))
    draw = ImageDraw.Draw(canvas)
    for i, (label, im) in enumerate(items):
        cx, cy = (i % cols) * w, (i // cols) * (h + label_h)
        im2 = im.resize((im.width * scale, im.height * scale), Image.NEAREST)
        canvas.alpha_composite(im2, (cx, cy))
        draw.text((cx + 2, cy + h + 1), label, fill=(230, 230, 230, 255))
    canvas.save(out)
    return out


def main():
    os.makedirs(SHEETS, exist_ok=True)
    # 1. the per-character head picture sets
    heads = []
    for nn in range(1, 20):
        rel = "g3d/chrt%02d.gim" % nn
        p = os.path.join(DUMP, rel)
        if not os.path.exists(p):
            print(rel, "missing")
            continue
        made = export(p, PNG, "chrt%02d" % nn)
        ok = [m for m in made if m[1] is not None]
        print(rel, "pictures", len(made), "decoded", len(ok))
        if ok:
            heads.append(("chr%02d pic0" % nn, ok[0][1]))
    sheet(heads, 5, 14, os.path.join(SHEETS, "heads.png"), scale=2)
    # one character's full picture set, to show the layout
    nn = 19
    made = export(os.path.join(DUMP, "g3d/chrt%02d.gim" % nn), PNG, "chrt%02d" % nn)
    sheet([("pic %d" % i, im) for i, im, _n in made if im is not None], 5, 14,
          os.path.join(SHEETS, "chrt%02d_all.png" % nn), scale=2)

    # 2. select bustups + VS enter art
    for stem_list, out, scale in (
        (["bustup_%s" % c for c in
          ("akane", "akasaka", "chie", "hanyuu", "irie", "kasai", "keiichi", "mion",
           "miyoko", "natsumi", "okonogi", "ooishi", "rena", "rika", "satoko",
           "satoshi", "sion", "takano", "tomitake")], "bustups.png", 1),
        (["vs_enter_%s" % c for c in
          ("akane", "akasaka", "chie", "hanyu", "hanyu_2", "kasai", "keiichi",
           "kyosuke", "mion", "miyo", "miyoko", "natumi", "okonogi", "ooishi",
           "rena", "rika", "satoko", "satoshi", "shion", "takano", "tomi", "vs",
           "chara_name00", "chara_name01")], "vs_enter.png", 1),
    ):
        items = []
        for stem in stem_list:
            p = os.path.join(DUMP, "gra/gim/select/%s.gim" % stem)
            if not os.path.exists(p):
                print(stem, "missing")
                continue
            made = export(p, PNG, "sel_" + stem)
            ok = [m for m in made if m[1] is not None]
            if ok:
                items.append((stem, ok[0][1]))
        sheet(items, 4, 14, os.path.join(SHEETS, out), scale=scale)

    # 3. cut-ins for the three new fighters
    items = []
    for c in ("satoshi", "miyoko", "okonogi"):
        for i in range(1, 7):
            p = os.path.join(DUMP, "gra/cutin/ci_%s_%02d.gim" % (c, i))
            if not os.path.exists(p):
                continue
            made = export(p, PNG, "cutin_%s_%02d" % (c, i))
            ok = [m for m in made if m[1] is not None]
            if ok:
                items.append(("%s_%02d" % (c, i), ok[0][1]))
    sheet(items, 6, 14, os.path.join(SHEETS, "cutin_new3.png"), scale=1)


if __name__ == "__main__":
    main()
