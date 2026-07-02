#!/usr/bin/env python3
"""
Extract all files from daybreakXX.dat archives into data/ folder.

Usage:
    python3 extract_dat.py [path_to_game_folder]

This extracts all files from daybreak00-07.dat into a data/ subfolder,
so the game (with the hook DLL) can load them directly from disk.

Format (reverse-engineered from FUN_00662d10, FUN_00663030):
  Header: uint16 num_entries
  Entry table: num_entries * 0x10c bytes (XOR-encoded)
  File data: XOR-encoded per file

  Entry struct (0x10c = 268 bytes):
    0x00  0x104  filename (null-terminated)
    0x104 4     file_size (uint32 LE)
    0x108 4     file_offset (uint32 LE)

  Entry table XOR:
    key=100, inc=100
    for each byte: byte ^= key; key=(key+inc)&0xFF; inc=(inc+77)&0xFF

  File data XOR:
    key = (file_offset >> 1) | 8  (constant per file)
    for each byte: byte ^= key
"""
import os, struct, sys

def decode_entry_table(data):
    key = 100
    inc = 100
    result = bytearray(data)
    for i in range(len(result)):
        result[i] ^= key
        key = (key + inc) & 0xFF
        inc = (inc + 77) & 0xFF
    return bytes(result)

def decode_file_data(data, file_offset):
    key = (file_offset >> 1) | 8
    return bytes(b ^ key for b in data)

def extract_archive(dat_path, output_dir):
    with open(dat_path, "rb") as f:
        raw = f.read()

    if len(raw) < 2:
        print(f"  {dat_path}: too small, skipping")
        return 0

    num_entries = struct.unpack_from("<H", raw, 0)[0]
    print(f"  {dat_path}: {num_entries} entries")

    table_size = num_entries * 0x10c
    if len(raw) < 2 + table_size:
        print(f"  {dat_path}: truncated, skipping")
        return 0

    table = decode_entry_table(raw[2:2 + table_size])

    count = 0
    for i in range(num_entries):
        entry = table[i * 0x10c:(i + 1) * 0x10c]
        filename = entry[:0x104].split(b'\x00')[0].decode('ascii', errors='replace')
        file_size = struct.unpack_from("<I", entry, 0x104)[0]
        file_offset = struct.unpack_from("<I", entry, 0x108)[0]

        if file_offset + file_size > len(raw):
            print(f"    skip {filename}: out of bounds")
            continue

        # Decode file data
        encoded = raw[file_offset:file_offset + file_size]
        decoded = decode_file_data(encoded, file_offset)

        # Create directory structure
        out_path = os.path.join(output_dir, filename.replace('\\', '/'))
        os.makedirs(os.path.dirname(out_path), exist_ok=True)

        with open(out_path, "wb") as f:
            f.write(decoded)

        count += 1
        if count <= 5:
            print(f"    extracted: {filename} ({file_size} bytes)")

    if count > 5:
        print(f"    ... and {count - 5} more files")

    return count

def main():
    game_dir = sys.argv[1] if len(sys.argv) > 1 else "."
    output_dir = os.path.join(game_dir, "data")

    archives = [
        "daybreak00.dat", "daybreak02.dat", "daybreak04.dat",
        "daybreak05.dat", "daybreak06.dat", "daybreak07.dat",
    ]

    print(f"Extracting archives from: {game_dir}")
    print(f"Output directory: {output_dir}")
    print()

    total = 0
    for arch in archives:
        path = os.path.join(game_dir, arch)
        if os.path.exists(path):
            total += extract_archive(path, output_dir)
        else:
            print(f"  {arch}: not found, skipping")

    print(f"\nTotal files extracted: {total}")
    print(f"Files are in: {output_dir}")
    print(f"\nNow run daybreak_launcher.exe to start the game with direct file mode.")

if __name__ == "__main__":
    main()
