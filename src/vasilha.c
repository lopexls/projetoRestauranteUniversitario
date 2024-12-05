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
    // Ingrediente não aceito.
    if (rando_uniform() > v->ingrediente->chanceAceitacao)
        return -1;

    const int stddev = v->ingrediente->porcaoMedia / 10;
    const int porcaoServida = rando_normal(v->ingrediente->porcaoMedia, stddev);

    v->qtdIng -= porcaoServida;

    if (v->qtdIng <= 0)
    {
        v->qtdIng = v->ingrediente->capVasilha;
        return TEMPREPOSI;
    }
    else
        return 0;
}
