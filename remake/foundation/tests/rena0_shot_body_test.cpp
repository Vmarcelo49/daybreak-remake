// P2-7 (2e) shot family — offline event checks for the recovered ground-shot body.
//
// The recovered body's interesting content is its ORDERED event list: which request the
// original publishes on which frame, and in which order. These cases pin that order from
// scalars alone (no install, no Match, no host), so a change in the adapted body is caught
// before anything is wired to the pilot.
//
// Expectations come from the bundle's `battle_rena_ground_shot.hpp` (weapon 0 and 1 branches);
// the frame numbers are the body's own `frame` values, not port ticks.
#include "gameplay/native/rena0_ground_shot_observation.h"

#include <cstdio>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
namespace native = gameplay::native;

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

native::Rena0GroundShotInput input(bool complete = false, bool grounded = true,
                                   bool special = false, int rounds = 6, float elevation = 0.f) {
    native::Rena0GroundShotInput in;
    in.complete = complete;
    in.grounded = grounded;
    in.special = special;
    in.rounds = rounds;
    in.elevation = elevation;
    in.heading = 0.f;
    in.position = {0.f, 0.f, 0.f};
    return in;
}

std::string kinds(const native::Rena0GroundShotEffects& fx) {
    static const char* names[] = {"activate",  "melee_statistics", "shot_statistics",
                                  "model",     "sound",            "voice",
                                  "attachment", "world_projectile", "clear_contact",
                                  "capacity",  "strike"};
    std::string out;
    for (const auto& e : fx.events) {
        if (!out.empty()) out += ",";
        out += names[static_cast<int>(e.kind)];
        // sound/voice/attachment carry an id, and weapon 1's strike request carries its live
        // flag as the id, so both are printed.
        // Every kind that carries a meaningful id prints it: sound/voice/attachment ids,
        // weapon 1's strike live flag, the model request's slot (-1 = unbind), and the
        // contact-capacity value.
        switch (e.kind) {
            case native::Rena0ShotEventKind::sound:
            case native::Rena0ShotEventKind::voice:
            case native::Rena0ShotEventKind::attachment_projectile:
            case native::Rena0ShotEventKind::strike:
            case native::Rena0ShotEventKind::model:
            case native::Rena0ShotEventKind::contact_capacity:
                out += ":" + std::to_string(e.id);
                break;
            default:
                break;
        }
    }
    return out;
}

int countKind(const native::Rena0GroundShotEffects& fx, native::Rena0ShotEventKind kind) {
    int n = 0;
    for (const auto& e : fx.events)
        if (e.kind == kind) ++n;
    return n;
}
}  // namespace

