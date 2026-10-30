// =============================================================================
//  debug_prims_geometry.cpp — host test for the device-free half of
//  render/debug_prims.h: line-list -> vertex generation, colour packing, the
//  box/cross/ray helpers, and the per-frame batch's growth and reuse.
//
//  No WebGPU, no device, no window: DEBUG_PRIMS_GEOMETRY_ONLY makes the header
//  skip its pipeline half, so this compiles and runs anywhere glm does.
//
//    g++ -std=c++20 -Wall -Wextra -I src
//        -I third_party/glm
//        tests/debug_prims_geometry.cpp -o /tmp/debug_prims_geometry
//    /tmp/debug_prims_geometry        # prints DEBUG_PRIMS_GEOMETRY: ok|FAIL
//
//  Every case prints expected vs got, and any mismatch makes the exit status 1.
//  Float comparisons are exact where the arithmetic is exact by construction, and
//  tolerance-based (with the tolerance printed) where it is not.
// =============================================================================

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define DEBUG_PRIMS_GEOMETRY_ONLY
#include "render/debug_prims.h"

namespace {

using render::DebugColor;
using render::DebugLine;
using render::DebugLineBatch;
using render::DebugVertex;

int g_checks = 0;
int g_failed = 0;

void checkBool(const char* what, bool want, bool got) {
    if (want == got) {
        std::printf("  [ok]   %s: %s\n", what, got ? "true" : "false");
        ++g_checks;
    } else {
        std::printf("  [FAIL] %s: want %s, got %s\n", what, want ? "true" : "false",
                    got ? "true" : "false");
        ++g_checks;
        ++g_failed;
    }
}

void checkInt(const char* what, long long want, long long got) {
    if (want == got) {
        std::printf("  [ok]   %s = %lld\n", what, got);
        ++g_checks;
    } else {
        std::printf("  [FAIL] %s: want %lld, got %lld\n", what, want, got);
        ++g_checks;
        ++g_failed;
    }
}

// Exact float comparison, bit patterns printed on mismatch: these expectations are
// values the code must produce exactly, not approximately.
void checkFloatExact(const char* what, float want, float got) {
    if (want == got) {
        std::printf("  [ok]   %s = %.9g (%a)\n", what, (double)got, (double)got);
        ++g_checks;
    } else {
        std::printf("  [FAIL] %s: want %.9g (%a), got %.9g (%a)\n", what, (double)want,
                    (double)want, (double)got, (double)got);
        ++g_checks;
        ++g_failed;
    }
}

void checkNear(const char* what, float want, float got, float tol) {
    const float d = std::fabs(want - got);
    if (d <= tol) {
        std::printf("  [ok]   %s = %.9g (want %.9g, |diff| %.3g <= %.3g)\n", what, (double)got,
                    (double)want, (double)d, (double)tol);
        ++g_checks;
    } else {
        std::printf("  [FAIL] %s: want %.9g, got %.9g (|diff| %.3g > %.3g)\n", what, (double)want,
                    (double)got, (double)d, (double)tol);
        ++g_checks;
        ++g_failed;
    }
}

void checkVec3Exact(const char* what, const glm::vec3& want, const glm::vec3& got) {
    if (want.x == got.x && want.y == got.y && want.z == got.z) {
        std::printf("  [ok]   %s = (%.9g, %.9g, %.9g)\n", what, (double)got.x, (double)got.y,
                    (double)got.z);
        ++g_checks;
    } else {
        std::printf("  [FAIL] %s: want (%.9g, %.9g, %.9g), got (%.9g, %.9g, %.9g)\n", what,
                    (double)want.x, (double)want.y, (double)want.z, (double)got.x, (double)got.y,
                    (double)got.z);
        ++g_checks;
        ++g_failed;
    }
}

void checkColor(const char* what, DebugColor want, DebugColor got) {
    if (want == got) {
        std::printf("  [ok]   %s = 0x%08x\n", what, got);
        ++g_checks;
    } else {
        std::printf("  [FAIL] %s: want 0x%08x, got 0x%08x\n", what, want, got);
        ++g_checks;
        ++g_failed;
    }
}

void checkBytes(const char* what, const uint8_t* want, const uint8_t* got, size_t n) {
    size_t bad = n;
    for (size_t i = 0; i < n; ++i)
        if (want[i] != got[i]) {
            bad = i;
            break;
        }
    if (bad == n) {
        std::printf("  [ok]   %s: %zu bytes identical\n", what, n);
        ++g_checks;
        return;
    }
    std::printf("  [FAIL] %s: first difference at byte %zu (want 0x%02x, got 0x%02x)\n", what, bad,
                want[bad], got[bad]);
    ++g_checks;
    ++g_failed;
}

void checkVertices(const char* what, const std::vector<DebugVertex>& want,
                   const std::vector<DebugVertex>& got) {
    if (want.size() != got.size()) {
        std::printf("  [FAIL] %s: want %zu vertices, got %zu\n", what, want.size(), got.size());
        ++g_checks;
        ++g_failed;
        return;
    }
    for (size_t i = 0; i < want.size(); ++i) {
        if (want[i].pos != got[i].pos || want[i].color != got[i].color) {
            std::printf("  [FAIL] %s: vertex %zu differs (want pos (%.9g, %.9g, %.9g) col "
                        "0x%08x, got pos (%.9g, %.9g, %.9g) col 0x%08x)\n",
                        what, i, (double)want[i].pos.x, (double)want[i].pos.y,
                        (double)want[i].pos.z, want[i].color, (double)got[i].pos.x,
                        (double)got[i].pos.y, (double)got[i].pos.z, got[i].color);
            ++g_checks;
            ++g_failed;
            return;
        }
    }
    std::printf("  [ok]   %s: %zu vertices identical\n", what, got.size());
    ++g_checks;
}

bool sameBytes(const std::vector<DebugVertex>& a, const std::vector<DebugVertex>& b) {
    return a.size() == b.size() &&
           (a.empty() || std::memcmp(a.data(), b.data(), a.size() * sizeof(DebugVertex)) == 0);
}

// The one transform a debug line ever goes through is in the vertex shader:
//   out.clip = camera.viewProj * vec4<f32>(pos, 1.0);
// A host test cannot run WGSL, so this mirrors that single multiply to pin the
// convention the shader depends on: column-major (M * v, not v * M), left-handed
// view, and a 0..1 clip depth range (glm::perspectiveLH_ZO) — the same matrix
// main.cpp already hands SceneRenderer::setCamera.
glm::vec4 clipOf(const glm::mat4& viewProj, const glm::vec3& p) {
    return viewProj * glm::vec4(p, 1.f);
}

// Corner index of a box vertex, in the encoding appendBox documents: bit 0 = x high,
// bit 1 = y high, bit 2 = z high. -1 when the point is not a corner of this box.
int cornerIndex(const glm::vec3& p, const glm::vec3& lo, const glm::vec3& hi) {
    int idx = 0;
    for (int axis = 0; axis < 3; ++axis) {
        if (p[axis] == hi[axis]) idx |= 1 << axis;
        else if (p[axis] != lo[axis]) return -1;
    }
    return idx;
}

void testColorPacking() {
    std::printf("\n-- colour packing (D3DCOLOR 0xAARRGGBB, the DX9 D3DFVF_DIFFUSE value) --\n");
    checkColor("packColor(0x12,0x34,0x56,0x78)", 0x78123456u,
               render::packColor(0x12, 0x34, 0x56, 0x78));
    checkColor("packColor(0x12,0x34,0x56) defaults alpha to 0xff", 0xff123456u,
               render::packColor(0x12, 0x34, 0x56));
    checkColor("packColor(0,0,0,0)", 0x00000000u, render::packColor(0, 0, 0, 0));
    const DebugColor c = render::packColor(0xab, 0xcd, 0xef, 0x01);
    checkInt("colorR(0x01abcdef)", 0xab, render::colorR(c));
    checkInt("colorG(0x01abcdef)", 0xcd, render::colorG(c));
    checkInt("colorB(0x01abcdef)", 0xef, render::colorB(c));
    checkInt("colorA(0x01abcdef)", 0x01, render::colorA(c));
    checkColor("kWhite", 0xffffffffu, render::kWhite);
    checkColor("kRed", 0xffff0000u, render::kRed);
    checkColor("kGreen", 0xff00ff00u, render::kGreen);
    checkColor("kBlue", 0xff0000ffu, render::kBlue);
    checkColor("kYellow", 0xffffff00u, render::kYellow);
    checkColor("kCyan", 0xff00ffffu, render::kCyan);
    checkColor("kMagenta", 0xffff00ffu, render::kMagenta);
    // A D3DCOLOR value transfers unchanged, and its channels round-trip: this is the
    // property that lets a ported DX9 call site keep its literal.
    const DebugColor literal = 0x80ff8000u;
    checkColor("a D3DCOLOR literal round-trips through the channel extractors", literal,
               render::packColor(render::colorR(literal), render::colorG(literal),
                                 render::colorB(literal), render::colorA(literal)));

    // unpackColor mirrors the shader's per-channel float conversion; the WGSL
    // expression is recomputed here independently and must match bit for bit, so a
    // drift between debug_line_wgsl.h and debug_prims.h fails this test.
    const DebugColor src = render::packColor(0x12, 0x34, 0x56, 0x78);
    const uint32_t packed = src;
    const glm::vec4 wgsl((float)((packed >> 16u) & 0xFFu), (float)((packed >> 8u) & 0xFFu),
                         (float)(packed & 0xFFu), (float)((packed >> 24u) & 0xFFu));
    const glm::vec4 mirror = wgsl / 255.f;
    checkVec3Exact("unpackColor(0x78123456).rgb matches the WGSL formula",
                   glm::vec3(mirror.x, mirror.y, mirror.z), glm::vec3(render::unpackColor(src)));
    checkFloatExact("unpackColor(0x78123456).a matches the WGSL formula", mirror.w,
                    render::unpackColor(src).w);
    checkFloatExact("unpackColor(0xff0000ff).b == 1.0", 1.f, render::unpackColor(render::kBlue).b);
    checkFloatExact("unpackColor(0x00000000).rgb == 0", 0.f, render::unpackColor(0u).x);
}

void testVertexFormat() {
    std::printf("\n-- vertex format (the 16 bytes uploaded per vertex) --\n");
    checkInt("sizeof(DebugVertex)", 16, (long long)sizeof(DebugVertex));
    checkInt("offsetof(DebugVertex, pos)", 0, (long long)offsetof(DebugVertex, pos));
    checkInt("offsetof(DebugVertex, color)", 12, (long long)offsetof(DebugVertex, color));

#if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__)
    std::printf("  [skip] byte image: host is not little-endian (attribute read is LE)\n");
#else
    const DebugVertex v{glm::vec3(1.f, -2.f, 0.5f), render::packColor(0x11, 0x22, 0x33, 0x44)};
    // Hand-computed: 1.0f = 0x3F800000, -2.0f = 0xC0000000, 0.5f = 0x3F000000, all
    // little-endian. The colour is D3DCOLOR 0x44112233 (a=44 r=11 g=22 b=33), so the
    // bytes on the wire are b g r a = 33 22 11 44; a little-endian u32 read of those
    // four bytes gives 0x44112233 back, which is the value the shader's shifts unpack.
    // That endianness bridge is the whole reason the attribute is a raw u32 and not a
    // unorm8x4 (which would read memory as r g b a and swap red with blue).
    const uint8_t want[16] = {0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x00, 0xC0,
                              0x00, 0x00, 0x00, 0x3F, 0x33, 0x22, 0x11, 0x44};
    uint8_t got[16];
    std::memcpy(got, &v, sizeof got);
    checkBytes("vertex byte image (xyz f32 LE + D3DCOLOR u32 LE)", want, got, sizeof got);
#endif
}

void testLineList() {
    std::printf("\n-- line list -> vertices --\n");
    std::vector<DebugVertex> verts;
    render::appendLine(verts, glm::vec3(1.f, 2.f, 3.f), glm::vec3(-4.f, -5.f, -6.f),
                       render::kRed);
    checkInt("appendLine emits 2 vertices", 2, (long long)verts.size());
    checkVec3Exact("vertex 0 is a, verbatim", glm::vec3(1.f, 2.f, 3.f), verts[0].pos);
    checkVec3Exact("vertex 1 is b, verbatim", glm::vec3(-4.f, -5.f, -6.f), verts[1].pos);
    checkColor("vertex 0 colour", render::kRed, verts[0].color);
    checkColor("vertex 1 colour", render::kRed, verts[1].color);
    std::vector<DebugVertex> defaulted;
    render::appendLine(defaulted, glm::vec3(0.f), glm::vec3(1.f));
    checkColor("appendLine's default colour is kWhite", render::kWhite, defaulted[0].color);

    // World-space values pass through untouched: no CPU transform, no rounding.
    std::vector<DebugVertex> big;
    const glm::vec3 far(12345.678f, -0.000125f, 98765.4321f);
    render::appendLine(big, far, far, render::kGreen);
    checkVec3Exact("positions are stored unmodified (no CPU transform)", far, big[0].pos);
    checkVec3Exact("a zero-length segment keeps both identical endpoints", far, big[1].pos);

    const std::vector<DebugLine> lines = {
        {glm::vec3(0.f), glm::vec3(1.f, 0.f, 0.f), render::kRed},
        {glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f), render::kGreen},
        {glm::vec3(0.f), glm::vec3(0.f, 0.f, 1.f), render::kBlue},
    };
    std::vector<DebugVertex> expanded;
    render::appendLines(expanded, lines);
    checkInt("appendLines: 3 lines -> 6 vertices", 6, (long long)expanded.size());
    checkVec3Exact("expand keeps line order (line 2 start)", glm::vec3(0.f), expanded[4].pos);
    checkVec3Exact("expand keeps line order (line 2 end)", glm::vec3(0.f, 0.f, 1.f),
                   expanded[5].pos);
    checkColor("expand keeps per-line colour (line 2)", render::kBlue, expanded[5].color);
}

