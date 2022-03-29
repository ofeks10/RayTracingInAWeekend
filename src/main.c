#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hittable.h"
#include "camera.h"


color_t ray_color(const ray_t ray, const hittable_t *world, int object_amount, int depth) {
    hit_record_t rec;

    if (depth <= 0) {
        return vec3_init(0.0, 0.0, 0.0);
    }

    for (size_t i = 0; i < object_amount; i++)
    {
        if (hittable_hit(world[i], ray, 0.0001, INFINITY, &rec)) {
            vec3_t target = vec3_add(vec3_random_in_hemisphere(rec.normal), (rec.p, rec.normal));
            ray_t bouncing_ray = ray_init(rec.p, vec3_sub(target, rec.p));
            return vec3_mult_scaler(ray_color(bouncing_ray, world, object_amount, depth - 1), 0.5);
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

    camera_t cam = camera_init();


    printf("P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);

    sphere_t sphere = sphere_init(vec3_init(0.0, 0.0, -1.0), 0.5);
    sphere_t background_sphere = sphere_init(vec3_init(0.0, -100.5, -1.0), 100.0);
    world[0] = hittable_init(&sphere, SPHERE);
    world[1] = hittable_init(&background_sphere, SPHERE);
    object_amount++;
    object_amount++;

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