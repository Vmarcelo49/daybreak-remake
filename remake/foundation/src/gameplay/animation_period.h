#pragma once
// The engine's animation window: how many updates a clip occupies.
//
// FUN_0041e839 divides D3DX GetPeriod() (seconds) by the 0.016 constant at 0x6a2434 and
// converts the result with the helper at 0x66b668. That helper is the compiler's own
// float-to-int conversion — 1148 call sites across the image — and it truncates toward
// zero: it rounds with `fistp`, forms the residual `x - round(x)` and corrects it with
// `add ecx,0x7fffffff; sbb eax,0`, which subtracts one exactly when the rounding went up
// (disassembly at 0x66b668-0x66b6c5). Truncation is therefore what the original does, not
// nearest-even: a clip whose period is 23.96 frames occupies 23 updates, and one that is
// exactly 12.5 occupies 12.
//
// The recovered bundle states the same rule (`actor_animation_clock.hpp:17-22`,
// `unsigned(period / 0.016f)`), and the shipped data depends on it: the side dash's
// recovery clip is 1840 ticks = 23.96 frames.
//
// An earlier port note claimed this conversion "rounds" and used std::nearbyint, which
// agrees only for clips that are a whole number of updates or a .5 tie that rounds down.

#include "assets/xmodel.h"
#include "gameplay/combat_record.h"

#include <cmath>
#include <cstddef>

namespace gameplay {

// Updates the clip occupies; 0 is a REAL window (the source's strict `period < elapsed`
// then advances on the first update), and -1 means the window cannot be derived from the
// data. Keeping those apart matters: a synthetic half-update clip truncates to 0 and must
// still advance.
inline int animation_period_frames(const xm::Model& model, int setIndex) {
    if (setIndex < 0 || static_cast<std::size_t>(setIndex) >= model.anims.size()) return -1;
    const float ticksPerSecond = model.ticksPerSecond;
    if (!std::isfinite(ticksPerSecond) || ticksPerSecond <= 0.f) return -1;
    const float duration = model.anims[static_cast<std::size_t>(setIndex)].duration;
    if (!std::isfinite(duration) || duration < 0.f) return -1;
    // static_cast truncates toward zero, which is the original's conversion.
    return static_cast<int>(duration / ticksPerSecond / kOriginalAnimationTick);
}

}  // namespace gameplay
