#include <stdio.h>
#include <math.h>

#include "consts.h"
#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hittable.h"


color_t ray_color(const ray_t ray, const hittable_t *world, int object_amount) {
    hit_record_t rec;
    for (size_t i = 0; i < object_amount; i++)
    {
        sphere_t sphere = *(sphere_t *)world[i].object;
        if (hittable_hit(world[i], ray, 0.001, INFINITY, &rec)) {
            return vec3_mult_scaler(vec3_add(rec.normal, vec3_init(1.0, 1.0, 1.0)), 0.5);
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

    double viewport_height = 2.0;
    double viewport_width = ASPECT_RATION * viewport_height;
    double focal_length = 1.0;

    point3_t origin = vec3_init(0.0, 0.0, 0.0);
    vec3_t horizontal = vec3_init(viewport_width, 0.0, 0.0);
    vec3_t vertical = vec3_init(0.0, viewport_height, 0.0);

    vec3_t lower_left_corner = vec3_init(-0.5 * viewport_width, -0.5 * viewport_height, -focal_length);

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
            double u = (double)i / (double)(IMAGE_WIDTH - 1);
            double v = (double)j / (double)(IMAGE_HEIGHT - 1);
            ray_t ray = ray_init(origin, lower_left_corner);

            ray.direction.x += u * horizontal.x;
            ray.direction.y += v * vertical.y;

            write_color(stdout, (const color_t)ray_color((const ray_t)ray, world, object_amount));
        }
    }
    fprintf(stderr, "\n");
}