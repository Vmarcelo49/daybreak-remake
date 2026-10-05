// physics/raycast.cpp — see raycast.h for the contract and why it is shaped this way.
//
// One intersection kernel (Möller–Trumbore) plus two loop flavors, mirroring the
// reference's two walkers (remake/src/physics/raycast.cpp:41-120): keep the smallest t,
// or stop at the first hit. The flavors share one templated loop so the triangle and
// traversal logic cannot drift between them, with the choice folded at compile time
// (no branch in the hot path).
#include "physics/raycast.h"

#include <algorithm>
#include <cmath>
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

namespace {

bool triangleVertices(const xm::Model& model, int32_t meshIndex, uint32_t faceIndex,
                      const xm::Vertex*& a, const xm::Vertex*& b, const xm::Vertex*& c) {
    if (meshIndex < 0 || static_cast<size_t>(meshIndex) >= model.meshes.size()) return false;
    const xm::Mesh& mesh = model.meshes[static_cast<size_t>(meshIndex)];
    const size_t first = static_cast<size_t>(faceIndex) * 3;
    if (first + 2 >= mesh.indices.size()) return false;
    const uint32_t ia = mesh.indices[first], ib = mesh.indices[first + 1], ic = mesh.indices[first + 2];
    if (ia >= mesh.vertices.size() || ib >= mesh.vertices.size() || ic >= mesh.vertices.size()) return false;
    a = &mesh.vertices[ia];
    b = &mesh.vertices[ib];
    c = &mesh.vertices[ic];
    return true;
}

glm::vec3 surfaceNormal(const xm::Vertex& a, const xm::Vertex& b, const xm::Vertex& c) {
    const glm::vec3 cross = glm::cross(b.pos - a.pos, c.pos - a.pos);
    const float length = glm::length(cross);
    return length > 1e-6f ? cross / length : glm::vec3(0.f);
}

bool finite(const glm::vec3& p) {
    return std::isfinite(p.x) && std::isfinite(p.y) && std::isfinite(p.z);
}

}  // namespace

void MovementCollision::setMeshes(const xm::Model* movementMesh,
                                  const xm::Model* groundMesh) {
    movementMesh_ = movementMesh;
    groundMesh_ = groundMesh;
    movementIndex_ = movementMesh ? buildModelIndex(*movementMesh) : ModelIndex{};
    groundIndex_ = !groundMesh ? ModelIndex{}
                  : groundMesh == movementMesh ? movementIndex_
                  : buildModelIndex(*groundMesh);
    movementTriangles_ = 0;
    groundTriangles_ = 0;
    for (const int32_t mi : movementIndex_.meshOrder)
        movementTriangles_ += movementMesh_->meshes[static_cast<size_t>(mi)].indices.size() / 3;
    for (const int32_t mi : groundIndex_.meshOrder)
        groundTriangles_ += groundMesh_->meshes[static_cast<size_t>(mi)].indices.size() / 3;

    haveBounds_ = false;
    boundsMin_ = glm::vec3(std::numeric_limits<float>::max());
    boundsMax_ = glm::vec3(std::numeric_limits<float>::lowest());
    auto includeBounds = [&](const xm::Model* model, const ModelIndex& index) {
        if (!model) return;
        for (const int32_t mi : index.meshOrder) {
            for (const xm::Vertex& vertex : model->meshes[static_cast<size_t>(mi)].vertices) {
                if (!finite(vertex.pos)) continue;
                boundsMin_ = glm::min(boundsMin_, vertex.pos);
                boundsMax_ = glm::max(boundsMax_, vertex.pos);
                haveBounds_ = true;
            }
        }
    };
    includeBounds(movementMesh_, movementIndex_);
    if (groundMesh_ != movementMesh_) includeBounds(groundMesh_, groundIndex_);
}

