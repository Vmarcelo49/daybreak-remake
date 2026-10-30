#pragma once
#include <array>
#include <cstdint>
namespace daybreak {
// Stable handles replace original actor-relative pointers. Names distinguish
// duplicate fields without assuming they are previous/current animation states.
struct BattleActionState {
    std::array<std::uint32_t,3> words_2c{};
    std::uint32_t word_684=0,state=0,secondary_state=0,phase=0,secondary_phase=0;
    std::uint32_t frame_index=0,timer_ae04=0,timer_ae08=0,frame_handle=0,state_table_index=0;
};
// 0x421100. Host owns phase/frame assets and animation-channel binding.
template<class Host> void change_battle_phase(BattleActionState& s,std::uint32_t phase,Host& host){
    s.secondary_phase=phase;s.phase=phase;s.frame_index=0;s.timer_ae08=0;s.timer_ae04=0;
    auto entry=host.phase(s.state,s.phase);s.frame_handle=host.frame(entry,s.frame_index);
    entry=host.phase(s.secondary_state,s.secondary_phase);host.bind(0,host.animation(entry));
    entry=host.phase(s.state,s.phase);host.bind(1,host.animation(entry));
}
// 0x421080. Does not own state table bounds; host must validate loaded assets.
template<class Host> void change_battle_action(BattleActionState& s,std::uint32_t state,Host& host){
    s.words_2c={0,0,0};s.word_684=0xffffffffu;s.secondary_state=state;s.state=state;
    change_battle_phase(s,0,host);s.state_table_index=s.state;
}
}