int main() {
    std::puts("P2-7 shot family — recovered ground-shot body, offline event checks");
    std::puts("\n== weapon 0 (Rena+0, the pilot combo) ==");
    {
        native::Rena0GroundShotMotion s;
        s.speed = 5.f;
        s.offset = 100.f;
        const auto fx = native::advance_rena0_ground_shot(0, s, input());
        checkEq(1, countKind(fx, native::Rena0ShotEventKind::activate), "frame 0 publishes activate");
        checkEq(0, countKind(fx, native::Rena0ShotEventKind::model), "no model request before frame 12");
        checkEq(1, (int)fx.events.size(), "frame 0 publishes exactly one event");
        checkEq(80, (long long)s.offset, "the offset approaches its target by 20 per frame");
        check(fx.next_state == -1, "a live shot proposes no state change");
    }
    {
        native::Rena0GroundShotMotion s;
        s.frame = 11;
        const auto fx = native::advance_rena0_ground_shot(0, s, input());
        checkEq(0, (int)fx.events.size(), "frame 11 publishes nothing");
        checkEq(0, countKind(fx, native::Rena0ShotEventKind::model), "frame 11 is still before the model window");
    }
    {
        native::Rena0GroundShotMotion s;
        s.frame = 12;
        s.phase = 0;
        s.speed = 3.f;
        const auto fx = native::advance_rena0_ground_shot(0, s, input(false, true, false, 6, 45.f));
        check(kinds(fx) == "model:-1,model:-1,sound:70,shot_statistics,voice:27,attachment:0",
              "frame 12 publishes model, sound 70, statistics, voice 27, attachment 0 in order — got " +
                  kinds(fx));
        checkEq(30, s.pitch, "the pitch clamps the elevation to +30");
        checkEq(2, countKind(fx, native::Rena0ShotEventKind::model), "both model slots are requested");
        checkEq(25, (long long)(s.speed * 10.f), "phase 0 decays the speed by 0.5 per frame (3.0 -> 2.5)");
    }
    {
        native::Rena0GroundShotMotion s;
        s.frame = 12;
        s.phase = 0;
        const auto fx = native::advance_rena0_ground_shot(0, s, input(false, true, true, 6, -45.f));
        checkEq(6, [&] {
            for (const auto& e : fx.events)
                if (e.kind == native::Rena0ShotEventKind::attachment_projectile) return e.id;
            return -1;
        }(), "an armed special requests bullet 6");
        checkEq(-30, s.pitch, "the pitch clamps the elevation to -30");
    }
    {
        native::Rena0GroundShotMotion s;
        s.frame = 12;
        const auto fx = native::advance_rena0_ground_shot(0, s, input(false, true, false, 1));
        check(kinds(fx).find("voice:30") != std::string::npos,
              "the last round selects voice 30 instead of 27 — got " + kinds(fx));
        bool predicate = false;
        for (const auto& e : fx.events)
            if (e.kind == native::Rena0ShotEventKind::voice) {
                predicate = e.voice_current_rounds;
                checkEq(27, e.voice_other, "the voice event carries the original's other id");
            }
        check(predicate, "the voice event marks the host-resolved round predicate");
    }
    {
        native::Rena0GroundShotMotion s;
        s.frame = 20;
        const auto fx = native::advance_rena0_ground_shot(0, s, input());
        check(kinds(fx) == "model:-1,model:-1", "past frame 12 only the model requests repeat — got " + kinds(fx));
    }
    {
        native::Rena0GroundShotMotion s;
        const auto fx = native::advance_rena0_ground_shot(0, s, input(true));
        checkEq(0, fx.next_state, "a completed shot proposes state 0");
        checkEq(0, (int)fx.events.size(), "a completed shot publishes nothing");
    }
    {
        native::Rena0GroundShotMotion s;
        const auto fx = native::advance_rena0_ground_shot(0, s, input(false, false));
        checkEq(43, fx.next_state, "losing the ground proposes state 43");
        checkEq(5, (long long)(s.gravity * 10), "losing the ground sets gravity 0.5");
        checkEq(0, (int)fx.events.size(), "the airborne proposal publishes nothing");
    }

    std::puts("\n== weapon 1 ==");
    {
        native::Rena0GroundShotMotion s;
        s.offset = 100.f;
        const auto fx = native::advance_rena0_ground_shot(1, s, input());
        check(kinds(fx) == "activate,melee_statistics,clear_contact,capacity:1,strike:0",
              "weapon 1's first frame publishes activate, melee statistics, clear_contact, capacity — got " +
                  kinds(fx));
        checkEq(65, (long long)s.offset, "weapon 1 approaches with 20 then 15 on its first frame");
        checkEq(0, (long long)(s.movement * 10), "weapon 1 zeroes the movement channel");
    }
    {
        native::Rena0GroundShotMotion s;
        s.frame = 7;
        native::advance_rena0_ground_shot(1, s, input());
        checkEq(45, (long long)s.speed, "weapon 1 sets speed 45 at frame 7");
    }
    {
        native::Rena0GroundShotMotion s;
        s.frame = 15;
        const auto fx = native::advance_rena0_ground_shot(1, s, input());
        check(kinds(fx) == "sound:67,voice:29,strike:1",
              "weapon 1's frame 15 publishes sound 67, voice 29 and the strike — got " + kinds(fx));
        checkEq(0, (long long)s.speed, "weapon 1 zeroes the speed at frame 15");
    }
    {
        native::Rena0GroundShotMotion s;
        s.frame = 18;
        const auto fx = native::advance_rena0_ground_shot(1, s, input());
        check(kinds(fx) == "sound:77,shot_statistics,attachment:6,strike:1",
              "weapon 1's frame 18 publishes sound 77, statistics, one attachment, strike — got " + kinds(fx));
    }
    {
        native::Rena0GroundShotMotion s;
        s.frame = 18;
        const auto fx = native::advance_rena0_ground_shot(1, s, input(false, true, true));
        checkEq(2, countKind(fx, native::Rena0ShotEventKind::attachment_projectile),
                "an armed special requests two attachments for one statistics call");
        checkEq(0, (int)fx.events[2].id, "the first special attachment is bullet 0");
        checkEq(9, (int)fx.events[3].id, "the second special attachment is bullet 9");
    }
    {
        native::Rena0GroundShotMotion s;
        s.frame = 8;
        const auto fx = native::advance_rena0_ground_shot(1, s, input());
        checkEq(1, (int)fx.events.back().id, "the strike request is live from frame 8");
        s.frame = 19;
        const auto fx2 = native::advance_rena0_ground_shot(1, s, input());
        checkEq(0, (int)fx2.events.back().id, "the strike request is off after frame 18");
    }

    std::puts("\n== the unadapted branch fails loudly ==");
    {
        native::Rena0GroundShotMotion s;
        bool threw = false;
        std::string what;
        try {
            native::advance_rena0_ground_shot(2, s, input());
        } catch (const std::invalid_argument& e) {
            threw = true;
            what = e.what();
        }
        check(threw, "weapon 2 throws instead of returning an empty result");
        check(what.find("cosine") != std::string::npos,
              "the refusal names the missing legacy cosine table");
    }

    if (failures) {
        std::fprintf(stderr, "RENA0_SHOT_BODY: FAIL (%d of %d checks)\n", failures, checks);
        return 1;
    }
    std::printf("RENA0_SHOT_BODY: PASS (%d checks, skips=0)\n", checks);
    return 0;
}
