#!/usr/bin/env python3
"""Tests for `tools/make_update_manifest.py` (issue #100).

The update manifest is what the updater downloads, verifies and acts on, so the tool
that writes it must (a) prove each archive really matches the package manifest inside
it and (b) produce the same bytes for the same inputs, because the file is signed.
These tests build small synthetic tar.gz and zip archives — no game data, no network,
no build output — and expect both the success shape and every refusal.
"""

import hashlib
import io
import os
import struct
import subprocess
import sys
import tarfile
import tempfile
import unittest
import zipfile
import zlib
from pathlib import Path

TESTS = Path(__file__).resolve().parent
TOOLS = TESTS.parent / "tools"

PACKAGE_TOOL = str(TOOLS / "package_manifest.py")
UPDATE_TOOL = str(TOOLS / "make_update_manifest.py")

VERSION = "1.2.3"
LINUX_TOP = "daybreak-1.2.3-linux-x86_64"
LINUX_ARCHIVE = LINUX_TOP + ".tar.gz"
WINDOWS_ARCHIVE = "daybreak-1.2.3-abc1234-windows-x86_64.zip"

LINUX_FILES = {
    "run": (b"#!/bin/sh\nexit 0\n", 0o755),
    "lib/libfoo.so": (b"libbytes", 0o644),
    "assets/font.otf": (b"font", 0o644),
}
WINDOWS_FILES = {
    "DaybreakRemake.exe": (b"MZ fake", 0o644),
    "SDL3.dll": (b"dll", 0o644),
    "assets/font.otf": (b"font", 0o644),
}


def write_stage(root, name, files, target, launch, version=VERSION):
    """Create a stage dir and the real package manifest for it."""
    stage = root / name
    for relative, (data, mode) in files.items():
        path = stage / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(data)
        path.chmod(mode)
    result = subprocess.run(
        [sys.executable, "-I", PACKAGE_TOOL, "write", str(stage),
         "--version=" + version, "--target=" + target, "--launch=" + launch],
        capture_output=True, text=True,
    )
    assert result.returncode == 0, result.stderr
    return stage, (stage / "package-manifest.txt").read_text()


def write_tar(path, top, files, manifest_text, extra_members=(), top_name=None,
              fmt=tarfile.USTAR_FORMAT):
    # The release format is POSIX ustar, so the valid fixtures are built in it.
    with tarfile.open(path, "w:gz", format=fmt) as archive:
        directory = tarfile.TarInfo(top_name or top)
        directory.type = tarfile.DIRTYPE
        directory.mode = 0o755
        archive.addfile(directory)
        for relative, (data, mode) in files.items():
            info = tarfile.TarInfo((top_name or top) + "/" + relative)
            info.size = len(data)
            info.mode = mode
            archive.addfile(info, io.BytesIO(data))
        if manifest_text is not None:
            payload = manifest_text.encode()
            info = tarfile.TarInfo((top_name or top) + "/package-manifest.txt")
            info.size = len(payload)
            info.mode = 0o644
            archive.addfile(info, io.BytesIO(payload))
        for member in extra_members:
            archive.addfile(member)


def write_zip(path, files, manifest_text):
    with zipfile.ZipFile(path, "w", zipfile.ZIP_DEFLATED) as archive:
        for relative, (data, mode) in files.items():
            info = zipfile.ZipInfo(relative)
            info.external_attr = (0o100000 | mode) << 16
            info.compress_type = zipfile.ZIP_DEFLATED
            archive.writestr(info, data)
        info = zipfile.ZipInfo("package-manifest.txt")
        info.external_attr = 0o100644 << 16
        info.compress_type = zipfile.ZIP_DEFLATED
        archive.writestr(info, manifest_text)