GroundHit MovementCollision::groundAt(float x, float z, float referenceY,
                                      float maxRise, float maxDrop) const {
    GroundHit best;
    if (!groundMesh_ || groundTriangles_ == 0 || !std::isfinite(x) || !std::isfinite(z) ||
        !std::isfinite(referenceY)) return best;
    const float upper = referenceY + std::max(0.f, maxRise) + 1e-3f;
    const float lower = referenceY - std::max(0.f, maxDrop) - 1e-3f;
    constexpr float kMinGroundNormalY = 0.45f;  // provisional 63-degree walkable-slope limit

    for (const int32_t mi : groundIndex_.meshOrder) {
        const xm::Mesh& mesh = groundMesh_->meshes[static_cast<size_t>(mi)];
        for (size_t face = 0; face + 2 < mesh.indices.size(); face += 3) {
            const uint32_t ia = mesh.indices[face], ib = mesh.indices[face + 1], ic = mesh.indices[face + 2];
            if (ia >= mesh.vertices.size() || ib >= mesh.vertices.size() || ic >= mesh.vertices.size()) continue;
            const xm::Vertex& a = mesh.vertices[ia];
            const xm::Vertex& b = mesh.vertices[ib];
            const xm::Vertex& c = mesh.vertices[ic];
            const glm::vec3 normal = surfaceNormal(a, b, c);
            if (normal.y < kMinGroundNormalY) continue;  // collision.x ground faces are upward wound

            const float denominator = (b.pos.z - c.pos.z) * (a.pos.x - c.pos.x) +
                                      (c.pos.x - b.pos.x) * (a.pos.z - c.pos.z);
            if (std::abs(denominator) < 1e-6f) continue;
            const float wa = ((b.pos.z - c.pos.z) * (x - c.pos.x) +
                              (c.pos.x - b.pos.x) * (z - c.pos.z)) / denominator;
            const float wb = ((c.pos.z - a.pos.z) * (x - c.pos.x) +
                              (a.pos.x - c.pos.x) * (z - c.pos.z)) / denominator;
            const float wc = 1.f - wa - wb;
            if (wa < -1e-4f || wb < -1e-4f || wc < -1e-4f) continue;
            const float height = wa * a.pos.y + wb * b.pos.y + wc * c.pos.y;
            if (!(height >= lower && height <= upper) || (best.hit && height <= best.height)) continue;
            best.hit = true;
            best.height = height;
            best.point = glm::vec3(x, height, z);
            best.normal = normal;
            best.mesh = mi;
            best.faceIndex = static_cast<uint32_t>(face / 3);
        }
    }
    return best;
}

RayHit MovementCollision::firstWallHit(const glm::vec3& start,
                                       const glm::vec3& delta) const {
    RayHit best;
    if (!movementMesh_ || movementTriangles_ == 0) return best;
    const glm::vec2 horizontal(delta.x, delta.z);
    const float distance = glm::length(horizontal);
    if (!(distance > 1e-5f)) return best;
    const glm::vec3 direction(horizontal.x / distance, 0.f, horizontal.y / distance);
    constexpr float kWallNormalY = 0.70f;
    constexpr float kBodyHeights[] = {10.f, kFighterHeight * 0.5f,
                                      kFighterHeight - 10.f};
    constexpr int kRingSamples = 12;
    for (int sample = -1; sample < kRingSamples; ++sample) {
        glm::vec2 offset(0.f);
        if (sample >= 0) {
            const float angle = 6.28318530718f * static_cast<float>(sample) /
                                static_cast<float>(kRingSamples);
            offset = glm::vec2(std::cos(angle), std::sin(angle)) * kFighterRadius;
        }
        for (const float height : kBodyHeights) {
            const glm::vec3 origin(start.x + offset.x, start.y + height,
                                   start.z + offset.y);
            RayHit wallHit;
            float closest = distance;
            for (const int32_t mi : movementIndex_.meshOrder) {
                const xm::Mesh& mesh = movementMesh_->meshes[static_cast<size_t>(mi)];
                for (size_t face = 0; face + 2 < mesh.indices.size(); face += 3) {
                    const uint32_t ia = mesh.indices[face], ib = mesh.indices[face + 1],
                                   ic = mesh.indices[face + 2];
                    if (ia >= mesh.vertices.size() || ib >= mesh.vertices.size() ||
                        ic >= mesh.vertices.size()) continue;
                    const xm::Vertex& a = mesh.vertices[ia];
                    const xm::Vertex& b = mesh.vertices[ib];
                    const xm::Vertex& c = mesh.vertices[ic];
                    glm::vec3 normal = surfaceNormal(a, b, c);
                    if (std::abs(normal.y) >= kWallNormalY) continue; // floors and ramps use groundAt
                    normal.y = 0.f;
                    const float normalLength = glm::length(normal);
                    if (!(normalLength > 1e-5f)) continue;
                    normal /= normalLength;
                    if (glm::dot(normal, direction) > 0.f) normal = -normal;
                    if (glm::dot(normal, direction) >= -1e-4f) continue;
                    float t = 0.f, u = 0.f, v = 0.f;
                    if (!intersectTriangle(a.pos, b.pos, c.pos, origin, direction,
                                           closest, t, u, v)) continue;
                    closest = t;
                    wallHit.hit = true;
                    wallHit.faceIndex = static_cast<uint32_t>(face / 3);
                    wallHit.u = u;
                    wallHit.v = v;
                    wallHit.dist = t;
                    wallHit.point = origin + direction * t;
                    wallHit.mesh = mi;
                }
            }
            if (!wallHit.hit || (best.hit && wallHit.dist >= best.dist)) continue;
            best = wallHit;
        }
    }
    return best;
}

