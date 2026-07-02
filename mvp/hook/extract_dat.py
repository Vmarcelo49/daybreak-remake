#!/usr/bin/env python3
"""
Extract all files from daybreakXX.dat archives into data/ folder.

Usage:
    python3 extract_dat.py [path_to_game_folder]

This extracts all files from daybreak00-07.dat into a data/ subfolder,
so the game (with the hook DLL) can load them directly from disk.

Format (reverse-engineered from FUN_00662d10, FUN_00663030):

  File layout:
    0x00    2         num_entries (uint16 LE)
    0x02    N * 0x10c entry_table (XOR-encoded)
    0x02+N*0x10c     file_data (XOR-encoded per file)

  Entry struct (0x10c = 268 bytes):
    0x00  0x104  filename (null-terminated string)
    0x104 4     file_size (uint32 LE)
    0x108 4     file_offset (uint32 LE, from start of .dat)

  Entry table XOR (key evolves per byte):
    key=100, inc=100
    for each byte: byte ^= key; key=(key+inc)&0xFF; inc=(inc+77)&0xFF

  File data XOR (key is constant per file):
    key = ((file_offset >> 1) & 0xFF) | 8   ← MUST mask to byte first!
    for each byte: byte ^= key

  The (byte) cast in the original C code truncates to 8 bits:
    ((byte)(uVar1 >> 1) | 8)  =  ((uVar1 >> 1) & 0xFF) | 8
"""
import os, struct, sys

def decode_entry_table(data):
    """XOR-decode the entry table with evolving key."""
    key = 100  # 'd'
    inc = 100  # 'd'
    result = bytearray(data)
    for i in range(len(result)):
        result[i] ^= key
        key = (key + inc) & 0xFF
        inc = (inc + 77) & 0xFF  # 'M' = 77
    return bytes(result)

def decode_file_data(data, file_offset):
    """XOR-decode file data with constant key per file.

    Key = ((file_offset >> 1) & 0xFF) | 8
    The & 0xFF is critical — without it, key can exceed 255.
    """
    key = ((file_offset >> 1) & 0xFF) | 8
    return bytes(b ^ key for b in data)

def extract_archive(dat_path, output_dir):
    """Extract all files from one .dat archive."""
    with open(dat_path, "rb") as f:
        raw = f.read()

    if len(raw) < 2:
        print(f"  {dat_path}: too small, skipping")
        return 0

    num_entries = struct.unpack_from("<H", raw, 0)[0]
    print(f"  {dat_path}: {num_entries} entries, {len(raw):,} bytes")

    # Sanity check: 7677 entries * 268 bytes = ~2MB just for the table
    table_size = num_entries * 0x10c
    if table_size > len(raw):
        print(f"  {dat_path}: entry table exceeds file size, skipping")
        return 0

    # Decode entry table
    table = decode_entry_table(raw[2:2 + table_size])

    count = 0
    errors = 0
    for i in range(num_entries):
        entry_off = i * 0x10c
        entry = table[entry_off:entry_off + 0x10c]

        # Parse entry
        filename = entry[:0x104].split(b'\x00')[0].decode('ascii', errors='replace')
        file_size = struct.unpack_from("<I", entry, 0x104)[0]
        file_offset = struct.unpack_from("<I", entry, 0x108)[0]

        # Sanity checks
        if file_size == 0 or file_size > 100 * 1024 * 1024:  # > 100MB = suspicious
            errors += 1
            continue
        if file_offset < 2 + table_size:  # offset inside header/table
            errors += 1
            continue
        if file_offset + file_size > len(raw):
            errors += 1
            continue

        # Decode file data
        encoded = raw[file_offset:file_offset + file_size]
        try:
            decoded = decode_file_data(encoded, file_offset)
        except ValueError as e:
            print(f"    ERROR decoding {filename}: {e}")
            print(f"      file_offset=0x{file_offset:x}, key=0x{((file_offset>>1)&0xFF)|8:02x}")
            errors += 1
            continue

        # Create directory structure
        safe_path = filename.replace('\\', '/').lstrip('/')
        out_path = os.path.join(output_dir, safe_path)
        out_dir = os.path.dirname(out_path)
        if out_dir:
            os.makedirs(out_dir, exist_ok=True)

        with open(out_path, "wb") as f:
            f.write(decoded)

        count += 1
        if count <= 5:
            print(f"    extracted: {filename} ({file_size} bytes)")

    if count > 5:
        print(f"    ... and {count - 5} more files")
    if errors > 0:
        print(f"    {errors} entries skipped (invalid)")

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
