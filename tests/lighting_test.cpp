// tests/lighting_test.cpp — device-free test for the scene renderer's fixed-function
// lighting constants and the arithmetic they feed.
//
// Build from the repo root (glm from third_party, plus the fetched webgpu.h: the header
// that carries these constants is a WebGPU consumer, so it pulls webgpu.h even though
// this test never creates a device or a texture). The webgpu include dir is the one the
// build already fetched; on a Linux tree it is:
//   g++ -std=c++23 -O2 -Wall -Wextra
//       -I src -I src/assets
//       -I third_party/glm
//       -I build/linux/_deps/wgpu-linux-x86_64-release-src/include
//       tests/lighting_test.cpp -o /tmp/lighting_test
//   /tmp/lighting_test
//
// What this pins, all of it read off remake/src/core/scenes.cpp:736-769 (the DX9
// gameplay state block the banked reference frames were rendered with):
//   1. the four light constants and the clear colour, value for value;
//   2. the two derived quantities the shader depends on — the normalised light vector,
//      hence N.L = 0.816497 for the stage's +Y ground, and the pre-summed ambient 0.55
//      that Ca multiplies once;
//   3. the equation itself against a number measured on the banked frame: stage21's
//      ground (N.L = 0.816497, baked vertex colour 0.244) renders at 0.719 of its texel
//      in the DX9 frame, and 0.55 + 0.85*N.L*vcol reproduces that to 1e-3 — while the
//      constants this track replaced land at 1.166 and putting the vertex colour on the
//      ambient term too lands at 0.304, so a regression to either fails here instead of
//      costing another 480000-pixel comparison to notice.
//
// What this does NOT prove: that the WGSL evaluates this arithmetic. There is no
// device-free way to execute the shader, and this test reads no GPU state — it pins the
// CPU side, which is where the values drifted unnoticed the first time.
//
// Exit status: 0 when every check passed, 1 otherwise.

#include "render/scene_renderer.h"

#include <cmath>
#include <cstdio>
#include <string>

