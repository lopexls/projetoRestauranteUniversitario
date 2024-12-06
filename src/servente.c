#define _DEFAULT_SOURCE

#include "config.h"
#include "relogio.h"
#include "servente.h"
#include "xalloc.h"

#include <stdbool.h>
#include <stdlib.h>


void servente_free(Servente *servente)
{
    free(servente);
}


Servente *servente_new(void)
{
    return xcalloc(1, sizeof(Servente));
}


Servente *servente_transfere(Servente *servente)
{
    servente->hora_ultima_mudanca = hora_atual;
    return servente;
}


int servente_mais_antigo(const Servente *a, const Servente *b)
{
    if (a->hora_ultima_mudanca < b->hora_ultima_mudanca)
        return -1;
    else if (a->hora_ultima_mudanca > b->hora_ultima_mudanca)
        return 1;
    else
        return 0;
}


int servente_inicia_atendimento(Servente *servente)
{
    int tempo_de_servico = rand() % (TEMPUSUMAX + 1 - TEMPUSUMIN) + TEMPUSUMIN;
    servente->livre_as = hora_atual + tempo_de_servico;
    servente->s_atendimento_acumulado += tempo_de_servico;
    ++servente->n_usuarios_servidos;

    return tempo_de_servico;
}


bool servente_pode_atender(const Servente *servente)
{
    return hora_atual >= servente->livre_as;
}


bool servente_precisa_descansar(const Servente *servente)
{
    return (hora_atual - servente->hora_ultima_mudanca) >= TEMPSERMAX;
}


bool servente_pode_trabalhar(const Servente *servente)
{
    return (hora_atual - servente->hora_ultima_mudanca) >= TEMPSERINT;
}


int servente_tempo_atendimento_medio(const Servente *servente)
{
    return (servente->n_usuarios_servidos?
            servente->s_atendimento_acumulado / servente->n_usuarios_servidos
            : 0);
}
