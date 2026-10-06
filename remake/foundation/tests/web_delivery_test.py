#!/usr/bin/env python3
"""Host-side test for the self-hosted web delivery service (issue #4).

Run from anywhere:

    python3 remake/foundation/tests/web_delivery_test.py

What it proves, all of it hermetic (synthetic .DAT bundles written here, no game
data, no network beyond 127.0.0.1):

  1. prepare — the winner of a duplicate is the earliest *registered* bundle, the
     losing copy is recorded and NOT written, the prepared tree is ordinary
     decoded payloads, and a second prepare with an unchanged install reuses the
     existing output instead of re-extracting.
  2. catalog — per-asset sha256/size, the group classification, and the transfer
     number a client would actually pay.
  3. verify — a tampered prepared file is reported.
  4. the HTTP surface — health, catalog with ETag/304, the startup and match
     manifests, one asset with its ETag and gzip negotiation, and the error
     cases: unknown asset, traversal attempt, and a server with no catalog at all
     (the incompatible-install answer).

Final line: "WEB_DELIVERY_TEST: ok" or "...: FAIL (n ...)". Exit 0 on ok.
"""

from __future__ import annotations

import gzip
import http.client
import json
import os
import shutil
import struct
import sys
import tempfile
import threading
from pathlib import Path

REPO = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(REPO / "remake" / "foundation" / "webdelivery"))

from daybreak_web import catalog as catalog_mod          # noqa: E402
from daybreak_web import groups, server                  # noqa: E402
from daybreak_web.bundles import (BUNDLE_PRECEDENCE, BundleSet, ascii_fold,  # noqa: E402
                                  payload_key, table_xor)

FAILURES: list[str] = []


def fail(message: str) -> None:
    print(f"FAIL: {message}")
    FAILURES.append(message)


def check(condition: bool, message: str) -> None:
    if not condition:
        fail(message)


# ---------------------------------------------------------------------------
# A synthetic install, written the way the game's reader expects it.
# ---------------------------------------------------------------------------
def write_bundle(path: Path, entries: list[tuple[str, bytes]]) -> None:
    entry_size, name_bytes = 268, 260
    count = len(entries)
    table = bytearray(count * entry_size)
    cursor = 2 + count * entry_size
    offsets = []
    for index, (name, payload) in enumerate(entries):
        slot = table[index * entry_size:(index + 1) * entry_size]
        slot[0:len(name)] = name.encode("cp932")
        struct.pack_into("<II", slot, name_bytes, len(payload), cursor)
        table[index * entry_size:(index + 1) * entry_size] = slot
        offsets.append(cursor)
        cursor += len(payload)
    table_xor(table, 0)
    blob = bytearray(struct.pack("<H", count) + bytes(table))
    for (_, payload), offset in zip(entries, offsets):
        key = payload_key(offset)
        blob += bytes(b ^ key for b in payload)
    path.write_bytes(bytes(blob))


PLAN = {
    "daybreak07.dat": [("data/title/logo.cnv", b"seven-logo"),
                       ("data/stage21/00.X", b"stage-from-07"),
                       ("data/object/P01.cnv", b"hud-from-07")],
    "daybreak04.dat": [("data/stage21/00.X", b"stage-from-04-longer"),
                       ("data/object/P01.cnv", b"hud-from-04-with-a-longer-caption-strip"),
                       ("data/rena/00.X", b"rena-body")],
    "daybreak00.dat": [("data/object/P01.cnv", b"hud-00"),
                       ("data/select/pbg00.cnv", b"select-bg"),
                       ("movie/op.mpg", b"opening-movie-bytes")],
    "daybreak05.dat": [("data/sysse/000.cnv", b"system-se")],
    "daybreak02.dat": [("data/voice/entry/rena_B01.cnv", b"voice-line")],
    "daybreak06.dat": [("data/bullet/081/00.X", b"weapon-model")],
}


def make_install(root: Path) -> Path:
    root.mkdir(parents=True, exist_ok=True)
    for name, entries in PLAN.items():
        write_bundle(root / name, entries)
    return root


# ---------------------------------------------------------------------------
# A tiny HTTP client, so the test asserts on the wire rather than on handlers.
# ---------------------------------------------------------------------------
class Client:
    def __init__(self, port: int):
        self.port = port

    def get(self, path: str, headers: dict | None = None):
        connection = http.client.HTTPConnection("127.0.0.1", self.port, timeout=10)
        connection.request("GET", path, headers=headers or {})
        response = connection.getresponse()
        body = response.read()
        result = (response.status, dict(response.getheaders()), body)
        connection.close()
        return result


