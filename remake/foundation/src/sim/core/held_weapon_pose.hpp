#pragma once
#include "actor_world_hierarchy.hpp"
#include "weapon_item_data.hpp"
namespace daybreak {
// 41e180 passes Prop1/Prop2 to433eb0. 42fff0 copies that bone matrix;
// 430120 supplies it as the weapon model's world matrix. DAT position/rotation
// fields are actually trail endpoints, not an extra model transform.
inline LegacyMatrix held_weapon_pose(const ActorSkeleton& actor,unsigned slot,const LegacyMatrix& world){
 if(slot>1)throw std::out_of_range("Weapon hand slot");const auto bone=actor.find(slot?"Bip01_Prop2":"Bip01_Prop1");
 if(!bone)throw std::runtime_error("Weapon attachment bone missing");std::vector<LegacyMatrix> combined;
 combine_actor_world_hierarchy(actor,world,combined);return combined.at(bone);
}
inline std::array<int,2> held_weapon_models(unsigned character,unsigned weapon,unsigned state,unsigned phase,unsigned tick,bool boosted=false){
 if(character==0&&weapon==0&&state==400&&tick>11)return {{-1,-1}};
 if(character==0&&state==350&&(weapon==0||(weapon==2&&tick>116)))return {{-1,-1}};
 if(character==14&&weapon==1&&state==401&&boosted)return {{2,-1}};
 std::array<int,2> out{{0,1}};if(character!=1)return out;
 if(state==360||(state==350&&(phase<2||(phase==2&&tick<10))))return {{4,-1}};
 if(weapon!=0){if(state==450||state==460)return {{2,-1}};if(weapon==2&&state==404&&tick==17)return {{3,-1}};return out;}
 if((state>=450&&state<=454)||state==460){
  const unsigned split=state==453?21:18;
  if(state==454&&tick==17)return {{3,-1}};
  if(tick<split)return {{2,-1}};
  if(state!=452&&tick>(state==450?47u:50u))return out;
  return {{3,-1}};
 }
 return out;
}
}
