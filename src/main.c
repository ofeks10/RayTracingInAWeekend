#include <stdio.h>

#include "consts.h"

int main(void) {
    printf("P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);

    for (int j = IMAGE_HEIGHT - 1; j >= 0; --j) {
        fprintf(stderr, "\rScan lines remaining: %d", j);
        for (int i = 0; i < IMAGE_WIDTH; ++i) {
            double r = (double) i / (double) (IMAGE_WIDTH - 1);
            double g = (double) j / (double) (IMAGE_HEIGHT - 1);
            double b = 0.25;

            int ir = (int) (r * 255.0);
            int ig = (int) (g * 255.0);
            int ib = (int) (b * 255.0);

            printf("%d %d %d\n", ir, ig, ib);
        }
    }
    fprintf(stderr, "\n");
}