#!/usr/bin/env python3
"""Compare visible translated cells on actual English and Japanese port captures.

This checks selected deterministic states, not every possible UI state or OCR. The
owner-approved title logo, movies, story dialogue and player names are excluded.
"""
import pathlib
import re
import subprocess
import sys
import tempfile

ROOT = pathlib.Path(__file__).resolve().parents[1]
WIDTH, HEIGHT = 800, 600


def capture(exe, install, directory, name, language, args):
    out = directory / f"{name}-{language}.ppm"
    run = subprocess.run([exe, f"--install={install}", "--headless", "--no-audio",
                          f"--language={language}", f"--out={out}", "--size=800x600", *args],
                         stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, timeout=120)
    if run.returncode != 0 or "RESULT: ok" not in run.stdout:
        raise AssertionError(f"{name} {language}: {run.stdout[-2000:]}")
    data = out.read_bytes()
    marker = b"\n255\n"
    end = data.find(marker)
    assert end >= 0 and len(data) - end - len(marker) == WIDTH * HEIGHT * 3
    return data[end + len(marker):], run.stdout


def check_regions(name, english, japanese, regions):
    for rect in regions:
        x0, y0, x1, y1 = rect
        difference = 0
        for y in range(y0, y1):
            start = (y * WIDTH + x0) * 3
            end = (y * WIDTH + x1) * 3
            difference += sum(abs(a - b) for a, b in zip(english[start:end], japanese[start:end]))
        assert difference > 5000, f"{name}: no meaningful translation difference in {rect}: {difference}"


def main():
    exe, install = sys.argv[1:]
    if not (pathlib.Path(install) / "daybreak00.dat").exists():
        print("SKIP: no game install")
        return 77
    stage_script = ROOT / "tests/scripts/frontend-com-rematch.txt"
    cases = [
        ("title", ["--screen=title", "--frames=90"], [(300, y, 500, y + 42) for y in range(285, 573, 48)]),
        ("select", ["--screen=title", "--local-players=1", f"--script={ROOT / 'tests/scripts/select-slidein.txt'}", "--frames=110"], [(230, 68, 570, 150)]),
        ("stage", ["--screen=title", "--local-players=1", f"--script={stage_script}", "--frames=310"], [(45, y, 305, y + 28) for y in (110, 260, 310, 360, 410, 460, 540)]),
        ("storyteam", ["--screen=storyteam", "--frames=90"], [(300, 5, 500, 50), (270, 305, 530, 350), (270, 355, 530, 400), (300, 410, 510, 440)]),
        ("options", ["--screen=options", "--frames=90"], [(300, 50, 500, 90), (130, 125, 320, 155)]),
        ("keyconfig", ["--screen=keyconfig", "--frames=90"], [(280, 25, 520, 60), (130, 100, 300, 130)]),
        ("online", ["--screen=netplay", "--frames=90"], [(300, 50, 500, 90), (130, 105, 320, 135)]),
    ]
    with tempfile.TemporaryDirectory() as tmp:
        directory = pathlib.Path(tmp)
        for name, args, regions in cases:
            en, _ = capture(exe, install, directory, name, "en", args)
            ja, _ = capture(exe, install, directory, name, "ja", args)
            check_regions(name, en, ja, regions)
            print(f"{name}: {len(regions)} visible regions differ")
        keep_alive = ",".join(f"f1@{tick}" for tick in range(0, 3600, 120))
        report_args = ["--screen=title", "--local-players=1", f"--script={stage_script}",
                       f"--debug-keys={keep_alive}", "--frames=5025"]
        en, log = capture(exe, install, directory, "report", "en", report_args)
        assert "[menu] scene: result" in log, "report capture never reached results"
        titles = re.findall(r"\[title\] panel \d+ fighter \d+ -> \d+ '([^']*)'", log)
        assert len(titles) == 4 and all(title and title.isascii() for title in titles), titles
        ja, log = capture(exe, install, directory, "report", "ja", report_args)
        assert "[menu] scene: result" in log, "Japanese report capture never reached results"
        check_regions("report", en, ja, [(260, 5, 540, 50), (300, 125, 760, 156),
                                         (300, 197, 760, 228), (300, 269, 760, 300),
                                         (300, 341, 760, 372)])
        print("report: header and four earned titles differ")
    print("locale_screen_check: sampled translated screen regions ok")
    return 0


if __name__ == "__main__":
    sys.exit(main())
