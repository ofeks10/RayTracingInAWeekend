#ifndef SPHERE_H
#define SPHERE_H

#include <stdbool.h>

#include "hit_record.h"
#include "ray.h"
#include "vec3.h"
#include "material.h"


typedef struct sphere {
    vec3_t center;
    double radius;
    material_t *material;
} sphere_t;

sphere_t sphere_init_empty(void);
sphere_t sphere_init(vec3_t center, double radius, material_t *material);
bool sphere_hit(const sphere_t sphere, const ray_t r, double t_min, double t_max, hit_record_t *rec);


#endif // SPHERE_H