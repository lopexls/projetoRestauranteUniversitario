#include "rando.h"

#include <math.h>
#include <stdlib.h>
#include <time.h>


__attribute__((constructor)) void rando_seed(void)
{
    srand(time(0));
}


double rando_uniform(void)
{
    return (double) rand() / RAND_MAX;
}


double rando_normal(void)
{
    double u1 = rando_uniform();
    double u2 = rando_uniform();

    return sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
}


int rando_normal_int(int min, int max, int media, double stddev)
{
    return media + stddev * rando_normal();
}
