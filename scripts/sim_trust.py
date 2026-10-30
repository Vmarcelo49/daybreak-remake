#!/usr/bin/env python3
"""Run simfuzz across all 46 combos in parallel and summarise the result (docs/DIRECTION.md, M2).

usage: sim_trust.py BUILD_DIR RUNS TICKS OUTPUT.json [--first-seed N]
"""
import argparse
import collections
import json
import os
import subprocess
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path


def run_combo(build: Path, character: int, weapon: int, runs: int, ticks: int, first: int) -> dict:
    done = subprocess.run([str(build / "simfuzz"), str(character), str(weapon), str(runs), str(ticks), str(first)],
                          cwd=build, capture_output=True, text=True)
    if done.returncode != 0:
        return {"combo": f"{character}+{weapon}", "character": character, "weapon": weapon, "crash": done.returncode,
                "stderr": done.stderr[-400:], "runs": runs, "ticks": 0, "finished": 0, "counts": {"process_crash": 1},
                "reports": [], "declared": [], "reached": []}
    return json.loads(done.stdout)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("build", type=Path)
    parser.add_argument("runs", type=int)
    parser.add_argument("ticks", type=int)
    parser.add_argument("output", type=Path)
    parser.add_argument("--first-seed", type=int, default=1)
    args = parser.parse_args()
    args.build = args.build.resolve()

    combos = [(c, w) for c in range(16) for w in range(3 if c < 14 else 2)]
    with ThreadPoolExecutor(max_workers=os.cpu_count()) as pool:
        results = list(pool.map(lambda cw: run_combo(args.build, *cw, args.runs, args.ticks, args.first_seed), combos))
    args.output.write_text(json.dumps(results, indent=0))

    kinds = collections.Counter()
    for result in results:
        kinds.update(result["counts"])
    print(f"combos {len(results)} ticks {sum(r['ticks'] for r in results)} finished {sum(r['finished'] for r in results)}")
    print("findings:", dict(kinds) or "none")
    for result in results:
        declared, reached = set(result["declared"]), set(result["reached"])
        print(f"{result['combo']:<16} declared {len(declared):>3} reached {len(declared & reached):>3} "
              f"undeclared {sorted(reached - declared)[:8]} findings {result['counts'] or ''}")


if __name__ == "__main__":
    main()
