# Vendored reference simulation

The battle simulation from **Ginkiha's `DaybreakRebuild`**, snapshot 2026-10-10, used with
the author's permission (`AGENTS.md`, "Licence"). It reconstructs behaviour of Higurashi
Daybreak's `DaybreakDX.exe`; `FUN_...` names and raw offsets are recovery references, not
calls into the original.

- **What is here:** the include closure of the simulation entry points plus the seven
  compiled combat-body modules. No Windows, Direct3D or DirectSound code, and no game assets.
- **Layout:** files keep their bundle names. `MANIFEST.sha256` records the hash of every file
  as copied, so `sha256sum -c MANIFEST.sha256` (run here) shows exactly what has diverged.
- **Rules:** nothing outside `src/sim/` includes these files. Do not reformat them; generated
  bodies stay byte-identical. Every local change goes in [`PATCHES.md`](PATCHES.md) with its
  evidence.
- **Standard headers:** the bundle relies on transitive includes that libstdc++ does not
  provide, so `../core_prelude.h` is force-included instead of patching each file.
- **zlib:** `zlib/` holds the inflate subset of zlib 1.3.2, unmodified, with its licence.
  It is outside the manifest, which covers the simulation files.

Running here shows only that the code runs. Its author calls full compatibility with the
original unproven, and so do we: see [`docs/DIRECTION.md`](../../../../../docs/DIRECTION.md) §2.
