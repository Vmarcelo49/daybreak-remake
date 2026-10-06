#pragma once
// Stylized / simplified lighting normals (issue #25, experiment E) and the generated
// shadow-threshold mask (experiment F).
//
// In its own header, not in scene_renderer.h, for one reason: this is the half of the
// experiment that needs no device. Keeping it out of the WebGPU-including header lets
// tests/npr_normals_test.cpp pin the geometry device-free, which is where the failure
// modes live (a cluster radius that merges a whole limb, a blend that inverts the
// terminator, a mask that is constant).
//
// Nothing here is recovered from the original: the shipped .X has no secondary normal and
// no shadow mask, so this is a PORT-SIDE authoring stand-in. The mesh keeps its geometric
// normal, its silhouette and its skinning; only the lighting reads this.
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <unordered_map>
#include <vector>

#include <glm/glm.hpp>

#include "assets/xmodel.h"

namespace render {

// ---------------------------------------------------------------------------------------
// What it does, and why this shape:
//   * vertices are accumulated into clusters by their bind-pose position quantised to
//     1/256 of the mesh's bounding-box diagonal. Coincident vertices (every UV/normal
//     seam the exporter split) therefore land in one cluster, which is the whole point:
//     the seams are what make a shaded mesh's normals noisy where the artist authored
//     one smooth form.
//   * the cluster normal is the AREA-WEIGHTED average of its faces' geometric normals
//     (the cross product's magnitude is twice the area, so summing unnormalised cross
//     products weights by area for free) — the Guilty Gear note's "simplifying vertex
//     normals to obtain broad anime-like shadows while retaining detailed geometry".
//   * each vertex is blended towards its cluster normal by `smoothing`, 0 leaving the
//     geometric normal and 1 taking the cluster's. The blend rather than a hard replace
//     is deliberate: a hard replace collapses a curved surface's normals into its faces,
//     and the experiment wants "coarser", not "a different mesh".
//   * normals the cluster average would flip (>90 degrees off the geometric one) keep the
//     geometric normal. On a thin part (a skirt panel, a sleeve) the two sides are
//     usually further apart than the cluster radius, but a hair card's front and back can
//     cluster together, and a flipped normal there lights the back of the card as if it
//     faced the camera.
//   * the mask (NprVertex::npr.w) is a generated scalar, not authored data: it is high on
//     up-facing surfaces and low on down-facing ones, which is where an anime shadow read
//     wants the band to fall (under the chin, under the hair, under a sleeve). The shader
//     turns it into a bias on its band edges; `maskBias` scales how far from neutral 0.5
//     it is allowed to go, and 0 is the E-only arm where the mask does not ride along.
//
// `out` receives one NprVertex per mesh vertex. Returns the number of vertices that got a
// cluster normal (0 for a mesh with no usable faces, which is the "no stream" case).
// ---------------------------------------------------------------------------------------
inline size_t buildNprNormals(const xm::Mesh& mesh, std::vector<xm::NprVertex>& out,
                              float smoothing = 1.f, float maskBias = 1.f) {
    out.assign(mesh.vertices.size(), xm::NprVertex{});
    const size_t n = mesh.vertices.size();
    if (n == 0 || mesh.indices.size() < 3) return 0;

    glm::vec3 lo = mesh.vertices[0].pos, hi = mesh.vertices[0].pos;
    for (const xm::Vertex& v : mesh.vertices) {
        lo = glm::min(lo, v.pos);
        hi = glm::max(hi, v.pos);
    }
    // The cluster grid. 1/16 of the bounding-box diagonal: a head, a forearm or a skirt
    // panel is several cells across, so a cluster is a small patch of surface and not a
    // limb. (An earlier 1/256 was so fine that a cluster held one triangle, which made the
    // "smoothed" normal differ from the geometric one by 10 degrees on average and changed
    // NO pixel of the capture — a coarse normal has to be coarse at the scale the shading
    // reads, not at the scale the exporter's seams are at.)
    const float inv = 16.f / glm::max(glm::length(hi - lo), 1e-6f);

    // The cluster key is the integer coordinate triple itself, packed into one int64 with
    // a bias. A hash would be smaller but cannot be stepped, and stepping is exactly what
    // the neighbour passes below need.
    constexpr int64_t kBias = 1 << 19;
    constexpr int64_t kSpan = 1 << 20;
    auto coordOf = [&](const glm::vec3& p) {
        return glm::ivec3((int)std::lround(p.x * inv), (int)std::lround(p.y * inv),
                          (int)std::lround(p.z * inv));
    };
    auto packOf = [&](const glm::ivec3& c) {
        return ((int64_t)(c.x + kBias) * kSpan + (c.y + kBias)) * kSpan + (c.z + kBias);
    };

    // Which way a triangle's right-handed cross product points is a property of the
    // authoring convention, and the shipped .X files are clockwise-front in a left-handed
    // space — so their cross products point INWARD. Rather than make every caller state a
    // convention (and get it wrong once, which silently produced an empty stream on all
    // four of rena's meshes), the mesh's own shading normals are the hint: each face is
    // oriented by the sign of its agreement with its vertices' geometric normals. A mesh
    // whose normals are themselves inconsistent gets the raw cross product, which the flip
    // guard below then rejects rather than using backwards.
    float orient = 0.f;
    for (size_t i = 0; i + 2 < mesh.indices.size(); i += 3) {
        const uint32_t a = mesh.indices[i], b = mesh.indices[i + 1], c = mesh.indices[i + 2];
        if (a >= n || b >= n || c >= n) continue;
        const glm::vec3& pa = mesh.vertices[a].pos;
        const glm::vec3& pb = mesh.vertices[b].pos;
        const glm::vec3& pc = mesh.vertices[c].pos;
        const glm::vec3 face = glm::cross(pb - pa, pc - pa);
        const glm::vec3 hinted = mesh.vertices[a].normal + mesh.vertices[b].normal +
                                 mesh.vertices[c].normal;
        orient += glm::dot(face, hinted);
    }
    const float sign = orient < 0.f ? -1.f : 1.f;

    // Pass 1: each cluster gets the area-weighted sum of its own faces.
    std::unordered_map<int64_t, glm::vec3> acc;
    acc.reserve(n);
    for (size_t i = 0; i + 2 < mesh.indices.size(); i += 3) {
        const uint32_t a = mesh.indices[i], b = mesh.indices[i + 1], c = mesh.indices[i + 2];
        if (a >= n || b >= n || c >= n) continue;
        const glm::vec3& pa = mesh.vertices[a].pos;
        const glm::vec3& pb = mesh.vertices[b].pos;
        const glm::vec3& pc = mesh.vertices[c].pos;
        // Unnormalised cross product: its magnitude is twice the triangle's area, so
        // summing these weights the average by area without a second division.
        const glm::vec3 face = glm::cross(pb - pa, pc - pa) * sign;
        for (uint32_t idx : {a, b, c}) acc[packOf(coordOf(mesh.vertices[idx].pos))] += face;
    }

    // Passes 2..N: a cluster's normal is blended with its 26 neighbours (the 3x3x3 shell
    // around its own cell, itself weighted twice). One pass would already average the
    // seams inside a patch; the extra passes are what make the result read as ONE broad
    // form instead of a mosaic of patches, which is the whole point of the technique — and
    // the reason the first version of this function (per-vertex clusters, no passes)
    // measured zero changed pixels on a real capture.
    constexpr int kClusterPasses = 3;
    std::unordered_map<int64_t, glm::vec3> cur = acc;
    for (int pass = 0; pass < kClusterPasses; ++pass) {
        std::unordered_map<int64_t, glm::vec3> next = cur;
        for (const auto& kv : cur) {
            if (glm::dot(kv.second, kv.second) < 1e-12f) continue;
            const glm::vec3 self = glm::normalize(kv.second);
            // Unpack the coordinate triple back out of the key.
            int64_t rest = kv.first;
            const int cz = (int)(rest % kSpan) - (int)kBias;
            rest /= kSpan;
            const int cy = (int)(rest % kSpan) - (int)kBias;
            rest /= kSpan;
            const int cx = (int)rest - (int)kBias;
            glm::vec3 sum = self;
            for (int dz = -1; dz <= 1; ++dz)
                for (int dy = -1; dy <= 1; ++dy)
                    for (int dx = -1; dx <= 1; ++dx) {
                        if (!dx && !dy && !dz) continue;
                        const auto it = cur.find(packOf(glm::ivec3(cx + dx, cy + dy, cz + dz)));
                        if (it == cur.end() || glm::dot(it->second, it->second) < 1e-12f) continue;
                        sum += glm::normalize(it->second);
                    }
            next[kv.first] = sum;
        }
        cur.swap(next);
    }

    size_t filled = 0;
    for (size_t i = 0; i < n; ++i) {
        const xm::Vertex& src = mesh.vertices[i];
        glm::vec4& dst = out[i].npr;
        const auto it = cur.find(packOf(coordOf(src.pos)));
        dst = glm::vec4(0.f);
        // No cluster (an isolated vertex) or a degenerate accumulation: leave the record
        // zero, which the shader reads as "no secondary normal".
        if (it == cur.end() || glm::dot(it->second, it->second) < 1e-12f) continue;
        const glm::vec3 cluster = glm::normalize(it->second);
        const glm::vec3 geo = glm::length(src.normal) > 1e-6f ? glm::normalize(src.normal)
                                                             : cluster;
        if (glm::dot(cluster, geo) <= 0.f) continue;   // would flip: keep the geometric one
        const glm::vec3 mixed = glm::normalize(glm::mix(geo, cluster, glm::clamp(smoothing, 0.f, 1.f)));
        // The mask (F): the shader adds (mask - 0.5) * BAND_BIAS to its band edges, so a
        // value ABOVE neutral pushes the surface towards LIGHT and one below pushes it
        // towards SHADOW. Up-facing geometry is what an anime read keeps lit, so that is
        // the direction the generated scalar goes: 1 up-facing, 0 down-facing. (The
        // obvious `-mixed.y * 0.5 + 0.5` is the exact opposite; the test caught it.)
        // `maskBias` 0 pins the mask at neutral, which is the arm the E experiment runs in:
        // the secondary normal is the experiment, the mask is a separate hypothesis and
        // must not ride along.
        //
        // The deviation is deliberately bounded well inside [0,1]: an earlier version
        // mapped the whole range and measured 0.001..0.999 on rena, which drives the
        // shader's band edges to the ends of the term and turns the mask into a hard
        // binary cut on every surface. A shadow mask is a bias on an edge, not a second
        // lighting model.
        const float up = (1.f + glm::clamp(mixed.y, -1.f, 1.f)) * 0.5f;
        const float mask = glm::clamp(0.5f + (up - 0.5f) * 0.5f * maskBias, 0.f, 1.f);
        dst = glm::vec4(mixed, mask);
        ++filled;
    }
    return filled;
}

}  // namespace render
