#!/usr/bin/env python3
"""Runs tests/update_http_test against tests/http_fixture.py (issue #100).

CTest cannot hand the binary a live server, so this wrapper starts the fixture on an
ephemeral port, passes its base URL, and stops it afterwards.
"""
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import http_fixture  # noqa: E402


def main():
    if len(sys.argv) != 2:
        print("usage: run_update_http_test.py <update_http_test binary>", file=sys.stderr)
        return 2
    server, _thread, base_url = http_fixture.start()
    try:
        completed = subprocess.run([sys.argv[1], base_url])
        return completed.returncode
    finally:
        server.shutdown()
        server.server_close()


if __name__ == "__main__":
    sys.exit(main())
