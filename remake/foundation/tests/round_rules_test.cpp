// =============================================================================
//  round_rules_test.cpp — KO, Overkill, respawn and victory rules (issue #11).
//
//  The economy's own arithmetic is pinned in match_economy_test.cpp; this test
//  drives the same rules through Match, i.e. through Fighter::take_damage, the
//  projectile pool and MatchFrame, which is where the acceptance criteria live:
//
//    * 1v1 KO -> Overkill -> respawn, each credit counted exactly once;
//    * 2v2 with teams: the credit goes to the VICTIM's side, and a partner's death
//      cannot move it;
//    * the Overkill window and its cutoff: a downed body keeps taking +1-per-hit
//      until it respawns, and no hit on it can re-enter the KO state or restart the
//      death clock;
//    * the airborne respawn restores the recovered state (HP, ammo, move 0xc2's set)
//      and keeps the fighter's own team and spawn slot;
//    * the respawn re-entry is not selectable by the target lock ([fighter+0xaecb] is
//      read only by FUN_0041f580's lock-validity test) and NO damage immunity is
//      claimed anywhere;
//    * capacity extremes, both-side bursts and the timed-round tiebreaks all report a
//      winning side through MatchFrame.
//
//  Recovered rules and their sites are documented in gameplay/match_economy.h; the
//  port rules (same-frame burst detection, the seconds countdown, kRespawnSec as the
//  single KO clock where the original counts the KO move's phases) are listed there
//  too and repeated where a check depends on one.
//
//  Build (the CMake target is `round_rules_test`):
//    cmake --build remake/foundation/build/linux --target round_rules_test
//  Exit status: 0 when every check passes, 1 otherwise.
// =============================================================================
#include "gameplay/match.h"

#include <cmath>
#include <cstdio>
#include "synthetic_combo.h"

