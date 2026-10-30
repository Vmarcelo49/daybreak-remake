#pragma once
#include "development_animated_combat.hpp"
#include "item11_22_projectiles.hpp"
namespace daybreak {
// Common item-script context: manager+2c actor survives reflection of obj+8.
// Attack ownership stays in state.owner; actor services use manager_owner.
struct ProjectileManagerServices {
 DevelopmentAnimatedCombat& combat;const BattleWorld& world;unsigned manager_owner;
    void retarget_owner(KeiichiNormalProjectile& s){
     // Original 005f7430 performs exactly
     // obj->target = obj->item_data->manager_actor (obj+38 <- [obj+11c]+2c).
     // It neither destroys children nor changes their pool ownership.
     s.target=manager_owner;
    }
    void target_refresh(KeiichiNormalProjectile& s){
     const auto& opponents=world.actors.at(manager_owner).relationships.opponents;
     for(const auto candidate:opponents)if(candidate!=s.target&&candidate<world.actors.size()){
      s.target=candidate;notify_projectile_retarget(s);return;
     }
    }
    unsigned field_rank_increment(const KeiichiNormalProjectile& s){
     auto& rank=combat.field_contact_rank[manager_owner];++rank;if(projectile_signed(rank)>3)rank=3;
     combat.field_contact_rank_timer[manager_owner]=360;return rank;
    }
    unsigned owner_state(const KeiichiNormalProjectile& s)const{return combat.current_action_state(manager_owner);}
    int owner_health(const KeiichiNormalProjectile& s)const{return damage_signed(combat.health.at(manager_owner));}
    unsigned owner_projectile_command(const KeiichiNormalProjectile& s)const{return combat.owner_orbit_command(manager_owner);}
    unsigned owner_current_target(const KeiichiNormalProjectile& s)const{return world.actors.at(manager_owner).relationships.target;}
    std::array<float,3> owner_position(const KeiichiNormalProjectile& s)const{return world.actors.at(manager_owner).position;}
    void store_owner_field_position(const KeiichiNormalProjectile& s){
     for(unsigned n=0;n<3;++n)combat.projectile_owner_integer_field[manager_owner][n]=item22_integer_coordinate(s.position[n]);
    }
    std::array<float,3> owner_field_position(const KeiichiNormalProjectile& s)const{
     const auto& p=combat.projectile_owner_integer_field.at(manager_owner);return {float(p[0]),float(p[1]),float(p[2])};
    }
    unsigned owner_field_exit(const KeiichiNormalProjectile& s)const{return combat.projectile_owner_field_exit.at(manager_owner);}
    void request_owner_field_exit(const KeiichiNormalProjectile& s){combat.projectile_owner_field_exit.at(manager_owner)=1;}
    float owner_heading(const KeiichiNormalProjectile& s)const{return world.actors.at(manager_owner).heading;}
    float owner_pitch(const KeiichiNormalProjectile& s)const{return combat.projectile_owner_pitch(manager_owner);}
    bool owner_linked_pose(const KeiichiNormalProjectile& s,std::array<float,3>& position,
                          float& heading,float& offset)const{
     const auto linked=combat.target_availability.at(manager_owner).paired_actor;
     if(linked>=world.actors.size())return false;
     const auto& actor=world.actors[linked];position=actor.position;heading=actor.heading;
     std::memcpy(&offset,&actor.relationships.heading_offset_bits,4);return true;
    }
    float owner_offset(const KeiichiNormalProjectile& s)const{
     float result;const auto bits=world.actors.at(manager_owner).relationships.heading_offset_bits;
     std::memcpy(&result,&bits,sizeof result);return result;
    }
    unsigned owner_phase(const KeiichiNormalProjectile& s)const{return combat.projectile_owner_phase(manager_owner);}
    unsigned owner_animation_frame(const KeiichiNormalProjectile& s)const{
     return combat.projectile_owner_animation_frame(manager_owner);
    }
    int owner_input_x(const KeiichiNormalProjectile& s)const{return combat.projectile_input_x(manager_owner);}
    void owner_signal(const KeiichiNormalProjectile& s,unsigned value){combat.notify_roster_shot_projectile_signal(manager_owner,value);}
    void owner_projectile_aim(const KeiichiNormalProjectile& s,
                              const std::array<float,3>& aim_position){
     combat.projectile_owner_aim[manager_owner]=aim_position;
    }
    std::array<float,3> owner_aim(const KeiichiNormalProjectile& s)const{return combat.projectile_owner_aim.at(manager_owner);}
    unsigned owner_signal_value(const KeiichiNormalProjectile& s)const{return combat.projectile_owner_signal(manager_owner);}
    std::array<float,3> owner_right_hand(const KeiichiNormalProjectile& s)const{
     std::optional<ActorSkeleton> fallback;
     //The 32-bit string implementation cannot store this name inline.
     //Keep one immutable lookup key instead of allocating it on each read.
     static const std::string hand_name="Bip01_R_Hand";
     const auto& pose=combat.render_pose_view(manager_owner,fallback);const auto bone=pose.find(hand_name);
     if(!bone)throw std::runtime_error("Projectile owner right hand bone missing");
     //64E6C0 returns the already combined hand matrix; neither caller resamples
     //the pose. Transform the origin as at5FEE82/6243EC, discarding W only.
     const auto matrix=combat.actor_bone_world(world,manager_owner,bone);
     const auto point=transform_actor_point({0,0,0},matrix);
     return {point[0],point[1],point[2]};
    }
};
}
