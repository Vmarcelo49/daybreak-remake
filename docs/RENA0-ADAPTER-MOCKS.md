# Rena+0 adapter sketches after source reconnaissance

These are **non-compiling design mocks**, not new runtime code or a change to
the approved pilot contract. They show where recovered Rena+0 decisions could
meet the current foundation game path. The source navigation audit is
[`RENA0-SOURCE-MAP.md`](RENA0-SOURCE-MAP.md); the measured field/service seam
and actual pilot evidence remain in [`PILOT-SEAM.md`](PILOT-SEAM.md). The pilot
verdict remains pending in `SCOREBOARD.md`. No original-runtime parity follows
from these sketches.

## Reconnaissance that constrains the design

1. **The equipped combo is the key.** The bundle's `character_dispatch.hpp:9`
   identifies `(character=0, weapon=0)` with original update `0x0043ffc0`.
   `character_asset_files.hpp:14-25` builds `data/rena/00.dat`, then obtains the
   item ID from that DAT; it does not infer the item from the filename. In the
   port, `CharacterMoves::character_index()` and the parsed `weapon_id()` are
   separate checks (`remake/foundation/src/gameplay/character_moves.h:79-93`),
   and `WeaponDefinition` owns the item/bullet table
   (`remake/foundation/src/gameplay/weapon_definition.h:68-88`).
2. **Admission is earlier than action execution.** With native slot 7 enabled
   and a recovered equipped actor, the bundle calls
   `advance_native_slot7_body` and continues the admission loop
   (`development_animated_combat.hpp:1689-1692`). The later hand-written
   admission block is not the effective source path for that case. A port mock
   must use the state proposed by admission on the correct tick, then let the
   selected action body run; a convenient Rena-named function is not
   automatically the first handler.
3. **Generated bodies can win.** The bundle checks native shooting, full
   charge and special strike, then dash and jump before its later action chain
   (`development_animated_combat.hpp:2060-2076`). The generated remaining-melee
   route for Rena+0 states 332-334 and 340-341 precedes the Rena-named melee
   helper (`:2367-2380`, then `:2482`). Body ownership should be resolved per
   state rather than by filename.
4. **The port already has several seams.** `Fighter::PilotLocomotion`,
   `PilotGuard`, `PilotShot` and `PilotCharge` exist behind the Rena+0 flag
   (`fighter.h:554-628`, `main.cpp:3978-4042`). The resolver already maps a
   proposed move/phase to a model-bounded animation set with named failures
   (`native/rena0_resolver.h:74-108`). Melee admission already runs through the
   recovered selector on the default path (`fighter.cpp:467-475`). These mocks
   extend or consolidate those facts; they are not a proposal to add a second
   permanent decision layer.
5. **The current shot pool is deferred.** `Fighter::update` queues pending
   shots; `Match::step` drains them, asks `ProjectilePool::spawn`, then updates
   contacts (`match.cpp:299-331`). The bundle's State-400 callback attempts
   magazine admission while its body runs
   (`development_animated_combat.hpp:2540-2558`, `:931-960`). Its mobile shooter
   also needs live magazine changes before subsequent body statements
   (`:2576-2595`). Therefore an event vector applied after `Fighter::update`
   cannot, by itself, model every ordered shooting decision.

The bundle's `rena_mobile_input()` hardcoded defaults are not called by its
production path. That path fills bullet/magazine and animation-phase metadata
from the loaded DATs (`development_animated_combat.hpp:2576-2589`). A mock
must do the same; copying those defaults would create an unverified duplicate.

## Mock 0: a synchronous slot-7 admission seam

The generated `slot7_body_0_0` covers far more than one attack button. Its
conditional branches request dash, special, shot, melee, jump and guard states
(`slot7_native_bodies_20260929.hpp:3-398`). The body reads current state,
button counters, priority rows, frame flags, contact, magazines and mode words.
Its callbacks for state/pose admission, contact, special activation, voice and
partner state run **during** the body
(`slot7_native_control.hpp:59-89`, `slot7_native_world.inc.hpp:20-77`).

