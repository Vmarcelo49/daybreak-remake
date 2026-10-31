#!/usr/bin/env python3
"""Online play (docs/ONLINE-PLAN.md, step 6): four real games walk lobby, selection, battle, results, lobby.

Headless, over localhost, with scripted buttons. Agreement between peers, not with the original.
"""
import pathlib
import re
import socket
import subprocess
import sys
import tempfile

FRAMES = 8000
PLAYERS = 4


def press(tick, *keys):
    return f"{tick} {' '.join(keys)}\n{tick + 6} -\n"


def select_own_panel(start):
    """On the selection screen: claim a panel, then confirm the fighter, weapon, mode and controller."""
    return [press(start + 16 * i, "JUMP") for i in range(5)]


def host_script():
    # After the panel: to the decide cell, start the stage page, 60 seconds, and start the match.
    lines = ["60 WAIT netplaylobby\n", press(100, "JUMP"), "130 WAIT select\n"]
    lines += select_own_panel(300)
    lines += [press(460, "DOWN"), press(480, "DOWN")]
    # Pressed again and again, since it waits until the other player has chosen.
    lines += [press(tick, "JUMP") for tick in range(520, 760, 24)]
    # A random stage skips the variation row: one down to the time limit, and two ups wrap to START.
    lines += [press(800, "DOWN"), press(840, "RIGHT"), press(860, "UP"), press(880, "UP")]
    lines += [press(tick, "JUMP") for tick in range(900, 960, 24)]
    lines += ["1000 WAIT result\n"]
    lines += [press(tick, "JUMP") for tick in range(1010, FRAMES, 30)]
    return "".join(lines)


def join_script():
    lines = ["60 WAIT netplaylobby\n", press(100, "JUMP"), "130 WAIT select\n"]
    lines += select_own_panel(300)
    lines += ["1000 WAIT result\n"]
    lines += [press(tick, "JUMP") for tick in range(1010, FRAMES, 30)]
    return "".join(lines)


def scenes(log):
    return re.findall(r"\[menu\] scene: (\w+)", log)


def main():
    daybreak, install = sys.argv[1], sys.argv[2]
    if not (pathlib.Path(install) / "daybreak00.dat").exists():
        print("SKIP: no install")
        return 77
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as probe:
        probe.bind(("127.0.0.1", 0))
        port = probe.getsockname()[1]
    with tempfile.TemporaryDirectory() as name:
        folder = pathlib.Path(name)
        (folder / "host.txt").write_text(host_script())
        (folder / "join.txt").write_text(join_script())
        common = ["--headless", "--no-audio", f"--install={install}", f"--frames={FRAMES}", "--size=320x180"]
        games = [("host", subprocess.Popen([daybreak, *common, f"--net-host={port}", f"--script={folder}/host.txt", f"--out={folder}/host.ppm"],
                                           stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, errors="replace"))]
        for peer in range(1, PLAYERS):
            games.append((f"join {peer}", subprocess.Popen([daybreak, *common, f"--net-join=127.0.0.1:{port}", f"--script={folder}/join.txt", f"--out={folder}/join{peer}.ppm"],
                                                           stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, errors="replace")))
        failed = False
        for role, process in games:
            out, _ = process.communicate(timeout=400)
            walk = scenes(out)
            net = re.findall(r"\[net\][^\n]*", out)
            print(f"{role}: {' '.join(walk)}")
            print(f"{role}: {net}, exit {process.returncode}")
            first = walk.index("netplaylobby") if "netplaylobby" in walk else -1
            wanted = ["netplaylobby", "select", "vs", "result", "netplaylobby"]
            if walk[first:first + len(wanted)] != wanted:
                print(f"FAIL: {role} did not walk {wanted}")
                failed = True
            if not any(" 0 desyncs" in line for line in net):
                print(f"FAIL: {role} has no clean match report")
                failed = True
    print("online_flow_check: failed" if failed else "online_flow_check: ok")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
