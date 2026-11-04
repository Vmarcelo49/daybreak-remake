#!/usr/bin/env python3
"""Build the fake install and served fixtures for tests/update_apply_test.cpp (issue #100).

The archives come from the real release tools (`package_manifest.py` writes the package
manifest, the tar is POSIX ustar) and the update manifests are signed with throwaway keys
by `release_sign`. The C++ test then drives check/apply against the loopback server, so the
step-1 + 2 + 3 chain is exercised with no game data and no internet.

    run_update_apply_test.py <update_apply_test> <update_stub> <release_sign>
"""
import hashlib
import shutil
import subprocess
import sys
import tarfile
import tempfile
from pathlib import Path

TESTS = Path(__file__).resolve().parent
TOOLS = TESTS.parent / "tools"
sys.path.insert(0, str(TESTS))

import http_fixture  # noqa: E402

OLD_VERSION = "1.0.0"
NEW_VERSION = "2.0.0"
LAYOUT_VERSION = "3.0.0"


def run(*args):
    subprocess.run([str(argument) for argument in args], check=True,
                   stdout=subprocess.DEVNULL)


def stage(directory, files):
    for relative, (data, mode) in files.items():
        target = directory / relative
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_bytes(data)
        target.chmod(mode)


def package_manifest(stage_dir, version, launch="daybreak"):
    run(sys.executable, "-I", TOOLS / "package_manifest.py", "write", stage_dir,
        "--version=" + version, "--target=linux-x86_64", "--launch=" + launch)


def make_archive(stage_dir, version, out):
    out.parent.mkdir(parents=True, exist_ok=True)
    top = "daybreak-%s-linux-x86_64" % version
    with tarfile.open(out, "w:gz", format=tarfile.USTAR_FORMAT) as archive:
        archive.add(stage_dir, arcname=top)
    return out


