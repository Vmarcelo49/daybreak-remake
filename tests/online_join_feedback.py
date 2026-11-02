#!/usr/bin/env python3
"""A join that cannot finish has to say why: each way of failing, from the real menu, by keyboard."""
import json
import pathlib
import socket
import subprocess
import sys
import tempfile
import time

SERVER_SOURCE = pathlib.Path(__file__).resolve().parents[1] / "server"
ROOM_CODE_ROW, ADDRESS_ROW, SERVER_ROW = 1, 2, 6
DEFAULT_SERVER_LENGTH = 19
# The menu reports a failed join after its first-contact silence (net::Lobby's
# kFirstContactMs), so the run only has to carry the script to the row and the wait out.
# 1000 frames covers that with margin; 1400 was 40% more wall time for nothing, and 700 was
# measured short (the first join had not reported yet).
FRAMES = 1000


def free_port():
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as probe:
        probe.bind(("127.0.0.1", 0))
        return probe.getsockname()[1]


def press(tick, key):
    return f"{tick} {key}\n{tick + 6} -\n"


def join(daybreak, install, folder, server, row, text, expected):
    """Point the menu at a server, write on a join row, and wait for the reason."""
    script, keys, tick = ["40 WAIT netplay\n"], [], 60
    position = 0
    if server:
        while position < SERVER_ROW:
            script.append(press(tick, "DOWN"))
            tick, position = tick + 20, position + 1
        script.append(press(tick, "JUMP"))
        keys.append(f"{tick + 20}:{'<bs>' * DEFAULT_SERVER_LENGTH}{server}<enter>")
        tick += 40
    while position != row:
        step = 1 if position < row else -1
        script.append(press(tick, "DOWN" if step > 0 else "UP"))
        tick, position = tick + 20, position + step
    script.append(press(tick, "JUMP"))
    keys.append(f"{tick + 20}:{text}<enter>")
    path = folder / "join.txt"
    path.write_text("".join(script))
    run = subprocess.run([daybreak, "--headless", "--no-audio", "--language=en", f"--install={install}", "--size=800x600",
                          "--screen=netplay", f"--frames={FRAMES}", f"--script={path}", f"--text-keys={','.join(keys)}",
                          f"--out={folder}/out.ppm"], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, timeout=120)
    reasons = [line for line in run.stdout.splitlines() if line.startswith("[online]")]
    scenes = [line.split()[2] for line in run.stdout.splitlines() if line.startswith("[menu] scene:")]
    assert run.returncode == 0, f"{expected}: exit {run.returncode}"
    assert reasons == [f"[online] {expected}"], f"{expected}: said {reasons}"
    assert scenes == ["netplay", "netplaylobby", "netplay"], f"{expected}: went {scenes}"
    print(f"ok: {expected}")


def main():
    daybreak, netctl, install = sys.argv[1], sys.argv[2], sys.argv[3]
    if not (pathlib.Path(install) / "daybreak00.dat").exists():
        print("SKIP: no install")
        return 77
    with tempfile.TemporaryDirectory() as name:
        folder = pathlib.Path(name)
        join(daybreak, install, folder, f"127.0.0.1:{free_port()}", ROOM_CODE_ROW, "abcd", "The server did not answer.")
        join(daybreak, install, folder, None, ADDRESS_ROW, f"127.0.0.1:{free_port()}", "Nobody answered at that address.")

        binary = folder / "daybreak-rendezvous"
        try:
            subprocess.run(["go", "build", "-o", str(binary), "."], cwd=SERVER_SOURCE, check=True)
        except (OSError, subprocess.CalledProcessError):
            print("room codes: not run, no Go toolchain")
            return 0
        port = free_port()
        address = f"127.0.0.1:{port}"
        server = subprocess.Popen([str(binary), "-addr", address, "-log", "error"])
        try:
            time.sleep(0.3)
            # A room whose host is gone stays on the server for a while: found, and nobody there.
            host = subprocess.Popen([netctl, "--host", str(free_port()), "--peers", "2", "--game", install, "--server", address],
                                    stdout=subprocess.PIPE, text=True)
            code = json.loads(host.stdout.readline())["code"]
            host.kill()
            host.wait()
            join(daybreak, install, folder, address, ROOM_CODE_ROW, code, "Room found, but the host did not answer.")
            wrong = "ZZZZ" if code != "ZZZZ" else "YYYY"
            join(daybreak, install, folder, address, ROOM_CODE_ROW, wrong, "No room has that code.")
        finally:
            server.kill()
    print("online_join_feedback: ok")
    return 0


if __name__ == "__main__":
    sys.exit(main())
