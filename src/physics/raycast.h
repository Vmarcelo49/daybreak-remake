#pragma once
// physics/raycast.h — CPU triangle-mesh raycast: the D3DXIntersect replacement for
// the SDL3 + WebGPU foundation (docs/FULL-REPLACEMENT-PLAN.md §4, "CPU raycast").
//
// Contract, ported from the DX9 reference (remake/src/physics/raycast.{h,cpp},
// read-only) so call sites move over unchanged:
//
//   * It is a mesh-vs-ray query, not a physics engine. The original answers every
//     "did this hit?" question with D3DXIntersect against triangle meshes — no
//     sphere/AABB/OBB code exists (remake/src/physics/raycast.h:7-9). This module
//     reproduces that query surface: closest hit (raycast_model, raycast.h:64) and
//     the early-out yes/no variant (raycast_model_any, raycast.h:73).
//   * FUN_004011f0 loads three collision files per stage. collision.x supplies separate
//     movement and ground query purposes; collision_camera.x is camera-only, and
//     collision_tama.x is projectile-only (remake/src/maps/stage.h:11-14).
//     The camera clamp consumes its mesh through game::ICameraCollision below.
//   * Hits are reported as face index + barycentric u,v + distance along the ray
//     (raycast.h:21-25), and `maxDist <= 0` means "no cutoff" (raycast.cpp:66).
//   * NO frame transform. The reference walks D3DXFRAME but never multiplies by a
//     frame world matrix, because D3DXIntersect is defined in the mesh's own vertex
//     space and the caller's ray is already in that space (raycast.h:60-63).
//     Measured on the shipped assets, that omission is a no-op: every collision*.x
//     frame carries an identity FrameTransformMatrix, the camera meshes have no
//     frames at all, and all collision meshes are unskinned. So this code intersects
//     raw mesh vertices; a skinned mesh would be intersected in bind pose, which is
//     what D3DXIntersect does too (it has no skinning step).
//   * Traversal order is the reference's walk — a frame's mesh containers, then its
//     children, then its siblings (raycast.cpp:41-83). Closest hit is order
//     independent, but ties and the early-out query are not, so the order is kept.
//
// Brute force over every triangle: no BVH. The plan allows one "if profiles demand
// it"; measured with tests/raycast_analytic.cpp on the largest shipped camera mesh
// (stage06/stage16 collision_camera.X: 29 meshes, 628 triangles, 990 vertices), the
// closest-hit walk costs 5.67 us/ray at -O2 (~9.0 ns per triangle, including the
// 29-container walk), i.e. 0.34 ms per second at one camera ray per 60 Hz frame, where
// a BVH would cost more to build per stage than it saves per query. The same test
// measures 200.8 us/ray at 32768 triangles, which is where a BVH would start to pay.
// This file is the reference implementation to diff a BVH against if one is ever added.
//
// glm + the asset layer's mesh types only: no WebGPU, no window, host-testable.

#include <cstddef>
#include <cstdint>
#include <vector>

#include <glm/glm.hpp>

#include "assets/xmodel.h"        // xm::Vertex / xm::Mesh / xm::Model (read-only use)
#include "camera/camera_collision.h"

