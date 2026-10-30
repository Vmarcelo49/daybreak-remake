// tests/raycast_analytic.cpp — host test for physics/raycast.{h,cpp}.
//
// Build from the repo root (glm ships in the foundation's third_party):
//   g++ -std=c++20 -O2 -Wall -Wextra -I remake/foundation/src
//       -I remake/foundation/third_party/glm remake/foundation/src/physics/raycast.cpp
//       remake/foundation/tests/raycast_analytic.cpp -o /tmp/raycast_analytic
//   /tmp/raycast_analytic [path/to/collision_camera.X]
//
// What the evidence is, and what it is not:
//   * Exact analytic cases: hand-built triangles/meshes whose expected t, u, v are
//     exactly representable in float, compared with `==` (no tolerance). Cases whose
//     expectation is not representable (a centroid's 1/3) are labelled `ok~` and print
//     the measured residual instead of hiding it. Verified at -O0, -O2 and -O3;
//     -march=native keeps every intersection value exact and only shifts the derived
//     barycentric reconstruction sum by ~1.4e-6 (FMA contraction), which that one case
//     bounds instead of comparing exactly.
//   * An independent cross-check: a second intersection method (plane equation plus
//     edge half-space classification in double precision) over pseudo-random rays,
//     compared against the Möller–Trumbore implementation under test. This is evidence
//     of internal agreement, NOT parity with D3DXIntersect.
//   * A real-asset smoke test: every triangle of a loaded stage collision mesh is
//     re-hit from 100 units along its normal, and the whole-model walk is exercised.
//   * Cost per ray on the real mesh and on synthetic grids of a stated size.
//   * NOT D3DXIntersect parity: the DX9 build has no CLI path that calls the raycast
//     (remake/src/main.cpp includes physics/raycast.h at line 50 and never calls it),
//     so there is no oracle to compare against. See the task report.
//
// Exit status: 0 when every check passed, 1 otherwise.

#define XMODEL_IMPLEMENTATION   // this is the one TU that compiles the asset layer
#include "assets/xmodel.h"

#include "physics/raycast.h"
#include "render/arena_camera.h"   // arenaClampEye: the clamp consumer's math (read-only use)

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>

