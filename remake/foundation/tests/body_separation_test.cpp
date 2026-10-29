// Body separation (FUN_006394c0): the recovered push-apart that keeps two bodies from standing
// inside each other. Two layers are checked, because either can regress alone:
//   * the formula (`body_separation`), against the listing's constants and degenerate cases;
//   * the wiring (Match::separate_bodies), which must actually move both fighters once per
//     frame and leave pairs alone when the vertical gate is closed.

#include <cmath>
#include <cstdio>
#include <vector>

#include "gameplay/body_separation.h"
#include "gameplay/fighter.h"
#include "gameplay/match.h"

namespace {

int g_checks = 0;
int g_failed = 0;

void check(bool ok, const char* what) {
    ++g_checks;
    if (ok) return;
    ++g_failed;
    std::printf("FAIL: %s\n", what);
}

void checkNear(float want, float got, float eps, const char* what) {
    ++g_checks;
    if (std::fabs(want - got) <= eps) return;
    ++g_failed;
    std::printf("FAIL: %s (want %.4f got %.4f)\n", what, want, got);
}

constexpr float kDt = 1.f / 60.f;

}  // namespace

int main() {
    using namespace gameplay;

    // --- the formula, against the listing (section by section) ---
    {
        // 20 units apart -> each takes half of the 40-unit gap, so the pair ends exactly at 60.
        const BodySeparation s = body_separation({0.f, 0.f, 0.f}, {0.f, 0.f, 20.f});
        check(s.active, "a 20-unit gap is a separation case");
        checkNear(0.f, s.push.x, 1e-4f, "a z-only gap pushes along z, not x");
        checkNear(-20.f, s.push.z, 1e-4f, "first body takes half the remaining overlap");

        // Already touching the radius -> no push, and that includes the boundary itself.
        check(!body_separation({0.f, 0.f, 0.f}, {0.f, 0.f, 60.f}).active,
              "exactly 60 apart is outside the window (the listing tests dist < 60)");
        check(body_separation({0.f, 0.f, 0.f}, {0.f, 0.f, 59.5f}).active,
              "just inside 60 is still a separation case");
        checkNear(-0.25f, body_separation({0, 0, 0}, {0, 0, 59.5f}).push.z, 1e-4f,
                  "(60 - 59.5) / 2 is the half-push");

        // The vertical delta is a GATE, never a direction: the push stays horizontal.
        const BodySeparation sloped = body_separation({0.f, 0.f, 0.f}, {0.f, 55.f, 20.f});
        check(sloped.active, "a 55-unit height delta is inside the vertical gate");
        checkNear(0.f, sloped.push.y, 1e-6f, "the push never moves a body vertically");
        check(!body_separation({0.f, 0.f, 0.f}, {0.f, 60.f, 0.f}).active,
              "exactly 60 of height closes the gate");
        check(!body_separation({0.f, 0.f, 0.f}, {0.f, 60.5f, 20.f}).active,
              "height above 60 closes the gate even when the bodies overlap in XZ");

        // Degenerate overlap: the listing forces dx = 1 and distance = 1, so the pair separates
        // to 59 rather than 60. Pinned because "fix" it to 60 would be a silent behaviour change.
        const BodySeparation same = body_separation({5.f, 0.f, 5.f}, {5.f, 0.f, 5.f});
        check(same.active, "two bodies on the same point still separate");
        checkNear(29.5f, same.push.x, 1e-4f, "the degenerate case moves each body 29.5");
        checkNear(0.f, same.push.z, 1e-4f, "and along the forced x direction");
    }

    // --- the wiring: a real Match must move both bodies on its own ---
    {
        MatchConfig config;
        config.fighterCount = 2;
        config.side[0] = 0;
        config.side[1] = 1;
        config.spawn[0] = glm::vec3(0.f, 0.f, 0.f);
        config.spawn[1] = glm::vec3(0.f, 0.f, 20.f);
        // No models, controllers or weapon tables: this layer only needs positions, and the
        // separation must work in a match that has no animation at all.
        const xm::Model* models[kMatchFighterCount] = {nullptr, nullptr, nullptr, nullptr};
        xm::Controller* controllers[kMatchFighterCount] = {nullptr, nullptr, nullptr, nullptr};
        Match match;
        match.reset(config, models, controllers, nullptr, nullptr);
        match.set_body_separation(true);   // the mechanic is opt-in (V3-45)

        const glm::vec3 firstStart = match.fighter(0).position();
        const glm::vec3 secondStart = match.fighter(1).position();
        match.step(nullptr, nullptr, kDt);

        const glm::vec3 delta = match.fighter(0).position() - match.fighter(1).position();
        const float distance = std::sqrt(delta.x * delta.x + delta.z * delta.z);
        checkNear(60.f, distance, 0.5f, "one frame leaves the pair at the 60-unit separation");

        // Both bodies move, and each moves about half: the listing pushes both halves, so a
        // one-sided implementation (which would also end at 60) fails here.
        const float firstMoved = glm::length(match.fighter(0).position() - firstStart);
        const float secondMoved = glm::length(match.fighter(1).position() - secondStart);
        checkNear(firstMoved, secondMoved, 0.5f, "both bodies take the same share of the push");
        check(firstMoved > 15.f && firstMoved < 25.f, "each body moves about half the overlap");
    }

    // --- the vertical gate, through the match ---
    {
        MatchConfig config;
        config.fighterCount = 2;
        config.side[0] = 0;
        config.side[1] = 1;
        config.spawn[0] = glm::vec3(0.f, 0.f, 0.f);
        config.spawn[1] = glm::vec3(0.f, 70.f, 20.f);   // overlapping in XZ, but 70 up
        const xm::Model* models[kMatchFighterCount] = {nullptr, nullptr, nullptr, nullptr};
        xm::Controller* controllers[kMatchFighterCount] = {nullptr, nullptr, nullptr, nullptr};
        Match match;
        match.reset(config, models, controllers, nullptr, nullptr);
        match.set_body_separation(true);
        match.step(nullptr, nullptr, kDt);
        const glm::vec3 delta = match.fighter(0).position() - match.fighter(1).position();
        const float distance = std::sqrt(delta.x * delta.x + delta.z * delta.z);
        checkNear(20.f, distance, 0.5f,
                  "a body more than 60 units up is not pushed, even when the XZ gap is small");
    }

    // --- a far pair is left alone ---
    {
        MatchConfig config;
        config.fighterCount = 2;
        config.side[0] = 0;
        config.side[1] = 1;
        config.spawn[0] = glm::vec3(0.f, 0.f, 0.f);
        config.spawn[1] = glm::vec3(0.f, 0.f, 600.f);
        const xm::Model* models[kMatchFighterCount] = {nullptr, nullptr, nullptr, nullptr};
        xm::Controller* controllers[kMatchFighterCount] = {nullptr, nullptr, nullptr, nullptr};
        Match match;
        match.reset(config, models, controllers, nullptr, nullptr);
        match.set_body_separation(true);
        const glm::vec3 before = match.fighter(1).position();
        match.step(nullptr, nullptr, kDt);
        const glm::vec3 delta = match.fighter(1).position() - before;
        checkNear(0.f, std::sqrt(delta.x * delta.x + delta.z * delta.z), 1e-3f,
                  "a pair 600 units apart is not pushed at all");
    }

    std::printf("BODY_SEPARATION: %d checks, %d failed\n", g_checks, g_failed);
    return g_failed == 0 ? 0 : 1;
}
