#!/usr/bin/env python3
"""Python and C++ must accept and refuse the same update inputs (issue #100).

The Python tools are the release side and the C++ parsers/readers are the game side, so a
disagreement means a release the tool published is one the game cannot read, or a file the
game accepts is one the tool refused. This test feeds both halves the same synthetic
manifests and archives and compares the verdicts, checks that the C++ parser accepts the
update manifest the Python tool writes, and parses the real package tarball when one has
been built (and says so when it has not).

    update_crosscheck_test.py <update_crosscheck binary> <repo root>
"""
import subprocess
import sys
import tarfile
import tempfile
from pathlib import Path

TESTS = Path(__file__).resolve().parent
sys.path.insert(0, str(TESTS))
sys.path.insert(0, str(TESTS.parent / "tools"))

import make_update_manifest as mum  # noqa: E402
import package_manifest as pm  # noqa: E402
import update_manifest_test as fixtures  # noqa: E402

HASH_A = "a" * 64
HASH_B = "b" * 64
TOP = fixtures.LINUX_TOP
VERSION = fixtures.VERSION


def python_manifest_ok(text):
    try:
        pm.parse_manifest(text)
        return True
    except pm.ManifestError:
        return False


def python_tar_ok(path):
    try:
        mum.read_linux_archive(path)
        return True
    except pm.ManifestError:
        return False


def python_zip_ok(path):
    try:
        mum.read_windows_archive(path)
        return True
    except pm.ManifestError:
        return False


def cpp(tool, *args):
    return subprocess.run([str(tool), *args], capture_output=True, text=True)


def package_manifest_text(version=VERSION, target="linux-x86_64", launch="run",
                          body=None):
    if body is None:
        body = HASH_A + "  5  x  run\n"
    return (
        "format = 1\nversion = %s\ntarget = %s\nlaunch = %s\n[files]\n%s"
        % (version, target, launch, body)
    )


def manifest_fixtures():
    valid = package_manifest_text()
    return {
        "valid": valid,
        "unknown-format": valid.replace("format = 1", "format = 2"),
        "crlf": valid.replace("\n", "\r\n"),
        "bad-hash": valid.replace(HASH_A, "g" * 64),
        "unsorted": package_manifest_text(
            body=HASH_A + "  5  -  b\n" + HASH_B + "  5  x  a\n"
        ),
        "duplicate": package_manifest_text(
            body=HASH_A + "  5  x  a\n" + HASH_A + "  5  -  a\n"
        ),
        "launch-missing": valid.replace("launch = run", "launch = nope"),
        "traversal": package_manifest_text(body=HASH_A + "  5  x  ../evil\n"),
        "case-collision": package_manifest_text(
            body=HASH_A + "  5  x  A.txt\n" + HASH_B + "  5  -  a.txt\n"
        ),
        "reserved": package_manifest_text(body=HASH_A + "  5  x  CON\n"),
        "trailing-dot": package_manifest_text(body=HASH_A + "  5  x  dir./x\n"),
        "self-entry": package_manifest_text(
            body=HASH_A + "  5  x  a\n" + HASH_B + "  5  -  package-manifest.txt\n"
        ),
        "blank-line": valid.replace("[files]\n", "[files]\n\n"),
        "windows-mode-x": package_manifest_text(
            target="windows-x86_64", launch="run", body=HASH_A + "  5  x  run\n"
        ),
        "no-final-newline": valid[:-1],
    }


def build_tar_fixtures(directory):
    """Every fixture carries a valid package-manifest.txt, so a refusal is structural."""
    _, manifest = fixtures.write_stage(
        directory, "cross-stage", fixtures.LINUX_FILES, "linux-x86_64", "run"
    )
    written = {}

    def write(name, extra_members=(), fmt=tarfile.USTAR_FORMAT, top=TOP):
        path = directory / (name + ".tar.gz")
        fixtures.write_tar(path, top, fixtures.LINUX_FILES, manifest,
                           extra_members=extra_members, fmt=fmt)
        written[name] = path

    write("valid")
    write("gnu-long-name",
          extra_members=[fixtures.tarfile_member(TOP + "/" + "x" * 150)],
          fmt=tarfile.GNU_FORMAT)
    write("pax",
          extra_members=[fixtures.tarfile_member(TOP + "/" + "y" * 150)],
          fmt=tarfile.PAX_FORMAT)
    write("symlink", extra_members=[fixtures.tarfile_member(
        TOP + "/link", type=tarfile.SYMTYPE, linkname="run")])
    write("hardlink", extra_members=[fixtures.tarfile_member(
        TOP + "/link", type=tarfile.LNKTYPE, linkname=TOP + "/run")])
    write("traversal", extra_members=[fixtures.tarfile_member("../evil")])
    write("two-tops", extra_members=[fixtures.tarfile_member("other/file")])
    write("root-file", extra_members=[fixtures.tarfile_member("rootfile")])
    write("case-collision", extra_members=[fixtures.tarfile_member(TOP + "/RUN")])
    write("reserved", extra_members=[fixtures.tarfile_member(TOP + "/CON")])

    valid = (directory / "valid.tar.gz").read_bytes()
    middle = len(valid) // 2
    (directory / "corrupted.tar.gz").write_bytes(
        valid[:middle] + bytes([valid[middle] ^ 0xFF]) + valid[middle + 1:]
    )
    written["corrupted"] = directory / "corrupted.tar.gz"
    (directory / "truncated.tar.gz").write_bytes(valid[:-8])
    written["truncated"] = directory / "truncated.tar.gz"
    (directory / "trailing.tar.gz").write_bytes(valid + b"junk")
    written["trailing"] = directory / "trailing.tar.gz"
    return written