glm::vec3 MovementCollision::slideSegment(const glm::vec3& start,
                                         const glm::vec3& delta,
                                         bool& hitWall) const {
    glm::vec3 position = start;
    glm::vec3 remaining(delta.x, 0.f, delta.z);
    constexpr float kWallSkin = 2.f;
    for (int contact = 0; contact < 4; ++contact) {
        const float distance = glm::length(glm::vec2(remaining.x, remaining.z));
        if (!(distance > 1e-4f)) break;
        const RayHit hit = firstWallHit(position, remaining);
        if (!hit.hit) {
            position += remaining;
            break;
        }
        hitWall = true;
        const xm::Vertex *a = nullptr, *b = nullptr, *c = nullptr;
        if (!triangleVertices(*movementMesh_, hit.mesh, hit.faceIndex, a, b, c)) break;
        glm::vec3 normal = surfaceNormal(*a, *b, *c);
        normal.y = 0.f;
        normal = glm::normalize(normal);
        const glm::vec2 horizontalDirection(remaining.x, remaining.z);
        if (normal.x * horizontalDirection.x + normal.z * horizontalDirection.y > 0.f)
            normal = -normal;
        const float safeDistance = std::max(0.f, hit.dist - kWallSkin);
        const glm::vec3 direction = remaining / distance;
        position += direction * safeDistance;
        remaining -= direction * safeDistance;
        const float intoWall = glm::dot(remaining, normal);
        if (intoWall < 0.f) remaining -= normal * intoWall;
    }
    return position;
}

