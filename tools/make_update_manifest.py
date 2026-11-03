#!/usr/bin/env python3
"""Build `update-manifest.txt` from the two release archives (issue #100).

The updater reads one small text file from the newest release instead of calling the
GitHub API. This tool is the release step that produces it: it opens each archive,
verifies the archive against the `package-manifest.txt` inside it (so the hashes it
publishes describe what the archive really contains, not what the packaging script
intended), and writes the archive names, sizes and hashes in a fixed order.

The output is signed, so its bytes are the contract: same inputs, same bytes. Stdlib
only (`gzip` via `zlib`, `struct`, `hashlib`), run with `python3 -I`.

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
import struct
import sys
import zlib
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
# The release's own names, so a stale or renamed artifact cannot be published. The
# revision is lowercase hex only: a dirty tree's "-dirty" suffix must never be released.
WINDOWS_ARCHIVE_RE = re.compile(
    r"^daybreak-(?P<version>[0-9]+\.[0-9]+\.[0-9]+)-(?P<revision>[0-9a-f]{7,40})"
    r"-windows-x86_64\.zip$"
)


def linux_archive_name(version):
    return "daybreak-%s-linux-x86_64.tar.gz" % version


def linux_top_directory(version):
    return "daybreak-%s-linux-x86_64" % version


class ArchiveError(pm.ManifestError):
    """A release archive that does not match its manifest or the format."""


def _decode_name(raw, where):
    try:
        return raw.decode("utf-8")
    except UnicodeDecodeError:
        raise ArchiveError("%s: an archive member name is not valid UTF-8" % where)


# --- Linux: one gzip member holding a POSIX ustar archive -------------------------
#
# The game's reader (src/update/archive.cpp) implements exactly this set, so anything
# accepted here but unreadable there would be an update nobody can apply. The headers
# are parsed raw because tarfile's member view hides the GNU long-name records and pax
# headers this must refuse.

GZIP_LIMIT = 2 * 1024 * 1024 * 1024
MAX_ENTRIES = 10000
MAX_TOTAL_UNCOMPRESSED = 1024 * 1024 * 1024
MAX_RATIO = 200


def _octal(field, what, where):
    text = field.split(b"\0", 1)[0].strip()
    if not text:
        return 0
    if text[0] & 0x80:
        raise ArchiveError(
            "%s: %s uses base-256 encoding, which is not POSIX ustar" % (where, what)
        )
    if any(character not in b"01234567" for character in text):
        raise ArchiveError("%s: %s is not an octal number" % (where, what))
    return int(text, 8)


def _cstring(field):
    return field.split(b"\0", 1)[0]


def gunzip_member(data, where):
    """Inflate the archive's single gzip member; zlib checks the CRC32 and ISIZE."""
    if len(data) < 18 or data[:2] != b"\x1f\x8b":
        raise ArchiveError("%s: not a gzip file" % where)
    if data[2] != 8:
        raise ArchiveError("%s: gzip method %d is not deflate" % (where, data[2]))
    inflater = zlib.decompressobj(16 + zlib.MAX_WBITS)
    pending = data
    chunks = []
    total = 0
    try:
        while True:
            chunk = inflater.decompress(pending, 1 << 20)
            pending = inflater.unconsumed_tail
            if chunk:
                total += len(chunk)
                if total > GZIP_LIMIT:
                    raise ArchiveError(
                        "%s: decompressed data exceeds %d bytes" % (where, GZIP_LIMIT)
                    )
                chunks.append(chunk)
            if inflater.eof:
                break
            if not chunk and not pending:
                raise ArchiveError("%s: truncated gzip stream" % where)
    except zlib.error as error:
        raise ArchiveError("%s: damaged gzip stream: %s" % (where, error))
    if inflater.unused_data:
        raise ArchiveError(
            "%s: data after the gzip member (exactly one member is allowed)" % where
        )
    return b"".join(chunks)


