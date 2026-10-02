// physics/raycast.cpp — see raycast.h for the contract and why it is shaped this way.
//
// One intersection kernel (Möller–Trumbore) plus two loop flavors, mirroring the
// reference's two walkers (remake/src/physics/raycast.cpp:41-120): keep the smallest t,
// or stop at the first hit. The flavors share one templated loop so the triangle and
// traversal logic cannot drift between them, with the choice folded at compile time
// (no branch in the hot path).
#include "physics/raycast.h"

#include <limits>

namespace game::physics {
namespace {

// Möller–Trumbore, non-culling, dir not normalized: t stays the raw ray parameter,
// which is what the reference's `dist` is. A degenerate triangle is rejected by the
// determinant test, and every range check is a positive test so a NaN (0/0) fails it
// instead of slipping through both branches.
bool intersectTriangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2,
                       const glm::vec3& origin, const glm::vec3& dir, float maxDist,
                       float& tOut, float& uOut, float& vOut) {
    const glm::vec3 e1 = v1 - v0;
    const glm::vec3 e2 = v2 - v0;
    const glm::vec3 p  = glm::cross(dir, e2);
    const float     det = glm::dot(e1, p);
    if (!(det != 0.0f)) return false;                    // ray parallel to the plane
    const float     inv = 1.0f / det;
    const glm::vec3 tv  = origin - v0;
    const float     u   = glm::dot(tv, p) * inv;         // weight of v1
    if (!(u >= 0.0f && u <= 1.0f)) return false;
    const glm::vec3 q = glm::cross(tv, e1);
    const float     v = glm::dot(dir, q) * inv;          // weight of v2
    if (!(v >= 0.0f && u + v <= 1.0f)) return false;
    const float t = glm::dot(e2, q) * inv;
    if (!(t >= 0.0f)) return false;                      // behind the origin
    if (maxDist > 0.0f && !(t <= maxDist)) return false;  // cutoff is inclusive
    tOut = t;
    uOut = u;
    vOut = v;
    return true;
}

// Shared triangle loop. Closest == true keeps the smallest t (first triangle wins a
// tie, like the reference's `dist < s.dist`); Closest == false returns at the first
// passing triangle and leaves `best` untouched.
template <bool Closest>
bool castTriangles(const TriangleMeshView& mesh, const glm::vec3& origin, const glm::vec3& dir,
                   float maxDist, RaycastStats* stats, RayHit& best) {
    if (!mesh.vertices || !mesh.indices) return false;
    const size_t vertexCount = mesh.vertexCount;
    const size_t triCount    = mesh.indexCount / 3;
    for (size_t i = 0; i < triCount; ++i) {
        if (stats) ++stats->trianglesTested;
        const uint32_t i0 = mesh.indices[3 * i + 0];
        const uint32_t i1 = mesh.indices[3 * i + 1];
        const uint32_t i2 = mesh.indices[3 * i + 2];
        // Bounds-checked so a malformed file cannot read out of range; the loader
        // already guarantees this for shipped assets.
        if (i0 >= vertexCount || i1 >= vertexCount || i2 >= vertexCount) continue;

        float t = 0.f, u = 0.f, v = 0.f;
        if (!intersectTriangle(mesh.vertices[i0].pos, mesh.vertices[i1].pos,
                               mesh.vertices[i2].pos, origin, dir, maxDist, t, u, v)) {
            continue;
        }
        if constexpr (!Closest) return true;
        if (best.hit && !(t < best.dist)) continue;
        best.hit       = true;
        best.faceIndex = static_cast<uint32_t>(i);
        best.u         = u;
        best.v         = v;
        best.dist      = t;
        best.point     = origin + dir * t;
    }
    return best.hit;
}

// Shared model walk over a prebuilt traversal order.
template <bool Closest>
bool castModel(const xm::Model& model, const ModelIndex& index, const glm::vec3& origin,
               const glm::vec3& dir, float maxDist, RaycastStats* stats, RayHit& best) {
    float bestT = std::numeric_limits<float>::infinity();
    for (const int32_t mi : index.meshOrder) {
        const xm::Mesh& m = model.meshes[static_cast<size_t>(mi)];
        if (m.indices.size() < 3 || m.vertices.empty()) continue;
        if (stats) ++stats->meshesVisited;

        if constexpr (Closest) {
            const RayHit h = raycastTriangles(meshView(m), origin, dir, maxDist, stats);
            if (!h.hit || !(h.dist < bestT)) continue;
            best    = h;
            best.mesh = mi;
            bestT   = h.dist;
        } else {
            if (!raycastTrianglesAny(meshView(m), origin, dir, maxDist, stats)) continue;
            best.hit  = true;
            best.mesh = mi;
            return true;
        }
    }
    return best.hit;
}

}  // namespace

