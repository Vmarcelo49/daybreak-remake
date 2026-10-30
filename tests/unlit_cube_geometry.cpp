// tests/unlit_cube_geometry.cpp — device-free checks on the solid cube pass's geometry.
//
// The point of this test is that the DX9 cube is a *content* primitive (every shot,
// spark and aura is one), so its geometry is not free to be approximately right: the 36
// vertices are the ones remake/src/render/debug_prim.cpp:71-90 emits, and a future edit
// that "cleans up" the winding or reorders a face must fail here rather than silently
// shift pixels. Both geometry-only guards are defined so neither header pulls WebGPU.
#define DEBUG_PRIMS_GEOMETRY_ONLY 1

#include <cmath>
#include <cstdio>
#include <cstring>

// The cube is part of the debug-prims pass — the DX9 file has both (remake/src/render/
// debug_prim.{h,cpp} is a cube pass that this foundation also uses for real content:
// shots, sparks, auras), so its geometry is pinned here alongside the line geometry.
#include "render/debug_prims.h"

namespace {

int checks = 0;
int failures = 0;

void ok(bool cond, const char* what) {
    ++checks;
    if (!cond) ++failures;
    std::printf("  %-4s %s\n", cond ? "ok" : "FAIL", what);
}

void okf(bool cond, const char* what, float got, float want, float eps = 1e-6f) {
    ++checks;
    if (!cond) ++failures;
    std::printf("  %-4s %-52s got=%.6f want=%.6f eps=%g\n", cond ? "ok" : "FAIL", what, got,
                want, eps);
}

bool near(float a, float b, float eps = 1e-6f) { return std::fabs(a - b) <= eps; }

// Exact vertex order of the DX9 pass, transcribed independently of buildCube so a
// change to either side shows up as a mismatch rather than agreeing with itself.
struct V { float x, y, z; };
V referenceVertex(int i, float cx, float cy, float cz, float h) {
    const float x0 = cx - h, x1 = cx + h;
    const float y0 = cy - h, y1 = cy + h;
    const float z0 = cz - h, z1 = cz + h;
    switch (i) {
        case 0:  return {x0, y0, z0};
        case 1:  return {x0, y1, z0};
        case 2:  return {x1, y1, z0};
        case 3:  return {x0, y0, z0};
        case 4:  return {x1, y1, z0};
        case 5:  return {x1, y0, z0};
        case 6:  return {x0, y0, z1};
        case 7:  return {x1, y1, z1};
        case 8:  return {x0, y1, z1};
        case 9:  return {x0, y0, z1};
        case 10: return {x1, y0, z1};
        case 11: return {x1, y1, z1};
        case 12: return {x0, y0, z0};
        case 13: return {x0, y0, z1};
        case 14: return {x0, y1, z1};
        case 15: return {x0, y0, z0};
        case 16: return {x0, y1, z1};
        case 17: return {x0, y1, z0};
        case 18: return {x1, y0, z0};
        case 19: return {x1, y1, z1};
        case 20: return {x1, y0, z1};
        case 21: return {x1, y0, z0};
        case 22: return {x1, y1, z0};
        case 23: return {x1, y1, z1};
        case 24: return {x0, y1, z0};
        case 25: return {x0, y1, z1};
        case 26: return {x1, y1, z1};
        case 27: return {x0, y1, z0};
        case 28: return {x1, y1, z1};
        case 29: return {x1, y1, z0};
        case 30: return {x0, y0, z0};
        case 31: return {x1, y0, z1};
        case 32: return {x0, y0, z1};
        case 33: return {x0, y0, z0};
        case 34: return {x1, y0, z0};
        case 35: return {x1, y0, z1};
        default: return {0.f, 0.f, 0.f};
    }
}

}  // namespace

