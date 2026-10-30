#pragma once
#include "keiichi_cpu.hpp"
namespace daybreak {
//460d90 /4696d0 /4577e0. Shared legacy CPU counters; Mion-specific policy.
template<class Random> void advance_mion_cpu(KeiichiCpuState& s,KeiichiCpuInput& out,const KeiichiCpuContext& c,Random& random){
 if(c.weapon>2)throw std::invalid_argument("Unsupported Mion CPU weapon");
 out.dash=0;out.target=0;out.held.fill(0);out.released.fill(0);
 float range_scale=1;unsigned shooting=100,melee=100;
 switch(c.command){
 case 0:out.target=c.nearest_target_request;break;
 case 1:out.target=c.nearest_target_request;range_scale=.25f;shooting=50;melee=200;break;
 case 2:out.target=c.nearest_target_request;range_scale=1.5f;shooting=200;melee=c.weapon==0?50:25;break;
 case 3:out.target=c.target_index!=c.ally_target_index;break;
 case 4:out.target=c.target_index==c.ally_target_index;break;
 case 5:out.target=c.nearest_target_request;range_scale=3;shooting=5;melee=5;break;
 }
 if((!c.special845&&c.threshold32c<=c.timer83c&&(c.action<100||c.action>299))||
    (!c.special844&&c.threshold324<=c.timer838&&c.action<300)){
  out.held[1]=out.held[2]=1;return;
 }
 auto roll=[&](unsigned divisor){return random.next()%divisor;};
 const auto d=c.distance_squared;
 if(c.grounded&&s.jump==0&&c.gauge>650&&d>40000&&roll(100)==1)s.jump=int(roll(120))+10;
 if(c.grounded&&c.obstacle_distance<=300&&c.gauge>650&&d>250000&&roll(100)<10)s.jump=int(roll(120))+60;
 if(s.charge==0&&(c.weapon==0?roll(500)==0:((roll(500)==0||(roll(450)==0&&c.command==2))&&d>1000000)))s.charge=int(roll(180))+180;
 if(s.charge==0&&(roll(c.weapon==0?100:200)==0||(roll(c.weapon==0?85:150)==0&&c.command==2)))s.charge=int(roll(180));
 if(s.charge>0){--s.charge;out.held[2]=4;}
 const unsigned side_chance=(c.command==5?4u:1u)*10;
 if(s.lateral>0){
  --s.lateral;out.x=1;
  if(roll(100)<side_chance&&s.jump<1)out.dash=4;
  if(roll(100)<side_chance&&c.gauge>500&&s.jump<1)out.dash=4;
 }else if(s.lateral<0){
  ++s.lateral;out.x=-1;
  if(roll(100)<side_chance&&s.jump<1)out.dash=3;
  if(roll(100)<side_chance&&c.gauge>500&&s.jump<1)out.dash=3;
 }else if(roll(100)==0)s.lateral=int(roll(400))-200;
 const float range=(c.weapon==0?1000000.f:360000.f)*range_scale*range_scale;
 if(s.forward>0){
  --s.forward;out.z=-1;
  if(roll(500)<(c.command==5?10u:1u)&&s.jump<1&&out.dash==0)out.dash=1;
  if(roll(500)<(c.command==5?30u:10u)&&c.gauge>500&&d>(c.weapon==0?2250000.f:1000000.f)*range_scale*range_scale&&s.jump<1&&out.dash==0)out.dash=1;
 }else if(s.forward<0){
  ++s.forward;out.z=1;
  if(roll(250)<(c.command==5?3u:1u)&&s.jump<1&&out.dash==0)out.dash=2;
 }else s.forward=int(roll(300))-(range<=d?60:240);
 if(s.jump>0){out.held[0]=c.grounded?3:4;--s.jump;}
 if(c.grounded&&c.action!=40&&c.action!=41)s.jump=0;
 if(d<160000&&roll(100)<melee){
  if((roll(100)==0||(roll(75)==0&&c.command==1))&&d<90000){out.x=out.z=0;out.released[1]=1;return;}
  if(roll(100)==0||(roll(75)==0&&c.command==1)){out.x=0;out.z=-1;out.released[1]=1;return;}
  if((roll(100)==0||(roll(75)==0&&c.command==1))&&d<90000){out.z=0;out.x=1;out.released[1]=1;return;}
 }
 if(roll(100)<shooting){
  const float obstacle_squared=c.obstacle_distance*c.obstacle_distance;
  if((roll(c.weapon==0?100:125)==0||(roll(c.weapon==0?75:100)==0&&c.command==2))&&d<obstacle_squared&&(c.weapon==0||d<1000000)){out.released[2]=1;s.charge=0;}
  if(roll(c.weapon==0?60:150)!=0){if(roll(c.weapon==0?50:125)!=0)return;if(c.command!=2)return;}
  if((c.weapon!=0||d>1000000)&&obstacle_squared>d){out.released[2]=1;s.charge=0;}
 }
}
}
