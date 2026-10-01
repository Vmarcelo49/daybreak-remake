// =============================================================================
//  stage.h — Stage container (matches the original game's per-stage layout).
//
//  The original DaybreakDX.exe (fcn.004011f0) loads THREE collision meshes
//  per stage, each as a separate XModel:
//
//    %s/collision.x          — general collision (walls, floor)
//    %s/collision_camera.x   — camera-only collision (more permissive)
//    %s/collision_tama.x     — projectile ("tama" = 玉, ball) collision
//
//  plus a visible stage mesh (geometry the player sees).  This struct owns
//  all four as XModel handles and exposes per-mesh raycast helpers so the
//  gameplay / camera / projectile code can each query the right mesh.
//
//  Path convention: the stage's name (e.g. "schoolyard") is interpolated
//  into "%s/collision.x" by the asset manager before calling Stage::load,
//  so Stage itself just takes fully-resolved paths.
// =============================================================================
#pragma once

#include <d3d9.h>

#include <memory>
#include <string>

#include "file_parser/x_model_loader.h"

namespace daybreak::maps {

enum class CollisionChannel : int {
    Character = 0,   // collision.x         — fighter body / movement
    Camera    = 1,   // collision_camera.x  — camera collision only
    Projectile= 2,   // collision_tama.x    — projectile ("tama") collision
};

class Stage {
public:
    Stage() = default;
    ~Stage();

    Stage(const Stage&)            = delete;
    Stage& operator=(const Stage&) = delete;
    Stage(Stage&&)                 = delete;
    Stage& operator=(Stage&&)      = delete;

    // Loads the four meshes for a stage.
    //
    // `base_dir` is the stage's directory (e.g. "data/stage/schoolyard/").
    // The loader looks for:
    //   <base_dir>/collision.x
    //   <base_dir>/collision_camera.x
    //   <base_dir>/collision_tama.x
    //   <base_dir>/stage.x     (the visible mesh — optional, missing OK)
    //
    // Returns true if at least the visible stage mesh loaded.  Missing
    // collision meshes are logged as warnings but don't fail the load —
    // some stages ship without collision_camera.x (then camera uses the
    // character collision mesh as fallback).
    bool load(IDirect3DDevice9* device, const std::string& base_dir);

    // Releases all owned meshes.  Safe to call multiple times.
    void unload();

    bool is_loaded() const { return m_visible_mesh.get() != nullptr; }

    // Access the visible stage mesh (geometry the player sees).
    XModel* visible_mesh() const { return m_visible_mesh.get(); }

    // Access a collision mesh.  Returns nullptr if that mesh failed to
    // load (caller should fall back to a less-restrictive channel).
    XModel* collision_mesh(CollisionChannel channel) const;

    // Convenience: raycast against a specific collision channel.  Returns
    // a no-hit RaycastHit if the channel's mesh isn't loaded.
    //
    // Internally calls physics::raycast_model on the mesh's root frame.
    // The ray must be in world space — Stage does NOT apply any transform
    // (matching the original game, which loads collision*.x with identity
    // frame transforms).
    struct RaycastHit {  // re-export so callers don't need physics/raycast.h
        bool        hit        = false;
        DWORD       faceIndex  = 0;
        float       u          = 0.0f;
        float       v          = 0.0f;
        float       dist       = 0.0f;
        float       point[3]   = {0.0f, 0.0f, 0.0f};
    };
    RaycastHit raycast(CollisionChannel channel,
                       const float rayPos[3],
                       const float rayDir[3],
                       float maxDist = 0.0f) const;

    // Quick "did I hit anything at all" test — early-outs on first hit.
    bool raycast_any(CollisionChannel channel,
                     const float rayPos[3],
                     const float rayDir[3],
                     float maxDist = 0.0f) const;

private:
    std::unique_ptr<XModel> m_visible_mesh;       // stage.x
    std::unique_ptr<XModel> m_collision_char;     // collision.x
    std::unique_ptr<XModel> m_collision_camera;   // collision_camera.x
    std::unique_ptr<XModel> m_collision_tama;     // collision_tama.x
};

} // namespace daybreak::maps
