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

// SSE's rsqrtss and rcpps are estimates whose returned bits belong to the CPU model rather than to
// the ISA, so the core's normalise and skinning paths would start from a different value on each
// machine and the two battles would part (issue #107). Redirected here, at the call sites, for the
// same reason and in the same way as sin and cos: the vendored headers keep as they are. The
// intrinsic headers are included first so that these names are the functions, not macros, and the
// core's own `#include <xmmintrin.h>` then finds the guard already set.
#include <xmmintrin.h>
inline __m128 det_core_rsqrt_ss(__m128 v) { return _mm_set_ss(::det_rsqrt(_mm_cvtss_f32(v))); }
inline __m128 det_core_rcp_ps(__m128 v) {
    return _mm_set_ps(::det_rcp(_mm_cvtss_f32(_mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 3, 3)))),
                      ::det_rcp(_mm_cvtss_f32(_mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2)))),
                      ::det_rcp(_mm_cvtss_f32(_mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1)))),
                      ::det_rcp(_mm_cvtss_f32(v)));
}
#define _mm_rsqrt_ss det_core_rsqrt_ss
#define _mm_rcp_ps det_core_rcp_ps
