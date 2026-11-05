#pragma once
// One sin, cos and atan2 for every machine (det_math.c). The rest of the program, which only draws,
// keeps the C runtime's.
#ifdef __cplusplus
extern "C" {
#endif
double det_sin(double x);
double det_cos(double x);
double det_atan2(double y, double x);
// SSE's rsqrtss and rcpps return an estimate whose exact bits are the CPU model's, not the ISA's,
// so two machines can disagree in the last place (issue #107). These replace the estimates the
// core's D3DX normalise and skinning paths start from, with the exactly rounded value.
float det_rsqrt(float x);
float det_rcp(float x);
#ifdef __cplusplus
}
#endif