namespace game::physics {

// One ray hit against one triangle of one mesh. Mirrors physics::RaycastHit
// (remake/src/physics/raycast.h:43-51) with the DX9 types replaced:
//   dist  — the reference's `dist`: the parameter t of point = origin + t*dir. It is
//           the metric distance only when dir is unit length, which is how every
//           reference call site passes it (e.g. remake/src/render/arena_camera.cpp:110).
//   u, v  — the reference's barycentric pair; w = 1-u-v weights the first vertex, so
//           point = (1-u-v)*v0 + u*v1 + v*v2 for the triangle's vertex order.
//   mesh  — index into xm::Model::meshes (the reference's ID3DXMesh*); faceIndex is
//           relative to that mesh, exactly as D3DXIntersect reports it.
// On a miss every field keeps its default (hit=false, faceIndex=0, u=v=dist=0,
// point=(0,0,0), mesh=-1); the reference leaves its outputs untouched on a miss.
struct RayHit {
    bool      hit       = false;
    uint32_t  faceIndex = 0;
    float     u         = 0.f;
    float     v         = 0.f;
    float     dist      = 0.f;
    glm::vec3 point{0.f};
    int32_t   mesh = -1;
};

// Optional counter hook. Costs one increment per tested triangle when non-null and
// nothing when null. Exists so tests can prove the early-out actually stops, and so a
// profile can report triangles-tested per ray instead of guessing.
struct RaycastStats {
    size_t trianglesTested = 0;
    size_t meshesVisited   = 0;   // meshes with at least one triangle that were tested
};

// One mesh container's geometry, zero-copy over xm::Mesh (xm::Vertex is interleaved,
// so the view cannot be a bare glm::vec3*).
struct TriangleMeshView {
    const xm::Vertex* vertices    = nullptr;
    size_t            vertexCount = 0;
    const uint32_t*   indices     = nullptr;
    size_t            indexCount  = 0;   // multiples of 3 beyond the last full triangle are ignored
};

inline TriangleMeshView meshView(const xm::Mesh& m) {
    return {m.vertices.data(), m.vertices.size(), m.indices.data(), m.indices.size()};
}

// Closest hit over one mesh container (the reference's per-container D3DXIntersect,
// raycast.cpp:60-63). `dir` need not be unit length; `maxDist <= 0` disables the
// cutoff and the cutoff is inclusive, both matching the reference's
// `maxDist <= 0 || dist <= maxDist` (raycast.cpp:66). Hits at t == 0 (origin on the
// triangle) count; hits behind the origin (t < 0) do not. Winding is ignored: like
// D3DXIntersect this is not a backface-culling query, and the original relies on
// hitting both sides of a wall.
RayHit raycastTriangles(const TriangleMeshView& mesh, const glm::vec3& origin,
                        const glm::vec3& dir, float maxDist = 0.f,
                        RaycastStats* stats = nullptr);

// Same tests, but returns at the first triangle that passes — the reference's
// raycast_model_any early-out (raycast.cpp:94-120). Which triangle that is depends on
// traversal order; the closest hit is deliberately not computed.
bool raycastTrianglesAny(const TriangleMeshView& mesh, const glm::vec3& origin,
                         const glm::vec3& dir, float maxDist = 0.f,
                         RaycastStats* stats = nullptr);

// Traversal order for one model, resolved once. The reference walks a live D3DXFRAME
// tree on every call; xm::Model is flat frame/mesh arrays, so the same order is
// flattened here. Build this at load time next to the model: the per-ray paths never
// allocate.
struct ModelIndex {
    // xm::Model::meshes indices in visit order.
    //
    // Frame-less meshes come first, in mesh order: the reference has no such case (a
    // D3DXMESHCONTAINER always hangs off a D3DXFRAME), but xm::Mesh::frame == -1 means
    // "no frame" and every shipped collision_camera.X is built that way, so mesh order
    // is what reproduces the reference's container-chain order for real stages.
    //
    // Then each root frame in index order, depth-first: a frame's containers, then its
    // first child's whole subtree, then the next sibling. Meshes whose frame cannot be
    // reached from a root (out-of-range index, parent cycle) are appended in mesh order
    // so the index stays total.
    std::vector<int32_t> meshOrder;
};

ModelIndex buildModelIndex(const xm::Model& model);

// Closest hit over every mesh reachable through `index` (the recursive walk of
// raycast.cpp:41-83, flattened). Skinned meshes are intersected in bind pose.
RayHit raycastModel(const xm::Model& model, const ModelIndex& index, const glm::vec3& origin,
                    const glm::vec3& dir, float maxDist = 0.f, RaycastStats* stats = nullptr);

// Early-out variant over the same walk (raycast.cpp:94-120): true as soon as any
// triangle passes. This is the reference's line-of-sight/occlusion shape.
bool raycastModelAny(const xm::Model& model, const ModelIndex& index, const glm::vec3& origin,
                     const glm::vec3& dir, float maxDist = 0.f, RaycastStats* stats = nullptr);

// Convenience for one-off queries: builds the traversal order per call (one small
// allocation). Per-frame paths hold a ModelIndex; CameraCollision below does.
RayHit raycastModel(const xm::Model& model, const glm::vec3& origin, const glm::vec3& dir,
                    float maxDist = 0.f, RaycastStats* stats = nullptr);

// True when anything SOLID lies between `from` and `to`. Built on raycastModelAny's
// early-out walk (raycast.cpp:94-120), which is the reference's own occlusion shape,
// driven along the segment in the same short steps the camera clamp uses so a fast
// swing cannot step past a thin wall. A null mesh or an empty index reports "not
// blocked", which is what the reference does when collision.x is absent — melee then
// passes, rather than every attack silently failing on a stage without collision.
bool segmentBlocked(const glm::vec3& from, const glm::vec3& to, const xm::Model* model,
                    const ModelIndex* index = nullptr);

// A walkable surface found in the stage's ground channel. The normal is kept so
// callers and tests can distinguish a valid support plane from a vertical wall.
struct GroundHit {
    bool      hit = false;
    float     height = 0.f;
    glm::vec3 point{0.f};
    glm::vec3 normal{0.f, 1.f, 0.f};
    int32_t   mesh = -1;
    uint32_t  faceIndex = 0;
};

struct MovementResult {
    glm::vec3 position{0.f};
    bool      grounded = false;
    bool      hitWall = false;
};

// FUN_004011f0 establishes collision.x as the general fighter channel, and the existing
// D3DXIntersect replacement preserves its triangle queries. Movement and ground support
// use distinct queries over that same model. The 20-unit radius follows the movement
// measurements in FighterConstants (fighter.h, RE section 14.7); body height, step-up
// and step-down remain provisional port rules. Sweeps cover the full requested segment,
// independent of dash speed, and slide the remaining displacement along wall normals.
class MovementCollision {
public:
    // Both arguments are borrowed from the fully assembled scene. They are often the
    // same collision.x model, but separate bindings keep each purpose explicit.
    void setMeshes(const xm::Model* movementMesh, const xm::Model* groundMesh);

