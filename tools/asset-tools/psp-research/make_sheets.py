"""Assemble rendered take frames into labelled contact sheets.

    python3 make_sheets.py chrm17 chrm18 chrm19 chrm02 [--per-sheet 12]

Reads the manifest render_takes.py writes and the root-motion table
(take_root_motion.tsv), and builds one PNG per group of takes:

    takes/<rig>_sheet<N>.png

Each row is one take: a label column (index, chunk name, frame count, net root
displacement dx/dy/dz in file units, vertical excursion) and six evenly spaced frames
sampled over the take's frame range, at 160x200 per frame (downscaled from the 320x400
render). The character is drawn in a fixed right-profile window, so a moving root reads
as movement against the ground line and the vertical tick at z=0.
"""
import argparse
import json
import os
import sys

from PIL import Image, ImageDraw, ImageFont

HERE = os.path.dirname(os.path.abspath(__file__))
PSP = os.path.normpath(os.path.join(HERE, ".."))
TAKES = os.path.join(PSP, "takes")
FRAMES = os.path.join(TAKES, "frames")
FONT = "/usr/share/fonts/TTF/DejaVuSans.ttf"
FONT_BOLD = "/usr/share/fonts/TTF/DejaVuSans-Bold.ttf"

CELL_W, CELL_H = 160, 200
LABEL_W = 250
HEADER_H = 34
FOOTER_H = 16

FIGHTERS = {"chrm17": "Satoshi (chrm17 / chr170)",
            "chrm18": "Miyoko (chrm18 / chr180)",
            "chrm19": "Okonogi (chrm19 / chr190)",
            "chrm02": "Keiichi (chrm02 / chr020)"}


def load_root_motion(rig):
    """Model-space root motion from the posed rig (measure_takes.py).

    The raw GMO curves are in each bone's own frame, and chrm18/chrm19 rotate the root's
    parent chain, so the curve values are not model space there. The posed bone is.
    """
    rows = {}
    path = os.path.join(PSP, "notes", f"take_profile_{rig}.tsv")
    with open(path) as f:
        header = f.readline().rstrip("\n").split("\t")
        for line in f:
            if line.startswith("#") or not line.strip():
                continue
            parts = line.rstrip("\n").split("\t")
            row = dict(zip(header, parts))
            rows[int(row["take_index"])] = row
    return rows


def label_lines(entry, root):
    lines = [f"#{entry['take_index']:02d}  {entry['take_name']}",
             f"{entry['frames']:.0f} frames  ({entry['start']:.0f}..{entry['end']:.0f}) @30fps"]
    if root is None:
        lines.append("no profile")
    else:
        lines.append(f"root d = {float(root['net_dx']):+.1f} {float(root['net_dy']):+.1f} "
                     f"{float(root['net_dz']):+.1f}")
        span_y = float(root["y_max"]) - float(root["y_min"])
        span_x = float(root["x_max"]) - float(root["x_min"])
        span_z = float(root["z_max"]) - float(root["z_min"])
        lines.append(f"peak x/y/z {span_x:.0f}/{span_y:.0f}/{span_z:.0f}  air {root['air_frames']}f"
                     f"  pitch {float(root['pitch_min']):.0f}-{float(root['pitch_max']):.0f}")
    return lines


def build_sheet(rig, sheet_no, entries, root_motion, out, dummy_note=""):
    font = ImageFont.truetype(FONT, 14)
    small = ImageFont.truetype(FONT, 12)
    bold = ImageFont.truetype(FONT_BOLD, 15)
    width = LABEL_W + 6 * CELL_W
    height = HEADER_H + len(entries) * CELL_H + FOOTER_H
    sheet = Image.new("RGB", (width, height), (24, 26, 30))
    draw = ImageDraw.Draw(sheet)
    draw.text((8, 9), f"{FIGHTERS.get(rig, rig)}  --  sheet {sheet_no}  "
                      f"(file +Z forward = image right, +Y up; tick at z=0, line at y=0)",
              font=bold, fill=(230, 232, 238))
    for row, entry in enumerate(entries):
        top = HEADER_H + row * CELL_H
        if row % 2 == 0:
            draw.rectangle([0, top, width, top + CELL_H], fill=(30, 33, 38))
        lines = label_lines(entry, root_motion.get(entry["take_index"]))
        for k, text in enumerate(lines):
            draw.text((8, top + 8 + k * 17), text, font=font if k < 2 else small,
                      fill=(235, 236, 240) if k == 0 else (170, 175, 185))
        for col, path in enumerate(entry["images"]):
            x = LABEL_W + col * CELL_W
            if os.path.exists(path):
                image = Image.open(path).convert("RGB").resize((CELL_W, CELL_H), Image.LANCZOS)
                sheet.paste(image, (x, top))
            draw.rectangle([x, top, x + CELL_W - 1, top + CELL_H - 1], outline=(60, 64, 72))
            u = col / max(1, len(entry["images"]) - 1)
            draw.text((x + 4, top + 3), f"u={u:.1f}", font=small, fill=(150, 155, 165))
        if not entry["images"]:
            draw.text((LABEL_W + 8, top + 8), "empty take: no curves (Dummy slot)",
                      font=small, fill=(200, 120, 120))
    draw.text((8, height - FOOTER_H + 1),
              f"frames sampled u=0..1 over each take's own range; renders by render_takes.py"
              f"   |   empty Dummy slots (not rendered): {dummy_note}",
              font=small, fill=(120, 124, 132))
    sheet.save(out)
    return out, sheet.size


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("rigs", nargs="+")
    ap.add_argument("--per-sheet", type=int, default=12)
    a = ap.parse_args()
    made = []
    for rig in a.rigs:
        manifest = os.path.join(FRAMES, rig + ".json")
        meta = json.load(open(manifest))
        root_motion = load_root_motion(rig)
        takes = meta["takes"]
        dummies = [t["take_index"] for t in takes if t["empty"]]
        dummy_note = ", ".join(str(i) for i in dummies)
        takes = [t for t in takes if not t["empty"]]
        chunks = [takes[i:i + a.per_sheet] for i in range(0, len(takes), a.per_sheet)]
        for n, chunk in enumerate(chunks, 1):
            out = os.path.join(TAKES, f"{rig}_sheet{n}.png")
            path, size = build_sheet(rig, n, chunk, root_motion, out, dummy_note)
            made.append((path, size, chunk[0]["take_index"], chunk[-1]["take_index"]))
    for path, size, first, last in made:
        print(f"{path}  {size[0]}x{size[1]}  takes {first}..{last}")


if __name__ == "__main__":
    main()
