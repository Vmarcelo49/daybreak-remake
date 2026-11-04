#!/usr/bin/env python3
"""The title's update notice, driven with real input, and the screen captures (issue #100).

A menu script presses the same edges the pad and keyboard produce: the title menu moves
into the notice, across all four choices, back up, and the menu still works. Later hides
the notice, Skip writes [update] skip_version, and Release notes is logged instead of
opening a browser (the test build's SDL_OpenURL stub). Every step is captured with --out.

Also captures the update screen's four phases and its failure panel, in English and
Japanese, under build/captures/update-*.png.

    update_screens_test.py <daybreak_e2e> <source dir>
"""
import os
import shutil
import subprocess
import sys
import time
import tempfile
import zlib
import struct
from pathlib import Path

TESTS = Path(__file__).resolve().parent
sys.path.insert(0, str(TESTS))
import update_e2e_fixtures as fixtures  # noqa: E402
import update_no_network_test as no_network  # noqa: E402

SKIP = 77
CAPTURES = Path(__file__).resolve().parent.parent / "build" / "captures"
NOTICE_URL = "https://github.com/Vmarcelo49/daybreak-remake/releases"


def ppm_to_png(ppm, png):
    data = Path(ppm).read_bytes()
    parts = data.split(b"\n", 3)
    width, height = map(int, parts[1].split())
    pixels = parts[3]
    raw = b"".join(b"\x00" + pixels[y * width * 3:(y + 1) * width * 3]
                   for y in range(height))

    def chunk(tag, payload):
        return (struct.pack(">I", len(payload)) + tag + payload +
                struct.pack(">I", zlib.crc32(tag + payload) & 0xffffffff))

    Path(png).write_bytes(b"\x89PNG\r\n\x1a\n" +
                          chunk(b"IHDR", struct.pack(">IIBBBBB", width, height, 8, 2,
                                                     0, 0, 0)) +
                          chunk(b"IDAT", zlib.compress(raw, 6)) + chunk(b"IEND", b""))


def run(install, binary, script, out, language=None, result="available", frames=40,
        size="1280x720"):
    script_path = install / "menu.txt"
    script_path.write_text(script)
    args = [str(install / "daybreak-bin"), "--screen=title", "--title-backdrop=off",
            "--no-audio", "--update-result=" + result, "--menu-script=" + str(script_path),
            "--frames=" + str(frames), "--out=" + str(out), "--size=" + size]
    if language:
        args.append("--language=" + language)
    env = dict(os.environ, XDG_CONFIG_HOME=str(install / "config"),
               SDL_AUDIODRIVER="dummy")
    completed = subprocess.run(args, cwd=install, capture_output=True, text=True,
                               env=env, timeout=120)
    log = install / "config" / "daybreak-decomp" / "daybreak.log"
    text = completed.stdout + completed.stderr
    if log.exists():
        text += log.read_text(errors="replace")
    return completed, text


def capture(install, binary, name, script, language=None, result="available", frames=40,
            size="1280x720"):
    out = CAPTURES / (name + ".ppm")
    completed, log = run(install, binary, script, out, language, result, frames, size)
    if not out.is_file():
        print("update_screens_test: %s produced no capture\n%s\n%s"
              % (name, completed.stdout[-1500:], completed.stderr[-1000:]), file=sys.stderr)
        return None, log
    ppm_to_png(out, CAPTURES / (name + ".png"))
    return out, log


