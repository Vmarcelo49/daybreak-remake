#!/usr/bin/env python3
"""
Extract AND convert files from daybreakXX.dat archives.

Two-step process:
  1. Extract .dat → .cnv files (XOR-decoded)
  2. Convert .cnv → original format (.bmp / .wav)

Conversion rules (reverse-engineered from FUN_00661d10, FUN_00665020, FUN_00665e70):
  - .cnv with "BM" magic → rename to .bmp (it's a standard BMP file)
  - .cnv with audio header (starts with 01 00) → convert to .wav (add RIFF header)
  - .cnv with other content → leave as .cnv (unknown format)
  - .ogg, .sfl, .mpg, .dat, .sav → keep as-is (already original format)

The game (FUN_00661d10) works like this:
  1. Takes filename "data/title/back00.bmp"
  2. Changes extension to .cnv → "data/title/back00.cnv"
  3. Loads .cnv from archive
  4. If .cnv starts with "BM" → treats as BMP (FUN_00665020)
  5. If .cnv starts with audio header → treats as WAV

So for direct file mode to work, we need:
  - data/title/back00.bmp (actual BMP file, not .cnv)
  - data/voice/.../xxx.wav (actual WAV file, not .cnv)

This script does the conversion during extraction so the hook can
load the original-format files directly from disk.

Usage:
    python3 extract_dat.py [path_to_game_folder]
"""
import os, struct, sys, wave, io

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

def cnv_to_wav(cnv_data):
    """Convert .cnv audio format to standard WAV.
    
    .cnv audio header (16 bytes):
      offset 0: uint16 channels
      offset 2: uint16 unknown (always 1?)
      offset 4: uint32 sample_rate
      offset 8: uint32 byte_rate
      offset 12: uint16 block_align
      offset 14: uint16 bits_per_sample
    Followed by raw PCM data.
    
    WAV format:
      RIFF header (12 bytes)
      fmt chunk (24 bytes)
      data chunk header (8 bytes) + PCM data
    """
    if len(cnv_data) < 16:
        return None
    
    channels = struct.unpack_from("<H", cnv_data, 0)[0]
    sample_rate = struct.unpack_from("<I", cnv_data, 4)[0]
    byte_rate = struct.unpack_from("<I", cnv_data, 8)[0]
    block_align = struct.unpack_from("<H", cnv_data, 12)[0]
    bits_per_sample = struct.unpack_from("<H", cnv_data, 14)[0]
    
    pcm_data = cnv_data[16:]
    data_size = len(pcm_data)
    
    # Build WAV file
    wav = io.BytesIO()
    
    # RIFF header
    wav.write(b'RIFF')
    wav.write(struct.pack('<I', 36 + data_size))  # file size - 8
    wav.write(b'WAVE')
    
    # fmt chunk
    wav.write(b'fmt ')
    wav.write(struct.pack('<I', 16))  # chunk size
    wav.write(struct.pack('<H', 1))   # audio format = PCM
    wav.write(struct.pack('<H', channels))
    wav.write(struct.pack('<I', sample_rate))
    wav.write(struct.pack('<I', byte_rate))
    wav.write(struct.pack('<H', block_align))
    wav.write(struct.pack('<H', bits_per_sample))
    
    # data chunk
    wav.write(b'data')
    wav.write(struct.pack('<I', data_size))
    wav.write(pcm_data)
    
    return wav.getvalue()

