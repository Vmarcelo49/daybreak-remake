# TODO — daybreak_mvp

> Once MVP compiles and runs (shows window, clear screen, closes on ESC), here's the incremental path to a real port.

## Phase MVP+1: First scene (Title screen)

**Goal**: Show something other than clear screen.

- [ ] Extract all 10 shaders from `DaybreakDX.exe` (see `shaders/README.md`)
- [ ] Port `RenderTitle` (FUN_00403470) — 58 lines, smallest scene renderer
- [ ] Load `data/title/back00.bmp`, `data/title/logo.bmp`, `data/title/title.bmp`
- [ ] Implement `DrawSprite` (FUN_00646110) and `DrawMenuItem` (FUN_00655830)
- [ ] Translate the 9 menu items from RenderTitle (positions Y=128,160,...,384)
- [ ] Add basic menu navigation (up/down arrows)

**Estimated effort**: 1-2 days

## Phase MVP+2: Scene state machine

**Goal**: Navigate between scenes (Title → Select → VS → Battle, even if Battle is a stub).

- [ ] Port `LoadNextScene` (FUN_00406310) — 127 lines, state machine dispatcher
- [ ] Port `MainGameLoop` (FUN_00412110) — top dispatcher (still being analyzed)
- [ ] Port `SceneFactory` (FUN_004020a0) — allocates scene state objects
- [ ] Implement `GameState` struct (offsets from `binary_data/scene_table/FASE9_REPORT.md`)
- [ ] Stub all scene renderers except Title

**Estimated effort**: 3-5 days

## Phase MVP+3: Asset loading

**Goal**: Load and display real game assets.

- [ ] Port `LoadMeshFromX` (FUN_0064d940) — uses `D3DXLoadMeshHierarchyFromXInMemory`
- [ ] Port texture loading (FUN_00655600, FUN_006560c0)
- [ ] Port `FUN_00653540` (resource exists check) and `FUN_00653a40` (resource size)
- [ ] Implement `.x` file loading from `data/` directory
- [ ] Implement BMP texture loading via D3DX

**Estimated effort**: 3-5 days

## Phase MVP+4: Input mapping

**Goal**: Real keyboard → game actions mapping (not just ESC).

- [ ] Map DirectInput key codes to game actions (confirm, cancel, up, down, etc.)
- [ ] Port input globals from `binary_data/network_analysis/FASE11B_REPORT.md`:
  - `0x006cae94` → joystick X
  - `0x006cae98` → joystick Y
  - `0x006cae9c` → confirm button
  - `0x006caea0` → cancel button
- [ ] Port `IsKeyPressed` (FUN_006586d0) — checks `& 0x80` at offset+0x20+key

**Estimated effort**: 1 day

## Phase MVP+5: Battle scene (the big one)

**Goal**: Actually play a fight.

- [ ] Port `RenderBattle` (FUN_004072b0) — 256 lines, the largest scene renderer
- [ ] Port character mesh loading and animation
- [ ] Port collision detection (`D3DXIntersect` is in original)
- [ ] Port projectile system (the "tama" mesh from collision_tama.x)
- [ ] Port HUD rendering
- [ ] Port character state machines (player input → animation → movement)

**Estimated effort**: 2-4 weeks (this is the bulk of the game)

## Phase MVP+6: Audio

**Goal**: Background music + sound effects.

- [ ] Decompile `InitAudio` (FUN_00661ad0) to confirm if it's DirectMusic or Miles
- [ ] Read GUIDs at `0x006ab884` and `0x006ab894` to identify audio system
- [ ] Port audio loading for `.ogg` files (BGM) and `.wav` files (voices)
- [ ] Port `WorkerThread` (FUN_006580a0) — likely sound mixer

**Estimated effort**: 1 week

## Phase MVP+7: Multiplayer (optional)

**Goal**: Online multiplayer via Steamworks or custom UDP.

- [ ] Replace DirectPlay 8 with Steamworks API (or EOS, or custom UDP)
- [ ] Port `NetworkMenuDispatcher` (FUN_00412ac0) UI
- [ ] Port `SendToPlayerOrBroadcast`, `ClientSendToServer`, `ServerSendToPlayer`
- [ ] Port message type factories (FUN_0065f180-260)
- [ ] Implement matchmaking (Steam lobbies or equivalent)

**Estimated effort**: 2-4 weeks

## Phase MVP+8: Polish

- [ ] Handle alt-tab properly (device lost recovery is in MVP but untested)
- [ ] Add window resize support (original is fixed 800x600)
- [ ] Add fullscreen toggle
- [ ] Add save/load for `config.dat`
- [ ] Port `SaveConfigFile` (FUN_006488d0) and `LoadConfigFile` (FUN_006486c0)

**Estimated effort**: 1-2 weeks

## Total roadmap estimate

- **MVP** (compiles + runs + clear screen): 2-3 days ← current
- **MVP+1 to MVP+4** (playable single player basic): 2-3 weeks
- **MVP+5** (full battle): 2-4 weeks (longest phase)
- **MVP+6** (audio): 1 week
- **MVP+7** (multiplayer): 2-4 weeks (optional)
- **MVP+8** (polish): 1-2 weeks

**Total to a playable single-player port**: ~2-3 months of focused work.
**Total to full feature parity**: ~4-6 months.
