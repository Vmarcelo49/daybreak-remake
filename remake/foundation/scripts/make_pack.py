#!/usr/bin/env python3
"""Generate a runtime asset-pack manifest from an extracted game-data tree.

The manifest is plain text: an `asset=` line naming the demo's scene, an
optional `base=` line the file paths resolve against (default: the manifest's
own directory), then one relative path per line. The demo mirrors each path
under /packs/ in the browser. Nothing here is committed — manifests and packs
reference the user's own local data.

Usage:
    make_pack.py <data-root> <rel-dir> --asset '<cli-arg>' [--base <url>] [--out manifest.txt]
Example:
    make_pack.py Higurashi-Daybreak/data akane \\
        --asset '--character=/packs/akane:0' --out /tmp/packs/akane/manifest.txt
"""
import argparse
import os
import sys

LICENSED_SUFFIXES = (".x", ".X", ".cnv", ".bmp", ".dat", ".ogg", ".wav", ".mpg")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("data_root")
    ap.add_argument("rel_dir")
    ap.add_argument("--asset", required=True)
    ap.add_argument("--base", default="")
    ap.add_argument("--out", required=True)
    args = ap.parse_args()

    src = os.path.join(args.data_root, args.rel_dir)
    if not os.path.isdir(src):
        sys.exit(f"not a directory: {src}")
    paths = []
    for dirpath, _, filenames in os.walk(src):
        for name in sorted(filenames):
            full = os.path.join(dirpath, name)
            rel = os.path.relpath(full, args.data_root).replace(os.sep, "/")
            if rel.lower().endswith(LICENSED_SUFFIXES):
                paths.append(rel)
    if not paths:
        sys.exit("no asset files found")

    with open(args.out, "w", encoding="utf-8") as f:
        f.write(f"asset={args.asset}\n")
        if args.base:
            f.write(f"base={args.base}\n")
        f.write("\n".join(paths) + "\n")
    print(f"wrote {args.out}: {len(paths)} files")


if __name__ == "__main__":
    main()
