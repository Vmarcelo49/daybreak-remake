"""Shared setup for the update tests (issue #100): a synthetic packaged install and an
N+1 release built with the real tools. No game data is committed; the title art comes
from the local install and the tests skip when it is absent."""
import hashlib
import shutil
import subprocess
import sys
import tarfile
import zipfile
from pathlib import Path

TOOLS = Path(__file__).resolve().parent.parent / "tools"
TITLE_FILES = ("back00.cnv", "logo.cnv", "title.cnv")


def sha256_file(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def title_available(game_dir):
    return all((Path(game_dir) / "data" / "title" / name).is_file() for name in TITLE_FILES)


def make_install(package_dir, install_dir, game_dir):
    """The packaged build plus the title art and fake game/player files."""
    shutil.copytree(package_dir, install_dir)
    (install_dir / "data" / "title").mkdir(parents=True, exist_ok=True)
    for name in TITLE_FILES:
        shutil.copy2(Path(game_dir) / "data" / "title" / name,
                     install_dir / "data" / "title" / name)
    # No fake daybreak00.dat: the bundle reader would try to open it and the launch would
    # fail. The install runs as an extracted tree (data/ from the working directory).
    for relative, data in {
        "data/x.cnv": b"fake game texture",
        "custom-textures/a.png": b"player texture",
        "player-notes.txt": b"player notes",
    }.items():
        target = install_dir / relative
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_bytes(data)
    return install_dir


def make_release(package_dir, out_dir, version):
    """The same build stamped with a new VERSION and one changed package file, as the
    Linux tarball and the Windows zip make_update_manifest.py wants."""
    out_dir.mkdir(parents=True, exist_ok=True)
    linux_stage = out_dir / "linux-stage"
    shutil.copytree(package_dir, linux_stage)
    readme = linux_stage / "README-LINUX.md"
    readme.write_text(readme.read_text() + "\nUpdated by the loopback test.\n")
    subprocess.run([sys.executable, "-I", str(TOOLS / "package_manifest.py"), "write",
                    str(linux_stage), "--version=" + version, "--target=linux-x86_64",
                    "--launch=daybreak"], check=True, stdout=subprocess.DEVNULL)
    linux = out_dir / ("daybreak-%s-linux-x86_64.tar.gz" % version)
    with tarfile.open(linux, "w:gz", format=tarfile.USTAR_FORMAT) as archive:
        archive.add(linux_stage, arcname="daybreak-%s-linux-x86_64" % version)

    windows_stage = out_dir / "windows-stage"
    shutil.copytree(package_dir, windows_stage)
    # The Windows package's entry point: the manifest names it, the reader only checks
    # that the archive and the manifest agree.
    (windows_stage / "DaybreakRemake.exe").write_bytes(b"MZ fake windows build")
    subprocess.run([sys.executable, "-I", str(TOOLS / "package_manifest.py"), "write",
                    str(windows_stage), "--version=" + version,
                    "--target=windows-x86_64", "--launch=DaybreakRemake.exe"],
                   check=True, stdout=subprocess.DEVNULL)
    windows = out_dir / ("daybreak-%s-abc1234-windows-x86_64.zip" % version)
    with zipfile.ZipFile(windows, "w") as archive:
        for path in sorted(windows_stage.rglob("*")):
            if path.is_file():
                archive.write(path, path.relative_to(windows_stage))
    return linux, windows


def build_update_manifest(release_dir, version, linux, windows, out):
    subprocess.run([sys.executable, "-I", str(TOOLS / "make_update_manifest.py"),
                    "--version=" + version, "--linux=" + str(linux),
                    "--windows=" + str(windows), "--out=" + str(out)],
                   check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    return out


def keypair(release_sign, directory):
    directory.mkdir(parents=True, exist_ok=True)
    secret = directory / "release.release-secret"
    public = directory / "release.pub"
    subprocess.run([str(release_sign), "keygen", "--secret=" + str(secret),
                    "--public=" + str(public)], check=True, stdout=subprocess.DEVNULL)
    return secret, public.read_text().strip()


def sign(release_sign, manifest, secret, public_hex):
    subprocess.run([str(release_sign), "sign", "--secret=" + str(secret),
                    "--expect-public=" + public_hex, str(manifest)],
                   check=True, stdout=subprocess.DEVNULL)
