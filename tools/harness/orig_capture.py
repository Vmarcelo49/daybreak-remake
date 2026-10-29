#!/usr/bin/env python3
"""Tier-1 capture: record the ORIGINAL DaybreakDX.exe's actor state per tick.

Spawns the original under Wine as a descendant of this process, so yama
ptrace_scope=1 permits process_vm_readv (see README.md). Read-only: nothing is
written into the game, no code is patched.

    python3 tools/harness/orig_capture.py --seconds 60 \
        --keys "boot:12,down:1,confirm:2,confirm:3,confirm:6" --out battle.jsonl

Exit codes: 0 captured (or ran without a battle), 2 read denied, 3 game never
appeared.
"""
import argparse
import ctypes
import ctypes.util
import glob
import json
import os
import signal
import subprocess
import sys
import time

# --- addresses (provenance in README.md; do not change without evidence) ------
IMAGE_BASE = 0x400000
ACTOR_PTRS = 0x006CFAE0      # DAT_006cfae0: 4 actor pointers (FUN_006348b0:13)
OFF_ANIM_TICK = 0xAE04       # timing-hooks.json: 7741 sites, disp 0xae04
OFF_ANIM_PHASE = 0xADF4      # animation-system handoff

PR_SET_CHILD_SUBREAPER = 36
MAX_ACTORS = 4

libc = ctypes.CDLL(ctypes.util.find_library("c") or "libc.so.6", use_errno=True)


class IOVec(ctypes.Structure):
    _fields_ = [("base", ctypes.c_void_p), ("len", ctypes.c_size_t)]


def vm_read(pid, addr, size):
    """process_vm_readv without stopping the target."""
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


def become_subreaper():
    if libc.prctl(PR_SET_CHILD_SUBREAPER, 1, 0, 0, 0) != 0:
        err = ctypes.get_errno()
        print(f"harness: prctl(PR_SET_CHILD_SUBREAPER) failed: {os.strerror(err)}",
              file=sys.stderr)
        return False
    return True


def kill_stale(exe):
    for entry in glob.glob("/proc/[0-9]*"):
        try:
            if open(entry + "/comm").read().strip() == exe:
                os.kill(int(entry.rsplit("/", 1)[1]), signal.SIGTERM)
        except OSError:
            pass


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


def game_window(class_hint):
    """Window id of the game, or None. xdotool is only needed for --keys."""
    # WM_CLASS is the executable name under Wine, not the Win32 class name.
    for args in (["search", "--onlyvisible", "--class", class_hint],
                 ["search", "--onlyvisible", "--class", "daybreakdx.exe"],
                 ["search", "--onlyvisible", "--name", "ver1"],
                 ["search", "--onlyvisible", "--name", "Daybreak"]):
        try:
            out = subprocess.run(["xdotool"] + args, capture_output=True, text=True,
                                 timeout=10).stdout.split()
            if out:
                return out[-1]
        except (OSError, subprocess.SubprocessError):
            return None
    return None


KEYCODES = {"confirm": "Return", "cancel": "Escape", "up": "Up", "down": "Down",
            "left": "Left", "right": "Right", "boot": None}


def drive_keys(spec, class_hint):
    """Run the documented menu flow. Returns True if keys were sent."""
    steps = []
    for part in spec.split(","):
        name, _, secs = part.partition(":")
        steps.append((name.strip(), float(secs or 1)))
    win = game_window(class_hint)
    if not win:
        print("harness: game window not found; skipping key drive", file=sys.stderr)
        return False
    subprocess.run(["xdotool", "windowactivate", "--sync", win], timeout=10)
    active = subprocess.run(["xdotool", "getactivewindow"], capture_output=True,
                            text=True, timeout=10).stdout.strip()
    if active != win:
        print(f"harness: refusing to type — active window {active!r} is not the game "
              f"{win!r}", file=sys.stderr)
        return False
    for name, secs in steps:
        key = KEYCODES.get(name)
        if key:
            subprocess.run(["xdotool", "key", "--clearmodifiers", key], timeout=10)
            print(f"harness: key {name} ({key})", flush=True)
        time.sleep(secs)
    return True


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--install", default="Higurashi-Daybreak")
    ap.add_argument("--exe", default="DaybreakDX.exe")
    ap.add_argument("--wine", default="wine")
    ap.add_argument("--out", default="local-data/harness/orig.jsonl")
    ap.add_argument("--seconds", type=float, default=30)
    ap.add_argument("--keys", default="")
    ap.add_argument("--window-class", default="daybreakdx")
    ap.add_argument("--boot-timeout", type=int, default=120)
    ap.add_argument("--poll-ms", type=int, default=4)
    args = ap.parse_args()

    install = os.path.abspath(args.install)
    if not os.path.isfile(os.path.join(install, args.exe)):
        print(f"harness: {args.exe} not found under {install}", file=sys.stderr)
        return 3

    become_subreaper()
    kill_stale(args.exe)

    env = dict(os.environ, WINEDEBUG="-all")
    log = open("/tmp/harness-wine.log", "wb")
    print(f"harness: spawning {args.wine} {args.exe} in {install}", flush=True)
    launcher = subprocess.Popen([args.wine, args.exe], cwd=install, env=env,
                                stdout=log, stderr=subprocess.STDOUT)

    pid = find_game(args.exe, args.boot_timeout)
    if pid is None:
        print("harness: game process never appeared", file=sys.stderr)
        return 3
    print(f"harness: game pid={pid}", flush=True)

    os.makedirs(os.path.dirname(os.path.abspath(args.out)) or ".", exist_ok=True)
    out = open(args.out, "w")

    try:
        vm_read(pid, IMAGE_BASE, 4)
    except OSError as exc:
        print(f"harness: read denied ({exc}) — is this the harness's own child?",
              file=sys.stderr)
        return 2

    # Let the game reach the title before any keys.
    time.sleep(8)
    if args.keys:
        drive_keys(args.keys, args.window_class)

    deadline = time.time() + args.seconds
    last = {}
    rows = 0
    battles = 0
    in_battle = False
    while time.time() < deadline:
        ptrs = [u32(pid, ACTOR_PTRS + i * 4) for i in range(MAX_ACTORS)]
        live = [p for p in ptrs if p > 0x10000]
        if live and not in_battle:
            in_battle = True
            battles += 1
            print(f"harness: actor array populated ({len(live)} actors) — battle started",
                  flush=True)
        for slot, base in enumerate(ptrs):
            if base <= 0x10000:
                continue
            tick = u32(pid, base + OFF_ANIM_TICK)
            if last.get(slot) == tick:
                continue
            last[slot] = tick
            row = {"tick": tick, "slot": slot, "actor": hex(base),
                   "anim_phase": u32(pid, base + OFF_ANIM_PHASE)}
            out.write(json.dumps(row) + "\n")
            rows += 1
        time.sleep(args.poll_ms / 1000.0)

    out.close()
    print(f"harness: wrote {rows} rows to {args.out}; battles seen={battles}",
          flush=True)
    if launcher.poll() is None:
        launcher.terminate()
    kill_stale(args.exe)
    return 0


if __name__ == "__main__":
    sys.exit(main())
