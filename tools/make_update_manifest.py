#!/usr/bin/env python3
"""Build `update-manifest.txt` from the two release archives (issue #100).

The updater reads one small text file from the newest release instead of calling the
GitHub API. This tool is the release step that produces it: it opens each archive,
verifies the archive against the `package-manifest.txt` inside it (so the hashes it
publishes describe what the archive really contains, not what the packaging script
intended), and writes the archive names, sizes and hashes in a fixed order.

The output is signed, so its bytes are the contract: same inputs, same bytes. Stdlib
only, run with `python3 -I`.

    python3 -I tools/make_update_manifest.py --version=1.0.0 \\
        --linux=daybreak-1.0.0-linux-x86_64.tar.gz \\
        --windows=daybreak-1.0.0-2d33582-windows-x86_64.zip \\
        --out=update-manifest.txt

The format is specified in docs/AUTO-UPDATE.md.
"""

import argparse
import hashlib
import os
import re
import stat
import sys
import tarfile
import zipfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import package_manifest as pm  # noqa: E402

REPOSITORY = "https://github.com/Vmarcelo49/daybreak-remake"
NOTES_PREFIX = REPOSITORY + "/releases/tag/v"

# A plain X.Y.Z, as the updater's version comparison expects: no suffix, no leading
# zeros (semver forbids them), no "v".
SEMVER_RE = re.compile(r"^(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)\.(0|[1-9][0-9]*)$")
# The archive name ends up in a URL and on a `key = value` line, so keep it boring.
ARCHIVE_NAME_RE = re.compile(r"^[A-Za-z0-9._+-]+$")


class ArchiveError(pm.ManifestError):
    """A release archive that does not match its manifest or the format."""


def member_name(raw, where):
    """Normalise one archive member name and reject anything unsafe."""
    name = raw[2:] if raw.startswith("./") else raw
    name = name.rstrip("/")
    if not name:
        raise ArchiveError("%s: empty archive member name" % where)
    pm.check_relative_path(name, where)
    return name


def read_linux_archive(path):
    """Read a Linux .tar.gz: returns (files, exec bits, manifest text)."""
    label = Path(path).name
    files = {}
    modes = {}
    try:
        with tarfile.open(path, "r:gz") as archive:
            for member in archive:
                name = member_name(member.name, label)
                if member.isdir():
                    continue
                if member.issym():
                    raise ArchiveError(
                        "%s: %s is a symlink; an archive may only hold regular files "
                        "and directories" % (label, name)
                    )
                if member.islnk():
                    raise ArchiveError(
                        "%s: %s is a hard link; an archive may only hold regular files "
                        "and directories" % (label, name)
                    )
                if not member.isfile():
                    raise ArchiveError(
                        "%s: %s is not a regular file (tar type %r)"
                        % (label, name, member.type)
                    )
                if name in files:
                    raise ArchiveError("%s: %s appears twice in the archive" % (label, name))
                handle = archive.extractfile(member)
                if handle is None:
                    raise ArchiveError("%s: cannot read %s" % (label, name))
                data = handle.read()
                if len(data) != member.size:
                    raise ArchiveError(
                        "%s: %s is truncated (%d of %d bytes)"
                        % (label, name, len(data), member.size)
                    )
                files[name] = data
                modes[name] = bool(member.mode & 0o111)
    except tarfile.TarError as error:
        raise ArchiveError("%s: not a readable tar.gz: %s" % (path, error))

    top = {name.split("/")[0] for name in files}
    if len(top) != 1:
        raise ArchiveError(
            "%s: expected one top-level directory, found %d (%s)"
            % (label, len(top), ", ".join(sorted(top)))
        )
    prefix = top.pop() + "/"
    relative = {}
    exec_bits = {}
    for name, data in files.items():
        if not name.startswith(prefix):
            raise ArchiveError(
                "%s: %s is outside the top-level directory %s"
                % (label, name, prefix)
            )
        relative[name[len(prefix):]] = data
        exec_bits[name[len(prefix):]] = modes[name]
    manifest = take_manifest(relative, label)
    exec_bits.pop(pm.MANIFEST_NAME, None)
    return relative, exec_bits, manifest


def read_windows_archive(path):
    """Read a flat Windows .zip: returns (files, exec bits, manifest text)."""
    label = Path(path).name
    files = {}
    modes = {}
    try:
        with zipfile.ZipFile(path) as archive:
            for info in archive.infolist():
                name = member_name(info.filename, label)
                mode = info.external_attr >> 16
                if info.is_dir():
                    continue
                if stat.S_ISLNK(mode):
                    raise ArchiveError(
                        "%s: %s is a symlink; an archive may only hold regular files "
                        "and directories" % (label, name)
                    )
                if mode & 0o170000 and not stat.S_ISREG(mode):
                    raise ArchiveError(
                        "%s: %s is not a regular file (mode %o)" % (label, name, mode)
                    )
                if name in files:
                    raise ArchiveError("%s: %s appears twice in the archive" % (label, name))
                files[name] = archive.read(info)
                modes[name] = bool(mode & 0o111)
    except zipfile.BadZipFile as error:
        raise ArchiveError("%s: not a readable zip: %s" % (path, error))

    manifest = take_manifest(files, label)
    modes.pop(pm.MANIFEST_NAME, None)
    return files, modes, manifest


def take_manifest(files, where):
    """Remove and return the package manifest; it is not one of the files it lists."""
    if pm.MANIFEST_NAME not in files:
        raise ArchiveError(
            "%s: no %s at the package root" % (where, pm.MANIFEST_NAME)
        )
    return files.pop(pm.MANIFEST_NAME)


