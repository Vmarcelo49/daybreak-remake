#!/usr/bin/env python3
"""Online play (docs/ONLINE-PLAN.md, step 4): real instances over a bad localhost network.

Agreement between peers, not with the original. Skips without an install.
"""
import json
import pathlib
import shutil
import signal
import socket
import subprocess
import sys
import tempfile
import time

TICKS = 10000
PROXY = pathlib.Path(__file__).resolve().parents[1] / "tools" / "net_proxy.py"
SERVER_SOURCE = pathlib.Path(__file__).resolve().parents[1] / "server"


def free_port():
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as probe:
        probe.bind(("127.0.0.1", 0))
        return probe.getsockname()[1]


def start_proxy():
    port = free_port()
    process = subprocess.Popen([sys.executable, str(PROXY), "--port", str(port), "--delay-ms", "100", "--jitter-ms", "10",
                                "--loss", "0.05", "--duplicate", "0.01"])
    return process, f"127.0.0.1:{port}"


def start_peers(netctl, game, folder, count, ticks, time_limit=None):
    proxy, address = start_proxy()
    port = free_port()
    common = ["--game", game, "--ticks", str(ticks), "--proxy", address]
    peers = []
    logs = []
    for peer in range(count):
        log = folder / f"{count}-{ticks}-{peer}.log"
        logs.append(log)
        role = ["--host", str(port), "--peers", str(count), "--seed", str(count * 11 + 3)] if peer == 0 else ["--join", f"127.0.0.1:{port}"]
        if time_limit:
            role += ["--time-limit", str(time_limit)]
        peers.append(subprocess.Popen([netctl, *role, *common, "--log", str(log)], stdout=subprocess.PIPE, text=True))
        time.sleep(0.1)
    return proxy, peers, logs


def result_of(out):
    # GekkoNet prints notices of its own to stdout.
    return json.loads([line for line in out.splitlines() if line.startswith("{")][-1])


def read_log(path):
    return dict(line.split() for line in pathlib.Path(path).read_text().splitlines())


def compare(logs, name):
    tables = [read_log(path) for path in logs]
    common = set(tables[0]).intersection(*tables[1:])
    assert len(common) > 0, f"{name}: no frame in common"
    for key in common:
        values = {table[key] for table in tables}
        assert len(values) == 1, f"{name}: frame {key} differs: {values}"
    return len(common)


def full_match(netctl, game, folder, count):
    proxy, peers, logs = start_peers(netctl, game, folder, count, TICKS, time_limit=60)
    try:
        results = []
        for peer in peers:
            out, _ = peer.communicate(timeout=TICKS / 60 + 150)
            print(f"{count} peers: {result_of(out)}")
            assert peer.returncode == 0, f"{count} peers: a peer failed"
            results.append(result_of(out))
    finally:
        proxy.kill()
    frames = compare(logs, f"{count} peers")
    assert frames > TICKS - 50, f"{count} peers: only {frames} frames compared"
    assert all(r["desyncs"] == 0 for r in results)
    assert sum(r["rollbacks"] for r in results) > 0, f"{count} peers: the network never caused a rollback"
    assert len({r["round_over"] for r in results}) == 1, f"{count} peers: the round ended on different frames"
    assert results[0]["round_over"] > 0, f"{count} peers: the round never ended"
    print(f"{count} peers: {frames} frames equal, round over at {results[0]['round_over']}")


def dropped_peer(netctl, game, folder):
    proxy, peers, logs = start_peers(netctl, game, folder, 4, 1500)
    try:
        time.sleep(8)
        peers[2].send_signal(signal.SIGKILL)
        peers[2].wait()
        results = []
        for index, peer in enumerate(peers):
            if index == 2:
                continue
            out, _ = peer.communicate(timeout=120)
            print(f"dropped peer: {result_of(out)}")
            assert peer.returncode == 0, "dropped peer: a survivor failed"
            results.append(result_of(out))
    finally:
        proxy.kill()
    survivors = [log for index, log in enumerate(logs) if index != 2]
    frames = compare(survivors, "dropped peer")
    assert all(r["slots"] == "HCHH" for r in results), f"dropped peer: its slot is not COM: {results}"
    assert all(r["disconnects"] == 1 for r in results), f"dropped peer: {results}"
    assert frames > 1400, f"dropped peer: only {frames} frames compared"
    print(f"dropped peer: {frames} frames equal, its slot is COM")


