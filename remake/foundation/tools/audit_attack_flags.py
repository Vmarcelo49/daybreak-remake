#!/usr/bin/env python3
"""Build and run the bundle-winning combat-record inventory tool."""
import argparse
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def main():
    cli = argparse.ArgumentParser()
    cli.add_argument("game", type=Path, nargs="?", default=Path("Higurashi-Daybreak"))
    cli.add_argument("--mask", default="0x8")
    args = cli.parse_args()
    build = ROOT / "build" / "linux"
    binary = build / "audit_attack_flags"
    subprocess.run(
        ["c++", "-std=c++17", "-O2", "-Isrc", "tools/audit_attack_flags.cpp",
         "-L" + str(build), "-lfoundation_gameplay", "-lfoundation_assets",
         "-Wl,-rpath," + str(build), "-o", str(binary)],
        cwd=ROOT, check=True)
    subprocess.run([str(binary), str(args.game.resolve()), args.mask], cwd=ROOT, check=True)


if __name__ == "__main__":
    main()
