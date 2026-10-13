#!/usr/bin/env python3
"""Regression tests for the checking tools themselves.

The audit found that the tools protecting the product could silently pass: a crash became
a skip, a truncated trace was called a match, and an unexpected asset-sweep failure was
absorbed by a count. These tests pin the corrected behaviour so it cannot regress, and
they need no game data, no GPU and no build output.

Run directly (`python3 tests/check_tools_test.py`) or through CTest
(`ctest -R check_tools_test`).
"""
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

TESTS = Path(__file__).resolve().parent
sys.path.insert(0, str(TESTS))

import capture_probe  # noqa: E402
import release_check  # noqa: E402
import showcase  # noqa: E402


def write_script(path, body):
    path.write_text("#!/bin/sh\n" + body, encoding="utf-8")
    path.chmod(0o755)
    return str(path)


class RunDemoTests(unittest.TestCase):
    """run_demo must separate a missing prerequisite from a broken run."""

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.dir = Path(self.tmp.name)
        self.install = self.dir / "install"
        (self.install / "data").mkdir(parents=True)
        self.out = str(self.dir / "out.ppm")

    def tearDown(self):
        self.tmp.cleanup()

    def test_missing_install_is_a_prerequisite(self):
        with self.assertRaises(capture_probe.PrerequisiteMissing):
            capture_probe.require_install(str(self.dir / "absent"), "suite")

    def test_present_install_passes_the_prerequisite(self):
        capture_probe.require_install(str(self.install), "suite")

    def test_missing_asset_inside_an_install_fails(self):
        with self.assertRaises(capture_probe.CaptureFailed):
            capture_probe.require_asset(str(self.install / "data" / "stage01"),
                                        "suite", "stage01")

    def test_no_adapter_marker_is_a_prerequisite(self):
        demo = write_script(self.dir / "noadapter.sh",
                            'echo "RESULT: no usable GPU adapter: needs Vulkan"\nexit 1\n')
        with self.assertRaises(capture_probe.PrerequisiteMissing):
            capture_probe.run_demo(demo, str(self.install), self.out, [])

    def test_execution_failure_is_a_failure_not_a_skip(self):
        # The audit's reproduction: /bin/false used to become exit 77.
        demo = write_script(self.dir / "crash.sh", 'echo "loader exploded"\nexit 3\n')
        with self.assertRaises(capture_probe.CaptureFailed) as caught:
            capture_probe.run_demo(demo, str(self.install), self.out, [])
        self.assertIn("loader exploded", str(caught.exception))

    def test_missing_ok_marker_is_a_failure(self):
        demo = write_script(self.dir / "noresult.sh", 'echo "did something"\nexit 0\n')
        with self.assertRaises(capture_probe.CaptureFailed):
            capture_probe.run_demo(demo, str(self.install), self.out, [])

    def test_ok_marker_with_nonzero_exit_is_a_failure(self):
        demo = write_script(self.dir / "contradiction.sh", 'echo "RESULT: ok"\nexit 2\n')
        with self.assertRaises(capture_probe.CaptureFailed):
            capture_probe.run_demo(demo, str(self.install), self.out, [])

    def test_timeout_is_a_failure(self):
        demo = write_script(self.dir / "hang.sh", 'sleep 5\n')
        with self.assertRaises(capture_probe.CaptureFailed):
            capture_probe.run_demo(demo, str(self.install), self.out, [], timeout=0.2)

    def test_success_returns_the_transcript(self):
        demo = write_script(self.dir / "ok.sh", 'echo "RESULT: ok"\nexit 0\n')
        self.assertIn("RESULT: ok",
                      capture_probe.run_demo(demo, str(self.install), self.out, []))


