"""Prepare the host's install once, and describe the result as a catalog.

Two outputs, both outside Git and both under one directory the host mounts as a
volume:

    <out>/data/...        the winning copy of every catalogued asset, as the
    <out>/movie/...       ordinary decoded archive payload (archive lookup and
                          the DAT payload XOR are gone; runtime decoding of
                          .cnv/.X is untouched)
    <out>/.transfer/...   precompressed copies, kept only where gzip measured a
                          real gain (Step 6's rule, applied at prepare time so
                          the transfer cost is in the catalog rather than
                          guessed at serve time)
    <out>/catalog.json    the versioned catalog: per-asset size, sha256, the
                          bundle that won, every other copy, and its group

Why the winner is written and not the last copy: `extract_dat.py` flattens the
archives in file-number order, so a name shipped twice keeps whichever archive
came last. That is *not* what the game reads — 983 names ship in more than one
bundle, 445 of those groups differ in bytes, and the exe resolves the earliest
*registered* bundle (see `dat_bundle.cpp`). Writing the winner is the whole
point of the prepare step; the losing copies are recorded, not written.
"""

from __future__ import annotations

import gzip
import hashlib
import json
import os
import shutil
import time
from dataclasses import dataclass, field
from pathlib import Path
from typing import Iterable, Sequence

from . import groups
from .bundles import BUNDLE_PRECEDENCE, BundleSet

#: Bumped when the catalog's shape changes in a way a client must notice.
CATALOG_FORMAT = 1

#: gzip is applied per asset only when it beats this ratio. The value is a
#: *measured* choice: Step 6 asks for compression to be chosen from
#: measurements, not from a guess, and `prepare` reports the per-extension
#: outcome so the number is visible.
GZIP_MAX_RATIO = 0.95

#: Extensions the measurement says do not compress usefully (already-compressed
#: containers). `--gzip=auto` skips them without spending the CPU; the measured
#: per-extension table in the report is what put them here.
GZIP_SKIP_SUFFIXES: tuple[str, ...] = (
    ".mpg", ".ogg", ".wav", ".sfl", ".cnv", ".dat",
)

CHUNK = 1 << 20


