#!/usr/bin/env python3
"""No gated launch may touch the network (issue #100, step 4).

Builds a synthetic *packaged* install (the real binary plus a package-manifest.txt, so the
development-tree rule is not what suppresses the check), points DAYBREAK_UPDATE_URL at the
loopback fixture server and runs the binary in every mode the gate covers. The server
counts requests: every gated mode must leave it empty. The positive control — a normal
title launch with none of the gating flags — must make exactly one manifest and one .sig
request; without it, a zero would prove nothing.

    update_no_network_test.py <daybreak> <source dir>
"""
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
# A throwaway key, so the check gets past "no trusted key" and actually asks the server;
# the manifest is garbage and the signature check fails after the two fetches.
TEST_KEY = "11" * 32


def make_packaged_install(source, binary, install, game_dir):
    """The build's binary and fonts, a real package-manifest.txt, and the title art."""
    install.mkdir(parents=True)
    shutil.copy2(binary, install / "daybreak-bin")
    shutil.copytree(Path(binary).parent / "assets" / "fonts", install / "assets" / "fonts")
    shutil.copytree(source / "assets" / "locale", install / "assets" / "locale")
    subprocess.run([sys.executable, "-I", str(fixtures.TOOLS / "package_manifest.py"),
                    "write", str(install), "--version=0.2.1", "--target=linux-x86_64",
                    "--launch=daybreak-bin"], check=True, stdout=subprocess.DEVNULL)
    # A fake daybreak00.dat cannot be opened by the bundle reader (the real one is 1.5 GB),
    # so the install runs as an extracted tree: the working directory is the game folder
    # and the title art is read from data/. The package manifest still makes the binary's
    # folder an installed package, which is the rule this test is about.
    (install / "data" / "title").mkdir(parents=True, exist_ok=True)
    for name in fixtures.TITLE_FILES:
        shutil.copy2(Path(game_dir) / "data" / "title" / name,
                     install / "data" / "title" / name)
    return install


def environment(install, config, base):
    env = dict(os.environ)
    env.update({
        "DAYBREAK_UPDATE_URL": base + "/",
        "DAYBREAK_UPDATE_TEST_HTTP": "1",
        "XDG_CONFIG_HOME": str(config),
        "SDL_AUDIODRIVER": "dummy",
    })
    # CTest exports DAYBREAK_NO_UPDATE_CHECK=1 for every test; the positive control must
    # not inherit it, and the one mode that tests it sets it explicitly below.
    env.pop("DAYBREAK_NO_UPDATE_CHECK", None)
    return env


def run_gated(install, config, base, args, env_extra=None, seconds=2.5):
    """A launch that must not check: start it, give it time to reach the title, stop it."""
    env = environment(install, config, base)
    if env_extra:
        env.update(env_extra)
    process = subprocess.Popen(
        [str(install / "daybreak-bin"), "--screen=title", "--title-backdrop=off",
         "--no-audio", "--test-update-key=" + TEST_KEY] + args, cwd=install,
        stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, env=env)
    try:
        process.wait(timeout=seconds)
    except subprocess.TimeoutExpired:
        process.terminate()
        try:
            process.wait(timeout=10)
        except subprocess.TimeoutExpired:
            process.kill()