MovementResult MovementCollision::move(const glm::vec3& start,
                                       const glm::vec3& desired,
                                       bool grounded) const {
    MovementResult result{desired, grounded, false};
    if (!finite(start) || !finite(desired)) {
        result.position = finite(start) ? start : glm::vec3(0.f);
        result.grounded = false;
        result.hitWall = true;
        return result;
    }
    if (movementTriangles_ == 0) {
        if (grounded && groundTriangles_ != 0) {
            const GroundHit support = groundAt(desired.x, desired.z, start.y,
                                               kMaxStepUp, kMaxStepDown);
            if (support.hit) result.position.y = support.height;
            else result.grounded = false;
        }
        return result;
    }

    const glm::vec2 total(desired.x - start.x, desired.z - start.z);
    const float length = glm::length(total);
    if (length > 15000.f) {
        result.position = start;
        result.grounded = grounded;
        result.hitWall = true;
        return result;
    }
    const int steps = std::max(1, std::min(512, static_cast<int>(std::ceil(length / 30.f))));
    const glm::vec2 stride = total / static_cast<float>(steps);
    glm::vec3 position = start;
    bool onGround = grounded;
    for (int i = 0; i < steps; ++i) {
        const glm::vec3 before = position;
        const glm::vec3 segment(stride.x, 0.f, stride.y);
        GroundHit predictedSupport;
        if (onGround && groundTriangles_ != 0) {
            const float strideLength = glm::length(glm::vec2(segment.x, segment.z));
            const glm::vec2 lead = strideLength > 1e-5f
                ? glm::vec2(segment.x, segment.z) * (kFighterRadius / strideLength)
                : glm::vec2(0.f);
            const float probeX = before.x + segment.x;
            const float probeZ = before.z + segment.z;
            predictedSupport = groundAt(probeX, probeZ, before.y,
                                        kMaxStepUp, kMaxStepDown);
            const GroundHit leadingSupport = groundAt(probeX + lead.x, probeZ + lead.y,
                                                       before.y, kMaxStepUp, kMaxStepDown);
            if (leadingSupport.hit) {
                bool isStepAhead = !predictedSupport.hit;
                if (predictedSupport.hit && leadingSupport.normal.y > 1e-4f) {
                    const float slopeRise = -(leadingSupport.normal.x * lead.x +
                                              leadingSupport.normal.z * lead.y) /
                                            leadingSupport.normal.y;
                    isStepAhead = leadingSupport.height > predictedSupport.height +
                                  slopeRise + 2.f;
                }
                if (isStepAhead) predictedSupport = leadingSupport;
            }
            const GroundHit highStep = groundAt(probeX + lead.x, probeZ + lead.y,
                                                before.y, 500.f, 0.f);
            if (highStep.hit && highStep.height > before.y + kMaxStepUp) {
                result.hitWall = true;
                break;
            }
        }

        // Lift the sweep to a reachable step's top. This lets the fighter walk up a
        // low riser while still checking the raised body against ceilings and walls.
        glm::vec3 sweepStart = before;
        if (predictedSupport.hit && predictedSupport.height > before.y)
            sweepStart.y = predictedSupport.height;
        position = slideSegment(sweepStart, segment, result.hitWall);
        if (predictedSupport.hit) {
            const GroundHit support = groundAt(position.x, position.z, before.y,
                                               kMaxStepUp, kMaxStepDown);
            if (support.hit) {
                position.y = support.height;
                const float leadDistance = glm::length(glm::vec2(position.x - before.x,
                                                                  position.z - before.z));
                if (predictedSupport.height > support.height + 1.f &&
                    predictedSupport.height <= before.y + kMaxStepUp &&
                    leadDistance <= kFighterRadius + 1e-3f)
                    position.y = predictedSupport.height;
                continue;
            }
            const float leadDistance = glm::length(glm::vec2(position.x - before.x,
                                                              position.z - before.z));
            if (leadDistance <= kFighterRadius + 1e-3f &&
                predictedSupport.height <= before.y + kMaxStepUp) {
                position.y = predictedSupport.height;
                continue;
            }
        }
        position.y = before.y;
        if (onGround && groundTriangles_ != 0)
            onGround = false;  // a ledge or a drop beyond the step allowance starts a fall
    }
    result.position = position;
    result.grounded = onGround;
    return result;
}

bool MovementCollision::insideHorizontalBounds(float x, float z) const {
    if (!haveBounds_) return true;
    constexpr float kBoundaryPadding = 500.f;
    return x >= boundsMin_.x - kBoundaryPadding && x <= boundsMax_.x + kBoundaryPadding &&
           z >= boundsMin_.z - kBoundaryPadding && z <= boundsMax_.z + kBoundaryPadding;
}

bool MovementCollision::validPosition(const glm::vec3& position) const {
    if (!finite(position)) return false;
    if (!haveBounds_) return true;
    constexpr float kVerticalPadding = 1000.f;
    return insideHorizontalBounds(position.x, position.z) &&
           position.y >= boundsMin_.y - kVerticalPadding &&
           position.y <= boundsMax_.y + kVerticalPadding;
}