```cpp
// DESIGN ONLY. The real field census must precede any implementation.
struct Rena0AdmissionView {
    ActionCursor current;
    SourceInputCounters input;  // held/released words, not just key edges
    int dashCommand;            // actor +0x830
    int fighterGauge;           // actor +0x834, separate from stamina
    MovePriorityView priorities; // from the equipped NN.dat, not copied constants
    FrameFlags currentFrame;
    MutableMagazineView magazines;
    SpecialModeView special;
    ActorRelationshipView relationship;
    AdmissionStatistics statistics; // direct bank deltas, including empty shots
};
struct Rena0AdmissionServices {
    virtual void enterState(int state) = 0;      // also binds state/pose now
    virtual unsigned contactFlagsNow() = 0;
    virtual void activateSpecial() = 0;
    virtual void queueVoice(const VoiceRequest&) = 0;
    virtual PartnerSnapshot partnerNow() = 0;
};

struct AdmissionResult {
    enum class Disposition { Unsupported, HandledNoState, EnteredState };
    Disposition disposition;
    int state;                    // valid only for EnteredState
    Reason reason;
};
AdmissionResult advanceRena0Slot7(Rena0AdmissionView&,
                                  Rena0AdmissionServices&);
```

This mock has a deliberate **stop condition**: if the `(0,0)` body requires
large portions of the bundle's actor/services layer after every read/write is
counted, use the measured Option A/B decision in `DIRECTION.md` §4 2a. Do not
replace its bank with zero-filled typed fields or substitute the later
hand-written Rena admission predicates. The current port already has a
recovered melee selector, but that is only one branch of slot 7.

The read-only [`slot-7 audit`](RENA0-SLOT7-AUDIT.md) found 61 distinct direct
word indexes, including 29 destination-priority constants, and six synchronous
world-service kinds. All 33 literal requested state rows exist in the pinned
Rena+0 DAT. Those counts bound the mapping exercise; they do not establish
that this mock's interface covers every branch.

