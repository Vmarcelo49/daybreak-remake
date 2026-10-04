#pragma once
#include "input/input.h"
#include <deque>

namespace fnd::input
{
// A render can sample both sides of a tap before the next simulation tick.
// Preserve that order; catch-up ticks must not repeat a sampled press edge.
class TickInput
{
  public:
    void sample(const PlayerState &state)
    {
        bool changed = false;
        for (int a = 0; a < ActionCount; ++a)
            changed = changed || state.down[a] != latest_.down[a];
        latest_ = state;
        if (changed)
            pending_.push_back(state);
    }
    const PlayerState &consume()
    {
        const PlayerState next = pending_.empty() ? latest_ : pending_.front();
        if (!pending_.empty())
            pending_.pop_front();
        for (int a = 0; a < ActionCount; ++a)
            tick_.down[a] = next.down[a];
        tick_.stick_x  = next.stick_x;
        tick_.stick_y  = next.stick_y;
        tick_.stick_rx = next.stick_rx;
        tick_.stick_ry = next.stick_ry;
        compute_edges(tick_);
        return tick_;
    }

  private:
    PlayerState latest_, tick_;
    std::deque<PlayerState> pending_;
};
} // namespace fnd::input
