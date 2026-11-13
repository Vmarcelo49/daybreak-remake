#!/usr/bin/env python3
"""Real GekkoNet battles and outcome messages through a lossy UDP proxy."""
import json
import pathlib
import socket
import subprocess
import sys
import time


def port():
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
        sock.bind(("127.0.0.1", 0))
        return sock.getsockname()[1]


def run(netctl, game, corrupt):
    proxy_port, host_port = port(), port()
    proxy = pathlib.Path(__file__).resolve().parents[1] / "tools" / "net_proxy.py"
    relay = subprocess.Popen([sys.executable, str(proxy), "--port", str(proxy_port), "--delay-ms", "80",
                              "--jitter-ms", "15", "--loss", "0.08", "--seed", "9"])
    peers = []
    try:
        time.sleep(0.2)
        common = ["--game", game, "--ticks", "2200", "--time-limit", "20", "--proxy", f"127.0.0.1:{proxy_port}", "--test-outcome"]
        peers.append(subprocess.Popen([netctl, "--host", str(host_port), "--peers", "2", *common,
                                       *(["--test-corrupt-frame", "120"] if corrupt else [])],
                                      stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True))
        peers.append(subprocess.Popen([netctl, "--join", f"127.0.0.1:{host_port}", *common],
                                      stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True))
        results = []
        for peer in peers:
            output, _ = peer.communicate(timeout=100)
            print(output)
            assert peer.returncode == 0, "peer failed"
            results.append(json.loads([line for line in output.splitlines() if line.startswith('{')][-1]))
        expected = "desync" if corrupt else "valid"
        assert all(result["outcome"] == expected for result in results), results
        if not corrupt:
            assert sum(result["rollbacks"] for result in results) > 0, results
        else:
            assert sum(result["desyncs"] for result in results) > 0, results
            assert any(result["abort_acknowledged"] for result in results), results
    finally:
        for peer in peers:
            if peer.poll() is None:
                peer.kill()
                peer.wait()
        relay.terminate()
        relay.wait()


if __name__ == "__main__":
    if not (pathlib.Path(sys.argv[2]) / "daybreak00.dat").exists():
        print("SKIP: no install")
        sys.exit(77)
    run(sys.argv[1], sys.argv[2], True)
    run(sys.argv[1], sys.argv[2], False)
    print("battle_outcome_network: ok")