class ReadPpmTests(unittest.TestCase):
    """A capture that is absent or malformed fails; it is never 'nothing to check'."""

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.dir = Path(self.tmp.name)

    def tearDown(self):
        self.tmp.cleanup()

    def test_missing_file_fails(self):
        with self.assertRaises(capture_probe.CaptureFailed):
            capture_probe.read_ppm(str(self.dir / "absent.ppm"))

    def test_non_ppm_fails(self):
        p = self.dir / "not.ppm"
        p.write_bytes(b"PNG-ish")
        with self.assertRaises(capture_probe.CaptureFailed):
            capture_probe.read_ppm(str(p))

    def test_truncated_payload_fails(self):
        p = self.dir / "short.ppm"
        p.write_bytes(b"P6\n4 4\n255\n" + b"\x00" * 10)
        with self.assertRaises(capture_probe.CaptureFailed):
            capture_probe.read_ppm(str(p))

    def test_valid_ppm_parses(self):
        p = self.dir / "ok.ppm"
        p.write_bytes(b"P6\n2 2\n255\n" + b"\x11" * 12)
        w, h, px = capture_probe.read_ppm(str(p))
        self.assertEqual((w, h), (2, 2))
        self.assertEqual(len(px), 12)

    def test_empty_markers_fail(self):
        with self.assertRaises(capture_probe.CaptureFailed):
            capture_probe.require_markers("cyan markers", [], "suite")

    def test_main_guard_maps_outcomes(self):
        # main_guard prints the reason, so capture the expected chatter.
        import contextlib
        import io

        def body_prereq():
            raise capture_probe.PrerequisiteMissing("no data")
        def body_fail():
            raise capture_probe.CaptureFailed("crashed")
        def body_ok():
            return 0

        with contextlib.redirect_stdout(io.StringIO()):
            self.assertEqual(capture_probe.main_guard(body_prereq), 77)
            self.assertEqual(capture_probe.main_guard(body_fail), 1)
            self.assertEqual(capture_probe.main_guard(body_ok), 0)


class CompareMatchTracesTests(unittest.TestCase):
    """Two traces of different lengths are not a match, however long the prefix."""

    LINE = ("[daybreak] cam eye=(0,0,0) p1=(1,2,3,idle) p2=(4,5,6,walk)\n")

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.dir = Path(self.tmp.name)

    def tearDown(self):
        self.tmp.cleanup()

    def run_compare(self, a_text, b_text, *args):
        a = self.dir / "a.log"
        b = self.dir / "b.log"
        a.write_text(a_text, encoding="utf-8")
        b.write_text(b_text, encoding="utf-8")
        script = TESTS / "compare_match_traces.py"
        proc = subprocess.run([sys.executable, str(script), str(a), str(b), *args],
                              capture_output=True, text=True)
        return proc.returncode, proc.stdout + proc.stderr

    def test_two_against_one_is_rejected(self):
        # The audit's exact reproduction: 2 samples vs 1 used to exit 0.
        code, out = self.run_compare(self.LINE * 2, self.LINE)
        self.assertEqual(code, 1)
        self.assertIn("lengths differ", out)

    def test_prefix_mode_never_claims_a_match(self):
        code, out = self.run_compare(self.LINE * 2, self.LINE, "--prefix")
        self.assertEqual(code, 1)
        self.assertIn("not a match", out)

    def test_equal_traces_match(self):
        code, out = self.run_compare(self.LINE * 3, self.LINE * 3)
        self.assertEqual(code, 0)
        self.assertIn("MATCH_TRACES: ok", out)

    def test_empty_trace_fails(self):
        code, out = self.run_compare("", self.LINE)
        self.assertEqual(code, 1)
        self.assertIn("no trace lines", out)


class ShowcaseSweepTests(unittest.TestCase):
    """The sweep judges cells by name and reason, never by how many failed."""

    def test_documented_stage_gap_is_accepted(self):
        gap = showcase.expected_gap("rena", "stage05", 4)
        self.assertIsNotNone(gap)

    def test_documented_kasai_gap_is_accepted(self):
        self.assertIsNotNone(showcase.expected_gap("kasai", "stage01", 2))
        self.assertIsNotNone(showcase.expected_gap("kasai", "stage05", 6))

    def test_a_new_untextured_cell_is_unexpected(self):
        self.assertIsNone(showcase.expected_gap("rena", "stage01", 2))

    def test_a_wrong_count_is_unexpected(self):
        # rena x stage05 is documented at 4 untextured draws; 7 is a new defect.
        self.assertIsNone(showcase.expected_gap("rena", "stage05", 7))

    def test_kasai_is_excluded_from_the_stage_gap_entry(self):
        # kasai's own entry owns that cell (2 or 6), so the stage entry must not claim it.
        self.assertIsNone(showcase.expected_gap("kasai", "stage05", 4))


