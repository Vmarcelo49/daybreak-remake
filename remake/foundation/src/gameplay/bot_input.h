#pragma once
// gameplay/bot_input.h — the host's one call into the COM decision state.
//
// The decision core lives in gameplay/bot_brain.h (recovered tactic cells, weights,
// timers and gates). This header is the seam between it and a live Match: it builds the
// brain's world view from the match's own targeting, projectile and collision state, and
// writes the resulting input. Nothing here decides anything.

#include "gameplay/bot_brain.h"
#include "gameplay/match.h"

namespace gameplay {

// The recovered tactics readout: player+0x310 (cell) and +0x314 (timer).
//
// FUN_0041f580:291-295 cycles the cell `(cell + 1) % 6` on the Tactics press, mirrors it
// onto player 0's cell and writes +0x314 = 2.0f. FUN_004201a0:13-15 drains +0x314 by 0.2
// per frame down to -6.0, and FUN_00644150:92-96 fades the boxed readout with it: the
// cell is drawn while +0x314 > -1.0, its alpha running (value + 1.0) below zero. Those
// 0.2 steps are the unit here, so the readout is up for kHoldTicks frames and its alpha
// tail runs kFadeTicks more.
//
// Port rule: the cell starts at the recovered default 0 (FUN_00421730:11) but with the
// timer already armed, so a round opens showing the default cell the way the reference
// battle capture does; the original only arms the timer on a press.
class TacticReadout {
public:
    static constexpr int kHoldTicks = 10;   // +0x314 = 2.0f, drained 0.2/frame
    static constexpr int kFadeTicks = 5;    // +0x314 falls 0.0 → -1.0 over the fade

    void reset(BotTactic cell = BotTactic::Adaptive, bool armed = true) {
        m_cell = cell;
        m_timer = armed ? kHoldTicks : -kFadeTicks;
    }

    // One Tactics press: cycle the cell and re-arm the readout timer.
    BotTactic press() {
        m_cell = bot_tactic_from_cell(bot_tactic_cell(m_cell) + 1);
        m_timer = kHoldTicks;
        return m_cell;
    }

    // One fixed tick of the recovered drain.
    void tick() {
        if (m_timer > -kFadeTicks - 1) --m_timer;
    }

    BotTactic cell() const { return m_cell; }
    // The HUD contract: >= 0 is the boxed cell to draw, < 0 hides it.
    int hud_cell() const { return m_timer > -kFadeTicks ? bot_tactic_cell(m_cell) : -1; }
    int ticks_left() const { return m_timer; }
    bool visible() const { return m_timer > -kFadeTicks; }

private:
    BotTactic m_cell = BotTactic::Adaptive;
    int m_timer = kHoldTicks;
};

// Everything the bridge needs that is not the brain's own state. One struct so the host's
// call site stays one line (main.cpp's tickMatch).
struct BotContext {
    Match* match = nullptr;                        // borrowed; must outlive the call
    const game::physics::MovementCollision* collision = nullptr;
    int    fighterIndex = 0;                       // a FIGHTER index (never a panel)
    int    leaderTarget = kNoTarget;               // the viewer's lock, for cells 3/4
};

// Fills `view` from the match: the fighter's selected hostile, its partner, the living
// hostile count, the incoming threat and the stage collision. Ally exclusion happens
// here — a same-side fighter is never a target and never a threat.
void buildBotView(BotView& view, const BotContext& ctx);

// One COM tick: sense, decide, and apply the retarget request through the match's own
// cycle (bounded by the recovered 15-tick switch pulse, exactly as the viewer's tap is).
// `brain` owns all persistent state, `input` receives the tick's keys.
void updateBotInput(BotBrain& brain, const BotContext& ctx, fnd::input::PlayerState& input,
                    uint64_t tick);

}  // namespace gameplay
