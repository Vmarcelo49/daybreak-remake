# EFFECTS-TRAILS — item-backed weapon ribbons

> **Status:** the shared ribbon renderer is source-aligned, with asset-backed miss
> witnesses for Rena+0/item001 and Akane+0/item016. Other handler windows and exact
> blend parity remain open. This corrects the earlier conclusion that the executable
> had no trail geometry.

## Original path

- `FUN_00433eb0` constructs a prop only when its item row has a nonempty model name.
  It passes that prop's item texture and the two ribbon anchors into `FUN_0042fe90`.
  A texture-only item row is not an available prop.
- `FUN_0042fff0` samples the transformed tip. When it changes, the object shifts its
  12-point history and grows an active ribbon by five triangles, up to 40. An inactive
  ribbon decays by two triangles on every update.
- `FUN_00430120` transforms the item's root and tip through the current prop matrix,
  then expands the history into spline samples. `FUN_004303b0` draws those samples as
  a triangle fan using the prop's item-texture handle. Its constructor `FUN_0042fce0`
  initializes the non-root vertices at U=1; the draw assigns V from the sample index.
- The separate `data/trail/%02d.bmp` table is loaded by `FUN_00633ca0`, but its
  connection to this item-backed draw path is not established. The Rena+0 ribbon
  texture comes from its item row (`kiseki02.cnv`), not a guessed table index.

For Rena 0, `FUN_0043ffc0` reasserts prop-active windows every update. Move 300's
ribbon is active in phase 2, ticks 3–10; moves 301 and 302 use ticks 10–16 and 12–17.
`move_behavior.h` carries those windows. The prop's active latch is separate from hit
resolution, so the ribbon appears on a whiff.

Akane 0 (`FUN_00595460`, item016) binds manager prop slot 0 to item model 2 for
its normal, dash, and aerial moves. Source windows are move 300 phase 2 ticks 3–10,
301 ticks 10–16, 302 ticks 10–13, move 330 phase 2 ticks 10–15, 331 phase 2 ticks
7–16, move 340 ticks 16–24, and 341 ticks 17–19. The trail descriptor keeps the
manager slot (Prop1 bone) separate from item model 2 (anchors and texture). Current
real-input dispatch reaches 300, 330 and 340; Akane's neutral 301/302 chain is not
reachable because the port gates chain admission on its unrelated `MoveProgram`
registry (tracked in #66). Rows 301/302/331/341 are recorded as source-backed
descriptors, not claimed as live paths.

## Port and verification

`WeaponTrail` keeps world-space samples from the bound item model's anchors, transformed
through the manager slot's `Bip01_Prop1/2` bone. The renderer gives the dynamic mesh an
identity model matrix because the fighter and posed bone transforms are already included
in each point. It creates a trail carrier only when some item slot has a model name,
matching the source availability gate, and chooses the active item model's texture.
U stays at the outer edge and V advances along the trail, matching the original vertex
setup.

`animation_data_test` exercises the shipped Rena+0/item001 combo with a distant dummy.
The move 300 ribbon first grows at match frame 87 (phase 2, post-step elapsed 4, which
corresponds to source tick 3), while the match reports no contact. The test compares
the dynamic mesh endpoints against a separate `xm::Controller::evalWorld` transform of
the equipped prop anchors, and checks that item001's texture-only second row produces
no second ribbon. The same whiff is rendered at the final active sample; the original
screenshots supplied during issue #53 show the broad cyan/blue blade sweep. The port
uses its existing additive `Pass::Effect` state. `FUN_004303b0` sets D3D draw state,
but its exact WebGPU blend/fade equivalent is not established, so the capture is a
shape/color-family match rather than a pixel-parity claim.

`animation_data_test` also drives actual Akane+0 input with a distant dummy. The
move-300 miss starts its ribbon at frame 92 (phase 2, post-step tick 4/source tick 3),
dash move 330 at frame 102 (phase 2, post-step tick 11/source tick 10), and aerial
move 340 at frame 87 (phase 0, post-step tick 17/source tick 16). In each case the test
checks the active item model is 2 and compares the dynamic trail endpoints with a
separate evaluation of that model's anchors through the posed Prop1 bone. The source
phase table also drives AttackA completion when every phase has a valid rig clip and a
zero `+0x20` auto-advance gate. Missing clips or nonzero gates keep the contact-timer
fallback, so a gated move cannot be left stuck waiting for an unimplemented handler
callback (#70).

The visible Akane weapon meshes still conflate manager prop slots with item-model
indices and attach every item model to Prop1; this is independently tracked by #69.
The trail witness validates its source-selected item016 model-2 anchors/texture and world
anchors, not corrected visible katana/sheath placement. `data/trail/%02d.bmp` is a
separate table whose connection to item-backed ribbons remains unestablished.

Remaining checks: source-backed activation windows for other character/weapon handlers
and whether any producer uses the dedicated `data/trail` table.
