# DaybreakDX.exe — reverse-engineering findings and port notes

This is a historical RE notebook for the original 2007 executable, not a current
DX9 implementation guide. `DaybreakDX.exe` (2.8 MB) was analyzed with radare2
5.9.8 (`remake/scripts/r2.sh`). DX9/D3DX claims below describe the original
binary; the current product is `remake/foundation/` (SDL3 + WebGPU), and the old
`remake/src/` remake tree was deleted in Phase 5. Current parser and runtime
claims should be checked against foundation source and `remake/docs/decisions.md`.

## 1. PE header

| Field         | Value                                            |
|---------------|--------------------------------------------------|
| Format        | PE32 (32-bit), Intel i386                        |
| Image base    | `0x00400000`                                     |
| Subsystem     | Windows GUI                                      |
| Compiled      | `Wed Jul 11 09:04:45 2007`                       |
| PDB path      | `D:\nonotaro\works\あべし\Daybreak.pdb`            |
| Version       | `ver1.11` (string at `.rdata`)                   |
| Window class  | `HigurashiDaybreak`                              |
| Stripped      | **no** (has symbols + line numbers)              |
| NX (DEP)      | no                                               |
| ASLR          | no (fixed base)                                  |

## 2. PE sections

```
.text   0x00401000   0x2a0000   r-x   (code, 2.7 MB)
.rdata  0x006a1000   0x016000   r--   (read-only data, strings, IAT)
.data   0x006b7000   0x023000   rw-   (globals)
.rsrc   0x006da000   0x001000   r--   (resources)
```

## 3. Imported DLLs

| DLL           | Purpose                                                 |
|---------------|---------------------------------------------------------|
| `KERNEL32.dll`| file I/O, sync, memory                                  |
| `USER32.dll`  | window, message box, input                              |
| `GDI32.dll`   | 2D drawing                                              |
| `d3d9.dll`    | Direct3D 9 (rendering)                                  |
| `d3dx9_25.dll`| D3DX March 2006 — `D3DXLoadMeshHierarchyFromXA`, etc.  |
| `DINPUT8.dll` | DirectInput 8 (keyboard / joystick / gamepad)          |
| `WINMM.dll`   | Windows Multimedia (audio playback)                    |
| `ole32.dll`   | COM                                                     |
| `OLEAUT32.dll`| COM automation                                          |
| `IMM32.dll`   | Input Method Manager (Japanese text input)             |

**Note**: the game ships with `d3dx9_25.dll` (DX9 March 2006 SDK). The foundation does not link any D3DX — it parses `.X` itself (`foundation/src/assets/xmodel.h`: `xm::loadMemory`, `xmodel.h:267`) on the SDL3 + WebGPU path — so there is no `d3dx9_43` import to pick. The DLL version only matters to the frozen DX9 reference bank under `remake/tests/parity-baseline/`, not to what we ship.

## 4. .DAT parser — confirmed bit-exact match

### 4.1 Bundle .DAT files (the `daybreakNN.dat` family)

Located at: **`fcn.00662d10`** (function starts at `0x00662d10`, contains the constants `268`, `100`, `77`).

Decompiled flow:

```c
// Read 2-byte numFiles (uint16 LE)
ReadFile(hFile, &numFiles, 2, ...);

// Allocate numFiles * 268 bytes
uint8_t* table = malloc(numFiles * 268);

// Read encrypted table
ReadFile(hFile, table, numFiles * 268, ...);

// Decrypt table (counter=100, key=100, increment=77 — hardcoded to index=0)
uint8_t key     = 100;       // 0x64   ← matches Go's (100*(0+1) + 0) & 0xff
uint8_t counter = 100;       // 0x64   ← matches Go's (100 + 0*77) & 0xff
for (size_t i = 0; i < numFiles * 268; ++i) {
    table[i] ^= key;
    key     = (key     + counter) & 0xff;   // matches Go
    counter = (counter + 77)    & 0xff;     // matches Go (add eax, 0x4d)
}

// Parse entries
for (size_t i = 0; i < numFiles; ++i) {
    uint8_t* entry = table + i * 268;
    char*    filename = entry + 0;       // 260 bytes (Shift-JIS, null-padded)
    uint32_t length   = *(uint32_t*)(entry + 0x104);   // 260
    uint32_t offset   = *(uint32_t*)(entry + 0x108);   // 264
    add_to_entries(filename, length, offset);
}
```

The original uses entry size 268, key/counter 100, increment 77 (`+ 0x4D`),
and fields `filename@0`, `length@260`, `offset@264`. These are the format
facts to compare with the current parser; this RE note alone is not a present-day
runtime verification claim.

### 4.2 Standalone .DAT files (e.g. `data/effect/%03d.dat`)

Located at: **`fcn.00662a74`** (contains `shr ecx, 1; or ecx, 8`).

