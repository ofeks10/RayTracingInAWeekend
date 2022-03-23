#include <stdio.h>

#include "color.h"


void write_color(FILE *f, const color_t *c) {
    fprintf(f, "%d %d %d\n",(int)(255.0 * c->x), (int)(255.0 * c->y), (int)(255.0 * c->z));
}