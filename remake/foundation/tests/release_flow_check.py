#!/usr/bin/env python3
"""release_flow_check.py — automate the release flow gate's evidence.

Why: `RELEASE-CHECKLIST.md` §3 requires a run to reach title -> selection -> stage -> VS
-> battle -> results -> selection and to complete its rounds, and it says the transcript
has to be read to confirm that. Reading it by hand is exactly the kind of check that
quietly stops happening, and `RESULT: ok` alone once passed a run where the results screen
never appeared. This script runs a recipe and asserts the evidence instead:

  * every required scene transition appears, in order;
  * the roster the recipe asked for is the roster the run built;
  * the required number of rounds completed;
  * the capture was written and is a valid frame.

Bounded timeouts: a run that stops advancing fails rather than hanging the gate.

Usage:
    release_flow_check.py <demo> <install> [--recipe 1v1|2v2|com|4p] [--rounds N]
                          [--frames N] [--out FILE] [--workdir DIR]
"""
import argparse
import re
import subprocess
import sys
import tempfile
from pathlib import Path

FOUNDATION = Path(__file__).resolve().parents[1]
SCRIPTS = FOUNDATION / "tests" / "scripts"

# Every recipe: the script, the player count, the required scene chain, the participants
# the launch must present and the rounds the run has to complete. The scene names are the
# ones the demo prints as `[menu] scene: <name>`.
RECIPES = {
    "1v1": {"script": "frontend-1v1-rematch.txt", "players": 2, "fighters": 2,
            "scenes": ["select", "vs", "result"], "rounds": 3, "frames": 15500},
    "2v2": {"script": "frontend-2v2-rematch.txt", "players": 4, "fighters": 4,
            "scenes": ["select", "vs", "result"], "rounds": 3, "frames": 15500},
    "com": {"script": "frontend-com-rematch.txt", "players": 1, "fighters": 2,
            "scenes": ["select", "vs", "result"], "rounds": 3, "frames": 15500},
    "4p":  {"script": "frontend-4p.txt", "players": 4, "fighters": 4,
            "scenes": ["select", "vs", "result"], "rounds": 1, "frames": 9600},
}

SCENE_RE = re.compile(r"\[menu\] scene: (\w+)")
ROUND_RE = re.compile(r"round over, side (-?\d+)")
ROSTER_RE = re.compile(r"\[menu\] battle: (\d+) fighter")


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("demo")
    ap.add_argument("install")
    ap.add_argument("--recipe", choices=sorted(RECIPES), default="1v1")
    ap.add_argument("--rounds", type=int, default=None)
    ap.add_argument("--frames", type=int, default=None)
    ap.add_argument("--out", default=None)
    ap.add_argument("--workdir", default=None)
    ap.add_argument("--timeout", type=float, default=900.0)
    args = ap.parse_args()

    recipe = RECIPES[args.recipe]
    rounds_required = args.rounds if args.rounds is not None else recipe["rounds"]
    # One round is roughly 4400 logic ticks in these recipes; leave headroom for the
    # extra rounds and the menu time between them.
    frames = args.frames if args.frames is not None else recipe["frames"]
    workdir = Path(args.workdir).resolve() if args.workdir else Path(tempfile.mkdtemp(prefix="flow_"))
    workdir.mkdir(parents=True, exist_ok=True)
    out = Path(args.out).resolve() if args.out else workdir / ("flow-%s.ppm" % args.recipe)
    if not Path(args.install, "data").is_dir():
        print("SKIP: no game data at %s" % args.install)
        return 77

    cmd = [str(Path(args.demo).resolve()), "--install=" + str(Path(args.install).resolve()),
           "--screen=title", "--local-players=%d" % recipe["players"],
           "--script=" + str(SCRIPTS / recipe["script"]),
           "--headless", "--no-audio", "--out=" + str(out), "--size=1280x720",
           "--frames=%d" % frames]
    print("release_flow_check: %s (%d frame budget, %d round(s) required)"
          % (args.recipe, frames, rounds_required))
    try:
        proc = subprocess.run(cmd, capture_output=True, text=True, encoding="utf-8",
                              errors="replace", timeout=args.timeout)
    except subprocess.TimeoutExpired:
        print("FAIL: the run did not finish within %ss — a stuck state, not a pass"
              % args.timeout)
        return 1
    text = (proc.stdout or "") + "\n" + (proc.stderr or "")
    artifacts = workdir / ("%s-transcript.txt" % args.recipe)
    artifacts.write_text(text, encoding="utf-8")

    failures = []
    if "RESULT: ok" not in text:
        failures.append("the run did not print `RESULT: ok` (exit %d)" % proc.returncode)

    scenes = SCENE_RE.findall(text)
    if not scenes:
        failures.append("no `[menu] scene:` lines: the front end never reported a scene")
    else:
        # The required chain must appear IN ORDER, allowing repeats (a rematch returns
        # through selection) but not a missing hop.
        position = 0
        for required in recipe["scenes"]:
            while position < len(scenes) and scenes[position] != required:
                position += 1
            if position == len(scenes):
                failures.append("scene %r never appeared after %r (saw: %s)"
                                % (required, recipe["scenes"][0], " -> ".join(scenes[:12])))
                break
            position += 1

    roster = ROSTER_RE.search(text)
    if not roster:
        failures.append("the run never reported a battle roster")
    elif int(roster.group(1)) != recipe["fighters"]:
        failures.append("the battle built %s fighter(s), the recipe asks for %d"
                        % (roster.group(1), recipe["fighters"]))

    completed = len(ROUND_RE.findall(text))
    if completed < rounds_required:
        failures.append("only %d round(s) resolved, %d required" % (completed, rounds_required))

    if not out.exists():
        failures.append("no capture at %s" % out)
    else:
        head = out.read_bytes()[:2]
        if head != b"P6":
            failures.append("the capture at %s is not a PPM (starts %r)" % (out, head))

    print("release_flow_check: scenes=%s" % " -> ".join(scenes[:8]))
    print("release_flow_check: rounds resolved=%d (required %d), roster=%s, capture=%s"
          % (completed, rounds_required, roster.group(1) if roster else "?",
             "yes" if out.exists() else "no"))
    if failures:
        print("release_flow_check: FAIL")
        for line in failures:
            print("  " + line)
        print("  transcript kept at %s" % artifacts)
        return 1
    print("release_flow_check: ok — transitions, roster, rounds and capture all verified")
    return 0


if __name__ == "__main__":
    sys.exit(main())
