# Texture packs

A pack is a folder of PNGs that replace the game's textures. Nothing in the install changes.

```bash
./build/linux/daybreak --texture-pack=/path/to/pack --install=Higurashi-Daybreak
```

## Layout

Each image sits at the game's path with `.png` in place of the extension. Names compare case-blind.
A texture the pack does not have keeps the original.

```
pack/data/rena/some-texture.png     replaces data/rena/some-texture.cnv
pack/data/title/back00.png          replaces data/title/back00.cnv
```

## Sizes

| What | Size rule |
|---|---|
| Model and stage textures | Any size. Their coordinates are relative |
| Menu and HUD sheets | A whole multiple of the original, the same in both directions: 2x, 3x, 4x. Screens cut cells by the original's pixels, so any other size is refused with a message |

Translated labels are painted over a pack's sheet at its own scale.

## Limits

- PNG only, native builds only. The web build has no folder to read.
- `--texture-pack` lasts one run. No setting saves it.
- Textures above 8192 px are refused by the renderer.
- A stage texture's shipped `_1` and `_2` mip files are still used only when their sizes fit the
  replacement; otherwise the mips are computed.
