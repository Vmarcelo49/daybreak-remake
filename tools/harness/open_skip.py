#!/usr/bin/env python3
"""Open the original, wait 2 s after the process appears, press Z once. Nothing else.

This is deliberately the smallest thing that can work, per the owner's recipe:

  1. launch the game and wait for the process to exist,
  2. wait 2 s (the opening movie is up by then),
  3. press Z exactly **once** to skip the movie,
  4. take a screenshot so the resulting screen can be checked.

The point of the single press is that extra presses are what select ストーリー:
once the movie is skipped, another Z lands on the title menu and starts story
mode. So this script presses once and stops, and the screenshot is the evidence
of where that leaves us.

    python3 tools/harness/open_skip.py
"""
import argparse
import glob
import os
import signal
import subprocess
import sys
import time


def find_game(exe, timeout=120):
    for _ in range(timeout):
        for entry in glob.glob("/proc/[0-9]*"):
            try:
                if open(entry + "/comm").read().strip() == exe:
                    return int(entry.rsplit("/", 1)[1])
            except OSError:
                continue
        time.sleep(0.2)
    return None


def find_window(class_hint, timeout=20):
    for _ in range(timeout * 5):
        for spec in (["--class", class_hint], ["--class", "daybreakdx.exe"],
                     ["--name", "ver1"]):
            try:
                out = subprocess.run(["xdotool", "search", "--onlyvisible"] + spec,
                                     capture_output=True, text=True,
                                     timeout=10).stdout.split()
                if out:
                    return out[-1]
            except (OSError, subprocess.SubprocessError):
                pass
        time.sleep(0.2)
    return None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--install", default="Higurashi-Daybreak")
    ap.add_argument("--exe", default="DaybreakDX.exe")
    ap.add_argument("--wait", type=float, default=2.0)
    ap.add_argument("--hold", type=float, default=0.2,
                    help="how long Z is held; ~0.2 s spans a frame at 60 Hz")
    ap.add_argument("--after", type=float, default=2.0)
    ap.add_argument("--shot", default="local-data/harness/shots/open-skip.png")
    ap.add_argument("--window-class", default="daybreakdx")
    args = ap.parse_args()

    install = os.path.abspath(args.install)
    for entry in glob.glob("/proc/[0-9]*"):
        try:
            if open(entry + "/comm").read().strip() == args.exe:
                os.kill(int(entry.rsplit("/", 1)[1]), signal.SIGTERM)
        except OSError:
            pass
    time.sleep(2)

    print("[open_skip] launching", flush=True)
    subprocess.Popen(["wine", args.exe], cwd=install,
                     env=dict(os.environ, WINEDEBUG="-all"),
                     stdout=open("/tmp/open-skip-wine.log", "wb"),
                     stderr=subprocess.STDOUT)

    pid = find_game(args.exe)
    if pid is None:
        print("[open_skip] game process never appeared", file=sys.stderr)
        return 3
    print(f"[open_skip] process created: pid={pid}", flush=True)

    time.sleep(args.wait)
    win = find_window(args.window_class)
    print(f"[open_skip] window={win}; waiting {args.wait}s then pressing Z once",
          flush=True)
    if win:
        subprocess.run(["xdotool", "windowactivate", "--sync", win], timeout=10)

    subprocess.run(["xdotool", "keydown", "z"], timeout=10)
    time.sleep(args.hold)
    subprocess.run(["xdotool", "keyup", "z"], timeout=10)
    print("[open_skip] Z pressed once; no further input", flush=True)

    time.sleep(args.after)
    os.makedirs(os.path.dirname(os.path.abspath(args.shot)) or ".", exist_ok=True)
    if win:
        subprocess.run(["import", "-window", win, args.shot], timeout=30)
        print(f"[open_skip] screenshot -> {args.shot}", flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
