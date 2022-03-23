#include "ray.h"


void ray_init_empty(ray_t *r) {
    vec3_init_empty(&r->origin);
    vec3_init_empty(&r->direction);
}

void ray_init(ray_t *r, const vec3_t *origin, const vec3_t *direction) {
    vec3_init(&r->origin, origin->x, origin->y, origin->z);
    vec3_init(&r->direction, direction->x, direction->y, direction->z);
}

void ray_at(ray_t *r, const double t, vec3_t *result) {
    vec3_init(result, r->origin.x + t * r->direction.x,
              r->origin.y + t * r->direction.y,
              r->origin.z + t * r->direction.z);
}