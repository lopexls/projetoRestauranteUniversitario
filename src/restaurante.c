#define _DEFAULT_SOURCE

#include "restaurante.h"
#include "usuario.h"
#include "xalloc.h"

#include <stdlib.h>
#include <stdbool.h>

Restaurante *restaurante_new(Refeicao ref, int velocidade)
{
    Restaurante *new = xmalloc(sizeof(*new));

    new->descanso = descanso_new();

    for (int i = 0; i < NING; ++i)
        inicializarIngrediente(&new->cardapio[i], i);

    for (int i = 0; i < QTDBANCADAMAX; ++i)
        new->bancadas[i] = bancada_new(new->cardapio);

    new->refeicao = ref;
    new->velocidade = velocidade;

    return new;
}


void restaurante_free(Restaurante *ru)
{
    for (int i = 0; i < QTDBANCADAMAX; ++i)
        bancada_free(ru->bancadas[i]);

    descanso_free(ru->descanso);

    free(ru);
}


int restaurante_simula(Restaurante *ru)
{
    relogio_set(ru->refeicao);

    bancada_ativar(ru->bancadas[0], ru->descanso);

    for (int i = 0; i < 50; ++i)
    {
        bancada_recebe_usuario(ru->bancadas[0], usuario_new());
    }

    for (int i = 0; i < 100; ++i)
    {
        Usuario *saindo = bancada_atendimento(ru->bancadas[0]);
        if (saindo)
            usuario_free(saindo);

        ++hora_atual;
    }

    bancada_desativar(ru->bancadas[0], ru->descanso);

    return 0;
}
