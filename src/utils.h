#ifndef CONSTS_H
#define CONSTS_H

#include <stdlib.h>


#define ASPECT_RATIO (3.0 / 2.0)
#define IMAGE_WIDTH  (1200)
#define IMAGE_HEIGHT ((int)(IMAGE_WIDTH / ASPECT_RATIO))
#define SAMPLES_PER_PIXEL (500)

double random_double(void);
double random_range(double min, double max);
double clamp(double x, double min, double max);
double degrees_to_radians(double degrees);

#endif // CONSTS_H