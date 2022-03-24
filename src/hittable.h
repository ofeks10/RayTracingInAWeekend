#ifndef HITTABLE_H
#define HITTABLE_H

#include <stdbool.h>

#include "ray.h"
#include "hit_record.h"


enum hittable_type { SPHERE };
typedef hittable_type hittable_type_t;

typedef struct hittable {
    void *object;
    hittable_type_t type;
} hittable_t;

hittable_t hittable_init(void *object, hittable_type_t type);
bool hittable_hit(hittable_t h, ray_t ray, double t_min, double t_max, hit_record_t *rec);


#endif // HITTABLE_H