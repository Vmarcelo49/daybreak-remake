cmake_minimum_required(VERSION 3.20)

# The version lives in VERSION so that bumping it is a one-line act — and the only
# thing that triggers the multi-target CI build (see .github/workflows).
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" FOUNDATION_VERSION)
string(STRIP "${FOUNDATION_VERSION}" FOUNDATION_VERSION)
project(daybreak_foundation VERSION ${FOUNDATION_VERSION} LANGUAGES C CXX)

# Multi-platform foundation: SDL3 + WebGPU (webgpu.h), built for Linux, Windows
# (MinGW cross-compile) and the web (Emscripten) from this one file.
#
#   linux    cmake -B build/linux   -GNinja
#   windows  cmake -B build/windows -GNinja -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/mingw-w64-x86_64.cmake
#   web      emcmake cmake -B build/web -GNinja
#
# The WebGPU implementation is picked per target by third_party/webgpu (the
# WebGPU-distribution project): wgpu-native natively, emdawnwebgpu on the web.

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE AND NOT EMSCRIPTEN)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/third_party/webgpu/CMakeLists.txt")
    message(FATAL_ERROR "third_party/ is empty — run scripts/fetch_deps.sh first")
endif()
add_subdirectory(third_party/webgpu)

if(EMSCRIPTEN)
    # SDL3 is supplied by the Emscripten port; it also owns the <canvas>.
    add_compile_options(-sUSE_SDL=3)
    add_link_options(-sUSE_SDL=3 -sASYNCIFY=1 -sALLOW_MEMORY_GROWTH=1 -sSTACK_SIZE=1048576 -sFETCH=1 -lidbfs.js)
    add_link_options("SHELL:--preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets/fonts@/assets/fonts")
    # Local game data can be mounted at /assets for browser verification. Both stay
    # local-only: the data is copyrighted and build/ is ignored, so this never changes
    # what the plain web build contains.
    set(FOUNDATION_WEB_ASSETS "" CACHE PATH "Local directory preloaded as /assets in the web build")
    set(FOUNDATION_WEB_ASSET "" CACHE STRING "Single asset argument injected on web, e.g. --character=/assets/akane:0")
    if(FOUNDATION_WEB_ASSETS)
        add_link_options("SHELL:--preload-file ${FOUNDATION_WEB_ASSETS}@/assets")
    endif()
else()
    find_package(SDL3 REQUIRED)
    add_subdirectory(third_party/sdl3webgpu)
endif()

# glm is the asset layer's only third-party dependency (xmodel.h works in mat4/vec3).
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/third_party/glm")

# The Daybreak asset layer: .X/.cnv decoding and scene assembly, unchanged from the
# backend it was proved on. dat_bundle/dat_crypto read the shipped daybreakXX.dat
# archives, so an install can be used without extracting it (see docs/CJK-TEXT.md
# for the sibling text decision and tests/dat_bundle_bytes.cpp for the parity proof).
add_library(foundation_assets STATIC
    src/assets/assets.cpp
    src/assets/asset_source.cpp
    src/assets/dat_bundle.cpp
    src/assets/dat_crypto.cpp
    src/assets/exe_strings.cpp)
target_include_directories(foundation_assets PUBLIC src/assets)
target_link_libraries(foundation_assets PUBLIC glm)

add_library(foundation STATIC
    src/platform/platform.cpp
    src/platform/surface.cpp
    src/platform/web_pack.cpp
    src/gpu/gpu.cpp)
target_include_directories(foundation PUBLIC src)
target_link_libraries(foundation PUBLIC webgpu)

if(NOT EMSCRIPTEN)
    target_link_libraries(foundation PUBLIC SDL3::SDL3 sdl3webgpu)
endif()

# The scene renderer is the one layer above gpu/ that also needs the asset layer: it
# builds the pipelines raw WebGPU requires and consumes xm::Vertex / xm::DrawUniform.
# debug_prims is its line-list sibling: a second pass over the same encoder, used to
# annotate a frame (capture diagnostics), with a device-free geometry half the host
# test below exercises.
add_library(foundation_render STATIC
    src/render/scene_renderer.cpp
    src/render/debug_prims.cpp)
