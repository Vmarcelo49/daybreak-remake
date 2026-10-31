#!/usr/bin/env python3
"""Online play (docs/ONLINE-PLAN.md, step 5): the Linux and Windows builds must simulate alike.

Every legal combo runs for 10,000 ticks, as a human and as COM, under both builds. Agreement between
builds, not with the original. The Windows build runs under Wine, not on Windows.
"""
import concurrent.futures
import json
import os
import pathlib
import shutil
import subprocess
import sys
import tempfile

TICKS = 10000
STAGES = [1, 2, 3, 4, 5, 6, 11, 12, 13, 14, 15, 16, 21]


def run(command, binary, cwd, roster, run_id, extra=()):
    args = [*command, "--game", "Higurashi-Daybreak", "--ticks", str(TICKS), "--busy", "--seed", str(run_id + 1),
            "--stage", str(STAGES[run_id % len(STAGES)]), "--roster", *roster, *extra]
    env = dict(os.environ, WINEDEBUG="-all")
    out = subprocess.run(args, cwd=cwd, env=env, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, timeout=240)
    if out.returncode != 0:
        raise RuntimeError(f"{binary} failed on {roster}: {out.stderr[-300:]}")
    return json.loads(out.stdout.splitlines()[-1])


def first_difference(linux, windows, cwd, roster, run_id):
    with tempfile.TemporaryDirectory(dir=cwd) as folder:
        name = pathlib.Path(folder).name
        run(linux, "linux", cwd, roster, run_id, ["--hash-log", f"{name}/l.log"])
        run(windows, "windows", cwd, roster, run_id, ["--hash-log", f"{name}/w.log"])
        a = pathlib.Path(folder, "l.log").read_text().splitlines()
        b = pathlib.Path(folder, "w.log").read_text().splitlines()
    for line_a, line_b in zip(a, b):
        if line_a != line_b:
            return line_a.split()[0]
    return "none"


def main():
    simctl, simctl_exe, install = sys.argv[1], pathlib.Path(sys.argv[2]), pathlib.Path(sys.argv[3])
    if not (install / "daybreak00.dat").exists():
        print("SKIP: no install")
        return 77
    if not simctl_exe.exists() or not shutil.which("wine"):
        print("SKIP: needs Wine and build/windows/simctl.exe")
        return 77
    cwd = install.parent
    linux = [str(pathlib.Path(simctl).resolve())]
    windows = ["wine", str(simctl_exe.resolve())]

    combos = subprocess.run([*linux, "--list"], stdout=subprocess.PIPE, text=True, check=True).stdout.split()
    assert len(combos) == 46, f"{len(combos)} combos"
    # Groups of 4 so each match has more going on. The groups change between passes.
    jobs = []
    for suffix, offset in ((":human", 0), ("", 17)):
        turned = combos[offset:] + combos[:offset]
        for start in range(0, len(turned), 4):
            group = (turned[start:start + 4] + turned[:4])[:4]
            jobs.append([combo + suffix for combo in group])
    # One human among COMs mixes both paths.
    for start in range(0, len(combos), 4):
        group = (combos[start:start + 4] + combos[:4])[:4]
        jobs.append([group[0] + ":human", *group[1:]])

    def compare(job):
        run_id, roster = job
        a = run(linux, "linux", cwd, roster, run_id)
        b = run(windows, "windows", cwd, roster, run_id)
        return run_id, roster, a, b

    failures = 0
    finished = 0
    with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:
        for run_id, roster, a, b in pool.map(compare, enumerate(jobs)):
            finished += a["finished"]
            if a["state_hash"] == b["state_hash"] and a["hash"] == b["hash"]:
                continue
            failures += 1
            at = first_difference(linux, windows, cwd, roster, run_id)
            print(f"DIFFER run {run_id} {roster}: first at tick {at}")
    print(f"{len(jobs)} matches of {TICKS} ticks, {finished} finished, {failures} differ")
    if failures:
        print("cross_build_check: failed")
        return 1
    print("cross_build_check: ok")
    return 0


if __name__ == "__main__":
    sys.exit(main())
