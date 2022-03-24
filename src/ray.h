#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct ray {
    vec3_t origin;
    vec3_t direction;
} ray_t;

ray_t ray_init_empty(void);
ray_t ray_init(const vec3_t origin, const vec3_t direction);
vec3_t ray_at(ray_t r, const double t);

#endif // RAY_H