```c
// Read the whole file
DWORD filesize = GetFileSize(hFile, NULL);
uint8_t* buf = malloc(filesize);
ReadFile(hFile, buf, filesize, ...);

// Compute key from a stored offset field (struct +0x108)
uint32_t offset = bundle->offset_field;     // 0x108
uint8_t  key    = ((offset >> 1) & 0xff) | 0x08;   // ← matches Go's GetFileKey

// XOR every byte with the single key
for (DWORD i = 0; i < filesize; ++i) {
    buf[i] ^= key;
}
```

The original's standalone-file key formula is `((offset >> 1) & 0xff) | 0x08`.
Compare with `remake/foundation/src/assets/dat_crypto.cpp` for the port implementation.

### 4.3 Bootstrap

`fcn.0064d250` at `0x64d403` registers six bundles:

```
daybreak00.dat   → global @ 0x6ca830
daybreak02.dat   → global @ 0x6ca834
daybreak04.dat   → global @ 0x6ca838 (inferred from pattern)
daybreak05.dat   → ...
daybreak06.dat   → ...
daybreak07.dat   → ...
```

(All six strings appear sequentially at `0x6a5598`–`0x6a55e8` in `.rdata`.)

Note: `daybreak01.dat`, `daybreak03.dat` are skipped — likely removed between Daybreak and Daybreak Kai.

## 5. Filesystem layout (from strings)

### Bundle .DAT (6 main bundles, loaded at startup)
```
daybreak00.dat   daybreak02.dat   daybreak04.dat
daybreak05.dat   daybreak06.dat   daybreak07.dat
```

### Standalone .DAT (per-asset)
```
data/%s/%02d.dat             generic per-character data
data/effect/%03d.dat         effects
data/item/%03d.dat           items
data/bullet/%03d/%03d.dat    bullets (per character / per bullet)
data/scenario/team%02d.dat   scenario data
config.dat                   global config
%s/env.dat                   environment per stage
```

### Audio
```
data/bgm/title.ogg           title screen BGM
data/bgm/titlesemi.ogg       title semi BGM
data/bgm/select01.ogg        select screen BGM
data/voice/entry/%s.wav      voice entry files
```

### Shader
```
Microsoft (R) D3DX9 Shader Compiler 9.06.168.0000   (D3DX9 embedded shader compiler)
```

## 6. Other findings (original-binary observations)

- **No “cnv” string** was found in the executable. This describes the original's
  BMP/WAV/OGG file requests, not the port's asset pipeline: the current
  foundation decodes shipped CNV images/audio at runtime (`remake/foundation/src/assets/cnv.h`).
- **`DInput-Error`** is present; the original initializes DirectInput. The port
  uses SDL3 (`remake/foundation/src/input/`).
- **Japanese strings** are present as Shift-JIS. The port decodes relevant names
  and text before its UTF-8 renderer.
- Compiled with VS2003/2005 (inferred from the PDB path and runtime strings).
- No anti-debugging or packing was observed.

## 7. Compatibility verdict for our C++ parser

## Original-reader compatibility matrix (for comparison with current source)

| Binary format fact | Value |
|---|---|
| Header / table | `uint16 LE` file count; `numFiles * 268` bytes |
| Table cipher | key 100, counter 100, increment 77 (`0x4d`), XOR |
| Entry fields | 260-byte filename at 0; length at 260; offset at 264 |
| Filename encoding | Shift-JIS / CP932 |
| Standalone data cipher | `((offset >> 1) & 0xff) | 0x08`, XOR each byte |

The original's format is the RE result; the old parser-column comparison is
retired because its `remake/src/` implementation was deleted in Phase 5. The
current foundation sources are `remake/foundation/src/assets/dat_bundle.cpp`
and `dat_crypto.cpp`; current runtime/build evidence is in
`remake/foundation/docs/BUILD-linux.md` and `remake/foundation/docs/RELEASE-CHECKLIST.md`.

## 8. Files / locations for the next stages

| What                       | Where (in the binary)            |
|----------------------------|----------------------------------|
| Bundle bootstrap           | `fcn.0064d250`                   |
| Bundle .DAT open + parse   | `fcn.00662d10`                   |
| Standalone .DAT open+decrypt | `fcn.00662a74`                 |
| Generic file-open helper   | `fcn.00653540`                   |
| Window class registration  | (xref of `HigurashiDaybreak` @ 0x6a5540) |
| DirectInput init           | (xref of `DInput-Error` string)  |
| **.X model loader**        | `fcn.0064d940` (calls `D3DXLoadMeshHierarchyFromXInMemory`) |
| **.X hierarchy destructor**| `fcn.0064dc40` (calls `D3DXFrameDestroy`) |
| **Biped skeleton walker**  | `fcn.0064ddd0` (recursive, walks `pFrameFirstChild`/`pFrameSibling`) |
| **Raycast — closest hit**  | `fcn.0042d3b0` (main entry, 1478 bytes) |
| **Raycast — closest hit, recursive** | `fcn.0042cd50` (uses `D3DXIntersect` per mesh) |
| **Raycast — any hit, recursive**     | `fcn.0042d2c0` (early-out on first hit) |
| **Raycast — closest hit, frame hierarchy walk** | `fcn.00633930` |
| **Stage collision.X loader** | `fcn.004011f0` (loads `collision.x`, `collision_camera.x`, `collision_tama.x`) |
| **Hitbox builder**         | `fcn.006333b0` (4 calls to `D3DXVec3Transform`; writes AABB at +0x30/+0x60) |
| **Matrix inverse (IK?)**   | `fcn.00420b30` |