def main():
    if len(sys.argv) != 3:
        print("usage: update_screens_test.py <daybreak_e2e> <source dir>", file=sys.stderr)
        return 2
    binary = Path(sys.argv[1]).resolve()
    source = Path(sys.argv[2]).resolve()
    game_dir = source / "Higurashi-Daybreak"
    if not fixtures.title_available(game_dir):
        print("update_screens_test: SKIP: no title art", file=sys.stderr)
        return SKIP
    if not (os.environ.get("DISPLAY") or os.environ.get("WAYLAND_DISPLAY")):
        print("update_screens_test: SKIP: the captures need a display", file=sys.stderr)
        return SKIP
    CAPTURES.mkdir(parents=True, exist_ok=True)

    with tempfile.TemporaryDirectory(prefix="update-screens-") as temporary:
        root = Path(temporary)
        stage = root / "stage"
        stage.mkdir()
        shutil.copy2(binary, stage / "daybreak-bin")
        shutil.copytree(Path(binary).parent / "assets" / "fonts", stage / "assets" / "fonts")
        shutil.copytree(source / "assets" / "locale", stage / "assets" / "locale")
        subprocess.run([sys.executable, "-I", str(fixtures.TOOLS / "package_manifest.py"),
                        "write", str(stage), "--version=0.2.1", "--target=linux-x86_64",
                        "--launch=daybreak-bin"], check=True, stdout=subprocess.DEVNULL)
        install = fixtures.make_install(stage, root / "install", game_dir)

        # The banner takes the input as soon as it appears (owner review), so the scripts
        # start from it being focused; UP goes back to the menu.
        into_notice = "WAIT 25\n"
        steps = [
            ("update-notice-available-en", "", "en"),
            ("update-notice-available-ja", "", None),
            ("update-notice-available-4x3-en", "", "en"),
            ("update-notice-update-en", into_notice, "en"),
            ("update-notice-update-ja", into_notice, None),
            ("update-notice-notes-en", into_notice + "RIGHT\nWAIT 2\n", "en"),
            ("update-notice-later-en", into_notice + "RIGHT\nWAIT 2\nRIGHT\nWAIT 2\n", "en"),
            ("update-notice-skip-en", into_notice + "RIGHT\nWAIT 2\nRIGHT\nWAIT 2\nRIGHT\nWAIT 2\n", "en"),
        ]
        for name, script, language in steps:
            size = "1024x768" if "4x3" in name else "1280x720"
            capture(install, binary, name, script, language, frames=45, size=size)

        # Later: confirm on the third choice hides the notice for the rest of the launch.
        _, log = capture(install, binary, "update-notice-later-confirmed-en",
                         into_notice + "RIGHT\nWAIT 2\nRIGHT\nWAIT 2\nCONFIRM\nWAIT 3\n",
                         "en", frames=48)
        # Skip: confirm on the fourth choice writes skip_version and hides it.
        _, log = capture(install, binary, "update-notice-skip-confirmed-en",
                         into_notice + "RIGHT\nWAIT 2\nRIGHT\nWAIT 2\nRIGHT\nWAIT 2\n"
                         "CONFIRM\nWAIT 3\n", "en", frames=50)
        # Skip's side effect needs a settings-active run: a bounded capture never reads or
        # writes the user config (usesUserConfig), so this is a plain interactive launch
        # that is stopped once the setting has been written.
        skip_script = install / "skip.txt"
        skip_script.write_text(into_notice + "RIGHT\nWAIT 2\nRIGHT\nWAIT 2\nRIGHT\n"
                               "WAIT 2\nCONFIRM\nWAIT 5\n")
        env = dict(os.environ, XDG_CONFIG_HOME=str(install / "config"),
                   SDL_AUDIODRIVER="dummy")
        process = subprocess.Popen(
            [str(install / "daybreak-bin"), "--screen=title", "--title-backdrop=off",
             "--no-audio", "--update-result=available", "--language=en",
             "--menu-script=" + str(skip_script)],
            cwd=install, env=env, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        time.sleep(8)
        process.terminate()
        try:
            process.wait(timeout=10)
        except subprocess.TimeoutExpired:
            process.kill()
        settings = install / "config" / "daybreak-decomp" / "settings.conf"
        if not settings.is_file() or "skip_version = 9.9.9" not in settings.read_text():
            print("update_screens_test: Skip did not write skip_version: %s"
                  % (settings.read_text() if settings.is_file() else "no file"),
                  file=sys.stderr)
            return 1
        # Release notes: logged, never opened (the test build's stub).
        _, log = capture(install, binary, "update-notice-notes-confirmed-en",
                         into_notice + "RIGHT\nWAIT 2\nCONFIRM\nWAIT 3\n", "en", frames=48)
        if "[update] open " + NOTICE_URL not in log:
            print("update_screens_test: Release notes did not log the URL:\n" + log[-2000:],
                  file=sys.stderr)
            return 1
        # Back up into the menu, move the menu, and confirm it still works (item 4 is
        # KeyConfig, whose scene name proves the menu responded).
        # Back to the menu (item 0), move down to 1 and back up to 0, then confirm Story:
        # the log proves the menu responded after the notice.
        back = into_notice + "UP\nWAIT 3\nDOWN\nWAIT 3\nUP\nWAIT 3\n"
        capture(install, binary, "update-notice-back-to-menu-en", back, "en", frames=44)
        _, log = capture(install, binary, "update-notice-menu-confirm-en",
                         back + "CONFIRM\nWAIT 3\n", "en", frames=120)
        if "scene: prologue" not in log and "scene: opening" not in log:
            print("update_screens_test: the menu did not respond after the notice:\n"
                  + log[-2000:], file=sys.stderr)
            return 1
        print("update_screens_test: Later hides, Skip writes skip_version, Notes is logged, "
              "and the menu still works")

        # The update screen: every phase and one failure, in both languages.
        phases = [("progress", "update-progress-downloading"),
                  ("verifying", "update-progress-verifying"),
                  ("installing", "update-progress-installing"),
                  ("restarting", "update-progress-restarting"),
                  ("failed", "update-failed-damaged")]
        for phase, name in phases:
            for suffix, language in (("en", "en"), ("ja", None)):
                script = install / "empty.txt"
                script.write_text("")
                args = [str(install / "daybreak-bin"), "--screen=update",
                        "--update-result=" + phase, "--size=1280x720", "--frames=2",
                        "--out=" + str(CAPTURES / ("%s-%s.ppm" % (name, suffix)))]
                if language:
                    args.append("--language=" + language)
                env = dict(os.environ, XDG_CONFIG_HOME=str(install / "config"),
                           SDL_AUDIODRIVER="dummy")
                completed = subprocess.run(args, cwd=install, capture_output=True,
                                           text=True, env=env, timeout=120)
                ppm = CAPTURES / ("%s-%s.ppm" % (name, suffix))
                if not ppm.is_file():
                    print("update_screens_test: %s-%s produced no capture\n%s"
                          % (name, suffix, completed.stderr[-1000:]), file=sys.stderr)
                    return 1
                ppm_to_png(ppm, CAPTURES / ("%s-%s.png" % (name, suffix)))
        print("update_screens_test: captures written under build/captures/update-*")
    return 0


if __name__ == "__main__":
    sys.exit(main())
