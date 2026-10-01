// =============================================================================
//  stage.cpp — see stage.h for the design rationale.
// =============================================================================
#include "stage.h"

#include <cstdio>

#include "physics/raycast.h"

namespace daybreak::maps {

namespace {

// Tiny RAII helper: loads an XModel, logs on failure, leaves the unique_ptr
// null on failure (caller checks before use).
std::unique_ptr<XModel> try_load_x(IDirect3DDevice9* device,
                                    const std::string& path,
                                    bool required) {
    auto m = std::make_unique<XModel>();
    if (m->load(device, path)) {
        return m;
    }
    if (required) {
        std::fprintf(stderr, "[daybreak] Stage: required mesh failed: %s\n",
                     path.c_str());
    } else {
        std::printf("[daybreak] Stage: optional mesh missing (ok): %s\n",
                    path.c_str());
    }
    return nullptr;
}

} // namespace

Stage::~Stage() { unload(); }

bool Stage::load(IDirect3DDevice9* device, const std::string& base_dir) {
    unload();

    std::string dir = base_dir;
    if (dir.empty() || (dir.back() != '/' && dir.back() != '\\')) {
        dir += '/';
    }

    // Visible mesh — required (a stage with no visible mesh is useless).
    m_visible_mesh = try_load_x(device, dir + "stage.x", /*required=*/true);
    if (!m_visible_mesh) return false;

    // Three collision meshes — optional, missing is logged but not fatal.
    m_collision_char   = try_load_x(device, dir + "collision.x",         /*required=*/false);
    m_collision_camera = try_load_x(device, dir + "collision_camera.x",  /*required=*/false);
    m_collision_tama   = try_load_x(device, dir + "collision_tama.x",    /*required=*/false);

    std::printf("[daybreak] Stage loaded from %s  (coll: char=%d cam=%d tama=%d)\n",
                dir.c_str(),
                m_collision_char   ? 1 : 0,
                m_collision_camera ? 1 : 0,
                m_collision_tama   ? 1 : 0);
    return true;
}

void Stage::unload() {
    m_visible_mesh.reset();
    m_collision_char.reset();
    m_collision_camera.reset();
    m_collision_tama.reset();
}

XModel* Stage::collision_mesh(CollisionChannel channel) const {
    switch (channel) {
        case CollisionChannel::Character:  return m_collision_char.get();
        case CollisionChannel::Camera:     return m_collision_camera.get();
        case CollisionChannel::Projectile: return m_collision_tama.get();
    }
    return nullptr;
}

Stage::RaycastHit Stage::raycast(CollisionChannel channel,
                                  const float rayPos[3],
                                  const float rayDir[3],
                                  float maxDist) const {
    RaycastHit out;
    XModel* m = collision_mesh(channel);
    if (!m || !m->root_frame()) return out;

    D3DXVECTOR3 pos(rayPos[0], rayPos[1], rayPos[2]);
    D3DXVECTOR3 dir(rayDir[0], rayDir[1], rayDir[2]);
    auto hit = daybreak::physics::raycast_model(m->root_frame(), pos, dir, maxDist);
    if (hit.hit) {
        out.hit       = true;
        out.faceIndex = hit.faceIndex;
        out.u         = hit.u;
        out.v         = hit.v;
        out.dist      = hit.dist;
        out.point[0]  = hit.point.x;
        out.point[1]  = hit.point.y;
        out.point[2]  = hit.point.z;
    }
    return out;
}

bool Stage::raycast_any(CollisionChannel channel,
                        const float rayPos[3],
                        const float rayDir[3],
                        float maxDist) const {
    XModel* m = collision_mesh(channel);
    if (!m || !m->root_frame()) return false;

    D3DXVECTOR3 pos(rayPos[0], rayPos[1], rayPos[2]);
    D3DXVECTOR3 dir(rayDir[0], rayDir[1], rayDir[2]);
    return daybreak::physics::raycast_model_any(m->root_frame(), pos, dir, maxDist);
}

} // namespace daybreak::maps
