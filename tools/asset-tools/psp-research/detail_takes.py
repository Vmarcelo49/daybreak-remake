"""Render and compose a close-up strip for a handful of takes.

    python3 detail_takes.py <rig> <take,take,...> [--frames 12] [--cols 12]

Renders the named takes with render_takes.py at 240x300 per frame, twice the sheet's
per-cell size, and stacks them into one image takes/detail_<rig>_<ids>.png. Used to
settle the takes the 6-frame contact sheet leaves ambiguous.
"""
import argparse
import json
import os
import subprocess
import sys

from PIL import Image, ImageDraw, ImageFont

HERE = os.path.dirname(os.path.abspath(__file__))
PSP = os.path.normpath(os.path.join(HERE, ".."))
TAKES = os.path.join(PSP, "takes")
FONT = "/usr/share/fonts/TTF/DejaVuSans-Bold.ttf"
MESH = {"chrm17": "chr170", "chrm18": "chr180", "chrm19": "chr190", "chrm02": "chr020"}
CELL_W, CELL_H = 240, 300
LABEL_W = 150


def root_row(rig, index):
    path = os.path.join(PSP, "notes", "take_root_motion.tsv")
    with open(path) as f:
        header = f.readline().rstrip("\n").split("\t")
        for line in f:
            parts = line.rstrip("\n").split("\t")
            row = dict(zip(header, parts))
            if row["rig"] == rig and int(row["take_index"]) == index:
                return row
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("rig")
    ap.add_argument("takes")
    ap.add_argument("--frames", type=int, default=12)
    ap.add_argument("--width", type=int, default=CELL_W)
    ap.add_argument("--height", type=int, default=CELL_H)
    ap.add_argument("--ortho", type=float, default=0.0)
    a = ap.parse_args()
    ids = [int(x) for x in a.takes.split(",") if x.strip()]
    outdir = os.path.join(TAKES, "frames", f"detail_{a.rig}_{'_'.join(map(str, ids))}")
    manifest = outdir + ".json"
    cmd = ["blender", "-b", "--factory-startup", "-P", os.path.join(HERE, "render_takes.py"),
           "--", "--rig", os.path.join(PSP, "dump", "g3d", a.rig + ".gmo"),
           "--mesh", os.path.join(PSP, "dump", "g3d", MESH[a.rig] + ".gmo"),
           "--out", outdir, "--manifest", manifest, "--frames", str(a.frames),
           "--width", str(a.width), "--height", str(a.height),
           "--only", ",".join(str(i) for i in ids)]
    if a.ortho:
        cmd += ["--ortho", str(a.ortho)]
    subprocess.run(cmd, check=True, capture_output=True)
    meta = json.load(open(manifest))
    wanted = [t for t in meta["takes"] if t["take_index"] in ids]
    font = ImageFont.truetype(FONT, 13)
    width = LABEL_W + a.frames * a.width
    height = 20 + len(wanted) * a.height
    sheet = Image.new("RGB", (width, height), (22, 24, 28))
    draw = ImageDraw.Draw(sheet)
    for row, entry in enumerate(wanted):
        top = 20 + row * a.height
        root = root_row(a.rig, entry["take_index"])
        draw.text((6, top + 6), f"#{entry['take_index']:02d}", font=font, fill=(240, 240, 245))
        draw.text((6, top + 24), entry["take_name"], font=font, fill=(200, 205, 215))
        draw.text((6, top + 42), f"{entry['frames']:.0f}f", font=font, fill=(180, 185, 195))
        if root:
            draw.text((6, top + 60), f"dy{float(root['dy']):+.0f}", font=font, fill=(160, 200, 160))
            draw.text((6, top + 78), f"dz{float(root['dz']):+.0f}", font=font, fill=(160, 200, 160))
        count = max(1, len(entry["images"]) - 1)
        for col, path in enumerate(entry["images"]):
            if os.path.exists(path):
                sheet.paste(Image.open(path).convert("RGB"), (LABEL_W + col * a.width, top))
            draw.text((LABEL_W + col * a.width + 4, top + 3), f"u={col / count:.2f}",
                      font=font, fill=(210, 215, 225))
    out = os.path.join(TAKES, f"detail_{a.rig}_{'_'.join(map(str, ids))}.png")
    sheet.save(out)
    print(out, sheet.size)


if __name__ == "__main__":
    main()
