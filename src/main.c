#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "utils.h"
#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hittable.h"
#include "camera.h"
#include "material.h"


color_t ray_color(const ray_t ray, const hittable_t *world, int object_amount, int depth) {
    hit_record_t rec;

    if (depth <= 0) {
        return vec3_init(0.0, 0.0, 0.0);
    }

    if (hittable_hit(world, object_amount, ray, 0.0001, INFINITY, &rec)) {
        ray_t scattered;
        color_t attenuation;
        if (material_scatter(rec.material, ray, &rec, &attenuation, &scattered)) {
            return vec3_mult_vec(attenuation, ray_color(scattered, world, object_amount, depth - 1));
        } else {
            return vec3_init(0.0, 0.0, 0.0);
        }
    }

    vec3_t unit_direction = vec3_unit_vector(ray.direction);

    double t = 0.5 * (unit_direction.y + 1.0);

    vec3_t result = vec3_add(vec3_mult_scaler(vec3_init(1.0, 1.0, 1.0), 1.0 - t),
        vec3_mult_scaler(vec3_init(0.5, 0.7, 1.0), t));

    return result;
}


int main(void) {
    int object_amount = 0;
    hittable_t world[500] = { 0 };
    srand(time(NULL));

    point3_t look_from = vec3_init(13.0, 2.0, 3.0);
    point3_t look_at = vec3_init(0.0, 0.0, 0.0);
    vec3_t vup = vec3_init(0.0, 1.0, 0.0);
    double dist_to_focus = 10.0;
    double aperture = 0.1;

    camera_t cam = camera_init(20.0, ASPECT_RATIO, look_from, look_at, vup, aperture, dist_to_focus);

    printf("P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);

    /* scene: */
    material_t material_ground = material_lambertian_init(vec3_init(0.5, 0.5, 0.5));
    sphere_t ground = sphere_init(vec3_init(0.0, -1000.0, 0.0), 1000.0, &material_ground);
    world[0] = hittable_init(&ground, SPHERE);
    object_amount++;

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double choose_mat = random_double();
            point3_t center = vec3_init(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if (vec3_length(vec3_sub(center, vec3_init(4.0, 0.2, 0.0))) > 0.9) {
                if (choose_mat < 0.8) {
                    material_t material_mat = material_lambertian_init(vec3_mult_vec(vec3_init_random(), vec3_init_random()));
                    material_t *malloced_mat = malloc(sizeof(material_t));
                    *malloced_mat = material_mat;
                    sphere_t mat = sphere_init(center, 0.2, malloced_mat);
                    sphere_t *malloced_sphere = malloc(sizeof(sphere_t));
                    *malloced_sphere = mat;
                    world[object_amount] = hittable_init(malloced_sphere, SPHERE);
                } else if (choose_mat < 0.95) {
                    material_t material_mat = material_metal_init(vec3_init(0.5 * (1 + random_double()), 0.5 * (1 + random_double()), 0.5 * (1 + random_double())), 0.5 * random_double());
                    material_t *malloced_mat = malloc(sizeof(material_t));
                    *malloced_mat = material_mat;
                    sphere_t mat = sphere_init(center, 0.2, malloced_mat);
                    sphere_t *malloced_sphere = malloc(sizeof(sphere_t));
                    *malloced_sphere = mat;
                    world[object_amount] = hittable_init(malloced_sphere, SPHERE);
                } else {
                    material_t material_mat = material_dielectric_init(1.5);
                    material_t *malloced_mat = malloc(sizeof(material_t));
                    sphere_t mat = sphere_init(center, 0.2, malloced_mat);
                    sphere_t *malloced_sphere = malloc(sizeof(sphere_t));
                    *malloced_sphere = mat;
                    world[object_amount] = hittable_init(malloced_sphere, SPHERE);
                }
                object_amount++;
            }
        }
    }

    material_t mat_diel = material_dielectric_init(1.5);
    sphere_t glass = sphere_init(vec3_init(0.0, 1.0, 0.0), 1.0, &mat_diel);
    world[object_amount] = hittable_init(&glass, SPHERE);
    object_amount++;

    material_t mat_lamb = material_lambertian_init(vec3_init(0.4, 0.2, 0.1));
    sphere_t lambert = sphere_init(vec3_init(-4.0, 1.0, 0.0), 1.0, &mat_lamb);
    world[object_amount] = hittable_init(&lambert, SPHERE);
    object_amount++;

    material_t mat_metal = material_metal_init(vec3_init(0.7, 0.6, 0.5), 0.0);
    sphere_t metal = sphere_init(vec3_init(4.0, 1.0, 0.0), 1.0, &mat_metal);
    world[object_amount] = hittable_init(&metal, SPHERE);
    object_amount++;

    for (int j = IMAGE_HEIGHT - 1; j >= 0; --j) {
        fprintf(stderr, "\rScan lines remaining: %d", j);
        for (int i = 0; i < IMAGE_WIDTH; ++i) {
            color_t pixel_color = vec3_init(0.0, 0.0, 0.0);
            for (int s = 0; s < SAMPLES_PER_PIXEL; ++s) {
                double u = (i + random_double()) / (IMAGE_WIDTH - 1);
                double v = (j + random_double()) / (IMAGE_HEIGHT - 1);
                ray_t ray = camera_get_ray(cam, u, v);
                pixel_color = vec3_add(pixel_color, ray_color(ray, world, object_amount, 10));
            }

            write_color(stdout, pixel_color, SAMPLES_PER_PIXEL);
        }
    }
    fprintf(stderr, "\n");
}