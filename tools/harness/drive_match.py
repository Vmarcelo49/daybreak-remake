#!/usr/bin/env python3
"""Drive the ORIGINAL from boot into a Versus match, unattended.

The owner's recipe is simple — after the window appears, press `Z` to skip the
opening movie, then walk the menus. The trap (hit on 2026-10-14) is that the
movie and the title are separated by a lag: `Z` presses that land on the title
select ストーリー and start story mode instead, which is not the state we want.

The recipe that works (proved 2026-10-14, `open_skip.py`) is a *single* Z pressed
2 s after the process appears: it skips the movie and lands on the main menu. A
motion gate (press Z only while the picture moves) was tried first and **failed** —
the presses that landed after the movie were gone selected ストーリー. Hence one
press, then nothing until the menu step.

Then the documented menu flow, every press held ~1.5 s so a 60 Hz frame samples
it (`tools/harness/README.md`):

    DOWN  Z                      -> team select (青組/赤組)
    Z Z Z Z Z                    -> red team, Rena, weapon 0, hypermode, 1P
    UP  Z                        -> match settings
    UP  Z                        -> start match

Read-only against the game; the only writes are keystrokes. Prints a step log and
saves screenshots for evidence.

    python3 tools/harness/drive_match.py --shots local-data/harness/shots
"""
import argparse
import ctypes
import ctypes.util
import glob
import os
import signal
import subprocess
import sys
import time

ACTOR_PTRS = 0x006CFAE0      # DAT_006cfae0, four actor pointers
OFF_ANIM_TICK = 0xAE04
PR_SET_CHILD_SUBREAPER = 36
HOLD_MENU = 1.5              # seconds a menu key is held (>= 1 frame at 60 Hz)
HOLD_SKIP = 0.25             # seconds a movie-skip tap is held

libc = ctypes.CDLL(ctypes.util.find_library("c") or "libc.so.6", use_errno=True)


class IOVec(ctypes.Structure):
    _fields_ = [("base", ctypes.c_void_p), ("len", ctypes.c_size_t)]


def vm_read(pid, addr, size):
    buf = ctypes.create_string_buffer(size)
    local = IOVec(ctypes.cast(buf, ctypes.c_void_p), size)
    remote = IOVec(ctypes.c_void_p(addr), size)
    n = libc.process_vm_readv(ctypes.c_int(pid), ctypes.byref(local), ctypes.c_ulong(1),
                              ctypes.byref(remote), ctypes.c_ulong(1), ctypes.c_ulong(0))
    if n < 0:
        err = ctypes.get_errno()
        raise OSError(err, os.strerror(err))
    return buf.raw[:n]


def u32(pid, addr):
    return int.from_bytes(vm_read(pid, addr, 4), "little")


def find_game(exe, timeout=120):
    for _ in range(timeout):
        for entry in glob.glob("/proc/[0-9]*"):
            try:
                if open(entry + "/comm").read().strip() == exe:
                    return int(entry.rsplit("/", 1)[1])
            except OSError:
                continue
        time.sleep(1)
    return None


def window(class_hint, timeout=60):
    for _ in range(timeout):
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
        time.sleep(1)
    return None


def capture(win, path=None):
    args = ["import", "-window", win]
    if path:
        args.append(path)
    else:
        args.append("png:-")
    out = subprocess.run(args, capture_output=True, timeout=30)
    return out.stdout


