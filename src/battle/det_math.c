// One sin, cos and atan2 for every machine, so online peers compute the same floats.
//
// The C runtimes do not agree: glibc and Windows' differ in the last bits of a double, which the
// core's casts to float hide until the rare value that rounds the other way (docs/ONLINE-PLAN.md,
// step 5). This is musl v1.2.5's code, from src/math, concatenated and renamed, under the notices
// below and package/LICENSES/musl-MIT.txt. One change: arguments past 2^20*(pi/2) reduce through
// fmod instead of __rem_pio2_large. fmod is exact everywhere, so such a value is the same on every
// machine, though less accurate, and no sensible angle gets there.
#include "battle/det_math.h"

#include <float.h>
#include <math.h>
#include <stdint.h>

#define EPS DBL_EPSILON
#define predict_false(x) (x)
#define FORCE_EVAL(x) do { volatile double forced = (x); (void)forced; } while (0)
#define EXTRACT_WORDS(hi, lo, d) do { union { double f; uint64_t i; } words = {d}; (hi) = words.i >> 32; (lo) = (uint32_t)words.i; } while (0)
#define GET_HIGH_WORD(hi, d) do { union { double f; uint64_t i; } words = {d}; (hi) = words.i >> 32; } while (0)
#define SET_HIGH_WORD(d, hi) do { union { double f; uint64_t i; } words = {d}; words.i &= 0xffffffff; words.i |= (uint64_t)(hi) << 32; (d) = words.f; } while (0)
#define SET_LOW_WORD(d, lo) do { union { double f; uint64_t i; } words = {d}; words.i &= 0xffffffff00000000ull; words.i |= (uint32_t)(lo); (d) = words.f; } while (0)
/* origin: FreeBSD /usr/src/lib/msun/src/k_sin.c */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
/* det_kernel_sin( x, y, iy)
 * kernel sin function on ~[-pi/4, pi/4] (except on -0), pi/4 ~ 0.7854
 * Input x is assumed to be bounded by ~pi/4 in magnitude.
 * Input y is the tail of x.
 * Input iy indicates whether y is 0. (if iy=0, y assume to be 0).
 *
 * Algorithm
 *      1. Since sin(-x) = -sin(x), we need only to consider positive x.
 *      2. Callers must return sin(-0) = -0 without calling here since our
 *         odd polynomial is not evaluated in a way that preserves -0.
 *         Callers may do the optimization sin(x) ~ x for tiny x.
 *      3. sin(x) is approximated by a polynomial of degree 13 on
 *         [0,pi/4]
 *                               3            13
 *              sin(x) ~ x + S1*x + ... + S6*x
 *         where
 *
 *      |sin(x)         2     4     6     8     10     12  |     -58
 *      |----- - (1+S1*x +S2*x +S3*x +S4*x +S5*x  +S6*x   )| <= 2
 *      |  x                                               |
 *
 *      4. sin(x+y) = sin(x) + sin'(x')*y
 *                  ~ sin(x) + (1-x*x/2)*y
 *         For better accuracy, let
 *                   3      2      2      2      2
 *              r = x *(S2+x *(S3+x *(S4+x *(S5+x *S6))))
 *         then                   3    2
 *              sin(x) = x + (S1*x + (x *(r-y/2)+y))
 */


static const double
S1  = -1.66666666666666324348e-01, /* 0xBFC55555, 0x55555549 */
S2  =  8.33333333332248946124e-03, /* 0x3F811111, 0x1110F8A6 */
S3  = -1.98412698298579493134e-04, /* 0xBF2A01A0, 0x19C161D5 */
S4  =  2.75573137070700676789e-06, /* 0x3EC71DE3, 0x57B1FE7D */
S5  = -2.50507602534068634195e-08, /* 0xBE5AE5E6, 0x8A2B9CEB */
S6  =  1.58969099521155010221e-10; /* 0x3DE5D93A, 0x5ACFD57C */

