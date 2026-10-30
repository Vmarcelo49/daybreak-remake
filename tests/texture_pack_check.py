#!/usr/bin/env python3
"""tools/asset-tools/texture_pack.py against the install: what it extracts, and what verify refuses."""
import subprocess
import sys
import tempfile
from pathlib import Path

try:
    from PIL import Image
except ImportError:
    print("SKIP: no Pillow")
    sys.exit(77)

ROOT = Path(__file__).resolve().parents[1]
INSTALL = ROOT / "Higurashi-Daybreak"
TOOL = ROOT / "tools" / "asset-tools" / "texture_pack.py"


def run(*args):
    return subprocess.run([sys.executable, str(TOOL), *args], capture_output=True, text=True)


def verify(pack):
    return run("verify", "--install", str(INSTALL), "--pack", str(pack))


def expect_refused(pack, broken, word):
    result = verify(pack)
    assert result.returncode == 1 and word in result.stdout, (broken, result.stdout)


def main():
    if not (INSTALL / "daybreak00.dat").exists():
        print("SKIP: no install")
        return 77
    with tempfile.TemporaryDirectory() as folder:
        pack = Path(folder) / "pack"
        done = run("extract", "--install", str(INSTALL), "--out", str(pack), "--only", "data/aura,data/stage01,data/directx")
        assert done.returncode == 0, done.stderr
        names = {p.relative_to(pack).as_posix() for p in pack.rglob("*.png")}
        assert names and all(n.startswith(("data/aura/", "data/stage01/")) for n in names), names
        assert not any(n[:-4].endswith(("_1", "_2")) and n[:-6] + ".png" in names for n in names)

        good = verify(pack)
        assert good.returncode == 0 and "0 error(s)" in good.stdout, good.stdout

        with_alpha = next(p for p in sorted(pack.rglob("*.png")) if Image.open(p).getchannel("A").getextrema()[0] < 255)
        original = Image.open(with_alpha).copy()
        original.resize((original.width * 3, original.height * 2)).save(with_alpha)
        assert "changes the shape" in verify(pack).stdout
        original.convert("RGB").save(with_alpha)
        expect_refused(pack, "lost alpha", "lost it")
        original.save(with_alpha)

        stray = pack / "data" / "aura" / "not-in-the-game.png"
        original.save(stray)
        expect_refused(pack, "unknown name", "no texture by this name")
        stray.unlink()

        sheet = pack / "data" / "title" / "title.png"
        sheet.parent.mkdir()
        Image.new("RGBA", (101, 100)).save(sheet)
        expect_refused(pack, "sheet size", "whole multiple")
        sheet.unlink()

        (pack / "data" / "aura" / "photo.jpg").write_bytes(b"x")
        assert "ignored" in verify(pack).stdout

        duplicates = pack / "duplicates.txt"
        duplicates.write_text("data/aura/none\tdata/aura/none\n", encoding="utf-8")
        expect_refused(pack, "bad duplicate", "does not exist")
    print("texture_pack_check: ok")
    return 0


if __name__ == "__main__":
    sys.exit(main())
