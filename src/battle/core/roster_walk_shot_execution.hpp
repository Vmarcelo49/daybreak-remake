#pragma once
#include "keiichi_walk_shot.hpp"
#include <array>
#include <vector>

namespace daybreak {

struct RosterWalkShotProfile {
 float speed;
 unsigned stop_frame,first_fire,last_fire,interval;
 int sound;
 std::array<unsigned,3> bullets{};
 unsigned count;
 GroundShotOrigin origin=GroundShotOrigin::RightHand;
};

inline bool roster_walk_shot_recovered(unsigned character,unsigned weapon){
 return (character==4&&weapon==0)||(character==5&&weapon==0)||
  (character==6&&weapon==2)||(character==7&&weapon==0)||character==10||
  (character==14&&weapon<2);
}

// Original actor slot-6 state410/411/412, sampled in both neutral and moving
// input for every roster configuration which can enter these states. State411
// and 412 share the same schedule within each character/weapon pair.
inline RosterWalkShotProfile roster_walk_shot_profile(unsigned character,unsigned weapon,unsigned state){
 if(!keiichi_walk_shot_state(state))throw std::invalid_argument("Walking shot state");
 switch(character){
 case 4:if(weapon==0)return {4.f,21,20,20,1,95,{0,0,0},1};break;
 case 5:if(weapon==0)return {8.f,13,12,12,1,116,{0,0,0},1,GroundShotOrigin::AttachmentZero};break;
 case 6:if(weapon==2)return {6.25f,state==410?1u:36u,15,35,3,230,{5,7,0},2,GroundShotOrigin::AttachmentZero};break;
 case 7:if(weapon==0)return {6.75f,21,13,21,4,128,{0,0,0},1};break;
 case 10:
  if(weapon==0)return {5.5f,21,12,12,1,128,{16,16,16},3};
  if(weapon==1)return {5.5f,21,12,12,1,128,{1,0,0},2};
  if(weapon==2)return {5.5f,21,12,12,1,128,{0,0,0},3};
  break;
 case 14:
  if(weapon==0)return {4.f,21,20,20,1,213,{0,0,0},1};
  if(weapon==1)return {4.f,21,20,20,1,217,{0,0,0},1};
  break;
 }
 throw std::invalid_argument("Unrecovered roster walking shot");
}

inline GroundShotEffects advance_roster_walk_shot(unsigned character,unsigned weapon,
 unsigned state,KeiichiWalkShot& walk,unsigned phase,unsigned frame,bool complete,bool grounded,
 int x,int z,float& speed,float& offset,float& movement,float elevation,unsigned rounds,
 bool boosted,BattleRandom& random,std::vector<GroundShotEffects>& requests){
 requests.clear();
 auto out=advance_keiichi_walk_shot(walk,state,phase,frame,complete,grounded,x,z,
  speed,offset,movement,elevation,rounds,false);
 if(out.next_state>=0)return out;
 const auto p=roster_walk_shot_profile(character,weapon,state);
 speed=(x||z||frame<p.stop_frame)?p.speed:0.f;
 out.fire=false;out.effect=-1;out.voice=-1;
 if(frame<p.first_fire||frame>p.last_fire||(frame-p.first_fire)%p.interval)return out;
 out.fire=true;out.effect=p.sound;out.voice=frame==p.first_fire?27:-1;
 const int low=state==410?-40:state==411?20:-100;
 const int high=state==410?40:state==411?100:-20;
 out.yaw=float(std::clamp(int(-offset),low,high));
 out.pitch=float(std::clamp(int(elevation),-40,40));
 unsigned count=p.count;
 if(boosted&&((character==4&&weapon==0)||(character==14&&weapon==1)))count=2;
 if(boosted&&character==10&&weapon==1)count=4;
 out.attack_calls=character==10?(weapon==1?2u:3u):count==2&&character!=6?2u:1u;
 for(unsigned n=0;n<count;++n){
  auto bullet=out;bullet.bullet_slot=n<p.count?p.bullets[n]:0;bullet.origin=p.origin;
  if(character==4||(character==14&&weapon==1)){
   bullet.origin=GroundShotOrigin::World;bullet.origin_height=70;
   if(character==14&&boosted)bullet.bullet_slot=2;
   bullet.world_forward_x=(state==410||boosted)?60.f:0.f;
   bullet.world_forward_z=60;
   if(boosted)bullet.world_lateral=n==0?40.f:-40.f;
  }else if(character==14){
   bullet.origin=GroundShotOrigin::World;bullet.origin_height=70;
   bullet.world_forward_x=bullet.world_forward_z=70;
   if(boosted)bullet.bullet_slot=3;
  }else if(character==10){
   bullet.origin=GroundShotOrigin::World;bullet.origin_height=125;
   bullet.world_forward_x=bullet.world_forward_z=100;
   if(weapon==0){
    bullet.bullet_slot=boosted?1u:16u;
    if(n==1){bullet.yaw-=4;bullet.world_yaw=-11;}
    if(n==2){bullet.yaw+=4;bullet.world_yaw=11;}
   }else if(weapon==1){
    bullet.bullet_slot=boosted?std::array<unsigned,4>{3,2,1,0}[n]:p.bullets[n];
    bullet.yaw+=n%2==0?25.f:-25.f;
   }else{
    bullet.bullet_slot=boosted?1u:0u;
    if(n==1)bullet.world_yaw=-15;
    if(n==2)bullet.world_yaw=15;
   }
  }else if(character==5){
   if(boosted)bullet.bullet_slot=2;
  }else if(character==7){
   if(boosted)bullet.bullet_slot=6;
  }else if(character==6){
   if(n==0){
    bullet.bullet_slot=boosted?6u:5u;
    if(state==410){
     bullet.pitch+=float(random.next()%6u)-3.f;
     bullet.yaw=float(random.next()%6u)-3.f;
    }
   }else {bullet.bullet_slot=7;bullet.yaw=bullet.pitch=0;}
  }
  requests.push_back(bullet);
 }
 out.bullet_slot=requests.front().bullet_slot;out.origin=requests.front().origin;
 return out;
}

}
