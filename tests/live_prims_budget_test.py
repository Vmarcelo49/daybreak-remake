#!/usr/bin/env python3
"""Pin that every frame which draws `render::DebugPrims` passes opens its pass budget.

Issue #108: a live match with Hanyuu's time stop ended with `RESULT: debug prims frame
overran its 16 per-pass slots`. `DebugPrims` numbers its passes with `pass_`, one vertex
region and one uniform slot each, because a frame records several passes into one command
buffer and submits once (issue #61). `beginFrame()` is what resets that counter for the
next frame; a pass past the budget fails instead of aliasing into another pass's region.
The capture hook calls it once per captured frame (`render_capture.inc`), but the live
render loop never did (`frame_loop.inc`), so the counter kept rising across frames. In
normal play the only live prims pass is the time-stop negative, gated by
`Battle::time_stop_active()` — so Hanyuu's stop drew 16 inverted frames and the 17th made
`drawBatch` fail, which ends the game through `SDL_APP_FAILURE`. One view (online) aborts
after 16 frames, a two-view split after 8, four views after 4.

Why this is a source guard and not a rendered one: the live loop needs a window and a
swapchain, and every render test in this repository renders through `--out`, which takes
the capture path and therefore calls `beginFrame()` every frame. A capture can never see
this defect; there is no headless live harness to hang a pixel verdict on. The behavioural
check, for a machine with a display, is a *bounded live* run — `--match` WITHOUT `--out`:
with the budget reset missing it exits with the error above at the 17th time-stop frame,
and with it the run reaches `--frames` and exits 0. This file instead pins the structure
that makes that true, and the fixtures below prove it fails on the pre-fix tree.

The invariant, per file that issues a prims pass: it must call `beginFrame()` (per-file
rule), once per frame, before the first pass and outside the per-view loop (live-block
rule), and the capture hook keeps its own once-per-captured-frame call.

Run directly (`python3 tests/live_prims_budget_test.py`) or through CTest
(`ctest -R live_prims_budget_test`). Needs no game data, no GPU and no build output.
"""
import re
import shutil
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

# One pass as a caller writes it. The receiver names are the app's two: `app->debugPrims`
# in the frame loop and `ck->prims` in the capture hook. `DebugPrims::invertView` (the
# definition) has no `->`/`.` receiver, so the renderer's own file is not a call site.
PASS_RE = re.compile(r"(?:prims\s*->|debugPrims\s*\.)\s*(?:invertView|drawCubes|draw)\s*\(")
RESET_RE = re.compile(r"(?:prims\s*->|debugPrims\s*\.)\s*beginFrame\s*\(\s*\)")

# The frame loop's two uses of the shared condition: the capture block that only fills the
# hook, and the live block that actually records passes. The last one is the live frame.
PRIMS_BLOCK_RE = re.compile(r"if\s*\(\s*app\s*->\s*opts\s*\.\s*debugPrims\s*\|\|\s*"
                            r"app\s*->\s*matchMode\s*\)")
LIVE_FRAME_RE = re.compile(r"gpu::beginFrame\s*\(\s*app\s*->\s*ctx\s*,\s*app\s*->\s*sc")
VIEW_LOOP_RE = re.compile(r"for\s*\(\s*const\s+render::ViewCamera\s*&\s*camera\s*:\s*"
                          r"frameCameras\s*\)")
CAPTURE_HOOK_RE = re.compile(r"bool\s+captureHook\s*\(")
CAPTURE_VIEW_LOOP_RE = re.compile(r"for\s*\(\s*const\s+render::ViewCamera\s*&\s*frameView\s*:\s*"
                                  r"ck\s*->\s*views\s*\)")


def read(path):
    return path.read_text(encoding="utf-8", errors="replace")


