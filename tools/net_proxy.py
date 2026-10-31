#!/usr/bin/env python3
"""A bad network for online tests: delay, jitter, loss and duplication between local instances.

Each instance runs with --proxy. A packet arrives here as 4 bytes of IPv4, 2 of port (big-endian) and
the payload, and leaves for that address with the sender's address in the same 6-byte prefix.
"""
import argparse
import heapq
import random
import select
import socket
import time


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("--port", type=int, required=True)
    parser.add_argument("--delay-ms", type=float, default=0)
    parser.add_argument("--jitter-ms", type=float, default=0)
    parser.add_argument("--loss", type=float, default=0, help="fraction of packets lost, 0 to 1")
    parser.add_argument("--duplicate", type=float, default=0, help="fraction of packets sent twice, 0 to 1")
    parser.add_argument("--seed", type=int, default=1)
    args = parser.parse_args()

    random.seed(args.seed)
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind(("127.0.0.1", args.port))
    waiting = []
    order = 0
    while True:
        timeout = max(0, waiting[0][0] - time.monotonic()) if waiting else 0.1
        if select.select([sock], [], [], timeout)[0]:
            packet, sender = sock.recvfrom(2048)
            if len(packet) < 6 or random.random() < args.loss:
                continue
            target = (socket.inet_ntoa(packet[:4]), int.from_bytes(packet[4:6], "big"))
            framed = socket.inet_aton(sender[0]) + sender[1].to_bytes(2, "big") + packet[6:]
            for _ in range(2 if random.random() < args.duplicate else 1):
                delay = args.delay_ms + random.uniform(-args.jitter_ms, args.jitter_ms)
                order += 1
                heapq.heappush(waiting, (time.monotonic() + max(0, delay) / 1000, order, target, framed))
        now = time.monotonic()
        while waiting and waiting[0][0] <= now:
            _, _, target, framed = heapq.heappop(waiting)
            sock.sendto(framed, target)


if __name__ == "__main__":
    main()
