#!/usr/bin/env python3
"""Issue #90: a translated sheet the device refuses still draws, from a smaller copy.

A refused texture used to leave a handle that binds nothing, so its quads drew the previous sheet.
Tier 5, on our own build; --texture-limit stands in for a machine short of memory. Skips without an install.
"""
import pathlib
import subprocess
import sys
import tempfile

SCRIPT = pathlib.Path(__file__).resolve().parent / "scripts" / "select-slidein.txt"
WIDTH, HEIGHT = 1280, 720
# The character name plate, the draw the report showed wrong.
PLATE = (234, 70, 541, 146)


def capture(demo, install, folder, name, *extra):
    out = folder / f"{name}.ppm"
    run = subprocess.run([demo, f"--install={install}", "--screen=title", "--local-players=1", f"--script={SCRIPT}",
                          "--language=en", "--no-audio", "--headless", f"--out={out}", f"--size={WIDTH}x{HEIGHT}",
                          "--frames=110", *extra], capture_output=True, text=True, timeout=180)
    log = run.stdout + run.stderr
    assert "RESULT: ok" in log, f"{name}: {log[-400:]}"
    data = out.read_bytes()
    return data[len(data) - WIDTH * HEIGHT * 3:], log


def plate_difference(a, b):
    x0, y0, x1, y1 = PLATE
    total = 0
    for y in range(y0, y1):
        start, end = (y * WIDTH + x0) * 3, (y * WIDTH + x1) * 3
        total += sum(abs(p - q) for p, q in zip(a[start:end], b[start:end]))
    return total / ((x1 - x0) * (y1 - y0) * 3)


def main():
    demo, install = sys.argv[1], sys.argv[2]
    if not pathlib.Path(install, "data").is_dir():
        print("SKIP: no game data")
        return 77
    with tempfile.TemporaryDirectory() as name:
        folder = pathlib.Path(name)
        full, log = capture(demo, install, folder, "full")
        assert "failed, trying half" not in log, "the plain run should not fall back"
        limited, log = capture(demo, install, folder, "limited", "--texture-limit=1024")
        assert "failed, trying half" in log, "the limit never reached a sheet"
        assert "uncaptured error" not in log, "a refused texture reached the device's uncaptured path"
    difference = plate_difference(full, limited)
    print(f"plate difference {difference:.2f} of 255")
    assert difference < 6, "the plate is not the same sheet any more"
    print("texture_fallback_check: ok")
    return 0


if __name__ == "__main__":
    sys.exit(main())