static double det_kernel_sin(double x, double y, int iy)
{
	double_t z,r,v,w;

	z = x*x;
	w = z*z;
	r = S2 + z*(S3 + z*S4) + z*w*(S5 + z*S6);
	v = z*x;
	if (iy == 0)
		return x + v*(S1 + z*r);
	else
		return x - ((z*(0.5*y - v*r) - y) - v*S1);
}

/* origin: FreeBSD /usr/src/lib/msun/src/k_cos.c */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
/*
 * det_kernel_cos( x,  y )
 * kernel cos function on [-pi/4, pi/4], pi/4 ~ 0.785398164
 * Input x is assumed to be bounded by ~pi/4 in magnitude.
 * Input y is the tail of x.
 *
 * Algorithm
 *      1. Since cos(-x) = cos(x), we need only to consider positive x.
 *      2. if x < 2^-27 (hx<0x3e400000 0), return 1 with inexact if x!=0.
 *      3. cos(x) is approximated by a polynomial of degree 14 on
 *         [0,pi/4]
 *                                       4            14
 *              cos(x) ~ 1 - x*x/2 + C1*x + ... + C6*x
 *         where the remez error is
 *
 *      |              2     4     6     8     10    12     14 |     -58
 *      |cos(x)-(1-.5*x +C1*x +C2*x +C3*x +C4*x +C5*x  +C6*x  )| <= 2
 *      |                                                      |
 *
 *                     4     6     8     10    12     14
 *      4. let r = C1*x +C2*x +C3*x +C4*x +C5*x  +C6*x  , then
 *             cos(x) ~ 1 - x*x/2 + r
 *         since cos(x+y) ~ cos(x) - sin(x)*y
 *                        ~ cos(x) - x*y,
 *         a correction term is necessary in cos(x) and hence
 *              cos(x+y) = 1 - (x*x/2 - (r - x*y))
 *         For better accuracy, rearrange to
 *              cos(x+y) ~ w + (tmp + (r-x*y))
 *         where w = 1 - x*x/2 and tmp is a tiny correction term
 *         (1 - x*x/2 == w + tmp exactly in infinite precision).
 *         The exactness of w + tmp in infinite precision depends on w
 *         and tmp having the same precision as x.  If they have extra
 *         precision due to compiler bugs, then the extra precision is
 *         only good provided it is retained in all terms of the final
 *         expression for cos().  Retention happens in all cases tested
 *         under FreeBSD, so don't pessimize things by forcibly clipping
 *         any extra precision in w.
 */


static const double
C1  =  4.16666666666666019037e-02, /* 0x3FA55555, 0x5555554C */
C2  = -1.38888888888741095749e-03, /* 0xBF56C16C, 0x16C15177 */
C3  =  2.48015872894767294178e-05, /* 0x3EFA01A0, 0x19CB1590 */
C4  = -2.75573143513906633035e-07, /* 0xBE927E4F, 0x809C52AD */
C5  =  2.08757232129817482790e-09, /* 0x3E21EE9E, 0xBDB4B1C4 */
C6  = -1.13596475577881948265e-11; /* 0xBDA8FAE9, 0xBE8838D4 */

static double det_kernel_cos(double x, double y)
{
	double_t hz,z,r,w;

	z  = x*x;
	w  = z*z;
	r  = z*(C1+z*(C2+z*C3)) + w*w*(C4+z*(C5+z*C6));
	hz = 0.5*z;
	w  = 1.0-hz;
	return w + (((1.0-w)-hz) + (z*r-x*y));
}

/* origin: FreeBSD /usr/src/lib/msun/src/e_rem_pio2.c */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 *
 * Optimized by Bruce D. Evans.
 */
/* det_rem_pio2(x,y)
 *
 * return the remainder of x rem pi/2 in y[0]+y[1]
 * use __rem_pio2_large() for large x
 */



