#include <stdbool.h>
#include <math.h>

#include "vec3.h"
#include "utils.h"

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

static double reflectance(double cosine, double ref_idx) {
    double r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1.0 - r0) * pow(1.0 - cosine, 5.0);
}

static bool material_dielectric_scatter(material_t *material, ray_t ray_in, hit_record_t *hit_record, color_t *attenuation, ray_t *scattered) {
    *attenuation = vec3_init(1.0, 1.0, 1.0);
    double refraction_ratio = material->material.dielectric.index_of_refraction;
    refraction_ratio = hit_record->front_face ? (1.0 / refraction_ratio) : refraction_ratio;

    vec3_t unit_direction = vec3_unit_vector(ray_in.direction);
    double cos_theta = fmin(vec3_dot(vec3_mult_scaler(unit_direction, -1.0), hit_record->normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    vec3_t direction;

    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double()) {
        direction = vec3_reflect(unit_direction, hit_record->normal);
    } else {
        direction = vec3_refract(unit_direction, hit_record->normal, refraction_ratio);
    }

    *scattered = ray_init(hit_record->p, direction);
    return true;
}

bool material_scatter(material_t *material, ray_t ray_in, hit_record_t *hit_record, color_t *attenuation, ray_t *scattered) {
    if (material->type == MATERIAL_LAMBERTIAN) {
        return material_lambertian_scatter(material, ray_in, hit_record, attenuation, scattered);
    } else if (material->type == MATERIAL_METAL) {
        return material_metal_scatter(material, ray_in, hit_record, attenuation, scattered);
    } else if (material->type == MATERIAL_DIELECTRIC) {
        return material_dielectric_scatter(material, ray_in, hit_record, attenuation, scattered);
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

material_t material_dielectric_init(double index_of_refraction) {
    material_t m;
    m.type = MATERIAL_DIELECTRIC;
    m.material.dielectric.index_of_refraction = index_of_refraction;
    return m;
}