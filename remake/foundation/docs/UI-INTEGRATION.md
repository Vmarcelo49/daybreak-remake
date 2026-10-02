# UI integration (applied)

The seams below are the ones `CMakeLists.txt` and `src/main.cpp` actually use
(merged in `48119f6`; PORT-PLAN's parent-owned phase is over). `ui/` needs a
live `WGPUDevice`/`WGPUQueue`, the swapchain format and one encoder per frame —
and, for the atlas HUD and the screens, `fnd::assets::assetSource()`
(bundle-first CNV resolution, hud_atlas.h:30-35) plus the fetched faces under
`third_party/fonts/` for the text paths.

## CMake

```cmake
add_library(foundation_ui STATIC
    src/ui/sprite.cpp
    src/ui/font.cpp
    src/ui/hud.cpp
    src/ui/hud_atlas.cpp
    src/ui/text.cpp
    src/ui/fallback.cpp
    src/ui/screen.cpp
    src/ui/screen_title.cpp)
target_include_directories(foundation_ui PUBLIC src)
target_include_directories(foundation_ui PRIVATE third_party/stb)  # stb_truetype.h
# hud_atlas.cpp decodes HUD sheets through xm::decodeCnvImage, which assets/ owns.
target_link_libraries(foundation_ui PUBLIC foundation_assets)
target_link_libraries(foundation_ui PUBLIC foundation)

target_link_libraries(foundation_demo PRIVATE foundation_ui)
```

`src/shaders/ui_wgsl.h` is `#include`-embedded like `model_wgsl.h`; no build
rule needed. No compile definitions are required on any target: `ui/` has no
backend `#if` (the present-call difference stays inside `gpu.cpp`'s
`endFrame`, which the UI pass never touches).

## main.cpp wiring sketch

Init once (main.cpp:491-495): `ui::SpriteRenderer uiRenderer;
ui::ScreenStack screens; ui::HudComposer hudComposer;` — with
`HudComposer::uploadFont` non-fatal on the game path but deliberately fatal on
the `--hud-test` capture rig, because a capture without labels would silently
prove less (main.cpp:1406-1411).

Per frame: `uiRenderer.beginFrame(w, h)` then
`hudComposer.compose(uiRenderer, state, layout)` in the same encoder the 3D pass
used (the `HudTestHook`, main.cpp:1839-1846), state filled by
`gameplay/hud_fill.h`'s `hudStateFor` for a match and `game/hud_bridge.h`'s
`makeHudState` for the versus timeline. Menus are the other path:
`ui::drawScreenFrame(screens, ui, w, h, enc, view, format, error)` on the window
path (main.cpp:2016), `screenCaptureHook` under `--screen --out`
(main.cpp:1856-1860, 1987). `ui::FallbackOverlay` is compiled but not wired into
any frame.

Notes for the integrator:

- **Same encoder, one submit.** HUD quads join the frame the 3D pass started;
  `render()` opens a `Load`-preserving pass, so ordering is 3D-then-UI with no
  extra present and no FIFO change.
- **`computeHudLayout` is the fallback's layout.** `compose()` draws the
  original's atlas HUD whenever `HudAtlas::upload` resolved the sheets (fixed
  800x600 anchors from FUN_00644150), and falls back to the DX9 text/bars body —
  `computeHudLayout`'s rects plus the font chain — only when a sheet is missing
  (hud.cpp:393-410).
- **Resize-safe.** `beginFrame` re-takes the viewport every frame and the
  shader maps pixels to NDC from a per-frame uniform — no pipeline or buffer
  rebuild on `WINDOW_PIXEL_SIZE_CHANGED` beyond the existing swapchain
  reconfigure.
- **Offscreen captures.** `SceneRenderer::capture`/`captureUi` take a
  `UiHook(encoder, view, format, userdata)`; the hook does the
  `beginFrame`/`render` pair (scene_renderer.h:226-252; the HUD hook is
  main.cpp:1839-1846, called from `captureHook` at main.cpp:1901-1906).
  `capture()` fails on a menu frame because there is no 3D pass, so menus use
  `captureUi()` against a cleared opaque-black target (main.cpp:1987-1989).
- **Two atlases, two failure modes.** The battle sheets are all-or-nothing: one
  missing sheet puts the whole text HUD back with a single stderr line naming it
  (hud.cpp:259-273). The label atlas independently prefers the fetched font
  chain (`loadHudChain`) over the bitmap atlas; only when both are absent are
  labels skipped and bars still drawn (hud.cpp:158-210, 213-246).
- **Text input encoding.** Strings are UTF-8: the bitmap path decodes through
  `ui::utf8Next`, and `ui::TextLayer` (`ui/text.h`) is the CJK-capable path with
  `\cRRGGBB`/`\n` control codes. Shift-JIS game names must pass through
  `xm::sjisToUtf8` (assets/cnv.h) first, as texture resolution does. The battle
  HUD's own labels (`LIMIT`, `MAIN`, `適当`, …) are atlas cells, not strings.

## Front-end screens (the second seam)

`ui::ScreenStack`/`ui::Screen`/`makeScreen`/`parseScreenId` (src/ui/screen.h)
port FUN_00657c80's switcher (the 25-frame fade) and FUN_004020a0's factory;
`screen_title.{h,cpp}` is scene 1 (FUN_00410d60/FUN_00410f60/FUN_004114f0, all
atlas art). `--screen=<id|name>` boots one, `--script=` drives it, `--out`
captures it (main.cpp:1687-1725); a new screen is one factory row plus one class
(screen.cpp:47-49).
