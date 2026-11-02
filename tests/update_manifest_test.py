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
import subprocess
import sys
import tarfile
import tempfile
import unittest
import zipfile
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


def write_tar(path, top, files, manifest_text, extra_members=(), top_name=None):
    with tarfile.open(path, "w:gz") as archive:
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

    def run_tool(self, linux, windows, version=VERSION, out=None):
        out = out or (self.root / "update-manifest.txt")
        result = subprocess.run(
            [sys.executable, "-I", UPDATE_TOOL,
             "--version=" + version, "--linux=" + str(linux),
             "--windows=" + str(windows), "--out=" + str(out)],
            capture_output=True, text=True,
        )
        return result, out

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
        linux, windows = self.make_pair()
        result, _ = self.run_tool(linux, windows, version="1.2.4")
        self.assertEqual(result.returncode, 1)
        self.assertIn("says version", result.stderr)

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
