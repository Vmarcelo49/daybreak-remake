"""The .DAT archive reader, mirroring ``src/assets/dat_bundle.{h,cpp}``.

RECOVERED, not invented. Everything in this module is the same rule the original
exe implements and the native foundation already ports:

  * packed little-endian table, ``uint16 numFiles`` then ``numFiles * 268`` bytes
    XOR-encrypted with the stateful table cipher (exe 0x00662d10, key=100);
  * each 268-byte entry is ``char name[260]`` (CP932, NUL-padded), ``uint32
    length``, ``uint32 offset``;
  * payloads sit at ``offset`` and are XOR-encrypted with one byte derived from
    that offset (exe 0x00663030);
  * a lookup is **exact first, then ASCII-case-insensitive** — the exe's bundle
    index compares with ``__stricmp`` (0x00663c20), which folds only A-Z;
  * duplicate names resolve to the **earliest registered** bundle, and the
    registration order (daybreak07, 04, 00, then the tail) is not the
    file-number order (see ``dat_bundle.cpp``'s derivation).

Keeping this a second implementation rather than a binding is deliberate: the
catalog has to be checkable *against* the native reader, and a shared
implementation could only agree with itself. ``tests/web_catalog_order.cpp``
compares the two orderings directly.
"""

from __future__ import annotations

import struct
from dataclasses import dataclass
from pathlib import Path
from typing import Iterator, Sequence

#: Registration (precedence) order — the native ``DatBundleSet::bundleFileName``.
#: The first four are the RE'd registration sites (0x64d4d4 / 0x64d4ee / 0x64d4fe
#: and the tail from the exe's own name table, .rdata 0x6a5598); daybreak01 and
#: daybreak03 are not in the game's list at all.
BUNDLE_PRECEDENCE: tuple[str, ...] = (
    "daybreak07.dat",
    "daybreak04.dat",
    "daybreak00.dat",
    "daybreak05.dat",
    "daybreak02.dat",
    "daybreak06.dat",
)

#: Name-table byte layout (dat_bundle.cpp's kEntrySize / kFilenameBytes / ...).
ENTRY_SIZE = 268
FILENAME_BYTES = 260
LENGTH_OFFSET = 260
OFFSET_OFFSET = 264


class BundleError(Exception):
    """A bundle could not be read; the text says which and why."""


def table_xor(data: bytearray, index: int = 0) -> None:
    """In-place table-block cipher. Its own inverse (``dat_crypto.cpp``)."""
    index &= 0x1FF
    counter = (100 + index * 77) & 0xFF
    triangular = (index * (index - 1)) // 2
    key = (100 * (index + 1) + ((triangular & 0xFF) * 77)) & 0xFF
    for i in range(len(data)):
        data[i] ^= key
        key = (key + counter) & 0xFF
        counter = (counter + 77) & 0xFF


def payload_key(offset: int) -> int:
    """Per-payload XOR byte: ``((offset >> 1) & 0xff) | 0x08``."""
    return ((offset >> 1) & 0xFF) | 0x08


def _translate_table(offset: int) -> bytes:
    """256-byte translation table for one payload key (``bytes.translate``)."""
    key = payload_key(offset)
    return bytes(b ^ key for b in range(256))


def ascii_fold(name: str) -> str:
    """The exe's ``__stricmp`` fold in the "C" locale: A-Z only, bytes >= 0x80
    compare exactly — reproduced on the decoded string, where non-ASCII
    characters are already code points and never change case."""
    return "".join(chr(ord(c) + 32) if "A" <= c <= "Z" else c for c in name)


@dataclass(frozen=True)
class Entry:
    """One file-table entry."""

    bundle: str
    precedence: int      # position in BUNDLE_PRECEDENCE
    index: int           # position in this bundle's own table
    offset: int
    length: int
    raw_name: bytes      # the 260-byte slot up to the first NUL (CP932)
    name: str            # decoded UTF-8 logical path ("data/rika/01.X")

    @property
    def key(self) -> str:
        return self.name


