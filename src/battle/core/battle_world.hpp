#pragma once
#include "battle_teams.hpp"
#include "battle_relationships.hpp"
#include "battle_facing.hpp"
#include "battle_horizontal_move.hpp"
#include "battle_vertical_move.hpp"
#include "floor_color_policy.hpp"
#include "battle_motion.hpp"
#include <cstring>
#include <stdexcept>
namespace daybreak {
struct BattleActor {
    std::array<float,3> position{};
    float heading=180.f;
    std::uint8_t ally_flag=0;
    BattleRelationships relationships;
    float collision_distance=0;
    std::uint8_t collided=0;
    float floor_distance=10000;
    // Native41ddc9 initializes84 to one before the first floor query.
    std::uint8_t grounded=1;
    FloorColorFlags floor_flags;
    BattleMotionState motion;
};
// A stable 0..3 handle replaces an original pointer. Shared-field links use
// the same handle space, but identify the actor's shared field specifically.
struct BattleWorld {
    std::array<BattleActor,4> actors;
    BattleTeams teams;
    template<class FloorHost> void move_vertical(unsigned slot,float velocity,const FloorHost& floor){
        auto& actor=actors.at(slot);
        const auto result=floor.query(actor.position,velocity);
        BattleVerticalState state{actor.position,actor.floor_distance,actor.grounded};
        apply_battle_floor(state,velocity,result.floor);
        actor.position=state.position;actor.floor_distance=state.floor_distance;actor.grounded=state.grounded;actor.floor_flags=result.flags;
    }
    template<class CollisionHost> void move_horizontal(unsigned slot,const BattleVector& motion,CollisionHost& collision){
        auto& actor=actors.at(slot);
        BattleHorizontalState state{actor.position,actor.collision_distance,actor.collided};
        move_battle_horizontal(state,motion,collision);
        actor.position=state.position;actor.collision_distance=state.collision_distance;actor.collided=state.collided;
    }
    void add_ally(unsigned self,unsigned other){
        auto& a=actors.at(self);auto& b=actors.at(other);
        add_battle_ally(a.relationships,other,b.ally_flag,other);
    }
    void add_opponent(unsigned self,unsigned other){
        auto& actor=actors.at(self);
        add_battle_opponent(actor.relationships,other,[&](BattleRelationships& r){
            const auto& target=actors.at(r.target);
            float offset;std::memcpy(&offset,&r.heading_offset_bits,4);
            BattleFacing facing{actor.heading,offset};
            face_battle_target(facing,actor.position[0],actor.position[2],target.position[0],target.position[2]);
            actor.heading=facing.heading;std::memcpy(&r.heading_offset_bits,&facing.offset,4);
        });
    }
    void initialize(const std::array<std::array<float,3>,4>& positions,
                    const std::array<std::uint8_t,4>& flags,
                    const std::array<std::uint8_t,4>& modes,
                    const std::array<std::uint32_t,2>& resources){
        // Check all inputs before changing an existing world.
        for(const auto& position:positions)for(float value:position)
            if(!std::isfinite(value))throw std::invalid_argument("Nonfinite battle spawn position");
        for(unsigned i=0;i<4;++i){actors[i]=BattleActor{};actors[i].position=positions[i];actors[i].ally_flag=flags[i];actors[i].relationships.mode=modes[i];}
        initialize_battle_teams(teams,resources,*this);
    }
};
}
