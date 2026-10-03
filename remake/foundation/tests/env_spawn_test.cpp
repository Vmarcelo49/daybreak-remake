// =============================================================================
//  env_spawn_test.cpp — host test for the A1 spawn contract
//  (ROADMAP-PENDING.md A1; parser: src/assets/scene.h readEnv):
//  env.dat layout, the shared stage01/stage21 spawn region, and the data
//  properties the port's P1=points[0] / P2=points[1] default relies on.
//
//  Provenance: the original's reader FUN_004011f0 (fog five ints, header four
//  at file 0x14, four spawn triples at 0x24 stride 12) and its consumer
//  FUN_00423420 (verbatim 3-float copy from scene+0x44+slot*12 — no axis
//  swap, so file (a,b,c) is vec3 (x,y,z)). The slot order (P1=0, P2=1) comes
//  from the four consecutive FUN_0041dcb0 applications after
//  FUN_0064ab30 creates fighters in index order; the selection itself lives
//  in main.cpp initMatch (static, capture-pinned by BATTLE-HUD-SPEC.md §7),
//  so this test pins the data half: exact bytes through the port's parser.
//
//  Needs the game install (GAME_DIR or <game_dir> arg); skips cleanly without
//  it, following animation_pose_test. Links asset_source for readEnv's file
//  seam, like dat_bundle_bytes.
//
//    g++ -std=c++17 -Wall -Wextra -I remake/foundation/src
//        -I remake/foundation/third_party/glm
//        remake/foundation/tests/env_spawn_test.cpp
//        remake/foundation/src/assets/asset_source.cpp
//        remake/foundation/src/assets/dat_bundle.cpp
//        remake/foundation/src/assets/dat_crypto.cpp -o /tmp/env_spawn_test
//    /tmp/env_spawn_test [game_dir]       # prints ENV_SPAWN: ok|FAIL|skip
// =============================================================================

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <string>

// This TU owns the asset-stack implementations it exercises (readEnv's seam
// lives in scene.h's SCENE_IMPLEMENTATION block and parses through xmodel/cnv
// decoders), so it must not link foundation_assets — same rule as the
// XMODEL_IMPLEMENTATION tests (see CMakeLists).
#define SCENE_IMPLEMENTATION
#define XMODEL_IMPLEMENTATION
#define CNV_IMPLEMENTATION
#include "assets/scene.h"

