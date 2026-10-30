#pragma once
#include <array>
#include <stdexcept>
namespace daybreak {
enum class BattleSoundMode : unsigned {Plain=0,Spatial=1};
//64ae70 uses the request byte AND the master's54e0 setting.
inline BattleSoundMode resolve_battle_sound_mode(BattleSoundMode mode,bool spatial_enabled){return unsigned(mode)!=0&&spatial_enabled?BattleSoundMode::Spatial:BattleSoundMode::Plain;}
inline BattleSoundMode native_battle_sound_mode(unsigned service){
 if(service==0x42c880)return BattleSoundMode::Plain;
 if(service==0x42c8b0)return BattleSoundMode::Spatial;
 throw std::invalid_argument("Unknown actor sound service identity");
}
//65a260 is called with ECX=6d1a50. Its +3e0/+3e4 cursors are shared
// across all sound resources, rather than stored in each sound resource.
class BattleSoundRing {
 std::array<unsigned,2> next_{};
public:
 static constexpr unsigned size=32;
 unsigned next(BattleSoundMode mode)const{return next_.at(unsigned(mode));}
 void played(BattleSoundMode mode){auto& slot=next_.at(unsigned(mode));slot=(slot+1)%size;}
};
inline constexpr unsigned battle_sound_buffer_bytes=0x80000;
}
