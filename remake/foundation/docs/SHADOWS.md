# Character shadows (issue #21 row 1) — recovery

The original's 影の表示 row (`DAT_006cfcea`) gates **one light-space render of every
fighter's own body and weapon into a 1024x1024 off-screen target, which the stage
geometry then samples projectively and darkens by 0.3 where its own light-space
depth is behind the map's**. It is a shadow map, not a planar projected silhouette:
the earlier note in `ROADMAP-PENDING.md` ("a projected second draw of the
character") named the caster draw correctly but not what the draw feeds.

Every address below was read on the **live original** through the Ghidra bridge
(`DaybreakDX.exe`, md5 `a136ddc01bd7ef355b759b88ac89e02c`, 2920448 bytes) unless a
line says otherwise; the same functions in `research/decompiled/` (the **patched**
copy) agree instruction for instruction, so nothing here rests on the patch. Two
facts that shape the search:

* **`D3DXMatrixShadow` is not used.** The PE import table has 175 names and no
  `D3DXMatrixShadow`; the imported D3DX matrix helpers are Inverse, LookAtLH,
  Multiply, PerspectiveFovLH, RotationAxis/X/Y/YawPitchRoll/Z, Scaling and
  Translation. The projection is a light *camera* (view x projection), not a
  plane-projection matrix.
* **There is no per-stage light input.** The light is a fixed point plus the
  frame's camera eye; see "The light" below.

## Read site

`FUN_006396f0` (the battle view loop), per view, at `0x639b7b-0x639bc6`:

```
FUN_006507c0()                       ; camera + light matrices, 0x639b80
FUN_00651110(2)                      ; technique mode 2 = the shadow caster, 0x639b8c
if (DAT_006cfcea != 0)               ; the 影の表示 toggle, 0x639b91
  for (i = 0; i < 4; ++i)
    FUN_004207d0(scene->fighters[i]) ; one call per fighter slot, 0x639bc1
FUN_00651110(0)                      ; back to the plain technique, 0x639bcf
```

`FUN_004207d0` (`0x004207d0`, live): `FUN_0064e1a0(fighter->[0x11c])` then
`FUN_00434970(fighter + 0x6a0)`. The first walks the fighter's scene-graph node
tree and calls each node's own render callback (`FUN_0064e130` -> `FUN_0064e110` ->
`FUN_006519b0`: `if (node->0x2c) node->0x2c(parent)`); the second draws the body and
weapon sub-objects (`param_1[0x18]` and `param_1[0x1c]` indices into the 0x970-byte
sub-object array at `+4`). Both end in the renderer's current technique function
(`0x6d13c0 + 0x2c`), which `FUN_00651110(2)` set to `FUN_00652880`
(`FUN_00651110` case 2, `0x00651110`).

## The caster pass

`FUN_00652880` (`0x00652880`), the mode-2 technique:

* `SetRenderState(D3DRS_CULLMODE = 0x16, 3)` at `0x6528a4` — cull CCW, the same as
  the plain 3D path.
* sets the effect parameter **`mTransform`** (handle string `"mTransform"` at
  `0x6aab98`) to **`&DAT_006d15d0`** (`0x6528d3`): the light matrix, and *only*
  that matrix — no world matrix is folded in (the plain path's `FUN_006519f0`
  sets `D3DTS_WORLD` instead).
* draws the same sub-object list as the plain path, with the same `Power == 0`
  alpha test.

`DAT_006d15d0` is `renderer + 0x210`, named **`mTransformLight`** by the effect
bindings (`FUN_00652220` at `0x652279`/`0x6524e2`, `FUN_00652af0` at
`0x652b85`/`0x652cf9`, `FUN_00652e40` at `0x652ede`/`0x653068`).

The technique's own effect blob is slot 2 of the ten `D3DXCreateEffect` calls in
`FUN_0064ff80` (`0x0064ff80`): `renderer+0x08` = the blob at `0x6a7b10`, length
`0x32c` (`FUN_0064ff80:24-27`). It is committed as
`remake/assets/shaders/effect_2.bin` and has exactly one technique
(`SampleTexhnique`) with one pass, one vs_1_1 and one ps_1_1:

```hlsl
// vs_1_1 (blob +0x1b4), disassembled with the shipped d3dx9_25.dll
dcl_position v0
dp4 oPos.x, v0, c0        ; clip = pos * mTransform
dp4 r0.w, v0, c3          ; w
rcp r1.w, r0.w
dp4 r0.z, v0, c2          ; z
dp4 oPos.y, v0, c1
mul oD0.w, r1.w, r0.z     ; oD0.w = z/w  -> the NDC depth
mov oPos.zw, r0
mov oD0.xyz, c4.x         ; rgb = 1 (def c4, 1,0,0,0)

// ps_1_1 (blob +0x164)
mov r0, v0                ; write (1,1,1, z/w) straight out
```

So the map stores, in its **alpha** channel, the caster's light-space NDC depth;
its RGB is white.

**Target.** `FUN_00650410` (`0x00650410`, the same function that loads the toon
ramp) creates it once:

* `0x650468-0x650495`: `CreateTexture(0x400, 0x400, 1, 1, D3DFMT_A8R8G8B8 = 0x15, 0,
  &renderer+0x34, 0)` — a **1024x1024 A8R8G8B8** texture.
* `0x650498-0x65052b`: `CreateTexture(0x400, 0x400, 1, 1, D3DUSAGE_DEPTHSTENCIL =
  0x50, 0, &renderer+0x38, 0)`, falling back to `D3DFMT_D24S8 = 0x51` and then to
  `0x15` — a 1024x1024 depth surface.
* `0x65052e-0x6505b0`: `GetRenderTarget(0, &renderer+0x27c)`,
  `GetDepthStencilSurface(&renderer+0x280)`, then `GetSurfaceLevel(0,
  &renderer+0x284)` and `(0, &renderer+0x288)` — the saved main targets and the
  map's own surfaces.

`FUN_00651110` case 2 (`0x00651110`, `0x6512c0-0x651360`) then, on entry only:

```
SetRenderState(D3DRS_FOGENABLE = 0x1c, 0)         ; fog off
SetRenderState(D3DRS_SRCBLEND  = 0x13, 2)         ; ONE
SetRenderState(D3DRS_DESTBLEND = 0x14, 1)         ; ZERO  -> the source is copied
SetRenderTarget(0, renderer+0x284)
SetDepthStencilSurface(renderer+0x288)
Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 0xff000000, 1.0f, 0)
```

The clear's alpha is **1.0**, which is the "nothing cast here" sentinel the
receiver compares against. On the way out (`DAT_006b77b4 == 2`, `0x6512c0-0x6512e0`)
it restores `renderer+0x27c`/`+0x280` and `ZWRITEENABLE`, `SRCALPHA`/`INVSRCALPHA`.

## The light

`FUN_006507c0` (`0x006507c0`), the per-view camera + light update, called from the
read site at `0x639b80`:

```
0x650833-0x65084d  a vec3 built from immediates: (0x447a0000, 0x49742400, 0x48f42400)
                   = (1000.0, 1000000.0, 500000.0)                     <- the light's eye
0x65084d-0x650875  d = |cameraEye - lightEye|      (FUN_0042dfd0 subtract,
                                                    FUN_0042df50 -> sqrt)
0x650878-0x6508a6  D3DXMatrixLookAtLH(out = renderer+0x190,
                                       pEye = (1000, 1e6, 5e5),
                                       pAt  = renderer+0xe0,   // the camera's EYE
                                       pUp  = renderer+0xf8)   // the camera's up
0x6508ab-0x6508dc  D3DXMatrixPerspectiveFovLH(out = renderer+0x1d0,
                                       fovy   = 0x3a89421f = 0.0010471975f,
                                       aspect = 0x3f800000 = 1.0,
                                       znear  = d - 0x6a1720 (= 300.0),
                                       zfar   = d + 0x6a4928 (= 800.0))
0x6509a5-0x6509d4  renderer+0x150 = renderer+0x60 * renderer+0x110   // the camera's
                   own view * projection ("mTransform")
0x6509d9-0x650a1c  renderer+0x210 = ((lightView * lightProj) * matA)  // mTransformLight
```