## 9. .X model loading — how the game does it

### 9.1 Loader entry point — `fcn.0064d940`

The game has a single function that loads every `.x` file. It is called from
11 different sites (character meshes, stage meshes, collision meshes, effect
meshes, aura meshes, etc).

```c
// Pseudocode of fcn.0064d940
bool load_x(XModel* out, const char* path) {
    // 1. Open the file via the daybreak-generic helper (fcn.00653540)
    //    which wraps CreateFileA + ReadFile.  Reads the entire file into
    //    a malloc'd buffer.
    FileHandle h = open_for_read(path);
    if (!h) return false;

    DWORD filesize = GetFileSize(h, ...);
    uint8_t* buf = malloc(filesize);
    ReadFile(h, buf, filesize, ...);
    CloseHandle(h);

    // 2. Parse it in memory via D3DXLoadMeshHierarchyFromXInMemory.
    //    Notable: flags = 0x220 (= D3DXMESH_MANAGED = D3DXMESH_VB_MANAGED |
    //    D3DXMESH_IB_MANAGED, 0x020 | 0x200: managed-pool vertex and index
    //    buffers). This is NOT D3DXMESH_32BIT (0x001) | D3DXMESH_NPATCHES
    //    (0x4000) — that pair would read 0x4001. The flag only tells D3DX
    //    where to keep buffers, nothing about index width or subdivision,
    //    so there is no N-patch divergence to chase in the loader.
    ID3DXAllocateHierarchy* alloc = ...;  // global at 0x6d16f8
    HRESULT hr = D3DXLoadMeshHierarchyFromXInMemory(
        buf, filesize,
        0x220,                     // <-- mesh flags (MANAGED = VB_MANAGED | IB_MANAGED:
                                     //     managed-pool vertex and index buffers)
        device,
        alloc,
        nullptr,                   // user data callback (NULL)
        &out->rootFrame,
        &out->animController);

    free(buf);

    if (FAILED(hr)) return false;

    // 3. If we got an animation controller, walk the first 2 animation
    //    sets and bind them to tracks 0 and 1 of the controller.  Sets
    //    up playback speed = 1.0, weight = 1.0, position = 0.
    if (out->animController) {
        DWORD numSets = out->animController->GetNumAnimationSets();
        DWORD maxTracks = out->animController->GetMaxNumAnimationSets();
        for (DWORD t = 0; t < maxTracks; ++t) {
            out->animController->SetTrackEnable(t, FALSE);
        }
        for (DWORD i = 0; i < min(numSets, 2); ++i) {
            ID3DXAnimationSet* set = ...;
            out->animController->SetTrackAnimationSet(i, set);
            out->animController->SetTrackEnable(i, TRUE);
            out->animController->SetTrackWeight(i, 1.0f);
            out->animController->SetTrackSpeed(i, 1.0f);
            out->animController->SetTrackPosition(i, 0.0);
        }
    }

    // 4. Walk the frame hierarchy looking for a frame named "Bip"
    //    (3ds Max Biped root marker).  This is the skeleton root.
    find_bip_frame(out->rootFrame);

    return true;
}
```

**Key takeaways for the port:**

- The game parses in memory (`FUN_0064d940` calls
  `D3DXLoadMeshHierarchyFromXInMemory`). The foundation does the same shape
  without D3DX: `xm::loadFile` (`xmodel.h:269`) reads the file into memory
  and parses via `xm::loadMemory` (`xmodel.h:267`, `2051`), which handles
  all three shipped `.X` encodings. There is no file-based D3DX call and
  no `D3DXMESH_SYSTEMMEM` flag left to switch — that guidance predates the
  Phase 5 cutover that deleted the DX9 tree.

- The mesh flags `0x220` (`D3DXMESH_MANAGED` = `D3DXMESH_VB_MANAGED` |
  `D3DXMESH_IB_MANAGED`, `0x020` | `0x200`) tell D3DX to keep vertex and
  index buffers in the managed pool. This is NOT `D3DXMESH_32BIT` (`0x001`)
  | `D3DXMESH_NPATCHES` (`0x4000`) — that pair would read `0x4001`. The
  flag says nothing about index width or subdivision, so there is no
  N-patch divergence to chase in the loader.

- The skeleton is a **3ds Max Biped** — frame names start with `Bip01_`
  (`Bip01_Head`, `Bip01_Spine`, `Bip01_Prop1`, `Bip01_Prop2`, ...).  Any
  bone lookup logic in the port should expect Biped naming.

