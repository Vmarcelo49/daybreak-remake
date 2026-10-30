#pragma once
#include "battle_magazine.hpp"
#include <array>
#include <cmath>
#include <cstring>
#include <functional>
#include <stdexcept>
#include <vector>
#include <type_traits>

namespace daybreak {
using uint=std::uint32_t;
using undefined4=std::int32_t;
inline float slot7_word_real(std::uint32_t word){float value;std::memcpy(&value,&word,4);return value;}
inline std::int32_t slot7_real_word(float value){std::int32_t word;std::memcpy(&word,&value,4);return word;}
inline std::int32_t slot7_word_add(std::int32_t value,std::int32_t delta){
 const auto word=std::uint32_t(value)+std::uint32_t(delta);std::int32_t result;std::memcpy(&result,&word,4);return result;
}
struct Slot7BodyContext;
struct Slot7NativeEvent{char kind=0;unsigned address=0;std::vector<std::int32_t> args;};
struct Slot7NativeServices{
 // State/upperState, activation notifications, voice delivery and paired throw
 // must finish before the next original source statement. Callbacks operate on
 // the bank, never native actor pointers. Closed State/pose services are reused.
 std::function<int(const Slot7NativeEvent&,Slot7BodyContext&)> invoke;
};
struct Slot7BodyContext{
 std::array<std::int32_t,0x2c00> w{};
 std::array<std::int32_t,0x2c00> partner{};
 std::vector<Slot7NativeEvent> events;
 const Slot7NativeServices& services;
 std::uint32_t frame_flags=0,contact=0;
 std::array<std::uint32_t,4> global_6cfb28{};
 int partner_token=1;
 explicit Slot7BodyContext(const Slot7NativeServices& value):services(value){}
 float real(unsigned offset)const{return slot7_word_real(unsigned(w.at(offset/4)));}
 float set_real(unsigned offset,float value){w.at(offset/4)=slot7_real_word(value);return value;}
 signed char byte(unsigned offset)const{return static_cast<signed char>(std::uint32_t(w.at(offset/4))>>((offset%4)*8));}
 short half(unsigned offset)const{return static_cast<short>(std::uint32_t(w.at(offset/4))>>((offset%4)*8));}
 void set_byte(unsigned offset,unsigned value){
  auto word=std::uint32_t(w.at(offset/4));const unsigned shift=(offset%4)*8;
  word=(word&~(255u<<shift))|((value&255u)<<shift);std::memcpy(&w.at(offset/4),&word,4);
 }
 int current_priority()const{
  const int state=w.at(0xadec/4);if(state<0||state>=1000)throw std::out_of_range("Slot7 current priority outside original table");
  return w.at((0x880+unsigned(state)*0x1c+4)/4);
 }
 int partner_word(int token,unsigned offset)const{
  if(token!=partner_token)throw std::out_of_range("Slot7 actor-owned ally reference missing");
  return partner.at(offset/4);
 }
 unsigned global_actor_word(unsigned tag)const{return global_6cfb28.at(tag);}
 signed char partner_byte(int token,unsigned offset)const{
  return static_cast<signed char>(std::uint32_t(partner_word(token,offset))>>((offset%4)*8));
 }
 template<class T>static std::int32_t raw(T value){
  if constexpr(std::is_floating_point_v<T>)return slot7_real_word(float(value));else return std::int32_t(value);
 }
 template<class...Args>int event(char kind,unsigned address,Args...args){
  events.push_back({kind,address,{raw(args)...}});const auto request=events.back();
  if(!services.invoke)throw std::logic_error("Slot7 synchronous world service not bound");
  return services.invoke(request,*this);
 }
 int slot7_ftol(unsigned offset,unsigned scalar){
  // Original D3D x87 precision is24 bits. FILD/FMUL rounds its product to
  // float precision before the truncating CRT call, despite no FSTP in RAW.
  volatile float product=float(w.at(offset/4))*slot7_word_real(scalar);
  return int(product);
 }
 void FUN_00421080(int state){event('N',0x421080,state);}
 void FUN_004211f0(int state){event('Y',0x4211f0,state);}
 void FUN_004220e0(){event('A',0x4220e0);w[0x83c/4]=w[0x330/4];set_byte(0x845,1);}
 void FUN_00422240(int id,int priority,int selector){event('V',0x422240,id,priority,selector);}
 void FUN_00422560(int tag,int id,int priority,int flag){event('v',0x422560,tag,id,priority,flag);}
 template<class...Args>int FUN_00422bd0(Args...args){return event('T',0x422bd0,args...);}
 void FUN_00422f40(){set_byte(0x2dc,0);event('Z',0x422f40);}
 unsigned FUN_0042c7b0(){event('R',0x42c7b0);return contact;}
 void FUN_00435560(int multiplier){
  if(multiplier>0)w[0x6d8/4]=w[0x71c/4]=multiplier;
 }
 unsigned FUN_0043f3e0(){
  BattleMagazine magazine;std::memcpy(&magazine,w.data()+0x708/4,sizeof magazine);
  const unsigned result=charge_battle_magazine(magazine);
  std::memcpy(w.data()+0x708/4,&magazine,sizeof magazine);return result;
 }
 int* FUN_00658a10(int index){
  if(index!=0)throw std::out_of_range("Slot7 unexpected actor-owned ally list index");
  event('P',0x658a10,index);return &partner_token;
 }
};
#if defined(DAYBREAK_COMPILED_NATIVE_BODIES)
void dispatch_slot7_body(Slot7BodyContext& n,unsigned ch,unsigned we);
#else
#include "slot7_native_bodies_20260929.hpp"
#endif
}
