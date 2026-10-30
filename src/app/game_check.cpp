// Compile coverage for the header-only game interfaces (Track M follow-through).
//
// game/ is headers-only by design (glm+std, hud_bridge.h over ui/) so the
// gameplay side can include it without linking anything — which means no
// translation unit would otherwise compile these headers on a target build.
// This TU exists for exactly that: including every game header here fails
// every target build if one of them stops compiling. The static_asserts pin
// the small structural facts the wiring in main.cpp relies on.
#include <type_traits>

#include "camera/camera_collision.h"
#include "render/effect_events.h"
#include "camera/fighter_pose.h"
#include "hud/hud_bridge.h"
#include "hud/hud_values.h"
#include "battle/match_view.h"
#include "hud/view_layout.h"

static_assert(std::is_default_constructible<game::FighterPose>::value,
              "FighterPose must stay aggregate-constructible for arenaTargetFrom");
static_assert(std::is_default_constructible<game::GameHudValues>::value,
              "GameHudValues must stay aggregate-constructible for syntheticHudValues");
static_assert(sizeof(game::EffectEventQueue) > 0u, "effect queue must be a complete type");
static_assert(std::is_default_constructible<game::MatchView>::value,
              "MatchView must stay default-constructible: a frame's views are filled in place");
static_assert(game::kMaxHumanViews == game::viewCellCount(game::SplitLayout::Four),
              "the view array and the four-cell grid must agree");
