#include "ray.h"
#include "sphere.h"
#include "hit_record.h"
#include "hittable.h"


hittable_t hittable_init(void *object, hittable_type_t type) {
    hittable_t h;
    h.object = object;
    h.type = type;
    return h;
}

bool hittable_hit(hittable_t h, ray_t ray, double t_min, double t_max, hit_record_t *rec) {
    switch (h.type) {
        case SPHERE:
            return sphere_hit(*(sphere_t *)h.object, ray, t_min, t_max, rec);
        default:
            return false;
    }
}