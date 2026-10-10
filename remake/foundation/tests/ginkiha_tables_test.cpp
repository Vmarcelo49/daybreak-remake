// Pins the generated Ginkiha table against the values the port phases consume.
//
// WHY this test exists: the importer writes a ~5k-line generated header; a silent drift in
// the bundle (a re-extraction against a different EXE, a renamed key) would otherwise flow
// straight into gameplay as plausible numbers. The test reads the entry points the pilot
// (Rena 0) and Fase 2 need, and cross-checks the bundle against our own recovery:
// combat-hooks' shot400 usage matrix vs attack-preview's traces must agree on which frame
// Rena's first shot fires, and the bundle's dispatch update must equal the handler our
// move_behavior.h already gates the recovered program on.
//
// Provenance: DaybreakDX.exe SHA256 27e61475…a6a07f02 (our binary, research/binary_data),
// extracted by remake/foundation/tools/import_ginkiha_tables.py from the Ginkiha bundles
// under .local-analysis/ (never committed). Full rationale: docs/reports/ginkiha-port-plan.md §1.
#include "gameplay/ginkiha_tables.h"
#include "gameplay/move_behavior.h"

#include <cstdio>
#include <cstring>

namespace {

int g_checks = 0;
int g_failures = 0;

void check(bool ok, const char* what) {
    ++g_checks;
    if (!ok) {
        ++g_failures;
        std::printf("  FAIL %s\n", what);
    }
}

const ginkiha::BirthProfile* findBirth(int character, int weapon, int slot) {
    for (int i = 0; i < ginkiha::kBirthProfileCount; ++i) {
        const ginkiha::BirthProfile& entry = ginkiha::kBirthProfile[i];
        if (entry.character == character && entry.weapon == weapon && entry.slot == slot) return &entry;
    }
    return nullptr;
}

unsigned int walkVa(int character, int weapon) {
    for (int i = 0; i < ginkiha::kWalkHandlerCount; ++i) {
        if (ginkiha::kWalkHandler[i].character == character &&
            ginkiha::kWalkHandler[i].weapon == weapon)
            return ginkiha::kWalkHandler[i].va;
    }
    return 0;
}

// First fire frame recorded for a combo/variant in the shot400 traces (-1 if absent),
// plus the fire event count for that variant (twins count twice).
int traceFireFrame(int character, int weapon, int variant, bool tag) {
    for (int i = 0; i < ginkiha::kShotTraceSummaryCount; ++i) {
        const ginkiha::ShotTraceSummary& entry = ginkiha::kShotTraceSummary[i];
        if (entry.character == character && entry.weapon == weapon && entry.variant == variant &&
            entry.tag == tag)
            return entry.fire_frame;
    }
    return -2;
}

int traceFireEvents(int character, int weapon, int variant, bool tag) {
    for (int i = 0; i < ginkiha::kShotTraceSummaryCount; ++i) {
        const ginkiha::ShotTraceSummary& entry = ginkiha::kShotTraceSummary[i];
        if (entry.character == character && entry.weapon == weapon && entry.variant == variant &&
            entry.tag == tag)
            return entry.fire_events;
    }
    return -1;
}

}  // namespace

