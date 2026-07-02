#!/usr/bin/env python3
"""
Pack files back into daybreakXX.dat archive format.

Reverse of extract_dat.py — re-packs files (including modified ones) into
.dat archives with correct XOR encoding.

Usage:
    python3 dat_packer.py <input_directory> <output.dat>
    python3 dat_packer.py data/ daybreak00.dat

Format (reverse-engineered from FUN_00662d10, FUN_00663030):
  Header: uint16 num_entries
  Entry table: num_entries * 0x10c bytes (XOR-encoded)
  File data: XOR-encoded per file

  Entry struct (0x10c = 268 bytes):
    0x00  0x104  filename (null-terminated, Shift-JIS encoding)
    0x104 4     file_size (uint32 LE)
    0x108 4     file_offset (uint32 LE, from start of .dat)

  Entry table XOR:
    key=100, inc=100
    for each byte: byte ^= key; key=(key+inc)&0xFF; inc=(inc+77)&0xFF

  File data XOR:
    key = ((file_offset >> 1) & 0xFF) | 8  (constant per file)
    for each byte: byte ^= key

Workflow for modding:
  1. extract_dat.py .          → extract .dat to data/ folder (.cnv files)
  2. cnv_convert.py --batch data/  → convert .cnv → .bmp/.wav
  3. Edit .bmp/.wav files (Photoshop, Audacity, etc.)
  4. cnv_pack.py --batch data/     → convert .bmp/.wav → .cnv
  5. dat_packer.py data/ daybreak00.dat  → repack into .dat
  6. Replace original .dat with modified one
"""
import os, struct, sys

def encode_entry_table(data):
    """XOR-encode the entry table with evolving key."""
    key = 100
    inc = 100
    result = bytearray(data)
    for i in range(len(result)):
        result[i] ^= key
        key = (key + inc) & 0xFF
        inc = (inc + 77) & 0xFF
    return bytes(result)

def encode_file_data(data, file_offset):
    """XOR-encode file data with constant key per file."""
    key = ((file_offset >> 1) & 0xFF) | 8
    return bytes(b ^ key for b in data)

def encode_filename(filename):
    """Encode filename to Shift-JIS bytes, null-padded to 0x104 (260) bytes."""
    # Try Shift-JIS first (for Japanese characters), then ASCII
    for encoding in ('shift-jis', 'cp932', 'ascii'):
        try:
            name_bytes = filename.encode(encoding)
            break
        except (UnicodeEncodeError, LookupError):
            continue
    else:
        name_bytes = filename.encode('ascii', errors='replace')

    # Pad to 0x104 bytes with nulls
    if len(name_bytes) >= 0x104:
        name_bytes = name_bytes[:0x103] + b'\x00'
    else:
        name_bytes = name_bytes + b'\x00' * (0x104 - len(name_bytes))

    return name_bytes

def collect_files(input_dir):
    """Collect all files from input directory tree.

    Returns list of (filename_for_dat, file_path, file_data) tuples.
    Filenames are relative paths with forward slashes, including 'data/' prefix
    if the directory structure has it.
    """
    files = []

    # Check if input_dir itself is 'data/' or contains 'data/'
    # We want filenames inside .dat to start with "data/" or "movie/" etc.
    dir_name = os.path.basename(os.path.normpath(input_dir))

    for root, dirs, filenames in os.walk(input_dir):
        for f in sorted(filenames):
            full_path = os.path.join(root, f)
            # Get relative path from input_dir
            rel_path = os.path.relpath(full_path, input_dir)
            # Convert to forward slashes
            rel_path = rel_path.replace('\\', '/')

            # If input_dir is NOT 'data', prepend 'data/'
            if dir_name.lower() != 'data' and not rel_path.startswith('data/'):
                dat_filename = 'data/' + rel_path
            else:
                dat_filename = rel_path

            # Read file data
            with open(full_path, 'rb') as fp:
                file_data = fp.read()

            files.append((dat_filename, full_path, file_data))

    return files

def pack_archive(input_dir, output_path):
    """Pack all files from input_dir into a .dat archive."""
    files = collect_files(input_dir)

    if not files:
        print(f"ERROR: No files found in {input_dir}")
        return False

    print(f"Packing {len(files)} files into {output_path}")

    # Calculate offsets
    num_entries = len(files)
    table_size = num_entries * 0x10c
    data_start = 2 + table_size  # after num_entries + entry table

    # Build entry table and file data
    current_offset = data_start
    entries = []
    all_file_data = bytearray()

    for i, (dat_filename, file_path, file_data) in enumerate(files):
        file_size = len(file_data)

        # Build entry (0x10c = 268 bytes)
        name_bytes = encode_filename(dat_filename)
        entry = bytearray(name_bytes)  # 0x104 bytes
        entry += struct.pack('<I', file_size)    # 4 bytes: file_size
        entry += struct.pack('<I', current_offset)  # 4 bytes: file_offset

        entries.append(bytes(entry))

        # XOR-encode file data
        encoded_data = encode_file_data(file_data, current_offset)
        all_file_data += encoded_data

        if i < 5 or i >= len(files) - 3:
            print(f"  [{i+1}/{num_entries}] {dat_filename} ({file_size} bytes, offset 0x{current_offset:x})")
        elif i == 5:
            print(f"  ...")

        current_offset += file_size

    # Build entry table
    raw_table = b''.join(entries)
    encoded_table = encode_entry_table(raw_table)

    # Write .dat file
    with open(output_path, 'wb') as f:
        # Header: num_entries (uint16 LE)
        f.write(struct.pack('<H', num_entries))
        # Encoded entry table
        f.write(encoded_table)
        # Encoded file data
        f.write(all_file_data)

    total_size = 2 + len(encoded_table) + len(all_file_data)
    print(f"\nArchive created: {output_path}")
    print(f"  Entries: {num_entries}")
    print(f"  Table size: {len(encoded_table):,} bytes")
    print(f"  Data size: {len(all_file_data):,} bytes")
    print(f"  Total: {total_size:,} bytes")

    return True

def main():
    if len(sys.argv) < 3:
        print("Usage:")
        print(f"  {sys.argv[0]} <input_directory> <output.dat>")
        print(f"  {sys.argv[0]} data/ daybreak00.dat")
        print()
        print("Modding workflow:")
        print("  1. python3 extract_dat.py .              # extract .dat → .cnv")
        print("  2. python3 cnv_convert.py --batch data/  # .cnv → .bmp/.wav")
        print("  3. Edit .bmp/.wav files")
        print("  4. python3 cnv_pack.py --batch data/     # .bmp/.wav → .cnv")
        print("  5. python3 dat_packer.py data/ out.dat   # repack .dat")
        sys.exit(1)

    input_dir = sys.argv[1]
    output_path = sys.argv[2]

    if not os.path.isdir(input_dir):
        print(f"ERROR: {input_dir} is not a directory")
        sys.exit(1)

    pack_archive(input_dir, output_path)

if __name__ == "__main__":
    main()
