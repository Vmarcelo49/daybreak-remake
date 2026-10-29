#!/usr/bin/env python3
"""Locate the game-state struct (and therefore the current scene id) by signature.

The struct is a stack local of the entry function (`FUN_0064d250`), so it has no
static address. Its signature is documented:

  * `+0x2e14` is incremented once per call of `LoadNextScene` — i.e. once per frame
    (`research/decompiled/LoadNextScene.c:12`);
  * `+0x2e18` is the switch value that selects the top-level phase
    (`LoadNextScene.c:22`; `research/symbols/types.json` GameState hypothesis);
  * `+0x2e20` is the sub-scene id.

So: scan writable memory for a dword that advances about once per frame, then
check that the candidate base looks like a game state. Read-only.

    python3 tools/harness/find_gamestate.py --seconds 6
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


def regions(pid, want_stack=False):
    """Writable, non-shared regions worth scanning."""
    out = []
    for line in open(f"/proc/{pid}/maps"):
        parts = line.split()
        if len(parts) < 2 or "w" not in parts[1] or "s" in parts[1]:
            continue
        if want_stack != ("[stack]" in line):
            continue
        lo, hi = parts[0].split("-")
        out.append((int(lo, 16), int(hi, 16)))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--install", default="Higurashi-Daybreak")
    ap.add_argument("--exe", default="DaybreakDX.exe")
    ap.add_argument("--seconds", type=float, default=6)
    ap.add_argument("--boot", type=float, default=14)
    args = ap.parse_args()

    install = os.path.abspath(args.install)
    libc.prctl(PR_SET_CHILD_SUBREAPER, 1, 0, 0, 0)
    for entry in glob.glob("/proc/[0-9]*"):
        try:
            if open(entry + "/comm").read().strip() == args.exe:
                os.kill(int(entry.rsplit("/", 1)[1]), signal.SIGTERM)
        except OSError:
            pass

    log = open("/tmp/find-gamestate-wine.log", "wb")
    proc = subprocess.Popen(["wine", args.exe], cwd=install,
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
        print("find_gamestate: game never appeared", file=sys.stderr)
        return 3
    print(f"find_gamestate: pid={pid}, booting {args.boot}s", flush=True)
    time.sleep(args.boot)

    # Sample writable regions twice, one second apart.
    sample = {}
    for lo, hi in regions(pid):
        size = hi - lo
        if size <= 0 or size > 64 * 1024 * 1024:
            continue
        try:
            sample[(lo, hi)] = vm_read(pid, lo, size)
        except OSError:
            continue
    time.sleep(1.0)
    now = {}
    for (lo, hi), before in sample.items():
        try:
            now[(lo, hi)] = vm_read(pid, lo, size=hi - lo)
        except OSError:
            continue

    hits = []
    for key, before in sample.items():
        after = now.get(key)
        if after is None:
            continue
        lo, _hi = key
        for off in range(0, len(before) - 4, 4):
            b = int.from_bytes(before[off:off + 4], "little")
            a = int.from_bytes(after[off:off + 4], "little")
            delta = (a - b) & 0xFFFFFFFF
            if 40 <= delta <= 80:            # ~60 frames in one second
                hits.append((lo + off, b, a, delta))

    print(f"find_gamestate: {len(hits)} dwords advanced 40..80 in 1 s", flush=True)
    for addr, b, a, delta in hits[:40]:
        base = addr - OFF_FRAME
        try:
            scene = int.from_bytes(vm_read(pid, base + OFF_SCENE, 4), "little")
            sub = int.from_bytes(vm_read(pid, base + OFF_SUBSCENE, 4), "little")
        except OSError:
            continue
        tag = "  <== plausible" if scene < 0x20 and sub < 0x1000 else ""
        print(f"  counter@{addr:#010x} {b} -> {a} (+{delta})  "
              f"base={base:#010x} scene={scene} sub={sub}{tag}", flush=True)

    print("find_gamestate: leaving the game running for a follow-up watch", flush=True)
    print(f"find_gamestate: wine pid={proc.pid}", flush=True)
    return 0


if __name__ == "__main__":
    sys.exit(main())
