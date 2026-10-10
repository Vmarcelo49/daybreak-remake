#!/usr/bin/env python3
"""Guard request counting, exact selection and refusal of stale recon inputs."""
from pathlib import Path
import sys
import tempfile
import unittest

TOOLS = Path(__file__).resolve().parents[1] / "tools"
sys.path.insert(0, str(TOOLS))
import ginkiha_recon as recon


class ReconUnitTests(unittest.TestCase):
    def test_counts_every_request_and_attachment_row_operand(self):
        frames = [{"frame": 20, "events": [["fire_attachment", 0, 2, 0, 0]] +
                  [["fire_attachment", 0, 0, 0, 0]] * 20},
                  {"frame": 19, "events": [["fire_world", 7, 1, 2, 3, 4, 5],
                                              ["fire_hand", 3, 0, 0], ["voice", 27]]}]
        result = recon.summarize_frames(frames)
        self.assertEqual(result["requests"], 23)
        self.assertEqual(result["first_frame"], 20)
        self.assertEqual(result["rows"], {"0": 20, "2": 1, "3": 1, "7": 1})
        self.assertEqual(result["origins"], {"attachment": 21, "hand": 1, "world": 1})
        self.assertIsNone(recon.summarize_frames([])["first_frame"])

    def test_body_ranges_do_not_bleed_into_neighbor(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "bodies.hpp"
            path.write_text("inline void shoot_body_3_2_400(C& n)\n{\n if (true) { n.FUN_00435450(0); }\n}\n\n"
                            "inline void shoot_body_3_2_402(C& n)\n{\n n.FUN_00435220(0);\n}\n")
            bodies = recon.body_index(path)
            self.assertEqual(bodies[(3, 2, 400)]["last_line"], 4)
            self.assertEqual(bodies[(3, 2, 400)]["helpers"], ["FUN_00435450"])
            self.assertEqual(bodies[(3, 2, 402)]["first_line"], 6)

    def test_unknown_runtime_syntax_is_not_reported_as_unbound(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "move_behavior.h"
            path.write_text("static constexpr MoveProgram changed = make_program();")
            with self.assertRaisesRegex(ValueError, "syntax changed"):
                recon.runtime_bindings(path)


@unittest.skipUnless(Path(recon.DEFAULT_SUPPORT).is_dir() and Path(recon.DEFAULT_REFERENCE).is_dir(),
                     "local Ginkiha bundles unavailable")
class BundleReconTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.runtime = recon.REPO / "remake/foundation/src/gameplay/move_behavior.h"
        cls.inventory = recon.Recon(Path(recon.DEFAULT_SUPPORT), Path(recon.DEFAULT_REFERENCE), cls.runtime)

    def test_roster_exact_selection_and_all_request_origins(self):
        self.assertEqual(len(self.inventory.roster), 46)
        satoko = self.inventory.combo(3, 2)
        self.assertEqual((satoko["swap"], satoko["item_id"]), (12, 38))
        for trace in satoko["extended_requests"].values():
            self.assertEqual(len(trace), 6)
            for summary in trace.values():
                self.assertEqual(summary["origins"], {"world": 2})
                self.assertEqual(summary["first_frame"], 20)
        self.assertEqual(self.inventory.combo(3, 1)["usage"], {})
        kasai = self.inventory.combo(12, 0)
        self.assertEqual(kasai["preview_requests"]["12:0:normal:0"]["requests"], 21)
        self.assertEqual(kasai["preview_requests"]["12:0:tag:0"]["requests"], 31)
        self.assertEqual(self.inventory.combo(0, 1)["bodies"], {})
        with self.assertRaisesRegex(ValueError, "unknown character"):
            self.inventory.combo(14, 2)

    def test_wrong_combo_runtime_handler_is_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            runtime = Path(directory) / "move_behavior.h"
            runtime.write_text(self.runtime.read_text().replace("{3,2,0x4bc040,", "{3,2,0xdeadbe,"))
            with self.assertRaisesRegex(ValueError, "handler mismatch"):
                recon.Recon(Path(recon.DEFAULT_SUPPORT), Path(recon.DEFAULT_REFERENCE), runtime)

    def test_hash_drift_is_rejected_before_report(self):
        with tempfile.TemporaryDirectory() as directory:
            support = Path(directory)
            (support / "catalogs").mkdir()
            (support / "SHA256SUMS.txt").write_bytes((Path(recon.DEFAULT_SUPPORT) / "SHA256SUMS.txt").read_bytes())
            (support / "catalogs/combat-hooks.json").write_text("{}")
            with self.assertRaisesRegex(ValueError, "bundle hash mismatch"):
                recon.Recon(support, Path(recon.DEFAULT_REFERENCE), self.runtime)


if __name__ == "__main__":
    unittest.main()
