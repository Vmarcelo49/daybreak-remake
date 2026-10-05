// =============================================================================
//  animation_pose_test.cpp — the .X animation path against the shipped rigs.
//
//  Device-free on purpose: links only glm and defines XMODEL_IMPLEMENTATION
//  itself, like raycast_analytic and fighter_script_test (linking
//  foundation_assets as well would be a duplicate-definition error).
//
//  Run from the repo root, or point it at an install:
//
//      GAME_DIR=Higurashi-Daybreak ./animation_pose_test
//      ./animation_pose_test <game_dir> <repo_dir>
//
//  What it proves, for real shipped .X files:
//   1. Set ordering and key goldens for data/rika/01.X, all traceable to the
//      file's own text (xm::LoadOptions::convertedTextOut emits it):
//        * Model::anims[0] is the file's LAST AnimationSet, "Anim-124". The
//          reference enumerates sets in reverse file order: the Microsoft
//          d3dx9_25.dll the original ships (native under Wine) answers
//          GetAnimationSet(0) = "Anim-124" and set i = file set (N-1-i) for all
//          124 sets, on the same file the same DLL reports 4800 source ticks/s
//          and the same per-key S/R/T this loader derives. Bootstrap order, not
//          key interpretation, was the divergence — in file order index 0 was a
//          170-degree rigid root flip and tumbled every animated model.
//        * the animation's first key IS the root frame's FrameTransformMatrix,
//          so the pose at t=0 equals the bind pose on every frame;
//        * the root's key at tick 80 and the composed world positions of two
//          named bones match the key matrices written in the .X text.
//   2. Pose invariants over every shipped character rig the test can find
//      (data/<name>/<NN>.X with a skinned mesh): upper bone above the root in
//      Y, skeleton Y extent a sane factor of the bind pose's, no frame's world
//      matrix a reflection, root world translation anchored to the bind root
//      and near the arena origin in X/Z — sampled across the default set.
//   3. SKIP cleanly when the game data is absent, so the suite stays runnable
//      on a checkout without an install.
//
//  Final line: "ANIMATION_POSE: ok" or "ANIMATION_POSE: FAIL (n ...)".
//  Exit code 0 on ok/skip, 1 on any mismatch.
// =============================================================================
#define XMODEL_IMPLEMENTATION
#include "assets/xmodel.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace {

int g_failures = 0;

void fail(const std::string& msg) {
    std::printf("  FAIL: %s\n", msg.c_str());
    ++g_failures;
}

// Expected-vs-got, so a failure prints the numbers that decide it.
void expectNear(const std::string& what, float got, float want, float eps) {
    const float d = std::fabs(got - want);
    if (d > eps) {
        char buf[256];
        std::snprintf(buf, sizeof buf, "%s: got %.6f want %.6f (|d|=%.6g > %g)", what.c_str(), got,
                      want, (double)d, (double)eps);
        fail(buf);
    }
}

void expectMat3(const std::string& what, const glm::mat3& got, const float fileRows[3][3],
                float eps) {
    // The loader reads the .X matrix floats in file order into glm's [column][row]
    // storage, so the text's element F[i][j] lands in got[i][j] — and as a linear map
    // got is the transpose of the file's row-vector matrix, which is what composes
    // with world = parent * local. Compared element-wise, the indices line up.
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            char buf[160];
            std::snprintf(buf, sizeof buf, "%s[%d][%d]", what.c_str(), i, j);
            expectNear(buf, got[i][j], fileRows[i][j], eps);
        }
}

fs::path findRepoRoot(fs::path start) {
    std::error_code ec;
    for (int depth = 0; depth < 12 && !start.empty(); ++depth) {
        if (fs::exists(start / "remake" / "foundation" / "src" / "assets" / "xmodel.h", ec))
            return start;
        const fs::path parent = start.parent_path();
        if (parent == start) break;
        start = parent;
    }
    return {};
}

