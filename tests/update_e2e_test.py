#!/usr/bin/env python3
"""The whole update through the real binary (issue #100, step 4).

A synthetic install of the packaged build (version 0.2.1), a 0.2.2 release built with the
real tools and signed with a throwaway key, served over the step-2 loopback server. A menu
script drives title -> notice -> Update -> progress -> relaunch; the test then checks the
new manifest, the untouched game files and the cleaned workspace. A second run with a
corrupted archive must fail as "damaged" and leave 0.2.1 intact.

The binary under test is daybreak_e2e: the same game built with DAYBREAK_UPDATE_TEST_BUILD,
which is the only build that accepts --test-update-key. A release build refuses to compile
that path (update_release_guard_test).

    update_e2e_test.py <daybreak_e2e> <source dir> <release_sign>
"""
import hashlib
import os
import shutil
import subprocess
import sys
import tempfile
import time
from pathlib import Path

TESTS = Path(__file__).resolve().parent
sys.path.insert(0, str(TESTS))
import http_fixture  # noqa: E402
import update_e2e_fixtures as fixtures  # noqa: E402

SKIP = 77
N = "0.2.1"
NEXT = "0.2.2"
MENU_SCRIPT = """# Title menu -> notice -> Update.
WAIT 90
UP
WAIT 3
DOWN
WAIT 3
CONFIRM
WAIT 5
"""


def sha256(path):
    return fixtures.sha256_file(path)


def make_stage(source, binary, stage):
    """A package-shaped build tree: the binary, its fonts, the locale, a manifest."""
    stage.mkdir(parents=True)
    shutil.copy2(binary, stage / "daybreak-bin")
    shutil.copytree(Path(binary).parent / "assets" / "fonts", stage / "assets" / "fonts")
    shutil.copytree(source / "assets" / "locale", stage / "assets" / "locale")
    (stage / "README-LINUX.md").write_text("daybreak test package\n")
    # The package's launcher, which is what the update relaunches into.
    launcher = stage / "daybreak"
    launcher.write_text('#!/bin/sh\nexec "$(dirname "$0")/daybreak-bin" "$@"\n')
    launcher.chmod(0o755)
    subprocess.run([sys.executable, "-I", str(fixtures.TOOLS / "package_manifest.py"),
                    "write", str(stage), "--version=" + N, "--target=linux-x86_64",
                    "--launch=daybreak-bin"], check=True, stdout=subprocess.DEVNULL)
    return stage


def game_files(install):
    return {name: sha256(install / name) for name in
            ("data/x.cnv", "custom-textures/a.png", "player-notes.txt")}


def start(binary, install, env, script, language="en"):
    return subprocess.Popen(
        [str(install / "daybreak-bin"), "--screen=title", "--title-backdrop=off",
         "--no-audio", "--language=" + language, "--menu-script=" + str(script),
         "--test-update-key=" + env["TEST_KEY"]],
        cwd=install, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, env=env["env"])


def log_text(config):
    text = ""
    for name in ("daybreak.log", "daybreak-previous.log"):
        path = config / "daybreak-decomp" / name
        if path.is_file():
            text += path.read_text(errors="replace")
    return text


def wait_for(process, config, needle, timeout=90):
    deadline = time.time() + timeout
    while time.time() < deadline:
        text = log_text(config)
        if needle in text:
            return text
        if process.poll() is not None and needle in log_text(config):
            return log_text(config)
        time.sleep(0.2)
    return log_text(config)