target_link_libraries(foundation_render PUBLIC foundation foundation_assets)

# The 2D/UI layer: sprite batch, bitmap font, HUD composition, diagnostics. Same
# shape as foundation_render; verified headless before wiring (docs/UI-VERIFY.md).
add_library(foundation_ui STATIC
    src/ui/sprite.cpp
    src/ui/font.cpp
    src/ui/caption.cpp
    src/ui/hud.cpp
    src/ui/hud_atlas.cpp
    src/ui/text.cpp
    src/ui/fallback.cpp
    src/ui/screen.cpp
    src/ui/screen_title.cpp
    src/ui/screen_select.cpp
    src/ui/screen_stage_select.cpp
    src/ui/screen_vs.cpp
    src/ui/screen_result.cpp
    src/ui/result_quote.cpp
    src/ui/frontend_launch.cpp
    src/ui/frontend_settings.cpp
    src/settings/user_settings.cpp
    src/ui/screen_options.cpp
    src/ui/soft_keyboard.cpp)
target_include_directories(foundation_ui PUBLIC src)
# hud_atlas.cpp decodes HUD sheets through xm::decodeCnvImage, which assets/ owns: state it
# here so a target linking foundation_ui alone still links.
target_link_libraries(foundation_ui PUBLIC foundation_assets)
# stb_truetype for the CJK rasterizer, alongside the vendored stb_vorbis the media
# layer uses (foundation_media adds the same directory).
target_include_directories(foundation_ui PRIVATE third_party/stb)
target_link_libraries(foundation_ui PUBLIC foundation)

# Media/input contracts and tables. Header-only by design (they unit-test
# anywhere), so this library is one TU of static_asserts against the real SDL3
# headers: the tables cannot drift from SDL3 without failing every target build.
add_library(foundation_media STATIC src/input/pin_tables.cpp src/audio/audio_engine.cpp
    src/audio/combat_audio.cpp
                          src/input/input_backend.cpp)
target_include_directories(foundation_media PUBLIC src)
target_include_directories(foundation_media PRIVATE third_party/stb)
if(NOT EMSCRIPTEN)
    target_link_libraries(foundation_media PUBLIC SDL3::SDL3)
endif()

# Game-facing interfaces: header-only (glm+std, plus hud_bridge.h over ui/), so
# this library is a check TU that forces every target to compile them — the
# same rationale as the pin TU above.
add_library(foundation_game STATIC src/game/game_check.cpp)
target_include_directories(foundation_game PUBLIC src)
target_link_libraries(foundation_game PUBLIC foundation_ui glm)

# Collision queries over loaded meshes: the D3DXIntersect replacement (CPU
# triangle raycast) plus the arena camera clamp's physics side. No WebGPU and no
# window, so gameplay code links it without a device.
add_library(foundation_physics STATIC src/physics/raycast.cpp)
target_include_directories(foundation_physics PUBLIC src)
target_link_libraries(foundation_physics PUBLIC foundation_assets glm)

# The ported game truth (FULL-REPLACEMENT-PLAN.md Phase 2): fighter/projectile
# simulation, the match loop that composes them in the reference's order, the match
# economy and the HUD value computation — lifted out of remake/src so the WebGPU path
# runs the game's own rules instead of a scripted vignette. hud_fill.cpp is the one TU
# here that reaches ui/ -> webgpu.h (through game/hud_bridge.h), which foundation_ui
# supplies; the simulation half is std + glm + the ported raycast.
add_library(foundation_gameplay STATIC
    src/gameplay/arena_camera.cpp
    src/gameplay/fighter.cpp
    src/gameplay/projectile.cpp
    src/gameplay/match.cpp
    src/gameplay/match_economy.cpp
    src/gameplay/character_moves.cpp
    src/gameplay/weapon_definition.cpp
    src/gameplay/bot_brain.cpp
    src/gameplay/bot_input.cpp
    src/gameplay/hud_fill.cpp
    src/gameplay/result_title.cpp)
