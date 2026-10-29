#!/usr/bin/env python3
"""Identify the game's current-scene variable by behaviour, not by guessing.

Candidates come from the documented GameState signature (`+0x2e14` advances once
per frame, `+0x2e18` is the top-level switch; `research/decompiled/LoadNextScene.c`
and `research/symbols/types.json`). The scanner keeps only 32-bit guest addresses
(the 64-bit host allocations Wine makes for itself are noise), then the tool
drives the documented menu keys and logs which candidate changes on each press.

Read-only. Keys go to the game window only. The tool never patches the game.

    python3 tools/harness/find_scene.py --boot 16 --watch 45
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

OFF_FRAME = 0x2E14
OFF_SCENE = 0x2E18
OFF_SUBSCENE = 0x2E20
GUEST_LIMIT = 1 << 32
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


def dword(pid, addr):
    return int.from_bytes(vm_read(pid, addr, 4), "little")


def guest_writable_regions(pid):
    out = []
    for line in open(f"/proc/{pid}/maps"):
        parts = line.split()
        if len(parts) < 2 or "w" not in parts[1] or "s" in parts[1]:
            continue
        lo, hi = parts[0].split("-")
        lo, hi = int(lo, 16), int(hi, 16)
        if hi > GUEST_LIMIT or hi - lo > 64 * 1024 * 1024:
            continue
        out.append((lo, hi))
    return out


def find_candidates(pid):
    first = {}
    for lo, hi in guest_writable_regions(pid):
        try:
            first[(lo, hi)] = vm_read(pid, lo, hi - lo)
        except OSError:
            continue
    time.sleep(1.0)
    cands = []
    for (lo, _hi), before in first.items():
        try:
            after = vm_read(pid, lo, len(before))
        except OSError:
            continue
        for off in range(0, len(before) - 4, 4):
            b = int.from_bytes(before[off:off + 4], "little")
            a = int.from_bytes(after[off:off + 4], "little")
            if b < 200 or not 40 <= ((a - b) & 0xFFFFFFFF) <= 80:
                continue
            base = lo + off - OFF_FRAME
            if base < 0x10000:
                continue
            try:
                scene = dword(pid, base + OFF_SCENE)
                sub = dword(pid, base + OFF_SUBSCENE)
            except OSError:
                continue
            if scene < 0x20 and sub < 0x1000:
                cands.append((base, scene, sub))
    return cands


# (gap before the press, key). Each press is held -- see hold_key().
KEY_SEQUENCE = [
    (2.0, "z"), (3.0, "Down"), (3.0, "z"),
    (3.5, "z"), (3.5, "z"), (3.5, "z"), (3.5, "z"),
    (3.0, "Up"), (2.5, "z"), (3.0, "Up"), (2.5, "z"),
]
HOLD_SECONDS = 1.5          # longer than one ~1 s frame under Wine


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--install", default="Higurashi-Daybreak")
    ap.add_argument("--exe", default="DaybreakDX.exe")
    ap.add_argument("--boot", type=float, default=16)
    ap.add_argument("--watch", type=float, default=45)
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

    log = open("/tmp/find-scene-wine.log", "wb")
    subprocess.Popen(["wine", args.exe], cwd=install,
                     env=dict(os.environ, WINEDEBUG="-all"),
                     stdout=log, stderr=subprocess.STDOUT)

    pid = None
    for _ in range(120):
        for entry in glob.glob("/proc/[0-9]*"):
            try:
                if open(entry + "/comm").read().strip() == args.exe:
                    pid = int(entry.rsplit("/", 1)[1])
                    break
            except OSError:
                continue
        if pid:
            break
        time.sleep(1)
    if not pid:
        print("find_scene: game never appeared", file=sys.stderr)
        return 3
    print(f"find_scene: pid={pid}; booting {args.boot}s", flush=True)
    time.sleep(args.boot)

    cands = find_candidates(pid)
    print(f"find_scene: {len(cands)} candidate game-state bases", flush=True)
    for base, scene, sub in cands:
        print(f"  base={base:#010x} scene={scene} sub={sub}", flush=True)
    if not cands:
        return 1

    # Wine sets WM_CLASS from the executable name, not the Win32 class
    # ("daybreakdx.exe"); verified on this machine 2026-10-14.
    win = None
    for spec in (["--class", args.window_class], ["--class", "daybreakdx.exe"],
                 ["--name", "ver1"], ["--name", "Daybreak"]):
        try:
            out = subprocess.run(["xdotool", "search", "--onlyvisible"] + spec,
                                 capture_output=True, text=True, timeout=10).stdout.split()
            if out:
                win = out[-1]
                break
        except (OSError, subprocess.SubprocessError):
            pass
    if win:
        subprocess.run(["xdotool", "windowactivate", "--sync", win], timeout=10)
    print(f"find_scene: window={win}", flush=True)

    last = {base: scene for base, scene, _ in cands}
    t0 = time.time()
    presses = [(t0 + dt, key) for dt, key in KEY_SEQUENCE]
    pi = 0
    while time.time() - t0 < args.watch:
        now = time.time()
        while pi < len(presses) and now >= presses[pi][0]:
            key = presses[pi][1]
            if win:
                # Hold across a frame: press, wait, release.
                subprocess.run(["xdotool", "keydown", key], timeout=10)
                time.sleep(HOLD_SECONDS)
                subprocess.run(["xdotool", "keyup", key], timeout=10)
            print(f"[{time.time() - t0:6.1f}s] KEY {key} (held {HOLD_SECONDS}s)",
                  flush=True)
            pi += 1
        for base, _s, _sub in cands:
            try:
                v = dword(pid, base + OFF_SCENE)
                sub = dword(pid, base + OFF_SUBSCENE)
            except OSError:
                continue
            if last.get(base) != v:
                print(f"[{now - t0:6.1f}s] base={base:#010x} scene "
                      f"{last.get(base)} -> {v} (sub={sub})", flush=True)
                last[base] = v
        time.sleep(0.1)
    print("find_scene: done; game left running", flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