void testAabbOutline() {
    std::printf("\n-- AABB outline: 12 edges / 24 vertices --\n");
    const glm::vec3 lo(-1.f, -2.f, -3.f);
    const glm::vec3 hi(4.f, 5.f, 6.f);

    std::vector<DebugVertex> verts;
    render::appendBox(verts, lo, hi, render::kYellow);
    checkInt("appendBox emits 24 vertices", 24, (long long)verts.size());
    checkInt("appendBox emits 12 edges", 12, (long long)(verts.size() / 2));

    bool colored = true;
    bool oneAxis = true;
    int used[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int edges[12][2];
    int edgeCount = 0;
    for (size_t i = 0; i + 1 < verts.size(); i += 2) {
        if (verts[i].color != render::kYellow || verts[i + 1].color != render::kYellow)
            colored = false;
        const glm::vec3 a = verts[i].pos, b = verts[i + 1].pos;
        int differing = 0;
        if (a.x != b.x) ++differing;
        if (a.y != b.y) ++differing;
        if (a.z != b.z) ++differing;
        if (differing != 1) oneAxis = false;
        const int ia = cornerIndex(a, lo, hi), ib = cornerIndex(b, lo, hi);
        if (ia < 0 || ib < 0) oneAxis = false;
        else {
            used[ia] = 1;
            used[ib] = 1;
            if (edgeCount < 12) {
                edges[edgeCount][0] = ia < ib ? ia : ib;
                edges[edgeCount][1] = ia < ib ? ib : ia;
            }
            ++edgeCount;
        }
    }
    checkBool("every edge endpoint carries the requested colour", true, colored);
    checkBool("every edge differs in exactly one axis", true, oneAxis);
    checkInt("edges appended", 12, edgeCount);

    int covered = 0;
    for (int u : used) covered += u;
    checkInt("all 8 corners used", 8, covered);

    // The 12 cube edges, written out independently of the helper's table: bit 0 = x
    // high, bit 1 = y high, bit 2 = z high.
    const int wantEdges[12][2] = {{0, 1}, {2, 3}, {4, 5}, {6, 7}, {0, 2}, {1, 3},
                                  {4, 6}, {5, 7}, {0, 4}, {1, 5}, {2, 6}, {3, 7}};
    bool sameEdges = true;
    int present = 0;
    for (const int(&w)[2] : wantEdges) {
        bool found = false;
        for (int e = 0; e < edgeCount; ++e)
            if (edges[e][0] == w[0] && edges[e][1] == w[1]) found = true;
        if (!found) sameEdges = false;
        else ++present;
    }
    checkInt("expected cube edges present", 12, present);
    checkBool("edge set == the 12 cube edges (no duplicates, none missing)", true, sameEdges);

    // An inverted pair describes the same box; a degenerate one is 12 zero-length edges.
    std::vector<DebugVertex> inverted;
    render::appendBox(inverted, hi, lo, render::kYellow);
    checkVertices("inverted lo/hi yields the same 24 vertices", verts, inverted);

    std::vector<DebugVertex> degenerate;
    render::appendBox(degenerate, glm::vec3(7.f), glm::vec3(7.f), render::kCyan);
    checkInt("degenerate box still emits 24 vertices", 24, (long long)degenerate.size());
    bool allZeroLength = true;
    for (size_t i = 0; i + 1 < degenerate.size(); i += 2)
        if (degenerate[i].pos != degenerate[i + 1].pos) allZeroLength = false;
    checkBool("degenerate box is 12 zero-length edges (rasterises to nothing)", true,
              allZeroLength);

    std::vector<DebugVertex> repeat;
    render::appendBox(repeat, lo, hi, render::kYellow);
    checkBool("repeat generation is byte-identical", true, sameBytes(verts, repeat));
}

void testCross() {
    std::printf("\n-- cross: 3 axis segments, 6 vertices --\n");
    const glm::vec3 center(10.f, -20.f, 30.f);
    std::vector<DebugVertex> verts;
    render::appendCross(verts, center, glm::vec3(1.f, 2.f, 3.f), render::kMagenta);
    checkInt("appendCross(vec3 half) emits 6 vertices", 6, (long long)verts.size());
    checkVec3Exact("X arm start", glm::vec3(9.f, -20.f, 30.f), verts[0].pos);
    checkVec3Exact("X arm end", glm::vec3(11.f, -20.f, 30.f), verts[1].pos);
    checkVec3Exact("Y arm start", glm::vec3(10.f, -22.f, 30.f), verts[2].pos);
    checkVec3Exact("Y arm end", glm::vec3(10.f, -18.f, 30.f), verts[3].pos);
    checkVec3Exact("Z arm start", glm::vec3(10.f, -20.f, 27.f), verts[4].pos);
    checkVec3Exact("Z arm end", glm::vec3(10.f, -20.f, 33.f), verts[5].pos);
    checkColor("arms carry the requested colour", render::kMagenta, verts[5].color);

    std::vector<DebugVertex> scalar;
    render::appendCross(scalar, center, 2.f, render::kMagenta);
    checkVec3Exact("scalar half: X arm start", glm::vec3(8.f, -20.f, 30.f), scalar[0].pos);
    checkVec3Exact("scalar half: X arm end", glm::vec3(12.f, -20.f, 30.f), scalar[1].pos);
    checkVec3Exact("scalar half: Y arm end", glm::vec3(10.f, -18.f, 30.f), scalar[3].pos);
    checkVec3Exact("scalar half: Z arm end", glm::vec3(10.f, -20.f, 32.f), scalar[5].pos);
    std::vector<DebugVertex> equal;
    render::appendCross(equal, center, glm::vec3(2.f), render::kMagenta);
    checkBool("scalar overload is byte-identical to the vec3 overload", true,
              sameBytes(scalar, equal));
}

void testRay() {
    std::printf("\n-- ray: origin -> origin + dir * len --\n");
    std::vector<DebugVertex> verts;
    render::appendRay(verts, glm::vec3(0.f), glm::vec3(0.f, 0.f, 1.f), 5.f, render::kCyan);
    checkInt("unit direction emits 2 vertices", 2, (long long)verts.size());
    checkVec3Exact("origin", glm::vec3(0.f), verts[0].pos);
    checkVec3Exact("tip = origin + dir * len", glm::vec3(0.f, 0.f, 5.f), verts[1].pos);

    std::vector<DebugVertex> unnormalised;
    render::appendRay(unnormalised, glm::vec3(1.f, 1.f, 1.f), glm::vec3(3.f, 4.f, 0.f), 10.f,
                      render::kCyan);
    checkInt("non-unit direction emits 2 vertices", 2, (long long)unnormalised.size());
    // |(3,4,0)| = 5 exactly, so the scale is exactly 10/5 = 2.
    checkVec3Exact("len is a distance along dir (dir normalised first)",
                   glm::vec3(7.f, 9.f, 1.f), unnormalised[1].pos);

    std::vector<DebugVertex> diagonal;
    render::appendRay(diagonal, glm::vec3(0.f), glm::vec3(1.f, 1.f, 1.f), 1.f, render::kCyan);
    checkInt("diagonal direction emits 2 vertices", 2, (long long)diagonal.size());
    const float inv = 1.f / std::sqrt(3.f);
    checkNear("diagonal tip x = 1/sqrt(3)", inv, diagonal[1].pos.x, 1e-6f);
    checkNear("diagonal tip y = 1/sqrt(3)", inv, diagonal[1].pos.y, 1e-6f);
    checkNear("diagonal tip z = 1/sqrt(3)", inv, diagonal[1].pos.z, 1e-6f);

    checkBool("isRayDrawable(zero dir)", false, render::isRayDrawable(glm::vec3(0.f), 1.f));
    checkBool("isRayDrawable(zero len)", false, render::isRayDrawable(glm::vec3(1.f), 0.f));
    checkBool("isRayDrawable(negative len)", false, render::isRayDrawable(glm::vec3(1.f), -1.f));
    const float nan = std::nanf("");
    checkBool("isRayDrawable(NaN len)", false, render::isRayDrawable(glm::vec3(1.f), nan));
    checkBool("isRayDrawable(NaN dir)", false,
              render::isRayDrawable(glm::vec3(nan, 0.f, 0.f), 1.f));
    checkBool("isRayDrawable(inf dir)", false,
              render::isRayDrawable(glm::vec3(INFINITY, 0.f, 0.f), 1.f));
    checkBool("isRayDrawable(unit dir, positive len)", true,
              render::isRayDrawable(glm::vec3(0.f, 0.f, 1.f), 1.f));

    std::vector<DebugVertex> skipped;
    render::appendRay(skipped, glm::vec3(0.f), glm::vec3(0.f), 10.f, render::kCyan);
    render::appendRay(skipped, glm::vec3(0.f), glm::vec3(1.f, 0.f, 0.f), 0.f, render::kCyan);
    render::appendRay(skipped, glm::vec3(0.f), glm::vec3(nan, 0.f, 0.f), 1.f, render::kCyan);
    checkInt("degenerate rays append nothing", 0, (long long)skipped.size());
}

// The --hitbox-debug overlay's sphere. Device-free, like everything else here: the
// geometry half of debug_prims.h is compiled without WebGPU precisely so a debug
// primitive can be pinned on the host.
void testSphere() {
    std::printf("\n-- sphere: filled UV sphere for --hitbox-debug --\n");
    // Device-free by construction: this file compiles the geometry half of debug_prims.h
    // with no WebGPU, so a debug primitive is pinnable on the host.
    render::CubeBatch batch;
    batch.addSphere(glm::vec3(10.f, 20.f, 30.f), 30.f, render::packColor(255, 40, 40, 110), 8, 6);
    // 8 slices x 6 stacks x 6 vertices: two triangles per quad, stack-major then
    // slice-major.
    checkInt("vertex count", 8 * 6 * 6, (long long)batch.vertices().size());

    render::CubeBatch again;
    again.addSphere(glm::vec3(10.f, 20.f, 30.f), 30.f, render::packColor(255, 40, 40, 110), 8, 6);
    bool same = batch.vertices().size() == again.vertices().size();
    for (size_t i = 0; same && i < batch.vertices().size(); ++i) {
        const DebugVertex& x = batch.vertices()[i];
        const DebugVertex& y = again.vertices()[i];
        same = x.pos == y.pos && x.color == y.color;
    }
    checkBool("same arguments give a byte-identical buffer", true, same);

    bool onSurface = true;
    for (const DebugVertex& v : batch.vertices()) {
        const float dx = v.pos.x - 10.f, dy = v.pos.y - 20.f, dz = v.pos.z - 30.f;
        const float d = std::sqrt(dx * dx + dy * dy + dz * dz);
        if (std::fabs(d - 30.f) > 0.01f) onSurface = false;
    }
    checkBool("every vertex lies on the sphere surface", true, onSurface);

    // The overlay's translucency IS the alpha channel, so it has to survive.
    checkInt("alpha preserved in the vertex colour", 110,
             (long long)render::colorA(batch.vertices()[0].color));

    // Degenerate inputs ask for nothing and must emit nothing.
    render::CubeBatch empty;
    empty.addSphere(glm::vec3(0, 0, 0), 0.f, render::kRed);
    empty.addSphere(glm::vec3(0, 0, 0), 30.f, render::kRed, 2, 8);
    checkInt("a degenerate sphere emits nothing", 0, (long long)empty.vertices().size());
    checkBool("and reports empty", true, empty.empty());

    // The drop path respects the batch limit, like the cube's.
    render::CubeBatch capped(64);
    capped.addSphere(glm::vec3(0, 0, 0), 30.f, render::kRed, 12, 8);   // 576 > 64
    checkBool("an over-limit sphere is dropped, not truncated", true, capped.empty());
    checkBool("and counted as dropped vertices", true, capped.droppedVertices() > 0);
}

void testBatchReuse() {
    std::printf("\n-- batch: per-frame growth and reuse --\n");
    DebugLineBatch batch;
    checkInt("default limit", 65536, (long long)batch.limit());
    checkBool("a fresh batch is empty", true, batch.empty());

    batch.clear();
    batch.line(glm::vec3(0.f), glm::vec3(1.f, 0.f, 0.f), render::kRed);
    checkInt("frame 1: 1 line -> 2 vertices", 2, (long long)batch.vertexCount());
    checkInt("frame 1: lineCount", 1, (long long)batch.lineCount());
    checkInt("frame 1: nothing dropped", 0, (long long)batch.droppedVertices());
    const size_t cap1 = batch.capacity();
    const DebugVertex* ptr1 = batch.vertices().data();

    batch.clear();
    batch.box(glm::vec3(-1.f), glm::vec3(1.f), render::kGreen);
    checkInt("frame 2: box -> 24 vertices", 24, (long long)batch.vertexCount());
    const size_t cap2 = batch.capacity();
    const DebugVertex* ptr2 = batch.vertices().data();
    checkBool("frame 2 grew the storage (capacity >= 24)", true, cap2 >= 24);
    checkBool("frame 2 reallocated (growth happened on the larger frame)", true, ptr2 != ptr1);
    checkBool("clear() kept the capacity from frame 1", true, cap2 >= cap1);

    const std::vector<DebugVertex> frame2 = batch.vertices();
    batch.clear();
    batch.box(glm::vec3(-1.f), glm::vec3(1.f), render::kGreen);
    const size_t cap3 = batch.capacity();
    const DebugVertex* ptr3 = batch.vertices().data();
    checkInt("frame 3: same 24 vertices", 24, (long long)batch.vertexCount());
    checkBool("frame 3 reused the allocation (same data pointer)", true, ptr3 == ptr2);
    checkBool("frame 3 allocated nothing (capacity unchanged)", true, cap3 == cap2);
    checkBool("frame 3 refilled the same bytes", true, sameBytes(frame2, batch.vertices()));

    std::printf("  (info) capacities: frame 1 = %zu, frame 2 = %zu, frame 3 = %zu vertices\n",
                cap1, cap2, cap3);

    // Reuse with a different primitive mix, still no reallocation.
    batch.clear();
    batch.cross(glm::vec3(1.f), 0.5f, render::kBlue);
    batch.ray(glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f), 2.f, render::kCyan);
    checkInt("cross + ray -> 6 + 2 vertices", 8, (long long)batch.vertexCount());
    checkBool("mixed primitives reuse the same storage", true, batch.vertices().data() == ptr2);

    // Drop accounting: whole primitives, counted, reset by clear().
    DebugLineBatch tiny(6);
    tiny.box(glm::vec3(-1.f), glm::vec3(1.f));
    checkInt("small-limit batch: box refused entirely", 0, (long long)tiny.vertexCount());
    checkInt("small-limit batch: refused box counted 24 vertices dropped", 24,
             (long long)tiny.droppedVertices());
    tiny.line(glm::vec3(0.f), glm::vec3(1.f, 0.f, 0.f));
    tiny.line(glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));
    tiny.line(glm::vec3(0.f), glm::vec3(0.f, 0.f, 1.f));
    checkInt("small-limit batch: 3 lines fit exactly", 6, (long long)tiny.vertexCount());
    tiny.line(glm::vec3(0.f), glm::vec3(1.f));
    checkInt("small-limit batch: 4th line refused", 6, (long long)tiny.vertexCount());
    checkInt("small-limit batch: drops accumulate", 26, (long long)tiny.droppedVertices());
    tiny.clear();
    checkInt("clear() resets the drop counter", 0, (long long)tiny.droppedVertices());
    checkInt("clear() keeps vertexCount at 0", 0, (long long)tiny.vertexCount());
    tiny.ray(glm::vec3(0.f), glm::vec3(0.f), 5.f);
    checkInt("a degenerate ray is not counted as a drop", 0, (long long)tiny.droppedVertices());

    // append(vector<DebugLine>) must equal appendLines() on the same input.
    const std::vector<DebugLine> lines = {
        {glm::vec3(0.f), glm::vec3(1.f, 2.f, 3.f), render::kWhite},
        {glm::vec3(4.f, 5.f, 6.f), glm::vec3(7.f, 8.f, 9.f), 0x80402010u},
    };
    DebugLineBatch viaBatch;
    viaBatch.append(lines);
    std::vector<DebugVertex> viaFree;
    render::appendLines(viaFree, lines);
    checkBool("batch.append(lines) == appendLines(lines)", true,
              sameBytes(viaBatch.vertices(), viaFree));
    checkInt("2 lines -> 4 vertices", 4, (long long)viaBatch.vertexCount());

    // Repeated identical frames produce identical bytes (the capture requirement).
    DebugLineBatch a;
    DebugLineBatch b;
    for (int frame = 0; frame < 3; ++frame) {
        a.clear();
        a.box(glm::vec3(-2.f, -1.f, 0.f), glm::vec3(2.f, 1.f, 4.f), render::kRed);
        a.cross(glm::vec3(1.f, 2.f, 3.f), 0.25f, render::kGreen);
        a.ray(glm::vec3(0.f), glm::vec3(0.f, 0.f, 1.f), 3.f, render::kBlue);
        b.clear();
        b.box(glm::vec3(-2.f, -1.f, 0.f), glm::vec3(2.f, 1.f, 4.f), render::kRed);
        b.cross(glm::vec3(1.f, 2.f, 3.f), 0.25f, render::kGreen);
        b.ray(glm::vec3(0.f), glm::vec3(0.f, 0.f, 1.f), 3.f, render::kBlue);
    }
    checkInt("box + cross + ray -> 24 + 6 + 2 vertices", 32, (long long)a.vertexCount());
    checkBool("three frames of the same input are byte-identical across instances", true,
              sameBytes(a.vertices(), b.vertices()));
}