/*
 * invpio2:  53 bits of 2/pi
 * pio2_1:   first  33 bit of pi/2
 * pio2_1t:  pi/2 - pio2_1
 * pio2_2:   second 33 bit of pi/2
 * pio2_2t:  pi/2 - (pio2_1+pio2_2)
 * pio2_3:   third  33 bit of pi/2
 * pio2_3t:  pi/2 - (pio2_1+pio2_2+pio2_3)
 */
static const double
toint   = 1.5/EPS,
pio4    = 0x1.921fb54442d18p-1,
invpio2 = 6.36619772367581382433e-01, /* 0x3FE45F30, 0x6DC9C883 */
pio2_1  = 1.57079632673412561417e+00, /* 0x3FF921FB, 0x54400000 */
pio2_1t = 6.07710050650619224932e-11, /* 0x3DD0B461, 0x1A626331 */
pio2_2  = 6.07710050630396597660e-11, /* 0x3DD0B461, 0x1A600000 */
pio2_2t = 2.02226624879595063154e-21, /* 0x3BA3198A, 0x2E037073 */
pio2_3  = 2.02226624871116645580e-21, /* 0x3BA3198A, 0x2E000000 */
pio2_3t = 8.47842766036889956997e-32; /* 0x397B839A, 0x252049C1 */

/* caller must handle the case when reduction is not needed: |x| ~<= pi/4 */
static int det_rem_pio2(double x, double *y)
{
	union {double f; uint64_t i;} u = {x};
	double_t z,w,t,r,fn;
		uint32_t ix;
	int sign, n, ex, ey;

	sign = u.i>>63;
	ix = u.i>>32 & 0x7fffffff;
	if (ix <= 0x400f6a7a) {  /* |x| ~<= 5pi/4 */
		if ((ix & 0xfffff) == 0x921fb)  /* |x| ~= pi/2 or 2pi/2 */
			goto medium;  /* cancellation -- use medium case */
		if (ix <= 0x4002d97c) {  /* |x| ~<= 3pi/4 */
			if (!sign) {
				z = x - pio2_1;  /* one round good to 85 bits */
				y[0] = z - pio2_1t;
				y[1] = (z-y[0]) - pio2_1t;
				return 1;
			} else {
				z = x + pio2_1;
				y[0] = z + pio2_1t;
				y[1] = (z-y[0]) + pio2_1t;
				return -1;
			}
		} else {
			if (!sign) {
				z = x - 2*pio2_1;
				y[0] = z - 2*pio2_1t;
				y[1] = (z-y[0]) - 2*pio2_1t;
				return 2;
			} else {
				z = x + 2*pio2_1;
				y[0] = z + 2*pio2_1t;
				y[1] = (z-y[0]) + 2*pio2_1t;
				return -2;
			}
		}
	}
	if (ix <= 0x401c463b) {  /* |x| ~<= 9pi/4 */
		if (ix <= 0x4015fdbc) {  /* |x| ~<= 7pi/4 */
			if (ix == 0x4012d97c)  /* |x| ~= 3pi/2 */
				goto medium;
			if (!sign) {
				z = x - 3*pio2_1;
				y[0] = z - 3*pio2_1t;
				y[1] = (z-y[0]) - 3*pio2_1t;
				return 3;
			} else {
				z = x + 3*pio2_1;
				y[0] = z + 3*pio2_1t;
				y[1] = (z-y[0]) + 3*pio2_1t;
				return -3;
			}
		} else {
			if (ix == 0x401921fb)  /* |x| ~= 4pi/2 */
				goto medium;
			if (!sign) {
				z = x - 4*pio2_1;
				y[0] = z - 4*pio2_1t;
				y[1] = (z-y[0]) - 4*pio2_1t;
				return 4;
			} else {
				z = x + 4*pio2_1;
				y[0] = z + 4*pio2_1t;
				y[1] = (z-y[0]) + 4*pio2_1t;
				return -4;
			}
		}
	}
	if (ix < 0x413921fb) {  /* |x| ~< 2^20*(pi/2), medium size */
medium:
		/* rint(x/(pi/2)) */
		fn = (double_t)x*invpio2 + toint - toint;
		n = (int32_t)fn;
		r = x - fn*pio2_1;
		w = fn*pio2_1t;  /* 1st round, good to 85 bits */
		/* Matters with directed rounding. */
		if (predict_false(r - w < -pio4)) {
			n--;
			fn--;
			r = x - fn*pio2_1;
			w = fn*pio2_1t;
		} else if (predict_false(r - w > pio4)) {
			n++;
			fn++;
			r = x - fn*pio2_1;
			w = fn*pio2_1t;
		}
		y[0] = r - w;
		u.f = y[0];
		ey = u.i>>52 & 0x7ff;
		ex = ix>>20;
		if (ex - ey > 16) { /* 2nd round, good to 118 bits */
			t = r;
			w = fn*pio2_2;
			r = t - w;
			w = fn*pio2_2t - ((t-r)-w);
			y[0] = r - w;
			u.f = y[0];
			ey = u.i>>52 & 0x7ff;
			if (ex - ey > 49) {  /* 3rd round, good to 151 bits, covers all cases */
				t = r;
				w = fn*pio2_3;
				r = t - w;
				w = fn*pio2_3t - ((t-r)-w);
				y[0] = r - w;
			}
		}
		y[1] = (r - y[0]) - w;
		return n;
	}
	if (ix >= 0x7ff00000) {  /* x is inf or NaN */
		y[0] = y[1] = x - x;
		return 0;
	}
	return det_rem_pio2(fmod(x, 0x1.921fb54442d18p+2), y);
}

