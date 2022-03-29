#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

typedef struct camera {
    point3_t origin;
    point3_t lower_left_corner;
    vec3_t horizontal;
    vec3_t vertical;
} camera_t;

camera_t camera_init();
ray_t camera_get_ray(camera_t camera, float u, float v);

#endif // CAMERA_H