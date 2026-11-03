#!/usr/bin/env python3
"""A release build without a trusted key must not compile (issue #100, step 4).

Compiles tests/release_guard_probe.cpp three ways: plain (ok), with
DAYBREAK_RELEASE_BUILD (must fail, naming the key) and with the temporary
DAYBREAK_ALLOW_UNSIGNED_PACKAGE escape (ok again). The packaging scripts always pass
DAYBREAK_RELEASE_BUILD=ON, so an unsigned package cannot be built by accident.

    release_guard_test.py <c++ compiler>
"""
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
PROBE = ROOT / "tests" / "release_guard_probe.cpp"


def compile_with(compiler, defines, output):
    return subprocess.run(
        [compiler, "-std=c++17", "-I", str(ROOT / "src"), "-c", str(PROBE),
         "-o", str(output)] + defines,
        capture_output=True, text=True)


def main():
    if len(sys.argv) != 2:
        print("usage: release_guard_test.py <c++ compiler>", file=sys.stderr)
        return 2
    compiler = sys.argv[1]
    with tempfile.TemporaryDirectory(prefix="release-guard-") as temporary:
        output = Path(temporary) / "probe.o"
        plain = compile_with(compiler, [], output)
        if plain.returncode != 0:
            print("release_guard_test: the probe does not compile without the macro:\n"
                  + plain.stderr, file=sys.stderr)
            return 1
        guarded = compile_with(compiler, ["-DDAYBREAK_RELEASE_BUILD=1"], output)
        if guarded.returncode == 0:
            print("release_guard_test: a release build compiled with an empty key list",
                  file=sys.stderr)
            return 1
        if "trusted release key" not in guarded.stderr:
            print("release_guard_test: the failure does not name the key:\n"
                  + guarded.stderr, file=sys.stderr)
            return 1
        test_build = compile_with(
            compiler, ["-DDAYBREAK_RELEASE_BUILD=1", "-DDAYBREAK_UPDATE_TEST_BUILD=1"],
            output)
        if test_build.returncode == 0:
            print("release_guard_test: a release build accepted the test-key path",
                  file=sys.stderr)
            return 1
        if "must never be a release build" not in test_build.stderr:
            print("release_guard_test: the test-key refusal does not say why:\n"
                  + test_build.stderr, file=sys.stderr)
            return 1
        escaped = compile_with(
            compiler,
            ["-DDAYBREAK_RELEASE_BUILD=1", "-DDAYBREAK_ALLOW_UNSIGNED_PACKAGE=1"],
            output)
        if escaped.returncode != 0:
            print("release_guard_test: the temporary escape no longer compiles:\n"
                  + escaped.stderr, file=sys.stderr)
            return 1
    print("release_guard_test: the release key guard fails the build as intended")
    return 0


if __name__ == "__main__":
    sys.exit(main())
