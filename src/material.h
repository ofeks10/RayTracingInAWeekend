#ifndef MATERIAL_H
#define MATERIAL_H

#include <stdbool.h>

#include "vec3.h"
#include "hit_record.h"
#include "ray.h"


typedef enum material_type {
    MATERIAL_LAMBERTIAN,
    MATERIAL_METAL,
    MATERIAL_DIELECTRIC,
    MATERIAL_DIFFUSE_LIGHT
} material_type_t;

typedef struct hit_record hit_record_t;
typedef struct lambertian {
    vec3_t albedo;
} lambertian_t;

union material_data {
    struct {
        vec3_t albedo;
    } lambertian;
    struct {
        vec3_t albedo;
        double fuzz;
    } metal;
    struct {
        double index_of_refraction;
    } dielectric;
    struct {
        vec3_t emitted;
    } diffuse_light;
};

typedef struct material {
    material_type_t type;
    union material_data material;
} material_t;

bool material_scatter(material_t *material, ray_t ray_in, hit_record_t *hit_record, color_t *attenuation, ray_t *scattered);
material_t material_lambertian_init(vec3_t albedo);
material_t material_metal_init(vec3_t albedo, double fuzz);

#endif // MATERIAL_H