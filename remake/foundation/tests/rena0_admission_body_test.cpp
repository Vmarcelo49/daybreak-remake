// P2-5 (2c) — offline body tests for the recovered Rena+0 **melee admission** body.
//
// The port's adaptation lives in `src/gameplay/melee_admission.h`; the recovered body is
// `battle_rena_melee_admission.hpp` in the local bundle. Each case feeds explicit scalars
// into the admission and checks the admitted move row, so the adapter is pinned without
// Match or Fighter in the loop.
//
// Evidence note (AGENTS.md): the expectations come from the recovered body's own branch
// order, and the port implements the same source, so agreement is a **consistency check of
// the adaptation**, not independent original proof. The port deliberately omits the
// recovered `boosted` (armed+ready) arms — its own comment calls that a recorded gap — so
// no case here asserts a boosted branch.
//
// `RENA0_ADMISSION_MATRIX=1` additionally prints the row this admission returns for a set
// of source states on the ground and in the air — the reachable set of the real table's
// gate, which is what several expectations above are anchored to.
//
// Install-backed: the priority gate reads the real move table's `cancelThreshold`/`priority`
// (character_moves.h:46-49), so a data-free run exits 77 and is reported Skipped, never a
// pass.
#include "combo_fixture.h"
#include "gameplay/melee_admission.h"

#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <string>

namespace {
int checks = 0, failures = 0;

void checkEq(int expected, int got, const char* name) {
    ++checks;
    const bool ok = expected == got;
    if (!ok) ++failures;
    std::printf("  %-66s %s", name, ok ? "ok" : "FAIL");
    if (!ok) std::printf(" (expected %d, got %d)", expected, got);
    std::printf("\n");
}

gameplay::AttackAdmissionInput in(int weapon, int state, int phase, bool grounded, int x, int z,
                                  bool normal) {
    gameplay::AttackAdmissionInput v;
    v.weaponSlot = weapon;
    v.state = state;
    v.phase = phase;
    v.grounded = grounded;
    v.x = x;
    v.z = z;
    v.normalFlag = normal;
    return v;
}
}  // namespace

int main() {
    if (test::gameInstall().empty()) {
        std::puts("SKIP: no game install reachable; the admission gate needs the real move table (not a pass)");
        return 77;
    }
    try {
        test::Combo combo;
        std::string error;
        if (!combo.load(0, 0, error)) throw std::runtime_error("Rena+0 data unavailable: " + error);
        gameplay::AttackAdmissionTable table{&combo.moves};
        const auto admit = [&](const gameplay::AttackAdmissionInput& v) {
            return gameplay::rena_melee_admission(v, table);
        };
        std::puts("P2-5 offline body tests — recovered Rena+0 melee admission (explicit inputs)");
        std::puts("\n== grounded dash sources (bundle :13-19) ==");
        checkEq(331, admit(in(0, 20, 0, true, 1, 0, true)), "forward dash + lateral input admits 331");
        checkEq(330, admit(in(0, 20, 0, true, 0, 0, true)),
                "forward dash without lateral input admits 330");
        checkEq(330, admit(in(0, 23, 0, true, 0, -1, true)), "side dash with back held admits 330");
        checkEq(331, admit(in(0, 23, 0, true, 0, 0, true)), "side dash without back admits 331");
        checkEq(331, admit(in(0, 24, 0, true, 0, 0, true)), "the other side dash admits 331 too");
        checkEq(-1, admit(in(0, 20, 0, true, 0, 0, false)),
                "without the 0x100 flag a dash source admits nothing");

        std::puts("\n== grounded directional branches (bundle :22-23) ==");
        checkEq(310, admit(in(0, 300, 0, true, 0, -1, true)), "back held admits 310");
        checkEq(311, admit(in(0, 300, 0, true, 1, 0, true)), "lateral held admits 311");
        checkEq(-1, admit(in(0, 300, 0, true, 0, 0, false)), "no axis and no flag admits nothing");

        std::puts("\n== grounded chain and landing sources (bundle :24-31) ==");
        checkEq(340, admit(in(0, 329, 0, true, 0, 0, true)), "the landing source admits 340");
        checkEq(341, admit(in(0, 340, 0, true, 0, 0, true)), "Rena+0's 340 follow-up admits 341");
        checkEq(301, admit(in(0, 300, 1, true, 0, 0, true)), "the neutral chain admits 301 from 300");
        checkEq(302, admit(in(0, 301, 1, true, 0, 0, true)), "Rena+0's chain admits 302 from 301");
        checkEq(300, admit(in(0, 10, 1, true, 0, 0, true)),
                "the chain's fallback admits 300 from a non-row state");
        checkEq(-1, admit(in(0, 302, 1, true, 0, 0, true)),
                "the real table refuses the 302 fallback (row 302 exists, so the gate decides)");
        checkEq(-1, admit(in(0, 310, 1, true, 0, 0, true)),
                "the real table refuses 300 out of row 310 (cancelThreshold > priority)");

        std::puts("\n== airborne branches (bundle :9-12) ==");
        checkEq(332, admit(in(0, 30, 1, false, 0, 0, true)), "an air dash with phases left admits 332");
        checkEq(320, admit(in(0, 30, 2, false, 0, 0, true)),
                "an air dash past its phases admits the aerial row 320");
        checkEq(320, admit(in(0, 10, 0, false, 0, 0, true)),
                "another airborne source with a permissive gate admits 320");
        checkEq(-1, admit(in(0, 15, 0, false, 0, 0, true)),
                "the real table refuses 320 out of row 15: the gate is data-driven, not structural");
        checkEq(-1, admit(in(0, 15, 0, false, 0, 0, false)),
                "airborne without the flag admits nothing");

        std::puts("\n== the recovered weapon-2 exclusions (bundle :24-31) ==");
        checkEq(-1, admit(in(2, 300, 0, true, 0, 0, true)),
                "weapon 2 may not re-enter the row it holds (300)");
        checkEq(310, admit(in(2, 300, 0, true, 0, -1, true)),
                "weapon 2's back branch is still admitted when its own row differs");
        checkEq(320, admit(in(2, 30, 5, false, 0, 0, true)),
                "weapon 2 has no 332 branch and falls through to 320");

        if (std::getenv("RENA0_ADMISSION_MATRIX")) {
            std::printf("\n== gate matrix (diagnostic, env-gated) ==\n");
            const int states[] = {0, 10, 20, 23, 24, 30, 44, 300, 301, 302, 310, 311, 320, 329,
                                  331, 332, 333, 340, 341, 400, 402};
            for (int st : states)
                std::printf("    grounded state %3d -> %3d   airborne state %3d -> %3d\n", st,
                            admit(in(0, st, 2, true, 0, 0, true)), st,
                            admit(in(0, st, 0, false, 0, 0, true)));
        }
        if (failures) {
            std::fprintf(stderr, "RENA0_ADMISSION_BODY: FAIL (%d of %d checks)\n", failures, checks);
            return 1;
        }
        std::printf("RENA0_ADMISSION_BODY: PASS (%d checks, skips=0)\n", checks);
        return 0;
    } catch (const std::exception& e) {
        std::fprintf(stderr, "FAIL: %s\n", e.what());
        return 1;
    }
}