def main():
    if len(sys.argv) != 3:
        print("usage: update_no_network_test.py <daybreak> <source dir>", file=sys.stderr)
        return 2
    binary = Path(sys.argv[1]).resolve()
    source = Path(sys.argv[2]).resolve()
    game_dir = source / "Higurashi-Daybreak"
    if not fixtures.title_available(game_dir):
        print("update_no_network_test: SKIP: no title art in Higurashi-Daybreak", file=sys.stderr)
        return SKIP
    if not (os.environ.get("DISPLAY") or os.environ.get("WAYLAND_DISPLAY")):
        print("update_no_network_test: SKIP: the positive control needs a display",
              file=sys.stderr)
        return SKIP

    with tempfile.TemporaryDirectory(prefix="update-no-network-") as temporary:
        root = Path(temporary)
        install = make_packaged_install(source, binary, root / "install", game_dir)
        config = root / "config"
        config.mkdir()
        served = root / "served"
        served.mkdir()
        (served / "update-manifest.txt").write_bytes(b"not a real manifest\n")
        (served / "update-manifest.txt.sig").write_bytes(b"not a real signature\n")
        server, _thread, base = http_fixture.start(root=served)
        try:
            def requests():
                return list(server.requests)

            # The positive control: a normal launch, no gating flag at all.
            env = environment(install, config, base)
            process = subprocess.Popen(
                [str(install / "daybreak-bin"), "--screen=title", "--title-backdrop=off",
                 "--no-audio", "--test-update-key=" + TEST_KEY], cwd=install,
                stdout=subprocess.DEVNULL,
                stderr=subprocess.DEVNULL, env=env)
            deadline = time.time() + 20
            while time.time() < deadline and len(server.requests) < 2:
                time.sleep(0.1)
            process.terminate()
            try:
                process.wait(timeout=10)
            except subprocess.TimeoutExpired:
                process.kill()
            control = requests()
            if len(control) != 2:
                print("update_no_network_test: the positive control made %d request(s), "
                      "expected 2: %s" % (len(control), control), file=sys.stderr)
                return 1
            if not control[0].endswith("update-manifest.txt") or \
                    not control[1].endswith("update-manifest.txt.sig"):
                print("update_no_network_test: the control fetched the wrong files: %s"
                      % control, file=sys.stderr)
                return 1
            print("positive control: 2 requests (%s)" % ", ".join(control))

            # check = off, in a temp config.
            settings = config / "daybreak-decomp" / "settings.conf"
            settings.parent.mkdir(parents=True, exist_ok=True)
            settings.write_text("version = 9\n[game]\ninstall_dir =\n[update]\ncheck = off\n")
            server.requests.clear()
            run_gated(install, config, base, [])
            if requests():
                print("check=off made %s" % requests(), file=sys.stderr)
                return 1
            print("check = off: 0 requests")
            # Back to on, so every mode below is proved by its own flag, not by this file.
            settings.write_text("version = 9\n[game]\ninstall_dir =\n[update]\ncheck = on\n")

            # Each mode carries only its own flag (plus what that flag itself needs), so a
            # gated run cannot be passing because some other flag gated it.
            modes = [
                ("--no-update-check", ["--no-update-check"], None),
                ("--frames", ["--frames=2"], None),
                ("--out", ["--out=" + str(root / "d.ppm")], None),
                ("--script", ["--script=" + str(source / "tests" / "scripts" / "air-attack.txt")], None),
                ("DAYBREAK_NO_UPDATE_CHECK", [], {"DAYBREAK_NO_UPDATE_CHECK": "1"}),
                ("--headless", ["--headless", "--out=" + str(root / "g.ppm")], None),
                ("--hud-test", ["--hud-test"], None),
                ("--bench", ["--bench=1"], None),
                ("--list", ["--list"], None),
                ("--audio-test", ["--audio-test"], None),
                ("--input-test", ["--input-test"], None),
                ("--pause-overlay", ["--pause-overlay=1", "--out=" + str(root / "j.ppm")], None),
                ("--net-stress", ["--net-stress=1", "--out=" + str(root / "k.ppm")], None),
                ("--rollback-stress", ["--rollback-stress=1", "--out=" + str(root / "l.ppm")], None),
                ("--hud-probe", ["--hud-probe"], None),
                ("--debug-keys", ["--debug-keys=f2@0"], None),
                ("--text-keys", ["--text-keys=10:AB"], None),
                ("--update-result", ["--update-result=available"], None),
            ]
            for name, args, extra in modes:
                server.requests.clear()
                run_gated(install, config, base, args, extra)
                if requests():
                    print("%s made %s" % (name, requests()), file=sys.stderr)
                    return 1
                print("%s: 0 requests" % name)
        finally:
            server.shutdown()
            server.server_close()
    print("update_no_network_test: every gated mode made 0 requests, the control made 2")
    return 0


if __name__ == "__main__":
    sys.exit(main())