class Bundle:
    """One opened .DAT, holding its parsed table (payloads are read on demand)."""

    def __init__(self, path: Path, precedence: int) -> None:
        self.path = path
        self.name = path.name
        self.precedence = precedence
        self.entries: list[Entry] = []
        self.error = ""
        self._size = 0
        self._load()

    def _load(self) -> None:
        try:
            self._size = self.path.stat().st_size
        except OSError as exc:
            self.error = f"cannot stat {self.path}: {exc}"
            return
        try:
            with self.path.open("rb") as handle:
                header = handle.read(2)
                if len(header) != 2:
                    raise BundleError("short header (want 2 bytes, got %d)" % len(header))
                count = struct.unpack("<H", header)[0]
                table = bytearray(handle.read(count * ENTRY_SIZE))
                if len(table) != count * ENTRY_SIZE:
                    raise BundleError(
                        "table truncated (want %d bytes, got %d; numFiles=%d)"
                        % (count * ENTRY_SIZE, len(table), count)
                    )
        except (OSError, BundleError) as exc:
            self.error = f"{self.name}: {exc}"
            return

        table_xor(table, 0)
        for i in range(count):
            base = i * ENTRY_SIZE
            slot = bytes(table[base:base + FILENAME_BYTES])
            raw = slot.split(b"\x00", 1)[0]
            length, offset = struct.unpack_from("<II", table, base + LENGTH_OFFSET)
            self.entries.append(
                Entry(
                    bundle=self.name,
                    precedence=self.precedence,
                    index=i,
                    offset=offset,
                    length=length,
                    raw_name=raw,
                    name=decode_name(raw),
                )
            )

    @property
    def size(self) -> int:
        return self._size

    def read(self, entry: Entry) -> bytes:
        """Read + decrypt one payload, with the native bounds check first."""
        if entry.length and entry.offset + entry.length > self._size:
            raise BundleError(
                "entry %d (%s) out of bounds: offset %d + length %d > file size %d"
                % (entry.index, entry.name, entry.offset, entry.length, self._size)
            )
        with self.path.open("rb") as handle:
            handle.seek(entry.offset)
            data = handle.read(entry.length)
        if len(data) != entry.length:
            raise BundleError(
                "short read for %s (%d/%d bytes)" % (entry.name, len(data), entry.length)
            )
        return data.translate(_translate_table(entry.offset))


def decode_name(raw: bytes) -> str:
    """CP932 -> UTF-8 for one name slot.

    ``errors="replace"`` keeps a broken slot from killing a whole install; the
    native reader passes unmapped bytes through instead, which is the one place
    the two decoders can disagree (dat_bundle.h measures that at 98/12345 names,
    all but one .cnv). The ordering check compares *raw* name bytes, so a decode
    difference can never mask a precedence difference.
    """
    return raw.decode("cp932", errors="replace").replace("\\", "/")


class BundleSet:
    """The six bundles in precedence order, with the native lookup rules."""

    def __init__(self, install_dir: Path, names: Sequence[str] = BUNDLE_PRECEDENCE) -> None:
        self.install_dir = Path(install_dir)
        self.bundles: list[Bundle] = [
            Bundle(self.install_dir / name, i) for i, name in enumerate(names)
        ]
        # Lowercased-name -> first entry in precedence order, for the folded lookup.
        self._folded: dict[str, Entry] = {}
        for entry in self.entries():
            key = ascii_fold(entry.name)
            if key not in self._folded:
                self._folded[key] = entry

    @property
    def open_bundles(self) -> list[Bundle]:
        return [b for b in self.bundles if not b.error]

    @property
    def missing(self) -> list[str]:
        return [b.name for b in self.bundles if b.error]

    def entries(self) -> Iterator[Entry]:
        """Every entry, bundles in precedence order, tables in file order."""
        for bundle in self.bundles:
            yield from bundle.entries

    def find(self, name: str) -> Entry | None:
        """Exact match first, then the ASCII fold — ``AssetSource::read``'s rule."""
        for bundle in self.bundles:
            for entry in bundle.entries:
                if entry.name == name:
                    return entry
        return self._folded.get(ascii_fold(name))

    def resolve(self) -> dict[str, Entry]:
        """Winner per logical name: the earliest registered bundle that has it."""
        winners: dict[str, Entry] = {}
        for entry in self.entries():
            winners.setdefault(entry.name, entry)
        return winners

    def copies(self) -> dict[str, list[Entry]]:
        """Every copy of every name, in precedence order (first copy wins)."""
        groups: dict[str, list[Entry]] = {}
        for entry in self.entries():
            groups.setdefault(entry.name, []).append(entry)
        return groups