def sha256_file(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as handle:
        while True:
            block = handle.read(CHUNK)
            if not block:
                break
            digest.update(block)
    return digest.hexdigest()


def install_fingerprint(install_dir: Path, names: Sequence[str] = BUNDLE_PRECEDENCE) -> dict:
    """What identifies this install for "has it changed?" purposes.

    Size + mtime per bundle, not a hash: a full hash of 4.4 GB would make every
    restart cost minutes, and the per-asset sha256 in the catalog is the real
    content identity. A host who wants the hashes runs `verify`.
    """
    bundles = []
    for name in names:
        path = install_dir / name
        try:
            stat = path.stat()
            bundles.append({"name": name, "size": stat.st_size,
                            "mtimeNs": stat.st_mtime_ns, "present": True})
        except OSError:
            bundles.append({"name": name, "size": 0, "mtimeNs": 0, "present": False})
    return {"bundles": bundles}


def fingerprint_matches(catalog: dict, fingerprint: dict) -> bool:
    """Compare a fresh install fingerprint against the one the catalog recorded.

    ``fingerprint`` is the shape :func:`install_fingerprint` returns; the catalog
    nests it under ``install.fingerprint``.
    """
    stored = catalog.get("install", {}).get("fingerprint", {})
    return stored.get("bundles") == fingerprint.get("bundles")


def _gzip_bytes(data: bytes) -> bytes:
    return gzip.compress(data, compresslevel=6, mtime=0)


def _write(path: Path, data: bytes) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    tmp = path.with_name(path.name + ".part")
    with tmp.open("wb") as handle:
        handle.write(data)
    os.replace(tmp, path)


@dataclass
class PrepareStats:
    prepared: int = 0
    skipped: int = 0
    reused: int = 0
    bytes_written: int = 0
    transfer_bytes: int = 0
    gzipped: int = 0
    duplicate_names: int = 0
    duplicate_copies: int = 0
    duplicate_groups_differing: int = 0
    per_extension: dict = field(default_factory=dict)
    seconds: float = 0.0


def _extension(asset_id: str) -> str:
    dot = asset_id.rfind(".")
    return asset_id[dot:].lower() if dot >= 0 else ""


def _record_extension(stats: PrepareStats, suffix: str, raw: int, gz: int | None) -> None:
    entry = stats.per_extension.setdefault(suffix, {"assets": 0, "raw": 0, "gz": 0})
    entry["assets"] += 1
    entry["raw"] += raw
    if gz is not None:
        entry["gz"] += gz


def _included(asset_id: str, includes: Sequence[str]) -> bool:
    return not includes or any(asset_id.startswith(prefix) for prefix in includes)


def prepare(install_dir: Path, out_dir: Path, *, includes: Sequence[str] = (),
            gzip_mode: str = "auto", hash_copies: bool = False,
            force: bool = False, progress=None) -> tuple[dict, PrepareStats]:
    """Extract the winning copies and write ``catalog.json``.

    Repeatable: with an unchanged install (same bundle sizes and mtimes), the
    same filters and a catalog whose prepared files are all still present, this
    returns the existing catalog without re-reading a payload.
    """
    install_dir = Path(install_dir)
    out_dir = Path(out_dir)
    started = time.monotonic()
    stats = PrepareStats()

    if not (install_dir / BUNDLE_PRECEDENCE[0]).exists() and not any(
        (install_dir / name).exists() for name in BUNDLE_PRECEDENCE
    ):
        raise FileNotFoundError(
            f"no daybreakXX.dat in {install_dir}: point --install at the directory "
            "holding the host's game installation"
        )

    fingerprint = install_fingerprint(install_dir)
    catalog_path = out_dir / "catalog.json"
    if catalog_path.exists() and not force:
        try:
            existing = json.loads(catalog_path.read_text(encoding="utf-8"))
        except (OSError, ValueError):
            existing = None
        if (existing and existing.get("format") == CATALOG_FORMAT
                and fingerprint_matches(existing, fingerprint)
                and existing.get("prepare", {}).get("includes", []) == list(includes)
                and existing.get("prepare", {}).get("gzip") == gzip_mode
                and _prepared_files_present(out_dir, existing)):
            stats.reused = len(existing.get("assets", []))
            stats.seconds = time.monotonic() - started
            return existing, stats

    bundle_set = BundleSet(install_dir)
    winners = bundle_set.resolve()
    copies = bundle_set.copies()

    assets = []
    total = len(winners)
    done = 0
    for asset_id, winner in winners.items():
        done += 1
        if not _included(asset_id, includes):
            continue
        if progress is not None:
            progress(done, total, asset_id)
        bundle = bundle_set.bundles[winner.precedence]
        data = bundle.read(winner)
        digest = hashlib.sha256(data).hexdigest()
        destination = out_dir / asset_id
        if destination.exists() and destination.stat().st_size == len(data) and \
                sha256_file(destination) == digest:
            stats.skipped += 1
        else:
            _write(destination, data)
            stats.prepared += 1
            stats.bytes_written += len(data)

        gz_size = 0
        suffix = _extension(asset_id)
        if gzip_mode != "off" and suffix not in GZIP_SKIP_SUFFIXES:
            packed = _gzip_bytes(data)
            if len(packed) < GZIP_MAX_RATIO * len(data):
                _write(prepared_path(out_dir, {"id": asset_id}, compressed=True), packed)
                gz_size = len(packed)
                stats.gzipped += 1
        _record_extension(stats, suffix, len(data), gz_size or None)

        entry = {
            "id": asset_id,
            "size": len(data),
            "sha256": digest,
            "gzipSize": gz_size,
            "owner": winner.bundle,
            "ownerIndex": winner.index,
            "group": groups.classify(asset_id),
        }
        group = copies.get(asset_id, [])
        if len(group) > 1:
            stats.duplicate_names += 1
            stats.duplicate_copies += len(group) - 1
            differing = False
            others = []
            for copy in group:
                if copy is winner:
                    continue
                record = {"bundle": copy.bundle, "index": copy.index, "size": copy.length}
                if hash_copies:
                    try:
                        other_digest = hashlib.sha256(
                            bundle_set.bundles[copy.precedence].read(copy)
                        ).hexdigest()
                    except Exception:            # a losing copy that cannot be read
                        other_digest = None
                    record["sha256"] = other_digest
                    if other_digest is not None and other_digest != digest:
                        differing = True
                elif copy.length != winner.length:
                    differing = True
                others.append(record)
            entry["copies"] = others
            if differing:
                stats.duplicate_groups_differing += 1
        assets.append(entry)

    assets.sort(key=lambda a: a["id"])
    stats.transfer_bytes = sum(a["gzipSize"] or a["size"] for a in assets)
    stats.seconds = time.monotonic() - started

    version = _catalog_version(assets, fingerprint, includes, gzip_mode)
    catalog = {
        "format": CATALOG_FORMAT,
        "catalogVersion": version,
        "generator": "daybreak-webdelivery/1",
        "createdUtc": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()),
        "precedence": list(BUNDLE_PRECEDENCE),
        "install": {
            "fingerprint": fingerprint,
            "missingBundles": bundle_set.missing,
            "entryCount": sum(len(b.entries) for b in bundle_set.bundles),
        },
        "prepare": {"includes": list(includes), "gzip": gzip_mode,
                    "hashCopies": hash_copies},
        "counts": {
            "assets": len(assets),
            "prepared": stats.prepared,
            "reused": stats.skipped,
            "duplicateNames": stats.duplicate_names,
            "duplicateCopies": stats.duplicate_copies,
            "duplicateGroupsDiffering": stats.duplicate_groups_differing,
            "rawBytes": sum(a["size"] for a in assets),
            "transferBytes": stats.transfer_bytes,
            "startupAssets": sum(1 for a in assets if a["group"] == groups.STARTUP),
            "startupTransferBytes": sum(
                (a["gzipSize"] or a["size"]) for a in assets if a["group"] == groups.STARTUP),
            "gateAssets": sum(1 for a in assets if groups.is_gate(a["id"])),
            "gateTransferBytes": sum(
                (a["gzipSize"] or a["size"]) for a in assets if groups.is_gate(a["id"])),
        },
        "extensions": {k: v for k, v in sorted(stats.per_extension.items())},
        "assets": assets,
    }
    out_dir.mkdir(parents=True, exist_ok=True)
    # The prepared tree is derived from the host's game install: make it
    # self-ignoring wherever the host puts it, so "never commit game data" does
    # not depend on this repository's .gitignore having the right entry.
    (out_dir / ".gitignore").write_text("*\n", encoding="utf-8")
    catalog_path.write_text(json.dumps(catalog, indent=1, ensure_ascii=False) + "\n",
                            encoding="utf-8")
    return catalog, stats


