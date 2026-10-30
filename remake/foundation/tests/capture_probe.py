#!/usr/bin/env python3
"""Shared harness for the rendered-frame capture suites.

Why it exists: six suites ran the demo and mapped *every* non-success to a skip, so a
crash, a loader regression or a vanished marker became a green CTest run with exit 77.
The distinction the suites actually need is:

  * a missing **prerequisite** (no game data, no GPU adapter) is a SKIP — the suite
    cannot speak about a machine that has neither, and CI has neither;
  * everything else — a nonzero exit, a missing ``RESULT: ok``, a capture that is not a
    valid PPM, a hung process or a missing expected marker — is a FAILURE.

Prerequisite detection is deliberately narrow and explicit: ``<install>/data`` must
exist, and the demo's own no-adapter error (``RESULT: no usable GPU adapter``) is the
only output treated as "the renderer is unavailable". Any other nonzero exit is a
failure, which is what makes a loader regression visible.

Usage in a suite::

    from capture_probe import CaptureFailed, PrerequisiteMissing, main_guard, run_demo

    def main():
        ...                       # run_demo/read_ppm raise on real problems
        return 0

    if __name__ == "__main__":
        sys.exit(main_guard(main))

``main_guard`` prints the retained transcript for a failure and returns 1, or prints
the reason and returns 77 for a missing prerequisite.
"""
import os
import subprocess

SKIP = 77

# The only output that means "this machine has no renderer". The demo prints its error
# through `RESULT: <error>`, and gpu.cpp:144 is where this text is produced.
NO_ADAPTER_MARKER = "no usable GPU adapter"
OK_MARKER = "RESULT: ok"
# Enough of the child's output to diagnose a failure without flooding a CI log.
TRANSCRIPT_TAIL_LINES = 40


class PrerequisiteMissing(Exception):
    """A prerequisite this suite needs is absent: report exit 77, not a verdict."""


class CaptureFailed(Exception):
    """The demo or its capture did not do what the suite has a right to expect."""


def have_install(install):
    """True when the install directory carries game data the suites can load."""
    return bool(install) and os.path.isdir(os.path.join(install, "data"))


def require_install(install, suite):
    if not have_install(install):
        raise PrerequisiteMissing("%s: no game data at %s" % (suite, install))


def require_asset(path, suite, what):
    """Fail when an available install is missing an asset the suite needs.

    The install's presence is the prerequisite (require_install); a missing directory
    *inside* an available install means the asset set is incomplete, and treating that as
    "nothing to check" would hide exactly the regression the suite exists to catch.
    """
    if not os.path.isdir(path):
        raise CaptureFailed("%s: %s missing at %s — the install is present but incomplete"
                            % (suite, what, path))


def transcript_tail(text, lines=TRANSCRIPT_TAIL_LINES):
    tail = (text or "").strip().splitlines()
    return "\n".join(tail[-lines:])


def run_demo(demo, install, out, args, cwd=None, timeout=900):
    """Run one headless capture, returning its merged transcript.

    Raises PrerequisiteMissing when the demo reports no usable GPU adapter, and
    CaptureFailed for a timeout, a nonzero exit or a missing `RESULT: ok`. A hang is a
    failure: a suite that waits forever must not look like a clean skip.
    """
    cmd = [demo, "--headless"]
    cmd += ["--install=" + install, "--out=" + out] + list(args)
    try:
        proc = subprocess.run(cmd, cwd=cwd, stdout=subprocess.PIPE,
                              stderr=subprocess.STDOUT, text=True,
                              encoding="utf-8", errors="replace", timeout=timeout)
    except subprocess.TimeoutExpired as exc:
        raise CaptureFailed("timed out after %ss: %s" % (timeout, " ".join(cmd))) from exc
    text = proc.stdout or ""
    if NO_ADAPTER_MARKER in text:
        raise PrerequisiteMissing("no usable GPU adapter (headless renderer unavailable)")
    if proc.returncode != 0 and OK_MARKER not in text:
        raise CaptureFailed("exit %d from %s\n%s"
                            % (proc.returncode, " ".join(cmd), transcript_tail(text)))
    if OK_MARKER not in text:
        raise CaptureFailed("no `%s` in the output of %s\n%s"
                            % (OK_MARKER, " ".join(cmd), transcript_tail(text)))
    if proc.returncode != 0:
        # `RESULT: ok` with a nonzero exit is contradictory: the process is telling us
        # two different things, so neither can be trusted.
        raise CaptureFailed("exit %d despite `%s` from %s"
                            % (proc.returncode, OK_MARKER, " ".join(cmd)))
    return text


def read_ppm(path):
    """Parse a binary PPM. Raises CaptureFailed when the file is absent or malformed."""
    suite = os.path.basename(path)
    try:
        with open(path, "rb") as handle:
            data = handle.read()
    except OSError as exc:
        raise CaptureFailed("no capture at %s (%s)" % (path, exc)) from exc
    if not data.startswith(b"P6"):
        raise CaptureFailed("%s is not a binary PPM (starts %r)" % (path, data[:8]))
    fields = []
    i = 2
    while len(fields) < 3:
        while i < len(data) and data[i:i + 1].isspace():
            i += 1
        if i >= len(data):
            raise CaptureFailed("%s: truncated PPM header" % path)
        if data[i:i + 1] == b"#":
            while i < len(data) and data[i:i + 1] not in (b"\n", b""):
                i += 1
            continue
        start = i
        while i < len(data) and not data[i:i + 1].isspace():
            i += 1
        try:
            fields.append(int(data[start:i]))
        except ValueError as exc:
            raise CaptureFailed("%s: bad PPM header field %r"
                                % (path, data[start:i])) from exc
    i += 1
    w, h, maxval = fields
    if w <= 0 or h <= 0 or maxval != 255:
        raise CaptureFailed("%s: unusable PPM geometry %dx%d maxval %d"
                            % (path, w, h, maxval))
    expected = w * h * 3
    pixels = data[i:i + expected]
    if len(pixels) != expected:
        raise CaptureFailed("%s: PPM payload is %d bytes, expected %d for %dx%d"
                            % (suite, len(pixels), expected, w, h))
    return w, h, pixels


def require_markers(name, markers, suite):
    """Fail when an expected marker set is empty.

    Markers that stop appearing are exactly what a capture suite is for: the old code
    treated an empty set as "nothing to measure" and skipped.
    """
    if not markers:
        raise CaptureFailed("%s: no %s in the frame — the probe did not draw what the "
                            "suite measures" % (suite, name))
    return markers


def main_guard(body):
    """Run a suite body, mapping prerequisites to 77 and real problems to 1."""
    try:
        return body()
    except PrerequisiteMissing as exc:
        print("SKIP: %s" % exc)
        return SKIP
    except CaptureFailed as exc:
        print("FAIL: %s" % exc)
        return 1