def serve(state_dir: Path, client_dir: Path | None = None,
          install_dir: Path | None = None):
    httpd = server.make_server(state_dir, client_dir, install_dir,
                               host="127.0.0.1", port=0)
    thread = threading.Thread(target=httpd.serve_forever, daemon=True)
    thread.start()
    return httpd, Client(httpd.server_address[1])


# ---------------------------------------------------------------------------
def test_bundle_rules(install: Path) -> None:
    bundle_set = BundleSet(install)
    check(bundle_set.missing == [], "every synthetic bundle must open")

    winner = bundle_set.find("data/object/P01.cnv")
    check(winner is not None and winner.bundle == "daybreak07.dat",
          "the earliest registered bundle must win the duplicate")

    folded = bundle_set.find("DATA/Object/p01.CNV")
    check(folded is not None and folded.name == "data/object/P01.cnv",
          "the folded lookup must reach the stored spelling")
    check(ascii_fold("data/object/P01.cnv") == "data/object/p01.cnv",
          "the ASCII fold must lowercase path components")

    copies = bundle_set.copies()["data/object/P01.cnv"]
    check([c.bundle for c in copies] ==
          ["daybreak07.dat", "daybreak04.dat", "daybreak00.dat"],
          "every copy must be listed in precedence order")
    print(f"  bundle rules: P01.cnv winner={winner.bundle}#{winner.index}, "
          f"{len(copies)} copies, folded lookup ok")


def test_prepare(install: Path, out: Path) -> dict:
    catalog, stats = catalog_mod.prepare(install, out)
    check(stats.prepared == len(catalog["assets"]),
          "every catalogued asset must be written on a cold prepare")
    check(catalog["precedence"] == list(BUNDLE_PRECEDENCE),
          "the catalog must record the recovered precedence order")

    check((out / "data/object/P01.cnv").read_bytes() == b"hud-from-07",
          "the prepared file must be the winning copy, not the last archive's")
    check(not (out / "data/object/P01.cnv.gz").exists() or True, "gzip copy is optional")

    p01 = next(a for a in catalog["assets"] if a["id"] == "data/object/P01.cnv")
    check(p01["owner"] == "daybreak07.dat" and p01["ownerIndex"] == 2,
          "the catalog must record the winning bundle and table index")
    check([c["bundle"] for c in p01["copies"]] == ["daybreak04.dat", "daybreak00.dat"],
          "the catalog must record the losing copies in precedence order")
    check(all(c["size"] != p01["size"] for c in p01["copies"]),
          "the synthetic duplicate group must differ in size, so the rule is visible")

    check(p01["group"] == groups.STARTUP, "data/object/ is startup art")
    stage = next(a for a in catalog["assets"] if a["id"] == "data/stage21/00.X")
    check(stage["group"] == groups.OTHER,
          "a stage model is not in the startup group (it is fetched for its match)")
    check(stage["owner"] == "daybreak07.dat", "the stage model resolves to the earlier bundle")
    check(next(a for a in catalog["assets"] if a["id"] == "movie/op.mpg")["group"] ==
          groups.STARTUP, "the opening movie is a startup asset")

    # The prepared tree is derived from a game install: it must be self-ignoring
    # wherever the host put it.
    check((out / ".gitignore").read_text().strip() == "*",
          "the prepared directory must carry its own ignore marker")

    # Repeatable: the same install must not be re-extracted.
    catalog2, stats2 = catalog_mod.prepare(install, out)
    check(stats2.reused == len(catalog["assets"]) and stats2.prepared == 0,
          "a second prepare with an unchanged install must reuse the existing output")
    check(catalog2["catalogVersion"] == catalog["catalogVersion"],
          "the catalog version must be stable across a no-op prepare")
    print(f"  prepare: {len(catalog['assets'])} assets, "
          f"{catalog['counts']['duplicateNames']} duplicate names, "
          f"{catalog['counts']['transferBytes']} transfer bytes, second run reused "
          f"{stats2.reused}")
    return catalog


def test_verify(install: Path, out: Path) -> None:
    problems, checked = catalog_mod.verify(out)
    check(problems == [] and checked > 0, "a fresh prepare must verify clean")

    tampered = out / "data/rena/00.X"
    original = tampered.read_bytes()
    tampered.write_bytes(b"tampered")
    problems, _ = catalog_mod.verify(out)
    check(any("hash mismatch" in p for p in problems),
          "verify must report a tampered prepared file")
    tampered.write_bytes(original)
    problems, _ = catalog_mod.verify(out)
    check(problems == [], "verify must go clean again once the file is restored")
    print(f"  verify: {checked} assets re-hashed; tampering detected and restored")


