#define _GNU_SOURCE

#include "config.h"
#include "servente.h"
#include "xalloc.h"

#include <stdbool.h>


Servente *servente_new(int hora_atual)
{
    Servente *ptr = xcalloc(1, sizeof(Servente));

    ptr->hora_ultima_mudanca = hora_atual;

    return ptr;
}


Servente *servente_transfere(Servente *servente, int hora_atual)
{
    servente->hora_ultima_mudanca = hora_atual;
    return servente;
}


int servente_inicia_servico(Servente *servente)
{
    servente->cooldown = rand() % (BANSERMAX + 1 - BANSERMIN) + BANSERMIN;
    servente->tempo_servico_acumulado += servente->cooldown;
    ++servente->n_usuarios_servidos;

    return servente->cooldown;
}


void servente_continua_servico(Servente *servente)
{
    --servente->cooldown;
}


bool servente_esta_servindo(const Servente *servente)
{
    return servente->cooldown > 0;
}


bool servente_precisa_descansar(const Servente *servente, int hora_atual)
{
    return (hora_atual - servente->hora_ultima_mudanca) >= TEMPSERMAX;
}


bool servente_pode_trabalhar(const Servente *servente, int hora_atual)
{
    return (hora_atual - servente->hora_ultima_mudanca) >= TEMPSERINT;
}


double servente_tempo_servico_medio(const Servente *servente)
{
    return (double) servente->tempo_servico_acumulado
                    / servente->n_usuarios_servidos;
}