def build_server(folder):
    """The rendezvous server, or None without a Go toolchain."""
    go = shutil.which("go")
    if not go:
        return None
    binary = folder / "daybreak-rendezvous"
    subprocess.run([go, "build", "-o", str(binary), "."], cwd=SERVER_SOURCE, check=True)
    return binary


def by_room_code(netctl, game, folder, server_binary):
    port = free_port()
    server = subprocess.Popen([str(server_binary), "-addr", f"127.0.0.1:{port}", "-log", "error"])
    address = f"127.0.0.1:{port}"
    peers = []
    try:
        time.sleep(0.3)
        logs = [folder / f"code-{peer}.log" for peer in range(4)]
        common = ["--game", game, "--ticks", "900", "--server", address]
        peers.append(subprocess.Popen([netctl, "--host", str(free_port()), "--peers", "4", "--seed", "5", *common, "--log", str(logs[0])],
                                      stdout=subprocess.PIPE, text=True))
        line = peers[0].stdout.readline()
        code = json.loads(line)["code"]
        wrong = subprocess.run([netctl, "--join-code", "ZZZZ" if code != "ZZZZ" else "YYYY", *common], stdout=subprocess.PIPE, text=True, timeout=30)
        assert wrong.returncode == 3 and "No room has that code" in wrong.stdout, f"a wrong code: {wrong.stdout}"
        for peer in range(1, 4):
            peers.append(subprocess.Popen([netctl, "--join-code", code, *common, "--log", str(logs[peer])], stdout=subprocess.PIPE, text=True))
        results = []
        for peer in peers:
            out, _ = peer.communicate(timeout=120)
            assert peer.returncode == 0, f"room code: a peer failed: {out}"
            results.append(result_of(out))
    finally:
        for peer in peers:
            if peer.poll() is None:
                peer.kill()
        server.kill()
    frames = compare(logs, "room code")
    assert all(r["desyncs"] == 0 for r in results)
    assert frames > 800, f"room code: only {frames} frames compared"
    print(f"room code {code}: 4 peers, {frames} frames equal")


def refused(netctl, game):
    port = free_port()
    host = subprocess.Popen([netctl, "--host", str(port), "--peers", "2", "--game", game], stdout=subprocess.PIPE, text=True)
    try:
        joiner = subprocess.run([netctl, "--join", f"127.0.0.1:{port}", "--game", game, "--game-hash", "1"],
                                stdout=subprocess.PIPE, text=True, timeout=30)
    finally:
        host.kill()
        host.wait()
    print(f"refused: {joiner.stdout.strip()}")
    assert joiner.returncode == 3, "different game data was not refused"
    assert "different game data" in joiner.stdout


def main():
    netctl, game = sys.argv[1], sys.argv[2]
    if not (pathlib.Path(game) / "daybreak00.dat").exists():
        print("SKIP: no install")
        return 77
    with tempfile.TemporaryDirectory() as folder_name:
        folder = pathlib.Path(folder_name)
        refused(netctl, game)
        server_binary = build_server(folder)
        if server_binary:
            by_room_code(netctl, game, folder, server_binary)
        else:
            print("room code: not run, no Go toolchain")
        dropped_peer(netctl, game, folder)
        full_match(netctl, game, folder, 2)
        full_match(netctl, game, folder, 4)
    print("net_play_check: ok")
    return 0


if __name__ == "__main__":
    sys.exit(main())