namespace {

int checks = 0;
int failures = 0;

void check(bool condition, const char* name) {
    ++checks;
    if (!condition) ++failures;
    std::printf("  %-62s %s\n", name, condition ? "ok" : "FAIL");
}

void checkInt(int expected, int actual, const char* name) {
    ++checks;
    const bool same = expected == actual;
    if (!same) ++failures;
    std::printf("  %-62s %s", name, same ? "ok" : "FAIL");
    if (!same) std::printf("  (expected %d, got %d)", expected, actual);
    std::printf("\n");
}

void checkFloat(float expected, float actual, float tolerance, const char* name) {
    ++checks;
    const bool same = std::fabs(expected - actual) <= tolerance;
    if (!same) ++failures;
    std::printf("  %-62s %s", name, same ? "ok" : "FAIL");
    if (!same) std::printf("  (expected %g, got %g)", (double)expected, (double)actual);
    std::printf("\n");
}

void section(const char* title) { std::printf("\n-- %s\n", title); }

constexpr double kDt = 1.0 / 64.0;  // the port's fixed step

// A 1v1 with no models: Fighter::reset() drives the whole state machine, which is
// what Match::reset does for a null model (match.cpp:22-23).
// One synthetic combo for every match here. Static because the config holds POINTERS into
// it and Match copies the config, so it has to outlive each match (AGENTS rule 7).
const test::synthetic::Combo& matchCombo() {
    static const test::synthetic::Combo combo;
    return combo;
}

void setup1v1(gameplay::Match& match, gameplay::MatchConfig& config, int timeLimit = 0,
              const int balloonSize[2] = nullptr) {
    config.fighterCount = 2;
    config.side[0] = 0;
    config.side[1] = 1;
    config.spawn[0] = glm::vec3(0, 0, 0);
    config.spawn[1] = glm::vec3(300, 0, 0);
    config.facing[0] = 0.0f;
    config.facing[1] = 3.14159f;
    config.timeLimit = timeLimit;
    if (balloonSize) {
        config.balloonSize[0] = balloonSize[0];
        config.balloonSize[1] = balloonSize[1];
    }
    matchCombo().bind(config, config.fighterCount);
    const xm::Model* models[4] = {};
    xm::Controller* anims[4] = {};
    match.reset(config, models, anims, nullptr, nullptr);
    match.economy().setLogFile(nullptr);
}

// A 2v2: 0/1 blue, 2/3 red, which is what a four-fighter launch builds.
void setup2v2(gameplay::Match& match, gameplay::MatchConfig& config) {
    config.fighterCount = 4;
    config.side[0] = config.side[1] = 0;
    config.side[2] = config.side[3] = 1;
    config.spawn[0] = glm::vec3(0, 0, 0);
    config.spawn[1] = glm::vec3(-400, 0, 0);
    config.spawn[2] = glm::vec3(900, 0, 0);
    config.spawn[3] = glm::vec3(1400, 0, 0);
    matchCombo().bind(config, config.fighterCount);
    const xm::Model* models[4] = {};
    xm::Controller* anims[4] = {};
    match.reset(config, models, anims, nullptr, nullptr);
    match.economy().setLogFile(nullptr);
}

// Step until the frame reports the round over, or give up.
gameplay::MatchFrame stepUntilRoundOver(gameplay::Match& match, int maxFrames = 4000) {
    gameplay::MatchFrame frame;
    for (int i = 0; i < maxFrames; ++i) {
        frame = match.step(nullptr, nullptr, kDt);
        if (frame.roundOver) return frame;
    }
    return frame;
}

// ---------------------------------------------------------------------------
// 1v1: KO -> Overkill -> respawn, each credit exactly once.
// ---------------------------------------------------------------------------
void testOneVsOneKoOverkillRespawn() {
    section("1v1: KO -> Overkill -> respawn");
    gameplay::Match match;
    gameplay::MatchConfig config;
    setup1v1(match, config);

    // A clean kill: damage equal to the HP pool, so the overkill term is 0. The +1
    // reaction bonus is the melee default (the port's shared swing carries no hit
    // category; FUN_0063ba80's default branch is 198, the downed reaction).
    match.fighter(1).take_damage(match.fighter(1).max_hp(), &match.fighter(0));
    const gameplay::MatchFrame koFrame = match.step(nullptr, nullptr, kDt);
    checkInt(21, koFrame.koCredits[1], "the KO credit reaches MatchFrame (20 + reaction)");
    checkInt(21, static_cast<int>(match.economy().balloon(1)),
             "the balloon credits the VICTIM's side");
    checkInt(0, static_cast<int>(match.economy().balloon(0)), "the killer's side is untouched");
    checkInt(1, match.economy().kos(1), "exactly one KO credit");
    checkInt(1, match.fighter(1).stats().deaths, "one death on the victim");
    checkInt(1, match.fighter(0).stats().kos, "one KO on the attacker");
    check(koFrame.koSting, "the KO sting window is open");
    check(!koFrame.respawned[1], "no respawn on the KO frame");

    // The KO is not re-credited on the following frames.
    for (int i = 0; i < 30; ++i) match.step(nullptr, nullptr, kDt);
    checkInt(1, match.economy().kos(1), "still one KO credit after 30 frames");
    checkInt(21, static_cast<int>(match.economy().balloon(1)), "and the balloon is unchanged");

    // Overkill: a projectile that lands on the downed body credits exactly +1 each
    // (FUN_00637950 @0x638e0d-0x638e37) and cannot add a second KO credit.
    const glm::vec3 body = match.fighter(1).position();
    checkInt(100, match.fighter(0).hp(), "the attacker is untouched");

    auto fireAtBody = [&]() {
        // Owner-less shots take the shared tier tuning, so the hit radius is the
        // recovered 55-unit Tap radius and the spawn is at the body itself.
        match.shots().spawn(body, glm::vec3(0, 0, 1), gameplay::ShotTier::Tap, nullptr);
        return match.step(nullptr, nullptr, kDt);
    };
    gameplay::MatchFrame overkill = fireAtBody();
    checkInt(1, overkill.overkillHits[1], "one Overkill hit reported");
    checkInt(22, static_cast<int>(match.economy().balloon(1)), "the Overkill credit is +1");
    checkInt(1, match.economy().kos(1), "Overkill adds no KO credit");
    checkInt(1, match.economy().overkills(1), "one Overkill credit counted");
    checkInt(0, match.fighter(1).hp(), "the downed body stays at 0 HP");
    checkInt(1, match.fighter(1).stats().deaths, "and its death count does not move");

    overkill = fireAtBody();
    checkInt(23, static_cast<int>(match.economy().balloon(1)),
             "a second hit credits another +1");
    checkInt(2, match.economy().overkills(1), "two Overkill credits, one per hit");
    checkInt(1, match.economy().kos(1), "still exactly one KO credit");

    // The Overkill window ends with the respawn: kRespawnSec is the port's KO clock
    // (the original's is the KO move's phases + 30 frames, FUN_00428510
    // @0x42a14d-0x42a17d — see the port-rule list in match_economy.h).
    int frames = 0;
    gameplay::MatchFrame respawn;
    while (frames < 600) {
        respawn = match.step(nullptr, nullptr, kDt);
        ++frames;
        if (respawn.respawned[1]) break;
    }
    check(respawn.respawned[1], "the KO'd fighter respawns");
    checkInt(1, match.economy().respawns(1), "one respawn counted");
    checkFloat(gameplay::FighterConstants::kRespawnAirY, match.fighter(1).position().y, 0.5f,
               "the respawn is airborne at the recovered height");
    check(match.fighter(1).airborne(), "and reports itself airborne");
    check(match.fighter(1).hp() == match.fighter(1).max_hp(), "HP is restored");
    check(match.fighter(1).respawn_locked(),
          "the re-entry is not selectable until it lands ([fighter+0xaecb])");
    checkFloat(300.0f, match.fighter(1).position().x, 0.5f,
               "the respawn keeps the fighter's own spawn slot X");
    checkInt(1, match.config().side[1], "and its team identity");

    // A hit during the re-entry is not Overkill (the fighter is alive again) and gives
    // no balloon.
    const int before = static_cast<int>(match.economy().balloon(1));
    match.shots().spawn(match.fighter(1).position(), glm::vec3(0, 0, 1),
                        gameplay::ShotTier::Tap, nullptr);
    match.step(nullptr, nullptr, kDt);
    checkInt(before, static_cast<int>(match.economy().balloon(1)),
             "a hit on the respawned fighter credits no Overkill");

    // Landing ends the lock and puts the fighter back in play.
    for (int i = 0; i < 400 && match.fighter(1).airborne(); ++i)
        match.step(nullptr, nullptr, kDt);
    check(!match.fighter(1).airborne(), "the respawned fighter lands");
    check(!match.fighter(1).respawn_locked(), "and the lock ends on landing");
}

// ---------------------------------------------------------------------------
// One blow, one credit: a killing shot must not also add an Overkill +1.
// ---------------------------------------------------------------------------
void testKillingBlowDoesNotDoubleCredit() {
    section("a killing blow credits once (KO XOR Overkill)");
    gameplay::Match match;
    gameplay::MatchConfig config;
    setup1v1(match, config);
    match.step(nullptr, nullptr, kDt);

    // Leave the victim at 1 HP, then land a shot that kills it. FUN_00637950 branches
    // on `0 < [victim+0x7a4]` BEFORE the damage (local_39 @0x638c20-0x638c35): a blow
    // that kills takes the KO branch, and only a blow on an already-down body takes
    // the Overkill branch. There is no path that takes both, so the frame must show
    // the KO credit alone.
    match.fighter(1).set_hp(1);
    const glm::vec3 body = match.fighter(1).position();
    match.shots().spawn(body, glm::vec3(0, 0, 1), gameplay::ShotTier::Tap, nullptr);
    const gameplay::MatchFrame kill = match.step(nullptr, nullptr, kDt);
    checkInt(21, kill.koCredits[1], "the killing shot credits 20 + the reaction bonus");
    checkInt(0, kill.overkillHits[1], "and no Overkill credit for the same blow");
    checkInt(21, static_cast<int>(match.economy().balloon(1)), "the balloon moved once");
    checkInt(1, match.economy().kos(1), "one KO credit");
    checkInt(0, match.economy().overkills(1), "zero Overkill credits");
    check(!match.fighter(1).is_alive(), "the victim is down");

    // The next blow on the same body is a real Overkill event and credits +1 only.
    match.shots().spawn(body, glm::vec3(0, 0, 1), gameplay::ShotTier::Tap, nullptr);
    const gameplay::MatchFrame over = match.step(nullptr, nullptr, kDt);
    checkInt(0, over.koCredits[1], "no second KO credit");
    checkInt(1, over.overkillHits[1], "one Overkill credit");
    checkInt(22, static_cast<int>(match.economy().balloon(1)), "+1 exactly");

    // Two DIFFERENT blows in one frame are two events and both count: the first kills,
    // the second lands on the body it left behind.
    gameplay::Match two;
    gameplay::MatchConfig twoConfig;
    setup1v1(two, twoConfig);
    two.step(nullptr, nullptr, kDt);
    two.fighter(1).set_hp(1);
    const glm::vec3 body2 = two.fighter(1).position();
    two.shots().spawn(body2, glm::vec3(0, 0, 1), gameplay::ShotTier::Tap, nullptr);
    two.shots().spawn(body2, glm::vec3(0, 0, 1), gameplay::ShotTier::Tap, nullptr);
    const gameplay::MatchFrame both = two.step(nullptr, nullptr, kDt);
    checkInt(21, both.koCredits[1], "the first blow's KO credit");
    checkInt(1, both.overkillHits[1], "the second blow's Overkill credit");
    checkInt(22, static_cast<int>(two.economy().balloon(1)),
             "22 = 21 + 1, two events, no double count of either");
    checkInt(1, two.economy().kos(1), "still one KO");
    checkInt(1, two.economy().overkills(1), "one Overkill");
}

// ---------------------------------------------------------------------------
// The target lock must not select a fighter that is still in its re-entry.
// ---------------------------------------------------------------------------
void testRespawnIsNotSelectable() {
    section("respawn re-entry: not selectable, not immune");
    gameplay::Match match;
    gameplay::MatchConfig config;
    config.fighterCount = 4;
    config.side[0] = config.side[1] = 0;
    config.side[2] = config.side[3] = 1;
    config.spawn[0] = glm::vec3(0, 0, 0);
    config.spawn[1] = glm::vec3(-500, 0, 0);
    config.spawn[2] = glm::vec3(300, 0, 0);
    config.spawn[3] = glm::vec3(600, 0, 0);
    const xm::Model* models[4] = {};
    xm::Controller* anims[4] = {};
    match.reset(config, models, anims, nullptr, nullptr);
    match.economy().setLogFile(nullptr);
    match.step(nullptr, nullptr, kDt);  // seed the locks

    // Blue 0 locks the closer enemy 2, then 2 dies and respawns.
    match.fighter(2).take_damage(match.fighter(2).max_hp(), &match.fighter(0));
    int frames = 0;
    while (frames < 600) {
        ++frames;
        if (match.step(nullptr, nullptr, kDt).respawned[2]) break;
    }
    check(match.fighter(2).respawn_locked(), "enemy 2 is airborne and locked out");
    checkInt(3, match.melee_target(0),
             "melee target selection skips the respawn-locked enemy and takes the other");
    // The lock itself is not the port's business here — the marker is — but the
    // exclusion must not have been implemented as damage immunity: the original reads
    // [fighter+0xaecb] in the lock test only, so a hit still lands.
    const int hpBefore = match.fighter(2).hp();
    match.fighter(2).take_damage(5, &match.fighter(0));
    checkInt(hpBefore - 5, match.fighter(2).hp(),
             "no damage immunity is invented for the re-entry");
}

// ---------------------------------------------------------------------------
// 2v2: teams keep their own balloon, and a partner's death cannot move it.
// ---------------------------------------------------------------------------
void testTwoVsTwoCredits() {
    section("2v2: team credits stay on the victim's side");
    gameplay::Match match;
    gameplay::MatchConfig config;
    setup2v2(match, config);
    const fnd::input::PlayerState* inputs[4] = {};
    match.step(inputs, kDt);

    match.fighter(2).take_damage(match.fighter(2).max_hp(), &match.fighter(0));
    const gameplay::MatchFrame f1 = match.step(inputs, kDt);
    checkInt(21, f1.koCredits[2], "the red fighter's KO credits red");
    checkInt(21, static_cast<int>(match.economy().balloon(1)), "red's balloon is at 21");
    checkInt(0, static_cast<int>(match.economy().balloon(0)), "blue is untouched");
    checkInt(0, f1.koCredits[3], "the red partner is not credited for it");
    checkInt(1, match.economy().kos(1), "one red KO counted");

    // The partner dies in the same team and credits the same side once more.
    match.fighter(3).take_damage(match.fighter(3).max_hp(), &match.fighter(0));
    const gameplay::MatchFrame f2 = match.step(inputs, kDt);
    checkInt(21, f2.koCredits[3], "the partner's KO credits red too");
    checkInt(42, static_cast<int>(match.economy().balloon(1)), "red at 42");
    checkInt(2, match.economy().kos(1), "two red KOs counted");
    checkInt(0, match.economy().kos(0), "blue still has none");

    // Both red fighters die in the SAME frame: both credited, no double count, and
    // neither blue fighter's index is involved.
    for (int i = 0; i < 400; ++i) match.step(inputs, kDt);  // both respawn
    checkInt(2, match.economy().respawns(1), "both red fighters respawned");
    match.fighter(2).take_damage(match.fighter(2).max_hp(), &match.fighter(0));
    match.fighter(3).take_damage(match.fighter(3).max_hp(), &match.fighter(0));
    const gameplay::MatchFrame f3 = match.step(inputs, kDt);
    checkInt(21, f3.koCredits[2], "fighter 2's credit");
    checkInt(21, f3.koCredits[3], "fighter 3's credit");
    checkInt(4, match.economy().kos(1), "four red KOs, two of them this frame");
    checkInt(84, static_cast<int>(match.economy().balloon(1)), "red at 84");

    // 84 < 100: no burst, and the round keeps running with both sides alive after the
    // respawns come back.
    check(!f3.roundOver, "no round end at 84%");
    for (int i = 0; i < 400; ++i) match.step(inputs, kDt);
    check(match.fighter(2).is_alive() && match.fighter(3).is_alive(),
          "both red fighters are back in play");
}

// ---------------------------------------------------------------------------
// Capacity extremes at the match level: the handicap is the LIMIT.
// ---------------------------------------------------------------------------
void testCapacityExtremes() {
    section("capacity extremes: 40% bursts early, 200% holds");
    {
        gameplay::Match match;
        gameplay::MatchConfig config;
        const int sizes[2] = {100, 40};  // the victim's side carries the handicap
        setup1v1(match, config, 0, sizes);
        match.fighter(1).take_damage(match.fighter(1).max_hp(), &match.fighter(0));
        gameplay::MatchFrame f = match.step(nullptr, nullptr, kDt);
        checkInt(21, f.koCredits[1], "one KO at the 40% handicap");
        check(!f.roundOver, "21 < 40 does not burst");
        for (int i = 0; i < 400; ++i) {
            f = match.step(nullptr, nullptr, kDt);
            if (f.respawned[1]) break;
        }
        check(f.respawned[1], "the fighter comes back under the handicap");
        match.fighter(1).take_damage(match.fighter(1).max_hp(), &match.fighter(0));
        const gameplay::MatchFrame burst = match.step(nullptr, nullptr, kDt);
        check(burst.roundOver, "the second KO reaches 42 >= 40 and bursts");
        checkInt(0, burst.roundOverSide, "the bursted side loses: side 0 wins");
        check(match.economy().roundEnd() == gameplay::RoundEnd::Burst,
              "the round end is a burst");
        check(!burst.respawned[1], "a bursted side does not respawn");
    }
    {
        gameplay::Match match;
        gameplay::MatchConfig config;
        const int sizes[2] = {200, 200};
        setup1v1(match, config, 0, sizes);
        // Nine clean KOs with a respawn between each: 189 < 200.
        for (int k = 0; k < 9; ++k) {
            match.fighter(1).take_damage(match.fighter(1).max_hp(), &match.fighter(0));
            gameplay::MatchFrame f = match.step(nullptr, nullptr, kDt);
            check(!f.roundOver, k == 0 ? "no burst at 21 with a 200% capacity"
                                       : "no burst below 200%");
            for (int i = 0; i < 400; ++i) {
                f = match.step(nullptr, nullptr, kDt);
                if (f.respawned[1]) break;
            }
        }
        checkInt(189, static_cast<int>(match.economy().balloon(1)), "nine KOs reach 189");
        match.fighter(1).take_damage(match.fighter(1).max_hp(), &match.fighter(0));
        const gameplay::MatchFrame burst = match.step(nullptr, nullptr, kDt);
        check(burst.roundOver, "the tenth KO bursts the 200% capacity");
        checkInt(0, burst.roundOverSide, "and side 0 wins");
    }
}

// ---------------------------------------------------------------------------
// Simultaneous deaths and both-side bursts.
// ---------------------------------------------------------------------------
void testSimultaneousDeathsAndBursts() {
    section("simultaneous deaths and both-side bursts");
    {
        gameplay::Match match;
        gameplay::MatchConfig config;
        setup1v1(match, config);
        // Both fighters die before the same step: both sides are credited once.
        match.fighter(0).take_damage(match.fighter(0).max_hp(), &match.fighter(1));
        match.fighter(1).take_damage(match.fighter(1).max_hp(), &match.fighter(0));
        const gameplay::MatchFrame f = match.step(nullptr, nullptr, kDt);
        checkInt(21, static_cast<int>(match.economy().balloon(0)), "side 0 credited once");
        checkInt(21, static_cast<int>(match.economy().balloon(1)), "side 1 credited once");
        checkInt(1, match.economy().kos(0), "one KO for side 0");
        checkInt(1, match.economy().kos(1), "one KO for side 1");
        check(!f.roundOver, "21/21 is not a burst");
    }
    {
        gameplay::Match match;
        gameplay::MatchConfig config;
        const int sizes[2] = {40, 40};
        setup1v1(match, config, 0, sizes);
        // First pair of deaths, respawn, then both die again in one frame: both sides
        // reach 42 >= 40. The original's per-slot scan lets the LAST bursting slot
        // decide (FUN_00635d40 @0x6370a7-0x637171); with one fighter per side that is
        // fighter index 1, i.e. side 1 loses and side 0 wins.
        match.fighter(0).take_damage(match.fighter(0).max_hp(), &match.fighter(1));
        match.fighter(1).take_damage(match.fighter(1).max_hp(), &match.fighter(0));
        gameplay::MatchFrame f = match.step(nullptr, nullptr, kDt);
        check(!f.roundOver, "the first simultaneous pair does not burst at 40%");
        for (int i = 0; i < 400; ++i) {
            f = match.step(nullptr, nullptr, kDt);
            if (f.respawned[0] && f.respawned[1]) break;
        }
        check(f.respawned[0] && f.respawned[1], "both sides respawn");
        match.fighter(0).take_damage(match.fighter(0).max_hp(), &match.fighter(1));
        match.fighter(1).take_damage(match.fighter(1).max_hp(), &match.fighter(0));
        const gameplay::MatchFrame burst = match.step(nullptr, nullptr, kDt);
        check(burst.roundOver, "both sides burst in the same frame");
        checkInt(0, burst.roundOverSide,
                 "the highest bursting fighter index (1, side 1) loses -> side 0 wins");
        checkInt(42, static_cast<int>(match.economy().balloon(0)), "side 0 at 42");
        checkInt(42, static_cast<int>(match.economy().balloon(1)), "side 1 at 42");
        checkInt(4, match.economy().kos(0) + match.economy().kos(1),
                 "four KOs total: one per side in each simultaneous pair");
    }
    {
        // 2v2 both-side burst through Overkill: 40% each, one KO each side, then
        // enough overkill hits in one frame to push both over.
        gameplay::Match match;
        gameplay::MatchConfig config;
        config.fighterCount = 4;
        config.side[0] = config.side[1] = 0;
        config.side[2] = config.side[3] = 1;
        config.spawn[0] = glm::vec3(0, 0, 0);
        config.spawn[1] = glm::vec3(-500, 0, 0);
        config.spawn[2] = glm::vec3(300, 0, 0);
        config.spawn[3] = glm::vec3(700, 0, 0);
        config.balloonSize[0] = config.balloonSize[1] = 40;
        const xm::Model* models[4] = {};
        xm::Controller* anims[4] = {};
        match.reset(config, models, anims, nullptr, nullptr);
        match.economy().setLogFile(nullptr);
        const fnd::input::PlayerState* inputs[4] = {};

        match.fighter(0).take_damage(match.fighter(0).max_hp(), &match.fighter(2));
        match.fighter(2).take_damage(match.fighter(2).max_hp(), &match.fighter(0));
        match.step(inputs, kDt);
        checkInt(21, static_cast<int>(match.economy().balloon(0)), "blue at 21");
        checkInt(21, static_cast<int>(match.economy().balloon(1)), "red at 21");
        check(!match.economy().roundOver(), "21 < 40 for both");

        // 19 hits on blue's downed fighter and 12 on red's, all before one step: blue
        // reaches 40 (bursts), red reaches 33 (does not). The pool holds 32 shots, so
        // the two volleys have to fit inside it (gameplay/projectile.h:186).
        const glm::vec3 blueBody = match.fighter(0).position();
        const glm::vec3 redBody = match.fighter(2).position();
        for (int i = 0; i < 19; ++i)
            match.shots().spawn(blueBody, glm::vec3(0, 0, 1), gameplay::ShotTier::Tap, nullptr);
        for (int i = 0; i < 12; ++i)
            match.shots().spawn(redBody, glm::vec3(0, 0, 1), gameplay::ShotTier::Tap, nullptr);
        const gameplay::MatchFrame f = match.step(inputs, kDt);
        check(f.roundOver, "the Overkill hits burst the 40% side");
        checkInt(40, static_cast<int>(match.economy().balloon(0)), "blue reached 40");
        checkInt(33, static_cast<int>(match.economy().balloon(1)), "red reached 33");
        checkInt(1, f.roundOverSide, "only blue burst, so red wins");
    }
}

// ---------------------------------------------------------------------------
// Timeout: winner reporting through MatchFrame, both tiebreaks.
// ---------------------------------------------------------------------------
void testTimeoutWinnerReporting() {
    section("timeout: lower balloon, then HP, then the generator");
    {
        gameplay::Match match;
        gameplay::MatchConfig config;
        setup1v1(match, config, /*timeLimit=*/2);
        // Side 1 takes one KO; side 0 stays clean. When the clock runs out the LOWER
        // balloon (side 0) wins — the recovered sense (FUN_00635d40 @0x636e9c-0x636ee9).
        match.fighter(1).take_damage(match.fighter(1).max_hp(), &match.fighter(0));
        match.step(nullptr, nullptr, kDt);
        checkFloat(21.0f, match.economy().balloon(1), 0.001f, "side 1 carries the KO");
        const gameplay::MatchFrame f = stepUntilRoundOver(match);
        check(f.roundOver, "the timed round ends");
        check(match.economy().roundEnd() == gameplay::RoundEnd::Timeout, "by the clock");
        checkInt(0, f.roundOverSide, "the lower balloon wins: side 0");
        check(f.roundOverSide == 0 || f.roundOverSide == 1,
              "a timed round always reports a side");
    }
    {
        gameplay::Match match;
        gameplay::MatchConfig config;
        setup1v1(match, config, /*timeLimit=*/2);
        // Equal balloons, unequal HP: the higher total wins (FUN_00635d40
        // @0x636ef4-0x636f8a). Side 1 is left at half HP.
        match.fighter(1).set_hp(50);
        const gameplay::MatchFrame f = stepUntilRoundOver(match);
        check(f.roundOver, "the timed round ends with equal balloons");
        checkInt(0, f.roundOverSide, "the higher HP total (side 0) wins");
    }
    {
        gameplay::Match match;
        gameplay::MatchConfig config;
        setup1v1(match, config, /*timeLimit=*/2);
        // Equal balloons and equal HP: the generator decides, and the result is still a
        // side. Two matches with the same seed must agree (gameplay/rng.h).
        match.economy().set_rng_seed(0x5eed);
        const gameplay::MatchFrame f = stepUntilRoundOver(match);
        check(f.roundOver, "the timed round ends on a full tie");
        check(f.roundOverSide == 0 || f.roundOverSide == 1,
              "the generator still produces a side, never -1");

        gameplay::Match same;
        gameplay::MatchConfig sameConfig;
        setup1v1(same, sameConfig, /*timeLimit=*/2);
        same.economy().set_rng_seed(0x5eed);
        const gameplay::MatchFrame g = stepUntilRoundOver(same);
        checkInt(f.roundOverSide, g.roundOverSide, "the same seed resolves the same tie");
    }
    {
        // No limit at all: the round never ends by itself.
        gameplay::Match match;
        gameplay::MatchConfig config;
        setup1v1(match, config, /*timeLimit=*/0);
        for (int i = 0; i < 600; ++i) match.step(nullptr, nullptr, kDt);
        check(!match.economy().roundOver(), "an unlimited round keeps running");
        checkFloat(0.0f, (float)match.economy().timeLeft(), 0.001f, "timeLeft() is 0 = no limit");
    }
}

}  // namespace

int main() {
    std::printf("round rules test (KO, Overkill, respawn, victory) — no device\n");
    testOneVsOneKoOverkillRespawn();
    testKillingBlowDoesNotDoubleCredit();
    testRespawnIsNotSelectable();
    testTwoVsTwoCredits();
    testCapacityExtremes();
    testSimultaneousDeathsAndBursts();
    testTimeoutWinnerReporting();
    std::printf("\nchecks: %d, failures: %d\n", checks, failures);
    std::printf("ROUND_RULES: %s\n", failures == 0 ? "ok" : "FAIL");
    return failures == 0 ? 0 : 1;
}
