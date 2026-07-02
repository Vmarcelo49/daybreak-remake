# Shaders — D3DX Effects extracted from original DaybreakDX.exe

## Source

The original binary contains **10 D3DX compiled effects** embedded as data, loaded by `CreateAllShaders` (FUN_0064ff80).

| File | Original address | Size (bytes) |
|------|------------------|--------------|
| `effect_0.bin` | `0x006a5f68` | 3499 |
| `effect_1.bin` | `0x006a6cd8` | 3640 |
| `effect_2.bin` | `0x006a7b10` | 812 |
| `effect_3.bin` | `0x006a7e40` | 1964 |
| `effect_4.bin` | `0x006a85f0` | 1744 |
| `effect_5.bin` | `0x006a8cc0` | 1920 |
| `effect_6.bin` | `0x006a9440` | 1932 |
| `effect_7.bin` | (to extract) | (to extract) |
| `effect_8.bin` | (to extract) | (to extract) |
| `effect_9.bin` | (to extract) | (to extract) |

## How to extract

The shaders are stored in the `.rdata` section of `DaybreakDX.exe`. To extract:

### Option 1: Use a hex editor

1. Open `DaybreakDX.exe` in a hex editor (e.g., HxD on Windows, bless on Linux)
2. Go to address `0x006a5f68 - 0x00400000 = 0x2a5f68` (file offset = virtual address - image base)
3. Select 3499 bytes
4. Save as `effect_0.bin`
5. Repeat for the other 6 known addresses

### Option 2: Python script

```python
# extract_shaders.py
import os

# Format: (output_name, file_offset, size)
# file_offset = virtual_address - 0x400000 (image base)
SHADERS = [
    ("effect_0.bin", 0x2a5f68, 3499),
    ("effect_1.bin", 0x2a6cd8, 3640),
    ("effect_2.bin", 0x2a7b10, 812),
    ("effect_3.bin", 0x2a7e40, 1964),
    ("effect_4.bin", 0x2a85f0, 1744),
    ("effect_5.bin", 0x2a8cc0, 1920),
    ("effect_6.bin", 0x2a9440, 1932),
    # effect_7, 8, 9: addresses not yet extracted from CreateAllShaders
]

with open("DaybreakDX.exe", "rb") as f:
    exe = f.read()

for name, offset, size in SHADERS:
    with open(name, "wb") as f:
        f.write(exe[offset:offset+size])
    print(f"Extracted {name}: {size} bytes")
```

### Option 3: From MCP (next session)

If the MCP tunnel is reopened, the extraction agent can read each shader via `read_memory`:

```bash
python3 /home/z/my-project/scripts/ghidra_mcp.py "read_memory" \
  '{"address":"0x006a5f68","size":16}' \
  "/tmp/shader_0_chunk.txt"
```

But this is slow (16 bytes per call) — for 3499 bytes, would need 219 calls. Better to use the PE file directly.

## License

These compiled shader effects are copyright Twilight Frontier / 07th Expansion. They are extracted here under fair use for the purpose of interoperability with the original game.

**Do not redistribute** the shaders separately — only as part of this decompilation project.
