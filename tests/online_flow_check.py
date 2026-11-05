#!/usr/bin/env python3
"""Online play (docs/ONLINE-PLAN.md, step 6): real games walk lobby, selection, battle, results, lobby.

Headless, over localhost, with scripted buttons. Agreement between peers, not with the original.

Two walks, because the second one is a bug the first one could not see:
  * four players, everyone pressing, walk the whole loop;
  * two players where ONLY THE HOST PRESSES after the round. The result screen's win text ->
    report -> done beats advance on a confirm, so a confirm read from each machine's own pad
    walked each machine's timeline separately: the peer that pressed reached the lobby while the
    other sat on the report for the rest of the run (the owner's two-machine report). Both peers
    must still walk result -> netplaylobby.
"""
import pathlib
import re
import socket
import subprocess
import sys
import tempfile

# Frames are 60 Hz of REAL time here: the port throttles an online capture to the frame rate,
# because peers and their timeouts live in real time (frame_loop.inc). The walk needs the
# lobby, the selection, the versus intro, a 60 s round, the result and the way back, so the
# budget follows the round: ~1000 frames of screens, 3600 of round, and the rest of the
# presentation and the return. It is therefore a labelled slow test (issue #98 test-time
# rework): 8000 frames was 133 s of wall time, and this is ~100 s — the round is the floor
# while the stage page's shortest finite limit is 60 s.
#
# The result screen's beats are shared lockstep frames now, so the walk needs headroom past the
# round (which ends around frame 5450) for the report's own reveal and the lockstep's input delay;
# 5600 left ~140 frames and failed under load.
FRAMES = 6000

WALKED = ["netplaylobby", "select", "vs", "result", "netplaylobby"]


def press(tick, *keys):
    return f"{tick} {' '.join(keys)}\n{tick + 6} -\n"


def select_own_panel(start):
    """On the selection screen: claim a panel, then confirm the fighter, weapon, mode and controller."""
    return [press(start + 16 * i, "JUMP") for i in range(5)]


def host_script(presses_after_round):
    # After the panel: to the decide cell, start the stage page, 60 seconds, and start the match.
    lines = ["60 WAIT netplaylobby\n", press(100, "JUMP"), "130 WAIT select\n"]
    lines += select_own_panel(300)
    lines += [press(460, "DOWN"), press(480, "DOWN")]
    # Pressed again and again, since it waits until the other player has chosen.
    lines += [press(tick, "JUMP") for tick in range(520, 760, 24)]
    # A random stage skips the variation row: one down to the time limit (one step right is
    # the page's shortest finite round, 60 s), and two ups wrap to START.
    lines += [press(800, "DOWN"), press(840, "RIGHT"), press(860, "UP"), press(880, "UP")]
    lines += [press(tick, "JUMP") for tick in range(900, 960, 24)]
    if presses_after_round:
        # The round ends around frame 5400 whatever ticks the script names, so the presses cover
        # the rest of the run instead of landing on a tick guessed from an older budget.
        lines += ["1000 WAIT result\n"]
        lines += [press(tick, "JUMP") for tick in range(1010, FRAMES, 20)]
    return "".join(lines)


def join_script(presses_after_round):
    lines = ["60 WAIT netplaylobby\n", press(100, "JUMP"), "130 WAIT select\n"]
    lines += select_own_panel(300)
    if presses_after_round:
        lines += ["1000 WAIT result\n"]
        lines += [press(tick, "JUMP") for tick in range(1010, FRAMES, 20)]
    return "".join(lines)


def scenes(log):
    return re.findall(r"\[menu\] scene: (\w+)", log)


def walk(daybreak, install, players, host_presses, join_presses, folder, tag):
    """Runs one room: the host plus `players - 1` joiners. True when every peer walked the loop."""
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as probe:
        probe.bind(("127.0.0.1", 0))
        port = probe.getsockname()[1]
    (folder / "host.txt").write_text(host_script(host_presses))
    (folder / "join.txt").write_text(join_script(join_presses))
    common = ["--headless", "--no-audio", f"--install={install}", f"--frames={FRAMES}", "--size=320x180"]
    games = [("host", subprocess.Popen([daybreak, *common, f"--net-host={port}", f"--script={folder}/host.txt", f"--out={folder}/{tag}-host.ppm"],
                                       stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, errors="replace"))]
    for peer in range(1, players):
        games.append((f"join {peer}", subprocess.Popen([daybreak, *common, f"--net-join=127.0.0.1:{port}", f"--script={folder}/join.txt", f"--out={folder}/{tag}-join{peer}.ppm"],
                                                       stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, errors="replace")))
    passed = True
    for role, process in games:
        out, _ = process.communicate(timeout=400)
        seen = scenes(out)
        net = re.findall(r"\[net\][^\n]*", out)
        print(f"{role}: {' '.join(seen)}")
        print(f"{role}: {net}, exit {process.returncode}")
        first = seen.index("netplaylobby") if "netplaylobby" in seen else -1
        if seen[first:first + len(WALKED)] != WALKED:
            print(f"FAIL: {role} did not walk {WALKED}")
            passed = False
        if not any(" 0 desyncs" in line for line in net):
            print(f"FAIL: {role} has no clean match report")
            passed = False
    return passed


def main():
    daybreak, install = sys.argv[1], sys.argv[2]
    if not (pathlib.Path(install) / "daybreak00.dat").exists():
        print("SKIP: no install")
        return 77
    failed = False
    with tempfile.TemporaryDirectory() as name:
        # Everyone pressing: four players walk the loop.
        print("--- four players, every one pressing")
        if not walk(daybreak, install, 4, True, True, pathlib.Path(name), "all-press"):
            failed = True
        # Only the host pressing: the joiner's result screen must follow it back to the room.
        print("--- two players, only the host presses after the round")
        if not walk(daybreak, install, 2, True, False, pathlib.Path(name), "one-press"):
            failed = True
    print("online_flow_check: failed" if failed else "online_flow_check: ok")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
