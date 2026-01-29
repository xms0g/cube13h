#include "mat.h"
#include "math.h"

void mtxIdentity(Mat3* out) {
    int i, j;
    
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j)
            out->m[i][j] = (i == j) ? 1.0 : 0.0;
}

void mtxRotz(Mat3* out, double angle) {
    // | c -s  0 |
    // | s  c  0 |
    // | 0  0  1 |
    double c = cosLUT(angle);
    double s = sinLUT(angle);
    
    mtxIdentity(out);
    
    out->m[0][0] = c;
    out->m[0][1] = -s;
    out->m[1][0] = s;
    out->m[1][1] = c;
}

void mtxRoty(Mat3* out, double angle) {
    // |  c  0  s |
    // |  0  1  0 |
    // | -s  0  c |
    double c = cosLUT(angle);
    double s = sinLUT(angle);
    
    mtxIdentity(out);
    
    out->m[0][0] = c;
    out->m[0][2] = s;
    out->m[2][0] = -s;
    out->m[2][2] = c;
}

void mtxRotx(Mat3* out, double angle) {
    // | 1  0  0 |
    // | 0  c -s |
    // | 0  s  c |
    double c = cosLUT(angle);
    double s = sinLUT(angle);
    
    mtxIdentity(out);
    
    out->m[1][1] = c;
    out->m[1][2] = -s;
    out->m[2][1] = s;
    out->m[2][2] = c;
}

void mtxMulVec3(Vec3* out, const Mat3* m, const Vec3* v) {
    out->x = m->m[0][0] * v->x + m->m[0][1] * v->y + m->m[0][2] * v->z;
    out->y = m->m[1][0] * v->x + m->m[1][1] * v->y + m->m[1][2] * v->z;
    out->z = m->m[2][0] * v->x + m->m[2][1] * v->y + m->m[2][2] * v->z;
}

void mtxMulMat3(Mat3* out, const Mat3* m1, const Mat3* m2) {
    int i, j;
   
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            out->m[i][j] = m1->m[i][0] * m2->m[0][j] + m1->m[i][1] * m2->m[1][j] + m1->m[i][2] * m2->m[2][j];
        }
    }
}