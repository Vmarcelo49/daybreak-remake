#!/usr/bin/env python3
"""native_check.py — data-free native test guard for ordinary changes (issue #127).

Why this exists: CTest exits 0 both when a filter matches zero tests and when a
selected test SKIPs (exit 77, "no game data / no GPU"). Either would leave a cheap
CI check green while proving nothing. This wrapper pins an explicit set of tests
that need no install, no GPU and no external network, and succeeds only when every
one of them is discovered, executes and passes.

It is a per-change signal, not a release gate: no packaging, no artifacts and no
install-backed or original-runtime claims. It cannot replace the release workflows
or the install-backed local gates, which stay authoritative.

Usage:
    python3 scripts/native_check.py build/linux
    python3 scripts/native_check.py build/linux --expect fixed_step_test,user_settings_test
"""
import argparse
import os
import re
import subprocess
import sys
import tempfile
import xml.etree.ElementTree as ET
from pathlib import Path

FOUNDATION = Path(__file__).resolve().parents[1]

# Data-free by construction: pure logic, source-text checks or synthetic data the
# test writes itself. None takes an install path or opens a GPU; web_delivery_test
# binds a loopback HTTP server, so no external network is required.
# Keep this list explicit rather than deriving it from a label: a filter that matches
# zero tests is the exact silent-pass this guard is here to prevent.
EXPECTED_TESTS = (
    "battle_pause_test",
    "canvas_layout_test",
    "check_tools_test",
    "debug_prims_geometry",
    "english_captions_test",
    "fixed_step_test",
    "live_prims_budget_test",
    "math_accuracy_test",
    "update_archive_test",
    "update_crypto_test",
    "update_logic_test",
    "user_settings_test",
    "web_delivery_test",
)


def summarize_junit(path):
    """(passed, skipped, failed) testcase names from a CTest JUnit report."""
    root = ET.parse(path).getroot()
    passed, skipped, failed = [], [], []
    for case in root.iter("testcase"):
        name = case.get("name", "?")
        if case.find("skipped") is not None:
            skipped.append(name)
        elif case.find("failure") is not None or case.find("error") is not None:
            failed.append(name)
        else:
            passed.append(name)
    return passed, skipped, failed


def ctest_env():
    """English CTest headers: the Total Tests line is parsed, not translated text."""
    return dict(os.environ, LC_ALL="C")


def discovery_total(build_dir, regex):
    """CTest's own count for the filter, not a count of listing lines."""
    listed = subprocess.run(["ctest", "-N", "-R", regex], cwd=build_dir,
                            capture_output=True, text=True, env=ctest_env())
    if listed.returncode != 0:
        sys.exit("native_check: ctest -N failed (exit %d): %s"
                 % (listed.returncode, listed.stderr.strip()))
    for line in listed.stdout.splitlines():
        if line.startswith("Total Tests:"):
            return int(line.split(":", 1)[1].strip())
    sys.exit("native_check: ctest -N printed no Total Tests line; cannot guard "
             "an empty selection")


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("build_dir", nargs="?", default=str(FOUNDATION / "build" / "linux"))
    ap.add_argument("--expect", default=None,
                    help="comma-separated test names to require instead of the "
                         "built-in data-free set (for exercising this guard)")
    ap.add_argument("--timeout", type=float, default=900.0)
    args = ap.parse_args()

    expected = ([t.strip() for t in args.expect.split(",") if t.strip()]
                if args.expect else list(EXPECTED_TESTS))
    if not expected:
        sys.exit("native_check: empty expected set — the check would be vacuous")

    build_dir = Path(args.build_dir).resolve()
    if not (build_dir / "CTestTestfile.cmake").exists():
        sys.exit("native_check: %s is not a configured CTest build directory" % build_dir)

    # Anchored alternation: adding a test elsewhere in the suite must not change
    # what this guard selects.
    regex = "^(" + "|".join(re.escape(t) for t in expected) + ")$"

    total = discovery_total(build_dir, regex)
    print("native_check: %d expected test(s), %d discovered" % (len(expected), total))
    if total == 0:
        sys.exit("native_check: zero tests matched — refusing a green vacuous check")
    if total != len(expected):
        sys.exit("native_check: discovery mismatch: %d matched, %d expected "
                 "(a test was renamed or removed)" % (total, len(expected)))

    with tempfile.TemporaryDirectory() as tmp:
        junit = os.path.join(tmp, "results.xml")
        run = subprocess.run(
            ["ctest", "-R", regex, "--no-tests=error", "--output-on-failure",
             "--output-junit", junit],
            cwd=build_dir, capture_output=True, text=True, timeout=args.timeout,
            env=ctest_env())
        print(run.stdout)
        if run.returncode != 0:
            print(run.stderr)
        if not os.path.exists(junit):
            sys.exit("native_check: ctest wrote no JUnit report; cannot tell a skip "
                     "from a pass (exit %d)" % run.returncode)

        passed, skipped, failed = summarize_junit(junit)
        print("native_check: passed=%d skipped=%d failed=%d (ctest exit %d)"
              % (len(passed), len(skipped), len(failed), run.returncode))
        for name in skipped:
            print("  SKIPPED (proved nothing): %s" % name)
        for name in failed:
            print("  FAILED: %s" % name)

    problems = []
    if skipped:
        problems.append("%d skipped" % len(skipped))
    if failed:
        problems.append("%d failed" % len(failed))
    missing = set(expected) - set(passed)
    if missing:
        problems.append("%d not executed: %s" % (len(missing), ", ".join(sorted(missing))))
    if run.returncode != 0:
        problems.append("ctest exit %d" % run.returncode)
    if len(passed) != len(expected):
        problems.append("%d passed vs %d expected" % (len(passed), len(expected)))
    if problems:
        print("native_check: FAIL — " + "; ".join(problems))
        return 1
    print("native_check: ok — every selected data-free test executed and passed")
    return 0


if __name__ == "__main__":
    sys.exit(main())
