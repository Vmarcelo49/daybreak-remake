#!/usr/bin/env python3
"""A tiny local HTTP server for tests/update_http_test.cpp (issue #100).

Only what the HTTP seam's tests need: a body with a Content-Length, a redirect chain, a
404, a body larger than a caller's cap with and without a Content-Length, a slow trickle
the client can cancel, and a stall. Plain HTTP on 127.0.0.1 is the one exception the URL
policy allows, and only while DAYBREAK_UPDATE_TEST_HTTP=1.
"""
import threading
import time
from pathlib import Path
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer

BODY = b"hello update"


class Handler(BaseHTTPRequestHandler):
    protocol_version = "HTTP/1.1"

    def log_message(self, *args):  # keep CTest output readable
        pass

    def _serve_file(self, path):
        root = Path(self.server.root).resolve()
        target = (root / path.lstrip("/")).resolve()
        if root not in target.parents and target != root:
            self._send(404)
            return
        if not target.is_file():
            self._send(404)
            return
        self._send(200, target.read_bytes())

    def _send(self, status, body=b"", headers=()):
        self.send_response(status)
        for name, value in headers:
            self.send_header(name, value)
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        if body:
            self.wfile.write(body)

    def do_GET(self):  # noqa: N802 - BaseHTTPRequestHandler's name
        self.server.requests.append(self.path)
        path = self.path.split("?")[0]
        if getattr(self.server, "root", None) is not None and not path.startswith(
            ("/ok", "/redirect/", "/missing", "/big", "/chunked", "/slow", "/stall")
        ):
            self._serve_file(path)
            return
        if self.path == "/ok":
            self._send(200, BODY)
        elif self.path.startswith("/redirect/"):
            count = int(self.path.rsplit("/", 1)[1])
            if count > 0:
                self._send(302, headers=[("Location", "/redirect/%d" % (count - 1))])
            else:
                self._send(200, BODY)
        elif self.path == "/missing":
            self._send(404)
        elif self.path == "/big":
            self._send(200, b"x" * 4096)
        elif self.path == "/chunked":
            self.send_response(200)
            self.send_header("Transfer-Encoding", "chunked")
            self.end_headers()
            for _ in range(4):
                chunk = b"y" * 1024
                self.wfile.write(b"%x\r\n" % len(chunk) + chunk + b"\r\n")
            self.wfile.write(b"0\r\n\r\n")
        elif self.path == "/slow":
            self.send_response(200)
            self.send_header("Content-Length", "1000")
            self.end_headers()
            for _ in range(10):
                self.wfile.write(b"z" * 100)
                self.wfile.flush()
                time.sleep(0.1)
        elif self.path == "/stall":
            self.send_response(200)
            self.send_header("Content-Length", "100")
            self.end_headers()
            self.wfile.flush()
            time.sleep(3)
        else:
            self._send(404)


class Server(ThreadingHTTPServer):
    daemon_threads = True

    def handle_error(self, request, client_address):
        # A cancelled transfer closes the socket under the handler; that is the test
        # working, not a failure worth a traceback.
        pass


def start(host="127.0.0.1", port=0, root=None):
    """Serve the fixed routes, and (with `root`) any other path from that directory."""
    server = Server((host, port), Handler)
    server.root = root
    server.requests = []
    thread = threading.Thread(target=server.serve_forever, daemon=True)
    thread.start()
    return server, thread, "http://%s:%d" % (host, server.server_address[1])
