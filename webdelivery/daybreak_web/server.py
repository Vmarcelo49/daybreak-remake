"""The same-origin HTTP surface: the client, the catalog, and one asset at a time.

What it serves, and why each piece exists:

    /                     a tiny index that points at the client
    /client/<file>        the built web client (wasm, js, html) — same origin
    /api/health           catalog identity + counts, for the client's probe
    /api/catalog          the versioned catalog (JSON, ETag/304)
    /api/manifest/startup the startup group as a per-asset manifest
    /api/manifest/match   the match group for a confirmed stage + fighters + weapons
    /api/asset/<id>       one catalogued asset, ETag from its sha256, gzip when it helps

Two rules are load-bearing:

  * **Only catalogued ids are reachable.** The request path is looked up in the
    catalog and the file served is ``prepared_dir / catalog_id`` — the client's
    own bytes never reach the filesystem, so there is no traversal to defend
    against and no way to name a file the prepare step did not vouch for.
  * **The client is not the source of truth about what it may ask for.** The
    manifests come from the catalog; a browser that asks for a match's assets
    asks for exactly the ids the loader scopes cover.

Nothing here is a general-purpose file server, and nothing here is multi-user:
one host, their own install, one origin (issue #4's non-scope).
"""

from __future__ import annotations

import json
import mimetypes
import posixpath
import threading
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
from urllib.parse import parse_qs, unquote, urlparse

from . import catalog as catalog_mod
from .bundles import ascii_fold

#: Types the browser needs exactly right; the rest falls back to mimetypes.
CONTENT_TYPES = {
    ".js": "text/javascript",
    ".wasm": "application/wasm",
    ".html": "text/html; charset=utf-8",
    ".data": "application/octet-stream",
    ".css": "text/css; charset=utf-8",
    ".json": "application/json",
}

INDEX_HTML = """<!doctype html>
<meta charset="utf-8">
<title>Higurashi Daybreak — self-hosted web</title>
<body style="font:14px system-ui;background:#111;color:#ddd;padding:2rem">
<h1>Higurashi Daybreak — self-hosted web delivery</h1>
<p>The web client is served from this same origin; the assets come from your own
installation, prepared once.</p>
<p><a style="color:#8cf" href="/client/daybreak.html?delivery=1">Start the client</a></p>
<p>Catalog: <a style="color:#8cf" href="/api/catalog">/api/catalog</a> ·
health: <a style="color:#8cf" href="/api/health">/api/health</a> ·
startup manifest: <a style="color:#8cf" href="/api/manifest/startup">/api/manifest/startup</a></p>
<p id="status">checking…</p>
<script>
fetch('/api/health').then(r => r.json()).then(h => {
  document.getElementById('status').textContent =
    h.ok ? `${h.assets} assets prepared, catalog ${h.catalogVersion.slice(0, 12)}…`
         : 'not prepared: ' + h.error;
}).catch(e => { document.getElementById('status').textContent = 'health check failed: ' + e; });
</script>
"""


class DeliveryState:
    """Everything the handlers read, built once at startup."""

    def __init__(self, prepared_dir: Path, client_dir: Path | None, install_dir: Path | None):
        self.prepared_dir = Path(prepared_dir)
        self.client_dir = Path(client_dir) if client_dir else None
        self.install_dir = Path(install_dir) if install_dir else None
        self.lock = threading.Lock()
        self.catalog: dict | None = None
        self.error = ""
        self.by_id: dict[str, dict] = {}
        self.by_fold: dict[str, str] = {}
        self.reload()

    def reload(self) -> None:
        try:
            catalog = catalog_mod.load_catalog(self.prepared_dir)
        except (FileNotFoundError, ValueError) as exc:
            with self.lock:
                self.catalog = None
                self.by_id = {}
                self.by_fold = {}
                self.error = str(exc)
            return
        by_id = {asset["id"]: asset for asset in catalog["assets"]}
        by_fold = {}
        for asset_id in by_id:
            by_fold.setdefault(ascii_fold(asset_id), asset_id)
        with self.lock:
            self.catalog = catalog
            self.by_id = by_id
            self.by_fold = by_fold
            self.error = ""

    def install_is_stale(self) -> str:
        """Empty when compatible; otherwise the reason to report as 409.

        Only checked when the install is mounted into the serving container: the
        usual deployment serves from the prepared volume alone, and a host who
        re-ran prepare against a new install will see the new catalog anyway.
        """
        if not self.install_dir or self.catalog is None:
            return ""
        fingerprint = catalog_mod.install_fingerprint(self.install_dir)
        if not catalog_mod.fingerprint_matches(self.catalog, fingerprint):
            return ("the mounted install does not match the prepared catalog; "
                    "re-run prepare")
        return ""

    def asset(self, raw_id: str) -> dict | None:
        with self.lock:
            if raw_id in self.by_id:
                return self.by_id[raw_id]
            folded = self.by_fold.get(ascii_fold(raw_id))
            return self.by_id[folded] if folded else None


