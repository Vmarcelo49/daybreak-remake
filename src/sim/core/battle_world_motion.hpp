#pragma once
#include "battle_world.hpp"
namespace daybreak {
// Actor position/heading/relationship offset are authoritative. Motion owns
// speed, velocity, applied vector, relative angle (+0x60), gate and blocked.
template<class Wall,class Floor> void update_world_motion(BattleWorld& world,unsigned slot,Wall& wall,const Floor& floor){
    auto& actor=world.actors.at(slot);auto& motion=actor.motion;
    motion.position=actor.position;motion.grounded=actor.grounded;
    motion.angles[0]=actor.heading;std::memcpy(&motion.angles[2],&actor.relationships.heading_offset_bits,4);
    struct Host {
        BattleWorld& world;unsigned slot;Wall& wall;const Floor& floor;
        void horizontal(BattleMotionState& s,const BattleVector& delta){
            world.actors[slot].position=s.position;world.move_horizontal(slot,delta,wall);s.position=world.actors[slot].position;
        }
        void vertical(BattleMotionState& s,float& velocity){
            world.actors[slot].position=s.position;world.actors[slot].grounded=std::uint8_t(s.grounded);
            world.move_vertical(slot,velocity,floor);s.position=world.actors[slot].position;s.grounded=world.actors[slot].grounded;
        }
        void face_target(BattleMotionState& s){
            const auto& target=world.actors.at(world.actors[slot].relationships.target);
            BattleFacing facing{s.angles[0],s.angles[2]};
            face_battle_target(facing,s.position[0],s.position[2],target.position[0],target.position[2]);
            s.angles[0]=facing.heading;s.angles[2]=facing.offset;
        }
    } host{world,slot,wall,floor};
    update_battle_motion(motion,host);
    actor.position=motion.position;actor.grounded=std::uint8_t(motion.grounded);actor.heading=motion.angles[0];
    std::memcpy(&actor.relationships.heading_offset_bits,&motion.angles[2],4);
}
}
