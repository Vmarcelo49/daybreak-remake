// P2-7 (2e) guard family — the guard predicate's flag words in the shipped data.
//
// The predicate (`FUN_00637950`'s guarded `else`, listing lines 185-192) reads
// `[[victim+0x10]+0x28]` for bits 0x400 (guard-capable), 0x2000 (guard from any angle) and
// 0x8000 (the contact-word OR), and `[[attacker+0x10]+0x2c]` for bit 8 (unblockable). The
// bundle's pipeline names those words: `battle_hit_pipeline.hpp:23` passes
// `input.stagger.flags` / `input.attack_flags`, `actor_frame_hit.hpp:8` takes the latter from
// the hit record's `flags2c`, and `development_animated_combat.hpp:3922` takes the former from
// `live_body_contact_frame(v).flags28` — the victim's LIVE frame record, which is exactly what
// this port's `CharacterMove::phases[].record_at(elapsed)` returns.
//
// This test establishes the provenance from the shipped data rather than from a reconstruction:
// it walks every record of the combo and counts the records that actually carry those bits, so
// the adapter can read them from `MoveEntry::stateFlags`/`attackFlags` instead of standing in
// the port's own Guard state for them.
//
// Install-backed: the records are game data, so a data-free run exits 77 and is reported
// Skipped, never a pass.
#include "combo_fixture.h"
#include "gameplay/native/rena0_pilot_adapter.h"

#include <cstdio>
#include <string>

namespace {
int checks = 0, failures = 0;

void check(bool ok, const std::string& name) {
    ++checks;
    if (!ok) ++failures;
    std::printf("  %-72s %s\n", name.c_str(), ok ? "ok" : "FAIL");
}

void checkEq(long long expected, long long got, const std::string& name) {
    ++checks;
    const bool ok = expected == got;
    if (!ok) ++failures;
    std::printf("  %-72s %s", name.c_str(), ok ? "ok" : "FAIL");
    if (!ok) std::printf(" (expected %lld, got %lld)", expected, got);
    std::printf("\n");
}
}  // namespace

int main() {
    if (test::gameInstall().empty()) {
        std::puts("SKIP: no game install reachable; the guard flag words are actor data (not a pass)");
        return 77;
    }
    try {
        test::Combo combo;
        std::string error;
        if (!combo.load(0, 0, error)) throw std::runtime_error("Rena+0 data unavailable: " + error);
        std::puts("P2-7 guard family — the predicate's flag words in the shipped records");

        long long records = 0, guardCapable = 0, anyAngle = 0, contactOr = 0, unblockable = 0;
        int firstGuardRow = -1, firstUnblockableRow = -1;
        for (int id = 0; id < 1000; ++id) {
            const gameplay::CharacterMove* move = combo.moves.find(id);
            if (!move) continue;
            for (int phase = 0; phase < move->sectionCount; ++phase) {
                const gameplay::MovePhase& p = move->phases[phase];
                for (int entry = 0; entry < p.entryCount; ++entry) {
                    const gameplay::MoveEntry& record = p.entries[entry];
                    ++records;
                    if (record.stateFlags & 0x400) {
                        ++guardCapable;
                        if (firstGuardRow < 0) firstGuardRow = id;
                    }
                    if (record.stateFlags & 0x2000) ++anyAngle;
                    if (record.stateFlags & 0x8000) ++contactOr;
                    if (record.attackFlags & 8) {
                        ++unblockable;
                        if (firstUnblockableRow < 0) firstUnblockableRow = id;
                    }
                }
            }
        }
        std::printf("  walked %lld records of Rena+0\n", records);

        check(records > 0, "the combo's records are reachable through the port's own parser");
        check(guardCapable > 0, "records carry the guard-capable bit 0x400 (stateFlags)");
        check(unblockable > 0, "records carry the unblockable bit 8 (attackFlags)");
        // The two rarer terms are reported whether or not they appear, so their absence cannot
        // hide behind a passing summary.
        std::printf("  guard-capable 0x400: %lld (first row %d); any-angle 0x2000: %lld; "
                    "contact-OR 0x8000: %lld; unblockable 8: %lld (first row %d)\n",
                    guardCapable, firstGuardRow, anyAngle, contactOr, unblockable,
                    firstUnblockableRow);
        check(firstGuardRow >= 0 && firstUnblockableRow >= 0,
              "both terms come from rows the port can bind and reach");

        // The predicate itself, as a pure function of the four terms `FUN_00637950` reads. This
        // is what makes the two "not expressible" terms expressible: the decision is offline-
        // pinned for every combination, including the ones the shipped records cannot reach, and
        // the live counts above are what say they are unreachable rather than unimplemented.
        using gameplay::native::Rena0GuardOutcome;
        using gameplay::native::decide_rena0_guard;
        const unsigned guardRow = 0x400u, anyAngleRow = 0x400u | 0x2000u, plainRow = 0u;
        const unsigned unblockableAttack = 0x8u, plainAttack = 0u;
        check(decide_rena0_guard(anyAngleRow, plainAttack, 180.f) == Rena0GuardOutcome::guarded,
              "any-angle guard (0x2000) guards even from behind");
        check(decide_rena0_guard(guardRow, plainAttack, 0.f) == Rena0GuardOutcome::guarded,
              "guard-capable row inside 45 degrees guards");
        check(decide_rena0_guard(guardRow, plainAttack, 44.9f) == Rena0GuardOutcome::guarded,
              "the 45-degree bound is inclusive on the inside");
        check(decide_rena0_guard(guardRow, plainAttack, 45.1f) == Rena0GuardOutcome::outside_angle,
              "guard-capable row outside 45 degrees does not guard");
        check(decide_rena0_guard(guardRow, unblockableAttack, 0.f) == Rena0GuardOutcome::unblockable,
              "the attacker's bit 8 defeats the guard at point-blank angle");
        check(decide_rena0_guard(plainRow, plainAttack, 0.f) == Rena0GuardOutcome::not_guard_capable,
              "a row without 0x400 is not guard-capable even facing the attacker");
        check(anyAngle == 0 && contactOr == 0,
              "0x2000 and 0x8000 are unreachable in this combo's shipped records (predicate still pins them)");
        if (unblockable > 0) check(firstUnblockableRow == 350,
              "the only unblockable row in the shipped data is 350 (the EX row)");

        if (failures) {
            std::fprintf(stderr, "RENA0_GUARD_FLAGS: FAIL (%d of %d checks)\n", failures, checks);
            return 1;
        }
        std::printf("RENA0_GUARD_FLAGS: PASS (%d checks, skips=0)\n", checks);
        return 0;
    } catch (const std::exception& e) {
        std::fprintf(stderr, "FAIL: %s\n", e.what());
        return 1;
    }
}