/* origin: FreeBSD /usr/src/lib/msun/src/s_sin.c */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
/* sin(x)
 * Return sine function of x.
 *
 * kernel function:
 *      det_kernel_sin            ... sine function on [-pi/4,pi/4]
 *      det_kernel_cos            ... cose function on [-pi/4,pi/4]
 *      det_rem_pio2       ... argument reduction routine
 *
 * Method.
 *      Let S,C and T denote the sin, cos and tan respectively on
 *      [-PI/4, +PI/4]. Reduce the argument x to y1+y2 = x-k*pi/2
 *      in [-pi/4 , +pi/4], and let n = k mod 4.
 *      We have
 *
 *          n        sin(x)      cos(x)        tan(x)
 *     ----------------------------------------------------------
 *          0          S           C             T
 *          1          C          -S            -1/T
 *          2         -S          -C             T
 *          3         -C           S            -1/T
 *     ----------------------------------------------------------
 *
 * Special cases:
 *      Let trig be any of sin, cos, or tan.
 *      trig(+-INF)  is NaN, with signals;
 *      trig(NaN)    is that NaN;
 *
 * Accuracy:
 *      TRIG(x) returns trig(x) nearly rounded
 */


double det_sin(double x)
{
	double y[2];
	uint32_t ix;
	unsigned n;

	/* High word of x. */
	GET_HIGH_WORD(ix, x);
	ix &= 0x7fffffff;

	/* |x| ~< pi/4 */
	if (ix <= 0x3fe921fb) {
		if (ix < 0x3e500000) {  /* |x| < 2**-26 */
			/* raise inexact if x != 0 and underflow if subnormal*/
			FORCE_EVAL(ix < 0x00100000 ? x/0x1p120f : x+0x1p120f);
			return x;
		}
		return det_kernel_sin(x, 0.0, 0);
	}

	/* sin(Inf or NaN) is NaN */
	if (ix >= 0x7ff00000)
		return x - x;

	/* argument reduction needed */
	n = det_rem_pio2(x, y);
	switch (n&3) {
	case 0: return  det_kernel_sin(y[0], y[1], 1);
	case 1: return  det_kernel_cos(y[0], y[1]);
	case 2: return -det_kernel_sin(y[0], y[1], 1);
	default:
		return -det_kernel_cos(y[0], y[1]);
	}
}

