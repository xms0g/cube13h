#include "math.h"
#include <math.h>

#define LUT_SIZE 2048

static double sinTable[LUT_SIZE];
static double cosTable[LUT_SIZE];

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

void initSinCosLUT(void) {
    int i;
    // This function can be used to initialize any sine/cosine lookup tables if needed.
    // Currently, it does nothing as we are using the standard library functions.

    for (i = 0; i < LUT_SIZE; i++) {
        double rad = (i * TWO_PI) / LUT_SIZE;
        sinTable[i] = sin(rad);
        cosTable[i] = cos(rad);
    }
}

static int calcIndex(double angle) {
    int idx = (int)(angle * (LUT_SIZE / TWO_PI));
    if (idx < 0) idx = 0;
    if (idx >= LUT_SIZE) idx = LUT_SIZE - 1;
    return idx;
}

double sinLUT(double angle) {
    return sinTable[calcIndex(angle)];
}

double cosLUT(double angle) {
    return cosTable[calcIndex(angle)];
}