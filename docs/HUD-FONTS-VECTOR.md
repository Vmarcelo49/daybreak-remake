# HUD lettering and vector-sheet survey

> **Status: historical art survey; useful source material, not the runtime font
> plan.** The product keeps the game's HUD sheets and image-based numerals and
> labels. Product caption text uses the shared Gyrotrope Black face with the
> bundled Japanese fallback; see `assets/fonts/README.md` and `CJK-TEXT.md`.
> The proposed SDF-atlas migration and Nunito/M PLUS replacement fonts below
> were never adopted and are intentionally not treated as next steps.

## Atlas evidence

The survey measured the shipped CNV sheets (`data/object/p00.cnv`, `P01.cnv`,
`p02.cnv`, `p03.cnv`, `p06.cnv`, `p09.cnv`, `system.cnv`, plus chat/network
sheets) using the repository CNV decoder. The original artwork remains the
battle HUD path: `HudAtlas` loads image sheets, `HudComposer::composeBattle`
draws their numerals and labels, and falls back to text only when game data is
unavailable (`src/ui/hud_atlas.h`, `src/ui/hud.cpp`). `BATTLE-HUD-SPEC.md` is
the detailed current reference for atlas cells, pivots, screen coordinates and
remaining asset questions.

The main lettering findings still useful when checking that path:

- P00 contains the large white and red digit rows and the small green and yellow
  digit rows. The small yellow row uses 32-pixel cells (not the earlier 28-pixel
  pitch guess); `HudFont::SmallYellow` is the live FPS-counter row.
- The `LIMIT`, `MAX`, bar words and player/com tags are baked into HUD artwork.
  The P03 command labels (`適当`, `格闘`, `射撃`, `集中`, `各個`, `後退`) and
  alert/ring symbols are sprite cells, not dynamic font strings.
- The editable chat names are codepoints laid out by the soft-keyboard atlas;
  that grid's appearance is art, while the entered name text is rendered through
  the font chain. See `FRONTEND-PLAN.md` and the completed E6 entry in
  `ROADMAP-PENDING.md`.
- The original's GDI path serves unbounded result/chat/story text, not fixed
  image-based menu labels. The current cross-platform font decision and runtime
  implementation are recorded in `CJK-TEXT.md` and `assets/fonts/README.md`.

## Vector sheets retained as comparison material

`hud-vectors/` contains the adopted whole-sheet SVG delivery, its generator,
comparison plates and the original `vendor/hud_vetorizado_v2.zip`. These are
reviewable source/reference artifacts, not runtime HUD textures. The SVGs use
native 512-atlas coordinates; the comparison plates put the original and vector
renders side by side at 2x. The historical delivery measured about 4.8/255
mean absolute difference on P00; gradients, glows and rims are approximations,
not pixel-exact source art.

The committed sheets and comparison plates exist in the current tree. Their
pipeline needs extracted HUD PNG inputs and external tracing/rendering packages;
the delivery was not regenerated as part of this audit. `pipeline/build_all.py`
recreates sheets from scratch, so it overwrites sheet edits; the pipeline has no
marker-based hand-edit protection. Keep hand-tuned experiments outside the
regeneration path unless that behavior is changed.

## Historical proposal (not adopted)

The earlier recommendation was to bake these SVG sheets to an SDF atlas for
fixed HUD text and fetch Nunito Black Italic / M PLUS Rounded 1c Bold for
additional dynamic text. That proposal predates the current shared Gyrotrope +
Japanese fallback caption path and remains only as historical design context;
no SDF bake or replacement-font integration is present in the product. Fixed
HUD lettering continues to use the original atlas art. Open sprite-source
questions, including the battle `com` word, are listed in
`BATTLE-HUD-SPEC.md` §6.
