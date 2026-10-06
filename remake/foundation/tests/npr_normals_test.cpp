// tests/npr_normals_test.cpp — the secondary lighting normals and generated shadow mask
// (issue #25, experiments E and F).
//
// Device-free on purpose. What this half of the experiment can get wrong is geometry: a
// cluster radius that merges a whole limb into one normal, a blend that flips a normal and
// lights the back of a hair card, a mask that comes out constant (which would make the F
// experiment a no-op that looks exactly like a technique with no visible effect), or a
// stage mesh picking up a stream it should not have.
//
// What it does NOT prove: that the WGSL lights with the stream, or that the shading looks
// better. Both are captures — see tests/npr_experiments.py.
//
// Usage: npr_normals_test <install-dir>   (exit 77 without one, like the capture tests)
#include <cmath>
#include <cstdio>
#include <filesystem>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#define XMODEL_IMPLEMENTATION
#include "assets/xmodel.h"
#include "render/npr_normals.h"

namespace {

int g_checks = 0, g_failures = 0;

void check(bool ok, const std::string& what) {
    ++g_checks;
    if (!ok) {
        ++g_failures;
        std::printf("  FAIL %s\n", what.c_str());
    }
}

// A quad in the XZ plane: two triangles, four coincident-in-pairs vertices whose geometric
// normals all point up. Smoothing must not move them and the mask must stay near its
// up-facing end.
xm::Mesh flatQuad() {
    xm::Mesh m;
    m.name = "quad";
    const glm::vec3 n(0.f, 1.f, 0.f);
    // (-10,-10) -> (10,-10) -> (10,10) -> (-10,10): the winding whose right-handed cross
    // product is +Y, which is what the builder accumulates (and what the shipped assets
    // are authored in).
    // Wound so the right-handed cross product points DOWN, which is the shipped assets'
    // convention (clockwise-front in a left-handed space) and therefore what
    // kNprAssetWinding compensates for.
    const glm::vec3 corners[4] = {{-10.f, 0.f, -10.f}, {10.f, 0.f, -10.f},
                                  {10.f, 0.f, 10.f}, {-10.f, 0.f, 10.f}};
    for (int i = 0; i < 4; ++i) {
        xm::Vertex v;
        v.pos = corners[i];
        v.normal = n;
        m.vertices.push_back(v);
    }
    m.indices = {0, 1, 2, 0, 2, 3};
    xm::Submesh s;
    s.indexCount = 6;
    m.submeshes.push_back(s);
    m.materials.push_back(xm::Material{});
    return m;
}

// A 2x2 grid of a sphere's worth of directions, welded: every vertex carries a DIFFERENT
// geometric normal (so a smoothing that did nothing would be invisible) while the faces
// are large enough to have a real area weight.
xm::Mesh facetedDome() {
    xm::Mesh m;
    m.name = "dome";
    const int n = 5;
    for (int y = 0; y <= n; ++y) {
        for (int x = 0; x <= n; ++x) {
            const float u = (float)x / (float)n, v = (float)y / (float)n;
            const float a = u * 3.14159265f * 0.5f, b = v * 3.14159265f * 0.5f;
            const glm::vec3 p(std::sin(a) * std::cos(b), std::cos(a), std::sin(a) * std::sin(b));
            xm::Vertex vert;
            vert.pos = p * 50.f;
            // Deliberately noisy: a face-ish normal plus a wobble, which is what an
            // exported seam looks like.
            vert.normal = glm::normalize(p + glm::vec3(0.20f * ((x % 2) ? 1.f : -1.f), 0.f,
                                                       0.20f * ((y % 2) ? 1.f : -1.f)));
            m.vertices.push_back(vert);
        }
    }
    for (int y = 0; y < n; ++y)
        for (int x = 0; x < n; ++x) {
            const uint32_t i = (uint32_t)(y * (n + 1) + x);
            m.indices.push_back(i);
            m.indices.push_back(i + (uint32_t)(n + 1));
            m.indices.push_back(i + 1);
            m.indices.push_back(i + 1);
            m.indices.push_back(i + (uint32_t)(n + 1));
            m.indices.push_back(i + (uint32_t)(n + 1) + 1);
        }
    xm::Submesh s;
    s.indexCount = (uint32_t)m.indices.size();
    m.submeshes.push_back(s);
    m.materials.push_back(xm::Material{});
    return m;
}

// The angle between the geometric normal and the one the lighting would use.
float angleDeg(const glm::vec3& a, const glm::vec3& b) {
    const float d = glm::dot(glm::normalize(a), glm::normalize(b));
    return glm::degrees(std::acos(glm::clamp(d, -1.f, 1.f)));
}

void syntheticCases() {
    // 1. A flat quad: the cluster normal is the geometric one, so nothing moves and the
    //    mask stays on the up-facing end (above neutral 0.5, below 1).
    std::vector<xm::NprVertex> out;
    const xm::Mesh quad = flatQuad();
    check(render::buildNprNormals(quad, out) == 4, "a flat quad fills every vertex");
    for (size_t i = 0; i < out.size(); ++i) {
        const glm::vec4& n = out[i].npr;
        check(angleDeg(glm::vec3(n), glm::vec3(0.f, 1.f, 0.f)) < 0.5f,
              "a flat quad's secondary normal stays the geometric one");
        check(n.w > 0.5f && n.w <= 1.f, "an up-facing quad's mask is above neutral");
    }

    // 2. The dome: the noisy geometric normals must be pulled towards the smooth surface,
    //    i.e. the secondary normal must be CLOSER to the sphere's radial direction than the
    //    geometric one on average, and no vertex may end up flipped.
    const xm::Mesh dome = facetedDome();
    std::vector<xm::NprVertex> dout;
    const size_t filled = render::buildNprNormals(dome, dout);
    check(filled == dome.vertices.size(), "the dome fills every vertex");
    double geoErr = 0.0, nprErr = 0.0;
    size_t counted = 0, flipped = 0;
    for (size_t i = 0; i < dout.size(); ++i) {
        const glm::vec3 radial = glm::normalize(dome.vertices[i].pos);
        geoErr += angleDeg(dome.vertices[i].normal, radial);
        nprErr += angleDeg(glm::vec3(dout[i].npr), radial);
        if (angleDeg(dome.vertices[i].normal, glm::vec3(dout[i].npr)) > 90.f) ++flipped;
        ++counted;
    }
    geoErr /= (double)counted;
    nprErr /= (double)counted;
    std::printf("  dome: mean error vs the smooth surface %.2f deg (geometric) -> %.2f deg "
                "(secondary)\n", geoErr, nprErr);
    check(nprErr < geoErr * 0.5, "smoothing at least halves the normal error on a noisy dome");
    check(flipped == 0, "no secondary normal is flipped against its geometric one");

    // 3. smoothing = 0 is the identity: the experiment must be able to say "no smoothing"
    //    without changing the mesh.
    std::vector<xm::NprVertex> idout;
    render::buildNprNormals(dome, idout, /*smoothing=*/0.f);
    for (size_t i = 0; i < idout.size(); ++i)
        check(angleDeg(glm::vec3(idout[i].npr), dome.vertices[i].normal) < 0.5f,
              "smoothing=0 keeps the geometric normal");

    // 4. maskBias = 0 pins the mask at neutral, which is what makes the F experiment's
    //    "mask off" arm a real control rather than a slightly different mask.
    std::vector<xm::NprVertex> mout;
    render::buildNprNormals(dome, mout, 0.85f, /*maskBias=*/0.f);
    for (const xm::NprVertex& v : mout)
        check(std::fabs(v.npr.w - 0.5f) < 1e-6f, "maskBias=0 pins the mask at neutral");

    // 5. An empty mesh is the "no stream" case, not a crash.
    xm::Mesh empty;
    std::vector<xm::NprVertex> eout;
    check(render::buildNprNormals(empty, eout) == 0, "an empty mesh builds nothing");

    // 6. The winding convention is inferred from the mesh's own normals, not assumed: the
    //    same quad wound the other way must produce the SAME secondary normals, because
    //    the orientation hint flips the accumulated cross products. Getting this wrong is
    //    silent — it empties the stream, which then looks exactly like a technique with no
    //    visible effect (it did, on all four of rena's meshes).
    xm::Mesh rev = flatQuad();
    rev.indices = {0, 2, 1, 0, 3, 2};
    std::vector<xm::NprVertex> rout;
    check(render::buildNprNormals(rev, rout) == 4,
          "a reversed winding still fills every vertex (the orientation hint flips it)");
    for (size_t i = 0; i < rout.size(); ++i)
        check(angleDeg(glm::vec3(rout[i].npr), glm::vec3(0.f, 1.f, 0.f)) < 0.5f,
              "a reversed winding's secondary normal still points the way its normals do");

    // 7. A mesh whose normals are all zero has no hint to give: the raw cross product is
    //    used, and the flip guard is then free to reject it. It must not crash and must
    //    not fabricate a direction.
    xm::Mesh blind = flatQuad();
    for (xm::Vertex& v : blind.vertices) v.normal = glm::vec3(0.f);
    std::vector<xm::NprVertex> bout;
    render::buildNprNormals(blind, bout);
}

// The real assets: the mesh the experiment actually shades must get a stream whose normals
// are close to (not identical to) the geometric ones, and the shipped stage must not need
// one at all — the renderer only asks for character/weapon roles.
void assetCases(const std::string& install) {
    const std::string character = install + "/data/rena/00.X";
    xm::Model model = xm::loadFile(character);
    if (model.meshes.empty()) {
        std::printf("  (no %s: asset cases skipped)\n", character.c_str());
        return;
    }
    size_t meshes = 0, verts = 0, filled = 0, moved = 0;
    double sum = 0.0;
    float worst = 0.f;
    bool masksVary = false;
    float maskLo = 1.f, maskHi = 0.f;
    for (const xm::Mesh& mesh : model.meshes) {
        std::vector<xm::NprVertex> out;
        const size_t got = render::buildNprNormals(mesh, out);
        if (got == 0) continue;
        ++meshes;
        verts += mesh.vertices.size();
        filled += got;
        for (size_t i = 0; i < out.size(); ++i) {
            const glm::vec4& n = out[i].npr;
            if (glm::dot(glm::vec3(n), glm::vec3(n)) < 0.25f) continue;
            const float deg = angleDeg(mesh.vertices[i].normal, glm::vec3(n));
            if (deg > 90.f) {
                check(false, "a shipped mesh got a flipped secondary normal");
                return;
            }
            if (deg > 0.5f) ++moved;
            sum += deg;
            worst = std::max(worst, deg);
            maskLo = std::min(maskLo, n.w);
            maskHi = std::max(maskHi, n.w);
        }
    }
    std::printf("  rena 00.X: %zu mesh(es), %zu/%zu vertices filled, %zu moved "
                "(mean %.2f deg, worst %.2f), mask %.3f..%.3f\n",
                meshes, filled, verts, moved, filled ? sum / (double)filled : 0.0, worst,
                maskLo, maskHi);
    check(meshes > 0, "the shipped character has meshes with a usable stream");
    check(filled > verts / 2, "most of the character's vertices get a secondary normal");
    check(moved > filled / 4, "smoothing actually moves a quarter of the normals");
    check(worst < 90.f, "no shipped normal is flipped");
    masksVary = maskHi - maskLo > 0.05f;
    check(masksVary, "the generated mask varies across the character");
}

}  // namespace

