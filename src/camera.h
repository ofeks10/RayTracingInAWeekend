#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

typedef struct camera {
    point3_t origin;
    point3_t lower_left_corner;
    vec3_t horizontal;
    vec3_t vertical;
    double lens_radius;
    vec3_t u;
    vec3_t v;
    vec3_t w;
} camera_t;

camera_t camera_init(double vertical_fov, double aspect, point3_t look_from, point3_t look_at, vec3_t vup, double aperture, double focus_dist);
ray_t camera_get_ray(camera_t camera, double s, double t);

#endif // CAMERA_H