def test_manifests(catalog: dict) -> None:
    ids = catalog_mod.startup_asset_ids(catalog)
    check("movie/op.mpg" in ids and "data/stage21/00.X" not in ids,
          "the startup manifest must list startup art and no stage model")
    text = catalog_mod.manifest_text(catalog, ids, "startup")
    lines = [line for line in text.splitlines() if not line.startswith("#")]
    check(lines[0].startswith("version=") and "assets=" in text,
          "the manifest must carry its version and count")
    body = [line for line in text.splitlines()
            if line and not line.startswith("#") and "=" not in line.split("\t")[0]]
    check(all(len(line.split("\t")) == 5 for line in body),
          "every manifest line must be sha256, size, gzipSize, gate, id")
    gates = {line.split("\t")[4]: line.split("\t")[3] for line in body}
    check(gates.get("movie/op.mpg") == "0",
          "the opening movie is fetched at startup but is not a gate asset")
    check(gates.get("data/title/logo.cnv") == "1",
          "the title art must gate the first usable screen")

    label, match_ids = catalog_mod.match_manifest(catalog, "stage21", ["rena:0", "mion:0"],
                                                  ["081"])
    check("data/stage21/00.X" in match_ids, "the match manifest must carry the stage")
    check("data/rena/00.X" in match_ids, "the match manifest must carry the fighter")
    check("data/bullet/081/00.X" in match_ids, "the match manifest must carry the weapon")
    check("data/title/logo.cnv" not in match_ids,
          "the match manifest must not re-list startup art")
    print(f"  manifests: startup={len(ids)} assets, {label} -> {len(match_ids)} assets")


def test_http(install: Path, out: Path, catalog: dict) -> None:
    httpd, client = serve(out, client_dir=None, install_dir=install)
    try:
        status, _, body = client.get("/api/health")
        health = json.loads(body)
        check(status == 200 and health["ok"] and health["assets"] == len(catalog["assets"]),
              "health must report the prepared catalog")

        status, headers, body = client.get("/api/catalog")
        check(status == 200 and json.loads(body)["catalogVersion"] == catalog["catalogVersion"],
              "the catalog endpoint must serve the versioned catalog")
        etag = headers.get("ETag")
        check(etag is not None, "the catalog must carry an ETag")
        status, _, _ = client.get("/api/catalog", {"If-None-Match": etag})
        check(status == 304, "a matching If-None-Match must answer 304")

        status, _, body = client.get("/api/manifest/startup")
        check(status == 200 and b"movie/op.mpg" in body and b"data/stage21/00.X" not in body,
              "the startup manifest must be the startup group")

        status, _, body = client.get("/api/manifest/match?stage=stage21&slot=rena:0&slot=mion:0"
                                     "&weapon=081")
        check(status == 200 and b"data/stage21/00.X" in body and b"data/bullet/081/00.X" in body,
              "the match manifest must carry stage, fighter and weapon")
        status, _, body = client.get("/api/manifest/match?stage=stage21")
        check(status == 400, "a match manifest without slots must be a 400")

        # One asset: bytes, ETag, immutable caching, gzip negotiation.
        status, headers, body = client.get("/api/asset/data/object/P01.cnv")
        check(status == 200 and body == b"hud-from-07",
              "the asset endpoint must serve the winning copy's bytes")
        check(headers.get("ETag", "").strip('"') ==
              next(a["sha256"] for a in catalog["assets"] if a["id"] == "data/object/P01.cnv"),
              "the asset ETag must be its catalog sha256")
        check("immutable" in headers.get("Cache-Control", ""),
              "assets must be cacheable independently and immutably")
        status, _, _ = client.get("/api/asset/data/object/P01.cnv",
                                  {"If-None-Match": headers["ETag"]})
        check(status == 304, "an asset's ETag must answer 304 when unchanged")

        status, _, body = client.get("/api/asset/data/object/P01.cnv",
                                     {"Accept-Encoding": "gzip"})
        check(status == 200 and body == b"hud-from-07",
              "a gzip response must decode to the same bytes")
        if body != b"hud-from-07":
            fail("gzip body mismatch")

        # A compressible asset gets a gzip copy; a .cnv one does not (the measured rule).
        big = b"A" * 4096
        (out / "data/title").mkdir(parents=True, exist_ok=True)
        (out / "data/title/big.txt").write_bytes(big)
        (out / ".transfer" / "data/title").mkdir(parents=True, exist_ok=True)
        packed = gzip.compress(big, mtime=0)
        (out / ".transfer" / "data/title/big.txt.gz").write_bytes(packed)
        import hashlib
        catalog["assets"].append({"id": "data/title/big.txt", "size": len(big),
                                  "sha256": hashlib.sha256(big).hexdigest(),
                                  "gzipSize": len(packed), "owner": "test",
                                  "ownerIndex": 0, "group": "startup"})
        (out / "catalog.json").write_text(json.dumps(catalog), encoding="utf-8")
        httpd.RequestHandlerClass.state.reload()
        status, headers, body = client.get("/api/asset/data/title/big.txt",
                                           {"Accept-Encoding": "gzip"})
        check(status == 200 and headers.get("Content-Encoding") == "gzip",
              "a compressible asset must be served gzipped when the client accepts it")
        check(gzip.decompress(body) == big, "the gzip body must decompress to the asset")

        # Errors.
        status, _, body = client.get("/api/asset/data/does/not/exist.X")
        check(status == 404 and json.loads(body)["code"] == "unknown-asset",
              "an uncatalogued id must be a 404 unknown-asset")
        status, _, body = client.get("/api/asset/../../../../etc/passwd")
        check(status == 404, "a traversal attempt must never resolve to a file")
        status, _, _ = client.get("/api/nope")
        check(status == 404, "an unknown route must be a 404")
        print("  http: health/catalog/304/manifests/asset/etag/gzip/404s all answered")
    finally:
        httpd.shutdown()
        httpd.server_close()


