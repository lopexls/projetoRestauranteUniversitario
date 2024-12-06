#ifndef RANDO_H
#define RANDO_H


double rando_uniform(void);
int rando_uniform_int(int min, int max);
double rando_normal(double media, double stddev);
double rando_chi_squared(double hora_relativa) __attribute__((const));


#endif // RANDO_H
