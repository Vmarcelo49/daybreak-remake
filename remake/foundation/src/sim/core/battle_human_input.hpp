#pragma once
#include "battle_input_channel.hpp"
#include "battle_input_buttons.hpp"
#include "controller_state.hpp"
#include "battle_phase_services.hpp"
#include "keiichi_cpu.hpp"
#include <algorithm>
namespace daybreak {
inline net::Input merge_battle_human_inputs(net::Input input,const net::Input& extra){
 if((input.buttons|extra.buttons)&battle_physical_tag){
  const auto raw=battle_physical_buttons(input.buttons)|battle_physical_buttons(extra.buttons);
  input.buttons=battle_button_carrier(raw,((input.buttons|extra.buttons)&32)!=0);
 }else input.buttons|=extra.buttons;
 if(extra.x)input.x=extra.x;if(extra.z)input.z=extra.z;return input;
}
//41efe0 polls the actor's own +240 controller. Max-combined primary counts
// are written back into that same bank, including status/scene/body clears.
struct BattleHumanInput {
 LegacyControllerState controller;
 std::array<std::uint32_t,4> released{};
 BattleHumanInput(){controller.words[24]=1;}
 std::uint32_t held(unsigned button)const{return controller.words.at(16+button);}
 std::int32_t x()const{return controller_signed(controller.words[14]);}
 std::int32_t z()const{return controller_signed(controller.words[15]);}
 unsigned buttons()const{
  const auto& w=controller.words;const bool jump=w[16]!=0,melee=w[17]!=0;
  return unsigned(melee)|(unsigned(jump)<<1)|(unsigned(jump&&melee)<<2)|
   (unsigned(w[19]!=0)<<3)|(unsigned(w[18]!=0)<<4)|(unsigned(w[22]==1)<<5);
 }
 void acquire(const net::Input& input,bool attack_status){
  auto& w=controller.words;const std::array<std::uint32_t,4> previous{{w[16],w[17],w[18],w[19]}};
  w[13]=(battle_physical_buttons(input.buttons)<<4)|
   (input.x<0?4u:input.x>0?8u:0u)|(input.z<0?1u:input.z>0?2u:0u);
  poll_legacy_controller(controller,{});
  w[16]=std::max(w[16],w[21]);w[17]=std::max({w[17],w[20],w[21]});w[18]=std::max(w[18],w[20]);
  for(unsigned b=0;b<4;++b)released[b]=previous[b]&&w[16+b]==0?previous[b]:0;
  if(attack_status){w[17]=w[18]=released[1]=released[2]=0;}
 }
 //CPU owns the same acquired bank;657390 is skipped, not a zero poll.
 void acquire_cpu(const KeiichiCpuInput& input){
  auto& w=controller.words;w[14]=std::uint32_t(input.x);w[15]=std::uint32_t(input.z);
  for(unsigned b=0;b<3;++b){w[16+b]=std::uint32_t(input.held[b]);released[b]=std::uint32_t(input.released[b]);}
  w[19]=std::uint32_t(input.target);
  for(unsigned b=0;b<4;++b)w[20+b]=input.auxiliary[b];
 }
 //41efe0 clears BOTH previous and current ten-word banks during local IME.
 // An ordinary zero poll would release the previously held shooting button.
 void suppress_chat(){std::fill(controller.words.begin()+14,controller.words.begin()+24,0);released.fill(0);}
 void gate(const BattlePhaseAdmission& admission,unsigned actor){
  if(!admission.blocks_commands(actor))return;
  auto& w=controller.words;const auto target=w[19],command=w[22];
  std::fill(w.begin()+14,w.begin()+24,0);released.fill(0);
  if(admission.phase==1){w[19]=target;w[22]=command;}
 }
 void body_counters(unsigned jump,unsigned melee,unsigned shoot,unsigned chord){
  auto& w=controller.words;w[16]=jump;w[17]=melee;w[18]=shoot;w[20]=chord;
 }
};
}