    const xm::Model* movementMesh() const { return movementMesh_; }
    const xm::Model* groundMesh() const { return groundMesh_; }
    bool empty() const { return movementTriangles_ == 0 && groundTriangles_ == 0; }
    bool hasGround() const { return groundTriangles_ != 0; }

    // Searches [referenceY - maxDrop, referenceY + maxRise], choosing the highest
    // upward-facing ground triangle under (x,z). maxRise/maxDrop are provisional port
    // rules; the original collision mesh supplies the geometry, not these tolerances.
    GroundHit groundAt(float x, float z, float referenceY,
                       float maxRise, float maxDrop) const;

    // Sweeps from `start` to `desired` in XZ, following reachable ground when
    // grounded. Airborne movement gets the same wall sweep but keeps its Y for the
    // fighter's vertical integrator. The sweep is a continuous set of rays offset
    // around the fighter footprint, with multiple body-height samples.
    MovementResult move(const glm::vec3& start, const glm::vec3& desired,
                        bool grounded) const;

    // Project a preferred env.dat/override spawn onto a walkable surface. If that
    // point is unusable, select the nearest valid supplied spawn, then the nearest
    // walkable triangle centroid. Returns a finite fallback if the stage has no
    // movement geometry.
    glm::vec3 resolveSpawn(const glm::vec3& preferred,
                          const glm::vec3* candidates = nullptr,
                          size_t candidateCount = 0) const;

