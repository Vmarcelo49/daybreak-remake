# Runtime caption fonts

`gyrotrope-black.otf` is the user-selected Gyrotrope Black face for all new
runtime text. Its SHA-256 is
`05cdab1a1d4d50939725beceb39fa424a0a3b3a0406892113fff67190e104197`.

Use `ui::CaptionText` for captions and `ui::loadCaptionFont` when a screen
owns its own `TextLayer`. Call `CaptionText::prepare` with all frame strings
before drawing text that may add Unicode glyphs to the atlas. HUD captions,
result text, settings/key configuration and diagnostics use this shared
choice. Existing image labels and image-based numerals keep their original art.

Gyrotrope lacks Japanese glyphs; `NotoSansCJKjp-Regular.otf` supplies them
through the font chain. The repository-level `fetch_deps.sh` fetches it into
ignored `foundation/third_party/fonts/`, separate from `foundation/build.sh deps`.
Native packages include both faces under `assets/fonts`; web preloads available
faces there.
The embedded bitmap font remains an emergency fallback for missing fonts or
unsupported glyphs. Historical DX9 metric tests explicitly use their original
Liberation Sans reference and do not define the product's caption face.
