#pragma once
#include "battle_magazine.hpp"
#include <array>
#include <vector>
#include <string>
#include <stdexcept>
namespace daybreak {
struct WeaponAttachmentData {
 // 433eb0/42fe90: second name is the sweep/trail texture, despite the old
 // exporter field name. position/rotation are its root and tip, not Euler angles.
 std::string model,animation;
 std::array<std::int32_t,3> socket_offset{},position{},rotation{};
};
struct WeaponBulletData {
 std::int32_t magazine_index=-1;
 std::uint32_t word04=0,file=0,variant=0;
 std::int32_t registration_id()const{return damage_signed(file*10u+variant);}
};
struct WeaponItemData {
 std::string label;std::array<std::uint32_t,2> reserved{};
 std::vector<WeaponAttachmentData> attachments;
 std::array<BattleMagazine,2> magazines;
 std::vector<WeaponBulletData> bullets;
 std::size_t consumed=0;
 std::vector<std::uint8_t> trailing; // Preserved exporter data beyond433eb0 reads.
};
// 433eb0 reads item DAT; names retain CP932 bytes. Rendering attachments is separate.
inline WeaponItemData read_weapon_item_data(const std::vector<std::uint8_t>& bytes){
 std::size_t pos=0;auto take=[&](std::size_t n){if(n>bytes.size()-pos)throw std::runtime_error("Truncated weapon item");auto p=bytes.data()+pos;pos+=n;return p;};
 auto word=[&](){auto p=take(4);return std::uint32_t(p[0])|(std::uint32_t(p[1])<<8)|(std::uint32_t(p[2])<<16)|(std::uint32_t(p[3])<<24);};
 auto integer=[&](){return damage_signed(word());};
 auto text=[&](){auto p=take(30);std::size_t n=0;while(n<30&&p[n])++n;return std::string(reinterpret_cast<const char*>(p),n);};
 WeaponItemData out;const auto objects=word(),bullets=word();
 out.label=text();for(auto& v:out.reserved)v=word();
 // Remaining fixed fields: two24-byte magazine records and16 bytes per bullet.
 if(objects>(bytes.size()-pos)/96u)throw std::runtime_error("Excessive weapon attachment count");
 for(unsigned i=0;i<objects;++i){WeaponAttachmentData a;a.model=text();a.animation=text();for(auto* values:{&a.socket_offset,&a.position,&a.rotation})for(auto& v:*values)v=integer();out.attachments.push_back(std::move(a));}
 for(auto& m:out.magazines){
  m.capacity=word();m.rounds=m.capacity;m.mode=word();m.reload_threshold=word();m.shot_interval=word();m.cooldown=m.shot_interval;
  m.word24=word();m.word2c=word();
  if(m.mode==0)m.display=m.word34=m.capacity;
  else if(m.mode==1||m.mode==2)m.display=m.word34=m.capacity*m.reload_threshold;
 }
 if(bullets>(bytes.size()-pos)/16u)throw std::runtime_error("Excessive weapon bullet count");
 for(unsigned i=0;i<bullets;++i){WeaponBulletData b;b.magazine_index=integer();b.word04=word();b.file=word();b.variant=word();out.bullets.push_back(b);}
 out.consumed=pos;out.trailing.assign(bytes.begin()+pos,bytes.end());return out;
}
}
