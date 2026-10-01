# UI integration proposal (parent-owned seams — do not apply in this track)

`CMakeLists.txt` and `src/main.cpp` are parent-owned until this track is ready
to merge (PORT-PLAN merge order). Apply the snippets below verbatim or adapted;
nothing in `src/ui/*` assumes either — the library only needs a live
`WGPUDevice`/`WGPUQueue`, the swapchain format, and one encoder per frame.

## CMake

```cmake
# Next to foundation_render: same shape (needs gpu helpers + glm types),
# no new third-party dependency.
add_library(foundation_ui STATIC
    src/ui/sprite.cpp
    src/ui/font.cpp
    src/ui/hud.cpp
    src/ui/fallback.cpp)
target_include_directories(foundation_ui PUBLIC src)
target_link_libraries(foundation_ui PUBLIC foundation glm)

# Demo wiring (verification only):
target_link_libraries(foundation_demo PRIVATE foundation_ui)
```

`src/shaders/ui_wgsl.h` is `#include`-embedded like `model_wgsl.h`; no build
rule needed. No compile definitions are required on any target: `ui/` has no
backend `#if` (the present-call difference stays inside `gpu.cpp`'s
`endFrame`, which the UI pass never touches).

## main.cpp wiring sketch

Init once, next to the scene renderer:

```cpp
#include "ui/fallback.h"
#include "ui/hud.h"
#include "ui/sprite.h"

ui::SpriteRenderer ui;
ui::HudComposer hud;
ui::FallbackOverlay diag;
if (!ui.init(ctx.device, ctx.queue, error)) { /* fatal like renderer init */ }
std::string uiError;
if (!hud.uploadFont(ui, uiError)) { /* non-fatal: bars still draw, note it */ }
if (!diag.uploadFont(ui, uiError)) { /* non-fatal: panel still draws */ }
```

Per frame, after `renderer.render(target, …)` recorded into the same encoder
(`frame.encoder`) and before `gpu::endFrame`:

```cpp
ui.beginFrame(sc.width, sc.height);
if (haveHudState) {
    ui::HudState st;      // fill from game state (HP, gauges, sting timer…)
    hud.compose(ui, st, ui::computeHudLayout(sc.width, sc.height));
} else if (!error.empty() || showDiag) {
    auto lines = ui::buildDiagLines(ctx.adapterName, ctx.backend,
                                    sc.width, sc.height, error,
                                    frames, avgDeltaMs);
    size_t longest = 0;
    for (auto& l : lines) longest = std::max(longest, l.size());
    diag.draw(ui, ui::computeDiagPanel(sc.width, sc.height, lines.size(), longest), lines);
}
if (!ui.render(frame.encoder, frame.view, sc.format, error)) { /* fail frame */ }
```

Notes for the integrator:

- **Same encoder, one submit.** HUD quads join the frame the 3D pass started;
  `render()` opens a `Load`-preserving pass, so ordering is 3D-then-UI with no
  extra present and no FIFO change.
- **Resize-safe.** `beginFrame` re-takes the viewport every frame and the
  shader maps pixels to NDC from a per-frame uniform — no pipeline or buffer
  rebuild on `WINDOW_PIXEL_SIZE_CHANGED` beyond the existing swapchain
  reconfigure.
- **Offscreen captures** keep working unchanged: `SceneRenderer::capture`
  renders 3D into its own texture; add the same two calls (`beginFrame` with
  the capture size, `render` into the capture encoder) before its
  copy-to-readback to get HUD-in-capture. The scratch test in `UI-VERIFY.md`
  proves the pattern headless.
- **Font upload failure is non-fatal by design.** `compose()` skips labels
  when the atlas id is `-1` but still draws bars; `FallbackOverlay::draw`
  still draws its panel. Wire the error string into the diagnostics line so
  the failure is visible instead of silent.
- **Text input encoding.** HUD labels are UTF-8 (`pushText` decodes it);
  Shift-JIS game names must pass through `xm::sjisToUtf8` first, the same
  conversion texture resolution uses.
