#define _DEFAULT_SOURCE

#include "config.h"
#include "ingrediente.h"
#include "rando.h"


static const int porcaoMediaDoTipo[] = {200, 100, 100, 100, 50, 25, 100};
static const double aceitacaoMediaDoTipo[] = {0.95, 0.9, 0.75, 0.65, 0.65, 0.65, 1.0};


void inicializarIngrediente(Ingrediente *i, TipoIngrediente t)
{
    i->capVasilha = QTDPORCVAS * porcaoMediaDoTipo[t];
    i->chanceAceitacao = rando_normal() + (aceitacaoMediaDoTipo[t] - 0.5);
    i->porcaoMedia = porcaoMediaDoTipo[t];
}


