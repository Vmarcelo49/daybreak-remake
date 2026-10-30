#!/usr/bin/env python3
"""Extract the 3D textures for upscaling, and check a pack before it ships.

    texture_pack.py extract --install DIR --out DIR [--only data/rena,data/stage01]
    texture_pack.py verify  --install DIR --pack DIR

`extract` writes PNGs at the game's paths with their alpha, so its output is already a pack.
Identical textures are written once, and duplicates.txt names the rest: keep it with the images.
It leaves out what must not be upscaled:

  * menu, HUD and 2D sheets, whose screens cut cells by the original's pixels;
  * data/directx/toon, a lighting ramp and not a picture;
  * a stage's `_1` and `_2` files: the renderer builds mips for a larger replacement.

`verify` exits 1 on an error. A warning is a mistake only sometimes. Needs Pillow.
"""
from __future__ import annotations

import argparse
import hashlib
import re
import sys
from pathlib import Path

from PIL import Image

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / "webdelivery"))
from daybreak_web.bundles import BundleSet  # noqa: E402

SHEET_DIRS = ("chat", "config", "keyconfig", "network", "object", "select", "talk", "teamselect", "title", "vs", "win")
NOT_PICTURES = ("data/directx/",)
AUDIO_DIRS = ("data/se/", "data/sysse/", "data/voice/")
MAX_SIZE = 8192  # the renderer refuses more
MIP_SUFFIX = re.compile(r"_[12]$")


def decode_cnv(data: bytes) -> Image.Image | None:
    """decodeCnvImage in src/assets/cnv.h. None for an audio .cnv."""
    if len(data) < 17:
        return None
    height = int.from_bytes(data[5:9], "little")
    width = int.from_bytes(data[9:13], "little")
    compressed = int.from_bytes(data[13:17], "little")
    if not 0 < width <= MAX_SIZE or not 0 < height <= MAX_SIZE or compressed:
        return None
    payload = len(data) - 17
    if payload == width * height * 4:
        return Image.frombuffer("RGBA", (width, height), data[17:], "raw", "BGRA", 0, 1)
    if payload == width * height * 3:
        return Image.frombuffer("RGB", (width, height), data[17:], "raw", "BGR", 0, 1).convert("RGBA")
    return None


def game_images(install: Path) -> tuple[dict, BundleSet]:
    """Lower-case stem -> (path as shipped, entry), for every .cnv, and the bundles to read them."""
    bundles = BundleSet(install)
    images = {}
    for entry in bundles.resolve().values():
        path = entry.name.replace("\\", "/")
        if path.lower().endswith(".cnv"):
            images.setdefault(path[:-4].lower(), (path, entry))
    return images, bundles


def is_sheet(stem: str) -> bool:
    return stem.split("/")[1] in SHEET_DIRS if stem.count("/") >= 2 else False


def is_upscalable(stem: str, stems) -> bool:
    if is_sheet(stem) or stem.startswith(NOT_PICTURES):
        return False
    return not (MIP_SUFFIX.search(stem) and stem[:-2] in stems)


def extract(args) -> int:
    images, bundles = game_images(args.install)
    only = tuple(p.strip().rstrip("/").lower() + "/" for p in args.only.split(",")) if args.only else ()
    written = pixels = 0
    first: dict[tuple, str] = {}
    duplicates = []
    for stem, (path, entry) in sorted(images.items()):
        if not is_upscalable(stem, images) or stem.startswith(AUDIO_DIRS) or (only and not stem.startswith(only)):
            continue
        image = decode_cnv(bundles.bundles[entry.precedence].read(entry))
        if image is None:
            print(f"skipped, not an image: {path}")
            continue
        content = (image.size, hashlib.sha256(image.tobytes()).digest())
        if content in first:
            duplicates.append(f"{path[:-4]}\t{first[content]}\n")
            continue
        first[content] = path[:-4]
        out = args.out / (path[:-4] + ".png")
        out.parent.mkdir(parents=True, exist_ok=True)
        image.save(out, compress_level=3)
        written += 1
        pixels += image.width * image.height
    if written:
        (args.out / "duplicates.txt").write_text("".join(duplicates), encoding="utf-8", newline="\n")
    print(f"{written} textures, {pixels / 1e6:.1f} Mpx, and {len(duplicates)} duplicates in {args.out}")
    return 0 if written else 1


