#pragma once
#include "legacy_battle_snapshot.hpp"
#include "legacy_battle_event_codec.hpp"
#include <utility>
namespace daybreak {
//640EA0 common four-actor host producer, independent of character/weapon.
//Values are the raw actor fields, not HUD percentages or rendered poses.
struct LegacyHostMirrorActor {
 LegacySnapshotActor snapshot;
 std::array<std::int32_t,2> weapon{};
 std::uint8_t trail=0,mode=0,command=0;
 std::int32_t stop=0,invincible=0,opponent=0,ally=0;
 std::array<float,4> pose{};float pivot=0;
 std::array<std::int32_t,9> status{};
 std::int32_t health=0,movement=0,contact=0;
 std::array<std::int32_t,3> charge{};
 std::array<std::int32_t,2> magazines{},charge_progress{};
 bool manual=false;float manual_pitch=0;
};
struct LegacyHostMirrorState {
 std::uint32_t tick=0;std::array<LegacyHostMirrorActor,4> actors{};
 std::array<std::int32_t,2> balloons{};
};
struct LegacyHostMirrorPeer {bool connected=false;std::uint8_t actor=255;};
struct LegacyHostMirrorMessage {
 unsigned recipient=0,timeout=0,flags=0;std::vector<std::uint8_t> wire;
 //0 means broadcast. These are original call flags BEFORE the wrapper adds
 //DPNSEND_NOLOOPBACK.88=GUARANTEED|HIGH,42=NOCOMPLETE|LOW,2=NOCOMPLETE.
};
class LegacyHostBattleMirror {
 struct ActorCache {
  std::array<std::int32_t,2> weapon{};std::uint8_t trail=0;
  std::int32_t stop=0,opponent=0,ally=0;
  std::uint16_t invincible=0;std::array<std::uint16_t,9> status{};
  std::array<float,4> pose{};float pivot=0;
  std::array<std::int32_t,4> health{};
  std::uint16_t special=0,movement=0,contact=0,command=0;
  std::array<std::uint16_t,2> magazines{},charge_progress{};
 };
 std::array<ActorCache,4> cache_{};
 static int signed16(std::uint16_t n){return n<32768?int(n):int(n)-65536;}
 static int signed8(std::uint8_t n){return n<128?int(n):int(n)-256;}
 static int selected_charge(const LegacyHostMirrorActor& a){return a.charge[a.mode==1?1:a.mode==2?2:0];}
 bool collect_impl(const LegacyHostMirrorState& s,const std::array<LegacyHostMirrorPeer,8>& peers,
                   LegacySnapshotPrecision precision,std::vector<LegacyHostMirrorMessage>& out){
  LegacyBattleSnapshot snapshot;snapshot.tick=s.tick;
  for(unsigned i=0;i<4;++i)snapshot.actors[i]=s.actors[i].snapshot;
  snapshot.kind=select_legacy_snapshot_kind(snapshot.actors);
  std::array<std::uint8_t,93> encoded{};std::size_t length=0;
  if(!encode_legacy_snapshot(snapshot,precision,encoded,length))return false;
  out.push_back({0,0x30,0x88,{encoded.begin(),encoded.begin()+length}});
  auto send=[&](LegacyBattleEvent event,unsigned recipient,unsigned timeout,unsigned flags){
   LegacyHostMirrorMessage m{recipient,timeout,flags,{}};
   if(!encode_legacy_battle_event(event,m.wire,precision==LegacySnapshotPrecision::single?24:53))return false;
   out.push_back(std::move(m));return true;
  };
  auto packet=[](unsigned tag){LegacyBattleEvent p;p.tag=std::uint8_t(tag);return p;};
  for(unsigned i=0;i<4;++i){const auto& a=s.actors[i];auto& c=cache_[i];
   if(c.weapon!=a.weapon||c.trail!=a.trail){c.weapon=a.weapon;c.trail=a.trail;
    auto p=packet(0x26);p.put(8,i);p.put(12,a.weapon[0]);p.put(16,a.weapon[1]);p.put(20,a.trail,1);if(!send(p,0,0,8))return false;}
   if(c.stop<a.stop){auto p=packet(0x27);p.put(8,i);p.put(12,a.stop);if(!send(p,0,0,8))return false;}c.stop=a.stop;
   if(signed16(c.invincible)<a.invincible){auto p=packet(0x29);p.put(8,i);p.put(12,a.invincible,2);if(!send(p,0,0,8))return false;}c.invincible=std::uint16_t(a.invincible);
   if(c.opponent!=a.opponent){c.opponent=a.opponent;auto p=packet(0x2a);p.put(8,i);p.put(12,a.opponent);if(!send(p,0,0,0x88))return false;}
   if(c.ally!=a.ally){c.ally=a.ally;auto p=packet(0x2b);p.put(8,i);p.put(12,a.ally);if(!send(p,0,0,0x88))return false;}
   bool pose_changed=false;
   //Native FUCOMPP/TEST C0,C2,C3 treats unordered as unequal.
   for(unsigned j=0;j<4;++j)pose_changed|=c.pose[j]!=a.pose[j];
   if(pose_changed){c.pose=a.pose;c.pivot=a.pivot;auto p=packet(0x1a);p.put(8,i,1);
    for(unsigned j=0;j<4;++j)p.real(12+4*j,a.pose[j]);p.real(28,a.pivot);if(!send(p,0,0,8))return false;}
   for(unsigned j=0;j<9;++j){const int old=signed16(c.status[j]),next=a.status[j];
    if(old<next||(old>2&&next==0)){auto p=packet(0x1e);p.put(8,i,1);p.put(9,j,1);p.put(10,next,2);if(!send(p,0,0,8))return false;}c.status[j]=std::uint16_t(next);}
  }
  for(unsigned i=0;i<4;++i){const auto& a=s.actors[i];auto& c=cache_[i];std::vector<unsigned> recipients;
   for(unsigned n=1;n<8;++n)if(peers[n].connected&&signed8(peers[n].actor)==int(i))recipients.push_back(n);
   if(recipients.empty())continue; //Target-only caches freeze without a peer.
   auto each=[&](const LegacyBattleEvent& p,unsigned timeout,unsigned flags){for(auto recipient:recipients)if(!send(p,recipient,timeout,flags))return false;return true;};
   if(s.tick&1u){bool changed=false;for(unsigned j=0;j<4;++j){changed|=c.health[j]!=s.actors[j].health;c.health[j]=s.actors[j].health;}
    const auto special=selected_charge(a);changed|=signed16(c.special)!=special;c.special=std::uint16_t(special);
    if(changed){auto p=packet(0x1c);for(unsigned j=0;j<4;++j)p.put(8+4*j,c.health[j]);p.put(24,c.special,2);if(!each(p,0,8))return false;}
    if(signed16(c.movement)!=a.movement){c.movement=std::uint16_t(a.movement);auto p=packet(0x1d);p.put(8,c.movement,2);if(!each(p,0,signed16(c.movement)==1000?8:0x42))return false;}
   }
   if(signed16(c.contact)!=a.contact){c.contact=std::uint16_t(a.contact);auto p=packet(0x2c);p.put(8,c.contact,2);if(!each(p,0,0x88))return false;}
   if(signed16(c.command)!=signed8(a.command)){c.command=std::uint16_t(signed8(a.command));auto p=packet(0x2d);p.put(8,c.command,2);if(!each(p,0,0x88))return false;}
   if(signed16(c.magazines[0])!=a.magazines[0]||signed16(c.magazines[1])!=a.magazines[1]){
    auto p=packet(0x2e);for(unsigned j=0;j<2;++j){c.magazines[j]=std::uint16_t(a.magazines[j]);p.put(8+2*j,c.magazines[j],2);}if(!each(p,0,8))return false;}
   if(signed16(c.charge_progress[0])!=a.charge_progress[0]||signed16(c.charge_progress[1])!=a.charge_progress[1]){
    auto p=packet(0x2f);for(unsigned j=0;j<2;++j){c.charge_progress[j]=std::uint16_t(a.charge_progress[j]);p.put(8+2*j,c.charge_progress[j],2);}
    const bool zero=c.charge_progress[0]==0||c.charge_progress[1]==0;if(!each(p,zero?0:5,zero?8:0x42))return false;}
   if(a.manual){auto p=packet(0x23);p.real(8,a.manual_pitch);if(!each(p,5,2))return false;}
  }
  if(legacy_snapshot_signed(s.tick)%60!=0){auto p=packet(0x30);p.put(8,s.balloons[0],2);p.put(10,s.balloons[1],2);if(!send(p,0,0,8))return false;}
  return true;
 }
public:
 //642060 copies current fields after all actors initialize. It intentionally
 //does NOT reset cached pose[3] (+68), even between rounds. Default zero is
 //only the cleared-scene audit fixture, not a claim about packet constructors.
 void prime(const LegacyHostMirrorState& s){
  for(unsigned i=0;i<4;++i){const auto& a=s.actors[i];auto& c=cache_[i];
   c.weapon=a.weapon;c.trail=a.trail;c.stop=a.stop;c.invincible=std::uint16_t(a.invincible);c.opponent=a.opponent;c.ally=a.ally;
   for(unsigned j=0;j<3;++j)c.pose[j]=a.pose[j];c.pivot=a.pivot;
   for(unsigned j=0;j<9;++j)c.status[j]=std::uint16_t(a.status[j]);
   for(unsigned j=0;j<4;++j)c.health[j]=s.actors[j].health;
   //Initialization selects838 only for mode0,840 for2,83C otherwise.
   c.special=std::uint16_t(a.charge[a.mode==0?0:a.mode==2?2:1]);c.movement=std::uint16_t(a.movement);c.contact=std::uint16_t(a.contact);c.command=std::uint16_t(signed8(a.command));
   for(unsigned j=0;j<2;++j){c.magazines[j]=std::uint16_t(a.magazines[j]);c.charge_progress[j]=std::uint16_t(a.charge_progress[j]);}
  }
 }
 //Prepare transactionally: invalid encoding never commits an unsent cache.
 bool collect(const LegacyHostMirrorState& s,const std::array<LegacyHostMirrorPeer,8>& peers,
              LegacySnapshotPrecision precision,std::vector<LegacyHostMirrorMessage>& out){
  auto next=*this;std::vector<LegacyHostMirrorMessage> prepared;
  if(!next.collect_impl(s,peers,precision,prepared))return false;*this=next;out=std::move(prepared);return true;
 }
};
}
