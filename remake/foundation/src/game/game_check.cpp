// Compile coverage for the header-only game interfaces (Track M follow-through).
//
// game/ is headers-only by design (glm+std, hud_bridge.h over ui/) so the
// gameplay side can include it without linking anything — which means no
// translation unit would otherwise compile these headers on a target build.
// This TU exists for exactly that: including every game header here fails
// every target build if one of them stops compiling. The static_asserts pin
// the small structural facts the wiring in main.cpp relies on.
#include <type_traits>

#include "game/camera_collision.h"
#include "game/effect_events.h"
#include "game/fighter_pose.h"
#include "game/hud_bridge.h"
#include "game/hud_values.h"

static_assert(std::is_default_constructible<game::FighterPose>::value,
              "FighterPose must stay aggregate-constructible for arenaTargetFrom");
static_assert(std::is_default_constructible<game::GameHudValues>::value,
              "GameHudValues must stay aggregate-constructible for syntheticHudValues");
static_assert(sizeof(game::EffectEventQueue) > 0u, "effect queue must be a complete type");