def sha256_file(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def tarfile_member(name, size=0, mode=0o644, type=tarfile.REGTYPE, linkname=""):
    """One tar member with full control, for the hostile fixtures."""
    member = tarfile.TarInfo(name)
    member.size = size
    member.mode = mode
    member.type = type
    member.linkname = linkname
    return member


def raw_zip(path, entries):
    """Build a zip by hand, so tests can set flags, methods and extra fields zipfile hides."""
    locals_ = []
    centrals = []
    offset = 0
    for entry in entries:
        name = entry["name"].encode() if isinstance(entry["name"], str) else entry["name"]
        data = entry.get("data", b"")
        method = entry.get("method", 0)
        flags = entry.get("flags", 0)
        extra_local = entry.get("extra_local", b"")
        extra_central = entry.get("extra_central", b"")
        crc = entry.get("crc", zlib.crc32(data) & 0xFFFFFFFF)
        if method == 8:
            compressor = zlib.compressobj(9, zlib.DEFLATED, -15)
            compressed = compressor.compress(data) + compressor.flush()
        else:
            compressed = data
        comp_size = entry.get("comp_size", len(compressed))
        uncomp_size = entry.get("uncomp_size", len(data))
        local_name = entry.get("local_name", name)
        if isinstance(local_name, str):
            local_name = local_name.encode()
        local = (
            struct.pack("<4sHHHHHIIIHH", b"PK\x03\x04", 20, flags, method, 0, 0,
                        crc, len(compressed), len(data), len(local_name),
                        len(extra_local))
            + local_name + extra_local + compressed
        )
        central = (
            struct.pack("<4sHHHHHHIIIHHHHHII", b"PK\x01\x02", 20, 20, flags, method,
                        0, 0, crc, comp_size, uncomp_size, len(name),
                        len(extra_central), 0, entry.get("disk", 0), 0,
                        entry.get("external", 0o100644 << 16), offset)
            + name + extra_central
        )
        locals_.append(local)
        centrals.append(central)
        offset += len(local)
    directory = b"".join(centrals)
    eocd = struct.pack("<4sHHHHIIH", b"PK\x05\x06", 0, 0, len(entries), len(entries),
                       len(directory), offset, 0)
    path.write_bytes(b"".join(locals_) + directory + eocd)


class UpdateManifestTest(unittest.TestCase):
    def setUp(self):
        self._tmp = tempfile.TemporaryDirectory(prefix="update-manifest-test-")
        self.root = Path(self._tmp.name)

    def tearDown(self):
        self._tmp.cleanup()

    def make_pair(self):
        _, linux_manifest = write_stage(
            self.root, "linux-stage", LINUX_FILES, "linux-x86_64", "run"
        )
        _, windows_manifest = write_stage(
            self.root, "windows-stage", WINDOWS_FILES, "windows-x86_64",
            "DaybreakRemake.exe",
        )
        linux = self.root / LINUX_ARCHIVE
        write_tar(linux, LINUX_TOP, LINUX_FILES, linux_manifest)
        windows = self.root / WINDOWS_ARCHIVE
        write_zip(windows, WINDOWS_FILES, windows_manifest)
        return linux, windows

    def run_tool(self, linux, windows, version=VERSION, out=None, env=None):
        out = out or (self.root / "update-manifest.txt")
        environment = dict(os.environ)
        if env:
            environment.update(env)
        result = subprocess.run(
            [sys.executable, "-I", UPDATE_TOOL,
             "--version=" + version, "--linux=" + str(linux),
             "--windows=" + str(windows), "--out=" + str(out)],
            capture_output=True, text=True, env=environment,
        )
        return result, out

    def test_rejects_an_unsigned_test_build(self):
        marker = {"BUILD-INFO.txt": (b"Version: 1.2.3\nSigned: unsigned-test-build\n",
                                     0o644)}
        linux_files = dict(LINUX_FILES, **marker)
        windows_files = dict(WINDOWS_FILES, **marker)
        _, linux_manifest = write_stage(
            self.root, "unsigned-linux", linux_files, "linux-x86_64", "run")
        _, windows_manifest = write_stage(
            self.root, "unsigned-windows", windows_files, "windows-x86_64",
            "DaybreakRemake.exe")
        linux = self.root / LINUX_ARCHIVE
        write_tar(linux, LINUX_TOP, linux_files, linux_manifest)
        windows = self.root / WINDOWS_ARCHIVE
        write_zip(windows, windows_files, windows_manifest)
        # The CI job exports the escape; this test owns the environment it checks.
        refused, _ = self.run_tool(
            linux, windows, env={"DAYBREAK_ALLOW_UNSIGNED_PACKAGE": ""})
        self.assertEqual(refused.returncode, 1, refused.stderr)
        self.assertIn("unsigned-test-build", refused.stderr)
        allowed, _ = self.run_tool(
            linux, windows, env={"DAYBREAK_ALLOW_UNSIGNED_PACKAGE": "1"})
        self.assertEqual(allowed.returncode, 0, allowed.stderr)
        self.assertIn("unsigned test build", allowed.stderr)

    def test_success_writes_the_exact_format(self):
        linux, windows = self.make_pair()
        result, out = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 0, result.stderr)
        expected = (
            "format = 1\n"
            "version = 1.2.3\n"
            "notes = https://github.com/Vmarcelo49/daybreak-remake/releases/tag/v1.2.3\n"
            "[linux-x86_64]\n"
            "archive = %s\n"
            "size = %d\n"
            "sha256 = %s\n"
            "[windows-x86_64]\n"
            "archive = %s\n"
            "size = %d\n"
            "sha256 = %s\n"
            % (LINUX_ARCHIVE, linux.stat().st_size, sha256_file(linux),
               WINDOWS_ARCHIVE, windows.stat().st_size, sha256_file(windows))
        )
        self.assertEqual(out.read_text(), expected)
        for line in expected.splitlines():
            self.assertEqual(line, line.rstrip(), "trailing whitespace: %r" % line)

    def test_output_is_reproducible(self):
        linux, windows = self.make_pair()
        first, first_path = self.run_tool(linux, windows, out=self.root / "one.txt")
        second, second_path = self.run_tool(linux, windows, out=self.root / "two.txt")
        self.assertEqual(first.returncode, 0, first.stderr)
        self.assertEqual(second.returncode, 0, second.stderr)
        self.assertEqual(first_path.read_bytes(), second_path.read_bytes())

    def test_rejects_a_missing_package_manifest(self):
        linux, windows = self.make_pair()
        write_tar(linux, LINUX_TOP, LINUX_FILES, None)
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("no package-manifest.txt", result.stderr)

    def test_rejects_an_extra_file(self):
        linux, windows = self.make_pair()
        files = dict(LINUX_FILES)
        files["stray.txt"] = (b"stray", 0o644)
        _, manifest = write_stage(self.root, "extra-stage", LINUX_FILES,
                                  "linux-x86_64", "run")
        write_tar(linux, LINUX_TOP, files, manifest)
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("does not list", result.stderr)

    def test_rejects_a_hash_mismatch(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "hash-stage", LINUX_FILES,
                                  "linux-x86_64", "run")
        files = dict(LINUX_FILES)
        files["lib/libfoo.so"] = (b"LIBBYTES", 0o644)
        write_tar(linux, LINUX_TOP, files, manifest)
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("hashes to", result.stderr)

    def test_rejects_a_lost_exec_bit(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "exec-stage", LINUX_FILES,
                                  "linux-x86_64", "run")
        files = dict(LINUX_FILES)
        files["run"] = (LINUX_FILES["run"][0], 0o644)
        write_tar(linux, LINUX_TOP, files, manifest)
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("the manifest says", result.stderr)

    def test_rejects_a_symlink_member(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "symlink-stage", LINUX_FILES,
                                  "linux-x86_64", "run")
        link = tarfile.TarInfo(LINUX_TOP + "/link")
        link.type = tarfile.SYMTYPE
        link.linkname = "run"
        write_tar(linux, LINUX_TOP, LINUX_FILES, manifest, extra_members=[link])
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("symlink", result.stderr)

    def test_rejects_a_hard_link_member(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "hardlink-stage", LINUX_FILES,
                                  "linux-x86_64", "run")
        link = tarfile.TarInfo(LINUX_TOP + "/link")
        link.type = tarfile.LNKTYPE
        link.linkname = LINUX_TOP + "/run"
        write_tar(linux, LINUX_TOP, LINUX_FILES, manifest, extra_members=[link])
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("hard link", result.stderr)

    def test_rejects_a_case_collision_in_the_archive(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "case-stage", LINUX_FILES,
                                  "linux-x86_64", "run")
        extra = tarfile.TarInfo(LINUX_TOP + "/RUN")
        extra.size = 0
        extra.mode = 0o644
        write_tar(linux, LINUX_TOP, LINUX_FILES, manifest, extra_members=[extra])
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("differ only in case", result.stderr)

    def test_rejects_a_file_that_is_also_a_directory(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "prefix-stage", LINUX_FILES,
                                  "linux-x86_64", "run")
        extra = tarfile.TarInfo(LINUX_TOP + "/run/child")
        extra.size = 0
        extra.mode = 0o644
        write_tar(linux, LINUX_TOP, LINUX_FILES, manifest, extra_members=[extra])
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("also a directory", result.stderr)

    def test_rejects_a_windows_device_name_in_the_archive(self):
        linux, windows = self.make_pair()
        _, windows_manifest = write_stage(
            self.root, "device-stage", WINDOWS_FILES, "windows-x86_64",
            "DaybreakRemake.exe",
        )
        with zipfile.ZipFile(windows, "w") as archive:
            for relative, (data, mode) in WINDOWS_FILES.items():
                info = zipfile.ZipInfo(relative)
                info.external_attr = (0o100000 | mode) << 16
                archive.writestr(info, data)
            info = zipfile.ZipInfo("package-manifest.txt")
            info.external_attr = 0o100644 << 16
            archive.writestr(info, windows_manifest)
            info = zipfile.ZipInfo("CON")
            info.external_attr = 0o100644 << 16
            archive.writestr(info, b"x")
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("device name", result.stderr)

    def test_rejects_an_unsafe_member_path(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "unsafe-stage", LINUX_FILES,
                                  "linux-x86_64", "run")
        evil = tarfile.TarInfo("../evil")
        evil.size = 0
        evil.mode = 0o644
        write_tar(linux, LINUX_TOP, LINUX_FILES, manifest, extra_members=[evil])
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("component", result.stderr)

    def test_rejects_two_top_level_directories(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "two-top-stage", LINUX_FILES,
                                  "linux-x86_64", "run")
        extra = tarfile.TarInfo("other/file")
        extra.size = 0
        extra.mode = 0o644
        write_tar(linux, LINUX_TOP, LINUX_FILES, manifest, extra_members=[extra])
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("top-level directory", result.stderr)

    def test_rejects_a_version_mismatch(self):
        # Archives named for 1.2.4 whose package manifests still say 1.2.3: the name
        # checks pass, so this exercises the manifest-version comparison.
        _, linux_manifest = write_stage(
            self.root, "mismatch-linux", LINUX_FILES, "linux-x86_64", "run"
        )
        _, windows_manifest = write_stage(
            self.root, "mismatch-windows", WINDOWS_FILES, "windows-x86_64",
            "DaybreakRemake.exe",
        )
        linux = self.root / "daybreak-1.2.4-linux-x86_64.tar.gz"
        write_tar(linux, "daybreak-1.2.4-linux-x86_64", LINUX_FILES, linux_manifest)
        windows = self.root / "daybreak-1.2.4-abc1234-windows-x86_64.zip"
        write_zip(windows, WINDOWS_FILES, windows_manifest)
        result, _ = self.run_tool(linux, windows, version="1.2.4")
        self.assertEqual(result.returncode, 1)
        self.assertIn("says version", result.stderr)

    def test_rejects_a_renamed_linux_archive(self):
        linux, windows = self.make_pair()
        renamed = self.root / "daybreak-1.2.3-linux-x86_64-copy.tar.gz"
        linux.rename(renamed)
        result, _ = self.run_tool(renamed, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("the release's Linux archive is", result.stderr)

    def test_rejects_a_wrong_linux_top_directory(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "top-stage", LINUX_FILES,
                                  "linux-x86_64", "run")
        write_tar(linux, LINUX_TOP, LINUX_FILES, manifest,
                  top_name="daybreak-9.9.9-linux-x86_64")
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("top-level directory", result.stderr)

    def test_rejects_a_windows_archive_without_a_revision(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "norev-stage", WINDOWS_FILES,
                                  "windows-x86_64", "DaybreakRemake.exe")
        renamed = self.root / "daybreak-1.2.3-windows-x86_64.zip"
        write_zip(renamed, WINDOWS_FILES, manifest)
        result, _ = self.run_tool(linux, renamed)
        self.assertEqual(result.returncode, 1)
        self.assertIn("must not be released", result.stderr)

    def test_rejects_a_dirty_windows_archive(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "dirty-stage", WINDOWS_FILES,
                                  "windows-x86_64", "DaybreakRemake.exe")
        renamed = self.root / "daybreak-1.2.3-abc1234-dirty-windows-x86_64.zip"
        write_zip(renamed, WINDOWS_FILES, manifest)
        result, _ = self.run_tool(linux, renamed)
        self.assertEqual(result.returncode, 1)
        self.assertIn("must not be released", result.stderr)

    def test_rejects_a_short_windows_revision(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "shortrev-stage", WINDOWS_FILES,
                                  "windows-x86_64", "DaybreakRemake.exe")
        renamed = self.root / "daybreak-1.2.3-abc12-windows-x86_64.zip"
        write_zip(renamed, WINDOWS_FILES, manifest)
        result, _ = self.run_tool(linux, renamed)
        self.assertEqual(result.returncode, 1)
        self.assertIn("must not be released", result.stderr)

    def test_rejects_a_bad_semver(self):
        linux, windows = self.make_pair()
        for version in ("1.2", "v1.2.3", "01.2.3", "1.2.3-rc1"):
            with self.subTest(version=version):
                result, _ = self.run_tool(linux, windows, version=version)
                self.assertEqual(result.returncode, 1)
                self.assertIn("plain X.Y.Z", result.stderr)

    def test_rejects_a_windows_symlink(self):
        linux, windows = self.make_pair()
        _, windows_manifest = write_stage(
            self.root, "winlink-stage", WINDOWS_FILES, "windows-x86_64",
            "DaybreakRemake.exe",
        )
        with zipfile.ZipFile(windows, "w") as archive:
            for relative, (data, _) in WINDOWS_FILES.items():
                info = zipfile.ZipInfo(relative)
                info.external_attr = 0o100644 << 16
                archive.writestr(info, data)
            info = zipfile.ZipInfo("package-manifest.txt")
            info.external_attr = 0o100644 << 16
            archive.writestr(info, windows_manifest)
            link = zipfile.ZipInfo("link")
            link.external_attr = (0o120777) << 16
            archive.writestr(link, b"run")
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("symlink", result.stderr)

    def test_rejects_the_wrong_target(self):
        linux, windows = self.make_pair()
        # A valid manifest for the other platform: parseable, wrong for this archive.
        swapped = dict(WINDOWS_FILES)
        swapped["DaybreakRemake.exe"] = (WINDOWS_FILES["DaybreakRemake.exe"][0], 0o755)
        _, linux_target_manifest = write_stage(
            self.root, "swap-stage", swapped, "linux-x86_64", "DaybreakRemake.exe"
        )
        write_zip(windows, WINDOWS_FILES, linux_target_manifest)
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("says target", result.stderr)

    def test_rejects_a_missing_archive(self):
        linux, windows = self.make_pair()
        result, _ = self.run_tool(self.root / "absent.tar.gz", windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("no such file", result.stderr)

    def test_rejects_a_gnu_long_name_archive(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "gnu-stage", LINUX_FILES,
                                  "linux-x86_64", "run")
        long_name = "x" * 150
        extra = tarfile.TarInfo(LINUX_TOP + "/" + long_name)
        extra.size = 0
        extra.mode = 0o644
        write_tar(linux, LINUX_TOP, LINUX_FILES, manifest, extra_members=[extra],
                  fmt=tarfile.GNU_FORMAT)
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("not a POSIX ustar", result.stderr)

    def test_rejects_a_pax_archive(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "pax-stage", LINUX_FILES,
                                  "linux-x86_64", "run")
        extra = tarfile.TarInfo(LINUX_TOP + "/" + "y" * 150)
        extra.size = 0
        extra.mode = 0o644
        write_tar(linux, LINUX_TOP, LINUX_FILES, manifest, extra_members=[extra],
                  fmt=tarfile.PAX_FORMAT)
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("type", result.stderr)

    def test_rejects_a_sparse_tar_member(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "sparse-stage", LINUX_FILES,
                                  "linux-x86_64", "run")
        sparse = tarfile.TarInfo(LINUX_TOP + "/sparse")
        sparse.type = tarfile.GNUTYPE_SPARSE
        sparse.size = 0
        write_tar(linux, LINUX_TOP, LINUX_FILES, manifest, extra_members=[sparse])
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("type", result.stderr)

    def test_rejects_an_encrypted_zip_entry(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "enc-stage", WINDOWS_FILES,
                                  "windows-x86_64", "DaybreakRemake.exe")
        entries = [{"name": name, "data": data, "method": 8}
                   for name, (data, _) in WINDOWS_FILES.items()]
        entries.append({"name": "package-manifest.txt", "data": manifest.encode(),
                        "method": 8})
        entries[0]["flags"] = 0x0001
        raw_zip(windows, entries)
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("encrypted", result.stderr)

    def test_rejects_a_bzip2_zip_entry(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "bz-stage", WINDOWS_FILES,
                                  "windows-x86_64", "DaybreakRemake.exe")
        with zipfile.ZipFile(windows, "w", zipfile.ZIP_BZIP2) as archive:
            for name, (data, _) in WINDOWS_FILES.items():
                archive.writestr(name, data)
            archive.writestr("package-manifest.txt", manifest)
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("compression method 12", result.stderr)

    def test_rejects_a_zip64_extra_field(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "z64-stage", WINDOWS_FILES,
                                  "windows-x86_64", "DaybreakRemake.exe")
        entries = [{"name": name, "data": data, "method": 0}
                   for name, (data, _) in WINDOWS_FILES.items()]
        entries.append({"name": "package-manifest.txt", "data": manifest.encode(),
                        "method": 0})
        entries[0]["extra_central"] = struct.pack("<HH", 0x0001, 16) + b"\0" * 16
        raw_zip(windows, entries)
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("zip64", result.stderr)

    def test_rejects_a_truncated_gzip(self):
        linux, windows = self.make_pair()
        linux.write_bytes(linux.read_bytes()[:-8])
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("gzip", result.stderr)

    def test_rejects_trailing_data_after_the_gzip_member(self):
        linux, windows = self.make_pair()
        linux.write_bytes(linux.read_bytes() + b"junk")
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("data after the gzip member", result.stderr)

    def test_rejects_a_mismatched_local_zip_name(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "local-stage", WINDOWS_FILES,
                                  "windows-x86_64", "DaybreakRemake.exe")
        entries = [{"name": name, "data": data, "method": 8}
                   for name, (data, _) in WINDOWS_FILES.items()]
        entries.append({"name": "package-manifest.txt", "data": manifest.encode(),
                        "method": 8})
        entries[0]["local_name"] = "Other.exe"
        raw_zip(windows, entries)
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("different name", result.stderr)

    def test_rejects_a_bad_crc(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "crc-stage", WINDOWS_FILES,
                                  "windows-x86_64", "DaybreakRemake.exe")
        entries = [{"name": name, "data": data, "method": 8}
                   for name, (data, _) in WINDOWS_FILES.items()]
        entries.append({"name": "package-manifest.txt", "data": manifest.encode(),
                        "method": 8})
        entries[0]["crc"] = 0xDEADBEEF
        raw_zip(windows, entries)
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("CRC32", result.stderr)

    def test_rejects_a_zip_bomb_ratio(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "bomb-stage", WINDOWS_FILES,
                                  "windows-x86_64", "DaybreakRemake.exe")
        entries = [{"name": name, "data": data, "method": 8}
                   for name, (data, _) in WINDOWS_FILES.items()]
        entries.append({"name": "package-manifest.txt", "data": manifest.encode(),
                        "method": 8})
        entries[0]["uncomp_size"] = 10 * 1024 * 1024
        raw_zip(windows, entries)
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 1)
        self.assertIn("zip bomb", result.stderr)

    def test_accepts_a_stored_zip(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "stored-stage", WINDOWS_FILES,
                                  "windows-x86_64", "DaybreakRemake.exe")
        entries = [{"name": name, "data": data, "method": 0}
                   for name, (data, _) in WINDOWS_FILES.items()]
        entries.append({"name": "package-manifest.txt", "data": manifest.encode(),
                        "method": 0})
        raw_zip(windows, entries)
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 0, result.stderr)

    def test_accepts_dot_slash_zip_names(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "dotzip-stage", WINDOWS_FILES,
                                  "windows-x86_64", "DaybreakRemake.exe")
        entries = [{"name": "./" + name, "data": data, "method": 8}
                   for name, (data, _) in WINDOWS_FILES.items()]
        entries.append({"name": "./package-manifest.txt", "data": manifest.encode(),
                        "method": 8})
        raw_zip(windows, entries)
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 0, result.stderr)

    def test_accepts_dot_slash_tar_names(self):
        linux, windows = self.make_pair()
        _, manifest = write_stage(self.root, "dotslash-stage", LINUX_FILES,
                                  "linux-x86_64", "run")
        write_tar(linux, LINUX_TOP, LINUX_FILES, manifest,
                  top_name="./" + LINUX_TOP)
        result, _ = self.run_tool(linux, windows)
        self.assertEqual(result.returncode, 0, result.stderr)


if __name__ == "__main__":
    unittest.main(verbosity=2)
