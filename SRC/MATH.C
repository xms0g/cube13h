#include "math.h"

double invSqrt(double n) {
    long i;
    float x2, y;

    x2 = n * 0.5F;
    y = n;
    i = *(long *)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float *)&i;
    y = y * (1.5f - (x2 * y * y));   // 1st iteration
    y = y * (1.5f - (x2 * y * y));   // 2nd iteration

    return y;
}