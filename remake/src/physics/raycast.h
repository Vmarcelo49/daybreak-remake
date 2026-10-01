// =============================================================================
//  raycast.h — mesh-vs-ray collision (D3DXIntersect wrapper).
//
//  Ported direction taken from the original DaybreakDX.exe (analyzed with
//  radare2 — see docs/reverse-engineering.md):
//
//    * The game uses D3DXIntersect for ALL collision queries. There is no
//      custom sphere/AABB/OBB code — every "did this hit?" question is
//      answered by raycasting against a triangle mesh.
//
//    * Three collision meshes are loaded per stage, each as a regular XModel:
//        - "%s/collision.x"          general collision (walls, floor)
//        - "%s/collision_camera.x"   camera-only collision
//        - "%s/collision_tama.x"     projectile ("tama" = 玉, ball) collision
//
//    * The raycast walks the D3DXFRAME hierarchy recursively and calls
//      D3DXIntersect on every mesh container it finds, in model space.
//      No transform is applied to the ray — the mesh is assumed to already
//      be in world space (or the caller pre-transforms the ray).
//
//    * Hit information is stored as:
//        - BOOL  hit
//        - DWORD faceIndex
//        - float u, v (barycentric)
//        - float dist (distance along the ray direction)
//
//  This module exposes one function: raycast_model() does the recursive
//  walk + D3DXIntersect, returning the closest hit (or no hit).  A second
//  function, raycast_model_any(), returns on the first hit (cheaper when
//  you only care about line-of-sight, not the impact point).
// =============================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9anim.h>

#include <cstdint>

namespace daybreak::physics {

// A single ray hit against a triangle in a mesh container.
struct RaycastHit {
    bool        hit        = false;
    DWORD       faceIndex  = 0;
    float       u          = 0.0f;
    float       v          = 0.0f;
    float       dist       = 0.0f;   // distance along the ray direction
    D3DXVECTOR3 point      {};       // hit point in world space (computed)
    ID3DXMesh*  mesh       = nullptr; // which mesh container was hit
};

// Cast `rayPos + t*rayDir` (for t in [0, maxDist]) against every mesh
// container reachable from `rootFrame` (recursive walk over pFrameFirstChild
// and pFrameSibling, mirroring the original game's traversal).
//
// Returns the closest hit (smallest t).  If `maxDist` is <= 0, no distance
// cutoff is applied.
//
// Note: like the original game, this does NOT transform the ray by the
// frame's world matrix.  The meshes are expected to already be in the
// space the ray is in (typically world space for stage collision meshes,
// which are loaded without any frame hierarchy transform).
RaycastHit raycast_model(D3DXFRAME* rootFrame,
                         const D3DXVECTOR3& rayPos,
                         const D3DXVECTOR3& rayDir,
                         float maxDist = 0.0f);

// Same as raycast_model, but returns as soon as ANY triangle is hit within
// maxDist — cheaper than finding the closest hit when you only need a
// yes/no answer (line-of-sight checks, "is the target occluded?" tests,
// "is this point inside a wall?" probes).
bool raycast_model_any(D3DXFRAME* rootFrame,
                       const D3DXVECTOR3& rayPos,
                       const D3DXVECTOR3& rayDir,
                       float maxDist = 0.0f);

} // namespace daybreak::physics
