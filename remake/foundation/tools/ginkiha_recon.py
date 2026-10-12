#!/usr/bin/env python3
"""Read-only combo recon; callback requests never imply admitted projectiles.

Inputs stay local. Reports contain exact combo identities, source hashes and body
ranges so porting does not depend on repeated ad-hoc prefix filters or truncated dumps.
"""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path
import re

from import_ginkiha_tables import (
    DEFAULT_REFERENCE, DEFAULT_SUPPORT, REFERENCE_EXE_SHA256, check_exe, load_json,
)

REPO = Path(__file__).resolve().parents[3]
ORIGINS = {"fire_attachment": "attachment", "fire_hand": "hand", "fire_world": "world"}
BODY_FILES = ("shoot_native_bodies_20260929.hpp", "full_charge_native_bodies_20260929.hpp")


def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def summarize_frames(frames: list[dict]) -> dict:
    counts = Counter()
    ticks = []
    slots = Counter()
    for frame in frames:
        for event in frame["events"]:
            if event[0] not in ORIGINS:
                continue
            counts[ORIGINS[event[0]]] += 1
            ticks.append(frame["frame"])
            # Attachment callbacks carry attachment slot before projectile row.
            slots[event[2] if event[0] == "fire_attachment" else event[1]] += 1
    return {"samples": len(frames), "first_frame": ticks[0] if ticks else None,
            "requests": len(ticks), "origins": dict(sorted(counts.items())),
            "rows": {str(k): v for k, v in sorted(slots.items())}}


def body_index(path: Path) -> dict:
    lines = path.read_text().splitlines()
    starts = [(i, re.fullmatch(r"inline void (\w+_body_(\d+)_(\d+)_(\d+))\(.*", line))
              for i, line in enumerate(lines)]
    starts = [(i, m) for i, m in starts if m]
    result = {}
    for i, match in starts:
        depth = 0
        opened = False
        for end in range(i + 1, len(lines)):
            depth += lines[end].count("{") - lines[end].count("}")
            opened |= "{" in lines[end]
            if opened and depth == 0:
                break
        else:
            raise ValueError(f"unclosed body: {match[1]}")
        key = (int(match[2]), int(match[3]), int(match[4]))
        if key in result:
            raise ValueError(f"duplicate body: {key}")
        helpers = sorted(set(re.findall(r"n\.(FUN_[0-9a-fA-F]+)\(", "\n".join(lines[i:end + 1]))))
        result[key] = {"file": f"reference/source/{path.name}", "function": match[1],
                       "first_line": i + 1, "last_line": end + 1, "helpers": helpers}
    return result


def runtime_bindings(path: Path) -> tuple[dict, dict]:
    text = path.read_text()
    programs = {}
    # The shot array ends the required part; the optional trailing members (the
    # chase/dive policy pointers a recovered body attaches to a program) match
    # without being pinned, so adding a body does not read as a syntax change.
    pattern = r"static constexpr MoveProgram (\w+) = \{(k\w+Rules), std::size\(\2\),\s*\{\{(-?\d+),(-?\d+)\},\{(-?\d+),(-?\d+)\},\{(-?\d+),(-?\d+)\}\}(?:,[^;]*)?\};"
    for match in re.finditer(pattern, text):
        programs[match[1]] = {"rules": match[2], "shot": [int(v) for v in match.groups()[2:]]}
    declarations = re.findall(r"static constexpr MoveProgram (\w+) =", text)
    if set(declarations) != set(programs):
        raise ValueError("MoveProgram syntax changed; update binding reader instead of reporting missing coverage")
    bindings = {}
    for address, name in re.findall(r"if \(binding->handler == (0x[0-9a-fA-F]+)\) return &(\w+);", text):
        if name not in programs or int(address, 16) in bindings:
            raise ValueError("ambiguous runtime dispatch")
        bindings[int(address, 16)] = programs[name]
    if len(bindings) != len(programs):
        raise ValueError("unmapped runtime program")
    locomotion_text = text.split("inline constexpr LocomotionDefinition kLocomotion[] = {", 1)[1].split("};", 1)[0]
    handlers = {}
    for ch, we, address in re.findall(r"\{(\d+),(\d+),(0x[0-9a-fA-F]+),", locomotion_text):
        key = (int(ch), int(we))
        if key in handlers:
            raise ValueError("duplicate locomotion combo")
        handlers[key] = int(address, 16)
    return bindings, handlers


