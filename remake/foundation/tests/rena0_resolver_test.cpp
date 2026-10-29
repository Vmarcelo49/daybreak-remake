// P2-6 (2d) — tests for the isolated Rena+0 resolver.
//
// The row names what to test: model bounds, equipped weapon, phase changes and the
// side-dash regression. It also requires the resolver to be pilot-path only, so this test
// verifies that nothing under src/ includes it (the "unwired" scan) — a future edit that
// wires the resolver into the default path without the owner's approval fails here.
//
// Install-backed: the interesting cases are the real move table's rows, phases and
// priority gate, so a data-free run exits 77 and is reported Skipped, never a pass.
#include "combo_fixture.h"
#include "gameplay/native/rena0_resolver.h"

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace {
namespace native = gameplay::native;

int checks = 0, failures = 0;

void check(bool ok, const std::string& name) {
    ++checks;
    if (!ok) ++failures;
    std::printf("  %-70s %s\n", name.c_str(), ok ? "ok" : "FAIL");
}

void checkEq(int expected, int got, const std::string& name) {
    ++checks;
    const bool ok = expected == got;
    if (!ok) ++failures;
    std::printf("  %-70s %s", name.c_str(), ok ? "ok" : "FAIL");
    if (!ok) std::printf(" (expected %d, got %d)", expected, got);
    std::printf("\n");
}

void checkWeaponReason(const char* expected, const native::Rena0WeaponResolution& r,
                       const std::string& name) {
    const bool ok = std::string(r.reason) == expected;
    check(ok, name + (ok ? "" : std::string(" (expected reason '") + expected + "', got '" +
                                r.reason + "')"));
}

void checkReason(const char* expected, const native::Rena0Resolution& r, const std::string& name) {
    const bool ok = std::string(r.reason) == expected;
    check(ok, name + (ok ? "" : std::string(" (expected reason '") + expected + "', got '" +
                                r.reason + "')"));
}

native::Rena0ResolverView meleeView(int state, int x, int z, bool actionable = true) {
    native::Rena0ResolverView v;
    v.weaponSlot = 0;
    v.actionState = state;
    v.stateEnum = 3;  // Attack: not a locomotion state
    v.grounded = true;
    v.actionable = actionable;
    v.inputX = x;
    v.inputZ = z;
    return v;
}

native::Rena0ResolverView locomotionView(int stateEnum, int x, int z) {
    native::Rena0ResolverView v;
    v.weaponSlot = 0;
    v.actionState = stateEnum;
    v.stateEnum = stateEnum;
    v.phase = 0;
    v.elapsed = 0;
    v.counter = 0;
    v.grounded = true;
    v.actionable = true;
    v.duration = 83;
    v.hold = true;
    v.inputX = x;
    v.inputZ = z;
    return v;
}

// The pilot-path-only guarantee, in the two shapes 2e needs:
//   * the resolver may be included only from the adaptation layer (src/gameplay/native/),
//     never from the default path — the legacy decision code must not see it;
//   * the pilot adapter (the only thing that runs behind --native-actions=rena0) may be
//     included only from the adaptation layer and from the flag site in main.cpp.
// Returns the number of files scanned so a wrong directory cannot pass.
int unwiredScan(const std::string& srcDir, int& resolverHits, int& adapterHits, int& observerHits) {
    int scanned = 0;
    resolverHits = 0;
    adapterHits = 0;
    observerHits = 0;
    for (const auto& entry : std::filesystem::recursive_directory_iterator(srcDir)) {
        if (!entry.is_regular_file()) continue;
        const std::string path = entry.path().string();
        const auto ext = entry.path().extension();
        if (ext != ".h" && ext != ".hpp" && ext != ".cpp" && ext != ".cc") continue;
        ++scanned;
        const bool inNative = path.find("src/gameplay/native/") != std::string::npos;
        const bool isAdapter = path.find("native/rena0_pilot_adapter.h") != std::string::npos;
        const bool isResolver = path.find("native/rena0_resolver.h") != std::string::npos;
        const bool isFlagSite = path.find("src/main.cpp") != std::string::npos;
        std::ifstream in(entry.path());
        std::string line;
        while (std::getline(in, line)) {
            // Only real inclusions count: a comment that names the header is documentation,
            // not wiring, and the guard must not force comments to lie about the path.
            if (line.find("#include") == std::string::npos) continue;
            if (!isResolver && !inNative && line.find("rena0_resolver.h") != std::string::npos) {
                std::fprintf(stderr, "    unwired scan: %s includes the resolver outside native/\n",
                             path.c_str());
                ++resolverHits;
            }
            if (!isAdapter && !inNative && !isFlagSite &&
                line.find("rena0_pilot_adapter.h") != std::string::npos) {
                std::fprintf(stderr, "    unwired scan: %s includes the pilot adapter outside native/ "
                                     "and main.cpp\n", path.c_str());
                ++adapterHits;
            }
            // The observation-only recovered bodies must stay out of the default path too:
            // they are evidence and pilot inputs, never decision code for the shipped combos.
            if (!inNative && (line.find("rena0_locomotion_observation.h") != std::string::npos ||
                              line.find("rena0_ground_shot_observation.h") != std::string::npos ||
                              line.find("rena0_guard_observation.h") != std::string::npos ||
                              line.find("rena0_charge_observation.h") != std::string::npos ||
                              line.find("rena0_mode_gauges.h") != std::string::npos ||
                              line.find("rena0_steering.h") != std::string::npos)) {
                std::fprintf(stderr, "    unwired scan: %s includes a recovered observation body "
                                     "outside native/\n", path.c_str());
                ++observerHits;
            }
        }
    }
    return scanned;
}
}  // namespace

