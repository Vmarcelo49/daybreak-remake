#pragma once
#include <array>
#include <optional>
namespace daybreak {
// 435990 accepts either a contact vector or the direction produced by42c8e0.
// Contact vectors must not make a round trip through heading/pitch lookup.
struct BattleEffectRequest {
 unsigned actor=0,id=0;
 std::array<float,3> position{};
 float heading=0,pitch=0;
 std::optional<std::array<float,3>> direction;
};
}
