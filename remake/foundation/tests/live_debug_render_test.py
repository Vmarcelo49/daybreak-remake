#!/usr/bin/env python3
"""Opt-in visible Linux integration test; the supplied session belongs to its game."""
import argparse
import json
from pathlib import Path
import sys
import time
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
from live_debug import Client

p = argparse.ArgumentParser(description=__doc__)
p.add_argument("session")
p.add_argument("--output", required=True, type=Path)
a = p.parse_args()
c = Client(a.session)
records = []


def command(text):
    r = c.command(text)
    records.append({"command": text, "result": r})
    return r


try:
    initial = command("PAUSE")
    time.sleep(0.1)
    frozen = command("STATUS")
    assert frozen["tick"] == initial["tick"]
    assert frozen["renders"] > initial["renders"]
    n = command("STEP 100")
    assert n["tick"] == frozen["tick"] + 100
    assert Path(n["screenshot"]).read_bytes().startswith(b"P6\n")
    time.sleep(0.1)
    assert command("STATUS")["tick"] == n["tick"]
    start = n["tick"]
    command("INPUT 0 1 Lock")
    command("STEP 2")
    command("BREAK state 0 -1 0 1")
    edge = command("INPUT 0 1 Jump")
    stopped = command("STEP 10")
    assert stopped["tick"] == start + 3 == edge["first_tick"]
    assert stopped["reason"] == "state"
    assert stopped["fighters"][0]["pressed"] == ["Jump"]
    assert stopped["fighters"][0]["airborne"]
    assert Path(stopped["screenshot"]).exists()
    time.sleep(0.1)
    assert command("STATUS")["tick"] == stopped["tick"]
    released = command("STEP 1")
    assert "Jump" in released["fighters"][0]["released"]
    command("CLEAR")
    command("STEP 6")
    command("INPUT 0 1 Forward")
    command("INPUT 0 1 -")
    command("INPUT 0 1 Forward")
    dash = command("STEP 3")
    f = dash["fighters"][0]
    assert f["air_dash"] and f["airborne"]
    command("INPUT 0 1 Attack")
    command("BREAK move 0 332 0 1")
    attack = command("STEP 40")
    assert attack["reason"] == "move"
    f = attack["fighters"][0]
    assert f["attack_move"] == f["bound_move"] == 332
    assert f["tag"] == f["set"] == 83 and not f["fallback"]
    assert not f["volume"]["active"] and not f["contact"]
    command("CLEAR")
    command("BREAK volume 0 -1 0 1")
    volume = command("STEP 30")
    assert volume["reason"] == "volume"
    assert volume["fighters"][0]["record"]["radius"] != 0
    assert volume["fighters"][0]["volume"]["active"]
    assert not volume["fighters"][0]["contact"], "distant enemy should remain a whiff"
    command("CLEAR")
    print("LIVE_DEBUG_RENDER: exact stepping, rendering while frozen, ordered edges, state/move/volume breakpoints and synchronized image paths passed")
finally:
    c.close()
    a.output.write_text(json.dumps(records, indent=2) + "\n")
