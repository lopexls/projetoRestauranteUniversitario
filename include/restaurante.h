#ifndef RESTAURANTE_H
#define RESTAURANTE_H

#include "bancada.h"
#include "config.h"
#include "ingrediente.h"
#include "relogio.h"


typedef struct
{
    Refeicao refeicao;
    int velocidade;

    Ingrediente cardapio[NING];
    Bancada *bancadas[QTDBANCADAMAX];
    Descanso *descanso;
} Restaurante;


Restaurante *restaurante_new(Refeicao ref, int velocidade);
void restaurante_free(Restaurante *ru);

int restaurante_simula(Restaurante *ru);


#endif // RESTAURANTE_H