    // Used by the fighter's last-safe-position recovery. A missing collision file is
    // intentionally permissive; invalid non-finite values are still rejected.
    bool validPosition(const glm::vec3& position) const;

    static constexpr float kFighterRadius = 20.f;
    static constexpr float kFighterHeight = 145.f;
    static constexpr float kMaxStepUp = 50.f;
    static constexpr float kMaxStepDown = 120.f;

private:
    const xm::Model* movementMesh_ = nullptr;
    const xm::Model* groundMesh_ = nullptr;
    ModelIndex movementIndex_;
    ModelIndex groundIndex_;
    size_t movementTriangles_ = 0;
    size_t groundTriangles_ = 0;
    glm::vec3 boundsMin_{0.f};
    glm::vec3 boundsMax_{0.f};
    bool haveBounds_ = false;

    // One movement triangle's axis-aligned bounds, in the mesh's own vertex space (the
    // queries apply no frame transform — see the file comment).
    struct FaceBounds {
        glm::vec3 lo{0.f};
        glm::vec3 hi{0.f};
    };
    // Per mesh, then per face: the bounds firstWallHit's sweep prunes with. Filled by
    // setMeshes. A mesh the movement index does not walk gets an empty entry and is never
    // asked for one.
    std::vector<std::vector<FaceBounds>> movementFaceBounds_;

    // True when the horizontal sweep segment [origin, origin + direction*limit] can reach
    // the face's bounds. `limit <= 0` means "no cutoff", exactly as intersectTriangle reads
    // maxDist. Conservative by construction: a face it answers false for holds no point
    // within the segment, so it can never drop a hit. A direction component of exactly zero
    // is tested as containment rather than through its reciprocal, because a ray that grazes
    // a slab boundary must still be kept.
    static bool sweepReachesBounds(const FaceBounds& bounds, const glm::vec3& origin,
                                   const glm::vec3& direction, float invDx, float invDz,
                                   float limit);

    RayHit firstWallHit(const glm::vec3& start, const glm::vec3& delta) const;
    glm::vec3 slideSegment(const glm::vec3& start, const glm::vec3& delta,
                           bool& hitWall) const;
    bool insideHorizontalBounds(float x, float z) const;
    GroundHit nearestGround(float x, float z) const;
};

// The physics side of the arena camera clamp (camera/camera_collision.h:36-40): the
// distance from the aim to the first collision_camera.x blocker along the
// aim -> desired-eye segment.
//
//   * setMesh(nullptr) — or a mesh with no triangles, which two shipped stages have
//     (stage04/stage14 collision_camera.x parse to 0 vertices / 0 triangles) — makes
//     every query answer "no hit", the contract's fallback for stages that ship no
//     camera collision geometry (camera_collision.h:33-35). Passing collision.x
//     instead is caller policy (the reference's fallback note, remake/src/maps/stage.h:57),
//     not applied here.
//   * The reference clamps only when hit.dist < the segment length
//     (remake/src/render/arena_camera.cpp:111-113); that comparison lives here so the
//     caller's hitDist is exactly the reference's hit.dist.
//   * The 20-unit pull-back is NOT applied here: it is arenaClampEye's margin
//     (camera/arena_view.h), which keeps render tuning out of physics. Pair this
//     with game::clampHitDistance() so a miss and an unblocked segment behave alike.
class CameraCollision final : public game::ICameraCollision {
public:
    // Rebuilds the traversal order; null is valid and means "no camera geometry".
    void setMesh(const xm::Model* cameraMesh);

    const xm::Model* mesh() const { return mesh_; }

    // True when no triangle can be hit, i.e. the query will always answer "no hit".
    bool empty() const { return triangles_ == 0; }

    CameraClampResult queryClamp(const CameraClampQuery& q) const override;

private:
    const xm::Model* mesh_      = nullptr;
    ModelIndex       index_;
    size_t           triangles_ = 0;
};

}  // namespace game::physics
