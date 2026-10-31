#!/usr/bin/env python3
"""Online play (docs/ONLINE-PLAN.md, step 6): two real games walk lobby, battle, results and lobby.

Headless, over localhost, with scripted buttons. Agreement between peers, not with the original.
"""
import pathlib
import re
import socket
import subprocess
import sys
import tempfile

FRAMES = 7000


def presses(start, stop, step=30):
    return [f"{tick} JUMP\n{tick + 6} -\n" for tick in range(start, stop, step)]


def host_script():
    # The cursor starts on START: up twice to the time limit, 60 seconds, and back down.
    lines = ["60 WAIT netplaylobby\n", "100 UP\n106 -\n112 UP\n118 -\n124 RIGHT\n130 -\n136 DOWN\n142 -\n148 DOWN\n154 -\n"]
    return "".join(lines + presses(200, FRAMES))


def join_script():
    lines = ["60 WAIT netplaylobby\n", "200 JUMP\n206 -\n", "300 WAIT result\n"]
    return "".join(lines + presses(310, FRAMES))


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
        common = ["--headless", "--no-audio", f"--install={install}", f"--frames={FRAMES}", "--size=640x360"]
        host = subprocess.Popen([daybreak, *common, f"--net-host={port}", f"--script={folder}/host.txt", f"--out={folder}/host.ppm"],
                                stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, errors="replace")
        join = subprocess.Popen([daybreak, *common, f"--net-join=127.0.0.1:{port}", f"--script={folder}/join.txt", f"--out={folder}/join.ppm"],
                                stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, errors="replace")
        failed = False
        for role, process in (("host", host), ("join", join)):
            out, _ = process.communicate(timeout=400)
            walk = scenes(out)
            net = re.findall(r"\[net\][^\n]*", out)
            print(f"{role}: {' '.join(walk)}")
            print(f"{role}: {net}, exit {process.returncode}")
            first = walk.index("netplaylobby") if "netplaylobby" in walk else -1
            wanted = ["netplaylobby", "vs", "result", "netplaylobby"]
            if walk[first:first + len(wanted)] != wanted:
                print(f"FAIL: {role} did not walk {wanted}")
                failed = True
            if not net or " 0 desyncs" not in net[0]:
                print(f"FAIL: {role} has no clean match report")
                failed = True
    print("online_flow_check: failed" if failed else "online_flow_check: ok")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