def _catalog_version(assets: Iterable[dict], fingerprint: dict,
                     includes: Sequence[str], gzip_mode: str) -> str:
    """Identity of the catalog *document* (not of an individual asset).

    Per-asset cache identity is the asset's own sha256, so changing one asset
    changes one cache key. This version exists so a client can tell "the
    catalog I hold is the one the server has" in one comparison.
    """
    digest = hashlib.sha256()
    digest.update(f"format={CATALOG_FORMAT}\n".encode())
    digest.update(("precedence=" + ",".join(BUNDLE_PRECEDENCE) + "\n").encode())
    digest.update(("includes=" + ",".join(includes) + "\n").encode())
    digest.update(f"gzip={gzip_mode}\n".encode())
    digest.update(json.dumps(fingerprint, sort_keys=True).encode())
    for asset in assets:
        digest.update(f"{asset['id']}\t{asset['size']}\t{asset['sha256']}\t"
                      f"{asset['owner']}\t{asset['ownerIndex']}\n".encode())
    return digest.hexdigest()


def _prepared_files_present(out_dir: Path, catalog: dict) -> bool:
    """Every catalogued asset still on disk with the recorded size.

    Size only: `verify` re-hashes. This is the restart path, and re-hashing
    2.6 GB on every container start would be its own defect.
    """
    for asset in catalog.get("assets", []):
        path = out_dir / asset["id"]
        try:
            if path.stat().st_size != asset["size"]:
                return False
        except OSError:
            return False
    return True


