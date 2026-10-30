# Third-party notices — the Linux release package

Every component the package ships or links, the licence it is under, and where its licence
text comes from. The package's own code is `daybreak-decomp.txt` (the repository's
`LICENSE`).

| Component | What it is here | Licence | Text |
|---|---|---|---|
| daybreak-decomp | the port itself (the executable's own code) | The Golden Witch License | `daybreak-decomp.txt` |
| SDL3 | window, input, audio, timing — shipped as `lib/libSDL3.so.0` | zlib | `SDL3.txt` |
| wgpu-native v24.0.3.1 | the WebGPU implementation behind `webgpu.h` — shipped as `lib/libwgpu_native.so` | MIT (upstream also offers Apache-2.0) | `wgpu-native-MIT.txt` |
| WebGPU-distribution (third_party/webgpu) | the CMake wrapper and headers that fetch wgpu-native | MIT | `wgpu-distribution-MIT.txt` |
| Gyrotrope Black | the runtime caption face, `assets/fonts/gyrotrope-black.otf` | SIL Open Font License 1.1 | `SIL-OFL-1.1.txt` |
| Goldman Bold | translated label face, `assets/fonts/Goldman-Bold.ttf` | SIL Open Font License 1.1 |
| Noto Sans CJK JP Regular | Japanese fallback face, `assets/fonts/NotoSansCJKjp-Regular.otf` | SIL Open Font License 1.1 | `SIL-OFL-1.1.txt` |
| GLM | header-only math (compiled into the executable) | MIT | `glm-MIT.txt` |
| stb_truetype / stb_vorbis | header-only font rasterizer and Ogg Vorbis decoder (compiled into the executable) | MIT or public domain, at your option | `stb.txt` |
| pl_mpeg | MPEG-1 video + MP2 audio + MPEG-PS demux, the opening/staff-roll movie decoder (compiled into the executable) | MIT | `pl_mpeg-MIT.txt` |

Notes:

- The two font faces carry their copyright in their own name tables: Gyrotrope Black is
  "Copyright 2025 David Moles" (trademark of David Moles), and Noto Sans CJK JP is
  "© 2014-2021 Adobe (http://www.adobe.com/)" (Noto is a trademark of Google Inc.); both
  are licensed under the SIL Open Font License 1.1, whose text is `SIL-OFL-1.1.txt`. The
  package redistributes them unmodified.
- wgpu-native is dual-licensed MIT / Apache-2.0; the MIT text is included here. The
  prebuilt `libwgpu_native.so` is fetched by `scripts/fetch_deps.sh`
  from the pinned upstream release `v24.0.3.1`.
- `libstdc++`, `libm`, `libgcc_s`, `libc` and the dynamic loader are **not** bundled: they
  are part of the distribution the package runs on, and shipping them would break the
  distribution's own ABI rules. `ldd` on the packaged executable shows them resolving from
  the system.
- pl_mpeg ships no separate licence file upstream: `pl_mpeg.h` carries
  `SPDX-License-Identifier: MIT` in its header and the project README states the licence.
  The text above is the standard MIT grant and the copyright holder is the library's author
  and publisher, Dominic Szablewski. It is fetched as one pinned raw blob by
  `scripts/fetch_deps.sh`, like the two stb headers.
- The movies pl_mpeg decodes (`Higurashi-Daybreak/data/movie/*.mpg`) are **not** part of
  this package or of any artifact built here: they are user-owned game data, exactly like
  the rest of the install.
