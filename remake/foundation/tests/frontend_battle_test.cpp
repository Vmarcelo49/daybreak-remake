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
    fnd::input::PlayerState botA, botB;
    for (uint64_t frame = 1; frame <= 100; ++frame) {
        gameplay::updateBotInput(botA,match.fighter(0),match.fighter(1),frame);
        gameplay::updateBotInput(botB,match.fighter(0),match.fighter(1),frame);
        for (int a = 0; a < fnd::input::ActionCount; ++a) CHECK(botA.down[a] == botB.down[a]);
    }
    CHECK(!botA.down[fnd::input::Guard]);
    for (int frame = 0; frame < 61; ++frame) match.step(nullptr,nullptr,1./60.);
    CHECK(match.economy().roundOver());
    CHECK(match.economy().roundOverSide() == -1);
    gameplay::MatchEconomy economy(nullptr);
    economy.set_round_rules(0,config.balloonSize);
    economy.tick(.01);
    const bool dead[2] = {false,false};
    economy.update(dead);
    CHECK(economy.balloon(0) == 52.5f && economy.balloon(1) == 10.5f);
    const bool alive[2] = {true,true};
    economy.reset();
    economy.set_round_rules(1,config.balloonSize);
    economy.tick(.1); economy.update(dead);
    economy.tick(1); economy.update(alive);
    CHECK(economy.roundOverSide() == 0);

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
    CHECK(teamEconomy.update(teamAlive,sides).respawned[2] == false);
    CHECK(teamEconomy.balloon(0) == 0.f && teamEconomy.balloon(1) == 10.5f);
    teamEconomy.tick(3.0);
    CHECK(teamEconomy.update(teamAlive,sides).respawned[2]);
    std::puts("FRONTEND_BATTLE: ok");
}
