#include "gameplay/arena_camera.h"
#include "gameplay/fixed_step.h"
#include "gameplay/match.h"
#include "input/tick_input.h"
#include <cstdio>
#include <limits>
#include "synthetic_combo.h"

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

struct Run
{
    gameplay::Match match;
    // MatchConfig holds POINTERS to the combo, and Match copies the config, so the
    // fixture has to outlive every step the run makes (AGENTS rule 7).
    test::synthetic::Combo combo;
    gameplay::ArenaCamera camera;
    gameplay::CameraTarget targets[4];
    int ticks = 0, shots = 0, respawns = 0;
};

static void replay(Run &run, int renderHz, int fighterCount)
{
    gameplay::MatchConfig config;
    config.fighterCount = fighterCount;
    config.spawn[1]     = glm::vec3(500, 0, 0);
    config.spawn[2]     = glm::vec3(600, 0, 300);
    config.spawn[3]     = glm::vec3(600, 0, -300);
    if (fighterCount == 4)
    {
        config.side[0] = config.side[1] = 0;
        config.side[2] = config.side[3] = 1;
    }
    // AGENTS rule 7: the replay drives a battle, so every fighter carries a combo.
    run.combo.bind(config, fighterCount);
    const xm::Model *models[4]    = {};
    xm::Controller *animations[4] = {};
    run.match.reset(config, models, animations, nullptr, nullptr);
    run.match.economy().setLogFile(nullptr);
    std::vector<gameplay::CameraTarget *> targets;
    for (int i = 0; i < fighterCount; ++i)
        targets.push_back(&run.targets[i]);
    run.camera.set_target_pool(targets);
    run.camera.set_active_target(0);
    gameplay::FixedStep clock;
    fnd::input::PlayerState input;
    for (int render = 0; render < renderHz * 10; ++render)
    {
        const int steps = clock.advance(1.0 / renderHz);
        for (int step = 0; step < steps; ++step)
        {
            ++run.ticks;
            for (bool &down : input.down)
                down = false;
            input.down[fnd::input::Right]   = run.ticks >= 70 && run.ticks < 110;
            input.down[fnd::input::Jump]    = run.ticks >= 120 && run.ticks < 140;
            input.down[fnd::input::Shoot]   = run.ticks >= 150 && run.ticks < 170;
            input.down[fnd::input::AttackA] = run.ticks == 200;
            fnd::input::compute_edges(input);
            // Exercise the KO clock across render grouping as well as movement. A
            // clean KO (damage == the HP pool) keeps the recovered overkill term at 0;
            // a 1000-point hit would be a tenfold overkill and legitimately bursts the
            // balloon, because FUN_00639160's -HP/1000 term is uncapped.
            if (run.ticks == 240)
                run.match.fighter(fighterCount - 1)
                    .take_damage(run.match.fighter(fighterCount - 1).max_hp(),
                                 &run.match.fighter(0));
            const fnd::input::PlayerState *inputs[4] = {&input, nullptr, nullptr, nullptr};
            const auto frame = run.match.step(inputs, gameplay::FixedStep::seconds);
            run.shots += frame.shotsSpawned;
            run.respawns += frame.respawned[fighterCount - 1];
            for (int i = 0; i < fighterCount; ++i)
            {
                run.targets[i].position  = run.match.fighter(i).position();
                run.targets[i].facingYaw = run.match.fighter(i).facing_yaw();
                run.targets[i].alive     = run.match.fighter(i).is_alive();
            }
            run.camera.update(gameplay::FixedStep::seconds);
        }
    }
}

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

    for (int fighterCount : {2, 4})
    {
        Run baseline;
        replay(baseline, 60, fighterCount);
        CHECK(baseline.ticks == gameplay::FixedStep::tickRate * 10 && baseline.shots > 0 &&
              baseline.respawns == 1);
        for (int hz : {30, 144})
        {
            Run other;
            replay(other, hz, fighterCount);
            CHECK(other.ticks == baseline.ticks);
            CHECK(other.shots == baseline.shots && other.respawns == baseline.respawns);
            CHECK(other.match.economy().elapsed() == baseline.match.economy().elapsed());
            CHECK(other.match.economy().balloon(1) == baseline.match.economy().balloon(1));
            CHECK(other.camera.eye() == baseline.camera.eye());
            for (int i = 0; i < fighterCount; ++i)
            {
                const auto &a = baseline.match.fighter(i);
                const auto &b = other.match.fighter(i);
                CHECK(a.position() == b.position() && a.facing_yaw() == b.facing_yaw());
                CHECK(a.hp() == b.hp() && a.state() == b.state());
                CHECK(a.stamina() == b.stamina() && a.main_frac() == b.main_frac());
                CHECK(a.hyper_gauge() == b.hyper_gauge());
            }
        }
    }
    std::puts("fixed_step_test: input edges, bounded stalls and 30/60/144 Hz replay pass");
    return 0;
}