namespace {

int g_checks   = 0;
int g_failures = 0;

std::string f2s(float v) {
    char b[32];
    std::snprintf(b, sizeof b, "%.6f", static_cast<double>(v == 0.f ? 0.f : v));
    return b;
}
std::string v3s(const glm::vec3& v) {
    return "(" + f2s(v.x) + ", " + f2s(v.y) + ", " + f2s(v.z) + ")";
}

void section(const char* s) { std::printf("\n%s\n", s); }
void info(const std::string& s) { std::printf("  --   %s\n", s.c_str()); }

void check(bool ok, const std::string& what, const std::string& got, const std::string& want) {
    ++g_checks;
    if (ok) {
        std::printf("  ok   %-46s %s\n", what.c_str(), got.c_str());
    } else {
        ++g_failures;
        std::printf("  FAIL %-46s got %s, want %s\n", what.c_str(), got.c_str(), want.c_str());
    }
}
void checkNear(float got, float want, float tol, const std::string& what) {
    check(std::fabs(got - want) <= tol, what, f2s(got), f2s(want) + " +/- " + f2s(tol));
}

// ---------------------------------------------------------------------------------------
// The light the DX9 gameplay pass installs (scenes.cpp:745-769)
// ---------------------------------------------------------------------------------------
void lightConstantCases() {
    section("light 0, D3DLIGHT_DIRECTIONAL (scenes.cpp:764-767)");
    info("Direction is the authored vector; D3D normalises it for the N.L dot product,");
    info("which is why the renderer normalises on upload instead of trusting the asset.");

    const glm::vec3 wantDir(0.5f, -1.0f, 0.5f);
    check(render::kLightDirection == wantDir, "kLightDirection == (0.5, -1, 0.5)",
          v3s(render::kLightDirection), v3s(wantDir));
    checkNear(render::kLightDiffuse, 0.85f, 0.f, "kLightDiffuse == 0.85 (scenes.cpp:765)");
    checkNear(render::kLightAmbient, 0.20f, 0.f, "kLightAmbient == 0.20 (scenes.cpp:766)");
    checkNear(render::kGlobalAmbient, 0.35f, 0.f, "kGlobalAmbient == 0.35 (scenes.cpp:746)");
}

// ---------------------------------------------------------------------------------------
// Derived quantities the shader evaluates: the normalised key, and Ga + La
// ---------------------------------------------------------------------------------------
void derivedCases() {
    section("derived terms");

    const glm::vec3 l = glm::normalize(-render::kLightDirection);   // vertex -> light
    // 1/sqrt(2.25) = 0.666667 per component on x/z, 0.816497 on y.
    checkNear(l.x, -0.408248f, 1e-6f, "normalised light x");
    checkNear(l.y, 0.816497f, 1e-6f, "normalised light y");
    checkNear(l.z, -0.408248f, 1e-6f, "normalised light z");

    // The stage's ground is +Y, so its N.L is the light's y — the number every ground
    // factor below is built from.
    const float ndl = glm::dot(glm::vec3(0.f, 1.f, 0.f), l);
    checkNear(ndl, 0.816497f, 1e-6f, "ground (+Y) N.L");

    const float ambientSum = render::kGlobalAmbient + render::kLightAmbient;
    checkNear(ambientSum, 0.55f, 0.f, "Ca multiplier: Ga + La == 0.55");
}

// ---------------------------------------------------------------------------------------
// The equation, against the factor measured on the banked DX9 frame
// ---------------------------------------------------------------------------------------
void equationCases() {
    section("lit = Ca*(Ga + La) + Cd*Ld*saturate(N.L), fitted to the banked frame");

    const glm::vec3 l = glm::normalize(-render::kLightDirection);
    const float ndl = glm::dot(glm::vec3(0.f, 1.f, 0.f), l);
    const float ambientSum = render::kGlobalAmbient + render::kLightAmbient;

    // stage21's ground: baked vertex colour 0.244 (the mesh's own COLOR1, which is the
    // diffuse material source), material ambient/diffuse white. The DX9 frame measures
    // 0.719 there — dx9/texel over 83k pixels of that mesh, fitted per pixel.
    const float vcol = 0.244f;
    const float fitted = ambientSum + render::kLightDiffuse * ndl * vcol;
    checkNear(fitted, 0.719f, 1e-3f, "ground factor reproduces the measured 0.719");

    // The two ways this went wrong before, both asserted as wrong:
    //   * the replaced constants (ambient 0.35+0.36+0.40 tints, light colour 1.0) gave
    //     1.166 for the same surface — the 2.7x-dark stage;
    //   * putting the vertex colour on the whole lit term instead of the diffuse term
    //     gives 1.244*vcol = 0.303.
    const float replaced = 0.35f + 1.0f * ndl;              // old ambient + |N.L| light
    const float vcolEverywhere = (ambientSum + render::kLightDiffuse * ndl) * vcol;
    check(std::fabs(replaced - 0.719f) > 0.4f, "replaced constants do NOT fit (1.166)",
          f2s(replaced), "far from 0.719");
    check(std::fabs(vcolEverywhere - 0.719f) > 0.4f, "vcol on the ambient term does NOT fit",
          f2s(vcolEverywhere), "far from 0.719");
}

// ---------------------------------------------------------------------------------------
// The clear colour (scenes.cpp:736-737)
// ---------------------------------------------------------------------------------------
void clearColourCases() {
    section("D3DCOLOR_XRGB(40, 42, 54) clear (scenes.cpp:736)");
    check(render::kClearRed == 40, "kClearRed == 40", std::to_string(render::kClearRed), "40");
    check(render::kClearGreen == 42, "kClearGreen == 42",
          std::to_string(render::kClearGreen), "42");
    check(render::kClearBlue == 54, "kClearBlue == 54",
          std::to_string(render::kClearBlue), "54");
}

// ---------------------------------------------------------------------------------------
// The stage mip chain (scene_renderer.h's buildMipChain / mipLevelCount)
//
// Why these values: the sampler now advertises `mipmapFilter: linear` on a chain this
// renderer generates, so a wrong level count or a filter that mishandles non-power-of-two
// art changes every minified pixel in a frame — and nothing else in the test suite is
// device-free enough to notice. The reference's own chains are 3 levels for a 128x128
// stage texture (X.cnv + X_1.cnv + X_2.cnv, shipped art the asset layer does not expose
// here); this renderer uploads the full chain instead, which is the standard rule.
// ---------------------------------------------------------------------------------------
void mipChainCases() {
    section("mipLevelCount — full chain, floor(log2(max)) + 1");

    check(render::mipLevelCount(1, 1) == 1, "1x1 -> 1 level", std::to_string(render::mipLevelCount(1, 1)), "1");
    check(render::mipLevelCount(128, 128) == 8, "128x128 -> 8 levels", std::to_string(render::mipLevelCount(128, 128)), "8");
    // A 128x128 stage texture ships 3 levels as art; the generated chain goes further,
    // which only matters past the point the reference would have clamped anyway.
    info("reference chain depth for a 128x128 stage texture is 3 (shipped X_1/X_2)");
    check(render::mipLevelCount(256, 128) == 9, "256x128 -> 9 (max dimension)", std::to_string(render::mipLevelCount(256, 128)), "9");
    check(render::mipLevelCount(300, 200) == 9, "300x200 (NPOT) -> 9", std::to_string(render::mipLevelCount(300, 200)), "9");
    check(render::mipLevelCount(0, 4) == 1, "empty dimension -> 1", std::to_string(render::mipLevelCount(0, 4)), "1");

    section("buildMipChain — level 0 byte-identical, then 2x2 box averages");

    // A 4x4 grey ramp: level 1's first texel averages 0,1,4,5 = 10 -> (10+2)/4 = 3.
    std::vector<uint8_t> img((size_t)4 * 4 * 4);
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            uint8_t* t = img.data() + ((size_t)y * 4 + x) * 4;
            t[0] = (uint8_t)(y * 4 + x);
            t[1] = (uint8_t)(255 - (y * 4 + x));
            t[2] = 7;
            t[3] = (uint8_t)(y * 4 + x);
        }
    }
    std::vector<std::vector<uint8_t>> levels;
    render::buildMipChain(img.data(), 4, 4, levels);
    check(levels.size() == 3, "4x4 -> 3 levels", std::to_string(levels.size()), "3");
    check(levels[0] == img, "level 0 is the uploaded image verbatim",
          std::to_string(levels[0].size()) + " B", std::to_string(img.size()) + " B");
    check(levels[1].size() == (size_t)2 * 2 * 4, "level 1 is 2x2", std::to_string(levels[1].size()), "16");
    check(levels[2].size() == (size_t)1 * 1 * 4, "level 2 is 1x1", std::to_string(levels[2].size()), "4");
    check(levels[1][0] == 3, "level 1 texel 0: mean(0,1,4,5) rounds half up to 3",
          std::to_string(levels[1][0]), "3");
    // The green channel is the same ramp inverted: mean(255,254,251,250) = 252.5 -> 253.
    check(levels[1][1] == 253, "level 1 texel 1: the 255-ramp green averages to 253",
          std::to_string(levels[1][1]), "253");
    check(levels[1][3] == 3, "level 1 alpha mirrors the red ramp", std::to_string(levels[1][3]), "3");
    check(levels[2][2] == 7, "level 2 keeps the constant channel", std::to_string(levels[2][2]), "7");

    // Odd dimensions drop the remainder column/row rather than averaging a phantom
    // neighbour: a 3x3 of distinct bytes averages exactly the top-left 2x2.
    std::vector<uint8_t> odd((size_t)3 * 3 * 4, 0);
    for (size_t i = 0; i < 9; ++i)
        for (int c = 0; c < 4; ++c) odd[i * 4 + c] = (uint8_t)(10 * (int)i);
    render::buildMipChain(odd.data(), 3, 3, levels);
    check(levels.size() == 2, "3x3 -> 2 levels", std::to_string(levels.size()), "2");
    check(levels[1].size() == 4, "3x3 -> 1x1", std::to_string(levels[1].size()), "4");
    check(levels[1][0] == (0 + 10 + 30 + 40 + 2) / 4, "3x3 keeps the top-left 2x2 only (20)",
          std::to_string(levels[1][0]), std::to_string((0 + 10 + 30 + 40 + 2) / 4));

    // Guardships: an empty image yields no levels instead of a bad allocation.
    render::buildMipChain(nullptr, 8, 8, levels);
    check(levels.empty(), "null image -> no levels", std::to_string(levels.size()), "0");
    render::buildMipChain(img.data(), 0, 8, levels);
    check(levels.empty(), "zero width -> no levels", std::to_string(levels.size()), "0");

    section("mipSiblingName / mipShippedDimsOk — the shipped-level substitution rule");

    // FUN_00656c80's %s_%d.bmp walk starts at _1: the name surgery only touches
    // the ASCII tail, so Shift-JIS stems survive byte-identical.
    check(render::mipSiblingName("wall.bmp", 1) == "wall_1.bmp", "wall.bmp level 1 -> wall_1.bmp",
          render::mipSiblingName("wall.bmp", 1), "wall_1.bmp");
    check(render::mipSiblingName("wall.bmp", 2) == "wall_2.bmp", "wall.bmp level 2 -> wall_2.bmp",
          render::mipSiblingName("wall.bmp", 2), "wall_2.bmp");
    check(render::mipSiblingName("noext", 1) == "noext_1", "extensionless name takes the suffix bare",
          render::mipSiblingName("noext", 1), "noext_1");
    check(render::mipSiblingName("", 1).empty(), "empty name -> empty sibling",
          std::to_string(render::mipSiblingName("", 1).size()), "0");
    check(render::mipSiblingName("wall.bmp", 0).empty(), "level 0 is never a sibling",
          std::to_string(render::mipSiblingName("wall.bmp", 0).size()), "0");

    // The FUN_00656c80 width gate: exactly the halved dims (floor, min 1), else
    // the box level stays. stage01's survey: all 85 _1 and 57/58 _2 match; the
    // one _2 sized like a _1 (64x64 base, 32x32 _2) must not substitute.
    check(render::mipShippedDimsOk(256, 256, 128, 128, 1), "256 -> 128 at level 1",
          "true", "true");
    check(render::mipShippedDimsOk(256, 256, 64, 64, 2), "256 -> 64 at level 2",
          "true", "true");
    check(!render::mipShippedDimsOk(64, 64, 32, 32, 2), "64 -> 32 at level 2 rejected (wants 16)",
          "false", "false");
    check(!render::mipShippedDimsOk(256, 256, 128, 128, 2), "level-1 dims rejected at level 2",
          "false", "false");
    check(!render::mipShippedDimsOk(256, 256, 127, 128, 1), "off-by-one width rejected",
          "false", "false");
    check(render::mipShippedDimsOk(3, 3, 1, 1, 1), "odd dims floor-halve (3 -> 1)",
          "true", "true");
    check(!render::mipShippedDimsOk(256, 256, 0, 128, 1), "empty sibling rejected",
          "false", "false");
}

}  // namespace

int main() {
    lightConstantCases();
    derivedCases();
    equationCases();
    clearColourCases();
    mipChainCases();

    std::printf("\nchecks=%d failures=%d\n", g_checks, g_failures);
    std::printf("LIGHTING: %s\n", g_failures == 0 ? "ok" : "FAIL");
    return g_failures == 0 ? 0 : 1;
}
