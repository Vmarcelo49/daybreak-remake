#pragma once
#include "shoot_native_control.hpp"
#include "full_charge_aim.hpp"
namespace daybreak {
struct FullChargeMissingVictim:std::logic_error{FullChargeMissingVictim():std::logic_error("Original full-charge victim receiver is null") {}};
struct FullChargeNativeMotion:ShootNativeMotion{float manual_aim=0;int manual_aim_flag=0,bone_token=0,pair_token=0;};
struct FullChargeNativeEffects:ShootNativeEffects{bool victim_recovered=false;};
struct FullChargeBodyContext:ShootBodyContext{
 using ShootBodyContext::ShootBodyContext;
 template<class... Args> void FUN_00422300(Args... args){event('V',0x422300,args...);}
 void FUN_00423530(const char* name){
  out.events.push_back({'G',0x423530,{},name});const auto request=out.events.back();
  if(!services.invoke)throw std::logic_error("Full-charge capture bone service missing");w[0xaed4/4]=services.invoke(request,*this);
 }
 void FUN_00422ab0(int state,int damage,int scaling,const char* bone){
  out.events.push_back({'T',0x422ab0,{state,damage,scaling},bone?bone:""});const auto request=out.events.back();
  if(!services.invoke)throw std::logic_error("Full-charge held-damage service missing");services.invoke(request,*this);
 }
 void FUN_00422ed0(){w[0x2dc/4]=(w[0x2dc/4]&~255)|1;event('Z',0x422ed0);}
 int FUN_0066b65c(int argument){return argument<0?-argument:argument;} // Original integer abs, not FTOL.
 template<class Target,class Step> void FUN_0042db10(Target target,Step step){ShootBodyContext::FUN_0042db10(raw(target),raw(step));}
 void victim_state(int state){if(!w[0xaed0/4])throw FullChargeMissingVictim();event('n',0x421080,state);}
 void natsumi_capture_particle(){
  volatile float heading=remaining_real(unsigned(w[0x5c/4]));volatile float angle=heading+remaining_real(unsigned(w[0x64/4]));
  volatile float dx=legacy_trig(angle,false)*60.f,dz=legacy_trig(angle,true)*60.f;
  volatile float x=remaining_real(unsigned(w[0x14/4]))+dx,z=remaining_real(unsigned(w[0x1c/4]))+dz;
  event('P',0x100e100,30,x,remaining_real(unsigned(w[0x18/4])),z,heading,0.f);
 }
};
#if defined(DAYBREAK_COMPILED_NATIVE_BODIES)
bool full_charge_native_body_binding(unsigned ch,unsigned we,unsigned state);
void dispatch_full_charge_body(FullChargeBodyContext& n,unsigned ch,unsigned we,unsigned state);
#else
#include "full_charge_native_bodies_20260929.hpp"
#endif
#include "full_charge_native_advance.inc.hpp"
}
