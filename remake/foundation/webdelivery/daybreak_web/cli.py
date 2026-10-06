"""Command line: prepare once, verify, inspect the ordering, measure, serve.

    python3 -m daybreak_web prepare --install /game --out /data
    python3 -m daybreak_web verify  --out /data
    python3 -m daybreak_web order   --install /game        # which bundle wins
    python3 -m daybreak_web measure --out /data --match stage21/rena:0,mion:0/001,002
    python3 -m daybreak_web serve   --out /data --client /client --port 8080

`order` is the host's answer to "which copy does the game actually read?" and is
also the oracle `tests/web_catalog_order.cpp` compares the native reader against;
it never writes anything, so it is safe on a read-only install.
"""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from . import catalog as catalog_mod
from . import groups, server
from .bundles import BundleSet


def _cmd_prepare(args) -> int:
    install = Path(args.install)
    out = Path(args.out)

    def progress(done: int, total: int, asset_id: str) -> None:
        if args.quiet:
            return
        if done % 250 == 0 or done == total:
            print(f"  [{done}/{total}] {asset_id}", flush=True)

    try:
        catalog, stats = catalog_mod.prepare(
            install, out, includes=args.include, gzip_mode=args.gzip,
            hash_copies=args.hash_copies, force=args.force, progress=progress)
    except FileNotFoundError as exc:
        print(f"prepare: {exc}", file=sys.stderr)
        return 2

    counts = catalog["counts"]
    if stats.reused:
        print(f"prepare: up to date — {stats.reused} assets already prepared under {out}")
        return 0
    print(f"prepare: {counts['assets']} assets, {counts['rawBytes'] / 1e6:.1f} MB prepared "
          f"({stats.prepared} written, {stats.skipped} already current) in {stats.seconds:.1f} s")
    print(f"prepare: duplicates — {counts['duplicateNames']} names in more than one bundle, "
          f"{counts['duplicateCopies']} losing copies recorded, "
          f"{counts['duplicateGroupsDiffering']} groups differ in bytes")
    print(f"prepare: transfer — {counts['transferBytes'] / 1e6:.1f} MB "
          f"({stats.gzipped} assets precompressed)")
    print(f"prepare: startup — {counts['startupAssets']} assets, "
          f"{counts['startupTransferBytes'] / 1e6:.1f} MB "
          f"(gate: {counts['gateAssets']} assets, {counts['gateTransferBytes'] / 1e6:.1f} MB)")
    print(f"prepare: catalog {catalog['catalogVersion'][:16]}… -> {out / 'catalog.json'}")
    return 0


def _cmd_verify(args) -> int:
    try:
        problems, checked = catalog_mod.verify(Path(args.out))
    except (FileNotFoundError, ValueError) as exc:
        print(f"verify: {exc}", file=sys.stderr)
        return 2
    for problem in problems[:50]:
        print(f"verify: {problem}")
    if problems:
        print(f"verify: {len(problems)} problem(s) in {checked} assets")
        return 1
    print(f"verify: ok — {checked} assets re-hashed against the catalog")
    return 0


def _cmd_order(args) -> int:
    """Print the resolved ordering, one line per logical name.

    Columns: raw CP932 name bytes (hex), winning bundle, that bundle's table
    index, payload size, decoded name. The raw bytes are the key so the check
    against the native reader does not depend on either side's CP932 decoder.
    """
    import hashlib

    bundle_set = BundleSet(Path(args.install))
    if not bundle_set.open_bundles:
        print("order: no bundle could be opened", file=sys.stderr)
        return 2
    winners = bundle_set.resolve()
    for name in sorted(winners):
        entry = winners[name]
        line = [entry.raw_name.hex(), entry.bundle, str(entry.index), str(entry.length)]
        if args.hash:
            digest = hashlib.sha256(
                bundle_set.bundles[entry.precedence].read(entry)).hexdigest()
            line.append(digest)
        line.append(name)
        print("\t".join(line))
    return 0


