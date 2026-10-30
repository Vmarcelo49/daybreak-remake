#!/usr/bin/env python3
"""showcase.py — asset smoke check + progress showcase captures.

Two jobs, one headless binary (build/linux/foundation_demo):

1. Checker (--check): run every (character, stage) pair headless for a few
   frames and report which pairs load with a fully textured draw list. A
   broken .X model, a missing stage scene, or an unresolvable texture all
   surface as failures — the cheap integrity check for the asset pipeline,
   with the demo's own loader (scene.h: loadCharacter/loadStage) as oracle.

2. Showcase (--shots): capture a curated set of high-resolution frames for
   progress screenshots, in match mode so the HUD is visible.

Usage:
  python3 tests/showcase.py --check     # full character x stage matrix
  python3 tests/showcase.py --shots      # curated showcase captures
  python3 tests/showcase.py              # both

The checker matrix is deliberately small per run (30 frames, 320x240): the
draw list is static, so a few frames are enough to see what loaded.
"""

import argparse
import re
import subprocess
import sys
import tempfile
from pathlib import Path

FOUNDATION = Path(__file__).resolve().parents[1]
DATA = FOUNDATION.parents[1] / "Higurashi-Daybreak" / "data"
BINARY = FOUNDATION / "build" / "linux" / "foundation_demo"

# Directories that live next to the characters but are not characters: stages
# (auto-detected separately), VFX tables, audio, UI and config.
NOT_CHARACTERS = {
    "aura", "bgm", "bullet", "camera", "chat", "config", "directX", "effect",
    "item", "keyconfig", "movie", "network", "object", "scenario", "se",
    "select", "sysse", "talk", "teamselect", "title", "trail", "voice", "vs",
    "win",
}

DRAWS_RE = re.compile(r"draws: (\d+) \((\d+) textured, (\d+) untextured")


# The install's documented data gaps (RELEASE-CHECKLIST.md 4.2). Every entry names the
# exact cell and the exact count it is allowed to report; anything else fails on its own
# merits, so one new regression can never hide inside a total. The list replaces the old
# `--allow-problems=43` count, which accepted any 43 bad cells — including a crash.
EXPECTED_GAPS = (
    # stage05/stage15 ship no dust/particle textures, so the stage draws 4 untextured
    # draws with the stage geometry and no character-specific texture is involved.
    {"stages": ("stage05", "stage15"), "except_character": "kasai",
     "untextured": (4,), "why": "stage dust/particle textures are not in the install"},
    # kasai's `g` texture is missing, so its model reports 2 untextured draws on every
    # stage — or 6 where the stage gap above also applies.
    {"characters": ("kasai",), "untextured": (2, 6),
     "why": "kasai's `g` texture is not in the install"},
)

# The roster and stage counts the sweep claims to cover, so an empty or shrunken discovery
# fails instead of silently reporting a smaller, easier matrix as green.
EXPECTED_CHARACTERS = 16
EXPECTED_STAGES = 13
# The checklist's cell total for the table above (30 stage-gap cells + 13 kasai cells).
EXPECTED_GAP_CELLS = 43


def expected_gap(character, stage, untextured):
    """The documented gap this cell matches, or None when it is unexpected."""
    for gap in EXPECTED_GAPS:
        if "characters" in gap and character not in gap["characters"]:
            continue
        if "except_character" in gap and character == gap["except_character"]:
            continue
        if "stages" in gap and stage not in gap["stages"]:
            continue
        if untextured not in gap["untextured"]:
            continue
        return gap
    return None


def discover_characters():
    """Base character dirs only: contain at least one .X, are not a stage/table
    dir, and have no costume suffix (loadCharacter's _B.._F variants share the
    base dir's .dat files, so checking the base covers them)."""
    chars = []
    for d in sorted(DATA.iterdir()):
        if not d.is_dir() or d.name.startswith("stage") or d.name in NOT_CHARACTERS:
            continue
        if re.fullmatch(r"[a-z]+_[A-Fa-f]", d.name):
            continue
        if any(d.glob("*.X")):
            chars.append(d.name)
    return chars


def discover_stages():
    return sorted(d.name for d in DATA.iterdir()
                  if d.is_dir() and re.fullmatch(r"stage\d+", d.name))


