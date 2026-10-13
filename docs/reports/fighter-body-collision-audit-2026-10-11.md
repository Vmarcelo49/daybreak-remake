# Fighter body-collision source audit — 2026-10-11

## Finding

The inspected source establishes collision with stage geometry during fighter movement and hit detection for active attacks. It does not establish passive fighter-to-fighter body separation. No passive collider radius/height, grounded or airborne predicate, team/liveness gate, push split, or pair-processing order was recovered in this bounded trace. No passive separation was added to the remake; any later push-apart behavior needs additional original evidence or an explicit port-policy label.

This is a bounded negative finding, not proof that every path in the original executable lacks passive separation. The local original `Higurashi-Daybreak/DaybreakDX.exe` matches MD5 `a136ddc01bd7ef355b759b88ac89e02c`; the readable C files cited below are the repository's mass decompilation from a patched executable. The function addresses and Rena+0 vtable were also checked against the local original image.

## Traced paths

The normal battle update in `FUN_00634f60` (`research/decompiled/FUN_00634f60.c`, address `0x00634f60`, lines 98–127) dispatches the fighter input/move callbacks, calls `FUN_0042e110`, then enters `FUN_006358c0`. Its four-slot path (`research/decompiled/FUN_006358c0.c`, address `0x006358c0`, lines 22–36) calls `FUN_004202b0` once per slot before updating each fighter's transformed pose.

`FUN_004202b0` (`research/decompiled/FUN_004202b0.c`, address `0x004202b0`, lines 13–27) calculates one fighter's displacement from its own speed and movement/facing angles. It submits that displacement to `FUN_0042cb50`; then it applies the vertical query and refreshes the bearing to the selected target. The horizontal helper `FUN_0042cb50` (`research/decompiled/FUN_0042cb50.c`, address `0x0042cb50`, lines 17–47) moves the same actor after calling `FUN_0042d3b0`. That recursive helper (`research/decompiled/FUN_0042d3b0.c`, address `0x0042d3b0`, lines 75–85 and 178–182) walks the supplied mesh/frame tree and runs `D3DXIntersect` on its meshes. The vertical path is `FUN_0042c970` → `FUN_0042cd50`, also a stage-mesh ray query. These helpers operate on the actor's requested movement against a mesh; they do not accept or enumerate the fighter roster.

Rena+0's active move and input callbacks are grounded by the character vtable, not the base table. `FUN_0064c840` constructs the base player object with `FUN_0041d870` and installs vtable `0x006a4e10` (`research/decompiled/FUN_0064c840.c`, address `0x0064c840`). The original vtable entries at that address are `+0x18 FUN_0043ffc0` (move executor), `+0x1c FUN_00445ee0` (input selector), and `+0x24 FUN_00447710`; the latter forwards to `FUN_00428250`, which updates status/HUD cues. The base vtable `0x006a240c` installed by `FUN_0041d870` is replaced here, so its callbacks are not the active Rena+0 path.

The Rena+0 move executor `FUN_0043ffc0` uses target distance and move state to select attacks, shots, turns and transitions. The horizontal distance helper `FUN_0042d980` is the squared XZ distance to the current target. `FUN_00421c80` compares squared distances to roster fighters to choose an aim target. `FUN_0041f580` maintains the fighter's per-player target and facing state (`research/decompiled/FUN_0041f580.c`, address `0x0041f580`, lines 182–239); these are selection/heading paths, not position separation.

The attack-contact path is separate. `FUN_00637680` (`research/decompiled/FUN_00637680.c`, address `0x00637680`) iterates active hit objects and fighters, then calls `FUN_00637950` to resolve attack-volume contacts. The literal `0x41f00000` passed at `FUN_00637950` lines 90–130 is 30.0 and belongs to the melee victim-body sphere/capsule test. It is not evidence for a passive movement collider. The port's 20-unit stage movement stencil documented in `remake/foundation/docs/ROADMAP-PENDING.md` §“Stage collision implementation update” is also a port-side movement rule, not an original fighter-to-fighter radius.

## Remaining evidence gap

The traced scheduler, Rena+0 callbacks, movement/pose path, stage-ray helpers, target-distance routines, and active attack resolver expose no passive actor-contact response. They do not establish whether the original permits overlap in every state or whether an additional original-only path handles it. A source-backed implementation therefore cannot currently choose a radius, height, state gate, team rule, or response order without inventing behavior.
