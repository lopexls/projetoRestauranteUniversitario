#ifndef VASILHA_H
#define VASILHA_H

#include "ingrediente.h"

#include <stdbool.h>


typedef struct
{
    int qtdIng;
    Ingrediente *ingrediente;
} Vasilha;


void inicializarVasilha(Vasilha *v, Ingrediente *i);

int servirDaVasilha(Vasilha *v, bool vegetariano);

#endif // VASILHA_H
