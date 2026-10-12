#!/usr/bin/env python3
"""Local typed client for an explicitly enabled match; never evaluates commands."""
import argparse
import json
import os
from pathlib import Path
import socket
import stat


class Client:
    def __init__(self, directory):
        self.directory = Path(directory).resolve()
        info = self.directory.stat()
        if info.st_uid != os.getuid() or stat.S_IMODE(info.st_mode) != 0o700:
            raise ValueError("debug directory must be owned by this user and mode 0700")
        pid, token = (self.directory / "session").read_text().splitlines()
        self.pid = int(pid)
        self.token = token
        self.socket = socket.socket(socket.AF_UNIX)
        self.socket.settimeout(30)
        self.socket.connect(str(self.directory / "control.sock"))
        import struct
        peer_pid, peer_uid, _ = struct.unpack("3i", self.socket.getsockopt(socket.SOL_SOCKET, socket.SO_PEERCRED, 12))
        if peer_pid != self.pid or peer_uid != os.getuid():
            self.socket.close()
            raise ValueError("session process identity mismatch")
        self.stream = self.socket.makefile("rb")
        self.command("HELLO " + token)

    def command(self, command):
        if "\n" in command or "\r" in command:
            raise ValueError("one protocol command required")
        self.socket.sendall(command.encode("ascii") + b"\n")
        line = self.stream.readline(65537)
        if not line or len(line) > 65536:
            raise ValueError("disconnected or oversized response")
        result = json.loads(line)
        if "error" in result:
            raise ValueError(result["error"])
        if "session" in result and result["session"] != self.token:
            raise ValueError("stale session")
        return result

    def close(self):
        self.stream.close()
        self.socket.close()


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("session", help="exact private session directory printed by the game")
    p.add_argument("--output", type=Path, help="save client-side JSON transcript")
    args = p.parse_args()
    client = Client(args.session)
    records = []
    print("Attached to process", client.pid, "(disconnect freezes and clears scheduled input)")
    print("Commands: status, pause, resume, step N, input F SPAN ACTIONS, break KIND F VALUE CHAR ITEM, clear, detach")
    try:
        while True:
            line = input("> ").strip()
            if not line:
                continue
            op, *rest = line.split()
            if op not in {"status", "pause", "resume", "step", "input", "break", "clear", "detach", "stop"}:
                print("Unknown typed command")
                continue
            command = op.upper() + (" " + " ".join(rest) if rest else "")
            try:
                result = client.command(command)
                records.append({"command": command, "result": result})
                print(json.dumps(result, indent=2))
            except ValueError as e:
                print(e)
            if op in {"detach", "stop"}:
                break
    except (EOFError, KeyboardInterrupt):
        pass
    finally:
        client.close()
        if args.output:
            args.output.write_text(json.dumps(records, indent=2) + "\n")


if __name__ == "__main__":
    main()
