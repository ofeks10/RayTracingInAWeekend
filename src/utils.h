#ifndef CONSTS_H
#define CONSTS_H

#include <stdlib.h>


#define ASPECT_RATIO (16.0 / 9.0)
#define IMAGE_WIDTH  (400)
#define IMAGE_HEIGHT ((int)(IMAGE_WIDTH / ASPECT_RATIO))
#define SAMPLES_PER_PIXEL (100)

double random_double(void);
double random_range(double min, double max);
double clamp(double x, double min, double max);

#endif // CONSTS_H