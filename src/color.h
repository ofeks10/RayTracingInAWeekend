#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>

#include "vec3.h"


void write_color(FILE *f, const color_t c, int samples_per_pixel);

#endif // COLOR_H