- Animation sets are bound to **up to 2 tracks** at load time.  Our port
  binds only 1 track; the original keeps track 1 free for blending (e.g.
  upper-body attack animation on track 1 over the lower-body run animation
  on track 0).

### 9.2 Stage collision meshes — `fcn.004011f0`

Three collision `.x` files are loaded per stage, each as a separate XModel:

```
%s/collision.x          → stage->collision       (+0x24)
%s/collision_camera.x   → stage->collision_cam   (+0x28)
%s/collision_tama.x     → stage->collision_tama  (+0x28, after freeing the previous)
```

The naming is in Japanese:
- `tama` (玉) = "ball" / projectile
- `collision_tama.x` is the projectile collision mesh — separate from the
  character collision mesh, presumably because projectiles should pass
  through small obstacles that characters would collide with.

The foundation currently loads and identifies the three collision roles in
`remake/foundation/src/assets/scene.h` and queries them through
`remake/foundation/src/physics/raycast.h`. The closest-hit (`raycastModel`) and
early-out (`raycastModelAny`) shapes correspond to `FUN_0042d3b0` /
`FUN_0042cd50` and `FUN_0042d2c0`; old snake_case `raycast_model*` names refer
to the deleted DX9 side.

## 10. Collision — how the game does it

### 10.1 All collision is `D3DXIntersect`

There is **no custom sphere/AABB/OBB code** in the game. Every collision
query is a raycast against a triangle mesh, done via `D3DXIntersect`.

The game has 4 `D3DXIntersect` call sites:

| Function       | Size  | Purpose                                                 |
|----------------|-------|---------------------------------------------------------|
| `fcn.0042d3b0` | 1478B | Main entry — closest-hit raycast against a frame tree  |
| `fcn.0042cd50` |  ~1KB | Recursive walker — same as above, used by something else |
| `fcn.0042d2c0` |  235B | Any-hit raycast (early-out on first triangle hit)       |
| `fcn.00633930` |  297B | Recursive any-hit walker; stores closest in `obj+0x96`  |

All four follow the same pattern:

```c
// Walk the D3DXFRAME hierarchy recursively.
void walk(D3DXFRAME* frame, RayState* s) {
    D3DXMESHCONTAINER* mc = frame->pMeshContainer;   // offset +0x44
    while (mc) {
        if (mc->MeshData.Type == D3DXMESHTYPE_MESH) {
            BOOL hit;
            DWORD face;
            float u, v, dist;
            D3DXIntersect(mc->MeshData.pMesh,
                          &s->rayPos, &s->rayDir,
                          &hit, &face, &u, &v, &dist,
                          nullptr, nullptr);
            if (hit && dist < s->bestDist && dist <= s->maxDist) {
                s->bestDist = dist;
                s->bestFace = face;
                ...
            }
        }
        mc = mc->pNextMeshContainer;   // offset +0x20
    }
    walk(frame->pFrameFirstChild, s);  // offset +0x48
    walk(frame->pFrameSibling, s);     // offset +0x4c
}
```

**Key takeaways for the port:**

- The original passes the ray **in model space** — it does NOT transform
  the ray by each frame's `worldMatrix`.  This is correct because the
  collision meshes are loaded without any per-frame transforms (the
  artists exported them with identity transforms).

- The original calls `D3DXIntersect` with `ppAllHits=nullptr` and
  `pCountOfHits=nullptr` — it only uses the single closest-hit output
  (`pHit` + `pFaceIndex` + `pU` + `pV` + `pDist`).  Our `raycast_model`
  does the same.

- The original's `raycast_model_any` (the "did I hit anything at all?"
  variant) is the one used for line-of-sight checks.  Our implementation
  mirrors this with early-out.

### 10.2 Float constants seen in the collision code

| Address     | Value   | Likely meaning                                |
|-------------|---------|-----------------------------------------------|
| `0x6a16d0`  | 1.0     | Default Y offset (capsule height?)            |
| `0x6a16d4`  | 400.0   | Max raycast range (default)                   |
| `0x6a16d8`  | 200.0   | Mid-range cutoff                              |
| `0x6a16c4`  | 20.0    | Capsule radius / hitbox radius                |
| `0x6a16cc`  | 0.2     | Small epsilon (skin width)                    |
| `0x6a16f8`  | 50.0    | Animation blend distance                      |
| `0x6a24c4`  | 0.01    | Numeric epsilon                               |
| `0x6a24cc`  | 1.5     | Multiplier (character scale?)                 |

### 10.3 Hitbox struct layout (inferred from `fcn.006333b0`)