int main(int argc, char** argv) {
    // The synthetic cases need nothing but glm, so they always run. The asset case needs
    // one shipped mesh: without it the test says so and exits 77, the same
    // skip-without-the-install contract the capture tests use, so a CI box without the
    // game data does not report a false failure.
    //
    // "There is an install" has to mean the directory is there, not that CMake passed a
    // path: CMake always passes one, so an argument-only check ran the asset cases on a
    // runner with no game data and aborted on the missing mesh (issue #28).
    syntheticCases();
    std::error_code ec;
    const bool haveInstall = argc > 1 && argv[1][0] != '\0' &&
                             std::filesystem::is_directory(argv[1], ec);
    if (haveInstall) {
        assetCases(argv[1]);
    } else {
        std::printf("  (no game install at %s: asset cases skipped)\n",
                    argc > 1 && argv[1][0] ? argv[1] : "(no path given)");
    }
    std::printf("\nchecks=%d failures=%d\n", g_checks, g_failures);
    if (g_failures != 0) {
        std::printf("NPR NORMALS: FAIL\n");
        return 1;
    }
    if (!haveInstall) {
        std::printf("NPR NORMALS: skipped (no install)\n");
        return 77;
    }
    std::printf("NPR NORMALS: ok\n");
    return 0;
}
