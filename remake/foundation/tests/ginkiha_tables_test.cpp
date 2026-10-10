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

    // 12. Seventh combo (Kasai 1 = character 12, weapon 1, swap code 38): pins the
    //    bundle rows Fase 2's Kasai program will consume. His pattern is phase-0-only
    //    (all other combos span phases 0..5): slots 0 (normal), 1 (tag) and 2 (both)
    //    fire at frames 10 and 15..24 — 11 pairs each, 44 total. The traces fire twin
    //    rows 2+0 only in variant 0. Two births are sampled (slot 0 speed 34.75 turn
    //    0.76, slot 10 speed 39.75 turn 1.26).
    const ginkiha::BirthProfile* kasai = findBirth(12, 1, 0);
    check(kasai != nullptr, "Kasai 1/0 birth profile exists");
    if (kasai) {
        check(kasai->swap_code == 38, "Kasai 1 maps to swap code 38");
        check(kasai->speed == 34.75f, "Kasai 1/0 birth speed 34.75");
        check(kasai->turn_birth > 0.759f && kasai->turn_birth < 0.761f,
              "Kasai 1/0 birth turn 0.76");
    }
    const ginkiha::BirthProfile* kasai10 = findBirth(12, 1, 10);
    check(kasai10 != nullptr, "Kasai 1/10 birth profile exists");
    if (kasai10) {
        check(kasai10->speed == 39.75f, "Kasai 1/10 birth speed 39.75");
        check(kasai10->turn_birth > 1.259f && kasai10->turn_birth < 1.261f,
              "Kasai 1/10 birth turn 1.26");
    }
    int kasaiPairs = 0;
    bool kasaiShape = true;
    for (int i = 0; i < ginkiha::kShotFireRecordCount; ++i) {
        const ginkiha::ShotFireRecord& entry = ginkiha::kShotFireRecord[i];
        if (entry.character == 12 && entry.weapon == 1 && entry.slot == 0 && !entry.tag) {
            ++kasaiPairs;
            if (entry.phase != 0) kasaiShape = false;
            if (entry.frame != 10 && (entry.frame < 15 || entry.frame > 24)) kasaiShape = false;
        }
    }
    check(kasaiPairs == 11, "Kasai 1/0 usage holds 11 fire records");
    check(kasaiShape, "Kasai 1/0 usage shape is phase 0 only, frames 10 and 15..24");
    check(traceFireFrame(12, 1, 0, false) == 10, "Kasai 1/0 trace opens at 10F");
    check(traceFireEvents(12, 1, 0, false) == 22, "Kasai 1/0 trace holds 22 twin events");
    bool kasaiSilent = true;
    for (int v = 1; v < 6; ++v) {
        if (traceFireFrame(12, 1, v, false) != -1) kasaiSilent = false;
    }
    check(kasaiSilent, "Kasai 1/0 other variants record no fire");
    unsigned int kasaiUpdate = 0;
    for (int i = 0; i < ginkiha::kDispatchIdentityCount; ++i) {
        if (ginkiha::kDispatchIdentity[i].character == 12 &&
            ginkiha::kDispatchIdentity[i].weapon == 1)
            kasaiUpdate = ginkiha::kDispatchIdentity[i].update;
    }
    check(kasaiUpdate == 0x005B9680u, "Kasai 1 dispatch update is 0x5b9680");
    const gameplay::LocomotionDefinition* kasai1 = nullptr;
    for (const gameplay::LocomotionDefinition& entry : gameplay::kLocomotion) {
        if (entry.character == 12 && entry.slot == 1) kasai1 = &entry;
    }
    if (kasai1) check(kasaiUpdate == kasai1->handler, "bundle dispatch matches kLocomotion (Kasai 1)");
    check(walkVa(12, 1) == 0x005B9B16u, "Kasai 1 walk site is 0x5b9b16 (Fase 2 oracle)");

    // 13. Eighth combo (Takano 0 = character 7, weapon 0, swap code 22): pins the bundle
    //    rows Fase 2's Takano program will consume. Slots 0 (normal) and 6 (tag) fire
    //    phases 0..5 at frames 12, 15 and 18 (18 pairs each); the traces record NO fire
    //    under fixed inputs (like Rika/Chie). Two births are sampled (slot 0 speed 35.0
    //    with no turn data, slot 10 speed 55.0).
    const ginkiha::BirthProfile* takano = findBirth(7, 0, 0);
    check(takano != nullptr, "Takano 0/0 birth profile exists");
    if (takano) {
        check(takano->swap_code == 22, "Takano 0 maps to swap code 22");
        check(takano->speed == 35.0f, "Takano 0/0 birth speed 35.0");
        check(takano->turn_birth == 0.0f && takano->turn_next == 0.0f,
              "Takano 0/0 birth has no turn data");
    }
    const ginkiha::BirthProfile* takano10 = findBirth(7, 0, 10);
    check(takano10 != nullptr, "Takano 0/10 birth profile exists");
    if (takano10) check(takano10->speed == 55.0f, "Takano 0/10 birth speed 55.0");
    int takanoPairs = 0;
    bool takanoShape = true;
    for (int i = 0; i < ginkiha::kShotFireRecordCount; ++i) {
        const ginkiha::ShotFireRecord& entry = ginkiha::kShotFireRecord[i];
        if (entry.character == 7 && entry.weapon == 0 && entry.slot == 0 && !entry.tag) {
            ++takanoPairs;
            if (entry.phase < 0 || entry.phase > 5 || (entry.frame != 12 && entry.frame != 15 &&
                                                       entry.frame != 18))
                takanoShape = false;
        }
    }
    check(takanoPairs == 18, "Takano 0/0 usage holds 18 fire records");
    check(takanoShape, "Takano 0/0 usage shape is phases 0..5, frames 12/15/18");
    bool takanoSilent = true;
    for (int v = 0; v < 6; ++v) {
        if (traceFireFrame(7, 0, v, false) != -1) takanoSilent = false;
    }
    check(takanoSilent, "Takano 0/0 traces record no fire under fixed inputs");
    unsigned int takanoUpdate = 0;
    for (int i = 0; i < ginkiha::kDispatchIdentityCount; ++i) {
        if (ginkiha::kDispatchIdentity[i].character == 7 &&
            ginkiha::kDispatchIdentity[i].weapon == 0)
            takanoUpdate = ginkiha::kDispatchIdentity[i].update;
    }
    check(takanoUpdate == 0x00531CE0u, "Takano 0 dispatch update is 0x531ce0");
    const gameplay::LocomotionDefinition* takano0 = nullptr;
    for (const gameplay::LocomotionDefinition& entry : gameplay::kLocomotion) {
        if (entry.character == 7 && entry.slot == 0) takano0 = &entry;
    }
    if (takano0) check(takanoUpdate == takano0->handler, "bundle dispatch matches kLocomotion (Takano 0)");
    check(walkVa(7, 0) == 0x00532176u, "Takano 0 walk site is 0x532176 (Fase 2 oracle)");

    // 14. Ninth combo (Irie 1 = character 10, weapon 1, swap code 32): pins the bundle
    //    rows Fase 2's Irie program will consume. Rena-like single anchor (phases 0..5
    //    at frame 12) across four slots — 0 and 1 in both modes, 2 and 3 tag-only (6
    //    pairs each, 36 total). The traces record NO fire under fixed inputs. Two
    //    births are sampled (slot 0 speed 35.0 with near-zero turn, slot 10 speed 47.5).
    const ginkiha::BirthProfile* irie = findBirth(10, 1, 0);
    check(irie != nullptr, "Irie 1/0 birth profile exists");
    if (irie) {
        check(irie->swap_code == 32, "Irie 1 maps to swap code 32");
        check(irie->speed == 35.0f, "Irie 1/0 birth speed 35.0");
    }
    const ginkiha::BirthProfile* irie10 = findBirth(10, 1, 10);
    check(irie10 != nullptr, "Irie 1/10 birth profile exists");
    if (irie10) check(irie10->speed == 47.5f, "Irie 1/10 birth speed 47.5");
    int iriePairs = 0;
    bool irieShape = true;
    for (int i = 0; i < ginkiha::kShotFireRecordCount; ++i) {
        const ginkiha::ShotFireRecord& entry = ginkiha::kShotFireRecord[i];
        if (entry.character == 10 && entry.weapon == 1 && entry.slot == 0 && !entry.tag) {
            ++iriePairs;
            if (entry.phase < 0 || entry.phase > 5 || entry.frame != 12) irieShape = false;
        }
    }
    check(iriePairs == 6, "Irie 1/0 usage holds 6 fire records");
    check(irieShape, "Irie 1/0 usage shape is phases 0..5 at frame 12");
    bool irieSilent = true;
    for (int v = 0; v < 6; ++v) {
        if (traceFireFrame(10, 1, v, false) != -1) irieSilent = false;
    }
    check(irieSilent, "Irie 1/0 traces record no fire under fixed inputs");
    unsigned int irieUpdate = 0;
    for (int i = 0; i < ginkiha::kDispatchIdentityCount; ++i) {
        if (ginkiha::kDispatchIdentity[i].character == 10 &&
            ginkiha::kDispatchIdentity[i].weapon == 1)
            irieUpdate = ginkiha::kDispatchIdentity[i].update;
    }
    check(irieUpdate == 0x0057F600u, "Irie 1 dispatch update is 0x57f600");
    const gameplay::LocomotionDefinition* irie1 = nullptr;
    for (const gameplay::LocomotionDefinition& entry : gameplay::kLocomotion) {
        if (entry.character == 10 && entry.slot == 1) irie1 = &entry;
    }
    if (irie1) check(irieUpdate == irie1->handler, "bundle dispatch matches kLocomotion (Irie 1)");
    check(walkVa(10, 1) == 0x0057FA4Au, "Irie 1 walk site is 0x57fa4a (Fase 2 oracle)");

    // 15. Tenth combo (Mion 2 = character 1, weapon 2, swap code 6): pins the bundle
    //    rows Fase 2's Mion-2 program will consume. Twin anchors (frames 10 AND 18, row 0
    //    both) in every variant — the second two-anchor pattern after Kasai's twin rows.
    //    Usage agrees per variant; the traces fire row 0 at both frames.
    const ginkiha::BirthProfile* mion2 = findBirth(1, 2, 0);
    check(mion2 != nullptr, "Mion 2/0 birth profile exists");
    if (mion2) {
        check(mion2->swap_code == 6, "Mion 2 maps to swap code 6");
        check(mion2->speed == 35.0f, "Mion 2/0 birth speed 35.0");
        check(mion2->turn_birth > 0.099f && mion2->turn_birth < 0.101f,
              "Mion 2/0 birth turn 0.1");
    }
    int mion2Pairs = 0;
    bool mion2Shape = true;
    for (int i = 0; i < ginkiha::kShotFireRecordCount; ++i) {
        const ginkiha::ShotFireRecord& entry = ginkiha::kShotFireRecord[i];
        if (entry.character == 1 && entry.weapon == 2 && entry.slot == 0 && !entry.tag) {
            ++mion2Pairs;
            if (entry.phase < 0 || entry.phase > 5 || (entry.frame != 10 && entry.frame != 18))
                mion2Shape = false;
        }
    }
    check(mion2Pairs == 12, "Mion 2/0 usage holds 12 fire records");
    check(mion2Shape, "Mion 2/0 usage shape is phases 0..5, frames 10 and 18");
    bool mion2Twin = true;
    for (int variant = 0; variant < 6; ++variant) {
        if (traceFireFrame(1, 2, variant, false) != 10) mion2Twin = false;
        if (traceFireEvents(1, 2, variant, false) != 2) mion2Twin = false;
    }
    check(mion2Twin, "Mion 2 traces open at 10F with 2 events each");
    unsigned int mion2Update = 0;
    for (int i = 0; i < ginkiha::kDispatchIdentityCount; ++i) {
        if (ginkiha::kDispatchIdentity[i].character == 1 &&
            ginkiha::kDispatchIdentity[i].weapon == 2)
            mion2Update = ginkiha::kDispatchIdentity[i].update;
    }
    check(mion2Update == 0x0044FA10u, "Mion 2 dispatch update is 0x44fa10");
    const gameplay::LocomotionDefinition* mion22 = nullptr;
    for (const gameplay::LocomotionDefinition& entry : gameplay::kLocomotion) {
        if (entry.character == 1 && entry.slot == 2) mion22 = &entry;
    }
    if (mion22) check(mion2Update == mion22->handler, "bundle dispatch matches kLocomotion (Mion 2)");
    check(walkVa(1, 2) == 0x0044FEA6u, "Mion 2 walk site is 0x44fea6 (Fase 2 oracle)");

    // 16. Eleventh combo (Rika 2 = character 4, weapon 2, swap code 15): pins the bundle
    //    rows Fase 2's Rika-2 program will consume. Single anchor (frame 15, all phases)
    //    across slots 0 (both modes), 1 and 2 (tag) — 6 pairs each. The traces record NO
    //    fire under fixed inputs. Two births are sampled (slot 0 speed 39.75, slot 10
    //    speed 39.5, both turnless).
    const ginkiha::BirthProfile* rika2 = findBirth(4, 2, 0);
    check(rika2 != nullptr, "Rika 2/0 birth profile exists");
    if (rika2) {
        check(rika2->swap_code == 15, "Rika 2 maps to swap code 15");
        check(rika2->speed == 39.75f, "Rika 2/0 birth speed 39.75");
        check(rika2->turn_birth == 0.0f && rika2->turn_next == 0.0f,
              "Rika 2/0 birth has no turn data");
    }
    const ginkiha::BirthProfile* rika210 = findBirth(4, 2, 10);
    check(rika210 != nullptr, "Rika 2/10 birth profile exists");
    if (rika210) check(rika210->speed == 39.5f, "Rika 2/10 birth speed 39.5");
    int rika2Pairs = 0;
    bool rika2Shape = true;
    for (int i = 0; i < ginkiha::kShotFireRecordCount; ++i) {
        const ginkiha::ShotFireRecord& entry = ginkiha::kShotFireRecord[i];
        if (entry.character == 4 && entry.weapon == 2 && entry.slot == 0 && !entry.tag) {
            ++rika2Pairs;
            if (entry.phase < 0 || entry.phase > 5 || entry.frame != 15) rika2Shape = false;
        }
    }
    check(rika2Pairs == 6, "Rika 2/0 usage holds 6 fire records");
    check(rika2Shape, "Rika 2/0 usage shape is phases 0..5 at frame 15");
    bool rika2Silent = true;
    for (int v = 0; v < 6; ++v) {
        if (traceFireFrame(4, 2, v, false) != -1) rika2Silent = false;
    }
    check(rika2Silent, "Rika 2/0 traces record no fire under fixed inputs");
    unsigned int rika2Update = 0;
    for (int i = 0; i < ginkiha::kDispatchIdentityCount; ++i) {
        if (ginkiha::kDispatchIdentity[i].character == 4 &&
            ginkiha::kDispatchIdentity[i].weapon == 2)
            rika2Update = ginkiha::kDispatchIdentity[i].update;
    }
    check(rika2Update == 0x0049D890u, "Rika 2 dispatch update is 0x49d890");
    const gameplay::LocomotionDefinition* rika22 = nullptr;
    for (const gameplay::LocomotionDefinition& entry : gameplay::kLocomotion) {
        if (entry.character == 4 && entry.slot == 2) rika22 = &entry;
    }
    if (rika22) check(rika2Update == rika22->handler, "bundle dispatch matches kLocomotion (Rika 2)");
    check(walkVa(4, 2) == 0x0049DD26u, "Rika 2 walk site is 0x49dd26 (Fase 2 oracle)");

    // 17. Twelfth combo (Kasai 0 = character 12, weapon 0, swap code 37): pins the bundle
    //    rows Fase 2's Kasai-0 program will consume. Single anchor (frame 20, all phases)
    //    across slots 0 (normal), 1 (tag) and 2 (both) — 6 pairs each. The traces fire a
    //    mixed salvo at frame 20: one row-2 plus three row-0 events (4 events total).
    //    Two births share speed 28.0 (slots 0 and 10, both turnless).
    const ginkiha::BirthProfile* kasai0 = findBirth(12, 0, 0);
    check(kasai0 != nullptr, "Kasai 0/0 birth profile exists");
    if (kasai0) {
        check(kasai0->swap_code == 37, "Kasai 0 maps to swap code 37");
        check(kasai0->speed == 28.0f, "Kasai 0/0 birth speed 28.0");
        check(kasai0->turn_birth == 0.0f && kasai0->turn_next == 0.0f,
              "Kasai 0/0 birth has no turn data");
    }
    const ginkiha::BirthProfile* kasai010 = findBirth(12, 0, 10);
    check(kasai010 != nullptr, "Kasai 0/10 birth profile exists");
    if (kasai010) check(kasai010->speed == 28.0f, "Kasai 0/10 birth speed 28.0");
    int kasai0Pairs = 0;
    bool kasai0Shape = true;
    for (int i = 0; i < ginkiha::kShotFireRecordCount; ++i) {
        const ginkiha::ShotFireRecord& entry = ginkiha::kShotFireRecord[i];
        if (entry.character == 12 && entry.weapon == 0 && entry.slot == 0 && !entry.tag) {
            ++kasai0Pairs;
            if (entry.phase < 0 || entry.phase > 5 || entry.frame != 20) kasai0Shape = false;
        }
    }
    check(kasai0Pairs == 6, "Kasai 0/0 usage holds 6 fire records");
    check(kasai0Shape, "Kasai 0/0 usage shape is phases 0..5 at frame 20");
    check(traceFireFrame(12, 0, 0, false) == 20, "Kasai 0/0 trace opens at 20F");
    // Scatter volley: 21 fire events at frame 20 per normal variant (1x row 2 + 20x
    // row 0 with shared aim), 31 per tag variant (1x row 2 + 30x row 1). The count,
    // not just the frame, is the pinned fact — an earlier pin read only the first
    // four events of a truncated dump and rightly failed.
    bool kasaiVolley = true;
    for (int v = 0; v < 6; ++v) {
        if (traceFireFrame(12, 0, v, false) != 20) kasaiVolley = false;
        if (traceFireEvents(12, 0, v, false) != 21) kasaiVolley = false;
        if (traceFireFrame(12, 0, v, true) != 20) kasaiVolley = false;
        if (traceFireEvents(12, 0, v, true) != 31) kasaiVolley = false;
    }
    check(kasaiVolley, "Kasai 0/0 volley is 21 normal / 31 tag events at 20F");
    unsigned int kasai0Update = 0;
    for (int i = 0; i < ginkiha::kDispatchIdentityCount; ++i) {
        if (ginkiha::kDispatchIdentity[i].character == 12 &&
            ginkiha::kDispatchIdentity[i].weapon == 0)
            kasai0Update = ginkiha::kDispatchIdentity[i].update;
    }
    check(kasai0Update == 0x005B0990u, "Kasai 0 dispatch update is 0x5b0990");
    const gameplay::LocomotionDefinition* kasai00 = nullptr;
    for (const gameplay::LocomotionDefinition& entry : gameplay::kLocomotion) {
        if (entry.character == 12 && entry.slot == 0) kasai00 = &entry;
    }
    if (kasai00) check(kasai0Update == kasai00->handler, "bundle dispatch matches kLocomotion (Kasai 0)");
    check(walkVa(12, 0) == 0x005B0E29u, "Kasai 0 walk site is 0x5b0e29 (Fase 2 oracle)");

    // 18. Thirteenth combo (Satoko 0 = character 3, weapon 0, swap code 10): pins the
    //    bundle rows Fase 2's Satoko program will consume. Single anchor (frame 17, all
    //    phases) on slot 0 in both modes — 6 pairs each. The traces record NO fire under
    //    fixed inputs. Two births are sampled (slot 0 speed 27.5 turn 0.5, slot 10
    //    speed 40.0 turn 0.75).
    const ginkiha::BirthProfile* satoko = findBirth(3, 0, 0);
    check(satoko != nullptr, "Satoko 0/0 birth profile exists");
    if (satoko) {
        check(satoko->swap_code == 10, "Satoko 0 maps to swap code 10");
        check(satoko->speed == 27.5f, "Satoko 0/0 birth speed 27.5");
        check(satoko->turn_birth > 0.499f && satoko->turn_birth < 0.501f,
              "Satoko 0/0 birth turn 0.5");
    }
    const ginkiha::BirthProfile* satoko10 = findBirth(3, 0, 10);
    check(satoko10 != nullptr, "Satoko 0/10 birth profile exists");
    if (satoko10) {
        check(satoko10->speed == 40.0f, "Satoko 0/10 birth speed 40.0");
        check(satoko10->turn_birth > 0.749f && satoko10->turn_birth < 0.751f,
              "Satoko 0/10 birth turn 0.75");
    }
    int satokoPairs = 0;
    bool satokoShape = true;
    for (int i = 0; i < ginkiha::kShotFireRecordCount; ++i) {
        const ginkiha::ShotFireRecord& entry = ginkiha::kShotFireRecord[i];
        if (entry.character == 3 && entry.weapon == 0 && entry.slot == 0 && !entry.tag) {
            ++satokoPairs;
            if (entry.phase < 0 || entry.phase > 5 || entry.frame != 17) satokoShape = false;
        }
    }
    check(satokoPairs == 6, "Satoko 0/0 usage holds 6 fire records");
    check(satokoShape, "Satoko 0/0 usage shape is phases 0..5 at frame 17");
    bool satokoSilent = true;
    for (int v = 0; v < 6; ++v) {
        if (traceFireFrame(3, 0, v, false) != -1) satokoSilent = false;
    }
    check(satokoSilent, "Satoko 0/0 traces record no fire under fixed inputs");
    unsigned int satokoUpdate = 0;
    for (int i = 0; i < ginkiha::kDispatchIdentityCount; ++i) {
        if (ginkiha::kDispatchIdentity[i].character == 3 &&
            ginkiha::kDispatchIdentity[i].weapon == 0)
            satokoUpdate = ginkiha::kDispatchIdentity[i].update;
    }
    check(satokoUpdate == 0x004A9C40u, "Satoko 0 dispatch update is 0x4a9c40");
    const gameplay::LocomotionDefinition* satoko0 = nullptr;
    for (const gameplay::LocomotionDefinition& entry : gameplay::kLocomotion) {
        if (entry.character == 3 && entry.slot == 0) satoko0 = &entry;
    }
    if (satoko0) check(satokoUpdate == satoko0->handler, "bundle dispatch matches kLocomotion (Satoko 0)");
    check(walkVa(3, 0) == 0x004AA093u, "Satoko 0 walk site is 0x4aa093 (Fase 2 oracle)");

    // 19. Fourteenth combo (Rika 0 = character 4, weapon 0, swap code 13): pins the
    //    bundle rows Fase 2's Rika-0 program will consume. Single anchor (frame 15, all
    //    phases) on slot 0 normal and slot 1 tag — 6 pairs each. The traces record NO
    //    fire under fixed inputs. Two births are sampled (slot 0 speed 35.0, slot 10
    //    speed 55.0, both turnless).
    const ginkiha::BirthProfile* rika0 = findBirth(4, 0, 0);
    check(rika0 != nullptr, "Rika 0/0 birth profile exists");
    if (rika0) {
        check(rika0->swap_code == 13, "Rika 0 maps to swap code 13");
        check(rika0->speed == 35.0f, "Rika 0/0 birth speed 35.0");
        check(rika0->turn_birth == 0.0f && rika0->turn_next == 0.0f,
              "Rika 0/0 birth has no turn data");
    }
    const ginkiha::BirthProfile* rika010 = findBirth(4, 0, 10);
    check(rika010 != nullptr, "Rika 0/10 birth profile exists");
    if (rika010) check(rika010->speed == 55.0f, "Rika 0/10 birth speed 55.0");
    int rika0Pairs = 0;
    bool rika0Shape = true;
    for (int i = 0; i < ginkiha::kShotFireRecordCount; ++i) {
        const ginkiha::ShotFireRecord& entry = ginkiha::kShotFireRecord[i];
        if (entry.character == 4 && entry.weapon == 0 && entry.slot == 0 && !entry.tag) {
            ++rika0Pairs;
            if (entry.phase < 0 || entry.phase > 5 || entry.frame != 15) rika0Shape = false;
        }
    }
    check(rika0Pairs == 6, "Rika 0/0 usage holds 6 fire records");
    check(rika0Shape, "Rika 0/0 usage shape is phases 0..5 at frame 15");
    bool rika0Silent = true;
    for (int v = 0; v < 6; ++v) {
        if (traceFireFrame(4, 0, v, false) != -1) rika0Silent = false;
    }
    check(rika0Silent, "Rika 0/0 traces record no fire under fixed inputs");
    unsigned int rika0Update = 0;
    for (int i = 0; i < ginkiha::kDispatchIdentityCount; ++i) {
        if (ginkiha::kDispatchIdentity[i].character == 4 &&
            ginkiha::kDispatchIdentity[i].weapon == 0)
            rika0Update = ginkiha::kDispatchIdentity[i].update;
    }
    check(rika0Update == 0x00484BE0u, "Rika 0 dispatch update is 0x484be0");
    const gameplay::LocomotionDefinition* rika00 = nullptr;
    for (const gameplay::LocomotionDefinition& entry : gameplay::kLocomotion) {
        if (entry.character == 4 && entry.slot == 0) rika00 = &entry;
    }
    if (rika00) check(rika0Update == rika00->handler, "bundle dispatch matches kLocomotion (Rika 0)");
    check(walkVa(4, 0) == 0x0048502Du, "Rika 0 walk site is 0x48502d (Fase 2 oracle)");

    // 20. Fifteenth combo (Shion 0 = character 5, weapon 0, swap code 16): pins the
    //    bundle rows Fase 2's Shion program will consume. Single anchor (frame 16, all
    //    phases) on slot 0 normal and slot 2 tag — note the missing slot 1 (unlike the
    //    usual 0/1 pairing). The traces record NO fire under fixed inputs. A single
    //    birth is sampled (slot 0 speed 35.0 with next-tick turn 0.25 but no birth
    //    turn); slots 1-9 record speed 0.
    const ginkiha::BirthProfile* shion = findBirth(5, 0, 0);
    check(shion != nullptr, "Shion 0/0 birth profile exists");
    if (shion) {
        check(shion->swap_code == 16, "Shion 0 maps to swap code 16");
        check(shion->speed == 35.0f, "Shion 0/0 birth speed 35.0");
    }
    int shionPairs = 0;
    bool shionShape = true;
    for (int i = 0; i < ginkiha::kShotFireRecordCount; ++i) {
        const ginkiha::ShotFireRecord& entry = ginkiha::kShotFireRecord[i];
        if (entry.character == 5 && entry.weapon == 0 && entry.slot == 0 && !entry.tag) {
            ++shionPairs;
            if (entry.phase < 0 || entry.phase > 5 || entry.frame != 16) shionShape = false;
        }
    }
    check(shionPairs == 6, "Shion 0/0 usage holds 6 fire records");
    check(shionShape, "Shion 0/0 usage shape is phases 0..5 at frame 16");
    bool shionSilent = true;
    for (int v = 0; v < 6; ++v) {
        if (traceFireFrame(5, 0, v, false) != -1) shionSilent = false;
    }
    check(shionSilent, "Shion 0/0 traces record no fire under fixed inputs");
    unsigned int shionUpdate = 0;
    for (int i = 0; i < ginkiha::kDispatchIdentityCount; ++i) {
        if (ginkiha::kDispatchIdentity[i].character == 5 &&
            ginkiha::kDispatchIdentity[i].weapon == 0)
            shionUpdate = ginkiha::kDispatchIdentity[i].update;
    }
    check(shionUpdate == 0x004F92A0u, "Shion 0 dispatch update is 0x4f92a0");
    const gameplay::LocomotionDefinition* shion0 = nullptr;
    for (const gameplay::LocomotionDefinition& entry : gameplay::kLocomotion) {
        if (entry.character == 5 && entry.slot == 0) shion0 = &entry;
    }
    if (shion0) check(shionUpdate == shion0->handler, "bundle dispatch matches kLocomotion (Shion 0)");
    check(walkVa(5, 0) == 0x004F973Cu, "Shion 0 walk site is 0x4f973c (Fase 2 oracle)");

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
