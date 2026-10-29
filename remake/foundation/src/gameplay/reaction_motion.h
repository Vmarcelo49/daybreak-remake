#pragma once

namespace gameplay {

// What a reaction row DOES to the victim. In the original the hit code writes no motion at
// all: it names a row (record combat[13] normally, combat[14] once the victim's +0x7c0 has
// reached 100, +100 when the hit comes from behind) and that row's handler applies the
// movement. FUN_00428510's dispatch table is the source of every constant below.
//
// Rows with no entry (and every row outside the reaction band) apply nothing — damage,
// freeze and gauges only. That is why two hits can look completely different while sharing
// the same "hit" state.
struct ReactionMotion {
    bool  applies = false;
    float speed = 0.f;      // +0x54: signed horizontal speed, per TICK (negative = backwards)
    float rise = 0.f;       // +0x40: vertical speed, per tick (positive = up)
    float gravity = 0.f;    // +0x58
    float decel = 0.f;      // per-tick change of `speed` toward zero
    // The from-record rows take the two impulses from the attack record:
    //   combat[17] (+0x74) -> +0x40, the LIFT
    //   combat[18] (+0x78) -> +0x54, the horizontal SLIDE
    // Only {105,113,114,115,116,121,133} read them; every other row ignores the pair even
    // though the data still stores it.
    bool  liftFromRecord = false;
    bool  slideFromRecord = false;
};

// Recovered constants (FUN_00428510 handlers; the +100 band is the back-hit mirror with the
// sign flipped).
inline ReactionMotion reaction_motion(int row) {
    ReactionMotion m;
    m.applies = true;
    switch (row) {
        // Ground stagger: slide straight back, decelerating. 101 is the same body as 100.
        case 100: case 101: m.speed = -25.f; m.decel = 1.5f; break;
        case 102:           m.speed = -20.f; m.decel = 0.5f; break;
        // Long stagger: the handler idles through phase 0 and slides on phase 1.
        case 104:           m.speed = -15.f; m.decel = 1.5f; break;
        // Launchers: the impulse is the record's own pair, converted at the phase-1 boundary.
        case 105: case 113: case 114: case 115: case 133:
                            m.liftFromRecord = m.slideFromRecord = true; m.gravity = 0.3f; break;
        case 116:           m.liftFromRecord = m.slideFromRecord = true; m.gravity = 1.0f; break;
        // Pop up in place: a fixed lift with its own gravity.
        case 106:           m.rise = 9.f; m.gravity = 0.6f; break;
        // Ground slide from the record's horizontal impulse.
        case 121:           m.slideFromRecord = true; break;   // horizontal only
        // Crumple: no displacement at all, the animation carries the hit.
        case 130: case 131: break;
        // Reel end.
        case 134:           m.speed = -20.f; m.decel = 0.5f; break;
        // Back-hit mirrors: same bodies, signs flipped.
        case 200: case 201: m.speed = 25.f;  m.decel = 1.5f; break;
        case 202:           m.speed = 20.f;  m.decel = 0.5f; break;
        case 204:           m.speed = 15.f;  m.decel = 1.5f; break;
        case 213: case 214: case 215: case 233:
                            m.liftFromRecord = m.slideFromRecord = true; m.gravity = 0.3f; break;
        case 216:           m.liftFromRecord = m.slideFromRecord = true; m.gravity = 1.0f; break;
        case 221:           m.slideFromRecord = true; break;
        case 230: case 231: break;
        case 234:           m.speed = 20.f;  m.decel = 0.5f; break;
        default:            m.applies = false; break;
    }
    return m;
}

}  // namespace gameplay
