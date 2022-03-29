#include <stdbool.h>
#include <math.h>

#include "hit_record.h"
#include "ray.h"
#include "vec3.h"
#include "sphere.h"


sphere_t sphere_init_empty(void) {
    sphere_t s;
    s.center = vec3_init_empty();
    s.radius = 0.0;
    return s;
}

sphere_t sphere_init(vec3_t center, double radius, material_t *material) {
    sphere_t s;
    s.center = vec3_init(center.x, center.y, center.z);
    s.radius = radius;
    s.material = material;
    return s;
}

bool sphere_hit(const sphere_t sphere, const ray_t r, double t_min, double t_max, hit_record_t *rec) {
    vec3_t oc = vec3_sub(r.origin, sphere.center);
    double a = vec3_length_sq(r.direction);
    double half_b = vec3_dot(oc, r.direction);
    double c = vec3_length_sq(oc) - sphere.radius * sphere.radius;

    double discriminant = (half_b * half_b) - (a * c);
    if (discriminant < 0) {
        return false;
    }

    double discriminant_sq = sqrt(discriminant);

    double root = (-half_b - discriminant_sq) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + discriminant_sq) / a;
        if (root < t_min || t_max < root) {
            return false;
        }
    }

    rec->t = root;
    rec->p = ray_at(r, root);
    vec3_t outward_normal = vec3_div_scaler(vec3_sub(rec->p, sphere.center), sphere.radius);
    set_face_normal(rec, r, outward_normal);
    rec->material = sphere.material;

    return true;
}