#!/usr/bin/env python3
"""Write and check `package-manifest.txt`, the file list a release package owns (issue #100).

Players extract a package into their game folder, next to the copyrighted data, so the
updater may replace only files the package itself owns. This manifest is that list: one
line per shipped file, with the hash, size and mode the updater checks before it applies
anything. `scripts/package_linux.sh` and `scripts/package_windows.sh` generate it, and the
same `check` validates the staged tree so a package that passes here is the package the
updater accepts.

    python3 -I tools/package_manifest.py write <stage-dir> \\
        --version=<X.Y.Z> --target=<linux-x86_64|windows-x86_64> --launch=<path>
    python3 -I tools/package_manifest.py check <stage-dir>

The format is specified in docs/AUTO-UPDATE.md. Stdlib only, and `-I` (isolated mode) is
part of the contract: nothing here may depend on the caller's environment.
"""

import argparse
import hashlib
import os
import re
import stat
import sys
from dataclasses import dataclass
from pathlib import Path

MANIFEST_NAME = "package-manifest.txt"
FORMAT = 1
TARGETS = ("linux-x86_64", "windows-x86_64")

_ENTRY_RE = re.compile(r"^([0-9a-f]{64})  ([0-9]+)  ([x-])  (.+)$")
_VERSION_RE = re.compile(r"^[0-9A-Za-z][0-9A-Za-z.+~-]*$")
_DRIVE_RE = re.compile(r"^[A-Za-z]:")
# NTFS rules. A manifest drives updates on both platforms and a layout change may move
# files between them, so a path that only works on Linux is refused for both targets.
_WINDOWS_FORBIDDEN = set('<>:"|?*')
_RESERVED_NAMES = frozenset(
    ["con", "prn", "aux", "nul"]
    + ["com%d" % number for number in range(1, 10)]
    + ["lpt%d" % number for number in range(1, 10)]
)


class ManifestError(Exception):
    """A staged package, a manifest or an archive that does not follow the format."""


@dataclass(frozen=True)
class Entry:
    path: str
    sha256: str
    size: int
    mode: str  # "x" (must be executable) or "-"


@dataclass(frozen=True)
class Manifest:
    version: str
    target: str
    launch: str
    entries: tuple


def check_version(version):
    """A version is one token: no spaces, newlines or '=' that would break the line."""
    if not _VERSION_RE.match(version):
        raise ManifestError(
            "version %r must be a token like 1.2.3 (letters, digits, '.', '+', '~', '-')"
            % (version,)
        )


def check_relative_path(path, where="path"):
    """Reject anything the updater must never write outside the package root.

    The rules are shared by the manifest and by the archive readers
    (`tools/make_update_manifest.py`), so a path accepted in one place is accepted in
    both and no archive can smuggle in a traversal the manifest would not list.
    """
    if not path:
        raise ManifestError("%s: empty path" % where)
    if path != path.strip():
        raise ManifestError("%s: %r starts or ends with whitespace" % (where, path))
    for char in path:
        if ord(char) < 0x20 or ord(char) == 0x7F:
            raise ManifestError("%s: %r contains a control character" % (where, path))
    if "\\" in path:
        raise ManifestError("%s: %r contains a backslash; paths use '/'" % (where, path))
    if path.startswith("/"):
        raise ManifestError("%s: %r is an absolute path" % (where, path))
    if _DRIVE_RE.match(path):
        raise ManifestError("%s: %r starts with a drive letter" % (where, path))
    components = path.split("/")
    if any(part in ("", ".", "..") for part in components):
        raise ManifestError(
            "%s: %r has an empty, '.' or '..' path component" % (where, path)
        )
    forbidden = sorted(set(path) & _WINDOWS_FORBIDDEN)
    if forbidden:
        raise ManifestError(
            "%s: %r contains %s, which NTFS does not allow"
            % (where, path, " ".join(repr(char) for char in forbidden))
        )
    for component in components:
        if component.endswith((".", " ")):
            raise ManifestError(
                "%s: %r has a component ending in '.' or a space, which Windows "
                "silently drops" % (where, path)
            )
        # "CON", "con.txt" and "aux.tar.gz" all name a device on Windows.
        stem = component.split(".")[0]
        if stem.lower() in _RESERVED_NAMES:
            raise ManifestError(
                "%s: %r has the Windows device name %r" % (where, path, stem)
            )
    try:
        path.encode("utf-8")
    except UnicodeEncodeError:
        raise ManifestError("%s: %r is not valid UTF-8" % (where, path))


def check_entry_paths(paths, where="files"):
    """Cross-entry rules a single path cannot see: case collisions and file/dir clashes.

    Both platforms end up holding these paths, and NTFS is case-insensitive: two entries
    that differ only in case would overwrite each other, and a file `a` beside `a/b` is
    not representable at all.
    """
    seen = {}
    for path in paths:
        folded = path.casefold()
        if folded in seen:
            raise ManifestError(
                "%s: %r and %r differ only in case" % (where, path, seen[folded])
            )
        seen[folded] = path
    files = set(paths)
    for path in paths:
        parts = path.split("/")
        for index in range(1, len(parts)):
            prefix = "/".join(parts[:index])
            if prefix in files:
                raise ManifestError(
                    "%s: %r is a file and also a directory of %r"
                    % (where, prefix, path)
                )


