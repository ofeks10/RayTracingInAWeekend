#include "hit_record.h"
#include "ray.h"


void set_face_normal(hit_record_t *rec, const ray_t r, vec3_t outward_normal) {
    rec->front_face = vec3_dot(r.direction, outward_normal) < 0;
    rec->normal = rec->front_face ? outward_normal : vec3_mult_scaler(outward_normal, -1);
}