namespace {

using game::physics::buildModelIndex;
using game::physics::CameraCollision;
using game::physics::ModelIndex;
using game::physics::RayHit;
using game::physics::RaycastStats;
using game::physics::TriangleMeshView;

int g_checks   = 0;
int g_failures = 0;

// ---------------------------------------------------------------------------------------
// Reporting
// ---------------------------------------------------------------------------------------
std::string sf(float v) {
    char b[32];
    // -0 and +0 are the same barycentric/t value; print them the same so exact string
    // comparison does not depend on which side of the kernel produced the zero.
    std::snprintf(b, sizeof b, "%.9g", static_cast<double>(v == 0.f ? 0.f : v));
    return b;
}
std::string sd(double v) {
    char b[32];
    std::snprintf(b, sizeof b, "%.9g", v);
    return b;
}
std::string sz(size_t v) {
    char b[32];
    std::snprintf(b, sizeof b, "%zu", v);
    return b;
}
std::string sb(bool v) { return v ? "true" : "false"; }
std::string sv(const glm::vec3& v) {
    return "(" + sf(v.x) + "," + sf(v.y) + "," + sf(v.z) + ")";
}
std::string sh(const RayHit& h) {
    return "hit=" + std::string(h.hit ? "1" : "0") + " mesh=" + std::to_string(h.mesh) +
           " face=" + std::to_string(h.faceIndex) + " u=" + sf(h.u) + " v=" + sf(h.v) +
           " t=" + sf(h.dist) + " p=" + sv(h.point);
}
std::string sstats(const RaycastStats& s) {
    return "tris=" + sz(s.trianglesTested) + " meshes=" + sz(s.meshesVisited);
}

void check(const std::string& name, const std::string& expected, const std::string& got) {
    ++g_checks;
    const bool ok = (expected == got);
    if (!ok) ++g_failures;
    std::printf("  [%-4s] %-62s expected=%s  got=%s\n", ok ? "ok" : "FAIL", name.c_str(),
                expected.c_str(), got.c_str());
}

// For cases whose expected value is not exactly representable (real-file coordinates,
// 1/3 barycentrics). Labelled `ok~` so no reader mistakes it for an exact check.
void checkNear(const std::string& name, double expected, double got, double tol) {
    ++g_checks;
    const double d  = std::fabs(got - expected);
    const bool   ok = (d <= tol);
    if (!ok) ++g_failures;
    std::printf("  [%-4s] %-62s expected=%.9g tol=%.1g  got=%.9g  |d|=%.3g\n",
                ok ? "ok~" : "FAIL", name.c_str(), expected, tol, got, d);
}

void info(const std::string& text) { std::printf("  ....   %s\n", text.c_str()); }

// One-sided bound: for measurements that must not exceed a limit (they are not
// "expected to equal" anything).
void checkLe(const std::string& name, double bound, double got) {
    ++g_checks;
    const bool ok = (got <= bound);
    if (!ok) ++g_failures;
    std::printf("  [%-4s] %-62s must be<=%.9g  got=%.9g\n", ok ? "ok~" : "FAIL", name.c_str(),
                bound, got);
}
void section(const char* title) { std::printf("\n== %s ==\n", title); }

// ---------------------------------------------------------------------------------------
// Hand-built geometry
// ---------------------------------------------------------------------------------------
struct Tri {
    glm::vec3 a, b, c;
};

glm::vec3 triCentroid(const Tri& t) { return (t.a + t.b + t.c) / 3.0f; }

glm::vec3 triNormal(const Tri& t) {
    const glm::vec3 n = glm::cross(t.b - t.a, t.c - t.a);
    const float     l = glm::length(n);
    return l > 0.f ? n / l : glm::vec3(0.f);
}

// Plane x = k, spanning y,z in [-1,1]. A ray along +x through (k,0,0) lands on the
// v1-v2 edge midpoint, so u = v = 0.5 exactly.
Tri planeX(float k) { return {{k, -1.f, -1.f}, {k, 1.f, -1.f}, {k, -1.f, 1.f}}; }

// v0 = (k,0,0), v1 = (k,2,0), v2 = (k,0,2): axis-aligned rays can hit a vertex and an
// edge midpoint exactly.
Tri xFace(float k) { return {{k, 0.f, 0.f}, {k, 2.f, 0.f}, {k, 0.f, 2.f}}; }

// Same shape scaled by 3, so the centroid (k,1,1) is exactly representable.
Tri xFace3(float k) { return {{k, 0.f, 0.f}, {k, 3.f, 0.f}, {k, 0.f, 3.f}}; }

// One mesh per call, vertices unshared so face index i is tris[i] by construction.
// `frame` defaults to -1: the shape every shipped collision_camera.X has.
int addMesh(xm::Model& model, const std::vector<Tri>& tris, int frame = -1,
            const char* name = "") {
    xm::Mesh m;
    m.name  = name;
    m.frame = frame;
    m.vertices.reserve(tris.size() * 3);
    m.indices.reserve(tris.size() * 3);
    for (const Tri& t : tris) {
        const glm::vec3 corners[3] = {t.a, t.b, t.c};
        for (const glm::vec3& p : corners) {
            xm::Vertex v;
            v.pos = p;
            m.vertices.push_back(v);
        }
        const uint32_t base = static_cast<uint32_t>(m.indices.size());
        m.indices.push_back(base + 0);
        m.indices.push_back(base + 1);
        m.indices.push_back(base + 2);
    }
    model.meshes.push_back(std::move(m));
    return static_cast<int>(model.meshes.size()) - 1;
}

// `meshIdx` is a model-level notion: the per-container entry points leave it at -1.
RayHit expectHit(uint32_t face, float u, float v, float t, const glm::vec3& p, int meshIdx = -1) {
    RayHit h;
    h.hit       = true;
    h.faceIndex = face;
    h.u         = u;
    h.v         = v;
    h.dist      = t;
    h.point     = p;
    h.mesh      = meshIdx;
    return h;
}

std::string sorder(const ModelIndex& index) {
    std::string s = "{";
    for (size_t i = 0; i < index.meshOrder.size(); ++i) {
        if (i) s += ",";
        s += std::to_string(index.meshOrder[i]);
    }
    return s + "}";
}

// ---------------------------------------------------------------------------------------
// 1. Single-triangle exact cases (the intersection kernel itself)
// ---------------------------------------------------------------------------------------
void triangleCases() {
    section("1. single triangle, exact expectations");
    xm::Model model;
    addMesh(model, {planeX(5.f)});
    const TriangleMeshView view = game::physics::meshView(model.meshes[0]);

    check("plane x=5, ray +x from origin",
          sh(expectHit(0, 0.5f, 0.5f, 5.f, {5.f, 0.f, 0.f})),
          sh(game::physics::raycastTriangles(view, {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f})));

    // Barycentric at the three vertices, at an edge midpoint and at the centroid.
    xm::Model vmodel;
    addMesh(vmodel, {xFace(5.f)});
    const TriangleMeshView vview = game::physics::meshView(vmodel.meshes[0]);
    check("vertex v0 (xFace), ray +x through (k,0,0): u=0 v=0",
          sh(expectHit(0, 0.f, 0.f, 5.f, {5.f, 0.f, 0.f})),
          sh(game::physics::raycastTriangles(vview, {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f})));
    check("vertex v1, ray +x through (k,2,0): u=1 v=0",
          sh(expectHit(0, 1.f, 0.f, 5.f, {5.f, 2.f, 0.f})),
          sh(game::physics::raycastTriangles(vview, {0.f, 2.f, 0.f}, {1.f, 0.f, 0.f})));
    check("vertex v2, ray +x through (k,0,2): u=0 v=1",
          sh(expectHit(0, 0.f, 1.f, 5.f, {5.f, 0.f, 2.f})),
          sh(game::physics::raycastTriangles(vview, {0.f, 0.f, 2.f}, {1.f, 0.f, 0.f})));
    check("edge midpoint (v1,v2), ray +x through (k,1,1): u=v=0.5",
          sh(expectHit(0, 0.5f, 0.5f, 5.f, {5.f, 1.f, 1.f})),
          sh(game::physics::raycastTriangles(vview, {0.f, 1.f, 1.f}, {1.f, 0.f, 0.f})));

    xm::Model cmodel;
    addMesh(cmodel, {xFace3(5.f)});
    const Tri              ctri  = xFace3(5.f);
    const TriangleMeshView cview = game::physics::meshView(cmodel.meshes[0]);
    const RayHit centroid = game::physics::raycastTriangles(cview, {0.f, 1.f, 1.f}, {1.f, 0.f, 0.f});
    const glm::vec3 recon =
        (1.f - centroid.u - centroid.v) * ctri.a + centroid.u * ctri.b + centroid.v * ctri.c;
    check("centroid: hit at t=5 and p=(5,1,1) exactly",
          sh(expectHit(0, centroid.u, centroid.v, 5.f, {5.f, 1.f, 1.f})), sh(centroid));
    check("centroid: u == v bitwise", sb(true), sb(centroid.u == centroid.v));
    // The reconstruction is a derived sum: an FMA-contracting build (-march=native on an
    // FMA host) shifts it by ~1.4e-6 while u, v, t and the hit point above stay exact
    // (measured). Bounded, not compared exactly.
    checkLe("centroid: |barycentric reconstruction - hit point| <= 1e-5",
            1e-5, static_cast<double>(glm::length(recon - glm::vec3(5.f, 1.f, 1.f))));
    checkNear("centroid: u vs 1/3 (1/3 is not representable; residual shown, not asserted)",
              1.0 / 3.0, static_cast<double>(centroid.u), 1e-6);

    // t is the raw ray parameter: a non-unit dir scales it (the reference's `dist`).
    check("non-unit dir (2,0,0): t=2.5, point still (5,0,0)",
          sh(expectHit(0, 0.5f, 0.5f, 2.5f, {5.f, 0.f, 0.f})),
          sh(game::physics::raycastTriangles(view, {0.f, 0.f, 0.f}, {2.f, 0.f, 0.f})));

    // Misses.
    check("miss: (0,3,0) + t(1,0,0): u would be 1.5",
          sh(RayHit{}), sh(game::physics::raycastTriangles(view, {0.f, 3.f, 0.f}, {1.f, 0.f, 0.f})));
    check("miss: xFace (0,3,3) + t(1,0,0): u+v > 1",
          sh(RayHit{}), sh(game::physics::raycastTriangles(vview, {0.f, 3.f, 3.f}, {1.f, 0.f, 0.f})));
    check("miss: ray parallel to the triangle plane (det == 0)",
          sh(RayHit{}), sh(game::physics::raycastTriangles(view, {0.f, 0.f, 0.f}, {0.f, 1.f, 0.f})));
    check("miss: hit behind the origin (plane x=5, dir -x)",
          sh(RayHit{}), sh(game::physics::raycastTriangles(view, {0.f, 0.f, 0.f}, {-1.f, 0.f, 0.f})));

    // maxDist: exclusive > cutoff, inclusive == cutoff, <= 0 disables it.
    check("maxDist=4 < t=5: miss",
          sh(RayHit{}),
          sh(game::physics::raycastTriangles(view, {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f}, 4.f)));
    check("maxDist=5 == t: hit (cutoff inclusive, raycast.cpp:66)",
          sh(expectHit(0, 0.5f, 0.5f, 5.f, {5.f, 0.f, 0.f})),
          sh(game::physics::raycastTriangles(view, {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f}, 5.f)));
    check("maxDist=-1: no cutoff",
          sh(expectHit(0, 0.5f, 0.5f, 5.f, {5.f, 0.f, 0.f})),
          sh(game::physics::raycastTriangles(view, {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f}, -1.f)));

    // Boundary and scale.
    check("origin exactly on the triangle: t=0 is a hit",
          sh(expectHit(0, 0.5f, 0.5f, 0.f, {5.f, 0.f, 0.f})),
          sh(game::physics::raycastTriangles(view, {5.f, 0.f, 0.f}, {1.f, 0.f, 0.f})));
    check("back face: ray -x from (10,0,0) hits at t=5 (non-culling, like D3DXIntersect)",
          sh(expectHit(0, 0.5f, 0.5f, 5.f, {5.f, 0.f, 0.f})),
          sh(game::physics::raycastTriangles(view, {10.f, 0.f, 0.f}, {-1.f, 0.f, 0.f})));
    xm::Model farModel;
    addMesh(farModel, {planeX(3000.f)});
    check("game-unit scale: plane x=3000, t=3000 exactly",
          sh(expectHit(0, 0.5f, 0.5f, 3000.f, {3000.f, 0.f, 0.f})),
          sh(game::physics::raycastTriangles(game::physics::meshView(farModel.meshes[0]),
                                             {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f})));

    // Degenerate / malformed inputs must miss, not crash or read out of range.
    const Tri degenerate{{1.f, 1.f, 1.f}, {1.f, 1.f, 1.f}, {1.f, 1.f, 1.f}};
    xm::Model dmodel;
    addMesh(dmodel, {degenerate});
    check("degenerate triangle (all vertices equal): miss",
          sh(RayHit{}), sh(game::physics::raycastTriangles(
                            game::physics::meshView(dmodel.meshes[0]), {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f})));
    check("null view: miss", sh(RayHit{}),
          sh(game::physics::raycastTriangles(TriangleMeshView{}, {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f})));
    check("zero triangles: miss", sh(RayHit{}),
          sh(game::physics::raycastTriangles(
              TriangleMeshView{model.meshes[0].vertices.data(), model.meshes[0].vertices.size(),
                               model.meshes[0].indices.data(), 0},
              {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f})));
    {
        xm::Vertex verts[3] = {};
        verts[0].pos = {5.f, -1.f, -1.f};
        verts[1].pos = {5.f, 1.f, -1.f};
        verts[2].pos = {5.f, -1.f, 1.f};
        const uint32_t bad[3] = {0u, 1u, 7u};   // 7 is out of range
        check("out-of-range index: miss, no out-of-bounds read",
              sh(RayHit{}),
              sh(game::physics::raycastTriangles(TriangleMeshView{verts, 3, bad, 3},
                                                 {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f})));
    }
}

// ---------------------------------------------------------------------------------------
// 2. Model-level: closest hit, ties, traversal order, early-out
// ---------------------------------------------------------------------------------------
void modelCases() {
    section("2. model walk: closest hit, ties, frame order, early-out");

    {
        xm::Model m;
        addMesh(m, {planeX(5.f)});   // mesh 0: far
        addMesh(m, {planeX(3.f)});   // mesh 1: near
        const ModelIndex idx = buildModelIndex(m);
        check("closest of two meshes: t=3, mesh 1",
              sh(expectHit(0, 0.5f, 0.5f, 3.f, {3.f, 0.f, 0.f}, 1)),
              sh(game::physics::raycastModel(m, idx, {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f})));
        check("model traversal order == mesh order (all frames -1)",
              sorder(ModelIndex{{0, 1}}), sorder(idx));
    }
    {
        xm::Model m;
        addMesh(m, {planeX(7.f), planeX(2.f)});   // closest is face 1
        const ModelIndex idx = buildModelIndex(m);
        check("closest within one mesh: face 1 wins",
              sh(expectHit(1, 0.5f, 0.5f, 2.f, {2.f, 0.f, 0.f}, 0)),
              sh(game::physics::raycastModel(m, idx, {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f})));
    }
    {
        xm::Model m;
        addMesh(m, {planeX(3.f), planeX(3.f)});   // exact tie, face 0 first
        addMesh(m, {planeX(3.f)});                // exact tie, later mesh
        const ModelIndex idx = buildModelIndex(m);
        check("tie in one mesh and across meshes: earliest face of the earliest mesh wins",
              sh(expectHit(0, 0.5f, 0.5f, 3.f, {3.f, 0.f, 0.f}, 0)),
              sh(game::physics::raycastModel(m, idx, {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f})));
    }
    {
        // Frame hierarchy: frame 0 (root) -> frame 1 (child). Model mesh order is
        // deliberately reversed, so traversal order is observable: the root's mesh is
        // visited before its child's (reference walk: containers, child, sibling).
        xm::Model m;
        m.frames.resize(2);
        m.frames[0].name   = "root";
        m.frames[0].parent = -1;
        m.frames[1].name   = "child";
        m.frames[1].parent = 0;
        const int nearMesh = addMesh(m, {planeX(2.f)}, 1, "child-near");   // meshes[0]
        const int farMesh  = addMesh(m, {planeX(5.f)}, 0, "root-far");     // meshes[1]
        const ModelIndex idx = buildModelIndex(m);
        check("frame walk: root frame's mesh before its child's mesh",
              sorder(ModelIndex{{farMesh, nearMesh}}), sorder(idx));

        // Hoisted: `sb(call(&s)) + sstats(s)` has unsequenced operands if written as one
        // expression, which would read the stats before the call.
        RaycastStats s;
        const bool   anyFirst =
            game::physics::raycastModelAny(m, idx, {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f}, 0.f, &s);
        check("any, maxDist=0: frames[0] mesh tested first and hits",
              sb(true) + " " + sstats(RaycastStats{1, 1}), sb(anyFirst) + " " + sstats(s));

        s = RaycastStats{};
        const bool anyCut4 =
            game::physics::raycastModelAny(m, idx, {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f}, 4.f, &s);
        check("any, maxDist=4: far mesh's triangle tested and rejected, child mesh found second",
              sb(true) + " " + sstats(RaycastStats{2, 2}), sb(anyCut4) + " " + sstats(s));
        check("closest across the frame walk: t=2, child mesh",
              sh(expectHit(0, 0.5f, 0.5f, 2.f, {2.f, 0.f, 0.f}, nearMesh)),
              sh(game::physics::raycastModel(m, idx, {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f})));
    }
    {
        // The shipped shape that does have frames: stage06/stage16 collision.x is three
        // root frames, one mesh each, in frame order.
        xm::Model m;
        m.frames.resize(3);
        for (int f = 0; f < 3; ++f) {
            m.frames[static_cast<size_t>(f)].parent = -1;
            addMesh(m, {planeX(5.f - static_cast<float>(f))}, f);
        }
        check("3 root frames, one mesh each: order {0,1,2} (stage06 collision.x shape)",
              sorder(ModelIndex{{0, 1, 2}}), sorder(buildModelIndex(m)));
    }
    {
        // Totality: a mesh whose frame index is out of range is still visited.
        xm::Model m;
        m.frames.resize(1);
        m.frames[0].parent = -1;
        addMesh(m, {planeX(3.f)}, 99);
        const ModelIndex idx = buildModelIndex(m);
        check("mesh with out-of-range frame is still visited", sorder(ModelIndex{{0}}), sorder(idx));
        check("...and hittable", sh(expectHit(0, 0.5f, 0.5f, 3.f, {3.f, 0.f, 0.f}, 0)),
              sh(game::physics::raycastModel(m, idx, {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f})));
    }
    {
        // Early-out proof: mesh 0 holds the hit triangle first of three, mesh 1 exists.
        xm::Model m;
        addMesh(m, {planeX(2.f), planeX(5.f), planeX(7.f)});
        addMesh(m, {planeX(9.f)});
        const ModelIndex idx = buildModelIndex(m);

        RaycastStats s;
        const bool any = game::physics::raycastModelAny(m, idx, {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f}, 0.f, &s);
        check("any: stops after the first triangle of the first mesh", sb(true) + " " + sstats(RaycastStats{1, 1}),
              sb(any) + " " + sstats(s));

        s = RaycastStats{};
        const bool missAll = game::physics::raycastModelAny(m, idx, {0.f, 3.f, 0.f}, {1.f, 0.f, 0.f}, 0.f, &s);
        check("any: no hit tests every triangle of every mesh", sb(false) + " " + sstats(RaycastStats{4, 2}),
              sb(missAll) + " " + sstats(s));

        s = RaycastStats{};
        const bool anyCut = game::physics::raycastModelAny(m, idx, {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f}, 1.f, &s);
        check("any: maxDist=1 rejects every triangle", sb(false) + " " + sstats(RaycastStats{4, 2}),
              sb(anyCut) + " " + sstats(s));

        s = RaycastStats{};
        const bool anyNear = game::physics::raycastModelAny(m, idx, {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f}, 2.f, &s);
        check("any: maxDist=2 accepts the first triangle", sb(true) + " " + sstats(RaycastStats{1, 1}),
              sb(anyNear) + " " + sstats(s));

        // The convenience overload (builds the index per call) must agree exactly.
        check("raycastModel(model, ...) convenience == index overload",
              sh(game::physics::raycastModel(m, idx, {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f})),
              sh(game::physics::raycastModel(m, {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f})));
    }
    {
        // The empty container two shipped stages have (stage04/stage14 camera meshes).
        xm::Model m;
        addMesh(m, {});
        const ModelIndex idx = buildModelIndex(m);
        check("mesh with no triangles: order lists it, raycast misses",
              sorder(ModelIndex{{0}}) + " " + sh(RayHit{}),
              sorder(idx) + " " +
                  sh(game::physics::raycastModel(m, idx, {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f})));
    }
}

// ---------------------------------------------------------------------------------------
// 3. game::ICameraCollision over the raycast (+ the arena clamp composition)
// ---------------------------------------------------------------------------------------
void cameraCollisionCases() {
    section("3. CameraCollision: the arena camera clamp contract");

    const auto query = [](const CameraCollision& c, const glm::vec3& aim, const glm::vec3& eye) {
        const game::CameraClampResult r = c.queryClamp({aim, eye});
        return "hit=" + std::string(r.hit ? "1" : "0") + " hitDist=" + sf(r.hitDist);
    };

    {
        CameraCollision c;   // no mesh set: the "stage ships no collision_camera.x" case
        check("no mesh: no hit", "hit=0 hitDist=0", query(c, {0.f, 0.f, 0.f}, {5.f, 0.f, 0.f}));
        check("no mesh: empty() true", sb(true), sb(c.empty()));
    }
    {
        xm::Model m;
        addMesh(m, {planeX(4.f)});
        CameraCollision c;
        c.setMesh(&m);
        check("blocker at t=4 of a length-5 segment: hit 4",
              "hit=1 hitDist=4", query(c, {0.f, 0.f, 0.f}, {5.f, 0.f, 0.f}));
        check("mesh with triangles: empty() false", sb(false), sb(c.empty()));
    }
    {
        xm::Model m;
        addMesh(m, {planeX(5.f)});   // exactly at the desired eye
        CameraCollision c;
        c.setMesh(&m);
        check("blocker exactly at the desired eye: no hit (reference needs dist < segLen)",
              "hit=0 hitDist=0", query(c, {0.f, 0.f, 0.f}, {5.f, 0.f, 0.f}));
    }
    {
        xm::Model m;
        addMesh(m, {planeX(3.f)});
        CameraCollision c;
        c.setMesh(&m);
        check("blocker beyond the segment end (segment 2): no hit",
              "hit=0 hitDist=0", query(c, {0.f, 0.f, 0.f}, {2.f, 0.f, 0.f}));
    }
    {
        xm::Model m;
        addMesh(m, {planeX(-4.f)});   // behind the aim
        CameraCollision c;
        c.setMesh(&m);
        check("blocker behind the aim: no hit", "hit=0 hitDist=0",
              query(c, {0.f, 0.f, 0.f}, {5.f, 0.f, 0.f}));
    }
    {
        xm::Model m;
        addMesh(m, {planeX(3.f)});
        CameraCollision c;
        c.setMesh(&m);
        check("degenerate segment (aim == desiredEye): no hit", "hit=0 hitDist=0",
              query(c, {1.f, 2.f, 3.f}, {1.f, 2.f, 3.f}));
    }
    {
        xm::Model m;
        addMesh(m, {});   // 0-triangle mesh: stage04/stage14 collision_camera.x
        CameraCollision c;
        c.setMesh(&m);
        check("empty collision mesh: empty() true", sb(true), sb(c.empty()));
        check("empty collision mesh: no hit", "hit=0 hitDist=0",
              query(c, {0.f, 0.f, 0.f}, {5.f, 0.f, 0.f}));
    }
    {
        // clampHitDistance resolves a miss to the segment length (camera_collision.h:45).
        check("clampHitDistance(hit 4, seg 5) == 4", sf(4.f),
              sf(game::clampHitDistance({true, 4.f}, 5.f)));
        check("clampHitDistance(miss, seg 5) == 5", sf(5.f),
              sf(game::clampHitDistance({false, 0.f}, 5.f)));
    }
    {
        // The wiring the parent will use: query -> clampHitDistance -> arenaClampEye.
        xm::Model m;
        addMesh(m, {planeX(50.f)});
        CameraCollision c;
        c.setMesh(&m);
        const glm::vec3 aim(0.f), eye(100.f, 0.f, 0.f);
        const game::CameraClampResult r = c.queryClamp({aim, eye});
        const float seg = glm::length(eye - aim);
        const glm::vec3 clamped0 = render::arenaClampEye(aim, eye, game::clampHitDistance(r, seg), 0.f);
        check("composed clamp, margin=0: eye pulled to the blocker (50,0,0)", sv({50.f, 0.f, 0.f}),
              sv(clamped0));
        const glm::vec3 clamped20 = render::arenaClampEye(aim, eye, game::clampHitDistance(r, seg));
        checkNear("composed clamp, default margin=20: eye at x=30 (float path from a 0.3 scale)",
                  30.0, static_cast<double>(clamped20.x), 1e-4);
        check("composed clamp on a clear segment: desired eye unchanged", sv(eye),
              sv(render::arenaClampEye(aim, eye, game::clampHitDistance({false, 0.f}, seg), 0.f)));

        xm::Model near;
        addMesh(near, {planeX(10.f)});
        CameraCollision cn;
        cn.setMesh(&near);
        const game::CameraClampResult rn = cn.queryClamp({aim, eye});
        check("blocker inside the margin (10 < 20): eye collapses onto the aim", sv(aim),
              sv(render::arenaClampEye(aim, eye, game::clampHitDistance(rn, seg))));
    }
}

// ---------------------------------------------------------------------------------------
// 4. Independent cross-check: plane + edge half-space method, double precision
// ---------------------------------------------------------------------------------------
struct OracleTri {
    Tri tri;
    int mesh = -1;
    int face = -1;
};

struct OracleHit {
    bool   hit = false;
    double t = 0.0, u = 0.0, v = 0.0;
    int    mesh = -1, face = -1;
};

// Different algebraic route from the implementation under test: intersect the plane,
// then solve the barycentrics with a 2x2 Cramer system on the plane's dominant axis and
// classify against the three edges. Nothing is shared with intersectTriangle().
OracleHit oracleClosest(const std::vector<OracleTri>& tris, const glm::vec3& origin,
                        const glm::vec3& dir, float maxDist) {
    OracleHit best;
    const glm::dvec3 o(origin);
    const glm::dvec3 d(dir);
    for (const OracleTri& ot : tris) {
        const glm::dvec3 a(ot.tri.a), b(ot.tri.b), c(ot.tri.c);
        const glm::dvec3 e1 = b - a, e2 = c - a;
        const glm::dvec3 n  = glm::cross(e1, e2);
        const double     den = glm::dot(n, d);
        if (den == 0.0) continue;
        const double t = glm::dot(n, a - o) / den;
        if (t < 0.0) continue;
        if (maxDist > 0.f && t > static_cast<double>(maxDist)) continue;

        const glm::dvec3 p = o + d * t;
        const glm::dvec3 w = p - a;
        int    ax = 0;
        double an = std::fabs(n.x);
        if (std::fabs(n.y) > an) { ax = 1; an = std::fabs(n.y); }
        if (std::fabs(n.z) > an) { ax = 2; }
        const int i0 = (ax + 1) % 3;
        const int i1 = (ax + 2) % 3;
        const double det2 = e1[i0] * e2[i1] - e1[i1] * e2[i0];
        if (det2 == 0.0) continue;
        const double u = (w[i0] * e2[i1] - w[i1] * e2[i0]) / det2;
        const double v = (e1[i0] * w[i1] - e1[i1] * w[i0]) / det2;
        constexpr double kEps = 1e-9;
        if (u < -kEps || v < -kEps || u + v > 1.0 + kEps) continue;
        if (!best.hit || t < best.t) {
            best.hit  = true;
            best.t    = t;
            best.u    = u;
            best.v    = v;
            best.mesh = ot.mesh;
            best.face = ot.face;
        }
    }
    return best;
}

Tri rotateAboutCentroid(const Tri& t, float rx, float ry, float rz) {
    const glm::vec3 c = triCentroid(t);
    const glm::mat4 R = glm::rotate(glm::mat4(1.f), rx, {1.f, 0.f, 0.f}) *
                        glm::rotate(glm::mat4(1.f), ry, {0.f, 1.f, 0.f}) *
                        glm::rotate(glm::mat4(1.f), rz, {0.f, 0.f, 1.f});
    const glm::mat3 R3(R);
    return {c + R3 * (t.a - c), c + R3 * (t.b - c), c + R3 * (t.c - c)};
}

void crossCheckCases() {
    section("4. independent cross-check (plane + edge method, doubles)");

    uint32_t seed = 0x2f6e2b1u;
    const auto rnd = [&seed]() {
        seed = seed * 1664525u + 1013904223u;
        return static_cast<float>((seed >> 8) & 0xFFFFFFu) / static_cast<float>(0x1000000u);
    };

    // 24 triangles on 24 well-separated planes (x = 4*j, size <= ~2), grouped into 4
    // meshes and independently rotated per triangle. Separation keeps the closest hit
    // unambiguous, so face identity is checkable too.
    xm::Model model;
    std::vector<OracleTri> oracle;
    for (int meshIdx = 0; meshIdx < 4; ++meshIdx) {
        std::vector<Tri> tris;
        for (int k = 0; k < 6; ++k) {
            const int  j = meshIdx * 6 + k;
            const float x = 4.f * static_cast<float>(j);
            const Tri base = xFace(x);
            const Tri t = rotateAboutCentroid(base, rnd() * 6.2831853f, rnd() * 6.2831853f,
                                              rnd() * 6.2831853f);
            tris.push_back(t);
            oracle.push_back({t, meshIdx, k});
        }
        addMesh(model, tris);
    }
    const ModelIndex idx = buildModelIndex(model);

    const int    kRays      = 2000;
    size_t       mineHits = 0, oracleHits = 0, hitMissMismatch = 0, identityMismatch = 0;
    double       maxDt = 0.0, maxDu = 0.0, maxDv = 0.0;
    for (int i = 0; i < kRays; ++i) {
        const glm::vec3 origin(rnd() * 104.f - 6.f, rnd() * 40.f - 20.f, rnd() * 40.f - 20.f);
        glm::vec3       dir;
        if (i % 5 == 0) {
            // Fully random direction: exercises misses.
            dir = glm::vec3(rnd() * 2.f - 1.f, rnd() * 2.f - 1.f, rnd() * 2.f - 1.f);
        } else {
            // Aimed near a random triangle's centroid, jittered so some rays miss the
            // edges: exercises hits with varied barycentrics.
            const OracleTri& aim = oracle[static_cast<size_t>(rnd() * static_cast<float>(oracle.size()))];
            const glm::vec3  jitter(rnd() * 3.f - 1.5f, rnd() * 3.f - 1.5f, rnd() * 3.f - 1.5f);
            dir = triCentroid(aim.tri) + jitter - origin;
        }
        dir = glm::normalize(dir);

        const RayHit mine = game::physics::raycastModel(model, idx, origin, dir, 0.f);
        const OracleHit ref = oracleClosest(oracle, origin, dir, 0.f);
        if (mine.hit) ++mineHits;
        if (ref.hit) ++oracleHits;
        if (mine.hit != ref.hit) { ++hitMissMismatch; continue; }
        if (!mine.hit) continue;
        const double dt = std::fabs(static_cast<double>(mine.dist) - ref.t);
        maxDt = std::max(maxDt, dt);
        if (dt > 1e-9) {
            if (mine.mesh != ref.mesh || static_cast<int>(mine.faceIndex) != ref.face) ++identityMismatch;
        }
        maxDu = std::max(maxDu, std::fabs(static_cast<double>(mine.u) - ref.u));
        maxDv = std::max(maxDv, std::fabs(static_cast<double>(mine.v) - ref.v));
    }
    info("rays=" + sz(kRays) + "  mine hits=" + sz(mineHits) + "  oracle hits=" + sz(oracleHits) +
         "  max|dt|=" + sd(maxDt) + "  max|du|=" + sd(maxDu) + "  max|dv|=" + sd(maxDv));
    check("cross-check: hit/miss agreement", sz(0), sz(hitMissMismatch));
    check("cross-check: mesh+face identity on non-tied hits", sz(0), sz(identityMismatch));
    // Tolerances bound float32 noise against a float64 reference on geometry spanning
    // ~100 units (ulp(100) = 7.6e-6), not agreement with D3DXIntersect.
    checkNear("cross-check: max |dt| against the float64 oracle", 0.0, maxDt, 1e-4);
    checkNear("cross-check: max |du| against the float64 oracle", 0.0, maxDu, 2e-4);
    checkNear("cross-check: max |dv| against the float64 oracle", 0.0, maxDv, 2e-4);
    check("cross-check exercised both hits and misses", sb(true),
          sb(mineHits > 0 && mineHits < static_cast<size_t>(kRays)));
}

// ---------------------------------------------------------------------------------------
// 5. Real assets
// ---------------------------------------------------------------------------------------
const char* kDefaultMeshes[] = {
    "Higurashi-Daybreak/data/stage06/collision_camera.X",   // largest camera mesh: 628 tris
    "Higurashi-Daybreak/data/stage21/collision_camera.X",   // 299 tris
    "Higurashi-Daybreak/data/stage04/collision_camera.x",   // shipped empty: 0 tris
};

bool loadAsset(const char* arg, xm::Model& model, std::string& path) {
    std::vector<std::string> candidates;
    if (arg && *arg) candidates.emplace_back(arg);
    else {
        for (const char* c : kDefaultMeshes) candidates.emplace_back(c);
    }
    for (const std::string& c : candidates) {
        try {
            model = xm::loadFile(c);
        } catch (const std::exception& e) {
            std::printf("  ....   load failed: %s (%s)\n", c.c_str(), e.what());
            continue;
        }
        path = c;
        return true;
    }
    return false;
}

size_t meshTriangles(const xm::Model& m) {
    size_t n = 0;
    for (const xm::Mesh& mesh : m.meshes) n += mesh.indices.size() / 3;
    return n;
}

// ---------------------------------------------------------------------------------------
// 6. Cost per ray// ---------------------------------------------------------------------------------------
struct PerfResult {
    double usClosest = 0.0, usAny = 0.0;
    double trisPerRayClosest = 0.0, trisPerRayAny = 0.0;
    double hitRate = 0.0;
};

// Bounds-to-bounds rays: origin and direction target are random points in the mesh's
// (slightly inflated) bounding box. That is the shape of the camera clamp's aim->eye
// segment, i.e. an arbitrary direction across the stage, not a ray aimed at a normal.
PerfResult measure(const xm::Model& model, const ModelIndex& index, size_t rays, float maxDist) {
    glm::vec3 lo(0.f), hi(0.f);
    bool      first = true;
    for (const xm::Mesh& m : model.meshes) {
        for (const xm::Vertex& v : m.vertices) {
            if (first) { lo = hi = v.pos; first = false; }
            lo = glm::min(lo, v.pos);
            hi = glm::max(hi, v.pos);
        }
    }
    const glm::vec3 pad = (hi - lo) * 0.1f + glm::vec3(1.f);
    lo -= pad;
    hi += pad;

    uint32_t     seed = 0x9e3779b9u;
    const auto   rnd = [&seed]() {
        seed = seed * 1664525u + 1013904223u;
        return static_cast<float>((seed >> 8) & 0xFFFFFFu) / static_cast<float>(0x1000000u);
    };
    std::vector<glm::vec3> origins(rays), dirs(rays);
    for (size_t i = 0; i < rays; ++i) {
        const glm::vec3 a = lo + (hi - lo) * glm::vec3(rnd(), rnd(), rnd());
        const glm::vec3 b = lo + (hi - lo) * glm::vec3(rnd(), rnd(), rnd());
        origins[i] = a;
        dirs[i]    = glm::normalize(b - a);
    }

    PerfResult r;
    const int reps = 3;
    for (int rep = 0; rep < reps; ++rep) {
        auto t0 = std::chrono::steady_clock::now();
        size_t hits = 0;
        for (size_t i = 0; i < rays; ++i) {
            if (game::physics::raycastModel(model, index, origins[i], dirs[i], maxDist).hit) ++hits;
        }
        auto t1 = std::chrono::steady_clock::now();
        const double us = std::chrono::duration<double, std::micro>(t1 - t0).count() /
                          static_cast<double>(rays);
        if (rep == 0 || us < r.usClosest) r.usClosest = us;
        if (rep == 0) r.hitRate = static_cast<double>(hits) / static_cast<double>(rays);

        t0 = std::chrono::steady_clock::now();
        for (size_t i = 0; i < rays; ++i) {
            game::physics::raycastModelAny(model, index, origins[i], dirs[i], maxDist);
        }
        t1 = std::chrono::steady_clock::now();
        const double usAny = std::chrono::duration<double, std::micro>(t1 - t0).count() /
                             static_cast<double>(rays);
        if (rep == 0 || usAny < r.usAny) r.usAny = usAny;
    }

    // Separate counting pass (the stats hook is off in the timed loops above).
    RaycastStats s;
    for (size_t i = 0; i < rays; ++i) {
        game::physics::raycastModel(model, index, origins[i], dirs[i], maxDist, &s);
    }
    RaycastStats sa;
    for (size_t i = 0; i < rays; ++i) {
        game::physics::raycastModelAny(model, index, origins[i], dirs[i], maxDist, &sa);
    }
    r.trisPerRayClosest = static_cast<double>(s.trianglesTested) / static_cast<double>(rays);
    r.trisPerRayAny     = static_cast<double>(sa.trianglesTested) / static_cast<double>(rays);
    return r;
}

void printPerf(const std::string& label, const xm::Model& model, const ModelIndex& index,
               size_t meshes, size_t tris, size_t rays, float maxDist) {
    const PerfResult r = measure(model, index, rays, maxDist);
    std::printf("  %-34s meshes=%-3zu tris=%-6zu rays=%-7zu  closest=%.4f us/ray (%.1f tris/ray)"
                "  any=%.4f us/ray (%.1f tris/ray)  hits=%.1f%%\n",
                label.c_str(), meshes, tris, rays, r.usClosest, r.trisPerRayClosest, r.usAny,
                r.trisPerRayAny, r.hitRate * 100.0);
    std::printf("  %-34s (%zu rays x 60 fps: closest %.3f ms/frame, any %.3f ms/frame)\n", "", rays,
                r.usClosest * 60.0 / 1000.0, r.usAny * 60.0 / 1000.0);
}

// Flat grid of 2*cols*rows triangles in the plane y=0, spanning [-extent,extent]^2:
// a stand-in for a stage floor at a controllable triangle count.
xm::Model gridModel(int cols, int rows, float extent) {
    xm::Model model;
    std::vector<Tri> tris;
    tris.reserve(static_cast<size_t>(cols) * rows * 2);
    const float dx = 2.f * extent / static_cast<float>(cols);
    const float dz = 2.f * extent / static_cast<float>(rows);
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            const float x0 = -extent + dx * static_cast<float>(i);
            const float z0 = -extent + dz * static_cast<float>(j);
            const float x1 = x0 + dx, z1 = z0 + dz;
            tris.push_back({{x0, 0.f, z0}, {x1, 0.f, z0}, {x0, 0.f, z1}});
            tris.push_back({{x1, 0.f, z0}, {x1, 0.f, z1}, {x0, 0.f, z1}});
        }
    }
    addMesh(model, tris, -1, "grid");
    return model;
}