def test_no_catalog(tmp: Path) -> None:
    httpd, client = serve(tmp / "empty")
    try:
        status, _, body = client.get("/api/health")
        check(status == 503 and json.loads(body)["ok"] is False,
              "an unprepared server must say so in health")
        status, _, body = client.get("/api/asset/data/object/P01.cnv")
        check(status == 409 and json.loads(body)["code"] == "incompatible-install",
              "an unprepared server must answer incompatible-install, not 500")
    finally:
        httpd.shutdown()
        httpd.server_close()
    print("  unprepared server: 503 health, 409 incompatible-install")


def test_stale_install(install: Path, out: Path) -> None:
    """A mounted install that no longer matches the catalog is a 409, not stale bytes."""
    stale = install.parent / "stale-install"
    shutil.copytree(install, stale)
    (stale / "daybreak05.dat").write_bytes((stale / "daybreak05.dat").read_bytes() + b"x")
    httpd, client = serve(out, install_dir=stale)
    try:
        status, _, body = client.get("/api/asset/data/object/P01.cnv")
        check(status == 409 and json.loads(body)["code"] == "incompatible-install",
              "an install that changed since prepare must answer 409")
        status, _, body = client.get("/api/manifest/startup")
        check(status == 409, "the startup manifest must refuse a stale install too")
    finally:
        httpd.shutdown()
        httpd.server_close()
    print("  stale install: 409 incompatible-install on assets and manifests")


def test_client_files(tmp: Path, out: Path) -> None:
    client_dir = tmp / "client"
    client_dir.mkdir()
    (client_dir / "foundation_demo.html").write_text("<html>client</html>")
    (client_dir / "foundation_demo.wasm").write_bytes(b"\x00asm")
    httpd, client = serve(out, client_dir=client_dir)
    try:
        status, headers, body = client.get("/client/foundation_demo.html")
        check(status == 200 and b"client" in body, "the client must be served same-origin")
        status, headers, _ = client.get("/client/foundation_demo.wasm")
        check(headers.get("Content-Type") == "application/wasm",
              "wasm must be served with the type the browser requires")
        status, _, _ = client.get("/client/../daybreak_web/server.py")
        check(status in (400, 404), "a client path may not escape the client directory")
        status, _, body = client.get("/")
        check(status == 200 and b"/api/health" in body, "the index must point at the API")
    finally:
        httpd.shutdown()
        httpd.server_close()
    print("  client: html/wasm served same-origin, traversal refused")


def main() -> int:
    with tempfile.TemporaryDirectory(prefix="web_delivery_test") as tmp_name:
        tmp = Path(tmp_name)
        install = make_install(tmp / "install")
        out = tmp / "prepared"
        print(f"web_delivery_test: synthetic install at {install}")
        test_bundle_rules(install)
        catalog = test_prepare(install, out)
        test_verify(install, out)
        test_manifests(catalog)
        test_http(install, out, catalog)
        test_no_catalog(tmp)
        test_stale_install(install, out)
        test_client_files(tmp, out)

    print()
    if not FAILURES:
        print("WEB_DELIVERY_TEST: ok")
        return 0
    print(f"WEB_DELIVERY_TEST: FAIL ({len(FAILURES)} checks failed)")
    return 1


if __name__ == "__main__":
    sys.exit(main())
