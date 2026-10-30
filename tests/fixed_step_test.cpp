#include "battle/fixed_step.h"
#include "input/tick_input.h"
#include <cstdio>
#include <limits>

#define CHECK(condition)                                                                           \
    do                                                                                             \
    {                                                                                              \
        if (!(condition))                                                                          \
        {                                                                                          \
            std::fprintf(stderr, "line %d: %s\n", __LINE__, #condition);                           \
            return 1;                                                                              \
        }                                                                                          \
    } while (0)

// F1-9: after P0-10 the shipped live cadence is the owner's 60 Hz (D15, which supersedes
// D9's 64 Hz), and the scripted/--out capture domain is the same number. These pin the
// decision, not the arithmetic: if either cadence moves alone, one of them fails here.
static_assert(gameplay::FixedStep::tickRate == 60, "Live simulation uses the owner's 60 Hz (D15)");
static_assert(gameplay::FixedStep::scriptedCaptureSeconds == gameplay::FixedStep::seconds,
              "the live step and the scripted capture step are the same number (F1-9)");

int main()
{
    gameplay::FixedStep clock;
    CHECK(clock.advance(0.0) == 0);
    CHECK(clock.advance(-1.0) == 0);
    CHECK(clock.advance(std::numeric_limits<double>::quiet_NaN()) == 0);
    CHECK(clock.advance(std::numeric_limits<double>::infinity()) == 0);
    CHECK(clock.advance(gameplay::FixedStep::seconds / 2.0) == 0);
    CHECK(clock.alpha() > .49f && clock.alpha() < .51f);
    CHECK(clock.advance(gameplay::FixedStep::seconds / 2.0) == 1);
    CHECK(clock.advance(gameplay::FixedStep::seconds * 30.3) == gameplay::FixedStep::maxCatchUp);
    CHECK(clock.alpha() > .29f && clock.alpha() < .31f);
    CHECK(clock.advance(gameplay::FixedStep::seconds / 2.0) == 0);
    CHECK(clock.advance(std::numeric_limits<double>::max()) == gameplay::FixedStep::maxCatchUp);
    CHECK(clock.alpha() >= 0.f && clock.alpha() < 1.f);

    using namespace fnd::input;
    TickInput queued;
    PlayerState sample;
    sample.down[Jump] = true;
    sample.stick_x    = 12345;
    queued.sample(sample);
    queued.sample(sample);
    sample.down[Jump] = false;
    sample.stick_x    = 0;
    queued.sample(sample);
    CHECK(queued.consume().just_pressed[Jump]);
    const auto &released = queued.consume();
    CHECK(released.just_released[Jump] && !released.down[Jump]);
    CHECK(!queued.consume().just_released[Jump]);
    sample.down[Shoot] = true;
    sample.stick_x     = 16000;
    queued.sample(sample);
    const auto &pressed = queued.consume();
    CHECK(pressed.just_pressed[Shoot] && pressed.press_timer[Shoot] == 2);
    CHECK(pressed.stick_x == 16000);
    const auto &held = queued.consume();
    CHECK(held.down[Shoot] && !held.just_pressed[Shoot] && held.press_timer[Shoot] == 1);
    CHECK(queued.consume().press_timer[Shoot] == 0);
    sample = {}; // Focus loss/device removal is a release, including analog intent.
    queued.sample(sample);
    CHECK(queued.consume().just_released[Shoot]);
    CHECK(queued.consume().stick_x == 0);

    std::puts("fixed_step_test: input edges and bounded stalls pass");
    return 0;
}