class Handler(BaseHTTPRequestHandler):
    server_version = "daybreak-webdelivery/1"
    protocol_version = "HTTP/1.1"

    state: DeliveryState          # set on the server class before serving

    def log_message(self, fmt, *args):        # one line per request, to stdout
        print("[webdelivery] %s - %s" % (self.address_string(), fmt % args), flush=True)

    # ------------------------------------------------------------------ helpers
    def _send(self, status: int, body: bytes, content_type: str, extra: dict | None = None):
        self.send_response(status)
        self.send_header("Content-Type", content_type)
        self.send_header("Content-Length", str(len(body)))
        for key, value in (extra or {}).items():
            self.send_header(key, value)
        self.end_headers()
        if self.command != "HEAD":
            self.wfile.write(body)

    def _json(self, status: int, payload: dict, extra: dict | None = None):
        body = (json.dumps(payload, indent=1) + "\n").encode("utf-8")
        self._send(status, body, "application/json", extra)

    def _error(self, status: int, code: str, message: str):
        self._json(status, {"error": message, "code": code})

    def _not_modified(self, etag: str):
        self.send_response(304)
        self.send_header("ETag", etag)
        self.send_header("Content-Length", "0")
        self.end_headers()

    # -------------------------------------------------------------------- verbs
    def do_GET(self):        # noqa: N802 - http.server's name
        self._route()

    def do_HEAD(self):       # noqa: N802
        self._route()

    def _route(self):
        parsed = urlparse(self.path)
        route = unquote(parsed.path)
        query = parse_qs(parsed.query)

        if route in ("/", "/index.html"):
            self._send(200, INDEX_HTML.encode("utf-8"), "text/html; charset=utf-8")
        elif route.startswith("/client/"):
            self._client_file(route[len("/client/"):])
        elif route == "/api/health":
            self._health()
        elif route == "/api/catalog":
            self._catalog()
        elif route == "/api/manifest/startup":
            self._manifest_startup()
        elif route == "/api/manifest/match":
            self._manifest_match(query)
        elif route.startswith("/api/asset/"):
            self._asset(route[len("/api/asset/"):], query)
        else:
            self._error(404, "no-route", f"no route for {route}")

    # ------------------------------------------------------------------ handlers
    def _client_file(self, relative: str):
        state = self.state
        if state.client_dir is None:
            self._error(404, "no-client", "this server was started without --client-dir")
            return
        # Containment: resolve inside the client directory only.
        safe = posixpath.normpath("/" + relative).lstrip("/")
        if safe.startswith("..") or "/../" in safe:
            self._error(400, "bad-path", "path escapes the client directory")
            return
        path = state.client_dir / safe
        if not path.is_file():
            self._error(404, "no-client-file", f"no client file {safe}")
            return
        content_type = CONTENT_TYPES.get(path.suffix) or \
            mimetypes.guess_type(path.name)[0] or "application/octet-stream"
        stat = path.stat()
        etag = f'"{int(stat.st_mtime)}-{stat.st_size}"'
        if self.headers.get("If-None-Match") == etag:
            self._not_modified(etag)
            return
        self._send(200, path.read_bytes(), content_type,
                   {"ETag": etag, "Cache-Control": "no-cache"})

    def _health(self):
        state = self.state
        stale = state.install_is_stale()
        if state.catalog is None:
            self._json(503, {"ok": False, "error": state.error or "not prepared"})
            return
        self._json(200, {
            "ok": not stale,
            "catalogVersion": state.catalog["catalogVersion"],
            "format": state.catalog["format"],
            "assets": state.catalog["counts"]["assets"],
            "rawBytes": state.catalog["counts"]["rawBytes"],
            "transferBytes": state.catalog["counts"]["transferBytes"],
            "precedence": state.catalog["precedence"],
            "error": stale,
        })

    def _catalog(self):
        state = self.state
        if state.catalog is None:
            self._error(409, "incompatible-install",
                        state.error or "no prepared catalog: run prepare against the install")
            return
        body = (json.dumps(state.catalog, indent=1, ensure_ascii=False) + "\n").encode("utf-8")
        etag = f'"{state.catalog["catalogVersion"]}"'
        if self.headers.get("If-None-Match") == etag:
            self._not_modified(etag)
            return
        self._send(200, body, "application/json",
                   {"ETag": etag, "Cache-Control": "no-cache"})

    def _manifest_startup(self):
        state = self.state
        if state.catalog is None:
            self._error(409, "incompatible-install", state.error or "not prepared")
            return
        stale = state.install_is_stale()
        if stale:
            self._error(409, "incompatible-install", stale)
            return
        ids = catalog_mod.startup_asset_ids(state.catalog)
        text = catalog_mod.manifest_text(state.catalog, ids, "startup")
        etag = f'"startup-{state.catalog["catalogVersion"]}"'
        if self.headers.get("If-None-Match") == etag:
            self._not_modified(etag)
            return
        self._send(200, text.encode("utf-8"), "text/plain; charset=utf-8",
                   {"ETag": etag, "Cache-Control": "no-cache"})

    def _manifest_match(self, query: dict):
        state = self.state
        if state.catalog is None:
            self._error(409, "incompatible-install", state.error or "not prepared")
            return
        stage = (query.get("stage") or [""])[0]
        slots = query.get("slot") or []
        weapons = query.get("weapon") or []
        if not stage or not slots:
            self._error(400, "bad-request",
                        "match manifest needs ?stage=<stageNN> and at least one &slot=<name[:costume]>")
            return
        try:
            label, ids = catalog_mod.match_manifest(state.catalog, stage, slots, weapons)
        except KeyError as exc:
            self._error(404, "unknown-asset", str(exc))
            return
        text = catalog_mod.manifest_text(state.catalog, ids, label)
        self._send(200, text.encode("utf-8"), "text/plain; charset=utf-8",
                   {"Cache-Control": "no-cache"})

    def _asset(self, raw_id: str, query: dict):
        state = self.state
        if state.catalog is None:
            self._error(409, "incompatible-install",
                        state.error or "no prepared catalog: run prepare against the install")
            return
        stale = state.install_is_stale()
        if stale:
            self._error(409, "incompatible-install", stale)
            return
        if not raw_id:
            self._error(400, "bad-request", "empty asset id")
            return
        asset = state.asset(raw_id)
        if asset is None:
            self._error(404, "unknown-asset",
                        f"{raw_id} is not in the catalog (only prepared ids are servable)")
            return

        accept = self.headers.get("Accept-Encoding", "")
        wants_gzip = asset.get("gzipSize") and "gzip" in accept.lower() and \
            query.get("raw", ["0"])[0] not in ("1", "true")
        path = catalog_mod.prepared_path(state.prepared_dir, asset, wants_gzip)
        try:
            body = path.read_bytes()
        except OSError as exc:
            self._error(500, "prepared-file-missing",
                        f"{asset['id']} is catalogued but not on the volume: {exc}")
            return
        if len(body) != (asset["gzipSize"] if wants_gzip else asset["size"]):
            self._error(500, "prepared-file-wrong-size",
                        f"{asset['id']} on the volume does not match the catalog; re-run prepare")
            return

        etag = f'"{asset["sha256"]}{"-gz" if wants_gzip else ""}"'
        headers = {
            "ETag": etag,
            # Content-addressed: the id's bytes can never change under this URL
            # without the catalog changing, and a changed catalog means a changed
            # sha256 means a different URL. That is what lets a browser keep an
            # asset independently of every other asset (plan Step 3).
            "Cache-Control": "public, max-age=31536000, immutable",
            "Vary": "Accept-Encoding",
        }
        if wants_gzip:
            headers["Content-Encoding"] = "gzip"
        if self.headers.get("If-None-Match") == etag:
            self._not_modified(etag)
            return
        self._send(200, body, CONTENT_TYPES.get(Path(asset["id"]).suffix)
                   or mimetypes.guess_type(asset["id"])[0] or "application/octet-stream",
                   headers)


