"""Helpers for reading the decrypted PSP EBOOT (PRX, image at address 0).

file offset = vaddr + 0xc0 for .text/.rodata/.data
sections (vaddr): .text 0x40, .rodata 0x18d0c0 (+0x52c7c), .data 0x1e3a80 (+0xe44c)
(all given as file offsets in the task; vaddr = fileoff - 0xc0)
"""
import os, re, struct

HERE = os.path.dirname(os.path.abspath(__file__))
PSP = os.path.normpath(os.path.join(HERE, ".."))
EBOOT = os.path.join(PSP, "EBOOT.dec")
DECOMP = os.path.join(PSP, "decomp")
B = 0xc0  # file offset bias

_data = None
def data():
    global _data
    if _data is None:
        _data = open(EBOOT, "rb").read()
    return _data

def off(vaddr):
    return vaddr + B

def u8(vaddr):  return data()[off(vaddr)]
def u16(vaddr): return struct.unpack_from("<H", data(), off(vaddr))[0]
def u32(vaddr): return struct.unpack_from("<I", data(), off(vaddr))[0]
def s32(vaddr): return struct.unpack_from("<i", data(), off(vaddr))[0]
def f32(vaddr): return struct.unpack_from("<f", data(), off(vaddr))[0]
def bytes_at(vaddr, n): return data()[off(vaddr):off(vaddr) + n]
def cstr(vaddr, n=128):
    b = bytes_at(vaddr, n)
    z = b.find(b"\0")
    return (b if z < 0 else b[:z]).decode("latin-1")

# ---- function index -------------------------------------------------------
_index = None
def index():
    """[(addr, name, size)] sorted by addr, plus dict by addr."""
    global _index
    if _index is None:
        rows = []
        for line in open(os.path.join(DECOMP, "_index.txt")):
            p = line.split()
            if len(p) >= 3:
                rows.append((int(p[0], 16), p[1], int(p[2])))
        rows.sort()
        _index = rows
    return _index

def func_at(addr):
    """Function containing addr -> (start, name, size) or None."""
    best = None
    for a, n, s in index():
        if a <= addr < a + s:
            best = (a, n, s)
        if a > addr:
            break
    return best

def decomp_file(fname):
    return os.path.join(DECOMP, fname)

def src(addr):
    """Decompiled C text of the function at addr (must be a function start)."""
    p = os.path.join(DECOMP, "%08x.c" % addr)
    if not os.path.exists(p):
        return None
    return open(p, encoding="utf-8", errors="replace").read()

def callers(fnname):
    """Functions whose decomp text mentions fnname."""
    out = []
    for a, n, s in index():
        p = os.path.join(DECOMP, "%08x.c" % a)
        if not os.path.exists(p):
            continue
        t = open(p, encoding="utf-8", errors="replace").read()
        if fnname in t:
            out.append((a, n, s))
    return out

def calls_in(addr):
    """[(addr, name)] of FUN_/PTR_ references in a function's decomp text."""
    t = src(addr) or ""
    seen = []
    for m in re.finditer(r"\b(FUN_[0-9a-f]{8}|PTR_[A-Za-z_0-9]+|DAT_[0-9a-f]{8})\b", t):
        if m.group(1) not in seen:
            seen.append(m.group(1))
    return seen

# ---- tables ---------------------------------------------------------------
def table_u32(vaddr, n):
    return [u32(vaddr + 4 * i) for i in range(n)]

def dump_floats(vaddr, n):
    return [f32(vaddr + 4 * i) for i in range(n)]
