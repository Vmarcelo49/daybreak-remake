#!/usr/bin/env python3
"""A PSP fighter's finished match reaches its result screen and leaves it.

Issue #91's criterion is a whole match: start, KO or time, results. The battle for the three PSP
fighters belongs to other tracks, so this drives the screen the match ends on directly:
`--screen=result --result-winner=<dir>:<weapon>` opens it on a finished 1v1 that fighter won, the
same slots and outcome the host writes when a round resolves. Two confirms then walk the quote and
the report, which must land on the selection.

Cases, each a real headless capture of the product:
  * a PSP winner WITH the converted art (a temp psp-data holding a 512x512 data/win/16a.cnv): the
    portrait is drawn;
  * a PSP winner WITHOUT any art (an empty psp-data): the screen must not refuse, draws no
    portrait, and still reaches the selection;
  * the PC control (Rena 0): unchanged — her shipped portrait and her shipped quote.

The PSP art used here is synthetic (a flat-colour sheet), so no PSP file is needed and nothing from
the ISO is read. Skips (77) without the PC game install.
"""
import pathlib
import struct
import subprocess
import sys
import tempfile

WIDTH, HEIGHT = 800, 600
# The 1v1 winner portrait's quad (screen_result.cpp): (144,60) 512x512, under the bands at y 424.
PORTRAIT = (144 + 128, 60 + 128, 144 + 384, 60 + 300)
MAGENTA = (255, 0, 255)


def win_sheet(path):
    """A 512x512 CNV image: opaque magenta, the colour the portrait check looks for."""
    path.parent.mkdir(parents=True, exist_ok=True)
    header = struct.pack("<BIIII", 32, 512, 512, 512, 0)
    pixel = bytes((MAGENTA[2], MAGENTA[1], MAGENTA[0], 255))     # BGRA
    path.write_bytes(header + pixel * (512 * 512))


def run(exe, install, out, args, frames, script=None):
    command = [exe, f"--install={install}", "--headless", "--no-audio", "--screen=result",
               f"--frames={frames}", "--size=800x600", f"--out={out}", *args]
    if script:
        command.append(f"--menu-script={script}")
    done = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True,
                          timeout=180)
    return done.returncode, done.stdout


def pixels(path):
    data = path.read_bytes()
    marker = b"\n255\n"
    end = data.find(marker)
    assert end >= 0 and len(data) - end - len(marker) == WIDTH * HEIGHT * 3, path
    return data[end + len(marker):]


def magenta_share(frame, rect):
    x0, y0, x1, y1 = rect
    hits = total = 0
    for y in range(y0, y1, 4):
        for x in range(x0, x1, 4):
            i = (y * WIDTH + x) * 3
            r, g, b = frame[i], frame[i + 1], frame[i + 2]
            hits += r > 200 and g < 60 and b > 200
            total += 1
    return hits / total


def main():
    exe, install = sys.argv[1:3]
    if not (pathlib.Path(install) / "daybreak00.dat").exists():
        print("SKIP: no game install")
        return 77
    failures = []
    with tempfile.TemporaryDirectory() as temp:
        temp = pathlib.Path(temp)
        with_art = temp / "with-art"
        win_sheet(with_art / "data" / "win" / "16a.cnv")
        no_art = temp / "no-art"
        no_art.mkdir()
        script = temp / "confirm.txt"
        script.write_text("WAIT 10\nCONFIRM\nWAIT 10\nCONFIRM\n")

        cases = [
            ("satoshi-with-art", [f"--psp-data={with_art}", "--result-winner=satoshi:3"], "portrait"),
            ("okonogi-no-art", [f"--psp-data={no_art}", "--result-winner=okonogi:1"], "empty"),
            ("rena-control", ["--result-winner=rena:0"], "quote"),
        ]
        for name, args, expect in cases:
            # 1. The screen opens, and what it draws for the winner.
            shot = temp / f"{name}.ppm"
            code, output = run(exe, install, shot, args, 30)
            if code != 0 or "RESULT: ok" not in output:
                failures.append(f"{name}: the result screen did not open:\n{output[-1500:]}")
                continue
            share = magenta_share(pixels(shot), PORTRAIT)
            if expect == "portrait" and share < 0.9:
                failures.append(f"{name}: the psp-data portrait is not drawn ({share:.2f})")
            if expect == "empty" and share > 0.0:
                failures.append(f"{name}: a portrait appeared with no art ({share:.2f})")
            if expect == "quote" and "script data/scenario/win/00-00-" not in output:
                failures.append(f"{name}: the PC winner lost its shipped quote:\n{output[-800:]}")
            if expect != "quote" and "script  persona" not in output:
                failures.append(f"{name}: a PSP winner read a win script:\n{output[-800:]}")
            # 2. Two confirms walk quote -> report -> the selection.
            code, output = run(exe, install, temp / f"{name}-leave.ppm", args, 90, script)
            if code != 0 or "RESULT: ok" not in output or "[menu] scene: select" not in output:
                failures.append(f"{name}: the result screen did not lead back to the selection:\n"
                                f"{output[-1500:]}")
    for failure in failures:
        print("FAIL", failure)
    if failures:
        return 1
    print("psp_result_check: PSP winners open and leave the result screen with and without art; "
          "the PC control is unchanged")
    return 0


if __name__ == "__main__":
    sys.exit(main())
