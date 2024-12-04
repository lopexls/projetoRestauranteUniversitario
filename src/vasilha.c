#define _DEFAULT_SOURCE

#include "config.h"
#include "rando.h"
#include "vasilha.h"


void inicializarVasilha(Vasilha *v, const Ingrediente *i)
{
    v->qtdIng = i->capVasilha;
    v->ingrediente = i;
}


int servirDaVasilha(Vasilha *v)
{
    if (rando_uniform() < v->ingrediente->chanceAceitacao)
        return 0;

    int stddev = v->ingrediente->porcaoMedia / 10;
    int min = v->ingrediente->porcaoMedia - (5 * stddev);
    int max = v->ingrediente->porcaoMedia + (5 * stddev);

    int porcaoServida = rando_normal(v->ingrediente->porcaoMedia, stddev);

    v->qtdIng -= porcaoServida;

    if (v->qtdIng <= 0)
    {
        v->qtdIng = v->ingrediente->capVasilha;
        return TEMPREPOVAS;
    }
    else
        return 0;
}
