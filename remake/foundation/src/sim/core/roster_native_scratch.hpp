#pragma once
#include <cstdint>
namespace daybreak {
// Actor E8/EC/F0/F4/F8 are shared across action states. A known bit records an
// observed native writer, not a guessed zero at construction or phase admission.
struct RosterNativeScratch {
 std::int32_t e8=0,ec=0,f0=0,f4=0,f8=0;
 std::uint32_t known=0;
};
inline std::int32_t native_scratch_increment(std::int32_t value){
 return static_cast<std::int32_t>(static_cast<std::uint32_t>(value)+1u);
}
}