def run_capture(char, enemy, stage, frames, size, out, script=None, co_spawn=False,
                slot=0):
    """One headless demo run. Returns (ok, textured, untextured, stderr_tail).

    `slot` is stated explicitly and passed to the demo: the default is the character's
    first weapon, and a sweep that leaves it implicit cannot honestly claim more than
    "base model with slot 0" coverage (AGENTS rule 7).
    """
    cmd = [str(BINARY), "--headless", f"--out={out}",
           f"--stage={DATA / stage}", f"--character={DATA / char}:{slot}",
           f"--enemy={DATA / enemy}:{slot}", "--match", "--camera=arena",
           f"--frames={frames}", f"--size={size}"]
    if co_spawn:
        # Midpoint of the stage's arena: both fighters start together so
        # the scripted melee presses all land (see write_fx_script).
        cmd += ["--spawn=-803,200,-2200", "--spawn2=-803,200,-2200"]
    if script:
        cmd.append(f"--script={script}")
    # errors="replace": the demo prints Shift-JIS stage/character names to
    # stderr, which is not UTF-8.
    try:
        p = subprocess.run(cmd, capture_output=True, text=True,
                           encoding="utf-8", errors="replace", timeout=180)
    except subprocess.TimeoutExpired:
        return False, 0, 0, "timeout"
    text = p.stdout + "\n" + p.stderr
    m = DRAWS_RE.search(text)
    ok = p.returncode == 0 and "RESULT: ok" in text and m is not None
    textured = int(m.group(2)) if m else 0
    untextured = int(m.group(3)) if m else 0
    tail = p.stderr.strip().splitlines()[-1] if p.stderr.strip() else ""
    return ok, textured, untextured, tail


def check_matrix(out_dir, slot=0):
    """Sweep every (base character, slot-0 weapon x stage) cell and judge each one.

    A cell is allowed only when EXPECTED_GAPS names it AND the untextured count matches
    that entry. Everything else fails regardless of how many cells failed, so a crash or
    a new untextured draw cannot hide inside a tolerated total.
    """
    chars, stages = discover_characters(), discover_stages()
    # Discovery is a claim of its own: an empty or shrunken sweep would make the run look
    # clean while covering less than the checklist says it covers.
    if not chars or not stages:
        print("REGRESSION: character or stage discovery came back empty "
              f"({len(chars)} character(s), {len(stages)} stage(s))")
        return False
    if len(chars) != EXPECTED_CHARACTERS or len(stages) != EXPECTED_STAGES:
        print(f"REGRESSION: discovery found {len(chars)} character(s) x {len(stages)} "
              f"stage(s), but the coverage claim is "
              f"{EXPECTED_CHARACTERS} x {EXPECTED_STAGES} (checklist 4.2)")
        return False
    print(f"asset check: {len(chars)} character(s) x slot-{slot} weapon x "
          f"{len(stages)} stage(s) -> {len(chars) * len(stages)} runs")
    print("           " + "  ".join(s[-2:] for s in stages))
    failures, tolerated = [], []
    for c in chars:
        row = []
        for s in stages:
            out = out_dir / f"chk_{c}_{s}.ppm"
            ok, _, untex, tail = run_capture(c, c, s, 30, "320x240", out, slot=slot)
            if not ok:
                cell, why = "F", tail
            elif untex:
                cell, why = "U", f"{untex} untextured"
            else:
                cell, why = "P", ""
            if cell == "U":
                gap = expected_gap(c, s, untex)
                if gap:
                    tolerated.append((c, s, why, gap["why"]))
                else:
                    failures.append((c, s, why))
            elif cell == "F":
                # A failed run is never a documented data gap: the baseline names
                # untextured draws, not crashes. `P` falls through untouched.
                failures.append((c, s, why))
            row.append(cell)
        print(f"  {c:<10}" + "  ".join(row))
    print(f"\n{len(chars) * len(stages) - len(failures) - len(tolerated)} pass, "
          f"{len(tolerated)} documented gap(s), {len(failures)} unexpected problem(s)")
    for c, s, why, reason in tolerated:
        print(f"  expected: {c} x {s}: {why} ({reason})")
    for c, s, why in failures:
        print(f"  UNEXPECTED: {c} x {s}: {why}")
    if failures:
        print(f"REGRESSION: {len(failures)} unexpected problem cell(s) — a cell that is "
              f"not in the documented baseline is a regression, not a data gap "
              f"(checklist 4.2)")
        return False
    # The table is a claim about THIS install: a different total means either the install
    # changed or the loader did, and either way the table needs re-deriving rather than
    # silently absorbing the difference.
    if len(tolerated) != EXPECTED_GAP_CELLS:
        print(f"REGRESSION: {len(tolerated)} documented gap cell(s) reproduced, but the "
              f"baseline records {EXPECTED_GAP_CELLS} (checklist 4.2). Re-derive the table "
              f"deliberately; do not widen it to make a run pass.")
        return False
    return True


