#include <math.h>

#include "ray.h"
#include "vec3.h"
#include "utils.h"

#include "camera.h"


camera_t camera_init(double vertical_fov, double aspect, point3_t look_from, point3_t look_at, vec3_t vup, double aperture, double focus_dist) {
    camera_t c;

    double theta = degrees_to_radians(vertical_fov);
    double h = tan(theta / 2.0);
    double viewport_height = 2.0 * h;
    double viewport_width = ASPECT_RATIO * viewport_height;

    c.w = vec3_unit_vector(vec3_sub(look_from, look_at));
    c.u = vec3_unit_vector(vec3_cross(vup, c.w));
    c.v = vec3_cross(c.w, c.u);

    c.origin = look_from;
    c.horizontal = vec3_mult_scaler(c.u, viewport_width * focus_dist);
    c.vertical = vec3_mult_scaler(c.v, viewport_height * focus_dist);

    c.lower_left_corner = vec3_add(c.origin, vec3_add(vec3_add(vec3_mult_scaler(c.vertical, -0.5), vec3_mult_scaler(c.horizontal, -0.5)), vec3_mult_scaler(c.w, -1.0 * focus_dist)));

    c.lens_radius = aperture / 2.0;
    return c;
}


ray_t camera_get_ray(camera_t camera, double s, double t) {
    vec3_t rd = vec3_mult_scaler(vec3_random_in_unit_sphere(), camera.lens_radius);
    vec3_t offset = vec3_add(vec3_mult_scaler(camera.u, rd.x), vec3_mult_scaler(camera.v, rd.y));

    point3_t direction = vec3_sub(vec3_sub(
        vec3_add(vec3_add(camera.lower_left_corner, vec3_mult_scaler(camera.horizontal, s)),
            vec3_mult_scaler(camera.vertical, t)),
        camera.origin), offset);

    return ray_init(vec3_add(camera.origin, offset), direction);
}