def blank_literals(text):
    """`text` with comment bodies and string/char literals replaced by spaces.

    Same length, same newlines: an index in the result is an index in the input and a line
    number is `text.count("\\n", 0, index) + 1`. This keeps braces inside a message out of
    the brace matching without moving the call sites the report names.
    """
    out = list(text)
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == "/" and i + 1 < n and text[i + 1] == "/":
            j = text.find("\n", i)
            j = n if j < 0 else j
            for k in range(i, j):
                out[k] = " "
            i = j
        elif c == "/" and i + 1 < n and text[i + 1] == "*":
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
            for k in range(i, j):
                if out[k] != "\n":
                    out[k] = " "
            i = j
        elif c in "\"'":
            quote, j = c, i + 1
            while j < n:
                if text[j] == "\\":
                    j += 2
                    continue
                if text[j] == quote or text[j] == "\n":
                    break
                j += 1
            for k in range(i + 1, min(j, n)):
                if out[k] != "\n":
                    out[k] = " "
            i = j + 1
        else:
            i += 1
    return "".join(out)


def line_of(text, index):
    return text.count("\n", 0, index) + 1


def block_end(blank, start):
    """(open, close) of the first `{...}` at or after `start`, or None."""
    open_at = blank.find("{", start)
    if open_at < 0:
        return None
    depth = 0
    for i in range(open_at, len(blank)):
        if blank[i] == "{":
            depth += 1
        elif blank[i] == "}":
            depth -= 1
            if depth == 0:
                return open_at, i
    return None


def check_file_rule(blank, problems, name):
    """Every file that records a pass must also open the frame's budget."""
    if PASS_RE.search(blank) and not RESET_RE.search(blank):
        problems.append(
            "%s records debug-prims passes but never calls beginFrame(): the budget is "
            "per process, so a later frame overruns it (issue #108)" % name)


def check_live_block(text, blank, problems):
    blocks = [m for m in PRIMS_BLOCK_RE.finditer(blank)]
    if len(blocks) != 2:
        problems.append(
            "src/app/frame_loop.inc has %d `if (app->opts.debugPrims || app->matchMode)` "
            "blocks; this guard knows the capture setup and the live frame (2). Update it "
            "with the new shape" % len(blocks))
        return
    live = blocks[-1]
    body = block_end(blank, live.start())
    if body is None:
        problems.append("src/app/frame_loop.inc: the live debug-prims block has no body")
        return
    open_at, close_at = body
    passes = [m.start() for m in PASS_RE.finditer(blank, open_at, close_at)]
    if not passes:
        problems.append(
            "src/app/frame_loop.inc: the live debug-prims block records no pass any more; "
            "this guard no longer covers the live path — update it to follow the passes")
        return
    # The reset may sit just outside the block (right after gpu::beginFrame) as long as it
    # is in the same frame and before the block's first pass.
    frames = [m.start() for m in LIVE_FRAME_RE.finditer(blank, 0, live.start())]
    region_start = frames[-1] if frames else live.start()
    resets = [m.start() for m in RESET_RE.finditer(blank, region_start, close_at)]
    if len(resets) != 1:
        if not resets:
            problems.append(
                "src/app/frame_loop.inc:%d: the live render path never calls "
                "debugPrims.beginFrame(). The pass budget is per process, so the time "
                "stop's negative (issue #108) exhausts it and the game exits with "
                "\"debug prims frame overran its 16 per-pass slots\""
                % line_of(text, live.start()))
        else:
            problems.append(
                "src/app/frame_loop.inc:%d: the live render path calls beginFrame() %d "
                "times per frame; it must open the budget exactly once"
                % (line_of(text, live.start()), len(resets)))
        return
    reset = resets[0]
    first_pass = passes[0]
    if reset > first_pass:
        problems.append(
            "src/app/frame_loop.inc:%d: beginFrame() comes after the frame's first pass "
            "at line %d; the budget must be opened before every pass of the frame"
            % (line_of(text, reset), line_of(text, first_pass)))
    loops = [m.start() for m in VIEW_LOOP_RE.finditer(blank, open_at, close_at)]
    if not loops:
        problems.append(
            "src/app/frame_loop.inc: the live block has no per-view "
            "`for (const render::ViewCamera& camera : frameCameras)` loop; update this guard")
    elif reset > loops[0]:
        problems.append(
            "src/app/frame_loop.inc:%d: beginFrame() is inside the per-view loop at line "
            "%d; one reset per frame, not one per view (per-view slots are issue #61's "
            "aliasing)" % (line_of(text, reset), line_of(text, loops[0])))


