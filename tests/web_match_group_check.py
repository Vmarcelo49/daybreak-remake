#!/usr/bin/env python3
"""Does the web client's download cover what the core reads in a match?

For every legal combo, builds a tree holding only the startup and match groups the browser
would have, runs simctl on it, and requires the hash of the same battle on the install. A
missing file either throws or changes the battle, because the core probes optional assets.

    usage: web_match_group_check.py <simctl> <install> <prepared tree> [--ticks N]

Exit 77 (skip) without a prepared tree: `python3 -m daybreak_web prepare` makes one.
"""
import argparse
import json
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "webdelivery"))
from daybreak_web import groups  # noqa: E402


def weapon_table():
    """kCharacterDirs and kWeaponIds, which are what the client requests the group from."""
    text = (ROOT / "src/battle/weapon_definition.h").read_text(encoding="utf-8")
    dirs = re.search(r"kCharacterDirs\[kCharacterCount\] = \{(.*?)\};", text, re.S).group(1)
    ids = re.search(r"kWeaponIds\[kCharacterCount\]\[kWeaponSlots\] = \{(.*?)\n\};", text, re.S).group(1)
    names = re.findall(r'"(\w+)"', dirs)
    rows = [[int(n) for n in re.findall(r"-?\d+", row)] for row in re.findall(r"\{([^{}]*)\}", ids)]
    return dict(zip(names, rows))


def run_hash(simctl, game, roster, ticks):
    proc = subprocess.run([simctl, "--game", str(game), "--roster", *roster, "--ticks", str(ticks)],
                          capture_output=True, text=True, errors="replace")
    found = re.search(r'"hash":"([0-9a-f]+)"', proc.stdout)
    return found.group(1) if found else "failed: " + proc.stderr.strip()[-160:]


def build_tree(tree, prepared, ids):
    for asset_id in ids:
        link = tree / asset_id
        link.parent.mkdir(parents=True, exist_ok=True)
        os.symlink(prepared / asset_id, link)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("simctl")
    parser.add_argument("install")
    parser.add_argument("prepared")
    parser.add_argument("--ticks", type=int, default=1200)
    args = parser.parse_args()

    prepared = Path(args.prepared).resolve()
    if not (prepared / "catalog.json").is_file():
        print("SKIP: no prepared tree at %s" % prepared)
        return 77

    assets = json.loads((prepared / "catalog.json").read_text(encoding="utf-8"))["assets"]
    startup = [a["id"] for a in assets if groups.classify(a["id"]) == groups.STARTUP]
    table = weapon_table()
    combos = subprocess.run([args.simctl, "--list"], capture_output=True, text=True,
                            check=True).stdout.split()
    failures = 0
    rosters = [combos[i:i + 4] for i in range(0, len(combos), 4)]
    for roster in rosters:
        roster += combos[:4 - len(roster)]
        slots, weapons = [], []
        for combo in roster:
            name, slot = combo.split(":")
            slots.append(name)
            weapons.append("%03d" % table[name][int(slot)])
        ids = groups.match_asset_ids(assets, "stage01", slots, weapons)
        with tempfile.TemporaryDirectory(prefix="web_group_") as tmp:
            build_tree(Path(tmp), prepared, sorted(set(startup) | set(ids)))
            got = run_hash(args.simctl, tmp, roster, args.ticks)
        want = run_hash(args.simctl, args.install, roster, args.ticks)
        verdict = "ok" if got == want else "MISMATCH"
        failures += got != want
        print("%-8s %s: %s" % (verdict, " ".join(roster), got if got != want else want))
    print("web_match_group_check: %d roster(s), %d failure(s)" % (len(rosters), failures))
    return 1 if failures else 0


if __name__ == "__main__":
    sys.exit(main())