def hash_file(path):
    digest = hashlib.sha256()
    with open(path, "rb") as handle:
        for chunk in iter(lambda: handle.read(1 << 20), b""):
            digest.update(chunk)
    return digest.hexdigest()


def scan_stage(stage):
    """Every regular file in the stage, as (relative path, lstat), sorted bytewise.

    Directories are implied by their files, so they are not returned; a symlink,
    device, fifo or socket is refused rather than skipped, because a package that
    silently omits one would fail the updater's own check later.
    """
    stage = Path(stage)
    if not stage.is_dir():
        raise ManifestError("%s: not a directory" % stage)

    found = []

    def walk(directory, prefix):
        try:
            entries = list(os.scandir(directory))
        except OSError as error:
            raise ManifestError("%s: cannot read directory: %s" % (directory, error))
        for entry in entries:
            relative = prefix + entry.name if not prefix else prefix + "/" + entry.name
            try:
                info = entry.stat(follow_symlinks=False)
            except OSError as error:
                raise ManifestError("%s: cannot stat: %s" % (relative, error))
            if stat.S_ISLNK(info.st_mode):
                raise ManifestError(
                    "%s: symlinks are not allowed in a package" % relative
                )
            if stat.S_ISDIR(info.st_mode):
                walk(Path(entry.path), relative)
            elif stat.S_ISREG(info.st_mode):
                # The manifest describes the package; it is not part of it.
                if relative == MANIFEST_NAME:
                    continue
                found.append((relative, info))
            else:
                raise ManifestError(
                    "%s: not a regular file (device, fifo or socket)" % relative
                )

    walk(stage, "")
    found.sort(key=lambda item: item[0].encode("utf-8"))
    return found


def entry_mode(target, info):
    """'x' when the file must be executable: the staged exec bit on Linux, never on Windows."""
    if target == "linux-x86_64" and (info.st_mode & 0o111):
        return "x"
    return "-"


def build_manifest(stage, version, target, launch):
    """Render the manifest text for a staged package; does not write it."""
    check_version(version)
    if target not in TARGETS:
        raise ManifestError(
            "target %r must be one of %s" % (target, ", ".join(TARGETS))
        )
    check_relative_path(launch, "launch")

    entries = []
    for relative, info in scan_stage(stage):
        check_relative_path(relative, "file")
        entries.append(
            Entry(relative, hash_file(Path(stage) / relative), info.st_size,
                  entry_mode(target, info))
        )

    check_entry_paths([entry.path for entry in entries])
    by_path = {entry.path: entry for entry in entries}
    if launch not in by_path:
        raise ManifestError(
            "launch %r is not one of the package's files; it must name a shipped file"
            % launch
        )
    if target == "linux-x86_64" and by_path[launch].mode != "x":
        raise ManifestError(
            "launch %r is not executable in the staged package" % launch
        )

    lines = [
        "format = %d" % FORMAT,
        "version = %s" % version,
        "target = %s" % target,
        "launch = %s" % launch,
        "[files]",
    ]
    lines.extend(
        "%s  %d  %s  %s" % (entry.sha256, entry.size, entry.mode, entry.path)
        for entry in entries
    )
    return "\n".join(lines) + "\n"