The two constants were read from the live image, not from a doc: `0x6a1720` =
`0x43960000` = 300.0, `0x6a4928` = `0x44480000` = 800.0, `0x6aac70` = `0x3f490fdb` =
pi/4.

**Direction.** The light's eye is a hardcoded point ~1.118e6 units from the camera
eye, so the direction of travel is `normalize(cameraEye - (1000, 1e6, 5e5))`. For
any camera eye inside the arena (|eye| < a few thousand units) that is
`-(0.0009, 0.8944, 0.4472)` to within 0.1 degrees: **the sun sits at
`normalize(1000, 1000000, 500000)`, i.e. `(0, 2, 1)/sqrt(5)` up to the negligible x
term — elevation 63.4 degrees, azimuth +Z.** It is a **constant, not a per-stage
value**: the only per-frame input is the camera eye's *position*, which moves the
direction by less than a tenth of a degree across the whole playfield, and no
stage/`env.dat` field reaches this function (the port's `env.dat` reader covers
fog only, and the constants here are immediates in `.text`). The human's "the
direction of the sun depends on the map" is therefore **not supported by the
data**.

**Projection.** A 0.0010472 rad (0.06 degree) vertical FOV at ~1.118e6 units is a
~1170x1170-unit window on the scene centred on the camera eye, 1100 units deep
(300 in front of it, 800 behind) — effectively an orthographic light box, and the
reason the shadows in the original's prints are crisp only near the fighters the
camera is following.

**The clip tweak (`matA`, `0x6508e1-0x6509a0`).** After the two matrices are
combined the code post-multiplies a small matrix built as
`RotZ(-atan2(dz, dx) - pi/4) * Scale(0.9, 0.9, 1) * Translate(0.7, -0.7, 0)`,
where `(dx, dz)` is the camera's `(at - eye)` on the ground plane. It touches only
clip x/y (its z and w rows are the identity), and **the receiver's projected
texture coordinates are built from the same matrix**, so it cancels in the depth
test and in the lookup. What it does change is how much of the 1024x1024 map the
scene occupies. The port omits it (see PORT RULES).

## The receiver

The stage's ground is drawn by `FUN_00401b80` (`0x00401b80`, called from the same
view loop at `0x639dcc` with the stage object), which picks technique **mode 3**
when the stage object's byte `+0x2c` is non-zero and mode 0 otherwise. Mode 3 is
`FUN_00652af0` (`0x00652af0`), which binds:

* `"mTransform"` = `&DAT_006d1510` = `renderer+0x150` (the camera's view*proj),
* `"mTransformLight"` = `&DAT_006d15d0` = `renderer+0x210` (the light matrix),
* `"Tex0"` (handle `0x6aabf8`) = the material's own texture,
* `"Tex1"` (handle `0x6aac00`) = `DAT_006d13f4` = `renderer+0x34`, **the shadow map**.

Its effect is slot 3 (`renderer+0x28 == 3`), i.e. the blob at `0x6a7e40`, length
`0x7ac` (`FUN_0064ff80:31-34`), committed as `remake/assets/shaders/effect_3.bin`:

```hlsl
// vs_1_1 (blob +0x46c), 24 slots
def c8, 0.5, -0.5, 0, 1
def c9, 2, 1, -1, -0.0199999996      ; the depth bias
def c10, 0.949999988, 0, 0, 0        ; the depth clamp
dcl_position v0 / dcl_color v1 / dcl_texcoord v2
oPos = v0 * mTransform                                   ; the camera's clip position
dp4 r1.w, v0, c7 / dp4 r0.w, v0, c6 / rcp r1.w, r1.w     ; 1/w of the LIGHT matrix
mad r0.w, r0.w, r1.w, c9.w                               ; z/w - 0.02
min oD1.w, r0.w, c10.x                                   ; clamp at 0.95
dp4 r1.w, v0, c4 / dp4 r0.w, v0, c5
mad oT1.x, (x/w), 0.5, 0.5
mad oT1.y, (-y/w), 0.5, 0.5                              ; the projective texcoord pair

// ps_1_1 (blob +0x34c)
def c0, 0.3, 0.3, 0.3, 0
def c1, 0, 0, 0, 0
tex t0 / tex t1                       ; t0 = albedo, t1 = the shadow map
sub r0.w, v1, t1_bias                 ; (own light depth - bias) - map alpha
cnd r1, r0.w, c0, c1                  ; 0.3 when the comparison holds, else 0
sub r0, t0, r1                        ; albedo - that
mul r0, r0, v0                        ; * the vertex colour
add r0.xyz, r0, v1                    ; + the vertex term
```

So a receiver in shadow has **0.3 subtracted from its albedo** (a flat subtract,
clamped at 0 by `sub`), not multiplied. The sampler for Tex1 is border-clamped to
black (`FUN_00651110` case 3/4, `0x6513ab-0x6513f6`: `SetSamplerState(1, ADDRESSU=1,
4=BORDER)`, `(1, ADDRESSV=2, 4)`, `(1, BORDERCOLOR=4, 0xff000000)`).

The other stage techniques repeat the same pattern: `FUN_00652af0` mode 4 and
`FUN_00652e40` modes 5/6 bind the same map, and `effect_4/5/6.bin`'s pixel shaders
are the same `sub` + `cnd` + `sub` with the depth in `oD0.w`/`oD1.w` instead. The
character toon techniques (`FUN_00652220`) also bind the map, as `"Tex2"` — and
**never read it**: their pixel shader samples `t2` and the arithmetic uses only
`t0`, `t1` and `v0`. There is no character self-shadowing in the original.

## Open item: the `cnd` threshold

`cnd` in ps_1_1 is documented as `dst = (src0.a > 0.5) ? src1 : src2`, and the
disassembled source is `r0.wwww`. With the recovered near/far the whole scene maps
into `z/w` in roughly `[0.13, 0.44]`, and a fighter's own height is only ~130
units of light-space depth (~0.12 of NDC), so a literal `> 0.5` test could never
shadow a ground receiver — while the original's own prints plainly show ground
shadows (`remake/docs/reference/battle-stamina.webp`: a full character silhouette
on the ground next to the runner). The two readings that make the code work are
`> 0` (the natural codegen for an HLSL `a > b`, and the reading under which the
cleared alpha of 1.0 and the 0.95 clamp both do exactly their job) and "the
hardware's `cnd` threshold is not 0.5 in this case". The port implements the
comparison as `own - bias > map`, i.e. the threshold-0 reading, and labels it a
port rule with this reason. Nothing else about the pass depends on the choice.

## What is NOT recovered

* The stage object's `+0x2c` flag (which selects mode 3 over mode 0 for a stage).
  It is not written by any function that names the stage global `DAT_006cfaf0`
  directly, so which option or asset property sets it is still open. The port
  gates its receiver term on the shadow option instead (PORT RULE).
* Whether the map is rendered per *view* in the original: `FUN_006507c0` and the
  caster pass are both inside the per-view loop, so yes in structure; the port
  keeps one map per view for the same reason.
* The exact sampler filtering of Tex1 beyond the border/clamp state above (the
  effect file's own sampler state is not in the dump).

## PORT RULES (labelled, issue #21 row 1)

1. **The clip tweak is omitted.** `matA` multiplies both the caster's clip
   position and the receiver's projected texcoords, so it cannot move a shadow;
   it only changes the map's texel density and the region it covers. The port
   builds the light view/projection without it and samples the untweaked frustum.
2. **The `cnd` threshold is read as 0, not 0.5** — see the open item above.
3. **The receiver is gated by the shadow option, not by the stage's technique
   flag.** The original's mode-3 selection lives in a stage property this
   recovery could not pin; the port's shadow option is the switch the user
   actually has.
4. **The light's up vector is world +Y.** The original reads the camera object's
   own up vector; every camera the port builds is Y-up (`glm::lookAtLH(eye, aim,
   (0,1,0))`), so the constant is the same vector.
5. **Border sampling becomes a shader-side range test.** WebGPU has no border
   address mode; the receiver treats a projected coordinate outside `[0,1]` as
   "no caster" instead of reading a black border, which is what the original's
   `D3DTADDRESS_BORDER` + black border colour produces.