namespace fs = std::filesystem;
namespace {

int g_checks = 0;
int g_failed = 0;

void check_int(const char* what, long long want, long long got) {
    ++g_checks;
    const bool ok = (want == got);
    if (!ok) ++g_failed;
    std::printf("  %-58s exp %-12lld got %-12lld %s\n", what, want, got, ok ? "ok" : "FAIL");
}

void check_near(const char* what, float want, float got, float tol) {
    ++g_checks;
    const bool ok = std::fabs(want - got) <= tol;
    if (!ok) ++g_failed;
    std::printf("  %-58s exp %-12.6g got %-12.6g %s\n", what, (double)want, (double)got,
                ok ? "ok" : "FAIL");
}

void check_bool(const char* what, bool want, bool got) {
    ++g_checks;
    const bool ok = (want == got);
    if (!ok) ++g_failed;
    std::printf("  %-58s exp %-12s got %-12s %s\n", what, want ? "true" : "false",
                got ? "true" : "false", ok ? "ok" : "FAIL");
}

// The four spawn triples, byte-identical in stage01 and stage21 env.dat.
const int kSpawns[4][3] = {
    {-463, 200, -2200},
    {-1363, 200, -2200},
    {-406, 200, -105},
    {-1363, 200, -105},
};

void check_stage(const char* name, const xm::StageEnv& env, int fogEnd, const int rgb[3]) {
    std::printf("== %s ==\n", name);
    check_bool("env present", true, env.present);
    check_int("fog start", 0, (long long)env.fogStart);
    check_int("fog end", fogEnd, (long long)env.fogEnd);
    check_bool("fog enabled (end > start)", true, env.fogEnabled);
    check_near("fog red", rgb[0] / 255.f, env.fogColor.r, 1e-6f);
    check_near("fog green", rgb[1] / 255.f, env.fogColor.g, 1e-6f);
    check_near("fog blue", rgb[2] / 255.f, env.fogColor.b, 1e-6f);
    const int hdr[4] = {-2264, -3406, 2900, 1393};
    for (int i = 0; i < 4; ++i) {
        char what[48];
        std::snprintf(what, sizeof what, "header[%d]", i);
        check_int(what, hdr[i], (long long)env.header[i]);
    }
    for (int i = 0; i < 4; ++i) {
        // No axis swap: the file's (a,b,c) is the vec3 (x,y,z), so the
        // shared middle value 200 is the y-up height, not a swapped z.
        char what[48];
        std::snprintf(what, sizeof what, "points[%d].x (file order kept)", i);
        check_int(what, kSpawns[i][0], (long long)std::lround(env.points[i].x));
        std::snprintf(what, sizeof what, "points[%d].y is the 200 height", i);
        check_int(what, kSpawns[i][1], (long long)std::lround(env.points[i].y));
        std::snprintf(what, sizeof what, "points[%d].z (file order kept)", i);
        check_int(what, kSpawns[i][2], (long long)std::lround(env.points[i].z));
    }
    // The pairing the defaults and the A2 sweep rely on: [0],[1] are the far
    // pair (z=-2200, P1/P2), [2],[3] the near pair (z=-105).
    check_near("far pair shares z=-2200", env.points[0].z, env.points[1].z, 1e-6f);
    check_near("near pair shares z=-105", env.points[2].z, env.points[3].z, 1e-6f);
    check_bool("far pair is two distinct points", true,
                 env.points[0].x != env.points[1].x);
}

}  // namespace

int main(int argc, char** argv) {
    const char* envGame = std::getenv("GAME_DIR");
    fs::path game;
    if (argc > 1) {
        game = fs::path(argv[1]);
    } else if (envGame) {
        game = fs::path(envGame);
    } else {
        // Like animation_pose_test: walk up from the test binary and the cwd
        // to the repo root (marked by remake/foundation), so ctest — which
        // runs from build/linux — finds the install next to the repo.
        game = fs::path("Higurashi-Daybreak");
        for (fs::path d : {fs::absolute(fs::path(argv[0])).parent_path(),
                           fs::current_path()}) {
            for (fs::path r = d; !r.empty(); r = r.parent_path()) {
                std::error_code ec2;
                if (fs::is_directory(r / "remake" / "foundation", ec2)) {
                    game = r / "Higurashi-Daybreak";
                    break;
                }
                if (r == r.parent_path()) break;
            }
            std::error_code ec2;
            if (fs::is_directory(game / "data", ec2)) break;
        }
    }
    const fs::path s01 = game / "data" / "stage01" / "env.dat";
    const fs::path s21 = game / "data" / "stage21" / "env.dat";

    std::error_code ec;
    if (!fs::is_regular_file(s01, ec) || !fs::is_regular_file(s21, ec)) {
        std::printf("SKIP: no env.dat at %s (set GAME_DIR or pass <game_dir>)\n",
                    s01.string().c_str());
        std::printf("ENV_SPAWN: ok\n");
        return 0;
    }

    xm::StageEnv e01, e21;
    xm::detail::readEnv(s01.string(), e01);
    xm::detail::readEnv(s21.string(), e21);
    // stage01 fog reaches 60000, stage21 stops at 10000; the spawn region
    // (everything from file 0x14) is shared. Tints differ per stage.
    const int rgb01[3] = {77, 100, 120};
    const int rgb21[3] = {15, 20, 50};
    check_stage("stage01", e01, 60000, rgb01);
    check_stage("stage21", e21, 10000, rgb21);

    std::printf("%d checks, %d failed\n", g_checks, g_failed);
    std::printf(g_failed ? "ENV_SPAWN: FAIL\n" : "ENV_SPAWN: ok\n");
    return g_failed ? 1 : 0;
}
