#!/usr/bin/env python3
"""
Extract all files from daybreakXX.dat archives into data/ folder.

Usage:
    python3 extract_dat.py [path_to_game_folder]

Format (reverse-engineered from FUN_00662d10, FUN_00663030):
  Header: uint16 num_entries
  Entry table: num_entries * 0x10c bytes (XOR-encoded)
  File data: XOR-encoded per file

  Entry struct (0x10c = 268 bytes):
    0x00  0x104  filename (null-terminated, Shift-JIS encoding for Japanese)
    0x104 4     file_size (uint32 LE)
    0x108 4     file_offset (uint32 LE)

  Entry table XOR:
    key=100, inc=100
    for each byte: byte ^= key; key=(key+inc)&0xFF; inc=(inc+77)&0xFF

  File data XOR:
    key = ((file_offset >> 1) & 0xFF) | 8  (constant per file)
    for each byte: byte ^= key

Filename encoding:
  Filenames inside .dat use Shift-JIS (Japanese Windows encoding).
  Some filenames contain Japanese characters (e.g., character names).
  On Windows, the filesystem uses UTF-16 internally, and CreateFileA
  with Shift-JIS strings works correctly. On Linux/Wine, we need to
  handle encoding carefully.
"""
import os, struct, sys, shutil

def decode_entry_table(data):
    """XOR-decode the entry table with evolving key."""
    key = 100
    inc = 100
    result = bytearray(data)
    for i in range(len(result)):
        result[i] ^= key
        key = (key + inc) & 0xFF
        inc = (inc + 77) & 0xFF
    return bytes(result)

def decode_file_data(data, file_offset):
    """XOR-decode file data with constant key per file."""
    key = ((file_offset >> 1) & 0xFF) | 8
    return bytes(b ^ key for b in data)

def safe_filename(raw_bytes):
    """Convert filename bytes to a filesystem-safe string.
    
    Filenames in .dat are Shift-JIS encoded. Try Shift-JIS first,
    then CP932 (Windows Japanese), then ASCII with replacement.
    
    For filesystem safety, replace characters that are invalid on Windows:
    \ / : * ? " < > |
    """
    # Try Shift-JIS (same as CP932 on Windows)
    for encoding in ('shift-jis', 'cp932', 'ascii'):
        try:
            name = raw_bytes.decode(encoding)
            break
        except (UnicodeDecodeError, LookupError):
            continue
    else:
        # Last resort: decode with errors='replace'
        name = raw_bytes.decode('ascii', errors='replace')
    
    # Replace characters that are invalid on Windows filesystems
    # The game uses / as path separator, which is fine
    # But some Japanese chars might cause issues on certain filesystems
    safe = name
    for char in '\\:*?"<>|':
        safe = safe.replace(char, '_')
    
    return safe

def extract_archive(dat_path, output_dir):
    """Extract all files from one .dat archive."""
    with open(dat_path, "rb") as f:
        raw = f.read()

    if len(raw) < 2:
        print(f"  {dat_path}: too small, skipping")
        return 0

    num_entries = struct.unpack_from("<H", raw, 0)[0]
    print(f"  {dat_path}: {num_entries} entries, {len(raw):,} bytes")

    table_size = num_entries * 0x10c
    if table_size > len(raw):
        print(f"  {dat_path}: entry table exceeds file size, skipping")
        return 0

    table = decode_entry_table(raw[2:2 + table_size])

    count = 0
    errors = 0
    for i in range(num_entries):
        entry_off = i * 0x10c
        entry = table[entry_off:entry_off + 0x10c]

        # Extract raw filename bytes (null-terminated)
        name_bytes = entry[:0x104].split(b'\x00')[0]
        
        # Decode filename (Shift-JIS for Japanese, ASCII for English)
        filename = safe_filename(name_bytes)
        
        file_size = struct.unpack_from("<I", entry, 0x104)[0]
        file_offset = struct.unpack_from("<I", entry, 0x108)[0]

        # Sanity checks
        if file_size == 0 or file_size > 100 * 1024 * 1024:
            errors += 1
            continue
        if file_offset < 2 + table_size:
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
            errors += 1
            continue

        # Create directory structure
        # Filenames inside .dat already include "data/" prefix
        safe_path = filename.replace('\\', '/').lstrip('/')
        if safe_path.startswith("data/"):
            parent_dir = os.path.dirname(output_dir)
            out_path = os.path.join(parent_dir, safe_path)
        else:
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
