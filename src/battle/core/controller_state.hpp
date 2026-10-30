#pragma once
#include <array>
#include <cstdint>
#include <cstring>
#include <stdexcept>
namespace daybreak {
// Original controller object (100 bytes). +0 device is signed byte: -1 keyboard,
// other negative values disabled; +0x60 selects the packed-input path.
struct LegacyControllerState {std::array<std::uint32_t,25> words{};};
//643230 checks controller+1, copied from the52-byte binding record by657330.
inline bool controller_shows_self_hud(const LegacyControllerState& state){return (state.words[0]&0xff00u)!=0;}
struct ControllerDeviceSnapshot {
    std::array<std::uint8_t,256> keyboard{};
    std::int32_t x=0,y=0;
    std::array<std::uint8_t,32> buttons{};
};
inline std::int32_t controller_signed(std::uint32_t bits){std::int32_t result;std::memcpy(&result,&bits,4);return result;}
// 0x657330: config.dat stores four consecutive 52-byte binding records. Applying
// one resets counters but preserves packed input and the network-mode flag.
inline void configure_legacy_controller(LegacyControllerState& state,const std::array<std::uint32_t,13>& bindings,std::uint8_t device_count){
    for(unsigned i=0;i<13;++i)state.words[i]=bindings[i];
    int device=int(state.words[0]&255);if(device>=128)device-=256;
    if(device>=device_count){for(unsigned i=0;i<13;++i)state.words[i]=0;state.words[0]=254;}
    for(unsigned i=14;i<24;++i)state.words[i]=0;
}
// 0x657390 after the OS snapshot has been read. Unsigned operations intentionally
// preserve x86 counter wraparound, including the signed axis direction checks.
inline void poll_legacy_controller(LegacyControllerState& state,const ControllerDeviceSnapshot& input){
    auto& w=state.words;
    auto axis=[&](unsigned index,bool negative,bool positive){
        if(negative){if(controller_signed(w[index])>0)w[index]=0;--w[index];}
        else if(positive){if(controller_signed(w[index])<0)w[index]=0;++w[index];}
        else w[index]=0;
    };
    auto button=[&](unsigned index,bool held){w[index]=held?w[index]+1:0;};
    if(w[24]&255){
        axis(14,w[13]&4,w[13]&8);axis(15,w[13]&1,w[13]&2);
        for(unsigned i=0;i<8;++i)button(16+i,w[13]&(16u<<i));
        return;
    }
    int device=int(w[0]&255);if(device>=128)device-=256;
    if(device<0 && device!=-1){for(unsigned i=14;i<24;++i)w[i]=0;return;}
    if(device==-1){
        // Missing/unsupported scan codes are unbound. In particular, a stale
        // keyboard mapping must not prevent a controller profile from playing.
        auto held=[&](std::uint32_t binding){return binding<input.keyboard.size()&&(input.keyboard[binding]&128)!=0;};
        if(controller_signed(w[3])>=0 && controller_signed(w[4])>=0)axis(14,held(w[3]),held(w[4]));
        if(controller_signed(w[1])>=0 && controller_signed(w[2])>=0)axis(15,held(w[1]),held(w[2]));
        for(unsigned i=0;i<8;++i)if(controller_signed(w[5+i])>=0)button(16+i,held(w[5+i]));
    }else{
        axis(14,input.x < -500,input.x > 500);axis(15,input.y < -500,input.y > 500);
        for(unsigned i=0;i<8;++i)if(controller_signed(w[5+i])>=0){
            const auto binding=w[5+i];
            button(16+i,binding<input.buttons.size()&&input.buttons[binding]!=0);
        }
    }
}
}
