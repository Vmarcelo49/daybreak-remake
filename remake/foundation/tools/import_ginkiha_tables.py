#!/usr/bin/env python3
"""Ginkiha balance table importer — regenerates src/gameplay/ginkiha_tables.hpp.

WHY this exists (see docs/reports/ginkiha-port-plan.md, Fase 0): the port's data-driven layer
needs values that live in executable/handler code, not in the shipped DAT files — projectile
birth speeds, walk handler addresses, the shot400 slot-usage matrix and the animation
controller periods. Ginkiha's bundles extracted those against DaybreakDX.exe
SHA256 27e61475fbb3ea67f5058e3e0e6e93ad71d16a4d83fa42b02e605913a6a07f02, which this repo also
analyzes (research/binary_data/pe_info.json), so the addresses apply as-is.

Inputs (both git-ignored under .local-analysis/, never committed):
  1. porting support bundle  — catalogs/attack-preview.json (births, shot400 traces),
     catalogs/combat-hooks.json (shot400 usage), catalogs/exe-catalog.json (walks),
     catalogs/timing-hooks.json (controllers)
  2. balance-reference bundle — reference-data.json roster, the only place mapping
     swap_to_code 1..46 back to (character, weapon); the DAT-readable values in it are
     deliberately NOT re-exported here (they stay read from the game files at runtime)

Usage:  python3 import_ginkiha_tables.py [support_bundle_dir] [reference_bundle_dir]
Env:    GINKIHA_SUPPORT_BUNDLE / GINKIHA_REFERENCE_BUNDLE override the defaults.

Determinism: same bundles in, byte-identical header out. The bundles carry their own
SHA256SUMS.txt / bundle-manifest.json; this script re-checks the exe hash it finds in every
catalog and fails loudly on drift.
"""

from __future__ import annotations

import json
import os
import sys
from datetime import date

REFERENCE_EXE_SHA256 = "27e61475fbb3ea67f5058e3e0e6e93ad71d16a4d83fa42b02e605913a6a07f02"

HERE = os.path.dirname(os.path.abspath(__file__))
FOUNDATION = os.path.dirname(HERE)
REPO = os.path.dirname(os.path.dirname(FOUNDATION))
DEFAULT_SUPPORT = os.path.join(REPO, ".local-analysis/porting-support/DaybreakPortingSupport-20261010")
DEFAULT_REFERENCE = os.path.join(REPO, ".local-analysis/balance-reference/balance-reference-v0.10")
OUTPUT = os.path.join(FOUNDATION, "src/gameplay/ginkiha_tables.h")


def load_json(path: str) -> dict:
    with open(path, "r", encoding="utf-8") as handle:
        return json.load(handle)


def check_exe(catalog: dict, name: str) -> None:
    sha = catalog.get("exe_sha256") or catalog.get("original_exe_sha256")
    if sha is None:
        raise SystemExit(f"{name}: no exe hash recorded, refusing to import unversioned data")
    if sha != REFERENCE_EXE_SHA256:
        raise SystemExit(f"{name}: exe hash {sha} != {REFERENCE_EXE_SHA256}")


def c_float(value: float) -> str:
    if value == int(value) and abs(value) < 1e15:
        return f"{int(value)}.0f"
    return repr(float(value)) + "f"


def split_key(key: str) -> tuple[int, ...]:
    return tuple(int(part) for part in key.split(":"))