target_include_directories(foundation_gameplay PUBLIC src)
target_link_libraries(foundation_gameplay
    PUBLIC foundation_physics
    PRIVATE foundation_ui)

add_executable(foundation_demo src/main.cpp)
target_link_libraries(foundation_demo PRIVATE foundation_render foundation_ui foundation_media foundation_game foundation_physics foundation_gameplay)

set(CAPTION_CJK_FONT "${CMAKE_CURRENT_SOURCE_DIR}/third_party/fonts/NotoSansCJKjp-Regular.otf")
if(EMSCRIPTEN)
    set_property(TARGET foundation_demo APPEND PROPERTY LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/assets/fonts/gyrotrope-black.otf")
    if(EXISTS "${CAPTION_CJK_FONT}")
        target_link_options(foundation_demo PRIVATE "SHELL:--preload-file ${CAPTION_CJK_FONT}@/assets/fonts/NotoSansCJKjp-Regular.otf")
        set_property(TARGET foundation_demo APPEND PROPERTY LINK_DEPENDS "${CAPTION_CJK_FONT}")
    endif()
else()
    add_custom_target(foundation_caption_fonts
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets/fonts" "$<TARGET_FILE_DIR:foundation_demo>/assets/fonts")
    add_dependencies(foundation_demo foundation_caption_fonts)
    if(EXISTS "${CAPTION_CJK_FONT}")
        add_custom_command(TARGET foundation_caption_fonts POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CAPTION_CJK_FONT}" "$<TARGET_FILE_DIR:foundation_demo>/assets/fonts/NotoSansCJKjp-Regular.otf")
    endif()
endif()

# Host-side tests. Native-only on purpose: the Windows target is cross-compiled and
# the web target cannot run a host binary, so neither can execute them, and building
# them there would only add a target nothing runs. All three are device-free by design:
# debug_prims_geometry compiles the renderer's geometry half without webgpu.h,
# raycast_analytic needs only glm and real .X collision meshes, and dat_bundle_bytes
# needs python3 plus a local install at run time (it skips itself without one).
if(NOT EMSCRIPTEN AND NOT CMAKE_CROSSCOMPILING)
    enable_testing()

    # The split-screen HUD placement check: a capture test, because the defect it pins
    # lived in the GPU path (one shared viewport uniform rewritten by every pass), which
    # no layout test can see. It renders two headless frames through --hud-probe, so it
    # skips itself (exit 77) without a renderer or the game data.
    find_package(Python3 COMPONENTS Interpreter QUIET)
    if(Python3_Interpreter_FOUND)
        add_test(NAME hud_cell_scale
                 COMMAND ${Python3_EXECUTABLE}
                         "${CMAKE_CURRENT_SOURCE_DIR}/tests/hud_cell_scale.py"
                         "$<TARGET_FILE:foundation_demo>" "${CMAKE_CURRENT_SOURCE_DIR}/../../Higurashi-Daybreak"
                         "${CMAKE_CURRENT_SOURCE_DIR}")
        set_tests_properties(hud_cell_scale PROPERTIES SKIP_RETURN_CODE 77 TIMEOUT 900)
    endif()

    add_executable(debug_prims_geometry tests/debug_prims_geometry.cpp)
    target_include_directories(debug_prims_geometry PRIVATE src)
    target_link_libraries(debug_prims_geometry PRIVATE glm)
    add_test(NAME debug_prims_geometry COMMAND debug_prims_geometry)

    # Links only glm: the test defines XMODEL_IMPLEMENTATION itself (it loads real .X
    # collision meshes), so foundation_assets would be a duplicate-definition error.
    add_executable(raycast_analytic tests/raycast_analytic.cpp src/physics/raycast.cpp)
    target_include_directories(raycast_analytic PRIVATE src)
    target_link_libraries(raycast_analytic PRIVATE glm)
    add_test(NAME raycast_analytic COMMAND raycast_analytic)

    # Skips itself with a clear message when $GAME_DIR (or the default install) is
    # absent, so the suite stays runnable on a checkout without the game data.
    add_executable(dat_bundle_bytes tests/dat_bundle_bytes.cpp
                   src/assets/dat_bundle.cpp src/assets/dat_crypto.cpp
                   src/assets/asset_source.cpp)
    target_include_directories(dat_bundle_bytes PRIVATE src)
    add_test(NAME dat_bundle_bytes COMMAND dat_bundle_bytes)

    # Economy + HUD fill: device-free, and it links match_economy.cpp only —
    # hud_fill.cpp's bridge half needs webgpu.h, so the test includes just the
    # value header (the seam TU is compiled by foundation_gameplay).
    add_executable(match_economy_test tests/match_economy_test.cpp
                   src/gameplay/match_economy.cpp)
    target_include_directories(match_economy_test PRIVATE src)
    add_test(NAME match_economy_test COMMAND match_economy_test)

    # The ported simulation: compiles the gameplay sources directly, like
    # raycast_analytic above, because the test defines XMODEL_IMPLEMENTATION itself
    # (it builds synthetic xm::Models), so linking foundation_assets as well would be
    # a duplicate-definition error.
    add_executable(fighter_script_test tests/fighter_script_test.cpp
                   src/gameplay/fighter.cpp src/gameplay/projectile.cpp
                   src/gameplay/character_moves.cpp src/gameplay/weapon_definition.cpp
                   src/physics/raycast.cpp)
    target_include_directories(fighter_script_test PRIVATE src)
    target_link_libraries(fighter_script_test PRIVATE glm)
    add_test(NAME fighter_script_test COMMAND fighter_script_test)

    # The effect-card live set: header-only game logic (glm + std), no device.
    add_executable(fx_cards_test tests/fx_cards_test.cpp)
    target_include_directories(fx_cards_test PRIVATE src)
    target_link_libraries(fx_cards_test PRIVATE glm)
    add_test(NAME fx_cards_test COMMAND fx_cards_test)

    # The env.dat spawn contract: owns the scene/cnv/xmodel implementations
    # itself (see the test header), so like the XMODEL_IMPLEMENTATION tests
    # it must not link foundation_assets. Skips without a game install.
    add_executable(env_spawn_test tests/env_spawn_test.cpp
                   src/assets/asset_source.cpp src/assets/dat_bundle.cpp
                   src/assets/dat_crypto.cpp)
    target_include_directories(env_spawn_test PRIVATE src)
    target_link_libraries(env_spawn_test PRIVATE glm)
    add_test(NAME env_spawn_test COMMAND env_spawn_test)

    # The arena camera: game state only (no device). Compiles the ported raycast in
    # directly, like the two tests above; it builds its xm::Model fixtures by hand, so
    # it must not link foundation_assets (which defines XMODEL_IMPLEMENTATION).
    add_executable(arena_camera_test tests/arena_camera_test.cpp
                   src/gameplay/arena_camera.cpp src/physics/raycast.cpp)
    target_include_directories(arena_camera_test PRIVATE src)
    target_link_libraries(arena_camera_test PRIVATE glm)
    add_test(NAME arena_camera_test COMMAND arena_camera_test)

    # Swept stage movement, ground support, landing and match spawn recovery. Synthetic
    # geometry runs everywhere; passing a local data/ directory also checks real stages.
    add_executable(stage_movement_test tests/stage_movement_test.cpp)
    target_link_libraries(stage_movement_test PRIVATE foundation_gameplay)
    add_test(NAME stage_movement_test COMMAND stage_movement_test)

    # The per-weapon combat definitions (issue #9): the data/item/NNN.dat reader
    # transcribed from FUN_00433eb0, every shipped weapon swept, and a match smoke run
    # for all 46 legal character/weapon selections. Device-free; the shipped-data parts
    # skip themselves when the install is absent.
    add_executable(weapon_definition_test tests/weapon_definition_test.cpp)
    target_link_libraries(weapon_definition_test PRIVATE foundation_gameplay)
    add_test(NAME weapon_definition_test COMMAND weapon_definition_test)

    # Issue #10: directional/aerial/multi-target melee. Needs the gameplay lib for
    # Match/Fighter and the physics lib for the #7 collision mesh; the character move
    # table parse is device-free and skips its shipped-data half without an install.
    add_executable(melee_rules_test tests/melee_rules_test.cpp)
    target_link_libraries(melee_rules_test PRIVATE foundation_gameplay)
    add_test(NAME melee_rules_test COMMAND melee_rules_test)

    # The per-fighter combat target (issue #8): cycling, hold-for-ally, the 15-tick
    # switch pulse, the KO/invalid-index fallbacks and the Match wiring that makes
    # facing and melee follow the lock. Drives TargetLocks directly and Match through
    # its public API; both live in foundation_gameplay.
    add_executable(target_lock_test tests/target_lock_test.cpp)
    target_link_libraries(target_lock_test PRIVATE foundation_gameplay)
    add_test(NAME target_lock_test COMMAND target_lock_test)

    # Issue #11: KO -> Overkill -> respawn, team credits, capacity extremes,
    # simultaneous deaths/bursts and the timed-round winner, driven through Match so
    # Fighter::take_damage, the projectile pool and MatchFrame are all covered.
    add_executable(round_rules_test tests/round_rules_test.cpp)
    target_link_libraries(round_rules_test PRIVATE foundation_gameplay)
    add_test(NAME round_rules_test COMMAND round_rules_test)

    # Issue #14: the COM decision state — determinism, the recovered tactic table, the
    # resource/availability gates, retargeting, ally exclusion and the wall/corner
    # recovery, all against a synthetic "Rena 1" combo and the #7 collision sweeps.
    add_executable(bot_brain_test tests/bot_brain_test.cpp)
    target_link_libraries(bot_brain_test PRIVATE foundation_gameplay)
    add_test(NAME bot_brain_test COMMAND bot_brain_test)

    # The .X animation path against the shipped rigs: defines XMODEL_IMPLEMENTATION
    # itself (same reason as raycast_analytic), sweeps data/<name>/<NN>.X at run time,
    # and skips itself when the install is absent.
    add_executable(animation_pose_test tests/animation_pose_test.cpp)
    target_include_directories(animation_pose_test PRIVATE src)
    target_link_libraries(animation_pose_test PRIVATE glm)
    add_test(NAME animation_pose_test COMMAND animation_pose_test)

    # The DX9 pass's fixed-function light and clear constants: device-free, and pinned
    # because the numbers are load-bearing to the third decimal (a wrong triple lands
    # 1.5x..2.7x off and only a 480000-pixel comparison shows it). It includes
    # render/scene_renderer.h for them, so it needs that header's own include path
    # (webgpu.h from the imported target) although it never creates a device;
    # foundation_assets supplies src/assets for scene.h.
    add_executable(lighting_test tests/lighting_test.cpp)
    target_include_directories(lighting_test PRIVATE src)
    target_link_libraries(lighting_test PRIVATE foundation_assets webgpu glm)
    add_test(NAME lighting_test COMMAND lighting_test)

    # The CJK text layer: device-free (it rasterizes into host memory), and it links
    # the bitmap font in because half its contract is "bit-for-bit identical to
    # ui::measureText/ui::layoutText when no font is loaded". It SKIPs without the
    # fetched font, which is not committed (scripts/fetch_deps.sh pins its sha256).
    add_executable(text_test tests/text_test.cpp src/ui/text.cpp src/ui/font.cpp)
    target_include_directories(text_test PRIVATE src third_party/stb)
    target_link_libraries(text_test PRIVATE glm)
    add_test(NAME text_test COMMAND text_test)

    add_executable(caption_font_test tests/caption_font_test.cpp)
    target_link_libraries(caption_font_test PRIVATE foundation_ui)
    add_test(NAME caption_font_test COMMAND caption_font_test)
    set_tests_properties(caption_font_test PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

    # The battle HUD's sprite table and draw geometry: device-free arithmetic over the
    # transcribed .rdata anchors, so it needs the headers' include path and webgpu.h only.
    add_executable(hud_sprite_table tests/hud_sprite_table.cpp)
    target_include_directories(hud_sprite_table PRIVATE src)
    target_link_libraries(hud_sprite_table PRIVATE webgpu)
    add_test(NAME hud_sprite_table COMMAND hud_sprite_table)
    add_executable(canvas_layout_test tests/canvas_layout_test.cpp)
    target_include_directories(canvas_layout_test PRIVATE src)
    target_link_libraries(canvas_layout_test PRIVATE webgpu)
    add_test(NAME canvas_layout_test COMMAND canvas_layout_test)
    add_executable(hud_layout_test tests/hud_layout_test.cpp)
    target_include_directories(hud_layout_test PRIVATE src)
    target_link_libraries(hud_layout_test PRIVATE webgpu)
    add_test(NAME hud_layout_test COMMAND hud_layout_test)

    # Issue #12's split-screen plumbing: the recovered one/two/four-cell geometry, the
    # controller-keyed view assignment, per-view projection into each view's own aspect,
    # the synthetic pad pattern, and the guard that rendering N views does not multiply
    # simulation or audio updates (it steps a real Match and compares a 1-view with a
    # 4-view run). Device-free; links foundation_gameplay for Match/Fighter and the HUD fill.
    add_executable(view_layout_test tests/view_layout_test.cpp)
    target_include_directories(view_layout_test PRIVATE src)
    target_link_libraries(view_layout_test PRIVATE foundation_gameplay glm webgpu)
    add_test(NAME view_layout_test COMMAND view_layout_test)

    # The HUD's text metrics against the banked DX9 frames: device-free (it rasterizes
    # into host memory), it pins the reference's GDI advance table, the baseline offset
    # and the rasterizer's placement, and it SKIPs without the fetched Latin face
    # (scripts/fetch_deps.sh pins its sha256).
    add_executable(hud_text_test tests/hud_text_test.cpp src/ui/text.cpp src/ui/font.cpp)
    target_include_directories(hud_text_test PRIVATE src third_party/stb)
    add_test(NAME hud_text_test COMMAND hud_text_test)

    # The cube pass's geometry: device-free, like debug_prims_geometry. It defines both
    # geometry-only guards, so it compiles the two headers without any WebGPU header.
    add_executable(unlit_cube_geometry tests/unlit_cube_geometry.cpp)
    target_include_directories(unlit_cube_geometry PRIVATE src)
    target_link_libraries(unlit_cube_geometry PRIVATE glm)
    add_test(NAME unlit_cube_geometry COMMAND unlit_cube_geometry)

    # The front-end screen stack and the title menu's cursor machine: device-free (the
    # stack's factory is injected, so transitions run against fake screens). It links
    # foundation_ui for makeScreen -> screen_title -> hud_atlas -> sprite, but never
    # creates a device.
    add_executable(input_backend_test tests/input_backend_test.cpp)
    target_link_libraries(input_backend_test PRIVATE foundation_media foundation_gameplay)
    add_test(NAME input_backend_test COMMAND input_backend_test
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/scripts/frontend-smoke.txt")
    add_executable(frontend_battle_test tests/frontend_battle_test.cpp)
    target_link_libraries(frontend_battle_test PRIVATE foundation_gameplay)
    add_test(NAME frontend_battle_test COMMAND frontend_battle_test)
    add_executable(fixed_step_test tests/fixed_step_test.cpp)
    target_link_libraries(fixed_step_test PRIVATE foundation_gameplay)
    add_test(NAME fixed_step_test COMMAND fixed_step_test)
    # Issue #13's participant roster and the screen geometry it drives: the 1v1/2v1/2v2
    # derivations, the four recovered VS slots, the result report's rows and the victory
    # layer's transition. Device-free (header-only tables plus the timeline).
    # Issue #20's recovered result rules: the victory-quote plan (pair, persona, grade, the
    # single-script fallback), the win-script alternatives, and the earned-title chain over the
    # per-fighter record. Device-free; the shipped title names are checked when the install is
    # present, like the other asset-backed tests.
    # Issue #16's live combat audio policy: event identity, de-duplication, per-fighter
    # voice channels, suspend/resume and repeated-match cleanup. Device-free (a recording
    # sink stands in for the engine).
    add_executable(combat_audio_test tests/combat_audio_test.cpp)
    target_link_libraries(combat_audio_test PRIVATE foundation_media glm)
    add_test(NAME combat_audio_test COMMAND combat_audio_test)

    # Issue #16's asset-backed live match: four shipped combos, a COM 2v2 with a full gauge
    # and low HP, the real event derivation and the real (probed) voice files, twice.
    add_executable(combat_audio_match_test tests/combat_audio_match_test.cpp)
    target_link_libraries(combat_audio_match_test PRIVATE foundation_gameplay foundation_media glm)
    add_test(NAME combat_audio_match_test COMMAND combat_audio_match_test)

    add_executable(result_title_test tests/result_title_test.cpp)
    target_link_libraries(result_title_test PRIVATE foundation_gameplay foundation_ui foundation_assets glm)
    add_test(NAME result_title_test COMMAND result_title_test)

    add_executable(participant_layout_test tests/participant_layout_test.cpp)
    target_link_libraries(participant_layout_test PRIVATE foundation_ui glm)
    add_test(NAME participant_layout_test COMMAND participant_layout_test)

    foreach(frontend_test select_menu_test stage_vs_test frontend_config_test result_screen_test)
        add_executable(${frontend_test} tests/${frontend_test}.cpp)
        target_link_libraries(${frontend_test} PRIVATE foundation_ui glm)
        add_test(NAME ${frontend_test} COMMAND ${frontend_test})
    endforeach()
    # The two recovered damage chains, pinned against real combo data (Rena + item 001).
    add_executable(damage_scale_test tests/damage_scale_test.cpp)
    target_link_libraries(damage_scale_test PRIVATE foundation_gameplay)
    add_test(NAME damage_scale_test COMMAND damage_scale_test)
    # Issue #15's pause semantics: the match gate, the menu and the stale-edge rule.
    # Device-free (no SDL, no assets), like the other gameplay tests.
    add_executable(battle_pause_test tests/battle_pause_test.cpp)
    target_link_libraries(battle_pause_test PRIVATE foundation_gameplay)
    add_test(NAME battle_pause_test COMMAND battle_pause_test)

    # Issue #19's user configuration: the parser/validator, the atomic write and the
    # controller-placement policy. Device-free on purpose (the settings TU is std-only),
    # so it runs anywhere the host suite does.
    add_executable(user_settings_test tests/user_settings_test.cpp src/settings/user_settings.cpp)
    target_include_directories(user_settings_test PRIVATE src)
    add_test(NAME user_settings_test COMMAND user_settings_test)

    add_executable(screen_stack_test tests/screen_stack_test.cpp)
    target_include_directories(screen_stack_test PRIVATE src)
    target_link_libraries(screen_stack_test PRIVATE foundation_ui glm)
    add_test(NAME screen_stack_test COMMAND screen_stack_test)
endif()

if(EMSCRIPTEN)
    set_target_properties(foundation_demo PROPERTIES SUFFIX ".html")
    # argv never reaches wasm, so a local verification build can name its one asset here.
    # The plain web build leaves this empty and keeps the triangle demo.
    if(FOUNDATION_WEB_ASSET)
        target_compile_definitions(foundation_demo PRIVATE "FOUNDATION_WEB_ASSET=\"${FOUNDATION_WEB_ASSET}\"")
    endif()
else()
    target_copy_webgpu_binaries(foundation_demo)
endif()
