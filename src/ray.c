#include "ray.h"


ray_t ray_init_empty(void) {
    ray_t r;
    r.origin = vec3_init_empty();
    r.direction = vec3_init_empty();
    return r;
}

ray_t ray_init(const vec3_t origin, const vec3_t direction) {
    ray_t r;
    r.origin = vec3_init(origin.x, origin.y, origin.z);
    r.direction = vec3_init(direction.x, direction.y, direction.z);
    return r;
}

vec3_t ray_at(ray_t r, const double t) {
    return vec3_init(r.origin.x + t * r.direction.x,
                        r.origin.y + t * r.direction.y,
                        r.origin.z + t * r.direction.z);
}