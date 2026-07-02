#!/usr/bin/env python3
"""
Convert .cnv files to their original formats (.bmp for images, .wav for audio).

Usage:
    python3 cnv_convert.py <input.cnv> [output.bmp|output.wav]
    python3 cnv_convert.py --batch <directory>     # convert all .cnv in directory

CNV Image Format (reverse-engineered from FUN_00665e70):
    Offset 0  (1 byte):  bits per pixel (8, 16, 24, 32)
    Offset 1  (4 bytes): field_1 (usually same as width)
    Offset 5  (4 bytes): height
    Offset 9  (4 bytes): width
    Offset 13 (4 bytes): compressed_size (0 = uncompressed)
    Offset 17: pixel data (width * height * bpp/8 bytes if uncompressed)

CNV Audio Format (reverse-engineered from FUN_00665020 audio path):
    Offset 0  (2 bytes): channels
    Offset 2  (2 bytes): unknown (always 1)
    Offset 4  (4 bytes): sample_rate
    Offset 8  (4 bytes): byte_rate
    Offset 12 (2 bytes): block_align
    Offset 14 (2 bytes): bits_per_sample
    Offset 16: raw PCM data

Detection:
    - Image .cnv: first byte is 8, 16, 24, or 32 (bpp)
                  AND offset 13 reads as 0 (uncompressed) or valid compressed size
    - Audio .cnv: first 2 bytes are 01 00 or 02 00 (channels)
                  AND offset 4 reads as 44100, 22050, or 48000 (sample_rate)
"""
import os, struct, sys, wave, io

def is_audio_cnv(data):
    """Check if .cnv data is audio format."""
    if len(data) < 16:
        return False
    channels = struct.unpack_from("<H", data, 0)[0]
    sample_rate = struct.unpack_from("<I", data, 4)[0]
    bits = struct.unpack_from("<H", data, 14)[0]
    return channels in (1, 2) and sample_rate in (22050, 44100, 48000) and bits in (8, 16)

def is_image_cnv(data):
    """Check if .cnv data is image format."""
    if len(data) < 17:
        return False
    bpp = data[0]
    if bpp not in (8, 16, 24, 32):
        return False
    field1 = struct.unpack_from("<I", data, 1)[0]
    height = struct.unpack_from("<I", data, 5)[0]
    width = struct.unpack_from("<I", data, 9)[0]
    compressed = struct.unpack_from("<I", data, 13)[0]
    
    # Sanity check: dimensions should be reasonable
    if width == 0 or height == 0 or width > 8192 or height > 8192:
        return False
    
    # If uncompressed, check pixel data size matches
    if compressed == 0:
        if bpp >= 24:
            expected = width * height * 4
        else:
            expected = width * height * bpp // 8
        actual = len(data) - 17
        return actual == expected
    
    # Compressed: just check we have enough data
    return len(data) > 17 + compressed

def convert_audio_cnv(data):
    """Convert audio .cnv to WAV format."""
    channels = struct.unpack_from("<H", data, 0)[0]
    sample_rate = struct.unpack_from("<I", data, 4)[0]
    byte_rate = struct.unpack_from("<I", data, 8)[0]
    block_align = struct.unpack_from("<H", data, 12)[0]
    bits = struct.unpack_from("<H", data, 14)[0]
    
    pcm = data[16:]
    
    wav = bytearray()
    # RIFF header
    wav += b'RIFF'
    wav += struct.pack('<I', 36 + len(pcm))
    wav += b'WAVE'
    # fmt chunk
    wav += b'fmt '
    wav += struct.pack('<I', 16)
    wav += struct.pack('<H', 1)  # PCM
    wav += struct.pack('<H', channels)
    wav += struct.pack('<I', sample_rate)
    wav += struct.pack('<I', byte_rate)
    wav += struct.pack('<H', block_align)
    wav += struct.pack('<H', bits)
    # data chunk
    wav += b'data'
    wav += struct.pack('<I', len(pcm))
    wav += pcm
    
    return bytes(wav)