def convert_cnv_file(filename, cnv_data):
    """Convert .cnv data to original format.
    
    Returns (new_filename, converted_data) or (filename, cnv_data) if no conversion needed.
    """
    if len(cnv_data) < 4:
        return filename, cnv_data
    
    # Check if it's a BMP (magic "BM" = 0x42 0x4D)
    if cnv_data[:2] == b'BM':
        # .cnv is actually a BMP — just change extension
        new_name = filename[:-4] + '.bmp' if filename.endswith('.cnv') else filename
        return new_name, cnv_data
    
    # Check if it's audio .cnv (starts with 01 00 = channels=1)
    if cnv_data[0] == 0x01 and cnv_data[1] == 0x00 and len(cnv_data) >= 16:
        # Try to parse as audio header
        sample_rate = struct.unpack_from("<I", cnv_data, 4)[0]
        bits = struct.unpack_from("<H", cnv_data, 14)[0]
        # Sanity check: sample_rate should be 44100 or 22050, bits should be 16
        if sample_rate in (44100, 22050, 48000) and bits in (8, 16):
            wav_data = cnv_to_wav(cnv_data)
            if wav_data:
                new_name = filename[:-4] + '.wav' if filename.endswith('.cnv') else filename
                return new_name, wav_data
    
    # Unknown format — keep as .cnv
    return filename, cnv_data

def extract_archive(dat_path, output_dir):
    """Extract and convert all files from one .dat archive."""
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
    converted = 0
    errors = 0
    for i in range(num_entries):
        entry_off = i * 0x10c
        entry = table[entry_off:entry_off + 0x10c]

        filename = entry[:0x104].split(b'\x00')[0].decode('ascii', errors='replace')
        file_size = struct.unpack_from("<I", entry, 0x104)[0]
        file_offset = struct.unpack_from("<I", entry, 0x108)[0]

        if file_size == 0 or file_size > 100 * 1024 * 1024:
            errors += 1
            continue
        if file_offset < 2 + table_size:
            errors += 1
            continue
        if file_offset + file_size > len(raw):
            errors += 1
            continue

        encoded = raw[file_offset:file_offset + file_size]
        try:
            decoded = decode_file_data(encoded, file_offset)
        except ValueError as e:
            print(f"    ERROR decoding {filename}: {e}")
            errors += 1
            continue

        # DON'T convert .cnv — the game opens .cnv files from disk.
        # Image .cnv files ARE BMPs (magic "BM") — game reads them as BMP.
        # Audio .cnv files have custom 16-byte header — game reads them natively.
        # Just extract as-is with .cnv extension.
        out_filename = filename
        out_data = decoded

        # Create directory structure
        safe_path = out_filename.replace('\\', '/').lstrip('/')
        if safe_path.startswith("data/"):
            parent_dir = os.path.dirname(output_dir)
            out_path = os.path.join(parent_dir, safe_path)
        else:
            out_path = os.path.join(output_dir, safe_path)
        out_dir = os.path.dirname(out_path)
        if out_dir:
            os.makedirs(out_dir, exist_ok=True)

        with open(out_path, "wb") as f:
            f.write(out_data)

        count += 1
        if count <= 5:
            ext_change = f" → {out_filename.rsplit('.', 1)[-1]}" if out_filename != filename else ""
            print(f"    extracted: {filename}{ext_change} ({file_size} bytes)")

    if count > 5:
        print(f"    ... and {count - 5} more files")
    if converted > 0:
        print(f"    Converted {converted} .cnv files to .bmp/.wav")
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

    print(f"Extracting and converting archives from: {game_dir}")
    print(f"Output directory: {output_dir}")
    print(f"Conversion: .cnv → .bmp (images), .cnv → .wav (audio)")
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
    
    # Count converted files
    bmp_count = 0
    wav_count = 0
    cnv_count = 0
    other_count = 0
    for root, dirs, files in os.walk(output_dir):
        for f in files:
            ext = f.rsplit('.', 1)[-1].lower() if '.' in f else ''
            if ext == 'bmp': bmp_count += 1
            elif ext == 'wav': wav_count += 1
            elif ext == 'cnv': cnv_count += 1
            else: other_count += 1
    
    print(f"\nFile summary:")
    print(f"  .bmp files: {bmp_count}")
    print(f"  .wav files: {wav_count}")
    print(f"  .cnv files: {cnv_count} (unconverted — unknown format)")
    print(f"  Other: {other_count} (.ogg, .sfl, .dat, .mpg, etc.)")
    print(f"\nNow run daybreak_launcher.exe to start the game with direct file mode.")

if __name__ == "__main__":
    main()
