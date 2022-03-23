#include <stdio.h>

#include "consts.h"
#include "color.h"
#include "vec3.h"
#include "ray.h"

void ray_color(const ray_t *ray, color_t *output) {
    vec3_t unit_direction;
    vec3_copy(&unit_direction, (const vec3_t *)&ray->direction);
    vec3_unit_vector(&unit_direction);

    double t = 0.5 * (unit_direction.y + 1.0);

    color_t white, blue;
    vec3_init(&white, 1.0, 1.0, 1.0);
    vec3_init(&blue, 0.5, 0.7, 1.0);

    vec3_mult_scaler(&white, 1.0 - t);
    vec3_mult_scaler(&blue, t);

    vec3_copy(output, &white);
    vec3_add(output, &blue);
}


int main(void) {
    printf("P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);

    double viewport_height = 2.0;
    double viewport_width = ASPECT_RATION * viewport_height;
    double focal_length = 1.0;

    point3_t origin;
    vec3_t horizontal, vertical;
    vec3_init(&origin, 0.0, 0.0, 0.0);
    vec3_init(&horizontal, viewport_width, 0.0, 0.0);
    vec3_init(&vertical, 0.0, viewport_height, 0.0);

    vec3_t lower_left_corner;
    vec3_copy(&lower_left_corner, &origin);
    lower_left_corner.x -= 0.5 * viewport_width;
    lower_left_corner.y -= 0.5 * viewport_height;
    lower_left_corner.z -= focal_length;

    for (int j = IMAGE_HEIGHT - 1; j >= 0; --j) {
        fprintf(stderr, "\rScan lines remaining: %d", j);
        for (int i = 0; i < IMAGE_WIDTH; ++i) {
            double u = (double)i / (double)(IMAGE_WIDTH - 1);
            double v = (double)j / (double)(IMAGE_HEIGHT - 1);
            ray_t ray;
            ray_init(&ray, &origin, &lower_left_corner);
            ray.direction.x += u * horizontal.x;
            ray.direction.y += v * vertical.y;

            color_t pixel_color;
            ray_color(&ray, &pixel_color);

            write_color(stdout, &pixel_color);
        }
    }
    fprintf(stderr, "\n");
}