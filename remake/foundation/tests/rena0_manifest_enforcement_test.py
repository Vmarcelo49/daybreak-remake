#!/usr/bin/env python3
"""Exercise approved v3 scope with scratch mutations, never editing the real fixtures."""
import pathlib
import shutil
import subprocess
import sys
import tempfile


def main():
    runner = pathlib.Path(sys.argv[1]).resolve()
    source = pathlib.Path(sys.argv[2]).resolve()
    baseline = subprocess.run([str(runner), str(source)], capture_output=True, text=True)
    if baseline.returncode == 77:
        print("SKIP: manifest enforcement needs the install-backed fixture runner (not a pass)")
        return 77
    if baseline.returncode != 0:
        print(baseline.stdout + baseline.stderr)
        return 1

    cases = [
        ("missing-manifest-with-decoy", None, None, "missing acceptance manifest"),
        ("missing-legacy-guard", "case guard-gate        rena0-guard-gate-legacy.fixture\n",
         None, "case/fixture pair 'guard-gate' / 'rena0-guard-gate-legacy.fixture'"),
        ("repointed-pilot-guard", "case guard-gate        rena0-guard-gate-pilot.fixture",
         "case guard-gate        rena0-guard-hold.fixture",
         "case/fixture pair 'guard-gate' / 'rena0-guard-gate-pilot.fixture'"),
        ("missing-right-dash", "case ground-dashes     rena0-ground-dash-right.fixture\n",
         None, "case/fixture pair 'ground-dashes' / 'rena0-ground-dash-right.fixture'"),
        ("missing-charge-field", "field charge_gauge     rena0-powered-shot.fixture\n",
         None, "acceptance field 'charge_gauge'"),
        ("missing-powered-shot-case", "case shot-gauge        rena0-powered-shot.fixture\n",
         None, "case/fixture pair 'shot-gauge' / 'rena0-powered-shot.fixture'"),
        ("repointed-damage-field", "field dummy_hp         rena0-hit-ground-300.fixture",
         "field dummy_hp         rena0-guard-gate-pilot.fixture",
         "acceptance field 'dummy_hp' for fixture 'rena0-hit-ground-300.fixture'"),
    ]
    # CTest's build directory owns all temporary files. TemporaryDirectory cleans only its
    # known scratch tree; the source fixture directory remains read-only.
    with tempfile.TemporaryDirectory(prefix="rena0-manifest-", dir=pathlib.Path.cwd()) as temp:
        for name, old, new, expected in cases:
            destination = pathlib.Path(temp) / name
            shutil.copytree(source, destination)
            manifest = destination / "MANIFEST.txt"
            if old is None:
                manifest.rename(destination / "DECOY.txt")
            else:
                text = manifest.read_text()
                if text.count(old) != 1:
                    print(f"FAIL {name}: mutation no longer has exactly one target")
                    return 1
                manifest.write_text(text.replace(old, new or "", 1))
            if name == "missing-legacy-guard":
                (destination / "rena0-guard-gate-legacy.fixture").unlink()
            if name == "repointed-pilot-guard":
                (destination / "rena0-guard-gate-pilot.fixture").unlink()
            if name == "repointed-damage-field":
                hit = destination / "rena0-hit-ground-300.fixture"
                hit.write_text("\n".join(line for line in hit.read_text().splitlines()
                                          if " dummy_hp " not in line) + "\n")
            result = subprocess.run([str(runner), str(destination)], capture_output=True, text=True)
            output = result.stdout + result.stderr
            if result.returncode != 1 or expected not in output:
                print(f"FAIL {name}: exit={result.returncode}; expected diagnostic: {expected}")
                print(output)
                return 1
            print(f"  {name}: rejected (exit 1, expected diagnostic)")
    print(f"RENA0_MANIFEST_ENFORCEMENT: PASS ({len(cases)} mutations, skips=0)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
