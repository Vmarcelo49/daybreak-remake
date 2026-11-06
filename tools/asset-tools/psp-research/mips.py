"""Minimal MIPS32 (Allegrex) decoder sufficient for reading call sites / struct accesses."""
import struct, eboot as e

REGS = ("zero at v0 v1 a0 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 "
        "s0 s1 s2 s3 s4 s5 s6 s7 t8 t9 k0 k1 gp sp fp ra").split()

I_ALU = {0x08:"addi",0x09:"addiu",0x0a:"slti",0x0b:"sltiu",0x0c:"andi",0x0d:"ori",0x0e:"xori"}
SHIFT = {0x00:"sll",0x02:"srl",0x03:"sra"}
BR = {0x04:"beq",0x05:"bne",0x06:"blez",0x07:"bgtz"}
LOADS = {0x20:"lb",0x21:"lh",0x23:"lw",0x24:"lbu",0x25:"lhu",0x28:"sb",0x29:"sh",0x2b:"sw",
         0x31:"lwc1",0x39:"swc1",0x26:"lwr",0x2e:"swr",0x22:"lwl",0x2a:"swl"}
EXTRA = {0x1f:"",0x1e:"",0x2f:"cache",0x30:"ll",0x38:"sc"}
FPU = {"add.s","sub.s","mul.s","div.s","sqrt.s","abs.s","mov.s","neg.s","cvt.s.w","cvt.w.s",
       "trunc.w.s","ceil.w.s","floor.w.s","round.w.s"}
FMT = {"s":0,"d":1,"w":4,"l":5}

def immi(w): return struct.unpack("<h", struct.pack("<H", w & 0xffff))[0]

def reg(w, s): return REGS[(w >> s) & 0x1f]

def decode(vaddr):
    w = e.u32(vaddr)
    op = w >> 26
    rs, rt, rd = reg(w,21), reg(w,16), reg(w,11)
    sa = (w >> 6) & 0x1f
    fn = w & 0x3f
    if w == 0: return "nop"
    if op == 0:
        if fn == 0x08: return "jr %s" % rs
        if fn == 0x09: return "jalr %s" % rs
        if fn == 0x0c: return "syscall"
        if fn == 0x0d: return "break"
        if fn == 0x10: return "mfhi %s" % rd
        if fn == 0x12: return "mflo %s" % rd
        if fn == 0x11: return "mthi %s" % rs
        if fn == 0x13: return "mtlo %s" % rs
        if fn in (0x18,0x19,0x1a,0x1b): return "%s %s,%s,%s" % ({0x18:"mult",0x19:"multu",0x1a:"div",0x1b:"divu"}[fn], rs, rt, "")
        if fn in (0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x2a,0x2b):
            n = {0x20:"add",0x21:"addu",0x22:"sub",0x23:"subu",0x24:"and",0x25:"or",0x26:"xor",
                 0x27:"nor",0x2a:"slt",0x2b:"sltu"}[fn]
            return "%s %s,%s,%s" % (n, rd, rs, rt)
        if fn in SHIFT: return "%s %s,%s,%d" % (SHIFT[fn], rd, rt, sa)
        if fn in (0x04,0x06,0x07): return "%s %s,%s,%d" % ({0x04:"sllv",0x06:"srlv",0x07:"srav"}[fn], rd, rt, rs)
        if fn == 0x02: return "srl %s,%s,%d" % (rd, rt, sa)
        if 0x30 <= fn <= 0x3f:
            fmt = (w >> 21) & 0x1f
            f = {0x30:"add",0x31:"sub",0x32:"mul",0x33:"div",0x34:"sqrt",0x35:"abs",0x36:"mov",
                 0x37:"neg"}.get(fn)
            fd = (w >> 6) & 0x1f
            fs = (w >> 11) & 0x1f
            ft = (w >> 16) & 0x1f
            if f:
                return "%s%s f%d,f%d,f%d" % (f, "." + {0:".s",1:".d",4:".w"}.get(fmt,"?"), fd, fs, ft)
            if fn in (0x3c,0x3d): return "c.%s.%s f%d,f%d" % ("lt" if fn==0x3c else "eq", "s" if fmt==0 else "d", fs, ft)
            return "fpu? %08x" % w
        return ".word %08x" % w
    if op in I_ALU: return "%s %s,%s,%d" % (I_ALU[op], rt, rs, immi(w))
    if op in BR:
        off = immi(w) << 2
        return "%s %s,%s,%#x" % (BR[op], rs, rt, vaddr + 4 + off)
    if op == 1:
        rt = (w >> 16) & 0x1f
        n = {0:"bltz",1:"bgez",0x10:"bltzal",0x11:"bgezal"}.get(rt, "bcond%d" % rt)
        return "%s %s,%#x" % (n, rs, vaddr + 4 + (immi(w) << 2))
    if op == 2: return "j %#x" % (((vaddr + 4) & 0xf0000000) | ((w & 0x3ffffff) << 2))
    if op == 3: return "jal %#x" % (((vaddr + 4) & 0xf0000000) | ((w & 0x3ffffff) << 2))
    if op in LOADS:
        return "%s %s,%d(%s)" % (LOADS[op], rt, immi(w), rs)
    if op == 0x0f: return "lui %s,%#06x" % (rt, w & 0xffff)
    if op == 0x0a: return "slti %s,%s,%d" % (rt, rs, immi(w))
    if op == 0x0b: return "sltiu %s,%s,%d" % (rt, rs, immi(w))
    if op == 0x0c: return "andi %s,%s,%#x" % (rt, rs, w & 0xffff)
    if op == 0x0d: return "ori %s,%s,%#x" % (rt, rs, w & 0xffff)
    if op == 0x0e: return "xori %s,%s,%#x" % (rt, rs, w & 0xffff)
    if op == 0x1c:  # Allegrex VFPU etc.
        return "vfpu? %08x" % w
    return ".word %08x" % w

def dis(vaddr, n):
    out = []
    for i in range(n):
        a = vaddr + 4 * i
        out.append("%08x: %s" % (a, decode(a)))
    return "\n".join(out)

if __name__ == "__main__":
    import sys
    a = int(sys.argv[1], 16); n = int(sys.argv[2]) if len(sys.argv) > 2 else 20
    print(dis(a, n))
