#include <cstdio>
#include "gameplay/match.h"
#include "gameplay/bot_input.h"

#define CHECK(condition) do { if (!(condition)) { std::fprintf(stderr,"line %d: %s\n",__LINE__,#condition); return 1; } } while (0)
int main() {
    gameplay::Match match;
    gameplay::MatchConfig config;
    config.healthPercent = 200;
    config.gaugePercent = 200;
    config.startHP[0] = config.startHP[1] = 200;
    config.timeLimit = 1;
    config.balloonSize[0] = 40;
    config.balloonSize[1] = 200;
    config.spawn[1] = glm::vec3(500,0,0);
    const xm::Model* models[2] = {};
    xm::Controller* animations[2] = {};
    match.reset(config,models,animations,nullptr,nullptr);
    match.economy().setLogFile(nullptr);
    CHECK(match.fighter(0).hp() == 200);
    CHECK(match.fighter(1).max_hp() == 200);
    match.fighter(1).take_damage(20,&match.fighter(0));
    CHECK(match.fighter(1).hp() == 180);
    CHECK(match.fighter(0).stats().damageDealt == 20);
    CHECK(match.fighter(1).stats().damageTaken == 20);
    match.fighter(1).take_damage(1000,&match.fighter(0));
    CHECK(match.fighter(0).stats().kos == 1 && match.fighter(1).stats().deaths == 1);
    match.fighter(1).take_damage(1000,&match.fighter(0));
    CHECK(match.fighter(0).stats().kos == 1);
    match.fighter(1).reset(config.spawn[1],0);
    CHECK(match.fighter(1).hp() == 200 && match.fighter(1).stats().deaths == 1);
    // Issue #14: the COM decision state replaced the frame-modulo sparring policy. It is
    // still deterministic — two brains on the SAME seed and the same view produce the same
    // input for the same tick — and it does not sit on Guard when nothing threatens it.
    gameplay::BotBrain brainA, brainB;
    brainA.reset(4242);
    brainB.reset(4242);
    gameplay::BotContext ctx;
    ctx.match = &match;
    ctx.fighterIndex = 0;
    fnd::input::PlayerState botA, botB;
    for (uint64_t frame = 1; frame <= 100; ++frame) {
        gameplay::updateBotInput(brainA,ctx,botA,frame);
        gameplay::updateBotInput(brainB,ctx,botB,frame);
        for (int a = 0; a < fnd::input::ActionCount; ++a) CHECK(botA.down[a] == botB.down[a]);
    }
    CHECK(!botA.down[fnd::input::Guard]);
    for (int frame = 0; frame < 61; ++frame) match.step(nullptr,nullptr,1./60.);
    CHECK(match.economy().roundOver());
    // Issue #11: a timed round always names a side. Fighter 1 was KO'd before the
    // first step, so side 1 carries that KO's balloon and side 0 carries none: the
    // LOWER balloon wins (FUN_00635d40 @0x636e9c-0x636ee9), i.e. side 0. The DX9 port
    // returned -1 here; that draw exit does not exist in the original.
    CHECK(match.economy().roundOverSide() == 0);
    gameplay::MatchEconomy economy(nullptr);
    economy.set_round_rules(0,config.balloonSize);
    economy.tick(.01);
    const bool dead[2] = {false,false};
    economy.update(dead);
    // The credit is the raw 20 base, NOT a capacity-normalized value: the 40/200
    // balloon-size handicap is the per-side LIMIT, not an increment multiplier
    // (scene+0x43c4/+0x43c8 vs the 0x14 literal at FUN_00639160:0x6393b5).
    CHECK(economy.balloon(0) == 20.f && economy.balloon(1) == 20.f);
    CHECK(economy.capacity(0) == 40.f && economy.capacity(1) == 200.f);
    CHECK(!economy.roundOver());
    const bool alive[2] = {true,true};
    economy.reset();
    economy.set_round_rules(1,config.balloonSize);
    // Side 0 takes one KO and comes back; side 1 stays clean, so side 1 has the LOWER
    // balloon when the clock runs out.
    const bool side0Dead[2] = {false,true};
    economy.tick(.1); economy.note_death(0); economy.update(side0Dead);
    economy.tick(1); economy.update(alive);
    CHECK(economy.roundOverSide() == 1);

    gameplay::Match teamMatch;
    gameplay::MatchConfig teamConfig;
    teamConfig.fighterCount = 3;
    teamConfig.side[0] = teamConfig.side[1] = 0;
    teamConfig.side[2] = teamConfig.side[3] = 1;
    teamConfig.spawn[1] = glm::vec3(-900,0,0);
    teamConfig.spawn[2] = glm::vec3(900,0,0);
    teamConfig.spawn[3] = glm::vec3(1200,0,0);
    const xm::Model* teamModels[4] = {};
    xm::Controller* teamAnimations[4] = {};
    teamMatch.reset(teamConfig,teamModels,teamAnimations,nullptr,nullptr);
    teamMatch.economy().setLogFile(nullptr);
    const fnd::input::PlayerState* teamInputs[4] = {};
    teamMatch.step(teamInputs,1./60.);
    CHECK(teamMatch.config().fighterCount == 3);
    CHECK(teamMatch.economy().balloon(0) == 0.f && teamMatch.economy().balloon(1) == 0.f);
    teamConfig.fighterCount = 4;
    teamMatch.reset(teamConfig,teamModels,teamAnimations,nullptr,nullptr);
    teamMatch.economy().setLogFile(nullptr);
    teamMatch.step(teamInputs,1./60.);
    CHECK(teamMatch.config().fighterCount == 4);
    CHECK(teamMatch.economy().balloon(0) == 0.f && teamMatch.economy().balloon(1) == 0.f);

    gameplay::MatchEconomy teamEconomy(nullptr);
    teamEconomy.set_round_rules(0,config.balloonSize);
    const bool teamAlive[4] = {true,true,false,true};
    const int sides[4] = {0,0,1,1};
    teamEconomy.tick(.01);
    CHECK(teamEconomy.update(teamAlive,sides,4).respawned[2] == false);
    // One KO credits the victim's own side with the raw base; the 40%/200% handicap
    // only moves where that side's LIMIT is.
    CHECK(teamEconomy.balloon(0) == 0.f && teamEconomy.balloon(1) == 20.f);
    CHECK(teamEconomy.kos(1) == 1 && teamEconomy.kos(0) == 0);
    teamEconomy.tick(3.0);
    CHECK(teamEconomy.update(teamAlive,sides,4).respawned[2]);
    std::puts("FRONTEND_BATTLE: ok");
}