def ustar_entries(raw, where):
    """Walk raw ustar headers: [(name bytes, is_dir, mode, content)]."""
    if len(raw) % 512 != 0:
        raise ArchiveError("%s: tar data is not a multiple of 512 bytes" % where)
    entries = []
    offset = 0
    ended = False
    while offset < len(raw):
        header = raw[offset:offset + 512]
        if header == b"\0" * 512:
            if any(raw[offset:]):
                raise ArchiveError("%s: data after the end-of-archive blocks" % where)
            ended = True
            break
        checksum = _octal(header[148:156], "header checksum", where)
        actual = sum(header[:148]) + 8 * 0x20 + sum(header[156:])
        if checksum != actual:
            raise ArchiveError(
                "%s: tar header checksum mismatch at offset %d" % (where, offset)
            )
        if header[257:263] != b"ustar\0" or header[263:265] != b"00":
            raise ArchiveError(
                "%s: not a POSIX ustar archive (magic %r); GNU and pax extensions are "
                "not supported" % (where, header[257:265])
            )
        typeflag = header[156:157]
        name = _cstring(header[0:100])
        prefix = _cstring(header[345:500])
        if not name:
            raise ArchiveError("%s: tar member with an empty name" % where)
        full = prefix + b"/" + name if prefix else name
        size = _octal(header[124:136], "size", where)
        mode = _octal(header[100:108], "mode", where)
        if typeflag in (b"0", b"\0"):
            is_dir = False
        elif typeflag == b"5":
            is_dir = True
        elif typeflag == b"2":
            raise ArchiveError(
                "%s: %r is a symlink; only regular files and directories are supported"
                % (where, full)
            )
        elif typeflag == b"1":
            raise ArchiveError(
                "%s: %r is a hard link; only regular files and directories are supported"
                % (where, full)
            )
        else:
            raise ArchiveError(
                "%s: tar member %r has type %r; only regular files (0) and directories "
                "(5) are supported" % (where, full, typeflag)
            )
        if is_dir:
            if size:
                raise ArchiveError("%s: directory %r has a size" % (where, full))
            entries.append((full.rstrip(b"/"), True, mode, b""))
            offset += 512
        else:
            if full.endswith(b"/"):
                raise ArchiveError("%s: file %r has a trailing slash" % (where, full))
            end = offset + 512 + size
            if end > len(raw):
                raise ArchiveError("%s: %r is truncated" % (where, full))
            entries.append((full, False, mode, raw[offset + 512:end]))
            offset += 512 + ((size + 511) // 512) * 512
    if not ended:
        raise ArchiveError("%s: no end-of-archive blocks" % where)
    return entries


def read_linux_archive(path):
    """Read a Linux .tar.gz: returns (top directory, files, exec bits, manifest text)."""
    label = Path(path).name
    raw = gunzip_member(Path(path).read_bytes(), label)
    entries = ustar_entries(raw, label)

    normalised = []
    for name, is_dir, mode, content in entries:
        text = _decode_name(name, label)
        if text.startswith("./"):
            text = text[2:]
        pm.check_relative_path(text, label)
        normalised.append((text, is_dir, mode, content))

    tops = {text.split("/")[0] for text, _, _, _ in normalised}
    if len(tops) != 1:
        raise ArchiveError(
            "%s: expected one top-level directory, found %d (%s)"
            % (label, len(tops), ", ".join(sorted(tops)))
        )
    top = tops.pop()
    prefix = top + "/"
    files = {}
    exec_bits = {}
    for text, is_dir, mode, content in normalised:
        if text == top:
            if not is_dir:
                raise ArchiveError(
                    "%s: %r is the top-level entry but not a directory" % (label, text)
                )
            continue
        if not text.startswith(prefix):
            raise ArchiveError(
                "%s: %r is outside the top-level directory %r" % (label, text, top)
            )
        relative = text[len(prefix):]
        if is_dir:
            continue
        if relative in files:
            raise ArchiveError("%s: %r appears twice in the archive" % (label, relative))
        files[relative] = content
        exec_bits[relative] = bool(mode & 0o111)
    pm.check_entry_paths(sorted(files), label)
    manifest = take_manifest(files, label)
    exec_bits.pop(pm.MANIFEST_NAME, None)
    return top, files, exec_bits, manifest


# --- Windows: one flat zip, methods 0/8, no encryption, no zip64 ------------------

ZIP_LOCAL_SIGNATURE = b"PK\x03\x04"
ZIP_CENTRAL_SIGNATURE = b"PK\x01\x02"
ZIP_EOCD_SIGNATURE = b"PK\x05\x06"


def _has_zip64_extra(extra):
    position = 0
    while position + 4 <= len(extra):
        tag, size = struct.unpack_from("<HH", extra, position)
        if tag == 0x0001:
            return True
        position += 4 + size
    return False


def _zip_name(raw_name, flags, where):
    if flags & 0x0800:
        return _decode_name(raw_name, where)
    if any(byte >= 0x80 for byte in raw_name):
        raise ArchiveError(
            "%s: %r is not ASCII and the entry does not set the UTF-8 flag"
            % (where, raw_name)
        )
    return raw_name.decode("ascii")


def read_windows_archive(path):
    """Read a flat Windows .zip: returns (files, exec bits, manifest text)."""
    label = Path(path).name
    data = Path(path).read_bytes()
    if len(data) < 22:
        raise ArchiveError("%s: too small to be a zip" % label)
    eocd = data.rfind(ZIP_EOCD_SIGNATURE, max(0, len(data) - (65535 + 22)))
    if eocd < 0:
        raise ArchiveError("%s: no end-of-central-directory record" % label)
    if eocd + 22 > len(data):
        raise ArchiveError("%s: truncated end-of-central-directory record" % label)
    (disk, central_disk, entries_disk, entries_total, central_size, central_offset,
     comment_length) = struct.unpack_from("<HHHHIIH", data, eocd + 4)
    if eocd + 22 + comment_length != len(data):
        raise ArchiveError(
            "%s: the archive comment runs past the end of the file" % label
        )
    if disk != 0 or central_disk != 0 or entries_disk != entries_total:
        raise ArchiveError("%s: multi-disk archives are not supported" % label)
    if (entries_total == 0xFFFF or central_size == 0xFFFFFFFF
            or central_offset == 0xFFFFFFFF):
        raise ArchiveError("%s: zip64 archives are not supported" % label)
    if entries_total > MAX_ENTRIES:
        raise ArchiveError(
            "%s: %d entries exceeds the %d-entry limit"
            % (label, entries_total, MAX_ENTRIES)
        )

    files = {}
    modes = {}
    total_uncompressed = 0
    position = central_offset
    for _ in range(entries_total):
        if position + 46 > len(data):
            raise ArchiveError("%s: truncated central directory" % label)
        if data[position:position + 4] != ZIP_CENTRAL_SIGNATURE:
            raise ArchiveError(
                "%s: bad central directory signature at offset %d" % (label, position)
            )
        (_, _, flags, method, _, _, crc, compressed_size, uncompressed_size,
         name_length, extra_length, comment_size, disk_start, _, external,
         local_offset) = struct.unpack_from("<HHHHHHIIIHHHHHII", data, position + 4)
        name_start = position + 46
        name_end = name_start + name_length
        extra_end = name_end + extra_length
        next_position = extra_end + comment_size
        if next_position > len(data):
            raise ArchiveError("%s: truncated central directory entry" % label)
        raw_name = data[name_start:name_end]
        name = _zip_name(raw_name, flags, label)
        if name.startswith("./"):
            name = name[2:]
        mode = (external >> 16) & 0xFFFF
        if (mode & 0o170000) == 0o120000:
            raise ArchiveError(
                "%s: %r is a symlink; only regular files and directories are supported"
                % (label, name)
            )
        if flags & 0x0001:
            raise ArchiveError(
                "%s: %r is encrypted; encrypted entries are not supported" % (label, name)
            )
        if method not in (0, 8):
            raise ArchiveError(
                "%s: %r uses compression method %d; only 0 (stored) and 8 (deflate) are "
                "supported" % (label, name, method)
            )
        if _has_zip64_extra(data[name_end:extra_end]):
            raise ArchiveError(
                "%s: %r has a zip64 extra field; zip64 is not supported" % (label, name)
            )
        if disk_start != 0:
            raise ArchiveError("%s: %r starts on another disk" % (label, name))

        if (local_offset + 30 > len(data)
                or data[local_offset:local_offset + 4] != ZIP_LOCAL_SIGNATURE):
            raise ArchiveError(
                "%s: %r has no local header at offset %d" % (label, name, local_offset)
            )
        (_, local_flags, local_method, _, _, _, _, _, local_name_length,
         local_extra_length) = struct.unpack_from("<HHHHHIIIHH", data, local_offset + 4)
        local_name_start = local_offset + 30
        local_name_end = local_name_start + local_name_length
        local_extra_end = local_name_end + local_extra_length
        if local_extra_end > len(data):
            raise ArchiveError("%s: %r has a truncated local header" % (label, name))
        if data[local_name_start:local_name_end] != raw_name:
            raise ArchiveError(
                "%s: %r has a different name in its local header" % (label, name)
            )
        if _has_zip64_extra(data[local_name_end:local_extra_end]):
            raise ArchiveError(
                "%s: %r has a zip64 local extra field; zip64 is not supported"
                % (label, name)
            )
        if local_method != method or local_flags & 0x0001:
            raise ArchiveError(
                "%s: %r has an inconsistent local header" % (label, name)
            )

        data_start = local_extra_end
        data_end = data_start + compressed_size
        if data_end > len(data):
            raise ArchiveError("%s: %r is truncated" % (label, name))
        compressed = data[data_start:data_end]
        if method == 0:
            if compressed_size != uncompressed_size:
                raise ArchiveError(
                    "%s: stored entry %r has mismatched sizes" % (label, name)
                )
            content = compressed
        else:
            if uncompressed_size > MAX_TOTAL_UNCOMPRESSED:
                raise ArchiveError(
                    "%s: %r declares %d bytes, beyond the %d-byte limit"
                    % (label, name, uncompressed_size, MAX_TOTAL_UNCOMPRESSED)
                )
            if compressed_size == 0 or uncompressed_size > MAX_RATIO * compressed_size:
                raise ArchiveError(
                    "%s: %r inflates beyond %d:1 (a zip bomb?)"
                    % (label, name, MAX_RATIO)
                )
            inflater = zlib.decompressobj(-15)
            try:
                content = inflater.decompress(compressed, uncompressed_size + 1)
            except zlib.error as error:
                raise ArchiveError(
                    "%s: %r is not valid deflate data: %s" % (label, name, error)
                )
            if len(content) != uncompressed_size:
                raise ArchiveError(
                    "%s: %r inflates to %d bytes, the directory says %d"
                    % (label, name, len(content), uncompressed_size)
                )
            if not inflater.eof or inflater.unused_data or inflater.unconsumed_tail:
                raise ArchiveError(
                    "%s: %r's deflate stream does not end where the entry does"
                    % (label, name)
                )
        if (zlib.crc32(content) & 0xFFFFFFFF) != crc:
            raise ArchiveError("%s: %r fails its CRC32 check" % (label, name))

        is_dir = name.endswith("/")
        normalised = name.rstrip("/")
        if not normalised:
            raise ArchiveError("%s: empty archive member name" % label)
        pm.check_relative_path(normalised, label)
        if is_dir:
            if content:
                raise ArchiveError("%s: directory %r holds data" % (label, name))
        else:
            if normalised in files:
                raise ArchiveError(
                    "%s: %r appears twice in the archive" % (label, normalised)
                )
            total_uncompressed += uncompressed_size
            if total_uncompressed > MAX_TOTAL_UNCOMPRESSED:
                raise ArchiveError(
                    "%s: uncompressed data exceeds %d bytes"
                    % (label, MAX_TOTAL_UNCOMPRESSED)
                )
            files[normalised] = content
            modes[normalised] = bool((external >> 16) & 0o111)
        position = next_position

    if position != central_offset + central_size:
        raise ArchiveError(
            "%s: central directory size does not match the end record" % label
        )
    pm.check_entry_paths(sorted(files), label)
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

    if archive_name(linux_path) != linux_archive_name(version):
        raise ArchiveError(
            "--linux is %r; the release's Linux archive is %r"
            % (os.path.basename(linux_path), linux_archive_name(version))
        )
    windows_name = archive_name(windows_path)
    windows_match = WINDOWS_ARCHIVE_RE.match(windows_name)
    if not windows_match:
        raise ArchiveError(
            "--windows is %r; the release's Windows archive is "
            "daybreak-<version>-<7 to 40 lowercase hex>-windows-x86_64.zip "
            "(a '-dirty' build must not be released)" % windows_name
        )
    if windows_match.group("version") != version:
        raise ArchiveError(
            "--windows is %r, which names version %r, --version is %r"
            % (windows_name, windows_match.group("version"), version)
        )

    linux_top, linux_files, linux_modes, linux_manifest = read_linux_archive(linux_path)
    if linux_top != linux_top_directory(version):
        raise ArchiveError(
            "%s: top-level directory is %r, expected %r"
            % (archive_name(linux_path), linux_top, linux_top_directory(version))
        )
    check_against_manifest(
        linux_files, linux_modes, linux_manifest, "linux-x86_64", version,
        archive_name(linux_path),
    )
    windows_files, windows_modes, windows_manifest = read_windows_archive(windows_path)
    check_against_manifest(
        windows_files, windows_modes, windows_manifest, "windows-x86_64", version,
        windows_name,
    )

    linux_sha256, linux_size = archive_facts(linux_path)
    windows_sha256, windows_size = archive_facts(windows_path)
    return render(
        version,
        linux_archive_name(version), linux_size, linux_sha256,
        windows_name, windows_size, windows_sha256,
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
    # A damaged archive must be a one-line failure, never a traceback: the parsers raise
    # ArchiveError for everything they detect, and these are the exceptions a hostile or
    # corrupt file can still provoke from the standard library.
    except (pm.ManifestError, OSError, EOFError, zlib.error, NotImplementedError,
            RuntimeError, struct.error) as error:
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
