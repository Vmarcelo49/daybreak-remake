#pragma once
namespace daybreak {
struct MionChargeAdmission { int state=-1; bool full_charge=false; };
//45f4d0/467d70/456030 charge-release branches. This is the charge branch
//only: callers must preserve earlier chord priority and later normal fallback.
template<class Priority> MionChargeAdmission mion_charge_admission(unsigned weapon,
 int current,int phase,bool grounded,int release,int stage,int rounds,int priority,Priority first){
 if(release<=0||rounds<=0||(current>=100&&current<=299))return {};
 if(stage==2){const int next=grounded?350:360;return priority<=first(next)?MionChargeAdmission{next,true}:MionChargeAdmission{};}
 if(stage!=1)return {};
 if(!grounded)return priority<=first(460)?MionChargeAdmission{460,false}:MionChargeAdmission{};
 if(priority>first(450))return {};
 if(weapon==0&&phase<2){
  if(current==20)return {454,false};
  if(current==23)return {451,false};
  if(current==24)return {452,false};
  if(current==27)return {453,false};
 }
 return {450,false};
}
}
