#ifndef VEC3_H
#define VEC3_H

#include <stdbool.h>

typedef struct vec3 {
    double x;
    double y;
    double z;
} vec3_t;

vec3_t vec3_init_empty(void);
vec3_t vec3_init(double x, double y, double z);
vec3_t vec3_init_random(void);
vec3_t vec3_init_random_range(double min, double max);
void vec3_invert(vec3_t v);
vec3_t vec3_add(vec3_t v, vec3_t u);
vec3_t vec3_sub(vec3_t v, vec3_t u);
vec3_t vec3_mult_scaler(vec3_t v, const double s);
vec3_t vec3_div_scaler(vec3_t v, const double s);
vec3_t vec3_mult_vec(vec3_t v, vec3_t u);
vec3_t vec3_div_vec(vec3_t v, vec3_t u);
double vec3_dot(vec3_t v, vec3_t u);
vec3_t vec3_cross(vec3_t v, vec3_t u);
vec3_t vec3_unit_vector(vec3_t v);
double vec3_length(vec3_t v);
double vec3_length_sq(vec3_t v);
vec3_t vec3_copy(vec3_t v, const vec3_t u);
vec3_t vec3_random_in_unit_sphere(void);
vec3_t vec3_random_in_hemisphere(vec3_t normal);
bool vec3_is_near_zero(vec3_t v);
vec3_t vec3_reflect(vec3_t v, vec3_t normal);
vec3_t vec3_refract(vec3_t v, vec3_t normal, double etai_over_etat);

typedef vec3_t point3_t;
typedef vec3_t color_t;

#endif // VEC3_H
