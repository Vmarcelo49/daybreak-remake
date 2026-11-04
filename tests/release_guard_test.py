#!/usr/bin/env python3
"""The release key guard must be real (issue #100, step 4).

Compiles tests/release_guard_probe.cpp four ways:

* plain — the probe builds;
* with DAYBREAK_RELEASE_BUILD — the real header carries the owner's key, so it builds;
* with DAYBREAK_RELEASE_BUILD against an emptied copy of the header — it must fail,
  naming the key (the copy is generated here, so the product header keeps no test seam);
* with DAYBREAK_RELEASE_BUILD and DAYBREAK_UPDATE_TEST_BUILD — it must fail, because the
  test-key path must never ship in a release.

    release_guard_test.py <c++ compiler>
"""
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
PROBE = ROOT / "tests" / "release_guard_probe.cpp"


def compile_with(compiler, defines, output, include=None):
    command = [compiler, "-std=c++17"]
    for path in include or []:
        command += ["-I", str(path)]
    command += ["-c", str(PROBE), "-o", str(output)] + defines
    return subprocess.run(command, capture_output=True, text=True)


def main():
    if len(sys.argv) != 2:
        print("usage: release_guard_test.py <c++ compiler>", file=sys.stderr)
        return 2
    compiler = sys.argv[1]
    header = ROOT / "src" / "update" / "release_keys.h"
    with tempfile.TemporaryDirectory(prefix="release-guard-") as temporary:
        work = Path(temporary)
        output = work / "probe.o"
        plain = compile_with(compiler, [], output, [ROOT / "src"])
        if plain.returncode != 0:
            print("release_guard_test: the probe does not compile without the macro:\n"
                  + plain.stderr, file=sys.stderr)
            return 1
        release = compile_with(compiler, ["-DDAYBREAK_RELEASE_BUILD=1"], output,
                               [ROOT / "src"])
        if release.returncode != 0:
            print("release_guard_test: the release build does not accept the owner's key:\n"
                  + release.stderr, file=sys.stderr)
            return 1

        # The same header with the list emptied: the guard must fire.
        text = header.read_text()
        emptied, count = re.subn(
            r"std::array<std::array<std::uint8_t, 32>, \d+> kReleaseKeys = \{.*?\};",
            "std::array<std::array<std::uint8_t, 32>, 0> kReleaseKeys = {};",
            text, flags=re.S)
        if count != 1:
            print("release_guard_test: cannot find the key array in %s" % header,
                  file=sys.stderr)
            return 1
        copy = work / "empty" / "update"
        copy.mkdir(parents=True)
        (copy / "release_keys.h").write_text(emptied)
        empty = compile_with(compiler, ["-DDAYBREAK_RELEASE_BUILD=1"], output,
                             [work / "empty", ROOT / "src"])
        if empty.returncode == 0:
            print("release_guard_test: a release build compiled with an empty key list",
                  file=sys.stderr)
            return 1
        if "trusted release key" not in empty.stderr:
            print("release_guard_test: the failure does not name the key:\n"
                  + empty.stderr, file=sys.stderr)
            return 1

        test_build = compile_with(
            compiler, ["-DDAYBREAK_RELEASE_BUILD=1", "-DDAYBREAK_UPDATE_TEST_BUILD=1"],
            output, [ROOT / "src"])
        if test_build.returncode == 0:
            print("release_guard_test: a release build accepted the test-key path",
                  file=sys.stderr)
            return 1
        if "must never be a release build" not in test_build.stderr:
            print("release_guard_test: the test-key refusal does not say why:\n"
                  + test_build.stderr, file=sys.stderr)
            return 1
    print("release_guard_test: the owner's key builds a release, an empty list fails, "
          "and the test-key path is refused")
    return 0


if __name__ == "__main__":
    sys.exit(main())
