#include <math.h>

#include "ray.h"
#include "vec3.h"
#include "utils.h"

#include "camera.h"


camera_t camera_init(double vertical_fov, double aspect, point3_t look_from, point3_t look_at, vec3_t vup) {
    camera_t c;

    double theta = degrees_to_radians(vertical_fov);
    double h = tan(theta / 2.0);
    double viewport_height = 2.0 * h;
    double viewport_width = ASPECT_RATIO * viewport_height;

    vec3_t w = vec3_unit_vector(vec3_sub(look_from, look_at));
    vec3_t u = vec3_unit_vector(vec3_cross(vup, w));
    vec3_t v = vec3_cross(w, u);

    c.origin = look_from;
    c.horizontal = vec3_mult_scaler(u, viewport_width);
    c.vertical = vec3_mult_scaler(v, viewport_height);

    c.lower_left_corner = vec3_add(c.origin, vec3_add(vec3_add(vec3_mult_scaler(c.vertical, -0.5), vec3_mult_scaler(c.horizontal, -0.5)), vec3_mult_scaler(w, -1.0)));

   return c;
}


ray_t camera_get_ray(camera_t camera, double s, double t) {
    point3_t direction = vec3_sub(
        vec3_add(vec3_add(camera.lower_left_corner, vec3_mult_scaler(camera.horizontal, s)),
            vec3_mult_scaler(camera.vertical, t)),
        camera.origin);

    return ray_init(camera.origin, direction);
}