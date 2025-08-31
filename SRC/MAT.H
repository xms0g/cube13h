#ifndef MAT_H
#define MAT_H

#include "vec.h"

typedef struct {
    double m[3][3];
} Mat3;

void mtxIdentity(Mat3* out);

void mtxRotz(Mat3* out, double angle);

void mtxRoty(Mat3* out, double angle);

void mtxRotx(Mat3* out, double angle);

void mtxMulVec3(Vec3* out, const Mat3* m, const Vec3* v);

void mtxMulMat3(Mat3* out, const Mat3* m1, const Mat3* m2);

#endif