int main() {
    std::printf("unlit_cube_geometry — the solid cube pass's vertex stream\n\n");

    std::printf("== constants ==\n");
    ok(render::kCubeVertices == 36, "36 vertices per cube");
    ok(render::kCubeTriangles == 12, "12 triangles per cube");
    ok(render::kCubeVertices == render::kCubeTriangles * 3, "vertices = triangles * 3");
    ok(sizeof(render::DebugVertex) == 16, "vertex is 16 bytes (3 floats + u32, unpacked)");
    ok(offsetof(render::DebugVertex, pos) == 0, "position at offset 0");
    ok(offsetof(render::DebugVertex, color) == 12, "colour at offset 12");

    std::printf("\n== vertex order matches debug_prim.cpp:71-90 ==\n");
    {
        const float h = 12.f, cx = 100.f, cy = 200.f, cz = -300.f;
        const render::DebugColor color = render::packColor(130, 220, 255, 255);
        render::DebugVertex v[render::kCubeVertices];
        render::buildCube({cx, cy, cz}, h, color, v);
        int mismatch = 0;
        for (int i = 0; i < 36; ++i) {
            const V want = referenceVertex(i, cx, cy, cz, h);
            if (!near(v[i].pos.x, want.x) || !near(v[i].pos.y, want.y) || !near(v[i].pos.z, want.z))
                ++mismatch;
            if (v[i].color != color) ++mismatch;
        }
        ok(mismatch == 0, "all 36 vertices are position- and colour-identical to the source");
        ok(v[0].pos.x == cx - h && v[0].pos.y == cy - h && v[0].pos.z == cz - h, "vertex 0 is the -X-Y-Z corner");
        ok(v[2].pos.x == cx + h && v[2].pos.y == cy + h && v[2].pos.z == cz - h, "vertex 2 is the +X+Y-Z corner");
        ok(v[35].pos.x == cx + h && v[35].pos.y == cy - h && v[35].pos.z == cz + h, "vertex 35 is the +X-Y+Z corner");
    }

    std::printf("\n== the cube is a closed axis-aligned box ==\n");
    {
        const float h = 5.f;
        render::DebugVertex v[render::kCubeVertices];
        render::buildCube({0.f, 0.f, 0.f}, h, 0xffffffffu, v);
        float mn[3] = {1e9f, 1e9f, 1e9f}, mx[3] = {-1e9f, -1e9f, -1e9f};
        for (int i = 0; i < 36; ++i) {
            const float p[3] = {v[i].pos.x, v[i].pos.y, v[i].pos.z};
            for (int c = 0; c < 3; ++c) {
                mn[c] = std::fmin(mn[c], p[c]);
                mx[c] = std::fmax(mx[c], p[c]);
            }
        }
        okf(mn[0] == -h && mx[0] == h, "X extent is exactly +/- h", mx[0] - mn[0], 2 * h);
        okf(mn[1] == -h && mx[1] == h, "Y extent is exactly +/- h", mx[1] - mn[1], 2 * h);
        okf(mn[2] == -h && mx[2] == h, "Z extent is exactly +/- h", mx[2] - mn[2], 2 * h);
        // The 12 triangles must tile the whole surface: their areas sum to the cube's
        // 6 faces of (2h)^2. Counting vertices per axis plane would not work — every
        // corner lies on three of them at once, which is how the first draft of this
        // test managed to be wrong about correct code.
        double area = 0.0;
        for (int t = 0; t < 12; ++t) {
            const render::DebugVertex& a = v[t * 3 + 0];
            const render::DebugVertex& b = v[t * 3 + 1];
            const render::DebugVertex& c = v[t * 3 + 2];
            const double ux = b.pos.x - a.pos.x, uy = b.pos.y - a.pos.y, uz = b.pos.z - a.pos.z;
            const double wx = c.pos.x - a.pos.x, wy = c.pos.y - a.pos.y, wz = c.pos.z - a.pos.z;
            const double nx = uy * wz - uz * wy;
            const double ny = uz * wx - ux * wz;
            const double nz = ux * wy - uy * wx;
            area += 0.5 * std::sqrt(nx * nx + ny * ny + nz * nz);
        }
        okf(std::fabs(area - 24.0 * h * h) < 1e-6, "the 12 triangles tile the surface (area = 24h^2)",
            (float)area, 24.f * h * h, 1e-6f);
        ok(area > 0.0, "no triangle is degenerate");
    }

    std::printf("\n== batch: caps, drop accounting, submission order ==\n");
    {
        render::CubeBatch batch(72);   // room for exactly 2 cubes
        ok(batch.empty(), "a fresh batch is empty");
        ok(batch.cubes() == 0 && batch.vertices().empty(), "fresh batch has 0 cubes / 0 vertices");
        batch.add({1.f, 2.f, 3.f}, 4.f, render::packColor(255, 0, 0, 255));
        batch.add({5.f, 6.f, 7.f}, 8.f, render::packColor(0, 255, 0, 255));
        ok(batch.cubes() == 2, "two cubes fit at the limit");
        ok(batch.vertices().size() == 72, "two cubes are 72 vertices");
        ok(batch.droppedVertices() == 0, "nothing dropped at the limit");
        const render::DebugColor first = batch.vertices()[0].color;
        const render::DebugColor second = batch.vertices()[36].color;
        ok(first == render::packColor(255, 0, 0, 255), "cube 0 keeps its colour, in submission order");
        ok(second == render::packColor(0, 255, 0, 255), "cube 1 keeps its colour, in submission order");
        ok(batch.vertices()[0].pos.x == 1.f - 4.f, "cube 0's first vertex is its own centre minus h");
        ok(batch.vertices()[36].pos.x == 5.f - 8.f, "cube 1's first vertex is its own centre minus h");
        batch.add({9.f, 9.f, 9.f}, 1.f, 0xffffffffu);   // over the limit
        ok(batch.cubes() == 2, "an over-limit cube does not enter the batch");
        ok(batch.droppedVertices() == 36, "the dropped cube is accounted for as 36 vertices");
        ok(batch.limit() == 72, "the limit is reported");
        batch.clear();
        ok(batch.empty() && batch.droppedVertices() == 0, "clear() empties the batch and the drop count");
        ok(batch.limit() == 72, "clear() keeps the limit");
    }

    std::printf("\n== colour packing is the shared debug_prims implementation ==\n");
    {
        // The DX9 passes D3DCOLOR (0xAARRGGBB). The cube pass reuses render::packColor
        // rather than defining a second packing: this pins that they agree.
        const render::DebugColor c = render::packColor(130, 220, 255, 90);
        ok(c == 0x5a82dcffu, "packColor(130,220,255,90) == 0x5A82DCFF");
        ok(render::colorR(c) == 130 && render::colorG(c) == 220 && render::colorB(c) == 255,
           "packColor round-trips through colorR/G/B");
        render::DebugVertex v[render::kCubeVertices];
        render::buildCube({0.f, 0.f, 0.f}, 1.f, c, v);
        int allSame = 1;
        for (int i = 0; i < 36; ++i)
            if (v[i].color != c) allSame = 0;
        ok(allSame == 1, "every vertex of a cube carries the caller's D3DCOLOR unchanged");
    }

    std::printf("\n%dx checks, %d failed\n", checks, failures);
    std::printf("UNLIT_CUBE: %s\n", failures == 0 ? "ok" : "FAIL");
    return failures == 0 ? 0 : 1;
}