def make_server(prepared_dir: Path, client_dir: Path | None = None,
                install_dir: Path | None = None, host: str = "0.0.0.0",
                port: int = 8080) -> ThreadingHTTPServer:
    state = DeliveryState(prepared_dir, client_dir, install_dir)
    handler = type("BoundHandler", (Handler,), {"state": state})
    server = ThreadingHTTPServer((host, port), handler)
    server.daemon_threads = True
    return server


def serve(prepared_dir: Path, client_dir: Path | None = None,
          install_dir: Path | None = None, host: str = "0.0.0.0",
          port: int = 8080) -> None:
    server = make_server(prepared_dir, client_dir, install_dir, host, port)
    state = server.RequestHandlerClass.state
    if state.catalog is None:
        print(f"[webdelivery] serving WITHOUT a catalog: {state.error}", flush=True)
    else:
        counts = state.catalog["counts"]
        print(f"[webdelivery] catalog {state.catalog['catalogVersion'][:12]}… "
              f"{counts['assets']} assets, {counts['rawBytes'] / 1e6:.1f} MB prepared "
              f"({counts['transferBytes'] / 1e6:.1f} MB over the wire)", flush=True)
    print(f"[webdelivery] listening on http://{host}:{port}/", flush=True)
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        pass
    finally:
        server.server_close()