A local body probe showed that idle→dash 20 depends on the frame's `0x100`
window and the fighter gauge `+0x834 > 0`, while idle→shot 400 needs primary
rounds; an empty tap writes an empty-shot statistic and requests a voice.
Equipped `Match` scenarios now show bounded recovered-body/port differences:
the port enters dash 20 at gauge zero, and an empty tap emits no voice
([`RENA0-SLOT7-AUDIT.md`](RENA0-SLOT7-AUDIT.md), "Production
`Match`/`Fighter` comparisons"). They do not establish original-runtime
parity or decide the eventual pilot-flag implementation.

The disposition matters at the integration point. With the pilot flag off,
`Fighter` follows its existing path. With the flag on and Rena+0 equipped,
slot 7 runs once before the legacy admission checks. `EnteredState` binds the
source-requested row through the existing resolver. `HandledNoState` means
the source evaluated the input and **refused or serviced it without a state**:
the legacy dash/shot selector must not then admit that same input. An empty
shot belongs here because its voice/statistic are still ordered effects.
`Unsupported` is a named pilot coverage gap, never silently reclassified as a
source refusal. This shape preserves the flag-off control until the owner's
verdict and avoids two authoritative decisions on a flagged tick.

## Mock A: a narrow action proposal at the existing fighter seam

This is the smallest shape for a body whose result is a state, move, or motion
proposal and whose required services have already been mapped. It fits the
existing Rena+0 flag and `Fighter::PilotLocomotion` pattern. Types and function
names below are illustrative; none exists as a new API.

```cpp
// DESIGN ONLY: host fills every field from a documented source or returns a
// named unsupported result. No default zero for an unmapped source word.
struct Rena0FrameView {
    ComboId combo;                 // character 0, weapon slot 0, item 001 checked
    ActionCursor cursor;           // state, phase, frame, paired clock
    InputEdges input;              // current and previous input in source order
    ActorMotion motion;            // units and angle convention explicit
    MoveRecordView move;           // current NN.dat frame, if one is bound
};
struct Rena0Proposal {
    OptionalState nextState;
    OptionalMove nextMove;
    OptionalPhase nextPhase;
    OptionalMotion motion;
    Reason reason;                 // applied, refused, or named missing dependency
};

Rena0Proposal evaluateRena0Body(const Rena0FrameView&, const MoveCatalog&);
```

**Possible handoff:** `App` attaches a pilot policy to the equipped Rena+0
fighter before `Match::step` (as it already does at `main.cpp:3978-4007`). The
body supplies only the decision channels it owns. `Fighter` retains the
existing position integration, collision, and phase/binding services where
the pilot seam has established them (`PILOT-SEAM.md` §16). The existing
`resolve_rena0_set` maps a resulting row and phase to the actual model set;
missing rows or bounds remain explicit. The default path remains attached to
no pilot policy until the owner verdict.

**Where this mock fits:** idle/walk proposals and selected action-body outputs
*after* admission; it can consume a row supplied by the existing recovered
melee selector. It is **not** an implementation of the generated slot-7
admission above. It does not solve ordered shot services, hit/KO, or the
bundle's paired clock by declaring those fields zero. Adding a broad `Fighter`
reference to the body would hide the field map that Phase 2b requires.

## Mock B: a synchronous host for the State-400 shooting body

The bundle's `advance_rena_ground_shot` publishes events in source order
(`battle_rena_ground_shot.hpp:24-44`). Rena+0 frame 12 requests model clears,
sound 70, shooting statistics, a voice chosen from current rounds, and an
attachment projectile. The host must distinguish **attempted request**,
**magazine admission**, **pool birth**, and **contact**. These are separate
events in the bundle and in the port.

```cpp
// DESIGN ONLY: called at each body statement, not after collecting the frame.
struct Rena0ShotHost {
    virtual void selectHeldModel(int slot, int model) = 0;
    virtual void queueSound(int id) = 0;
    virtual void queueVoice(int id, int priority) = 0;
    virtual void noteShotAttempt() = 0;
    virtual AdmissionResult requestAttachmentShot(const ShotRequest&) = 0;
    virtual int primaryRoundsNow() const = 0;
};

ShotBodyResult advanceRena0State400(
    const Rena0FrameView&, Rena0ShotHost& host);
```

`requestAttachmentShot` would check the equipped item bullet row and consume
the appropriate magazine immediately, matching
`append_actor_projectile_request` (`development_animated_combat.hpp:931-960`).
It would then enqueue a birth request for the existing `ProjectilePool` rather
than equating an attempt with a spawned projectile. Bone/socket resolution
must use the current posed actor and selected held model; a hidden model `-1`
changes the offset source (`:947-957`). The later `Match` pool and contact
passes still own birth success and hit results (`match.cpp:299-331`).

The port's present `rena0_ground_shot_observation.h` returns an ordered event
vector for a bounded comparison (`:83-91`), and the pilot compares fire,
sound, voice and model behaviour (`PILOT-SEAM.md` §18, §24). That observer is
useful evidence. This mock would need an explicit synchronous execution seam
before it could drive every shooting effect. In particular, a future mobile
shooting case cannot use a post-body replay of events when an earlier request
changes the rounds read by a later voice or shot.

## Mock C: a bounded world view for charge and projectile sockets

The source audit found a concrete world dependency for full charge: actor and
target relationships, bone/socket transforms, and statistics
(`PILOT-SEAM.md` §11-12; `full_charge_native_world.inc.hpp:23-43`). A bounded
view expresses that dependency without importing the bundle's entire
`BattleWorld`. The owner already chose that bounded-facade direction for the
pilot (`PILOT-SEAM.md` §12).

```cpp
// DESIGN ONLY. Queries use existing Match/Fighter/asset owners; each query
// either returns a value with documented units or a named missing dependency.
struct Rena0WorldView {
    virtual ActorSnapshot actor(int slot) const = 0;
    virtual RelationshipSnapshot relations(int slot) const = 0;
    virtual OptionalWorldPoint weaponSocket(int slot, int hand,
                                            int selectedModel) const = 0;
    virtual RandomWord nextBattleRandom() = 0;
};

ChargeResult advanceRena0Charge(const Rena0FrameView&,
                                Rena0WorldView&, Rena0ShotHost&);
```

This is a **shape to measure**, not an assertion that the charge action bodies
are ready to drive. The current pilot adapted charge gauge rules and pinned
their observable effects, while its proposed v3 still names the generated
charge move bodies as excluded (`PILOT-EVIDENCE-CONTRACT.md` V3-2). Socket
and target queries would need fixture values and real-data checks before any
authoritative use. If implementing this view pulls in most of the bundle's
actor/services machinery, `DIRECTION.md` §4 2a says to stop and present the
broader adoption option to the owner.

## Checks before any mock becomes implementation

| Check | Concrete result required |
|---|---|
| Dispatch ownership | For each Rena+0 state, record the winning slot-7 and body predicate, including generated-body precedence. |
| Input/context | Map every consumed field to port state, a justified new field, or a named blocker; pin previous-input semantics and units. |
| Data | Read actual Rena+0 NN.dat and item-1 entries through the existing loaders; distinguish installed values from source defaults. |
| Synchronous services | Verify ordered RNG, magazine admission, model/socket lookup, projectile enqueue, and later pool/contact outputs in a bounded fixture. |
| Binding | Use the one Rena+0 resolver; a missing row/phase/set or model bound fails with an explicit reason. |
| Evidence | Compare standalone body and integrated adapter on identical fixture input; add independent addressed-code or artifact checks where available. Shared-source agreement is only consistency evidence. |
| Rollback | Keep the existing flag-off path through the owner's 2g verdict; do not delete it while the verdict is pending. |

No row here authorizes expanding to another combo, changing approved contract
exclusions, or replacing the currently frozen decision path. The sketches are
review material for the Rena+0 pilot only.
