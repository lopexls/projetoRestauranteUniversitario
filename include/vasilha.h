#ifndef VASILHA_H
#define VASILHA_H

#include "ingrediente.h"

typedef struct
{
    int qtdIng;
    const Ingrediente *ingrediente;
} Vasilha;


void inicializarVasilha(Vasilha *v, const Ingrediente *i);

int servirDaVasilha(Vasilha *v);

#endif // VASILHA_H
