#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "utils.h"

double random_double() {
    // srand(time(NULL));
    return (double)rand() / (double)(RAND_MAX);
}

double random_range(double min, double max) {
    return min + random_double() * (max - min);
}

double clamp(double x, double min, double max) {
    return x < min ? min : (x > max ? max : x);
}

double degrees_to_radians(double degrees) {
    return degrees * M_PI / 180.0;
}