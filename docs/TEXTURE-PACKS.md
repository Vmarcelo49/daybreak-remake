# Texture packs

A pack is a folder of PNGs that replace the game's textures. Nothing in the install changes, and a
texture no pack has keeps the original.

## Where the game looks

Beside the executable, with no setting. The first folder that has a texture wins:

| Folder | Meant for |
|---|---|
| `--texture-pack=<dir>` | One run. This is the only folder a verification run reads |
| `custom-textures/` | The player's own changes, which a downloaded pack cannot overwrite |
| `hd-textures/` | The downloadable pack. The download and its prompt are not built yet |

## Making a pack

```bash
python3 tools/asset-tools/texture_pack.py extract --install Higurashi-Daybreak --out extracted
```

This writes 1,169 PNGs and `duplicates.txt`. The game has 3,303 3D textures, and many repeat across
costumes and stages, so each picture is written once. `--only data/rena,data/stage01` limits it to
those folders, which suits a first test. It needs Pillow.

1. Upscale the PNGs. Keep the folders and names, and keep the alpha channel.
2. Copy `duplicates.txt` into the result. Without it, the repeats keep the original.
3. Check it:

```bash
python3 tools/asset-tools/texture_pack.py verify --install Higurashi-Daybreak --pack upscaled
```

`verify` exits 1 on a name the game does not have, a lost alpha channel, a bad sheet size, an image
above 8192 px or a broken `duplicates.txt`. It warns on a changed shape and on files the game ignores,
such as a `.webp` from an upscaler, and it reports how many of the 3D textures are replaced.

Extraction leaves out menu, HUD and 2D sheets, the lighting ramp `data/directx/toon`, and a stage's
`_1` and `_2` mips.

## Layout

Each image sits at the game's path with `.png` in place of the extension. Names compare case-blind.

```
pack/data/rena/some-texture.png     replaces data/rena/some-texture.cnv
pack/data/title/back00.png          replaces data/title/back00.cnv
```

`duplicates.txt` has one `path<TAB>path it is the same as` per line. It applies inside its own folder,
so an image in `custom-textures/` still wins over a duplicate in `hd-textures/`.

## Sizes

| What | Size rule |
|---|---|
| Model and stage textures | Any size. Their coordinates are relative |
| Menu and HUD sheets | A whole multiple of the original, the same in both directions: 2x, 3x, 4x. Screens cut cells by the original's pixels, so any other size is refused with a message |

Translated labels are painted over a pack's sheet at its own scale.

## Rendering

A pack's texture always gets a full computed mip chain, including on fighters, whose originals have
none, because a large texture would shimmer at a distance. The original's `_1` and `_2` files are used
only under an original base.

This changes how distant ground looks. The original stops at `_2`, so far gravel stays busy and
contrasted; a full chain averages it out.

## Limits

- PNG only, native builds only. The web build has no folder to read.
- Measured on 2026-10-30 with every texture at 4x by Lanczos, which adds no detail, so a real upscaler
  will be larger: 271 MB on disk. `--screen=battle --frames=400` at 1280x720 took 3.8 s instead of
  2.3 s, with 622 MB of peak memory instead of 294 MB.
