#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "color.h"


void write_color(FILE *f, const color_t c, int samples_per_pixel) {
    double r = c.x;
    double g = c.y;
    double b = c.z;

    double scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    fprintf(f, "%d %d %d\n",
        (int)(255.0 * clamp(r, 0, 0.999)),
        (int)(255.0 * clamp(g, 0, 0.999)),
        (int)(255.0 * clamp(b, 0, 0.999)));
}