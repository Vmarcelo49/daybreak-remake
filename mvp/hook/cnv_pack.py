#!/usr/bin/env python3
"""
Convert .bmp/.wav files back to .cnv format.

Reverse of cnv_convert.py — packs edited assets back into game's .cnv format.

Usage:
    python3 cnv_pack.py <input.bmp|input.wav> [output.cnv]
    python3 cnv_pack.py --batch <directory>     # convert all .bmp/.wav in directory

CNV Image Format (17-byte header + pixel data):
    Offset 0  (1 byte):  bits per pixel (8/16/24/32)
    Offset 1  (4 bytes): field_1 (same as width)
    Offset 5  (4 bytes): height
    Offset 9  (4 bytes): width
    Offset 13 (4 bytes): compressed_size (0 = uncompressed)
    Offset 17: pixel data (BMP pixel data, flipped top-down)

CNV Audio Format (16-byte header + PCM data):
    Offset 0  (2 bytes): channels
    Offset 2  (2 bytes): unknown (always 1)
    Offset 4  (4 bytes): sample_rate
    Offset 8  (4 bytes): byte_rate
    Offset 12 (2 bytes): block_align
    Offset 14 (2 bytes): bits_per_sample
    Offset 16: raw PCM data
"""
import os, struct, sys, wave

