#ifndef RANDO_H
#define RANDO_H


double rando_uniform(void);
int rando_uniform_int(int min, int max);
double rando_exp(double lambda);
double rando_normal(double media, double stddev);
double rando_ex_normal(double media, double stddev, double lambda);


#endif // RANDO_H