def main():
    if len(sys.argv) != 4:
        print("usage: update_e2e_test.py <daybreak_e2e> <source dir> <release_sign>",
              file=sys.stderr)
        return 2
    binary = Path(sys.argv[1]).resolve()
    source = Path(sys.argv[2]).resolve()
    release_sign = Path(sys.argv[3]).resolve()
    game_dir = source / "Higurashi-Daybreak"
    if not fixtures.title_available(game_dir):
        print("update_e2e_test: SKIP: no title art in Higurashi-Daybreak", file=sys.stderr)
        return SKIP
    if not (os.environ.get("DISPLAY") or os.environ.get("WAYLAND_DISPLAY")):
        print("update_e2e_test: SKIP: the run needs a display", file=sys.stderr)
        return SKIP

    with tempfile.TemporaryDirectory(prefix="update-e2e-") as temporary:
        root = Path(temporary)
        stage = make_stage(source, binary, root / "stage")
        install = fixtures.make_install(stage, root / "install", game_dir)
        before = game_files(install)

        linux, windows = fixtures.make_release(stage, root / "release", NEXT)
        manifest = fixtures.build_update_manifest(root / "release", NEXT, linux, windows,
                                                  root / "release" / "update-manifest.txt")
        secret, public = fixtures.keypair(release_sign, root / "keys")
        fixtures.sign(release_sign, manifest, secret, public)

        served = root / "served"
        served.mkdir()
        shutil.copy2(manifest, served / "update-manifest.txt")
        shutil.copy2(Path(str(manifest) + ".sig"), served / "update-manifest.txt.sig")
        shutil.copy2(linux, served / linux.name)
        server, _thread, base = http_fixture.start(root=served)
        config = root / "config"
        script = root / "menu.txt"
        script.write_text(MENU_SCRIPT)
        child = dict(os.environ, DAYBREAK_UPDATE_URL=base + "/",
                     DAYBREAK_UPDATE_TEST_HTTP="1", XDG_CONFIG_HOME=str(config),
                     SDL_AUDIODRIVER="dummy")
        # CTest exports DAYBREAK_NO_UPDATE_CHECK=1 for every test; this one exists to run
        # the real check.
        child.pop("DAYBREAK_NO_UPDATE_CHECK", None)
        env = {"env": child, "TEST_KEY": public}
        try:
            process = start(binary, install, env, script)
            text = wait_for(process, config, "relaunched after updating from " + N)
            if "relaunched after updating from " + N not in text:
                print("update_e2e_test: no relaunch; log:\n" + text[-3000:], file=sys.stderr)
                process.terminate()
                return 1
            process.terminate()
            try:
                process.wait(timeout=10)
            except subprocess.TimeoutExpired:
                process.kill()
            if (install / "package-manifest.txt").read_text().find("version = " + NEXT) < 0:
                print("update_e2e_test: the installed manifest is not " + NEXT, file=sys.stderr)
                return 1
            if "Updated by the loopback test" not in (install / "README-LINUX.md").read_text():
                print("update_e2e_test: the package file was not replaced", file=sys.stderr)
                return 1
            after = game_files(install)
            if before != after:
                print("update_e2e_test: a non-package file changed: %s -> %s"
                      % (before, after), file=sys.stderr)
                return 1
            leftovers = [str(p) for p in install.rglob("*.old")] + \
                        [str(p) for p in install.glob(".daybreak-update")]
            if leftovers:
                print("update_e2e_test: leftovers after the update: %s" % leftovers,
                      file=sys.stderr)
                return 1
            print("update_e2e_test: 0.2.1 -> 0.2.2 relaunched, game files unchanged, "
                  "workspace clean")

            # Second run: a corrupted archive must fail as a damaged download and leave N.
            corrupt = root / "corrupt"
            corrupt.mkdir()
            shutil.copy2(manifest, corrupt / "update-manifest.txt")
            shutil.copy2(Path(str(manifest) + ".sig"), corrupt / "update-manifest.txt.sig")
            data = bytearray(linux.read_bytes())
            data[len(data) // 2] ^= 0xFF
            (corrupt / linux.name).write_bytes(bytes(data))
            server.shutdown()
            server.server_close()
            server, _thread, base = http_fixture.start(root=corrupt)
            env["env"]["DAYBREAK_UPDATE_URL"] = base + "/"
            config2 = root / "config2"
            env["env"]["XDG_CONFIG_HOME"] = str(config2)
            install2 = fixtures.make_install(stage, root / "install2", game_dir)
            before2 = game_files(install2)
            process = start(binary, install2, env, script)
            text = wait_for(process, config2, "[update] failed:", timeout=90)
            process.terminate()
            try:
                process.wait(timeout=10)
            except subprocess.TimeoutExpired:
                process.kill()
            if "damaged" not in text:
                print("update_e2e_test: the corrupted run did not say damaged; log:\n"
                      + text[-3000:], file=sys.stderr)
                return 1
            if (install2 / "package-manifest.txt").read_text().find("version = " + N) < 0:
                print("update_e2e_test: the corrupted run changed the manifest",
                      file=sys.stderr)
                return 1
            if before2 != game_files(install2):
                print("update_e2e_test: the corrupted run changed a game file",
                      file=sys.stderr)
                return 1
            if (install2 / ".daybreak-update").exists():
                print("update_e2e_test: the corrupted run left a workspace", file=sys.stderr)
                return 1
            print("update_e2e_test: a corrupted archive fails as damaged and leaves 0.2.1")
        finally:
            server.shutdown()
            server.server_close()
    return 0


if __name__ == "__main__":
    sys.exit(main())
