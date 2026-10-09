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

// First fire frame recorded for a combo/slot in the shot400 traces (-1 if absent).
int traceFireFrame(int character, int weapon, int slot, bool tag) {
    for (int i = 0; i < ginkiha::kShotTraceSummaryCount; ++i) {
        const ginkiha::ShotTraceSummary& entry = ginkiha::kShotTraceSummary[i];
        if (entry.character == character && entry.weapon == weapon && entry.slot == slot &&
            entry.tag == tag)
            return entry.fire_frame;
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
    check(traceFireFrame(0, 0, 0, false) == usageFrame,
          "trace fire frame matches usage matrix (12F)");
    check(traceFireFrame(0, 0, 0, false) >= 0, "Rena 0/0 trace recorded");

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

    std::printf("ginkiha_tables_test: %d checks, %d failures\n", g_checks, g_failures);
    return g_failures == 0 ? 0 : 1;
}