The function at `fcn.006333b0` builds an axis-aligned bounding box for an
object, using 4 calls to `D3DXVec3Transform` (probably transforming the
8 AABB corners by the object's world matrix, then taking min/max). The
result is written to:

```
obj + 0x30, 0x34, 0x38   = vec3  AABB.min  (or max — first corner)
obj + 0x60, 0x64, 0x68   = vec3  AABB.max  (or min — second corner)
obj + 0x78                = float hitRadius  (sphere test, used in fcn.00633930)
obj + 0x96                = float lastHitDist (cached raycast result)
```

This is consistent with a **sphere + AABB hybrid** for culling, with the
actual hit test still being a triangle raycast.

## 11. Original loader/collision facts and foundation pointers

| Original-binary fact | Current foundation reference |
|---|---|
| In-memory `.X` loader; `0x220` D3DX managed-buffer flags | `remake/foundation/src/assets/xmodel.h` implements the parser/controller without D3DX flags |
| Up to two original animation tracks at load | `xm::Controller` supports multiple tracks; see `xmodel.h` |
| Biped frame names such as `Bip01_*` | Preserved as asset naming facts; foundation frame lookup is in `xmodel.h` |
| Collision uses mesh-space ray tests, no per-frame transform | `remake/foundation/src/physics/raycast.h` documents the matching query surface and traversal |
| Original closest-hit/early-out walkers | Foundation `raycastModel` / `raycastModelAny` are the corresponding APIs |
| Stage uses collision, camera, and projectile meshes | Roles and stage loading are in `remake/foundation/src/assets/scene.h`; camera queries in `src/physics/raycast.h` |

The former compatibility table compared against the deleted DX9 remake and
contained obsolete snake_case names and paths. This replacement is a navigation
aid, not a fresh pixel-parity verdict; consult current source/tests for current
behavior and verification.

## 12. radare2 setup (for future sessions)

`remake/scripts/r2.sh` wraps `r2` and the various `r2*` tools (`rabin2`, `rafind2`, `rahash2`, `rasm2`, etc.) with the correct `LD_LIBRARY_PATH` and `MAGIC` env vars. The radare2 install itself lives under `remake/tools/r2/` and is fetched by `remake/scripts/fetch_deps.sh` (see the r2 block in `fetch_deps.sh`).

```bash
./remake/scripts/r2.sh rabin2 -I path/to/DaybreakDX.exe
./remake/scripts/r2.sh r2 -q -c 'aaa; pdf @ fcn.00662d10' path/to/DaybreakDX.exe
```

## 13. Validation against real game assets

After receiving the actual `.DAT` files from the original game via FileVault,
we ran our native Linux test harness against them. All four bundles opened
cleanly and all extracted payloads validated as their expected file types.

### Bundle summary

| Bundle | Size | Entries | Content |
|---|---|---|---|
| `daybreak00.dat` | 1.43 GB | **7,677** | Character models, stage meshes, voices, win screens — **the main asset bundle** |
| `daybreak05.dat` | 47 MB | 41 | BGM tracks (`.ogg` + `.sfl` pairs) |
| `daybreak06.dat` | 439 MB | 5 | Story-mode FMVs (`.mpg` — out of scope for the port) |
| `daybreak07.dat` | 3.35 MB | 178 | Items, bullets, voice snippets, per-character data |

### Characters observed in the supplied asset install (paths `data/<char>/`)

`akane`, `akasaka`, `chie`, `hanyu`, `irie`, `kasai`, `keiichi`, `mion`,
`ohishi`, `rena`, `rika`, `satoko`, `shion`, `takano` — **14 characters**.

Each character ships with:
- `data/<char>/00.X` — main 3D model (binary `.X`, 7-10 MB each)
- `data/<char>/01.X` — alternate model (costume / form change?)
- `data/<char>/00.dat`, `01.dat`, `02.dat` — animation/move data (referenced as `"00.X"` etc internally — confirmed by hex dump of `takano/02.dat`)
- `data/<char>/*.cnv` — CNV textures; the original requests BMP names, while the current foundation decodes CNV at runtime (`remake/foundation/src/assets/cnv.h`).

### Stages confirmed (paths `data/stageNN/`)

`stage01` through `stage06`, `stage11` through `stage15`, `stage21` — **12 stages**.

Each stage ships with:
- `data/stageNN/NN.X` + `NNb.X` — visible stage mesh (multiple parts, `b` = broken/damage state)
- `data/stageNN/collision.x` — character collision
- `data/stageNN/collision_tama.x` — projectile collision (玉 = ball)
- `data/stageNN/collision_camera.x` — camera collision (only some stages; others fall back to character collision)
- `data/stageNN/env.dat` — environment data (84 bytes; small config)

### `.X` file formats observed

The game ships `.X` files in **three different D3DX-supported encodings**:

| Magic | Format | Use |
|---|---|---|
| `xof 0302txt 0064` | text format | `stageNN/collision.x` (small, human-readable, used for collision meshes) |
| `xof 0303bin 0032` | binary format | `data/<char>/<NN>.X` (character models, 7-10 MB) |
| `xof 0303bzip0032` | bzip-compressed | `data/stageNN/NN.X` (stage visible meshes) |

All three encodings are accepted by the original D3DX in-memory loader. The
foundation parser also handles text, binary, and bzip-compressed `.X` (see
`remake/foundation/src/assets/xmodel.h`); current parser verification is
tracked in the foundation build/release records.

### Asset integrity validated

- ✅ `daybreak07.dat` (178 entries) — opened, listed, all 178 payloads extracted
- ✅ `data/bgm/win.ogg` — 879 KB Vorbis audio, validated by `ffprobe`:
  `codec_name=vorbis, sample_rate=44100, channels=2, channel_layout=stereo`
- ✅ `data/bgm/win.sfl` — 136 bytes loop-point file (SF2-style)
- ✅ `data/rika/01.X` — 9.6 MB binary `.X`, magic `xof 0303bin 0032`
- ✅ `data/takano/00.X` — 7.4 MB binary `.X`, same magic
- ✅ `data/stage21/collision.x` — 36 KB text `.X`, magic `xof 0302txt 0064`,
  contains 1 Mesh (no Frame, no Material, no SkinWeights — pure collision geometry)
- ✅ `data/stage21/00.X` — 3.5 KB bzip-compressed `.X`, magic `xof 0303bzip0032`

### Internal data file format

Looking inside `data/takano/02.dat` (74 KB character animation data):

```
000000 04 00 00 00 30 30 2e 58 00 00 00 00 00 00 00 00  → "....00.X........"
```

The first DWORD is `0x00000004` (likely version=4), followed by a 260-byte
filename field containing the string `"00.X"` (the model this animation
set targets). Same pattern in `data/bullet/044/003.dat`:

```
000000 04 00 00 00 33 30 2e 58 00 00 00 00 00 00 00 00  → "....30.X........"
000120 01 00 00 00 42 69 70 30 30 00 00 00 00 00 00 00  → "....Bip00......."
```

This confirms:
- The animation/move data files reference their `.X` model by filename
- The string `"Bip00"` (not `Bip01`) appears inside `bullet/044/003.dat`
  at offset 0x124 — this might be a hitbox attachment bone (note the
  diverging naming from the `Bip01_*` strings we saw in `DaybreakDX.exe`
  for character skeletons; could be a different rig for bullets)

### Conclusion (historical validation record)

This install-backed validation confirmed the parser at the time and documented
representative `.X` payloads. The “start M1 (asset manager)” milestone is
obsolete: the current foundation asset layer, parser, collision, and runtime
paths are already in place. See `remake/foundation/docs/BUILD-linux.md` and
`RELEASE-CHECKLIST.md` for current run/build evidence.

## 14. Camera system (RE round 2 — focused investigation)

After the user clarified that **the game is 2v2** (not 1v1 as the original
roadmap assumed) and that **the camera is always locked onto one of the 4
fighters with a button to cycle targets**, we did a focused RE pass on the
camera subsystem.

### 14.1 Camera-related strings

Only two strings mention "camera" in the entire binary:

```
%s/collision_camera.x     ← stage collision mesh (camera-only)
@data/camera/01.x         ← camera model file (the @ prefix is a Frame name marker)
```

`data/camera/01.x` is loaded as a regular `.X` model — likely the camera's
own visible representation (a small icon or arrow that indicates which
fighter is currently targeted).

### 14.2 View + projection matrix setup — `fcn.006507c0`

This is the original game's **main camera update function**. It is the only
place that calls both `D3DXMatrixLookAtLH` and `D3DXMatrixPerspectiveFovLH`.
It is called from one site: `fcn.006396f0` (the original main scene render path).

Layout of the camera struct (passed in `ecx`, offset `+0x60` from the
argument the caller passes — i.e. the camera struct lives inside a
larger scene struct at offset `+0x60`):

```
struct Camera {
    // offset 0x00..0x5f of the enclosing struct (not camera's)
    // offset 0x60..0xdf — camera sub-struct starts here
    //   (the function does ecx += 0x60 then calls fcn.00661770
    //    with ecx as the camera struct)
    ...
    // offset 0xe0 (relative to enclosing struct) — vec3 eye
    float eye_x;     // +0xe0
    float eye_y;     // +0xe4
    float eye_z;     // +0xe8
    // offset 0xec (relative) — vec3 target
    float target_x;  // +0xec
    float target_y;  // +0xf0
    float target_z;  // +0xf4
    // offset 0xf8 (relative) — vec3 up
    float up_x;      // +0xf8
    float up_y;      // +0xfc
    float up_z;      // +0x100
    // offset 0x110 — output view matrix (D3DXMATRIX, 16 floats = 64 bytes)
    D3DXMATRIX view_matrix;  // +0x110..0x14f
    // offset 0x190 — output projection matrix
    D3DXMATRIX proj_matrix;  // +0x190..0x1cf
    // offset 0x1d0 — perspective params (fov, aspect, znear, zfar)
    float fov;        // +0x1d0
    float aspect;     // +0x1d4
    float znear;      // +0x1d8
    float zfar;       // +0x1dc
    // offset 0xe0..0x110 also used for "delta" computation (target - eye)
};
```

The function:
1. Calls `fcn.00661770(camera_struct)` — this is the **camera
   orientation helper** that normalizes eye/target/up vectors and
   computes the view matrix internally.  70 instructions, calls
   `D3DXMatrixLookAtLH` + 2× `D3DXVec3Normalize`.
2. Calls `ID3DXAnimationController::SetTrackAnimationSet` (vtable +0xb0,
   with track 2 and 3) — this is **track blending setup**, suggesting
   the camera might be driven by animation tracks too (e.g. a "camera
   shake" animation overlaid on the base camera).
3. Builds a vec3 at `0x6c78ac` (camera eye — global) using:
   ```
   eye = (500000.0, 1000000.0, 1000.0)  // initial values from pushed constants
   ```
   then transforms it via `D3DXMatrixRotationZ(angle - π/4)` — the
   camera orbits around the target with a Z-axis rotation.  The
   constant `0x6aac70` (= π/4 = 0.7853982) is subtracted, suggesting
   the baseline camera angle is 45° from +X.
4. Calls `D3DXMatrixLookAtLH(&view_matrix, &eye, &target, &up)` —
   the eye/target/up come from the camera struct fields at +0xe0/+0xec/+0xf8.
5. Calls `D3DXMatrixPerspectiveFovLH(&proj_matrix, fov, aspect, znear, zfar)`
   where fov/aspect/znear/zfar come from struct +0x1d0..0x1dc.

### 14.3 Camera state globals — `0x6c7890`..`0x6c78c8`

A block of globals stores the camera's per-frame raycast state (used
for collision):

```
0x6c7898  byte    mode flag (camera active?)
0x6c789c  float   previous-frame closest hit distance
0x6c78a4  float   current closest hit distance (reset to 10000.0 each frame)
0x6c78a8  byte    "hit occurred" flag
0x6c78ac  vec3    camera eye position (written by fcn.0042d3b0 raycast)
0x6c78b8  vec3    camera target position (or hit point)
0x6c78c0  vec3    camera up vector
0x6c78c8  vec3    hit normal (probably)
```

These are written by `fcn.0042d3b0` (the closest-hit raycast we
already documented in section 10) and read by `fcn.006507c0` (the
camera update).

### 14.4 Camera collision flow

```
fcn.0042cb50 (camera_update_with_collision)
  ├─ resets 0x6c78a4 to 10000.0
  ├─ resets 0x6c78a8 to 0
  ├─ calls fcn.0064ecb0(camera_target_pos) → world matrix
  ├─ calls fcn.0042d3b0 (recursive closest-hit raycast)
  │     └─ writes hit distance to 0x6c78a4
  │     └─ writes hit point to 0x6c78ac, 0x6c78b8, 0x6c78c0 (vec3s)
  ├─ stores 0x6c78a4 to struct+0x80 (cached hit distance)
  ├─ if hit flag (struct+0x85) was set:
  │     ├─ calls fcn.0042dec0(struct+0x14, &0x6c78ac) — apply hit point
  │     ├─ reads 0x6c78b8/bc/c0 (the hit vec3) into locals
  │     ├─ resets struct+0x85 hit flag
  │     ├─ resets 0x6c78a4 to 10000.0
  │     ├─ second raycast from the new position
  │     └─ if hit again, jump to "apply" path; else lerp eye position
  └─ else: lerp eye toward target
```

So the camera does **two raycasts per frame**: one from the desired eye
position toward the target (to detect walls between camera and target),
and if that hits, a second raycast from the hit point to refine the
position.  This is the standard "camera collision spring" pattern.

### 14.5 Camera reset — `fcn.0042c970`

Called from 3 sites (`fcn.004202b0`, `fcn.005f5e00`, `fcn.00633ab0`).
Resets:
- struct+0x7c to `0x461c4000` (= 10000.0, max distance sentinel)
- `0x6c789c`, `0x6c78ac`, `0x6c78b0`, `0x6c78b4` to 0 (eye + target zeroed)
- `0x6c7898`, `0x6c78a8` to 0 (mode + hit flag zeroed)

Then does an initial raycast (`fcn.0042cd50`) to seed the camera
position.

### 14.6 The "target switch" button

We did NOT find a dedicated function named "switch_target" or similar.
The 16 `CTAB` strings in the binary are unrelated (they're Win32 control-
class names from a tabbed dialog, likely the config window).

The target-switch logic is likely integrated into the main input-update
function (probably `fcn.006396f0` or its caller) — when the user taps
the target button, the code:
1. Iterates the 4 fighter slots.
2. Picks the next alive fighter that's not the current target.
3. Updates a global "current camera target" pointer.
4. The camera update function then uses that pointer's position as the
   target for `D3DXMatrixLookAtLH`.

We don't have the exact global pointer name yet — that needs dynamic
analysis (running the game under a debugger) or further static RE of
the input dispatch code.  For the port, we mirror this design: the
`gameplay::ArenaCamera` holds a target pool and a `cycle_target()`
method (`foundation/src/gameplay/arena_camera.h:180-188`:
`set_target_pool`, `set_active_target`, `cycle_target`).

### 14.7 Float constants used by the camera

| Address     | Hex         | Float       | Likely meaning                          |
|-------------|-------------|-------------|-----------------------------------------|
| `0x6a16c4`  | 0x41a00000  | 20.0        | Capsule/hitbox radius                   |
| `0x6a16c8`  | 0x00000000  | 0.0         | Zero sentinel (range check)             |
| `0x6a1720`  | 0x43960000  | 300.0       | Camera height offset                    |
| `0x6a4928`  | 0x44480000  | 800.0       | Camera distance offset                  |
| `0x6aac70`  | 0x3f490fdb  | π/4 (0.785) | Baseline Z-rotation (45°) for camera    |
| (literal)   | 0x461c4000  | 10000.0     | Max raycast distance (sentinel)         |
| (literal)   | 0x48f42400  | 500000.0    | Initial eye X (far away, gets replaced) |
| (literal)   | 0x49742400  | 1000000.0   | Initial eye Y                           |
| (literal)   | 0x447a0000  | 1000.0      | Initial eye Z                           |
| (literal)   | 0x3a89421f  | 0.00105     | FOV epsilon (anti-zero)                 |
| (literal)   | 0x3f800000  | 1.0         | Aspect placeholder (real aspect from struct) |

### 14.8 Camera struct field map (offsets relative to enclosing scene struct)

```
+0x60   camera sub-struct start (passed to fcn.00661770)
+0x7c   float  last hit distance (cached, reset to 10000.0)
+0x80   float  hit distance (current, from 0x6c78a4)
+0x84   byte   hit flag (was there a collision this frame?)
+0x85   byte   hit flag (second-raycast needed?)
+0xe0   vec3   eye position
+0xe8   vec3   (used as temp: target - eye direction)
+0xec   vec3   target position (look-at target)
+0xf4   vec3   (used as temp: up - target)
+0xf8   vec3   up vector
+0x110  D3DXMATRIX  view matrix (output of D3DXMatrixLookAtLH)
+0x190  D3DXMATRIX  projection matrix (output of D3DXMatrixPerspectiveFovLH)
+0x1d0  float  fov (radians)
+0x1d4  float  aspect ratio
+0x1d8  float  near clip
+0x1dc  float  far clip
```

### 14.9 Historical design implications (the foundation implementation now exists)

The following were recommendations at the time of this RE pass, not current
open work. The `gameplay::ArenaCamera` and camera collision path now exist in
`remake/foundation/src/gameplay/arena_camera.{h,cpp}` and
`remake/foundation/src/physics/raycast.h`; the banked DX9 oracle and original
prints remain the available comparisons. The original-derived ideas were:

1. **Hold a target pointer** (not a fixed position).  The camera always
   looks at one fighter; "switch target" cycles the pointer through
   the alive fighters.
2. **Orbit with Z-axis rotation**, baseline at 45°.  The camera's
   horizontal angle is `current_angle - π/4` — this suggests the
   "default" view is at 45° offset from the fighter's facing direction.
3. **Use a fixed height offset** (300.0 units, from `0x6a1720`) and
   **distance offset** (800.0 units, from `0x6a4928`).  These are
   large — the game uses a generous camera distance, consistent with
   the "see all 4 fighters" requirement of 2v2.
4. **Two-pass raycast** against `collision_camera.x`: first from the
   desired eye position toward the target; if blocked, do a second
   raycast from the hit point and lerp the eye to the unobstructed
   position.  This is the "camera collision spring" pattern.
5. **Support up to 2 animation tracks** (the camera calls
   `SetTrackAnimationSet` with track 2 and 3 — tracks 0/1 are
   reserved for fighters, tracks 2/3 for camera).  This is likely
   used for camera shake / scripted camera moves during specials.
6. **2v2 awareness**: with 4 fighters, the camera must keep all 4 in
   frame.  The 800-unit distance offset accommodates this — when
   fighters spread out, the camera pulls back; when they cluster,
   it pushes in.  The target pointer determines the *focus* (which
   fighter the camera centers on), but the framing adjusts to keep
   all visible.

### 14.10 Open questions from the original RE pass (historical)

- **Exact target-switch button**: we know it exists but haven't found
  the input dispatch code.  Need to either (a) run the game under a
  debugger and break on `gameplay::ArenaCamera::set_active_target`
  (`arena_camera.h:180ff`) rather than the nonexistent `set_target`, or
  (b) trace xrefs
  to the global "current camera target" pointer once we identify it.
- **Auto-target vs manual**: does the camera auto-switch when the
  current target dies, or only on button press?
- **Team awareness**: in 2v2, does the camera prefer same-team targets
  or alternate between teams?
- **Camera shake during specials**: the track-2/3 binding suggests
  yes, but we haven't traced the actual shake animation data.

These were open questions when the RE pass was written. Current release and
verification status is tracked in `remake/foundation/docs/ROADMAP-PENDING.md`
and `RELEASE-CHECKLIST.md`; this historical list is not the current task list.