/* origin: FreeBSD /usr/src/lib/msun/src/s_cos.c */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
/* cos(x)
 * Return cosine function of x.
 *
 * kernel function:
 *      det_kernel_sin           ... sine function on [-pi/4,pi/4]
 *      det_kernel_cos           ... cosine function on [-pi/4,pi/4]
 *      det_rem_pio2      ... argument reduction routine
 *
 * Method.
 *      Let S,C and T denote the sin, cos and tan respectively on
 *      [-PI/4, +PI/4]. Reduce the argument x to y1+y2 = x-k*pi/2
 *      in [-pi/4 , +pi/4], and let n = k mod 4.
 *      We have
 *
 *          n        sin(x)      cos(x)        tan(x)
 *     ----------------------------------------------------------
 *          0          S           C             T
 *          1          C          -S            -1/T
 *          2         -S          -C             T
 *          3         -C           S            -1/T
 *     ----------------------------------------------------------
 *
 * Special cases:
 *      Let trig be any of sin, cos, or tan.
 *      trig(+-INF)  is NaN, with signals;
 *      trig(NaN)    is that NaN;
 *
 * Accuracy:
 *      TRIG(x) returns trig(x) nearly rounded
 */


double det_cos(double x)
{
	double y[2];
	uint32_t ix;
	unsigned n;

	GET_HIGH_WORD(ix, x);
	ix &= 0x7fffffff;

	/* |x| ~< pi/4 */
	if (ix <= 0x3fe921fb) {
		if (ix < 0x3e46a09e) {  /* |x| < 2**-27 * sqrt(2) */
			/* raise inexact if x!=0 */
			FORCE_EVAL(x + 0x1p120f);
			return 1.0;
		}
		return det_kernel_cos(x, 0);
	}

	/* cos(Inf or NaN) is NaN */
	if (ix >= 0x7ff00000)
		return x-x;

	/* argument reduction */
	n = det_rem_pio2(x, y);
	switch (n&3) {
	case 0: return  det_kernel_cos(y[0], y[1]);
	case 1: return -det_kernel_sin(y[0], y[1], 1);
	case 2: return -det_kernel_cos(y[0], y[1]);
	default:
		return  det_kernel_sin(y[0], y[1], 1);
	}
}

/* origin: FreeBSD /usr/src/lib/msun/src/s_atan.c */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 */
/* atan(x)
 * Method
 *   1. Reduce x to positive by atan(x) = -atan(-x).
 *   2. According to the integer k=4t+0.25 chopped, t=x, the argument
 *      is further reduced to one of the following intervals and the
 *      arctangent of t is evaluated by the corresponding formula:
 *
 *      [0,7/16]      atan(x) = t-t^3*(a1+t^2*(a2+...(a10+t^2*a11)...)
 *      [7/16,11/16]  atan(x) = atan(1/2) + atan( (t-0.5)/(1+t/2) )
 *      [11/16.19/16] atan(x) = atan( 1 ) + atan( (t-1)/(1+t) )
 *      [19/16,39/16] atan(x) = atan(3/2) + atan( (t-1.5)/(1+1.5t) )
 *      [39/16,INF]   atan(x) = atan(INF) + atan( -1/t )
 *
 * Constants:
 * The hexadecimal values are the intended ones for the following
 * constants. The decimal values may be used, provided that the
 * compiler will convert from decimal to binary accurately enough
 * to produce the hexadecimal values shown.
 */



static const double atanhi[] = {
  4.63647609000806093515e-01, /* atan(0.5)hi 0x3FDDAC67, 0x0561BB4F */
  7.85398163397448278999e-01, /* atan(1.0)hi 0x3FE921FB, 0x54442D18 */
  9.82793723247329054082e-01, /* atan(1.5)hi 0x3FEF730B, 0xD281F69B */
  1.57079632679489655800e+00, /* atan(inf)hi 0x3FF921FB, 0x54442D18 */
};

