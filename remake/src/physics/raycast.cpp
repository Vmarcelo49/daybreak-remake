// =============================================================================
//  raycast.cpp — see raycast.h for design notes.
//
//  Mirrors the original game's traversal pattern (see fcn.0042d3b0,
//  fcn.0042cd50, fcn.0042d2c0, fcn.00633930 in DaybreakDX.exe):
//
//    walk(frame):
//      for mc in frame.pMeshContainer chain:
//        D3DXIntersect(mc.mesh, rayPos, rayDir, &hit, &face, &u, &v, &dist, ...)
//        if hit and dist < best: record closest
//      walk(frame.pFrameFirstChild)
//      walk(frame.pFrameSibling)
//
//  Two flavors:
//    - raycast_model()     : closest hit (loops through all hits, picks min)
//    - raycast_model_any() : early-out on first hit
//
//  The original game uses globals for the "best so far" hit state.  We pass
//  it through a struct instead — same speed, reentrant, no globals.
// =============================================================================
#include "raycast.h"

#include <algorithm>
#include <limits>

namespace daybreak::physics {

namespace {

// Recursive walker for the "closest hit" variant.
struct ClosestHitState {
    D3DXVECTOR3 rayPos;
    D3DXVECTOR3 rayDir;
    float       maxDist;
    bool        found;
    DWORD       faceIndex;
    float       u, v, dist;
    ID3DXMesh*  mesh;
};

void walk_closest(D3DXFRAME* frame, ClosestHitState& s) {
    if (!frame) return;

    // In D3DXFRAME, pMeshContainer is the head; each D3DXMESHCONTAINER has
    // pNextMeshContainer at offset +0x20.
    D3DXMESHCONTAINER* mc = frame->pMeshContainer;
    while (mc) {
        if (mc->MeshData.Type == D3DXMESHTYPE_MESH && mc->MeshData.pMesh) {
            ID3DXMesh* mesh = mc->MeshData.pMesh;

            BOOL  hit     = FALSE;
            DWORD faceIdx = 0;
            float u       = 0.0f;
            float v       = 0.0f;
            float dist    = 0.0f;

            // We pass nullptr for ppAllHits / pCountOfHits — we only care
            // about the closest hit, which D3DXIntersect returns in pDist /
            // pFaceIndex / pU / pV directly.
            HRESULT hr = D3DXIntersect(mesh,
                                       &s.rayPos, &s.rayDir,
                                       &hit, &faceIdx, &u, &v, &dist,
                                       nullptr, nullptr);
            if (SUCCEEDED(hr) && hit) {
                if ((!s.found || dist < s.dist) &&
                    (s.maxDist <= 0.0f || dist <= s.maxDist)) {
                    s.found     = true;
                    s.faceIndex = faceIdx;
                    s.u         = u;
                    s.v         = v;
                    s.dist      = dist;
                    s.mesh      = mesh;
                }
            }
        }
        mc = mc->pNextMeshContainer;
    }

    // Recurse into the frame hierarchy.  The original game walks both
    // pFrameFirstChild (+0x48) and pFrameSibling (+0x4c) — same here.
    if (frame->pFrameFirstChild) walk_closest(frame->pFrameFirstChild, s);
    if (frame->pFrameSibling)    walk_closest(frame->pFrameSibling,    s);
}

// Recursive walker for the "any hit" variant — early-outs as soon as it
// finds anything within maxDist.
struct AnyHitState {
    D3DXVECTOR3 rayPos;
    D3DXVECTOR3 rayDir;
    float       maxDist;
    bool        found;
};

bool walk_any(D3DXFRAME* frame, AnyHitState& s) {
    if (!frame) return false;

    D3DXMESHCONTAINER* mc = frame->pMeshContainer;
    while (mc) {
        if (mc->MeshData.Type == D3DXMESHTYPE_MESH && mc->MeshData.pMesh) {
            BOOL  hit     = FALSE;
            DWORD faceIdx = 0;
            float u = 0.0f, v = 0.0f, dist = 0.0f;

            HRESULT hr = D3DXIntersect(mc->MeshData.pMesh,
                                       &s.rayPos, &s.rayDir,
                                       &hit, &faceIdx, &u, &v, &dist,
                                       nullptr, nullptr);
            if (SUCCEEDED(hr) && hit &&
                (s.maxDist <= 0.0f || dist <= s.maxDist)) {
                s.found = true;
                return true;
            }
        }
        mc = mc->pNextMeshContainer;
    }

    if (frame->pFrameFirstChild && walk_any(frame->pFrameFirstChild, s)) return true;
    if (frame->pFrameSibling    && walk_any(frame->pFrameSibling,    s)) return true;
    return false;
}

} // namespace

RaycastHit raycast_model(D3DXFRAME* rootFrame,
                         const D3DXVECTOR3& rayPos,
                         const D3DXVECTOR3& rayDir,
                         float maxDist) {
    ClosestHitState s{};
    s.rayPos = rayPos;
    s.rayDir = rayDir;
    s.maxDist = maxDist;
    s.found = false;
    s.dist = std::numeric_limits<float>::max();
    s.mesh = nullptr;

    walk_closest(rootFrame, s);

    RaycastHit out;
    if (s.found) {
        out.hit       = true;
        out.faceIndex = s.faceIndex;
        out.u         = s.u;
        out.v         = s.v;
        out.dist      = s.dist;
        out.mesh      = s.mesh;
        out.point = D3DXVECTOR3(
            rayPos.x + s.dist * rayDir.x,
            rayPos.y + s.dist * rayDir.y,
            rayPos.z + s.dist * rayDir.z);
    }
    return out;
}

bool raycast_model_any(D3DXFRAME* rootFrame,
                       const D3DXVECTOR3& rayPos,
                       const D3DXVECTOR3& rayDir,
                       float maxDist) {
    AnyHitState s{};
    s.rayPos  = rayPos;
    s.rayDir  = rayDir;
    s.maxDist = maxDist;
    s.found   = false;
    walk_any(rootFrame, s);
    return s.found;
}

} // namespace daybreak::physics
