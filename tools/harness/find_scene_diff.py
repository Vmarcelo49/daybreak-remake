#!/usr/bin/env python3
"""Find the current-scene variable WITHOUT sending any input.

The movie → title transition happens on its own, so sampling writable guest
memory across it reveals which dwords carry scene state — no keystrokes, no
timing races, nothing written into the game.

Method: hash every 4 KiB page of the 32-bit guest's writable memory, re-sample
every few seconds, and remember the dwords inside pages that changed. Candidates
are then ranked by how many *small* values they took (a scene id is 0..0x16).

    python3 tools/harness/find_scene_diff.py --watch 90
"""
import argparse
import ctypes
import ctypes.util
import glob
import hashlib
import os
import signal
import subprocess
import sys
import time

PAGE = 4096
GUEST_LIMIT = 1 << 32
PR_SET_CHILD_SUBREAPER = 36
MAX_REGION = 128 * 1024 * 1024

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


def guest_regions(pid):
    out = []
    for line in open(f"/proc/{pid}/maps"):
        parts = line.split()
        if len(parts) < 2 or "w" not in parts[1] or "s" in parts[1]:
            continue
        lo, hi = (int(x, 16) for x in parts[0].split("-"))
        if hi > GUEST_LIMIT or hi - lo > MAX_REGION:
            continue
        out.append((lo, hi))
    return out


def snapshot(pid, regions):
    """page address -> 8-byte hash."""
    pages = {}
    for lo, hi in regions:
        try:
            data = vm_read(pid, lo, hi - lo)
        except OSError:
            continue
        for off in range(0, len(data) - PAGE + 1, PAGE):
            pages[lo + off] = hashlib.blake2b(data[off:off + PAGE], digest_size=8).digest()
    return pages


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--install", default="Higurashi-Daybreak")
    ap.add_argument("--exe", default="DaybreakDX.exe")
    ap.add_argument("--boot", type=float, default=6)
    ap.add_argument("--watch", type=float, default=90)
    ap.add_argument("--interval", type=float, default=4)
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
                     stdout=open("/tmp/scene-diff-wine.log", "wb"),
                     stderr=subprocess.STDOUT)
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
        print("find_scene_diff: game never appeared", file=sys.stderr)
        return 3
    print(f"find_scene_diff: pid={pid}; boot {args.boot}s then sampling", flush=True)
    time.sleep(args.boot)

    regions = guest_regions(pid)
    total = sum(hi - lo for lo, hi in regions)
    print(f"find_scene_diff: {len(regions)} regions, {total / 1e6:.0f} MB", flush=True)

    prev = snapshot(pid, regions)
    print(f"find_scene_diff: {len(prev)} pages hashed", flush=True)

    # addr -> list of (t, value) for dwords that ever took a small value
    interesting = {}
    t0 = time.time()
    while time.time() - t0 < args.watch:
        time.sleep(args.interval)
        cur = snapshot(pid, regions)
        changed = [p for p, h in cur.items() if prev.get(p) != h]
        if changed:
            print(f"[{time.time() - t0:5.1f}s] {len(changed)} pages changed", flush=True)
        for page in changed:
            try:
                data = vm_read(pid, page, PAGE)
            except OSError:
                continue
            for off in range(0, PAGE - 4, 4):
                v = int.from_bytes(data[off:off + 4], "little")
                if v < 0x40:                      # scene-like small value
                    interesting.setdefault(page + off, []).append(
                        (round(time.time() - t0, 1), v))
        prev = cur

    print(f"\nfind_scene_diff: {len(interesting)} small-valued dwords changed", flush=True)
    ranked = sorted(interesting.items(), key=lambda kv: -len({v for _, v in kv[1]}))
    for addr, series in ranked[:25]:
        vals = [v for _, v in series]
        if len(set(vals)) < 2:                    # a flag flipping once is weak
            continue
        print(f"  {addr:#010x}: {vals[:20]}", flush=True)

    for entry in glob.glob("/proc/[0-9]*"):
        try:
            if open(entry + "/comm").read().strip() == args.exe:
                os.kill(int(entry.rsplit("/", 1)[1]), signal.SIGTERM)
        except OSError:
            pass
    print("find_scene_diff: game stopped", flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
