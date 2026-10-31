#pragma once
// Force-included for the vendored core: it relies on these arriving transitively, which
// holds for its original x86-windows-gnu toolchain but not for libstdc++.
#include <climits>
#include <cstring>

// Every call the core makes to these goes to one implementation, on every machine (det_math.c).
// The headers stay as vendored. fmod and sqrt stay in the C runtime, whose answers are exact by
// definition. pow is only ever called to square.
#include <cmath>
#include <stdexcept>

#include "battle/det_math.h"

namespace std {
inline double det_core_sin(double x) { return ::det_sin(x); }
inline double det_core_cos(double x) { return ::det_cos(x); }
inline double det_core_atan2(double y, double x) { return ::det_atan2(y, x); }
inline double det_core_pow(double x, double y) {
    if (y != 2.) throw std::logic_error("core: pow is only expected to square");
    return x * x;
}
}  // namespace std
#define sin det_core_sin
#define cos det_core_cos
#define atan2 det_core_atan2
#define pow det_core_pow