static const double atanlo[] = {
  2.26987774529616870924e-17, /* atan(0.5)lo 0x3C7A2B7F, 0x222F65E2 */
  3.06161699786838301793e-17, /* atan(1.0)lo 0x3C81A626, 0x33145C07 */
  1.39033110312309984516e-17, /* atan(1.5)lo 0x3C700788, 0x7AF0CBBD */
  6.12323399573676603587e-17, /* atan(inf)lo 0x3C91A626, 0x33145C07 */
};

static const double aT[] = {
  3.33333333333329318027e-01, /* 0x3FD55555, 0x5555550D */
 -1.99999999998764832476e-01, /* 0xBFC99999, 0x9998EBC4 */
  1.42857142725034663711e-01, /* 0x3FC24924, 0x920083FF */
 -1.11111104054623557880e-01, /* 0xBFBC71C6, 0xFE231671 */
  9.09088713343650656196e-02, /* 0x3FB745CD, 0xC54C206E */
 -7.69187620504482999495e-02, /* 0xBFB3B0F2, 0xAF749A6D */
  6.66107313738753120669e-02, /* 0x3FB10D66, 0xA0D03D51 */
 -5.83357013379057348645e-02, /* 0xBFADDE2D, 0x52DEFD9A */
  4.97687799461593236017e-02, /* 0x3FA97B4B, 0x24760DEB */
 -3.65315727442169155270e-02, /* 0xBFA2B444, 0x2C6A6C2F */
  1.62858201153657823623e-02, /* 0x3F90AD3A, 0xE322DA11 */
};

static double det_atan(double x)
{
	double_t w,s1,s2,z;
	uint32_t ix,sign;
	int id;

	GET_HIGH_WORD(ix, x);
	sign = ix >> 31;
	ix &= 0x7fffffff;
	if (ix >= 0x44100000) {   /* if |x| >= 2^66 */
		if (isnan(x))
			return x;
		z = atanhi[3] + 0x1p-120f;
		return sign ? -z : z;
	}
	if (ix < 0x3fdc0000) {    /* |x| < 0.4375 */
		if (ix < 0x3e400000) {  /* |x| < 2^-27 */
			if (ix < 0x00100000)
				/* raise underflow for subnormal x */
				FORCE_EVAL((float)x);
			return x;
		}
		id = -1;
	} else {
		x = fabs(x);
		if (ix < 0x3ff30000) {  /* |x| < 1.1875 */
			if (ix < 0x3fe60000) {  /*  7/16 <= |x| < 11/16 */
				id = 0;
				x = (2.0*x-1.0)/(2.0+x);
			} else {                /* 11/16 <= |x| < 19/16 */
				id = 1;
				x = (x-1.0)/(x+1.0);
			}
		} else {
			if (ix < 0x40038000) {  /* |x| < 2.4375 */
				id = 2;
				x = (x-1.5)/(1.0+1.5*x);
			} else {                /* 2.4375 <= |x| < 2^66 */
				id = 3;
				x = -1.0/x;
			}
		}
	}
	/* end of argument reduction */
	z = x*x;
	w = z*z;
	/* break sum from i=0 to 10 aT[i]z**(i+1) into odd and even poly */
	s1 = z*(aT[0]+w*(aT[2]+w*(aT[4]+w*(aT[6]+w*(aT[8]+w*aT[10])))));
	s2 = w*(aT[1]+w*(aT[3]+w*(aT[5]+w*(aT[7]+w*aT[9]))));
	if (id < 0)
		return x - x*(s1+s2);
	z = atanhi[id] - (x*(s1+s2) - atanlo[id] - x);
	return sign ? -z : z;
}

/* origin: FreeBSD /usr/src/lib/msun/src/e_atan2.c */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice
 * is preserved.
 * ====================================================
 *
 */