GroundHit MovementCollision::nearestGround(float x, float z) const {
    GroundHit best;
    if (!groundMesh_ || groundTriangles_ == 0) return best;
    constexpr float kMinGroundNormalY = 0.45f;
    float bestDistance = std::numeric_limits<float>::infinity();
    for (const int32_t mi : groundIndex_.meshOrder) {
        const xm::Mesh& mesh = groundMesh_->meshes[static_cast<size_t>(mi)];
        for (size_t face = 0; face + 2 < mesh.indices.size(); face += 3) {
            const uint32_t ia = mesh.indices[face], ib = mesh.indices[face + 1], ic = mesh.indices[face + 2];
            if (ia >= mesh.vertices.size() || ib >= mesh.vertices.size() || ic >= mesh.vertices.size()) continue;
            const xm::Vertex& a = mesh.vertices[ia];
            const xm::Vertex& b = mesh.vertices[ib];
            const xm::Vertex& c = mesh.vertices[ic];
            const glm::vec3 normal = surfaceNormal(a, b, c);
            if (normal.y < kMinGroundNormalY) continue;
            const glm::vec3 center = (a.pos + b.pos + c.pos) / 3.f;
            const float dx = center.x - x, dz = center.z - z;
            const float distance = dx * dx + dz * dz;
            if (!(distance < bestDistance)) continue;
            bestDistance = distance;
            best.hit = true;
            best.height = center.y;
            best.point = center;
            best.normal = normal;
            best.mesh = mi;
            best.faceIndex = static_cast<uint32_t>(face / 3);
        }
    }
    return best;
}

glm::vec3 MovementCollision::resolveSpawn(const glm::vec3& preferred,
                                         const glm::vec3* candidates,
                                         size_t candidateCount) const {
    auto project = [&](const glm::vec3& candidate, glm::vec3& resolved) {
        if (!finite(candidate) || !insideHorizontalBounds(candidate.x, candidate.z)) return false;
        GroundHit support = groundAt(candidate.x, candidate.z, candidate.y, 50.f, 10000.f);
        if (!support.hit) support = groundAt(candidate.x, candidate.z, candidate.y, 500.f, 10000.f);
        if (!support.hit) return false;
        resolved = glm::vec3(candidate.x, support.height, candidate.z);
        return validPosition(resolved);
    };

    glm::vec3 resolved;
    if (project(preferred, resolved)) return resolved;

    size_t bestIndex = candidateCount;
    float bestDistance = std::numeric_limits<float>::infinity();
    if (finite(preferred)) {
        for (size_t i = 0; candidates && i < candidateCount; ++i) {
            if (!finite(candidates[i])) continue;
            const glm::vec2 delta(candidates[i].x - preferred.x, candidates[i].z - preferred.z);
            const float distance = glm::dot(delta, delta);
            if (distance < bestDistance) { bestDistance = distance; bestIndex = i; }
        }
    }
    if (bestIndex < candidateCount && project(candidates[bestIndex], resolved)) return resolved;
    // Other supplied env slots are still safer than an invalid override.
    for (size_t i = 0; candidates && i < candidateCount; ++i)
        if (i != bestIndex && project(candidates[i], resolved)) return resolved;

    if (finite(preferred)) {
        const GroundHit nearest = nearestGround(preferred.x, preferred.z);
        if (nearest.hit) return nearest.point;
    }
    if (haveBounds_) {
        const float x = (boundsMin_.x + boundsMax_.x) * 0.5f;
        const float z = (boundsMin_.z + boundsMax_.z) * 0.5f;
        const GroundHit nearest = nearestGround(x, z);
        if (nearest.hit) return nearest.point;
    }
    if (finite(preferred)) return preferred;
    for (size_t i = 0; candidates && i < candidateCount; ++i)
        if (finite(candidates[i])) return candidates[i];
    return glm::vec3(0.f);
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

bool segmentBlocked(const glm::vec3& from, const glm::vec3& to, const xm::Model* model,
                    const ModelIndex* index) {
    if (model == nullptr) return false;
    const glm::vec3 leg = to - from;
    const float     len = glm::length(leg);
    if (!(len > 0.0f)) return false;              // degenerate (and NaN) is not a blocker
    const glm::vec3 dir = leg / len;

    if (index != nullptr) {
        // One early-out ray is enough for a thin wall, but a stepper keeps a fast swing
        // from tunnelling past a single-triangle barrier: the camera clamp solves the
        // same problem by taking the closest hit over the whole segment, and this takes
        // the same raycast, only stopping at the first blocker.
        constexpr float kStep = 40.0f;
        for (float travelled = 0.0f; travelled < len; travelled += kStep) {
            const float reach = std::min(kStep, len - travelled);
            if (raycastModelAny(*model, *index, from + dir * travelled, dir, reach))
                return true;
        }
        return false;
    }
    // No cached traversal order: build one for this call (the header notes that
    // variant allocates per call, which is fine for a one-off query).
    return raycastModel(*model, from, dir, len).hit;
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
