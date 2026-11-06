# Path map after the 2026-10-30 reorganization

This tree is the same product and the same research corpus, moved so that the layout says
what each part is. The map below is complete for the paths the 2026-10-30 reorganization
touched; where a path does not appear, its name is unchanged. That move landed on `main`;
`docs/archive/` keeps the closed plans with their original text.

## The product tree

| Before | After |
|---|---|
| `remake/foundation/CMakeLists.txt` | `CMakeLists.txt` |
| `remake/foundation/build.sh` | `build.sh` |
| `remake/foundation/VERSION` | `VERSION` |
| `remake/foundation/README.md` | `README.md` (rewritten; the old text is merged into it) |
| `remake/foundation/src/**` | `src/**` (regrouped below) |
| `remake/foundation/tests/**` | `tests/**` |
| `remake/foundation/cmake/**` | `cmake/**` |
| `remake/foundation/scripts/**` | `scripts/**` |
| `remake/foundation/package/**` | `package/**` |
| `remake/foundation/webdelivery/**` | `webdelivery/**` |
| `remake/foundation/assets/**` | `assets/**` |
| `remake/foundation/tools/**` | `tools/**` |
| `remake/foundation/build/`, `third_party/` | `build/`, `third_party/` (both ignored) |
| `remake/foundation/build/linux/foundation_demo` | `build/linux/daybreak` |
| the packaged binary `foundation_demo` | `daybreak-bin` (the launcher keeps `daybreak`) |
| `remake/tools/asset-tools/**` | `tools/asset-tools/**` |
| `remake/tools/hook-tracer/**` | `tools/hook-tracer/**` |
| `remake/scripts/fetch_deps.sh`, `remake/scripts/r2.sh` | deleted (the first duplicated the product's fetcher; the second pointed at a path that never existed) |
| `remake/README.md` | `docs/archive/remake-README.md` |
| `remake/.gitignore` | absorbed into `.gitignore` |

CMake targets dropped the `foundation_` prefix: `foundation_assets` → `assets`,
`foundation` → `runtime`, `foundation_render` → `render`, `foundation_ui` → `ui`,
`foundation_media` → `media`, `foundation_game` → `game_interfaces`,
`foundation_physics` → `physics`, `foundation_gameplay` → `gameplay`,
`foundation_sim` → `battle_core`, `foundation_sim_zlib` → `battle_core_zlib`,
`foundation_sim_backend` → `battle_backend`, `foundation_caption_fonts` → `caption_fonts`,
`foundation_demo` → `daybreak`.

## `src/` inside the product

| Before | After |
|---|---|
| `src/main.cpp` | `src/app/main.cpp` (split into the blocks below) |
| `src/sim/battle.{h,cpp}` | `src/battle/battle.{h,cpp}` |
| `src/sim/core_battle.{h,cpp}` | `src/battle/core_battle.{h,cpp}` |
| `src/sim/simctl.cpp`, `src/sim/simfuzz.cpp` | `src/battle/simctl.cpp`, `src/battle/simfuzz.cpp` |
| `src/sim/script.h`, `src/sim/core_prelude.h` | `src/battle/script.h`, `src/battle/core_prelude.h` |
| `src/sim/core/**` | `src/battle/core/**` (content untouched) |
| `src/game/battle_types.h`, `battle_view.h`, `match_view.h` | `src/battle/` |
| `src/gameplay/character_moves.*`, `combat_record.h`, `weapon_definition.*`, `weapon_trail.h`, `match_economy.*`, `rng.h`, `held_axis.h`, `battle_pause.h`, `fixed_step.h` | `src/battle/` |
| `src/gameplay/hud_fill.*` | `src/hud/hud_fill.*` |
| `src/gameplay/result_title.*` | `src/frontend/result_title.*` |
| `src/gameplay/arena_camera.*` | `src/camera/arena_camera.*` |
| `src/render/arena_camera.h` | `src/camera/arena_view.h` (the two names no longer collide) |
| `src/game/camera_collision.h`, `fighter_pose.h` | `src/camera/` |
| `src/game/hud_bridge.h`, `hud_values.h` | `src/hud/` |
| `src/game/view_layout.h` | `src/hud/view_layout.h` |
| `src/game/effect_catalog.h`, `effect_events.h`, `fx_cards.h`, `aura_attach.h`, `muzzle_slot.h`, `shot_visual.h` | `src/render/` |
| `src/game/game_check.cpp` | `src/app/game_check.cpp` |
| `src/ui/hud.*`, `hud_atlas.*`, `pause_layout.h`, `fallback.*` | `src/hud/` |
| `src/ui/screen*.{h,cpp}`, `frontend_*.{h,cpp}`, `participants.h`, `result_quote.*`, `soft_keyboard.*` | `src/frontend/` |
| `src/ui/{sprite,font,text,caption}.{h,cpp}` | `src/ui/` (unchanged) |
| `src/{assets,audio,gpu,input,movie,platform,physics,render,settings,shaders}/**` | unchanged |

The app blocks under `src/app/` are `app.h` (shared types), `app_forward.inc` (internal
declarations), `options.inc`, `scene.inc`, `combat_audio.inc`, `match.inc`,
`render_capture.inc` and `frame_loop.inc`; `main.cpp` keeps the entry points and the wiring.
The app is one translation unit, and the blocks are included from `main.cpp` for that reason.

## The documentation and the evidence

| Before | After |
|---|---|
| `remake/docs/**` | `docs/**` |
| `remake/foundation/docs/**` | `docs/**` |
| `docs/reports/ginkiha-*.md`, `docs/reports/fighter-*.md` | `docs/archive/` |
| `docs/PILOT-SEAM.md`, `docs/PILOT-EVIDENCE-CONTRACT.md`, `docs/RENA0-*.md` | `docs/archive/` |
| `docs/FULL-REPLACEMENT-PLAN.md`, `docs/FRONTEND-PLAN.md`, `docs/port-from-mvp-plan.md`, `docs/roadmap.md`, `docs/placeholders.md` | `docs/archive/` |
| `remake/assets/**` | `research/evidence/assets/**` |
| `remake/tests/parity-baseline/**` | `research/evidence/parity-baseline/**` |
| `remake/tests/npr-evidence/**` | `research/evidence/npr-evidence/**` |
| `remake/docs/reference/**` | `docs/reference/**` |

Archived documents keep their text, so paths inside them are historical. Use this table, not
the text, when following one of them.

## Documents archived after the reorganization (2026-11-05)

These documents declared themselves historical, or recorded work that was already closed.
They keep their original text, plus a one-line archive banner where the title still read as
current. Current documents use the new path; the historical work logs in
`docs/archive/DIRECTION-STATUS.md` and `docs/agents/` keep the old one.

| Before | After |
|---|---|
| `docs/status.md` | `docs/archive/status.md` |
| `docs/reverse-engineering.md` | `docs/archive/reverse-engineering.md` |
| `docs/HUD-FONTS-VECTOR.md` | `docs/archive/HUD-FONTS-VECTOR.md` |
| `docs/PORT-PLAN.md` | `docs/archive/PORT-PLAN.md` |
| `docs/UI-VERIFY.md` | `docs/archive/UI-VERIFY.md` |
| `docs/RELEASE-LINUX.md` | `docs/archive/RELEASE-LINUX.md` |
| `docs/reports/checks-audit-2026-10-10.md` | `docs/archive/checks-audit-2026-10-10.md` |
| `docs/reports/reorganization-brief-2026-10-30.md` | `docs/archive/reorganization-brief-2026-10-30.md` |
| `docs/DIRECTION.md` (retired milestone plan) | `docs/archive/DIRECTION.md`; current direction remains at `docs/DIRECTION.md` |
| `docs/DIRECTION-STATUS.md` | `docs/archive/DIRECTION-STATUS.md` |
| `docs/SCOREBOARD.md` | `docs/archive/SCOREBOARD.md` |
| `docs/EXCEPTIONS.md` | `docs/archive/EXCEPTIONS.md` |
| `docs/QUESTIONS.md` (historical entries) | `docs/archive/QUESTIONS.md`; current questions remain at `docs/QUESTIONS.md` |