class Recon:
    def __init__(self, support: Path, reference: Path, runtime: Path):
        self.sources = {}
        manifest = {}
        for line in (support / "SHA256SUMS.txt").read_text().splitlines():
            sha, name = line.split(None, 1)
            manifest[name.strip()] = sha

        def support_file(name):
            path = support / name
            actual = digest(path)
            if actual != manifest.get(name):
                raise ValueError(f"bundle hash mismatch: {name}")
            self.sources[name] = actual
            return path

        roster_path = reference / "reference-data.json"
        roster = load_json(str(roster_path))
        check_exe(roster, "reference-data.json")
        self.sources["balance-reference/reference-data.json"] = digest(roster_path)
        self.roster = roster["roster"]
        keys = {(r["character"], r["weapon"]) for r in self.roster}
        swaps = {r["swap_to_code"] for r in self.roster}
        if len(self.roster) != 46 or len(keys) != 46 or swaps != set(range(1, 47)):
            raise ValueError("roster must contain 46 unique combos and swaps 1..46")
        self.catalogs = {}
        for name in ("combat-hooks", "attack-preview", "exe-catalog"):
            data = load_json(str(support_file(f"catalogs/{name}.json")))
            check_exe(data, name)
            self.catalogs[name] = data
        self.bodies = {}
        for name in BODY_FILES:
            for key, body in body_index(support_file(f"reference/source/{name}")).items():
                self.bodies.setdefault(key, []).append(body)
        self.traces = {}
        for name, expected in self.catalogs["attack-preview"]["sources"].items():
            path = support_file(f"traces/{name}")
            if self.sources[f"traces/{name}"] != expected:
                raise ValueError(f"preview/trace identity mismatch: {name}")
            groups = {}
            for line in path.read_text().splitlines():
                record = json.loads(line)
                key = (record["character"], record["weapon"], record["phase"])
                groups.setdefault(key, []).append(record)
            self.traces[name] = groups
        self.bindings, handlers = runtime_bindings(runtime)
        dispatch = self.catalogs["combat-hooks"]["dispatch"]
        if len(dispatch) != 46 or {(d["ch"], d["we"]) for d in dispatch} != keys or set(handlers) != keys:
            raise ValueError("dispatch/locomotion must cover exactly the roster")
        for entry in dispatch:
            key = (entry["ch"], entry["we"])
            if handlers[key] != entry["update"]:
                raise ValueError(f"dispatch/locomotion handler mismatch: {key}")
        self.sources["remake/foundation/src/gameplay/move_behavior.h"] = digest(runtime)

    def combo(self, character: int, weapon: int) -> dict:
        roster = next((r for r in self.roster if (r["character"], r["weapon"]) == (character, weapon)), None)
        if roster is None:
            raise ValueError(f"unknown character+weapon combo: {character}:{weapon}")
        hooks = self.catalogs["combat-hooks"]
        dispatch = [d for d in hooks["dispatch"] if (d["ch"], d["we"]) == (character, weapon)]
        if len(dispatch) != 1:
            raise ValueError("combo needs exactly one dispatch identity")
        preview = self.catalogs["attack-preview"]
        prefix = f"{character}:{weapon}:"
        swap = roster["swap_to_code"]
        return {
            "label": f"{roster['name_en']} {weapon}", "character": character, "weapon": weapon,
            "swap": swap, "item_id": roster["item_id"], "actor": roster["actor"], "item": roster["item"],
            "magazines": roster["magazines"], "dispatch": dispatch[0],
            "walk": self.catalogs["exe-catalog"]["walks"][f"{character}:{weapon}"],
            "births": {k: v for k, v in preview["births"].items() if k.split(":")[0] == str(swap)},
            "usage": {k: v for k, v in hooks["shot400_usage"].items() if k.startswith(prefix)},
            "preview_requests": {k: summarize_frames(v) for k, v in preview["shot400"].items() if k.startswith(prefix)},
            "extended_requests": {name: {str(phase): summarize_frames(frames)
                for (ch, we, phase), frames in groups.items() if (ch, we) == (character, weapon)}
                for name, groups in self.traces.items()},
            "bodies": {str(state): body for (ch, we, state), body in sorted(self.bodies.items())
                       if (ch, we) == (character, weapon)},
            "runtime_binding": self.bindings.get(dispatch[0]["update"]),
            "scope": "Forced-phase requests and static source ranges; no reachability, admission or geometry claim.",
        }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--character", type=int)
    parser.add_argument("--weapon", type=int)
    parser.add_argument("--all", action="store_true", help="inventory all 46 combos")
    parser.add_argument("--support", type=Path, default=Path(DEFAULT_SUPPORT))
    parser.add_argument("--reference", type=Path, default=Path(DEFAULT_REFERENCE))
    parser.add_argument("--output", type=Path, help="write a local JSON report instead of stdout")
    args = parser.parse_args()
    if args.all:
        if args.character is not None or args.weapon is not None:
            parser.error("--all cannot be combined with a combo selector")
    elif args.character is None or args.weapon is None:
        parser.error("provide both --character and --weapon, or --all")
    if args.output and any(args.output.resolve().is_relative_to(root.resolve())
                           for root in (args.support, args.reference)):
        parser.error("reports cannot overwrite read-only bundle inputs")
    try:
        recon = Recon(args.support, args.reference, REPO / "remake/foundation/src/gameplay/move_behavior.h")
        combos = [recon.combo(r["character"], r["weapon"]) for r in recon.roster] if args.all else [recon.combo(args.character, args.weapon)]
        report = {"exe_sha256": REFERENCE_EXE_SHA256, "sources": recon.sources, "combos": combos}
        result = json.dumps(report, indent=2, ensure_ascii=False) + "\n"
        if args.output:
            args.output.write_text(result)
        else:
            print(result, end="")
    except (ValueError, OSError, KeyError, IndexError) as error:
        parser.exit(1, f"recon: {error}\n")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