def check_against_manifest(files, exec_bits, manifest_text, target, version, where):
    try:
        manifest = pm.parse_manifest(manifest_text.decode("utf-8"))
    except UnicodeDecodeError:
        raise ArchiveError("%s: %s is not valid UTF-8" % (where, pm.MANIFEST_NAME))
    if manifest.target != target:
        raise ArchiveError(
            "%s: %s says target %r, expected %r"
            % (where, pm.MANIFEST_NAME, manifest.target, target)
        )
    if manifest.version != version:
        raise ArchiveError(
            "%s: %s says version %r, --version is %r"
            % (where, pm.MANIFEST_NAME, manifest.version, version)
        )

    # The archive's own paths get the same NTFS rules as the manifest's: a case
    # collision or a file/directory clash is refused before anything else is compared.
    pm.check_entry_paths(sorted(files), where)

    listed = {entry.path: entry for entry in manifest.entries}
    missing = sorted(set(listed) - set(files))
    if missing:
        raise ArchiveError(
            "%s: the manifest lists %d file(s) the archive does not hold, e.g. %s"
            % (where, len(missing), missing[0])
        )
    extra = sorted(set(files) - set(listed))
    if extra:
        raise ArchiveError(
            "%s: the archive holds %d file(s) the manifest does not list, e.g. %s"
            % (where, len(extra), extra[0])
        )

    for path in sorted(listed):
        entry = listed[path]
        data = files[path]
        if len(data) != entry.size:
            raise ArchiveError(
                "%s: %s is %d bytes, the manifest says %d"
                % (where, path, len(data), entry.size)
            )
        digest = hashlib.sha256(data).hexdigest()
        if digest != entry.sha256:
            raise ArchiveError(
                "%s: %s hashes to %s, the manifest says %s"
                % (where, path, digest, entry.sha256)
            )
        # Zip modes are not meaningful on Windows and its manifest says '-' everywhere,
        # so only the Linux archive has an exec bit to compare.
        if target == "linux-x86_64":
            actual = "x" if exec_bits[path] else "-"
            if entry.mode != actual:
                raise ArchiveError(
                    "%s: %s is %r in the archive, the manifest says %r"
                    % (where, path, actual, entry.mode)
                )
    return manifest


def archive_facts(path):
    """The sha256 and size of the archive file itself, as the updater will see them."""
    info = os.stat(path)
    if not stat.S_ISREG(info.st_mode):
        raise ArchiveError("%s: not a regular file" % path)
    digest = hashlib.sha256()
    with open(path, "rb") as handle:
        for chunk in iter(lambda: handle.read(1 << 20), b""):
            digest.update(chunk)
    return digest.hexdigest(), info.st_size


def archive_name(path):
    name = os.path.basename(path)
    if not ARCHIVE_NAME_RE.match(name):
        raise ArchiveError(
            "%s: the archive name must be URL-safe (letters, digits, '.', '_', '+', '-')"
            % path
        )
    return name


def render(version, linux_name, linux_size, linux_sha256,
           windows_name, windows_size, windows_sha256):
    return (
        "format = 1\n"
        "version = %s\n"
        "notes = %s%s\n"
        "[linux-x86_64]\n"
        "archive = %s\n"
        "size = %d\n"
        "sha256 = %s\n"
        "[windows-x86_64]\n"
        "archive = %s\n"
        "size = %d\n"
        "sha256 = %s\n"
        % (version, NOTES_PREFIX, version,
           linux_name, linux_size, linux_sha256,
           windows_name, windows_size, windows_sha256)
    )


def build(version, linux_path, windows_path):
    if not SEMVER_RE.match(version):
        raise ArchiveError(
            "--version %r must be a plain X.Y.Z semver (no suffix, no leading zeros)"
            % (version,)
        )
    for path in (linux_path, windows_path):
        if not os.path.isfile(path):
            raise ArchiveError("%s: no such file" % path)

    linux_files, linux_modes, linux_manifest = read_linux_archive(linux_path)
    check_against_manifest(
        linux_files, linux_modes, linux_manifest, "linux-x86_64", version,
        archive_name(linux_path),
    )
    windows_files, windows_modes, windows_manifest = read_windows_archive(windows_path)
    check_against_manifest(
        windows_files, windows_modes, windows_manifest, "windows-x86_64", version,
        archive_name(windows_path),
    )

    linux_sha256, linux_size = archive_facts(linux_path)
    windows_sha256, windows_size = archive_facts(windows_path)
    return render(
        version,
        archive_name(linux_path), linux_size, linux_sha256,
        archive_name(windows_path), windows_size, windows_sha256,
    )


def main(argv):
    parser = argparse.ArgumentParser(
        prog="make_update_manifest.py",
        description="Build update-manifest.txt from the Linux and Windows release "
                    "archives (docs/AUTO-UPDATE.md).",
    )
    parser.add_argument("--version", required=True, help="the release's X.Y.Z")
    parser.add_argument("--linux", required=True, help="the Linux .tar.gz")
    parser.add_argument("--windows", required=True, help="the Windows .zip")
    parser.add_argument("--out", required=True, help="where to write update-manifest.txt")
    args = parser.parse_args(argv)

    try:
        text = build(args.version, args.linux, args.windows)
        with open(args.out, "w", encoding="utf-8", newline="\n") as handle:
            handle.write(text)
    except pm.ManifestError as error:
        print("make_update_manifest: %s" % error, file=sys.stderr)
        return 1
    except OSError as error:
        print("make_update_manifest: %s" % error, file=sys.stderr)
        return 1

    print(
        "make_update_manifest: wrote %s (version %s, linux %s, windows %s)"
        % (args.out, args.version,
           os.path.basename(args.linux), os.path.basename(args.windows))
    )
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
