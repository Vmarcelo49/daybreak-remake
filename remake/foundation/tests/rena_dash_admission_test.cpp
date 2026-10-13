#include "gameplay/dash_history.h"
#include "gameplay/rena_dash_admission.h"

#include <cstdio>
#include <cstdlib>

namespace {
int checks = 0;
int failures = 0;

void expect(bool condition, const char* label) {
    ++checks;
    if (!condition) ++failures;
    std::printf("  %-62s %s\n", label, condition ? "ok" : "FAIL");
}

void history_cases() {
    std::puts("\n== Rena+0/+1/+2 15-sample directional history ==");
    gameplay::DashHistory history;
    unsigned command = 0;
    for (unsigned i = 0; i < gameplay::DashHistory::kSamples; ++i)
        command = history.push(0, 0);
    expect(command == 0, "fifteen neutral samples have no dash command");
    for (int i = 0; i < 2; ++i) command = history.push(0, -1);
    command = history.push(0, 0);
    command = history.push(0, 0);
    command = history.push(0, -1);
    expect(command == 1, "forward / neutral / forward selects command 1");
    for (unsigned i = 0; i < gameplay::DashHistory::kSamples; ++i)
        command = history.push(0, 0);
    expect(command == 0, "expired direction samples leave the history window");

    history.reset();
    for (int i = 0; i < 2; ++i) history.push(-1, 0);
    history.push(0, 0);
    history.push(0, 0);
    command = history.push(-1, 0);
    expect(command == 3, "left / neutral / left selects command 3");

    history.reset();
    for (int i = 0; i < 2; ++i) history.push(0, 1);
    history.push(0, 0);
    history.push(0, 0);
    command = history.push(0, 1);
    expect(command == 2, "back / neutral / back selects command 2");

    history.reset();
    for (int i = 0; i < 2; ++i) history.push(1, 0);
    history.push(0, 0);
    history.push(0, 0);
    command = history.push(1, 0);
    expect(command == 4, "right / neutral / right selects command 4");

    history.reset();
    history.push(0, 1); // back pair is found by command 2's later scan
    history.push(0, 0);
    history.push(0, 1);
    history.push(0, -1); // newer forward pair is also found by command 1
    history.push(0, 0);
    expect(history.push(0, -1) == 2,
           "the command-2 scan overwrites an earlier command-1 match");
}

gameplay::RenaDashRows all_rows() {
    gameplay::RenaDashRows rows;
    rows.firstPriority = {10, 10, 10, 10};
    rows.present = {true, true, true, true};
    return rows;
}

void admission_cases() {
    std::puts("\n== Rena+0/+1/+2 dash admission source predicates ==");
    const auto rows = all_rows();
    for (int weapon = 0; weapon < 3; ++weapon) {
        const char* combo = weapon == 0 ? "Rena+0" : weapon == 1 ? "Rena+1" : "Rena+2";
        for (unsigned command = 1; command <= 4; ++command) {
            const gameplay::RenaDashInput ground{weapon, 0, command, true, 1000, true, 0, 0};
            const auto result = gameplay::rena_dash_admission(ground, rows);
            const int expected = gameplay::rena_dash_ground_candidate(command);
            char label[128];
            std::snprintf(label, sizeof(label), "%s ground command %u selects row %d",
                          combo, command, expected);
            expect(result.state == expected && !result.airborne, label);

            auto air = ground;
            air.grounded = false;
            const auto aerial = gameplay::rena_dash_admission(air, rows);
            std::snprintf(label, sizeof(label), "%s airborne command %u selects row 30",
                          combo, command);
            expect(aerial.state == 30 && aerial.airborne, label);
        }
    }

    auto input = gameplay::RenaDashInput{0, 310, 2, true, 1000, true, 1, 100};
    auto result = gameplay::rena_dash_admission(input, rows);
    expect(result.state == 28, "Rena+0 grounded back-dash contact selects row 28 before 27 gate");
    input.weaponSlot = 1;
    result = gameplay::rena_dash_admission(input, rows);
    expect(result.state == 28, "Rena+1 grounded back-dash contact selects row 28");
    input.weaponSlot = 2;
    result = gameplay::rena_dash_admission(input, rows);
    expect(result.state == 27, "Rena+2 has no special row-28 contact branch");
    input.weaponSlot = 0;
    input.currentState = 320;
    result = gameplay::rena_dash_admission(input, rows);
    expect(result.state == 27, "Rena+0 state 320 excludes the special row-28 branch");

    input.weaponSlot = 0;
    input.grounded = false;
    input.currentState = 310;
    input.currentCancelThreshold = 100;
    input.contact = 1;
    result = gameplay::rena_dash_admission(input, rows);
    expect(result.state == 30 && result.airborne,
           "Rena+0 air back-contact exception selects row 30");

    input.command = 1;
    input.currentState = 10;
    input.grounded = true;
    input.currentCancelThreshold = 11;
    input.contact = 0;
    result = gameplay::rena_dash_admission(input, rows);
    expect(result.state == -1, "Rena+0 candidate priority gate rejects threshold 11 over priority 10");
    input.currentCancelThreshold = 10;
    result = gameplay::rena_dash_admission(input, rows);
    expect(result.state == 20, "Rena+0 candidate priority gate admits equality");
    input.gauge = 0;
    result = gameplay::rena_dash_admission(input, rows);
    expect(result.state == -1, "Rena+0 empty +0x834 action gauge rejects dash");
    input.gauge = 1000;
    input.normalFlag = false;
    result = gameplay::rena_dash_admission(input, rows);
    expect(result.state == -1, "Rena+0 missing NN flags28 0x100 rejects dash");
    input.normalFlag = true;
    auto distinct = rows;
    distinct.firstPriority = {10, 20, 30, 40};
    input.command = 2;
    input.currentCancelThreshold = 25;
    result = gameplay::rena_dash_admission(input, distinct);
    expect(result.state == -1, "Rena+0 command 2 uses candidate row 27 priority");
    input.command = 4;
    input.currentCancelThreshold = 35;
    result = gameplay::rena_dash_admission(input, distinct);
    expect(result.state == 23, "Rena+0 command 4 uses candidate row 23 priority");
    distinct.present = {true, true, true, false};
    result = gameplay::rena_dash_admission(input, distinct);
    expect(result.state == -1, "Rena+0 command 4 checks row-23 presence");
    distinct.present = {true, false, true, true};
    input.command = 2;
    input.currentState = 10;
    input.currentCancelThreshold = 10;
    input.contact = 0;
    result = gameplay::rena_dash_admission(input, distinct);
    expect(result.state == -1, "Rena+0 command 2 rejects absent row 27");

    input.command = 1;
    input.currentCancelThreshold = 10;
    auto missing = rows;
    missing.present[0] = false;
    result = gameplay::rena_dash_admission(input, missing);
    expect(result.state == -1, "Rena+0 missing candidate row rejects dash");
    input.command = 2;
    input.currentState = 310;
    input.currentCancelThreshold = 100;
    input.contact = 1;
    input.grounded = false;
    input.weaponSlot = 1;
    result = gameplay::rena_dash_admission(input, rows);
    expect(result.state == -1, "Rena+1 back-contact exception remains absent off ground");
}
} // namespace

int main() {
    history_cases();
    admission_cases();
    std::printf("\n%d checks, %d failed\n", checks, failures);
    std::printf("RENA_DASH_ADMISSION: %s\n", failures ? "FAIL" : "ok");
    return failures ? EXIT_FAILURE : EXIT_SUCCESS;
}