struct PoseStats {
    float maxRootDrift = 0.f;   // |root world T - bind root world T|
    float maxAbsX = 0.f, maxAbsZ = 0.f;
    float minUpAboveRoot = 1e30f;
    float extY = 0.f, bindExtY = 0.f;
    float minDet = 1e30f;
    int   minDetFrame = -1;
    float maxBindDeltaAtT0 = 0.f;
};

// One model: load, check index 0 against the bind pose, then the invariants over
// the default set's duration.
bool checkModel(const fs::path& file, PoseStats& stats, std::string& error) {
    xm::Model model;
    try {
        model = xm::loadFile(file.string(), xm::LoadOptions{});
    } catch (const std::exception& e) {
        error = std::string("load threw: ") + e.what();
        return false;
    }
    bool skinned = false;
    for (const xm::Mesh& m : model.meshes)
        if (m.skinned && !m.bones.empty()) skinned = true;
    if (!skinned) return false;                      // not a character rig
    if (model.anims.empty() || model.anims[0].duration <= 0.f) return false;
    if (model.frames.empty()) { error = "no frames"; return false; }

    // Runtime move selection is verified against each fighter's bound NN.dat in
    // melee_rules_test. This test focuses on .X ordering and pose invariants.

    std::vector<glm::mat4> bind, world;
    model.evalPose(nullptr, 0.f, false, bind);
    model.evalPose(&model.anims[0], 0.f, false, world);

    // The reference's set 0 opens on the bind pose: its first key is the same
    // matrix as the frame's own FrameTransformMatrix (see the goldens below).
    for (size_t i = 0; i < model.frames.size(); ++i)
        stats.maxBindDeltaAtT0 = std::max(
            stats.maxBindDeltaAtT0, glm::length(glm::vec3(world[i][3] - bind[i][3])));

    // Upper bone: the rig's head when it has one, else the highest bind frame.
    int upper = model.findFrame("Bip01_Head");
    if (upper < 0) {
        float best = -1e30f;
        for (size_t i = 0; i < bind.size(); ++i)
            if (bind[i][3].y > best) { best = bind[i][3].y; upper = (int)i; }
    }
    float bindMinY = 1e30f;
    for (const glm::mat4& b : bind) bindMinY = std::min(bindMinY, b[3].y);
    for (const glm::mat4& b : bind)
        stats.bindExtY = std::max(stats.bindExtY, b[3].y - bindMinY);

    const float durationSec = model.anims[0].duration / model.ticksPerSecond;
    const int samples = 8;
    for (int s = 0; s <= samples; ++s) {
        model.evalPose(&model.anims[0], durationSec * (float)s / (float)samples, false, world);
        const glm::vec3 rootT(world[0][3]);
        stats.maxRootDrift = std::max(stats.maxRootDrift, glm::length(rootT - glm::vec3(bind[0][3])));
        stats.maxAbsX = std::max(stats.maxAbsX, std::fabs(rootT.x));
        stats.maxAbsZ = std::max(stats.maxAbsZ, std::fabs(rootT.z));
        stats.minUpAboveRoot =
            std::min(stats.minUpAboveRoot, world[(size_t)upper][3].y - rootT.y);
        float minY = 1e30f, maxY = -1e30f;
        for (size_t i = 0; i < world.size(); ++i) {
            minY = std::min(minY, world[i][3].y);
            maxY = std::max(maxY, world[i][3].y);
            const float det = glm::determinant(glm::mat3(world[i]));
            if (det < stats.minDet) { stats.minDet = det; stats.minDetFrame = (int)i; }
        }
        stats.extY = std::max(stats.extY, maxY - minY);
    }
    return true;
}

}  // namespace