def build_zip_fixtures(directory):
    _, manifest = fixtures.write_stage(
        directory, "cross-win-stage", fixtures.WINDOWS_FILES, "windows-x86_64",
        "DaybreakRemake.exe",
    )
    entries = [
        {"name": name, "data": data, "method": 8}
        for name, (data, _) in fixtures.WINDOWS_FILES.items()
    ]
    entries.append({"name": "package-manifest.txt", "data": manifest.encode(),
                    "method": 8})
    written = {}

    def write(name, mutate=None):
        copy = [dict(entry) for entry in entries]
        if mutate is not None:
            mutate(copy)
        path = directory / (name + ".zip")
        fixtures.raw_zip(path, copy)
        written[name] = path

    write("valid")
    write("stored", lambda items: [item.update(method=0) for item in items])
    write("encrypted", lambda items: items[0].update(flags=0x0001))
    write("bzip2", lambda items: items[0].update(method=12))
    write("zip64", lambda items: items[0].update(
        extra_central=b"\x01\x00\x10\x00" + b"\0" * 16))
    write("local-name", lambda items: items[0].update(local_name="Other.exe"))
    write("bad-crc", lambda items: items[0].update(crc=0xDEADBEEF))
    write("bomb", lambda items: items[0].update(uncomp_size=10 * 1024 * 1024))
    write("symlink", lambda items: items[0].update(external=0o120777 << 16))

    data = (directory / "valid.zip").read_bytes()
    eocd = data.rfind(b"PK\x05\x06")
    patched = bytearray(data)
    patched[eocd + 4:eocd + 6] = b"\x01\x00"  # disk number: multi-disk
    (directory / "multi-disk.zip").write_bytes(bytes(patched))
    written["multi-disk"] = directory / "multi-disk.zip"
    (directory / "truncated.zip").write_bytes(data[: len(data) // 2])
    written["truncated"] = directory / "truncated.zip"
    return written


def check(condition, what):
    if not condition:
        print("FAIL: %s" % what)
    return 0 if condition else 1


def main():
    if len(sys.argv) != 3:
        print("usage: update_crosscheck_test.py <update_crosscheck> <repo root>",
              file=sys.stderr)
        return 2
    tool = Path(sys.argv[1])
    repo = Path(sys.argv[2])
    failures = 0
    checks = 0

    def compare(name, python_ok, *args):
        nonlocal failures, checks
        result = cpp(tool, *args)
        cpp_ok = result.returncode == 0
        checks += 1
        if python_ok != cpp_ok:
            print("MISMATCH %s: python=%s cpp=%s (%s)"
                  % (name, python_ok, cpp_ok, result.stderr.strip()))
            failures += 1

    with tempfile.TemporaryDirectory(prefix="update-crosscheck-") as temporary:
        directory = Path(temporary)

        for name, text in manifest_fixtures().items():
            path = directory / ("manifest-" + name + ".txt")
            path.write_text(text)
            compare("manifest/" + name, python_manifest_ok(text), "manifest",
                    str(path))

        tars = build_tar_fixtures(directory)
        for name, path in tars.items():
            compare("tar/" + name, python_tar_ok(path), "archive", "tar", str(path))

        zips = build_zip_fixtures(directory)
        for name, path in zips.items():
            compare("zip/" + name, python_zip_ok(path), "archive", "zip", str(path))

        # The update manifest is written by Python and read by C++ only: check that the
        # generated file is accepted, and that a mutated one is refused. The archives need
        # the release's own names for build() to accept them.
        linux_release = directory / ("daybreak-%s-linux-x86_64.tar.gz" % VERSION)
        linux_release.write_bytes(tars["valid"].read_bytes())
        windows_release = directory / (
            "daybreak-%s-abc1234-windows-x86_64.zip" % VERSION)
        windows_release.write_bytes(zips["valid"].read_bytes())
        generated = mum.build(VERSION, str(linux_release), str(windows_release))
        generated_path = directory / "update-manifest.txt"
        generated_path.write_text(generated)
        result = cpp(tool, "update-manifest", str(generated_path))
        failures += check(result.returncode == 0,
                          "the generated update manifest must parse in C++ (%s)"
                          % result.stderr.strip())
        checks += 1
        mutated = directory / "update-manifest-mutated.txt"
        mutated.write_text(generated.replace("format = 1", "format = 2"))
        result = cpp(tool, "update-manifest", str(mutated))
        failures += check(result.returncode != 0,
                          "an unknown update-manifest format must be refused")
        checks += 1

    real_tarball = sorted(
        (repo / "build" / "package").glob("daybreak-*-linux-x86_64.tar.gz"))
    if real_tarball:
        for path in real_tarball:
            compare("real/" + path.name, python_tar_ok(path), "archive", "tar",
                    str(path))
            print("real tarball: %s" % path.name)
    else:
        print("real tarball: skipped (no build/package tarball)")

    real_zip = sorted(
        (repo / "build" / "package").glob("daybreak-*-windows-x86_64.zip"))
    if real_zip:
        for path in real_zip:
            compare("real/" + path.name, python_zip_ok(path), "archive", "zip",
                    str(path))
    else:
        print("real Windows zip: skipped (not built on this machine)")

    print("update_crosscheck_test: %d checks, %d failure(s)" % (checks, failures))
    return 0 if failures == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
