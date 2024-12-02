#define _DEFAULT_SOURCE

#include "rando.h"
#include "vasilha.h"


void inicializarVasilha(Vasilha *v, Ingrediente *i)
{
    v->qtdIng = i->capVasilha;
    v->ing = i;
}


int servirDaVasilha(Vasilha *v)
{
    if (rando_uniform() < v->ingrediente->chanceAceitacao)
        return 0;

    int stddev = v->ingrediente->porcaoMedia / 10;
    int min = v->ingrediente->porcaoMedia - (5 * stddev);
    int max = v->ingrediente->porcaoMedia + (5 * stddev);

    int porcaoServida = rando_normal_int(min, max,
                                         v->ingrediente->porcaoMedia,
                                         stddev);

    v->qtdIng -= porcaoServida;

    if (v->qtdIng <= 0)
    {
        v->qtdIng = v->ingrediente->capVasilha;
        return TEMPREPOVAS;
    }
    else
        return 0;
}
