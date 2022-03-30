#include <stddef.h>

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

bool hittable_hit(const hittable_t *h, size_t amount, ray_t ray, double t_min, double t_max, hit_record_t *rec) {
    hit_record_t temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;
    for (size_t i = 0; i < amount; i++)
    {
        if (h[i].type == SPHERE)
        {
            if (sphere_hit(*(sphere_t *)h[i].object, ray, t_min, closest_so_far, &temp_rec))
            {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                *rec = temp_rec;
            }
        }
    }
    return hit_anything;
}