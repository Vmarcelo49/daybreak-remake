# daybreak — Higurashi Daybreak port

The product is [`foundation/`](foundation/README.md): C++17, **SDL3 + WebGPU**
(`webgpu.h`, wgpu-native on native targets and emdawnwebgpu on the web),
built for **Linux, Windows and the web**. It reads the original `.X` models,
`.cnv` textures and `.dat` bundles directly; no asset conversion is required.

The playable front end connects title → team/character/weapon/hypermode/controller
selection → stage/battle settings → VS/countdown → live **1v1 or 2v2** battle →
victory/quote/report → selection. COM fighters and local split-screen are
supported; LAN netplay and story mode remain unimplemented.
See the [remaining roadmap](foundation/docs/ROADMAP-PENDING.md) for current gaps.

Battle rendering and HUD placement adapt automatically to the viewport,
including ultrawide displays. Menus retain a centered 4:3 canvas with black
bars. Options provide native resolution selection, fullscreen and volume
controls; settings and bindings persist in the native user's config file (when
available), while browser settings remain process-local. See
[the settings policy](foundation/docs/USER-SETTINGS.md). Runtime captions use
[Gyrotrope Black with a Japanese fallback](foundation/assets/fonts/README.md);
existing image captions retain their original art.

## Build and run

From the repository root:

```bash
./remake/foundation/build.sh deps     # one-time dependency setup
./remake/foundation/build.sh linux    # also windows, web, all
./remake/foundation/build/linux/foundation_demo --install=Higurashi-Daybreak --screen=title
```

Use your own local game install for the original assets. Detailed build,
capture and verification instructions live in the
[foundation README](foundation/README.md).

## Project map

| Path | Purpose |
|---|---|
| [`foundation/`](foundation/README.md) | Product source, tests, builds and current implementation docs |
| [`docs/decisions.md`](docs/decisions.md) | Binding scope and technology decisions |
| [`docs/game-spec.md`](docs/game-spec.md) | Original game's mechanics and flow |
| [`docs/reference/`](docs/reference/README.md) | Ground-truth captures of the original |
| [`tests/parity-baseline/`](tests/parity-baseline/README.md) | Frozen DX9 reference captures and logs |
| [`tools/asset-tools/`](tools/asset-tools/README.md) | Offline archive and CNV utilities |
| [`tools/hook-tracer/`](tools/hook-tracer/README.md) | File-access tracing of the original executable |
| [`assets/shaders/`](assets/shaders/README.md) | Original D3DX effect bytecode, retained as evidence |

## Historical implementations

`mvp/` was retired on 2026-10-01. The DX9 + SDL2 remake was removed in the
Phase 5 cutover on 2026-10-02; `remake/src/`, `remake/build.sh` and its executable
are no longer the product. The A/B reference is the frozen parity bank plus
the original's captures, rather than a buildable DX9 binary.

The cutover's deletion list, retained evidence and rollback tag
`pre-webgpu-cutover` (`37ed31d`) are documented in
[`FULL-REPLACEMENT-PLAN.md` §8](foundation/docs/FULL-REPLACEMENT-PLAN.md).
[`docs/placeholders.md`](docs/placeholders.md),
[`docs/roadmap.md`](docs/roadmap.md) and
[`docs/port-from-mvp-plan.md`](docs/port-from-mvp-plan.md) preserve the former
implementations' records; their build paths and pending-work notes are historical.
