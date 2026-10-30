#include "hud/hud_fill.h"

// The ui seam: hud/hud_bridge.h reaches hud/hud.h -> sprite.h -> webgpu.h. This
// is the only translation unit of the gameplay HUD port that includes it; the
// mapping itself (fillHudValues, hud_fill.h) stays device-free so the host test
// links match_economy.cpp alone.
#include "hud/hud_bridge.h"

namespace gameplay {

ui::HudState hudStateFor(const MatchEconomy& eco, const HudFillInput& in) {
    return game::makeHudState(fillHudValues(eco, in));
}

}  // namespace gameplay
