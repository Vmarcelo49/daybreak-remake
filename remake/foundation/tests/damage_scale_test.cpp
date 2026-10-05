// The two recovered damage chains, pinned against real combo data (Rena + item 001).
//
// WHY this test exists: the port used to read the record's +0x44 field (`hpDamage`) as the
// HP damage, which made every landed hit remove ~1 HP (the field is really the victim's
// gauge feed — FUN_00637950:280). A 100 HP fighter then needed ~100 clean hits, so no
// normal match could reach a KO. The numbers below are the recovered chains evaluated on
// the shipped data, and they are exact integers: a change to the field mapping, the neutral
// stats or the pool scale moves them.
//
// Provenance:
//   MELEE FUN_00639160 @0x639160-0x6391b0  ((((power * atk)/100 * def)/100 * 100)/setting)
//   SHOT  FUN_00637950 @0x637950           ((((base * tier)/100 * atk)/100 * def)/100)
//   stats FUN_0043ded0 @0x43dee3/@0x43dee9 (attack 100, defense 50, reset every frame)
//   setting FUN_00633ca0 @0x633cf3         (scene+0x43cc = 100 by default)
//   data  data/rena/00.dat move 300 combat[0x00] = 1500; data/bullet/001/000.dat blob[0] = 1750
#include "gameplay/character_moves.h"
#include "gameplay/fighter.h"
#include "gameplay/fixed_step.h"
#include "input/input.h"
#include "gameplay/match.h"
#include "gameplay/weapon_definition.h"

#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

namespace {

int g_checks = 0;
int g_failures = 0;

void check(bool ok, const std::string& what) {
    ++g_checks;
    if (!ok) {
        ++g_failures;
        std::printf("  FAIL %s\n", what.c_str());
    }
}

void checkInt(const std::string& what, long long expected, long long actual) {
    ++g_checks;
    if (expected != actual) {
        ++g_failures;
        std::printf("  FAIL %s: expected %lld, got %lld\n", what.c_str(), expected, actual);
    }
}

std::vector<uint8_t> readFile(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) return {};
    return std::vector<uint8_t>((std::istreambuf_iterator<char>(file)),
                                std::istreambuf_iterator<char>());
}

// The install, from $GAME_DIR or by walking up from the working directory (the same rule the
// other asset-backed tests use).
std::filesystem::path findInstall() {
    std::error_code ec;
    if (const char* configured = std::getenv("GAME_DIR")) {
        const std::filesystem::path candidate(configured);
        if (std::filesystem::is_regular_file(candidate / "data" / "rena" / "00.dat", ec))
            return candidate;
    }
    for (auto dir = std::filesystem::current_path(ec); !dir.empty(); dir = dir.parent_path()) {
        for (const auto& root : {dir, dir / "Higurashi-Daybreak"}) {
            if (std::filesystem::is_regular_file(root / "data" / "rena" / "00.dat", ec))
                return root;
        }
        const auto parent = dir.parent_path();
        if (parent == dir) break;
    }
    return {};
}

// A fighter bound to the real combo, on a 100 HP pool like the front-end battle's.
gameplay::Fighter makeFighter(const gameplay::CharacterMoves& moves,
                              const gameplay::WeaponDefinition& weapon,
                              const gameplay::BulletParameter& bullet, const glm::vec3& at) {
    gameplay::Fighter fighter;
    fighter.reset(at, 0.0f);
    fighter.set_moves(&moves);
    fighter.set_weapon(&weapon);
    fighter.set_bullet_parameter(1, &bullet);
    fighter.set_hp(gameplay::FighterConstants::kMaxHP);
    return fighter;
}

}  // namespace