int main() {
    // 1. Shape: the importer emitted the whole cross product it claims.
    check(ginkiha::kBirthProfileCount == 591, "591 birth profiles");
    check(ginkiha::kWalkHandlerCount == 46, "46 walk handlers");
    check(ginkiha::kAnimationControllerCount > 0, "animation controllers present");

    // 2. Pilot values (Rena 0 = character 0, weapon 0, swap code 1): birth speed 37.5 and
    //    turn rate 0.2 come from attack-preview.json births["1:0"].
    const ginkiha::BirthProfile* rena = findBirth(0, 0, 0);
    check(rena != nullptr, "Rena 0/0 birth profile exists");
    if (rena) {
        check(rena->swap_code == 1, "Rena 0 maps to swap code 1");
        check(rena->speed == 37.5f, "Rena 0/0 birth speed 37.5");
        check(rena->turn_birth > 0.199f && rena->turn_birth < 0.201f, "Rena 0/0 birth turn 0.2");
        check(rena->turn_next > 0.199f && rena->turn_next < 0.201f, "Rena 0/0 next tick turn 0.2");
    }

    // 3. Cross-source agreement for the pilot: the usage matrix says Rena's first shot
    //    fires at state400 frame 12 in every phase 0..5, and the trace records the same
    //    frame. A divergence here means the bundle's two extractions no longer describe
    //    the same binary.
    int usageFrame = -1;
    int usagePairs = 0;
    for (int i = 0; i < ginkiha::kShotFireRecordCount; ++i) {
        const ginkiha::ShotFireRecord& entry = ginkiha::kShotFireRecord[i];
        if (entry.character == 0 && entry.weapon == 0 && entry.slot == 0 && !entry.tag) {
            ++usagePairs;
            if (usageFrame < 0) usageFrame = entry.frame;
            check(entry.frame == usageFrame, "Rena 0/0 usage frame consistent across phases");
        }
    }
    check(usagePairs == 6, "Rena 0/0 usage covers phases 0..5");
    check(usageFrame == 12, "Rena 0/0 usage anchor frame 12");
    // Every traced normal variant fires at the usage frame — the two extractions agree
    // per variant, not just on average.
    for (int variant = 0; variant < 6; ++variant) {
        char what[80];
        std::snprintf(what, sizeof what, "Rena 0/0 trace variant %d fires at 12F", variant);
        check(traceFireFrame(0, 0, variant, false) == usageFrame, what);
    }

    // 4. The bundle's dispatch entry for Rena 0 (combat-hooks.json dispatch[]) must agree
    //    with our own recovered handler — move_behavior.h gated the whole nata program on
    //    0x43ffc0, so a table regenerated against a different binary cannot silently
    //    redefine the pilot's dispatch. The walks[] VA is a different kind of address (the
    //    state-10 site inside the update, not its head), pinned below as Fase 2's oracle.
    const gameplay::LocomotionDefinition* rena0 = nullptr;
    for (const gameplay::LocomotionDefinition& entry : gameplay::kLocomotion) {
        if (entry.character == 0 && entry.slot == 0) rena0 = &entry;
    }
    check(rena0 != nullptr, "kLocomotion has the Rena 0 entry");
    unsigned int dispatchUpdate = 0;
    unsigned int dispatchVtable = 0;
    for (int i = 0; i < ginkiha::kDispatchIdentityCount; ++i) {
        if (ginkiha::kDispatchIdentity[i].character == 0 &&
            ginkiha::kDispatchIdentity[i].weapon == 0) {
            dispatchUpdate = ginkiha::kDispatchIdentity[i].update;
            dispatchVtable = ginkiha::kDispatchIdentity[i].vtable;
        }
    }
    if (rena0) {
        check(dispatchUpdate == rena0->handler, "bundle dispatch update matches kLocomotion handler");
        check(dispatchUpdate == 0x0043FFC0u, "Rena 0 dispatch update is 0x43ffc0");
    }
    check(dispatchVtable == 0x006A4E10u, "Rena 0 factory vtable is the first slot");
    check(walkVa(0, 0) == 0x00440412u,
          "Rena 0 walk state-10 site is 0x440412 (exe-catalog.walks, Fase 2 oracle)");

    // 5. Controller calibration for the pilot's model: rena/00.x exists with a period.
    bool renaModel = false;
    for (int i = 0; i < ginkiha::kAnimationControllerCount; ++i) {
        if (std::strcmp(ginkiha::kAnimationController[i].model, "data/rena/00.x") == 0) {
            renaModel = true;
            check(ginkiha::kAnimationController[i].period_seconds > 0.0, "rena/00.x period positive");
        }
    }
    check(renaModel, "rena/00.x controller set present");

    // 7. Second combo (Mion 0 = character 1, weapon 0, swap code 4): pins the bundle
    //    rows Fase 2's Mion program will consume. Unlike Rena's six uniform phases, Mion
    //    fires slot 0 only in variants 1 and 3 at frame 2 (usage '1:0:0'), and her birth
    //    is faster (42.5) with a child spawn — both must survive regeneration drift.
    const ginkiha::BirthProfile* mion = findBirth(1, 0, 0);
    check(mion != nullptr, "Mion 0/0 birth profile exists");
    if (mion) {
        check(mion->swap_code == 4, "Mion 0 maps to swap code 4");
        check(mion->speed == 42.5f, "Mion 0/0 birth speed 42.5");
        check(mion->turn_birth > 0.099f && mion->turn_birth < 0.101f, "Mion 0/0 birth turn 0.1");
    }
    int mionPairs = 0;
    int mionFrame = -1;
    for (int i = 0; i < ginkiha::kShotFireRecordCount; ++i) {
        const ginkiha::ShotFireRecord& entry = ginkiha::kShotFireRecord[i];
        if (entry.character == 1 && entry.weapon == 0 && entry.slot == 0 && !entry.tag) {
            ++mionPairs;
            if (mionFrame < 0) mionFrame = entry.frame;
            check(entry.frame == mionFrame, "Mion 0/0 usage frame consistent");
        }
    }
    check(mionPairs == 2, "Mion 0/0 usage covers variants 1 and 3 only");
    check(mionFrame == 2, "Mion 0/0 usage anchor frame 2");
    // The traces agree per variant, including the negative: variants 0/2/4/5 record
    // no fire event (-1), exactly the variants missing from the usage matrix.
    for (int variant = 0; variant < 6; ++variant) {
        const int expected = (variant == 1 || variant == 3) ? mionFrame : -1;
        char what[80];
        std::snprintf(what, sizeof what, "Mion 0/0 trace variant %d fire frame", variant);
        check(traceFireFrame(1, 0, variant, false) == expected, what);
    }
    unsigned int mionUpdate = 0;
    for (int i = 0; i < ginkiha::kDispatchIdentityCount; ++i) {
        if (ginkiha::kDispatchIdentity[i].character == 1 &&
            ginkiha::kDispatchIdentity[i].weapon == 0)
            mionUpdate = ginkiha::kDispatchIdentity[i].update;
    }
    check(mionUpdate == 0x004582A0u, "Mion 0 dispatch update is 0x4582a0");
    const gameplay::LocomotionDefinition* mion0 = nullptr;
    for (const gameplay::LocomotionDefinition& entry : gameplay::kLocomotion) {
        if (entry.character == 1 && entry.slot == 0) mion0 = &entry;
    }
    if (mion0) check(mionUpdate == mion0->handler, "bundle dispatch matches kLocomotion (Mion 0)");
    check(walkVa(1, 0) == 0x00458736u, "Mion 0 walk site is 0x458736 (Fase 2 oracle)");

    // 8. Third combo (Rika 1 = character 4, weapon 1, swap code 14): pins the bundle
    //    rows Fase 2's Rika program will consume. Her pattern differs from both pilots:
    //    slot 0 fires phases 0..5 on EVERY EVEN frame 12..40 (90 pairs — a repeating
    //    schedule, not a single anchor), birth speed is 45.0 with no turn data, and the
    //    traces record NO fire event under fixed inputs — so, unlike Rena/Mion, there is
    //    no trace-vs-usage cross-check to pin here, only the documented divergence.
    const ginkiha::BirthProfile* rika = findBirth(4, 1, 0);
    check(rika != nullptr, "Rika 1/0 birth profile exists");
    if (rika) {
        check(rika->swap_code == 14, "Rika 1 maps to swap code 14");
        check(rika->speed == 45.0f, "Rika 1/0 birth speed 45.0");
        check(rika->turn_birth == 0.0f && rika->turn_next == 0.0f,
              "Rika 1/0 birth has no turn data");
    }
    int rikaPairs = 0;
    bool rikaShape = true;
    for (int i = 0; i < ginkiha::kShotFireRecordCount; ++i) {
        const ginkiha::ShotFireRecord& entry = ginkiha::kShotFireRecord[i];
        if (entry.character == 4 && entry.weapon == 1 && entry.slot == 0 && !entry.tag) {
            ++rikaPairs;
            if (entry.phase < 0 || entry.phase > 5 || entry.frame < 12 || entry.frame > 40 ||
                (entry.frame % 2) != 0)
                rikaShape = false;
        }
    }
    check(rikaPairs == 90, "Rika 1/0 usage holds 90 fire records");
    check(rikaShape, "Rika 1/0 usage shape is phases 0..5, even frames 12..40");
    bool rikaTraceSilent = true;
    for (int v = 0; v < 6; ++v) {
        if (traceFireFrame(4, 1, v, false) != -1) rikaTraceSilent = false;
    }
    check(rikaTraceSilent, "Rika 1/0 traces record no fire under fixed inputs");
    unsigned int rikaUpdate = 0;
    for (int i = 0; i < ginkiha::kDispatchIdentityCount; ++i) {
        if (ginkiha::kDispatchIdentity[i].character == 4 &&
            ginkiha::kDispatchIdentity[i].weapon == 1)
            rikaUpdate = ginkiha::kDispatchIdentity[i].update;
    }
    check(rikaUpdate == 0x00492F70u, "Rika 1 dispatch update is 0x492f70");
    const gameplay::LocomotionDefinition* rika1 = nullptr;
    for (const gameplay::LocomotionDefinition& entry : gameplay::kLocomotion) {
        if (entry.character == 4 && entry.slot == 1) rika1 = &entry;
    }
    if (rika1) check(rikaUpdate == rika1->handler, "bundle dispatch matches kLocomotion (Rika 1)");
    check(walkVa(4, 1) == 0x004933BDu, "Rika 1 walk site is 0x4933bd (Fase 2 oracle)");

    // 9. Fourth combo (Tomitake 2 = character 6, weapon 2, swap code 21): pins the
    //    bundle rows Fase 2's Tomitake program will consume. His pattern is a third
    //    shape: twin shots (TWO fire events per frame) on every third tick 15..33,
    //    slots 5 (normal) and 6 (tag) plus slot 7 in both modes — 168 pairs total.
    //    Note the slot split: the sampled birth lives on slot 0 (speed 35.0 — the row
    //    the charges fire), while the tap fires slots 5+7, which have no sampled birth.
    const ginkiha::BirthProfile* tomitake = findBirth(6, 2, 0);
    check(tomitake != nullptr, "Tomitake 2/0 birth profile exists");
    if (tomitake) {
        check(tomitake->swap_code == 21, "Tomitake 2 maps to swap code 21");
        check(tomitake->speed == 35.0f, "Tomitake 2/0 birth speed 35.0");
        check(tomitake->turn_birth == 0.0f && tomitake->turn_next == 0.0f,
              "Tomitake 2/0 birth has no turn data");
    }
    int tomitakePairs = 0;
    bool tomitakeShape = true;
    for (int i = 0; i < ginkiha::kShotFireRecordCount; ++i) {
        const ginkiha::ShotFireRecord& entry = ginkiha::kShotFireRecord[i];
        if (entry.character == 6 && entry.weapon == 2 &&
            (entry.slot == 5 || entry.slot == 6 || entry.slot == 7)) {
            ++tomitakePairs;
            if (entry.phase < 0 || entry.phase > 5 || entry.frame < 15 || entry.frame > 33 ||
                ((entry.frame - 15) % 3) != 0)
                tomitakeShape = false;
        }
    }
    check(tomitakePairs == 168, "Tomitake 2 usage holds 168 fire records");
    check(tomitakeShape, "Tomitake 2 usage shape is phases 0..5, frames 15..33 step 3");
    // Every traced variant opens fire at frame 15 with two events per scheduled frame
    // (twin shots); the usage matrix independently schedules the same frames.
    bool tomitakeTwin = true;
    for (int variant = 0; variant < 6; ++variant) {
        if (traceFireFrame(6, 2, variant, false) != 15) tomitakeTwin = false;
        if (traceFireEvents(6, 2, variant, false) != 14) tomitakeTwin = false;
    }
    check(tomitakeTwin, "Tomitake 2 traces open at 15F with 14 events each");
    unsigned int tomitakeUpdate = 0;
    for (int i = 0; i < ginkiha::kDispatchIdentityCount; ++i) {
        if (ginkiha::kDispatchIdentity[i].character == 6 &&
            ginkiha::kDispatchIdentity[i].weapon == 2)
            tomitakeUpdate = ginkiha::kDispatchIdentity[i].update;
    }
    check(tomitakeUpdate == 0x00527880u, "Tomitake 2 dispatch update is 0x527880");
    const gameplay::LocomotionDefinition* tomitake2 = nullptr;
    for (const gameplay::LocomotionDefinition& entry : gameplay::kLocomotion) {
        if (entry.character == 6 && entry.slot == 2) tomitake2 = &entry;
    }
    if (tomitake2) check(tomitakeUpdate == tomitake2->handler, "bundle dispatch matches kLocomotion (Tomitake 2)");
    check(walkVa(6, 2) == 0x00527D4Fu, "Tomitake 2 walk site is 0x527d4f (Fase 2 oracle)");

    // 10. Fifth combo (Keiichi 2 = character 2, weapon 2, swap code 9): pins the bundle
    //    rows Fase 2's Keiichi program will consume. His pattern is a fourth shape: a
    //    DENSE burst — slot 0 fires phases 0..5 on every consecutive frame 10..20
    //    (66 pairs; tag mirrors it on slot 1). Two births are sampled (slot 0 speed
    //    42.5 with a two-sample turn trace [5.0, 0.15], slot 10 speed 39.5) — the only
    //    combo so far with a second sampled birth.
    const ginkiha::BirthProfile* keiichi = findBirth(2, 2, 0);
    check(keiichi != nullptr, "Keiichi 2/0 birth profile exists");
    if (keiichi) {
        check(keiichi->swap_code == 9, "Keiichi 2 maps to swap code 9");
        check(keiichi->speed == 42.5f, "Keiichi 2/0 birth speed 42.5");
        check(keiichi->turn_birth == 5.0f, "Keiichi 2/0 birth turn opens at 5.0");
        check(keiichi->turn_next > 0.149f && keiichi->turn_next < 0.151f,
              "Keiichi 2/0 next tick turn 0.15");
    }
    const ginkiha::BirthProfile* keiichi10 = findBirth(2, 2, 10);
    check(keiichi10 != nullptr, "Keiichi 2/10 birth profile exists");
    if (keiichi10) {
        check(keiichi10->speed == 39.5f, "Keiichi 2/10 birth speed 39.5");
        check(keiichi10->turn_birth == 0.0f && keiichi10->turn_next == 0.0f,
              "Keiichi 2/10 birth has no turn data");
    }
    int keiichiPairs = 0;
    bool keiichiShape = true;
    for (int i = 0; i < ginkiha::kShotFireRecordCount; ++i) {
        const ginkiha::ShotFireRecord& entry = ginkiha::kShotFireRecord[i];
        if (entry.character == 2 && entry.weapon == 2 && entry.slot == 0 && !entry.tag) {
            ++keiichiPairs;
            if (entry.phase < 0 || entry.phase > 5 || entry.frame < 10 || entry.frame > 20)
                keiichiShape = false;
        }
    }
    check(keiichiPairs == 66, "Keiichi 2/0 usage holds 66 fire records");
    check(keiichiShape, "Keiichi 2/0 usage shape is phases 0..5, frames 10..20");
    bool keiichiDense = true;
    for (int variant = 0; variant < 6; ++variant) {
        if (traceFireFrame(2, 2, variant, false) != 10) keiichiDense = false;
        if (traceFireEvents(2, 2, variant, false) != 11) keiichiDense = false;
    }
    check(keiichiDense, "Keiichi 2 traces open at 10F with 11 events each");
    unsigned int keiichiUpdate = 0;
    for (int i = 0; i < ginkiha::kDispatchIdentityCount; ++i) {
        if (ginkiha::kDispatchIdentity[i].character == 2 &&
            ginkiha::kDispatchIdentity[i].weapon == 2)
            keiichiUpdate = ginkiha::kDispatchIdentity[i].update;
    }
    check(keiichiUpdate == 0x0047B940u, "Keiichi 2 dispatch update is 0x47b940");
    const gameplay::LocomotionDefinition* keiichi2 = nullptr;
    for (const gameplay::LocomotionDefinition& entry : gameplay::kLocomotion) {
        if (entry.character == 2 && entry.slot == 2) keiichi2 = &entry;
    }
    if (keiichi2) check(keiichiUpdate == keiichi2->handler, "bundle dispatch matches kLocomotion (Keiichi 2)");
    check(walkVa(2, 2) == 0x0047BD8Au, "Keiichi 2 walk site is 0x47bd8a (Fase 2 oracle)");

    // 11. Sixth combo (Chie 2 = character 11, weapon 2, swap code 36): pins the bundle
    //    rows Fase 2's Chie program will consume. Her pattern is step-3 like Tomitake's
    //    (phases 0..5 at frames 15,18,21,24 — 24 pairs per slot) but single shots, and
    //    the traces record NO fire under fixed inputs (like Rika) — so no trace
    //    cross-check, only the documented divergence. Two births are sampled (slot 0
    //    speed 80.0, slot 10 speed 120.0).
    const ginkiha::BirthProfile* chie = findBirth(11, 2, 0);
    check(chie != nullptr, "Chie 2/0 birth profile exists");
    if (chie) {
        check(chie->swap_code == 36, "Chie 2 maps to swap code 36");
        check(chie->speed == 80.0f, "Chie 2/0 birth speed 80.0");
    }
    const ginkiha::BirthProfile* chie10 = findBirth(11, 2, 10);
    check(chie10 != nullptr, "Chie 2/10 birth profile exists");
    if (chie10) check(chie10->speed == 120.0f, "Chie 2/10 birth speed 120.0");
    int chiePairs = 0;
    bool chieShape = true;
    for (int i = 0; i < ginkiha::kShotFireRecordCount; ++i) {
        const ginkiha::ShotFireRecord& entry = ginkiha::kShotFireRecord[i];
        if (entry.character == 11 && entry.weapon == 2 && entry.slot == 0 && !entry.tag) {
            ++chiePairs;
            if (entry.phase < 0 || entry.phase > 5 || entry.frame < 15 || entry.frame > 24 ||
                ((entry.frame - 15) % 3) != 0)
                chieShape = false;
        }
    }
    check(chiePairs == 24, "Chie 2/0 usage holds 24 fire records");
    check(chieShape, "Chie 2/0 usage shape is phases 0..5, frames 15..24 step 3");
    bool chieTraceSilent = true;
    for (int v = 0; v < 6; ++v) {
        if (traceFireFrame(11, 2, v, false) != -1) chieTraceSilent = false;
    }
    check(chieTraceSilent, "Chie 2/0 traces record no fire under fixed inputs");
    unsigned int chieUpdate = 0;
    for (int i = 0; i < ginkiha::kDispatchIdentityCount; ++i) {
        if (ginkiha::kDispatchIdentity[i].character == 11 &&
            ginkiha::kDispatchIdentity[i].weapon == 2)
            chieUpdate = ginkiha::kDispatchIdentity[i].update;
    }
    check(chieUpdate == 0x00566A40u, "Chie 2 dispatch update is 0x566a40");
    const gameplay::LocomotionDefinition* chie2 = nullptr;
    for (const gameplay::LocomotionDefinition& entry : gameplay::kLocomotion) {
        if (entry.character == 11 && entry.slot == 2) chie2 = &entry;
    }
    if (chie2) check(chieUpdate == chie2->handler, "bundle dispatch matches kLocomotion (Chie 2)");
    check(walkVa(11, 2) == 0x00566EF7u, "Chie 2 walk site is 0x566ef7 (Fase 2 oracle)");

    // 6. Independent-recovery agreement for the pilot's ground tap: move_behavior.h's
    //    nata program launches item row 0 at tick 12 with citations into FUN_0044xxxx;
    //    the bundle's shot400 usage says the same slot fires at frame 12 in every phase.
    //    Two extractions of the same fact — if either drifts, the pilot's launch tick is
    //    no longer trustworthy. (Rena's tag row is slot 6, also at 12; that binding is a
    //    documented Fase 1 gap, so only the verified tap is checked here.)
    int nataLaunchTick = -1;
    for (const gameplay::MoveRule& rule : gameplay::kNataRules) {
        if (rule.move == 400 && rule.operation == gameplay::MoveOp::Launch) nataLaunchTick = rule.first;
    }
    check(nataLaunchTick == 12, "nata 400 tap launches at tick 12");
    check(nataLaunchTick == usageFrame, "nata launch tick equals the bundle's fire frame");

    std::printf("ginkiha_tables_test: %d checks, %d failures\n", g_checks, g_failures);
    return g_failures == 0 ? 0 : 1;
}
