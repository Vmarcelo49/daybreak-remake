#!/usr/bin/env python3
"""
Generate a synthetic .DAT file in the Higurashi Daybreak format for testing
the C++ DatBundle parser.

Layout (all little-endian):
  offset 0:  uint16  numFiles
  offset 2:  uint8   fileTable[numFiles * 268]   (XOR-encrypted with index=0)

  Each 268-byte entry (decrypted):
    [0:260]   filename in Shift-JIS, null-padded
    [260:264] uint32 length
    [264:268] uint32 offset

  File payloads: XOR with key = ((offset >> 1) & 0xff) | 0x08

Table encryption (index = 0):
  counter = (100 + 0*77) & 0xff = 100
  key     = (100*1 + 0) & 0xff  = 100
  for each byte i:
    out[i] = in[i] ^ key
    key     = (key + counter) & 0xff
    counter = (counter + 77) & 0xff
"""
import struct
import sys
import os


def encrypt_table(index: int, data: bytes) -> bytes:
    """Mirror of Go's DecryptFileTableBlock."""
    index &= 0x1ff
    counter = (100 + index * 77) & 0xff
    tri = (index * (index - 1)) // 2
    key = (100 * (index + 1) + ((tri & 0xff) * 77)) & 0xff
    out = bytearray(len(data))
    for i, b in enumerate(data):
        out[i] = b ^ key
        key = (key + counter) & 0xff
        counter = (counter + 77) & 0xff
    return bytes(out)


def file_data_key(offset: int) -> int:
    return ((offset >> 1) & 0xff) | 0x08


def xor_payload(offset: int, data: bytes) -> bytes:
    k = file_data_key(offset)
    return bytes(b ^ k for b in data)


def build_entry(filename_sjis: bytes, length: int, offset: int) -> bytes:
    """Build a 268-byte decrypted table entry."""
    if len(filename_sjis) > 259:
        raise ValueError("filename too long")
    name_field = filename_sjis + b'\x00' * (260 - len(filename_sjis))
    return name_field + struct.pack('<II', length, offset)


def main():
    # Three test files with ASCII names + one with a Shift-JIS Japanese name.
    files = [
        # (sjis_name, payload)
        (b"readme.txt",         b"hello daybreak\nthis is a test file.\n"),
        (b"data.bin",           bytes(range(256)) * 4),     # 1024 bytes
        (b"subdir/nested.x",   b"xof 0303txt 0032\n# placeholder\n"),
        # Shift-JIS for " テスト " (test): 0x83 0x65 0x83 0x58 0x83 0x67
        ("\u30c6\u30b9\u30c8.txt".encode("cp932"),
         b"japanese filename test\n"),
    ]

    num_files = len(files)
    # Compute offsets: header(2) + table(num_files * 268) + payloads
    table_size = num_files * 268
    first_payload_offset = 2 + table_size

    # Layout: place each file right after the previous one
    entries = []
    offset = first_payload_offset
    for sjis_name, payload in files:
        entries.append((sjis_name, len(payload), offset, payload))
        offset += len(payload)

    # Build decrypted table
    table = b"".join(
        build_entry(name, length, off)
        for (name, length, off, _) in entries
    )
    assert len(table) == table_size

    # Encrypt table
    encrypted_table = encrypt_table(0, table)

    # Build output: header + encrypted table + encrypted payloads
    out = bytearray()
    out += struct.pack('<H', num_files)
    out += encrypted_table
    for (_, _, off, payload) in entries:
        # Sanity: ensure we're at the right offset
        assert len(out) == off, f"offset mismatch: expected {off}, got {len(out)}"
        out += xor_payload(off, payload)

    out_path = sys.argv[1] if len(sys.argv) > 1 else "test.dat"
    with open(out_path, "wb") as f:
        f.write(out)

    print(f"wrote {out_path} ({len(out)} bytes, {num_files} entries)")
    print("entries:")
    for (name, length, off, _) in entries:
        try:
            decoded = name.decode('cp932')
        except UnicodeDecodeError:
            decoded = repr(name)
        print(f"  offset={off:6d}  length={length:6d}  name={decoded!r}")


if __name__ == "__main__":
    main()