void testClipConvention() {
    std::printf("\n-- position transform (the viewProj convention the WGSL relies on) --\n");
    // Exactly main.cpp's projection: perspectiveLH_ZO, 45 degrees, and its lookAtLH
    // view. The numbers below are the properties the shader depends on, not a
    // rendering result: M * v, w > 0 in front of the eye, clip z in [0, 1].
    const glm::mat4 proj = glm::perspectiveLH_ZO(glm::radians(90.f), 1.f, 1.f, 101.f);
    const glm::vec3 eye(0.f, 0.f, -5.f);
    const glm::mat4 view = glm::lookAtLH(eye, glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));
    const glm::mat4 viewProj = proj * view;

    const glm::vec4 eyeSpace = view * glm::vec4(0.f, 0.f, 0.f, 1.f);
    checkVec3Exact("lookAtLH puts the origin 5 units in front (view z = +5)",
                   glm::vec3(0.f, 0.f, 5.f), glm::vec3(eyeSpace));

    const glm::vec4 clip = clipOf(viewProj, glm::vec3(0.f));
    checkFloatExact("clip.w == view z (left-handed, no proj flip)", 5.f, clip.w);
    checkNear("clip.z / clip.w is inside the 0..1 WebGPU depth range", 0.808f, clip.z / clip.w,
              1e-4f);

    const glm::vec4 nearClip = clipOf(proj, glm::vec3(0.f, 0.f, 1.f));
    checkFloatExact("a point on the near plane has clip z = 0 (ZO range)", 0.f, nearClip.z);
    const glm::vec4 farClip = clipOf(proj, glm::vec3(0.f, 0.f, 101.f));
    checkNear("a point on the far plane has clip z / w = 1 (ZO range)", 1.f,
              farClip.z / farClip.w, 1e-6f);
    checkBool("a point behind the eye has negative w and is clipped", true,
              clipOf(viewProj, glm::vec3(0.f, 0.f, -6.f)).w < 0.f);

    // Ordering matters for depth-tested lines: nearer must be smaller in clip z.
    const glm::vec4 nearClip2 = clipOf(viewProj, glm::vec3(0.f, 0.f, -3.5f));
    const glm::vec4 farClip2 = clipOf(viewProj, glm::vec3(0.f, 0.f, 5.f));
    const float zNear = nearClip2.z / nearClip2.w;
    const float zFar = farClip2.z / farClip2.w;
    checkBool("depth is monotonic: a nearer point has a smaller clip z", true, zNear < zFar);
    std::printf("  (info) clip z at 1.5 and 10 units in front of the eye: %.6f < %.6f\n",
                (double)zNear, (double)zFar);
}

}  // namespace

int main() {
    std::printf("debug_prims geometry test (no WebGPU: DEBUG_PRIMS_GEOMETRY_ONLY)\n");
    std::printf("sizeof(DebugVertex) = %zu, sizeof(DebugLine) = %zu\n", sizeof(DebugVertex),
                sizeof(DebugLine));

    testColorPacking();
    testVertexFormat();
    testLineList();
    testAabbOutline();
    testCross();
    testRay();
    testSphere();
    testBatchReuse();
    testClipConvention();

    std::printf("\nchecks: %d, failures: %d\n", g_checks, g_failed);
    std::printf("DEBUG_PRIMS_GEOMETRY: %s\n", g_failed == 0 ? "ok" : "FAIL");
    return g_failed == 0 ? 0 : 1;
}