int main(int argc, char** argv) {
    const char* envRepo = std::getenv("REPO_DIR");
    const char* envGame = std::getenv("GAME_DIR");
    fs::path repo = argc > 2 ? fs::path(argv[2])
                             : (envRepo ? fs::path(envRepo) : findRepoRoot(fs::current_path()));
    if (repo.empty()) repo = findRepoRoot(fs::absolute(argv[0]).parent_path());
    if (repo.empty()) repo = fs::current_path();
    const fs::path game = argc > 1 ? fs::path(argv[1])
                                   : (envGame ? fs::path(envGame) : repo / "Higurashi-Daybreak");
    const fs::path data = game / "data";

    std::printf("animation_pose_test: repo=%s game=%s\n", repo.string().c_str(),
                game.string().c_str());

    std::error_code ec;
    if (!fs::is_directory(data, ec)) {
        std::printf("SKIP: no game data at %s (set GAME_DIR or pass <game_dir> <repo_dir>)\n",
                    data.string().c_str());
        std::printf("ANIMATION_POSE: ok\n");
        return 0;
    }

    // ---------------------------------------------------------------- goldens
    // data/rika/01.X, cited from the loader's own converted text:
    //   * "AnimationSet Anim-124" is the file's last set (39 channels, 110 keys
    //     spaced 80 ticks, last at 8720).
    //   * its "Animation Anim-Bip00" key at 0 is byte-identical to the
    //     FrameTransformMatrix of "Frame Bip00" at the top of the file.
    //   * its key at 80 stores the row-vector matrix
    //       -0.000339723862, 0.37944597,  -0.925213814, 0,
    //       -0.106389552,   0.919949174,  0.377325892, 0,
    //        0.994324446,   0.0985612646, 0.0400565453, 0,
    //        1.18313444,   60.3249512,    0.396200538, 1
    const fs::path rika = data / "rika" / "01.X";
    if (fs::exists(rika, ec)) {
        xm::Model model;
        bool loaded = true;
        try {
            model = xm::loadFile(rika.string(), xm::LoadOptions{});
        } catch (const std::exception& e) {
            loaded = false;
            fail(std::string("loading ") + rika.string() + " threw: " + e.what());
        }
        if (!loaded) {
            std::printf("ANIMATION_POSE: FAIL (%d check%s)\n", g_failures,
                        g_failures == 1 ? "" : "s");
            return 1;
        }
        std::printf("goldens: %s (%zu sets, reference index 0 = \"%s\", %.0f ticks)\n",
                    rika.string().c_str(), model.anims.size(),
                    model.anims.empty() ? "?" : model.anims[0].name.c_str(),
                    model.anims.empty() ? 0.f : model.anims[0].duration);
        if (model.anims.size() != 124) {
            fail("rika/01.X should have 124 animation sets");
        } else {
            if (model.anims.front().name != "Anim-124")
                fail("reference index 0 must be the file's last set \"Anim-124\", got \"" +
                     model.anims.front().name + "\"");
            if (model.anims.back().name != "Anim-1")
                fail("last index must be the file's first set \"Anim-1\", got \"" +
                     model.anims.back().name + "\"");
            expectNear("rika anims[0].duration", model.anims[0].duration, 8720.f, 0.f);
        }
        if (!model.anims.empty() && model.anims[0].duration > 0.f) {
            const xm::AnimSet& set = model.anims[0];
            std::vector<glm::mat4> bind, world;
            model.evalPose(nullptr, 0.f, false, bind);
            model.evalPose(&set, 0.f, false, world);
            float worst = 0.f;
            for (size_t i = 0; i < bind.size(); ++i)
                worst = std::max(worst, glm::length(glm::vec3(world[i][3] - bind[i][3])));
            std::printf("  t=0 vs bind: max |dT| = %.6f (want ~0: key 0 is the bind matrix)\n",
                        worst);
            expectNear("pose(t=0) == bind pose", worst, 0.f, 1e-2f);

            // Root key at tick 80, straight from the text above.
            const float rows80[3][3] = {{-0.000339723862f, 0.37944597f, -0.925213814f},
                                        {-0.106389552f, 0.919949174f, 0.377325892f},
                                        {0.994324446f, 0.0985612646f, 0.0400565453f}};
            model.evalPose(&set, 80.f / model.ticksPerSecond, false, world);
            const glm::vec3 rootT(world[0][3]);
            std::printf("  tick 80 root T: got (%.6f %.6f %.6f) want (1.183134 60.324951 "
                        "0.396201)\n",
                        rootT.x, rootT.y, rootT.z);
            expectNear("root T.x @80", rootT.x, 1.18313444f, 1e-4f);
            expectNear("root T.y @80", rootT.y, 60.3249512f, 1e-4f);
            expectNear("root T.z @80", rootT.z, 0.396200538f, 1e-4f);
            expectMat3("root R @80", glm::mat3(world[0]), rows80, 1e-5f);

            // Two named bones, composed through the Frame hierarchy: at t=0 they
            // sit where the bind chain puts them, and at tick 4000 they follow
            // the text's Anim-124 keys (the head key is "Anim-Bip01_Head").
            struct BoneGolden { const char* name; int tick; float x, y, z; float eps; };
            const BoneGolden bones[] = {
                {"Bip01_Head", 0, -2.823842f, 95.057449f, 4.141029f, 1e-3f},
                {"Bip00_L_Foot", 0, 11.197368f, 13.706257f, 2.571085f, 1e-3f},
                {"Bip01_Head", 4000, 5.417700f, 94.475822f, 6.808473f, 1e-2f},
            };
            for (const BoneGolden& g : bones) {
                const int f = model.findFrame(g.name);
                if (f < 0) { fail(std::string("no frame ") + g.name); continue; }
                model.evalPose(&set, (float)g.tick / model.ticksPerSecond, false, world);
                const glm::vec3 t(world[(size_t)f][3]);
                char what[128];
                std::snprintf(what, sizeof what, "%s world T @%d", g.name, g.tick);
                std::printf("  %s: got (%.6f %.6f %.6f) want (%.6f %.6f %.6f)\n", what, t.x, t.y,
                            t.z, g.x, g.y, g.z);
                expectNear(std::string(what) + ".x", t.x, g.x, g.eps);
                expectNear(std::string(what) + ".y", t.y, g.y, g.eps);
                expectNear(std::string(what) + ".z", t.z, g.z, g.eps);
            }
        }
    } else {
        std::printf("goldens: %s absent, skipped\n", rika.string().c_str());
    }

    // ------------------------------------------------------------- invariants
    // Every shipped character rig: data/<name>/<NN>.X with a skinned mesh. The
    // thresholds are the measured envelope over the shipped install (worst case
    // in parentheses) with headroom, so a new asset cannot quietly break them.
    PoseStats stats;
    int models = 0, unreadable = 0, failedModels = 0;
    std::vector<std::string> failedNames;
    std::vector<fs::path> files;
    for (fs::directory_iterator it(data, ec), end; it != end && !ec; it.increment(ec)) {
        if (!it->is_directory()) continue;
        std::error_code ec2;
        for (fs::directory_iterator f(it->path(), ec2), fend; f != fend && !ec2; f.increment(ec2)) {
            const std::string name = f->path().filename().string();
            if (name.size() == 4 && name[2] == '.' && name[3] == 'X' &&
                std::isdigit((unsigned char)name[0]) && std::isdigit((unsigned char)name[1]))
                files.push_back(f->path());
        }
    }
    std::sort(files.begin(), files.end());

    for (const fs::path& file : files) {
        PoseStats s;
        std::string error;
        bool ok = false;
        try {
            ok = checkModel(file, s, error);
        } catch (const std::exception& e) {
            error = std::string("threw: ") + e.what();
        }
        if (!error.empty()) {
            ++unreadable;
            fail(file.filename().string() + " in " + file.parent_path().filename().string() + ": " +
                 error);
            continue;
        }
        if (!ok) continue;   // not a skinned character rig

        ++models;
        stats.maxBindDeltaAtT0 = std::max(stats.maxBindDeltaAtT0, s.maxBindDeltaAtT0);
        stats.maxRootDrift = std::max(stats.maxRootDrift, s.maxRootDrift);
        stats.maxAbsX = std::max(stats.maxAbsX, s.maxAbsX);
        stats.maxAbsZ = std::max(stats.maxAbsZ, s.maxAbsZ);
        stats.minUpAboveRoot = std::min(stats.minUpAboveRoot, s.minUpAboveRoot);
        stats.extY = std::max(stats.extY, s.extY);
        stats.bindExtY = std::max(stats.bindExtY, s.bindExtY);
        if (s.minDet < stats.minDet) { stats.minDet = s.minDet; stats.minDetFrame = s.minDetFrame; }

        // (a) reference index 0 opens on the bind pose (worst shipped rig: 0.0001 units),
        //     which is also the check that fails if the set order ever reverts to file order
        if (s.maxBindDeltaAtT0 > 0.05f) {
            ++failedModels;
            char buf[256];
            std::snprintf(buf, sizeof buf, "%s/%s: set 0 t=0 is %.4f units off the bind pose",
                          file.parent_path().filename().string().c_str(),
                          file.filename().string().c_str(), (double)s.maxBindDeltaAtT0);
            failedNames.push_back(buf);
        }
        // (b) the upper bone stays above the root (worst shipped rig: 28.8 units above)
        if (!(s.minUpAboveRoot > 0.f)) {
            ++failedModels;
            char buf[256];
            std::snprintf(buf, sizeof buf, "%s/%s: upper bone %.2f below the root",
                          file.parent_path().filename().string().c_str(),
                          file.filename().string().c_str(), (double)s.minUpAboveRoot);
            failedNames.push_back(buf);
        }
        // (c) skeleton Y extent within a sane factor of the bind pose (worst: 1.25x)
        if (!(s.extY <= 2.f * s.bindExtY && s.extY >= 0.5f * s.bindExtY)) {
            ++failedModels;
            char buf[256];
            std::snprintf(buf, sizeof buf, "%s/%s: Y extent %.1f vs bind %.1f",
                          file.parent_path().filename().string().c_str(),
                          file.filename().string().c_str(), (double)s.extY, (double)s.bindExtY);
            failedNames.push_back(buf);
        }
        // (d) no frame's world matrix is a reflection
        if (!(s.minDet > 0.f)) {
            ++failedModels;
            char buf[256];
            std::snprintf(buf, sizeof buf, "%s/%s: frame %d determinant %.4f <= 0",
                          file.parent_path().filename().string().c_str(),
                          file.filename().string().c_str(), s.minDetFrame, (double)s.minDet);
            failedNames.push_back(buf);
        }
        // (e) the root stays put: anchored to its bind position and near the arena origin
        // in X/Z. These rigs put the root at mid-height (bind y ~= 60), so "near the
        // origin" is read as X/Z plus a bind-anchored bound on the full offset.
        if (!(s.maxRootDrift <= 40.f && s.maxAbsX <= 25.f && s.maxAbsZ <= 25.f)) {
            ++failedModels;
            char buf[256];
            std::snprintf(buf, sizeof buf, "%s/%s: root drift %.2f (|x|max %.2f |z|max %.2f)",
                          file.parent_path().filename().string().c_str(),
                          file.filename().string().c_str(), (double)s.maxRootDrift,
                          (double)s.maxAbsX, (double)s.maxAbsZ);
            failedNames.push_back(buf);
        }
    }

    for (const std::string& f : failedNames) fail(f);
    std::printf("sweep: %zu candidate files, %d skinned rigs checked, %d unreadable, %d failed\n",
                files.size(), models, unreadable, failedModels);
    std::printf("  worst over all rigs: set0 t=0 off bind %.6f | root drift %.2f (|x| %.2f |z| "
                "%.2f) | upper bone above root %.2f | Y extent %.1f (bind %.1f) | min det %.4f "
                "(frame %d)\n",
                (double)stats.maxBindDeltaAtT0, (double)stats.maxRootDrift, (double)stats.maxAbsX,
                (double)stats.maxAbsZ, (double)stats.minUpAboveRoot, (double)stats.extY,
                (double)stats.bindExtY, (double)stats.minDet, stats.minDetFrame);

    if (g_failures == 0) {
        std::printf("ANIMATION_POSE: ok\n");
        return 0;
    }
    std::printf("ANIMATION_POSE: FAIL (%d check%s)\n", g_failures, g_failures == 1 ? "" : "s");
    return 1;
}
