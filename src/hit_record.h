#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include <stdbool.h>

#include "vec3.h"
#include "ray.h"
#include "material.h"

typedef struct material material_t;

typedef struct hit_record {
    vec3_t p;
    vec3_t normal;
    double t;
    bool front_face;
    material_t *material;
} hit_record_t;

void set_face_normal(hit_record_t *rec, const ray_t r, vec3_t outward_normal);

#endif // HIT_RECORD_H
