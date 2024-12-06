#define _DEFAULT_SOURCE

#include "config.h"
#include "rando.h"
#include "relogio.h"
#include "usuario.h"
#include "xalloc.h"

#include <stdio.h>


void usuario_free(Usuario *u)
{
    free(u);
}


Usuario *usuario_new(void)
{
    Usuario *new = xcalloc(1, sizeof(*new));

    if (rando_uniform() > USUCHANCEVEG)
        new->tipo = CARNIVORO;
    else
        new->tipo = VEGETARIANO;

    new->hora_criacao = hora_atual;

    return new;
}


bool usuario_esta_aguardando(const Usuario *u)
{
    return u->hora_fim_atendimento <= 0;
}


bool usuario_foi_atendido(const Usuario *u)
{
    if (u->hora_fim_atendimento <= 0)
        return false;

    return hora_atual >= u->hora_fim_atendimento;
}


bool usuario_vegetariano(const Usuario *u)
{
    return u->tipo == VEGETARIANO;
}


int usuario_tempo_fila(const Usuario *u)
{
    return u->hora_chega_bancada - u->hora_criacao;
}


int usuario_tempo_atendimento(const Usuario *u)
{
    return u->hora_sai_bancada - u->hora_chega_bancada;
}


int usuario_tempo_total(const Usuario *u)
{
    return usuario_tempo_atendimento(u) + usuario_tempo_fila(u);
}


Usuario *usuario_avancar(Usuario *u)
{
    u->hora_fim_atendimento = -1;
    return u;
}


Usuario *usuario_entrar_bancada(Usuario *u)
{
    u->hora_chega_bancada = hora_atual;
    u->hora_fim_atendimento = -1;
    return u;
}


Usuario *usuario_deixar_bancada(Usuario *u)
{
    u->hora_sai_bancada = hora_atual;
    return u;
}


Usuario *usuario_inicia_atendimento(Usuario *u, int tempo)
{
    u->hora_fim_atendimento = hora_atual + tempo;
    return u;
}
