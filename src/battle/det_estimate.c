// The reciprocal and reciprocal square root the vendored core starts its D3DX normalise and skinning
// paths from, as exactly rounded values instead of the CPU's estimates (issue #107).
//
// The original D3DX9 Vec3/Vec4Normalize reads SSE's rsqrtss and then takes one Newton step, and its
// skinning divides through rcpps the same way. Both instructions are specified only to within a
// relative error bound — 1.5*2^-12 for rsqrtss — and the bits they actually return are a per-model
// table. Measured: the same probe binary gives 00bbea513765195f on a Ryzen 5 5600 and 08f27ffa2a95fa4c
// on an i3-10100T, and the Newton step does not fold the two onto the same float (it leaves 33% and
// 40% of inputs, respectively, away from the exactly rounded answer). So two peers on different CPU
// models genuinely simulate different battles from the same inputs, which is what desynced the
// two-machine room at frame 181.
//
// sqrt and division are IEEE-751 exact operations, so the value computed here is identical on every
// machine, and on the web build, whose SSE emulation supplies its own rsqrtss again. This is a
// deliberate behaviour change on the machines whose estimate was not already exact; see
// src/battle/core/PATCHES.md.
#include "battle/det_math.h"

#include <math.h>

float det_rsqrt(float x) { return (float)(1.0 / sqrt((double)x)); }

float det_rcp(float x) { return (float)(1.0 / (double)x); }
