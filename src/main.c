#include <stdio.h>

#include "consts.h"
#include "color.h"
#include "vec3.h"
#include "ray.h"

color_t ray_color(const ray_t ray) {
    vec3_t unit_direction = vec3_unit_vector(ray.direction);

    double t = 0.5 * (unit_direction.y + 1.0);

    vec3_t result = vec3_add(vec3_mult_scaler(vec3_init(1.0, 1.0, 1.0), 1.0 - t),
        vec3_mult_scaler(vec3_init(0.5, 0.7, 1.0), t));

    return result;
}


int main(void) {
    printf("P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);

    double viewport_height = 2.0;
    double viewport_width = ASPECT_RATION * viewport_height;
    double focal_length = 1.0;

    point3_t origin = vec3_init(0.0, 0.0, 0.0);
    vec3_t horizontal = vec3_init(viewport_width, 0.0, 0.0);
    vec3_t vertical = vec3_init(0.0, viewport_height, 0.0);

    vec3_t lower_left_corner = vec3_init(-0.5 * viewport_width, -0.5 * viewport_height, -focal_length);

    for (int j = IMAGE_HEIGHT - 1; j >= 0; --j) {
        fprintf(stderr, "\rScan lines remaining: %d", j);
        for (int i = 0; i < IMAGE_WIDTH; ++i) {
            double u = (double)i / (double)(IMAGE_WIDTH - 1);
            double v = (double)j / (double)(IMAGE_HEIGHT - 1);
            ray_t ray = ray_init(origin, lower_left_corner);

            ray.direction.x += u * horizontal.x;
            ray.direction.y += v * vertical.y;

            write_color(stdout, (const color_t)ray_color((const ray_t)ray));
        }
    }
    fprintf(stderr, "\n");
}