def check_capture_hook(text, blank, problems):
    hook = CAPTURE_HOOK_RE.search(blank)
    if not hook:
        problems.append("src/app/render_capture.inc: captureHook not found; update this guard")
        return
    body = block_end(blank, hook.end())
    if body is None:
        problems.append("src/app/render_capture.inc: captureHook has no body")
        return
    open_at, close_at = body
    passes = [m.start() for m in PASS_RE.finditer(blank, open_at, close_at)]
    resets = [m.start() for m in RESET_RE.finditer(blank, open_at, close_at)]
    if not passes:
        problems.append(
            "src/app/render_capture.inc: captureHook records no debug-prims pass; update "
            "this guard")
        return
    if len(resets) != 1:
        problems.append(
            "src/app/render_capture.inc:%d: captureHook must open the captured frame's "
            "budget exactly once (found %d)"
            % (line_of(text, hook.start()), len(resets)))
        return
    reset = resets[0]
    if reset > passes[0]:
        problems.append(
            "src/app/render_capture.inc:%d: beginFrame() comes after the first captured "
            "pass at line %d" % (line_of(text, reset), line_of(text, passes[0])))
    loops = [m.start() for m in CAPTURE_VIEW_LOOP_RE.finditer(blank, open_at, close_at)]
    if not loops:
        problems.append(
            "src/app/render_capture.inc: captureHook has no per-view loop; update this guard")
    elif reset > loops[0]:
        problems.append(
            "src/app/render_capture.inc:%d: beginFrame() is inside captureHook's per-view "
            "loop at line %d; one reset per captured frame"
            % (line_of(text, reset), line_of(text, loops[0])))


def check_tree(root):
    """Every violation in `root`'s app sources, as human-readable lines."""
    problems = []
    frame_loop_path = root / "src" / "app" / "frame_loop.inc"
    capture_path = root / "src" / "app" / "render_capture.inc"
    frame_text = read(frame_loop_path)
    capture_text = read(capture_path)
    frame_blank = blank_literals(frame_text)
    capture_blank = blank_literals(capture_text)
    check_live_block(frame_text, frame_blank, problems)
    check_capture_hook(capture_text, capture_blank, problems)
    for path in sorted((root / "src").rglob("*")):
        if path.suffix not in (".cpp", ".inc", ".hpp", ".h"):
            continue
        # The renderer's own file defines these entry points; it is not a caller.
        if path.name.startswith("debug_prims."):
            continue
        check_file_rule(blank_literals(read(path)), problems,
                        path.relative_to(root).as_posix())
    return problems


class LivePrimsBudgetTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.root = Path(self.tmp.name)
        # Only the app's compositors: that is where the guard's new-file case lives, and
        # the checkout's own tree is what the real-tree test scans.
        shutil.copytree(ROOT / "src" / "app", self.root / "src" / "app")

    def tearDown(self):
        self.tmp.cleanup()

    def location(self, relative, block_of):
        """(path, text, blank, open_at, close_at) for the first brace block of a marker."""
        path = self.root / relative
        text = read(path)
        blank = blank_literals(text)
        marker = block_of.search(blank)
        self.assertIsNotNone(marker, "fixture precondition: %s not found" % relative)
        body = block_end(blank, marker.start())
        self.assertIsNotNone(body, "fixture precondition: %s has no body" % relative)
        return path, text, blank, body[0], body[1]

    def delete(self, path, blank, start, end):
        text = read(path)
        path.write_text(text[:start] + text[end:], encoding="utf-8")

    def live_reset(self):
        """(path, text, blank, open, close, reset_match) for the live frame's reset."""
        path = self.root / "src" / "app" / "frame_loop.inc"
        text = read(path)
        blank = blank_literals(text)
        blocks = list(PRIMS_BLOCK_RE.finditer(blank))
        self.assertEqual(len(blocks), 2, "fixture precondition: two prims blocks")
        body = block_end(blank, blocks[-1].start())
        self.assertIsNotNone(body, "fixture precondition: the live block has no body")
        open_at, close_at = body
        frames = [m.start() for m in LIVE_FRAME_RE.finditer(blank, 0, blocks[-1].start())]
        start = frames[-1] if frames else open_at
        reset = RESET_RE.search(blank, start, close_at)
        self.assertIsNotNone(reset, "fixture precondition: the live path has no reset")
        return path, text, blank, open_at, close_at, reset

    def problems(self):
        return check_tree(self.root)

    def test_the_real_tree_opens_every_frame_budget(self):
        self.assertEqual(check_tree(ROOT), [])

    def test_a_live_path_without_the_reset_is_the_issue_108_regression(self):
        path, _, blank, _, _, reset = self.live_reset()
        self.delete(path, blank, reset.start(), reset.end())
        problems = self.problems()
        self.assertTrue(any("never calls debugPrims.beginFrame" in p for p in problems),
                        "expected the missing live reset to be named, got %r" % problems)
        self.assertTrue(any("frame_loop.inc records debug-prims passes" in p for p in problems),
                        "expected the per-file rule to name frame_loop.inc, got %r" % problems)

    def test_a_reset_inside_the_view_loop_is_not_enough(self):
        path, _, blank, _, _, reset = self.live_reset()
        self.delete(path, blank, reset.start(), reset.end())
        text = read(path)
        blank = blank_literals(text)
        blocks = list(PRIMS_BLOCK_RE.finditer(blank))
        open_at, close_at = block_end(blank, blocks[-1].start())
        loop = VIEW_LOOP_RE.search(blank, open_at, close_at)
        self.assertIsNotNone(loop, "fixture precondition: no per-view loop")
        brace = blank.find("{", loop.end())
        self.assertGreater(brace, 0, "fixture precondition: the loop has no body")
        path.write_text(text[:brace + 1] + "\n                app->debugPrims.beginFrame();" +
                        text[brace + 1:], encoding="utf-8")
        problems = self.problems()
        self.assertTrue(any("inside the per-view loop" in p for p in problems),
                        "expected a per-view reset to be refused, got %r" % problems)

    def test_the_capture_hook_keeps_its_own_reset(self):
        path, _, blank, open_at, close_at = self.location("src/app/render_capture.inc",
                                                          CAPTURE_HOOK_RE)
        reset = RESET_RE.search(blank, open_at, close_at)
        self.assertIsNotNone(reset, "fixture precondition: captureHook has no reset")
        self.delete(path, blank, reset.start(), reset.end())
        problems = self.problems()
        self.assertTrue(any("captureHook must open" in p for p in problems),
                        "expected the capture hook's missing reset to be named, got %r" % problems)

    def test_a_new_compositor_with_a_pass_and_no_reset_is_named(self):
        (self.root / "src" / "app" / "extra.inc").write_text(
            "void drawExtra(App& app) {\n"
            "    app->debugPrims.invertView(target, rect, error);\n"
            "}\n", encoding="utf-8")
        problems = self.problems()
        self.assertTrue(any("src/app/extra.inc records debug-prims passes" in p for p in problems),
                        "expected the per-file rule to name the new compositor, got %r" %
                        problems)


if __name__ == "__main__":
    if not (ROOT / "src" / "app" / "frame_loop.inc").exists():
        sys.exit("live_prims_budget_test: run from a checkout (src/app/frame_loop.inc missing)")
    unittest.main(verbosity=2)
