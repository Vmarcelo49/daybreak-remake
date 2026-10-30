#pragma once
#include "stage_collision_mesh.hpp"
#include "legacy_stage_surface_scalar24.hpp"
#include "battle_vertical_move.hpp"
#include "battle_floor_selection.hpp"
namespace daybreak {
using StageFloorQuery=BattleFloorSelection;
//42cd50 scalar PC24 vertex/edge/cross/Normalize geometry and ALL-hit ordering.
// Final optimized DAT face-ID mapping is a separate loader boundary.
class StageFloorCollision {
    const StageCollisionMesh& mesh_;
    static std::uint8_t channel(double value){
        if(!std::isfinite(value))throw std::invalid_argument("Nonfinite floor color");
        // Retained bounded native text-X color proof: nearest-byte conversion.
        return std::uint8_t(std::max(0.,std::min(255.,std::floor(value*255.+.5))));
    }
public:
    explicit StageFloorCollision(const StageCollisionMesh& mesh):mesh_(mesh){}
    StageFloorQuery query(const BattleVector& position,float velocity)const{
        if(!std::isfinite(velocity))throw std::invalid_argument("Nonfinite floor velocity");
        for(float v:position)if(!std::isfinite(v))throw std::invalid_argument("Nonfinite floor position");
        StageFloorQuery out;volatile float origin_y=position[1]+50.f;
        for(const auto& hit:mesh_.intersect({{position[0],origin_y,position[2]}},{{0,-1,0}})){
            const auto& face=mesh_.face_for_hit(hit);std::uint8_t red=0,blue=0;
            if(face.has_color_block){
                // Retained original-DLL X loader proof: omitted COLOR0=00ffffff.
                if(face.colors[0]){red=channel((*face.colors[0])[0]);blue=channel((*face.colors[0])[2]);}
                else red=blue=255;
            }
            const float ray=static_cast<float>(hit.distance);
            if(!out.accept(face.has_color_block,red,blue,ray,velocity))continue;
            const auto normal=legacy_stage_surface_normal(collision_native_triangle(face));
            out.observe(ray,velocity,normal);
        }
        return out;
    }
};
}
