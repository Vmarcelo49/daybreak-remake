#!/usr/bin/env python3
"""The real game binary must finish or roll back a crashed update (issue #100, step 4).

Copies the built binary into a synthetic install (no game data), plants the `applying`
journal and a backup of the kind an interrupted apply leaves, and runs it with `--list` —
the one mode that reaches the recovery call and exits before opening assets. Both the
legacy format-1 journal (with a `<target>.old` backup) and the format-2 journal (with an
explicit workspace backup path) must recover. A second run in a folder with no
`package-manifest.txt` proves a development tree is left alone.

    update_recovery_test.py <daybreak binary>
"""
import hashlib
import os
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

JOURNAL_LEGACY = """format = 1
state = applying
version = 2.0.0
manifest = {manifest_hash}
[operations]
replace foo.txt
"""

JOURNAL_V2 = """format = 2
state = applying
version = 2.0.0
manifest = {manifest_hash}
[backups]
backup/foo.txt\tfoo.txt
[operations]
replace foo.txt
"""


def write(path, data, mode=0o644):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(data)
    path.chmod(mode)


def plant(root, with_manifest, version=1, orphan=False):
    """Leave the install as a crash between the journal and the commit would."""
    write(root / "foo.txt", b"new contents\n")
    if version == 1:
        write(root / "foo.txt.old", b"old contents\n")
    else:
        write(root / ".daybreak-update" / "1.0.0" / "backup" / "foo.txt",
              b"old contents\n")
        if orphan:
            write(root / "foo.txt.old", b"user orphan\n")
    journal = JOURNAL_LEGACY if version == 1 else JOURNAL_V2
    write(root / ".daybreak-update" / "1.0.0" / "journal",
          journal.format(manifest_hash="a" * 64).encode())
    if with_manifest:
        binary = (root / "daybreak").read_bytes()
        manifest = (
            "format = 1\nversion = 1.0.0\ntarget = linux-x86_64\nlaunch = daybreak\n"
            "[files]\n%s  %d  x  daybreak\n"
            % (hashlib.sha256(binary).hexdigest(), len(binary))
        )
        write(root / "package-manifest.txt", manifest.encode())
    else:
        (root / "package-manifest.txt").unlink(missing_ok=True)


def run(binary, root):
    environment = dict(os.environ)
    environment["SDL_AUDIODRIVER"] = "dummy"
    environment["XDG_CONFIG_HOME"] = str(root / "config")
    return subprocess.run([str(binary), "--no-audio", "--list"], cwd=root,
                          capture_output=True, text=True, env=environment, timeout=120)


def main():
    if len(sys.argv) != 2:
        print("usage: update_recovery_test.py <daybreak binary>", file=sys.stderr)
        return 2
    binary = Path(sys.argv[1])
    with tempfile.TemporaryDirectory(prefix="update-recovery-") as temporary:
        root = Path(temporary) / "install"
        root.mkdir()
        shutil.copy2(binary, root / "daybreak")

        for version in (1, 2):
            plant(root, with_manifest=True, version=version, orphan=(version == 2))
            result = run(root / "daybreak", root)
            if "recovered an interrupted update" not in result.stdout:
                print("update_recovery_test: the game did not log the recovery for "
                      "format %d:\n" % version + result.stdout + result.stderr,
                      file=sys.stderr)
                return 1
            if (root / "foo.txt").read_bytes() != b"old contents\n":
                print("update_recovery_test: the replaced file was not restored for "
                      "format %d" % version, file=sys.stderr)
                return 1
            if version == 1 and (root / "foo.txt.old").exists():
                print("update_recovery_test: the .old file was not cleaned up",
                      file=sys.stderr)
                return 1
            if version == 2:
                if (root / ".daybreak-update" / "1.0.0" / "backup" / "foo.txt").exists():
                    print("update_recovery_test: the journal's backup was not consumed",
                          file=sys.stderr)
                    return 1
                if (root / "foo.txt.old").read_bytes() != b"user orphan\n":
                    print("update_recovery_test: a legacy orphan was touched by "
                          "format-2 recovery", file=sys.stderr)
                    return 1
            if (root / ".daybreak-update").exists():
                print("update_recovery_test: the workspace was not removed for "
                      "format %d" % version, file=sys.stderr)
                return 1

        # A development tree has no package manifest: recovery must not touch it.
        plant(root, with_manifest=False)
        result = run(root / "daybreak", root)
        if "recovered an interrupted update" in result.stdout:
            print("update_recovery_test: recovery acted in a development tree", file=sys.stderr)
            return 1
        if (root / "foo.txt").read_bytes() != b"new contents\n" or \
                not (root / ".daybreak-update" / "1.0.0" / "journal").exists():
            print("update_recovery_test: a development tree was modified", file=sys.stderr)
            return 1
    print("update_recovery_test: the game rolls back both journal formats, leaves legacy "
          "orphans alone, and only recovers in an installed package")
    return 0


if __name__ == "__main__":
    sys.exit(main())
