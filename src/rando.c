#define _DEFAULT_SOURCE

#include "rando.h"

#include <math.h>
#include <stdlib.h>
#include <time.h>


__attribute__((constructor)) void rando_seed(void)
{
    srand(time(0));
}


static double box_muller(void)
{
    const double u1 = rando_uniform();
    const double u2 = rando_uniform();

    return sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
}


double rando_uniform(void)
{
    return rand() / (RAND_MAX + 1.0);
}


int rando_uniform_int(int min, int max)
{
    return rand() % (max - min + 1) + min;
}


double rando_normal(double media, double stddev)
{
    return media + stddev * box_muller();
}


double rando_chi_squared(double hora_fracionada)
{
    const int df = 5;
    const double scale = 6.0;
    const double x = hora_fracionada * 10;

    const double v = exp(-x / 2.0) * pow(x, (df / 2.0) - 1)
                     / ((pow(2, df / 2.0) * tgamma(df / 2.0)));

    return scale * v;
}
