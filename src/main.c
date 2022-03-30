#include <stdio.h>
#include <math.h>

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
    hittable_t world[10] = { 0 };

    camera_t cam = camera_init(20.0, ASPECT_RATIO, vec3_init(-2, 2, 1), vec3_init(0, 0, -1), vec3_init(0, 1, 0));

    printf("P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);

    material_t material_ground = material_lambertian_init(vec3_init(0.8, 0.8, 0.0));
    material_t material_center = material_lambertian_init(vec3_init(0.1, 0.2, 0.5));
    material_t material_right = material_metal_init(vec3_init(0.8, 0.8, 0.8), 0.3);
    material_t material_left = material_dielectric_init(1.5);

    sphere_t sphere_center = sphere_init(vec3_init(0.0, 0.0, -1.0), 0.5, &material_center);
    sphere_t sphere_right = sphere_init(vec3_init(1.0, 0.0, -1.0), 0.5, &material_right);
    sphere_t sphere_left = sphere_init(vec3_init(-1.0, 0.0, -1.0), 0.5, &material_left);
    sphere_t sphere_left2 = sphere_init(vec3_init(-1.0, 0.0, -1.0), -0.4, &material_left);
    sphere_t background_sphere = sphere_init(vec3_init(0.0, -100.5, -1.0), 100.0, &material_ground);

    world[0] = hittable_init(&sphere_center, SPHERE);
    world[1] = hittable_init(&sphere_right, SPHERE);
    world[3] = hittable_init(&sphere_left, SPHERE);
    world[2] = hittable_init(&sphere_left2, SPHERE);
    world[4] = hittable_init(&background_sphere, SPHERE);

    object_amount += 5;

    for (int j = IMAGE_HEIGHT - 1; j >= 0; --j) {
        fprintf(stderr, "\rScan lines remaining: %d", j);
        for (int i = 0; i < IMAGE_WIDTH; ++i) {
            color_t pixel_color = vec3_init(0.0, 0.0, 0.0);
            for (int s = 0; s < SAMPLES_PER_PIXEL; ++s) {
                double u = (i + random_double()) / (IMAGE_WIDTH - 1);
                double v = (j + random_double()) / (IMAGE_HEIGHT - 1);
                ray_t ray = camera_get_ray(cam, u, v);
                pixel_color = vec3_add(pixel_color, ray_color(ray, world, object_amount, 50));
            }

            write_color(stdout, pixel_color, SAMPLES_PER_PIXEL);
        }
    }
    fprintf(stderr, "\n");
}