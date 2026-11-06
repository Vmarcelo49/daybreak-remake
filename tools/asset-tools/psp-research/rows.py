"""Row id -> handler fn -> callees, plus per-weapon validity from .acv S4."""
import collections, os, re, sys, eboot as e

T = 0x1b08f4
N = 350
GEN = 0x77cd8

def handlers():
    return [(e.u32(T + i * 8), e.u32(T + i * 8 + 4)) for i in range(N)]

def ftext(addr):
    p = os.path.join(e.DECOMP, "%08x.c" % addr)
    return open(p, encoding="utf-8", errors="replace").read() if os.path.exists(p) else ""

def classify(fn):
    t = ftext(fn)
    calls = sorted(set(re.findall(r"\bFUN_[0-9a-f]{8}\b", t)))
    return t, calls

if __name__ == "__main__":
    hs = handlers()
    gen = [i for i, (f, _) in enumerate(hs) if GEN in classify(f)[1]]
    print("handlers that reference FUN_00077cd8: %d" % len(gen))
    print("their rows:", gen[:40], "...")
    # classify
    bins = collections.Counter()
    for i, (f, fl) in enumerate(hs):
        t, calls = classify(f)
        if GEN in calls: bins["generic"] += 1
        elif not t.strip(): bins["nodecomp"] += 1
        else: bins["other"] += 1
    print(bins)
    import acv
    for wp in "abcd":
        p = "../dump/activity_chr16%s.acv" % wp
        if not os.path.exists(p):
            continue
        a = acv.Acv(p)
        valid = [r for r, h in enumerate(a.handlers) if h != 0xffffffff]
        shared = [r for r in valid if GEN in classify(hs[a.handlers[r]][0])[1]]
        print("chr16%s: valid rows %d, generic-runner rows %d" % (wp, len(valid), len(shared)))
