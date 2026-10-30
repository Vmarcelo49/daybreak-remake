#pragma once
#include <array>
#include <cstdint>
#include <stdexcept>
namespace daybreak {
// 472b00 / 47ae30 / 4840d0. CPU writes legacy counters directly, not key states.
struct KeiichiCpuInput {
 int x=0,z=0; //278/27c persist unless a branch overwrites them
 std::array<int,3> held{}; //280 jump,284 melee,288 shoot
 std::array<int,3> released{}; //2b0/2b4/2b8
 int target=0,dash=0; //28c/830
 //41efe0/slot5 retains290/294/298/29c at HUMAN-to-CPU takeover.
 //Slot7 can write290;6352xx phase gates clear all ten acquired words.
 std::array<std::uint32_t,4> auxiliary{};
};
struct KeiichiCpuState {int lateral=0,forward=0,jump=0,charge=0;}; //864..870
struct KeiichiCpuContext {
 unsigned weapon=0;int command=0,action=0,gauge=0;
 bool grounded=false,special844=false,special845=false;
 int threshold324=0,timer838=0,threshold32c=0,timer83c=0;
 float obstacle_distance=10000,distance_squared=0; //42cc90 /42d980 results
 unsigned target_index=0,ally_target_index=0;
 bool nearest_target_request=false; //421c80 output; target mutation happens later
};
//421c80 ignores vertical distance and prefers the sole opponent with7ac==0.
inline bool cpu_nearest_target_request(unsigned current,int cooldown,
 const std::array<float,2>& horizontal_squared,const std::array<int,2>& timer7ac){
 if(cooldown!=0)return false;
 unsigned wanted;
 if(timer7ac[0]!=0&&timer7ac[1]==0)wanted=1;
 else if(timer7ac[1]!=0&&timer7ac[0]==0)wanted=0;
 else wanted=horizontal_squared[1]<horizontal_squared[0]?1u:0u;
 return current!=wanted;
}
// The host must refresh obstacle_distance before calling (42cc90). Preserve RNG
// short-circuit order, including draws whose command predicate is checked later.
template<class Random> void advance_keiichi_cpu(KeiichiCpuState& s,KeiichiCpuInput& out,const KeiichiCpuContext& c,Random& random){
 if(c.weapon>2)throw std::invalid_argument("Unsupported Keiichi CPU weapon");
 out.dash=0;out.target=0;out.held.fill(0);out.released.fill(0);
 float range_scale=1;unsigned shooting=100,melee=100;
 switch(c.command){
 case 0:out.target=c.nearest_target_request;break;
 case 1:out.target=c.nearest_target_request;range_scale=.25f;shooting=50;melee=200;break;
 case 2:out.target=c.nearest_target_request;range_scale=c.weapon==1?3.f:3.5f;shooting=200;melee=50;break;
 case 3:out.target=c.target_index!=c.ally_target_index;break;
 case 4:out.target=c.target_index==c.ally_target_index;break;
 case 5:out.target=c.nearest_target_request;range_scale=7;shooting=5;melee=5;break;
 }
 if((!c.special845&&c.threshold32c<=c.timer83c&&(c.action<100||c.action>299))||
    (!c.special844&&c.threshold324<=c.timer838&&c.action<300)){
  out.held[1]=out.held[2]=1;return;
 }
 auto roll=[&](unsigned divisor){return random.next()%divisor;};
 const auto d=c.distance_squared;
 if(c.grounded&&s.jump==0&&c.gauge>650&&d>40000&&roll(100)==1)s.jump=int(roll(120))+10;
 if(c.grounded&&c.obstacle_distance<=300&&c.gauge>650&&d>250000&&roll(100)<10)s.jump=int(roll(120))+60;
 if(s.charge==0&&roll(400)==0)s.charge=int(roll(180))+180;
 if(s.charge==0&&(roll(c.weapon==1?150:200)==0||(roll(c.weapon==1?125:150)==0&&c.command==2)))s.charge=int(roll(180));
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
 const float range=(c.weapon==1?422500.f:250000.f)*range_scale*range_scale;
 if(s.forward>0){
  --s.forward;out.z=-1;
  if(roll(300)<(c.command==5?10u:1u)&&s.jump<1&&out.dash==0)out.dash=1;
  if(roll(300)<(c.command==5?36u:12u)&&c.gauge>500&&d>range&&s.jump<1&&out.dash==0)out.dash=1;
 }else if(s.forward<0){
  ++s.forward;out.z=1;
  if(roll(400)<(c.command==5?3u:1u)&&s.jump<1&&out.dash==0)out.dash=2;
 }else s.forward=int(roll(300))-(range<=d?60:240);
 if(s.jump>0){out.held[0]=c.grounded?3:4;--s.jump;}
 if(c.grounded&&c.action!=40&&c.action!=41)s.jump=0;
 if(d<250000&&roll(100)<melee){
  if((roll(2500)==0||(roll(1250)==0&&c.command==1))&&d<40000){out.released[1]=out.released[2]=out.held[1]=out.held[2]=1;return;}
  if((roll(50)==0||(roll(25)==0&&c.command==1))&&d<250000){out.x=out.z=0;out.released[1]=1;return;}
  if((roll(50)==0||(roll(25)==0&&c.command==1))&&d<202500){out.x=0;out.z=-1;out.released[1]=1;return;}
  if((roll(50)==0||(roll(25)==0&&c.command==1))&&d<122500){out.z=0;out.x=1;out.released[1]=1;return;}
 }
 if(roll(100)<shooting){
  const float obstacle_squared=c.obstacle_distance*c.obstacle_distance;
  if((roll(200)==0||(roll(150)==0&&c.command==2))&&d<obstacle_squared){out.released[2]=1;s.charge=0;}
  if(roll(125)!=0){if(roll(110)!=0)return;if(c.command!=2)return;}
  if(d<2250000&&obstacle_squared>d){out.released[2]=1;s.charge=0;}
 }
}
}
