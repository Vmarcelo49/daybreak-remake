#!/usr/bin/env python3
"""Exercise result-screen revocation after asymmetric confirmation loss."""
import pathlib
import socket
import sys
import tempfile

def relay_packets(port):
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
        sock.bind(("127.0.0.1", port))
        while True:
            packet, sender = sock.recvfrom(2048)
            if len(packet) < 6:
                continue
            # Drop the host's seals, but deliver offers, aborts and acknowledgements.
            if len(packet) >= 13 and packet[6] == ord('O') and packet[11] == 0 and packet[12] == 2:
                continue
            target = (socket.inet_ntoa(packet[:4]), int.from_bytes(packet[4:6], "big"))
            framed = socket.inet_aton(sender[0]) + sender[1].to_bytes(2, "big") + packet[6:]
            sock.sendto(framed, target)


if __name__ == "__main__":
    from online_flow_check import result_race

    if not (pathlib.Path(sys.argv[2]) / "daybreak00.dat").exists():
        print("SKIP: no install")
        sys.exit(77)
    with tempfile.TemporaryDirectory() as name:
        sys.exit(0 if result_race(sys.argv[1], sys.argv[2], pathlib.Path(name)) else 1)
