#ifndef VASILHA_H
#define VASILHA_H

#include "ingrediente.h"

typedef struct
{
    int qtdIng;
    Ingrediente *ingrediente;
} Vasilha;


void inicializarVasilha(Vasilha *v, Ingrediente *i);


#endif // VASILHA_H