def convert_image_cnv(data):
    """Convert image .cnv to BMP format."""
    bpp = data[0]
    field1 = struct.unpack_from("<I", data, 1)[0]
    height = struct.unpack_from("<I", data, 5)[0]
    width = struct.unpack_from("<I", data, 9)[0]
    compressed = struct.unpack_from("<I", data, 13)[0]
    
    if compressed != 0:
        print(f"  WARNING: Compressed .cnv not supported yet (compressed_size={compressed})")
        return None
    
    pixel_data = data[17:]
    
    # Calculate BMP row size (padded to 4 bytes)
    bytes_per_pixel = bpp // 8
    if bpp >= 24:
        bytes_per_pixel = 4  # D3D uses 4 bytes for 24+ bpp
    
    row_size_raw = width * bytes_per_pixel
    row_size = (row_size_raw + 3) & ~3  # Pad to 4 bytes
    pixel_data_size = row_size * height
    
    # Color table for 8bpp
    color_table_size = 0
    if bpp == 8:
        color_table_size = 256 * 4
    
    bmp_header_size = 14 + 40 + color_table_size
    bmp_file_size = bmp_header_size + pixel_data_size
    
    bmp = bytearray()
    
    # BMP file header (14 bytes)
    bmp += b'BM'
    bmp += struct.pack('<I', bmp_file_size)
    bmp += struct.pack('<HH', 0, 0)
    bmp += struct.pack('<I', bmp_header_size)
    
    # DIB header (BITMAPINFOHEADER, 40 bytes)
    bmp += struct.pack('<I', 40)
    bmp += struct.pack('<i', width)
    bmp += struct.pack('<i', height)  # positive = bottom-up
    bmp += struct.pack('<H', 1)  # planes
    bmp += struct.pack('<H', bpp if bpp in (8, 16, 24, 32) else 32)
    bmp += struct.pack('<I', 0)  # no compression
    bmp += struct.pack('<I', pixel_data_size)
    bmp += struct.pack('<i', 2835)  # 72 DPI
    bmp += struct.pack('<i', 2835)
    bmp += struct.pack('<I', 256 if bpp == 8 else 0)
    bmp += struct.pack('<I', 0)
    
    # Color table for 8bpp (would need to extract from .cnv — skip for now)
    if bpp == 8:
        # Fill with grayscale palette as placeholder
        for i in range(256):
            bmp += bytes([i, i, i, 0])
    
    # Pixel data — .cnv is top-down, BMP is bottom-up
    # Flip rows vertically
    src_row_size = width * bytes_per_pixel
    for row in range(height - 1, -1, -1):
        row_data = pixel_data[row * src_row_size:(row + 1) * src_row_size]
        # Pad row if needed
        if len(row_data) < row_size:
            row_data += b'\x00' * (row_size - len(row_data))
        bmp += row_data
    
    return bytes(bmp)

def convert_cnv(input_path, output_path=None):
    """Convert a single .cnv file. Returns output path or None on failure."""
    with open(input_path, 'rb') as f:
        data = f.read()
    
    # Detect format
    if is_audio_cnv(data):
        if output_path is None:
            output_path = os.path.splitext(input_path)[0] + '.wav'
        converted = convert_audio_cnv(data)
        if converted:
            with open(output_path, 'wb') as f:
                f.write(converted)
            print(f"  {os.path.basename(input_path)} → {os.path.basename(output_path)} (audio, {len(converted)} bytes)")
            return output_path
    elif is_image_cnv(data):
        if output_path is None:
            output_path = os.path.splitext(input_path)[0] + '.bmp'
        converted = convert_image_cnv(data)
        if converted:
            with open(output_path, 'wb') as f:
                f.write(converted)
            print(f"  {os.path.basename(input_path)} → {os.path.basename(output_path)} (image, {len(converted)} bytes)")
            return output_path
    else:
        print(f"  {os.path.basename(input_path)} → UNKNOWN FORMAT (first 4 bytes: {data[:4].hex()})")
        return None
    
    return None

def batch_convert(directory):
    """Convert all .cnv files in a directory tree."""
    count = 0
    failed = 0
    for root, dirs, files in os.walk(directory):
        for f in files:
            if f.lower().endswith('.cnv'):
                input_path = os.path.join(root, f)
                result = convert_cnv(input_path)
                if result:
                    count += 1
                else:
                    failed += 1
    print(f"\nConverted: {count}, Failed: {failed}")
    return count

def main():
    if len(sys.argv) < 2:
        print("Usage:")
        print(f"  {sys.argv[0]} <input.cnv> [output]")
        print(f"  {sys.argv[0]} --batch <directory>")
        sys.exit(1)
    
    if sys.argv[1] == '--batch':
        directory = sys.argv[2] if len(sys.argv) > 2 else '.'
        print(f"Batch converting .cnv files in: {directory}")
        batch_convert(directory)
    else:
        input_path = sys.argv[1]
        output_path = sys.argv[2] if len(sys.argv) > 2 else None
        convert_cnv(input_path, output_path)

if __name__ == "__main__":
    main()
