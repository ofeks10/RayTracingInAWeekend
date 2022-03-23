#ifndef VEC3_H
#define VEC3_H

typedef struct vec3 {
    double x;
    double y;
    double z;
} vec3_t;

void vec3_init_empty(vec3_t *v);
void vec3_init(vec3_t *v, double x, double y, double z);
void vec3_invert(vec3_t *v);
void vec3_add(vec3_t *v, vec3_t *u);
void vec3_sub(vec3_t *v, vec3_t *u);
void vec3_mult_scalar(vec3_t *v, const double s);
void vec3_div_scaler(vec3_t *v, const double s);
void vec3_mult_vec(vec3_t *v, vec3_t *u);
void vec3_div_vec(vec3_t *v, vec3_t *u);
double vec3_dot(vec3_t *v, vec3_t *u);
void vec3_cross(vec3_t *v, vec3_t *u);
void vec3_unit_vector(vec3_t *v);
double vec3_length(vec3_t *v);
double vec3_length_sq(vec3_t *v);

typedef vec3_t point3_t;
typedef vec3_t color_t;

#endif // VEC3_H