def write_fx_script(path):
    """The VFX showcase input script: 13 melee hits (fills the Friendship gauge)
    then SPECIAL on the last frame, so the capture shows the hit card and the
    active aura card. Co-spawned fighters make every press land."""
    lines = []
    f = 100
    for _ in range(13):
        lines.append(f"{f - 10} -")
        lines.append(f"{f} MELEE")
        f += 60
    lines.append("880 -")
    lines.append("890 SPECIAL")
    Path(path).write_text("\n".join(lines) + "\n")


def showcase_shots(out_dir):
    # (name, p1, p2, stage, frames, size, co_spawn, fx)
    shots = [
        ("rena_mion_stage01",      "rena",     "mion",    "stage01", 120, "1280x720", False, False),
        ("chie_rika_stage02",      "chie",     "rika",    "stage02", 120, "1280x720", False, False),
        ("satoko_hanyu_stage11",   "satoko",   "hanyu",   "stage11", 120, "1280x720", False, False),
        ("keiichi_shion_stage06",  "keiichi",  "shion",   "stage06", 120, "1280x720", False, False),
        ("akane_tomitake_stage16", "akane",    "tomitake", "stage16", 120, "1280x720", False, False),
        ("irie_kasai_stage21",     "irie",     "kasai",   "stage21", 120, "1280x720", False, False),
        ("mion_rika_stage15",      "mion",     "rika",    "stage15", 120, "1280x720", False, False),
        ("rena_mion_fx_stage01",   "rena",     "mion",    "stage01", 950, "1280x720", True,  True),
    ]
    ok_all = True
    for name, c1, c2, stage, frames, size, co_spawn, fx in shots:
        out = out_dir / f"shot_{name}.ppm"
        script = None
        if fx:
            script = out_dir / f"script_{name}.txt"
            write_fx_script(script)
        ok, textured, untextured, tail = run_capture(c1, c2, stage, frames, size, out,
                                                     script, co_spawn)
        ok_shot = ok and untextured == 0
        ok_all &= ok_shot
        extra = f"{textured} textured, {untextured} untextured" if ok else tail
        print(f"  {name:<24} {'ok' if ok_shot else 'FAIL'}  ({extra})")
    return ok_all


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--check", action="store_true", help="run the full asset matrix")
    # The install ships genuine data gaps (checklist 4.2), so a CORRECT sweep is not a
    # clean one. They are enumerated in EXPECTED_GAPS by cell and reason instead of being
    # tolerated as a count, so a crash or a new untextured draw always fails.
    ap.add_argument("--slot", type=int, default=0, metavar="N",
                    help="weapon slot to bind for every cell (default 0; the coverage "
                         "claim is character x that slot x stage)")
    ap.add_argument("--shots", action="store_true", help="run the curated showcase captures")
    ap.add_argument("--out-dir", default=tempfile.mkdtemp(prefix="showcase_"))
    args = ap.parse_args()
    if not args.check and not args.shots:
        args.check = args.shots = True

    out_dir = Path(args.out_dir)
    out_dir.mkdir(parents=True, exist_ok=True)
    if not BINARY.exists():
        sys.exit(f"binary not found: {BINARY} (run ./build.sh linux first)")

    ok = True
    if args.check:
        ok = check_matrix(out_dir, args.slot) and ok
    if args.shots:
        ok = showcase_shots(out_dir) and ok
    print(f"images in: {out_dir}")
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
