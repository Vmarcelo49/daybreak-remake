#pragma once
#include "jump_native_control.hpp"
#include "battle_steering.hpp"
#include <type_traits>

namespace daybreak {
struct SharedRecoveryEvent {
 char kind=0;unsigned address=0;std::vector<std::int32_t> args;
};
struct SharedRecoveryContext {
 std::array<std::int32_t,0x2be0> w{};
 int duration=0,hold=0;bool complete=false;unsigned scratch_written=0;
 std::vector<SharedRecoveryEvent> events;
 explicit SharedRecoveryContext(int ticks,int held,bool done):duration(ticks),hold(held),complete(done){}
 template<class T> static std::int32_t raw(T value){
  if constexpr(std::is_floating_point_v<T>)return remaining_bits(float(value));
  else return std::int32_t(value);
 }
 template<class... Args> void emit(char kind,unsigned address,Args... args){events.push_back({kind,address,{raw(args)...}});}
 void clock_event(char kind,unsigned address,int value=-1){
  SharedRecoveryEvent e{kind,address,{}};
  if(kind!='I')e.args.push_back(value);
  for(auto index:{0x2b7b,0x2b7d,0x2b81,0x2b82,0x2b7f})e.args.push_back(w[index]);
  events.push_back(std::move(e));
 }
 int write_scratch(unsigned index,int value){scratch_written|=1u<<(index-0x3a);w.at(index)=value;return value;}
 char byte(unsigned offset)const{return char(std::uint32_t(w.at(offset/4))>>((offset%4)*8));}
 void FUN_00421080(int state){
  clock_event('N',0x421080,state);
  w[0xb]=w[0xc]=w[0xd]=0;w[0x1a1]=-1;w[0x2b7b]=w[0x2b7c]=state;
  FUN_00421100(0);
 }
 void FUN_00421100(int phase){
  clock_event('H',0x421100,phase);
  w[0x2b7d]=w[0x2b7e]=phase;w[0x2b7f]=w[0x2b81]=w[0x2b82]=0;
 }
 void FUN_004212f0(){clock_event('I',0x4212f0);}
 int FUN_004218c0(){emit('C',0x4218c0,int(complete));return complete;}
 void FUN_00421780(){
  emit('T',0x421780,w[0x2b7b],w[0x2b7d],w[0x2b81],w[0x2b82],w[0x2b7f],w[0x17],w[0x19],w[0x21d],w[0x9e],w[0x9f]);
  float offset=remaining_real(unsigned(w[0x19]));
  steer_battle_offset(offset,w[0x9e],w[0x9f],remaining_real(unsigned(w[0x21d])));
  w[0x19]=remaining_bits(offset);
 }
 void FUN_00434a70(int index,int model){emit('M',0x434a70,index,model);}
 void FUN_00434bd0(){emit('L',0x434bd0);}
 template<class... Args> void FUN_00435450(Args... args){emit('W',0x435450,args...);}
 void FUN_00422300(int id,int choice,int priority,int channel){emit('V',0x422300,id,choice,priority,channel);}
 void FUN_0042c8b0(int value){emit('E',0x42c8b0,value);}
 void FUN_004230e0(){emit('J',0x4230e0,1);}
 template<class T,class... Args> float FUN_0065d010(T angle,Args...){return legacy_trig(remaining_real(unsigned(raw(angle))),true);}
 template<class T,class... Args> float FUN_0065d050(T angle,Args...){return legacy_trig(remaining_real(unsigned(raw(angle))),false);}
};
#include "shared_recovery_bodies_20261004.hpp"
inline bool shared_recovery_body_state(unsigned character,unsigned state,bool){
 return state==124||state==128||state==187||state==190||(state==186&&character==3);
}
}
