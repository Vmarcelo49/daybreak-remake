#include "gameplay/result_title.h"

#include "assets/exe_strings.h"

namespace gameplay {
namespace {

// The original rolls `FUN_0065d150() % 100 < p` on the branches that can award the penalty
// title. Same LCG the front end uses, so a run with a fixed seed reproduces.
int rollPercent(uint32_t& rng) {
    rng = rng * 1664525u + 1013904223u;
    return (int)((rng >> 8) % 100u);
}

}  // namespace

bool loadResultTitles(const std::string& exePath, ResultTitleTable& out, std::string& error) {
    // VA 0x6b7308: the table FUN_00430860 indexes (`(&PTR_DAT_006b7308)[index]`), 41 entries
    // terminated by a null pointer.
    constexpr uint32_t kTitleTableVa = 0x6b7308;
    if (!fnd::assets::readExeStringTable(exePath, kTitleTableVa, out.titles, error)) return false;
    if (!out.loaded()) {
        error = "title table has " + std::to_string(out.titles.size()) + " entries, expected " +
                std::to_string(kResultTitleCount);
        return false;
    }
    return true;
}

int resultTitleIndex(const ResultRecord& r, uint32_t& rng, bool* resolved) {
    // Conditions whose fields are not recovered are SKIPPED, and every skip is counted: the
    // returned index is then the original's own answer for a record that had not matched those
    // conditions, which is not a claim about the record. `resolved` says whether the chain ran
    // end to end, and `skipped` names how many conditions could not be evaluated (the docs list
    // them; the caller logs the count).
    int skipped = 0;
    auto skip = [&]() { ++skipped; };
    auto finish = [&](int index) {
        if (resolved) *resolved = skipped == 0;
        return index;
    };
    // `roll < percent` awards the penalty title instead of the branch's own title.
    auto pick = [&](int percent, int title) {
        return rollPercent(rng) < percent ? kResultTitlePenalty : title;
    };
    const float hitsDealt = (float)r.hitsDealt();
    const float hitsTaken = (float)r.hitsTaken();
    const float eventsDealt = (float)r.eventsDealt();
    const int damageDealt = r.damageDealt();
    const int damageTaken = r.damageTaken();

    if (r.koed) {
        // Branch A: capacity - balloon < 1 — this fighter ended the round out of budget.
        if (r.enemyCapacity * 30000 / 100 <= damageDealt && hitsDealt * .5f < eventsDealt)
            return finish(pick(1, 22));
        if ((float)r.eventsTaken() <= hitsTaken * .1f &&
            (float)r.eventsFromOthers <= (float)r.hitsFromOthers * .1f &&
            hitsDealt * .5f < eventsDealt)
            return finish(pick(1, 24));
        // UNRESOLVED: +0x64 (a float accumulator, 4e6 threshold) gates this branch.
        skip();
        // UNRESOLVED: +0x20 > 14999.
        skip();
        if (r.enemyCapacity * 25000 / 100 <= damageDealt &&
            (float)(r.teamCapacity * 35000 / 100) <= (float)damageTaken && r.shotHits <= r.meleeHits)
            return finish(pick(6, 31));
        // UNRESOLVED: +0x54 > 19.
        skip();
        // UNRESOLVED: +0x60 > 2.
        skip();
        // UNRESOLVED: +0x60 == 0.
        skip();
        if (r.hitsDealt() <= r.teamCapacity * 0x14 / 100) return finish(pick(16, 27));
        if (r.enemyCapacity * 25000 / 100 <= damageDealt && (double)hitsTaken <= (double)hitsDealt * .05)
            return finish(pick(6, 29));
        // UNRESOLVED: +0x6c > 249.
        skip();
        if ((float)r.hitsFromTarget * .5f < (float)r.eventsFromTarget &&
            (float)r.eventsFromOthers <= (float)r.hitsFromOthers * .05f)
            return finish(pick(6, 36));
        // UNRESOLVED: +0x48 (>= 10% of capacity) and +0x20 == 0.
        skip();
        // UNRESOLVED: +0x7c/+0x80 (alive-fraction).
        skip();
        if (r.enemyCapacity * 15000 / 100 <= damageDealt &&
            damageTaken <= r.teamCapacity * 20000 / 100 && hitsTaken <= hitsDealt * .35f &&
            (float)r.hitsFromTarget > (float)r.hitsToTarget * .25f)
            return finish(pick(3, 19));
        if (r.enemyCapacity * 12000 / 100 <= damageDealt &&
            damageTaken <= r.teamCapacity * 25000 / 100 && hitsTaken <= hitsDealt * .5f &&
            (float)r.hitsFromTarget > (float)r.hitsToTarget * .15f)
            return finish(pick(6, 37));
        // UNRESOLVED: +0x34 (hits on the local player) > hitsDealt * 0.75.
        skip();
        if (r.enemyCapacity * 9000 / 100 <= damageDealt &&
            damageTaken <= r.teamCapacity * 30000 / 100 && hitsTaken <= hitsDealt * .65f &&
            (float)r.hitsFromTarget > (float)r.hitsToTarget * .1f)
            return finish(pick(11, 39));
        return finish(kResultTitleFallback);
    }

    // Branch B: still standing (capacity - balloon >= 1).
    if (r.enemyCapacity * 35000 / 100 <= damageDealt &&
        damageTaken <= r.teamCapacity * 0x30d4 / 100 && hitsTaken <= hitsDealt * .15f &&
        (float)r.hitsFromTarget > (float)r.hitsToTarget * .5f)
        return finish(6);
    if (r.enemyCapacity * 25000 / 100 <= damageDealt &&
        damageTaken <= r.teamCapacity * 25000 / 100 && r.hitsOnLocalPlayer == 0)
        return finish(3);
    if (hitsTaken <= hitsDealt * .1f &&
        (float)r.hitsFromOthers <= (float)r.hitsToOthers * .1f &&
        (float)r.hitsFromTarget > (float)r.hitsToTarget * .5f)
        return finish(4);
    if (r.enemyCapacity * 30000 / 100 <= damageDealt &&
        (float)r.hitsFromTarget > (float)r.hitsToTarget * .75f && r.meleeHits <= r.shotHits)
        return finish(0xd);
    if (r.enemyCapacity * 25000 / 100 <= damageDealt &&
        damageTaken <= r.teamCapacity * 0x445c / 100 && hitsTaken <= hitsDealt * .2f &&
        (float)r.hitsFromTarget > (float)r.hitsToTarget * .4f)
        return finish(0xc);
    // UNRESOLVED: +0x20 >= 15% of capacity.
    skip();
    if (r.enemyCapacity * 40000 / 100 <= damageDealt && r.teamCapacity * 40000 / 100 <= damageTaken)
        return finish(0x21);
    // UNRESOLVED: +0x74 > 14.
    skip();
    // UNRESOLVED: +0x58 > 1.
    skip();
    // UNRESOLVED: +0x58 > 1 (with damage to others >= 10% and hits to target <= hits to others).
    skip();
    // UNRESOLVED: +0x78 + 0x74 > 19 (melee <= shot).
    skip();
    // UNRESOLVED: +0x78 + 0x74 < 21 (melee <= shot).
    skip();
    if (r.enemyCapacity * 30000 / 100 <= damageDealt &&
        (float)r.hitsFromTarget > (float)r.hitsToTarget * .25f && r.shotHits <= r.meleeHits)
        return finish(2);
    if (damageDealt <= r.enemyCapacity * 15000 / 100 &&
        r.teamCapacity * 35000 / 100 <= damageTaken && r.shotHits <= r.meleeHits)
        return finish(7);
    // UNRESOLVED: +0x58 > 2.
    skip();
    // UNRESOLVED: +0x5c > 14.
    skip();
    // UNRESOLVED: +0x70 > 19.
    skip();
    if (r.teamCapacity * 200 / 100 <= r.hitsFromTarget) return finish(1);
    // UNRESOLVED: +0x54 >= 20% of capacity.
    skip();
    // UNRESOLVED: +0x48 (>= 10% of capacity) and +0x20 == 0.
    skip();
    if (r.enemyCapacity * 15000 / 100 <= damageDealt &&
        damageTaken <= r.teamCapacity * 20000 / 100 && hitsTaken <= hitsDealt * .35f &&
        (float)r.hitsFromTarget > (float)r.hitsToTarget * .25f)
        return finish(0x13);
    if (r.enemyCapacity * 12000 / 100 <= damageDealt &&
        damageTaken <= r.teamCapacity * 25000 / 100 && hitsTaken <= hitsDealt * .5f &&
        (float)r.hitsFromTarget > (float)r.hitsToTarget * .15f)
        return finish(0x25);
    // UNRESOLVED: +0x34 (hits on the local player) > hitsDealt * 0.75.
    skip();
    if (r.enemyCapacity * 9000 / 100 <= damageDealt &&
        damageTaken <= r.teamCapacity * 30000 / 100 && hitsTaken <= hitsDealt * .65f &&
        (float)r.hitsFromTarget > (float)r.hitsToTarget * .1f)
        return finish(0x27);
    return finish(kResultTitleFallback);
}

}  // namespace gameplay
