#include <stdio.h>

#include "consts.h"
#include "color.h"
#include "vec3.h"

int main(void) {
    printf("P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);

    for (int j = IMAGE_HEIGHT - 1; j >= 0; --j) {
        fprintf(stderr, "\rScan lines remaining: %d", j);
        for (int i = 0; i < IMAGE_WIDTH; ++i) {
            color_t c;
            vec3_init(&c,
                (double) i / (double) (IMAGE_WIDTH - 1),
                (double) j / (double) (IMAGE_HEIGHT - 1),
                0.25);
            write_color(stdout, &c);
        }
    }
    fprintf(stderr, "\n");
}