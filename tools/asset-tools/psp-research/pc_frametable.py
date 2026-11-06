"""Read a PC `data/<char>/NN.dat` frame table (the layout the core's
`actor_frame_data.hpp` parses) and report states -> phases -> animation set index.

    python3 pc_frametable.py <file.dat> [--json out.json] [--sets 0,1,2]
"""
import json
import struct
import sys


def read(path, has_params=True):
    b = open(path, "rb").read()
    pos = 0

    def word():
        nonlocal pos
        v = struct.unpack_from("<I", b, pos)[0]
        pos += 4
        return v

    def integer():
        nonlocal pos
        v = struct.unpack_from("<i", b, pos)[0]
        pos += 4
        return v

    def text(n):
        nonlocal pos
        raw = b[pos:pos + n]
        pos += n
        return raw.split(b"\0", 1)[0].decode("cp932", "replace")

    out = {"magic": word(), "model": text(260), "parameters": [word() for _ in range(6)] if has_params else []}
    states = []
    for _ in range(word()):
        st = {"id": word(), "a": word(), "b": word(), "phases": []}
        for _ in range(word()):
            ph = {"set": word(), "frames": []}
            for _ in range(word()):
                ph["frames"].append({
                    "bone": text(30), "start": integer(),
                    "first": [integer() for _ in range(3)], "extent": word(),
                    "fields": [word() for _ in range(20)],
                    "flags28": word(), "flags2c": word(), "shape": word(),
                    "second": [integer() for _ in range(3)],
                })
            st["phases"].append(ph)
        states.append(st)
    out["states"] = states
    out["consumed"] = pos
    out["bytes"] = len(b)
    return out


def main():
    path = sys.argv[1]
    d = read(path)
    print("%s: %d bytes, model %r, %d states, consumed %d"
          % (path, d["bytes"], d["model"], len(d["states"]), d["consumed"]))
    for st in d["states"]:
        print("  state %3d (%d,%d): sets %s" % (st["id"], st["a"], st["b"],
              [p["set"] for p in st["phases"]]))
    if "--json" in sys.argv:
        json.dump(d, open(sys.argv[sys.argv.index("--json") + 1], "w"))


if __name__ == "__main__":
    main()