def bmp_to_cnv(bmp_data):
    """Convert BMP file data to CNV image format."""
    if len(bmp_data) < 54 or bmp_data[:2] != b'BM':
        return None

    # Parse BMP header
    dib_header_size = struct.unpack_from("<I", bmp_data, 14)[0]
    width = struct.unpack_from("<i", bmp_data, 18)[0]
    height = struct.unpack_from("<i", bmp_data, 22)[0]
    bpp = struct.unpack_from("<H", bmp_data, 28)[0]
    compression = struct.unpack_from("<I", bmp_data, 30)[0]
    pixel_offset = struct.unpack_from("<I", bmp_data, 10)[0]

    if compression != 0:
        print(f"  ERROR: Compressed BMP not supported (compression={compression})")
        return None

    # For 24bpp BMP, D3D uses 32bpp (4 bytes per pixel)
    cnv_bpp = 32 if bpp >= 24 else bpp

    # Calculate row sizes
    bytes_per_pixel = bpp // 8
    if bpp >= 24:
        bytes_per_pixel = 4  # D3D always uses 4 bytes for 24+ bpp

    # BMP is bottom-up; .cnv is top-down
    bmp_row_size = ((width * (bpp // 8) + 3) & ~3)  # BMP rows padded to 4 bytes
    pixel_data = bmp_data[pixel_offset:]

    # Build CNV
    cnv = bytearray()

    # Header (17 bytes)
    cnv.append(cnv_bpp)                           # bpp (1 byte)
    cnv += struct.pack('<I', width)                # field_1 (4 bytes)
    cnv += struct.pack('<I', abs(height))          # height (4 bytes)
    cnv += struct.pack('<I', width)                # width (4 bytes)
    cnv += struct.pack('<I', 0)                    # compressed_size = 0 (4 bytes)

    # Pixel data — CNV is bottom-up (same as BMP), so copy directly
    h = abs(height)
    src_bpp = bpp // 8
    for row in range(h):
        row_start = row * bmp_row_size
        if bpp >= 24:
            # Convert RGB/BGR to RGBA/BGRA (4 bytes per pixel)
            for x in range(width):
                idx = row_start + x * (bpp // 8)
                if bpp == 32:
                    b, g, r, a = pixel_data[idx:idx+4]
                    cnv += bytes([b, g, r, a])
                elif bpp == 24:
                    b, g, r = pixel_data[idx:idx+3]
                    cnv += bytes([b, g, r, 0xFF])  # opaque alpha
        else:
            # 8/16 bpp: copy raw
            row_data = pixel_data[row_start:row_start + width * src_bpp]
            cnv += row_data

    return bytes(cnv)

def wav_to_cnv(wav_data):
    """Convert WAV file data to CNV audio format."""
    if len(wav_data) < 44 or wav_data[:4] != b'RIFF':
        return None

    # Parse WAV header
    channels = struct.unpack_from("<H", wav_data, 22)[0]
    sample_rate = struct.unpack_from("<I", wav_data, 24)[0]
    byte_rate = struct.unpack_from("<I", wav_data, 28)[0]
    block_align = struct.unpack_from("<H", wav_data, 32)[0]
    bits = struct.unpack_from("<H", wav_data, 34)[0]

    # Find data chunk
    pos = 36
    pcm_data = None
    while pos < len(wav_data) - 8:
        chunk_id = wav_data[pos:pos+4]
        chunk_size = struct.unpack_from("<I", wav_data, pos+4)[0]
        if chunk_id == b'data':
            pcm_data = wav_data[pos+8:pos+8+chunk_size]
            break
        pos += 8 + chunk_size

    if pcm_data is None:
        print("  ERROR: No data chunk in WAV")
        return None

    # Build CNV
    cnv = bytearray()
    cnv += struct.pack('<H', channels)       # channels
    cnv += struct.pack('<H', 1)              # unknown (always 1)
    cnv += struct.pack('<I', sample_rate)    # sample_rate
    cnv += struct.pack('<I', byte_rate)      # byte_rate
    cnv += struct.pack('<H', block_align)    # block_align
    cnv += struct.pack('<H', bits)           # bits_per_sample
    cnv += pcm_data                          # raw PCM

    return bytes(cnv)

def convert_to_cnv(input_path, output_path=None):
    """Convert .bmp or .wav to .cnv. Returns output path or None."""
    with open(input_path, 'rb') as f:
        data = f.read()

    ext = os.path.splitext(input_path)[1].lower()
    converted = None

    if ext == '.bmp':
        if output_path is None:
            output_path = os.path.splitext(input_path)[0] + '.cnv'
        converted = bmp_to_cnv(data)
        if converted:
            print(f"  {os.path.basename(input_path)} → {os.path.basename(output_path)} (image, {len(converted)} bytes)")
    elif ext == '.wav':
        if output_path is None:
            output_path = os.path.splitext(input_path)[0] + '.cnv'
        converted = wav_to_cnv(data)
        if converted:
            print(f"  {os.path.basename(input_path)} → {os.path.basename(output_path)} (audio, {len(converted)} bytes)")
    else:
        print(f"  {os.path.basename(input_path)} → SKIP (not .bmp or .wav)")
        return None

    if converted:
        with open(output_path, 'wb') as f:
            f.write(converted)
        return output_path
    return None

def batch_convert(directory):
    """Convert all .bmp and .wav files in a directory tree to .cnv."""
    count = 0
    failed = 0
    for root, dirs, files in os.walk(directory):
        for f in sorted(files):
            ext = f.lower().rsplit('.', 1)[-1] if '.' in f else ''
            if ext in ('bmp', 'wav'):
                input_path = os.path.join(root, f)
                result = convert_to_cnv(input_path)
                if result:
                    count += 1
                else:
                    failed += 1
    print(f"\nConverted: {count}, Failed: {failed}")
    return count

def main():
    if len(sys.argv) < 2:
        print("Usage:")
        print(f"  {sys.argv[0]} <input.bmp|input.wav> [output.cnv]")
        print(f"  {sys.argv[0]} --batch <directory>")
        sys.exit(1)

    if sys.argv[1] == '--batch':
        directory = sys.argv[2] if len(sys.argv) > 2 else '.'
        print(f"Batch converting .bmp/.wav → .cnv in: {directory}")
        batch_convert(directory)
    else:
        input_path = sys.argv[1]
        output_path = sys.argv[2] if len(sys.argv) > 2 else None
        convert_to_cnv(input_path, output_path)

if __name__ == "__main__":
    main()
