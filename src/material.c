#include <stdbool.h>

#include "vec3.h"

#include "material.h"


static bool material_lambertian_scatter(material_t *material, ray_t ray_in, hit_record_t *hit_record, color_t *attenuation, ray_t *scattered) {
    vec3_t scatter_direction = vec3_add(hit_record->normal, vec3_random_in_hemisphere(hit_record->normal));

    if (vec3_is_near_zero(scatter_direction)) {
        scatter_direction = hit_record->normal;
    }

    *scattered = ray_init(hit_record->p, scatter_direction);
    *attenuation = material->material.lambertian.albedo;
    return true;
}

static bool material_metal_scatter(material_t *material, ray_t ray_in, hit_record_t *hit_record, color_t *attenuation, ray_t *scattered) {
    vec3_t reflected = vec3_reflect(vec3_unit_vector(ray_in.direction), hit_record->normal);
    *scattered = ray_init(hit_record->p, vec3_add(reflected, vec3_mult_scaler(vec3_random_in_unit_sphere(), material->material.metal.fuzz)));
    *attenuation = material->material.metal.albedo;
    return vec3_dot(scattered->direction, hit_record->normal) > 0;
}

bool material_scatter(material_t *material, ray_t ray_in, hit_record_t *hit_record, color_t *attenuation, ray_t *scattered) {
    if (material->type == MATERIAL_LAMBERTIAN) {
        return material_lambertian_scatter(material, ray_in, hit_record, attenuation, scattered);
    } else if (material->type == MATERIAL_METAL) {
        return material_metal_scatter(material, ray_in, hit_record, attenuation, scattered);
    }
}

material_t material_lambertian_init(vec3_t albedo) {
    material_t m;
    m.type = MATERIAL_LAMBERTIAN;
    m.material.lambertian.albedo = albedo;
    return m;
}

material_t material_metal_init(vec3_t albedo, double fuzz) {
    material_t m;
    m.type = MATERIAL_METAL;
    m.material.metal.albedo = albedo;
    m.material.metal.fuzz = fuzz;
    return m;
}