# UI integration (applied)

The seams below cover the core HUD, screen-stack, and capture paths currently
used by `CMakeLists.txt` and `src/main.cpp`; they were merged in `48119f6`.
`ui/` needs a live `WGPUDevice`/`WGPUQueue`, the swapchain format and one
encoder per frame. Atlas screens/HUD use `fnd::assets::assetSource()`
(bundle-first CNV resolution, `hud_atlas.h:30-35`). Runtime captions load the
packaged Gyrotrope face and Japanese fallback through `ui/caption.h`; build and
font packaging details are in `CMakeLists.txt:200-215,236-243` and the target
build docs.

## CMake

`foundation_ui` is a static target with UI, screen, caption, result, settings,
and soft-keyboard translation units. It links `foundation_assets`, `foundation`,
and `foundation_movie` and includes `third_party/stb` privately for
`stb_truetype` (see `CMakeLists.txt:99-132`). The initial 2026-10-02 target
contained only sprite/font/HUD/text/fallback plus the screen stack and title
screen; the table here is intentionally omitted because `CMakeLists.txt` is the
current, authoritative source list.

`ui_wgsl` is include-embedded; no shader build rule is needed. Shared UI code
has no backend `#if`; presentation differences stay inside `gpu.cpp`.

## Historical main.cpp wiring sketch

This sketch records the early integration shape; current line references are
listed under [Front-end screens](#front-end-screens-the-second-seam) and the
release checklist.

Historically, initialization was described as `SpriteRenderer`, `ScreenStack`,
and `HudComposer`; the app currently initializes these in separate boot paths.
HUD state is filled for match views and the scripted versus timeline, then
composed over the 3D frame. Menus draw through `ui::drawScreenFrame` on the
window path (`main.cpp:6207-6212`) and through `screenCaptureHook` for captures
(`main.cpp:5662-5667,6176-6178`). `ui::FallbackOverlay` remains library support,
not wired into a frame path.

Runtime composition notes:

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
- **HUD asset fallbacks.** Battle art sheets are all-or-nothing: one missing
  sheet selects the text HUD and logs the missing asset (`hud.cpp:259-273`).
  Text labels prefer the runtime caption font chain; if it cannot load, the
  embedded bitmap atlas is used (`hud.cpp:110-134`).
- **Text input encoding.** `ui::TextLayer` accepts UTF-8 and implements the
  `\cRRGGBB`/`\n` control codes; its bitmap fallback decodes via `utf8Next`.
  Shift-JIS game strings are converted with `xm::sjisToUtf8` before rendering.
  The battle HUD's art labels (`LIMIT`, `MAIN`, `適当`, …) remain atlas cells.

## Front-end screens (the second seam)

`ui::ScreenStack`/`ui::Screen`/`makeScreen`/`parseScreenId` (src/ui/screen.h)
port FUN_00657c80's switcher (the 25-frame fade) and FUN_004020a0's factory;
`screen_title.{h,cpp}` is scene 1 (FUN_00410d60/FUN_00410f60/FUN_004114f0, all
atlas art). `--screen=<id|name>` boots one, `--script=` drives it, `--out`
captures it (main.cpp:1687-1725); a new screen is one factory row plus one class
(screen.cpp:47-49).