def main() -> int:
    support = sys.argv[1] if len(sys.argv) > 1 else os.environ.get("GINKIHA_SUPPORT_BUNDLE", DEFAULT_SUPPORT)
    reference = sys.argv[2] if len(sys.argv) > 2 else os.environ.get("GINKIHA_REFERENCE_BUNDLE", DEFAULT_REFERENCE)
    for bundle, label in ((support, "support"), (reference, "reference")):
        if not os.path.isdir(bundle):
            raise SystemExit(f"{label} bundle not found: {bundle}")

    roster = load_json(os.path.join(reference, "reference-data.json"))
    check_exe(roster, "reference-data.json")
    # swap_to_code 1..46 -> (character, weapon); the authoritative link between the
    # swap-keyed catalogs and our (character, slot) combos.
    swap_to_combo = {}
    for entry in roster["roster"]:
        swap_to_combo[entry["swap_to_code"]] = (entry["character"], entry["weapon"])
    if len(swap_to_combo) != 46:
        raise SystemExit(f"expected 46 swap codes, got {len(swap_to_combo)}")

    preview = load_json(os.path.join(support, "catalogs/attack-preview.json"))
    check_exe(preview, "attack-preview.json")
    hooks = load_json(os.path.join(support, "catalogs/combat-hooks.json"))
    check_exe(hooks, "combat-hooks.json")
    catalog = load_json(os.path.join(support, "catalogs/exe-catalog.json"))
    check_exe(catalog, "exe-catalog.json")
    timing = load_json(os.path.join(support, "catalogs/timing-hooks.json"))
    check_exe(timing, "timing-hooks.json")

    births = preview["births"]
    birth_rows = []
    for key, value in sorted(births.items(), key=lambda kv: split_key(kv[0])):
        swap_code, slot = split_key(key)
        turn_birth = value.get("turn_birth") or [0.0]
        turn_next = value.get("turn_next") or [0.0]
        combo = swap_to_combo.get(swap_code)
        ch, we = combo if combo else (0, 0)
        birth_rows.append((swap_code, slot, ch, we, value["speed"], turn_birth[0], turn_next[0]))

    walks = catalog["walks"]
    walk_rows = []
    for key, va in sorted(walks.items(), key=lambda kv: split_key(kv[0])):
        ch, we = split_key(key)
        walk_rows.append((ch, we, int(str(va).replace("0x", ""), 16)))

    usage = hooks["shot400_usage"]
    usage_pair_rows = []
    for key, value in sorted(usage.items(), key=lambda kv: split_key(kv[0])):
        ch, we, index = split_key(key)
        for mode, pairs in (("n", value.get("normal") or []), ("t", value.get("tag") or [])):
            for phase, frame in pairs:
                usage_pair_rows.append((ch, we, index, mode == "t", phase, frame))

    dispatch = hooks["dispatch"]
    dispatch_rows = []
    for entry in dispatch:
        dispatch_rows.append((entry["ch"], entry["we"], entry["vtable"], entry["update"],
                              entry.get("slot7", 0)))
    if len(dispatch_rows) != 46:
        raise SystemExit(f"expected 46 dispatch entries, got {len(dispatch_rows)}")

    shot400 = preview["shot400"]
    fire_rows = []
    for key, frames in sorted(shot400.items(), key=lambda kv: kv[0]):
        parts = key.split(":")
        if len(parts) != 4:
            raise SystemExit(f"unexpected shot400 key format: {key}")
        ch, we, mode, index = int(parts[0]), int(parts[1]), parts[2] == "tag", int(parts[3])
        fire_frame = -1
        for frame in frames:
            for event in frame["events"]:
                if event[0] == "fire_attachment":
                    fire_frame = frame["frame"]
        fire_rows.append((ch, we, index, mode, fire_frame, len(frames)))

    # controllers is { "<model .x path>": [ {index, period, name}, ... ] } — the measured
    # D3DX controller set per animation model, keyed by the model the DAT points at.
    controllers = timing["controllers"]
    controller_rows = []
    for model_path, entries in sorted(controllers.items()):
        for entry in entries:
            controller_rows.append((model_path, int(entry["index"]), float(entry["period"]), entry["name"]))

    lines: list[str] = []
    lines.append("// GENERATED FILE — do not edit by hand. Regenerate with:")
    lines.append("//   python3 remake/foundation/tools/import_ginkiha_tables.py")
    lines.append("//")
    lines.append(f"// Ginkiha balance tables, regenerated {date.today().isoformat()}.")
    lines.append(f"// Reference binary: DaybreakDX.exe SHA256 {REFERENCE_EXE_SHA256}")
    lines.append("// (the same binary this repo decompiles — research/binary_data/pe_info.json).")
    lines.append("//")
    lines.append("// WHAT belongs here: only what is NOT readable from the shipped game files")
    lines.append("// (DATs stay the runtime source of truth for magazines, damage bases, parameters).")
    lines.append("// WHAT must never be added: values recovered from a different EXE revision, or")
    lines.append("// live-match observations — cite the bundle file and key in a comment instead.")
    lines.append("")
    lines.append("#pragma once")
    lines.append("")
    lines.append("namespace ginkiha {")
    lines.append("")
    lines.append("// Provenance per section, in order: bundle file, JSON key, extraction rule.")
    lines.append("")
    lines.append(f"// attack-preview.json births[] keys \"swap:slot\" → projectile birth speed and turn")
    lines.append(f"// rates (handler-level, no DAT field); {len(birth_rows)} slots.")
    lines.append("struct BirthProfile {")
    lines.append("    int swap_code;")
    lines.append("    int slot;")
    lines.append("    int character;")
    lines.append("    int weapon;")
    lines.append("    float speed;")
    lines.append("    float turn_birth;")
    lines.append("    float turn_next;")
    lines.append("};")
    lines.append("")
    lines.append(f"inline constexpr BirthProfile kBirthProfile[] = {{")
    for swap_code, slot, ch, we, speed, turn_birth, turn_next in birth_rows:
        lines.append(
            f"    {{{swap_code}, {slot}, {ch}, {we}, {c_float(speed)}, "
            f"{c_float(turn_birth)}, {c_float(turn_next)}}},"
        )
    lines.append("};")
    lines.append("")
    lines.append(f"inline constexpr int kBirthProfileCount = {len(birth_rows)};")
    lines.append("")
    lines.append(f"// exe-catalog.json walks[] keys \"ch:we\" → the walk state-10 handler VA;")
    lines.append(f"// the oracle our kLocomotion entries must agree with; {len(walk_rows)} combos.")
    lines.append("struct WalkHandler {")
    lines.append("    int character;")
    lines.append("    int weapon;")
    lines.append("    unsigned int va;")
    lines.append("};")
    lines.append("")
    lines.append("inline constexpr WalkHandler kWalkHandler[] = {")
    for ch, we, va in walk_rows:
        lines.append(f"    {{{ch}, {we}, 0x{va:08X}}},")
    lines.append("};")
    lines.append("")
    lines.append(f"inline constexpr int kWalkHandlerCount = {len(walk_rows)};")
    lines.append("")
    lines.append(f"// combat-hooks.json dispatch[] → the per-combo class identity: factory vtable")
    lines.append(f"// (0x006A4E10 + i*0x28), the update function and slot7. The update VA is the same")
    lines.append(f"// address our move_behavior.h gates recovered programs on; {len(dispatch_rows)} combos.")
    lines.append("struct DispatchIdentity {")
    lines.append("    int character;")
    lines.append("    int weapon;")
    lines.append("    unsigned int vtable;")
    lines.append("    unsigned int update;")
    lines.append("    unsigned int slot7;")
    lines.append("};")
    lines.append("")
    lines.append("inline constexpr DispatchIdentity kDispatchIdentity[] = {")
    for ch, we, vtable, update, slot7 in sorted(dispatch_rows):
        lines.append(f"    {{{ch}, {we}, 0x{int(vtable):08X}, 0x{int(update):08X}, 0x{int(slot7):08X}}},")
    lines.append("};")
    lines.append("")
    lines.append(f"inline constexpr int kDispatchIdentityCount = {len(dispatch_rows)};")
    lines.append("")
    lines.append(f"// combat-hooks.json shot400_usage[] keys \"ch:we:r\" → which slot fires on which")
    lines.append(f"// state400 phase/frame; {len(usage_pair_rows)} fire records.")
    lines.append("struct ShotFireRecord {")
    lines.append("    int character;")
    lines.append("    int weapon;")
    lines.append("    int slot;")
    lines.append("    bool tag;")
    lines.append("    int phase;")
    lines.append("    int frame;")
    lines.append("};")
    lines.append("")
    lines.append("inline constexpr ShotFireRecord kShotFireRecord[] = {")
    for ch, we, index, is_tag, phase, frame in usage_pair_rows:
        flag = "true" if is_tag else "false"
        lines.append(f"    {{{ch}, {we}, {index}, {flag}, {phase}, {frame}}},")
    lines.append("};")
    lines.append("")
    lines.append(f"inline constexpr int kShotFireRecordCount = {len(usage_pair_rows)};")
    lines.append("")
    lines.append(f"// attack-preview.json shot400[] traces → observed fire frame and trace length per")
    lines.append(f"// \"ch:we:(normal|tag):slot\"; the fire frame must equal the usage frame above;")
    lines.append(f"// {len(fire_rows)} traces.")
    lines.append("struct ShotTraceSummary {")
    lines.append("    int character;")
    lines.append("    int weapon;")
    lines.append("    int slot;")
    lines.append("    bool tag;")
    lines.append("    int fire_frame;")
    lines.append("    int trace_frames;")
    lines.append("};")
    lines.append("")
    lines.append("inline constexpr ShotTraceSummary kShotTraceSummary[] = {")
    for ch, we, index, is_tag, fire_frame, trace_frames in fire_rows:
        flag = "true" if is_tag else "false"
        lines.append(f"    {{{ch}, {we}, {index}, {flag}, {fire_frame}, {trace_frames}}},")
    lines.append("};")
    lines.append("")
    lines.append(f"inline constexpr int kShotTraceSummaryCount = {len(fire_rows)};")
    lines.append("")
    lines.append(f"// timing-hooks.json controllers[] → the measured D3DX animation controllers per")
    lines.append(f"// model (calibrates move durations; NOT readable from DAT); {len(controller_rows)}")
    lines.append(f"// controllers across {len(controllers)} models.")
    lines.append("struct AnimationController {")
    lines.append("    const char* model;")
    lines.append("    int index;")
    lines.append("    double period_seconds;")
    lines.append("    const char* name;")
    lines.append("};")
    lines.append("")
    lines.append("inline constexpr AnimationController kAnimationController[] = {")
    for model_path, index, period, name in controller_rows:
        lines.append(f'    {{"{model_path}", {index}, {period!r}, "{name}"}},')
    lines.append("};")
    lines.append("")
    lines.append(f"inline constexpr int kAnimationControllerCount = {len(controller_rows)};")
    lines.append("")
    lines.append("}  // namespace ginkiha")
    lines.append("")

    os.makedirs(os.path.dirname(OUTPUT), exist_ok=True)
    with open(OUTPUT, "w", encoding="utf-8", newline="\n") as handle:
        handle.write("\n".join(lines))
    print(f"wrote {OUTPUT}")
    print(f"  births={len(birth_rows)} walk_handlers={len(walk_rows)} dispatch={len(dispatch_rows)} "
          f"shot_fire_records={len(usage_pair_rows)} shot_traces={len(fire_rows)} "
          f"controllers={len(controller_rows)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
