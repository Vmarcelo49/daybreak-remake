#!/usr/bin/env python3
"""Watch the original's per-slot input structs while keys are sent.

Answers two questions at once:

1. do `xdotool` XTEST keys reach the game's DirectInput state? and
2. where exactly do the input fields live, so the harness can drive the game
   deterministically by writing them instead of racing a laggy game with timed
   keystrokes.

`FRONTEND-PLAN.md` §"Input" documents per-slot structs at `DAT_006cae94`, stride
0x19 dwords (100 bytes), one per player slot: `[0]` left/right, `[1]` up/down,
`[2]` confirm edge, `[3]` cancel edge, `[8]` second confirm.

Read-only. Keys go to the game window only.

    python3 tools/harness/probe_input.py --boot 16 --watch 20
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

INPUT_BASE = 0x006CAE94      # DAT_006cae94: per-slot input structs
SLOT_STRIDE = 100            # 0x19 dwords
SLOT_COUNT = 4
WATCH_DWORDS = 16            # per slot, enough to cover the documented fields
PR_SET_CHILD_SUBREAPER = 36

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


def window(class_hint):
    for spec in (["--class", class_hint], ["--class", "daybreakdx.exe"],
                 ["--name", "ver1"]):
        try:
            out = subprocess.run(["xdotool", "search", "--onlyvisible"] + spec,
                                 capture_output=True, text=True, timeout=10).stdout.split()
            if out:
                return out[-1]
        except (OSError, subprocess.SubprocessError):
            pass
    return None


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


def read_slots(pid):
    out = {}
    for slot in range(SLOT_COUNT):
        base = INPUT_BASE + slot * SLOT_STRIDE
        raw = vm_read(pid, base, WATCH_DWORDS * 4)
        out[slot] = [int.from_bytes(raw[i * 4:i * 4 + 4], "little")
                     for i in range(WATCH_DWORDS)]
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--install", default="Higurashi-Daybreak")
    ap.add_argument("--exe", default="DaybreakDX.exe")
    ap.add_argument("--boot", type=float, default=16)
    ap.add_argument("--watch", type=float, default=20)
    ap.add_argument("--window-class", default="daybreakdx")
    args = ap.parse_args()

    install = os.path.abspath(args.install)
    libc.prctl(PR_SET_CHILD_SUBREAPER, 1, 0, 0, 0)
    for entry in glob.glob("/proc/[0-9]*"):
        try:
            if open(entry + "/comm").read().strip() == args.exe:
                os.kill(int(entry.rsplit("/", 1)[1]), signal.SIGTERM)
        except OSError:
            pass

    subprocess.Popen(["wine", args.exe], cwd=install,
                     env=dict(os.environ, WINEDEBUG="-all"),
                     stdout=open("/tmp/probe-input-wine.log", "wb"),
                     stderr=subprocess.STDOUT)
    pid = find_game(args.exe)
    if pid is None:
        print("probe_input: game never appeared", file=sys.stderr)
        return 3
    print(f"probe_input: pid={pid}; booting {args.boot}s", flush=True)
    time.sleep(args.boot)

    win = window(args.window_class)
    if win:
        subprocess.run(["xdotool", "windowactivate", "--sync", win], timeout=10)
        active = subprocess.run(["xdotool", "getactivewindow"], capture_output=True,
                                text=True, timeout=10).stdout.strip()
        print(f"probe_input: window={win} active={active}", flush=True)
    else:
        print("probe_input: no window; keys will be skipped", file=sys.stderr)

    try:
        first = read_slots(pid)
    except OSError as exc:
        print(f"probe_input: read denied: {exc}", file=sys.stderr)
        return 2
    print("probe_input: slot field values at rest:", flush=True)
    for slot, vals in first.items():
        nz = {i: v for i, v in enumerate(vals) if v}
        print(f"  slot {slot}: {nz if nz else 'all zero'}", flush=True)

    last = first
    presses = [(3.0, "z"), (2.0, "Down"), (2.0, "z")]
    t0 = time.time()
    pi = 0
    changes = 0
    while time.time() - t0 < args.watch:
        now = time.time()
        while pi < len(presses) and now - t0 >= sum(d for d, _ in presses[:pi + 1]):
            key = presses[pi][1]
            if win:
                subprocess.run(["xdotool", "key", "--clearmodifiers", key], timeout=10)
            print(f"[{now - t0:5.1f}s] KEY {key}", flush=True)
            pi += 1
        try:
            cur = read_slots(pid)
        except OSError:
            break
        for slot in cur:
            for i, (a, b) in enumerate(zip(last[slot], cur[slot])):
                if a != b:
                    print(f"[{now - t0:5.1f}s] slot {slot} [0x{i*4:02x}] "
                          f"{a} -> {b}", flush=True)
                    changes += 1
        last = cur
        time.sleep(0.02)
    print(f"probe_input: {changes} field changes observed; game left running", flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
