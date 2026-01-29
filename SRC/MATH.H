#ifndef MATH_H
#define MATH_H

#include <math.h>

#define TWO_PI 6.283185307179586

#define absf(v) (v < 0 ? 0 - v : v)

#define ceilf(v) ((int)v + 1)

#define floorf(v) (int)v

#define signbit(v) (v < 0.0 ? 1 : 0)

#define round(v) (signbit(v) ? ceilf(v - 0.5) : floorf(v + 0.5))

#define min(n0, n1) (n1 ^ ((n0 ^ n1) & -(n0 < n1)))

#define max(n0, n1) (n1 ^ ((n0 ^ n1) & -(n0 > n1)))

double invSqrt(double n);

void initSinCosLUT(void);

double sinLUT(double angle);

double cosLUT(double angle);

#endif