RayHit raycastTriangles(const TriangleMeshView& mesh, const glm::vec3& origin,
                        const glm::vec3& dir, float maxDist, RaycastStats* stats) {
    RayHit best;
    castTriangles<true>(mesh, origin, dir, maxDist, stats, best);
    return best;
}

bool raycastTrianglesAny(const TriangleMeshView& mesh, const glm::vec3& origin,
                         const glm::vec3& dir, float maxDist, RaycastStats* stats) {
    RayHit unused;
    return castTriangles<false>(mesh, origin, dir, maxDist, stats, unused);
}

ModelIndex buildModelIndex(const xm::Model& model) {
    ModelIndex   index;
    const size_t meshCount  = model.meshes.size();
    const size_t frameCount = model.frames.size();

    for (size_t i = 0; i < meshCount; ++i) {
        if (model.meshes[i].frame < 0) index.meshOrder.push_back(static_cast<int32_t>(i));
    }

    // Roots pushed in reverse so the first root is popped first; children likewise, so
    // the walk is depth-first with siblings in index order.
    std::vector<bool>    frameSeen(frameCount, false);
    std::vector<int32_t> stack;
    for (size_t f = frameCount; f-- > 0;) {
        if (model.frames[f].parent < 0) stack.push_back(static_cast<int32_t>(f));
    }
    while (!stack.empty()) {
        const int32_t f = stack.back();
        stack.pop_back();
        if (frameSeen[static_cast<size_t>(f)]) continue;
        frameSeen[static_cast<size_t>(f)] = true;

        for (size_t i = 0; i < meshCount; ++i) {
            if (model.meshes[i].frame == f) index.meshOrder.push_back(static_cast<int32_t>(i));
        }
        for (size_t c = frameCount; c-- > 0;) {
            if (model.frames[c].parent == f) stack.push_back(static_cast<int32_t>(c));
        }
    }

    for (size_t i = 0; i < meshCount; ++i) {
        const int32_t f = model.meshes[i].frame;
        if (f < 0) continue;
        if (static_cast<size_t>(f) >= frameCount || !frameSeen[static_cast<size_t>(f)]) {
            index.meshOrder.push_back(static_cast<int32_t>(i));
        }
    }
    return index;
}

RayHit raycastModel(const xm::Model& model, const ModelIndex& index, const glm::vec3& origin,
                    const glm::vec3& dir, float maxDist, RaycastStats* stats) {
    RayHit best;
    castModel<true>(model, index, origin, dir, maxDist, stats, best);
    return best;
}

bool raycastModelAny(const xm::Model& model, const ModelIndex& index, const glm::vec3& origin,
                     const glm::vec3& dir, float maxDist, RaycastStats* stats) {
    RayHit unused;
    return castModel<false>(model, index, origin, dir, maxDist, stats, unused);
}

RayHit raycastModel(const xm::Model& model, const glm::vec3& origin, const glm::vec3& dir,
                    float maxDist, RaycastStats* stats) {
    const ModelIndex index = buildModelIndex(model);
    return raycastModel(model, index, origin, dir, maxDist, stats);
}

void CameraCollision::setMesh(const xm::Model* cameraMesh) {
    mesh_      = cameraMesh;
    index_     = ModelIndex{};
    triangles_ = 0;
    if (!cameraMesh) return;
    index_ = buildModelIndex(*cameraMesh);
    for (const int32_t mi : index_.meshOrder) {
        triangles_ += cameraMesh->meshes[static_cast<size_t>(mi)].indices.size() / 3;
    }
}

CameraClampResult CameraCollision::queryClamp(const CameraClampQuery& q) const {
    CameraClampResult r;
    if (triangles_ == 0 || !mesh_) return r;   // no camera geometry: the contract's "no hit"
    const glm::vec3 leg = q.desiredEye - q.aim;
    const float     len = glm::length(leg);
    if (!(len > 0.0f)) return r;               // degenerate segment (also NaN)
    const glm::vec3 dir = leg / len;
    const RayHit    hit = raycastModel(*mesh_, index_, q.aim, dir, len);
    // A blocker exactly at the desired eye leaves the eye unclamped: the reference
    // requires dist < desiredDist (remake/src/render/arena_camera.cpp:111-113).
    if (!hit.hit || !(hit.dist < len)) return r;
    r.hit     = true;
    r.hitDist = hit.dist;
    return r;
}

}  // namespace game::physics