def press(win, key, hold):
    subprocess.run(["xdotool", "windowactivate", "--sync", win], timeout=10)
    subprocess.run(["xdotool", "keydown", key], timeout=10)
    time.sleep(hold)
    subprocess.run(["xdotool", "keyup", key], timeout=10)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--install", default="Higurashi-Daybreak")
    ap.add_argument("--exe", default="DaybreakDX.exe")
    ap.add_argument("--shots", default="local-data/harness/shots")
    ap.add_argument("--window-class", default="daybreakdx")
    ap.add_argument("--wait", type=float, default=2.0,
                    help="seconds after the process appears before the single skip press")
    args = ap.parse_args()

    install = os.path.abspath(args.install)
    os.makedirs(args.shots, exist_ok=True)
    log = []

    def note(step, **kw):
        row = {"step": step, "t": round(time.time() % 10000, 1), **kw}
        log.append(row)
        print(f"[drive] {step} {kw if kw else ''}", flush=True)

    libc.prctl(PR_SET_CHILD_SUBREAPER, 1, 0, 0, 0)
    for entry in glob.glob("/proc/[0-9]*"):
        try:
            if open(entry + "/comm").read().strip() == args.exe:
                os.kill(int(entry.rsplit("/", 1)[1]), signal.SIGTERM)
        except OSError:
            pass

    note("launch")
    subprocess.Popen(["wine", args.exe], cwd=install,
                     env=dict(os.environ, WINEDEBUG="-all"),
                     stdout=open("/tmp/drive-match-wine.log", "wb"),
                     stderr=subprocess.STDOUT)
    pid = find_game(args.exe)
    if pid is None:
        note("error", why="game never appeared")
        return 3
    # --- stage A: skip the opening movie ------------------------------------
    # Proven recipe (2026-10-14): exactly ONE Z, 2 s after the process appears,
    # skips the movie and lands on the main menu. Extra presses are what start
    # ストーリー — they land on the title once the movie is gone — so there is one
    # press and then no input until the menu step below.
    time.sleep(args.wait)
    win = window(args.window_class)
    if win is None:
        note("error", why="window never appeared")
        return 3
    note("window", pid=pid, win=win)
    press(win, "z", HOLD_SKIP)
    note("skip-movie", presses=1)
    time.sleep(3.0)
    capture(win, os.path.join(args.shots, "drive-1-after-skip.png"))

    # --- stage B: title -> team select --------------------------------------
    time.sleep(2.0)
    press(win, "Down", HOLD_MENU)
    time.sleep(1.0)
    press(win, "z", HOLD_MENU)
    time.sleep(4.0)
    capture(win, os.path.join(args.shots, "drive-2-team-select.png"))
    note("entered-versus")

    # --- stage C: red team, Rena, weapon 0, hypermode, 1P -------------------
    for i in range(5):
        press(win, "z", HOLD_MENU)
        time.sleep(2.0)
        note("confirm", n=i + 1)
    capture(win, os.path.join(args.shots, "drive-3-ready.png"))

    # --- stage D: match settings, then start --------------------------------
    press(win, "Up", HOLD_MENU)
    time.sleep(1.0)
    press(win, "z", HOLD_MENU)
    time.sleep(2.0)
    press(win, "Up", HOLD_MENU)
    time.sleep(1.0)
    press(win, "z", HOLD_MENU)
    note("start-match-sent")

    # --- stage E: confirm actors and a running tick -------------------------
    deadline = time.time() + 45
    ptrs, ticks = [], []
    while time.time() < deadline:
        ptrs = [u32(pid, ACTOR_PTRS + i * 4) for i in range(4)]
        if all(p > 0x10000 for p in ptrs):
            t0 = [u32(pid, p + OFF_ANIM_TICK) for p in ptrs]
            time.sleep(3.0)
            t1 = [u32(pid, p + OFF_ANIM_TICK) for p in ptrs]
            if any(a != b for a, b in zip(t0, t1)):
                ticks = list(zip(t0, t1))
                break
        time.sleep(2.0)
    capture(win, os.path.join(args.shots, "drive-4-match.png"))
    note("result", actors=[hex(p) for p in ptrs], ticks=ticks,
         reached_match=bool(ticks))
    print("\n[drive] summary:")
    for row in log:
        print("   ", row)
    return 0 if ticks else 1


if __name__ == "__main__":
    sys.exit(main())