def prepared_path(out_dir: Path, asset: dict, compressed: bool = False) -> Path:
    """Where one catalogued asset lives under the prepared volume.

    The compressed copies sit in a sibling ``.transfer/`` tree rather than next to
    the payload: the prepared tree is meant to be a plain decoded-asset tree a
    native build can point at, and a second ``.gz`` beside every name would show
    up in every directory listing the loaders walk.
    """
    if compressed:
        return Path(out_dir) / ".transfer" / (asset["id"] + ".gz")
    return Path(out_dir) / asset["id"]


def load_catalog(out_dir: Path) -> dict:
    path = Path(out_dir) / "catalog.json"
    if not path.exists():
        raise FileNotFoundError(
            f"no catalog at {path}: run the prepare step against the host's install first"
        )
    catalog = json.loads(path.read_text(encoding="utf-8"))
    if catalog.get("format") != CATALOG_FORMAT:
        raise ValueError(
            f"catalog format {catalog.get('format')} is not {CATALOG_FORMAT}; re-run prepare"
        )
    return catalog


def verify(out_dir: Path, catalog: dict | None = None) -> tuple[list[str], int]:
    """Re-hash every prepared asset. Returns (problems, checked)."""
    catalog = catalog or load_catalog(out_dir)
    problems = []
    checked = 0
    for asset in catalog.get("assets", []):
        path = Path(out_dir) / asset["id"]
        checked += 1
        if not path.exists():
            problems.append(f"missing: {asset['id']}")
            continue
        digest = sha256_file(path)
        if digest != asset["sha256"]:
            problems.append(f"hash mismatch: {asset['id']} ({digest} != {asset['sha256']})")
        gz = prepared_path(out_dir, asset, compressed=True)
        if asset.get("gzipSize"):
            if not gz.exists() or gz.stat().st_size != asset["gzipSize"]:
                problems.append(f"compressed copy wrong: {asset['id']}")
    return problems, checked


def manifest_text(catalog: dict, asset_ids: Sequence[str], label: str) -> str:
    """The compact per-asset manifest the wasm client parses.

    One line per asset, tab separated: sha256, size, gzip size (0 = none), gate
    flag (1 = needed before the first usable screen), logical id. The catalog is
    the source of truth; this is a projection of it, so the client never has to
    carry a JSON parser into wasm.
    """
    by_id = {asset["id"]: asset for asset in catalog["assets"]}
    lines = [
        "# daybreak web asset manifest",
        f"version={catalog['catalogVersion']}",
        f"group={label}",
    ]
    total = 0
    body = []
    for asset_id in asset_ids:
        asset = by_id.get(asset_id)
        if asset is None:
            raise KeyError(f"asset not in catalog: {asset_id}")
        transfer = asset.get("gzipSize") or asset["size"]
        total += transfer
        gate = 1 if groups.is_gate(asset_id) else 0
        body.append(f"{asset['sha256']}\t{asset['size']}\t{asset.get('gzipSize', 0)}\t"
                    f"{gate}\t{asset_id}")
    lines.append(f"bytes={total}")
    lines.append(f"assets={len(body)}")
    return "\n".join(lines + body) + "\n"


def startup_asset_ids(catalog: dict) -> list[str]:
    return sorted(a["id"] for a in catalog["assets"] if a["group"] == groups.STARTUP)


def match_manifest(catalog: dict, stage: str, slots: Sequence[str],
                   weapons: Sequence[str] = ()) -> tuple[str, list[str]]:
    ids = groups.match_asset_ids(catalog["assets"], stage, slots, weapons)
    label = f"match:{stage}:{','.join(slots)}"
    if weapons:
        label += ":" + ",".join(weapons)
    return label, ids


def copy_client_tree(source: Path, destination: Path) -> list[str]:
    """Copy the built web client next to the catalog (used by the Dockerfile)."""
    destination.mkdir(parents=True, exist_ok=True)
    copied = []
    for path in sorted(Path(source).iterdir()):
        if path.is_file() and path.suffix in (".js", ".wasm", ".html", ".data", ".css"):
            shutil.copy2(path, destination / path.name)
            copied.append(path.name)
    return copied
