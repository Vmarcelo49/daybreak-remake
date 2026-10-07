#!/usr/bin/env python3
"""Recover combo/handler bindings and immediate locomotion values; print evidence.

FUN_00649790 -> constructor -> original vtable +0x18. Never use constructor
order as a character id without reading the factory's character/slot branches.
Output is deliberately not a general C decompiler: missing/conditional values
are reported, not substituted with another fighter's tuning.
"""
import argparse
import pathlib
import re
import struct


def main():
    cli = argparse.ArgumentParser()
    cli.add_argument("exe", type=pathlib.Path)
    cli.add_argument("--repo", type=pathlib.Path, default=pathlib.Path("."))
    cli.add_argument("--dash-details", action="store_true")
    args = cli.parse_args()
    image = args.exe.read_bytes()
    pe = struct.unpack_from("<I", image, 0x3c)[0]
    count = struct.unpack_from("<H", image, pe + 6)[0]
    optional = struct.unpack_from("<H", image, pe + 20)[0]
    base = struct.unpack_from("<I", image, pe + 52)[0]
    sections = [struct.unpack_from("<8sIIII", image, pe + 24 + optional + 40 * i)
                for i in range(count)]

    def word(address):
        for _, virtual_size, va, raw_size, raw in sections:
            if va <= address - base < va + max(virtual_size, raw_size):
                return struct.unpack_from("<I", image, raw + address - base - va)[0]
        raise ValueError(f"unmapped address {address:x}")

    corpus = args.repo / "research/decompiled"
    factory = (corpus / "FUN_00649790.c").read_text()
    for character, branch in re.findall(r"case (0x[0-9a-f]+|\d+):(.*?)(?=\n  case |\n  default:|\Z)",
                                         factory, re.S):
        for slot, constructor in re.findall(
                r"if \(param_2 == (\d+)\).*?uVar2 = FUN_([0-9a-f]+)\(\)", branch, re.S):
            constructor_text = (corpus / f"FUN_{constructor}.c").read_text()
            table = int(re.search(r"PTR_(?:FUN|LAB)_([0-9a-f]+)", constructor_text)[1], 16)
            handler = word(table + 0x18)
            text = (corpus / f"FUN_{handler:08x}.c").read_text()
            cases = re.split(r"case (0x[0-9a-f]+|[0-9]+):", text)
            blocks = {int(cases[i], 0): cases[i + 1] for i in range(1, len(cases), 2)}

            def speeds(move):
                values = re.findall(r"param_1\[0x15\] = (0x[0-9a-f]+);", blocks.get(move, ""))
                return [struct.unpack("<f", struct.pack("<I", int(value, 16)))[0]
                        for value in values]

            print(character, slot, f"ctor={constructor}", f"vtable={table:08x}",
                  f"handler={handler:08x}", f"walk={speeds(10)}",
                  f"dash={speeds(20)}", f"air={speeds(30)}")
            if args.dash_details:
                block = blocks.get(20, "")
                decay = re.findall(r"param_1\[0x15\].*? - ([0-9.]+)\)", block)
                drain = re.findall(r"param_1\[0x20d\] \+ -(0x[0-9a-f]+|\d+)", block)
                hold = re.findall(r"param_1\[0x3a\] < (0x[0-9a-f]+|\d+)", block)
                hold_tick = re.findall(r"param_1\[0x2b81\] == (0x[0-9a-f]+|\d+)\) && \(param_1\[0x3a\]", block)
                steer = re.findall(r"param_1\[0x21d\] = (0x[0-9a-f]+);", block)
                print("  dash", "decay=", decay, "drain=", drain, "hold=", hold, "hold_tick=", hold_tick,
                      "steer=", [struct.unpack("<f",struct.pack("<I",int(v,16)))[0]
                                  for v in steer])


if __name__ == "__main__":
    main()
