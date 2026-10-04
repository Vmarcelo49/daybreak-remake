#pragma once
#include <algorithm>
#include <cmath>

namespace gameplay
{
// Combat timers and FUN_004201a0's HUD pulse count updates, not presents.
// Live gameplay uses the user-selected 64 Hz port cadence; historical
// captures bypass this clock with their explicit --dt.
class FixedStep
{
  public:
    static constexpr int tickRate   = 64;
    static constexpr double seconds = 1.0 / tickRate;
    static constexpr int maxCatchUp = 8;

    int advance(double elapsed)
    {
        if (!std::isfinite(elapsed) || elapsed <= 0.0)
            return 0;
        // Discard whole overdue ticks after a stall, retaining the fractional
        // phase. This bounds latency/work rather than replaying seconds of input.
        const double total = remainder_ + std::min(elapsed, 60.0);
        const double ticks = std::floor((total + 1e-10) / seconds);
        remainder_         = std::max(0.0, total - ticks * seconds);
        return static_cast<int>(std::min(ticks, static_cast<double>(maxCatchUp)));
    }
    float alpha() const
    {
        return static_cast<float>(remainder_ / seconds);
    }

  private:
    double remainder_ = 0.0;
};
} // namespace gameplay