int main(int argc, char** argv) {
    const std::string srcDir = argc > 1 ? argv[1] : "src";
    if (test::gameInstall().empty()) {
        std::puts("SKIP: no game install reachable; the resolver binds real rows and phases (not a pass)");
        return 77;
    }
    try {
        test::Combo combo;
        std::string error;
        if (!combo.load(0, 0, error)) throw std::runtime_error("Rena+0 data unavailable: " + error);
        const gameplay::CharacterMoves& moves = combo.moves;
        std::puts("P2-6 resolver tests — explicit move/phase/set and fallback reasons");

        std::puts("\n== model bounds ==");
        {
            const int idleSet = moves.first_set_index(0);
            const auto r = native::resolve_rena0_set(0, 0, &moves, &combo.model);
            checkEq(idleSet, r.setId, "row 0 resolves to the table's phase-0 set");
            checkReason("set-resolved", r, "a resolvable row reports set-resolved");
            check(r.source == native::Rena0BindingSource::Fallback,
                  "the bare set resolver claims no source");

            xm::Model small = combo.model;  // a rig one anim short of the row's set
            small.anims.resize(static_cast<std::size_t>(idleSet));
            const auto clipped = native::resolve_rena0_set(0, 0, &moves, &small);
            checkEq(-1, clipped.setId, "a set at the rig's edge resolves to nothing");
            checkReason("set-out-of-model-bounds", clipped, "the bounds failure is named");

            checkReason("no-move-row", native::resolve_rena0_set(-1, 0, &moves, &combo.model),
                        "no row is reported as no-move-row");
            checkReason("no-move-table", native::resolve_rena0_set(0, 0, nullptr, &combo.model),
                        "no table is reported as no-move-table");
            checkReason("move-row-absent", native::resolve_rena0_set(9999, 0, &moves, &combo.model),
                        "an id the table lacks is reported as move-row-absent");
            checkReason("phase-set-unbound", native::resolve_rena0_set(0, 7, &moves, &combo.model),
                        "a phase past the row's sections is reported as phase-set-unbound");
            checkEq(idleSet, native::resolve_rena0_set(0, 0, &moves, nullptr).setId,
                    "without a model the row still resolves (bounds checking is the model's job)");
        }

        std::puts("\n== equipped weapon ==");
        {
            const auto bound = native::resolve_rena0_weapon(0, &combo.weapon);
            checkEq(combo.weapon.id, bound.weaponId, "a bound weapon reports the definition's id");
            checkWeaponReason("weapon-bound", bound, "a bound weapon says so");
            checkWeaponReason("weapon-unbound", native::resolve_rena0_weapon(-1, &combo.weapon),
                        "an unbound slot is a named failure, not a zero");
            checkWeaponReason("weapon-data-absent", native::resolve_rena0_weapon(0, nullptr),
                        "a missing definition is a named failure");
        }

        std::puts("\n== phase changes ==");
        {
            const gameplay::CharacterMove* dash = moves.find(20);
            if (!dash) {
                check(false, "the real table has the dash row 20 this case needs");
            } else {
                std::vector<int> sets;
                for (int phase = 0; phase < dash->sectionCount; ++phase) {
                    const auto r = native::resolve_rena0_set(20, phase, &moves, &combo.model);
                    checkEq(dash->phase_set_index(phase), r.setId,
                            "row 20 phase " + std::to_string(phase) + " resolves its own set");
                    sets.push_back(r.setId);
                }
                check(dash->sectionCount >= 2 && sets.front() != sets.back(),
                      "the phase sets differ across the row (a real phase change, not a constant)");
                checkReason("phase-set-unbound",
                            native::resolve_rena0_set(20, dash->sectionCount, &moves, &combo.model),
                            "one phase past the row is a named failure");
            }
        }

        std::puts("\n== side-dash regression (the row's named regression) ==");
        {
            const auto sideBack = native::resolve_rena0_admission(meleeView(23, 0, -1), &moves, &combo.model);
            checkEq(330, sideBack.moveId, "side dash with back held admits 330");
            check(sideBack.source == native::Rena0BindingSource::RecoveredAdmission,
                  "the side-dash row is attributed to the recovered admission");
            check(sideBack.setId >= 0, "the side-dash row resolves an animation set");
            const auto sideNeutral = native::resolve_rena0_admission(meleeView(23, 0, 0), &moves, &combo.model);
            checkEq(331, sideNeutral.moveId, "side dash without back admits 331");
            checkEq(330, native::resolve_rena0_admission(meleeView(24, 0, -1), &moves, &combo.model).moveId,
                    "the other side dash admits 330 with back held");
            checkEq(331, native::resolve_rena0_admission(meleeView(24, 0, 0), &moves, &combo.model).moveId,
                    "the other side dash admits 331 without back");
            checkEq(330, native::resolve_rena0_admission(meleeView(20, 0, 0), &moves, &combo.model).moveId,
                    "the forward dash still admits 330 (the branch did not collapse)");
            checkEq(331, native::resolve_rena0_admission(meleeView(20, 1, 0), &moves, &combo.model).moveId,
                    "the forward dash with a lateral input admits 331");
            const auto refused = native::resolve_rena0_admission(meleeView(302, 0, 0, false), &moves, &combo.model);
            checkEq(-1, refused.moveId, "without the actionable window the admission refuses");
            checkReason("admission-refused", refused, "the refusal is named");
        }

        std::puts("\n== locomotion resolution ==");
        {
            const auto idle = native::resolve_rena0_locomotion(locomotionView(0, 0, 0), &moves, &combo.model);
            checkEq(0, idle.moveId, "idle resolves the idle row");
            checkEq(moves.first_set_index(0), idle.setId, "idle resolves the idle row's set");
            check(idle.source == native::Rena0BindingSource::LocomotionBody,
                  "the idle resolution is attributed to the locomotion body");
            const auto walk = native::resolve_rena0_locomotion(locomotionView(1, 0, -1), &moves, &combo.model);
            checkEq(10, walk.moveId, "walk resolves the walk row");
            checkEq(moves.first_set_index(10), walk.setId, "walk resolves the walk row's set");

            // The stop word suppresses the body for that update (FUN_0043ffc0:28), so the
            // incoming row stands rather than being replaced — the resolver must report the
            // walk row it was in, not invent an idle transition.
            auto stopped = locomotionView(1, 0, -1);
            stopped.stop = 256;
            const auto suppressed = native::resolve_rena0_locomotion(stopped, &moves, &combo.model);
            checkEq(10, suppressed.moveId, "a stop word keeps the incoming row (the body is suppressed)");
            checkEq(moves.first_set_index(10), suppressed.setId, "the suppressed tick keeps its set");

            auto airborne = locomotionView(0, 0, 0);
            airborne.grounded = false;
            const auto air = native::resolve_rena0_locomotion(airborne, &moves, &combo.model);
            checkEq(-1, air.moveId, "the airborne proposal resolves no row");
            checkReason("airborne-set-unresolved", air,
                        "the airborne clip dependency is named, not invented");

            const auto dashState = native::resolve_rena0_locomotion(locomotionView(20, 0, 0), &moves, &combo.model);
            checkEq(-1, dashState.moveId, "a non-locomotion state resolves no row");
            checkReason("not-a-locomotion-state", dashState, "the out-of-domain state is named");
        }

        std::puts("\n== the recovered boosted arm is named, not guessed ==");
        {
            auto chaining = meleeView(300, 0, 0);
            chaining.armedSpecial = true;
            const auto r = native::resolve_rena0_admission(chaining, &moves, &combo.model);
            check(r.boostedGap, "an armed special inside the window flags the unmodelled boost arm");
            checkEq(301, r.moveId, "the un-boosted chain row is still reported");
            auto stuck = meleeView(310, 0, 0);
            stuck.armedSpecial = true;
            const auto refused = native::resolve_rena0_admission(stuck, &moves, &combo.model);
            checkEq(-1, refused.moveId, "an armed special changes nothing the port can model");
            checkReason("armed-special-unrecovered", refused, "the gap is the reported reason");
        }

        std::puts("\n== pilot-path only (the unwired guarantee) ==");
        {
            int resolverHits = 0, adapterHits = 0, observerHits = 0;
            const int scanned = unwiredScan(srcDir, resolverHits, adapterHits, observerHits);
            check(scanned > 50, "the unwired scan actually walked the source tree (" +
                                    std::to_string(scanned) + " files)");
            checkEq(0, resolverHits,
                     "the resolver is included only from src/gameplay/native/ (never the default path)");
            checkEq(0, adapterHits,
                     "the pilot adapter is included only from native/ and the flag site in main.cpp");
            checkEq(0, observerHits,
                     "the recovered observation bodies are included only from native/");
        }

        if (failures) {
            std::fprintf(stderr, "RENA0_RESOLVER: FAIL (%d of %d checks)\n", failures, checks);
            return 1;
        }
        std::printf("RENA0_RESOLVER: PASS (%d checks, skips=0)\n", checks);
        return 0;
    } catch (const std::exception& e) {
        std::fprintf(stderr, "FAIL: %s\n", e.what());
        return 1;
    }
}