def sha256_file(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def update_manifest_text(version, archive):
    size = archive.stat().st_size
    sha = sha256_file(archive)
    dummy = "0" * 64
    return (
        "format = 1\n"
        "version = %s\n"
        "notes = https://github.com/Vmarcelo49/daybreak-remake/releases/tag/v%s\n"
        "[linux-x86_64]\n"
        "archive = %s\n"
        "size = %d\n"
        "sha256 = %s\n"
        "[windows-x86_64]\n"
        "archive = daybreak-%s-abc1234-windows-x86_64.zip\n"
        "size = 1\n"
        "sha256 = %s\n"
        % (version, version, archive.name, size, sha, version, dummy)
    )


def sign(release_sign, manifest, secret, public):
    run(release_sign, "sign", "--secret=" + str(secret),
        "--expect-public=" + str(public), manifest)


def build(fixtures, stub, release_sign):
    first_secret = fixtures / "release.release-secret"
    first_public = fixtures / "release.pub"
    second_secret = fixtures / "other.release-secret"
    second_public = fixtures / "other.pub"
    run(release_sign, "keygen", "--secret=" + str(first_secret),
        "--public=" + str(first_public))
    run(release_sign, "keygen", "--secret=" + str(second_secret),
        "--public=" + str(second_public))

    stub_bytes = stub.read_bytes()
    old = fixtures / "old"
    stage(old, {
        "daybreak": (stub_bytes, 0o755),
        "daybreak-bin": (stub_bytes, 0o755),
        "lib/libold.so": (b"old library", 0o644),
        "assets/font.otf": (b"old font", 0o644),
    })
    package_manifest(old, OLD_VERSION)
    # The player's own files and the game's data: never in a package manifest.
    stage(old, {
        "data/game.dat": (b"game data", 0o644),
        "data/x.cnv": (b"game texture", 0o644),
        "custom-textures/a.png": (b"player texture", 0o644),
        "daybreak00.dat": (b"game bundle", 0o644),
        "player-notes.txt": (b"player notes", 0o644),
        "settings.conf": (b"volume = 1\n", 0o644),
    })

    new_stage = fixtures / "new-stage"
    stage(new_stage, {
        "daybreak": (stub_bytes, 0o755),
        "daybreak-bin": (stub_bytes, 0o755),
        "lib/libnew.so": (b"new library", 0o644),
        "assets/font.otf": (b"new font", 0o644),
        "README.txt": (b"new readme", 0o644),
    })
    package_manifest(new_stage, NEW_VERSION)
    new_archive = make_archive(
        new_stage, NEW_VERSION,
        fixtures / "archives" / ("daybreak-%s-linux-x86_64.tar.gz" % NEW_VERSION))

    layout_stage = fixtures / "layout-stage"
    stage(layout_stage, {
        "bin/daybreak": (stub_bytes, 0o755),
        "bin/daybreak-bin": (stub_bytes, 0o755),
        "assets/font.otf": (b"layout font", 0o644),
    })
    package_manifest(layout_stage, LAYOUT_VERSION, launch="bin/daybreak")
    layout_archive = make_archive(
        layout_stage, LAYOUT_VERSION,
        fixtures / "archives" / ("daybreak-%s-linux-x86_64.tar.gz" % LAYOUT_VERSION))

    # A package that adds a file the player already owns, with different bytes.
    collision_stage = fixtures / "collision-stage"
    shutil.copytree(new_stage, collision_stage)
    (collision_stage / "player-notes.txt").write_bytes(b"package notes")
    (collision_stage / "package-manifest.txt").unlink()
    package_manifest(collision_stage, NEW_VERSION)
    collision_archive = make_archive(
        collision_stage, NEW_VERSION,
        fixtures / "archives" / ("collision-%s.tar.gz" % NEW_VERSION))

    # A package whose own manifest lies about one file's hash.
    mismatch_stage = fixtures / "mismatch-stage"
    shutil.copytree(new_stage, mismatch_stage)
    manifest_text = (mismatch_stage / "package-manifest.txt").read_text()
    (mismatch_stage / "package-manifest.txt").write_text(
        manifest_text.replace(sha256_file(new_stage / "assets/font.otf"),
                              "0" * 64))
    mismatch_archive = make_archive(
        mismatch_stage, NEW_VERSION,
        fixtures / "archives" / ("mismatch-%s.tar.gz" % NEW_VERSION))

    # A package that would write into the game's own data folder.
    game_stage = fixtures / "game-stage"
    shutil.copytree(new_stage, game_stage)
    (game_stage / "data").mkdir()
    (game_stage / "data/evil.cnv").write_bytes(b"evil")
    manifest_lines = (game_stage / "package-manifest.txt").read_text().splitlines()
    header = manifest_lines[:5]
    entries = manifest_lines[5:]
    entries.append("%s  4  -  data/evil.cnv" % hashlib.sha256(b"evil").hexdigest())
    entries.sort()
    (game_stage / "package-manifest.txt").write_text(
        "\n".join(header + entries) + "\n")
    game_archive = make_archive(
        game_stage, NEW_VERSION,
        fixtures / "archives" / ("gamearea-%s.tar.gz" % NEW_VERSION))

    scenarios = fixtures / "scenarios"

    def scenario(name, text, archive=None, secret=None, public=None, tamper=False):
        directory = scenarios / name
        directory.mkdir(parents=True)
        (directory / "update-manifest.txt").write_text(text)
        if archive is not None:
            shutil.copy2(archive, directory / archive.name)
        if secret is not None:
            sign(release_sign, directory / "update-manifest.txt", secret, public)
        if tamper:
            with open(directory / "update-manifest.txt", "a") as handle:
                handle.write("\n")

    good = update_manifest_text(NEW_VERSION, new_archive)
    scenario("good", good, new_archive, first_secret, first_public)
    scenario("uptodate", update_manifest_text(OLD_VERSION, new_archive), new_archive,
             first_secret, first_public)
    scenario("skip", good, new_archive, first_secret, first_public)
    scenario("manual", good.replace("format = 1", "format = 2"), new_archive,
             first_secret, first_public)
    scenario("badsig", good, new_archive, first_secret, first_public, tamper=True)
    scenario("unknownkey", good, new_archive, second_secret, second_public)
    scenario("wrongsize",
             good.replace("size = %d" % new_archive.stat().st_size,
                          "size = %d" % (new_archive.stat().st_size + 1)),
             new_archive, first_secret, first_public)
    scenario("wronghash", good.replace(sha256_file(new_archive), "f" * 64),
             new_archive, first_secret, first_public)
    scenario("layout", update_manifest_text(LAYOUT_VERSION, layout_archive),
             layout_archive, first_secret, first_public)
    scenario("collision", update_manifest_text(NEW_VERSION, collision_archive),
             collision_archive, first_secret, first_public)
    scenario("stagedmismatch", update_manifest_text(NEW_VERSION, mismatch_archive),
             mismatch_archive, first_secret, first_public)
    scenario("gamearea", update_manifest_text(NEW_VERSION, game_archive),
             game_archive, first_secret, first_public)
    return first_public.read_text().strip()


def main():
    if len(sys.argv) != 4:
        print("usage: run_update_apply_test.py <update_apply_test> <update_stub> "
              "<release_sign>", file=sys.stderr)
        return 2
    apply_test, stub, release_sign = (Path(argument) for argument in sys.argv[1:4])
    with tempfile.TemporaryDirectory(prefix="update-apply-fixtures-") as temporary:
        fixtures = Path(temporary) / "fixtures"
        fixtures.mkdir()
        key_hex = build(fixtures, stub, release_sign)
        server, _thread, base_url = http_fixture.start(root=fixtures)
        try:
            completed = subprocess.run([
                str(apply_test),
                "--fixtures=" + str(fixtures),
                "--base=" + base_url + "/",
                "--key=" + key_hex,
                "--stub=" + str(stub),
            ])
            return completed.returncode
        finally:
            server.shutdown()
            server.server_close()


if __name__ == "__main__":
    sys.exit(main())