def _cmd_measure(args) -> int:
    """Step 6: the transfer numbers, from the catalog, not from a guess."""
    try:
        catalog = catalog_mod.load_catalog(Path(args.out))
    except (FileNotFoundError, ValueError) as exc:
        print(f"measure: {exc}", file=sys.stderr)
        return 2

    def totals(assets) -> tuple[int, int, int]:
        raw = sum(a["size"] for a in assets)
        transfer = sum(a.get("gzipSize") or a["size"] for a in assets)
        gz = sum(1 for a in assets if a.get("gzipSize"))
        return raw, transfer, gz

    print("extension\tassets\traw MB\ttransfer MB\tratio\tgzipped")
    for suffix, stats in catalog.get("extensions", {}).items():
        raw = stats["raw"]
        transfer = stats["gz"] or raw
        print(f"{suffix or '(none)'}\t{stats['assets']}\t{raw / 1e6:.2f}\t"
              f"{transfer / 1e6:.2f}\t{transfer / raw if raw else 1:.3f}\t{stats['gz']}")

    startup = [a for a in catalog["assets"] if a["group"] == groups.STARTUP]
    raw, transfer, gz = totals(startup)
    print(f"\nstartup group\t{len(startup)}\t{raw / 1e6:.2f}\t{transfer / 1e6:.2f}\t"
          f"{transfer / raw if raw else 1:.3f}\t{gz}")
    for match in args.match or []:
        # Fields are separated by '/', not ':', because a slot spec carries its own
        # colon ("rena:0") and splitting on it silently dropped the weapons.
        parts = match.split("/")
        stage = parts[0]
        slots = parts[1].split(",") if len(parts) > 1 and parts[1] else []
        weapons = parts[2].split(",") if len(parts) > 2 and parts[2] else []
        label, ids = catalog_mod.match_manifest(catalog, stage, slots, weapons)
        by_id = {a["id"]: a for a in catalog["assets"]}
        selected = [by_id[i] for i in ids]
        raw, transfer, gz = totals(selected)
        print(f"{label}\t{len(selected)}\t{raw / 1e6:.2f}\t{transfer / 1e6:.2f}\t"
              f"{transfer / raw if raw else 1:.3f}\t{gz}")
    raw, transfer, gz = totals(catalog["assets"])
    print(f"catalog\t{len(catalog['assets'])}\t{raw / 1e6:.2f}\t{transfer / 1e6:.2f}\t"
          f"{transfer / raw if raw else 1:.3f}\t{gz}")
    return 0


def _cmd_serve(args) -> int:
    server.serve(Path(args.out), Path(args.client) if args.client else None,
                 Path(args.install) if args.install else None, args.host, args.port)
    return 0


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(prog="daybreak_web", description=__doc__)
    sub = parser.add_subparsers(dest="command", required=True)

    prepare = sub.add_parser("prepare", help="extract the winning copies and write the catalog")
    prepare.add_argument("--install", required=True, help="directory holding daybreakXX.dat")
    prepare.add_argument("--out", required=True, help="prepared-data volume")
    prepare.add_argument("--include", action="append", default=[],
                         help="only assets under this prefix (repeatable; default: everything)")
    prepare.add_argument("--gzip", choices=("auto", "off"), default="auto")
    prepare.add_argument("--hash-copies", action="store_true",
                         help="also hash the losing copies (slower; proves byte differences)")
    prepare.add_argument("--force", action="store_true", help="ignore an existing catalog")
    prepare.add_argument("--quiet", action="store_true")
    prepare.set_defaults(func=_cmd_prepare)

    verify = sub.add_parser("verify", help="re-hash the prepared tree against the catalog")
    verify.add_argument("--out", required=True)
    verify.set_defaults(func=_cmd_verify)

    order = sub.add_parser("order", help="print which bundle wins for every name (read-only)")
    order.add_argument("--install", required=True)
    order.add_argument("--hash", action="store_true", help="also hash each winning payload")
    order.set_defaults(func=_cmd_order)

    measure = sub.add_parser("measure", help="transfer sizes per extension and group")
    measure.add_argument("--out", required=True)
    measure.add_argument("--match", action="append", default=[],
                         help="stage/char[:costume],char[:costume]/weapon,weapon")
    measure.set_defaults(func=_cmd_measure)

    serve_cmd = sub.add_parser("serve", help="serve the client and the asset API")
    serve_cmd.add_argument("--out", required=True, help="prepared-data volume")
    serve_cmd.add_argument("--client", default="", help="directory holding the web client build")
    serve_cmd.add_argument("--install", default="",
                           help="optional read-only install, checked for staleness")
    serve_cmd.add_argument("--host", default="0.0.0.0")
    serve_cmd.add_argument("--port", type=int, default=8080)
    serve_cmd.set_defaults(func=_cmd_serve)

    args = parser.parse_args(argv)
    return args.func(args)
