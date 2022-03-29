#include <math.h>

#include "utils.h"
#include "vec3.h"


vec3_t vec3_init_empty(void) {
    vec3_t new = {0.0, 0.0, 0.0};
    return new;
}

vec3_t vec3_init(double x, double y, double z) {
    vec3_t new = {x, y, z};
    return new;
}

vec3_t vec3_init_random(void) {
    vec3_t new = {random_double(), random_double(), random_double()};
    return new;
}

vec3_t vec3_init_random_range(double min, double max) {
    vec3_t new = {random_range(min, max), random_range(min, max), random_range(min, max)};
    return new;
}

void vec3_invert(vec3_t v) {
    v.x = -v.x;
    v.y = -v.y;
    v.z = -v.z;
}

vec3_t vec3_add(vec3_t v, vec3_t u) {
    vec3_t res = vec3_init_empty();
    res.x = v.x + u.x;
    res.y = v.y + u.y;
    res.z = v.z + u.z;
    return res;
}

vec3_t vec3_sub(vec3_t v, vec3_t u) {
    vec3_t res = vec3_init_empty();
    res.x = v.x - u.x;
    res.y = v.y - u.y;
    res.z = v.z - u.z;
    return res;
}

vec3_t vec3_mult_scaler(vec3_t v, const double s) {
    vec3_t res = vec3_init_empty();
    res.x = v.x * s;
    res.y = v.y * s;
    res.z = v.z * s;
    return res;
}

vec3_t vec3_div_scaler(vec3_t v, const double s) {
    return vec3_mult_scaler(v, 1.0 / s);
}

vec3_t vec3_mult_vec(vec3_t v, vec3_t u) {
    vec3_t res = vec3_init_empty();
    res.x = v.x * u.x;
    res.y = v.y * u.y;
    res.z = v.z * u.z;
    return res;
}

vec3_t vec3_div_vec(vec3_t v, vec3_t u) {
    return vec3_mult_vec(v, vec3_init(1.0 / u.x, 1.0 / u.y, 1.0 / u.z));
}

double vec3_dot(vec3_t v, vec3_t u) {
    return v.x * u.x + v.y * u.y + v.z * u.z;
}

vec3_t vec3_cross(vec3_t v, vec3_t u) {
    vec3_t res = vec3_init_empty();
    res.x = v.y * u.z - v.z * u.y;
    res.y = v.z * u.x - v.x * u.z;
    res.z = v.x * u.y - v.y * u.x;
    return res;
}

vec3_t vec3_unit_vector(vec3_t v) {
    double length = vec3_length(v);
    return vec3_div_scaler(v, length);
}

double vec3_length(vec3_t v) {
    return sqrt(vec3_length_sq(v));
}

double vec3_length_sq(vec3_t v) {
    return vec3_dot(v, v);
}

vec3_t vec3_random_in_unit_sphere(void) {
    vec3_t p;
    do {
        p = vec3_init_random_range(-1.0, 1.0);
    } while (vec3_length_sq(p) >= 1.0);
    return p;
}

vec3_t vec3_random_in_hemisphere(vec3_t normal) {
    vec3_t in_unit_sphere = vec3_random_in_unit_sphere();
    if (vec3_dot(in_unit_sphere, normal) > 0.0) {
        return in_unit_sphere;
    } else {
        return vec3_mult_scaler(in_unit_sphere, -1.0);
    }
}