def parse_manifest(text):
    """Parse and validate a manifest. Strict on purpose: this file is a contract."""
    if "\r" in text:
        raise ManifestError("the manifest uses CRLF; it must use LF line endings")
    if not text.endswith("\n"):
        raise ManifestError("the manifest must end with a newline")
    lines = text.split("\n")[:-1]
    if len(lines) < 5:
        raise ManifestError("the manifest is truncated: fewer than five header lines")

    format_match = re.match(r"^format = ([0-9]+)$", lines[0])
    if not format_match:
        raise ManifestError("line 1 must be 'format = %d'" % FORMAT)
    if int(format_match.group(1)) != FORMAT:
        raise ManifestError(
            "the manifest has format %s, which this tool does not understand"
            % format_match.group(1)
        )

    header = {}
    for index, key in enumerate(("version", "target", "launch")):
        line = lines[1 + index]
        prefix = "%s = " % key
        if not line.startswith(prefix):
            raise ManifestError("line %d must be '%s<value>'" % (index + 2, prefix))
        value = line[len(prefix):]
        if not value:
            raise ManifestError("line %d: empty %s" % (index + 2, key))
        if value != value.strip():
            raise ManifestError("line %d: %s has surrounding whitespace" % (index + 2, key))
        header[key] = value

    check_version(header["version"])
    if header["target"] not in TARGETS:
        raise ManifestError(
            "target %r must be one of %s"
            % (header["target"], ", ".join(TARGETS))
        )
    check_relative_path(header["launch"], "launch")

    if lines[4] != "[files]":
        raise ManifestError("line 5 must be '[files]'")

    entries = []
    seen = set()
    for number, line in enumerate(lines[5:], start=6):
        if not line:
            raise ManifestError("line %d: blank line" % number)
        match = _ENTRY_RE.match(line)
        if not match:
            raise ManifestError(
                "line %d: not '<sha256>  <size>  <mode>  <path>' "
                "(two spaces between fields)" % number
            )
        sha256, size_text, mode, path = match.groups()
        check_relative_path(path, "line %d" % number)
        if path == MANIFEST_NAME:
            raise ManifestError("line %d: the manifest must not list itself" % number)
        if path in seen:
            raise ManifestError("line %d: %r is listed twice" % (number, path))
        if str(int(size_text)) != size_text:
            raise ManifestError("line %d: size %r is not canonical" % (number, size_text))
        if header["target"] == "windows-x86_64" and mode == "x":
            raise ManifestError(
                "line %d: a windows-x86_64 manifest uses '-' for every file" % number
            )
        seen.add(path)
        entries.append(Entry(path, sha256, int(size_text), mode))

    if not entries:
        raise ManifestError("the manifest lists no files")
    check_entry_paths([entry.path for entry in entries])
    if [entry.path for entry in entries] != sorted(
        (entry.path for entry in entries), key=lambda path: path.encode("utf-8")
    ):
        raise ManifestError("entries must be sorted bytewise by path")
    by_path = {entry.path: entry for entry in entries}
    if header["launch"] not in by_path:
        raise ManifestError("launch %r is not listed" % header["launch"])
    if header["target"] == "linux-x86_64" and by_path[header["launch"]].mode != "x":
        raise ManifestError("launch %r must have mode 'x'" % header["launch"])

    return Manifest(header["version"], header["target"], header["launch"], tuple(entries))


def read_manifest(stage):
    path = Path(stage) / MANIFEST_NAME
    if not path.is_file():
        raise ManifestError("%s: missing" % path)
    try:
        return parse_manifest(path.read_bytes().decode("utf-8"))
    except UnicodeDecodeError:
        raise ManifestError("%s: not valid UTF-8" % path)


def check_stage(stage):
    """Verify a staged package against its own manifest; returns the parsed manifest."""
    manifest = read_manifest(stage)
    listed = {entry.path: entry for entry in manifest.entries}

    actual = {}
    for relative, info in scan_stage(stage):
        check_relative_path(relative, "file")
        actual[relative] = (info.st_size, entry_mode(manifest.target, info))

    missing = sorted(set(listed) - set(actual))
    if missing:
        raise ManifestError(
            "%d file(s) listed but missing, e.g. %s" % (len(missing), missing[0])
        )
    extra = sorted(set(actual) - set(listed))
    if extra:
        raise ManifestError(
            "%d file(s) in the stage are not listed, e.g. %s" % (len(extra), extra[0])
        )

    for path in sorted(listed, key=lambda path: path.encode("utf-8")):
        entry = listed[path]
        size, mode = actual[path]
        if size != entry.size:
            raise ManifestError(
                "%s: size is %d, the manifest says %d" % (path, size, entry.size)
            )
        if mode != entry.mode:
            raise ManifestError(
                "%s: mode is %r, the manifest says %r (exec bit changed?)"
                % (path, mode, entry.mode)
            )
        digest = hash_file(Path(stage) / path)
        if digest != entry.sha256:
            raise ManifestError(
                "%s: sha256 is %s, the manifest says %s" % (path, digest, entry.sha256)
            )
    return manifest


def main(argv):
    parser = argparse.ArgumentParser(
        prog="package_manifest.py",
        description="Write and check package-manifest.txt (docs/AUTO-UPDATE.md).",
    )
    commands = parser.add_subparsers(dest="command", required=True)

    write = commands.add_parser(
        "write", help="write package-manifest.txt into a staged package"
    )
    write.add_argument("stage", help="the staged package root")
    write.add_argument("--version", required=True, help="the package's VERSION")
    write.add_argument("--target", required=True, choices=TARGETS)
    write.add_argument("--launch", required=True, help="the package's entry point")

    check = commands.add_parser(
        "check", help="verify a staged package against its package-manifest.txt"
    )
    check.add_argument("stage", help="the staged package root")

    args = parser.parse_args(argv)
    try:
        if args.command == "write":
            text = build_manifest(args.stage, args.version, args.target, args.launch)
            path = Path(args.stage) / MANIFEST_NAME
            with open(path, "w", encoding="utf-8", newline="\n") as handle:
                handle.write(text)
            count = text.count("\n") - 5
            print(
                "package_manifest: wrote %s (%d files, target %s, launch %s)"
                % (path, count, args.target, args.launch)
            )
        else:
            manifest = check_stage(args.stage)
            print(
                "package_manifest: ok (%d files, target %s, launch %s)"
                % (len(manifest.entries), manifest.target, manifest.launch)
            )
    except ManifestError as error:
        print("package_manifest: %s" % error, file=sys.stderr)
        return 1
    except OSError as error:
        print("package_manifest: %s" % error, file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
