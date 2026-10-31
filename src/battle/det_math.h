#pragma once
// One sin, cos and atan2 for every machine (det_math.c). The rest of the program, which only draws,
// keeps the C runtime's.
#ifdef __cplusplus
extern "C" {
#endif
double det_sin(double x);
double det_cos(double x);
double det_atan2(double y, double x);
#ifdef __cplusplus
}
#endif
