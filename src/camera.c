#include "ray.h"
#include "vec3.h"
#include "utils.h"

#include "camera.h"

camera_t camera_init() {
    camera_t c;
    double viewport_height = 2.0;
    double viewport_width = ASPECT_RATIO * viewport_height;
    double focal_length = 1.0;

    c.origin = vec3_init(0.0, 0.0, 0.0);
    c.horizontal = vec3_init(viewport_width, 0.0, 0.0);
    c.vertical = vec3_init(0.0, viewport_height, 0.0);

    c.lower_left_corner = vec3_init(-0.5 * viewport_width, -0.5 * viewport_height, -focal_length);

   return c;
}


ray_t camera_get_ray(camera_t camera, float u, float v) {
    point3_t direction = vec3_sub(
        vec3_add(vec3_add(camera.lower_left_corner, vec3_mult_scaler(camera.horizontal, u)),
            vec3_mult_scaler(camera.vertical, v)),
        camera.origin);

    return ray_init(camera.origin, direction);
}