#include "vec.h"
#include "math.h"

void vecNormalize(Vec3* v) {
    double length = vecInvLen(v);
    
    v->x *= length;
    v->y *= length;
    v->z *= length;
}

double vecInvLen(const Vec3* v) {
    return invSqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}

void vecSAdd(Vec3* v, const double scalar) {
    v->x += scalar;
    v->y += scalar;
    v->z += scalar;
}

void vecProject(Vec2* out, const Vec3* v, const int fov) {
    out->x = (fov * v->x) / v->z;
    out->y = (fov * v->y) / v->z;
}

void vecRotx(Vec3* out, const Vec3* v, const double angle) {
    double cosA = cos(angle);
    double sinA = sin(angle);

    out->x = v->x;
    out->y = v->y * cosA - v->z * sinA;
    out->z = v->y * sinA + v->z * cosA;
}

void vecRoty(Vec3* out, const Vec3* v, const double angle) {
    double cosA = cos(angle);
    double sinA = sin(angle);

    out->x = v->x * cosA - v->z * sinA;
    out->y = v->y;
    out->z = v->x * sinA + v->z * cosA;
}

void vecRotz(Vec3* out, const Vec3* v, const double angle) {
    double cosA = cos(angle);
    double sinA = sin(angle);
   
    out->x = v->x * cosA - v->y * sinA;
    out->y = v->x * sinA + v->y * cosA;
    out->z = v->z;
}

void vecAdd(Vec3* out, const Vec3* v0, const Vec3* v1) {
    out->x = v0->x + v1->x;
    out->y = v0->y + v1->y;
    out->z = v0->z + v1->z;
}

void vecSub(Vec3* out, const Vec3* v0, const Vec3* v1) {
    out->x = v0->x - v1->x;
    out->y = v0->y - v1->y;
    out->z = v0->z - v1->z;
}

double vecDot(const Vec3* v0, const Vec3* v1) {
    return v0->x * v1->x + v0->y * v1->y + v0->z * v1->z;
}

void vecCross(Vec3* out, const Vec3* v0, const Vec3* v1) {
    out->x = v0->y * v1->z - v0->z * v1->y;
    out->y = v0->z * v1->x - v0->x * v1->z;
    out->z = v0->x * v1->y - v0->y * v1->x;
}