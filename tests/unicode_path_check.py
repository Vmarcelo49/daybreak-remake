#!/usr/bin/env python3
"""A battle has to load from a game folder with a non-English name, on the Windows build.

Windows reads a narrow path in its own code page and the game's paths are UTF-8, so this can only fail
there. Runs under Wine, headless. A tester's report: `battle: Cannot open archive`.
"""
import os
import pathlib
import shutil
import subprocess
import sys
import tempfile


def main():
    exe, install = pathlib.Path(sys.argv[1]).resolve(), pathlib.Path(sys.argv[2]).resolve()
    if not (install / "daybreak00.dat").exists():
        print("SKIP: no install")
        return 77
    if not exe.exists() or not shutil.which("wine"):
        print("SKIP: needs Wine and the Windows build")
        return 77
    failed = False
    with tempfile.TemporaryDirectory() as root:
        for name in ("ひぐらし デイブレイク", "João Ação"):
            folder = pathlib.Path(root) / name
            folder.mkdir()
            for item in install.iterdir():
                (folder / item.name).symlink_to(item)
            env = dict(os.environ, WINEDEBUG="-all", XDG_CONFIG_HOME=root)
            result = subprocess.run([ "wine", str(exe), "--headless", "--no-audio", "--screen=battle", "--frames=30", "--size=320x180",
                                     f"--install={folder}", "--out=out.ppm"], cwd=root, env=env, capture_output=True, timeout=120)
            out = (result.stdout + result.stderr).decode("utf-8", "replace")
            loaded = result.returncode == 0 and "RESULT: ok" in out and "4 fighters" in out
            print(f"{name}: {'loaded' if loaded else 'FAILED'}")
            if not loaded:
                print(out[-400:])
                failed = True
    print("unicode_path_check: failed" if failed else "unicode_path_check: ok")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
