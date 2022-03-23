#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct ray {
    vec3_t origin;
    vec3_t direction;
} ray_t;

void ray_init_empty(ray_t *r);
void ray_init(ray_t *r, const vec3_t *origin, const vec3_t *direction);
void ray_at(ray_t *r, const double t, vec3_t *result);

#endif // RAY_H