/* atan2(y,x)
 * Method :
 *      1. Reduce y to positive by atan2(y,x)=-atan2(-y,x).
 *      2. Reduce x to positive by (if x and y are unexceptional):
 *              ARG (x+iy) = arctan(y/x)           ... if x > 0,
 *              ARG (x+iy) = pi - arctan[y/(-x)]   ... if x < 0,
 *
 * Special cases:
 *
 *      ATAN2((anything), NaN ) is NaN;
 *      ATAN2(NAN , (anything) ) is NaN;
 *      ATAN2(+-0, +(anything but NaN)) is +-0  ;
 *      ATAN2(+-0, -(anything but NaN)) is +-pi ;
 *      ATAN2(+-(anything but 0 and NaN), 0) is +-pi/2;
 *      ATAN2(+-(anything but INF and NaN), +INF) is +-0 ;
 *      ATAN2(+-(anything but INF and NaN), -INF) is +-pi;
 *      ATAN2(+-INF,+INF ) is +-pi/4 ;
 *      ATAN2(+-INF,-INF ) is +-3pi/4;
 *      ATAN2(+-INF, (anything but,0,NaN, and INF)) is +-pi/2;
 *
 * Constants:
 * The hexadecimal values are the intended ones for the following
 * constants. The decimal values may be used, provided that the
 * compiler will convert from decimal to binary accurately enough
 * to produce the hexadecimal values shown.
 */


static const double
pi     = 3.1415926535897931160E+00, /* 0x400921FB, 0x54442D18 */
pi_lo  = 1.2246467991473531772E-16; /* 0x3CA1A626, 0x33145C07 */

double det_atan2(double y, double x)
{
	double z;
	uint32_t m,lx,ly,ix,iy;

	if (isnan(x) || isnan(y))
		return x+y;
	EXTRACT_WORDS(ix, lx, x);
	EXTRACT_WORDS(iy, ly, y);
	if ((ix-0x3ff00000 | lx) == 0)  /* x = 1.0 */
		return det_atan(y);
	m = ((iy>>31)&1) | ((ix>>30)&2);  /* 2*sign(x)+sign(y) */
	ix = ix & 0x7fffffff;
	iy = iy & 0x7fffffff;

	/* when y = 0 */
	if ((iy|ly) == 0) {
		switch(m) {
		case 0:
		case 1: return y;   /* det_atan(+-0,+anything)=+-0 */
		case 2: return  pi; /* det_atan(+0,-anything) = pi */
		case 3: return -pi; /* det_atan(-0,-anything) =-pi */
		}
	}
	/* when x = 0 */
	if ((ix|lx) == 0)
		return m&1 ? -pi/2 : pi/2;
	/* when x is INF */
	if (ix == 0x7ff00000) {
		if (iy == 0x7ff00000) {
			switch(m) {
			case 0: return  pi/4;   /* det_atan(+INF,+INF) */
			case 1: return -pi/4;   /* det_atan(-INF,+INF) */
			case 2: return  3*pi/4; /* det_atan(+INF,-INF) */
			case 3: return -3*pi/4; /* det_atan(-INF,-INF) */
			}
		} else {
			switch(m) {
			case 0: return  0.0; /* det_atan(+...,+INF) */
			case 1: return -0.0; /* det_atan(-...,+INF) */
			case 2: return  pi;  /* det_atan(+...,-INF) */
			case 3: return -pi;  /* det_atan(-...,-INF) */
			}
		}
	}
	/* |y/x| > 0x1p64 */
	if (ix+(64<<20) < iy || iy == 0x7ff00000)
		return m&1 ? -pi/2 : pi/2;

	/* z = det_atan(|y/x|) without spurious underflow */
	if ((m&2) && iy+(64<<20) < ix)  /* |y/x| < 0x1p-64, x<0 */
		z = 0;
	else
		z = det_atan(fabs(y/x));
	switch (m) {
	case 0: return z;              /* det_atan(+,+) */
	case 1: return -z;             /* det_atan(-,+) */
	case 2: return pi - (z-pi_lo); /* det_atan(+,-) */
	default: /* case 3 */
		return (z-pi_lo) - pi; /* det_atan(-,-) */
	}
}
