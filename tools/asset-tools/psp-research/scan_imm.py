"""Scan .text for loads/stores/immediates referencing a given constant offset.

Usage: python3 scan_imm.py 0x1994 [0x1998 ...]
       python3 scan_imm.py --range 0x1900 0x1a00

Prints "vaddr  fn  instruction" for every lw/sw/lb/sb/lh/sh/lwc1/swc1/ll/sc whose
signed 16-bit immediate equals the value, plus ori/addiu/lui pairs for 32-bit constants.
"""
import sys, struct
import eboot as e, mips as m

TEXT_START, TEXT_END = 0x40, 0x168690
LOADS = {0x20: "lb", 0x21: "lh", 0x23: "lw", 0x24: "lbu", 0x25: "lhu", 0x28: "sb",
         0x29: "sh", 0x2b: "sw", 0x31: "lwc1", 0x39: "swc1", 0x30: "ll", 0x38: "sc"}


def scan(target, text_start=TEXT_START, text_end=TEXT_END):
    d = e.data()
    out = []
    for va in range(text_start, text_end, 4):
        w = struct.unpack_from("<I", d, va + e.B)[0]
        op = w >> 26
        imm = struct.unpack("<h", struct.pack("<H", w & 0xffff))[0]
        if op in LOADS and imm == target:
            out.append((va, m.decode(va)))
        elif op in (0x0d, 0x09, 0x0c) and (w & 0xffff) == (target & 0xffff):
            # ori / addiu / andi with the low half
            out.append((va, m.decode(va)))
    return out


def main():
    if sys.argv[1] == "--range":
        lo, hi = int(sys.argv[2], 0), int(sys.argv[3], 0)
        targets = range(lo, hi, 4)
    else:
        targets = [int(x, 0) for x in sys.argv[1:]]
    for t in targets:
        rows = scan(t)
        if not rows:
            continue
        print("=== imm %#x (%d hits)" % (t, len(rows)))
        for va, ins in rows:
            fn = e.func_at(va)
            print("  %08x  %-16s %s" % (va, fn[1] if fn else "-", ins))


if __name__ == "__main__":
    main()
