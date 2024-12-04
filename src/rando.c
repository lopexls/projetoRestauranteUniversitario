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
    return rand() / (RAND_MAX + 1.0);
}


int rando_uniform_int(int min, int max)
{
    return rand() % (max - min + 1) + min;
}


static double box_muller(void)
{
    const double u1 = rando_uniform();
    const double u2 = rando_uniform();

    return sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
}


double rando_exp(double lambda)
{
    return -log(1 - rando_uniform()) / lambda;
}


double rando_normal(double media, double stddev)
{
    return media + stddev * box_muller();
}


double rando_ex_normal(double media, double stddev, double lambda)
{
    return rando_normal(media, stddev) + rando_exp(lambda);
}