// ---------------------------------------------------------------------------------------
// 5b. Real-asset smoke test (uses measure() above)
// ---------------------------------------------------------------------------------------
void realAssetCases(const xm::Model& model, const std::string& path, float& outUsClosest,
                    float& outUsAny, size_t& outTris, std::string& outPerfNote) {
    section("5. real stage asset");
    const size_t tris = meshTriangles(model);
    outTris = tris;
    std::printf("  ....   %s: encoding=%s frames=%zu meshes=%zu triangles=%zu\n", path.c_str(),
                model.stats.encoding.c_str(), model.frames.size(), model.meshes.size(), tris);

    const ModelIndex idx = buildModelIndex(model);
    check("index covers every mesh", sz(model.meshes.size()), sz(idx.meshOrder.size()));

    if (tris == 0) {
        // stage04/stage14 ship a collision_camera.x that parses to no geometry: the
        // camera path must degrade to "no hit", not crash or clamp to zero.
        CameraCollision c;
        c.setMesh(&model);
        const game::CameraClampResult r = c.queryClamp({{0.f, 0.f, 0.f}, {5.f, 0.f, 0.f}});
        check("empty real camera mesh: empty() true", sb(true), sb(c.empty()));
        check("empty real camera mesh: query no hit",
              "hit=0 hitDist=0",
              "hit=" + std::string(r.hit ? "1" : "0") + " hitDist=" + sf(r.hitDist));
        outPerfNote = "no triangles: perf measurement not applicable";
        return;
    }

    // Every triangle is re-hit from 100 units along its normal, and the model-level
    // answer is checked against the container-level one. Two assertions are correct by
    // construction on overlapping stage geometry (a first draft wrongly assumed the
    // tested triangle is the closest hit, which is only true on isolated geometry):
    //   * the per-container cast hits something at t <= 100 + tol — no blocker can sit
    //     behind the offset origin;
    //   * the model-level hit's reported barycentrics reconstruct its reported point,
    //     and that point lies on the reported triangle's plane. That is the invariant
    //     that makes u,v trustworthy on real, large-coordinate meshes.
    // Tolerances are float noise bounds (coordinates reach ~9000, ulp ~1e-3), unlike the
    // analytic cases above.
    size_t misses = 0, degenerate = 0, modelAnyHits = 0, reconChecked = 0, farViolations = 0,
           faceViolations = 0;
    double worstT = 0.0, worstRecon = 0.0, worstPlane = 0.0;
    for (const int32_t mi : idx.meshOrder) {
        const xm::Mesh&         m    = model.meshes[static_cast<size_t>(mi)];
        const TriangleMeshView  view = game::physics::meshView(m);
        for (size_t f = 0; f + 2 < m.indices.size(); f += 3) {
            const Tri t{m.vertices[m.indices[f + 0]].pos, m.vertices[m.indices[f + 1]].pos,
                        m.vertices[m.indices[f + 2]].pos};
            const glm::vec3 n = triNormal(t);
            if (n == glm::vec3(0.f)) { ++degenerate; continue; }
            const glm::vec3 o = triCentroid(t) + n * 100.f;
            const RayHit    h = game::physics::raycastTriangles(view, o, -n, 200.f);
            if (!h.hit) { ++misses; continue; }
            worstT = std::max(worstT, static_cast<double>(h.dist));
            if (game::physics::raycastModelAny(model, idx, o, -n, 200.f)) ++modelAnyHits;

            const RayHit c = game::physics::raycastModel(model, idx, o, -n, 200.f);
            if (!c.hit) continue;
            // The model walk minimizes over containers, so it can never be farther than
            // the single-container answer for the same ray (identical arithmetic).
            if (c.dist > h.dist) ++farViolations;
            if (c.mesh < 0 || static_cast<size_t>(c.mesh) >= model.meshes.size()) {
                ++faceViolations;
                continue;
            }
            const xm::Mesh& cm = model.meshes[static_cast<size_t>(c.mesh)];
            const size_t    i0 = 3 * static_cast<size_t>(c.faceIndex) + 0;
            if (i0 + 2 >= cm.indices.size()) {
                ++faceViolations;
                continue;
            }
            const glm::vec3 a = cm.vertices[cm.indices[i0 + 0]].pos;
            const glm::vec3 b = cm.vertices[cm.indices[i0 + 1]].pos;
            const glm::vec3 d = cm.vertices[cm.indices[i0 + 2]].pos;
            const glm::vec3 recon = (1.f - c.u - c.v) * a + c.u * b + c.v * d;
            worstRecon = std::max(worstRecon, static_cast<double>(glm::length(recon - c.point)));
            worstPlane =
                std::max(worstPlane, std::fabs(static_cast<double>(glm::dot(triNormal({a, b, d}),
                                                                           c.point - a))));
            ++reconChecked;
        }
    }
    info("per-container re-hit; degenerate (zero-area) skipped=" + sz(degenerate) +
         "  worst t=" + sd(worstT) + "  barycentric reconstruction checked on " + sz(reconChecked) +
         " closest hits");
    check("real mesh: every non-degenerate triangle re-hit from 100 units out", sz(0), sz(misses));
    check("real mesh: model-level any-hit on every one of those rays", sz(tris - degenerate),
          sz(modelAnyHits));
    check("real mesh: model closest hit never farther than the container hit", sz(0), sz(farViolations));
    check("real mesh: closest hit always reported against a real triangle", sz(0), sz(faceViolations));
    check("real mesh: closest hit recomputed for every ray", sz(tris - degenerate), sz(reconChecked));
    checkLe("real mesh: every re-hit at t <= 100 + tolerance (nothing behind the offset)",
            100.05, worstT);
    checkLe("real mesh: |barycentric reconstruction - reported point| <= 0.05", 0.05, worstRecon);
    checkLe("real mesh: |reported point - reported triangle plane| <= 0.05", 0.05, worstPlane);

    // Cost, with the camera clamp's workload shape and maxDist = the segment length.
    const size_t rays = std::min<size_t>(300000, std::max<size_t>(20000, 20000000 / std::max<size_t>(tris, 1)));
    glm::vec3 lo(0.f), hi(0.f);
    bool first = true;
    for (const xm::Mesh& m : model.meshes) {
        for (const xm::Vertex& v : m.vertices) {
            if (first) { lo = hi = v.pos; first = false; }
            lo = glm::min(lo, v.pos);
            hi = glm::max(hi, v.pos);
        }
    }
    const float maxDist = glm::length(hi - lo);
    const PerfResult r = measure(model, idx, rays, maxDist);
    outUsClosest = static_cast<float>(r.usClosest);
    outUsAny     = static_cast<float>(r.usAny);
    std::printf("  %-24s meshes=%-3zu tris=%-6zu rays=%-7zu  closest=%.4f us/ray (%.1f tris/ray)"
                "  any=%.4f us/ray (%.1f tris/ray)  hits=%.1f%%  maxDist=%.1f\n",
                "real (camera-clamp rays)", model.meshes.size(), tris, rays, r.usClosest,
                r.trisPerRayClosest, r.usAny, r.trisPerRayAny, r.hitRate * 100.0,
                static_cast<double>(maxDist));
}

}  // namespace

