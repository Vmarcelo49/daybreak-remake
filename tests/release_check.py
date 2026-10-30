#!/usr/bin/env python3
"""release_check.py — require asset/GPU-backed suites to EXECUTE, not skip.

Why: the host suite is green on a machine with no game data and no GPU because the
asset-backed suites report exit 77 there. That is the right default for day-to-day
runs, but it means "65/65 passed" says nothing about whether those suites ever ran.
This gate closes that hole: it runs every `asset`-labelled suite and fails if any of
them was SKIPPED, if any failed, or if the label matched nothing.

Usage (from the build directory or anywhere, with the build dir as argv[1]):

    python3 tests/release_check.py build/linux

Exit 0 only when every labelled suite executed and passed.
"""
import argparse
import os
import subprocess
import sys
import tempfile
import xml.etree.ElementTree as ET
from pathlib import Path

FOUNDATION = Path(__file__).resolve().parents[1]
LABEL = "asset"


def summarize_junit(path):
    """(executed, skipped, failed) test names from a CTest JUnit report.

    CTest marks a SKIP_RETURN_CODE exit as `<skipped>` in the report, which is how this
    gate can tell "proved nothing" from "passed".
    """
    root = ET.parse(path).getroot()
    executed, skipped, failed = [], [], []
    for case in root.iter("testcase"):
        name = case.get("name", "?")
        if case.find("skipped") is not None:
            skipped.append(name)
        elif case.find("failure") is not None or case.find("error") is not None:
            failed.append(name)
        else:
            executed.append(name)
    return executed, skipped, failed


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("build_dir", nargs="?", default=str(FOUNDATION / "build" / "linux"))
    ap.add_argument("--label", default=LABEL)
    ap.add_argument("--timeout", type=float, default=3600.0)
    args = ap.parse_args()
    build_dir = Path(args.build_dir).resolve()
    if not (build_dir / "CTestTestfile.cmake").exists():
        sys.exit("release_check: %s is not a configured CTest build directory" % build_dir)

    # Discovery first: an empty match would otherwise report a clean gate.
    listed = subprocess.run(["ctest", "-N", "-L", args.label], cwd=build_dir,
                            capture_output=True, text=True)
    # CTest's own total, not a count of the listing lines: the listing format varies with
    # the label filter and a stale parser would silently pass an empty gate.
    total = 0
    for line in listed.stdout.splitlines():
        if line.startswith("Total Tests:"):
            total = int(line.split(":", 1)[1].strip())
    if total == 0:
        sys.exit("release_check: no tests carry the '%s' label — the gate would be "
                 "vacuous" % args.label)
    print("release_check: %d '%s'-labelled suite(s) must execute" % (total, args.label))

    with tempfile.TemporaryDirectory() as tmp:
        junit = os.path.join(tmp, "results.xml")
        run = subprocess.run(
            ["ctest", "-L", args.label, "--output-on-failure", "--output-junit", junit],
            cwd=build_dir, capture_output=True, text=True, timeout=args.timeout)
        print(run.stdout)
        if run.returncode != 0:
            print(run.stderr)
        if not os.path.exists(junit):
            sys.exit("release_check: ctest wrote no JUnit report; cannot tell a skip "
                     "from a pass (exit %d)" % run.returncode)

        executed, skipped, failed = summarize_junit(junit)
        print("release_check: executed=%d skipped=%d failed=%d"
              % (len(executed), len(skipped), len(failed)))
        for name in skipped:
            print("  SKIPPED (a prerequisite was missing, so it proved nothing): %s" % name)
        for name in failed:
            print("  FAILED: %s" % name)

    if failed or skipped:
        print("release_check: FAIL — the release gate needs every %s suite to run"
              % args.label)
        return 1
    if len(executed) != total:
        print("release_check: FAIL — %d suite(s) listed but %d reported"
              % (total, len(executed)))
        return 1
    print("release_check: ok — every %s-labelled suite executed and passed" % args.label)
    return 0


if __name__ == "__main__":
    sys.exit(main())
