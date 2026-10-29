#include "gameplay/fighter.h"
#include "gameplay/fixed_step.h"
#include "gameplay/match.h"
#include "physics/raycast.h"

#include <array>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <limits>
#include <string>
#include "synthetic_combo.h"

namespace {

int checks = 0;
int failures = 0;

void check(bool condition, const char* name) {
    ++checks;
    if (!condition) ++failures;
    std::printf("  %-54s %s\n", name, condition ? "ok" : "FAIL");
}

void near(float expected, float actual, float tolerance, const char* name) {
    check(std::isfinite(actual) && std::abs(expected - actual) <= tolerance, name);
    if (!std::isfinite(actual) || std::abs(expected - actual) > tolerance)
        std::printf("    expected %.4f, got %.4f (tol %.4f)\n", expected, actual, tolerance);
}

void addTriangle(xm::Mesh& mesh, const glm::vec3& a, const glm::vec3& b,
                 const glm::vec3& c) {
    const uint32_t base = static_cast<uint32_t>(mesh.vertices.size());
    for (const glm::vec3& point : {a, b, c}) {
        xm::Vertex vertex;
        vertex.pos = point;
        mesh.vertices.push_back(vertex);
    }
    mesh.indices.insert(mesh.indices.end(), {base, base + 1, base + 2});
}

void addQuad(xm::Mesh& mesh, const glm::vec3& a, const glm::vec3& b,
             const glm::vec3& c, const glm::vec3& d) {
    addTriangle(mesh, a, b, c);
    addTriangle(mesh, a, c, d);
}

void addFloor(xm::Mesh& mesh, float y = 0.f, float extent = 1000.f) {
    // This winding gives the loader's ground query the same upward-facing floor normal
    // found in collision.x (FUN_004011f0 loads that channel for the stage).
    addQuad(mesh, {-extent, y, -extent}, {-extent, y, extent},
            {extent, y, extent}, {extent, y, -extent});
}

xm::Model flatStage() {
    xm::Model model;
    model.meshes.emplace_back();
    addFloor(model.meshes.back());
    return model;
}

xm::Model wallStage(bool corner) {
    xm::Model model = flatStage();
    xm::Mesh& mesh = model.meshes[0];
    addQuad(mesh, {100.f, 0.f, -500.f}, {100.f, 200.f, -500.f},
            {100.f, 200.f, 500.f}, {100.f, 0.f, 500.f});
    if (corner)
        addQuad(mesh, {-500.f, 0.f, 100.f}, {500.f, 0.f, 100.f},
                {500.f, 200.f, 100.f}, {-500.f, 200.f, 100.f});
    return model;
}

xm::Model stepStage(float stepHeight) {
    xm::Model model = flatStage();
    xm::Mesh& mesh = model.meshes[0];
    addQuad(mesh, {150.f, stepHeight, -200.f}, {150.f, stepHeight, 200.f},
            {300.f, stepHeight, 200.f}, {300.f, stepHeight, -200.f});
    addQuad(mesh, {150.f, 0.f, -200.f}, {150.f, stepHeight, -200.f},
            {150.f, stepHeight, 200.f}, {150.f, 0.f, 200.f});
    return model;
}

xm::Model rampStage() {
    xm::Model model;
    model.meshes.emplace_back();
    xm::Mesh& mesh = model.meshes.back();
    addQuad(mesh, {-200.f, 0.f, -200.f}, {-200.f, 0.f, 200.f},
            {0.f, 0.f, 200.f}, {0.f, 0.f, -200.f});
    addQuad(mesh, {0.f, 0.f, -200.f}, {0.f, 0.f, 200.f},
            {200.f, 100.f, 200.f}, {200.f, 100.f, -200.f});
    return model;
}

void testFlatAndGround() {
    std::puts("\n== flat ground, slope and step surfaces ==");
    xm::Model flat = flatStage();
    game::physics::MovementCollision collision;
    collision.setMeshes(&flat, &flat);
    const auto ground = collision.groundAt(30.f, -70.f, 100.f, 0.f, 150.f);
    check(ground.hit, "flat stage resolves ground from collision geometry");
    near(0.f, ground.height, 1e-4f, "flat ground height");
    check(ground.normal.y > 0.99f, "flat ground normal points up");

    xm::Model ramp = rampStage();
    collision.setMeshes(&ramp, &ramp);
    const auto slope = collision.groundAt(100.f, 0.f, 100.f, 100.f, 100.f);
    check(slope.hit, "elevated slope is walkable");
    near(50.f, slope.height, 1e-3f, "slope interpolates height from triangle");
    check(slope.normal.y > 0.8f, "slope normal passes walkable-angle gate");
    auto rampMove = collision.move({-40.f, 0.f, 0.f}, {40.f, 0.f, 0.f}, true);
    check(rampMove.grounded, "grounded movement follows a ramp");
    near(20.f, rampMove.position.y, 1.f, "ramp movement follows local elevation");

    xm::Model lowStep = stepStage(40.f);
    collision.setMeshes(&lowStep, &lowStep);
    const auto low = collision.move({0.f, 0.f, 0.f}, {220.f, 0.f, 0.f}, true);
    check(low.grounded, "step below provisional climb limit remains grounded");
    near(220.f, low.position.x, 0.1f, "fighter climbs a reachable step");
    near(40.f, low.position.y, 0.1f, "fighter lands on the elevated step surface");

    xm::Model highStep = stepStage(100.f);
    collision.setMeshes(&highStep, &highStep);
    const auto high = collision.move({0.f, 0.f, 0.f}, {220.f, 0.f, 0.f}, true);
    check(high.hitWall && high.position.x < 150.f,
          "step above provisional climb limit blocks forward motion");
}

void testSweepsAndFighterLanding() {
    std::puts("\n== swept walls, corners, dash distance and landing ==");
    xm::Model wall = wallStage(false);
    game::physics::MovementCollision collision;
    collision.setMeshes(&wall, &wall);
    const auto fast = collision.move({0.f, 0.f, 0.f}, {3000.f, 0.f, 0.f}, true);
    check(fast.hitWall && fast.position.x < 85.f,
          "full-speed swept displacement cannot tunnel through a wall");
    const auto slide = collision.move({0.f, 0.f, 0.f}, {200.f, 0.f, 120.f}, true);
    check(slide.hitWall && slide.position.x < 85.f,
          "wall contact keeps the body outside the wall by its radius");
    check(slide.position.z > 80.f, "remaining displacement slides along the wall");

    xm::Model corner = wallStage(true);
    collision.setMeshes(&corner, &corner);
    const auto cornerMove = collision.move({0.f, 0.f, 0.f}, {240.f, 0.f, 240.f}, true);
    check(cornerMove.hitWall && cornerMove.position.x < 85.f && cornerMove.position.z < 85.f,
          "two swept wall contacts stop a diagonal dash at a corner");

    collision.setMeshes(&wall, &wall);
    gameplay::Fighter fighter;
    fighter.init(nullptr, nullptr, {0.f, 20.f, 0.f}, 1.5707963f);
    constexpr double dt = gameplay::FixedStep::seconds;
    for (int i = 0; i < gameplay::FighterConstants::kBattleStartFrames; ++i)
        fighter.update(nullptr, nullptr, dt, &collision);
    fnd::input::PlayerState input;
    input.down[fnd::input::Action::Up] = true;
    fnd::input::compute_edges(input);
    fighter.update(&input, nullptr, dt, &collision); // first tap
    input.down[fnd::input::Action::Up] = false;
    fnd::input::compute_edges(input);
    fighter.update(&input, nullptr, dt, &collision);
    input.down[fnd::input::Action::Up] = true;
    fnd::input::compute_edges(input);
    fighter.update(&input, nullptr, dt, &collision); // dash starts toward +X
    input.down[fnd::input::Action::Up] = false;
    for (int i = 0; i < 40; ++i) {
        fnd::input::compute_edges(input);
        fighter.update(&input, nullptr, dt, &collision);
    }
    check(fighter.position().x < 85.f,
          "fighter dash update integrates collision before committing each tick");

    xm::Model floor = flatStage();
    collision.setMeshes(&floor, &floor);
    fighter.init(nullptr, nullptr, {0.f, 100.f, 0.f}, 0.f);
    for (int i = 0; i < gameplay::FighterConstants::kBattleStartFrames; ++i)
        fighter.update(nullptr, nullptr, dt, &collision);
    near(0.f, fighter.position().y, 0.1f, "initial spawn is grounded on the real floor");
    input = {};
    input.down[fnd::input::Action::Jump] = true;
    fnd::input::compute_edges(input);
    fighter.update(&input, nullptr, dt, &collision);
    input.down[fnd::input::Action::Jump] = false;
    for (int i = 0; i < 180 && fighter.airborne(); ++i) {
        fnd::input::compute_edges(input);
        fighter.update(&input, nullptr, dt, &collision);
    }
    check(!fighter.airborne(), "airborne fighter lands on the swept ground interval");
    near(0.f, fighter.position().y, 0.1f, "landing snaps to floor height");

    game::physics::MovementCollision missingStageCollision;
    fighter.init(nullptr, nullptr, {0.f, 0.f, 0.f}, 0.f);
    for (int i = 0; i < gameplay::FighterConstants::kBattleStartFrames; ++i)
        fighter.update(nullptr, nullptr, dt, &missingStageCollision);
    input = {};
    input.down[fnd::input::Action::Jump] = true;
    fnd::input::compute_edges(input);
    fighter.update(&input, nullptr, dt, &missingStageCollision);
    input.down[fnd::input::Action::Jump] = false;
    for (int i = 0; i < 180 && fighter.airborne(); ++i) {
        fnd::input::compute_edges(input);
        fighter.update(&input, nullptr, dt, &missingStageCollision);
    }
    check(!fighter.airborne(), "missing ground mesh retains the legacy spawn-plane landing");
}

void testSpawnAndRecovery() {
    std::puts("\n== env slots, spawn recovery and respawn ==");
    xm::Model floor = flatStage();
    game::physics::MovementCollision collision;
    collision.setMeshes(&floor, &floor);
    const float nan = std::numeric_limits<float>::quiet_NaN();
    check(!collision.validPosition({nan, 0.f, 0.f}), "non-finite world positions are rejected");
    check(!collision.validPosition({5000.f, 0.f, 0.f}), "positions outside stage bounds are rejected");

    const xm::Model* models[4]{};
    xm::Controller* anims[4]{};
    gameplay::MatchConfig config;
    config.spawn[0] = {-100.f, 200.f, -100.f}; // original env slot 0 (blue)
    config.spawn[1] = {100.f, 200.f, 100.f};   // original env slot 2 (red in 1v1)
    // AGENTS rule 7: this match is damaged and stepped, so it is equipped. Static so the
    // combo outlives the match, which copies the config's pointers.
    static const test::synthetic::Combo combo;
    combo.bind(config, 2);
    gameplay::Match match;
    match.reset(config, models, anims, nullptr, nullptr, &collision);
    near(-100.f, match.fighter(0).position().x, 0.1f, "blue fighter retains original slot 0 X");
    near(-100.f, match.fighter(0).position().z, 0.1f, "blue fighter retains original slot 0 Z");
    near(100.f, match.fighter(1).position().x, 0.1f, "red fighter retains original slot 2 X");
    near(100.f, match.fighter(1).position().z, 0.1f, "red fighter retains original slot 2 Z");
    near(0.f, match.fighter(0).position().y, 0.1f, "env spawn height projects onto ground");

    const glm::vec3 invalidCandidates[2] = {{nan, nan, nan}, {150.f, 200.f, 150.f}};
    const glm::vec3 recovered = collision.resolveSpawn(invalidCandidates[0], invalidCandidates, 2);
    check(collision.validPosition(recovered), "invalid spawn recovers to a valid stage point");
    near(150.f, recovered.x, 0.1f, "invalid spawn uses nearest valid env slot X");
    near(150.f, recovered.z, 0.1f, "invalid spawn uses nearest valid env slot Z");

    // A clean KO: damage equal to the HP pool, so the recovered overkill term is 0 and
    // the balloon stays under its LIMIT (a 1000-point hit would be a tenfold overkill
    // and legitimately bursts — FUN_00639160 @0x6393a5 divides by 1000 with no cap).
    match.fighter(0).take_damage(match.fighter(0).max_hp());
    match.step(nullptr, nullptr, gameplay::FixedStep::seconds);
    const gameplay::MatchFrame respawn = match.step(nullptr, nullptr, 10.0);
    check(respawn.respawned[0], "KO respawn fires through the match economy");
    near(-100.f, match.fighter(0).position().x, 0.1f,
         "respawn keeps the fighter's original slot X");
    near(-100.f, match.fighter(0).position().z, 0.1f,
         "respawn keeps the fighter's original slot Z");
    near(gameplay::FighterConstants::kRespawnAirY, match.fighter(0).position().y, 0.1f,
         "respawn re-enters at the recovered air height ([fighter+0x18] = 1000.0f, "
         "FUN_00421bd0 @0x421c62-0x421c65)");
    check(match.fighter(0).airborne(), "the respawn re-entry is airborne");
    check(match.fighter(0).respawn_locked(),
          "the respawn re-entry is not targetable until it lands ([fighter+0xaecb])");
    check(match.fighter(0).hp() == match.fighter(0).max_hp(), "the respawn restores HP");
    for (int i = 0; i < 300 && match.fighter(0).airborne(); ++i)
        match.step(nullptr, nullptr, gameplay::FixedStep::seconds);
    check(!match.fighter(0).airborne(), "the respawned fighter falls back onto the stage");
    check(!match.fighter(0).respawn_locked(), "the respawn lock ends on landing");
    near(0.f, match.fighter(0).position().y, 0.1f, "landed on the stage floor");
}

int32_t readI32(const std::array<uint8_t, 0x54>& bytes, size_t offset) {
    return static_cast<int32_t>(static_cast<uint32_t>(bytes[offset]) |
        (static_cast<uint32_t>(bytes[offset + 1]) << 8) |
        (static_cast<uint32_t>(bytes[offset + 2]) << 16) |
        (static_cast<uint32_t>(bytes[offset + 3]) << 24));
}

void testInstalledStages(const std::filesystem::path& dataRoot) {
    std::puts("\n== installed stage collision channels and original env slots ==");
    for (const char* stageName : {"stage01", "stage04", "stage06", "stage15", "stage21"}) {
        const std::filesystem::path directory = dataRoot / stageName;
        std::filesystem::path collisionPath;
        for (const char* file : {"collision.X", "collision.x"}) {
            const auto candidate = directory / file;
            if (std::filesystem::exists(candidate)) { collisionPath = candidate; break; }
        }
        const auto envPath = directory / "env.dat";
        std::array<uint8_t, 0x54> env{};
        std::ifstream input(envPath, std::ios::binary);
        input.read(reinterpret_cast<char*>(env.data()), static_cast<std::streamsize>(env.size()));
        if (collisionPath.empty() || input.gcount() != static_cast<std::streamsize>(env.size())) {
            check(false, (std::string(stageName) + " assets available for collision check").c_str());
            continue;
        }
        xm::Model model = xm::loadFile(collisionPath.string());
        game::physics::MovementCollision collision;
        collision.setMeshes(&model, &model);
        check(!collision.empty(), (std::string(stageName) + " movement/ground mesh parsed").c_str());
        for (int slot : {0, 2}) {
            const size_t offset = 0x24 + static_cast<size_t>(slot) * 12;
            const glm::vec3 spawn(static_cast<float>(readI32(env, offset)),
                                  static_cast<float>(readI32(env, offset + 4)),
                                  static_cast<float>(readI32(env, offset + 8)));
            const auto ground = collision.groundAt(spawn.x, spawn.z, spawn.y, 50.f, 1000.f);
            const glm::vec3 resolved = collision.resolveSpawn(spawn);
            const bool sameSlot = std::abs(resolved.x - spawn.x) < 1.f &&
                                  std::abs(resolved.z - spawn.z) < 1.f;
            check(ground.hit && sameSlot && collision.validPosition(resolved),
                  (std::string(stageName) + " original env spawn slot " + std::to_string(slot)).c_str());
        }
    }
}

// Issue #30's sweep prune must never drop a hit the unpruned walk would take. The failing
// case is a ray that lands exactly on a bounds CORNER: the two slab parameters are equal in
// exact arithmetic but are reached through different reciprocals per axis, so a 1-ulp
// disagreement empties the interval. Without the slack term in sweepReachesBounds the sweep
// stops a full kWallSkin short of the wall here (x = 80 against 78.0082). Measured with the
// differential harness: 6 mismatches over 469,090 trials, all of this class.
void testCornerGrazeIsNotPruned() {
    xm::Model model = flatStage();
    xm::Mesh& mesh = model.meshes[0];
    addQuad(mesh, {100.f, 0.f, -200.f}, {100.f, 0.f, 300.f},
            {100.f, 200.f, 300.f}, {100.f, 200.f, -200.f});

    game::physics::MovementCollision collision;
    collision.setMeshes(&model, &model);

    const game::physics::MovementResult hit =
        collision.move({25.f, 100.f, 125.f}, {300.f, 100.f, 100.f}, false);
    check(hit.position.x < 79.f,
          "a sweep landing on a bounds corner is not pruned (issue #30)");
    check(hit.hitWall, "and it still reports the wall");
    std::printf("        corner graze: position.x = %.7f (unpruned walk gives 78.0082169)\n",
                static_cast<double>(hit.position.x));
}

}  // namespace

int main(int argc, char** argv) {
    testFlatAndGround();
    testSweepsAndFighterLanding();
    testSpawnAndRecovery();
    testCornerGrazeIsNotPruned();
    if (argc > 1) testInstalledStages(argv[1]);
    std::printf("\nSTAGE_MOVEMENT: %s (%d checks, %d failed)\n",
                failures == 0 ? "ok" : "FAIL", checks, failures);
    return failures == 0 ? 0 : 1;
}
