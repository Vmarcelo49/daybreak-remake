#!/usr/bin/env python3
"""Tests for `tools/package_manifest.py` (issue #100).

The package manifest is the list the updater uses to decide what it may replace, so it
has to be exact: sorted, hashed, mode-carrying and hostile-input-proof. These tests drive
the real command line the packaging scripts use, and parse crafted manifests directly,
with no game data, no network and no build output.
"""

import hashlib
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

TESTS = Path(__file__).resolve().parent
TOOLS = TESTS.parent / "tools"
sys.path.insert(0, str(TOOLS))

import package_manifest as pm  # noqa: E402

TOOL = str(TOOLS / "package_manifest.py")


def run_tool(*args):
    return subprocess.run(
        [sys.executable, "-I", TOOL, *args], capture_output=True, text=True
    )


def write_file(path, data=b"", mode=0o644):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(data)
    path.chmod(mode)
    return path


def sha256(data):
    return hashlib.sha256(data).hexdigest()


class PackageManifestTest(unittest.TestCase):
    def setUp(self):
        self._tmp = tempfile.TemporaryDirectory(prefix="package-manifest-test-")
        self.root = Path(self._tmp.name)

    def tearDown(self):
        self._tmp.cleanup()

    def make_stage(self, files, name="stage"):
        stage = self.root / name
        stage.mkdir()
        for relative, data, mode in files:
            write_file(stage / relative, data, mode)
        return stage

    def write_manifest(self, stage, version="1.2.3", target="linux-x86_64", launch="run"):
        return run_tool(
            "write", str(stage),
            "--version=" + version, "--target=" + target, "--launch=" + launch,
        )

    def test_write_pins_the_exact_format(self):
        stage = self.make_stage([
            ("a.txt", b"alpha\n", 0o644),
            ("run", b"#!/bin/sh\n", 0o755),
        ])
        result = self.write_manifest(stage)
        self.assertEqual(result.returncode, 0, result.stderr)
        expected = (
            "format = 1\n"
            "version = 1.2.3\n"
            "target = linux-x86_64\n"
            "launch = run\n"
            "[files]\n"
            "%s  6  -  a.txt\n"
            "%s  10  x  run\n"
            % (sha256(b"alpha\n"), sha256(b"#!/bin/sh\n"))
        )
        self.assertEqual((stage / "package-manifest.txt").read_text(), expected)

    def test_write_sorts_bytewise_and_skips_itself(self):
        stage = self.make_stage([
            ("b.txt", b"b", 0o644),
            ("A.txt", b"a", 0o755),
            ("assets/z.otf", b"z", 0o644),
            ("assets/aa.otf", b"aa", 0o644),
        ])
        write_file(stage / "package-manifest.txt", b"stale\n")
        result = self.write_manifest(stage, launch="A.txt")
        self.assertEqual(result.returncode, 0, result.stderr)
        manifest = pm.parse_manifest((stage / "package-manifest.txt").read_text())
        self.assertEqual(
            [entry.path for entry in manifest.entries],
            ["A.txt", "assets/aa.otf", "assets/z.otf", "b.txt"],
        )
        self.assertNotIn("package-manifest.txt", [e.path for e in manifest.entries])

    def test_write_is_reproducible(self):
        stage = self.make_stage([("run", b"x", 0o755), ("a", b"y", 0o644)])
        self.assertEqual(self.write_manifest(stage).returncode, 0)
        first = (stage / "package-manifest.txt").read_bytes()
        self.assertEqual(self.write_manifest(stage).returncode, 0)
        self.assertEqual((stage / "package-manifest.txt").read_bytes(), first)

    def test_check_accepts_a_generated_manifest(self):
        stage = self.make_stage([("run", b"x", 0o755), ("lib/a.so", b"y", 0o644)])
        self.assertEqual(self.write_manifest(stage).returncode, 0)
        result = run_tool("check", str(stage))
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("package_manifest: ok", result.stdout)

    def test_check_rejects_a_tampered_file(self):
        stage = self.make_stage([("run", b"x", 0o755), ("a", b"y", 0o644)])
        self.assertEqual(self.write_manifest(stage).returncode, 0)
        (stage / "a").write_bytes(b"Y")
        result = run_tool("check", str(stage))
        self.assertEqual(result.returncode, 1)
        self.assertIn("sha256", result.stderr)

    def test_check_rejects_an_extra_file(self):
        stage = self.make_stage([("run", b"x", 0o755)])
        self.assertEqual(self.write_manifest(stage).returncode, 0)
        write_file(stage / "unexpected", b"z")
        result = run_tool("check", str(stage))
        self.assertEqual(result.returncode, 1)
        self.assertIn("not listed", result.stderr)

    def test_check_rejects_a_missing_file(self):
        stage = self.make_stage([("run", b"x", 0o755), ("a", b"y", 0o644)])
        self.assertEqual(self.write_manifest(stage).returncode, 0)
        (stage / "a").unlink()
        result = run_tool("check", str(stage))
        self.assertEqual(result.returncode, 1)
        self.assertIn("missing", result.stderr)

    def test_check_rejects_a_changed_exec_bit(self):
        stage = self.make_stage([("run", b"x", 0o755)])
        self.assertEqual(self.write_manifest(stage).returncode, 0)
        (stage / "run").chmod(0o644)
        result = run_tool("check", str(stage))
        self.assertEqual(result.returncode, 1)
        self.assertIn("mode", result.stderr)

    def test_write_rejects_a_symlink(self):
        stage = self.make_stage([("run", b"x", 0o755)])
        (stage / "link").symlink_to("run")
        result = self.write_manifest(stage)
        self.assertEqual(result.returncode, 1)
        self.assertIn("symlink", result.stderr)

    def test_write_rejects_unsafe_names(self):
        for index, name in enumerate(("back\\slash", "C:evil", "control\x01name")):
            with self.subTest(name=name):
                stage = self.make_stage([("run", b"x", 0o755)], name="stage-%d" % index)
                write_file(stage / name, b"z")
                result = self.write_manifest(stage)
                self.assertEqual(result.returncode, 1, result.stdout)
                self.assertIn("package_manifest:", result.stderr)

    def test_write_rejects_windows_forbidden_characters(self):
        for index, character in enumerate('<>:"|?*'):
            with self.subTest(character=character):
                stage = self.make_stage([("run", b"x", 0o755)], name="stage-char-%d" % index)
                write_file(stage / ("bad" + character + "name"), b"z")
                result = self.write_manifest(stage)
                self.assertEqual(result.returncode, 1, result.stdout)
                self.assertIn("NTFS", result.stderr)

    def test_write_rejects_a_component_ending_in_dot_or_space(self):
        # A whole-path trailing space is caught by the whitespace rule; the component rule
        # is what catches the ones Windows would silently drop inside the path.
        cases = {
            "trailing.": "ending in '.' or a space",
            "trailing ": "whitespace",
            "dir./inner": "ending in '.' or a space",
            "dir /inner": "ending in '.' or a space",
        }
        for index, (name, message) in enumerate(cases.items()):
            with self.subTest(name=name):
                stage = self.make_stage([("run", b"x", 0o755)], name="stage-dot-%d" % index)
                write_file(stage / name, b"z")
                result = self.write_manifest(stage)
                self.assertEqual(result.returncode, 1, result.stdout)
                self.assertIn(message, result.stderr)

    def test_write_rejects_windows_device_names(self):
        for index, name in enumerate(
            ("CON", "con.txt", "aux", "COM1", "LPT9", "nul.dat", "dir/PRN")
        ):
            with self.subTest(name=name):
                stage = self.make_stage([("run", b"x", 0o755)], name="stage-dev-%d" % index)
                write_file(stage / name, b"z")
                result = self.write_manifest(stage)
                self.assertEqual(result.returncode, 1, result.stdout)
                self.assertIn("device name", result.stderr)

    def test_write_rejects_a_case_collision(self):
        stage = self.make_stage([
            ("run", b"x", 0o755),
            ("A.txt", b"upper", 0o644),
            ("a.txt", b"lower", 0o644),
        ])
        result = self.write_manifest(stage)
        self.assertEqual(result.returncode, 1)
        self.assertIn("differ only in case", result.stderr)

    def test_parse_rejects_a_file_that_is_also_a_directory(self):
        text = (
            "format = 1\nversion = 1.2.3\ntarget = linux-x86_64\nlaunch = a\n[files]\n"
            "%s  1  x  a\n%s  1  -  a/b\n" % (sha256(b"a"), sha256(b"b"))
        )
        with self.assertRaises(pm.ManifestError) as caught:
            pm.parse_manifest(text)
        self.assertIn("also a directory", str(caught.exception))

    def test_parse_rejects_a_case_collision(self):
        text = (
            "format = 1\nversion = 1.2.3\ntarget = linux-x86_64\nlaunch = A.txt\n[files]\n"
            "%s  1  x  A.txt\n%s  1  -  a.txt\n" % (sha256(b"a"), sha256(b"b"))
        )
        with self.assertRaises(pm.ManifestError) as caught:
            pm.parse_manifest(text)
        self.assertIn("differ only in case", str(caught.exception))

    def test_write_rejects_a_launch_that_is_not_shipped(self):
        stage = self.make_stage([("run", b"x", 0o755)])
        result = self.write_manifest(stage, launch="daybreak")
        self.assertEqual(result.returncode, 1)
        self.assertIn("not one of the package's files", result.stderr)

    def test_write_rejects_a_non_executable_launch(self):
        stage = self.make_stage([("run", b"x", 0o644)])
        result = self.write_manifest(stage)
        self.assertEqual(result.returncode, 1)
        self.assertIn("not executable", result.stderr)

    def test_write_rejects_an_unsafe_launch(self):
        stage = self.make_stage([("run", b"x", 0o755)])
        result = self.write_manifest(stage, launch="../run")
        self.assertEqual(result.returncode, 1)
        self.assertIn("component", result.stderr)

    def test_write_rejects_a_bad_version(self):
        stage = self.make_stage([("run", b"x", 0o755)])
        result = self.write_manifest(stage, version="1.2 3")
        self.assertEqual(result.returncode, 1)
        self.assertIn("version", result.stderr)

    def test_write_rejects_an_unknown_target(self):
        stage = self.make_stage([("run", b"x", 0o755)])
        result = self.write_manifest(stage, target="macos-x86_64")
        self.assertEqual(result.returncode, 2)

    def test_windows_modes_are_always_dash(self):
        stage = self.make_stage([("DaybreakRemake.exe", b"MZ", 0o755)])
        result = self.write_manifest(
            stage, target="windows-x86_64", launch="DaybreakRemake.exe"
        )
        self.assertEqual(result.returncode, 0, result.stderr)
        manifest = pm.parse_manifest((stage / "package-manifest.txt").read_text())
        self.assertEqual({entry.mode for entry in manifest.entries}, {"-"})

    def test_parse_rejects_an_unknown_format(self):
        text = "format = 2\nversion = 1.2.3\ntarget = linux-x86_64\nlaunch = run\n[files]\n"
        with self.assertRaises(pm.ManifestError) as caught:
            pm.parse_manifest(text)
        self.assertIn("does not understand", str(caught.exception))

    def test_parse_rejects_unsorted_entries(self):
        text = (
            "format = 1\nversion = 1.2.3\ntarget = linux-x86_64\nlaunch = b\n[files]\n"
            "%s  1  -  b\n%s  1  -  a\n" % (sha256(b"b"), sha256(b"a"))
        )
        with self.assertRaises(pm.ManifestError) as caught:
            pm.parse_manifest(text)
        self.assertIn("sorted", str(caught.exception))

    def test_parse_rejects_listing_itself(self):
        text = (
            "format = 1\nversion = 1.2.3\ntarget = linux-x86_64\nlaunch = run\n[files]\n"
            "%s  1  x  run\n%s  1  -  package-manifest.txt\n"
            % (sha256(b"r"), sha256(b"m"))
        )
        with self.assertRaises(pm.ManifestError) as caught:
            pm.parse_manifest(text)
        self.assertIn("itself", str(caught.exception))

    def test_parse_rejects_traversal(self):
        text = (
            "format = 1\nversion = 1.2.3\ntarget = linux-x86_64\nlaunch = run\n[files]\n"
            "%s  1  x  run\n%s  1  -  ../evil\n" % (sha256(b"r"), sha256(b"e"))
        )
        with self.assertRaises(pm.ManifestError) as caught:
            pm.parse_manifest(text)
        self.assertIn("component", str(caught.exception))

    def test_parse_rejects_crlf(self):
        text = "format = 1\r\nversion = 1.2.3\r\ntarget = linux-x86_64\r\nlaunch = run\r\n[files]\r\n"
        with self.assertRaises(pm.ManifestError) as caught:
            pm.parse_manifest(text)
        self.assertIn("CRLF", str(caught.exception))

    def test_check_rejects_a_hand_edited_hash(self):
        stage = self.make_stage([("run", b"x", 0o755)])
        self.assertEqual(self.write_manifest(stage).returncode, 0)
        path = stage / "package-manifest.txt"
        text = path.read_text().replace(sha256(b"x"), "0" * 64)
        path.write_text(text)
        result = run_tool("check", str(stage))
        self.assertEqual(result.returncode, 1)
        self.assertIn("sha256", result.stderr)

    def test_check_without_a_manifest_fails(self):
        stage = self.make_stage([("run", b"x", 0o755)])
        result = run_tool("check", str(stage))
        self.assertEqual(result.returncode, 1)
        self.assertIn("missing", result.stderr)


if __name__ == "__main__":
    unittest.main(verbosity=2)