int main() {
    const std::filesystem::path install = findInstall();
    if (install.empty()) {
        std::printf("damage_scale_test: SKIP (no game install found; set GAME_DIR)\n");
        return 0;
    }
    std::string error;
    gameplay::CharacterMoves moves;
    gameplay::WeaponDefinition weapon;
    gameplay::BulletParameter bullet;
    {
        const std::vector<uint8_t> bytes = readFile((install / "data/rena/00.dat").string());
        if (bytes.empty() || !moves.parse(bytes.data(), bytes.size(), error)) {
            std::printf("damage_scale_test: SKIP (rena move table: %s)\n", error.c_str());
            return 0;
        }
        const std::vector<uint8_t> item = readFile((install / "data/item/001.dat").string());
        if (item.empty() || !weapon.parse(1, item.data(), item.size(), error)) {
            std::printf("damage_scale_test: SKIP (item 001: %s)\n", error.c_str());
            return 0;
        }
        const std::vector<uint8_t> shot = readFile((install / "data/bullet/001/000.dat").string());
        if (shot.empty() || !gameplay::parseBulletParameter(shot.data(), shot.size(), 0, bullet, error)) {
            std::printf("damage_scale_test: SKIP (bullet 001/000: %s)\n", error.c_str());
            return 0;
        }
    }

    std::printf("\n-- the data the chains are evaluated on\n");
    {
        const gameplay::CharacterMove* move = moves.find(300);
        check(move != nullptr, "rena move 300 is in the table");
        const gameplay::MoveEntry* hit = nullptr;
        for (int p = 0; move && p < move->sectionCount && !hit; ++p)
            for (int e = 0; e < move->phases[p].entryCount; ++e)
                if (move->phases[p].entries[e].has_combat()) { hit = &move->phases[p].entries[e]; break; }
        check(hit != nullptr, "move 300 has a combat entry");
        if (hit) {
            checkInt("move 300 combat[0x00] (baseDamage, the HP power)", 1500, hit->baseDamage);
            checkInt("move 300 combat[0x05] (hpDamage, the gauge feed)", 50, hit->hpDamage);
            checkInt("move 300 hitRadius", 20, hit->hitRadius);
        }
        checkInt("item 001 tap bullet blob[0] (baseDamage)", 1750, bullet.baseDamage);
        checkInt("item 001 tap bullet blob[5] (hpDamage, the gauge feed)", 75, bullet.hpDamage);
    }

    std::printf("\n-- melee: 1500 -> 750 on the pool -> 8 HP on the port's 100 HP scale\n");
    {
        gameplay::Fighter attacker = makeFighter(moves, weapon, bullet, glm::vec3(0, 0, 0));
        const gameplay::MeleeSwing swing = attacker.preview_melee_swing(false, false);
        check(swing.dataDriven, "the swing is data-driven (the move table is bound)");
        checkInt("swing damage", 8, swing.damage);
        // 750/10000 of a 100 HP pool is 7.5, and the port's rounding convention is +0.5.
        checkInt("the pool figure it came from", 750, 1500 / 2);
    }

    std::printf("\n-- shot: 1750 -> 875 on the pool -> 9 HP on the port's 100 HP scale\n");
    {
        gameplay::Fighter shooter = makeFighter(moves, weapon, bullet, glm::vec3(0, 0, 0));
        checkInt("tap shot damage", 9, shooter.shot_params_for(gameplay::ShotTier::Tap).damage);
        checkInt("the tap radius comes from the same bullet", 30,
                 (int)shooter.shot_params_for(gameplay::ShotTier::Tap).hitRadius);
    }

    std::printf("\n-- a light hit no longer removes ~1 HP: the KO lands in a sane count\n");
    {
        gameplay::MatchConfig config;
        config.fighterCount = 2;
        config.spawn[1] = glm::vec3(0, 0, 40);   // inside 30 (body) + 20 (move 300)
        const xm::Model* models[4] = {};
        xm::Controller* animations[4] = {};
        gameplay::Match match;
        match.reset(config, models, animations, nullptr, nullptr);
        match.economy().setLogFile(nullptr);
        match.fighter(0).set_moves(&moves);
        match.fighter(0).set_weapon(&weapon);
        match.fighter(0).set_bullet_parameter(1, &bullet);
        match.fighter(1).set_moves(&moves);
        match.fighter(1).set_hp(gameplay::FighterConstants::kMaxHP);

        // P1 melees on a 20-tick period; the swing's own windows pace the rest.
        fnd::input::PlayerState input;
        int hits = 0;
        int firstHitDamage = -1;
        for (int tick = 0; tick < 1200 && match.fighter(1).is_alive(); ++tick) {
            for (bool& down : input.down) down = false;
            input.down[fnd::input::AttackA] = (tick % 20) < 3;
            fnd::input::compute_edges(input);
            const fnd::input::PlayerState* inputs[4] = {&input, nullptr, nullptr, nullptr};
            const int before = match.fighter(1).hp();
            const gameplay::MatchFrame frame = match.step(inputs, gameplay::FixedStep::seconds);
            if (frame.meleeHit[0]) {
                ++hits;
                if (firstHitDamage < 0) firstHitDamage = before - match.fighter(1).hp();
            }
        }
        checkInt("one landed hit removes the recovered 8 HP (not the old 1)", 8, firstHitDamage);
        check(!match.fighter(1).is_alive(), "a stationary dummy goes down");
        check(hits >= 12 && hits <= 15, "the KO lands in 12..15 landed hits");
        checkInt("and the economy credited exactly one KO", 1, match.economy().kos(1));
        checkInt("with one respawn still pending (the KO clock is running)", 0,
                 match.economy().respawns(1));
    }

    std::printf("\n-- the legacy path (no move table) keeps its shared tuning\n");
    {
        gameplay::Fighter bare;
        bare.reset(glm::vec3(0, 0, 0), 0.0f);
        const gameplay::MeleeSwing swing = bare.preview_melee_swing(false, false);
        check(!swing.dataDriven, "no move table: the legacy swing");
        checkInt("legacy light damage", gameplay::FighterConstants::kLightDamage, swing.damage);
    }

    std::printf("\nchecks: %d, failures: %d\n", g_checks, g_failures);
    if (g_failures == 0) std::printf("DAMAGE_SCALE: ok\n");
    return g_failures == 0 ? 0 : 1;
}