class ShowcaseMatrixTests(unittest.TestCase):
    """check_matrix's own verdicts, with the demo faked out."""

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.dir = Path(self.tmp.name)
        self.saved = (showcase.discover_characters, showcase.discover_stages,
                      showcase.run_capture, showcase.EXPECTED_CHARACTERS,
                      showcase.EXPECTED_STAGES, showcase.EXPECTED_GAP_CELLS)

    def tearDown(self):
        (showcase.discover_characters, showcase.discover_stages, showcase.run_capture,
         showcase.EXPECTED_CHARACTERS, showcase.EXPECTED_STAGES,
         showcase.EXPECTED_GAP_CELLS) = self.saved
        self.tmp.cleanup()

    def set_claims(self, characters, stages, gap_cells):
        """Pin the sweep's coverage claim to the fake matrix under test."""
        showcase.EXPECTED_CHARACTERS = characters
        showcase.EXPECTED_STAGES = stages
        showcase.EXPECTED_GAP_CELLS = gap_cells

    def install_fake(self, chars, stages, result):
        showcase.discover_characters = lambda: list(chars)
        showcase.discover_stages = lambda: list(stages)
        showcase.run_capture = lambda *a, **k: result

    def test_empty_discovery_fails(self):
        self.install_fake([], [], (True, 10, 0, ""))
        self.assertFalse(showcase.check_matrix(self.dir))

    def test_shrunken_discovery_fails(self):
        # One character and one stage is not the claimed 16 x 13 coverage.
        self.install_fake(["rena"], ["stage01"], (True, 10, 0, ""))
        self.set_claims(16, 13, 0)
        self.assertFalse(showcase.check_matrix(self.dir))

    def test_unexpected_crash_fails_regardless_of_other_gaps(self):
        chars = ["rena", "kasai"]
        stages = ["stage05", "stage01"]
        self.install_fake(chars, stages, (True, 10, 4, ""))
        # Only rena x stage05 is a documented gap here; the crash on stage01 must fail the
        # sweep even though a tolerated cell exists alongside it.
        self.set_claims(2, 2, 1)
        showcase.run_capture = (lambda c, e, s, *a, **k:
                                (False, 0, 0, "segfault") if s == "stage01"
                                else (True, 10, 4, ""))
        self.assertFalse(showcase.check_matrix(self.dir))

    def test_a_passing_cell_is_never_reported_as_a_failure(self):
        # A regression in the classifier itself: an `else` that catches the passing case
        # would fail every clean sweep.
        self.install_fake(["rena"], ["stage01"], (True, 10, 0, ""))
        self.set_claims(1, 1, 0)
        self.assertTrue(showcase.check_matrix(self.dir))

    def test_clean_sweep_with_only_documented_gaps_passes(self):
        self.install_fake(["rena"], ["stage05"], (True, 10, 4, ""))
        self.set_claims(1, 1, 1)
        self.assertTrue(showcase.check_matrix(self.dir))


class ReleaseCheckTests(unittest.TestCase):
    """The release gate must tell a skip from a pass in CTest's own report."""

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.dir = Path(self.tmp.name)

    def tearDown(self):
        self.tmp.cleanup()

    def write_report(self, cases):
        path = self.dir / "report.xml"
        body = "".join(cases)
        path.write_text('<?xml version="1.0"?><testsuites><testsuite>' + body +
                        "</testsuite></testsuites>", encoding="utf-8")
        return str(path)

    def test_summarize_separates_executed_skipped_and_failed(self):
        path = self.write_report([
            '<testcase name="ran"/>',
            '<testcase name="skipped"><skipped/></testcase>',
            '<testcase name="broke"><failure message="boom"/></testcase>',
        ])
        executed, skipped, failed = release_check.summarize_junit(path)
        self.assertEqual(executed, ["ran"])
        self.assertEqual(skipped, ["skipped"])
        self.assertEqual(failed, ["broke"])

    def test_an_all_skipped_report_is_not_a_pass(self):
        path = self.write_report([
            '<testcase name="a"><skipped/></testcase>',
            '<testcase name="b"><skipped/></testcase>',
        ])
        executed, skipped, failed = release_check.summarize_junit(path)
        self.assertEqual(executed, [])
        self.assertEqual(len(skipped), 2)


class ReconTestExitCodeTests(unittest.TestCase):
    """A fully skipped recon run reports 77, never a pass."""

    def test_all_skipped_exits_77(self):
        script = TESTS / "ginkiha_recon_test.py"
        source = script.read_text(encoding="utf-8")
        # The mechanism, not a full run: the code path exists and returns 77 when nothing
        # ran. Running it for real is CTest's job (it needs the local bundle).
        self.assertIn("sys.exit(77)", source)
        self.assertIn("if ran == 0:", source)
        self.assertIn("SKIP_RETURN_CODE 77", (TESTS.parent / "CMakeLists.txt").read_text(
            encoding="utf-8"))


if __name__ == "__main__":
    unittest.main(verbosity=2)
