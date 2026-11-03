#!/usr/bin/env python3
"""Does the web client's download carry the front end through a whole match?

`web_match_group_check.py` proves the *core's* reads are covered; this one proves the
*front end* is. It runs the COM-rematch flow on the real install to learn the match the
front end picks, builds the asset tree a browser would hold for that match (startup group
plus the match group, linked from the prepared catalogue), and runs the same flow inside
that tree with no installation — which is the MEMFS the wasm client plays from.

Issue #88 is the failure this guards: the round's end reads a victory script and the winner
art, and neither was in any group, so a delivered match died on an uncaught
"C++ exception" the moment the result screen opened.

    usage: web_frontend_tree_check.py <daybreak binary> <install> <prepared tree> [--frames N]

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

#: One round of the measured COM cycle: the battle starts at tick 446 and its result screen
#: opens at 2811 (tests/scripts/frontend-com-rematch.txt).
FRAMES = 3200
SCRIPT = ROOT / "tests" / "scripts" / "frontend-com-rematch.txt"

STAGE_RE = re.compile(r"\[data/(stage\d+)\]")
MOVE_RE = re.compile(r"^\[moves\] fighter \d \(.+?\): data/(\w+)/", re.M)
ITEM_RE = re.compile(r"^\[weapons\] fighter \d .+?: item (\d+)", re.M)


def run(binary, cwd, script, frames, out, install=None):
    """One headless front-end run; returns (exit code, output)."""
    command = [str(binary), "--headless", "--no-audio", f"--out={out}",
               "--screen=title", "--local-players=1", f"--script={script}",
               f"--frames={frames}", "--size=1280x720"]
    if install is not None:
        command.append(f"--install={install}")
    env = dict(os.environ)
    # Never read the host's remembered install: this run is defined by its working directory.
    env["XDG_CONFIG_HOME"] = str(Path(out).parent)
    env.pop("DAYBREAK_INSTALL", None)
    try:
        done = subprocess.run(command, cwd=str(cwd), capture_output=True, text=True,
                              errors="replace", timeout=600, env=env)
    except subprocess.TimeoutExpired:
        return -1, "timeout"
    return done.returncode, done.stdout + done.stderr


def match_from(output):
    """The stage, character directories and weapon items the front end picked."""
    stage = STAGE_RE.search(output)
    dirs = MOVE_RE.findall(output)
    items = ITEM_RE.findall(output)
    if not stage or len(dirs) != 4 or len(items) != 4:
        return None
    return stage.group(1), dirs, items


def build_tree(tree, prepared, asset_ids):
    for asset_id in asset_ids:
        destination = tree / asset_id
        destination.parent.mkdir(parents=True, exist_ok=True)
        if not destination.exists():
            os.symlink(prepared / asset_id, destination)
    # The port's own fonts and locale sheets sit beside the executable; the wasm client has
    # them preloaded at /assets, so the native stand-in needs the same visible path.
    if not (tree / "assets").exists():
        os.symlink(ROOT / "assets", tree / "assets")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("binary")
    parser.add_argument("install")
    parser.add_argument("prepared")
    parser.add_argument("--frames", type=int, default=FRAMES)
    args = parser.parse_args()

    binary = Path(args.binary).resolve()
    prepared = Path(args.prepared).resolve()
    if not (prepared / "catalog.json").is_file():
        print("SKIP: no prepared tree at %s" % prepared)
        return 77
    assets = json.loads((prepared / "catalog.json").read_text(encoding="utf-8"))["assets"]

    with tempfile.TemporaryDirectory(prefix="web_front_tree_") as tmp:
        tmp = Path(tmp)
        # 1. What match does the front end pick? Its COM panels are the original's RNG, so
        #    the tree has to be built for the run that follows, not for a guess.
        code, full = run(binary, ROOT, SCRIPT, args.frames, tmp / "full.ppm",
                         install=Path(args.install).resolve())
        found = match_from(full)
        if code != 0 or "RESULT: ok" not in full or found is None:
            print("FAIL: the flow did not reach a result on the install")
            print(full[-2000:])
            return 1
        stage, dirs, items = found
        print("picked: %s %s items %s" % (stage, " ".join(dirs), " ".join(items)))

        # 2. The tree a browser holds for exactly that match.
        startup = [a["id"] for a in assets if groups.classify(a["id"]) == groups.STARTUP]
        slots = ["data/%s:0" % name for name in dirs]
        ids = groups.match_asset_ids(assets, stage, slots, items)
        tree = tmp / "tree"
        build_tree(tree, prepared, sorted(set(startup) | set(ids)))

        # 3. The same flow from inside it: no --install, so every read lands in the tree.
        code, output = run(binary, tree, SCRIPT, args.frames, tmp / "tree.ppm")
        # Report a miss the tree adds, not one the installation itself has: a few assets the
        # game probes for and walks past (an absent shot model) are missing from the disc too.
        already_absent = set(full.splitlines())
        bad = [line for line in output.splitlines()
               if re.search(r"Asset not found|in no open bundle|cannot read|victory line unavailable", line)
               and line not in already_absent]
        result = [line for line in output.splitlines() if line.startswith("RESULT:")]
        quoted = "[result] side" in output
        if bad:
            print("the tree is missing something the install has:")
            for line in bad[:10]:
                print("  " + line)
        print("tree run: exit %d, %s, result quote %s"
              % (code, result[-1] if result else "(no RESULT line)", "read" if quoted else "NOT read"))
        if bad or code != 0 or "RESULT: ok" not in output or not quoted:
            print(output[-2000:])
            return 1
    print("web_frontend_tree_check: ok")
    return 0


if __name__ == "__main__":
    sys.exit(main())
