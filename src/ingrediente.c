#define _DEFAULT_SOURCE

#include "config.h"
#include "ingrediente.h"
#include "rando.h"

#define STDDEVACEITA 0.05

static const int porcaoMediaDoTipo[] = {150, 70, 120, 80, 50, 30, 100};
static const double aceitacaoMediaDoTipo[] = {0.95, 0.9, 0.75, 0.65, 0.65, 0.65, 1.0};


void inicializarIngrediente(Ingrediente *i, TipoIngrediente t)
{
    i->capVasilha = QTDPORCVAS * porcaoMediaDoTipo[t];
    i->porcaoMedia = porcaoMediaDoTipo[t];

    do
    {
        // É preciso garantir que a aceitação o ingrediente esteja no intervalo
        // (0, 1). Isso vai ser verdade na imensa maioria dos casos.
        // Ainda assim, deve ter um jeito melhor de fazer isso.
        i->chanceAceitacao = rando_normal(aceitacaoMediaDoTipo[t], STDDEVACEITA);

    } while (i->chanceAceitacao <= 0.0 || i->chanceAceitacao >= 1.0);
}