int main(int argc, char** argv) {
    std::printf("raycast_analytic — game::physics::raycast (foundation, no D3DX)\n");
    std::printf("compiler: GNU C++ %d.%d.%d   (built %s %s)\n", __GNUC__, __GNUC_MINOR__,
                __GNUC_PATCHLEVEL__, __DATE__, __TIME__);

    triangleCases();
    modelCases();
    cameraCollisionCases();
    crossCheckCases();

    xm::Model   real;
    std::string realPath;
    float       realUsClosest = 0.f, realUsAny = 0.f;
    size_t      realTris = 0;
    std::string perfNote;
    const bool  haveReal = loadAsset(argc > 1 ? argv[1] : nullptr, real, realPath);
    if (haveReal) {
        realAssetCases(real, realPath, realUsClosest, realUsAny, realTris, perfNote);
    } else {
        section("5. real stage asset");
        info("skipped: no stage collision mesh found; pass one as argv[1]");
    }

    section("6. cost per ray (best of 3 timed passes; stats hook off while timing)");
    if (haveReal && realTris > 0) {
        std::printf("  %-24s tris=%-6zu closest=%.4f us/ray  any=%.4f us/ray\n", "real mesh",
                    realTris, static_cast<double>(realUsClosest), static_cast<double>(realUsAny));
    } else if (haveReal) {
        info(std::string("real mesh: ") + perfNote);
    }
    {
        xm::Model g = gridModel(18, 18, 1000.f);   // 648 triangles: the largest shipped mesh is 628
        const ModelIndex gidx = buildModelIndex(g);
        printPerf("synthetic grid 648 tris", g, gidx, g.meshes.size(), meshTriangles(g), 30000, 0.f);
    }
    {
        xm::Model g = gridModel(128, 128, 1000.f);   // 32768 triangles: the BVH question
        const ModelIndex gidx = buildModelIndex(g);
        printPerf("synthetic grid 32768 tris", g, gidx, g.meshes.size(), meshTriangles(g), 2000, 0.f);
    }

    std::printf("\nchecks=%d failures=%d\n", g_checks, g_failures);
    std::printf("RAYCAST_ANALYTIC: %s\n", g_failures == 0 ? "ok" : "FAIL");
    return g_failures == 0 ? 0 : 1;
}
