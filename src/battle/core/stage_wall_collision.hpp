#pragma once
#include "stage_collision_mesh.hpp"
#include "legacy_stage_surface_scalar24.hpp"
#include "battle_horizontal_move.hpp"
#include "battle_wall_selection.hpp"
namespace daybreak {
//42d3b0 scalar PC24 motion length/ray origin/surface geometry adapter.
// The CLOSED mesh-local response reducer and ALL-hit traversal are retained.
class StageWallCollision {
    const StageCollisionMesh& mesh_;
public:
    explicit StageWallCollision(const StageCollisionMesh& mesh):mesh_(mesh){}
    bool has_motion(const BattleVector& motion)const{return motion[0]!=0||motion[1]!=0||motion[2]!=0;}
    BattleCollisionResult collide(const BattleVector& position,const BattleVector& motion,float maximum)const{
        const float length=projectile_motion_length(motion);
        if(!(length>0)){BattleCollisionResult result;result.distance=maximum;return result;}
        //42d3fe calls the same selected D3DX Normalize as the surface frames.
        const auto ray=actor_controller_normalize3(motion);
        const CollisionPoint direction{{ray[0],ray[1],ray[2]}};
        const auto original_origin=legacy_stage_wall_origin(position);
        const CollisionPoint origin{{original_origin[0],original_origin[1],original_origin[2]}};
        BattleWallSelection selection;
        for(const auto& hit:mesh_.intersect(origin,direction)){
            const auto& triangle=mesh_.face_for_hit(hit);
            const auto normal=legacy_stage_surface_normal(collision_native_triangle(triangle));
            const float normal_y=float(normal[1]);volatile float squared_y=normal_y*normal_y;if(!(squared_y<0.5f))continue;
            const auto h=legacy_stage_surface_horizontal(normal),t=legacy_stage_surface_tangent(normal);
            const float incidence=battle_wall_dot(ray,h);
            selection.observe(make_battle_wall_candidate(hit.mesh,float(hit.distance),incidence,h,t));
        }
        return selection.resolve(ray,float(length),maximum);
    }
};
}
