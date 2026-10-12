# Checks inventory and audit — 2026-10-10

## Disposition (addressed 2026-10-10)

Every finding below was re-checked against the current code before it was changed, and the
original evidence is preserved unedited beneath this section. Status key: **fixed** (code
changed and verified), **partly** (some of the finding is addressed; the remainder is named),
**deferred** (out of this change's scope, with the reason).

| # | Finding | Status | What changed |
|---|---|---|---|
| A | Fail execution regressions instead of skipping them | **fixed** | New `tests/capture_probe.py` is the shared harness for all six rendered-frame suites. It skips ONLY for a missing prerequisite (`<install>/data`, or the demo's own `RESULT: no usable GPU adapter`); a nonzero exit, a missing `RESULT: ok`, a hung run (bounded timeout), a capture that is not a valid PPM, a truncated payload and a missing expected marker all raise `CaptureFailed` and preserve the transcript tail. `hud_cell_scale`'s empty-cyan-marker case now fails. Verified: the audit's `/bin/false` reproduction returns 1 with the transcript, the adapter case returns 77, and an empty marker set returns 1. |
| B | Stop counting skipped work as passed | **fixed** | `dat_bundle_bytes`, `text_test`, `hud_text_test` and `combat_audio_match_test` return **77** on an unavailable prerequisite and all four now set CTest's `SKIP_RETURN_CODE`. A font that exists but cannot be read, and an item/move file that is missing or unparseable **inside an available install**, are now failures rather than skips. `ginkiha_recon_test.py` exits 77 only when every case was skipped. New `tests/release_check.py` is the release mode that requires the asset/GPU suites to execute: it runs every `asset`-labelled suite and fails on any skip, failure or empty label match. Measured: 21/21 executed, 0 skipped. |
| C | Replace the asset sweep's failure count with named exceptions | **fixed** | `showcase.py`'s `--allow-problems=43` is gone. `EXPECTED_GAPS` names each documented cell and the exact untextured count it may report (stage05/stage15 at 4, kasai at 2 or 6); anything else fails regardless of the total, and a crashed cell is never a gap. Discovery is asserted non-empty and pinned to the claimed 16 characters x 13 stages, and the reproduced gap total must equal the documented 43 or the table needs re-deriving. The coverage claim now states the weapon slot, and every command passes it explicitly. Measured: 165 pass, 43 documented gaps, **0 unexpected**. |
| D | Reject incomplete trace comparisons | **fixed** | `compare_match_traces.py` requires equal sample counts by default and fails with both lengths named. `--prefix` is the explicit diagnostic: it compares the common prefix and **returns 1 either way**, so a truncated run can never be reported as a match. Verified against the audit's 2-vs-1 reproduction (exit 1) and the prefix mode (exit 1, "not a match"). *Not done:* recording character+weapon identity in trace metadata needs the demo to print it; deferred as a product change. |
| E | Make the full release flow executable and state-aware | **partly** | Issue #63's cause was confirmed and fixed: the stage page's time-limit row cycles `wrap(v + dx*60, 300)` from the original's default 0, so the recipes' two LEFT presses selected 180 s instead of 60 s. All five recipes now press LEFT four times and every later event moved by the same +24 frames, so the battle offsets are unchanged. Measured on `frontend-1v1-rematch`: the settings line reads the intended `time 60s, health 50%, gauge 100%, balloon 40%/40%`, all three rounds end `(time up) at frame 3600` (the pre-fix value), and the ladder is the pre-fix ladder **+24** on every entry after the stage page. New `tests/release_flow_check.py` automates the evidence the checklist parsed by hand: required scene order, roster, resolved rounds and the capture file, with a bounded timeout, keeping the transcript on failure. New `WAIT <scene>` script directive holds a script until a named scene is current, with tests in `input_backend_test`; the recorded recipes keep their fixed taps because re-writing them would invalidate banked ladders. **No capture digest was re-banked** — §3 says so explicitly. |
| F | Cross-target execution and earlier feedback | **deferred** | Out of scope by the task statement ("leave broader Windows/browser execution automation ... for a separate change"). |
| G | Bring standalone reconstruction tests into automation | **fixed** | `ginkiha_recon_test.py` is registered in CTest with `SKIP_RETURN_CODE 77`; its synthetic cases always run and its bundle cases skip when the local reference is absent. Measured: 6 ran, 0 skipped, exit 0. |
| H | Fix unequipped Match fixtures | **fixed** | New `tests/synthetic_combo.h` supplies a synthetic character+weapon pair (move table + item) for data-free suites; `bot_brain_test`'s duplicate builders were folded into it. `frontend_battle_test` and the other five suites that construct and step a `gameplay::Match` (`battle_pause_test`, `debug_keys_test`, `fixed_step_test`, `round_rules_test`, `stage_movement_test`, `view_layout_test`) now bind it, so no fixture claims a battle without a combo (AGENTS rule 7). Fixture lifetimes were checked against `MatchConfig`'s pointer semantics. |
| I | Preserve measurement tools, distinguish them from gates | **partly** | `compare_frames.py` is left as the measurement tool it is; adding acceptance thresholds is the separately-scoped image-threshold calibration the task defers. |
| J | Remove demonstrably pointless work | **fixed** | `jinja2` is removed from the index workflow's install step (confirmed unused: `generate_index.py` imports only the standard library). `coverage_report.py`'s membership loop with a `pass` body is deleted; the report still runs and produces the same hot-spot ranking. |

New regression coverage for the checkers themselves: `tests/check_tools_test.py`
(31 cases, data-free) pins execution failure, missing `RESULT: ok`, the contradiction of
`RESULT: ok` with a nonzero exit, timeouts, absent/malformed/truncated captures, empty
markers, the prerequisite/failure split, unequal trace lengths, prefix mode never claiming
a match, the sweep's per-cell exceptions and its empty/shrunken discovery, the release
gate's JUnit skip detection, and the recon suite's 77-on-all-skipped contract.

Registration after this change: **66 CTest suites** (65 + `ginkiha_recon_test`), plus
`check_tools_test` (67). `release_check.py` and `release_flow_check.py` are release gates
run explicitly, not CTest entries: the first needs a configured build directory, the
second needs game data and takes minutes per recipe.

---


## Scope and evidence

This inventories the project's test suites, CI jobs, verification tools, release
recipes and contribution checks. It does not enumerate every defensive condition
inside the game or every assertion within a suite.

The configured Linux build registers **65 CTest suites**, matching the current
native CMake registrations. The working tree already contains unrelated changes,
including an untracked Windows startup smoke test; these are identified separately.
The local binaries were tested without rebuilding, so their results do not certify
the current modified source. No implementation or existing test was changed by this audit.

Sources: [CMake registrations](../../remake/foundation/CMakeLists.txt),
[build workflow](../../.github/workflows/build-foundation.yml),
[index workflow](../../.github/workflows/build-index.yml),
[release checklist](../../remake/foundation/docs/RELEASE-CHECKLIST.md), and
[contribution rules](../../AGENTS.md).

## 1. All 65 registered suites

Names below are CTest names. C++ sources are under `remake/foundation/tests/`;
the six capture suites and delivery service suite use Python there.

| # | Suite | What it checks |
|---|---|---|
| 1 | `hud_cell_scale` | Rendered HUD probe placement and scaling across split-screen cells. |
| 2 | `hud_view_geometry` | Actual per-view reticle geometry; catches reuse of another view's vertices. |
| 3 | `pause_overlay_panel` | Rendered pause panel, text scale, split-screen composition and frozen clocks. |
| 4 | `toon_ramp` | Default/off identity, on-state toon effect, stage exclusion and split-screen. |
| 5 | `character_shadow` | Default/off identity, deterministic localized darkening, split-screen and no-caster control. |
| 6 | `npr_experiments` | Opt-in shading technique properties, off-state identity and inert-effect detection. |
| 7 | `web_delivery_test` | Synthetic bundles, catalog preparation/verification and local HTTP delivery. |
| 8 | `debug_prims_geometry` | Debug lines, boxes, crosses, colors and batch reuse. |
| 9 | `raycast_analytic` | Known ray/triangle answers and optional real collision meshes. |
| 10 | `dat_bundle_bytes` | Archive reader bytes, indices, names and duplicate precedence against an independent Python oracle. |
| 11 | `web_catalog_order` | Web catalog duplicate resolution versus the native bundle order. |
| 12 | `web_assets_test` | Host-side hashing and asset client catalog/path contracts. |
| 13 | `match_economy_test` | Balloon, LIMIT, KO and round economy arithmetic. |
| 14 | `fighter_script_test` | Scripted fighter/projectile behavior and many combo-specific move regressions. |
| 15 | `animation_data_test` | Animation/move parsing and execution, synthetic cases and shipped combo data. |
| 16 | `ginkiha_tables_test` | Generated recovered tables, dispatch bindings and cross-table consistency. |
| 17 | `fx_cards_test` | Effect card lifecycle, capacity and expiration. |
| 18 | `effect_catalog_test` | Effect descriptor mapping, variants, lifetimes and recovered shot visuals. |
| 19 | `env_spawn_test` | Stage environment parsing and spawn coordinates/order. |
| 20 | `shadow_map_test` | Recovered shadow/light camera constants and projection arithmetic. |
| 21 | `arena_camera_test` | Arena camera following and collision behavior. |
| 22 | `stage_movement_test` | Stage collision, sliding and movement regressions. |
| 23 | `weapon_definition_test` | Weapon parsing/rejection plus the 46 legal character+weapon bindings and real-data sweep. |
| 24 | `melee_rules_test` | Melee selection, direction, aerial and hit-rule behavior. |
| 25 | `target_lock_test` | Independent locks, switching, validity and enemy selection. |
| 26 | `lock_switch_camera_test` | Lock switching through the actual application tick/camera path. |
| 27 | `live_camera_smoothness_test` | Actual tick-to-render interpolation at multiple render rates and view counts. |
| 28 | `debug_keys_test` | Recovered debug key map, gates and battle effects. |
| 29 | `round_rules_test` | KO, Overkill, respawn and team victory through Match. |
| 30 | `bot_brain_test` | COM decision weights, deterministic seeds and unavailable-action handling. |
| 31 | `animation_pose_test` | Animation evaluation and shipped rig poses. |
| 32 | `npr_normals_test` | Lighting normal clustering/blending and generated shadow masks. |
| 33 | `lighting_test` | Renderer lighting/clear constants and lighting arithmetic. |
| 34 | `controller_scene_lifetime_test` | Animation controller/model ownership across actual scene replacement. |
| 35 | `text_test` | CJK text loading, layout/rasterization and bitmap fallback compatibility. |
| 36 | `caption_font_test` | Shared caption font loading and Latin/Japanese glyph coverage. |
| 37 | `launcher_test` | Packaged launcher's install search order, migration and failure messages. |
| 38 | `hud_sprite_table` | Recovered HUD sprite anchors and geometry. |
| 39 | `canvas_layout_test` | Centered/clipped menu canvas and aspect behavior. |
| 40 | `hud_layout_test` | Battle HUD anchors and layout arithmetic. |
| 41 | `pause_overlay_layout_test` | Pause menu sizing, text margins and containment across resolutions. |
| 42 | `view_layout_test` | View cells, controller assignment, projection and single-step behavior with multiple views. |
| 43 | `hud_text_test` | Reference text advances, baseline and glyph placement. |
| 44 | `unlit_cube_geometry` | Solid cube geometry, colors, capacity and submission order. |
| 45 | `input_backend_test` | Input backend/script handling. |
| 46 | `device_isolation_test` | Actual SDL key/gamepad events, virtual pad and capture/focus isolation. |
| 47 | `frontend_battle_test` | Match settings, stats, bot determinism, team counts and round outcome. |
| 48 | `fixed_step_test` | Fixed simulation cadence, catch-up and input transition consumption. |
| 49 | `combat_audio_test` | Event identity, deduplication, voice channels and cleanup using a recording sink. |
| 50 | `combat_audio_match_test` | Asset-backed COM 2v2 event/audio derivation and repeated-match cleanup. |
| 51 | `bgm_loop_test` | Missing/invalid/valid optional loop sheet behavior. |
| 52 | `result_title_test` | Recovered victory quote and earned-title rules; optional installed title names. |
| 53 | `participant_layout_test` | Participant derivation and VS/result geometry for different team counts. |
| 54 | `select_menu_test` | Character/weapon selection, readiness, launch binding and synthetic pad navigation. |
| 55 | `stage_vs_test` | Stage/settings navigation and VS sequence rules. |
| 56 | `frontend_config_test` | Options, input binding capture and soft keyboard behavior. |
| 57 | `result_screen_test` | Victory→quote→report progression and winner portrait count. |
| 58 | `select_cursor_test` | Recovered cursor rates, bounds and attraction behavior. |
| 59 | `select_row_slidein_test` | Recovered selection entry/row transition timing and geometry. |
| 60 | `frontend_lifecycle_test` | What selection entry/rematch clears and preserves. |
| 61 | `countdown_overlay_test` | Round-start boundary and overlay composition without a GPU. |
| 62 | `damage_scale_test` | Recovered damage calculation chains using combo data. |
| 63 | `battle_pause_test` | Frozen match, input edge cleanup and pause menu choices. |
| 64 | `user_settings_test` | Settings parsing, validation, atomic persistence and path policies. |
| 65 | `screen_stack_test` | Screen transitions, title menu and opening/movie host seam. |

## 2. Checks outside those 65 suites

| Check/tool | Purpose and execution |
|---|---|
| Linux CI build + CTest | Every qualifying push to main; Release compile/link and native suites. Game-data-dependent coverage is unavailable on the runner. |
| Windows cross-build | VERSION-changing pushes or manual dispatch; compile/link and existence of the EXE. No execution in this job. |
| Web build | Same cadence as Windows; compile/link and existence of HTML/WASM. No browser execution in this job. |
| Matrix gate | Examines the push's before/after range for VERSION changes; runs the matrix if the range is unavailable. |
| SDL table compile-time pins | `src/input/pin_tables.cpp`: static assertions against real SDL input/audio enum values, built across targets. |
| Dependency/configuration preconditions | Required tools/dependencies, pinned fetched versions and CMake configuration checks. Version pins are not tests of existing dependency contents. |
| Linux package script | Required files and executable bits, exclusion of game assets, library resolution inside package/base system, deterministic archive construction and SHA-256 output. |
| Windows package script | Present in the modified working tree: staged files, DLL import dependency checks, excluded game assets/scripts and ZIP hash. |
| `windows_startup_smoke` | Present in the modified working tree; Windows-only target, excluded from the default build and absent from CTest. Exercises two startup/settings cycles. |
| Web client packaging | `webdelivery/scripts/package-client.sh`: stages the deployable browser client. Separate from live browser verification. |
| `ginkiha_recon_test.py` | Six unittest methods: trace parsing/summaries, source body boundaries, runtime syntax rejection, roster/origins, binding mismatch and source hash drift. Not registered in CTest/CI. |
| Ginkiha import/recon validation | Tools reject reference EXE identity mismatches; reconstruction also validates source bundle hashes and runtime handler bindings. |
| `showcase.py --check` | Base-character × stage loading/texture matrix; defaults to weapon slot 0, with optional count-based failure allowance. |
| `showcase.py --shots` | Curated rendered match/FX captures with load/texture checks. |
| `compare_match_traces.py` | Fighter positions and animation states against banked traces; camera deltas informational. |
| `compare_frames.py` | Frame RMSE, coverage, luminance and side-by-side output. A measurement tool: returns success regardless of visual mismatch. |
| `hud_bands.py` | HUD/scene band comparison against original reference images. |
| `title_bands.py` | Title region comparisons and cursor-related masks. |
| `measure_framing.py` | Character framing measurements from image masks. |
| `pin_viewpoint.py` | Reproduces spawn/camera configurations and asserts scene-floor comparison values/winner. |
| `npr_evidence.py` | Shading parameter sweeps, region metrics and visual evidence sheets. Separate from registered NPR property tests. |
| Frozen parity bank | Captures, logs and hash manifest under `remake/tests/parity-baseline/`; reference evidence rather than an automatically executed suite. `regen.sh` requires the retired DX9 executable. |
| Research ingest | Hashes source bodies, updates inventory and detects stale reviewed identities. |
| Research recomposition | Generates readable output from dump/symbol truth; not a gameplay test. |
| Research coverage report | Counts statuses/decompilation and ranks callgraph hotspots; required before research commits, but does not validate behavior. |
| Index workflow | Generates INDEX files, commits changes and uploads artifacts; inventory maintenance rather than behavioral validation. |
| Contribution review | Before every commit: read unstaged and staged diffs; remove dead code, temporary debugging, duplicated logic and useless comments. Research commits additionally require coverage reporting. |

## 3. Release/manual checks

The release checklist records these separately from CTest:

1. Build and package the Linux release; verify launcher behavior and package contents.
2. Complete title→selection→stage→VS/countdown→battle→results→selection for
   1v1 with two human slots, one human versus COM and four-fighter 2v2.
3. Three-round rematches for each scenario; additional four-player loop capture.
4. Prolonged four-player run: five complete rounds, expected transition/round
   lines, FX population/drop counters, crash absence and sampled memory/thread stability.
5. Sweep all 46 character+weapon bindings and base-character × stage texture loading.
6. Compare captured frames/digests, fighter traces and selected original-image bands.
7. Play a live battle to assess camera/input presentation; captures do not exercise
   live interpolation in the same way.
8. Wayland and X11 window runs, present mode, frame pacing, low/high refresh,
   fullscreen and resolution changes.
9. Windows/Wine and browser title/battle execution with game data; report the
   actual adapter and delivery path. These are local recorded runs, not CI jobs.
10. Audio/input smoke paths (`--audio-test`, `--input-test`) and movie execution
    evidence; dummy audio and synthetic input do not establish real-device behavior.

Known limits must remain explicit: the checklist says the four fixed-tick frontend
recipes no longer reproduce after the time-limit default correction (issue #63).
Its Windows/web records also describe rematch/navigation/delivery defects. Those
are recorded evidence, not fresh results of this audit. Hardware browser adapters,
browser visual parity, macOS and some real-device checks remain unverified.

## 4. Recommendations, in priority order

### A. Fail execution regressions instead of skipping them — high priority

`hud_cell_scale.py` maps any nonzero exit or missing `RESULT: ok` to `None`;
the caller returns 77. Substituting `/bin/false` with a synthetic data directory
reproduced **exit 77**, not failure. Similar broad handling appears in other
capture helpers. A game crash or loader regression can therefore become a green
CTest run with a skipped suite. `hud_cell_scale` also skips when all cyan probe
markers are absent, although disappearing markers are something it should detect.

Check install/adapter prerequisites explicitly. Once available, crashes, bad
output and missing expected markers should fail and preserve the transcript.

### B. Stop counting skipped work as passed — high priority

`dat_bundle_bytes`, `text_test`, `hud_text_test` and `combat_audio_match_test`
return 0 on some unavailable-input paths. Several other suites mix always-run
cases with internally skipped asset cases, so a suite-level pass does not mean
every case ran. In `combat_audio_match_test`, an item/move parse failure can also
be treated as a skip even when the install exists.

Use exit 77 plus `SKIP_RETURN_CODE` for fully skipped suites. Split hermetic and
asset-backed cases where useful, and expose executed/skipped case counts. Missing
optional prerequisites may skip; corrupt expected data should fail. Add an
explicit release mode that requires the data/GPU suites to execute.

### C. Replace the asset sweep's failure count with named exceptions — high priority

`showcase.py --allow-problems=43` accepts any set of at most 43 bad cells,
including crashes. A stubbed one-cell sweep with an unexpected crash returned
True under that allowance. One fixed known gap can conceal one new regression.

Record allowed combo/stage cells and failure reasons; reject every unexpected
failure regardless of total. Assert nonempty discovery and expected roster/stage
coverage. Enumerate explicit weapon slots and costumes when claiming all legal
selection coverage: the current base-directory sweep defaults to slot 0, and
sharing move tables does not prove different costume meshes/textures load.

### D. Reject incomplete trace comparisons — high priority

`compare_match_traces.py` compares `min(len(a), len(b))` and merely prints a
note for unequal counts. Two reference samples versus one matching sample
reproduced **exit 0**. Require equal expected sample counts and identify samples
by logic tick where possible. Preserve any intentional prefix comparison as an
explicit diagnostic option. Also record character+weapon identity in trace metadata.

### E. Make the full release flow executable and state-aware — high priority

The documented frontend recipes currently carry an explicit non-reproduction
warning. `RESULT: ok` alone previously passed even when results never appeared;
the checklist correctly requires transition evidence, but parsing it is manual.

Repair the scripts and automate expected scene/round/roster/output checks.
State-aware input should wait for selection/VS/results rather than assuming
fixed offsets; keep timeouts to catch stuck states. Run the required long-run
ladder as part of the release gate and retain transcripts/captures on failure.

### F. Add cross-target execution and earlier feedback — medium/high priority

The Windows EXE and web HTML/WASM existence checks add little beyond a successful
link and do not test launch behavior. Retain artifact checks if useful for
packaging, but prioritize isolated startup, title, battle and rematch smoke runs.
The existing Windows smoke target is opt-in and CI does not invoke it.

Foundation CI has no pull-request trigger and usually postpones cross-target
builds until VERSION changes. Consider Linux checks on PRs and cross-target
checks on relevant platform changes or a scheduled/manual release gate. Add a
browser delivery/navigation smoke test; host client/server tests cannot verify
Emscripten filesystem materialization, browser caching or canvas execution.

### G. Bring standalone reconstruction tests into automation — medium priority

`ginkiha_recon_test.py` ran six tests successfully in this audit but is absent
from CTest and both workflows. Register its synthetic tests; keep unavailable
local-bundle checks visibly skipped. They cover tools that feed gameplay tables.

### H. Fix unequipped Match fixtures — medium priority

`frontend_battle_test` resets Match with default configuration, null models and
null move-table arguments, then exercises damage, bot behavior and stepping.
It never binds a character+weapon fixture. That conflicts with AGENTS rule 7.
Give such match tests explicit synthetic combos; pure economy arithmetic can
continue to test MatchEconomy without pretending to run an equipped battle.
Audit other Match fixtures before claiming they meet this policy.

### I. Preserve measurement tools, but distinguish them from gates — medium priority

`compare_frames.py` deliberately returns 0 for visual mismatches and resizes
mismatched input dimensions. It is useful for investigation. For automated
acceptance, add explicit thresholds and strict dimension checks, with any
resampling opt-in. Store reference identity, render size, backend and case
metadata with results; choose tolerances appropriate to that comparison.

### J. Remove demonstrably pointless work — low priority

The index workflow installs `jinja2`, but `generate_index.py` uses only the
standard library and no template import. Remove that dependency installation.

`coverage_report.py` has a loop converting addresses and testing membership
whose body is only `pass`; its result is unused. Remove it. The useful metric
generation should stay, and research would benefit from schema/lifecycle tests
for invalid statuses, stale hashes and unresolved dependencies. Neither workflow
currently enforces those research invariants.

The package/archive hashes are useful integrity identifiers; merely printing a
hash does not automatically test reproducibility. Add a two-build comparison
only if reproducibility is a release promise being gated.

## 5. What should stay

No complete registered suite is proven useless by this audit. Apparent overlap
often covers different failure layers:

- `hud_layout_test`/`view_layout_test` validate arithmetic; `hud_cell_scale`
  and `hud_view_geometry` catch GPU uniform/vertex reuse defects.
- `pause_overlay_layout_test` and `pause_overlay_panel` similarly cover layout
  rules versus actual rendering and frozen clocks.
- `shadow_map_test` pins recovered values; `character_shadow` proves the values
  produce a rendered effect.
- `match_economy_test` checks arithmetic; `round_rules_test` checks integration
  through damage, respawn and team credit.
- `combat_audio_test` checks policy in isolation; `combat_audio_match_test`
  checks actual match-derived events and asset bindings.
- `fixed_step_test` checks timing machinery; `live_camera_smoothness_test`
  catches presentation defects invisible to deterministic captures.
- Cube/debug geometry is still used by the current renderer, including debug
  volumes; stale comments about retired shot visuals do not make the suite dead.

Consolidate repeated PPM parsers/capture helpers when repairing skip semantics,
but retain the distinct assertions. Opt-in NPR sweeps could be labeled as a
separate expensive test group; they still protect supported experimental behavior.

## 6. Audit execution

- Confirmed 65 suites with `ctest -N`.
- Ran `ginkiha_recon_test.py`: six tests, all passed.
- Reproduced truncated-trace success, execution-failure skip and count-based
  acceptance of an unexpected asset-sweep crash using temporary synthetic inputs.
- Native CTest run: 65/65 reported Passed, no suite-level failures or skips;
  176.02 seconds. This is the existing build, without a source rebuild, and
  suite-level success does not establish that internally optional cases ran.
- Cross-checked the inventory against CTest's JSON list: all 65 names present,
  with no extra or missing names.
- Did not run release match ladders, rebuild modified source, package releases,
  execute Windows/browser targets or change the existing tests.
