#define _DEFAULT_SOURCE

#include "restaurante.h"
#include "xalloc.h"

#include <stdlib.h>


Restaurante *restaurante_new(Refeicao ref, int velocidade)
{
    Restaurante *new = xmalloc(sizeof(*new));

    new->descanso = descanso_new();

    for (int i = 0; i < NING; ++i)
        inicializarIngrediente(&new->cardapio[i], i);

    for (int i = 0; i < QTDBANCADAMAX; ++i)
        new->bancadas[i] = bancada_new(new->cardapio);

    return new;
}


void restaurante_free(Restaurante *restaurante)
{
    for (int i = 0; i < QTDBANCADAMAX; ++i)
        bancada_free(restaurante->bancadas[i]);

    descanso_free(restaurante->descanso);

    free(restaurante);
}


int restaurante_simula(Restaurante *restaurante)
{
    return 0;
}
