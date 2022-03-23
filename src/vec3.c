#include <math.h>

#include "vec3.h"


void vec3_init_empty(vec3_t *v) {
    v->x = 0.0;
    v->y = 0.0;
    v->z = 0.0;
}

void vec3_init(vec3_t *v, double x, double y, double z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

void vec3_invert(vec3_t *v) {
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
}

void vec3_add(vec3_t *v, vec3_t *u) {
    v->x += u->x;
    v->y += u->y;
    v->z += u->z;
}

void vec3_sub(vec3_t *v, vec3_t *u) {
    v->x -= u->x;
    v->y -= u->y;
    v->z -= u->z;
}

void vec3_mult_scaler(vec3_t *v, const double s) {
    v->x *= s;
    v->y *= s;
    v->z *= s;
}

void vec3_div_scaler(vec3_t *v, const double s) {
    vec3_mult_scaler(v, 1.0 / s);
}

void vec3_mult_vec(vec3_t *v, vec3_t *u) {
    v->x *= u->x;
    v->y *= u->y;
    v->z *= u->z;
}

void vec3_div_vec(vec3_t *v, vec3_t *u) {
    v->x /= u->x;
    v->y /= u->y;
    v->z /= u->z;
}

double vec3_dot(vec3_t *v, vec3_t *u) {
    return v->x * u->x + v->y * u->y + v->z * u->z;
}

void vec3_cross(vec3_t *v, vec3_t *u) {
    v->x = v->y * u->z - v->z * u->y;
    v->y = v->z * u->x - v->x * u->z;
    v->z = v->x * u->y - v->y * u->x;
}

void vec3_unit_vector(vec3_t *v) {
    double length = vec3_length(v);
    vec3_div_scaler(v, length);
}

double vec3_length(vec3_t *v) {
    return sqrt(vec3_length_sq(v));
}

double vec3_length_sq(vec3_t *v) {
    return v->x * v->x + v->y * v->y + v->z * v->z;
}