def check(file: Path, stem: str, images, bundles, report) -> None:
    if stem not in images:
        report("error", file, "the game has no texture by this name")
        return
    path, entry = images[stem]
    original = decode_cnv(bundles.bundles[entry.precedence].read(entry))
    if original is None:
        report("error", file, f"{path} is not an image")
        return
    try:
        with Image.open(file) as opened:
            image = opened.convert("RGBA")
    except OSError as failure:
        report("error", file, f"not a readable PNG: {failure}")
        return

    size, base = image.size, original.size
    if max(size) > MAX_SIZE:
        report("error", file, f"{size[0]}x{size[1]} is above the renderer's {MAX_SIZE}")
    if is_sheet(stem):
        whole = size[0] % base[0] == 0 and size[0] * base[1] == size[1] * base[0]
        if not whole:
            report("error", file, f"{size[0]}x{size[1]}: a sheet must be a whole multiple of {base[0]}x{base[1]}")
    elif abs(size[0] * base[1] - size[1] * base[0]) > max(size[0], size[1]):
        report("warning", file, f"{size[0]}x{size[1]} changes the shape of {base[0]}x{base[1]}")
    if stem.startswith(NOT_PICTURES):
        report("warning", file, "this is a lighting ramp, not a picture")
    elif MIP_SUFFIX.search(stem) and stem[:-2] in images:
        report("warning", file, "a mip file: the renderer uses it only at half the size of its base")

    if original.getchannel("A").getextrema()[0] < 255 and image.getchannel("A").getextrema()[0] == 255:
        report("error", file, "the original has transparency and this image lost it")


def verify(args) -> int:
    images, bundles = game_images(args.install)
    counts = {"error": 0, "warning": 0}

    def report(level: str, file: Path, message: str) -> None:
        counts[level] += 1
        print(f"{level}: {file.relative_to(args.pack).as_posix()}: {message}")

    checked = 0
    stems: dict[str, Path] = {}
    duplicates = args.pack / "duplicates.txt"
    for file in sorted(p for p in args.pack.rglob("*") if p.is_file()):
        if file == duplicates:
            continue
        if file.suffix.lower() != ".png":
            report("warning", file, "ignored, the game reads only .png")
            continue
        stem = file.relative_to(args.pack).with_suffix("").as_posix().lower()
        if stem in stems:
            report("error", file, f"the same texture as {stems[stem].relative_to(args.pack).as_posix()}")
        stems[stem] = file
        check(file, stem, images, bundles, report)
        checked += 1
    covered = set(stems)
    if duplicates.is_file():
        for number, line in enumerate(duplicates.read_text(encoding="utf-8").splitlines(), 1):
            alias, _, source = (part.lower() for part in line.partition("\t"))
            if alias not in images or source not in stems:
                report("error", duplicates, f"line {number} names a texture that does not exist: {line}")
            covered.add(alias)
    wanted = {stem for stem in images if is_upscalable(stem, images) and not stem.startswith(AUDIO_DIRS)}
    print(f"{len(covered & wanted)} of {len(wanted)} 3D textures replaced")
    print(f"{checked} images, {counts['error']} error(s), {counts['warning']} warning(s)")
    return 1 if counts["error"] or not checked else 0


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    commands = parser.add_subparsers(dest="command", required=True)
    one = commands.add_parser("extract")
    one.add_argument("--install", type=Path, required=True)
    one.add_argument("--out", type=Path, required=True)
    one.add_argument("--only", help="comma-separated folders, such as data/rena,data/stage01")
    one.set_defaults(run=extract)
    two = commands.add_parser("verify")
    two.add_argument("--install", type=Path, required=True)
    two.add_argument("--pack", type=Path, required=True)
    two.set_defaults(run=verify)
    args = parser.parse_args()
    return args.run(args)


if __name__ == "__main__":
    sys.exit(main())
